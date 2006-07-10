------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Check generic instances.
--
--  Used with 'name' test to find each corresponding declaration for all
--  names.


with Ada.Numerics.Discrete_Random;

procedure A0004 is

   package Random is new Ada.Numerics.Discrete_Random (Integer);

   X : Random.Generator;
   V : constant Integer := Random.Random (X);
begin
   null;
end A0004;
