/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stddef.h>

#include <shared/xalloc.h>

#include <adt/entry.h>
#include <adt/zone.h>

#include "ast.h"

struct ast *
init_ast(void)
{
	struct ast *new;

	new = xmalloc(sizeof *new);
	new->global = new_zone(new);
	new->table  = NULL;
	new->groups = NULL;

	return new;
}

int
all_groups_empty(struct ast *ast)
{
	struct group *p;

	assert(ast != NULL);

	for (p = ast->groups; p != NULL; p = p->next) {
		if (!is_group_empty(p)) {
			return 0;
		}
	}

	return 1;
}

struct group *
tree_find_group(struct ast *ast, struct group *g)
{
	struct group *p;

	assert(ast != NULL);
	assert(g != NULL);

	for (p = ast->groups; p != NULL; p = p->next) {
		if (is_group_equal(p, g)) {
			return p;
		}
	}

	return NULL;
}

void
set_builtin_type(struct ast *ast, struct entry **e, char *lexi_type)
{
	assert(ast != NULL);
	assert(e != NULL);
	assert(lexi_type != NULL);

	/* TODO: assert(table_get_entry(&ast->table, &str) == NULL) */
	*e = table_add_type(&ast->table, lexi_type);
}

