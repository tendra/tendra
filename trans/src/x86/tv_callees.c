/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>

#include <local/exp.h>

#include <tdf/tag.h>

#include <reader/externs.h>

#include <construct/installglob.h>
#include <construct/install_fns.h>
#include <construct/exp.h>

#include <main/flags.h>

#include "tv_callees.h"

/*
 * Transforms caller arguments of general procs with variable callees,
 * to appear like a structure whose address is another callee.
 * This enables consistent coding without demanding a separate register
 * for caller argument addressing.
 * Also, record need for env_size.
 */
void
transform_var_callees(void)
{
	dec *d;

	for (d = top_def; d != NULL; d = d->next) {
		exp tag = d->exp;

		if (son(tag) != NULL && son(tag)->tag == general_proc_tag
		    && proc_has_vcallees(son(tag)))
		{
			shape pc_sh = f_pointer(f_callers_alignment(0));
			int param_offset = 0;
			exp gp_body = son(son(tag));
			exp newdec = getexp(sh(gp_body), NULL, 1, NULL, NULL, 0, 0, ident_tag);
			exp newlist = NULL;
			son(newdec) = getexp(pc_sh, NULL, 0, NULL, NULL, 0, 0, formal_callee_tag);

			while (gp_body->tag == ident_tag && isparam(gp_body)
			       && son(gp_body)->tag != formal_callee_tag)
			{
				exp arg_id = gp_body;
				exp oldlist = pt(arg_id);
				gp_body = bro(son(gp_body));

				while (oldlist != NULL) {
					exp this_n = oldlist;
					exp new_n = getexp(pc_sh, this_n, 1, newdec, newlist, 0, 0, name_tag);
					oldlist = pt(oldlist);
					newlist = new_n;
					no(newdec)++;

					if (isvar(arg_id)) {
						this_n->tag = reff_tag;
						son(this_n) = new_n;
						no(this_n) += param_offset;
					} else {
						exp r = getexp(f_pointer(f_alignment(sh(son(arg_id)))),
						               this_n, 1, new_n, NULL, 0, no(this_n) + param_offset, reff_tag);
						bro(new_n) = r;
						this_n->tag = cont_tag;
						son(this_n) = r;
					}

					pt(this_n) = NULL;
				}

				/* This may still be accessed by env_offset.
				 * We need to distinguish the special case. */
				arg_id->tag = 0;

				no(arg_id) = param_offset;
				bro(arg_id) = NULL;
				pt(arg_id) = NULL;
				param_offset = rounder(param_offset + shape_size(sh(son(arg_id))), param_align);
				retcell(son(arg_id));
				son(arg_id) = NULL;
			}

			{
				setparam (newdec);	/* not var */
				setcaonly(newdec);
				bro(son(newdec)) = gp_body;
				setfather(newdec, gp_body);
				gp_body = newdec;
			}

			son(son(tag)) = gp_body;
			setfather(son(tag), gp_body);
		}

		if (son(tag) != NULL &&
		    (son(tag)->tag == proc_tag || son(tag)->tag == general_proc_tag))
		{
			exp nlist = pt(tag);
			while (nlist != NULL) {
				if (nlist->tag == name_tag && nlist->last && bro(nlist) != NULL &&
				    bro(nlist)->tag == env_size_tag) {
					set_proc_needs_envsize(son(tag));
				}
				nlist = pt(nlist);
			}
		}
	}
}

