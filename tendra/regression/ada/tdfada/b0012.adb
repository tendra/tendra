--  Purpose: check unsigned integer operations.
--  Dependencies:: standard.ads

procedure B0012 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "Report");

   type Mod_256 is mod 256;
   type Mod_16  is mod 16;
   type Mod_10  is mod 10;

   A_256 : Mod_256 := 254;
   B_256 : Mod_256 := 3;
   Zero  : constant Integer := Integer'Last - Integer'Last;
   Z_256 : constant Mod_256 := Mod_256'Val (Zero);

   A_16 : Mod_16 := 14;
   B_16 : Mod_16 := 3;

   A_10 : Mod_10 := 8;
   B_10 : Mod_10 := 3;

begin
   if -A_256 /= 2 then
      Report (False);
      return;
   end if;

   if -A_16 /= 2 then
      Report (False);
      return;
   end if;

   if -A_10 /= 2 then
      Report (False);
      return;
   end if;

   if A_256 + B_256 /= 1 then
      Report (False);
      return;
   end if;

   if A_16 + B_16 /= 1 then
      Report (False);
      return;
   end if;

   if A_10 + B_10 /= 1 then
      Report (False);
      return;
   end if;

   if B_256 - A_256 /= 5 then
      Report (False);
      return;
   end if;

   if B_16 - A_16 /= 5 then
      Report (False);
      return;
   end if;

   if B_10 - A_10 /= 5 then
      Report (False);
      return;
   end if;

   if A_256 * B_256 /= 250 then
      Report (False);
      return;
   end if;

   if A_16 * B_16 /= 10 then
      Report (False);
      return;
   end if;

   if A_10 * B_10 /= 4 then
      Report (False);
      return;
   end if;

   if A_256 / B_256 /= 84 then
      Report (False);
      return;
   end if;

   if A_16 / B_16 /= 4 then
      Report (False);
      return;
   end if;

   if A_10 / B_10 /= 2 then
      Report (False);
      return;
   end if;

   if (A_256 or B_256) /= 255 then
      Report (False);
      return;
   end if;

   if (A_16 or B_16) /= 15 then
      Report (False);
      return;
   end if;

   if (A_10 or B_10) /= 1 then
      Report (False);
      return;
   end if;

   if (A_256 xor B_256) /= 253 then
      Report (False);
      return;
   end if;

   if (A_16 xor B_16) /= 13 then
      Report (False);
      return;
   end if;

   if (A_10 xor B_10) /= 1 then
      Report (False);
      return;
   end if;

   if (A_256 and B_256) /= 2 then
      Report (False);
      return;
   end if;

   if (A_16 and B_16) /= 2 then
      Report (False);
      return;
   end if;

   if (A_10 and B_10) /= 0 then
      Report (False);
      return;
   end if;

   if (not A_256) /= 1 then
      Report (False);
      return;
   end if;

   if (not A_16) /= 1 then
      Report (False);
      return;
   end if;

   if (not A_10) /= 1 then
      Report (False);
      return;
   end if;

   if abs A_256 /= 254 then
      Report (False);
      return;
   end if;

   if abs A_16 /= 14 then
      Report (False);
      return;
   end if;

   if abs A_10 /= 8 then
      Report (False);
      return;
   end if;

   if A_256 ** 3 /= 248 then
      Report (False);
      return;
   end if;

   if A_16 ** 3 /= 8 then
      Report (False);
      return;
   end if;

   if A_10 ** 3 /= 2 then
      Report (False);
      return;
   end if;

   if Mod_256'First /= 0 then
      Report (False);
      return;
   end if;

   if Mod_256'Last /= 255 then
      Report (False);
      return;
   end if;

   if Mod_256'Min (A_256, B_256) /= B_256 then
      Report (False);
      return;
   end if;

   if Mod_256'Max (A_256, B_256) /= A_256 then
      Report (False);
      return;
   end if;

   if Mod_256'Pos (A_256) /= 254 then
      Report (False);
      return;
   end if;

   if Mod_256'Val (3) /= B_256 then
      Report (False);
      return;
   end if;

   if Mod_256'Succ (B_256) /= 4 then
      Report (False);
      return;
   end if;

   if Mod_256'Pred (B_256) /= 2 then
      Report (False);
      return;
   end if;

   if Mod_256'Succ (255) /= 0 then
      Report (False);
      return;
   end if;

   if Mod_256'Pred (0) /= 255 then
      Report (False);
      return;
   end if;

   if Mod_10'Succ (9) /= 0 then
      Report (False);
      return;
   end if;

   if Mod_10'Pred (0) /= 9 then
      Report (False);
      return;
   end if;

   --  Static expressions:

   if 255 + Z_256 /= 255 then
      Report (False);
      return;
   end if;

   if 255 - Z_256 /= 255 then
      Report (False);
      return;
   end if;

   if 255 * Z_256 /= 0 then
      Report (False);
      return;
   end if;

   if Z_256 / 255 /= 0 then
      Report (False);
      return;
   end if;

   if -Z_256 /= 0 then
      Report (False);
      return;
   end if;

   if Z_256 ** 2 /= 0 then
      Report (False);
      return;
   end if;

   if (Z_256 and 1) /= 0 then
      Report (False);
      return;
   end if;

   if (Z_256 or 1) /= 1 then
      Report (False);
      return;
   end if;

   if (Z_256 xor 1) /= 1 then
      Report (False);
      return;
   end if;

   if (not Z_256) /= 255 then
      Report (False);
      return;
   end if;

   if Mod_256'Succ (255 + Z_256) /= 0 then
      Report (False);
      return;
   end if;

   if Mod_256'Pred (Z_256) /= 255 then
      Report (False);
      return;
   end if;

   Report (True);
end B0012;
