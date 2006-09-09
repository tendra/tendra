--  Purpose: verify attribute evaluation.
--  Dependencies:: standard.ads

procedure B0009 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "Report");

   X   : Integer := Integer'First + 1;
   Y   : Integer := Integer'First + 2;
   C   : Character := '3';
   Yes : Boolean := True;
   No  : Boolean := False;
begin
   if Integer'Min (X, Y) /= X then
      Report (False);
      return;
   end if;

   if Integer'Max (X, Y) /= Y then
      Report (False);
      return;
   end if;

   if Integer'Succ (X) /= Y then
      Report (False);
      return;
   end if;

   if Integer'Pred (Y) /= X then
      Report (False);
      return;
   end if;

   if Integer'Pos (Y) /= X + 1 then
      Report (False);
      return;
   end if;

   if Integer'Val (Y) /= X + 1 then
      Report (False);
      return;
   end if;

   if Character'Min (C, '5') /= '3' then
      Report (False);
      return;
   end if;

   if Character'Max (C, '5') /= '5' then
      Report (False);
      return;
   end if;

   if Character'Succ (C) /= '4' then
      Report (False);
      return;
   end if;

   if Character'Pred (C) /= '2' then
      Report (False);
      return;
   end if;

   if Character'Pos (C) /= 51 then
      Report (False);
      return;
   end if;

   if Character'Val (51) /= C then
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

   Report (True);
end B0009;
