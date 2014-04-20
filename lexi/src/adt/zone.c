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

#include <adt/zone.h>
#include <adt/char.h>
#include <adt/cmd.h>

#include "../ast.h"

/*
 * FIND A ZONE
 *
 * This routine finds a zone within the current zone. This does not include
 * searching in parent zones.
 */
static struct zone *
find_zone(struct zone *z, char *name)
{
	struct zone *q;

	assert(z != NULL);
	assert(name != NULL);

	for (q = z->next; q != NULL; q = q->opt) {
		if (q->name == NULL) {
			continue;
		}

		if (strcmp(q->name, name) == 0) {
			return q;
		}
	}

	return NULL;
}

/*
 * COUNT MAXIMUM TOKEN LENGTH
 *
 * Find the maximum token length necessary for a given zone
 */
size_t
zone_maxlength(struct zone *z, int in_prepass)
{
	size_t max;
	struct zone *p;

	assert(z != NULL);

	{
		struct character *pass;

		pass = in_prepass ? z->pre : z->main;
		max  = pass == NULL ? 0 : char_maxlength(pass);
	}

	for (p = z->next; p != NULL; p = p->opt) {
		size_t l;

		l = zone_maxlength(p, in_prepass);
		if (l > max) {
			max = l;
		}
	}

	return max;
}

/*
 * ALLOCATE A NEW ZONE
 *
 * This routine allocates a new zone.
 *
 * TODO: make this private, and provide a add_globalzone() instead.
 */
struct zone *
new_zone(struct ast *ast)
{
	struct zone *new;

	assert(ast != NULL);

	new = xmalloc(sizeof *new);
	new->name = NULL;
	new->kind = ZONE_PURE;

	new->main = NULL;
	new->pre  = NULL;

	new->keywords    = NULL;
	new->groups      = NULL;
	new->white_space = NULL;

	new->local = NULL;
	new->enter = NULL;
	new->exit  = NULL;

	new->opt  = NULL;
	new->next = NULL;
	new->up   = NULL;

	new->ast = ast;

	return new;
}

/*
 * ADD A ZONE
 *
 * This routine adds a new zone named zid under the current zone z
 */
struct zone *
add_zone(struct zone *z, char *name, const char *e, int endmarkerclosed)
{
	struct zone *new;
	struct cmd *cmd;
	struct cmd_list *cmd_list;

	assert(z != NULL);
	assert(name != NULL);
	assert(e != NULL);

	if (find_zone(z, name)) {
		error(ERROR_SERIOUS, "Zone %s already exists in this scope", name);
		return NULL;
	}

	new = new_zone(z->ast);
	new->name = name;
	new->opt = z->next;
	z->next = new;
	new->up = z;

	cmd = add_cmd_pop_zone(z, endmarkerclosed);
	cmd_list = add_cmd_list();
	*cmd_list->tail = cmd;
	cmd_list->tail = &cmd->next;

	add_mainpass(new, e, cmd_list);

	return new;
}

struct character *
add_mainpass(struct zone *z, const char *s, struct cmd_list *l)
{
	struct character *new;

	assert(z != NULL);
	assert(s != NULL);
	assert(l != NULL);

	new = add_string(z, &z->main, s);
	if (new == NULL) {
		return NULL;
	}

	if (new->u.cmds != NULL) {
		error(ERROR_SERIOUS, "Token \"%s\" already exists in zone %s", s, zone_name(z));
		return NULL;
	}

	new->u.cmds = l;

	return new;
}

struct character *
add_prepass(struct zone *z, const char *s, char *m)
{
	struct character *new;

	assert(z != NULL);
	assert(s != NULL);
	assert(m != NULL);

	new = add_string(z, &z->pre, s);
	assert(new != NULL);

	if (new->u.map != NULL) {
		error(ERROR_SERIOUS, "Mapping \"%s\" already exists in zone %s", s, zone_name(z));
		return NULL;
	}

	new->u.map = m;

	return new;
}

int
zone_isglobal(struct zone *z)
{
	assert(z != NULL);

	return z == tree_get_globalzone(z->ast);
}

const char *
zone_name(struct zone *z)
{
	assert(z != NULL);

	if (z->name == NULL) {
		return "the global zone";
	}

	return z->name;
}

