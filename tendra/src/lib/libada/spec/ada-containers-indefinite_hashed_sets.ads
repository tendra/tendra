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

   with function Hash (Element : in Element_Type) return Hash_Type;

   with function Equivalent_Elements (Left  : in Element_Type;
                                      Right : in Element_Type)
          return Boolean;

   with function "=" (Left  : in Element_Type;
                      Right : in Element_Type)
          return Boolean is <>;

package Ada.Containers.Indefinite_Hashed_Sets is

   pragma Preelaborate (Indefinite_Hashed_Sets);

   type Set is tagged private;
   pragma Preelaborable_Initialization (Set);

   type Cursor is private;
   pragma Preelaborable_Initialization (Cursor);

   Empty_Set : constant Set;

   No_Element : constant Cursor;

   function "=" (Left  : in Set;
                 Right : in Set)
     return Boolean;

   function Equivalent_Sets (Left  : in Set;
                             Right : in Set)
     return Boolean;

   function To_Set (New_Item : in Element_Type) return Set;

   function Capacity (Container : in Set) return Count_Type;

   procedure Reserve_Capacity (Container : in out Set;
                               Capacity  : in     Count_Type);

   function Length (Container : in Set) return Count_Type;

   function Is_Empty (Container : in Set) return Boolean;

   procedure Clear (Container : in out Set);

   function Element (Position : in Cursor) return Element_Type;

   procedure Replace_Element (Container : in out Set;
                              Position  : in     Cursor;
                              New_Item  : in     Element_Type);

   procedure Query_Element
    (Position : in Cursor;
     Process  : not null access procedure (Element : in Element_Type));

   procedure Move (Target : in out Set;
                   Source : in out Set);

   procedure Insert (Container : in out Set;
                     New_Item  : in     Element_Type;
                     Position  :    out Cursor;
                     Inserted  :    out Boolean);

   procedure Insert (Container : in out Set;
                     New_Item  : in     Element_Type);

   procedure Include (Container : in out Set;
                      New_Item  : in     Element_Type);

   procedure Replace (Container : in out Set;
                      New_Item  : in     Element_Type);

   procedure Exclude (Container : in out Set;
                      Item      : in     Element_Type);

   procedure Delete (Container : in out Set;
                     Item      : in     Element_Type);

   procedure Delete (Container : in out Set;
                     Position  : in out Cursor);

   procedure Union (Target : in out Set;
                    Source : in     Set);

   function Union (Left  : in Set;
                   Right : in Set)
     return Set;

   function "or" (Left  : in Set;
                  Right : in Set)
     return Set renames Union;

   procedure Intersection (Target : in out Set;
                           Source : in     Set);

   function Intersection (Left  : in Set;
                          Right : in Set)
     return Set;

   function "and" (Left  : in Set;
                   Right : in Set)
     return Set renames Intersection;

   procedure Difference (Target : in out Set;
                         Source : in     Set);

   function Difference (Left  : in Set;
                        Right : in Set)
     return Set;

   function "-" (Left  : in Set;
                 Right : in Set)
     return Set renames Difference;

   procedure Symmetric_Difference (Target : in out Set;
                                   Source : in     Set);

   function Symmetric_Difference (Left  : in Set;
                                  Right : in Set)
     return Set;

   function "xor" (Left  : in Set;
                   Right : in Set)
     return Set renames Symmetric_Difference;

   function Overlap (Left  : in Set;
                     Right : in Set)
     return Boolean;

   function Is_Subset (Subset : in Set;
                       Of_Set : in Set)
     return Boolean;

   function First (Container : in Set) return Cursor;

   function Next (Position : in Cursor) return Cursor;

   procedure Next (Position : in out Cursor);

   function Find (Container : in Set;
                  Item      : in Element_Type)
     return Cursor;

   function Contains (Container : in Set;
                      Item      : in Element_Type)
     return Boolean;

   function Has_Element (Position : in Cursor) return Boolean;

   function Equivalent_Elements (Left  : in Cursor;
                                 Right : in Cursor)
     return Boolean;

   function Equivalent_Elements (Left  : in Cursor;
                                 Right : in Element_Type)
     return Boolean;

   function Equivalent_Elements (Left  : in Element_Type;
                                 Right : in Cursor)
     return Boolean;

   procedure Iterate
    (Container : in Set;
     Process   : not null access procedure (Position : in Cursor));

   generic
      type Key_Type  (<>) is private;

      with function Key (Element : in Element_Type) return Key_Type;

      with function Hash (Key : in Key_Type) return Hash_Type;

      with function Equivalent_Keys (Left  : in Key_Type;
                                     Right : in Key_Type)
             return Boolean;

   package Generic_Keys is

      function Key (Position : in Cursor) return Key_Type;

      function Element (Container : in Set;
                        Key       : in Key_Type)
        return Element_Type;

      procedure Replace (Container : in out Set;
                         Key       : in     Key_Type;
                         New_Item  : in     Element_Type);

      procedure Exclude (Container : in out Set;
                         Key       : in     Key_Type);

      procedure Delete (Container : in out Set;
                        Key       : in     Key_Type);

      function Find (Container : in Set;
                     Key       : in Key_Type)
        return Cursor;

      function Contains (Container : in Set;
                         Key       : in Key_Type)
        return Boolean;

      procedure Update_Element_Preserving_Key
       (Container : in out Set;
        Position  : in     Cursor;
        Process   : not null access procedure (Element : in out Element_Type));

   end Generic_Keys;

private

   type Set is tagged null record;

   Empty_Set : constant Set := (null record);

   type Cursor is null record;

   No_Element : constant Cursor := (null record);

end Ada.Containers.Indefinite_Hashed_Sets;
