/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/* 80x86/tv_callees.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: tv_callees.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1995/10/18  11:24:35  pwe
 * diag struct
 *
 * Revision 1.4  1995/10/16  17:45:55  pwe
 * frame alignments
 *
 * Revision 1.3  1995/08/30  16:06:57  pwe
 * prepare exception trapping
 *
 * Revision 1.2  1995/08/14  13:54:08  pwe
 * several corrections, tail calls and error jumps
 *
 * Revision 1.1  1995/08/04  08:29:50  pwe
 * 4.0 general procs implemented
 *
**********************************************************************/

#include "config.h"
#include "common_types.h"
#include "installglob.h"
#include "externs.h"
#include "flags.h"
#include "install_fns.h"
#include "tags.h"
#include "expmacs.h"
#include "exp.h"
#include "tv_callees.h"


void transform_var_callees
    PROTO_Z ()
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
  while (my_def != (dec *) 0) {
    exp tg = my_def -> dec_u.dec_val.dec_exp;
    if (son(tg) != nilexp && name(son(tg)) == general_proc_tag
		&& proc_has_vcallees(son(tg))) {
      shape pc_sh = f_pointer(f_callers_alignment(0));
      int param_offset = 0;
      exp gp_body = son(son(tg));
      exp newdec = getexp (sh(gp_body), nilexp, 1, nilexp, nilexp, 0, 0, ident_tag);
      exp newlist = nilexp;
      son(newdec) = getexp (pc_sh, nilexp, 0, nilexp, nilexp, 0, 0, formal_callee_tag);

      while (name(gp_body) == ident_tag && isparam(gp_body)
		&& name(son(gp_body)) != formal_callee_tag) {
	exp arg_id = gp_body;
	exp oldlist = pt(arg_id);
	gp_body = bro(son(gp_body));
	while (oldlist != nilexp) {
	  exp this_n = oldlist;
	  exp new_n = getexp (pc_sh, this_n, 1, newdec, newlist, 0, 0, name_tag);
	  oldlist = pt(oldlist);
	  newlist = new_n;
	  no(newdec) ++;
	  if (isvar(arg_id)) {
	    name(this_n) = reff_tag;
	    son(this_n) = new_n;
	    no(this_n) += param_offset;
	  }
	  else {
	    exp r = getexp (f_pointer(f_alignment(sh(son(arg_id)))),
		 this_n, 1, new_n, nilexp, 0, no(this_n)+param_offset, reff_tag);
	    bro(new_n) = r;
	    name(this_n) = cont_tag;
	    son(this_n) = r;
	  }
	  pt(this_n) = nilexp;
	}

	name(arg_id) = 0;	/* This may still be accessed by env_offset.
				   We need to distinguish the special case.
				*/
	no(arg_id) = param_offset;
	bro(arg_id) = nilexp;
	pt(arg_id) = nilexp;
        param_offset = rounder(param_offset + shape_size(sh(son(arg_id))), param_align);
	retcell(son(arg_id));
	son(arg_id) = nilexp;
      }
      {
	setparam (newdec);	/* not var */
	setcaonly (newdec);
	bro(son(newdec)) = gp_body;
	setfather(newdec, gp_body);
	gp_body = newdec;
      }
      son(son(tg)) = gp_body;
      setfather(son(tg),gp_body);
    }

    if (son(tg) != nilexp &&
	(name(son(tg)) == proc_tag || name(son(tg)) == general_proc_tag)) {
      exp nlist = pt(tg);
      while (nlist != nilexp) {
	if (name(nlist) == name_tag && last(nlist) && bro(nlist) != nilexp &&
		name(bro(nlist)) == env_size_tag)
	  set_proc_needs_envsize(son(tg));
	nlist = pt(nlist);
      }
    }

    my_def = my_def -> def_next;
  }
  return;
}
