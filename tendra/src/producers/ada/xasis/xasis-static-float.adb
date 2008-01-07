with Asis.Expressions;
with Asis.Definitions;
with XASIS.Static.Discrete;

package body XASIS.Static.Float is
   use Asis;
   use XASIS.Integers;
   use XASIS.Fractions;
   use Asis.Expressions;

   package F renames XASIS.Fractions;
   function B (Data : Boolean) return Value renames Discrete.B;

   --------------
   -- Evaluate --
   --------------

   function Evaluate
     (Object : Type_Class;
      Kind   : Asis.Operator_Kinds;
      Args   : Asis.Association_List)
      return Value
   is
   begin
      case Kind is
         when A_Unary_Plus_Operator =>
            return Evaluate (Actual_Parameter (Args (1)));

         when A_Unary_Minus_Operator | An_Abs_Operator =>
            declare
               Item : Value renames
                 Evaluate (Actual_Parameter (Args (1)));
            begin
               if not Is_Float (Item) then
                  return Undefined;
               elsif Kind = A_Unary_Minus_Operator then
                  return V (-Item.Fraction);
               else
                  return V (abs Item.Fraction);
               end if;
            end;

         when others =>
            declare
               Left  : Value renames
                 Evaluate (Actual_Parameter (Args (1)));
               Right : Value renames
                 Evaluate (Actual_Parameter (Args (2)));
            begin
               if Is_Float (Left) and Is_Float (Right) then
                  case Kind is
                     when A_Plus_Operator =>
                        return V (Left.Fraction + Right.Fraction);
                     when A_Minus_Operator =>
                        return V (Left.Fraction - Right.Fraction);
                     when A_Multiply_Operator =>
                        return V (Left.Fraction * Right.Fraction);
                     when A_Divide_Operator =>
                        Check_Zero (Right);
                        return V (Left.Fraction / Right.Fraction);
                     when An_Equal_Operator =>
                        return B (Left.Fraction = Right.Fraction);
                     when A_Not_Equal_Operator =>
                        return B (Left.Fraction /= Right.Fraction);
                     when A_Less_Than_Operator =>
                        return B (Left.Fraction < Right.Fraction);
                     when A_Less_Than_Or_Equal_Operator =>
                        return B (Left.Fraction <= Right.Fraction);
                     when A_Greater_Than_Operator =>
                        return B (Left.Fraction > Right.Fraction);
                     when A_Greater_Than_Or_Equal_Operator =>
                        return B (Left.Fraction >= Right.Fraction);
                     when others =>
                        null;
                  end case;
               elsif Is_Float (Left) and Discrete.Is_Discrete (Right) then
                  case Kind is
                     when A_Multiply_Operator =>
                        return V (Left.Fraction * Int (Right.Pos));
                     when A_Divide_Operator =>
                        Check_Zero (Right);
                        return V (Left.Fraction / Int (Right.Pos));
                     when An_Exponentiate_Operator =>
                        return V (Left.Fraction ** Right.Pos);
                     when others =>
                        null;
                  end case;
               elsif Discrete.Is_Discrete (Left) and Is_Float (Right) then
                  case Kind is
                     when A_Multiply_Operator =>
                        return V (Int (Left.Pos) * Right.Fraction);
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
         when An_Adjacent_Attribute
           | A_Copy_Sign_Attribute
           | A_Max_Attribute
           | A_Min_Attribute
           | A_Remainder_Attribute
           =>
            declare
               L : Value renames Evaluate (Actual_Parameter (Args (1)));
               R : Value renames Evaluate (Actual_Parameter (Args (2)));
            begin
               if Is_Float (L) and Is_Float (R) then
                  case Kind is
                     when An_Adjacent_Attribute =>
                        if L.Fraction = R.Fraction then
                           return L;
                        else
                           return Undefined;
                        end if;

                     when A_Copy_Sign_Attribute =>
                        if L.Fraction = F.Zero then
                           return L;
                        elsif L.Fraction < F.Zero xor R.Fraction < F.Zero then
                           return V (-L.Fraction);
                        else
                           return L;
                        end if;

                     when A_Max_Attribute =>
                        if L.Fraction < R.Fraction then
                           return R;
                        else
                           return L;
                        end if;

                     when A_Min_Attribute =>
                        if L.Fraction > R.Fraction then
                           return R;
                        else
                           return L;
                        end if;

                     when A_Remainder_Attribute =>
                        declare
                           D   : constant F.Fraction :=
                             L.Fraction / R.Fraction;
                           N   : I.Value := Truncate (D);
                           A   : constant F.Fraction :=
                             Int (I.Two) * abs (Int (N) - D);
                        begin
                           if A = F.One then
                              if N mod I.Two = I.One then
                                 if N > I.Zero then
                                    N := N + I.One;
                                 else
                                    N := N - I.One;
                                 end if;
                              end if;
                           elsif A > F.One then
                              if N > I.Zero then
                                 N := N + I.One;
                              else
                                 N := N - I.One;
                              end if;
                           end if;

                           return V (L.Fraction - Int (N) * R.Fraction);
                        end;

                     when others =>
                        null;
                  end case;
               else
                  return Undefined;
               end if;
            end;

         when A_Ceiling_Attribute
           | A_Floor_Attribute
           | A_Rounding_Attribute
           | A_Truncation_Attribute
           | An_Unbiased_Rounding_Attribute
           =>
            declare
               X : Value renames Evaluate (Actual_Parameter (Args (1)));
            begin
               if not Is_Float (X) then
                  return Undefined;
               end if;

               case Kind is
                  when A_Ceiling_Attribute =>
                     declare
                        T : constant F.Fraction := Int (Truncate (X.Fraction));
                     begin
                        if X.Fraction = T then
                           return X;
                        elsif X.Fraction > F.Zero then
                           return V (T + F.One);
                        else
                           return V (T);
                        end if;
                     end;

                  when A_Floor_Attribute =>
                     declare
                        T : constant F.Fraction := Int (Truncate (X.Fraction));
                     begin
                        if X.Fraction = T then
                           return X;
                        elsif X.Fraction < F.Zero then
                           return V (T - F.One);
                        else
                           return V (T);
                        end if;
                     end;

                  when A_Rounding_Attribute =>
                     declare
                        R : constant F.Fraction := X.Fraction;
                        L : constant I.Value := Truncate (R);
                        U : I.Value;
                     begin
                        if X.Fraction >= F.Zero then
                           U := L + I.One;
                        else
                           U := L - I.One;
                        end if;

                        if abs (Int (L) - R) < abs (Int (U) - R) then
                           return V (Int (L));
                        else
                           return V (Int (U));
                        end if;
                     end;

                  when A_Truncation_Attribute =>
                     return V (Int (Truncate (X.Fraction)));

                  when An_Unbiased_Rounding_Attribute =>
                     declare
                        R : constant F.Fraction := X.Fraction;
                        L : constant I.Value := Truncate (R);
                        U : I.Value;
                     begin
                        if X.Fraction >= F.Zero then
                           U := L + I.One;
                        else
                           U := L - I.One;
                        end if;

                        if abs (Int (L) - R) = abs (Int (U) - R) then
                           if L mod I.Two = I.Zero then
                              return V (Int (L));
                           else
                              return V (Int (U));
                           end if;
                        elsif abs (Int (L) - R) < abs (Int (U) - R) then
                           return V (Int (L));
                        else
                           return V (Int (U));
                        end if;
                     end;

                  when others =>
                     null;
               end case;
            end;

         when A_Compose_Attribute  --  depend on unknown S'Machine_Radix
           | An_Exponent_Attribute
           | A_Fraction_Attribute
           | A_Leading_Part_Attribute
           | A_Machine_Attribute
           | A_Machine_Rounding_Attribute
           | A_Model_Attribute
           | A_Pred_Attribute
           | A_Succ_Attribute
           | A_Scaling_Attribute
           =>
            return Undefined;

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
         when An_Alignment_Attribute
           | A_Denorm_Attribute
           | A_Machine_Emax_Attribute
           | A_Machine_Emin_Attribute
           | A_Machine_Mantissa_Attribute
           | A_Machine_Overflows_Attribute
           | A_Machine_Radix_Attribute
           | A_Machine_Rounds_Attribute
           | A_Max_Size_In_Storage_Elements_Attribute
           | A_Model_Emin_Attribute
           | A_Model_Epsilon_Attribute
           | A_Model_Mantissa_Attribute
           | A_Model_Small_Attribute
           | A_Safe_First_Attribute
           | A_Safe_Last_Attribute
           | A_Signed_Zeros_Attribute
           | A_Size_Attribute
           | A_Stream_Size_Attribute
           | A_Wide_Wide_Width_Attribute
           | A_Wide_Width_Attribute
           | A_Width_Attribute
           =>
            return Undefined;

         when A_Digits_Attribute =>
            declare
               use Asis.Definitions;

               Def : constant Asis.Definition :=
                 Classes.Get_Definition (Object.Info);
            begin
               return Evaluate (Digits_Expression (Def));
            end;

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

         when others =>
            null;
      end case;

      Raise_Error (Internal_Error);
      return Undefined;
   end Evaluate;

   -------
   -- V --
   -------

   function V (Data : F.Fraction) return Value is
   begin
      return (Static_Float, Data);
   end V;

   --------------
   -- Is_Float --
   --------------

   function Is_Float (Right : Value) return Boolean is
   begin
      return Right.Kind = Static_Float;
   end Is_Float;

end XASIS.Static.Float;

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
