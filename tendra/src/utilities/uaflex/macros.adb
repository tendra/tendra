with Ada.Strings.Unbounded;

package body Macros is
   package U renames Ada.Strings.Unbounded;

   type Node;
   type Node_Access is access all Node;
   type Node is record
      Next : Node_Access;
      Name : U.Unbounded_String;
      Expr : Expression;
   end record;

   List : Node_Access;

   procedure Find_One
     (Name  : in     String;
      Expr  :    out Expression;
      Found :    out Boolean);

   ---------
   -- Add --
   ---------

   procedure Add
     (Name : String;
      Expr : Expression)
   is
      Temp  : Expression;
      Found : Boolean;
   begin
      Find_One (Name, Temp, Found);

      if not Found then
         List := new Node'(List, U.To_Unbounded_String (Name), Expr);
      end if;
   end Add;

   ----------
   -- Find --
   ----------

   function Find (Name : String) return Expression is
      Expr  : Expression;
      Found : Boolean;
   begin
      Find_One (Name, Expr, Found);

      if not Found then
         raise Not_Found;
      end if;

      return Expr;
   end Find;

   --------------
   -- Find_One --
   --------------

   procedure Find_One
     (Name  : in     String;
      Expr  :    out Expression;
      Found :    out Boolean)
   is
      use type U.Unbounded_String;

      Ptr : Node_Access := List;
   begin
      while Ptr /= null loop
         if Ptr.Name = Name then
            Expr := Ptr.Expr;
            Found := True;
            return;
         end if;

         Ptr := Ptr.Next;
      end loop;

      Found := False;
   end Find_One;

end Macros;

