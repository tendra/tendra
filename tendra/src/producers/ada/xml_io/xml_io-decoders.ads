with XML_IO.Readers;
with XML_IO.Internals;
with Encodings.Unicode;
with Ada.Strings.Unbounded;

package XML_IO.Decoders is
   use Encodings;
   use Ada.Strings.Unbounded;

   subtype Unicode_Character is Internals.Unicode_Character;

   package Implementation is new Internals.Implementation
     (XML_Unbounded        => Unbounded_String,
      Decode               => Unicode.Decode,
      Readers              => Readers,
      To_XML_String        => To_Unbounded_String,
      To_Encoding          => To_Encoding,
      Nil_Literal          => "");

end XML_IO.Decoders;
