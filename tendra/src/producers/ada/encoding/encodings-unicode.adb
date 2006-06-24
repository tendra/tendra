with Encodings.Maps.ISO_8859_1;
with Encodings.Maps.ISO_8859_2;
with Encodings.Maps.ISO_8859_3;
with Encodings.Maps.ISO_8859_4;
with Encodings.Maps.ISO_8859_5;
with Encodings.Maps.ISO_8859_6;
with Encodings.Maps.ISO_8859_7;
with Encodings.Maps.ISO_8859_8;
with Encodings.Maps.ISO_8859_9;
with Encodings.Maps.ISO_8859_10;
with Encodings.Maps.ISO_8859_11;
with Encodings.Maps.ISO_8859_13;
with Encodings.Maps.ISO_8859_14;
with Encodings.Maps.ISO_8859_15;
with Encodings.Maps.ISO_8859_16;
with Encodings.Maps.CP_037;
with Encodings.Maps.CP_424;
with Encodings.Maps.CP_437;
with Encodings.Maps.CP_500;
with Encodings.Maps.CP_737;
with Encodings.Maps.CP_775;
with Encodings.Maps.CP_850;
with Encodings.Maps.CP_852;
with Encodings.Maps.CP_855;
with Encodings.Maps.CP_856;
with Encodings.Maps.CP_857;
with Encodings.Maps.CP_860;
with Encodings.Maps.CP_861;
with Encodings.Maps.CP_862;
with Encodings.Maps.CP_863;
with Encodings.Maps.CP_864;
with Encodings.Maps.CP_865;
with Encodings.Maps.CP_866;
with Encodings.Maps.CP_869;
with Encodings.Maps.CP_874;
with Encodings.Maps.CP_875;
with Encodings.Maps.CP_1006;
with Encodings.Maps.CP_1026;
with Encodings.Maps.CP_1250;
with Encodings.Maps.CP_1251;
with Encodings.Maps.CP_1252;
with Encodings.Maps.CP_1253;
with Encodings.Maps.CP_1254;
with Encodings.Maps.CP_1255;
with Encodings.Maps.CP_1256;
with Encodings.Maps.CP_1257;
with Encodings.Maps.CP_1258;
with Encodings.Maps.AtariST;
with Encodings.Maps.KOI8_R;

