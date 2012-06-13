/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/error.h>

#include "config.h"

#include "installglob.h"
#include "exp.h"
#include "expmacs.h"
#include "tags.h"
#include "flags.h"
#include "refactor.h"
#include "refactor_id.h"
#include "const.h"
#include "shapemacs.h"
#include "glopt.h"
#include "optimise.h"

#include "refactor_ext.h"


/***********************************************************************
  refactor_ext examines the external definition e to see if it can be
  improved. It returns 1 if it makes a change, 0 otherwise.
 ***********************************************************************/

void
refactor_ext(exp e)
{
	exp def = son(e);

	/* if it is not used or there is no definition here, do nothing */
	if (no(e) == 0 || def == nilexp) {
		return;
	}

	if ((!PIC_code || brog(e)->dec_u.dec_val.dec_var == 0) && !isvar(e) &&
	    (name(def) == val_tag || name(def) == real_tag ||
	     name(def) == null_tag)) {
		while (pt(e) != nilexp) {
			/* substitute constants in */
			exp q = pt(e);
			if (bro(q) != nilexp) {
				/* can be nilexp for diags */
				exp d = copy(def);
				replace(q, d, nilexp);
				kill_exp(q, q);
			} else {
				pt(e) = pt(q);
			}
		}
		return;
	}

	return;
}

