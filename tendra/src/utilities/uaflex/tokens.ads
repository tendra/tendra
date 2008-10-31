package Tokens is

   procedure Get_Token
     (Name   : in     String;
      Result :    out Positive);

   function Count return Natural;

   function Token_Name (Index : Positive) return String;

end Tokens;
