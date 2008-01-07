with Nodes.Database;
with Gela.Containers.Stacks;

with Text_Streams.File;
with XML_IO.Stream_Readers;

with Ada.Strings.Unbounded;    use Ada.Strings.Unbounded;

package body Nodes.Read is

   package Stacks is new Gela.Containers.Stacks (Unbounded_String);
   Stack : Stacks.Stack;

   ---------------
   -- Read_File --
   ---------------

   procedure Read_File (File_Name : String) is
      use XML_IO;
      package R renames XML_IO.Stream_Readers;

      Stream  : aliased Text_Streams.File.File_Text_Stream;
      Parser  : R.Reader (Stream'Access, R.Default_Buffer_Size);

      procedure On_Element is
         function Get_Attribute (Name : String) return String;
         function Get_Type return String;

         function Get_Attribute (Name : String) return String is
         begin
            return R.Attribute_Value (Parser, Name);
         end Get_Attribute;


         function Get_Type return String is
            Tipe : constant String := Get_Attribute ("type");
         begin
            if Tipe'Length > 5
              and then Tipe (Tipe'First .. Tipe'First + 4) = "Asis."
            then
               return Tipe (Tipe'First + 5 .. Tipe'Last);
            else
               return Tipe;
            end if;
         end Get_Type;

         Local_Name    : String := R.Name (Parser);
      begin
         if Local_Name = "node" then
            declare
               Name   : constant String := Get_Attribute ("name");
            begin
               if Stacks.Is_Empty (Stack) then
                  Database.Create_Node (Name, "");
               else
                  Database.Create_Node
                    (Name, To_String (Stacks.Top (Stack)));
               end if;

               Stacks.Push (Stack, To_Unbounded_String (Name));
            end;
         elsif Local_Name = "attr" then
            Database.Create_Attribute (Get_Attribute ("name"), Get_Type);
         end if;
      end On_Element;

   begin  --  Read_File
      Text_Streams.File.Open (Stream, File_Name);
      R.Initialize (Parser);

      while R.More_Pieces (Parser) loop
         case R.Piece_Kind (Parser) is
            when Start_Element =>
               On_Element;
            when End_Element =>
               if R.Name (Parser) = "node" then
                  Stacks.Pop (Stack);
               end if;
            when others =>
               null;
         end case;

         R.Next (Parser);
      end loop;
   end Read_File;

end Nodes.Read;


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
