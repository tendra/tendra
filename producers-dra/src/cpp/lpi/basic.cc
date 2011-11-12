/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include "implement.h"
#pragma implement interface "basic.h"


/*
    IMPLEMENTATION OF BASIC TYPES

    These declarations and macro definitions give the implementation of
    the basic type interface.
*/

typedef BOOLEAN bool_type ;
typedef PTR_MEMBER ptr_mem_type ;
typedef PTR_MEM_FUNC ptr_mem_func_type ;
typedef VTABLE_1 vtable_diag ;


/*
    IMPLEMENTATION OF RUN-TIME TYPE INFORMATION INTERFACE

    These declarations and macro definitions give the implementation of
    the run-time type information tokens.
*/

typedef TYPE_INFO typeid_type ;
typedef BASE_INFO baseid_type ;

#define typeid_make( X, Y, Z )\
	{ ( X ), ( Y ), ( Z ), &__TCPPLUS_ti_vtbl }

#define typeid_basic( X )\
	( __TCPPLUS_typeid + ( X ) )

#define baseid_make( X, Y, Z, A, B )\
	{ ( X ), offset ( Y ), ( Z ), ( A ), ( B ) }

#define dyn_cast( X, Y )\
	( __TCPPLUS_dynamic_cast ( ( X ), ( Y ) ) )


/*
    IMPLEMENTATION OF TERMINATION FUNCTION INTERFACE

    These declarations and macro definitions give the implementation of
    the termination function tokens.
*/

typedef DTOR_LIST destr_type ;

#define destr_init()\
	__TCPPLUS_init () ;

#define destr_global( X, Y, Z )\
	{\
	    ( X )->arg = ( Y ) ;\
	    ( X )->func = ( Z ) ;\
	    ( X )->next = __TCPPLUS_dtors ;\
	    __TCPPLUS_dtors = ( X ) ;\
	}

#define destr_local( X, Y, Z )\
	{\
	    ( X )->arg = ( Y ) ;\
	    ( X )->func = ( Z ) ;\
	    ( X )->next = __TCPPLUS_except.buf [0]->dtors ;\
	    __TCPPLUS_except.buf [0]->dtors = ( X ) ;\
	}

#define destr_end( X )\
	{\
	    __TCPPLUS_except.buf [0]->dtors = ( X )->next ;\
	}

#define destr_null		{ NULL, NULL, NULL }
#define destr_ptr( X )		( ( X )->arg )
#define destr_atexit( X )	__TCPPLUS_atexit ( ( X ) )
#define destr_main		{}
