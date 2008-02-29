------------------------------------------------------------------------------
--                         G E L A   H A S H                                --
--                 Repository implementation for Gela                       --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  Purpose:

--  Name  : CRC-16 [CCITT]
--  Width : 16
--  Poly  : 0x1021 x^16 + x^12 + x^5 + 1
--  Init  : 0xFFFF
--  RefIn : False
--  RefOut: False
--  XorOut: 0x0000
--  Check : 0x29B1 ("123456789")
--  MaxLen: 4095 byte (32767 bit)

with Ada.Streams;

package Gela.Hash.CRC_16 is

   type CRC_Type is mod 2 ** 16;

   type Hasher is private;

   Initial_Hasher : constant Hasher;

   Max_Len        : constant := 4095;

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
      return CRC_Type;

   function Calculate
     (Value : in String)
      return CRC_Type;

   function Wide_Calculate
     (Value : in Wide_String)
      return CRC_Type;

   function Wide_Wide_Calculate
     (Value : in Wide_Wide_String)
      return CRC_Type;

   function Calculate
     (Value : in Ada.Streams.Stream_Element_Array)
      return CRC_Type;

   function To_Hash
     (T : in CRC_Type)
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

   Max_Len_Error : exception;

private

   type Hasher is record
      Length : Integer  := 0;
      Cm_Reg : CRC_Type := 16#FFFF#;
   end record;

   Initial_Hasher : constant Hasher :=
     (Length => 0, Cm_Reg => 16#FFFF#);

end Gela.Hash.CRC_16;

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
