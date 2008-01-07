package body Encodings.Classes is

   function Get_Class
     (Object : in Coder;
      C      : in Wide_Character)
     return Character_Class;
   pragma Inline (Get_Class);

   ------------
   -- Decode --
   ------------

   procedure Decode
     (Text        : in     Raw_String;
      Text_Last   :    out Natural;
      Result      :    out Wide_String;
      Result_Last :    out Natural;
      Classes     :    out Character_Classes;
      Object      : in out Coder)
   is
      Index : Cache_Index;
      X     : Positive;
   begin
      Decode (Text, Text_Last, Result, Result_Last, Object.Map);

      if Object.Map = UTF_8 then
         for J in Result'First .. Result_Last loop
            Index := Wide_Character'Pos (Result (J)) mod Cache_Index'Last + 1;

            if Object.Wide (Index) = Result (J) and
              Object.Cache (Index) /= Unknown
            then
               Classes (J) := Object.Cache (Index);
            else
               Classes (J)          := Get_Class (Object, Result (J));
               Object.Cache (Index) := Classes (J);
               Object.Wide (Index)  := Result (J);

               if Classes (J) = Unknown then
                  Object.Prefix := Result (J);
               else
                  Object.Prefix := ' ';
               end if;
            end if;
         end loop;
      else
         X := Result'First;

         for J in Text'First .. Text_Last loop
            if Object.Classes (Text (J)) /= Unknown then
               Classes (X)               := Object.Classes (Text (J));
            else
               Classes (X)               := Get_Class (Object, Result (X));
               Object.Classes (Text (J)) := Classes (X);

               if Classes (X) = Unknown then
                  Object.Prefix := Result (X);
               else
                  Object.Prefix := ' ';
               end if;
            end if;

            X := X + 1;
         end loop;
      end if;
   end Decode;

   ---------------
   -- Get_Class --
   ---------------

   function Get_Class
     (Object : in Coder;
      C      : in Wide_Character) return Character_Class is
   begin
      if Object.Prefix = ' ' then
         return Get_Class ((1 => C));
      else
         return Get_Class (Object.Prefix & C);
      end if;
   end Get_Class;

end Encodings.Classes;
