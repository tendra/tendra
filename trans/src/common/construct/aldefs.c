/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/error.h>

#include <utility/max.h>

#include <reader/basicread.h>

#include <construct/installglob.h>
#include <construct/aldefs.h>

/*
 * The alignment definitions form a set of simultaneous equations
 * of the form
 *
 *  a_1 = f1(a_1, a_2 ... a_n)
 *  a_2 = f2(a_1, a_2 ... a_n)
 *  ...
 *
 * The functions f1 f2 etc. are formed entirely from f_alignment,
 * which takes a shape and delivers an alignment, and unite_sets.
 * f_alignment provides constants. Since the representation of
 * alignments must be a homomorphism of sets under unite_sets, and
 * since any program contains a finite number of basic alignments,
 * these equations can be solved by iterating unite_sets until
 * no further change occurs. Unite_sets is represented here by max.
 */

void
process_aldefs(void)
{
	aldef *p;
	bool changed;
	bool complete;

	/* iterate max until no change */
	do {
		changed  = false;
		complete = true;

		for (p = top_aldef; p != NULL; p = p->next) {
			switch (p->al.state) {
			case ALDEF_VAL: break;

			case ALDEF_JOINAB: {
				alignment a;
				alignment b;

				a = p->al.u.join.a;
				b = p->al.u.join.b;
				if (a->al.state == ALDEF_VAL && b->al.state == ALDEF_VAL) {
					p->al.state = ALDEF_VAL;
					p->al.u.val = MAX(a->al.u.val, b->al.u.val);
					changed  = true;
				} else {
					complete = false;
				}
				break;
			}

			case ALDEF_JOINA: {
				alignment a;

				a = p->al.u.join.a;
				if (a->al.state == ALDEF_VAL) {
					p->al.state = ALDEF_VAL;
					p->al.u.val = a->al.u.val;
					changed  = true;
				} else {
					complete = false;
				}
				break;
			}

			default:
				error(ERR_INTERNAL, "illegal alignment");
			}
		}
	} while (changed);

	if (!complete) {
		error(ERR_INTERNAL, "incomplete alignment equations");
	}
}

