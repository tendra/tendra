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
#include "calculus.h"
#include "error.h"
#include "common.h"
#include "type_ops.h"
#include "xalloc.h"


/*
    TYPE REPRESENTING A LIST OF ALGEBRAS

    This type is used to represent the list of all algebras.
*/

typedef struct ALGEBRA_LIST_tag {
    ALGEBRA_DEFN alg ;
    struct ALGEBRA_LIST_tag *next ;
} ALGEBRA_LIST ;


/*
    CURRENT ALGEBRA

    The variable algebra holds all the information on the algebra read
    from the input file.  The list all_algebras contains a list of all
    the algebras defined.
*/

ALGEBRA_DEFN *algebra = NULL ;
static ALGEBRA_LIST *all_algebras = NULL ;


/*
    CREATE A NEW ALGEBRA

    This routine allocates and initialises a new algebra structure.
*/

void new_algebra
    PROTO_Z ()
{
    ALGEBRA_LIST *p = xmalloc_nof ( ALGEBRA_LIST, 1 ) ;
    p->alg.name = "ALGEBRA" ;
    p->alg.major_no = 1 ;
    p->alg.minor_no = 0 ;
    p->alg.primitives = NULL_list ( PRIMITIVE_P ) ;
    p->alg.identities = NULL_list ( IDENTITY_P ) ;
    p->alg.enumerations = NULL_list ( ENUM_P ) ;
    p->alg.structures = NULL_list ( STRUCTURE_P ) ;
    p->alg.unions = NULL_list ( UNION_P ) ;
    p->alg.types = NULL_list ( TYPE_P ) ;
    p->next = all_algebras ;
    all_algebras = p ;
    algebra = &( p->alg ) ;
    return ;
}


/*
    LOOK UP AN ALGEBRA

    This routine looks up the algebra named nm.  It returns null if the
    algebra has not been defined.
*/

ALGEBRA_DEFN *find_algebra
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    ALGEBRA_LIST *p ;
    for ( p = all_algebras ; p != NULL ; p = p->next ) {
	if ( streq ( p->alg.name, nm ) ) return ( &( p->alg ) ) ;
    }
    return ( NULL ) ;
}


/*
    LAST IDENTIFIER

    This variable is set by name_type and name_aux_type to the identifier
    of the last non-composite type looked up.
*/

static CLASS_ID_P last_id = NULL_ptr ( CLASS_ID ) ;


/*
    REGISTER A TYPE

    This routine adds the type t to the list of all types.
*/

TYPE_P register_type
    PROTO_N ( ( t ) )
    PROTO_T ( TYPE_P t )
{
    char *nm = name_type ( t ) ;
    CLASS_ID_P id = last_id ;
    LIST ( TYPE_P ) r = algebra->types ;
    while ( !IS_NULL_list ( r ) ) {
	TYPE_P s = DEREF_ptr ( HEAD_list ( r ) ) ;
	if ( streq ( name_type ( s ), nm ) ) {

	    /* Check for multiple definition */
	    if ( !IS_type_undef ( DEREF_type ( s ) ) ) {
		char *fn1 = DEREF_string ( cid_file ( id ) ) ;
		int ln1 = DEREF_int ( cid_line ( id ) ) ;
		char *fn2 = DEREF_string ( cid_file ( last_id ) ) ;
		int ln2 = DEREF_int ( cid_line ( last_id ) ) ;
		if ( fn2 == crt_file_name ) {
		    char *fn = fn1 ;
		    int ln = ln1 ;
		    fn1 = fn2 ;
		    ln1 = ln2 ;
		    fn2 = fn ;
		    ln2 = ln ;
		}
		error_posn ( ERROR_SERIOUS, fn1, ln1,
			     "Type %s already defined (at %s, line %d)",
			     nm, fn2, ln2 ) ;
	    }

	    COPY_type ( s, DEREF_type ( t ) ) ;
	    return ( s ) ;
	}
	r = TAIL_list ( r ) ;
    }
    CONS_ptr ( t, algebra->types, algebra->types ) ;
    return ( t ) ;
}


/*
    LOOK UP A NAMED TYPE

    This routine looks up the type named nm in the list of all types
    associated with the algebra alg.  The type is created if necessary,
    and the result is returned.
*/

