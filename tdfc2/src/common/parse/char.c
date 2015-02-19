/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include <shared/check.h>

#include "config.h"

#include "c_types.h"
#include "char.h"
#include "literal.h"


/*
    This flag is true if the native codeset is ASCII.  It is initially -1
    indicating that the conversion tables have not been initialised.
*/

int is_ascii = -1;


/*
    These tables give the conversions of ASCII to and from the native
    codeset.  The ASCII to native table is deduced for the portable
    codeset from the list of characters in char.h which is given in
    ASCII sequence.
*/


static character to_ascii_tab[NO_CHAR + 1];

static character from_ascii_tab[NO_CHAR + 1] = {
#define NONE			char_illegal
#define CHAR_DATA(A, B, C, D)	(D),
#include "char.h"
#undef CHAR_DATA
	NONE			/* dummy last element */
};



/*
    DOES HOST MACHINE HAVE EXTENDED CHARACTERS?

    The function is_extended() returns true if a character value is considered
    an extended value.
*/

int
is_extended(int c)
{
	if (c == char_eof) {
		return 0;
	}

	return (unsigned) c >= NO_CHAR;
}


/*
    This routine converts the character c from the native codeset to
    ASCII.
*/

unsigned long
to_ascii(unsigned long c, int *ch)
{
	if (c < NO_CHAR) {
		c = (unsigned long)to_ascii_tab[c];
		*ch = CHAR_ASCII;
	}
	return c;
}


void
init_ascii(void)
{
	unsigned c;
	int asc;

	assert(is_ascii == -1);

	/* Set up conversion tables */
	asc = 1;
	for (c = 0; c < NO_CHAR; c++) {
		to_ascii_tab[c] = (character)c;
	}

	for (c = 0; c < NO_CHAR; c++) {
		unsigned a = (unsigned)from_ascii_tab[c];
		if (a == NONE) {
			a = c;
		}
		if (a != c) {
			asc = 0;
		}
		from_ascii_tab[c] = (character)a;
		to_ascii_tab[a] = (character)c;
	}

	is_ascii = asc;
}


/*
    This routine converts the character c to the native codeset from
    ASCII.
*/

unsigned long
from_ascii(unsigned long c, int *ch)
{
	if (c < NO_CHAR) {
		c = (unsigned long)from_ascii_tab[c];
		*ch = CHAR_SIMPLE;
	}
	return c;
}


/*
    This routine maps the look-up table p from ASCII to native codeset.
*/

void
map_ascii(unsigned char *p)
{
	unsigned c;

	assert(is_ascii != -1);

	if (is_ascii == 0) {
		/* Map table */
		unsigned char b = p[NONE];
		unsigned char copy[NO_CHAR];
		for (c = 0; c < NO_CHAR; c++) {
			copy[c] = p[c];
			p[c] = b;
		}
		SET(copy);
		for (c = 0; c < NO_CHAR; c++) {
			character a = from_ascii_tab[c];
			p[a] = copy[c];
		}
	}
}


/*
    This table gives the ranges of the unicode characters which are
    suitable for use in an identifier name in ascending order.  It is
    derived from Annex E of the standard (which derives from ISO/IEC
    PDTR 10176) with two misprints corrected.  0e0d should be 0e8d
    and 5e76 should be fe76.  Note that the upper and lower case
    English alphabets have been included even though they are not
    valid universal character names.
*/

