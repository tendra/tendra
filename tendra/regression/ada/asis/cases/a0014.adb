------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Ada 2005. Check box in aggregates
--

procedure A0014 is

   type My_Rec is record
      X : Integer;
      Y : Float;
      Z : Boolean;
   end record;

   Text_1 : constant String (1 .. 10) := (1 .. 3 => 'A', others => <>);
   Text_2 : constant String (1 .. 10) := ('A', 'B', others => <>);
   Rec    : constant My_Rec := (X => 1, others => <>);
begin
   null;
end;
