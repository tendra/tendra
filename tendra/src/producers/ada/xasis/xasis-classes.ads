------------------------------------------------------------------------------
--                           G E L A   X A S I S                            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Let you check if type is integer, scalar, string, etc
--  Be aware this unit dont get into account if type is private.
--  It always takes full view of the type.

with Asis;

package XASIS.Classes is

   function Is_Elementary           (Tipe : Asis.Declaration) return Boolean;
   function Is_Scalar               (Tipe : Asis.Declaration) return Boolean;
   function Is_Discrete             (Tipe : Asis.Declaration) return Boolean;
   function Is_Enumeration          (Tipe : Asis.Declaration) return Boolean;
   function Is_Character            (Tipe : Asis.Declaration) return Boolean;
   function Is_Boolean              (Tipe : Asis.Declaration) return Boolean;
   function Is_Signed_Integer       (Tipe : Asis.Declaration) return Boolean;
   function Is_Modular_Integer      (Tipe : Asis.Declaration) return Boolean;
   function Is_Float_Point          (Tipe : Asis.Declaration) return Boolean;
   function Is_Ordinary_Fixed_Point (Tipe : Asis.Declaration) return Boolean;
   function Is_Decimal_Fixed_Point  (Tipe : Asis.Declaration) return Boolean;
   function Is_Object_Access        (Tipe : Asis.Declaration) return Boolean;
   function Is_Subprogram_Access    (Tipe : Asis.Declaration) return Boolean;
   function Is_String               (Tipe : Asis.Declaration) return Boolean;
   function Is_Array                (Tipe : Asis.Declaration) return Boolean;
   function Is_Untagged_Record      (Tipe : Asis.Declaration) return Boolean;
   function Is_Tagged               (Tipe : Asis.Declaration) return Boolean;
   function Is_Task                 (Tipe : Asis.Declaration) return Boolean;
   function Is_Protected            (Tipe : Asis.Declaration) return Boolean;
   function Is_Integer              (Tipe : Asis.Declaration) return Boolean;
   function Is_Real                 (Tipe : Asis.Declaration) return Boolean;
   function Is_Fixed_Point          (Tipe : Asis.Declaration) return Boolean;
   function Is_Access               (Tipe : Asis.Declaration) return Boolean;
   function Is_Composite            (Tipe : Asis.Declaration) return Boolean;

   type Type_Info is private;

   function Type_From_Declaration  (Tipe : Asis.Declaration) return Type_Info;
   function Type_From_Subtype_Mark  (Mark : Asis.Expression) return Type_Info;
   function Type_From_Indication    (Ind  : Asis.Definition) return Type_Info;
   function Type_From_Discrete_Def  (Def  : Asis.Definition) return Type_Info;
   function Type_Of_Declaration    (Decl : Asis.Declaration) return Type_Info;
   function Type_Of_Range   (Lower, Upper : Asis.Expression) return Type_Info;
   function Type_Of_Range         (Lower, Upper : Type_Info) return Type_Info;

   procedure Set_Class_Wide  (Info : in out Type_Info);

   function Is_Not_Type             (Info : Type_Info) return Boolean;
   function Is_Declaration          (Info : Type_Info) return Boolean;
   function Is_Definition           (Info : Type_Info) return Boolean;
   function Is_Class_Wide           (Info : Type_Info) return Boolean;
   function Is_Anonymous_Access     (Info : Type_Info) return Boolean;

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
     (Info   : Type_Info;
      Length : Asis.List_Index) return Boolean;

   function Get_Declaration (Info : Type_Info) return Asis.Declaration;
   function Get_Definition  (Info : Type_Info) return Asis.Definition;

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

   function Destination_Type (Info : Type_Info) return Type_Info;

   function Debug_Image (Info : Type_Info) return Wide_String;

   function Get_Array_Index_Type
     (Info  : Type_Info;
      Index : Asis.List_Index := 1) return Type_Info;

   function Get_Array_Element_Type (Tipe : Type_Info) return Type_Info;

   Not_A_Type : constant Type_Info;

   package T is
      function Universal_Integer return Type_Info;
      function Universal_Real    return Type_Info;
      function Universal_Fixed   return Type_Info;
      function Root_Integer      return Type_Info;
      function Root_Real         return Type_Info;
      function System_Address    return Type_Info;
      function System_Bit_Order  return Type_Info;
      function Integer           return Type_Info;
      function String            return Type_Info;
      function Wide_String       return Type_Info;
      function Boolean           return Type_Info;
      function Exception_Id      return Type_Info;
      function Task_Id           return Type_Info;
      function Root_Storage_Pool return Type_Info;
      function Tag               return Type_Info;
      function Natural           return Type_Info;
      function Duration          return Type_Info;
      function Wide_Character    return Type_Info;
      function Character         return Type_Info;
      function Root_Stream_Type  return Type_Info;
   end T;
   
private

   type Class_Kinds is
     (A_Character,
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
      A_String,
      An_Other_Array,
      A_Untagged_Record,
      A_Tagged,
      A_Task,
      A_Protected,
      A_Private,
      An_Incomplete);

   subtype An_Elementary is Class_Kinds
     range A_Character .. A_Function_Access;

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
     range A_Constant_Access .. A_Function_Access;

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

   function Type_Class (Tipe : Asis.Element) return Class_Kinds;

   generic
      Lower       : Class_Kinds;
      Upper       : Class_Kinds;
      With_Access : Boolean := False;
   package Class_Range is
      function Is_Class (Tipe : Asis.Declaration) return Boolean;
      function Is_Class (Info : Type_Info) return Boolean;
   end Class_Range;

   type Type_Info is record
      Element    : Asis.Element;
      Class_Kind : Class_Kinds;
      Class_Wide : Boolean := False;
      Definition : Boolean := False;
      Is_Access  : Boolean := False;
   end record;

   Not_A_Type : constant Type_Info :=
     (Asis.Nil_Element, Class_Kinds'First, False, False, False);

end XASIS.Classes;


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
