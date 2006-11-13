--  Purpose: check subtype membership test.
--  Dependencies:: standard.ads
   
procedure B0018 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "Report");
   
   type Int is range -7 .. 7;
   type Modular is mod 8;
   type Real is digits 5 range -7.0 .. 7.0;
   type Fixed is delta 0.1 range -7.0 .. 7.0;
   type Fix   is delta 2.0 range -7.0 .. 7.0;
   
   X_Int   : Int := 4;
   X_Mod   : Modular := 4;
   X_Real  : Real := 4.0;
   X_Fixed : Fixed := 4.0;
   X_Fix   : Fix := 4.0;
begin
   if X_Int not in Int then
      Report (False);
      return;
   end if;

   if X_Mod not in Modular then
      Report (False);
      return;
   end if;

   if X_Real not in Real then
      Report (False);
      return;
   end if;

   if X_Fixed not in Fixed then
      Report (False);
      return;
   end if;

   if X_Fix not in Fix then
      Report (False);
      return;
   end if;

   Report (True);
end B0018;
