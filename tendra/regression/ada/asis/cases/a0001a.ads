package A0001A is
   A : Integer;

   type Type_A is private;

   function "not" (Left : Integer) return Type_A;

private
   B : Integer;

   type Type_A is new Integer;
end;
