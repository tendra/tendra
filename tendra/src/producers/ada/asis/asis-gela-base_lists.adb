with Asis.Errors;
with Asis.Exceptions;
with Asis.Implementation;

package body Asis.Gela.Base_Lists is

   function Is_Pragma (Item : Asis.Element) return Boolean;

   ---------
   -- Add --
   ---------

   procedure Add
     (Container : in out Primary_Base_List_Node;
      Item      : in     Element)
   is
      use ER_Element_Lists;

      Item_Pos : constant Text_Position := End_Position (Item.all);
      List_Pos : Text_Position;
   begin
      if Length (Container) > 0 then
         List_Pos := Start_Position (First (Container.Content).all);
      else
         List_Pos := Start_Position (Container);
      end if;

      Set_Start_Position (Container, Start_Position (Item.all));
      Set_End_Position (Container, End_Position (Item.all));

      if List_Pos < Item_Pos or else Item_Pos = Nil_Text_Position Then
         Append (Container.Content, Item);
      else
         Prepend (Container.Content, Item);
      end if;

      Container.Last_Index := 0;
      Container.Length     := Container.Length + 1;
   end Add;

   ---------------
   -- Add_After --
   ---------------

   procedure Add_After
     (Container : in out Primary_Base_List_Node;
      Target    : in     Element;
      Item      : in     Element)
   is
      use ER_Element_Lists;
   begin
      Set_Start_Position (Container, Start_Position (Item.all));
      Set_End_Position (Container, End_Position (Item.all));

      if not Assigned (Target) then
         Prepend (Container.Content, Item);
      else
         Insert_After (Container.Content, Target, Item);
      end if;

      Container.Last_Index := 0;
      Container.Length     := Container.Length + 1;
   end Add_After;

   ---------------------
   -- Check_Item_Kind --
   ---------------------

   procedure Check_Item_Kind
      (Item    : in Element;
       Allowed : in Element_Kind_List)
   is
      Kind : constant Element_Kinds := Element_Kind (Item.all);
   begin
      for I in Allowed'Range loop
         if Kind = Allowed (I) then
            return;
         end if;
      end loop;

      Implementation.Set_Status
        (Asis.Errors.Internal_Error,
         "Check_Item_Kind: " & Element_Kinds'Wide_Image (Kind));

      raise Exceptions.ASIS_Inappropriate_Element;
   end Check_Item_Kind;

   -----------
   -- Clone --
   -----------

   function Clone
     (Item   : Primary_Base_List_Node;
      Parent : Asis.Element) return Asis.Element is
   begin
      return Asis.Nil_Element;
   end Clone;

   ------------------
   -- Element_Kind --
   ------------------

   function Element_Kind
     (Element : in Primary_Base_List_Node)
      return Element_Kinds
   is
   begin
      return Not_An_Element;
   end Element_Kind;

   ------------------
   -- End_Position --
   ------------------

   function End_Position
     (Element : Primary_Base_List_Node)
      return Text_Position
   is
      use ER_Element_Lists;
   begin
      return Element.End_Position;
   end End_Position;

   ----------
   -- Find --
   ----------

   function Find
     (Container : Primary_Base_List_Node;
      Item      : Element)
      return Boolean
   is
      use ER_Element_Lists;
      Next : aliased Asis.Element;
   begin
      while Iterate (Container.Content, Next'Access) loop
         if Is_Equal (Next, Item) then
            return True;
         end if;
      end loop;

      return False;
   end Find;

   --------------
   -- Get_Item --
   --------------

   function Get_Item
     (Item  : access Primary_Base_List_Node;
      Index : Positive)
      return Element
   is
      use ER_Element_Lists;
   begin
      if Index not in 1 .. Item.Length then
         raise Constraint_Error;
      elsif Item.Last_Index = 0 then
         Item.Last_Index := 1;
         Item.Last_Item  := First (Item.Content);
      end if;

      loop
         if Item.Last_Index = Index then
            return Item.Last_Item;
         elsif Item.Last_Index = Item.Length then
            Item.Last_Index := 1;
            Item.Last_Item  := First (Item.Content);
         else
            Item.Last_Index := Item.Last_Index + 1;
            Item.Last_Item := Get_Next (Item.Last_Item);
         end if;
      end loop;

      return Nil_Element;
   end Get_Item;

   --------------
   -- Get_Next --
   --------------

   function Get_Next (Item : Element) return Element is
   begin
      return Next_Element (Item.all);
   end Get_Next;

   --------------
   -- Get_Next --
   --------------

   function Get_Next
     (Item : Primary_Base_List_Node)
      return Element
   is
   begin
      return Nil_Element;
   end Get_Next;

   -------------
   -- Is_List --
   -------------

   function Is_List (Item : Primary_Base_List_Node) return Boolean is
   begin
      return True;
   end Is_List;

   ---------------
   -- Is_Pragma --
   ---------------

   function Is_Pragma (Item : Asis.Element) return Boolean is
   begin
      return Element_Kind (Item.all) = A_Pragma;
   end Is_Pragma;

   ------------
   -- Length --
   ------------

   function Length
     (Item : Primary_Base_List_Node)
      return Natural
   is
   begin
      return Item.Length;
   end Length;

   ------------
   -- Remove --
   ------------

   procedure Remove
     (Container : in out Primary_Base_List_Node;
      Item      : in     Element)
   is
   begin
      ER_Element_Lists.Delete (Container.Content, Item);
      Container.Last_Index := 0;
      Container.Length     := Container.Length - 1;
   end Remove;

   ---------------------
   -- Secondary_Lists --
   ---------------------

   package body Secondary_Lists is

      ---------
      -- Add --
      ---------

      procedure Add
        (Container : in out List_Node;
         Item      : in     Element)
      is
         use Element_Lists;
         Item_Pos : constant Text_Position := Start_Position (Item.all);
      begin
         Check_Item_Kind (Item, Allowed);
         if Is_Empty (Container)
           or else End_Position (Last_Element (Container).all) < Item_Pos
         then
            Append (List (Container), Item);
         else
            Prepend (List (Container), Item);
         end if;
      end Add;

      ---------
      -- Get --
      ---------

      function Get
        (Item  : List_Node;
         Index : Positive)
        return Asis.Element
      is
         use Element_Lists;
         Ptr : Cursor := First (Item);
      begin
         for J in 2 .. Index loop
            Ptr := Next (Ptr);
         end loop;

         return Element_Lists.Element (Ptr);
      end Get;

      ------------
      -- Length --
      ------------

      function Length (Item : List_Node) return Natural is
         use Element_Lists;
         Result : Natural := 0;
         Ptr    : Cursor := First (Item);
      begin
         while Has_Element (Ptr) loop
            Result := Result + 1;
            Ptr    := Next (Ptr);
         end loop;

         return Result;
      end Length;

      ------------
      -- Remove --
      ------------

      procedure Remove
        (Container : in out List_Node;
         Item      : in     Element)
      is
         use Element_Lists;
         Ptr : Cursor := Find (Container, Item);
      begin
         if Has_Element (Ptr) then
            Delete (Container, Ptr);
         end if;
      end Remove;

      ---------
      -- Set --
      ---------

      procedure Set
        (Container : in out List_Node;
         Items     : in     Element_List)
      is
      begin
         Clear (Container);
         for I in Items'Range loop
            Add (Container, Items (I));
         end loop;
      end Set;

      ------------------------------
      -- To_Compilation_Unit_List --
      ------------------------------

      function To_Compilation_Unit_List
        (Item : List_Node)
         return Asis.Compilation_Unit_List
      is
         List   : constant Asis.Element_List := To_Element_List (Item);
         Result : Compilation_Unit_List (List'Range);
      begin
         for I in List'Range loop
            Result (I) := Compilation_Unit (List (I));
         end loop;

         return Result;
      end To_Compilation_Unit_List;

      ---------------------
      -- To_Element_List --
      ---------------------

      function To_Element_List
        (Item : List_Node)
         return Asis.Element_List
      is
      begin
         return To_Element_List (Item, True);
      end To_Element_List;

      ---------------------
      -- To_Element_List --
      ---------------------

      function To_Element_List
        (Item            : List_Node;
         Include_Pragmas : Boolean)
         return Asis.Element_List
      is
         use Element_Lists;
         Result : Asis.Element_List (1 .. ASIS_Natural (Length (Item)));
         Index  : ASIS_Natural := 0;
         Temp   : Asis.Element;
         Ptr    : Cursor := First (Item);
      begin
         while Has_Element (Ptr) loop
            Temp := Element_Lists.Element (Ptr);

            if Include_Pragmas or else not Is_Pragma (Temp) then
               Index          := Index + 1;
               Result (Index) := Temp;
            end if;

            Ptr := Next (Ptr);
         end loop;

         return Result (1 .. Index);
      end To_Element_List;

      --------------------
      -- To_Pragma_List --
      --------------------

      function To_Pragma_List
        (Item : List_Node)
         return Asis.Element_List
      is
         use Element_Lists;
         Result : Asis.Element_List (1 .. ASIS_Natural (Length (Item)));
         Index  : ASIS_Natural := 0;
         Temp   : Asis.Element;
         Ptr    : Cursor := First (Item);
      begin
         while Has_Element (Ptr) loop
            Temp := Element_Lists.Element (Ptr);

            if Is_Pragma (Temp) then
               Index          := Index + 1;
               Result (Index) := Temp;
            end if;

            Ptr := Next (Ptr);
         end loop;

         return Result (1 .. Index);
      end To_Pragma_List;

   end Secondary_Lists;

   --------------
   -- Set_Next --
   --------------

   procedure Set_Next (Item, Next : Element) is
   begin
      Set_Next_Element (Item.all, Next);
   end Set_Next;

   --------------
   -- Set_Next --
   --------------

   procedure Set_Next
     (Item : in out Primary_Base_List_Node;
      Next : in     Element)
   is
   begin
      null;
   end Set_Next;

   ------------------------
   -- Set_Start_Position --
   ------------------------

   procedure Set_Start_Position
     (Element : in out Primary_Base_List_Node'Class;
      Value   : in     Asis.Text_Position)
   is
   begin
      if Length (Element) = 0 or else Value < Element.Start_Position then
         Element.Start_Position := Value;
      end if;
   end Set_Start_Position;

   ----------------------
   -- Set_End_Position --
   ----------------------

   procedure Set_End_Position
     (Element : in out Primary_Base_List_Node'Class;
      Value   : in     Asis.Text_Position)
   is
   begin
      if Length (Element) = 0 or else Element.End_Position < Value then
         Element.End_Position := Value;
      end if;
   end Set_End_Position;

   --------------------
   -- Start_Position --
   --------------------

   function Start_Position
     (Element : Primary_Base_List_Node)
      return Text_Position
   is
   begin
      return Element.Start_Position;
   end Start_Position;

   ------------------------------
   -- To_Compilation_Unit_List --
   ------------------------------

   function To_Compilation_Unit_List
     (Item : Primary_Base_List_Node)
      return Asis.Compilation_Unit_List
   is
      List   : constant Asis.Element_List := To_Element_List (Item);
      Result : Compilation_Unit_List (List'Range);
      Last   : ASIS_Natural := 0;
      List_I : Asis.Element;
   begin
      for I in List'Range loop
         List_I := List (I);

         if List_I.all in Compilation_Unit_Node'Class then
            Last := Last + 1;
            Result (Last) := Compilation_Unit (List_I);
         end if;
      end loop;

      return Result (1 .. Last);
   end To_Compilation_Unit_List;

   ---------------------
   -- To_Element_List --
   ---------------------

   function To_Element_List
     (Item : Primary_Base_List_Node)
      return Asis.Element_List
   is
   begin
      return To_Element_List (Item, True);
   end To_Element_List;

   ---------------------
   -- To_Element_List --
   ---------------------

   function To_Element_List
     (Item            : Primary_Base_List_Node;
      Include_Pragmas : Boolean)
      return Asis.Element_List
   is
      use ER_Element_Lists;
      Result : Asis.Element_List (1 .. ASIS_Natural (Item.Length));
      Next   : aliased Element;
      Index  : ASIS_Natural := 0;
   begin
      while Iterate (Item.Content, Next'Access) loop
         if Include_Pragmas or else not Is_Pragma (Next) then
            Index := Index + 1;
            Result (Index) := Next;
         end if;
      end loop;

      return Result (1 .. Index);
   end To_Element_List;

   --------------------
   -- To_Pragma_List --
   --------------------

   function To_Pragma_List
     (Item : Primary_Base_List_Node)
      return Asis.Element_List
   is
      use ER_Element_Lists;
      Result : Asis.Element_List (1 .. ASIS_Natural (Item.Length));
      Next   : aliased Element;
      Index  : ASIS_Natural := 0;
   begin
      while Iterate (Item.Content, Next'Access) loop
         if Is_Pragma (Next) then
            Index := Index + 1;
            Result (Index) := Next;
         end if;
      end loop;

      return Result (1 .. Index);
   end To_Pragma_List;

end Asis.Gela.Base_Lists;



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
