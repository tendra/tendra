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


/*
 *  Define special_fn which recognises and replaces some special
 *  function calls.
 */

#include "config.h"
#include "common_types.h"
#include "tags.h"
#include "externs.h"
#include "expmacs.h"
#include "shapemacs.h"
#include "exp.h"
#include "basicread.h"
#include "flags.h"
#include "table_fns.h"
#include "installglob.h"
#include "check.h"
#include "localflags.h"
#include "me_fns.h"
#include "spec.h"


/* PROCEDURES */

speci
special_fn(exp a1, exp a2, shape s)
{
	/* look for special functions */
	speci spr;
	dec* dp = brog (son (a1));
	char *id = dp -> dec_u.dec_val.dec_id;
	spr.is_special = 0;
	if (id == (char *) 0)
		return (spr);
	id += prefix_length;

	if (a2 != nilexp && last(a2) && !strcmp (id, "__trans386_special")) {
		exp r = me_b3(s, a1, a2, apply_tag);
		setbuiltin(r);	/* dummy proc, so ignore state of do_special_fns */
		spr.is_special = 1;
		spr.special_exp = r;
		return (spr);
	};

	if (!strcmp (id, "setjmp")) {
		has_setjmp = 1;
		module_has_setjmp = 1;
	};

	if (!strcmp (id, "longjmp")) {
		exp r = getexp(f_bottom, nilexp, 0, a1, nilexp, 0, 0,apply_tag);
		has_setjmp = 1;
		if (last(a2) || bro(a2) == nilexp)
			return spr;
		bro(a1) = a2;
		clearlast(a1);
		parked(a2) = 0;
		clearlast(a2);
		a2 = bro(a2);
		setlast(a2);
		parked(a2) = 0;
		bro(a2) = r;
		spr.is_special = 1;
		spr.special_exp = r;
	};

	/* we must always set has_setjmp if it is longjmp,
	 *        otherwise registers are not reset.
	 *        so don't do do_special_fns test until after longjmp test. */
	if (!do_special_fns)
		return spr;

	if (a2 != nilexp && last(a2) && !strcmp (id, "__builtin_alloca")) {
		exp r = getexp (s, nilexp, 0, a2, nilexp, 0,
						0, alloca_tag);
		setfather(r, son(r));
		has_alloca = 1;
		spr.is_special = 1;
		spr.special_exp = r;
		kill_exp (a1, a1);
		return (spr);
	};

	if (a2 != nilexp && last(a2) && !strcmp (id, "exit")) {
		exp r = me_b3(f_bottom, a1, a2, apply_tag);
		spr.is_special = 1;
		spr.special_exp = r;
		return (spr);
	};

	if (a2 == nilexp && !strcmp (id, "abort")) {
		exp r = me_u3(f_bottom, a1, apply_tag);
		spr.is_special = 1;
		spr.special_exp = r;
		return (spr);
	};

	return (spr);
}
