with Ada.Text_IO;
with Text_Streams.File;
with XML_IO.Stream_Readers;

procedure Test_XML_IO is
   use XML_IO;
   package R renames XML_IO.Stream_Readers;

   Stream : aliased Text_Streams.File.File_Text_Stream;
   Parser : R.Reader (Stream'Access, 32);-- R.Default_Buffer_Size);
begin
   Text_Streams.File.Open (Stream, "aaa.xml");
   R.Initialize (Parser);

   while R.More_Pieces (Parser) loop
      Ada.Text_IO.Put_Line
        ("Kind: " & Piece_Kinds'Image (R.Piece_Kind (Parser)));

      case R.Piece_Kind (Parser) is
         when Start_Document =>
            Ada.Text_IO.Put_Line
              (" Encoding: " & R.Encoding (Parser));
            Ada.Text_IO.Put_Line
              (" Standalone: " & Boolean'Image (R.Standalone (Parser)));

         when DTD | End_Document =>
            null;

         when Entity_Reference =>
            Ada.Text_IO.Put_Line
              (" Name: " & R.Name (Parser));

         when Start_Element =>
            Ada.Text_IO.Put_Line
              (" Name: " & R.Name (Parser));

            for I in 1 .. R.Attribute_Count (Parser) loop
               Ada.Text_IO.Put_Line
                 (" Attr : " & R.Attribute_Name (Parser, I)
                  & " = " & R.Attribute_Value (Parser, I));
            end loop;

         when End_Element =>
            Ada.Text_IO.Put_Line
              (" Name: " & R.Name (Parser));

         when Comment
           | Characters
           | CDATA_Section
           =>
            Ada.Text_IO.Put_Line
              (" Text: " & R.Text (Parser));

         when Processing_Instruction =>
            Ada.Text_IO.Put_Line
              (" Name: " & R.Name (Parser));
            Ada.Text_IO.Put_Line
              (" Text: " & R.Text (Parser));

         when Attribute | Namespace =>
            null;
      end case;

      R.Next (Parser);
   end loop;
end Test_XML_IO;
