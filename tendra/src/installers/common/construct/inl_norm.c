/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
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

/* normalised_inlining chooses the order in which inlining is to be
 *   done.
 */

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
#include "xalloc.h"
#ifdef NEWDIAGS
#include "dg_aux.h"
#endif
#include "inl_norm.h"


int print_inlines = 0;

/* Procedures */

/*********************************************************************
 *  test a declaration to see that the identifier is only used as an
 *  applied procedure.
 *********************************************************************/


int
apply_only(exp e)
{
	exp t = pt (e);
	int ao = 1;
	exp f;
	while (ao && t != nilexp) {
#ifdef NEWDIAGS
		if (isdiaginfo(t))
			t = pt (t);
		else {
			f = father(t);
			if (name (f) == apply_tag && son(f) == t)
				t = pt (t);
			else
				ao = 0;
		};
#else
		f = father(t);
		if (name (f) == apply_tag && son(f) == t)
			t = pt (t);
		else
			ao = 0;
#endif
	};
	return (ao);
}


void
normalised_inlining()
{
	int proc_count = 0;
	dec * my_def;
	dec ** to_dec;
	exp def;
	int i;
	int j;
	char * consider;
	int * order;
	char * uses;
	int changed;
	int low;
	int high;
	int no_inlined =0;
	
	if (!do_inlining)
		return;
	
	/* count the defined procedures */
	
	my_def = top_def;
	while (my_def != (dec *) 0) {
		exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
		
		def = son(crt_exp);
		if (def != nilexp && !isvar (crt_exp) && name (def) == proc_tag &&
			!isrecursive(def) && apply_only (crt_exp) && !proc_has_setjmp(def) &&
			!proc_uses_crt_env(def) &&
			!proc_has_alloca(def) &&
			!proc_has_lv(def)) {
			proc_count++;
		}
		my_def = my_def -> def_next;
	}
	
	/* allocate
	 *     a matrix, uses, to hold uses[i, j] - i calls j
	 *     a vector, to_dec, to hold dec* (number -> dec)
	 *     a vector, consider, 1 if still considering.
	 *     a vector, order, of the procedure numbers (+1) ordered
	 */
	
	uses = (char*)xcalloc(proc_count * proc_count, sizeof(char));
	to_dec = (dec**)xcalloc(proc_count, sizeof(dec*));
	consider = (char*)xcalloc(proc_count, sizeof(char));
    /* assumes calloc clears consider */
	order = (int*)xcalloc(proc_count, sizeof(int));
    /* assumes calloc clears order */
	
	
	/* form the to_dec vector and set index in each proc dec.
	 *     set consider vector */
	
	my_def = top_def;
	i = 0;
	while (my_def != (dec *) 0) {
		exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
		
		def = son(crt_exp);
		if (def != nilexp && !isvar (crt_exp) && name (def) == proc_tag &&
			!isrecursive(def) && apply_only (crt_exp) && !proc_has_setjmp(def) &&
			!proc_uses_crt_env(def) &&
			!proc_has_alloca(def) &&
			!proc_has_lv(def)) {
			to_dec[i] = my_def;
			my_def -> dec_u.dec_val.index = i;
			consider[i] = 1;
			i++;
		}
		my_def = my_def -> def_next;
	}
	
	/* form uses matrix: uses[i, j] implies i calls j */
	
	for (i = 0; i < proc_count; i++) {
		exp crt_exp = to_dec[i] -> dec_u.dec_val.dec_exp;
		
		if (no(crt_exp) == 0 || son(crt_exp) == nilexp) {
			consider[i] = 0;
		}
		else {
			exp t = pt(crt_exp);
			
			while (t != nilexp) {
				exp k = t;
#ifdef NEWDIAGS
				if (isdiaginfo(t)) {
					t = pt (t);
					continue;
				}
#endif
				while (k != nilexp && name(k) != hold_tag && name(k) != 102
					   && name(k) != proc_tag && name(k) != general_proc_tag)
					k = bro(k);
				if (k != nilexp && name(k) == proc_tag) {
					int up = brog(bro(k)) -> dec_u.dec_val.index;
					if (up >=0 && up< proc_count) {
						uses[proc_count *up + i] = 1;
					}
				}
				t = pt(t);
			}
		}
	}
	
	/* form the order list from uses */
	
	low = 0;
	high = proc_count-1;
	changed = 1;
	while (changed) {
		changed = 0;
		
		for (i = 0; i < proc_count; i++) {
			if (consider[i]) {
				int good = 1;
				for (j = 0; good && j < proc_count; j++) {
					if (consider[j] && uses[i*proc_count+j] == 1)
						good = 0;
				}
				if (good) {
					consider[i] = 0;
					order[low++] = i+1;
					changed = 1;
				}
			}
		}
		
		for (i = 0; i < proc_count; i++) {
			if (consider[i]) {
				int good = 1;
				for (j = 0; good && j < proc_count; j++) {
					if (consider[j] && uses[j*proc_count+i] == 1)
						good = 0;
				}
				if (good) {
					consider[i] = 0;
					order[high--] = i+1;
					changed = 1;
				}
			}
		}
	}
	
	/* permit inlining of static recursive functions */
	
	for (i = 0; i < proc_count; i++) {
		if (consider[i]) {
			order[low++] = i+1;
		}
	}
	
	/* try to inline in given order */
	
	for (i = proc_count-1; i >= 0; i--) {
		if (order[i] > 0) {
			exp crt_exp;
			exp t;
			exp k;
			int total_uses;
			int crt_uses;
			int this_changed = 1;
			my_def = to_dec[order[i] - 1];
			crt_exp = my_def -> dec_u.dec_val.dec_exp;
			def = son(crt_exp);
			total_uses = no(crt_exp);
#ifdef NEWDIAGS
			if (diagnose)
				start_diag_inlining (def, my_def->dec_u.dec_val.diag_info);
#endif
			
			while (this_changed) {
				this_changed = 0;
				t = pt(crt_exp);
				crt_uses = no(crt_exp);
				while (t!=nilexp) {
					exp nextt = pt(t);
					exp dad;
#ifdef NEWDIAGS
					if (isdiaginfo(t)) {
						t = pt (t);
						continue;
					}
#endif
					dad = father(t);
					if (istoinline(dad)) {
						inline_exp(dad);
						
						k = t;
						while (k != nilexp && name(k) != hold_tag && name(k) != proc_tag)
							k = bro(k);
						if (print_inlines)
							IGNORE fprintf(stderr, "%s inlined in %s\n",
										   my_def -> dec_u.dec_val.dec_id,
										   brog(bro(k)) -> dec_u.dec_val.dec_id);
						
						this_changed = 1;
						break;
					}
					else
						if (no_inlined > 10000) {
							break; /* pathological expansion in AVS */
						}
						else {
							int ch = inlinechoice(t, def, total_uses);
							if (ch == 0)
								break;
							if (ch == 2) {
								inline_exp(dad);
								no_inlined++;
								
								k = t;
								while (k != nilexp && name(k) != hold_tag && name(k) != proc_tag)
									k = bro(k);
								if (print_inlines)
									IGNORE fprintf(stderr, "%s inlined in %s\n",
												   my_def -> dec_u.dec_val.dec_id,
												   brog(bro(k)) -> dec_u.dec_val.dec_id);
								
								this_changed = 1;
								break;
							}
						};
					t = nextt;
				}
				if (crt_uses <= no(crt_exp))
					break;
			}
#ifdef NEWDIAGS
			if (diagnose)
				end_diag_inlining (def, my_def->dec_u.dec_val.diag_info);
#endif
		}
	}
	
	xfree((void*)to_dec);
	xfree((void*)uses);
	xfree((void*)consider);
	xfree((void*)order);
	
	return;
}
