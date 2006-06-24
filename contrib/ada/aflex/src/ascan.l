-- Copyright (c) 1990 Regents of the University of California.
-- All rights reserved.
--
-- This software was developed by John Self of the Arcadia project
-- at the University of California, Irvine.
--
-- Redistribution and use in source and binary forms are permitted
-- provided that the above copyright notice and this paragraph are
-- duplicated in all such forms and that any documentation,
-- advertising materials, and other materials related to such
-- distribution and use acknowledge that the software was developed
-- by the University of California, Irvine.  The name of the
-- University may not be used to endorse or promote products derived
-- from this software without specific prior written permission.
-- THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
-- IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
-- WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.

-- TITLE scanner specification file
-- AUTHOR: John Self (UCI)
-- DESCRIPTION regular expressions and actions matching tokens
--             that aflex expects to find in its input.
-- NOTES input to aflex (NOT alex.)  It uses exclusive start conditions
--       and case insensitive scanner generation available only in aflex
--       (or flex if you use C.)
--       generate scanner using the command 'aflex -is ascan.l'
-- $Header: /dc/uc/self/arcadia/aflex/ada/src/RCS/ascan.l,v 1.19 1991/12/03 23:08:24 self Exp self $ 

%x SECT2 SECT2PROLOG SECT3 PICKUPDEF SC CARETISBOL NUM QUOTE
%x FIRSTCCL CCL ACTION RECOVER BRACEERROR
%x ACTION_STRING

WS		[ \t\f]+
OPTWS		[ \t\f]*
NOT_WS		[^ \t\f\n]

NAME		[a-z_][a-z_0-9-]*
NOT_NAME	[^a-z_\n]+

SCNAME		{NAME}

ESCSEQ		\\([^\n]|[0-9]{1,3})

%%

^{WS}			{ indented_code := true; }
^#.*\n			{ linenum := linenum + 1; ECHO;
				-- treat as a comment;
			}
^{OPTWS}"--".*\n	{ linenum := linenum + 1; ECHO; }
^"%s"(tart)?		{ return ( SCDECL ); }
^"%x"			{ return ( XSCDECL ); }

{WS}			{ return ( WHITESPACE ); }

^"%%".*			{
			sectnum := 2;
			misc.line_directive_out;
			ENTER(SECT2PROLOG);
			return ( SECTEND );
			}

^"%"[^%sx]" ".*\n		{
			text_io.put( Standard_Error, "old-style lex command at line " );
			int_io.put( Standard_Error, linenum );
			text_io.put( Standard_Error, "ignored:" );
			text_io.new_line( Standard_Error );
			text_io.put( Standard_Error, ASCII.HT );
			text_io.put( Standard_Error, yytext(1..YYLength) );
			linenum := linenum + 1;
			}

^{NAME}			{
			nmstr := vstr(yytext(1..YYLength));
			didadef := false;
			ENTER(PICKUPDEF);
			}

{SCNAME}		{ nmstr := vstr(yytext(1..YYLength));
			  return NAME;
			}
^{OPTWS}\n		{ linenum := linenum + 1;
			  -- allows blank lines in section 1;
			}
{OPTWS}\n			{ linenum := linenum + 1; return Newline; }
.			{ misc.synerr( "illegal character" );ENTER(RECOVER);}

<PICKUPDEF>{WS}		{ null;
			  -- separates name and definition;
			}

<PICKUPDEF>{NOT_WS}.*	{
			nmdef := vstr(yytext(1..YYLength));

			i := tstring.len( nmdef );
			while ( i >= tstring.first ) loop
			    if ( (CHAR(nmdef,i) /= ' ') and
				 (CHAR(nmdef,i) /= ASCII.HT) ) then
				exit;
			    end if;
			    i := i - 1;
			end loop;

                        sym.ndinstal( nmstr,
				tstring.slice(nmdef, tstring.first, i) );
			didadef := true;
			}

<PICKUPDEF>\n		{
			if ( not didadef ) then
			    misc.synerr( "incomplete name definition" );
			end if;
			ENTER(0);
			linenum := linenum + 1;
			}

<RECOVER>.*\n		{ linenum := linenum + 1;
			  ENTER(0);
			  nmstr := vstr(yytext(1..YYLength));
			  return NAME;
			}

<SECT2PROLOG>.*\n/{NOT_WS}	{
			linenum := linenum + 1;
			ACTION_ECHO;
			MARK_END_OF_PROLOG;
			ENTER(SECT2);
			}

