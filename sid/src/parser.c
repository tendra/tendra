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

static void ZR249(GrammarP);
static void ZR244(GrammarP);
static void ZR145(GrammarP, TypeTupleT *);
static void ZR263(GrammarP, TypeTupleT *, TypeTupleT *);
static void ZR246(GrammarP);
static void ZR181(GrammarP, TypeTupleT *);
static void ZR253(GrammarP);
static void ZR173(GrammarP, TypeTupleT *);
static void ZR155(GrammarP);
static void ZR185(GrammarP, TypeTupleT *);
static void ZR235(GrammarP);
static void ZR154(GrammarP);
static void ZR157(GrammarP);
static void ZR193(GrammarP, TypeTupleT *);
static void ZR205(GrammarP);
static void ZR175(GrammarP, TypeTupleT *);
static void ZR171(GrammarP);
extern void sid_parse_grammar(GrammarP);
static void ZR148(GrammarP, TypeTupleT *);
static void ZR300(GrammarP, NStringT *);
static void ZR150(GrammarP, TypeTupleT *);
static void ZR302(GrammarP);
static void ZR187(GrammarP, TypeTupleT *);
static void ZR303(GrammarP, NStringT *);
static void ZR304(GrammarP, NStringT *);
static void ZR213(GrammarP, TypeTupleT *);
static void ZR233(GrammarP);
static void ZR162(GrammarP);
static void ZR209(GrammarP, TypeTupleT *);
static void ZR268(GrammarP);
static void ZR136(GrammarP, TypeTupleT *);
static void ZR274(GrammarP);
static void ZR195(GrammarP);
static void ZR196(GrammarP);
static void ZR133(GrammarP, TypeTupleT *, TypeTupleT *);
static void ZR222(GrammarP);
static void ZR164(GrammarP);
static void ZR228(GrammarP);
static void ZR231(GrammarP, TypeTupleT *);
static void ZR232(GrammarP);
static void ZR197(GrammarP);
static void ZR242(GrammarP);
static void ZR276(GrammarP);
static void ZR178(GrammarP, TypeTupleT *);
static void ZR240(GrammarP);
static void ZR248(GrammarP);
static void ZR190(GrammarP, TypeTupleT *);

/* BEGINNING OF STATIC VARIABLES */

static BoolT ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZR249(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_249:;
    {
	ZR246 (sid_current_grammar);
	/* BEGINNING OF INLINE: 251 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_ALT_HSEP):
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list::production-defn-alternatives */
		    goto ZL2_249;
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
	/* END OF INLINE: 251 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR244(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF ACTION: handler */
	{
#line 1001 "parser.act"

		if (sid_current_entry) {
			sid_current_alt = alt_create();
		}
	
#line 247 "tmp.parser.c"
	}
	/* END OF ACTION: handler */
	ZR242 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: x-handler */
	{
#line 1019 "parser.act"

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
	
#line 275 "tmp.parser.c"
	}
	/* END OF ACTION: x-handler */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR145(GrammarP sid_current_grammar, TypeTupleT *ZI135)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_145:;
    {
	ZR136 (sid_current_grammar, ZI135);
	/* BEGINNING OF INLINE: 147 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-close-tuple-or-skipped-or-eof */
		{
#line 2025 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_CLOSE_HTUPLE)
			|| CURRENT_TERMINAL == (LEXER_TOK_EOF)
			|| sid_propagating_error);
	
#line 309 "tmp.parser.c"
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
		    goto ZL2_145;
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
#line 1599 "parser.act"

		if (!sid_propagating_error) {
			E_expected_separator();
		}
	
#line 341 "tmp.parser.c"
		}
		/* END OF ACTION: expected-separator */
		/* BEGINNING OF INLINE: sid-parse-grammar::function-type-defn::tuple-defn-list-1 */
		goto ZL2_145;
		/* END OF INLINE: sid-parse-grammar::function-type-defn::tuple-defn-list-1 */
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
	/* END OF INLINE: 147 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR263(GrammarP sid_current_grammar, TypeTupleT *ZI131, TypeTupleT *ZI132)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_DEFINE): case (LEXER_TOK_BEGIN_HSCOPE):
	{
	    /* BEGINNING OF ACTION: prod */
	    {
#line 808 "parser.act"

		if (sid_current_entry) {
			KeyT *key;

			key = entry_key(sid_current_entry);

			if (rule_is_defined(sid_current_rule)) {
				E_rule_already_defined(key);
				sid_current_entry = NULL;
				types_destroy((ZI131));
				types_destroy((ZI132));
			} else {
				TypeTupleT *param   = rule_param(sid_current_rule);
				TypeTupleT *result  = rule_result(sid_current_rule);
				BoolT       errored = FALSE;

				rule_defined(sid_current_rule);
				if (!types_disjoint_names((ZI131))) {
					E_rule_param_clash(key, (ZI131));
					errored = TRUE;
				}

				if (types_check_shadowing((ZI131), &sid_scope_stack,
					sid_current_rule)) {
					errored = TRUE;
				}

				if (sid_redefining_entry) {
					if (!types_fillin_names(param, (ZI131))) {
						E_rule_param_mismatch(key, param, (ZI131));
						errored = TRUE;
					}
					types_destroy((ZI131));
				} else {
					types_assign(param, (ZI131));
				}

				if (!types_disjoint_names((ZI132))) {
					E_rule_result_clash(key, (ZI132));
					errored = TRUE;
				}

				if (types_check_shadowing((ZI132), &sid_scope_stack,
					sid_current_rule)) {
					errored = TRUE;
				}

				if (types_contains_references((ZI132))) {
					E_rule_result_has_refs(key, (ZI132));
					errored = TRUE;
				}

				{
					EntryT *type;

					type = types_find_ignored((ZI131));
					if (type != NULL) {
						E_ignored_type(key_get_string(entry_key(type)));
						errored = TRUE;
					}

					type = types_find_ignored((ZI132));
					if (type != NULL) {
						E_ignored_type(key_get_string(entry_key(type)));
						errored = TRUE;
					}
				}

				if (sid_redefining_entry) {
					if (!types_fillin_names(result, (ZI132))) {
						E_rule_result_mismatch(key, result, (ZI132));
						errored = TRUE;
					}
					types_destroy((ZI132));
				} else {
					types_assign(result, (ZI132));
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
			types_destroy((ZI131));
			types_destroy((ZI132));
		}

		sid_alternative   = 0;
		sid_internal_rule = FALSE;
		sid_external_rule = sid_current_entry;
		nstring_init(&sid_maximum_scope);
	
#line 465 "tmp.parser.c"
	    }
	    /* END OF ACTION: prod */
	    /* BEGINNING OF ACTION: push-scope */
	    {
#line 913 "parser.act"

		if (sid_current_entry) {
			KeyT     *key   = entry_key(sid_current_entry);
			NStringT *scope = key_get_string(key);

			scope_stack_push(&sid_scope_stack, scope);
		}
	
#line 479 "tmp.parser.c"
	    }
	    /* END OF ACTION: push-scope */
	    ZR205 (sid_current_grammar);
	    ZR228 (sid_current_grammar);
	    /* BEGINNING OF INLINE: 265 */
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
#line 1683 "parser.act"

		if (!sid_propagating_error) {
			E_expected_begin_rule();
		}
	
#line 510 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-begin-rule */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 265 */
	    ZR233 (sid_current_grammar);
	    ZR240 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: pop-scope */
	    {
#line 919 "parser.act"

		if (sid_current_entry) {
			scope_stack_pop(&sid_scope_stack);
		}
	
#line 531 "tmp.parser.c"
	    }
	    /* END OF ACTION: pop-scope */
	    /* BEGINNING OF ACTION: x-prod */
	    {
#line 904 "parser.act"

		if (sid_current_entry) {
			nstring_assign(rule_maximum_scope(sid_current_rule),
				&sid_maximum_scope);
		} else {
			nstring_destroy(&sid_maximum_scope);
		}
	
#line 545 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-prod */
	    ZR248 (sid_current_grammar);
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
#line 741 "parser.act"

		if (sid_current_entry) {
			KeyT       *key     = entry_key(sid_current_entry);
			TypeTupleT *param   = rule_param(sid_current_rule);
			TypeTupleT *result  = rule_result(sid_current_rule);
			BoolT       errored = FALSE;

			if (types_contains_names((ZI131))) {
				E_rule_param_has_names(key, (ZI131));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(param, (ZI131))) {
					E_rule_param_mismatch(key, param, (ZI131));
					errored = TRUE;
				}
			}

			if (types_contains_names((ZI132))) {
				E_rule_result_has_names(key, (ZI132));
				errored = TRUE;
			}

			if (types_contains_references((ZI132))) {
				E_rule_result_has_refs(key, (ZI132));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(result, (ZI132))) {
					E_rule_result_mismatch(key, result, (ZI132));
					errored = TRUE;
				}
			}

			{
				EntryT *type;

				type = types_find_ignored((ZI131));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
					errored = TRUE;
				}

				type = types_find_ignored((ZI132));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
					errored = TRUE;
				}
			}

			if (errored || sid_redefining_entry) {
				types_destroy((ZI131));
				types_destroy((ZI132));
			} else {
				types_assign(param, (ZI131));
				types_assign(result, (ZI132));
			}
		} else {
			types_destroy((ZI131));
			types_destroy((ZI132));
		}
	
#line 624 "tmp.parser.c"
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
ZR246(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_EMPTY):
	{
	    /* BEGINNING OF ACTION: empty-alt */
	    {
#line 960 "parser.act"

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
	
#line 672 "tmp.parser.c"
	    }
	    /* END OF ACTION: empty-alt */
	    ADVANCE_LEXER;
	    ZR248 (sid_current_grammar);
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
#line 976 "parser.act"

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
	
#line 704 "tmp.parser.c"
	    }
	    /* END OF ACTION: non-empty-alt */
	    ZR242 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: x-non-empty-alt */
	    {
#line 995 "parser.act"

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
	
#line 733 "tmp.parser.c"
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
#line 1701 "parser.act"

		if (!sid_propagating_error) {
			E_expected_alternative();
		}
	
#line 754 "tmp.parser.c"
	}
	/* END OF ACTION: expected-alternative */
	/* BEGINNING OF ACTION: skip-to-end-of-alternative */
	{
#line 1921 "parser.act"

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
	
#line 784 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-alternative */
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2016 "parser.act"

		sid_propagating_error = FALSE;
	
#line 793 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
    }
}

static void
ZR181(GrammarP sid_current_grammar, TypeTupleT *ZI135)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_PRED_HRESULT): case (LEXER_TOK_IGNORE): case (LEXER_TOK_REFERENCE):
	{
	    ZR178 (sid_current_grammar, ZI135);
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
ZR253(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI160;

	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_IDENTIFIER):
	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 840 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 255 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_TYPEMARK):
		{
		    ADVANCE_LEXER;
		    ZR300 (sid_current_grammar, &ZI160);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		}
		break;
	      case (LEXER_TOK_TERMINATOR): case (LEXER_TOK_DEFINE): case (LEXER_TOK_BEGIN_HSCOPE):
		{
		    TypeTupleT ZI131;
		    TypeTupleT ZI132;

		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 367 "parser.act"

		types_init(&(ZI131));
	
#line 872 "tmp.parser.c"
		    }
		    /* END OF ACTION: init-tuple */
		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 367 "parser.act"

		types_init(&(ZI132));
	
