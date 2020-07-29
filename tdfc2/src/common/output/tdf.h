/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef TDF_INCLUDED
#define TDF_INCLUDED


/*
    TDF CONSTRUCT ENCODING MACROS

    The main TDF construct encoding macros are automatically generated
    from the TDF specification.  There are two versions provided, which
    one is included depends on the value of TDF_VERSION.

    Note that the version of the TDF database used contains a couple of
    corrections from the standard version:

     - A construct make_token_def has been added to represent
       a token definition.
     - The sort diag_tag has been added to the edge constructors.

    The macros generated only handle the encoding of the construct - the
    construct parameters need to be encoded by hand (the C producer does
    something similar, but including the construct parameters).
    For example, make_tdf generates a macro:

      void ENC_plus ( BITSTREAM * ) ;

    which encodes the plus construct (91 as 7 bits in extended format).
    A typical use of this macro, for adding the expressions a and b would be:

      ENC_plus ( bs ) ;
      ENC_impossible ( bs ) ;
      bs = enc_exp ( bs, a ) ;
      bs = enc_exp ( bs, b ) ;

    Each function or variable is compiled to TDF as its definition is
    encountered. For some definitions, such as inline functions, the
    compilation may be deferred until it is clear whether or not the
    identifier has been used. There is a final pass over all identifiers
    during the variable analysis routines which incorporates this check.
    Because of the organisation of a TDF capsule it is necessary to store
    all of the compiled TDF in memory until the end of the program, when
    the complete capsule, including external tag and token names and linkage
    information, is written to the output file.

*/

#if (TDF_VERSION == 401)
#include <output/tdf1.h>
#else
#error Unknown TDF version number!
#endif


/*
    EXTRA ENCODING MACROS

    These macros give further useful encoding constructs.  Again A appears
    more than once in certain of these macros.
*/

#define ENC_LIST(A, B)		{ ENC_BITS(A, 1, 0); ENC_INT(A, B); }
#define ENC_SLIST(A, B)		ENC_INT(A, B)
#define ENC_LENGTH(A, B)	ENC_INT(A, B)

#define ENC_INT_SMALL(A, B)	ENC_BITS(A, 4,(B) + 8)
#define ENC_LIST_SMALL(A, B)	ENC_BITS(A, 5,(B) + 8)
#define ENC_SLIST_SMALL(A, B)	ENC_INT_SMALL(A, B)
#define ENC_LEN_SMALL(A, B)	ENC_INT_SMALL(A, B)

#define ENC_NTEST(A, B)		ENX_ntest(A,(B) + 3)
#define ENC_RMODE(A, B)		ENX_rounding_mode(A,(B) + 3)

#define ENC_SEQUENCE(A, B)	{ ENC_sequence(A); ENC_LIST(A, B); }
#define ENC_SEQ_SMALL(A, B)	{ ENC_sequence(A); ENC_LIST_SMALL(A, B); }

#ifndef LINK_dg_comp_props
#define LINK_dg_comp_props		"<error>"
#define TDF_DIAG4			0
#else
#define TDF_DIAG4			1
#endif

#ifndef LINK_dg_tag
#define LINK_dg_tag			"<error>"
#endif

#ifndef ENC_make_string
#define ENC_make_string(A)		/* empty */
#endif

#ifndef ENC_initial_value
#define ENC_initial_value(A)		/* empty */
#endif

#ifndef ENC_token_definition
#define ENC_token_definition(A)		ENC_BITS(A, 1, 1)
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
