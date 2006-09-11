with Asis.Definitions;
with Asis.Expressions;

package body XASIS.Static.Unsigned is

   use Asis;
   use XASIS.Integers;
   use Asis.Expressions;
   use XASIS.Static.Discrete;

   function Modulus (Object : Type_Class) return Value;

   function U
     (Data   : XASIS.Integers.Value;
      Object : Type_Class) return Value;

   function Eval
     (Element : Asis.Expression;
      Object  : Type_Class) return Value;

   ----------
   -- Eval --
   ----------

   function Eval
     (Element : Asis.Expression;
      Object  : Type_Class) return Value
   is
      Module : Value renames Modulus (Object);
      Item   : Value renames Evaluate (Element);
   begin
      if Is_Discrete (Module)
        and then Is_Discrete (Item)
        and then Item.Pos >= Module.Pos
      then
         Raise_Error (Exceed_Modulus);
      end if;

      return Item;
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
   begin
      case Kind is
         when A_Unary_Plus_Operator | An_Abs_Operator =>
            return Eval (Actual_Parameter (Args (1)), Object);

         when A_Unary_Minus_Operator | A_Not_Operator =>
            declare
               Item : Value renames
                 Eval (Actual_Parameter (Args (1)), Object);
            begin
               if not Is_Discrete (Item) then
                  return Undefined;
               elsif Kind = A_Unary_Minus_Operator then
                  return U (-Item.Pos, Object);
               else
                  return U (-Item.Pos - One, Object);
               end if;
            end;

         when A_Plus_Operator
           | A_Minus_Operator
           | A_Multiply_Operator
           | A_Divide_Operator
           | A_Mod_Operator
           | A_Rem_Operator
           | An_Exponentiate_Operator
           =>
            declare
               Left  : Value renames
                 Eval (Actual_Parameter (Args (1)), Object);
               Right : Value renames
                 Eval (Actual_Parameter (Args (2)), Object);
            begin
               if Is_Discrete (Left) and Is_Discrete (Right) then
                  case Kind is
                     when A_Plus_Operator =>
                        return U (Left.Pos + Right.Pos, Object);
                     when A_Minus_Operator =>
                        return U (Left.Pos - Right.Pos, Object);
                     when A_Multiply_Operator =>
                        return U (Left.Pos * Right.Pos, Object);
                     when A_Divide_Operator =>
                        Check_Zero (Right);
                        return U (Left.Pos / Right.Pos, Object);
                     when A_Mod_Operator =>
                        Check_Zero (Right);
                        return U (Left.Pos mod Right.Pos, Object);
                     when A_Rem_Operator =>
                        Check_Zero (Right);
                        return U (Left.Pos rem Right.Pos, Object);
                     when An_Exponentiate_Operator =>
                        return U (Left.Pos ** Right.Pos, Object);
                     when others =>
                        null;
                  end case;
               else
                  return Undefined;
               end if;
            end;

         when others =>
            return Evaluate (Discrete.Type_Class (Object), Kind, Args);
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
      Element : Asis.Expression) return Value is
   begin
      case Kind is
         when A_Modulus_Attribute =>
            return Modulus (Object);

         when others =>
            return Evaluate (Discrete.Type_Class (Object), Kind, Element);
      end case;
   end Evaluate;

   -------------
   -- Modulus --
   -------------

   function Modulus (Object : Type_Class) return Value is
      use Asis.Definitions;

      Def : constant Asis.Definition := Classes.Get_Definition (Object.Info);
   begin
      return Evaluate (Mod_Static_Expression (Def));
   end Modulus;

   -------
   -- U --
   -------

   function U
     (Data   : XASIS.Integers.Value;
      Object : Type_Class) return Value
   is
      Module : Value renames Modulus (Object);
   begin
      if Is_Discrete (Module) then
         return I (Data mod Module.Pos);
      else
         return Undefined;
      end if;
   end U;

end XASIS.Static.Unsigned;


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
