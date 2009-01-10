with Ada.Unchecked_Conversion;
with Ada.Unchecked_Deallocation;

package body Gela.Source_Buffers.Wide_Strings is

   type Wide_Character_Access is access all Wide_Character;
   pragma Controlled (Wide_Character_Access);

   ------------------
   -- Buffer_Start --
   ------------------

   function Buffer_Start (Object : Source_Buffer) return Cursor is
   begin
      return Object.Buffer_Start;
   end Buffer_Start;

   -----------
   -- Clear --
   -----------

   procedure Clear (Object : in out Source_Buffer) is
      procedure Free is new Ada.Unchecked_Deallocation
        (Wide_String_Buffer, Wide_String_Access);
   begin
      if Object.Buffer /= null then
         Free (Object.Buffer);
      end if;
   end Clear;

   ----------------
   -- Initialize --
   ----------------

   procedure Initialize
     (Object : in out Source_Buffer;
      Text   : in     Wide_String)
   is
      function "+" is new Ada.Unchecked_Conversion
        (Source => Wide_Character_Access, Target => Cursor);

   begin
      Clear (Object);
      Object.Buffer := new Wide_String_Buffer (1 .. Text'Length + 1);
      Object.Buffer.all (Object.Buffer.all'Last) := Wide_Character'Val (0);
      Object.Buffer.all (1 .. Text'Length) := Wide_String_Buffer (Text);
      Object.Buffer_Start := +(Object.Buffer.all (1)'Access);
   end Initialize;

end Gela.Source_Buffers.Wide_Strings;

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
------------------------------------------------------------------------------
