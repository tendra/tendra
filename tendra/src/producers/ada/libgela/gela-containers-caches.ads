with Gela.Embeded_Links.Caches;

generic
   type Element is private;
   type Hash_Type is range <>;

   with function Hash (Item : Element) return Hash_Type is <>;
   with function "=" (Left, Right : Element) return Boolean is <>;

package Gela.Containers.Caches is

   type Cache (Size : Hash_Type) is limited private;

   function Preferred_Size (Size : Hash_Type) return Hash_Type;

   procedure Add
     (Container : in out Cache;
      Object    : in     Element);

   procedure Remove
     (Container : in out Cache;
      Object    : in     Element);

   procedure Find
     (Container : in out Cache;
      Object    : in out Element;
      Found     :    out Boolean;
      Touch     : in     Boolean := True);

private

   type Node;
   type Node_Access is access all Node;

   type Node is record
      Next_Hash : Node_Access;
      Next      : Node_Access;
      Prev      : Node_Access;
      Data      : Element;
   end record;

   function Hash (Object : Node) return Hash_Type;

   function  Get_Next_Hash (Item : Node_Access) return Node_Access;
   procedure Set_Next_Hash (Item, Next : Node_Access);
   function  Get_Next      (Item : Node_Access) return Node_Access;
   procedure Set_Next      (Item, Next : Node_Access);
   function  Get_Prev      (Item : Node_Access) return Node_Access;
   procedure Set_Prev      (Item, Prev : Node_Access);
   function "=" (Left, Right : Node) return Boolean;

   pragma Inline (Hash);
   pragma Inline (Get_Next_Hash);
   pragma Inline (Set_Next_Hash);
   pragma Inline (Get_Next);
   pragma Inline (Set_Next);
   pragma Inline (Get_Prev);
   pragma Inline (Set_Prev);
   pragma Inline ("=");

   package EL_Caches is
      new Gela.Embeded_Links.Caches (Node, Node_Access, Hash_Type);

   type Cache (Size : Hash_Type) is record
      Data : EL_Caches.Cache (Size);
      Free : Node_Access;
   end record;

end Gela.Containers.Caches;


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
