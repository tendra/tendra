with Ada.Unchecked_Deallocation;

package body Gela.Containers.Caches is

   ---------
   -- "=" --
   ---------

   function "=" (Left, Right : Node) return Boolean is
   begin
      return Left.Data = Right.Data;
   end "=";

   ---------
   -- Add --
   ---------

   procedure Add
     (Container : in out Cache;
      Object    : in     Element)
   is
      Added : Node_Access;
   begin
      if Container.Free = null then
         Added := new Node;
      else
         Added := Container.Free;
      end if;

      Added.Data := Object;

      EL_Caches.Add (Container.Data, Added, Container.Free);
   end Add;

   ----------
   -- Find --
   ----------

   procedure Find
     (Container : in out Cache;
      Object    : in out Element;
      Found     :    out Boolean;
      Touch     : in     Boolean := True)
   is
      Target  : Node;
      Removed : Node_Access;
   begin
      Target.Data := Object;
      EL_Caches.Find (Container.Data, Target, Removed, Touch);

      if Removed /= null then
         Found := True;
         Object := Removed.Data;
      else
         Found := False;
      end if;
   end Find;

   --------------
   -- Get_Next --
   --------------

   function Get_Next (Item : Node_Access) return Node_Access is
   begin
      return Item.Next;
   end Get_Next;

   -------------------
   -- Get_Next_Hash --
   -------------------

   function Get_Next_Hash (Item : Node_Access) return Node_Access is
   begin
      return Item.Next_Hash;
   end Get_Next_Hash;

   --------------
   -- Get_Prev --
   --------------

   function Get_Prev (Item : Node_Access) return Node_Access is
   begin
      return Item.Prev;
   end Get_Prev;

   ----------
   -- Hash --
   ----------

   function Hash (Object : Node) return Hash_Type is
   begin
      return Hash (Object.Data);
   end Hash;

   --------------------
   -- Preferred_Size --
   --------------------

   function Preferred_Size (Size : Hash_Type) return Hash_Type is
   begin
      return EL_Caches.Preferred_Size (Size);
   end Preferred_Size;

   ------------
   -- Remove --
   ------------

   procedure Remove
     (Container : in out Cache;
      Object    : in     Element)
   is
      procedure Free is
         new Ada.Unchecked_Deallocation (Node, Node_Access);

      Target  : Node;
      Removed : Node_Access;
   begin
      Target.Data := Object;
      EL_Caches.Find (Container.Data, Target, Removed, False);

      if Removed /= null then
         EL_Caches.Remove (Container.Data, Removed);

         if Container.Free = null then
            Container.Free := Removed;
         else
            Free (Removed);
         end if;
      end if;
   end Remove;

   --------------
   -- Set_Next --
   --------------

   procedure Set_Next (Item, Next : Node_Access) is
   begin
      Item.Next := Next;
   end Set_Next;

   -------------------
   -- Set_Next_Hash --
   -------------------

   procedure Set_Next_Hash (Item, Next : Node_Access) is
   begin
      Item.Next_Hash := Next;
   end Set_Next_Hash;

   --------------
   -- Set_Prev --
   --------------

   procedure Set_Prev (Item, Prev : Node_Access) is
   begin
      Item.Prev := Prev;
   end Set_Prev;

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
