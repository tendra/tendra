------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Check some visibility rules.
--  Used with 'name' test to find each corresponding declaration for all
--  names.

with A0001A;
with A0001B;
with Ada.Exceptions;

procedure A0001 is

   procedure Name is
      use Ada.Exceptions;

      package Name is
         type Name is record
            Name : Integer;
         end record;
      end;

      Var : Name.Name := (Name => 1);
   begin
      declare
         Name : Integer := A0001.Name.Var.Name;
      begin
         Name := 1;
         
         for Name in Boolean loop
            Var.Name := Boolean'Pos (Name);

            begin
               <<Name>>
               goto Name;
            end;
         end loop;
--  Dont work yet:
--      exception
--         when Name : Constraint_Error =>
--            Reraise_Occurrence (Name);
--         when Name : others =>
--            Reraise_Occurrence (Name);
      end;
   end;

begin
   Name;

   declare
      use A0001A, A0001B;
   begin
--      A := B;
      null;
   end;

   declare
      use type A0001A.Type_A;
      Var : A0001A.Type_A;
   begin
--      Var := not 1;
      null;
   end;

   declare
      use type A0001B.Type_B;
      Var : A0001B.Type_B;
   begin
--      Var := not 1;
      null;
   end;

end;
