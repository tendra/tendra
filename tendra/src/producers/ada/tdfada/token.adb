with Asis;

with States;
with TenDRA;
with TenDRA.Types;
with TenDRA.Output;
with TenDRA.Streams;
with XASIS.Classes;

package body Token is

   Error : exception;

   ----------------
   -- Initialize --
   ----------------

   procedure Initialize
     (Stream : in out TenDRA.Streams.Memory_Stream;
      Kind   : in     States.Support_Kinds)
   is
      use States;
      use TenDRA;
      use TenDRA.Types;
   begin
      case Kind is
         when Compare_Integer_Value | Compare_Float_Value =>
            Streams.Expect (Stream, Dummy,
                            ((NTEST_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False)));
         when Boolean_Jump =>
            Streams.Expect (Stream, Dummy,
                            ((NAT_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (LABEL_SORT, Singular, False)));
         when Constraint_Error_If =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (LABEL_SORT, Singular, False)));
         when Enum_Succ_Pred_Attr =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False),
                             (NAT_SORT, Singular, False)));
         when Signed_Succ_Pred_Attr =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False),
                             (NAT_SORT, Singular, False)));
         when Enum_Val_Attr =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False)));
         when Signed_Val_Attr =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False)));
         when Signed_Base_Lower | Signed_Base_Upper =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False)));
         when Mod_Plus | Mod_Minus | Mod_Multiply
           | Mod_Or | Mod_Xor | Mod_And =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False)));
         when Mod_Power =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False)));
         when Mod_Not | Mod_Negative =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (VARIETY_SORT, Singular, False)));
         when Test_Range_Jump =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (NAT_SORT, Singular, False),
                             (LABEL_SORT, Singular, False)));
         when Make_Float_Id =>
            Streams.Expect (Stream, Dummy,
                            (1 => (EXP_SORT, Singular, False)));
         when Make_Float_Range_Id =>
            Streams.Expect (Stream, Dummy,
                            ((EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False)));
         when Rep_Fv | Rep_Fv_Max_Val 
           | Make_Float_Attr =>
            Streams.Expect (Stream, Dummy,
                            (1 => (NAT_SORT, Singular, False)));
         when Make_Float_Attr_1 =>
            Streams.Expect (Stream, Dummy,
                            ((NAT_SORT, Singular, False),
                             (EXP_SORT, Singular, False)));
         when Make_Float_Attr_2 =>
            Streams.Expect (Stream, Dummy,
                            ((NAT_SORT, Singular, False),
                             (EXP_SORT, Singular, False),
                             (EXP_SORT, Singular, False)));
      end case;
   end Initialize;

   ---------------
   -- New_Token --
   ---------------

   procedure New_Token
     (State : access States.State;
      Link  : in     States.Linkage_Access)
   is
      use States;
      use TenDRA;
      use TenDRA.Types;

      Decl : Linkage_Access;
      O    : Streams.Memory_Stream renames State.Units (TOKDEC).all;
   begin
      Link.Usage := Link.Usage or Declared;

      Decl := Find (State, Link.all, TOKDEC);
      Output.TDF (O, c_make_tokdec);
      Output.TDFINT (O, Decl.Unit_Code (TOKDEC));
      Output.No_Option (O);
      Inc (State.Length (TOKDEC));

      case Link.Kind is
         when Shape_Token =>
            Output.TDF (O, c_shape);

         when Variety_Token =>
            if XASIS.Classes.Is_Scalar (Link.Tipe) then
               if XASIS.Classes.Is_Discrete (Link.Tipe) then
                  Output.TDF (O, c_variety);
               else
                  Output.TDF (O, c_floating_variety);
               end if;
            else
               raise Error;
            end if;

         when Name_Token | Value_Token =>
            Output.TDF (O, c_exp);

         when Type_Param_Token =>
            case Link.Param is
               when Float_Id =>
                  Output.TDF (O, c_nat);
               when Lower | Upper | Base_Lower | Base_Upper =>
                  Output.TDF (O, c_exp);
            end case;

         when Support_Token =>
            case Link.Support is
               when Compare_Integer_Value | Compare_Float_Value =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 3);
                  Output.TDF (O, c_ntest);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);

               when Boolean_Jump =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 3);
                  Output.TDF (O, c_nat);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_label);

               when Constraint_Error_If =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 2);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_label);

               when Enum_Succ_Pred_Attr =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 4);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);
                  Output.TDF (O, c_nat);

               when Signed_Succ_Pred_Attr =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 3);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);
                  Output.TDF (O, c_nat);

               when Enum_Val_Attr =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 4);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);

               when Signed_Val_Attr =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 2);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);

               when Signed_Base_Lower | Signed_Base_Upper =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 3);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);

               when Mod_Plus | Mod_Minus | Mod_Multiply
                 | Mod_Or | Mod_Xor | Mod_And =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 4);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);

               when Mod_Power =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 5);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);
                  Output.TDF (O, c_variety);

               when Mod_Not | Mod_Negative =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 3);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_variety);

               when Test_Range_Jump =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 5);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_nat);
                  Output.TDF (O, c_label);

               when Make_Float_Id =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_nat);
                  Output.List_Count (O, 1);
                  Output.TDF (O, c_exp);

               when Make_Float_Range_Id =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_nat);
                  Output.List_Count (O, 3);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);

               when Rep_Fv =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_floating_variety);
                  Output.List_Count (O, 1);
                  Output.TDF (O, c_nat);

               when Rep_Fv_Max_Val | Make_Float_Attr =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 1);
                  Output.TDF (O, c_nat);

               when Make_Float_Attr_1 =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 2);
                  Output.TDF (O, c_nat);
                  Output.TDF (O, c_exp);

               when Make_Float_Attr_2 =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 3);
                  Output.TDF (O, c_nat);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);

            end case;

         when Subtype_Attribute_Token =>
            case Link.Attribute is
               when Asis.A_First_Attribute
                 | Asis.A_Last_Attribute
                 | Asis.A_Succ_Attribute
                 | Asis.A_Pred_Attribute
                 | Asis.A_Pos_Attribute
                 | Asis.A_Val_Attribute
                 | Asis.A_Ceiling_Attribute
                 | Asis.A_Floor_Attribute
                 | Asis.A_Rounding_Attribute
                 | Asis.A_Truncation_Attribute
                 | Asis.An_Unbiased_Rounding_Attribute
                 | Asis.An_Exponent_Attribute
                 | Asis.A_Fraction_Attribute
                 | Asis.A_Machine_Attribute
                 | Asis.A_Model_Attribute
                 =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 1);
                  Output.TDF (O, c_exp);
               when Asis.A_Min_Attribute
                 | Asis.A_Max_Attribute
                 | Asis.An_Adjacent_Attribute
                 | Asis.A_Copy_Sign_Attribute
                 | Asis.A_Remainder_Attribute
                 | Asis.A_Leading_Part_Attribute
                 | Asis.A_Compose_Attribute
                 | Asis.A_Scaling_Attribute
                 =>
                  Output.TDF (O, c_token);
                  Output.TDF (O, c_exp);
                  Output.List_Count (O, 2);
                  Output.TDF (O, c_exp);
                  Output.TDF (O, c_exp);
               when Asis.A_Modulus_Attribute
                 | Asis.A_Denorm_Attribute
                 | Asis.A_Machine_Emax_Attribute
                 | Asis.A_Machine_Emin_Attribute
                 | Asis.A_Machine_Mantissa_Attribute
                 | Asis.A_Machine_Overflows_Attribute
                 | Asis.A_Machine_Radix_Attribute
                 | Asis.A_Machine_Rounds_Attribute
                 | Asis.A_Max_Size_In_Storage_Elements_Attribute
                 | Asis.A_Model_Emin_Attribute
                 | Asis.A_Model_Epsilon_Attribute
                 | Asis.A_Model_Mantissa_Attribute
                 | Asis.A_Model_Small_Attribute
                 | Asis.A_Safe_First_Attribute
                 | Asis.A_Safe_Last_Attribute
                 | Asis.A_Signed_Zeros_Attribute
                 =>
                  Output.TDF (O, c_exp);
               when others =>
                  raise States.Error;
            end case;
         when Tag | Proc_Tag =>
            null;
      end case;
   end New_Token;

end Token;


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
