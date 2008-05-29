------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

generic
   type Key_Type (<>) is private;
   type Element_Type (<>) is private;

   with function "<" (Left  : in Key_Type;
                      Right : in Key_Type)
          return Boolean is <>;

   with function "=" (Left  : in Element_Type;
                      Right : in Element_Type)
          return Boolean is <>;

package Ada.Containers.Indefinite_Ordered_Maps is

   pragma Preelaborate (Indefinite_Ordered_Maps);

   function Equivalent_Keys (Left  : in Key_Type;
                             Right : in Key_Type)
     return Boolean;

   type Map is tagged private;
   pragma Preelaborable_Initialization (Map);

   type Cursor is private;
   pragma Preelaborable_Initialization (Cursor);

   Empty_Map : constant Map;

   No_Element : constant Cursor;

   function "=" (Left  : in Map;
                 Right : in Map)
     return Boolean;

   function Length (Container : in Map) return Count_Type;

   function Is_Empty (Container : in Map) return Boolean;

   procedure Clear (Container : in out Map);

   function Key (Position : in Cursor) return Key_Type;

   function Element (Position : in Cursor) return Element_Type;

   procedure Replace_Element (Container : in out Map;
                              Position  : in     Cursor;
                              New_Item  : in     Element_Type);

   procedure Query_Element
    (Position : in Cursor;
     Process  : not null access procedure (Key     : in Key_Type;
                                           Element : in Element_Type));

   procedure Update_Element
    (Container : in out Map;
     Position  : in     Cursor;
     Process   : not null access procedure (Key     : in     Key_Type;
                                            Element : in out Element_Type));

   procedure Move (Target : in out Map;
                   Source : in out Map);

   procedure Insert (Container : in out Map;
                     Key       : in     Key_Type;
                     New_Item  : in     Element_Type;
                     Position  :    out Cursor;
                     Inserted  :    out Boolean);

   procedure Insert (Container : in out Map;
                     Key       : in     Key_Type;
                     New_Item  : in     Element_Type);

   procedure Include (Container : in out Map;
                      Key       : in     Key_Type;
                      New_Item  : in     Element_Type);

   procedure Replace (Container : in out Map;
                      Key       : in     Key_Type;
                      New_Item  : in     Element_Type);

   procedure Exclude (Container : in out Map;
                      Key       : in     Key_Type);

   procedure Delete (Container : in out Map;
                     Key       : in     Key_Type);

   procedure Delete (Container : in out Map;
                     Position  : in out Cursor);

   procedure Delete_First (Container : in out Map);

   procedure Delete_Last (Container : in out Map);

   function First (Container : in Map) return Cursor;

   function First_Element (Container : in Map) return Element_Type;

   function First_Key (Container : in Map) return Key_Type;

   function Last (Container : in Map) return Cursor;

   function Last_Element (Container : in Map) return Element_Type;

   function Last_Key (Container : in Map) return Key_Type;

   function Next (Position : in Cursor) return Cursor;

   procedure Next (Position : in out Cursor);

   function Previous (Position : in Cursor) return Cursor;

   procedure Previous (Position : in out Cursor);

   function Find (Container : in Map;
                  Key       : in Key_Type)
     return Cursor;

   function Element (Container : in Map;
                     Key       : in Key_Type)
     return Element_Type;

   function Floor (Container : in Map;
                   Key       : in Key_Type)
     return Cursor;

   function Ceiling (Container : in Map;
                     Key       : in Key_Type)
     return Cursor;

   function Contains (Container : in Map;
                      Key       : in Key_Type)
     return Boolean;

   function Has_Element (Position : in Cursor) return Boolean;

   function "<" (Left  : in Cursor;
                 Right : in Cursor)
     return Boolean;

   function ">" (Left  : in Cursor;
                 Right : in Cursor)
     return Boolean;

   function "<" (Left  : in Cursor;
                 Right : in Key_Type)
     return Boolean;

   function ">" (Left  : in Cursor;
                 Right : in Key_Type)
     return Boolean;

   function "<" (Left  : in Key_Type;
                 Right : in Cursor)
     return Boolean;

   function ">" (Left  : in Key_Type;
                 Right : in Cursor)
     return Boolean;

   procedure Iterate
    (Container : in Map;
     Process   : not null access procedure (Position : in Cursor));

   procedure Reverse_Iterate
    (Container : in Map;
     Process   : not null access procedure (Position : in Cursor));

private

   type Map is tagged null record;

   Empty_Map : constant Map := (null record);

   type Cursor is null record;

   No_Element : constant Cursor := (null record);

end Ada.Containers.Indefinite_Ordered_Maps;
