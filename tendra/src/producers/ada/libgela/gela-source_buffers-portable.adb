with Ada.Streams.Stream_IO;
with Ada.Unchecked_Deallocation;

package body Gela.Source_Buffers.Portable is

   ----------
   -- Open --
   ----------

   procedure Open
     (This : in out Source_Buffer;
      Name : in     String)
   is
      use Ada.Streams;
      use Ada.Streams.Stream_IO;

      subtype IO_Count is Ada.Streams.Stream_IO.Count;

      Input     : File_Type;
      File_Size : IO_Count;
      Upper     : Stream_Element_Offset;
      Last      : Stream_Element_Offset;
   begin
      Open (Input, In_File, Name);

      File_Size := Size (Input);

      if File_Size > IO_Count (Offset'Last) then
         Close (Input);
         raise Use_Error;
      else
         This.Internal_Size := Offset (File_Size);
      end if;

      if This.Internal_Size = 0 then
         return;
      end if;

      Upper := Stream_Element_Offset (File_Size);

      This.Internal_Array := new Stream_Element_Array (1 .. Upper);

      Read (Input, This.Internal_Array.all, Last);

      This.Internal_Array (Last + 1 .. Upper) := (others => 0);

      This.Internal_Data := This.Internal_Array (1)'Address;

      Close (Input);
   end Open;

   -----------
   -- Close --
   -----------

   procedure Close (This : in out Source_Buffer) is
      procedure Deallocate is new Ada.Unchecked_Deallocation
        (Ada.Streams.Stream_Element_Array, Array_Access);
   begin
      Deallocate (This.Internal_Array);
      This.Internal_Data := System.Null_Address;
   end Close;

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
