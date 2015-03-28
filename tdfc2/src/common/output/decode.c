/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include <tdf/bitstream.h>
#include <tdf/decode.h>
#include <tdf/encode.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/option.h>
#include <utility/error.h>
#include <utility/buffer.h>

#include <parse/char.h>
#include <parse/file.h>
#include <parse/literal.h>

#include <output/decode.h>
#include <output/encode.h>


/*
    This routine reads a string from the bitstream bs into the buffer bf.
*/

void
de_tdfstring(BITSTREAM *bs, BUFFER *bf)
{
	unsigned m = (unsigned)de_int(bs);
	unsigned long n = de_int(bs);
	string p = stretch_buffer(bf, bf->posn, n);
	bf->posn = p + n;
	while (n) {
		int ch = CHAR_SIMPLE;
		unsigned long c = (unsigned long)de_bits(bs, m);
		c = from_ascii(c, &ch);
		*(p++) = (character)c;
		n--;
	}
	*p = 0;
	return;
}
