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


/**** c-code.c --- SID C code ADT routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the C code ADT used to represent action definitions
 * for the C output language.
 *
 **** Change Log:
 * $Log: c-code.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:42  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1996/03/01  09:53:12  smf
 * c-code.c, c-out-info.c, c-out-info.h, c-output.c:
 * 	- improved unreachable code analysis;
 * 	- improved some output formatting;
 * 	- added support for comment or macro to mark unreachable code.
 *
 * Revision 1.2  1994/12/15  09:56:23  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:17  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "c-code.h"
#include "c-out-key.h"
#include "c-output.h"
#include "gen-errors.h"
#include "name.h"

/*--------------------------------------------------------------------------*/

static void
c_code_set_labels PROTO_N ((code))
		  PROTO_T (CCodeP code)
{
    CCodeItemP item;

    for (item = code->head; item; item = item->next) {
	if (item->type == CCT_LABEL) {
	    NameP name = entry_get_name (item->u.ident);

	    if (!name_has_label (name)) {
		name_set_label (name, c_out_next_label ());
	    }
	}
    }
}

static void
c_code_reset_labels PROTO_N ((code))
		    PROTO_T (CCodeP code)
{
    CCodeItemP item;

    for (item = code->head; item; item = item->next) {
	if (item->type == CCT_LABEL) {
	    NameP name = entry_get_name (item->u.ident);

	    name_reset_label (name);
	}
    }
}

static EntryP
c_code_get_translation PROTO_N ((state, translator, ident, type_ref,
			      reference_ref, entry_ref))
		       PROTO_T (SaveRStackP state X
				TypeBTransP translator X
				EntryP      ident X
				EntryP     *type_ref X
				BoolT      *reference_ref X
				EntryP     *entry_ref)
{
    EntryP entry = btrans_get_translation (translator, ident);
    EntryP stack_entry;

    ASSERT (entry);
    stack_entry = rstack_get_translation (state, entry, type_ref,
					  reference_ref);
    if ((stack_entry == NIL (EntryP)) && (entry_is_non_local (entry))) {
	stack_entry    = entry;
	*type_ref      = entry_get_non_local (entry);
	*reference_ref = FALSE;
    }
    ASSERT (stack_entry);
    if (entry_ref) {
	*entry_ref = entry;
    }
    return (stack_entry);
}

/*--------------------------------------------------------------------------*/

CCodeP
c_code_create PROTO_N ((file, line))
	      PROTO_T (CStringP file X
		       unsigned line)
{
    CCodeP code = ALLOCATE (CCodeT);

    code->head = NIL (CCodeItemP);
    code->tail = &(code->head);
    code->file = file;
    code->line = line;
    types_init (&(code->param));
    types_init (&(code->result));
    return (code);
}

