/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef NEEDSCAN_INCLUDED
#define NEEDSCAN_INCLUDED

#include <reader/exp.h>

#include <construct/installtypes.h>

/* condition for shape to be treated as a struct */
#define sparccpd(s) (s->tag == cpdhd || s->tag == nofhd || \
                     s->tag == shcomplexhd || shape_size(s) >64 || \
                     s->tag == u64hd || s->tag == s64hd)

extern bool subvar_use(exp);
extern needs likediv(exp *, exp **);
extern needs likeplus(exp *, exp **);
extern needs scan(exp *, exp **);

extern void check_asm_seq(exp e, int ext);

extern int maxfix, maxfloat;

#endif /* NEEDSCAN_INCLUDED */
