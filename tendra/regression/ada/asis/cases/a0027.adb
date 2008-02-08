------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--

procedure A0027 is

   generic
   package G is
      type T is limited private;

      function Equal (Left, Right : T) return Boolean;

      function "=" (Left, Right : T) return Boolean renames Equal;

      function Not_Equal (Left, Right : T) return Boolean renames "/=";

   private
      type T is (Ignore);
   end;

   package body G is
      function Equal (Left, Right : T) return Boolean is
      begin
         return False;
      end Equal;
   end;

   package I is new G;

   use I;

   O1, O2 : T;

   Test_1 : Boolean := O1 = O2;
   Test_2 : Boolean := O1 /= O2;

begin
   null;
end;

