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
    COPYRIGHT MESSAGE

    These variables give the file containing the copyright message, and,
    after the first time it is processed, the message text.
*/

char *copyright = null ;
static char *copyright_text = null ;


/*
    OUTPUT MACROS

    These macros are used as convenient shorthands for various print
    routines.
*/

#define OUT		IGNORE fprintf
#define OUTC( X, Y )	IGNORE fputc ( Y, X )
#define OUTS( X, Y )	IGNORE fputs ( Y, X )


/*
    OUTPUT TRICKS

    A number of minor tricks are required in the headers, mostly due to
    library building problems.
*/

static boolean weak_proto = 0 ;
#define enum_hack	"__enum_"
#define is_hidden( X )	strneq ( X, HIDDEN_NAME, HIDDEN_LEN )


/*
    OUTPUT FILE

    These variables hold information about the current output file.
*/

static info *crt_info = null ;
static int column = 0 ;


/*
    DOES A TYPE HAVE A TAIL COMPONENT?

    This routine checks whether the type t has an array, bitfield or
    function component.
*/

static int is_tailed_type
    PROTO_N ( ( t ) )
    PROTO_T ( type *t )
{
    if ( t ) {
	switch ( t->id ) {
	    case TYPE_ARRAY :
	    case TYPE_BITFIELD :
	    case TYPE_PROC : {
		return ( 1 ) ;
	    }
	}
    }
    return ( 0 ) ;
}


/*
    PRINT THE HEAD OF A TYPE

    This routine prints the head of the type t, that is to say the base type
    and the pointer components, to the file output.
*/

static int print_head
    PROTO_N ( ( output, t, sp, tok ) )
    PROTO_T ( FILE *output X type *t X int sp X int tok )
{
    if ( t == null ) return ( sp ) ;
    switch ( t->id ) {
	case TYPE_VOID :
	case TYPE_INT :
	case TYPE_SIGNED :
	case TYPE_UNSIGNED :
	case TYPE_FLOAT :
	case TYPE_ARITH :
	case TYPE_SCALAR :
	case TYPE_STRUCT :
	case TYPE_UNION :
	case TYPE_ENUM :
	case TYPE_GENERIC :
	case TYPE_DEFINED :
	case TYPE_PROMOTE : {
	    OUTS ( output, t->u.obj->name ) ;
	    sp = 1 ;
	    break ;
	}
	case TYPE_STRUCT_TAG : {
	    OUT ( output, "struct %s", t->u.obj->name ) ;
	    sp = 1 ;
	    break ;
	}
	case TYPE_UNION_TAG : {
	    OUT ( output, "union %s", t->u.obj->name ) ;
	    sp = 1 ;
	    break ;
	}
	case TYPE_ENUM_TAG : {
	    if ( tok ) {
		OUT ( output, "%s%s", enum_hack, t->u.obj->name ) ;
	    } else {
		OUT ( output, "enum %s", t->u.obj->name ) ;
	    }
	    sp = 1 ;
	    break ;
	}
	case TYPE_LVALUE : {
	    OUTS ( output, "lvalue " ) ;
	    if ( tok ) OUTS ( output, ": " ) ;
	    sp = print_head ( output, t->u.subtype, 0, tok ) ;
	    break ;
	}
	case TYPE_QUALIFIER : {
	    OUT ( output, "%s ", t->v.str ) ;
	    sp = print_head ( output, t->u.subtype, 0, tok ) ;
	    break ;
	}
	case TYPE_RVALUE : {
	    if ( tok ) OUTS ( output, "rvalue : " ) ;
	    sp = print_head ( output, t->u.subtype, 0, tok ) ;
	    break ;
	}
	case TYPE_PTR : {
	    type *s = t->u.subtype ;
	    char *q = t->v.str ;
	    sp = print_head ( output, s, sp, tok ) ;
	    if ( sp ) OUTC ( output, ' ' ) ;
	    if ( is_tailed_type ( s ) ) {
		OUTS ( output, "( *" ) ;
	    } else {
		OUTS ( output, "*" ) ;
	    }
	    sp = 0 ;
	    if ( q ) {
		OUT ( output, " %s", q ) ;
		sp = 1 ;
	    }
	    break ;
	}
	case TYPE_ARRAY :
	case TYPE_BITFIELD :
	case TYPE_PROC : {
	    sp = print_head ( output, t->u.subtype, sp, tok ) ;
	    break ;
	}
	default : {
	    /* Unknown types */
	    error ( ERR_INTERNAL, "Unknown type identifier, '%d'", t->id ) ;
	    break ;
	}
    }
    return ( sp ) ;
}


/*
    PRINT THE TAIL OF A TYPE

    This routine prints the tail of the type t, that is to say the array,
    bitfield and function components, to the file output.
*/

