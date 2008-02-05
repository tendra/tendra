/*
 * Automatically generated from the files:
 *	parser.sid
 * and
 *	parser.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */


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

#include <limits.h>
#include <assert.h>

#include "parser.h"
#include "adt/action.h"
#include "adt/basic.h"
#include "eds/bitvec.h"
#include "eds/dalloc.h"
#include "eds/dstring.h"
#include "gen-errors.h"
#include "grammar.h"
#include "lexer.h"
#include "adt/non-local.h"
#include "adt/rule.h"
#include "adt/scope.h"
#include "adt/table.h"
#include "adt/types.h"

#define CURRENT_TERMINAL lexer_get_terminal (sid_current_stream)
#define ADVANCE_LEXER lexer_next_token (sid_current_stream)
#define SAVE_LEXER(x) (lexer_save_terminal (sid_current_stream, (LexerTokenT) (x)))
#define RESTORE_LEXER (lexer_restore_terminal (sid_current_stream))
#define ALT_LIMIT (UINT_MAX - 1)

/* typedefs for the maps section */
typedef AltT * AltP;
typedef EntryT * EntryP;
typedef ItemT * ItemP;
typedef RuleT *RuleP;

LexerStreamT *		sid_current_stream;

static ScopeStackT	sid_scope_stack;
static ScopeStackT	sid_global_scope;
static ScopeStackT *sid_current_scope;
static EntryT *		sid_current_entry;
static RuleT *		sid_enclosing_rule;
static union {
    BasicT *	basic;
    ActionT *	action;
    RuleT *		rule;
} sid_current;
static BoolT		sid_redefining_entry;
static NStringT		sid_maximum_scope;
static TypeTupleT	sid_saved_type;
static TypeTupleT	sid_current_type;
static EntryT *		sid_saved_pred_id;
static EntryT *		sid_current_pred_id;
static EntryT *		sid_unique_pred_id = NULL;
static EntryT *		sid_predicate_type = NULL;
static AltT *		sid_current_alt;
static ItemT *		sid_current_item;
static unsigned		sid_alternative;
static BoolT            sid_internal_rule;
static EntryT *		sid_external_rule;
static unsigned		sid_num_alternatives = 0;
static NonLocalEntryT *	sid_non_local;
static BoolT		sid_propagating_error = FALSE;
static BoolT		sid_finished_terminals = FALSE;

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZR235(GrammarP);
static void ZR230(GrammarP);
static void ZR137(GrammarP);
static void ZR232(GrammarP);
static void ZR171(GrammarP);
static void ZR239(GrammarP);
static void ZR146(GrammarP);
static void ZR163(GrammarP);
static void ZR147(GrammarP);
static void ZR175(GrammarP);
static void ZR221(GrammarP);
static void ZR281(GrammarP, NStringT *);
static void ZR149(GrammarP);
static void ZR283(GrammarP);
static void ZR183(GrammarP);
static void ZR192(GrammarP);
static void ZR284(GrammarP, NStringT *);
static void ZR285(GrammarP, NStringT *);
static void ZR165(GrammarP);
static void ZR161(GrammarP);
extern void sid_parse_grammar(GrammarP);
static void ZR140(GrammarP);
static void ZR142(GrammarP);
static void ZR177(GrammarP);
static void ZR199(GrammarP);
static void ZR219(GrammarP);
static void ZR153(GrammarP);
static void ZR196(GrammarP);
static void ZR185(GrammarP);
static void ZR253(GrammarP);
static void ZR186(GrammarP);
static void ZR128(GrammarP);
static void ZR259(GrammarP);
static void ZR126(GrammarP);
static void ZR208(GrammarP);
static void ZR217(GrammarP);
static void ZR155(GrammarP);
static void ZR187(GrammarP);
static void ZR228(GrammarP);
static void ZR261(GrammarP);
static void ZR168(GrammarP);
static void ZR246(GrammarP);
static void ZR248(GrammarP);
static void ZR249(GrammarP);
static void ZR180(GrammarP);
static void ZR251(GrammarP);
static void ZR252(GrammarP);

/* BEGINNING OF STATIC VARIABLES */

