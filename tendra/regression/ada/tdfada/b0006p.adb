package B0006P is

   --  This procedure does nothing. It's used to avoid optimization.
   procedure Nothing (X, Y : in out Boolean);

   --  Call to this function results in test failure
   function Never_Call return Boolean;
end;

package body B0006P is

   procedure Nothing (X, Y : in out Boolean) is
   begin
      null;
   end;

   function Never_Call return Boolean is
      procedure Report (Status : Boolean);
      pragma Import (C, Report, "Report");
   begin
      Report (False);

      return False;
   end;

end;
