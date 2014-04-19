/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <shared/check.h>
#include <shared/xalloc.h>
#include <shared/error.h>

#include <adt/char.h>

#include <adt/group.h>	/* XXX */
#include <adt/zone.h>	/* XXX */
#include <adt/cmd.h>	/* XXX */

/*
 * FIND AN ESCAPE SEQUENCE
 *
 * This routine finds the character corresponding to the escape sequence c,
 * or EOF for \e.
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
 * ARE TWO VALUES EQUAL?
 */
static int
values_equal(enum char_type type, const union char_value *a, const union char_value *b)
{
	switch (type) {
	case group_letter:
		return a->g.not == b->g.not && is_group_equal(a->g.gn->g, b->g.gn->g);

	case char_letter:
		return a->c == b->c;
	}

	UNREACHED;
	return 0;
}

/*
 * ALLOCATE A NEW CHARACTER
 *
 * This routine allocates a new character with value v.
 */
static struct character *
new_char(enum char_type type, const union char_value *v)
{
    struct character *new;

	assert(v != NULL);

	switch (type) {
	case group_letter:
		assert(v->g.gn != NULL);
		break;

	case char_letter:
		assert(v->c >= 0 || v->c == EOF);
		break;
	}

	new = xmalloc(sizeof *new);
    new->opt  = NULL;
    new->next = NULL;
	new->type = type;
	new->v    = *v;

	/* XXX: nonportable: u.map and u.cmds may differ in representation */
	new->u.map = NULL;

    return new;
}

/*
 * COUNT MAXIMUM TOKEN LENGTH
 *
 *Find the maximum token length within the given lexical pass.
 */
size_t
char_maxlength(struct character *c)
{
	struct character *p;
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
 * FIND AN EXISTING ALTERNATIVE OF THE GIVEN VALUE, OR ADD A NEW ONE
 */
static struct character *
find_or_add(struct character **n, enum char_type type, const union char_value *v)
{
	assert(n != NULL);

	/* find an existing node, if present */
	{
		struct character *p;

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
		struct character *new;

		new = new_char(type, v);
		new->opt = *n;
		*n = new;

		return new;
	}
}

/*
 * ADD A STRING
 *
 * This routine adds the string s to the lexical pass n. This reads a C string
 * and creates a trail of characters in the trie. *n may be NULL for an empty
 * trie.
 *
 * The string given may contain escape sequences as per find_escape().
 *
 * TODO: Could move parsing into the .lxi file; strings would make a nice zone.
 */
struct character *
add_string(struct zone *z, struct character **n, const char *s)
{
	const char *p;
	struct character *leaf;

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
			v.g.gn = find_group(z, p);
			if (v.g.gn == NULL) {
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

