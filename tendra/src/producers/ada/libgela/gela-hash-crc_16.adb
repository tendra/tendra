
with Ada.Unchecked_Conversion;

package body Gela.Hash.CRC_16 is

   type Index_Type  is mod 2 ** 8;

   Keys : constant array (0 .. 255)
   of CRC_Type :=
     (0,     4129,  8258,  12387, 16516, 20645, 24774, 28903,
      33032, 37161, 41290, 45419, 49548, 53677, 57806, 61935,
      4657,  528,   12915, 8786,  21173, 17044, 29431, 25302,
      37689, 33560, 45947, 41818, 54205, 50076, 62463, 58334,
      9314,  13379, 1056,  5121,  25830, 29895, 17572, 21637,
      42346, 46411, 34088, 38153, 58862, 62927, 50604, 54669,
      13907, 9842,  5649,  1584,  30423, 26358, 22165, 18100,
      46939, 42874, 38681, 34616, 63455, 59390, 55197, 51132,
      18628, 22757, 26758, 30887, 2112,  6241,  10242, 14371,
      51660, 55789, 59790, 63919, 35144, 39273, 43274, 47403,
      23285, 19156, 31415, 27286, 6769,  2640,  14899, 10770,
      56317, 52188, 64447, 60318, 39801, 35672, 47931, 43802,
      27814, 31879, 19684, 23749, 11298, 15363, 3168,  7233,
      60846, 64911, 52716, 56781, 44330, 48395, 36200, 40265,
      32407, 28342, 24277, 20212, 15891, 11826, 7761,  3696,
      65439, 61374, 57309, 53244, 48923, 44858, 40793, 36728,
      37256, 33193, 45514, 41451, 53516, 49453, 61774, 57711,
      4224,  161,   12482, 8419,  20484, 16421, 28742, 24679,
      33721, 37784, 41979, 46042, 49981, 54044, 58239, 62302,
      689,   4752,  8947,  13010, 16949, 21012, 25207, 29270,
      46570, 42443, 38312, 34185, 62830, 58703, 54572, 50445,
      13538, 9411,  5280,  1153,  29798, 25671, 21540, 17413,
      42971, 47098, 34713, 38840, 59231, 63358, 50973, 55100,
      9939,  14066, 1681,  5808,  26199, 30326, 17941, 22068,
      55628, 51565, 63758, 59695, 39368, 35305, 47498, 43435,
      22596, 18533, 30726, 26663, 6336,  2273,  14466, 10403,
      52093, 56156, 60223, 64286, 35833, 39896, 43963, 48026,
      19061, 23124, 27191, 31254, 2801,  6864,  10931, 14994,
      64814, 60687, 56684, 52557, 48554, 44427, 40424, 36297,
      31782, 27655, 23652, 19525, 15522, 11395, 7392,  3265,
      61215, 65342, 53085, 57212, 44955, 49082, 36825, 40952,
      28183, 32310, 20053, 24180, 11923, 16050, 3793,  7920);

   type Bit  is  (Off, On);
   for  Bit  use (Off => 0, On => 1);
   for  Bit'Size  use 1;

   type Byte is record
      b7 : Bit;
      b6 : Bit;
      b5 : Bit;
      b4 : Bit;
      b3 : Bit;
      b2 : Bit;
      b1 : Bit;
      b0 : Bit;
   end record;

   for Byte use record
      b7 at 0 range 7 .. 7;
      b6 at 0 range 6 .. 6;
      b5 at 0 range 5 .. 5;
      b4 at 0 range 4 .. 4;
      b3 at 0 range 3 .. 3;
      b2 at 0 range 2 .. 2;
      b1 at 0 range 1 .. 1;
      b0 at 0 range 0 .. 0;
   end record;

   type Byte_Array is array (Natural range <>) of Byte;

   procedure Update
     (This  : in out Hasher;
      Value : in     Byte_Array);

   ------------
   -- Update --
   ------------

   procedure Update
     (This  : in out Hasher;
      Value : in     String)
   is
      subtype C_Array is
        Byte_Array (1 .. Value'Size / Byte'Size);

      function To_Array is
        new Ada.Unchecked_Conversion (String, C_Array);
   begin
      Update (This, To_Array (Value));
   end Update;

   -----------------
   -- Wide_Update --
   -----------------

   procedure Wide_Update
     (This  : in out Hasher;
      Value : in     Wide_String)
   is
      subtype C_Array is
        Byte_Array (1 .. Value'Size / Byte'Size);

      function To_Array is
        new Ada.Unchecked_Conversion (Wide_String, C_Array);
   begin
      Update (This, To_Array (Value));
   end Wide_Update;

   ----------------------
   -- Wide_Wide_Update --
   ----------------------

   procedure Wide_Wide_Update
     (This  : in out Hasher;
      Value : in     Wide_Wide_String)
   is
      subtype C_Array is
        Byte_Array (1 .. Value'Size / Byte'Size);

      function To_Array is
        new Ada.Unchecked_Conversion (Wide_Wide_String, C_Array);
   begin
      Update (This, To_Array (Value));
   end Wide_Wide_Update;

   ------------
   -- Update --
   ------------

   procedure Update
     (This  : in out Hasher;
      Value : in     Ada.Streams.Stream_Element_Array)
   is
      subtype C_Array is
        Byte_Array (1 .. Value'Size / Byte'Size);

      function To_Array is
        new Ada.Unchecked_Conversion
          (Ada.Streams.Stream_Element_Array, C_Array);
   begin
      Update (This, To_Array (Value));
   end Update;

   ------------
   -- Result --
   ------------

   function Result
     (This : in Hasher)
      return CRC_Type
   is
   begin
      return This.Cm_Reg;
   end Result;

   -- Calculate --
   function Calculate
     (Value : in String)
      return CRC_Type
   is
      H : Hasher;
   begin
      Update (H, Value);
      return Result (H);
   end Calculate;

   -- Wide_Calculate --
   function Wide_Calculate
     (Value : in Wide_String)
      return CRC_Type
   is
      H : Hasher;
   begin
      Wide_Update (H, Value);
      return Result (H);
   end Wide_Calculate;

   -- Wide_Wide_Calculate --
   function Wide_Wide_Calculate
     (Value : in Wide_Wide_String)
      return CRC_Type
   is
      H : Hasher;
   begin
      Wide_Wide_Update (H, Value);
      return Result (H);
   end Wide_Wide_Calculate;

   -- Calculate --
   function Calculate
     (Value : in Ada.Streams.Stream_Element_Array)
      return CRC_Type
   is
      H : Hasher;
   begin
      Update (H, Value);
      return Result (H);
   end Calculate;

   -- To_Hash --
   function To_Hash
     (T : in CRC_Type)
      return Hash_Type
   is
   begin
      return Hash_Type (T);
   end To_Hash;

   -- Calculate --
   function Calculate
     (Value : in String)
      return Hash_Type
   is
   begin
      return To_Hash (Calculate (Value));
   end Calculate;

   -- Wide_Calculate --
   function Wide_Calculate
     (Value : in Wide_String)
      return Hash_Type
   is
   begin
      return To_Hash (Wide_Calculate (Value));
   end Wide_Calculate;

   -- Calculate --
   function Wide_Wide_Calculate
     (Value : in Wide_Wide_String)
      return Hash_Type
   is
   begin
      return To_Hash (Wide_Wide_Calculate (Value));
   end Wide_Wide_Calculate;

   -- Calculate --
   function Calculate
     (Value : in Ada.Streams.Stream_Element_Array)
      return Hash_Type
   is
   begin
      return To_Hash (Calculate (Value));
   end Calculate;

   ------------
   -- Update --
   ------------

   type Word is record
      bt1 : Byte;
      bt0 : Byte;
   end record;

   for Word use record
      bt1 at 0 range 8 .. 15;
      bt0 at 0 range 0 .. 7;
   end record;

   for Word'Size use CRC_Type'Size;

   procedure Bit_XOR
     (L : in out Bit;
      R : in     Bit)
   is
   begin
      if L = Off then
         if R = On then
            L := On;
         else
            L := Off;
         end if;
      else
         if R = Off then
            L := On;
         else
            L := Off;
         end if;
      end if;
   end Bit_XOR;

   procedure Bits_XOR
     (L : in out Byte;
      R : in     Byte)
   is
   begin
      Bit_XOR (L.b0, R.b0);
      Bit_XOR (L.b1, R.b1);
      Bit_XOR (L.b2, R.b2);
      Bit_XOR (L.b3, R.b3);
      Bit_XOR (L.b4, R.b4);
      Bit_XOR (L.b5, R.b5);
      Bit_XOR (L.b6, R.b6);
      Bit_XOR (L.b7, R.b7);
   end Bits_XOR;

   function Bits_XOR
     (L : in Word;
      R : in Word)
      return Word
   is
      Result : Word := L;
   begin
      Bits_XOR (Result.bt1, R.bt1);
      Bits_XOR (Result.bt0, R.bt0);
      return Result;
   end Bits_XOR;

   function Bits_XOR
     (L : in Byte;
      R : in Byte)
      return Byte
   is
      Result : Byte := L;
   begin
      Bits_XOR (Result, R);
      return Result;
   end Bits_XOR;

   function Shift_Left
     (L : in Word)
      return Word
   is
      Result : Word := L;
   begin
      Result.bt1 := Result.bt0;
      Result.bt0 := (others => Off);
      return Result;
   end Shift_Left;

   procedure Update
     (This  : in out Hasher;
      Value : in     Byte_Array)
   is
      function To_Index is
        new Ada.Unchecked_Conversion
          (Byte, Index_Type);

      function To_CRC is
        new Ada.Unchecked_Conversion
          (CRC_Type, CRC_Type);

      function To_Word is
        new Ada.Unchecked_Conversion
          (CRC_Type, Word);

      function To_CRC is
        new Ada.Unchecked_Conversion
          (Word, CRC_Type);

      Reg       : Word := To_Word (This.Cm_Reg);
      Key_Index : Byte;
   begin
      This.Length := This.Length + Value'Length;

      if This.Length > Max_Len then
         raise Max_Len_Error;
      end if;

      for Index in Value'Range loop
         Key_Index := Bits_XOR (Reg.bt1, Value (Index));

         Reg := Bits_XOR
           (Shift_Left (Reg), To_Word (Keys (Integer (To_Index (Key_Index)))));
      end loop;

      This.Cm_Reg := To_CRC (Reg);
   end Update;

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
