------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Ada 2005. Check extended return statement
--

procedure A0015 is

   type My_Rec is record
      X : Integer;
   end record;

   function Value return Integer is
   begin
      return 0;
   end;

   function Value return My_Rec is
   begin
      return (X => 0);
   end;

   function Test return My_Rec is
      Result : Boolean;
   begin
      return
         Result : aliased My_Rec := Value
      do
        Result.X := 2;
      end return;
   end Test;

begin
   null;
end;
