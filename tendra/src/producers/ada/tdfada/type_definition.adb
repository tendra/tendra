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
      Tipe  : in     XASIS.Classes.Type_Info;
      Rng   : in     Asis.Range_Constraint);

   procedure Make_Signed_Base
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

   procedure Make_Modular_Bounds
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info;
      Expr  : in     Asis.Expression);

   procedure Apply_Lower_Upper
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info;
      Param : in out Streams.Memory_Stream;
      Kind  : in     Type_Param_Kinds);

   -----------------------
   -- Apply_Lower_Upper --
   -----------------------

   procedure Apply_Lower_Upper
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info;
      Param : in out Streams.Memory_Stream;
      Kind  : in     Type_Param_Kinds)
   is
      Limit : constant Small := Find_Type_Param (State, Tipe, Kind, TOKDEF);
   begin
      Output.TDF (Param, c_exp_apply_token);
      Output.TDF (Param, c_make_tok);
      Output.TDFINT (Param, Limit);
      Output.BITSTREAM (Param, Empty);
   end Apply_Lower_Upper;

   -------------
   -- Compile --
   -------------

   procedure Compile
     (State    : access States.State;
      Element  : in     Asis.Definition)
   is
      use XASIS.Utils;
      use XASIS.Classes;
      use Asis.Definitions;

      Tipe  : constant Type_Info :=
        Type_From_Declaration (Elements.Enclosing_Element (Element));
   begin
      case Elements.Type_Kind (Element) is
         when An_Enumeration_Type_Definition =>
            declare
               List  : constant Asis.Declaration_List :=
                 Enumeration_Literal_Declarations (Element);
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
            Make_Signed_Bounds (State, Tipe, Integer_Constraint (Element));
            Make_Signed_Base (State, Tipe);
            Make_Signed_Variety (State, Tipe);
            Make_Shape_From_Variety (State, Tipe);
            Make_Attributes (State, Tipe);

         when A_Modular_Type_Definition =>
            Make_Modular_Bounds
              (State, Tipe, Mod_Static_Expression (Element));
            Make_Signed_Variety (State, Tipe);
            Make_Shape_From_Variety (State, Tipe);
            Make_Attributes (State, Tipe);

         when A_Root_Type_Definition
           | An_Unconstrained_Array_Definition
           | An_Ordinary_Fixed_Point_Definition =>
            null;

         when A_Floating_Point_Definition =>
            declare
               Bounds : constant Asis.Range_Constraint :=
                 Real_Range_Constraint (Element);
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
      begin
         for J in Args'Range loop
            Args (J) := State.Unit_Total (TOKDEF, States.Token);
            Inc (State.Unit_Total (TOKDEF, States.Token));
         end loop;

         Streams.Expect
           (D, Dummy, ((TOKEN_DEFN_SORT, Singular, False),
                       (EXP_SORT, Singular, False)));

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
         Dummy : Arg_List (1 .. 1);
      begin
         Open_Token_Def (D, Dummy);

         Output.TDF (D, c_change_variety);
         Output.TDF (D, c_continue);
         Output.TDF (D, c_var_apply_token);
         Output.TDF (D, c_make_tok);
         Output.TDFINT (D, Var);
         Output.BITSTREAM (D, Empty);

         if Kind = A_First_Attribute then
            Apply_Lower_Upper (State, Tipe, D, Lower);
         else
            Apply_Lower_Upper (State, Tipe, D, Upper);
         end if;

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
         elsif Is_Modular_Integer (Tipe) then
            if Kind = A_Succ_Attribute then
               Macro := Find_Support (State, Mod_Plus, TOKDEF);
               Token.Initialize (Param, Mod_Plus);
            else
               Macro := Find_Support (State, Mod_Minus, TOKDEF);
               Token.Initialize (Param, Mod_Minus);
            end if;
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
         elsif Is_Modular_Integer (Tipe) then
            Expression.Output_Int (State, Tipe, 1, Param, TOKDEF);
            Apply_Lower_Upper (State, Tipe, Param, Upper);
         end if;

         Output.TDF (Param, c_var_apply_token);
         Output.TDF (Param, c_make_tok);
         Output.TDFINT (Param, Var);
         Output.BITSTREAM (Param, Empty);

         if not Is_Modular_Integer (Tipe) then
            Output.TDF (Param, c_make_nat);

            if Kind = A_Succ_Attribute then
               Output.TDFINT (Param, 0);
            else
               Output.TDFINT (Param, 1);
            end if;
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

         if Is_Enumeration (Tipe) or Is_Modular_Integer (Tipe) then
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

         if Is_Enumeration (Tipe) or Is_Modular_Integer (Tipe) then
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

      procedure Make_Modulus (Kind : Asis.Attribute_Kinds) is
         D     : aliased Streams.Memory_Stream;
         Arg   : Arg_List (1 .. 0);
      begin
         Open_Token_Def (D, Arg);

         Output.TDF (D, c_plus);
         Output.TDF (D, c_impossible);
         Apply_Lower_Upper (State, Tipe, D, Upper);
         Expression.Output_Int (State, T.Universal_Integer, 1, D, TOKDEF);

         Close_Token_Def (Kind, D);
      end Make_Modulus;

   begin
      if Is_Discrete (Tipe) then
         Make_First_Last (A_First_Attribute);
         Make_First_Last (A_Last_Attribute);
         Make_Min_Max (A_Min_Attribute);
         Make_Min_Max (A_Max_Attribute);
         Make_Pos (A_Pos_Attribute);
         Make_Val (A_Val_Attribute);

         if Is_Enumeration (Tipe)
           or Is_Signed_Integer (Tipe)
           or Is_Modular_Integer (Tipe)
         then
            Make_Succ_Pred (A_Succ_Attribute);
            Make_Succ_Pred (A_Pred_Attribute);
         end if;

         if Is_Modular_Integer (Tipe) then
            Make_Modulus (A_Modulus_Attribute);
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
   begin
      Streams.Expect
        (D, Dummy, ((TOKEN_DEFN_SORT, Singular, False),
                    (EXP_SORT, Singular, False)));
      Output.TDF (D, c_token_definition);
      Output.TDF (D, c_exp);
      Output.List_Count (D, 0);

      Expression.Output_Int (State, Tipe, Small (Index) - 1, D, TOKDEF);

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

      procedure Evaluate
        (D     : in out Streams.Memory_Stream;
         Expr  : in     Small) is
      begin
         Expression.Output_Int (State, T.Universal_Integer, Expr, D, TOKDEF);
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

   -------------------------
   -- Make_Modular_Bounds --
   -------------------------

   procedure Make_Modular_Bounds
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info;
      Expr  : in     Asis.Expression)
   is
      use XASIS.Utils;
      use XASIS.Classes;

      procedure Evaluate
        (D     : in out Streams.Memory_Stream;
         Lower : in     Boolean) is
      begin
         if Lower then
            Expression.Output_Int (State, T.Universal_Integer, 0, D, TOKDEF);
         else
            Output.TDF (D, c_minus);
            Output.TDF (D, c_impossible);

            Expression.Computed_Static
              (State, Expr, T.Root_Integer, D, TOKDEF);

            Expression.Output_Int (State, T.Universal_Integer, 1, D, TOKDEF);
         end if;
      end Evaluate;

      procedure Make_Token is new Make_Param_Token (Boolean, Evaluate);

   begin
      Make_Token (State, Tipe, Lower, True);
      Make_Token (State, Tipe, Upper, False);
   end Make_Modular_Bounds;

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
      Apply_Lower_Upper (State, Tipe, D, Lower);

      --  Upper boundary
      Output.TDF (D, c_computed_signed_nat);
      Apply_Lower_Upper (State, Tipe, D, Upper);

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
      Tipe  : in     XASIS.Classes.Type_Info;
      Rng   : in     Asis.Range_Constraint)
   is
      use XASIS.Utils;
      use XASIS.Classes;

      procedure Evaluate
        (D     : in out Streams.Memory_Stream;
         Expr  : in     Asis.Expression) is
      begin
         Expression.Computed_Static (State, Expr, T.Root_Integer, D, TOKDEF);
      end Evaluate;

      procedure Make_Token is new Make_Param_Token (Asis.Expression, Evaluate);

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

   ----------------------
   -- Make_Signed_Base --
   ----------------------

   procedure Make_Signed_Base
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info)
   is
      use XASIS.Utils;
      use XASIS.Classes;

      Var   : constant Small := Find_Variety (State, Tipe, TOKDEF);

      procedure Evaluate
        (D      : in out Streams.Memory_Stream;
         Kind   : in     Support_Kinds)
      is
         Param : Streams.Memory_Stream;
         Macro : constant Small := Find_Support (State, Kind, TOKDEF);
      begin
         Token.Initialize (Param, Kind);

         Apply_Lower_Upper (State, Tipe, Param, Lower);
         Apply_Lower_Upper (State, Tipe, Param, Upper);

         Output.TDF (Param, c_var_apply_token);
         Output.TDF (Param, c_make_tok);
         Output.TDFINT (Param, Var);
         Output.BITSTREAM (Param, Empty);

         Output.TDF (D, c_exp_apply_token);
         Output.TDF (D, c_make_tok);
         Output.TDFINT (D, Macro);
         Output.BITSTREAM (D, Param);
      end Evaluate;

      procedure Make_Token is new Make_Param_Token (Support_Kinds, Evaluate);

   begin
      Make_Token (State, Tipe, Base_Lower, Signed_Base_Lower);
      Make_Token (State, Tipe, Base_Upper, Signed_Base_Upper);
   end Make_Signed_Base;

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
