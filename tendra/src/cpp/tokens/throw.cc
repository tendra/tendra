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


#pragma implement interface "longjump.h"
#include "implement.h"
#pragma implement interface "throw.h"
#include <exception>
using namespace std ;


/*
    IMPLEMENTATION OF EXCEPTION HANDLING INTERFACE

    These declarations and macro definitions give the implementation of
    the exception handling tokens declared in throw.h.
*/

#define throw_exception( X, Y, Z )\
	( __TCPPLUS_throw ( ( X ), ( Y ), ( Z ) ) )

#define rethrow_exception()	( __TCPPLUS_throw ( NULL, NULL, NULL ) )
#define catch_exception( X )	( __TCPPLUS_catch ( ( X ) ) )
#define alloc_exception( X )	( __TCPPLUS_alloc_except ( ( X ) ) )
#define value_exception		( __TCPPLUS_except.value [1] )
#define caught_exception()	( __TCPPLUS_except.unwinding = false )
#define end_exception()		( __TCPPLUS_handled () )
#define ill_exception( X )	( __TCPPLUS_unexpected ( ( X ) ) )

typedef EXCEPTION exception_type ;

#define try_begin( X, Y, Z )\
	{\
	    ( X )->frame = ( Y ) ;\
	    ( X )->label = ( Z ) ;\
	    ( X )->dtors = NULL ;\
	    ( X )->next = __TCPPLUS_except.buf [0] ;\
	    __TCPPLUS_except.buf [0] = ( X ) ;\
	}

#define try_end( X )\
	{\
	    __TCPPLUS_except.buf [0] = ( X )->next ;\
	}
