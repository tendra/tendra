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


/*** c-out-types.c --- Output type objects.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the type output routines for C.
 *
 *** Change Log:
 * $Log: c-out-types.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:43  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:56:40  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:20  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "c-out-types.h"
#include "action.h"
#include "basic.h"
#include "c-code.h"
#include "c-out-key.h"
#include "entry.h"
#include "name.h"
#include "output.h"
#include "rstack.h"
#include "type.h"

/*--------------------------------------------------------------------------*/

static void
c_output_param_assign PROTO_N ((info, inputs))
		      PROTO_T (COutputInfoP info X
			       TypeTupleP   inputs)
{
    OStreamP        ostream = c_out_info_ostream (info);
    TypeTupleEntryP ptr;

    for (ptr = inputs->head; ptr; ptr = ptr->next) {
	TypeP  type = entry_get_type (ptr->type);
	CCodeP code;

	if ((!(ptr->reference)) &&
	    ((code = type_get_param_assign_code (type)) != NIL (CCodeP))) {
	    KeyP key = entry_key (ptr->type);

	    c_output_key_message (info, "/* BEGINNING OF PARAM ASSIGNMENT: ",
				  key, " */", C_INDENT_STEP);
	    c_output_open (info, C_INDENT_STEP);
	    c_output_location (info, c_code_file (code),
			       c_code_line (code));
	    c_output_c_code_param_assign (info, code, ptr->type, ptr->name);
	    c_output_location (info, ostream_name (ostream),
			       ostream_line (ostream) + 1);
	    c_output_close (info, C_INDENT_STEP);
	    c_output_key_message (info, "/* END OF PARAM ASSIGNMENT: ",
				  key, " */", C_INDENT_STEP);
	}
    }
}

static void
c_output_non_ansi_params PROTO_N ((info, inputs, outputs))
			 PROTO_T (COutputInfoP info X
				  TypeTupleP   inputs X
				  TypeTupleP   outputs)
{
    OStreamP        ostream    = c_out_info_ostream (info);
    NStringP        in_prefix  = c_out_info_in_prefix (info);
    NStringP        out_prefix = c_out_info_out_prefix (info);
    CStringP        sep        = "";
    TypeTupleEntryP ptr;

    write_char (ostream, '(');
    for (ptr = inputs->head; ptr; ptr = ptr->next) {
	write_cstring (ostream, sep);
	if ((!(ptr->reference)) &&
	    (type_get_assign_code (entry_get_type (ptr->type)) !=
	     NIL (GenericP))) {
	    c_output_key (info, entry_key (ptr->name), out_prefix);
	} else {
	    c_output_key (info, entry_key (ptr->name), in_prefix);
	}
	sep = ", ";
    }
    for (ptr = outputs->head; ptr; ptr = ptr->next) {
	write_cstring (ostream, sep);
	c_output_key (info, entry_key (ptr->name), out_prefix);
	sep = ", ";
    }
    write_char (ostream, ')');
}

static void
c_output_non_ansi_type_defn PROTO_N ((info, inputs, outputs))
			    PROTO_T (COutputInfoP info X
				     TypeTupleP   inputs X
				     TypeTupleP   outputs)
{
    OStreamP        ostream    = c_out_info_ostream (info);
    NStringP        in_prefix  = c_out_info_in_prefix (info);
    NStringP        out_prefix = c_out_info_out_prefix (info);
    BoolT           specials   = FALSE;
    TypeTupleEntryP ptr;

    c_output_non_ansi_params (info, inputs, outputs);
    write_newline (ostream);
    for (ptr = inputs->head; ptr; ptr = ptr->next) {
	output_indent (c_out_info_info (info), C_INDENT_FOR_PARAM);
	c_output_mapped_key (info, ptr->type);
	write_char (ostream, ' ');
	if (ptr->reference) {
	    write_char (ostream, '*');
	    c_output_key (info, entry_key (ptr->name), in_prefix);
	} else if (type_get_assign_code (entry_get_type (ptr->type)) !=
		   NIL (GenericP)) {
	    write_char (ostream, '*');
	    c_output_key (info, entry_key (ptr->name), out_prefix);
	    specials = TRUE;
	} else {
	    c_output_key (info, entry_key (ptr->name), in_prefix);
	}
	write_char (ostream, ';');
	write_newline (ostream);
    }
    for (ptr = outputs->head; ptr; ptr = ptr->next) {
	output_indent (c_out_info_info (info), C_INDENT_FOR_PARAM);
	c_output_mapped_key (info, ptr->type);
	write_cstring (ostream, " *");
	c_output_key (info, entry_key (ptr->name), out_prefix);
	write_char (ostream, ';');
	write_newline (ostream);
    }
    write_char (ostream, '{');
    write_newline (ostream);
    if (specials) {
	for (ptr = inputs->head; ptr; ptr = ptr->next) {
	    if ((!(ptr->reference)) &&
		(type_get_assign_code (entry_get_type (ptr->type)) !=
		 NIL (GenericP))) {
		output_indent (c_out_info_info (info), C_INDENT_STEP);
		c_output_mapped_key (info, ptr->type);
		write_char (ostream, ' ');
		c_output_key (info, entry_key (ptr->name), in_prefix);
		write_char (ostream, ';');
		write_newline (ostream);
	    }
	}
    }
    if (outputs->head) {
	for (ptr = outputs->head; ptr; ptr = ptr->next) {
	    output_indent (c_out_info_info (info), C_INDENT_STEP);
	    c_output_mapped_key (info, ptr->type);
	    write_char (ostream, ' ');
	    c_output_key (info, entry_key (ptr->name), in_prefix);
	    write_char (ostream, ';');
	    write_newline (ostream);
	}
    }
    if (specials || (outputs->head != NIL (TypeTupleEntryP))) {
	write_newline (ostream);
    }
    if (specials) {
	c_output_param_assign (info, inputs);
    }
}

