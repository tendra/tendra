with Ada.Finalization;

package Symbols is

   type Symbol is mod 16#110001#;

   type Symbol_Array is array (Positive range <>) of Symbol;

   type Symbol_Set is private;

   function To_Range  (Single       : Symbol)       return Symbol_Set;
   function To_Range  (Some         : Symbol_Array) return Symbol_Set;
   function To_Range  (Lower, Upper : Symbol)       return Symbol_Set;
   function "or"      (Left, Right  : Symbol_Set)   return Symbol_Set;
   function "and"     (Left, Right  : Symbol_Set)   return Symbol_Set;
   function "-"       (Left, Right  : Symbol_Set)   return Symbol_Set;
   function "*"       (Left, Right  : Symbol_Set)   return Boolean;
   function Intersect (Left, Right  : Symbol_Set)   return Boolean renames "*";
   function Is_Empty  (Left         : Symbol_Set)   return Boolean;
   function Is_Equal  (Left, Right  : Symbol_Set)   return Boolean;

   function Range_Image
     (Left   : Symbol_Set;
      Indent : String) return String;

   Empty        : constant Symbol_Set;
   Not_A_Symbol : constant Symbol := Symbol'Last;

   type Symbol_Set_Array is array (Positive range <>) of Symbol_Set;

   function Distinct_Symbol_Sets
     (Next : in Symbol_Set_Array) return Symbol_Set_Array;

private

   package F renames Ada.Finalization;

   type Set_Node;
   type Node_Access is access all Set_Node;

   type Symbol_Set is new F.Controlled with record
      Node : Node_Access;
   end record;

   type Symbol_Range is record
      Lower, Upper : Symbol;
   end record;

   function "*"      (Left, Right  : Symbol_Range) return Boolean;
   function "or"     (Left, Right  : Symbol_Range) return Symbol_Range;
   function "and"    (Left, Right  : Symbol_Range) return Symbol_Range;

   type Symbol_Ranges is array (Positive range <>) of Symbol_Range;

   type Set_Node (Length : Natural) is record
      Count  : Natural;
      Ranges : Symbol_Ranges (1 .. Length);
   end record;

   procedure Adjust (Object : in out Symbol_Set);
   procedure Finalize (Object : in out Symbol_Set);

   Empty_Node : aliased Set_Node :=
     (0, 2, (others => (Not_A_Symbol, Not_A_Symbol)));
   Empty : constant Symbol_Set := (F.Controlled with Empty_Node'Access);

   pragma Inline ("*");
   pragma Inline (Is_Empty);
   pragma Inline (Is_Equal);

end Symbols;
