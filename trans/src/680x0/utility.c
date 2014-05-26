/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdarg.h>

#include <shared/check.h>

#include <reader/basicread.h>

#include "instrs.h"
#include "utility.h"

extern long crt_line_num;
extern char *crt_fname;
extern char *progname;

long total_calloced;

#if 0
/* Makes automatically generated makefile work */
#include "xalloc.c"
#endif


/*
    FIND THE FIRST NONZERO BIT

    This routine returns the bit number of the least significant set
    bit in n.  For 0 it returns -1.
*/

int
bit_one(bitpattern n)
{
	int c = 0;
	bitpattern m;
	for (m = n; m; m >>= 1, c++) {
		if (m & 1) {
			return c;
		}
	}
	return -1;
}


/*
    FIND THE NUMBER OF SET BITS

    The number of set bits in n is returned.
*/

int
bits_in(bitpattern n)
{
	/* Table of bits in : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F */
	static int b[16] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };
	int c = 0;
	while (n) {
		c += b[n & 0xf];
		n >>= 4;
	}
	return c;
}


/*
    BIT PATTERNS

    lo_bits [n] is the number with its bottom n bits set and the rest
    zero.  hi_bits [n] is the number with its top n bits set and the rest
    zero.
*/

bitpattern lo_bits[] = { 0,
	0x00000001, 0x00000003, 0x00000007, 0x0000000f,
	0x0000001f, 0x0000003f, 0x0000007f, 0x000000ff,
	0x000001ff, 0x000003ff, 0x000007ff, 0x00000fff,
	0x00001fff, 0x00003fff, 0x00007fff, 0x0000ffff,
	0x0001ffff, 0x0003ffff, 0x0007ffff, 0x000fffff,
	0x001fffff, 0x003fffff, 0x007fffff, 0x00ffffff,
	0x01ffffff, 0x03ffffff, 0x07ffffff, 0x0fffffff,
	0x1fffffff, 0x3fffffff, 0x7fffffff, 0xffffffff };

bitpattern hi_bits[] = { 0,
	0x80000000, 0xc0000000, 0xe0000000, 0xf0000000,
	0xf8000000, 0xfc000000, 0xfe000000, 0xff000000,
	0xff800000, 0xffc00000, 0xffe00000, 0xfff00000,
	0xfff80000, 0xfffc0000, 0xfffe0000, 0xffff0000,
	0xffff8000, 0xffffc000, 0xffffe000, 0xfffff000,
	0xfffff800, 0xfffffc00, 0xfffffe00, 0xffffff00,
	0xffffff80, 0xffffffc0, 0xffffffe0, 0xfffffff0,
	0xfffffff8, 0xfffffffc, 0xfffffffe, 0xffffffff };
