generic
   type Item_Type is private;
   type Index_Type is range <>;
package Gela.Containers.Vectors is
   pragma Preelaborate;

   type Vector is private;

   procedure Add
     (Object : in out Vector;
      Item   : in     Item_Type);

   procedure Clear (Object : in out Vector);

   procedure Free (Object : in out Vector);

   function Length (Object : Vector) return Index_Type'Base;

   function Get (Object : Vector; Index : Index_Type) return Item_Type;

   procedure Set
     (Object : in out Vector;
      Index  : in     Index_Type;
      Item   : in     Item_Type);

   procedure Copy
     (Target : in out Vector;
      Source : in     Vector);

private
   type Vector_Node;
   type Vector is access all Vector_Node;

   Default_Size : constant Index_Type := 8 * 4096 / Item_Type'Size;

   type Table is array (Index_Type range <>) of Item_Type;

   type Vector_Node (Size : Index_Type) is record
      Data : Table (1 .. Size);
      Last : Index_Type'Base := 0;
      Next : Vector;
   end record;

end Gela.Containers.Vectors;
