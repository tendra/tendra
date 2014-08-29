/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * c-code.c - SID C code ADT routines.
 *
 * This file implements the C code ADT used to represent action definitions
 * for the C output language.
 */

#include <assert.h>

#include <shared/check.h>
#include <shared/error.h>

#include "c-code.h"
#include "c-out-key.h"
#include "c-output.h"
#include "../adt/name.h"

static void
c_code_set_labels(CCodeT *code)
{
	CCodeItemT *item;

	for (item = code->head; item; item = item->next) {
		if (item->type == CCT_LABEL) {
			NameT *name = entry_get_name(item->u.ident);

			if (!name_has_label(name)) {
				name_set_label(name, c_out_next_label());
			}
		}
	}
}

static void
c_code_reset_labels(CCodeT *code)
{
	CCodeItemT *item;

	for (item = code->head; item; item = item->next) {
		if (item->type == CCT_LABEL) {
			NameT *name = entry_get_name(item->u.ident);

			name_reset_label(name);
		}
	}
}

static EntryT *
c_code_get_translation(SaveRStackT *state, TypeBTransT *translator, EntryT *ident,
	EntryT **type_ref, BoolT *reference_ref, EntryT * *entry_ref)
{
	EntryT *entry;
	EntryT *stack_entry;

	entry = btrans_get_translation(translator, ident);
	assert(entry);

	stack_entry = rstack_get_translation(state, entry, type_ref, reference_ref);
	if (stack_entry == NULL && entry_is_non_local(entry)) {
		stack_entry = entry;
		*type_ref = entry_get_non_local(entry);
		*reference_ref = FALSE;
	}

	assert(stack_entry);
	if (entry_ref) {
		*entry_ref = entry;
	}

	return stack_entry;
}

static void

code_undefined_result(void *gclosure, EntryT *name)
{
	CCodeT *code = gclosure;

	error_posn(ERROR_FATAL, c_code_file(code), (int) c_code_line(code),
		"code result '%K' is not defined", (void *) entry_key(name));
}


/*
 * Externally-visible functions
 */

CCodeT *
c_code_create(const char *file, unsigned line)
{
	CCodeT *code = ALLOCATE(CCodeT);

	code->head = NULL;
	code->tail = &code->head;
	code->file = file;
	code->line = line;
	types_init(&code->param);
	types_init(&code->result);

	return code;
}

void
c_code_append_string(CCodeT *code, NStringT *string)
{
	CCodeItemT *item = ALLOCATE(CCodeItemT);

	item->next  = NULL;
	item->type  = CCT_STRING;
	nstring_assign(&item->u.string, string);
	*code->tail = item;
	code->tail  = &item->next;
}

void
c_code_append_basic(CCodeT *code, NStringT *string)
{
	CCodeItemT *item = ALLOCATE(CCodeItemT);

	item->next  = NULL;
	item->type  = CCT_BASIC;
	nstring_assign(&item->u.string, string);
	*code->tail = item;
	code->tail  = &item->next;
}

void
c_code_append_label(CCodeT *code, NStringT *string)
{
	CCodeItemT *item = ALLOCATE(CCodeItemT);

	item->next  = NULL;
	item->type  = CCT_LABEL;
	nstring_assign(&item->u.string, string);
	*code->tail = item;
	code->tail  = &item->next;
}

void
c_code_append_identifier(CCodeT *code, NStringT *string)
{
	CCodeItemT *item = ALLOCATE(CCodeItemT);

	item->next  = NULL;
	item->type  = CCT_IDENT;
	nstring_assign(&item->u.string, string);
	*code->tail = item;
	code->tail  = &item->next;
}

void
c_code_append_modifiable(CCodeT *code, NStringT *string)
{
	CCodeItemT *item = ALLOCATE(CCodeItemT);

	item->next  = NULL;
	item->type  = CCT_MOD_IDENT;
	nstring_assign(&item->u.string, string);
	*code->tail = item;
	code->tail  = &item->next;
}

void
c_code_append_reference(CCodeT *code, NStringT *string)
{
	CCodeItemT *item = ALLOCATE(CCodeItemT);

	item->next  = NULL;
	item->type  = CCT_REF_IDENT;
	nstring_assign(&item->u.string, string);
	*code->tail = item;
	code->tail  = &item->next;
}

void
c_code_append_exception(CCodeT *code)
{
	CCodeItemT *item = ALLOCATE(CCodeItemT);

	item->next  = NULL;
	item->type  = CCT_EXCEPTION;
	*code->tail = item;
	code->tail  = &item->next;
}

