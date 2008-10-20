with Ada.Streams.Stream_IO;
with Ada.Unchecked_Conversion;
with Ada.Unchecked_Deallocation;

package body Gela.Source_Buffers.Portable is

   type Stream_Element_Access is access all Ada.Streams.Stream_Element;

   function Convert is new Ada.Unchecked_Conversion
     (Stream_Element_Access, Cursor);

   ----------
   -- Open --
   ----------

   procedure Open
     (Object    : in out Source_Buffer;
      File_Name : in     String)
   is
      use Ada.Streams;
      use Ada.Streams.Stream_IO;

      subtype IO_Count is Ada.Streams.Stream_IO.Count;

      Input     : File_Type;
      File_Size : IO_Count;
      Upper     : Stream_Element_Offset;
      Last      : Stream_Element_Offset;

      End_Of_File : constant Stream_Element :=
        Stream_Element'Val (Code_Unit'Pos (Source_Buffers.End_Of_File));
   begin
      Open (Input, In_File, File_Name);

      File_Size := Size (Input);

      --  Reserve a few bytes for End_Of_File marker.
      Upper := Stream_Element_Offset (File_Size + 2);

      Object.Internal_Array := new Stream_Element_Array (1 .. Upper);

      Read (Input, Object.Internal_Array.all, Last);

      Object.Internal_Array (Last + 1 .. Upper) := (others => End_Of_File);

      Close (Input);
   end Open;

   -----------
   -- Close --
   -----------

   procedure Close (Object : in out Source_Buffer) is
      procedure Deallocate is new Ada.Unchecked_Deallocation
        (Ada.Streams.Stream_Element_Array, Array_Access);
   begin
      Deallocate (Object.Internal_Array);
   end Close;

   ------------------
   -- Buffer_Start --
   ------------------

   function Buffer_Start (Object : Source_Buffer) return Cursor is
   begin
      return Convert (Object.Internal_Array (1)'Access);
   end Buffer_Start;

end Gela.Source_Buffers.Portable;

------------------------------------------------------------------------------
--  Copyright (c) 2008, Maxim Reznik
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
--
--  Authors:
--    Andry Ogorodnik
--    Maxim Reznik
--    Vadim Godunko
------------------------------------------------------------------------------
