/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED

#include <string.h>

#include <shared/xalloc.h>

typedef unsigned long bitpattern;

extern int bits_in(bitpattern);
extern int bit_one(bitpattern);

extern bitpattern lo_bits[];
extern bitpattern hi_bits[];

#define  alloc_nof(TYPE, N)\
	((TYPE *)xmalloc((N)* sizeof(TYPE)))

#define  realloc_nof(PTR, TYPE, N)\
	((TYPE *)xrealloc((PTR), (N)* sizeof(TYPE)))

#define  eq(X, Y)		(!strcmp((X), (Y)))
#define  maximum(X, Y)	(((X) > (Y))?(X):(Y))
#define  minimum(X, Y)	(((X) > (Y))?(Y):(X))
#define  array_size(X)	(sizeof(X) / sizeof(X[0]))
#define  round(X, Y)		((Y)*(((X) + (Y) - 1) / (Y)))
#define  log2(X)		bit_one(X)
#define  pow2(X)		(1 << (X))
#define  is_pow2(X)		(((X) & ((X) - 1)) == 0)

#endif
