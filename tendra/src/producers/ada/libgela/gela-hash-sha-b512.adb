
with Ada.Unchecked_Conversion;

package body Gela.Hash.SHA.b512 is

   --  K Constants
   K : constant array (1 .. 80) of Interfaces.Unsigned_64 :=
     (16#428A2F98D728AE22#, 16#7137449123EF65CD#,
      16#B5C0FBCFEC4D3B2F#, 16#E9B5DBA58189DBBC#,
      16#3956C25BF348B538#, 16#59F111F1B605D019#,
      16#923F82A4AF194F9B#, 16#AB1C5ED5DA6D8118#,
      16#D807AA98A3030242#, 16#12835B0145706FBE#,
      16#243185BE4EE4B28C#, 16#550C7DC3D5FFB4E2#,
      16#72BE5D74F27B896F#, 16#80DEB1FE3B1696B1#,
      16#9BDC06A725C71235#, 16#C19BF174CF692694#,
      16#E49B69C19EF14AD2#, 16#EFBE4786384F25E3#,
      16#0FC19DC68B8CD5B5#, 16#240CA1CC77AC9C65#,
      16#2DE92C6F592B0275#, 16#4A7484AA6EA6E483#,
      16#5CB0A9DCBD41FBD4#, 16#76F988DA831153B5#,
      16#983E5152EE66DFAB#, 16#A831C66D2DB43210#,
      16#B00327C898FB213F#, 16#BF597FC7BEEF0EE4#,
      16#C6E00BF33DA88FC2#, 16#D5A79147930AA725#,
      16#06CA6351E003826F#, 16#142929670A0E6E70#,
      16#27B70A8546D22FFC#, 16#2E1B21385C26C926#,
      16#4D2C6DFC5AC42AED#, 16#53380D139D95B3DF#,
      16#650A73548BAF63DE#, 16#766A0ABB3C77B2A8#,
      16#81C2C92E47EDAEE6#, 16#92722C851482353B#,
      16#A2BFE8A14CF10364#, 16#A81A664BBC423001#,
      16#C24B8B70D0F89791#, 16#C76C51A30654BE30#,
      16#D192E819D6EF5218#, 16#D69906245565A910#,
      16#F40E35855771202A#, 16#106AA07032BBD1B8#,
      16#19A4C116B8D2D0C8#, 16#1E376C085141AB53#,
      16#2748774CDF8EEB99#, 16#34B0BCB5E19B48A8#,
      16#391C0CB3C5C95A63#, 16#4ED8AA4AE3418ACB#,
      16#5B9CCA4F7763E373#, 16#682E6FF3D6B2B8A3#,
      16#748F82EE5DEFB2FC#, 16#78A5636F43172F60#,
      16#84C87814A1F0AB72#, 16#8CC702081A6439EC#,
      16#90BEFFFA23631E28#, 16#A4506CEBDE82BDE9#,
      16#BEF9A3F7B2C67915#, 16#C67178F2E372532B#,
      16#CA273ECEEA26619C#, 16#D186B8C721C0C207#,
      16#EADA7DD6CDE0EB1E#, 16#F57D4F7FEE6ED178#,
      16#06F067AA72176FBA#, 16#0A637DC5A2C898A6#,
      16#113F9804BEF90DAE#, 16#1B710B35131C471B#,
      16#28DB77F523047D84#, 16#32CAAB7B40C72493#,
      16#3C9EBE0A15C9BEBC#, 16#431D67C49C100D4C#,
      16#4CC5D4BECB3E42B6#, 16#597F299CFC657E2A#,
      16#5FCB6FAB3AD6FAEC#, 16#6C44198C4A475817#);

   Hex_Chars : constant array
     (Interfaces.Unsigned_64 range 0 .. 15) of Character :=
     ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
     'a', 'b', 'c', 'd', 'e', 'f');

   -- Stream_Element_Array8 --
   subtype Stream_Element_Array8 is
     Ada.Streams.Stream_Element_Array (1 .. 8);

   -- Endian --
   function Endian
     (Value : in Stream_Element_Array8)
      return Interfaces.Unsigned_64;

   -- Sigma0 --
   function Sigma0
     (Value : in Interfaces.Unsigned_64)
      return Interfaces.Unsigned_64;

   -- Sigma1 --
   function Sigma1
     (Value : in Interfaces.Unsigned_64)
      return Interfaces.Unsigned_64;

   -- E0 --
   function E0
     (Value : in Interfaces.Unsigned_64)
      return Interfaces.Unsigned_64;

   -- E1 --
   function E1
     (Value : in Interfaces.Unsigned_64)
      return Interfaces.Unsigned_64;

   -- Ch --
   function Ch
     (X, Y, Z : in Interfaces.Unsigned_64)
      return Interfaces.Unsigned_64;

   -- Maj --
   function Maj
     (X, Y, Z : in Interfaces.Unsigned_64)
      return Interfaces.Unsigned_64;

   ---------------
   -- Calculate --
   ---------------

   function Calculate
     (Value : in String)
      return SHA512
   is
      H   : Hasher_512;
      Res : SHA512;
   begin
      Update (H, Value);
      Result (H, Res);
      return Res;
   end Calculate;

   --------------------
   -- Wide_Calculate --
   --------------------

   function Wide_Calculate
     (Value : in Wide_String)
      return SHA512
   is
      H   : Hasher_512;
      Res : SHA512;
   begin
      Wide_Update (H, Value);
      Result (H, Res);
      return Res;
   end Wide_Calculate;

   -------------------------
   -- Wide_Wide_Calculate --
   -------------------------

   function Wide_Wide_Calculate
     (Value : in Wide_Wide_String)
      return SHA512
   is
      H   : Hasher_512;
      Res : SHA512;
   begin
      Wide_Wide_Update (H, Value);
      Result (H, Res);
      return Res;
   end Wide_Wide_Calculate;

   ---------------
   -- Calculate --
   ---------------

   function Calculate
     (Value : in Ada.Streams.Stream_Element_Array)
      return SHA512
   is
      H   : Hasher_512;
      Res : SHA512;
   begin
      Update (H, Value);
      Result (H, Res);
      return Res;
   end Calculate;

   ------------
   -- Update --
   ------------

   procedure Update
     (This  : in out Hasher_512;
      Value : in     Ada.Streams.Stream_Element_Array)
   is
      use Ada.Streams;

      Buffer : constant Stream_Element_Array :=
        This.Internal_Buffer (1 .. This.Last) & Value;

      Index : Stream_Element_Offset := Buffer'First;
   begin
      while Index + 127 <= Buffer'Last loop
         Process (This, Buffer (Index .. Index + 127));
         Index := Index + 128;
      end loop;

      This.Last := Buffer'Last - Index + 1;

      This.Internal_Buffer (1 .. This.Last) :=
        Buffer (Index .. Buffer'Last);

      This.Length := This.Length + Value'Length;
   end Update;

   -------------
   -- Process --
   -------------

   procedure Process
     (This  : in out Hasher_512;
      Value : in     Ada.Streams.Stream_Element_Array)
   is
      use Interfaces;
      use Ada.Streams;

      Hash : Hash_Array (1 .. 8) := This.Internal_Hash;

      W            : Hash_Array (1 .. 80);
      Temp1, Temp2 : Interfaces.Unsigned_64;
      Position     : Stream_Element_Offset;
   begin
      for Index in 1 .. 16 loop
         Position  := Stream_Element_Offset (((Index - 1) * 8) + 1);
         W (Index) := Endian (Value (Position .. Position + 7));
      end loop;

      for Index in 17 .. 80 loop
         W (Index) :=
           Sigma1 (W (Index - 2))
           + W (Index - 7)
           + Sigma0 (W (Index - 15))
           + W (Index - 16);
      end loop;

      for Index in 1 .. 80 loop
         Temp1 := Hash (8)
           + E1 (Hash (5))
           + Ch (Hash (5), Hash (6), Hash (7))
           + K (Index)
           + W (Index);

         Temp2 := E0 (Hash (1))
           + Maj (Hash (1), Hash (2), Hash (3));

         Hash (8) := Hash (7);
         Hash (7) := Hash (6);
         Hash (6) := Hash (5);
         Hash (5) := Hash (4) + Temp1;
         Hash (4) := Hash (3);
         Hash (3) := Hash (2);
         Hash (2) := Hash (1);
         Hash (1) := Temp1 + Temp2;
      end loop;

      for Index in 1 .. 8 loop
         This.Internal_Hash (Index) :=
           This.Internal_Hash (Index) + Hash (Index);
      end loop;
   end Process;

   ------------
   -- Result --
   ------------

   procedure Result
     (This  : in out Hasher_512;
      Value :    out SHA512)
   is
      use Ada.Streams;
      use Interfaces;

      Last   : Stream_Element_Array (1 .. 128) := (others => 0);
      Length : Unsigned_64 := Unsigned_64 (This.Length) * 8;

      Result_Position : Positive := Value'First;

      -- To_Hex --
      procedure To_Hex
        (Item : in Unsigned_64)
      is
         V        : Unsigned_64 := Item;
         Position : Integer     := Result_Position + 15;
      begin
         for Index in 1 .. 8 loop
            Value (Position) := Hex_Chars (V and 16#0F#);
            Position := Position - 1;
            V := Shift_Right (V, 4);
            Value (Position) := Hex_Chars (V and 16#0F#);
            Position := Position - 1;
            V := Shift_Right (V, 4);
         end loop;
         Result_Position := Result_Position + 16;
      end To_Hex;

   begin
      Last (1 .. This.Last) := This.Internal_Buffer (1 .. This.Last);
      Last (This.Last + 1)  := 16#80#;

      if This.Last > 112 then
         Process (This, Last);
         Last := (others => 0);
      end if;

      for Index in 121 .. 128 loop
         Last (Stream_Element_Offset (Index)) :=
           Stream_Element
             ((Shift_Right (Length, (128 - Index) * 8)) and 16#FF#);
      end loop;

      Process (This, Last);

      for Index in 1 .. 8 loop
         To_Hex (This.Internal_Hash (Index));
      end loop;
   end Result;

   ------------
   -- Endian --
   ------------

   function Endian
     (Value : in Stream_Element_Array8)
      return Interfaces.Unsigned_64
   is
      function To_I64 is
        new Ada.Unchecked_Conversion
          (Stream_Element_Array8, Interfaces.Unsigned_64);

      Temp : Stream_Element_Array8 :=
        (Value (8), Value (7), Value (6), Value (5),
         Value (4), Value (3), Value (2), Value (1));
   begin
      return To_I64 (Temp);
   end Endian;

   ------------
   -- Sigma0 --
   ------------

   function Sigma0
     (Value : in Interfaces.Unsigned_64)
      return Interfaces.Unsigned_64
   is
      use Interfaces;
   begin
      return Rotate_Right (Value, 1)
        xor Rotate_Right (Value, 8)
        xor Shift_Right (Value, 7);
   end Sigma0;

   ------------
   -- Sigma1 --
   ------------

   function Sigma1
     (Value : in Interfaces.Unsigned_64)
      return Interfaces.Unsigned_64
   is
      use Interfaces;
   begin
      return Rotate_Right (Value, 19)
        xor Rotate_Right (Value, 61)
        xor Shift_Right (Value, 6);
   end Sigma1;

   --------
   -- E0 --
   --------

   function E0
     (Value : in Interfaces.Unsigned_64)
      return Interfaces.Unsigned_64
   is
      use Interfaces;
   begin
      return Rotate_Right (Value, 28)
        xor Rotate_Right (Value, 34)
        xor Rotate_Right (Value, 39);
   end E0;

   --------
   -- E1 --
   --------

   function E1
     (Value : in Interfaces.Unsigned_64)
      return Interfaces.Unsigned_64
   is
      use Interfaces;
   begin
      return Rotate_Right (Value, 14)
        xor Rotate_Right (Value, 18)
        xor Rotate_Right (Value, 41);
   end E1;

   --------
   -- Ch --
   --------

   function Ch
     (X, Y, Z : in Interfaces.Unsigned_64)
      return Interfaces.Unsigned_64
   is
      use Interfaces;
   begin
      return (X and Y) xor ((not X) and Z);
   end Ch;

   ---------
   -- Maj --
   ---------

   function Maj
     (X, Y, Z : in Interfaces.Unsigned_64)
      return Interfaces.Unsigned_64
   is
      use Interfaces;
   begin
      return (X and Y) xor (X and Z) xor (Y and Z);
   end Maj;

end Gela.Hash.SHA.b512;

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