void
c_code_append_advance(CCodeT *code)
{
	CCodeItemT *item = ALLOCATE(CCodeItemT);

	item->next  = NULL;
	item->type  = CCT_ADVANCE;
	*code->tail = item;
	code->tail  = &item->next;
}

void
c_code_append_terminal(CCodeT *code)
{
	CCodeItemT *item = ALLOCATE(CCodeItemT);

	item->next  = NULL;
	item->type  = CCT_TERMINAL;
	*code->tail = item;
	code->tail  = &item->next;
}

void
c_code_check(CCodeT *code, BoolT exceptions, BoolT cct_exceptions,
	BoolT param_op, TypeTupleT *param,
	TypeTupleT *result, TableT *table)
{
	CCodeItemT *item;
	EntryT     *entry;

	for (item = code->head; item; item = item->next) {
		switch (item->type) EXHAUSTIVE {
		case CCT_IDENT:
			entry = table_add_name(table, &item->u.string);
			item->u.ident = entry;
			if ((param == NULL || !types_contains(param, entry))
				&& (result == NULL || !types_contains(result, entry))) {
				error_posn(ERROR_FATAL, c_code_file(code), (int) c_code_line(code),
					"substituted identifier '%K' is not a parameter or result",
					(void *) entry_key(entry));
			} else if (result) {
				name_used(entry_get_name(entry));
			}
			break;

		case CCT_MOD_IDENT:
			entry = table_add_name(table, &item->u.string);
			item->u.ident = entry;
			if (exceptions) {
				if (param == NULL || !types_mutated(param, entry)) {
					error_posn(ERROR_FATAL, c_code_file(code), (int) c_code_line(code),
						"substituted mutable identifier '%K' is not a parameter",
						(void *) entry_key(entry));
				}
			} else {
				error_posn(ERROR_FATAL, c_code_file(code), (int) c_code_line(code),
					"substituted mutable identifier '%K' in assignment operator definition",
					(void *) entry_key(entry));
			}
			break;

		case CCT_REF_IDENT:
			entry = table_add_name(table, &item->u.string);
			item->u.ident = entry;
			if (!param_op) {
				if (param == NULL || !types_contains(param, entry)) {
					error_posn(ERROR_FATAL, c_code_file(code), (int) c_code_line(code),
						"substituted reference identifier '%K' is not a parameter",
						(void *) entry_key(entry));
				}
			} else {
				error_posn(ERROR_FATAL, c_code_file(code), (int) c_code_line(code),
					"substituted address of identifier '%K' in parameter assignment operator definition",
					(void *) entry_key(entry));
			}
			break;

		case CCT_BASIC:
			entry = table_get_basic(table, &item->u.string);
			/*
			 * Note that we do not check basic_get_ignored() here;
			 * grammar_check_complete() for details.
			 */
			if (!entry) {
				error_posn(ERROR_FATAL, c_code_file(code), (int) c_code_line(code),
					"substituted terminal '%s' hasn't been declared or defined",
						nstring_contents(&item->u.string));
			} else {
				item->u.basic = entry;
			}
			break;

		case CCT_LABEL:
			entry = table_add_name(table, &item->u.string);
			item->u.ident = entry;
			if (param == NULL && result == NULL) {
				error_posn(ERROR_FATAL, c_code_file(code), (int) c_code_line(code),
					"substituted label '%K' in unparameterised block",
					(void *) entry_key(entry));
			}
			break;

		case CCT_EXCEPTION:
			if (!cct_exceptions) {
				error_posn(ERROR_SERIOUS, c_code_file(code), (int) c_code_line(code),
					"substituted exception call in unsuitable code block");
			}
			break;

		case CCT_ADVANCE:
			if (!exceptions) {
				error_posn(ERROR_SERIOUS, c_code_file(code), (int) c_code_line(code),
					"substituted lexer advance call in unsuitable code block");
			}
			break;

		case CCT_TERMINAL:
			if (!exceptions) {
				error_posn(ERROR_SERIOUS, c_code_file(code), (int) c_code_line(code),
					"substituted current terminal call in unsuitable code block");
			}
			break;

		case CCT_STRING:
			break;
		}
	}

	if (result) {
		types_check_used(result, code_undefined_result, code);
		for (item = code->head; item; item = item->next) {
			if (item->type == CCT_IDENT) {
				name_not_used(entry_get_name(item->u.ident));
			}
		}
	}

	if (param) {
		types_assign(&code->param, param);
	}

	if (result) {
		types_assign(&code->result, result);
	}
}

