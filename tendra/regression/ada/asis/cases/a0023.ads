------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Check bag-fix: override by instantiation
--

with Ada.Unchecked_Deallocation;

package A0023 is

   type Integer_Access is access all Integer;

   procedure Free;

   procedure Free is
      new Ada.Unchecked_Deallocation (Integer, Integer_Access);

end;
