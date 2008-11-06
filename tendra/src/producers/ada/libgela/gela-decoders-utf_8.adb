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

         case Char is
            when 16#00# .. 16#7F# =>
               Result (Index) := Wide_Character'Val (Char);
            when 16#80# .. 2#1101_1111# =>
               Char := (Char and 2#1_1111#) * 2 ** 6 +
                 (Character'Pos (Element (Pos)) and 2#11_1111#);
               Next (Pos);
               Result (Index) := Wide_Character'Val (Char);
            when 2#1110_0000# .. 2#1110_1111# =>
               Char := (Char and 2#1111#) * 2 ** 6 +
                 (Character'Pos (Element (Pos)) and 2#11_1111#);
               Next (Pos);

               Char := Char * 2 ** 6 +
                 (Character'Pos (Element (Pos)) and 2#11_1111#);
               Next (Pos);
               Result (Index) := Wide_Character'Val (Char);
            when 2#1111_0000# .. 2#1111_0111# =>
               Char := (Char and 2#111#) * 2 ** 6 +
                 (Character'Pos (Element (Pos)) and 2#11_1111#);
               Next (Pos);

               Char := Char * 2 ** 6 +
                 (Character'Pos (Element (Pos)) and 2#11_1111#);
               Next (Pos);

               Char := Char * 2 ** 6 +
                 (Character'Pos (Element (Pos)) and 2#11_1111#);
               Next (Pos);

               if Char > 16#FFFF# then
                  Char := Char - 16#1_0000#;
                  Result (Index) :=
                    Wide_Character'Val (16#D800# + (Char / 2 ** 10));
                  Index := Index + 1;
                  Result (Index) :=
                    Wide_Character'Val (16#DC00# + (Char and 16#3FF#));
               else
                  Result (Index) := Wide_Character'Val (Char);
               end if;
            when 2#1111_1000# .. 2#1111_1011# =>
               Result (Index) := Wide_Character'Last;
               Next (Pos);
               Next (Pos);
               Next (Pos);
               Next (Pos);
            when others =>
               Result (Index) := Wide_Character'Last;
               Next (Pos);
               Next (Pos);
               Next (Pos);
               Next (Pos);
               Next (Pos);
         end case;
      end loop;

      Last := Index;
   end Decode;

end Gela.Decoders.UTF_8;

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
