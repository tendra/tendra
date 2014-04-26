/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/check.h>
#include <shared/xalloc.h>
#include <shared/error.h>

#include <adt/arg.h>
#include <adt/cmd.h>
#include <adt/zone.h>

static struct cmd *
new_cmd(enum cmd_kind kind)
{
	struct cmd *p;

	p = xmalloc(sizeof *p);
	p->kind = kind;
	p->next = NULL;

	return p;
}

struct cmd *
add_cmd_return(char *name)
{
	struct cmd *p;

	p = new_cmd(CMD_RETURN);
	p->u.name = name;

	return p;
}

struct cmd *
add_cmd_donothing(void)
{
	struct cmd *p;

	p = new_cmd(CMD_NOOP);

	return p;
}

struct cmd *
add_cmd_action(struct entry *ea, struct arg *lhs, struct arg *rhs)
{
	struct cmd *p;

	p = new_cmd(CMD_ACTION);
	p->u.act.ea  = ea;
	p->u.act.rhs = rhs;
	p->u.act.lhs = lhs;

	return p;
}

struct cmd *
add_cmd_push_zone(struct zone *z)
{
	struct cmd *p;

	p = new_cmd(CMD_PUSH_ZONE);
	p->u.s.z = z;
	p->u.s.is_beginendmarker_in_zone = 1;

	return p;
}

struct cmd *
add_cmd_pop_zone(struct zone *z, int is_endmarker_in_zone)
{
	struct cmd *p;

	p = new_cmd(CMD_POP_ZONE);
	p->u.s.z = z;
	p->u.s.is_beginendmarker_in_zone = is_endmarker_in_zone;

	return p;
}

struct cmd_list *
add_cmd_list(void)
{
	struct cmd_list *p;

	p = xmalloc(sizeof *p);
	p->head   = NULL;
	p->tail   = &p->head;
	p->locals = NULL;

	return p;
}

unsigned
cmd_return_count(struct cmd_list *cmds)
{
	struct cmd *p;
	unsigned n;

	n = 0;

	for (p = cmds->head; p != NULL; p = p->next) {
		switch (p->kind) {
		case CMD_RETURN:
			n++;
			break;

		case CMD_ACTION:
			n += arg_return_count(p->u.act.lhs);
			break;

		default:
			break;
		}
	}

	return n;
}

