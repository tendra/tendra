package A0028 is

   package Bbb is
      type T is (A, B, C);
      function "+" (Left : String) return T;
   end Bbb;

   package Ccc is   
      type T2 is new Bbb.T;
   end Ccc;
   
   use type Ccc.T2;

   X2 : Ccc.T2 := +"C";

end A0028;
