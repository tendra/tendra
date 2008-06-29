/*
 * Automatically generated from the files:
 *	parser.sid
 * and
 *	parser.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 175 "parser.act"


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

	#define ERROR_TERMINAL LEXER_TOK_ERROR
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

#line 131 "tmp.parser.c"


#ifndef ERROR_TERMINAL
#error "-s no-numeric-terminals given and ERROR_TERMINAL is not defined"
#endif

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
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_246:;
    {
	ZR243 (sid_current_grammar);
	/* BEGINNING OF INLINE: 248 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_ALT_HSEP):
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list::production-defn-alternatives */
		    goto ZL2_246;
		    /* END OF INLINE: sid-parse-grammar::production-defn-list::production-defn-alternatives */
		}
		/*UNREACHED*/
	      case (ERROR_TERMINAL):
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
	/* END OF INLINE: 248 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR241(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF ACTION: handler */
	{
#line 928 "parser.act"

		if (sid_current_entry) {
			sid_current_alt = alt_create();
		}
	
#line 244 "tmp.parser.c"
	}
	/* END OF ACTION: handler */
	ZR239 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: x-handler */
	{
#line 946 "parser.act"

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
	
#line 272 "tmp.parser.c"
	}
	/* END OF ACTION: x-handler */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR260(GrammarP sid_current_grammar, TypeTupleT *ZI129, TypeTupleT *ZI130)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_DEFINE): case (LEXER_TOK_BEGIN_HSCOPE):
	{
	    /* BEGINNING OF ACTION: prod */
	    {
#line 751 "parser.act"

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
	
#line 372 "tmp.parser.c"
	    }
	    /* END OF ACTION: prod */
	    /* BEGINNING OF ACTION: push-scope */
	    {
#line 840 "parser.act"

		if (sid_current_entry) {
			KeyT     *key   = entry_key(sid_current_entry);
			NStringT *scope = key_get_string(key);

			scope_stack_push(&sid_scope_stack, scope);
		}
	
#line 386 "tmp.parser.c"
	    }
	    /* END OF ACTION: push-scope */
	    ZR202 (sid_current_grammar);
	    ZR225 (sid_current_grammar);
	    /* BEGINNING OF INLINE: 262 */
	    {
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{
		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_BEGIN_HRULE):
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-begin-rule */
		    {
#line 1610 "parser.act"

		if (!sid_propagating_error) {
			E_expected_begin_rule();
		}
	
#line 417 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-begin-rule */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 262 */
	    ZR230 (sid_current_grammar);
	    ZR237 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: pop-scope */
	    {
#line 846 "parser.act"

		if (sid_current_entry) {
			scope_stack_pop(&sid_scope_stack);
		}
	
#line 438 "tmp.parser.c"
	    }
	    /* END OF ACTION: pop-scope */
	    /* BEGINNING OF ACTION: x-prod */
	    {
#line 831 "parser.act"

		if (sid_current_entry) {
			nstring_assign(rule_maximum_scope(sid_current_rule),
				&sid_maximum_scope);
		} else {
			nstring_destroy(&sid_maximum_scope);
		}
	
#line 452 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-prod */
	    ZR245 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_TERMINATOR):
	{
	    /* BEGINNING OF ACTION: x-rule */
	    {
#line 700 "parser.act"

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
	
#line 515 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-rule */
	    ADVANCE_LEXER;
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR143(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_143:;
    {
	ZR134 (sid_current_grammar, ZI133);
	/* BEGINNING OF INLINE: 145 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-close-tuple-or-skipped-or-eof */
		{
#line 1952 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == LEXER_TOK_CLOSE_HTUPLE
			|| CURRENT_TERMINAL == LEXER_TOK_EOF
			|| sid_propagating_error);
	
#line 556 "tmp.parser.c"
		}
		/* END OF ACTION: is-close-tuple-or-skipped-or-eof */
		if (!ZI0)
		    goto ZL5;
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL5:;
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_SEPARATOR):
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: sid-parse-grammar::function-type-defn::tuple-defn-list-1 */
		    goto ZL2_143;
		    /* END OF INLINE: sid-parse-grammar::function-type-defn::tuple-defn-list-1 */
		}
		/*UNREACHED*/
	      default:
		goto ZL4;
	    }
	    /*UNREACHED*/
	  ZL4:;
	    {
		/* BEGINNING OF ACTION: expected-separator */
		{
#line 1526 "parser.act"

		if (!sid_propagating_error) {
			E_expected_separator();
		}
	
#line 588 "tmp.parser.c"
		}
		/* END OF ACTION: expected-separator */
		/* BEGINNING OF INLINE: sid-parse-grammar::function-type-defn::tuple-defn-list-1 */
		goto ZL2_143;
		/* END OF INLINE: sid-parse-grammar::function-type-defn::tuple-defn-list-1 */
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
	/* END OF INLINE: 145 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR243(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_EMPTY):
	{
	    /* BEGINNING OF ACTION: empty-alt */
	    {
#line 887 "parser.act"

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
	
#line 637 "tmp.parser.c"
	    }
	    /* END OF ACTION: empty-alt */
	    ADVANCE_LEXER;
	    ZR245 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_OPEN_HTUPLE): case (LEXER_TOK_BEGIN_HACTION): case (LEXER_TOK_BEGIN_HRULE):
      case (LEXER_TOK_PRED_HRESULT): case (LEXER_TOK_IGNORE): case (LEXER_TOK_REFERENCE):
	{
	    /* BEGINNING OF ACTION: non-empty-alt */
	    {
#line 903 "parser.act"

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
	
#line 669 "tmp.parser.c"
	    }
	    /* END OF ACTION: non-empty-alt */
	    ZR239 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: x-non-empty-alt */
	    {
#line 922 "parser.act"

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
	
#line 698 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-non-empty-alt */
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-alternative */
	{
#line 1628 "parser.act"

		if (!sid_propagating_error) {
			E_expected_alternative();
		}
	
#line 719 "tmp.parser.c"
	}
	/* END OF ACTION: expected-alternative */
	/* BEGINNING OF ACTION: skip-to-end-of-alternative */
	{
#line 1848 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_END_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HSCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 749 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-alternative */
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 1943 "parser.act"

		sid_propagating_error = FALSE;
	
#line 758 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
    }
}

static void
ZR178(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_PRED_HRESULT): case (LEXER_TOK_IGNORE): case (LEXER_TOK_REFERENCE):
	{
	    ZR175 (sid_current_grammar, ZI133);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR250(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI157;

	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_IDENTIFIER):
	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 805 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 252 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_TYPEMARK):
		{
		    ADVANCE_LEXER;
		    ZR297 (sid_current_grammar, &ZI157);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		}
		break;
	      case (LEXER_TOK_TERMINATOR): case (LEXER_TOK_DEFINE): case (LEXER_TOK_BEGIN_HSCOPE):
		{
		    TypeTupleT ZI129;
		    TypeTupleT ZI130;

		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 344 "parser.act"

		types_init(&(ZI129));
	
#line 837 "tmp.parser.c"
		    }
		    /* END OF ACTION: init-tuple */
		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 344 "parser.act"

		types_init(&(ZI130));
	
#line 846 "tmp.parser.c"
		    }
		    /* END OF ACTION: init-tuple */
		    /* BEGINNING OF ACTION: rule */
		    {
#line 682 "parser.act"

		sid_current_entry = scope_stack_add_rule(sid_current_scope,
			grammar_table(sid_current_grammar), &(ZI157), sid_enclosing_rule,
			&sid_redefining_entry);
		if (sid_current_entry) {
			sid_current_rule = entry_get_rule(sid_current_entry);
		} else {
			E_duplicate_rule((&ZI157));
			nstring_destroy(&(ZI157));
		}
	
#line 863 "tmp.parser.c"
		    }
		    /* END OF ACTION: rule */
		    ZR260 (sid_current_grammar, &ZI129, &ZI130);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
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
		/* BEGINNING OF ACTION: expected-other-defn */
		{
#line 1634 "parser.act"

		if (!sid_propagating_error) {
			E_expected_other_defn();
		}
	
#line 887 "tmp.parser.c"
		}
		/* END OF ACTION: expected-other-defn */
		/* BEGINNING OF ACTION: destroy-string */
		{
#line 1679 "parser.act"

		nstring_destroy(&(ZI157));
	
#line 896 "tmp.parser.c"
		}
		/* END OF ACTION: destroy-string */
		/* BEGINNING OF ACTION: skip-to-end-of-other-defn */
		{
#line 1873 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_END_HSCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 925 "tmp.parser.c"
		}
		/* END OF ACTION: skip-to-end-of-other-defn */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 252 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR170(GrammarP sid_current_grammar, TypeTupleT *ZO133)
{
    TypeTupleT ZI133;

    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF ACTION: current-tuple */
	{
#line 349 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 954 "tmp.parser.c"
	}
	/* END OF ACTION: current-tuple */
	ZR192 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 344 "parser.act"

		types_init(&(ZI133));
	
#line 968 "tmp.parser.c"
	}
	/* END OF ACTION: init-tuple */
	ZR178 (sid_current_grammar, &ZI133);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 1943 "parser.act"

		sid_propagating_error = FALSE;
	
#line 982 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	ZR193 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
  ZL0:;
    /* BEGINNING OF RESULT ASSIGNMENT: TypeTupleT */
    {
#line 251 "parser.act"

		ZO133->head = ZI133.head;

		if (ZO133->head == NULL) {
			ZO133->tail = &(ZO133->head);
		} else {
			ZO133->tail= ZI133.tail ;
		}
	#line 1007 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: TypeTupleT */
}

static void
ZR152(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_ARROW):
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-arrow */
	{
#line 1544 "parser.act"

		if (!sid_propagating_error) {
			E_expected_arrow();
		}
	
#line 1038 "tmp.parser.c"
	}
	/* END OF ACTION: expected-arrow */
    }
}

static void
ZR153(GrammarP sid_current_grammar)
{
  ZL2_153:;
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER):
	{
	    ZR155 (sid_current_grammar);
	    /* BEGINNING OF INLINE: sid-parse-grammar::type-decl-list */
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_153;
	    }
	    /* END OF INLINE: sid-parse-grammar::type-decl-list */
	}
	/*UNREACHED*/
      case (ERROR_TERMINAL):
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR182(GrammarP sid_current_grammar, TypeTupleT *ZO133)
{
    TypeTupleT ZI133;

    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF ACTION: current-tuple */
	{
#line 349 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 1088 "tmp.parser.c"
	}
	/* END OF ACTION: current-tuple */
	ZR192 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 344 "parser.act"

		types_init(&(ZI133));
	
#line 1102 "tmp.parser.c"
	}
	/* END OF ACTION: init-tuple */
	ZR190 (sid_current_grammar, &ZI133);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 1943 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1116 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	ZR193 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
  ZL0:;
    /* BEGINNING OF RESULT ASSIGNMENT: TypeTupleT */
    {
#line 251 "parser.act"

		ZO133->head = ZI133.head;

		if (ZO133->head == NULL) {
			ZO133->tail = &(ZO133->head);
		} else {
			ZO133->tail= ZI133.tail ;
		}
	#line 1141 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: TypeTupleT */
}

