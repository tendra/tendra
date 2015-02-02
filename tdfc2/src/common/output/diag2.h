/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef DIAG2_INCLUDED
#define DIAG2_INCLUDED


/*
    TDF DIAGNOSTICS (TDF 4.1 FORMAT) ENCODING ROUTINES

    The routines in this module are concerned with the encoding of TDF
    new format diagnostic information.
*/

#if (TDF_OUTPUT && TDF_DIAG4)
extern void enc_dg_id(IDENTIFIER, int);
extern void enc_dg_token(IDENTIFIER, TYPE);
extern BITSTREAM *enc_dg_local(BITSTREAM *, IDENTIFIER, BITSTREAM *);
extern BITSTREAM *enc_dg_params(BITSTREAM *, LIST(IDENTIFIER), BITSTREAM *,
				EXP);
extern BITSTREAM *enc_dg_name(BITSTREAM *, IDENTIFIER, TYPE);
extern BITSTREAM *enc_dg_type(BITSTREAM *, TYPE, int);
extern BITSTREAM *enc_dg_compilation(BITSTREAM *);
extern BITSTREAM *enc_dg_stmt(BITSTREAM *, EXP, int);
extern ulong enc_dg_basetype(TYPE, int);
extern int enc_dg_pending(void);
#endif


#endif