#line 881 "tmp.parser.c"
		    }
		    /* END OF ACTION: init-tuple */
		    /* BEGINNING OF ACTION: rule */
		    {
#line 723 "parser.act"

		sid_current_entry = scope_stack_add_rule(sid_current_scope,
			grammar_table(sid_current_grammar), &(ZI160), sid_enclosing_rule,
			&sid_redefining_entry);
		if (sid_current_entry) {
			sid_current_rule = entry_get_rule(sid_current_entry);
		} else {
			E_duplicate_rule((&ZI160));
			nstring_destroy(&(ZI160));
		}
	
#line 898 "tmp.parser.c"
		    }
		    /* END OF ACTION: rule */
		    ZR263 (sid_current_grammar, &ZI131, &ZI132);
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
#line 1707 "parser.act"

		if (!sid_propagating_error) {
			E_expected_other_defn();
		}
	
#line 922 "tmp.parser.c"
		}
		/* END OF ACTION: expected-other-defn */
		/* BEGINNING OF ACTION: destroy-string */
		{
#line 1752 "parser.act"

		nstring_destroy(&(ZI160));
	
#line 931 "tmp.parser.c"
		}
		/* END OF ACTION: destroy-string */
		/* BEGINNING OF ACTION: skip-to-end-of-other-defn */
		{
#line 1946 "parser.act"

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
	
#line 960 "tmp.parser.c"
		}
		/* END OF ACTION: skip-to-end-of-other-defn */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 255 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR173(GrammarP sid_current_grammar, TypeTupleT *ZO135)
{
    TypeTupleT ZI135;

    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF ACTION: current-tuple */
	{
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 989 "tmp.parser.c"
	}
	/* END OF ACTION: current-tuple */
	ZR195 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 367 "parser.act"

		types_init(&(ZI135));
	
#line 1003 "tmp.parser.c"
	}
	/* END OF ACTION: init-tuple */
	ZR181 (sid_current_grammar, &ZI135);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2016 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1017 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	ZR196 (sid_current_grammar);
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

		ZO135->head = ZI135.head;

		if (ZO135->head == NULL) {
			ZO135->tail = &ZO135->head;
		} else {
			ZO135->tail= ZI135.tail ;
		}
	#line 1042 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: TypeTupleT */
}

static void
ZR155(GrammarP sid_current_grammar)
{
  ZL2_155:;
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_IGNORE):
	{
	    ZR157 (sid_current_grammar);
	    /* BEGINNING OF INLINE: sid-parse-grammar::type-decl-list */
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_155;
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
ZR185(GrammarP sid_current_grammar, TypeTupleT *ZO135)
{
    TypeTupleT ZI135;

    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF ACTION: current-tuple */
	{
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 1091 "tmp.parser.c"
	}
	/* END OF ACTION: current-tuple */
	ZR195 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 367 "parser.act"

		types_init(&(ZI135));
	
#line 1105 "tmp.parser.c"
	}
	/* END OF ACTION: init-tuple */
	ZR193 (sid_current_grammar, &ZI135);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2016 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1119 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	ZR196 (sid_current_grammar);
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

		ZO135->head = ZI135.head;

		if (ZO135->head == NULL) {
			ZO135->tail = &ZO135->head;
		} else {
			ZO135->tail= ZI135.tail ;
		}
	#line 1144 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: TypeTupleT */
}

static void
ZR235(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_BEGIN_HRULE):
	{
	    EntryP ZI166;
	    RuleP ZI72;
	    AltP ZI237;
	    BoolT ZI238;
	    ItemP ZI239;

	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: save */
	    {
#line 1022 "parser.act"

		(ZI166)      = sid_current_entry;
		(ZI72)       = sid_current_rule;
		(ZI237)        = sid_current_alt;
		(ZI238)   = sid_internal_rule;
		(ZI239)             = NULL;
		sid_internal_rule = TRUE;

		if (sid_current_entry && sid_current_alt) {
			sid_current_entry = table_add_generated_rule(grammar_table(sid_current_grammar), FALSE);
			sid_current_rule  = entry_get_rule(sid_current_entry);
			(ZI239)             = item_create(sid_current_entry);

			rule_defined(sid_current_rule);
			item_inlinable((ZI239));
			types_copy(item_param((ZI239)), rule_param((ZI72)));
			types_append_copy(item_param((ZI239)), alt_names((ZI237)));
			types_copy(rule_param(sid_current_rule), item_param((ZI239)));
			types_make_references(rule_param(sid_current_rule), item_param((ZI239)));
			alt_add_item((ZI237), (ZI239));
		} else {
			sid_current_entry = NULL;
		}
	
#line 1189 "tmp.parser.c"
	    }
	    /* END OF ACTION: save */
	    ZR233 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: restore */
	    {
#line 1047 "parser.act"

		if ((ZI166) && (ZI237)) {
			rule_compute_result_intersect(sid_current_rule);
			types_copy(item_result((ZI239)), rule_result(sid_current_rule));
			types_add_new_names(alt_names((ZI237)), item_result((ZI239)),
			grammar_get_predicate_id(sid_current_grammar));
		}

		sid_internal_rule = (ZI238);
		sid_current_alt   = (ZI237);
		sid_current_rule  = (ZI72);
		sid_current_entry = (ZI166);
	
#line 1213 "tmp.parser.c"
	    }
	    /* END OF ACTION: restore */
	    ZR240 (sid_current_grammar);
	    ZR248 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_OPEN_HTUPLE): case (LEXER_TOK_BEGIN_HACTION): case (LEXER_TOK_PRED_HRESULT):
      case (LEXER_TOK_IGNORE): case (LEXER_TOK_REFERENCE):
	{
	    ZR222 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 2016 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1238 "tmp.parser.c"
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
ZR154(GrammarP sid_current_grammar)
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
#line 1617 "parser.act"

		if (!sid_propagating_error) {
			E_expected_arrow();
		}
	
#line 1280 "tmp.parser.c"
	}
	/* END OF ACTION: expected-arrow */
    }
}

static void
ZR157(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF INLINE: 159 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_IDENTIFIER):
		{
		    NStringT ZI160;

		    /* BEGINNING OF EXTRACT: IDENTIFIER */
		    {
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 1306 "tmp.parser.c"
		    }
		    /* END OF EXTRACT: IDENTIFIER */
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: add-type */
		    {
#line 282 "parser.act"

		if (table_add_type(grammar_table(sid_current_grammar), &(ZI160), FALSE) == NULL) {
			E_duplicate_type((&ZI160));
			nstring_destroy(&(ZI160));
		}
	
#line 1319 "tmp.parser.c"
		    }
		    /* END OF ACTION: add-type */
		}
		break;
	      case (LEXER_TOK_IGNORE):
		{
		    NStringT ZI160;

		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 1337 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: i-add-type */
		    {
#line 289 "parser.act"

		if (table_add_type(grammar_table(sid_current_grammar), &(ZI160), TRUE) == NULL) {
			E_duplicate_type((&ZI160));
			nstring_destroy(&(ZI160));
		}
	
#line 1354 "tmp.parser.c"
		    }
		    /* END OF ACTION: i-add-type */
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	/* END OF INLINE: 159 */
	ZR248 (sid_current_grammar);
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
ZR193(GrammarP sid_current_grammar, TypeTupleT *ZI135)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_REFERENCE):
	{
	    ZR190 (sid_current_grammar, ZI135);
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
ZR205(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_BEGIN_HSCOPE):
	{
	    EntryP ZI166;
	    RuleP ZI72;

	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: save-scope */
	    {
#line 922 "parser.act"

		(ZI166) = sid_current_entry;
		(ZI72)  = sid_enclosing_rule;

		sid_enclosing_rule = sid_current_rule;
	
#line 1419 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-scope */
	    ZR171 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: restore-scope */
	    {
#line 929 "parser.act"

		sid_current_entry  = (ZI166);
		sid_current_rule   = sid_enclosing_rule;
		sid_enclosing_rule = (ZI72);
		sid_alternative    = 0;
		sid_internal_rule  = FALSE;
		sid_external_rule  = sid_current_entry;

		nstring_init(&sid_maximum_scope);
	
#line 1440 "tmp.parser.c"
	    }
	    /* END OF ACTION: restore-scope */
	    /* BEGINNING OF INLINE: 207 */
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
#line 1653 "parser.act"

		if (!sid_propagating_error) {
			E_expected_end_scope();
		}
	
#line 1465 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-end-scope */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 207 */
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
ZR175(GrammarP sid_current_grammar, TypeTupleT *ZI135)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI160;

	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 1499 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: add-name */
	    {
#line 415 "parser.act"

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI160), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI160));

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
			types_add_name_and_type((ZI135), name_entry, NULL, FALSE);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI160));
		} else if (non_local_entry) {
			types_add_name_and_type((ZI135), non_local_entry, NULL, FALSE);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI160));
		} else {
			types_add_name((ZI135), grammar_table(sid_current_grammar), &(ZI160), FALSE);
		}
	
#line 1545 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-name */
	}
	break;
      case (LEXER_TOK_IGNORE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: add-void */
	    {
#line 543 "parser.act"

		EntryT *entry;

		entry = table_add_generated_name(grammar_table(sid_current_grammar));
		types_add_name_entry((ZI135), entry);
	
#line 1562 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-void */
	}
	break;
      case (LEXER_TOK_PRED_HRESULT):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: add-pred */
	    {
#line 536 "parser.act"

		if (sid_current_pred_id) {
			E_multi_predicate_return();
		}
		sid_current_pred_id = TRUE;
		types_add_name_entry((ZI135), grammar_get_predicate_id(sid_current_grammar));
	
#line 1580 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-pred */
	}
	break;
      case (LEXER_TOK_REFERENCE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 177 */
	    {
		{
		    NStringT ZI160;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 1601 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: add-var */
		    {
#line 496 "parser.act"

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI160), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI160));

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
			types_add_name_and_type_var((ZI135), name_entry, NULL);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI160));
		} else if (non_local_entry) {
			types_add_name_and_type_var((ZI135), non_local_entry, NULL);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI160));
		} else {
			E_undefined_assignment((&ZI160));
			types_add_name((ZI135), grammar_table(sid_current_grammar), &(ZI160), FALSE);
		}
	
#line 1652 "tmp.parser.c"
		    }
		    /* END OF ACTION: add-var */
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1581 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 1667 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 177 */
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
#line 1629 "parser.act"

		if (!sid_propagating_error) {
			E_expected_lhs_name();
		}
	
#line 1692 "tmp.parser.c"
	}
	/* END OF ACTION: expected-lhs-name */
	/* BEGINNING OF ACTION: skip-to-end-of-lhs-name */
	{
#line 1827 "parser.act"

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
	
#line 1719 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-lhs-name */
    }
}

