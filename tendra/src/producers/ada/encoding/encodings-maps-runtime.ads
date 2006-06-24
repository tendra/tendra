--  This package tries to load encoding tables from file
--  at runtime using Encodings.Read

package Encodings.Maps.Runtime is

   procedure Encode
     (Text        : in     Wide_String;
      Text_Last   :    out Natural;
      Result      :    out Raw_String;
      Result_Last :    out Natural;
      Map         : in     Encoding);

   procedure Decode
     (Text        : in     Raw_String;
      Text_Last   :    out Natural;
      Result      :    out Wide_String;
      Result_Last :    out Natural;
      Map         : in     Encoding);

   function File (Map : Encoding) return String;

end Encodings.Maps.Runtime;
