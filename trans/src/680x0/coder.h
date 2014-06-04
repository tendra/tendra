/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CODER_INCLUDED
#define CODER_INCLUDED

#include <local/ash.h>

#include <reader/exptypes.h>

extern void coder(where, ash, exp);


/*
    LOCATION IDENTIFIERS

    These values are used by the register allocation routines to indicate
    where an expression is held.
*/

#define  reg_pl		0	/* In a register */
#define  par_pl		1	/* On the stack (procedure argument) */
#define  var_pl		2	/* On the stack (allocated variable) */
#define  nowhere_pl	3	/* Elsewhere */
#ifndef tdf3
#define  par2_pl        4       /* procedure argument accessed by use of A5 */
#define  par3_pl        5       /* procedure argument accessed by use of SP */
#endif
/*
    TEST NUMBERS

    These numbers give the tests recognised by branch, cmp etc.
*/

#define  tst_le		1L
#define  tst_ls		2L
#define  tst_ge		3L
#define  tst_gr		4L
#define  tst_neq	5L
#define  tst_eq		6L
#define  tst_ngr	7L
#define  tst_nge	8L
#define  tst_nls	9L
#define  tst_nle	10L

#endif
