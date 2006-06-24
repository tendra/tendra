with Tokens;
with Generate;
with Gramar_Items;
with Nodes.Read;
with Nodes.Database;
with Gramar_Items.Code;
with Ada.Command_Line;
with Ada.Text_IO;

procedure Xml_To_Y is
   package C renames Ada.Command_Line;
begin
   if C.Argument_Count /= 4 then
      Ada.Text_IO.Put_Line
        ("Usage : xml_to_y xml_hier.xml tokens.xml fixed.xml code.xml");
   else
      Nodes.Read.Read_File (C.Argument (1));
      Tokens.Read_File (C.Argument (2));
      Gramar_Items.Read_File (C.Argument (3));
      Gramar_Items.Code.Read_Code_File (C.Argument (4));
      Generate.All_Tokens;
      Generate.Start_Rule;
      Generate.Token_Rules;
      Generate.All_Rules;
      Generate.Options_And_Lists;

      declare
         use Ada.Text_IO;
         use Nodes.Database;
         Output : File_Type;
      begin
         Create (Output, Name => "output.txt");
         for I in 1 .. Last_Node loop
            Put_Line (Output, Node_Name (I) & ":");
            for J in 1 .. Last_Attribute (I) loop
               Put_Line (Output, "   " & Attribute_Name (I, J) &
                                 " : " & Attribute_Type (I, J) & ";");
            end loop;
         end loop;
      end;
   end if;
end Xml_To_Y;


------------------------------------------------------------------------------
--  Copyright (c) 2006, Maxim Reznik
--  All rights reserved.
--
--  Redistribution and use in source and binary forms, with or without
--  modification, are permitted provided that the following conditions are met:
--
--     * Redistributions of source code must retain the above copyright notice,
--     * this list of conditions and the following disclaimer.
--     * Redistributions in binary form must reproduce the above copyright
--     * notice, this list of conditions and the following disclaimer in the
--     * documentation and/or other materials provided with the distribution.
--
--  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
--  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
--  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
--  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
--  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
--  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
--  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
--  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
--  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
--  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
--  POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------
