--  Purpose: check float point operations.
--  Dependencies:: standard.ads

procedure B0015 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "Report");

   type Real is digits 5 range 1.0 .. 100.0;

   Two          : Real := 2.0;
   Three        : Real := 3.0;
   One_And_Half : Real := 1.5;

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

   if Two * Three /= 6.0 then
      Report (False);
      return;
   end if;

   if Two / Three >= 0.66667 then
      Report (False);
      return;
   end if;

   if Two / Three < 0.66666 then
      Report (False);
      return;
   end if;

   if Two ** 7 /= 128.0 then
      Report (False);
      return;
   end if;

   if abs (Two - Three) /= 1.0 then
      Report (False);
      return;
   end if;

   if Real'Ceiling (One_And_Half) /= 2.0 then
      Report (False);
      return;
   end if;

   if Real'Floor (One_And_Half) /= 1.0 then
      Report (False);
      return;
   end if;

   if Real'Rounding (One_And_Half) /= 2.0 then
      Report (False);
      return;
   end if;

   if Real'Truncation (One_And_Half) /= 1.0 then
      Report (False);
      return;
   end if;

   if Real'Ceiling (-One_And_Half) /= -1.0 then
      Report (False);
      return;
   end if;

   if Real'Floor (-One_And_Half) /= -2.0 then
      Report (False);
      return;
   end if;

   if Real'Rounding (-One_And_Half) /= -2.0 then
      Report (False);
      return;
   end if;

   if Real'Truncation (-One_And_Half) /= -1.0 then
      Report (False);
      return;
   end if;

   if Real'Ceiling (1.5) /= 2.0 then
      Report (False);
      return;
   end if;

   if Real'Floor (1.5) /= 1.0 then
      Report (False);
      return;
   end if;

   if Real'Rounding (1.5) /= 2.0 then
      Report (False);
      return;
   end if;

   if Real'Truncation (1.5) /= 1.0 then
      Report (False);
      return;
   end if;

   if Real'Ceiling (-1.5) /= -1.0 then
      Report (False);
      return;
   end if;

   if Real'Floor (-1.5) /= -2.0 then
      Report (False);
      return;
   end if;

   if Real'Rounding (-1.5) /= -2.0 then
      Report (False);
      return;
   end if;

   if Real'Truncation (-1.5) /= -1.0 then
      Report (False);
      return;
   end if;

   Report (True);
end B0015;
