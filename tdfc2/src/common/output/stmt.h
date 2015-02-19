/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef STMT_INCLUDED
#define STMT_INCLUDED


/*
    TDF STATEMENT ENCODING ROUTINES

    The routines in this module are concerned with the encoding of
    statements as TDF expressions.
*/

extern BITSTREAM *enc_stmt(BITSTREAM *, EXP);
extern BITSTREAM *enc_compound_stmt(BITSTREAM *, EXP);
extern BITSTREAM *enc_stmt_exp(BITSTREAM *, EXP, TYPE, int);
extern unsigned stmt_length(EXP);
extern PTR(LOCATION)crt_enc_loc;

extern unsigned long no_destructors;


#endif
