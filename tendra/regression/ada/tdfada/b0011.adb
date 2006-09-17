--  Purpose: check 'Base attribute evaluation.
--  Dependencies:: standard.ads
--  TODO: Check 'First when #79 will be fixed

procedure B0011 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "Report");

   type Int is range 1 .. Integer'Last - 1;

   X : Int := Int'Base'Last;
   Y : Int := Int'Val (Integer'Last);
   Z : Int := Int'Base'Last - Int'Val (Integer'Last);
begin
   if Int'Last = Int'Base'Last then
      Report (False);
      return;
   end if;

   if Z /= 0 then
      Report (False);
      return;
   end if;

   if X /= Y then
      Report (False);
      return;
   end if;

   if Int'Base'Last /= Int'Val (Integer'Last) then
      Report (False);
      return;
   end if;

   if Boolean'Last /= Boolean'Base'Last then
      Report (False);
      return;
   end if;

   Report (True);
end B0011;
