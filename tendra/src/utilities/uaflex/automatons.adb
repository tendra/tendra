with Ada.Unchecked_Deallocation;

package body Automatons is

   type Edge_Access_Access is access all Edge_Access;

   function Get_State
     (Automaton : in DFA;
      From      : in State)
     return Edge_Access_Access;

   Error : exception;

   --------------
   -- Add_Edge --
   --------------

   procedure Add_Edge
     (Automaton : in out DFA;
      From      : in     State;
      To        : in     State;
      Set       : in     Symbols.Symbol_Set)
   is
      use type Symbols.Symbol_Set;

      function Find_Prev
        (Ptr : in Edge_Access_Access;
         To  : in State) return Edge_Access_Access;

      function Find_Prev
        (Ptr : in Edge_Access_Access;
         To  : in State) return Edge_Access_Access
      is
      begin
         if Ptr.all = null then
            return Ptr;
         elsif Ptr.all.Jump <= To then
            return Ptr;
         else
            return Find_Prev (Ptr.all.Next'Access, To);
         end if;
      end Find_Prev;

      Ptr   : Edge_Access_Access := Get_State (Automaton, From);
      Next  : Edge_Access;
   begin
      Ptr := Find_Prev (Ptr, To);

      if Ptr.all /= null and then Ptr.all.Jump = To then
         Ptr.all.Symbol := Ptr.all.Symbol or Set;
      else
         Next        := new Edge;
         Next.Next   := Ptr.all;
         Next.Jump   := To;
         Next.Symbol := Set;
         Ptr.all     := Next;
      end if;
   end Add_Edge;

   ---------------------
   --  Clear_All_Sets --
   ---------------------

   procedure Clear_All_Sets (Automaton : in out DFA) is
   begin
      if Automaton /= null then
         for I in 1 .. Automaton.Last - Automaton.First + 1 loop
            Positions.Clear (Automaton.States (I).Set);
         end loop;

         Clear_All_Sets (Automaton.Next);
      end if;
   end Clear_All_Sets;

   ------------------
   -- Create_State --
   ------------------

   procedure Create_State
     (Automaton : in out DFA;
      S         :    out State;
      Set       : in     Positions.Set := Positions.Empty_Set;
      Start     : in     Natural := 0)
   is
      Temp : DFA;
   begin
      if Automaton = null
        or else Automaton.Last = Automaton.First + Length - 1
      then
         Temp := new Node;

         if Automaton = null then
            Temp.First := 1;
         else
            Temp.First := Automaton.Last + 1;
         end if;

         Temp.Last   := Temp.First - 1;
         Temp.Marked := Temp.Last;
         Temp.Next   := Automaton;
         Automaton   := Temp;
      end if;

      Automaton.Last := Automaton.Last + 1;
      S              := Automaton.Last;
      Automaton.States (S - Automaton.First + 1).Set   := Set;
      Automaton.States (S - Automaton.First + 1).Start := Start;
   end Create_State;

   ------------
   -- Delete --
   ------------

   procedure Delete (Automaton : in out DFA) is
      procedure Free is new Ada.Unchecked_Deallocation (Node, DFA);
   begin
      if Automaton /= null then
         for I in 1 .. Automaton.Last - Automaton.First + 1 loop
            Positions.Clear (Automaton.States (I).Set);
         end loop;

         Delete (Automaton.Next);
         Free (Automaton);
         Automaton := null;
      end if;
   end Delete;

   ------------------
   -- Edge_Symbols --
   ------------------

   function Edge_Symbols
     (Automaton : DFA;
      S         : State;
      Edge      : Positive) return Symbols.Symbol_Set
   is
      Ptr   : Edge_Access := Get_State (Automaton, S).all;
   begin
      for I in 2 .. Edge loop
         Ptr := Ptr.Next;
      end loop;

      return Ptr.Symbol;
   end Edge_Symbols;

   ---------------
   -- Edge_Jump --
   ---------------

   function Edge_Jump
     (Automaton : DFA;
      S         : State;
      Edge      : Positive) return State
   is
      Ptr   : Edge_Access := Get_State (Automaton, S).all;
   begin
      for I in 2 .. Edge loop
         Ptr := Ptr.Next;
      end loop;

      return Ptr.Jump;
   end Edge_Jump;

   -----------
   -- Edges --
   -----------

   function Edges
     (Automaton : DFA;
      S         : State) return Natural
   is
      Ptr   : Edge_Access := Get_State (Automaton, S).all;
      Count : Natural := 0;
   begin
      while Ptr /= null loop
         Ptr := Ptr.Next;
         Count := Count + 1;
      end loop;

      return Count;
   end Edges;

   --------------
   -- Get_Next --
   --------------

   procedure Get_Next
     (Automaton : in out DFA;
      S         :    out State;
      Set       :    out Positions.Set)
   is
   begin
      if Automaton.Next /= null and then Has_More (Automaton.Next) then
         Get_Next (Automaton.Next, S, Set);
      elsif Has_More (Automaton) then
         Automaton.Marked := Automaton.Marked + 1;
         S := Automaton.Marked;
         Set := Automaton.States (S - Automaton.First + 1).Set;
      else
         raise Error;
      end if;
   end Get_Next;

   ---------------
   -- Get_State --
   ---------------

   function Get_State
     (Automaton : in DFA;
      From      : in State)
     return Edge_Access_Access
   is
   begin
      if Automaton = null or else From > Automaton.Last then
         raise Error;
      elsif From < Automaton.First then
         return Get_State (Automaton.Next, From);
      else
         return Automaton.States (From - Automaton.First + 1).Edge'Access;
      end if;
   end Get_State;

   ---------------
   -- Get_Token --
   ---------------

   function Get_Token
     (Automaton : DFA;
      S         : State) return Token is
   begin
      if Automaton = null or else S > Automaton.Last then
         raise Error;
      elsif S < Automaton.First then
         return Get_Token (Automaton.Next, S);
      else
         return Automaton.States (S - Automaton.First + 1).Target;
      end if;
   end Get_Token;

   ---------------
   -- Get_Start --
   ---------------

   function Get_Start
     (Automaton : DFA;
      S         : State) return Natural is
   begin
      if Automaton = null or else S > Automaton.Last then
         raise Error;
      elsif S < Automaton.First then
         return Get_Start (Automaton.Next, S);
      else
         return Automaton.States (S - Automaton.First + 1).Start;
      end if;
   end Get_Start;

   --------------
   -- Has_More --
   --------------

   function Has_More (Automaton : in DFA) return Boolean is
   begin
      return Automaton.Marked < Automaton.Last;
   end Has_More;

   ----------------
   -- Last_State --
   ----------------

   function Last_State (Automaton : DFA) return State is
   begin
      if Automaton = null then
         return 0;
      else
         return Automaton.Last;
      end if;
   end Last_State;

   ----------------
   -- Need_State --
   ----------------

   procedure Need_State
     (Automaton : in out DFA;
      S         :    out State;
      Set       : in out Positions.Set;
      Start     : in     Natural := 0)
   is
      function Exist (Automaton : in DFA) return Boolean is
         use Positions;
      begin
         if Automaton = null then
            return False;
         end if;

         for I in 1 .. Automaton.Last - Automaton.First + 1 loop
            if Equal (Automaton.States (I).Set, Set) then
               S := Automaton.First + I - 1;
               Positions.Clear (Set);

               return True;
            end if;
         end loop;

         return Exist (Automaton.Next);
      end Exist;

   begin
      if not Exist (Automaton) then
         Create_State (Automaton, S, Set, Start);
      end if;
   end Need_State;

   ---------------
   -- Set_Token --
   ---------------

   procedure Set_Token
     (Automaton : in out DFA;
      S         : in     State;
      Target    : in     Token) is
   begin
      if Automaton = null or else S > Automaton.Last then
         raise Error;
      elsif S < Automaton.First then
         Set_Token (Automaton.Next, S, Target);
      else
         Automaton.States (S - Automaton.First + 1).Target := Target;
      end if;
   end Set_Token;

end Automatons;

