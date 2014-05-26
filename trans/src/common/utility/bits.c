/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <utility/bits.h>

int
bitsin(long b)
{
	int   n;
	long  mask;

	n    = 0;
	mask = 1;

	for ( ; b != 0; ) {
		n += ((b & mask) != 0) ? 1 : 0;
		b &= ~mask;
		mask <<= 1;
	}

	return n;
}

