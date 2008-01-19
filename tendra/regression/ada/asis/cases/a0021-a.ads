package A0021.A is
   type T2 is new T1 with null record;

   procedure R1 (Item : T2) renames P1;

   package Nested is
      procedure Use_Body;
      
      type T3 is new T1 with null record;
   end Nested;

private
   procedure R2 (Item : T2) renames P2;
end;
