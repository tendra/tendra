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


#ifndef TDF_INCLUDED
#define TDF_INCLUDED


/*
    TDF CONSTRUCT ENCODING MACROS

    The main TDF construct encoding macros are automatically generated
    from the TDF specification.  There are two versions provided, which
    one is included depends on the value of TDF_VERSION.
*/

#if TDF_OUTPUT
#if ( TDF_VERSION == 401 )
#include "tdf1.h"
#else
FAIL_COMPILER Unknown TDF version number!
#endif
#else
#define TDF_major		( TDF_VERSION / 100 )
#define TDF_minor		( TDF_VERSION % 100 )
#endif


/*
    EXTRA ENCODING MACROS

    These macros give further useful encoding constructs.  Again A appears
    more than once in certain of these macros.
*/

#define ENC_LIST( A, B )	{ ENC_BITS ( A, 1, 0 ) ; ENC_INT ( A, B ) ; }
#define ENC_SLIST( A, B )	ENC_INT ( A, B )
#define ENC_LENGTH( A, B )	ENC_INT ( A, B )

#define ENC_INT_SMALL( A, B )	ENC_BITS ( A, 4, ( B ) + 8 )
#define ENC_LIST_SMALL( A, B )	ENC_BITS ( A, 5, ( B ) + 8 )
#define ENC_SLIST_SMALL( A, B )	ENC_INT_SMALL ( A, B )
#define ENC_LEN_SMALL( A, B )	ENC_INT_SMALL ( A, B )

#define ENC_NTEST( A, B )	ENX_ntest ( A, ( B ) + 3 )
#define ENC_RMODE( A, B )	ENX_rounding_mode ( A, ( B ) + 3 )

#define ENC_SEQUENCE( A, B )	{ ENC_sequence ( A ) ; ENC_LIST ( A, B ) ; }
#define ENC_SEQ_SMALL( A, B )	{ ENC_sequence ( A ) ; ENC_LIST_SMALL ( A, B ) ; }

#ifndef LINK_dg_comp_props
#define LINK_dg_comp_props		"<error>"
#define TDF_NEW_DIAG			0
#else
#define TDF_NEW_DIAG			1
#endif

#ifndef LINK_dg_tag
#define LINK_dg_tag			"<error>"
#endif

#ifndef ENC_make_string
#define ENC_make_string( A )		/* empty */
#endif

#ifndef ENC_initial_value
#define ENC_initial_value( A )		/* empty */
#endif

#ifndef ENC_token_definition
#define ENC_token_definition( A )	ENC_BITS ( A, 1, 1 )
#endif


/*
    ENCODING PARAMETERS

    This macros give various values which are used to parameterise the
    encoding.
*/

#define ARRAY_PADDING		1
#define STRING_PADDING		7
#define SMALL_COMPOUND_INIT	4
#define SMALL_FLOAT_CONST	128
#define SMALL_ARRAY_BOUND	10000


#endif
