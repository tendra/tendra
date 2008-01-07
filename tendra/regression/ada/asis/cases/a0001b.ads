package A0001B is
   B : Integer;

   type Type_B is private;

   function "not" (Left : Integer) return Type_B;

private
   A : Integer;

   type Type_B is new Integer;
end;
