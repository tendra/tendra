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
#include "letter.h"
#include "zone.h"


struct lexer_parse_tree_tag {
	struct zone_tag *global_zone;

	FILE *copyright_file;

	unsigned int no_total_groups;
	char_group_list groups_list;

	TableT table; /* Actions and types */

	EntryT* lexi_char_type;    /*  for #0 arguments */
	EntryT* lexi_string_type;  /*  for #* arguments */
	EntryT* lexi_int_type;     /*  for #n arguments */
	EntryT* lexi_terminal_type;     /*  for $ = returns */

	letter_translation *letters;
	letter last_letter_code;
	letter eof_letter_code;
	letter next_generated_key;
};


/*
Initialize the main parse tree
*/
lexer_parse_tree*
init_lexer_parse_tree(void) {
  lexer_parse_tree *t;

  t = xmalloc(sizeof *t);

  int i = 0;
  letter_translation* trans;
  t->letters = NULL;
  
  /* This might change once we add support for other charsets */
  for(i=0; i<256; i++) {
    trans=new_letter_translation(char_letter);
    trans->letter_code=i;
    trans->u.ch=i;
    tree_add_translation(t, trans);
  }
  trans=new_letter_translation(eof_letter);
  t->eof_letter_code=i;
  trans->letter_code=i++;
  tree_add_translation(t, trans);

  trans=new_letter_translation(last_letter);
  t->last_letter_code=i;
  trans->letter_code=i++;
  tree_add_translation(t, trans);

  t->next_generated_key=i;

  t->no_total_groups=0;
  t->global_zone=new_zone("global",t);
  t->groups_list.head=NULL;
  (t->groups_list.tail)=&(t->groups_list.head);

  return t;
}

int
tree_zoneisglobal(lexer_parse_tree *t, zone *z)
{
	assert(t != NULL);
	assert(z != NULL);

	return tree_get_globalzone(t) == z;
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

	return t->table;
}

letter
tree_get_lastlettercode(lexer_parse_tree *t)
{
	assert(t != NULL);

	return t->last_letter_code;
}

letter
tree_get_eoflettercode(lexer_parse_tree *t)
{
	assert(t != NULL);

	return t->eof_letter_code;
}

char_group_list *
tree_get_grouplist(lexer_parse_tree *t)
{
	assert(t != NULL);

	return &t->groups_list;
}

unsigned int
tree_get_totalnogroups(lexer_parse_tree *t)
{
	assert(t != NULL);

	/* TODO: instead of storing this, we can count on the fly */
	return t->no_total_groups;
}

/* TODO: this is silly, and can go when tree_get_totalnogroups() runs on the fly */
void
tree_inctotalnogroups(lexer_parse_tree *t)
{
	assert(t != NULL);

	t->no_total_groups++;
}

int
all_groups_empty(lexer_parse_tree *t)
{
	char_group *g;

	assert(t != NULL);

	for (g = t->groups_list.head; g != NULL; g = g->next_in_groups_list) {
		if (!is_group_empty(g)) {
			return 0;
		}
	}

	return 1;
}

letter_translation *
tree_get_translation(lexer_parse_tree *t, character *c)
{
	assert(t != NULL);
	assert(c != NULL);

	return tree_get_translationl(t, c->ch);
}

/* TODO: this is only used in a couple of places, which ought to be rewritten */
letter_translation *
tree_get_translationl(lexer_parse_tree *t, letter l)
{
	letter_translation *p;

	assert(t != NULL);

	for (p = t->letters; p != NULL; p = p->next) {
		if (p->letter_code == l) {
			return p;
		}
	}

	return NULL;
}

void
tree_add_translation(lexer_parse_tree *t, letter_translation *trans)
{
	assert(t != NULL);
	assert(trans != NULL);

	trans->next = t->letters;
	t->letters = trans;
}

/* TODO: I am dubious about requiring .next_generated_key */
letter
tree_add_generated_key(lexer_parse_tree *t)
{
	assert(t != NULL);

	return t->next_generated_key++;
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

