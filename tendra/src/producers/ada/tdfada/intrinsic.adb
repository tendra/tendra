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
with Declaration;

package body Intrinsic is
   use Asis;
   use States;
   use TenDRA;
   use TenDRA.Types;

   function Get_NTest
     (Oper   : Asis.Operator_Kinds;
      Invert : Boolean := False)
     return TenDRA.Types.Construct;

   procedure Output_Overflow
     (B      : in out Stream'Class;
      Static : in     Boolean);

   -------------------
   -- Function_Call --
   -------------------

   procedure Function_Call
     (State   : access States.State;
      Element : in     Asis.Element;
      Tipe    : in     XASIS.Classes.Type_Info;
      Callee  : in     Asis.Declaration;
      Static  : in     Boolean;
      B       : in out Stream'Class;
      Unit    : in     States.Unit_Kinds)
   is
      use Asis;
      use Asis.Expressions;

      Name  : Asis.Defining_Name   := XASIS.Utils.Declaration_Name (Callee);
      Oper  : Asis.Operator_Kinds  := Asis.Elements.Operator_Kind (Name);
      List  : Asis.Association_List :=
        Asis.Expressions.Function_Call_Parameters (Element, True);
      Types : array (List'Range) of XASIS.Classes.Type_Info :=
        (others => Tipe);

      procedure Each_Child (B : in out Stream'Class) is
      begin
         for J in List'Range loop
            Expression.Compile
              (State, Actual_Parameter (List (J)), Types (J), Static, B, Unit);
         end loop;
      end Each_Child;

      procedure Mod_Oper (Kind : Support_Kinds) is
         Macro : constant Small := Find_Support (State, Kind, Unit);
         Last  : constant Small := Find_Type_Param (State, Tipe, Upper, Unit);
         Var   : Small := States.Find_Variety (State, Tipe, Unit);
         Param : Streams.Memory_Stream;
      begin
         Token.Initialize (Param, Kind);
         Each_Child (Param);

         Output.TDF (Param, c_exp_apply_token);
         Output.TDF (Param, c_make_tok);
         Output.TDFINT (Param, Last);
         Output.BITSTREAM (Param, Empty);

         Output.TDF (Param, c_var_apply_token);
         Output.TDF (Param, c_make_tok);
         Output.TDFINT (Param, Var);
         Output.BITSTREAM (Param, Empty);

         if Kind = Mod_Power then
            Var := States.Find_Variety (State, Types (2), Unit);

            Output.TDF (Param, c_var_apply_token);
            Output.TDF (Param, c_make_tok);
            Output.TDFINT (Param, Var);
            Output.BITSTREAM (Param, Empty);
         end if;

         Output.TDF (B, c_exp_apply_token);
         Output.TDF (B, c_make_tok);
         Output.TDFINT (B, Macro);
         Output.BITSTREAM (B, Param);
      end Mod_Oper;

      procedure Static_Mod_Oper (Kind : Construct) is
         Tok : constant Small := Find_Attribute
           (State, XASIS.Classes.Get_Declaration (Tipe),
            A_Modulus_Attribute, Unit);
      begin
         Output.TDF (B, c_rem1);
         Output.TDF (B, c_impossible);
         Output.TDF (B, c_impossible);

         Output.TDF (B, Kind);

         if Kind = c_and or Kind = c_or or Kind = c_xor or Kind = C_Not then
            null;
         elsif Kind = c_div2 or Kind = c_rem2 or Kind = c_rem1 then
            Output_Overflow (B, Static);
            Output_Overflow (B, Static);
         else
            Output_Overflow (B, Static);
         end if;

         Each_Child (B);

         Output.TDF (B, c_exp_apply_token);
         Output.TDF (B, c_make_tok);
         Output.TDFINT (B, Tok);
         Output.BITSTREAM (B, Empty);
      end Static_Mod_Oper;

      procedure Fix_Types is
         Profile : constant Asis.Parameter_Specification_List :=
           XASIS.Utils.Get_Profile (Callee);
         Info    : XASIS.Classes.Type_Info;
         Expr    : Asis.Expression;
         Decl    : Asis.Declaration;
      begin
         for J in Profile'Range loop
            Info := XASIS.Classes.Type_Of_Declaration (Profile (J));

            if XASIS.Classes.Is_Universal (Info) then
               Expr := Actual_Parameter (List (J));
               Decl := Asis.Expressions.Corresponding_Expression_Type (Expr);
               Info := XASIS.Classes.Type_From_Declaration (Decl);

               if XASIS.Classes.Is_Universal (Info) then
                  Info := Tipe;
               end if;
            end if;

            Types (J) := Info;
         end loop;
      end Fix_Types;

   begin
      if XASIS.Classes.Is_Signed_Integer (Tipe) then
         case Oper is
            when A_Plus_Operator =>
               Output.TDF (B, c_plus);
               Output_Overflow (B, Static);
               Each_Child (B);
            when A_Minus_Operator =>
               Output.TDF (B, c_minus);
               Output_Overflow (B, Static);
               Each_Child (B);
            when A_Unary_Plus_Operator =>
               Each_Child (B);
            when A_Unary_Minus_Operator =>
               Output.TDF (B, c_negate);
               Output_Overflow (B, Static);
               Each_Child (B);
            when A_Multiply_Operator =>
               Output.TDF (B, c_mult);
               Output_Overflow (B, Static);
               Each_Child (B);
            when A_Divide_Operator =>
               Output.TDF (B, c_div2);
               Output_Overflow (B, Static);
               Output_Overflow (B, Static);
               Each_Child (B);
            when A_Mod_Operator =>
               Output.TDF (B, c_rem1);
               Output_Overflow (B, Static);
               Output_Overflow (B, Static);
               Each_Child (B);
            when A_Rem_Operator =>
               Output.TDF (B, c_rem2);
               Output_Overflow (B, Static);
               Output_Overflow (B, Static);
               Each_Child (B);
            when An_Exponentiate_Operator =>
               Output.TDF (B, c_power);
               Output_Overflow (B, Static);
               Types (2) := XASIS.Classes.T.Integer;
               Each_Child (B);
            when An_Abs_Operator =>
               Output.TDF (B, c_abs);
               Output_Overflow (B, Static);
               Each_Child (B);
            when others =>
               raise States.Error;
         end case;

      elsif XASIS.Classes.Is_Float_Point (Tipe) then
         case Oper is
            when A_Plus_Operator =>
               Output.TDF (B, c_floating_plus);
               Output_Overflow (B, Static);
               Output.List_Count (B, 2);
               Each_Child (B);
            when A_Minus_Operator =>
               Output.TDF (B, c_floating_minus);
               Output_Overflow (B, Static);
               Each_Child (B);
            when A_Unary_Plus_Operator =>
               Each_Child (B);
            when A_Unary_Minus_Operator =>
               Output.TDF (B, c_floating_negate);
               Output_Overflow (B, Static);
               Each_Child (B);
            when A_Multiply_Operator =>
               Output.TDF (B, c_floating_mult);
               Output_Overflow (B, Static);
               Output.List_Count (B, 2);
               Each_Child (B);
            when A_Divide_Operator =>
               Output.TDF (B, c_floating_div);
               Output_Overflow (B, Static);
               Each_Child (B);
            when An_Exponentiate_Operator =>
               Output.TDF (B, c_floating_power);
               Output_Overflow (B, Static);
               Types (2) := XASIS.Classes.T.Integer;
               Each_Child (B);
            when An_Abs_Operator =>
               Output.TDF (B, c_floating_abs);
               Output_Overflow (B, Static);
               Each_Child (B);
            when others =>
               raise States.Error;
         end case;

      elsif XASIS.Classes.Is_Fixed_Point (Tipe) then
         case Oper is
            when A_Plus_Operator =>
               Output.TDF (B, c_plus);
               Output_Overflow (B, Static);
               Each_Child (B);
            when A_Minus_Operator =>
               Output.TDF (B, c_minus);
               Output_Overflow (B, Static);
               Each_Child (B);
            when A_Unary_Plus_Operator =>
               Each_Child (B);
            when A_Unary_Minus_Operator =>
               Output.TDF (B, c_negate);
               Output_Overflow (B, Static);
               Each_Child (B);
            when A_Multiply_Operator | A_Divide_Operator =>
               declare
                  Param : Streams.Memory_Stream;
                  Macro : Small;
               begin
                  if Oper = A_Multiply_Operator then
                     Macro := Find_Support (State, Fixed_Multiply, Unit);
                     Token.Initialize (Param, Fixed_Multiply);
                  else
                     Macro := Find_Support (State, Fixed_Divide, Unit);
                     Token.Initialize (Param, Fixed_Divide);
                  end if;

                  Fix_Types;
                  Each_Child (Param);
                  Declaration.Output_Variety (State, Tipe, Param, Unit);

                  Expression.Apply_Type_Param
                    (State, Types (1), Param, Unit, Base_Upper);

                  Expression.Apply_Type_Param
                    (State, Types (2), Param, Unit, Base_Upper);

                  Expression.Apply_Attribute
                    (State, Types (1), Param, Unit, A_Small_Attribute);

                  if XASIS.Classes.Is_Fixed_Point (Types (2)) then
                     Expression.Apply_Attribute
                       (State, Types (2), Param, Unit, A_Small_Attribute);
                  else
                     Output.TDF (Param, c_make_floating);
                     Expression.Output_Universal_Variety
                       (State, XASIS.Classes.T.Root_Real, Param, Unit);
                     Output.TDF (Param, c_to_nearest);
                     Output.TDF (Param, c_false);
                     Output.TDF (Param, c_make_string);
                     Output.TDFSTRING (Param, "1");
                     Output.TDF (Param, c_make_nat);
                     Output.TDFINT (Param, 10);
                     Expression.Output_Signed_Nat (Param, 0);
                  end if;

                  Expression.Apply_Attribute
                    (State, Tipe, Param, Unit, A_Small_Attribute);

                  Output_Overflow (Param, Static);

                  Output.TDF (B, c_exp_apply_token);
                  Output.TDF (B, c_make_tok);
                  Output.TDFINT (B, Macro);
                  Output.BITSTREAM (B, Param);
               end;
            when An_Exponentiate_Operator =>
               Output.TDF (B, c_floating_power);
               Output_Overflow (B, Static);
               Types (2) := XASIS.Classes.T.Integer;
               Each_Child (B);
            when An_Abs_Operator =>
               Output.TDF (B, c_abs);
               Output_Overflow (B, Static);
               Each_Child (B);
            when others =>
               raise States.Error;
         end case;

      elsif XASIS.Classes.Is_Modular_Integer (Tipe) then
         if Static then
            case Oper is
               when A_Plus_Operator =>
                  Static_Mod_Oper (c_plus);
               when A_Minus_Operator =>
                  Static_Mod_Oper (c_minus);
               when A_Unary_Plus_Operator =>
                  Each_Child (B);
               when A_Unary_Minus_Operator =>
                  Static_Mod_Oper (c_negate);
               when A_Multiply_Operator =>
                  Static_Mod_Oper (c_mult);
               when A_Divide_Operator =>
                  Static_Mod_Oper (c_div2);
               when A_Mod_Operator =>
                  Static_Mod_Oper (c_rem1);
               when A_Rem_Operator =>
                  Static_Mod_Oper (c_rem2);
               when An_Exponentiate_Operator =>
                  Types (2) := XASIS.Classes.T.Integer;
                  Static_Mod_Oper (c_power);
               when An_Abs_Operator =>
                  Each_Child (B);
               when An_And_Operator =>
                  Static_Mod_Oper (c_and);
               when An_Or_Operator =>
                  Static_Mod_Oper (c_or);
               when An_Xor_Operator =>
                  Static_Mod_Oper (c_xor);
               when A_Not_Operator =>
                  Static_Mod_Oper (c_not);
               when others =>
                  raise States.Error;
            end case;
         else
            case Oper is
               when A_Plus_Operator =>
                  Mod_Oper (Mod_Plus);
               when A_Minus_Operator =>
                  Mod_Oper (Mod_Minus);
               when A_Unary_Plus_Operator =>
                  Each_Child (B);
               when A_Unary_Minus_Operator =>
                  Mod_Oper (Mod_Negative);
               when A_Multiply_Operator =>
                  Mod_Oper (Mod_Multiply);
               when A_Divide_Operator =>
                  Output.TDF (B, c_div2);
                  Output_Overflow (B, Static);
                  Output_Overflow (B, Static);
                  Each_Child (B);
               when A_Mod_Operator =>
                  Output.TDF (B, c_rem1);
                  Output_Overflow (B, Static);
                  Output_Overflow (B, Static);
                  Each_Child (B);
               when A_Rem_Operator =>
                  Output.TDF (B, c_rem2);
                  Output_Overflow (B, Static);
                  Output_Overflow (B, Static);
                  Each_Child (B);
               when An_Exponentiate_Operator =>
                  Types (2) := XASIS.Classes.T.Integer;
                  Mod_Oper (Mod_Power);
               when An_Abs_Operator =>
                  Each_Child (B);
               when An_And_Operator =>
                  Mod_Oper (Mod_And);
               when An_Or_Operator =>
                  Mod_Oper (Mod_Or);
               when An_Xor_Operator =>
                  Mod_Oper (Mod_Xor);
               when A_Not_Operator =>
                  Mod_Oper (Mod_Not);
               when others =>
                  raise States.Error;
            end case;
         end if;
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
         Tok    : TenDRA.Small;
         Params : Streams.Memory_Stream;
      begin
         if XASIS.Classes.Is_Float_Point (Info) then
            Tok := Find_Support (State, Compare_Float_Value, Unit);
         else
            Tok := Find_Support (State, Compare_Integer_Value, Unit);
         end if;

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
         Tok    : TenDRA.Small := Find_Support (State, Boolean_Jump, Unit);
         Params : Streams.Memory_Stream;
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
               if XASIS.Classes.Is_Float_Point (Info) then
                  Output.TDF (B, c_floating_test);
                  Output.No_Option (B);
                  Output_Overflow (B, Static);
               else
                  Output.TDF (B, c_integer_test);
                  Output.No_Option (B);
               end if;

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

   ---------------------
   -- Output_Overflow --
   ---------------------

   procedure Output_Overflow
     (B      : in out Stream'Class;
      Static : in     Boolean) is
   begin
      if Static then
         Output.TDF (B, c_impossible);
      else
         Output.TDF (B, c_trap);
         Output.List_Count (B, 1);
         Output.TDF (B, c_overflow);
      end if;
   end Output_Overflow;

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
