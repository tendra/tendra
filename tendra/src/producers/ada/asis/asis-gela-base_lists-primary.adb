------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$:

package body Asis.Gela.Base_Lists.Primary is

   ---------
   -- Add --
   ---------

   procedure Add
     (Container : in out List_Node;
      Item      : in     Element) is
   begin
      Check_Item_Kind (Item, Allowed);
      Add (Primary_Base_List_Node (Container), Item);
   end Add;

   ---------------
   -- Add_After --
   ---------------

   procedure Add_After
     (Container : in out List_Node;
      Target    : in     Element;
      Item      : in     Element) is
   begin
      Check_Item_Kind (Item, Allowed);
      Add_After (Primary_Base_List_Node (Container), Target, Item);
   end Add_After;

   -------------
   -- Destroy --
   -------------

   procedure Destroy (Item : in out List) is
   begin
      ER_Element_Lists.Clear (Item.Content);
   end Destroy;

   ---------------
   -- Deep_Copy --
   ---------------

   function Deep_Copy
     (Items  : in Asis.Element_List;
      Cloner : in Cloner_Class;
      Parent : in Asis.Element) return Asis.Element
   is
      Result : constant List := new List_Node;
      Item   : Asis.Element;
   begin
      for I in Items'Range loop
         Item := Asis.Copy (Cloner, Items (I), Parent);

         if Assigned (Item) then
            Add (Result.all, Item);
         end if;
      end loop;

      return Asis.Element (Result);
   end Deep_Copy;

   ---------------------
   -- To_Element_List --
   ---------------------

   function To_Element_List
     (Item            : List;
      Include_Pragmas : Boolean)
     return Asis.Element_List
   is
   begin
      if Item = null then
         return Nil_Element_List;
      else
         return To_Element_List (Item.all, Include_Pragmas);
      end if;
   end To_Element_List;

   ------------------------------
   -- To_Compilation_Unit_List --
   ------------------------------

   function To_Compilation_Unit_List
     (Item : List)
     return Asis.Compilation_Unit_List
   is
   begin
      if Item = null then
         return Nil_Compilation_Unit_List;
      else
         return To_Compilation_Unit_List (Item.all);
      end if;
   end To_Compilation_Unit_List;

end Asis.Gela.Base_Lists.Primary;


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
