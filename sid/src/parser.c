/*
 * Automatically generated from the files:
 *	parser.sid
 * and
 *	parser.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 143 "parser.act"


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

	#include <exds/common.h>
	#include <exds/exception.h>
	#include <exds/bitvec.h>
	#include <exds/dalloc.h>
	#include <exds/dstring.h>

	#include "adt/action.h"
	#include "adt/basic.h"
	#include "adt/key.h"
	#include "adt/non-local.h"
	#include "adt/rule.h"
	#include "adt/scope.h"
	#include "adt/table.h"
	#include "adt/types.h"

	#include "shared/check/check.h"
	#include "parser.h"
	#include "gen-errors.h"
	#include "grammar.h"
	#include "lexer.h"

	#define ERROR_TERMINAL (LEXER_TOK_ERROR)
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

#line 134 "tmp.parser.c"


#ifndef ERROR_TERMINAL
#error "-s no-numeric-terminals given and ERROR_TERMINAL is not defined"
#endif

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZR255(GrammarP);
static void ZR250(GrammarP);
static void ZR148(GrammarP, TypeTupleT *);
static void ZR166(GrammarP, NStringT *);
static void ZR269(GrammarP, TypeTupleT *, TypeTupleT *);
static void ZR252(GrammarP);
static void ZR187(GrammarP, TypeTupleT *);
static void ZR259(GrammarP);
static void ZR179(GrammarP, TypeTupleT *);
static void ZR158(GrammarP);
static void ZR191(GrammarP, TypeTupleT *);
static void ZR241(GrammarP);
static void ZR160(GrammarP);
static void ZR199(GrammarP, TypeTupleT *);
static void ZR211(GrammarP);
static void ZR157(GrammarP);
static void ZR181(GrammarP, TypeTupleT *);
static void ZR177(GrammarP);
extern void sid_parse_grammar(GrammarP);
static void ZR151(GrammarP, TypeTupleT *);
static void ZR153(GrammarP, TypeTupleT *);
static void ZR193(GrammarP, TypeTupleT *);
static void ZR306(GrammarP, NStringT *);
static void ZR308(GrammarP);
static void ZR219(GrammarP, TypeTupleT *);
static void ZR309(GrammarP, NStringT *);
static void ZR239(GrammarP);
static void ZR310(GrammarP, NStringT *);
static void ZR168(GrammarP);
static void ZR215(GrammarP, TypeTupleT *);
static void ZR274(GrammarP);
static void ZR139(GrammarP, TypeTupleT *);
static void ZR280(GrammarP);
static void ZR201(GrammarP);
static void ZR202(GrammarP);
static void ZR136(GrammarP, TypeTupleT *, TypeTupleT *);
static void ZR228(GrammarP);
static void ZR170(GrammarP);
static void ZR203(GrammarP);
static void ZR234(GrammarP);
static void ZR248(GrammarP);
static void ZR282(GrammarP);
static void ZR237(GrammarP, TypeTupleT *);
static void ZR238(GrammarP);
static void ZR184(GrammarP, TypeTupleT *);
static void ZR246(GrammarP);
static void ZR247(GrammarP);
static void ZR196(GrammarP, TypeTupleT *);

/* BEGINNING OF STATIC VARIABLES */

static BoolT ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZR255(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_255:;
    {
	ZR252 (sid_current_grammar);
	/* BEGINNING OF INLINE: 257 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_ALT_HSEP):
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list::production-defn-alternatives */
		    goto ZL2_255;
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
	/* END OF INLINE: 257 */
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
	/* BEGINNING OF ACTION: handler */
	{
#line 1016 "parser.act"

		if (sid_current_entry) {
			sid_current_alt = alt_create();
		}
	
#line 248 "tmp.parser.c"
	}
	/* END OF ACTION: handler */
	ZR248 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: x-handler */
	{
#line 1034 "parser.act"

		if (sid_current_entry && sid_current_alt) {
			if (types_check_names(rule_result(sid_current_rule),
				alt_names(sid_current_alt))) {
				TypeTupleT used;

				types_copy(&used, rule_result(sid_current_rule));
				item_compute_minimal_dataflow(alt_item_head(sid_current_alt),
					&used);
				types_destroy(&used);
				rule_set_handler(sid_current_rule, sid_current_alt);
			} else {
				(void) alt_deallocate(sid_current_alt);
				E_handler_result_mismatch(entry_key(sid_external_rule));
			}
		}
	
#line 276 "tmp.parser.c"
	}
	/* END OF ACTION: x-handler */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR148(GrammarP sid_current_grammar, TypeTupleT *ZI138)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_148:;
    {
	ZR139 (sid_current_grammar, ZI138);
	/* BEGINNING OF INLINE: 150 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-close-tuple-or-skipped-or-eof */
		{
#line 2046 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_CLOSE_HTUPLE)
			|| CURRENT_TERMINAL == (LEXER_TOK_EOF)
			|| sid_propagating_error);
	
#line 310 "tmp.parser.c"
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
		    goto ZL2_148;
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
#line 1620 "parser.act"

		if (!sid_propagating_error) {
			E_expected_separator();
		}
	
#line 342 "tmp.parser.c"
		}
		/* END OF ACTION: expected-separator */
		/* BEGINNING OF INLINE: sid-parse-grammar::function-type-defn::tuple-defn-list-1 */
		goto ZL2_148;
		/* END OF INLINE: sid-parse-grammar::function-type-defn::tuple-defn-list-1 */
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
	/* END OF INLINE: 150 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR166(GrammarP sid_current_grammar, NStringT *ZO165)
{
    NStringT ZI165;

    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_BASIC):
	{
	    /* BEGINNING OF EXTRACT: BASIC */
	    {
#line 270 "parser.act"

		nstring_assign(&ZI165, lexer_string_value(sid_current_stream));
	
#line 374 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: BASIC */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: x-basic */
	    {
#line 366 "parser.act"

		EntryT *entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI165));

		if (entry) {
			if (!entry_is_basic(entry)) {
				E_identifier_is_not_basic((&ZI165));
			}
		}

	
#line 391 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-basic */
	}
	break;
      case (LEXER_TOK_IDENTIFIER):
	{
	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI165, lexer_string_value(sid_current_stream));
	
#line 404 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	}
	break;
      case (ERROR_TERMINAL):
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
  ZL0:;
    /* BEGINNING OF RESULT ASSIGNMENT: StringT */
    {
#line 250 "parser.act"

		nstring_assign(ZO165, (&ZI165));
	#line 425 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: StringT */
}

static void
ZR269(GrammarP sid_current_grammar, TypeTupleT *ZI134, TypeTupleT *ZI135)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_DEFINE): case (LEXER_TOK_BEGIN_HSCOPE):
	{
	    /* BEGINNING OF ACTION: prod */
	    {
#line 823 "parser.act"

		if (sid_current_entry) {
			KeyT *key;

			key = entry_key(sid_current_entry);

			if (rule_is_defined(sid_current_rule)) {
				E_rule_already_defined(key);
				sid_current_entry = NULL;
				types_destroy((ZI134));
				types_destroy((ZI135));
			} else {
				TypeTupleT *param   = rule_param(sid_current_rule);
				TypeTupleT *result  = rule_result(sid_current_rule);
				BoolT       errored = FALSE;

				rule_defined(sid_current_rule);
				if (!types_disjoint_names((ZI134))) {
					E_rule_param_clash(key, (ZI134));
					errored = TRUE;
				}

				if (types_check_shadowing((ZI134), &sid_scope_stack,
					sid_current_rule)) {
					errored = TRUE;
				}

				if (sid_redefining_entry) {
					if (!types_fillin_names(param, (ZI134))) {
						E_rule_param_mismatch(key, param, (ZI134));
						errored = TRUE;
					}
					types_destroy((ZI134));
				} else {
					types_assign(param, (ZI134));
				}

				if (!types_disjoint_names((ZI135))) {
					E_rule_result_clash(key, (ZI135));
					errored = TRUE;
				}

				if (types_check_shadowing((ZI135), &sid_scope_stack,
					sid_current_rule)) {
					errored = TRUE;
				}

				if (types_contains_references((ZI135))) {
					E_rule_result_has_refs(key, (ZI135));
					errored = TRUE;
				}

				{
					EntryT *type;

					type = types_find_ignored((ZI134));
					if (type != NULL) {
						E_ignored_type(key_get_string(entry_key(type)));
						errored = TRUE;
					}

					type = types_find_ignored((ZI135));
					if (type != NULL) {
						E_ignored_type(key_get_string(entry_key(type)));
						errored = TRUE;
					}
				}

				if (sid_redefining_entry) {
					if (!types_fillin_names(result, (ZI135))) {
						E_rule_result_mismatch(key, result, (ZI135));
						errored = TRUE;
					}
					types_destroy((ZI135));
				} else {
					types_assign(result, (ZI135));
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
			types_destroy((ZI134));
			types_destroy((ZI135));
		}

		sid_alternative   = 0;
		sid_internal_rule = FALSE;
		sid_external_rule = sid_current_entry;
		nstring_init(&sid_maximum_scope);
	
#line 536 "tmp.parser.c"
	    }
	    /* END OF ACTION: prod */
	    /* BEGINNING OF ACTION: push-scope */
	    {
#line 928 "parser.act"

		if (sid_current_entry) {
			KeyT     *key   = entry_key(sid_current_entry);
			NStringT *scope = key_get_string(key);

			scope_stack_push(&sid_scope_stack, scope);
		}
	
#line 550 "tmp.parser.c"
	    }
	    /* END OF ACTION: push-scope */
	    ZR211 (sid_current_grammar);
	    ZR234 (sid_current_grammar);
	    /* BEGINNING OF INLINE: 271 */
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
#line 1704 "parser.act"

		if (!sid_propagating_error) {
			E_expected_begin_rule();
		}
	
#line 581 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-begin-rule */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 271 */
	    ZR239 (sid_current_grammar);
	    ZR246 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: pop-scope */
	    {
#line 934 "parser.act"

		if (sid_current_entry) {
			scope_stack_pop(&sid_scope_stack);
		}
	
#line 602 "tmp.parser.c"
	    }
	    /* END OF ACTION: pop-scope */
	    /* BEGINNING OF ACTION: x-prod */
	    {
#line 919 "parser.act"

		if (sid_current_entry) {
			nstring_assign(rule_maximum_scope(sid_current_rule),
				&sid_maximum_scope);
		} else {
			nstring_destroy(&sid_maximum_scope);
		}
	
#line 616 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-prod */
	    ZR247 (sid_current_grammar);
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
#line 756 "parser.act"

		if (sid_current_entry) {
			KeyT       *key     = entry_key(sid_current_entry);
			TypeTupleT *param   = rule_param(sid_current_rule);
			TypeTupleT *result  = rule_result(sid_current_rule);
			BoolT       errored = FALSE;

			if (types_contains_names((ZI134))) {
				E_rule_param_has_names(key, (ZI134));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(param, (ZI134))) {
					E_rule_param_mismatch(key, param, (ZI134));
					errored = TRUE;
				}
			}

			if (types_contains_names((ZI135))) {
				E_rule_result_has_names(key, (ZI135));
				errored = TRUE;
			}

			if (types_contains_references((ZI135))) {
				E_rule_result_has_refs(key, (ZI135));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(result, (ZI135))) {
					E_rule_result_mismatch(key, result, (ZI135));
					errored = TRUE;
				}
			}

			{
				EntryT *type;

				type = types_find_ignored((ZI134));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
					errored = TRUE;
				}

				type = types_find_ignored((ZI135));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
					errored = TRUE;
				}
			}

			if (errored || sid_redefining_entry) {
				types_destroy((ZI134));
				types_destroy((ZI135));
			} else {
				types_assign(param, (ZI134));
				types_assign(result, (ZI135));
			}
		} else {
			types_destroy((ZI134));
			types_destroy((ZI135));
		}
	
#line 695 "tmp.parser.c"
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
ZR252(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_EMPTY):
	{
	    /* BEGINNING OF ACTION: empty-alt */
	    {
#line 975 "parser.act"

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
				E_alt_result_mismatch(entry_key(sid_external_rule),
					sid_alternative);
			} else {
				rule_add_empty_alt(sid_current_rule);
			}
		}
	
