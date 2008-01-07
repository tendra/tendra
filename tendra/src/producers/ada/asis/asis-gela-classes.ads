------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Represent information about a type and operations to classify it.

package Asis.Gela.Classes is

   type Type_Info is private;

   function Type_From_Declaration
     (Tipe  : Asis.Declaration;
      Place : Asis.Element) return Type_Info;
   --  Return information about a type given by type_declaration.
   --  Place element is used to provide "point of view", because
   --  type could be private from one point, but concrete from
   --  another.

   function Type_From_Subtype_Mark
     (Mark  : Asis.Expression;
      Place : Asis.Element) return Type_Info;
   --  Return information about a type given by subtype_mark

   function Type_From_Indication
     (Ind   : Asis.Definition;
      Place : Asis.Element) return Type_Info;
   --  Return information about a type given by subtype_indication
   --  Ind should be subtype_indication
   --  (or access_definition from parameter_and_result_profile)

   function Type_From_Discrete_Def
     (Def   : Asis.Definition;
      Place : Asis.Element) return Type_Info;
   --  Return information about a type given by discrete_definition

   function Type_Of_Declaration
     (Decl  : Asis.Declaration;
      Place : Asis.Element) return Type_Info;
   --  Return information about a type used in object declaration

   function Type_Of_Name
     (Name  : Asis.Defining_Name;
      Place : Asis.Element) return Type_Info;
   --  Return information about a type given by defining_name

   function Type_Of_Range
     (Lower, Upper : Asis.Expression) return Type_Info;

   function Type_Of_Range
     (Lower, Upper : Type_Info) return Type_Info;

   procedure Set_Class_Wide  (Info : in out Type_Info);
   --  Turn type into class-wide
   function Drop_Class (Info : Type_Info) return Type_Info;
   --  Remove 'Class from Type_Info

   procedure Set_Access      (Info : in out Type_Info; Value : Boolean);
   --  Turn type into anonymouse access

   --  Clasification requests

   function Is_Not_Type             (Info : Type_Info) return Boolean;
   function Is_Declaration          (Info : Type_Info) return Boolean;
   function Is_Definition           (Info : Type_Info) return Boolean;
   function Is_Class_Wide           (Info : Type_Info) return Boolean;
   function Is_Anonymous_Access     (Info : Type_Info) return Boolean;
   function Is_Limited              (Info : Type_Info) return Boolean;

   function Is_Elementary           (Info : Type_Info) return Boolean;
   function Is_Scalar               (Info : Type_Info) return Boolean;
   function Is_Discrete             (Info : Type_Info) return Boolean;
   function Is_Enumeration          (Info : Type_Info) return Boolean;
   function Is_Character            (Info : Type_Info) return Boolean;
   function Is_Boolean              (Info : Type_Info) return Boolean;
   function Is_Signed_Integer       (Info : Type_Info) return Boolean;
   function Is_Modular_Integer      (Info : Type_Info) return Boolean;
   function Is_Float_Point          (Info : Type_Info) return Boolean;
   function Is_Ordinary_Fixed_Point (Info : Type_Info) return Boolean;
   function Is_Decimal_Fixed_Point  (Info : Type_Info) return Boolean;
   function Is_Constant_Access      (Info : Type_Info) return Boolean;
   function Is_Variable_Access      (Info : Type_Info) return Boolean;
   function Is_Object_Access        (Info : Type_Info) return Boolean;
   function Is_General_Access       (Info : Type_Info) return Boolean;
   function Is_Procedure_Access     (Info : Type_Info) return Boolean;
   function Is_Function_Access      (Info : Type_Info) return Boolean;
   function Is_Subprogram_Access    (Info : Type_Info) return Boolean;
   function Is_String               (Info : Type_Info) return Boolean;
   function Is_Array                (Info : Type_Info) return Boolean;
   function Is_Boolean_Array        (Info : Type_Info) return Boolean;
   function Is_Discrete_Array       (Info : Type_Info) return Boolean;
   function Is_Untagged_Record      (Info : Type_Info) return Boolean;
   function Is_Tagged               (Info : Type_Info) return Boolean;
   function Is_Task                 (Info : Type_Info) return Boolean;
   function Is_Protected            (Info : Type_Info) return Boolean;
   function Is_Integer              (Info : Type_Info) return Boolean;
   function Is_Real                 (Info : Type_Info) return Boolean;
   function Is_Fixed_Point          (Info : Type_Info) return Boolean;
   function Is_Numeric              (Info : Type_Info) return Boolean;
   function Is_Access               (Info : Type_Info) return Boolean;
   function Is_Composite            (Info : Type_Info) return Boolean;
   function Is_Universal            (Info : Type_Info) return Boolean;
   function Is_Incomplete           (Info : Type_Info) return Boolean;

   function Is_Array
     (Tipe   : Type_Info;
      Length : Asis.List_Index) return Boolean;

   function Get_Subtype (Info : Type_Info) return Asis.Declaration;

   --  Misc functions
   function Is_Equal (Left, Right : Type_Info) return Boolean;

   function Is_Covered
     (Specific   : Type_Info;
      Class_Wide : Type_Info) return Boolean;

   function Is_Expected_Type
     (Specific : Type_Info;
      Expected : Type_Info) return Boolean;

   function Is_Subtype_Mark (Mark : Asis.Expression) return Boolean;
   function Is_Type_Declaration (Decl : Asis.Declaration) return Boolean;

   function Debug_Image (Info : Type_Info) return Wide_String;

   function Destination_Type (Tipe  : Type_Info) return Type_Info;

   function Get_Array_Element_Type
     (Tipe  : Type_Info) return Type_Info;

   function Get_Array_Index_Type
     (Tipe  : Type_Info;
      Index : Asis.List_Index := 1) return Type_Info;

   function Parent_Type (Tipe : Type_Info) return Type_Info;
   function Top_Parent_Type (Tipe : Type_Info) return Type_Info;
   function Function_Result_Type (Tipe : Type_Info) return Type_Info;
   function Subprogram_Parameters
     (Tipe : Type_Info) return Asis.Parameter_Specification_List;

   function Conform_Access_Type
     (Decl : Asis.Declaration;
      Tipe : Type_Info) return Boolean;

   function Destinated_Are_Type_Conformant
     (Left, Right : Type_Info) return Boolean;
   --  Left, Right should be Is_Subprogram_Access and Is_Anonymous_Access

   function Find_Component
     (Tipe : Type_Info;
      Name : Asis.Program_Text) return Asis.Declaration;

   function Get_Declaration (Info : Type_Info) return Asis.Declaration;
   function Get_Place       (Info : Type_Info) return Asis.Element;
   function Get_Type_Def    (Tipe : Type_Info) return Asis.Definition;
   function Is_Child_Of     (Child, Parent : Type_Info) return Boolean;

   Not_A_Type : constant Type_Info;