static void
c_output_ansi_type_defn PROTO_N ((info, inputs, outputs))
			PROTO_T (COutputInfoP info X
				 TypeTupleP   inputs X
				 TypeTupleP   outputs)
{
    OStreamP        ostream    = c_out_info_ostream (info);
    NStringP        in_prefix  = c_out_info_in_prefix (info);
    NStringP        out_prefix = c_out_info_out_prefix (info);
    CStringP        sep        = "";
    BoolT           specials   = FALSE;
    TypeTupleEntryP ptr;
    BoolT           ossg       = c_out_info_get_ossg (info);

    if ((inputs->head == NIL (TypeTupleEntryP)) &&
	(outputs->head == NIL (TypeTupleEntryP))) {
	if (ossg) {
	    write_cstring (ostream, "PROTO_Z ()");
	} else {
	    write_cstring (ostream, "(void)");
	}
    } else {
	if (ossg) {
	    write_cstring (ostream, "PROTO_N (");
	    c_output_non_ansi_params (info, inputs, outputs);
	    write_char (ostream, ')');
	    write_newline (ostream);
	    write_cstring (ostream, "  PROTO_T ");
	}

	write_char (ostream, '(');
	for (ptr = inputs->head; ptr; ptr = ptr->next) {
	    write_cstring (ostream, sep);
	    c_output_mapped_key (info, ptr->type);
	    write_char (ostream, ' ');
	    if (ptr->reference) {
		write_char (ostream, '*');
		c_output_key (info, entry_key (ptr->name), in_prefix);
	    } else if (type_get_assign_code (entry_get_type (ptr->type)) !=
		       NIL (GenericP)) {
		write_char (ostream, '*');
		c_output_key (info, entry_key (ptr->name), out_prefix);
		specials = TRUE;
	    } else {
		c_output_key (info, entry_key (ptr->name), in_prefix);
	    }
	    sep = (ossg ? " X " : ", ");
	}
	for (ptr = outputs->head; ptr; ptr = ptr->next) {
	    write_cstring (ostream, sep);
	    c_output_mapped_key (info, ptr->type);
	    write_cstring (ostream, " *");
	    c_output_key (info, entry_key (ptr->name), out_prefix);
	    sep = (ossg ? " X " : ", ");
	}
	write_char (ostream, ')');
    }
    write_newline (ostream);
    write_char (ostream, '{');
    write_newline (ostream);
    if (specials) {
	for (ptr = inputs->head; ptr; ptr = ptr->next) {
	    if ((!(ptr->reference)) &&
		(type_get_assign_code (entry_get_type (ptr->type)) !=
		 NIL (GenericP))) {
		output_indent (c_out_info_info (info), C_INDENT_STEP);
		c_output_mapped_key (info, ptr->type);
		write_char (ostream, ' ');
		c_output_key (info, entry_key (ptr->name), in_prefix);
		write_char (ostream, ';');
		write_newline (ostream);
	    }
	}
    }
    if (outputs->head) {
	for (ptr = outputs->head; ptr; ptr = ptr->next) {
	    output_indent (c_out_info_info (info), C_INDENT_STEP);
	    c_output_mapped_key (info, ptr->type);
	    write_char (ostream, ' ');
	    c_output_key (info, entry_key (ptr->name), in_prefix);
	    write_char (ostream, ';');
	    write_newline (ostream);
	}
    }
    if (specials || (outputs->head != NIL (TypeTupleEntryP))) {
	write_newline (ostream);
    }
    if (specials) {
	c_output_param_assign (info, inputs);
    }
}