static void
ZR171(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_171:;
    {
	ZR268 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2016 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1744 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	/* BEGINNING OF INLINE: 272 */
	{
	    {
		/* BEGINNING OF ACTION: is-blt-entry-or-end-scope-or-eof */
		{
#line 2019 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_EOF)
			|| CURRENT_TERMINAL == (LEXER_TOK_END_HSCOPE)
			|| CURRENT_TERMINAL == (LEXER_TOK_BLT_HENTRY));
	
#line 1758 "tmp.parser.c"
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
		    goto ZL2_171;
		    /* END OF INLINE: sid-parse-grammar::production-defn-list */
		}
		/*UNREACHED*/
	      default:
		goto ZL1;
	    }
	  ZL3:;
	}
	/* END OF INLINE: 272 */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-production-defn */
	{
#line 1713 "parser.act"

		if (!sid_propagating_error) {
			E_expected_production_defn();
		}
	
#line 1793 "tmp.parser.c"
	}
	/* END OF ACTION: expected-production-defn */
	/* BEGINNING OF ACTION: skip-to-end-of-production-defn */
	{
#line 1970 "parser.act"

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
	
#line 1822 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-production-defn */
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2016 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1831 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	/* BEGINNING OF INLINE: 273 */
	{
	    {
		/* BEGINNING OF ACTION: is-blt-entry-or-end-scope-or-eof */
		{
#line 2019 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_EOF)
			|| CURRENT_TERMINAL == (LEXER_TOK_END_HSCOPE)
			|| CURRENT_TERMINAL == (LEXER_TOK_BLT_HENTRY));
	
#line 1845 "tmp.parser.c"
		}
		/* END OF ACTION: is-blt-entry-or-end-scope-or-eof */
		if (!ZI0)
		    goto ZL7;
	    }
	    goto ZL6;
	  ZL7:;
	    {
		/* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list */
		goto ZL2_171;
		/* END OF INLINE: sid-parse-grammar::production-defn-list */
	    }
	    /*UNREACHED*/
	  ZL6:;
	}
	/* END OF INLINE: 273 */
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
#line 274 "parser.act"

		scope_stack_init(&sid_scope_stack);
		scope_stack_init(&sid_global_scope);
	
#line 1879 "tmp.parser.c"
	}
	/* END OF ACTION: init */
	/* BEGINNING OF INLINE: 279 */
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
#line 1719 "parser.act"

		if (!sid_propagating_error) {
			E_expected_blt_types();
		}
	
#line 1904 "tmp.parser.c"
		}
		/* END OF ACTION: expected-blt-types */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 279 */
	ZR155 (sid_current_grammar);
	/* BEGINNING OF INLINE: 280 */
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
#line 1725 "parser.act"

		if (!sid_propagating_error) {
			E_expected_blt_terminals();
		}
	
#line 1938 "tmp.parser.c"
		}
		/* END OF ACTION: expected-blt-terminals */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 280 */
	ZR162 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: x-terminals */
	{
#line 359 "parser.act"

		unsigned max_terminal = grammar_max_terminal(sid_current_grammar);

		bitvec_set_size(max_terminal);
		sid_finished_terminals = TRUE;
	
#line 1959 "tmp.parser.c"
	}
	/* END OF ACTION: x-terminals */
	/* BEGINNING OF INLINE: 281 */
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
#line 1731 "parser.act"

		if (!sid_propagating_error) {
			E_expected_blt_productions();
		}
	
#line 1984 "tmp.parser.c"
		}
		/* END OF ACTION: expected-blt-productions */
	    }
	  ZL6:;
	}
	/* END OF INLINE: 281 */
	ZR171 (sid_current_grammar);
	/* BEGINNING OF INLINE: 282 */
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
#line 1737 "parser.act"

		if (!sid_propagating_error) {
			E_expected_blt_entry();
		}
	
#line 2018 "tmp.parser.c"
		}
		/* END OF ACTION: expected-blt-entry */
	    }
	  ZL8:;
	}
	/* END OF INLINE: 282 */
	ZR274 (sid_current_grammar);
	ZR248 (sid_current_grammar);
	/* BEGINNING OF INLINE: 284 */
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
#line 1743 "parser.act"

		if (!sid_propagating_error) {
			E_expected_eof();
		}
	
#line 2053 "tmp.parser.c"
		}
		/* END OF ACTION: expected-eof */
	    }
	  ZL10:;
	}
	/* END OF INLINE: 284 */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: unhandled-syntax-error */
	{
#line 1569 "parser.act"

		UNREACHED;
	
#line 2070 "tmp.parser.c"
	}
	/* END OF ACTION: unhandled-syntax-error */
    }
}

static void
ZR148(GrammarP sid_current_grammar, TypeTupleT *ZI135)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_TYPEMARK):
	{
	    ZR145 (sid_current_grammar, ZI135);
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
ZR300(GrammarP sid_current_grammar, NStringT *ZI160)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_OPEN_HTUPLE):
	{
	    TypeTupleT ZI131;
	    TypeTupleT ZI132;

	    ZR150 (sid_current_grammar, &ZI131);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2120 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR154 (sid_current_grammar);
	    ZR150 (sid_current_grammar, &ZI132);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: rule */
	    {
#line 723 "parser.act"

		sid_current_entry = scope_stack_add_rule(sid_current_scope,
			grammar_table(sid_current_grammar), &(*ZI160), sid_enclosing_rule,
			&sid_redefining_entry);
		if (sid_current_entry) {
			sid_current_rule = entry_get_rule(sid_current_entry);
		} else {
			E_duplicate_rule((ZI160));
			nstring_destroy(&(*ZI160));
		}
	
#line 2143 "tmp.parser.c"
	    }
	    /* END OF ACTION: rule */
	    ZR263 (sid_current_grammar, &ZI131, &ZI132);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_IDENTIFIER):
	{
	    /* BEGINNING OF INLINE: 256 */
	    {
		{
		    NStringT ZI141;
		    NonLocalEntryP ZI257;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI141, lexer_string_value(sid_current_stream));
	
#line 2169 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: non-local */
		    {
#line 648 "parser.act"

		(ZI257) = NULL;
		if (sid_enclosing_rule == NULL || sid_current_scope == &sid_global_scope) {
			E_global_scope_non_local((ZI160));
			nstring_destroy(&(*ZI160));
		} else {
			EntryT *type;

			type = table_get_type(grammar_table(sid_current_grammar), (&ZI141));
			if (type == NULL) {
				E_unknown_type((&ZI141));
				nstring_destroy(&(*ZI160));
			} else {
				EntryT *name;

				name = scope_stack_add_non_local(sid_current_scope,
					grammar_table(sid_current_grammar), &(*ZI160), type,
					sid_enclosing_rule);
				if (name) {
					NonLocalListT *non_locals;

					non_locals = rule_non_locals(sid_enclosing_rule);
					(ZI257) = non_local_list_add(non_locals, name, type);
				} else {
					E_duplicate_non_local((ZI160));
					nstring_destroy(&(*ZI160));
				}
			}
		}
		nstring_destroy(&(ZI141));
	
#line 2211 "tmp.parser.c"
		    }
		    /* END OF ACTION: non-local */
		    /* BEGINNING OF INLINE: 258 */
		    {
			switch (CURRENT_TERMINAL) {
			  case (LEXER_TOK_DEFINE):
			    {
				ADVANCE_LEXER;
				/* BEGINNING OF INLINE: 259 */
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
#line 1641 "parser.act"

		if (!sid_propagating_error) {
			E_expected_begin_action();
		}
	
#line 2242 "tmp.parser.c"
					}
					/* END OF ACTION: expected-begin-action */
				    }
				  ZL6:;
				}
				/* END OF INLINE: 259 */
				/* BEGINNING OF INLINE: 260 */
				{
				    {
					NStringT ZI53;

					switch (CURRENT_TERMINAL) {
					  case (LEXER_TOK_IDENTIFIER):
					    /* BEGINNING OF EXTRACT: IDENTIFIER */
					    {
#line 266 "parser.act"

		nstring_assign(&ZI53, lexer_string_value(sid_current_stream));
	
#line 2262 "tmp.parser.c"
					    }
					    /* END OF EXTRACT: IDENTIFIER */
					    break;
					  default:
					    goto ZL9;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: non-local-init */
					{
#line 683 "parser.act"

		EntryT *actionentry;

		actionentry = scope_stack_get_action(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI53));

		if (actionentry == NULL) {
			E_unknown_action((&ZI53));
		} else if ((ZI257)) {
			EntryT     *type   = non_local_entry_get_type((ZI257));
			KeyT       *name   = entry_key(non_local_entry_get_name((ZI257)));
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
			non_local_entry_set_initialiser((ZI257), actionentry);
		}
		nstring_destroy(&(ZI53));
	
#line 2314 "tmp.parser.c"
					}
					/* END OF ACTION: non-local-init */
					ZR232 (sid_current_grammar);
					ZR248 (sid_current_grammar);
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
#line 1581 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 2335 "tmp.parser.c"
					}
					/* END OF ACTION: expected-identifier */
				    }
				  ZL8:;
				}
				/* END OF INLINE: 260 */
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
#line 1749 "parser.act"

		if (!sid_propagating_error) {
			E_expected_terminator_or_define();
		}
	
#line 2363 "tmp.parser.c"
			    }
			    /* END OF ACTION: expected-terminator-or-define */
			}
		      ZL4:;
		    }
		    /* END OF INLINE: 258 */
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1581 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 2382 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: destroy-string */
		    {
#line 1752 "parser.act"

		nstring_destroy(&(*ZI160));
	
#line 2391 "tmp.parser.c"
		    }
		    /* END OF ACTION: destroy-string */
		    /* BEGINNING OF ACTION: skip-to-end-of-other-defn */
		    {
#line 1946 "parser.act"

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
	
#line 2420 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-other-defn */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 256 */
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
ZR150(GrammarP sid_current_grammar, TypeTupleT *ZO135)
{
    TypeTupleT ZI135;

    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 367 "parser.act"

		types_init(&(ZI135));
	
#line 2455 "tmp.parser.c"
	}
	/* END OF ACTION: init-tuple */
	ZR195 (sid_current_grammar);
	ZR148 (sid_current_grammar, &ZI135);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2016 "parser.act"

		sid_propagating_error = FALSE;
	
#line 2470 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	ZR196 (sid_current_grammar);
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

		ZO135->head = ZI135.head;

		if (ZO135->head == NULL) {
			ZO135->tail = &ZO135->head;
		} else {
			ZO135->tail= ZI135.tail ;
		}
	#line 2495 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: TypeTupleT */
}

static void
ZR302(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IGNORE):
	{
	    TypeTupleT ZI208;

	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 367 "parser.act"

		types_init(&(ZI208));
	
#line 2515 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: add-void */
	    {
#line 543 "parser.act"

		EntryT *entry;

		entry = table_add_generated_name(grammar_table(sid_current_grammar));
		types_add_name_entry((&ZI208), entry);
	
#line 2527 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-void */
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2536 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR228 (sid_current_grammar);
	    ZR213 (sid_current_grammar, &ZI208);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_PRED_HRESULT):
	{
	    TypeTupleT ZI208;

	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 367 "parser.act"

		types_init(&(ZI208));
	
#line 2558 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: add-pred */
	    {
#line 536 "parser.act"

		if (sid_current_pred_id) {
			E_multi_predicate_return();
		}
		sid_current_pred_id = TRUE;
		types_add_name_entry((&ZI208), grammar_get_predicate_id(sid_current_grammar));
	
#line 2571 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-pred */
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2580 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR228 (sid_current_grammar);
	    ZR213 (sid_current_grammar, &ZI208);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_BEGIN_HACTION):
	{
	    TypeTupleT ZI208;

	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2601 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 367 "parser.act"

		types_init(&(ZI208));
	
#line 2610 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    ADVANCE_LEXER;
	    ZR231 (sid_current_grammar, &ZI208);
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
ZR187(GrammarP sid_current_grammar, TypeTupleT *ZI135)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI160;

	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 2646 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: add-name */
	    {
#line 415 "parser.act"

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI160), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI160));

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
			types_add_name_and_type((ZI135), name_entry, NULL, FALSE);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI160));
		} else if (non_local_entry) {
			types_add_name_and_type((ZI135), non_local_entry, NULL, FALSE);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI160));
		} else {
			types_add_name((ZI135), grammar_table(sid_current_grammar), &(ZI160), FALSE);
		}
	
