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

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA disk (VERSION 1.1)
    BY calculus (VERSION 1.2)
*/

#ifndef WRITE_DEF_H_INCLUDED
#define WRITE_DEF_H_INCLUDED

#include "disk.h"
#include "type_ops.h"

/* Disk writing function declarations */

#ifndef WRITE_disk_list_ptr_type
#define WRITE_disk_list_ptr_type( A ) WRITE_list_ptr_type ( A )
#endif

#ifndef WRITE_list_ptr_type
static void WRITE_list_ptr_type PROTO_S ( ( LIST ( PTR ( TYPE ) ) ) ) ;
#endif

#ifndef WRITE_disk_string
#define WRITE_disk_string( A ) WRITE_string ( A )
#endif

#ifndef WRITE_disk_int
#define WRITE_disk_int( A ) WRITE_int ( A )
#endif

#ifndef WRITE_type
static void WRITE_type PROTO_S ( ( TYPE ) ) ;
#endif

#ifndef WRITE_zero_int
#define WRITE_zero_int( A ) WRITE_int ( A )
#endif

#ifndef WRITE_PRIMITIVE_P
#define WRITE_PRIMITIVE_P( A ) WRITE_ptr_prim ( A )
#endif

#ifndef WRITE_ptr_prim
static void WRITE_ptr_prim PROTO_S ( ( PTR ( PRIMITIVE ) ) ) ;
#endif

#ifndef WRITE_prim
static void WRITE_prim PROTO_S ( ( PRIMITIVE ) ) ;
#endif

#ifndef WRITE_CLASS_ID_P
#define WRITE_CLASS_ID_P( A ) WRITE_ptr_cid ( A )
#endif

#ifndef WRITE_ptr_cid
static void WRITE_ptr_cid PROTO_S ( ( PTR ( CLASS_ID ) ) ) ;
#endif

#ifndef WRITE_cid
static void WRITE_cid PROTO_S ( ( CLASS_ID ) ) ;
#endif

#ifndef WRITE_name_string
#define WRITE_name_string( A ) WRITE_string ( A )
#endif

#ifndef WRITE_IDENTITY_P
#define WRITE_IDENTITY_P( A ) WRITE_ptr_ident ( A )
#endif

#ifndef WRITE_ptr_ident
static void WRITE_ptr_ident PROTO_S ( ( PTR ( IDENTITY ) ) ) ;
#endif

#ifndef WRITE_ident
static void WRITE_ident PROTO_S ( ( IDENTITY ) ) ;
#endif

#ifndef WRITE_TYPE_P
#define WRITE_TYPE_P( A ) WRITE_ptr_type ( A )
#endif

#ifndef WRITE_ptr_type
static void WRITE_ptr_type PROTO_S ( ( PTR ( TYPE ) ) ) ;
#endif

#ifndef WRITE_ENUM_P
#define WRITE_ENUM_P( A ) WRITE_ptr_en ( A )
#endif

#ifndef WRITE_ptr_en
static void WRITE_ptr_en PROTO_S ( ( PTR ( ENUM ) ) ) ;
#endif

#ifndef WRITE_en
static void WRITE_en PROTO_S ( ( ENUM ) ) ;
#endif

#ifndef WRITE_list_ptr_ec
static void WRITE_list_ptr_ec PROTO_S ( ( LIST ( PTR ( ECONST ) ) ) ) ;
#endif

#ifndef WRITE_list_ECONST_P
#define WRITE_list_ECONST_P( A ) WRITE_list_ptr_ec ( A )
#endif

#ifndef WRITE_ECONST_P
#define WRITE_ECONST_P( A ) WRITE_ptr_ec ( A )
#endif

#ifndef WRITE_ptr_ec
static void WRITE_ptr_ec PROTO_S ( ( PTR ( ECONST ) ) ) ;
#endif

#ifndef WRITE_ec
static void WRITE_ec PROTO_S ( ( ECONST ) ) ;
#endif

#ifndef WRITE_STRUCTURE_P
#define WRITE_STRUCTURE_P( A ) WRITE_ptr_str ( A )
#endif

#ifndef WRITE_ptr_str
static void WRITE_ptr_str PROTO_S ( ( PTR ( STRUCTURE ) ) ) ;
#endif

#ifndef WRITE_str
static void WRITE_str PROTO_S ( ( STRUCTURE ) ) ;
#endif

