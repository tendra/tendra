
with Ada.Unchecked_Conversion;

package body Gela.Hash.SHA is

   ------------
   -- Update --
   ------------

   procedure Update
     (This  : in out Hasher'Class;
      Value : in     String)
   is
      use Ada.Streams;

      subtype C_Array is
        Ada.Streams.Stream_Element_Array
          (1 .. Value'Size / Stream_Element'Size);

      function To_Array is
        new Ada.Unchecked_Conversion (String, C_Array);
   begin
      Update (This, To_Array (Value));
   end Update;

   -----------------
   -- Wide_Update --
   -----------------

   procedure Wide_Update
     (This  : in out Hasher'Class;
      Value : in     Wide_String)
   is
      use Ada.Streams;

      subtype C_Array is
        Ada.Streams.Stream_Element_Array
          (1 .. Value'Size / Stream_Element'Size);

      function To_Array is
        new Ada.Unchecked_Conversion (Wide_String, C_Array);
   begin
      Update (This, To_Array (Value));
   end Wide_Update;

   ----------------------
   -- Wide_Wide_Update --
   ----------------------

   procedure Wide_Wide_Update
     (This  : in out Hasher'Class;
      Value : in     Wide_Wide_String)
   is
      use Ada.Streams;

      subtype C_Array is
        Ada.Streams.Stream_Element_Array
          (1 .. Value'Size / Stream_Element'Size);

      function To_Array is
        new Ada.Unchecked_Conversion (Wide_Wide_String, C_Array);
   begin
      Update (This, To_Array (Value));
   end Wide_Wide_Update;

end Gela.Hash.SHA;

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
