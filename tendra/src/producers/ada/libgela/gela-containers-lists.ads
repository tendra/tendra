with Gela.Embeded_Links.Lists;

generic
   type Element_Type is private;
   with function "=" (Left, Right : Element_Type)
                     return Boolean is <>;
package Gela.Containers.Lists is
   pragma Preelaborate (Lists);

   type List is limited private;

   type Cursor is private;

   No_Element : constant Cursor;

   function Is_Empty (Container : List) return Boolean;

   procedure Clear (Container : in out List);

   function Element (Position : Cursor)
                    return Element_Type;

   procedure Prepend (Container : in out List;
                      New_Item  : in     Element_Type);

   procedure Append (Container : in out List;
                     New_Item  : in     Element_Type);

   procedure Delete (Container : in out List;
                     Position  : in out Cursor);

   procedure Delete_First (Container : in out List);

   function First (Container : List) return Cursor;

   function First_Element (Container : List) return Element_Type;

   function Last_Element (Container : List) return Element_Type;

   function Next (Position : Cursor) return Cursor;

   function Find (Container : List;
                  Item      : Element_Type;
                  Position  : Cursor := No_Element)
                 return Cursor;

   function Contains (Container : List;
                      Item      : Element_Type) return Boolean;

   function Has_Element (Position : Cursor) return Boolean;

private
   type Node;

   type Node_Access is access all Node;

   type Node is record
      Next : Node_Access;
      Data : Element_Type;
   end record;

   function  Get_Next (Item : Node_Access) return Node_Access;
   procedure Set_Next (Item, Next : Node_Access);

   pragma Inline (Get_Next, Set_Next);

   package E is new Gela.Embeded_Links.Lists (Node, Node_Access);

   type List is limited record
      X : aliased E.List;
   end record;

   type List_Access is access constant E.List;

   type Cursor is record
      Ptr  : Node_Access;
      List : List_Access;
   end record;

   No_Element : constant Cursor := (null, null);

end Gela.Containers.Lists;
