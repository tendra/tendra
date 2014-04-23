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
struct args_list;

#include "localnames.h"

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
			struct entry *ea;
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
	int return_count;
};

struct cmd *add_cmd_return(char *name);
struct cmd *add_cmd_donothing(void);
struct cmd *add_cmd_action(struct entry *, struct args_list *, struct args_list *);
struct cmd *add_cmd_mapping(char *map);

struct cmd *add_cmd_push_zone(struct zone *z);
struct cmd *add_cmd_pop_zone(struct zone *z, int is_endmarker_in_zone);
struct cmd_list *add_cmd_list(void);

#endif

