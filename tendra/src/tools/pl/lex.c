/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:57:23 $
$Revision: 1.1.1.1 $
$Log: lex.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:23  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1995/09/05  16:27:49  currie
 * include files + 2r lex
 *
 * Revision 1.3  1995/08/15  16:14:38  currie
 * for build 4.0
 *
 * Revision 1.2  1995/06/08  09:13:51  currie
 * Added sigs to tokdecs/defs
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.3  1994/12/05  10:13:02  currie
 * Extended size of input buffer
 *
 * Revision 1.2  1994/07/21  10:36:20  currie
 * Added banner
 *
***********************************************************************/

#include "config.h"
#include "util.h"
#include "defs.h"
#include "includes.h"
#include "syntax.h"
#include "reserved.h"
#include "consfile.h"

typedef struct FStack_struct{ FILE * file; char * fname; unsigned long line;
				struct FStack_struct * next; } FStack;

static FStack * fstack = (FStack*)0;
LEX lex_v;
FILE * in_file;


char buff[BUFFLEN];
int bind = -1;

static char lexeme[BUFFLEN+1];
unsigned long cLINE = 0;
static char numstr[BUFFLEN+1];
int lnum;
long radix;


static void push_current
    PROTO_Z ()
{
    FStack * x = MALLOC(FStack);
    x->file = in_file; x->fname = file_name;
    x->line = cLINE; x->next = fstack;
    fstack = x;
}


static void pop_current
    PROTO_Z ()
{
    in_file = fstack->file; file_name = fstack->fname;
    cLINE = fstack->line;
    fstack = fstack->next;
}


static int directive
    PROTO_Z ()
{
    if (buff[0] == '#') {
	char c = buff[8];
   	buff[8] = 0;
   	if (strcmp(buff+1,"include")==0) {
	    push_current();
	    in_file = open_include(buff+9);
	    bind = -1;
	    cLINE = 0;
	    return 1;
   	}
   	buff[8] = c;
    }
    return 0;
}


static LEX symbol
    PROTO_N ( (s) )
    PROTO_T ( int s )
{
    LEX l;
    l.t = s;
    return l;
}


static int mygetc
    PROTO_Z ()
{
    while(bind<0 || buff[bind]==0) {
     	cLINE++;
	if (fgets(buff, BUFFLEN, in_file) == 0) {
	    if (fstack == (FStack *)0) return -1;
	    pop_current();
	} else {
	    if (directive()!=1) bind = 0;
	}
     }
     return(buff[bind++]);
}


static int string_char
    PROTO_N ( (q) )
    PROTO_T ( int q )
{
    int c = mygetc();
    switch (c) {
	case '\\': {
	    c = mygetc();
	    if (c=='t') return '\t';
	    if (c=='n') return '\n';
	    if (c=='r') return '\r';
	    return c;
	}
	case '"': {
	    if(q) return -1;
	    break ;
	}
    }
    return c;
}


static LEX charval
    PROTO_Z ()
{
    LEX l;
    l.t = lex_character;
    l.val.v = string_char(0);
    if (mygetc()!= '\'') fail("Unmatched quote");
    return l;
}


static LEX stringval
    PROTO_Z ()
{
    LEX l;
    l.t = lex_qstring;
    l.val.name = "";
    for(;;) {
	int i;
	for(i=0; i<BUFFLEN; i++) {
	    int c = string_char(1);
	    if (c<0) {
		lexeme[i] = 0;
		l.val.name = append_string(l.val.name, lexeme);
		return l;
	    }
	    lexeme[i]= (char)c;
	}
	lexeme[i] = 0;
	l.val.name = append_string(l.val.name, lexeme);
    }
}


static int terminator
    PROTO_N ( (x, number) )
    PROTO_T ( int x X int number )
{
    switch (x) {
  	case '(': case ')': case '[': case ']': case '{':
  	case '}': case ':': case ';': case ',': case ' ':
  	case 0: case '\t': case '\n': case '\'': case '"': case -1: {
	    return 1;
	}
  	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9': {
	    return number;
	}
    }
    return 0;
}


static LEX term_val
    PROTO_N ( (i) )
    PROTO_T ( int i )
{
    LEX l;
    l.t = terminals[i].t;
    l.val.name = terminals[i].name;
    return l;
}


