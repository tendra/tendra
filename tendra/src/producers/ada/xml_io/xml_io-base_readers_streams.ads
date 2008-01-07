with Text_Streams;
with XML_IO.Internals;
with XML_IO.Base_Readers;

generic
   with package Implementation is new XML_IO.Internals.Implementation (<>);

   type Input_Stream (Input : access Text_Streams.Text_Stream'Class) is
     limited private;

   with procedure Read
     (Input  : in out Input_Stream;
      Buffer : in out Implementation.XML_String;
      Free   :    out Natural);

package XML_IO.Base_Readers_Streams is

   package Base_Readers renames Implementation.Readers;
   subtype XML_String   is Implementation.XML_String;

   type Reader (Input       : access Text_Streams.Text_Stream'Class;
                Buffer_Size : Positive) is
     new Base_Readers.Reader with private;

   function More_Pieces     (Parser : in Reader) return Boolean;
   function Piece_Kind      (Parser : in Reader) return Piece_Kinds;
   function Encoding        (Parser : in Reader) return XML_String;
   function Standalone      (Parser : in Reader) return Boolean;
   function Text            (Parser : in Reader) return XML_String;
   function Name            (Parser : in Reader) return XML_String;
   function Attribute_Count (Parser : in Reader) return List_Count;

   procedure Initialize     (Parser : in out Reader);
   procedure Next (Parser : in out Reader);


   function Attribute_Name
     (Parser : in Reader;
      Index  : in List_Index) return XML_String;

   function Attribute_Value
     (Parser : in Reader;
      Index  : in List_Index) return XML_String;

   function Attribute_Value
     (Parser      : in Reader;
      Name        : in XML_String;
      Default     : in XML_String := Implementation.Nil_Literal;
      Raise_Error : in Boolean := False) return XML_String;

   Default_Buffer_Size : constant Positive := 8192;

private

   type Reader (Input       : access Text_Streams.Text_Stream'Class;
                Buffer_Size : Positive) is
     new Implementation.Reader with record
        Stream : Input_Stream (Input);
        Buffer : Xml_String (1 .. Buffer_Size);
     end record;

   procedure Read
     (Parser : in out Reader;
      Buffer : in out XML_String;
      Last   :    out Natural);

end XML_IO.Base_Readers_Streams;
