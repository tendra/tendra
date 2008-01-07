------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Ada 2005. Anonimous access types in other constructs.
--

procedure A0008 is

   Object : access Integer := null;

   An_Array : array (Boolean) of access Integer;

   type Rec (D : access Boolean) is record
      Component : access Integer;
   end record;

   generic
      Formal_Object_Declaration : access Integer;
   procedure Generic_Proc;

   procedure Generic_Proc is
   begin
      Formal_Object_Declaration.all := 1;
   end;

begin
   null;
end;
