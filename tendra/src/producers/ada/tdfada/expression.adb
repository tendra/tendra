with TenDRA;
with TenDRA.Types;
with TenDRA.Output;
with TenDRA.Streams;

with XASIS.Types;
with XASIS.Utils;
with XASIS.Static;
with XASIS.Classes;

with Asis.Elements;
with Asis.Statements;
with Asis.Extensions;
with Asis.Expressions;
with Asis.Declarations;

with Token;
with Utils;
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
      Static   : in     Boolean;
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

   procedure Output_Universal_Variety
     (State    : access States.State;
      Tipe     : in     XASIS.Classes.Type_Info;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds);

   procedure Output_Change_Variety
     (State    : access States.State;
      Tipe     : in     XASIS.Classes.Type_Info;
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
               Output.TDF (B, c_minimum);
               Compile_Arguments (B);
            when A_Max_Attribute =>
               Output.TDF (B, c_maximum);
               Compile_Arguments (B);
            when A_Succ_Attribute =>
               Output.TDF (B, c_plus);
               Output.TDF (B, c_impossible);
               Compile_Arguments (B);
               Output.TDF (B, c_make_int);
               Output_Universal_Variety (State, Prefix_Type, B, Unit);
               Output_Signed_Nat (B, 1);
            when A_Pred_Attribute =>
               Output.TDF (B, c_minus);
               Output.TDF (B, c_impossible);
               Compile_Arguments (B);
               Output.TDF (B, c_make_int);
               Output_Universal_Variety (State, Prefix_Type, B, Unit);
               Output_Signed_Nat (B, 1);
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
         if not XASIS.Classes.Is_Boolean (Tipe) then
            --  Convert from Universal_Integer to Tipe
            Output.TDF (B, c_change_variety);
            Output.TDF (B, c_continue);
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
         use XASIS.Utils;
         use XASIS.Classes;

         Decl        : Asis.Declaration;
         Token       : Small;
         Prefix_Type : Type_Info;
         Root_Type   : Type_Info;
         Param       : Streams.Memory_Stream;
         Exps        : constant Asis.Expression_List :=
           Attribute_Designator_Expressions (Element);
         Kind        : Attribute_Kinds :=
           Asis.Elements.Attribute_Kind (Element);
         Base        : constant array (Boolean)
           of Type_Param_Kinds := (False => Base_Lower, True => Base_Upper);
      begin
         case Kind is
            when A_First_Attribute | A_Last_Attribute =>
               Decl := Selected_Name_Declaration (Prefix (Element), True);
               Prefix_Type := Type_From_Declaration (Decl);

               if Static and not Is_Boolean (Prefix_Type) then
                  Output.TDF (B, c_change_variety);
                  Output.TDF (B, c_continue);
                  Output_Universal_Variety (State, Prefix_Type, B, Unit);
               end if;

               Output.TDF (B, c_exp_apply_token);
               Output.TDF (B, c_make_tok);

               if (Is_Signed_Integer (Prefix_Type)
                 or Is_Float_Point (Prefix_Type))
                 and then not Is_Constrained (Prefix (Element))
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
                                 XASIS.Classes.Type_From_Declaration (Decl),
                                 Static, B, Unit);
                     when A_Constant_Declaration =>
                        Compile (State,
                                 Initialization_Expression (Decl),
                                 XASIS.Classes.Type_From_Declaration (Decl),
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
            Short_Circuit (State, Element, False, Static, B, Unit);
--        | An_In_Range_Membership_Test
--        | A_Not_In_Range_Membership_Test
--        | An_In_Type_Membership_Test
--        | A_Not_In_Type_Membership_Test
--        | A_Null_Literal
         when A_Parenthesized_Expression =>
            Compile (State, Expression_Parenthesized (Element),
                     Tipe, Static, B, Unit);
--        | A_Type_Conversion
--        | A_Qualified_Expression
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
            Short_Circuit (State, Element, Negative, Static, B, Unit);

         when A_Parenthesized_Expression =>
            Compile_Boolean (State,
                             Expression_Parenthesized (Element),
                             Negative,
                             B, Unit);

--        | A_Type_Conversion
--        | A_Qualified_Expression

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

         when A_Parenthesized_Expression =>
            Compile_Boolean
              (State, Expression_Parenthesized (Element),
               Negative, Label, B, Unit);
--        | A_Type_Conversion
--        | A_Qualified_Expression

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

      procedure Defined_Static is
         Value : XASIS.Static.Value := XASIS.Static.Evaluate (Element);
         Image : Wide_String := XASIS.Static.Image (Value);
         Val   : Small;  --  TODO: Fix for values larger then Small
      begin
         Output.TDF (B, c_make_int);
         Output_Universal_Variety (State, Tipe, B, Unit);
         Output.TDF (B, c_make_signed_nat);

         if Image (Image'First) = '-' then
            Output.TDFBOOL (B, True);
            Val := Small'Wide_Value (Image (2 .. Image'Last));
         else
            Output.TDFBOOL (B, False);
            Val := Small'Wide_Value (Image);
         end if;

         Output.TDFINT (B, Val);
      end Defined_Static;
   begin
      if Utils.Is_Defined (Element) then
         Defined_Static;
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
         
         if Asis.Elements.Expression_Kind (Prefix) = An_Attribute_Reference then
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
                    (State, Element, Callee, Static, B, Unit);
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
      Unit     : in     States.Unit_Kinds)
   is
      Var   : constant Small := States.Find_Variety (State, Tipe, Unit);
   begin
      Output.TDF (B, c_change_variety);
      Output.TDF (B, c_continue);
      Output.TDF (B, c_var_apply_token);
      Output.TDF (B, c_make_tok);
      Output.TDFINT (B, Var);
      Output.BITSTREAM (B, States.Empty);
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
      Output.TDF (B, c_var_apply_token);
      Output.TDF (B, c_make_tok);
      Output.TDFINT (B, Var);
      Output.BITSTREAM (B, States.Empty);
   end Output_Universal_Variety;

   -------------------
   -- Short_Circuit --
   -------------------

   procedure Short_Circuit
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
         Short_Circuit (State, Element, Negative, Label, Static, B, Unit);
         Output_Boolean (State, True, B, Unit);
      end;

      Output_Boolean (State, False, B, Unit);
   end Short_Circuit;

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
