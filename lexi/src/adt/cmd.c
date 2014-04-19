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
	p->is_reference = false;

	return p;
}

struct arg *
add_arg(enum arg_type t, unsigned int d)
{
	struct arg *p;

	p = new_arg();
	p->type    = t;
	p->u.digit = d;

	return p;
}

struct arg *
add_identifier_arg(char *s)
{
	struct arg *p;

	p = new_arg();
	p->type      = arg_identifier;
	p->u.literal = s;

	return p;
}

struct arg *
add_reference_arg(char *s)
{
	struct arg *p;

	p = new_arg();
	p->type         = arg_identifier;
	p->u.literal    = s;
	p->is_reference = true;

	return p;
}

struct arg *
add_terminal_arg(char * s)
{
	struct arg *p;

	p = new_arg();
	p->type      = arg_terminal;
	p->u.literal = s;

	return p;
}

struct arg *
add_none_arg(void)
{
	struct arg *p;

	p = new_arg();
	p->type      = arg_none;
	p->u.literal = NULL;

	return p;
}

void
arg_output(struct arg *p, bool is_ref, int d, FILE *file)
{
	switch (p->type) {
	case arg_charP:
		error(ERROR_SERIOUS, "#* is not implemented yet at output level"); 
		break;

	case arg_char_nb:
		/*TODO assert(p->u.digit<nb_of_chars);*/
		fprintf(file, "c%d", p->u.digit);
		break;

	case arg_nb_of_chars:
		fprintf(file, "%d", d);
		break;

	case arg_identifier:
		if (p->is_reference) {
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

	case arg_terminal:
		fprintf(file, "%s", p->u.literal);
		break;

	case arg_ignore:
		error(ERROR_SERIOUS, "Ignore symbol ! is not implemented yet at output level"); 
		/*TODO implement*/
		break;

	case arg_return_terminal:
		fprintf(file, "ZT1"); /*TODO make prefixes option controllable or lct file controllable*/
		break;

	case arg_none:
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
	p->nb_return_terminal = 0;

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
new_cmd(enum cmd_type type)
{
	struct cmd *p;

	p = xmalloc(sizeof *p);
	p->type = type;
	p->next = NULL;

	return p;
}

struct cmd *
add_cmd_return_terminal(char *name)
{
	struct cmd *p;

	p = new_cmd(return_terminal);
	p->u.name = name;

	return p;
}

struct cmd *
add_cmd_donothing(void)
{
	struct cmd *p;

	p = new_cmd(do_nothing);

	return p;
}

struct cmd *
add_cmd_action(struct entry *ea, struct args_list *lhs, struct args_list *rhs)
{
	struct cmd *p;

	p = new_cmd(action_call);
	p->u.act.called_act = ea;
	p->u.act.rhs = rhs;
	p->u.act.lhs = lhs;

	return p;
}

struct cmd *
add_cmd_pushzone(struct zone *z)
{
	struct cmd *p;

	p = new_cmd(push_zone);
	p->u.s.z = z;
	p->u.s.is_beginendmarker_in_zone = 1;

	return p;
}

struct cmd *
add_cmd_popzone(struct zone *z, int is_endmarker_in_zone)
{
	struct cmd *p;

	p = new_cmd(pop_zone);
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
	p->nb_return_terminal = 0;

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

