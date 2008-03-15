
with Ada.Unchecked_Conversion;
with Ada.Streams.Stream_IO;

with Gela.Hash.SHA.b512;

package body Gela.Repository.Dictionary.File is

   Signature : constant String := "Gela_Repository_Dictionary$";
   Version   : constant String := "v1.0";
   Extension : constant String := ".grd";

   use Ada.Streams.Stream_IO;

   Signature_Size : constant Ada.Streams.Stream_IO.Count :=
     Signature'Size / Ada.Streams.Stream_Element'Size
       + Version'Size / Ada.Streams.Stream_Element'Size;

   Minimum_Size : constant Ada.Streams.Stream_IO.Count :=
     Signature_Size
     + Gela.Hash.SHA.b512.SHA512'Size / Ada.Streams.Stream_Element'Size
     + Integer'Size / Ada.Streams.Stream_Element'Size;

   Divisor : constant :=
     Wide_Wide_Character'Size / Ada.Streams.Stream_Element'Size;

   ----------------
   -- Initialize --
   ----------------

   procedure Initialize
     (This : in out Gela_Dictionary_File)
   is
      File : File_Type;
      File_Stream : Stream_Access;
      Last        : Ada.Streams.Stream_Element_Offset;

      -- Read_Element --
      procedure Read_Element
      is
         use Ada.Streams;

         Element     : ID_Point;
         String_Size : Integer;
      begin
         ID'Read (File_Stream, Element.Num);
         Integer'Read (File_Stream, String_Size);

         declare
            subtype Constrained_Wide_Wide_String is
              Wide_Wide_String (1 .. String_Size);

            function To_Wide_Wide_String is new
              Ada.Unchecked_Conversion
                (Stream_Element_Array, Constrained_Wide_Wide_String);

            String_Data : Stream_Element_Array
              (1 .. Stream_Element_Offset (String_Size * Divisor));
         begin
            Read (File, String_Data, Last);
            Element.Data := new Wide_Wide_String'
              (To_Wide_Wide_String (String_Data));
         end;

         Insert (This, Count (This) + 1, Element);
      end Read_Element;
   begin
      try :
      begin
         Open (File, In_File, "dictionary" & Extension);
      exception
         when others =>
            return;
      end try;

      if not Is_Open (File)
        or else Size (File) < Minimum_Size
      then
         Close (File);
         return;
      end if;

      File_Stream := Stream (File);

      declare
         File_Signature : String (1 .. Signature'Length);
      begin
         String'Read (File_Stream, File_Signature);

         if File_Signature /= Signature then
            Close (File);
            return;
         end if;
      end;

      declare
         File_Version : String (1 .. Version'Length);
      begin
         String'Read (File_Stream, File_Version);

         if File_Version /= Version then
            Close (File);
            return;
         end if;
      end;

      declare
         use Gela.Hash.SHA.b512;
         use Ada.Streams;

         Store_SHA, File_SHA : SHA512;
         File_Hasher : Hasher_512;

         Data_Array : Ada.Streams.Stream_Element_Array (1 .. 128);
      begin
         SHA512'Read (File_Stream, Store_SHA);

         loop
            Read (File_Stream.all, Data_Array, Last);
            if Last = Data_Array'Last then
               Update (File_Hasher, Data_Array);
            else
               Update (File_Hasher, Data_Array (1 .. Last));
               exit;
            end if;
         end loop;

         Result (File_Hasher, File_SHA);

         if File_SHA /= File_SHA then
            Close (File);
            return;
         end if;
      end;

      Set_Index (File, Signature_Size + 1
                 + Gela.Hash.SHA.b512.SHA512'Size /
                   Ada.Streams.Stream_Element'Size);

      declare
         Count : Integer;
      begin
         Integer'Read (File_Stream, Count);

         for Index in 1 .. Count loop
            Read_Element;
         end loop;
      end;

      Close (File);

   exception
      when others =>
         Close (File);
         raise;
   end Initialize;

   ----------
   -- Save --
   ----------

   procedure Save
     (This : in out Gela_Dictionary_File)
   is
      use Ada.Streams;

      File : File_Type;
      File_Stream : Stream_Access;

      subtype Integer_Stream_Element_Array is
        Stream_Element_Array
          (1 .. Integer'Size / Stream_Element'Size);

      function To_Stream_Element_Array is new
        Ada.Unchecked_Conversion
          (Integer, Integer_Stream_Element_Array);

      subtype ID_Stream_Element_Array is
        Stream_Element_Array
          (1 .. ID'Size / Stream_Element'Size);

      function To_Stream_Element_Array is new
        Ada.Unchecked_Conversion
          (ID, ID_Stream_Element_Array);

      -- Element_Data --
      function Element_Data
        (Index : in Positive)
         return Ada.Streams.Stream_Element_Array
      is
         String_Size : constant Integer :=
           This.Data (Index).Data'Length;

         subtype Constrained_Stream_Element_Array is
           Stream_Element_Array
             (1 .. Stream_Element_Offset (String_Size * Divisor));

         function To_Stream_Element_Array is new
           Ada.Unchecked_Conversion
             (Wide_Wide_String, Constrained_Stream_Element_Array);

      begin
         return To_Stream_Element_Array (This.Data (Index).Num)
           & To_Stream_Element_Array (String_Size)
           & To_Stream_Element_Array (This.Data (Index).Data.all);
      end Element_Data;

   begin
      try :
      begin
         Open (File, Out_File, "dictionary.grp");
      exception
         when others =>
            Create (File, Out_File, "dictionary" & Extension);
      end try;

      if not Is_Open (File) then
         raise Use_Error;
      end if;

      File_Stream := Stream (File);
      String'Write (File_Stream, Signature);
      String'Write (File_Stream, Version);

      declare
         use Gela.Hash.SHA.b512;

         File_SHA : SHA512;
         File_Hasher : Hasher_512;
      begin
         Update (File_Hasher, To_Stream_Element_Array (Count (This)));

         for Index in 1 .. Count (This) loop
            Update (File_Hasher, Element_Data (Index));
         end loop;

         Result (File_Hasher, File_SHA);

         SHA512'Write (File_Stream, File_SHA);
      end;

      Write (File, To_Stream_Element_Array (Count (This)));

      for Index in 1 .. Count (This) loop
         Write (File, Element_Data (Index));
      end loop;

      Close (File);
   end Save;

end Gela.Repository.Dictionary.File;

------------------------------------------------------------------------------
--  Copyright (c) 2006, Andry Ogorodnik
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
