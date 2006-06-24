with Asis.Elements;
with Asis.Declarations;
with Asis.Gela.Lists;
with Asis.Gela.Elements.Decl;
with Asis.Gela.Elements.Defs;
with Asis.Gela.Elements.Expr;
with Asis.Gela.Element_Utils;
with Asis.Gela.Elements.Assoc;

package body Asis.Gela.Instances.Utils is

   function New_Direct_Name
     (Inst   : Asis.Declaration;
      Name   : Asis.Defining_Name) return Asis.Expression;

   function Clone_Procedure
     (Item   : Asis.Element;
      Parent : Asis.Element) return Asis.Element;

   function Clone_Function
     (Item   : Asis.Element;
      Parent : Asis.Element) return Asis.Element;

   function Clone_Package
     (Item   : Asis.Element;
      Parent : Asis.Element) return Asis.Element;

   -----------------------
   -- Clone_Declaration --
   -----------------------

   function Clone_Declaration
     (Item   : Asis.Element;
      Parent : Asis.Element) return Asis.Element
   is
      use Asis.Elements;
   begin
      case Declaration_Kind (Parent) is
         when A_Package_Instantiation =>
            return Clone_Package (Item, Parent);
         when A_Procedure_Instantiation =>
            return Clone_Procedure (Item, Parent);
         when A_Function_Instantiation =>
            return Clone_Function (Item, Parent);
         when others =>
            raise Internal_Error;
      end case;
   end Clone_Declaration;

   --------------------
   -- Clone_Function --
   --------------------

   function Clone_Function
     (Item   : Asis.Element;
      Parent : Asis.Element)
      return Asis.Element
   is
      use Asis.Gela.Elements.Decl;

      Result : Function_Declaration_Ptr := new Function_Declaration_Node;
   begin
      Set_Enclosing_Element (Result.all, Parent);
      Set_Enclosing_Compilation_Unit
        (Result.all, Enclosing_Compilation_Unit (Parent.all));
      Set_Is_Dispatching_Operation
        (Result.all, Is_Dispatching_Operation (Item.all));
      Set_Trait_Kind (Result.all, An_Ordinary_Trait);
      Set_Instance (Asis.Element (Result), Item);

      return Asis.Element (Result);
   end Clone_Function;

   -------------------
   -- Clone_Package --
   -------------------

   function Clone_Package
     (Item   : Asis.Element;
      Parent : Asis.Element)
      return Asis.Element
   is
      use Asis.Gela.Elements.Decl;

      Result : Package_Declaration_Ptr := new Package_Declaration_Node;
   begin
      Set_Enclosing_Element (Result.all, Parent);
      Set_Enclosing_Compilation_Unit
        (Result.all, Enclosing_Compilation_Unit (Parent.all));
      Set_Instance (Asis.Element (Result), Item);

      return Asis.Element (Result);
   end Clone_Package;

   ---------------------
   -- Clone_Procedure --
   ---------------------

   function Clone_Procedure
     (Item   : Asis.Element;
      Parent : Asis.Element)
      return Asis.Element
   is
      use Asis.Gela.Elements.Decl;

      Result : Procedure_Declaration_Ptr := new Procedure_Declaration_Node;
   begin
      Set_Enclosing_Element (Result.all, Parent);
      Set_Enclosing_Compilation_Unit
        (Result.all, Enclosing_Compilation_Unit (Parent.all));
      Set_Is_Dispatching_Operation
        (Result.all, Is_Dispatching_Operation (Item.all));
      Set_Trait_Kind (Result.all, An_Ordinary_Trait);
      Set_Instance (Asis.Element (Result), Item);

      return Asis.Element (Result);
   end Clone_Procedure;

   -----------------
   -- Clone_Views --
   -----------------

   procedure Clone_Views
     (Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Target : in     Asis.Declaration)
   is
      use Asis.Gela.Elements.Decl;
      use Lists.Primary_Declaration_Lists;

      View_List : Asis.Element;
      Node      : Package_Instantiation_Node'Class
        renames Package_Instantiation_Node'Class (Inst.all);
      Result    : Package_Instantiation_Node'Class
        renames Package_Instantiation_Node'Class (Target.all);
      Views     : Asis.Element_List :=
        To_Element_List (List (Parameter_Views_List (Node)).all, False);
   begin
      View_List := Deep_Copy (Views, Object, Target);
      Set_Parameter_Views (Result, View_List);
   end Clone_Views;

   ---------------------
   -- Set_Declaration --
   ---------------------

   procedure Set_Declaration
     (Result : access Elements.Declaration_Node'Class;
      Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name)
   is
      use Asis.Elements;
      use Asis.Gela.Lists;
      use Asis.Gela.Elements;
      use Asis.Gela.Elements.Decl;
      use Primary_Defining_Name_Lists;
      Name_List : Asis.Element;
      View_List : Primary_Declaration_Lists.List;
      Formal    : Asis.Declaration := Enclosing_Element (Name);
      Node      : Package_Instantiation_Node'Class
        renames Package_Instantiation_Node'Class (Inst.all);
   begin
      if Assigned (Parameter_Views_List (Node)) then
         View_List :=
           Primary_Declaration_Lists.List (Parameter_Views_List (Node));
      else
         View_List := new Primary_Declaration_Lists.List_Node;
         Set_Parameter_Views (Node, Asis.Element (View_List));
      end if;

      Primary_Declaration_Lists.Add
        (View_List.all, Asis.Element (Result));

      Set_Enclosing_Element (Result.all, Inst);
      Set_Enclosing_Compilation_Unit
        (Result.all, Enclosing_Compilation_Unit (Inst.all));
      Set_Declaration_Origin (Result.all, An_Explicit_Declaration);

      Name_List := Lists.Primary_Defining_Name_Lists.Deep_Copy
        ((1 => Name), Object, Asis.Element (Result));

      Set_Names (Result.all, Name_List);
      Set_Instance (Asis.Element (Result), Formal);
   end Set_Declaration;

   -------------------
   -- Make_Constant --
   -------------------

   function Make_Constant
     (Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in     Asis.Expression)
     return Asis.Defining_Name
   is
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Gela.Elements.Decl;
      use Asis.Gela.Elements.Defs;

      Result    : Constant_Declaration_Ptr := new Constant_Declaration_Node;
      Formal    : Asis.Declaration := Enclosing_Element (Name);
      Mark      : Asis.Expression := Declaration_Subtype_Mark (Formal);
      Ind       : Subtype_Indication_Ptr := new Subtype_Indication_Node;
   begin
      Set_Declaration (Result, Object, Inst, Name);
      Set_Trait_Kind (Result.all, An_Ordinary_Trait);

      Set_Enclosing_Element (Ind.all, Asis.Element (Result));
      Set_Enclosing_Compilation_Unit
        (Ind.all, Enclosing_Compilation_Unit (Inst.all));

      Mark := Deep_Copy (Cloner => Object,
                         Source => Mark,
                         Parent => Asis.Element (Ind));

      Set_Subtype_Mark (Ind.all, Asis.Element (Mark));
      Set_Object_Declaration_View (Result.all, Asis.Element (Ind));
      Set_Initialization_Expression (Result.all, Actual);

      return Names (Result.all) (1);
   end Make_Constant;

   ---------------------------
   --  Make_Object_Renaming --
   ---------------------------

   function Make_Object_Renaming
     (Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in     Asis.Expression) return Asis.Defining_Name
   is
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Gela.Elements.Decl;
      use Asis.Gela.Elements.Defs;
      Result    : Object_Renaming_Declaration_Ptr :=
        new Object_Renaming_Declaration_Node;
      Formal    : Asis.Declaration := Enclosing_Element (Name);
      Mark      : Asis.Expression := Declaration_Subtype_Mark (Formal);
   begin
      Set_Declaration (Result, Object, Inst, Name);
      Mark := Deep_Copy (Cloner => Object,
                         Source => Mark,
                         Parent => Asis.Element (Result));
      Set_Declaration_Subtype_Mark (Result.all, Asis.Element (Mark));
      Set_Renamed_Entity (Result.all, Actual);

      return Names (Result.all) (1);
   end Make_Object_Renaming;

   ---------------------------
   -- Make_Package_Renaming --
   ---------------------------

   function Make_Package_Renaming
     (Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in     Asis.Expression) return Asis.Defining_Name
   is
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Gela.Elements.Decl;
      Result    : Package_Renaming_Declaration_Ptr :=
        new Package_Renaming_Declaration_Node;
   begin
      Set_Declaration (Result, Object, Inst, Name);
      Set_Renamed_Entity (Result.all, Actual);

      return Names (Result.all) (1);
   end Make_Package_Renaming;

   -----------------------------
   --  Make_Function_Renaming --
   -----------------------------

   function Make_Function_Renaming
     (Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in     Asis.Expression) return Asis.Defining_Name
   is
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Gela.Elements.Decl;
      use Lists.Primary_Parameter_Lists;
      Formal    : Asis.Declaration := Enclosing_Element (Name);
      Profile   : Asis.Element;
      Result    : Function_Renaming_Declaration_Ptr :=
        new Function_Renaming_Declaration_Node;
      Params    : Asis.Element_List :=
        Parameter_Profile (Formal);
   begin
      Set_Declaration (Result, Object, Inst, Name);
      Set_Renamed_Entity (Result.all, Actual);
      Profile := Lists.Primary_Parameter_Lists.Deep_Copy
        (Params, Object, Asis.Element (Result));
      Set_Parameter_Profile (Result.all, Profile);
      Set_Result_Profile
        (Result.all,
         Deep_Copy (Cloner => Object,
                    Source => Result_Profile (Formal),
                    Parent => Asis.Element (Result)));

      return Names (Result.all) (1);
   end Make_Function_Renaming;

   -----------------------------
   -- Make_Procedure_Renaming --
   -----------------------------

   function Make_Procedure_Renaming
     (Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in     Asis.Expression) return Asis.Defining_Name
   is
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Gela.Elements.Decl;
      use Lists.Primary_Parameter_Lists;
      Formal    : Asis.Declaration := Enclosing_Element (Name);
      Profile   : Asis.Element;
      Result    : Procedure_Renaming_Declaration_Ptr :=
        new Procedure_Renaming_Declaration_Node;
      Params    : Asis.Element_List :=
        Parameter_Profile (Formal);
   begin
      Set_Declaration (Result, Object, Inst, Name);
      Set_Renamed_Entity (Result.all, Actual);
      Profile := Lists.Primary_Parameter_Lists.Deep_Copy
        (Params, Object, Asis.Element (Result));
      Set_Parameter_Profile (Result.all, Profile);

      return Names (Result.all) (1);
   end Make_Procedure_Renaming;

   ------------------
   -- Make_Subtype --
   ------------------

   function Make_Subtype
     (Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in     Asis.Expression) return Asis.Defining_Name
   is
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Gela.Elements.Defs;
      use Asis.Gela.Elements.Decl;
      Result    : Subtype_Declaration_Ptr := new Subtype_Declaration_Node;
      Ind       : Subtype_Indication_Ptr := new Subtype_Indication_Node;
   begin
      Set_Declaration (Result, Object, Inst, Name);
      Set_Enclosing_Element (Ind.all, Asis.Element (Result));
      Set_Enclosing_Compilation_Unit
        (Ind.all, Enclosing_Compilation_Unit (Inst.all));
      Set_Subtype_Mark (Ind.all, Actual);
      Set_Type_Declaration_View (Result.all, Asis.Element (Ind));

      return Names (Result.all) (1);
   end Make_Subtype;

   ---------------------
   -- New_Direct_Name --
   ---------------------

   type Base_Identifier_Access is
     access all Asis.Gela.Elements.Expr.Base_Identifier_Node'Class;

   function New_Direct_Name
     (Inst   : Asis.Declaration;
      Name   : Asis.Defining_Name) return Asis.Expression
   is
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Gela.Elements.Expr;

      Result : Base_Identifier_Access;
   begin
      case Defining_Name_Kind (Name) is
         when A_Defining_Identifier =>
            Result := new Identifier_Node;
         when A_Defining_Operator_Symbol =>
            Result := new Operator_Symbol_Node;
            Set_Operator_Kind
              (Operator_Symbol_Node (Result.all),
               Operator_Kind (Name));
         when others =>
            raise Internal_Error;
      end case;

      Set_Name_Image (Result.all, Defining_Name_Image (Name));
      Set_Enclosing_Element (Result.all, Asis.Nil_Element);  --  Mark the Name
