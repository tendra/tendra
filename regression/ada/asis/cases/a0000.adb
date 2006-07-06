------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Check recognition of all Ada constructions.
--
--  This test containts all Ada 95 constructions except
--  A_Root_Type_Definition:
--    A_Root_Integer_Definition
--    A_Root_Real_Definition
--    A_Universal_Integer_Definition
--    A_Universal_Real_Definition
--    A_Universal_Fixed_Definition
--  A_Code_Statement

pragma Page;

with A0000A;
use  A0000A;
with A0000A.B;

with Ada.Calendar;

procedure A0000 is
   use type A0000A.Type_1;

   type Defining_Identifier is
     ('x',                             --  Defining_Character_Literal
      Defining_Enumeration_Literal);

   function "not"                      --  Defining_Operator_Symbol
     (Left : Integer) return Integer;

   --  Declaration_Kinds

   type Ordinary_Type_Declaration (Param : Boolean) is record
      case Param is
         when True =>
            Value : Integer;
         when others =>
            null;
      end case;
   end record;

   task type Task_Type_Declaration is
      entry Entry_Declaration;
      entry Run;
   end Task_Type_Declaration;

   protected type Protected_Type_Declaration is
      entry Entry_Body_Declaration;
   private
      State : Boolean;
   end Protected_Type_Declaration;

   type Incomplete_Type_Declaration;
   type Incomplete_Type_Declaration is range 1 .. 1;

   subtype Private_Type_Declaration is A0000A.Private_Type_Declaration;

   subtype Private_Extension_Declaration is
     A0000A.Private_Extension_Declaration;

   subtype Subtype_Declaration is Integer;

   Variable_Declaration : String (3 .. 20);

   Constant_Declaration : constant Integer := 1;

   Deferred_Constant_Declaration : constant Private_Type_Declaration :=
     A0000A.Deferred_Constant_Declaration;

   task Single_Task_Declaration is
      entry Run;
   end Single_Task_Declaration;

   protected Single_Protected_Declaration is
      entry Run;
   end Single_Protected_Declaration;

   Integer_Number_Declaration : constant := 1;
   Real_Number_Declaration    : constant := 3.1415;

   type Type_1 is (An_Enumeration_Literal_Specification);

   type Type_2 (Discriminant_Specification : Integer) is record
      Component_Declaration : Integer;
   end record;

   procedure Proc_1 is
   begin
      for Loop_Parameter_Specification in 1 .. 2 loop
        null;
      end loop;
   end Proc_1;

   procedure Procedure_Declaration;

   function Function_Declaration
     (Parameter_Specification : Integer) return Boolean;

   procedure Procedure_Body_Declaration is
   begin
      null;
   end Procedure_Body_Declaration;

   function Function_Body_Declaration return Integer is
   begin
      return 1;
   end Function_Body_Declaration;

   package Package_Declaration is
   end Package_Declaration;

   package Package_Body_Declaration is
      procedure Proc;
   end Package_Body_Declaration;

   package body Package_Body_Declaration is
      procedure Proc renames Procedure_Body_Declaration;
   end Package_Body_Declaration;

   Object_Renaming_Declaration : Integer renames Constant_Declaration;

   E : exception;
   Exception_Renaming_Declaration : exception renames E;

   package Package_Renaming_Declaration renames Package_Declaration;

   procedure Procedure_Renaming_Declaration renames Procedure_Declaration;

   function Function_Renaming_Declaration
     (Parameter_Specification : Integer) return Boolean
     renames Function_Declaration;

   generic package G_Pack is end G_Pack;
   generic package Generic_Package_Renaming_Declaration renames G_Pack;

   generic procedure G_Proc;
   generic procedure Generic_Procedure_Renaming_Declaration renames G_Proc;

   generic function G_Funct return Boolean;
   generic function Generic_Function_Renaming_Declaration renames G_Funct;

   task Task_Body_Declaration;

   task body Task_Body_Declaration is
   begin
      null;
   end Task_Body_Declaration;

   protected Protected_Body_Declaration is
      procedure Proc;
   end Protected_Body_Declaration;

   protected body Protected_Body_Declaration is
      procedure Proc is
      begin
         null;
      end Proc;
   end Protected_Body_Declaration;

   protected Prot is
      entry Entry_Declaration (Boolean);
   end Prot;

   protected body Prot is
      entry Entry_Declaration (for Entry_Index_Specification in Boolean)
        when True is
      begin
         if Function_Declaration (2) then
            <<Requeue_Statement>>
            requeue Entry_Declaration (True);
         else
            <<Requeue_Statement_With_Abort>>
            requeue Entry_Declaration (False) with abort;
         end if;
      end Entry_Declaration;
   end Prot;

   procedure Procedure_Body_Stub is separate;
   function Function_Body_Stub return Boolean is separate;

   package Package_Body_Stub is
      procedure Proc;
   end Package_Body_Stub;

   package body Package_Body_Stub is separate;

   task Task_Body_Stub;

   task body Task_Body_Stub is separate;

   protected Protected_Body_Stub is
      procedure Proc;
   end Protected_Body_Stub;

   protected body Protected_Body_Stub is separate;

   Exception_Declaration : exception;

   procedure Proc_2 is
   begin
      null;
   exception
      when Choice_Parameter_Specification : others => null;
   end Proc_2;

   generic procedure Generic_Procedure_Declaration;
   procedure Generic_Procedure_Declaration is begin null; end;

   generic
      type Type_1 is (<>);
   function Generic_Function_Declaration return Integer;

   function Generic_Function_Declaration return Integer is
   begin
      return 0;
   end Generic_Function_Declaration;

   generic package Generic_Package_Declaration is end;

   package Package_Instantiation is new Generic_Package_Declaration;

   procedure Procedure_Instantiation is new Generic_Procedure_Declaration;

   function Function_Instantiation is
      new Generic_Function_Declaration (Boolean);

   generic
      Formal_Object_Declaration : in Integer := 1;

      type Formal_Type_Declaration is private;

      with procedure Formal_Procedure_Declaration (X : in Integer);

      with function Formal_Function_Declaration return Boolean is True;

      with package Formal_Package_Declaration is
        new Generic_Package_Declaration;

      with package Formal_Package_Declaration_With_Box is
        new Generic_Package_Declaration (<>);

   procedure Proc_3;

   -----------------
   -- Trait_Kinds --
   -----------------

   Aliased_Trait : aliased Type_2 (1) := (1, 2);

   procedure Proc_4 (Access_Definition_Trait : access Integer) is
   begin
      for Reverse_Trait in reverse Boolean loop
         null;
      end loop;
   end Proc_4;

   --  other traits in A0000A package

   ----------------
   -- Mode_Kinds --
   ----------------

   procedure Proc_5
      (Default_In_Mode :        Integer;
       In_Mode         : in     Integer;
       Out_Mode        :    out Integer;
       In_Out_Mode     : in out Integer) is
   begin
      Out_Mode := In_Mode;
   end Proc_5;

   generic
      with procedure Name_Default is Procedure_Declaration;
      with procedure Box_Default is <>;
      with procedure Nil_Default;
   procedure Subprogram_Default_Kinds;

   ----------------
   -- Type_Kinds --
   ----------------

   type Derived_Type_Definition is new Integer;

   type Type_3 is tagged null record;

   type Derived_Record_Extension_Definition is new Type_3 with record
      X : Integer;
   end record;

   type Enumeration_Type_Definition is (X);

   type Signed_Integer_Type_Definition is range 1 .. 2;

   type Modular_Type_Definition is mod 256;

   --  Root_Type_Definition

   type Floating_Point_Definition is digits 8;

   type Ordinary_Fixed_Point_Definition is
     delta 0.01 range 0.0 .. 1_000_000.0;

   type Decimal_Fixed_Point_Definition is delta 0.01 digits 8;

   type Constrained_Array_Definition is array (Boolean) of Integer;

   type Unconstrained_Array_Definition is array (Integer range <>) of Integer;

   type Record_Type_Definition is record
      X : Integer;
   end record;

   type Tagged_Record_Type_Definition is tagged null record;

   type Access_Type_Definition is access Integer;

   generic
      type Formal_Private_Type_Definition is private;

      type Formal_Tagged_Private_Type_Definition is tagged private;

      type Formal_Derived_Type_Definition is
        new Formal_Private_Type_Definition;

      type Formal_Discrete_Type_Definition is (<>);

      type Formal_Signed_Integer_Type_Definition is range <>;

      type Formal_Modular_Type_Definition is mod <>;

      type Formal_Floating_Point_Definition is digits <>;

      type Formal_Ordinary_Fixed_Point_Definition is delta <>;

      type Formal_Decimal_Fixed_Point_Definition is delta <> digits <>;

      type Formal_Unconstrained_Array_Definition is
        array (Integer range <>) of Formal_Private_Type_Definition;

      type Formal_Constrained_Array_Definition is
        array (Boolean) of Formal_Private_Type_Definition;

      type Formal_Access_Type_Definition is
        access all Formal_Private_Type_Definition;

   package Formal_Type_Kinds is
   end Formal_Type_Kinds;

   -----------------------
   -- Access_Type_Kinds --
   -----------------------

   type Pool_Specific_Access_To_Variable is access Boolean;

   type Access_To_Variable is access all Boolean;

   type Access_To_Constant is access constant Boolean;

   type Access_To_Procedure is access procedure;

   type Access_To_Protected_Procedure is access protected procedure;

   type Access_To_Function is access function return Boolean;

   type Access_To_Protected_Function is
     access protected function return Boolean;

   ----------------------
   -- Constraint_Kinds --
   ----------------------

   subtype Range_Attribute_Reference is Integer range Positive'Range;
   subtype Simple_Expression_Range is Integer range 1 .. 2;
   subtype Digits_Constraint is Float digits 3;
   subtype Delta_Constraint is Duration delta 0.01;
   subtype Index_Constraint is String (1 .. 10);
   subtype Discriminant_Constraint is Type_2 (1);

   --   Discrete_Range_Kinds
   Discrete_Subtype_Indication        : String (Simple_Expression_Range);
   Discrete_Range_Attribute_Reference : String (Variable_Declaration'Range);
   Discrete_Simple_Expression_Range   : String (21 .. 30);


   Pragma_Argument_Association : Access_Type_Definition;
   pragma Import (C, Pragma_Argument_Association);

   ----------------------
   -- Expression_Kinds --
   ----------------------

   Integer_Literal      : constant Integer   := 1;
   Real_Literal         : constant Float     := 0.1;
   String_Literal       : constant String    := "abc";
   Identifier           : constant Integer   := Integer_Literal;
   Operator_Symbol      : constant Integer   := 1 + 1;
   Character_Literal    : constant Character := 'X';
   Enumeration_Literal  : constant Boolean   := True;
   Explicit_Dereference : constant Integer  := Pragma_Argument_Association.all;
   Function_Call        : constant Boolean   := Function_Declaration (1);
   Indexed_Component    : constant Character := String_Literal (1);
   Slice                : constant String    := String_Literal (1 .. 2);
   Selected_Component   : constant Integer   :=
     Aliased_Trait.Component_Declaration;
   Attribute_Reference  : constant Integer   := String_Literal'First;
   Record_Aggregate     : constant Type_2    := (1, 2);
   Extension_Aggregate  : constant Derived_Record_Extension_Definition :=
    (Type_3 with 1);

   Positional_Array_Aggregate   : constant String := ('a', 'b');
   Named_Array_Aggregate        : constant String := (1 => 'a', 2 => 'b');
   And_Then_Short_Circuit       : constant Boolean := True and then False;
   Or_Else_Short_Circuit        : constant Boolean := True or else False;
   In_Range_Membership_Test     : constant Boolean := 2 in 1 .. 10;
   Not_In_Range_Membership_Test : constant Boolean := 2 not in 1 .. 10;
   In_Type_Membership_Test      : constant Boolean :=
     Extension_Aggregate in Type_3'Class;

   Not_In_Type_Membership_Test  : constant Boolean :=
     Extension_Aggregate not in Type_3'Class;

   Null_Literal                 : constant Access_Type_Definition := null;
   Parenthesized_Expression     : constant Integer := (1);
   Type_Conversion              : constant Signed_Integer_Type_Definition :=
     Signed_Integer_Type_Definition (Integer_Literal);

   Qualified_Expression         : constant Integer := Integer'(1);
   Allocation_From_Subtype      : constant Access_Type_Definition :=
     new Integer;

   Allocation_From_Qualified_Expression : constant Access_Type_Definition :=
     new Integer'(10);

   ------------------
   -- Clause_Kinds --
   ------------------

   type Attribute_Definition_Clause is range 1 .. 10_000;
   for Attribute_Definition_Clause'Size use 16;

   type Enumeration_Representation_Clause is (A, B, C);
   for Enumeration_Representation_Clause use (A => 1, B => 2, C => 3);

   type Record_Representation_Clause is record
      X : Integer;
      C : Character;
   end record;

   for Record_Representation_Clause use record
      X at 0  range 0 .. 31;
      C at 32 range 0 .. 7;
   end record;

   At_Clause : Integer;
   for At_Clause use at Aliased_Trait'Address;

   ------------------
   --  Completions --
   ------------------

   function "not" (Left : Integer) return Integer is
   begin
      return Left;
   end "not";

   procedure Proc_3 is begin null; end;

   task body Task_Type_Declaration is
   begin
      <<Terminate_Alternative_Statement>>
      select
         accept Entry_Declaration;
      or
         terminate;
      end select;

      <<Selective_Accept_Statement>>
      select
         accept Entry_Declaration;
      or
         accept Run;
      end select;


   end Task_Type_Declaration;

   protected body Protected_Type_Declaration is
      entry Entry_Body_Declaration when State is
      begin
         null;
      end Entry_Body_Declaration;
   end Protected_Type_Declaration;

   task body Single_Task_Declaration is
   begin
      accept Run;
   end Single_Task_Declaration;

   protected body Single_Protected_Declaration is
      entry Run when True is
      begin
         null;
      end Run;
   end Single_Protected_Declaration;

   procedure Procedure_Declaration is begin null; end;

   function Function_Declaration
     (Parameter_Specification : Integer) return Boolean is
   begin
      return False;
   end Function_Declaration;

   procedure G_Proc is begin null; end;

   function G_Funct return Boolean is
   begin
      return True;
   end G_Funct;

   procedure Subprogram_Default_Kinds is begin null; end;

begin
   <<Null_Statement>>
   null;

   <<Assignment_Statement>>
   Variable_Declaration := (others => ' ');

   <<If_Statement>>
   if Enumeration_Literal then
      return;
   elsif Function_Call then
      Procedure_Body_Declaration;
   else
      Procedure_Declaration;
   end if;

   <<Case_Statement>>
   case Integer_Literal is
      when 1 =>
         Procedure_Declaration;
      when others =>
         null;
   end case;

   <<Loop_Statement>>
   loop
      Procedure_Declaration;
   end loop;

   <<While_Loop_Statement>>
   while Function_Declaration (1) loop
      Procedure_Declaration;
   end loop;

   <<For_Loop_Statement>>
   for Discrete_Range_Attribute_Reference in String_Literal'Range loop
      <<Block_Statement>>
      declare
         Variable : Integer := 1;
      begin
         <<Exit_Statement>>
         exit when Variable > Discrete_Range_Attribute_Reference;

         <<Goto_Statement>>
         goto Procedure_Call_Statement;

         <<Procedure_Call_Statement>>
         Procedure_Declaration;

         <<Return_Statement>>
         if Discrete_Range_Attribute_Reference > 5 then
            return;
         end if;

        <<Entry_Call_Statement>>
        Single_Task_Declaration.Run;

      end;
   end loop;

   <<Delay_Until_Statement>>
   delay until Ada.Calendar.Clock;

   <<Delay_Relative_Statement>>
   delay 1.0;

   <<Timed_Entry_Call_Statement>>
   select
      Single_Task_Declaration.Run;
   or
      delay 1.0;
   end select;

   <<Conditional_Entry_Call_Statement>>
   select
      Single_Task_Declaration.Run;
   else
      Pragma_Argument_Association.all := 0;
   end select;

   <<Asynchronous_Select_Statement>>
   select
      delay 1.0;
   then abort
      Procedure_Declaration;
   end select;

   <<Abort_Statement>>
   abort Single_Task_Declaration;

   <<Raise_Statement>>
   raise Exception_Renaming_Declaration;

end A0000;
