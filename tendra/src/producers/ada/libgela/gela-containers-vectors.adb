with Ada.Unchecked_Deallocation;

package body Gela.Containers.Vectors is

   ---------
   -- Add --
   ---------

   procedure Add
     (Object : in out Vector;
      Item   : in     Item_Type)
   is
   begin
      if Object = null then
         Object := new Vector_Node (Default_Size);
      end if;

      if Object.Last < Object.Size then
         Object.Last := Object.Last + 1;
         Object.Data (Object.Last) := Item;
      else
         Add (Object.Next, Item);
      end if;
   end Add;

   -----------
   -- Clear --
   -----------

   procedure Clear (Object : in out Vector) is
   begin
      if Object /= null then
         Object.Last := 0;
         Clear (Object.Next);
      end if;
   end Clear;

   ----------
   -- Free --
   ----------

   procedure Free (Object : in out Vector) is
      procedure Release is new
        Ada.Unchecked_Deallocation (Vector_Node, Vector);
   begin
      if Object /= null then
         Free (Object.Next);
         Release (Object);
      end if;
   end Free;

   ------------
   -- Length --
   ------------

   function Length (Object : Vector) return Index_Type'Base is
   begin
      if Object = null then
         return 0;
      else
         return Length (Object.Next) + Object.Last;
      end if;
   end Length;

   ---------
   -- Get --
   ---------

   function Get (Object : Vector; Index : Index_Type) return Item_Type is
   begin
      if Object = null then
         raise Constraint_Error;
      elsif Index <= Object.Last then
         return Object.Data (Index);
      else
         return Get (Object.Next, Index - Object.Last);
      end if;
   end Get;

   ---------
   -- Set --
   ---------

   procedure Set
     (Object : in out Vector;
      Index  : in     Index_Type;
      Item   : in     Item_Type) is
   begin
      if Object = null then
         raise Constraint_Error;
      elsif Index <= Object.Last then
         Object.Data (Index) := Item;
      else
         Set (Object.Next, Index - Object.Last, Item);
      end if;
   end Set;

   ----------
   -- Copy --
   ----------

   procedure Copy
     (Target : in out Vector;
      Source : in     Vector)
   is
      Temp : Vector := Source;
      Pos  : Index_Type := 1;
   begin
      if Target /= null and then Target.Size /= Length (Source) then
         Free  (Target);
      end if;

      if Source /= null and Target = null then
         Target := new Vector_Node (Length (Source));
         Target.Last := Target.Size;
      else
         Clear (Target);
      end if;

      while Temp /= null loop
         Target.Data (Pos .. Pos + Temp.Last - 1) :=
           Temp.Data (1 .. Temp.Last);

         Pos  := Pos + Temp.Last;
         Temp := Temp.Next;
      end loop;
   end Copy;

end Gela.Containers.Vectors;
