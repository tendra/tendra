/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:57:24 $
$Revision: 1.1.1.1 $
$Log: find_id.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:24  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.2  1994/07/21  10:36:11  currie
 * Added banner
 *
***********************************************************************/
#include "config.h"
#include "util.h"
#include "defs.h"
#include "find_id.h"
#include "syntax.h"


Tagdec *tagdecs;
Tagdec *localdecs;
Tokdec *tokdecs;
Labdec *labdecs;
Al_tagdec *al_tagdecs;


Tagdec *
find_tag(char * n)
{
	Tagdec *t = tagdecs;
	while (t != (Tagdec *)0) {
		if (strcmp(n, t->idname.id) == 0) {
			return t;
		}
		t = t->next;
	}
	t = localdecs;
	while (t != (Tagdec *)0) {
		if (strcmp(n, t->idname.id) == 0) {
			break;
		}
		t = t->next;
	}
	return t;
}


Tokdec *
find_tok(char * n)
{
	Tokdec * t = tokdecs;
	while (t != (Tokdec *)0) {
		if (strcmp(n, t->idname.id) == 0) {
			break;
		}
		t = t->next;
	}
	return t;
}


Labdec *
find_lab(char * n)
{
	Labdec *t = labdecs;
	while (t != (Labdec *)0) {
		if (strcmp(n, t->idname.id) == 0) {
			break;
		}
		t = t->next;
	}
	return t;
}


Al_tagdec *
find_al_tag(char * n)
{
	Al_tagdec *t = al_tagdecs;
	while (t != (Al_tagdec *)0) {
		if (strcmp(n, t->idname.id) == 0) {
			break;
		}
		t = t->next;
	}
	return t;
}


static int
tok_kind(Sort * x)
{
	switch (x->sort) {
	case access_sort:
		return access_tok;
	case al_tag_sort:
		return al_tag_tok;
	case bitfield_variety_sort:
		return bitfield_variety_tok;
	case error_treatment_sort:
		return error_treatment_tok;
	case exp_sort:
		return exp_tok;
	case floating_variety_sort:
		return floating_variety_tok;
	case label_sort:
		return label_tok;
	case nat_sort:
		return nat_tok;
	case ntest_sort:
		return ntest_tok;
	case rounding_mode_sort:
		return rounding_mode_tok;
	case shape_sort:
		return shape_tok;
	case signed_nat_sort:
		return signed_nat_tok;
	case tag_sort:
		return tag_tok;
	case token_sort:
		return tok_kind(&x->toksort->ressort);
	case variety_sort:
		return variety_tok;
	}
	fail("Not a sort - internal error");
	return 0;
}

void
tidy_labels(Labdec *old)
{
	Labdec **rl = &labdecs;
	while (*rl != old) {
		if ((*rl)->declared) {
			*rl = (*rl)->next;
		} else {
			rl = &((*rl)->next);
		}
	}
}