static BoolT ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZR235(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
  ZL2_235:;
    {
	ZR232 (sid_current_grammar);
	{
	    switch (CURRENT_TERMINAL) {
	      case 15:
		{
		    ADVANCE_LEXER;
		    goto ZL2_235;
		}
		/*UNREACHED*/
	      case 26:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR230(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	{

    if (sid_current_entry) {
	sid_current_alt = alt_create ();
    }
	}
	ZR228 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ((sid_current_entry) && (sid_current_alt)) {
	if (types_check_names (rule_result (sid_current.rule),
			       alt_names (sid_current_alt))) {
	    TypeTupleT used;

	    types_copy (&used, rule_result (sid_current.rule));
	    item_compute_minimal_dataflow (alt_item_head (sid_current_alt),
					   &used);
	    types_destroy (&used);
	    rule_set_handler (sid_current.rule, sid_current_alt);
	} else {
	    (void) alt_deallocate (sid_current_alt);
	    E_handler_result_mismatch (entry_key (sid_external_rule));
	}
    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR137(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
  ZL2_137:;
    {
	ZR128 (sid_current_grammar);
	{
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		{

    (ZI0) = ((CURRENT_TERMINAL == LEXER_TOK_CLOSE_TUPLE) ||
		  (CURRENT_TERMINAL == LEXER_TOK_EOF) ||
		  (sid_propagating_error));
		}
		if (!ZI0)
		    goto ZL5;
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL5:;
	    switch (CURRENT_TERMINAL) {
	      case 23:
		{
		    ADVANCE_LEXER;
		    goto ZL2_137;
		}
		/*UNREACHED*/
	      default:
		goto ZL4;
	    }
	    /*UNREACHED*/
	  ZL4:;
	    {
		{

    if (!sid_propagating_error) {
	E_expected_separator ();
    }
		}
		goto ZL2_137;
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR232(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 17:
	{
	    {

    if ((++ sid_num_alternatives) == ALT_LIMIT) {
	E_too_many_alternatives ();
	UNREACHED;
    }
    if (!sid_internal_rule) {
	sid_alternative ++;
    }
    if (sid_current_entry) {
	if (rule_has_empty_alt (sid_current.rule)) {
	    E_multiple_empty_alts (entry_key (sid_external_rule));
	} else if (!types_equal_zero_tuple (rule_result (sid_current.rule))) {
	    E_alt_result_mismatch (entry_key (sid_external_rule),
				   sid_alternative);
	} else {
	    rule_add_empty_alt (sid_current.rule);
	}
    }
	    }
	    ADVANCE_LEXER;
	    ZR252 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 4: case 6: case 10: case 13: case 18:
      case 19: case 24:
	{
	    {

    if ((++ sid_num_alternatives) == ALT_LIMIT) {
	E_too_many_alternatives ();
	UNREACHED;
    }
    if (!sid_internal_rule) {
	sid_alternative ++;
    }
    if (sid_current_entry) {
	sid_current_alt = alt_create ();
    }
	    }
	    ZR228 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ((sid_current_entry) && (sid_current_alt)) {
	if (types_check_names (rule_result (sid_current.rule),
			       alt_names (sid_current_alt))) {
	    TypeTupleT used;

	    types_copy (&used, rule_result (sid_current.rule));
	    item_compute_minimal_dataflow (alt_item_head (sid_current_alt),
					   &used);
	    types_destroy (&used);
	    rule_add_alt (sid_current.rule, sid_current_alt);
	} else {
	    (void) alt_deallocate (sid_current_alt);
	    E_alt_result_mismatch (entry_key (sid_external_rule),
				   sid_alternative);
	}
    }
	    }
	}
	break;
      case 26:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_alternative ();
    }
	}
	{

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_ALT_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_SCOPE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
	}
	{

    sid_propagating_error = FALSE;
	}
    }
}

static void
ZR171(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 4: case 18: case 19: case 24:
	{
	    ZR168 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 26:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR239(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	NStringT ZI151;

	switch (CURRENT_TERMINAL) {
	  case 4:
	    {

    nstring_assign (&ZI151, lexer_string_value (sid_current_stream));
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 5:
		{
		    ADVANCE_LEXER;
		    ZR281 (sid_current_grammar, &ZI151);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		}
		break;
	      case 9: case 12: case 21:
		{
		    {

    types_init (&sid_saved_type);
    types_init (&sid_current_type);
    sid_saved_pred_id   = NULL;
    sid_current_pred_id = NULL;
		    }
		    {

    sid_current_entry = scope_stack_add_rule (sid_current_scope,
					      grammar_table(sid_current_grammar), &(ZI151),
					      sid_enclosing_rule,
					      &sid_redefining_entry);
    if (sid_current_entry) {
	sid_current.rule = entry_get_rule (sid_current_entry);
    } else {
	E_duplicate_rule ((&ZI151));
	nstring_destroy (&(ZI151));
    }
		    }
		    ZR248 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		}
		break;
	      default:
		goto ZL3;
	    }
	    goto ZL2;
	  ZL3:;
	    {
		{

    if (!sid_propagating_error) {
	E_expected_other_defn ();
    }
		}
		{

    nstring_destroy (&(ZI151));
		}
		{

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_SCOPE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
		}
	    }
	  ZL2:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR146(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 8:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_arrow ();
    }
	}
    }
}

static void
ZR163(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	{

    types_init (&sid_current_type);
    sid_current_pred_id = NULL;
	}
	ZR185 (sid_current_grammar);
	ZR171 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    sid_propagating_error = FALSE;
	}
	ZR186 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR147(GrammarP sid_current_grammar)
{
  ZL2_147:;
    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    ZR149 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_147;
	    }
	}
	/*UNREACHED*/
      case 26:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR175(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	{

    types_init (&sid_current_type);
    sid_current_pred_id = NULL;
	}
	ZR185 (sid_current_grammar);
	ZR183 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    sid_propagating_error = FALSE;
	}
	ZR186 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR221(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 13:
	{
	    EntryP ZI194;
	    RuleP ZI67;
	    AltP ZI223;
	    BoolT ZI224;
	    ItemP ZI225;

	    ADVANCE_LEXER;
	    {

    (ZI194)      = sid_current_entry;
    (ZI67)       = sid_current.rule;
    (ZI223)        = sid_current_alt;
    (ZI224)   = sid_internal_rule;
    (ZI225)             = NULL;
    sid_internal_rule = TRUE;
    if ((sid_current_entry) && (sid_current_alt)) {
	sid_current_entry = table_add_generated_rule (grammar_table(sid_current_grammar),
						      FALSE);
	sid_current.rule  = entry_get_rule (sid_current_entry);
	(ZI225)             = item_create (sid_current_entry);
	rule_defined (sid_current.rule);
	item_inlinable ((ZI225));
	types_copy (item_param ((ZI225)), rule_param ((ZI67)));
	types_append_copy (item_param ((ZI225)), alt_names ((ZI223)));
	types_copy (rule_param (sid_current.rule), item_param ((ZI225)));
	types_make_references (rule_param (sid_current.rule),
			       item_param ((ZI225)));
	alt_add_item ((ZI223), (ZI225));
    } else {
	sid_current_entry = NULL;
    }
	    }
	    ZR219 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if (((ZI194)) && ((ZI223))) {
	rule_compute_result_intersect (sid_current.rule);
	types_copy (item_result ((ZI225)), rule_result (sid_current.rule));
	types_add_new_names (alt_names ((ZI223)), item_result ((ZI225)),
			     sid_unique_pred_id);
    }
    sid_internal_rule = (ZI224);
    sid_current_alt   = (ZI223);
    sid_current.rule  = (ZI67);
    sid_current_entry = (ZI194);
	    }
	    ZR251 (sid_current_grammar);
	    ZR252 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 4: case 6: case 10: case 18: case 19:
      case 24:
	{
	    ZR208 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    sid_propagating_error = FALSE;
	    }
	}
	break;
      case 26:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR281(GrammarP sid_current_grammar, NStringT *ZI151)
{
    switch (CURRENT_TERMINAL) {
      case 6:
	{
	    ZR142 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    types_assign (&sid_saved_type, &sid_current_type);
    sid_saved_pred_id = sid_current_pred_id;
	    }
	    ZR146 (sid_current_grammar);
	    ZR142 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    sid_current_entry = scope_stack_add_rule (sid_current_scope,
					      grammar_table(sid_current_grammar), &(*ZI151),
					      sid_enclosing_rule,
					      &sid_redefining_entry);
    if (sid_current_entry) {
	sid_current.rule = entry_get_rule (sid_current_entry);
    } else {
	E_duplicate_rule ((ZI151));
	nstring_destroy (&(*ZI151));
    }
	    }
	    ZR248 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 4:
	{
	    {
		{
		    NStringT ZI133;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

    nstring_assign (&ZI133, lexer_string_value (sid_current_stream));
			}
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    {

    sid_non_local = NULL;
    if ((sid_enclosing_rule == NULL) ||
	(sid_current_scope == &sid_global_scope)) {
	E_global_scope_non_local ((ZI151));
	nstring_destroy (&(*ZI151));
    } else {
	EntryT * type = table_get_type (grammar_table(sid_current_grammar), (&ZI133));

	if (type == NULL) {
	    E_unknown_type ((&ZI133));
	    nstring_destroy (&(*ZI151));
	} else {
	    EntryT * name = scope_stack_add_non_local (sid_current_scope,
						     grammar_table(sid_current_grammar),
						     &(*ZI151), type,
						     sid_enclosing_rule);

	    if (name) {
		NonLocalListT * non_locals = rule_non_locals (sid_enclosing_rule);
		sid_non_local = non_local_list_add (non_locals, name, type);
	    } else {
		E_duplicate_non_local ((ZI151));
		nstring_destroy (&(*ZI151));
	    }
	}
    }
    nstring_destroy (&(ZI133));
		    }
		    {
			switch (CURRENT_TERMINAL) {
			  case 12:
			    {
				ADVANCE_LEXER;
				{
				    {
					switch (CURRENT_TERMINAL) {
					  case 10:
					    break;
					  default:
					    goto ZL7;
					}
					ADVANCE_LEXER;
				    }
				    goto ZL6;
				  ZL7:;
				    {
					{

    if (!sid_propagating_error) {
	E_expected_begin_action ();
    }
					}
				    }
				  ZL6:;
				}
				{
				    {
					NStringT ZI49;

					switch (CURRENT_TERMINAL) {
					  case 4:
					    {

    nstring_assign (&ZI49, lexer_string_value (sid_current_stream));
					    }
					    break;
					  default:
					    goto ZL9;
					}
					ADVANCE_LEXER;
					{

    EntryT * entry = scope_stack_get_action (&sid_scope_stack, grammar_table(sid_current_grammar),
					   (&ZI49));

    if (entry == NULL) {
	E_unknown_action ((&ZI49));
    } else if (sid_non_local) {
	EntryT *     type   = non_local_entry_get_type (sid_non_local);
	KeyT *       name   = entry_key (non_local_entry_get_name (sid_non_local));
	ActionT *    action = entry_get_action (entry);
	TypeTupleT * param  = action_param (action);
	TypeTupleT * result = action_result (action);
	TypeTupleT tuple;
	TypeTupleT ref_tuple;

	types_init (&tuple);
	types_init (&ref_tuple);
	types_add_type_entry (&tuple, type, FALSE);
	types_add_type_entry (&ref_tuple, type, TRUE);
	if ((!types_equal (param, &tuple)) &&
	    (!types_equal (param, &ref_tuple)) &&
	    (!types_equal_zero_tuple (param))) {
	    E_initialiser_param_mismatch (name, &tuple, &ref_tuple, param);
	}
	if (!types_equal (result, &tuple)) {
	    E_initialiser_result_mismatch (name, &tuple, result);
	}
	types_destroy (&ref_tuple);
	types_destroy (&tuple);
	non_local_entry_set_initialiser (sid_non_local, entry);
    }
    nstring_destroy (&(ZI49));
					}
					ZR246 (sid_current_grammar);
					ZR252 (sid_current_grammar);
					if ((CURRENT_TERMINAL) == 26) {
					    RESTORE_LEXER;
					    goto ZL9;
					}
				    }
				    goto ZL8;
				  ZL9:;
				    {
					{

    if (!sid_propagating_error) {
	E_expected_identifier ();
    }
					}
				    }
				  ZL8:;
				}
			    }
			    break;
			  case 9:
			    {
				ADVANCE_LEXER;
			    }
			    break;
			  default:
			    goto ZL5;
			}
			goto ZL4;
		      ZL5:;
			{
			    {

    if (!sid_propagating_error) {
	E_expected_terminator_or_define ();
    }
			    }
			}
		      ZL4:;
		    }
		}
		goto ZL2;
	      ZL3:;
		{
		    {

    if (!sid_propagating_error) {
	E_expected_identifier ();
    }
		    }
		    {

    nstring_destroy (&(*ZI151));
		    }
		    {

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_SCOPE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
		    }
		}
	      ZL2:;
	    }
	}
	break;
      case 26:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR149(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	NStringT ZI151;

	switch (CURRENT_TERMINAL) {
	  case 4:
	    {

    nstring_assign (&ZI151, lexer_string_value (sid_current_stream));
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    if (table_add_type (grammar_table(sid_current_grammar), &(ZI151)) == NULL) {
	E_duplicate_type ((&ZI151));
	nstring_destroy (&(ZI151));
    }
	}
	ZR252 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR283(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 18:
	{
	    {

    if (sid_current_pred_id) {
	E_multi_predicate_return ();
    } else if (sid_unique_pred_id == NULL) {
	sid_unique_pred_id = grammar_get_predicate_id (sid_current_grammar);
    }
    sid_current_pred_id = sid_unique_pred_id;
    types_add_name_entry (&sid_current_type, sid_current_pred_id);
	    }
	    ADVANCE_LEXER;
	    {

    types_assign (&sid_saved_type, &sid_current_type);
    sid_saved_pred_id = sid_current_pred_id;
	    }
	    ZR249 (sid_current_grammar);
	    ZR199 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 19:
	{
	    {

    EntryT * entry = table_add_generated_name (grammar_table(sid_current_grammar));

    types_add_name_entry (&sid_current_type, entry);
	    }
	    ADVANCE_LEXER;
	    {

    types_assign (&sid_saved_type, &sid_current_type);
    sid_saved_pred_id = sid_current_pred_id;
	    }
	    ZR249 (sid_current_grammar);
	    ZR199 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 10:
	{
	    {

    types_assign (&sid_saved_type, &sid_current_type);
    sid_saved_pred_id = sid_current_pred_id;
	    }
	    ADVANCE_LEXER;
	    ZR217 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 26:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR183(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 4: case 24:
	{
	    ZR180 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 26:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR192(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 21:
	{
	    EntryP ZI194;
	    RuleP ZI67;

	    ADVANCE_LEXER;
	    {

    (ZI194)       = sid_current_entry;
    (ZI67)        = sid_enclosing_rule;

    sid_enclosing_rule = sid_current.rule;
	    }
	    ZR161 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    sid_current_entry  = (ZI194);
    sid_current.rule   = sid_enclosing_rule;
    sid_enclosing_rule = (ZI67);
    sid_alternative    = 0;
    sid_internal_rule  = FALSE;
    sid_external_rule  = sid_current_entry;
    nstring_init (&sid_maximum_scope);
	    }
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 22:
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		}
		goto ZL2;
	      ZL3:;
		{
		    {

    if (!sid_propagating_error) {
	E_expected_end_scope ();
    }
		    }
		}
	      ZL2:;
	    }
	}
	break;
      case 26:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR284(GrammarP sid_current_grammar, NStringT *ZI151)
{
    switch (CURRENT_TERMINAL) {
      case 12:
	{
	    {

    NStringT scope;
    EntryT *   non_local_entry = scope_stack_get_non_local (&sid_scope_stack,
							  grammar_table(sid_current_grammar),
							  (ZI151), &scope);
    EntryT *   name_entry      = table_get_entry (grammar_table(sid_current_grammar), (ZI151));

    if (name_entry) {
	if ((sid_current_entry) && (sid_current_alt)) {
	    if ((!types_contains (alt_names (sid_current_alt), name_entry)) &&
		(!types_contains (rule_param (sid_current.rule),
				  name_entry))) {
		name_entry = NULL;
	    }
	} else {
	    name_entry = NULL;
	}
    }
    if (name_entry) {
	types_add_name_and_type (&sid_current_type, name_entry, NULL,
				 FALSE);
	if (non_local_entry) {
	    nstring_destroy (&scope);
	}
	nstring_destroy (&(*ZI151));
    } else if (non_local_entry) {
	types_add_name_and_type (&sid_current_type, non_local_entry,
				 NULL, FALSE);
	if (nstring_length (&scope) > nstring_length (&sid_maximum_scope)) {
	    nstring_destroy (&sid_maximum_scope);
	    nstring_assign (&sid_maximum_scope, &scope);
	} else {
	    nstring_destroy (&scope);
	}
	nstring_destroy (&(*ZI151));
    } else {
	types_add_name (&sid_current_type, grammar_table(sid_current_grammar), &(*ZI151), FALSE);
    }
	    }
	    {

    types_assign (&sid_saved_type, &sid_current_type);
    sid_saved_pred_id = sid_current_pred_id;
	    }
	    ADVANCE_LEXER;
	    ZR199 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 6: case 9:
	{
	    {

    types_assign (&sid_saved_type, &sid_current_type);
    sid_saved_pred_id = sid_current_pred_id;
	    }
	    ZR285 (sid_current_grammar, ZI151);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 26:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR285(GrammarP sid_current_grammar, NStringT *ZI151)
{
    switch (CURRENT_TERMINAL) {
      case 6:
	{
	    ZR175 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    TypeTupleT * param  = NULL;
    TypeTupleT * result = NULL;
    EntryT *     entry  = NULL;
    RuleT *      rule;
    BasicT *     basic;

    if ((sid_current_entry) && (sid_current_alt)) {
	entry = scope_stack_get_rule (&sid_scope_stack, grammar_table(sid_current_grammar),
				      (ZI151));
	if (entry) {
	    sid_current_item = item_create (entry);
	    rule             = entry_get_rule (entry);
	    param            = rule_param (rule);
	    result           = rule_result (rule);
	} else {
	    entry = table_get_basic (grammar_table(sid_current_grammar), (ZI151));
	    if (entry) {
		sid_current_item = item_create (entry);
		basic            = entry_get_basic (entry);
		param            = NULL;
		result           = basic_result (basic);
		if (basic_get_ignored (basic)) {
		    E_ignored_basic_call ((ZI151));
		}
	    } else {
		E_unknown_rule_or_basic ((ZI151));
		sid_current_item = NULL;
	    }
	}
    } else {
	sid_current_item = NULL;
    }
    nstring_destroy (&(*ZI151));
    if (sid_current_item) {
	BoolT errored = FALSE;
	KeyT *  key     = entry_key (entry);

	if (types_resolve (&sid_current_type, rule_param (sid_current.rule),
			   alt_names (sid_current_alt), E_undefined_name,
			   entry_key (sid_external_rule), sid_alternative)) {
	    if (param) {
		if (types_equal (&sid_current_type, param)) {
		    item_add_param (sid_current_item, &sid_current_type);
		} else {
		    E_rule_param_call_mismatch (key, param, &sid_current_type);
		    types_destroy (&sid_current_type);
		    errored = TRUE;
		}
	    } else {
		if (!types_equal_zero_tuple (&sid_current_type)) {
		    E_basic_param_call_mismatch (key, &sid_current_type);
		    types_destroy (&sid_current_type);
		    errored = TRUE;
		}
	    }
	} else {
	    types_destroy (&sid_current_type);
	    errored = TRUE;
	}
	if (types_disjoint_names (&sid_saved_type)) {
	    if (types_check_undefined (&sid_saved_type,
				       rule_param (sid_current.rule),
				       alt_names (sid_current_alt),
				       E_redefined_name,
				       entry_key (sid_external_rule),
				       sid_alternative)) {
		if (types_fillin_types (&sid_saved_type, result)) {
		    types_add_new_names (alt_names (sid_current_alt),
					 &sid_saved_type, sid_unique_pred_id);
		    if (sid_saved_pred_id) {
			E_predicate ();
		    }
		    item_add_result (sid_current_item, &sid_saved_type);
		} else {
		    if (param) {
			E_rule_result_call_mismatch (key, result,
						     &sid_saved_type);
		    } else {
			E_basic_result_call_mismatch (key, result,
						      &sid_saved_type);
		    }
		    types_destroy (&sid_saved_type);
		    errored = TRUE;
		}
	    } else {
		types_destroy (&sid_saved_type);
		errored = TRUE;
	    }
	} else {
	    if (param) {
		E_rule_result_call_clash (key, &sid_saved_type);
	    } else {
		E_basic_result_call_clash (key, &sid_saved_type);
	    }
	    types_destroy (&sid_saved_type);
	    errored = TRUE;
	}
	if (errored) {
	    (void) item_deallocate (sid_current_item);
	    sid_current_item = NULL;
	    (void) alt_deallocate (sid_current_alt);
	    sid_current_alt  = NULL;
	} else {
	    alt_add_item (sid_current_alt, sid_current_item);
	}
    } else {
	if (sid_current_alt) {
	    (void) alt_deallocate (sid_current_alt);
	    sid_current_alt = NULL;
	}
	types_destroy (&sid_saved_type);
	types_destroy (&sid_current_type);
    }
	    }
	    ZR252 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 9:
	{
	    {

    types_init (&sid_current_type);
    sid_current_pred_id = NULL;
	    }
	    {

    TypeTupleT * param  = NULL;
    TypeTupleT * result = NULL;
    EntryT *     entry  = NULL;
    RuleT *      rule;
    BasicT *     basic;

    if ((sid_current_entry) && (sid_current_alt)) {
	entry = scope_stack_get_rule (&sid_scope_stack, grammar_table(sid_current_grammar),
				      (ZI151));
	if (entry) {
	    sid_current_item = item_create (entry);
	    rule             = entry_get_rule (entry);
	    param            = rule_param (rule);
	    result           = rule_result (rule);
	} else {
	    entry = table_get_basic (grammar_table(sid_current_grammar), (ZI151));
	    if (entry) {
		sid_current_item = item_create (entry);
		basic            = entry_get_basic (entry);
		param            = NULL;
		result           = basic_result (basic);
		if (basic_get_ignored (basic)) {
		    E_ignored_basic_call ((ZI151));
		}
	    } else {
		E_unknown_rule_or_basic ((ZI151));
		sid_current_item = NULL;
	    }
	}
    } else {
	sid_current_item = NULL;
    }
    nstring_destroy (&(*ZI151));
    if (sid_current_item) {
	BoolT errored = FALSE;
	KeyT *  key     = entry_key (entry);

	if (types_resolve (&sid_current_type, rule_param (sid_current.rule),
			   alt_names (sid_current_alt), E_undefined_name,
			   entry_key (sid_external_rule), sid_alternative)) {
	    if (param) {
		if (types_equal (&sid_current_type, param)) {
		    item_add_param (sid_current_item, &sid_current_type);
		} else {
		    E_rule_param_call_mismatch (key, param, &sid_current_type);
		    types_destroy (&sid_current_type);
		    errored = TRUE;
		}
	    } else {
		if (!types_equal_zero_tuple (&sid_current_type)) {
		    E_basic_param_call_mismatch (key, &sid_current_type);
		    types_destroy (&sid_current_type);
		    errored = TRUE;
		}
	    }
	} else {
	    types_destroy (&sid_current_type);
	    errored = TRUE;
	}
	if (types_disjoint_names (&sid_saved_type)) {
	    if (types_check_undefined (&sid_saved_type,
				       rule_param (sid_current.rule),
				       alt_names (sid_current_alt),
				       E_redefined_name,
				       entry_key (sid_external_rule),
				       sid_alternative)) {
		if (types_fillin_types (&sid_saved_type, result)) {
		    types_add_new_names (alt_names (sid_current_alt),
					 &sid_saved_type, sid_unique_pred_id);
		    if (sid_saved_pred_id) {
			E_predicate ();
		    }
		    item_add_result (sid_current_item, &sid_saved_type);
		} else {
		    if (param) {
			E_rule_result_call_mismatch (key, result,
						     &sid_saved_type);
		    } else {
			E_basic_result_call_mismatch (key, result,
						      &sid_saved_type);
		    }
		    types_destroy (&sid_saved_type);
		    errored = TRUE;
		}
	    } else {
		types_destroy (&sid_saved_type);
		errored = TRUE;
	    }
	} else {
	    if (param) {
		E_rule_result_call_clash (key, &sid_saved_type);
	    } else {
		E_basic_result_call_clash (key, &sid_saved_type);
	    }
	    types_destroy (&sid_saved_type);
	    errored = TRUE;
	}
	if (errored) {
	    (void) item_deallocate (sid_current_item);
	    sid_current_item = NULL;
	    (void) alt_deallocate (sid_current_alt);
	    sid_current_alt  = NULL;
	} else {
	    alt_add_item (sid_current_alt, sid_current_item);
	}
    } else {
	if (sid_current_alt) {
	    (void) alt_deallocate (sid_current_alt);
	    sid_current_alt = NULL;
	}
	types_destroy (&sid_saved_type);
	types_destroy (&sid_current_type);
    }
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 26:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR165(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    NStringT ZI151;

	    {

    nstring_assign (&ZI151, lexer_string_value (sid_current_stream));
	    }
	    ADVANCE_LEXER;
	    {

    NStringT scope;
    EntryT *   non_local_entry = scope_stack_get_non_local (&sid_scope_stack,
							  grammar_table(sid_current_grammar),
							  (&ZI151), &scope);
    EntryT *   name_entry      = table_get_entry (grammar_table(sid_current_grammar), (&ZI151));

    if (name_entry) {
	if ((sid_current_entry) && (sid_current_alt)) {
	    if ((!types_contains (alt_names (sid_current_alt), name_entry)) &&
		(!types_contains (rule_param (sid_current.rule),
				  name_entry))) {
		name_entry = NULL;
	    }
	} else {
	    name_entry = NULL;
	}
    }
    if (name_entry) {
	types_add_name_and_type (&sid_current_type, name_entry, NULL,
				 FALSE);
	if (non_local_entry) {
	    nstring_destroy (&scope);
	}
	nstring_destroy (&(ZI151));
    } else if (non_local_entry) {
	types_add_name_and_type (&sid_current_type, non_local_entry,
				 NULL, FALSE);
	if (nstring_length (&scope) > nstring_length (&sid_maximum_scope)) {
	    nstring_destroy (&sid_maximum_scope);
	    nstring_assign (&sid_maximum_scope, &scope);
	} else {
	    nstring_destroy (&scope);
	}
	nstring_destroy (&(ZI151));
    } else {
	types_add_name (&sid_current_type, grammar_table(sid_current_grammar), &(ZI151), FALSE);
    }
	    }
	}
	break;
      case 19:
	{
	    ADVANCE_LEXER;
	    {

    EntryT * entry = table_add_generated_name (grammar_table(sid_current_grammar));

    types_add_name_entry (&sid_current_type, entry);
	    }
	}
	break;
      case 18:
	{
	    ADVANCE_LEXER;
	    {

    if (sid_current_pred_id) {
	E_multi_predicate_return ();
    } else if (sid_unique_pred_id == NULL) {
	sid_unique_pred_id = grammar_get_predicate_id (sid_current_grammar);
    }
    sid_current_pred_id = sid_unique_pred_id;
    types_add_name_entry (&sid_current_type, sid_current_pred_id);
	    }
	}
	break;
      case 24:
	{
	    ADVANCE_LEXER;
	    {
		{
		    NStringT ZI151;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

    nstring_assign (&ZI151, lexer_string_value (sid_current_stream));
			}
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    {

    NStringT scope;
    EntryT *   non_local_entry = scope_stack_get_non_local (&sid_scope_stack,
							  grammar_table(sid_current_grammar),
							  (&ZI151), &scope);
    EntryT *   name_entry      = table_get_entry (grammar_table(sid_current_grammar), (&ZI151));

    if (name_entry) {
	if ((sid_current_entry) && (sid_current_alt)) {
	    if ((!types_contains (alt_names (sid_current_alt), name_entry)) &&
		(!types_contains (rule_param (sid_current.rule),
				  name_entry))) {
		name_entry = NULL;
	    }
	} else {
	    name_entry = NULL;
	}
    }
    if (name_entry) {
	types_add_name_and_type_var (&sid_current_type, name_entry,
				     NULL);
	if (non_local_entry) {
	    nstring_destroy (&scope);
	}
	nstring_destroy (&(ZI151));
    } else if (non_local_entry) {
	types_add_name_and_type_var (&sid_current_type, non_local_entry,
				     NULL);
	if (nstring_length (&scope) > nstring_length (&sid_maximum_scope)) {
	    nstring_destroy (&sid_maximum_scope);
	    nstring_assign (&sid_maximum_scope, &scope);
	} else {
	    nstring_destroy (&scope);
	}
	nstring_destroy (&(ZI151));
    } else {
	E_undefined_assignment ((&ZI151));
	types_add_name (&sid_current_type, grammar_table(sid_current_grammar), &(ZI151), FALSE);
    }
		    }
		}
		goto ZL2;
	      ZL3:;
		{
		    {

    if (!sid_propagating_error) {
	E_expected_identifier ();
    }
		    }
		}
	      ZL2:;
	    }
	}
	break;
      case 26:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_lhs_name ();
    }
	}
	{

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
	}
    }
}

static void
ZR161(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
  ZL2_161:;
    {
	ZR253 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    sid_propagating_error = FALSE;
	}
	{
	    {
		{

    (ZI0) = ((CURRENT_TERMINAL == LEXER_TOK_EOF) ||
		  (CURRENT_TERMINAL == LEXER_TOK_END_SCOPE) ||
		  (CURRENT_TERMINAL == LEXER_TOK_BLT_ENTRY));
		}
		if (!ZI0)
		    goto ZL4;
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL4:;
	    switch (CURRENT_TERMINAL) {
	      case 4: case 10: case 20:
		{
		    goto ZL2_161;
		}
		/*UNREACHED*/
	      default:
		goto ZL1;
	    }
	  ZL3:;
	}
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_production_defn ();
    }
	}
	{

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_SCOPE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
	}
	{

    sid_propagating_error = FALSE;
	}
	{
	    {
		{

    (ZI0) = ((CURRENT_TERMINAL == LEXER_TOK_EOF) ||
		  (CURRENT_TERMINAL == LEXER_TOK_END_SCOPE) ||
		  (CURRENT_TERMINAL == LEXER_TOK_BLT_ENTRY));
		}
		if (!ZI0)
		    goto ZL7;
	    }
	    goto ZL6;
	  ZL7:;
	    {
		goto ZL2_161;
	    }
	    /*UNREACHED*/
	  ZL6:;
	}
    }
}

void
sid_parse_grammar(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	{

scope_stack_init (&sid_scope_stack);
scope_stack_init (&sid_global_scope);
	}
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 0:
		    break;
		  default:
		    goto ZL3;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL2;
	  ZL3:;
	    {
		{

    if (!sid_propagating_error) {
	E_expected_blt_types ();
    }
		}
	    }
	  ZL2:;
	}
	ZR147 (sid_current_grammar);
	{
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 1:
		    break;
		  default:
		    goto ZL5;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL4;
	  ZL5:;
	    {
		{

    if (!sid_propagating_error) {
	E_expected_blt_terminals ();
    }
		}
	    }
	  ZL4:;
	}
	ZR153 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    unsigned max_terminal = grammar_max_terminal (sid_current_grammar);

    bitvec_set_size (max_terminal);
    sid_finished_terminals = TRUE;
	}
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 2:
		    break;
		  default:
		    goto ZL7;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL6;
	  ZL7:;
	    {
		{

    if (!sid_propagating_error) {
	E_expected_blt_productions ();
    }
		}
	    }
	  ZL6:;
	}
	ZR161 (sid_current_grammar);
	{
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 3:
		    break;
		  default:
		    goto ZL9;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL8;
	  ZL9:;
	    {
		{

    if (!sid_propagating_error) {
	E_expected_blt_entry ();
    }
		}
	    }
	  ZL8:;
	}
	ZR259 (sid_current_grammar);
	ZR252 (sid_current_grammar);
	{
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 25:
		    break;
		  default:
		    goto ZL11;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL10;
	  ZL11:;
	    {
		{

    if (!sid_propagating_error) {
	E_expected_eof ();
    }
		}
	    }
	  ZL10:;
	}
    }
    return;
  ZL1:;
    {
	{

    UNREACHED;
	}
    }
}

static void
ZR140(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 4: case 5:
	{
	    ZR137 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 26:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR142(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	{

    types_init (&sid_current_type);
    sid_current_pred_id = NULL;
	}
	ZR185 (sid_current_grammar);
	ZR140 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    sid_propagating_error = FALSE;
	}
	ZR186 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR177(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    NStringT ZI151;

	    {

    nstring_assign (&ZI151, lexer_string_value (sid_current_stream));
	    }
	    ADVANCE_LEXER;
	    {

    NStringT scope;
    EntryT *   non_local_entry = scope_stack_get_non_local (&sid_scope_stack,
							  grammar_table(sid_current_grammar),
							  (&ZI151), &scope);
    EntryT *   name_entry      = table_get_entry (grammar_table(sid_current_grammar), (&ZI151));

    if (name_entry) {
	if ((sid_current_entry) && (sid_current_alt)) {
	    if ((!types_contains (alt_names (sid_current_alt), name_entry)) &&
		(!types_contains (rule_param (sid_current.rule),
				  name_entry))) {
		name_entry = NULL;
	    }
	} else {
	    name_entry = NULL;
	}
    }
    if (name_entry) {
	types_add_name_and_type (&sid_current_type, name_entry, NULL,
				 FALSE);
	if (non_local_entry) {
	    nstring_destroy (&scope);
	}
	nstring_destroy (&(ZI151));
    } else if (non_local_entry) {
	types_add_name_and_type (&sid_current_type, non_local_entry,
				 NULL, FALSE);
	if (nstring_length (&scope) > nstring_length (&sid_maximum_scope)) {
	    nstring_destroy (&sid_maximum_scope);
	    nstring_assign (&sid_maximum_scope, &scope);
	} else {
	    nstring_destroy (&scope);
	}
	nstring_destroy (&(ZI151));
    } else {
	types_add_name (&sid_current_type, grammar_table(sid_current_grammar), &(ZI151), FALSE);
    }
	    }
	}
	break;
      case 24:
	{
	    ADVANCE_LEXER;
	    {
		{
		    NStringT ZI151;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

    nstring_assign (&ZI151, lexer_string_value (sid_current_stream));
			}
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    {

    NStringT scope;
    EntryT *   non_local_entry = scope_stack_get_non_local (&sid_scope_stack,
							  grammar_table(sid_current_grammar),
							  (&ZI151), &scope);
    EntryT *   name_entry      = table_get_entry (grammar_table(sid_current_grammar), (&ZI151));

    if (name_entry) {
	if ((sid_current_entry) && (sid_current_alt)) {
	    if ((!types_contains (alt_names (sid_current_alt), name_entry)) &&
		(!types_contains (rule_param (sid_current.rule),
				  name_entry))) {
		name_entry = NULL;
	    }
	} else {
	    name_entry = NULL;
	}
    }
    if (name_entry) {
	types_add_name_and_type (&sid_current_type, name_entry, NULL,
				 TRUE);
	if (non_local_entry) {
	    nstring_destroy (&scope);
	}
	nstring_destroy (&(ZI151));
    } else if (non_local_entry) {
	types_add_name_and_type (&sid_current_type, non_local_entry,
				 NULL, TRUE);
	if (nstring_length (&scope) > nstring_length (&sid_maximum_scope)) {
	    nstring_destroy (&sid_maximum_scope);
	    nstring_assign (&sid_maximum_scope, &scope);
	} else {
	    nstring_destroy (&scope);
	}
	nstring_destroy (&(ZI151));
    } else {
	types_add_name (&sid_current_type, grammar_table(sid_current_grammar), &(ZI151), TRUE);
    }
		    }
		}
		goto ZL2;
	      ZL3:;
		{
		    {

    if (!sid_propagating_error) {
	E_expected_identifier ();
    }
		    }
		    {

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
		    }
		}
	      ZL2:;
	    }
	}
	break;
      case 26:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_rhs_name ();
    }
	}
	{

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
	}
    }
}

static void
ZR199(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 10:
	{
	    ADVANCE_LEXER;
	    ZR217 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 4:
	{
	    NStringT ZI151;

	    {

    nstring_assign (&ZI151, lexer_string_value (sid_current_stream));
	    }
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 6:
		    {
			ZR175 (sid_current_grammar);
			if ((CURRENT_TERMINAL) == 26) {
			    RESTORE_LEXER;
			    goto ZL3;
			}
			{

    TypeTupleT * param  = NULL;
    TypeTupleT * result = NULL;
    EntryT *     entry  = NULL;
    RuleT *      rule;
    BasicT *     basic;

    if ((sid_current_entry) && (sid_current_alt)) {
	entry = scope_stack_get_rule (&sid_scope_stack, grammar_table(sid_current_grammar),
				      (&ZI151));
	if (entry) {
	    sid_current_item = item_create (entry);
	    rule             = entry_get_rule (entry);
	    param            = rule_param (rule);
	    result           = rule_result (rule);
	} else {
	    entry = table_get_basic (grammar_table(sid_current_grammar), (&ZI151));
	    if (entry) {
		sid_current_item = item_create (entry);
		basic            = entry_get_basic (entry);
		param            = NULL;
		result           = basic_result (basic);
		if (basic_get_ignored (basic)) {
		    E_ignored_basic_call ((&ZI151));
		}
	    } else {
		E_unknown_rule_or_basic ((&ZI151));
		sid_current_item = NULL;
	    }
	}
    } else {
	sid_current_item = NULL;
    }
    nstring_destroy (&(ZI151));
    if (sid_current_item) {
	BoolT errored = FALSE;
	KeyT *  key     = entry_key (entry);

	if (types_resolve (&sid_current_type, rule_param (sid_current.rule),
			   alt_names (sid_current_alt), E_undefined_name,
			   entry_key (sid_external_rule), sid_alternative)) {
	    if (param) {
		if (types_equal (&sid_current_type, param)) {
		    item_add_param (sid_current_item, &sid_current_type);
		} else {
		    E_rule_param_call_mismatch (key, param, &sid_current_type);
		    types_destroy (&sid_current_type);
		    errored = TRUE;
		}
	    } else {
		if (!types_equal_zero_tuple (&sid_current_type)) {
		    E_basic_param_call_mismatch (key, &sid_current_type);
		    types_destroy (&sid_current_type);
		    errored = TRUE;
		}
	    }
	} else {
	    types_destroy (&sid_current_type);
	    errored = TRUE;
	}
	if (types_disjoint_names (&sid_saved_type)) {
	    if (types_check_undefined (&sid_saved_type,
				       rule_param (sid_current.rule),
				       alt_names (sid_current_alt),
				       E_redefined_name,
				       entry_key (sid_external_rule),
				       sid_alternative)) {
		if (types_fillin_types (&sid_saved_type, result)) {
		    types_add_new_names (alt_names (sid_current_alt),
					 &sid_saved_type, sid_unique_pred_id);
		    if (sid_saved_pred_id) {
			E_predicate ();
		    }
		    item_add_result (sid_current_item, &sid_saved_type);
		} else {
		    if (param) {
			E_rule_result_call_mismatch (key, result,
						     &sid_saved_type);
		    } else {
			E_basic_result_call_mismatch (key, result,
						      &sid_saved_type);
		    }
		    types_destroy (&sid_saved_type);
		    errored = TRUE;
		}
	    } else {
		types_destroy (&sid_saved_type);
		errored = TRUE;
	    }
	} else {
	    if (param) {
		E_rule_result_call_clash (key, &sid_saved_type);
	    } else {
		E_basic_result_call_clash (key, &sid_saved_type);
	    }
	    types_destroy (&sid_saved_type);
	    errored = TRUE;
	}
	if (errored) {
	    (void) item_deallocate (sid_current_item);
	    sid_current_item = NULL;
	    (void) alt_deallocate (sid_current_alt);
	    sid_current_alt  = NULL;
	} else {
	    alt_add_item (sid_current_alt, sid_current_item);
	}
    } else {
	if (sid_current_alt) {
	    (void) alt_deallocate (sid_current_alt);
	    sid_current_alt = NULL;
	}
	types_destroy (&sid_saved_type);
	types_destroy (&sid_current_type);
    }
			}
			ZR252 (sid_current_grammar);
			if ((CURRENT_TERMINAL) == 26) {
			    RESTORE_LEXER;
			    goto ZL3;
			}
		    }
		    break;
		  case 9:
		    {
			{

    types_init (&sid_current_type);
    sid_current_pred_id = NULL;
			}
			{

    EntryT *     name_entry = table_get_entry (grammar_table(sid_current_grammar), (&ZI151));
    EntryT *     entry      = NULL;
    TypeTupleT * param      = NULL;
    TypeTupleT * result     = NULL;
    RuleT *      rule;
    BasicT *     basic;

    if ((sid_current_entry) && (sid_current_alt)) {
	if ((name_entry != NULL) &&
	    (!types_contains (alt_names (sid_current_alt), name_entry)) &&
	    (!types_contains (rule_param (sid_current.rule), name_entry))) {
	    name_entry = NULL;
	}
	entry = scope_stack_get_rule (&sid_scope_stack, grammar_table(sid_current_grammar),
				      (&ZI151));
	if (entry) {
	    sid_current_item = item_create (entry);
	    rule             = entry_get_rule (entry);
	    param            = rule_param (rule);
	    result           = rule_result (rule);
	} else {
	    entry = table_get_basic (grammar_table(sid_current_grammar), (&ZI151));
	    if (entry) {
		sid_current_item = item_create (entry);
		basic            = entry_get_basic (entry);
		param            = NULL;
		result           = basic_result (basic);
		if ((name_entry == NULL) &&
		    basic_get_ignored (basic)) {
		    E_ignored_basic_call ((&ZI151));
		}
	    }
	}
	if ((entry == NULL) && (name_entry == NULL)) {
	    NStringT scope;

	    name_entry = scope_stack_get_non_local (&sid_scope_stack,
						    grammar_table(sid_current_grammar),
						    (&ZI151), &scope);
	    if (name_entry) {
		if (nstring_length (&scope) >
		    nstring_length (&sid_maximum_scope)) {
		    nstring_destroy (&sid_maximum_scope);
		    nstring_assign (&sid_maximum_scope, &scope);
		} else {
		    nstring_destroy (&scope);
		}
	    } else {
		E_unknown_rule_or_basic ((&ZI151));
	    }
	} else if ((entry != NULL) && (name_entry != NULL)) {
	    E_ambiguous_call ((&ZI151));
	    entry      = NULL;
	    name_entry = NULL;
	}
    } else {
	name_entry = NULL;
    }
    nstring_destroy (&(ZI151));
    if (entry) {
	BoolT errored = FALSE;
	KeyT *  key     = entry_key (entry);

	if (types_resolve (&sid_current_type, rule_param (sid_current.rule),
			   alt_names (sid_current_alt), E_undefined_name,
			   entry_key (sid_external_rule), sid_alternative)) {
	    if (param) {
		if (types_equal (&sid_current_type, param)) {
		    item_add_param (sid_current_item, &sid_current_type);
		} else {
		    E_rule_param_call_mismatch (key, param, &sid_current_type);
		    types_destroy (&sid_current_type);
		    errored = TRUE;
		}
	    } else {
		if (!types_equal_zero_tuple (&sid_current_type)) {
		    E_basic_param_call_mismatch (key, &sid_current_type);
		    types_destroy (&sid_current_type);
		    errored = TRUE;
		}
	    }
	} else {
	    types_destroy (&sid_current_type);
	    errored = TRUE;
	}
	if (types_disjoint_names (&sid_saved_type)) {
	    if (types_check_undefined (&sid_saved_type,
				       rule_param (sid_current.rule),
				       alt_names (sid_current_alt),
				       E_redefined_name,
				       entry_key (sid_external_rule),
				       sid_alternative)) {
		if (types_fillin_types (&sid_saved_type, result)) {
		    types_add_new_names (alt_names (sid_current_alt),
					 &sid_saved_type, sid_unique_pred_id);
		    if (sid_saved_pred_id) {
			E_predicate ();
		    }
		    item_add_result (sid_current_item, &sid_saved_type);
		} else {
		    if (param) {
			E_rule_result_call_mismatch (key, result,
						     &sid_saved_type);
		    } else {
			E_basic_result_call_mismatch (key, result,
						      &sid_saved_type);
		    }
		    types_destroy (&sid_saved_type);
		    errored = TRUE;
		}
	    } else {
		types_destroy (&sid_saved_type);
		errored = TRUE;
	    }
	} else {
	    if (param) {
		E_rule_result_call_clash (key, &sid_saved_type);
	    } else {
		E_basic_result_call_clash (key, &sid_saved_type);
	    }
	    types_destroy (&sid_saved_type);
	    errored = TRUE;
	}
	if (errored) {
	    (void) item_deallocate (sid_current_item);
	    sid_current_item = NULL;
	    (void) alt_deallocate (sid_current_alt);
	    sid_current_alt  = NULL;
	} else {
	    alt_add_item (sid_current_alt, sid_current_item);
	}
    } else if (name_entry) {
	types_add_name_entry (&sid_current_type, name_entry);
	entry = table_add_rename (grammar_table(sid_current_grammar));
	if (types_resolve (&sid_current_type, rule_param (sid_current.rule),
			   alt_names (sid_current_alt), E_undefined_name,
			   entry_key (sid_external_rule), sid_alternative)) {
	    if (types_contains_references (&sid_current_type)) {
		E_identity_param_has_refs (&sid_current_type,
					   entry_key (sid_external_rule),
					   sid_alternative);
		types_destroy (&sid_current_type);
		sid_current_item = NULL;
	    } else {
		sid_current_item = item_create (entry);
		item_add_param (sid_current_item, &sid_current_type);
	    }
	} else {
	    types_destroy (&sid_current_type);
	    sid_current_item = NULL;
	}
	if (types_disjoint_names (&sid_saved_type)) {
	    if (types_check_undefined (&sid_saved_type,
				       rule_param (sid_current.rule),
				       alt_names (sid_current_alt),
				       E_redefined_name,
				       entry_key (sid_external_rule),
				       sid_alternative)) {
		if (sid_current_item) {
		    if (types_fillin_types (&sid_saved_type,
					    item_param (sid_current_item))) {
			types_add_new_names (alt_names (sid_current_alt),
					     &sid_saved_type,
					     sid_unique_pred_id);
			if (sid_saved_pred_id) {
			    E_predicate ();
			}
			item_add_result (sid_current_item, &sid_saved_type);
			alt_add_item (sid_current_alt, sid_current_item);
		    } else {
			E_identity_mismatch (item_param (sid_current_item),
					     &sid_saved_type);
			types_destroy (&sid_saved_type);
			(void) item_deallocate (sid_current_item);
			sid_current_item = NULL;
		    }
		}
	    } else {
		types_destroy (&sid_saved_type);
		if (sid_current_item) {
		    (void) item_deallocate (sid_current_item);
		    sid_current_item = NULL;
		}
	    }
	} else {
	    E_identity_result_clash (&sid_saved_type);
	    types_destroy (&sid_saved_type);
	    if (sid_current_item) {
		(void) item_deallocate (sid_current_item);
		sid_current_item = NULL;
	    }
	}
	if (sid_current_item == NULL) {
	    (void) alt_deallocate (sid_current_alt);
	    sid_current_alt = NULL;
	}
    } else {
	if (sid_current_alt) {
	    (void) alt_deallocate (sid_current_alt);
	    sid_current_alt = NULL;
	}
	types_destroy (&sid_saved_type);
	types_destroy (&sid_current_type);
    }
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL3;
		}
		goto ZL2;
	      ZL3:;
		{
		    {

    if (!sid_propagating_error) {
	E_expected_tuple_or_term ();
    }
		    }
		    {

    nstring_destroy (&(ZI151));
		    }
		    {

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_ALT_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_SCOPE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
		    }
		}
	      ZL2:;
	    }
	}
	break;
      case 6:
	{
	    ZR175 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ((sid_current_entry) && (sid_current_alt)) {
	EntryT * entry = table_add_rename (grammar_table(sid_current_grammar));

	if (types_resolve (&sid_current_type, rule_param (sid_current.rule),
			   alt_names (sid_current_alt), E_undefined_name,
			   entry_key (sid_external_rule), sid_alternative)) {
	    if (types_contains_references (&sid_current_type)) {
		E_identity_param_has_refs (&sid_current_type,
					   entry_key (sid_external_rule),
					   sid_alternative);
		types_destroy (&sid_current_type);
		sid_current_item = NULL;
	    } else {
		sid_current_item = item_create (entry);
		item_add_param (sid_current_item, &sid_current_type);
	    }
	} else {
	    types_destroy (&sid_current_type);
	    sid_current_item = NULL;
	}
	if (types_disjoint_names (&sid_saved_type)) {
	    if (types_check_undefined (&sid_saved_type,
				       rule_param (sid_current.rule),
				       alt_names (sid_current_alt),
				       E_redefined_name,
				       entry_key (sid_external_rule),
				       sid_alternative)) {
		if (sid_current_item) {
		    if (types_fillin_types (&sid_saved_type,
					    item_param (sid_current_item))) {
			types_add_new_names (alt_names (sid_current_alt),
					     &sid_saved_type,
					     sid_unique_pred_id);
			if (sid_saved_pred_id) {
			    E_predicate ();
			}
			item_add_result (sid_current_item, &sid_saved_type);
			alt_add_item (sid_current_alt, sid_current_item);
		    } else {
			E_identity_mismatch (item_param (sid_current_item),
					     &sid_saved_type);
			types_destroy (&sid_saved_type);
			(void) item_deallocate (sid_current_item);
			sid_current_item = NULL;
		    }
		}
	    } else {
		types_destroy (&sid_saved_type);
		if (sid_current_item) {
		    (void) item_deallocate (sid_current_item);
		    sid_current_item = NULL;
		}
	    }
	} else {
	    E_identity_result_clash (&sid_saved_type);
	    types_destroy (&sid_saved_type);
	    if (sid_current_item) {
		(void) item_deallocate (sid_current_item);
		sid_current_item = NULL;
	    }
	}
	if (sid_current_item == NULL) {
	    (void) alt_deallocate (sid_current_alt);
	    sid_current_alt = NULL;
	}
    } else {
	types_destroy (&sid_saved_type);
	types_destroy (&sid_current_type);
    }
	    }
	    ZR252 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 24:
	{
	    {

    types_init (&sid_current_type);
    sid_current_pred_id = NULL;
	    }
	    ADVANCE_LEXER;
	    {
		{
		    NStringT ZI151;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

    nstring_assign (&ZI151, lexer_string_value (sid_current_stream));
			}
			break;
		      default:
			goto ZL5;
		    }
		    ADVANCE_LEXER;
		    {

    NStringT scope;
    EntryT *   non_local_entry = scope_stack_get_non_local (&sid_scope_stack,
							  grammar_table(sid_current_grammar),
							  (&ZI151), &scope);
    EntryT *   name_entry      = table_get_entry (grammar_table(sid_current_grammar), (&ZI151));

    if (name_entry) {
	if ((sid_current_entry) && (sid_current_alt)) {
	    if ((!types_contains (alt_names (sid_current_alt), name_entry)) &&
		(!types_contains (rule_param (sid_current.rule),
				  name_entry))) {
		name_entry = NULL;
	    }
	} else {
	    name_entry = NULL;
	}
    }
    if (name_entry) {
	types_add_name_and_type (&sid_current_type, name_entry, NULL,
				 TRUE);
	if (non_local_entry) {
	    nstring_destroy (&scope);
	}
	nstring_destroy (&(ZI151));
    } else if (non_local_entry) {
	types_add_name_and_type (&sid_current_type, non_local_entry,
				 NULL, TRUE);
	if (nstring_length (&scope) > nstring_length (&sid_maximum_scope)) {
	    nstring_destroy (&sid_maximum_scope);
	    nstring_assign (&sid_maximum_scope, &scope);
	} else {
	    nstring_destroy (&scope);
	}
	nstring_destroy (&(ZI151));
    } else {
	types_add_name (&sid_current_type, grammar_table(sid_current_grammar), &(ZI151), TRUE);
    }
		    }
		    {

    if ((sid_current_entry) && (sid_current_alt)) {
	EntryT * entry = table_add_rename (grammar_table(sid_current_grammar));

	if (types_resolve (&sid_current_type, rule_param (sid_current.rule),
			   alt_names (sid_current_alt), E_undefined_name,
			   entry_key (sid_external_rule), sid_alternative)) {
	    if (types_contains_references (&sid_current_type)) {
		E_identity_param_has_refs (&sid_current_type,
					   entry_key (sid_external_rule),
					   sid_alternative);
		types_destroy (&sid_current_type);
		sid_current_item = NULL;
	    } else {
		sid_current_item = item_create (entry);
		item_add_param (sid_current_item, &sid_current_type);
	    }
	} else {
	    types_destroy (&sid_current_type);
	    sid_current_item = NULL;
	}
	if (types_disjoint_names (&sid_saved_type)) {
	    if (types_check_undefined (&sid_saved_type,
				       rule_param (sid_current.rule),
				       alt_names (sid_current_alt),
				       E_redefined_name,
				       entry_key (sid_external_rule),
				       sid_alternative)) {
		if (sid_current_item) {
		    if (types_fillin_types (&sid_saved_type,
					    item_param (sid_current_item))) {
			types_add_new_names (alt_names (sid_current_alt),
					     &sid_saved_type,
					     sid_unique_pred_id);
			if (sid_saved_pred_id) {
			    E_predicate ();
			}
			item_add_result (sid_current_item, &sid_saved_type);
			alt_add_item (sid_current_alt, sid_current_item);
		    } else {
			E_identity_mismatch (item_param (sid_current_item),
					     &sid_saved_type);
			types_destroy (&sid_saved_type);
			(void) item_deallocate (sid_current_item);
			sid_current_item = NULL;
		    }
		}
	    } else {
		types_destroy (&sid_saved_type);
		if (sid_current_item) {
		    (void) item_deallocate (sid_current_item);
		    sid_current_item = NULL;
		}
	    }
	} else {
	    E_identity_result_clash (&sid_saved_type);
	    types_destroy (&sid_saved_type);
	    if (sid_current_item) {
		(void) item_deallocate (sid_current_item);
		sid_current_item = NULL;
	    }
	}
	if (sid_current_item == NULL) {
	    (void) alt_deallocate (sid_current_alt);
	    sid_current_alt = NULL;
	}
    } else {
	types_destroy (&sid_saved_type);
	types_destroy (&sid_current_type);
    }
		    }
		    ZR252 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL5;
		    }
		}
		goto ZL4;
	      ZL5:;
		{
		    {

    if (!sid_propagating_error) {
	E_expected_identifier ();
    }
		    }
		    {

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_ALT_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_SCOPE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
		    }
		}
	      ZL4:;
	    }
	}
	break;
      case 26:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_item_rhs ();
    }
	}
	{

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_ALT_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_SCOPE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
	}
    }
}

static void
ZR219(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	ZR235 (sid_current_grammar);
	{
	    switch (CURRENT_TERMINAL) {
	      case 16:
		{
		    ADVANCE_LEXER;
		    ZR230 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 26:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR153(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
  ZL2_153:;
    {
	ZR155 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    sid_propagating_error = FALSE;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 4: case 19:
		{
		    goto ZL2_153;
		}
		/*UNREACHED*/
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR196(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 6:
	{
	    ZR175 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if (sid_current_item) {
	BoolT   errored = FALSE;
	EntryT * entry   = item_entry (sid_current_item);
	ActionT *action  = entry_get_action (entry);

	if (types_resolve (&sid_current_type, rule_param (sid_current.rule),
			   alt_names (sid_current_alt), E_undefined_name,
			   entry_key (sid_external_rule), sid_alternative)) {
	    if (types_equal (&sid_current_type, action_param (action))) {
		item_add_param (sid_current_item, &sid_current_type);
	    } else {
		E_action_param_call_mismatch (entry_key (entry),
					      action_param (action),
					      &sid_current_type);
		types_destroy (&sid_current_type);
		errored = TRUE;
	    }
	} else {
	    types_destroy (&sid_current_type);
	    errored = TRUE;
	}
	if (types_disjoint_names (&sid_saved_type)) {
	    if (types_check_undefined (&sid_saved_type,
				       rule_param (sid_current.rule),
				       alt_names (sid_current_alt),
				       E_redefined_name,
				       entry_key (sid_external_rule),
				       sid_alternative)) {
		if (types_fillin_types (&sid_saved_type,
					action_result (action))) {
		    types_add_new_names (alt_names (sid_current_alt),
					 &sid_saved_type, sid_unique_pred_id);
		    if (sid_saved_pred_id) {
			BoolT  reference;
			EntryT * type = types_find_name_type (&sid_saved_type,
							    sid_saved_pred_id,
							    &reference);

			assert((type != NULL) && (!reference));
			if (sid_predicate_type) {
			    if (type != sid_predicate_type) {
				E_predicate_type (sid_predicate_type, type);
			    }
			} else {
			    grammar_set_predicate_type (sid_current_grammar,
							type);
			    sid_predicate_type = type;
			}
			item_to_predicate (sid_current_item);
		    }
		    item_add_result (sid_current_item, &sid_saved_type);
		} else {
		    E_action_result_call_mismatch (entry_key (entry),
						   action_result (action),
						   &sid_saved_type);
		    types_destroy (&sid_saved_type);
		    errored = TRUE;
		}
	    } else {
		types_destroy (&sid_saved_type);
		errored = TRUE;
	    }
	} else {
	    E_action_result_call_clash (entry_key (entry), &sid_saved_type);
	    types_destroy (&sid_saved_type);
	    errored = TRUE;
	}
	if (errored) {
	    (void) item_deallocate (sid_current_item);
	    sid_current_item = NULL;
	    (void) alt_deallocate (sid_current_alt);
	    sid_current_alt  = NULL;
	} else {
	    alt_add_item (sid_current_alt, sid_current_item);
	}
    } else {
	types_destroy (&sid_saved_type);
	types_destroy (&sid_current_type);
    }
	    }
	    ZR252 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 9:
	{
	    {

    types_init (&sid_current_type);
    sid_current_pred_id = NULL;
	    }
	    {

    if (sid_current_item) {
	BoolT   errored = FALSE;
	EntryT * entry   = item_entry (sid_current_item);
	ActionT *action  = entry_get_action (entry);

	if (types_resolve (&sid_current_type, rule_param (sid_current.rule),
			   alt_names (sid_current_alt), E_undefined_name,
			   entry_key (sid_external_rule), sid_alternative)) {
	    if (types_equal (&sid_current_type, action_param (action))) {
		item_add_param (sid_current_item, &sid_current_type);
	    } else {
		E_action_param_call_mismatch (entry_key (entry),
					      action_param (action),
					      &sid_current_type);
		types_destroy (&sid_current_type);
		errored = TRUE;
	    }
	} else {
	    types_destroy (&sid_current_type);
	    errored = TRUE;
	}
	if (types_disjoint_names (&sid_saved_type)) {
	    if (types_check_undefined (&sid_saved_type,
				       rule_param (sid_current.rule),
				       alt_names (sid_current_alt),
				       E_redefined_name,
				       entry_key (sid_external_rule),
				       sid_alternative)) {
		if (types_fillin_types (&sid_saved_type,
					action_result (action))) {
		    types_add_new_names (alt_names (sid_current_alt),
					 &sid_saved_type, sid_unique_pred_id);
		    if (sid_saved_pred_id) {
			BoolT  reference;
			EntryT * type = types_find_name_type (&sid_saved_type,
							    sid_saved_pred_id,
							    &reference);

			assert((type != NULL) && (!reference));
			if (sid_predicate_type) {
			    if (type != sid_predicate_type) {
				E_predicate_type (sid_predicate_type, type);
			    }
			} else {
			    grammar_set_predicate_type (sid_current_grammar,
							type);
			    sid_predicate_type = type;
			}
			item_to_predicate (sid_current_item);
		    }
		    item_add_result (sid_current_item, &sid_saved_type);
		} else {
		    E_action_result_call_mismatch (entry_key (entry),
						   action_result (action),
						   &sid_saved_type);
		    types_destroy (&sid_saved_type);
		    errored = TRUE;
		}
	    } else {
		types_destroy (&sid_saved_type);
		errored = TRUE;
	    }
	} else {
	    E_action_result_call_clash (entry_key (entry), &sid_saved_type);
	    types_destroy (&sid_saved_type);
	    errored = TRUE;
	}
	if (errored) {
	    (void) item_deallocate (sid_current_item);
	    sid_current_item = NULL;
	    (void) alt_deallocate (sid_current_alt);
	    sid_current_alt  = NULL;
	} else {
	    alt_add_item (sid_current_alt, sid_current_item);
	}
    } else {
	types_destroy (&sid_saved_type);
	types_destroy (&sid_current_type);
    }
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 26:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_tuple_or_term ();
    }
	}
	{

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_ALT_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_SCOPE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
	}
    }
}

static void
ZR185(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 6:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_open_tuple ();
    }
	}
    }
}

static void
ZR253(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	{
	    switch (CURRENT_TERMINAL) {
	      case 20:
		{
		    ADVANCE_LEXER;
		    {

    sid_current_scope = &sid_global_scope;
		    }
		}
		break;
	      default:
		{
		    {

    sid_current_scope = &sid_scope_stack;
		    }
		}
		break;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 10:
		{
		    ZR187 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 4:
		{
		    ZR239 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		goto ZL1;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR186(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 7:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_close_tuple ();
    }
	}
    }
}

static void
ZR128(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    NStringT ZI130;

	    {

    nstring_assign (&ZI130, lexer_string_value (sid_current_stream));
	    }
	    ADVANCE_LEXER;
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 5:
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		}
		goto ZL2;
	      ZL3:;
		{
		    {

    if (!sid_propagating_error) {
	E_expected_typemark ();
    }
		    }
		}
	      ZL2:;
	    }
	    {
		{
		    NStringT ZI133;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

    nstring_assign (&ZI133, lexer_string_value (sid_current_stream));
			}
			break;
		      default:
			goto ZL5;
		    }
		    ADVANCE_LEXER;
		    {
			switch (CURRENT_TERMINAL) {
			  case 24:
			    {
				ADVANCE_LEXER;
				{

    if (!types_add_typed_name (&sid_current_type, grammar_table(sid_current_grammar), &(ZI130),
			       (&ZI133), TRUE)) {
	E_unknown_type ((&ZI133));
    }
    nstring_destroy (&(ZI133));
				}
			    }
			    break;
			  default:
			    {
				{

    if (!types_add_typed_name (&sid_current_type, grammar_table(sid_current_grammar), &(ZI130),
			       (&ZI133), FALSE)) {
	E_unknown_type ((&ZI133));
    }
    nstring_destroy (&(ZI133));
				}
			    }
			    break;
			}
		    }
		}
		goto ZL4;
	      ZL5:;
		{
		    {

    if (!sid_propagating_error) {
	E_expected_identifier ();
    }
		    }
		    {

    nstring_destroy (&(ZI130));
		    }
		    {

    if (sid_finished_terminals) {
	while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	       (CURRENT_TERMINAL != LEXER_TOK_DEFINE) &&
	       (CURRENT_TERMINAL != LEXER_TOK_BEGIN_SCOPE) &&
	       (CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE) &&
	       (CURRENT_TERMINAL != LEXER_TOK_SEPARATOR) &&
	       (CURRENT_TERMINAL != LEXER_TOK_CLOSE_TUPLE) &&
	       (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	       (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
		nstring_destroy (lexer_string_value (sid_current_stream));
	    }
	    ADVANCE_LEXER;
	}
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	    ADVANCE_LEXER;
	}
    } else {
	while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	       (CURRENT_TERMINAL != LEXER_TOK_SEPARATOR) &&
	       (CURRENT_TERMINAL != LEXER_TOK_CLOSE_TUPLE) &&
	       (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	       (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	       (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
		nstring_destroy (lexer_string_value (sid_current_stream));
	    }
	    ADVANCE_LEXER;
	}
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	    ADVANCE_LEXER;
	}
    }
    sid_propagating_error = TRUE;
		    }
		}
	      ZL4:;
	    }
	}
	break;
      case 5:
	{
	    ADVANCE_LEXER;
	    {
		{
		    NStringT ZI133;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

    nstring_assign (&ZI133, lexer_string_value (sid_current_stream));
			}
			break;
		      default:
			goto ZL8;
		    }
		    ADVANCE_LEXER;
		    {
			switch (CURRENT_TERMINAL) {
			  case 24:
			    {
				ADVANCE_LEXER;
				{

    if (!types_add_type (&sid_current_type, grammar_table(sid_current_grammar), (&ZI133), TRUE)) {
	E_unknown_type ((&ZI133));
    }
    nstring_destroy (&(ZI133));
				}
			    }
			    break;
			  default:
			    {
				{

    if (!types_add_type (&sid_current_type, grammar_table(sid_current_grammar), (&ZI133),
			 FALSE)) {
	E_unknown_type ((&ZI133));
    }
    nstring_destroy (&(ZI133));
				}
			    }
			    break;
			}
		    }
		}
		goto ZL7;
	      ZL8:;
		{
		    {

    if (!sid_propagating_error) {
	E_expected_identifier ();
    }
		    }
		    {

    if (sid_finished_terminals) {
	while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	       (CURRENT_TERMINAL != LEXER_TOK_DEFINE) &&
	       (CURRENT_TERMINAL != LEXER_TOK_BEGIN_SCOPE) &&
	       (CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE) &&
	       (CURRENT_TERMINAL != LEXER_TOK_SEPARATOR) &&
	       (CURRENT_TERMINAL != LEXER_TOK_CLOSE_TUPLE) &&
	       (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	       (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
		nstring_destroy (lexer_string_value (sid_current_stream));
	    }
	    ADVANCE_LEXER;
	}
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	    ADVANCE_LEXER;
	}
    } else {
	while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	       (CURRENT_TERMINAL != LEXER_TOK_SEPARATOR) &&
	       (CURRENT_TERMINAL != LEXER_TOK_CLOSE_TUPLE) &&
	       (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	       (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	       (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
		nstring_destroy (lexer_string_value (sid_current_stream));
	    }
	    ADVANCE_LEXER;
	}
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	    ADVANCE_LEXER;
	}
    }
    sid_propagating_error = TRUE;
		    }
		}
	      ZL7:;
	    }
	}
	break;
      case 26:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_tuple_defn ();
    }
	}
	{

    if (sid_finished_terminals) {
	while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	       (CURRENT_TERMINAL != LEXER_TOK_DEFINE) &&
	       (CURRENT_TERMINAL != LEXER_TOK_BEGIN_SCOPE) &&
	       (CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE) &&
	       (CURRENT_TERMINAL != LEXER_TOK_SEPARATOR) &&
	       (CURRENT_TERMINAL != LEXER_TOK_CLOSE_TUPLE) &&
	       (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	       (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
		nstring_destroy (lexer_string_value (sid_current_stream));
	    }
	    ADVANCE_LEXER;
	}
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	    ADVANCE_LEXER;
	}
    } else {
	while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	       (CURRENT_TERMINAL != LEXER_TOK_SEPARATOR) &&
	       (CURRENT_TERMINAL != LEXER_TOK_CLOSE_TUPLE) &&
	       (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	       (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	       (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
		nstring_destroy (lexer_string_value (sid_current_stream));
	    }
	    ADVANCE_LEXER;
	}
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	    ADVANCE_LEXER;
	}
    }
    sid_propagating_error = TRUE;
	}
    }
}

