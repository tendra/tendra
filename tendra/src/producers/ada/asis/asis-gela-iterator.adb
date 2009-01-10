------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$:

with Asis.Gela.Base_Lists;           use Asis.Gela.Base_Lists;

package body Asis.Gela.Iterator is

   procedure Real_Walk_Element
     (Element   : in out Asis.Element;
      Control   : in out Traverse_Control;
      State     : in out State_Information;
      Read_Only : in     Boolean);

   procedure Walk_List
     (List      : access Primary_Base_List_Node'Class;
      Control   : in out Traverse_Control;
      State     : in out State_Information;
      Read_Only : in     Boolean);

   ------------------
   -- Walk_Element --
   ------------------

   procedure Walk_Element
     (Element : in     Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information)
   is
      Store : Asis.Element := Element;
   begin
      Check_Nil_Element (Element, "Walk_Element");
      Real_Walk_Element (Store, Control, State, True);
      pragma Assert (Is_Equal (Store, Element));
   end Walk_Element;

   ------------------
   -- Walk_Element --
   ------------------

   procedure Walk_Element
     (Element   : in out Asis.Element;
      Control   : in out Traverse_Control;
      State     : in out State_Information;
      Read_Only : in     Boolean)
   is
   begin
      Check_Nil_Element (Element, "Walk_Element");
      Real_Walk_Element (Element, Control, State, Read_Only);
   end Walk_Element;

   ---------------------------
   -- Walk_Element_And_Free --
   ---------------------------

   procedure Walk_Element_And_Free
     (Element : in out Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information)
   is
      --  Store : Asis.Element := Element;
   begin
      Check_Nil_Element (Element, "Walk_Element_And_Free");
      Real_Walk_Element (Element, Control, State, False);
      --  if not Is_Equal (Store, Element) then
      --     Free (Store);
      --  end if;
   end Walk_Element_And_Free;

   ---------------
   -- Walk_List --
   ---------------

   procedure Walk_List
     (List      : access Primary_Base_List_Node'Class;
      Control   : in out Traverse_Control;
      State     : in out State_Information;
      Read_Only : in     Boolean)
   is
      Element : Asis.Element;
      Store   : Asis.Element;
   begin
      pragma Assert (Control = Continue);

      for I in 1 .. Length (List.all) loop
         Element := Get_Item (List, I);
         Store := Element;
         Real_Walk_Element (Element, Control, State, Read_Only);

         if not Read_Only
           and then not Is_Equal (Store, Element)
         then
            if Assigned (Element) then
               Add_After (List.all, Store, Element);
            end if;
            Remove (List.all, Store);
            --  Free (Store);
         end if;

         exit when Control /= Continue;
      end loop;
   end Walk_List;

   -----------------------
   -- Real_Walk_Element --
   -----------------------

   procedure Real_Walk_Element
     (Element   : in out Asis.Element;
      Control   : in out Traverse_Control;
      State     : in out State_Information;
      Read_Only : in     Boolean)
   is
   begin
      if not Assigned (Element) or Control /= Continue then
         return;
      end if;

      Pre_Operation (Element, Control, State);
      pragma Assert (Assigned (Element) or Control = Abandon_Children);

      if Control = Continue then
         declare
            Children : constant Traverse_List := Asis.Children (Element);
            Store    : Asis.Element;
         begin
            for I in Children'Range loop
               if Children (I).Is_List and then
                 Assigned (Children (I).List)
               then

                  Walk_List (Primary_Base_List (Children (I).List),
                             Control, State, Read_Only);

               elsif not Children (I).Is_List and then
                 Assigned (Children (I).Item.all)
               then

                  Store := Children (I).Item.all;
                  Real_Walk_Element (Children (I).Item.all,
                                     Control, State, Read_Only);

                  if not Read_Only
                    and then not Is_Equal (Store, Children (I).Item.all)
                  then
                     null;
                     --  Free (Store);
                  end if;
               end if;

               exit when Control /= Continue;
            end loop;
         end;
      end if;

      if Control = Abandon_Siblings then
         Control := Continue;
      end if;

      if Control = Continue then
         Post_Operation (Element, Control, State);
      end if;

      if Control = Abandon_Children then
         Control := Continue;
      end if;
   end Real_Walk_Element;

end Asis.Gela.Iterator;



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
