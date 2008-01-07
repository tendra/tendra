------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Ada 2005. Check syntax of anonimous access types.
--

procedure A0006 is

   procedure P1 (X : access Integer) is
   begin
      null;
   end;

   procedure P2 (X : access constant Integer) is
   begin
      null;
   end;

   procedure P (X : access procedure (Y : Integer)) is
   begin
      null;
   end;

   procedure P (X : access protected procedure (Y : Boolean)) is
   begin
      null;
   end;

   procedure P (X : access function (Y : Integer) return String) is
   begin
      null;
   end;

   procedure P (X : access protected function (Y : Boolean) return String) is
   begin
      null;
   end;

   procedure X1 (Y : Integer) is
   begin
      null;
   end;
begin
   P (X1'Access);
end;
