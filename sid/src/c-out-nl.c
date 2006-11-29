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


/*** c-out-nl.c --- Output of non local name list ADT objects.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the non local name list output routines used by SID.
 *
 *** Change Log:
 * $Log: c-out-nl.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:43  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:56:34  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:20  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "c-out-nl.h"
#include "action.h"
#include "c-code.h"
#include "c-out-key.h"
#include "c-out-types.h"

/*--------------------------------------------------------------------------*/

typedef struct NonLocalClosureT {
    COutputInfoP	info;
    SaveRStackP		state;
    unsigned		indent;
} NonLocalClosureT, *NonLocalClosureP;

/*--------------------------------------------------------------------------*/

static void
c_output_save_non_locals_1(COutputInfoP info, NonLocalEntryP non_local,
			   SaveRStackP non_local_state, RStackP rstack,
			   RuleP handler_rule, TableP table, unsigned indent)
{
    OStreamP ostream = c_out_info_ostream(info);
    EntryP   entry   = non_local_entry_get_initialiser(non_local);

    if (entry) {
	EntryP      type;
	BoolT       reference;
	EntryP      translation = rstack_get_translation(non_local_state,
							 non_local->name,
							 &type, &reference);
	KeyP        key         = entry_key(entry);
	ActionP     action      = entry_get_action(entry);
	TypeTupleP  param       = action_param(action);
	CCodeP      code        = action_get_code(action);
	BoolT       copies;
	TypeTupleT  args;
	TypeTupleT  result_args;
	SaveRStackT state;

	c_output_key_message (info, "/* BEGINNING OF INITIALISER: ", key,
			      " */", indent);
	c_output_open(info, indent);
	rstack_save_state(rstack, &state);
	rstack_push_frame(rstack);
	types_init(&args);
	if (!types_equal_zero_tuple(param)) {
	    types_add_name_and_type(&args, translation, type, reference);
	}
	types_init(&result_args);
	types_add_name_and_type(&result_args, non_local->name, type, FALSE);
	copies = c_output_required_copies(info, c_code_param(code),
					  &args, rstack, &state,
					  indent + C_INDENT_STEP, table);
	if (copies) {
	    c_output_open(info, indent + C_INDENT_STEP);
	}
	rstack_save_state(rstack, &state);
	c_output_location(info, c_code_file(code), c_code_line(code));
	c_output_c_code_action(info, code, &args, &result_args, &state,
			       handler_rule);
	c_output_location(info, ostream_name(ostream),
			  ostream_line(ostream) + 1);
	rstack_pop_frame(rstack);
	if (copies) {
	    c_output_close(info, indent + C_INDENT_STEP);
	}
	c_output_close(info, indent);
	c_output_key_message (info, "/* END OF INITIALISER: ", key, " */",
			      indent);
	types_destroy(&result_args);
	types_destroy(&args);
    }
}

static void
c_output_restore_non_locals_1(EntryP from, EntryP to, GenericP gclosure)
{
    NonLocalClosureP closure = (NonLocalClosureP)gclosure;
    COutputInfoP     info    = closure->info;
    SaveRStackP      state   = closure->state;
    unsigned         indent  = closure->indent;

    c_output_assign(info, to, from, state, state, indent);
}

/*--------------------------------------------------------------------------*/

void
c_output_non_locals(COutputInfoP info, NonLocalListP non_locals)
{
    OStreamP       ostream = c_out_info_ostream(info);
    NonLocalEntryP non_local;

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
c_output_declare_non_locals(COutputInfoP info, NonLocalListP non_locals)
{
    OStreamP       ostream = c_out_info_ostream(info);
    NonLocalEntryP non_local;

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
c_output_save_non_locals(COutputInfoP info, RuleP rule, unsigned indent,
			 RStackP rstack, RStackP non_local_stack,
			 RuleP handler_rule, TableP table)
{
    OStreamP       ostream    = c_out_info_ostream(info);
    NStringP       in_prefix  = c_out_info_in_prefix(info);
    NonLocalListP  non_locals = rule_non_locals(rule);
    NonLocalEntryP non_local;
    SaveRStackT    state;
    SaveRStackT    non_local_state;

    for (non_local = non_locals->head; non_local;
	 non_local = non_local->next) {
	EntryP entry = table_add_generated_name(table);

	output_indent(c_out_info_info(info), indent);
	c_output_mapped_key(info, non_local->type);
	write_char(ostream, ' ');
	c_output_key(info, entry_key(entry), in_prefix);
	write_newline(ostream);
	rstack_add_translation(non_local_stack, non_local->name, entry,
			       non_local->type, FALSE);
	rstack_add_translation(rstack, entry, entry, non_local->type, FALSE);
    }
    write_newline(ostream);
    rstack_save_state(rstack, &state);
    rstack_save_state(non_local_stack, &non_local_state);
    for (non_local = non_locals->head; non_local;
	 non_local = non_local->next) {
	EntryP type;
	BoolT  reference;
	EntryP entry = rstack_get_translation(&non_local_state,
					      non_local->name, &type,
					      &reference);

	ASSERT((entry != NIL(EntryP)) && (type == non_local->type) &&
	       (!reference));
	c_output_assign(info, non_local->name, entry, &state, &state, indent);
    }
    for (non_local = non_locals->head; non_local;
	 non_local = non_local->next) {
	c_output_save_non_locals_1(info, non_local, &non_local_state,
				   rstack, handler_rule, table, indent);
    }
    rstack_save_state(non_local_stack, rule_non_local_state(rule));
}

void
c_output_restore_non_locals(COutputInfoP info, RuleP rule, unsigned indent,
			    RStackP rstack, RStackP non_local_stack)
{
    NonLocalClosureT closure;
    SaveRStackT      state;

    rstack_save_state(rstack, &state);
    closure.info   = info;
    closure.state  = &state;
    closure.indent = indent;
    rstack_apply_for_non_locals(non_local_stack, rule_non_local_state(rule),
				c_output_restore_non_locals_1,
				(GenericP) &closure);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../output" "../generated")
 * end:
**/