static EntryP
types_get_entry PROTO_N ((entry, state, type_ref, reference_ref))
		PROTO_T (EntryP      entry X
			 SaveRStackP state X
			 EntryP     *type_ref X
			 BoolT      *reference_ref)
{
    EntryP trans_entry;

    trans_entry = rstack_get_translation (state, entry, type_ref,
					  reference_ref);
    if ((trans_entry == NIL (EntryP)) && (entry_is_non_local (entry))) {
	trans_entry    = entry;
	*type_ref      = entry_get_non_local (entry);
	*reference_ref = FALSE;
    }
    ASSERT (trans_entry);
    return (trans_entry);
}

static KeyP
types_get_key PROTO_N ((entry, state, type_ref, reference_ref))
	      PROTO_T (EntryP      entry X
		       SaveRStackP state X
		       EntryP     *type_ref X
		       BoolT      *reference_ref)
{
    EntryP trans = types_get_entry (entry, state, type_ref, reference_ref);

    return (entry_key (trans));
}

/*--------------------------------------------------------------------------*/

void
c_output_assign PROTO_N ((info, in_entry, out_entry, in_state, out_state,
			  indent))
		PROTO_T (COutputInfoP info X
			 EntryP       in_entry X
			 EntryP       out_entry X
			 SaveRStackP  in_state X
			 SaveRStackP  out_state X
			 unsigned     indent)
{
    OStreamP ostream  = c_out_info_ostream (info);
    EntryP   in_type;
    EntryP   out_type;
    BoolT    in_reference;
    BoolT    out_reference;
    EntryP   in_name  = types_get_entry (in_entry, in_state, &in_type,
					 &in_reference);
    EntryP   out_name = types_get_entry (out_entry, out_state, &out_type,
					 &out_reference);

    ASSERT (in_type == out_type);
    if (in_name != out_name) {
	TypeP  type = entry_get_type (in_type);
	CCodeP code;

	if ((code = type_get_assign_code (type)) != NIL (CCodeP)) {
	    KeyP key = entry_key (in_type);

	    c_output_key_message (info, "/* BEGINNING OF ASSIGNMENT: ", key,
				  " */", indent);
	    c_output_open (info, indent);
	    c_output_location (info, c_code_file (code), c_code_line (code));
	    c_output_c_code_assign (info, code, in_type, in_name, out_name,
				    in_reference, out_reference);
	    c_output_location (info, ostream_name (ostream),
			       ostream_line (ostream) + 1);
	    c_output_close (info, indent);
	    c_output_key_message (info, "/* END OF ASSIGNMENT: ", key, " */",
				  indent);
	} else {
	    KeyP     in_key    = entry_key (in_name);
	    KeyP     out_key   = entry_key (out_name);
	    NStringP in_prefix = c_out_info_in_prefix (info);

	    output_indent (c_out_info_info (info), indent);
	    if (out_reference) {
		write_char (ostream, '*');
	    }
	    c_output_key (info, out_key, in_prefix);
	    write_cstring (ostream, " = ");
	    if (in_reference) {
		write_char (ostream, '*');
	    }
	    c_output_key (info, in_key, in_prefix);
	    write_char (ostream, ';');
	    write_newline (ostream);
	}
    }
}

void
c_output_type_decl PROTO_N ((info, inputs, outputs))
		   PROTO_T (COutputInfoP info X
			    TypeTupleP   inputs X
			    TypeTupleP   outputs)
{
    OStreamP ostream = c_out_info_ostream (info);

    if (c_out_info_get_prototypes (info)) {
	CStringP        sep  = "";
	TypeTupleEntryP ptr;
	BoolT           ossg = c_out_info_get_ossg (info);

	if (ossg) {
	    write_cstring (ostream, "PROTO_S (") ;
	}
	write_char (ostream, '(');
	for (ptr = inputs->head; ptr; ptr = ptr->next) {
	    write_cstring (ostream, sep);
	    c_output_mapped_key (info, ptr->type);
	    if ((ptr->reference) ||
		(type_get_assign_code (entry_get_type (ptr->type)) !=
		 NIL (GenericP))) {
		write_cstring (ostream, " *");
	    }
	    sep = ", ";
	}
	for (ptr = outputs->head; ptr; ptr = ptr->next) {
	    write_cstring (ostream, sep);
	    c_output_mapped_key (info, ptr->type);
	    write_cstring (ostream, " *");
	    sep = ", ";
	}
	if ((inputs->head == NIL (TypeTupleEntryP)) &&
	    (outputs->head == NIL (TypeTupleEntryP))) {
	    write_cstring (ostream, "void");
	}
	write_char (ostream, ')');
	if (ossg) {
	    write_char (ostream, ')');
	}
    } else {
	write_cstring (ostream, " ()");
    }
}