#line 743 "tmp.parser.c"
	    }
	    /* END OF ACTION: empty-alt */
	    ADVANCE_LEXER;
	    ZR247 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_BASIC): case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_OPEN_HTUPLE): case (LEXER_TOK_BEGIN_HACTION):
      case (LEXER_TOK_BEGIN_HRULE): case (LEXER_TOK_PRED_HRESULT): case (LEXER_TOK_IGNORE): case (LEXER_TOK_REFERENCE):
	{
	    /* BEGINNING OF ACTION: non-empty-alt */
	    {
#line 991 "parser.act"

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
	
#line 775 "tmp.parser.c"
	    }
	    /* END OF ACTION: non-empty-alt */
	    ZR248 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: x-non-empty-alt */
	    {
#line 1010 "parser.act"

		if (sid_current_entry && sid_current_alt) {
			if (types_check_names(rule_result(sid_current_rule),
				alt_names(sid_current_alt))) {
				TypeTupleT used;

				types_copy(&used, rule_result(sid_current_rule));
				item_compute_minimal_dataflow(alt_item_head(sid_current_alt),
					&used);
				types_destroy(&used);
				rule_add_alt(sid_current_rule, sid_current_alt);
			} else {
				(void) alt_deallocate(sid_current_alt);
				E_alt_result_mismatch(entry_key(sid_external_rule),
					sid_alternative);
			}
		}
	
#line 804 "tmp.parser.c"
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
#line 1722 "parser.act"

		if (!sid_propagating_error) {
			E_expected_alternative();
		}
	
#line 825 "tmp.parser.c"
	}
	/* END OF ACTION: expected-alternative */
	/* BEGINNING OF ACTION: skip-to-end-of-alternative */
	{
#line 1942 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_ALT_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_HANDLER_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HSCOPE)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 855 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-alternative */
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2037 "parser.act"

		sid_propagating_error = FALSE;
	
#line 864 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
    }
}

static void
ZR187(GrammarP sid_current_grammar, TypeTupleT *ZI138)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_PRED_HRESULT): case (LEXER_TOK_IGNORE): case (LEXER_TOK_REFERENCE):
	{
	    ZR184 (sid_current_grammar, ZI138);
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
ZR259(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI163;

	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_IDENTIFIER):
	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 911 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 261 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_TYPEMARK):
		{
		    ADVANCE_LEXER;
		    ZR306 (sid_current_grammar, &ZI163);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		}
		break;
	      case (LEXER_TOK_TERMINATOR): case (LEXER_TOK_DEFINE): case (LEXER_TOK_BEGIN_HSCOPE):
		{
		    TypeTupleT ZI134;
		    TypeTupleT ZI135;

		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 382 "parser.act"

		types_init(&(ZI134));
	
#line 943 "tmp.parser.c"
		    }
		    /* END OF ACTION: init-tuple */
		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 382 "parser.act"

		types_init(&(ZI135));
	
#line 952 "tmp.parser.c"
		    }
		    /* END OF ACTION: init-tuple */
		    /* BEGINNING OF ACTION: rule */
		    {
#line 738 "parser.act"

		sid_current_entry = scope_stack_add_rule(sid_current_scope,
			grammar_table(sid_current_grammar), &(ZI163), sid_enclosing_rule,
			&sid_redefining_entry);
		if (sid_current_entry) {
			sid_current_rule = entry_get_rule(sid_current_entry);
		} else {
			E_duplicate_rule((&ZI163));
			nstring_destroy(&(ZI163));
		}
	
#line 969 "tmp.parser.c"
		    }
		    /* END OF ACTION: rule */
		    ZR269 (sid_current_grammar, &ZI134, &ZI135);
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
#line 1728 "parser.act"

		if (!sid_propagating_error) {
			E_expected_other_defn();
		}
	
#line 993 "tmp.parser.c"
		}
		/* END OF ACTION: expected-other-defn */
		/* BEGINNING OF ACTION: destroy-string */
		{
#line 1773 "parser.act"

		nstring_destroy(&(ZI163));
	
#line 1002 "tmp.parser.c"
		}
		/* END OF ACTION: destroy-string */
		/* BEGINNING OF ACTION: skip-to-end-of-other-defn */
		{
#line 1967 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HSCOPE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 1031 "tmp.parser.c"
		}
		/* END OF ACTION: skip-to-end-of-other-defn */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 261 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR179(GrammarP sid_current_grammar, TypeTupleT *ZO138)
{
    TypeTupleT ZI138;

    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF ACTION: current-tuple */
	{
#line 387 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 1060 "tmp.parser.c"
	}
	/* END OF ACTION: current-tuple */
	ZR201 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 382 "parser.act"

		types_init(&(ZI138));
	
#line 1074 "tmp.parser.c"
	}
	/* END OF ACTION: init-tuple */
	ZR187 (sid_current_grammar, &ZI138);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2037 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1088 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	ZR202 (sid_current_grammar);
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
#line 254 "parser.act"

		ZO138->head = ZI138.head;

		if (ZO138->head == NULL) {
			ZO138->tail = &ZO138->head;
		} else {
			ZO138->tail= ZI138.tail ;
		}
	#line 1113 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: TypeTupleT */
}

static void
ZR158(GrammarP sid_current_grammar)
{
  ZL2_158:;
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_IGNORE):
	{
	    ZR160 (sid_current_grammar);
	    /* BEGINNING OF INLINE: sid-parse-grammar::type-decl-list */
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_158;
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
ZR191(GrammarP sid_current_grammar, TypeTupleT *ZO138)
{
    TypeTupleT ZI138;

    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF ACTION: current-tuple */
	{
#line 387 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 1162 "tmp.parser.c"
	}
	/* END OF ACTION: current-tuple */
	ZR201 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 382 "parser.act"

		types_init(&(ZI138));
	
#line 1176 "tmp.parser.c"
	}
	/* END OF ACTION: init-tuple */
	ZR199 (sid_current_grammar, &ZI138);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2037 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1190 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	ZR202 (sid_current_grammar);
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
#line 254 "parser.act"

		ZO138->head = ZI138.head;

		if (ZO138->head == NULL) {
			ZO138->tail = &ZO138->head;
		} else {
			ZO138->tail= ZI138.tail ;
		}
	#line 1215 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: TypeTupleT */
}

static void
ZR241(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_BEGIN_HRULE):
	{
	    EntryP ZI172;
	    RuleP ZI75;
	    AltP ZI243;
	    BoolT ZI244;
	    ItemP ZI245;

	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: save */
	    {
#line 1037 "parser.act"

		(ZI172)      = sid_current_entry;
		(ZI75)       = sid_current_rule;
		(ZI243)        = sid_current_alt;
		(ZI244)   = sid_internal_rule;
		(ZI245)             = NULL;
		sid_internal_rule = TRUE;

		if (sid_current_entry && sid_current_alt) {
			sid_current_entry = table_add_generated_rule(grammar_table(sid_current_grammar), FALSE);
			sid_current_rule  = entry_get_rule(sid_current_entry);
			(ZI245)             = item_create(sid_current_entry);

			rule_defined(sid_current_rule);
			item_inlinable((ZI245));
			types_copy(item_param((ZI245)), rule_param((ZI75)));
			types_append_copy(item_param((ZI245)), alt_names((ZI243)));
			types_copy(rule_param(sid_current_rule), item_param((ZI245)));
			types_make_references(rule_param(sid_current_rule), item_param((ZI245)));
			alt_add_item((ZI243), (ZI245));
		} else {
			sid_current_entry = NULL;
		}
	
#line 1260 "tmp.parser.c"
	    }
	    /* END OF ACTION: save */
	    ZR239 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: restore */
	    {
#line 1062 "parser.act"

		if ((ZI172) && (ZI243)) {
			rule_compute_result_intersect(sid_current_rule);
			types_copy(item_result((ZI245)), rule_result(sid_current_rule));
			types_add_new_names(alt_names((ZI243)), item_result((ZI245)),
			grammar_get_predicate_id(sid_current_grammar));
		}

		sid_internal_rule = (ZI244);
		sid_current_alt   = (ZI243);
		sid_current_rule  = (ZI75);
		sid_current_entry = (ZI172);
	
#line 1284 "tmp.parser.c"
	    }
	    /* END OF ACTION: restore */
	    ZR246 (sid_current_grammar);
	    ZR247 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_BASIC): case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_OPEN_HTUPLE): case (LEXER_TOK_BEGIN_HACTION):
      case (LEXER_TOK_PRED_HRESULT): case (LEXER_TOK_IGNORE): case (LEXER_TOK_REFERENCE):
	{
	    ZR228 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 2037 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1309 "tmp.parser.c"
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
ZR160(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF INLINE: 162 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_IDENTIFIER):
		{
		    NStringT ZI163;

		    /* BEGINNING OF EXTRACT: IDENTIFIER */
		    {
#line 266 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 1345 "tmp.parser.c"
		    }
		    /* END OF EXTRACT: IDENTIFIER */
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: add-type */
		    {
#line 286 "parser.act"

		if (table_add_type(grammar_table(sid_current_grammar), &(ZI163), FALSE) == NULL) {
			E_duplicate_type((&ZI163));
			nstring_destroy(&(ZI163));
		}
	
#line 1358 "tmp.parser.c"
		    }
		    /* END OF ACTION: add-type */
		}
		break;
	      case (LEXER_TOK_IGNORE):
		{
		    NStringT ZI163;

		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 1376 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: i-add-type */
		    {
#line 293 "parser.act"

		if (table_add_type(grammar_table(sid_current_grammar), &(ZI163), TRUE) == NULL) {
			E_duplicate_type((&ZI163));
			nstring_destroy(&(ZI163));
		}
	
#line 1393 "tmp.parser.c"
		    }
		    /* END OF ACTION: i-add-type */
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
#line 1596 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 1412 "tmp.parser.c"
		}
		/* END OF ACTION: expected-identifier */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 162 */
	ZR247 (sid_current_grammar);
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
ZR199(GrammarP sid_current_grammar, TypeTupleT *ZI138)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_REFERENCE):
	{
	    ZR196 (sid_current_grammar, ZI138);
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
ZR211(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_BEGIN_HSCOPE):
	{
	    EntryP ZI172;
	    RuleP ZI75;

	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: save-scope */
	    {
#line 937 "parser.act"

		(ZI172) = sid_current_entry;
		(ZI75)  = sid_enclosing_rule;

		sid_enclosing_rule = sid_current_rule;
	
#line 1474 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-scope */
	    ZR177 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: restore-scope */
	    {
#line 944 "parser.act"

		sid_current_entry  = (ZI172);
		sid_current_rule   = sid_enclosing_rule;
		sid_enclosing_rule = (ZI75);
		sid_alternative    = 0;
		sid_internal_rule  = FALSE;
		sid_external_rule  = sid_current_entry;

		nstring_init(&sid_maximum_scope);
	
#line 1495 "tmp.parser.c"
	    }
	    /* END OF ACTION: restore-scope */
	    /* BEGINNING OF INLINE: 213 */
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
#line 1674 "parser.act"

		if (!sid_propagating_error) {
			E_expected_end_scope();
		}
	
#line 1520 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-end-scope */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 213 */
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
ZR157(GrammarP sid_current_grammar)
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
#line 1638 "parser.act"

		if (!sid_propagating_error) {
			E_expected_arrow();
		}
	
#line 1566 "tmp.parser.c"
	}
	/* END OF ACTION: expected-arrow */
    }
}

static void
ZR181(GrammarP sid_current_grammar, TypeTupleT *ZI138)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI163;

	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 1586 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: add-name */
	    {
#line 430 "parser.act"

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI163), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI163));

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
			types_add_name_and_type((ZI138), name_entry, NULL, FALSE);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI163));
		} else if (non_local_entry) {
			types_add_name_and_type((ZI138), non_local_entry, NULL, FALSE);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI163));
		} else {
			types_add_name((ZI138), grammar_table(sid_current_grammar), &(ZI163), FALSE);
		}
	
#line 1632 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-name */
	}
	break;
      case (LEXER_TOK_IGNORE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: add-void */
	    {
#line 558 "parser.act"

		EntryT *entry;

		entry = table_add_generated_name(grammar_table(sid_current_grammar));
		types_add_name_entry((ZI138), entry);
	
#line 1649 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-void */
	}
	break;
      case (LEXER_TOK_PRED_HRESULT):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: add-pred */
	    {
#line 551 "parser.act"

		if (sid_current_pred_id) {
			E_multi_predicate_return();
		}
		sid_current_pred_id = TRUE;
		types_add_name_entry((ZI138), grammar_get_predicate_id(sid_current_grammar));
	
#line 1667 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-pred */
	}
	break;
      case (LEXER_TOK_REFERENCE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 183 */
	    {
		{
		    NStringT ZI163;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 1688 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: add-var */
		    {
#line 511 "parser.act"

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI163), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI163));

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
			types_add_name_and_type_var((ZI138), name_entry, NULL);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI163));
		} else if (non_local_entry) {
			types_add_name_and_type_var((ZI138), non_local_entry, NULL);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI163));
		} else {
			E_undefined_assignment((&ZI163));
			types_add_name((ZI138), grammar_table(sid_current_grammar), &(ZI163), FALSE);
		}
	
