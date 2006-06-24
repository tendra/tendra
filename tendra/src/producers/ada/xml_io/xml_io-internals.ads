with Ada.Finalization;
with Encodings.Unicode;
with XML_IO.Base_Readers;

package XML_IO.Internals is

   subtype Unicode_Character is Encodings.Unicode.Unicode_Character;

   Invalid_Character : constant Unicode_Character :=
     Encodings.Unicode.Empty_Buffer;

   type Character_Class is
     (' ',  --  space, tab, lf, cr
      '!', '"', '#',
      '$',  --
      '&', ''', '-',
      '.',  --
      '/',
      '0',  --  0 .. 9
      ';', '<', '=', '>', '?',
      'A',  -- A .. F a .. f
      'X',  --
      '[', ']',
      'x',
      'z', -- yz
      Bad_Character, End_Of_Buffer
      );

   function Get_Class
     (Char : in Unicode_Character) return Character_Class;

   type Internal_State is
     (In_Misc,
      In_PI,
      In_Content,
      In_Comment,
      In_Element,
      In_Empty_Element,
      In_Apostrophes,
      In_Quotes,
      In_CD_Start,
      In_CD);

   type Token is
     (Comment_Text_Token,      --  ...-->
      Name_Token,
      PI_Text_Token,           --  ...?>
      Value_Token,             --  ..['"]
      Char_Data_Token,
      Entity_Reference_Token,  --  &Name;
      Char_Reference_Token,    --  &#...;
      CData_Token,             --  ...]]>

      Space_Token,
      Start_Token,             --  '<'
      PI_Token,                --  '<?'
      Doctype_Token,           --  '<!'
      Comment_Token,           --  '<!--'
      Eq_Token,                --  '='
      Apostrophe_Token,        --  '''
      Quote_Token,             --  '"'
      PI_End_Token,            --  '?>'
      Empty_End_Token,         --  '/>'
      End_Element_Token,       --  '>'
      End_Token,               --  '</'
      CD_Start_Token,          --  '<!['
      Square_Token,            --  '['
      End_Of_Buffer,
      End_Of_File,
      Error);

   subtype Text_Token is Token range Comment_Text_Token .. CData_Token;

   generic
      with package Readers is
        new XML_IO.Base_Readers (<>);

      with procedure Decode
        (Buffer   : in     Readers.XML_String;
         Index    : in out Positive;
         Free     : in     Positive;
         Encoding : in     Encodings.Encoding;
         Char     :    out Unicode_Character);

      with function To_Encoding
        (Name : Readers.XML_String) return Encodings.Encoding;

      type XML_Unbounded   is private;

      with function To_Unbounded_String
        (Source : in Readers.XML_String)
        return XML_Unbounded is <>;

      with function To_String
        (Source : in XML_Unbounded)
        return Readers.XML_String is <>;

      with function "="
        (Left  : in Readers.XML_String;
         Right : in XML_Unbounded)
        return Boolean is <>;

      with function "&"
        (Left  : in XML_Unbounded;
         Right : in Readers.XML_String)
        return XML_Unbounded is <>;

      with function "&"
        (Left  : in XML_Unbounded;
         Right : in XML_Unbounded)
        return XML_Unbounded is <>;

      with function To_XML_String
        (Source : in String)
        return XML_Unbounded is <>;

      Nil_Literal          : in Readers.XML_String;  --  "";

   package Implementation is

      subtype XML_String is Readers.XML_String;

      type Token_Value is private;

      function Value
        (Buffer : in XML_String;
         Data   : in Token_Value) return XML_String;

      type Reader is abstract new Readers.Reader with private;

      function More_Pieces (Parser : in Reader) return Boolean;
      function Piece_Kind  (Parser : in Reader) return Piece_Kinds;

      procedure Next
        (Buffer : in out XML_String;
         Parser : in out Reader);

      function Encoding        (Parser : in Reader) return Token_Value;
      function Encoding        (Parser : in Reader) return Encodings.Encoding;
      function Standalone      (Parser : in Reader) return Boolean;
      function Text            (Parser : in Reader) return Token_Value;
      function Name            (Parser : in Reader) return Token_Value;
      function Attribute_Count (Parser : in Reader) return List_Count;

      function Attribute_Name
        (Parser : in Reader;
         Index  : in List_Index) return Token_Value;

      function Attribute_Value
        (Parser : in Reader;
         Index  : in List_Index) return Token_Value;

      procedure Initialize
        (Buffer : in out XML_String;
         Parser : in out Reader);

      procedure Read
        (Parser : in out Reader;
         Buffer : in out XML_String;
         Last   :    out Natural)
         is abstract;

   private

      type Token_Value is record
         From   : Natural;        --  0 if not started
         To     : Natural;        --  0 if not finished
         Stored : XML_Unbounded;  --  saved part
      end record;

      type Token_Values is array (List_Index range <>) of Token_Value;
      type Token_Values_Access is access all Token_Values;

      Embeded_Attr : constant := 8;

      type Piece_State (Kind : Piece_Kinds := End_Document) is record
         case Kind is
            when Start_Document =>
               Encoding     : Token_Value;
               Standalone   : Boolean;

            when DTD | End_Document =>
               null;

            when Start_Element
              | Entity_Reference
              | End_Element
              | Processing_Instruction
              | Attribute
              | Namespace
              =>
               Name         : Token_Value;

               case Kind is
                  when Start_Element =>
                     Count   : List_Count;
                     Names   : Token_Values (1 .. Embeded_Attr);
                     Values  : Token_Values (1 .. Embeded_Attr);

                  when Processing_Instruction =>
                     PI_Text : Token_Value;

                  when Attribute | Namespace =>
                     Value    : Token_Value;

                  when others =>
                     null;
               end case;

            when Comment
              | Characters
              | CDATA_Section
              =>
               Text : Token_Value;
         end case;
      end record;

      type Token_Sub_State is range 0 .. 12;

      type Tokenizer_State is record
         Kind  : Token;
         Value : Token_Value;
         Amp   : Token_Value;
         X     : Token_Sub_State;
         Prev  : Character_Class;
      end record;

      type Input_State is record
         Index    : Positive;
         Free     : Positive;
         Prev     : Positive;
         Encoding : Encodings.Encoding;
      end record;

      type Reader_State is new Ada.Finalization.Limited_Controlled with record
         Input        : Input_State;
         Token        : Tokenizer_State;
         In_State     : Internal_State;
         Deep         : Natural;
         Piece        : Piece_State;
         Extra_Names  : Token_Values_Access;
         Extra_Values : Token_Values_Access;
      end record;

      type Reader is abstract new Readers.Reader with record
         The : Reader_State;
      end record;

   end Implementation;

end XML_IO.Internals;
