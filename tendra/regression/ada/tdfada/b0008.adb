--  Purpose: verify target dependent static expression evaluation.
--  Dependencies:: standard.ads

procedure B0008 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "Report");

   X   : constant := Integer'First + 1;
   Y   : constant := Integer'First + 2;
   Yes : constant Boolean := Boolean'Val (Y - X);
   No  : constant Boolean := Boolean'Val (Y - Y);
   One : constant Character := Character'Val (48 + Y - X);
   Two : constant Character := Character'Val (49 + Y - X);
begin
   if Y - X /= 1 then
      Report (False);
      return;
   end if;

   if Integer'Pred (Y) /= X then
      Report (False);
      return;
   end if;

   if Integer'Succ (X) /= Y then
      Report (False);
      return;
   end if;

   if Integer'Min (X, Y) /= X then
      Report (False);
      return;
   end if;

   if Integer'Max (X, Y) /= Y then
      Report (False);
      return;
   end if;

   if Integer'Pos (X) /= X then
      Report (False);
      return;
   end if;

   if Integer'Val (X) /= X then
      Report (False);
      return;
   end if;

   if Yes /= True or No /= False then
      Report (False);
      return;
   end if;

   if Boolean'Pos (No) /= 0 or Boolean'Pos (Yes) /= 1  then
      Report (False);
      return;
   end if;

   if Boolean'Pred (Yes) /= No then
      Report (False);
      return;
   end if;

   if Boolean'Succ (No) /= Yes then
      Report (False);
      return;
   end if;

   if Boolean'Min (Yes, No) /= No then
      Report (False);
      return;
   end if;

   if Boolean'Max (Yes, No) /= Yes then
      Report (False);
      return;
   end if;

   if One /= '1' or Two /= '2' then
      Report (False);
      return;
   end if;

   if Character'Pos (One) /= 49 or Character'Pos (Two) /= 50  then
      Report (False);
      return;
   end if;

   if Character'Pred (Two) /= One then
      Report (False);
      return;
   end if;

   if Character'Succ (One) /= Two then
      Report (False);
      return;
   end if;

   if Character'Min (One, Two) /= One then
      Report (False);
      return;
   end if;

   if Character'Max (One, Two) /= Two then
      Report (False);
      return;
   end if;

   Report (True);
end B0008;
