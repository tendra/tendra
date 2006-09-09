with Asis.Elements;
with Asis.Expressions;
with Asis.Declarations;

with XASIS.Types;
with XASIS.Utils;
with XASIS.Classes;

with TenDRA;
with TenDRA.Types;
with TenDRA.Output;
with TenDRA.Streams;

with Token;
with Expression;

package body Intrinsic is
   use Asis;
   use TenDRA;
   use TenDRA.Types;

   function Get_NTest
     (Oper   : Asis.Operator_Kinds;
      Invert : Boolean := False)
     return TenDRA.Types.Construct;

   -------------------
   -- Function_Call --
   -------------------

   procedure Function_Call
     (State   : access States.State;
      Element : in     Asis.Element;
      Callee  : in     Asis.Declaration;
      Static  : in     Boolean;
      B       : in out Stream'Class;
      Unit    : in     States.Unit_Kinds)
   is
      use Asis;
      use Asis.Expressions;

      procedure Output_Overflow;

      Name  : Asis.Defining_Name :=
        XASIS.Utils.Declaration_Name (Callee);
      Oper  : Asis.Operator_Kinds :=
        Asis.Elements.Operator_Kind (Name);
      Tipe  : Asis.Type_Definition :=
        Asis.Declarations.Corresponding_Type (Callee);
      Info  : XASIS.Classes.Type_Info :=
        XASIS.Classes.Type_From_Declaration
          (Asis.Elements.Enclosing_Element (Tipe));
      List  : Asis.Association_List :=
        Asis.Expressions.Function_Call_Parameters (Element, True);
      Types : array (List'Range) of XASIS.Classes.Type_Info :=
        (others => Info);

      procedure Output_Overflow is
      begin
         if Static then
            Output.TDF (B, c_continue);
         else
            Output.TDF (B, c_trap);
            Output.List_Count (B, 1);
            Output.TDF (B, c_overflow);
         end if;
      end Output_Overflow;

      procedure Each_Child (Bool_Value : Boolean := True) is
      begin
         for J in List'Range loop
            Expression.Compile
              (State, Actual_Parameter (List (J)), Types (J), Static, B, Unit);
         end loop;
      end Each_Child;

   begin
      if XASIS.Classes.Is_Signed_Integer (Info) then
         case Oper is
            when A_Plus_Operator =>
               Output.TDF (B, c_plus);
               Output_Overflow;
               Each_Child;
            when A_Minus_Operator =>
               Output.TDF (B, c_minus);
               Output_Overflow;
               Each_Child;
            when A_Unary_Plus_Operator =>
               Each_Child;
            when A_Unary_Minus_Operator =>
               Output.TDF (B, c_negate);
               Output_Overflow;
               Each_Child;
            when A_Multiply_Operator =>
               Output.TDF (B, c_mult);
               Output_Overflow;
               Each_Child;
            when A_Divide_Operator =>
               Output.TDF (B, c_div2);
               Output_Overflow;
               Output_Overflow;
               Each_Child;
            when A_Mod_Operator =>
               Output.TDF (B, c_rem1);
               Output_Overflow;
               Output_Overflow;
               Each_Child;
            when A_Rem_Operator =>
               Output.TDF (B, c_rem2);
               Output_Overflow;
               Output_Overflow;
               Each_Child;
            when An_Exponentiate_Operator =>
               Output.TDF (B, c_power);
               Output_Overflow;
               Types (2) := XASIS.Classes.T.Integer;
               Each_Child;
            when An_Abs_Operator =>
               Output.TDF (B, c_abs);
               Output_Overflow;
               Each_Child;
            when others =>
               raise States.Error;
         end case;
      else
         raise States.Error;
      end if;
   end Function_Call;

   ---------------------------
   -- Function_Call_Boolean --
   ---------------------------

   procedure Function_Call_Boolean
     (State    : access States.State;
      Element  : in     Asis.Element;
      Callee   : in     Asis.Declaration;
      Negative : in     Boolean;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use Asis;
      use Expression;
      use Asis.Expressions;

      Name  : Asis.Defining_Name :=
        Asis.Declarations.Names (Callee) (1);
      Oper  : Asis.Operator_Kinds :=
        Asis.Elements.Operator_Kind (Name);
      Tipe  : Asis.Type_Definition :=
        Asis.Declarations.Corresponding_Type (Callee);
      Info  : XASIS.Classes.Type_Info :=
        XASIS.Classes.Type_From_Declaration
          (Asis.Elements.Enclosing_Element (Tipe));
      List  : Asis.Association_List :=
        Function_Call_Parameters (Element, True);

      procedure Output_Compare_Value is
         use States;
         Tok    : TenDRA.Small := Find_Support (State, Compare_Integer_Value);
         Params : aliased Streams.Memory_Stream;
      begin
         Token.Initialize (Params, Compare_Integer_Value);
         Output.TDF (Params, Get_NTest (Oper, Negative));

         for J in List'Range loop
            Compile
              (State, Actual_Parameter (List (J)), Info, Static, Params, Unit);
         end loop;

         Output.TDF (B, c_exp_apply_token);
         Output.TDF (B, c_make_tok);
         Output.TDFINT (B, Tok);
         Output.BITSTREAM (B, Params);
      end Output_Compare_Value;

   begin
      if XASIS.Classes.Is_Boolean (Info) then
         case Oper is
            when An_And_Operator
              | An_Or_Operator =>
               if Negative then
                  if Oper = An_And_Operator then
                     Output.TDF (B, c_or);
                  else
                     Output.TDF (B, c_and);
                  end if;
               else
                  if Oper = An_And_Operator then
                     Output.TDF (B, c_and);
                  else
                     Output.TDF (B, c_or);
                  end if;
               end if;

               Compile_Boolean
                 (State,
                  Actual_Parameter (List (1)),
                  Negative, B, Unit);

               Compile_Boolean
                 (State,
                  Actual_Parameter (List (2)),
                  Negative, B, Unit);

            when An_Xor_Operator =>
               Output.TDF (B, c_xor);

               Compile_Boolean
                 (State,
                  Actual_Parameter (List (1)),
                  Negative, B, Unit);

               Compile_Boolean
                 (State,
                  Actual_Parameter (List (2)),
                  False, B, Unit);

            when An_Equal_Operator
              | A_Not_Equal_Operator =>

               if Oper = An_Equal_Operator xor Negative then
                  Invert_Boolean (State, B, Unit);
               end if;

               Output.TDF (B, c_xor);

               Compile_Boolean
                 (State, Actual_Parameter (List (1)), False, B, Unit);
               Compile_Boolean
                 (State, Actual_Parameter (List (2)), False, B, Unit);

            when A_Less_Than_Operator
              | A_Greater_Than_Or_Equal_Operator
              =>

               if Oper = A_Less_Than_Operator xor Negative then
                  Output.TDF (B, c_and);
                  Compile_Boolean
                    (State,
                     Actual_Parameter (List (1)),
                     True, B, Unit);

                  Compile_Boolean
                    (State,
                     Actual_Parameter (List (2)),
                     False, B, Unit);
               else
                  Output.TDF (B, c_or);
                  Compile_Boolean
                    (State,
                     Actual_Parameter (List (1)),
                     False, B, Unit);

                  Compile_Boolean
                    (State,
                     Actual_Parameter (List (2)),
                     True, B, Unit);
               end if;

            when A_Less_Than_Or_Equal_Operator
              | A_Greater_Than_Operator
              =>
               if Oper = A_Greater_Than_Operator xor Negative then
                  Output.TDF (B, c_and);
                  Compile_Boolean
                    (State,
                     Actual_Parameter (List (1)),
                     False, B, Unit);

                  Compile_Boolean
                    (State,
                     Actual_Parameter (List (2)),
                     True, B, Unit);
               else
                  Output.TDF (B, c_or);
                  Compile_Boolean
                    (State,
                     Actual_Parameter (List (1)),
                     True, B, Unit);

                  Compile_Boolean
                    (State,
                     Actual_Parameter (List (2)),
                     False, B, Unit);
               end if;

            when A_Not_Operator =>
               Compile_Boolean
                 (State,
                  Actual_Parameter (List (1)),
                  not Negative, B, Unit);

            when others =>
               raise States.Error;
         end case;
      else
         case Oper is
            when An_Equal_Operator
              | A_Not_Equal_Operator
              | A_Less_Than_Operator
              | A_Less_Than_Or_Equal_Operator
              | A_Greater_Than_Operator
              | A_Greater_Than_Or_Equal_Operator
              =>
               Output_Compare_Value;
            when others =>
               raise States.Error;
         end case;
      end if;
   end Function_Call_Boolean;

   ---------------------------
   -- Function_Call_Boolean --
   ---------------------------

   procedure Function_Call_Boolean
     (State    : access States.State;
      Element  : in     Asis.Element;
      Callee   : in     Asis.Declaration;
      Negative : in     Boolean;
      Label    : in     TenDRA.Small;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use Asis;
      use Expression;
      use Asis.Expressions;

      Name  : Asis.Defining_Name :=
        Asis.Declarations.Names (Callee) (1);
      Oper  : Asis.Operator_Kinds :=
        Asis.Elements.Operator_Kind (Name);
      Tipe  : Asis.Type_Definition :=
        Asis.Declarations.Corresponding_Type (Callee);
      Info  : XASIS.Classes.Type_Info :=
        XASIS.Classes.Type_From_Declaration
          (Asis.Elements.Enclosing_Element (Tipe));
      List  : Asis.Association_List :=
        Asis.Expressions.Function_Call_Parameters (Element, True);

      procedure Output_Logic_Jump (Op : TenDRA.Types.Construct) is
         use States;
         Tok    : TenDRA.Small := Find_Support (State, Boolean_Jump);
         Params : aliased Streams.Memory_Stream;
      begin
         Token.Initialize (Params, Boolean_Jump);
         Output.TDF (Params, c_make_nat);

         if Negative then
            Output.TDFINT (Params, 1);
         else
            Output.TDFINT (Params, 0);
         end if;

         Output.TDF (Params, Op);

         Compile_Boolean
           (State, Actual_Parameter (List (1)), False, Params, Unit);
         Compile_Boolean
           (State, Actual_Parameter (List (2)), False, Params, Unit);

         Output.TDF (Params, c_make_label);
         Output.TDFINT (Params, Label);
         Output.TDF (B, c_exp_apply_token);
         Output.TDF (B, c_make_tok);
         Output.TDFINT (B, Tok);
         Output.BITSTREAM (B, Params);
      end Output_Logic_Jump;

   begin
      if XASIS.Classes.Is_Boolean (Info) then
         case Oper is
            when An_And_Operator =>
               Output_Logic_Jump (c_and);

            when An_Or_Operator =>
               Output_Logic_Jump (c_or);

            when An_Xor_Operator =>
               Output_Logic_Jump (c_xor);

            when An_Equal_Operator
              | A_Not_Equal_Operator
              | A_Less_Than_Operator
              | A_Less_Than_Or_Equal_Operator
              | A_Greater_Than_Operator
              | A_Greater_Than_Or_Equal_Operator
              =>
               Output.TDF (B, c_integer_test);
               Output.No_Option (B);
               Output.TDF (B, Get_NTest (Oper, Negative));
               Output.TDF (B, c_make_label);
               Output.TDFINT (B, Label);
               Compile_Boolean
                 (State, Actual_Parameter (List (1)), False, B, Unit);
               Compile_Boolean
                 (State, Actual_Parameter (List (2)), False, B, Unit);

            when A_Not_Operator =>
               Compile_Boolean
                 (State,
                  Actual_Parameter (List (1)),
                  not Negative,
                  Label,
                  B, Unit);

            when others =>
               raise States.Error;
         end case;
      else
         case Oper is
            when An_Equal_Operator
              | A_Not_Equal_Operator
              | A_Less_Than_Operator
              | A_Less_Than_Or_Equal_Operator
              | A_Greater_Than_Operator
              | A_Greater_Than_Or_Equal_Operator
              =>
               Output.TDF (B, c_integer_test);
               Output.No_Option (B);
               Output.TDF (B, Get_NTest (Oper, Negative));
               Output.TDF (B, c_make_label);
               Output.TDFINT (B, Label);
               Compile
                 (State, Actual_Parameter (List (1)), Info, Static, B, Unit);
               Compile
                 (State, Actual_Parameter (List (2)), Info, Static, B, Unit);
            when others =>
               raise States.Error;
         end case;
      end if;
   end Function_Call_Boolean;

   ---------------
   -- Get_NTest --
   ---------------

   function Get_NTest
     (Oper   : Asis.Operator_Kinds;
      Invert : Boolean := False)
     return TenDRA.Types.Construct is
   begin
      if Invert then
         case Oper is
            when Asis.An_Equal_Operator =>
               return c_not_equal;
            when Asis.A_Not_Equal_Operator =>
               return c_equal;
            when Asis.A_Less_Than_Operator =>
               return c_not_less_than;
            when Asis.A_Less_Than_Or_Equal_Operator =>
               return c_not_less_than_or_equal;
            when Asis.A_Greater_Than_Operator =>
               return c_not_greater_than;
            when Asis.A_Greater_Than_Or_Equal_Operator =>
               return c_not_greater_than_or_equal;
            when others =>
               raise States.Error;
         end case;
      else
         case Oper is
            when Asis.An_Equal_Operator =>
               return c_equal;
            when Asis.A_Not_Equal_Operator =>
               return c_not_equal;
            when Asis.A_Less_Than_Operator =>
               return c_less_than;
            when Asis.A_Less_Than_Or_Equal_Operator =>
               return c_less_than_or_equal;
            when Asis.A_Greater_Than_Operator =>
               return c_greater_than;
            when Asis.A_Greater_Than_Or_Equal_Operator =>
               return c_greater_than_or_equal;
            when others =>
               raise States.Error;
         end case;
      end if;
   end Get_NTest;

end Intrinsic;



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
