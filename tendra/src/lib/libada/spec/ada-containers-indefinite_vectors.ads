------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

generic
   type Index_Type is range <>;
   type Element_Type (<>) is private;

   with function "=" (Left  : in Element_Type;
                      Right : in Element_Type)
          return Boolean is <>;

package Ada.Containers.Indefinite_Vectors is

   pragma Preelaborate (Indefinite_Vectors);

   subtype Extended_Index is Index_Type'Base
     range Index_Type'First - 1
             .. Index_Type'Min (Index_Type'Base'Last - 1, Index_Type'Last) + 1;

   No_Index : constant Extended_Index := Extended_Index'First;

   type Vector is tagged private;
   pragma Preelaborable_Initialization (Vector);

   type Cursor is private;
   pragma Preelaborable_Initialization (Cursor);

   Empty_Vector : constant Vector;

   No_Element : constant Cursor;

   function "=" (Left  : in Vector;
                 Right : in Vector)
     return Boolean;

   function To_Vector (Length : in Count_Type) return Vector;

   function To_Vector (New_Item : in Element_Type;
                       Length   : in Count_Type)
     return Vector;

   function "&" (Left  : in Vector;
                 Right : in Vector)
     return Vector;

   function "&" (Left  : in Vector;
                 Right : in Element_Type)
     return Vector;

   function "&" (Left  : in Element_Type;
                 Right : in Vector)
     return Vector;

   function "&" (Left  : in Element_Type;
                 Right : in Element_Type)
     return Vector;

   function Capacity (Container : in Vector) return Count_Type;

   procedure Reserve_Capacity (Container : in out Vector;
                               Capacity  : in     Count_Type);

   function Length (Container : in Vector) return Count_Type;

   procedure Set_Length (Container : in out Vector;
                         Length    : in     Count_Type);

   function Is_Empty (Container : in Vector) return Boolean;

   procedure Clear (Container : in out Vector);

   function To_Cursor (Container : Vector;
                       Index     : Extended_Index)
     return Cursor;

   function To_Index (Position : in Cursor) return Extended_Index;

   function Element (Container : in Vector;
                     Index     : in Index_Type)
     return Element_Type;

   function Element (Position : in Cursor) return Element_Type;

   procedure Replace_Element (Container : in out Vector;
                              Index     : in     Index_Type;
                              New_Item  : in     Element_Type);

   procedure Replace_Element (Container : in out Vector;
                              Position  : in     Cursor;
                              New_item :  in     Element_Type);

   procedure Query_Element
    (Container : in Vector;
     Index     : in Index_Type;
     Process   : not null access procedure (Element : in Element_Type));

   procedure Query_Element
    (Position : in Cursor;
     Process  : not null access procedure (Element : in Element_Type));

   procedure Update_Element
    (Container : in out Vector;
     Index     : in     Index_Type;
     Process   : not null access procedure (Element : in out Element_Type));

   procedure Update_Element
    (Container : in out Vector;
     Position  : in      Cursor;
     Process   : not null access procedure (Element : in out Element_Type));

   procedure Move (Target : in out Vector;
                   Source : in out Vector);

   procedure Insert (Container : in out Vector;
                     Before    : in     Extended_Index;
                     New_Item  : in     Vector);

   procedure Insert (Container : in out Vector;
                     Before    : in     Cursor;
                     New_Item  : in     Vector);

   procedure Insert (Container : in out Vector;
                     Before    : in     Cursor;
                     New_Item  : in     Vector;
                     Position  :    out Cursor);

   procedure Insert (Container : in out Vector;
                     Before    : in     Extended_Index;
                     New_Item  : in     Element_Type;
                     Count     : in     Count_Type := 1);

   procedure Insert (Container : in out Vector;
                     Before    : in     Cursor;
                     New_Item  : in     Element_Type;
                     Count     : in     Count_Type := 1);

   procedure Insert (Container : in out Vector;
                     Before    : in     Cursor;
                     New_Item  : in     Element_Type;
                     Position  :    out Cursor;
                     Count     : in     Count_Type := 1);

   procedure Prepend (Container : in out Vector;
                      New_Item  : in     Vector);

   procedure Prepend (Container : in out Vector;
                      New_Item  : in     Element_Type;
                      Count     : in     Count_Type := 1);

   procedure Append (Container : in out Vector;
                     New_Item  : in     Vector);

   procedure Append (Container : in out Vector;
                     New_Item  : in     Element_Type;
                     Count     : in     Count_Type := 1);

   procedure Insert_Space (Container : in out Vector;
                           Before    : in     Extended_Index;
                           Count     : in     Count_Type := 1);

   procedure Insert_Space (Container : in out Vector;
                           Before    : in     Cursor;
                           Position  :    out Cursor;
                           Count     : in     Count_Type := 1);

   procedure Delete (Container : in out Vector;
                     Index     : in     Extended_Index;
                     Count     : in     Count_Type := 1);

   procedure Delete (Container : in out Vector;
                     Position  : in out Cursor;
                     Count     : in     Count_Type := 1);

   procedure Delete_First (Container : in out Vector;
                           Count     : in     Count_Type := 1);

   procedure Delete_Last (Container : in out Vector;
                          Count     : in     Count_Type := 1);

   procedure Reverse_Elements (Container : in out Vector);

   procedure Swap (Container : in out Vector;
                   I         : in     Index_Type;
                   J         : in     Index_Type);

   procedure Swap (Container : in out Vector;
                   I         : in     Cursor;
                   J         : in     Cursor);

   function First_Index (Container : in Vector) return Index_Type;

   function First (Container : in Vector) return Cursor;

   function First_Element (Container : in Vector) return Element_Type;

   function Last_Index (Container : in Vector) return Extended_Index;

   function Last (Container : in Vector) return Cursor;

   function Last_Element (Container : in Vector) return Element_Type;

   function Next (Position : in Cursor) return Cursor;

   procedure Next (Position : in out Cursor);

   function Previous (Position : in Cursor) return Cursor;

   procedure Previous (Position : in out Cursor);

   function Find_Index (Container : in Vector;
                        Item      : in Element_Type;
                        Index     : in Index_Type := Index_Type'First)
     return Extended_Index;

   function Find (Container : in Vector;
                  Item      : in Element_Type;
                  Position  : in Cursor := No_Element)
     return Cursor;

   function Reverse_Find_Index (Container : in Vector;
                                Item      : in Element_Type;
                                Index     : in Index_Type := Index_Type'Last)
     return Extended_Index;

   function Reverse_Find (Container : in Vector;
                          Item      : in Element_Type;
                          Position  : in Cursor := No_Element)
     return Cursor;

   function Contains (Container : in Vector;
                      Item      : in Element_Type)
     return Boolean;

   function Has_Element (Position : in Cursor) return Boolean;

   procedure Iterate
    (Container : in Vector;
     Process   : not null access procedure (Position : in Cursor));

   procedure Reverse_Iterate
     (Container : in Vector;
      Process   : not null access procedure (Position : in Cursor));

   generic
      with function "<" (Left  : in Element_Type;
                         Right : in Element_Type)
             return Boolean is <>;

   package Generic_Sorting is

      function Is_Sorted (Container : in Vector) return Boolean;

      procedure Sort (Container : in out Vector);

      procedure Merge (Target : in out Vector;
                       Source : in out Vector);

   end Generic_Sorting;

private

   type Vector is tagged null record;

   Empty_Vector : constant Vector := (null record);

   type Cursor is null record;

   No_Element : constant Cursor := (null record);

end Ada.Containers.Indefinite_Vectors;
