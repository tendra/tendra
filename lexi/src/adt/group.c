/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/

#include <assert.h>
#include <string.h>

#include "xalloc/xalloc.h"
#include "error/error.h"

#include "char.h"
#include "group.h"
#include "zone.h"
#include "tree.h"


static void
unescape_string(zone *z, int *o, char *s)
{
	const char *p;
	unsigned int i;

	for (i = 0; i <= 255; i++) {
		o[i] = 0;
	}

	/* TODO: this is strikngly similar to add_string(). fold both into the .lxi file? */
	for (p = s; *p != '\0'; p++) {
		char_group_name *g;
		char *e;
		int not;
		int c;

		switch (*p) {
		case '[':
			not = 0;

			p++;
			if (*p == '^') {
				not = 1;
				p++;
			}

			e = strchr(p, ']');
			if (e == NULL || *p == '\0') {
				error(ERROR_SERIOUS, "Unterminated group");
				break;
			}

			*e = '\0';
			g = find_group(z, p);
			if (g == NULL) {
				error(ERROR_SERIOUS, "Unknown group '%s'", p);
				break;
			}

			/* merge in the named group */
			for (i = 0; i <= 255; i++) {
				o[i] |= not ? !in_group(g->def, i) : in_group(g->def, i);
			}

			p = e;
			break;

		case '\\':
			p++;
			if (*p == '\0') {
				error(ERROR_SERIOUS, "Missing escape");
				break;
			}

			c = find_escape(*p);
			if (c == EOF) {
				error(ERROR_SERIOUS, "Groups may not contain EOF");
				break;
			}

			i = (unsigned char) c;
			o[i] = 1;
			break;

		default:
			i = (unsigned char ) *p;
			o[i] = 1;
			break;
		}
	}
}

/*
    CREATE A NEW GROUP

    This routine creates a new character group with definition s, which is
	a null-terminated string of escaped values as per find_escape(). It may
	not contain "\e" (for EOF), since EOF is not permitted in groups.

	s may be NULL to indicate the empty group.
*/

char_group_name*
make_group(zone *z, char *name, char *defn)
{
	char_group_name *new;
	char_group_defn *new_def;

	assert(z != NULL);
	assert(name != NULL);

	if (strlen(defn) == 0) {
		defn = NULL;
	}

	{
		char_group_name *g;

		g = find_group(z, name);
		if (g != NULL && g->z == z) {
			error(ERROR_SERIOUS, "Group '%s' already defined for this zone", name);
			return NULL;
		}
	}

	new = xmalloc(sizeof *new);
	new->name = name;
	new->z = z;
	new->next = z->groups;
	z->groups = new;

	new_def = xmalloc(sizeof *new_def);
	if (defn == NULL) {
		unescape_string(z, new_def->defn, "");
	} else {
		unescape_string(z, new_def->defn, defn);
	}
	new->def=new_def;
	tree_add_group(z->top_level, new_def);

	return new;
}


/*
    IS A LETTER IN A GROUP?
*/

int
in_group(char_group_defn *g, char c)
{
	assert(g != NULL);

	return g->defn[(unsigned char) c];
}


/*
	IS A GROUP EMPTY?
*/

int
is_group_empty(char_group_defn *g)
{
	unsigned int i;

	assert(g != NULL);

	for (i = 0; i <= 255; i++) {
		if (g->defn[i]) {
			return 0;
		}
	}

	return 1;
}


/*
	ARE TWO GROUPS EQUIVALENT?
*/

int
is_group_equal(char_group_defn *a, char_group_defn *b)
{
	unsigned int i;

	assert(a != NULL);
	assert(b != NULL);

	for (i = 0; i <= 255; i++) {
		if (!!a->defn[i] != !!b->defn[i]) {
			return 0;
		}
	}

	return 1;
}


/*
	FIND A GROUP BY NAME

	This searches within the list of groups specific to a zone and its parent
	zones, rather than in all groups globally.
*/

char_group_name *
find_group(const zone *z, const char *name)
{
	char_group_name *p;

	for (p = z->groups; p != NULL; p = p->next) {
		if (0 == strcmp(name, p->name)) {
			return p;
		}
	}

	if (z->up == NULL) {
		return NULL;
	}

	return find_group(z->up, name);
}

