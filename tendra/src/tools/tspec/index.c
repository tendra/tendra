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
#include "object.h"
#include "hash.h"
#include "name.h"
#include "type.h"
#include "print.h"
#include "utility.h"


/*
    FLAGS

    These flags are used to indicate various output states indicated by
    preprocessing directives.  A value of 1 is the default (which
    actually means that the condition is false), 2 means that the given
    statement is true, and 0 means that its negation is true.
*/

static int building_libs = 1 ;
static int commented_out = 1 ;


/*
    FIELD SEPARATOR

    The field separator for the machine processable index.  This
    separator can be changed, but no command line option is provided to
    do this as '$' seems ideal.
*/

static char field_sep = '$' ;


/*
    PRINT FIELD SEPARATOR

    Routine to print field separator of the machine processable index.
*/

#define print_field_sep()	IGNORE putchar ( field_sep )


/*
    PRINT FIELD

    Routine to print field and separator of the machine processable index.
*/

static void print_field
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    IGNORE printf ( "%s%c", s, field_sep ) ;
    return ;
}


/*
    PRINT ESCAPED FIELD

    Routine to print field without separator of the machine processable
    index, escaping characters that could confuse output processing tools.
*/

static void print_escape
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    int c ;
    while ( ( c = *s++ ) != '\0' ) {
	if ( c == field_sep ) {
	    IGNORE printf ( "\\F" ) ;
	} else if ( c == '\n' ) {
	    IGNORE printf ( "\\n" ) ;
	} else if ( c == '\\' ) {
	    IGNORE printf ( "\\\\" ) ;
	} else {
	    IGNORE putchar ( c ) ;
	}
    }
    return ;
}


/*
    PRINT VALUE FIELD

    Routine to print the final value field of the machine processable index.
*/

static void print_value
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    print_field_sep () ;
    print_escape ( s ) ;
    IGNORE putchar ( '\n' ) ;
    return ;
}


/*
    PRINT EMPTY VALUE FIELD

    Routine to print the final empty value field of the machine processable
    index.
*/

static void print_no_value
    PROTO_Z ()
{
    IGNORE printf ( "%c\n", field_sep ) ;
    return ;
}


/*
    PRINT SORT, INFO AND TYPE FIELDS

    Routine to print sort, info and type fields of the machine processable
    index.
*/

static void print_sit_v
    PROTO_N ( ( s, i, t, nm ) )
    PROTO_T ( char *s X char *i X type *t X char *nm )
{
    IGNORE printf ( "%s%c%s%c", s, field_sep, i, field_sep ) ;
    IGNORE print_type ( stdout, t, nm, 0 ) ;
    return ;
}


/*
    PRINT SORT AND TYPE FIELDS

    Routine to print sort, empty info, and type fields of the machine
    processable index.
*/

static void print_st_v
    PROTO_N ( ( s, t, nm ) )
    PROTO_T ( char *s X type *t X char *nm )
{
    print_sit_v ( s, "", t, nm ) ;
    return ;
}


/*
    PRINT SORT AND INFO FIELDS

    Routine to print sort, info, and empty type fields of the machine
    processable index.
*/

static void print_si_v
    PROTO_N ( ( s, i ) )
    PROTO_T ( char *s X char *i )
{
    IGNORE printf ( "%s%c%s%c", s, field_sep, i, field_sep ) ;
    return ;
}


/*
    PRINT SORT FIELD

    Routine to print sort, empty info, and empty type fields of the
    machine processable index.
*/

static void print_s_v
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    IGNORE printf ( "%s%c%c", s, field_sep, field_sep ) ;
    return ;
}


/*
    PRINT SORT, INFO, TYPE AND EMPTY VALUE FIELDS

    Routine to print sort, info, type and empty value fields of the
    machine processable index.
*/

static void print_sit
    PROTO_N ( ( s, i, t, nm ) )
    PROTO_T ( char *s X char *i X type *t X char *nm )
{
    print_sit_v ( s, i, t, nm ) ;
    print_no_value () ;
    return ;
}


/*
    PRINT SORT, TYPE AND EMPTY VALUE FIELDS

    Routine to print sort, empty info, type and empty value fields of the
    machine processable index.
*/

static void print_st
    PROTO_N ( ( s, t, nm ) )
    PROTO_T ( char *s X type *t X char *nm )
{
    print_st_v ( s, t, nm ) ;
    print_no_value () ;
    return ;
}


