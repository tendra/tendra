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

	#include "shared/check/check.h"
	#include "parser.h"
	#include "adt/action.h"
	#include "adt/basic.h"
	#include <exds/common.h>
	#include <exds/exception.h>
	#include <exds/bitvec.h>
	#include <exds/dalloc.h>
	#include <exds/dstring.h>
	#include "gen-errors.h"
	#include "grammar.h"
	#include "lexer.h"
	#include "adt/non-local.h"
	#include "adt/rule.h"
	#include "adt/scope.h"
	#include "adt/table.h"
	#include "adt/types.h"

	#define CURRENT_TERMINAL lexer_get_terminal(sid_current_stream)
	#define ADVANCE_LEXER lexer_next_token(sid_current_stream)
	#define SAVE_LEXER(x) (lexer_save_terminal(sid_current_stream, (LexerTokenT) (x)))
	#define RESTORE_LEXER (lexer_restore_terminal(sid_current_stream))
	#define ALT_LIMIT (UINT_MAX - 1)

	/* typedefs for the maps section */
	typedef AltT *AltP;
	typedef EntryT *EntryP;
	typedef ItemT *ItemP;
	typedef RuleT *RuleP;
	typedef NonLocalEntryT *NonLocalEntryP;

	LexerStreamT *sid_current_stream;

	static ScopeStackT  sid_scope_stack;
	static ScopeStackT  sid_global_scope;
	static ScopeStackT *sid_current_scope;
	static EntryT      *sid_current_entry;
	static RuleT       *sid_enclosing_rule;
	static RuleT       *sid_current_rule;
	static BoolT        sid_redefining_entry;
	static NStringT     sid_maximum_scope;
	static BoolT        sid_saved_pred_id;
	static BoolT        sid_current_pred_id;
	static AltT        *sid_current_alt;
	static ItemT       *sid_current_item;
	static unsigned     sid_alternative;
	static BoolT        sid_internal_rule;
	static EntryT      *sid_external_rule;
	static unsigned     sid_num_alternatives = 0;
	static BoolT        sid_propagating_error = FALSE;
	static BoolT        sid_finished_terminals = FALSE;


/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZR246(GrammarP);
static void ZR241(GrammarP);
static void ZR260(GrammarP, TypeTupleT *, TypeTupleT *);
static void ZR143(GrammarP, TypeTupleT *);
static void ZR243(GrammarP);
static void ZR178(GrammarP, TypeTupleT *);
static void ZR250(GrammarP);
static void ZR170(GrammarP, TypeTupleT *);
static void ZR152(GrammarP);
static void ZR153(GrammarP);
static void ZR182(GrammarP, TypeTupleT *);
static void ZR232(GrammarP);
static void ZR155(GrammarP);
static void ZR190(GrammarP, TypeTupleT *);
static void ZR202(GrammarP);
static void ZR172(GrammarP, TypeTupleT *);
static void ZR168(GrammarP);
extern void sid_parse_grammar(GrammarP);
static void ZR146(GrammarP, TypeTupleT *);
static void ZR297(GrammarP, NStringT *);
static void ZR299(GrammarP);
static void ZR300(GrammarP, NStringT *);
static void ZR301(GrammarP, NStringT *);
static void ZR148(GrammarP, TypeTupleT *);
static void ZR184(GrammarP, TypeTupleT *);
static void ZR210(GrammarP, TypeTupleT *);
static void ZR230(GrammarP);
static void ZR159(GrammarP);
static void ZR206(GrammarP, TypeTupleT *);
static void ZR265(GrammarP);
static void ZR134(GrammarP, TypeTupleT *);
static void ZR192(GrammarP);
static void ZR271(GrammarP);
static void ZR193(GrammarP);
static void ZR131(GrammarP, TypeTupleT *, TypeTupleT *);
static void ZR219(GrammarP);
static void ZR161(GrammarP);
static void ZR225(GrammarP);
static void ZR228(GrammarP, TypeTupleT *);
static void ZR229(GrammarP);
static void ZR194(GrammarP);
static void ZR239(GrammarP);
static void ZR273(GrammarP);
static void ZR237(GrammarP);
static void ZR175(GrammarP, TypeTupleT *);
static void ZR245(GrammarP);
static void ZR187(GrammarP, TypeTupleT *);

/* BEGINNING OF STATIC VARIABLES */

