------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Ada 2005. Check access types equality operator.
--

procedure A0009 is
   type Int_Access is access all Integer;
   type Proc_Access is access procedure;
   A, B   : Int_Access;
   X, Y   : access Integer;
   P, Q   : Proc_Access;
   S, T   : access procedure;
   Ignore : Boolean;
begin
   Ignore := A = null;
   Ignore := A = B;
   Ignore := X = null;
   Ignore := X = Y;
   Ignore := A = Y;
   Ignore := P = null;
   Ignore := P = Q;
   Ignore := S = null;
   Ignore := S = T;
   Ignore := P = T;
end;
