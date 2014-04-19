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
add_cmd_action(struct entry *ea, struct args_list *lhs, struct args_list *rhs)
{
	struct cmd *p;

	p = new_cmd(CMD_ACTION);
	p->u.act.called_act = ea;
	p->u.act.rhs = rhs;
	p->u.act.lhs = lhs;

	return p;
}

struct cmd *
add_cmd_pushzone(struct zone *z)
{
	struct cmd *p;

	p = new_cmd(CMD_PUSH_ZONE);
	p->u.s.z = z;
	p->u.s.is_beginendmarker_in_zone = 1;

	return p;
}

struct cmd *
add_cmd_popzone(struct zone *z, int is_endmarker_in_zone)
{
	struct cmd *p;

	p = new_cmd(CMD_POP_ZONE);
	p->u.s.z = z;
	p->u.s.is_beginendmarker_in_zone = is_endmarker_in_zone;

	return p;
}

static struct cmd_list *
new_cmd_list(void)
{
	struct cmd_list *p;

	p = xmalloc(sizeof *p);
	p->head = NULL;
	p->tail = &p->head;
	p->size = 0;
	p->nb_return = 0;

	localnames_init(&p->local_names);

	return p;
}

struct cmd_list *
add_cmd_list (void)
{
	struct cmd_list *p = new_cmd_list();

	return p;
}

struct LocalNamesT *
cmdlist_localnames(struct cmd_list *l)
{
	return &l->local_names;
}

