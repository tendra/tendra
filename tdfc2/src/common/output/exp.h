/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef EXP_INCLUDED
#define EXP_INCLUDED


/*
    TDF EXP ENCODING ROUTINES

    The routines in this module are concerned with the encoding of TDF
    EXPs and related sorts.
*/

#if TDF_OUTPUT
extern BITSTREAM *enc_exp(BITSTREAM *, EXP);
extern BITSTREAM *enc_addr_exp(BITSTREAM *, TYPE, EXP);
extern BITSTREAM *enc_cont_exp(BITSTREAM *, TYPE, EXP);
extern BITSTREAM *enc_null_exp(BITSTREAM *, TYPE);
extern BITSTREAM *enc_make_int(BITSTREAM *, TYPE, int);
extern BITSTREAM *enc_make_snat(BITSTREAM *, int);
extern BITSTREAM *enc_condition(BITSTREAM *, EXP, ulong, ulong);
extern BITSTREAM *enc_assign_op(BITSTREAM *, TYPE, int *);
extern BITSTREAM *enc_cont_op(BITSTREAM *, TYPE, int *);
extern BITSTREAM *enc_ntest(BITSTREAM *, NTEST);
extern BITSTREAM *enc_exp_list(BITSTREAM *, LIST(EXP));
extern BITSTREAM *enc_dummy_exp(BITSTREAM *, TYPE, ulong, OFFSET, int, int);
extern BITSTREAM *enc_compare(BITSTREAM *, EXP, EXP, NTEST, ulong, ulong);
extern BITSTREAM *enc_error_treatment(BITSTREAM *, TYPE);
extern EXP simplify_cond(EXP, int *);
#endif


#endif
