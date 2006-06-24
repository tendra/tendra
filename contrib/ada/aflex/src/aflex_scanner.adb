
with PARSE_TOKENS, SCANNER; use PARSE_TOKENS, SCANNER; 

package body AFLEX_SCANNER is 
  function YYLEX return TOKEN is 
  begin
    return SCANNER.GET_TOKEN; 
  end YYLEX; 

end AFLEX_SCANNER; 
