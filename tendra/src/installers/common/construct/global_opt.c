/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/




#include "config.h"
#include "common_types.h"
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
 *  checkext examines the external definition e to see if it can be
 *  improved. It returns 1 if it makes a change, 0 otherwise.
 ***********************************************************************/

void
rec_inl(exp p)
{
	if (pt(p) != nilexp)
		rec_inl(pt(p));
	
	inline_exp (father (p));
	return;
}

void
checkext(exp e)
{
	exp def = son (e);
	
	if (no (e) == 0 || def == nilexp)
		return;			/* if it is not used or there is no
						 *				   definition here, do nothing */
	
	if ((!PIC_code || brog(e)->dec_u.dec_val.dec_var == 0) && !isvar (e) &&
		(name (def) == val_tag || name (def) == real_tag
		 || name(def) == null_tag)) {
		while (pt (e) != nilexp) {
			/* substitute constants in */
			exp q = pt (e);
			if (bro(q) != nilexp) {/* can be nilexp for diags */
				exp d = copy (def);
				replace (q, d, nilexp);
				kill_exp (q, q);
			}
			else pt(e) = pt(q);
		}
		return;
	};
	
	return;
}


void
opt_all_exps()
{
	dec * my_def;
	
#if 0
	/* take constant expression out of loops */
	if (do_loopconsts)
		repeat_consts ();
#endif
	
	if (do_unroll)
		unroller();
	
	my_def = top_def;
	while (my_def != (dec *) 0) {
		exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
		checkext (crt_exp);
		glopt(my_def);
		my_def = my_def -> def_next;
	};
	
	normalised_inlining();
	
#if 1
	/* take constant expression out of loops */
	if (do_loopconsts)
		repeat_consts ();
#endif
	
	/* replace indexing on loop variable by incremented pointer access */
	if (do_foralls)
		forall_opt ();
	
	
	
	return;
}
