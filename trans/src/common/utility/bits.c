/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <utility/bits.h>

int lsmask[33] = {
	0,
	0x1, 0x3, 0x7, 0xf,
	0x1f, 0x3f, 0x7f, 0xff,
	0x1ff, 0x3ff, 0x7ff, 0xfff,
	0x1fff, 0x3fff, 0x7fff, 0xffff,
	0x1ffff, 0x3ffff, 0x7ffff, 0xfffff,
	0x1fffff, 0x3fffff, 0x7fffff, 0xffffff,
	0x1ffffff, 0x3ffffff, 0x7ffffff, 0xfffffff,
	0x1fffffff, 0x3fffffff, 0x7fffffff, (int) 0xffffffff
};

int msmask[33] = {
	0,
	(int) 0x80000000,  (int) 0xc0000000, (int) 0xe0000000, (int) 0xf0000000,
	(int) 0xf8000000,  (int) 0xfc000000, (int) 0xfe000000, (int) 0xff000000,
	(int) 0xff800000,  (int) 0xffc00000, (int) 0xffe00000, (int) 0xfff00000,
	(int) 0xfff80000,  (int) 0xfffc0000, (int) 0xfffe0000, (int) 0xffff0000,
	(int) 0xffff8000,  (int) 0xffffc000, (int) 0xffffe000, (int) 0xfffff000,
	(int) 0xfffff800,  (int) 0xfffffc00, (int) 0xfffffe00, (int) 0xffffff00,
	(int) 0xffffff80,  (int) 0xffffffc0, (int) 0xffffffe0, (int) 0xfffffff0,
	(int) 0xfffffff8,  (int) 0xfffffffc, (int) 0xfffffffe, (int) 0xffffffff
};

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

