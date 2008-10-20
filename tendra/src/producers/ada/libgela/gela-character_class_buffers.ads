------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Buffers from this package holds class for each character from source
--  buffer. Special character class (End_Of_Buffer) signals buffer is
--  empty.

package Gela.Character_Class_Buffers is

   type Character_Class is mod 256;
   for Character_Class'Size use 8;

   End_Of_Buffer : constant Character_Class;

   type Character_Class_Buffer is limited private;

   procedure Put
     (Object : in out Character_Class_Buffer;
      Item   : in     Character_Class;
      Full   :    out Boolean);

   procedure Get
     (Object : in out Character_Class_Buffer;
      Item   :    out Character_Class);

   procedure Mark         (Object : in out Character_Class_Buffer);
   procedure Back_To_Mark (Object : in out Character_Class_Buffer);

private

   type Array_Index is mod 4096;

   type Character_Class_Array is array (Array_Index) of Character_Class;

   type Character_Class_Buffer is record
      --  Index points to last read character
      Index : Array_Index := Array_Index'Last - 1;
      --  Free points to where next Put will place an item
      Free  : Array_Index := 0;
      Mark  : Array_Index := 0;
      Data  : Character_Class_Array := (others => End_Of_Buffer);
   end record;

   End_Of_Buffer : constant Character_Class := 0;

   pragma Inline (Put);
   pragma Inline (Get);
   pragma Inline (Mark);
   pragma Inline (Back_To_Mark);
end Gela.Character_Class_Buffers;

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
------------------------------------------------------------------------------
