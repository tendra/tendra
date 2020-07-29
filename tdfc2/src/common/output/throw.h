/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef THROW_INCLUDED
#define THROW_INCLUDED


/*
    TDF EXCEPTION HANDLING ENCODING ROUTINES

    The routines in this module are concerned with the encoding of
    exception handling as TDF expressions.
*/

extern BITSTREAM *enc_try(BITSTREAM *, EXP);
extern BITSTREAM *enc_throw(BITSTREAM *, EXP, EXP, EXP);
extern BITSTREAM *enc_rethrow(BITSTREAM *);
extern BITSTREAM *enc_thrown(BITSTREAM *, TYPE);
extern BITSTREAM *enc_try_func(BITSTREAM *, EXP);
extern BITSTREAM *enc_catch_func(BITSTREAM *, LIST(TYPE), EXP);
extern BITSTREAM *enc_destr_func(BITSTREAM *, EXP);
extern BITSTREAM *enc_try_start(BITSTREAM *, ulong *, unsigned);
extern BITSTREAM *enc_try_end(BITSTREAM *, ulong);
extern int in_exception_spec;


#endif
