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


#include "config.h"
#include <ctype.h>
#include "types.h"
#include "file.h"
#include "high.h"
#include "names.h"
#include "node.h"
#include "shape.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"
#include "write.h"


/*
    FLAGS CONTROLLING OUTPUT OF TOKENS ETC

    The output is in the fully expanded form if verbose is true.  The
    shape of each expression is printed if print_shapes is true.  The
    flag func_output controls whether the output should be lisp-like
    (default) or c-like.
*/

boolean verbose = 0 ;
boolean print_shapes = 0 ;
boolean func_output = 0 ;


/*
    PRINT A NUMBER OF SPACES

    An indentation of d spaces is printed to the output file.
*/

void print_spaces
    PROTO_N ( ( d ) )
    PROTO_T ( int d )
{
    int n = 2 * d ;
    while ( n >= 8 ) {
	IGNORE fputc ( '\t', output ) ;
	n -= 8 ;
    }
    while ( n ) {
	IGNORE fputc ( ' ', output ) ;
	n-- ;
    }
    return ;
}


/*
    PRINT A NODE

    The node p is printed to the output file with an indentation of
    d spaces.
*/

static boolean print_node
    PROTO_N ( ( p, d ) )
    PROTO_T ( node *p X int d )
{
    boolean negate = 0 ;
    boolean newline = 0 ;
    while ( p ) {
	construct *q = p->cons ;
	sortname s = q->sortnum ;
	long m = q->encoding ;
	newline = 0 ;
	switch ( s ) {

	    case SORT_tdfbool : {
		/* Set neg for subsequent number */
		negate = ( boolean ) ( m ? 1 : 0 ) ;
		break ;
	    }

	    case SORT_bytestream : {
		/* Print a bytestream */
		newline = print_node ( p->son, d ) ;
		break ;
	    }

	    case SORT_completion : {
		/* Print a completion */
		newline = print_node ( p->son, d ) ;
		break ;
	    }

	    case SORT_small_tdfint : {
		/* Print a small number */
		long n = q->encoding ;
		print_spaces ( d ) ;
		if ( negate ) n = -n ;
		IGNORE fprintf ( output, "%ld", n ) ;
		negate = 0 ;
		newline = 1 ;
		break ;
	    }

	    case SORT_tdfint : {
		/* Print a number */
		char *num = q->name ;
		print_spaces ( d ) ;
		if ( fits_ulong ( num, 0 ) ) {
		    unsigned long n = octal_to_ulong ( num ) ;
		    if ( negate && n ) IGNORE fputc ( '-', output ) ;
		    IGNORE fprintf ( output, "%lu", n ) ;
		} else {
		    if ( negate ) IGNORE fputc ( '-', output ) ;
		    IGNORE fprintf ( output, "0%s", num ) ;
		}
		negate = 0 ;
		newline = 1 ;
		break ;
	    }

	    case SORT_option : {
		/* Print an optional argument */
		if ( p->son ) {
		    newline = print_node ( p->son, d ) ;
		} else {
		    print_spaces ( d ) ;
		    IGNORE fputc ( '-', output ) ;
		    newline = 1 ;
		}
		break ;
	    }

	    case SORT_repeat : {
		/* Print a repeated argument */
		if ( m == 0 ) {
		    print_spaces ( d ) ;
		    IGNORE fputc ( '|', output ) ;
		    newline = 1 ;
		} else {
		    newline = print_node ( p->son, d ) ;
		    if ( func_output ) IGNORE fputc ( ',', output ) ;
		    IGNORE fputs ( " |", output ) ;
		}
		break ;
	    }

	    case SORT_tdfstring : {
		/* Print a string */
		int i, n = ( int ) m ;
		print_spaces ( d ) ;
		if ( n == -1 ) {
		    char *f = ( func_output ? "%s (\n" : "( %s\n" ) ;
		    IGNORE fprintf ( output, f, MAKE_STRING ) ;
		    newline = print_node ( p->son, d + 1 ) ;
		    IGNORE fputs ( " )", output ) ;
		} else {
		    IGNORE fputc ( '"', output ) ;
		    for ( i = 0 ; i < n ; i++ ) {
			int c = ( ( q->name [i] ) & 0xff ) ;
			if ( isprint ( c ) ) {
			    if ( c == '\\' || c == '"' ) {
				IGNORE fputc ( '\\', output ) ;
			    }
			    IGNORE fputc ( c, output ) ;
			} else {
			    if ( c == '\n' ) {
				IGNORE fputs ( "\\n", output ) ;
			    } else if ( c == '\t' ) {
				IGNORE fputs ( "\\t", output ) ;
			    } else {
				unsigned co = ( unsigned ) c ;
				IGNORE fprintf ( output, "\\%03o", co ) ;
			    }
			}
		    }
		    IGNORE fputc ( '"', output ) ;
		    newline = 1 ;
		}
		break ;
	    }

	    case SORT_nat : {
		/* Print a nat */
		if ( m != ENC_make_nat ) goto default_label ;
		newline = print_node ( p->son, d ) ;
		break ;
	    }

	    case SORT_signed_nat : {
		/* Print a signed_nat */
		if ( m != ENC_make_signed_nat ) goto default_label ;
		newline = print_node ( p->son, d ) ;
		break ;
	    }

	    case SORT_string : {
		/* Print a string */
		if ( m != ENC_make_string ) goto default_label ;
		newline = print_node ( p->son, d ) ;
		break ;
	    }

	    case SORT_al_tag : {
		/* Print an alignment tag */
		if ( verbose || m != ENC_make_al_tag || p->son == null ) {
		    goto default_label ;
		}
		newline = print_node ( p->son, d ) ;
		break ;
	    }

	    case SORT_label : {
		/* Print a label */
		if ( verbose || m != ENC_make_label || p->son == null ) {
		    goto default_label ;
		}
		newline = print_node ( p->son, d ) ;
		break ;
	    }

	    case SORT_tag : {
		/* Print a tag */
		if ( verbose || m != ENC_make_tag || p->son == null ) {
		    goto default_label ;
		}
		newline = print_node ( p->son, d ) ;
		break ;
	    }

	    case SORT_exp : {
		static node special_node ;
		if ( print_shapes && p->shape != &special_node ) {
		    /* Change exp to show shape */
		    node *z = new_node () ;
		    z->cons = &exp_shape ;
		    z->bro = p->bro ;
		    z->son = p ;
		    if ( p->shape ) {
			z->son->bro = copy_node ( p->shape ) ;
		    } else {
			z->son->bro = new_node () ;
			z->son->bro->cons = &unknown_cons ;
		    }
		    p->shape = &special_node ;
		    p = z ;
		    q = p->cons ;
		    m = q->encoding ;
		}
		goto default_label ;
	    }

	    default : {
		/* Print a simple sort */
		default_label : {
		    if ( !verbose && m == sort_tokens [s] && p->son &&
			 p->son->cons->sortnum == SORT_token ) {
			newline = print_node ( p->son, d ) ;
		    } else {
			print_spaces ( d ) ;
			if ( p->son ) {
			    char *f = ( func_output ? "%s (\n" : "( %s\n" ) ;
			    IGNORE fprintf ( output, f, q->name ) ;
			    newline = print_node ( p->son, d + 1 ) ;
			    IGNORE fputs ( " )", output ) ;
			} else {
			    IGNORE fprintf ( output, "%s", q->name ) ;
			    newline = 1 ;
			}
		    }
		}
		break ;
	    }
	}
	p = p->bro ;
	if ( newline && p ) {
	    if ( func_output ) IGNORE fputc ( ',', output ) ;
	    IGNORE fputc ( '\n', output ) ;
	    newline = 0 ;
	}
    }
    return ( newline ) ;
}