const char *
c_code_file(CCodeT *code)
{
	return code->file;
}

unsigned
c_code_line(CCodeT *code)
{
	return code->line;
}

TypeTupleT *
c_code_param(CCodeT *code)
{
	return &code->param;
}

TypeTupleT *
c_code_result(CCodeT *code)
{
	return &code->result;
}

void
c_code_deallocate(CCodeT *code)
{
	CCodeItemT *item;
	CCodeItemT *next;

	for (item = code->head; item; item = next) {
		next = item->next;

		switch (item->type) EXHAUSTIVE {
		case CCT_STRING:
			nstring_destroy(&item->u.string);
			break;

		case CCT_IDENT:
		case CCT_MOD_IDENT:
		case CCT_REF_IDENT:
		case CCT_BASIC:
		case CCT_LABEL:
		case CCT_EXCEPTION:
		case CCT_TERMINAL:
		case CCT_ADVANCE:
			break;
		}

		DEALLOCATE(item);
	}

	types_destroy(&code->param);
	types_destroy(&code->result);
	DEALLOCATE(code);
}

void
c_output_c_code_action(COutputInfoT *info, CCodeT *code, TypeTupleT *param,
	TypeTupleT *result, SaveRStackT *state, RuleT *handler_rule)
{
	OStreamT   *ostream      = c_out_info_ostream(info);
	NStringT   *label_prefix = c_out_info_label_prefix(info);
	NStringT   *in_prefix    = c_out_info_in_prefix(info);
	CCodeItemT *item;
	CCodeItemT *last_item = NULL;
	EntryT     *stack_entry;
	EntryT     *entry;
	EntryT     *stack_type;
	BoolT       stack_reference;
	BoolT       use_cast;
	TypeBTransT translator;

	char c;

	c_code_set_labels(code);
	btrans_init(&translator);
	btrans_add_translations(&translator, &code->param, param);
	btrans_add_translations(&translator, &code->result, result);

	for (item = code->head; item; item = item->next) {
		switch (item->type) EXHAUSTIVE {
		case CCT_STRING:
			write_nstring(ostream, &item->u.string);
			break;

		case CCT_BASIC:
			c_output_terminal_entry(info, item->u.basic);
			break;

		case CCT_LABEL:
			write_nstring(ostream, label_prefix);
			write_unsigned(ostream,
				name_get_label(entry_get_name(item->u.ident)));
			break;

		case CCT_IDENT:
			stack_entry = c_code_get_translation(state, &translator,
				item->u.ident, &stack_type, &stack_reference, &entry);
			use_cast = types_contains(param, entry) && c_out_info_get_casts(info);
			if (use_cast) {
				write_cstring(ostream, "((");
				c_output_mapped_key(info, stack_type);
				write_cstring(ostream, ") (");
			} else {
				write_char(ostream, '(');
			}

			if (stack_reference) {
				write_char(ostream, '*');
			}

			c_output_key(info, entry_key(stack_entry), in_prefix);

			if (use_cast) {
				write_cstring(ostream, "))");
			} else {
				write_char(ostream, ')');
			}
			break;

		case CCT_MOD_IDENT:
			stack_entry = c_code_get_translation(state, &translator,
				item->u.ident, &stack_type, &stack_reference, NULL);

			write_char(ostream, '(');
			if (stack_reference) {
				write_char(ostream, '*');
			}
			c_output_key(info, entry_key(stack_entry), in_prefix);
			write_char(ostream, ')');
			break;

		case CCT_REF_IDENT:
			stack_entry = c_code_get_translation(state, &translator,
				item->u.ident, &stack_type, &stack_reference, NULL);
			write_char(ostream, '(');
			if (!stack_reference) {
				write_char(ostream, '&');
			}
			c_output_key(info, entry_key(stack_entry), in_prefix);
			write_char(ostream, ')');
			break;

		case CCT_EXCEPTION:
			write_cstring(ostream, "goto ");
			write_nstring(ostream, label_prefix);
			write_unsigned(ostream, rule_get_handler_label(handler_rule));
			break;

		case CCT_ADVANCE:
			write_cstring(ostream, "ADVANCE_LEXER");
			break;

		case CCT_TERMINAL:
			write_cstring(ostream, "CURRENT_TERMINAL");
			break;
		}
		last_item = item;
	}

	assert(last_item != NULL);
	if (last_item->type == CCT_STRING) {
		c = nstring_contents(&last_item->u.string)[nstring_length(&last_item->u.string) - 1];
		if (c != '\n' && c != '\r') {
			write_newline(ostream);
		}
	} else {
		write_newline(ostream);
	}

	btrans_destroy(&translator);
	c_code_reset_labels(code);
}

