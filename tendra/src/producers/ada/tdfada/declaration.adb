with TenDRA;
with TenDRA.Types;
with TenDRA.Output;
with TenDRA.Streams;

with Token;
with Utils;
with Ranges;
with Statement;
with Expression;
with Type_Definition;

with XASIS.Utils;
with XASIS.Static;
with XASIS.Classes;

with Asis.Elements;
with Asis.Declarations;

package body Declaration is

   use States;
   use TenDRA;
   use TenDRA.Types;

   type Variable_Kind is (Identity, Variable, Token);

   procedure Subroutine
     (State    : access States.State;
      Element  : in     Asis.Declaration);

   procedure Compile_Local
     (State    : access States.State;
      Element  : in     Asis.Declaration);

   procedure Variable
     (State    : access States.State;
      Element  : in     Asis.Declaration);

   function Variable_Is
     (Element : Asis.Declaration) return Variable_Kind;

   procedure Make_Name_Token
     (State : access States.State;
      Name  : in     Asis.Defining_Name);

   procedure Make_Value_Token
     (State : access States.State;
      Name  : in     Asis.Defining_Name;
      Tipe  : in     XASIS.Classes.Type_Info;
      Const : in     Variable_Kind;
      Init  : in     Asis.Expression := Asis.Nil_Element);

   procedure Parameter
     (State   : access States.State;
      Element : in     Asis.Declaration;
      Write   : in     Boolean);

   Error : exception;

   -------------
   -- Compile --
   -------------

   procedure Compile
     (State    : access States.State;
      Decl     : in     Asis.Declaration)
   is
      use Asis;
      use Asis.Declarations;
   begin
      case Elements.Declaration_Kind (Decl) is
         when An_Ordinary_Type_Declaration =>
            Type_Definition.Compile (State, Type_Declaration_View (Decl));

--       | A_Task_Type_Declaration
--       | A_Protected_Type_Declaration
--       | An_Incomplete_Type_Declaration
--       | A_Private_Type_Declaration
--       | A_Private_Extension_Declaration
--       | A_Subtype_Declaration
         when A_Variable_Declaration | A_Constant_Declaration =>
            Variable (State, Decl);
--       | A_Deferred_Constant_Declaration
--       | A_Single_Task_Declaration
--       | A_Single_Protected_Declaration
--       | An_Integer_Number_Declaration
--       | A_Real_Number_Declaration
--       | An_Enumeration_Literal_Specification
--       | A_Discriminant_Specification
--       | A_Component_Declaration
--       | A_Loop_Parameter_Specification
--       | A_Procedure_Declaration
--       | A_Function_Declaration
--       | A_Parameter_Specification
         when A_Procedure_Body_Declaration | A_Function_Body_Declaration =>
            Subroutine (State, Decl);
         when A_Package_Declaration =>
            declare
               List : Element_List :=
                 Visible_Part_Declarative_Items (Decl)
                 & Private_Part_Declarative_Items (Decl);
            begin
               for J in List'Range loop
                  Compile (State, List (J));
               end loop;
            end;

         when A_Package_Body_Declaration =>
            declare
               List : Element_List := Body_Declarative_Items (Decl);
            begin
               for J in List'Range loop
                  Compile (State, List (J));
               end loop;
            end;

