with Gela.Classificators.Cache;

package body Gela.Classificators.UTF_16 is

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
      Item_2       : Code_Point;
      Class        : Character_Class;
      Skip         : Boolean;
   begin
      loop
         Code := Element (Input);
         Item := Code_Unit'Pos (Code);
         Next (Input);
         Code := Element (Input);
         Item := Item + 256 * Code_Unit'Pos (Code);

         if Item in 16#D800# .. 16#DBFF# then
            Next (Input);
            Code := Element (Input);
            Item_2 := Code_Unit'Pos (Code);
            Next (Input);
            Code := Element (Input);
            Item_2 := Item_2 + 256 * Code_Unit'Pos (Code);
            Item := (Item - 16#D800#) * 2 ** 10 + (Item_2 - 16#DC00#);
            Skip := True;
         else
            Skip := False;
         end if;

         Class := Cache.Get_Character_Class (Item);

         Put (Buffer, Class, Full);

         exit when Item = 0;

         Next (Input);

         Put (Buffer, Skip_Code, Full);

         if Skip then
            Put (Buffer, Skip_Code, Full);
            Put (Buffer, Skip_Code, Full);
         end if;

         if Full then
            Put (Buffer, End_Of_Buffer, Full);
            return;
         end if;
      end loop;
   end Read;

end Gela.Classificators.UTF_16;

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
