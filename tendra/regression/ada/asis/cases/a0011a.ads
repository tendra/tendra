with A0011;

package A0011A is
   type Item is private;

   package Nested is
      type Some_Record is record
         Object : A0011.Some_Access;
      end record;
   end Nested;

private
   type Item is null record;
end A0011A;