<SECT2PROLOG>.*\n	{ linenum := linenum + 1; ACTION_ECHO; }

<SECT2PROLOG><<EOF>>	{ MARK_END_OF_PROLOG;
			  return End_Of_Input;
			}

<SECT2>^{OPTWS}\n	{ linenum := linenum + 1;
			  -- allow blank lines in sect2;}
			
			-- this rule matches indented lines which
			-- are not comments.
<SECT2>^{WS}{NOT_WS}"--".*\n	{
			misc.synerr("indented code found outside of action");
			linenum := linenum + 1;
			}

<SECT2>"<"		{ ENTER(SC); return ( '<' ); }
<SECT2>^"^"		{ return ( '^' ); } 
<SECT2>\"		{ ENTER(QUOTE); return ( '"' ); }
<SECT2>"{"/[0-9]		{ ENTER(NUM); return ( '{' ); }
<SECT2>"{"[^0-9\n][^}\n]*	{ ENTER(BRACEERROR); }
<SECT2>"$"/[ \t\n]	{ return ( '$' ); }

<SECT2>{WS}"|".*\n	{ continued_action := true;
			  linenum := linenum + 1;
			  return Newline;
			}

<SECT2>^{OPTWS}"--".*\n	{ linenum := linenum + 1; ACTION_ECHO; }

<SECT2>{WS}		{
			-- this rule is separate from the one below because
			-- otherwise we get variable trailing context, so
			-- we can't build the scanner using -{f,F}

			bracelevel := 0;
			continued_action := false;
			ENTER(ACTION);
			return Newline;
			}

<SECT2>{OPTWS}/\n	{
			bracelevel := 0;
			continued_action := false;
			ENTER(ACTION);
			return Newline;
			}

<SECT2>^{OPTWS}\n	{ linenum := linenum + 1; return Newline; }

<SECT2>"<<EOF>>"	{ return ( EOF_OP ); }

<SECT2>^"%%".*		{
			sectnum := 3;
			ENTER(SECT3);
			return ( End_Of_Input );
			-- to stop the parser
			}

<SECT2>"["([^\\\]\n]|{ESCSEQ})+"]"	{

			nmstr := vstr(yytext(1..YYLength));

			-- check to see if we've already encountered this ccl
                        cclval := sym.ccllookup( nmstr );
			if ( cclval /= 0 ) then
			    yylval := cclval;
			    cclreuse := cclreuse + 1;
			    return ( PREVCCL );
			else
			    -- we fudge a bit.  We know that this ccl will
			    -- soon be numbered as lastccl + 1 by cclinit
			    sym.cclinstal( nmstr, lastccl + 1 );

			    -- push back everything but the leading bracket
			    -- so the ccl can be rescanned

			    PUT_BACK_STRING(nmstr, 1);

			    ENTER(FIRSTCCL);
			    return ( '[' );
			end if;
			}

<SECT2>"{"{NAME}"}"	{
			nmstr := vstr(yytext(1..YYLength));
			-- chop leading and trailing brace
			tmpbuf := slice(vstr(yytext(1..YYLength)),
								2, YYLength-1);

			nmdefptr := sym.ndlookup( tmpbuf );
			if ( nmdefptr = NUL ) then
			    misc.synerr( "undefined {name}" );
			else
			    -- push back name surrounded by ()'s
			    unput(')');
			    PUT_BACK_STRING(nmdefptr, 0);
			    unput('(');
			end if;
			}

<SECT2>[/|*+?.()]	{ tmpbuf := vstr(yytext(1..YYLength));
			  case tstring.CHAR(tmpbuf,1) is
				when '/' => return '/';
				when '|' => return '|';
				when '*' => return '*';
				when '+' => return '+';
				when '?' => return '?';
				when '.' => return '.';
				when '(' => return '(';
				when ')' => return ')';
				when others =>
					misc.aflexerror("error in aflex case");
			  end case;
			}
<SECT2>.		{ tmpbuf := vstr(yytext(1..YYLength));
			  yylval := CHARACTER'POS(CHAR(tmpbuf,1));
			  return CHAR;
			}
<SECT2>\n		{ linenum := linenum + 1; return Newline; }


<SC>","			{ return ( ',' ); }
<SC>">"			{ ENTER(SECT2); return ( '>' ); }
<SC>">"/"^"		{ ENTER(CARETISBOL); return ( '>' ); }
<SC>{SCNAME}		{ nmstr := vstr(yytext(1..YYLength));
			  return NAME;
			}
