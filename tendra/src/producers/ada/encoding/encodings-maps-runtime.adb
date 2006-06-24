with Encodings.Read;

package body Encodings.Maps.Runtime is

   type Mapping_Access is access all Read.Mapping;

   Mapping_List : array (Encoding) of Mapping_Access;

   ------------
   -- Decode --
   ------------

   procedure Decode
     (Text        : in     Raw_String;
      Text_Last   :    out Natural;
      Result      :    out Wide_String;
      Result_Last :    out Natural;
      Map         : in     Encoding)
   is
   begin
      if Mapping_List (Map) = null then
         Mapping_List (Map) := new Read.Mapping'(Read.Table (File (Map)));
      end if;

      Decode (Text, Text_Last, Result, Result_Last,
              Forward => Mapping_List (Map).Forward);
   end Decode;

   ------------
   -- Encode --
   ------------

   procedure Encode
     (Text        : in     Wide_String;
      Text_Last   :    out Natural;
      Result      :    out Raw_String;
      Result_Last :    out Natural;
      Map         : in     Encoding)
   is
   begin
      if Mapping_List (Map) = null then
         Mapping_List (Map) := new Read.Mapping'(Read.Table (File (Map)));
      end if;

      Encode (Text, Text_Last, Result, Result_Last,
              Ranges   => Mapping_List (Map).Ranges,
              Backward => Mapping_List (Map).Backward);
   end Encode;

   ----------
   -- File --
   ----------

   function File (Map : Encoding) return String is
      --  Prefix is mirror of http://www.unicode.org/Public/MAPPINGS/
      Prefix : constant String := "data/";
   begin
      case Map is
         when ISO_8859_1 =>
            return Prefix & "ISO8859/8859-1.TXT";
         when ISO_8859_2 =>
            return Prefix & "ISO8859/8859-2.TXT";
         when ISO_8859_3 =>
            return Prefix & "ISO8859/8859-3.TXT";
         when ISO_8859_4 =>
            return Prefix & "ISO8859/8859-4.TXT";
         when ISO_8859_5 =>
            return Prefix & "ISO8859/8859-5.TXT";
         when ISO_8859_6 =>
            return Prefix & "ISO8859/8859-6.TXT";
         when ISO_8859_7 =>
            return Prefix & "ISO8859/8859-7.TXT";
         when ISO_8859_8 =>
            return Prefix & "ISO8859/8859-8.TXT";
         when ISO_8859_9 =>
            return Prefix & "ISO8859/8859-9.TXT";
         when ISO_8859_10 =>
            return Prefix & "ISO8859/8859-10.TXT";
         when ISO_8859_11 =>
            return Prefix & "ISO8859/8859-11.TXT";
         when ISO_8859_13 =>
            return Prefix & "ISO8859/8859-13.TXT";
         when ISO_8859_14 =>
            return Prefix & "ISO8859/8859-14.TXT";
         when ISO_8859_15 =>
            return Prefix & "ISO8859/8859-15.TXT";
         when ISO_8859_16 =>
            return Prefix & "ISO8859/8859-16.TXT";
         when CP_037 =>
            return Prefix & "VENDORS/MICSFT/EBCDIC/CP037.TXT";
         when CP_500 =>
            return Prefix & "VENDORS/MICSFT/EBCDIC/CP500.TXT";
         when CP_875 =>
            return Prefix & "VENDORS/MICSFT/EBCDIC/CP875.TXT";
         when CP_1026 =>
            return Prefix & "VENDORS/MICSFT/EBCDIC/CP1026.TXT";
         when CP_874 =>
            return Prefix & "VENDORS/MICSFT/WINDOWS/CP874.TXT";
         when CP_1250 =>
            return Prefix & "VENDORS/MICSFT/WINDOWS/CP1250.TXT";
         when CP_1251 =>
            return Prefix & "VENDORS/MICSFT/WINDOWS/CP1251.TXT";
         when CP_1252 =>
            return Prefix & "VENDORS/MICSFT/WINDOWS/CP1252.TXT";
         when CP_1253 =>
            return Prefix & "VENDORS/MICSFT/WINDOWS/CP1253.TXT";
         when CP_1254 =>
            return Prefix & "VENDORS/MICSFT/WINDOWS/CP1254.TXT";
         when CP_1255 =>
            return Prefix & "VENDORS/MICSFT/WINDOWS/CP1255.TXT";
         when CP_1256 =>
            return Prefix & "VENDORS/MICSFT/WINDOWS/CP1256.TXT";
         when CP_1257 =>
            return Prefix & "VENDORS/MICSFT/WINDOWS/CP1257.TXT";
         when CP_1258 =>
            return Prefix & "VENDORS/MICSFT/WINDOWS/CP1258.TXT";
         when CP_437 =>
            return Prefix & "VENDORS/MICSFT/PC/CP437.TXT";
         when CP_737 =>
            return Prefix & "VENDORS/MICSFT/PC/CP737.TXT";
         when CP_775 =>
            return Prefix & "VENDORS/MICSFT/PC/CP775.TXT";
         when CP_850 =>
            return Prefix & "VENDORS/MICSFT/PC/CP850.TXT";
         when CP_852 =>
            return Prefix & "VENDORS/MICSFT/PC/CP852.TXT";
         when CP_855 =>
            return Prefix & "VENDORS/MICSFT/PC/CP855.TXT";
         when CP_857 =>
            return Prefix & "VENDORS/MICSFT/PC/CP857.TXT";
         when CP_860 =>
            return Prefix & "VENDORS/MICSFT/PC/CP860.TXT";
         when CP_861 =>
            return Prefix & "VENDORS/MICSFT/PC/CP861.TXT";
         when CP_862 =>
            return Prefix & "VENDORS/MICSFT/PC/CP862.TXT";
         when CP_863 =>
            return Prefix & "VENDORS/MICSFT/PC/CP863.TXT";
         when CP_864 =>
            return Prefix & "VENDORS/MICSFT/PC/CP864.TXT";
         when CP_865 =>
            return Prefix & "VENDORS/MICSFT/PC/CP865.TXT";
         when CP_866 =>
            return Prefix & "VENDORS/MICSFT/PC/CP866.TXT";
         when CP_869 =>
            return Prefix & "VENDORS/MICSFT/PC/CP869.TXT";
         when AtariST =>
            return Prefix & "VENDORS/MISC/ATARIST.TXT";
         when CP_1006 =>
            return Prefix & "VENDORS/MISC/CP1006.TXT";
         when CP_424 =>
            return Prefix & "VENDORS/MISC/CP424.TXT";
         when CP_856 =>
            return Prefix & "VENDORS/MISC/CP856.TXT";
         when KOI8_R =>
            return Prefix & "VENDORS/MISC/KOI8-R.TXT";
         when Unknown | UTF_8 =>
            return "";
      end case;
   end File;

begin
   Encoder_List (Unknown) := Encode'Access;
   Decoder_List (Unknown) := Decode'Access;
end Encodings.Maps.Runtime;

