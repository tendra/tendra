------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Ada 2005. Check raise with message statement
--

procedure A0013 is

   function Data return String is
   begin
      return "";
   end;

   function Data return Integer is
   begin
      return 0;
   end;

begin
   raise Constraint_Error with Data;
end;
