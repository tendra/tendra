with Gela.Classificators;

package body Gela.Decoders.UTF_8 is

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
      use type Gela.Classificators.Code_Point;

      Pos   : Cursor := From;
      Char  : Gela.Classificators.Code_Point;
      Index : Natural := Result'First - 1;
   begin
      while Pos /= To loop
         Index := Index + 1;

         Char := Character'Pos (Element (Pos));
         Next (Pos);
         Char := Char + 256 * Character'Pos (Element (Pos));
         Next (Pos);
         Result (Index) := Wide_Character'Val (Char);
      end loop;

      Last := Index;
   end Decode;

end Gela.Decoders.UTF_8;

------------------------------------------------------------------------------
--  Copyright (c) 2009, Maxim Reznik
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
