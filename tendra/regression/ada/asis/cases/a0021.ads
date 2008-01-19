------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: check inherited subprograms in private operations
--  (Attention: a0021.adb contains a0021.A body)

package A0021 is
   type T1 is tagged null record;
   procedure P1 (Item : T1);
private
   procedure P2 (Item : T1);
end;
