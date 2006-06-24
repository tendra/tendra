package body Gela.Embeded_Links.Lists is

   ---------------------
   -- Agreed_To_Array --
   ---------------------

   function Agreed_To_Array (Container : List) return Access_Array is
      Count : Index'Base := 0;
      Next  : aliased Element_Access;
   begin
      while Iterate (Container, Next'Access) loop
         if Agree (Next) then
            Count := Count + 1;
         end if;
      end loop;

      declare
         Vector : Access_Array (1 .. Count);
      begin
         Count := 0;

         while Iterate (Container, Next'Access) loop
            if Agree (Next) then
               Count := Count + 1;
               Vector (Count) := Next;
            end if;
         end loop;

         return Vector;
      end;
   end Agreed_To_Array;

   --------------------------------
   -- Agreed_To_Array_With_Param --
   --------------------------------

   function Agreed_To_Array_With_Param
     (Container : List;
      Param : Parameter)
      return Access_Array
   is
      Count : Index'Base := 0;
      Next  : aliased Element_Access;
   begin
      while Iterate (Container, Next'Access) loop
         if Agree (Next, Param) then
            Count := Count + 1;
         end if;
      end loop;

      declare
         Vector : Access_Array (1 .. Count);
      begin
         Count := 0;

         while Iterate (Container, Next'Access) loop
            Count := Count + 1;

            if Agree (Next, Param) then
               Count := Count + 1;
               Vector (Count) := Next;
            end if;
         end loop;

         return Vector;
      end;
   end Agreed_To_Array_With_Param;

   ------------
   -- Append --
   ------------

   procedure Append
     (Container : in out List;
      New_Item  : in     Element_Access) is
   begin
      pragma Assert (Get_Next (New_Item) = null);
      Prepend (Container, New_Item);
      Container.Tail := New_Item;
   end Append;

   -----------
   -- Clear --
   -----------

   procedure Clear (Container : in out List) is
      Next  : aliased Element_Access;
      Prev  : Element_Access := Last (Container);
   begin
      while Iterate (Container, Next'Access) loop
         Set_Next (Prev, null);
         Prev := Next;
      end loop;

      Container.Tail := null;
   end Clear;

   ------------
   -- Delete --
   ------------

   procedure Delete
     (Container : in out List;
      Item      : in     Element_Access)
   is
      Prev  : Element_Access := First (Container);
      Next  : aliased Element_Access := Prev;
   begin
      pragma Assert (Get_Next (Item) = null);

      if Item = Prev then
         Delete_First (Container, Prev);
      else
         while Iterate (Container, Next'Access) loop
            if Next = Item then
               Delete_Next (Container, Prev, Next);
               return;
            else
               Prev := Next;
            end if;
         end loop;
      end if;
   end Delete;

   ------------------
   -- Delete_First --
   ------------------

   procedure Delete_First
     (Container : in out List;
      Removed   :    out Element_Access)
   is
   begin
      if Is_Empty (Container) then
         Removed := null;
         return;
      end if;

      Removed := First (Container);

      if Removed = Last (Container) then
         Container.Tail := null;
      else
         Set_Next (Last (Container), Get_Next (Removed));
      end if;

      Set_Next (Removed, null);
   end Delete_First;

   -----------------
   -- Delete_Next --
   -----------------

   procedure Delete_Next
     (Container : in out List;
      After     : in     Element_Access;
      Removed   :    out Element_Access)
   is
   begin
      pragma Assert (Get_Next (After) /= null);

      if After /= Last (Container) then
         Removed := Get_Next (After);
         Set_Next (After, Get_Next (Removed));

         if Removed = Last (Container) then
            Container.Tail := After;
         end if;
      else
         Removed := null;
      end if;
   end Delete_Next;

   -----------
   -- First --
   -----------

   function First (Container : List) return Element_Access is
   begin
      return Get_Next (Container.Tail);
   end First;

   --------------
   -- For_Each --
   --------------

   procedure For_Each (Container : in List) is
      Next  : aliased Element_Access;
   begin
      while Iterate (Container, Next'Access) loop
         Proc (Next);
      end loop;
   end For_Each;

   -------------------------
   -- For_Each_With_Param --
   -------------------------

   procedure For_Each_With_Param
     (Container : in     List;
      Param     : in out Parameter)
   is
      Next  : aliased Element_Access;
   begin
      while Iterate (Container, Next'Access) loop
         Proc (Next, Param);
      end loop;
   end For_Each_With_Param;

   --------------------
   -- Generic_Search --
   --------------------

   package body Generic_Search is

      ---------
      -- "=" --
      ---------

      function "=" (Left, Right : List) return Boolean is
         Left_Item  : aliased Element_Access;
         Right_Item : aliased Element_Access;
      begin
         while Iterate (Left, Left_Item'Access)
           and then Iterate (Right, Right_Item'Access)
         loop
            if Left_Item.all /= Right_Item.all then
               return False;
            end if;
         end loop;

         return Left_Item = null and then Right_Item = null;
      end "=";

      --------------
      -- Contains --
      --------------

      function Contains
        (Container : List;
         Item      : Element_Type)
         return Boolean
      is
         Next  : aliased Element_Access;
      begin
         while Iterate (Container, Next'Access) loop
            if Next.all = Item then
               return True;
            end if;
         end loop;

         return False;
      end Contains;

      ----------
      -- Find --
      ----------

      function Find
        (Container : List;
         Item      : Element_Type;
         After     : Element_Access := null)
         return Element_Access
      is
         Next  : aliased Element_Access := After;
      begin
         pragma Assert (After = null or else Get_Next (After) /= null);

         while Iterate (Container, Next'Access) loop
            if Next.all = Item then
               return Next;
            end if;
         end loop;

         return null;
      end Find;

   end Generic_Search;

   ------------------
   -- Insert_After --
   ------------------

   procedure Insert_After
     (Container : in out List;
      After     : in     Element_Access;
      New_Item  : in     Element_Access)
   is
   begin
      pragma Assert (Get_Next (After) /= null and Get_Next (New_Item) = null);

      Set_Next (New_Item, Get_Next (After));
      Set_Next (After, New_Item);

      if Container.Tail = After then
         Container.Tail := New_Item;
      end if;
   end Insert_After;

   --------------
   -- Is_Empty --
   --------------

   function Is_Empty (Container : List) return Boolean is
   begin
      return Container.Tail = null;
   end Is_Empty;

   -------------
   -- Iterate --
   -------------

   function Iterate
     (Container : in List;
      Next      : access Element_Access)
      return Boolean
   is
   begin
      pragma Assert (Next.all = null or else Get_Next (Next.all) /= null);

      if Is_Empty (Container) or Next.all = Last (Container) then
         Next.all := null;
         return False;
      elsif Next.all = null then
         Next.all := First (Container);
         return True;
      else
         Next.all := Get_Next (Next.all);
         return True;
      end if;
   end Iterate;

   ----------
   -- Last --
   ----------

   function Last (Container : List) return Element_Access is
   begin
      return Container.Tail;
   end Last;

   ------------
   -- Length --
   ------------

   function Length (Container : List) return Natural is
      Result : Natural := 0;
      Next   : aliased Element_Access;
   begin
      while Iterate (Container, Next'Access) loop
         Result := Result + 1;
      end loop;

      return Result;
   end Length;

   ----------
   -- Next --
   ----------

   function Next
     (Container : List;
      Item      : Element_Access)
      return Element_Access
   is
   begin
      pragma Assert (Item /= null and Get_Next (Item) /= null);

      if Item = Last (Container) then
         return null;
      else
         return Get_Next (Item);
      end if;
   end Next;

   -------------
   -- Prepend --
   -------------

   procedure Prepend
     (Container : in out List;
      New_Item  : in     Element_Access)
   is
   begin
      pragma Assert (Get_Next (New_Item) = null);

      if Is_Empty (Container) then
         Container.Tail := New_Item;
         Set_Next (New_Item, New_Item);
      else
         Set_Next (New_Item, Get_Next (Container.Tail));
         Set_Next (Container.Tail, New_Item);
      end if;
   end Prepend;

   ------------------
   -- Splice_After --
   ------------------

   procedure Splice_After
     (Target   : in out List;
      Source   : in out List;
      After    : in     Element_Access := null)
   is
      Last : Element_Access;
   begin
      if Is_Empty (Source) then
         return;
      elsif Is_Empty (Target) then
         Target.Tail := Source.Tail;
      else
         if After = null then
            Last := After;
         else
            Last := Target.Tail;
         end if;

         Set_Next (Source.Tail, Get_Next (Last));
         Set_Next (Last, Source.Tail);

         if Last = Target.Tail then
            Target.Tail := Source.Tail;
         end if;
      end if;

      Source.Tail := null;
   end Splice_After;

   --------------
   -- To_Array --
   --------------

   function To_Array (Container : List) return Access_Array is
      Count  : Index'Base := Index'Base (Length (Container));
      Next   : aliased Element_Access;
      Vector : Access_Array (1 .. Count);
   begin
      Count := 0;

      while Iterate (Container, Next'Access) loop
         Count := Count + 1;
         Vector (Count) := Next;
      end loop;

      return Vector;
   end To_Array;

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
