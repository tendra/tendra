------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Provide types to represent posible interpretations

with Asis.Gela.Classes;
with Gela.Containers.Lists;      use Gela;
with Gela.Embeded_Links.Lists;

package Asis.Gela.Overloads.Types is

   --------------------
   -- Interpretation --
   --------------------

   type Interpretation_Kinds is
     (An_Identifier,
      A_General_Access,
      An_Object_Access,
      A_Subprogram_Access,
      An_Array_Aggregate,
      A_Record_Aggregate,
      An_Extension_Aggregate,
      A_Boolean,
      A_Null,
      A_Type,
      A_String_Type,          --   Up_Only
      An_Expression,
      A_Declaration,
      A_Procedure_Call,
      A_Subprogram_Reference,
      A_Range,
      An_Attribute_Function,
      A_Family_Member,
      A_Subaggregate,         --    Down_only
      A_Skip);

   subtype Up_Only_Kinds is Interpretation_Kinds
     range An_Identifier .. A_String_Type;

   subtype Down_Only_Kinds is Interpretation_Kinds
     range A_Subaggregate .. A_Skip;

   type Interpretation (Kind : Interpretation_Kinds := A_String_Type)
      is record
         case Kind is
            when An_Expression =>
               Expression_Type : Classes.Type_Info;
            when An_Identifier =>
               Identifier : Asis.Identifier;
            when A_Declaration | A_Family_Member =>
               Declaration : Asis.Declaration;
            when A_String_Type | A_Procedure_Call | A_General_Access |
              An_Array_Aggregate | A_Record_Aggregate |
              An_Extension_Aggregate | A_Boolean | A_Null =>
               null;
            when A_Subprogram_Access =>
               Profile : Asis.Declaration;
            when An_Object_Access =>
               Object_Type : Classes.Type_Info;
            when A_Subprogram_Reference =>
               Access_Type : Classes.Type_Info;
            when A_Range =>
               Range_Type : Classes.Type_Info;
            when A_Subaggregate =>
               Array_Type : Classes.Type_Info;
               Deep       : Asis.List_Index;
            when An_Attribute_Function =>
               Prefix     : Asis.Declaration;
               Attr_Kind  : Asis.Attribute_Kinds;
               Class_Wide : Boolean;
            when A_Type =>
               Type_Info : Classes.Type_Info;
            when A_Skip =>
               null;
         end case;
      end record;

   function Image (Object : Interpretation) return Wide_String;

   subtype Up_Interpretation is Interpretation;

   function Up_Expression
     (Expression_Type : Asis.Element;
      Place           : Asis.Element) return Up_Interpretation;

   function Up_Expression
     (Info : Classes.Type_Info) return Up_Interpretation;

   type Down_Interpretation is new Interpretation;

   function To_Down_Interpretation
     (Item : Up_Interpretation) return Down_Interpretation;

   function Dereference (Tipe : Classes.Type_Info)
     return Up_Interpretation;

   ------------------
   -- Implicit_Set --
   ------------------

   type Implicit_Set is private;

   function Create return Implicit_Set;

   procedure Destroy (Set : in out Implicit_Set);

   ---------------------------
   -- Up_Interpretation_Set --
   ---------------------------

   type Up_Interpretation_Set is private;

   function Create return Up_Interpretation_Set;

   procedure Destroy (Set : in out Up_Interpretation_Set);

   procedure Add
     (Container : in out Up_Interpretation_Set;
      Item      : in     Up_Interpretation);

   function Length (Set   : Up_Interpretation_Set) return Natural;

   procedure Get
     (Set   : in out Up_Interpretation_Set;
      Index : in     Positive;
      Item  :    out Up_Interpretation);

   procedure Resolve_Identifier
     (Set    : in out Up_Interpretation_Set);

   procedure Expand_Prefix
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element);

