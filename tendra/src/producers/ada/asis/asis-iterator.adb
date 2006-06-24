------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $
--  Purpose:
--  Read-only iterator over tree of ASIS elements

with Asis.Gela;
with Asis.Gela.Base_Lists;

package body Asis.Iterator is

   ----------------------
   -- Traverse_Element --
   ----------------------

   procedure Traverse_Element
     (Element : in     Asis.Element;
      Control : in out Traverse_Control;
      State   : in out State_Information)
   is

      procedure Walk_List
        (Element : in     Asis.Element;
         Control : in out Traverse_Control;
         State   : in out State_Information)
      is
         use Asis.Gela.Base_Lists;
         List : constant Primary_Base_List := Primary_Base_List (Element);
         Item : Asis.Element;
      begin
         for I in 1 .. Length (List.all) loop
            Item := Get_Item (List, I);

            Traverse_Element (Item, Control, State);

            exit when Control /= Continue;
         end loop;
      end Walk_List;

   begin
      Check_Nil_Element (Element, "Traverse_Element");

      if Control /= Continue then
         return;
      end if;

      declare
         Children : constant Traverse_List := Asis.Children (Element);
      begin
         Pre_Operation (Element, Control, State);

         if Control = Continue then
            for I in Children'Range loop
               if Children (I).Is_List and then
                 Assigned (Children (I).List)
               then

                  Walk_List (Children (I).List, Control, State);

               elsif not Children (I).Is_List and then
                 Assigned (Children (I).Item.all)
               then

                  Traverse_Element (Children (I).Item.all, Control, State);

               end if;

               exit when Control /= Continue;
            end loop;

            if Control = Abandon_Siblings then
               Control := Continue;
            end if;
         end if;

         if Control = Continue then
            Post_Operation (Element, Control, State);
         end if;

         if Control = Abandon_Children then
            Control := Continue;
         end if;
      end;
   end Traverse_Element;

end Asis.Iterator;



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