static void
ZR232(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_BEGIN_HRULE):
	{
	    EntryP ZI163;
	    RuleP ZI70;
	    AltP ZI234;
	    BoolT ZI235;
	    ItemP ZI236;

	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: save */
	    {
#line 949 "parser.act"

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
	
#line 1186 "tmp.parser.c"
	    }
	    /* END OF ACTION: save */
	    ZR230 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: restore */
	    {
#line 974 "parser.act"

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
	
#line 1210 "tmp.parser.c"
	    }
	    /* END OF ACTION: restore */
	    ZR237 (sid_current_grammar);
	    ZR245 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_OPEN_HTUPLE): case (LEXER_TOK_BEGIN_HACTION): case (LEXER_TOK_PRED_HRESULT):
      case (LEXER_TOK_IGNORE): case (LEXER_TOK_REFERENCE):
	{
	    ZR219 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 1943 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1235 "tmp.parser.c"
	    }
	    /* END OF ACTION: skip-recover */
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR155(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI157;

	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_IDENTIFIER):
	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 1268 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF ACTION: add-type */
	{
#line 279 "parser.act"

		if (table_add_type (grammar_table(sid_current_grammar), &(ZI157)) == NULL) {
			E_duplicate_type((&ZI157));
			nstring_destroy(&(ZI157));
		}
	
#line 1285 "tmp.parser.c"
	}
	/* END OF ACTION: add-type */
	ZR245 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR190(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_REFERENCE):
	{
	    ZR187 (sid_current_grammar, ZI133);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR202(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_BEGIN_HSCOPE):
	{
	    EntryP ZI163;
	    RuleP ZI70;

	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: save-scope */
	    {
#line 849 "parser.act"

		(ZI163) = sid_current_entry;
		(ZI70)  = sid_enclosing_rule;

		sid_enclosing_rule = sid_current_rule;
	
#line 1343 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-scope */
	    ZR168 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: restore-scope */
	    {
#line 856 "parser.act"

		sid_current_entry  = (ZI163);
		sid_current_rule   = sid_enclosing_rule;
		sid_enclosing_rule = (ZI70);
		sid_alternative    = 0;
		sid_internal_rule  = FALSE;
		sid_external_rule  = sid_current_entry;

		nstring_init(&sid_maximum_scope);
	
#line 1364 "tmp.parser.c"
	    }
	    /* END OF ACTION: restore-scope */
	    /* BEGINNING OF INLINE: 204 */
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_END_HSCOPE):
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-end-scope */
		    {
#line 1580 "parser.act"

		if (!sid_propagating_error) {
			E_expected_end_scope();
		}
	
#line 1389 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-end-scope */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 204 */
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR172(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI157;

	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 1423 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: add-name */
	    {
#line 392 "parser.act"

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
	
#line 1469 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-name */
	}
	break;
      case (LEXER_TOK_IGNORE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: add-void */
	    {
#line 520 "parser.act"

		EntryT *entry;

		entry = table_add_generated_name(grammar_table(sid_current_grammar));
		types_add_name_entry((ZI133), entry);
	
#line 1486 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-void */
	}
	break;
      case (LEXER_TOK_PRED_HRESULT):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: add-pred */
	    {
#line 513 "parser.act"

		if (sid_current_pred_id) {
			E_multi_predicate_return();
		}
		sid_current_pred_id = TRUE;
		types_add_name_entry((ZI133), grammar_get_predicate_id(sid_current_grammar));
	
#line 1504 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-pred */
	}
	break;
      case (LEXER_TOK_REFERENCE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 174 */
	    {
		{
		    NStringT ZI157;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 1525 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: add-var */
		    {
#line 473 "parser.act"

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
	
#line 1576 "tmp.parser.c"
		    }
		    /* END OF ACTION: add-var */
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1508 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 1591 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 174 */
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-lhs-name */
	{
#line 1556 "parser.act"

		if (!sid_propagating_error) {
			E_expected_lhs_name();
		}
	
#line 1616 "tmp.parser.c"
	}
	/* END OF ACTION: expected-lhs-name */
	/* BEGINNING OF ACTION: skip-to-end-of-lhs-name */
	{
#line 1754 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 1643 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-lhs-name */
    }
}

static void
ZR168(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_168:;
    {
	ZR265 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 1943 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1668 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	/* BEGINNING OF INLINE: 269 */
	{
	    {
		/* BEGINNING OF ACTION: is-blt-entry-or-end-scope-or-eof */
		{
#line 1946 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == LEXER_TOK_EOF
			|| CURRENT_TERMINAL == LEXER_TOK_END_HSCOPE
			|| CURRENT_TERMINAL == LEXER_TOK_BLT_HENTRY);
	
#line 1682 "tmp.parser.c"
		}
		/* END OF ACTION: is-blt-entry-or-end-scope-or-eof */
		if (!ZI0)
		    goto ZL4;
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL4:;
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_BEGIN_HACTION): case (LEXER_TOK_IGNORE): case (LEXER_TOK_SCOPEMARK):
		{
		    /* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list */
		    goto ZL2_168;
		    /* END OF INLINE: sid-parse-grammar::production-defn-list */
		}
		/*UNREACHED*/
	      default:
		goto ZL1;
	    }
	  ZL3:;
	}
	/* END OF INLINE: 269 */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-production-defn */
	{
#line 1640 "parser.act"

		if (!sid_propagating_error) {
			E_expected_production_defn();
		}
	
#line 1717 "tmp.parser.c"
	}
	/* END OF ACTION: expected-production-defn */
	/* BEGINNING OF ACTION: skip-to-end-of-production-defn */
	{
#line 1897 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_END_HSCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 1746 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-production-defn */
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 1943 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1755 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	/* BEGINNING OF INLINE: 270 */
	{
	    {
		/* BEGINNING OF ACTION: is-blt-entry-or-end-scope-or-eof */
		{
#line 1946 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == LEXER_TOK_EOF
			|| CURRENT_TERMINAL == LEXER_TOK_END_HSCOPE
			|| CURRENT_TERMINAL == LEXER_TOK_BLT_HENTRY);
	
#line 1769 "tmp.parser.c"
		}
		/* END OF ACTION: is-blt-entry-or-end-scope-or-eof */
		if (!ZI0)
		    goto ZL7;
	    }
	    goto ZL6;
	  ZL7:;
	    {
		/* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list */
		goto ZL2_168;
		/* END OF INLINE: sid-parse-grammar::production-defn-list */
	    }
	    /*UNREACHED*/
	  ZL6:;
	}
	/* END OF INLINE: 270 */
    }
}

void
sid_parse_grammar(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF ACTION: init */
	{
#line 271 "parser.act"

		scope_stack_init(&sid_scope_stack);
		scope_stack_init(&sid_global_scope);
	
#line 1803 "tmp.parser.c"
	}
	/* END OF ACTION: init */
	/* BEGINNING OF INLINE: 276 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case (LEXER_TOK_BLT_HTYPES):
		    break;
		  default:
		    goto ZL3;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: expected-blt-types */
		{
#line 1646 "parser.act"

		if (!sid_propagating_error) {
			E_expected_blt_types();
		}
	
#line 1828 "tmp.parser.c"
		}
		/* END OF ACTION: expected-blt-types */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 276 */
	ZR153 (sid_current_grammar);
	/* BEGINNING OF INLINE: 277 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case (LEXER_TOK_BLT_HTERMINALS):
		    break;
		  default:
		    goto ZL5;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL4;
	  ZL5:;
	    {
		/* BEGINNING OF ACTION: expected-blt-terminals */
		{
#line 1652 "parser.act"

		if (!sid_propagating_error) {
			E_expected_blt_terminals();
		}
	
#line 1862 "tmp.parser.c"
		}
		/* END OF ACTION: expected-blt-terminals */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 277 */
	ZR159 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: x-terminals */
	{
#line 336 "parser.act"

		unsigned max_terminal = grammar_max_terminal(sid_current_grammar);

		bitvec_set_size(max_terminal);
		sid_finished_terminals = TRUE;
	
#line 1883 "tmp.parser.c"
	}
	/* END OF ACTION: x-terminals */
	/* BEGINNING OF INLINE: 278 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case (LEXER_TOK_BLT_HPRODUCTIONS):
		    break;
		  default:
		    goto ZL7;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL6;
	  ZL7:;
	    {
		/* BEGINNING OF ACTION: expected-blt-productions */
		{
#line 1658 "parser.act"

		if (!sid_propagating_error) {
			E_expected_blt_productions();
		}
	
#line 1908 "tmp.parser.c"
		}
		/* END OF ACTION: expected-blt-productions */
	    }
	  ZL6:;
	}
	/* END OF INLINE: 278 */
	ZR168 (sid_current_grammar);
	/* BEGINNING OF INLINE: 279 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case (LEXER_TOK_BLT_HENTRY):
		    break;
		  default:
		    goto ZL9;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL8;
	  ZL9:;
	    {
		/* BEGINNING OF ACTION: expected-blt-entry */
		{
#line 1664 "parser.act"

		if (!sid_propagating_error) {
			E_expected_blt_entry();
		}
	
#line 1942 "tmp.parser.c"
		}
		/* END OF ACTION: expected-blt-entry */
	    }
	  ZL8:;
	}
	/* END OF INLINE: 279 */
	ZR271 (sid_current_grammar);
	ZR245 (sid_current_grammar);
	/* BEGINNING OF INLINE: 281 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case (LEXER_TOK_EOF):
		    break;
		  default:
		    goto ZL11;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL10;
	  ZL11:;
	    {
		/* BEGINNING OF ACTION: expected-eof */
		{
#line 1670 "parser.act"

		if (!sid_propagating_error) {
			E_expected_eof();
		}
	
#line 1977 "tmp.parser.c"
		}
		/* END OF ACTION: expected-eof */
	    }
	  ZL10:;
	}
	/* END OF INLINE: 281 */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: unhandled-syntax-error */
	{
#line 1496 "parser.act"

		UNREACHED;
	
#line 1994 "tmp.parser.c"
	}
	/* END OF ACTION: unhandled-syntax-error */
    }
}