#line 1739 "tmp.parser.c"
		    }
		    /* END OF ACTION: add-var */
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1596 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 1754 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 183 */
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
#line 1650 "parser.act"

		if (!sid_propagating_error) {
			E_expected_lhs_name();
		}
	
#line 1779 "tmp.parser.c"
	}
	/* END OF ACTION: expected-lhs-name */
	/* BEGINNING OF ACTION: skip-to-end-of-lhs-name */
	{
#line 1848 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 1806 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-lhs-name */
    }
}

static void
ZR177(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_177:;
    {
	ZR274 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2037 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1831 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	/* BEGINNING OF INLINE: 278 */
	{
	    {
		/* BEGINNING OF ACTION: is-blt-entry-or-end-scope-or-eof */
		{
#line 2040 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_EOF)
			|| CURRENT_TERMINAL == (LEXER_TOK_END_HSCOPE)
			|| CURRENT_TERMINAL == (LEXER_TOK_BLT_HENTRY));
	
#line 1845 "tmp.parser.c"
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
		    goto ZL2_177;
		    /* END OF INLINE: sid-parse-grammar::production-defn-list */
		}
		/*UNREACHED*/
	      default:
		goto ZL1;
	    }
	  ZL3:;
	}
	/* END OF INLINE: 278 */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-production-defn */
	{
#line 1734 "parser.act"

		if (!sid_propagating_error) {
			E_expected_production_defn();
		}
	
#line 1880 "tmp.parser.c"
	}
	/* END OF ACTION: expected-production-defn */
	/* BEGINNING OF ACTION: skip-to-end-of-production-defn */
	{
#line 1991 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HSCOPE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 1909 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-production-defn */
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2037 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1918 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	/* BEGINNING OF INLINE: 279 */
	{
	    {
		/* BEGINNING OF ACTION: is-blt-entry-or-end-scope-or-eof */
		{
#line 2040 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_EOF)
			|| CURRENT_TERMINAL == (LEXER_TOK_END_HSCOPE)
			|| CURRENT_TERMINAL == (LEXER_TOK_BLT_HENTRY));
	
#line 1932 "tmp.parser.c"
		}
		/* END OF ACTION: is-blt-entry-or-end-scope-or-eof */
		if (!ZI0)
		    goto ZL7;
	    }
	    goto ZL6;
	  ZL7:;
	    {
		/* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list */
		goto ZL2_177;
		/* END OF INLINE: sid-parse-grammar::production-defn-list */
	    }
	    /*UNREACHED*/
	  ZL6:;
	}
	/* END OF INLINE: 279 */
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
#line 278 "parser.act"

		scope_stack_init(&sid_scope_stack);
		scope_stack_init(&sid_global_scope);
	
#line 1966 "tmp.parser.c"
	}
	/* END OF ACTION: init */
	/* BEGINNING OF INLINE: 285 */
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
#line 1740 "parser.act"

		if (!sid_propagating_error) {
			E_expected_blt_types();
		}
	
#line 1991 "tmp.parser.c"
		}
		/* END OF ACTION: expected-blt-types */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 285 */
	ZR158 (sid_current_grammar);
	/* BEGINNING OF INLINE: 286 */
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
#line 1746 "parser.act"

		if (!sid_propagating_error) {
			E_expected_blt_terminals();
		}
	
#line 2025 "tmp.parser.c"
		}
		/* END OF ACTION: expected-blt-terminals */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 286 */
	ZR168 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: x-terminals */
	{
#line 363 "parser.act"

		unsigned max_terminal = grammar_max_terminal(sid_current_grammar);

		bitvec_set_size(max_terminal);
		sid_finished_terminals = TRUE;
	
#line 2046 "tmp.parser.c"
	}
	/* END OF ACTION: x-terminals */
	/* BEGINNING OF INLINE: 287 */
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
#line 1752 "parser.act"

		if (!sid_propagating_error) {
			E_expected_blt_productions();
		}
	
#line 2071 "tmp.parser.c"
		}
		/* END OF ACTION: expected-blt-productions */
	    }
	  ZL6:;
	}
	/* END OF INLINE: 287 */
	ZR177 (sid_current_grammar);
	/* BEGINNING OF INLINE: 288 */
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
#line 1758 "parser.act"

		if (!sid_propagating_error) {
			E_expected_blt_entry();
		}
	
#line 2105 "tmp.parser.c"
		}
		/* END OF ACTION: expected-blt-entry */
	    }
	  ZL8:;
	}
	/* END OF INLINE: 288 */
	ZR280 (sid_current_grammar);
	ZR247 (sid_current_grammar);
	/* BEGINNING OF INLINE: 290 */
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
#line 1764 "parser.act"

		if (!sid_propagating_error) {
			E_expected_eof();
		}
	
#line 2140 "tmp.parser.c"
		}
		/* END OF ACTION: expected-eof */
	    }
	  ZL10:;
	}
	/* END OF INLINE: 290 */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: unhandled-syntax-error */
	{
#line 1584 "parser.act"

		UNREACHED;
	
#line 2157 "tmp.parser.c"
	}
	/* END OF ACTION: unhandled-syntax-error */
    }
}

static void
ZR151(GrammarP sid_current_grammar, TypeTupleT *ZI138)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_TYPEMARK):
	{
	    ZR148 (sid_current_grammar, ZI138);
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
ZR153(GrammarP sid_current_grammar, TypeTupleT *ZO138)
{
    TypeTupleT ZI138;

    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 382 "parser.act"

		types_init(&(ZI138));
	
#line 2202 "tmp.parser.c"
	}
	/* END OF ACTION: init-tuple */
	ZR201 (sid_current_grammar);
	ZR151 (sid_current_grammar, &ZI138);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2037 "parser.act"

		sid_propagating_error = FALSE;
	
#line 2217 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	ZR202 (sid_current_grammar);
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
#line 254 "parser.act"

		ZO138->head = ZI138.head;

		if (ZO138->head == NULL) {
			ZO138->tail = &ZO138->head;
		} else {
			ZO138->tail= ZI138.tail ;
		}
	#line 2242 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: TypeTupleT */
}

static void
ZR193(GrammarP sid_current_grammar, TypeTupleT *ZI138)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI163;

	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 2261 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: add-name */
	    {
#line 430 "parser.act"

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI163), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI163));

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
			types_add_name_and_type((ZI138), name_entry, NULL, FALSE);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI163));
		} else if (non_local_entry) {
			types_add_name_and_type((ZI138), non_local_entry, NULL, FALSE);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI163));
		} else {
			types_add_name((ZI138), grammar_table(sid_current_grammar), &(ZI163), FALSE);
		}
	
#line 2307 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-name */
	}
	break;
      case (LEXER_TOK_REFERENCE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 195 */
	    {
		{
		    NStringT ZI163;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 2328 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: add-ref-name */
		    {
#line 471 "parser.act"

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI163), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI163));

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
			types_add_name_and_type ((ZI138), name_entry, NULL, TRUE);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI163));
		} else if (non_local_entry) {
			types_add_name_and_type ((ZI138), non_local_entry, NULL, TRUE);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI163));
		} else {
			types_add_name((ZI138), grammar_table(sid_current_grammar), &(ZI163), TRUE);
		}
	
#line 2378 "tmp.parser.c"
		    }
		    /* END OF ACTION: add-ref-name */
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1596 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 2393 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: skip-to-end-of-rhs-name */
		    {
#line 1870 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 2420 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-rhs-name */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 195 */
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
#line 1656 "parser.act"

		if (!sid_propagating_error) {
			E_expected_rhs_name();
		}
	
#line 2445 "tmp.parser.c"
	}
	/* END OF ACTION: expected-rhs-name */
	/* BEGINNING OF ACTION: skip-to-end-of-rhs-name */
	{
#line 1870 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 2472 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-rhs-name */
    }
}