TYPE_P find_type
    PROTO_N ( ( alg, nm ) )
    PROTO_T ( ALGEBRA_DEFN *alg X char *nm )
{
    TYPE s0 ;
    TYPE_P s ;
    LIST ( TYPE_P ) t = alg->types ;
    while ( !IS_NULL_list ( t ) ) {
	s = DEREF_ptr ( HEAD_list ( t ) ) ;
	if ( streq ( name_type ( s ), nm ) ) return ( s ) ;
	t = TAIL_list ( t ) ;
    }
    s = MAKE_ptr ( SIZE_type ) ;
    MAKE_type_undef ( 0, nm, s0 ) ;
    COPY_type ( s, s0 ) ;
    s = register_type ( s ) ;
    return ( s ) ;
}


/*
    DOES A TYPE INVOLVE AN IDENTITY

    This routine checks whether the type t is an identity or a compound
    type derived from an identity.
*/

int is_identity_type
    PROTO_N ( ( t ) )
    PROTO_T ( TYPE_P t )
{
    TYPE t0 = DEREF_type ( t ) ;
    while ( IS_type_ptr_etc ( t0 ) ) {
	t0 = DEREF_type ( DEREF_ptr ( type_ptr_etc_sub ( t0 ) ) ) ;
    }
    return ( IS_type_ident ( t0 ) ) ;
}


/*
    DEAL WITH COMPOUND TYPES INVOLVING IDENTITIES

    From the point of view of the list of all types, identity types are
    distinct from their definitions.  This routine is called after creating
    a compound type, r, to ensure that the corresponding type with any
    identities replaced by their definition is also created.
*/

static TYPE_P compound_identity
    PROTO_N ( ( r, depth ) )
    PROTO_T ( TYPE_P r X int depth )
{
    TYPE r0 = DEREF_type ( r ) ;
    if ( depth > MAX_TYPE_DEPTH ) {
	error ( ERROR_SERIOUS, "Cyclic type definition involving %s",
		name_type ( r ) ) ;
	return ( NULL_ptr ( TYPE ) ) ;
    }
    if ( IS_type_ident ( r0 ) ) {
	IDENTITY_P a = DEREF_ptr ( type_ident_id ( DEREF_type ( r ) ) ) ;
	TYPE_P s = DEREF_ptr ( ident_defn ( a ) ) ;
	return ( s ) ;
    }
    if ( IS_type_ptr_etc ( r0 ) ) {
	unsigned tag = TAG_type ( r0 ) ;
	TYPE_P s = DEREF_ptr ( type_ptr_etc_sub ( r0 ) ) ;
	s = compound_identity ( s, depth ) ;
	if ( !IS_NULL_ptr ( s ) ) {
	    return ( compound_type ( tag, s, depth + 1 ) ) ;
	}
    }
    return ( NULL_ptr ( TYPE ) ) ;
}


/*
    CREATE A COMPOUND TYPE

    This routine creates a compound type from the type operation indicated
    by tag and the sub-type r.  The routine is designed to ensure that
    only one copy of each type is created.
*/

TYPE_P compound_type
    PROTO_N ( ( tag, r, depth ) )
    PROTO_T ( unsigned tag X TYPE_P r X int depth )
{
    TYPE s0 ;
    TYPE_P s ;
    LIST ( TYPE_P ) t = algebra->types ;

    /* Search for uses */
    while ( !IS_NULL_list ( t ) ) {
	s = DEREF_ptr ( HEAD_list ( t ) ) ;
	s0 = DEREF_type ( s ) ;
	if ( TAG_type ( s0 ) == tag ) {
	    TYPE_P rr = DEREF_ptr ( type_ptr_etc_sub ( s0 ) ) ;
	    if ( EQ_ptr ( r, rr ) ) return ( s ) ;
	}
	t = TAIL_list ( t ) ;
    }
    s = MAKE_ptr ( SIZE_type ) ;
    MAKE_type_ptr_etc ( tag, 0, r, s0 ) ;
    COPY_type ( s, s0 ) ;
    CONS_ptr ( s, algebra->types, algebra->types ) ;
    ( void ) compound_identity ( s, depth ) ;
    return ( s ) ;
}


/*
    CHECK FOR UNDEFINED TYPES

    This routine scans the list of all types for any which remain undefined
    at the end of the compilation.  It also calculates the sizes of all
    the defined types.
*/