static LEX cons_val
    PROTO_N ( (i) )
    PROTO_T ( int i )
{
    LEX l;
    l.t = constructs[i].t;
    l.val.v = i;
    return l;
}


static LEX id_val
    PROTO_N ( (id) )
    PROTO_T ( char * id )
{
    LEX l;
    l.t = lex_ident;
    l.val.name = copy_string(id);
    return l;
}


static LEX tok_val
    PROTO_N ( (td) )
    PROTO_T ( Tokdec * td )
{
    LEX l;
    int st = td->sort.ressort.sort;
    l.val.tokname = td;
    again:
    switch(st) {
	case access_sort: l.t = access_tok; break ;
	case alignment_sort: l.t = alignment_tok; break;
	case al_tag_sort: l.t = al_tag_tok; break;
	case bitfield_variety_sort: l.t = bitfield_variety_tok; break;
	case bool_sort: l.t = bool_tok; break;
	case error_treatment_sort: l.t = error_treatment_tok; break;
	case exp_sort: l.t =  exp_tok; break;
	case floating_variety_sort: l.t = floating_variety_tok; break ;
	case label_sort: l.t = label_tok; break;
	case nat_sort: l.t = nat_tok; break;
	case ntest_sort: l.t = ntest_tok; break ;
	case rounding_mode_sort: l.t =rounding_mode_tok; break;
	case shape_sort: l.t=shape_tok; break;
	case signed_nat_sort: l.t = signed_nat_tok; break ;
	case string_sort: l.t = string_tok; break;
	case tag_sort: l.t = tag_tok; break;
	case transfer_mode_sort: l.t = transfer_mode_tok; break;
	case variety_sort: l.t=variety_tok; break;
	case token_sort: {
	    st = td->sort.ressort.toksort->ressort.sort;
	    goto again;
	}
	default: fail("Not a legal sort"); break;
    }
    return l;
}


static LEX decode
    PROTO_N ( (id) )
    PROTO_T ( char * id )
{
    int lower = 0;
    int upper = no_of_terminals-1;
    int mid;
    int cl,cu,cm;
    Tokdec * td;

    cl = strcmp(terminals[lower].name, id);
    if (cl == 0) return term_val(lower);
    if (cl > 0) goto notterm;
    cu = strcmp(terminals[upper].name, id);
    if (cu == 0) return term_val(upper);
    if (cu < 0) goto notterm;
    while ( (mid = (upper+lower)/2), upper-lower > 1) {
	cm = strcmp(terminals[mid].name, id);
	if (cm == 0) return term_val(mid);
	if ((cm ^ cl) >= 0) {
	    lower = mid;
	} else if ((cm ^ cu) >= 0) {
	    upper = mid;
	} else {
	    break;
	}
    }

    notterm:
    lower = 0;
    upper = no_of_cons-1;
    cl = strcmp(constructs[lower].name, id);
    if (cl == 0) return cons_val(lower);
    if (cl > 0) goto notcons;
    cu = strcmp(constructs[upper].name, id);
    if (cu == 0) return cons_val(upper);
    if (cu < 0) goto notcons;
    while ( (mid = (upper+lower)/2), upper-lower > 1 ) {
	cm = strcmp(constructs[mid].name, id);
	if (cm == 0) return cons_val(mid);
	if ((cm ^ cl) >= 0) {
	    lower = mid;
	} else if ((cm ^ cu) >= 0) {
	    upper = mid;
	} else {
	    break;
	}
    }

    notcons:
    if (search_for_toks) {
	td = tokdecs;
	while(td != (Tokdec*)0) {
	    if (strcmp(id, td->idname.id)==0) {
		return tok_val(td);
	    }
	    td = td->next;
	}
    }
    return id_val(id);
}


char * fformat
    PROTO_N ( (s, l) )
    PROTO_T ( char * s X int l )
{
    int i;
    for(i=0; i<l; i++) {
  	char c = s[i];
	if (c>='a' && c<= 'f') {
	    s[i] = (char)(c-'a'+10+'0');
	} else if (c>='A' && c<= 'F') {
	    s[i] = (char)(c-'A'+10+'0');
	}
    }
    return s;
}


long stoi
    PROTO_N ( (s, n) )
    PROTO_T ( char * s X int n )
{
    long ans = 0;
    int i;
    for(i=0; i<n; i++) {
	int x = s[i];
  	int d = (x>='0' && x<='9')? x-'0':
  		(x>='a' && x<='f')? x-'a'+10: x-'A'+10;
  	ans = ans*radix+d;
    }
    return ans;
}


