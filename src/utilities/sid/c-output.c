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


/*** c-output.c --- Output routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the SID output routines.
 *
 *** Change Log:
 * $Log: c-output.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:43  release
 * First version to be checked into rolling release.
 *
 * Revision 1.6  1996/03/01  09:53:17  smf
 * c-code.c, c-out-info.c, c-out-info.h, c-output.c:
 * 	- improved unreachable code analysis;
 * 	- improved some output formatting;
 * 	- added support for comment or macro to mark unreachable code.
 *
 * Revision 1.5  1996/02/28  15:52:05  smf
 * Fixed a bug that occured when a rule with a single alternative and an
 * exception handler was inlined into another rule.  The bug caused the inner
 * rule's exception handler to handle any exceptions that occur in the enclosing
 * rule.
 *
 * Revision 1.4  1994/12/23  09:44:47  smf
 * Fixing "CR94_227.sid-exception-optimisation-bug" - corrected exception
 * terminal checking.
 *
 * Revision 1.3  1994/12/15  09:56:43  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.2  1994/11/11  11:42:32  smf
 * Fixed the number of the error terminal, as it was one higher than necessary.
 *
 * Revision 1.1.1.1  1994/07/25  16:04:20  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "c-output.h"
#include "action.h"
#include "basic.h"
#include "c-code.h"
#include "c-out-key.h"
#include "c-out-nl.h"
#include "c-out-types.h"
#include "dstring.h"
#include "gen-errors.h"
#include "output.h"
#include "name.h"
#include "rstack.h"
#include "rule.h"
#include "type.h"

/*--------------------------------------------------------------------------*/

typedef struct COutClosureT {
    COutputInfoP		info;
    TableP			table;
    EntryP			predicate_id;
    EntryP			predicate_type;
    unsigned			error_terminal;
} COutClosureT, *COutClosureP;

/*--------------------------------------------------------------------------*/

static unsigned out_current_label;

/*--------------------------------------------------------------------------*/

static void
c_output_indent PROTO_N ((info, indent))
		PROTO_T (COutputInfoP info X
			 unsigned     indent)
{
    output_indent (c_out_info_info (info), indent);
}
#ifdef FS_FAST
#define c_output_indent(info, indent) \
	output_indent (c_out_info_info (info), indent)
#endif /* defined (FS_FAST) */

static void
c_output_identification PROTO_N ((info))
			PROTO_T (COutputInfoP info)
{
    OStreamP ostream = c_out_info_ostream (info);

    write_cstring (ostream, "/*");
    write_newline (ostream);
    write_cstring (ostream, " * Automatically generated from the files:");
    write_newline (ostream);
    write_cstring (ostream, " *\t");
    write_cstring (ostream, c_out_info_source_name (info));
    write_newline (ostream);
    write_cstring (ostream, " * and");
    write_newline (ostream);
    write_cstring (ostream, " *\t");
    write_cstring (ostream, c_out_info_c_source_name (info));
    write_newline (ostream);
    write_cstring (ostream, " * by:");
    write_newline (ostream);
    write_cstring (ostream, " *\t");
    write_cstring (ostream, c_out_info_program_name (info));
    write_newline (ostream);
    write_cstring (ostream, " */");
    write_newline (ostream);
    write_newline (ostream);
}

static void
c_output_declaration_1 PROTO_N ((info, rule))
		       PROTO_T (COutputInfoP info X
				RuleP        rule)
{
    OStreamP ostream = c_out_info_ostream (info);
    EntryP   entry   = rule_entry (rule);
  
    if (rule_is_required (rule)) {
	write_cstring (ostream, "extern void ");
    } else if (rule_needs_function (rule)) {
	if (c_out_info_get_split (info) != 0) {
	    write_cstring (ostream, "extern void ");
	} else {
	    write_cstring (ostream, "static void ");
	}
    } else {
	return;
    }
    c_output_mapped_key (info, entry);
    write_char (ostream, ' ');
    c_output_type_decl (info, rule_param (rule), rule_result (rule));
    write_char (ostream, ';');
    write_newline (ostream);
}

static void
c_output_declaration PROTO_N ((entry, gclosure))
		     PROTO_T (EntryP   entry X
			      GenericP gclosure)
{
    if (entry_is_rule (entry)) {
	RuleP        rule = entry_get_rule (entry);
	COutputInfoP info = (COutputInfoP) gclosure;

	c_output_declaration_1 (info, rule);
    }
}

static void
c_output_ext_declaration_1 PROTO_N ((info, rule))
			   PROTO_T (COutputInfoP info X
				    RuleP        rule)
{
    OStreamP ostream = c_out_info_ostream (info);
    EntryP   entry   = rule_entry (rule);
  
    if (rule_is_required (rule)) {
	write_cstring (ostream, "extern void ");
    } else {
	return;
    }
    c_output_mapped_key (info, entry);
    write_char (ostream, ' ');
    c_output_type_decl (info, rule_param (rule), rule_result (rule));
    write_char (ostream, ';');
    write_newline (ostream);
}

static void
c_output_ext_declaration PROTO_N ((entry, gclosure))
			 PROTO_T (EntryP   entry X
				  GenericP gclosure)
{
    if (entry_is_rule (entry)) {
	RuleP        rule = entry_get_rule (entry);
	COutputInfoP info = (COutputInfoP) gclosure;

	c_output_ext_declaration_1 (info, rule);
    }
}

static void
c_output_terminal_1 PROTO_N ((info, entry))
		    PROTO_T (COutputInfoP info X
			     EntryP       entry)
{
    OStreamP ostream = c_out_info_ostream (info);
    BasicP   basic   = entry_get_basic (entry);

    write_cstring (ostream, "#define ");
    c_output_mapped_key (info, entry);
    write_cstring (ostream, " (");
    write_unsigned (ostream, basic_terminal (basic));
    write_char (ostream, ')');
    write_newline (ostream);
}