#ifndef WRITE_list_ptr_cmp
static void WRITE_list_ptr_cmp PROTO_S ( ( LIST ( PTR ( COMPONENT ) ) ) ) ;
#endif

#ifndef WRITE_list_COMPONENT_P
#define WRITE_list_COMPONENT_P( A ) WRITE_list_ptr_cmp ( A )
#endif

#ifndef WRITE_COMPONENT_P
#define WRITE_COMPONENT_P( A ) WRITE_ptr_cmp ( A )
#endif

#ifndef WRITE_ptr_cmp
static void WRITE_ptr_cmp PROTO_S ( ( PTR ( COMPONENT ) ) ) ;
#endif

#ifndef WRITE_cmp
static void WRITE_cmp PROTO_S ( ( COMPONENT ) ) ;
#endif

#ifndef WRITE_UNION_P
#define WRITE_UNION_P( A ) WRITE_ptr_un ( A )
#endif

#ifndef WRITE_ptr_un
static void WRITE_ptr_un PROTO_S ( ( PTR ( UNION ) ) ) ;
#endif

#ifndef WRITE_un
static void WRITE_un PROTO_S ( ( UNION ) ) ;
#endif

#ifndef WRITE_list_ptr_fld
static void WRITE_list_ptr_fld PROTO_S ( ( LIST ( PTR ( FIELD ) ) ) ) ;
#endif

#ifndef WRITE_list_FIELD_P
#define WRITE_list_FIELD_P( A ) WRITE_list_ptr_fld ( A )
#endif

#ifndef WRITE_FIELD_P
#define WRITE_FIELD_P( A ) WRITE_ptr_fld ( A )
#endif

#ifndef WRITE_ptr_fld
static void WRITE_ptr_fld PROTO_S ( ( PTR ( FIELD ) ) ) ;
#endif

#ifndef WRITE_fld
static void WRITE_fld PROTO_S ( ( FIELD ) ) ;
#endif

#ifndef WRITE_list_ptr_map
static void WRITE_list_ptr_map PROTO_S ( ( LIST ( PTR ( MAP ) ) ) ) ;
#endif

#ifndef WRITE_list_MAP_P
#define WRITE_list_MAP_P( A ) WRITE_list_ptr_map ( A )
#endif

#ifndef WRITE_MAP_P
#define WRITE_MAP_P( A ) WRITE_ptr_map ( A )
#endif

#ifndef WRITE_ptr_map
static void WRITE_ptr_map PROTO_S ( ( PTR ( MAP ) ) ) ;
#endif

#ifndef WRITE_map
static void WRITE_map PROTO_S ( ( MAP ) ) ;
#endif

#ifndef WRITE_list_ptr_arg
static void WRITE_list_ptr_arg PROTO_S ( ( LIST ( PTR ( ARGUMENT ) ) ) ) ;
#endif

#ifndef WRITE_list_ARGUMENT_P
#define WRITE_list_ARGUMENT_P( A ) WRITE_list_ptr_arg ( A )
#endif

#ifndef WRITE_ARGUMENT_P
#define WRITE_ARGUMENT_P( A ) WRITE_ptr_arg ( A )
#endif

#ifndef WRITE_ptr_arg
static void WRITE_ptr_arg PROTO_S ( ( PTR ( ARGUMENT ) ) ) ;
#endif

#ifndef WRITE_arg
static void WRITE_arg PROTO_S ( ( ARGUMENT ) ) ;
#endif


/* Disk writing routine for LIST ( PTR ( TYPE ) ) */

#ifndef WRITE_list_ptr_type

