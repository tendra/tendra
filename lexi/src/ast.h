/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_AST_H
#define LEXI_AST_H

struct group;
struct character;
struct zone;

struct ast {
	struct zone *global;

	struct group *groups;

	struct entry *table; /* Actions and types */

	struct entry *lexi_char_type;     /* for #0 arguments */
	struct entry *lexi_string_type;   /* for #* arguments */
	struct entry *lexi_int_type;      /* for #n arguments */
	struct entry *lexi_terminal_type; /* for $ = returns  */
};

struct ast *init_ast(void);
int all_groups_empty(struct ast *t);
int tree_add_generated_key(struct ast *t);
struct group *tree_find_group(struct ast *t, struct group *b);
void set_builtin_type(struct ast *ast, struct entry **e, char *lexi_type);

#endif