#line 2692 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-name */
	}
	break;
      case (LEXER_TOK_REFERENCE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 189 */
	    {
		{
		    NStringT ZI160;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 2713 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: add-ref-name */
		    {
#line 456 "parser.act"

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI160), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI160));

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
			types_add_name_and_type ((ZI135), name_entry, NULL, TRUE);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI160));
		} else if (non_local_entry) {
			types_add_name_and_type ((ZI135), non_local_entry, NULL, TRUE);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI160));
		} else {
			types_add_name((ZI135), grammar_table(sid_current_grammar), &(ZI160), TRUE);
		}
	
#line 2763 "tmp.parser.c"
		    }
		    /* END OF ACTION: add-ref-name */
		}
		goto ZL2;
	      ZL3:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1581 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 2778 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: skip-to-end-of-rhs-name */
		    {
#line 1849 "parser.act"

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
	
#line 2805 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-rhs-name */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 189 */
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
#line 1635 "parser.act"

		if (!sid_propagating_error) {
			E_expected_rhs_name();
		}
	
#line 2830 "tmp.parser.c"
	}
	/* END OF ACTION: expected-rhs-name */
	/* BEGINNING OF ACTION: skip-to-end-of-rhs-name */
	{
#line 1849 "parser.act"

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
	
#line 2857 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-rhs-name */
    }
}

static void
ZR303(GrammarP sid_current_grammar, NStringT *ZI160)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_DEFINE):
	{
	    TypeTupleT ZI208;

	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 367 "parser.act"

		types_init(&(ZI208));
	
#line 2877 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: add-name */
	    {
#line 415 "parser.act"

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (ZI160), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (ZI160));

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
			types_add_name_and_type((&ZI208), name_entry, NULL, FALSE);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(*ZI160));
		} else if (non_local_entry) {
			types_add_name_and_type((&ZI208), non_local_entry, NULL, FALSE);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(*ZI160));
		} else {
			types_add_name((&ZI208), grammar_table(sid_current_grammar), &(*ZI160), FALSE);
		}
	
