with Ada.Unchecked_Deallocation;

package body Gela.Containers.Lists is
   use E;
   procedure Free is new  Ada.Unchecked_Deallocation (Node, Node_Access);

   ------------
   -- Append --
   ------------

   procedure Append
     (Container : in out List;
      New_Item  : in     Element_Type)
   is
   begin
      Append (Container.X, new Node'(null, New_Item));
   end Append;

   -----------
   -- Clear --
   -----------

   procedure Clear (Container : in out List) is
      Next : Node_Access;
   begin
      while not Is_Empty (Container.X) loop
         Delete_First (Container.X, Next);
         Free (Next);
      end loop;
   end Clear;

   --------------
   -- Contains --
   --------------

   function Contains
     (Container : List;
      Item      : Element_Type)
      return Boolean
   is
      Next : aliased Node_Access;
   begin
      while Iterate (Container.X, Next'Access) loop
         if Next.Data = Item then
            return True;
         end if;
      end loop;

      return False;
   end Contains;

   ------------
   -- Delete --
   ------------

   procedure Delete (Container : in out List;
                     Position  : in out Cursor)
   is
      Result : Cursor := Next (Position);
   begin
      Delete (Container.X, Position.Ptr);
      Position := Result;
   end Delete;

   ------------------
   -- Delete_First --
   ------------------

   procedure Delete_First (Container : in out List) is
      Next : Node_Access;
   begin
      Delete_First (Container.X, Next);
      Free (Next);
   end Delete_First;

   -------------
   -- Element --
   -------------

   function Element (Position : Cursor) return Element_Type is
   begin
      return Position.Ptr.Data;
   end Element;

   ----------
   -- Find --
   ----------

   function Find
     (Container : List;
      Item      : Element_Type;
      Position  : Cursor := No_Element) return Cursor
   is
      Next : aliased Node_Access := Position.Ptr;
   begin
      while Iterate (Container.X, Next'Access) loop
         if Next.Data = Item then
            return (Next, Container.X'Unchecked_Access);
         end if;
      end loop;

      return No_Element;
   end Find;

   -----------
   -- First --
   -----------

   function First (Container : List) return Cursor is
   begin
      if Is_Empty (Container.X) then
         return No_Element;
      else
         return (First (Container.X), Container.X'Unchecked_Access);
      end if;
   end First;

   -------------------
   -- First_Element --
   -------------------

   function First_Element (Container : List) return Element_Type is
   begin
      return First (Container.X).Data;
   end First_Element;

   --------------
   -- Get_Next --
   --------------

   function Get_Next (Item : Node_Access) return Node_Access is
   begin
      return Item.Next;
   end Get_Next;

   -----------------
   -- Has_Element --
   -----------------

   function Has_Element (Position : Cursor) return Boolean is
   begin
      return Position.Ptr /= null;
   end Has_Element;

   --------------
   -- Is_Empty --
   --------------

   function Is_Empty (Container : List) return Boolean is
   begin
      return Is_Empty (Container.X);
   end Is_Empty;

   ------------------
   -- Last_Element --
   ------------------

   function Last_Element (Container : List) return Element_Type is
   begin
      return Last (Container.X).Data;
   end Last_Element;

   ----------
   -- Next --
   ----------

   function Next (Position : Cursor) return Cursor is
   begin
      if Position.Ptr = E.Last (Position.List.all) then
         return No_Element;
      else
         return (Get_Next (Position.Ptr), Position.List);
      end if;
   end Next;

   -------------
   -- Prepend --
   -------------

   procedure Prepend
     (Container : in out List;
      New_Item  : in     Element_Type)
   is
   begin
      Prepend (Container.X, new Node'(null, New_Item));
   end Prepend;

   --------------
   -- Set_Next --
   --------------

   procedure Set_Next (Item, Next : Node_Access) is
   begin
      Item.Next := Next;
   end Set_Next;

end Gela.Containers.Lists;