static void
ZR306(GrammarP sid_current_grammar, NStringT *ZI163)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_OPEN_HTUPLE):
	{
	    TypeTupleT ZI134;
	    TypeTupleT ZI135;

	    ZR153 (sid_current_grammar, &ZI134);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 391 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2498 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR157 (sid_current_grammar);
	    ZR153 (sid_current_grammar, &ZI135);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: rule */
	    {
#line 738 "parser.act"

		sid_current_entry = scope_stack_add_rule(sid_current_scope,
			grammar_table(sid_current_grammar), &(*ZI163), sid_enclosing_rule,
			&sid_redefining_entry);
		if (sid_current_entry) {
			sid_current_rule = entry_get_rule(sid_current_entry);
		} else {
			E_duplicate_rule((ZI163));
			nstring_destroy(&(*ZI163));
		}
	
#line 2521 "tmp.parser.c"
	    }
	    /* END OF ACTION: rule */
	    ZR269 (sid_current_grammar, &ZI134, &ZI135);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_IDENTIFIER):
	{
	    /* BEGINNING OF INLINE: 262 */
	    {
		{
		    NStringT ZI144;
		    NonLocalEntryP ZI263;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI144, lexer_string_value(sid_current_stream));
	
#line 2547 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: non-local */
		    {
#line 663 "parser.act"

		(ZI263) = NULL;
		if (sid_enclosing_rule == NULL || sid_current_scope == &sid_global_scope) {
			E_global_scope_non_local((ZI163));
			nstring_destroy(&(*ZI163));
		} else {
			EntryT *type;

			type = table_get_type(grammar_table(sid_current_grammar), (&ZI144));
			if (type == NULL) {
				E_unknown_type((&ZI144));
				nstring_destroy(&(*ZI163));
			} else {
				EntryT *name;

				name = scope_stack_add_non_local(sid_current_scope,
					grammar_table(sid_current_grammar), &(*ZI163), type,
					sid_enclosing_rule);
				if (name) {
					NonLocalListT *non_locals;

					non_locals = rule_non_locals(sid_enclosing_rule);
					(ZI263) = non_local_list_add(non_locals, name, type);
				} else {
					E_duplicate_non_local((ZI163));
					nstring_destroy(&(*ZI163));
				}
			}
		}
		nstring_destroy(&(ZI144));
	
#line 2589 "tmp.parser.c"
		    }
		    /* END OF ACTION: non-local */
		    /* BEGINNING OF INLINE: 264 */
		    {
			switch (CURRENT_TERMINAL) {
			  case (LEXER_TOK_DEFINE):
			    {
				ADVANCE_LEXER;
				/* BEGINNING OF INLINE: 265 */
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
#line 1662 "parser.act"

		if (!sid_propagating_error) {
			E_expected_begin_action();
		}
	
#line 2620 "tmp.parser.c"
					}
					/* END OF ACTION: expected-begin-action */
				    }
				  ZL6:;
				}
				/* END OF INLINE: 265 */
				/* BEGINNING OF INLINE: 266 */
				{
				    {
					NStringT ZI56;

					switch (CURRENT_TERMINAL) {
					  case (LEXER_TOK_IDENTIFIER):
					    /* BEGINNING OF EXTRACT: IDENTIFIER */
					    {
#line 266 "parser.act"

		nstring_assign(&ZI56, lexer_string_value(sid_current_stream));
	
#line 2640 "tmp.parser.c"
					    }
					    /* END OF EXTRACT: IDENTIFIER */
					    break;
					  default:
					    goto ZL9;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: non-local-init */
					{
#line 698 "parser.act"

		EntryT *actionentry;

		actionentry = scope_stack_get_action(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI56));

		if (actionentry == NULL) {
			E_unknown_action((&ZI56));
		} else if ((ZI263)) {
			EntryT     *type   = non_local_entry_get_type((ZI263));
			KeyT       *name   = entry_key(non_local_entry_get_name((ZI263)));
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
			non_local_entry_set_initialiser((ZI263), actionentry);
		}
		nstring_destroy(&(ZI56));
	
#line 2692 "tmp.parser.c"
					}
					/* END OF ACTION: non-local-init */
					ZR238 (sid_current_grammar);
					ZR247 (sid_current_grammar);
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
#line 1596 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 2713 "tmp.parser.c"
					}
					/* END OF ACTION: expected-identifier */
				    }
				  ZL8:;
				}
				/* END OF INLINE: 266 */
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
#line 1770 "parser.act"

		if (!sid_propagating_error) {
			E_expected_terminator_or_define();
		}
	
#line 2741 "tmp.parser.c"
			    }
			    /* END OF ACTION: expected-terminator-or-define */
			}
		      ZL4:;
		    }
		    /* END OF INLINE: 264 */
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1596 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 2760 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: destroy-string */
		    {
#line 1773 "parser.act"

		nstring_destroy(&(*ZI163));
	
#line 2769 "tmp.parser.c"
		    }
		    /* END OF ACTION: destroy-string */
		    /* BEGINNING OF ACTION: skip-to-end-of-other-defn */
		    {
#line 1967 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HSCOPE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 2798 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-other-defn */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 262 */
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
ZR308(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IGNORE):
	{
	    TypeTupleT ZI214;

	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 382 "parser.act"

		types_init(&(ZI214));
	
#line 2833 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: add-void */
	    {
#line 558 "parser.act"

		EntryT *entry;

		entry = table_add_generated_name(grammar_table(sid_current_grammar));
		types_add_name_entry((&ZI214), entry);
	
#line 2845 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-void */
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 391 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2854 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR234 (sid_current_grammar);
	    ZR219 (sid_current_grammar, &ZI214);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_PRED_HRESULT):
	{
	    TypeTupleT ZI214;

	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 382 "parser.act"

		types_init(&(ZI214));
	
#line 2876 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: add-pred */
	    {
#line 551 "parser.act"

		if (sid_current_pred_id) {
			E_multi_predicate_return();
		}
		sid_current_pred_id = TRUE;
		types_add_name_entry((&ZI214), grammar_get_predicate_id(sid_current_grammar));
	
#line 2889 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-pred */
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 391 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2898 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR234 (sid_current_grammar);
	    ZR219 (sid_current_grammar, &ZI214);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_BEGIN_HACTION):
	{
	    TypeTupleT ZI214;

	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 391 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2919 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 382 "parser.act"

		types_init(&(ZI214));
	
#line 2928 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    ADVANCE_LEXER;
	    ZR237 (sid_current_grammar, &ZI214);
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
ZR219(GrammarP sid_current_grammar, TypeTupleT *ZI214)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_BEGIN_HACTION):
	{
	    ADVANCE_LEXER;
	    ZR237 (sid_current_grammar, ZI214);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_BASIC): case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI163;

	    ZR166 (sid_current_grammar, &ZI163);
	    /* BEGINNING OF INLINE: 223 */
	    {
		switch (CURRENT_TERMINAL) {
		  case (LEXER_TOK_OPEN_HTUPLE):
		    {
			TypeTupleT ZI217;

			ZR191 (sid_current_grammar, &ZI217);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			    RESTORE_LEXER;
			    goto ZL3;
			}
			/* BEGINNING OF ACTION: x-prod-rule */
			{
#line 1251 "parser.act"

		TypeTupleT *param  = NULL;
		TypeTupleT *result = NULL;
		EntryT     *entry  = NULL;
		RuleT      *rule;
		BasicT     *basic;

		if (sid_current_entry && sid_current_alt) {
			entry = scope_stack_get_rule(&sid_scope_stack,
				grammar_table(sid_current_grammar), (&ZI163));
			if (entry) {
				sid_current_item = item_create(entry);
				rule             = entry_get_rule(entry);
				param            = rule_param(rule);
				result           = rule_result(rule);
			} else {
				entry = table_get_basic(grammar_table(sid_current_grammar), (&ZI163));
				if (entry) {
					sid_current_item = item_create(entry);
					basic            = entry_get_basic(entry);
					param            = NULL;
					result           = basic_result(basic);

					if (basic_get_ignored(basic)) {
						E_ignored_basic_call((&ZI163));
					}
				} else {
					E_unknown_rule_or_basic((&ZI163));
					sid_current_item = NULL;
				}
			}
		} else {
			sid_current_item = NULL;
		}

		nstring_destroy(&(ZI163));
		if (sid_current_item) {
			BoolT  errored = FALSE;
			KeyT  *key     = entry_key(entry);

			if (types_resolve((&ZI217), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (param) {
					if (types_equal((&ZI217), param)) {
						item_add_param(sid_current_item, (&ZI217));
					} else {
						E_rule_param_call_mismatch(key, param, (&ZI217));
						types_destroy((&ZI217));
						errored = TRUE;
					}
				} else {
					if (!types_equal_zero_tuple((&ZI217))) {
						E_basic_param_call_mismatch(key, (&ZI217));
						types_destroy((&ZI217));
						errored = TRUE;
					}
				}
			} else {
				types_destroy((&ZI217));
				errored = TRUE;
			}

			if (types_disjoint_names((ZI214))) {
				if (types_check_undefined((ZI214), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((ZI214), result)) {
						types_add_new_names(alt_names(sid_current_alt),
							(ZI214), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							E_predicate ();
						}
						item_add_result(sid_current_item, (ZI214));
					} else {
						if (param) {
							E_rule_result_call_mismatch(key, result, (ZI214));
						} else {
							E_basic_result_call_mismatch(key, result, (ZI214));
						}
						types_destroy((ZI214));
						errored = TRUE;
					}
				} else {
					types_destroy((ZI214));
					errored = TRUE;
				}
			} else {
				if (param) {
					E_rule_result_call_clash(key, (ZI214));
				} else {
					E_basic_result_call_clash(key, (ZI214));
				}

				types_destroy((ZI214));
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
			types_destroy((ZI214));
			types_destroy((&ZI217));
		}
	
#line 3099 "tmp.parser.c"
			}
			/* END OF ACTION: x-prod-rule */
			ZR247 (sid_current_grammar);
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
#line 387 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 3117 "tmp.parser.c"
			}
			/* END OF ACTION: current-tuple */
			/* BEGINNING OF ACTION: x-prod-rule-or-identity */
			{
#line 1359 "parser.act"

		EntryT     *name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI163));
		EntryT     *entry      = NULL;
		TypeTupleT *param      = NULL;
		TypeTupleT *result     = NULL;
		RuleT      *rule;
		BasicT     *basic;
		TypeTupleT  rhs;

		types_init(&rhs);

		if (sid_current_entry && sid_current_alt) {
			if (name_entry != NULL &&
				!types_contains(alt_names(sid_current_alt), name_entry) &&
				!types_contains(rule_param(sid_current_rule), name_entry)) {
				name_entry = NULL;
			}

			entry = scope_stack_get_rule(&sid_scope_stack, grammar_table(sid_current_grammar),
				(&ZI163));
			if (entry) {
				sid_current_item = item_create (entry);
				rule             = entry_get_rule (entry);
				param            = rule_param(rule);
				result           = rule_result(rule);
			} else {
				entry = table_get_basic(grammar_table(sid_current_grammar), (&ZI163));
				if (entry) {
					sid_current_item = item_create (entry);
					basic            = entry_get_basic(entry);
					param            = NULL;
					result           = basic_result(basic);
					if (name_entry == NULL && basic_get_ignored(basic)) {
						E_ignored_basic_call((&ZI163));
					}
				}
			}

			if (entry == NULL && name_entry == NULL) {
				NStringT scope;

				name_entry = scope_stack_get_non_local(&sid_scope_stack,
					grammar_table(sid_current_grammar), (&ZI163), &scope);
				if (name_entry) {
					if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
						nstring_destroy(&sid_maximum_scope);
						nstring_assign(&sid_maximum_scope, &scope);
					} else {
						nstring_destroy(&scope);
					}
				} else {
					E_unknown_rule_or_basic((&ZI163));
				}
			} else if (entry != NULL && name_entry != NULL) {
				E_ambiguous_call((&ZI163));
				entry      = NULL;
				name_entry = NULL;
			}
		} else {
			name_entry = NULL;
		}
		nstring_destroy(&(ZI163));

		if (entry) {
			BoolT  errored = FALSE;
			KeyT  *key     = entry_key(entry);

			if (types_resolve(&rhs, rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (param) {
					if (types_equal(&rhs, param)) {
						item_add_param(sid_current_item, &rhs);
					} else {
						E_rule_param_call_mismatch(key, param, &rhs);
						types_destroy(&rhs);
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

			if (types_disjoint_names((ZI214))) {
				if (types_check_undefined((ZI214), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((ZI214), result)) {
						types_add_new_names(alt_names(sid_current_alt),
							(ZI214), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							E_predicate();
						}
						item_add_result(sid_current_item, (ZI214));
					} else {
						if (param) {
							E_rule_result_call_mismatch(key, result, (ZI214));
						} else {
							E_basic_result_call_mismatch(key, result, (ZI214));
						}
						types_destroy((ZI214));
						errored = TRUE;
					}
				} else {
					types_destroy((ZI214));
					errored = TRUE;
				}
			} else {
				if (param) {
					E_rule_result_call_clash(key, (ZI214));
				} else {
					E_basic_result_call_clash(key, (ZI214));
				}
				types_destroy((ZI214));
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
			if (types_resolve(&rhs, rule_param(sid_current_rule),
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

			if (types_disjoint_names((ZI214))) {
				if (types_check_undefined((ZI214), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (sid_current_item) {
						if (types_fillin_types((ZI214), item_param(sid_current_item))) {
							types_add_new_names(alt_names(sid_current_alt),
								(ZI214), grammar_get_predicate_id(sid_current_grammar));
							if (sid_saved_pred_id) {
								E_predicate();
							}
							item_add_result(sid_current_item, (ZI214));
							alt_add_item(sid_current_alt, sid_current_item);
						} else {
							E_identity_mismatch(item_param(sid_current_item), (ZI214));
							types_destroy((ZI214));
							(void) item_deallocate(sid_current_item);
							sid_current_item = NULL;
						}
					}
				} else {
					types_destroy((ZI214));
					if (sid_current_item) {
						(void) item_deallocate(sid_current_item);
						sid_current_item = NULL;
					}
				}
			} else {
				E_identity_result_clash((ZI214));
				types_destroy((ZI214));
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
			types_destroy((ZI214));
			types_destroy(&rhs);
		}
	
#line 3324 "tmp.parser.c"
			}
			/* END OF ACTION: x-prod-rule-or-identity */
			ADVANCE_LEXER;
		    }
		    break;
		  case (ERROR_TERMINAL):
		    RESTORE_LEXER;
		    goto ZL3;
		  default:
		    goto ZL3;
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-tuple-or-terminator */
		    {
#line 1680 "parser.act"

		if (!sid_propagating_error) {
			E_expected_tuple_or_term();
		}
	
#line 3347 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-tuple-or-terminator */
		    /* BEGINNING OF ACTION: destroy-string */
		    {
#line 1773 "parser.act"

		nstring_destroy(&(ZI163));
	
#line 3356 "tmp.parser.c"
		    }
		    /* END OF ACTION: destroy-string */
		    /* BEGINNING OF ACTION: skip-to-end-of-item */
		    {
#line 1915 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_ALT_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_HANDLER_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_BEGIN_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HSCOPE)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 3388 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-item */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 223 */
	}
	break;
      case (LEXER_TOK_OPEN_HTUPLE):
	{
	    TypeTupleT ZI217;

	    ZR191 (sid_current_grammar, &ZI217);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: x-identity */
	    {
#line 1179 "parser.act"

		if (sid_current_entry && sid_current_alt) {
			EntryT *entry = table_add_rename(grammar_table(sid_current_grammar));

			if (types_resolve((&ZI217), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_contains_references((&ZI217))) {
					E_identity_param_has_refs((&ZI217), entry_key(sid_external_rule),
						sid_alternative);
					types_destroy((&ZI217));
					sid_current_item = NULL;
				} else {
					sid_current_item = item_create(entry);
					item_add_param(sid_current_item, (&ZI217));
				}
			} else {
				types_destroy((&ZI217));
				sid_current_item = NULL;
			}

			if (types_disjoint_names((ZI214))) {
				if (types_check_undefined((ZI214), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (sid_current_item) {
						if (types_fillin_types((ZI214), item_param(sid_current_item))) {
							types_add_new_names(alt_names(sid_current_alt),
							(ZI214), grammar_get_predicate_id(sid_current_grammar));
							if (sid_saved_pred_id) {
								E_predicate();
							}
							item_add_result(sid_current_item, (ZI214));
							alt_add_item(sid_current_alt, sid_current_item);
						} else {
							E_identity_mismatch(item_param(sid_current_item), (ZI214));
							types_destroy((ZI214));
							(void) item_deallocate(sid_current_item);
							sid_current_item = NULL;
						}
					}
				} else {
					types_destroy((ZI214));
					if (sid_current_item) {
						(void) item_deallocate(sid_current_item);
						sid_current_item = NULL;
					}
				}
			} else {
				E_identity_result_clash((ZI214));
				types_destroy((ZI214));
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
			types_destroy((ZI214));
			types_destroy((&ZI217));
		}
	
#line 3475 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-identity */
	    ZR247 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_REFERENCE):
	{
	    TypeTupleT ZI217;

	    /* BEGINNING OF ACTION: current-tuple */
	    {
#line 387 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 3495 "tmp.parser.c"
	    }
	    /* END OF ACTION: current-tuple */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 382 "parser.act"

		types_init(&(ZI217));
	
#line 3505 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF INLINE: 225 */
	    {
		{
		    NStringT ZI163;

		    ZR166 (sid_current_grammar, &ZI163);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL5;
		    }
		    /* BEGINNING OF ACTION: add-ref-name */
		    {
#line 471 "parser.act"

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI163), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI163));

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
			types_add_name_and_type ((&ZI217), name_entry, NULL, TRUE);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI163));
		} else if (non_local_entry) {
			types_add_name_and_type ((&ZI217), non_local_entry, NULL, TRUE);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI163));
		} else {
			types_add_name((&ZI217), grammar_table(sid_current_grammar), &(ZI163), TRUE);
		}
	
#line 3560 "tmp.parser.c"
		    }
		    /* END OF ACTION: add-ref-name */
		    /* BEGINNING OF ACTION: x-identity */
		    {
#line 1179 "parser.act"

		if (sid_current_entry && sid_current_alt) {
			EntryT *entry = table_add_rename(grammar_table(sid_current_grammar));

			if (types_resolve((&ZI217), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_contains_references((&ZI217))) {
					E_identity_param_has_refs((&ZI217), entry_key(sid_external_rule),
						sid_alternative);
					types_destroy((&ZI217));
					sid_current_item = NULL;
				} else {
					sid_current_item = item_create(entry);
					item_add_param(sid_current_item, (&ZI217));
				}
			} else {
				types_destroy((&ZI217));
				sid_current_item = NULL;
			}

			if (types_disjoint_names((ZI214))) {
				if (types_check_undefined((ZI214), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (sid_current_item) {
						if (types_fillin_types((ZI214), item_param(sid_current_item))) {
							types_add_new_names(alt_names(sid_current_alt),
							(ZI214), grammar_get_predicate_id(sid_current_grammar));
							if (sid_saved_pred_id) {
								E_predicate();
							}
							item_add_result(sid_current_item, (ZI214));
							alt_add_item(sid_current_alt, sid_current_item);
						} else {
							E_identity_mismatch(item_param(sid_current_item), (ZI214));
							types_destroy((ZI214));
							(void) item_deallocate(sid_current_item);
							sid_current_item = NULL;
						}
					}
				} else {
					types_destroy((ZI214));
					if (sid_current_item) {
						(void) item_deallocate(sid_current_item);
						sid_current_item = NULL;
					}
				}
			} else {
				E_identity_result_clash((ZI214));
				types_destroy((ZI214));
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
			types_destroy((ZI214));
			types_destroy((&ZI217));
		}
	
#line 3632 "tmp.parser.c"
		    }
		    /* END OF ACTION: x-identity */
		    ZR247 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL5;
		    }
		}
		goto ZL4;
	      ZL5:;
		{
		    /* BEGINNING OF ACTION: expected-identifier-or-basic */
		    {
#line 1602 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier_or_basic();
		}
	
#line 3652 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier-or-basic */
		    /* BEGINNING OF ACTION: skip-to-end-of-item */
		    {
#line 1915 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_ALT_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_HANDLER_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_BEGIN_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HSCOPE)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 3684 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-item */
		}
	      ZL4:;
	    }
	    /* END OF INLINE: 225 */
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
#line 1686 "parser.act"

		if (!sid_propagating_error) {
			E_expected_item_rhs();
		}
	
#line 3709 "tmp.parser.c"
	}
	/* END OF ACTION: expected-item-rhs */
	/* BEGINNING OF ACTION: skip-to-end-of-item */
	{
#line 1915 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_ALT_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_HANDLER_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_BEGIN_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HSCOPE)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 3741 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-item */
    }
}

static void
ZR309(GrammarP sid_current_grammar, NStringT *ZI163)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_DEFINE):
	{
	    TypeTupleT ZI214;

	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 382 "parser.act"

		types_init(&(ZI214));
	
#line 3761 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: add-name */
	    {
#line 430 "parser.act"

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (ZI163), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (ZI163));

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
			types_add_name_and_type((&ZI214), name_entry, NULL, FALSE);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(*ZI163));
		} else if (non_local_entry) {
			types_add_name_and_type((&ZI214), non_local_entry, NULL, FALSE);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(*ZI163));
		} else {
			types_add_name((&ZI214), grammar_table(sid_current_grammar), &(*ZI163), FALSE);
		}
	
#line 3806 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-name */
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 391 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 3815 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ADVANCE_LEXER;
	    ZR219 (sid_current_grammar, &ZI214);
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
#line 391 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 3834 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR310 (sid_current_grammar, ZI163);
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
ZR239(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	ZR255 (sid_current_grammar);
	/* BEGINNING OF INLINE: 258 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_HANDLER_HSEP):
		{
		    ADVANCE_LEXER;
		    ZR250 (sid_current_grammar);
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
	/* END OF INLINE: 258 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR310(GrammarP sid_current_grammar, NStringT *ZI163)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_TERMINATOR):
	{
	    TypeTupleT ZI214;
	    TypeTupleT ZI217;

	    /* BEGINNING OF ACTION: current-tuple */
	    {
#line 387 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 3906 "tmp.parser.c"
	    }
	    /* END OF ACTION: current-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 382 "parser.act"

		types_init(&(ZI214));
	
#line 3915 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 382 "parser.act"

		types_init(&(ZI217));
	
#line 3924 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: x-prod-rule */
	    {
#line 1251 "parser.act"

		TypeTupleT *param  = NULL;
		TypeTupleT *result = NULL;
		EntryT     *entry  = NULL;
		RuleT      *rule;
		BasicT     *basic;

		if (sid_current_entry && sid_current_alt) {
			entry = scope_stack_get_rule(&sid_scope_stack,
				grammar_table(sid_current_grammar), (ZI163));
			if (entry) {
				sid_current_item = item_create(entry);
				rule             = entry_get_rule(entry);
				param            = rule_param(rule);
				result           = rule_result(rule);
			} else {
				entry = table_get_basic(grammar_table(sid_current_grammar), (ZI163));
				if (entry) {
					sid_current_item = item_create(entry);
					basic            = entry_get_basic(entry);
					param            = NULL;
					result           = basic_result(basic);

					if (basic_get_ignored(basic)) {
						E_ignored_basic_call((ZI163));
					}
				} else {
					E_unknown_rule_or_basic((ZI163));
					sid_current_item = NULL;
				}
			}
		} else {
			sid_current_item = NULL;
		}

		nstring_destroy(&(*ZI163));
		if (sid_current_item) {
			BoolT  errored = FALSE;
			KeyT  *key     = entry_key(entry);

			if (types_resolve((&ZI217), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (param) {
					if (types_equal((&ZI217), param)) {
						item_add_param(sid_current_item, (&ZI217));
					} else {
						E_rule_param_call_mismatch(key, param, (&ZI217));
						types_destroy((&ZI217));
						errored = TRUE;
					}
				} else {
					if (!types_equal_zero_tuple((&ZI217))) {
						E_basic_param_call_mismatch(key, (&ZI217));
						types_destroy((&ZI217));
						errored = TRUE;
					}
				}
			} else {
				types_destroy((&ZI217));
				errored = TRUE;
			}

			if (types_disjoint_names((&ZI214))) {
				if (types_check_undefined((&ZI214), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((&ZI214), result)) {
						types_add_new_names(alt_names(sid_current_alt),
							(&ZI214), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							E_predicate ();
						}
						item_add_result(sid_current_item, (&ZI214));
					} else {
						if (param) {
							E_rule_result_call_mismatch(key, result, (&ZI214));
						} else {
							E_basic_result_call_mismatch(key, result, (&ZI214));
						}
						types_destroy((&ZI214));
						errored = TRUE;
					}
				} else {
					types_destroy((&ZI214));
					errored = TRUE;
				}
			} else {
				if (param) {
					E_rule_result_call_clash(key, (&ZI214));
				} else {
					E_basic_result_call_clash(key, (&ZI214));
				}

				types_destroy((&ZI214));
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
			types_destroy((&ZI214));
			types_destroy((&ZI217));
		}
	
#line 4045 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-prod-rule */
	    ADVANCE_LEXER;
	}
	break;
      case (LEXER_TOK_OPEN_HTUPLE):
	{
	    TypeTupleT ZI214;
	    TypeTupleT ZI217;

	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 382 "parser.act"

		types_init(&(ZI214));
	
#line 4062 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    ZR191 (sid_current_grammar, &ZI217);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: x-prod-rule */
	    {
#line 1251 "parser.act"

		TypeTupleT *param  = NULL;
		TypeTupleT *result = NULL;
		EntryT     *entry  = NULL;
		RuleT      *rule;
		BasicT     *basic;

		if (sid_current_entry && sid_current_alt) {
			entry = scope_stack_get_rule(&sid_scope_stack,
				grammar_table(sid_current_grammar), (ZI163));
			if (entry) {
				sid_current_item = item_create(entry);
				rule             = entry_get_rule(entry);
				param            = rule_param(rule);
				result           = rule_result(rule);
			} else {
				entry = table_get_basic(grammar_table(sid_current_grammar), (ZI163));
				if (entry) {
					sid_current_item = item_create(entry);
					basic            = entry_get_basic(entry);
					param            = NULL;
					result           = basic_result(basic);

					if (basic_get_ignored(basic)) {
						E_ignored_basic_call((ZI163));
					}
				} else {
					E_unknown_rule_or_basic((ZI163));
					sid_current_item = NULL;
				}
			}
		} else {
			sid_current_item = NULL;
		}

		nstring_destroy(&(*ZI163));
		if (sid_current_item) {
			BoolT  errored = FALSE;
			KeyT  *key     = entry_key(entry);

			if (types_resolve((&ZI217), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (param) {
					if (types_equal((&ZI217), param)) {
						item_add_param(sid_current_item, (&ZI217));
					} else {
						E_rule_param_call_mismatch(key, param, (&ZI217));
						types_destroy((&ZI217));
						errored = TRUE;
					}
				} else {
					if (!types_equal_zero_tuple((&ZI217))) {
						E_basic_param_call_mismatch(key, (&ZI217));
						types_destroy((&ZI217));
						errored = TRUE;
					}
				}
			} else {
				types_destroy((&ZI217));
				errored = TRUE;
			}

			if (types_disjoint_names((&ZI214))) {
				if (types_check_undefined((&ZI214), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((&ZI214), result)) {
						types_add_new_names(alt_names(sid_current_alt),
							(&ZI214), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							E_predicate ();
						}
						item_add_result(sid_current_item, (&ZI214));
					} else {
						if (param) {
							E_rule_result_call_mismatch(key, result, (&ZI214));
						} else {
							E_basic_result_call_mismatch(key, result, (&ZI214));
						}
						types_destroy((&ZI214));
						errored = TRUE;
					}
				} else {
					types_destroy((&ZI214));
					errored = TRUE;
				}
			} else {
				if (param) {
					E_rule_result_call_clash(key, (&ZI214));
				} else {
					E_basic_result_call_clash(key, (&ZI214));
				}

				types_destroy((&ZI214));
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
			types_destroy((&ZI214));
			types_destroy((&ZI217));
		}
	
#line 4188 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-prod-rule */
	    ZR247 (sid_current_grammar);
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
ZR168(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_168:;
    {
	ZR170 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2037 "parser.act"

		sid_propagating_error = FALSE;
	
#line 4228 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	/* BEGINNING OF INLINE: 176 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_BASIC): case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_IGNORE):
		{
		    /* BEGINNING OF INLINE: sid-parse-grammar::terminal-decn-list */
		    goto ZL2_168;
		    /* END OF INLINE: sid-parse-grammar::terminal-decn-list */
		}
		/*UNREACHED*/
	      default:
		break;
	    }
	}
	/* END OF INLINE: 176 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR215(GrammarP sid_current_grammar, TypeTupleT *ZI214)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_OPEN_HTUPLE):
	{
	    TypeTupleT ZI217;

	    ZR191 (sid_current_grammar, &ZI217);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: x-prod-action */
	    {
#line 1105 "parser.act"

		if (sid_current_item) {
			BoolT    errored = FALSE;
			EntryT  *entry   = item_entry(sid_current_item);
			ActionT *action  = entry_get_action(entry);

			if (action_get_ignored(action)) {
				E_ignored_action_call(key_get_string(entry_key(entry)));
			}

			if (types_resolve((&ZI217), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_equal((&ZI217), action_param(action))) {
					item_add_param(sid_current_item, (&ZI217));
				} else {
					E_action_param_call_mismatch(entry_key(entry),
							  action_param(action), (&ZI217));
					types_destroy((&ZI217));
					errored = TRUE;
				}
			} else {
				types_destroy((&ZI217));
				errored = TRUE;
			}

			if (types_disjoint_names((ZI214))) {
				if (types_check_undefined((ZI214), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((ZI214), action_result(action))) {
						types_add_new_names(alt_names(sid_current_alt),
							(ZI214), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							BoolT   reference;
							EntryT *type;

							type = types_find_name_type((ZI214),
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
						item_add_result(sid_current_item, (ZI214));
					} else {
						E_action_result_call_mismatch(entry_key(entry),
							action_result(action), (ZI214));
						types_destroy((ZI214));
						errored = TRUE;
					}
				} else {
					types_destroy((ZI214));
					errored = TRUE;
				}
			} else {
				E_action_result_call_clash(entry_key(entry), (ZI214));
				types_destroy((ZI214));
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
			types_destroy((ZI214));
			types_destroy((&ZI217));
		}
	
#line 4348 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-prod-action */
	    ZR247 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_TERMINATOR):
	{
	    TypeTupleT ZI217;

	    /* BEGINNING OF ACTION: current-tuple */
	    {
#line 387 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 4368 "tmp.parser.c"
	    }
	    /* END OF ACTION: current-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 382 "parser.act"

		types_init(&(ZI217));
	
#line 4377 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: x-prod-action */
	    {
#line 1105 "parser.act"

		if (sid_current_item) {
			BoolT    errored = FALSE;
			EntryT  *entry   = item_entry(sid_current_item);
			ActionT *action  = entry_get_action(entry);

			if (action_get_ignored(action)) {
				E_ignored_action_call(key_get_string(entry_key(entry)));
			}

			if (types_resolve((&ZI217), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_equal((&ZI217), action_param(action))) {
					item_add_param(sid_current_item, (&ZI217));
				} else {
					E_action_param_call_mismatch(entry_key(entry),
							  action_param(action), (&ZI217));
					types_destroy((&ZI217));
					errored = TRUE;
				}
			} else {
				types_destroy((&ZI217));
				errored = TRUE;
			}

			if (types_disjoint_names((ZI214))) {
				if (types_check_undefined((ZI214), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((ZI214), action_result(action))) {
						types_add_new_names(alt_names(sid_current_alt),
							(ZI214), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							BoolT   reference;
							EntryT *type;

							type = types_find_name_type((ZI214),
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
						item_add_result(sid_current_item, (ZI214));
					} else {
						E_action_result_call_mismatch(entry_key(entry),
							action_result(action), (ZI214));
						types_destroy((ZI214));
						errored = TRUE;
					}
				} else {
					types_destroy((ZI214));
					errored = TRUE;
				}
			} else {
				E_action_result_call_clash(entry_key(entry), (ZI214));
				types_destroy((ZI214));
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
			types_destroy((ZI214));
			types_destroy((&ZI217));
		}
	
#line 4462 "tmp.parser.c"
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
#line 1680 "parser.act"

		if (!sid_propagating_error) {
			E_expected_tuple_or_term();
		}
	
#line 4484 "tmp.parser.c"
	}
	/* END OF ACTION: expected-tuple-or-terminator */
	/* BEGINNING OF ACTION: skip-to-end-of-item */
	{
#line 1915 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_ALT_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_HANDLER_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_BEGIN_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HSCOPE)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 4516 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-item */
    }
}

static void
ZR274(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF INLINE: 276 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_SCOPEMARK):
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: use-global */
		    {
#line 568 "parser.act"

		sid_current_scope = &sid_global_scope;
	
#line 4541 "tmp.parser.c"
		    }
		    /* END OF ACTION: use-global */
		}
		break;
	      default:
		{
		    /* BEGINNING OF ACTION: use-local */
		    {
#line 572 "parser.act"

		sid_current_scope = &sid_scope_stack;
	
#line 4554 "tmp.parser.c"
		    }
		    /* END OF ACTION: use-local */
		}
		break;
	    }
	}
	/* END OF INLINE: 276 */
	/* BEGINNING OF INLINE: 277 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_BEGIN_HACTION): case (LEXER_TOK_IGNORE):
		{
		    ZR203 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case (LEXER_TOK_IDENTIFIER):
		{
		    ZR259 (sid_current_grammar);
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
	/* END OF INLINE: 277 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR139(GrammarP sid_current_grammar, TypeTupleT *ZI138)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI141;

	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI141, lexer_string_value(sid_current_stream));
	
#line 4609 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 142 */
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
#line 1590 "parser.act"

		if (!sid_propagating_error) {
			E_expected_typemark();
		}
	
#line 4635 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-typemark */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 142 */
	    /* BEGINNING OF INLINE: 143 */
	    {
		{
		    NStringT ZI144;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI144, lexer_string_value(sid_current_stream));
	
#line 4655 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL5;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: 145 */
		    {
			switch (CURRENT_TERMINAL) {
			  case (LEXER_TOK_REFERENCE):
			    {
				ADVANCE_LEXER;
				/* BEGINNING OF ACTION: tuple-ref-name */
				{
#line 402 "parser.act"

		if (!types_add_typed_name((ZI138), grammar_table(sid_current_grammar),
			&(ZI141), (&ZI144), TRUE)) {
			E_unknown_type((&ZI144));
		}
		nstring_destroy(&(ZI144));
	
#line 4679 "tmp.parser.c"
				}
				/* END OF ACTION: tuple-ref-name */
			    }
			    break;
			  default:
			    {
				/* BEGINNING OF ACTION: tuple-name */
				{
#line 394 "parser.act"

		if (!types_add_typed_name((ZI138), grammar_table(sid_current_grammar),
			&(ZI141), (&ZI144), FALSE)) {
			E_unknown_type((&ZI144));
		}
		nstring_destroy(&(ZI144));
	
#line 4696 "tmp.parser.c"
				}
				/* END OF ACTION: tuple-name */
			    }
			    break;
			}
		    }
		    /* END OF INLINE: 145 */
		}
		goto ZL4;
	      ZL5:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1596 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 4716 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: destroy-string */
		    {
#line 1773 "parser.act"

		nstring_destroy(&(ZI141));
	
#line 4725 "tmp.parser.c"
		    }
		    /* END OF ACTION: destroy-string */
		    /* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
		    {
#line 1779 "parser.act"

		if (sid_finished_terminals) {
			while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
				&& CURRENT_TERMINAL != (LEXER_TOK_DEFINE)
				&& CURRENT_TERMINAL != (LEXER_TOK_BEGIN_HSCOPE)
				&& CURRENT_TERMINAL != (LEXER_TOK_BEGIN_HRULE)
				&& CURRENT_TERMINAL != (LEXER_TOK_SEPARATOR)
				&& CURRENT_TERMINAL != (LEXER_TOK_CLOSE_HTUPLE)
				&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
				&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
				if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
					nstring_destroy(lexer_string_value(sid_current_stream));
				}
				ADVANCE_LEXER;
			}

			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}

			if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
				ADVANCE_LEXER;
			}
		} else {
			while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
				&& CURRENT_TERMINAL != (LEXER_TOK_SEPARATOR)
				&& CURRENT_TERMINAL != (LEXER_TOK_CLOSE_HTUPLE)
				&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
				&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
				&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
				if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
					nstring_destroy(lexer_string_value (sid_current_stream));
				}
				ADVANCE_LEXER;
			}

			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value (sid_current_stream));
			}

			if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
				ADVANCE_LEXER;
			}
		}

		sid_propagating_error = TRUE;
	
#line 4778 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-tuple-defn */
		}
	      ZL4:;
	    }
	    /* END OF INLINE: 143 */
	}
	break;
      case (LEXER_TOK_TYPEMARK):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 146 */
	    {
		{
		    NStringT ZI144;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI144, lexer_string_value(sid_current_stream));
	
#line 4803 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL8;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: 147 */
		    {
			switch (CURRENT_TERMINAL) {
			  case (LEXER_TOK_REFERENCE):
			    {
				ADVANCE_LEXER;
				/* BEGINNING OF ACTION: tuple-ref-type */
				{
#line 418 "parser.act"

		if (!types_add_type((ZI138), grammar_table(sid_current_grammar), (&ZI144), TRUE)) {
			E_unknown_type((&ZI144));
		}
		nstring_destroy(&(ZI144));
	
#line 4826 "tmp.parser.c"
				}
				/* END OF ACTION: tuple-ref-type */
			    }
			    break;
			  default:
			    {
				/* BEGINNING OF ACTION: tuple-type */
				{
#line 410 "parser.act"

		if (!types_add_type((ZI138), grammar_table(sid_current_grammar), (&ZI144),
			FALSE)) {
			E_unknown_type((&ZI144));
		}
		nstring_destroy(&(ZI144));
	
#line 4843 "tmp.parser.c"
				}
				/* END OF ACTION: tuple-type */
			    }
			    break;
			}
		    }
		    /* END OF INLINE: 147 */
		}
		goto ZL7;
	      ZL8:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1596 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 4863 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
		    {
#line 1779 "parser.act"

		if (sid_finished_terminals) {
			while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
				&& CURRENT_TERMINAL != (LEXER_TOK_DEFINE)
				&& CURRENT_TERMINAL != (LEXER_TOK_BEGIN_HSCOPE)
				&& CURRENT_TERMINAL != (LEXER_TOK_BEGIN_HRULE)
				&& CURRENT_TERMINAL != (LEXER_TOK_SEPARATOR)
				&& CURRENT_TERMINAL != (LEXER_TOK_CLOSE_HTUPLE)
				&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
				&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
				if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
					nstring_destroy(lexer_string_value(sid_current_stream));
				}
				ADVANCE_LEXER;
			}

			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}

			if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
				ADVANCE_LEXER;
			}
		} else {
			while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
				&& CURRENT_TERMINAL != (LEXER_TOK_SEPARATOR)
				&& CURRENT_TERMINAL != (LEXER_TOK_CLOSE_HTUPLE)
				&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
				&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
				&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
				if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
					nstring_destroy(lexer_string_value (sid_current_stream));
				}
				ADVANCE_LEXER;
			}

			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value (sid_current_stream));
			}

			if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
				ADVANCE_LEXER;
			}
		}

		sid_propagating_error = TRUE;
	
#line 4916 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-tuple-defn */
		}
	      ZL7:;
	    }
	    /* END OF INLINE: 146 */
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
#line 1608 "parser.act"

		if (!sid_propagating_error) {
			E_expected_tuple_defn();
		}
	
#line 4941 "tmp.parser.c"
	}
	/* END OF ACTION: expected-tuple-defn */
	/* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
	{
#line 1779 "parser.act"

		if (sid_finished_terminals) {
			while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
				&& CURRENT_TERMINAL != (LEXER_TOK_DEFINE)
				&& CURRENT_TERMINAL != (LEXER_TOK_BEGIN_HSCOPE)
				&& CURRENT_TERMINAL != (LEXER_TOK_BEGIN_HRULE)
				&& CURRENT_TERMINAL != (LEXER_TOK_SEPARATOR)
				&& CURRENT_TERMINAL != (LEXER_TOK_CLOSE_HTUPLE)
				&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
				&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
				if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
					nstring_destroy(lexer_string_value(sid_current_stream));
				}
				ADVANCE_LEXER;
			}

			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}

			if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
				ADVANCE_LEXER;
			}
		} else {
			while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
				&& CURRENT_TERMINAL != (LEXER_TOK_SEPARATOR)
				&& CURRENT_TERMINAL != (LEXER_TOK_CLOSE_HTUPLE)
				&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
				&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
				&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
				if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
					nstring_destroy(lexer_string_value (sid_current_stream));
				}
				ADVANCE_LEXER;
			}

			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value (sid_current_stream));
			}

			if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
				ADVANCE_LEXER;
			}
		}

		sid_propagating_error = TRUE;
	
#line 4994 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-tuple-defn */
    }
}