static void print_tail
    PROTO_N ( ( output, t, tok ) )
    PROTO_T ( FILE *output X type *t X int tok )
{
    if ( t == null ) return ;
    switch ( t->id ) {
	case TYPE_LVALUE :
	case TYPE_RVALUE :
	case TYPE_QUALIFIER : {
	    print_tail ( output, t->u.subtype, tok ) ;
	    break ;
	}
	case TYPE_PTR : {
	    type *s = t->u.subtype ;
	    if ( is_tailed_type ( s ) ) {
		OUTS ( output, " )" ) ;
	    }
	    print_tail ( output, s, tok ) ;
	    break ;
	}
	case TYPE_ARRAY : {
	    OUT ( output, " [%s]", t->v.str ) ;
	    print_tail ( output, t->u.subtype, tok ) ;
	    break ;
	}
	case TYPE_BITFIELD : {
	    if ( tok ) {
		OUT ( output, " %% %s", t->v.str ) ;
	    } else {
		OUT ( output, " : %s", t->v.str ) ;
	    }
	    print_tail ( output, t->u.subtype, tok ) ;
	    break ;
	}
	case TYPE_PROC : {
	    type *s = t->v.next ;
	    if ( s ) {
		OUTS ( output, " ( " ) ;
		while ( s ) {
		    print_type ( output, s->u.subtype, null_str, tok ) ;
		    s = s->v.next ;
		    if ( s ) OUTS ( output, ", " ) ;
		}
		OUTS ( output, " )" ) ;
	    } else {
		OUTS ( output, " ()" ) ;
	    }
	    print_tail ( output, t->u.subtype, tok ) ;
	    break ;
	}
    }
    return ;
}


/*
    PRINT A TYPE

    This routine prints the object nm of type t to the file output.
*/

void print_type
    PROTO_N ( ( output, t, nm, tok ) )
    PROTO_T ( FILE *output X type *t X char *nm X int tok )
{
    if ( t ) {
	int sp = print_head ( output, t, 0, tok ) ;
	if ( nm ) {
	    if ( sp ) OUTC ( output, ' ' ) ;
	    OUTS ( output, nm ) ;
	}
	print_tail ( output, t, tok ) ;
    }
    return ;
}


/*
    PRINT A STRUCT OR UNION DEFINITION

    This routine prints the specification for a structure or union type,
    t, with internal name nm and external name tnm, to output.
*/

static void print_struct_defn
    PROTO_N ( ( output, t, nm, tnm, d ) )
    PROTO_T ( FILE *output X type *t X char *nm X char *tnm X int d )
{
    char *tok, *tag ;
    object *q = t->v.obj2 ;
    boolean show_token = 1, show_interface = 1 ;
    boolean show_ignore = 1, show_defn = 1 ;

    /* Find the token type */
    switch ( t->id ) EXHAUSTIVE {
	case TYPE_STRUCT : tok = "STRUCT" ; tag = "" ; break ;
	case TYPE_STRUCT_TAG : tok = "STRUCT" ; tag = "TAG " ; break ;
	case TYPE_UNION : tok = "UNION" ; tag = "" ; break ;
	case TYPE_UNION_TAG : tok = "UNION" ; tag = "TAG " ; break ;
    }

    /* Deal with undefined tokens immediately */
    if ( q == null ) {
	OUT ( output, "#pragma token %s %s%s # %s\n", tok, tag, nm, tnm ) ;
	return ;
    }

    /* Deal with the various definition cases */
    switch ( t->state ) {
	case 0 : {
	    /* Definition is immediate */
	    if ( is_hidden ( nm ) ) {
		show_token = 0 ;
		show_interface = 0 ;
		show_ignore = 0 ;
	    }
	    break ;
	}
	case 1 : {
	    /* Definition is elsewhere */
	    show_interface = 0 ;
	    show_ignore = 0 ;
	    show_defn = 0 ;
	    t->state = 2 ;
	    break ;
	}
	case 2 : {
	    /* Declaration was earlier in file */
	    show_token = 0 ;
	    t->state = 0 ;
	    break ;
	}
	case 3 : {
	    /* Declaration was in another file */
	    if ( d ) {
		show_token = 0 ;
		show_interface = 0 ;
		t->state = 1 ;
	    } else {
		show_interface = 0 ;
		show_ignore = 0 ;
		show_defn = 0 ;
		t->state = 2 ;
	    }
	    break ;
	}
    }

    /* Print the token if necessary */
    if ( show_token ) {
	OUT ( output, "#pragma token %s %s%s # %s\n", tok, tag, nm, tnm ) ;
    }

    /* Print the interface statement */
    if ( show_interface ) {
	char *b = BUILDING_MACRO ;
	OUT ( output, "#ifdef %s\n", b ) ;
	OUT ( output, "#pragma interface %s%s\n", tag, nm ) ;
	OUT ( output, "#else /* %s */\n", b ) ;
    }

    /* Print the ignore statement */
    if ( show_ignore ) {
	if ( !show_interface ) {
	    char *b = BUILDING_MACRO ;
	    OUT ( output, "#ifndef %s\n", b ) ;
	}
	OUT ( output, "#pragma ignore %s%s\n", tag, nm ) ;
    }

    /* Print the type definition */
    if ( show_defn ) {
	tok = ( tok [0] == 'S' ? "struct" : "union" ) ;
	if ( *tag ) {
	    OUT ( output, "%s %s {\n", tok, nm ) ;
	} else {
	    OUT ( output, "typedef %s {\n", tok ) ;
	}
	while ( q ) {
	    field *f = q->u.u_obj->u.u_field ;
	    OUTS ( output, "    " ) ;
	    print_type ( output, f->ftype, f->fname, 0 ) ;
	    OUTS ( output, " ;\n" ) ;
	    q = q->next ;
	}
	if ( *tag ) {
	    OUTS ( output, "} ;\n" ) ;
	} else {
	    OUT ( output, "} %s ;\n", nm ) ;
	}
    }

    /* Print the final #endif */
    if ( show_interface || show_ignore ) {
	char *b = BUILDING_MACRO ;
	OUT ( output, "#endif /* %s */\n", b ) ;
    }
    return ;
}


