--  Auto generated file. Don't edit

package Encodings.Maps.ISO_8859_16 is

   function Decode (Char : Character) return Wide_Character;
   pragma Inline (Decode);

   procedure Encode
     (Text        : in     Wide_String;
      Text_Last   :    out Natural;
      Result      :    out Raw_String;
      Result_Last :    out Natural;
      Map         : in     Encoding := Encodings.ISO_8859_16);

   procedure Decode
     (Text        : in     Raw_String;
      Text_Last   :    out Natural;
      Result      :    out Wide_String;
      Result_Last :    out Natural;
      Map         : in     Encoding := Encodings.ISO_8859_16);

end Encodings.Maps.ISO_8859_16;
