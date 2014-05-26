/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <utility/bits.h>

int
bits_in(bitpattern n)
{
	/* Table of bits in: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F */
	static int b[16] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };
	int c;

	c = 0;

	while (n) {
		c += b[n & 0xf];
		n >>= 4;
	}

	return c;
}

int
bit_one(bitpattern n)
{
	bitpattern m;
	int c;

	c = 0;

	for (m = n; m; m >>= 1, c++) {
		if (m & 1) {
			return c;
		}
	}

	return -1;
}