static BoolT ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZR246(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
  ZL2_246:;
    {
	ZR243 (sid_current_grammar);
	{
	    switch (CURRENT_TERMINAL) {
	      case 15:
		{
		    ADVANCE_LEXER;
		    goto ZL2_246;
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
ZR241(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	{

		if (sid_current_entry) {
			sid_current_alt = alt_create();
		}
	
	}
	ZR239 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

		if (sid_current_entry && sid_current_alt) {
			if (types_check_names(rule_result(sid_current_rule),
				alt_names(sid_current_alt))) {
				TypeTupleT used;

				types_copy(&used, rule_result (sid_current_rule));
				item_compute_minimal_dataflow (alt_item_head (sid_current_alt),
					&used);
				types_destroy(&used);
				rule_set_handler(sid_current_rule, sid_current_alt);
			} else {
				(void) alt_deallocate(sid_current_alt);
				E_handler_result_mismatch(entry_key (sid_external_rule));
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
ZR260(GrammarP sid_current_grammar, TypeTupleT *ZI129, TypeTupleT *ZI130)
{
    switch (CURRENT_TERMINAL) {
      case 12: case 21:
	{
	    {

		if (sid_current_entry) {
			KeyT *key;

			key = entry_key(sid_current_entry);

			if (rule_is_defined(sid_current_rule)) {
				E_rule_already_defined (key);
				sid_current_entry = NULL;
				types_destroy((ZI129));
				types_destroy((ZI130));
			} else {
				TypeTupleT *param   = rule_param(sid_current_rule);
				TypeTupleT *result  = rule_result(sid_current_rule);
				BoolT       errored = FALSE;

				rule_defined(sid_current_rule);
				if (!types_disjoint_names((ZI129))) {
					E_rule_param_clash(key, (ZI129));
					errored = TRUE;
				}

				if (types_check_shadowing((ZI129), &sid_scope_stack,
					sid_current_rule)) {
					errored = TRUE;
				}

				if (sid_redefining_entry) {
					if (!types_fillin_names(param, (ZI129))) {
						E_rule_param_mismatch(key, param, (ZI129));
						errored = TRUE;
					}
					types_destroy((ZI129));
				} else {
					types_assign(param, (ZI129));
				}

				if (!types_disjoint_names((ZI130))) {
					E_rule_result_clash(key, (ZI130));
					errored = TRUE;
				}

				if (types_check_shadowing((ZI130), &sid_scope_stack,
					sid_current_rule)) {
					errored = TRUE;
				}

				if (types_contains_references((ZI130))) {
					E_rule_result_has_refs(key, (ZI130));
					errored = TRUE;
				}

				if (sid_redefining_entry) {
					if (!types_fillin_names(result, (ZI130))) {
						E_rule_result_mismatch(key, result, (ZI130));
						errored = TRUE;
					}
					types_destroy((ZI130));
				} else {
					types_assign(result, (ZI130));
				}

				if (errored) {
					sid_current_entry = NULL;
				} else {
					if (types_intersect(param, result)) {
						E_rule_formal_clash(key, param, result);
						sid_current_entry = NULL;
					}
				}
			}
		} else {
			types_destroy((ZI129));
			types_destroy((ZI130));
		}

		sid_alternative   = 0;
		sid_internal_rule = FALSE;
		sid_external_rule = sid_current_entry;
		nstring_init(&sid_maximum_scope);
	
	    }
	    {

		if (sid_current_entry) {
			KeyT     *key   = entry_key(sid_current_entry);
			NStringT *scope = key_get_string(key);

			scope_stack_push(&sid_scope_stack, scope);
		}
	
	    }
	    ZR202 (sid_current_grammar);
	    ZR225 (sid_current_grammar);
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
			E_expected_begin_rule();
		}
	
		    }
		}
	      ZL2:;
	    }
	    ZR230 (sid_current_grammar);
	    ZR237 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

		if (sid_current_entry) {
			scope_stack_pop(&sid_scope_stack);
		}
	
	    }
	    {

		if (sid_current_entry) {
			nstring_assign(rule_maximum_scope(sid_current_rule),
				&sid_maximum_scope);
		} else {
			nstring_destroy(&sid_maximum_scope);
		}
	
	    }
	    ZR245 (sid_current_grammar);
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
			KeyT       *key     = entry_key (sid_current_entry);
			TypeTupleT *param   = rule_param (sid_current_rule);
			TypeTupleT *result  = rule_result (sid_current_rule);
			BoolT       errored = FALSE;

			if (types_contains_names((ZI129))) {
				E_rule_param_has_names(key, (ZI129));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(param, (ZI129))) {
					E_rule_param_mismatch(key, param, (ZI129));
					errored = TRUE;
				}
			}

			if (types_contains_names((ZI130))) {
				E_rule_result_has_names(key, (ZI130));
				errored = TRUE;
			}

			if (types_contains_references((ZI130))) {
				E_rule_result_has_refs(key, (ZI130));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(result, (ZI130))) {
					E_rule_result_mismatch (key, result, (ZI130));
					errored = TRUE;
				}
			}

			if (errored || sid_redefining_entry) {
				types_destroy((ZI129));
				types_destroy((ZI130));
			} else {
				types_assign(param, (ZI129));
				types_assign(result, (ZI130));
			}
		} else {
			types_destroy((ZI129));
			types_destroy((ZI130));
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
ZR143(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
  ZL2_143:;
    {
	ZR134 (sid_current_grammar, ZI133);
	{
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		{

		(ZI0) = (CURRENT_TERMINAL == LEXER_TOK_CLOSE_TUPLE
			|| CURRENT_TERMINAL == LEXER_TOK_EOF
			|| sid_propagating_error);
	
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
		    goto ZL2_143;
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
			E_expected_separator();
		}
	
		}
		goto ZL2_143;
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
ZR243(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 17:
	{
	    {

		sid_num_alternatives++;
		if (sid_num_alternatives == ALT_LIMIT) {
			E_too_many_alternatives();
			UNREACHED;
		}

		if (!sid_internal_rule) {
			sid_alternative++;
		}

		if (sid_current_entry) {
			if (rule_has_empty_alt(sid_current_rule)) {
				E_multiple_empty_alts(entry_key(sid_external_rule));
			} else if (!types_equal_zero_tuple(rule_result(sid_current_rule))) {
				E_alt_result_mismatch(entry_key (sid_external_rule),
					sid_alternative);
			} else {
				rule_add_empty_alt(sid_current_rule);
			}
		}
	
	    }
	    ADVANCE_LEXER;
	    ZR245 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 4: case 6: case 10: case 13:
      case 18: case 19: case 24:
	{
	    {

		sid_num_alternatives++;
		if (sid_num_alternatives == ALT_LIMIT) {
			E_too_many_alternatives();
			UNREACHED;
		}

		if (!sid_internal_rule) {
			sid_alternative++;
		}

		if (sid_current_entry) {
			sid_current_alt = alt_create();
		}
	
	    }
	    ZR239 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

		if (sid_current_entry && sid_current_alt) {
			if (types_check_names(rule_result(sid_current_rule),
				alt_names(sid_current_alt))) {
				TypeTupleT used;

				types_copy(&used, rule_result(sid_current_rule));
				item_compute_minimal_dataflow(alt_item_head (sid_current_alt),
					&used);
				types_destroy(&used);
				rule_add_alt(sid_current_rule, sid_current_alt);
			} else {
				(void) alt_deallocate(sid_current_alt);
				E_alt_result_mismatch(entry_key (sid_external_rule),
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
			E_expected_alternative();
		}
	
	}
	{

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_END_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_SCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
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
ZR178(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    switch (CURRENT_TERMINAL) {
      case 4: case 18: case 19: case 24:
	{
	    ZR175 (sid_current_grammar, ZI133);
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
ZR250(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	NStringT ZI157;

	switch (CURRENT_TERMINAL) {
	  case 4:
	    {

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
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
		    ZR297 (sid_current_grammar, &ZI157);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		}
		break;
	      case 9: case 12: case 21:
		{
		    TypeTupleT ZI129;
		    TypeTupleT ZI130;

		    {

		types_init(&(ZI129));
	
		    }
		    {

		types_init(&(ZI130));
	
		    }
		    {

		sid_current_entry = scope_stack_add_rule(sid_current_scope,
			grammar_table(sid_current_grammar), &(ZI157), sid_enclosing_rule,
			&sid_redefining_entry);
		if (sid_current_entry) {
			sid_current_rule = entry_get_rule(sid_current_entry);
		} else {
			E_duplicate_rule((&ZI157));
			nstring_destroy(&(ZI157));
		}
	
		    }
		    ZR260 (sid_current_grammar, &ZI129, &ZI130);
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
			E_expected_other_defn();
		}
	
		}
		{

		nstring_destroy(&(ZI157));
	
		}
		{

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_END_SCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_END_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
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
ZR170(GrammarP sid_current_grammar, TypeTupleT *ZO133)
{
    TypeTupleT ZI133;

    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	{

		sid_current_pred_id = FALSE;
	
	}
	ZR192 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

		types_init(&(ZI133));
	
	}
	ZR178 (sid_current_grammar, &ZI133);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

		sid_propagating_error = FALSE;
	
	}
	ZR193 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (26);
    return;
  ZL0:;
    {

		ZO133->head = ZI133.head;

		if (ZO133->head == NULL) {
			ZO133->tail = &(ZO133->head);
		} else {
			ZO133->tail= ZI133.tail ;
		}
	    }
}

static void
ZR152(GrammarP sid_current_grammar)
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
			E_expected_arrow();
		}
	
	}
    }
}

static void
ZR153(GrammarP sid_current_grammar)
{
  ZL2_153:;
    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    ZR155 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_153;
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
ZR182(GrammarP sid_current_grammar, TypeTupleT *ZO133)
{
    TypeTupleT ZI133;

    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	{

		sid_current_pred_id = FALSE;
	
	}
	ZR192 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

		types_init(&(ZI133));
	
	}
	ZR190 (sid_current_grammar, &ZI133);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

		sid_propagating_error = FALSE;
	
	}
	ZR193 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (26);
    return;
  ZL0:;
    {

		ZO133->head = ZI133.head;

		if (ZO133->head == NULL) {
			ZO133->tail = &(ZO133->head);
		} else {
			ZO133->tail= ZI133.tail ;
		}
	    }
}

static void
ZR232(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 13:
	{
	    EntryP ZI163;
	    RuleP ZI70;
	    AltP ZI234;
	    BoolT ZI235;
	    ItemP ZI236;

	    ADVANCE_LEXER;
	    {

		(ZI163)      = sid_current_entry;
		(ZI70)       = sid_current_rule;
		(ZI234)        = sid_current_alt;
		(ZI235)   = sid_internal_rule;
		(ZI236)             = NULL;
		sid_internal_rule = TRUE;

		if (sid_current_entry && sid_current_alt) {
			sid_current_entry = table_add_generated_rule(grammar_table(sid_current_grammar), FALSE);
			sid_current_rule  = entry_get_rule(sid_current_entry);
			(ZI236)             = item_create(sid_current_entry);

			rule_defined(sid_current_rule);
			item_inlinable((ZI236));
			types_copy(item_param((ZI236)), rule_param((ZI70)));
			types_append_copy(item_param((ZI236)), alt_names((ZI234)));
			types_copy(rule_param(sid_current_rule), item_param((ZI236)));
			types_make_references(rule_param (sid_current_rule), item_param((ZI236)));
			alt_add_item((ZI234), (ZI236));
		} else {
			sid_current_entry = NULL;
		}
	
	    }
	    ZR230 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

		if ((ZI163) && (ZI234)) {
			rule_compute_result_intersect(sid_current_rule);
			types_copy (item_result((ZI236)), rule_result(sid_current_rule));
			types_add_new_names(alt_names((ZI234)), item_result((ZI236)),
			grammar_get_predicate_id(sid_current_grammar));
		}

		sid_internal_rule = (ZI235);
		sid_current_alt   = (ZI234);
		sid_current_rule  = (ZI70);
		sid_current_entry = (ZI163);
	
	    }
	    ZR237 (sid_current_grammar);
	    ZR245 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 4: case 6: case 10: case 18:
      case 19: case 24:
	{
	    ZR219 (sid_current_grammar);
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
ZR155(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	NStringT ZI157;

	switch (CURRENT_TERMINAL) {
	  case 4:
	    {

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

		if (table_add_type (grammar_table(sid_current_grammar), &(ZI157)) == NULL) {
			E_duplicate_type((&ZI157));
			nstring_destroy(&(ZI157));
		}
	
	}
	ZR245 (sid_current_grammar);
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
ZR190(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    switch (CURRENT_TERMINAL) {
      case 4: case 24:
	{
	    ZR187 (sid_current_grammar, ZI133);
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
ZR202(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 21:
	{
	    EntryP ZI163;
	    RuleP ZI70;

	    ADVANCE_LEXER;
	    {

		(ZI163) = sid_current_entry;
		(ZI70)  = sid_enclosing_rule;

		sid_enclosing_rule = sid_current_rule;
	
	    }
	    ZR168 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

		sid_current_entry  = (ZI163);
		sid_current_rule   = sid_enclosing_rule;
		sid_enclosing_rule = (ZI70);
		sid_alternative    = 0;
		sid_internal_rule  = FALSE;
		sid_external_rule  = sid_current_entry;

		nstring_init(&sid_maximum_scope);
	
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
			E_expected_end_scope();
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
ZR172(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    NStringT ZI157;

	    {

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
	    }
	    ADVANCE_LEXER;
	    {

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local (&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI157), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI157));

		if (name_entry) {
			if (sid_current_entry && sid_current_alt) {
				if (!types_contains(alt_names(sid_current_alt), name_entry) &&
					!types_contains(rule_param(sid_current_rule), name_entry)) {
						name_entry = NULL;
				}
			} else {
				name_entry = NULL;
			}
		}

		if (name_entry) {
			types_add_name_and_type((ZI133), name_entry, NULL, FALSE);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI157));
		} else if (non_local_entry) {
			types_add_name_and_type((ZI133), non_local_entry, NULL, FALSE);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI157));
		} else {
			types_add_name((ZI133), grammar_table(sid_current_grammar), &(ZI157), FALSE);
		}
	
	    }
	}
	break;
      case 19:
	{
	    ADVANCE_LEXER;
	    {

		EntryT *entry;

		entry = table_add_generated_name(grammar_table(sid_current_grammar));
		types_add_name_entry((ZI133), entry);
	
	    }
	}
	break;
      case 18:
	{
	    ADVANCE_LEXER;
	    {

		if (sid_current_pred_id) {
			E_multi_predicate_return();
		}
		sid_current_pred_id = TRUE;
		types_add_name_entry((ZI133), grammar_get_predicate_id(sid_current_grammar));
	
	    }
	}
	break;
      case 24:
	{
	    ADVANCE_LEXER;
	    {
		{
		    NStringT ZI157;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
			}
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    {

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI157), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI157));

		if (name_entry) {
			if (sid_current_entry && sid_current_alt) {
				if (!types_contains(alt_names(sid_current_alt), name_entry) &&
					!types_contains(rule_param(sid_current_rule), name_entry)) {
					name_entry = NULL;
				}
			} else {
				name_entry = NULL;
			}
		}

		if (name_entry) {
			types_add_name_and_type_var((ZI133), name_entry, NULL);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI157));
		} else if (non_local_entry) {
			types_add_name_and_type_var ((ZI133), non_local_entry, NULL);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy (&sid_maximum_scope);
				nstring_assign (&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI157));
		} else {
			E_undefined_assignment((&ZI157));
			types_add_name((ZI133), grammar_table(sid_current_grammar), &(ZI157), FALSE);
		}
	
		    }
		}
		goto ZL2;
	      ZL3:;
		{
		    {

		if (!sid_propagating_error) {
			E_expected_identifier();
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
			E_expected_lhs_name();
		}
	
	}
	{

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
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
	ZR265 (sid_current_grammar);
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

		(ZI0) = (CURRENT_TERMINAL == LEXER_TOK_EOF
			|| CURRENT_TERMINAL == LEXER_TOK_END_SCOPE
			|| CURRENT_TERMINAL == LEXER_TOK_BLT_ENTRY);
	
		}
		if (!ZI0)
		    goto ZL4;
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL4:;
	    switch (CURRENT_TERMINAL) {
	      case 4: case 10: case 19: case 20:
		{
		    goto ZL2_168;
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
			E_expected_production_defn();
		}
	
	}
	{

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_END_SCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_END_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
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

		(ZI0) = (CURRENT_TERMINAL == LEXER_TOK_EOF
			|| CURRENT_TERMINAL == LEXER_TOK_END_SCOPE
			|| CURRENT_TERMINAL == LEXER_TOK_BLT_ENTRY);
	
		}
		if (!ZI0)
		    goto ZL7;
	    }
	    goto ZL6;
	  ZL7:;
	    {
		goto ZL2_168;
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

		scope_stack_init(&sid_scope_stack);
		scope_stack_init(&sid_global_scope);
	
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
			E_expected_blt_types();
		}
	
		}
	    }
	  ZL2:;
	}
	ZR153 (sid_current_grammar);
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
			E_expected_blt_terminals();
		}
	
		}
	    }
	  ZL4:;
	}
	ZR159 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

		unsigned max_terminal = grammar_max_terminal(sid_current_grammar);

		bitvec_set_size(max_terminal);
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
			E_expected_blt_productions();
		}
	
		}
	    }
	  ZL6:;
	}
	ZR168 (sid_current_grammar);
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
			E_expected_blt_entry();
		}
	
		}
	    }
	  ZL8:;
	}
	ZR271 (sid_current_grammar);
	ZR245 (sid_current_grammar);
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
			E_expected_eof();
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
ZR146(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    switch (CURRENT_TERMINAL) {
      case 4: case 5:
	{
	    ZR143 (sid_current_grammar, ZI133);
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
ZR297(GrammarP sid_current_grammar, NStringT *ZI157)
{
    switch (CURRENT_TERMINAL) {
      case 6:
	{
	    TypeTupleT ZI129;
	    TypeTupleT ZI130;

	    ZR148 (sid_current_grammar, &ZI129);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

		sid_saved_pred_id = sid_current_pred_id;
	
	    }
	    ZR152 (sid_current_grammar);
	    ZR148 (sid_current_grammar, &ZI130);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

		sid_current_entry = scope_stack_add_rule(sid_current_scope,
			grammar_table(sid_current_grammar), &(*ZI157), sid_enclosing_rule,
			&sid_redefining_entry);
		if (sid_current_entry) {
			sid_current_rule = entry_get_rule(sid_current_entry);
		} else {
			E_duplicate_rule((ZI157));
			nstring_destroy(&(*ZI157));
		}
	
	    }
	    ZR260 (sid_current_grammar, &ZI129, &ZI130);
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
		    NStringT ZI139;
		    NonLocalEntryP ZI254;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

		nstring_assign(&ZI139, lexer_string_value(sid_current_stream));
	
			}
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    {

		(ZI254) = NULL;
		if (sid_enclosing_rule == NULL || sid_current_scope == &sid_global_scope) {
			E_global_scope_non_local((ZI157));
			nstring_destroy(&(*ZI157));
		} else {
			EntryT *type;

			type = table_get_type(grammar_table(sid_current_grammar), (&ZI139));
			if (type == NULL) {
				E_unknown_type((&ZI139));
				nstring_destroy(&(*ZI157));
			} else {
				EntryT *name;

				name = scope_stack_add_non_local (sid_current_scope,
					grammar_table(sid_current_grammar), &(*ZI157), type,
					sid_enclosing_rule);
				if (name) {
					NonLocalListT *non_locals;

					non_locals = rule_non_locals(sid_enclosing_rule);
					(ZI254) = non_local_list_add(non_locals, name, type);
				} else {
					E_duplicate_non_local((ZI157));
					nstring_destroy(&(*ZI157));
				}
			}
		}
		nstring_destroy(&(ZI139));
	
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
			E_expected_begin_action();
		}
	
					}
				    }
				  ZL6:;
				}
				{
				    {
					NStringT ZI51;

					switch (CURRENT_TERMINAL) {
					  case 4:
					    {

		nstring_assign(&ZI51, lexer_string_value(sid_current_stream));
	
					    }
					    break;
					  default:
					    goto ZL9;
					}
					ADVANCE_LEXER;
					{

		EntryT *actionentry;

		actionentry = scope_stack_get_action(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI51));

		if (actionentry == NULL) {
			E_unknown_action ((&ZI51));
		} else if ((ZI254)) {
			EntryT     *type   = non_local_entry_get_type((ZI254));
			KeyT       *name   = entry_key(non_local_entry_get_name((ZI254)));
			ActionT    *action = entry_get_action(actionentry);
			TypeTupleT *param  = action_param(action);
			TypeTupleT *result = action_result(action);
			TypeTupleT  tuple;
			TypeTupleT  ref_tuple;

			if (action_get_ignored(action)) {
				E_ignored_action_call(key_get_string(entry_key(actionentry)));
			}

			types_init(&tuple);
			types_init(&ref_tuple);
			types_add_type_entry(&tuple, type, FALSE);
			types_add_type_entry(&ref_tuple, type, TRUE);

			if (!types_equal(param, &tuple) && !types_equal(param, &ref_tuple)
				&& !types_equal_zero_tuple(param)) {
				E_initialiser_param_mismatch(name, &tuple, &ref_tuple, param);
			}

			if (!types_equal(result, &tuple)) {
				E_initialiser_result_mismatch(name, &tuple, result);
			}

			types_destroy(&ref_tuple);
			types_destroy(&tuple);
			non_local_entry_set_initialiser((ZI254), actionentry);
		}
		nstring_destroy(&(ZI51));
	
					}
					ZR229 (sid_current_grammar);
					ZR245 (sid_current_grammar);
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
			E_expected_identifier();
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
			E_expected_terminator_or_define();
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
			E_expected_identifier();
		}
	
		    }
		    {

		nstring_destroy(&(*ZI157));
	
		    }
		    {

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_END_SCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_END_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
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
ZR299(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 19:
	{
	    TypeTupleT ZI205;

	    ADVANCE_LEXER;
	    {

		types_init(&(ZI205));
	
	    }
	    {

		EntryT *entry;

		entry = table_add_generated_name(grammar_table(sid_current_grammar));
		types_add_name_entry((&ZI205), entry);
	
	    }
	    {

		sid_saved_pred_id = sid_current_pred_id;
	
	    }
	    ZR225 (sid_current_grammar);
	    ZR210 (sid_current_grammar, &ZI205);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 18:
	{
	    TypeTupleT ZI205;

	    ADVANCE_LEXER;
	    {

		types_init(&(ZI205));
	
	    }
	    {

		if (sid_current_pred_id) {
			E_multi_predicate_return();
		}
		sid_current_pred_id = TRUE;
		types_add_name_entry((&ZI205), grammar_get_predicate_id(sid_current_grammar));
	
	    }
	    {

		sid_saved_pred_id = sid_current_pred_id;
	
	    }
	    ZR225 (sid_current_grammar);
	    ZR210 (sid_current_grammar, &ZI205);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 10:
	{
	    TypeTupleT ZI205;

	    {

		sid_saved_pred_id = sid_current_pred_id;
	
	    }
	    {

		types_init(&(ZI205));
	
	    }
	    ADVANCE_LEXER;
	    ZR228 (sid_current_grammar, &ZI205);
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
ZR300(GrammarP sid_current_grammar, NStringT *ZI157)
{
    switch (CURRENT_TERMINAL) {
      case 12:
	{
	    TypeTupleT ZI205;

	    {

		types_init(&(ZI205));
	
	    }
	    {

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local (&sid_scope_stack,
			grammar_table(sid_current_grammar), (ZI157), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (ZI157));

		if (name_entry) {
			if (sid_current_entry && sid_current_alt) {
				if (!types_contains(alt_names(sid_current_alt), name_entry) &&
					!types_contains(rule_param(sid_current_rule), name_entry)) {
						name_entry = NULL;
				}
			} else {
				name_entry = NULL;
			}
		}

		if (name_entry) {
			types_add_name_and_type((&ZI205), name_entry, NULL, FALSE);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(*ZI157));
		} else if (non_local_entry) {
			types_add_name_and_type((&ZI205), non_local_entry, NULL, FALSE);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(*ZI157));
		} else {
			types_add_name((&ZI205), grammar_table(sid_current_grammar), &(*ZI157), FALSE);
		}
	
	    }
	    {

		sid_saved_pred_id = sid_current_pred_id;
	
	    }
	    ADVANCE_LEXER;
	    ZR210 (sid_current_grammar, &ZI205);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 6: case 9:
	{
	    {

		sid_saved_pred_id = sid_current_pred_id;
	
	    }
	    ZR301 (sid_current_grammar, ZI157);
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
ZR301(GrammarP sid_current_grammar, NStringT *ZI157)
{
    switch (CURRENT_TERMINAL) {
      case 9:
	{
	    TypeTupleT ZI205;
	    TypeTupleT ZI208;

	    {

		sid_current_pred_id = FALSE;
	
	    }
	    {

		types_init(&(ZI205));
	
	    }
	    {

		types_init(&(ZI208));
	
	    }
	    {

		TypeTupleT *param  = NULL;
		TypeTupleT *result = NULL;
		EntryT     *entry  = NULL;
		RuleT      *rule;
		BasicT     *basic;

		if (sid_current_entry && sid_current_alt) {
			entry = scope_stack_get_rule(&sid_scope_stack,
				grammar_table(sid_current_grammar), (ZI157));
			if (entry) {
				sid_current_item = item_create(entry);
				rule             = entry_get_rule(entry);
				param            = rule_param(rule);
				result           = rule_result(rule);
			} else {
				entry = table_get_basic(grammar_table(sid_current_grammar), (ZI157));
				if (entry) {
					sid_current_item = item_create(entry);
					basic            = entry_get_basic(entry);
					param            = NULL;
					result           = basic_result(basic);

					if (basic_get_ignored(basic)) {
						E_ignored_basic_call((ZI157));
					}
				} else {
					E_unknown_rule_or_basic((ZI157));
					sid_current_item = NULL;
				}
			}
		} else {
			sid_current_item = NULL;
		}

		nstring_destroy(&(*ZI157));
		if (sid_current_item) {
			BoolT  errored = FALSE;
			KeyT  *key     = entry_key (entry);

			if (types_resolve((&ZI208), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (param) {
					if (types_equal((&ZI208), param)) {
						item_add_param(sid_current_item, (&ZI208));
					} else {
						E_rule_param_call_mismatch(key, param, (&ZI208));
						types_destroy((&ZI208));
						errored = TRUE;
					}
				} else {
					if (!types_equal_zero_tuple((&ZI208))) {
						E_basic_param_call_mismatch(key, (&ZI208));
						types_destroy((&ZI208));
						errored = TRUE;
					}
				}
			} else {
				types_destroy((&ZI208));
				errored = TRUE;
			}

			if (types_disjoint_names ((&ZI205))) {
				if (types_check_undefined ((&ZI205), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((&ZI205), result)) {
						types_add_new_names(alt_names (sid_current_alt),
							(&ZI205), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							E_predicate ();
						}
						item_add_result(sid_current_item, (&ZI205));
					} else {
						if (param) {
							E_rule_result_call_mismatch(key, result, (&ZI205));
						} else {
							E_basic_result_call_mismatch(key, result, (&ZI205));
						}
						types_destroy((&ZI205));
						errored = TRUE;
					}
				} else {
					types_destroy((&ZI205));
					errored = TRUE;
				}
			} else {
				if (param) {
					E_rule_result_call_clash (key, (&ZI205));
				} else {
					E_basic_result_call_clash (key, (&ZI205));
				}

				types_destroy ((&ZI205));
				errored = TRUE;
			}

			if (errored) {
				(void) item_deallocate(sid_current_item);
				sid_current_item = NULL;
				(void) alt_deallocate(sid_current_alt);
				sid_current_alt  = NULL;
			} else {
				alt_add_item(sid_current_alt, sid_current_item);
			}
		} else {
			if (sid_current_alt) {
				(void) alt_deallocate (sid_current_alt);
				sid_current_alt = NULL;
			}
			types_destroy ((&ZI205));
			types_destroy ((&ZI208));
		}
	
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 6:
	{
	    TypeTupleT ZI205;
	    TypeTupleT ZI208;

	    {

		types_init(&(ZI205));
	
	    }
	    ZR182 (sid_current_grammar, &ZI208);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

		TypeTupleT *param  = NULL;
		TypeTupleT *result = NULL;
		EntryT     *entry  = NULL;
		RuleT      *rule;
		BasicT     *basic;

		if (sid_current_entry && sid_current_alt) {
			entry = scope_stack_get_rule(&sid_scope_stack,
				grammar_table(sid_current_grammar), (ZI157));
			if (entry) {
				sid_current_item = item_create(entry);
				rule             = entry_get_rule(entry);
				param            = rule_param(rule);
				result           = rule_result(rule);
			} else {
				entry = table_get_basic(grammar_table(sid_current_grammar), (ZI157));
				if (entry) {
					sid_current_item = item_create(entry);
					basic            = entry_get_basic(entry);
					param            = NULL;
					result           = basic_result(basic);

					if (basic_get_ignored(basic)) {
						E_ignored_basic_call((ZI157));
					}
				} else {
					E_unknown_rule_or_basic((ZI157));
					sid_current_item = NULL;
				}
			}
		} else {
			sid_current_item = NULL;
		}

		nstring_destroy(&(*ZI157));
		if (sid_current_item) {
			BoolT  errored = FALSE;
			KeyT  *key     = entry_key (entry);

			if (types_resolve((&ZI208), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (param) {
					if (types_equal((&ZI208), param)) {
						item_add_param(sid_current_item, (&ZI208));
					} else {
						E_rule_param_call_mismatch(key, param, (&ZI208));
						types_destroy((&ZI208));
						errored = TRUE;
					}
				} else {
					if (!types_equal_zero_tuple((&ZI208))) {
						E_basic_param_call_mismatch(key, (&ZI208));
						types_destroy((&ZI208));
						errored = TRUE;
					}
				}
			} else {
				types_destroy((&ZI208));
				errored = TRUE;
			}

			if (types_disjoint_names ((&ZI205))) {
				if (types_check_undefined ((&ZI205), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((&ZI205), result)) {
						types_add_new_names(alt_names (sid_current_alt),
							(&ZI205), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							E_predicate ();
						}
						item_add_result(sid_current_item, (&ZI205));
					} else {
						if (param) {
							E_rule_result_call_mismatch(key, result, (&ZI205));
						} else {
							E_basic_result_call_mismatch(key, result, (&ZI205));
						}
						types_destroy((&ZI205));
						errored = TRUE;
					}
				} else {
					types_destroy((&ZI205));
					errored = TRUE;
				}
			} else {
				if (param) {
					E_rule_result_call_clash (key, (&ZI205));
				} else {
					E_basic_result_call_clash (key, (&ZI205));
				}

				types_destroy ((&ZI205));
				errored = TRUE;
			}

			if (errored) {
				(void) item_deallocate(sid_current_item);
				sid_current_item = NULL;
				(void) alt_deallocate(sid_current_alt);
				sid_current_alt  = NULL;
			} else {
				alt_add_item(sid_current_alt, sid_current_item);
			}
		} else {
			if (sid_current_alt) {
				(void) alt_deallocate (sid_current_alt);
				sid_current_alt = NULL;
			}
			types_destroy ((&ZI205));
			types_destroy ((&ZI208));
		}
	
	    }
	    ZR245 (sid_current_grammar);
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
ZR148(GrammarP sid_current_grammar, TypeTupleT *ZO133)
{
    TypeTupleT ZI133;

    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	{

		types_init(&(ZI133));
	
	}
	ZR192 (sid_current_grammar);
	ZR146 (sid_current_grammar, &ZI133);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

		sid_propagating_error = FALSE;
	
	}
	ZR193 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == 26) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (26);
    return;
  ZL0:;
    {

		ZO133->head = ZI133.head;

		if (ZO133->head == NULL) {
			ZO133->tail = &(ZO133->head);
		} else {
			ZO133->tail= ZI133.tail ;
		}
	    }
}

static void
ZR184(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    NStringT ZI157;

	    {

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
	    }
	    ADVANCE_LEXER;
	    {

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local (&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI157), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI157));

		if (name_entry) {
			if (sid_current_entry && sid_current_alt) {
				if (!types_contains(alt_names(sid_current_alt), name_entry) &&
					!types_contains(rule_param(sid_current_rule), name_entry)) {
						name_entry = NULL;
				}
			} else {
				name_entry = NULL;
			}
		}

		if (name_entry) {
			types_add_name_and_type((ZI133), name_entry, NULL, FALSE);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI157));
		} else if (non_local_entry) {
			types_add_name_and_type((ZI133), non_local_entry, NULL, FALSE);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI157));
		} else {
			types_add_name((ZI133), grammar_table(sid_current_grammar), &(ZI157), FALSE);
		}
	
	    }
	}
	break;
      case 24:
	{
	    ADVANCE_LEXER;
	    {
		{
		    NStringT ZI157;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
			}
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    {

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI157), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI157));

		if (name_entry) {
			if (sid_current_entry && sid_current_alt) {
				if (!types_contains(alt_names(sid_current_alt), name_entry) &&
					!types_contains(rule_param(sid_current_rule), name_entry)) {
						name_entry = NULL;
				}
			} else {
				name_entry = NULL;
			}
		}

		if (name_entry) {
			types_add_name_and_type ((ZI133), name_entry, NULL, TRUE);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI157));
		} else if (non_local_entry) {
			types_add_name_and_type ((ZI133), non_local_entry, NULL, TRUE);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI157));
		} else {
			types_add_name((ZI133), grammar_table(sid_current_grammar), &(ZI157), TRUE);
		}
	
		    }
		}
		goto ZL2;
	      ZL3:;
		{
		    {

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
		    }
		    {

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
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
			E_expected_rhs_name();
		}
	
	}
	{

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
	}
    }
}