void check_types
    PROTO_Z ()
{
    LIST ( TYPE_P ) t = algebra->types ;
    while ( !IS_NULL_list ( t ) ) {
	TYPE_P s = DEREF_ptr ( HEAD_list ( t ) ) ;
	TYPE s0 = DEREF_type ( s ) ;
	if ( IS_type_undef ( s0 ) ) {
	    char *nm = name_type ( s ) ;
	    error ( ERROR_SERIOUS, "Type %s used but not defined", nm ) ;
	} else {
	    int sz = size_type ( s, 0 ) ;
	    COPY_int ( type_size ( s0 ), sz ) ;
	}
	t = TAIL_list ( t ) ;
    }
    return ;
}


/*
    FIND LIST OF DERIVED TYPES

    This routine builds up a list of all the types used in the derivation
    of t.
*/

static LIST ( TYPE_P ) derived_types
    PROTO_N ( ( t, p ) )
    PROTO_T ( TYPE_P t X LIST ( TYPE_P ) p )
{
    TYPE t0 ;
    unsigned tag ;
    LIST ( TYPE_P ) q = p ;
    while ( !IS_NULL_list ( q ) ) {
	TYPE_P s = DEREF_ptr ( HEAD_list ( q ) ) ;
	if ( EQ_ptr ( s, t ) ) return ( p ) ;
	q = TAIL_list ( q ) ;
    }
    CONS_ptr ( t, p, p ) ;
    t0 = DEREF_type ( t ) ;
    tag = TAG_type ( t0 ) ;
    switch ( tag ) {

	case type_ident_tag : {
	    /* Identity definition */
	    IDENTITY_P r = DEREF_ptr ( type_ident_id ( t0 ) ) ;
	    TYPE_P s = DEREF_ptr ( ident_defn ( r ) ) ;
	    p = derived_types ( s, p ) ;
	    break ;
	}

	case type_structure_tag : {
	    /* Structure components */
	    STRUCTURE_P r = DEREF_ptr ( type_structure_struc ( t0 ) ) ;
	    LIST ( COMPONENT_P ) c = DEREF_list ( str_defn ( r ) ) ;
	    while ( !IS_NULL_list ( c ) ) {
		COMPONENT_P cmp = DEREF_ptr ( HEAD_list ( c ) ) ;
		TYPE_P s = DEREF_ptr ( cmp_type ( cmp ) ) ;
		p = derived_types ( s, p ) ;
		c = TAIL_list ( c ) ;
	    }
	    break ;
	}

	case type_onion_tag : {
	    /* Union components, fields and maps */
	    UNION_P r = DEREF_ptr ( type_onion_un ( t0 ) ) ;
	    LIST ( COMPONENT_P ) c = DEREF_list ( un_s_defn ( r ) ) ;
	    LIST ( FIELD_P ) f = DEREF_list ( un_u_defn ( r ) ) ;
	    LIST ( MAP_P ) m = DEREF_list ( un_map ( r ) ) ;
	    while ( !IS_NULL_list ( c ) ) {
		COMPONENT_P cmp = DEREF_ptr ( HEAD_list ( c ) ) ;
		TYPE_P s = DEREF_ptr ( cmp_type ( cmp ) ) ;
		p = derived_types ( s, p ) ;
		c = TAIL_list ( c ) ;
	    }
	    while ( !IS_NULL_list ( f ) ) {
		FIELD_P fld = DEREF_ptr ( HEAD_list ( f ) ) ;
		c = DEREF_list ( fld_defn ( fld ) ) ;
		while ( !IS_NULL_list ( c ) ) {
		    COMPONENT_P cmp = DEREF_ptr ( HEAD_list ( c ) ) ;
		    TYPE_P s = DEREF_ptr ( cmp_type ( cmp ) ) ;
		    p = derived_types ( s, p ) ;
		    c = TAIL_list ( c ) ;
		}
		f = TAIL_list ( f ) ;
	    }
	    while ( !IS_NULL_list ( m ) ) {
		MAP_P map = DEREF_ptr ( HEAD_list ( m ) ) ;
		LIST ( ARGUMENT_P ) a = DEREF_list ( map_args ( map ) ) ;
		TYPE_P s = DEREF_ptr ( map_ret_type ( map ) ) ;
		p = derived_types ( s, p ) ;
		while ( !IS_NULL_list ( a ) ) {
		    ARGUMENT_P arg = DEREF_ptr ( HEAD_list ( a ) ) ;
		    s = DEREF_ptr ( arg_type ( arg ) ) ;
		    p = derived_types ( s, p ) ;
		    a = TAIL_list ( a ) ;
		}
		m = TAIL_list ( m ) ;
	    }
	    break ;
	}

	case type_list_tag :
	case type_ptr_tag :
	case type_stack_tag :
	case type_vec_tag :
	case type_vec_ptr_tag : {
	    /* Pointer subtypes */
	    TYPE_P s = DEREF_ptr ( type_ptr_etc_sub ( t0 ) ) ;
	    p = derived_types ( s, p ) ;
	    break ;
	}
    }
    return ( p ) ;
}


