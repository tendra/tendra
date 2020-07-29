/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef UTILITY_IMATH_H
#define UTILITY_IMATH_H

#define  iround(X, Y)		((Y)*(((X) + (Y) - 1) / (Y)))
#define  ilog2(X)		bit_one(X)
#define  ipow2(X)		(1 << (X))
#define  is_pow2(X)		(((X) & ((X) - 1)) == 0)

#endif
