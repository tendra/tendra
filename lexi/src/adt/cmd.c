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

static struct arg *
new_arg(void)
{
	struct arg *p;

	p = xmalloc(sizeof *p);
	p->next = NULL;
	p->is_ref = false;

	return p;
}

struct arg *
add_arg(enum arg_kind kind, unsigned int d)
{
	struct arg *p;

	p = new_arg();
	p->kind    = kind;
	p->u.digit = d;

	return p;
}

struct arg *
add_ident(char *s)
{
	struct arg *p;

	p = new_arg();
	p->kind      = ARG_IDENT;
	p->u.literal = s;

	return p;
}

struct arg *
add_ref(char *s)
{
	struct arg *p;

	p = new_arg();
	p->kind         = ARG_IDENT;
	p->u.literal    = s;
	p->is_ref = true;

	return p;
}

struct arg *
add_terminal(char * s)
{
	struct arg *p;

	p = new_arg();
	p->kind      = ARG_TERMINAL;
	p->u.literal = s;

	return p;
}

struct arg *
add_none(void)
{
	struct arg *p;

	p = new_arg();
	p->kind      = ARG_NONE;
	p->u.literal = NULL;

	return p;
}

void
arg_out(struct arg *p, bool is_ref, int d, FILE *file)
{
	switch (p->kind) {
	case ARG_CHARP:
		error(ERROR_SERIOUS, "#* is not implemented yet at output level");
		break;

	case ARG_CHAR_NUM:
		/*TODO assert(p->u.digit < nb_of_chars);*/
		fprintf(file, "c%d", p->u.digit);
		break;

	case ARG_CHAR_COUNT:
		fprintf(file, "%d", d);
		break;

	case ARG_IDENT:
		if (p->is_ref) {
			/* TODO: assert(is_ref); */
			fprintf(file, "%s", p->u.literal);
		} else {
			if (is_ref) {
				fprintf(file, "(*%s)", p->u.literal);
			} else {
				fprintf(file, "%s", p->u.literal);
			}
		}
		break;

	case ARG_TERMINAL:
		fprintf(file, "%s", p->u.literal);
		break;

	case ARG_IGNORE:
		error(ERROR_SERIOUS, "Ignore symbol ! is not implemented yet at output level");
		/* TODO: implement */
		break;

	case ARG_RETURN:
		fprintf(file, "ZT1"); /* TODO: make prefixes option controllable or lct file controllable */
		break;

	case ARG_NONE:
	default:
		UNREACHED;
		break;
	}
}

static struct args_list *
new_args_list(void)
{
	struct args_list *p;

	p = xmalloc(sizeof *p);
	p->head = NULL;
	p->tail = &p->head;
	p->nb_return = 0;

	return p;
}

struct args_list *
add_args_list(void)
{
	struct args_list *p;

	p = new_args_list();

	return p;
}

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