/*
    PRINT A TOKENISED TYPE

    This routine is the special case of print_token which deals with
    tokenised types.
*/

static void print_token_type
    PROTO_N ( ( output, p, tnm ) )
    PROTO_T ( FILE *output X object *p X char *tnm )
{
    char *tok = "TYPE" ;
    char *nm = p->name ;
    type *t = p->u.u_type ;
    int i = t->id ;
    switch ( i ) {

	case TYPE_DEFINED : {
	    /* Defined types */
	    char *tm, *sp ;
	    type *s = t->v.next ;
	    char *b = BUILDING_MACRO ;
	    if ( s == type_bottom ) {
		sp = "bottom" ;
	    } else if ( s == type_printf ) {
		sp = "... printf" ;
	    } else if ( s == type_scanf ) {
		sp = "... scanf" ;
	    } else {
		OUTS ( output, "typedef " ) ;
		print_type ( output, s, nm, 0 ) ;
		OUTS ( output, " ;\n" ) ;
		break ;
	    }
	    /* Allow for special types */
	    tm = "__TenDRA__" ;
	    OUT ( output, "#ifndef %s\n", b ) ;
	    OUT ( output, "#ifdef %s\n", tm ) ;
	    OUT ( output, "#pragma TenDRA type %s for %s\n", nm, sp ) ;
	    OUT ( output, "#else /* %s */\n", tm ) ;
	    OUT ( output, "typedef %s %s ;\n", s->u.obj->name, nm ) ;
	    OUT ( output, "#endif /* %s */\n", tm ) ;
	    OUT ( output, "#else /* %s */\n", b ) ;
	    OUT ( output, "typedef %s %s ;\n", s->u.obj->name, nm ) ;
	    OUT ( output, "#endif /* %s */\n", b ) ;
	    break ;
	}

	case TYPE_INT : tok = "VARIETY" ; goto generic_lab ;
	case TYPE_SIGNED : tok = "VARIETY signed" ; goto generic_lab ;
	case TYPE_UNSIGNED : tok = "VARIETY unsigned" ; goto generic_lab ;
	case TYPE_FLOAT : tok = "FLOAT" ; goto generic_lab ;
	case TYPE_ARITH : tok = "ARITHMETIC" ; goto generic_lab ;
	case TYPE_SCALAR : tok = "SCALAR" ; goto generic_lab ;

	case TYPE_GENERIC :
	generic_lab : {
	    /* Generic types */
	    OUT ( output, "#pragma token %s %s # %s\n", tok, nm, tnm ) ;
	    break ;
	}

	case TYPE_PROMOTE : {
	    /* Promotion types */
	    char *pt = t->v.next->u.obj->name ;
	    OUT ( output, "#pragma token VARIETY %s # %s\n", nm, tnm ) ;
	    OUT ( output, "#pragma promote %s : %s\n", pt, nm ) ;
	    break ;
	}

	case TYPE_STRUCT :
	case TYPE_STRUCT_TAG :
	case TYPE_UNION :
	case TYPE_UNION_TAG : {
	    /* Structure or union types */
	    print_struct_defn ( output, t, nm, tnm, 0 ) ;
	    break ;
	}

	case TYPE_ENUM :
	case TYPE_ENUM_TAG : {
	    /* Enumeration types are a complete hack */
	    char *b = BUILDING_MACRO ;
	    boolean tagged = ( boolean ) ( i == TYPE_ENUM ? 0 : 1 ) ;
	    object *q = t->v.obj2 ;
	    OUT ( output, "#ifndef %s\n", b ) ;

	    /* Print the enumeration type */
	    if ( tagged ) {
		OUT ( output, "typedef enum %s {", nm ) ;
	    } else {
		OUTS ( output, "typedef enum {" ) ;
	    }

	    /* Print the enumeration elements */
	    while ( q ) {
		object *r = q->u.u_obj ;
		char *v = r->u.u_str ;
		if ( v && v [0] ) {
		    OUT ( output, "\n    %s = %s", r->name, v ) ;
		} else {
		    OUT ( output, "\n    %s", r->name ) ;
		}
		q = q->next ;
		if ( q ) OUTC ( output, ',' ) ;
	    }

	    /* Print the end of the enumeration type */
	    if ( tagged ) {
		IGNORE sprintf ( buffer, "%s%s", enum_hack, nm ) ;
		OUT ( output, "\n} %s ;\n", buffer ) ;
	    } else {
		OUT ( output, "\n} %s ;\n", nm ) ;
	    }

	    /* Print the hacked library building version */
	    OUT ( output, "#else /* %s */\n", b ) ;
	    if ( tagged ) {
		OUT ( output, "typedef int %s ;\n", buffer ) ;
	    } else {
		OUT ( output, "#pragma token VARIETY %s # %s\n", nm, tnm ) ;
		OUT ( output, "#pragma promote %s : %s\n", nm, nm ) ;
		OUT ( output, "#pragma interface %s\n", nm ) ;
	    }
	    OUT ( output, "#endif /* %s */\n", b ) ;
	    break ;
	}

	default : {
	    /* Other types */
	    error ( ERR_INTERNAL, "Unknown type identifier, '%d'\n", i ) ;
	    break ;
	}
    }
    return ;
}


