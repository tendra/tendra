--  Purpose: check fixed point operations.
--  Dependencies:: standard.ads

procedure B0016 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "Report");

   type Fixed is delta 0.1 range -7.0 .. 7.0;

   One          : Fixed := 1.0;
   Two          : Fixed := 2.0;
   Three        : Fixed := 3.0;
   One_And_Half : Fixed := 1.5;

   type Fixed_16 is delta 0.01 range -100.0 .. 100.0;
   Two_16       : Fixed_16 := 2.0;
   Half_16      : Fixed_16 := 0.5;
   
begin
   if Two + Three /= 5.0 then
      Report (False);
      return;
   end if;

   if Two - Three /= -1.0 then
      Report (False);
      return;
   end if;

   if -Three /= -3.0 then
      Report (False);
      return;
   end if;

   if Three / 2 /= One_And_Half then
      Report (False);
      return;
   end if;
      
   if Three / Two_16 /= One_And_Half then
      Report (False);
      return;
   end if;
      
   if One / Two_16 /= Half_16 then
      Report (False);
      return;
   end if;
      
   if One_And_Half * 2 /= Three then
      Report (False);
      return;
   end if;
      
   if One_And_Half * Two_16 /= Three then
      Report (False);
      return;
   end if;
      
   if abs (Two - Three) /= 1.0 then
      Report (False);
      return;
   end if;

   if Fixed'First >= Fixed'Last then
      Report (False);
      return;
   end if;

   if Fixed'First <= Fixed'Base'First then
      Report (False);
      return;
   end if;

   if Fixed'Last >= Fixed'Base'Last then
      Report (False);
      return;
   end if;

   if Fixed'Max (Two, Three) /= Three then
      Report (False);
      return;
   end if;

   if Fixed'Min (Two, Three) /= Two then
      Report (False);
      return;
   end if;

   if Fixed'Succ (Two) <= Two then
      Report (False);
      return;
   end if;

   if Fixed'Pred (Two) >= Two then
      Report (False);
      return;
   end if;

   Report (True);
end B0016;
