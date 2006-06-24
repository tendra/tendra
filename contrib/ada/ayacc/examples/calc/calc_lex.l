%% 
[A-Z]       { return IDENTIFIER; }
[a-z]       { return IDENTIFIER; }
[0-9]+      { return NUMBER; }
"**"        { return EXP; }
"("         { return '('; }
")"         { return ')'; }
"+"         { return '+'; }
"/"         { return '/'; }
"*"         { return '*'; }
"="         { return '='; }
"-"         { return '-'; }
\n          { return NEW_LINE; }
[\t ]+      { null;} 
%%
-- Added to the with list of SPEC
with calc.tokens; use  calc.tokens;
##
   function YYLex return Token;
##
--  Added to the with list of BODY
##
--  Added before YYLex start
##
--  Appended after YYLex end

