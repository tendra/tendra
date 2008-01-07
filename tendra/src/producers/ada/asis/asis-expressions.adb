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

with XASIS.Utils;

package body Asis.Expressions is

   ----------------------
   -- Actual_Parameter --
   ----------------------

   function Actual_Parameter
     (Association : in Asis.Association)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Association, "Actual_Parameter");
      return Actual_Parameter (Association.all);
   end Actual_Parameter;

   ------------------------------------
   -- Allocator_Qualified_Expression --
   ------------------------------------

   function Allocator_Qualified_Expression
     (Expression : in Asis.Expression)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Expression, "Allocator_Qualified_Expression");
      return Allocator_Qualified_Expression (Expression.all);
   end Allocator_Qualified_Expression;

   ----------------------------------
   -- Allocator_Subtype_Indication --
   ----------------------------------

   function Allocator_Subtype_Indication
     (Expression : in Asis.Expression)
      return Asis.Subtype_Indication
   is
   begin
      Check_Nil_Element (Expression, "Allocator_Subtype_Indication");
      return Allocator_Subtype_Indication (Expression.all);
   end Allocator_Subtype_Indication;

   ----------------------------------
   -- Array_Component_Associations --
   ----------------------------------

   function Array_Component_Associations
     (Expression : in Asis.Expression)
      return Asis.Association_List
   is
   begin
      Check_Nil_Element (Expression, "Array_Component_Associations");
      return Array_Component_Associations (Expression.all);
   end Array_Component_Associations;

   -----------------------------
   -- Array_Component_Choices --
   -----------------------------

   function Array_Component_Choices
     (Association : in Asis.Association)
      return Asis.Expression_List
   is
   begin
      Check_Nil_Element (Association, "Array_Component_Choices");
      return Array_Component_Choices (Association.all);
   end Array_Component_Choices;

   --------------------------------------
   -- Attribute_Designator_Expressions --
   --------------------------------------

   function Attribute_Designator_Expressions
     (Expression : in Asis.Expression)
      return Asis.Expression_List
   is
   begin
      Check_Nil_Element (Expression, "Attribute_Designator_Expressions");
      return Attribute_Designator_Expressions (Expression.all);
   end Attribute_Designator_Expressions;

   -------------------------------------
   -- Attribute_Designator_Identifier --
   -------------------------------------

   function Attribute_Designator_Identifier
     (Expression : in Asis.Expression)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Expression, "Attribute_Designator_Identifier");
      return Attribute_Designator_Identifier (Expression.all);
   end Attribute_Designator_Identifier;

   --------------------------
   -- Component_Expression --
   --------------------------

   function Component_Expression
     (Association : in Asis.Association)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Association, "Component_Expression");
      return Component_Expression (Association.all);
   end Component_Expression;

   ---------------------------------------
   -- Converted_Or_Qualified_Expression --
   ---------------------------------------

   function Converted_Or_Qualified_Expression
     (Expression : in Asis.Expression)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Expression, "Converted_Or_Qualified_Expression");
      return Converted_Or_Qualified_Expression (Expression.all);
   end Converted_Or_Qualified_Expression;

   -----------------------------------------
   -- Converted_Or_Qualified_Subtype_Mark --
   -----------------------------------------

   function Converted_Or_Qualified_Subtype_Mark
     (Expression : in Asis.Expression)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Expression, "Converted_Or_Qualified_Subtype_Mark");
      return Converted_Or_Qualified_Subtype_Mark (Expression.all);
   end Converted_Or_Qualified_Subtype_Mark;

   -----------------------------------
   -- Corresponding_Called_Function --
   -----------------------------------

   function Corresponding_Called_Function
     (Expression : in Asis.Expression)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Expression, "Corresponding_Called_Function");
      return Corresponding_Called_Function (Expression.all);
   end Corresponding_Called_Function;

   -----------------------------------
   -- Corresponding_Expression_Type --
   -----------------------------------

   function Corresponding_Expression_Type
     (Expression : in Asis.Expression)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Expression, "Corresponding_Expression_Type");
      return Corresponding_Expression_Type (Expression.all);
   end Corresponding_Expression_Type;

   ------------------------------------
   -- Corresponding_Name_Declaration --
   ------------------------------------

   function Corresponding_Name_Declaration
     (Reference : in Asis.Expression)
      return Asis.Element
   is
   begin
      Check_Nil_Element (Reference, "Corresponding_Name_Declaration");
      return Corresponding_Name_Declaration (Reference.all);
   end Corresponding_Name_Declaration;

   -----------------------------------
   -- Corresponding_Name_Definition --
   -----------------------------------

   function Corresponding_Name_Definition
     (Reference : in Asis.Expression)
      return Asis.Defining_Name
   is
      List : constant Asis.Defining_Name_List :=
        Corresponding_Name_Definition_List (Reference.all);
   begin
      if List'Length = 0 then
         return Nil_Element;
      else
         return List (List'First);
      end if;
   end Corresponding_Name_Definition;

   ----------------------------------------
   -- Corresponding_Name_Definition_List --
   ----------------------------------------

   function Corresponding_Name_Definition_List
     (Reference : in Asis.Element)
      return Asis.Defining_Name_List
   is
   begin
      Check_Nil_Element (Reference, "Corresponding_Name_Definition_List");
      return Corresponding_Name_Definition_List (Reference.all);
   end Corresponding_Name_Definition_List;

   -----------------------------
   -- Discriminant_Expression --
   -----------------------------

   function Discriminant_Expression
     (Association : in Asis.Discriminant_Association)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Association, "Discriminant_Expression");
      return Discriminant_Expression (Association.all);
   end Discriminant_Expression;

   ---------------------------------
   -- Discriminant_Selector_Names --
   ---------------------------------

   function Discriminant_Selector_Names
     (Association : in Asis.Discriminant_Association)
      return Asis.Expression_List
   is
   begin
      Check_Nil_Element (Association, "Discriminant_Selector_Names");
      if Is_Normalized (Association) then
         return (1 => Discriminant_Selector_Name (Association.all));
      else
         return Discriminant_Selector_Names (Association.all);
      end if;
   end Discriminant_Selector_Names;

   ------------------------------
   -- Expression_Parenthesized --
   ------------------------------

   function Expression_Parenthesized
     (Expression : in Asis.Expression)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Expression, "Expression_Parenthesized");
      return Expression_Parenthesized (Expression.all);
   end Expression_Parenthesized;

   ------------------------------------
   -- Extension_Aggregate_Expression --
   ------------------------------------

   function Extension_Aggregate_Expression
     (Expression : in Asis.Expression)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Expression, "Extension_Aggregate_Expression");
      return Extension_Aggregate_Expression (Expression.all);
   end Extension_Aggregate_Expression;

   ----------------------
   -- Formal_Parameter --
   ----------------------

   function Formal_Parameter
     (Association : in Asis.Association)
      return Asis.Element
   is
   begin
      Check_Nil_Element (Association, "Formal_Parameter");
      return Formal_Parameter (Association.all);
   end Formal_Parameter;

   ------------------------------
   -- Function_Call_Parameters --
   ------------------------------

   function Function_Call_Parameters
     (Expression : in Asis.Expression;
      Normalized : in Boolean := False)
      return Asis.Association_List
   is
   begin
      Check_Nil_Element (Expression, "Function_Call_Parameters");
      if Normalized then
         return Normalized_Function_Call_Parameters (Expression.all);
      else
         return Function_Call_Parameters (Expression.all);
      end if;
   end Function_Call_Parameters;

   -----------------------
   -- Index_Expressions --
   -----------------------

   function Index_Expressions
     (Expression : in Asis.Expression)
      return Asis.Expression_List
   is
   begin
      Check_Nil_Element (Expression, "Index_Expressions");
      return Index_Expressions (Expression.all);
   end Index_Expressions;

   ------------------------------
   -- Is_Defaulted_Association --
   ------------------------------

   function Is_Defaulted_Association
     (Association : in Asis.Association)
      return Boolean
   is
   begin
      Check_Nil_Element (Association, "Is_Defaulted_Association");
      return Is_Defaulted_Association (Association.all);
   end Is_Defaulted_Association;

   -------------------
   -- Is_Normalized --
   -------------------

   function Is_Normalized
     (Association : in Asis.Association)
      return Boolean
   is
   begin
      Check_Nil_Element (Association, "Is_Normalized");
      return Is_Normalized (Association.all);
   end Is_Normalized;

   --------------------
   -- Is_Prefix_Call --
   --------------------

   function Is_Prefix_Call
     (Expression : in Asis.Expression)
      return Boolean
   is
   begin
      Check_Nil_Element (Expression, "Is_Prefix_Call");
      return Is_Prefix_Call (Expression.all);
   end Is_Prefix_Call;

   -------------------
   -- Is_Referenced --
   -------------------

   function Is_Referenced
     (Name           : in Asis.Element;
      Within_Element : in Asis.Element;
      Implicitly     : in Boolean := False)
      return Boolean
   is
   begin
      return References (Name, Within_Element, Implicitly)'Length > 0;
   end Is_Referenced;

   --------------------------------
   -- Membership_Test_Expression --
   --------------------------------

   function Membership_Test_Expression
     (Expression : in Asis.Expression)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Expression, "Membership_Test_Expression");
      return Membership_Test_Expression (Expression.all);
   end Membership_Test_Expression;

   ---------------------------
   -- Membership_Test_Range --
   ---------------------------

   function Membership_Test_Range
     (Expression : in Asis.Expression)
      return Asis.Range_Constraint
   is
   begin
      Check_Nil_Element (Expression, "Membership_Test_Range");
      return Membership_Test_Range (Expression.all);
   end Membership_Test_Range;

   ----------------------------------
   -- Membership_Test_Subtype_Mark --
   ----------------------------------

   function Membership_Test_Subtype_Mark
     (Expression : in Asis.Expression)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Expression, "Membership_Test_Subtype_Mark");
      return Membership_Test_Subtype_Mark (Expression.all);
   end Membership_Test_Subtype_Mark;

   ----------------
   -- Name_Image --
   ----------------

   function Name_Image
     (Expression : in Asis.Expression)
      return Program_Text
   is
   begin
      Check_Nil_Element (Expression, "Name_Image");
      return Name_Image (Expression.all);
   end Name_Image;

   ------------
   -- Prefix --
   ------------

   function Prefix
     (Expression : in Asis.Expression)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Expression, "Prefix");
      return Prefix (Expression.all);
   end Prefix;

   -----------------------------------
   -- Record_Component_Associations --
   -----------------------------------

   function Record_Component_Associations
     (Expression : in Asis.Expression;
      Normalized : in Boolean := False)
      return Asis.Association_List
   is
   begin
      Check_Nil_Element (Expression, "Record_Component_Associations");
      if Normalized then
         return Normalized_Record_Component_Associations (Expression.all);
      else
         return Record_Component_Associations (Expression.all);
      end if;
   end Record_Component_Associations;

   ------------------------------
   -- Record_Component_Choices --
   ------------------------------

   function Record_Component_Choices
     (Association : in Asis.Association)
      return Asis.Expression_List
   is
   begin
      Check_Nil_Element (Association, "Record_Component_Choices");
      if Is_Normalized (Association) then
         return (1 => Record_Component_Choice (Association.all));
      else
         return Record_Component_Choices (Association.all);
      end if;
   end Record_Component_Choices;

   ----------------
   -- References --
   ----------------

   function References
     (Name           : in Asis.Element;
      Within_Element : in Asis.Element;
      Implicitly     : in Boolean := False)
      return Asis.Name_List
   is
      Result : Asis.Name_List := References (Name.all, True);
      Last   : Asis.List_Index := 1;
   begin
      for I in Result'Range loop
         if (Implicitly or else not Is_Part_Of_Implicit (Result (I).all))
           and then XASIS.Utils.Is_Child_Of (Result (I), Within_Element)
         then
           Result (Last) := Result (I);
           Last := Last + 1;
         end if;
      end loop;

      return Result (1 .. Last - 1);
   end References;

   --------------
   -- Selector --
   --------------

   function Selector
     (Expression : in Asis.Expression)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Expression, "Selector");
      return Selector (Expression.all);
   end Selector;

   ---------------------------------------------
   -- Short_Circuit_Operation_Left_Expression --
   ---------------------------------------------

   function Short_Circuit_Operation_Left_Expression
     (Expression : in Asis.Expression)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Expression, "Short_Circuit_Operation_Left_Expression");
      return Short_Circuit_Operation_Left_Expression (Expression.all);
   end Short_Circuit_Operation_Left_Expression;

   ----------------------------------------------
   -- Short_Circuit_Operation_Right_Expression --
   ----------------------------------------------

   function Short_Circuit_Operation_Right_Expression
     (Expression : in Asis.Expression)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Expression, "Short_Circuit_Operation_Right_Expression");
      return Short_Circuit_Operation_Right_Expression (Expression.all);
   end Short_Circuit_Operation_Right_Expression;

   -----------------
   -- Slice_Range --
   -----------------

   function Slice_Range
     (Expression : in Asis.Expression)
      return Asis.Discrete_Range
   is
   begin
      Check_Nil_Element (Expression, "Slice_Range");
      return Slice_Range (Expression.all);
   end Slice_Range;

   -----------------
   -- Value_Image --
   -----------------

   function Value_Image
     (Expression : in Asis.Expression)
      return Wide_String
   is
   begin
      Check_Nil_Element (Expression, "Value_Image");
      return Value_Image (Expression.all);
   end Value_Image;

end Asis.Expressions;


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
