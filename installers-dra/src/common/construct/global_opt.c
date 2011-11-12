/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:47 $
$Revision: 1.1.1.1 $
$Log: global_opt.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1995/09/27  12:39:23  currie
 * Peters PIC code
 *
 * Revision 1.3  1995/09/19  11:51:45  currie
 * Changed name of init fn +gcc static bug
 *
 * Revision 1.2  1995/06/09  08:37:40  currie
 * loose name tag with diags
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/

#include <stddef.h>

#include "config.h"
#include "installglob.h"
#include "exp.h"
#include "expmacs.h"
#include "tags.h"
#include "check.h"
#include "flags.h"
#include "check_id.h"
#include "const.h"
#include "foralls.h"
#include "shapemacs.h"
#include "glopt.h"
#include "inline.h"
#include "global_opt.h"
#include "inl_norm.h"
#include "unroll.h"


/* PROCEDURES */


/***********************************************************************
  checkext examines the external definition e to see if it can be
  improved. It returns 1 if it makes a change, 0 otherwise.
 ***********************************************************************/

void
rec_inl(exp p)
{
	if (pt(p) != nilexp) {
		rec_inl(pt(p));
	}

	inline_exp(father(p));
	return;
}


void
checkext(exp e)
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


void
opt_all_exps(void)
{
	dec *my_def;

#if 0
	/* take constant expression out of loops */
	if (do_loopconsts)
		repeat_consts();
#endif

	if (do_unroll) {
		unroller();
	}

	my_def = top_def;
	while (my_def != (dec *)0) {
		exp crt_exp = my_def->dec_u.dec_val.dec_exp;
		checkext(crt_exp);
		glopt(my_def);
		my_def = my_def -> def_next;
	}

	normalised_inlining();

#if 1
	/* take constant expression out of loops */
	if (do_loopconsts) {
		repeat_consts();
	}
#endif

	/* replace indexing on loop variable by incremented pointer access */
	if (do_foralls) {
		forall_opt();
	}

	return;
}
