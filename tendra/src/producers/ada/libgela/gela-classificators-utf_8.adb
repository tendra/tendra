with Gela.Classificators.Cache;

package body Gela.Classificators.UTF_8 is

   package Cache is new Classificators.Cache (To_Character_Class);

   ----------------
   -- Initialize --
   ----------------

   procedure Initialize is
   begin
      Cache.Initialize;
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

      Full         : Boolean;
      Code         : Code_Unit;
      Item         : Code_Point;
      Class        : Character_Class;
      Skip         : Natural range  0 .. 5;
   begin
      loop
         Code  := Element (Input);
         Item  := Code_Unit'Pos (Code);

         case Item is
            when 16#00# .. 16#7F# =>
               Skip := 0;
            when 16#80# .. 2#1101_1111# =>
               Skip := 1;
               Next (Input);
               Item := (Item and 2#1_1111#) * 2 ** 6 +
                 (Code_Unit'Pos (Element (Input)) and 2#11_1111#);
            when 2#1110_0000# .. 2#1110_1111# =>
               Skip := 2;
               Next (Input);
               Item := (Item and 2#1111#) * 2 ** 6 +
                 (Code_Unit'Pos (Element (Input)) and 2#11_1111#);

               Next (Input);
               Item := Item * 2 ** 6 +
                 (Code_Unit'Pos (Element (Input)) and 2#11_1111#);
            when 2#1111_0000# .. 2#1111_0111# =>
               Skip := 3;
               Next (Input);
               Item := (Item and 2#111#) * 2 ** 6 +
                 (Code_Unit'Pos (Element (Input)) and 2#11_1111#);

               Next (Input);
               Item := Item * 2 ** 6 +
                 (Code_Unit'Pos (Element (Input)) and 2#11_1111#);

               Next (Input);
               Item := Item * 2 ** 6 +
                 (Code_Unit'Pos (Element (Input)) and 2#11_1111#);
            when 2#1111_1000# .. 2#1111_1011# =>
               Skip := 4;
               Item := 16#FFFF#;
               Next (Input);
               Next (Input);
               Next (Input);
               Next (Input);
            when others =>
               Skip := 5;
               Item := 16#FFFF#;
               Next (Input);
               Next (Input);
               Next (Input);
               Next (Input);
               Next (Input);
         end case;

         Class := Cache.Get_Character_Class (Item);

         Put (Buffer, Class, Full);

         if Code = End_Of_File then
            Put (Buffer, Class, Full);
            exit;
         end if;

         Next (Input);

         for J in 1 .. Skip loop
            Put (Buffer, Skip_Code, Full);
         end loop;

         if Full then
            Put (Buffer, End_Of_Buffer, Full);
            return;
         end if;
      end loop;
   end Read;

end Gela.Classificators.UTF_8;

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
