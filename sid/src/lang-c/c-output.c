/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * c-output.c - Output routines.
 *
 * This file implements the SID output routines.
 */

#include <assert.h>
#include <string.h>
#include <errno.h>

#include <shared/check.h>
#include <shared/error.h>

#include <exds/dstring.h>
#include <exds/ostream.h>

#include "c-output.h"
#include "../adt/action.h"
#include "../adt/basic.h"
#include "c-code.h"
#include "c-out-key.h"
#include "c-out-nl.h"
#include "c-out-types.h"
#include "../output.h"
#include "../adt/name.h"
#include "../adt/rstack.h"
#include "../adt/rule.h"
#include "../adt/type.h"

typedef struct COutClosureT {
	COutputInfoT *		info;
	TableT *			table;
	EntryT *			predicate_id;
	EntryT *			predicate_type;
	unsigned			error_terminal;
} COutClosureT;

static unsigned out_current_label;

static void
c_output_indent(COutputInfoT *info, unsigned indent)
{
	output_indent(c_out_info_info(info), indent);
}

static void
c_output_identification(COutputInfoT *info)
{
	OStreamT *ostream = c_out_info_ostream(info);

	write_cstring(ostream, "/*");
	write_newline(ostream);
	write_cstring(ostream, " * Automatically generated from the files:");
	write_newline(ostream);
	write_cstring(ostream, " *\t");
	write_cstring(ostream, c_out_info_source_name(info));
	write_newline(ostream);
	write_cstring(ostream, " * and");
	write_newline(ostream);
	write_cstring(ostream, " *\t");
	write_cstring(ostream, c_out_info_c_source_name(info));
	write_newline(ostream);
	write_cstring(ostream, " * by:");
	write_newline(ostream);
	write_cstring(ostream, " *\t");
	write_cstring(ostream, c_out_info_program_name(info));
	write_newline(ostream);
	write_cstring(ostream, " */");
	write_newline(ostream);
	write_newline(ostream);
}

static void
c_output_declaration_1(COutputInfoT *info, RuleT *rule)
{
	OStreamT *ostream = c_out_info_ostream(info);
	EntryT   *entry   = rule_entry(rule);

	if (rule_is_required(rule)) {
		write_cstring(ostream, "extern void ");
	} else if (rule_needs_function(rule)) {
		if (c_out_info_get_split(info) != 0) {
			write_cstring(ostream, "extern void ");
		} else {
			write_cstring(ostream, "static void ");
		}
	} else {
		return;
	}

	c_output_mapped_key(info, entry);
	c_output_type_decl(info, rule_param(rule), rule_result(rule));
	write_char(ostream, ';');
	write_newline(ostream);
}

static void
c_output_declaration(EntryT *entry, void *gclosure)
{
	if (entry_is_rule(entry)) {
		RuleT        *rule = entry_get_rule(entry);
		COutputInfoT *info = gclosure;

		c_output_declaration_1(info, rule);
	}
}

static void
c_output_ext_declaration_1(COutputInfoT *info, RuleT *rule)
{
	OStreamT *ostream = c_out_info_ostream(info);
	EntryT   *entry   = rule_entry(rule);

	if (rule_is_required(rule)) {
		write_cstring(ostream, "extern void ");
	} else {
		return;
	}

	c_output_mapped_key(info, entry);
	c_output_type_decl(info, rule_param(rule), rule_result(rule));
	write_char(ostream, ';');
	write_newline(ostream);
}

static void
c_output_ext_declaration(EntryT *entry, void *gclosure)
{
	if (entry_is_rule(entry)) {
		RuleT        *rule = entry_get_rule(entry);
		COutputInfoT *info = gclosure;

		c_output_ext_declaration_1(info, rule);
	}
}

static void
c_output_error_terminal(COutputInfoT *info, unsigned error_terminal)
{
	OStreamT *ostream = c_out_info_ostream(info);

	if (c_out_info_get_numeric_terminals(info)) {
		write_unsigned(ostream, error_terminal);
	} else {
		write_cstring(ostream, "(ERROR_TERMINAL)");
	}
}

static void
c_output_terminal_1(COutputInfoT *info, EntryT *entry)
{
	OStreamT *ostream = c_out_info_ostream(info);
	BasicT   *basic   = entry_get_basic(entry);

	write_cstring(ostream, "#define ");
	c_output_mapped_key(info, entry);
	write_cstring(ostream, " (");
	write_unsigned(ostream, basic_terminal(basic));
	write_char(ostream, ')');
	write_newline(ostream);
}

static void
c_output_terminal(EntryT *entry, void *gclosure)
{
	if (entry_is_basic(entry)) {
		COutputInfoT *info = gclosure;

		c_output_terminal_1(info, entry);
	}
}

static void
c_output_static_vars_1(EntryT *entry, void *gclosure)
{
	if (entry_is_rule(entry)) {
		COutputInfoT *info = gclosure;
		RuleT        *rule = entry_get_rule(entry);

		c_output_non_locals(info, rule_non_locals(rule));
	}
}