--       | An_Object_Renaming_Declaration
--       | An_Exception_Renaming_Declaration
--       | A_Package_Renaming_Declaration
--       | A_Procedure_Renaming_Declaration
--       | A_Function_Renaming_Declaration
--       | A_Generic_Package_Renaming_Declaration
--       | A_Generic_Procedure_Renaming_Declaration
--       | A_Generic_Function_Renaming_Declaration
--       | A_Task_Body_Declaration
--       | A_Protected_Body_Declaration
--       | An_Entry_Declaration
--       | An_Entry_Body_Declaration
--       | An_Entry_Index_Specification
--       | A_Procedure_Body_Stub
--       | A_Function_Body_Stub
--       | A_Package_Body_Stub
--       | A_Task_Body_Stub
--       | A_Protected_Body_Stub
--       | An_Exception_Declaration
--       | A_Choice_Parameter_Specification
--       | A_Generic_Procedure_Declaration
--       | A_Generic_Function_Declaration
--       | A_Generic_Package_Declaration
--       | A_Package_Instantiation
--       | A_Procedure_Instantiation
--       | A_Function_Instantiation
--       | A_Formal_Object_Declaration
--       | A_Formal_Type_Declaration
--       | A_Formal_Procedure_Declaration
--       | A_Formal_Function_Declaration
--       | A_Formal_Package_Declaration
--       | A_Formal_Package_Declaration_With_Box
         when others => null;
      end case;
   end Compile;

   -------------------
   -- Compile_Local --
   -------------------

   procedure Compile_Local
     (State    : access States.State;
      Element  : in     Asis.Declaration)
   is
   begin
      null;
   end Compile_Local;

   --------------------
   -- Loop_Parameter --
   --------------------

   procedure Loop_Parameter
     (State    : access States.State;
      Decl     : in     Asis.Declaration;
      Def      :    out Asis.Discrete_Subtype_Definition;
      Tag      :    out TenDRA.Small;
      Incr     :    out Boolean;
      Context  :    out Ranges.Range_Context)
   is
      use XASIS.Classes;
      use Asis.Declarations;
      use type Asis.Trait_Kinds;

      B     : TenDRA.Streams.Memory_Stream
        renames State.Units (TAGDEF).all;

      Trait   : constant Asis.Trait_Kinds := Asis.Elements.Trait_Kind (Decl);
      Tipe    : constant Type_Info := Type_Of_Declaration (Decl);
      List    : constant Asis.Defining_Name_List := Names (Decl);
      Lower   : XASIS.Static.Bound_Kinds;
   begin
      Tag := Find_Tag (State, List (1), TAGDEF, False);
      Def := Specification_Subtype_Definition (Decl);

      if Trait = Asis.A_Reverse_Trait then
         Incr  := False;
         Lower := XASIS.Static.Upper;
      else
         Incr  := True;
         Lower := XASIS.Static.Lower;
      end if;

      Ranges.New_Context_Discrete
        (State, Def, Tipe, False, B, TAGDEF, Context);

      Output.TDF (B, c_variable);
      Output.TDF (B, c_add_accesses);
      Output.TDF (B, c_no_other_read);
      Output.TDF (B, c_no_other_write);
      Output.TDF (B, c_make_tag);
      Output.TDFINT (B, Tag);

      Ranges.Compile_Discrete
        (State, Def, Tipe, False, B, TAGDEF, Context, Lower);

      Make_Value_Token (State, List (1), Tipe, Variable);
   end Loop_Parameter;

   ---------------------
   -- Make_Name_Token --
   ---------------------

   procedure Make_Name_Token
     (State : access States.State;
      Name  : in     Asis.Defining_Name)
   is
      T    : TenDRA.Streams.Memory_Stream
        renames State.Units (TOKDEF).all;
      D    : aliased Streams.Memory_Stream;
      Tok  : TenDRA.Small := Find_Name (State, Name, TOKDEF, False);
      Tag  : TenDRA.Small := Find_Tag (State, Name, TOKDEF);
   begin
      Streams.Expect
        (D, Dummy, ((TOKEN_DEFN_SORT, Singular, False),
                    (EXP_SORT, Singular, False)));
      Output.TDF (D, c_token_definition);
      Output.TDF (D, c_exp);
      Output.List_Count (D, 0);

      Output.TDF (D, c_obtain_tag);
      Output.TDF (D, c_make_tag);
      Output.TDFINT (D, Tag);

      Inc (State.Length (TOKDEF));
      Output.TDF (T, c_make_tokdef);
      Output.TDFINT (T, Tok);
      Output.No_Option (T);  --  signature
      Output.BITSTREAM (T, D);
   end Make_Name_Token;

   ----------------------
   -- Make_Value_Token --
   ----------------------

   procedure Make_Value_Token
     (State : access States.State;
      Name  : in     Asis.Defining_Name;
      Tipe  : in     XASIS.Classes.Type_Info;
      Const : in     Variable_Kind;
      Init  : in     Asis.Expression := Asis.Nil_Element)
   is
      T    : TenDRA.Streams.Memory_Stream
        renames State.Units (TOKDEF).all;
      D    : aliased Streams.Memory_Stream;
      Tok  : TenDRA.Small := Find_Value (State, Name, TOKDEF, False);
      Tag  : TenDRA.Small;
   begin
      Streams.Expect
        (D, Dummy, ((TOKEN_DEFN_SORT, Singular, False),
                    (EXP_SORT, Singular, False)));
      Output.TDF (D, c_token_definition);
      Output.TDF (D, c_exp);
      Output.List_Count (D, 0);

      if Const = Token then
         Expression.Compile (State, Init, Tipe, False, D, TOKDEF);
      else
         Tag := Find_Tag (State, Name, TOKDEF);

         if Const = Variable then
            Output.TDF (D, c_contents);
            Output_Shape (State, Tipe, D, TOKDEF);
         end if;

         Output.TDF (D, c_obtain_tag);
         Output.TDF (D, c_make_tag);
         Output.TDFINT (D, Tag);
      end if;

      Inc (State.Length (TOKDEF));
      Output.TDF (T, c_make_tokdef);
      Output.TDFINT (T, Tok);
      Output.No_Option (T);  --  signature
      Output.BITSTREAM (T, D);
   end Make_Value_Token;

   -------------
   -- New_Tag --
   -------------

   procedure New_Tag
     (State : access States.State;
      Link  : in     States.Linkage_Access)
   is
      use Asis;
      use States;
      use TenDRA;
      use TenDRA.Types;
      use XASIS.Classes;