void
c_output_type_defn PROTO_N ((info, inputs, outputs))
		   PROTO_T (COutputInfoP info X
			    TypeTupleP   inputs X
			    TypeTupleP   outputs)
{
    if (c_out_info_get_prototypes (info)) {
	c_output_ansi_type_defn (info, inputs, outputs);
    } else {
	c_output_non_ansi_type_defn (info, inputs, outputs);
    }
}

void
c_output_result_assign PROTO_N ((info, outputs, indent))
		       PROTO_T (COutputInfoP info X
				TypeTupleP   outputs X
				unsigned     indent)
{
    OStreamP        ostream    = c_out_info_ostream (info);
    NStringP        in_prefix  = c_out_info_in_prefix (info);
    NStringP        out_prefix = c_out_info_out_prefix (info);
    TypeTupleEntryP ptr;

    for (ptr = outputs->head; ptr; ptr = ptr->next) {
	TypeP  type = entry_get_type (ptr->type);
	CCodeP code;

	if ((code = type_get_result_assign_code (type)) != NIL (CCodeP)) {
	    KeyP key = entry_key (ptr->type);

	    c_output_key_message (info, "/* BEGINNING OF RESULT ASSIGNMENT: ",
				  key, " */", indent);
	    c_output_open (info, indent);
	    c_output_location (info, c_code_file (code), c_code_line (code));
	    c_output_c_code_result_assign (info, code, ptr->type, ptr->name);
	    c_output_location (info, ostream_name (ostream),
			       ostream_line (ostream) + 1);
	    c_output_close (info, indent);
	    c_output_key_message (info, "/* END OF RESULT ASSIGNMENT: ", key,
				  " */", indent);
	} else {
	    output_indent (c_out_info_info (info), indent);
	    write_char (ostream, '*');
	    c_output_key (info, entry_key (ptr->name), out_prefix);
	    write_cstring (ostream, " = ");
	    c_output_key (info, entry_key (ptr->name), in_prefix);
	    write_char (ostream, ';');
	    write_newline (ostream);
	}
    }
}

void
c_output_alt_names PROTO_N ((info, names, exclude, state, indent))
		   PROTO_T (COutputInfoP info X
			    TypeTupleP   names X
			    TypeTupleP   exclude X
			    SaveRStackP  state X
			    unsigned     indent)
{
    OStreamP        ostream   = c_out_info_ostream (info);
    NStringP        in_prefix = c_out_info_in_prefix (info);
    BoolT           want_nl   = FALSE;
    TypeTupleEntryP ptr;

    for (ptr = names->head; ptr; ptr = ptr->next) {
	if (!types_contains (exclude, ptr->name)) {
	    EntryP type;
	    BoolT  reference;

	    output_indent (c_out_info_info (info), indent);
	    c_output_mapped_key (info, ptr->type);
	    write_char (ostream, ' ');
	    c_output_key (info, types_get_key (ptr->name, state, &type,
					       &reference), in_prefix);
	    ASSERT ((type == ptr->type) && (!reference));
	    write_char (ostream, ';');
	    write_newline (ostream);
	    want_nl = TRUE;
	}
    }
    if (want_nl) {
	write_newline (ostream);
    }
}