static struct {
	unsigned long lo;
	unsigned long hi;
} alpha_range[] = {
	/* Latin */
	{ 0x0041, 0x005a }, { 0x0061, 0x007a }, { 0x00c0, 0x00d6 },
	{ 0x00d8, 0x00f6 }, { 0x00f8, 0x01f5 }, { 0x01fa, 0x0217 },
	{ 0x0250, 0x02a8 },

	/* Greek */
	{ 0x0384, 0x0384 }, { 0x0388, 0x038a }, { 0x038c, 0x038c },
	{ 0x038e, 0x03a1 }, { 0x03a3, 0x03ce }, { 0x03d0, 0x03d6 },
	{ 0x03da, 0x03da }, { 0x03dc, 0x03dc }, { 0x03de, 0x03de },
	{ 0x03e0, 0x03e0 }, { 0x03e2, 0x03f3 },

	/* Cyrilic */
	{ 0x0401, 0x040d }, { 0x040f, 0x044f }, { 0x0451, 0x045c },
	{ 0x045e, 0x0481 }, { 0x0490, 0x04c4 }, { 0x04c7, 0x04c8 },
	{ 0x04cb, 0x04cc }, { 0x04d0, 0x04eb }, { 0x04ee, 0x04f5 },
	{ 0x04f8, 0x04f9 },

	/* Armenian */
	{ 0x0531, 0x0556 }, { 0x0561, 0x0587 },

	/* Hebrew */
	{ 0x05d0, 0x05ea }, { 0x05f0, 0x05f4 },

	/* Arabic */
	{ 0x0621, 0x063a }, { 0x0640, 0x0652 }, { 0x0670, 0x06b7 },
	{ 0x06ba, 0x06be }, { 0x06c0, 0x06ce }, { 0x06e5, 0x06e7 },

	/* Devanagari */
	{ 0x0905, 0x0939 }, { 0x0958, 0x0962 },

	/* Bengali */
	{ 0x0985, 0x098c }, { 0x098f, 0x0990 }, { 0x0993, 0x09a8 },
	{ 0x09aa, 0x09b0 }, { 0x09b2, 0x09b2 }, { 0x09b6, 0x09b9 },
	{ 0x09dc, 0x09dd }, { 0x09df, 0x09e1 }, { 0x09f0, 0x09f1 },

	/* Gurmukhi */
	{ 0x0a05, 0x0a0a }, { 0x0a0f, 0x0a10 }, { 0x0a13, 0x0a28 },
	{ 0x0a2a, 0x0a30 }, { 0x0a32, 0x0a33 }, { 0x0a35, 0x0a36 },
	{ 0x0a38, 0x0a39 }, { 0x0a59, 0x0a5c }, { 0x0a5e, 0x0a5e },

	/* Gujarati */
	{ 0x0a85, 0x0a8b }, { 0x0a8d, 0x0a8d }, { 0x0a8f, 0x0a91 },
	{ 0x0a93, 0x0aa8 }, { 0x0aaa, 0x0ab0 }, { 0x0ab2, 0x0ab3 },
	{ 0x0ab5, 0x0ab9 }, { 0x0ae0, 0x0ae0 },

	/* Oriya */
	{ 0x0b05, 0x0b0c }, { 0x0b0f, 0x0b10 }, { 0x0b13, 0x0b28 },
	{ 0x0b2a, 0x0b30 }, { 0x0b32, 0x0b33 }, { 0x0b36, 0x0b39 },
	{ 0x0b5c, 0x0b5d }, { 0x0b5f, 0x0b61 },

	/* Tamil */
	{ 0x0b85, 0x0b8a }, { 0x0b8e, 0x0b90 }, { 0x0b92, 0x0b95 },
	{ 0x0b99, 0x0b9a }, { 0x0b9c, 0x0b9c }, { 0x0b9e, 0x0b9f },
	{ 0x0ba3, 0x0ba4 }, { 0x0ba8, 0x0baa }, { 0x0bae, 0x0bb5 },
	{ 0x0bb7, 0x0bb9 },

	/* Telugu */
	{ 0x0c05, 0x0c0c }, { 0x0c0e, 0x0c10 }, { 0x0c12, 0x0c28 },
	{ 0x0c2a, 0x0c33 }, { 0x0c35, 0x0c39 }, { 0x0c60, 0x0c61 },

	/* Kannada */
	{ 0x0c85, 0x0c8c }, { 0x0c8e, 0x0c90 }, { 0x0c92, 0x0ca8 },
	{ 0x0caa, 0x0cb3 }, { 0x0cb5, 0x0cb9 }, { 0x0ce0, 0x0ce1 },

	/* Malayalam */
	{ 0x0d05, 0x0d0c }, { 0x0d0e, 0x0d10 }, { 0x0d12, 0x0d28 },
	{ 0x0d2a, 0x0d39 }, { 0x0d60, 0x0d61 },

	/* Thai */
	{ 0x0e01, 0x0e30 }, { 0x0e32, 0x0e33 }, { 0x0e40, 0x0e46 },
	{ 0x0e4f, 0x0e5b },

	/* Lao */
	{ 0x0e81, 0x0e82 }, { 0x0e84, 0x0e84 }, { 0x0e87, 0x0e87 },
	{ 0x0e88, 0x0e88 }, { 0x0e8a, 0x0e8a }, { 0x0e8d, 0x0e8d },
	{ 0x0e94, 0x0e97 }, { 0x0e99, 0x0e9f }, { 0x0ea1, 0x0ea3 },
	{ 0x0ea5, 0x0ea5 }, { 0x0ea7, 0x0ea7 }, { 0x0eaa, 0x0eaa },
	{ 0x0eab, 0x0eab }, { 0x0ead, 0x0eb0 }, { 0x0eb2, 0x0eb2 },
	{ 0x0eb3, 0x0eb3 }, { 0x0ebd, 0x0ebd }, { 0x0ec0, 0x0ec4 },
	{ 0x0ec6, 0x0ec6 },

	/* Georgian */
	{ 0x10a0, 0x10c5 }, { 0x10d0, 0x10f6 },

	/* Hangul */
	{ 0x1100, 0x1159 }, { 0x1161, 0x11a2 }, { 0x11a8, 0x11f9 },

	/* Latin (continued) */
	{ 0x1e00, 0x1e9a }, { 0x1ea0, 0x1ef9 },

	/* Greek (continued) */
	{ 0x1f00, 0x1f15 }, { 0x1f18, 0x1f1d }, { 0x1f20, 0x1f45 },
	{ 0x1f48, 0x1f4d }, { 0x1f50, 0x1f57 }, { 0x1f59, 0x1f59 },
	{ 0x1f5b, 0x1f5b }, { 0x1f5d, 0x1f5d }, { 0x1f5f, 0x1f7d },
	{ 0x1f80, 0x1fb4 }, { 0x1fb6, 0x1fbc }, { 0x1fc2, 0x1fc4 },
	{ 0x1fc6, 0x1fcc }, { 0x1fd0, 0x1fd3 }, { 0x1fd6, 0x1fdb },
	{ 0x1fe0, 0x1fec }, { 0x1ff2, 0x1ff4 }, { 0x1ff6, 0x1ffc },

	/* Hiragana */
	{ 0x3041, 0x3094 }, { 0x309b, 0x309e },

	/* Katakana */
	{ 0x30a1, 0x30fe },

	/* Bopmofo */
	{ 0x3105, 0x312c },

	/* CJK Unified Ideographs */
	{ 0x4e00UL, 0x9fa5UL }, { 0xf900UL, 0xfa2dUL }, { 0xfb1fUL, 0xfb36UL },
	{ 0xfb38UL, 0xfb3cUL }, { 0xfb3eUL, 0xfb3eUL }, { 0xfb40UL, 0xfb41UL },
	{ 0xfb42UL, 0xfb44UL }, { 0xfb46UL, 0xfbb1UL }, { 0xfbd3UL, 0xfd3fUL },
	{ 0xfd50UL, 0xfd8fUL }, { 0xfd92UL, 0xfdc7UL }, { 0xfdf0UL, 0xfdfbUL },
	{ 0xfe70UL, 0xfe72UL }, { 0xfe74UL, 0xfe74UL }, { 0xfe76UL, 0xfefcUL },
	{ 0xff21UL, 0xff3aUL }, { 0xff41UL, 0xff5aUL }, { 0xff66UL, 0xffbeUL },
	{ 0xffc2UL, 0xffc7UL }, { 0xffcaUL, 0xffcfUL }, { 0xffd2UL, 0xffd7UL },
	{ 0xffdaUL, 0xffdcUL }
};


/*
    This routine checks whether the unicode character c represents an
    alphabetic value suitable for use in an identifier name.  It
    operates by performing a binary chop on the table above.
*/

int
unicode_alpha(unsigned long c)
{
	int i = 0;
	int j = array_size(alpha_range) - 1;
	do {
		int k = (i + j) / 2;
		if (c < alpha_range[k].lo) {
			/* Lower half */
			j = k - 1;
		} else if (c > alpha_range[k].hi) {
			/* Upper half */
			i = k + 1;
		} else {
			/* Match found */
			return 1;
		}
	} while (i <= j);
	return 0;
}