static void
ZR146(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_TYPEMARK):
	{
	    ZR143 (sid_current_grammar, ZI133);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR297(GrammarP sid_current_grammar, NStringT *ZI157)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_OPEN_HTUPLE):
	{
	    TypeTupleT ZI129;
	    TypeTupleT ZI130;

	    ZR148 (sid_current_grammar, &ZI129);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 353 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2044 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR152 (sid_current_grammar);
	    ZR148 (sid_current_grammar, &ZI130);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: rule */
	    {
#line 682 "parser.act"

		sid_current_entry = scope_stack_add_rule(sid_current_scope,
			grammar_table(sid_current_grammar), &(*ZI157), sid_enclosing_rule,
			&sid_redefining_entry);
		if (sid_current_entry) {
			sid_current_rule = entry_get_rule(sid_current_entry);
		} else {
			E_duplicate_rule((ZI157));
			nstring_destroy(&(*ZI157));
		}
	
#line 2067 "tmp.parser.c"
	    }
	    /* END OF ACTION: rule */
	    ZR260 (sid_current_grammar, &ZI129, &ZI130);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_IDENTIFIER):
	{
	    /* BEGINNING OF INLINE: 253 */
	    {
		{
		    NStringT ZI139;
		    NonLocalEntryP ZI254;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 263 "parser.act"

		nstring_assign(&ZI139, lexer_string_value(sid_current_stream));
	
#line 2093 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: non-local */
		    {
#line 607 "parser.act"

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
	
#line 2135 "tmp.parser.c"
		    }
		    /* END OF ACTION: non-local */
		    /* BEGINNING OF INLINE: 255 */
		    {
			switch (CURRENT_TERMINAL) {
			  case (LEXER_TOK_DEFINE):
			    {
				ADVANCE_LEXER;
				/* BEGINNING OF INLINE: 256 */
				{
				    {
					switch (CURRENT_TERMINAL) {
					  case (LEXER_TOK_BEGIN_HACTION):
					    break;
					  default:
					    goto ZL7;
					}
					ADVANCE_LEXER;
				    }
				    goto ZL6;
				  ZL7:;
				    {
					/* BEGINNING OF ACTION: expected-begin-action */
					{
#line 1568 "parser.act"

		if (!sid_propagating_error) {
			E_expected_begin_action();
		}
	
#line 2166 "tmp.parser.c"
					}
					/* END OF ACTION: expected-begin-action */
				    }
				  ZL6:;
				}
				/* END OF INLINE: 256 */
				/* BEGINNING OF INLINE: 257 */
				{
				    {
					NStringT ZI51;

					switch (CURRENT_TERMINAL) {
					  case (LEXER_TOK_IDENTIFIER):
					    /* BEGINNING OF EXTRACT: IDENTIFIER */
					    {
#line 263 "parser.act"

		nstring_assign(&ZI51, lexer_string_value(sid_current_stream));
	
#line 2186 "tmp.parser.c"
					    }
					    /* END OF EXTRACT: IDENTIFIER */
					    break;
					  default:
					    goto ZL9;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: non-local-init */
					{
#line 642 "parser.act"

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
	
#line 2238 "tmp.parser.c"
					}
					/* END OF ACTION: non-local-init */
					ZR229 (sid_current_grammar);
					ZR245 (sid_current_grammar);
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					    RESTORE_LEXER;
					    goto ZL9;
					}
				    }
				    goto ZL8;
				  ZL9:;
				    {
					/* BEGINNING OF ACTION: expected-identifier */
					{
#line 1508 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 2259 "tmp.parser.c"
					}
					/* END OF ACTION: expected-identifier */
				    }
				  ZL8:;
				}
				/* END OF INLINE: 257 */
			    }
			    break;
			  case (LEXER_TOK_TERMINATOR):
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
			    /* BEGINNING OF ACTION: expected-terminator-or-define */
			    {
#line 1676 "parser.act"

		if (!sid_propagating_error) {
			E_expected_terminator_or_define();
		}
	
#line 2287 "tmp.parser.c"
			    }
			    /* END OF ACTION: expected-terminator-or-define */
			}
		      ZL4:;
		    }
		    /* END OF INLINE: 255 */
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1508 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 2306 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: destroy-string */
		    {
#line 1679 "parser.act"

		nstring_destroy(&(*ZI157));
	
#line 2315 "tmp.parser.c"
		    }
		    /* END OF ACTION: destroy-string */
		    /* BEGINNING OF ACTION: skip-to-end-of-other-defn */
		    {
#line 1873 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_END_HSCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 2344 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-other-defn */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 253 */
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR299(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IGNORE):
	{
	    TypeTupleT ZI205;

	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 344 "parser.act"

		types_init(&(ZI205));
	
#line 2379 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: add-void */
	    {
#line 520 "parser.act"

		EntryT *entry;

		entry = table_add_generated_name(grammar_table(sid_current_grammar));
		types_add_name_entry((&ZI205), entry);
	
#line 2391 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-void */
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 353 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2400 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR225 (sid_current_grammar);
	    ZR210 (sid_current_grammar, &ZI205);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_PRED_HRESULT):
	{
	    TypeTupleT ZI205;

	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 344 "parser.act"

		types_init(&(ZI205));
	
#line 2422 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: add-pred */
	    {
#line 513 "parser.act"

		if (sid_current_pred_id) {
			E_multi_predicate_return();
		}
		sid_current_pred_id = TRUE;
		types_add_name_entry((&ZI205), grammar_get_predicate_id(sid_current_grammar));
	
#line 2435 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-pred */
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 353 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2444 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR225 (sid_current_grammar);
	    ZR210 (sid_current_grammar, &ZI205);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_BEGIN_HACTION):
	{
	    TypeTupleT ZI205;

	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 353 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2465 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 344 "parser.act"

		types_init(&(ZI205));
	
#line 2474 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    ADVANCE_LEXER;
	    ZR228 (sid_current_grammar, &ZI205);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR300(GrammarP sid_current_grammar, NStringT *ZI157)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_DEFINE):
	{
	    TypeTupleT ZI205;

	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 344 "parser.act"

		types_init(&(ZI205));
	
#line 2510 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: add-name */
	    {
#line 392 "parser.act"

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
	
#line 2555 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-name */
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 353 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2564 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ADVANCE_LEXER;
	    ZR210 (sid_current_grammar, &ZI205);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_OPEN_HTUPLE): case (LEXER_TOK_TERMINATOR):
	{
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 353 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2583 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR301 (sid_current_grammar, ZI157);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR301(GrammarP sid_current_grammar, NStringT *ZI157)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_TERMINATOR):
	{
	    TypeTupleT ZI205;
	    TypeTupleT ZI208;

	    /* BEGINNING OF ACTION: current-tuple */
	    {
#line 349 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 2619 "tmp.parser.c"
	    }
	    /* END OF ACTION: current-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 344 "parser.act"

		types_init(&(ZI205));
	
#line 2628 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 344 "parser.act"

		types_init(&(ZI208));
	
#line 2637 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: x-prod-rule */
	    {
#line 1163 "parser.act"

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
	
#line 2758 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-prod-rule */
	    ADVANCE_LEXER;
	}
	break;
      case (LEXER_TOK_OPEN_HTUPLE):
	{
	    TypeTupleT ZI205;
	    TypeTupleT ZI208;

	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 344 "parser.act"

		types_init(&(ZI205));
	
#line 2775 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    ZR182 (sid_current_grammar, &ZI208);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: x-prod-rule */
	    {
#line 1163 "parser.act"

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
	
#line 2901 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-prod-rule */
	    ZR245 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR148(GrammarP sid_current_grammar, TypeTupleT *ZO133)
{
    TypeTupleT ZI133;

    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 344 "parser.act"

		types_init(&(ZI133));
	
#line 2937 "tmp.parser.c"
	}
	/* END OF ACTION: init-tuple */
	ZR192 (sid_current_grammar);
	ZR146 (sid_current_grammar, &ZI133);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 1943 "parser.act"

		sid_propagating_error = FALSE;
	
#line 2952 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	ZR193 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
  ZL0:;
    /* BEGINNING OF RESULT ASSIGNMENT: TypeTupleT */
    {
#line 251 "parser.act"

		ZO133->head = ZI133.head;

		if (ZO133->head == NULL) {
			ZO133->tail = &(ZO133->head);
		} else {
			ZO133->tail= ZI133.tail ;
		}
	#line 2977 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: TypeTupleT */
}

static void
ZR184(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI157;

	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 2996 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: add-name */
	    {
#line 392 "parser.act"

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
	
#line 3042 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-name */
	}
	break;
      case (LEXER_TOK_REFERENCE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 186 */
	    {
		{
		    NStringT ZI157;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 3063 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: add-ref-name */
		    {
#line 433 "parser.act"

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
	
#line 3113 "tmp.parser.c"
		    }
		    /* END OF ACTION: add-ref-name */
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1508 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 3128 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: skip-to-end-of-rhs-name */
		    {
#line 1776 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 3155 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-rhs-name */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 186 */
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-rhs-name */
	{
#line 1562 "parser.act"

		if (!sid_propagating_error) {
			E_expected_rhs_name();
		}
	
#line 3180 "tmp.parser.c"
	}
	/* END OF ACTION: expected-rhs-name */
	/* BEGINNING OF ACTION: skip-to-end-of-rhs-name */
	{
#line 1776 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 3207 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-rhs-name */
    }
}

static void
ZR210(GrammarP sid_current_grammar, TypeTupleT *ZI205)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_BEGIN_HACTION):
	{
	    ADVANCE_LEXER;
	    ZR228 (sid_current_grammar, ZI205);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI157;

	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 3237 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 214 */
	    {
		switch (CURRENT_TERMINAL) {
		  case (LEXER_TOK_OPEN_HTUPLE):
		    {
			TypeTupleT ZI208;

			ZR182 (sid_current_grammar, &ZI208);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			    RESTORE_LEXER;
			    goto ZL3;
			}
			/* BEGINNING OF ACTION: x-prod-rule */
			{
#line 1163 "parser.act"

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
	
#line 3371 "tmp.parser.c"
			}
			/* END OF ACTION: x-prod-rule */
			ZR245 (sid_current_grammar);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			    RESTORE_LEXER;
			    goto ZL3;
			}
		    }
		    break;
		  case (LEXER_TOK_TERMINATOR):
		    {
			/* BEGINNING OF ACTION: current-tuple */
			{
#line 349 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 3389 "tmp.parser.c"
			}
			/* END OF ACTION: current-tuple */
			/* BEGINNING OF ACTION: x-prod-rule-or-identity */
			{
#line 1271 "parser.act"

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
	
#line 3596 "tmp.parser.c"
			}
			/* END OF ACTION: x-prod-rule-or-identity */
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL3;
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-tuple-or-terminator */
		    {
#line 1586 "parser.act"

		if (!sid_propagating_error) {
			E_expected_tuple_or_term();
		}
	
#line 3616 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-tuple-or-terminator */
		    /* BEGINNING OF ACTION: destroy-string */
		    {
#line 1679 "parser.act"

		nstring_destroy(&(ZI157));
	
#line 3625 "tmp.parser.c"
		    }
		    /* END OF ACTION: destroy-string */
		    /* BEGINNING OF ACTION: skip-to-end-of-item */
		    {
#line 1821 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HSCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 3657 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-item */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 214 */
	}
	break;
      case (LEXER_TOK_OPEN_HTUPLE):
	{
	    TypeTupleT ZI208;

	    ZR182 (sid_current_grammar, &ZI208);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: x-identity */
	    {
#line 1091 "parser.act"

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
	
#line 3744 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-identity */
	    ZR245 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_REFERENCE):
	{
	    TypeTupleT ZI208;

	    /* BEGINNING OF ACTION: current-tuple */
	    {
#line 349 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 3764 "tmp.parser.c"
	    }
	    /* END OF ACTION: current-tuple */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 344 "parser.act"

		types_init(&(ZI208));
	
#line 3774 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF INLINE: 216 */
	    {
		{
		    NStringT ZI157;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 3790 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL5;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: add-ref-name */
		    {
#line 433 "parser.act"

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
	
#line 3840 "tmp.parser.c"
		    }
		    /* END OF ACTION: add-ref-name */
		    /* BEGINNING OF ACTION: x-identity */
		    {
#line 1091 "parser.act"

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
	
#line 3912 "tmp.parser.c"
		    }
		    /* END OF ACTION: x-identity */
		    ZR245 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL5;
		    }
		}
		goto ZL4;
	      ZL5:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1508 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 3932 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: skip-to-end-of-item */
		    {
#line 1821 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HSCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 3964 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-item */
		}
	      ZL4:;
	    }
	    /* END OF INLINE: 216 */
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-item-rhs */
	{
#line 1592 "parser.act"

		if (!sid_propagating_error) {
			E_expected_item_rhs();
		}
	
#line 3989 "tmp.parser.c"
	}
	/* END OF ACTION: expected-item-rhs */
	/* BEGINNING OF ACTION: skip-to-end-of-item */
	{
#line 1821 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HSCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 4021 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-item */
    }
}

static void
ZR230(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	ZR246 (sid_current_grammar);
	/* BEGINNING OF INLINE: 249 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_HANDLER_HSEP):
		{
		    ADVANCE_LEXER;
		    ZR241 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case (ERROR_TERMINAL):
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
	/* END OF INLINE: 249 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR159(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_159:;
    {
	ZR161 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 1943 "parser.act"

		sid_propagating_error = FALSE;
	
#line 4082 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	/* BEGINNING OF INLINE: 167 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_IGNORE):
		{
		    /* BEGINNING OF INLINE: sid-parse-grammar::terminal-decn-list */
		    goto ZL2_159;
		    /* END OF INLINE: sid-parse-grammar::terminal-decn-list */
		}
		/*UNREACHED*/
	      default:
		break;
	    }
	}
	/* END OF INLINE: 167 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR206(GrammarP sid_current_grammar, TypeTupleT *ZI205)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_OPEN_HTUPLE):
	{
	    TypeTupleT ZI208;

	    ZR182 (sid_current_grammar, &ZI208);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: x-prod-action */
	    {
#line 1017 "parser.act"

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
	
#line 4202 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-prod-action */
	    ZR245 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_TERMINATOR):
	{
	    TypeTupleT ZI208;

	    /* BEGINNING OF ACTION: current-tuple */
	    {
#line 349 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 4222 "tmp.parser.c"
	    }
	    /* END OF ACTION: current-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 344 "parser.act"

		types_init(&(ZI208));
	
#line 4231 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: x-prod-action */
	    {
#line 1017 "parser.act"

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
	
#line 4316 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-prod-action */
	    ADVANCE_LEXER;
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-tuple-or-terminator */
	{
#line 1586 "parser.act"

		if (!sid_propagating_error) {
			E_expected_tuple_or_term();
		}
	
#line 4338 "tmp.parser.c"
	}
	/* END OF ACTION: expected-tuple-or-terminator */
	/* BEGINNING OF ACTION: skip-to-end-of-item */
	{
#line 1821 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HSCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 4370 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-item */
    }
}

static void
ZR265(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF INLINE: 267 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_SCOPEMARK):
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: use-global */
		    {
#line 530 "parser.act"

		sid_current_scope = &sid_global_scope;
	
#line 4395 "tmp.parser.c"
		    }
		    /* END OF ACTION: use-global */
		}
		break;
	      default:
		{
		    /* BEGINNING OF ACTION: use-local */
		    {
#line 534 "parser.act"

		sid_current_scope = &sid_scope_stack;
	
#line 4408 "tmp.parser.c"
		    }
		    /* END OF ACTION: use-local */
		}
		break;
	    }
	}
	/* END OF INLINE: 267 */
	/* BEGINNING OF INLINE: 268 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_BEGIN_HACTION): case (LEXER_TOK_IGNORE):
		{
		    ZR194 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case (LEXER_TOK_IDENTIFIER):
		{
		    ZR250 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	/* END OF INLINE: 268 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR134(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI136;

	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 263 "parser.act"

		nstring_assign(&ZI136, lexer_string_value(sid_current_stream));
	
#line 4463 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 137 */
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_TYPEMARK):
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-typemark */
		    {
#line 1502 "parser.act"

		if (!sid_propagating_error) {
			E_expected_typemark();
		}
	
#line 4489 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-typemark */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 137 */
	    /* BEGINNING OF INLINE: 138 */
	    {
		{
		    NStringT ZI139;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 263 "parser.act"

		nstring_assign(&ZI139, lexer_string_value(sid_current_stream));
	
#line 4509 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL5;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: 140 */
		    {
			switch (CURRENT_TERMINAL) {
			  case (LEXER_TOK_REFERENCE):
			    {
				ADVANCE_LEXER;
				/* BEGINNING OF ACTION: tuple-ref-name */
				{
#line 364 "parser.act"

		if (!types_add_typed_name((ZI133), grammar_table(sid_current_grammar),
			&(ZI136), (&ZI139), TRUE)) {
			E_unknown_type((&ZI139));
		}
		nstring_destroy(&(ZI139));
	
#line 4533 "tmp.parser.c"
				}
				/* END OF ACTION: tuple-ref-name */
			    }
			    break;
			  default:
			    {
				/* BEGINNING OF ACTION: tuple-name */
				{
#line 356 "parser.act"

		if (!types_add_typed_name((ZI133), grammar_table(sid_current_grammar),
			&(ZI136), (&ZI139), FALSE)) {
			E_unknown_type((&ZI139));
		}
		nstring_destroy(&(ZI139));
	
#line 4550 "tmp.parser.c"
				}
				/* END OF ACTION: tuple-name */
			    }
			    break;
			}
		    }
		    /* END OF INLINE: 140 */
		}
		goto ZL4;
	      ZL5:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1508 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 4570 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: destroy-string */
		    {
#line 1679 "parser.act"

		nstring_destroy(&(ZI136));
	
#line 4579 "tmp.parser.c"
		    }
		    /* END OF ACTION: destroy-string */
		    /* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
		    {
#line 1685 "parser.act"

		if (sid_finished_terminals) {
			while (CURRENT_TERMINAL != LEXER_TOK_EOF
				&& CURRENT_TERMINAL != LEXER_TOK_DEFINE
				&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_HSCOPE
				&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_HRULE
				&& CURRENT_TERMINAL != LEXER_TOK_SEPARATOR
				&& CURRENT_TERMINAL != LEXER_TOK_CLOSE_HTUPLE
				&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
				&& CURRENT_TERMINAL != LEXER_TOK_CLOSE_HTUPLE
				&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 4632 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-tuple-defn */
		}
	      ZL4:;
	    }
	    /* END OF INLINE: 138 */
	}
	break;
      case (LEXER_TOK_TYPEMARK):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 141 */
	    {
		{
		    NStringT ZI139;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 263 "parser.act"

		nstring_assign(&ZI139, lexer_string_value(sid_current_stream));
	
#line 4657 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL8;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: 142 */
		    {
			switch (CURRENT_TERMINAL) {
			  case (LEXER_TOK_REFERENCE):
			    {
				ADVANCE_LEXER;
				/* BEGINNING OF ACTION: tuple-ref-type */
				{
#line 380 "parser.act"

		if (!types_add_type((ZI133), grammar_table(sid_current_grammar), (&ZI139), TRUE)) {
			E_unknown_type((&ZI139));
		}
		nstring_destroy(&(ZI139));
	
#line 4680 "tmp.parser.c"
				}
				/* END OF ACTION: tuple-ref-type */
			    }
			    break;
			  default:
			    {
				/* BEGINNING OF ACTION: tuple-type */
				{
#line 372 "parser.act"

		if (!types_add_type((ZI133), grammar_table(sid_current_grammar), (&ZI139),
		FALSE)) {
			E_unknown_type((&ZI139));
		}
		nstring_destroy(&(ZI139));
	
#line 4697 "tmp.parser.c"
				}
				/* END OF ACTION: tuple-type */
			    }
			    break;
			}
		    }
		    /* END OF INLINE: 142 */
		}
		goto ZL7;
	      ZL8:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1508 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 4717 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
		    {
#line 1685 "parser.act"

		if (sid_finished_terminals) {
			while (CURRENT_TERMINAL != LEXER_TOK_EOF
				&& CURRENT_TERMINAL != LEXER_TOK_DEFINE
				&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_HSCOPE
				&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_HRULE
				&& CURRENT_TERMINAL != LEXER_TOK_SEPARATOR
				&& CURRENT_TERMINAL != LEXER_TOK_CLOSE_HTUPLE
				&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
				&& CURRENT_TERMINAL != LEXER_TOK_CLOSE_HTUPLE
				&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 4770 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-tuple-defn */
		}
	      ZL7:;
	    }
	    /* END OF INLINE: 141 */
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-tuple-defn */
	{
#line 1514 "parser.act"

		if (!sid_propagating_error) {
			E_expected_tuple_defn();
		}
	
#line 4795 "tmp.parser.c"
	}
	/* END OF ACTION: expected-tuple-defn */
	/* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
	{
#line 1685 "parser.act"

		if (sid_finished_terminals) {
			while (CURRENT_TERMINAL != LEXER_TOK_EOF
				&& CURRENT_TERMINAL != LEXER_TOK_DEFINE
				&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_HSCOPE
				&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_HRULE
				&& CURRENT_TERMINAL != LEXER_TOK_SEPARATOR
				&& CURRENT_TERMINAL != LEXER_TOK_CLOSE_HTUPLE
				&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
				&& CURRENT_TERMINAL != LEXER_TOK_CLOSE_HTUPLE
				&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
				&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 4848 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-tuple-defn */
    }
}

static void
ZR192(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_OPEN_HTUPLE):
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-open-tuple */
	{
#line 1532 "parser.act"

		if (!sid_propagating_error) {
			E_expected_open_tuple();
		}
	
#line 4880 "tmp.parser.c"
	}
	/* END OF ACTION: expected-open-tuple */
    }
}

static void
ZR271(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_271:;
    {
	ZR273 (sid_current_grammar);
	/* BEGINNING OF INLINE: 274 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-terminator */
		{
#line 1958 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == LEXER_TOK_TERMINATOR);
	
#line 4908 "tmp.parser.c"
		}
		/* END OF ACTION: is-terminator */
		if (!ZI0)
		    goto ZL5;
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL5:;
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_SEPARATOR):
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: sid-parse-grammar::entry-list */
		    goto ZL2_271;
		    /* END OF INLINE: sid-parse-grammar::entry-list */
		}
		/*UNREACHED*/
	      default:
		goto ZL4;
	    }
	    /*UNREACHED*/
	  ZL4:;
	    {
		/* BEGINNING OF ACTION: expected-separator */
		{
#line 1526 "parser.act"

		if (!sid_propagating_error) {
			E_expected_separator();
		}
	
#line 4940 "tmp.parser.c"
		}
		/* END OF ACTION: expected-separator */
		/* BEGINNING OF ACTION: skip-to-end-of-entry-list */
		{
#line 1921 "parser.act"

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
	
#line 4966 "tmp.parser.c"
		}
		/* END OF ACTION: skip-to-end-of-entry-list */
		/* BEGINNING OF ACTION: skip-recover */
		{
#line 1943 "parser.act"

		sid_propagating_error = FALSE;
	
#line 4975 "tmp.parser.c"
		}
		/* END OF ACTION: skip-recover */
		/* BEGINNING OF INLINE: 275 */
		{
		    {
			/* BEGINNING OF ACTION: is-not-separator */
			{
#line 1962 "parser.act"

		(ZI0) = (CURRENT_TERMINAL != LEXER_TOK_SEPARATOR);
	
#line 4987 "tmp.parser.c"
			}
			/* END OF ACTION: is-not-separator */
			if (!ZI0)
			    goto ZL7;
		    }
		    goto ZL6;
		  ZL7:;
		    {
			/* BEGINNING OF INLINE: sid-parse-grammar::entry-list */
			goto ZL2_271;
			/* END OF INLINE: sid-parse-grammar::entry-list */
		    }
		    /*UNREACHED*/
		  ZL6:;
		}
		/* END OF INLINE: 275 */
	    }
	  ZL3:;
	}
	/* END OF INLINE: 274 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR193(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_CLOSE_HTUPLE):
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-close-tuple */
	{
#line 1538 "parser.act"

		if (!sid_propagating_error) {
			E_expected_close_tuple();
		}
	
#line 5041 "tmp.parser.c"
	}
	/* END OF ACTION: expected-close-tuple */
    }
}

static void
ZR131(GrammarP sid_current_grammar, TypeTupleT *ZO129, TypeTupleT *ZO130)
{
    TypeTupleT ZI129;
    TypeTupleT ZI130;

    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_TYPEMARK):
	{
	    ADVANCE_LEXER;
	    ZR148 (sid_current_grammar, &ZI129);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 353 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 5068 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR152 (sid_current_grammar);
	    ZR148 (sid_current_grammar, &ZI130);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 344 "parser.act"

		types_init(&(ZI129));
	
#line 5087 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 344 "parser.act"

		types_init(&(ZI130));
	
#line 5096 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	}
	break;
      case (ERROR_TERMINAL):
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
  ZL0:;
    /* BEGINNING OF RESULT ASSIGNMENT: TypeTupleT */
    {
#line 251 "parser.act"

		ZO129->head = ZI129.head;

		if (ZO129->head == NULL) {
			ZO129->tail = &(ZO129->head);
		} else {
			ZO129->tail= ZI129.tail ;
		}
	#line 5120 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: TypeTupleT */
    /* BEGINNING OF RESULT ASSIGNMENT: TypeTupleT */
    {
#line 251 "parser.act"

		ZO130->head = ZI130.head;

		if (ZO130->head == NULL) {
			ZO130->tail = &(ZO130->head);
		} else {
			ZO130->tail= ZI130.tail ;
		}
	#line 5134 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: TypeTupleT */
}

static void
ZR219(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI157;

	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 5153 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 226 */
	    {
		{
		    /* BEGINNING OF ACTION: current-tuple */
		    {
#line 349 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 5166 "tmp.parser.c"
		    }
		    /* END OF ACTION: current-tuple */
		    ZR300 (sid_current_grammar, &ZI157);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-tuple-or-define-or-terminator */
		    {
#line 1604 "parser.act"

		if (!sid_propagating_error) {
			E_expected_tuple_def_or_term();
		}
	
#line 5186 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-tuple-or-define-or-terminator */
		    /* BEGINNING OF ACTION: destroy-string */
		    {
#line 1679 "parser.act"

		nstring_destroy(&(ZI157));
	
#line 5195 "tmp.parser.c"
		    }
		    /* END OF ACTION: destroy-string */
		    /* BEGINNING OF ACTION: skip-to-end-of-item */
		    {
#line 1821 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HSCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 5227 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-item */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 226 */
	}
	break;
      case (LEXER_TOK_REFERENCE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 224 */
	    {
		{
		    NStringT ZI157;
		    TypeTupleT ZI205;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 5253 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL5;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: current-tuple */
		    {
#line 349 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 5267 "tmp.parser.c"
		    }
		    /* END OF ACTION: current-tuple */
		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 344 "parser.act"

		types_init(&(ZI205));
	
#line 5276 "tmp.parser.c"
		    }
		    /* END OF ACTION: init-tuple */
		    /* BEGINNING OF ACTION: add-var */
		    {
#line 473 "parser.act"

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
	
#line 5322 "tmp.parser.c"
		    }
		    /* END OF ACTION: add-var */
		    /* BEGINNING OF ACTION: save-tuple */
		    {
#line 353 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 5331 "tmp.parser.c"
		    }
		    /* END OF ACTION: save-tuple */
		    ZR225 (sid_current_grammar);
		    ZR210 (sid_current_grammar, &ZI205);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL5;
		    }
		}
		goto ZL4;
	      ZL5:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1508 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 5352 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		}
	      ZL4:;
	    }
	    /* END OF INLINE: 224 */
	}
	break;
      case (LEXER_TOK_OPEN_HTUPLE):
	{
	    TypeTupleT ZI205;

	    ZR170 (sid_current_grammar, &ZI205);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 353 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 5376 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR225 (sid_current_grammar);
	    ZR210 (sid_current_grammar, &ZI205);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_BEGIN_HACTION): case (LEXER_TOK_PRED_HRESULT): case (LEXER_TOK_IGNORE):
	{
	    /* BEGINNING OF ACTION: current-tuple */
	    {
#line 349 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 5395 "tmp.parser.c"
	    }
	    /* END OF ACTION: current-tuple */
	    ZR299 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR161(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI157;
	    EntryP ZI163;
	    TypeTupleT ZI129;
	    TypeTupleT ZI130;

	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 5433 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: terminal */
	    {
#line 291 "parser.act"

		(ZI163) = table_add_basic(grammar_table(sid_current_grammar), &(ZI157),
			sid_current_grammar, FALSE);
		if ((ZI163) == NULL) {
			E_duplicate_basic((&ZI157));
			nstring_destroy(&(ZI157));
		}
	
#line 5448 "tmp.parser.c"
	    }
	    /* END OF ACTION: terminal */
	    ZR131 (sid_current_grammar, &ZI129, &ZI130);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: x-terminal */
	    {
#line 309 "parser.act"

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
	
#line 5481 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-terminal */
	    ZR245 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_IGNORE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 165 */
	    {
		{
		    NStringT ZI157;
		    EntryP ZI163;
		    TypeTupleT ZI129;
		    TypeTupleT ZI130;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 5510 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: i-terminal */
		    {
#line 300 "parser.act"

		(ZI163) = table_add_basic(grammar_table(sid_current_grammar), &(ZI157),
			sid_current_grammar, TRUE);
		if ((ZI163) == NULL) {
			E_duplicate_basic((&ZI157));
			nstring_destroy(&(ZI157));
		}
	
#line 5529 "tmp.parser.c"
		    }
		    /* END OF ACTION: i-terminal */
		    ZR131 (sid_current_grammar, &ZI129, &ZI130);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		    /* BEGINNING OF ACTION: x-terminal */
		    {
#line 309 "parser.act"

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
	
#line 5562 "tmp.parser.c"
		    }
		    /* END OF ACTION: x-terminal */
		    ZR245 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1508 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 5582 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: skip-to-end-of-terminal-decn */
		    {
#line 1732 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 5609 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-terminal-decn */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 165 */
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-terminal-decn */
	{
#line 1520 "parser.act"

		if (!sid_propagating_error) {
			E_expected_terminal_decn();
		}
	
#line 5634 "tmp.parser.c"
	}
	/* END OF ACTION: expected-terminal-decn */
	/* BEGINNING OF ACTION: skip-to-end-of-terminal-decn */
	{
#line 1732 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 5661 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-terminal-decn */
    }
}

static void
ZR225(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_DEFINE):
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-define */
	{
#line 1598 "parser.act"

		if (!sid_propagating_error) {
			E_expected_define();
		}
	
#line 5693 "tmp.parser.c"
	}
	/* END OF ACTION: expected-define */
    }
}

static void
ZR228(GrammarP sid_current_grammar, TypeTupleT *ZI205)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI157;

	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_IDENTIFIER):
	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 5716 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF ACTION: prod-action */
	{
#line 992 "parser.act"

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
	
#line 5746 "tmp.parser.c"
	}
	/* END OF ACTION: prod-action */
	ZR229 (sid_current_grammar);
	ZR206 (sid_current_grammar, ZI205);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-identifier */
	{
#line 1508 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 5767 "tmp.parser.c"
	}
	/* END OF ACTION: expected-identifier */
	/* BEGINNING OF ACTION: skip-to-end-of-item */
	{
#line 1821 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HSCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 5799 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-item */
    }
}

static void
ZR229(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_END_HACTION):
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-end-action */
	{
#line 1574 "parser.act"

		if (!sid_propagating_error) {
			E_expected_end_action();
		}
	
#line 5831 "tmp.parser.c"
	}
	/* END OF ACTION: expected-end-action */
    }
}

static void
ZR194(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF INLINE: 196 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_BEGIN_HACTION):
		{
		    NStringT ZI157;
		    EntryP ZI163;
		    TypeTupleT ZI129;
		    TypeTupleT ZI130;

		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 5863 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: action */
		    {
#line 537 "parser.act"

		(ZI163) = scope_stack_add_action (sid_current_scope,
			grammar_table(sid_current_grammar), &(ZI157), sid_enclosing_rule,
			&sid_redefining_entry, FALSE);
		if (!(ZI163)) {
			E_duplicate_action((&ZI157));
			nstring_destroy(&(ZI157));
		}
	
#line 5883 "tmp.parser.c"
		    }
		    /* END OF ACTION: action */
		    ZR229 (sid_current_grammar);
		    ZR131 (sid_current_grammar, &ZI129, &ZI130);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		    /* BEGINNING OF ACTION: x-action */
		    {
#line 557 "parser.act"

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
	
#line 5944 "tmp.parser.c"
		    }
		    /* END OF ACTION: x-action */
		    ZR245 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		}
		break;
	      case (LEXER_TOK_IGNORE):
		{
		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_BEGIN_HACTION):
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: 199 */
		    {
			{
			    NStringT ZI157;
			    EntryP ZI163;
			    TypeTupleT ZI129;
			    TypeTupleT ZI130;

			    switch (CURRENT_TERMINAL) {
			      case (LEXER_TOK_IDENTIFIER):
				/* BEGINNING OF EXTRACT: IDENTIFIER */
				{
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 5980 "tmp.parser.c"
				}
				/* END OF EXTRACT: IDENTIFIER */
				break;
			      default:
				goto ZL5;
			    }
			    ADVANCE_LEXER;
			    /* BEGINNING OF ACTION: i-action */
			    {
#line 547 "parser.act"

		(ZI163) = scope_stack_add_action (sid_current_scope,
			grammar_table(sid_current_grammar), &(ZI157), sid_enclosing_rule,
			&sid_redefining_entry, TRUE);
		if (!(ZI163)) {
			E_duplicate_action((&ZI157));
			nstring_destroy(&(ZI157));
		}
	
#line 6000 "tmp.parser.c"
			    }
			    /* END OF ACTION: i-action */
			    ZR229 (sid_current_grammar);
			    ZR131 (sid_current_grammar, &ZI129, &ZI130);
			    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL5;
			    }
			    /* BEGINNING OF ACTION: x-action */
			    {
#line 557 "parser.act"

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
	
#line 6061 "tmp.parser.c"
			    }
			    /* END OF ACTION: x-action */
			    ZR245 (sid_current_grammar);
			    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL5;
			    }
			}
			goto ZL4;
		      ZL5:;
			{
			    /* BEGINNING OF ACTION: expected-identifier */
			    {
#line 1508 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 6081 "tmp.parser.c"
			    }
			    /* END OF ACTION: expected-identifier */
			    /* BEGINNING OF ACTION: skip-to-end-of-action-decn */
			    {
#line 1798 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_END_HSCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 6109 "tmp.parser.c"
			    }
			    /* END OF ACTION: skip-to-end-of-action-decn */
			}
		      ZL4:;
		    }
		    /* END OF INLINE: 199 */
		}
		break;
	      default:
		goto ZL3;
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: expected-identifier */
		{
#line 1508 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 6132 "tmp.parser.c"
		}
		/* END OF ACTION: expected-identifier */
		/* BEGINNING OF ACTION: skip-to-end-of-action-decn */
		{
#line 1798 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_END_HSCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 6160 "tmp.parser.c"
		}
		/* END OF ACTION: skip-to-end-of-action-decn */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 196 */
    }
}

static void
ZR239(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_239:;
    {
	ZR232 (sid_current_grammar);
	/* BEGINNING OF INLINE: 298 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_OPEN_HTUPLE): case (LEXER_TOK_BEGIN_HACTION): case (LEXER_TOK_BEGIN_HRULE):
	      case (LEXER_TOK_PRED_HRESULT): case (LEXER_TOK_IGNORE): case (LEXER_TOK_REFERENCE):
		{
		    /* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list::production-defn-non-empty-alternative */
		    goto ZL2_239;
		    /* END OF INLINE: sid-parse-grammar::production-defn-list::production-defn-non-empty-alternative */
		}
		/*UNREACHED*/
	      case (ERROR_TERMINAL):
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
	/* END OF INLINE: 298 */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-item */
	{
#line 1622 "parser.act"

		if (!sid_propagating_error) {
			E_expected_item();
		}
	
#line 6210 "tmp.parser.c"
	}
	/* END OF ACTION: expected-item */
	/* BEGINNING OF ACTION: skip-to-end-of-item */
	{
#line 1821 "parser.act"

		while (CURRENT_TERMINAL != LEXER_TOK_EOF
			&& CURRENT_TERMINAL != LEXER_TOK_TERMINATOR
			&& CURRENT_TERMINAL != LEXER_TOK_ALT_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_HANDLER_HSEP
			&& CURRENT_TERMINAL != LEXER_TOK_BEGIN_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HRULE
			&& CURRENT_TERMINAL != LEXER_TOK_END_HSCOPE
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HPRODUCTIONS
			&& CURRENT_TERMINAL != LEXER_TOK_BLT_HENTRY) {
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
	
#line 6242 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-item */
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 1943 "parser.act"

		sid_propagating_error = FALSE;
	
#line 6251 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
    }
}

static void
ZR273(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI157;

	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_IDENTIFIER):
	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 263 "parser.act"

		nstring_assign(&ZI157, lexer_string_value(sid_current_stream));
	
#line 6274 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF ACTION: add-entry */
	{
#line 1475 "parser.act"

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
	
#line 6301 "tmp.parser.c"
	}
	/* END OF ACTION: add-entry */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-identifier */
	{
#line 1508 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 6316 "tmp.parser.c"
	}
	/* END OF ACTION: expected-identifier */
    }
}

