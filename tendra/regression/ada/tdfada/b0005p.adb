package B0005P is

   function The_Same (X : Boolean) return Boolean;

   type Int is range 0 .. 100;

   function The_Same (X : Int) return Int;

end;

package body B0005P is

   function The_Same (X : Boolean) return Boolean is
   begin
      return X;
   end The_Same;

   function The_Same (X : Int) return Int is
   begin
      return X;
   end The_Same;

end;
