package body A0021.A is
   package body Nested is
      procedure Use_Body is
      begin
         null;
      end;

      procedure R2 (Item : T3) renames P2;
   end Nested;
end;
