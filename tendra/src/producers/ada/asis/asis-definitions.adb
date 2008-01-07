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

package body Asis.Definitions is

   ---------------------------------------
   -- Access_To_Function_Result_Profile --
   ---------------------------------------

   function Access_To_Function_Result_Profile
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Expression
   is
      Result : Asis.Definition;
   begin
      Check_Nil_Element (Type_Definition, "Access_To_Function_Result_Profile");

      if Definition_Kind (Type_Definition.all) = An_Access_Definition then
         Raise_Inappropriate_Element ("Access_To_Function_Result_Profile");
      end if;

      Result := Access_To_Function_Result_Subtype (Type_Definition.all);

      if Assigned (Result) then
         case Definition_Kind (Result.all) is
            when A_Subtype_Indication =>
               return Get_Subtype_Mark (Result.all);
            when others =>
               raise Unimplemented;
         end case;
      end if;

      return Result;
   end Access_To_Function_Result_Profile;

   ---------------------------------------
   -- Access_To_Function_Result_Subtype --
   ---------------------------------------

   function Access_To_Function_Result_Subtype
     (Definition : in Asis.Definition)
      return Asis.Definition
   is
   begin
      Check_Nil_Element (Definition, "Access_To_Function_Result_Subtype");
      return Access_To_Function_Result_Subtype (Definition.all);
   end Access_To_Function_Result_Subtype;

   ---------------------------------
   -- Access_To_Object_Definition --
   ---------------------------------

   function Access_To_Object_Definition
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Subtype_Indication
   is
   begin
      Check_Nil_Element (Type_Definition, "Access_To_Object_Definition");
      return Get_Access_To_Object_Definition (Type_Definition.all);
   end Access_To_Object_Definition;

   --------------------------------------------
   -- Access_To_Subprogram_Parameter_Profile --
   --------------------------------------------

   function Access_To_Subprogram_Parameter_Profile
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Parameter_Specification_List
   is
   begin
      Check_Nil_Element (Type_Definition, "Access_To_Subprogram_Parameter_Profile");
      return Access_To_Subprogram_Parameter_Profile (Type_Definition.all);
   end Access_To_Subprogram_Parameter_Profile;

   ---------------------------------
   -- Ancestor_Subtype_Indication --
   ---------------------------------

   function Ancestor_Subtype_Indication
     (Definition : in Asis.Definition)
      return Asis.Subtype_Indication
   is
   begin
      Check_Nil_Element (Definition, "Ancestor_Subtype_Indication");
      return Ancestor_Subtype_Indication (Definition.all);
   end Ancestor_Subtype_Indication;

   ---------------------------------------------
   -- Anonymous_Access_To_Object_Subtype_Mark --
   ---------------------------------------------

   function Anonymous_Access_To_Object_Subtype_Mark
     (Definition : Asis.Definition)
      return Asis.Name
   is
   begin
      Check_Nil_Element
        (Definition, "Anonymous_Access_To_Object_Subtype_Mark");
      return Anonymous_Access_To_Object_Subtype_Mark (Definition.all);
   end Anonymous_Access_To_Object_Subtype_Mark;

   --------------------------------
   -- Array_Component_Definition --
   --------------------------------

   function Array_Component_Definition
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Component_Definition
   is
   begin
      Check_Nil_Element (Type_Definition, "Array_Component_Definition");
      return Array_Component_Definition (Type_Definition.all);
   end Array_Component_Definition;

   ----------------------------------
   -- Component_Subtype_Indication --
   ----------------------------------

   function Component_Subtype_Indication
     (Component_Definition : in Asis.Component_Definition)
      return Asis.Subtype_Indication
   is
   begin
      Check_Nil_Element (Component_Definition, "Component_Subtype_Indication");
      return Component_Subtype_Indication (Component_Definition.all);
   end Component_Subtype_Indication;

   ----------------------------------
   -- Corresponding_Parent_Subtype --
   ----------------------------------

   function Corresponding_Parent_Subtype
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Type_Definition, "Corresponding_Parent_Subtype");
      return Corresponding_Parent_Subtype (Type_Definition.all);
   end Corresponding_Parent_Subtype;

   -----------------------------
   -- Corresponding_Root_Type --
   -----------------------------

   function Corresponding_Root_Type
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Type_Definition, "Corresponding_Root_Type");
      return Corresponding_Root_Type (Type_Definition.all);
   end Corresponding_Root_Type;

   ----------------------------------
   -- Corresponding_Type_Operators --
   ----------------------------------

   function Corresponding_Type_Operators
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Declaration_List
   is
      Kind : constant Asis.Definition_Kinds :=
        Definition_Kind (Type_Definition.all);
   begin
      Check_Nil_Element (Type_Definition, "Corresponding_Type_Operators");

      if Kind /= A_Type_Definition and Kind /= A_Formal_Type_Definition then
         Raise_Inappropriate_Element ("Corresponding_Type_Operators");
      end if;

      return Corresponding_Type_Operators (Type_Definition.all);
   end Corresponding_Type_Operators;

   ----------------------------------
   -- Corresponding_Type_Structure --
   ----------------------------------

   function Corresponding_Type_Structure
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Type_Definition, "Corresponding_Type_Structure");
      return Corresponding_Type_Structure (Type_Definition.all);
   end Corresponding_Type_Structure;

   ----------------------
   -- Delta_Expression --
   ----------------------

   function Delta_Expression
     (Definition : in Asis.Definition)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Definition, "Delta_Expression");
      return Delta_Expression (Definition.all);
   end Delta_Expression;

   -----------------------
   -- Digits_Expression --
   -----------------------

   function Digits_Expression
     (Definition : in Asis.Definition)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Definition, "Digits_Expression");
      return Digits_Expression (Definition.all);
   end Digits_Expression;

   ---------------------
   -- Discrete_Ranges --
   ---------------------

   function Discrete_Ranges
     (Constraint : in Asis.Constraint)
      return Asis.Discrete_Range_List
   is
   begin
      Check_Nil_Element (Constraint, "Discrete_Ranges");
      return Discrete_Ranges (Constraint.all);
   end Discrete_Ranges;

   ----------------------------------
   -- Discrete_Subtype_Definitions --
   ----------------------------------

   function Discrete_Subtype_Definitions
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Definition_List
   is
   begin
      Check_Nil_Element (Type_Definition, "Discrete_Subtype_Definitions");
      return Discrete_Subtype_Definitions (Type_Definition.all);
   end Discrete_Subtype_Definitions;

   -------------------------------
   -- Discriminant_Associations --
   -------------------------------

   function Discriminant_Associations
     (Constraint : in Asis.Constraint;
      Normalized : in Boolean := False)
      return Asis.Discriminant_Association_List
   is
   begin
      Check_Nil_Element (Constraint, "Discriminant_Associations");
      if Normalized then
         return Normalized_Discriminant_Associations (Constraint.all);
      else
         return Discriminant_Associations (Constraint.all);
      end if;
   end Discriminant_Associations;

   ------------------------------
   -- Discriminant_Direct_Name --
   ------------------------------

   function Discriminant_Direct_Name
     (Variant_Part : in Asis.Record_Component)
      return Asis.Name
   is
   begin
      Check_Nil_Element (Variant_Part, "Discriminant_Direct_Name");
      return Discriminant_Direct_Name (Variant_Part.all);
   end Discriminant_Direct_Name;

   -------------------
   -- Discriminants --
   -------------------

   function Discriminants
     (Definition : in Asis.Definition)
      return Asis.Discriminant_Specification_List
   is
   begin
      Check_Nil_Element (Definition, "Discriminants");
      return Discriminants (Definition.all);
   end Discriminants;

   --------------------------------------
   -- Enumeration_Literal_Declarations --
   --------------------------------------

   function Enumeration_Literal_Declarations
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Declaration_List
   is
   begin
      Check_Nil_Element (Type_Definition, "Enumeration_Literal_Declarations");
      return Enumeration_Literal_Declarations (Type_Definition.all);
   end Enumeration_Literal_Declarations;

   -------------------------
   -- Implicit_Components --
   -------------------------

   function Implicit_Components
     (Definition : in Asis.Definition)
      return Asis.Record_Component_List
   is
   begin
      Check_Nil_Element (Definition, "Implicit_Components");
      return Implicit_Components (Definition.all);
   end Implicit_Components;

   -------------------------------------
   -- Implicit_Inherited_Declarations --
   -------------------------------------

   function Implicit_Inherited_Declarations
     (Definition : in Asis.Definition)
      return Asis.Declaration_List
   is
   begin
      Check_Nil_Element (Definition, "Implicit_Inherited_Declarations");
      return Implicit_Inherited_Declarations (Definition.all);
   end Implicit_Inherited_Declarations;

   ------------------------------------
   -- Implicit_Inherited_Subprograms --
   ------------------------------------

   function Implicit_Inherited_Subprograms
     (Definition : in Asis.Definition)
      return Asis.Declaration_List
   is
   begin
      Check_Nil_Element (Definition, "Implicit_Inherited_Subprograms");
      return Implicit_Inherited_Subprograms (Definition.all);
   end Implicit_Inherited_Subprograms;

   -------------------------------
   -- Index_Subtype_Definitions --
   -------------------------------

   function Index_Subtype_Definitions
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Expression_List
   is
   begin
      Check_Nil_Element (Type_Definition, "Index_Subtype_Definitions");
      return Index_Subtype_Definitions (Type_Definition.all);
   end Index_Subtype_Definitions;

   ------------------------
   -- Integer_Constraint --
   ------------------------

   function Integer_Constraint
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Range_Constraint
   is
   begin
      Check_Nil_Element (Type_Definition, "Integer_Constraint");
      return Integer_Constraint (Type_Definition.all);
   end Integer_Constraint;

   ------------------------
   -- Is_Private_Present --
   ------------------------

   function Is_Private_Present
     (Definition : in Asis.Definition)
      return Boolean
   is
   begin
      return Assigned (Definition) and then
        Is_Private_Present (Definition.all);
   end Is_Private_Present;

   --------------------------------
   -- Is_Task_Definition_Present --
   --------------------------------

   function Is_Task_Definition_Present
     (Definition : in Asis.Definition)
      return Boolean
   is
   begin
      return Assigned (Definition) and then
         Is_Task_Definition_Present (Definition);
   end Is_Task_Definition_Present;

   -----------------
   -- Lower_Bound --
   -----------------

   function Lower_Bound
     (Constraint : in Asis.Range_Constraint)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Constraint, "Lower_Bound");
      return Lower_Bound (Constraint.all);
   end Lower_Bound;

   ---------------------------
   -- Mod_Static_Expression --
   ---------------------------

   function Mod_Static_Expression
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Type_Definition, "Mod_Static_Expression");
      return Mod_Static_Expression (Type_Definition.all);
   end Mod_Static_Expression;

   -------------------------------
   -- Parent_Subtype_Indication --
   -------------------------------

   function Parent_Subtype_Indication
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Subtype_Indication
   is
   begin
      Check_Nil_Element (Type_Definition, "Parent_Subtype_Indication");
      return Parent_Subtype_Indication (Type_Definition.all);
   end Parent_Subtype_Indication;

   ------------------------
   -- Private_Part_Items --
   ------------------------

   function Private_Part_Items
     (Definition : in Asis.Definition;
      Include_Pragmas : in Boolean := False)
      return Asis.Declarative_Item_List
   is
   begin
      Check_Nil_Element (Definition, "Private_Part_Items");
      return Private_Part_Items (Definition.all, Include_Pragmas);
   end Private_Part_Items;

   ---------------------
   -- Progenitor_List --
   ---------------------

   function Progenitor_List
     (Type_Definition : Asis.Definition)
     return Asis.Name_List is
   begin
      Check_Nil_Element (Type_Definition, "Progenitor_List");
      return Progenitor_List (Type_Definition.all);
   end Progenitor_List;

   ---------------------
   -- Range_Attribute --
   ---------------------

   function Range_Attribute
     (Constraint : in Asis.Range_Constraint)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Constraint, "Range_Attribute");
      return Range_Attribute (Constraint.all);
   end Range_Attribute;

   ---------------------------
   -- Real_Range_Constraint --
   ---------------------------

   function Real_Range_Constraint
     (Definition : in Asis.Definition)
      return Asis.Range_Constraint
   is
   begin
      Check_Nil_Element (Definition, "Real_Range_Constraint");
      return Real_Range_Constraint (Definition.all);
   end Real_Range_Constraint;

   -----------------------
   -- Record_Components --
   -----------------------

   function Record_Components
     (Definition : in Asis.Definition;
      Include_Pragmas : in Boolean := False)
      return Asis.Record_Component_List
   is
   begin
      Check_Nil_Element (Definition, "Record_Components");
      return Record_Components (Definition.all, Include_Pragmas);
   end Record_Components;

   -----------------------
   -- Record_Definition --
   -----------------------

   function Record_Definition
     (Type_Definition : in Asis.Type_Definition)
      return Asis.Definition
   is
   begin
      Check_Nil_Element (Type_Definition, "Record_Definition");
      return Get_Record_Definition (Type_Definition.all);
   end Record_Definition;

   ------------------------
   -- Subtype_Constraint --
   ------------------------

   function Subtype_Constraint
     (Definition : in Asis.Definition)
      return Asis.Constraint
   is
   begin
      Check_Nil_Element (Definition, "Subtype_Constraint");
      return Subtype_Constraint (Definition.all);
   end Subtype_Constraint;

   ------------------
   -- Subtype_Mark --
   ------------------

   function Subtype_Mark
     (Definition : in Asis.Definition)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Definition, "Subtype_Mark");
      return Get_Subtype_Mark (Definition.all);
   end Subtype_Mark;

   -----------------
   -- Upper_Bound --
   -----------------

   function Upper_Bound
     (Constraint : in Asis.Range_Constraint)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Constraint, "Upper_Bound");
      return Upper_Bound (Constraint.all);
   end Upper_Bound;

   ---------------------
   -- Variant_Choices --
   ---------------------

   function Variant_Choices
     (Variant : in Asis.Variant)
      return Asis.Element_List
   is
   begin
      Check_Nil_Element (Variant, "Variant_Choices");
      return Variant_Choices (Variant.all);
   end Variant_Choices;

   --------------
   -- Variants --
   --------------

   function Variants
     (Variant_Part    : in Asis.Record_Component;
      Include_Pragmas : in Boolean := False)
      return Asis.Variant_List
   is
   begin
      Check_Nil_Element (Variant_Part, "Variants");
      return Variants (Variant_Part.all, Include_Pragmas);
   end Variants;

   ------------------------
   -- Visible_Part_Items --
   ------------------------

   function Visible_Part_Items
     (Definition : in Asis.Definition;
      Include_Pragmas : in Boolean := False)
      return Asis.Declarative_Item_List
   is
   begin
      Check_Nil_Element (Definition, "Visible_Part_Items");
      return Visible_Part_Items (Definition.all, Include_Pragmas);
   end Visible_Part_Items;

end Asis.Definitions;


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