static void
ZR259(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
  ZL2_259:;
    {
	ZR261 (sid_current_grammar);
	{
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		{

    (ZI0) = (CURRENT_TERMINAL == LEXER_TOK_TERMINATOR);
		}
		if (!ZI0)
		    goto ZL5;
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL5:;
	    switch (CURRENT_TERMINAL) {
	      case 23:
		{
		    ADVANCE_LEXER;
		    goto ZL2_259;
		}
		/*UNREACHED*/
	      default:
		goto ZL4;
	    }
	    /*UNREACHED*/
	  ZL4:;
	    {
		{

    if (!sid_propagating_error) {
	E_expected_separator ();
    }
		}
		{

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_SEPARATOR)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
		}
		{

    sid_propagating_error = FALSE;
		}
		{
		    {
			{

    (ZI0) = (CURRENT_TERMINAL != LEXER_TOK_SEPARATOR);
			}
			if (!ZI0)
			    goto ZL7;
		    }
		    goto ZL6;
		  ZL7:;
		    {
			goto ZL2_259;
		    }
		    /*UNREACHED*/
		  ZL6:;
		}
	    }
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR126(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 5:
	{
	    ADVANCE_LEXER;
	    ZR142 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    types_assign (&sid_saved_type, &sid_current_type);
    sid_saved_pred_id = sid_current_pred_id;
	    }
	    ZR146 (sid_current_grammar);
	    ZR142 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    types_init (&sid_saved_type);
    types_init (&sid_current_type);
    sid_saved_pred_id   = NULL;
    sid_current_pred_id = NULL;
	    }
	}
	break;
      case 26:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR208(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    NStringT ZI151;

	    {

    nstring_assign (&ZI151, lexer_string_value (sid_current_stream));
	    }
	    ADVANCE_LEXER;
	    {
		{
		    {

    types_init (&sid_current_type);
    sid_current_pred_id = NULL;
		    }
		    ZR284 (sid_current_grammar, &ZI151);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		}
		goto ZL2;
	      ZL3:;
		{
		    {

    if (!sid_propagating_error) {
	E_expected_tuple_def_or_term ();
    }
		    }
		    {

    nstring_destroy (&(ZI151));
		    }
		    {

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_ALT_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_SCOPE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
		    }
		}
	      ZL2:;
	    }
	}
	break;
      case 24:
	{
	    ADVANCE_LEXER;
	    {
		{
		    NStringT ZI151;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

    nstring_assign (&ZI151, lexer_string_value (sid_current_stream));
			}
			break;
		      default:
			goto ZL5;
		    }
		    ADVANCE_LEXER;
		    {

    types_init (&sid_current_type);
    sid_current_pred_id = NULL;
		    }
		    {

    NStringT scope;
    EntryT *   non_local_entry = scope_stack_get_non_local (&sid_scope_stack,
							  grammar_table(sid_current_grammar),
							  (&ZI151), &scope);
    EntryT *   name_entry      = table_get_entry (grammar_table(sid_current_grammar), (&ZI151));

    if (name_entry) {
	if ((sid_current_entry) && (sid_current_alt)) {
	    if ((!types_contains (alt_names (sid_current_alt), name_entry)) &&
		(!types_contains (rule_param (sid_current.rule),
				  name_entry))) {
		name_entry = NULL;
	    }
	} else {
	    name_entry = NULL;
	}
    }
    if (name_entry) {
	types_add_name_and_type_var (&sid_current_type, name_entry,
				     NULL);
	if (non_local_entry) {
	    nstring_destroy (&scope);
	}
	nstring_destroy (&(ZI151));
    } else if (non_local_entry) {
	types_add_name_and_type_var (&sid_current_type, non_local_entry,
				     NULL);
	if (nstring_length (&scope) > nstring_length (&sid_maximum_scope)) {
	    nstring_destroy (&sid_maximum_scope);
	    nstring_assign (&sid_maximum_scope, &scope);
	} else {
	    nstring_destroy (&scope);
	}
	nstring_destroy (&(ZI151));
    } else {
	E_undefined_assignment ((&ZI151));
	types_add_name (&sid_current_type, grammar_table(sid_current_grammar), &(ZI151), FALSE);
    }
		    }
		    {

    types_assign (&sid_saved_type, &sid_current_type);
    sid_saved_pred_id = sid_current_pred_id;
		    }
		    ZR249 (sid_current_grammar);
		    ZR199 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL5;
		    }
		}
		goto ZL4;
	      ZL5:;
		{
		    {

    if (!sid_propagating_error) {
	E_expected_identifier ();
    }
		    }
		}
	      ZL4:;
	    }
	}
	break;
      case 6:
	{
	    ZR163 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    types_assign (&sid_saved_type, &sid_current_type);
    sid_saved_pred_id = sid_current_pred_id;
	    }
	    ZR249 (sid_current_grammar);
	    ZR199 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 10: case 18: case 19:
	{
	    {

    types_init (&sid_current_type);
    sid_current_pred_id = NULL;
	    }
	    ZR283 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 26:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR217(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	NStringT ZI151;

	switch (CURRENT_TERMINAL) {
	  case 4:
	    {

    nstring_assign (&ZI151, lexer_string_value (sid_current_stream));
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    if ((sid_current_entry) && (sid_current_alt)) {
	EntryT * entry = scope_stack_get_action (&sid_scope_stack,
					       grammar_table(sid_current_grammar), (&ZI151));

	if (entry) {
	    sid_current_item = item_create (entry);
	} else {
	    E_unknown_action ((&ZI151));
	    sid_current_item = NULL;
	    (void) alt_deallocate (sid_current_alt);
	    sid_current_alt  = NULL;
	}
    } else {
	sid_current_item = NULL;
    }
    nstring_destroy (&(ZI151));
	}
	ZR246 (sid_current_grammar);
	ZR196 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_identifier ();
    }
	}
	{

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_ALT_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_SCOPE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
	}
    }
}

