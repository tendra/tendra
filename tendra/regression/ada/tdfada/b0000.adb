--  Purpose: Test if Report procedure is working.
--  This test doesn't use any Ada unit, even Standard.

procedure B0000 is
   type Boolean is (False, True);
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "report");
begin
   Report (True);
end B0000;