/*
    IMPORT A LIST OF TYPES

    This routine imports all the types in the list t.
*/

static void import_type_list
    PROTO_N ( ( t ) )
    PROTO_T ( LIST ( TYPE_P ) t )
{
    while ( !IS_NULL_list ( t ) ) {
	TYPE_P s = DEREF_ptr ( HEAD_list ( t ) ) ;
	TYPE s0 = DEREF_type ( s ) ;
	unsigned tag = TAG_type ( s0 ) ;
	switch ( tag ) {
	    case type_primitive_tag : {
		PRIMITIVE_P p = DEREF_ptr ( type_primitive_prim ( s0 ) ) ;
		CONS_ptr ( p, algebra->primitives, algebra->primitives ) ;
		goto register_lab ;
	    }
	    case type_ident_tag : {
		IDENTITY_P p = DEREF_ptr ( type_ident_id ( s0 ) ) ;
		CONS_ptr ( p, algebra->identities, algebra->identities ) ;
		goto register_lab ;
	    }
	    case type_enumeration_tag : {
		ENUM_P p = DEREF_ptr ( type_enumeration_en ( s0 ) ) ;
		CONS_ptr ( p, algebra->enumerations, algebra->enumerations ) ;
		goto register_lab ;
	    }
	    case type_structure_tag : {
		STRUCTURE_P p = DEREF_ptr ( type_structure_struc ( s0 ) ) ;
		CONS_ptr ( p, algebra->structures, algebra->structures ) ;
		goto register_lab ;
	    }
	    case type_onion_tag : {
		UNION_P p = DEREF_ptr ( type_onion_un ( s0 ) ) ;
		CONS_ptr ( p, algebra->unions, algebra->unions ) ;
		goto register_lab ;
	    }
	    register_lab : {
		TYPE_P r = register_type ( s ) ;
		if ( !EQ_ptr ( r, s ) ) {
		    error ( ERROR_SERIOUS,
			    "Can't import previously used type %s",
			    name_type ( s ) ) ;
		}
		break ;
	    }
	    default : {
		TYPE_P p = DEREF_ptr ( type_ptr_etc_sub ( s0 ) ) ;
		( void ) compound_type ( tag, p, 0 ) ;
		break ;
	    }
	}
	t = TAIL_list ( t ) ;
    }
    return ;
}


/*
    IMPORT A SINGLE ITEM FROM AN ALGEBRA

    This routine imports the type named nm from the algebra alg into the
    current algebra.
*/

void import_type
    PROTO_N ( ( alg, nm ) )
    PROTO_T ( char *alg X char *nm )
{
    TYPE_P t ;
    LIST ( TYPE_P ) p ;
    ALGEBRA_DEFN *a = find_algebra ( alg ) ;
    if ( a == NULL ) {
	error ( ERROR_SERIOUS, "Algebra %s not defined", alg ) ;
	return ;
    } else if ( a == algebra ) {
	error ( ERROR_SERIOUS, "Can't import from current algebra" ) ;
	return ;
    }
    t = find_type ( a, nm ) ;
    if ( IS_type_undef ( DEREF_type ( t ) ) ) {
	error ( ERROR_SERIOUS, "Type %s::%s not defined", alg, nm ) ;
	return ;
    }
    p = derived_types ( t, NULL_list ( TYPE_P ) ) ;
    import_type_list ( p ) ;
    while ( !IS_NULL_list ( p ) ) {
	DESTROY_CONS_ptr ( destroy_calculus, t, p, p ) ;
	UNUSED ( t ) ;
    }
    return ;
}


