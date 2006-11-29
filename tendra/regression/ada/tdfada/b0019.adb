--  Purpose: check subtype attributes.
--  Dependencies:: standard.ads
   
procedure B0019 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "Report");

   X : Integer := 5;
      
   subtype Int  is Integer range X .. 7;
   subtype Attr is Integer range Int'Range;
begin
   if Positive'First /= 1 then
      Report (False);
      return;
   end if;

   if Positive'Last /= Integer'Last then
      Report (False);
      return;
   end if;

   if Int'First /= X then
      Report (False);
      return;
   end if;

   if Int'Last /= 7 then
      Report (False);
      return;
   end if;

   if Int'Base'First /= Integer'Base'First then
      Report (False);
      return;
   end if;

   if Attr'First /= X then
      Report (False);
      return;
   end if;

   if Attr'Last /= 7 then
      Report (False);
      return;
   end if;

   Report (True);
end B0019;
