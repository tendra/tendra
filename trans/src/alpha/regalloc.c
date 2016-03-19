/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * functions to allocate register and stack space for a proc.
 * The following changes are made to the ident tags:
 *
 * props(ident) contains inreg_bits or infreg_bits, no(ident)==0
 * => value is a t reg(chosen in make_code()).
 * props(ident) contains reg bits =>  no(ident) is sreg.
 * props(ident) is instore => no = displacement*64+SP.
 */

#include <stddef.h>

#include <local/ash.h>

#include <utility/max.h>

#include <tdf/tag.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>

#include "procrec.h"
#include "bitsmacs.h"
#include "regable.h"
#include "regmacs.h"
#include "frames.h"
#include "reg_defs.h"
#include "make_code.h"
#include "regalloc.h"

static spacereq zerospace;

static spacereq
maxspace(spacereq a, spacereq b)
{
	a.fixdump |= b.fixdump;
	a.fltdump |= b.fltdump;
	a.stack = MAX(a.stack, b.stack);

	return a;
}

static int spareparregs = 0;

/*
 * Delivers a spacereq which gives the local stack bit
 * requirement in the stack field and the s regs used as bit
 * positions in the fixdump, sdump and ddump fields for fixed
 * point, single and double floats respectively.
 *
 * e is a proc body . freefixed and freefloat are the number of
 * fixed and floating s regs available. These are initialised at
 * the outer level but may be reduced by usage in paralloc
 */
spacereq
regalloc(exp e, int freefixed, int freefloat, int stack)
{
	int n = e->tag;
	exp s = son(e);
	spacereq def;

	if (n == ident_tag) {
		int ffix   = freefixed;
		int ffloat = freefloat;
		int st = stack;
		int old_spareparregs = spareparregs;
		spacereq body;
		ash a;

		if (props(e) & defer_bit) {
			/* the tag declared is transparent to code production */
			def = zerospace;
		} else {
			a = ashof(sh(s));

			if (s->tag != compound_tag && s->tag != nof_tag
			    && s->tag != concatnof_tag ) {
				def = regalloc(s, freefixed, freefloat, stack);
			} else  {
				/*elements of tuples are done separately so evaluate above dec*/
				if (a.ashalign <= 64 || (stack & 0x40) == 0) {
					st = stack + ((a.ashsize + 63) & ~63);
				} else {
					st = stack + 64 + ((a.ashsize + 63) & ~63);
				}
				def = regalloc(s, freefixed, freefloat, st);
			}

			if ((props(e) & inreg_bits) == 0 && fixregable(e) && no(e) < ffix) {
				/* suitable for s reg , no(e) has been set
				   up by weights */
				props(e) |= (inreg_bits | sreguse);
				no(e) = ffix + 8; /* will be in s reg , note s0 = $9 */
				def.fixdump |= (1 << (no(e) - FIRST_S_REG)/*ffix*/);
				ffix -= 1;
				/* def.fixdump |= (1 << no(e)); */
			} else if ((props(e) & infreg_bits) == 0
			           && floatregable(e) && no(e) < ffloat) {
				/* suitable for float s reg , no(e) has been set up by weights */
				props(e) |= (infreg_bits | sreguse);
				no(e) = ffloat + 1;	/* will be in s reg,note start from $f9*/
				def.fltdump |= (1 << ffloat);
				ffloat -= 1;
				/* have another look at this */
			} else if ((props(e) & inanyreg) == 0) {
				if (fixregable(e) && PossParReg(e) && spareparregs > 0) {
					props(e) |= inreg_bits;
					no(e) = NO_REG;
					spareparregs--;
				}
				/* not suitable for reg allocation */
				else if (son(e)->tag == val_tag && !isvar(e) && !isvis(e)) {
					exp t = pt(e);
					for ( ; t != NULL;) {
						exp p = pt(t);
						t->tag = val_tag;
						son(t) = NULL;
						no(t) = no(son(e));
						props(t) = 0;
						pt(t) = NULL;
						t = p;
					}
					pt(e) = NULL;
					props(e) |= defer_bit;
					def = zerospace;
				} else if (son(e)->tag == name_tag && !isvar(e) && !isvis(e)) {
					/* must have been forced  - defer it */
					props(e) |= defer_bit;
					def = zerospace;
				} else if (isparam(e)) {
					if (props(son(e)) != 0) {
						spareparregs++;
					}
					no(e) = 0;
					/* don't know framesize yet;
					 displacement in no(son(e)) */
				} else {		/* allocate on stack */
					int basereg = Has_vcallees ? local_reg : (Has_fp ? FP : SP);
					if (a.ashalign <= 64 || (stack & 0x40) == 0) {
						st = stack + ((a.ashsize + 63) & ~63);
					} else {
						stack += 64;
						st = stack + ((a.ashsize + 63) & ~63);
					}
					def.stack = MAX(def.stack, st);
					no(e) = stack * 2 + basereg;
				}
			} else if (no(e) == 101) {
				/*
				 * Use the result register (the result register has the
				 * same number for both floating and fixed point results.
				 */
				no(e) = RESULT_REG;
			}
			/* else  allocation of stack like regs in make_code */
		}

		body = regalloc(bro(s), ffix, ffloat, st);
		spareparregs = old_spareparregs;
		return maxspace (body, def);
	} else if (n == case_tag) {
		/* recurse on all expressions in tree */
		return regalloc (s, freefixed, freefloat, stack);
	} else if (n != name_tag && n != env_offset_tag && n != general_env_offset_tag && s != NULL) {
		def = regalloc(s, freefixed, freefloat, stack);
		while (!s->last) {
			s = bro(s);
			def = maxspace(def, regalloc(s, freefixed, freefloat, stack));
		}
		return def;
	} else {
		def = zerospace;
		def.stack = stack;
		return def;
	}
}

