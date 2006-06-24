with TenDRA.Types;
with TenDRA.Streams;

package TenDRA.Output is

   procedure TDFINT
     (Output : in out Streams.Stream'Class;
      Value  : in     Small;
      Last   : in     Boolean := True;
      Check  : in     Boolean := True;
      Align  : in     Boolean := False);

   procedure TDFBOOL
     (Output : in out Streams.Stream'Class;
      Value  : in     Boolean);

   procedure TDFSTRING
     (Output : in out Streams.Stream'Class;
      Value  : in     String);

   procedure TDFIDENT
     (Output : in out Streams.Stream'Class;
      Value  : in     String);

   procedure BITSTREAM
     (Output : in out Streams.Stream'Class;
      Value  : in     Streams.Memory_Stream);

   procedure BYTESTREAM
     (Output : in out Streams.Stream'Class;
      Value  : in out Streams.Memory_Stream);

   procedure BYTE_ALIGN
     (Output : in out Streams.Stream'Class)
     renames Streams.Flush_Byte;

   procedure Extendable_Int
     (Output : in out Streams.Stream'Class;
      Value  : in     Word;
      Length : in     Bit_Count);

   procedure Basic_Int
     (Output : in out Streams.Stream'Class;
      Value  : in     Word;
      Length : in     Bit_Count)
     renames Streams.Write;

   procedure No_Option
     (Object : in out Streams.Stream'Class)
     renames Streams.Write_No_Option;

   procedure List_Count
     (Object : in out Streams.Stream'Class;
      Value  : in     Small);

   procedure TDF
     (Output : in out Streams.Stream'Class;
      Value  : in     Types.Construct);

   procedure Set_Debug (Value : Boolean := True);

end TenDRA.Output;



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
