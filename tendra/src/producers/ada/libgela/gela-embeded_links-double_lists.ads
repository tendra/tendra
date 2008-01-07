--  This is effective implementation of double linked list container.
--  Item of the list contains embeded link to next and prev elements, so
--    +  no memory allocation required
--    +  limited undefinite types allowed as items of list
--    -  it can't be in more then one list at once.
--    -  easy to break list if pass element to wrong list

with Gela.Embeded_Links.Lists;

generic
   type Element_Type (<>) is limited private;
   type Element_Access is access all Element_Type;

   --  get embeded link of element
   with function  Get_Next (Item : Element_Access) return Element_Access is <>;
   with function  Get_Prev (Item : Element_Access) return Element_Access is <>;
   --  set embeded link of element
   with procedure Set_Next (Item, Next : Element_Access) is <>;
   with procedure Set_Prev (Item, Prev : Element_Access) is <>;

package Gela.Embeded_Links.Double_Lists is

   package Simple_Lists is
      new Gela.Embeded_Links.Lists (Element_Type, Element_Access);

   type List is new Simple_Lists.List;

   --  Empty_List : List renames List (Simple_Lists.Empty_List); ???

   procedure Clear (Container : in out List);

   procedure Insert_After
     (Container : in out List;
      After     : in     Element_Access;
      New_Item  : in     Element_Access);

   procedure Insert
     (Container : in out List;
      Before    : in     Element_Access;
      New_Item  : in     Element_Access);

   procedure Append
     (Container : in out List;
      New_Item  : in     Element_Access);

   procedure Prepend
     (Container : in out List;
      New_Item  : in     Element_Access);

   procedure Delete
     (Container : in out List;
      Item      : in     Element_Access);

   procedure Delete_Next
     (Container : in out List;
      After     : in     Element_Access;
      Removed   :    out Element_Access);

   procedure Delete_First
     (Container : in out List;
      Removed   :    out Element_Access);

   procedure Delete_Last
     (Container : in out List;
      Removed   :    out Element_Access);

   procedure Splice_After
     (Target   : in out List;
      Source   : in out List;
      After    : in     Element_Access := null);

   generic package Generic_Search renames Simple_Lists.Generic_Search;

   generic procedure For_Each renames Simple_Lists.For_Each;

   generic procedure For_Each_With_Param
     renames Simple_Lists.For_Each_With_Param;

   generic function To_Array renames Simple_Lists.To_Array;

   generic function Agreed_To_Array renames Simple_Lists.Agreed_To_Array;

   generic function Agreed_To_Array_With_Param
     renames Simple_Lists.Agreed_To_Array_With_Param;

private

--   Empty_List : constant List := (Tail => null);

   pragma Inline (Insert);
   pragma Inline (Insert_After);
   pragma Inline (Append);
   pragma Inline (Prepend);
   pragma Inline (Delete);
   pragma Inline (Delete_Next);
   pragma Inline (Delete_First);
   pragma Inline (Delete_Last);
   pragma Inline (Splice_After);

end Gela.Embeded_Links.Double_Lists;


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
