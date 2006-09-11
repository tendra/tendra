with Ada.Characters.Handling;
with Ada.Unchecked_Deallocation;

with Asis.Elements;
with Asis.Definitions;
with Asis.Expressions;
with Asis.Declarations;

with XASIS.Static.Iter;
with XASIS.Static.Signed;
with XASIS.Static.Discrete;
with XASIS.Static.Unsigned;

pragma Elaborate (XASIS.Static.Iter);

package body XASIS.Static is

   type Calculator is null record;

   function Literal
     (Object  : access Calculator;
      Element : in     Asis.Expression) return Value;

   function Operator
     (Object  : access Calculator;
      Tipe    : in     Classes.Type_Info;
      Kind    : in     Asis.Operator_Kinds;
      Args    : in     Asis.Association_List) return Value;

   function Attribute
     (Object  : access Calculator;
      Tipe    : in     Classes.Type_Info;
      Kind    : in     Asis.Attribute_Kinds;
      Element : in     Asis.Expression) return Value;

   function Attribute_Call
     (Object  : access Calculator;
      Tipe    : in     Classes.Type_Info;
      Kind    : in     Asis.Attribute_Kinds;
      Args    : in     Asis.Association_List) return Value;

   function Check_Range
     (Object   : access Calculator;
      Expr     : in     Asis.Expression;
      Bounds   : in     Static_Range;
      Invert   : in     Boolean) return Value;

   function Undefined
     (Object  : access Calculator;
      Element : in     Asis.Expression) return Value;

   function Range_Of_Array
     (Object  : access Calculator;
      Decl    : in     Asis.Declaration;
      Attr    : in     Asis.Expression) return Static_Range;

   function Range_Of_Type
     (Object   : access Calculator;
      Type_Def : in     Asis.Definition) return Static_Range;

   function String_Constant_Range
     (Object  : access Calculator;
      Decl    : in     Asis.Declaration) return Static_Range;

   package S is new XASIS.Static.Iter
     (Value, Static_Range, Calculator,
      Literal => Literal,
      Operator => Operator,
      Attribute => Attribute,
      Attribute_Call => Attribute_Call,
      Check_Range => Check_Range,
      Undefined => Undefined,
      Range_Of_Array => Range_Of_Array,
      Range_Of_Type => Range_Of_Type,
      String_Constant_Range => String_Constant_Range);

   function Get_Type_Class (Info : Classes.Type_Info) return Type_Class'Class;

   function "+" (Item : Asis.ASIS_Integer) return XASIS.Integers.Value;

   function Check_Range
     (Object   : access Calculator;
      Val      : in     Value;
      Bounds   : in     Static_Range;
      Invert   : in     Boolean) return Value;

   ---------
   -- "+" --
   ---------

   function "+" (Item : Value) return Asis.ASIS_Integer is
   begin
      if Item.Kind = Static_Discrete then
         return Asis.ASIS_Integer'Value (XASIS.Integers.Image (Item.Pos));
      else
         Raise_Error (Unexpected_Type);
         return 0;
      end if;
   end "+";

   ---------
   -- "+" --
   ---------

   function "+" (Item : Asis.ASIS_Integer) return XASIS.Integers.Value is
   begin
      return XASIS.Integers.Literal (Asis.ASIS_Integer'Image (Item));
   end "+";

   ------------
   -- Adjust --
   ------------

   procedure Adjust (Object : in out Integer_Array_Node) is
   begin
      if Object.Data /= null then
         Object.Data := new Integer_Array'(Object.Data.all);
      end if;
   end Adjust;

   -------------------------------------
   -- Attribute_Designator_Expression --
   -------------------------------------

   function Attribute_Designator_Expression
     (Attr : Asis.Expression)
      return Value
   is
      Args : constant Asis.Expression_List :=
        Asis.Expressions.Attribute_Designator_Expressions (Attr);
   begin
      if Args'Length > 0 then
         return Evaluate (Args (1));
      else
         return Static_One;
      end if;
   end Attribute_Designator_Expression;

   ----------------
   -- Check_Zero --
   ----------------

   procedure Check_Zero (Item : Value) is
   begin
      if Item = Static_Zero then
         Raise_Error (Division_By_Zero);
      end if;
   end Check_Zero;

   -----------------
   -- Debug_Image --
   -----------------

   function Debug_Image (Item : Value) return Wide_String is
      use Ada.Characters.Handling;
   begin
      case Item.Kind is
         when Static_Discrete =>
            return "Static_Discrete:" &
              To_Wide_String (XASIS.Integers.Image (Item.Pos));
         when Static_Undefined =>
            return "Static_Undefined";
         when others =>
            return "";
      end case;
   end Debug_Image;

   --------------
   -- Evaluate --
   --------------

   function Evaluate (Element : Asis.Expression) return Value is
      Object : aliased Calculator;
   begin
      return S.Evaluate (Object'Access, Element);
   end Evaluate;

   --------------
   -- Finalize --
   --------------

   procedure Finalize (Object : in out Integer_Array_Node) is
      procedure Free is
         new Ada.Unchecked_Deallocation (Integer_Array, Integer_Array_Access);
   begin
      if Object.Data /= null then
         Free (Object.Data);
      end if;
   end Finalize;

   -----------
   -- Image --
   -----------

   function Image (Item : Value) return Wide_String is
      use Ada.Characters.Handling;
   begin
      if Item.Kind /= Static_Discrete then
         Raise_Error (Unexpected_Type);
      end if;

      return To_Wide_String (XASIS.Integers.Image (Item.Pos));
   end Image;

   --------------
   -- In_Range --
   --------------

   function In_Range
     (Item    : Value;
      Element : Asis.Definition)
      return Boolean
   is
      Object : aliased Calculator;
      Rng    : constant Static_Range :=
        S.Get_Discrete_Range (Object'Access, Element);
   begin
      return Check_Range (Object'Access, Item, Rng, False) = Static_True;
   end In_Range;

   ----------------------------
   -- Static_Range_Attribute --
   ----------------------------

   function Static_Range_Attribute
     (Attr   : Asis.Expression)
      return Static_Range
   is
      Object : aliased Calculator;
   begin
      return S.Static_Range_Attribute (Object'Access, Attr);
   end Static_Range_Attribute;

   --------------------
   -- Get_Type_Class --
   --------------------

   function Get_Type_Class
     (Info : Classes.Type_Info) return Type_Class'Class is
   begin
      if Classes.Is_Discrete (Info) then
         if Classes.Is_Integer (Info) then
            if Classes.Is_Modular_Integer (Info) then
               return Unsigned.Type_Class'(Info => Info);
            else
               return Signed.Type_Class'(Info => Info);
            end if;
         else
            return Discrete.Type_Class'(Info => Info);
         end if;
      else
         Raise_Error (Not_Implemented);
         return Get_Type_Class (Info);
      end if;
   end Get_Type_Class;

   ---------------
   -- Undefined --
   ---------------

   function Undefined return Value is
   begin
      return (Kind => Static_Undefined);
   end Undefined;

   ---------------------------------------------
   --  Static.Iter procedures inplimentation  --
   ---------------------------------------------

   -------------
   -- Literal --
   -------------

   function Literal
     (Object  : access Calculator;
      Element : in     Asis.Expression) return Value
   is
      use Asis;
      use Asis.Elements;
      use Asis.Expressions;

      Kind : constant Asis.Expression_Kinds := Expression_Kind (Element);
   begin
      case Kind is
         when An_Integer_Literal =>
            declare
               Image : Wide_String := Value_Image (Element);
               Text  : String :=
                 Ada.Characters.Handling.To_String (Image);
            begin
               return Discrete.I (XASIS.Integers.Literal (Text));
            end;
--         | A_Real_Literal
         when An_Enumeration_Literal | A_Character_Literal =>
            declare
               Name : constant Asis.Defining_Name :=
                 Corresponding_Name_Definition (Element);
               Decl : constant Asis.Declaration := Enclosing_Element (Name);
               Pos  : constant Wide_String :=
                 Asis.Declarations.Position_Number_Image (Name);
               Text : constant String :=
                 Ada.Characters.Handling.To_String (Pos);
            begin
               if Is_Part_Of_Implicit (Decl) then  --  impl defined character
                  declare
                     Img : constant Wide_String := Name_Image (Element);
                     Pos : constant Asis.ASIS_Natural :=
                       Wide_Character'Pos (Img (2));
                  begin
                     return Discrete.I (+Pos);
                  end;
               else
                  return Discrete.I (XASIS.Integers.Literal (Text));
               end if;
            end;

         when A_String_Literal =>
            declare
               use Ada.Finalization;

               function Dequote (Text : Wide_String) return Wide_String is
                  Result : Wide_String (Text'Range);
                  Last   : Natural := Result'First - 1;
                  Skip   : Boolean := False;
               begin
                  for J in Text'First + 2 .. Text'Last - 2 loop
                     if Skip then
                        Skip := False;
                     else
                        Last := Last + 1;
                        Result (Last) := Text (J);
                        Skip := Text (J) = '"';
                     end if;
                  end loop;

                  return Result (Result'First .. Last);
               end Dequote;

               Image : constant Wide_String :=
                 Dequote (Value_Image (Element));
               Text  : Integer_Array (1 .. Image'Length);
            begin
               for J in Image'Range loop
                  Text (Asis.ASIS_Positive (J)) :=
                    +Wide_Character'Pos (Image (J));
               end loop;

               return (Kind   => Static_String,
                       Lower  => XASIS.Integers.One,  --  TODO
                       Upper  => + (Text'Last),
                       String => (Controlled with new Integer_Array'(Text)));
            end;

         when others =>
            Raise_Error (Internal_Error);
            return Undefined;
      end case;
   end Literal;

   --------------
   -- Operator --
   --------------

   function Operator
     (Object  : access Calculator;
      Tipe    : in     Classes.Type_Info;
      Kind    : in     Asis.Operator_Kinds;
      Args    : in     Asis.Association_List) return Value
   is
      Switch : Type_Class'Class := Get_Type_Class (Tipe);
   begin
      return Evaluate (Switch, Kind, Args);
   end Operator;

   ---------------
   -- Attribute --
   ---------------

   function Attribute
     (Object  : access Calculator;
      Tipe    : in     Classes.Type_Info;
      Kind    : in     Asis.Attribute_Kinds;
      Element : in     Asis.Expression) return Value
   is
      Switch : Type_Class'Class := Get_Type_Class (Tipe);
   begin
      return Evaluate (Switch, Kind, Element);
   end Attribute;

   --------------------
   -- Attribute_Call --
   --------------------

   function Attribute_Call
     (Object  : access Calculator;
      Tipe    : in     Classes.Type_Info;
      Kind    : in     Asis.Attribute_Kinds;
      Args    : in     Asis.Association_List) return Value
   is
      Switch : Type_Class'Class := Get_Type_Class (Tipe);
   begin
      return Evaluate (Switch, Kind, Args);
   end Attribute_Call;

   -----------------
   -- Check_Range --
   -----------------

   function Check_Range
     (Object   : access Calculator;
      Expr     : in     Asis.Expression;
      Bounds   : in     Static_Range;
      Invert   : in     Boolean) return Value
   is
      Val : constant Value := S.Evaluate (Object, Expr);
   begin
      return Check_Range (Object, Val, Bounds, Invert);
   end Check_Range;

   -----------------
   -- Check_Range --
   -----------------

   function Check_Range
     (Object   : access Calculator;
      Val      : in     Value;
      Bounds   : in     Static_Range;
      Invert   : in     Boolean) return Value
   is
      use XASIS.Integers;
   begin
      if Discrete.Is_Discrete (Val)
        and then Discrete.Is_Discrete (Bounds (Lower))
      then
         if Val.Pos < Bounds (Lower).Pos then
            if Invert then
               return Static_True;
            else
               return Static_False;
            end if;
         elsif Discrete.Is_Discrete (Bounds (Upper)) then
            if Val.Pos <= Bounds (Upper).Pos xor Invert then
               return Static_True;
            else
               return Static_False;
            end if;
         end if;
      end if;

      return Undefined;
   end Check_Range;

   ----------------
   -- Last_Error --
   ----------------

   procedure Last_Error (Reason  : out Error_Reason) is
   begin
      Reason  := Last_Error_Reason;
   end Last_Error;

   ---------------
   -- Undefined --
   ---------------

   function Undefined
     (Object  : access Calculator;
      Element : in     Asis.Expression) return Value
   is
   begin
      return Undefined;
   end Undefined;

   -----------------
   -- Raise_Error --
   -----------------

   procedure Raise_Error (Reason  : Error_Reason) is
   begin
      Last_Error_Reason := Reason;

      raise Evaluation_Error;
   end Raise_Error;

   --------------------
   -- Range_Of_Array --
   --------------------

   function Range_Of_Array
     (Object  : access Calculator;
      Decl    : in     Asis.Declaration;
      Attr    : in     Asis.Expression) return Static_Range
   is
      Val   : constant Value := Attribute_Designator_Expression (Attr);
      Index : Asis.ASIS_Positive;
   begin
      if Discrete.Is_Discrete (Val) then
         Index := +Val;
      else
         return (Undefined, Undefined);
      end if;

      return S.Constrained_Array_Range (Object, Decl, Index);
   end Range_Of_Array;

   -------------------
   -- Range_Of_Type --
   -------------------

   function Range_Of_Type
     (Object   : access Calculator;
      Type_Def : in     Asis.Definition) return Static_Range
   is
      use Asis;
      use Asis.Definitions;
   begin
      case Asis.Elements.Type_Kind (Type_Def) is
         when An_Enumeration_Type_Definition =>
            declare
               List : constant Asis.Declaration_List :=
                 Enumeration_Literal_Declarations (Type_Def);
               Last : constant XASIS.Integers.Value := +(List'Length - 1);
            begin
               return (Static_Zero, Discrete.I (Last));
            end;

         when A_Signed_Integer_Type_Definition =>
            return (Undefined, Undefined);

         when A_Modular_Type_Definition =>
            declare
               use XASIS.Integers;

               Module : constant Asis.Expression :=
                 Mod_Static_Expression (Type_Def);
               Val    : constant Value := S.Evaluate (Object, Module);
            begin
               if Discrete.Is_Discrete (Val) then
                  return (Static_Zero, Discrete.I (Val.Pos - One));
               else
                  return (Undefined, Undefined);
               end if;
            end;

         when A_Floating_Point_Definition
           | An_Ordinary_Fixed_Point_Definition
           | A_Decimal_Fixed_Point_Definition
           =>
            return (Undefined, Undefined);

         when others =>
            Raise_Error (Internal_Error);
            return (Undefined, Undefined);
      end case;
   end Range_Of_Type;

   ---------------------------
   -- String_Constant_Range --
   ---------------------------

   function String_Constant_Range
     (Object  : access Calculator;
      Decl    : in     Asis.Declaration) return Static_Range
   is
      use XASIS.Static.Discrete;

      Val : constant Value := S.Evaluate_Static_Constant (Object, Decl);
   begin
      if Val.Kind = Static_Undefined then
         return (Undefined, Undefined);
      elsif Val.Kind = Static_String then
         return (I (Val.Lower), I (Val.Upper));
      else
         Raise_Error (Unexpected_Type);
         return (Undefined, Undefined);
      end if;
   end String_Constant_Range;

end XASIS.Static;


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
