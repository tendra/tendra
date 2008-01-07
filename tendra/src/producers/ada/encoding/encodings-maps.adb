package body Encodings.Maps is

   ------------
   -- Decode --
   ------------

   function Decode
     (Char     : Character;
      Forward  : Forward_Map)
      return Wide_Character
   is
   begin
      if Char in Forward'Range then
         if Forward (Char) = Undefined then
            raise Invalid_Encoding;
         else
            return Forward (Char);
         end if;
      else
         return Wide_Character'Val (Character'Pos (Char));
      end if;
   end Decode;

   ------------
   -- Decode --
   ------------

   procedure Decode
     (Text        : in     Raw_String;
      Text_Last   :    out Natural;
      Result      :    out Wide_String;
      Result_Last :    out Natural;
      Forward     : in     Forward_Map)
   is
      Length : Natural := Text'Length;
   begin
      if Length > Result'Length then
         Length := Result'Length;
      end if;

      for I in 1 .. Length loop
         Result (Result'First + I - 1) :=
           Decode (Text (Text'First + I - 1), Forward);
      end loop;

      Text_Last := Text'First + Length - 1;
      Result_Last := Result'First + Length - 1;
   end Decode;

   ------------
   -- Encode --
   ------------

   function Encode
     (Char     : Wide_Character;
      Ranges   : Wide_Ranges;
      Backward : Backward_Map)
      return Character
   is
      subtype W is Wide_Character;

      Lower : Range_Count := Ranges'First;
      Upper : Range_Count := Ranges'Last;
      Index : Range_Index;
      From  : Backward_Index;
   begin
      loop
         if Upper < Lower then
            raise Invalid_Encoding;
         end if;

         Index := (Upper + Lower) / 2;

         if Char < Ranges (Index).Lower then
            Upper := Index - 1;
         elsif Char > Ranges (Index).Upper then
            Lower := Index + 1;
         else
            From := Ranges (Index).Index +
              W'Pos (Char) - W'Pos (Ranges (Index).Lower);

            return Backward (From);
         end if;
      end loop;
   end Encode;

   ------------
   -- Encode --
   ------------

   procedure Encode
     (Text        : in     Wide_String;
      Text_Last   :    out Natural;
      Result      :    out Raw_String;
      Result_Last :    out Natural;
      Ranges      : in     Wide_Ranges;
      Backward    : in     Backward_Map)
   is
      Length : Natural := Text'Length;
   begin
      if Length > Result'Length then
         Length := Result'Length;
      end if;

      for I in 1 .. Length loop
         Result (Result'First + I - 1) :=
           Encode (Text (Text'First + I - 1), Ranges, Backward);
      end loop;

      Text_Last := Text'First + Length - 1;
      Result_Last := Result'First + Length - 1;
   end Encode;

end Encodings.Maps;

