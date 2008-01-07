--  Purpose: Test Boolean operations (result as jump).
--  Dependencies:: b0006p.adb standard.ads

with B0006P; use B0006P;

procedure B0006 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "Report");

   Yes : Boolean := True;
   No  : Boolean := False;
begin
   Nothing (Yes, No);  --  Avoid optimization of variables values

   if not (Yes and Yes) then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if No and Yes then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if No or No then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if not (No or Yes) then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if Yes xor Yes then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if not (No xor Yes) then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if not (Yes = Yes) then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if No = Yes then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if Yes /= Yes then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if not (No /= Yes) then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if Yes < Yes then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if not (No < Yes) then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if not (Yes <= Yes) then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if Yes <= No then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if Yes > Yes then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if not (Yes > No) then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if not (Yes >= Yes) then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if No >= Yes then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if not Yes then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if not (not No) then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if No and then Never_Call then
      Report (False);
      return;
   end if;

   Nothing (Yes, No);

   if not (Yes or else Never_Call) then
      Report (False);
      return;
   end if;

   Report (True);
end;