static void
c_output_static_vars_2(EntryT *entry, void *gclosure)
{
	if (entry_is_rule(entry)) {
		COutputInfoT *info = gclosure;
		RuleT        *rule = entry_get_rule(entry);

		c_output_declare_non_locals(info, rule_non_locals(rule));
	}
}

static void
c_output_static_vars(COutputInfoT *info, GrammarT *grammar, BoolT def)
{
	OStreamT *ostream        = c_out_info_ostream(info);
	TableT   *table          = grammar_table(grammar);
	EntryT   *predicate_type = grammar_get_predicate_type(grammar);

	if (def) {
		write_cstring (ostream, "/* BEGINNING OF STATIC VARIABLES */");
		write_newline(ostream);
		write_newline(ostream);
	}

	if (predicate_type) {
		if (def) {
			if (c_out_info_get_split(info) == 0) {
				write_cstring(ostream, "static ");
			}
		} else {
			write_cstring(ostream, "extern ");
		}

		c_output_mapped_key(info, predicate_type);
		write_char(ostream, ' ');
		c_output_key(info, entry_key(grammar_get_predicate_id(grammar)),
			c_out_info_in_prefix(info));
		write_char(ostream, ';');
		write_newline(ostream);
	}

	if (def) {
		table_iter(table, c_output_static_vars_1, info);
		write_newline(ostream);
	} else {
		table_iter(table, c_output_static_vars_2, info);
	}
}

static void
c_out_reset_labels(void)
{
	out_current_label = 0;
}

static void
c_output_label(COutputInfoT *info, unsigned label, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);
	NStringT *prefix  = c_out_info_label_prefix(info);

	c_output_indent(info, indent - C_INDENT_FOR_LABEL);
	write_nstring(ostream, prefix);
	write_unsigned(ostream, label);
	write_cstring(ostream, ":;");
	write_newline(ostream);
}

static void
c_output_jump(COutputInfoT *info, unsigned label, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);
	NStringT *prefix  = c_out_info_label_prefix(info);

	c_output_indent(info, indent);
	write_cstring(ostream, "goto ");
	write_nstring(ostream, prefix);
	write_unsigned(ostream, label);
	write_char(ostream, ';');
	write_newline(ostream);
}

static void
c_output_key_label(COutputInfoT *info, KeyT *key, unsigned label,
	unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_indent(info, indent - C_INDENT_FOR_LABEL);
	c_output_label_key(info, key, label);
	write_cstring(ostream, ":;");
	write_newline(ostream);
}

static void
c_output_key_jump(COutputInfoT *info, KeyT *key, unsigned label, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_indent(info, indent);
	write_cstring(ostream, "goto ");
	c_output_label_key(info, key, label);
	write_char(ostream, ';');
	write_newline(ostream);
}

static void
c_output_switch(COutputInfoT *info, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_indent(info, indent);
	write_cstring(ostream, "switch (CURRENT_TERMINAL) {");
	write_newline(ostream);
}

static void
c_output_case(COutputInfoT *info, EntryT *entry, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_indent(info, indent + C_INDENT_STEP - C_INDENT_FOR_CASE);
	write_cstring(ostream, "case ");
	c_output_terminal_entry(info, entry);
	write_char(ostream, ':');
	write_newline(ostream);
}

static void
c_output_error_case(COutputInfoT *info, unsigned error_terminal, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_indent(info, indent + C_INDENT_STEP - C_INDENT_FOR_CASE);
	write_cstring(ostream, "case ");
	c_output_error_terminal(info, error_terminal);
	write_char(ostream, ':');
	write_newline(ostream);
}

static void
c_output_default(COutputInfoT *info, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_indent(info, indent + C_INDENT_STEP - C_INDENT_FOR_CASE);
	write_cstring(ostream, "default:");
	write_newline(ostream);
}

static void
c_output_bitvec_cases(COutputInfoT *info, TableT *table, BitVecT *bitvec, unsigned indent)
{
	OStreamT *ostream  = c_out_info_ostream(info);
	unsigned terminal = bitvec_first_bit(bitvec);
	unsigned count    = 0;

	do {
		EntryT *entry = table_get_basic_by_number(table, terminal);

		if (count++ == 0) {
			c_output_indent(info, indent + C_INDENT_STEP - C_INDENT_FOR_CASE);
		} else {
			write_char(ostream, ' ');
		}

		write_cstring(ostream, "case ");
		c_output_terminal_entry(info, entry);
		write_char(ostream, ':');

		if (count == 4) {
			write_newline(ostream);
			count = 0;
		}
	} while (bitvec_next_bit(bitvec, &terminal));

	if (count != 0) {
		write_newline(ostream);
	}
}

static void
c_output_break(COutputInfoT *info, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_indent(info, indent);
	write_cstring(ostream, "break;");
	write_newline(ostream);
}

static void
c_output_return(COutputInfoT *info, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_indent(info, indent);
	write_cstring(ostream, "return;");
	write_newline(ostream);
}

static void
c_output_error_if(COutputInfoT *info, unsigned error_terminal, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_indent(info, indent);
	write_cstring(ostream, "if ((CURRENT_TERMINAL) == ");
	c_output_error_terminal(info, error_terminal);
	write_cstring(ostream, ") {");
	write_newline(ostream);
}