package body Encodings.Unicode is

   ------------
   -- Decode --
   ------------

   procedure Decode
     (Buffer : in     String;
      Index  : in out Positive;
      Free   : in     Positive;
      Map    : in     Encoding;
      Char   :    out Unicode_Character)
   is
      subtype C is Character;
      subtype W is Wide_Character;

      Ind : Positive := Index;

      function Continuing return Boolean is
      begin
         if Ind = Buffer'Last then
            Ind := Buffer'First;
         else
            Ind := Ind + 1;
         end if;

         if Ind = Free then
            Char := Empty_Buffer;
            return False;
         elsif C'Pos (Buffer (Ind)) in 2#1000_0000# .. 2#1011_1111# then
            Char := (Char * 2 ** 6) or (C'Pos (Buffer (Ind)) and 2#0011_1111#);
            return True;
         else
            raise Invalid_Encoding;
         end if;
      end Continuing;
      pragma Inline (Continuing);
   begin
      if Ind = Free then
         Char := Empty_Buffer;
         return;
      end if;

      case Map is
         when UTF_8 =>
           case C'Pos (Buffer (Ind)) is
              when 2#0000_0000# .. 2#0111_1111# =>
                 Char := C'Pos (Buffer (Ind));
              when 2#1100_0000# .. 2#1101_1111# =>
                 Char := C'Pos (Buffer (Ind)) and 2#0001_1111#;

                 if not Continuing then
                    return;
                 end if;

              when 2#1110_0000# .. 2#1110_1111# =>
                 Char := C'Pos (Buffer (Ind)) and 2#0000_1111#;

                 if not (Continuing and then Continuing) then
                    return;
                 end if;

              when 2#1111_0000# .. 2#1111_0111# =>
                 Char := C'Pos (Buffer (Ind)) and 2#0000_0111#;

                 if not (Continuing and then Continuing and then Continuing)
                 then
                    return;
                 end if;

              when 2#1111_1000# .. 2#1111_1011# =>
                 Char := C'Pos (Buffer (Ind)) and 2#0000_0011#;

                 if not (Continuing and then Continuing
                   and then Continuing  and then Continuing)
                 then
                    return;
                 end if;

              when 2#1111_1100# .. 2#1111_1101# =>
                 Char := C'Pos (Buffer (Ind)) and 2#0000_0001#;

                 if not (Continuing and then Continuing and then Continuing
                   and then Continuing  and then Continuing)
                 then
                    return;
                 end if;

              when others =>
                 raise Invalid_Encoding;
           end case;

         when ISO_8859_1 =>
            Char := W'Pos (Maps.ISO_8859_1.Decode (Buffer (Ind)));
         when ISO_8859_2 =>
            Char := W'Pos (Maps.ISO_8859_2.Decode (Buffer (Ind)));
         when ISO_8859_3 =>
            Char := W'Pos (Maps.ISO_8859_3.Decode (Buffer (Ind)));
         when ISO_8859_4 =>
            Char := W'Pos (Maps.ISO_8859_4.Decode (Buffer (Ind)));
         when ISO_8859_5 =>
            Char := W'Pos (Maps.ISO_8859_5.Decode (Buffer (Ind)));
         when ISO_8859_6 =>
            Char := W'Pos (Maps.ISO_8859_6.Decode (Buffer (Ind)));
         when ISO_8859_7 =>
            Char := W'Pos (Maps.ISO_8859_7.Decode (Buffer (Ind)));
         when ISO_8859_8 =>
            Char := W'Pos (Maps.ISO_8859_8.Decode (Buffer (Ind)));
         when ISO_8859_9 =>
            Char := W'Pos (Maps.ISO_8859_9.Decode (Buffer (Ind)));
         when ISO_8859_10 =>
            Char := W'Pos (Maps.ISO_8859_10.Decode (Buffer (Ind)));
         when ISO_8859_11 =>
            Char := W'Pos (Maps.ISO_8859_11.Decode (Buffer (Ind)));
         when ISO_8859_13 =>
            Char := W'Pos (Maps.ISO_8859_13.Decode (Buffer (Ind)));
         when ISO_8859_14 =>
            Char := W'Pos (Maps.ISO_8859_14.Decode (Buffer (Ind)));
         when ISO_8859_15 =>
            Char := W'Pos (Maps.ISO_8859_15.Decode (Buffer (Ind)));
         when ISO_8859_16 =>
            Char := W'Pos (Maps.ISO_8859_16.Decode (Buffer (Ind)));
         when CP_037 =>
            Char := W'Pos (Maps.CP_037.Decode (Buffer (Ind)));
         when CP_424 =>
            Char := W'Pos (Maps.CP_424.Decode (Buffer (Ind)));
         when CP_437 =>
            Char := W'Pos (Maps.CP_437.Decode (Buffer (Ind)));
         when CP_500 =>
            Char := W'Pos (Maps.CP_500.Decode (Buffer (Ind)));
         when CP_875 =>
            Char := W'Pos (Maps.CP_875.Decode (Buffer (Ind)));
         when CP_737 =>
            Char := W'Pos (Maps.CP_737.Decode (Buffer (Ind)));
         when CP_775 =>
            Char := W'Pos (Maps.CP_775.Decode (Buffer (Ind)));
         when CP_850 =>
            Char := W'Pos (Maps.CP_850.Decode (Buffer (Ind)));
         when CP_852 =>
            Char := W'Pos (Maps.CP_852.Decode (Buffer (Ind)));
         when CP_855 =>
            Char := W'Pos (Maps.CP_855.Decode (Buffer (Ind)));
         when CP_856 =>
            Char := W'Pos (Maps.CP_856.Decode (Buffer (Ind)));
         when CP_857 =>
            Char := W'Pos (Maps.CP_857.Decode (Buffer (Ind)));
         when CP_860 =>
            Char := W'Pos (Maps.CP_860.Decode (Buffer (Ind)));
         when CP_861 =>
            Char := W'Pos (Maps.CP_861.Decode (Buffer (Ind)));
         when CP_862 =>
            Char := W'Pos (Maps.CP_862.Decode (Buffer (Ind)));
         when CP_863 =>
            Char := W'Pos (Maps.CP_863.Decode (Buffer (Ind)));
         when CP_864 =>
            Char := W'Pos (Maps.CP_864.Decode (Buffer (Ind)));
         when CP_865 =>
            Char := W'Pos (Maps.CP_865.Decode (Buffer (Ind)));
         when CP_866 =>
            Char := W'Pos (Maps.CP_866.Decode (Buffer (Ind)));
         when CP_869 =>
            Char := W'Pos (Maps.CP_869.Decode (Buffer (Ind)));
         when CP_874 =>
            Char := W'Pos (Maps.CP_874.Decode (Buffer (Ind)));
         when CP_1006 =>
            Char := W'Pos (Maps.CP_1006.Decode (Buffer (Ind)));
         when CP_1026 =>
            Char := W'Pos (Maps.CP_1026.Decode (Buffer (Ind)));
         when CP_1250 =>
            Char := W'Pos (Maps.CP_1250.Decode (Buffer (Ind)));
         when CP_1251 =>
            Char := W'Pos (Maps.CP_1251.Decode (Buffer (Ind)));
         when CP_1252 =>
            Char := W'Pos (Maps.CP_1252.Decode (Buffer (Ind)));
         when CP_1253 =>
            Char := W'Pos (Maps.CP_1253.Decode (Buffer (Ind)));
         when CP_1254 =>
            Char := W'Pos (Maps.CP_1254.Decode (Buffer (Ind)));
         when CP_1255 =>
            Char := W'Pos (Maps.CP_1255.Decode (Buffer (Ind)));
         when CP_1256 =>
            Char := W'Pos (Maps.CP_1256.Decode (Buffer (Ind)));
         when CP_1257 =>
            Char := W'Pos (Maps.CP_1257.Decode (Buffer (Ind)));
         when CP_1258 =>
            Char := W'Pos (Maps.CP_1258.Decode (Buffer (Ind)));
         when KOI8_R =>
            Char := W'Pos (Maps.KOI8_R.Decode (Buffer (Ind)));
         when AtariST =>
            Char := W'Pos (Maps.AtariST.Decode (Buffer (Ind)));
         when Unknown =>
            raise Invalid_Encoding;
      end case;

      if Ind = Buffer'Last then
         Index := Buffer'First;
      else
         Index := Ind + 1;
      end if;
   end Decode;

end Encodings.Unicode;