static LEX numval
    PROTO_N ( (c) )
    PROTO_T ( int c )
{
    int isfloat = 0;
    char x;
    LEX l;
    radix = 10;
    lnum = 0;
    for(;;) {
	numstr[lnum++]= (char)c;
	switch (x=buff[bind]) {
	    case '0': case '1': case '2': case '3': case '4':
	    case '5': case '6': case '7': case '8': case '9': {
		if(x-'0'>=radix) break;
		c = mygetc();
		continue;
	    }
	    case 'a': case 'b': case 'c':
	    case 'd': case 'e': case 'f': {
		if(x-'a'+10>=radix) break;
		c = mygetc();
		continue;
	    }
	    case 'A': case 'B': case 'C':
	    case 'D': case 'E': case 'F': {
		if(x-'A'+10>=radix) break;
		c = mygetc();
		continue;
	    }
	    case 'r': case 'R': {
		if (isfloat) break;
		radix = stoi(&numstr[0], lnum);
		lnum = 0;
		IGNORE mygetc();
		switch (x=buff[bind]) {
		    case '0': case '1': case '2': case '3': case '4':
		    case '5': case '6': case '7': case '8': case '9': {
			if(x-'0' < radix) {
			    c = mygetc();
			    continue;
			}
			break;
		    }
		    case 'a': case 'b': case 'c':
		    case 'd': case 'e': case 'f': {
			if(x-'a'+10< radix) {
			    c = mygetc();
			    continue;
			}
			break;
		    }
		}
		break;
	    }
	    case '.': {
		if (isfloat) break;
		isfloat=1;
		c=mygetc();
		continue;
	    }
        }
        break;
   }
   l.t = (isfloat)?lex_float__den:lex_int__den;
   l.val.name = &numstr[0];
   return l;
}


LEX reader
    PROTO_Z ()
{
    int c;
    int ll;

    again:
    switch (c = mygetc()) {
	case '(': return symbol(lex_ord);
  	case ')': return symbol(lex_crd);
  	case '[': return symbol(lex_osq);
  	case ']': return symbol(lex_csq);
  	case '{': return symbol(lex_ocurl);
  	case '}': return symbol(lex_ccurl);
  	case ':': return symbol(lex_colon);
  	case ';': return symbol(lex_semi);
  	case ',': return symbol(lex_comma);

  	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9': {
	    return numval(c);
	}

  	case ' ': case 0: case '\t': case '\n': case '\r': {
	    goto again;
	}

  	case '\'': return charval();
  	case '"' : return stringval();
  	case -1: return symbol(lex_eof);

	default: {
	    int number = (c=='-' || c=='.');
	    ll = 0;
	    while (ll < BUFFLEN){
     		lexeme[ll++] = (char)c;
     		if (terminator(buff[bind], number)) break;
     		number = 0;
     		c = mygetc();
	    }
	    lexeme[ll] = 0;
	    if (ll==1) {
		switch(c) {
		    case '=': return symbol(lex_equals);
		    case '|': return symbol(lex_bar);
		    case '.': return symbol(lex_point);
		    case '?': return symbol(lex_query);
		    case '#': return symbol(lex_hash);
		}
	    }
	    if (strcmp(&lexeme[0],"/*")==0) {
     		int n = 1;
     		for(;;) {
		    c = mygetc();
		    while (c=='*') {
			c = mygetc();
			if (c == '/') {
			    if (--n == 0) goto again;
			    c = mygetc();
			}
		    }
		    if (c=='/') {
			c = mygetc();
			if (c=='*') n++;
		    }
		}
	    }
	    return decode(lexeme);
	}
    }
}


void skip_term
    PROTO_N ( (c) )
    PROTO_T ( int c )
{
    if (lex_v.t != c) {
	char *s = "?" ;
	switch ( c ) {
	    case lex_osq : s = "[" ; break ;
	    case lex_csq : s = "]" ; break ;
	    case lex_ord : s = "(" ; break ;
	    case lex_crd : s = ")" ; break ;
	    case lex_comma : s = "," ; break ;
	}
	fail ( "Syntax error, '%s' expected", s ) ;
    }
    lex_v = reader() ;
}