static void
c_output_else(COutputInfoT *info, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_indent(info, indent);
	write_cstring(ostream, "} else {");
	write_newline(ostream);
}

static void
c_output_restore(COutputInfoT *info, RuleT *handler_rule, BoolT outer_level,
	unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	if (outer_level) {
		c_output_return(info, indent);
	} else {
		c_output_indent(info, indent);
		write_cstring(ostream, "RESTORE_LEXER;");
		write_newline(ostream);
		c_output_jump(info, rule_get_handler_label(handler_rule), indent);
	}
}

static void
c_output_check(COutputInfoT *info, RuleT *handler_rule, BoolT outer_level,
	unsigned error_terminal, unsigned indent)
{
	c_output_error_if (info, error_terminal, indent);
	c_output_restore(info, handler_rule, outer_level, indent + C_INDENT_STEP);
	c_output_close(info, indent);
}

static void
c_output_advance(COutputInfoT *info, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_indent(info, indent);
	write_cstring(ostream, "ADVANCE_LEXER;");
	write_newline(ostream);
}

static void
c_output_unreachable(COutputInfoT *info, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_indent(info, indent);
	if (c_out_info_get_unreachable(info)) {
		write_cstring(ostream, "UNREACHED;");
	} else {
		write_cstring (ostream, "/*UNREACHED*/");
	}
	write_newline(ostream);
}

static void
c_output_basic_extract(COutputInfoT *info, CCodeT *code, ItemT *item, RuleT *handler_rule,
	KeyT *key, SaveRStackT *state, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_key_message (info, "/* BEGINNING OF EXTRACT: ", key, " */",
		indent);
	c_output_open(info, indent);
	c_output_location(info, c_code_file(code), c_code_line(code));
	c_output_c_code_basic(info, code, item_result(item), state, handler_rule);
	c_output_location(info, ostream_name(ostream), ostream_line(ostream) + 1);
	c_output_close(info, indent);
	c_output_key_message (info, "/* END OF EXTRACT: ", key, " */", indent);
}

static void
c_output_basic_in_alt(COutputInfoT *info, ItemT *item, RuleT *handler_rule,
	BoolT need_switch, BoolT need_check, BoolT outer_level,
	unsigned error_terminal, SaveRStackT *state, unsigned indent)
{
	EntryT  *entry       = item_entry(item);
	KeyT    *key         = entry_key(entry);
	BasicT  *basic       = entry_get_basic(entry);
	CCodeT  *code        = basic_get_result_code(basic);
	unsigned code_indent = need_switch ? indent + C_INDENT_STEP : indent;

	if (need_switch) {
		c_output_switch (info, indent);
		c_output_case(info, entry, indent);
		if (code) {
			c_output_basic_extract(info, code, item, handler_rule, key, state, code_indent);
		}
		c_output_break(info, code_indent);
		if (need_check) {
			c_output_error_case(info, error_terminal, indent);
			c_output_restore(info, handler_rule, outer_level, code_indent);
		}
		c_output_default(info, indent);
		c_output_jump(info, rule_get_handler_label(handler_rule), code_indent);
		c_output_close(info, indent);
	} else {
		assert(!need_check);
		if (code) {
			c_output_basic_extract(info, code, item, handler_rule, key, state, code_indent);
		}
	}
	c_output_advance(info, indent);
}

static void
c_output_tail_call(COutputInfoT *info, ItemT *item, RuleT *handler_rule,
	BoolT need_check, BoolT outer_level, unsigned error_terminal,
	RStackT *rstack, RStackT *non_local_stack, SaveRStackT *state,
	unsigned indent)
{
	unsigned  code_indent = need_check ? indent + C_INDENT_STEP : indent;
	EntryT   *entry       = item_entry(item);
	RuleT    *rule        = entry_get_rule(entry);
	KeyT     *key         = entry_key(entry);

	if (need_check) {
		c_output_error_if (info, error_terminal, indent);
		c_output_restore(info, handler_rule, outer_level, code_indent);
		c_output_else(info, indent);
	}

	c_output_restore_non_locals(info, rule, indent, rstack, non_local_stack);
	c_output_tail_decls(info, item_param(item), state, rule_param(rule),
		rule_rstack_state(rule), code_indent);
	c_output_key_jump(info, key, rule_get_start_label(rule), code_indent);
	if (need_check) {
		c_output_close(info, indent);
	}
}

/* TODO: prototypes to the top */
static BoolT c_output_rule(COutputInfoT *, RuleT *, RuleT *, EntryListT *, BoolT,
	EntryT *, unsigned, unsigned, RStackT *, RStackT *, TableT *);

