/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/*
 * c-code.c --- SID C code ADT routines.
 *
 * This file implements the C code ADT used to represent action definitions
 * for the C output language.
 */

#include <assert.h>

#include "../shared/check/check.h"
#include "c-code.h"
#include "c-out-key.h"
#include "c-output.h"
#include "../gen-errors.h"
#include "../adt/name.h"

static void
c_code_set_labels(CCodeT * code)
{
    CCodeItemT * item;

    for (item = code->head; item; item = item->next) {
	if (item->type == CCT_LABEL) {
	    NameT * name = entry_get_name(item->u.ident);

	    if (!name_has_label(name)) {
		name_set_label(name, c_out_next_label());
	    }
	}
    }
}

static void
c_code_reset_labels(CCodeT * code)
{
    CCodeItemT * item;

    for (item = code->head; item; item = item->next) {
	if (item->type == CCT_LABEL) {
	    NameT * name = entry_get_name(item->u.ident);

	    name_reset_label(name);
	}
    }
}

static EntryT *
c_code_get_translation(SaveRStackT * state, TypeBTransT * translator, EntryT * ident,
		       EntryT * *type_ref, BoolT *reference_ref,
		       EntryT * *entry_ref)
{
    EntryT * entry = btrans_get_translation(translator, ident);
    EntryT * stack_entry;

    assert(entry);
    stack_entry = rstack_get_translation(state, entry, type_ref,
					 reference_ref);
    if ((stack_entry == NULL) && (entry_is_non_local(entry))) {
	stack_entry    = entry;
	*type_ref      = entry_get_non_local(entry);
	*reference_ref = FALSE;
    }
    assert(stack_entry);
    if (entry_ref) {
	*entry_ref = entry;
    }
    return(stack_entry);
}


/*
 * Externally-visible functions
 */

CCodeT *
c_code_create(char * file, unsigned line)
{
    CCodeT * code = ALLOCATE(CCodeT);

    code->head = NULL;
    code->tail = &(code->head);
    code->file = file;
    code->line = line;
    types_init(&(code->param));
    types_init(&(code->result));
    return(code);
}

