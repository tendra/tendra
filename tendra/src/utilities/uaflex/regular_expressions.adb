package body Regular_Expressions is

   ----------------
   -- Add_To_DFA --
   ----------------

   procedure Add_To_DFA
     (Result   : in out Automatons.DFA;
      Item     : in     Expression;
      Starting : in     Positive)
   is
      use Symbols;
      use Positions;
      use Automatons;

      type Literal_Array is
        array (Position range <>) of Expression;
      type Set_Array is
        array (Position range <>) of Set;

      procedure Walk
        (Item  : in     Expression;
         First : in out Set;
         Last  : in out Set;
         Pos   : in out Position);

      procedure Add_To_Follow
        (First : in Set;
         Last  : in Set);

      procedure Get_State
        (Automaton : in out DFA;
         S         :    out State;
         Pos       : in out Set;
         Starting  : in     Natural := 0);

      function Get_Follow (Object : Set) return Set;
      function Get_Follow
        (Object : in Set;
         Symbol : in Symbol_Set) return Set;

      function Distinct (Element : Iterator) return Symbol_Set_Array;

      Count    : constant Position := Position (Literal_Count (Item));
      Literals : Literal_Array (1 .. Count);
      Follow   : Set_Array (1 .. Count);
      First    : Set;
      Last     : Set;
      Temp     : Position := 1;

      -------------------
      -- Add_To_Follow --
      -------------------

      procedure Add_To_Follow
        (First : in Set;
         Last  : in Set)
      is
         Element : Iterator := Start (Last);
      begin
         while Exist (Element) loop
            Add (Follow (+Element), First);
            Element := Next (Element);
         end loop;
      end Add_To_Follow;

      --------------
      -- Distinct --
      --------------

      function Distinct (Element : Iterator) return Symbol_Set_Array is

         function Count return Natural is
            Iter   : Iterator := Element;
            Result : Natural := 0;
         begin
            while Exist (Iter) loop
               Result := Result + 1;
               Iter := Next (Iter);
            end loop;

            return Result;
         end Count;

         Iter   : Iterator := Element;
         Index  : Natural  := 1;
         Result : Symbol_Set_Array (1 .. Count);
      begin
         while Exist (Iter) loop
            Result (Index) := Literals (+Iter).Chars;
            Index          := Index + 1;
            Iter           := Next (Iter);
         end loop;

         return Distinct_Symbol_Sets (Result);
      end Distinct;

      ----------------
      -- Get_Follow --
      ----------------

      function Get_Follow (Object : Set) return Set is
         Result  : Set;
         Element : Iterator := Start (Object);
      begin
         while Exist (Element) loop
            Add (Result, Follow (+Element));
            Element := Next (Element);
         end loop;

         return Result;
      end Get_Follow;

      ----------------
      -- Get_Follow --
      ----------------

      function Get_Follow
        (Object : in Set;
         Symbol : in Symbol_Set) return Set
      is
         Result  : Set;
         Element : Iterator := Start (Object);
      begin
         while Exist (Element) loop
            if Literals (+Element).Chars * Symbol then
               Add (Result, Follow (+Element));
            end if;

            Element := Next (Element);
         end loop;

         return Result;
      end Get_Follow;

      ---------------
      -- Get_State --
      ---------------

      procedure Get_State
        (Automaton : in out DFA;
         S         :    out State;
         Pos       : in out Set;
         Starting  : in     Natural := 0)
      is
         Element : Iterator := Start (Pos);
         Target  : Natural := 0;
      begin
         while Exist (Element) loop
            if Literals (+Element).Token > Target then
               Target := Literals (+Element).Token;
            end if;

            Element := Next (Element);
         end loop;

         Need_State (Automaton, S, Pos, Starting);
         Set_Token (Automaton, S, Token (Target));
      end Get_State;

      ----------
      -- Walk --
      ----------

      procedure Walk
        (Item  : in     Expression;
         First : in out Set;
         Last  : in out Set;
         Pos   : in out Position)
      is
         Result_First : Set;
         Result_Last  : Set;
      begin
         case Item.Kind is
            when Literal =>
               Literals (Pos) := Item;
               Add (First, Pos);
               Add (Last, Pos);
               Pos := Pos + 1;

            when Alternative =>
               Walk (Item.Left, First, Last, Pos);
               Walk (Item.Right, First, Last, Pos);

            when Sequence =>
               Walk (Item.Left, First, Result_Last, Pos);
               Walk (Item.Right, Result_First, Last, Pos);
               Add_To_Follow (Result_First, Result_Last);

               if Item.Left.Nullable then
                  Add (First, Result_First);
               end if;

               if Item.Right.Nullable then
                  Add (Last, Result_Last);
               end if;

               Clear (Result_First);
               Clear (Result_Last);

            when Iteration =>
               Walk (Item.Item, Result_First, Result_Last, Pos);
               Add_To_Follow (Result_First, Result_Last);
               Add (First, Result_First);
               Add (Last, Result_Last);

            when Optional | Apply =>
               Walk (Item.Child, First, Last, Pos);
         end case;
      end Walk;

      Current : State;
   begin
      Walk (Item, First, Last, Temp);
      Clear (Last);
      Clear_All_Sets (Result);
      Get_State (Result, Current, First, Starting);

      while Has_More (Result) loop
         Get_Next (Result, Current, First);

         declare
            Symbols : Symbol_Set_Array := Distinct (Start (First));
         begin
            for I in Symbols'Range loop
               declare
                  X    : Set := Get_Follow (First, Symbols (I));
                  Next : State;
                  Item : Iterator := Start (X);
               begin
                  if Exist (Item) then
                     Get_State (Result, Next, X);
                     Add_Edge (Result, Current, Next, Symbols (I));
                  end if;
               end;
            end loop;
         end;
      end loop;
   end Add_To_DFA;

   -------------------
   -- Literal_Count --
   -------------------

   function Literal_Count (Item : Expression) return Natural is
   begin
      case Item.Kind is
         when Literal =>
            return 1;
         when Alternative | Sequence =>
            return Literal_Count (Item.Left) + Literal_Count (Item.Right);
         when Iteration =>
            return Literal_Count (Item.Item);
         when Optional | Apply =>
            return Literal_Count (Item.Child);
      end case;
   end Literal_Count;

   ---------------------
   -- New_Alternative --
   ---------------------

   function New_Alternative
     (Left  :  Expression;
      Right :  Expression)
      return Expression
   is
      Result : Expression := new Expression_Node (Alternative);
   begin
      Result.Nullable := Left.Nullable or Right.Nullable;
      Result.Left := Left;
      Result.Right := Right;
      return Result;
   end New_Alternative;

   ---------------
   -- New_Apply --
   ---------------

   function New_Apply
     (Item       : Expression)
      return Expression
   is
      Result : Expression := new Expression_Node (Apply);
   begin
      Result.Nullable := Item.Nullable;
      Result.Child := Item;
      return Result;
   end New_Apply;

   -------------------
   -- New_Iteration --
   -------------------

   function New_Iteration
     (Item       : Expression;
      Allow_Zero : Boolean := True)
      return Expression
   is
      Result : Expression := new Expression_Node (Iteration);
   begin
      Result.Nullable := Item.Nullable or Allow_Zero;
      Result.Item := Item;
      Result.Allow_Zero := Allow_Zero;
      return Result;
   end New_Iteration;

   -----------------
   -- New_Literal --
   -----------------

   function New_Literal
     (S     : Symbol_Set)
      return Expression
   is
      Result : Expression := new Expression_Node (Literal);
   begin
      Result.Nullable := False;
      Result.Chars := S;
      return Result;
   end New_Literal;

   ------------------
   -- New_Optional --
   ------------------

   function New_Optional
     (Item       : Expression)
      return Expression
   is
      Result : Expression := new Expression_Node (Optional);
   begin
      Result.Nullable := True;
      Result.Child := Item;
      return Result;
   end New_Optional;

   --------------
   -- New_Rule --
   --------------

   function New_Rule (Item  : Expression;
                      Token : Natural) return Expression
   is
      Result : Expression := new Expression_Node (Literal);
   begin
      Result.Nullable := False;
      Result.Chars := To_Range (Not_A_Symbol);
      Result.Token := Token;
      return New_Sequence (Item, Result);
   end New_Rule;

   ------------------
   -- New_Sequence --
   ------------------

   function New_Sequence
     (Left  :  Expression;
      Right :  Expression)
      return Expression
   is
      Result : Expression := new Expression_Node (Sequence);
   begin
      Result.Nullable := Left.Nullable and Right.Nullable;
      Result.Left := Left;
      Result.Right := Right;
      return Result;
   end New_Sequence;

end Regular_Expressions;

