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


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/
#include "config.h"
#include "util.h"
#include "defs.h"
#include "find_id.h"
#include "syntax.h"


Tagdec * tagdecs;
Tagdec * localdecs;
Tokdec * tokdecs;
Labdec * labdecs;
Al_tagdec * al_tagdecs;


Tagdec *
find_tag(char * n)
{
    Tagdec * t = tagdecs;
    while (t != (Tagdec *)0) {
		if (strcmp(n, t->idname.id) == 0) return t;
		t = t->next;
    }
    t = localdecs;
    while (t != (Tagdec *)0) {
		if (strcmp(n, t->idname.id) == 0) break;
		t = t->next;
    }
    return t;
}

Tokdec *
find_tok(char * n)
{
    Tokdec * t = tokdecs;
    while (t != (Tokdec *)0) {
		if (strcmp(n, t->idname.id) == 0) break;
		t = t->next;
    }
    return t;
}

Labdec *
find_lab(char * n)
{
    Labdec * t = labdecs;
    while (t != (Labdec *)0) {
		if (strcmp(n, t->idname.id) == 0) break;
		t = t->next;
    }
    return t;
}

Al_tagdec *
find_al_tag(char * n)
{
    Al_tagdec * t = al_tagdecs;
    while (t != (Al_tagdec *)0) {
		if (strcmp(n, t->idname.id) == 0) break;
		t = t->next;
    }
    return t;
}

static int
tok_kind(Sort * x)
{
    switch (x->sort) {
	case access_sort: return access_tok;
	case al_tag_sort: return al_tag_tok;
	case bitfield_variety_sort:return bitfield_variety_tok;
	case error_treatment_sort: return error_treatment_tok;
	case exp_sort: return exp_tok;
	case floating_variety_sort: return floating_variety_tok;
	case label_sort: return label_tok;
	case nat_sort: return nat_tok;
	case ntest_sort: return ntest_tok;
	case rounding_mode_sort: return rounding_mode_tok;
	case shape_sort: return shape_tok;
	case signed_nat_sort: return signed_nat_tok;
	case tag_sort: return tag_tok;
	case token_sort: return tok_kind(&x->toksort->ressort);
	case variety_sort: return variety_tok;
    }
    fail("Not a sort - internal error");
    return 0;
}

void
tidy_labels(Labdec * old)
{
    Labdec ** rl = & labdecs;
    while (*rl != old) {
		if ((*rl)->declared) {
			*rl = (*rl)->next;
		} else {
			rl = &((*rl)->next);
		}
    }
}