static void
c_output_terminal PROTO_N ((entry, gclosure))
		  PROTO_T (EntryP   entry X
			   GenericP gclosure)
{
    if (entry_is_basic (entry)) {
	COutputInfoP info = (COutputInfoP) gclosure;

	c_output_terminal_1 (info, entry);
    }
}

static void
c_output_static_vars_1 PROTO_N ((entry, gclosure))
		       PROTO_T (EntryP   entry X
				GenericP gclosure)
{
    if (entry_is_rule (entry)) {
	COutputInfoP info = (COutputInfoP) gclosure;
	RuleP        rule = entry_get_rule (entry);

	c_output_non_locals (info, rule_non_locals (rule));
    }
}

static void
c_output_static_vars_2 PROTO_N ((entry, gclosure))
		       PROTO_T (EntryP   entry X
				GenericP gclosure)
{
    if (entry_is_rule (entry)) {
	COutputInfoP info = (COutputInfoP) gclosure;
	RuleP        rule = entry_get_rule (entry);

	c_output_declare_non_locals (info, rule_non_locals (rule));
    }
}

static void
c_output_static_vars PROTO_N ((info, grammar, def))
		     PROTO_T (COutputInfoP info X
			      GrammarP     grammar X
			      BoolT        def)
{
    OStreamP ostream        = c_out_info_ostream (info);
    TableP   table          = grammar_table (grammar);
    EntryP   predicate_type = grammar_get_predicate_type (grammar);

    if (def) {
	write_cstring (ostream, "/* BEGINNING OF STATIC VARIABLES */");
	write_newline (ostream);
	write_newline (ostream);
    }
    if (predicate_type) {
	if (def) {
	    if (c_out_info_get_split (info) == 0) {
		write_cstring (ostream, "static ");
	    }
	} else {
	    write_cstring (ostream, "extern ");
	}
	c_output_mapped_key (info, predicate_type);
	write_char (ostream, ' ');
	c_output_key (info, entry_key (grammar_get_predicate_id (grammar)),
		      c_out_info_in_prefix (info));
	write_char (ostream, ';');
	write_newline (ostream);
    }
    if (def) {
	table_iter (table, c_output_static_vars_1, (GenericP) info);
	write_newline (ostream);
    } else {
	table_iter (table, c_output_static_vars_2, (GenericP) info);
    }
}

static void
c_out_reset_labels PROTO_Z ()
{
    out_current_label = 0;
}

static void
c_output_label PROTO_N ((info, label, indent))
	       PROTO_T (COutputInfoP info X
			unsigned     label X
			unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);
    NStringP prefix  = c_out_info_label_prefix (info);

    c_output_indent (info, indent - C_INDENT_FOR_LABEL);
    write_nstring (ostream, prefix);
    write_unsigned (ostream, label);
    write_cstring (ostream, ":;");
    write_newline (ostream);
}

static void
c_output_jump PROTO_N ((info, label, indent))
	      PROTO_T (COutputInfoP info X
		       unsigned     label X
		       unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);
    NStringP prefix  = c_out_info_label_prefix (info);

    c_output_indent (info, indent);
    write_cstring (ostream, "goto ");
    write_nstring (ostream, prefix);
    write_unsigned (ostream, label);
    write_char (ostream, ';');
    write_newline (ostream);
}

static void
c_output_key_label PROTO_N ((info, key, label, indent))
		   PROTO_T (COutputInfoP info X
			    KeyP         key X
			    unsigned     label X
			    unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);

    c_output_indent (info, indent - C_INDENT_FOR_LABEL);
    c_output_label_key (info, key, label);
    write_cstring (ostream, ":;");
    write_newline (ostream);
}

static void
c_output_key_jump PROTO_N ((info, key, label, indent))
		  PROTO_T (COutputInfoP info X
			   KeyP         key X
			   unsigned     label X
			   unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);

    c_output_indent (info, indent);
    write_cstring (ostream, "goto ");
    c_output_label_key (info, key, label);
    write_char (ostream, ';');
    write_newline (ostream);
}

static void
c_output_switch PROTO_N ((info, indent))
		PROTO_T (COutputInfoP info X
			 unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);

    c_output_indent (info, indent);
    write_cstring (ostream, "switch (CURRENT_TERMINAL) {");
    write_newline (ostream);
}

static void
c_output_case PROTO_N ((info, terminal, indent))
	      PROTO_T (COutputInfoP info X
		       unsigned     terminal X
		       unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);

    c_output_indent (info, indent + C_INDENT_STEP - C_INDENT_FOR_CASE);
    write_cstring (ostream, "case ");
    write_unsigned (ostream, terminal);
    write_char (ostream, ':');
    write_newline (ostream);
}

static void
c_output_default PROTO_N ((info, indent))
		 PROTO_T (COutputInfoP info X
			  unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);

    c_output_indent (info, indent + C_INDENT_STEP - C_INDENT_FOR_CASE);
    write_cstring (ostream, "default:");
    write_newline (ostream);
}

static void
c_output_bitvec_cases PROTO_N ((info, bitvec, indent))
		      PROTO_T (COutputInfoP info X
			       BitVecP      bitvec X
			       unsigned     indent)
{
    OStreamP ostream  = c_out_info_ostream (info);
    unsigned terminal = bitvec_first_bit (bitvec);
    unsigned count    = 0;

    do {
	if (count ++ == 0) {
	    c_output_indent (info, indent + C_INDENT_STEP - C_INDENT_FOR_CASE);
	} else {
	    write_char (ostream, ' ');
	}
	write_cstring (ostream, "case ");
	write_unsigned (ostream, terminal);
	write_char (ostream, ':');
	if (count == 5) {
	    write_newline (ostream);
	    count = 0;
	}
    } while (bitvec_next_bit (bitvec, &terminal));
    if (count != 0) {
	write_newline (ostream);
    }
}

