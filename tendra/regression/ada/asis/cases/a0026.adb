------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Check preference of root_integer for ranges
--

procedure A0026 is
begin
   for i in reverse 1 .. 30 * 100 loop
      null;
   end loop;
end;
