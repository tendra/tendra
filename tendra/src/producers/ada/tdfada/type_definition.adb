with Asis.Elements;
with Asis.Definitions;

with XASIS.Types;
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

   generic
      type User_Type is private;
      with procedure Evaluate (D     : in out Streams.Memory_Stream;
                               Data  : in     User_Type);
   procedure Make_Param_Token
        (State : access States.State;
         Tipe  : in     XASIS.Classes.Type_Info;
         Param : in     States.Type_Param_Kinds;
         Data  : in     User_Type);

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

   procedure Make_Enum_Bounds
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

   procedure Make_Attributes
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
               if not Elements.Is_Part_Of_Implicit (List (1)) then
                  --  Process predefined Character in a special way
                  Make_Enum_Bounds (State, Tipe, List);
               end if;
               
               Make_Signed_Variety (State, Tipe);
               Make_Shape_From_Variety (State, Tipe);
               Make_Attributes (State, Tipe);
            end;

         when A_Signed_Integer_Type_Definition =>
            declare
               use XASIS.Utils;
               use XASIS.Classes;
               Tipe  : Type_Info :=
                 Type_From_Declaration (Elements.Enclosing_Element (Element));
            begin
               Make_Signed_Bounds (State, Tipe);
               Make_Signed_Variety (State, Tipe);
               Make_Shape_From_Variety (State, Tipe);
               Make_Attributes (State, Tipe);
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

   ---------------------
   -- Make_Attributes --
   ---------------------

   procedure Make_Attributes
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info)
   is
      use XASIS.Classes;

      Decl : constant Asis.Declaration := Get_Declaration (Tipe);

      type Arg_List is array (Positive range <>) of Small;

      --------------------
      -- Open_Token_Def --
      --------------------

      procedure Open_Token_Def
        (D    : in out Streams.Memory_Stream;
         Args :    out Arg_List)
      is
         Expect : constant Argument_List (1 .. 1 + Args'Length) := 
           (1      => (TOKEN_DEFN_SORT, Singular, False),
            others => (EXP_SORT, Singular, False));
      begin
         for J in Args'Range loop
            Args (J) := State.Unit_Total (TOKDEF, States.Token);
            Inc (State.Unit_Total (TOKDEF, States.Token));
         end loop;

         Streams.Expect (D, Types.Dummy, Expect);

         Output.TDF (D, c_token_definition);
         Output.TDF (D, c_exp);
         Output.List_Count (D, Args'Length);

         for J in Args'Range loop
            Output.TDF (D, c_make_tokformals);
            Output.TDF (D, c_exp);
            Output.TDFINT (D, Args (J));
         end loop;
      end Open_Token_Def;

      ---------------------
      -- Close_Token_Def --
      ---------------------

      procedure Close_Token_Def
        (Kind : in     Asis.Attribute_Kinds;
         D    : in out Streams.Memory_Stream)
      is
         T     : TenDRA.Streams.Memory_Stream
           renames State.Units (TOKDEF).all;
         Tok   : Small := Find_Attribute (State, Decl, Kind, TOKDEF, False);
      begin
         Inc (State.Length (TOKDEF));
         Output.TDF (T, c_make_tokdef);
         Output.TDFINT (T, Tok);
         Output.No_Option (T);  --  signature
         Output.BITSTREAM (T, D);
      end Close_Token_Def;

      ----------------------
      -- Apply_First_Last --
      ----------------------

      procedure Apply_First_Last
        (Param : in out Streams.Memory_Stream;
         Kind  : in     Asis.Attribute_Kinds)
      is
         Top   : Streams.Memory_Stream;
         Limit : constant Small := Find_Attribute (State, Decl, Kind, TOKDEF);
      begin
         Output.TDF (Param, c_exp_apply_token);
         Output.TDF (Param, c_make_tok);
         Output.TDFINT (Param, Limit);

         Streams.Expect (Top, Dummy, (1 => (EXP_SORT, Singular, False)));
         Output.TDF (Top, c_make_top);
         Output.BITSTREAM (Param, Top);
      end Apply_First_Last;

      ---------------------
      -- Make_First_Last --
      ---------------------

      procedure Make_First_Last (Kind : Asis.Attribute_Kinds) is
         D     : aliased Streams.Memory_Stream;
         Var   : Small := Find_Variety (State, Tipe, TOKDEF);
         Bound : Small;
         Dummy : Arg_List (1 .. 1);
      begin
         if Kind = A_First_Attribute then
            Bound := Find_Type_Param (State, Tipe, Lower, TOKDEF);
         else
            Bound := Find_Type_Param (State, Tipe, Upper, TOKDEF);
         end if;

         Open_Token_Def (D, Dummy);

         Output.TDF (D, c_change_variety);
         Output.TDF (D, c_continue);
         Output.TDF (D, c_var_apply_token);
         Output.TDF (D, c_make_tok);
         Output.TDFINT (D, Var);
         Output.BITSTREAM (D, Empty);
         Output.TDF (D, c_exp_apply_token);
         Output.TDF (D, c_make_tok);
         Output.TDFINT (D, Bound);
         Output.BITSTREAM (D, Empty);

         Close_Token_Def (Kind, D);
      end Make_First_Last;

      ------------------
      -- Make_Min_Max --
      ------------------

      procedure Make_Min_Max (Kind : Asis.Attribute_Kinds) is
         D     : aliased Streams.Memory_Stream;
         Var   : Small := Find_Variety (State, Tipe, TOKDEF);
         Args  : Arg_List (1 .. 2);
      begin
         Open_Token_Def (D, Args);

         if Kind = A_Min_Attribute then
            Output.TDF (D, c_minimum);
         else
            Output.TDF (D, c_maximum);
         end if;

         Output.TDF (D, c_exp_apply_token);
         Output.TDF (D, c_make_tok);
         Output.TDFINT (D, Args (1));
         Output.BITSTREAM (D, Empty);

         Output.TDF (D, c_exp_apply_token);
         Output.TDF (D, c_make_tok);
         Output.TDFINT (D, Args (2));
         Output.BITSTREAM (D, Empty);

         Close_Token_Def (Kind, D);
      end Make_Min_Max;

      --------------------
      -- Make_Succ_Pred --
      --------------------

      procedure Make_Succ_Pred (Kind : Asis.Attribute_Kinds) is
         D     : aliased Streams.Memory_Stream;
         Var   : Small := Find_Variety (State, Tipe, TOKDEF);
         Macro : Small;
         Param : Streams.Memory_Stream;
         Arg   : Arg_List (1 .. 1);
      begin
         Open_Token_Def (D, Arg);

         if Is_Enumeration (Tipe) then
            Macro := Find_Support (State, Enum_Succ_Pred_Attr, TOKDEF);
            Token.Initialize (Param, Enum_Succ_Pred_Attr);
         elsif Is_Signed_Integer (Tipe) then
            Macro := Find_Support (State, Signed_Succ_Pred_Attr, TOKDEF);
            Token.Initialize (Param, Signed_Succ_Pred_Attr);
         else
            raise States.Error;
         end if;

         Output.TDF (D, c_exp_apply_token);
         Output.TDF (D, c_make_tok);
         Output.TDFINT (D, Macro);

         Output.TDF (Param, c_exp_apply_token);
         Output.TDF (Param, c_make_tok);
         Output.TDFINT (Param, Arg (1));
         Output.BITSTREAM (Param, Empty);

         if Is_Enumeration (Tipe) then
            if Kind = A_Succ_Attribute then
               Apply_First_Last (Param, A_Last_Attribute);
            else
               Apply_First_Last (Param, A_First_Attribute);
            end if;
         end if;

         Output.TDF (Param, c_var_apply_token);
         Output.TDF (Param, c_make_tok);
         Output.TDFINT (Param, Var);
         Output.BITSTREAM (Param, Empty);

         Output.TDF (Param, c_make_nat);

         if Kind = A_Succ_Attribute then
            Output.TDFINT (Param, 0);
         else
            Output.TDFINT (Param, 1);
         end if;

         Output.BITSTREAM (D, Param);

         Close_Token_Def (Kind, D);
      end Make_Succ_Pred;

      --------------
      -- Make_Pos --
      --------------

      procedure Make_Pos (Kind : Asis.Attribute_Kinds) is
         D     : aliased Streams.Memory_Stream;
         Var   : Small := Find_Variety (State, Tipe, TOKDEF);
         Arg   : Arg_List (1 .. 1);
      begin
         Open_Token_Def (D, Arg);

         Output.TDF (D, c_change_variety);
         Output.TDF (D, c_trap);
         Output.List_Count (D, 1);
         Output.TDF (D, c_overflow);
         Output.TDF (D, c_var_apply_token);
         Output.TDF (D, c_make_tok);
         Output.TDFINT (D, Var);
         Output.BITSTREAM (D, Empty);

         Output.TDF (D, c_exp_apply_token);
         Output.TDF (D, c_make_tok);
         Output.TDFINT (D, Arg (1));
         Output.BITSTREAM (D, Empty);

         Close_Token_Def (Kind, D);
      end Make_Pos;

      --------------
      -- Make_Val --
      --------------

      procedure Make_Val (Kind : Asis.Attribute_Kinds) is
         D     : aliased Streams.Memory_Stream;
         Var   : Small := Find_Variety (State, Tipe, TOKDEF);
         Arg   : Arg_List (1 .. 1);
         Macro : Small;
         Param : Streams.Memory_Stream;
      begin
         Open_Token_Def (D, Arg);

         if Is_Enumeration (Tipe) then
            Macro := Find_Support (State, Enum_Val_Attr, TOKDEF);
            Token.Initialize (Param, Enum_Val_Attr);
         elsif Is_Signed_Integer (Tipe) then
            Macro := Find_Support (State, Signed_Val_Attr, TOKDEF);
            Token.Initialize (Param, Signed_Val_Attr);
         else
            raise States.Error;
         end if;

         Output.TDF (D, c_exp_apply_token);
         Output.TDF (D, c_make_tok);
         Output.TDFINT (D, Macro);

         Output.TDF (Param, c_exp_apply_token);
         Output.TDF (Param, c_make_tok);
         Output.TDFINT (Param, Arg (1));
         Output.BITSTREAM (Param, Empty);

         if Is_Enumeration (Tipe) then
            Apply_First_Last (Param, A_First_Attribute);
            Apply_First_Last (Param, A_Last_Attribute);
         end if;

         Output.TDF (Param, c_var_apply_token);
         Output.TDF (Param, c_make_tok);
         Output.TDFINT (Param, Var);
         Output.BITSTREAM (Param, Empty);

         Output.BITSTREAM (D, Param);

         Close_Token_Def (Kind, D);
      end Make_Val;
   begin
      if Is_Discrete (Tipe) then
         Make_First_Last (A_First_Attribute);
         Make_First_Last (A_Last_Attribute);
         Make_Min_Max (A_Min_Attribute);
         Make_Min_Max (A_Max_Attribute);
         Make_Pos (A_Pos_Attribute);
         Make_Val (A_Val_Attribute);

         if Is_Enumeration (Tipe) or Is_Signed_Integer (Tipe) then
            Make_Succ_Pred (A_Succ_Attribute);
            Make_Succ_Pred (A_Pred_Attribute);
         end if;
      end if;
   end Make_Attributes;

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
   begin
      Streams.Expect
        (D, Dummy, ((TOKEN_DEFN_SORT, Singular, False),
                    (EXP_SORT, Singular, False)));
      Output.TDF (D, c_token_definition);
      Output.TDF (D, c_exp);
      Output.List_Count (D, 0);

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

   ----------------------
   -- Make_Enum_Bounds --
   ----------------------

   procedure Make_Enum_Bounds
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info;
      List  : in     Asis.Declaration_List)
   is
      use XASIS.Utils;
      use XASIS.Classes;

      Var   : constant Small :=
        Expression.Universal_Variety (State, T.Root_Integer, TOKDEF);

      procedure Evaluate
        (D     : in out Streams.Memory_Stream;
         Expr  : in     Small) is
      begin
         Output.TDF (D, c_make_int);
         Output.TDF (D, c_var_apply_token);
         Output.TDF (D, c_make_tok);
         Output.TDFINT (D, Var);
         Output.BITSTREAM (D, Empty);
         Output.TDF (D, c_make_signed_nat);
         Output.TDFBOOL (D, False);
         Output.TDFINT (D, Expr);
      end Evaluate;

      procedure Make_Token is new Make_Param_Token (Small, Evaluate);

   begin
      Make_Token (State, Tipe, Lower, 0);
      Make_Token (State, Tipe, Upper, List'Length - 1);
   end Make_Enum_Bounds;

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

   ----------------------
   -- Make_Param_Token --
   ----------------------

   procedure Make_Param_Token
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info;
      Param : in     States.Type_Param_Kinds;
      Data  : in     User_Type)
   is
      T     : TenDRA.Streams.Memory_Stream renames State.Units (TOKDEF).all;
      D     : Streams.Memory_Stream;
      Token : Small := Find_Type_Param (State, Tipe, Param, TOKDEF, False);
   begin
      Streams.Expect
        (D, Dummy, ((TOKEN_DEFN_SORT, Singular, False),
                     (EXP_SORT, Singular, False)));

      Output.TDF (D, c_token_definition);
      Output.TDF (D, c_exp);
      Output.List_Count (D, 0);

      Evaluate (D, Data);

      Inc (State.Length (TOKDEF));
      Output.TDF (T, c_make_tokdef);
      Output.TDFINT (T, Token);
      Output.No_Option (T);  --  signature
      Output.BITSTREAM (T, D);
   end Make_Param_Token;

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
      Output.TDF (D, c_computed_signed_nat);
      Output.TDF (D, c_exp_apply_token);
      Output.TDF (D, c_make_tok);
      Output.TDFINT (D, First);
      Output.BITSTREAM (D, Empty);

      --  Upper boundary
      Output.TDF (D, c_computed_signed_nat);
      Output.TDF (D, c_exp_apply_token);
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

      Int   : constant Type_Info := T.Root_Integer;

      procedure Evaluate
        (D     : in out Streams.Memory_Stream;
         Expr  : in     Asis.Expression) is
      begin
         Expression.Computed_Static (State, Expr, Int, D, TOKDEF);
      end Evaluate;
      
      procedure Make_Token is new Make_Param_Token (Asis.Expression, Evaluate);
      
      Rng   : Asis.Range_Constraint :=
        Asis.Definitions.Integer_Constraint (Get_Definition (Tipe));
      Left  : Asis.Expression := Asis.Definitions.Lower_Bound (Rng);
      Right : Asis.Expression := Asis.Definitions.Upper_Bound (Rng);

   begin
      if not Elements.Is_Part_Of_Implicit (Left) then
         Make_Token (State, Tipe, Lower, Left);
      end if;

      if not Elements.Is_Part_Of_Implicit (Right) then
         Make_Token (State, Tipe, Upper, Right);
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