/*
    PRINT A TOKEN

    This routine prints the object p, representing the token tnm, to the
    file output.
*/

static void print_token
    PROTO_N ( ( output, p, tnm ) )
    PROTO_T ( FILE *output X object *p X char *tnm )
{
    char *nm = p->name ;
    switch ( p->objtype ) {

	case OBJ_CONST :
	case OBJ_EXP : {
	    /* Constants and expressions */
	    type *t = p->u.u_type ;
	    OUTS ( output, "#pragma token EXP " ) ;
	    if ( p->objtype == OBJ_CONST && t->id == TYPE_RVALUE ) {
		OUTS ( output, "const : " ) ;
		t = t->u.subtype ;
	    }
	    print_type ( output, t, null_str, 1 ) ;
	    OUT ( output, " : %s # %s\n", nm, tnm ) ;
	    break ;
	}

	case OBJ_EXTERN : {
	    /* External expressions */
	    type *t = p->u.u_type ;
	    if ( t->id == TYPE_LVALUE ) t = t->u.subtype ;
	    OUTS ( output, "extern " ) ;
	    print_type ( output, t, nm, 0 ) ;
	    OUTS ( output, " ;\n" ) ;
	    break ;
	}

	case OBJ_WEAK : {
	    /* Weak prototype declarations */
	    int sp ;
	    char *w = WEAK_PROTO ;
	    type *t = p->u.u_type ;
	    if ( !weak_proto ) {
		char *b = BUILDING_MACRO ;
		OUT ( output, "#ifndef %s\n", w ) ;
		OUT ( output, "#ifndef %s\n", b ) ;
		OUT ( output, "#pragma TenDRA keyword %s_KEY for weak\n", w ) ;
		OUT ( output, "#define %s( A )\t%s_KEY A\n", w, w ) ;
		OUT ( output, "#else /* %s */\n", b ) ;
		OUT ( output, "#define %s( A )\t()\n", w ) ;
		OUT ( output, "#endif /* %s */\n", b ) ;
		OUT ( output, "#endif /* %s */\n\n", w ) ;
		weak_proto = 1 ;
	    }
	    OUTS ( output, "extern " ) ;
	    sp = print_head ( output, t, 0, 0 ) ;
	    if ( sp ) OUTC ( output, ' ' ) ;
	    OUT ( output, "%s %s (", nm, w ) ;
	    print_tail ( output, t, 0 ) ;
	    OUTS ( output, " ) ;\n" ) ;
	    break ;
	}

	case OBJ_DEFINE : {
	    /* Macro definitions */
	    char *s = p->u.u_str ;
	    OUT ( output, "#define %s%s\n", nm, s ) ;
	    break ;
	}

	case OBJ_FIELD : {
	    /* Field selectors */
	    field *f = p->u.u_field ;
	    OUTS ( output, "#pragma token MEMBER " ) ;
	    print_type ( output, f->ftype, null_str, 1 ) ;
	    OUTS ( output, " : " ) ;
	    print_type ( output, f->stype, null_str, 1 ) ;
	    OUT ( output, " : %s # %s\n", f->fname, tnm ) ;
	    break ;
	}

	case OBJ_FUNC : {
	    /* Functions */
	    type *t = p->u.u_type ;
	    OUTS ( output, "#pragma token FUNC " ) ;
	    print_type ( output, t, null_str, 1 ) ;
	    OUT ( output, " : %s # %s\n", nm, tnm ) ;
	    break ;
	}

	case OBJ_MACRO : {
	    /* Macros */
	    type *t = p->u.u_type ;
	    type *s = t->v.next ;
	    OUTS ( output, "#pragma token PROC ( " ) ;
	    /* Print the macro arguments */
	    while ( s && s != type_none  ) {
		OUTS ( output, "EXP " ) ;
		print_type ( output, s->u.subtype, null_str, 1 ) ;
		s = s->v.next ;
		OUTS ( output, ( s ? " : , " : " : " ) ) ;
	    }
	    /* Print the macro result */
	    OUTS ( output, ") EXP " ) ;
	    print_type ( output, t->u.subtype, null_str, 1 ) ;
	    OUT ( output, " : %s # %s\n", nm, tnm ) ;
	    break ;
	}

	case OBJ_NAT : {
	    /* Nats */
	    OUT ( output, "#pragma token NAT %s # %s\n", nm, tnm ) ;
	    break ;
	}

	case OBJ_STATEMENT : {
	    /* Statements */
	    type *t = p->u.u_type ;
	    if ( t != null ) {
		/* Statements with arguments */
		type *s = t->v.next ;
		OUTS ( output, "#pragma token PROC ( " ) ;
		while ( s && s != type_none ) {
		    OUTS ( output, "EXP " ) ;
		    print_type ( output, s->u.subtype, null_str, 1 ) ;
		    s = s->v.next ;
		    OUTS ( output, ( s ? " : , " : " : " ) ) ;
		}
		OUT ( output, ") STATEMENT %s # %s\n", nm, tnm ) ;
	    } else {
		/* Statements with no arguments */
		OUT ( output, "#pragma token STATEMENT %s # %s\n", nm, tnm ) ;
	    }
	    break ;
	}

	case OBJ_TOKEN : {
	    /* Tokens */
	    char *s = p->u.u_str ;
	    OUT ( output, "#pragma token %s %s # %s\n", s, nm, tnm ) ;
	    break ;
	}

	case OBJ_TYPE : {
	    /* Types */
	    print_token_type ( output, p, tnm ) ;
	    break ;
	}

	default : {
	    /* Unknown objects */
	    error ( ERR_INTERNAL, "Unknown object type, '%d'", p->objtype ) ;
	    break ;
	}
    }
    return ;
}


