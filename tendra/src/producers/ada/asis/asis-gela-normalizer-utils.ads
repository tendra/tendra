------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Helper subprograms

with Asis.Declarations;

private package Asis.Gela.Normalizer.Utils is

   procedure Set_Default_Kind (Element : Asis.Element);
   procedure Set_Mode_Kind    (Element : Asis.Element);

   procedure Set_Names
     (Element : Asis.Element;
      Name    : Asis.Defining_Name := Asis.Nil_Element);

   procedure Check_Empty_Profile (Element : in out Asis.Element);
   procedure Check_Empty_Result (Profile : in out Asis.Element);
   procedure Check_Empty_Generic (Element : Asis.Element);
   procedure Normalize_Access_Type (Element : Asis.Element);
   procedure Normalize_Formal_Access_Type (Element : Asis.Element);

   procedure Normalize_Attribute_Reference (Element : Asis.Element);
   procedure Normalize_Qualified_Expression (Element : Asis.Element);
   procedure Normalize_Procedure_Call (Element : Asis.Element);
   procedure Normalize_Pragma_Argument (Element : in out Asis.Expression);

   procedure Normalize_Function_Call
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information);

   procedure Normalize_Record_Aggregate
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information);

   procedure To_Deferred_Constant (Element : in out Asis.Element);

   procedure Normalize_Enumeration_Rep_Clause (Element : in out Asis.Element);

   procedure Set_Start_Position
     (Element, Source : Asis.Element);

   procedure Set_Enum_Positions
     (List : Asis.Declaration_List);

   procedure Create_Incomplete_Definition (Element : Asis.Declaration);

   ----------------------------------
   -- Split_Function_Specification --
   ----------------------------------

   generic
      type Node_Type is new Element_Node with private;

      with function Specification (Element : Node_Type)
                                  return Asis.Element is <>;

      with procedure Set_Parameter_Profile
        (Element : in out Node_Type;
         Value   : in     Asis.Element) is <>;

      with procedure Set_Result_Subtype
        (Element : in out Node_Type;
         Value   : in     Asis.Expression) is <>;

   procedure Split_Function_Specification (Element : Asis.Element);

   -----------------------------------
   -- Split_Procedure_Specification --
   -----------------------------------

   generic
      type Node_Type is new Element_Node with private;

      with function Specification (Element : Node_Type)
                                  return Asis.Element is <>;

      with procedure Set_Parameter_Profile
        (Element : in out Node_Type;
         Value   : in     Asis.Element) is <>;

   procedure Split_Procedure_Specification (Element : Asis.Element);

   -------------------
   -- Split_Profile --
   -------------------

   generic
      type Node_Type is new Element_Node with private;

      with function Result_Subtype (Element : Node_Type)
                                   return Asis.Element is <>;

      with procedure Set_Parameter_Profile
        (Element : in out Node_Type;
         Value   : in     Asis.Element) is <>;

      with procedure Set_Result_Subtype
        (Element : in out Node_Type;
         Value   : in     Asis.Definition) is <>;

   procedure Split_Profile (Element : Asis.Element);

   ----------------------------------
   -- Normalize_Handled_Statements --
   ----------------------------------

   generic
      type Node_Type is new Element_Node with private;

      with function Handled_Statements
        (Element : Node_Type) return Asis.Element is <>;

      with procedure Set_Statements
        (Element : in out Node_Type;
         Value   : in     Asis.Element) is <>;

      with procedure Set_Exception_Handlers
        (Element : in out Node_Type;
         Value   : in     Asis.Element) is <>;

   procedure Normalize_Handled_Statements (Element : Asis.Element);

   ---------------------------
   -- Check_Back_Identifier --
   ---------------------------

   generic
      type Node_Type is new Element_Node with private;

      with function Compound_Name
        (Element : Node_Type) return Asis.Element is <>;

      with procedure Set_Is_Name_Repeated
        (Element : in out Node_Type;
         Value   : in     Boolean) is <>;

      with function Names (Element : Asis.Element) return Asis.Element_List
            is Asis.Declarations.Names;

   procedure Check_Back_Identifier (Element : Asis.Element);

   ---------------------------------
   -- Split_Package_Specification --
   ---------------------------------

   generic
      type Node_Type is new Element_Node with private;

      with function Specification (Element : Node_Type)
                                  return Asis.Element is <>;

      with procedure Set_Is_Name_Repeated
        (Element : in out Node_Type;
         Value   : in     Boolean) is <>;

      with procedure Set_Is_Private_Present
        (Element : in out Node_Type;
         Value   : in     Boolean) is <>;

      with procedure Set_Visible_Part_Declarative_Items
        (Element : in out Node_Type;
         Value   : in     Asis.Element) is <>;

      with procedure Set_Private_Part_Declarative_Items
        (Element : in out Node_Type;
         Value   : in     Asis.Element) is <>;

   procedure Split_Package_Specification (Element : Asis.Element);

   ---------------------------
   -- Set_Generic_Unit_Name --
   ---------------------------

   generic
      type Node_Type is new Element_Node with private;

      with procedure Set_Generic_Unit_Name
        (Element : in out Node_Type;
         Value   : in     Asis.Expression) is <>;

   procedure Set_Generic_Unit_Names (Element : Asis.Element);

   generic
      type Node_Type is new Element_Node with private;

      with procedure Set_Trait_Kind
        (Element : in out Node_Type;
         Value   : in     Asis.Trait_Kinds) is <>;

   procedure Set_Trait_Kind (Element : Asis.Element);

   ------------------------------
   -- Normalize_Component_List --
   ------------------------------

   generic
      type Node_Type is new Element_Node with private;

      with function Record_Components_List
        (Element : Node_Type) return Asis.Element is <>;

   procedure Normalize_Component_List (Element : Asis.Element);

   ---------------------
   -- Set_Has_Private --
   ---------------------

   generic
      type Node_Type is new Element_Node with private;

      with function Private_Part_Items_List
        (Element : Node_Type) return Asis.Element is <>;

      with procedure Set_Is_Private_Present
        (Element : in out Node_Type;
         Value   : in     Boolean) is <>;

   procedure Set_Has_Private (Element : Asis.Element);

   ----------------------
   -- Set_Formal_Array --
   ----------------------

   generic
      type Node_Type is new Element_Node with private;

      type Array_Type is new Element_Node with private;

      with procedure Set_Index_Subtype_Definitions
        (Element : in out Node_Type;
         Value   : in     Asis.Element) is <>;

      with function Index_Subtype_Definitions_List
        (Element : Array_Type) return Asis.Element is <>;

      with procedure Set_Array_Component_Definition
        (Element : in out Node_Type;
         Value   : in     Asis.Component_Definition) is <>;

      with function Array_Definition
        (Element : Node_Type) return Asis.Element is <>;

