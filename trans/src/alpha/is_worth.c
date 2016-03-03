/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/check.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <construct/exp.h>
#include <construct/is_worth.h>

#include "make_code.h"

bool
is_worth(exp c)
{
	unsigned char cnam = c->tag;
	bool isflt = is_floating(sh(c)->tag);

	if (sh(c)->tag == ptrhd && al1(sh(c)) == 1 ) {
		return 0;    /* ptr bits */
	}

	if (cnam == real_tag) {
		return true;
	}

	if (cnam == cont_tag && isflt && (son(c)->tag != name_tag || isglob(son(son(c))))) {
		return true;
	}

	if (cnam == cont_tag && son(c)->tag == name_tag && isglob(son(son (c)))) {
		return true;
	}

	if (cnam == val_tag) {
		/* it is sometimes worthwhile extracting big constants from loops ... */
		int n = no(c);
		exp dad;

		if (n == 0) {
			return false;
		}

		dad = father(c);
		if (dad == NULL) {
			return 0;    /* bug ? */
		}

		switch (dad->tag) {
		case and_tag: {
			exp grandad = father (dad);
			if ((grandad->tag == test_tag && (n & (n - 1)) == 0 &&
			     (props (grandad) == 5 || props (grandad) == 6) &&
			     (bro (son (grandad))->tag == val_tag
			      && no (bro (son (grandad))) == 0)) || (son(grandad)->tag ==
			              val_tag && no (son (grandad)) == 0)) {
				/*  a & 2^n == 0 is transformed later to shift and test negative */
				return 0;
			}
			/* else next case */
		}
		FALL_THROUGH;

		case or_tag:
		case xor_tag:
		case test_tag:
			return n < 0 || n >= 0xffff; /* short literal operands */

		case mult_tag:
		case offset_mult_tag:
			if (n <= 0x7fff && n > -0x8000) {
				return 0;    /* short literal operands */
			}

			/*a*2^n and a*2^(n+-1) are transformed later to shifts and adds */
			return (n & (n - 1)) != 0 && (n & (n + 1)) != 0 && ((n - 1) & (n - 2)) != 0;

		case div1_tag:
		case div2_tag:
		case rem2_tag:
			if (n <= 0x7fff && n > -0x8000) {
				return 0 /* short literal operands */ ;
			}

			/* a/2^n transformed later to shift */
			return (n & (n - 1)) != 0;

		default:
			return n > 0x7fff || n < -0x8000 /* short literal operands */ ;
		}
	}

	return (!is_o (cnam) && cnam != clear_tag) ||
	        /* ignore simple things unless ... */
	        (cnam == cont_tag && son(c)->tag == cont_tag &&
	         son(son(c))->tag == name_tag);
}

