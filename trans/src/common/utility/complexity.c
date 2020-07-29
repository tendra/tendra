/*
 * Copyright 2014, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>

#include <tdf/tag.h>

#include <construct/exp.h>

#include <utility/complexity.h>

#ifdef TRANS_SPARC
#include "sparcins.h"
#endif

/*
 * Apply complexity to a list of expressions
 */
static int
sbl(exp e, int count, int newdecs,
	int crit_decs, int crit_decsatapp, int apply_cost)
{
	int c;

	c = complexity(e, count, newdecs,
		crit_decs, crit_decsatapp, apply_cost);
	if (c < 0) {
		return c;
	}

	if (e->last) {
		return c;
	}

	return sbl(bro(e), c, newdecs,
		crit_decs, crit_decsatapp, apply_cost);
}

/* see utility/inline.h */
int
complexity(exp e, int count, int newdecs,
	int crit_decs, int crit_decsatapp, int apply_cost)
{
	unsigned char n = e->tag;

	if (count < 0) {
		return -1;
	}

	if (newdecs > crit_decs) {
		return -2;
	}

	if (son(e) == NULL) {
		return count;
	}

	/*
	 * This code has been merged from several sources. I believe these were
	 * copied and not updated over time, as new tags were introduced to TDF.
	 * Some tags were not present for certian architectures (prof_tag,
	 * val_tag, general_env_offset_tag, apply_general_tag); I think their
	 * presence here is either harmless or desirable.
	 */

	switch (n) {
	case apply_general_tag:
	case apply_tag:
		if (newdecs > crit_decsatapp) {
			return -3;
		}

		return sbl(son(e), count - apply_cost, newdecs + 1,
			crit_decs, crit_decsatapp, apply_cost);

	case rep_tag:
		return complexity(bro(son(e)), count - 1, newdecs + 1,
			crit_decs, crit_decsatapp, apply_cost);

	case res_tag:
		return complexity(son(e), count + 1, newdecs,
			crit_decs, crit_decsatapp, apply_cost);

	case ident_tag:
#if defined(TRANS_M68K) || defined(TRANS_HPPA)
		if (isloadparam(son(e))) {
			return sbl(son(e), count - 1, newdecs,
				crit_decs, crit_decsatapp, apply_cost);
		}
#endif
		return sbl(son(e), count - 1, newdecs + 1,
			crit_decs, crit_decsatapp, apply_cost);

	case val_tag:
#ifdef TRANS_SPARC
		return SIMM13_SIZE(no(e)) ? count : (count - 1);
#endif
	case top_tag:
	case prof_tag:
	case clear_tag:
		return count;

	case case_tag:
		return complexity(son(e), count - 1, newdecs,
			crit_decs, crit_decsatapp, apply_cost);

	case name_tag:
	case string_tag:
	case env_offset_tag:
		return count - 1;

	case labst_tag:
		return complexity(bro(son(e)), count, newdecs,
			crit_decs, crit_decsatapp, apply_cost);

	case cond_tag:
	case seq_tag:
	case solve_tag:
		return sbl(son(e), count, newdecs,
			crit_decs, crit_decsatapp, apply_cost);

	default:
		return sbl(son(e), count - 1, newdecs,
			crit_decs, crit_decsatapp, apply_cost);
	}
}

