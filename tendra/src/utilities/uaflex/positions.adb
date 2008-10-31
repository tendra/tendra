with Ada.Unchecked_Deallocation;

package body Positions is

   ---------
   -- "+" --
   ---------

   function "+" (Object : in Iterator) return Position is
   begin
      return Object.Data;
   end "+";

   ---------
   -- Add --
   ---------

   procedure Add
     (Object : in out Set;
      Pos    : in     Position)
   is
      X : Set := Object;
   begin
      if Object = null then
         Object := new Node'(Pos, null);
      elsif Object.Data < Pos then
         Object := new Node'(Pos, Object);
      elsif Object.Data > Pos then
         Add (Object.Next, Pos);
      end if;
   end Add;

   ---------
   -- Add --
   ---------

   procedure Add
     (Object : in out Set;
      Pos    : in     Set)
   is
      Element : Iterator := Start (Pos);
   begin
      while Exist (Element) loop
         Add (Object, +Element);
         Element := Next (Element);
      end loop;
   end Add;

   -----------
   -- Clear --
   -----------

   procedure Clear (Object : in out Set) is
      procedure Free is new Ada.Unchecked_Deallocation (Node, Set);
   begin
      if Object /= null then
         Clear (Object.Next);
         Free (Object);
      end if;
   end Clear;

   --------------
   -- Contains --
   --------------

   function Contains
     (Object : in Set;
      Pos    : in Position)
      return Boolean
   is
      Element : Iterator := Start (Object);
   begin
      while Exist (Element) loop
         if Pos = +Element then
            return True;
         end if;

         Element := Next (Element);
      end loop;

      return False;
   end Contains;

   -----------
   -- Equal --
   -----------

   function Equal (Left, Right : Set) return Boolean is
   begin
      if Left = null and Right = null then
         return True;
      elsif Left /= null and Right /= null then
         return Left.Data = Right.Data and then
           Equal (Left.Next, Right.Next);
      else
         return False;
      end if;
   end Equal;

   -----------
   -- Exist --
   -----------

   function Exist (Object : in Iterator) return Boolean is
   begin
      return Object /= null;
   end Exist;

   ----------
   -- Next --
   ----------

   function Next (Object : in Iterator) return Iterator is
   begin
      return Iterator (Object.Next);
   end Next;

   -----------
   -- Start --
   -----------

   function Start (Object : in Set) return Iterator is
   begin
      return Iterator (Object);
   end Start;

end Positions;