void
c_output_c_code_basic(COutputInfoT * info, CCodeT * code, TypeTupleT * result,
	SaveRStackT * state, RuleT *handler_rule)
{
	OStreamT   *ostream      = c_out_info_ostream(info);
	NStringT   *label_prefix = c_out_info_label_prefix(info);
	NStringT   *in_prefix    = c_out_info_in_prefix(info);
	CCodeItemT *item;
	CCodeItemT *last_item = NULL;
	EntryT     *stack_entry;
	EntryT     *stack_type;
	BoolT       stack_reference;
	TypeBTransT translator;
	char c;

	c_code_set_labels(code);
	btrans_init(&translator);
	btrans_add_translations(&translator, &code->result, result);

	for (item = code->head; item; item = item->next) {
		switch (item->type) EXHAUSTIVE {
		case CCT_STRING:
			write_nstring(ostream, &item->u.string);
			break;

		case CCT_BASIC:
			c_output_terminal_entry(info, item->u.basic);
			break;

		case CCT_LABEL:
			write_nstring(ostream, label_prefix);
			write_unsigned(ostream, name_get_label(entry_get_name(item->u.ident)));
			break;

		case CCT_IDENT:
			stack_entry = c_code_get_translation(state, &translator,
				item->u.ident, &stack_type, &stack_reference, NULL);
			c_output_key(info, entry_key(stack_entry), in_prefix);
			break;

		case CCT_EXCEPTION:
			write_cstring(ostream, "goto ");
			write_nstring(ostream, label_prefix);
			write_unsigned(ostream, rule_get_handler_label(handler_rule));
			break;

		case CCT_MOD_IDENT:
		case CCT_REF_IDENT:
		case CCT_ADVANCE:
		case CCT_TERMINAL:
			UNREACHED;
		}

		last_item = item;
	}

	assert(last_item != NULL);
	if (last_item->type == CCT_STRING) {
		c = nstring_contents(&last_item->u.string)[nstring_length(&last_item->u.string) - 1] ;
		if (c != '\n' && c != '\r') {
			write_newline(ostream);
		}
	} else {
		write_newline(ostream);
	}

	btrans_destroy(&translator);
	c_code_reset_labels(code);
}

void
c_output_c_code_assign(COutputInfoT *info, CCodeT *code, EntryT *type,
	EntryT *from, EntryT *to, BoolT from_reference, BoolT to_reference)
{
	OStreamT   *ostream      = c_out_info_ostream(info);
	NStringT   *label_prefix = c_out_info_label_prefix(info);
	NStringT   *in_prefix    = c_out_info_in_prefix(info);
	BoolT       is_param;
	BoolT       use_cast;
	CCodeItemT *item;

	c_code_set_labels(code);
	for (item = code->head; item; item = item->next) {
		switch (item->type) EXHAUSTIVE {
		case CCT_STRING:
			write_nstring(ostream, &item->u.string);
			break;

		case CCT_BASIC:
			c_output_terminal_entry(info, item->u.basic);
			break;

		case CCT_LABEL:
			write_nstring(ostream, label_prefix);
			write_unsigned(ostream,
			name_get_label(entry_get_name(item->u.ident)));
			break;

		case CCT_IDENT:
			is_param = types_contains(&code->param, item->u.ident);
			use_cast = (is_param && c_out_info_get_casts(info));
			if (use_cast) {
				write_cstring(ostream, "((");
				c_output_mapped_key(info, type);
				write_cstring(ostream, ") (");
			} else {
				write_char(ostream, '(');
			}

			if (is_param) {
				if (from_reference) {
					write_char(ostream, '*');
				}

				c_output_key(info, entry_key(from), in_prefix);
			} else {
				if (to_reference) {
					write_char(ostream, '*');
				}
				c_output_key(info, entry_key(to), in_prefix);
			}

			if (use_cast) {
				write_cstring(ostream, "))");
			} else {
				write_char(ostream, ')');
			}
			break;

		case CCT_REF_IDENT:
			write_char(ostream, '(');
			if (!from_reference) {
				write_char(ostream, '&');
			}
			c_output_key(info, entry_key(from), in_prefix);
			write_char(ostream, ')');
			break;

		case CCT_MOD_IDENT:
		case CCT_EXCEPTION:
		case CCT_ADVANCE:
		case CCT_TERMINAL:
			UNREACHED;
		}
	}
	c_code_reset_labels(code);
}