--   procedure Expand_Function_Call
   procedure Expand_Expression
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element);

   procedure Expand_Attribute_Prefix
     (Set         : in out Up_Interpretation_Set;
      Impl        : in out Implicit_Set;
      Element     : in     Asis.Element;
      Dereference : in     Boolean := True);

   procedure Constrain_To_Access_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element);

   procedure Constrain_To_Numeric_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element);

   procedure Constrain_To_Integer_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element);

   procedure Constrain_To_Boolean_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element);

   procedure Constrain_To_Discrete_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element);

   procedure Constrain_To_Real_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element);

   procedure Constrain_To_Non_Limited_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element);

   procedure Constrain_To_Tagged_Non_Limited_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element);

   procedure Constrain_To_Tagged_Types
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element);

   procedure Constrain_To_Type
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element;
      Tipe    : in     Classes.Type_Info);

   procedure Constrain_To_Range
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element;
      Tipe    : in     Classes.Type_Info);

   procedure Constrain_To_Discrete_Range
     (Set     : in out Up_Interpretation_Set;
      Impl    : in out Implicit_Set;
      Element : in     Asis.Element);

   procedure Constrain_To_Calls
     (Set     : in out Up_Interpretation_Set);

   procedure Constrain_To_Expected_Profile
     (Set     : in out Up_Interpretation_Set;
      Profile : in     Asis.Declaration;
      Place   : in     Asis.Element;
      Empty   : in     Boolean := False);

   procedure Select_Prefered
     (Set     : in out Up_Interpretation_Set);

   function Has_Type
     (Set    : Up_Interpretation_Set;
      Mark   : Classes.Type_Info) return Boolean;

   function Get_Type
     (Set    : Up_Interpretation_Set;
      Mark   : Classes.Type_Info) return Up_Interpretation;

   function Has_Interpretation
      (Set   : Up_Interpretation_Set;
       Item  : Asis.Element) return Boolean;

   function Image (Set : Up_Interpretation_Set) return Wide_String;

   type Up_Interpretation_Set_Array is
      array (Positive range <>) of Up_Interpretation_Set;

   ---------------------------
   -- Stored_Interpretation --
   ---------------------------

   type Stored_Interpretation_Kinds is
     (A_Function_Call,
      A_Procedure_Call,
      A_Slice,
      An_Array,
      A_Subprogram_Reference,
      A_Component,
      A_Family,
      A_Type_Conversion);

   type Type_Infos is array (List_Index range <>) of Classes.Type_Info;
   type Type_Infos_Access is access Type_Infos;

   type Stored_Interpretation
      is record
         Kind        : Stored_Interpretation_Kinds;
         Down        : Up_Interpretation;
         Result_Type : Classes.Type_Info;
         Component   : Asis.Declaration;
         Real_Types  : Type_Infos_Access;
      end record;

   --  Think about Stored_Interpretation as a way to pass data from
   --  Up pass to Down pass routine.

   ----------------
   -- Stored_Set --
   ----------------

   type Stored_Set is private;

   function Create return Stored_Set;

   procedure Destroy (Set : in out Stored_Set);

   procedure Add
     (Container : in out Stored_Set;
      Item      : in     Stored_Interpretation);

   function Length (Set   : Stored_Set) return Natural;

   procedure Get
     (Set   : in out Stored_Set;
      Index : in     Positive;
      Item  :    out Stored_Interpretation);

   -----------------
   -- Stored_Sets --
   -----------------

   type Stored_Sets is private;

   function Create return Stored_Sets;

   procedure Destroy (Set : in out Stored_Sets);

   procedure Put
     (Set  : in out Stored_Sets;
      Key  : in     Asis.Element;
      Item : in     Stored_Set);

   procedure Get
     (Set  : in     Stored_Sets;
      Key  : in     Asis.Element;
      Item :    out Stored_Set);

   function Check_Name (Name : Up_Interpretation) return Boolean;

   function Get_Profile
     (Name : Up_Interpretation) return Asis.Parameter_Specification_List;

   function Get_Parameter_Type
     (Name    : Up_Interpretation;
      Profile : Asis.Parameter_Specification_List;
      Index   : List_Index;
      Place   : Asis.Element) return Classes.Type_Info;

   function Get_Result_Profile
     (Name  : Up_Interpretation;
      Place : Asis.Element) return Up_Interpretation;

   procedure Check_Implicit
     (Set     : in out Implicit_Set;
      Store   : in out Stored_Sets;
      Element : in out Asis.Element;
      Down    : in out Down_Interpretation);

private

   package L is new Containers.Lists (Up_Interpretation);

   type L_List_Access is access all L.List;

   type Up_Interpretation_Set is record
      Items  : L_List_Access;
      Length : Natural :=0;
      Index  : Natural :=0;
      Pos    : L.Cursor := L.No_Element;
   end record;

   package R is new Containers.Lists (Stored_Interpretation);

   type Stored_Set_Node is record
      Key    : Asis.Element;
      Next   : Stored_Set;
      List   : R.List;
      Length : Natural :=0;
      Index  : Natural :=0;
      Pos    : R.Cursor := R.No_Element;
   end record;

   type Stored_Set is access all Stored_Set_Node;

   function Get_Next (Left : Stored_Set) return Stored_Set;
   procedure Set_Next (Left, Next : Stored_Set);

   package S is new Embeded_Links.Lists (Stored_Set_Node, Stored_Set);

   type Stored_Sets is access all S.List;

   type Implicit_Node is record
      Key         : Asis.Element;
      Down        : Up_Interpretation;
      Return_Type : Classes.Type_Info;
      Is_Call     : Boolean;
   end record;

   package Implicit_Nodes is new Containers.Lists (Implicit_Node);

   type Implicit_Node_List is access all Implicit_Nodes.List;

   type Implicit_Set is access all Implicit_Nodes.List;

end Asis.Gela.Overloads.Types;



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
