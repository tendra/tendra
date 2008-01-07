--  Purpose: test signed integer operations
--  Dependencies:: standard.ads

procedure B0010 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "Report");
   
   type Int is range -1000 .. 1000;
   A : Int := 10;
   B : Int := 11;
   C : Int := 5;
begin
   if A = B  then Report (False); return; end if;
   if A /= B - 1  then Report (False); return; end if;
   if A < C then Report (False); return; end if;
   if A <= C then Report (False); return; end if;
   if A > B then Report (False); return; end if;
   if A >= B then Report (False); return; end if;

   if A + B /= 21 then Report (False); return; end if;
   if A + C /= 15 then Report (False); return; end if;

   if A - B /= -1 then Report (False); return; end if;
   if A - C /= 5 then Report (False); return; end if;

   if +A /= 10 then Report (False); return; end if;
   if -A /= -10 then Report (False); return; end if;

   if A * B /= 110 then Report (False); return; end if;
   if -A * C /= -50 then Report (False); return; end if;

   if A / C /= 2 then Report (False); return; end if;
   if A rem C /= 0 then Report (False); return; end if;
   if A mod C /= 0 then Report (False); return; end if;

   if B / C /= 2 then Report (False); return; end if;
   if B rem C /= 1 then Report (False); return; end if;
   if B mod C /= 1 then Report (False); return; end if;

   if (-A) / C /= -2 then Report (False); return; end if;
   if (-A) rem C /= 0 then Report (False); return; end if;
   if (-A) mod C /= 0 then Report (False); return; end if;

   if (-B) / C /= -2 then Report (False); return; end if;
   if (-B) rem C /= -1 then Report (False); return; end if;
   if (-B) mod C /= 4 then Report (False); return; end if;

   if A / (-C) /= -2 then Report (False); return; end if;
   if A rem (-C) /= 0 then Report (False); return; end if;
   if A mod (-C) /= 0 then Report (False); return; end if;

   if B / (-C) /= -2 then Report (False); return; end if;
   if B rem (-C) /= 1 then Report (False); return; end if;
   if B mod (-C) /= -4 then Report (False); return; end if;

   if (-A) / (-C) /= 2 then Report (False); return; end if;
   if (-A) rem (-C) /= 0 then Report (False); return; end if;
   if (-A) mod (-C) /= 0 then Report (False); return; end if;

   if (-B) / (-C) /= 2 then Report (False); return; end if;
   if (-B) rem (-C) /= -1 then Report (False); return; end if;
   if (-B) mod (-C) /= -1 then Report (False); return; end if;

   if C ** 4 /= 625 then Report (False); return; end if;

   if abs (A) /= 10 then Report (False); return; end if;
   if abs (C - A) /= 5 then Report (False); return; end if;

   Report (True);
end B0010;
