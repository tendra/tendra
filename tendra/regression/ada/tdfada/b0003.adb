--  Purpose: Test procedure call and 'in out' parameter
--  Dependencies:: standard.ads b0003p.adb

with b0003p;

procedure B0003 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report);

   X : Boolean;
begin
   X := False;
   b0003p (X);  --  Invert X
   Report (X);
end;
