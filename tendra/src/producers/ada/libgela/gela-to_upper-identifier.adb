------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$

separate (Gela.To_Upper)
procedure Identifier
  (Text   : in     Wide_String;
   Result :    out Wide_String;
   Last   :    out Natural)
is
   subtype Code_Point is Item range 0 .. 16#10FFFF#;

   K     : Positive := Result'First;
   Code  : Code_Point;
   Pos   : Code_Point;
   Upper : Item;
begin
   for J in Text'Range loop
      Pos := W'Pos (Text (J));

      if Pos in 16#D800# .. 16#DBFF# then
         Code := Pos - 16#D800#;
      else
         if Pos in 16#DC00# .. 16#DFFF# then
            Pos := 2 ** 10 * Code + (Pos - 16#DC00#) + 16#1_0000#;
         end if;

         Upper := S (Pos / 256).all (Pos mod 256);

         if Upper <= Code_Point'Last then
            if Upper = It_Self then
               Code := Pos;
            else
               Code := Upper;
            end if;

            if Code <= 16#FFFF# then
               Result (K) := W'Val (Code);
            else
               Result (K) := W'Val ((Code / 2 ** 10 + 16#D400#));
               K := K + 1;
               Result (K) := W'Val ((Code mod 2 ** 10 + 16#DC00#));
            end if;

            K := K + 1;
         else
            for J in 1 .. Upper mod 4 loop
               Result (K) := Special_Casing (Integer (Upper/4 + J - 1));
               K := K + 1;
            end loop;
         end if;
      end if;
   end loop;

   Last := K - 1;
end Identifier;

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
