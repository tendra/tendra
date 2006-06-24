with TenDRA;
with TenDRA.Types;
with TenDRA.Output;
with TenDRA.Streams;

with XASIS.Types;
with XASIS.Utils;
with XASIS.Classes;

with Asis.Elements;
with Asis.Statements;
with Asis.Expressions;

with Token;
with Utils;
with Intrinsic;

package body Expression is
   use Asis;
   use TenDRA;
   use TenDRA.Types;

   procedure Identifier
     (State   : access States.State;
      Element : in     Asis.Element;
      L_Value : in     Boolean := False);

   procedure Short_Circuit
     (State    : access States.State;
      Element  : in     Asis.Element;
      Negative : in     Boolean);

   procedure Short_Circuit
     (State    : access States.State;
      Element  : in     Asis.Element;
      Negative : in     Boolean;
      Label    : in     TenDRA.Small);

   procedure Function_Call_Boolean
     (State    : access States.State;
      Element  : in     Asis.Element;
      Negative : in     Boolean);

   procedure Function_Call_Boolean
     (State    : access States.State;
      Element  : in     Asis.Element;
      Negative : in     Boolean;
      Label    : in     TenDRA.Small);

   procedure Ada_Call
     (State   : access States.State;
      Element : in     Asis.Element;
      Callee  : in     Asis.Declaration);

   function Call_Parameters
     (Element : Asis.Element) return Asis.Association_List;

   --------------
   -- Ada_Call --
   --------------

   procedure Ada_Call
     (State   : access States.State;
      Element : in     Asis.Element;
      Callee  : in     Asis.Declaration)
   is
      use Asis;
      use States;
      use Asis.Elements;
      use Asis.Expressions;


      B      : TenDRA.Streams.Memory_Stream
        renames State.Units (TAGDEF).all;
      Count  : TenDRA.Small := 0;
      List   : Asis.Association_List := Call_Parameters (Element);
      Caller : array (List'Range) of Boolean := (others => False);
      Tags   : array (List'Range) of TenDRA.Small;
   begin
      for J in List'Range loop
         declare
            Param : constant Asis.Declaration
              := Enclosing_Element (Formal_Parameter (List (J)));
         begin
            if Utils.Out_By_Copy_Parameter (Param) then
               Caller (J) := True;
               Tags (J) := State.Unit_Total (TAGDEF, Tag);
               Inc (State.Unit_Total (TAGDEF, Tag));
               Count := Count + 1;
            end if;
         end;
      end loop;

      Output.TDF (B, c_apply_general_proc);

      if Statement_Kind (Element) = A_Procedure_Call_Statement then
         Output.TDF (B, c_top);
      else
         raise Error;
      end if;

      Output.No_Option (B);

      if Is_Nil (Callee) then
         raise Error;
      else
         declare
            Name : Asis.Defining_Name := XASIS.Utils.Declaration_Name (Callee);
            Proc : TenDRA.Small := Find_Proc (State, Name);
         begin
            Output.TDF (B, c_obtain_tag);
            Output.TDF (B, c_make_tag);
            Output.TDFINT (B, Proc);
         end;
      end if;

      Output.List_Count (B, Count);

      for J in List'Range loop
         if Caller (J) then
            declare
               use XASIS.Classes;
               Param : constant Asis.Declaration
                 := Enclosing_Element (Formal_Parameter (List (J)));
               Tipe  : Type_Info := Type_Of_Declaration (Param);
               Shp   : TenDRA.Small := Find_Shape (State, Tipe);
            begin
               Output.TDF (B, c_make_otagexp);
               Output.TDF (B, c_make_tag);
               Output.TDFINT (B, Tags (J));

               if Mode_Kind (Param) = An_Out_Mode then
                  Output.TDF (B, c_make_value);
                  Output.TDF (B, c_shape_apply_token);
                  Output.TDF (B, c_make_tok);
                  Output.TDFINT (B, Shp);
                  Output.BITSTREAM (B, Empty);
               else
                  Compile (State, Actual_Parameter (List (J)), Tipe);
               end if;
            end;
         end if;
      end loop;

      Output.TDF (B, c_make_callee_list);
      Output.List_Count (B, List'Length - Count);

      for J in List'Range loop
         if not Caller (J) then
            declare
               use XASIS.Classes;
               Param : constant Asis.Declaration
                 := Enclosing_Element (Formal_Parameter (List (J)));
               Tipe  : Type_Info := Type_Of_Declaration (Param);
            begin
               --  State.Address := False;  --  TODO by ref
               Compile (State, Actual_Parameter (List (J)), Tipe);
            end;
         end if;
      end loop;

      --  postlude

      if Count = 0 then
         Output.TDF (B, c_make_top);
      elsif Count > 1 then
         Output.TDF (B, c_sequence);
         Output.List_Count (B, Count - 1);
      end if;

      for J in List'Range loop
         if Caller (J) then
            declare
               use XASIS.Classes;
               Param : constant Asis.Declaration
                 := Enclosing_Element (Formal_Parameter (List (J)));
               Tipe  : Type_Info := Type_Of_Declaration (Param);
            begin
               Output.TDF (B, c_assign);
               Compile (State, Actual_Parameter (List (J)), Tipe);
               Output.TDF (B, c_obtain_tag);
               Output.TDF (B, c_make_tag);
               Output.TDFINT (B, Tags (J));
            end;
         end if;
      end loop;
   end Ada_Call;

   ----------------
   -- Apply_Name --
   ----------------

   procedure Apply_Name
     (State   : access States.State;
      Element : in     Asis.Element;
      L_Value : in     Boolean := False)
   is
      use States;

      B      : TenDRA.Streams.Memory_Stream
        renames State.Units (TAGDEF).all;
      Name   : Asis.Defining_Name :=
        Asis.Expressions.Corresponding_Name_Definition (Element);
   begin
      Apply_Defining_Name (B, State, Name, L_Value);
   end Apply_Name;

   -------------------------
   -- Apply_Defining_Name --
   -------------------------

   procedure Apply_Defining_Name
     (B       : in out TenDRA.Streams.Memory_Stream;
      State   : access States.State;
      Name    : in     Asis.Defining_Name;
      L_Value : in     Boolean := False;
      Unit    : in     States.Unit_Kinds := States.TAGDEF)
   is
      use States;

      Tok    : TenDRA.Small := Find_Name (State, Name, Unit);
      Params : aliased Streams.Memory_Stream;
   begin
      Token.Initialize (Params, Name_Token);
      Output.TDF (Params, c_make_nat);

      if L_Value then
         Output.TDFINT (Params, 1);
      else
         Output.TDFINT (Params, 0);
      end if;

      Output.TDF (B, c_exp_apply_token);
      Output.TDF (B, c_make_tok);
      Output.TDFINT (B, Tok);
      Output.BITSTREAM (B, Params);
   end Apply_Defining_Name;

   ---------------------
   -- Call_Parameters --
   ---------------------

   function Call_Parameters
     (Element : Asis.Element) return Asis.Association_List
   is
      use Asis;
   begin
      if Elements.Element_Kind (Element) = An_Expression then
         return Asis.Expressions.Function_Call_Parameters (Element, True);
      else
         return Asis.Statements.Call_Statement_Parameters (Element, True);
      end if;
   end Call_Parameters;

   -------------
   -- Compile --
   -------------

   procedure Compile
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Tipe     : in     XASIS.Classes.Type_Info)
   is
      use Asis;
      use States;
      use Asis.Expressions;
      B     : TenDRA.Streams.Memory_Stream
        renames State.Units (TAGDEF).all;
   begin
      case Elements.Expression_Kind (Element) is
         when An_Integer_Literal =>
            declare
               use XASIS.Classes;

               Var : TenDRA.Small := Find_Variety (State, Tipe);
               Img : Wide_String  := Value_Image (Element);
               Val : Small        := Small'Wide_Value (Img);
            begin
               Output.TDF (B, c_make_int);
               Output.TDF (B, c_var_apply_token);
               Output.TDF (B, c_make_tok);
               Output.TDFINT (B, Var);
               Output.BITSTREAM (B, Empty);
               Output.TDF (B, c_make_signed_nat);
               Output.TDFBOOL (B, False);
               Output.TDFINT (B, Val);
            end;
--        | A_Real_Literal
--        | A_String_Literal
         when An_Identifier
--        | An_Operator_Symbol
           =>
            Identifier (State, Element);
--        | A_Character_Literal
         when An_Enumeration_Literal =>
            Apply_Name (State, Element);

--        | An_Explicit_Dereference
         when A_Function_Call =>
            Function_Call (State, Element, Tipe);
--        | An_Indexed_Component
--        | A_Slice
--        | A_Selected_Component
--        | An_Attribute_Reference
--        | A_Record_Aggregate
--        | An_Extension_Aggregate
--        | A_Positional_Array_Aggregate
--        | A_Named_Array_Aggregate
         when An_And_Then_Short_Circuit
           | An_Or_Else_Short_Circuit
           =>
            Short_Circuit (State, Element, False);
--        | An_In_Range_Membership_Test
--        | A_Not_In_Range_Membership_Test
--        | An_In_Type_Membership_Test
--        | A_Not_In_Type_Membership_Test
--        | A_Null_Literal
         when A_Parenthesized_Expression =>
            Compile (State, Expression_Parenthesized (Element), Tipe);
--        | A_Type_Conversion
--        | A_Qualified_Expression
--        | An_Allocation_From_Subtype
--        | An_Allocation_From_Qualified_Expression
         when others =>
            raise States.Error;
      end case;
   end Compile;

   ---------------------
   -- Compile_Boolean --
   ---------------------

   procedure Compile_Boolean
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Negative : in     Boolean)
   is
      use States;
      use Asis.Expressions;

      B      : TenDRA.Streams.Memory_Stream
        renames State.Units (TAGDEF).all;
   begin
      case Elements.Expression_Kind (Element) is
         when A_Function_Call =>
            Function_Call_Boolean (State, Element, Negative);

         when An_And_Then_Short_Circuit
           | An_Or_Else_Short_Circuit
           =>
            Short_Circuit (State, Element, Negative);

         when A_Parenthesized_Expression =>
            Compile_Boolean (State,
                             Expression_Parenthesized (Element),
                             Negative);

--        | A_Type_Conversion
--        | A_Qualified_Expression

         when others =>

            if Negative then
               Output.TDF (B, c_not);
            end if;

            Compile
              (State,
               Element,
               XASIS.Classes.Type_From_Declaration (XASIS.Types.Boolean));
      end case;
   end Compile_Boolean;

   ---------------------
   -- Compile_Boolean --
   ---------------------

   procedure Compile_Boolean
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Negative : in     Boolean;
      Label    : in     TenDRA.Small)
   is
      use States;
      use Asis.Expressions;

      B      : TenDRA.Streams.Memory_Stream
        renames State.Units (TAGDEF).all;
   begin
      case Elements.Expression_Kind (Element) is
         when A_Function_Call =>
            Function_Call_Boolean (State, Element, Negative, Label);

         when An_And_Then_Short_Circuit
           | An_Or_Else_Short_Circuit
           =>
            Short_Circuit (State, Element, Negative, Label);

         when A_Parenthesized_Expression =>
            Compile_Boolean
              (State, Expression_Parenthesized (Element), Negative, Label);
