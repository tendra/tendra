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
#include "expmacs.h"
#include "tags.h"
#include "label_ops.h"
#include "check.h"
#include "externs.h"
#include "exp.h"
#include "installglob.h"
#include "shapemacs.h"


/* label_is_next returns 1 if lab is a labst which immediately
 *   follows e, otherwise 0. e will not be nilexp
 */
int
label_is_next(exp lab, exp e)
{
	if (!indirect_jumps)
		return 0;
	while (last(e)) {
		e = bro(e);
		if (e == nilexp || name(e) >= ass_tag || name(sh(e)) != bothd)
			return 0;
	};
	if (name(bro(e)) == labst_tag)
		return bro(e) == lab;
	return 0;
}

static exp
is_jumper(exp e)
{
	if (name(e) == test_tag || name(e) == goto_tag ||
		name(e) == testbit_tag || name(e) == res_tag)
		return e;
	return nilexp;
}

static exp
down(exp e)
{
	if (name(e) == seq_tag)
		return down(son(son(e)));
	if (name(e) == cond_tag)
		return down(son(e));
	return e;
}

/* next_jump delivers a goto, res, test or testbit exp if this
 *   is certain to be the next thing obeyed after e. nilexp
 *   otherwise.
 */
static exp
next_jump(exp e)
{
	if (!indirect_jumps)
		return nilexp;
	
	do {
		while (last(e)) {
			e = bro(e);
			if (e == nilexp || name(e) >= goto_tag)
				return nilexp;
		};
		e = bro(e);
	} while (name(e) == labst_tag && (e = father(e), name(e)!=rep_tag));
	
	if (is_jumper(e))
		return e;
	if (name(e) == seq_tag || name(e) == cond_tag)
		return is_jumper(down(e));
	if (name(e) == top_tag)
		return next_jump(e);
	return nilexp;
}

/* next_jump delivers a goto, res, test or testbit exp if this
 *   is certain to be the next thing obeyed after e and there is no
 *   other route to the goto (etc.). nilexp otherwise.
 */
exp
short_next_jump(exp e)
{
	if (!indirect_jumps)
		return nilexp;
	
    while (last(e)) {
		e = bro(e);
		if (e == nilexp || name(e) >= cond_tag)
			return nilexp;
    };
    e = bro(e);
	
	if (is_jumper(e))
		return e;
	if (name(e) == seq_tag || name(e) == cond_tag)
		return is_jumper(down(e));
	if (name(e) == top_tag)
		return short_next_jump(e);
	return nilexp;
}

exp
jump_dest(exp lab)
{
	return next_jump(son(lab));
}

exp
final_dest(exp lab)
{
	exp final = lab;
	exp temp, ll;
	while (name(final) == labst_tag) {
		temp = jump_dest(final);
		if (temp != nilexp && name(temp) == goto_tag && pt(temp) != final) {
			ll = lab;
			while (ll != final) {
				if (pt(temp) == ll)
					return final;		/* pathological loop */
				ll = pt(jump_dest(ll));
			}
			final = pt(temp);
		}
		else
			break;
	};
	return final;
}

/* delivers 1 iff when a jumps, b also jumps
 *   a and b will be test or testbit
 */
static int
subsumes(exp a, exp b)
{
	if (name(a) == name(b) &&
		test_number(a) == test_number(b) &&
		eq_exp(son(a), son(b)) &&
		eq_exp(bro(son(a)), bro(son(b))))
		return 1;
	return 0;
}

exp
final_dest_test(exp lab, exp e)
{
	exp final = lab;
	exp temp, ll;
	while (name(final) == labst_tag) {
		temp = jump_dest(final);
		if (temp == nilexp || final == pt(temp))
			return final;
		if (name(temp) == goto_tag || (name(temp) == name(e) && subsumes(e, temp))) {
			ll = lab;
			while (ll != final) {
				if (pt(temp) == ll)
					return final;		/* pathological loop */
				ll = pt(jump_dest(ll));
			}
			final = pt(temp);
		}
		else
			break;
	};
	return final;
}

