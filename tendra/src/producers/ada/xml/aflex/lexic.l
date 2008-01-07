identifier_letter ([a-zA-Z])
digit             ([0-9])
letter_or_digit   ({identifier_letter}|{digit})
decimal_literal   ({numeral}("."{numeral})?({exponent})?)
numeral           ({digit}("_"?{digit})*)
exponent          (([Ee]"+"?{numeral})|([Ee]"-"{numeral}))
a_based_literal   ({base}"#"{based_numeral}("."{based_numeral})?"#"{exponent}?)
b_based_literal   ({base}":"{based_numeral}("."{based_numeral})?":"{exponent}?)
based_literal     ({a_based_literal}|{b_based_literal})
base              ({numeral})
based_numeral     ({extended_digit}("_"?{extended_digit})*)
extended_digit    ({digit}|[A-Fa-f])
a_string_element  ((\"\")|[^"])
a_string_literal  (\"{a_string_element}*\")
b_string_element  ("%%"|[^"%])
b_string_literal  ("%"{b_string_element}*"%")
string_literal    ({a_string_literal}|{b_string_literal})
%%
({identifier_letter}("_"?{letter_or_digit})*) { Advance_Text; return Identifier_Token;}
({decimal_literal}|{based_literal})           { Advance_Text; return Choose_Numeric_Literal;}
"!"                                           { Advance (1);  return Vertical_Line_Token;}
({string_literal})                            { Advance_Text; return String_Literal_Token;}
"--".*                                        { Comment; }
[ \a\b\f\r\t\v]                               { Advance (1); }
[\n]                                          { Advance_New_Line; }
'.'                                           { 
   -------------------------------------------------
   --  Check if it's qualified expression. Example:
   --  Character'('A')
   --  '(' isn't character literal
   -------------------------------------------------

      if Last_Token = Identifier_Token then
         Advance (1);
         yyless (1);
         return Apostrophe_Token;
      else
         Advance (3);
         return Character_Literal_Token;
      end if;
}

%%
with Parser.Tokens;

##

   procedure Set_Input (File_Name : in String);
   procedure Close;

   subtype Token is Parser.Tokens.Token;

   function Get_Token return Token;
   function Get_Token_Value    return Wide_String;
   function Get_Current_Line   return Positive;
   function Get_Current_Column return Positive;

   End_Of_Input : Token renames Parser.Tokens.End_Of_Input;

##
with Ada.Strings.Fixed;
with Ada.Characters.Handling;
with Parser.Tokens;              use Parser.Tokens;
with Text_IO;                    use Text_IO;
##

   procedure Advance (Columns : in Positive);
   procedure Advance_New_Line;
   procedure Advance_Text;
   procedure Comment;
   function  Choose_Numeric_Literal return Token;

   Current_Line   : Positive;
   Current_Column : Positive;
   Last_Token     : Token;

   procedure Set_Input (File_Name : in String) is
   begin
      Lexer_IO.Open_Input (File_Name);
      Lexer_IO.Create_Output;
      Current_Line   := 1;
      Current_Column := 1;
   end Set_Input;

   procedure Close is
   begin
      Lexer_IO.Close_Input;
   end Close;

   procedure Advance (Columns : in Positive) is
   begin
      Current_Column := Current_Column + Columns;
   end Advance;

   procedure Advance_New_Line is
   begin
      Current_Line   := Current_Line + 1;
      Current_Column := 1;
   end Advance_New_Line;

   procedure Advance_Text is
   begin
      Current_Column := Current_Column + YYLength;
   end Advance_Text;

   procedure Comment is
   begin
      null;
   end Comment;

   function Get_Current_Line return Positive is
   begin
      return Current_Line;
   end Get_Current_Line;

   function Get_Current_Column return Positive is
   begin
      return Current_Column;
   end Get_Current_Column;

   function Get_Token_Value return Wide_String is
      use Ada.Characters.Handling;
   begin
      return To_Wide_String (YYText);
   end Get_Token_Value;

##

   function Get_Token return Token is
   begin
      Last_Token := YYLex;
      return Last_Token;
   end Get_Token;

   function  Choose_Numeric_Literal return Token is
      use Ada.Strings.Fixed;
   begin
      if Index (YYText, ".") = 0 then
         return Integer_Literal_Token;
      else
         return Real_Literal_Token;
      end if;
   end Choose_Numeric_Literal;