/*
    IMPORT AN ENTIRE ALGEBRA

    This routine imports all the types in the algebra alg into the current
    algebra.
*/

void import_algebra
    PROTO_N ( ( alg ) )
    PROTO_T ( char *alg )
{
    ALGEBRA_DEFN *a = find_algebra ( alg ) ;
    if ( a == NULL ) {
	error ( ERROR_SERIOUS, "Algebra %s not defined", alg ) ;
	return ;
    } else if ( a == algebra ) {
	error ( ERROR_SERIOUS, "Can't import from current algebra" ) ;
	return ;
    }
    import_type_list ( a->types ) ;
    return ;
}


/*
    FIND THE SIZE OF A TYPE

    This routine calculates the size of the type t.
*/

int size_type
    PROTO_N ( ( t, depth ) )
    PROTO_T ( TYPE_P t X int depth )
{
    TYPE t0 = DEREF_type ( t ) ;
    int sz = DEREF_int ( type_size ( t0 ) ) ;
    if ( sz ) return ( sz ) ;

    if ( depth > MAX_TYPE_DEPTH ) {
	error ( ERROR_SERIOUS, "Cyclic type definition involving %s",
		name_type ( t ) ) ;
	return ( 1 ) ;
    }

    switch ( TAG_type ( t0 ) ) {
	case type_ident_tag : {
	    IDENTITY_P i = DEREF_ptr ( type_ident_id ( t0 ) ) ;
	    TYPE_P_P s = ident_defn ( i ) ;
	    sz = size_type ( DEREF_ptr ( s ), depth + 1 ) ;
	    break ;
	}

	case type_structure_tag : {
	    STRUCTURE_P str = DEREF_ptr ( type_structure_struc ( t0 ) ) ;
	    LIST ( COMPONENT_P ) c = DEREF_list ( str_defn ( str ) ) ;
	    sz = 0 ;
	    while ( !IS_NULL_list ( c ) ) {
		TYPE_P_P s ;
		s = cmp_type ( DEREF_ptr ( HEAD_list ( c ) ) ) ;
		sz += size_type ( DEREF_ptr ( s ), depth + 1 ) ;
		c = TAIL_list ( c ) ;
	    }
	    break ;
	}

	case type_primitive_tag : sz = SIZE_PRIM ; break ;
	case type_enumeration_tag : sz = SIZE_ENUM ; break ;
	case type_onion_tag : sz = SIZE_UNION ; break ;
	case type_ptr_tag : sz = SIZE_PTR ; break ;
	case type_list_tag : sz = SIZE_LIST ; break ;
	case type_stack_tag : sz = SIZE_STACK ; break ;
	case type_vec_tag : sz = SIZE_VEC ; break ;
	case type_vec_ptr_tag : sz = SIZE_VEC_PTR ; break ;

	default : {
	    error ( ERROR_SERIOUS, "Can't take size of type %s",
		    name_type ( t ) ) ;
	    sz = 1 ;
	    break ;
	}
    }
    return ( sz ) ;
}


/*
    FIND THE NAME OF A TYPE

    This routine finds the long name of the type t.
*/

char *name_type
    PROTO_N ( ( t ) )
    PROTO_T ( TYPE_P t )
{
    CLASS_ID_P id ;
    TYPE t0 = DEREF_type ( t ) ;
    switch ( TAG_type ( t0 ) ) EXHAUSTIVE {
	case type_primitive_tag : {
	    PRIMITIVE_P a = DEREF_ptr ( type_primitive_prim ( t0 ) ) ;
	    id = DEREF_ptr ( prim_id ( a ) ) ;
	    break ;
	}
	case type_ident_tag : {
	    IDENTITY_P a = DEREF_ptr ( type_ident_id ( t0 ) ) ;
	    id = DEREF_ptr ( ident_id ( a ) ) ;
	    break ;
	}
	case type_enumeration_tag : {
	    ENUM_P a = DEREF_ptr ( type_enumeration_en ( t0 ) ) ;
	    id = DEREF_ptr ( en_id ( a ) ) ;
	    break ;
	}
	case type_structure_tag : {
	    STRUCTURE_P a = DEREF_ptr ( type_structure_struc ( t0 ) ) ;
	    id = DEREF_ptr ( str_id ( a ) ) ;
	    break ;
	}
	case type_onion_tag : {
	    UNION_P a = DEREF_ptr ( type_onion_un ( t0 ) ) ;
	    id = DEREF_ptr ( un_id ( a ) ) ;
	    break ;
	}
	case type_quote_tag : {
	    char *a = DEREF_string ( type_quote_defn ( t0 ) ) ;
	    return ( a ) ;
	}
	case type_ptr_tag : {
	    return ( "PTR" ) ;
	}
	case type_list_tag : {
	    return ( "LIST" ) ;
	}
	case type_stack_tag : {
	    return ( "STACK" ) ;
	}
	case type_vec_tag : {
	    return ( "VEC" ) ;
	}
	case type_vec_ptr_tag : {
	    return ( "VEC_PTR" ) ;
	}
	case type_undef_tag : {
	    char *a = DEREF_string ( type_undef_name ( t0 ) ) ;
	    return ( a ) ;
	}
    }
    last_id = id ;
    return ( DEREF_string ( cid_name ( id ) ) ) ;
}


