with Ada.Strings.Unbounded;

package body Tokens is

   package U renames Ada.Strings.Unbounded;

   type Node;
   type Node_Access is access all Node;
   type Node is record
      Next  : Node_Access;
      Name  : U.Unbounded_String;
      Index : Positive;
   end record;

   List : Node_Access;

   -----------
   -- Count --
   -----------

   function Count return Natural is
   begin
      if List = null then
         return 0;
      else
         return List.Index;
      end if;
   end Count;

   ---------------
   -- Get_Token --
   ---------------

   procedure Get_Token
     (Name   : in     String;
      Result :    out Positive)
   is
      use type U.Unbounded_String;
      Ptr : Node_Access := List;
   begin
      while Ptr /= null loop
         if Ptr.Name = Name then
            Result := Ptr.Index;
            return;
         end if;

         Ptr := Ptr.Next;
      end loop;

      Result := Count + 1;
      List   := new Node'(List, U.To_Unbounded_String (Name), Result);
   end Get_Token;

   ----------------
   -- Token_Name --
   ----------------

   function Token_Name (Index : Positive) return String is
      Ptr : Node_Access := List;
   begin
      while Ptr /= null loop
         if Ptr.Index = Index then
            return U.To_String (Ptr.Name);
         end if;

         Ptr := Ptr.Next;
      end loop;

      return "";
   end Token_Name;

end Tokens;

