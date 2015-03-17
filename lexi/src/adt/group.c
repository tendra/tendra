/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <string.h>

#include <shared/string.h>
#include <shared/xalloc.h>
#include <shared/error.h>

#include <adt/group.h>
#include <adt/zone.h>
#include <adt/trie.h>

#include "../ast.h"

static void
unescape_string(struct zone *z, int *o, char *s)
{
	const char *p;
	unsigned int i;

	for (i = 0; i <= 255; i++) {
		o[i] = 0;
	}

	/* TODO: this is strikngly similar to add_string(). fold both into the .lxi file? */
	for (p = s; *p != '\0'; p++) {
		struct group_name *gn;
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
				error(ERR_SERIOUS, "Unterminated group");
				break;
			}

			*e = '\0';
			gn = find_group(z, p);
			if (gn == NULL) {
				error(ERR_SERIOUS, "Unknown group '%s'", p);
				break;
			}

			/* merge in the named group */
			for (i = 0; i <= 255; i++) {
				o[i] |= not ? !in_group(gn->g, i) : in_group(gn->g, i);
			}

			p = e;
			break;

		case '\\':
			p++;
			if (*p == '\0') {
				error(ERR_SERIOUS, "Missing escape");
				break;
			}

			c = find_escape(*p);
			if (c == EOF) {
				error(ERR_SERIOUS, "Groups may not contain EOF");
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
 * CREATE A NEW GROUP
 *
 * This routine creates a new character group with definition s, which is
 * a null-terminated string of escaped values as per find_escape(). It may
 * not contain "\e" (for EOF), since EOF is not permitted in groups.
 *
 * s may be NULL to indicate the empty group.
 */
struct group_name *
make_group(struct zone *z, char *name, char *defn)
{
	struct group_name *gn;

	assert(z != NULL);
	assert(name != NULL);

	if (strlen(defn) == 0) {
		defn = NULL;
	}

	{
		struct group_name *gn;

		gn = find_group(z, name);
		if (gn != NULL && gn->z == z) {
			error(ERR_SERIOUS, "Group '%s' already defined for this zone", name);
			return NULL;
		}
	}

	gn = xmalloc(sizeof *gn);
	gn->name = name;
	gn->z = z;
	gn->next = z->groups;
	z->groups = gn;

	{
		struct group *new;
		struct group *old;

		new = xmalloc(sizeof *new);
		new->next = NULL;

		if (defn == NULL) {
			unescape_string(z, new->defn, "");
		} else {
			unescape_string(z, new->defn, defn);
		}

		old = tree_find_group(z->ast, new);
		if (old != NULL) {
			xfree(new);
			gn->g = old;
		} else {
			gn->g = new;
			new->next = z->ast->groups;
			z->ast->groups = new;
		}
	}

	return gn;
}

/*
 * IS A LETTER IN A GROUP?
 */
int
in_group(struct group *g, char c)
{
	assert(g != NULL);

	return g->defn[(unsigned char) c];
}

/*
 * IS A GROUP EMPTY?
 */
int
is_group_empty(struct group *g)
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
 * ARE TWO GROUPS EQUIVALENT?
 */
int
is_group_equal(struct group *a, struct group *b)
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
 * FIND A GROUP BY NAME
 *
 * This searches within the list of groups specific to a zone and its parent
 * zones, rather than in all groups globally.
 */
struct group_name *
find_group(const struct zone *z, const char *name)
{
	struct group_name *p;

	for (p = z->groups; p != NULL; p = p->next) {
		if (streq(name, p->name)) {
			return p;
		}
	}

	if (z->up == NULL) {
		return NULL;
	}

	return find_group(z->up, name);
}