void
c_output_rule_params PROTO_N ((info, inputs, outputs, state))
		     PROTO_T (COutputInfoP info X
			      TypeTupleP   inputs X
			      TypeTupleP   outputs X
			      SaveRStackP  state)
{
    OStreamP        ostream   = c_out_info_ostream (info);
    NStringP        in_prefix = c_out_info_in_prefix (info);
    CStringP        sep       = "";
    TypeTupleEntryP ptr;

    for (ptr = inputs->head; ptr; ptr = ptr->next) {
	TypeP  type = entry_get_type (ptr->type);
	CCodeP code = type_get_param_assign_code (type);
	EntryP type_entry;
	BoolT  reference;
	KeyP   key  = types_get_key (ptr->name, state, &type_entry,
				     &reference);

	write_cstring (ostream, sep);
	if ((ptr->reference && (!reference)) ||
	    ((!ptr->reference) && (!reference) && (code != NIL (CCodeP)))) {
	    write_char (ostream, '&');
	} else if ((!ptr->reference) && reference && (code == NIL (CCodeP))) {
	    write_char (ostream, '*');
	}
	c_output_key (info, key, in_prefix);
	sep = ", ";
    }
    for (ptr = outputs->head; ptr; ptr = ptr->next) {
	EntryP type_entry;
	BoolT  reference;

	write_cstring (ostream, sep);
	write_char (ostream, '&');
	c_output_key (info, types_get_key (ptr->name, state, &type_entry,
					   &reference), in_prefix);
	ASSERT ((type_entry == ptr->type) && (!reference));
	sep = ", ";
    }
}

void
c_output_rename PROTO_N ((info, inputs, outputs, state, indent))
		PROTO_T (COutputInfoP info X
			 TypeTupleP   inputs X
			 TypeTupleP   outputs X
			 SaveRStackP  state X
			 unsigned     indent)
{
    TypeTupleEntryP in_ptr  = inputs->head;
    TypeTupleEntryP out_ptr = outputs->head;

    while (in_ptr) {
	ASSERT (out_ptr);
	c_output_assign (info, in_ptr->name, out_ptr->name, state, state,
			 indent);
	in_ptr  = in_ptr->next;
	out_ptr = out_ptr->next;
    }
    ASSERT (out_ptr == NIL (TypeTupleEntryP));
}

void
c_output_tail_decls PROTO_N ((info, inputs, in_state, outputs, out_state,
			      indent))
		    PROTO_T (COutputInfoP info X
			     TypeTupleP   inputs X
			     SaveRStackP  in_state X
			     TypeTupleP   outputs X
			     SaveRStackP  out_state X
			     unsigned     indent)
{
    TypeTupleEntryP in_ptr  = inputs->head;
    TypeTupleEntryP out_ptr = outputs->head;

    while (in_ptr) {
	ASSERT (out_ptr);
	c_output_assign (info, in_ptr->name, out_ptr->name, in_state,
			 out_state, indent);
	in_ptr  = in_ptr->next;
	out_ptr = out_ptr->next;
    }
    ASSERT (out_ptr == NIL (TypeTupleEntryP));
}

BoolT
c_output_required_copies PROTO_N ((info, param, args, rstack, astate, indent,
				   table))
			 PROTO_T (COutputInfoP info X
				  TypeTupleP   param X
				  TypeTupleP   args X
				  RStackP      rstack X
				  SaveRStackP  astate X
				  unsigned     indent X
				  TableP       table)
{
    OStreamP        ostream   = c_out_info_ostream (info);
    NStringP        in_prefix = c_out_info_in_prefix (info);
    TypeTupleEntryP ptr       = param->head;
    TypeTupleEntryP aptr      = args->head;
    BoolT           copies    = FALSE;
    SaveRStackT     state;

    rstack_save_state (rstack, &state);
    while (ptr) {
	ASSERT (aptr);
	if (ptr->mutated && (!ptr->reference)) {
	    EntryP entry = table_add_generated_name (table);

	    output_indent (c_out_info_info (info), indent);
	    c_output_mapped_key (info, ptr->type);
	    write_char (ostream, ' ');
	    c_output_key (info, entry_key (entry), in_prefix);
	    write_char (ostream, ';');
	    write_newline (ostream);
	    copies = TRUE;
	    rstack_add_translation (rstack, aptr->name, entry, aptr->type,
				    FALSE);
	    rstack_add_translation (rstack, entry, entry, aptr->type, FALSE);
	}
	ptr  = ptr->next;
	aptr = aptr->next;
    }
    ASSERT (aptr == NIL (TypeTupleEntryP));
    if (copies) {
	write_newline (ostream);
	for (aptr = args->head, ptr = param->head; ptr;
	     ptr = ptr->next, aptr = aptr->next) {
	    ASSERT (aptr);
	    if (ptr->mutated && (!ptr->reference)) {
		EntryP type;
		BoolT  reference;
		EntryP entry = rstack_get_translation (&state, aptr->name,
						       &type, &reference);

		ASSERT (entry);
		c_output_assign (info, aptr->name, entry, astate, &state,
				 indent);
	    }
	}
	ASSERT (aptr == NIL (TypeTupleEntryP));
    }
    return (copies);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../output" "../generated")
 * end:
**/