static BoolT
c_output_rule_in_alt(COutputInfoT *info, ItemT *item, RuleT *handler_rule,
	EntryListT *call_list, BoolT need_check, BoolT outer_level,
	EntryT *predicate_id, unsigned error_terminal, unsigned indent,
	RStackT *rstack, RStackT *non_local_stack, TableT *table, BoolT *reachable_ref)
{
	OStreamT *ostream   = c_out_info_ostream(info);
	EntryT   *entry     = item_entry(item);
	RuleT    *rule      = entry_get_rule(entry);
	KeyT     *key       = entry_key(entry);
	BoolT     tail_call = (item_is_tail_call(item) &&
	rule_is_being_output(rule));
	SaveRStackT state;

	rstack_save_state(rstack, &state);
	if (item_is_inlinable(item)
		&& (tail_call
			|| !(rule_is_being_output(rule)
				|| rule_get_call_count(rule) > 1))) {

		c_output_key_message (info, "/* BEGINNING OF INLINE: ", key, " */",
			indent);

		if (tail_call) {
			c_output_tail_call(info, item, handler_rule, need_check,
			outer_level, error_terminal, rstack,
			non_local_stack, &state, indent);
			*reachable_ref = FALSE;
		} else {
			unsigned code_indent = indent + C_INDENT_STEP;
			BoolT    copies;

			c_output_open(info, indent);
			rstack_push_frame(rstack);
			copies = c_output_required_copies(info, rule_param(rule),
				item_param(item), rstack, &state, code_indent, table);
			if (copies) {
				c_output_open(info, code_indent);
				code_indent += C_INDENT_STEP;
			}
			rstack_save_state(rstack, &state);
			rstack_push_frame(rstack);
			rstack_compute_formal_inlining(rstack, rule_param(rule),
				item_param(item));
			rstack_compute_formal_inlining(rstack, rule_result(rule),
				item_result(item));
			rstack_save_state(rstack, rule_rstack_state(rule));
			if (!c_output_rule(info, rule, handler_rule,
				item_is_tail_call(item) ? call_list : rule_call_list(rule),
				need_check, predicate_id, error_terminal, code_indent,
				rstack, non_local_stack, table)) {
				*reachable_ref = FALSE;
			}
			rstack_pop_frame(rstack);
			if (copies) {
				c_output_close(info, indent + C_INDENT_STEP);
			}
			rstack_pop_frame(rstack);
			c_output_close(info, indent);
		}
		c_output_key_message (info, "/* END OF INLINE: ", key, " */", indent);
		return FALSE;
	}

	if (need_check && outer_level) {
		c_output_check(info, handler_rule, TRUE, error_terminal, indent);
	}
	c_output_indent(info, indent);
	c_output_mapped_key(info, entry);
	write_cstring(ostream, " (");
	c_output_rule_params(info, item_param(item), item_result(item), &state);
	write_cstring(ostream, ");");
	write_newline(ostream);

	return TRUE;
}

static void
c_output_action_in_alt(COutputInfoT *info, ItemT *item, RuleT *handler_rule,
	BoolT need_check, BoolT outer_level, unsigned error_terminal,
	RStackT *rstack, unsigned indent, TableT *table)
{
	OStreamT   *ostream = c_out_info_ostream(info);
	EntryT     *entry   = item_entry(item);
	ActionT    *action  = entry_get_action(entry);
	KeyT       *key     = entry_key(entry);
	CCodeT     *code    = action_get_code(action);
	SaveRStackT state;
	BoolT       copies;

	if (need_check) {
		c_output_check(info, handler_rule, outer_level, error_terminal,
		indent);
	}

	c_output_key_message (info, "/* BEGINNING OF ACTION: ", key, " */",
		indent);
	c_output_open(info, indent);
	rstack_save_state(rstack, &state);
	rstack_push_frame(rstack);
	copies = c_output_required_copies(info, c_code_param(code),
		item_param(item), rstack, &state,
	indent + C_INDENT_STEP, table);
	if (copies) {
		c_output_open(info, indent + C_INDENT_STEP);
	}
	rstack_save_state(rstack, &state);
	c_output_location(info, c_code_file(code), c_code_line(code));

	c_output_c_code_action(info, code, item_param(item),
	item_result(item), &state, handler_rule);
	c_output_location(info, ostream_name(ostream), ostream_line(ostream) + 1);
	rstack_pop_frame(rstack);
	if (copies) {
		c_output_close(info, indent + C_INDENT_STEP);
	}
	c_output_close(info, indent);
	c_output_key_message (info, "/* END OF ACTION: ", key, " */", indent);
}

static void
c_output_predicate_in_alt(COutputInfoT *info, RuleT *rule, ItemT *item,
	ItemT *initial, RuleT *handler_rule, BoolT needed_switch,
	BoolT need_check, BoolT outer_level, EntryT *predicate_id,
	unsigned error_terminal, RStackT *rstack, unsigned indent, TableT *table)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_action_in_alt(info, item, handler_rule, need_check, outer_level,
		error_terminal, rstack, indent, table);
	c_output_indent(info, indent);
	write_cstring(ostream, "if (!");
	c_output_key(info, entry_key(predicate_id), c_out_info_in_prefix(info));
	write_cstring(ostream, ")");
	write_newline(ostream);

	if (item == initial && !needed_switch) {
		unsigned label = c_out_next_label();

		c_output_jump(info, label, indent + C_INDENT_STEP);
		rule_set_next_label(rule, label);
	} else {
		c_output_jump(info, rule_get_handler_label(handler_rule),
			indent + C_INDENT_STEP);
	}
}