/*
    PRINT SORT, INFO AND EMPTY VALUE FIELDS

    Routine to print sort, info, empty type and empty value fields of the
    machine processable index.
*/

static void print_si
    PROTO_N ( ( s, i ) )
    PROTO_T ( char *s X char *i )
{
    print_si_v ( s, i ) ;
    print_no_value () ;
    return ;
}


/*
    PRINT SORT AND EMPTY VALUE FIELDS

    Routine to print sort, empty info, empty type and empty value fields
    of the machine processable index.
*/

static void print_s
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    print_s_v ( s ) ;
    print_no_value () ;
    return ;
}


/*
    IF STACK STATE

    This stack is used to keep track of the current +IF conditions.
*/

static object **if_stack = 0 ;
static int if_stack_sz = 0 ;
static int if_stack_index = 0 ;


/*
    STACK AN IF COMMAND OBJECT

    Routine to stack an object representing +IFxxx or +ELSE.
*/

static void stack_if
    PROTO_N ( ( p ) )
    PROTO_T ( object *p )
{
    if ( if_stack_index == if_stack_sz ) {
	if_stack_sz += 16 ;
	if_stack = realloc_nof ( if_stack, object *, if_stack_sz ) ;
    }
    if_stack [ if_stack_index ] = p ;
    if_stack_index++ ;
    return ;
}


/*
    UNSTACK AN IF COMMAND OBJECT

    Routine to unstack an object representing +IFxxx or +ELSE.
*/

static object *unstack_if
    PROTO_Z ()
{
    return ( if_stack [ --if_stack_index ] ) ;
}


/*
    PRINT IF NESTING

    Routine to print the currently stacked +IFxxx and +ELSE nesting.
*/

static void print_if_nest
    PROTO_Z ()
{
    int i ;
    for ( i = 0 ; i < if_stack_index ; i++ ) {
	char code ;
	object *p = if_stack [ i ] ;
	char *c = p->name ;

	if ( i > 0 ) print_escape ( ";" ) ;
	if ( i + 1 < if_stack_index &&
	  if_stack [ i + 1 ]->u.u_num == CMD_ELSE ) {
	    IGNORE printf ( "e" ) ;
	    i++ ;
	}
	switch ( p->u.u_num ) EXHAUSTIVE {
	    case CMD_IF : code = 'i' ; break ;
	    case CMD_IFDEF : code = 'd' ; break ;
	    case CMD_IFNDEF : code = 'n' ; break ;
	}
	IGNORE printf ( "%c", code ) ;
	print_escape ( ":" ) ;
	print_escape ( c ) ;
    }
    return ;
}


/*
    PRINT A MACHINE PROCESSABLE ITEM INDEX

    This routine prints the index item indicated by the token object p.
    u gives the token status, a the current file name, and e is used in
    enumeration items.  The output is in fields suitable for machine
    processing by tools such as 'awk'.
*/