/*
    FIND THE AUXILIARY NAME OF A TYPE

    This routine finds the short name of the type t.
*/

char *name_aux_type
    PROTO_N ( ( t ) )
    PROTO_T ( TYPE_P t )
{
    CLASS_ID_P id ;
    TYPE t0 = DEREF_type ( t ) ;
    switch ( TAG_type ( t0 ) ) EXHAUSTIVE {
	case type_primitive_tag : {
	    PRIMITIVE_P a = DEREF_ptr ( type_primitive_prim ( t0 ) ) ;
	    id = DEREF_ptr ( prim_id ( a ) ) ;
	    break ;
	}
	case type_ident_tag : {
	    IDENTITY_P a = DEREF_ptr ( type_ident_id ( t0 ) ) ;
	    return ( name_aux_type ( DEREF_ptr ( ident_defn ( a ) ) ) ) ;
	}
	case type_enumeration_tag : {
	    ENUM_P a = DEREF_ptr ( type_enumeration_en ( t0 ) ) ;
	    id = DEREF_ptr ( en_id ( a ) ) ;
	    break ;
	}
	case type_structure_tag : {
	    STRUCTURE_P a = DEREF_ptr ( type_structure_struc ( t0 ) ) ;
	    id = DEREF_ptr ( str_id ( a ) ) ;
	    break ;
	}
	case type_onion_tag : {
	    UNION_P a = DEREF_ptr ( type_onion_un ( t0 ) ) ;
	    id = DEREF_ptr ( un_id ( a ) ) ;
	    break ;
	}
	case type_quote_tag : {
	    char *a = DEREF_string ( type_quote_defn ( t0 ) ) ;
	    return ( a ) ;
	}
	case type_ptr_tag : {
	    return ( "ptr" ) ;
	}
	case type_list_tag : {
	    return ( "list" ) ;
	}
	case type_stack_tag : {
	    return ( "stack" ) ;
	}
	case type_vec_tag : {
	    return ( "vec" ) ;
	}
	case type_vec_ptr_tag : {
	    return ( "vec_ptr" ) ;
	}
	case type_undef_tag : {
	    char *a = DEREF_string ( type_undef_name ( t0 ) ) ;
	    return ( a ) ;
	}
    }
    last_id = id ;
    return ( DEREF_string ( cid_name_aux ( id ) ) ) ;
}


/*
    CHECK FOR COMPLEX TYPES

    This routine checks whether a type is complex in the sense that it
    requires the statement versions of COPY and DEREF rather than the
    expression versions.
*/

int is_complex_type
    PROTO_N ( ( t ) )
    PROTO_T ( TYPE_P t )
{
    TYPE t0 = DEREF_type ( t ) ;
    switch ( TAG_type ( t0 ) ) {
	case type_structure_tag :
	case type_vec_tag :
	case type_vec_ptr_tag : {
	    return ( 1 ) ;
	}
	case type_ident_tag : {
	    IDENTITY_P r = DEREF_ptr ( type_ident_id ( t0 ) ) ;
	    TYPE_P s = DEREF_ptr ( ident_defn ( r ) ) ;
	    return ( is_complex_type ( s ) ) ;
	}
    }
    return ( 0 ) ;
}
