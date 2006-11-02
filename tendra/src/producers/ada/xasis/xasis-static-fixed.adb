with Asis.Expressions;
with Asis.Definitions;
with XASIS.Static.Float;
with XASIS.Static.Discrete;

package body XASIS.Static.Fixed is
   use Asis;
   use XASIS.Integers;
   use XASIS.Fractions;
   use Asis.Expressions;

   package F renames XASIS.Fractions;
   function B (Data : Boolean) return Value renames Discrete.B;

   function Eval
     (Element : Asis.Expression;
      Object  : Type_Class) return Value;

   function Get_Small (Tipe : Classes.Type_Info) return Value;
   function Get_Delta (Tipe : Classes.Type_Info) return Value;
   function Get_Digits (Tipe : Classes.Type_Info) return Value;

   function Is_Float (Right : Value) return Boolean renames Float.Is_Float;

   ----------
   -- Eval --
   ----------

   function Eval
     (Element : Asis.Expression;
      Object  : Type_Class) return Value
   is
      Item : constant Value := Evaluate (Element);
   begin
      return V (Item, Object.Info);
   end Eval;

   --------------
   -- Evaluate --
   --------------

   function Evaluate
     (Object : Type_Class;
      Kind   : Asis.Operator_Kinds;
      Args   : Asis.Association_List)
      return Value
   is
      procedure Scale_Small
        (Left  : in out Value;
         Right : in     Value) is
      begin
         if Left.Invert_Small = Right.Invert_Small then
            Left.Small := Left.Small * Right.Small;
         elsif Left.Small >= Right.Small then
            Left.Small := Left.Small / Right.Small;
         else
            Left.Invert_Small := Right.Invert_Small;
            Left.Small := Right.Small / Left.Small;
         end if;
      end Scale_Small;

   begin
      case Kind is
         when A_Unary_Plus_Operator =>
            return Evaluate (Actual_Parameter (Args (1)));

         when A_Unary_Minus_Operator | An_Abs_Operator =>
            declare
               Item : Value :=
                 Eval (Actual_Parameter (Args (1)), Object);
            begin
               if not Is_Fixed (Item) then
                  return Undefined;
               elsif Kind = A_Unary_Minus_Operator then
                  Item.Fixed := -Item.Fixed;
                  return Item;
               else
                  Item.Fixed := abs Item.Fixed;
                  return Item;
               end if;
            end;

         when A_Multiply_Operator =>
            declare
               Left  : Value :=
                 Evaluate (Actual_Parameter (Args (1)));
               Right : Value :=
                 Evaluate (Actual_Parameter (Args (2)));
            begin
               if Is_Fixed (Left) and Is_Fixed (Right) then
                  Left.Fixed := Left.Fixed * Right.Fixed;
                  Scale_Small (Left, Right);

                  return Left;
               elsif Is_Fixed (Left) and Discrete.Is_Discrete (Right) then
                  Left.Fixed := Left.Fixed * Right.Pos;
                  return Left;
               elsif Discrete.Is_Discrete (Left) and Is_Fixed (Right) then
                  Right.Fixed := Right.Fixed * Left.Pos;
                  return Right;
               else
                  return Undefined;
               end if;
            end;

         when A_Divide_Operator =>
            declare
               Left  : Value :=
                 Evaluate (Actual_Parameter (Args (1)));
               Right : Value :=
                 Evaluate (Actual_Parameter (Args (2)));
            begin
               Check_Zero (Right);

               if Is_Fixed (Left) and Is_Fixed (Right) then
                  Left.Fixed := Left.Fixed / Right.Fixed;
                  Right.Invert_Small := not Right.Invert_Small;
                  Scale_Small (Left, Right);
                  return Left;
               elsif Is_Fixed (Left) and Discrete.Is_Discrete (Right) then
                  Left.Fixed := Left.Fixed / Right.Pos;
                  return Left;
               else
                  return Undefined;
               end if;
            end;

         when others =>
            declare
               Left  : Value :=
                 Eval (Actual_Parameter (Args (1)), Object);
               Right : Value renames
                 Eval (Actual_Parameter (Args (2)), Object);
            begin
               if Is_Fixed (Left) and Is_Fixed (Right) then
                  case Kind is
                     when A_Plus_Operator =>
                        Left.Fixed := Left.Fixed + Right.Fixed;
                        return Left;
                     when A_Minus_Operator =>
                        Left.Fixed := Left.Fixed - Right.Fixed;
                        return Left;
                     when An_Equal_Operator =>
                        return B (Left.Fixed = Right.Fixed);
                     when A_Not_Equal_Operator =>
                        return B (Left.Fixed /= Right.Fixed);
                     when A_Less_Than_Operator =>
                        return B (Left.Fixed < Right.Fixed);
                     when A_Less_Than_Or_Equal_Operator =>
                        return B (Left.Fixed <= Right.Fixed);
                     when A_Greater_Than_Operator =>
                        return B (Left.Fixed > Right.Fixed);
                     when A_Greater_Than_Or_Equal_Operator =>
                        return B (Left.Fixed >= Right.Fixed);
                     when others =>
                        null;
                  end case;
               else
                  return Undefined;
               end if;
            end;
      end case;

      Raise_Error (Internal_Error);
      return Undefined;
   end Evaluate;

   --------------
   -- Evaluate --
   --------------

   function Evaluate
     (Object : Type_Class;
      Kind   : Asis.Attribute_Kinds;
      Args   : Asis.Association_List)
      return Value
   is
   begin
      case Kind is
         when A_Round_Attribute =>
            declare
               X : Value renames Evaluate (Actual_Parameter (Args (1)));
               R : F.Fraction;
               L : I.Value;
               U : I.Value;
            begin
               if Is_Fixed (X) then
                  if X.Invert_Small then
                     R := Int (X.Fixed) / Int (X.Small);
                  else
                     return X;
                  end if;
               elsif not Is_Float (X) then
                  return Undefined;
               else
                  R := X.Fraction;
               end if;

               L := Truncate (R);

               if X.Fraction >= F.Zero then
                  U := L + I.One;
               else
                  U := L - I.One;
               end if;

               if abs (Int (L) - R) < abs (Int (U) - R) then
                  return Float.V (Int (L));
               else
                  return Float.V (Int (U));
               end if;
            end;
        when others =>
            null;
      end case;

      Raise_Error (Internal_Error);
      return Undefined;
   end Evaluate;

   --------------
   -- Evaluate --
   --------------

   function Evaluate
     (Object  : Type_Class;
      Kind    : Asis.Attribute_Kinds;
      Element : Asis.Expression)
      return Value
   is
   begin
      case Kind is
         when An_Aft_Attribute =>
            declare
               Item : Value := Get_Delta (Object.Info);
               N    : I.Value := I.One;
            begin
               if not Is_Float (Item) then
                  return Undefined;
               end if;

               while Int (I.Ten ** N) * Item.Fraction < F.One loop
                  N := N + I.One;
               end loop;

               return Discrete.I (N);
            end;
         when An_Alignment_Attribute
           | A_Fore_Attribute
           | A_Machine_Overflows_Attribute
           | A_Machine_Radix_Attribute
           | A_Machine_Rounds_Attribute
           | A_Max_Size_In_Storage_Elements_Attribute
           | A_Size_Attribute
           | A_Wide_Width_Attribute
           | A_Width_Attribute
           =>
            return Undefined;

         when A_Delta_Attribute =>
            return Get_Delta (Object.Info);

         when A_Digits_Attribute =>
            return Get_Digits (Object.Info);

         when A_First_Attribute =>
            declare
               Rng : Static_Range := Static_Range_Attribute (Element);
            begin
               return Rng (Lower);
            end;

         when A_Last_Attribute =>
            declare
               Rng : Static_Range := Static_Range_Attribute (Element);
            begin
               return Rng (Upper);
            end;

         when A_Scale_Attribute =>
            declare
               Item : Value := Get_Delta (Object.Info);
               N    : I.Value := I.Zero;
            begin
               if not Is_Float (Item) then
                  return Undefined;
               end if;

               if Item.Fraction < F.One then
                  while F.One / Int (I.Ten ** N) > Item.Fraction loop
                     N := N + I.One;
                  end loop;
               else
                  while Int (I.Ten ** N) < Item.Fraction loop
                     N := N + I.One;
                  end loop;
               end if;

               return Discrete.I (N);
            end;

         when A_Small_Attribute =>
            return Get_Digits (Object.Info);

         when others =>
            null;
      end case;

      Raise_Error (Internal_Error);
      return Undefined;
   end Evaluate;

   ---------------
   -- Get_Delta --
   ---------------

   function Get_Delta (Tipe : Classes.Type_Info) return Value is
      Def  : constant Asis.Definition := Classes.Get_Definition (Tipe);
      Delt : constant Asis.Expression :=
        Asis.Definitions.Delta_Expression (Def);
   begin
      return Evaluate (Delt);
   end Get_Delta;

   ----------------
   -- Get_Digits --
   ----------------

   function Get_Digits (Tipe : Classes.Type_Info) return Value is
      Def  : constant Asis.Definition := Classes.Get_Definition (Tipe);
      Expr : constant Asis.Expression :=
        Asis.Definitions.Digits_Expression (Def);
   begin
      return Evaluate (Expr);
   end Get_Digits;

   ---------------
   -- Get_Small --
   ---------------

   function Get_Small (Tipe : Classes.Type_Info) return Value is
      Val    : Value := Get_Delta (Tipe);
      Result : Value := (Static_Fixed, I.One, I.One, False);
   begin
      if not Is_Float (Val) then
         return Undefined;
      end if;

      if Val.Fraction < F.One then
         Result.Invert_Small := True;
         Val.Fraction := F.One / Val.Fraction;
      end if;

      if Classes.Is_Ordinary_Fixed_Point (Tipe) then
         while Int (Result.Small) < Val.Fraction loop
            Result.Small := Result.Small * I.Two;
         end loop;
      elsif Val.Fraction < F.One then
         Result.Small := Truncate (F.One / Val.Fraction);
      else
         Result.Small := Truncate (Val.Fraction);
      end if;

      return Result;
   end Get_Small;

   --------------
   -- Is_Fixed --
   --------------

   function Is_Fixed (Right : Value) return Boolean is
   begin
      return Right.Kind = Static_Fixed;
   end Is_Fixed;

   -------
   -- V --
   -------

   function V
     (Item : Value;
      Tipe : Classes.Type_Info) return Value
   is
      Small : Value := Get_Small (Tipe);
   begin
      if not Is_Fixed (Small) then
         return Undefined;
      elsif Is_Float (Item) then
         if Small.Invert_Small then
            Small.Fixed := Truncate (Item.Fraction * Int (Small.Small));
         else
            Small.Fixed := Truncate (Item.Fraction / Int (Small.Small));
         end if;

         return Small;
      elsif not Is_Fixed (Item) then
         return Undefined;
      elsif Small.Invert_Small = Item.Invert_Small
        and then Small.Small = Item.Small
      then
         return Item;
      else
         Small.Fixed := Item.Fixed;

         if Small.Invert_Small then
            Small.Fixed := Small.Fixed * Small.Small;
         end if;

         if not Item.Invert_Small then
            Small.Fixed := Small.Fixed * Item.Small;
         end if;

         if not Small.Invert_Small then
            Small.Fixed := Small.Fixed / Small.Small;
         end if;

         if Item.Invert_Small then
            Small.Fixed := Small.Fixed / Item.Small;
         end if;

         return Small;
      end if;
   end V;

end XASIS.Static.Fixed;

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
