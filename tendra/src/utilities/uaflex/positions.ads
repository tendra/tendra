package Positions is

   type Position is new Positive;

   type Set is private;

   function Equal (Left, Right : Set) return Boolean;

   procedure Add
     (Object : in out Set;
      Pos    : in     Position);

   procedure Add
     (Object : in out Set;
      Pos    : in     Set);

   function Contains
     (Object : in Set;
      Pos    : in Position) return Boolean;

   procedure Clear (Object : in out Set);

   type Iterator is private;

   function Start (Object : in Set) return Iterator;
   function Exist (Object : in Iterator) return Boolean;
   function Next  (Object : in Iterator) return Iterator;
   function "+"   (Object : in Iterator) return Position;

   Empty_Set : constant Set;

private
   type Node;
   type Set is access all Node;

   type Node is record
      Data : Position;
      Next : Set;
   end record;

   type Iterator is access all Node;

   Empty_Set : constant Set := null;

end Positions;
