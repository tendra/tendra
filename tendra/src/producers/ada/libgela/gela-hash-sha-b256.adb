
with Ada.Unchecked_Conversion;

package body Gela.Hash.SHA.b256 is

   --  K Constants
   K : constant array (1 .. 64) of Interfaces.Unsigned_32 :=
     (16#428a2f98#, 16#71374491#, 16#b5c0fbcf#, 16#e9b5dba5#,
      16#3956c25b#, 16#59f111f1#, 16#923f82a4#, 16#ab1c5ed5#,
      16#d807aa98#, 16#12835b01#, 16#243185be#, 16#550c7dc3#,
      16#72be5d74#, 16#80deb1fe#, 16#9bdc06a7#, 16#c19bf174#,
      16#e49b69c1#, 16#efbe4786#, 16#0fc19dc6#, 16#240ca1cc#,
      16#2de92c6f#, 16#4a7484aa#, 16#5cb0a9dc#, 16#76f988da#,
      16#983e5152#, 16#a831c66d#, 16#b00327c8#, 16#bf597fc7#,
      16#c6e00bf3#, 16#d5a79147#, 16#06ca6351#, 16#14292967#,
      16#27b70a85#, 16#2e1b2138#, 16#4d2c6dfc#, 16#53380d13#,
      16#650a7354#, 16#766a0abb#, 16#81c2c92e#, 16#92722c85#,
      16#a2bfe8a1#, 16#a81a664b#, 16#c24b8b70#, 16#c76c51a3#,
      16#d192e819#, 16#d6990624#, 16#f40e3585#, 16#106aa070#,
      16#19a4c116#, 16#1e376c08#, 16#2748774c#, 16#34b0bcb5#,
      16#391c0cb3#, 16#4ed8aa4a#, 16#5b9cca4f#, 16#682e6ff3#,
      16#748f82ee#, 16#78a5636f#, 16#84c87814#, 16#8cc70208#,
      16#90befffa#, 16#a4506ceb#, 16#bef9a3f7#, 16#c67178f2#);

   Hex_Chars : constant array
     (Interfaces.Unsigned_32 range 0 .. 15) of Character :=
     ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
     'a', 'b', 'c', 'd', 'e', 'f');

   -- Stream_Element_Array4 --
   subtype Stream_Element_Array4 is
     Ada.Streams.Stream_Element_Array (1 .. 4);

   -- Endian --
   function Endian
     (Value : in Stream_Element_Array4)
      return Interfaces.Unsigned_32;

   -- Sigma0 --
   function Sigma0
     (Value : in Interfaces.Unsigned_32)
      return Interfaces.Unsigned_32;

   -- Sigma1 --
   function Sigma1
     (Value : in Interfaces.Unsigned_32)
      return Interfaces.Unsigned_32;

   -- E0 --
   function E0
     (Value : in Interfaces.Unsigned_32)
      return Interfaces.Unsigned_32;

   -- E1 --
   function E1
     (Value : in Interfaces.Unsigned_32)
      return Interfaces.Unsigned_32;

   -- Ch --
   function Ch
     (X, Y, Z : in Interfaces.Unsigned_32)
      return Interfaces.Unsigned_32;

   -- Maj --
   function Maj
     (X, Y, Z : in Interfaces.Unsigned_32)
      return Interfaces.Unsigned_32;

   ---------------
   -- Calculate --
   ---------------

   function Calculate
     (Value : in String)
      return SHA256
   is
      H   : Hasher_256;
      Res : SHA256;
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
      return SHA256
   is
      H   : Hasher_256;
      Res : SHA256;
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
      return SHA256
   is
      H   : Hasher_256;
      Res : SHA256;
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
      return SHA256
   is
      H   : Hasher_256;
      Res : SHA256;
   begin
      Update (H, Value);
      Result (H, Res);
      return Res;
   end Calculate;

   ------------
   -- Update --
   ------------

   procedure Update
     (This  : in out Hasher_256;
      Value : in     Ada.Streams.Stream_Element_Array)
   is
      use Ada.Streams;

      Buffer : constant Stream_Element_Array :=
        This.Internal_Buffer (1 .. This.Last) & Value;

      Index : Stream_Element_Offset := Buffer'First;
   begin
      while Index + 63 <= Buffer'Last loop
         Process (This, Buffer (Index .. Index + 63));
         Index := Index + 64;
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
     (This  : in out Hasher_256;
      Value : in     Ada.Streams.Stream_Element_Array)
   is
      use Interfaces;
      use Ada.Streams;

      Hash : Hash_Array (1 .. 8) := This.Internal_Hash;

      W            : Hash_Array (1 .. 64);
      Temp1, Temp2 : Interfaces.Unsigned_32;
      Position     : Stream_Element_Offset;
   begin
      for Index in 1 .. 16 loop
         Position  := Stream_Element_Offset (((Index - 1) * 4) + 1);
         W (Index) := Endian (Value (Position .. Position + 3));
      end loop;

      for Index in 17 .. 64 loop
         W (Index) :=
           Sigma1 (W (Index - 2))
           + W (Index - 7)
           + Sigma0 (W (Index - 15))
           + W (Index - 16);
      end loop;

      for Index in 1 .. 64 loop
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
     (This  : in out Hasher_256;
      Value :    out SHA256)
   is
      use Ada.Streams;
      use Interfaces;

      Last   : Stream_Element_Array (1 .. 64) := (others => 0);
      Length : Unsigned_64 := Unsigned_64 (This.Length) * 8;

      Result_Position : Positive := Value'First;

      -- To_Hex --
      procedure To_Hex
        (Item : in Unsigned_32)
      is
         V        : Unsigned_32 := Item;
         Position : Integer     := Result_Position + 7;
      begin
         for Index in 1 .. 4 loop
            Value (Position) := Hex_Chars (V and 16#0F#);
            Position := Position - 1;
            V := Shift_Right (V, 4);
            Value (Position) := Hex_Chars (V and 16#0F#);
            Position := Position - 1;
            V := Shift_Right (V, 4);
         end loop;
         Result_Position := Result_Position + 8;
      end To_Hex;

   begin
      Last (1 .. This.Last) := This.Internal_Buffer (1 .. This.Last);
      Last (This.Last + 1)  := 16#80#;

      if This.Last > 55 then
         Process (This, Last);
         Last := (others => 0);
      end if;

      for Index in 57 .. 64 loop
         Last (Stream_Element_Offset (Index)) :=
           Stream_Element
             ((Shift_Right (Length, (64 - Index) * 8)) and 16#FF#);
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
     (Value : in Stream_Element_Array4)
      return Interfaces.Unsigned_32
   is
      function To_I32 is
        new Ada.Unchecked_Conversion
          (Stream_Element_Array4, Interfaces.Unsigned_32);

      Temp : Stream_Element_Array4 :=
        (Value (4), Value (3), Value (2), Value (1));
   begin
      return To_I32 (Temp);
   end Endian;

   ------------
   -- Sigma0 --
   ------------

   function Sigma0
     (Value : in Interfaces.Unsigned_32)
      return Interfaces.Unsigned_32
   is
      use Interfaces;
   begin
      return Rotate_Right (Value, 7)
        xor Rotate_Right (Value, 18)
        xor Shift_Right (Value, 3);
   end Sigma0;

   ------------
   -- Sigma1 --
   ------------

   function Sigma1
     (Value : in Interfaces.Unsigned_32)
      return Interfaces.Unsigned_32
   is
      use Interfaces;
   begin
      return Rotate_Right (Value, 17)
        xor Rotate_Right (Value, 19)
        xor Shift_Right (Value, 10);
   end Sigma1;

   --------
   -- E0 --
   --------

   function E0
     (Value : in Interfaces.Unsigned_32)
      return Interfaces.Unsigned_32
   is
      use Interfaces;
   begin
      return Rotate_Right (Value, 2)
        xor Rotate_Right (Value, 13)
        xor Rotate_Right (Value, 22);
   end E0;

   --------
   -- E1 --
   --------

   function E1
     (Value : in Interfaces.Unsigned_32)
      return Interfaces.Unsigned_32
   is
      use Interfaces;
   begin
      return Rotate_Right (Value, 6)
        xor Rotate_Right (Value, 11)
        xor Rotate_Right (Value, 25);
   end E1;

   --------
   -- Ch --
   --------

   function Ch
     (X, Y, Z : in Interfaces.Unsigned_32)
      return Interfaces.Unsigned_32
   is
      use Interfaces;
   begin
      return (X and Y) xor ((not X) and Z);
   end Ch;

   ---------
   -- Maj --
   ---------

   function Maj
     (X, Y, Z : in Interfaces.Unsigned_32)
      return Interfaces.Unsigned_32
   is
      use Interfaces;
   begin
      return (X and Y) xor (X and Z) xor (Y and Z);
   end Maj;

end Gela.Hash.SHA.b256;

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
