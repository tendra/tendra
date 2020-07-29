/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef INIT_INCLUDED
#define INIT_INCLUDED


/*
    TDF INITIALISATION ENCODING ROUTINES

    The routines in this module are concerned with the encoding of
    initialisation expressions.
*/

extern BITSTREAM *enc_init_tag(BITSTREAM *, ulong, OFFSET, int, TYPE, EXP, EXP,
			       int);
extern BITSTREAM *enc_init_global(BITSTREAM *, EXP, EXP, ulong, TYPE);
extern BITSTREAM *enc_init_local(BITSTREAM *, EXP, EXP, ulong, TYPE, EXP);
extern BITSTREAM *enc_assign_local(BITSTREAM *, EXP, EXP, ulong, TYPE, EXP);
extern BITSTREAM *enc_init_array(BITSTREAM *, EXP, NAT, TYPE);
extern BITSTREAM *enc_init_class(BITSTREAM *, EXP, CLASS_TYPE);
extern BITSTREAM *enc_term_local(BITSTREAM *, ulong, OFFSET, int, TYPE, EXP,
				 int);
extern BITSTREAM *enc_term_global(BITSTREAM *, ulong, TYPE, EXP, ulong);
extern BITSTREAM *enc_flag_test(BITSTREAM *, ulong, unsigned, int, NTEST);
extern BITSTREAM *enc_destr_count(BITSTREAM *, TYPE, int);
extern BITSTREAM *enc_term_type(BITSTREAM *, TYPE);
extern BITSTREAM *enc_dealloc(BITSTREAM *, EXP, ulong);
extern BITSTREAM *enc_alloc(BITSTREAM *, EXP);
extern BITSTREAM *make_term_local(BITSTREAM *, TYPE, EXP *, int);
extern void make_term_global(TYPE, EXP *);
extern EXP make_dummy_init(TYPE);
extern int is_init_complex(EXP);
extern int in_dynamic_init;
extern int in_static_init;


#endif
