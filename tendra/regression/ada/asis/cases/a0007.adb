------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Ada 2005. Anonimous access types in function result.
--

procedure A0007 is

   function X (I : Integer) return access procedure (B : Boolean) is
   begin
      return null;
   end;

   function X (I : Integer) return access procedure (B : Float) is
   begin
      return null;
   end;

begin
   X (1) (True);
end;
