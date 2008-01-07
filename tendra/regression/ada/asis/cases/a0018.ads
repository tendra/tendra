------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: check profile conformance rules for access result
--

package A0018 is
   type Rec is tagged null record;

   function F1 return access Rec;

   function F2 return access Rec renames F1;

end;
