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
#include "glopt.h"


/* PROCEDURES */

void
glopt(dec * dp)
{
	if (!writable_strings && !strcmp(dp -> dec_u.dec_val.dec_id, "strcpy"))
	{
		exp i = dp -> dec_u.dec_val.dec_exp;
		exp t = pt(i);
		if (t == nilexp)
			return;

		while (1)
		{
			if (!last(t) && !last(bro(t)) && last(bro(bro(t))) &&
				name(bro(bro(bro(t)))) == apply_tag &&
				son(bro(bro(bro(t)))) == t)
			{
				exp dest = bro(t);
				exp source = bro(dest);

				if (name(source) == name_tag && isglob(son(source)) &&
					isvar(son(source)) && no(son(source)) == 1)
				{
					dec * source_dec = brog(son(source));
					if (!source_dec -> dec_u.dec_val.extnamed &&
						son(source_dec -> dec_u.dec_val.dec_exp) != nilexp)
					{
						exp source_def = son(son(source));
						shape sha = sh(source_def);
						if (name(source_def) == string_tag &&
							props(source_def) == 8)
						{
							char * s = nostr(source_def);
							int j;
							int l = shape_size(sha) / 8;
							for (j=0; j < l && s[j] != 0; ++j);
							if (j < l)
							{
								exp q;
								exp to_change = bro(source);
								exp idsc = getexp(sh(bro(source)), nilexp, 0,
												  dest, nilexp,
												  0, 2, ident_tag);
								exp n1 = getexp(sh(dest), nilexp, 0, idsc,
												nilexp, 0, 0,
												name_tag);
								exp n2 = getexp(sh(dest), nilexp, 0, idsc, n1,
												0, 0, name_tag);
								exp_list el;

								pt(idsc) = n2;

								q = f_assign(n1, f_contents(sha, source));
								el.start = q;
								el.end = q;
								el.number = 1;
								q = f_sequence(el, n2);
								clearlast(dest);
								bro(dest) = q;
								setfather(idsc, q);
								kill_exp(t, t);
								replace(to_change, idsc, idsc);
								t = i;
							}
						}
					}
				}
			}

			if (pt(t) == nilexp)
				return;
			t = pt(t);
		}
	}

	if (!writable_strings && !strcmp(dp -> dec_u.dec_val.dec_id, "strlen"))
	{
		exp i = dp -> dec_u.dec_val.dec_exp;
		exp t = pt(i);
		if (t == nilexp)
			return;

		while (1)
		{
			if (!last(t) && last(bro(t)) &&
				name(bro(bro(t))) == apply_tag &&
				son(bro(bro(t))) == t)
			{
				exp st = bro(t);

				if (name(st) == name_tag && isglob(son(st)) &&
					isvar(son(st)) && no(son(st)) == 1)
				{
					dec * source_dec = brog(son(st));
					if (!source_dec -> dec_u.dec_val.extnamed &&
						son(source_dec -> dec_u.dec_val.dec_exp) != nilexp)
					{
						exp st_def = son(son(st));
						shape sha = sh(st_def);
						if (name(st_def) == string_tag &&
							props(st_def) == 8)
						{
							char * s = nostr(st_def);
							int j;
							int l = shape_size(sha) / 8;
							for (j=0; j < l && s[j] != 0; ++j);
							if (j < l)
							{
								exp to_change = bro(st);
								exp res = getexp(sh(to_change), nilexp, 0,
												 nilexp, nilexp, 0, j, val_tag);
								kill_exp(t, t);
								replace(to_change, res, nilexp);
								t = i;
							}
						}
					}
				}
			}

			if (pt(t) == nilexp)
				return;
			t = pt(t);
		}
	}



	return;
}
