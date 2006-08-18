function B0007P (X : Integer) return Integer is
begin
   if X = 1 then
      return 1;
   else
      return X * B0007P (X - 1);
   end if;
end B0007P;
