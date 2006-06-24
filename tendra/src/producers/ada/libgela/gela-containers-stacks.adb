with Ada.Unchecked_Deallocation;

package body Gela.Containers.Stacks is
   procedure Free is new  Ada.Unchecked_Deallocation (Node, Node_Access);

   -----------
   -- Clear --
   -----------

   procedure Clear (Container : in out Stack) is
      Next : Node_Access;
   begin
      while not Is_Empty (Container) loop
         Delete_First (Container, Next);
         Free (Next);
      end loop;
   end Clear;

   --------------
   -- Get_Next --
   --------------

   function Get_Next (Item : Node_Access) return Node_Access is
   begin
      return Item.Next;
   end Get_Next;

   --------------
   -- Is_Empty --
   --------------

   function Is_Empty (Container : Stack) return Boolean is
   begin
      return E.Is_Empty (E.List (Container));
   end Is_Empty;

   ------------
   -- Length --
   ------------

   function Length (Container : Stack) return Natural is
   begin
      return E.Length (E.List (Container));
   end Length;

   ---------
   -- Pop --
   ---------

   procedure Pop
     (Container : in out Stack;
      Item      :    out Element_Type)
   is
      Next : Node_Access;
   begin
      Delete_First (Container, Next);
      Item := Next.Data;
      Free (Next);
   end Pop;

   ---------
   -- Pop --
   ---------

   procedure Pop   (Container : in out Stack) is
      Ignore : Element_Type;
   begin
      Pop (Container, Ignore);
   end Pop;

   ----------
   -- Push --
   ----------

   procedure Push
     (Container : in out Stack;
      Item      : in     Element_Type)
   is
   begin
      Prepend (Container, new Node'(null, Item));
   end Push;

   --------------
   -- Set_Next --
   --------------

   procedure Set_Next (Item, Next : Node_Access) is
   begin
      Item.Next := Next;
   end Set_Next;

   ---------
   -- Top --
   ---------

   function Top (Container : Stack) return Element_Type is
   begin
      return First (Container).Data;
   end Top;

end Gela.Containers.Stacks;


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
