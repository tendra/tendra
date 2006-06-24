with Interfaces;
with Ada.Text_IO;

package body TenDRA.Output is

   procedure TDFSTRING
     (Output : in out Streams.Stream'Class;
      Value  : in     String;
      Flush  : in     Boolean);

   procedure Debug
     (Output : in Streams.Stream'Class;
      Text   : in String);

   Do_Debug : Boolean := False;

   ---------------
   -- BITSTREAM --
   ---------------

   procedure BITSTREAM
     (Output : in out Streams.Stream'Class;
      Value  : in     Streams.Memory_Stream)
   is
   begin
      Debug (Output, "BITSTREAM " & Streams.Pos (Value));
      Streams.TDFBITSTREAM (Output, Value);
   end BITSTREAM;

   ----------------
   -- BYTESTREAM --
   ----------------

   procedure BYTESTREAM
     (Output : in out Streams.Stream'Class;
      Value  : in out Streams.Memory_Stream)
   is
   begin
      Debug (Output, "BYTESTREAM " & Streams.Pos (Value));
      Streams.TDFBYTESTREAM (Output, Value);
   end BYTESTREAM;

   -----------
   -- Debug --
   -----------

   procedure Debug
     (Output : in Streams.Stream'Class;
      Text   : in String)
   is
   begin
      if Do_Debug then
         Ada.Text_IO.Put_Line (Streams.Pos (Output) & " " & Text);
      end if;
   end Debug;

   --------------------
   -- Extendable_Int --
   --------------------

   procedure Extendable_Int
     (Output : in out Streams.Stream'Class;
      Value  : in     Word;
      Length : in     Bit_Count)
   is
      Limit : constant Word := 2 ** Natural (Length) - 1;
   begin
      if Value = 0 then
         raise Constraint_Error;
      elsif Value <= Limit then
         Streams.Write (Output, Value, Length);
      else
         Streams.Write (Output, 0, Length);
         Extendable_Int (Output, Value - Limit, Length);
      end if;
   end Extendable_Int;

   ----------------
   -- List_Count --
   ----------------

   procedure List_Count
     (Object : in out Streams.Stream'Class;
      Value  : in     Small)
   is
   begin
      Debug (Object, "List" & Small'Image (Value));
      Streams.Write_List_Count (Object, Value);
   end List_Count;

   ---------------
   -- Set_Debug --
   ---------------

   procedure Set_Debug (Value : Boolean := True) is
   begin
      Do_Debug := Value;
   end Set_Debug;

   ---------
   -- TDF --
   ---------

   procedure TDF
     (Output : in out Streams.Stream'Class;
      Value  : in     Types.Construct)
   is
      Sort   : Types.Sort_Kind     := Types.Result (Value);
      Code   : Word                := Types.Code (Value);
      Bits   : Bit_Count           := Types.Bits (Sort);
      List   : Types.Argument_List := Types.Arguments (Value);
   begin
      Debug (Output, Types.Construct'Image (Value));
      Streams.Check (Output, Value);

      if Types.Extended (Sort) then
         Extendable_Int (Output, Code, Bits);
      else
         Basic_Int (Output, Code, Bits);
      end if;

      Streams.Expect (Output, Value, List);
   end TDF;

   -------------
   -- TDFBOOL --
   -------------

   procedure TDFBOOL
     (Output : in out Streams.Stream'Class;
      Value  : in     Boolean)
   is
      Map : constant array (Boolean) of Word := (False => 0, True => 1);
   begin
      Debug (Output, "TDFBOOL " & Boolean'Image (Value));
      Streams.Check (Output, Types.TDFBOOL_SORT);
      Basic_Int (Output, Map (Value), 1);
   end TDFBOOL;

   --------------
   -- TDFIDENT --
   --------------

   procedure TDFIDENT
     (Output : in out Streams.Stream'Class;
      Value  : in     String)
   is
   begin
      Debug (Output, "TDFIDENT " & Value);
      Streams.Check (Output, Types.TDFIDENT_SORT);
      TDFSTRING (Output, Value, True);
   end TDFIDENT;

   ------------
   -- TDFINT --
   ------------

   procedure TDFINT
     (Output : in out Streams.Stream'Class;
      Value  : in     Small;
      Last   : in     Boolean := True;
      Check  : in     Boolean := True;
      Align  : in     Boolean := False)
   is
      use TenDRA.Streams;

      function Top (Current  : Word) return Word is
         use Interfaces;
      begin
         return Word (Shift_Right (Unsigned_32 (Current), 29));
      end Top;

      procedure Fix_Count (Count : in out Bit_Count; Current : in out Word) is
         use Interfaces;
         Temp : Unsigned_32 := Unsigned_32 (Value);
      begin
         if Temp = 0 then
            Count := 4;
         else
            Count := 0;

            while Temp /= 0 loop
               Temp := Shift_Right (Temp, 3);
               Count := Count + 4;
            end loop;
         end if;

         if Aligned (Output) xor (Count mod 8 = 0) then
            Count := Count + 4;
         end if;

         Count := 3 * Count / 4;  --  Output bits to Value bits
         Current := Word (Shift_Left (Unsigned_32 (Value),
                                      Integer (32 - Count)));
      end Fix_Count;

      Starting : Boolean   := True;
      Count    : Bit_Count := 30;
      Current  : Word      := Word (Value) * 4;
      Next     : Word;
   begin
      if Check and Last then
         Debug (Output, "TDFINT " & Small'Image (Value));
         Streams.Check (Output, Types.TDFINT_SORT);
      end if;

      if Align then
         Fix_Count (Count, Current);
      end if;

      while Count > 0 loop
         Next    := Top (Current);
         Current := Current * 8;
         Count   := Count - 3;

         if Last and then Count = 0 then
            Write (Output, 8 or Next, 4);
         elsif not Starting or Next /= 0 or Align then
            Write (Output, Next, 4);
            Starting := False;
         end if;
      end loop;
   end TDFINT;

   ---------------
   -- TDFSTRING --
   ---------------

   procedure TDFSTRING
     (Output : in out Streams.Stream'Class;
      Value  : in     String;
      Flush  : in     Boolean)
   is
   begin
      TDFINT (Output, 8, Check => False);
      TDFINT (Output, Value'Length, Check => False);

      if Flush then
         Streams.Flush_Byte (Output);
      end if;

      for I in Value'Range loop
         Streams.Write (Output, Character'Pos (Value (I)), 8);
      end loop;

      if Flush then
         Streams.Flush_Byte (Output);
      end if;
   end TDFSTRING;

   ---------------
   -- TDFSTRING --
   ---------------

   procedure TDFSTRING
     (Output : in out Streams.Stream'Class;
      Value  : in     String)
   is
   begin
      Debug (Output, "TDFSTRING " & Value);
      Streams.Check (Output, Types.TDFSTRING_SORT);
      TDFSTRING (Output, Value, False);
   end TDFSTRING;

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