static void
ZR280(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_280:;
    {
	ZR282 (sid_current_grammar);
	/* BEGINNING OF INLINE: 283 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-terminator */
		{
#line 2052 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_TERMINATOR));
	
#line 5022 "tmp.parser.c"
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
		    goto ZL2_280;
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
#line 1620 "parser.act"

		if (!sid_propagating_error) {
			E_expected_separator();
		}
	
#line 5054 "tmp.parser.c"
		}
		/* END OF ACTION: expected-separator */
		/* BEGINNING OF ACTION: skip-to-end-of-entry-list */
		{
#line 2015 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_SEPARATOR)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 5080 "tmp.parser.c"
		}
		/* END OF ACTION: skip-to-end-of-entry-list */
		/* BEGINNING OF ACTION: skip-recover */
		{
#line 2037 "parser.act"

		sid_propagating_error = FALSE;
	
#line 5089 "tmp.parser.c"
		}
		/* END OF ACTION: skip-recover */
		/* BEGINNING OF INLINE: 284 */
		{
		    {
			/* BEGINNING OF ACTION: is-not-separator */
			{
#line 2056 "parser.act"

		(ZI0) = (CURRENT_TERMINAL != (LEXER_TOK_SEPARATOR));
	
#line 5101 "tmp.parser.c"
			}
			/* END OF ACTION: is-not-separator */
			if (!ZI0)
			    goto ZL7;
		    }
		    goto ZL6;
		  ZL7:;
		    {
			/* BEGINNING OF INLINE: sid-parse-grammar::entry-list */
			goto ZL2_280;
			/* END OF INLINE: sid-parse-grammar::entry-list */
		    }
		    /*UNREACHED*/
		  ZL6:;
		}
		/* END OF INLINE: 284 */
	    }
	  ZL3:;
	}
	/* END OF INLINE: 283 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR201(GrammarP sid_current_grammar)
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
#line 1626 "parser.act"

		if (!sid_propagating_error) {
			E_expected_open_tuple();
		}
	
#line 5155 "tmp.parser.c"
	}
	/* END OF ACTION: expected-open-tuple */
    }
}

