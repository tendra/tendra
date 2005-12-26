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
#include "dg_aux.h"
#include "mark_scope.h"


#ifdef NEWDIAGS

int doing_mark_scope = 0;

void
mark_scope(exp e)
{
	/* called by read_diag_id_scope; dgf(e) holds DIAG_INFO_ID */
	dg_info d = dgf(e);
	dg_info * ptr;
	exp id;
	if (!d || d->key != DGA_NAME || d->data.i_nam.dnam->key != DGN_OBJECT)
		return;
	id = son(d->data.i_nam.dnam->data.n_obj.obtain_val);
	if (name(id) == cont_tag)
		id = son(id);
	if (name(id) != name_tag)
		return;
	id = son(id);
	if (isparam(id))
		return;
	ptr = &(d->more);
	d = nildiag;
	while (*ptr && (*ptr)->key != DGA_SCOPE)
		ptr = &((*ptr)->more);
	if (!*ptr && name(e) == seq_tag && name(son(son(e))) == ass_tag
		&& last(son(son(e))) && name(bro(son(e))) != ident_tag) {
		ptr = &dgf(bro(son(e)));
		while (*ptr && (*ptr)->key != DGA_SCOPE)
			ptr = &((*ptr)->more);
	}
	if (*ptr) {
		d = *ptr;
		*ptr = d->more;
	}
	else {
		d = f_lexical_block_dg (no_dg_idname_option, no_dg_sourcepos_option);
		d->data.i_scope.begin_st = (long)(-1);
		doing_mark_scope = 1;
	}
	/* if (isglob(id)) */ {
		d->more = dgf(e);
		dgf(e) = d;
	}
#if 0
	else {
		exp def = son(id);
		if (dgf(def) && dgf(def)->key == DGA_SRC)
			dgf(e)->data.i_nam.dnam->whence = dgf(def)->data.i_src.startpos;
		d->more = dgf(id);
		dgf(id) = d;
	}
#endif
	return;
}

void
mark_scope2(exp e)
{
	/* called by read_diag_type_scope; dgf(e) holds DIAG_INFO_ID */
	dg_info d = dgf(e);
	dg_info * ptr;
	if (!d || d->key != DGA_NAME || d->data.i_nam.dnam->key != DGN_TYPE)
		return;
	ptr = &(d->more);
	d = nildiag;
	while (*ptr && (*ptr)->key != DGA_SCOPE)
		ptr = &((*ptr)->more);
	if (*ptr) {
		d = *ptr;
		*ptr = d->more;
	}
	else {
		d = f_lexical_block_dg (no_dg_idname_option, no_dg_sourcepos_option);
		d->data.i_scope.begin_st = (long)(-1);
		doing_mark_scope = 1;
	}
	d->more = dgf(e);
	dgf(e) = d;
	return;
}

void
correct_mark_scope(exp e)
{
	dg_info d = nildiag;
	dg_info * ptr = &(dgf(bro(son(e))));
	while (*ptr && (*ptr)->key != DGA_SCOPE)
		ptr = &((*ptr)->more);
	if (*ptr) {
		d = *ptr;
		*ptr = d->more;
	}
	if (d) {
		d->more = dgf(e);
		dgf(e) = d;
	}
	return;
}


#else


/* PROCEDURES */

static exp
previous_scope(exp e)
{
	if (!last(e) || bro(e) == nilexp)
		return nilexp;
	
	if (name(bro(e)) == diagnose_tag && (props(bro(e)) & 0x7) == 1)
		return previous_scope(bro(e));
	
	if (name(bro(e)) == diagnose_tag)
		return bro(e);
	
	if (name(bro(e)) == ident_tag && last(bro(e)))
	{
		if (bro(bro(e)) == nilexp)
			return nilexp;
		
		if (name(bro(bro(e))) == diagnose_tag &&
			(props(bro(bro(e))) & 0x7) == 1)
			return previous_scope(bro(bro(e)));
		
		if (name(bro(bro(e))) == diagnose_tag)
			return bro(bro(e));
		
		return nilexp;
	}
	
	return nilexp;
}


static int
param_scope(exp e)
{
	diag_info * d = dno(e);
	if (d -> key == DIAG_INFO_ID)
		return isparam(son(d -> data.id_scope.access));
	return 0;
}

static int
needs_hiding(exp a, exp b)
{
	diag_info * da = dno(a);
	diag_info * db = dno(b);
	
	if (da -> key != db -> key)
		return 0;
	
	switch (da -> key)
    {
	case DIAG_INFO_ID:
		return !strcmp(da -> data.id_scope.nme.ints.chars,
					   db -> data.id_scope.nme.ints.chars);
	case DIAG_INFO_TYPE:
		return !strcmp(da -> data.type_scope.nme.ints.chars,
					   db -> data.type_scope.nme.ints.chars);
	case DIAG_INFO_TAG:
		return !strcmp(da -> data.tag_scope.nme.ints.chars,
					   db -> data.tag_scope.nme.ints.chars);
	default: return 0;
    }
}

void
mark_scope(exp e)
{
	exp scope = e;
	
	if (param_scope(e))
		return;
	
	while (1)
	{
		scope = previous_scope(scope);
		
		if (scope == nilexp || param_scope(scope) ||
			needs_hiding(e, scope))
		{
			props(e) = (prop)(props(e) | 0x80);
			return;
		}
		
		if (props(scope) & 0x80)
			return;
		
	}
}

#endif
