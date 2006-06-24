with Encodings;
with Ada.Text_IO;

procedure Test is
   use Encodings;

   Text_1 : String :=
     Character'Val (16#D0#)
     & Character'Val (16#9F#)
     & Character'Val (16#D1#)
     & Character'Val (16#80#)
     & Character'Val (16#D0#)
     & Character'Val (16#B8#)
     & Character'Val (16#D0#)
     & Character'Val (16#B2#)
     & Character'Val (16#D0#)
     & Character'Val (16#B5#)
     & Character'Val (16#D1#)
     & Character'Val (16#82#);
   Wide_1 : Wide_String := Decode (Text_1, UTF_8);
   Text_2 : String := Encode (Wide_1, KOI8_R);
   Wide_2 : Wide_String := Decode (Text_2, KOI8_R);
   Text_3 : String := Encode (Wide_2, CP_1251);
   Wide_3 : Wide_String := Decode (Text_3, CP_1251);
   Text_4 : String := Encode (Wide_3, ISO_8859_5);
   Wide_4 : Wide_String := Decode (Text_4, ISO_8859_5);
begin
   if Wide_1 /= Wide_4 then
      Ada.Text_IO.Put_Line ("Fail");
   else
      Ada.Text_IO.Put_Line ("Pass");
   end if;
end Test;
