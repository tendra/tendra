--  Purpose: Test Boolean operations (result as value).
--  Dependencies:: b0004p.adb standard.ads

with B0004P; use B0004P;

procedure B0004 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "Report");

   Result : Boolean;
begin
   And_Operator (True, True, Result);

   if not Result then
      Report (False);
      return;
   end if;

   And_Operator (False, True, Result);

   if Result then
      Report (False);
      return;
   end if;

   Or_Operator (False, False, Result);

   if Result then
      Report (False);
      return;
   end if;

   Or_Operator (False, True, Result);

   if not Result then
      Report (False);
      return;
   end if;

   Xor_Operator (True, True, Result);

   if Result then
      Report (False);
      return;
   end if;

   Xor_Operator (False, True, Result);

   if not Result then
      Report (False);
      return;
   end if;

   Equal_Operator (True, True, Result);

   if not Result then
      Report (False);
      return;
   end if;

   Equal_Operator (False, True, Result);

   if Result then
      Report (False);
      return;
   end if;

   Not_Equal_Operator (True, True, Result);

   if Result then
      Report (False);
      return;
   end if;

   Not_Equal_Operator (False, True, Result);

   if not Result then
      Report (False);
      return;
   end if;

   Less_Than_Operator (True, True, Result);

   if Result then
      Report (False);
      return;
   end if;

   Less_Than_Operator (False, True, Result);

   if not Result then
      Report (False);
      return;
   end if;

   Less_Than_Or_Equal_Operator (True, True, Result);

   if not Result then
      Report (False);
      return;
   end if;

   Less_Than_Or_Equal_Operator (True, False, Result);

   if Result then
      Report (False);
      return;
   end if;

   Greater_Than_Operator (True, True, Result);

   if Result then
      Report (False);
      return;
   end if;

   Greater_Than_Operator (True, False, Result);

   if not Result then
      Report (False);
      return;
   end if;

   Greater_Than_Or_Equal_Operator (True, True, Result);

   if not Result then
      Report (False);
      return;
   end if;

   Greater_Than_Or_Equal_Operator (False, True, Result);

   if Result then
      Report (False);
      return;
   end if;

   Not_Operator (True, Result);

   if Result then
      Report (False);
      return;
   end if;

   Not_Operator (False, Result);

   if not Result then
      Report (False);
      return;
   end if;

   And_Then_Operator (True, True, Result);

   if not Result then
      Report (False);
      return;
   end if;

   And_Then_Operator (False, True, Result);

   if Result then
      Report (False);
      return;
   end if;

   Or_Else_Operator (False, False, Result);

   if Result then
      Report (False);
      return;
   end if;

   Or_Else_Operator (False, True, Result);

   if not Result then
      Report (False);
      return;
   end if;

   Report (True);
end;
