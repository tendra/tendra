with Asis.Elements;
with Asis.Definitions;

with XASIS.Utils;
with XASIS.Classes;

with Token;
with States;
with Expression;

with TenDRA;
with TenDRA.Types;
with TenDRA.Output;
with TenDRA.Streams;

with Ada.Wide_Text_IO;

package body Type_Definition is
   use Asis;
   use States;
   use TenDRA;
   use TenDRA.Types;

   procedure Make_Signed_Variety
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info);

   procedure Make_Signed_Bounds
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info);

   procedure Make_Float_Variety
     (State  : access States.State;
      Tipe   : in     XASIS.Classes.Type_Info;
      Bounds : in     Asis.Range_Constraint);

   procedure Make_Enum_Variety
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info;
      List  : in     Asis.Declaration_List);

   procedure Make_Enum_Literal
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info;
      List  : in     Asis.Declaration_List;
      Index : in     Asis.List_Index);

   procedure Make_Shape_From_Variety
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info);

   -------------
   -- Compile --
   -------------

   procedure Compile
     (State    : access States.State;
      Element  : in     Asis.Definition)
   is
   begin
      case Elements.Type_Kind (Element) is
         when An_Enumeration_Type_Definition =>
            declare
               use XASIS.Utils;
               use XASIS.Classes;
               Tipe  : Type_Info :=
                 Type_From_Declaration (Elements.Enclosing_Element (Element));
               List  : Asis.Declaration_List :=
                 Asis.Definitions.Enumeration_Literal_Declarations (Element);
            begin
               if Elements.Is_Part_Of_Implicit (List (1)) then
                  --  Process predefined Character in a special way
                  Make_Signed_Variety (State, Tipe);
                  Make_Shape_From_Variety (State, Tipe);
               else
                  Make_Enum_Variety (State, Tipe, List);
                  Make_Shape_From_Variety (State, Tipe);

                  for J in List'Range loop
                     Make_Enum_Literal (State, Tipe, List, J);
                  end loop;
               end if;
            end;

         when A_Signed_Integer_Type_Definition =>
            declare
               use XASIS.Utils;
               use XASIS.Classes;
               Tipe  : Type_Info :=
                 Type_From_Declaration (Elements.Enclosing_Element (Element));
            begin
               Make_Signed_Variety (State, Tipe);
               Make_Signed_Bounds (State, Tipe);
               Make_Shape_From_Variety (State, Tipe);
            end;

         when A_Root_Type_Definition
           | An_Unconstrained_Array_Definition
           | An_Ordinary_Fixed_Point_Definition =>
            null;

         when A_Floating_Point_Definition =>
            declare
               use XASIS.Utils;
               use XASIS.Classes;
               Bounds : constant Asis.Range_Constraint :=
                 Asis.Definitions.Real_Range_Constraint (Element);
               Tipe   : Type_Info :=
                 Type_From_Declaration (Elements.Enclosing_Element (Element));
            begin
               Make_Float_Variety (State, Tipe, Bounds);
               -- Make_Shape_From_Variety (State, Tipe);
            end;

         when others =>
            Ada.Wide_Text_IO.Put_Line (Elements.Debug_Image (Element));
            raise States.Error;
      end case;
   end Compile;

   -----------------------
   -- Make_Enum_Literal --
   -----------------------

   procedure Make_Enum_Literal
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info;
      List  : in     Asis.Declaration_List;
      Index : in     Asis.List_Index)
   is
      use XASIS.Utils;
      use XASIS.Classes;
      D     : aliased Streams.Memory_Stream;
      T     : TenDRA.Streams.Memory_Stream
        renames State.Units (TOKDEF).all;
      Name  : Asis.Defining_Name := Declaration_Name (List (Index));
      Tok   : Small := Find_Value (State, Name, TOKDEF, False);
      Var   : Small := Find_Variety (State, Tipe, TOKDEF);
      Addr  : TenDRA.Small := State.Unit_Total (TOKDEF, States.Token);
   begin
      Inc (State.Unit_Total (TOKDEF, States.Token));

      Streams.Expect
        (D, Dummy, ((TOKEN_DEFN_SORT, Singular, False),
                    (EXP_SORT, Singular, False)));
      Output.TDF (D, c_token_definition);
      Output.TDF (D, c_exp);
      Output.List_Count (D, 1);
      Output.TDF (D, c_make_tokformals);
      Output.TDF (D, c_nat);
      Output.TDFINT (D, Addr);

      Output.TDF (D, c_make_int);
      Output.TDF (D, c_var_apply_token);
      Output.TDF (D, c_make_tok);
      Output.TDFINT (D, Var);
      Output.BITSTREAM (D, Empty);
      Output.TDF (D, c_make_signed_nat);
      Output.TDFBOOL (D, False);
      Output.TDFINT (D, Small (Index) - 1);

      Inc (State.Length (TOKDEF));
      Output.TDF (T, c_make_tokdef);
      Output.TDFINT (T, Tok);
      Output.No_Option (T);  --  signature
      Output.BITSTREAM (T, D);
   end Make_Enum_Literal;

   -----------------------
   -- Make_Enum_Variety --
   -----------------------

   procedure Make_Enum_Variety
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info;
      List  : in     Asis.Declaration_List)
   is
      use XASIS.Utils;
      use XASIS.Classes;
      D     : aliased Streams.Memory_Stream;
      T     : TenDRA.Streams.Memory_Stream
        renames State.Units (TOKDEF).all;
      Var   : Small;
   begin
      Var := Find_Variety (State, Tipe, TOKDEF, False);

      Streams.Expect
        (D, Dummy, ((TOKEN_DEFN_SORT, Singular, False),
                    (VARIETY_SORT, Singular, False)));

      Output.TDF (D, c_token_definition);
      Output.TDF (D, c_variety);
      Output.List_Count (D, 0);
      Output.TDF (D, c_var_limits);
      Output.TDF (D, c_make_signed_nat);
      Output.TDFBOOL (D, False);
      Output.TDFINT (D, 0);

      Output.TDF (D, c_make_signed_nat);
      Output.TDFBOOL (D, False);
      Output.TDFINT (D, List'Length - 1);

      Inc (State.Length (TOKDEF));
      Output.TDF (T, c_make_tokdef);
      Output.TDFINT (T, Var);
      Output.No_Option (T);  --  signature
      Output.BITSTREAM (T, D);
   end Make_Enum_Variety;

   ------------------------
   -- Make_Float_Variety --
   ------------------------

   procedure Make_Float_Variety
     (State  : access States.State;
      Tipe   : in     XASIS.Classes.Type_Info;
      Bounds : in     Asis.Range_Constraint)
   is
      use XASIS.Utils;
      use XASIS.Classes;

--      Prec  : Small := Find_Type_Param (State, Tipe, Precision, TOKDEF);

      D     : aliased Streams.Memory_Stream;
      T     : TenDRA.Streams.Memory_Stream
        renames State.Units (TOKDEF).all;
--      Var   : Small := Find_Variety (State, Tipe, TOKDEF, False);
   begin
      null;
   end Make_Float_Variety;

   -------------------------
   -- Make_Signed_Variety --
   -------------------------

   procedure Make_Signed_Variety
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info)
   is
      use XASIS.Utils;
      use XASIS.Classes;

      First : Small := Find_Type_Param (State, Tipe, Lower, TOKDEF);
      Last  : Small := Find_Type_Param (State, Tipe, Upper, TOKDEF);

      D     : aliased Streams.Memory_Stream;
      T     : TenDRA.Streams.Memory_Stream
        renames State.Units (TOKDEF).all;
      Var   : Small := Find_Variety (State, Tipe, TOKDEF, False);
   begin
      Streams.Expect
        (D, Dummy, ((TOKEN_DEFN_SORT, Singular, False),
                    (VARIETY_SORT, Singular, False)));

      Output.TDF (D, c_token_definition);
      Output.TDF (D, c_variety);
      Output.List_Count (D, 0);
      Output.TDF (D, c_var_limits);

      --  Lower boundary
      Output.TDF (D, c_signed_nat_apply_token);
      Output.TDF (D, c_make_tok);
      Output.TDFINT (D, First);
      Output.BITSTREAM (D, Empty);

      --  Upper boundary
      Output.TDF (D, c_signed_nat_apply_token);
      Output.TDF (D, c_make_tok);
      Output.TDFINT (D, Last);
      Output.BITSTREAM (D, Empty);

      Inc (State.Length (TOKDEF));
      Output.TDF (T, c_make_tokdef);
      Output.TDFINT (T, Var);
      Output.No_Option (T);  --  signature
      Output.BITSTREAM (T, D);
   end Make_Signed_Variety;

   ------------------------
   -- Make_Signed_Bounds --
   ------------------------

   procedure Make_Signed_Bounds
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info)
   is
      use XASIS.Utils;
      use XASIS.Classes;

      procedure Make_Token
        (Expr  : Asis.Expression;
         Param : States.Type_Param_Kinds)
      is
         T     : TenDRA.Streams.Memory_Stream
           renames State.Units (TOKDEF).all;
         D     : aliased Streams.Memory_Stream;
         Token : Small := Find_Type_Param (State, Tipe, Param, TOKDEF, False);
      begin
         Streams.Expect
           (D, Dummy, ((TOKEN_DEFN_SORT, Singular, False),
                       (SIGNED_NAT_SORT, Singular, False)));

         Output.TDF (D, c_token_definition);
         Output.TDF (D, c_signed_nat);
         Output.List_Count (D, 0);
         Expression.Static_Signed_Nat (State, Expr, D);

         Inc (State.Length (TOKDEF));
         Output.TDF (T, c_make_tokdef);
         Output.TDFINT (T, Token);
         Output.No_Option (T);  --  signature
         Output.BITSTREAM (T, D);
      end Make_Token;

      Rng   : Asis.Range_Constraint :=
        Asis.Definitions.Integer_Constraint (Get_Definition (Tipe));
      Left  : Asis.Expression := Asis.Definitions.Lower_Bound (Rng);
      Right : Asis.Expression := Asis.Definitions.Upper_Bound (Rng);

   begin
      if Elements.Is_Part_Of_Implicit (Left)
        and then Elements.Is_Part_Of_Implicit (Right)
      then
         return;
      end if;

      if not Elements.Is_Part_Of_Implicit (Left) then
         Make_Token (Left, Lower);
      end if;

      if not Elements.Is_Part_Of_Implicit (Right) then
         Make_Token (Right, Upper);
      end if;
   end Make_Signed_Bounds;

   -----------------------------
   -- Make_Shape_From_Variety --
   -----------------------------

   procedure Make_Shape_From_Variety
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info)
   is
      use XASIS.Utils;
      use XASIS.Classes;
      D     : aliased Streams.Memory_Stream;
      T     : TenDRA.Streams.Memory_Stream
        renames State.Units (TOKDEF).all;
      Var   : Small := Find_Variety (State, Tipe, TOKDEF);
      Shape : Small := Find_Shape (State, Tipe, TOKDEF, False);
   begin
      Streams.Expect
        (D, Dummy, ((TOKEN_DEFN_SORT, Singular, False),
                    (SHAPE_SORT, Singular, False)));

      Output.TDF (D, c_token_definition);
      Output.TDF (D, c_shape);
      Output.List_Count (D, 0);
      Output.TDF (D, c_integer);
      Output.TDF (D, c_var_apply_token);
      Output.TDF (D, c_make_tok);
      Output.TDFINT (D, Var);
      Output.BITSTREAM (D, Empty);

      Inc (State.Length (TOKDEF));
      Output.TDF (T, c_make_tokdef);
      Output.TDFINT (T, Shape);
      Output.No_Option (T);  --  signature
      Output.BITSTREAM (T, D);
   end Make_Shape_From_Variety;

end Type_Definition;


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