static void
ZR202(GrammarP sid_current_grammar)
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
#line 1632 "parser.act"

		if (!sid_propagating_error) {
			E_expected_close_tuple();
		}
	
#line 5187 "tmp.parser.c"
	}
	/* END OF ACTION: expected-close-tuple */
    }
}

static void
ZR136(GrammarP sid_current_grammar, TypeTupleT *ZO134, TypeTupleT *ZO135)
{
    TypeTupleT ZI134;
    TypeTupleT ZI135;

    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_TYPEMARK):
	{
	    ADVANCE_LEXER;
	    ZR153 (sid_current_grammar, &ZI134);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 391 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 5214 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR157 (sid_current_grammar);
	    ZR153 (sid_current_grammar, &ZI135);
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
#line 382 "parser.act"

		types_init(&(ZI134));
	
#line 5233 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 382 "parser.act"

		types_init(&(ZI135));
	
#line 5242 "tmp.parser.c"
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
#line 254 "parser.act"

		ZO134->head = ZI134.head;

		if (ZO134->head == NULL) {
			ZO134->tail = &ZO134->head;
		} else {
			ZO134->tail= ZI134.tail ;
		}
	#line 5266 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: TypeTupleT */
    /* BEGINNING OF RESULT ASSIGNMENT: TypeTupleT */
    {
#line 254 "parser.act"

		ZO135->head = ZI135.head;

		if (ZO135->head == NULL) {
			ZO135->tail = &ZO135->head;
		} else {
			ZO135->tail= ZI135.tail ;
		}
	#line 5280 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: TypeTupleT */
}

static void
ZR228(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_REFERENCE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 233 */
	    {
		{
		    NStringT ZI163;
		    TypeTupleT ZI214;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 5306 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: current-tuple */
		    {
#line 387 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 5320 "tmp.parser.c"
		    }
		    /* END OF ACTION: current-tuple */
		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 382 "parser.act"

		types_init(&(ZI214));
	
#line 5329 "tmp.parser.c"
		    }
		    /* END OF ACTION: init-tuple */
		    /* BEGINNING OF ACTION: add-var */
		    {
#line 511 "parser.act"

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI163), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI163));

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
			types_add_name_and_type_var((&ZI214), name_entry, NULL);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI163));
		} else if (non_local_entry) {
			types_add_name_and_type_var((&ZI214), non_local_entry, NULL);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI163));
		} else {
			E_undefined_assignment((&ZI163));
			types_add_name((&ZI214), grammar_table(sid_current_grammar), &(ZI163), FALSE);
		}
	
