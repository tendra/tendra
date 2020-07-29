/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <local/tag.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>

#include <construct/aldefs.h>

#include <flpt/flpt.h>

#include "addr.h"
#include "move.h"
#include "bits.h"
#include "reg_defs.h"
#include "regexps.h"

regpeep regexps[64];

static bool
eq_size(shape as, shape bs)
{
	return shape_size(as) == shape_size(bs);
}

static bool sim_exp(exp a, exp b);

bool
eq_sze(shape as, shape bs)
{
	if (is_floating(as->tag)) {
		return as->tag == bs->tag;
	}

	if (is_floating(bs->tag)) {
		return 0;
	}

	return shape_size(as) == shape_size(bs) && shape_align(as) == shape_align(bs);
}

#define is_volatile(X)((X<9) || (X>15))

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
 * basically eq_exp except equal shapes requirement
 * is weakened to equal sizes and alignments
 */
static bool
sim_exp(exp a, exp b)
{
	if (a->tag != b->tag) {
		return 0;
	}

	if (a->tag == name_tag) {
		return son(a) == son(b) && no(a) == no(b) &&
		       eq_sze(sh(a), sh(b));
	}

	if (a->tag == maxlike_tag || a->tag == minlike_tag || a->tag == abslike_tag) {
		return(props(son(a)) == props(son(b)) && eq_size(sh(a), sh(b)) &&
		       sim_explist(son(son(a)), son(son(b))));
	}

	if (!is_a(a->tag) || !eq_sze(sh(a), sh(b))) {
		return 0;
	}

	return no(a) == no(b) && sim_explist(son(a), son(b));
}

/* forget all register - exp associations */
void
clear_all(void)
{
	int i;

	for (i = 0; i < 64; i++) {
		/* if (is_volatile(i)) { */
		regexps[i].keptexp = NULL;
		regexps[i].alignment = 0;
		setregalt(regexps[i].inans, NO_REG);
		/* } */
	}
}

/* forget reg i - exp association */
void
clear_reg(int i)
{
	i = abs(i);
	if (i >= 0 && i < 64) {
		regexps[i].keptexp = NULL;
		regexps[i].alignment = 0;
		setregalt(regexps[i].inans, NO_REG);
	}
}

void
clear_freg(int i)
{
	i = abs(i) + 32;
	if (i < 64) {
		regexps[i].keptexp = NULL;
		setregalt(regexps[i].inans, NO_REG); /* ?? */
	}
}

/* find if e has already been evaluated into a register */
ans
iskept(exp e)
{
	int i;
	ans nilans;
	ans aa;
	setregalt(nilans, 32);
	aa = nilans;

	for (i = 0; i < 48; i++) {
		exp ke   = regexps[i].keptexp;
		bool isc = regexps[i].iscont;

		if (ke == NULL) {
			/* there isn't an accociation with reg i */
			continue;
		}

		if (((!isc && sim_exp(ke, e)) ||
		     (e->tag == cont_tag && isc && eq_sze(sh(ke), sh(e))
		      && sim_exp(ke, son(e))))
		) {
			aa = (regexps[i].inans);
			switch (aa.discrim) {
			case notinreg:
				if (!aa.val.instoreans.adval) {
					/* the expression is given indirectly - it
					may have also been loaded into a
					 register */
					continue;
				}
				/* else ... */
				FALL_THROUGH;

			default:
				return aa;
			}
		} else if (ke->tag == cont_tag && !isc) {
			ans aq;
			aq = regexps[i].inans;
			if (aq.discrim == notinreg) {
				instore is;
				is = insalt(aq);
				if (!is.adval && is.b.offset == 0 && is.b.base > 0 && is.b.base < 31
				    && sim_exp(son(ke), e)) {
					/* the contents of req expression is here
					as a reg-offset */
					is.adval = 1;
					setinsalt(aq, is);
					return aq;
				}
			}
		} else if (ke->tag == reff_tag && !isc) {
			ans aq;
			aq = regexps[i].inans;
			if (aq.discrim == notinreg) {
				instore is;
				is = insalt(aq);
				if (is.adval && is.b.offset == (no(ke) / 8)
				    && is.b.base > 0 && is.b.base < 31
				    && sim_exp(son(ke), e)) {
					/* a ref select of req expression is here
					   as a reg-offset */
					is.adval = 1;
					is.b.offset = 0;
					setinsalt(aq, is);
					return aq;
				}
			}
		}
	}

	return aa;
}