--        | A_Type_Conversion
--        | A_Qualified_Expression

         when others =>

            declare
               Tok    : TenDRA.Small := Find_Support (State, Boolean_Jump);
               Params : aliased Streams.Memory_Stream;
               Saved  : Stream_Access := State.Units (TAGDEF);
            begin
               Token.Initialize (Params, Boolean_Jump);

               Output.TDF (Params, c_make_nat);

               if Negative then
                  Output.TDFINT (Params, 1);
               else
                  Output.TDFINT (Params, 0);
               end if;

               State.Units (TAGDEF) := Params'Unchecked_Access;

               Compile
                 (State,
                  Element,
                  XASIS.Classes.Type_From_Declaration (XASIS.Types.Boolean));

               State.Units (TAGDEF) := Saved;

               Output.TDF (Params, c_make_label);
               Output.TDFINT (Params, Label);
               Output.TDF (B, c_exp_apply_token);
               Output.TDF (B, c_make_tok);
               Output.TDFINT (B, Tok);
               Output.BITSTREAM (B, Params);
            end;
      end case;
   end Compile_Boolean;

   --------------------------
   -- Corresponding_Callee --
   --------------------------

   function Corresponding_Callee
     (Element : Asis.Element) return Asis.Declaration
   is
      use Asis;
   begin
      if Elements.Element_Kind (Element) = An_Expression then
         return Asis.Expressions.Corresponding_Called_Function (Element);
      else
         return Asis.Statements.Corresponding_Called_Entity (Element);
      end if;
   end Corresponding_Callee;

   -------------------
   -- Function_Call --
   -------------------

   procedure Function_Call
     (State   : access States.State;
      Element : in     Asis.Element;
      Tipe    : in     XASIS.Classes.Type_Info)
   is
      Callee : Asis.Declaration := Corresponding_Callee (Element);
   begin
      if Asis.Elements.Is_Nil (Callee) then
         null;  --  dispatch or attribute
         raise States.Error;
      else
         case Utils.Convention (Callee) is
            when Utils.Intrinsic =>
               if XASIS.Classes.Is_Boolean (Tipe) then
                  Intrinsic.Function_Call_Boolean
                    (State, Element, Callee, False);
               else
                  Intrinsic.Function_Call
                    (State, Element, Callee);
               end if;
            when Utils.Ada =>
               Ada_Call (State, Element, Callee);
            when others =>
               raise States.Error;
         end case;
      end if;
   end Function_Call;

   ---------------------------
   -- Function_Call_Boolean --
   ---------------------------

   procedure Function_Call_Boolean
     (State    : access States.State;
      Element  : in     Asis.Element;
      Negative : in     Boolean)
   is
      use States;
      Callee : Asis.Declaration := Corresponding_Callee (Element);
      B      : TenDRA.Streams.Memory_Stream
        renames State.Units (TAGDEF).all;
   begin
      if Asis.Elements.Is_Nil (Callee) then
         null;  --  dispatch or attribute
         raise States.Error;
      else
         case Utils.Convention (Callee) is
            when Utils.Intrinsic =>
               Intrinsic.Function_Call_Boolean
                 (State, Element, Callee, Negative);
            when Utils.Ada =>
               if Negative then
                  Output.TDF (B, c_not);
               end if;

               Ada_Call (State, Element, Callee);
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
      Negative : in     Boolean;
      Label    : in     TenDRA.Small)
   is
      use States;
      Callee : Asis.Declaration := Corresponding_Callee (Element);
      B      : TenDRA.Streams.Memory_Stream
        renames State.Units (TAGDEF).all;
   begin
      if Asis.Elements.Is_Nil (Callee) then
         null;  --  dispatch or attribute
         raise States.Error;
      else
         case Utils.Convention (Callee) is
            when Utils.Intrinsic =>
               Intrinsic.Function_Call_Boolean
                 (State, Element, Callee, Negative, Label);
            when Utils.Ada =>
               declare
                  use States;
                  Tok    : TenDRA.Small := Find_Support (State, Boolean_Jump);
                  Params : aliased Streams.Memory_Stream;
                  Saved  : Stream_Access := State.Units (TAGDEF);
               begin
                  Token.Initialize (Params, Boolean_Jump);

                  Output.TDF (Params, c_make_nat);

                  if Negative then
                     Output.TDFINT (Params, 1);
                  else
                     Output.TDFINT (Params, 0);
                  end if;

                  State.Units (TAGDEF) := Params'Unchecked_Access;
                  Ada_Call (State, Element, Callee);
                  State.Units (TAGDEF) := Saved;

                  Output.TDF (Params, c_make_label);
                  Output.TDFINT (Params, Label);
                  Output.TDF (B, c_exp_apply_token);
                  Output.TDF (B, c_make_tok);
                  Output.TDFINT (B, Tok);
                  Output.BITSTREAM (B, Params);
               end;
            when others =>
               raise States.Error;
         end case;
      end if;
   end Function_Call_Boolean;

   ----------------
   -- Identifier --
   ----------------

   procedure Identifier
     (State   : access States.State;
      Element : in     Asis.Element;
      L_Value : in     Boolean := False)
   is
      use States;
      use Asis.Expressions;
      use XASIS.Classes;

      Name  : Asis.Defining_Name :=
        Corresponding_Name_Definition (Element);
      Level : Positive := XASIS.Utils.Lexic_Level (Name);
   begin
      if Level = 1
        --  or else Level = State.Level
        or True
      then
         Apply_Name (State, Element, L_Value);
      else
         raise States.Error;
      end if;
   end Identifier;

   -------------------
   -- Short_Circuit --
   -------------------

   procedure Short_Circuit
     (State    : access States.State;
      Element  : in     Asis.Element;
      Negative : in     Boolean)
   is
      use Asis;
      use States;

      B       : TenDRA.Streams.Memory_Stream
        renames State.Units (TAGDEF).all;
      Params  : aliased Streams.Memory_Stream;
      Saved   : Stream_Access := State.Units (TAGDEF);
      Label   : Small;
      Tok     : TenDRA.Small;
   begin
      Tok := Find_Support (State, Boolean_Value);
      Token.Initialize (Params, Boolean_Value);
      State.Units (TAGDEF) := Params'Unchecked_Access;
      Label := State.Labels (TAGDEF);
      Inc (State.Labels (TAGDEF));
      Output.TDF (Params, c_make_label);
      Output.TDFINT (Params, Label);

      Short_Circuit (State, Element, Negative, Label);

      State.Units (TAGDEF) := Saved;
      Output.TDF (B, c_exp_apply_token);
      Output.TDF (B, c_make_tok);
      Output.TDFINT (B, Tok);
      Output.BITSTREAM (B, Params);
   end Short_Circuit;

   -------------------
   -- Short_Circuit --
   -------------------

   procedure Short_Circuit
     (State    : access States.State;
      Element  : in     Asis.Element;
      Negative : in     Boolean;
      Label    : in     TenDRA.Small)
   is
      use Asis;
      use States;
      use Asis.Expressions;

      Kind      : Expression_Kinds := Elements.Expression_Kind (Element);
      Not_Label : TenDRA.Small;
   begin
      if Kind = An_And_Then_Short_Circuit xor Negative then
         Output.TDF (State.Units (TAGDEF).all, c_sequence);
         Output.List_Count (State.Units (TAGDEF).all, 1);

         Compile_Boolean (State,
                          Short_Circuit_Operation_Left_Expression (Element),
                          Negative => Negative,
                          Label    => Label);

         Compile_Boolean (State,
                          Short_Circuit_Operation_Right_Expression (Element),
                          Negative => Negative,
                          Label    => Label);
      else
         Not_Label := State.Labels (TAGDEF);
         Inc (State.Labels (TAGDEF));
         Output.TDF (State.Units (TAGDEF).all, c_conditional);
         Output.TDF (State.Units (TAGDEF).all, c_make_label);
         Output.TDFINT (State.Units (TAGDEF).all, Not_Label);

         Compile_Boolean (State,
                          Short_Circuit_Operation_Left_Expression (Element),
                          Negative => Negative,
                          Label    => Not_Label);

         Compile_Boolean (State,
                          Short_Circuit_Operation_Right_Expression (Element),
                          Negative => Negative,
                          Label    => Label);
      end if;
   end Short_Circuit;

   -----------------
   -- Target_Name --
   -----------------

   procedure Target_Name
     (State    : access States.State;
      Element  : in     Asis.Expression)
   is
      use Asis.Expressions;
   begin
      case Elements.Expression_Kind (Element) is
         when An_Identifier
           =>
            Identifier (State, Element, L_Value => True);
         when A_Parenthesized_Expression =>
            Target_Name (State, Expression_Parenthesized (Element));
         when others =>
            raise States.Error;
      end case;
   end Target_Name;

end Expression;


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
