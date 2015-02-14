/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/error.h>

#include <reader/basicread.h>

#include <construct/installglob.h>
#include <construct/messages_c.h>
#include <construct/aldefs.h>

#define max(x, y)	((x) > (y)) ? (x) : (y)


/* The alignment definitions form a set of simultaneous equations
   of the form

     a1 = f1(a1,a2 .. an)
     a2 = f2(a1,a2 ... an)
     ...

   The functions f1 f2 etc. are formed entirely from f_alignment,
   which takes a shape and delivers an alignment, and unite_sets.
   f_alignment provides constants. Since the representation of
   alignments must be a homomorphism of sets under unite_sets, and
   since any program contains a finite number of basic alignments,
   these equations can be solved by iterating unite_sets until
   no further change occurs. Unite_sets is represented here by max.
*/

/* PROCEDURES */

void
process_aldefs(void)
{
	aldef *my_aldef;
	int changed; /* records whether a change has been made */
	int complete;

	/* iterate max until no change */
	do {
		my_aldef = top_aldef;
		changed = 0;
		complete = 1;
		while (my_aldef != NULL) {
			switch (my_aldef->al.al_n) {
			case 1: break;
			case 2: {
				alignment a1;
				alignment a2;
				a2 = my_aldef->al.al_val.al_join.b;
				a1 = my_aldef->al.al_val.al_join.a;
				if (a1->al.al_n == 1 && a2->al.al_n == 1) {
					my_aldef->al.al_n = 1;
					my_aldef->al.al_val.al =
					    max(a1->al.al_val.al, a2->al.al_val.al);
					changed = 1;
				} else {
					complete = 0;
				}
				break;
			}
			case 3: {
				alignment a1;
				a1 = my_aldef->al.al_val.al_join.a;
				if (a1->al.al_n == 1) {
					my_aldef->al.al_n = 1;
					my_aldef->al.al_val.al = a1->al.al_val.al;
					changed = 1;
				} else {
					complete = 0;
				}
				break;
			}
			default:
				error(ERROR_INTERNAL, ILLEGAL_ALIGNMENT);
			}
			my_aldef = my_aldef->next_aldef;
		}
	} while (changed);

	if (!complete) {
		error(ERROR_INTERNAL, INCOMPLETE_ALIGNMENT_EQS);
	}
}
