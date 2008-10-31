package body Gela.Decoders.Fixed_Width_8 is

   ------------
   -- Decode --
   ------------

   procedure Decode
     (Object : in     Decoder;
      From   : in     Source_Buffers.Cursor;
      To     : in     Source_Buffers.Cursor;
      Result :    out Wide_String;
      Last   :    out Natural)
   is
      use Source_Buffers;
      Pos   : Cursor := From;
      Char  : Character;
      Index : Natural := Result'First - 1;
   begin
      while Pos /= To loop
         Index := Index + 1;

         Char := Element (Pos);
         Next (Pos);

         if Character'Pos (Char) in Object.Table'Range then
            Result (Index) := Object.Table (Character'Pos (Char));
         else
            Result (Index) := Wide_Character'Val (Character'Pos (Char));
         end if;
      end loop;

      Last := Index;
   end Decode;

end Gela.Decoders.Fixed_Width_8;

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