static BoolT
c_output_alt(COutputInfoT *info, AltT *alt, RuleT *rule, RuleT *handler_rule,
	EntryListT *call_list, BoolT need_switch, BoolT need_check,
	BoolT outer_level, EntryT *predicate_id, unsigned error_terminal,
	unsigned indent, RStackT *rstack, RStackT *non_local_stack, TableT *table)
{
	ItemT    *initial       = alt_item_head(alt);
	BoolT     needed_switch = need_switch;
	unsigned  code_indent   = indent + C_INDENT_STEP;
	BoolT     reachable     = TRUE;
	ItemT    *item;
	SaveRStackT state;

	rstack_push_frame(rstack);
	rstack_compute_local_renaming(rstack, alt_names(alt), rule_result(rule),
		table);
	rstack_save_state(rstack, &state);
	c_output_open(info, indent);
	c_output_alt_names(info, alt_names(alt), rule_result(rule), &state,
		code_indent);

	for (item = initial; item; item = item_next(item)) {
		switch (item_type(item))EXHAUSTIVE {
		case ET_BASIC:
			c_output_basic_in_alt(info, item, handler_rule, need_switch,
				need_check, outer_level, error_terminal, &state, code_indent);
			need_switch = TRUE;
			need_check  = FALSE;
			break;

		case ET_RULE:
			need_check = c_output_rule_in_alt(info, item, handler_rule, call_list,
				need_check, outer_level, predicate_id, error_terminal, code_indent,
				rstack, non_local_stack, table, &reachable);
			need_switch = TRUE;
			break;

		case ET_PREDICATE:
			c_output_predicate_in_alt(info, rule, item, initial, handler_rule,
				needed_switch, need_check, outer_level, predicate_id,
				error_terminal, rstack, code_indent, table);
			need_switch = TRUE;
			need_check  = FALSE;
			break;

		case ET_ACTION:
			c_output_action_in_alt(info, item, handler_rule, need_check,
				outer_level, error_terminal, rstack, code_indent, table);
				need_check = FALSE;
				break;

		case ET_RENAME:
			if (need_check) {
				c_output_check(info, handler_rule, outer_level,
					error_terminal, code_indent);
			}
			c_output_rename(info, item_param(item), item_result(item),
				&state, code_indent);
			need_check = FALSE;
			break;

		case ET_NON_LOCAL:
		case ET_NAME:
		case ET_TYPE:
			UNREACHED;
		}
		outer_level = FALSE;
	}

	if (reachable) {
		if (need_check) {
			c_output_check(info, handler_rule, outer_level, error_terminal,
				code_indent);
		}
		if (item_is_predicate(initial) && (!needed_switch)) {
			c_output_jump(info, rule_get_end_label(rule), code_indent);
			reachable = FALSE;
		}
	}

	c_output_close(info, indent);
	if (!reachable) {
		c_output_unreachable(info, indent);
	}
	rstack_pop_frame(rstack);

	return reachable;
}

