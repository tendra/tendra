------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Procedural wrapper over Object-Oriented ASIS implementation

package body Asis.Declarations is

   --------------------------
   -- Body_Block_Statement --
   --------------------------

   function Body_Block_Statement
     (Declaration : in Asis.Declaration)
      return Asis.Statement
   is
   begin
      Check_Nil_Element (Declaration, "Body_Block_Statement");
      raise Unimplemented;
      return Nil_Element;
   end Body_Block_Statement;

   ----------------------------
   -- Body_Declarative_Items --
   ----------------------------

   function Body_Declarative_Items
     (Declaration     : in Asis.Declaration;
      Include_Pragmas : in Boolean := False)
      return Asis.Element_List
   is
   begin
      Check_Nil_Element (Declaration, "Body_Declarative_Items");
      return Body_Declarative_Items (Declaration.all, Include_Pragmas);
   end Body_Declarative_Items;

   -----------------------------
   -- Body_Exception_Handlers --
   -----------------------------

   function Body_Exception_Handlers
     (Declaration     : in Asis.Declaration;
      Include_Pragmas : in Boolean := False)
      return Asis.Exception_Handler_List
   is
   begin
      Check_Nil_Element (Declaration, "Body_Exception_Handlers");
      return Body_Exception_Handlers (Declaration.all, Include_Pragmas);
   end Body_Exception_Handlers;

   ---------------------
   -- Body_Statements --
   ---------------------

   function Body_Statements
     (Declaration     : in Asis.Declaration;
      Include_Pragmas : in Boolean := False)
      return Asis.Statement_List
   is
   begin
      Check_Nil_Element (Declaration, "Body_Statements");
      return Body_Statements (Declaration.all, Include_Pragmas);
   end Body_Statements;

   -------------------------------
   -- Corresponding_Base_Entity --
   -------------------------------

   function Corresponding_Base_Entity
     (Declaration : in Asis.Declaration)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Declaration, "Corresponding_Base_Entity");
      return Corresponding_Base_Entity (Declaration.all);
   end Corresponding_Base_Entity;

   ------------------------
   -- Corresponding_Body --
   ------------------------

   function Corresponding_Body
     (Declaration : in Asis.Declaration)
      return Asis.Declaration
   is
   begin
      case Declaration_Kind (Declaration.all) is
         when
           A_Function_Body_Declaration
           | A_Function_Body_Stub
           | A_Function_Renaming_Declaration
           | A_Package_Body_Declaration
           | A_Package_Body_Stub
           | A_Package_Renaming_Declaration
           | A_Procedure_Body_Declaration
           | A_Procedure_Renaming_Declaration
           | A_Procedure_Body_Stub
           | A_Task_Body_Declaration
           | A_Task_Body_Stub
           | A_Protected_Body_Declaration
           | A_Protected_Body_Stub
           | A_Generic_Package_Renaming_Declaration
           | A_Generic_Procedure_Renaming_Declaration
           | A_Generic_Function_Renaming_Declaration
           | An_Entry_Body_Declaration =>
            return Declaration;
         when others =>
            null;
      end case;

      Check_Nil_Element (Declaration, "Corresponding_Body");
      return Corresponding_Body (Declaration.all);
   end Corresponding_Body;

   ------------------------
   -- Corresponding_Body --
   ------------------------

   function Corresponding_Body
     (Declaration : in Asis.Declaration;
      The_Context : in Asis.Context)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Declaration, "Corresponding_Body");
      Check_Context (The_Context);
      return Corresponding_Body (Declaration, The_Context.all);
   end Corresponding_Body;

   -----------------------------
   -- Corresponding_Body_Stub --
   -----------------------------

   function Corresponding_Body_Stub
     (Subunit : in Asis.Declaration)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Subunit, "Corresponding_Body_Stub");
      return Corresponding_Body_Stub (Subunit.all);
   end Corresponding_Body_Stub;

   -----------------------------
   -- Corresponding_Body_Stub --
   -----------------------------

   function Corresponding_Body_Stub
     (Subunit     : in Asis.Declaration;
      The_Context : in Asis.Context)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Subunit, "Corresponding_Body_Stub");
      Check_Context (The_Context);
      return Corresponding_Body_Stub (Subunit, The_Context.all);
   end Corresponding_Body_Stub;

   ----------------------------------------
   -- Corresponding_Constant_Declaration --
   ----------------------------------------

   function Corresponding_Constant_Declaration
     (Name : in Asis.Defining_Name)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Name, "Corresponding_Constant_Declaration");
      return Corresponding_Constant_Declaration (Name.all);
   end Corresponding_Constant_Declaration;

   -------------------------------
   -- Corresponding_Declaration --
   -------------------------------

   function Corresponding_Declaration
     (Declaration : in Asis.Declaration)
      return Asis.Declaration
   is
   begin
      case Declaration_Kind (Declaration.all) is
         when
           A_Function_Declaration
           | A_Generic_Function_Declaration
           | A_Generic_Package_Declaration
           | A_Generic_Procedure_Declaration
           --  | A_Package_Declaration  return Limited_View or its completion
           | A_Package_Renaming_Declaration
           | A_Procedure_Declaration
           | A_Single_Task_Declaration
           | A_Task_Type_Declaration
           | A_Protected_Type_Declaration
           | A_Single_Protected_Declaration
           | A_Generic_Package_Renaming_Declaration
           | A_Generic_Procedure_Renaming_Declaration
           | A_Generic_Function_Renaming_Declaration
           | An_Entry_Declaration =>
            return Declaration;
         when others =>
            null;
      end case;

      Check_Nil_Element (Declaration, "Corresponding_Declaration");
      return Corresponding_Declaration (Declaration.all);
   end Corresponding_Declaration;

   -------------------------------
   -- Corresponding_Declaration --
   -------------------------------

   function Corresponding_Declaration
     (Declaration : in Asis.Declaration;
      The_Context : in Asis.Context)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Declaration, "Corresponding_Declaration");
      Check_Context (The_Context);
      return Corresponding_Declaration (Declaration, The_Context.all);
   end Corresponding_Declaration;

   -------------------------------------
   -- Corresponding_Equality_Operator --
   -------------------------------------

   function Corresponding_Equality_Operator
     (Declaration : in Asis.Declaration)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Declaration, "Corresponding_Equality_Operator");
      return Corresponding_Equality_Operator (Declaration.all);
   end Corresponding_Equality_Operator;

   ---------------------------------
   -- Corresponding_First_Subtype --
   ---------------------------------

   function Corresponding_First_Subtype
     (Declaration : in Asis.Declaration)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Declaration, "Corresponding_First_Subtype");

      case Declaration_Kind (Declaration.all) is
         when An_Ordinary_Type_Declaration |
           A_Task_Type_Declaration |
           A_Protected_Type_Declaration |
           A_Private_Type_Declaration |
           A_Private_Extension_Declaration |
           A_Formal_Type_Declaration =>
            return Declaration;
         when others =>
            return Corresponding_First_Subtype (Declaration.all);
      end case;
   end Corresponding_First_Subtype;

   -----------------------------------
   -- Corresponding_Generic_Element --
   -----------------------------------

   function Corresponding_Generic_Element
     (Reference : in Asis.Element)
      return Asis.Defining_Name
   is
   begin
      Check_Nil_Element (Reference, "Corresponding_Generic_Element");
      return Corresponding_Generic_Element (Reference.all);
   end Corresponding_Generic_Element;

   -----------------------------------
   -- Corresponding_Last_Constraint --
   -----------------------------------

   function Corresponding_Last_Constraint
     (Declaration : in Asis.Declaration)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Declaration, "Corresponding_Last_Constraint");

      case Declaration_Kind (Declaration.all) is
         when An_Ordinary_Type_Declaration |
           A_Task_Type_Declaration |
           A_Protected_Type_Declaration |
           A_Private_Type_Declaration |
           A_Private_Extension_Declaration |
           A_Formal_Type_Declaration =>
            return Declaration;
         when others =>
            return Corresponding_Last_Constraint (Declaration.all);
      end case;
   end Corresponding_Last_Constraint;

   --------------------------------
   -- Corresponding_Last_Subtype --
   --------------------------------

   function Corresponding_Last_Subtype
     (Declaration : in Asis.Declaration)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Declaration, "Corresponding_Last_Subtype");

      case Declaration_Kind (Declaration.all) is
         when An_Ordinary_Type_Declaration |
           A_Task_Type_Declaration |
           A_Protected_Type_Declaration |
           A_Private_Type_Declaration |
           A_Private_Extension_Declaration |
           A_Formal_Type_Declaration =>
            return Declaration;
         when others =>
            return Corresponding_Last_Subtype (Declaration.all);
      end case;
   end Corresponding_Last_Subtype;

   ------------------------------------------
   -- Corresponding_Representation_Clauses --
   ------------------------------------------

   function Corresponding_Representation_Clauses
     (Declaration : in Asis.Declaration)
      return Asis.Representation_Clause_List
   is
   begin
      Check_Nil_Element (Declaration, "Corresponding_Representation_Clauses");
      return Corresponding_Representation_Clauses (Declaration.all);
   end Corresponding_Representation_Clauses;

   -----------------------------------------
   -- Corresponding_Subprogram_Derivation --
   -----------------------------------------

   function Corresponding_Subprogram_Derivation
     (Declaration : in Asis.Declaration)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Declaration, "Corresponding_Subprogram_Derivation");
      return Corresponding_Subprogram_Derivation (Declaration.all);
   end Corresponding_Subprogram_Derivation;

   ---------------------------
   -- Corresponding_Subunit --
   ---------------------------

   function Corresponding_Subunit
     (Body_Stub : in Asis.Declaration)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Body_Stub, "Corresponding_Subunit");
      return Corresponding_Subunit (Body_Stub.all);
   end Corresponding_Subunit;

   ---------------------------
   -- Corresponding_Subunit --
   ---------------------------

   function Corresponding_Subunit
     (Body_Stub   : in Asis.Declaration;
      The_Context : in Asis.Context)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Body_Stub, "Corresponding_Subunit");
      Check_Context (The_Context);
      return Corresponding_Subunit (Body_Stub, The_Context.all);
   end Corresponding_Subunit;

   ------------------------
   -- Corresponding_Type --
   ------------------------

   function Corresponding_Type
     (Declaration : in Asis.Declaration)
      return Asis.Type_Definition
   is
   begin
      Check_Nil_Element (Declaration, "Corresponding_Type");
      return Corresponding_Type (Declaration.all);
   end Corresponding_Type;

   ------------------------------------
   -- Corresponding_Type_Declaration --
   ------------------------------------

   function Corresponding_Type_Declaration
     (Declaration : in Asis.Declaration)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Declaration, "Corresponding_Type_Declaration");
      return Corresponding_Type_Declaration (Declaration.all);
   end Corresponding_Type_Declaration;

   ------------------------------------
   -- Corresponding_Type_Declaration --
   ------------------------------------

   function Corresponding_Type_Declaration
     (Declaration : in Asis.Declaration;
      The_Context : in Asis.Context)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Declaration, "Corresponding_Type_Declaration");
      Check_Context (The_Context);
      return Corresponding_Type_Declaration (Declaration, The_Context.all);
   end Corresponding_Type_Declaration;

   ------------------------------
   -- Declaration_Subtype_Mark --
   ------------------------------

   function Declaration_Subtype_Mark
     (Declaration : in Asis.Declaration)
      return Asis.Expression
   is
      Result : Asis.Definition;
   begin
      Check_Nil_Element (Declaration, "Declaration_Subtype_Mark");

      case Declaration_Kind (Declaration.all) is
         when A_Variable_Declaration |
           A_Constant_Declaration |
           A_Deferred_Constant_Declaration |
           A_Single_Protected_Declaration |
           A_Single_Task_Declaration |
           A_Component_Declaration
           =>
            Raise_Inappropriate_Element ("Declaration_Subtype_Mark");
         when others =>
            null;
      end case;

      Result := Object_Declaration_Subtype (Declaration.all);

      if Assigned (Result) then
         case Definition_Kind (Result.all) is
            when A_Subtype_Indication =>
               return Get_Subtype_Mark (Result.all);
            when An_Access_Definition =>
               case Access_Definition_Kind (Result.all) is
                  when An_Anonymous_Access_To_Object_Definition =>
                     return
                       Anonymous_Access_To_Object_Subtype_Mark (Result.all);
                  when others =>
                     raise Unimplemented;
               end case;
            when others =>
               raise Unimplemented;
         end case;
      end if;

      return Result;
   end Declaration_Subtype_Mark;

   -------------------------
   -- Defining_Name_Image --
   -------------------------

   function Defining_Name_Image
     (Defining_Name : in Asis.Defining_Name)
      return Program_Text
   is
   begin
      Check_Nil_Element (Defining_Name, "Defining_Name_Image");
      return Defining_Name_Image (Defining_Name.all);
   end Defining_Name_Image;

   ---------------------
   -- Defining_Prefix --
   ---------------------

   function Defining_Prefix
     (Defining_Name : in Asis.Defining_Name)
      return Asis.Name
   is
   begin
      Check_Nil_Element (Defining_Name, "Defining_Prefix");
      return Defining_Prefix (Defining_Name.all);
   end Defining_Prefix;

   -----------------------
   -- Defining_Selector --
   -----------------------

   function Defining_Selector
     (Defining_Name : in Asis.Defining_Name)
      return Asis.Defining_Name
   is
   begin
      Check_Nil_Element (Defining_Name, "Defining_Selector");
      return Defining_Selector (Defining_Name.all);
   end Defining_Selector;

   -----------------------
   -- Discriminant_Part --
   -----------------------

   function Discriminant_Part
     (Declaration : in Asis.Declaration)
      return Asis.Definition
   is
   begin
      Check_Nil_Element (Declaration, "Discriminant_Part");
      return Discriminant_Part (Declaration.all);
   end Discriminant_Part;

   -------------------
   -- Entry_Barrier --
   -------------------

   function Entry_Barrier
     (Declaration : in Asis.Declaration)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Declaration, "Entry_Barrier");
      return Entry_Barrier (Declaration.all);
   end Entry_Barrier;

   -----------------------------
   -- Entry_Family_Definition --
   -----------------------------

   function Entry_Family_Definition
     (Declaration : in Asis.Declaration)
      return Asis.Discrete_Subtype_Definition
   is
   begin
      Check_Nil_Element (Declaration, "Entry_Family_Definition");
      return Entry_Family_Definition (Declaration.all);
   end Entry_Family_Definition;

   -------------------------------
   -- Entry_Index_Specification --
   -------------------------------

   function Entry_Index_Specification
     (Declaration : in Asis.Declaration)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Declaration, "Entry_Index_Specification");
      return Entry_Index_Specification (Declaration.all);
   end Entry_Index_Specification;

   -------------------------------
   -- Formal_Subprogram_Default --
   -------------------------------

   function Formal_Subprogram_Default
     (Declaration : in Asis.Generic_Formal_Parameter)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Declaration, "Formal_Subprogram_Default");
      return Formal_Subprogram_Default (Declaration.all);
   end Formal_Subprogram_Default;

   -------------------------
   -- Generic_Actual_Part --
   -------------------------

   function Generic_Actual_Part
     (Declaration : in Asis.Declaration;
      Normalized  : in Boolean := False)
      return Asis.Association_List
   is
   begin
      Check_Nil_Element (Declaration, "Generic_Actual_Part");
      if Normalized then
         return Normalized_Generic_Actual_Part (Declaration.all);
      else
         return Generic_Actual_Part (Declaration.all);
      end if;
   end Generic_Actual_Part;

   -------------------------
   -- Generic_Formal_Part --
   -------------------------

   function Generic_Formal_Part
     (Declaration     : in Asis.Declaration;
      Include_Pragmas : in Boolean := False)
      return Asis.Element_List
   is
   begin
      Check_Nil_Element (Declaration, "Generic_Formal_Part");
      return Generic_Formal_Part (Declaration.all, Include_Pragmas);
   end Generic_Formal_Part;

   -----------------------
   -- Generic_Unit_Name --
   -----------------------

   function Generic_Unit_Name
     (Declaration : in Asis.Declaration)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Declaration, "Generic_Unit_Name");
      return Generic_Unit_Name (Declaration.all);
   end Generic_Unit_Name;

   -------------------------------
   -- Initialization_Expression --
   -------------------------------

   function Initialization_Expression
     (Declaration : in Asis.Declaration)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Declaration, "Initialization_Expression");
      return Initialization_Expression (Declaration.all);
   end Initialization_Expression;

   ------------------------------
   -- Is_Dispatching_Operation --
   ------------------------------

   function Is_Dispatching_Operation
     (Declaration : in Asis.Element)
      return Boolean
   is
   begin
      Check_Nil_Element (Declaration, "Is_Dispatching_Operation");
      return Is_Dispatching_Operation (Declaration.all);
   end Is_Dispatching_Operation;

   ----------------------
   -- Is_Name_Repeated --
   ----------------------

   function Is_Name_Repeated
     (Declaration : in Asis.Declaration)
      return Boolean
   is
   begin
      Check_Nil_Element (Declaration, "Is_Name_Repeated");
      return Is_Name_Repeated (Declaration.all);
   end Is_Name_Repeated;

   ------------------------
   -- Is_Private_Present --
   ------------------------

   function Is_Private_Present
     (Declaration : in Asis.Declaration)
      return Boolean
   is
   begin
      Check_Nil_Element (Declaration, "Is_Private_Present");
      return Is_Private_Present (Declaration.all);
   end Is_Private_Present;

   ----------------
   -- Is_Subunit --
   ----------------

   function Is_Subunit (Declaration : in Asis.Declaration) return Boolean is
      Enclosing_Unit : constant Compilation_Unit :=
         Enclosing_Compilation_Unit (Declaration.all);
   begin
      Check_Nil_Element (Declaration, "Is_Subunit");
      return Is_Equal (Declaration, Unit_Declaration (Enclosing_Unit.all))
        and Unit_Kind (Enclosing_Unit.all) in A_Subunit;
   end Is_Subunit;

   -----------
   -- Names --
   -----------

   function Names
     (Declaration : in Asis.Declaration)
      return Asis.Defining_Name_List
   is
   begin
      Check_Nil_Element (Declaration, "Names");
      return Names (Declaration.all);
   end Names;

   -----------------------------
   -- Object_Declaration_View --
   -----------------------------

   function Object_Declaration_View
     (Declaration : in Asis.Declaration)
      return Asis.Definition
   is
      Result : Asis.Definition;
   begin
      Check_Nil_Element (Declaration, "Object_Declaration_View");

      case Declaration_Kind (Declaration.all) is
         when A_Discriminant_Specification |
           A_Parameter_Specification |
           A_Formal_Object_Declaration |
           An_Object_Renaming_Declaration
           =>
            Raise_Inappropriate_Element ("Object_Declaration_View");
         when others =>
            null;
      end case;

      Result := Object_Declaration_Subtype (Declaration.all);

      if Assigned (Result) and then
        Definition_Kind (Result.all) = An_Access_Definition
      then
        raise Unimplemented;
      end if;

      return Result;
   end Object_Declaration_View;

   --------------------------------
   -- Object_Declaration_Subtype --
   --------------------------------

   function Object_Declaration_Subtype
     (Declaration : in Asis.Declaration)
      return Asis.Definition is
   begin
      Check_Nil_Element (Declaration, "Object_Declaration_Subtype");
      return Object_Declaration_Subtype (Declaration.all);
   end Object_Declaration_Subtype;

   -------------------------------
   -- Overriding_Indicator_Kind --
   -------------------------------

   function Overriding_Indicator_Kind
     (Declaration : Asis.Declaration)
     return Asis.Overriding_Indicator_Kinds
   is
   begin
      if Assigned (Declaration) then
         return Overriding_Indicator_Kind (Declaration.all);
      else
         return Not_An_Overriding_Indicator;
      end if;
   end Overriding_Indicator_Kind;

   -----------------------
   -- Parameter_Profile --
   -----------------------

   function Parameter_Profile
     (Declaration : in Asis.Declaration)
      return Asis.Parameter_Specification_List
   is
   begin
      Check_Nil_Element (Declaration, "Parameter_Profile");
      return Parameter_Profile (Declaration.all);
   end Parameter_Profile;

   ---------------------------
   -- Position_Number_Image --
   ---------------------------

   function Position_Number_Image
     (Defining_Name : in Asis.Defining_Name)
      return Wide_String
   is
   begin
      Check_Nil_Element (Defining_Name, "Position_Number_Image");
      return Position_Number_Image (Defining_Name.all);
   end Position_Number_Image;

   ------------------------------------
   -- Private_Part_Declarative_Items --
   ------------------------------------

   function Private_Part_Declarative_Items
     (Declaration     : in Asis.Declaration;
      Include_Pragmas : in Boolean := False)
      return Asis.Declarative_Item_List
   is
   begin
      Check_Nil_Element (Declaration, "Private_Part_Declarative_Items");
      return Private_Part_Declarative_Items (Declaration.all, Include_Pragmas);
   end Private_Part_Declarative_Items;

   ---------------------
   -- Progenitor_List --
   ---------------------

   function Progenitor_List
     (Declaration : Asis.Declaration)
     return Asis.Name_List is
   begin
      Check_Nil_Element (Declaration, "Progenitor_List");
      return Progenitor_List (Declaration.all);
   end Progenitor_List;

   -------------------------------
   -- Protected_Operation_Items --
   -------------------------------

   function Protected_Operation_Items
     (Declaration     : in Asis.Declaration;
      Include_Pragmas : in Boolean := False)
      return Asis.Declaration_List
   is
   begin
      Check_Nil_Element (Declaration, "Protected_Operation_Items");
      return Protected_Operation_Items (Declaration.all, Include_Pragmas);
   end Protected_Operation_Items;

   --------------------
   -- Renamed_Entity --
   --------------------

   function Renamed_Entity
     (Declaration : in Asis.Declaration)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Declaration, "Renamed_Entity");
      return Renamed_Entity (Declaration.all);
   end Renamed_Entity;

   --------------------------------
   -- Representation_Value_Image --
   --------------------------------

   function Representation_Value_Image
     (Defining_Name : in Asis.Defining_Name)
      return Wide_String
   is
   begin
      Check_Nil_Element (Defining_Name, "Representation_Value_Image");
      return Representation_Value_Image (Defining_Name.all);
   end Representation_Value_Image;

   --------------------
   -- Result_Profile --
   --------------------

   function Result_Profile
     (Declaration : in Asis.Declaration)
      return Asis.Expression
   is
      Result : Asis.Definition;
   begin
      Check_Nil_Element (Declaration, "Result_Profile");
      Result := Result_Subtype (Declaration.all);

      if Assigned (Result) then
         case Definition_Kind (Result.all) is
            when A_Subtype_Indication =>
               return Get_Subtype_Mark (Result.all);
            when others =>
               raise Unimplemented;
         end case;
      end if;

      return Result;
   end Result_Profile;

   --------------------
   -- Result_Subtype --
   --------------------

   function Result_Subtype
     (Declaration : in Asis.Declaration)
      return Asis.Definition is
   begin
      Check_Nil_Element (Declaration, "Result_Subtype");
      return Result_Subtype (Declaration.all);
   end Result_Subtype;

   --------------------------------------
   -- Specification_Subtype_Definition --
   --------------------------------------

   function Specification_Subtype_Definition
     (Specification : in Asis.Declaration)
      return Asis.Discrete_Subtype_Definition
   is
   begin
      Check_Nil_Element (Specification, "Specification_Subtype_Definition");
      return Specification_Subtype_Definition (Specification.all);
   end Specification_Subtype_Definition;

   ---------------------------
   -- Type_Declaration_View --
   ---------------------------

   function Type_Declaration_View
     (Declaration : in Asis.Declaration)
      return Asis.Definition
   is
   begin
      Check_Nil_Element (Declaration, "Type_Declaration_View");
      return Type_Declaration_View (Declaration.all);
   end Type_Declaration_View;

   ------------------------------------
   -- Visible_Part_Declarative_Items --
   ------------------------------------

   function Visible_Part_Declarative_Items
     (Declaration     : in Asis.Declaration;
      Include_Pragmas : in Boolean := False)
      return Asis.Declarative_Item_List
   is
   begin
      Check_Nil_Element (Declaration, "Visible_Part_Declarative_Items");
      return Visible_Part_Declarative_Items (Declaration.all, Include_Pragmas);
   end Visible_Part_Declarative_Items;

end Asis.Declarations;


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
