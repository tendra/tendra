--  Auto generated file. Don't edit

package Encodings.Maps.KOI8_R is

   function Decode (Char : Character) return Wide_Character;
   pragma Inline (Decode);

   procedure Encode
     (Text        : in     Wide_String;
      Text_Last   :    out Natural;
      Result      :    out Raw_String;
      Result_Last :    out Natural;
      Map         : in     Encoding := Encodings.KOI8_R);

   procedure Decode
     (Text        : in     Raw_String;
      Text_Last   :    out Natural;
      Result      :    out Wide_String;
      Result_Last :    out Natural;
      Map         : in     Encoding := Encodings.KOI8_R);

end Encodings.Maps.KOI8_R;