/*
    TYPE REPRESENTING AN IF STATEMENT

    All if, else and endif statements are stored and simplified prior to
    output.  The ifcmd structure is used to represent the commands, with
    the dir field giving the command type and the nm field the associated
    expression.
*/

typedef struct {
    int dir ;
    char *nm ;
} ifcmd ;


/*
    PRINT A NUMBER OF IF STATEMENTS

    This routine outputs the list of if statements, ifs, to the file
    output.
*/

static void print_ifs
    PROTO_N ( ( output, ifs ) )
    PROTO_T ( FILE *output X ifcmd *ifs )
{
    ifcmd *p ;
    boolean changed ;

    /* Simplify the list of statements */
    do {
	ifcmd *q = null ;
	changed = 0 ;
	for ( p = ifs ; p->dir != CMD_END ; p++ ) {
	    int d = p->dir ;
	    if ( d != CMD_NONE ) {
		if ( q && q->dir != CMD_NONE ) {
		    int e = q->dir ;
		    if ( d == CMD_ENDIF ) {
			if ( e == CMD_ELSE ) {
			    /* else + endif -> endif */
			    q->dir = CMD_NONE ;
			    changed = 1 ;
			} else if ( e != CMD_ENDIF ) {
			    /* if + endif -> nothing */
			    p->dir = CMD_NONE ;
			    q->dir = CMD_NONE ;
			    changed = 1 ;
			}
		    }
		    if ( d == CMD_ELSE ) {
			if ( e == CMD_IFDEF ) {
			    /* ifdef + else -> ifndef */
			    p->dir = CMD_IFNDEF ;
			    q->dir = CMD_NONE ;
			    changed = 1 ;
			} else if ( e == CMD_IFDEF ) {
			    /* ifndef + else -> ifdef */
			    p->dir = CMD_IFDEF ;
			    q->dir = CMD_NONE ;
			    changed = 1 ;
			}
		    }
		}
		q = p ;
	    }
	}
    } while ( changed ) ;

    /* Print the result */
    if ( column ) OUTC ( output, '\n' ) ;
    for ( p = ifs ; p->dir != CMD_END ; p++ ) {
	switch ( p->dir ) {
	    case CMD_IF : {
		OUT ( output, "#if %s\n", p->nm ) ;
		break ;
	    }
	    case CMD_IFDEF : {
		OUT ( output, "#ifdef %s\n", p->nm ) ;
		break ;
	    }
	    case CMD_IFNDEF : {
		OUT ( output, "#ifndef %s\n", p->nm ) ;
		break ;
	    }
	    case CMD_ELSE : {
		OUT ( output, "#else /* %s */\n", p->nm ) ;
		break ;
	    }
	    case CMD_ENDIF : {
		OUT ( output, "#endif /* %s */\n", p->nm ) ;
		break ;
	    }
	}
    }
    column = 0 ;
    ifs [0].dir = CMD_END ;
    return ;
}


/*
    PRINT AN INTERFACE ITEM

    This routine prints an interface statement for the object p to the
    file output.
*/

static void print_interface
    PROTO_N ( ( output, p, ifs ) )
    PROTO_T ( FILE *output X object *p X ifcmd *ifs )
{
    char *nm = p->name ;
    switch ( p->objtype ) {

	case OBJ_CONST :
	case OBJ_EXP :
	case OBJ_MACRO :
	case OBJ_NAT :
	case OBJ_STATEMENT :
	case OBJ_TOKEN : {
	    /* Simple tokens are easy */
	    break ;
	}

	case OBJ_EXTERN :
	case OBJ_WEAK : {
	    /* Deal with externals */
	    nm = null ;
	    break ;
	}

	case OBJ_FIELD : {
	    /* Deal with fields */
	    field *f = p->u.u_field ;
	    switch ( f->stype->id ) {
		case TYPE_STRUCT_TAG :
		case TYPE_UNION_TAG : {
		    /* Tagged types require some attention */
		    IGNORE sprintf ( buffer, "TAG %s", nm ) ;
		    nm = buffer ;
		    break ;
		}
	    }
	    break ;
	}

	case OBJ_FUNC : {
	    /* Functions containing ... are not actually tokens */
	    type *t = p->u.u_type->v.next ;
	    while ( t != null ) {
		if ( t->u.subtype == type_ellipsis ) {
		    nm = null ;
		    break ;
		}
		t = t->v.next ;
	    }
	    break ;
	}

	case OBJ_DEFINE : {
	    /* Macro definitions are not tokens */
	    nm = null ;
	    break ;
	}

	case OBJ_TYPE : {
	    /* Deal with types */
	    type *t = p->u.u_type ;
	    switch ( t->id ) {
		case TYPE_STRUCT_TAG :
		case TYPE_UNION_TAG : {
		    /* Tagged types require some attention */
		    IGNORE sprintf ( buffer, "TAG %s", nm ) ;
		    nm = buffer ;
		    goto type_struct_lab ;
		}
		case TYPE_STRUCT :
		case TYPE_UNION :
		type_struct_lab : {
		    /* Some structures and unions are not tokens */
		    if ( t->v.obj2 ) {
			if ( t->state == 2 ) {
			    t->state = 3 ;
			} else {
			    nm = null ;
			}
		    }
		    break ;
		}
		case TYPE_DEFINED : {
		    /* Type definitions are not tokens */
		    nm = null ;
		    break ;
		}
		case TYPE_ENUM :
		case TYPE_ENUM_TAG : {
		    /* Enumeration types are not tokens */
		    nm = null ;
		    break ;
		}
	    }
	    break ;
	}

	default : {
	    /* Unknown objects */
	    error ( ERR_INTERNAL, "Unknown object type, '%d'", p->objtype ) ;
	    nm = null ;
	    break ;
	}
    }

    /* Print the interface statement */
    if ( nm ) {
	int n = ( int ) strlen ( nm ) + 1 ;
	if ( ifs [0].dir != CMD_END ) print_ifs ( output, ifs ) ;
	if ( column + n >= 60 ) {
	    OUTC ( output, '\n' ) ;
	    column = 0 ;
	}
	if ( column == 0 ) OUTS ( output, "#pragma interface" ) ;
	OUTC ( output, ' ' ) ;
	OUTS ( output, nm ) ;
	column += n ;
    }
    return ;
}


