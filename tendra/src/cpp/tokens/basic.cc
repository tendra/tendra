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
