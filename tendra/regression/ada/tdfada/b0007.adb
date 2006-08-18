--  Purpose: recursive function call (calculate factorial).
--  Dependencies:: b0007p.adb standard.ads

with B0007P;

procedure B0007 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "Report");
begin
   if B0007P (7) /= 5040 then
      Report (False);
      return;
   end if;

   Report (True);
end B0007;

