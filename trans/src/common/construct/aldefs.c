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
 *  a1 = f1(a1,a2 .. an)
 *  a2 = f2(a1,a2 ... an)
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

		for (p = top_aldef; p != NULL; p = p->next_aldef) {
			switch (p->al.al_n) {
			case 1: break;

			case 2: {
				alignment a1;
				alignment a2;

				a2 = p->al.al_val.al_join.b;
				a1 = p->al.al_val.al_join.a;
				if (a1->al.al_n == 1 && a2->al.al_n == 1) {
					p->al.al_n = 1;
					p->al.al_val.al = MAX(a1->al.al_val.al, a2->al.al_val.al);
					changed  = true;
				} else {
					complete = false;
				}
				break;
			}

			case 3: {
				alignment a1;

				a1 = p->al.al_val.al_join.a;
				if (a1->al.al_n == 1) {
					p->al.al_n = 1;
					p->al.al_val.al = a1->al.al_val.al;
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

