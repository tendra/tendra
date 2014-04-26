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
struct arg;

enum cmd_kind {
	CMD_RETURN,
	CMD_PUSH_ZONE,
	CMD_POP_ZONE,
	CMD_DISCARD,
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
			struct arg *lhs;
			struct arg *rhs;
		} act;
	} u;
};

struct cmd *add_cmd_return(char *name);
struct cmd *add_cmd_discard(void);
struct cmd *add_cmd_action(struct entry *, struct arg *, struct arg *);
struct cmd *add_cmd_mapping(char *map);

struct cmd *add_cmd_push_zone(struct zone *z);
struct cmd *add_cmd_pop_zone(struct zone *z, int is_endmarker_in_zone);
unsigned cmd_return_count(struct cmd *);

#endif