static void
ZR155(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    NStringT ZI151;

	    {

    nstring_assign (&ZI151, lexer_string_value (sid_current_stream));
	    }
	    ADVANCE_LEXER;
	    {

    sid_current_entry = table_add_basic (grammar_table(sid_current_grammar), &(ZI151),
					 sid_current_grammar, FALSE);
    if (sid_current_entry == NULL) {
	E_duplicate_basic ((&ZI151));
	nstring_destroy (&(ZI151));
    } else {
	sid_current.basic = entry_get_basic (sid_current_entry);
    }
	    }
	    ZR126 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if (sid_current_entry) {
	KeyT * key = entry_key (sid_current_entry);

	if (types_contains_names (&sid_saved_type)) {
	    E_basic_param_has_names (key, &sid_saved_type);
	}
	if (types_contains_names (&sid_current_type)) {
	    E_basic_result_has_names (key, &sid_current_type);
	}
	if (types_contains_references (&sid_current_type)) {
	    E_basic_result_has_refs (key, &sid_current_type);
	}
	if (!types_equal_zero_tuple (&sid_saved_type)) {
	    E_basic_param_mismatch (key, &sid_saved_type);
	}
	types_assign (basic_result (sid_current.basic), &sid_current_type);
    } else {
	types_destroy (&sid_current_type);
    }
    types_destroy (&sid_saved_type);
	    }
	    ZR252 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 19:
	{
	    ADVANCE_LEXER;
	    {
		{
		    NStringT ZI151;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

    nstring_assign (&ZI151, lexer_string_value (sid_current_stream));
			}
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    {

    sid_current_entry = table_add_basic (grammar_table(sid_current_grammar), &(ZI151),
					 sid_current_grammar, TRUE);
    if (sid_current_entry == NULL) {
	E_duplicate_basic ((&ZI151));
	nstring_destroy (&(ZI151));
    } else {
	sid_current.basic = entry_get_basic (sid_current_entry);
    }
		    }
		    ZR126 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		    {

    if (sid_current_entry) {
	KeyT * key = entry_key (sid_current_entry);

	if (types_contains_names (&sid_saved_type)) {
	    E_basic_param_has_names (key, &sid_saved_type);
	}
	if (types_contains_names (&sid_current_type)) {
	    E_basic_result_has_names (key, &sid_current_type);
	}
	if (types_contains_references (&sid_current_type)) {
	    E_basic_result_has_refs (key, &sid_current_type);
	}
	if (!types_equal_zero_tuple (&sid_saved_type)) {
	    E_basic_param_mismatch (key, &sid_saved_type);
	}
	types_assign (basic_result (sid_current.basic), &sid_current_type);
    } else {
	types_destroy (&sid_current_type);
    }
    types_destroy (&sid_saved_type);
		    }
		    ZR252 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		}
		goto ZL2;
	      ZL3:;
		{
		    {

    if (!sid_propagating_error) {
	E_expected_identifier ();
    }
		    }
		    {

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
		    }
		}
	      ZL2:;
	    }
	}
	break;
      case 26:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_terminal_decn ();
    }
	}
	{

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
	}
    }
}