static BoolT
c_output_rule(COutputInfoT *info, RuleT *rule, RuleT *handler_rule,
	EntryListT *call_list, BoolT need_check, EntryT *predicate_id,
	unsigned error_terminal, unsigned indent, RStackT *rstack,
	RStackT *non_local_stack, TableT *table)
{
	EntryT        *entry            = rule_entry(rule);
	KeyT          *key              = entry_key(entry);
	EntryListT    *predicate_firsts = rule_predicate_first(rule);
	BoolT          predicates       = (!entry_list_is_empty(predicate_firsts));
	RuleT         *old_handler_rule = handler_rule;
	BoolT          outer_level      = (old_handler_rule == rule);
	BoolT          reachable        = TRUE;
	unsigned       code_indent      = indent;
	NonLocalListT *non_locals       = rule_non_locals(rule);
	BoolT          has_non_locals   = (!non_local_list_is_empty(non_locals));
	AltT          *handler          = rule_get_handler(rule);
	BoolT          full_first_set   = bitvec_is_full(rule_first_set(rule));
	BoolT          one_alt          = rule_has_one_alt(rule);

	assert(!rule_is_being_output(rule));
	rule_being_output(rule);
	rule_set_end_label(rule, c_out_next_label());

	if (need_check && (predicates || has_non_locals || one_alt)) {
		c_output_check(info, handler_rule, outer_level, error_terminal, indent);
		need_check = FALSE;
	}

	if (outer_level) {
		rule_set_handler_label(rule, c_out_next_label());
	} else if ((handler != NULL) || has_non_locals) {
		handler_rule = rule;
		rule_set_handler_label(rule, c_out_next_label());
	}

	if (entry_list_contains(call_list, entry)) {
		unsigned label = c_out_next_label();

		c_output_key_label(info, key, label, indent);
			rule_set_start_label(rule, label);
	}

	if (has_non_locals) {
		c_output_open(info, indent);
		code_indent += C_INDENT_STEP;
		rstack_push_frame(rstack);
		rstack_push_frame(non_local_stack);
		c_output_save_non_locals(info, rule, code_indent, rstack,
		non_local_stack, handler_rule, table);
	}

	if (one_alt) {
		if (!rule_has_empty_alt(rule)) {
			AltT *alt = rule_alt_head(rule);

			reachable = c_output_alt(info, alt, rule, handler_rule, call_list,
				TRUE, need_check, outer_level, predicate_id, error_terminal,
				code_indent, rstack, non_local_stack, table);
		} else {
			if (need_check) {
				c_output_check(info, handler_rule, outer_level, error_terminal, code_indent);
			}
			reachable  = TRUE;
		}
	} else {
		BoolT non_predicate_alts = TRUE;
		AltT *see_through_alt    = rule_see_through_alt(rule);
		AltT *alt;

		if (predicates) {
			non_predicate_alts = FALSE;
			for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
				ItemT *item = alt_item_head(alt);

				if (!item_is_predicate(item)) {
					non_predicate_alts = TRUE;
					continue;
				}

				(void) c_output_alt(info, alt, rule, handler_rule,
					call_list, FALSE, FALSE, FALSE, predicate_id,
					error_terminal, code_indent, rstack, non_local_stack, table);
				c_output_label(info, rule_get_next_label(rule), code_indent);
			}
		}

		if (non_predicate_alts) {
			reachable = FALSE;
			c_output_switch (info, code_indent);
			for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
				ItemT *item = alt_item_head(alt);

				if (item_is_predicate(item)) {
					continue;
				}

				if (alt == see_through_alt) {
					assert(!full_first_set);
					c_output_default(info, code_indent);
				} else {
					c_output_bitvec_cases(info, table, alt_first_set(alt),
						code_indent);
				}

				if (c_output_alt(info, alt, rule, handler_rule, call_list,
						FALSE, FALSE, FALSE, predicate_id, error_terminal,
						code_indent + C_INDENT_STEP, rstack, non_local_stack,
						table)) {

					c_output_break(info, code_indent + C_INDENT_STEP);
					reachable = TRUE;
				}
			}

			if (need_check) {
				c_output_error_case(info, error_terminal, code_indent);
				c_output_restore(info, handler_rule, outer_level,
				code_indent + C_INDENT_STEP);

			}

			if (see_through_alt == NULL && !full_first_set) {
				c_output_default(info, code_indent);
				if (!rule_has_empty_alt(rule)) {
					c_output_jump(info, rule_get_handler_label(handler_rule),
						code_indent + C_INDENT_STEP);
				} else {
					c_output_break(info, code_indent + C_INDENT_STEP);
					reachable = TRUE;
				}
			}
			c_output_close(info, code_indent);
		} else {
			assert(!need_check);
			if (!rule_has_empty_alt(rule)) {
				c_output_jump(info, rule_get_handler_label(handler_rule),
					code_indent);
			}
		}
	}

	if ((handler != NULL || has_non_locals || outer_level)
		&& rule_used_handler_label(rule)) {

		if (reachable) {
			if (outer_level && types_equal_zero_tuple(rule_result(rule))
				&& !has_non_locals) {

				c_output_return(info, code_indent);
			} else {
				c_output_jump(info, rule_get_end_label(rule), code_indent);
			}
		} else {
			c_output_unreachable(info, code_indent);
		}
		reachable = FALSE;

		if (handler) {
			RuleT *cleanup_handler_rule = old_handler_rule;

			c_output_label(info, rule_get_handler_label(rule), code_indent);
			reachable = TRUE;
			if (outer_level || has_non_locals) {
				rule_set_handler_label(rule, c_out_next_label());
				cleanup_handler_rule = rule;
			}

			if (!c_output_alt(info, handler, rule, cleanup_handler_rule,
				call_list, TRUE, FALSE, FALSE, predicate_id,
				error_terminal, code_indent, rstack,
				non_local_stack, table)) {
				reachable = FALSE;
			}
		}

		if ((outer_level || has_non_locals) && rule_used_handler_label(rule)) {
			if (reachable) {
				c_output_jump(info, rule_get_end_label(rule), code_indent);
			} else if (handler) {
				c_output_unreachable(info, code_indent);
			}

			c_output_label(info, rule_get_handler_label(rule), code_indent);
			if (has_non_locals) {
				c_output_restore_non_locals(info, rule, code_indent, rstack,
					non_local_stack);
			}

			if (outer_level) {
				OStreamT *ostream = c_out_info_ostream(info);

				c_output_indent(info, code_indent);
				write_cstring(ostream, "SAVE_LEXER (");
				c_output_error_terminal(info, error_terminal);
				write_cstring(ostream, ");");
				write_newline(ostream);
				c_output_return(info, code_indent);
			} else {
				c_output_jump(info, rule_get_handler_label(old_handler_rule),
					code_indent);
			}
			reachable = FALSE;
		}
	}

	if (rule_used_end_label(rule)) {
		c_output_label(info, rule_get_end_label(rule), code_indent);
		reachable = TRUE;
	}

	if (reachable) {
		if (has_non_locals) {
			c_output_restore_non_locals(info, rule, code_indent, rstack,
				non_local_stack);
		}

		if (outer_level) {
			c_output_result_assign(info, rule_result(rule), code_indent);
		}
	}

	if (has_non_locals) {
		c_output_close(info, indent);
		rstack_pop_frame(non_local_stack);
		rstack_pop_frame(rstack);
	}

	rule_not_being_output(rule);
	return reachable;
}