void
c_code_append_string(CCodeT * code, NStringT * string)
{
    CCodeItemT * item = ALLOCATE(CCodeItemT);

    item->next    = NULL;
    item->type    = CCT_STRING;
    nstring_assign(&(item->u.string), string);
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_label(CCodeT * code, NStringT * string)
{
    CCodeItemT * item = ALLOCATE(CCodeItemT);

    item->next    = NULL;
    item->type    = CCT_LABEL;
    nstring_assign(&(item->u.string), string);
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_identifier(CCodeT * code, NStringT * string)
{
    CCodeItemT * item = ALLOCATE(CCodeItemT);

    item->next    = NULL;
    item->type    = CCT_IDENT;
    nstring_assign(&(item->u.string), string);
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_modifiable(CCodeT * code, NStringT * string)
{
    CCodeItemT * item = ALLOCATE(CCodeItemT);

    item->next    = NULL;
    item->type    = CCT_MOD_IDENT;
    nstring_assign(&(item->u.string), string);
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_reference(CCodeT * code, NStringT * string)
{
    CCodeItemT * item = ALLOCATE(CCodeItemT);

    item->next    = NULL;
    item->type    = CCT_REF_IDENT;
    nstring_assign(&(item->u.string), string);
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_exception(CCodeT * code)
{
    CCodeItemT * item = ALLOCATE(CCodeItemT);

    item->next    = NULL;
    item->type    = CCT_EXCEPTION;
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_advance(CCodeT * code)
{
    CCodeItemT * item = ALLOCATE(CCodeItemT);

    item->next    = NULL;
    item->type    = CCT_ADVANCE;
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_terminal(CCodeT * code)
{
    CCodeItemT * item = ALLOCATE(CCodeItemT);

    item->next    = NULL;
    item->type    = CCT_TERMINAL;
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_check(CCodeT * code, BoolT exceptions, BoolT param_op, TypeTupleT * param,
	     TypeTupleT * result, TableT * table)
{
    CCodeItemT * item;
    EntryT *     entry;

    for (item = code->head; item; item = item->next) {
	switch (item->type)EXHAUSTIVE {
	  case CCT_IDENT:
	    entry         = table_add_name(table, &(item->u.string));
	    item->u.ident = entry;
	    if (((param == NULL) ||
		 (!types_contains(param, entry))) &&
		((result == NULL) ||
		 (!types_contains(result, entry)))) {
		E_bad_id_substitution(c_code_file(code), c_code_line(code),
				      entry);
	    } else if (result) {
		name_used(entry_get_name(entry));
	    }
	    break;
	  case CCT_MOD_IDENT:
	    entry         = table_add_name(table, &(item->u.string));
	    item->u.ident = entry;
	    if (exceptions) {
		if ((param == NULL) ||
		    (!types_mutated(param, entry))) {
		    E_bad_mod_id_substitution(c_code_file(code),
					      c_code_line(code), entry);
		}
	    } else {
		E_mod_id_in_assign(c_code_file(code), c_code_line(code),
				   entry);
	    }
	    break;
	  case CCT_REF_IDENT:
	    entry         = table_add_name(table, &(item->u.string));
	    item->u.ident = entry;
	    if (!param_op) {
		if ((param == NULL) ||
		    (!types_contains(param, entry))) {
		    E_bad_ref_id_substitution(c_code_file(code),
					      c_code_line(code), entry);
		}
	    } else {
		E_ref_id_in_param_op(c_code_file(code), c_code_line(code),
				     entry);
	    }
	    break;
	  case CCT_LABEL:
	    entry         = table_add_name(table, &(item->u.string));
	    item->u.ident = entry;
	    if ((param == NULL) && (result == NULL)) {
		E_bad_label_substitution(c_code_file(code),
					 c_code_line(code), entry);
	    }
	    break;
	  case CCT_EXCEPTION:
	    if (!exceptions) {
		E_bad_exception_substitution(c_code_file(code),
					     c_code_line(code));
	    }
	    break;
	  case CCT_ADVANCE:
	    if (!exceptions) {
		E_bad_advance_substitution(c_code_file(code),
					   c_code_line(code));
	    }
	    break;
	  case CCT_TERMINAL:
	    if (!exceptions) {
		E_bad_terminal_substitution(c_code_file(code),
					    c_code_line(code));
	    }
	    break;
	  case CCT_STRING:
	    break;
	}
    }
    if (result) {
	types_check_used(result, E_code_undefined_result, code);
	for (item = code->head; item; item = item->next) {
	    if (item->type == CCT_IDENT) {
		name_not_used(entry_get_name(item->u.ident));
	    }
	}
    }
    if (param) {
	types_assign(&(code->param), param);
    }
    if (result) {
	types_assign(&(code->result), result);
    }
}

char *
c_code_file(CCodeT * code)
{
    return(code->file);
}

unsigned
c_code_line(CCodeT * code)
{
    return(code->line);
}

TypeTupleT *
c_code_param(CCodeT * code)
{
    return(&(code->param));
}

TypeTupleT *
c_code_result(CCodeT * code)
{
    return(&(code->result));
}

void
c_code_deallocate(CCodeT * code)
{
    CCodeItemT * item = code->head;

    while (item) {
	CCodeItemT * next = item->next;

	switch (item->type)EXHAUSTIVE {
	  case CCT_STRING:
	    nstring_destroy(&(item->u.string));
	    break;
	  case CCT_IDENT:
	  case CCT_MOD_IDENT:
	  case CCT_REF_IDENT:
	  case CCT_LABEL:
	  case CCT_EXCEPTION:
	  case CCT_TERMINAL:
	  case CCT_ADVANCE:
	    break;
	}
	DEALLOCATE(item);
	item = next;
    }
    types_destroy(&(code->param));
    types_destroy(&(code->result));
    DEALLOCATE(code);
}

void
c_output_c_code_action(COutputInfoT * info, CCodeT * code, TypeTupleT * param,
		       TypeTupleT * result, SaveRStackT * state,
		       RuleT * handler_rule)
{
    OStreamT *    ostream      = c_out_info_ostream(info);
    NStringT *    label_prefix = c_out_info_label_prefix(info);
    NStringT *    in_prefix    = c_out_info_in_prefix(info);
    CCodeItemT *  item;
    CCodeItemT *  last_item;
    EntryT *      stack_entry;
    EntryT *      entry;
    EntryT *      stack_type;
    BoolT       stack_reference;
    BoolT       use_cast;
    TypeBTransT translator;

    char c;

    c_code_set_labels(code);
    btrans_init(&translator);
    btrans_add_translations(&translator, &(code->param), param);
    btrans_add_translations(&translator, &(code->result), result);
    for (item = code->head; item; item = item->next) {
	switch (item->type)EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring(ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	    write_nstring(ostream, label_prefix);
	    write_unsigned(ostream,
			   name_get_label(entry_get_name(item->u.ident)));
	    break;
	  case CCT_IDENT:
	    stack_entry = c_code_get_translation(state, &translator,
						 item->u.ident, &stack_type,
						 &stack_reference, &entry);
	    use_cast = (types_contains(param, entry) &&
			c_out_info_get_casts(info));
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
						 item->u.ident, &stack_type,
						 &stack_reference,
						 NULL);
	    write_char(ostream, '(');
	    if (stack_reference) {
		write_char(ostream, '*');
	    }
	    c_output_key(info, entry_key(stack_entry), in_prefix);
	    write_char(ostream, ')');
	    break;
	  case CCT_REF_IDENT:
	    stack_entry = c_code_get_translation(state, &translator,
						 item->u.ident, &stack_type,
						 &stack_reference,
						 NULL);
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
	last_item=item;
    }
    if((last_item->type==CCT_STRING)) {
	c = nstring_contents(&last_item->u.string)[nstring_length(&last_item->u.string)-1] ;
	if(c!= '\n' && c!= '\r') {
	    write_newline(ostream);
	}
    } 
    else {
        write_newline(ostream);
    }
    btrans_destroy(&translator);
    c_code_reset_labels(code);
}

void
c_output_c_code_basic(COutputInfoT * info, CCodeT * code, TypeTupleT * result,
		      SaveRStackT * state)
{
    OStreamT *    ostream      = c_out_info_ostream(info);
    NStringT *    label_prefix = c_out_info_label_prefix(info);
    NStringT *    in_prefix    = c_out_info_in_prefix(info);
    CCodeItemT *  item;
    CCodeItemT *  last_item;
    EntryT *      stack_entry;
    EntryT *      stack_type;
    BoolT       stack_reference;
    TypeBTransT translator;
    char c;

    c_code_set_labels(code);
    btrans_init(&translator);
    btrans_add_translations(&translator, &(code->result), result);
    for (item = code->head; item; item = item->next) {
	switch (item->type)EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring(ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	    write_nstring(ostream, label_prefix);
	    write_unsigned(ostream,
			   name_get_label(entry_get_name(item->u.ident)));
	    break;
	  case CCT_IDENT:
	    stack_entry = c_code_get_translation(state, &translator,
						 item->u.ident, &stack_type,
						 &stack_reference,
						 NULL);
	    c_output_key(info, entry_key(stack_entry), in_prefix);
	    break;
	  case CCT_MOD_IDENT:
	  case CCT_REF_IDENT:
	  case CCT_EXCEPTION:
	  case CCT_ADVANCE:
	  case CCT_TERMINAL:
	    UNREACHED;
	}
	last_item=item;
    }
    if((last_item->type==CCT_STRING)) {
	c = nstring_contents(&last_item->u.string)[nstring_length(&last_item->u.string)-1] ;
	if(c!= '\n' && c!= '\r') {
	    write_newline(ostream);
	}
    }
    else {
        write_newline(ostream);
    }
    btrans_destroy(&translator);
    c_code_reset_labels(code);
}

void
c_output_c_code_assign(COutputInfoT * info, CCodeT * code, EntryT * type,
		       EntryT * from, EntryT * to, BoolT from_reference,
		       BoolT to_reference)
{
    OStreamT *   ostream      = c_out_info_ostream(info);
    NStringT *   label_prefix = c_out_info_label_prefix(info);
    NStringT *   in_prefix    = c_out_info_in_prefix(info);
    BoolT      is_param;
    BoolT      use_cast;
    CCodeItemT * item;

    c_code_set_labels(code);
    for (item = code->head; item; item = item->next) {
	switch (item->type)EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring(ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	    write_nstring(ostream, label_prefix);
	    write_unsigned(ostream,
			   name_get_label(entry_get_name(item->u.ident)));
	    break;
	  case CCT_IDENT:
	    is_param = types_contains(&(code->param), item->u.ident);
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
c_output_c_code_param_assign(COutputInfoT * info, CCodeT * code, EntryT * type,
			     EntryT * entry)
{
    OStreamT *   ostream      = c_out_info_ostream(info);
    NStringT *   label_prefix = c_out_info_label_prefix(info);
    NStringT *   in_prefix    = c_out_info_in_prefix(info);
    NStringT *   out_prefix   = c_out_info_out_prefix(info);
    CCodeItemT * item;

    c_code_set_labels(code);
    for (item = code->head; item; item = item->next) {
	switch (item->type)EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring(ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	    write_nstring(ostream, label_prefix);
	    write_unsigned(ostream,
			   name_get_label(entry_get_name(item->u.ident)));
	    break;
	  case CCT_IDENT:
	    if (types_contains(&(code->param), item->u.ident)) {
		BoolT use_cast = c_out_info_get_casts(info);

		if (use_cast) {
		    write_cstring(ostream, "((");
		    c_output_mapped_key(info, type);
		    write_cstring(ostream, " *) (");
		}
		c_output_key(info, entry_key(entry), out_prefix);
		if (use_cast) {
		    write_cstring(ostream, "))");
		}
	    } else {
		c_output_key(info, entry_key(entry), in_prefix);
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
c_output_c_code_result_assign(COutputInfoT * info, CCodeT * code, EntryT * type,
			      EntryT * entry)
{
    OStreamT *   ostream      = c_out_info_ostream(info);
    NStringT *   label_prefix = c_out_info_label_prefix(info);
    NStringT *   in_prefix    = c_out_info_in_prefix(info);
    NStringT *   out_prefix   = c_out_info_out_prefix(info);
    CCodeItemT * item;

    c_code_set_labels(code);
    for (item = code->head; item; item = item->next) {
	switch (item->type)EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring(ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	    write_nstring(ostream, label_prefix);
	    write_unsigned(ostream,
			   name_get_label(entry_get_name(item->u.ident)));
	    break;
	  case CCT_IDENT:
	    if (types_contains(&(code->param), item->u.ident)) {
		BoolT use_cast = c_out_info_get_casts(info);

		if (use_cast) {
		    write_cstring(ostream, "((");
		    c_output_mapped_key(info, type);
		    write_cstring(ostream, ") (");
		}
		c_output_key(info, entry_key(entry), in_prefix);
		if (use_cast) {
		    write_cstring(ostream, "))");
		}
	    } else {
		c_output_key(info, entry_key(entry), out_prefix);
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
c_output_c_code(COutputInfoT * info, CCodeT * code)
{
    OStreamT *   ostream = c_out_info_ostream(info);
    CCodeItemT * item;

    for (item = code->head; item; item = item->next) {
	switch (item->type)EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring(ostream, &(item->u.string));
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