/*
    PRINT AN EXTERNAL NAME

    The start of a statement with name title concerning the construct
    p is output.  dec is true if this is the first statement concerning p.
*/

static void print_name
    PROTO_N ( ( title, p, dec ) )
    PROTO_T ( char *title X construct *p X int dec )
{
    if ( !func_output ) IGNORE fputs ( "( ", output ) ;
    if ( p->ename == null ) IGNORE fprintf ( output, "%s ", LOCAL_DECL ) ;
    IGNORE fprintf ( output, "%s", title ) ;
    if ( func_output ) IGNORE fputs ( " (", output ) ;
    if ( p->ename && p->ename->cons->encoding && dec ) {
	char *f = ( func_output ? "\n  %s (\n" : "\n  ( %s\n" ) ;
	if ( p->ename->son->cons->sortnum == SORT_tdfstring ) {
	    if ( p->ename->son->bro == null ) {
		IGNORE fprintf ( output, f, MAKE_STRING_EXTERN ) ;
	    } else {
		IGNORE fprintf ( output, f, MAKE_CHAIN_EXTERN ) ;
	    }
	} else {
	    IGNORE fprintf ( output, f, MAKE_UNIQUE_EXTERN ) ;
	}
	IGNORE print_node ( p->ename->son, 2 ) ;
	if ( func_output ) {
	    IGNORE fputs ( " ),\n  ", output ) ;
	} else {
	    IGNORE fputs ( " )\n  ", output ) ;
	}
    } else {
	IGNORE fputc ( ' ', output ) ;
    }
    IGNORE fprintf ( output, "%s", p->name ) ;
    return ;
}


