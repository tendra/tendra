with Gela.Containers.Lists;

with Text_Streams.File;
with XML_IO.Stream_Readers;

with Ada.Strings.Unbounded;    use Ada.Strings.Unbounded;

package body Tokens is

   package Unbounded_String_Lists is
      new Gela.Containers.Lists (Unbounded_String, "=");

   type Delimiter is record
      Name : Unbounded_String;
      Text : Unbounded_String;
   end record;

   function "=" (Left, Right : Delimiter) return Boolean;

   package Delimiter_Lists is new Gela.Containers.Lists (Delimiter, "=");

   All_Delimiters : Delimiter_Lists.List;
   All_Tokens     : Unbounded_String_Lists.List;
   All_Keywords   : Unbounded_String_Lists.List;

   function "=" (Left, Right : Delimiter) return Boolean is
   begin
      return Left.Text = Right.Text;
   end "=";

   --------------------
   -- Delimiter_Name --
   --------------------

   function Delimiter_Name (Text : String) return String is
      use Delimiter_Lists;
      To_Find : constant Delimiter :=
         (Name => Null_Unbounded_String,
          Text => To_Unbounded_String (Text));
      Found   : constant Cursor := Find (All_Delimiters, To_Find);
   begin
      if Has_Element (Found) then
         return To_String (Element (Found).Name);
      else
         return "";
      end if;
   end Delimiter_Name;

   --------------
   -- Is_Token --
   --------------

   function Is_Token (Name : String) return Boolean is
      use Unbounded_String_Lists;
      To_Find : constant Unbounded_String := To_Unbounded_String (Name);
   begin
      return Contains (All_Tokens, To_Find);
   end Is_Token;

   ---------------
   -- Read_File --
   ---------------

   procedure Read_File (Name : String) is
      use XML_IO;
      package R renames XML_IO.Stream_Readers;

      Stream  : aliased Text_Streams.File.File_Text_Stream;
      Parser  : R.Reader (Stream'Access, R.Default_Buffer_Size);

      function Get_Attribute (Name : String) return Unbounded_String is
      begin
         return To_Unbounded_String (R.Attribute_Value (Parser, Name));
      end Get_Attribute;

      procedure On_Element is
         use Unbounded_String_Lists;

         Local_Name : constant String := R.Name (Parser);
      begin
         if Local_Name = "token" then
            if Get_Attribute ("type") = "yes" then
               Append (All_Tokens, Get_Attribute ("name"));
            end if;
         elsif Local_Name = "keyword" then
            Append (All_Keywords, Get_Attribute ("name"));
         elsif Local_Name = "delimiter" then
            declare
               use Delimiter_Lists;
               Delim : constant Delimiter :=
                  (Name => Get_Attribute ("name"),
                   Text => Get_Attribute ("text"));
            begin
               Append (All_Delimiters, Delim);
            end;
         end if;
      end On_Element;
   begin
      Text_Streams.File.Open (Stream, Name);
      R.Initialize (Parser);

      while R.More_Pieces (Parser) loop
         case R.Piece_Kind (Parser) is
            when Start_Element =>
               On_Element;
            when others =>
               null;
         end case;

         R.Next (Parser);
      end loop;
   end Read_File;

   -------------------
   -- For_Each_Name --
   -------------------

   procedure For_Each_Name is
      use Unbounded_String_Lists;
      C : Cursor;
      D : Delimiter_Lists.Cursor;
   begin
      C := First (All_Tokens);

      while Has_Element (C) loop
         Action (To_String (Element (C)));
         C := Next (C);
      end loop;

      D := Delimiter_Lists.First (All_Delimiters);

      while Delimiter_Lists.Has_Element (D) loop
         Action (To_String (Delimiter_Lists.Element (D).Name));
         D := Delimiter_Lists.Next (D);
      end loop;

      C := First (All_Keywords);

      while Has_Element (C) loop
         Action (To_String (Element (C)));
         C := Next (C);
      end loop;
   end For_Each_Name;

   ------------------
   -- Token_Length --
   ------------------

   function Token_Length    (Name : String) return Natural is
      use Delimiter_Lists;
      C : Cursor;
   begin
      C := First (All_Delimiters);

      while Has_Element (C) loop
         declare
            X : constant Delimiter := Element (C);
         begin
            if X.Name = Name then
               return Length (X.Text);
            end if;
         end;

         C := Next (C);
      end loop;

      if Unbounded_String_Lists.Contains
        (All_Tokens, To_Unbounded_String (Name))
      then
         return 0;
      end if;

      return Name'Length;
   end Token_Length;

end Tokens;



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
