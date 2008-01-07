with Gela.Embeded_Links.Lists;
with Gela.Embeded_Links.Double_Lists;

generic
   --  Element of list
   type Element (<>) is limited private;
   --  Pointer to element of list
   type Element_Ptr is access all Element;

   type Hash_Type is range <>;
   with function Hash (Item : Element) return Hash_Type is <>;

   with function  Get_Next_Hash (Item : Element_Ptr) return Element_Ptr is <>;
   with procedure Set_Next_Hash (Item, Next : Element_Ptr) is <>;
   with function  Get_Next (Item : Element_Ptr) return Element_Ptr is <>;
   with procedure Set_Next (Item, Next : Element_Ptr) is <>;
   with function  Get_Prev (Item : Element_Ptr) return Element_Ptr is <>;
   with procedure Set_Prev (Item, Prev : Element_Ptr) is <>;
   with function "=" (Left, Right : Element) return Boolean is <>;

package Gela.Embeded_Links.Caches is

   type Cache (Size : Hash_Type) is limited private;

   function Preferred_Size (Size : Hash_Type) return Hash_Type;

   procedure Add
     (Container : in out Cache;
      Item      : in     Element_Ptr;
      Removed   :    out Element_Ptr);

   procedure Remove
     (Container : in out Cache;
      Item      : in     Element_Ptr);

   procedure Find
     (Container : in out Cache;
      Item      : in     Element;
      Result    :    out Element_Ptr;
      Touch     : in     Boolean := True);

private

   package Lists is new Gela.Embeded_Links.Lists
     (Element, Element_Ptr, Get_Next_Hash, Set_Next_Hash);

   package FIFO_Lists is new Double_Lists (Element, Element_Ptr);

   type List_Array is array (Hash_Type range <>) of Lists.List;

   type Cache (Size : Hash_Type) is record
      FIFO    : FIFO_Lists.List;
      Choices : List_Array (1 .. Size);
   end record;

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
