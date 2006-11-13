--  Purpose: check type convertion.
--  Dependencies:: standard.ads

procedure B0017 is
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
   --  cast to signed integer
   if Integer (X_Int) /= 4 then
      Report (False);
      return;
   end if;

   if Int (X_Mod) /= X_Int then
      Report (False);
      return;
   end if;

   if Int (X_Real) /= X_Int then
      Report (False);
      return;
   end if;

   if Int (X_Fixed) /= X_Int then
      Report (False);
      return;
   end if;

   if Int (X_Fix) /= X_Int then
      Report (False);
      return;
   end if;

   --  cast to modular integer
   if Modular (X_Int) /= X_Mod then
      Report (False);
      return;
   end if;

   if Modular (X_Real) /= X_Mod then
      Report (False);
      return;
   end if;

   if Modular (X_Fixed) /= X_Mod then
      Report (False);
      return;
   end if;

   if Modular (X_Fix) /= X_Mod then
      Report (False);
      return;
   end if;

   if Modular'Base (X_Fix) /= X_Mod then
      Report (False);
      return;
   end if;

   --  cast to float point
   if Real (X_Int) /= X_Real then
      Report (False);
      return;
   end if;

   if Real (X_Mod) /= X_Real then
      Report (False);
      return;
   end if;

   if Float (X_Real) /= 4.0 then
      Report (False);
      return;
   end if;

   if Real (X_Fixed) /= X_Real then
      Report (False);
      return;
   end if;

   if Real (X_Fix) /= X_Real then
      Report (False);
      return;
   end if;

   --  cast to fixed point
   if Fixed (X_Int) /= X_Fixed then
      Report (False);
      return;
   end if;

   if Fixed (X_Mod) /= X_Fixed then
      Report (False);
      return;
   end if;

   if Fixed (X_Real) /= X_Fixed then
      Report (False);
      return;
   end if;

   if Fixed (X_Fix) /= X_Fixed then
      Report (False);
      return;
   end if;

   if Fix (X_Fixed) /= X_Fix then
      Report (False);
      return;
   end if;

   --  static cast to signed integer
   if Int (2 + 2) /= X_Int then
      Report (False);
      return;
   end if;

   --  qualified expr
   if Int'(4) /= X_Int then
      Report (False);
      return;
   end if;

   Report (True);
end B0017;