static void
c_output_break PROTO_N ((info, indent))
	       PROTO_T (COutputInfoP info X
			unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);

    c_output_indent (info, indent);
    write_cstring (ostream, "break;");
    write_newline (ostream);
}

static void
c_output_return PROTO_N ((info, indent))
		PROTO_T (COutputInfoP info X
			 unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);

    c_output_indent (info, indent);
    write_cstring (ostream, "return;");
    write_newline (ostream);
}

static void
c_output_error_if PROTO_N ((info, error_terminal, indent))
		  PROTO_T (COutputInfoP info X
			   unsigned     error_terminal X
			   unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);

    c_output_indent (info, indent);
    write_cstring (ostream, "if ((CURRENT_TERMINAL) == ");
    write_unsigned (ostream, error_terminal);
    write_cstring (ostream, ") {");
    write_newline (ostream);
}

static void
c_output_else PROTO_N ((info, indent))
	      PROTO_T (COutputInfoP info X
		       unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);

    c_output_indent (info, indent);
    write_cstring (ostream, "} else {");
    write_newline (ostream);
}

static void
c_output_restore PROTO_N ((info, handler_rule, outer_level, indent))
		 PROTO_T (COutputInfoP info X
			  RuleP        handler_rule X
			  BoolT        outer_level X
			  unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);

    if (outer_level) {
	c_output_return (info, indent);
    } else {
	c_output_indent (info, indent);
	write_cstring (ostream, "RESTORE_LEXER;");
	write_newline (ostream);
	c_output_jump (info, rule_get_handler_label (handler_rule), indent);
    }
}

static void
c_output_check PROTO_N ((info, handler_rule, outer_level, error_terminal,
			 indent))
	       PROTO_T (COutputInfoP info X
			RuleP        handler_rule X
			BoolT        outer_level X
			unsigned     error_terminal X
			unsigned     indent)
{
    c_output_error_if (info, error_terminal, indent);
    c_output_restore (info, handler_rule, outer_level, indent + C_INDENT_STEP);
    c_output_close (info, indent);
}

static void
c_output_advance PROTO_N ((info, indent))
		 PROTO_T (COutputInfoP info X
			  unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);

    c_output_indent (info, indent);
    write_cstring (ostream, "ADVANCE_LEXER;");
    write_newline (ostream);
}

static void
c_output_unreachable PROTO_N ((info, indent))
		     PROTO_T (COutputInfoP info X
			      unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);

    c_output_indent (info, indent);
    if (c_out_info_get_unreachable (info)) {
	write_cstring (ostream, "UNREACHED;");
    } else {
	write_cstring (ostream, "/*UNREACHED*/");
    }
    write_newline (ostream);
}

static void
c_output_basic_extract PROTO_N ((info, code, item, key, state, indent))
		       PROTO_T (COutputInfoP info X
				CCodeP       code X
				ItemP        item X
				KeyP         key X
				SaveRStackP  state X
				unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);

    c_output_key_message (info, "/* BEGINNING OF EXTRACT: ", key, " */",
			  indent);
    c_output_open (info, indent);
    c_output_location (info, c_code_file (code), c_code_line (code));
    c_output_c_code_basic (info, code, item_result (item), state);
    c_output_location (info, ostream_name (ostream),
		       ostream_line (ostream) + 1);
    c_output_close (info, indent);
    c_output_key_message (info, "/* END OF EXTRACT: ", key, " */", indent);
}

static void
c_output_basic_in_alt PROTO_N ((info, item, handler_rule, need_switch,
				need_check, outer_level, error_terminal, state,
				indent))
		      PROTO_T (COutputInfoP info X
			       ItemP        item X
			       RuleP        handler_rule X
			       BoolT        need_switch X
			       BoolT        need_check X
			       BoolT        outer_level X
			       unsigned     error_terminal X
			       SaveRStackP  state X
			       unsigned     indent)
{
    EntryP     entry       = item_entry (item);
    KeyP       key         = entry_key (entry);
    BasicP     basic       = entry_get_basic (entry);
    unsigned   terminal    = basic_terminal (basic);
    CCodeP     code        = basic_get_result_code (basic);
    unsigned   code_indent = (need_switch ? indent + C_INDENT_STEP : indent);

    if (need_switch) {
	c_output_switch (info, indent);
	c_output_case (info, terminal, indent);
	if (code) {
	    c_output_basic_extract (info, code, item, key, state, code_indent);
	}
	c_output_break (info, code_indent);
	if (need_check) {
	    c_output_case (info, error_terminal, indent);
	    c_output_restore (info, handler_rule, outer_level, code_indent);
	}
	c_output_default (info, indent);
	c_output_jump (info, rule_get_handler_label (handler_rule),
		       code_indent);
	c_output_close (info, indent);
    } else {
	ASSERT (!need_check);
	if (code) {
	    c_output_basic_extract (info, code, item, key, state, code_indent);
	}
    }
    c_output_advance (info, indent);
}

