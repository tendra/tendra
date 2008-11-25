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

#include "shared/xalloc/xalloc.h"

#include "../adt.h"

#include "char.h"
#include "tree.h"
#include "zone.h"

struct FILE_list_entry_tag {
	FILE* file;
	char* filename;
	FILE_list_entry* next;
};

struct lexer_parse_tree_tag {
	struct zone_tag *global_zone;

	FILE_list_entry  *copyright_head;
	FILE_list_entry **copyright_tail;

	char_group_defn *groups_list;

	EntryT *table; /* Actions and types */

	EntryT* lexi_char_type;    /*  for #0 arguments */
	EntryT* lexi_string_type;  /*  for #* arguments */
	EntryT* lexi_int_type;     /*  for #n arguments */
	EntryT* lexi_terminal_type;     /*  for $ = returns */
};


lexer_parse_tree*
init_lexer_parse_tree(void) {
	lexer_parse_tree *new;

	new = xmalloc(sizeof *new);
	new->table = NULL;
	new->global_zone = new_zone(new);
	new->groups_list = NULL;

	new->copyright_head = NULL;
	new->copyright_tail = &new->copyright_head;

	return new;
}

void
tree_add_copyright_file(lexer_parse_tree *t, FILE* file, char* filename) {
	FILE_list_entry *p;
	p = xmalloc(sizeof *p);
	p->file = file;
	p->filename = filename;
	p->next =NULL;

	*(t->copyright_tail) = p ;
	t->copyright_tail = &(p->next);
}

FILE_list_entry*
tree_get_copyright_list(lexer_parse_tree *t)
{
	return t->copyright_head;
}

FILE_list_entry*
file_list_next(FILE_list_entry* file_list)
{
	return file_list->next;
}

FILE*
file_list_crt_file(FILE_list_entry* file_entry)
{
	return file_entry->file;
}

char*
file_list_crt_filename(FILE_list_entry* file_entry)
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
	FILE_list_entry* file_list ;

	for(file_list = tree_get_copyright_list(t); 
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

void
tree_add_group(lexer_parse_tree *t, char_group_defn *g)
{
	assert(t != NULL);
	assert(g->next_in_groups_list == NULL);

	g->next_in_groups_list = t->groups_list;
	t->groups_list = g;
}

void 
set_predefined_char_lexi_type(lexer_parse_tree* top_level, char* lexi_type, char* c_type)
{
	NStringT str;
	nstring_copy_cstring(&str, lexi_type);
	NStringT cstr;
	nstring_copy_cstring(&cstr, c_type);

	/* TODO assert(table_get_entry(tree_get_table(top_level), &str) == NULL) */
       	EntryT* entry = table_add_type(tree_get_table(top_level), &str, true);
	TypeT* type = entry_get_type(entry);
	type_map(type, &cstr);
	top_level->lexi_char_type = entry;
}

void 
set_predefined_string_lexi_type(lexer_parse_tree* top_level, char* lexi_type, char* c_type)
{
	NStringT str;
	nstring_copy_cstring(&str, lexi_type);
	NStringT cstr;
	nstring_copy_cstring(&cstr, c_type);

	/* TODO assert(table_get_entry(tree_get_table(top_level), &str) == NULL) */
       	EntryT* entry = table_add_type(tree_get_table(top_level), &str, true);
	TypeT* type = entry_get_type(entry);
	type_map(type, &cstr);
	top_level->lexi_string_type = entry;
}

void 
set_predefined_terminal_lexi_type(lexer_parse_tree* top_level, char* lexi_type)
{
	NStringT str;
	nstring_copy_cstring(&str, lexi_type);

	/* TODO assert(table_get_entry(tree_get_table(top_level), &str) == NULL) */
       	EntryT* entry = table_add_type(tree_get_table(top_level), &str, true);
	top_level->lexi_terminal_type = entry;
}

void 
set_predefined_int_lexi_type(lexer_parse_tree* top_level, char* lexi_type, char* c_type)
{
	NStringT str;
	nstring_copy_cstring(&str, lexi_type);
	NStringT cstr;
	nstring_copy_cstring(&cstr, c_type);

	/* TODO assert(table_get_entry(tree_get_table(top_level), &str) == NULL) */
       	EntryT* entry = table_add_type(tree_get_table(top_level), &str, true);
	TypeT* type = entry_get_type(entry);
	type_map(type, &cstr);
	top_level->lexi_int_type = entry;
}

EntryT* lexer_char_type(lexer_parse_tree* top_level)
{
	return top_level->lexi_char_type;
}

EntryT* lexer_string_type(lexer_parse_tree* top_level)
{
	return top_level->lexi_string_type;
}

EntryT* lexer_int_type(lexer_parse_tree* top_level)
{
	return top_level->lexi_int_type;
}

EntryT* lexer_terminal_type(lexer_parse_tree* top_level)
{
	return top_level->lexi_terminal_type;
}

