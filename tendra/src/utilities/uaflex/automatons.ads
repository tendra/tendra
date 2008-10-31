with Symbols;
with Positions;

package Automatons is

   type State is private;
   type Token is new Natural;

   Not_A_Token : constant Token := 0;

   type DFA is private;

   procedure Need_State
     (Automaton : in out DFA;
      S         :    out State;
      Set       : in out Positions.Set;
      Start     : in     Natural := 0);

   procedure Add_Edge
     (Automaton : in out DFA;
      From      : in     State;
      To        : in     State;
      Set       : in     Symbols.Symbol_Set);

   function Has_More (Automaton : in DFA) return Boolean;

   procedure Get_Next
     (Automaton : in out DFA;
      S         :    out State;
      Set       :    out Positions.Set);

   procedure Set_Token
     (Automaton : in out DFA;
      S         : in     State;
      Target    : in     Token);

   procedure Clear_All_Sets (Automaton : in out DFA);

   procedure Delete (Automaton : in out DFA);

private

   type State is new Natural;

   type Edge;
   type Edge_Access is access all Edge;

   type Edge is record
      Next   : aliased Edge_Access;
      Jump   : State;
      Symbol : Symbols.Symbol_Set;
   end record;

   type State_Info is record
      Set    : Positions.Set;
      Edge   : aliased Edge_Access;
      Target : Token   := Not_A_Token;
      Start  : Natural := 0;
   end record;

   Length : constant State := 1024;
   type State_Array is array (State range 1 .. Length) of State_Info;

   type Node;
   type DFA is access all Node;

   type Node is record
      First  : State;
      Last   : State;
      Marked : State;
      Next   : DFA;
      States : State_Array;
   end record;

   -- Child access methods

   function Last_State (Automaton : DFA) return State;

   function Get_Token
     (Automaton : DFA;
      S         : State) return Token;

   function Get_Start
     (Automaton : DFA;
      S         : State) return Natural;

   function Edges
     (Automaton : DFA;
      S         : State) return Natural;

   function Edge_Symbols
     (Automaton : DFA;
      S         : State;
      Edge      : Positive) return Symbols.Symbol_Set;

   function Edge_Jump
     (Automaton : DFA;
      S         : State;
      Edge      : Positive) return State;

   procedure Create_State
     (Automaton : in out DFA;
      S         :    out State;
      Set       : in     Positions.Set := Positions.Empty_Set;
      Start     : in     Natural := 0);

end Automatons;