static void WRITE_list_ptr_type
    PROTO_N ( ( x_ ) )
    PROTO_T ( LIST ( PTR ( TYPE ) ) x_ )
{
    while ( !IS_NULL_list ( x_ ) ) {
	PTR ( TYPE ) y_ ;
	y_ = DEREF_ptr ( HEAD_list ( x_ ) ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_ptr_type ( y_ ) ;
	x_ = TAIL_list ( x_ ) ;
    }
    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    return ;
}

#endif


/* Disk writing routine for TYPE */

#ifndef WRITE_type

static void WRITE_type
    PROTO_N ( ( x_ ) )
    PROTO_T ( TYPE x_ )
{
    if ( IS_NULL_type ( x_ ) ) {
	WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    } else {
	zero_int size ;
	unsigned tag_ = TAG_type ( x_ ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_BITS ( 4, tag_ ) ;
	switch ( tag_ ) {
	    case type_primitive_tag : {
		PRIMITIVE_P prim ;
		unsigned alias_ = GET_ALIAS_type_primitive ( x_ ) ;
		if ( alias_ ) {
		    WRITE_ALIAS ( alias_ ) ;
		    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
		    break ;
		}
		alias_ = ++crt_disk_alias ;
		SET_ALIAS_type_primitive ( x_, alias_ ) ;
		WRITE_ALIAS ( alias_ ) ;
		WRITE_BITS ( 1, ( unsigned ) 1 ) ;
		DECONS_type_primitive ( size, prim,  x_ ) ;
		WRITE_zero_int ( size ) ;
		WRITE_PRIMITIVE_P ( prim ) ;
		break ;
	    }
	    case type_ident_tag : {
		IDENTITY_P id ;
		unsigned alias_ = GET_ALIAS_type_ident ( x_ ) ;
		if ( alias_ ) {
		    WRITE_ALIAS ( alias_ ) ;
		    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
		    break ;
		}
		alias_ = ++crt_disk_alias ;
		SET_ALIAS_type_ident ( x_, alias_ ) ;
		WRITE_ALIAS ( alias_ ) ;
		WRITE_BITS ( 1, ( unsigned ) 1 ) ;
		DECONS_type_ident ( size, id,  x_ ) ;
		WRITE_zero_int ( size ) ;
		WRITE_IDENTITY_P ( id ) ;
		break ;
	    }
	    case type_enumeration_tag : {
		ENUM_P en ;
		unsigned alias_ = GET_ALIAS_type_enumeration ( x_ ) ;
		if ( alias_ ) {
		    WRITE_ALIAS ( alias_ ) ;
		    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
		    break ;
		}
		alias_ = ++crt_disk_alias ;
		SET_ALIAS_type_enumeration ( x_, alias_ ) ;
		WRITE_ALIAS ( alias_ ) ;
		WRITE_BITS ( 1, ( unsigned ) 1 ) ;
		DECONS_type_enumeration ( size, en,  x_ ) ;
		WRITE_zero_int ( size ) ;
		WRITE_ENUM_P ( en ) ;
		break ;
	    }
	    case type_structure_tag : {
		STRUCTURE_P struc ;
		unsigned alias_ = GET_ALIAS_type_structure ( x_ ) ;
		if ( alias_ ) {
		    WRITE_ALIAS ( alias_ ) ;
		    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
		    break ;
		}
		alias_ = ++crt_disk_alias ;
		SET_ALIAS_type_structure ( x_, alias_ ) ;
		WRITE_ALIAS ( alias_ ) ;
		WRITE_BITS ( 1, ( unsigned ) 1 ) ;
		DECONS_type_structure ( size, struc,  x_ ) ;
		WRITE_zero_int ( size ) ;
		WRITE_STRUCTURE_P ( struc ) ;
		break ;
	    }
	    case type_onion_tag : {
		UNION_P un ;
		unsigned alias_ = GET_ALIAS_type_onion ( x_ ) ;
		if ( alias_ ) {
		    WRITE_ALIAS ( alias_ ) ;
		    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
		    break ;
		}
		alias_ = ++crt_disk_alias ;
		SET_ALIAS_type_onion ( x_, alias_ ) ;
		WRITE_ALIAS ( alias_ ) ;
		WRITE_BITS ( 1, ( unsigned ) 1 ) ;
		DECONS_type_onion ( size, un,  x_ ) ;
		WRITE_zero_int ( size ) ;
		WRITE_UNION_P ( un ) ;
		break ;
	    }
	    case type_ptr_tag : {
		TYPE_P sub ;
		unsigned alias_ = GET_ALIAS_type_ptr ( x_ ) ;
		if ( alias_ ) {
		    WRITE_ALIAS ( alias_ ) ;
		    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
		    break ;
		}
		alias_ = ++crt_disk_alias ;
		SET_ALIAS_type_ptr ( x_, alias_ ) ;
		WRITE_ALIAS ( alias_ ) ;
		WRITE_BITS ( 1, ( unsigned ) 1 ) ;
		DECONS_type_ptr ( size, sub,  x_ ) ;
		WRITE_zero_int ( size ) ;
		WRITE_TYPE_P ( sub ) ;
		break ;
	    }
	    case type_list_tag : {
		TYPE_P sub ;
		unsigned alias_ = GET_ALIAS_type_list ( x_ ) ;
		if ( alias_ ) {
		    WRITE_ALIAS ( alias_ ) ;
		    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
		    break ;
		}
		alias_ = ++crt_disk_alias ;
		SET_ALIAS_type_list ( x_, alias_ ) ;
		WRITE_ALIAS ( alias_ ) ;
		WRITE_BITS ( 1, ( unsigned ) 1 ) ;
		DECONS_type_list ( size, sub,  x_ ) ;
		WRITE_zero_int ( size ) ;
		WRITE_TYPE_P ( sub ) ;
		break ;
	    }
	    case type_stack_tag : {
		TYPE_P sub ;
		unsigned alias_ = GET_ALIAS_type_stack ( x_ ) ;
		if ( alias_ ) {
		    WRITE_ALIAS ( alias_ ) ;
		    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
		    break ;
		}
		alias_ = ++crt_disk_alias ;
		SET_ALIAS_type_stack ( x_, alias_ ) ;
		WRITE_ALIAS ( alias_ ) ;
		WRITE_BITS ( 1, ( unsigned ) 1 ) ;
		DECONS_type_stack ( size, sub,  x_ ) ;
		WRITE_zero_int ( size ) ;
		WRITE_TYPE_P ( sub ) ;
		break ;
	    }
	    case type_vec_tag : {
		TYPE_P sub ;
		unsigned alias_ = GET_ALIAS_type_vec ( x_ ) ;
		if ( alias_ ) {
		    WRITE_ALIAS ( alias_ ) ;
		    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
		    break ;
		}
		alias_ = ++crt_disk_alias ;
		SET_ALIAS_type_vec ( x_, alias_ ) ;
		WRITE_ALIAS ( alias_ ) ;
		WRITE_BITS ( 1, ( unsigned ) 1 ) ;
		DECONS_type_vec ( size, sub,  x_ ) ;
		WRITE_zero_int ( size ) ;
		WRITE_TYPE_P ( sub ) ;
		break ;
	    }
	    case type_vec_ptr_tag : {
		TYPE_P sub ;
		unsigned alias_ = GET_ALIAS_type_vec_ptr ( x_ ) ;
		if ( alias_ ) {
		    WRITE_ALIAS ( alias_ ) ;
		    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
		    break ;
		}
		alias_ = ++crt_disk_alias ;
		SET_ALIAS_type_vec_ptr ( x_, alias_ ) ;
		WRITE_ALIAS ( alias_ ) ;
		WRITE_BITS ( 1, ( unsigned ) 1 ) ;
		DECONS_type_vec_ptr ( size, sub,  x_ ) ;
		WRITE_zero_int ( size ) ;
		WRITE_TYPE_P ( sub ) ;
		break ;
	    }
	    case type_quote_tag : {
		string defn ;
		DECONS_type_quote ( size, defn,  x_ ) ;
		WRITE_zero_int ( size ) ;
		WRITE_string ( defn ) ;
		break ;
	    }
	    case type_undef_tag : {
		string name ;
		DECONS_type_undef ( size, name,  x_ ) ;
		WRITE_zero_int ( size ) ;
		WRITE_string ( name ) ;
		break ;
	    }
	}
    }
    return ;
}

#endif


/* Disk writing routine for PTR ( PRIMITIVE ) */

#ifndef WRITE_ptr_prim

static void WRITE_ptr_prim
    PROTO_N ( ( x_ ) )
    PROTO_T ( PTR ( PRIMITIVE ) x_ )
{
    if ( IS_NULL_ptr ( x_ ) ) {
	WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    } else {
	PRIMITIVE y_ ;
	DEREF_prim ( x_, y_ ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_prim ( y_ ) ;
    }
    return ;
}

#endif


/* Disk writing routine for PRIMITIVE */

#ifndef WRITE_prim

static void WRITE_prim
    PROTO_N ( ( x_ ) )
    PROTO_T ( PRIMITIVE x_ )
{
    WRITE_CLASS_ID_P ( x_.id ) ;
    WRITE_string ( x_.defn ) ;
    return ;
}

#endif


/* Disk writing routine for PTR ( CLASS_ID ) */

#ifndef WRITE_ptr_cid

static void WRITE_ptr_cid
    PROTO_N ( ( x_ ) )
    PROTO_T ( PTR ( CLASS_ID ) x_ )
{
    if ( IS_NULL_ptr ( x_ ) ) {
	WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    } else {
	CLASS_ID y_ ;
	DEREF_cid ( x_, y_ ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_cid ( y_ ) ;
    }
    return ;
}

#endif


/* Disk writing routine for CLASS_ID */

#ifndef WRITE_cid

static void WRITE_cid
    PROTO_N ( ( x_ ) )
    PROTO_T ( CLASS_ID x_ )
{
    WRITE_string ( x_.name ) ;
    WRITE_string ( x_.name_aux ) ;
    WRITE_int ( x_.flag ) ;
    WRITE_name_string ( x_.file ) ;
    WRITE_int ( x_.line ) ;
    return ;
}

#endif


/* Disk writing routine for PTR ( IDENTITY ) */

#ifndef WRITE_ptr_ident

static void WRITE_ptr_ident
    PROTO_N ( ( x_ ) )
    PROTO_T ( PTR ( IDENTITY ) x_ )
{
    if ( IS_NULL_ptr ( x_ ) ) {
	WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    } else {
	IDENTITY y_ ;
	DEREF_ident ( x_, y_ ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_ident ( y_ ) ;
    }
    return ;
}

#endif


/* Disk writing routine for IDENTITY */

#ifndef WRITE_ident

static void WRITE_ident
    PROTO_N ( ( x_ ) )
    PROTO_T ( IDENTITY x_ )
{
    WRITE_CLASS_ID_P ( x_.id ) ;
    WRITE_TYPE_P ( x_.defn ) ;
    return ;
}

#endif


/* Disk writing routine for PTR ( TYPE ) */

#ifndef WRITE_ptr_type

static void WRITE_ptr_type
    PROTO_N ( ( x_ ) )
    PROTO_T ( PTR ( TYPE ) x_ )
{
    if ( IS_NULL_ptr ( x_ ) ) {
	WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    } else {
	TYPE y_ ;
	y_ = DEREF_type ( x_ ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_type ( y_ ) ;
    }
    return ;
}

#endif


/* Disk writing routine for PTR ( ENUM ) */

#ifndef WRITE_ptr_en

static void WRITE_ptr_en
    PROTO_N ( ( x_ ) )
    PROTO_T ( PTR ( ENUM ) x_ )
{
    if ( IS_NULL_ptr ( x_ ) ) {
	WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    } else {
	ENUM y_ ;
	DEREF_en ( x_, y_ ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_en ( y_ ) ;
    }
    return ;
}

#endif


/* Disk writing routine for ENUM */

#ifndef WRITE_en

static void WRITE_en
    PROTO_N ( ( x_ ) )
    PROTO_T ( ENUM x_ )
{
    WRITE_CLASS_ID_P ( x_.id ) ;
    WRITE_list_ECONST_P ( x_.consts ) ;
    WRITE_number ( x_.order ) ;
    WRITE_int ( x_.lists ) ;
    return ;
}

#endif


/* Disk writing routine for LIST ( PTR ( ECONST ) ) */

#ifndef WRITE_list_ptr_ec

static void WRITE_list_ptr_ec
    PROTO_N ( ( x_ ) )
    PROTO_T ( LIST ( PTR ( ECONST ) ) x_ )
{
    while ( !IS_NULL_list ( x_ ) ) {
	PTR ( ECONST ) y_ ;
	y_ = DEREF_ptr ( HEAD_list ( x_ ) ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_ptr_ec ( y_ ) ;
	x_ = TAIL_list ( x_ ) ;
    }
    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    return ;
}

#endif


/* Disk writing routine for PTR ( ECONST ) */

#ifndef WRITE_ptr_ec

static void WRITE_ptr_ec
    PROTO_N ( ( x_ ) )
    PROTO_T ( PTR ( ECONST ) x_ )
{
    if ( IS_NULL_ptr ( x_ ) ) {
	WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    } else {
	ECONST y_ ;
	DEREF_ec ( x_, y_ ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_ec ( y_ ) ;
    }
    return ;
}

#endif


/* Disk writing routine for ECONST */

#ifndef WRITE_ec

static void WRITE_ec
    PROTO_N ( ( x_ ) )
    PROTO_T ( ECONST x_ )
{
    WRITE_string ( x_.name ) ;
    WRITE_number ( x_.value ) ;
    return ;
}

#endif


/* Disk writing routine for PTR ( STRUCTURE ) */

#ifndef WRITE_ptr_str

static void WRITE_ptr_str
    PROTO_N ( ( x_ ) )
    PROTO_T ( PTR ( STRUCTURE ) x_ )
{
    if ( IS_NULL_ptr ( x_ ) ) {
	WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    } else {
	STRUCTURE y_ ;
	DEREF_str ( x_, y_ ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_str ( y_ ) ;
    }
    return ;
}

#endif


/* Disk writing routine for STRUCTURE */

#ifndef WRITE_str

static void WRITE_str
    PROTO_N ( ( x_ ) )
    PROTO_T ( STRUCTURE x_ )
{
    WRITE_CLASS_ID_P ( x_.id ) ;
    WRITE_STRUCTURE_P ( x_.base ) ;
    WRITE_list_COMPONENT_P ( x_.defn ) ;
    WRITE_zero_int ( x_.output ) ;
    return ;
}

#endif


/* Disk writing routine for LIST ( PTR ( COMPONENT ) ) */

#ifndef WRITE_list_ptr_cmp

static void WRITE_list_ptr_cmp
    PROTO_N ( ( x_ ) )
    PROTO_T ( LIST ( PTR ( COMPONENT ) ) x_ )
{
    while ( !IS_NULL_list ( x_ ) ) {
	PTR ( COMPONENT ) y_ ;
	y_ = DEREF_ptr ( HEAD_list ( x_ ) ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_ptr_cmp ( y_ ) ;
	x_ = TAIL_list ( x_ ) ;
    }
    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    return ;
}

#endif


/* Disk writing routine for PTR ( COMPONENT ) */

#ifndef WRITE_ptr_cmp

static void WRITE_ptr_cmp
    PROTO_N ( ( x_ ) )
    PROTO_T ( PTR ( COMPONENT ) x_ )
{
    if ( IS_NULL_ptr ( x_ ) ) {
	WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    } else {
	COMPONENT y_ ;
	DEREF_cmp ( x_, y_ ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_cmp ( y_ ) ;
    }
    return ;
}

#endif


/* Disk writing routine for COMPONENT */

#ifndef WRITE_cmp

static void WRITE_cmp
    PROTO_N ( ( x_ ) )
    PROTO_T ( COMPONENT x_ )
{
    WRITE_string ( x_.name ) ;
    WRITE_TYPE_P ( x_.type ) ;
    WRITE_string ( x_.value ) ;
    return ;
}

#endif


/* Disk writing routine for PTR ( UNION ) */

#ifndef WRITE_ptr_un

static void WRITE_ptr_un
    PROTO_N ( ( x_ ) )
    PROTO_T ( PTR ( UNION ) x_ )
{
    if ( IS_NULL_ptr ( x_ ) ) {
	WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    } else {
	UNION y_ ;
	DEREF_un ( x_, y_ ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_un ( y_ ) ;
    }
    return ;
}

#endif


/* Disk writing routine for UNION */

#ifndef WRITE_un

static void WRITE_un
    PROTO_N ( ( x_ ) )
    PROTO_T ( UNION x_ )
{
    WRITE_CLASS_ID_P ( x_.id ) ;
    WRITE_UNION_P ( x_.base ) ;
    WRITE_list_COMPONENT_P ( x_.s_defn ) ;
    WRITE_list_FIELD_P ( x_.u_defn ) ;
    WRITE_list_MAP_P ( x_.map ) ;
    WRITE_int ( x_.no_fields ) ;
    return ;
}

#endif


/* Disk writing routine for LIST ( PTR ( FIELD ) ) */

#ifndef WRITE_list_ptr_fld

static void WRITE_list_ptr_fld
    PROTO_N ( ( x_ ) )
    PROTO_T ( LIST ( PTR ( FIELD ) ) x_ )
{
    while ( !IS_NULL_list ( x_ ) ) {
	PTR ( FIELD ) y_ ;
	y_ = DEREF_ptr ( HEAD_list ( x_ ) ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_ptr_fld ( y_ ) ;
	x_ = TAIL_list ( x_ ) ;
    }
    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    return ;
}

#endif


/* Disk writing routine for PTR ( FIELD ) */

#ifndef WRITE_ptr_fld

static void WRITE_ptr_fld
    PROTO_N ( ( x_ ) )
    PROTO_T ( PTR ( FIELD ) x_ )
{
    if ( IS_NULL_ptr ( x_ ) ) {
	WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    } else {
	FIELD y_ ;
	DEREF_fld ( x_, y_ ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_fld ( y_ ) ;
    }
    return ;
}

#endif


/* Disk writing routine for FIELD */

#ifndef WRITE_fld

static void WRITE_fld
    PROTO_N ( ( x_ ) )
    PROTO_T ( FIELD x_ )
{
    WRITE_string ( x_.name ) ;
    WRITE_int ( x_.tag ) ;
    WRITE_int ( x_.flag ) ;
    WRITE_int ( x_.set ) ;
    WRITE_FIELD_P ( x_.base ) ;
    WRITE_list_COMPONENT_P ( x_.defn ) ;
    return ;
}

#endif


/* Disk writing routine for LIST ( PTR ( MAP ) ) */

#ifndef WRITE_list_ptr_map

static void WRITE_list_ptr_map
    PROTO_N ( ( x_ ) )
    PROTO_T ( LIST ( PTR ( MAP ) ) x_ )
{
    while ( !IS_NULL_list ( x_ ) ) {
	PTR ( MAP ) y_ ;
	y_ = DEREF_ptr ( HEAD_list ( x_ ) ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_ptr_map ( y_ ) ;
	x_ = TAIL_list ( x_ ) ;
    }
    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    return ;
}

#endif


/* Disk writing routine for PTR ( MAP ) */

#ifndef WRITE_ptr_map

static void WRITE_ptr_map
    PROTO_N ( ( x_ ) )
    PROTO_T ( PTR ( MAP ) x_ )
{
    if ( IS_NULL_ptr ( x_ ) ) {
	WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    } else {
	MAP y_ ;
	DEREF_map ( x_, y_ ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_map ( y_ ) ;
    }
    return ;
}

#endif


/* Disk writing routine for MAP */

#ifndef WRITE_map

static void WRITE_map
    PROTO_N ( ( x_ ) )
    PROTO_T ( MAP x_ )
{
    WRITE_string ( x_.name ) ;
    WRITE_int ( x_.flag ) ;
    WRITE_TYPE_P ( x_.ret_type ) ;
    WRITE_list_ARGUMENT_P ( x_.args ) ;
    return ;
}

#endif


/* Disk writing routine for LIST ( PTR ( ARGUMENT ) ) */

#ifndef WRITE_list_ptr_arg

static void WRITE_list_ptr_arg
    PROTO_N ( ( x_ ) )
    PROTO_T ( LIST ( PTR ( ARGUMENT ) ) x_ )
{
    while ( !IS_NULL_list ( x_ ) ) {
	PTR ( ARGUMENT ) y_ ;
	y_ = DEREF_ptr ( HEAD_list ( x_ ) ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_ptr_arg ( y_ ) ;
	x_ = TAIL_list ( x_ ) ;
    }
    WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    return ;
}

#endif


/* Disk writing routine for PTR ( ARGUMENT ) */

#ifndef WRITE_ptr_arg

static void WRITE_ptr_arg
    PROTO_N ( ( x_ ) )
    PROTO_T ( PTR ( ARGUMENT ) x_ )
{
    if ( IS_NULL_ptr ( x_ ) ) {
	WRITE_BITS ( 1, ( unsigned ) 0 ) ;
    } else {
	ARGUMENT y_ ;
	DEREF_arg ( x_, y_ ) ;
	WRITE_BITS ( 1, ( unsigned ) 1 ) ;
	WRITE_arg ( y_ ) ;
    }
    return ;
}

#endif


/* Disk writing routine for ARGUMENT */

#ifndef WRITE_arg

static void WRITE_arg
    PROTO_N ( ( x_ ) )
    PROTO_T ( ARGUMENT x_ )
{
    WRITE_string ( x_.name ) ;
    WRITE_TYPE_P ( x_.type ) ;
    return ;
}

#endif


#endif