void
c_output_c_code_param_assign(COutputInfoT *info, CCodeT *code, EntryT *type,
	EntryT *entry)
{
	OStreamT   *ostream      = c_out_info_ostream(info);
	NStringT   *label_prefix = c_out_info_label_prefix(info);
	NStringT   *in_prefix    = c_out_info_in_prefix(info);
	NStringT   *out_prefix   = c_out_info_out_prefix(info);
	CCodeItemT *item;

	c_code_set_labels(code);
	for (item = code->head; item; item = item->next) {
		BoolT use_cast;

		switch (item->type) EXHAUSTIVE {
		case CCT_STRING:
			write_nstring(ostream, &item->u.string);
			break;

		case CCT_BASIC:
			c_output_terminal_entry(info, item->u.basic);
			break;

		case CCT_LABEL:
			write_nstring(ostream, label_prefix);
			write_unsigned(ostream,
				name_get_label(entry_get_name(item->u.ident)));
			break;

		case CCT_IDENT:
			if (!types_contains(&code->param, item->u.ident)) {
				c_output_key(info, entry_key(entry), in_prefix);
				break;
			}

			use_cast = c_out_info_get_casts(info);
			if (use_cast) {
				write_cstring(ostream, "((");
				c_output_mapped_key(info, type);
				write_cstring(ostream, " *) (");
			}

			c_output_key(info, entry_key(entry), out_prefix);

			if (use_cast) {
				write_cstring(ostream, "))");
			}
			break;

		case CCT_MOD_IDENT:
		case CCT_REF_IDENT:
		case CCT_EXCEPTION:
		case CCT_ADVANCE:
		case CCT_TERMINAL:
			UNREACHED;
		}
	}
	c_code_reset_labels(code);
}

void
c_output_c_code_result_assign(COutputInfoT *info, CCodeT *code, EntryT *type,
	EntryT *entry)
{
	OStreamT   *ostream      = c_out_info_ostream(info);
	NStringT   *label_prefix = c_out_info_label_prefix(info);
	NStringT   *in_prefix    = c_out_info_in_prefix(info);
	NStringT   *out_prefix   = c_out_info_out_prefix(info);
	CCodeItemT *item;

	c_code_set_labels(code);
	for (item = code->head; item; item = item->next) {
		BoolT use_cast;

		switch (item->type)EXHAUSTIVE {
		case CCT_STRING:
			write_nstring(ostream, &item->u.string);
			break;

		case CCT_BASIC:
			c_output_terminal_entry(info, item->u.basic);
			break;

		case CCT_LABEL:
			write_nstring(ostream, label_prefix);
			write_unsigned(ostream,
				name_get_label(entry_get_name(item->u.ident)));
			break;

		case CCT_IDENT:
			if (!types_contains(&code->param, item->u.ident)) {
				c_output_key(info, entry_key(entry), out_prefix);
				break;
			}

			use_cast = c_out_info_get_casts(info);

			if (use_cast) {
				write_cstring(ostream, "((");
				c_output_mapped_key(info, type);
				write_cstring(ostream, ") (");
			}

			c_output_key(info, entry_key(entry), in_prefix);

			if (use_cast) {
				write_cstring(ostream, "))");
			}
			break;

		case CCT_REF_IDENT:
			write_cstring(ostream, "(&");
			c_output_key(info, entry_key(entry), in_prefix);
			write_char(ostream, ')');
			break;

		case CCT_MOD_IDENT:
		case CCT_EXCEPTION:
		case CCT_ADVANCE:
		case CCT_TERMINAL:
			UNREACHED;
		}
	}
	c_code_reset_labels(code);
}

void
c_output_c_code(COutputInfoT *info, CCodeT *code)
{
	OStreamT   *ostream = c_out_info_ostream(info);
	CCodeItemT *item;

	for (item = code->head; item; item = item->next) {
		switch (item->type) EXHAUSTIVE {
		case CCT_STRING:
			write_nstring(ostream, &item->u.string);
			break;

		case CCT_BASIC:
			c_output_terminal_entry(info, item->u.basic);
			break;

		case CCT_LABEL:
		case CCT_IDENT:
		case CCT_MOD_IDENT:
		case CCT_REF_IDENT:
		case CCT_EXCEPTION:
		case CCT_ADVANCE:
		case CCT_TERMINAL:
			UNREACHED;
		}
	}
}
