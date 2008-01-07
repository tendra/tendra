------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Ada 2005. Check limited_with_clause
--

limited with A0011A;

package A0011 is
   X : access A0011A.Item := null;

   type Some_Access is access all A0011A.Nested.Some_Record;
end A0011;
