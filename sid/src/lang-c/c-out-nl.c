/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * c-out-nl.c - Output of non local name list ADT objects.
 *
 * This file implements the non local name list output routines used by SID.
 */

#include <assert.h>
#include <stddef.h>

#include <shared/bool.h>

#include "c-out-nl.h"
#include "../adt/action.h"
#include "c-code.h"
#include "c-out-key.h"
#include "c-out-types.h"

typedef struct NonLocalClosureT {
	COutputInfoT *info;
	SaveRStackT  *state;
	unsigned      indent;
} NonLocalClosureT;

static void
c_output_save_non_locals_1(COutputInfoT *info, NonLocalEntryT *non_local,
	SaveRStackT *non_local_state, RStackT *rstack,
	RuleT *handler_rule, TableT *table, unsigned indent)
{
	OStreamT   *ostream = c_out_info_ostream(info);
	EntryT     *entry   = non_local_entry_get_initialiser(non_local);
	EntryT     *type;
	bool       reference;
	EntryT     *translation;
	KeyT       *key;
	ActionT    *action;
	TypeTupleT *param;
	CCodeT     *code;
	bool       copies;
	TypeTupleT  args;
	TypeTupleT  result_args;
	SaveRStackT state;

	if (!entry) {
		return;
	}

	translation = rstack_get_translation(non_local_state, non_local->name,
		&type, &reference);
	key         = entry_key(entry);
	action      = entry_get_action(entry);
	param       = action_param(action);
	code        = action_get_code(action);

	c_output_key_message (info, "/* BEGINNING OF INITIALISER: ", key, " */",
		indent);
	c_output_open(info, indent);
	rstack_save_state(rstack, &state);
	rstack_push_frame(rstack);

	types_init(&args);
	if (!types_equal_zero_tuple(param)) {
		types_add_name_and_type(&args, translation, type, reference);
	}
	types_init(&result_args);
	types_add_name_and_type(&result_args, non_local->name, type, false);

	copies = c_output_required_copies(info, c_code_param(code),
		&args, rstack, &state, indent + C_INDENT_STEP, table);
	if (copies) {
		c_output_open(info, indent + C_INDENT_STEP);
	}

	rstack_save_state(rstack, &state);
	c_output_location(info, c_code_file(code), c_code_line(code));
	c_output_c_code_action(info, code, &args, &result_args, &state,
		handler_rule);
	c_output_location(info, ostream_name(ostream), ostream_line(ostream) + 1);
	rstack_pop_frame(rstack);

	if (copies) {
		c_output_close(info, indent + C_INDENT_STEP);
	}

	c_output_close(info, indent);
	c_output_key_message (info, "/* END OF INITIALISER: ", key, " */", indent);
	types_destroy(&result_args);
	types_destroy(&args);
}

static void
c_output_restore_non_locals_1(EntryT *from, EntryT *to, void *gclosure)
{
	/* XXX function pointer cast from void *? */
	NonLocalClosureT *closure = (NonLocalClosureT *) gclosure;
	COutputInfoT     *info    = closure->info;
	SaveRStackT      *state   = closure->state;
	unsigned          indent  = closure->indent;

	c_output_assign(info, to, from, state, state, indent);
}


/*
 * Externally visible functions
 */

void
c_output_non_locals(COutputInfoT *info, NonLocalListT *non_locals)
{
	OStreamT       *ostream = c_out_info_ostream(info);
	NonLocalEntryT *non_local;

	for (non_local = non_locals->head; non_local;
		non_local = non_local->next) {

		if (!c_out_info_get_split(info)) {
			write_cstring(ostream, "static ");
		}

		c_output_mapped_key(info, non_local->type);
		write_char(ostream, ' ');
		c_output_mapped_key(info, non_local->name);
		write_char(ostream, ';');
		write_newline(ostream);
	}
}

void
c_output_declare_non_locals(COutputInfoT *info, NonLocalListT *non_locals)
{
	OStreamT       *ostream = c_out_info_ostream(info);
	NonLocalEntryT *non_local;

	for (non_local = non_locals->head; non_local;
		non_local = non_local->next) {

		write_cstring(ostream, "extern ");
		c_output_mapped_key(info, non_local->type);
		write_char(ostream, ' ');
		c_output_mapped_key(info, non_local->name);
		write_char(ostream, ';');
		write_newline(ostream);
	}
}

void
c_output_save_non_locals(COutputInfoT *info, RuleT *rule, unsigned indent,
	RStackT *rstack, RStackT *non_local_stack, RuleT *handler_rule, TableT *table)
{
	OStreamT       *ostream    = c_out_info_ostream(info);
	NStringT       *in_prefix  = c_out_info_in_prefix(info);
	NonLocalListT  *non_locals = rule_non_locals(rule);
	NonLocalEntryT *non_local;
	SaveRStackT     state;
	SaveRStackT     non_local_state;

	for (non_local = non_locals->head; non_local; non_local = non_local->next) {
		EntryT *entry = table_add_generated_name(table);

		output_indent(c_out_info_info(info), indent);
		c_output_mapped_key(info, non_local->type);
		write_char(ostream, ' ');
		c_output_key(info, entry_key(entry), in_prefix);
		write_newline(ostream);
		rstack_add_translation(non_local_stack, non_local->name, entry,
		non_local->type, false);
		rstack_add_translation(rstack, entry, entry, non_local->type, false);
	}

	write_newline(ostream);
	rstack_save_state(rstack, &state);
	rstack_save_state(non_local_stack, &non_local_state);

	for (non_local = non_locals->head; non_local; non_local = non_local->next) {
		EntryT *type;
		bool   reference;
		EntryT *entry = rstack_get_translation(&non_local_state,
			non_local->name, &type, &reference);

		assert(entry != NULL && type == non_local->type && !reference);
		c_output_assign(info, non_local->name, entry, &state, &state, indent);
	}

	for (non_local = non_locals->head; non_local; non_local = non_local->next) {
		c_output_save_non_locals_1(info, non_local, &non_local_state,
			rstack, handler_rule, table, indent);
	}

	rstack_save_state(non_local_stack, rule_non_local_state(rule));
}

void
c_output_restore_non_locals(COutputInfoT *info, RuleT *rule, unsigned indent,
	RStackT *rstack, RStackT *non_local_stack)
{
	NonLocalClosureT closure;
	SaveRStackT      state;

	rstack_save_state(rstack, &state);
	closure.info   = info;
	closure.state  = &state;
	closure.indent = indent;
	rstack_apply_for_non_locals(non_local_stack, rule_non_local_state(rule),
		c_output_restore_non_locals_1, &closure);
}