#line 2922 "tmp.parser.c"
	    }
	    /* END OF ACTION: add-name */
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2931 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ADVANCE_LEXER;
	    ZR213 (sid_current_grammar, &ZI208);
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
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2950 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR304 (sid_current_grammar, ZI160);
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
ZR304(GrammarP sid_current_grammar, NStringT *ZI160)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_TERMINATOR):
	{
	    TypeTupleT ZI208;
	    TypeTupleT ZI211;

	    /* BEGINNING OF ACTION: current-tuple */
	    {
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 2986 "tmp.parser.c"
	    }
	    /* END OF ACTION: current-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 367 "parser.act"

		types_init(&(ZI208));
	
#line 2995 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 367 "parser.act"

		types_init(&(ZI211));
	
#line 3004 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: x-prod-rule */
	    {
#line 1236 "parser.act"

		TypeTupleT *param  = NULL;
		TypeTupleT *result = NULL;
		EntryT     *entry  = NULL;
		RuleT      *rule;
		BasicT     *basic;

		if (sid_current_entry && sid_current_alt) {
			entry = scope_stack_get_rule(&sid_scope_stack,
				grammar_table(sid_current_grammar), (ZI160));
			if (entry) {
				sid_current_item = item_create(entry);
				rule             = entry_get_rule(entry);
				param            = rule_param(rule);
				result           = rule_result(rule);
			} else {
				entry = table_get_basic(grammar_table(sid_current_grammar), (ZI160));
				if (entry) {
					sid_current_item = item_create(entry);
					basic            = entry_get_basic(entry);
					param            = NULL;
					result           = basic_result(basic);

					if (basic_get_ignored(basic)) {
						E_ignored_basic_call((ZI160));
					}
				} else {
					E_unknown_rule_or_basic((ZI160));
					sid_current_item = NULL;
				}
			}
		} else {
			sid_current_item = NULL;
		}

		nstring_destroy(&(*ZI160));
		if (sid_current_item) {
			BoolT  errored = FALSE;
			KeyT  *key     = entry_key(entry);

			if (types_resolve((&ZI211), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (param) {
					if (types_equal((&ZI211), param)) {
						item_add_param(sid_current_item, (&ZI211));
					} else {
						E_rule_param_call_mismatch(key, param, (&ZI211));
						types_destroy((&ZI211));
						errored = TRUE;
					}
				} else {
					if (!types_equal_zero_tuple((&ZI211))) {
						E_basic_param_call_mismatch(key, (&ZI211));
						types_destroy((&ZI211));
						errored = TRUE;
					}
				}
			} else {
				types_destroy((&ZI211));
				errored = TRUE;
			}

			if (types_disjoint_names((&ZI208))) {
				if (types_check_undefined((&ZI208), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((&ZI208), result)) {
						types_add_new_names(alt_names(sid_current_alt),
							(&ZI208), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							E_predicate ();
						}
						item_add_result(sid_current_item, (&ZI208));
					} else {
						if (param) {
							E_rule_result_call_mismatch(key, result, (&ZI208));
						} else {
							E_basic_result_call_mismatch(key, result, (&ZI208));
						}
						types_destroy((&ZI208));
						errored = TRUE;
					}
				} else {
					types_destroy((&ZI208));
					errored = TRUE;
				}
			} else {
				if (param) {
					E_rule_result_call_clash(key, (&ZI208));
				} else {
					E_basic_result_call_clash(key, (&ZI208));
				}

				types_destroy((&ZI208));
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
			types_destroy((&ZI208));
			types_destroy((&ZI211));
		}
	
#line 3125 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-prod-rule */
	    ADVANCE_LEXER;
	}
	break;
      case (LEXER_TOK_OPEN_HTUPLE):
	{
	    TypeTupleT ZI208;
	    TypeTupleT ZI211;

	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 367 "parser.act"

		types_init(&(ZI208));
	
#line 3142 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    ZR185 (sid_current_grammar, &ZI211);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: x-prod-rule */
	    {
#line 1236 "parser.act"

		TypeTupleT *param  = NULL;
		TypeTupleT *result = NULL;
		EntryT     *entry  = NULL;
		RuleT      *rule;
		BasicT     *basic;

		if (sid_current_entry && sid_current_alt) {
			entry = scope_stack_get_rule(&sid_scope_stack,
				grammar_table(sid_current_grammar), (ZI160));
			if (entry) {
				sid_current_item = item_create(entry);
				rule             = entry_get_rule(entry);
				param            = rule_param(rule);
				result           = rule_result(rule);
			} else {
				entry = table_get_basic(grammar_table(sid_current_grammar), (ZI160));
				if (entry) {
					sid_current_item = item_create(entry);
					basic            = entry_get_basic(entry);
					param            = NULL;
					result           = basic_result(basic);

					if (basic_get_ignored(basic)) {
						E_ignored_basic_call((ZI160));
					}
				} else {
					E_unknown_rule_or_basic((ZI160));
					sid_current_item = NULL;
				}
			}
		} else {
			sid_current_item = NULL;
		}

		nstring_destroy(&(*ZI160));
		if (sid_current_item) {
			BoolT  errored = FALSE;
			KeyT  *key     = entry_key(entry);

			if (types_resolve((&ZI211), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (param) {
					if (types_equal((&ZI211), param)) {
						item_add_param(sid_current_item, (&ZI211));
					} else {
						E_rule_param_call_mismatch(key, param, (&ZI211));
						types_destroy((&ZI211));
						errored = TRUE;
					}
				} else {
					if (!types_equal_zero_tuple((&ZI211))) {
						E_basic_param_call_mismatch(key, (&ZI211));
						types_destroy((&ZI211));
						errored = TRUE;
					}
				}
			} else {
				types_destroy((&ZI211));
				errored = TRUE;
			}

			if (types_disjoint_names((&ZI208))) {
				if (types_check_undefined((&ZI208), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((&ZI208), result)) {
						types_add_new_names(alt_names(sid_current_alt),
							(&ZI208), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							E_predicate ();
						}
						item_add_result(sid_current_item, (&ZI208));
					} else {
						if (param) {
							E_rule_result_call_mismatch(key, result, (&ZI208));
						} else {
							E_basic_result_call_mismatch(key, result, (&ZI208));
						}
						types_destroy((&ZI208));
						errored = TRUE;
					}
				} else {
					types_destroy((&ZI208));
					errored = TRUE;
				}
			} else {
				if (param) {
					E_rule_result_call_clash(key, (&ZI208));
				} else {
					E_basic_result_call_clash(key, (&ZI208));
				}

				types_destroy((&ZI208));
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
			types_destroy((&ZI208));
			types_destroy((&ZI211));
		}
	
#line 3268 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-prod-rule */
	    ZR248 (sid_current_grammar);
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
ZR213(GrammarP sid_current_grammar, TypeTupleT *ZI208)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_BEGIN_HACTION):
	{
	    ADVANCE_LEXER;
	    ZR231 (sid_current_grammar, ZI208);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI160;

	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 3313 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 217 */
	    {
		switch (CURRENT_TERMINAL) {
		  case (LEXER_TOK_OPEN_HTUPLE):
		    {
			TypeTupleT ZI211;

			ZR185 (sid_current_grammar, &ZI211);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			    RESTORE_LEXER;
			    goto ZL3;
			}
			/* BEGINNING OF ACTION: x-prod-rule */
			{
#line 1236 "parser.act"

		TypeTupleT *param  = NULL;
		TypeTupleT *result = NULL;
		EntryT     *entry  = NULL;
		RuleT      *rule;
		BasicT     *basic;

		if (sid_current_entry && sid_current_alt) {
			entry = scope_stack_get_rule(&sid_scope_stack,
				grammar_table(sid_current_grammar), (&ZI160));
			if (entry) {
				sid_current_item = item_create(entry);
				rule             = entry_get_rule(entry);
				param            = rule_param(rule);
				result           = rule_result(rule);
			} else {
				entry = table_get_basic(grammar_table(sid_current_grammar), (&ZI160));
				if (entry) {
					sid_current_item = item_create(entry);
					basic            = entry_get_basic(entry);
					param            = NULL;
					result           = basic_result(basic);

					if (basic_get_ignored(basic)) {
						E_ignored_basic_call((&ZI160));
					}
				} else {
					E_unknown_rule_or_basic((&ZI160));
					sid_current_item = NULL;
				}
			}
		} else {
			sid_current_item = NULL;
		}

		nstring_destroy(&(ZI160));
		if (sid_current_item) {
			BoolT  errored = FALSE;
			KeyT  *key     = entry_key(entry);

			if (types_resolve((&ZI211), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (param) {
					if (types_equal((&ZI211), param)) {
						item_add_param(sid_current_item, (&ZI211));
					} else {
						E_rule_param_call_mismatch(key, param, (&ZI211));
						types_destroy((&ZI211));
						errored = TRUE;
					}
				} else {
					if (!types_equal_zero_tuple((&ZI211))) {
						E_basic_param_call_mismatch(key, (&ZI211));
						types_destroy((&ZI211));
						errored = TRUE;
					}
				}
			} else {
				types_destroy((&ZI211));
				errored = TRUE;
			}

			if (types_disjoint_names((ZI208))) {
				if (types_check_undefined((ZI208), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((ZI208), result)) {
						types_add_new_names(alt_names(sid_current_alt),
							(ZI208), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							E_predicate ();
						}
						item_add_result(sid_current_item, (ZI208));
					} else {
						if (param) {
							E_rule_result_call_mismatch(key, result, (ZI208));
						} else {
							E_basic_result_call_mismatch(key, result, (ZI208));
						}
						types_destroy((ZI208));
						errored = TRUE;
					}
				} else {
					types_destroy((ZI208));
					errored = TRUE;
				}
			} else {
				if (param) {
					E_rule_result_call_clash(key, (ZI208));
				} else {
					E_basic_result_call_clash(key, (ZI208));
				}

				types_destroy((ZI208));
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
			types_destroy((ZI208));
			types_destroy((&ZI211));
		}
	
#line 3447 "tmp.parser.c"
			}
			/* END OF ACTION: x-prod-rule */
			ZR248 (sid_current_grammar);
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
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 3465 "tmp.parser.c"
			}
			/* END OF ACTION: current-tuple */
			/* BEGINNING OF ACTION: x-prod-rule-or-identity */
			{
#line 1344 "parser.act"

		EntryT     *name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI160));
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
				(&ZI160));
			if (entry) {
				sid_current_item = item_create (entry);
				rule             = entry_get_rule (entry);
				param            = rule_param(rule);
				result           = rule_result(rule);
			} else {
				entry = table_get_basic(grammar_table(sid_current_grammar), (&ZI160));
				if (entry) {
					sid_current_item = item_create (entry);
					basic            = entry_get_basic(entry);
					param            = NULL;
					result           = basic_result(basic);
					if (name_entry == NULL && basic_get_ignored(basic)) {
						E_ignored_basic_call((&ZI160));
					}
				}
			}

			if (entry == NULL && name_entry == NULL) {
				NStringT scope;

				name_entry = scope_stack_get_non_local(&sid_scope_stack,
					grammar_table(sid_current_grammar), (&ZI160), &scope);
				if (name_entry) {
					if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
						nstring_destroy(&sid_maximum_scope);
						nstring_assign(&sid_maximum_scope, &scope);
					} else {
						nstring_destroy(&scope);
					}
				} else {
					E_unknown_rule_or_basic((&ZI160));
				}
			} else if (entry != NULL && name_entry != NULL) {
				E_ambiguous_call((&ZI160));
				entry      = NULL;
				name_entry = NULL;
			}
		} else {
			name_entry = NULL;
		}
		nstring_destroy(&(ZI160));

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

			if (types_disjoint_names((ZI208))) {
				if (types_check_undefined((ZI208), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((ZI208), result)) {
						types_add_new_names(alt_names(sid_current_alt),
							(ZI208), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							E_predicate();
						}
						item_add_result(sid_current_item, (ZI208));
					} else {
						if (param) {
							E_rule_result_call_mismatch(key, result, (ZI208));
						} else {
							E_basic_result_call_mismatch(key, result, (ZI208));
						}
						types_destroy((ZI208));
						errored = TRUE;
					}
				} else {
					types_destroy((ZI208));
					errored = TRUE;
				}
			} else {
				if (param) {
					E_rule_result_call_clash(key, (ZI208));
				} else {
					E_basic_result_call_clash(key, (ZI208));
				}
				types_destroy((ZI208));
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

			if (types_disjoint_names((ZI208))) {
				if (types_check_undefined((ZI208), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (sid_current_item) {
						if (types_fillin_types((ZI208), item_param(sid_current_item))) {
							types_add_new_names(alt_names(sid_current_alt),
								(ZI208), grammar_get_predicate_id(sid_current_grammar));
							if (sid_saved_pred_id) {
								E_predicate();
							}
							item_add_result(sid_current_item, (ZI208));
							alt_add_item(sid_current_alt, sid_current_item);
						} else {
							E_identity_mismatch(item_param(sid_current_item), (ZI208));
							types_destroy((ZI208));
							(void) item_deallocate(sid_current_item);
							sid_current_item = NULL;
						}
					}
				} else {
					types_destroy((ZI208));
					if (sid_current_item) {
						(void) item_deallocate(sid_current_item);
						sid_current_item = NULL;
					}
				}
			} else {
				E_identity_result_clash((ZI208));
				types_destroy((ZI208));
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
			types_destroy((ZI208));
			types_destroy(&rhs);
		}
	
#line 3672 "tmp.parser.c"
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
#line 1659 "parser.act"

		if (!sid_propagating_error) {
			E_expected_tuple_or_term();
		}
	
#line 3692 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-tuple-or-terminator */
		    /* BEGINNING OF ACTION: destroy-string */
		    {
#line 1752 "parser.act"

		nstring_destroy(&(ZI160));
	
#line 3701 "tmp.parser.c"
		    }
		    /* END OF ACTION: destroy-string */
		    /* BEGINNING OF ACTION: skip-to-end-of-item */
		    {
#line 1894 "parser.act"

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
	
#line 3733 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-item */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 217 */
	}
	break;
      case (LEXER_TOK_OPEN_HTUPLE):
	{
	    TypeTupleT ZI211;

	    ZR185 (sid_current_grammar, &ZI211);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: x-identity */
	    {
#line 1164 "parser.act"

		if (sid_current_entry && sid_current_alt) {
			EntryT *entry = table_add_rename(grammar_table(sid_current_grammar));

			if (types_resolve((&ZI211), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_contains_references((&ZI211))) {
					E_identity_param_has_refs((&ZI211), entry_key(sid_external_rule),
						sid_alternative);
					types_destroy((&ZI211));
					sid_current_item = NULL;
				} else {
					sid_current_item = item_create(entry);
					item_add_param(sid_current_item, (&ZI211));
				}
			} else {
				types_destroy((&ZI211));
				sid_current_item = NULL;
			}

			if (types_disjoint_names((ZI208))) {
				if (types_check_undefined((ZI208), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (sid_current_item) {
						if (types_fillin_types((ZI208), item_param(sid_current_item))) {
							types_add_new_names(alt_names(sid_current_alt),
							(ZI208), grammar_get_predicate_id(sid_current_grammar));
							if (sid_saved_pred_id) {
								E_predicate();
							}
							item_add_result(sid_current_item, (ZI208));
							alt_add_item(sid_current_alt, sid_current_item);
						} else {
							E_identity_mismatch(item_param(sid_current_item), (ZI208));
							types_destroy((ZI208));
							(void) item_deallocate(sid_current_item);
							sid_current_item = NULL;
						}
					}
				} else {
					types_destroy((ZI208));
					if (sid_current_item) {
						(void) item_deallocate(sid_current_item);
						sid_current_item = NULL;
					}
				}
			} else {
				E_identity_result_clash((ZI208));
				types_destroy((ZI208));
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
			types_destroy((ZI208));
			types_destroy((&ZI211));
		}
	
#line 3820 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-identity */
	    ZR248 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_REFERENCE):
	{
	    TypeTupleT ZI211;

	    /* BEGINNING OF ACTION: current-tuple */
	    {
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 3840 "tmp.parser.c"
	    }
	    /* END OF ACTION: current-tuple */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 367 "parser.act"

		types_init(&(ZI211));
	
#line 3850 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF INLINE: 219 */
	    {
		{
		    NStringT ZI160;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 3866 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL5;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: add-ref-name */
		    {
#line 456 "parser.act"

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI160), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI160));

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
			types_add_name_and_type ((&ZI211), name_entry, NULL, TRUE);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI160));
		} else if (non_local_entry) {
			types_add_name_and_type ((&ZI211), non_local_entry, NULL, TRUE);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI160));
		} else {
			types_add_name((&ZI211), grammar_table(sid_current_grammar), &(ZI160), TRUE);
		}
	
#line 3916 "tmp.parser.c"
		    }
		    /* END OF ACTION: add-ref-name */
		    /* BEGINNING OF ACTION: x-identity */
		    {
#line 1164 "parser.act"

		if (sid_current_entry && sid_current_alt) {
			EntryT *entry = table_add_rename(grammar_table(sid_current_grammar));

			if (types_resolve((&ZI211), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_contains_references((&ZI211))) {
					E_identity_param_has_refs((&ZI211), entry_key(sid_external_rule),
						sid_alternative);
					types_destroy((&ZI211));
					sid_current_item = NULL;
				} else {
					sid_current_item = item_create(entry);
					item_add_param(sid_current_item, (&ZI211));
				}
			} else {
				types_destroy((&ZI211));
				sid_current_item = NULL;
			}

			if (types_disjoint_names((ZI208))) {
				if (types_check_undefined((ZI208), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (sid_current_item) {
						if (types_fillin_types((ZI208), item_param(sid_current_item))) {
							types_add_new_names(alt_names(sid_current_alt),
							(ZI208), grammar_get_predicate_id(sid_current_grammar));
							if (sid_saved_pred_id) {
								E_predicate();
							}
							item_add_result(sid_current_item, (ZI208));
							alt_add_item(sid_current_alt, sid_current_item);
						} else {
							E_identity_mismatch(item_param(sid_current_item), (ZI208));
							types_destroy((ZI208));
							(void) item_deallocate(sid_current_item);
							sid_current_item = NULL;
						}
					}
				} else {
					types_destroy((ZI208));
					if (sid_current_item) {
						(void) item_deallocate(sid_current_item);
						sid_current_item = NULL;
					}
				}
			} else {
				E_identity_result_clash((ZI208));
				types_destroy((ZI208));
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
			types_destroy((ZI208));
			types_destroy((&ZI211));
		}
	
#line 3988 "tmp.parser.c"
		    }
		    /* END OF ACTION: x-identity */
		    ZR248 (sid_current_grammar);
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
#line 1581 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 4008 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: skip-to-end-of-item */
		    {
#line 1894 "parser.act"

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
	
#line 4040 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-item */
		}
	      ZL4:;
	    }
	    /* END OF INLINE: 219 */
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
#line 1665 "parser.act"

		if (!sid_propagating_error) {
			E_expected_item_rhs();
		}
	
#line 4065 "tmp.parser.c"
	}
	/* END OF ACTION: expected-item-rhs */
	/* BEGINNING OF ACTION: skip-to-end-of-item */
	{
#line 1894 "parser.act"

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
	
#line 4097 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-item */
    }
}

static void
ZR233(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	ZR249 (sid_current_grammar);
	/* BEGINNING OF INLINE: 252 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_HANDLER_HSEP):
		{
		    ADVANCE_LEXER;
		    ZR244 (sid_current_grammar);
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
	/* END OF INLINE: 252 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR162(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_162:;
    {
	ZR164 (sid_current_grammar);
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2016 "parser.act"

		sid_propagating_error = FALSE;
	
#line 4158 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
	/* BEGINNING OF INLINE: 170 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_IGNORE):
		{
		    /* BEGINNING OF INLINE: sid-parse-grammar::terminal-decn-list */
		    goto ZL2_162;
		    /* END OF INLINE: sid-parse-grammar::terminal-decn-list */
		}
		/*UNREACHED*/
	      default:
		break;
	    }
	}
	/* END OF INLINE: 170 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR209(GrammarP sid_current_grammar, TypeTupleT *ZI208)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_OPEN_HTUPLE):
	{
	    TypeTupleT ZI211;

	    ZR185 (sid_current_grammar, &ZI211);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: x-prod-action */
	    {
#line 1090 "parser.act"

		if (sid_current_item) {
			BoolT    errored = FALSE;
			EntryT  *entry   = item_entry(sid_current_item);
			ActionT *action  = entry_get_action(entry);

			if (action_get_ignored(action)) {
				E_ignored_action_call(key_get_string(entry_key(entry)));
			}

			if (types_resolve((&ZI211), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_equal((&ZI211), action_param(action))) {
					item_add_param(sid_current_item, (&ZI211));
				} else {
					E_action_param_call_mismatch(entry_key(entry),
							  action_param(action), (&ZI211));
					types_destroy((&ZI211));
					errored = TRUE;
				}
			} else {
				types_destroy((&ZI211));
				errored = TRUE;
			}

			if (types_disjoint_names((ZI208))) {
				if (types_check_undefined((ZI208), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((ZI208), action_result(action))) {
						types_add_new_names(alt_names(sid_current_alt),
							(ZI208), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							BoolT   reference;
							EntryT *type;

							type = types_find_name_type((ZI208),
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
						item_add_result(sid_current_item, (ZI208));
					} else {
						E_action_result_call_mismatch(entry_key(entry),
							action_result(action), (ZI208));
						types_destroy((ZI208));
						errored = TRUE;
					}
				} else {
					types_destroy((ZI208));
					errored = TRUE;
				}
			} else {
				E_action_result_call_clash(entry_key(entry), (ZI208));
				types_destroy((ZI208));
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
			types_destroy((ZI208));
			types_destroy((&ZI211));
		}
	
#line 4278 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-prod-action */
	    ZR248 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_TERMINATOR):
	{
	    TypeTupleT ZI211;

	    /* BEGINNING OF ACTION: current-tuple */
	    {
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 4298 "tmp.parser.c"
	    }
	    /* END OF ACTION: current-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 367 "parser.act"

		types_init(&(ZI211));
	
#line 4307 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: x-prod-action */
	    {
#line 1090 "parser.act"

		if (sid_current_item) {
			BoolT    errored = FALSE;
			EntryT  *entry   = item_entry(sid_current_item);
			ActionT *action  = entry_get_action(entry);

			if (action_get_ignored(action)) {
				E_ignored_action_call(key_get_string(entry_key(entry)));
			}

			if (types_resolve((&ZI211), rule_param(sid_current_rule),
				alt_names(sid_current_alt), E_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_equal((&ZI211), action_param(action))) {
					item_add_param(sid_current_item, (&ZI211));
				} else {
					E_action_param_call_mismatch(entry_key(entry),
							  action_param(action), (&ZI211));
					types_destroy((&ZI211));
					errored = TRUE;
				}
			} else {
				types_destroy((&ZI211));
				errored = TRUE;
			}

			if (types_disjoint_names((ZI208))) {
				if (types_check_undefined((ZI208), rule_param(sid_current_rule),
					alt_names(sid_current_alt), E_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((ZI208), action_result(action))) {
						types_add_new_names(alt_names(sid_current_alt),
							(ZI208), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							BoolT   reference;
							EntryT *type;

							type = types_find_name_type((ZI208),
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
						item_add_result(sid_current_item, (ZI208));
					} else {
						E_action_result_call_mismatch(entry_key(entry),
							action_result(action), (ZI208));
						types_destroy((ZI208));
						errored = TRUE;
					}
				} else {
					types_destroy((ZI208));
					errored = TRUE;
				}
			} else {
				E_action_result_call_clash(entry_key(entry), (ZI208));
				types_destroy((ZI208));
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
			types_destroy((ZI208));
			types_destroy((&ZI211));
		}
	
#line 4392 "tmp.parser.c"
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
#line 1659 "parser.act"

		if (!sid_propagating_error) {
			E_expected_tuple_or_term();
		}
	
#line 4414 "tmp.parser.c"
	}
	/* END OF ACTION: expected-tuple-or-terminator */
	/* BEGINNING OF ACTION: skip-to-end-of-item */
	{
#line 1894 "parser.act"

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
	
#line 4446 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-item */
    }
}

static void
ZR268(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF INLINE: 270 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_SCOPEMARK):
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: use-global */
		    {
#line 553 "parser.act"

		sid_current_scope = &sid_global_scope;
	
#line 4471 "tmp.parser.c"
		    }
		    /* END OF ACTION: use-global */
		}
		break;
	      default:
		{
		    /* BEGINNING OF ACTION: use-local */
		    {
#line 557 "parser.act"

		sid_current_scope = &sid_scope_stack;
	
#line 4484 "tmp.parser.c"
		    }
		    /* END OF ACTION: use-local */
		}
		break;
	    }
	}
	/* END OF INLINE: 270 */
	/* BEGINNING OF INLINE: 271 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_BEGIN_HACTION): case (LEXER_TOK_IGNORE):
		{
		    ZR197 (sid_current_grammar);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case (LEXER_TOK_IDENTIFIER):
		{
		    ZR253 (sid_current_grammar);
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
	/* END OF INLINE: 271 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR136(GrammarP sid_current_grammar, TypeTupleT *ZI135)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI138;

	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI138, lexer_string_value(sid_current_stream));
	
#line 4539 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 139 */
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
#line 1575 "parser.act"

		if (!sid_propagating_error) {
			E_expected_typemark();
		}
	
#line 4565 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-typemark */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 139 */
	    /* BEGINNING OF INLINE: 140 */
	    {
		{
		    NStringT ZI141;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI141, lexer_string_value(sid_current_stream));
	
#line 4585 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL5;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: 142 */
		    {
			switch (CURRENT_TERMINAL) {
			  case (LEXER_TOK_REFERENCE):
			    {
				ADVANCE_LEXER;
				/* BEGINNING OF ACTION: tuple-ref-name */
				{
#line 387 "parser.act"

		if (!types_add_typed_name((ZI135), grammar_table(sid_current_grammar),
			&(ZI138), (&ZI141), TRUE)) {
			E_unknown_type((&ZI141));
		}
		nstring_destroy(&(ZI141));
	
#line 4609 "tmp.parser.c"
				}
				/* END OF ACTION: tuple-ref-name */
			    }
			    break;
			  default:
			    {
				/* BEGINNING OF ACTION: tuple-name */
				{
#line 379 "parser.act"

		if (!types_add_typed_name((ZI135), grammar_table(sid_current_grammar),
			&(ZI138), (&ZI141), FALSE)) {
			E_unknown_type((&ZI141));
		}
		nstring_destroy(&(ZI141));
	
#line 4626 "tmp.parser.c"
				}
				/* END OF ACTION: tuple-name */
			    }
			    break;
			}
		    }
		    /* END OF INLINE: 142 */
		}
		goto ZL4;
	      ZL5:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1581 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 4646 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: destroy-string */
		    {
#line 1752 "parser.act"

		nstring_destroy(&(ZI138));
	
#line 4655 "tmp.parser.c"
		    }
		    /* END OF ACTION: destroy-string */
		    /* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
		    {
#line 1758 "parser.act"

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
	
#line 4708 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-tuple-defn */
		}
	      ZL4:;
	    }
	    /* END OF INLINE: 140 */
	}
	break;
      case (LEXER_TOK_TYPEMARK):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 143 */
	    {
		{
		    NStringT ZI141;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI141, lexer_string_value(sid_current_stream));
	
#line 4733 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL8;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: 144 */
		    {
			switch (CURRENT_TERMINAL) {
			  case (LEXER_TOK_REFERENCE):
			    {
				ADVANCE_LEXER;
				/* BEGINNING OF ACTION: tuple-ref-type */
				{
#line 403 "parser.act"

		if (!types_add_type((ZI135), grammar_table(sid_current_grammar), (&ZI141), TRUE)) {
			E_unknown_type((&ZI141));
		}
		nstring_destroy(&(ZI141));
	
#line 4756 "tmp.parser.c"
				}
				/* END OF ACTION: tuple-ref-type */
			    }
			    break;
			  default:
			    {
				/* BEGINNING OF ACTION: tuple-type */
				{
#line 395 "parser.act"

		if (!types_add_type((ZI135), grammar_table(sid_current_grammar), (&ZI141),
			FALSE)) {
			E_unknown_type((&ZI141));
		}
		nstring_destroy(&(ZI141));
	
#line 4773 "tmp.parser.c"
				}
				/* END OF ACTION: tuple-type */
			    }
			    break;
			}
		    }
		    /* END OF INLINE: 144 */
		}
		goto ZL7;
	      ZL8:;
		{
		    /* BEGINNING OF ACTION: expected-identifier */
		    {
#line 1581 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 4793 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
		    {
#line 1758 "parser.act"

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
	
#line 4846 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-tuple-defn */
		}
	      ZL7:;
	    }
	    /* END OF INLINE: 143 */
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
#line 1587 "parser.act"

		if (!sid_propagating_error) {
			E_expected_tuple_defn();
		}
	
#line 4871 "tmp.parser.c"
	}
	/* END OF ACTION: expected-tuple-defn */
	/* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
	{
#line 1758 "parser.act"

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
	
#line 4924 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-tuple-defn */
    }
}

static void
ZR274(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_274:;
    {
	ZR276 (sid_current_grammar);
	/* BEGINNING OF INLINE: 277 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-terminator */
		{
#line 2031 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_TERMINATOR));
	
#line 4952 "tmp.parser.c"
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
		    goto ZL2_274;
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
#line 1599 "parser.act"

		if (!sid_propagating_error) {
			E_expected_separator();
		}
	
#line 4984 "tmp.parser.c"
		}
		/* END OF ACTION: expected-separator */
		/* BEGINNING OF ACTION: skip-to-end-of-entry-list */
		{
#line 1994 "parser.act"

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
	
#line 5010 "tmp.parser.c"
		}
		/* END OF ACTION: skip-to-end-of-entry-list */
		/* BEGINNING OF ACTION: skip-recover */
		{
#line 2016 "parser.act"

		sid_propagating_error = FALSE;
	
#line 5019 "tmp.parser.c"
		}
		/* END OF ACTION: skip-recover */
		/* BEGINNING OF INLINE: 278 */
		{
		    {
			/* BEGINNING OF ACTION: is-not-separator */
			{
#line 2035 "parser.act"

		(ZI0) = (CURRENT_TERMINAL != (LEXER_TOK_SEPARATOR));
	
#line 5031 "tmp.parser.c"
			}
			/* END OF ACTION: is-not-separator */
			if (!ZI0)
			    goto ZL7;
		    }
		    goto ZL6;
		  ZL7:;
		    {
			/* BEGINNING OF INLINE: sid-parse-grammar::entry-list */
			goto ZL2_274;
			/* END OF INLINE: sid-parse-grammar::entry-list */
		    }
		    /*UNREACHED*/
		  ZL6:;
		}
		/* END OF INLINE: 278 */
	    }
	  ZL3:;
	}
	/* END OF INLINE: 277 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR195(GrammarP sid_current_grammar)
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
#line 1605 "parser.act"

		if (!sid_propagating_error) {
			E_expected_open_tuple();
		}
	
#line 5085 "tmp.parser.c"
	}
	/* END OF ACTION: expected-open-tuple */
    }
}

