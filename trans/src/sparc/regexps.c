/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <utility/max.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>

#ifdef DWARF2
#include <local/dw2_config.h>
#endif

#include <construct/aldefs.h>

#include <main/flags.h>

#include "addrtypes.h"
#include "move.h"
#include "bitsmacs.h"
#include "regmacs.h"
#include "regexps.h"

#ifdef DWARF2
#include "dw2_extra.h"
#include <dwarf2/dw2_iface.h>
#endif

static bool
couldaffect(exp e, exp z);

/*
 * 0-31 represent the fixed point registers, 32-47 the floating point registers.
 */
regpeep regexps[48];

/*
 * Are two shapes of the same size, alignment, and floating-point-ness?
 */
static bool
eq_sze(shape as, shape bs)
{
	if (is_floating(as->tag)) {
		return as->tag == bs->tag;
	}

	if (is_floating(bs->tag)) {
		return 0;
	}

	return shape_size(as) == shape_size(bs)
		&& shape_align(as) == shape_align(bs);
}

/*
 * Are two lists of expressions similar?
 */
static bool
sim_explist(exp al, exp bl)
{
	if (al == NULL && bl == NULL) {
		return 1;
	}

	if (al == NULL || bl == NULL) {
		return 0;
	}

	if (!sim_exp(al, bl)) {
		return 0;
	}

	if (al->last && bl->last) {
		return 1;
	}

	if (al->last || bl->last) {
		return 0;
	}

	return sim_explist(bro(al), bro(bl));
}

/*
 * Basically this is the same as eq_exp except that equal shapes requirement
 * is weakened to equal size and alignment.
 */
bool
sim_exp(exp a, exp b)
{
	if (a->tag != b->tag) {
		return 0;
	}

	if (a->tag == name_tag) {
		return son(a) == son(b)
			&& no(a) == no(b)
			&& eq_sze(sh(a), sh(b));
	}

	if (!is_a(a->tag) || !eq_sze(sh(a), sh(b))) {
		return 0;
	}

	return no(a) == no(b)
		&& sim_explist(son(a), son(b))
		&& ((a->tag != current_env_tag) || (props(a) == props(b)));
}

/*
 * Forget all register-exp associations
 */
void
clear_all(void)
{
	int i;

	for (i = 0; i < 48; i++) {
		regexps[i].keptexp = NULL;
		setregalt(regexps [i].inans, 0);
#ifdef DWARF2
		if (diag == DIAG_DWARF2) {
			dw_close_regassn(i);
		}
#endif
	}
}

/*
 * Forget the exp associated with register i
 */
void
clear_reg(int i)
{
	i = ABS(i);

	if (i >= 0 && i < 48) {
		regexps[i].keptexp = NULL;
		setregalt(regexps [i].inans, 0);
#ifdef DWARF2
		if (diag == DIAG_DWARF2) {
			dw_close_regassn(i);
		}
#endif
	}
}

/*
 * Has an expression already been evaulated into a register?
 */
ans
iskept(exp e)
{
	int i;
	ans nilans;
	setregalt(nilans, 0);

#ifdef NO_KEPT_OPTS
	/* no register tracking */
	return nilans;
#endif

	if (sh(e)->tag == cpdhd) {
		/* Tracking of unions is unsafe */
		return nilans;
	}

	for (i = 0 ; i < 48 ; i++) {
		exp ke   = regexps[i].keptexp;
		bool isc = regexps[i].iscont;

		if (ke == NULL) {
			/* there isn't an association with register i? */
			continue;
		}

		if ((!isc && sim_exp(ke, e))
			|| (e->tag == cont_tag
				&& isc
				&& eq_sze(sh(ke), sh(e))
				&& sim_exp(ke, son (e))
				&& al1(sh(son(e))) == al1(sh(ke))))
		{
			ans aa;

			aa = regexps[i].inans;

			switch (discrim(aa)) {
			case notinreg:
				if (!aa.val.instoreans.adval) {
					/* the expression is given indirectly, it may
					   also be in another register */
					continue;
				}

				/* FALL THROUGH */

			default:
#ifdef DWARF2
				if (diag == DIAG_DWARF2) {
					dw_used_regassn(i);
				}
#endif
				return aa;
			}
		} else if (ke->tag == cont_tag && !isc) {
			ans aq;

			aq = regexps[i].inans;

			if (discrim(aq) == notinreg) {
				instore is;

				is = insalt(aq);
				if (!is.adval && is.b.offset == 0
					&& IS_FIXREG(is.b.base)
					&& sim_exp(son(ke), e))
				{
					/* the contents of required expression is here as
					 * a register-offset */
#ifdef DWARF2
					if (diag == DIAG_DWARF2) {
						dw_used_regassn(i);
					}
#endif
					is.adval = 1;
					setinsalt(aq, is);
					return aq;
				}
			}
		} else if (ke->tag == reff_tag && !isc) {
			ans aq;

			aq = regexps[i].inans;

			if (discrim(aq) == notinreg) {
				instore is;
				is = insalt(aq);
				if (is.adval && is.b.offset == (no(ke) / 8)
					&& IS_FIXREG(is.b.base)
					&& sim_exp(son(ke), e))
				{
					/* a ref selection of required expression is here as
					 * a register-offset */
#ifdef DWARF2
					if (diag == DIAG_DWARF2) {
						dw_used_regassn (i);
					}
#endif
					is.adval = 1;
					is.b.offset = 0;
					setinsalt(aq, is);
					return aq;
				}
			}
		}
	}

	return nilans;
}

/*
 * Set up an exp-location association
 */
