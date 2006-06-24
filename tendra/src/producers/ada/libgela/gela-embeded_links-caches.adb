package body Gela.Embeded_Links.Caches is

   package Search is new Lists.Generic_Search;

   use Lists;
   use Search;
   use FIFO_Lists;

   ---------
   -- Add --
   ---------

   procedure Add
     (Container : in out Cache;
      Item      : in     Element_Ptr;
      Removed   :    out Element_Ptr)
   is
      Index   : Hash_Type := Hash (Item.all) mod Container.Size + 1;
      Temp    : Element_Ptr;
   begin
      if not Is_Empty (Container.Choices (Index)) then
         Temp := Find (Container.Choices (Index), Item.all);

         if Temp /= null then
            Removed := null;
            return;
         end if;

         Removed := First (Container.FIFO);
         Remove (Container, Removed);
      else
         Removed := null;
      end if;

      Append (Container.Choices (Index), Item);
      Append (Container.FIFO, Item);
   end Add;

   ----------
   -- Find --
   ----------

   procedure Find
     (Container : in out Cache;
      Item      : in     Element;
      Result    :    out Element_Ptr;
      Touch     : in     Boolean := True)
   is
      Index : Hash_Type := Hash (Item) mod Container.Size + 1;
   begin
      Result := Find (Container.Choices (Index), Item);

      if Result /= null and Touch then
         Delete (Container.FIFO, Result);
         Append (Container.FIFO, Result);
      end if;
   end Find;

   --------------------
   -- Preferred_Size --
   --------------------

   function Preferred_Size (Size : Hash_Type) return Hash_Type is
      Try  : Hash_Type := Size;
      Mult : Hash_Type;
   begin
      loop
         Mult := 2;

         while Mult * Mult <= Try and Try mod Mult /= 0 loop
            Mult := Mult + 1;
         end loop;

         exit when Mult * Mult > Try;

         Try := Try + 1;
      end loop;

      return Try;
   end Preferred_Size;

   ------------
   -- Remove --
   ------------

   procedure Remove
     (Container : in out Cache;
      Item      : in     Element_Ptr)
   is
      Index : Hash_Type   := Hash (Item.all) mod Container.Size + 1;
      Temp  : Element_Ptr := Find (Container.Choices (Index), Item.all);
   begin
      if Temp /= null then
         Delete (Container.Choices (Index), Item);
         Delete (Container.FIFO, Item);
      end if;
   end Remove;

end Gela.Embeded_Links.Caches;



------------------------------------------------------------------------------
--  Copyright (c) 2006, Maxim Reznik
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