static void
ZR196(GrammarP sid_current_grammar)
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
#line 1611 "parser.act"

		if (!sid_propagating_error) {
			E_expected_close_tuple();
		}
	
#line 5117 "tmp.parser.c"
	}
	/* END OF ACTION: expected-close-tuple */
    }
}

static void
ZR133(GrammarP sid_current_grammar, TypeTupleT *ZO131, TypeTupleT *ZO132)
{
    TypeTupleT ZI131;
    TypeTupleT ZI132;

    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_TYPEMARK):
	{
	    ADVANCE_LEXER;
	    ZR150 (sid_current_grammar, &ZI131);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 5144 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR154 (sid_current_grammar);
	    ZR150 (sid_current_grammar, &ZI132);
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
#line 367 "parser.act"

		types_init(&(ZI131));
	
#line 5163 "tmp.parser.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 367 "parser.act"

		types_init(&(ZI132));
	
#line 5172 "tmp.parser.c"
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

		ZO131->head = ZI131.head;

		if (ZO131->head == NULL) {
			ZO131->tail = &ZO131->head;
		} else {
			ZO131->tail= ZI131.tail ;
		}
	#line 5196 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: TypeTupleT */
    /* BEGINNING OF RESULT ASSIGNMENT: TypeTupleT */
    {
#line 254 "parser.act"

		ZO132->head = ZI132.head;

		if (ZO132->head == NULL) {
			ZO132->tail = &ZO132->head;
		} else {
			ZO132->tail= ZI132.tail ;
		}
	#line 5210 "tmp.parser.c"
    }
    /* END OF RESULT ASSIGNMENT: TypeTupleT */
}