--        function External
--          (Unit : Asis.Compilation_Unit;
--           Name : Asis.Element) return Boolean
--        is
--           use Asis.Compilation_Units;

--           Name_Unit : Asis.Compilation_Unit :=
--             Asis.Elements.Enclosing_Compilation_Unit (Name);
--        begin
--           return Text_Name (Unit) /= Text_Name (Name_Unit);
--        end External;

--        function Is_Proc (Decl : Asis.Declaration) return Boolean is
--           use Asis;
--        begin
--           case Asis.Elements.Declaration_Kind (Decl) is
--              when A_Variable_Declaration
--                | A_Constant_Declaration
--                | An_Enumeration_Literal_Specification
--                | A_Discriminant_Specification
--                | A_Component_Declaration
--                | A_Loop_Parameter_Specification
--                | A_Parameter_Specification
--                | An_Object_Renaming_Declaration
--                | An_Entry_Index_Specification
--                =>
--                 return False;
--              when
--                A_Procedure_Declaration
--                | A_Function_Declaration
--                | A_Procedure_Body_Declaration
--                | A_Function_Body_Declaration
--                | A_Procedure_Renaming_Declaration
--                | A_Function_Renaming_Declaration
--                | An_Entry_Declaration
--                | An_Entry_Body_Declaration
--                | A_Procedure_Body_Stub
--                | A_Function_Body_Stub
--                | A_Procedure_Instantiation
--                | A_Function_Instantiation
--                =>
--                 return True;
--              when others =>
--                 raise Error;
--           end case;
--        end Is_Proc;

      S     : TenDRA.Streams.Memory_Stream
        renames State.Units (TAGDEC).all;
      Decl  : Asis.Declaration :=
        Asis.Elements.Enclosing_Element (Link.Name);
      Tag   : Small;
      Shape : Small;
   begin
      if Elements.Declaration_Kind (Decl) = A_Constant_Declaration
        and then Variable_Is (Decl) = Token then
         return;
      elsif Link.Kind = States.Tag
        and then XASIS.Utils.Lexic_Level (Link.Name) > 1
      then
         return;
      end if;

      Tag := Find (State, Link.all, TAGDEC);
      Link.Usage := Link.Usage or Declared;
      Inc (State.Length (TAGDEC));

      case Link.Kind is
         when Proc_Tag =>
            Output.TDF (S, c_make_id_tagdec);
         when States.Tag =>
            if Variable_Is (Decl) = Identity then
               Output.TDF (S, c_make_id_tagdec);
            else
               Output.TDF (S, c_make_var_tagdec);
            end if;
         when others =>
            null;
      end case;

      Output.TDFINT (S, Tag);
      Output.No_Option (S);  --  access
      Output.No_Option (S);  --  signature

      if Link.Kind = Proc_Tag then
         Output.TDF (S, c_proc);
      else
         Shape := Find_Shape (State, Type_Of_Declaration (Decl), TAGDEC);
         Output.TDF (S, c_shape_apply_token);
         Output.TDF (S, c_make_tok);
         Output.TDFINT (S, Shape);
         Output.BITSTREAM (S, Empty);
      end if;
   end New_Tag;

   ------------------
   -- Output_Shape --
   ------------------

   procedure Output_Shape
     (State   : access States.State;
      Tipe    : in     XASIS.Classes.Type_Info;
      B       : in out TenDRA.Streams.Stream'Class;
      Unit    : in     States.Unit_Kinds)
   is
      Shape : Small := Find_Shape (State, Tipe, Unit);
   begin
      Output.TDF (B, c_shape_apply_token);
      Output.TDF (B, c_make_tok);
      Output.TDFINT (B, Shape);
      Output.BITSTREAM (B, Empty);
   end Output_Shape;

   ---------------
   -- Parameter --
   ---------------

   procedure Parameter
     (State   : access States.State;
      Element : in     Asis.Declaration;
      Write   : in     Boolean)
   is
      use Asis;
      use Asis.Declarations;
      use XASIS.Classes;
      B     : TenDRA.Streams.Memory_Stream
        renames State.Units (TAGDEF).all;

      List  : Asis.Defining_Name_List := Names (Element);
      Tipe  : Type_Info := Type_Of_Declaration (Element);
      Tag   : TenDRA.Small;
   begin
      for K in List'Range loop
         Tag := Find_Tag (State, List (K), Usage => False);
         Output.TDF (B, c_make_tagshacc);
         Output_Shape (State, Tipe, B, TAGDEF);

         if Write then
            Output.TDF (B, c_out_par);
         else
            Output.TDF (B, c_constant);
            --  Output.No_Option (B);  --  access
         end if;

         Output.TDF (B, c_make_tag);
         Output.TDFINT (B, Tag);
         Make_Name_Token (State, List (K));
         Make_Value_Token (State, List (K), Tipe, Variable);
      end loop;
   end Parameter;

   ----------------
   -- Subroutine --
   ----------------

   procedure Subroutine
     (State    : access States.State;
      Element  : in     Asis.Declaration)
   is
      use XASIS.Classes;
      use Asis.Declarations;

      B      : TenDRA.Streams.Memory_Stream
        renames State.Units (TAGDEF).all;
      Name   : Asis.Defining_Name := XASIS.Utils.Declaration_Name (Element);
      Tag    : TenDRA.Small := Find_Proc (State, Name, Usage => False);
      Param  : Asis.Declaration_List := Parameter_Profile (Element);
      Result : Asis.Expression := XASIS.Utils.Get_Result_Profile (Element);
      Decl   : Asis.Declaration_List := Body_Declarative_Items (Element);
      Stmt   : Asis.Statement_List   := Body_Statements (Element);
      Copy   : array (Param'Range) of Boolean := (others => False);
      Caller : Small := 0;
      Callee : Small := 0;
   begin
      for J in Param'Range loop
         if Utils.Out_By_Copy_Parameter (Param (J)) then
            Copy (J) := True;
            Caller := Caller + Names (Param (J))'Length;
         else
            Callee := Callee + Names (Param (J))'Length;
         end if;
      end loop;

      Inc (State.Length (TAGDEF));
      Output.TDF (B, c_make_id_tagdef);
      Output.TDFINT (B, Tag);
      Output.No_Option (B);  --  signature
      Output.TDF (B, c_make_general_proc);

      if Asis.Elements.Is_Nil (Result) then
         Output.TDF (B, c_top);
      else
         Output_Shape (State, Type_From_Subtype_Mark (Result), B, TAGDEF);
      end if;

      Output.No_Option (B);
      Output.List_Count (B, Caller);  --  caller_intro

      for J in Param'Range loop
         if Copy (J) then
            Parameter (State, Param (J), Write => True);
         end if;
      end loop;

      Output.List_Count (B, Callee);  --  callee_intro

      for J in Param'Range loop
         if not Copy (J) then
            Parameter (State, Param (J), Write => False);
         end if;
      end loop;

      for J in Decl'Range loop
         Compile (State, Decl (J));
      end loop;

      Output.TDF (B, c_sequence);
      Output.List_Count (B, 1);

      Statement.Compile (State, Stmt, null);

      Output.TDF (B, c_return);
      Output.TDF (B, c_make_top);
   end Subroutine;

   -----------------
   -- Variable_Is --
   -----------------

   function Variable_Is (Element : Asis.Declaration) return Variable_Kind is
      use Asis;
      use Asis.Elements;
      use XASIS.Classes;
      use Asis.Declarations;
      Init  : constant Asis.Expression := Initialization_Expression (Element);
      Tipe  : constant Type_Info := Type_Of_Declaration (Element);
   begin
      if Declaration_Kind (Element) = A_Constant_Declaration
        and Utils.By_Copy_Type (Tipe)
      then
         if Trait_Kind (Element) = An_Aliased_Trait then
            return Variable;
         elsif Utils.Is_Static (Init) then
            return Token;
         elsif XASIS.Utils.Lexic_Level (Names (Element) (1)) /= 1 then
            return Identity;
         end if;
      end if;

      return Variable;
   end Variable_Is;

   --------------
   -- Variable --
   --------------

   procedure Variable
     (State    : access States.State;
      Element  : in     Asis.Declaration)
   is
      use Asis;
      use Asis.Elements;
      use Asis.Declarations;
      use XASIS.Classes;
      B     : TenDRA.Streams.Memory_Stream
        renames State.Units (TAGDEF).all;

      -------------------
      -- Output_Access --
      -------------------

      procedure Output_Access is
         Kind  : constant Declaration_Kinds := Declaration_Kind (Element);
         Trait : constant Trait_Kinds := Trait_Kind (Element);
      begin
         if Kind = A_Constant_Declaration
           and Trait /= An_Aliased_Trait
         then
            Output.TDF (B, c_add_accesses);
            Output.TDF (B, c_constant);
            Output.TDF (B, c_add_accesses);
            Output.TDF (B, c_no_other_read);
            Output.TDF (B, c_no_other_write);
         elsif Kind = A_Constant_Declaration then
            Output.TDF (B, c_constant);
         elsif Trait /= An_Aliased_Trait then
            Output.TDF (B, c_add_accesses);
            Output.TDF (B, c_no_other_read);
            Output.TDF (B, c_no_other_write);
         else
            Output.No_Option (B);  --  access
         end if;
      end Output_Access;

      Init  : Asis.Expression := Initialization_Expression (Element);
      Tipe  : Type_Info := Type_Of_Declaration (Element);
      Tag   : TenDRA.Small;
      List  : Asis.Defining_Name_List := Names (Element);
      Level : Positive := XASIS.Utils.Lexic_Level (List (1));
      Const : Variable_Kind := Variable_Is (Element);
   begin
      for J in List'Range loop
         if Const /= Token then
            Tag := Find_Tag (State, List (J), TAGDEF, False);
         end if;

         if Const = Variable then
            if Level = 1 then
               Output.TDF (B, c_make_var_tagdef);
               Output.TDFINT (B, Tag);
               Output_Access;
               Output.No_Option (B);  --  signature
               Inc (State.Length (TAGDEF));
            else  --  Level > 1
               Output.TDF (B, c_variable);
               Output_Access;
               Output.TDF (B, c_make_tag);
               Output.TDFINT (B, Tag);
            end if;
         elsif Const = Identity then
            if Level = 1 then
               Output.TDF (B, c_make_id_tagdef);
               Output.TDFINT (B, Tag);
               Output.No_Option (B);  --  signature
               Inc (State.Length (TAGDEF));
            else  --  Level > 1
               Output.TDF (B, c_identify);
               Output.No_Option (B);  --  access
            end if;
         end if;

         if Const /= Token then
            if Asis.Elements.Is_Nil (Init) then
               Output.TDF (B, c_make_value);
               Output_Shape (State, Tipe, B, TAGDEF);
            else
               --  TODO: Variable elaboration if Init isn't static
               Expression.Compile (State, Init, Tipe, False, B, TAGDEF);
            end if;
         end if;

         if Const = Variable then
            Make_Name_Token (State, List (J));
         end if;

         Make_Value_Token (State, List (J), Tipe, Const, Init);

      end loop;
   end Variable;

end Declaration;


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