static void
c_output_tail_call PROTO_N ((info, item, handler_rule, need_check, outer_level,
			     error_terminal, rstack, non_local_stack, state,
			     indent))
		   PROTO_T (COutputInfoP info X
			    ItemP        item X
			    RuleP        handler_rule X
			    BoolT        need_check X
			    BoolT        outer_level X
			    unsigned     error_terminal X
			    RStackP      rstack X
			    RStackP      non_local_stack X
			    SaveRStackP  state X
			    unsigned     indent)
{
    unsigned code_indent = (need_check ? indent + C_INDENT_STEP : indent);
    EntryP   entry       = item_entry (item);
    RuleP    rule        = entry_get_rule (entry);
    KeyP     key         = entry_key (entry);

    if (need_check) {
	c_output_error_if (info, error_terminal, indent);
	c_output_restore (info, handler_rule, outer_level, code_indent);
	c_output_else (info, indent);
    }
    c_output_restore_non_locals (info, rule, indent, rstack, non_local_stack);
    c_output_tail_decls (info, item_param (item), state, rule_param (rule),
			 rule_rstack_state (rule), code_indent);
    c_output_key_jump (info, key, rule_get_start_label (rule), code_indent);
    if (need_check) {
	c_output_close (info, indent);
    }
}

static BoolT				c_output_rule
	PROTO_S ((COutputInfoP, RuleP, RuleP, EntryListP, BoolT, EntryP,
		  unsigned, unsigned, RStackP, RStackP, TableP));

static BoolT
c_output_rule_in_alt PROTO_N ((info, item, handler_rule, call_list, need_check,
			       outer_level, predicate_id, error_terminal,
			       indent, rstack, non_local_stack, table,
			       reachable_ref))
		     PROTO_T (COutputInfoP info X
			      ItemP        item X
			      RuleP        handler_rule X
			      EntryListP   call_list X
			      BoolT        need_check X
			      BoolT        outer_level X
			      EntryP       predicate_id X
			      unsigned     error_terminal X
			      unsigned     indent X
			      RStackP      rstack X
			      RStackP      non_local_stack X
			      TableP       table X
			      BoolT       *reachable_ref)
{
    OStreamP    ostream   = c_out_info_ostream (info);
    EntryP      entry     = item_entry (item);
    RuleP       rule      = entry_get_rule (entry);
    KeyP        key       = entry_key (entry);
    BoolT       tail_call = (item_is_tail_call (item) &&
			     rule_is_being_output (rule));
    SaveRStackT state;

    rstack_save_state (rstack, &state);
    if ((item_is_inlinable (item)) &&
	(tail_call || (!(rule_is_being_output (rule) ||
			 (rule_get_call_count (rule) > 1))))) {
	c_output_key_message (info, "/* BEGINNING OF INLINE: ", key, " */",
			      indent);
	if (tail_call) {
	    c_output_tail_call (info, item, handler_rule, need_check,
				outer_level, error_terminal, rstack,
				non_local_stack, &state, indent);
	    *reachable_ref = FALSE;
	} else {
	    unsigned code_indent = (indent + C_INDENT_STEP);
	    BoolT    copies;

	    c_output_open (info, indent);
	    rstack_push_frame (rstack);
	    copies = c_output_required_copies (info, rule_param (rule),
					       item_param (item), rstack,
					       &state, code_indent, table);
	    if (copies) {
		c_output_open (info, code_indent);
		code_indent += C_INDENT_STEP;
	    }
	    rstack_save_state (rstack, &state);
	    rstack_push_frame (rstack);
	    rstack_compute_formal_inlining (rstack, rule_param (rule),
					    item_param (item));
	    rstack_compute_formal_inlining (rstack, rule_result (rule),
					    item_result (item));
	    rstack_save_state (rstack, rule_rstack_state (rule));
	    if (!c_output_rule (info, rule, handler_rule,
				item_is_tail_call (item) ? call_list :
				rule_call_list (rule), need_check,
				predicate_id, error_terminal, code_indent,
				rstack, non_local_stack, table)) {
		*reachable_ref = FALSE;
	    }
	    rstack_pop_frame (rstack);
	    if (copies) {
		c_output_close (info, indent + C_INDENT_STEP);
	    }
	    rstack_pop_frame (rstack);
	    c_output_close (info, indent);
	}
	c_output_key_message (info, "/* END OF INLINE: ", key, " */", indent);
	return (FALSE);
    }
    if (need_check && outer_level) {
	c_output_check (info, handler_rule, TRUE, error_terminal, indent);
    }
    c_output_indent (info, indent);
    c_output_mapped_key (info, entry);
    write_cstring (ostream, " (");
    c_output_rule_params (info, item_param (item), item_result (item), &state);
    write_cstring (ostream, ");");
    write_newline (ostream);
    return (TRUE);
}

static void
c_output_action_in_alt PROTO_N ((info, item, handler_rule, need_check,
				 outer_level, error_terminal, rstack, indent,
				 table))
		       PROTO_T (COutputInfoP info X
				ItemP        item X
				RuleP        handler_rule X
				BoolT        need_check X
				BoolT        outer_level X
				unsigned     error_terminal X
				RStackP      rstack X
				unsigned     indent X
				TableP       table)
{
    OStreamP    ostream = c_out_info_ostream (info);
    EntryP      entry   = item_entry (item);
    ActionP     action  = entry_get_action (entry);
    KeyP        key     = entry_key (entry);
    CCodeP      code    = action_get_code (action);
    SaveRStackT state;
    BoolT       copies;

    if (need_check) {
	c_output_check (info, handler_rule, outer_level, error_terminal,
			indent);
    }
    c_output_key_message (info, "/* BEGINNING OF ACTION: ", key, " */",
			  indent);
    c_output_open (info, indent);
    rstack_save_state (rstack, &state);
    rstack_push_frame (rstack);
    copies = c_output_required_copies (info, c_code_param (code),
				       item_param (item), rstack, &state,
				       indent + C_INDENT_STEP, table);
    if (copies) {
	c_output_open (info, indent + C_INDENT_STEP);
    }
    rstack_save_state (rstack, &state);
    c_output_location (info, c_code_file (code), c_code_line (code));
    c_output_c_code_action (info, code, item_param (item),
			    item_result (item), &state, handler_rule);
    c_output_location (info, ostream_name (ostream),
		       ostream_line (ostream) + 1);
    rstack_pop_frame (rstack);
    if (copies) {
	c_output_close (info, indent + C_INDENT_STEP);
    }
    c_output_close (info, indent);
    c_output_key_message (info, "/* END OF ACTION: ", key, " */", indent);
}