#line 5375 "tmp.parser.c"
		    }
		    /* END OF ACTION: add-var */
		    /* BEGINNING OF ACTION: save-tuple */
		    {
#line 391 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 5384 "tmp.parser.c"
		    }
		    /* END OF ACTION: save-tuple */
		    ZR234 (sid_current_grammar);
		    ZR219 (sid_current_grammar, &ZI214);
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
#line 1596 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 5405 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 233 */
	}
	break;
      case (LEXER_TOK_BASIC): case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI163;

	    ZR166 (sid_current_grammar, &ZI163);
	    /* BEGINNING OF INLINE: 235 */
	    {
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{
		    /* BEGINNING OF ACTION: current-tuple */
		    {
#line 387 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 5432 "tmp.parser.c"
		    }
		    /* END OF ACTION: current-tuple */
		    ZR309 (sid_current_grammar, &ZI163);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL5;
		    }
		}
		goto ZL4;
	      ZL5:;
		{
		    /* BEGINNING OF ACTION: expected-tuple-or-define-or-terminator */
		    {
#line 1698 "parser.act"

		if (!sid_propagating_error) {
			E_expected_tuple_def_or_term();
		}
	
#line 5452 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-tuple-or-define-or-terminator */
		    /* BEGINNING OF ACTION: destroy-string */
		    {
#line 1773 "parser.act"

		nstring_destroy(&(ZI163));
	
#line 5461 "tmp.parser.c"
		    }
		    /* END OF ACTION: destroy-string */
		    /* BEGINNING OF ACTION: skip-to-end-of-item */
		    {
#line 1915 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_ALT_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_HANDLER_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_BEGIN_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HSCOPE)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 5493 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-item */
		}
	      ZL4:;
	    }
	    /* END OF INLINE: 235 */
	}
	break;
      case (LEXER_TOK_OPEN_HTUPLE):
	{
	    TypeTupleT ZI214;

	    ZR179 (sid_current_grammar, &ZI214);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 391 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 5517 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR234 (sid_current_grammar);
	    ZR219 (sid_current_grammar, &ZI214);
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
#line 387 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 5536 "tmp.parser.c"
	    }
	    /* END OF ACTION: current-tuple */
	    ZR308 (sid_current_grammar);
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
ZR170(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IGNORE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 174 */
	    {
		{
		    NStringT ZI163;
		    EntryP ZI172;
		    TypeTupleT ZI134;
		    TypeTupleT ZI135;

		    ZR166 (sid_current_grammar, &ZI163);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		    /* BEGINNING OF ACTION: i-terminal */
		    {
#line 314 "parser.act"

		(ZI172) = table_add_basic(grammar_table(sid_current_grammar), &(ZI163),
			sid_current_grammar, TRUE);
		if ((ZI172) == NULL) {
			E_duplicate_basic((&ZI163));
			nstring_destroy(&(ZI163));
		}
	
#line 5588 "tmp.parser.c"
		    }
		    /* END OF ACTION: i-terminal */
		    ZR136 (sid_current_grammar, &ZI134, &ZI135);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		    /* BEGINNING OF ACTION: x-terminal */
		    {
#line 323 "parser.act"

		if ((ZI172)) {
			KeyT *key = entry_key((ZI172));
			BasicT *basic = entry_get_basic((ZI172));
			if (types_contains_names((&ZI134))) {
				E_basic_param_has_names(key, (&ZI134));
			}
			if (types_contains_names((&ZI135))) {
				E_basic_result_has_names(key, (&ZI135));
			}
			if (types_contains_references((&ZI135))) {
				E_basic_result_has_refs(key, (&ZI135));
			}
			if (!types_equal_zero_tuple((&ZI134))) {
				E_basic_param_mismatch(key, (&ZI134));
			}
			if (!basic_get_ignored(basic)) {
				EntryT *type;

				type = types_find_ignored((&ZI134));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
				}

				type = types_find_ignored((&ZI135));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
				}
			}
			types_assign(basic_result(basic), (&ZI135));
		} else {
			types_destroy((&ZI135));
		}
		types_destroy((&ZI134));
	
#line 5634 "tmp.parser.c"
		    }
		    /* END OF ACTION: x-terminal */
		    ZR247 (sid_current_grammar);
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
#line 1596 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 5654 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: skip-to-end-of-terminal-decn */
		    {
#line 1826 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 5681 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-terminal-decn */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 174 */
	}
	break;
      case (LEXER_TOK_BASIC): case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI163;
	    EntryP ZI172;
	    TypeTupleT ZI134;
	    TypeTupleT ZI135;

	    ZR166 (sid_current_grammar, &ZI163);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: terminal */
	    {
#line 305 "parser.act"

		(ZI172) = table_add_basic(grammar_table(sid_current_grammar), &(ZI163),
			sid_current_grammar, FALSE);
		if ((ZI172) == NULL) {
			E_duplicate_basic((&ZI163));
			nstring_destroy(&(ZI163));
		}
	
#line 5713 "tmp.parser.c"
	    }
	    /* END OF ACTION: terminal */
	    ZR136 (sid_current_grammar, &ZI134, &ZI135);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: x-terminal */
	    {
#line 323 "parser.act"

		if ((ZI172)) {
			KeyT *key = entry_key((ZI172));
			BasicT *basic = entry_get_basic((ZI172));
			if (types_contains_names((&ZI134))) {
				E_basic_param_has_names(key, (&ZI134));
			}
			if (types_contains_names((&ZI135))) {
				E_basic_result_has_names(key, (&ZI135));
			}
			if (types_contains_references((&ZI135))) {
				E_basic_result_has_refs(key, (&ZI135));
			}
			if (!types_equal_zero_tuple((&ZI134))) {
				E_basic_param_mismatch(key, (&ZI134));
			}
			if (!basic_get_ignored(basic)) {
				EntryT *type;

				type = types_find_ignored((&ZI134));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
				}

				type = types_find_ignored((&ZI135));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
				}
			}
			types_assign(basic_result(basic), (&ZI135));
		} else {
			types_destroy((&ZI135));
		}
		types_destroy((&ZI134));
	
#line 5759 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-terminal */
	    ZR247 (sid_current_grammar);
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
    {
	/* BEGINNING OF ACTION: expected-terminal-decn */
	{
#line 1614 "parser.act"

		if (!sid_propagating_error) {
			E_expected_terminal_decn();
		}
	
#line 5785 "tmp.parser.c"
	}
	/* END OF ACTION: expected-terminal-decn */
	/* BEGINNING OF ACTION: skip-to-end-of-terminal-decn */
	{
#line 1826 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 5812 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-terminal-decn */
    }
}