static void print_item_m
    PROTO_N ( ( p, u, a, e ) )
    PROTO_T ( object *p X char *u X char *a X type *e )
{
    char *nm ;
    char *ap ;
    char *tnm = p->name ;
    object *q = p->u.u_obj ;

    if ( q->objtype == OBJ_FIELD ) {
	nm = q->u.u_field->fname ;
    } else {
	nm = q->name ;
    }

    /* Field 1: C_SYMBOL */
    print_field ( nm ) ;

    /* Field 2: TOKEN */
    print_field ( tnm ) ;

    /* Field 3: STATUS */
    IGNORE printf ( "%c%c", u [ 0 ], field_sep ) ;

    /* Field 4: IF_NESTING */
    print_if_nest () ;
    print_field_sep () ;

    /* Field 5: API_LOCATION */
    for ( ap = a ; *ap && *ap != ':' ; ap++ ) IGNORE putchar ( *ap ) ;
    print_field_sep () ;

    /* Field 6: FILE_LOCATION */
    if ( *ap ) ap++ ;
    for ( ; *ap && *ap != ':' ; ap++ ) IGNORE putchar ( *ap ) ;
    print_field_sep () ;

    /* Field 7: LINE_LOCATION */
    IGNORE printf ( "%d%c", q->line_no, field_sep ) ;

    /* Field 8: SUBSET_NESTING */
    if ( *ap ) IGNORE printf ( "%s", ap + 1 ) ;
    print_field_sep () ;

    /* Fields 9-12: SORT, INFO, TYPE, VALUE */
    switch ( q->objtype ) {

	case OBJ_CONST : {
	    print_st ( "const", q->u.u_type, null_str ) ;
	    break ;
	}

	case OBJ_ENUMVAL : {
	    print_field ( "enum_member" ) ;
	    print_type ( stdout, e, null_str, 0 ) ;
	    print_field_sep () ;
	    if ( q->u.u_str ) {
		print_value ( q->u.u_str ) ;
	    } else {
		print_no_value () ;
	    }
	    break ;
	}

	case OBJ_EXP : {
	    type *t = q->u.u_type ;
	    char *s = ( t->id == TYPE_LVALUE ? "lvalue" : "rvalue" ) ;
	    print_st ( s, t, null_str ) ;
	    break ;
	}

	case OBJ_EXTERN : {
	    type *t = q->u.u_type ;
	    if ( t->id == TYPE_LVALUE ) t = t->u.subtype ;
	    if ( t->id == TYPE_PROC ) {
		print_sit ( "func", "extern", t, nm ) ;
	    } else {
		print_st ( "extern", t, null_str ) ;
	    }
	    break ;
	}

	case OBJ_WEAK : {
	    type *t = q->u.u_type ;
	    print_sit ( "func", "weak", t, nm ) ;
	    break ;
	}

	case OBJ_DEFINE : {
	    char *s = q->u.u_str ;
	    if ( *s == '(' ) {
		print_field ( "define" ) ;
		print_field ( "param" ) ;
		for ( ; *s && *s != ')' ; s++ ) {
		    IGNORE putchar ( *s ) ;
		}
		if ( *s == ')' ) s++ ;
		IGNORE printf ( ")" ) ;
	    } else {
		print_s_v ( "define" ) ;
	    }
	    while ( *s == ' ' ) s++ ;
	    print_value ( s ) ;
	    break ;
	}

	case OBJ_FIELD : {
	    field *f = q->u.u_field ;
	    print_field ( "member" ) ;
	    print_type ( stdout, f->stype, null_str, 0 ) ;
	    print_field_sep () ;
	    print_type ( stdout, f->ftype, null_str, 0 ) ;
	    print_no_value () ;
	    break ;
	}

	case OBJ_FUNC : {
	    print_st ( "func", q->u.u_type, nm ) ;
	    break ;
	}

	case OBJ_MACRO : {
	    print_st ( "macro", q->u.u_type, nm ) ;
	    break ;
	}

	case OBJ_NAT : {
	    print_s ( "nat" ) ;
	    break ;
	}

	case OBJ_STATEMENT : {
	    type *t = q->u.u_type ;
	    if ( t ) {
		print_sit ( "statement", "param", t, null_str ) ;
	    } else {
		print_s ( "statement" ) ;
	    }
	    break ;
	}

	case OBJ_TOKEN : {
	    print_s_v ( "token" ) ;
	    print_value ( q->u.u_str ) ;
	    break ;
	}

	case OBJ_TYPE : {
	    type *t = q->u.u_type ;
	    int i = t->id ;
	    switch ( i ) {

		case TYPE_DEFINED : {
		    print_st ( "typedef", t->v.next, null_str ) ;
		    break ;
		}

		case TYPE_GENERIC : {
		    print_s ( "opaque" ) ;
		    break ;
		}

		case TYPE_INT : {
		    print_s ( "integral" ) ;
		    break ;
		}

		case TYPE_SIGNED : {
		    print_s ( "signed_integral" ) ;
		    break ;
		}

		case TYPE_UNSIGNED : {
		    print_s ( "unsigned_integral" ) ;
		    break ;
		}

		case TYPE_PROMOTE : {
		    print_field ( "promotion" ) ;
		    print_type ( stdout, t->v.next, null_str, 0 ) ;
		    print_field_sep () ;
		    print_no_value () ;
		    break ;
		}

		case TYPE_FLOAT : {
		    print_s ( "floating" ) ;
		    break ;
		}

		case TYPE_ARITH : {
		    print_s ( "arithmetic" ) ;
		    break ;
		}

		case TYPE_SCALAR : {
		    print_s ( "scalar" ) ;
		    break ;
		}

		case TYPE_STRUCT :
		case TYPE_STRUCT_TAG :
		case TYPE_UNION :
		case TYPE_UNION_TAG :
		case TYPE_ENUM :
		case TYPE_ENUM_TAG : {
		    char *s ;
		    type *en = null ;
		    object *r = t->v.obj2 ;
		    char *inf = ( r ? "exact" : "" ) ;
		    switch ( i ) EXHAUSTIVE {
			case TYPE_STRUCT : s = "struct" ; break ;
			case TYPE_STRUCT_TAG : s = "struct_tag" ; break ;
			case TYPE_UNION : s = "union" ; break ;
			case TYPE_UNION_TAG : s = "union_tag" ; break ;
			case TYPE_ENUM : s = "enum" ; en = t ; break ;
			case TYPE_ENUM_TAG : s = "enum_tag" ; en = t ; break ;
		    }
		    print_si ( s, inf ) ;
		    while ( r ) {
			print_item_m ( r, u, a, en ) ;
			r = r->next ;
		    }
		    break ;
		}

		default : {
		    error ( ERR_INTERNAL, "Unknown type identifier, '%d'", i ) ;
		    break ;
		}
	    }
	    break ;
	}

	default : {
	    error ( ERR_INTERNAL, "Unknown object type, '%d'", q->objtype ) ;
	    break ;
	}
    }
    return ;
}


