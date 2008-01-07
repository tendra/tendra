------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: bug, too late building of normalized_profile inside
--  a representation clause
--

package A0019 is
   type Enum is (One, Two);
   for Enum use
      (One => -1,
       Two => 2);
end;