/*
    PRINT AN INCLUDED FILE
*/

static void print_include
    PROTO_N ( ( output, nm, on ) )
    PROTO_T ( FILE *output X char *nm X int on )
{
    object *p ;
    if ( nm == null ) return ;
    IGNORE sprintf ( buffer, "%s[%s]", crt_info->src, nm ) ;
    if ( search_hash ( files, buffer, no_version ) ) return ;
    p = make_object ( string_copy ( buffer ), OBJ_FILE ) ;
    p->u.u_file = null ;
    IGNORE add_hash ( files, p, no_version ) ;
    if ( on ) OUT ( output, "#include <%s>\n", nm ) ;
    return ;
}


/*
    PRINT AN OBJECT

    This routine prints the list of objects input to the file output, the
    form of the information to be printed being indicated by pass.
*/

static void print_object
    PROTO_N ( ( output, input, pass ) )
    PROTO_T ( FILE *output X object *input X int pass )
{
    object *p ;
    ifcmd ifs [100] ;
    ifs [0].dir = CMD_END ;
    for ( p = input ; p != null ; p = p->next ) {
	char *nm = p->name ;
	switch ( p->objtype ) {

	    case OBJ_IF	 : {
		/* If statements etc. */
		if ( pass != 1 ) {
		    int i = 0 ;
		    while ( ifs [i].dir != CMD_END ) i++ ;
		    ifs [i].dir = p->u.u_num ;
		    ifs [i].nm = p->name ;
		    ifs [ i + 1 ].dir = CMD_END ;
		    if ( i >= 90 ) print_ifs ( output, ifs ) ;
		}
		break ;
	    }

	    case OBJ_IMPLEMENT :
	    case OBJ_USE : {
		/* Inclusion statements */
		if ( pass < 2 && nm [ pass ] == '1' ) {
		    object *q = p->u.u_obj ;
		    info *i = q->u.u_info ;
		    char *b = BUILDING_MACRO ;
		    if ( streq ( i->api, LOCAL_API ) ) break ;
		    if ( ifs [0].dir != CMD_END ) print_ifs ( output, ifs ) ;
		    if ( pass == 0 ) {
			char *f ;
			char *dir ;
			char *m = i->protect ;
			int n = output_incl_len ;
			if ( nm [2] == 'G' ) {
			    OUT ( output, "#ifndef %s\n", b ) ;
			    dir = "#pragma extend interface [%s]\n" ;
			    OUT ( output, dir, i->file ) ;
			    OUT ( output, "#else /* %s */\n", b ) ;
			    m = "" ;
			}
			if ( *m ) OUT ( output, "#ifndef %s\n", m ) ;
			if ( local_input ) {
			    f = i->incl + n ;
			    dir = "#pragma extend interface <../%s>\n" ;
			} else {
			    f = relative ( crt_info->incl, i->incl, n ) ;
			    dir = "#pragma extend interface \"%s\"\n" ;
			}
			OUT ( output, dir, f ) ;
			if ( *m ) OUT ( output, "#endif /* %s */\n", m ) ;
			if ( nm [2] == 'G' ) {
			    OUT ( output, "#endif /* %s */\n", b ) ;
			}
		    } else {
			print_include ( output, i->file, 1 ) ;
		    }
		}
		break ;
	    }

	    case OBJ_SET : {
		/* Subsets */
		object *q = p->u.u_obj ;
		info *i = q->u.u_info ;
		if ( streq ( i->api, LOCAL_API ) ) {
		    if ( ifs [0].dir != CMD_END ) print_ifs ( output, ifs ) ;
		    print_object ( output, i->elements, pass ) ;
		} else {
		    if ( pass < 2 ) {
			if ( ifs [0].dir != CMD_END ) {
			    print_ifs ( output, ifs ) ;
			}
			print_set ( p, pass ) ;
		    }
		}
		break ;
	    }

	    case OBJ_TEXT_INCL : {
		/* Include file quoted text */
		if ( pass == 0 ) {
		    if ( ifs [0].dir != CMD_END ) print_ifs ( output, ifs ) ;
		    OUTS ( output, nm ) ;
		    OUTC ( output, '\n' ) ;
		}
		break ;
	    }

	    case OBJ_TEXT_SRC : {
		/* Source file quoted text */
		if ( pass == 1 ) {
		    if ( ifs [0].dir != CMD_END ) print_ifs ( output, ifs ) ;
		    OUTS ( output, nm ) ;
		    OUTC ( output, '\n' ) ;
		}
		break ;
	    }

	    case OBJ_TOKEN : {
		/* Tokenised objects */
		if ( pass == 0 ) {
		    if ( ifs [0].dir != CMD_END ) print_ifs ( output, ifs ) ;
		    print_token ( output, p->u.u_obj, nm ) ;
		} else if ( pass == 2 ) {
		    print_interface ( output, p->u.u_obj, ifs ) ;
		}
		break ;
	    }

	    case OBJ_TYPE : {
		/* Definition of previously declared type */
		if ( pass == 0 ) {
		    type *t = p->u.u_type ;
		    char *tnm = t->u.obj->name ;
		    print_struct_defn ( output, t, tnm, tnm, 1 ) ;
		}
		break ;
	    }

	    default : {
		/* Unknown objects */
		char *err = "Unknown object type, '%d'" ;
		error ( ERR_INTERNAL, err, p->objtype ) ;
		break ;
	    }
	}
    }
    if ( ifs [0].dir != CMD_END ) print_ifs ( output, ifs ) ;
    return ;
}


