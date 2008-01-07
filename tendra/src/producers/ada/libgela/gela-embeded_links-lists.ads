--  This is effective implementation of list container.
--  Item of the list contains embeded link to next element, so
--    +  no memory allocation required
--    +  limited undefinite types allowed as items of list
--    -  it can't be in more then one list at once.
--    -  easy to break list if pass element to wrong list

generic
   type Element_Type (<>) is limited private;
   type Element_Access is access all Element_Type;

   --  get embeded link of element
   with function  Get_Next (Item : Element_Access) return Element_Access is <>;
   --  set embeded link of element
   with procedure Set_Next (Item, Next : Element_Access) is <>;

package Gela.Embeded_Links.Lists is
   pragma Pure (Lists);

   type List is limited private;

   Empty_List : constant List;

   function Length   (Container : List) return Natural; -- Count_Type;
   function Is_Empty (Container : List) return Boolean;

   procedure Clear (Container : in out List);

   procedure Insert_After
     (Container : in out List;
      After     : in     Element_Access;
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

   procedure Splice_After
     (Target   : in out List;
      Source   : in out List;
      After    : in     Element_Access := null);

   function First    (Container : List) return Element_Access;
   function Last     (Container : List) return Element_Access;

   function Next
     (Container : List;
      Item      : Element_Access) return Element_Access;

   function Iterate
     (Container : in List;
      Next      : access Element_Access) return Boolean;

   generic
      with function "=" (Left, Right : Element_Type) return Boolean is <>;
   package Generic_Search is
      function "="      (Left, Right : List) return Boolean;

      function Find
        (Container : List;
         Item      : Element_Type;
         After     : Element_Access := null)
        return Element_Access;

      function Contains
        (Container : List;
         Item      : Element_Type) return Boolean;
   end Generic_Search;

   --  Call procedure Proc for each item in the list
   generic
      with procedure Proc (Item : in Element_Access);
   procedure For_Each (Container : in List);

   --  Call procedure Proc for each item in the list with parameter
   generic
      type Parameter (<>) is limited private;
      with procedure Proc (Item  : in     Element_Access;
                           Param : in out Parameter);
   procedure For_Each_With_Param
     (Container : in     List;
      Param     : in out Parameter);

   --  Conversion to array of pointer

   generic
      type Index is range <>;
      type Access_Array is array (Index range <>) of Element_Access;
   function To_Array (Container : List) return Access_Array;

   generic
      type Index is range <>;
      type Access_Array is array (Index range <>) of Element_Access;
      with function Agree (Item : in Element_Access) return Boolean;
   function Agreed_To_Array (Container : List) return Access_Array;

   generic
      type Index is range <>;
      type Access_Array is array (Index range <>) of Element_Access;
      type Parameter (<>) is limited private;
      with function Agree (Item  : in Element_Access;
                           Param : in Parameter)
                          return Boolean;
   function Agreed_To_Array_With_Param
     (Container : List;
      Param : Parameter)
      return Access_Array;

private
   type List is record
      Tail : Element_Access;
      --  Head = Get_Next (Tail)
   end record;

--   head         tail <- List
--     *-->*-->*-->*-+
--     ^             |
--     |             |
--     +-------------+

   Empty_List : constant List := (Tail => null);

   pragma Inline (Is_Empty);
   pragma Inline (Insert_After);
   pragma Inline (Append);
   pragma Inline (Prepend);
   pragma Inline (Delete_Next);
   pragma Inline (Delete_First);
   pragma Inline (Splice_After);
   pragma Inline (First);
   pragma Inline (Last);
   pragma Inline (Next);
   pragma Inline (Iterate);

end Gela.Embeded_Links.Lists;


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
