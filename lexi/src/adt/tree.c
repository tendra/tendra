/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stddef.h>

#include <shared/xalloc.h>

#include "../adt.h"

#include "char.h"
#include "tree.h"
#include "zone.h"

struct FILE_list_entry_tag {
	FILE *file;
	char *filename;
	FILE_list_entry *next;
};

struct lexer_parse_tree_tag {
	struct zone_tag *global_zone;

	FILE_list_entry  *copyright_head;
	FILE_list_entry **copyright_tail;

	char_group_defn *groups_list;

	EntryT *table; /* Actions and types */

	EntryT *lexi_char_type;     /* for #0 arguments */
	EntryT *lexi_string_type;   /* for #* arguments */
	EntryT *lexi_int_type;      /* for #n arguments */
	EntryT *lexi_terminal_type; /* for $ = returns  */
};

lexer_parse_tree *
init_lexer_parse_tree(void)
{
	lexer_parse_tree *new;

	new = xmalloc(sizeof *new);
	new->table       = NULL;
	new->global_zone = new_zone(new);
	new->groups_list = NULL;

	new->copyright_head = NULL;
	new->copyright_tail = &new->copyright_head;

	return new;
}

void
tree_add_copyright_file(lexer_parse_tree *t, FILE *file, char *filename)
{
	FILE_list_entry *p;

	p = xmalloc(sizeof *p);
	p->file     = file;
	p->filename = filename;
	p->next     = NULL;

	*(t->copyright_tail) = p;
	t->copyright_tail = &p->next;
}

FILE_list_entry *
tree_get_copyright_list(lexer_parse_tree *t)
{
	return t->copyright_head;
}

FILE_list_entry *
file_list_next(FILE_list_entry *file_list)
{
	return file_list->next;
}

FILE *
file_list_crt_file(FILE_list_entry *file_entry)
{
	return file_entry->file;
}

char *
file_list_crt_filename(FILE_list_entry *file_entry)
{
	return file_entry->filename;
}

int
tree_zoneisglobal(lexer_parse_tree *t, zone *z)
{
	assert(t != NULL);
	assert(z != NULL);

	return tree_get_globalzone(t) == z;
}

void tree_close_copyright_files(lexer_parse_tree *t)
{
	FILE_list_entry *file_list;

	for (file_list = tree_get_copyright_list(t);
			file_list != NULL;
			file_list = file_list_next(file_list)) {
		fclose(file_list_crt_file(file_list));
	}
}

zone *
tree_get_globalzone(lexer_parse_tree *t)
{
	assert(t != NULL);

	return t->global_zone;
}

EntryT **
tree_get_table(lexer_parse_tree *t)
{
	assert(t != NULL);

	return &t->table;
}

char_group_defn *
tree_get_grouplist(lexer_parse_tree *t)
{
	assert(t != NULL);

	return t->groups_list;
}

int
all_groups_empty(lexer_parse_tree *t)
{
	char_group_defn *g;

	assert(t != NULL);

	for (g = t->groups_list; g != NULL; g = g->next_in_groups_list) {
		if (!is_group_empty(g)) {
			return 0;
		}
	}

	return 1;
}

char_group_defn *
tree_find_group(lexer_parse_tree *t, char_group_defn *b)
{
	char_group_defn *g;

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
tree_add_group(lexer_parse_tree *t, char_group_defn *g)
{
	assert(t != NULL);
	assert(g->next_in_groups_list == NULL);

	g->next_in_groups_list = t->groups_list;
	t->groups_list = g;
}

void
set_predefined_char_lexi_type(lexer_parse_tree* top_level, char *lexi_type, char *c_type)
{
	NStringT str;
	NStringT cstr;
	EntryT *entry;
	TypeT *type;

	nstring_copy_cstring(&str, lexi_type);
	nstring_copy_cstring(&cstr, c_type);

	/* TODO assert(table_get_entry(tree_get_table(top_level), &str) == NULL) */
	entry = table_add_type(tree_get_table(top_level), &str, true);
	type  = entry_get_type(entry);

	type_map(type, &cstr);
	top_level->lexi_char_type = entry;
}

void
set_predefined_string_lexi_type(lexer_parse_tree *top_level, char *lexi_type, char *c_type)
{
	NStringT str;
	NStringT cstr;
	EntryT *entry;
	TypeT *type;

	nstring_copy_cstring(&str, lexi_type);
	nstring_copy_cstring(&cstr, c_type);

	/* TODO assert(table_get_entry(tree_get_table(top_level), &str) == NULL) */
	entry = table_add_type(tree_get_table(top_level), &str, true);
	type = entry_get_type(entry);

	type_map(type, &cstr);
	top_level->lexi_string_type = entry;
}

void
set_predefined_terminal_lexi_type(lexer_parse_tree *top_level, char *lexi_type)
{
	NStringT str;
	EntryT* entry;

	nstring_copy_cstring(&str, lexi_type);

	/* TODO assert(table_get_entry(tree_get_table(top_level), &str) == NULL) */
	entry = table_add_type(tree_get_table(top_level), &str, true);
	top_level->lexi_terminal_type = entry;
}

void
set_predefined_int_lexi_type(lexer_parse_tree* top_level, char *lexi_type, char *c_type)
{
	NStringT str;
	NStringT cstr;
	EntryT *entry;
	TypeT *type;

	nstring_copy_cstring(&str, lexi_type);
	nstring_copy_cstring(&cstr, c_type);

	/* TODO assert(table_get_entry(tree_get_table(top_level), &str) == NULL) */
	entry = table_add_type(tree_get_table(top_level), &str, true);
	type  = entry_get_type(entry);

	type_map(type, &cstr);
	top_level->lexi_int_type = entry;
}

EntryT *
lexer_char_type(lexer_parse_tree *top_level)
{
	return top_level->lexi_char_type;
}

EntryT *
lexer_string_type(lexer_parse_tree *top_level)
{
	return top_level->lexi_string_type;
}

EntryT *
lexer_int_type(lexer_parse_tree *top_level)
{
	return top_level->lexi_int_type;
}

EntryT *
lexer_terminal_type(lexer_parse_tree *top_level)
{
	return top_level->lexi_terminal_type;
}

