------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Ada 2005. Check mod attribute.
--

procedure A0012 is

   type Modular is mod 256;

   X1 : constant := Modular'Mod(257);

begin
   null;
end;
