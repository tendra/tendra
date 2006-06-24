with TenDRA.Types;
with Gela.Containers.Stacks;
with Ada.Sequential_IO;

package TenDRA.Streams is

   type Stream is abstract tagged limited private;
   type Stream_Access is access all Stream'Class;

   procedure Save
     (Object : in out Stream;
      Value  : in     Byte) is abstract;

   procedure Expect
     (Object : in out Stream;
      Parent : in     Types.Construct;
      List   : in     Types.Argument_List);

   procedure Check
     (Object : in out Stream;
      Item   : in     Types.Construct);

   procedure Check
     (Object : in out Stream;
      Sort   : in     Types.Sort_Kind;
      Item   : in     Types.Construct := Types.Dummy);

   procedure Write_No_Option
     (Object : in out Stream'Class);

   Unknown_Length : constant Small := Small'Last;

   procedure Write_List_Count
     (Object : in out Stream'Class;
      Value  : in     Small := Unknown_Length);

   procedure Write
     (Object : in out Stream'Class;
      Value  : in     Word;
      Length : in     Bit_Count);

   function Pos (Object : Stream) return String;

   function Aligned (Object : Stream) return Boolean;

   procedure Flush_Byte (Object : in out Stream'Class);

   type Memory_Stream is new Stream with private;

   procedure Reset
     (Object :    out Memory_Stream);

   procedure Save
     (Object : in out Memory_Stream;
      Value  : in     Byte);

   procedure Prepend
     (Object : in out Memory_Stream;
      Value  : in out Memory_Stream);

   procedure TDFBITSTREAM
     (Object : in out Stream'Class;
      Value  : in     Memory_Stream);

   procedure TDFBYTESTREAM
     (Object : in out Stream'Class;
      Value  : in out Memory_Stream);

   Syntax_Error : exception;

   type File_Stream is new Stream with private;

   procedure Save
     (Object : in out File_Stream;
      Value  : in     Byte);

   procedure Create
     (Object :    out File_Stream;
      Name   : in     String);

private

   type Check_Item is record
      Sort   : Types.Sort_Kind;
      Mode   : Types.Argument_Mode;
      Align  : Boolean;
      Count  : Small;
      Parent : Types.Construct;
   end record;

   package Stacks is new Gela.Containers.Stacks (Check_Item);

   function Next_Id return Positive;

   type Stream is abstract tagged limited record
      Id      : Positive               := Next_Id;
      Stack   : Stacks.Stack;
      Count   : Positive               := 1;
      Current : Byte                   := 0;
      Free    : Bit_Index range 1 .. 8 := 8;
   end record;

   type Buffer;
   type Buffer_Access is access all Buffer;

   type Memory_Stream is new Stream with record
      Length : Natural := 0;
      Next   : Buffer_Access;
   end record;

   package Byte_IO is new Ada.Sequential_IO (Byte);

   type File_Stream is new Stream with record
      File : Byte_IO.File_Type;
   end record;

end TenDRA.Streams;


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