/*
    ALIGNMENT TAG DECLARATION AUXILIARY PRINTING ROUTINE

    Print the declaration of the alignment tag p.
*/

static void print_aldec
    PROTO_N ( ( p ) )
    PROTO_T ( construct *p )
{
    if ( p->encoding == -1 ) return ;
    print_name ( MAKE_ALDEC, p, 1 ) ;
    IGNORE fputs ( ( func_output ? " ) ;\n\n" : " )\n\n" ), output ) ;
    return ;
}


/*
    ALIGNMENT TAG DEFINITION AUXILIARY PRINTING ROUTINE

    Print the definition of the alignment tag p.
*/

static void print_aldef
    PROTO_N ( ( p ) )
    PROTO_T ( construct *p )
{
    al_tag_info *info = get_al_tag_info ( p ) ;
    if ( p->encoding == -1 ) return ;
    if ( info->def == null ) return ;
    print_name ( MAKE_ALDEF, p, !show_aldecs ) ;
    if ( func_output ) IGNORE fputc ( ',', output ) ;
    IGNORE fputc ( '\n', output ) ;
    IGNORE print_node ( info->def, 1 ) ;
    IGNORE fputs ( ( func_output ? " ) ;\n\n" : " )\n\n" ), output ) ;
    return ;
}


/*
    TAG DECLARATION AUXILIARY PRINTING ROUTINE

    Print the declaration of the tag p.
*/

static void print_tagdec
    PROTO_N ( ( p ) )
    PROTO_T ( construct *p )
{
    tag_info *info = get_tag_info ( p ) ;
    if ( p->encoding == -1 || info->dec == null ) return ;
    switch ( info->var ) {
	case 0 : print_name ( MAKE_ID_TAGDEC, p, 1 ) ; break ;
	case 1 : print_name ( MAKE_VAR_TAGDEC, p, 1 ) ; break ;
	case 2 : print_name ( COMMON_TAGDEC, p, 1 ) ; break ;
    }
    if ( func_output ) IGNORE fputc ( ',', output ) ;
    IGNORE fputc ( '\n', output ) ;
    IGNORE print_node ( info->dec, 1 ) ;
    IGNORE fputs ( ( func_output ? " ) ;\n\n" : " )\n\n" ), output ) ;
    return ;
}


/*
    TAG DEFINITION AUXILIARY PRINTING ROUTINE

    Print the definition of the tag p.
*/