void
keepexp(exp e, ans loc)
{
	/* set up exp - address association */
	int pos;

	switch (loc.discrim) {
	case insomereg:
	case insomefreg:
		error(ERR_INTERNAL, "Keep ? reg");
		return;

	case inreg:
		pos = regalt(loc);
		break;

	case infreg:
		pos = fregalt(loc).fr + 32;
		break;

	case notinreg:
		pos = insalt(loc).b.base;
		if (pos < 0 || pos > 30) {
			return;
		}
	}

	if (pos == 0 || pos == 32) {
		return;
	}

	regexps[pos].keptexp = e;
	regexps[pos].inans   = loc;
	regexps[pos].iscont  = 0;
}

/* set up cont(e)-reg association */
void
keepcont(exp e, int reg)
{
	freg fr;
	int z;

	z = abs(reg);

	/*  if (z==2|| z==32) return;*/
	if (z > 31) {
		if (reg < 0) {
			fr.type = IEEE_double;
		} else {
			fr.type = IEEE_single;
		}
		fr.fr = z - 32;
		setfregalt(regexps[z].inans, fr);
	} else {
		instore is;
		is.b.base   = reg;
		is.b.offset = 0;
		is.adval = 1;
		setinsalt(regexps[z].inans, is);
	}

	regexps[z].keptexp = e;
	regexps[z].iscont  = 1;
}

/* set up e-reg association */
void
keepreg(exp e, int reg)
{
	freg fr;
	int z;

	z = abs(reg);
	if (z == 0) {
		return;
	}

	/*  if (z==2 || z==32) return;*/
	if (z > 31) {
		if (reg < 0) {
			fr.type = IEEE_double;
		} else {
			fr.type = IEEE_single;
		}
		fr.fr = z - 32;
		setfregalt(regexps[z].inans, fr);
	} else {
		instore is;
		is.b.base   = reg;
		is.b.offset = 0;
		is.adval = 1;
		setinsalt(regexps[z].inans, is);
	}

	regexps[z].keptexp = e;
	regexps[z].iscont  = 0;
}

static bool couldaffect(exp e, exp z);

/* could e be lhs? */
static bool
couldbe(exp e, exp lhs)
{
	int ne = e->tag;
	exp s = son(e);

	if (ne == name_tag) {
		if (lhs != 0 && s == son(lhs)) {
			return 1;
		}

		if (isvar(s)) {
			return lhs == 0 && isvis(s);
			/*
			return lhs == 0 && (isvis (s) || isglob(s));*/
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
			return son(s) == son(lhs) || isvis(son(lhs)) || isvis(son(s));
		}

		return 1;
	}

	if (ne == reff_tag || ne == field_tag) {
		return couldbe(s, lhs);
	}

	if (ne == addptr_tag || ne == subptr_tag) {
		return couldbe(s, lhs) || couldaffect(bro(s), lhs);
	}

	return 1;
}

/* could alteration to z affect e? */
static bool
couldaffect(exp e, exp z)
{
	int ne;

	ne = e->tag;
	if (ne == cont_tag) {
		return couldbe(son(e), z);
	}

	if (ne == name_tag) {
		if (isvar(son(e))) {
			return z == 0 && isvis(son(e));
		}

		if (son(e)->tag == proc_tag) {
			return 0;
		}

		if (son(son(e)) == NULL) {
			return 1 /* could it happen? */ ;
		}

		return couldaffect(son(son(e)), z);
	}

	if (ne < plus_tag || ne == contvol_tag) {
		return 1;
	}

	e = son(e);

	while (e != NULL) {
		if (couldaffect(e, z)) {
			return 1;
		}

		if (e->last) {
			return 0;
		}

		e = bro(e);
	}

	return 0;
}

/* does e depend on z */
bool
dependson(exp e, bool isc, exp z)
{
	if (e == NULL) {
		return 0;
	}

	for (;;) {
		if (z->tag == reff_tag || z->tag == addptr_tag ||
		    z->tag == subptr_tag) {
			z = son(z);
			if (z->tag == null_tag) {
				return 0;
			}
		} else if (z->tag != name_tag) {
			if (z->tag != cont_tag) {
				return 1;
			}
			z = 0;
			break;
		}

		if (z->tag == current_env_tag) {
			return 0;
		}

		if (isvar(son(z))) {
			break;
		}

		if (son(z)->tag == proc_tag) {
			z = 0;
			break;
		}

		if (son(son(z)) == NULL) {
			return 1;    /* can it happen? */
		}

		z = son(son(z));
	}

	/* z is now unambiguous variable name or 0 meaning some contents */

	return isc ? couldbe(e, z) : couldaffect(e, z);
}

/* remove association of any register which depends on lhs */
void
clear_dep_reg(exp lhs)
{
	int i;

	for (i = 0; i < 64; i++) {
		if (dependson(regexps[i].keptexp, regexps[i].iscont, lhs)) {
			regexps[i].keptexp = NULL;
			setregalt(regexps[i].inans, NO_REG);
		}
	}
}

