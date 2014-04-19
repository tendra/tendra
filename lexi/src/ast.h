/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_AST_H
#define LEXI_AST_H

struct ast;
struct group;
struct character;
struct zone;

struct ast *init_ast(void);
int tree_zoneisglobal(struct ast *, struct zone *);
struct zone *tree_get_globalzone(struct ast *);
struct entry **tree_get_table(struct ast *);
struct group *tree_get_grouplist(struct ast *t);

int all_groups_empty(struct ast *t);

int tree_add_generated_key(struct ast *t);
void tree_add_group(struct ast *t, struct group *g);
struct group *tree_find_group(struct ast *t, struct group *b);

void set_predefined_char_lexi_type(struct ast *, char *, char *);
void set_predefined_string_lexi_type(struct ast *, char *, char *);
void set_predefined_int_lexi_type(struct ast *, char *, char *);
void set_predefined_terminal_lexi_type(struct ast *, char *);

struct entry *lexer_char_type(struct ast *);
struct entry *lexer_string_type(struct ast *);
struct entry *lexer_int_type(struct ast *);
struct entry *lexer_terminal_type(struct ast *);

#endif

