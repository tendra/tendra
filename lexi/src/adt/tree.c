/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stddef.h>
#include <stdbool.h>

#include <shared/xalloc.h>

#include <adt/entry.h>
#include <adt/char.h>
#include <adt/tree.h>
#include <adt/zone.h>

struct lexer_parse_tree {
	struct zone *global_zone;

	struct char_group_defn *groups_list;

	struct EntryT *table; /* Actions and types */

	struct EntryT *lexi_char_type;     /* for #0 arguments */
	struct EntryT *lexi_string_type;   /* for #* arguments */
	struct EntryT *lexi_int_type;      /* for #n arguments */
	struct EntryT *lexi_terminal_type; /* for $ = returns  */
};

struct lexer_parse_tree *
init_lexer_parse_tree(void)
{
	struct lexer_parse_tree *new;

	new = xmalloc(sizeof *new);
	new->table       = NULL;
	new->global_zone = new_zone(new);
	new->groups_list = NULL;

	return new;
}

int
tree_zoneisglobal(struct lexer_parse_tree *t, struct zone *z)
{
	assert(t != NULL);
	assert(z != NULL);

	return tree_get_globalzone(t) == z;
}

struct zone *
tree_get_globalzone(struct lexer_parse_tree *t)
{
	assert(t != NULL);

	return t->global_zone;
}

struct EntryT **
tree_get_table(struct lexer_parse_tree *t)
{
	assert(t != NULL);

	return &t->table;
}

struct char_group_defn *
tree_get_grouplist(struct lexer_parse_tree *t)
{
	assert(t != NULL);

	return t->groups_list;
}

int
all_groups_empty(struct lexer_parse_tree *t)
{
	struct char_group_defn *g;

	assert(t != NULL);

	for (g = t->groups_list; g != NULL; g = g->next_in_groups_list) {
		if (!is_group_empty(g)) {
			return 0;
		}
	}

	return 1;
}

struct char_group_defn *
tree_find_group(struct lexer_parse_tree *t, struct char_group_defn *b)
{
	struct char_group_defn *g;

	assert(t != NULL);
	assert(b != NULL);

	for (g = t->groups_list; g != NULL; g = g->next_in_groups_list) {
		if (is_group_equal(g,b)) {
			return g;
		}
	}

	return NULL;
}

void
tree_add_group(struct lexer_parse_tree *t, struct char_group_defn *g)
{
	assert(t != NULL);
	assert(g->next_in_groups_list == NULL);

	g->next_in_groups_list = t->groups_list;
	t->groups_list = g;
}

void
set_predefined_char_lexi_type(struct lexer_parse_tree* top_level, char *lexi_type, char *c_type)
{
	NStringT str;
	NStringT cstr;
	struct EntryT *entry;
	struct TypeT *type;

	nstring_copy_cstring(&str, lexi_type);
	nstring_copy_cstring(&cstr, c_type);

	/* TODO assert(table_get_entry(tree_get_table(top_level), &str) == NULL) */
	entry = table_add_type(tree_get_table(top_level), &str, true);
	type  = entry_get_type(entry);

	type_map(type, &cstr);
	top_level->lexi_char_type = entry;
}

void
set_predefined_string_lexi_type(struct lexer_parse_tree *top_level, char *lexi_type, char *c_type)
{
	NStringT str;
	NStringT cstr;
	struct EntryT *entry;
	struct TypeT *type;

	nstring_copy_cstring(&str, lexi_type);
	nstring_copy_cstring(&cstr, c_type);

	/* TODO assert(table_get_entry(tree_get_table(top_level), &str) == NULL) */
	entry = table_add_type(tree_get_table(top_level), &str, true);
	type = entry_get_type(entry);

	type_map(type, &cstr);
	top_level->lexi_string_type = entry;
}

void
set_predefined_terminal_lexi_type(struct lexer_parse_tree *top_level, char *lexi_type)
{
	NStringT str;
	struct EntryT* entry;

	nstring_copy_cstring(&str, lexi_type);

	/* TODO assert(table_get_entry(tree_get_table(top_level), &str) == NULL) */
	entry = table_add_type(tree_get_table(top_level), &str, true);
	top_level->lexi_terminal_type = entry;
}

void
set_predefined_int_lexi_type(struct lexer_parse_tree* top_level, char *lexi_type, char *c_type)
{
	NStringT str;
	NStringT cstr;
	struct EntryT *entry;
	struct TypeT *type;

	nstring_copy_cstring(&str, lexi_type);
	nstring_copy_cstring(&cstr, c_type);

	/* TODO assert(table_get_entry(tree_get_table(top_level), &str) == NULL) */
	entry = table_add_type(tree_get_table(top_level), &str, true);
	type  = entry_get_type(entry);

	type_map(type, &cstr);
	top_level->lexi_int_type = entry;
}

struct EntryT *
lexer_char_type(struct lexer_parse_tree *top_level)
{
	return top_level->lexi_char_type;
}

struct EntryT *
lexer_string_type(struct lexer_parse_tree *top_level)
{
	return top_level->lexi_string_type;
}

struct EntryT *
lexer_int_type(struct lexer_parse_tree *top_level)
{
	return top_level->lexi_int_type;
}

struct EntryT *
lexer_terminal_type(struct lexer_parse_tree *top_level)
{
	return top_level->lexi_terminal_type;
}