/*
    PRINT AN INDEX ITEM

    This routine prints the index item indicated by the token object p.
    u gives the token status, a the current file name, and e is used in
    enumeration items.  The output is in a humun readable format.
*/

static void print_item_h
    PROTO_N ( ( p, u, a, e ) )
    PROTO_T ( object *p X char *u X char *a X type *e )
{
    char *tnm = p->name ;
    object *q = p->u.u_obj ;
    char *nm = q->name ;
    IGNORE printf ( "TOKEN: %s\n", tnm ) ;
    IGNORE printf ( "STATUS: %s", u ) ;
    if ( building_libs == 0 ) IGNORE printf ( " (not library building)" ) ;
    if ( building_libs == 2 ) IGNORE printf ( " (library building only)" ) ;
    IGNORE printf ( "\nDEFINED: %s, line %d\n", a, q->line_no ) ;
    IGNORE printf ( "INFO: " ) ;
    if ( commented_out == 2 ) IGNORE printf ( "(commented out) " ) ;

    switch ( q->objtype ) {

	case OBJ_CONST : {
	    IGNORE printf ( "%s is a constant expression of type ", nm ) ;
	    print_type ( stdout, q->u.u_type, null_str, 0 ) ;
	    IGNORE printf ( "\n\n" ) ;
	    break ;
	}

	case OBJ_ENUMVAL : {
	    IGNORE printf ( "%s is a member of the enumeration type ", nm ) ;
	    print_type ( stdout, e, null_str, 0 ) ;
	    IGNORE printf ( "\n\n" ) ;
	    break ;
	}

	case OBJ_EXP : {
	    IGNORE printf ( "%s is an expression of type ", nm ) ;
	    print_type ( stdout, q->u.u_type, null_str, 0 ) ;
	    IGNORE printf ( "\n\n" ) ;
	    break ;
	}

	case OBJ_EXTERN : {
	    type *t = q->u.u_type ;
	    if ( t->id == TYPE_LVALUE ) t = t->u.subtype ;
	    IGNORE printf ( "%s is an external ", nm ) ;
	    if ( t->id == TYPE_PROC ) {
		IGNORE printf ( "function with prototype " ) ;
		print_type ( stdout, t, nm, 0 ) ;
	    } else {
		IGNORE printf ( "expression with type " ) ;
		print_type ( stdout, t, null_str, 0 ) ;
	    }
	    IGNORE printf ( "\n\n" ) ;
	    break ;
	}

	case OBJ_WEAK : {
	    type *t = q->u.u_type ;
	    IGNORE printf ( "%s is an external ", nm ) ;
	    IGNORE printf ( "function with weak prototype " ) ;
	    print_type ( stdout, t, nm, 0 ) ;
	    IGNORE printf ( "\n\n" ) ;
	    break ;
	}

	case OBJ_DEFINE : {
	    char *s = q->u.u_str ;
	    IGNORE printf ( "%s is a macro ", nm ) ;
	    if ( *s == '(' ) {
		IGNORE printf ( "with arguments " ) ;
		for ( ; *s && *s != ')' ; s++ ) {
		    IGNORE putchar ( *s ) ;
		}
		if ( *s == ')' ) s++ ;
		IGNORE printf ( ") " ) ;
	    }
	    while ( *s == ' ' ) s++ ;
	    IGNORE printf ( "defined to be %s\n\n", s ) ;
	    break ;
	}

	case OBJ_FIELD : {
	    field *f = q->u.u_field ;
	    IGNORE printf ( "%s is a field selector of ", f->fname ) ;
	    print_type ( stdout, f->stype, null_str, 0 ) ;
	    IGNORE printf ( " of type " ) ;
	    print_type ( stdout, f->ftype, null_str, 0 ) ;
	    IGNORE printf ( "\n\n" ) ;
	    break ;
	}

	case OBJ_FUNC : {
	    IGNORE printf ( "%s is a function with prototype ", nm ) ;
	    print_type ( stdout, q->u.u_type, nm, 0 ) ;
	    IGNORE printf ( "\n\n" ) ;
	    break ;
	}

	case OBJ_MACRO : {
	    IGNORE printf ( "%s is a macro with prototype ", nm ) ;
	    print_type ( stdout, q->u.u_type, nm, 0 ) ;
	    IGNORE printf ( "\n\n" ) ;
	    break ;
	}

	case OBJ_NAT : {
	    IGNORE printf ( "%s is a constant integer\n\n", nm ) ;
	    break ;
	}

	case OBJ_STATEMENT : {
	    type *t = q->u.u_type ;
	    IGNORE printf ( "%s is a statement", nm ) ;
	    if ( t ) {
		IGNORE printf ( " with arguments" ) ;
		print_type ( stdout, t, null_str, 0 ) ;
	    }
	    IGNORE printf ( "\n\n" ) ;
	    break ;
	}

	case OBJ_TOKEN : {
	    IGNORE printf ( "%s is a complex token\n\n", nm ) ;
	    break ;
	}

	case OBJ_TYPE : {
	    type *t = q->u.u_type ;
	    int i = t->id ;
	    print_type ( stdout, t, null_str, 0 ) ;
	    switch ( i ) {

		case TYPE_DEFINED : {
		    IGNORE printf ( " is a type defined to be " ) ;
		    print_type ( stdout, t->v.next, null_str, 0 ) ;
		    IGNORE printf ( "\n\n" ) ;
		    break ;
		}

		case TYPE_GENERIC : {
		    IGNORE printf ( " is a type\n\n" ) ;
		    break ;
		}

		case TYPE_INT : {
		    IGNORE printf ( " is an integral type\n\n" ) ;
		    break ;
		}

		case TYPE_SIGNED : {
		    IGNORE printf ( " is a signed integral type\n\n" ) ;
		    break ;
		}

		case TYPE_UNSIGNED : {
		    IGNORE printf ( " is an unsigned integral type\n\n" ) ;
		    break ;
		}

		case TYPE_PROMOTE : {
		    IGNORE printf ( " is the integral promotion of " ) ;
		    print_type ( stdout, t->v.next, null_str, 0 ) ;
		    IGNORE printf ( "\n\n" ) ;
		    break ;
		}

		case TYPE_FLOAT : {
		    IGNORE printf ( " is a floating type\n\n" ) ;
		    break ;
		}

		case TYPE_ARITH : {
		    IGNORE printf ( " is an arithmetic type\n\n" ) ;
		    break ;
		}

		case TYPE_SCALAR : {
		    IGNORE printf ( " is a scalar type\n\n" ) ;
		    break ;
		}

		case TYPE_STRUCT :
		case TYPE_STRUCT_TAG :
		case TYPE_UNION :
		case TYPE_UNION_TAG : {
		    char *n ;
		    object *r = t->v.obj2 ;
		    switch ( i ) EXHAUSTIVE {
			case TYPE_STRUCT : n = "structure" ; break ;
			case TYPE_STRUCT_TAG : n = "structure" ; break ;
			case TYPE_UNION : n = "union" ; break ;
			case TYPE_UNION_TAG : n = "union" ; break ;
		    }
		    if ( r == null ) {
			IGNORE printf ( " is an inexact %s type\n\n", n ) ;
		    } else {
			IGNORE printf ( " is an exact %s type\n\n", n ) ;
			while ( r ) {
			    print_item_h ( r, u, a, ( type * ) null ) ;
			    r = r->next ;
			}
		    }
		    break ;
		}

		case TYPE_ENUM :
		case TYPE_ENUM_TAG : {
		    object *r = t->v.obj2 ;
		    IGNORE printf ( " is an enumeration type\n\n" ) ;
		    while ( r ) {
			print_item_h ( r, u, a, t ) ;
			r = r->next ;
		    }
		    break ;
		}

		default : {
		    IGNORE printf ( " is a type\n\n" ) ;
		    error ( ERR_INTERNAL, "Unknown type identifier, '%d'", i ) ;
		    break ;
		}
	    }
	    break ;
	}

	default : {
	    error ( ERR_INTERNAL, "Unknown object type, '%d'", q->objtype ) ;
	    break ;
	}
    }
    return ;
}