void
c_code_append_string PROTO_N ((code, string))
		     PROTO_T (CCodeP   code X
			      NStringP string)
{
    CCodeItemP item = ALLOCATE (CCodeItemT);

    item->next    = NIL (CCodeItemP);
    item->type    = CCT_STRING;
    nstring_assign (&(item->u.string), string);
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_label PROTO_N ((code, string))
		    PROTO_T (CCodeP   code X
			     NStringP string)
{
    CCodeItemP item = ALLOCATE (CCodeItemT);

    item->next    = NIL (CCodeItemP);
    item->type    = CCT_LABEL;
    nstring_assign (&(item->u.string), string);
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_identifier PROTO_N ((code, string))
			 PROTO_T (CCodeP   code X
				  NStringP string)
{
    CCodeItemP item = ALLOCATE (CCodeItemT);

    item->next    = NIL (CCodeItemP);
    item->type    = CCT_IDENT;
    nstring_assign (&(item->u.string), string);
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_modifiable PROTO_N ((code, string))
			 PROTO_T (CCodeP   code X
				  NStringP string)
{
    CCodeItemP item = ALLOCATE (CCodeItemT);

    item->next    = NIL (CCodeItemP);
    item->type    = CCT_MOD_IDENT;
    nstring_assign (&(item->u.string), string);
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_reference PROTO_N ((code, string))
			PROTO_T (CCodeP   code X
				 NStringP string)
{
    CCodeItemP item = ALLOCATE (CCodeItemT);

    item->next    = NIL (CCodeItemP);
    item->type    = CCT_REF_IDENT;
    nstring_assign (&(item->u.string), string);
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_exception PROTO_N ((code))
			PROTO_T (CCodeP code)
{
    CCodeItemP item = ALLOCATE (CCodeItemT);

    item->next    = NIL (CCodeItemP);
    item->type    = CCT_EXCEPTION;
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_advance PROTO_N ((code))
		      PROTO_T (CCodeP code)
{
    CCodeItemP item = ALLOCATE (CCodeItemT);

    item->next    = NIL (CCodeItemP);
    item->type    = CCT_ADVANCE;
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_append_terminal PROTO_N ((code))
		       PROTO_T (CCodeP code)
{
    CCodeItemP item = ALLOCATE (CCodeItemT);

    item->next    = NIL (CCodeItemP);
    item->type    = CCT_TERMINAL;
    *(code->tail) = item;
    code->tail    = &(item->next);
}

void
c_code_check PROTO_N ((code, exceptions, param_op, param, result, table))
	     PROTO_T (CCodeP     code X
		      BoolT      exceptions X
		      BoolT      param_op X
		      TypeTupleP param X
		      TypeTupleP result X
		      TableP     table)
{
    CCodeItemP item;
    EntryP     entry;

    for (item = code->head; item; item = item->next) {
	switch (item->type) EXHAUSTIVE {
	  case CCT_IDENT:
	    entry         = table_add_name (table, &(item->u.string));
	    item->u.ident = entry;
	    if (((param == NIL (TypeTupleP)) ||
		 (!types_contains (param, entry))) &&
		((result == NIL (TypeTupleP)) ||
		 (!types_contains (result, entry)))) {
		E_bad_id_substitution (c_code_file (code), c_code_line (code),
				       entry);
	    } else if (result) {
		name_used (entry_get_name (entry));
	    }
	    break;
	  case CCT_MOD_IDENT:
	    entry         = table_add_name (table, &(item->u.string));
	    item->u.ident = entry;
	    if (exceptions) {
		if ((param == NIL (TypeTupleP)) ||
		    (!types_mutated (param, entry))) {
		    E_bad_mod_id_substitution (c_code_file (code),
					       c_code_line (code), entry);
		}
	    } else {
		E_mod_id_in_assign (c_code_file (code), c_code_line (code),
				    entry);
	    }
	    break;
	  case CCT_REF_IDENT:
	    entry         = table_add_name (table, &(item->u.string));
	    item->u.ident = entry;
	    if (!param_op) {
		if ((param == NIL (TypeTupleP)) ||
		    (!types_contains (param, entry))) {
		    E_bad_ref_id_substitution (c_code_file (code),
					       c_code_line (code), entry);
		}
	    } else {
		E_ref_id_in_param_op (c_code_file (code), c_code_line (code),
				      entry);
	    }
	    break;
	  case CCT_LABEL:
	    entry         = table_add_name (table, &(item->u.string));
	    item->u.ident = entry;
	    if ((param == NIL (TypeTupleP)) && (result == NIL (TypeTupleP))) {
		E_bad_label_substitution (c_code_file (code),
					  c_code_line (code), entry);
	    }
	    break;
	  case CCT_EXCEPTION:
	    if (!exceptions) {
		E_bad_exception_substitution (c_code_file (code),
					      c_code_line (code));
	    }
	    break;
	  case CCT_ADVANCE:
	    if (!exceptions) {
		E_bad_advance_substitution (c_code_file (code),
					    c_code_line (code));
	    }
	    break;
	  case CCT_TERMINAL:
	    if (!exceptions) {
		E_bad_terminal_substitution (c_code_file (code),
					     c_code_line (code));
	    }
	    break;
	  case CCT_STRING:
	    break;
	}
    }
    if (result) {
	types_check_used (result, E_code_undefined_result, (GenericP) code);
	for (item = code->head; item; item = item->next) {
	    if (item->type == CCT_IDENT) {
		name_not_used (entry_get_name (item->u.ident));
	    }
	}
    }
    if (param) {
	types_assign (&(code->param), param);
    }
    if (result) {
	types_assign (&(code->result), result);
    }
}

#ifdef FS_FAST
#undef c_code_file
#endif /* defined (FS_FAST) */
CStringP
c_code_file PROTO_N ((code))
	    PROTO_T (CCodeP code)
{
    return (code->file);
}
#ifdef FS_FAST
#define c_code_file(c) ((c)->file)
#endif /* defined(FS_FAST) */

#ifdef FS_FAST
#undef c_code_line
#endif /* defined (FS_FAST) */
unsigned
c_code_line PROTO_N ((code))
	    PROTO_T (CCodeP code)
{
    return (code->line);
}
#ifdef FS_FAST
#define c_code_line(c) ((c)->line)
#endif /* defined(FS_FAST) */

TypeTupleP
c_code_param PROTO_N ((code))
	     PROTO_T (CCodeP code)
{
    return (&(code->param));
}

TypeTupleP
c_code_result PROTO_N ((code))
	      PROTO_T (CCodeP code)
{
    return (&(code->result));
}

void
c_code_deallocate PROTO_N ((code))
		  PROTO_T (CCodeP code)
{
    CCodeItemP item = code->head;

    while (item) {
	CCodeItemP next = item->next;

	switch (item->type) EXHAUSTIVE {
	  case CCT_STRING:
	    nstring_destroy (&(item->u.string));
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
	DEALLOCATE (item);
	item = next;
    }
    types_destroy (&(code->param));
    types_destroy (&(code->result));
    DEALLOCATE (code);
}

void
c_output_c_code_action PROTO_N ((info, code, param, result, state,
				 handler_rule))
		       PROTO_T (COutputInfoP info X
				CCodeP       code X
				TypeTupleP   param X
				TypeTupleP   result X
				SaveRStackP  state X
				RuleP        handler_rule)
{
    OStreamP    ostream      = c_out_info_ostream (info);
    NStringP    label_prefix = c_out_info_label_prefix (info);
    NStringP    in_prefix    = c_out_info_in_prefix (info);
    CCodeItemP  item;
    EntryP      stack_entry;
    EntryP      entry;
    EntryP      stack_type;
    BoolT       stack_reference;
    BoolT       use_cast;
    TypeBTransT translator;

    c_code_set_labels (code);
    btrans_init (&translator);
    btrans_add_translations (&translator, &(code->param), param);
    btrans_add_translations (&translator, &(code->result), result);
    for (item = code->head; item; item = item->next) {
	switch (item->type) EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring (ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	    write_nstring (ostream, label_prefix);
	    write_unsigned (ostream,
			    name_get_label (entry_get_name (item->u.ident)));
	    break;
	  case CCT_IDENT:
	    stack_entry = c_code_get_translation (state, &translator,
						  item->u.ident, &stack_type,
						  &stack_reference, &entry);
	    use_cast = (types_contains (param, entry) &&
			c_out_info_get_casts (info));
	    if (use_cast) {
		write_cstring (ostream, "((");
		c_output_mapped_key (info, stack_type);
		write_cstring (ostream, ") (");
	    } else {
		write_char (ostream, '(');
	    }
	    if (stack_reference) {
		write_char (ostream, '*');
	    }
	    c_output_key (info, entry_key (stack_entry), in_prefix);
	    if (use_cast) {
		write_cstring (ostream, "))");
	    } else {
		write_char (ostream, ')');
	    }
	    break;
	  case CCT_MOD_IDENT:
	    stack_entry = c_code_get_translation (state, &translator,
						  item->u.ident, &stack_type,
						  &stack_reference,
						  NIL (EntryP *));
	    write_char (ostream, '(');
	    if (stack_reference) {
		write_char (ostream, '*');
	    }
	    c_output_key (info, entry_key (stack_entry), in_prefix);
	    write_char (ostream, ')');
	    break;
	  case CCT_REF_IDENT:
	    stack_entry = c_code_get_translation (state, &translator,
						  item->u.ident, &stack_type,
						  &stack_reference,
						  NIL (EntryP *));
	    write_char (ostream, '(');
	    if (!stack_reference) {
		write_char (ostream, '&');
	    }
	    c_output_key (info, entry_key (stack_entry), in_prefix);
	    write_char (ostream, ')');
	    break;
	  case CCT_EXCEPTION:
	    write_cstring (ostream, "goto ");
	    write_nstring (ostream, label_prefix);
	    write_unsigned (ostream, rule_get_handler_label (handler_rule));
	    break;
	  case CCT_ADVANCE:
	    write_cstring (ostream, "ADVANCE_LEXER");
	    break;
	  case CCT_TERMINAL:
	    write_cstring (ostream, "CURRENT_TERMINAL");
	    break;
	}
    }
    btrans_destroy (&translator);
    c_code_reset_labels (code);
}

void
c_output_c_code_basic PROTO_N ((info, code, result, state))
		      PROTO_T (COutputInfoP info X
			       CCodeP       code X
			       TypeTupleP   result X
			       SaveRStackP  state)
{
    OStreamP    ostream      = c_out_info_ostream (info);
    NStringP    label_prefix = c_out_info_label_prefix (info);
    NStringP    in_prefix    = c_out_info_in_prefix (info);
    CCodeItemP  item;
    EntryP      stack_entry;
    EntryP      stack_type;
    BoolT       stack_reference;
    TypeBTransT translator;

    c_code_set_labels (code);
    btrans_init (&translator);
    btrans_add_translations (&translator, &(code->result), result);
    for (item = code->head; item; item = item->next) {
	switch (item->type) EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring (ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	    write_nstring (ostream, label_prefix);
	    write_unsigned (ostream,
			    name_get_label (entry_get_name (item->u.ident)));
	    break;
	  case CCT_IDENT:
	    stack_entry = c_code_get_translation (state, &translator,
						  item->u.ident, &stack_type,
						  &stack_reference,
						  NIL (EntryP *));
	    c_output_key (info, entry_key (stack_entry), in_prefix);
	    break;
	  case CCT_MOD_IDENT:
	  case CCT_REF_IDENT:
	  case CCT_EXCEPTION:
	  case CCT_ADVANCE:
	  case CCT_TERMINAL:
	    UNREACHED;
	}
    }
    btrans_destroy (&translator);
    c_code_reset_labels (code);
}

void
c_output_c_code_assign PROTO_N ((info, code, type, from, to, from_reference,
			      to_reference))
		       PROTO_T (COutputInfoP info X
				CCodeP       code X
				EntryP       type X
				EntryP       from X
				EntryP       to X
				BoolT        from_reference X
				BoolT        to_reference)
{
    OStreamP   ostream      = c_out_info_ostream (info);
    NStringP   label_prefix = c_out_info_label_prefix (info);
    NStringP   in_prefix    = c_out_info_in_prefix (info);
    BoolT      is_param;
    BoolT      use_cast;
    CCodeItemP item;

    c_code_set_labels (code);
    for (item = code->head; item; item = item->next) {
	switch (item->type) EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring (ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	    write_nstring (ostream, label_prefix);
	    write_unsigned (ostream,
			    name_get_label (entry_get_name (item->u.ident)));
	    break;
	  case CCT_IDENT:
	    is_param = types_contains (&(code->param), item->u.ident);
	    use_cast = (is_param && c_out_info_get_casts (info));
	    if (use_cast) {
		write_cstring (ostream, "((");
		c_output_mapped_key (info, type);
		write_cstring (ostream, ") (");
	    } else {
		write_char (ostream, '(');
	    }
	    if (is_param) {
		if (from_reference) {
		    write_char (ostream, '*');
		}
		c_output_key (info, entry_key (from), in_prefix);
	    } else {
		if (to_reference) {
		    write_char (ostream, '*');
		}
		c_output_key (info, entry_key (to), in_prefix);
	    }
	    if (use_cast) {
		write_cstring (ostream, "))");
	    } else {
		write_char (ostream, ')');
	    }
	    break;
	  case CCT_REF_IDENT:
	    write_char (ostream, '(');
	    if (!from_reference) {
		write_char (ostream, '&');
	    }
	    c_output_key (info, entry_key (from), in_prefix);
	    write_char (ostream, ')');
	    break;
	  case CCT_MOD_IDENT:
	  case CCT_EXCEPTION:
	  case CCT_ADVANCE:
	  case CCT_TERMINAL:
	    UNREACHED;
	}
    }
    c_code_reset_labels (code);
}

void
c_output_c_code_param_assign PROTO_N ((info, code, type, entry))
			     PROTO_T (COutputInfoP info X
				      CCodeP       code X
				      EntryP       type X
				      EntryP       entry)
{
    OStreamP   ostream      = c_out_info_ostream (info);
    NStringP   label_prefix = c_out_info_label_prefix (info);
    NStringP   in_prefix    = c_out_info_in_prefix (info);
    NStringP   out_prefix   = c_out_info_out_prefix (info);
    CCodeItemP item;

    c_code_set_labels (code);
    for (item = code->head; item; item = item->next) {
	switch (item->type) EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring (ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	    write_nstring (ostream, label_prefix);
	    write_unsigned (ostream,
			    name_get_label (entry_get_name (item->u.ident)));
	    break;
	  case CCT_IDENT:
	    if (types_contains (&(code->param), item->u.ident)) {
		BoolT use_cast = c_out_info_get_casts (info);

		if (use_cast) {
		    write_cstring (ostream, "((");
		    c_output_mapped_key (info, type);
		    write_cstring (ostream, " *) (");
		}
		c_output_key (info, entry_key (entry), out_prefix);
		if (use_cast) {
		    write_cstring (ostream, "))");
		}
	    } else {
		c_output_key (info, entry_key (entry), in_prefix);
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
    c_code_reset_labels (code);
}

void
c_output_c_code_result_assign PROTO_N ((info, code, type, entry))
			      PROTO_T (COutputInfoP info X
				       CCodeP       code X
				       EntryP       type X
				       EntryP       entry)
{
    OStreamP   ostream      = c_out_info_ostream (info);
    NStringP   label_prefix = c_out_info_label_prefix (info);
    NStringP   in_prefix    = c_out_info_in_prefix (info);
    NStringP   out_prefix   = c_out_info_out_prefix (info);
    CCodeItemP item;

    c_code_set_labels (code);
    for (item = code->head; item; item = item->next) {
	switch (item->type) EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring (ostream, &(item->u.string));
	    break;
	  case CCT_LABEL:
	    write_nstring (ostream, label_prefix);
	    write_unsigned (ostream,
			    name_get_label (entry_get_name (item->u.ident)));
	    break;
	  case CCT_IDENT:
	    if (types_contains (&(code->param), item->u.ident)) {
		BoolT use_cast = c_out_info_get_casts (info);

		if (use_cast) {
		    write_cstring (ostream, "((");
		    c_output_mapped_key (info, type);
		    write_cstring (ostream, ") (");
		}
		c_output_key (info, entry_key (entry), in_prefix);
		if (use_cast) {
		    write_cstring (ostream, "))");
		}
	    } else {
		c_output_key (info, entry_key (entry), out_prefix);
	    }
	    break;
	  case CCT_REF_IDENT:
	    write_cstring (ostream, "(&");
	    c_output_key (info, entry_key (entry), in_prefix);
	    write_char (ostream, ')');
	    break;
	  case CCT_MOD_IDENT:
	  case CCT_EXCEPTION:
	  case CCT_ADVANCE:
	  case CCT_TERMINAL:
	    UNREACHED;
	}
    }
    c_code_reset_labels (code);
}

void
c_output_c_code PROTO_N ((info, code))
		PROTO_T (COutputInfoP info X
			 CCodeP       code)
{
    OStreamP   ostream = c_out_info_ostream (info);
    CCodeItemP item;

    for (item = code->head; item; item = item->next) {
	switch (item->type) EXHAUSTIVE {
	  case CCT_STRING:
	    write_nstring (ostream, &(item->u.string));
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

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../output" "../generated")
 * end:
**/
