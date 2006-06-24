%token '(' ')' NUMBER IDENTIFIER NEW_LINE

%right     '='
%left      '+' '-' 
%left      '*' '/' 
%right     DUMMY
%nonassoc  EXP

{
type key_type is (cval, ival, noval); 

type yystype is record
  register : character;
  value    : integer; 
end record;
        
}

%% 

statements : statements statement 
           | 
           ;

statement  : expr end
               { put_line(integer'image($1.value)); }
           | error end 
               { put_line("Try again"); 
                 yyerrok; -- yyclearin;
               }
             statement
           ; 

expr       : id '=' expr 
               { registers($1.register) := $3.value; 
                 $$.value := $3.value; }
           | expr '+' expr 
               { $$.value :=  $1.value + $3.value; }
           | expr '-' expr 
               { $$.value :=  $1.value - $3.value; }
           | expr '*' expr 
               { $$.value :=  $1.value * $3.value; }
           | expr '/' expr 
               { $$.value :=  $1.value / $3.value; }
           | expr exp expr  
               { $$.value :=  integer(float($1.value) ** $3.value); }
           | '-' expr  %prec DUMMY 
               { $$.value := - $2.value; }
           | '(' expr ')' 
               { $$.value :=  $2.value; }
           | NUMBER
               { $$.value :=  character'pos(calc_lex_dfa.yytext(1)) -
		              character'pos('0'); } 
           | id 
	       { $$.value :=  registers($1.register); }
           ; 

id         : IDENTIFIER
               { $$.register := to_upper(calc_lex_dfa.yytext(1)); }
	   ;

end        : NEW_LINE
           | end_of_input 
           ;

%% --  next section will go before package statement in SPEC file

## --  next section will go after package statement in SPEC file 
   procedure YYParse;
## --  next section will go before package statement in BODY file
with calc_lex.dfa, calc_lex.IO, calc.error_report, Text_IO;
use  text_io, calc_lex, calc_lex.IO;
## --  next section will go after package statement in BODY file
    package calc_lex_dfa renames calc_lex.dfa;   
    package calc_lex_io  renames calc_lex.IO;   

    registers : array(Character'('A') .. Character'('Z')) of integer; 

    function to_upper(ch : in character) return character is
    begin
      if ch in 'a'..'z' then
	return character'val( character'pos(ch) - (character'pos('a') -
						   character'pos('A')) );
      else
	return ch;
      end if;
    end to_upper;

    procedure yyerror(s: string) is 
    begin 
        put_line(s); 
    end;
## --  yyparse will be inserted here follwed by the final section
--  Actually we just insert a comment for demonstration
