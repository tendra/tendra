with Ada.Text_IO;
with Ada.Command_Line;
with Encodings.Read.Write;
with Encodings.Maps.Runtime;

procedure Encodings.Converter is
   use Ada.Command_Line;
   Map : Encoding;
begin
   if Argument_Count /= 1 then
      Ada.Text_IO.Put_Line
        ("Usage encodings-converter <encoding-name>");
   else
      Map := Encoding'Value (Argument (1));
      declare
         Name  : constant String := Maps.Runtime.File (Map);
         Table : Encodings.Read.Mapping :=
           Encodings.Read.Table (Name);
      begin
         Encodings.Read.Write (Table, Map);
      end;
   end if;
end Encodings.Converter;
