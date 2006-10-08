with Asis.Expressions;

package body XASIS.Static.Discrete is

   use Asis;
   use XASIS.Integers;
   use Asis.Expressions;

   -----------------
   -- Is_Discrete --
   -----------------

   function Is_Discrete (Right : Value) return Boolean is
   begin
      case Right.Kind is
         when Static_Discrete =>
            return True;
         when Static_Undefined =>
            return False;
         when others =>
            Raise_Error (Unexpected_Type);
            return False;
      end case;
   end Is_Discrete;

   -------
   -- B --
   -------

   function B (Data : Boolean) return Value is
   begin
      if Data then
         return Static_True;
      else
         return Static_False;
      end if;
   end B;

   -------
   -- I --
   -------

   function I (Data : XASIS.Integers.Value) return Value is
   begin
      return (Static_Discrete, Data);
   end I;

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

         when A_Unary_Minus_Operator | An_Abs_Operator | A_Not_Operator =>
            declare
               Item : Value renames
                 Evaluate (Actual_Parameter (Args (1)));
            begin
               if not Is_Discrete (Item) then
                  return Undefined;
               elsif Kind = A_Unary_Minus_Operator then
                  return I (-Item.Pos);
               elsif Kind = An_Abs_Operator then
                  return I (abs Item.Pos);
               else
                  return B (Item.Pos = Zero);
               end if;
            end;

         when others =>
            declare
               Left  : Value renames
                 Evaluate (Actual_Parameter (Args (1)));
               Right : Value renames
                 Evaluate (Actual_Parameter (Args (2)));
            begin
               if Is_Discrete (Left) and Is_Discrete (Right) then
                  case Kind is
                     when An_And_Operator =>
                        return I (Left.Pos and Right.Pos);
                     when An_Or_Operator =>
                        return I (Left.Pos or Right.Pos);
                     when An_Xor_Operator =>
                        return I (Left.Pos xor Right.Pos);
                     when An_Equal_Operator =>
                        return B (Left.Pos = Right.Pos);
                     when A_Not_Equal_Operator =>
                        return B (Left.Pos /= Right.Pos);
                     when A_Less_Than_Operator =>
                        return B (Left.Pos < Right.Pos);
                     when A_Less_Than_Or_Equal_Operator =>
                        return B (Left.Pos <= Right.Pos);
                     when A_Greater_Than_Operator =>
                        return B (Left.Pos > Right.Pos);
                     when A_Greater_Than_Or_Equal_Operator =>
                        return B (Left.Pos >= Right.Pos);
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
         when A_Pos_Attribute
           | A_Pred_Attribute
           | A_Succ_Attribute
           | A_Val_Attribute =>
            declare
               Item : Value renames
                 Evaluate (Actual_Parameter (Args (1)));
            begin
               if not Is_Discrete (Item) then
                  return Undefined;
               end if;

               case Kind is
                  when A_Pos_Attribute | A_Val_Attribute =>
                     return Item;
                  when A_Pred_Attribute =>
                     return I (Item.Pos - One);
                  when A_Succ_Attribute =>
                     return I (Item.Pos + One);
                  when others =>
                     null;
               end case;
            end;

         when A_Max_Attribute | A_Min_Attribute =>
            declare
               Left  : Value renames
                 Evaluate (Actual_Parameter (Args (1)));
               Right : Value renames
                 Evaluate (Actual_Parameter (Args (2)));
            begin
               if Is_Discrete (Left) and Is_Discrete (Right) then
                  case Kind is
                     when A_Max_Attribute =>
                        if Left.Pos > Right.Pos then
                           return Left;
                        else
                           return Right;
                        end if;
                     when A_Min_Attribute =>
                        if Left.Pos < Right.Pos then
                           return Left;
                        else
                           return Right;
                        end if;
                     when others =>
                        null;
                  end case;
               else
                  return Undefined;
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
      if not Classes.Is_Declaration (Object.Info)
        and Kind /= A_First_Attribute
        and Kind /= A_Last_Attribute
        and Kind /= A_Length_Attribute
      then
         Raise_Error (Internal_Error);
      end if;

      case Kind is
         when An_Alignment_Attribute
           | A_Max_Size_In_Storage_Elements_Attribute
           | A_Size_Attribute
           | A_Wide_Width_Attribute
           | A_Width_Attribute
           =>
            return Undefined;

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

end XASIS.Static.Discrete;


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
