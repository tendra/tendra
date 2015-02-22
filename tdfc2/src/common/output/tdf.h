/* $Id$ */

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