static void
c_output_predicate_in_alt PROTO_N ((info, rule, item, initial, handler_rule,
				    needed_switch, need_check, outer_level,
				    predicate_id, error_terminal, rstack,
				    indent, table))
			  PROTO_T (COutputInfoP info X
				   RuleP        rule X
				   ItemP        item X
				   ItemP        initial X
				   RuleP        handler_rule X
				   BoolT        needed_switch X
				   BoolT        need_check X
				   BoolT        outer_level X
				   EntryP       predicate_id X
				   unsigned     error_terminal X
				   RStackP      rstack X
				   unsigned     indent X
				   TableP       table)
{
    OStreamP ostream = c_out_info_ostream (info);

    c_output_action_in_alt (info, item, handler_rule, need_check, outer_level,
			    error_terminal, rstack, indent, table);
    c_output_indent (info, indent);
    write_cstring (ostream, "if (!");
    c_output_key (info, entry_key (predicate_id), c_out_info_in_prefix (info));
    write_cstring (ostream, ")");
    write_newline (ostream);
    if ((item == initial) && (!needed_switch)) {
	unsigned label = c_out_next_label ();

	c_output_jump (info, label, indent + C_INDENT_STEP);
	rule_set_next_label (rule, label);
    } else {
	c_output_jump (info, rule_get_handler_label (handler_rule),
		       indent + C_INDENT_STEP);
    }
}

