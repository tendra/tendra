------------------------------------------------------------------------------
--                         G E L A   H A S H                                --
--                 Repository implementation for Gela                       --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  Purpose:
--  Hash by SHA-256 algoritm
--

with Interfaces;

package Gela.Hash.SHA.b256 is

   type SHA256 is
     array (1 .. 64) of Character;

   type Hasher_256 is
     new Hasher with private;

   Initial_Hasher : constant Hasher_256;

   procedure Result
     (This  : in out Hasher_256;
      Value :    out SHA256);

   function Calculate
     (Value : in String)
      return SHA256;

   function Wide_Calculate
     (Value : in Wide_String)
      return SHA256;

   function Wide_Wide_Calculate
     (Value : in Wide_Wide_String)
      return SHA256;

   function Calculate
     (Value : in Ada.Streams.Stream_Element_Array)
      return SHA256;

--     overriding
   procedure Update
     (This  : in out Hasher_256;
      Value : in     Ada.Streams.Stream_Element_Array);

private

   --  SHA-256 constants
   H1 : constant := 16#6a09e667#;
   H2 : constant := 16#bb67ae85#;
   H3 : constant := 16#3c6ef372#;
   H4 : constant := 16#a54ff53a#;
   H5 : constant := 16#510e527f#;
   H6 : constant := 16#9b05688c#;
   H7 : constant := 16#1f83d9ab#;
   H8 : constant := 16#5be0cd19#;

   type Hash_Array is
     array (Positive range <>) of Interfaces.Unsigned_32;

   type Hasher_256 is new Hasher
   with record
      Internal_Buffer : Ada.Streams.Stream_Element_Array (1 .. 63) :=
        (others => 0);

      Internal_Hash : Hash_Array (1 .. 8) :=
        (H1, H2, H3, H4, H5, H6, H7, H8);
   end record;

   procedure Process
     (This  : in out Hasher_256;
      Value : in     Ada.Streams.Stream_Element_Array);

   Initial_Hasher : constant Hasher_256 :=
     (Length          => 0,
      Last            => 0,
      Internal_Hash   => (H1, H2, H3, H4, H5, H6, H7, H8),
      Internal_Buffer => (others => 0));

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