static void
c_output_definition_1(COutputInfoT *info, RuleT *rule, EntryT *predicate_id,
	EntryT *predicate_type, unsigned error_terminal, TableT *table)
{
	OStreamT   *ostream = c_out_info_ostream(info);
	EntryT     *entry   = rule_entry(rule);
	unsigned    split   = c_out_info_get_split(info);
	RStackT     rstack;
	RStackT     non_local_stack;
	const char *name;
	CCodeT     *header;

	if (rule_is_required(rule)) {
		write_cstring(ostream, "void");
	} else if (rule_needs_function(rule)) {
		if (split != 0) {
			write_cstring(ostream, "void");
		} else {
			write_cstring(ostream, "static void");
		}
	} else {
		return;
	}

	write_newline(ostream);
	c_output_mapped_key(info, entry);
	c_output_type_defn(info, rule_param(rule), rule_result(rule));
	c_out_reset_labels();
	rstack_init(&rstack);
	rstack_push_frame(&rstack);
	rstack_add_translation(&rstack, predicate_id, predicate_id, predicate_type,
		FALSE);
	rstack_compute_formal_renaming(&rstack, rule_param(rule));
	rstack_compute_formal_renaming(&rstack, rule_result(rule));
	rstack_save_state(&rstack, rule_rstack_state(rule));
	rstack_init(&non_local_stack);

	(void) c_output_rule(info, rule, rule, rule_call_list(rule), TRUE,
		predicate_id, error_terminal, C_INDENT_STEP, &rstack, &non_local_stack,
		table);

	write_char(ostream, '}');
	write_newline(ostream);
	write_newline(ostream);
	rstack_destroy(&rstack);
	rstack_destroy(&non_local_stack);

	if (split == 0) {
		return;
	}

	if (ostream_line(ostream) < split) {
		return;
	}

	name   = ostream_gen_name(ostream);
	header = c_out_info_get_header1(info);

	write_cstring (ostream, "/* END OF FILE */");
	write_newline(ostream);
	ostream_close(ostream);

	if (!ostream_open(ostream, name)) {
		error(ERROR_FATAL, "cannot open output file '%s': %s", name, strerror(errno));
		UNREACHED;
	}

	c_output_identification(info);
	write_cstring (ostream, "/* BEGINNING OF HEADER */");
	write_newline(ostream);
	write_newline(ostream);
	write_cstring(ostream, "#define __SID_SPLIT");
	write_newline(ostream);
	c_output_location(info, c_code_file(header), c_code_line(header));
	c_output_c_code(info, header);
	c_output_location(info, ostream_name(ostream),
	ostream_line(ostream) + 1);
	write_newline(ostream);
}

static void
c_output_definition(EntryT *entry, void *gclosure)
{
	if (entry_is_rule(entry)) {
		RuleT        *rule           = entry_get_rule(entry);
		COutClosureT *closure        = (COutClosureT *)gclosure;
		COutputInfoT *info           = closure->info;
		TableT       *table          = closure->table;
		EntryT       *predicate_id   = closure->predicate_id;
		EntryT       *predicate_type = closure->predicate_type;
		unsigned      error_terminal = closure->error_terminal;

		c_output_definition_1(info, rule, predicate_id, predicate_type,
			error_terminal, table);
	}
}


/*
 * Externally visible functions
 */

void
c_output_parser(COutputInfoT *info, GrammarT *grammar)
{
	TableT       *table   = grammar_table(grammar);
	OStreamT     *ostream = c_out_info_ostream(info);
	CCodeT       *header  = c_out_info_get_header1(info);
	CCodeT       *trailer = c_out_info_get_trailer1(info);
	COutClosureT  closure;

	closure.info           = info;
	closure.table          = table;
	closure.predicate_id   = grammar_get_predicate_id(grammar);
	closure.predicate_type = grammar_get_predicate_type(grammar);
	closure.error_terminal = grammar_max_terminal(grammar);
	c_output_identification(info);

	write_cstring (ostream, "/* BEGINNING OF HEADER */");
	write_newline(ostream);
	write_newline(ostream);

	if (c_out_info_get_split(info) != 0) {
		write_cstring(ostream, "#define __SID_SPLIT");
		write_newline(ostream);
	}

	c_output_location(info, c_code_file(header), c_code_line(header));
	c_output_c_code(info, header);
	c_output_location(info, ostream_name(ostream), ostream_line(ostream) + 1);
	write_newline(ostream);

	/* TODO: #error for other undefined macros, too */

	if (!c_out_info_get_numeric_terminals(info)) {
		write_newline(ostream);
		write_cstring (ostream, "#ifndef ERROR_TERMINAL");
		write_newline(ostream);
		write_cstring (ostream, "#error \"-s no-numeric-terminals given and ERROR_TERMINAL is not defined\"");
		write_newline(ostream);
		write_cstring (ostream, "#endif");
		write_newline(ostream);
		write_newline(ostream);
	}

	if (c_out_info_get_split(info) == 0) {
		write_cstring (ostream, "/* BEGINNING OF FUNCTION DECLARATIONS */");
		write_newline(ostream);
		write_newline(ostream);
		table_iter(table, c_output_declaration, info);
		write_newline(ostream);
	}

	c_output_static_vars(info, grammar, TRUE);
	write_cstring (ostream, "/* BEGINNING OF FUNCTION DEFINITIONS */");
	write_newline(ostream);
	write_newline(ostream);
	table_iter(table, c_output_definition,  &closure);

	write_cstring (ostream, "/* BEGINNING OF TRAILER */");
	write_newline(ostream);
	write_newline(ostream);
	c_output_location(info, c_code_file(trailer), c_code_line(trailer));
	c_output_c_code(info, trailer);
	c_output_location(info, ostream_name(ostream), ostream_line(ostream) + 1);

	write_newline(ostream);
	write_cstring (ostream, "/* END OF FILE */");
	write_newline(ostream);
}