static void
ZR222(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI160;

	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 5229 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 229 */
	    {
		{
		    /* BEGINNING OF ACTION: current-tuple */
		    {
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 5242 "tmp.parser.c"
		    }
		    /* END OF ACTION: current-tuple */
		    ZR303 (sid_current_grammar, &ZI160);
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
#line 1677 "parser.act"

		if (!sid_propagating_error) {
			E_expected_tuple_def_or_term();
		}
	
#line 5262 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-tuple-or-define-or-terminator */
		    /* BEGINNING OF ACTION: destroy-string */
		    {
#line 1752 "parser.act"

		nstring_destroy(&(ZI160));
	
#line 5271 "tmp.parser.c"
		    }
		    /* END OF ACTION: destroy-string */
		    /* BEGINNING OF ACTION: skip-to-end-of-item */
		    {
#line 1894 "parser.act"

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
	
#line 5303 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-item */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 229 */
	}
	break;
      case (LEXER_TOK_REFERENCE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 227 */
	    {
		{
		    NStringT ZI160;
		    TypeTupleT ZI208;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 5329 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL5;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: current-tuple */
		    {
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 5343 "tmp.parser.c"
		    }
		    /* END OF ACTION: current-tuple */
		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 367 "parser.act"

		types_init(&(ZI208));
	
#line 5352 "tmp.parser.c"
		    }
		    /* END OF ACTION: init-tuple */
		    /* BEGINNING OF ACTION: add-var */
		    {
#line 496 "parser.act"

		NStringT scope;
		EntryT *non_local_entry;
		EntryT *name_entry;

		non_local_entry = scope_stack_get_non_local(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI160), &scope);
		name_entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI160));

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
			types_add_name_and_type_var((&ZI208), name_entry, NULL);
			if (non_local_entry) {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI160));
		} else if (non_local_entry) {
			types_add_name_and_type_var((&ZI208), non_local_entry, NULL);
			if (nstring_length(&scope) > nstring_length(&sid_maximum_scope)) {
				nstring_destroy(&sid_maximum_scope);
				nstring_assign(&sid_maximum_scope, &scope);
			} else {
				nstring_destroy(&scope);
			}
			nstring_destroy(&(ZI160));
		} else {
			E_undefined_assignment((&ZI160));
			types_add_name((&ZI208), grammar_table(sid_current_grammar), &(ZI160), FALSE);
		}
	
#line 5398 "tmp.parser.c"
		    }
		    /* END OF ACTION: add-var */
		    /* BEGINNING OF ACTION: save-tuple */
		    {
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 5407 "tmp.parser.c"
		    }
		    /* END OF ACTION: save-tuple */
		    ZR228 (sid_current_grammar);
		    ZR213 (sid_current_grammar, &ZI208);
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
#line 1581 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 5428 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		}
	      ZL4:;
	    }
	    /* END OF INLINE: 227 */
	}
	break;
      case (LEXER_TOK_OPEN_HTUPLE):
	{
	    TypeTupleT ZI208;

	    ZR173 (sid_current_grammar, &ZI208);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 5452 "tmp.parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR228 (sid_current_grammar);
	    ZR213 (sid_current_grammar, &ZI208);
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
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 5471 "tmp.parser.c"
	    }
	    /* END OF ACTION: current-tuple */
	    ZR302 (sid_current_grammar);
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
ZR164(GrammarP sid_current_grammar)
{
    switch (CURRENT_TERMINAL) {
      case (LEXER_TOK_IDENTIFIER):
	{
	    NStringT ZI160;
	    EntryP ZI166;
	    TypeTupleT ZI131;
	    TypeTupleT ZI132;

	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 5509 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: terminal */
	    {
#line 301 "parser.act"

		(ZI166) = table_add_basic(grammar_table(sid_current_grammar), &(ZI160),
			sid_current_grammar, FALSE);
		if ((ZI166) == NULL) {
			E_duplicate_basic((&ZI160));
			nstring_destroy(&(ZI160));
		}
	
#line 5524 "tmp.parser.c"
	    }
	    /* END OF ACTION: terminal */
	    ZR133 (sid_current_grammar, &ZI131, &ZI132);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: x-terminal */
	    {
#line 319 "parser.act"

		if ((ZI166)) {
			KeyT *key = entry_key((ZI166));
			BasicT *basic = entry_get_basic((ZI166));
			if (types_contains_names((&ZI131))) {
				E_basic_param_has_names(key, (&ZI131));
			}
			if (types_contains_names((&ZI132))) {
				E_basic_result_has_names(key, (&ZI132));
			}
			if (types_contains_references((&ZI132))) {
				E_basic_result_has_refs(key, (&ZI132));
			}
			if (!types_equal_zero_tuple((&ZI131))) {
				E_basic_param_mismatch(key, (&ZI131));
			}
			if (!basic_get_ignored(basic)) {
				EntryT *type;

				type = types_find_ignored((&ZI131));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
				}

				type = types_find_ignored((&ZI132));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
				}
			}
			types_assign(basic_result(basic), (&ZI132));
		} else {
			types_destroy((&ZI132));
		}
		types_destroy((&ZI131));
	
#line 5570 "tmp.parser.c"
	    }
	    /* END OF ACTION: x-terminal */
	    ZR248 (sid_current_grammar);
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case (LEXER_TOK_IGNORE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF INLINE: 168 */
	    {
		{
		    NStringT ZI160;
		    EntryP ZI166;
		    TypeTupleT ZI131;
		    TypeTupleT ZI132;

		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 5599 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: i-terminal */
		    {
#line 310 "parser.act"

		(ZI166) = table_add_basic(grammar_table(sid_current_grammar), &(ZI160),
			sid_current_grammar, TRUE);
		if ((ZI166) == NULL) {
			E_duplicate_basic((&ZI160));
			nstring_destroy(&(ZI160));
		}
	
#line 5618 "tmp.parser.c"
		    }
		    /* END OF ACTION: i-terminal */
		    ZR133 (sid_current_grammar, &ZI131, &ZI132);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		    /* BEGINNING OF ACTION: x-terminal */
		    {
#line 319 "parser.act"

		if ((ZI166)) {
			KeyT *key = entry_key((ZI166));
			BasicT *basic = entry_get_basic((ZI166));
			if (types_contains_names((&ZI131))) {
				E_basic_param_has_names(key, (&ZI131));
			}
			if (types_contains_names((&ZI132))) {
				E_basic_result_has_names(key, (&ZI132));
			}
			if (types_contains_references((&ZI132))) {
				E_basic_result_has_refs(key, (&ZI132));
			}
			if (!types_equal_zero_tuple((&ZI131))) {
				E_basic_param_mismatch(key, (&ZI131));
			}
			if (!basic_get_ignored(basic)) {
				EntryT *type;

				type = types_find_ignored((&ZI131));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
				}

				type = types_find_ignored((&ZI132));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
				}
			}
			types_assign(basic_result(basic), (&ZI132));
		} else {
			types_destroy((&ZI132));
		}
		types_destroy((&ZI131));
	
#line 5664 "tmp.parser.c"
		    }
		    /* END OF ACTION: x-terminal */
		    ZR248 (sid_current_grammar);
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
#line 1581 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 5684 "tmp.parser.c"
		    }
		    /* END OF ACTION: expected-identifier */
		    /* BEGINNING OF ACTION: skip-to-end-of-terminal-decn */
		    {
#line 1805 "parser.act"

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
	
#line 5711 "tmp.parser.c"
		    }
		    /* END OF ACTION: skip-to-end-of-terminal-decn */
		}
	      ZL2:;
	    }
	    /* END OF INLINE: 168 */
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
#line 1593 "parser.act"

		if (!sid_propagating_error) {
			E_expected_terminal_decn();
		}
	
#line 5736 "tmp.parser.c"
	}
	/* END OF ACTION: expected-terminal-decn */
	/* BEGINNING OF ACTION: skip-to-end-of-terminal-decn */
	{
#line 1805 "parser.act"

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
	
#line 5763 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-terminal-decn */
    }
}

static void
ZR228(GrammarP sid_current_grammar)
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
#line 1671 "parser.act"

		if (!sid_propagating_error) {
			E_expected_define();
		}
	
#line 5795 "tmp.parser.c"
	}
	/* END OF ACTION: expected-define */
    }
}

static void
ZR231(GrammarP sid_current_grammar, TypeTupleT *ZI208)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI160;

	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_IDENTIFIER):
	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 5818 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF ACTION: prod-action */
	{
#line 1065 "parser.act"

		if (sid_current_entry && sid_current_alt) {
			EntryT *entry;

			entry = scope_stack_get_action(&sid_scope_stack,
				grammar_table(sid_current_grammar), (&ZI160));
			if (entry) {
				sid_current_item = item_create(entry);
			} else {
				E_unknown_action((&ZI160));
				sid_current_item = NULL;
				(void) alt_deallocate(sid_current_alt);
				sid_current_alt  = NULL;
			}
		} else {
			sid_current_item = NULL;
		}
		nstring_destroy(&(ZI160));
	
#line 5848 "tmp.parser.c"
	}
	/* END OF ACTION: prod-action */
	ZR232 (sid_current_grammar);
	ZR209 (sid_current_grammar, ZI208);
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
#line 1581 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 5869 "tmp.parser.c"
	}
	/* END OF ACTION: expected-identifier */
	/* BEGINNING OF ACTION: skip-to-end-of-item */
	{
#line 1894 "parser.act"

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
	
#line 5901 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-item */
    }
}

static void
ZR232(GrammarP sid_current_grammar)
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
#line 1647 "parser.act"

		if (!sid_propagating_error) {
			E_expected_end_action();
		}
	
#line 5933 "tmp.parser.c"
	}
	/* END OF ACTION: expected-end-action */
    }
}