static BoolT
c_output_alt PROTO_N ((info, alt, rule, handler_rule, call_list, need_switch,
		       need_check, outer_level, predicate_id, error_terminal,
		       indent, rstack, non_local_stack, table))
	     PROTO_T (COutputInfoP info X
		      AltP         alt X
		      RuleP        rule X
		      RuleP        handler_rule X
		      EntryListP   call_list X
		      BoolT        need_switch X
		      BoolT        need_check X
		      BoolT        outer_level X
		      EntryP       predicate_id X
		      unsigned     error_terminal X
		      unsigned     indent X
		      RStackP      rstack X
		      RStackP      non_local_stack X
		      TableP       table)
{
    ItemP       initial       = alt_item_head (alt);
    BoolT       needed_switch = need_switch;
    unsigned    code_indent   = (indent + C_INDENT_STEP);
    BoolT       reachable     = TRUE;
    ItemP       item;
    SaveRStackT state;

    rstack_push_frame (rstack);
    rstack_compute_local_renaming (rstack, alt_names (alt), rule_result (rule),
				   table);
    rstack_save_state (rstack, &state);
    c_output_open (info, indent);
    c_output_alt_names (info, alt_names (alt), rule_result (rule), &state,
			code_indent);
    for (item = initial; item; item = item_next (item)) {
	switch (item_type (item)) EXHAUSTIVE {
	  case ET_BASIC:
	    c_output_basic_in_alt (info, item, handler_rule, need_switch,
				   need_check, outer_level, error_terminal,
				   &state, code_indent);
	    need_switch = TRUE;
	    need_check  = FALSE;
	    break;
	  case ET_RULE:
	    need_check  = c_output_rule_in_alt (info, item, handler_rule,
						call_list, need_check,
						outer_level, predicate_id,
						error_terminal, code_indent,
						rstack, non_local_stack, table,
						&reachable);
	    need_switch = TRUE;
	    break;
	  case ET_PREDICATE:
	    c_output_predicate_in_alt (info, rule, item, initial, handler_rule,
				       needed_switch, need_check, outer_level,
				       predicate_id, error_terminal, rstack,
				       code_indent, table);
	    need_switch = TRUE;
	    need_check  = FALSE;
	    break;
	  case ET_ACTION:
	    c_output_action_in_alt (info, item, handler_rule, need_check,
				    outer_level, error_terminal, rstack,
				    code_indent, table);
	    need_check = FALSE;
	    break;
	  case ET_RENAME:
	    if (need_check) {
		c_output_check (info, handler_rule, outer_level,
				error_terminal, code_indent);
	    }
	    c_output_rename (info, item_param (item), item_result (item),
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
	    c_output_check (info, handler_rule, outer_level, error_terminal,
			    code_indent);
	}
	if (item_is_predicate (initial) && (!needed_switch)) {
	    c_output_jump (info, rule_get_end_label (rule), code_indent);
	    reachable = FALSE;
	}
    }
    c_output_close (info, indent);
    if (!reachable) {
	c_output_unreachable (info, indent);
    }
    rstack_pop_frame (rstack);
    return (reachable);
}

static BoolT
c_output_rule PROTO_N ((info, rule, handler_rule, call_list, need_check,
			predicate_id, error_terminal, indent, rstack,
			non_local_stack, table))
	      PROTO_T (COutputInfoP info X
		       RuleP        rule X
		       RuleP        handler_rule X
		       EntryListP   call_list X
		       BoolT        need_check X
		       EntryP       predicate_id X
		       unsigned     error_terminal X
		       unsigned     indent X
		       RStackP      rstack X
		       RStackP      non_local_stack X
		       TableP       table)
{
    EntryP        entry            = rule_entry (rule);
    KeyP          key              = entry_key (entry);
    EntryListP    predicate_firsts = rule_predicate_first (rule);
    BoolT         predicates       = (!entry_list_is_empty (predicate_firsts));
    RuleP         old_handler_rule = handler_rule;
    BoolT         outer_level      = (old_handler_rule == rule);
    BoolT         reachable        = TRUE;
    unsigned      code_indent      = indent;
    NonLocalListP non_locals       = rule_non_locals (rule);
    BoolT         has_non_locals   = (!non_local_list_is_empty (non_locals));
    AltP          handler          = rule_get_handler (rule);
    BoolT         full_first_set   = bitvec_is_full (rule_first_set (rule));
    BoolT         one_alt          = rule_has_one_alt (rule);

    ASSERT (!rule_is_being_output (rule));
    rule_being_output (rule);
    rule_set_end_label (rule, c_out_next_label ());
    if (need_check && (predicates || has_non_locals || one_alt)) {
	c_output_check (info, handler_rule, outer_level, error_terminal,
			indent);
	need_check = FALSE;
    }
    if (outer_level) {
	rule_set_handler_label (rule, c_out_next_label ());
    } else if ((handler != NIL (AltP)) || has_non_locals) {
	handler_rule = rule;
	rule_set_handler_label (rule, c_out_next_label ());
    }
    if (entry_list_contains (call_list, entry)) {
	unsigned label = c_out_next_label ();

	c_output_key_label (info, key, label, indent);
	rule_set_start_label (rule, label);
    }
    if (has_non_locals) {
	c_output_open (info, indent);
	code_indent += C_INDENT_STEP;
	rstack_push_frame (rstack);
	rstack_push_frame (non_local_stack);
	c_output_save_non_locals (info, rule, code_indent, rstack,
				  non_local_stack, handler_rule, table);
    }
    if (one_alt) {
	if (!rule_has_empty_alt (rule)) {
	    AltP alt = rule_alt_head (rule);

	    reachable = c_output_alt (info, alt, rule, handler_rule, call_list,
				      TRUE, need_check, outer_level,
				      predicate_id, error_terminal,
				      code_indent, rstack, non_local_stack,
				      table);
	} else {
	    if (need_check) {
		c_output_check (info, handler_rule, outer_level,
				error_terminal, code_indent);
	    }
	    reachable  = TRUE;
	}
    } else {
	BoolT non_predicate_alts = TRUE;
	AltP  see_through_alt    = rule_see_through_alt (rule);
	AltP  alt;

	if (predicates) {
	    non_predicate_alts = FALSE;
	    for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
		ItemP item = alt_item_head (alt);

		if (item_is_predicate (item)) {
		    (void) c_output_alt (info, alt, rule, handler_rule,
					 call_list, FALSE, FALSE, FALSE,
					 predicate_id, error_terminal,
					 code_indent, rstack, non_local_stack,
					 table);
		    c_output_label (info, rule_get_next_label (rule),
				    code_indent);
		} else {
		    non_predicate_alts = TRUE;
		}
	    }
	}
	if (non_predicate_alts) {
	    reachable = FALSE;
	    c_output_switch (info, code_indent);
	    for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
		ItemP item = alt_item_head (alt);

		if (!item_is_predicate (item)) {
		    if (alt == see_through_alt) {
			ASSERT (!full_first_set);
			c_output_default (info, code_indent);
		    } else {
			c_output_bitvec_cases (info, alt_first_set (alt),
					       code_indent);
		    }
		    if (c_output_alt (info, alt, rule, handler_rule, call_list,
				      FALSE, FALSE, FALSE, predicate_id,
				      error_terminal,
				      code_indent + C_INDENT_STEP,
				      rstack, non_local_stack, table)) {
			c_output_break (info, code_indent + C_INDENT_STEP);
			reachable = TRUE;
		    }
		}
	    }
	    if (need_check) {
		c_output_case (info, error_terminal, code_indent);
		c_output_restore (info, handler_rule, outer_level,
				  code_indent + C_INDENT_STEP);
	    }
	    if ((see_through_alt == NIL (AltP)) && (!full_first_set)) {
		c_output_default (info, code_indent);
		if (!rule_has_empty_alt (rule)) {
		    c_output_jump (info, rule_get_handler_label (handler_rule),
				   code_indent + C_INDENT_STEP);
		} else {
		    c_output_break (info, code_indent + C_INDENT_STEP);
		    reachable = TRUE;
		}
	    }
	    c_output_close (info, code_indent);
	} else {
	    ASSERT (!need_check);
	    if (!rule_has_empty_alt (rule)) {
		c_output_jump (info, rule_get_handler_label (handler_rule),
			       code_indent);
	    }
	}
    }
    if (((handler != NIL (AltP)) || has_non_locals || outer_level) &&
	rule_used_handler_label (rule)) {
	if (reachable) {
	    if (outer_level && types_equal_zero_tuple (rule_result (rule)) &&
		(!has_non_locals)) {
		c_output_return (info, code_indent);
	    } else {
		c_output_jump (info, rule_get_end_label (rule), code_indent);
	    }
	} else {
	    c_output_unreachable (info, code_indent);
	}
	reachable = FALSE;
	if (handler) {
	    RuleP cleanup_handler_rule = old_handler_rule;

	    c_output_label (info, rule_get_handler_label (rule), code_indent);
	    reachable = TRUE;
	    if (outer_level || has_non_locals) {
		rule_set_handler_label (rule, c_out_next_label ());
		cleanup_handler_rule = rule;
	    }
	    if (!c_output_alt (info, handler, rule, cleanup_handler_rule,
			       call_list, TRUE, FALSE, FALSE, predicate_id,
			       error_terminal, code_indent, rstack,
			       non_local_stack, table)) {
		reachable = FALSE;
	    }
	}
	if ((outer_level || has_non_locals) &&
	    rule_used_handler_label (rule)) {
	    if (reachable) {
		c_output_jump (info, rule_get_end_label (rule), code_indent);
	    } else if (handler) {
		c_output_unreachable (info, code_indent);
	    }
	    c_output_label (info, rule_get_handler_label (rule), code_indent);
	    if (has_non_locals) {
		c_output_restore_non_locals (info, rule, code_indent, rstack,
					     non_local_stack);
	    }
	    if (outer_level) {
		OStreamP ostream = c_out_info_ostream (info);

		c_output_indent (info, code_indent);
		write_cstring (ostream, "SAVE_LEXER (");
		write_unsigned (ostream, error_terminal);
		write_cstring (ostream, ");");
		write_newline (ostream);
		c_output_return (info, code_indent);
	    } else {
		c_output_jump (info, rule_get_handler_label (old_handler_rule),
			       code_indent);
	    }
	    reachable = FALSE;
	}
    }
    if (rule_used_end_label (rule)) {
	c_output_label (info, rule_get_end_label (rule), code_indent);
	reachable = TRUE;
    }
    if (reachable) {
	if (has_non_locals) {
	    c_output_restore_non_locals (info, rule, code_indent, rstack,
					 non_local_stack);
	}
	if (outer_level) {
	    c_output_result_assign (info, rule_result (rule), code_indent);
	}
    }
    if (has_non_locals) {
	c_output_close (info, indent);
	rstack_pop_frame (non_local_stack);
	rstack_pop_frame (rstack);
    }
    rule_not_being_output (rule);
    return (reachable);
}

