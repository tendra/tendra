package A0020.A is
   type T5 is new T2;
private
   function F1 (Left, Right : T5) return T5 renames "&";
end;