static void
ZR210(GrammarP sid_current_grammar, TypeTupleT *ZI205)
{
    switch (CURRENT_TERMINAL) {
      case 10:
	{
	    ADVANCE_LEXER;
	    ZR228 (sid_current_grammar, ZI205);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 4:
	{
	    NStringT ZI157;

	    {

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
	    }
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 6:
		    {
			TypeTupleT ZI208;

			ZR182 (sid_current_grammar, &ZI208);
			if ((CURRENT_TERMINAL) == 26) {
			    RESTORE_LEXER;
			    goto ZL3;
			}
			{

		TypeTupleT *param  = NULL;
		TypeTupleT *result = NULL;
		EntryT     *entry  = NULL;
		RuleT      *rule;
		BasicT     *basic;

		if (sid_current_entry && sid_current_alt) {
			entry = scope_stack_get_rule(&sid_scope_stack,
				grammar_table(sid_current_grammar), (&ZI157));
			if (entry) {
				sid_current_item = item_create(entry);
				rule             = entry_get_rule(entry);
				param            = rule_param(rule);
				result           = rule_result(rule);
			} else {
				entry = table_get_basic(grammar_table(sid_current_grammar), (&ZI157));
				if (entry) {
					sid_current_item = item_create(entry);
					basic            = entry_get_basic(entry);
					param            = NULL;
					result           = basic_result(basic);

					if (basic_get_ignored(basic)) {
						E_ignored_basic_call((&ZI157));
					}
				} else {
					E_unknown_rule_or_basic((&ZI157));
					sid_current_item = NULL;
				}
			}
		} else {
			sid_current_item = NULL;
		}

		nstring_destroy(&(ZI157));
		if (sid_current_item) {
			BoolT  errored = FALSE;
			KeyT  *key     = entry_key (entry);

			if (types_resolve((&ZI208), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (param) {
					if (types_equal((&ZI208), param)) {
						item_add_param(sid_current_item, (&ZI208));
					} else {
						E_rule_param_call_mismatch(key, param, (&ZI208));
						types_destroy((&ZI208));
						errored = TRUE;
					}
				} else {
					if (!types_equal_zero_tuple((&ZI208))) {
						E_basic_param_call_mismatch(key, (&ZI208));
						types_destroy((&ZI208));
						errored = TRUE;
					}
				}
			} else {
				types_destroy((&ZI208));
				errored = TRUE;
			}

			if (types_disjoint_names ((ZI205))) {
				if (types_check_undefined ((ZI205), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((ZI205), result)) {
						types_add_new_names(alt_names (sid_current_alt),
							(ZI205), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							E_predicate ();
						}
						item_add_result(sid_current_item, (ZI205));
					} else {
						if (param) {
							E_rule_result_call_mismatch(key, result, (ZI205));
						} else {
							E_basic_result_call_mismatch(key, result, (ZI205));
						}
						types_destroy((ZI205));
						errored = TRUE;
					}
				} else {
					types_destroy((ZI205));
					errored = TRUE;
				}
			} else {
				if (param) {
					E_rule_result_call_clash (key, (ZI205));
				} else {
					E_basic_result_call_clash (key, (ZI205));
				}

				types_destroy ((ZI205));
				errored = TRUE;
			}

			if (errored) {
				(void) item_deallocate(sid_current_item);
				sid_current_item = NULL;
				(void) alt_deallocate(sid_current_alt);
				sid_current_alt  = NULL;
			} else {
				alt_add_item(sid_current_alt, sid_current_item);
			}
		} else {
			if (sid_current_alt) {
				(void) alt_deallocate (sid_current_alt);
				sid_current_alt = NULL;
			}
			types_destroy ((ZI205));
			types_destroy ((&ZI208));
		}
	
			}
			ZR245 (sid_current_grammar);
			if ((CURRENT_TERMINAL) == 26) {
			    RESTORE_LEXER;
			    goto ZL3;
			}
		    }
		    break;
		  case 9:
		    {
			{

		sid_current_pred_id = FALSE;
	
			}
			{

		EntryT     *name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI157));
		EntryT     *entry      = NULL;
		TypeTupleT *param      = NULL;
		TypeTupleT *result     = NULL;
		RuleT      *rule;
		BasicT     *basic;
		TypeTupleT  rhs;

		types_init(&rhs);

		if (sid_current_entry && sid_current_alt) {
			if (name_entry != NULL &&
				!types_contains(alt_names (sid_current_alt), name_entry) &&
				!types_contains(rule_param (sid_current_rule), name_entry)) {
				name_entry = NULL;
			}

			entry = scope_stack_get_rule(&sid_scope_stack, grammar_table(sid_current_grammar),
				(&ZI157));
			if (entry) {
				sid_current_item = item_create (entry);
				rule             = entry_get_rule (entry);
				param            = rule_param (rule);
				result           = rule_result (rule);
			} else {
				entry = table_get_basic(grammar_table(sid_current_grammar), (&ZI157));
				if (entry) {
					sid_current_item = item_create (entry);
					basic            = entry_get_basic (entry);
					param            = NULL;
					result           = basic_result (basic);
					if (name_entry == NULL && basic_get_ignored(basic)) {
						E_ignored_basic_call ((&ZI157));
					}
				}
			}

			if (entry == NULL && name_entry == NULL) {
				NStringT scope;

				name_entry = scope_stack_get_non_local (&sid_scope_stack,
					grammar_table(sid_current_grammar), (&ZI157), &scope);
				if (name_entry) {
					if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
						nstring_destroy(&sid_maximum_scope);
						nstring_assign(&sid_maximum_scope, &scope);
					} else {
						nstring_destroy(&scope);
					}
				} else {
					E_unknown_rule_or_basic((&ZI157));
				}
			} else if (entry != NULL && name_entry != NULL) {
				E_ambiguous_call((&ZI157));
				entry      = NULL;
				name_entry = NULL;
			}
		} else {
			name_entry = NULL;
		}
		nstring_destroy(&(ZI157));

		if (entry) {
			BoolT  errored = FALSE;
			KeyT  *key     = entry_key(entry);

			if (types_resolve(&rhs, rule_param (sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (param) {
					if (types_equal(&rhs, param)) {
						item_add_param(sid_current_item, &rhs);
					} else {
						E_rule_param_call_mismatch(key, param, &rhs);
						types_destroy (&rhs);
						errored = TRUE;
					}
				} else {
					if (!types_equal_zero_tuple(&rhs)) {
						E_basic_param_call_mismatch(key, &rhs);
						types_destroy(&rhs);
						errored = TRUE;
					}
				}
			} else {
				types_destroy(&rhs);
				errored = TRUE;
			}

			if (types_disjoint_names((ZI205))) {
				if (types_check_undefined((ZI205), rule_param (sid_current_rule),
					alt_names (sid_current_alt), E_redefined_name,
					entry_key (sid_external_rule), sid_alternative)) {
					if (types_fillin_types((ZI205), result)) {
						types_add_new_names(alt_names (sid_current_alt),
							(ZI205), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							E_predicate();
						}
						item_add_result(sid_current_item, (ZI205));
					} else {
						if (param) {
							E_rule_result_call_mismatch(key, result, (ZI205));
						} else {
							E_basic_result_call_mismatch (key, result, (ZI205));
						}
						types_destroy((ZI205));
						errored = TRUE;
					}
				} else {
					types_destroy((ZI205));
					errored = TRUE;
				}
			} else {
				if (param) {
					E_rule_result_call_clash(key, (ZI205));
				} else {
					E_basic_result_call_clash(key, (ZI205));
				}
				types_destroy((ZI205));
				errored = TRUE;
			}

			if (errored) {
				(void) item_deallocate(sid_current_item);
				sid_current_item = NULL;
				(void) alt_deallocate(sid_current_alt);
				sid_current_alt  = NULL;
			} else {
				alt_add_item(sid_current_alt, sid_current_item);
			}
		} else if (name_entry) {
			types_add_name_entry(&rhs, name_entry);
			entry = table_add_rename (grammar_table(sid_current_grammar));
			if (types_resolve (&rhs, rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_contains_references(&rhs)) {
					E_identity_param_has_refs(&rhs, entry_key(sid_external_rule),
						sid_alternative);
					types_destroy(&rhs);
					sid_current_item = NULL;
				} else {
					sid_current_item = item_create(entry);
					item_add_param(sid_current_item, &rhs);
				}
			} else {
				types_destroy(&rhs);
				sid_current_item = NULL;
			}

			if (types_disjoint_names((ZI205))) {
				if (types_check_undefined((ZI205), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (sid_current_item) {
						if (types_fillin_types((ZI205), item_param(sid_current_item))) {
							types_add_new_names(alt_names (sid_current_alt),
								(ZI205), grammar_get_predicate_id(sid_current_grammar));
							if (sid_saved_pred_id) {
								E_predicate();
							}
							item_add_result(sid_current_item, (ZI205));
							alt_add_item(sid_current_alt, sid_current_item);
						} else {
							E_identity_mismatch(item_param(sid_current_item), (ZI205));
							types_destroy((ZI205));
							(void) item_deallocate(sid_current_item);
							sid_current_item = NULL;
						}
					}
				} else {
					types_destroy((ZI205));
					if (sid_current_item) {
						(void) item_deallocate(sid_current_item);
						sid_current_item = NULL;
					}
				}
			} else {
				E_identity_result_clash((ZI205));
				types_destroy((ZI205));
				if (sid_current_item) {
					(void) item_deallocate(sid_current_item);
					sid_current_item = NULL;
				}
			}

			if (sid_current_item == NULL) {
				(void) alt_deallocate(sid_current_alt);
				sid_current_alt = NULL;
			}
		} else {
			if (sid_current_alt) {
				(void) alt_deallocate(sid_current_alt);
				sid_current_alt = NULL;
			}
			types_destroy((ZI205));
			types_destroy(&rhs);
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
			E_expected_tuple_or_term();
		}
	
		    }
		    {

		nstring_destroy(&(ZI157));
	
		    }
		    {

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_SCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
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
	    TypeTupleT ZI208;

	    ZR182 (sid_current_grammar, &ZI208);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

		if (sid_current_entry && sid_current_alt) {
			EntryT *entry = table_add_rename(grammar_table(sid_current_grammar));

			if (types_resolve((&ZI208), rule_param (sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_contains_references((&ZI208))) {
					E_identity_param_has_refs ((&ZI208), entry_key(sid_external_rule),
						sid_alternative);
					types_destroy ((&ZI208));
					sid_current_item = NULL;
				} else {
					sid_current_item = item_create(entry);
					item_add_param(sid_current_item, (&ZI208));
				}
			} else {
				types_destroy((&ZI208));
				sid_current_item = NULL;
			}

			if (types_disjoint_names((ZI205))) {
				if (types_check_undefined((ZI205), rule_param (sid_current_rule),
					alt_names (sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (sid_current_item) {
						if (types_fillin_types((ZI205), item_param(sid_current_item))) {
							types_add_new_names(alt_names (sid_current_alt),
							(ZI205), grammar_get_predicate_id(sid_current_grammar));
							if (sid_saved_pred_id) {
								E_predicate();
							}
							item_add_result(sid_current_item, (ZI205));
							alt_add_item(sid_current_alt, sid_current_item);
						} else {
							E_identity_mismatch(item_param (sid_current_item), (ZI205));
							types_destroy((ZI205));
							(void) item_deallocate(sid_current_item);
							sid_current_item = NULL;
						}
					}
				} else {
					types_destroy((ZI205));
					if (sid_current_item) {
						(void) item_deallocate(sid_current_item);
						sid_current_item = NULL;
					}
				}
			} else {
				E_identity_result_clash((ZI205));
				types_destroy ((ZI205));
				if (sid_current_item) {
					(void) item_deallocate(sid_current_item);
					sid_current_item = NULL;
				}
			}

			if (sid_current_item == NULL) {
				(void) alt_deallocate(sid_current_alt);
				sid_current_alt = NULL;
			}
		} else {
			types_destroy((ZI205));
			types_destroy((&ZI208));
		}
	
	    }
	    ZR245 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 24:
	{
	    TypeTupleT ZI208;

	    {

		sid_current_pred_id = FALSE;
	
	    }
	    ADVANCE_LEXER;
	    {

		types_init(&(ZI208));
	
	    }
	    {
		{
		    NStringT ZI157;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
			}
			break;
		      default:
			goto ZL5;
		    }
		    ADVANCE_LEXER;
		    {

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI157), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI157));

		if (name_entry) {
			if (sid_current_entry && sid_current_alt) {
				if (!types_contains(alt_names(sid_current_alt), name_entry) &&
					!types_contains(rule_param(sid_current_rule), name_entry)) {
						name_entry = NULL;
				}
			} else {
				name_entry = NULL;
			}
		}

		if (name_entry) {
			types_add_name_and_type ((&ZI208), name_entry, NULL, TRUE);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI157));
		} else if (non_local_entry) {
			types_add_name_and_type ((&ZI208), non_local_entry, NULL, TRUE);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI157));
		} else {
			types_add_name((&ZI208), grammar_table(sid_current_grammar), &(ZI157), TRUE);
		}
	
		    }
		    {

		if (sid_current_entry && sid_current_alt) {
			EntryT *entry = table_add_rename(grammar_table(sid_current_grammar));

			if (types_resolve((&ZI208), rule_param (sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_contains_references((&ZI208))) {
					E_identity_param_has_refs ((&ZI208), entry_key(sid_external_rule),
						sid_alternative);
					types_destroy ((&ZI208));
					sid_current_item = NULL;
				} else {
					sid_current_item = item_create(entry);
					item_add_param(sid_current_item, (&ZI208));
				}
			} else {
				types_destroy((&ZI208));
				sid_current_item = NULL;
			}

			if (types_disjoint_names((ZI205))) {
				if (types_check_undefined((ZI205), rule_param (sid_current_rule),
					alt_names (sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (sid_current_item) {
						if (types_fillin_types((ZI205), item_param(sid_current_item))) {
							types_add_new_names(alt_names (sid_current_alt),
							(ZI205), grammar_get_predicate_id(sid_current_grammar));
							if (sid_saved_pred_id) {
								E_predicate();
							}
							item_add_result(sid_current_item, (ZI205));
							alt_add_item(sid_current_alt, sid_current_item);
						} else {
							E_identity_mismatch(item_param (sid_current_item), (ZI205));
							types_destroy((ZI205));
							(void) item_deallocate(sid_current_item);
							sid_current_item = NULL;
						}
					}
				} else {
					types_destroy((ZI205));
					if (sid_current_item) {
						(void) item_deallocate(sid_current_item);
						sid_current_item = NULL;
					}
				}
			} else {
				E_identity_result_clash((ZI205));
				types_destroy ((ZI205));
				if (sid_current_item) {
					(void) item_deallocate(sid_current_item);
					sid_current_item = NULL;
				}
			}

			if (sid_current_item == NULL) {
				(void) alt_deallocate(sid_current_alt);
				sid_current_alt = NULL;
			}
		} else {
			types_destroy((ZI205));
			types_destroy((&ZI208));
		}
	
		    }
		    ZR245 (sid_current_grammar);
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
			E_expected_identifier();
		}
	
		    }
		    {

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_SCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
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
			E_expected_item_rhs();
		}
	
	}
	{

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_SCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
	}
    }
}

static void
ZR230(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	ZR246 (sid_current_grammar);
	{
	    switch (CURRENT_TERMINAL) {
	      case 16:
		{
		    ADVANCE_LEXER;
		    ZR241 (sid_current_grammar);
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
ZR159(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
  ZL2_159:;
    {
	ZR161 (sid_current_grammar);
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
		    goto ZL2_159;
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
ZR206(GrammarP sid_current_grammar, TypeTupleT *ZI205)
{
    switch (CURRENT_TERMINAL) {
      case 6:
	{
	    TypeTupleT ZI208;

	    ZR182 (sid_current_grammar, &ZI208);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

		if (sid_current_item) {
			BoolT    errored = FALSE;
			EntryT  *entry   = item_entry(sid_current_item);
			ActionT *action  = entry_get_action(entry);

			if (action_get_ignored(action)) {
				E_ignored_action_call(key_get_string(entry_key(entry)));
			}

			if (types_resolve((&ZI208), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_equal((&ZI208), action_param(action))) {
					item_add_param(sid_current_item, (&ZI208));
				} else {
					E_action_param_call_mismatch(entry_key (entry),
							  action_param(action), (&ZI208));
					types_destroy ((&ZI208));
					errored = TRUE;
				}
			} else {
				types_destroy((&ZI208));
				errored = TRUE;
			}

			if (types_disjoint_names((ZI205))) {
				if (types_check_undefined((ZI205), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((ZI205), action_result(action))) {
						types_add_new_names(alt_names(sid_current_alt),
							(ZI205), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							BoolT   reference;
							EntryT *type;

							type = types_find_name_type((ZI205),
								grammar_get_predicate_id(sid_current_grammar), &reference);
							assert(type != NULL && !reference);
							if (grammar_get_predicate_type(sid_current_grammar)) {
								if (type != grammar_get_predicate_type(sid_current_grammar)) {
									E_predicate_type(grammar_get_predicate_type(sid_current_grammar), type);
								}
							} else {
								grammar_set_predicate_type(sid_current_grammar, type);
							}
							item_to_predicate(sid_current_item);
						}
						item_add_result(sid_current_item, (ZI205));
					} else {
						E_action_result_call_mismatch(entry_key (entry),
							action_result(action), (ZI205));
						types_destroy((ZI205));
						errored = TRUE;
					}
				} else {
					types_destroy((ZI205));
					errored = TRUE;
				}
			} else {
				E_action_result_call_clash(entry_key (entry), (ZI205));
				types_destroy((ZI205));
				errored = TRUE;
			}

			if (errored) {
				(void) item_deallocate(sid_current_item);
				sid_current_item = NULL;
				(void) alt_deallocate(sid_current_alt);
				sid_current_alt  = NULL;
			} else {
				alt_add_item(sid_current_alt, sid_current_item);
			}
		} else {
			types_destroy((ZI205));
			types_destroy((&ZI208));
		}
	
	    }
	    ZR245 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 9:
	{
	    TypeTupleT ZI208;

	    {

		sid_current_pred_id = FALSE;
	
	    }
	    {

		types_init(&(ZI208));
	
	    }
	    {

		if (sid_current_item) {
			BoolT    errored = FALSE;
			EntryT  *entry   = item_entry(sid_current_item);
			ActionT *action  = entry_get_action(entry);

			if (action_get_ignored(action)) {
				E_ignored_action_call(key_get_string(entry_key(entry)));
			}

			if (types_resolve((&ZI208), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_equal((&ZI208), action_param(action))) {
					item_add_param(sid_current_item, (&ZI208));
				} else {
					E_action_param_call_mismatch(entry_key (entry),
							  action_param(action), (&ZI208));
					types_destroy ((&ZI208));
					errored = TRUE;
				}
			} else {
				types_destroy((&ZI208));
				errored = TRUE;
			}

			if (types_disjoint_names((ZI205))) {
				if (types_check_undefined((ZI205), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((ZI205), action_result(action))) {
						types_add_new_names(alt_names(sid_current_alt),
							(ZI205), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							BoolT   reference;
							EntryT *type;

							type = types_find_name_type((ZI205),
								grammar_get_predicate_id(sid_current_grammar), &reference);
							assert(type != NULL && !reference);
							if (grammar_get_predicate_type(sid_current_grammar)) {
								if (type != grammar_get_predicate_type(sid_current_grammar)) {
									E_predicate_type(grammar_get_predicate_type(sid_current_grammar), type);
								}
							} else {
								grammar_set_predicate_type(sid_current_grammar, type);
							}
							item_to_predicate(sid_current_item);
						}
						item_add_result(sid_current_item, (ZI205));
					} else {
						E_action_result_call_mismatch(entry_key (entry),
							action_result(action), (ZI205));
						types_destroy((ZI205));
						errored = TRUE;
					}
				} else {
					types_destroy((ZI205));
					errored = TRUE;
				}
			} else {
				E_action_result_call_clash(entry_key (entry), (ZI205));
				types_destroy((ZI205));
				errored = TRUE;
			}

			if (errored) {
				(void) item_deallocate(sid_current_item);
				sid_current_item = NULL;
				(void) alt_deallocate(sid_current_alt);
				sid_current_alt  = NULL;
			} else {
				alt_add_item(sid_current_alt, sid_current_item);
			}
		} else {
			types_destroy((ZI205));
			types_destroy((&ZI208));
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
			E_expected_tuple_or_term();
		}
	
	}
	{

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_SCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
	}
    }
}

static void
ZR265(GrammarP sid_current_grammar)
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
	      case 10: case 19:
		{
		    ZR194 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 4:
		{
		    ZR250 (sid_current_grammar);
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
ZR134(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    NStringT ZI136;

	    {

		nstring_assign(&ZI136, lexer_string_value(sid_current_stream));
	
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
			E_expected_typemark();
		}
	
		    }
		}
	      ZL2:;
	    }
	    {
		{
		    NStringT ZI139;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

		nstring_assign(&ZI139, lexer_string_value(sid_current_stream));
	
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

		if (!types_add_typed_name((ZI133), grammar_table(sid_current_grammar),
			&(ZI136), (&ZI139), TRUE)) {
			E_unknown_type((&ZI139));
		}
		nstring_destroy(&(ZI139));
	
				}
			    }
			    break;
			  default:
			    {
				{

		if (!types_add_typed_name((ZI133), grammar_table(sid_current_grammar),
			&(ZI136), (&ZI139), FALSE)) {
			E_unknown_type((&ZI139));
		}
		nstring_destroy(&(ZI139));
	
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
			E_expected_identifier();
		}
	
		    }
		    {

		nstring_destroy(&(ZI136));
	
		    }
		    {

		if (sid_finished_terminals) {
			while (CURRENT_TERMINAL != LEXER_TOK_EOF
				&& CURRENT_TERMINAL != LEXER_TOK_DEFINE
				&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_SCOPE
				&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE
				&& CURRENT_TERMINAL != LEXER_TOK_SEPARATOR
				&& CURRENT_TERMINAL != LEXER_TOK_CLOSE_TUPLE
				&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
				if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
					nstring_destroy(lexer_string_value(sid_current_stream));
				}
				ADVANCE_LEXER;
			}

			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}

			if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
				ADVANCE_LEXER;
			}
		} else {
			while (CURRENT_TERMINAL != LEXER_TOK_EOF
				&& CURRENT_TERMINAL != LEXER_TOK_SEPARATOR
				&& CURRENT_TERMINAL != LEXER_TOK_CLOSE_TUPLE
				&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
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
		    NStringT ZI139;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

		nstring_assign(&ZI139, lexer_string_value(sid_current_stream));
	
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

		if (!types_add_type((ZI133), grammar_table(sid_current_grammar), (&ZI139), TRUE)) {
			E_unknown_type((&ZI139));
		}
		nstring_destroy(&(ZI139));
	
				}
			    }
			    break;
			  default:
			    {
				{

		if (!types_add_type((ZI133), grammar_table(sid_current_grammar), (&ZI139),
		FALSE)) {
			E_unknown_type((&ZI139));
		}
		nstring_destroy(&(ZI139));
	
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
			E_expected_identifier();
		}
	
		    }
		    {

		if (sid_finished_terminals) {
			while (CURRENT_TERMINAL != LEXER_TOK_EOF
				&& CURRENT_TERMINAL != LEXER_TOK_DEFINE
				&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_SCOPE
				&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE
				&& CURRENT_TERMINAL != LEXER_TOK_SEPARATOR
				&& CURRENT_TERMINAL != LEXER_TOK_CLOSE_TUPLE
				&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
				if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
					nstring_destroy(lexer_string_value(sid_current_stream));
				}
				ADVANCE_LEXER;
			}

			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}

			if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
				ADVANCE_LEXER;
			}
		} else {
			while (CURRENT_TERMINAL != LEXER_TOK_EOF
				&& CURRENT_TERMINAL != LEXER_TOK_SEPARATOR
				&& CURRENT_TERMINAL != LEXER_TOK_CLOSE_TUPLE
				&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
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
			E_expected_tuple_defn();
		}
	
	}
	{

		if (sid_finished_terminals) {
			while (CURRENT_TERMINAL != LEXER_TOK_EOF
				&& CURRENT_TERMINAL != LEXER_TOK_DEFINE
				&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_SCOPE
				&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE
				&& CURRENT_TERMINAL != LEXER_TOK_SEPARATOR
				&& CURRENT_TERMINAL != LEXER_TOK_CLOSE_TUPLE
				&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
				if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
					nstring_destroy(lexer_string_value(sid_current_stream));
				}
				ADVANCE_LEXER;
			}

			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}

			if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
				ADVANCE_LEXER;
			}
		} else {
			while (CURRENT_TERMINAL != LEXER_TOK_EOF
				&& CURRENT_TERMINAL != LEXER_TOK_SEPARATOR
				&& CURRENT_TERMINAL != LEXER_TOK_CLOSE_TUPLE
				&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
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
ZR192(GrammarP sid_current_grammar)
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
			E_expected_open_tuple();
		}
	
	}
    }
}