static void
ZR203(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF INLINE: 205 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_BEGIN_HACTION):
		{
		    NStringT ZI163;
		    EntryP ZI172;
		    TypeTupleT ZI134;
		    TypeTupleT ZI135;

		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 5844 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: action */
		    {
#line 575 "parser.act"

		(ZI172) = scope_stack_add_action(sid_current_scope,
			grammar_table(sid_current_grammar), &(ZI163), sid_enclosing_rule,
			&sid_redefining_entry, FALSE);
			sid_current_entry = (ZI172);
		if (!(ZI172)) {
			E_duplicate_action((&ZI163));
			nstring_destroy(&(ZI163));
		}
	
#line 5865 "tmp.parser.c"
		    }
		    /* END OF ACTION: action */
		    ZR238 (sid_current_grammar);
		    ZR136 (sid_current_grammar, &ZI134, &ZI135);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		    /* BEGINNING OF ACTION: x-action */
		    {
#line 597 "parser.act"

		if ((ZI172)) {
			KeyT       *key     = entry_key(sid_current_entry);
			ActionT    *action  = entry_get_action((ZI172));
			TypeTupleT *param   = action_param(action);
			TypeTupleT *result  = action_result(action);
			BoolT       errored = FALSE;

			if (types_contains_names((&ZI134))) {
				E_action_param_has_names(key, (&ZI134));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(param, (&ZI134))) {
					E_action_param_mismatch(key, param, (&ZI134));
					errored = TRUE;
				}
			}

			if (types_contains_names((&ZI135))) {
				E_action_result_has_names(key, (&ZI135));
				errored = TRUE;
			}

			if (types_contains_references((&ZI135))) {
				E_action_result_has_refs(key, (&ZI135));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(result, (&ZI135))) {
					E_action_result_mismatch(key, result, (&ZI135));
					errored = TRUE;
				}
			}

			if (!action_get_ignored(action)) {
				EntryT *type;

				type = types_find_ignored((&ZI134));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
					errored = TRUE;
				}

				type = types_find_ignored((&ZI135));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
					errored = TRUE;
				}
			}

			if (errored || sid_redefining_entry) {
				types_destroy((&ZI134));
				types_destroy((&ZI135));
			} else {
				types_assign(param, (&ZI134));
				types_assign(result, (&ZI135));
			}
		} else {
			types_destroy((&ZI134));
			types_destroy((&ZI135));
		}
	
#line 5942 "tmp.parser.c"
		    }
		    /* END OF ACTION: x-action */
		    ZR247 (sid_current_grammar);
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
		    /* BEGINNING OF INLINE: 208 */
		    {
			{
			    NStringT ZI163;
			    EntryP ZI172;
			    TypeTupleT ZI134;
			    TypeTupleT ZI135;

			    switch (CURRENT_TERMINAL) {
			      case (LEXER_TOK_IDENTIFIER):
				/* BEGINNING OF EXTRACT: IDENTIFIER */
				{
#line 266 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 5978 "tmp.parser.c"
				}
				/* END OF EXTRACT: IDENTIFIER */
				break;
			      default:
				goto ZL5;
			    }
			    ADVANCE_LEXER;
			    /* BEGINNING OF ACTION: i-action */
			    {
#line 586 "parser.act"

		(ZI172) = scope_stack_add_action(sid_current_scope,
			grammar_table(sid_current_grammar), &(ZI163), sid_enclosing_rule,
			&sid_redefining_entry, TRUE);
			sid_current_entry = (ZI172);
		if (!(ZI172)) {
			E_duplicate_action((&ZI163));
			nstring_destroy(&(ZI163));
		}
	
#line 5999 "tmp.parser.c"
			    }
			    /* END OF ACTION: i-action */
			    ZR238 (sid_current_grammar);
			    ZR136 (sid_current_grammar, &ZI134, &ZI135);
			    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL5;
			    }
			    /* BEGINNING OF ACTION: x-action */
			    {
#line 597 "parser.act"

		if ((ZI172)) {
			KeyT       *key     = entry_key(sid_current_entry);
			ActionT    *action  = entry_get_action((ZI172));
			TypeTupleT *param   = action_param(action);
			TypeTupleT *result  = action_result(action);
			BoolT       errored = FALSE;

			if (types_contains_names((&ZI134))) {
				E_action_param_has_names(key, (&ZI134));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(param, (&ZI134))) {
					E_action_param_mismatch(key, param, (&ZI134));
					errored = TRUE;
				}
			}

			if (types_contains_names((&ZI135))) {
				E_action_result_has_names(key, (&ZI135));
				errored = TRUE;
			}

			if (types_contains_references((&ZI135))) {
				E_action_result_has_refs(key, (&ZI135));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(result, (&ZI135))) {
					E_action_result_mismatch(key, result, (&ZI135));
					errored = TRUE;
				}
			}

			if (!action_get_ignored(action)) {
				EntryT *type;

				type = types_find_ignored((&ZI134));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
					errored = TRUE;
				}

				type = types_find_ignored((&ZI135));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
					errored = TRUE;
				}
			}

			if (errored || sid_redefining_entry) {
				types_destroy((&ZI134));
				types_destroy((&ZI135));
			} else {
				types_assign(param, (&ZI134));
				types_assign(result, (&ZI135));
			}
		} else {
			types_destroy((&ZI134));
			types_destroy((&ZI135));
		}
	
#line 6076 "tmp.parser.c"
			    }
			    /* END OF ACTION: x-action */
			    ZR247 (sid_current_grammar);
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
#line 1596 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 6096 "tmp.parser.c"
			    }
			    /* END OF ACTION: expected-identifier */
			    /* BEGINNING OF ACTION: skip-to-end-of-action-decn */
			    {
#line 1892 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HSCOPE)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 6124 "tmp.parser.c"
			    }
			    /* END OF ACTION: skip-to-end-of-action-decn */
			}
		      ZL4:;
		    }
		    /* END OF INLINE: 208 */
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
#line 1596 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 6147 "tmp.parser.c"
		}
		/* END OF ACTION: expected-identifier */
		/* BEGINNING OF ACTION: skip-to-end-of-action-decn */
		{
#line 1892 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HSCOPE)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 6175 "tmp.parser.c"
		}
		/* END OF ACTION: skip-to-end-of-action-decn */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 205 */
    }
}

static void
ZR234(GrammarP sid_current_grammar)
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
#line 1692 "parser.act"

		if (!sid_propagating_error) {
			E_expected_define();
		}
	
#line 6211 "tmp.parser.c"
	}
	/* END OF ACTION: expected-define */
    }
}

static void
ZR248(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_248:;
    {
	ZR241 (sid_current_grammar);
	/* BEGINNING OF INLINE: 307 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_BASIC): case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_OPEN_HTUPLE): case (LEXER_TOK_BEGIN_HACTION):
	      case (LEXER_TOK_BEGIN_HRULE): case (LEXER_TOK_PRED_HRESULT): case (LEXER_TOK_IGNORE): case (LEXER_TOK_REFERENCE):
		{
		    /* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list::production-defn-non-empty-alternative */
		    goto ZL2_248;
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
	/* END OF INLINE: 307 */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-item */
	{
#line 1716 "parser.act"

		if (!sid_propagating_error) {
			E_expected_item();
		}
	
#line 6257 "tmp.parser.c"
	}
	/* END OF ACTION: expected-item */
	/* BEGINNING OF ACTION: skip-to-end-of-item */
	{
#line 1915 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_ALT_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_HANDLER_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_BEGIN_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HSCOPE)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 6289 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-item */
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2037 "parser.act"

		sid_propagating_error = FALSE;
	
#line 6298 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
    }
}

static void
ZR282(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI163;

	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_IDENTIFIER):
	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 6321 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF ACTION: add-entry */
	{
#line 1563 "parser.act"

		EntryT *entry;

		entry = table_get_rule(grammar_table(sid_current_grammar), (&ZI163));
		if (entry) {
			if (entry_list_contains(grammar_entry_list(sid_current_grammar), entry)) {
				E_mult_entry(entry_key(entry));
			} else {
				entry_list_add(grammar_entry_list(sid_current_grammar), entry);
				rule_required(entry_get_rule(entry));
			}
		} else {
			E_unknown_rule((&ZI163));
		}
		nstring_destroy(&(ZI163));
	
#line 6348 "tmp.parser.c"
	}
	/* END OF ACTION: add-entry */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-identifier */
	{
#line 1596 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 6363 "tmp.parser.c"
	}
	/* END OF ACTION: expected-identifier */
    }
}

static void
ZR237(GrammarP sid_current_grammar, TypeTupleT *ZI214)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI163;

	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_IDENTIFIER):
	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 6386 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF ACTION: prod-action */
	{
#line 1080 "parser.act"

		if (sid_current_entry && sid_current_alt) {
			EntryT *entry;

			entry = scope_stack_get_action(&sid_scope_stack,
				grammar_table(sid_current_grammar), (&ZI163));
			if (entry) {
				sid_current_item = item_create(entry);
			} else {
				E_unknown_action((&ZI163));
				sid_current_item = NULL;
				(void) alt_deallocate(sid_current_alt);
				sid_current_alt  = NULL;
			}
		} else {
			sid_current_item = NULL;
		}
		nstring_destroy(&(ZI163));
	
#line 6416 "tmp.parser.c"
	}
	/* END OF ACTION: prod-action */
	ZR238 (sid_current_grammar);
	ZR215 (sid_current_grammar, ZI214);
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
#line 1596 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 6437 "tmp.parser.c"
	}
	/* END OF ACTION: expected-identifier */
	/* BEGINNING OF ACTION: skip-to-end-of-item */
	{
#line 1915 "parser.act"

		while (CURRENT_TERMINAL != (LEXER_TOK_EOF)
			&& CURRENT_TERMINAL != (LEXER_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (LEXER_TOK_ALT_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_HANDLER_HSEP)
			&& CURRENT_TERMINAL != (LEXER_TOK_BEGIN_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HRULE)
			&& CURRENT_TERMINAL != (LEXER_TOK_END_HSCOPE)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HPRODUCTIONS)
			&& CURRENT_TERMINAL != (LEXER_TOK_BLT_HENTRY)) {
			if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
				nstring_destroy(lexer_string_value(sid_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (LEXER_TOK_IDENTIFIER)) {
			nstring_destroy(lexer_string_value(sid_current_stream));
		}

		if (CURRENT_TERMINAL != (LEXER_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		sid_propagating_error = TRUE;
	
#line 6469 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-item */
    }
}

static void
ZR238(GrammarP sid_current_grammar)
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
#line 1668 "parser.act"

		if (!sid_propagating_error) {
			E_expected_end_action();
		}
	
#line 6501 "tmp.parser.c"
	}
	/* END OF ACTION: expected-end-action */
    }
}

static void
ZR184(GrammarP sid_current_grammar, TypeTupleT *ZI138)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_184:;
    {
	ZR181 (sid_current_grammar, ZI138);
	/* BEGINNING OF INLINE: 186 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-close-tuple-or-skipped-or-eof */
		{
#line 2046 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_CLOSE_HTUPLE)
			|| CURRENT_TERMINAL == (LEXER_TOK_EOF)
			|| sid_propagating_error);
	
#line 6531 "tmp.parser.c"
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
		    goto ZL2_184;
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
#line 1620 "parser.act"

		if (!sid_propagating_error) {
			E_expected_separator();
		}
	
#line 6563 "tmp.parser.c"
		}
		/* END OF ACTION: expected-separator */
		/* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list::lhs-name-tuple::lhs-name-list-1 */
		goto ZL2_184;
		/* END OF INLINE: sid-parse-grammar::production-defn-list::lhs-name-tuple::lhs-name-list-1 */
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
	/* END OF INLINE: 186 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR246(GrammarP sid_current_grammar)
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
#line 1710 "parser.act"

		if (!sid_propagating_error) {
			E_expected_end_rule();
		}
	
#line 6607 "tmp.parser.c"
	}
	/* END OF ACTION: expected-end-rule */
    }
}

static void
ZR247(GrammarP sid_current_grammar)
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
#line 1644 "parser.act"

		if (!sid_propagating_error) {
			E_expected_terminator();
		}
	
#line 6639 "tmp.parser.c"
	}
	/* END OF ACTION: expected-terminator */
    }
}

static void
ZR196(GrammarP sid_current_grammar, TypeTupleT *ZI138)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_196:;
    {
	ZR193 (sid_current_grammar, ZI138);
	/* BEGINNING OF INLINE: 198 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-close-tuple-or-skipped-or-eof */
		{
#line 2046 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_CLOSE_HTUPLE)
			|| CURRENT_TERMINAL == (LEXER_TOK_EOF)
			|| sid_propagating_error);
	
#line 6669 "tmp.parser.c"
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
		    goto ZL2_196;
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
#line 1620 "parser.act"

		if (!sid_propagating_error) {
			E_expected_separator();
		}
	
#line 6701 "tmp.parser.c"
		}
		/* END OF ACTION: expected-separator */
		/* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list::rhs-name-tuple::rhs-name-list-1 */
		goto ZL2_196;
		/* END OF INLINE: sid-parse-grammar::production-defn-list::rhs-name-tuple::rhs-name-list-1 */
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
	/* END OF INLINE: 198 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

/* BEGINNING OF TRAILER */

#line 2061 "parser.act"


#line 6724 "tmp.parser.c"

/* END OF FILE */
