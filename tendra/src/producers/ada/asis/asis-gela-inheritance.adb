with XASIS.Types;
with XASIS.Utils;
with Asis.Elements;
with Asis.Statements;
with Asis.Definitions;
with Asis.Declarations;
with Asis.Gela.Classes;
with Asis.Gela.Element_Utils;
with Asis.Gela.Inheritance.Utils;

package body Asis.Gela.Inheritance is

   function Operate_On_Type
     (Oper : Asis.Declaration;
      Tipe : Classes.Type_Info) return Boolean;

   function Get_Declarative_Items
     (Item : Asis.Element) return Asis.Declaration_List;

   function Override (Decl : Asis.Declaration) return Boolean;

   function Is_Ext_Equal_Operator
     (Decl : Asis.Declaration;
      Tipe : Classes.Type_Info) return Boolean;

   procedure Make_Inherited_Subprogram
     (Oper   : Asis.Declaration;
      Point  : in out Visibility.Point;
      Tipe   : Classes.Type_Info;
      Parent : Classes.Type_Info);

   type Cloner is new Asis.Cloner with record
      Tipe   : Classes.Type_Info;
      Parent : Classes.Type_Info;
   end record;

   function Clone
     (Object : Cloner;
      Item   : Element;
      Parent : Element) return Element;

   -----------
   -- Clone --
   -----------

   function Clone
     (Object : Cloner;
      Item   : Element;
      Parent : Element) return Element
   is
      use Asis.Elements;
      use Asis.Gela.Classes;

      Result : Asis.Element;
      Expr   : Asis.Expression;
      Place  : Asis.Element := Get_Place (Object.Tipe);
      Tipe   : Type_Info;
      Upper  : Asis.Element := Enclosing_Element (Item.all);
   begin
      case Element_Kind (Parent) is
         when A_Declaration =>
            case Declaration_Kind (Parent) is
               when A_Parameter_Specification =>

                  Expr := Declaration_Subtype_Mark (Upper.all);

                  if Is_Equal (Item, Expr) then
                     Tipe := Type_From_Subtype_Mark (Expr, Place);

                     if Is_Equal (Tipe, Object.Parent) then
                        return Utils.Clone_Type (Item, Parent, Object.Tipe);
                     end if;
                  end if;

               when A_Function_Declaration =>

                  Expr := XASIS.Utils.Get_Result_Profile (Upper);

                  if Is_Equal (Item, Expr) then
                     Tipe := Type_From_Subtype_Mark (Expr, Place);

                     if Is_Equal (Tipe, Object.Parent) then
                        return Utils.Clone_Type (Item, Parent, Object.Tipe);
                     end if;
                  end if;

               when others =>
                  null;
            end case;

         when others =>
            null;
      end case;

      case Element_Kind (Item) is
         when A_Declaration =>
            case Declaration_Kind (Item) is
               when A_Function_Declaration
                 | A_Function_Body_Declaration
                 | A_Function_Body_Stub
                 | A_Function_Renaming_Declaration
                 | A_Generic_Function_Declaration
                 | A_Formal_Function_Declaration
                 | An_Enumeration_Literal_Specification =>

                  return Utils.Clone_Function (Item, Parent);

               when A_Procedure_Declaration
                 | A_Procedure_Body_Declaration
                 | A_Procedure_Body_Stub
                 | A_Procedure_Renaming_Declaration
                 | A_Generic_Procedure_Declaration
                 | A_Formal_Procedure_Declaration =>

                  return Utils.Clone_Procedure (Item, Parent);

               when others =>
                  null;
            end case;

         when others =>
            null;
      end case;

      Result := Clone (Item.all, Parent);
      Utils.Set_Inherited (Result);
      return Result;
   end Clone;

   ---------------------------
   -- Get_Declarative_Items --
   ---------------------------

   function Get_Declarative_Items
     (Item : Asis.Element) return Asis.Declaration_List
   is
      use Asis.Elements;
   begin
      case Element_Kind (Item) is
         when A_Statement =>
            case Statement_Kind (Item) is
               when A_Block_Statement =>
                  return Asis.Statements.Block_Declarative_Items (Item);
               when others =>
                  null;
            end case;

         when A_Declaration =>
            case Declaration_Kind (Item) is
               when A_Function_Body_Declaration |
                 A_Procedure_Body_Declaration |
                 A_Package_Body_Declaration |
                 A_Task_Body_Declaration |
                 An_Entry_Body_Declaration =>

                  return Asis.Declarations.Body_Declarative_Items (Item);

               when others =>
                  null;
            end case;

         when others =>
            null;
      end case;
      return Nil_Element_List;
   end Get_Declarative_Items;

   ---------------------------
   -- Is_Ext_Equal_Operator --
   ---------------------------

   function Is_Ext_Equal_Operator
     (Decl : Asis.Declaration;
      Tipe : Classes.Type_Info) return Boolean
   is
      use Asis.Elements;
      use Asis.Gela.Classes;

      Name : Asis.Element_List :=
        Asis.Declarations.Names (Decl);
      Kind : Asis.Operator_Kinds :=
        Operator_Kind (Name (1));
      Expr : Asis.Expression;
      Info : Type_Info;
      Base : Asis.Declaration;
      Def  : Asis.Definition := Get_Type_Def (Tipe);
   begin
      if Type_Kind (Def) /= A_Derived_Record_Extension_Definition
      then
         return False;
      end if;

      if Kind /= An_Equal_Operator then
         return False;
      end if;

      Expr := XASIS.Utils.Get_Result_Profile (Decl);
      Info := Type_From_Subtype_Mark (Expr, Get_Place (Tipe));
      Base := Classes.Get_Declaration (Info);

      if not Is_Equal (Base, XASIS.Types.Boolean) then
         return False;
      end if;

      declare
         List : Asis.Parameter_Specification_List
           := XASIS.Utils.Get_Profile (Decl);
      begin
         if List'Length = 2 and then
           not Is_Equal (Type_Of_Declaration (List (1), Get_Place (Tipe)),
                         Type_Of_Declaration (List (2), Get_Place (Tipe)))
         then
            return False;
         end if;
      end;

      return True;
   end Is_Ext_Equal_Operator;

   -------------------------------
   -- Make_Inherited_Subprogram --
   -------------------------------

   procedure Make_Inherited_Subprogram
     (Oper   : Asis.Declaration;
      Point  : in out Visibility.Point;
      Tipe   : Classes.Type_Info;
      Parent : Classes.Type_Info)
   is
      use Asis.Elements;

      The_Cloner : Cloner;
      Def        : Asis.Definition := Classes.Get_Type_Def (Tipe);
      Decl       : Asis.Declaration := Classes.Get_Declaration (Tipe);
      Overriden  : Boolean;
      Result     : Asis.Declaration;
   begin
      The_Cloner.Tipe   := Tipe;
      The_Cloner.Parent := Parent;
      Result := Deep_Copy (The_Cloner, Oper, Def);

      if Declaration_Kind (Oper) = An_Enumeration_Literal_Specification then
         Utils.Set_Result_Profile (Result, Tipe);
      end if;

      Visibility.New_Implicit_Declaration (Result, Point, Decl, Overriden);

      if not Overriden then
         Element_Utils.Add_Inherited_Subprogram (Def, Result);
      end if;
   end Make_Inherited_Subprogram;

   --------------------------------
   -- Make_Inherited_Subprograms --
   --------------------------------

   procedure Make_Inherited_Subprograms
     (Decl  : Asis.Declaration;
      Point : in out Visibility.Point)
   is
      Tipe   : Classes.Type_Info := Classes.Type_From_Declaration (Decl, Decl);
      Parent : Classes.Type_Info := Classes.Parent_Type (Tipe);
   begin
      if Classes.Is_Not_Type (Parent) then
         return;
      end if;

      declare
         List : Asis.Declaration_List := User_Primitive_Subprograms (Parent);
      begin
         for I in List'Range loop
            if not Is_Ext_Equal_Operator (List (I), Tipe) then
               Make_Inherited_Subprogram (List (I), Point, Tipe, Parent);
            end if;
         end loop;
      end;
   end Make_Inherited_Subprograms;

   ---------------------
   -- Operate_On_Type --
   ---------------------

   function Operate_On_Type
     (Oper : Asis.Declaration;
      Tipe : Classes.Type_Info) return Boolean
   is
      use XASIS.Utils;
      Expr  : Asis.Expression;
      Info  : Classes.Type_Info;
      Place : Asis.Element := Classes.Get_Place (Tipe);
   begin
      case Asis.Elements.Declaration_Kind (Oper) is
         when A_Function_Declaration
           | A_Function_Body_Declaration
           | A_Function_Body_Stub
           | A_Function_Renaming_Declaration
           | A_Generic_Function_Declaration
           | A_Formal_Function_Declaration =>

            Expr := Get_Result_Profile (Oper);
            Info := Classes.Type_From_Subtype_Mark (Expr, Place);

            if Classes.Is_Equal (Info, Tipe) then
               return True;
            end if;

         when A_Procedure_Declaration
           | A_Procedure_Body_Declaration
           | A_Procedure_Body_Stub
           | A_Procedure_Renaming_Declaration
           | A_Generic_Procedure_Declaration
           | A_Formal_Procedure_Declaration =>

            null;

         when others =>
            return False;
      end case;

      declare
         List : constant Asis.Parameter_Specification_List :=
           Get_Profile (Oper);
      begin
         for I in List'Range loop
            Info := Classes.Type_Of_Declaration (List (I), Place);

            if Classes.Is_Expected_Type (Info, Tipe) then
               return True;
            end if;
         end loop;
      end;

      return False;
   end Operate_On_Type;

   --------------
   -- Override --
   --------------

   function Override (Decl : Asis.Declaration) return Boolean is
      package U renames Asis.Gela.Element_Utils;
      List : constant Asis.Defining_Name_List :=
        Asis.Declarations.Names (Decl);
   begin
      return Assigned (U.Override (List (1)));
   end Override;

   --------------------------------
   -- User_Primitive_Subprograms --
   --------------------------------

   function User_Primitive_Subprograms
     (Info : Classes.Type_Info)
      return Asis.Declaration_List
   is
      function Get_Inherited (Def : Asis.Definition)
        return Asis.Declaration_List;

      function Get_Enum_Literals (Def : Asis.Definition)
        return Asis.Declaration_List;

      function Get_Package_Operations (Info : Classes.Type_Info)
        return Asis.Declaration_List;

      function Get_Other_Operations (Info : Classes.Type_Info)
        return Asis.Declaration_List;

      -------------------
      -- Get_Inherited --
      -------------------

      function Get_Inherited (Def : Asis.Definition)
        return Asis.Declaration_List
      is
         Def_Kind : Asis.Definition_Kinds :=
           Asis.Elements.Definition_Kind (Def);
      begin
         if Def_Kind = A_Private_Extension_Definition
           or else
           (Def_Kind = A_Type_Definition and then
            Asis.Elements.Type_Kind (Def) in
              A_Derived_Type_Definition ..
              A_Derived_Record_Extension_Definition)
           or else
           (Def_Kind = A_Formal_Type_Definition and then
            Asis.Elements.Formal_Type_Kind (Def) =
              A_Formal_Derived_Type_Definition)
         then
            declare
               Index : Asis.ASIS_Natural := 0;
               List  : Asis.Declaration_List :=
                 Asis.Definitions.Implicit_Inherited_Declarations (Def);
            begin
               for I in List'Range loop
                  if XASIS.Utils.Overloadable_Declaration (List (I)) then
                     Index := Index + 1;
                     List (Index) := List (I);
                  end if;
               end loop;

               return List (1 .. Index);
            end;
         else
            return Nil_Element_List;
         end if;
      end Get_Inherited;

      -----------------------
      -- Get_Enum_Literals --
      -----------------------

      function Get_Enum_Literals (Def : Asis.Definition)
        return Asis.Declaration_List
      is
         Def_Kind : Asis.Type_Kinds := Asis.Elements.Type_Kind (Def);
      begin
         if Def_Kind = An_Enumeration_Type_Definition then
            return Asis.Definitions.Enumeration_Literal_Declarations (Def);
         else
            return Nil_Element_List;
         end if;
      end Get_Enum_Literals;

      ----------------------------
      -- Get_Package_Operations --
      ----------------------------

      function Get_Package_Operations (Info : Classes.Type_Info)
        return Asis.Declaration_List
      is
         Decl : constant Asis.Declaration :=
           Classes.Get_Declaration (Info);
         Pkg  : constant Asis.Declaration :=
           Asis.Elements.Enclosing_Element (Decl);
      begin
         if Asis.Elements.Declaration_Kind (Pkg) /= A_Package_Declaration then
            return Nil_Element_List;
         end if;

         declare
            Index : Asis.ASIS_Natural := 0;
            List  : Asis.Declaration_List :=
              Asis.Declarations.Visible_Part_Declarative_Items (Pkg) &
              Asis.Declarations.Private_Part_Declarative_Items (Pkg);
         begin
            for I in List'Range loop
               if Operate_On_Type (List (I), Info) then
                  Index := Index + 1;
                  List (Index) := List (I);
               end if;
            end loop;

            return List (1 .. Index);
         end;
      end Get_Package_Operations;

      --------------------------
      -- Get_Other_Operations --
      --------------------------

      function Get_Other_Operations (Info : Classes.Type_Info)
        return Asis.Declaration_List
      is
         Decl   : constant Asis.Declaration :=
           Classes.Get_Declaration (Info);
         Parent : constant Asis.Element :=
           Asis.Elements.Enclosing_Element (Decl);
      begin
         if Asis.Elements.Declaration_Kind (Parent) = A_Package_Declaration
         then
            return Nil_Element_List;
         end if;

         declare
            Index : Asis.ASIS_Natural := 0;
            List  : Asis.Declaration_List :=
              Get_Declarative_Items (Parent);
         begin
            for I in List'Range loop
               if Operate_On_Type (List (I), Info)
                 and then Override (List (I))
                 and then not XASIS.Utils.Is_Completion (List (I))
               then
                  Index := Index + 1;
                  List (Index) := List (I);
               end if;
            end loop;

            return List (1 .. Index);
         end;
      end Get_Other_Operations;

      Def    : constant Asis.Definition := Classes.Get_Type_Def (Info);
      Result : constant Asis.Declaration_List :=
        Get_Inherited (Def) &
        Get_Enum_Literals (Def) &
        Get_Package_Operations (Info) &
        Get_Other_Operations (Info);
   begin
      return Result;
   end User_Primitive_Subprograms;

end Asis.Gela.Inheritance;


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
