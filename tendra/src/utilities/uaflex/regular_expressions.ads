with Symbols;   use Symbols;
with Positions;
with Automatons;

package Regular_Expressions is

   type Expression is private;

   function New_Literal     (S     : Symbol_Set)
     return Expression;

   function New_Rule        (Item  : Expression;
                             Token : Natural)
     return Expression;

   function New_Alternative (Left  :  Expression;
                             Right :  Expression)
     return Expression;

   function New_Sequence    (Left  :  Expression;
                             Right :  Expression)
     return Expression;

   function New_Iteration   (Item       : Expression;
                             Allow_Zero : Boolean := True)
     return Expression;

   function New_Optional    (Item       : Expression)
     return Expression;

   function New_Apply       (Item       : Expression)
     return Expression;

   procedure Add_To_DFA
     (Result   : in out Automatons.DFA;
      Item     : in     Expression;
      Starting : in     Positive);

   Syntax_Error : exception;

private

   function Literal_Count (Item : Expression) return Natural;

   type Expression_Node;
   type Expression is access all Expression_Node;

   type Expression_Kind is
      (Literal, Alternative, Sequence, Iteration, Optional, Apply);

   type Expression_Node (Kind : Expression_Kind) is record
      Nullable : Boolean;
      case Kind is
         when Literal =>
            Chars : Symbol_Set;
            Token : Natural := 0;
         when Alternative | Sequence =>
            Left, Right : Expression;
         when Iteration =>
            Item       : Expression;
            Allow_Zero : Boolean;
         when Optional | Apply =>
            Child : Expression;
      end case;
   end record;

end Regular_Expressions;