static void print_tagdef
    PROTO_N ( ( p ) )
    PROTO_T ( construct *p )
{
    char *instr ;
    tag_info *info = get_tag_info ( p ) ;
    node *d = info->def ;
    if ( p->encoding == -1 || d == null ) return ;
    switch ( info->var ) EXHAUSTIVE {
	case 0 : instr = MAKE_ID_TAGDEF ; break ;
	case 1 : instr = MAKE_VAR_TAGDEF ; break ;
	case 2 : instr = COMMON_TAGDEF ; break ;
    }
    while ( d ) {
	/* Can have multiple definitions */
	print_name ( instr, p, !show_tagdecs ) ;
	if ( func_output ) IGNORE fputc ( ',', output ) ;
	IGNORE fputc ( '\n', output ) ;
	IGNORE print_node ( d->son, 1 ) ;
	IGNORE fputs ( ( func_output ? " ) ;\n\n" : " )\n\n" ), output ) ;
	d = d->bro ;
    }
    return ;
}


/*
    TOKEN DECLARATION AUXILIARY PRINTING ROUTINE

    Print the declaration of the token p.
*/

static void print_tokdec
    PROTO_N ( ( p ) )
    PROTO_T ( construct *p )
{
    tok_info *info = get_tok_info ( p ) ;
    if ( p->encoding == -1 ) return ;
    if ( !info->dec ) return ;
    print_name ( MAKE_TOKDEC, p, 1 ) ;
    if ( func_output ) IGNORE fputc ( ',', output ) ;
    IGNORE fputc ( '\n', output ) ;
    if ( info->sig ) {
	IGNORE print_node ( info->sig, 1 ) ;
    } else {
	print_spaces ( 1 ) ;
	IGNORE fputc ( '-', output ) ;
    }
    if ( func_output ) IGNORE fputc ( ',', output ) ;
    IGNORE fputs ( "\n  ", output ) ;
    if ( info->args ) {
	int n = 0 ;
	char *q = info->args ;
	IGNORE fputs ( "( ", output ) ;
	while ( *q ) {
	    sortname s ;
	    q = find_sortname ( q, &s ) ;
	    q++ ;
	    if ( n++ == 8 ) {
		IGNORE fputs ( "\n  ", output ) ;
		n = 1 ;
	    }
	    IGNORE fputs ( sort_name ( s ), output ) ;
	    if ( func_output && *q ) IGNORE fputc ( ',', output ) ;
	    IGNORE fputc ( ' ', output ) ;
	}
	IGNORE fputs ( ") ", output ) ;
	if ( func_output ) IGNORE fputs ( "-> ", output ) ;
    }
    IGNORE fputs ( sort_name ( info->res ), output ) ;
    IGNORE fputs ( ( func_output ? " ) ;\n\n" : " )\n\n" ), output ) ;
    return ;
}


/*
    TOKEN DEFINITION AUXILIARY PRINTING ROUTINE

    Print the definition of the token p.
*/

static void print_tokdef
    PROTO_N ( ( p ) )
    PROTO_T ( construct *p )
{
    tok_info *info = get_tok_info ( p ) ;
    if ( p->encoding == -1 ) return ;
    if ( !info->dec ) return ;
    if ( info->def == null ) return ;
    print_name ( MAKE_TOKDEF, p, !show_tagdefs ) ;
    if ( func_output ) IGNORE fputc ( ',', output ) ;
    IGNORE fputc ( '\n', output ) ;
    if ( info->sig ) {
	IGNORE print_node ( info->sig, 1 ) ;
    } else {
	print_spaces ( 1 ) ;
	IGNORE fputc ( '-', output ) ;
    }
    if ( func_output ) IGNORE fputc ( ',', output ) ;
    IGNORE fputs ( "\n  ", output ) ;
    if ( info->args ) {
	int n = 0 ;
	construct **q = info->pars ;
	IGNORE fputs ( "( ", output ) ;
	while ( *q ) {
	    tok_info *qinfo = get_tok_info ( *q ) ;
	    if ( n++ == 4 ) {
		IGNORE fputs ( "\n    ", output ) ;
		n = 1 ;
	    }
	    IGNORE fprintf ( output, "%s %s", sort_name ( qinfo->res ),
			     ( *q )->name ) ;
	    q++ ;
	    if ( func_output && *q ) IGNORE fputc ( ',', output ) ;
	    IGNORE fputc ( ' ', output ) ;
	}
	IGNORE fputs ( ") ", output ) ;
	if ( func_output ) IGNORE fputs ( "-> ", output ) ;
    }
    IGNORE fputs ( sort_name ( info->res ), output ) ;
    if ( func_output ) IGNORE fputc ( ',', output ) ;
    IGNORE fputc ( '\n', output ) ;
    IGNORE print_node ( info->def, 1 ) ;
    IGNORE fputs ( ( func_output ? " ) ;\n\n" : " )\n\n" ), output ) ;
    return ;
}


