--  Purpose: Test function call
--  Dependencies:: b0005p.adb standard.ads

with B0005P; use B0005P;

procedure B0005 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "Report");

   Result : Boolean;
begin
   Result := The_Same (False);

   if Result then
      Report (False);
      return;
   end if;

   Result := The_Same (True);

   if not Result then
      Report (False);
      return;
   end if;

   if The_Same (False) then
      Report (False);
      return;
   end if;

   if not The_Same (True) then
      Report (False);
      return;
   end if;

   if The_Same (0) /= 0 then
      Report (False);
      return;
   end if;

   if The_Same (100) /= 100 then
      Report (False);
      return;
   end if;

   Report (True);
end;