static void
ZR237(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_END_HRULE):
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-end-rule */
	{
#line 1616 "parser.act"

		if (!sid_propagating_error) {
			E_expected_end_rule();
		}
	
#line 6348 "tmp.parser.c"
	}
	/* END OF ACTION: expected-end-rule */
    }
}

static void
ZR175(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_175:;
    {
	ZR172 (sid_current_grammar, ZI133);
	/* BEGINNING OF INLINE: 177 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-close-tuple-or-skipped-or-eof */
		{
#line 1952 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == LEXER_TOK_CLOSE_HTUPLE
			|| CURRENT_TERMINAL == LEXER_TOK_EOF
			|| sid_propagating_error);
	
#line 6378 "tmp.parser.c"
		}
		/* END OF ACTION: is-close-tuple-or-skipped-or-eof */
		if (!ZI0)
		    goto ZL5;
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL5:;
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_SEPARATOR):
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list::lhs-name-tuple::lhs-name-list-1 */
		    goto ZL2_175;
		    /* END OF INLINE: sid-parse-grammar::production-defn-list::lhs-name-tuple::lhs-name-list-1 */
		}
		/*UNREACHED*/
	      default:
		goto ZL4;
	    }
	    /*UNREACHED*/
	  ZL4:;
	    {
		/* BEGINNING OF ACTION: expected-separator */
		{
#line 1526 "parser.act"

		if (!sid_propagating_error) {
			E_expected_separator();
		}
	
#line 6410 "tmp.parser.c"
		}
		/* END OF ACTION: expected-separator */
		/* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list::lhs-name-tuple::lhs-name-list-1 */
		goto ZL2_175;
		/* END OF INLINE: sid-parse-grammar::production-defn-list::lhs-name-tuple::lhs-name-list-1 */
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
	/* END OF INLINE: 177 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR245(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_TERMINATOR):
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-terminator */
	{
#line 1550 "parser.act"

		if (!sid_propagating_error) {
			E_expected_terminator();
		}
	
#line 6454 "tmp.parser.c"
	}
	/* END OF ACTION: expected-terminator */
    }
}