private

   type Class_Kinds is
     (An_Incomplete,
      A_Character,
      A_Boolean,
      An_Other_Enum,
      An_Universal_Integer,
      A_Signed_Integer,
      A_Modular_Integer,
      An_Universal_Real,
      A_Float_Point,
      An_Universal_Fixed,
      A_Ordinary_Fixed_Point,
      A_Decimal_Fixed_Point,
      A_Constant_Access,
      A_Variable_Access,
      A_Pool_Access,
      A_Procedure_Access,
      A_Function_Access,
      A_Universal_Access,
      A_String,
      A_Boolean_Array,
      A_Other_Discrete_Array,
      An_Other_Array,
      A_Untagged_Record,
      A_Tagged,
      A_Task,
      A_Protected,
      A_Private);

   subtype An_Elementary is Class_Kinds
     range A_Character .. A_Universal_Access;

   subtype A_Scalar is Class_Kinds
     range A_Character .. A_Decimal_Fixed_Point;

   subtype A_Discrete is Class_Kinds
     range A_Character .. A_Modular_Integer;

   subtype An_Enumeration is Class_Kinds
     range A_Character .. An_Other_Enum;

   subtype An_Integer is Class_Kinds
     range An_Universal_Integer .. A_Modular_Integer;

   subtype A_Real is Class_Kinds
     range An_Universal_Real .. A_Decimal_Fixed_Point;

   subtype A_Fixed_Point is Class_Kinds
     range An_Universal_Fixed .. A_Decimal_Fixed_Point;

   subtype A_Numeric is Class_Kinds
     range An_Universal_Integer .. A_Decimal_Fixed_Point;

   subtype An_Access is Class_Kinds
     range A_Constant_Access .. A_Universal_Access;

   subtype A_Subprogram_Access is Class_Kinds
     range A_Procedure_Access .. A_Function_Access;

   subtype An_Object_Access is Class_Kinds
     range A_Constant_Access .. A_Pool_Access;

   subtype A_General_Access is Class_Kinds
     range A_Constant_Access .. A_Variable_Access;

   subtype A_Composite is Class_Kinds
     range A_String .. A_Private;

   subtype An_Array is Class_Kinds
     range A_String .. An_Other_Array;

   subtype A_Discrete_Array is Class_Kinds
     range A_String .. A_Other_Discrete_Array;

   type Info_Kinds is
     (Declaration_Info,      --  Ordinary type declaration
      Defining_Name_Info,    --  Anonymous type other then in return
      Return_Info);          --  Anonymous type in function return

   type Type_Info (Kind : Info_Kinds := Declaration_Info) is record
      Class_Kind     : Class_Kinds;
      Is_Class_Wide  : Boolean := False;
      Is_Access      : Boolean := False;
      Is_Limited     : Boolean := False;
      Place          : Asis.Element;  --  type viewed from Place

      case Kind is
         when Declaration_Info =>
            Base_Type : Asis.Declaration;
            Type_View : Asis.Declaration;
            Subtipe   : Asis.Declaration;
         when Defining_Name_Info =>
            Object_Name : Asis.Defining_Name;  --  name of object of anon type
         when Return_Info =>
            Access_Definition : Asis.Definition;
      end case;
   end record;

   Not_A_Type : constant Type_Info :=
     (Declaration_Info, Class_Kinds'First, False, False, False,
      others => Asis.Nil_Element);

end Asis.Gela.Classes;


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