/*
    SCAN AN OBJECT

    This routine scans the object input, calling print_set on any subsets.
*/

static void scan_object
    PROTO_N ( ( input, pass ) )
    PROTO_T ( object *input X int pass )
{
    object *p ;
    for ( p = input ; p != null ; p = p->next ) {
	if ( p->objtype == OBJ_SET ) {
	    object *q = p->u.u_obj ;
	    info *i = q->u.u_info ;
	    if ( streq ( i->api, LOCAL_API ) ) {
		scan_object ( i->elements, pass ) ;
	    } else {
		if ( pass < 2 ) print_set ( p, pass ) ;
	    }
	}
    }
    return ;
}


/*
    PRINT A SET

    This routine prints the set of objects given by input.  The form of the
    output is indicated by pass.
*/

void print_set
    PROTO_N ( ( input, pass ) )
    PROTO_T ( object *input X int pass )
{
    char *nm ;
    time_t t1, t2 ;
    FILE *output = null ;
    object *ss = input->u.u_obj ;
    info *i = ss->u.u_info ;
    column = 0 ;

    if ( streq ( i->api, LOCAL_API ) ) {
	/* Local files go to the standard output */
	if ( pass != 0 ) return ;
	nm = "stdout" ;
	output = stdout ;
	t1 = ( time_t ) 0 ;
	t2 = ( time_t ) 0 ;
    } else {
	nm = ( pass ? i->src : i->incl ) ;
	if ( nm == null || ( restrict_use && i->implemented == 0 ) ) {
	    scan_object ( i->elements, 1 ) ;
	    return ;
	}
	if ( pass == 1 && i->tokens == 0 ) {
	    if ( verbose > 1 ) {
		error ( ERR_INFO, "%s is not required ...", nm ) ;
	    }
	    scan_object ( i->elements, 1 ) ;
	    return ;
	}
	t1 = i->age ;
	if ( progdate > t1 ) t1 = progdate ;
	t2 = date_stamp ( nm ) ;
    }

    if ( ( t1 && t1 < t2 ) && !force_output ) {
	/* Output file is up to date */
	object *q ;
	if ( verbose > 1 ) error ( ERR_INFO, "%s is up to date ...", nm ) ;
	q = make_object ( nm, OBJ_FILE ) ;
	q->u.u_file = null ;
	IGNORE add_hash ( files, q, no_version ) ;
	for ( q = i->elements ; q != null ; q = q->next ) {
	    if ( q->objtype == OBJ_SET ) print_set ( q, pass ) ;
	}
    } else {
	/* Output file needs updating */
	object *q = null ;
	info *old_info = crt_info ;
	int old_column = column ;
	boolean old_weak_proto = weak_proto ;
	weak_proto = 0 ;

	/* Open output file */
	if ( output == null ) {
	    create_dir ( nm ) ;
	    if ( verbose ) error ( ERR_INFO, "Creating %s ...", nm ) ;
	    check_name ( nm ) ;
	    q = make_object ( nm, OBJ_FILE ) ;
	    q->u.u_file = null ;
	    IGNORE add_hash ( files, q, no_version ) ;
	    output = fopen ( nm, "w" ) ;
	    q->u.u_file = output ;
	    if ( output == null ) {
		error ( ERR_SERIOUS, "Can't open output file, %s", nm ) ;
		return ;
	    }
	}

	crt_info = i ;
	if ( pass == 0 ) {
	    /* Include output file */
	    char *m = i->protect ;
	    char *v = i->version ;

	    /* Print the copyright message */
	    if ( copyright ) {
		if ( copyright_text == null ) {
		    FILE *f = fopen ( copyright, "r" ) ;
		    if ( f == null ) {
			char *err = "Can't open copyright file, %s" ;
			error ( ERR_SERIOUS, err, copyright ) ;
			copyright_text = "" ;
		    } else {
			int c, j = 0 ;
			while ( c = getc ( f ), c != EOF ) {
			    buffer [j] = ( char ) c ;
			    if ( ++j >= buffsize ) {
				error ( ERR_SERIOUS, "Copyright too long" ) ;
				break ;
			    }
			}
			buffer [j] = 0 ;
			copyright_text = string_copy ( buffer ) ;
			IGNORE fclose ( f ) ;
		    }
		}
		OUTS ( output, copyright_text ) ;
	    }

	    /* Find the version number */
	    if ( v == null && i->subset ) {
		char *a = subset_name ( i->api, i->file, null_str ) ;
		object *ap = make_subset ( a ) ;
		v = ap->u.u_info->version ;
	    }
	    if ( v == null && i->file ) {
		char *a = subset_name ( i->api, null_str, null_str ) ;
		object *ap = make_subset ( a ) ;
		v = ap->u.u_info->version ;
	    }

	    /* Print the file header */
	    OUTS ( output, "/*\n    AUTOMATICALLY GENERATED BY " ) ;
	    OUT ( output, "%s %s\n", progname, progvers ) ;
	    OUT ( output, "    API SUBSET: %s", ss->name ) ;
	    if ( v ) OUT ( output, " (VERSION %s)", v ) ;
	    OUTS ( output, "\n*/\n\n" ) ;

	    /* Print the file body */
	    if ( *m ) {
		OUT ( output, "#ifndef %s\n", m ) ;
		OUT ( output, "#define %s\n\n", m ) ;
	    }
	    if ( i->elements ) {
		boolean is_cpplus = 0 ;
		if ( i->linkage ) {
		    if ( streq ( i->linkage, "C++" ) ) {
			OUT ( output, "extern \"%s\" {\n\n", i->linkage ) ;
			is_cpplus = 1 ;
		    } else {
			OUT ( output, "#ifdef __cplusplus\n" ) ;
			OUT ( output, "extern \"%s\" {\n", i->linkage ) ;
			OUT ( output, "#endif\n\n" ) ;
		    }
		}
		if ( i->nspace ) {
		    if ( is_cpplus ) {
			OUT ( output, "namespace %s {\n\n", i->nspace ) ;
		    } else {
			OUT ( output, "#ifdef __cplusplus\n" ) ;
			OUT ( output, "namespace %s {\n", i->nspace ) ;
			OUT ( output, "#endif\n\n" ) ;
		    }
		}
		if ( i->block ) {
		    char *dir ;
		    dir = "#pragma TenDRA declaration block %s begin\n\n" ;
		    OUT ( output, dir, i->block ) ;
		}
		print_object ( output, i->elements, 0 ) ;
		if ( i->tokens ) OUTC ( output, '\n' ) ;
		print_object ( output, i->elements, 2 ) ;
		if ( column ) OUTC ( output, '\n' ) ;
		if ( i->block ) {
		    char *dir ;
		    dir = "\n#pragma TenDRA declaration block end\n" ;
		    OUT ( output, dir ) ;
		}
		if ( i->nspace ) {
		    if ( is_cpplus ) {
			OUT ( output, "\n}\n" ) ;
		    } else {
			OUT ( output, "\n#ifdef __cplusplus\n" ) ;
			OUT ( output, "}\n" ) ;
			OUT ( output, "#endif\n" ) ;
		    }
		}
		if ( i->linkage ) {
		    if ( is_cpplus ) {
			OUT ( output, "\n}\n" ) ;
		    } else {
			OUT ( output, "\n#ifdef __cplusplus\n" ) ;
			OUT ( output, "}\n" ) ;
			OUT ( output, "#endif\n" ) ;
		    }
		}
	    }
	    if ( *m ) OUT ( output, "\n#endif /* %s */\n", m ) ;

	} else {
	    /* Source output file */
	    if ( i->method == null ) {
		char *m, *s ;
		char *w1, *w2 ;
		int n = output_incl_len ;
		m = macro_name ( DEFINE_PREFIX, i->api, i->file, i->subset ) ;
		w1 = macro_name ( WRONG_PREFIX, i->api, null_str, null_str ) ;
		w2 = macro_name ( WRONG_PREFIX, i->api, i->file, i->subset ) ;
		s = i->incl + n ;
		OUTS ( output, "/* AUTOMATICALLY GENERATED BY " ) ;
		OUT ( output, "%s %s */\n", progname, progvers ) ;
		OUT ( output, "#ifndef %s\n", w1 ) ;
		OUT ( output, "#ifndef %s\n", w2 ) ;
		OUT ( output, "#if #include ( %s )\n", i->file ) ;
		OUT ( output, "#define %s\n", m ) ;
		print_include ( output, i->file, 0 ) ;
		print_object ( output, i->elements, 1 ) ;
		OUT ( output, "#include <%s>\n", i->file ) ;
		OUT ( output, "#endif\n" ) ;
		OUT ( output, "#endif\n\n" ) ;
		OUT ( output, "#ifndef %s\n", m ) ;
		OUT ( output, "#pragma TenDRA no token definition allow\n" ) ;
		OUT ( output, "#endif\n" ) ;
		OUT ( output, "#pragma implement interface <../%s>\n", s ) ;
		OUT ( output, "#endif\n" ) ;
	    } else {
		print_object ( output, i->elements, 1 ) ;
	    }
	}

	/* End the output */
	IGNORE fclose ( output ) ;
	if ( q ) q->u.u_file = null ;
	crt_info = old_info ;
	column = old_column ;
	weak_proto = old_weak_proto ;
    }
    return ;
}
