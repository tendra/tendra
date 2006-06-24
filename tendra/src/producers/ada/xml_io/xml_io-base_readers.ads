with Encodings;

generic
   type XML_Character is (<>);
   type XML_String    is array (Positive range <>) of XML_Character;

   Nil_String : in XML_String;

package XML_IO.Base_Readers is

   ------------
   -- Reader --
   ------------

   type Reader is abstract tagged limited null record;

   function More_Pieces (Parser : in Reader) return Boolean     is abstract;
   function Piece_Kind  (Parser : in Reader) return Piece_Kinds is abstract;

   procedure Next (Parser : in out Reader)
      is abstract;

   function Encoding    (Parser : in Reader) return XML_String  is abstract;
   function Encoding    (Parser : in Reader) return Encodings.Encoding
      is abstract;
   --  Piece: Start_Document

   function Standalone  (Parser : in Reader) return Boolean     is abstract;
   --  Piece: Start_Document

   function Text        (Parser : in Reader) return XML_String is abstract;
   --  Piece: Characters, Processing_Instruction, Comment

   function Name        (Parser : in Reader) return XML_String  is abstract;
   --  Piece: Start_Element, End_Element, Processing_Instruction

   function Attribute_Count (Parser : in Reader) return List_Count
      is abstract;
   --  Piece: Start_Element

   function Attribute_Name
     (Parser : in Reader;
      Index  : in List_Index) return XML_String
      is abstract;
   --  Piece: Start_Element

   function Attribute_Value
     (Parser : in Reader;
      Index  : in List_Index) return XML_String
      is abstract;
   --  Piece: Start_Element

   function Attribute_Value
     (Parser      : in Reader;
      Name        : in XML_String;
      Default     : in XML_String := Nil_String;
      Raise_Error : in Boolean := False) return XML_String
      is abstract;
   --  Piece: Start_Element

end XML_IO.Base_Readers;