static void
c_output_definition_1 PROTO_N ((info, rule, predicate_id, predicate_type,
				error_terminal, table))
		      PROTO_T (COutputInfoP info X
			       RuleP        rule X
			       EntryP       predicate_id X
			       EntryP       predicate_type X
			       unsigned     error_terminal X
			       TableP       table)
{
    OStreamP ostream = c_out_info_ostream (info);
    EntryP   entry   = rule_entry (rule);
    unsigned split   = c_out_info_get_split (info);
    RStackT  rstack;
    RStackT  non_local_stack;

    if (rule_is_required (rule)) {
	write_cstring (ostream, "void");
    } else if (rule_needs_function (rule)) {
	if (split != 0) {
	    write_cstring (ostream, "void");
	} else {
	    write_cstring (ostream, "static void");
	}
    } else {
	return;
    }
    write_newline (ostream);
    c_output_mapped_key (info, entry);
    write_char (ostream, ' ');
    c_output_type_defn (info, rule_param (rule), rule_result (rule));
    c_out_reset_labels ();
    rstack_init (&rstack);
    rstack_push_frame (&rstack);
    rstack_add_translation (&rstack, predicate_id, predicate_id,
			    predicate_type, FALSE);
    rstack_compute_formal_renaming (&rstack, rule_param (rule));
    rstack_compute_formal_renaming (&rstack, rule_result (rule));
    rstack_save_state (&rstack, rule_rstack_state (rule));
    rstack_init (&non_local_stack);
    (void) c_output_rule (info, rule, rule, rule_call_list (rule), TRUE,
			  predicate_id, error_terminal, C_INDENT_STEP,
			  &rstack, &non_local_stack, table);
    write_char (ostream, '}');
    write_newline (ostream);
    write_newline (ostream);
    rstack_destroy (&rstack);
    rstack_destroy (&non_local_stack);
    if (split != 0) {
	if (ostream_line (ostream) >= split) {
	    CStringP     name    = ostream_gen_name (ostream);
	    CCodeP       header  = c_out_info_get_header1 (info);
	    write_cstring (ostream, "/* END OF FILE */");
	    write_newline (ostream);
	    ostream_close (ostream);
	    if (!ostream_open (ostream, name)) {
		E_cannot_open_output_file (name);
		UNREACHED;
	    }
	    c_output_identification (info);
	    write_cstring (ostream, "/* BEGINNING OF HEADER */");
	    write_newline (ostream);
	    write_newline (ostream);
	    write_cstring (ostream, "#define __SID_SPLIT");
	    write_newline (ostream);
	    c_output_location (info, c_code_file (header),
			       c_code_line (header));
	    c_output_c_code (info, header);
	    c_output_location (info, ostream_name (ostream),
			       ostream_line (ostream) + 1);
	    write_newline (ostream);
	}
    }
}

static void
c_output_definition PROTO_N ((entry, gclosure))
		    PROTO_T (EntryP   entry X
			     GenericP gclosure)
{
    if (entry_is_rule (entry)) {
	RuleP        rule           = entry_get_rule (entry);
	COutClosureP closure        = (COutClosureP) gclosure;
	COutputInfoP info           = closure->info;
	TableP       table          = closure->table;
	EntryP       predicate_id   = closure->predicate_id;
	EntryP       predicate_type = closure->predicate_type;
	unsigned     error_terminal = closure->error_terminal;

	c_output_definition_1 (info, rule, predicate_id, predicate_type,
			       error_terminal, table);
    }
}

/*--------------------------------------------------------------------------*/