static void
ZR187(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 10:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    {
		NStringT ZI151;

		switch (CURRENT_TERMINAL) {
		  case 4:
		    {

    nstring_assign (&ZI151, lexer_string_value (sid_current_stream));
		    }
		    break;
		  default:
		    goto ZL3;
		}
		ADVANCE_LEXER;
		{

    sid_current_entry = scope_stack_add_action (sid_current_scope,
						grammar_table(sid_current_grammar), &(ZI151),
						sid_enclosing_rule,
						&sid_redefining_entry);
    if (sid_current_entry) {
	sid_current.action = entry_get_action (sid_current_entry);
    } else {
	E_duplicate_action ((&ZI151));
	nstring_destroy (&(ZI151));
    }
		}
		ZR246 (sid_current_grammar);
		ZR126 (sid_current_grammar);
		if ((CURRENT_TERMINAL) == 26) {
		    RESTORE_LEXER;
		    goto ZL3;
		}
		{

    if (sid_current_entry) {
	KeyT *       key     = entry_key (sid_current_entry);
	TypeTupleT * param   = action_param (sid_current.action);
	TypeTupleT * result  = action_result (sid_current.action);
	BoolT      errored = FALSE;

	if (types_contains_names (&sid_saved_type)) {
	    E_action_param_has_names (key, &sid_saved_type);
	    errored = TRUE;
	}
	if (sid_redefining_entry) {
	    if (!types_equal (param, &sid_saved_type)) {
		E_action_param_mismatch (key, param, &sid_saved_type);
		errored = TRUE;
	    }
	}
	if (types_contains_names (&sid_current_type)) {
	    E_action_result_has_names (key, &sid_current_type);
	    errored = TRUE;
	}
	if (types_contains_references (&sid_current_type)) {
	    E_action_result_has_refs (key, &sid_current_type);
	    errored = TRUE;
	}
	if (sid_redefining_entry) {
	    if (!types_equal (result, &sid_current_type)) {
		E_action_result_mismatch (key, result, &sid_current_type);
		errored = TRUE;
	    }
	}
	if (errored || sid_redefining_entry) {
	    types_destroy (&sid_saved_type);
	    types_destroy (&sid_current_type);
	} else {
	    types_assign (param, &sid_saved_type);
	    types_assign (result, &sid_current_type);
	}
    } else {
	types_destroy (&sid_saved_type);
	types_destroy (&sid_current_type);
    }
		}
		ZR252 (sid_current_grammar);
		if ((CURRENT_TERMINAL) == 26) {
		    RESTORE_LEXER;
		    goto ZL3;
		}
	    }
	    goto ZL2;
	  ZL3:;
	    {
		{

    if (!sid_propagating_error) {
	E_expected_identifier ();
    }
		}
		{

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_SCOPE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
		}
	    }
	  ZL2:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR228(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
  ZL2_228:;
    {
	ZR221 (sid_current_grammar);
	{
	    switch (CURRENT_TERMINAL) {
	      case 4: case 6: case 10: case 13: case 18:
	      case 19: case 24:
		{
		    goto ZL2_228;
		}
		/*UNREACHED*/
	      case 26:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_item ();
    }
	}
	{

    while ((CURRENT_TERMINAL != LEXER_TOK_EOF) &&
	   (CURRENT_TERMINAL != LEXER_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != LEXER_TOK_ALT_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_RULE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_END_SCOPE) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS) &&
	   (CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY)) {
	if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	    nstring_destroy (lexer_string_value (sid_current_stream));
	}
	ADVANCE_LEXER;
    }
    if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
	nstring_destroy (lexer_string_value (sid_current_stream));
    }
    if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
	ADVANCE_LEXER;
    }
    sid_propagating_error = TRUE;
	}
	{

    sid_propagating_error = FALSE;
	}
    }
}