static void
ZR271(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
  ZL2_271:;
    {
	ZR273 (sid_current_grammar);
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
		    goto ZL2_271;
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
			E_expected_separator();
		}
	
		}
		{

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_SEPARATOR) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
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
			goto ZL2_271;
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
ZR193(GrammarP sid_current_grammar)
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
			E_expected_close_tuple();
		}
	
	}
    }
}

static void
ZR131(GrammarP sid_current_grammar, TypeTupleT *ZO129, TypeTupleT *ZO130)
{
    TypeTupleT ZI129;
    TypeTupleT ZI130;

    switch (CURRENT_TERMINAL) {
      case 5:
	{
	    ADVANCE_LEXER;
	    ZR148 (sid_current_grammar, &ZI129);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

		sid_saved_pred_id = sid_current_pred_id;
	
	    }
	    ZR152 (sid_current_grammar);
	    ZR148 (sid_current_grammar, &ZI130);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

		types_init(&(ZI129));
	
	    }
	    {

		types_init(&(ZI130));
	
	    }
	}
	break;
      case 26:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (26);
    return;
  ZL0:;
    {

		ZO129->head = ZI129.head;

		if (ZO129->head == NULL) {
			ZO129->tail = &(ZO129->head);
		} else {
			ZO129->tail= ZI129.tail ;
		}
	    }
    {

		ZO130->head = ZI130.head;

		if (ZO130->head == NULL) {
			ZO130->tail = &(ZO130->head);
		} else {
			ZO130->tail= ZI130.tail ;
		}
	    }
}

