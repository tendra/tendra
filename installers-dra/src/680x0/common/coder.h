/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CODER_INCLUDED
#define CODER_INCLUDED

#include "config.h"

#include "exptypes.h"
#include "localtypes.h"

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

#define  tst_le		L1
#define  tst_ls		L2
#define  tst_ge		L3
#define  tst_gr		L4
#define  tst_neq	L5
#define  tst_eq		L6
#define  tst_ngr	L7
#define  tst_nge	L8
#define  tst_nls	L9
#define  tst_nle	L10

#endif
