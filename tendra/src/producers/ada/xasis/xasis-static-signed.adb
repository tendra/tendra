with Asis.Expressions;

package body XASIS.Static.Signed is

   use Asis;
   use XASIS.Integers;
   use Asis.Expressions;
   use XASIS.Static.Discrete;

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
               if not Is_Discrete (Item) then
                  return Undefined;
               elsif Kind = A_Unary_Minus_Operator then
                  return I (-Item.Pos);
               else
                  return I (abs Item.Pos);
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
                 Evaluate (Actual_Parameter (Args (1)));
               Right : Value renames
                 Evaluate (Actual_Parameter (Args (2)));
            begin
               if Is_Discrete (Left) and Is_Discrete (Right) then
                  case Kind is
                     when A_Plus_Operator =>
                        return I (Left.Pos + Right.Pos);
                     when A_Minus_Operator =>
                        return I (Left.Pos - Right.Pos);
                     when A_Multiply_Operator =>
                        return I (Left.Pos * Right.Pos);
                     when A_Divide_Operator =>
                        return I (Left.Pos / Right.Pos);
                     when A_Mod_Operator =>
                        return I (Left.Pos mod Right.Pos);
                     when A_Rem_Operator =>
                        return I (Left.Pos rem Right.Pos);
                     when An_Exponentiate_Operator =>
                        return I (Left.Pos ** Right.Pos);
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

      raise Evaluation_Error;
   end Evaluate;

end XASIS.Static.Signed;


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
