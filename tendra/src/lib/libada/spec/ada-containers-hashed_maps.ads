------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

generic
   type Key_Type is private;
   type Element_Type is private;

   with function Hash (Key : in Key_Type) return Hash_Type;

   with function Equivalent_Keys (Left  : in Key_Type;
                                  Right : in Key_Type)
          return Boolean;

   with function "=" (Left  : in Element_Type;
                      Right : in Element_Type)
          return Boolean is <>;

package Ada.Containers.Hashed_Maps is

   pragma Preelaborate (Hashed_Maps);

   type Map is tagged private;
   pragma Preelaborable_Initialization (Map);

   type Cursor is private;
   pragma Preelaborable_Initialization (Cursor);

   Empty_Map : constant Map;

   No_Element : constant Cursor;

   function "=" (Left  : in Map;
                 Right : in Map)
     return Boolean;

   function Capacity (Container : in Map) return Count_Type;

   procedure Reserve_Capacity (Container : in out Map;
                               Capacity  : in     Count_Type);

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

   procedure Insert (Container   : in out Map;
                     Key         : in     Key_Type;
                     New_Item    : in     Element_Type;
                     Position    :    out Cursor;
                     Inserted    :    out Boolean);

   procedure Insert (Container : in out Map;
                     Key       : in     Key_Type;
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

   function First (Container : in Map) return Cursor;

   function Next (Position : in Cursor) return Cursor;

   procedure Next (Position : in out Cursor);

   function Find (Container : in Map;
                  Key       : in Key_Type)
     return Cursor;

   function Element (Container : in Map;
                     Key       : in Key_Type)
     return Element_Type;

   function Contains (Container : in Map;
                      Key       : in Key_Type)
     return Boolean;

   function Has_Element (Position : in Cursor) return Boolean;

   function Equivalent_Keys (Left  : in Cursor;
                             Right : in Cursor)
     return Boolean;

   function Equivalent_Keys (Left  : in Cursor;
                             Right : in Key_Type)
     return Boolean;

   function Equivalent_Keys (Left  : in Key_Type;
                             Right : in Cursor)
     return Boolean;

   procedure Iterate
    (Container : in Map;
     Process   : not null access procedure (Position : in Cursor));

private

   type Map is tagged null record;

   Empty_Map : constant Map := (null record);

   type Cursor is null record;

   No_Element : constant Cursor := (null record);

end Ada.Containers.Hashed_Maps;