--      Set_Enclosing_Element (Result.all, Inst);
      Set_Start_Position (Result.all, (1, 1));
      Set_End_Position (Result.all, Nil_Text_Position);
      Set_Enclosing_Compilation_Unit
        (Result.all, Enclosing_Compilation_Unit (Inst.all));

      return Asis.Expression (Result);
   end New_Direct_Name;

   --------------------------------
   -- New_Normalized_Association --
   --------------------------------

   procedure New_Normalized_Association
     (Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in out Asis.Expression)
   is
      use Asis.Elements;
      use Asis.Declarations;
      use Asis.Gela.Elements.Decl;
      use Asis.Gela.Elements.Assoc;

      Formal : Asis.Declaration := Enclosing_Element (Name);
      Result : Generic_Association_Ptr := new Generic_Association_Node;
      Node   : Package_Instantiation_Node'Class renames
        Package_Instantiation_Node'Class (Inst.all);
   begin
      if not Assigned (Actual) then
         case Declaration_Kind (Formal) is
            when A_Formal_Object_Declaration =>
               Actual := Initialization_Expression (Formal);

            when A_Formal_Function_Declaration
              | A_Formal_Procedure_Declaration =>
               case Default_Kind (Formal) is
                  when A_Name_Default =>
                     Actual := Formal_Subprogram_Default (Formal);

                  when A_Box_Default =>
                     Actual := New_Direct_Name (Inst, Name);

                  when others =>
                     null;
               end case;

            when others =>
               null;
         end case;

         Set_Is_Defaulted_Association (Result.all, True);
      end if;

      Set_Is_Normalized (Result.all, True);
      Set_Enclosing_Element (Result.all, Inst);
      Set_Enclosing_Compilation_Unit
        (Result.all, Enclosing_Compilation_Unit (Inst.all));
      Set_Formal_Parameter (Result.all, Name);
      Set_Actual_Parameter (Result.all, Actual);
      Set_Start_Position (Result.all, (1, 1));
      Set_End_Position (Result.all, Nil_Text_Position);

      Add_To_Normalized_Generic_Actual_Part (Node, Asis.Element (Result));
   end New_Normalized_Association;

   ----------------------------
   -- Set_Corresponding_Body --
   ----------------------------

   procedure Set_Corresponding_Body (Item, Source : Asis.Element) is
      use Asis.Gela.Elements.Decl;
      Node : Package_Instantiation_Node'Class renames
        Package_Instantiation_Node'Class (Source.all);
   begin
      Set_Corresponding_Body (Node, Item);
   end Set_Corresponding_Body;

   -----------------------------------
   -- Set_Corresponding_Declaration --
   -----------------------------------

   procedure Set_Corresponding_Declaration (Item, Source : Asis.Element) is
      use Asis.Gela.Elements.Decl;
      Node : Package_Instantiation_Node'Class renames
        Package_Instantiation_Node'Class (Source.all);
   begin
      Set_Corresponding_Declaration (Node, Item);
   end Set_Corresponding_Declaration;

   -------------------------
   -- Set_Generic_Element --
   -------------------------

   procedure Set_Generic_Element (Item, Source : Asis.Element) is
      use Asis.Gela.Elements.Expr;
      Node : Base_Identifier_Node'Class renames
        Base_Identifier_Node'Class (Item.all);
   begin
      Set_Corresponding_Generic_Element (Node, Source);
      Element_Utils.Set_Resolved (Item, (1 => Source));
   end Set_Generic_Element;

   ------------------
   -- Set_Instance --
   ------------------

   procedure Set_Instance (Item, Source : Asis.Element) is
      use Asis.Gela.Elements;

      Result : Base_Element_Ptr := Base_Element_Ptr (Item);
   begin
      Set_Is_Part_Of_Instance (Result.all, True);
      Set_Start_Position (Result.all, (1, 1));
      Set_End_Position (Result.all, Nil_Text_Position);

      if Element_Kind (Item.all) = A_Defining_Name then
         Set_Corresponding_Generic_Element
           (Defining_Name_Node (Item.all), Source);
      end if;
   end Set_Instance;

end Asis.Gela.Instances.Utils;



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