void
c_output_parser PROTO_N ((info, grammar))
		PROTO_T (COutputInfoP info X
			 GrammarP     grammar)
{
    TableP       table   = grammar_table (grammar);
    OStreamP     ostream = c_out_info_ostream (info);
    CCodeP       header  = c_out_info_get_header1 (info);
    CCodeP       trailer = c_out_info_get_trailer1 (info);
    COutClosureT closure;

    closure.info           = info;
    closure.table          = table;
    closure.predicate_id   = grammar_get_predicate_id (grammar);
    closure.predicate_type = grammar_get_predicate_type (grammar);
    closure.error_terminal = grammar_max_terminal (grammar);
    c_output_identification (info);
    write_cstring (ostream, "/* BEGINNING OF HEADER */");
    write_newline (ostream);
    write_newline (ostream);
    if (c_out_info_get_split (info) != 0) {
	write_cstring (ostream, "#define __SID_SPLIT");
	write_newline (ostream);
    }
    c_output_location (info, c_code_file (header), c_code_line (header));
    c_output_c_code (info, header);
    c_output_location (info, ostream_name (ostream),
		       ostream_line (ostream) + 1);
    write_newline (ostream);
    if (c_out_info_get_split (info) == 0) {
	write_cstring (ostream, "/* BEGINNING OF FUNCTION DECLARATIONS */");
	write_newline (ostream);
	write_newline (ostream);
	table_iter (table, c_output_declaration, (GenericP) info);
	write_newline (ostream);
    }
    c_output_static_vars (info, grammar, TRUE);
    write_cstring (ostream, "/* BEGINNING OF FUNCTION DEFINITIONS */");
    write_newline (ostream);
    write_newline (ostream);
    table_iter (table, c_output_definition, (GenericP) &closure);
    write_cstring (ostream, "/* BEGINNING OF TRAILER */");
    write_newline (ostream);
    write_newline (ostream);
    c_output_location (info, c_code_file (trailer), c_code_line (trailer));
    c_output_c_code (info, trailer);
    c_output_location (info, ostream_name (ostream),
		       ostream_line (ostream) + 1);
    write_newline (ostream);
    write_cstring (ostream, "/* END OF FILE */");
    write_newline (ostream);
}

void
c_output_header PROTO_N ((info, grammar))
		PROTO_T (COutputInfoP info X
			 GrammarP     grammar)
{
    TableP   table   = grammar_table (grammar);
    OStreamP ostream = c_out_info_ostream (info);
    CCodeP   header  = c_out_info_get_header2 (info);
    CCodeP   trailer = c_out_info_get_trailer2 (info);

    c_output_identification (info);
    write_cstring (ostream, "/* BEGINNING OF HEADER */");
    write_newline (ostream);
    write_newline (ostream);
    c_output_location (info, c_code_file (header), c_code_line (header));
    c_output_c_code (info, header);
    c_output_location (info, ostream_name (ostream),
		       ostream_line (ostream) + 1);
    write_newline (ostream);
    write_cstring (ostream, "/* BEGINNING OF FUNCTION DECLARATIONS */");
    write_newline (ostream);
    write_newline (ostream);
    if (c_out_info_get_split (info) != 0) {
	write_cstring (ostream, "#ifndef __SID_SPLIT");
	write_newline (ostream);
	table_iter (table, c_output_ext_declaration, (GenericP) info);
	write_cstring (ostream, "#else /* __SID_SPLIT */");
	write_newline (ostream);
	table_iter (table, c_output_declaration, (GenericP) info);
	c_output_static_vars (info, grammar, FALSE);
	write_cstring (ostream, "#endif /* __SID_SPLIT */");
	write_newline (ostream);
    } else {
	table_iter (table, c_output_ext_declaration, (GenericP) info);
    }
    write_newline (ostream);
    write_cstring (ostream, "/* BEGINNING OF TERMINAL DEFINITIONS */");
    write_newline (ostream);
    write_newline (ostream);
    table_iter (table, c_output_terminal, (GenericP) info);
    write_newline (ostream);
    write_cstring (ostream, "/* BEGINNING OF TRAILER */");
    write_newline (ostream);
    write_newline (ostream);
    c_output_location (info, c_code_file (trailer), c_code_line (trailer));
    c_output_c_code (info, trailer);
    c_output_location (info, ostream_name (ostream),
		       ostream_line (ostream) + 1);
    write_newline (ostream);
    write_cstring (ostream, "/* END OF FILE */");
    write_newline (ostream);
}

void
c_output_location PROTO_N ((info, file, line))
		  PROTO_T (COutputInfoP info X
			   CStringP     file X
			   unsigned     line)
{
    if (c_out_info_get_lines (info)) {
	OStreamP ostream = c_out_info_ostream (info);

	write_cstring (ostream, "#line ");
	write_unsigned (ostream, line);
	write_cstring (ostream, " \"");
	write_cstring (ostream, file);
	write_char (ostream, '"');
	write_newline (ostream);
    }
}

void
c_output_key_message PROTO_N ((info, prefix, key, suffix, indent))
		     PROTO_T (COutputInfoP info X
			      CStringP     prefix X
			      KeyP         key X
			      CStringP     suffix X
			      unsigned     indent)
{
    if (c_out_info_get_lines (info)) {
	OStreamP ostream = c_out_info_ostream (info);

	c_output_indent (info, indent);
	write_cstring (ostream, prefix);
	write_key (ostream, key);
	write_cstring (ostream, suffix);
	write_newline (ostream);
    }
}

unsigned
c_out_next_label PROTO_Z ()
{
    return (out_current_label ++);
}

void
c_output_open PROTO_N ((info, indent))
	      PROTO_T (COutputInfoP info X
		       unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);

    c_output_indent (info, indent);
    write_char (ostream, '{');
    write_newline (ostream);
}

void
c_output_close PROTO_N ((info, indent))
	       PROTO_T (COutputInfoP info X
			unsigned     indent)
{
    OStreamP ostream = c_out_info_ostream (info);

    c_output_indent (info, indent);
    write_char (ostream, '}');
    write_newline (ostream);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../output" "../generated")
 * end:
**/
