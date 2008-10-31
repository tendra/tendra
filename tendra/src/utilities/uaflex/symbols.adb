with Ada.Unchecked_Deallocation;
with Ada.Strings.Unbounded;

package body Symbols is

   function Min (Left, Right : Symbol) return Symbol;
   function Max (Left, Right : Symbol) return Symbol;

   ---------
   -- "*" --
   ---------

   function "*" (Left, Right  : Symbol_Set) return Boolean is
   begin
      return not Is_Empty (Left and Right);
   end "*";

   ---------
   -- "*" --
   ---------

   function "*" (Left, Right  : Symbol_Range)   return Boolean is
   begin
      if Left.Upper < Right.Lower or Left.Lower > Right.Upper then
         return False; --  no intersect
      else
         return True; --  intersect
      end if;
   end "*";

   ----------
   -- "or" --
   ----------

   function "or" (Left, Right  : Symbol_Range) return Symbol_Range is
   begin
      return (Min (Left.Lower, Right.Lower), Max (Left.Upper, Right.Upper));
   end "or";

   -----------
   -- "and" --
   -----------

   function "and" (Left, Right  : Symbol_Range) return Symbol_Range is
   begin
      return (Max (Left.Lower, Right.Lower), Min (Left.Upper, Right.Upper));
   end "and";

   ---------
   -- "-" --
   ---------

   function "-" (Left, Right  : Symbol_Set) return Symbol_Set is
      L       : Symbol_Ranges renames Left.Node.Ranges;
      R       : Symbol_Ranges renames Right.Node.Ranges;
      Max_Len : constant Natural := L'Length + 2 * R'Length;
      Result  : Symbol_Ranges (1 .. Max_Len);
      Last    : Natural := 0;
      Index   : Positive;
      Start   : Symbol;

      procedure New_Range (Lower, Upper : Symbol) is
      begin
         if Lower <= Upper then
            Last := Last + 1;
            Result (Last) := (Lower, Upper);
         end if;
      end New_Range;
   begin
      for I in L'Range loop
         Index := 1;
         Start := L (I).Lower;

         while Index in R'Range and then R (Index).Lower <= L (I).Upper loop
            if R (Index) * L (I) then
               if R (Index).Lower /= 0 then
                  New_Range (Start, R (Index).Lower - 1);
               end if;

               Start := R (Index).Upper + 1;
            end if;

            Index := Index + 1;
         end loop;

         if Start /= 0 then
            New_Range (Start, L (I).Upper);
         end if;
      end loop;

      return (F.Controlled with new Set_Node'(Last, 1, Result (1 .. Last)));
   end "-";

   -----------
   -- "and" --
   -----------

   function "and" (Left, Right  : Symbol_Set) return Symbol_Set is
      L       : Symbol_Ranges renames Left.Node.Ranges;
      R       : Symbol_Ranges renames Right.Node.Ranges;
      Max_Len : constant Natural := L'Length + R'Length;  --  actual Max (R,L)
      Result  : Symbol_Ranges (1 .. Max_Len);
      Last    : Natural := 0;
   begin
      for I in L'Range loop
         for J in R'Range loop
            if R (J) * L (I) then
               Last := Last + 1;
               Result (Last) := R (J) and L (I);
            end if;
         end loop;
      end loop;

      return (F.Controlled with new Set_Node'(Last, 1, Result (1 .. Last)));
   end "and";

   ----------
   -- "or" --
   ----------

   function "or" (Left, Right  : Symbol_Set) return Symbol_Set is
      L       : Symbol_Ranges renames Left.Node.Ranges;
      R       : Symbol_Ranges renames Right.Node.Ranges;
      Max_Len : constant Natural := L'Length + R'Length;
      Result  : Symbol_Ranges (1 .. Max_Len);
      Last    : Positive := 1;
      I, J    : Positive := 1;

      procedure New_Range (R : Symbol_Range) is
      begin
         if Result (Last) * R then
            Result (Last) := Result (Last) or R;
         else
            Last := Last + 1;
            Result (Last) := R;
         end if;
      end New_Range;
   begin
      if L'Length = 0 then
         return Right;
      elsif R'Length = 0 then
         return Left;
      end if;

      Result (Last) := (Min (R (J).Lower, L (I).Lower),
                        Min (R (J).Lower, L (I).Lower));

      while I in L'Range or J in R'Range loop
         if I in L'Range then
            if J in R'Range then
               if R (J).Lower < L (I).Lower then
                  New_Range (R (J));
                  J := J + 1;
               else
                  New_Range (L (I));
                  I := I + 1;
               end if;
            else
               New_Range (L (I));
               I := I + 1;
            end if;
         else
            New_Range (R (J));
            J := J + 1;
         end if;
      end loop;

      return (F.Controlled with new Set_Node'(Last, 1, Result (1 .. Last)));
   end "or";

   ------------
   -- Adjust --
   ------------

   procedure Adjust (Object : in out Symbol_Set) is
   begin
      if Object.Node /= null then
         Object.Node.Count := Object.Node.Count + 1;
      end if;
   end Adjust;

   --------------------------
   -- Distinct_Symbol_Sets --
   --------------------------

   function Distinct_Symbol_Sets
     (Next : in Symbol_Set_Array) return Symbol_Set_Array is
   begin
      for I in Next'Range loop
         for J in I + 1 .. Next'Last loop
            if not Is_Empty (Next (I))
              and then not Is_Empty (Next (J))
              and then Next (I) * Next (J)
            then
               return Distinct_Symbol_Sets
                 (Next (Next'First .. I - 1)
                  & (Next (I) - Next (J))
                  & Next (I + 1 .. J - 1)
                  & (Next (J) - Next (I))
                  & Next (J + 1 .. Next'Last)
                  & (Next (J) and Next (I)));
            end if;
         end loop;
      end loop;

      declare
         Result : Symbol_Set_Array (Next'Range);
         Last   : Integer := Result'First - 1;
      begin
         for I in Next'Range loop
            if not Is_Empty (Next (I)) then
               Last := Last + 1;
               Result (Last) := Next (I);
            end if;
         end loop;

         return Result (Result'First .. Last);
      end;
   end Distinct_Symbol_Sets;

   --------------
   -- Finalize --
   --------------

   procedure Finalize (Object : in out Symbol_Set) is
      procedure Free is
         new Ada.Unchecked_Deallocation (Set_Node, Node_Access);
   begin
      if Object.Node /= null then
         Object.Node.Count := Object.Node.Count - 1;

         if Object.Node.Count = 0 then
            Free (Object.Node);
         end if;
      end if;
   end Finalize;

   ---------
   -- Min --
   ---------

   function Min (Left, Right : Symbol) return Symbol is
   begin
      if Left < Right then
         return Left;
      else
         return Right;
      end if;
   end Min;

   ---------
   -- Max --
   ---------

   function Max (Left, Right : Symbol) return Symbol is
   begin
      if Left > Right then
         return Left;
      else
         return Right;
      end if;
   end Max;

   --------------
   -- Is_Empty --
   --------------

   function Is_Empty (Left : Symbol_Set) return Boolean is
   begin
      return Left.Node.Length = 0;
   end Is_Empty;

   --------------
   -- Is_Equal --
   --------------

   function Is_Equal (Left, Right  : Symbol_Set)   return Boolean is
   begin
      return Left.Node.Ranges = Right.Node.Ranges;
   end Is_Equal;

   -----------------
   -- Range_Image --
   -----------------

   function Range_Image
     (Left   : Symbol_Set;
      Indent : String) return String
   is
      use Ada.Strings.Unbounded;
      L       : Symbol_Ranges renames Left.Node.Ranges;
      NL      : constant Character := ASCII.LF;
      Result  : Unbounded_String;
   begin
      Result := Indent & To_Unbounded_String ("when ");
      for I in L'Range loop
         if I /= L'First then
            Result := Result & NL & Indent & "  | ";
         end if;
         if L (I).Lower = L (I).Upper then
            Result := Result & Symbol'Image (L (I).Lower);
         else
            Result := Result
              & Symbol'Image (L (I).Lower) & " .."
              & Symbol'Image (L (I).Upper);
         end if;
      end loop;

      return To_String (Result);
   end Range_Image;

   --------------
   -- To_Range --
   --------------

   function To_Range (Single : Symbol) return Symbol_Set is
   begin
      return (F.Controlled with new Set_Node'(1, 1, (1 => (Single, Single))));
   end To_Range;

   --------------
   -- To_Range --
   --------------

   function To_Range (Some : Symbol_Array) return Symbol_Set is
      Result : Symbol_Set;
   begin
      for I in Some'Range loop
         Result := Result or To_Range (Some (I));
      end loop;

      return Result;
   end To_Range;

   --------------
   -- To_Range --
   --------------

   function To_Range (Lower, Upper : Symbol) return Symbol_Set is
   begin
      return (F.Controlled with new Set_Node'(1, 1, (1 => (Lower, Upper))));
   end To_Range;

end Symbols;

