with A0020.A;
with A0020.B;
with A0020.B.C;

package body A0020 is

   package body Nested is
      function F1 (Left, Right : T7) return Boolean renames "=";

      procedure Use_Body is
      begin
         null;
      end;
   end Nested;

end;
