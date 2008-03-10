------------------------------------------------------------------------------
--                         G E L A   H A S H                                --
--                 Repository implementation for Gela                       --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  Purpose:

--  Name  : CRC-32 [Ethernet, PKZip, AUTODIN II, FDDI]
--  Width : 32
--  Poly  : 0x04C11DB7 x^32 + x^26 + x^22 + x^16 + x^12 + x^11
--                      + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x^1 + 1
--  Init  : 0xFFFFFFFF
--  RefIn : True
--  RefOut: True
--  XorOut: 0xFFFFFFFF
--  Check : 0xCBF43926 ("123456789")
--  MaxLen: 4095 byte (32767 bit)

with Ada.Streams;
with Interfaces;

package Gela.Hash.CRC.b32 is

   type CRC32 is new Interfaces.Unsigned_32;

   type Hasher is private;

   Initial_Hasher : constant Hasher;

   procedure Update
     (This  : in out Hasher;
      Value : in     String);

   procedure Wide_Update
     (This  : in out Hasher;
      Value : in     Wide_String);

   procedure Wide_Wide_Update
     (This  : in out Hasher;
      Value : in     Wide_Wide_String);

   procedure Update
     (This  : in out Hasher;
      Value : in     Ada.Streams.Stream_Element_Array);

   function Result
     (This : in Hasher)
      return CRC32;

   function Calculate
     (Value : in String)
      return CRC32;

   function Wide_Calculate
     (Value : in Wide_String)
      return CRC32;

   function Wide_Wide_Calculate
     (Value : in Wide_Wide_String)
      return CRC32;

   function Calculate
     (Value : in Ada.Streams.Stream_Element_Array)
      return CRC32;

   function To_Hash
     (T : in CRC32)
      return Hash_Type;
   pragma Inline (To_Hash);

   function Calculate
     (Value : in String)
      return Hash_Type;
   pragma Inline (Calculate);

   function Wide_Calculate
     (Value : in Wide_String)
      return Hash_Type;
   pragma Inline (Calculate);

   function Wide_Wide_Calculate
     (Value : in Wide_Wide_String)
      return Hash_Type;
   pragma Inline (Calculate);

   function Calculate
     (Value : in Ada.Streams.Stream_Element_Array)
      return Hash_Type;
   pragma Inline (Calculate);

private

   type Hasher is record
      Length : Integer   := 0;
      Cm_Reg : CRC32 := 16#FFFFFFFF#;
   end record;

   Initial_Hasher : constant Hasher :=
     (Length => 0, Cm_Reg => 16#FFFFFFFF#);

end Gela.Hash.CRC.b32;

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
