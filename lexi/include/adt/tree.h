/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_TREE_H
#define LEXI_TREE_H

struct lexer_parse_tree;
struct char_group_defn;
struct character;
struct zone;

struct lexer_parse_tree *init_lexer_parse_tree(void);
int tree_zoneisglobal(struct lexer_parse_tree *, struct zone *);
struct zone *tree_get_globalzone(struct lexer_parse_tree *);
struct EntryT **tree_get_table(struct lexer_parse_tree *);
struct char_group_defn *tree_get_grouplist(struct lexer_parse_tree *t);

int all_groups_empty(struct lexer_parse_tree *t);

int tree_add_generated_key(struct lexer_parse_tree *t);
void tree_add_group(struct lexer_parse_tree *t, struct char_group_defn *g);
struct char_group_defn *tree_find_group(struct lexer_parse_tree *t, struct char_group_defn *b);

void set_predefined_char_lexi_type(struct lexer_parse_tree *, char *, char *);
void set_predefined_string_lexi_type(struct lexer_parse_tree *, char *, char *);
void set_predefined_int_lexi_type(struct lexer_parse_tree *, char *, char *);
void set_predefined_terminal_lexi_type(struct lexer_parse_tree *, char *);

struct EntryT *lexer_char_type(struct lexer_parse_tree *);
struct EntryT *lexer_string_type(struct lexer_parse_tree *);
struct EntryT *lexer_int_type(struct lexer_parse_tree *);
struct EntryT *lexer_terminal_type(struct lexer_parse_tree *);

#endif

