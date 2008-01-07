package body Gela.Embeded_Links.Double_Lists is

   package S renames Simple_Lists;
   subtype L is Simple_Lists.List;

   ------------
   -- Append --
   ------------

   procedure Append
     (Container : in out List;
      New_Item  : in     Element_Access)
   is
   begin
      Set_Prev (New_Item, Last (Container));
      S.Append (L (Container), New_Item);
   end Append;

   -----------
   -- Clear --
   -----------

   procedure Clear (Container : in out List) is
      Next  : aliased Element_Access;
   begin
      while Iterate (Container, Next'Access) loop
         Set_Prev (Next, null);
      end loop;

      S.Clear (L (Container));
   end Clear;

   ------------
   -- Delete --
   ------------

   procedure Delete
     (Container : in out List;
      Item      : in     Element_Access)
   is
      Ignore : Element_Access;
   begin
      if Item = First (Container) then
         Delete_First (Container, Ignore);
      else
         Delete_Next (Container, Get_Prev (Item), Ignore);
      end if;

      Set_Prev (Item, null);
   end Delete;

   ------------------
   -- Delete_First --
   ------------------

   procedure Delete_First
     (Container : in out List;
      Removed   :    out Element_Access)
   is
   begin
      S.Delete_First (L (Container), Removed);

      if Removed /= null then
         Set_Prev (Removed, null);
      end if;

      if First (Container) /= null then
         Set_Prev (First (Container), null);
      end if;
   end Delete_First;

   -----------------
   -- Delete_Last --
   -----------------

   procedure Delete_Last
     (Container : in out List;
      Removed   :    out Element_Access)
   is
   begin
      if Is_Empty (Container) then
         Removed := null;
      elsif Last (Container) = First (Container) then
         Delete_First (Container, Removed);
      else
         Delete_Next (Container, Get_Prev (Last (Container)), Removed);
      end if;
   end Delete_Last;

   -----------------
   -- Delete_Next --
   -----------------

   procedure Delete_Next
     (Container : in out List;
      After     : in     Element_Access;
      Removed   :    out Element_Access)
   is
   begin
      S.Delete_Next (L (Container), After, Removed);

      if Removed /= null then
         if After /= Last (Container) then
            Set_Prev (Get_Next (After), Get_Prev (Removed));
         end if;

         Set_Prev (Removed, null);
      end if;
   end Delete_Next;

   ------------
   -- Insert --
   ------------

   procedure Insert
     (Container : in out List;
      Before    : in     Element_Access;
      New_Item  : in     Element_Access)
   is
   begin
      if Before = First (Container) then
         Prepend (Container, New_Item);
      else
         S.Insert_After (L (Container), Get_Prev (Before), New_Item);
      end if;
   end Insert;

   ------------------
   -- Insert_After --
   ------------------

   procedure Insert_After
     (Container : in out List;
      After     : in     Element_Access;
      New_Item  : in     Element_Access)
   is
   begin
      S.Insert_After (L (Container), After, New_Item);
      Set_Prev (New_Item, After);
   end Insert_After;

   -------------
   -- Prepend --
   -------------

   procedure Prepend
     (Container : in out List;
      New_Item  : in     Element_Access)
   is
      Head : constant Element_Access := First (Container);
   begin
      if Head /= null then
         Set_Prev (Head, New_Item);
      end if;

      S.Prepend (L (Container), New_Item);
   end Prepend;

   ------------------
   -- Splice_After --
   ------------------

   procedure Splice_After
     (Target   : in out List;
      Source   : in out List;
      After    : in     Element_Access := null)
   is
      Head : constant Element_Access := First (Source);
   begin
      if Head /= null then
         Set_Prev (Head, Last (Target));
      end if;

      S.Splice_After (L (Target), L (Source), After);
   end Splice_After;

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
