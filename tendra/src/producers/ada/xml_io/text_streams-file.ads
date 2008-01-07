with Ada.Text_IO;

package Text_Streams.File is

   ----------------------
   -- File_Text_Stream --
   ----------------------

   type File_Text_Stream is new Text_Stream with private;

   procedure Open
     (Object : in out File_Text_Stream;
      Name   : in String;
      Form   : in String := "");

   procedure Read
     (Object : in out File_Text_Stream;
      Text   :    out String;
      Last   :    out Natural);

private

   type File_Text_Stream is new Text_Stream with record
      Input    : Ada.Text_IO.File_Type;
      New_Line : Boolean;
   end record;

end Text_Streams.File;


