/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stdio.h>

#include <shared/string.h>

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
		if (streq(n, t->idname.id)) {
			return t;
		}
		t = t->next;
	}
	t = localdecs;
	while (t != (Tagdec *)0) {
		if (streq(n, t->idname.id)) {
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
		if (streq(n, t->idname.id)) {
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
		if (streq(n, t->idname.id)) {
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
		if (streq(n, t->idname.id)) {
			break;
		}
		t = t->next;
	}
	return t;
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
