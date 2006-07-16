--  Purpose: Test if Report procedure is working.
--  Dependencies:: standard.ads

procedure B0001 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "report");
begin
   Report (True);
end B0001;
