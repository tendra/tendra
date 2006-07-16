--  Purpose: Test basic statements
--  Dependencies:: standard.ads

procedure B0002 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report);

   X : Boolean;
   Y : Boolean;
begin
   null;

   X := True;

   if X = True then
      Y := False;
   else
      Y := True;
   end if;

   --  X = True, Y = False
   loop
      exit when Y = True;

      if Y = True then
         Y := False;
      else
         Y := True;
      end if;
   end loop;

   --  X = True, Y = True
   while X = True loop
      if Y = True then
         Y := False;
      else
         Y := True;
      end if;

      if X = True then
         X := False;
      else
         X := True;
      end if;
   end loop;

   --  X = False, Y = False
   if Y /= X then
      null;
   elsif X = False then
      Report (True);
      return;
   end if;

   Report (False);
end B0002;
