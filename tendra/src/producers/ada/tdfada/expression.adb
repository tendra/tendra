with TenDRA;
with TenDRA.Types;
with TenDRA.Output;
with TenDRA.Streams;

with XASIS.Types;
with XASIS.Utils;
with XASIS.Static;
with XASIS.Classes;
with XASIS.Fractions;
with XASIS.Integers;

with Asis.Elements;
with Asis.Statements;
with Asis.Extensions;
with Asis.Expressions;
with Asis.Declarations;

with Token;
with Utils;
with Ranges;
with Intrinsic;
with Declaration;

with Ada.Wide_Text_IO;

package body Expression is
   use Asis;
   use TenDRA;
   use TenDRA.Types;

   procedure Identifier
     (State    : access States.State;
      Element  : in     Asis.Element;
      L_Value  : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);

   procedure Short_Circuit
     (State    : access States.State;
      Element  : in     Asis.Element;
      Negative : in     Boolean;
      Label    : in     TenDRA.Small;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);

   procedure Range_Test
     (State    : access States.State;
      Element  : in     Asis.Element;
      Negative : in     Boolean;
      Label    : in     TenDRA.Small;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);

   procedure Subtype_Test
     (State    : access States.State;
      Element  : in     Asis.Element;
      Negative : in     Boolean;
      Label    : in     TenDRA.Small;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);

   procedure Ada_Call
     (State    : access States.State;
      Element  : in     Asis.Element;
      Callee   : in     Asis.Declaration;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);

   procedure Attribute_Call
     (State    : access States.State;
      Element  : in     Asis.Element;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);

   function Call_Parameters
     (Element : Asis.Element) return Asis.Association_List;

   procedure Output_Boolean
     (State    : access States.State;
      Value    : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);

   function Corresponding_Callee
     (Element : Asis.Element) return Asis.Declaration;

   procedure Compile_Internal
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);

   procedure Type_Conversion
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);

   procedure Qualified_Expression
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);

   generic
      with procedure Compile_Labeled
        (State    : access States.State;
         Element  : in     Asis.Element;
         Negative : in     Boolean;
         Label    : in     TenDRA.Small;
         Static   : in     Boolean;
         B        : in out Stream'Class;
         Unit     : in     States.Unit_Kinds);
   procedure Compile_To_Label
     (State    : access States.State;
      Element  : in     Asis.Element;
      Negative : in     Boolean;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);

   Small_Size : XASIS.Integers.Value := XASIS.Integers.Zero;

   ---------------------
   -- Apply_Attribute --
   ---------------------

   procedure Apply_Attribute
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info;
      Param : in out Stream'Class;
      Unit  : in     States.Unit_Kinds;
      Kind  : in     Asis.Attribute_Kinds)
   is
      Decl : constant Asis.Declaration := XASIS.Classes.Get_Declaration (Tipe);
   begin
      Apply_Attribute (State, Decl, Param, Unit, Kind);
   end Apply_Attribute;

   ---------------------
   -- Apply_Attribute --
   ---------------------

   procedure Apply_Attribute
     (State : access States.State;
      Decl  : in     Asis.Declaration;
      Param : in out Stream'Class;
      Unit  : in     States.Unit_Kinds;
      Kind  : in     Asis.Attribute_Kinds)
   is
      use States;
      Top   : Streams.Memory_Stream;
      Limit : constant Small := Find_Attribute (State, Decl, Kind, Unit);
   begin
      Output.TDF (Param, c_exp_apply_token);
      Output.TDF (Param, c_make_tok);
      Output.TDFINT (Param, Limit);

      if Kind = A_First_Attribute or Kind = A_Last_Attribute then
         Streams.Expect (Top, Dummy, (1 => (EXP_SORT, Singular, False)));
         Output.TDF (Top, c_make_top);
         Output.BITSTREAM (Param, Top);
      else
         Output.BITSTREAM (Param, Empty);
      end if;
   end Apply_Attribute;

   ----------------------
   -- Apply_Type_Param --
   ----------------------

   procedure Apply_Type_Param
     (State : access States.State;
      Tipe  : in     XASIS.Classes.Type_Info;
      Param : in out Stream'Class;
      Unit  : in     States.Unit_Kinds;
      Kind  : in     States.Type_Param_Kinds)
   is
      use States;
      Limit : constant Small := Find_Type_Param (State, Tipe, Kind, Unit);
   begin
      Output.TDF (Param, c_exp_apply_token);
      Output.TDF (Param, c_make_tok);
      Output.TDFINT (Param, Limit);
      Output.BITSTREAM (Param, Empty);
   end Apply_Type_Param;

   ----------------------
   -- Compile_To_Label --
   ----------------------

   procedure Compile_To_Label
     (State    : access States.State;
      Element  : in     Asis.Element;
      Negative : in     Boolean;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use Asis;
      use States;

      Label   : Small := State.Labels (Unit);
   begin
      Inc (State.Labels (Unit));
      Output.TDF (B, c_conditional);
      Output.TDF (B, c_make_label);
      Output.TDFINT (B, Label);

      begin
         Output.TDF (B, c_sequence);
         Output.List_Count (B, 1);
         Compile_Labeled (State, Element, Negative, Label, Static, B, Unit);
         Output_Boolean (State, True, B, Unit);
      end;

      Output_Boolean (State, False, B, Unit);
   end Compile_To_Label;

   procedure Short_Circuit_Bool is new Compile_To_Label (Short_Circuit);
   procedure Range_Test_Bool    is new Compile_To_Label (Range_Test);
   procedure Subtype_Test_Bool  is new Compile_To_Label (Subtype_Test);

   --------------
   -- Ada_Call --
   --------------

   procedure Ada_Call
     (State    : access States.State;
      Element  : in     Asis.Element;
      Callee   : in     Asis.Declaration;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use Asis;
      use States;
      use Asis.Elements;
      use Asis.Expressions;

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
               Tags (J) := State.Unit_Total (Unit, Tag);
               Inc (State.Unit_Total (Unit, Tag));
               Count := Count + 1;
            end if;
         end;
      end loop;

      Output.TDF (B, c_apply_general_proc);

      if Statement_Kind (Element) = A_Procedure_Call_Statement then
         Output.TDF (B, c_top);
      else
         declare
            use XASIS.Classes;

            Result : constant Asis.Expression :=
              XASIS.Utils.Get_Result_Profile (Callee);
            Tipe   : constant Type_Info := Type_From_Subtype_Mark (Result);
         begin
            Declaration.Output_Shape (State, Tipe, B, Unit);
         end;
      end if;

      Output.No_Option (B);

      if Is_Nil (Callee) then
         raise Error;
      else
         declare
            Name : Asis.Defining_Name := XASIS.Utils.Declaration_Name (Callee);
            Proc : TenDRA.Small := Find_Proc (State, Name, Unit);
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
            begin
               Output.TDF (B, c_make_otagexp);
               Output.TDF (B, c_make_tag);
               Output.TDFINT (B, Tags (J));

               if Mode_Kind (Param) = An_Out_Mode then
                  Output.TDF (B, c_make_value);
                  Declaration.Output_Shape (State, Tipe, B, Unit);
               else
                  Compile
                    (State, Actual_Parameter (List (J)), Tipe, False, B, Unit);
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
               Param : constant Asis.Declaration :=
                 Enclosing_Element (Formal_Parameter (List (J)));
               Tipe  : Type_Info := Type_Of_Declaration (Param);
            begin
               --  State.Address := False;  --  TODO by ref
               Compile
                 (State, Actual_Parameter (List (J)), Tipe, False, B, Unit);
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
               Param : constant Asis.Declaration :=
                 Enclosing_Element (Formal_Parameter (List (J)));
               Tipe  : Type_Info := Type_Of_Declaration (Param);
            begin
               Output.TDF (B, c_assign);
               Target_Name (State, Actual_Parameter (List (J)), B, Unit);
               Output.TDF (B, c_obtain_tag);
               Output.TDF (B, c_make_tag);
               Output.TDFINT (B, Tags (J));
            end;
         end if;
      end loop;
   end Ada_Call;

   --------------------
   -- Attribute_Call --
   --------------------

   procedure Attribute_Call
     (State    : access States.State;
      Element  : in     Asis.Element;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use States;
      use XASIS.Utils;
      use XASIS.Classes;

      Attr        : Asis.Expression := Asis.Expressions.Prefix (Element);
      Prefix      : Asis.Expression := Asis.Expressions.Prefix (Attr);
      Kind        : Asis.Attribute_Kinds :=
        Asis.Elements.Attribute_Kind (Attr);
      Decl        : Asis.Declaration :=
        Selected_Name_Declaration (Prefix, False);
      Prefix_Type : Type_Info := Type_From_Declaration (Decl);
      List        : Asis.Association_List := Call_Parameters (Element);
      Types       : Asis.Declaration_List (List'Range) :=
        Get_Attribute_Profile (Decl, Kind);
      Param       : Streams.Memory_Stream;
      Token       : Small;

      procedure Compile_Arguments (Param : in out Stream'Class) is
         use Asis.Expressions;
         Tipe     : Type_Info;
         Arg_Type : Asis.Declaration;
      begin
         for J in List'Range loop
            Tipe := Type_From_Declaration (Types (J));

            if Is_Universal (Tipe) then
               Arg_Type := Corresponding_Expression_Type
                 (Actual_Parameter (List (J)));
               Tipe := Type_From_Declaration (Arg_Type);

               if Is_Universal (Tipe) then
                  if Is_Integer (Tipe) then
                     Tipe := T.Root_Integer;
                  elsif Is_Real (Tipe) then
                     Tipe := T.Root_Real;
                  else
                     raise Error;
                  end if;
               end if;
            end if;

            Compile (State,
                     Actual_Parameter (List (J)),
                     Tipe,
                     Static, Param, Unit);
         end loop;
      end Compile_Arguments;

      procedure Static_Attribute_Call is
      begin
         case Kind is
            when A_Min_Attribute =>
               if Is_Float_Point (Tipe) then
                  Output.TDF (B, c_floating_minimum);
               else
                  Output.TDF (B, c_minimum);
               end if;

               Compile_Arguments (B);
            when A_Max_Attribute =>
               if Is_Float_Point (Tipe) then
                  Output.TDF (B, c_floating_maximum);
               else
                  Output.TDF (B, c_maximum);
               end if;

               Compile_Arguments (B);
            when A_Succ_Attribute =>
               if Is_Modular_Integer (Tipe) then
                  Output.TDF (B, c_rem1);
                  Output.TDF (B, c_impossible);
                  Output.TDF (B, c_impossible);

                  Output.TDF (B, c_plus);
                  Output.TDF (B, c_wrap);
                  Compile_Arguments (B);
                  Output.TDF (B, c_make_int);
                  Output_Universal_Variety (State, Prefix_Type, B, Unit);
                  Output_Signed_Nat (B, 1);

                  Token := Find_Attribute
                    (State, Decl, A_Modulus_Attribute, Unit);
                  Output.TDF (B, c_exp_apply_token);
                  Output.TDF (B, c_make_tok);
                  Output.TDFINT (B, Token);
                  Output.BITSTREAM (B, Empty);
               elsif Is_Discrete (Tipe) then
                  Output.TDF (B, c_plus);
                  Output.TDF (B, c_impossible);
                  Compile_Arguments (B);
                  Output.TDF (B, c_make_int);
                  Output_Universal_Variety (State, Prefix_Type, B, Unit);
                  Output_Signed_Nat (B, 1);
               else
                  raise States.Error;
               end if;
            when A_Pred_Attribute =>
               if Is_Modular_Integer (Tipe) then
                  Output.TDF (B, c_rem1);
                  Output.TDF (B, c_impossible);
                  Output.TDF (B, c_impossible);

                  Output.TDF (B, c_minus);
                  Output.TDF (B, c_wrap);
                  Compile_Arguments (B);
                  Output.TDF (B, c_make_int);
                  Output_Universal_Variety (State, Prefix_Type, B, Unit);
                  Output_Signed_Nat (B, 1);

                  Token := Find_Attribute
                    (State, Decl, A_Modulus_Attribute, Unit);
                  Output.TDF (B, c_exp_apply_token);
                  Output.TDF (B, c_make_tok);
                  Output.TDFINT (B, Token);
                  Output.BITSTREAM (B, Empty);
               elsif Is_Discrete (Tipe) then
                  Output.TDF (B, c_minus);
                  Output.TDF (B, c_impossible);
                  Compile_Arguments (B);
                  Output.TDF (B, c_make_int);
                  Output_Universal_Variety (State, Prefix_Type, B, Unit);
                  Output_Signed_Nat (B, 1);
               else
                  raise States.Error;
               end if;
            when A_Pos_Attribute =>
               if Is_Boolean (Prefix_Type) then
                  Output.TDF (B, c_change_variety);
                  Output.TDF (B, c_continue);
                  Output_Universal_Variety (State, T.Root_Integer, B, Unit);
               end if;

               Compile_Arguments (B);
            when A_Val_Attribute =>
               if Is_Boolean (Prefix_Type) then
                  Output_Change_Variety (State, Prefix_Type, B, Unit);
               end if;

               Compile_Arguments (B);
            when others =>
               raise States.Error;
         end case;
      end Static_Attribute_Call;
   begin
      if Static then
         Static_Attribute_Call;
         return;
      end if;

      case Kind is
         when A_Val_Attribute
           | A_Value_Attribute
           | An_Adjacent_Attribute
           | A_Ceiling_Attribute
           | A_Compose_Attribute
           | A_Copy_Sign_Attribute
           | A_Floor_Attribute
           | A_Fraction_Attribute
           | A_Leading_Part_Attribute
           | A_Machine_Attribute
           | A_Max_Attribute
           | A_Min_Attribute
           | A_Model_Attribute
           | A_Pred_Attribute
           | A_Remainder_Attribute
           | A_Round_Attribute
           | A_Rounding_Attribute
           | A_Scaling_Attribute
           | A_Succ_Attribute
           | A_Truncation_Attribute
           | An_Unbiased_Rounding_Attribute
           | A_Wide_Value_Attribute
           =>
            --  Attr result is the same as attr prefix
            null;

         when An_Exponent_Attribute
           | A_Pos_Attribute =>
            Output_Change_Variety (State, Tipe, B, Unit);

         when others =>
            raise States.Error;
      end case;

      Token := Find_Attribute (State, Decl, Kind, Unit);
      Output.TDF (B, c_exp_apply_token);
      Output.TDF (B, c_make_tok);
      Output.TDFINT (B, Token);

      Streams.Expect
        (Param, Dummy, (1 .. List'Length => (EXP_SORT, Singular, False)));

      Compile_Arguments (Param);

      Output.BITSTREAM (B, Param);
   end Attribute_Call;

   ----------------
   -- Apply_Name --
   ----------------

   procedure Apply_Name
     (State    : access States.State;
      Element  : in     Asis.Element;
      L_Value  : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use States;

      Name   : Asis.Defining_Name :=
        Asis.Expressions.Corresponding_Name_Definition (Element);
      Tok    : TenDRA.Small;
   begin
      if L_Value then
         Tok := Find_Name (State, Name, Unit);
      else
         Tok := Find_Value (State, Name, Unit);
      end if;

      Output.TDF (B, c_exp_apply_token);
      Output.TDF (B, c_make_tok);
      Output.TDFINT (B, Tok);
      Output.BITSTREAM (B, Empty);
   end Apply_Name;

   ---------------------
   -- Call_Parameters --
   ---------------------

   function Call_Parameters
     (Element : Asis.Element) return Asis.Association_List
   is
      use Asis;
      use Asis.Elements;
      use Asis.Expressions;
   begin
      if Element_Kind (Element) /= An_Expression then
         return Asis.Statements.Call_Statement_Parameters (Element, True);
      elsif Expression_Kind (Prefix (Element)) = An_Attribute_Reference then
         return Function_Call_Parameters (Element, False);
      else
         return Function_Call_Parameters (Element, True);
      end if;
   end Call_Parameters;

   -------------
   -- Compile --
   -------------

   procedure Compile
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use States;
      ---------------------------
      -- Cross_Static_Boundary --
      ---------------------------

      procedure Cross_Static_Boundary is
         Var   : Small := Find_Variety (State, Tipe, Unit);
      begin
         if XASIS.Classes.Is_Float_Point (Tipe) then
            Output.TDF (B, c_change_floating_variety);
            Output_Trap_Overflow (B);
            Output.TDF (B, c_flvar_apply_token);
            Output.TDF (B, c_make_tok);
            Output.TDFINT (B, Var);
            Output.BITSTREAM (B, Empty);
         elsif not XASIS.Classes.Is_Boolean (Tipe) then
            --  Convert from Universal_Integer to Tipe
            Output.TDF (B, c_change_variety);
            Output.TDF (B, c_continue);
            --  Output_Trap_Overflow (B);   TODO: why trap doesnt work?
            Output.TDF (B, c_var_apply_token);
            Output.TDF (B, c_make_tok);
            Output.TDFINT (B, Var);
            Output.BITSTREAM (B, Empty);
         end if;
      end Cross_Static_Boundary;

   begin
      if Utils.Is_Static (Element) then
         if not Static then
            Cross_Static_Boundary;
         end if;

         Computed_Static (State, Element, Tipe, B, Unit);
      else
         Compile_Internal (State, Element, Tipe, Static, B, Unit);
      end if;
   end Compile;

   --------------------------
   -- First_Last_Attribute --
   --------------------------

   procedure First_Last_Attribute
     (State    : access States.State;
      Prefix   : in     Asis.Expression;
      Kind     : in     Asis.Attribute_Kinds;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Exps     : in     Asis.Expression_List := Asis.Nil_Element_List)
   is
      use Asis;
      use States;
      use XASIS.Utils;
      use XASIS.Classes;
      use Asis.Expressions;

      Decl        : constant Asis.Declaration :=
        Selected_Name_Declaration (Prefix, True);
      Token       : Small;
      Prefix_Type : constant Type_Info := Type_From_Declaration (Decl);
      Root_Type   : Type_Info;
      Param       : Streams.Memory_Stream;
      Base        : constant array (Boolean)
        of Type_Param_Kinds := (False => Base_Lower, True => Base_Upper);
   begin
      if Kind /= A_First_Attribute and Kind /= A_Last_Attribute then
         raise States.Error;
      end if;

      if Static then
         if Is_Float_Point (Prefix_Type) then
            Output.TDF (B, c_change_floating_variety);
            Output.TDF (B, c_impossible);
            Output_Universal_Variety (State, Prefix_Type, B, Unit);
         elsif not Is_Boolean (Prefix_Type) then
            Output.TDF (B, c_change_variety);
            Output.TDF (B, c_continue);
            Output_Universal_Variety (State, Prefix_Type, B, Unit);
         end if;
      end if;

      Output.TDF (B, c_exp_apply_token);
      Output.TDF (B, c_make_tok);

      if (Is_Signed_Integer (Prefix_Type)
        or Is_Float_Point (Prefix_Type)
        or Is_Fixed_Point (Prefix_Type))
        and then not Is_Constrained (Prefix)
      then
         Token := Find_Type_Param
           (State, Prefix_Type, Base (Kind = A_Last_Attribute), Unit);

         Output.TDFINT (B, Token);
         Output.BITSTREAM (B, Empty);
      else
         Token := Find_Attribute (State, Decl, Kind, Unit);
         Output.TDFINT (B, Token);
         Streams.Expect
           (Param, Dummy, (1 => (EXP_SORT, Singular, False)));

         if Exps'Length > 0 then
            Root_Type := T.Root_Integer;
            Compile (State, Exps (1), Root_Type, True, Param, Unit);
         else
            Output.TDF (Param, c_make_top);
         end if;

         Output.BITSTREAM (B, Param);
      end if;
   end First_Last_Attribute;

   ----------------------
   -- Compile_Internal --
   ----------------------

   procedure Compile_Internal
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use Asis;
      use States;
      use Asis.Expressions;

      procedure Attribute_Reference is
         Exps        : constant Asis.Expression_List :=
           Attribute_Designator_Expressions (Element);
         Kind        : Attribute_Kinds :=
           Asis.Elements.Attribute_Kind (Element);
      begin
         case Kind is
            when A_First_Attribute | A_Last_Attribute =>
               First_Last_Attribute
                 (State, Prefix (Element), Kind, Static, B, Unit, Exps);

            when A_Modulus_Attribute
              | A_Denorm_Attribute
              | A_Machine_Emax_Attribute
              | A_Machine_Emin_Attribute
              | A_Machine_Mantissa_Attribute
              | A_Machine_Overflows_Attribute
              | A_Machine_Radix_Attribute
              | A_Machine_Rounds_Attribute
              | A_Max_Size_In_Storage_Elements_Attribute
              | A_Model_Emin_Attribute
              | A_Model_Epsilon_Attribute
              | A_Model_Mantissa_Attribute
              | A_Model_Small_Attribute
              | A_Safe_First_Attribute
              | A_Safe_Last_Attribute
              | A_Signed_Zeros_Attribute
              =>
               declare
                  Decl  : constant Asis.Declaration :=
                    XASIS.Utils.Selected_Name_Declaration
                      (Prefix (Element), True);
                  Token : constant Small :=
                    Find_Attribute (State, Decl, Kind, Unit);
               begin
                  if not Static then
                     case Kind is
                        when A_Modulus_Attribute
                          | A_Machine_Emax_Attribute
                          | A_Machine_Emin_Attribute
                          | A_Machine_Mantissa_Attribute
                          | A_Machine_Radix_Attribute
                          | A_Max_Size_In_Storage_Elements_Attribute
                          | A_Model_Emin_Attribute
                          | A_Model_Epsilon_Attribute
                          | A_Model_Mantissa_Attribute
                          | A_Model_Small_Attribute
                          | A_Safe_First_Attribute
                          | A_Safe_Last_Attribute
                          =>
                           Output_Change_Variety (State, Tipe, B, Unit);
                        when others =>
                          null;
                     end case;
                  end if;

                  Output.TDF (B, c_exp_apply_token);
                  Output.TDF (B, c_make_tok);
                  Output.TDFINT (B, Token);
                  Output.BITSTREAM (B, Empty);
               end;
            when others =>
               raise States.Error;
         end case;
      end Attribute_Reference;

   begin
      case Elements.Expression_Kind (Element) is
         when An_Integer_Literal
           | A_Real_Literal
           | A_String_Literal
           | A_Character_Literal
           | An_Enumeration_Literal
           =>  --  expected to be static & defined
            raise States.Error;
         when An_Identifier
--        | An_Operator_Symbol
           =>
            if Static then
               declare
                  use Asis.Declarations;
                  Decl : constant Asis.Declaration :=
                    Corresponding_Name_Declaration (Element);
               begin
                  case Asis.Elements.Declaration_Kind (Decl) is
                     when An_Object_Renaming_Declaration =>
                        Compile (State,
                                 Renamed_Entity (Decl),
                                 XASIS.Classes.Type_Of_Declaration (Decl),
                                 Static, B, Unit);
                     when A_Constant_Declaration =>
                        Compile (State,
                                 Initialization_Expression (Decl),
                                 XASIS.Classes.Type_Of_Declaration (Decl),
                                 Static, B, Unit);
                     when An_Integer_Number_Declaration
                       | A_Real_Number_Declaration =>
                        Compile (State,
                                 Initialization_Expression (Decl),
                                 Tipe,
                                 Static, B, Unit);
                     when others =>
                        raise Error;
                  end case;
               end;
            else
               Identifier
                 (State, Element, L_Value => False, B => B, Unit => Unit);

            end if;
--        | An_Explicit_Dereference
         when A_Function_Call =>
            Function_Call (State, Element, Tipe, Static, B, Unit);
--        | An_Indexed_Component
--        | A_Slice
--        | A_Selected_Component
         when An_Attribute_Reference =>
            Attribute_Reference;
--        | A_Record_Aggregate
--        | An_Extension_Aggregate
--        | A_Positional_Array_Aggregate
--        | A_Named_Array_Aggregate
         when An_And_Then_Short_Circuit
           | An_Or_Else_Short_Circuit
           =>
            Short_Circuit_Bool (State, Element, False, Static, B, Unit);
         when An_In_Range_Membership_Test =>
            Range_Test_Bool (State, Element, False, Static, B, Unit);
         when A_Not_In_Range_Membership_Test =>
            Range_Test_Bool (State, Element, True, Static, B, Unit);
         when An_In_Type_Membership_Test =>
            Subtype_Test_Bool (State, Element, False, Static, B, Unit);
         when A_Not_In_Type_Membership_Test =>
            Subtype_Test_Bool (State, Element, True, Static, B, Unit);
--        | A_Null_Literal
         when A_Parenthesized_Expression =>
            Compile (State, Expression_Parenthesized (Element),
                     Tipe, Static, B, Unit);
         when A_Type_Conversion =>
            Type_Conversion (State, Element, Tipe, Static, B, Unit);

         when A_Qualified_Expression =>
            Qualified_Expression (State, Element, Tipe, Static, B, Unit);
--        | An_Allocation_From_Subtype
--        | An_Allocation_From_Qualified_Expression
         when others =>
            raise States.Error;
      end case;
   end Compile_Internal;

   ---------------------
   -- Compile_Boolean --
   ---------------------

   procedure Compile_Boolean
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Negative : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use States;
      use Asis.Expressions;

      procedure Function_Call_Boolean;

      Static   : constant Boolean := Utils.Is_Static (Element);

      ---------------------------
      -- Function_Call_Boolean --
      ---------------------------

      procedure Function_Call_Boolean is
         Callee : Asis.Declaration := Corresponding_Callee (Element);
      begin
         if Asis.Elements.Is_Nil (Callee) then
            --  dispatch or attribute

            if Negative then
               Invert_Boolean (State, B, Unit);
            end if;

            Attribute_Call
              (State, Element, XASIS.Classes.T.Boolean, Static, B, Unit);
         else
            case Utils.Convention (Callee) is
               when Utils.Intrinsic =>
                  Intrinsic.Function_Call_Boolean
                    (State, Element, Callee, Negative, Static, B, Unit);
               when Utils.Ada =>
                  if Negative then
                     Invert_Boolean (State, B, Unit);
                  end if;

                  Ada_Call (State, Element, Callee, B, Unit);
               when others =>
                  raise States.Error;
            end case;
         end if;
      end Function_Call_Boolean;
   begin
      case Elements.Expression_Kind (Element) is
         when A_Function_Call =>
            Function_Call_Boolean;

         when An_And_Then_Short_Circuit
           | An_Or_Else_Short_Circuit
           =>
            Short_Circuit_Bool (State, Element, Negative, Static, B, Unit);

         when A_Parenthesized_Expression
           =>
            Compile_Boolean (State,
                             Expression_Parenthesized (Element),
                             Negative,
                             B, Unit);

         when An_In_Range_Membership_Test =>
            Range_Test_Bool (State, Element, Negative, Static, B, Unit);
         when A_Not_In_Range_Membership_Test =>
            Range_Test_Bool (State, Element, not Negative, Static, B, Unit);
         when An_In_Type_Membership_Test =>
            Subtype_Test_Bool (State, Element, Negative, Static, B, Unit);
         when A_Not_In_Type_Membership_Test =>
            Subtype_Test_Bool (State, Element, not Negative, Static, B, Unit);

         when A_Type_Conversion
           | A_Qualified_Expression =>
            Compile_Boolean (State,
                             Converted_Or_Qualified_Expression (Element),
                             Negative,
                             B, Unit);

         when others =>

            if Negative then
               Invert_Boolean (State, B, Unit);
            end if;

            Compile
              (State,
               Element,
               XASIS.Classes.T.Boolean,
               Static, B, Unit);
      end case;
   end Compile_Boolean;

   ---------------------
   -- Compile_Boolean --
   ---------------------

   procedure Compile_Boolean
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Negative : in     Boolean;
      Label    : in     TenDRA.Small;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use States;
      use Asis.Expressions;

      procedure Function_Call_Boolean;

      Static   : constant Boolean := Utils.Is_Static (Element);

      procedure Common_Jump is
         Tok    : constant TenDRA.Small :=
           Find_Support (State, Boolean_Jump, Unit);
         Params : Streams.Memory_Stream;
      begin
         Token.Initialize (Params, Boolean_Jump);

         Output.TDF (Params, c_make_nat);

         if Negative then
            Output.TDFINT (Params, 1);
         else
            Output.TDFINT (Params, 0);
         end if;

         Compile
           (State,
            Element,
            XASIS.Classes.T.Boolean,
            Static, Params, Unit);

         Output.TDF (Params, c_make_label);
         Output.TDFINT (Params, Label);
         Output.TDF (B, c_exp_apply_token);
         Output.TDF (B, c_make_tok);
         Output.TDFINT (B, Tok);
         Output.BITSTREAM (B, Params);
      end Common_Jump;

      ---------------------------
      -- Function_Call_Boolean --
      ---------------------------

      procedure Function_Call_Boolean is
         Callee : Asis.Declaration := Corresponding_Callee (Element);
      begin
         if Asis.Elements.Is_Nil (Callee) then
            --  dispatch or attribute
            Common_Jump;
            raise States.Error;
         else
            case Utils.Convention (Callee) is
               when Utils.Intrinsic =>
                  Intrinsic.Function_Call_Boolean
                    (State, Element, Callee, Negative, Label, Static, B, Unit);
               when Utils.Ada =>
                  Common_Jump;
               when others =>
                  raise States.Error;
            end case;
         end if;
      end Function_Call_Boolean;

   begin  --  Compile_Boolean (Label)
      if Static and then Utils.Is_Defined (Element) then
         Common_Jump;
         return;
      end if;

      case Elements.Expression_Kind (Element) is
         when A_Function_Call =>
            Function_Call_Boolean;

         when An_And_Then_Short_Circuit
           | An_Or_Else_Short_Circuit
           =>
            Short_Circuit (State, Element, Negative, Label, Static, B, Unit);

         when A_Parenthesized_Expression
           =>
            Compile_Boolean
              (State, Expression_Parenthesized (Element),
               Negative, Label, B, Unit);

         when An_In_Range_Membership_Test =>
            Range_Test (State, Element, Negative, Label, Static, B, Unit);

         when A_Not_In_Range_Membership_Test =>
            Range_Test (State, Element, not Negative, Label, Static, B, Unit);

         when An_In_Type_Membership_Test =>
            Subtype_Test (State, Element, Negative, Label, Static, B, Unit);

         when A_Not_In_Type_Membership_Test =>
            Subtype_Test
              (State, Element, not Negative, Label, Static, B, Unit);

         when A_Type_Conversion
           | A_Qualified_Expression =>
            Compile_Boolean
              (State, Converted_Or_Qualified_Expression (Element),
               Negative, Label, B, Unit);

         when others =>
            Common_Jump;
      end case;
   end Compile_Boolean;

   ---------------------
   -- Computed_Static --
   ---------------------

   procedure Computed_Static
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Tipe     : in     XASIS.Classes.Type_Info;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use States;

      procedure Output_Value (X : XASIS.Integers.Value) is
         use XASIS.Integers;

         procedure Write (Part  : Value; Last  : Boolean := True) is
            Val  : Small;
            Next : constant Value := Part / Small_Size;
         begin
            if Next = Zero then
               Val := Small'Value (Image (Part));
               Output.TDFINT (B, Val, Last => Last);
            else
               Write (Next, False);
               Val := Small'Value (Image (Part mod Small_Size));
               Output.TDFINT (B, Val, Last => Last, First => False);
            end if;
         end Write;

      begin
         if Small_Size = Zero then
            Small_Size := Literal (Small'Image (Small'Last)) + One;
         end if;

         Output.TDF (B, c_make_signed_nat);
         Output.TDFBOOL (B, X < Zero);
         Write (abs X);
      end Output_Value;

      procedure Defined_Static is
         Value : constant XASIS.Integers.Value :=
           XASIS.Static.Integer (XASIS.Static.Evaluate (Element));
      begin
         Output.TDF (B, c_make_int);
         Output_Universal_Variety (State, Tipe, B, Unit);
         Output_Value (Value);
      end Defined_Static;

      procedure Defined_Static_Float is
         use XASIS.Fractions;
         use type I.Value;

         Result : constant Fraction :=
           XASIS.Static.Fraction (XASIS.Static.Evaluate (Element));
         Image  : constant String := I.Image (abs Result.Numerator);
      begin
         if Result.Denominator /= I.One then
            Output.TDF (B, c_floating_div);
            Output.TDF (B, c_impossible);
         end if;

         Output.TDF (B, c_make_floating);
         Output_Universal_Variety (State, Tipe, B, Unit);
         Output.TDF (B, c_to_nearest);

         if Result < Zero then
            Output.TDF (B, c_true);
         else
            Output.TDF (B, c_false);
         end if;

         Output.TDF (B, c_make_string);
         Output.TDFSTRING (B, Image);
         Output.TDF (B, c_make_nat);
         Output.TDFINT (B, 10);
         Output_Value (Result.Exponent);

         if Result.Denominator /= I.One then
            Output.TDF (B, c_make_floating);
            Output_Universal_Variety (State, Tipe, B, Unit);
            Output.TDF (B, c_to_nearest);
            Output.TDF (B, c_false);
            Output.TDF (B, c_make_string);
            Output.TDFSTRING (B, I.Image (Result.Denominator));
            Output.TDF (B, c_make_nat);

            Output.TDFINT (B, 10);
            Output_Signed_Nat (B, 0);
         end if;
      end Defined_Static_Float;

      procedure Defined_Static_Fixed is
         use XASIS.Classes;
         Result : constant XASIS.Static.Value :=
           XASIS.Static.Evaluate (Element);
         Value : constant XASIS.Integers.Value :=
           XASIS.Static.To_Fixed (Result, Tipe);
      begin
         Output.TDF (B, c_make_int);
         Output_Universal_Variety (State, Tipe, B, Unit);
         Output_Value (Value);
      end Defined_Static_Fixed;
   begin
      if Utils.Is_Defined (Element) then
         if XASIS.Classes.Is_Fixed_Point (Tipe) then
            Defined_Static_Fixed;
         elsif XASIS.Classes.Is_Real (Tipe) then
            Defined_Static_Float;
         else
            Defined_Static;
         end if;
      else
         Compile_Internal (State, Element, Tipe, True, B, Unit);
      end if;
   end Computed_Static;

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
     (State    : access States.State;
      Element  : in     Asis.Element;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      Callee : Asis.Declaration := Corresponding_Callee (Element);
      Prefix : Asis.Expression;
   begin
      if Asis.Elements.Is_Nil (Callee) then
         Prefix := Asis.Expressions.Prefix (Element);

         if Elements.Expression_Kind (Prefix) = An_Attribute_Reference then
            Attribute_Call (State, Element, Tipe, Static, B, Unit);
         else
            Ada.Wide_Text_IO.Put_Line (Asis.Elements.Debug_Image (Element));
            null;  --  dispatch
            raise States.Error;
         end if;
      else
         case Utils.Convention (Callee) is
            when Utils.Intrinsic =>
               if XASIS.Classes.Is_Boolean (Tipe) then
                  Intrinsic.Function_Call_Boolean
                    (State, Element, Callee, False, Static, B, Unit);
               else
                  Intrinsic.Function_Call
                    (State, Element, Tipe, Callee, Static, B, Unit);
               end if;
            when Utils.Ada =>
               Ada_Call (State, Element, Callee, B, Unit);
            when others =>
               raise States.Error;
         end case;
      end if;
   end Function_Call;

   ----------------
   -- Identifier --
   ----------------

   procedure Identifier
     (State    : access States.State;
      Element  : in     Asis.Element;
      L_Value  : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
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
         Apply_Name (State, Element, L_Value, B, Unit);
      else
         raise States.Error;
      end if;
   end Identifier;

   --------------------
   -- Invert_Boolean --
   --------------------

   procedure Invert_Boolean
     (State    : access States.State;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use States;
   begin
      Output.TDF (B, c_xor);
      Output_Boolean (State, True, B, Unit);
   end Invert_Boolean;

   ---------------------------
   -- Output_Change_Variety --
   ---------------------------

   procedure Output_Change_Variety
     (State    : access States.State;
      Tipe     : in     XASIS.Classes.Type_Info;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Trap     : in     Boolean := False)
   is
      Var   : constant Small := States.Find_Variety (State, Tipe, Unit);
   begin
      if XASIS.Classes.Is_Float_Point (Tipe) then
         Output.TDF (B, c_change_floating_variety);
      else
         Output.TDF (B, c_change_variety);
      end if;

      if Trap then
         Output_Trap_Overflow (B);
      else
         Output.TDF (B, c_continue);
      end if;

      Declaration.Output_Variety (State, Tipe, B, Unit);
   end Output_Change_Variety;

   --------------------
   -- Output_Boolean --
   --------------------

   procedure Output_Boolean
     (State    : access States.State;
      Value    : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use States;
      use XASIS.Classes;

      Tipe  : Type_Info := T.Boolean;
      Var   : Small := Find_Variety (State, Tipe, Unit);
   begin
      Output.TDF (B, c_make_int);
      Output.TDF (B, c_var_apply_token);
      Output.TDF (B, c_make_tok);
      Output.TDFINT (B, Var);
      Output.BITSTREAM (B, Empty);
      Output_Signed_Nat (B, Boolean'Pos (Value));
   end Output_Boolean;

   ----------------
   -- Output_Int --
   ----------------

   procedure Output_Int
     (State    : access States.State;
      Tipe     : in     XASIS.Classes.Type_Info;
      Value    : in     TenDRA.Small;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Negative : in     Boolean := False)
   is
      Var   : constant Small := States.Find_Variety (State, Tipe, Unit);
   begin
      Output.TDF (B, c_make_int);
      Output.TDF (B, c_var_apply_token);
      Output.TDF (B, c_make_tok);
      Output.TDFINT (B, Var);
      Output.BITSTREAM (B, States.Empty);
      Output_Signed_Nat (B, Value, Negative);
   end Output_Int;

   -----------------------
   -- Output_Signed_Nat --
   -----------------------

   procedure Output_Signed_Nat
     (B        : in out Stream'Class;
      Value    : in     TenDRA.Small;
      Negative : in     Boolean := False) is
   begin
      Output.TDF (B, c_make_signed_nat);
      Output.TDFBOOL (B, Negative);
      Output.TDFINT (B, Value);
   end Output_Signed_Nat;

   --------------------------
   -- Output_Trap_Overflow --
   --------------------------

   procedure Output_Trap_Overflow (B : in out Stream'Class) is
   begin
         Output.TDF (B, c_trap);
         Output.List_Count (B, 1);
         Output.TDF (B, c_overflow);
   end Output_Trap_Overflow;

   ------------------------------
   -- Output_Universal_Variety --
   ------------------------------

   procedure Output_Universal_Variety
     (State    : access States.State;
      Tipe     : in     XASIS.Classes.Type_Info;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      Var : constant Small := Universal_Variety (State, Tipe, Unit);
   begin
      if XASIS.Classes.Is_Float_Point (Tipe) then
         Output.TDF (B, c_flvar_apply_token);
      else
         Output.TDF (B, c_var_apply_token);
      end if;

      Output.TDF (B, c_make_tok);
      Output.TDFINT (B, Var);
      Output.BITSTREAM (B, States.Empty);
   end Output_Universal_Variety;


   --------------------------
   -- Qualified_Expression --
   --------------------------

   procedure Qualified_Expression
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use XASIS.Classes;
      use Asis.Expressions;
      Target    : constant Asis.Expression :=
        Converted_Or_Qualified_Subtype_Mark (Element);
      Expr      : constant Asis.Expression :=
        Converted_Or_Qualified_Expression (Element);
      Type_Decl : constant Asis.Declaration :=
        Corresponding_Expression_Type (Expr);
      Expr_Type : constant Type_Info := Type_From_Declaration (Type_Decl);

      ------------------
      -- Compile_Expr --
      ------------------

      procedure Compile_Expr (B : in out Stream'Class) is
      begin
         Compile
           (State   => State,
            Element => Expr,
            Tipe    => Expr_Type,
            Static  => Static,
            B       => B,
            Unit    => Unit);
      end Compile_Expr;

   begin -- Qualified_Expression
      if Is_Constrained (Target) then
         declare
            use States;
            Decl   : constant Asis.Declaration :=
              XASIS.Utils.Selected_Name_Declaration (Target, True);
            Tok    : TenDRA.Small;
            Params : Streams.Memory_Stream;
         begin
            if Is_Float_Point (Tipe) then
               Tok := Find_Support (State, Float_In_Bounds, Unit);
               Token.Initialize (Params, Float_In_Bounds);
            else
               Tok := Find_Support (State, In_Bounds, Unit);
               Token.Initialize (Params, In_Bounds);
            end if;


            Apply_Attribute (State, Decl, Params, Unit, A_First_Attribute);
            Apply_Attribute (State, Decl, Params, Unit, A_Last_Attribute);
            Compile_Expr (Params);

            Output.TDF (B, c_exp_apply_token);
            Output.TDF (B, c_make_tok);
            Output.TDFINT (B, Tok);
            Output.BITSTREAM (B, Params);
         end;
      else --  unconstrained
         Compile_Expr (B);
      end if;
   end Qualified_Expression;

   ----------------
   -- Range_Test --
   ----------------

   procedure Range_Test
     (State    : access States.State;
      Element  : in     Asis.Element;
      Negative : in     Boolean;
      Label    : in     TenDRA.Small;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use States;
      use XASIS.Static;
      Tok     : TenDRA.Small;
      Expr    : constant Asis.Expression :=
        Asis.Expressions.Membership_Test_Expression (Element);
      Rng     : constant Asis.Range_Constraint :=
        Asis.Expressions.Membership_Test_Range (Element);
      Tipe    : constant XASIS.Classes.Type_Info :=
        Utils.Membership_Test_Type (Element);
      Params  : Streams.Memory_Stream;
      Context : Ranges.Range_Context;
   begin
      Ranges.New_Context (State, Rng, Tipe, Static, B, Unit, Context);

      if XASIS.Classes.Is_Float_Point (Tipe) then
         Tok := Find_Support (State, Float_Test_Range_Jump, Unit);
         Token.Initialize (Params, Float_Test_Range_Jump);
      else
         Tok := Find_Support (State, Test_Range_Jump, Unit);
         Token.Initialize (Params, Test_Range_Jump);
      end if;

      Compile (State, Expr, Tipe, Static, Params, Unit);
      Ranges.Compile (State, Rng, Tipe, Static, Params, Unit, Context, Lower);
      Ranges.Compile (State, Rng, Tipe, Static, Params, Unit, Context, Upper);

      Output.TDF (Params, c_make_nat);

      if Negative then
         Output.TDFINT (Params, 1);
      else
         Output.TDFINT (Params, 0);
      end if;

      Output.TDF (Params, c_make_label);
      Output.TDFINT (Params, Label);

      Output.TDF (B, c_exp_apply_token);
      Output.TDF (B, c_make_tok);
      Output.TDFINT (B, Tok);
      Output.BITSTREAM (B, Params);
   end Range_Test;

   ------------------
   -- Subtype_Test --
   ------------------

   procedure Subtype_Test
     (State    : access States.State;
      Element  : in     Asis.Element;
      Negative : in     Boolean;
      Label    : in     TenDRA.Small;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use States;
      use XASIS.Static;
      use XASIS.Classes;

      Tok     : TenDRA.Small;
      Expr    : constant Asis.Expression :=
        Asis.Expressions.Membership_Test_Expression (Element);
      Subtipe : constant Asis.Expression :=
        Asis.Expressions.Membership_Test_Subtype_Mark (Element);
      Tipe    : constant XASIS.Classes.Type_Info :=
        Type_From_Subtype_Mark (Subtipe);
      Params  : Streams.Memory_Stream;
   begin
      if Is_Float_Point (Tipe) then
         Tok := Find_Support (State, Float_Test_Range_Jump, Unit);
         Token.Initialize (Params, Float_Test_Range_Jump);
      else
         Tok := Find_Support (State, Test_Range_Jump, Unit);
         Token.Initialize (Params, Test_Range_Jump);
      end if;

      Compile (State, Expr, Tipe, Static, Params, Unit);

      if Is_Constrained (Subtipe) then
         declare
            Decl   : constant Asis.Declaration :=
              XASIS.Utils.Selected_Name_Declaration (Subtipe, True);
         begin
            Apply_Attribute (State, Decl, Params, Unit, A_First_Attribute);
            Apply_Attribute (State, Decl, Params, Unit, A_Last_Attribute);
         end;
      elsif Is_Signed_Integer (Tipe) or Is_Real (Tipe) then
         Apply_Type_Param (State, Tipe, Params, Unit, Base_Lower);
         Apply_Type_Param (State, Tipe, Params, Unit, Base_Upper);
      else
         Apply_Attribute (State, Tipe, Params, Unit, A_First_Attribute);
         Apply_Attribute (State, Tipe, Params, Unit, A_Last_Attribute);
      end if;

      Output.TDF (Params, c_make_nat);

      if Negative then
         Output.TDFINT (Params, 1);
      else
         Output.TDFINT (Params, 0);
      end if;

      Output.TDF (Params, c_make_label);
      Output.TDFINT (Params, Label);

      Output.TDF (B, c_exp_apply_token);
      Output.TDF (B, c_make_tok);
      Output.TDFINT (B, Tok);
      Output.BITSTREAM (B, Params);
   end Subtype_Test;

   -------------------
   -- Short_Circuit --
   -------------------

   procedure Short_Circuit
     (State    : access States.State;
      Element  : in     Asis.Element;
      Negative : in     Boolean;
      Label    : in     TenDRA.Small;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use Asis;
      use States;
      use Asis.Expressions;

      Kind      : Expression_Kinds := Elements.Expression_Kind (Element);
      Not_Label : TenDRA.Small;
   begin
      if Kind = An_And_Then_Short_Circuit xor Negative then
         Output.TDF (B, c_sequence);
         Output.List_Count (B, 1);

         Compile_Boolean (State,
                          Short_Circuit_Operation_Left_Expression (Element),
                          Negative => Negative,
                          Label    => Label,
                          B => B, Unit => Unit);

         Compile_Boolean (State,
                          Short_Circuit_Operation_Right_Expression (Element),
                          Negative => Negative,
                          Label    => Label,
                          B => B, Unit => Unit);
      else
         Not_Label := State.Labels (Unit);
         Inc (State.Labels (Unit));
         Output.TDF (B, c_conditional);
         Output.TDF (B, c_make_label);
         Output.TDFINT (B, Not_Label);

         Compile_Boolean (State,
                          Short_Circuit_Operation_Left_Expression (Element),
                          Negative => Negative,
                          Label    => Not_Label,
                          B => B, Unit => Unit);

         Compile_Boolean (State,
                          Short_Circuit_Operation_Right_Expression (Element),
                          Negative => Negative,
                          Label    => Label,
                          B => B, Unit => Unit);
      end if;
   end Short_Circuit;

   -----------------
   -- Target_Name --
   -----------------

   procedure Target_Name
     (State    : access States.State;
      Element  : in     Asis.Expression;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use Asis.Expressions;
   begin
      case Elements.Expression_Kind (Element) is
         when An_Identifier
           =>
            Identifier (State, Element, True, B, Unit);
         when A_Parenthesized_Expression =>
            Target_Name (State, Expression_Parenthesized (Element), B, Unit);
         when others =>
            raise States.Error;
      end case;
   end Target_Name;

   ---------------------
   -- Type_Conversion --
   ---------------------

   procedure Type_Conversion
     (State    : access States.State;
      Element  : in     Asis.Expression;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds)
   is
      use XASIS.Classes;
      use Asis.Expressions;
      Target    : constant Asis.Expression :=
        Converted_Or_Qualified_Subtype_Mark (Element);
      Expr      : constant Asis.Expression :=
        Converted_Or_Qualified_Expression (Element);
      Type_Decl : constant Asis.Declaration :=
        Corresponding_Expression_Type (Expr);
      Expr_Type : constant Type_Info := Type_From_Declaration (Type_Decl);

      ------------------
      -- Compile_Expr --
      ------------------

      procedure Compile_Expr (B : in out Stream'Class) is
      begin
         Compile
           (State   => State,
            Element => Expr,
            Tipe    => Expr_Type,
            Static  => Static,
            B       => B,
            Unit    => Unit);
      end Compile_Expr;

      -------------------
      -- Apply_Support --
      -------------------

      procedure Apply_Support
        (B    : in out Stream'Class;
         Kind : in     States.Support_Kinds)
      is
         use States;
         Tok    : constant TenDRA.Small := Find_Support (State, Kind, Unit);
         Params : Streams.Memory_Stream;
      begin
         Token.Initialize (Params, Kind);
         --  Left:
         Compile_Expr (Params);
         --  Small:

         if Kind = Fixed_To_Fixed then
            Apply_Attribute
              (State, Expr_Type, Params, Unit, A_Small_Attribute);
            Apply_Attribute
              (State, Tipe, Params, Unit, A_Small_Attribute);
         elsif Kind = Fixed_To_Int or Kind = Fixed_To_Float then
            Apply_Attribute
              (State, Expr_Type, Params, Unit, A_Small_Attribute);
         else
            Apply_Attribute
              (State, Tipe, Params, Unit, A_Small_Attribute);
         end if;

         if Static then
            Output_Universal_Variety (State, Expr_Type, Params, Unit);
            Output_Universal_Variety (State, Tipe, Params, Unit);
            Output.TDF (Params, c_continue);
         else
            Declaration.Output_Variety
              (State, Expr_Type, Params, Unit);
            Declaration.Output_Variety (State, Tipe, Params, Unit);
            Output_Trap_Overflow (Params);
         end if;

         Output.TDF (B, c_exp_apply_token);
         Output.TDF (B, c_make_tok);
         Output.TDFINT (B, Tok);
         Output.BITSTREAM (B, Params);
      end Apply_Support;

      -------------
      -- Convert --
      -------------

      procedure Convert (B : in out Stream'Class) is
      begin
         if Is_Numeric (Tipe) then

            if Is_Integer (Tipe) then

               if Is_Integer (Expr_Type) then
                  Output_Change_Variety
                    (State, Tipe, B, Unit, Trap => not Static);
                  Compile_Expr (B);
               elsif Is_Float_Point (Expr_Type) then
                  Output.TDF (B, c_round_with_mode);

                  if Static then
                     Output.TDF (B, c_continue);
                     Output.TDF (B, c_to_nearest);
                     Output_Universal_Variety (State, Tipe, B, Unit);
                  else
                     Output_Trap_Overflow (B);
                     Output.TDF (B, c_to_nearest);
                     Declaration.Output_Variety (State, Tipe, B, Unit);
                  end if;

                  Compile_Expr (B);
               elsif Is_Fixed_Point (Expr_Type) then
                  Apply_Support (B, States.Fixed_To_Int);
               else
                  --  should never happen
                  raise States.Error;
               end if;

               --  end cast to Integer
            elsif Is_Decimal_Fixed_Point (Tipe) then
               --  Not implemented
               raise States.Error;

            elsif Is_Float_Point (Tipe) then

               if Is_Integer (Expr_Type) then
                  Output.TDF (B, c_float_int);

                  if Static then
                     Output.TDF (B, c_continue);
                     Output_Universal_Variety (State, Tipe, B, Unit);
                  else
                     Output_Trap_Overflow (B);
                     Declaration.Output_Variety (State, Tipe, B, Unit);
                  end if;

                  Compile_Expr (B);
               elsif Is_Float_Point (Expr_Type) then
                  Output_Change_Variety
                    (State, Tipe, B, Unit, Trap => not Static);
                  Compile_Expr (B);
               elsif Is_Fixed_Point (Expr_Type) then
                  Apply_Support (B, States.Fixed_To_Float);
               else
                  --  should never happen
                  raise States.Error;
               end if;

               --  end cast to float point
            elsif Is_Fixed_Point (Tipe) then
               if Is_Integer (Expr_Type) then
                  Apply_Support (B, States.Int_To_Fixed);
               elsif Is_Float_Point (Expr_Type) then
                  Apply_Support (B, States.Float_To_Fixed);
               elsif Is_Fixed_Point (Expr_Type) then
                  Apply_Support (B, States.Fixed_To_Fixed);
               else
                  --  should never happen
                  raise States.Error;
               end if;
            else
               --  should never happen
               raise States.Error;
            end if;
         elsif Is_Enumeration (Tipe) then
            -- TODO: to changed representation
            Compile_Expr (B);
         else
            raise States.Error;
         end if;
      end Convert;

   begin -- Type_Conversion
      if Is_Constrained (Target) then
         declare
            use States;
            Decl   : constant Asis.Declaration :=
              XASIS.Utils.Selected_Name_Declaration (Target, True);
            Tok    : TenDRA.Small;
            Params : Streams.Memory_Stream;
         begin
            if Is_Float_Point (Tipe) then
               Tok := Find_Support (State, Float_In_Bounds, Unit);
               Token.Initialize (Params, Float_In_Bounds);
            else
               Tok := Find_Support (State, In_Bounds, Unit);
               Token.Initialize (Params, In_Bounds);
            end if;


            Apply_Attribute (State, Decl, Params, Unit, A_First_Attribute);
            Apply_Attribute (State, Decl, Params, Unit, A_Last_Attribute);
            Convert (Params);

            Output.TDF (B, c_exp_apply_token);
            Output.TDF (B, c_make_tok);
            Output.TDFINT (B, Tok);
            Output.BITSTREAM (B, Params);
         end;
      elsif Is_Modular_Integer (Tipe) then  --  unconstrained modular
         declare
            use States;
            Tok    : constant TenDRA.Small :=
              Find_Support (State, In_Bounds, Unit);
            Params : Streams.Memory_Stream;
         begin
            Token.Initialize (Params, In_Bounds);

            Apply_Attribute (State, Tipe, Params, Unit, A_First_Attribute);
            Apply_Attribute (State, Tipe, Params, Unit, A_Last_Attribute);
            Convert (Params);

            Output.TDF (B, c_exp_apply_token);
            Output.TDF (B, c_make_tok);
            Output.TDFINT (B, Tok);
            Output.BITSTREAM (B, Params);
         end;
      else
         Convert (B);
      end if;

   end Type_Conversion;

   -----------------------
   -- Universal_Variety --
   -----------------------

   function Universal_Variety
     (State    : access States.State;
      Tipe     : in     XASIS.Classes.Type_Info;
      Unit     : in     States.Unit_Kinds) return TenDRA.Small
   is
      use XASIS.Classes;
      Var : TenDRA.Small;
   begin
      if Is_Boolean (Tipe) then
         Var := States.Find_Variety (State, Tipe, Unit);
      elsif Is_Fixed_Point (Tipe) then
         declare
            Tipe  : constant Type_Info := T.Universal_Fixed;
         begin
            Var := States.Find_Variety (State, Tipe, Unit);
         end;
      elsif Is_Real (Tipe) then
         declare
            Tipe  : constant Type_Info := T.Universal_Real;
         begin
            Var := States.Find_Variety (State, Tipe, Unit);
         end;
      else
         declare
            Tipe  : constant Type_Info := T.Universal_Integer;
         begin
            Var := States.Find_Variety (State, Tipe, Unit);
         end;
      end if;

      return Var;
   end Universal_Variety;

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