static void
ZR197(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF INLINE: 199 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_BEGIN_HACTION):
		{
		    NStringT ZI160;
		    EntryP ZI166;
		    TypeTupleT ZI131;
		    TypeTupleT ZI132;

		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case (LEXER_TOK_IDENTIFIER):
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 5965 "tmp.parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		      default:
			goto ZL3;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: action */
		    {
#line 560 "parser.act"

		(ZI166) = scope_stack_add_action(sid_current_scope,
			grammar_table(sid_current_grammar), &(ZI160), sid_enclosing_rule,
			&sid_redefining_entry, FALSE);
			sid_current_entry = (ZI166);
		if (!(ZI166)) {
			E_duplicate_action((&ZI160));
			nstring_destroy(&(ZI160));
		}
	
#line 5986 "tmp.parser.c"
		    }
		    /* END OF ACTION: action */
		    ZR232 (sid_current_grammar);
		    ZR133 (sid_current_grammar, &ZI131, &ZI132);
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		    /* BEGINNING OF ACTION: x-action */
		    {
#line 582 "parser.act"

		if ((ZI166)) {
			KeyT       *key     = entry_key(sid_current_entry);
			ActionT    *action  = entry_get_action((ZI166));
			TypeTupleT *param   = action_param(action);
			TypeTupleT *result  = action_result(action);
			BoolT       errored = FALSE;

			if (types_contains_names((&ZI131))) {
				E_action_param_has_names(key, (&ZI131));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(param, (&ZI131))) {
					E_action_param_mismatch(key, param, (&ZI131));
					errored = TRUE;
				}
			}

			if (types_contains_names((&ZI132))) {
				E_action_result_has_names(key, (&ZI132));
				errored = TRUE;
			}

			if (types_contains_references((&ZI132))) {
				E_action_result_has_refs(key, (&ZI132));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(result, (&ZI132))) {
					E_action_result_mismatch(key, result, (&ZI132));
					errored = TRUE;
				}
			}

			if (!action_get_ignored(action)) {
				EntryT *type;

				type = types_find_ignored((&ZI131));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
					errored = TRUE;
				}

				type = types_find_ignored((&ZI132));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
					errored = TRUE;
				}
			}

			if (errored || sid_redefining_entry) {
				types_destroy((&ZI131));
				types_destroy((&ZI132));
			} else {
				types_assign(param, (&ZI131));
				types_assign(result, (&ZI132));
			}
		} else {
			types_destroy((&ZI131));
			types_destroy((&ZI132));
		}
	
#line 6063 "tmp.parser.c"
		    }
		    /* END OF ACTION: x-action */
		    ZR248 (sid_current_grammar);
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
		    /* BEGINNING OF INLINE: 202 */
		    {
			{
			    NStringT ZI160;
			    EntryP ZI166;
			    TypeTupleT ZI131;
			    TypeTupleT ZI132;

			    switch (CURRENT_TERMINAL) {
			      case (LEXER_TOK_IDENTIFIER):
				/* BEGINNING OF EXTRACT: IDENTIFIER */
				{
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 6099 "tmp.parser.c"
				}
				/* END OF EXTRACT: IDENTIFIER */
				break;
			      default:
				goto ZL5;
			    }
			    ADVANCE_LEXER;
			    /* BEGINNING OF ACTION: i-action */
			    {
#line 571 "parser.act"

		(ZI166) = scope_stack_add_action(sid_current_scope,
			grammar_table(sid_current_grammar), &(ZI160), sid_enclosing_rule,
			&sid_redefining_entry, TRUE);
			sid_current_entry = (ZI166);
		if (!(ZI166)) {
			E_duplicate_action((&ZI160));
			nstring_destroy(&(ZI160));
		}
	
#line 6120 "tmp.parser.c"
			    }
			    /* END OF ACTION: i-action */
			    ZR232 (sid_current_grammar);
			    ZR133 (sid_current_grammar, &ZI131, &ZI132);
			    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL5;
			    }
			    /* BEGINNING OF ACTION: x-action */
			    {
#line 582 "parser.act"

		if ((ZI166)) {
			KeyT       *key     = entry_key(sid_current_entry);
			ActionT    *action  = entry_get_action((ZI166));
			TypeTupleT *param   = action_param(action);
			TypeTupleT *result  = action_result(action);
			BoolT       errored = FALSE;

			if (types_contains_names((&ZI131))) {
				E_action_param_has_names(key, (&ZI131));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(param, (&ZI131))) {
					E_action_param_mismatch(key, param, (&ZI131));
					errored = TRUE;
				}
			}

			if (types_contains_names((&ZI132))) {
				E_action_result_has_names(key, (&ZI132));
				errored = TRUE;
			}

			if (types_contains_references((&ZI132))) {
				E_action_result_has_refs(key, (&ZI132));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(result, (&ZI132))) {
					E_action_result_mismatch(key, result, (&ZI132));
					errored = TRUE;
				}
			}

			if (!action_get_ignored(action)) {
				EntryT *type;

				type = types_find_ignored((&ZI131));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
					errored = TRUE;
				}

				type = types_find_ignored((&ZI132));
				if (type != NULL) {
					E_ignored_type(key_get_string(entry_key(type)));
					errored = TRUE;
				}
			}

			if (errored || sid_redefining_entry) {
				types_destroy((&ZI131));
				types_destroy((&ZI132));
			} else {
				types_assign(param, (&ZI131));
				types_assign(result, (&ZI132));
			}
		} else {
			types_destroy((&ZI131));
			types_destroy((&ZI132));
		}
	
#line 6197 "tmp.parser.c"
			    }
			    /* END OF ACTION: x-action */
			    ZR248 (sid_current_grammar);
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
#line 1581 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 6217 "tmp.parser.c"
			    }
			    /* END OF ACTION: expected-identifier */
			    /* BEGINNING OF ACTION: skip-to-end-of-action-decn */
			    {
#line 1871 "parser.act"

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
	
#line 6245 "tmp.parser.c"
			    }
			    /* END OF ACTION: skip-to-end-of-action-decn */
			}
		      ZL4:;
		    }
		    /* END OF INLINE: 202 */
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
#line 1581 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 6268 "tmp.parser.c"
		}
		/* END OF ACTION: expected-identifier */
		/* BEGINNING OF ACTION: skip-to-end-of-action-decn */
		{
#line 1871 "parser.act"

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
	
#line 6296 "tmp.parser.c"
		}
		/* END OF ACTION: skip-to-end-of-action-decn */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 199 */
    }
}

static void
ZR242(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_242:;
    {
	ZR235 (sid_current_grammar);
	/* BEGINNING OF INLINE: 301 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (LEXER_TOK_IDENTIFIER): case (LEXER_TOK_OPEN_HTUPLE): case (LEXER_TOK_BEGIN_HACTION): case (LEXER_TOK_BEGIN_HRULE):
	      case (LEXER_TOK_PRED_HRESULT): case (LEXER_TOK_IGNORE): case (LEXER_TOK_REFERENCE):
		{
		    /* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list::production-defn-non-empty-alternative */
		    goto ZL2_242;
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
	/* END OF INLINE: 301 */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-item */
	{
#line 1695 "parser.act"

		if (!sid_propagating_error) {
			E_expected_item();
		}
	
#line 6346 "tmp.parser.c"
	}
	/* END OF ACTION: expected-item */
	/* BEGINNING OF ACTION: skip-to-end-of-item */
	{
#line 1894 "parser.act"

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
	
#line 6378 "tmp.parser.c"
	}
	/* END OF ACTION: skip-to-end-of-item */
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 2016 "parser.act"

		sid_propagating_error = FALSE;
	
#line 6387 "tmp.parser.c"
	}
	/* END OF ACTION: skip-recover */
    }
}

static void
ZR276(GrammarP sid_current_grammar)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI160;

	switch (CURRENT_TERMINAL) {
	  case (LEXER_TOK_IDENTIFIER):
	    /* BEGINNING OF EXTRACT: IDENTIFIER */
	    {
#line 266 "parser.act"

		nstring_assign(&ZI160, lexer_string_value(sid_current_stream));
	
#line 6410 "tmp.parser.c"
	    }
	    /* END OF EXTRACT: IDENTIFIER */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF ACTION: add-entry */
	{
#line 1548 "parser.act"

		EntryT *entry;

		entry = table_get_rule(grammar_table(sid_current_grammar), (&ZI160));
		if (entry) {
			if (entry_list_contains(grammar_entry_list(sid_current_grammar), entry)) {
				E_mult_entry(entry_key(entry));
			} else {
				entry_list_add(grammar_entry_list(sid_current_grammar), entry);
				rule_required(entry_get_rule(entry));
			}
		} else {
			E_unknown_rule((&ZI160));
		}
		nstring_destroy(&(ZI160));
	
#line 6437 "tmp.parser.c"
	}
	/* END OF ACTION: add-entry */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-identifier */
	{
#line 1581 "parser.act"

		if (!sid_propagating_error) {
			E_expected_identifier();
		}
	
#line 6452 "tmp.parser.c"
	}
	/* END OF ACTION: expected-identifier */
    }
}

static void
ZR178(GrammarP sid_current_grammar, TypeTupleT *ZI135)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_178:;
    {
	ZR175 (sid_current_grammar, ZI135);
	/* BEGINNING OF INLINE: 180 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-close-tuple-or-skipped-or-eof */
		{
#line 2025 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_CLOSE_HTUPLE)
			|| CURRENT_TERMINAL == (LEXER_TOK_EOF)
			|| sid_propagating_error);
	
#line 6482 "tmp.parser.c"
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
		    goto ZL2_178;
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
#line 1599 "parser.act"

		if (!sid_propagating_error) {
			E_expected_separator();
		}
	
#line 6514 "tmp.parser.c"
		}
		/* END OF ACTION: expected-separator */
		/* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list::lhs-name-tuple::lhs-name-list-1 */
		goto ZL2_178;
		/* END OF INLINE: sid-parse-grammar::production-defn-list::lhs-name-tuple::lhs-name-list-1 */
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
	/* END OF INLINE: 180 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR240(GrammarP sid_current_grammar)
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
#line 1689 "parser.act"

		if (!sid_propagating_error) {
			E_expected_end_rule();
		}
	
#line 6558 "tmp.parser.c"
	}
	/* END OF ACTION: expected-end-rule */
    }
}

static void
ZR248(GrammarP sid_current_grammar)
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
#line 1623 "parser.act"

		if (!sid_propagating_error) {
			E_expected_terminator();
		}
	
#line 6590 "tmp.parser.c"
	}
	/* END OF ACTION: expected-terminator */
    }
}

static void
ZR190(GrammarP sid_current_grammar, TypeTupleT *ZI135)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_190:;
    {
	ZR187 (sid_current_grammar, ZI135);
	/* BEGINNING OF INLINE: 192 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-close-tuple-or-skipped-or-eof */
		{
#line 2025 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_CLOSE_HTUPLE)
			|| CURRENT_TERMINAL == (LEXER_TOK_EOF)
			|| sid_propagating_error);
	
#line 6620 "tmp.parser.c"
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
		    goto ZL2_190;
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
#line 1599 "parser.act"

		if (!sid_propagating_error) {
			E_expected_separator();
		}
	
#line 6652 "tmp.parser.c"
		}
		/* END OF ACTION: expected-separator */
		/* BEGINNING OF INLINE: sid-parse-grammar::production-defn-list::rhs-name-tuple::rhs-name-list-1 */
		goto ZL2_190;
		/* END OF INLINE: sid-parse-grammar::production-defn-list::rhs-name-tuple::rhs-name-list-1 */
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
	/* END OF INLINE: 192 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

/* BEGINNING OF TRAILER */

#line 2040 "parser.act"


#line 6675 "tmp.parser.c"

/* END OF FILE */