<SC>.			{ misc.synerr( "bad start condition name" ); }

<CARETISBOL>"^"		{ ENTER(SECT2); return ( '^' ); }


<QUOTE>[^"\n]		{ tmpbuf := vstr(yytext(1..YYLength));
			  yylval := CHARACTER'POS(CHAR(tmpbuf,1));
			  return CHAR;
			}
<QUOTE>\"		{ ENTER(SECT2); return ( '"' ); }

<QUOTE>\n		{
			misc.synerr( "missing quote" );
			ENTER(SECT2);
			linenum := linenum + 1;
			return ( '"' );
			}


<FIRSTCCL>"^"/[^-\n]	{ ENTER(CCL); return ( '^' ); }
<FIRSTCCL>"^"/-		{ return ( '^' ); }
<FIRSTCCL>-		{ ENTER(CCL); yylval := CHARACTER'POS('-'); return ( CHAR ); }
<FIRSTCCL>.		{ ENTER(CCL);
			  tmpbuf := vstr(yytext(1..YYLength));
			  yylval := CHARACTER'POS(CHAR(tmpbuf,1));
			  return CHAR;
			}

<CCL>-/[^\]\n]		{ return ( '-' ); }
<CCL>[^\]\n]		{ tmpbuf := vstr(yytext(1..YYLength));
			  yylval := CHARACTER'POS(CHAR(tmpbuf,1));
			  return CHAR;
			}
<CCL>"]"		{ ENTER(SECT2); return ( ']' ); }


<NUM>[0-9]+		{
			yylval := misc.myctoi( vstr(yytext(1..YYLength)) );
			return ( NUMBER );
			}

<NUM>","			{ return ( ',' ); }
<NUM>"}"			{ ENTER(SECT2); return ( '}' ); }

<NUM>.			{
			misc.synerr( "bad character inside {}'s" );
			ENTER(SECT2);
			return ( '}' );
			}

<NUM>\n			{
			misc.synerr( "missing }" );
			ENTER(SECT2);
			linenum := linenum + 1;
			return ( '}' );
			}


<BRACEERROR>"}"		{ misc.synerr( "bad name in {}'s" ); ENTER(SECT2); }
<BRACEERROR>\n		{ misc.synerr( "missing }" );
			  linenum := linenum + 1;
			  ENTER(SECT2);
			}

