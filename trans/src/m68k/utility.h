/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED

#define  round(X, Y)		((Y)*(((X) + (Y) - 1) / (Y)))
#define  log2(X)		bit_one(X)
#define  pow2(X)		(1 << (X))
#define  is_pow2(X)		(((X) & ((X) - 1)) == 0)

#endif
