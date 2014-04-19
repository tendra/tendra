/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef LEXI_CMD_H
#define LEXI_CMD_H

#include <stdbool.h>

struct zone;

#include "localnames.h"

enum arg_kind {
	ARG_CHARP,
	ARG_CHAR_NUM,
	ARG_CHAR_COUNT,
	ARG_IDENT,
	ARG_TERMINAL,
	ARG_IGNORE,
	ARG_RETURN,
	ARG_NONE
};

struct arg {
	enum arg_kind kind;
	struct arg *next;

	union {
		unsigned int digit;
		char *literal;
	} u;

	bool is_ref;
};

/* ordered */
struct args_list {
	struct arg  *head;
	struct arg **tail;
	int nb_return;
};

enum cmd_kind {
	CMD_RETURN,
	CMD_PUSH_ZONE,
	CMD_POP_ZONE,
	CMD_NOOP,
	CMD_ACTION
};

struct cmd {
	enum cmd_kind kind;
	struct cmd *next;

	union {
		char *name; /* token */
		struct {
			struct zone *z;
			int is_beginendmarker_in_zone;
		} s;
		struct {
			struct entry *called_act;
			struct args_list *lhs;
			struct args_list *rhs;
		} act;
	} u;
};

/* ordered */
struct cmd_list {
	struct cmd* head;
	struct cmd** tail;
	int size;
	struct LocalNamesT local_names;
	int nb_return;
};

struct arg *add_arg(enum arg_kind, unsigned int);
struct arg *add_ident(char *);
struct arg *add_ref(char *);
struct arg *add_terminal(char *);
struct arg *add_none(void);
void arg_out(struct arg *, bool, int, FILE *);
struct args_list *add_args_list(void);

struct cmd *add_cmd_return(char *name);
struct cmd *add_cmd_donothing(void);
struct cmd *add_cmd_action(struct entry *, struct args_list *, struct args_list *);
struct cmd *add_cmd_mapping(char *map);

struct cmd *add_cmd_pushzone(struct zone *z);
struct cmd *add_cmd_popzone(struct zone *z, int is_endmarker_in_zone);
struct cmd_list *add_cmd_list(void);

struct LocalNamesT *cmdlist_localnames(struct cmd_list *);

#endif

