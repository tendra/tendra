--/*------------------------------------------------------------------------*/
--/* Lexical input for LEX for LALR(1) Grammar for ANSI Ada                 */
--/*                                                                        */
--/*              Herman Fischer                                            */
--/*            Litton Data Systems                                         */
--/*              March 26, 1984                                            */
--/*                                                                        */
--/* Accompanies Public Domain YACC format Ada grammar                      */
--/*                                                                        */
--/* Modified by:                                                           */
--/*              Scott McConnell and Gordan Doak                           */
--/*                  Rockwell International                                */
--/*                    400 Collins Road                                    */
--/*                   Cedar Rapids, Iowa                                   */
--/*                    November 20, 1992                                   */
--/*                                                                        */
--/*------------------------------------------------------------------------*/

%START IDENT Z

A		[aA]
B		[bB]
C		[cC]
D		[dD]
E		[eE]
F		[fF]
G		[gG]
H		[hH]
I		[iI]
J		[jJ]
K		[kK]
L		[lL]
M		[mM]
N		[nN]
O		[oO]
P		[pP]
Q		[qQ]
R		[rR]
S		[sS]
T		[tT]
U		[uU]
V		[vV]
W		[wW]
X		[xX]
Y		[yY]
Z		[zZ]

  -- GRAPHIC_CHAR contains all 95 graphic characters except ['].  This
  -- is used too match character literals. (See LRM 2.1, 2.5)

GRAPHIC_CHAR  [ !"#$%&()*+,-./0-9:;<=>?@A-Z\[\\\]^_`a-z{|}~]

  -- STRING_CHAR contains the 95 graphic characters except ["%]. This
  -- is used too match STRING_LITERALS. (See LRM 2.1, 2.6, 2.10)

STRING_CHAR   [ !#$&'()*+,-./0-9:;<=>?@A-Z\[\\\]^_`a-z{|}~]

  -- String literals with ["] as string brackets must use double quotes
  -- for nested quotes and match single percent signs.

STRING_INTERNALS1  ({STRING_CHAR}*[%]*(\"\")*)*

  -- String literals with [%] as string brackets can not contain ["]
  -- nested [%] must be duplicated. (See LRM 2.1, 2.6, 2.10)

STRING_INTERNALS2  ({STRING_CHAR}*(\%\%)*)*

  -- The following matchs all valid string literals. (See LRM 2.1, 2.6, 2.10).

STRING_LITERAL  ((\"{STRING_INTERNALS1}\")|(\%{STRING_INTERNALS2}\%))

  -- The following are used to match all numeric literals.  (See LRM 2.4).
  -- Note that double underscores are rejected.

DIGIT_SEQUENCE    [0-9]([_]?[0-9])*
HEX_SEQUENCE      [0-9a-fA-F]([_]?[0-9a-fA-F])*
EXPONENT          {E}[-+]?{DIGIT_SEQUENCE}
BASED_INTERNALS   {HEX_SEQUENCE}([.]{HEX_SEQUENCE})?

%%

  -- The following are used to match all the Ada reserved words.
  -- See Ada LRM 2.9

{A}{B}{O}{R}{T}			{ECHO_L; ENTER(Z); return(ABORT_TOKEN);}
{A}{B}{S}			{ECHO_L; ENTER(Z); return(ABS_TOKEN);}
{A}{C}{C}{E}{P}{T}		{ECHO_L; ENTER(Z); return(ACCEPT_TOKEN);}
{A}{C}{C}{E}{S}{S}		{ECHO_L; ENTER(Z); return(ACCESS_TOKEN);}
{A}{L}{L}			{ECHO_L; ENTER(IDENT); return(ALL_TOKEN);}
{A}{N}{D}			{ECHO_L; ENTER(Z); return(AND_TOKEN);}
{A}{R}{R}{A}{Y}			{ECHO_L; ENTER(Z); return(ARRAY_TOKEN);}
{A}{T}				{ECHO_L; ENTER(Z); return(AT_TOKEN);}
{B}{E}{G}{I}{N}			{ECHO_L; ENTER(Z); return(BEGIN_TOKEN);}
{B}{O}{D}{Y}			{ECHO_L; ENTER(Z); return(BODY_TOKEN);}
{C}{A}{S}{E}			{ECHO_L; ENTER(Z); return(CASE_TOKEN);}
{C}{O}{N}{S}{T}{A}{N}{T}	{ECHO_L; ENTER(Z); return(CONSTANT_TOKEN);}
{D}{E}{C}{L}{A}{R}{E}		{ECHO_L; ENTER(Z); return(DECLARE_TOKEN);}
{D}{E}{L}{A}{Y}			{ECHO_L; ENTER(Z); return(DELAY_TOKEN);}
{D}{E}{L}{T}{A}			{ECHO_L; ENTER(Z); return(DELTA_TOKEN);}
{D}{I}{G}{I}{T}{S}		{ECHO_L; ENTER(Z); return(DIGITS_TOKEN);}
{D}{O}				{ECHO_L; ENTER(Z); return(DO_TOKEN);}
{E}{L}{S}{E}			{ECHO_L; ENTER(Z); return(ELSE_TOKEN);}
{E}{L}{S}{I}{F}		     	{ECHO_L; ENTER(Z); return(ELSIF_TOKEN);}
{E}{N}{D}			{ECHO_L; ENTER(Z); return(END_TOKEN);}
{E}{N}{T}{R}{Y}		 	{ECHO_L; ENTER(Z); return(ENTRY_TOKEN);}
{E}{X}{C}{E}{P}{T}{I}{O}{N} 	{ECHO_L; ENTER(Z); return(EXCEPTION_TOKEN);}
{E}{X}{I}{T}			{ECHO_L; ENTER(Z); return(EXIT_TOKEN);}
{F}{O}{R}			{ECHO_L; ENTER(Z); return(FOR_TOKEN);}
{F}{U}{N}{C}{T}{I}{O}{N} 	{ECHO_L; ENTER(Z); return(FUNCTION_TOKEN);}
{G}{E}{N}{E}{R}{I}{C}		{ECHO_L; ENTER(Z); return(GENERIC_TOKEN);}
{G}{O}{T}{O}			{ECHO_L; ENTER(Z); return(GOTO_TOKEN);}
{I}{F}				{ECHO_L; ENTER(Z); return(IF_TOKEN);}
{I}{N}				{ECHO_L; ENTER(Z); return(IN_TOKEN);}
{I}{S}			      	{ECHO_L; ENTER(Z); return(IS_TOKEN);}
{L}{I}{M}{I}{T}{E}{D}		{ECHO_L; ENTER(Z); return(LIMITED_TOKEN);}
{L}{O}{O}{P}		      	{ECHO_L; ENTER(Z); return(LOOP_TOKEN);}
{M}{O}{D}			{ECHO_L; ENTER(Z); return(MOD_TOKEN);}
{N}{E}{W}		  	{ECHO_L; ENTER(Z); return(NEW_TOKEN);}
{N}{O}{T}	         	{ECHO_L; ENTER(Z); return(NOT_TOKEN);}
{N}{U}{L}{L}			{ECHO_L; ENTER(Z); return(NULL_TOKEN);}
{O}{F}			 	{ECHO_L; ENTER(Z); return(OF_TOKEN);}
{O}{R}		         	{ECHO_L; ENTER(Z); return(OR_TOKEN);}
{O}{T}{H}{E}{R}{S}		{ECHO_L; ENTER(Z); return(OTHERS_TOKEN);}
{O}{U}{T}			{ECHO_L; ENTER(Z); return(OUT_TOKEN);}
{P}{A}{C}{K}{A}{G}{E}	 	{ECHO_L; ENTER(Z); return(PACKAGE_TOKEN);}
{P}{R}{A}{G}{M}{A}		{ECHO_L; ENTER(Z); return(PRAGMA_TOKEN);}
{P}{R}{I}{V}{A}{T}{E}		{ECHO_L; ENTER(Z); return(PRIVATE_TOKEN);}
{P}{R}{O}{C}{E}{D}{U}{R}{E} 	{ECHO_L; ENTER(Z); return(PROCEDURE_TOKEN);}
{R}{A}{I}{S}{E}			{ECHO_L; ENTER(Z); return(RAISE_TOKEN);}
{R}{A}{N}{G}{E}			{ECHO_L; ENTER(Z); return(RANGE_TOKEN);}
{R}{E}{C}{O}{R}{D}	   	{ECHO_L; ENTER(Z); return(RECORD_TOKEN);}
{R}{E}{M}			{ECHO_L; ENTER(Z); return(REM_TOKEN);}
{R}{E}{N}{A}{M}{E}{S}		{ECHO_L; ENTER(Z); return(RENAMES_TOKEN);}
{R}{E}{T}{U}{R}{N}		{ECHO_L; ENTER(Z); return(RETURN_TOKEN);}
{R}{E}{V}{E}{R}{S}{E}		{ECHO_L; ENTER(Z); return(REVERSE_TOKEN);}
{S}{E}{L}{E}{C}{T}		{ECHO_L; ENTER(Z); return(SELECT_TOKEN);}
{S}{E}{P}{A}{R}{A}{T}{E}	{ECHO_L; ENTER(Z); return(SEPARATE_TOKEN);}
{S}{U}{B}{T}{Y}{P}{E}		{ECHO_L; ENTER(Z); return(SUBTYPE_TOKEN);}
{T}{A}{S}{K}			{ECHO_L; ENTER(Z); return(TASK_TOKEN);}
{T}{E}{R}{M}{I}{N}{A}{T}{E}	{ECHO_L; ENTER(Z); return(TERMINATE_TOKEN);}
{T}{H}{E}{N}			{ECHO_L; ENTER(Z); return(THEN_TOKEN);}
{T}{Y}{P}{E}			{ECHO_L; ENTER(Z); return(TYPE_TOKEN);}
{U}{S}{E}			{ECHO_L; ENTER(Z); return(USE_TOKEN);}
{W}{H}{E}{N}			{ECHO_L; ENTER(Z); return(WHEN_TOKEN);}
{W}{H}{I}{L}{E}			{ECHO_L; ENTER(Z); return(WHILE_TOKEN);}
{W}{I}{T}{H}			{ECHO_L; ENTER(Z); return(WITH_TOKEN);}
{X}{O}{R}			{ECHO_L; ENTER(Z); return(XOR_TOKEN);}

  -- Match all the compound Ada delimiters.  See Ada LRM 2.2.

"=>"    {ECHO_L; ENTER(Z); return(ARROW);}
".."    {ECHO_L; ENTER(Z); return(DOUBLE_DOT);}
"**"    {ECHO_L; ENTER(Z); return(DOUBLE_STAR);}
":="    {ECHO_L; ENTER(Z); return(ASSIGNMENT);}
"/="    {ECHO_L; ENTER(Z); return(INEQUALITY);}
">="    {ECHO_L; ENTER(Z); return(GREATER_THAN_OR_EQUAL);}
"<="    {ECHO_L; ENTER(Z); return(LESS_THAN_OR_EQUAL);}
"<<"    {ECHO_L; ENTER(Z); return(LEFT_LABEL_BRACKET);}
">>"    {ECHO_L; ENTER(Z); return(RIGHT_LABEL_BRACKET);}
"<>"    {ECHO_L; ENTER(Z); return(BOX);}

  -- Match all the Ada delimiters.  See Ada LRM 2.2.

"&"        {ECHO_L; ENTER(Z);     return('&');}
<IDENT>\'  {ECHO_L; ENTER(Z);     return(''');}
"("        {ECHO_L; ENTER(Z);     return('(');}
")"        {ECHO_L; ENTER(IDENT); return(')');}
"*"        {ECHO_L; ENTER(Z);     return('*');}
"+"        {ECHO_L; ENTER(Z);     return('+');}
","        {ECHO_L; ENTER(Z);     return(',');}
"-"        {ECHO_L; ENTER(Z);     return('-');}
"."        {ECHO_L; ENTER(Z);     return('.');}
"/"        {ECHO_L; ENTER(Z);     return('/');}
":"        {ECHO_L; ENTER(Z);     return(':');}
";"        {ECHO_L; ENTER(Z);     return(';');}
"<"        {ECHO_L; ENTER(Z);     return('<');}
"="        {ECHO_L; ENTER(Z);     return('=');}
">"        {ECHO_L; ENTER(Z);     return('>');}
"|"        {ECHO_L; ENTER(Z);     return('|');}
"!"        {ECHO_L; ENTER(Z);     return('!');}  -- See Ada LRM 2.10 (2)

  -- The following is used to match all valid Ada identifiers
  -- except reserved words. Note that leading digits and underscores
  -- are not allowed and that double underscores are not allowed.
  -- See Ada LRM 2.3.

[a-zA-Z]([_]?[a-zA-Z0-9])*       {ECHO_L; ENTER(IDENT);return(IDENTIFIER);}

  -- Numeric literals are made up of two types: Decimal Literals and
  -- Based Literals. See Ada LRM 2.4  Both are returned using the token
  -- name INTEGER_LITERAL in this example.

  -- The following matches all Decimal Literals. See Ada LRM 2.4.1.
  -- Semantic checks must be made to confirm that the literal is valid.
  -- However, only syntacticly valid Decimal Literals will be matched.

{DIGIT_SEQUENCE}([.]{DIGIT_SEQUENCE})?{EXPONENT}?  {
			      ECHO_L; ENTER(Z);
			      return(INTEGER_LITERAL);}

  -- The following matches all Based Literals. See Ada LRM 2.4.1.
  -- Semantic checks must be made to confirm that the literal is valid.
  -- However, only syntacticly valid Decimal Literals will be matched.
  -- It supports the use of colens in place of pound signs.
  -- Please note that a base of any Natural number will be matched Ada
  -- only allowes a base to have a range of 2 .. 16.

{DIGIT_SEQUENCE}([#]{BASED_INTERNALS}[#]|[:]{BASED_INTERNALS}[:]){EXPONENT}? {
			      ECHO_L; ENTER(Z);
			      return(INTEGER_LITERAL);}

  -- Match all valid character literals.  See Ada LRM 2.6.

<Z>\'({GRAPHIC_CHAR}\'|\'\')    {ECHO_L; ENTER(Z); return(CHARACTER_LITERAL);}

  -- Match all valid string literals.  See Ada LRM 2.6.

{STRING_LITERAL}                {ECHO_L; ENTER(Z); return(STRING_LITERAL);}

  -- The following is used to math a directive used to turn trace information
  -- on and off.  This helps in the debugging of the lexical analyzer.

"--".*    {ECHO_L;           -- ignore comments to end-of-line
            if YYTEXT = "--!TRACE" then
              Trace := not Trace;
            end if; }

  -- The following matches all whitespace.  Except for vertical tabs.  AFLEX,
  -- ALEX and LEX does not support vertical tabs.  This causes use to fail
  -- when parsing some of the ACVC Btests.

[ \r\t\f]+ {ECHO_L;}        -- ignore spaces,Carriage returns,tabs,form feeds

  -- The following matches all new lines.

[\n]       {ECHO_L; linenum;}

  -- The following matches everything else and prints an error message
  -- indicating that something unexpected was found.

.          {ECHO_L; 
            text_io.put_line("?? lexical error" & ada_lex_dfa.yytext & "??");
	    num_errors := num_errors + 1;}

%%
--  Added to the with list of SPEC
with ada_parse.tokens; 
use  ada_parse.tokens;
##  
  lines      : positive := 1;
  num_errors     : natural := 0;
  standard_error : text_io.file_type;
  Trace          : Boolean := False;

  procedure ECHO_L; --local version_of define_string.
  procedure linenum; 

  function yylex return token;
##
  --  Added to the with list of BODY
##
  --  Added before YYLex
##
  --  Appended after YYLex
  procedure ECHO_L is
  --
  -- Local version of the  define string.
  -- 
  begin
-----    if Trace then
-----      TEXT_IO.PUT_Line("Token :" & YYTEXT & ":");
-----    end if;
	text_io.put(yytext);
  end ECHO_L;


  procedure linenum is
    line_number_string : constant string :=
          integer'image ( lines + 1 );
  begin
    lines := lines + 1;
    put(line_number_string);
    for i in 1 .. 5 - integer ( line_number_string'length ) loop
      text_io.put(" ");
    end loop;

  end linenum;
