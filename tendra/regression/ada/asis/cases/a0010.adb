------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Ada 2005. Check prefixed view interpretation.
--

procedure A0010 is

   package Inside is
      type T is tagged null record;
      procedure P1 (Item : T; X : Integer);
      procedure P2 (Item : T'Class; X : Boolean);

      type TT is new T with null record;

      function F1 (Item : TT; X : Integer) return Integer;
      function F2 (Item : TT) return Integer;
      procedure P3 (Item : TT);
   end Inside;

   package body Inside is
      procedure P1 (Item : T; X : Integer) is begin null; end;
      procedure P2 (Item : T'Class; X : Boolean) is begin null; end;
      procedure P3 (Item : TT) is begin null; end;

      function F1 (Item : TT; X : Integer) return Integer is
      begin
         return 0;
      end;

      function F2 (Item : TT) return Integer is
      begin
         return 0;
      end;
   end Inside;

   use Inside;

   OT  : T;
   OTT : TT;
   Int : Integer;

   procedure R1 (X : Boolean) renames OT.P2;

begin
   OT.P1 (1);
   OTT.P1 (1);
   OTT.P2 (True);
   OTT.P3;
   Int := OTT.F1 (1);
   Int := OTT.F2;
end A0010;
