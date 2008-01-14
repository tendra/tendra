------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: check private operations
--

package A0020 is
   type T1 is limited private;
   type T2 is array (Positive range <>) of T1;

   type T4 is record
      Item : T1;
   end record;

   procedure Use_Body;

private
   type T1 is mod 256;
   function F1 (Left, Right : T2) return Boolean renames "=";
   function F1 (Left, Right : T4) return Boolean renames "=";

   function F1 (Left, Right : T2) return T2 renames "&";
end;