static void
ZR219(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    NStringT ZI157;

	    {

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
	    }
	    ADVANCE_LEXER;
	    {
		{
		    {

		sid_current_pred_id = FALSE;
	
		    }
		    ZR300 (sid_current_grammar, &ZI157);
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
			E_expected_tuple_def_or_term();
		}
	
		    }
		    {

		nstring_destroy(&(ZI157));
	
		    }
		    {

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_SCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
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
		    NStringT ZI157;
		    TypeTupleT ZI205;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
			}
			break;
		      default:
			goto ZL5;
		    }
		    ADVANCE_LEXER;
		    {

		sid_current_pred_id = FALSE;
	
		    }
		    {

		types_init(&(ZI205));
	
		    }
		    {

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI157), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI157));

		if (name_entry) {
			if (sid_current_entry && sid_current_alt) {
				if (!types_contains(alt_names(sid_current_alt), name_entry) &&
					!types_contains(rule_param(sid_current_rule), name_entry)) {
					name_entry = NULL;
				}
			} else {
				name_entry = NULL;
			}
		}

		if (name_entry) {
			types_add_name_and_type_var((&ZI205), name_entry, NULL);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI157));
		} else if (non_local_entry) {
			types_add_name_and_type_var ((&ZI205), non_local_entry, NULL);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy (&sid_maximum_scope);
				nstring_assign (&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI157));
		} else {
			E_undefined_assignment((&ZI157));
			types_add_name((&ZI205), grammar_table(sid_current_grammar), &(ZI157), FALSE);
		}
	
		    }
		    {

		sid_saved_pred_id = sid_current_pred_id;
	
		    }
		    ZR225 (sid_current_grammar);
		    ZR210 (sid_current_grammar, &ZI205);
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
			E_expected_identifier();
		}
	
		    }
		}
	      ZL4:;
	    }
	}
	break;
      case 6:
	{
	    TypeTupleT ZI205;

	    ZR170 (sid_current_grammar, &ZI205);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

		sid_saved_pred_id = sid_current_pred_id;
	
	    }
	    ZR225 (sid_current_grammar);
	    ZR210 (sid_current_grammar, &ZI205);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 10: case 18: case 19:
	{
	    {

		sid_current_pred_id = FALSE;
	
	    }
	    ZR299 (sid_current_grammar);
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
ZR161(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    NStringT ZI157;
	    EntryP ZI163;
	    TypeTupleT ZI129;
	    TypeTupleT ZI130;

	    {

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
	    }
	    ADVANCE_LEXER;
	    {

		(ZI163) = table_add_basic(grammar_table(sid_current_grammar), &(ZI157),
			sid_current_grammar, FALSE);
		if ((ZI163) == NULL) {
			E_duplicate_basic((&ZI157));
			nstring_destroy(&(ZI157));
		}
	
	    }
	    ZR131 (sid_current_grammar, &ZI129, &ZI130);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

		if ((ZI163)) {
			KeyT *key = entry_key((ZI163));
			BasicT *basic = entry_get_basic((ZI163));
			if (types_contains_names((&ZI129))) {
				E_basic_param_has_names(key, (&ZI129));
			}
			if (types_contains_names((&ZI130))) {
				E_basic_result_has_names(key, (&ZI130));
			}
			if (types_contains_references((&ZI130))) {
				E_basic_result_has_refs(key, (&ZI130));
			}
			if (!types_equal_zero_tuple((&ZI129))) {
				E_basic_param_mismatch(key, (&ZI129));
			}
			types_assign(basic_result(basic), (&ZI130));
		} else {
			types_destroy((&ZI130));
		}
		types_destroy((&ZI129));
	
	    }
	    ZR245 (sid_current_grammar);
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
		    NStringT ZI157;
		    EntryP ZI163;
		    TypeTupleT ZI129;
		    TypeTupleT ZI130;

		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
			}
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    {

		(ZI163) = table_add_basic(grammar_table(sid_current_grammar), &(ZI157),
			sid_current_grammar, TRUE);
		if ((ZI163) == NULL) {
			E_duplicate_basic((&ZI157));
			nstring_destroy(&(ZI157));
		}
	
		    }
		    ZR131 (sid_current_grammar, &ZI129, &ZI130);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		    {

		if ((ZI163)) {
			KeyT *key = entry_key((ZI163));
			BasicT *basic = entry_get_basic((ZI163));
			if (types_contains_names((&ZI129))) {
				E_basic_param_has_names(key, (&ZI129));
			}
			if (types_contains_names((&ZI130))) {
				E_basic_result_has_names(key, (&ZI130));
			}
			if (types_contains_references((&ZI130))) {
				E_basic_result_has_refs(key, (&ZI130));
			}
			if (!types_equal_zero_tuple((&ZI129))) {
				E_basic_param_mismatch(key, (&ZI129));
			}
			types_assign(basic_result(basic), (&ZI130));
		} else {
			types_destroy((&ZI130));
		}
		types_destroy((&ZI129));
	
		    }
		    ZR245 (sid_current_grammar);
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
			E_expected_identifier();
		}
	
		    }
		    {

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
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
			E_expected_terminal_decn();
		}
	
	}
	{

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
	}
    }
}

