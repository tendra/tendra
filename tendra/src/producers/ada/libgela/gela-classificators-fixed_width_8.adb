with Gela.Source_Buffers.Strings;
with Gela.Character_Class_Buffers;

package body Gela.Classificators.Fixed_Width_8 is

   ----------------
   -- Initialize --
   ----------------

   procedure Initialize
     (Object  :    out Classificator;
      Decoder : in     Decoders.Decoder'Class)
   is
      use Gela.Source_Buffers;
      Input   : Strings.Source_Buffer;
      Trivial : String (1 .. 256);
      Plain   : Wide_String (Trivial'Range);
      Last    : Natural;
      From    : Cursor;
      To      : Cursor;
   begin
      for J in Trivial'Range loop
         Trivial (J) := Code_Unit'Val (J - 1);
      end loop;

      Strings.Initialize (Input, Trivial);
      From := Strings.Buffer_Start (Input);
      To   := From;

      loop
         Next (To);
         exit when Element (To) = End_Of_File;
      end loop;

      Decoders.Decode (Decoder, From, To, Plain, Last);

      for J in Plain'Range loop
         Object.Table (Code_Unit'Val (J - 1)) :=
           To_Character_Class (Wide_Character'Pos (Plain (J)));
      end loop;

      Strings.Clear (Input);
   end Initialize;

   ----------
   -- Read --
   ----------

   procedure Read
     (Object : in out Classificator;
      Input  : in out Source_Buffers.Cursor;
      Buffer : in out Character_Class_Buffers.Character_Class_Buffer)
   is
      use Gela.Source_Buffers;
      use Gela.Character_Class_Buffers;

      Full  : Boolean;
      Item  : Code_Unit;
      Class : Character_Class;
   begin
      loop
         Item  := Element (Input);
         Class := Object.Table (Item);
         Put (Buffer, Class, Full);

         exit when Item = End_Of_File;

         Next (Input);

         if Full then
            Put (Buffer, End_Of_Buffer, Full);
            return;
         end if;
      end loop;
   end Read;

end Gela.Classificators.Fixed_Width_8;

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
