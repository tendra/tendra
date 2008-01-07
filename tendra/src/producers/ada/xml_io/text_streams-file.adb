with Ada.Text_IO; use Ada.Text_IO;

package body Text_Streams.File is

   ----------
   -- Open --
   ----------

   procedure Open
     (Object : in out File_Text_Stream;
      Name   : in String;
      Form   : in String := "")
   is
   begin
      Open (Object.Input, In_File, Name, Form);
      Object.New_Line := False;
   end Open;

   ----------
   -- Read --
   ----------

   procedure Read
     (Object : in out File_Text_Stream;
      Text   :    out String;
      Last   :    out Natural)
   is
   begin
      Last := Text'First - 1;

      if not Is_Open (Object.Input) then
         return;
      elsif End_Of_File (Object.Input) then
         Close (Object.Input);
         return;
      end if;

      if Object.New_Line then
         Text (Last + 1) := ASCII.LF;
         Object.New_Line := False;
         Last := Last + 1;
      end if;

      while Last < Text'Last and not End_Of_File (Object.Input) loop
         Get_Line (Object.Input, Text (Last + 1 .. Text'Last), Last);

         if Last < Text'Last then
            Last := Last + 1;
            Text (Last) := ASCII.LF;
         elsif End_Of_Line (Object.Input) then
            Object.New_Line := True;
         end if;
      end loop;
   end Read;

end Text_Streams.File;