void
keepexp(exp e, ans loc)
{
	int reg;

	/* Find the register number */
	switch (discrim(loc)) {
	case insomereg:
	case insomefreg:
		error(ERR_SERIOUS, "Illegal location in keepexp");
		return;

	case inreg:
		reg = regalt(loc);
		break;

	case infreg:
		reg = fregalt(loc).fr + 32;
		break;

	case notinreg:
		reg = insalt(loc).b.base;
		if (!IS_FIXREG(reg)) {
			return;
		}
		break;
	}

	assert(reg >= 0 && reg < 48);
	assert(reg != R_TMP);

	regexps[reg].keptexp = e;
	regexps[reg].inans   = loc;
	regexps[reg].iscont  = 0;

#ifdef DWARF2
	if (diag == DIAG_DWARF2) {
		dw_init_regassn(reg);
	}
#endif
}

/*
 * Set up a contents-register association
 */
void
keepcont(exp e, int regcode)
{
	freg fr;
	int reg = ABS(regcode);

	assert(reg >= 0 && reg < 48);
	assert(reg != R_TMP);

	if (reg > 31) {
		fr.dble = regcode < 0;
		fr.fr = reg - 32;
		setfregalt(regexps[reg].inans, fr);
	} else {
		instore is;
		is.b.base = regcode;
		is.b.offset = 0;
		is.adval = 1;
		setinsalt(regexps[reg].inans, is);
	}

	regexps[reg].keptexp = e;
	regexps[reg].iscont  = 1;

#ifdef DWARF2
	if (diag == DIAG_DWARF2) {
		dw_init_regassn(reg);
	}
#endif
}

/*
 * Set up an exp-register association
 */
void
keepreg(exp e, int regcode)
{
	freg fr;
	int reg = ABS(regcode);

	assert(reg >= 0 && reg < 48);
	assert(reg != R_TMP);

	if (reg > 31) {
		fr.dble = regcode < 0;
		fr.fr = reg - 32;
		setfregalt(regexps[reg].inans, fr);
	} else {
		instore is;
		is.b.base   = regcode;
		is.b.offset = 0;
		is.adval    = 1;
		setinsalt(regexps[reg].inans, is);
	}

	regexps[reg].keptexp = e;
	regexps[reg].iscont  = 0;

#ifdef DWARF2
	if (diag == DIAG_DWARF2) {
		dw_init_regassn(reg);
	}
#endif
}

/* Could e be lhs? */
static bool
couldbe(exp e, exp lhs)
{
	unsigned char ne = e->tag ;
	exp s = son(e);

	if (ne == name_tag) {
		if (lhs != 0 && s == son(lhs)) {
			return 1;
		}

		if (isvar(s)) {
			return lhs == 0 && (isvis (s) || isglob(s));
		}

		if (s->tag == proc_tag) {
			return lhs == 0;
		}

		if (son(s) == NULL) {
			return 1;
		}

		return couldbe(son(s), lhs);
	}

	if (ne == cont_tag) {
		if (lhs != 0 && s->tag == name_tag && son(s) != NULL) {
			return son(s) == son(lhs)
				|| isvis(son(lhs))
				|| isvis(son(s));
		}

		return 1;
	}

	if (ne == reff_tag || ne == field_tag) {
		return couldbe(s, lhs);
	}

	if (ne == addptr_tag || ne == subptr_tag) {
		return couldbe (s, lhs) || couldaffect(bro(s), lhs);
	}

	return 1;
}

/*
 * Could an alteration to z affect e?
 */
static bool
couldaffect(exp e, exp z)
{
	unsigned char ne;

	ne = e->tag ;

	if (ne == cont_tag) {
		return couldbe(son(e), z);
	}

	if (ne == name_tag) {
		if (isvar (son(e))) {
			return z == 0 && isvis(son(e));
		}

		if (son(e)->tag == proc_tag) {
			return 0;
		}

		if (son(son(e)) == NULL) {
			return 1;
		}

		return couldaffect(son(son(e)), z);
	}

	if (ne < plus_tag || ne == contvol_tag) {
		return 1;
	}

	for (e = son(e); e != NULL; e = bro(e)) {
		if (couldaffect(e, z)) {
			return 1;
		}

		if (e->last) {
			return 0;
		}
	}

	return 0;
}

/*
 * Does e depend on z?
 */
static bool
dependson(exp e, bool isc, exp z)
{
	if (e == NULL) {
		return 0;
	}

	for (;;) {
		if (z->tag == reff_tag || z->tag == addptr_tag || z->tag == subptr_tag) {
			z = son(z);
		}

		if (z->tag != name_tag) {
			if (z->tag != cont_tag) {
				return 1;
			}

			z = 0;
			break;
		}

		if (isvar(son(z))) {
			break;
		}

		if (son(z)->tag == proc_tag) {
			z = 0;
			break;
		}

		if (son(son(z)) == NULL) {
			/* can it happen? */
			return 1;
		}

		z = son(son(z));
	}

	/* z is now unambiguous variable name or 0 (meaning some contents) */
	return isc ? couldbe(e, z) : couldaffect(e, z);
}

/*
 * Remove associations of any registers depending on lhs
 */
void
clear_dep_reg ( exp lhs )
{
	int i;

	for (i = 0; i < 48; i++) {
		if (regexps[i].keptexp == NULL) {
			continue;
		}

		switch(regexps[i].keptexp->tag) {
		case val_tag:
		case null_tag:
		case real_tag:
		case string_tag:
		case name_tag:
			if (!regexps[i].iscont) {
				/* constant value, cannot be changed by assign */
				continue;
			}

		default:
			if (!dependson(regexps[i].keptexp, regexps[i].iscont, lhs)) {
				continue;
			}

			regexps[i].keptexp = NULL;
			setregalt(regexps[i].inans, 0);

#ifdef DWARF2
			if (diag == DIAG_DWARF2) {
				dw_close_regassn(i);
			}
#endif
		}
	}
}