<ACTION>"{"		{ bracelevel := bracelevel + 1; }
<ACTION>"}"		{ bracelevel := bracelevel - 1; }
<ACTION>[^a-z_{}"'/\n]+	{ ACTION_ECHO; }
<ACTION>{NAME}		{ ACTION_ECHO; }
<ACTION>"--".*\n	{ linenum := linenum + 1; ACTION_ECHO; }
<ACTION>"'"([^'\\\n]|\\.)*"'"	{ ACTION_ECHO;
				  -- character constant;
			}

<ACTION>\"		{ ACTION_ECHO; ENTER(ACTION_STRING); }

<ACTION>\n		{
			linenum := linenum + 1;
			ACTION_ECHO;
			if ( bracelevel = 0 ) then
			    text_io.new_line ( temp_action_file );
			    ENTER(SECT2);
	                end if;
			}
<ACTION>.		{ ACTION_ECHO; }

<ACTION_STRING>[^"\\\n]+	{ ACTION_ECHO; }
<ACTION_STRING>\\.	{ ACTION_ECHO; }
<ACTION_STRING>\n	{ linenum := linenum + 1; ACTION_ECHO; }
<ACTION_STRING>\"	{ ACTION_ECHO; ENTER(ACTION); }
<ACTION_STRING>.	{ ACTION_ECHO; }


<SECT2,QUOTE,CCL>{ESCSEQ}	{
			yylval := CHARACTER'POS(misc.myesc( vstr(yytext(1..YYLength)) ));
			return ( CHAR );
			}

<FIRSTCCL>{ESCSEQ}	{
			yylval := CHARACTER'POS(misc.myesc( vstr(yytext(1..YYLength)) ));
			ENTER(CCL);
			return ( CHAR );
			}


<SECT3>.*(\n?)		{ if ( check_yylex_here ) then
				return End_Of_Input;
			  else
				ECHO;
			  end if;
			}
%%

with misc_defs, misc, sym, parse_tokens, int_io;
with tstring, ascan_dfa, ascan_io, external_file_manager;
use misc_defs, parse_tokens, tstring;
use ascan_dfa, ascan_io, external_file_manager;

package scanner is
    call_yylex : boolean := false;
    function get_token return Token;
end scanner;

package body scanner is

beglin : boolean := false;
i, bracelevel: integer;

function get_token return Token is
    toktype : Token;
    didadef, indented_code : boolean;
    cclval : integer;
    nmdefptr : vstring;
    nmdef, tmpbuf : vstring;

procedure ACTION_ECHO is
begin
    text_io.put( temp_action_file, yytext(1..YYLength) );
end ACTION_ECHO;

procedure MARK_END_OF_PROLOG is
begin
     text_io.put( temp_action_file, "%%%% end of prolog" );
     text_io.new_line( temp_action_file );
end MARK_END_OF_PROLOG;

procedure PUT_BACK_STRING(str : vstring; start : integer) is
begin
	for i in reverse start+1..tstring.len(str) loop
	    unput( CHAR(str,i) );
	end loop;
end PUT_BACK_STRING;

function check_yylex_here return boolean is
begin
	return ( (yytext'length >= 2) and then
			((yytext(1) = '#') and (yytext(2) = '#')));
end check_yylex_here;

##
begin
    if (call_yylex) then
    	toktype := YYLex;
    	call_yylex := false;
    	return toktype;
    end if;

    if ( eofseen ) then
	toktype := End_Of_Input;
    else
	toktype := YYLex;
    end if;
-- this tracing code allows easy tracing of aflex runs
if (trace) then
text_io.new_line(Standard_Error);
text_io.put(Standard_Error, "toktype = :" );
text_io.put(Standard_Error, Token'image(toktype));
text_io.put_line(Standard_Error, ":" );
end if;

    if ( toktype = End_Of_Input ) then
	eofseen := true;

	if ( sectnum = 1 ) then
	    misc.synerr(  "unexpected EOF" );
	    sectnum := 2;
	    toktype := SECTEND;
	else
	    if ( sectnum = 2 ) then
	    	sectnum := 3;
	    	toktype := SECTEND;
	    end if;
    	end if;
    end if;
    
    if ( trace ) then
	if ( beglin ) then
	    int_io.put( Standard_Error, num_rules + 1 );
	    text_io.put( Standard_Error, ASCII.HT );
	    beglin := false;
    	end if;

	case toktype is
	    when '<' | '>'|'^'|'$'|'"'|'['|']'|'{'|'}'|'|'|'('|
    	    	 ')'|'-'|'/'|'?'|'.'|'*'|'+'|',' =>
		text_io.put( Standard_Error, Token'image(toktype) );

	    when NEWLINE =>
		text_io.new_line(Standard_Error);
		if ( sectnum = 2 ) then
		    beglin := true;
    	    	end if;

	    when SCDECL =>
		text_io.put( Standard_Error, "%s" );

	    when XSCDECL =>
   		text_io.put( Standard_Error, "%x" );

	    when WHITESPACE =>
       		text_io.put( Standard_Error, " " );

	    when SECTEND =>
       		text_io.put_line( Standard_Error, "%%" );	   

		-- we set beglin to be true so we'll start
		-- writing out numbers as we echo rules.  aflexscan() has
		-- already assigned sectnum

		if ( sectnum = 2 ) then
		    beglin := true;
    	    	end if;

	    when NAME =>
		text_io.put( Standard_Error, ''' );
		text_io.put( Standard_Error, YYText);
		text_io.put( Standard_Error, ''' );

	    when CHAR =>
	    	if ( (yylval < CHARACTER'POS(' ')) or
		     (yylval = CHARACTER'POS(ASCII.DEL)) ) then
		    text_io.put( Standard_Error, '\' );
		    int_io.put( Standard_Error, yylval );
    		    text_io.put( Standard_Error, '\' );
		else
		    text_io.put( Standard_Error, Token'image(toktype) );
    	    	end if;

	    when NUMBER =>
    	    	int_io.put( Standard_Error, yylval );

	    when PREVCCL =>
		text_io.put( Standard_Error, '[' );
   	    	int_io.put( Standard_Error, yylval );
		text_io.put( Standard_Error, ']' );		

    	    when End_Of_Input =>
    	    	text_io.put( Standard_Error, "End Marker" );

	    when others =>
	    	text_io.put( Standard_Error, "Something weird:" );
		text_io.put_line( Standard_Error, Token'image(toktype));
    	end case;
    end if;
	    
    return toktype;

end get_token;
end scanner;
