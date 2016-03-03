/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/check.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <construct/exp.h>
#include <construct/is_worth.h>

#include "instruct.h"	/* IMM_SIZE() */
#include "regable.h"

/*
 * Will an ident exp be in memory?
 * We have to guess at this stage for non globals.
 */
#define INMEMIDENT(ident_exp)	(isvis(ident_exp) || isglob(ident_exp))

/*
 * is_worth() for a complicated cont_tag.
 * True for any combination of reff_tag, cont_tag and name_tag.
 * 'c' is the son of the top cont_tag.
 * Allowing anything causes a bug when compiling SPECINT92 085.gcc.
 */
static bool is_worth_cont_aux(exp c)
{
	switch (c->tag) {
	case reff_tag:
		if (no(c) != 0) {
			return 0;    /* dont optimise non-zero offset */
		}

		FALL_THROUGH;

	case cont_tag:
		return is_worth_cont_aux(son(c));

	case name_tag:
		return 1;

	default:
		return 0;
	}

	UNREACHED;
}

/*
 * Decide if expression c is worth declaring separately over a range it's
 * value will not change over, eg outside loop.
 * We have to balance the value of this against likely register pressure
 * impact.
 */
bool
is_worth(exp c)
{
	int cnam = c->tag;
	shape s = sh(c);

	if (!is_floating(s->tag) && !valregable(s)) {
		/* cannot go inreg, and anyway * too big to be worthwhile */
		return false;
	}

	if (s->tag == ptrhd && al1(s) == 1) {
		return false;    /* ptr bits */
	}

	if (cnam == real_tag) {
		return true;    /* real const complex to load */
	}

	if (cnam == goto_tag) {
		return false;    /* never identify a goto (causes bad labels) */
	}

	if (cnam == cont_tag && son(c)->tag == name_tag) {
		/* a simple load, most worthwile for globals to avoid TOC access */
		return INMEMIDENT(son(son(c)));
	}

	if (cnam == cont_tag) {
		/* complex load */
		return is_worth_cont_aux(son(c));
	}

	if (cnam == name_tag && isglob(son(c)) && s->tag != prokhd) {
		/* avoid load of TOC table entry in loops, except for params where there is no load delay */
		return father(c)->tag != apply_tag;
	}

	if (cnam == val_tag) {
		/* it is sometimes worthwhile extracting big constants from loops ... */
		long n = no(c);
		exp dad = father(c);

		switch (dad->tag) {
		case and_tag:	/* +++ allow for rlimn instruction */
		case or_tag:
		case xor_tag:
			return !(IMMLOGL_SIZE(n) || IMMLOGU_SIZE(n));	/* short literal operands */

		case mult_tag:
		case offset_mult_tag:
			/*
			 * a*2^n and a*2^(n+-1) are transformed later to shifts and adds
			 */
			return !IMM_SIZE(n) && (n & (n - 1)) != 0 && (n & (n + 1)) != 0 && ((n - 1) & (n - 2)) != 0;

		case div1_tag:
		case div2_tag:
		case rem2_tag:
			/* a/2^n transformed later to shift */
			return !IMM_SIZE(n) && (n & (n - 1)) != 0;

		case ass_tag:
		case assvol_tag: {
			/* must load all constants before store */
			/* +++ better way of working out inmem lhs */
			exp lhs = son(dad);

			if (lhs->tag == name_tag) {
				if (INMEMIDENT(son(lhs))) {
					return true;    /* inmem */
				} else {
					return !IMM_SIZE(n) && !IMMLOGU_SIZE(n);
				}
				/* big const */
			} else {
				/* complicated inmem */
				return true;
			}
		}

		default:
			return !IMM_SIZE(n) /* short literal operands */ ;
		}
	}

	if (is_o(cnam) || cnam == clear_tag) {
		/* simple construct */
		return false;
	}

	/* something complicated */
	return true;
}