/*
    PRINT INDEX USING PRINT ITEM FUNCTION

    This routine prints an index of the set object input using fn.
*/

typedef void ( *index_func ) PROTO_S ( ( object *, char *, char *, type * ) ) ;

static void print_index_with
    PROTO_N ( ( input, fn ) )
    PROTO_T ( object *input X index_func fn )
{
    object *p = input->u.u_obj ;
    info *i = p->u.u_info ;
    char *a = p->name ;
    char *u = ( i->implemented ? "implemented" : "used" ) ;
    for ( p = i->elements ; p != null ; p = p->next ) {
	switch ( p->objtype ) {

	    case OBJ_IF : {
		/* Deal with preprocessing directives */
		char *c = p->name ;
		if ( fn == print_item_m ) {
		    switch ( p->u.u_num ) {
			case CMD_IF :
			case CMD_IFDEF :
			case CMD_IFNDEF :
			case CMD_ELSE : {
			    stack_if ( p ) ;
			    break ;
			}
			case CMD_ENDIF : {
			    if ( unstack_if ()->u.u_num == CMD_ELSE ) {
				IGNORE unstack_if () ;
			    }
			    break ;
			}
		    }
		} else if ( streq ( c, BUILDING_MACRO ) ) {
		    /* Check for the building_libs macro */
		    switch ( p->u.u_num ) {
			case CMD_IF :
			case CMD_IFDEF : {
			    building_libs = 2 ;
			    break ;
			}
			case CMD_IFNDEF : {
			    building_libs = 0 ;
			    break ;
			}
			case CMD_ELSE : {
			    building_libs = 2 - building_libs ;
			    break ;
			}
			case CMD_ENDIF : {
			    building_libs = 1 ;
			    break ;
			}
		    }
		} else {
		    /* Check for integers */
		    int n = 0 ;
		    while ( *c == '-' ) c++ ;
		    while ( *c >= '0' && *c <= '9' ) {
			n = 10 * n + ( *c - '0' ) ;
			c++ ;
		    }
		    if ( *c == 0 ) {
			switch ( p->u.u_num ) {
			    case CMD_IF : {
				commented_out = ( n ? 0 : 2 ) ;
				break ;
			    }
			    case CMD_ELSE : {
				commented_out = 2 - commented_out ;
				break ;
			    }
			    case CMD_ENDIF : {
				commented_out = 1 ;
				break ;
			    }
			}
		    }
		}
		break ;
	    }

	    case OBJ_SET : {
		/* Deal with subsets */
		print_index_with ( p, fn ) ;
		break ;
	    }

	    case OBJ_TOKEN : {
		/* Deal with tokens */
		if ( i->implemented || !restrict_use ) {
		    ( *fn ) ( p, u, a, ( type * ) null ) ;
		}
		break ;
	    }
	}
    }
    return ;
}


/*
    PRINT MACHINE PROCESSABLE INDEX

    This routine prints an index intended for machine processing of the
    set object input.
*/

void print_machine_index
    PROTO_N ( ( input ) )
    PROTO_T ( object *input )
{
    print_index_with ( input, print_item_m ) ;
    return ;
}


/*
    PRINT INDEX

    This routine prints an index intended for human readers of the set
    object input.
*/

void print_index
    PROTO_N ( ( input ) )
    PROTO_T ( object *input )
{
    print_index_with ( input, print_item_h ) ;
    return ;
}