static void
ZR225(GrammarP sid_current_grammar)
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
			E_expected_define();
		}
	
	}
    }
}

static void
ZR228(GrammarP sid_current_grammar, TypeTupleT *ZI205)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	NStringT ZI157;

	switch (CURRENT_TERMINAL) {
	  case 4:
	    {

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

		if (sid_current_entry && sid_current_alt) {
			EntryT *entry;

			entry = scope_stack_get_action(&sid_scope_stack,
				grammar_table(sid_current_grammar), (&ZI157));
			if (entry) {
				sid_current_item = item_create(entry);
			} else {
				E_unknown_action((&ZI157));
				sid_current_item = NULL;
				(void) alt_deallocate(sid_current_alt);
				sid_current_alt  = NULL;
			}
		} else {
			sid_current_item = NULL;
		}
		nstring_destroy(&(ZI157));
	
	}
	ZR229 (sid_current_grammar);
	ZR206 (sid_current_grammar, ZI205);
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
			E_expected_identifier();
		}
	
	}
	{

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_SCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != LEXER_TOK_EOF) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
	}
    }
}

static void
ZR229(GrammarP sid_current_grammar)
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
			E_expected_end_action();
		}
	
	}
    }
}

static void
ZR194(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	{
	    switch (CURRENT_TERMINAL) {
	      case 10:
		{
		    NStringT ZI157;
		    EntryP ZI163;
		    TypeTupleT ZI129;
		    TypeTupleT ZI130;

		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 4:
			{

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
			}
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    {

		(ZI163) = scope_stack_add_action (sid_current_scope,
			grammar_table(sid_current_grammar), &(ZI157), sid_enclosing_rule,
			&sid_redefining_entry, FALSE);
		if (!(ZI163)) {
			E_duplicate_action((&ZI157));
			nstring_destroy(&(ZI157));
		}
	
		    }
		    ZR229 (sid_current_grammar);
		    ZR131 (sid_current_grammar, &ZI129, &ZI130);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		    {

		if ((ZI163)) {
			KeyT       *key     = entry_key(sid_current_entry);
			ActionT    *action  = entry_get_action((ZI163));
			TypeTupleT *param   = action_param(action);
			TypeTupleT *result  = action_result(action);
			BoolT       errored = FALSE;

			if (types_contains_names((&ZI129))) {
				E_action_param_has_names(key, (&ZI129));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(param, (&ZI129))) {
					E_action_param_mismatch(key, param, (&ZI129));
					errored = TRUE;
				}
			}

			if (types_contains_names((&ZI130))) {
				E_action_result_has_names(key, (&ZI130));
				errored = TRUE;
			}

			if (types_contains_references((&ZI130))) {
				E_action_result_has_refs(key, (&ZI130));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(result, (&ZI130))) {
					E_action_result_mismatch(key, result, (&ZI130));
					errored = TRUE;
				}
			}

			if (errored || sid_redefining_entry) {
				types_destroy((&ZI129));
				types_destroy((&ZI130));
			} else {
				types_assign(param, (&ZI129));
				types_assign(result, (&ZI130));
			}
		} else {
			types_destroy((&ZI129));
			types_destroy((&ZI130));
		}
	
		    }
		    ZR245 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		}
		break;
	      case 19:
		{
		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 10:
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    {
			{
			    NStringT ZI157;
			    EntryP ZI163;
			    TypeTupleT ZI129;
			    TypeTupleT ZI130;

			    switch (CURRENT_TERMINAL) {
			      case 4:
				{

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
				}
				break;
			      default:
				goto ZL5;
			    }
			    ADVANCE_LEXER;
			    {

		(ZI163) = scope_stack_add_action (sid_current_scope,
			grammar_table(sid_current_grammar), &(ZI157), sid_enclosing_rule,
			&sid_redefining_entry, TRUE);
		if (!(ZI163)) {
			E_duplicate_action((&ZI157));
			nstring_destroy(&(ZI157));
		}
	
			    }
			    ZR229 (sid_current_grammar);
			    ZR131 (sid_current_grammar, &ZI129, &ZI130);
			    if ((CURRENT_TERMINAL) == 26) {
				RESTORE_LEXER;
				goto ZL5;
			    }
			    {

		if ((ZI163)) {
			KeyT       *key     = entry_key(sid_current_entry);
			ActionT    *action  = entry_get_action((ZI163));
			TypeTupleT *param   = action_param(action);
			TypeTupleT *result  = action_result(action);
			BoolT       errored = FALSE;

			if (types_contains_names((&ZI129))) {
				E_action_param_has_names(key, (&ZI129));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(param, (&ZI129))) {
					E_action_param_mismatch(key, param, (&ZI129));
					errored = TRUE;
				}
			}

			if (types_contains_names((&ZI130))) {
				E_action_result_has_names(key, (&ZI130));
				errored = TRUE;
			}

			if (types_contains_references((&ZI130))) {
				E_action_result_has_refs(key, (&ZI130));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(result, (&ZI130))) {
					E_action_result_mismatch(key, result, (&ZI130));
					errored = TRUE;
				}
			}

			if (errored || sid_redefining_entry) {
				types_destroy((&ZI129));
				types_destroy((&ZI130));
			} else {
				types_assign(param, (&ZI129));
				types_assign(result, (&ZI130));
			}
		} else {
			types_destroy((&ZI129));
			types_destroy((&ZI130));
		}
	
			    }
			    ZR245 (sid_current_grammar);
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
			E_expected_identifier();
		}
	
			    }
			    {

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_END_SCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
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
	      default:
		goto ZL3;
	    }
	    goto ZL2;
	  ZL3:;
	    {
		{

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
		}
		{

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_END_SCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
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
}

static void
ZR239(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
  ZL2_239:;
    {
	ZR232 (sid_current_grammar);
	{
	    switch (CURRENT_TERMINAL) {
	      case 4: case 6: case 10: case 13:
	      case 18: case 19: case 24:
		{
		    goto ZL2_239;
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
			E_expected_item();
		}
	
	}
	{

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_SEP
			&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_RULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_SCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_PRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_ENTRY) {
			if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == LEXER_TOK_IDENTIFIER) {
			nstring_destroy(lexer_string_value(sid_current_stream));
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
ZR273(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	NStringT ZI157;

	switch (CURRENT_TERMINAL) {
	  case 4:
	    {

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

		EntryT *entry;

		entry = table_get_rule (grammar_table(sid_current_grammar), (&ZI157));
		if (entry) {
			if (entry_list_contains(grammar_entry_list(sid_current_grammar), entry)) {
				E_mult_entry(entry_key(entry));
			} else {
				entry_list_add(grammar_entry_list(sid_current_grammar), entry);
				rule_required(entry_get_rule (entry));
			}
		} else {
			E_unknown_rule((&ZI157));
		}
		nstring_destroy(&(ZI157));
	
	}
    }
    return;
  ZL1:;
    {
	{

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
	}
    }
}

static void
ZR237(GrammarP sid_current_grammar)
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
			E_expected_end_rule();
		}
	
	}
    }
}

static void
ZR175(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
  ZL2_175:;
    {
	ZR172 (sid_current_grammar, ZI133);
	{
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		{

		(ZI0) = (CURRENT_TERMINAL == LEXER_TOK_CLOSE_TUPLE
			|| CURRENT_TERMINAL == LEXER_TOK_EOF
			|| sid_propagating_error);
	
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
		    goto ZL2_175;
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
			E_expected_separator();
		}
	
		}
		goto ZL2_175;
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
ZR245(GrammarP sid_current_grammar)
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
			E_expected_terminator();
		}
	
	}
    }
}

static void
ZR187(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
  ZL2_187:;
    {
	ZR184 (sid_current_grammar, ZI133);
	{
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		{

		(ZI0) = (CURRENT_TERMINAL == LEXER_TOK_CLOSE_TUPLE
			|| CURRENT_TERMINAL == LEXER_TOK_EOF
			|| sid_propagating_error);
	
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
		    goto ZL2_187;
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
			E_expected_separator();
		}
	
		}
		goto ZL2_187;
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

/* BEGINNING OF TRAILER */




/* END OF FILE */
