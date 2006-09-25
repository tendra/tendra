--  Purpose: check for loo statement.
--  Dependencies:: standard.ads

procedure B0014 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "Report");

   type Int is range 0 .. 1000;
   One   : constant Int := 1;
   Count : Int := 0;
begin
   for J in One .. 0 loop
      Report (False);
      return;
   end loop;

   for J in One .. 10 loop
      Count := Count + J;
   end loop;

   if Count /= 55 then
      Report (False);
      return;
   end if;

   Report (True);
end B0014;
