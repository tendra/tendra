/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>


#include <reader/externs.h>

#include <construct/installglob.h>
#include <construct/install_fns.h>
#include <construct/tags.h>
#include <construct/exp.h>

#include <main/flags.h>

#include "tv_callees.h"
#include "localexpmacs.h"

void transform_var_callees
(void)
				/* Transforms caller arguments of general
				   procs with variable callees, to appear
				   like a structure whose address is
				   another callee. This enables consistent
				   coding without demanding a separate
				   register for caller argument addressing.
					Also, record need for env_size.
				*/
{
  dec * my_def = top_def;
  while (my_def != (dec *)0) {
    exp tg = my_def -> dec_u.dec_val.dec_exp;
    if (son(tg)!= NULL && name(son(tg)) == general_proc_tag
		&& proc_has_vcallees(son(tg))) {
      shape pc_sh = f_pointer(f_callers_alignment(0));
      int param_offset = 0;
      exp gp_body = son(son(tg));
      exp newdec = getexp(sh(gp_body), NULL, 1, NULL, NULL, 0, 0, ident_tag);
      exp newlist = NULL;
      son(newdec) = getexp(pc_sh, NULL, 0, NULL, NULL, 0, 0, formal_callee_tag);

      while (name(gp_body) == ident_tag && isparam(gp_body)
		&& name(son(gp_body))!= formal_callee_tag) {
	exp arg_id = gp_body;
	exp oldlist = pt(arg_id);
	gp_body = bro(son(gp_body));
	while (oldlist != NULL) {
	  exp this_n = oldlist;
	  exp new_n = getexp(pc_sh, this_n, 1, newdec, newlist, 0, 0, name_tag);
	  oldlist = pt(oldlist);
	  newlist = new_n;
	  no(newdec) ++;
	  if (isvar(arg_id)) {
	    name(this_n) = reff_tag;
	    son(this_n) = new_n;
	    no(this_n) += param_offset;
	  }
	  else {
	    exp r = getexp(f_pointer(f_alignment(sh(son(arg_id)))),
		 this_n, 1, new_n, NULL, 0, no(this_n) +param_offset, reff_tag);
	    bro(new_n) = r;
	    name(this_n) = cont_tag;
	    son(this_n) = r;
	  }
	  pt(this_n) = NULL;
	}

	name(arg_id) = 0;	/* This may still be accessed by env_offset.
				   We need to distinguish the special case.
				*/
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
      son(son(tg)) = gp_body;
      setfather(son(tg),gp_body);
    }

    if (son(tg)!= NULL &&
	(name(son(tg)) == proc_tag || name(son(tg)) == general_proc_tag)) {
      exp nlist = pt(tg);
      while (nlist != NULL) {
	if (name(nlist) == name_tag && last(nlist) && bro(nlist)!= NULL &&
		name(bro(nlist)) == env_size_tag)
	  set_proc_needs_envsize(son(tg));
	nlist = pt(nlist);
      }
    }

    my_def = my_def -> def_next;
  }
  return;
}