void
c_output_header(COutputInfoT *info, GrammarT *grammar)
{
	TableT   *table   = grammar_table(grammar);
	OStreamT *ostream = c_out_info_ostream(info);
	CCodeT   *header  = c_out_info_get_header2(info);
	CCodeT   *trailer = c_out_info_get_trailer2(info);

	c_output_identification(info);
	write_cstring (ostream, "/* BEGINNING OF HEADER */");
	write_newline(ostream);
	write_newline(ostream);
	c_output_location(info, c_code_file(header), c_code_line(header));
	c_output_c_code(info, header);
	c_output_location(info, ostream_name(ostream), ostream_line(ostream) + 1);

	write_newline(ostream);
	write_cstring (ostream, "/* BEGINNING OF FUNCTION DECLARATIONS */");
	write_newline(ostream);
	write_newline(ostream);

	if (c_out_info_get_split(info) != 0) {
		write_cstring(ostream, "#ifndef __SID_SPLIT");
		write_newline(ostream);
		table_iter(table, c_output_ext_declaration, info);
		write_cstring (ostream, "#else /* __SID_SPLIT */");
		write_newline(ostream);
		table_iter(table, c_output_declaration, info);
		c_output_static_vars(info, grammar, FALSE);
		write_cstring (ostream, "#endif /* __SID_SPLIT */");
		write_newline(ostream);
	} else {
		table_iter(table, c_output_ext_declaration, info);
	}

	if (c_out_info_get_terminals(info)) {
		write_newline(ostream);
		write_cstring (ostream, "/* BEGINNING OF TERMINAL DEFINITIONS */");
		write_newline(ostream);
		write_newline(ostream);
		table_iter(table, c_output_terminal, info);
		write_newline(ostream);
	}

	write_cstring (ostream, "/* BEGINNING OF TRAILER */");
	write_newline(ostream);
	write_newline(ostream);
	c_output_location(info, c_code_file(trailer), c_code_line(trailer));
	c_output_c_code(info, trailer);
	c_output_location(info, ostream_name(ostream), ostream_line(ostream) + 1);

	write_newline(ostream);
	write_cstring(ostream, "/* END OF FILE */");
	write_newline(ostream);
}

void
c_output_location(COutputInfoT *info, const char *file, unsigned line)
{
	OStreamT *ostream;

	if (!c_out_info_get_lines(info)) {
		return;
	}

	ostream = c_out_info_ostream(info);

	write_cstring(ostream, "#line ");
	write_unsigned(ostream, line);
	write_cstring(ostream, " \"");
	write_cstring(ostream, file);
	write_char(ostream, '"');
	write_newline(ostream);
}

void
c_output_key_message(COutputInfoT *info, char *prefix, KeyT *key,
	char *suffix, unsigned indent)
{
	OStreamT *ostream;

	if (!c_out_info_get_lines(info)) {
		return;
	}

	ostream = c_out_info_ostream(info);

	c_output_indent(info, indent);
	write_cstring(ostream, prefix);
	write_key(ostream, key);
	write_cstring(ostream, suffix);
	write_newline(ostream);
}

unsigned
c_out_next_label(void)
{
	return out_current_label++;
}

void
c_output_open(COutputInfoT *info, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_indent(info, indent);
	write_char(ostream, '{');
	write_newline(ostream);
}

void
c_output_close(COutputInfoT *info, unsigned indent)
{
	OStreamT *ostream = c_out_info_ostream(info);

	c_output_indent(info, indent);
	write_char(ostream, '}');
	write_newline(ostream);
}

void
c_output_terminal_entry(COutputInfoT *info, EntryT *entry)
{
	OStreamT *ostream = c_out_info_ostream(info);

	if (c_out_info_get_numeric_terminals(info)) {
		BasicT *basic = entry_get_basic(entry);

		write_unsigned(ostream, basic_terminal(basic));
	} else {
		KeyT     *key     = entry_key(entry);

		write_cstring(ostream, "(");
		c_output_string_key(info, key, c_out_info_terminal_prefix(info));
		write_cstring(ostream, ")");
	}
}