static void
ZR187(GrammarP sid_current_grammar, TypeTupleT *ZI133)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_187:;
    {
	ZR184 (sid_current_grammar, ZI133);
	/* BEGINNING OF INLINE: 189 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-close-tuple-or-skipped-or-eof */
		{
#line 1952 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == LEXER_TOK_CLOSE_HTUPLE
			|| CURRENT_TERMINAL == LEXER_TOK_EOF
			|| sid_propagating_error);
	
#line 6484 "tmp.parser.c"
		}
		/* END OF ACTION: is-close-tuple-or-skipped-or-eof */
		if (!ZI0)
		    goto ZL5;
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL5:;
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_SEPARATOR):
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list::rhs-name-tuple::rhs-name-list-1 */
		    goto ZL2_187;
		    /* END OF INLINE: sid-parse-grammar::production-defn-list::rhs-name-tuple::rhs-name-list-1 */
		}
		/*UNREACHED*/
	      default:
		goto ZL4;
	    }
	    /*UNREACHED*/
	  ZL4:;
	    {
		/* BEGINNING OF ACTION: expected-separator */
		{
#line 1526 "parser.act"

		if (!sid_propagating_error) {
			E_expected_separator();
		}
	
#line 6516 "tmp.parser.c"
		}
		/* END OF ACTION: expected-separator */
		/* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list::rhs-name-tuple::rhs-name-list-1 */
		goto ZL2_187;
		/* END OF INLINE: sid-parse-grammar::production-defn-list::rhs-name-tuple::rhs-name-list-1 */
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
	/* END OF INLINE: 189 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

/* BEGINNING OF TRAILER */

#line 1967 "parser.act"


#line 6539 "tmp.parser.c"

/* END OF FILE */
