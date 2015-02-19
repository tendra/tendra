/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef DIAG_INCLUDED
#define DIAG_INCLUDED


/*
    TDF DIAGNOSTICS ENCODING ROUTINES

    The routines in this module are concerned with the encoding of TDF
    diagnostic information.
*/

extern void enc_diag_id(IDENTIFIER, int);
extern void enc_diag_init(const char *, ulong, TYPE);
extern void enc_diag_token(IDENTIFIER, TYPE);
extern BITSTREAM *enc_diag_name(BITSTREAM *, IDENTIFIER, int);
extern BITSTREAM *enc_diag_local(BITSTREAM *, IDENTIFIER, BITSTREAM *);
extern BITSTREAM *enc_diag_params(BITSTREAM *, LIST(IDENTIFIER), BITSTREAM *,
				  EXP);
extern BITSTREAM *enc_diag_start(BITSTREAM *);
extern BITSTREAM *enc_diag_begin(BITSTREAM **);
extern BITSTREAM *enc_diag_stmt(BITSTREAM *, EXP, int);
extern BITSTREAM *enc_diag_end(BITSTREAM *, BITSTREAM *, EXP, int);
extern BITSTREAM *enc_diag_block(BITSTREAM *, EXP);
extern BITSTREAM *enc_diag_ctype(BITSTREAM *, CLASS_TYPE);
extern BITSTREAM *enc_diag_type(BITSTREAM *, TYPE, int);
extern int enc_diag_pending(void);
extern int is_diag_stmt(EXP);


#endif
