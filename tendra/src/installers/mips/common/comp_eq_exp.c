/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


/* a rather more complicated equivalence of expressions - allows sequences and
 *conditionals with tests which only jump to nearest conditional outlab;
 *initial call : comp_eq_exp(a,b,nilexp,nilexp)  */

#include "config.h"
#include "tags.h"
#include "expmacs.h"
#include "exptypes.h"
#include "shapemacs.h"
#include "common_types.h"
#include "exp.h"
#include "comp_eq_exp.h"

bool
comp_eq_explist(exp a, exp b, exp laba, exp labb)
{
	if (a==nilexp) return (b==nilexp);
	if (b==nilexp || !comp_eq_exp(a,b,laba,labb)) return 0;
	if (last(a)) return (last(b));
	if (last(b)) return 0;
	return comp_eq_explist(bro(a), bro(b), laba, labb);
}


bool
comp_eq_exp(exp a, exp b, exp laba, exp labb)
{
	if (name(a) != name(b) || !eq_shape(sh(a), sh(b))) return 0;
	if (name(a) == seq_tag) {
		return (comp_eq_explist(son(son(a)), son(son(b)), laba, labb) &&
				comp_eq_exp(bro(son(a)), bro(son(b)),laba,labb));
	}
	if (name(a) == cond_tag) {
		exp fa = son(a);
		exp fb = son(b);
	 	return (comp_eq_exp(fa,fb, bro(fa), bro(fb)) &&
				comp_eq_exp(bro(son(bro(fa))), bro(son(bro(fb))), laba, labb));
	}
	if (name(a)==test_tag) {
		return (pt(a)==laba && pt(b)==labb && props(a)==props(b) &&
				comp_eq_explist(son(a),son(b), laba, labb));
	}
	if (name(a)==name_tag) {
		return (son(a)==son(b) && no(a)==no(b));
	}
	
	return (is_a(name(a)) && no(a)==no(b) &&
			comp_eq_explist(son(a), son(b), laba, labb));
}
