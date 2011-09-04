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
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <shared/xalloc.h>
#include <shared/error.h>

#include "char.h"

#include "group.h"	/* XXX */
#include "zone.h"	/* XXX */
#include "instruction.h"	/* XXX */
#include "tree.h"	/* XXX */


/*
	FIND AN ESCAPE SEQUENCE

	This routine finds the character corresponding to the escape sequence c,
	or EOF for \e.
*/

int
find_escape(char c)
{
	switch (c) {
	case 'n':  return '\n';
	case 't':  return '\t';
	case 'v':  return '\v';
	case 'f':  return '\f';
	case 'r':  return '\r';
	case '?':  return '?';
	case '"':  return '"';
	case '[':  return '[';
	case '\\': return '\\';
	case '\'': return '\'';
	case 'e':  return EOF;

	default:
		error(ERROR_SERIOUS, "Unknown escape sequence, '\\%c'", c);
		return c;
	}
}


/*
	ARE TWO VALUES EQUAL?
*/

static int
values_equal(letter_translation_type type, const union char_value *a, const union char_value *b)
{
	switch (type) {
	case group_letter:
		return a->g.not == b->g.not && is_group_equal(a->g.grp->def, b->g.grp->def);

	case char_letter:
		return a->c == b->c;
	}

	assert(!"unreached");
	return 0;
}


/*
    ALLOCATE A NEW CHARACTER

    This routine allocates a new character with value v.
*/

static character *
new_char(letter_translation_type type, const union char_value *v)
{
    character *new;

	assert(v != NULL);

	switch (type) {
	case group_letter:
		assert(v->g.grp != NULL);
		break;

	case char_letter:
		assert(v->c >= 0 || v->c == EOF);
		break;
	}

	new = xmalloc(sizeof *new);
    new->opt = NULL;
    new->next = NULL;
	new->type = type;
	new->v = *v;

	/* XXX: nonportable: u.map and u.definition may differ in representation */
	new->u.map = NULL;

    return new;
}


/*
	COUNT MAXIMUM TOKEN LENGTH

	Find the maximum token length within the given lexical pass.
*/
size_t
char_maxlength(character *c)
{
	character *p;
	size_t maxopt;

	assert(c != NULL);

	maxopt = 0;
	for (p = c; p != NULL; p = p->opt) {
		size_t l;

		if (p->next == NULL) {
			continue;
		}

		l = char_maxlength(p->next) + 1;

		if (l > maxopt) {
			maxopt = l;
		}
	}

	return maxopt;
}


/*
	FIND AN EXISTING ALTERNATIVE OF THE GIVEN VALUE, OR ADD A NEW ONE
*/

static character *
find_or_add(character **n, letter_translation_type type, const union char_value *v)
{
	assert(n != NULL);

	/* find an existing node, if present */
	{
		character *p;

		for (p = *n; p != NULL; p = p->opt) {
			if (p->type != type) {
				continue;
			}

			if (values_equal(type, &p->v, v)) {
				return p;
			}
		}
	}

	/* otherwise, add a new node */
	{
		character *new;

		new = new_char(type, v);
		new->opt = *n;
		*n = new;

		return new;
	}
}


/*
	ADD A STRING

	This routine adds the string s to the lexical pass n. This reads a C string
	and creates a trail of characters in the trie. *n may be NULL for an empty
	trie.

	The string given may contain escape sequences as per find_escape().

	TODO: Could move parsing into the .lxi file; strings would make a nice zone.
*/
character *
add_string(zone *z, character **n, const char *s)
{
	const char *p;
	character *leaf;

	assert(z != NULL);
	assert(n != NULL);
	assert(s != NULL);

	if (strlen(s) == 0) {
		return NULL;
	}

	leaf = NULL;
	for (p = s; *p; p++) {
		char *e;
		union char_value v;

		switch (*p) {
		case '[':	/* group */
			v.g.not = 0;

			p++;
			if (*p == '^') {
				v.g.not = 1;
				p++;
			}

			e = strchr(p, ']');
			if (e == NULL || *p == '\0') {
				error(ERROR_SERIOUS, "Unterminated group");
				return NULL;
			}

			*e = '\0';
			v.g.grp = find_group(z, p);
			if (v.g.grp == NULL) {
				error(ERROR_SERIOUS, "Unknown group '%s'", p);
			}

			leaf = find_or_add(n, group_letter, &v);
			p = e;
			break;

		case '\\':	/* escaped character */
			p++;
			if (*p == '\0') {
				error(ERROR_SERIOUS, "Missing escape");
				break;
			}

			v.c = find_escape(*p);
			leaf = find_or_add(n, char_letter, &v);
			break;

		default:	/* literal character */
			v.c = *p;
			leaf = find_or_add(n, char_letter, &v);
			break;
		}

		assert(leaf != NULL);
		n = &leaf->next;
	}

	return leaf;
}