static void
ZR261(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	NStringT ZI151;

	switch (CURRENT_TERMINAL) {
	  case 4:
	    {

    nstring_assign (&ZI151, lexer_string_value (sid_current_stream));
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    EntryT * entry = table_get_rule (grammar_table(sid_current_grammar), (&ZI151));

    if (entry) {
	if (entry_list_contains (grammar_entry_list(sid_current_grammar), entry)) {
	    E_mult_entry (entry_key (entry));
	} else {
	    entry_list_add (grammar_entry_list(sid_current_grammar), entry);
	    rule_required (entry_get_rule (entry));
	}
    } else {
	E_unknown_rule ((&ZI151));
    }
    nstring_destroy (&(ZI151));
	}
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_identifier ();
    }
	}
    }
}

static void
ZR168(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
  ZL2_168:;
    {
	ZR165 (sid_current_grammar);
	{
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		{

    (ZI0) = ((CURRENT_TERMINAL == LEXER_TOK_CLOSE_TUPLE) ||
		  (CURRENT_TERMINAL == LEXER_TOK_EOF) ||
		  (sid_propagating_error));
		}
		if (!ZI0)
		    goto ZL5;
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL5:;
	    switch (CURRENT_TERMINAL) {
	      case 23:
		{
		    ADVANCE_LEXER;
		    goto ZL2_168;
		}
		/*UNREACHED*/
	      default:
		goto ZL4;
	    }
	    /*UNREACHED*/
	  ZL4:;
	    {
		{

    if (!sid_propagating_error) {
	E_expected_separator ();
    }
		}
		goto ZL2_168;
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR246(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 11:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_end_action ();
    }
	}
    }
}

static void
ZR248(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 12: case 21:
	{
	    {

    if (sid_current_entry) {
	KeyT * key = entry_key (sid_current_entry);

	if (rule_is_defined (sid_current.rule)) {
	    E_rule_already_defined (key);
	    sid_current_entry = NULL;
	    types_destroy (&sid_saved_type);
	    types_destroy (&sid_current_type);
	} else {
	    TypeTupleT * param   = rule_param (sid_current.rule);
	    TypeTupleT * result  = rule_result (sid_current.rule);
	    BoolT      errored = FALSE;

	    rule_defined (sid_current.rule);
	    if (!types_disjoint_names (&sid_saved_type)) {
		E_rule_param_clash (key, &sid_saved_type);
		errored = TRUE;
	    }
	    if (types_check_shadowing (&sid_saved_type, &sid_scope_stack,
				       sid_current.rule)) {
		errored = TRUE;
	    }
	    if (sid_redefining_entry) {
		if (!types_fillin_names (param, &sid_saved_type)) {
		    E_rule_param_mismatch (key, param, &sid_saved_type);
		    errored = TRUE;
		}
		types_destroy (&sid_saved_type);
	    } else {
		types_assign (param, &sid_saved_type);
	    }
	    if (!types_disjoint_names (&sid_current_type)) {
		E_rule_result_clash (key, &sid_current_type);
		errored = TRUE;
	    }
	    if (types_check_shadowing (&sid_current_type, &sid_scope_stack,
				       sid_current.rule)) {
		errored = TRUE;
	    }
	    if (types_contains_references (&sid_current_type)) {
		E_rule_result_has_refs (key, &sid_current_type);
		errored = TRUE;
	    }
	    if (sid_redefining_entry) {
		if (!types_fillin_names (result, &sid_current_type)) {
		    E_rule_result_mismatch (key, result, &sid_current_type);
		    errored = TRUE;
		}
		types_destroy (&sid_current_type);
	    } else {
		types_assign (result, &sid_current_type);
	    }
	    if (errored) {
		sid_current_entry = NULL;
	    } else {
		if (types_intersect (param, result)) {
		    E_rule_formal_clash (key, param, result);
		    sid_current_entry = NULL;
		}
	    }
	}
    } else {
	types_destroy (&sid_saved_type);
	types_destroy (&sid_current_type);
    }
    sid_alternative   = 0;
    sid_internal_rule = FALSE;
    sid_external_rule = sid_current_entry;
    nstring_init (&sid_maximum_scope);
	    }
	    {

    if (sid_current_entry) {
	KeyT *     key   = entry_key (sid_current_entry);
	NStringT * scope = key_get_string (key);

	scope_stack_push (&sid_scope_stack, scope);
    }
	    }
	    ZR192 (sid_current_grammar);
	    ZR249 (sid_current_grammar);
	    {
		if ((CURRENT_TERMINAL) == 26) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{
		    switch (CURRENT_TERMINAL) {
		      case 13:
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		}
		goto ZL2;
	      ZL3:;
		{
		    {

    if (!sid_propagating_error) {
	E_expected_begin_rule ();
    }
		    }
		}
	      ZL2:;
	    }
	    ZR219 (sid_current_grammar);
	    ZR251 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if (sid_current_entry) {
	scope_stack_pop (&sid_scope_stack);
    }
	    }
	    {

    if (sid_current_entry) {
	nstring_assign (rule_maximum_scope (sid_current.rule),
			&sid_maximum_scope);
    } else {
	nstring_destroy (&sid_maximum_scope);
    }
	    }
	    ZR252 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 9:
	{
	    {

    if (sid_current_entry) {
	KeyT *       key     = entry_key (sid_current_entry);
	TypeTupleT * param   = rule_param (sid_current.rule);
	TypeTupleT * result  = rule_result (sid_current.rule);
	BoolT      errored = FALSE;

	if (types_contains_names (&sid_saved_type)) {
	    E_rule_param_has_names (key, &sid_saved_type);
	    errored = TRUE;
	}
	if (sid_redefining_entry) {
	    if (!types_equal (param, &sid_saved_type)) {
		E_rule_param_mismatch (key, param, &sid_saved_type);
		errored = TRUE;
	    }
	}
	if (types_contains_names (&sid_current_type)) {
	    E_rule_result_has_names (key, &sid_current_type);
	    errored = TRUE;
	}
	if (types_contains_references (&sid_current_type)) {
	    E_rule_result_has_refs (key, &sid_current_type);
	    errored = TRUE;
	}
	if (sid_redefining_entry) {
	    if (!types_equal (result, &sid_current_type)) {
		E_rule_result_mismatch (key, result, &sid_current_type);
		errored = TRUE;
	    }
	}
	if (errored || sid_redefining_entry) {
	    types_destroy (&sid_saved_type);
	    types_destroy (&sid_current_type);
	} else {
	    types_assign (param, &sid_saved_type);
	    types_assign (result, &sid_current_type);
	}
    } else {
	types_destroy (&sid_saved_type);
	types_destroy (&sid_current_type);
    }
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 26:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR249(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 12:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_define ();
    }
	}
    }
}

static void
ZR180(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
  ZL2_180:;
    {
	ZR177 (sid_current_grammar);
	{
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		{

    (ZI0) = ((CURRENT_TERMINAL == LEXER_TOK_CLOSE_TUPLE) ||
		  (CURRENT_TERMINAL == LEXER_TOK_EOF) ||
		  (sid_propagating_error));
		}
		if (!ZI0)
		    goto ZL5;
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL5:;
	    switch (CURRENT_TERMINAL) {
	      case 23:
		{
		    ADVANCE_LEXER;
		    goto ZL2_180;
		}
		/*UNREACHED*/
	      default:
		goto ZL4;
	    }
	    /*UNREACHED*/
	  ZL4:;
	    {
		{

    if (!sid_propagating_error) {
	E_expected_separator ();
    }
		}
		goto ZL2_180;
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (26);
    return;
}

static void
ZR251(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 14:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_end_rule ();
    }
	}
    }
}

static void
ZR252(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 9:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	{

    if (!sid_propagating_error) {
	E_expected_terminator ();
    }
	}
    }
}

/* BEGINNING OF TRAILER */



/* END OF FILE */
