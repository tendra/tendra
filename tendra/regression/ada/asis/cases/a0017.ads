------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: bug, syntax error on parent_subtype_indication with
--  range constraint
--
with Interfaces.C;

package A0017 is
   type Event_Type is new Interfaces.C.int range 0 .. 65535;
end;
