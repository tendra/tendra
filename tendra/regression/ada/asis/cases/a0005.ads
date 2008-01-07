------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Check Interface types of Ada 2005.
--

with Ada.Finalization;
with A0005A;

package A0005 is

   type I3 is limited interface;

   type T1 is limited new A0005A.I1 with null record;

   type T2 is limited new A0005A.I1 and A0005A.I2 and I3 with null record;

   type T3 is limited new I3 and A0005A.I2 and A0005A.I1 with null record;

   type T4 is new Ada.Finalization.Limited_Controlled
     and A0005A.I1 and I3 with null record;

   task type T5 is new A0005A.I2 with end T5;

   protected type T6 is new A0005A.I2 with end T6;

end A0005;
