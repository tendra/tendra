------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

generic
   type Element_Type (<>) is private;

   with function "=" (Left  : in Element_Type;
                      Right : in Element_Type)
          return Boolean is <>;

package Ada.Containers.Indefinite_Doubly_Linked_Lists is

   pragma Preelaborate (Indefinite_Doubly_Linked_Lists);

   type List is tagged private;
   pragma Preelaborable_Initialization (List);

   type Cursor is private;
   pragma Preelaborable_Initialization (Cursor);

   Empty_List : constant List;

   No_Element : constant Cursor;

   function "=" (Left  : in List;
                 Right : in List)
     return Boolean;

   function Length (Container : in List) return Count_Type;

   function Is_Empty (Container : in List) return Boolean;

   procedure Clear (Container : in out List);

   function Element (Position : in Cursor) return Element_Type;

   procedure Replace_Element (Container : in out List;
                              Position  : in     Cursor;
                              New_Item  : in     Element_Type);

   procedure Query_Element
    (Position : in Cursor;
     Process  : not null access procedure (Element : in Element_Type));

   procedure Update_Element
    (Container : in out List;
     Position  : in     Cursor;
     Process   : not null access procedure (Element : in out Element_Type));

   procedure Move (Target : in out List;
                   Source : in out List);

   procedure Insert (Container : in out List;
                     Before    : in     Cursor;
                     New_Item  : in     Element_Type;
                     Count     : in     Count_Type := 1);

   procedure Insert (Container : in out List;
                     Before    : in     Cursor;
                     New_Item  : in     Element_Type;
                     Position  :    out Cursor;
                     Count     : in     Count_Type := 1);

   procedure Prepend (Container : in out List;
                      New_Item  : in     Element_Type;
                      Count     : in     Count_Type := 1);

   procedure Append (Container : in out List;
                     New_Item  : in     Element_Type;
                     Count     : in     Count_Type := 1);

   procedure Delete (Container : in out List;
                     Position  : in out Cursor;
                     Count     : in     Count_Type := 1);

   procedure Delete_First (Container : in out List;
                           Count     : in     Count_Type := 1);

   procedure Delete_Last (Container : in out List;
                          Count     : in     Count_Type := 1);

   procedure Reverse_Elements (Container : in out List);

   procedure Swap (Container : in out List;
                   I         : in     Cursor;
                   J         : in     Cursor);

   procedure Swap_Links (Container : in out List;
                         I         : in     Cursor;
                         J         : in     Cursor);

   procedure Splice (Target : in out List;
                     Before : in     Cursor;
                     Source : in out List);

   procedure Splice (Target   : in out List;
                     Before   : in     Cursor;
                     Source   : in out List;
                     Position : in out Cursor);

   procedure Splice (Container : in out List;
                     Before    : in     Cursor;
                     Position  : in     Cursor);

   function First (Container : in List) return Cursor;

   function First_Element (Container : in List) return Element_Type;

   function Last (Container : in List) return Cursor;

   function Last_Element (Container : in List) return Element_Type;

   function Next (Position : in Cursor) return Cursor;

   function Previous (Position : in Cursor) return Cursor;

   procedure Next (Position : in out Cursor);

   procedure Previous (Position : in out Cursor);

   function Find (Container : in List;
                  Item      : in Element_Type;
                  Position  : in Cursor := No_Element)
     return Cursor;

   function Reverse_Find (Container : in List;
                          Item      : in Element_Type;
                          Position  : in Cursor := No_Element)
     return Cursor;

   function Contains (Container : in List;
                      Item      : in Element_Type)
     return Boolean;

   function Has_Element (Position : in Cursor) return Boolean;

   procedure Iterate
    (Container : in List;
     Process   : not null access procedure (Position : in Cursor));

   procedure Reverse_Iterate
    (Container : in List;
     Process   : not null access procedure (Position : in Cursor));

   generic
      with function "<" (Left  : in Element_Type;
                         Right : in Element_Type)
             return Boolean is <>;

   package Generic_Sorting is

      function Is_Sorted (Container : in List) return Boolean;

      procedure Sort (Container : in out List);

      procedure Merge (Target : in out List;
                       Source : in out List);

   end Generic_Sorting;

private

   type List is tagged null record;

   Empty_List : constant List := (null record);

   type Cursor is null record;

   No_Element : constant Cursor := (null record);

end Ada.Containers.Indefinite_Doubly_Linked_Lists;
