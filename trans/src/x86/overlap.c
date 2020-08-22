/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>

#include <tdf/tag.h>

#include <construct/exp.h>

#include "localtypes.h"
#include "overlap.h"

/*
 * false if a value of shape sha at w1 cannot overlap with one at w2.
 * true if it does or might overlap.
 *
 * This is only used by move, so we can assume that w1 and w2 are addressable.
 */
int
might_overlap(shape sha, where w1, where w2)
{
	exp e1, e2;
	exp i1, i2;
	int off1, off2, sz;

	e1 = w1.where_exp;
	e2 = w2.where_exp;

	if (e1->tag != name_tag) {
		if (e2->tag == name_tag && iscaonly(child(e2))) {
			return 0;
		}

		return 1;
	}

	if (e2->tag != name_tag) {
		if (e1->tag == name_tag && iscaonly(child(e1))) {
			return 0;
		}

		return 1;
	}

	/* both are name_tags */
	i1 = child(e1);
	i2 = child(e2);
	if (isglob(i1)) {
		if (i1 != i2) {
			return 0;
		}

		sz = shape_size(sha);
		off1 = no(e1) + w1.where_off;
		off2 = no(e2) + w2.where_off;

		if (off1 <= off2 && (off1 + sz) > off2) {
			return 1;
		}

		if (off2 <= off1 && (off2 + sz) > off1) {
			return 1;
		}

		return 0;
	}

	if (isglob(i2)) {
		return 0;
	}

	/* both are local */
	if (ptno(i1) != ptno(i2)) {
		return 0;
	}

	sz = shape_size(sha);

	off1 = no(e1) + no(i1) + w1.where_off;
	off2 = no(e2) + no(i2) + w2.where_off;

	if (off1 <= off2 && (off1 + sz) > off2) {
		return 1;
	}

	if (off2 <= off1 && (off2 + sz) > off1) {
		return 1;
	}

	return 0;
}

