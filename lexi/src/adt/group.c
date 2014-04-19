/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <string.h>

#include <shared/xalloc.h>
#include <shared/error.h>

#include <adt/char.h>
#include <adt/group.h>
#include <adt/zone.h>
#include <adt/tree.h>

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
 * CREATE A NEW GROUP
 *
 * This routine creates a new character group with definition s, which is
 * a null-terminated string of escaped values as per find_escape(). It may
 * not contain "\e" (for EOF), since EOF is not permitted in groups.
 *
 * s may be NULL to indicate the empty group.
 */
char_group_name *
make_group(zone *z, char *name, char *defn)
{
	char_group_name *new;
	char_group_defn *new_def;
	char_group_defn *old_def;

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
	new_def->next_in_groups_list = NULL;

	if (defn == NULL) {
		unescape_string(z, new_def->defn, "");
	} else {
		unescape_string(z, new_def->defn, defn);
	}

	old_def = tree_find_group(z->top_level, new_def);
	if (old_def != NULL) {
		xfree(new_def);
		new->def = old_def;
	} else {
		tree_add_group(z->top_level, new_def);
		new->def = new_def;
	}

	return new;
}

/*
 * IS A LETTER IN A GROUP?
 */
int
in_group(char_group_defn *g, char c)
{
	assert(g != NULL);

	return g->defn[(unsigned char) c];
}

/*
 * IS A GROUP EMPTY?
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
 * ARE TWO GROUPS EQUIVALENT?
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
 * FIND A GROUP BY NAME
 *
 * This searches within the list of groups specific to a zone and its parent
 * zones, rather than in all groups globally.
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

