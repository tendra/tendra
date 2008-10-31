with Regular_Expressions; use Regular_Expressions;

package Macros is

   procedure Add
     (Name : String;
      Expr : Expression);

   function Find (Name : String) return Expression;

   Not_Found : exception;

end Macros;
