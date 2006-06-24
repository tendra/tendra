with XASIS.Utils;
with Asis.Elements;
with Asis.Gela.Errors;
with Asis.Expressions;
with Asis.Definitions;
with Asis.Declarations;
with Asis.Gela.Classes;
with Asis.Gela.Resolver;
with Asis.Gela.Overloads;
with Asis.Gela.Element_Utils;
with Asis.Gela.Instances.Utils;

with Gela.Containers.Lists;      use Gela;

package body Asis.Gela.Instances is

   type Pair is record
      Source : Asis.Element;
      Target : Asis.Element;
   end record;

   function "=" (Left, Right : Pair) return Boolean;

   package Pair_Lists is new Containers.Lists (Pair);

   function Find_Target
     (Map    : Pair_Lists.List;
      Source : Asis.Element) return Asis.Element;

   type List_Ptr is access all Pair_Lists.List;

   type Cloner is new Asis.Cloner with record
      Map      : List_Ptr;
      Instance : Asis.Declaration;
      Template : Asis.Declaration;
      Point    : Visibility.Point;
   end record;

   function Clone
     (Object : Cloner;
      Item   : Element;
      Parent : Element) return Element;

   procedure Create_Normalized_Actuals
     (Decl     : Asis.Declaration;
      Template : Asis.Declaration);

   procedure Make_Views
     (Object : Cloner'Class;
      Decl   : Asis.Declaration;
      Point  : Visibility.Point);

   procedure Make_View
     (Object : in     Cloner'Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in out Asis.Expression;
      Point  : in     Visibility.Point);

   procedure Resolve_Actual
     (Actual : in out Asis.Expression;
      Point  : in     Visibility.Point;
      View   : in     Asis.Defining_Name;
      Inst   : in     Asis.Declaration);

   function Get_Template (Name : in Asis.Expression) return Asis.Declaration;

   procedure Find_Formal_Implicit_Operators
     (Formal : Asis.Declaration;
      Actual : Asis.Expression;
      Map    : List_Ptr;
      Place  : Asis.Element);

   procedure Find_Inherited_Subprograms
     (Formal : Asis.Declaration;
      Actual : Asis.Expression;
      Map    : List_Ptr;
      Place  : Asis.Element);

   function Correspond_Oper
     (Formal : Asis.Declaration;
      Actual : Asis.Declaration;
      Place  : Asis.Element) return Boolean;

   function Correspond_Inherited
     (Formal : Asis.Declaration;
      Actual : Asis.Declaration;
      Place  : Asis.Element) return Boolean;


   ---------
   -- "=" --
   ---------

   function "=" (Left, Right : Pair) return Boolean is
   begin
      return Is_Equal (Left.Source, Right.Source);
   end "=";

   -----------
   -- Clone --
   -----------

   function Clone
     (Object : Cloner;
      Item   : Element;
      Parent : Element) return Element
   is
      use Asis.Elements;
      use Asis.Expressions;

      Result : Asis.Element;
      Ref    : Asis.Element;
      Target : Asis.Element;

      procedure Clone_Operators is
         use Asis.Definitions;
         use Asis.Gela.Element_Utils;
         Oper : Asis.Element_List :=
           Corresponding_Type_Operators (Item);
      begin
         for I in Oper'Range loop
            Add_Type_Operator
              (Result, Copy (Object, Oper (I), Result));
         end loop;
      end Clone_Operators;

      procedure Clone_Inherited is
         use Asis.Definitions;
         use Asis.Gela.Element_Utils;
         Oper : Asis.Element_List :=
           Implicit_Inherited_Subprograms (Item);
      begin
         for I in Oper'Range loop
            Add_Inherited_Subprogram
              (Result, Copy (Object, Oper (I), Result));
         end loop;
      end Clone_Inherited;

   begin
      if Is_Equal (Item, Object.Template) then
         Result := Utils.Clone_Declaration (Item, Parent);
      else
         Result := Clone (Item.all, Parent);
         Utils.Set_Instance (Result, Item);
      end if;

      case Element_Kind (Item) is
         when A_Defining_Name =>
            Pair_Lists.Append (Object.Map.all,
                               (Source => Item, Target => Result));

         when An_Expression =>
            case Expression_Kind (Item) is
               when An_Identifier
                 | An_Operator_Symbol
                 | A_Character_Literal
                 | An_Enumeration_Literal =>

                  Ref := Corresponding_Name_Definition (Item);

                  if Assigned (Ref) then
                     Target := Find_Target (Object.Map.all, Ref);
                     if Assigned (Target) then
                        Utils.Set_Generic_Element (Result, Target);
                     else
                        Utils.Set_Generic_Element (Result, Ref);

                        if XASIS.Utils.Is_Child_Of (Ref, Object.Template) then
                           raise Internal_Error;
                        end if;
                     end if;
                  end if;

               when others =>
                  null;
            end case;

         when A_Definition =>
            case Definition_Kind (Item) is
               when A_Type_Definition =>
                  Clone_Operators;

                  case Type_Kind (Item) is
                     when A_Derived_Type_Definition
                       | A_Derived_Record_Extension_Definition =>
                        Clone_Inherited;
                     when others =>
                        null;
                  end case;

               when A_Formal_Type_Definition =>
                  Clone_Operators;

                  case Formal_Type_Kind (Item) is
                     when A_Formal_Derived_Type_Definition =>
                        Clone_Inherited;
                     when others =>
                        null;
                  end case;

               when A_Private_Extension_Definition =>
                  Clone_Inherited;

               when others =>
                  null;
            end case;

         when A_Declaration =>
            case Declaration_Kind (Item) is
               when A_Generic_Instantiation =>
                  declare
                     use Asis.Declarations;
                     Copy     : Asis.Declaration;
                     Expanded : Asis.Declaration :=
                       Corresponding_Declaration (Item);
                  begin
                     Utils.Clone_Views (Object, Item, Result);
                     Copy := Deep_Copy (Object, Expanded, Result);
                     Utils.Set_Corresponding_Declaration (Copy, Result);
                  end;

               when others =>
                  null;
            end case;
         when others =>
            null;
      end case;

      return Result;
   end Clone;

   --------------------------
   -- Correspond_Inherited --
   --------------------------

   function Correspond_Inherited
     (Formal : Asis.Declaration;
      Actual : Asis.Declaration;
      Place  : Asis.Element) return Boolean
   is
      Formal_Base : Asis.Declaration :=
        Element_Utils.Base_Subprogram_Derivation (Formal);
      Actual_Base : Asis.Declaration :=
        Element_Utils.Base_Subprogram_Derivation (Formal);
   begin
      return Is_Equal (Formal_Base, Actual_Base);
   end Correspond_Inherited;

   ---------------------
   -- Correspond_Oper --
   ---------------------

   function Correspond_Oper
     (Formal : Asis.Declaration;
      Actual : Asis.Declaration;
      Place  : Asis.Element) return Boolean
   is
      use Asis.Elements;
      use Asis.Declarations;

      Formal_Kind  : Asis.Operator_Kinds;
      Actual_Kind  : Asis.Operator_Kinds;
   begin
      if not Is_Part_Of_Implicit (Actual) then
         return False;
      end if;

      Formal_Kind := Operator_Kind (Names (Formal) (1));
      Actual_Kind := Operator_Kind (Names (Actual) (1));

      if Formal_Kind /= Actual_Kind then
         return False;
      end if;

      case Actual_Kind is
         when A_Concatenate_Operator
           | A_Multiply_Operator
           | A_Divide_Operator =>

            declare
               use Asis.Gela.Classes;

               function Param_Of_Type
                 (Info  : Type_Info;
                  Param : Asis.Declaration) return Boolean
               is
                  Param_Info   : Type_Info :=
                    Type_Of_Declaration (Param, Place);
               begin
                  return Is_Equal (Info, Param_Info);
               end Param_Of_Type;

               procedure Check_Param
                 (Oper  : in Asis.Declaration;
                  Left  :    out Boolean;
                  Right :    out Boolean)
               is
                  Type_Decl : Asis.Declaration :=
                    Enclosing_Element (Corresponding_Type (Oper));
                  Info      : Type_Info :=
                    Type_From_Declaration (Type_Decl, Place);
                  Param     : Asis.Parameter_Specification_List :=
                    Parameter_Profile (Oper);
               begin
                  Left  := Param_Of_Type (Info, Param (1));
                  Right := Param_Of_Type (Info, Param (2));
               end Check_Param;

               Formal_Left  : Boolean;
               Formal_Right : Boolean;
               Actual_Left  : Boolean;
               Actual_Right : Boolean;
            begin
               Check_Param (Formal, Formal_Left, Formal_Right);
               Check_Param (Actual, Actual_Left, Actual_Right);

               return Formal_Left = Actual_Left
                 and Formal_Right = Actual_Right;
            end;

         when Not_An_Operator =>
            raise Internal_Error;

         when others =>
            return True;
      end case;
   end Correspond_Oper;

   -------------------------------
   -- Create_Normalized_Actuals --
   -------------------------------

   procedure Create_Normalized_Actuals
     (Decl     : Asis.Declaration;
      Template : Asis.Declaration)
   is
      use Asis.Elements;
      use Asis.Gela.Errors;
      use Asis.Declarations;

      function Find_Actual (Name : Asis.Defining_Name) return Asis.Expression;
      function Assoc_Needed (Name : Asis.Defining_Name) return Boolean;

      Index      : Asis.List_Index := 1;
      Actuals    : Asis.Association_List := Generic_Actual_Part (Decl);
      List       : Asis.Element_List := Generic_Formal_Part (Template);

      ------------------
      -- Assoc_Needed --
      ------------------

      function Assoc_Needed (Name : Asis.Defining_Name) return Boolean is
         Decl : Asis.Declaration := Enclosing_Element (Name);
      begin
         case Declaration_Kind (Decl) is
            when A_Formal_Object_Declaration =>
               return not Assigned (Initialization_Expression (Decl));
            when A_Formal_Function_Declaration
              | A_Formal_Procedure_Declaration =>
               return Default_Kind (Decl) = A_Nil_Default;
            when A_Formal_Type_Declaration
              | A_Formal_Package_Declaration
              | A_Formal_Package_Declaration_With_Box =>
               return True;
            when others =>
               raise Internal_Error;
         end case;
      end Assoc_Needed;

      -----------------
      -- Find_Actual --
      -----------------

      function Find_Actual (Name : Asis.Defining_Name) return Asis.Expression
      is
         use Asis.Expressions;
         Result : Asis.Expression;
         Formal : Asis.Expression;
      begin
         for I in Actuals'Range loop
            Formal := Formal_Parameter (Actuals (I));

            if Assigned (Formal)
              and then XASIS.Utils.Has_Name (Name, Name_Image (Formal))
            then
               Element_Utils.Set_Resolved (Formal, (1 => Name));
               return Actual_Parameter (Actuals (I));
            end if;
         end loop;

         if Index <= Actuals'Last
           and then not Assigned (Formal_Parameter (Actuals (Index)))
         then
            Result := Actual_Parameter (Actuals (Index));
            Index  := Index + 1;
         elsif Assoc_Needed (Name) then
            Report (Decl, Error_No_Association_Found,
                    Defining_Name_Image (Name));
         end if;

         return Result;
      end Find_Actual;

   begin  -- Create_Normalized_Actuals
      for I in List'Range loop
         if Element_Kind (List (I)) = A_Declaration then
            declare
               Def_Names : Asis.Defining_Name_List := Names (List (I));
               Actual    : Asis.Expression;
            begin
               for J in Def_Names'Range loop
                  Actual := Find_Actual (Def_Names (J));
                  Utils.New_Normalized_Association
                    (Decl, Def_Names (J), Actual);
               end loop;
            end;
         end if;
      end loop;
   end Create_Normalized_Actuals;

   --------------------------------
   -- Find_Inherited_Subprograms --
   --------------------------------

   procedure Find_Inherited_Subprograms
     (Formal : Asis.Declaration;
      Actual : Asis.Expression;
      Map    : List_Ptr;
      Place  : Asis.Element)
   is
      use Asis.Definitions;
      use Asis.Declarations;

      Found       : Boolean;
      Actual_Decl : Asis.Declaration :=
        XASIS.Utils.Selected_Name_Declaration (Actual, True);
      Actual_Type : Asis.Declaration :=
        Corresponding_First_Subtype (Actual_Decl);
      Actual_Def  : Asis.Definition := Type_Declaration_View (Actual_Type);
      Formal_Def  : Asis.Definition := Type_Declaration_View (Formal);
      F_Oper      : Asis.Element_List :=
        Implicit_Inherited_Subprograms (Formal_Def);
      A_Oper      : Asis.Element_List :=
        Implicit_Inherited_Subprograms (Actual_Def);
      F_Oper_Def  : Asis.Definition;
      A_Oper_Def  : Asis.Definition;
   begin
      for F in F_Oper'Range loop
         Found := False;

         for A in A_Oper'Range loop
            if Correspond_Inherited (F_Oper (F), A_Oper (A), Place) then
               F_Oper_Def := Names (F_Oper (F)) (1);
               A_Oper_Def := Names (A_Oper (A)) (1);
               Pair_Lists.Append
                 (Map.all, (Source => F_Oper_Def, Target => A_Oper_Def));

               if Found then
                  raise Internal_Error;
               end if;

               Found := True;
            end if;
         end loop;

         if not Found then
            --  Report actual type doesn't correspond to formal TODO
            raise Internal_Error;
         end if;
      end loop;
   end Find_Inherited_Subprograms;

   ------------------------------------
   -- Find_Formal_Implicit_Operators --
   ------------------------------------

   procedure Find_Formal_Implicit_Operators
     (Formal : Asis.Declaration;
      Actual : Asis.Expression;
      Map    : List_Ptr;
      Place  : Asis.Element)
   is
      use Asis.Definitions;
      use Asis.Declarations;

      Found       : Boolean;
      Actual_Decl : Asis.Declaration :=
        XASIS.Utils.Selected_Name_Declaration (Actual, True);
      Actual_Type : Asis.Declaration :=
        Corresponding_First_Subtype (Actual_Decl);
      Actual_Def  : Asis.Definition := Type_Declaration_View (Actual_Type);
      Formal_Def  : Asis.Definition := Type_Declaration_View (Formal);
      F_Oper      : Asis.Element_List :=
        Corresponding_Type_Operators (Formal_Def);
      A_Oper      : Asis.Element_List :=
        Corresponding_Type_Operators (Actual_Def.all);
      F_Oper_Def  : Asis.Definition;
      A_Oper_Def  : Asis.Definition;
   begin
      for F in F_Oper'Range loop
         Found := False;

         for A in A_Oper'Range loop
            if Correspond_Oper (F_Oper (F), A_Oper (A), Place) then
               F_Oper_Def := Names (F_Oper (F)) (1);
               A_Oper_Def := Names (A_Oper (A)) (1);
               Pair_Lists.Append
                 (Map.all, (Source => F_Oper_Def, Target => A_Oper_Def));

               if Found then
                  raise Internal_Error;
               end if;

               Found := True;
            end if;
         end loop;

         if not Found then
            --  Report actual type doesn't correspond to formal TODO
            raise Internal_Error;
         end if;
      end loop;
   end Find_Formal_Implicit_Operators;

   -----------------
   -- Find_Target --
   -----------------

   function Find_Target
     (Map    : Pair_Lists.List;
      Source : Asis.Element) return Asis.Element
   is
      Item  : Pair := (Source => Source, Target => Nil_Element);
      Index : Pair_Lists.Cursor := Pair_Lists.Find (Map, Item);
   begin
      if Pair_Lists.Has_Element (Index) then
         Item := Pair_Lists.Element (Index);
         return Item.Target;
      else
         return Asis.Nil_Element;
      end if;
   end Find_Target;

   ------------------
   -- Get_Template --
   ------------------

   function Get_Template (Name : in Asis.Expression) return Asis.Declaration is
      Template    : Asis.Declaration :=
        XASIS.Utils.Selected_Name_Declaration (Name, False);
      Declaration : Asis.Declaration :=
        XASIS.Utils.Declaration_For_Completion (Template);
   begin
      if Assigned (Declaration) then
         return Declaration;
      else
         return Template;
      end if;
   end Get_Template;

   -------------------------------
   -- Make_Instance_Declaration --
   -------------------------------

   procedure Make_Instance_Declaration
     (Decl  : Asis.Declaration;
      Point : Visibility.Point)
   is
      use Asis.Elements;
      use Asis.Gela.Errors;

      Name       : Asis.Expression :=
        Asis.Declarations.Generic_Unit_Name (Decl);
      Template   : Asis.Declaration := Get_Template (Name);
      The_Cloner : Cloner;
      Map        : aliased Pair_Lists.List;
      Copy       : Asis.Declaration;
      Templ_Body : Asis.Declaration;
   begin
      if Declaration_Kind (Template) not in A_Generic_Declaration then
         Report (Name, Error_Generic_Expected);
         return;
      end if;

      The_Cloner.Instance := Decl;
      The_Cloner.Template := Template;
      The_Cloner.Point    := Point;
      The_Cloner.Map      := Map'Unchecked_Access;

      Create_Normalized_Actuals (Decl, Template);
      Make_Views (The_Cloner, Decl, Point);
      Copy := Deep_Copy (The_Cloner, Template, Decl);
      Utils.Set_Corresponding_Declaration (Copy, Decl);
      Resolver.Process_Instance (Copy, Point);

      Templ_Body := Asis.Declarations.Corresponding_Body (Template);

      if Assigned (Templ_Body) then
         Copy := Deep_Copy (The_Cloner, Templ_Body, Decl);
         Utils.Set_Corresponding_Body (Copy, Decl);
      end if;
   end Make_Instance_Declaration;

   ---------------
   -- Make_View --
   ---------------

   procedure Make_View
     (Object : in     Cloner'Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in out Asis.Expression;
      Point  : in     Visibility.Point)
   is
      use Asis.Elements;
      Formal : Asis.Declaration := Enclosing_Element (Name);
      View   : Asis.Defining_Name;
   begin
      case Declaration_Kind (Formal) is
         when A_Formal_Object_Declaration =>
            case Mode_Kind (Formal) is
               when A_Default_In_Mode | An_In_Mode =>
                  View := Utils.Make_Constant (Object, Inst, Name, Actual);
                  Pair_Lists.Append (Object.Map.all,
                                     (Source => Name, Target => View));
               when others =>
                  View := Utils.Make_Object_Renaming
                    (Object, Inst, Name, Actual);
                  Pair_Lists.Append (Object.Map.all,
                                     (Source => Name, Target => View));
            end case;

         when A_Formal_Type_Declaration =>
            View := Utils.Make_Subtype (Object, Inst, Name, Actual);
            Pair_Lists.Append (Object.Map.all,
                               (Source => Name, Target => View));
            Find_Formal_Implicit_Operators (Formal, Actual, Object.Map, Inst);

            if Formal_Type_Kind (Formal) = A_Formal_Derived_Type_Definition
            then
               Find_Inherited_Subprograms (Formal, Actual, Object.Map, Inst);
            end if;

         when A_Formal_Procedure_Declaration =>
            View := Utils.Make_Procedure_Renaming (Object, Inst, Name, Actual);
            Pair_Lists.Append (Object.Map.all,
                               (Source => Name, Target => View));
            Resolve_Actual (Actual, Point, View, Inst);

         when A_Formal_Function_Declaration =>
            View := Utils.Make_Function_Renaming (Object, Inst, Name, Actual);
            Pair_Lists.Append (Object.Map.all,
                               (Source => Name, Target => View));
            Resolve_Actual (Actual, Point, View, Inst);

         when A_Formal_Package_Declaration
           | A_Formal_Package_Declaration_With_Box =>
            View := Utils.Make_Package_Renaming (Object, Inst, Name, Actual);
            Pair_Lists.Append (Object.Map.all,
                               (Source => Name, Target => View));

         when others =>
            null;
      end case;
   end Make_View;

   ----------------
   -- Make_Views --
   ----------------

   procedure Make_Views
     (Object : Cloner'Class;
      Decl   : Asis.Declaration;
      Point  : Visibility.Point)
   is
      use Asis.Expressions;
      use Asis.Declarations;
      Actuals : Asis.Association_List := Generic_Actual_Part (Decl, True);
      Actual  : Asis.Expression;
   begin
      for I in Actuals'Range loop
         Actual := Actual_Parameter (Actuals (I));
         Make_View (Object,
                    Decl,
                    Formal_Parameter (Actuals (I)),
                    Actual,
                    Point);
         if not Is_Equal (Actual, Actual_Parameter (Actuals (I))) then
            raise Internal_Error;
         end if;
      end loop;
   end Make_Views;

   --------------------
   -- Resolve_Actual --
   --------------------

   procedure Resolve_Actual
     (Actual : in out Asis.Expression;
      Point  : in     Visibility.Point;
      View   : in     Asis.Defining_Name;
      Inst   : in     Asis.Declaration)
   is
      use Asis.Elements;
      Decl : Asis.Declaration := Enclosing_Element (View);
   begin
      if not Assigned (Enclosing_Element (Actual)) then
         Element_Utils.Set_Enclosing_Element (Actual, Decl);

         Visibility.Try_To_Resolve (Actual, Point);
         Overloads.Resolve (Actual);

         Element_Utils.Set_Enclosing_Element (Actual, Inst);
      end if;
   end Resolve_Actual;

end Asis.Gela.Instances;


------------------------------------------------------------------------------
--  Copyright (c) 2006, Maxim Reznik
--  All rights reserved.
--
--  Redistribution and use in source and binary forms, with or without
--  modification, are permitted provided that the following conditions are met:
--
--     * Redistributions of source code must retain the above copyright notice,
--     * this list of conditions and the following disclaimer.
--     * Redistributions in binary form must reproduce the above copyright
--     * notice, this list of conditions and the following disclaimer in the
--     * documentation and/or other materials provided with the distribution.
--
--  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
--  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
--  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
--  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
--  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
--  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
--  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
--  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
--  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
--  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
--  POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------