/*
    PRINT A HIGH-LEVEL SORT

    This routine prints the high level sort h.
*/

static void print_high_sort
    PROTO_N ( ( h ) )
    PROTO_T ( high_sort *h )
{
    int i, n ;
    if ( h->id == SORT_unknown ) return ;
    if ( func_output ) {
	IGNORE fprintf ( output, "%s ( %s, ", MAKE_SORT, h->name ) ;
    } else {
	IGNORE fprintf ( output, "( %s %s ", MAKE_SORT, h->name ) ;
    }
    n = h->no_args ;
    if ( n ) {
	int m = 0 ;
	IGNORE fputs ( "( ", output ) ;
	for ( i = 0 ; i < n ; i++ ) {
	    if ( m++ == 8 ) {
		IGNORE fputs ( "\n  ", output ) ;
		m = 1 ;
	    }
	    IGNORE fputs ( sort_name ( h->args [i] ), output ) ;
	    if ( func_output && i < n - 1 ) IGNORE fputc ( ',', output ) ;
	    IGNORE fputc ( ' ', output ) ;
	}
	IGNORE fputs ( ") ", output ) ;
	if ( func_output ) IGNORE fputs ( "-> ", output ) ;
    }
    IGNORE fputs ( sort_name ( h->res ), output ) ;
    IGNORE fputs ( ( func_output ? " ) ;\n\n" : " )\n\n" ), output ) ;
    return ;
}


/*
    MAIN PRINTING ROUTINE

    This routine prints an entire capsule to the output file.
*/

void print_capsule
    PROTO_Z ()
{
    if ( high_sorts ) {
	int i ;
	IGNORE fputs ( "# HIGH-LEVEL SORTS\n\n", output ) ;
	for ( i = 0 ; i < crt_high_sort ; i++ ) {
	    print_high_sort ( high_sorts + i ) ;
	}
	IGNORE fputc ( '\n', output ) ;
    }
    if ( show_tokdecs ) {
	IGNORE fputs ( "# TOKEN DECLARATIONS\n\n", output ) ;
	apply_to_all ( print_tokdec, SORT_token ) ;
	IGNORE fputc ( '\n', output ) ;
    }
    if ( show_aldecs ) {
	IGNORE fputs ( "# ALIGNMENT TAG DECLARATIONS\n\n", output ) ;
	apply_to_all ( print_aldec, SORT_al_tag ) ;
	IGNORE fputc ( '\n', output ) ;
    }
    if ( show_tagdecs ) {
	IGNORE fputs ( "# TAG DECLARATIONS\n\n", output ) ;
	apply_to_all ( print_tagdec, SORT_tag ) ;
	IGNORE fputc ( '\n', output ) ;
    }
    if ( show_tokdefs ) {
	IGNORE fputs ( "# TOKEN DEFINITIONS\n\n", output ) ;
	apply_to_all ( print_tokdef, SORT_token ) ;
	IGNORE fputc ( '\n', output ) ;
    }
    if ( show_aldefs ) {
	IGNORE fputs ( "# ALIGNMENT TAG DEFINITIONS\n\n", output ) ;
	apply_to_all ( print_aldef, SORT_al_tag ) ;
	IGNORE fputc ( '\n', output ) ;
    }
    if ( show_tagdefs ) {
	IGNORE fputs ( "# TAG DEFINITIONS\n\n", output ) ;
	apply_to_all ( print_tagdef, SORT_tag ) ;
	IGNORE fputc ( '\n', output ) ;
    }
    return ;
}