--      with function Array_Component_Definition
--        (Element : Array_Type) return Asis.Element is <>;

   procedure Set_Formal_Array (Element : Asis.Element);

   -------------------------------
   -- Drop_Range_Attr_Reference --
   -------------------------------
   generic
      type Node_Type is new Element_Node with private;

      with procedure Set_Range_Attribute
        (Element : in out Node_Type;
         Value   : in     Asis.Expression) is <>;

   procedure Drop_Range_Attr_Reference (Element : Asis.Element);

   generic
      type Node_Type is new Element_Node with private;

      with procedure Set_Subtype_Mark
        (Element : in out Node_Type;
         Value   : in     Asis.Expression) is <>;

      with procedure Set_Subtype_Constraint
        (Element : in out Node_Type;
         Value   : in     Asis.Constraint) is <>;

   procedure Drop_Range_Subtype_Indication (Element : Asis.Element);


   ------------------------------------
   -- Normalize_Overriding_Indicator --
   ------------------------------------

   generic
      type Node_Type is new Element_Node with private;

      with function Overriding_Indicator
        (Element : Node_Type) return Asis.Element is <>;

      with procedure Set_Overriding_Indicator_Kind
        (Element : in out Node_Type;
         Value   : in     Asis.Overriding_Indicator_Kinds) is <>;

   procedure Normalize_Overriding_Indicator (Element : Asis.Element);

end Asis.Gela.Normalizer.Utils;


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
