------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$:

with Asis.Elements;
with Asis.Expressions;
with Asis.Gela.Lists;
with Asis.Gela.Errors;
with Asis.Gela.Classes;
with Asis.Gela.Base_Lists;
with Asis.Gela.Element_Utils;
with Asis.Gela.Elements.Expr;
with Asis.Gela.Elements.Assoc;
with Asis.Gela.Elements.Decl;
with Asis.Gela.Elements.Stmt;
with Asis.Gela.Elements.Defs.Rng;
with Asis.Gela.Elements.Defs.Const;
with Asis.Gela.Elements.Clause.Rep;
with Asis.Gela.Elements.Defs.Types;
with Asis.Gela.Elements.Defs.Formal;

package body Asis.Gela.Replace is

   procedure Function_To_Index_Constraint (Item : in out Asis.Element);
   procedure Function_To_Discriminant_Constraint (Item : in out Asis.Element);

   procedure Set_Enclosing_Element_In_List
     (List   : access Asis.Gela.Base_Lists.Primary_Base_List_Node'Class;
      Parent : Asis.Element);

   procedure Set_Enclosing_Element_In_List
     (List   : Asis.Element;
      Parent : Asis.Element);

   -----------------------------------------
   -- Could_Be_Positional_Array_Aggregate --
   -----------------------------------------

   function Could_Be_Positional_Array_Aggregate
     (Item : Asis.Element) return Boolean
   is
      use Asis.Elements;
      use Asis.Expressions;
      List : Asis.Association_List := Record_Component_Associations (Item);
   begin
      if List'Length = 0 then  --  null record
         return False;
      end if;
      for I in List'Range loop
         declare
            Choises : Asis.Expression_List :=
              Record_Component_Choices (List (I));
         begin
            if List'Length = 1 and then Choises'Length = 0 then
               return False;
            end if;
            if Choises'Length /= 0 then
               return False;
            end if;
            if Element_Kind (Component_Expression (List (I))) /= An_Expression
            then
               return False;
            end if;
         end;
      end loop;
      return True;
   end Could_Be_Positional_Array_Aggregate;

   ---------------------------------
   -- Expression_To_Function_Call --
   ---------------------------------

   procedure Expression_To_Function_Call (Item : in out Asis.Element) is
      use Asis.Gela.Elements.Expr;

      Result : Function_Call_Ptr := new Function_Call_Node;
   begin
      Element_Utils.Copy_Element
        (Source => Item,
         Target => Asis.Element (Result));

      Set_Prefix (Result.all, Item);
      Element_Utils.Set_Enclosing_Element (Item, Asis.Element (Result));
      Set_Is_Prefix_Call (Result.all, True);

      Item := Asis.Element (Result);
   end Expression_To_Function_Call;

   ----------------------------
   -- Function_To_Constraint --
   ----------------------------

   procedure Function_To_Constraint (Item : in out Asis.Element) is
      use Asis.Expressions;
      use Asis.Gela.Errors;
      use Asis.Gela.Classes;

      Subtipe : Asis.Subtype_Mark := Prefix (Item);
      Info    : Type_Info := Type_From_Subtype_Mark (Subtipe, Item);
   begin
      if Is_Not_Type (Info) or else Is_Definition (Info) then
         return;
      end if;

      if Is_Array (Info) then
         Function_To_Index_Constraint (Item);
      elsif Is_Composite (Info) then
         Function_To_Discriminant_Constraint (Item);
      else
         Report (Item, Error_Syntax_Bad_Constraints);
      end if;
   end Function_To_Constraint;

   -----------------------------------------
   -- Function_To_Discriminant_Constraint --
   -----------------------------------------

   procedure Function_To_Discriminant_Constraint (Item : in out Asis.Element)
   is
      use Asis.Elements;
      use Asis.Gela.Lists;
      use Asis.Gela.Errors;
      use Asis.Expressions;
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Elements.Assoc;
      use Asis.Gela.Element_Utils;
      use Primary_Association_Lists;
      use Asis.Gela.Elements.Defs.Const;

      List    : Asis.Association_List :=
        Function_Call_Parameters (Item);
      List_I : Asis.Element;
      Result : Discriminant_Constraint_Ptr :=
        new Discriminant_Constraint_Node;
      Assoc  : Discriminant_Association_Ptr;
      Node   : Record_Component_Association_Ptr;
      Child  : Asis.Element;
      Funct  : Function_Call_Node renames Function_Call_Node (Item.all);
      Aggr   : constant Asis.Element := Record_Aggregate (Funct);
      Assoc_List : Primary_Association_Lists.List := new List_Node;
      Old_List   : Primary_Choise_Lists.List;
   begin
      for I in List'Range loop
         List_I := List (I);
         Node := Record_Component_Association_Ptr (List_I);
         Child := Component_Expression (List_I);

         if Element_Kind (Child) = An_Expression then
            Assoc := new Discriminant_Association_Node;
            Copy_Element (List_I, Asis.Element (Assoc));
            Set_Discriminant_Expression (Assoc.all, Child);
            Set_Enclosing_Element (Child, Asis.Element (Assoc));
            Child := Record_Component_Choices_List (Node.all);
            Set_Discriminant_Selector_Names (Assoc.all, Child);
            Old_List := Primary_Choise_Lists.List (Child);

            if Assigned (Child) then
               Set_Enclosing_Element_In_List (Old_List, Asis.Element (Assoc));
            end if;

            Add (Assoc_List.all, Asis.Element (Assoc));
            Set_Enclosing_Element (Assoc.all, Asis.Element (Result));
         else
            Report (Child, Error_Syntax_Bad_Constraints);
         end if;

      end loop;

      Copy_Element (Item, Asis.Element (Result));
      Set_Discriminant_Associations (Result.all, Asis.Element (Assoc_List));
      Set_Start_Position (Result.all, Start_Position (Aggr.all));
      Set_End_Position (Result.all, End_Position (Aggr.all));
      Item := Asis.Element (Result);
   end Function_To_Discriminant_Constraint;

   -----------------------------------
   -- Function_To_Indexed_Component --
   -----------------------------------

   procedure Function_To_Indexed_Component (Item : in out Asis.Element) is
      use Asis.Expressions;
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Element_Utils;
      use Lists.Primary_Expression_Lists;

      Result : Indexed_Component_Ptr := new Indexed_Component_Node;
      Items  : List := new List_Node;
      List   : Asis.Association_List := Function_Call_Parameters (Item);
      Tmp    : Asis.Element;
   begin
      Copy_Element
        (Source => Item,
         Target => Asis.Element (Result));

      Tmp := Prefix (Item);
      Set_Prefix (Result.all, Tmp);
      Set_Enclosing_Element (Tmp, Asis.Element (Result));

      for I in List'Range loop
         Tmp := Component_Expression (List (I));
         Add (Items.all, Tmp);
         Set_Enclosing_Element (Tmp, Asis.Element (Result));
      end loop;

      Set_Index_Expressions (Result.all, Asis.Element (Items));
      Item := Asis.Element (Result);
   end Function_To_Indexed_Component;

   ----------------------------------
   -- Function_To_Index_Constraint --
   ----------------------------------

   procedure Function_To_Index_Constraint (Item : in out Asis.Element) is
      use Asis.Elements;
      use Asis.Expressions;
      use Asis.Gela.Errors;
      use Asis.Gela.Elements.Defs;
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Element_Utils;
      use Asis.Gela.Elements.Defs.Rng;
      use Asis.Gela.Elements.Defs.Const;
      use Lists.Primary_Definition_Lists;

      Result : Index_Constraint_Ptr := new Index_Constraint_Node;
      Ind    : Discrete_Subtype_Indication_Ptr;
      Ranges : List := new List_Node;
      Child  : Asis.Element;
      Funct  : Function_Call_Node renames Function_Call_Node (Item.all);
      Aggr   : constant Asis.Element := Record_Aggregate (Funct);
      List   : Asis.Association_List := Function_Call_Parameters (Item);
   begin
      Copy_Element (Item, Asis.Element (Result));

      for I in List'Range loop
         Child := Component_Expression (List (I));

         if Element_Kind (Child) = An_Expression then
            Ind := new Discrete_Subtype_Indication_Node;
            Copy_Element (Child, Asis.Element (Ind));
            Set_Subtype_Mark (Ind.all, Child);
            Set_Enclosing_Element (Child, Asis.Element (Ind));
            Child := Asis.Element (Ind);
         end if;

         if Element_Kind (Child) = A_Definition then
            Add (Ranges.all, Child);
            Set_Enclosing_Element (Child, Asis.Element (Result));
         else
            raise Internal_Error;
         end if;

         declare
            Choises : Asis.Expression_List :=
              Record_Component_Choices (List (I));
         begin
            if Choises'Length /= 0 then
               Report (Child, Error_Syntax_Bad_Constraints);
            end if;
         end;
      end loop;

      Set_Discrete_Ranges (Result.all, Asis.Element (Ranges));
      Set_Start_Position (Result.all, Start_Position (Aggr.all));
      Set_End_Position (Result.all, End_Position (Aggr.all));
      Item := Asis.Element (Result);
   end Function_To_Index_Constraint;

   -----------------------
   -- Function_To_Slice --
   -----------------------

   procedure Function_To_Slice (Item : in out Asis.Element) is
      use Asis.Expressions;
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Element_Utils;

      Result : Slice_Ptr := new Slice_Node;
      List   : Asis.Association_List := Function_Call_Parameters (Item);
      Tmp    : Asis.Element;
   begin
      Copy_Element
        (Source => Item,
         Target => Asis.Element (Result));

      Tmp := Prefix (Item);
      Set_Prefix (Result.all, Tmp);
      Set_Enclosing_Element (Tmp, Asis.Element (Result));

      Tmp := Component_Expression (List (1));
      Set_Slice_Range (Result.all, Tmp);
      Set_Enclosing_Element (Tmp, Asis.Element (Result));
      Item := Asis.Element (Result);
   end Function_To_Slice;

   ---------------------------------
   -- Function_To_Type_Conversion --
   ---------------------------------

   procedure Function_To_Type_Conversion (Item : in out Asis.Element) is
      use Asis.Expressions;
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Element_Utils;

      Result : Type_Conversion_Ptr := new Type_Conversion_Node;
      List   : Asis.Association_List := Function_Call_Parameters (Item);
      Tmp    : Asis.Element;
   begin
      Copy_Element
        (Source => Item,
         Target => Asis.Element (Result));

      Tmp := Prefix (Item);
      Set_Converted_Or_Qualified_Subtype_Mark (Result.all, Tmp);
      Set_Enclosing_Element (Tmp, Asis.Element (Result));

      Tmp := Component_Expression (List (1));
      Set_Converted_Or_Qualified_Expression (Result.all, Tmp);
      Set_Enclosing_Element (Tmp, Asis.Element (Result));
      Item := Asis.Element (Result);
   end Function_To_Type_Conversion;

   ---------------------------------------
   -- Identifier_To_Enumeration_Literal --
   ---------------------------------------

   procedure Identifier_To_Enumeration_Literal (Item : in out Asis.Element) is
      use Asis.Expressions;
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Element_Utils;
      Result : Enumeration_Literal_Ptr := new Enumeration_Literal_Node;
   begin
      Copy_Element
        (Source => Item,
         Target => Asis.Element (Result));

      Set_Name_Image (Result.all, Name_Image (Item));

      declare
         List : Element_List :=
           Corresponding_Name_Definition_List (Item);
      begin
         for I in List'Range loop
            Add_Defining_Name (Asis.Element (Result), List (I));
            Remove_Defining_Name (Item, List (I));
         end loop;
      end;

      Set_Corresponding_Name_Declaration (Result.all,
        Corresponding_Name_Declaration (Item));

      Item := Asis.Element (Result);
   end Identifier_To_Enumeration_Literal;

   -------------------------
   -- Integer_Real_Number --
   -------------------------

   procedure Integer_Real_Number (Item : in out Asis.Element) is
      use Asis.Gela.Elements.Decl;
      Node   : Integer_Number_Declaration_Node renames
        Integer_Number_Declaration_Node (Item.all);
   begin
      Set_Declaration_Kind (Node, A_Real_Number_Declaration);
   end Integer_Real_Number;

   -----------------------------------
   -- Interface_To_Formal_Interface --
   -----------------------------------

   procedure Interface_To_Formal_Interface (Item : in out Asis.Statement) is
      use Asis.Gela.Elements.Defs.Types;
      use Asis.Gela.Elements.Defs.Formal;

      Node   : Interface_Type_Node renames Interface_Type_Node (Item.all);
      Result : Formal_Interface_Type_Ptr := new Formal_Interface_Type_Node;
   begin
      Element_Utils.Copy_Element
        (Source => Item,
         Target => Asis.Element (Result));

      Set_Interface_Kind (Result.all, Interface_Kind (Node));
      Set_Progenitor_List (Result.all, Progenitor_List_List (Node));

      Item := Asis.Element (Result);
   end Interface_To_Formal_Interface;

   ---------------------------------------
   -- Operator_Symbol_To_String_Literal --
   ---------------------------------------

   procedure Operator_Symbol_To_String_Literal (Item : in out Asis.Element) is
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Element_Utils;
      Result : String_Literal_Ptr := new String_Literal_Node;
   begin
      Copy_Element
        (Source => Item,
         Target => Asis.Element (Result));

      Set_Value_Image (Result.all, Asis.Expressions.Name_Image (Item));
      Item := Asis.Element (Result);
   end Operator_Symbol_To_String_Literal;

   -----------------------------
   -- Procedure_To_Entry_Call --
   -----------------------------

   procedure Procedure_To_Entry_Call (Item : in out Asis.Element) is
      use Asis.Gela.Elements.Stmt;
      use Asis.Gela.Element_Utils;

      Result : Entry_Call_Statement_Ptr := new Entry_Call_Statement_Node;
      Node   : Procedure_Call_Statement_Node renames
        Procedure_Call_Statement_Node (Item.all);
      Tmp    : Asis.Element;
   begin
      Element_Utils.Copy_Element
        (Source => Item,
         Target => Asis.Element (Result));

      Tmp := Called_Name (Node);
      Set_Called_Name (Result.all, Tmp);
      Set_Enclosing_Element (Tmp, Asis.Element (Result));

      Tmp := Call_Statement_Parameters_List (Node);
      Set_Call_Statement_Parameters (Result.all, Tmp);
      Set_Enclosing_Element_In_List (Tmp, Asis.Element (Result));

      Tmp := Label_Names_List (Node);
      Set_Label_Names (Result.all, Tmp);
      Set_Enclosing_Element_In_List (Tmp, Asis.Element (Result));

      Item := Asis.Element (Result);
   end Procedure_To_Entry_Call;

   -------------------------------------
   -- Procedure_To_Indexed_Entry_Call --
   -------------------------------------

   procedure Procedure_To_Indexed_Entry_Call
     (Element : in out Asis.Statement)
   is
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Elements.Stmt;
      use Asis.Gela.Element_Utils;
      use Lists.Primary_Expression_Lists;

      Result : Entry_Call_Statement_Ptr := new Entry_Call_Statement_Node;
      Index  : Indexed_Component_Ptr := new Indexed_Component_Node;
      Node   : Procedure_Call_Statement_Node renames
        Procedure_Call_Statement_Node (Element.all);
      Tmp    : Asis.Element;
      Items  : List := new List_Node;
      List   : Asis.Association_List :=
        Call_Statement_Parameters (Element.all);
   begin
      Element_Utils.Copy_Element
        (Source => Element,
         Target => Asis.Element (Index));

      Tmp := Called_Name (Node);
      Set_Prefix (Index.all, Tmp);
      Set_Enclosing_Element (Tmp, Asis.Element (Index));

      Tmp := Component_Expression (List (1).all);
      Add (Items.all, Tmp);
      Set_Index_Expressions (Index.all, Asis.Element (Items));
      Set_Enclosing_Element (Tmp, Asis.Element (Index));

      Element_Utils.Copy_Element
        (Source => Element,
         Target => Asis.Element (Result));

      Set_Called_Name (Result.all, Asis.Element (Index));
      Set_Enclosing_Element (Index.all, Asis.Element (Result));

      Tmp := Label_Names_List (Node);
      Set_Label_Names (Result.all, Tmp);
      Set_Enclosing_Element_In_List (Tmp, Asis.Element (Result));

      Element := Asis.Element (Result);
   end Procedure_To_Indexed_Entry_Call;

   -------------------------------
   -- Record_To_Array_Aggregate --
   -------------------------------

   type Base_Array_Aggregate_Ptr is
      access all Asis.Gela.Elements.Expr.Base_Array_Aggregate_Node'Class;

   procedure Record_To_Array_Aggregate
     (Item       : in out Asis.Element;
      Positional : in Boolean)
   is
      use Asis.Expressions;
      use Asis.Gela.Lists.Primary_Association_Lists;
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Element_Utils;

      --  Pos & Named ptr used for Storage_Pool works
      Pos    : Positional_Array_Aggregate_Ptr;
      Named  : Named_Array_Aggregate_Ptr;
      Result : Base_Array_Aggregate_Ptr;
      Items  : List := List (Record_Component_Associations_List
                             (Record_Aggregate_Node (Item.all)));

   begin
      if Positional then
         Pos := new Positional_Array_Aggregate_Node;
         Result := Base_Array_Aggregate_Ptr (Pos);
      else
         Named := new Named_Array_Aggregate_Node;
         Result := Base_Array_Aggregate_Ptr (Named);
      end if;

      Copy_Element
        (Source => Item,
         Target => Asis.Element (Result));

      Set_Array_Component_Associations (Result.all, Asis.Element (Items));
      Set_Enclosing_Element_In_List (Items, Asis.Element (Result));
      Item := Asis.Element (Result);
   end Record_To_Array_Aggregate;

   ---------------------------------
   -- Record_To_Array_Association --
   ---------------------------------

   procedure Record_To_Array_Association (Item : in out Asis.Element) is
      use Asis.Expressions;
      use Asis.Gela.Lists.Primary_Choise_Lists;
      use Asis.Gela.Elements.Assoc;
      use Asis.Gela.Element_Utils;
      Result : Array_Component_Association_Ptr :=
        new Array_Component_Association_Node;
      Items  : List := List (Record_Component_Choices_List
                             (Record_Component_Association_Node (Item.all)));
   begin
      Copy_Element
        (Source => Item,
         Target => Asis.Element (Result));

      Set_Array_Component_Choices (Result.all, Asis.Element (Items));

      if Items /= null then
         Set_Enclosing_Element_In_List (Items, Asis.Element (Result));
      end if;

      Set_Component_Expression (Result.all, Component_Expression (Item));

      Set_Enclosing_Element
        (Component_Expression (Item), Asis.Element (Result));

      Item := Asis.Element (Result);
   end Record_To_Array_Association;

   --------------------------------------
   -- Record_To_Parameter_Association  --
   --------------------------------------

   procedure Record_To_Parameter_Association (Item : in out Asis.Element) is
      use Asis.Expressions;
      use Asis.Gela.Lists.Primary_Choise_Lists;
      use Asis.Gela.Elements.Assoc;
      use Asis.Gela.Element_Utils;
      Result : Parameter_Association_Ptr :=
        new Parameter_Association_Node;
      Items  : List := List (Record_Component_Choices_List
                             (Record_Component_Association_Node (Item.all)));
   begin
      Copy_Element
        (Source => Item,
         Target => Asis.Element (Result));

      Set_Actual_Parameter (Result.all, Component_Expression (Item));
      Set_Enclosing_Element
        (Component_Expression (Item), Asis.Element (Result));

      if Items /= null then
         Set_Formal_Parameter (Result.all, Get_Item (Items, 1));
         Set_Enclosing_Element (Get_Item (Items, 1), Asis.Element (Result));
         Destroy (Items);
      end if;

      Set_Is_Normalized (Result.all, False);
      Set_Is_Defaulted_Association (Result.all, False);
      Item := Asis.Element (Result);
   end Record_To_Parameter_Association;

   -----------------------------------
   -- Set_Enclosing_Element_In_List --
   -----------------------------------

   procedure Set_Enclosing_Element_In_List
     (List   : access Asis.Gela.Base_Lists.Primary_Base_List_Node'Class;
      Parent : Asis.Element)
   is
      use Asis.Gela.Base_Lists;
   begin
      for J in 1 ..  Length (List.all) loop
         Element_Utils.Set_Enclosing_Element (Get_Item (List, J), Parent);
      end loop;
   end Set_Enclosing_Element_In_List;

   -----------------------------------
   -- Set_Enclosing_Element_In_List --
   -----------------------------------

   procedure Set_Enclosing_Element_In_List
     (List   : Asis.Element;
      Parent : Asis.Element) is
   begin
      if Assigned (List) then
         Set_Enclosing_Element_In_List
           (Asis.Gela.Base_Lists.Primary_Base_List (List), Parent);
      end if;
   end Set_Enclosing_Element_In_List;

   -------------------------
   -- To_Timed_Entry_Call --
   -------------------------

   procedure To_Timed_Entry_Call (Element : in out Asis.Statement) is
      use Asis.Gela.Elements.Stmt;
      use Asis.Gela.Element_Utils;

      Node        : Selective_Accept_Statement_Node renames
        Selective_Accept_Statement_Node (Element.all);
      Statement   : constant Timed_Entry_Call_Statement_Ptr :=
        new Timed_Entry_Call_Statement_Node;
      Tmp         : Asis.Element;
   begin
      Copy_Element (Element, Asis.Element (Statement));
      Tmp := Label_Names_List (Node);
      Set_Label_Names (Statement.all, Tmp);
      Set_Enclosing_Element_In_List (Tmp, Asis.Statement (Statement));

      Tmp := Statement_Paths_List (Node);
      Set_Statement_Paths (Statement.all, Tmp);
      Set_Enclosing_Element_In_List (Tmp, Asis.Statement (Statement));
      Element := Asis.Statement (Statement);
   end To_Timed_Entry_Call;

   -------------------------------
   -- To_Conditional_Entry_Call --
   -------------------------------

   procedure To_Conditional_Entry_Call (Element : in out Asis.Statement) is
      use Asis.Gela.Elements.Stmt;
      use Asis.Gela.Element_Utils;

      Node        : Selective_Accept_Statement_Node renames
        Selective_Accept_Statement_Node (Element.all);
      Statement   : constant Conditional_Entry_Call_Statement_Ptr :=
        new Conditional_Entry_Call_Statement_Node;
      Tmp         : Asis.Element;
   begin
      Copy_Element (Element, Asis.Element (Statement));
      Tmp := Label_Names_List (Node);
      Set_Label_Names (Statement.all, Tmp);
      Set_Enclosing_Element_In_List (Tmp, Asis.Statement (Statement));

      Tmp := Statement_Paths_List (Node);
      Set_Statement_Paths (Statement.all, Tmp);
      Set_Enclosing_Element_In_List (Tmp, Asis.Statement (Statement));

      Element := Asis.Statement (Statement);
   end To_Conditional_Entry_Call;

   -------------------------------
   -- To_Enumeration_Rep_Clause --
   -------------------------------

   procedure To_Enumeration_Rep_Clause (Element : in out Asis.Statement) is
      use Asis.Gela.Element_Utils;
      use Asis.Gela.Elements.Clause.Rep;

      Result      : Enumeration_Representation_Clause_Ptr :=
        new Enumeration_Representation_Clause_Node;
      Expr        : Asis.Element :=
        Representation_Clause_Expression (Element.all);
      Temp        : Asis.Element;
      Positional  : Boolean :=
        Could_Be_Positional_Array_Aggregate (Expr);
   begin
      Record_To_Array_Aggregate (Expr, Positional);

      Copy_Element (Element, Asis.Element (Result));

      Set_Representation_Clause_Expression (Result.all, Expr);
      Set_Enclosing_Element (Expr, Asis.Element (Result));

      Temp := Representation_Clause_Name (Element.all);
      Set_Representation_Clause_Name (Result.all, Temp);
      Set_Enclosing_Element (Temp, Asis.Element (Result));

      Element := Asis.Element (Result);
   end To_Enumeration_Rep_Clause;

end Asis.Gela.Replace;



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
