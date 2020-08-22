/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>

#include <construct/installglob.h>
#include <construct/exp.h>

#include <utility/complexity.h>
#include <utility/imath.h>

#include <main/flags.h>

#include <refactor/optimise.h>

#define crit_inline    300
#define crit_decs      5
#define crit_decsatapp 5
#define apply_cost     3

/*
 * delivers 0 if no uses of this proc can be inlined.
 * delivers 1 if this use cannot be inlined
 * delivers 2 if this use can be inlined.
 */
int
inlinechoice(exp t, exp def, int total_uses)
{
	int res;

	exp apars;
	exp fpars;

	int newdecs = 0;
	int no_actuals;
	int max_complexity;

	int nparam;
	const int CONST_BONUS_UNIT = 16;
	int const_param_bonus;
	int adjusted_max_complexity;

	shape shdef = pt(def) /* Oh, yes it is! */;

	if (!eq_shape(sh(father(t)), shdef)) {
		/* shape required by application is different from definition */
		return 1;
	}

	nparam = 0;
	const_param_bonus = 0;

	max_complexity = crit_inline / total_uses;

	if (max_complexity < 15) {
		max_complexity = 15;
	} else if (max_complexity > 120) {
		max_complexity = 120;
	}

	apars = next(t); /* only uses are applications */
	no_actuals = t->last; /* if so then apars is apply_tag... */
	fpars = son(def);

	for (;;) {
		if (fpars->tag != ident_tag || !isparam(fpars)) {
			/* first beyond formals */
			if (!no_actuals) {
				newdecs = 10;
			}
			/* more actuals than formals, since apars->last->break */
			break;
		}
		nparam++;

		switch (apars->tag) {
		case val_tag:
		case real_tag:
		case string_tag:
		case name_tag:
			break;

		case cont_tag:
			if (son(apars)->tag == name_tag && isvar(son(son(apars))) &&
			    !isvar(fpars)) {
				break;
			}

		default:
			newdecs++;
		}

		switch (apars->tag) {
		case val_tag: {
			int n = no(apars);

			if (isbigval(apars)) {
				break;
			}

			/*
			 * Simple constant param. Increase desire to inline
			 * since a constant may cause further optimisation,
			 * eg. strength reduction (mul to shift) or dead code savings.
			 */

			if (0) {
				/* needs a register - poor */
				const_param_bonus += CONST_BONUS_UNIT / 4;
			} else if (n == 0 || (n > 0 && is_pow2(n))) {
				/* very good */
				const_param_bonus += CONST_BONUS_UNIT;
			} else {
				/* less good */
				const_param_bonus += CONST_BONUS_UNIT / 2;
			}

			break;
		}

		case real_tag:
			/* reals not that useful */
			const_param_bonus += CONST_BONUS_UNIT / 4;
			break;

		case string_tag:
		case name_tag:
			break;

		case cont_tag:
			if (son(apars)->tag == name_tag &&
			    isvar(son(son(apars))) &&
			    !isvar(fpars)) {
				break;
			}

			FALL_THROUGH;

		default:
			newdecs++;
			break;
		}

		fpars = next(son(fpars));
		if (apars->last) {
			break;
		}

		apars = next(apars);
	}

	adjusted_max_complexity = max_complexity;

	/*
	 * Increase to up to 3 times (average around 2) according
	 * to const params.
	 */
	if (nparam != 0) {
		adjusted_max_complexity +=
		    (2 * max_complexity * const_param_bonus) /
		    (CONST_BONUS_UNIT * nparam);
	}

	/* increase by number of instructions saved for call */
	adjusted_max_complexity += nparam - newdecs + 1;

	if (complexity(fpars, adjusted_max_complexity, newdecs, crit_decs, crit_decsatapp, apply_cost) >= 0) {
		res = 2;
	} else if (newdecs == 0) {
		res = 0;
	} else {
		res = 1;
	}

	return res;
}

