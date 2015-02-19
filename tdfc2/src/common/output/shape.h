/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef SHAPE_INCLUDED
#define SHAPE_INCLUDED


/*
    TDF SHAPE ENCODING ROUTINES

    The routines in this module are concerned with the encoding of TDF
    SHAPEs and related sorts.
*/

extern BITSTREAM *enc_add_ptr(BITSTREAM *, EXP, ulong, OFFSET, int);
extern BITSTREAM *enc_alignment(BITSTREAM *, TYPE);
extern BITSTREAM *enc_arith(BITSTREAM *, TYPE, int);
extern BITSTREAM *enc_bfvar(BITSTREAM *, TYPE);
extern BITSTREAM *enc_bool(BITSTREAM *, int);
extern BITSTREAM *enc_char(BITSTREAM *, STRING, TYPE, TYPE);
extern BITSTREAM *enc_extra_offset(BITSTREAM *, TYPE, OFFSET, int);
extern BITSTREAM *enc_float(BITSTREAM *, FLOAT, TYPE);
extern BITSTREAM *enc_float_int(BITSTREAM *, int, TYPE);
extern BITSTREAM *enc_flvar(BITSTREAM *, TYPE);
extern BITSTREAM *enc_int_lit(BITSTREAM *, NAT, TYPE, unsigned);
extern BITSTREAM *enc_nat(BITSTREAM *, NAT, int);
extern BITSTREAM *enc_offset(BITSTREAM *, OFFSET);
extern BITSTREAM *enc_shape(BITSTREAM *, TYPE);
extern BITSTREAM *enc_shape_offset(BITSTREAM *, TYPE);
extern BITSTREAM *enc_snat(BITSTREAM *, NAT, int, int);
extern BITSTREAM *enc_string(BITSTREAM *, STRING, TYPE);
extern BITSTREAM *enc_strlit(BITSTREAM *, STRING);
extern BITSTREAM *enc_variety(BITSTREAM *, TYPE);
extern int eq_type_rep(TYPE, TYPE, int);
extern int is_tokenised_class(TYPE);


#endif
