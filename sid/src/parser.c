/*
 * Automatically generated from the files:
 *	parser.sid
 * and
 *	parser.act
 * by:
 *	/Users/kate/svn/tendra20/obj-regen/bin/sid
 */

/* BEGINNING OF HEADER */

#line 74 "parser.act"


	/* $Id$ */

	/*
	 * Copyright 2008-2011, The TenDRA Project.
	 * Copyright 1997, United Kingdom Secretary of State for Defence.
	 *
	 * See doc/copyright/ for the full copyright terms.
	 */

	#include <limits.h>
	#include <assert.h>

	#include <exds/common.h>
	#include <exds/exception.h>
	#include <exds/bitvec.h>
	#include <exds/dalloc.h>
	#include <exds/dstring.h>

	#include <shared/check.h>
	#include <shared/error.h>

	#include "adt/action.h"
	#include "adt/basic.h"
	#include "adt/key.h"
	#include "adt/non-local.h"
	#include "adt/rule.h"
	#include "adt/scope.h"
	#include "adt/table.h"
	#include "adt/types.h"

	#include "parser.h"
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


	static void err_redeclared(const char *type, NStringT *name) {
		error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
			"identifier '%S' redeclared as %s",
			(void *) name, type);
	}

	static void err_unknown(const char *type, NStringT *name) {
		error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
			"%s '%S' hasn't been declared",
			type, (void *) name);
	}

	static void err_basic_mismatch(const char *type, KeyT *key, TypeTupleT *a) {
		error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
			"parameter type mismatch for %s of terminal '%K' [%Y should be ()])",
			type, (void *) key, (void *) a);
	}

	static void err_type_mismatch(const char *item, const char *verb, KeyT *key, TypeTupleT *a, TypeTupleT *b) {
		error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
			"%s type mismatch for %s '%K' [%Y should be %Y]",
			item, verb, (void *) key, (void *) a, (void *) b);
	}

	static void err_type_mismatch_of(const char *item, const char *verb, const char *entity,
		KeyT *key, TypeTupleT *a, TypeTupleT *b) {
		error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
			"%s type mismatch for %s of %s '%K' [%Y should be %Y]",
			item, verb, entity, (void *) key, (void *) a, (void *) b);
	}

	static void err_expected(const char *item) {
		error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
			"expected %s", item);
	}

	static void err_ignored(const char *item, NStringT *name) {
		error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
			"invocation of ignored %s '%S'", item, (void *) name);
	}

	static void err_undefined_name(KeyT *name, KeyT *rule, unsigned alt) {
		error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
			"undefined parameter name '%K' in alternative %u of production '%K'",
			(void *) name, alt, (void *) rule);
	}

	static void err_redefined_name(KeyT *name, KeyT *rule, unsigned alt) {
		error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
			"redefined name '%K' in alternative %u of production '%K'",
			(void *) name, alt, (void *) rule);
	}

#line 139 "parser.c"


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
#line 1034 "parser.act"

		if (sid_current_entry) {
			sid_current_alt = alt_create();
		}
	
#line 253 "parser.c"
		}
		/* END OF ACTION: handler */
		ZR248 (sid_current_grammar);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: x-handler */
		{
#line 1054 "parser.act"

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
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result formals are not defined in exception handler alternative of production '%K'",
					(void *) entry_key(sid_external_rule));
			}
		}
	
#line 283 "parser.c"
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
#line 2103 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_CLOSE_HTUPLE)
			|| CURRENT_TERMINAL == (LEXER_TOK_EOF)
			|| sid_propagating_error);
	
#line 317 "parser.c"
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
#line 1677 "parser.act"

		if (!sid_propagating_error) {
			err_expected("','");
		}
	
#line 349 "parser.c"
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
#line 247 "parser.act"

		nstring_assign(&ZI165, lexer_string_value(sid_current_stream));
	
#line 381 "parser.c"
			}
			/* END OF EXTRACT: BASIC */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: x-basic */
			{
#line 349 "parser.act"

		EntryT *entry = table_get_entry(grammar_table(sid_current_grammar), (&ZI165));

		if (entry) {
			if (!entry_is_basic(entry)) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"quoted identifier '%S' is not a terminal",
					(void *) (&ZI165));
			}
		}

	
#line 400 "parser.c"
			}
			/* END OF ACTION: x-basic */
		}
		break;
	case (LEXER_TOK_IDENTIFIER):
		{
			/* BEGINNING OF EXTRACT: IDENTIFIER */
			{
#line 243 "parser.act"

		nstring_assign(&ZI165, lexer_string_value(sid_current_stream));
	
#line 413 "parser.c"
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
#line 227 "parser.act"

		nstring_assign(ZO165, (&ZI165));
	#line 434 "parser.c"
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
#line 827 "parser.act"

		if (sid_current_entry) {
			KeyT *key;

			key = entry_key(sid_current_entry);

			if (rule_is_defined(sid_current_rule)) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"production '%K' is already defined", (void *) key);
				sid_current_entry = NULL;
				types_destroy((ZI134));
				types_destroy((ZI135));
			} else {
				TypeTupleT *param   = rule_param(sid_current_rule);
				TypeTupleT *result  = rule_result(sid_current_rule);
				BoolT       errored = FALSE;

				rule_defined(sid_current_rule);
				if (!types_disjoint_names((ZI134))) {
					error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
						"parameter names are not disjoint (or are missing) for production '%K' [parameter = %Y]",
						(void *) key, (void *) (ZI134));
					errored = TRUE;
				}

				if (types_check_shadowing((ZI134), &sid_scope_stack,
					sid_current_rule)) {
					errored = TRUE;
				}

				if (sid_redefining_entry) {
					if (!types_fillin_names(param, (ZI134))) {
						err_type_mismatch("parameter", "production", key, (ZI134), param);
						errored = TRUE;
					}
					types_destroy((ZI134));
				} else {
					types_assign(param, (ZI134));
				}

				if (!types_disjoint_names((ZI135))) {
					error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
						"result names are not disjoint (or are missing) for production '%K' [result = %Y]",
						(void *) key, (void *) (ZI135));
					errored = TRUE;
				}

				if (types_check_shadowing((ZI135), &sid_scope_stack,
					sid_current_rule)) {
					errored = TRUE;
				}

				if (types_contains_references((ZI135))) {
					error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
						"result of declaration or definition of rule '%K' has references [result = %Y]",
						(void *) key, (void *) (ZI135));
					errored = TRUE;
				}

				if (sid_redefining_entry) {
					if (!types_fillin_names(result, (ZI135))) {
						err_type_mismatch("result", "production", key, (ZI135), result);
						errored = TRUE;
					}
					types_destroy((ZI135));
				} else {
					types_assign(result, (ZI135));
				}

				{
					EntryT *type;

					type = types_find_ignored(param);
					if (type != NULL) {
						err_ignored("type", key_get_string(entry_key(type)));
						errored = TRUE;
					}

					type = types_find_ignored(result);
					if (type != NULL) {
						err_ignored("type", key_get_string(entry_key(type)));
						errored = TRUE;
					}
				}

				if (errored) {
					sid_current_entry = NULL;
				} else {
					if (types_intersect(param, result)) {
						error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
							"parameter and result names are not disjoint for production '%K' [parameter = %Y, result = %Y]",
							(void *) key, (void *) param, (void *) result);
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
	
#line 554 "parser.c"
			}
			/* END OF ACTION: prod */
			/* BEGINNING OF ACTION: push-scope */
			{
#line 940 "parser.act"

		if (sid_current_entry) {
			KeyT     *key   = entry_key(sid_current_entry);
			NStringT *scope = key_get_string(key);

			scope_stack_push(&sid_scope_stack, scope);
		}
	
#line 568 "parser.c"
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
#line 1761 "parser.act"

		if (!sid_propagating_error) {
			err_expected("'{'");
		}
	
#line 599 "parser.c"
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
#line 946 "parser.act"

		if (sid_current_entry) {
			scope_stack_pop(&sid_scope_stack);
		}
	
#line 620 "parser.c"
			}
			/* END OF ACTION: pop-scope */
			/* BEGINNING OF ACTION: x-prod */
			{
#line 931 "parser.act"

		if (sid_current_entry) {
			nstring_assign(rule_maximum_scope(sid_current_rule),
				&sid_maximum_scope);
		} else {
			nstring_destroy(&sid_maximum_scope);
		}
	
#line 634 "parser.c"
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
#line 753 "parser.act"

		if (sid_current_entry) {
			KeyT       *key     = entry_key(sid_current_entry);
			TypeTupleT *param   = rule_param(sid_current_rule);
			TypeTupleT *result  = rule_result(sid_current_rule);
			BoolT       errored = FALSE;

			if (types_contains_names((ZI134))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"parameter of declaration of rule '%K' has names [parameter = %Y]",
					(void *) key, (void *) (ZI134));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(param, (ZI134))) {
					err_type_mismatch("parameter", "production", key, (ZI134), param);
					errored = TRUE;
				}
			}

			if (types_contains_names((ZI135))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result of declaration of rule '%K' has names [result = %Y]",
					(void *) key, (void *) (ZI135));
				errored = TRUE;
			}

			if (types_contains_references((ZI135))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result of declaration or definition of rule '%K' has references [result = %Y]",
					(void *) key, (void *) (ZI135));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(result, (ZI135))) {
					err_type_mismatch("result", "production", key, (ZI135), result);
					errored = TRUE;
				}
			}

			{
				EntryT *type;

				type = types_find_ignored((ZI134));
				if (type != NULL) {
					err_ignored("type", key_get_string(entry_key(type)));
					errored = TRUE;
				}

				type = types_find_ignored((ZI135));
				if (type != NULL) {
					err_ignored("type", key_get_string(entry_key(type)));
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
	
#line 719 "parser.c"
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
#line 991 "parser.act"

		sid_num_alternatives++;
		if (sid_num_alternatives == ALT_LIMIT) {
			error_posn(ERR_FATAL, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
				"too many alternatives in grammar");
			UNREACHED;
		}

		if (!sid_internal_rule) {
			sid_alternative++;
		}

		if (sid_current_entry) {
			if (rule_has_empty_alt(sid_current_rule)) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"production '%K' has multiple empty alternatives",
					(void *) entry_key(sid_external_rule));
			} else if (!types_equal_zero_tuple(rule_result(sid_current_rule))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result formals are not defined in alternative %u of production '%K'",
					sid_alternative, (void *) entry_key(sid_external_rule));
			} else {
				rule_add_empty_alt(sid_current_rule);
			}
		}
	
#line 771 "parser.c"
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
#line 1008 "parser.act"

		sid_num_alternatives++;
		if (sid_num_alternatives == ALT_LIMIT) {
			error_posn(ERR_FATAL, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
				"too many alternatives in grammar");
			UNREACHED;
		}

		if (!sid_internal_rule) {
			sid_alternative++;
		}

		if (sid_current_entry) {
			sid_current_alt = alt_create();
		}
	
#line 804 "parser.c"
			}
			/* END OF ACTION: non-empty-alt */
			ZR248 (sid_current_grammar);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: x-non-empty-alt */
			{
#line 1028 "parser.act"

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
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result formals are not defined in alternative %u of production '%K'",
					sid_alternative, (void *) entry_key(sid_external_rule));
			}
		}
	
#line 834 "parser.c"
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
#line 1779 "parser.act"

		if (!sid_propagating_error) {
			err_expected("alternative");
		}
	
#line 855 "parser.c"
		}
		/* END OF ACTION: expected-alternative */
		/* BEGINNING OF ACTION: skip-to-end-of-alternative */
		{
#line 1999 "parser.act"

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
	
#line 885 "parser.c"
		}
		/* END OF ACTION: skip-to-end-of-alternative */
		/* BEGINNING OF ACTION: skip-recover */
		{
#line 2094 "parser.act"

		sid_propagating_error = FALSE;
	
#line 894 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 941 "parser.c"
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
#line 367 "parser.act"

		types_init(&(ZI134));
	
#line 973 "parser.c"
					}
					/* END OF ACTION: init-tuple */
					/* BEGINNING OF ACTION: init-tuple */
					{
#line 367 "parser.act"

		types_init(&(ZI135));
	
#line 982 "parser.c"
					}
					/* END OF ACTION: init-tuple */
					/* BEGINNING OF ACTION: rule */
					{
#line 735 "parser.act"

		sid_current_entry = scope_stack_add_rule(sid_current_scope,
			grammar_table(sid_current_grammar), &(ZI163), sid_enclosing_rule,
			&sid_redefining_entry);
		if (sid_current_entry) {
			sid_current_rule = entry_get_rule(sid_current_entry);
		} else {
			err_redeclared("rule", (&ZI163));
			nstring_destroy(&(ZI163));
		}
	
#line 999 "parser.c"
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
#line 1785 "parser.act"

		if (!sid_propagating_error) {
			err_expected("rule declaration or rule or non local name definition");
		}
	
#line 1023 "parser.c"
				}
				/* END OF ACTION: expected-other-defn */
				/* BEGINNING OF ACTION: destroy-string */
				{
#line 1830 "parser.act"

		nstring_destroy(&(ZI163));
	
#line 1032 "parser.c"
				}
				/* END OF ACTION: destroy-string */
				/* BEGINNING OF ACTION: skip-to-end-of-other-defn */
				{
#line 2024 "parser.act"

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
	
#line 1061 "parser.c"
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
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 1090 "parser.c"
		}
		/* END OF ACTION: current-tuple */
		ZR201 (sid_current_grammar);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: init-tuple */
		{
#line 367 "parser.act"

		types_init(&(ZI138));
	
#line 1104 "parser.c"
		}
		/* END OF ACTION: init-tuple */
		ZR187 (sid_current_grammar, &ZI138);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: skip-recover */
		{
#line 2094 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1118 "parser.c"
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
#line 231 "parser.act"

		ZO138->head = ZI138.head;

		if (ZO138->head == NULL) {
			ZO138->tail = &ZO138->head;
		} else {
			ZO138->tail= ZI138.tail ;
		}
	#line 1143 "parser.c"
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
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 1192 "parser.c"
		}
		/* END OF ACTION: current-tuple */
		ZR201 (sid_current_grammar);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: init-tuple */
		{
#line 367 "parser.act"

		types_init(&(ZI138));
	
#line 1206 "parser.c"
		}
		/* END OF ACTION: init-tuple */
		ZR199 (sid_current_grammar, &ZI138);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: skip-recover */
		{
#line 2094 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1220 "parser.c"
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
#line 231 "parser.act"

		ZO138->head = ZI138.head;

		if (ZO138->head == NULL) {
			ZO138->tail = &ZO138->head;
		} else {
			ZO138->tail= ZI138.tail ;
		}
	#line 1245 "parser.c"
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
#line 1057 "parser.act"

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
	
#line 1290 "parser.c"
			}
			/* END OF ACTION: save */
			ZR239 (sid_current_grammar);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: restore */
			{
#line 1082 "parser.act"

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
	
#line 1314 "parser.c"
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
#line 2094 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1339 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 1375 "parser.c"
					}
					/* END OF EXTRACT: IDENTIFIER */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: add-type */
					{
#line 263 "parser.act"

		if (table_add_type(grammar_table(sid_current_grammar), &(ZI163), FALSE) == NULL) {
			err_redeclared("type", (&ZI163));
			nstring_destroy(&(ZI163));
		}
	
#line 1388 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 1406 "parser.c"
						}
						/* END OF EXTRACT: IDENTIFIER */
						break;
					default:
						goto ZL3;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: i-add-type */
					{
#line 270 "parser.act"

		if (table_add_type(grammar_table(sid_current_grammar), &(ZI163), TRUE) == NULL) {
			err_redeclared("type", (&ZI163));
			nstring_destroy(&(ZI163));
		}
	
#line 1423 "parser.c"
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
#line 1653 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier");
		}
	
#line 1442 "parser.c"
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
#line 949 "parser.act"

		(ZI172) = sid_current_entry;
		(ZI75)  = sid_enclosing_rule;

		sid_enclosing_rule = sid_current_rule;
	
#line 1504 "parser.c"
			}
			/* END OF ACTION: save-scope */
			ZR177 (sid_current_grammar);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: restore-scope */
			{
#line 956 "parser.act"

		sid_current_entry  = (ZI172);
		sid_current_rule   = sid_enclosing_rule;
		sid_enclosing_rule = (ZI75);
		sid_alternative    = 0;
		sid_internal_rule  = FALSE;
		sid_external_rule  = sid_current_entry;

		nstring_init(&sid_maximum_scope);
	
#line 1525 "parser.c"
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
#line 1731 "parser.act"

		if (!sid_propagating_error) {
			err_expected("']'");
		}
	
#line 1550 "parser.c"
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
#line 1695 "parser.act"

		if (!sid_propagating_error) {
			err_expected("'->'");
		}
	
#line 1596 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 1616 "parser.c"
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
	
#line 1662 "parser.c"
			}
			/* END OF ACTION: add-name */
		}
		break;
	case (LEXER_TOK_IGNORE):
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: add-void */
			{
#line 545 "parser.act"

		EntryT *entry;

		entry = table_add_generated_name(grammar_table(sid_current_grammar));
		types_add_name_entry((ZI138), entry);
	
#line 1679 "parser.c"
			}
			/* END OF ACTION: add-void */
		}
		break;
	case (LEXER_TOK_PRED_HRESULT):
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: add-pred */
			{
#line 538 "parser.act"

		if (sid_current_pred_id) {
			error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
				"result contains more than one predicate result symbol");
		}
		sid_current_pred_id = TRUE;
		types_add_name_entry((ZI138), grammar_get_predicate_id(sid_current_grammar));
	
#line 1698 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 1719 "parser.c"
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
			error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
				"assignment to undefined name '%S'", (void *) (&ZI163));
			types_add_name((ZI138), grammar_table(sid_current_grammar), &(ZI163), FALSE);
		}
	
#line 1771 "parser.c"
					}
					/* END OF ACTION: add-var */
				}
				goto ZL2;
			ZL3:;
				{
					/* BEGINNING OF ACTION: expected-identifier */
					{
#line 1653 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier");
		}
	
#line 1786 "parser.c"
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
#line 1707 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier, '?' or '!'");
		}
	
#line 1811 "parser.c"
		}
		/* END OF ACTION: expected-lhs-name */
		/* BEGINNING OF ACTION: skip-to-end-of-lhs-name */
		{
#line 1905 "parser.act"

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
	
#line 1838 "parser.c"
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
#line 2094 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1863 "parser.c"
		}
		/* END OF ACTION: skip-recover */
		/* BEGINNING OF INLINE: 278 */
		{
			{
				/* BEGINNING OF ACTION: is-blt-entry-or-end-scope-or-eof */
				{
#line 2097 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_EOF)
			|| CURRENT_TERMINAL == (LEXER_TOK_END_HSCOPE)
			|| CURRENT_TERMINAL == (LEXER_TOK_BLT_HENTRY));
	
#line 1877 "parser.c"
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
#line 1791 "parser.act"

		if (!sid_propagating_error) {
			err_expected("rule declaration or definition, or action declaration");
		}
	
#line 1912 "parser.c"
		}
		/* END OF ACTION: expected-production-defn */
		/* BEGINNING OF ACTION: skip-to-end-of-production-defn */
		{
#line 2048 "parser.act"

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
	
#line 1941 "parser.c"
		}
		/* END OF ACTION: skip-to-end-of-production-defn */
		/* BEGINNING OF ACTION: skip-recover */
		{
#line 2094 "parser.act"

		sid_propagating_error = FALSE;
	
#line 1950 "parser.c"
		}
		/* END OF ACTION: skip-recover */
		/* BEGINNING OF INLINE: 279 */
		{
			{
				/* BEGINNING OF ACTION: is-blt-entry-or-end-scope-or-eof */
				{
#line 2097 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_EOF)
			|| CURRENT_TERMINAL == (LEXER_TOK_END_HSCOPE)
			|| CURRENT_TERMINAL == (LEXER_TOK_BLT_HENTRY));
	
#line 1964 "parser.c"
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
#line 255 "parser.act"

		scope_stack_init(&sid_scope_stack);
		scope_stack_init(&sid_global_scope);
	
#line 1998 "parser.c"
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
#line 1797 "parser.act"

		if (!sid_propagating_error) {
			err_expected("'%types%'");
		}
	
#line 2023 "parser.c"
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
#line 1803 "parser.act"

		if (!sid_propagating_error) {
			err_expected("'%terminals%'");
		}
	
#line 2057 "parser.c"
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
#line 346 "parser.act"

		unsigned max_terminal = grammar_max_terminal(sid_current_grammar);

		bitvec_set_size(max_terminal);
		sid_finished_terminals = TRUE;
	
#line 2078 "parser.c"
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
#line 1809 "parser.act"

		if (!sid_propagating_error) {
			err_expected("'%productions%'");
		}
	
#line 2103 "parser.c"
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
#line 1815 "parser.act"

		if (!sid_propagating_error) {
			err_expected("'%entry%'");
		}
	
#line 2137 "parser.c"
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
#line 1821 "parser.act"

		if (!sid_propagating_error) {
			err_expected("end of file");
		}
	
#line 2172 "parser.c"
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
#line 1641 "parser.act"

		UNREACHED;
	
#line 2189 "parser.c"
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
#line 367 "parser.act"

		types_init(&(ZI138));
	
#line 2234 "parser.c"
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
#line 2094 "parser.act"

		sid_propagating_error = FALSE;
	
#line 2249 "parser.c"
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
#line 231 "parser.act"

		ZO138->head = ZI138.head;

		if (ZO138->head == NULL) {
			ZO138->tail = &ZO138->head;
		} else {
			ZO138->tail= ZI138.tail ;
		}
	#line 2274 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 2293 "parser.c"
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
	
#line 2339 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 2360 "parser.c"
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
	
#line 2410 "parser.c"
					}
					/* END OF ACTION: add-ref-name */
				}
				goto ZL2;
			ZL3:;
				{
					/* BEGINNING OF ACTION: expected-identifier */
					{
#line 1653 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier");
		}
	
#line 2425 "parser.c"
					}
					/* END OF ACTION: expected-identifier */
					/* BEGINNING OF ACTION: skip-to-end-of-rhs-name */
					{
#line 1927 "parser.act"

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
	
#line 2452 "parser.c"
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
#line 1713 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier or '&'");
		}
	
#line 2477 "parser.c"
		}
		/* END OF ACTION: expected-rhs-name */
		/* BEGINNING OF ACTION: skip-to-end-of-rhs-name */
		{
#line 1927 "parser.act"

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
	
#line 2504 "parser.c"
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
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2530 "parser.c"
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
#line 735 "parser.act"

		sid_current_entry = scope_stack_add_rule(sid_current_scope,
			grammar_table(sid_current_grammar), &(*ZI163), sid_enclosing_rule,
			&sid_redefining_entry);
		if (sid_current_entry) {
			sid_current_rule = entry_get_rule(sid_current_entry);
		} else {
			err_redeclared("rule", (ZI163));
			nstring_destroy(&(*ZI163));
		}
	
#line 2553 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI144, lexer_string_value(sid_current_stream));
	
#line 2579 "parser.c"
						}
						/* END OF EXTRACT: IDENTIFIER */
						break;
					default:
						goto ZL3;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: non-local */
					{
#line 656 "parser.act"

		(ZI263) = NULL;
		if (sid_enclosing_rule == NULL || sid_current_scope == &sid_global_scope) {
			error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
				"definition of non local name '%S' at global scope",
				(void *) (ZI163));
			nstring_destroy(&(*ZI163));
		} else {
			EntryT *type;

			type = table_get_type(grammar_table(sid_current_grammar), (&ZI144));
			if (type == NULL) {
				err_unknown("type", (&ZI144));
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
					err_redeclared("non-local", (ZI163));
					nstring_destroy(&(*ZI163));
				}
			}
		}
		nstring_destroy(&(ZI144));
	
#line 2623 "parser.c"
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
#line 1719 "parser.act"

		if (!sid_propagating_error) {
			err_expected("'<'");
		}
	
#line 2654 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI56, lexer_string_value(sid_current_stream));
	
#line 2674 "parser.c"
											}
											/* END OF EXTRACT: IDENTIFIER */
											break;
										default:
											goto ZL9;
										}
										ADVANCE_LEXER;
										/* BEGINNING OF ACTION: non-local-init */
										{
#line 693 "parser.act"

		EntryT *actionentry;

		actionentry = scope_stack_get_action(&sid_scope_stack,
			grammar_table(sid_current_grammar), (&ZI56));

		if (actionentry == NULL) {
			err_unknown("action", (&ZI56));
		} else if ((ZI263)) {
			EntryT     *type   = non_local_entry_get_type((ZI263));
			KeyT       *name   = entry_key(non_local_entry_get_name((ZI263)));
			ActionT    *action = entry_get_action(actionentry);
			TypeTupleT *param  = action_param(action);
			TypeTupleT *result = action_result(action);
			TypeTupleT  tuple;
			TypeTupleT  ref_tuple;

			if (action_get_ignored(action)) {
				err_ignored("action call", key_get_string(entry_key(actionentry)));
			}

			types_init(&tuple);
			types_init(&ref_tuple);
			types_add_type_entry(&tuple, type, FALSE);
			types_add_type_entry(&ref_tuple, type, TRUE);

			if (!types_equal(param, &tuple) && !types_equal(param, &ref_tuple)
				&& !types_equal_zero_tuple(param)) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"parameter type mismatch for initialiser of non local name '%K' [%Y should be %Y, %Y or ()]",
					(void *) name, (void *) param, (void *) &tuple, (void *) &ref_tuple);
			}

			if (!types_equal(result, &tuple)) {
				err_type_mismatch_of("result", "initialiser", "non-local name", name, result, &tuple);
			}

			types_destroy(&ref_tuple);
			types_destroy(&tuple);
			non_local_entry_set_initialiser((ZI263), actionentry);
		}
		nstring_destroy(&(ZI56));
	
#line 2728 "parser.c"
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
#line 1653 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier");
		}
	
#line 2749 "parser.c"
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
#line 1827 "parser.act"

		if (!sid_propagating_error) {
			err_expected("';' or '='");
		}
	
#line 2777 "parser.c"
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
#line 1653 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier");
		}
	
#line 2796 "parser.c"
					}
					/* END OF ACTION: expected-identifier */
					/* BEGINNING OF ACTION: destroy-string */
					{
#line 1830 "parser.act"

		nstring_destroy(&(*ZI163));
	
#line 2805 "parser.c"
					}
					/* END OF ACTION: destroy-string */
					/* BEGINNING OF ACTION: skip-to-end-of-other-defn */
					{
#line 2024 "parser.act"

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
	
#line 2834 "parser.c"
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
#line 367 "parser.act"

		types_init(&(ZI214));
	
#line 2869 "parser.c"
			}
			/* END OF ACTION: init-tuple */
			/* BEGINNING OF ACTION: add-void */
			{
#line 545 "parser.act"

		EntryT *entry;

		entry = table_add_generated_name(grammar_table(sid_current_grammar));
		types_add_name_entry((&ZI214), entry);
	
#line 2881 "parser.c"
			}
			/* END OF ACTION: add-void */
			/* BEGINNING OF ACTION: save-tuple */
			{
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2890 "parser.c"
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
#line 367 "parser.act"

		types_init(&(ZI214));
	
#line 2912 "parser.c"
			}
			/* END OF ACTION: init-tuple */
			/* BEGINNING OF ACTION: add-pred */
			{
#line 538 "parser.act"

		if (sid_current_pred_id) {
			error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
				"result contains more than one predicate result symbol");
		}
		sid_current_pred_id = TRUE;
		types_add_name_entry((&ZI214), grammar_get_predicate_id(sid_current_grammar));
	
#line 2926 "parser.c"
			}
			/* END OF ACTION: add-pred */
			/* BEGINNING OF ACTION: save-tuple */
			{
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2935 "parser.c"
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
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 2956 "parser.c"
			}
			/* END OF ACTION: save-tuple */
			/* BEGINNING OF ACTION: init-tuple */
			{
#line 367 "parser.act"

		types_init(&(ZI214));
	
#line 2965 "parser.c"
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
#line 1281 "parser.act"

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
						err_ignored("terminal", (&ZI163));
					}
				} else {
					err_unknown("identifier", (&ZI163));
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
				alt_names(sid_current_alt), err_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (param) {
					if (types_equal((&ZI217), param)) {
						item_add_param(sid_current_item, (&ZI217));
					} else {
						err_type_mismatch_of("parameter", "invocation", "rule",
							key, (&ZI217), param);
						types_destroy((&ZI217));
						errored = TRUE;
					}
				} else {
					if (!types_equal_zero_tuple((&ZI217))) {
						err_basic_mismatch("invocation", key, (&ZI217));
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
					alt_names(sid_current_alt), err_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((ZI214), result)) {
						types_add_new_names(alt_names(sid_current_alt),
							(ZI214), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
								"predicate result symbol used in result of something other than an action");
						}
						item_add_result(sid_current_item, (ZI214));
					} else {
						if (param) {
							err_type_mismatch_of("result", "invocation", "rule",
								key, (ZI214), result);
						} else {
							err_type_mismatch_of("result", "invocation", "terminal",
								key, (ZI214), result);
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
					error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
						"result names are not disjoint for invocation of rule '%K' [result = %Y]",
						(void *) key, (void *) (ZI214));
				} else {
					error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
						"result names are not disjoint for invocation of terminal '%K' [result = %Y]",
						(void *) key, (void *) (ZI214));
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
	
#line 3144 "parser.c"
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
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 3162 "parser.c"
						}
						/* END OF ACTION: current-tuple */
						/* BEGINNING OF ACTION: x-prod-rule-or-identity */
						{
#line 1397 "parser.act"

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
						err_ignored("terminal", (&ZI163));
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
					err_unknown("identifier", (&ZI163));
				}
			} else if (entry != NULL && name_entry != NULL) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"identifier '%S' used in ambiguous context [may be name, rule or terminal]",
						(void *) (&ZI163));
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
				alt_names(sid_current_alt), err_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (param) {
					if (types_equal(&rhs, param)) {
						item_add_param(sid_current_item, &rhs);
					} else {
						err_type_mismatch_of("parameter", "invocation", "rule",
							key, &rhs, param);
						types_destroy(&rhs);
						errored = TRUE;
					}
				} else {
					if (!types_equal_zero_tuple(&rhs)) {
						err_basic_mismatch("invocation", key, &rhs);
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
					alt_names(sid_current_alt), err_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((ZI214), result)) {
						types_add_new_names(alt_names(sid_current_alt),
							(ZI214), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
								"predicate result symbol used in result of something other than an action");
						}
						item_add_result(sid_current_item, (ZI214));
					} else {
						if (param) {
							err_type_mismatch_of("result", "invocation", "rule",
								key, (ZI214), result);
						} else {
							err_type_mismatch_of("result", "invocation", "terminal",
								key, (ZI214), result);
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
					error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
						"result names are not disjoint for invocation of rule '%K' [result = %Y]",
						(void *) key, (void *) (ZI214));
				} else {
					error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
						"result names are not disjoint for invocation of terminal '%K' [result = %Y]",
						(void *) key, (void *) (ZI214));
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
				alt_names(sid_current_alt), err_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_contains_references(&rhs)) {
					error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
						"cannot take address of identity parameters in alternative %u of production '%K' [parameter = %Y]",
						sid_alternative, (void *) entry_key(sid_external_rule), (void *) &rhs);
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
					alt_names(sid_current_alt), err_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (sid_current_item) {
						if (types_fillin_types((ZI214), item_param(sid_current_item))) {
							types_add_new_names(alt_names(sid_current_alt),
								(ZI214), grammar_get_predicate_id(sid_current_grammar));
							if (sid_saved_pred_id) {
								error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
									"predicate result symbol used in result of something other than an action");
							}
							item_add_result(sid_current_item, (ZI214));
							alt_add_item(sid_current_alt, sid_current_item);
						} else {
							error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
								"type mismatch for identity [%Y should be %Y]",
								(void *) (ZI214), (void *) item_param(sid_current_item));
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
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result names are not disjoint for identity [result = %Y]",
					(void *) (ZI214));
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
	
#line 3386 "parser.c"
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
#line 1737 "parser.act"

		if (!sid_propagating_error) {
			err_expected("tuple or ';'");
		}
	
#line 3409 "parser.c"
					}
					/* END OF ACTION: expected-tuple-or-terminator */
					/* BEGINNING OF ACTION: destroy-string */
					{
#line 1830 "parser.act"

		nstring_destroy(&(ZI163));
	
#line 3418 "parser.c"
					}
					/* END OF ACTION: destroy-string */
					/* BEGINNING OF ACTION: skip-to-end-of-item */
					{
#line 1972 "parser.act"

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
	
#line 3450 "parser.c"
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
#line 1203 "parser.act"

		if (sid_current_entry && sid_current_alt) {
			EntryT *entry = table_add_rename(grammar_table(sid_current_grammar));

			if (types_resolve((&ZI217), rule_param(sid_current_rule),
				alt_names(sid_current_alt), err_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_contains_references((&ZI217))) {
					error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
						"cannot take address of identity parameters in alternative %u of production '%K' [parameter = %Y]",
						sid_alternative, (void *) entry_key(sid_external_rule), (void *) (&ZI217));
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
					alt_names(sid_current_alt), err_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (sid_current_item) {
						if (types_fillin_types((ZI214), item_param(sid_current_item))) {
							types_add_new_names(alt_names(sid_current_alt),
							(ZI214), grammar_get_predicate_id(sid_current_grammar));
							if (sid_saved_pred_id) {
								error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
									"predicate result symbol used in result of something other than an action");
							}
							item_add_result(sid_current_item, (ZI214));
							alt_add_item(sid_current_alt, sid_current_item);
						} else {
							error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
								"type mismatch for identity [%Y should be %Y]",
								(void *) (ZI214), (void *) item_param(sid_current_item));
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
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result names are not disjoint for identity [result = %Y]",
					(void *) (ZI214));
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
	
#line 3543 "parser.c"
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
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 3563 "parser.c"
			}
			/* END OF ACTION: current-tuple */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: init-tuple */
			{
#line 367 "parser.act"

		types_init(&(ZI217));
	
#line 3573 "parser.c"
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
#line 456 "parser.act"

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
	
#line 3628 "parser.c"
					}
					/* END OF ACTION: add-ref-name */
					/* BEGINNING OF ACTION: x-identity */
					{
#line 1203 "parser.act"

		if (sid_current_entry && sid_current_alt) {
			EntryT *entry = table_add_rename(grammar_table(sid_current_grammar));

			if (types_resolve((&ZI217), rule_param(sid_current_rule),
				alt_names(sid_current_alt), err_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_contains_references((&ZI217))) {
					error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
						"cannot take address of identity parameters in alternative %u of production '%K' [parameter = %Y]",
						sid_alternative, (void *) entry_key(sid_external_rule), (void *) (&ZI217));
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
					alt_names(sid_current_alt), err_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (sid_current_item) {
						if (types_fillin_types((ZI214), item_param(sid_current_item))) {
							types_add_new_names(alt_names(sid_current_alt),
							(ZI214), grammar_get_predicate_id(sid_current_grammar));
							if (sid_saved_pred_id) {
								error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
									"predicate result symbol used in result of something other than an action");
							}
							item_add_result(sid_current_item, (ZI214));
							alt_add_item(sid_current_alt, sid_current_item);
						} else {
							error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
								"type mismatch for identity [%Y should be %Y]",
								(void *) (ZI214), (void *) item_param(sid_current_item));
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
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result names are not disjoint for identity [result = %Y]",
					(void *) (ZI214));
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
	
#line 3706 "parser.c"
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
#line 1659 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier or terminal");
		}
	
#line 3726 "parser.c"
					}
					/* END OF ACTION: expected-identifier-or-basic */
					/* BEGINNING OF ACTION: skip-to-end-of-item */
					{
#line 1972 "parser.act"

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
	
#line 3758 "parser.c"
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
#line 1743 "parser.act"

		if (!sid_propagating_error) {
			err_expected("item right hand side");
		}
	
#line 3783 "parser.c"
		}
		/* END OF ACTION: expected-item-rhs */
		/* BEGINNING OF ACTION: skip-to-end-of-item */
		{
#line 1972 "parser.act"

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
	
#line 3815 "parser.c"
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
#line 367 "parser.act"

		types_init(&(ZI214));
	
#line 3835 "parser.c"
			}
			/* END OF ACTION: init-tuple */
			/* BEGINNING OF ACTION: add-name */
			{
#line 415 "parser.act"

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
	
#line 3880 "parser.c"
			}
			/* END OF ACTION: add-name */
			/* BEGINNING OF ACTION: save-tuple */
			{
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 3889 "parser.c"
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
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 3908 "parser.c"
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
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 3980 "parser.c"
			}
			/* END OF ACTION: current-tuple */
			/* BEGINNING OF ACTION: init-tuple */
			{
#line 367 "parser.act"

		types_init(&(ZI214));
	
#line 3989 "parser.c"
			}
			/* END OF ACTION: init-tuple */
			/* BEGINNING OF ACTION: init-tuple */
			{
#line 367 "parser.act"

		types_init(&(ZI217));
	
#line 3998 "parser.c"
			}
			/* END OF ACTION: init-tuple */
			/* BEGINNING OF ACTION: x-prod-rule */
			{
#line 1281 "parser.act"

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
						err_ignored("terminal", (ZI163));
					}
				} else {
					err_unknown("identifier", (ZI163));
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
				alt_names(sid_current_alt), err_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (param) {
					if (types_equal((&ZI217), param)) {
						item_add_param(sid_current_item, (&ZI217));
					} else {
						err_type_mismatch_of("parameter", "invocation", "rule",
							key, (&ZI217), param);
						types_destroy((&ZI217));
						errored = TRUE;
					}
				} else {
					if (!types_equal_zero_tuple((&ZI217))) {
						err_basic_mismatch("invocation", key, (&ZI217));
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
					alt_names(sid_current_alt), err_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((&ZI214), result)) {
						types_add_new_names(alt_names(sid_current_alt),
							(&ZI214), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
								"predicate result symbol used in result of something other than an action");
						}
						item_add_result(sid_current_item, (&ZI214));
					} else {
						if (param) {
							err_type_mismatch_of("result", "invocation", "rule",
								key, (&ZI214), result);
						} else {
							err_type_mismatch_of("result", "invocation", "terminal",
								key, (&ZI214), result);
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
					error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
						"result names are not disjoint for invocation of rule '%K' [result = %Y]",
						(void *) key, (void *) (&ZI214));
				} else {
					error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
						"result names are not disjoint for invocation of terminal '%K' [result = %Y]",
						(void *) key, (void *) (&ZI214));
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
	
#line 4127 "parser.c"
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
#line 367 "parser.act"

		types_init(&(ZI214));
	
#line 4144 "parser.c"
			}
			/* END OF ACTION: init-tuple */
			ZR191 (sid_current_grammar, &ZI217);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: x-prod-rule */
			{
#line 1281 "parser.act"

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
						err_ignored("terminal", (ZI163));
					}
				} else {
					err_unknown("identifier", (ZI163));
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
				alt_names(sid_current_alt), err_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (param) {
					if (types_equal((&ZI217), param)) {
						item_add_param(sid_current_item, (&ZI217));
					} else {
						err_type_mismatch_of("parameter", "invocation", "rule",
							key, (&ZI217), param);
						types_destroy((&ZI217));
						errored = TRUE;
					}
				} else {
					if (!types_equal_zero_tuple((&ZI217))) {
						err_basic_mismatch("invocation", key, (&ZI217));
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
					alt_names(sid_current_alt), err_redefined_name,
					entry_key(sid_external_rule), sid_alternative)) {
					if (types_fillin_types((&ZI214), result)) {
						types_add_new_names(alt_names(sid_current_alt),
							(&ZI214), grammar_get_predicate_id(sid_current_grammar));
						if (sid_saved_pred_id) {
							error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
								"predicate result symbol used in result of something other than an action");
						}
						item_add_result(sid_current_item, (&ZI214));
					} else {
						if (param) {
							err_type_mismatch_of("result", "invocation", "rule",
								key, (&ZI214), result);
						} else {
							err_type_mismatch_of("result", "invocation", "terminal",
								key, (&ZI214), result);
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
					error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
						"result names are not disjoint for invocation of rule '%K' [result = %Y]",
						(void *) key, (void *) (&ZI214));
				} else {
					error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
						"result names are not disjoint for invocation of terminal '%K' [result = %Y]",
						(void *) key, (void *) (&ZI214));
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
	
#line 4278 "parser.c"
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
#line 2094 "parser.act"

		sid_propagating_error = FALSE;
	
#line 4318 "parser.c"
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
#line 1125 "parser.act"

		if (sid_current_item) {
			BoolT    errored = FALSE;
			EntryT  *entry   = item_entry(sid_current_item);
			ActionT *action  = entry_get_action(entry);

			if (action_get_ignored(action)) {
				err_ignored("action call", key_get_string(entry_key(entry)));
			}

			if (types_resolve((&ZI217), rule_param(sid_current_rule),
				alt_names(sid_current_alt), err_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_equal((&ZI217), action_param(action))) {
					item_add_param(sid_current_item, (&ZI217));
				} else {
					err_type_mismatch_of("parameter", "invocation", "action",
						entry_key(entry), (&ZI217), action_param(action));
					types_destroy((&ZI217));
					errored = TRUE;
				}
			} else {
				types_destroy((&ZI217));
				errored = TRUE;
			}

			if (types_disjoint_names((ZI214))) {
				if (types_check_undefined((ZI214), rule_param(sid_current_rule),
					alt_names(sid_current_alt), err_redefined_name,
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
									error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
										"predicate type mismatch [%Y should be %Y]",
										(void *) type, (void *) grammar_get_predicate_type(sid_current_grammar));
								}
							} else {
								grammar_set_predicate_type(sid_current_grammar, type);
							}
							item_to_predicate(sid_current_item);
						}
						item_add_result(sid_current_item, (ZI214));
					} else {
						err_type_mismatch_of("result", "invocation", "action",
							entry_key(entry), (ZI214), action_result(action));
						types_destroy((ZI214));
						errored = TRUE;
					}
				} else {
					types_destroy((ZI214));
					errored = TRUE;
				}
			} else {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result names are not disjoint for invocation of action '%K' [result = %Y]",
					(void *) entry_key(entry), (void *) (ZI214));
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
	
#line 4442 "parser.c"
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
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 4462 "parser.c"
			}
			/* END OF ACTION: current-tuple */
			/* BEGINNING OF ACTION: init-tuple */
			{
#line 367 "parser.act"

		types_init(&(ZI217));
	
#line 4471 "parser.c"
			}
			/* END OF ACTION: init-tuple */
			/* BEGINNING OF ACTION: x-prod-action */
			{
#line 1125 "parser.act"

		if (sid_current_item) {
			BoolT    errored = FALSE;
			EntryT  *entry   = item_entry(sid_current_item);
			ActionT *action  = entry_get_action(entry);

			if (action_get_ignored(action)) {
				err_ignored("action call", key_get_string(entry_key(entry)));
			}

			if (types_resolve((&ZI217), rule_param(sid_current_rule),
				alt_names(sid_current_alt), err_undefined_name,
				entry_key(sid_external_rule), sid_alternative)) {
				if (types_equal((&ZI217), action_param(action))) {
					item_add_param(sid_current_item, (&ZI217));
				} else {
					err_type_mismatch_of("parameter", "invocation", "action",
						entry_key(entry), (&ZI217), action_param(action));
					types_destroy((&ZI217));
					errored = TRUE;
				}
			} else {
				types_destroy((&ZI217));
				errored = TRUE;
			}

			if (types_disjoint_names((ZI214))) {
				if (types_check_undefined((ZI214), rule_param(sid_current_rule),
					alt_names(sid_current_alt), err_redefined_name,
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
									error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
										"predicate type mismatch [%Y should be %Y]",
										(void *) type, (void *) grammar_get_predicate_type(sid_current_grammar));
								}
							} else {
								grammar_set_predicate_type(sid_current_grammar, type);
							}
							item_to_predicate(sid_current_item);
						}
						item_add_result(sid_current_item, (ZI214));
					} else {
						err_type_mismatch_of("result", "invocation", "action",
							entry_key(entry), (ZI214), action_result(action));
						types_destroy((ZI214));
						errored = TRUE;
					}
				} else {
					types_destroy((ZI214));
					errored = TRUE;
				}
			} else {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result names are not disjoint for invocation of action '%K' [result = %Y]",
					(void *) entry_key(entry), (void *) (ZI214));
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
	
#line 4560 "parser.c"
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
#line 1737 "parser.act"

		if (!sid_propagating_error) {
			err_expected("tuple or ';'");
		}
	
#line 4582 "parser.c"
		}
		/* END OF ACTION: expected-tuple-or-terminator */
		/* BEGINNING OF ACTION: skip-to-end-of-item */
		{
#line 1972 "parser.act"

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
	
#line 4614 "parser.c"
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
#line 555 "parser.act"

		sid_current_scope = &sid_global_scope;
	
#line 4639 "parser.c"
					}
					/* END OF ACTION: use-global */
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: use-local */
					{
#line 559 "parser.act"

		sid_current_scope = &sid_scope_stack;
	
#line 4652 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI141, lexer_string_value(sid_current_stream));
	
#line 4707 "parser.c"
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
#line 1647 "parser.act"

		if (!sid_propagating_error) {
			err_expected("':'");
		}
	
#line 4733 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI144, lexer_string_value(sid_current_stream));
	
#line 4753 "parser.c"
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
#line 387 "parser.act"

		if (!types_add_typed_name((ZI138), grammar_table(sid_current_grammar),
			&(ZI141), (&ZI144), TRUE)) {
			err_unknown("type", (&ZI144));
		}
		nstring_destroy(&(ZI144));
	
#line 4777 "parser.c"
								}
								/* END OF ACTION: tuple-ref-name */
							}
							break;
						default:
							{
								/* BEGINNING OF ACTION: tuple-name */
								{
#line 379 "parser.act"

		if (!types_add_typed_name((ZI138), grammar_table(sid_current_grammar),
			&(ZI141), (&ZI144), FALSE)) {
			err_unknown("type", (&ZI144));
		}
		nstring_destroy(&(ZI144));
	
#line 4794 "parser.c"
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
#line 1653 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier");
		}
	
#line 4814 "parser.c"
					}
					/* END OF ACTION: expected-identifier */
					/* BEGINNING OF ACTION: destroy-string */
					{
#line 1830 "parser.act"

		nstring_destroy(&(ZI141));
	
#line 4823 "parser.c"
					}
					/* END OF ACTION: destroy-string */
					/* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
					{
#line 1836 "parser.act"

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
	
#line 4876 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI144, lexer_string_value(sid_current_stream));
	
#line 4901 "parser.c"
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
#line 403 "parser.act"

		if (!types_add_type((ZI138), grammar_table(sid_current_grammar), (&ZI144), TRUE)) {
			err_unknown("type", (&ZI144));
		}
		nstring_destroy(&(ZI144));
	
#line 4924 "parser.c"
								}
								/* END OF ACTION: tuple-ref-type */
							}
							break;
						default:
							{
								/* BEGINNING OF ACTION: tuple-type */
								{
#line 395 "parser.act"

		if (!types_add_type((ZI138), grammar_table(sid_current_grammar), (&ZI144),
			FALSE)) {
			err_unknown("type", (&ZI144));
		}
		nstring_destroy(&(ZI144));
	
#line 4941 "parser.c"
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
#line 1653 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier");
		}
	
#line 4961 "parser.c"
					}
					/* END OF ACTION: expected-identifier */
					/* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
					{
#line 1836 "parser.act"

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
	
#line 5014 "parser.c"
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
#line 1665 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier or ':'");
		}
	
#line 5039 "parser.c"
		}
		/* END OF ACTION: expected-tuple-defn */
		/* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
		{
#line 1836 "parser.act"

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
	
#line 5092 "parser.c"
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
#line 2109 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_TERMINATOR));
	
#line 5120 "parser.c"
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
#line 1677 "parser.act"

		if (!sid_propagating_error) {
			err_expected("','");
		}
	
#line 5152 "parser.c"
				}
				/* END OF ACTION: expected-separator */
				/* BEGINNING OF ACTION: skip-to-end-of-entry-list */
				{
#line 2072 "parser.act"

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
	
#line 5178 "parser.c"
				}
				/* END OF ACTION: skip-to-end-of-entry-list */
				/* BEGINNING OF ACTION: skip-recover */
				{
#line 2094 "parser.act"

		sid_propagating_error = FALSE;
	
#line 5187 "parser.c"
				}
				/* END OF ACTION: skip-recover */
				/* BEGINNING OF INLINE: 284 */
				{
					{
						/* BEGINNING OF ACTION: is-not-separator */
						{
#line 2113 "parser.act"

		(ZI0) = (CURRENT_TERMINAL != (LEXER_TOK_SEPARATOR));
	
#line 5199 "parser.c"
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
#line 1683 "parser.act"

		if (!sid_propagating_error) {
			err_expected("'('");
		}
	
#line 5253 "parser.c"
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
#line 1689 "parser.act"

		if (!sid_propagating_error) {
			err_expected("')'");
		}
	
#line 5285 "parser.c"
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
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 5312 "parser.c"
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
#line 367 "parser.act"

		types_init(&(ZI134));
	
#line 5331 "parser.c"
			}
			/* END OF ACTION: init-tuple */
			/* BEGINNING OF ACTION: init-tuple */
			{
#line 367 "parser.act"

		types_init(&(ZI135));
	
#line 5340 "parser.c"
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
#line 231 "parser.act"

		ZO134->head = ZI134.head;

		if (ZO134->head == NULL) {
			ZO134->tail = &ZO134->head;
		} else {
			ZO134->tail= ZI134.tail ;
		}
	#line 5364 "parser.c"
	}
	/* END OF RESULT ASSIGNMENT: TypeTupleT */
	/* BEGINNING OF RESULT ASSIGNMENT: TypeTupleT */
	{
#line 231 "parser.act"

		ZO135->head = ZI135.head;

		if (ZO135->head == NULL) {
			ZO135->tail = &ZO135->head;
		} else {
			ZO135->tail= ZI135.tail ;
		}
	#line 5378 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 5404 "parser.c"
						}
						/* END OF EXTRACT: IDENTIFIER */
						break;
					default:
						goto ZL3;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: current-tuple */
					{
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 5418 "parser.c"
					}
					/* END OF ACTION: current-tuple */
					/* BEGINNING OF ACTION: init-tuple */
					{
#line 367 "parser.act"

		types_init(&(ZI214));
	
#line 5427 "parser.c"
					}
					/* END OF ACTION: init-tuple */
					/* BEGINNING OF ACTION: add-var */
					{
#line 496 "parser.act"

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
			error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
				"assignment to undefined name '%S'", (void *) (&ZI163));
			types_add_name((&ZI214), grammar_table(sid_current_grammar), &(ZI163), FALSE);
		}
	
#line 5474 "parser.c"
					}
					/* END OF ACTION: add-var */
					/* BEGINNING OF ACTION: save-tuple */
					{
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 5483 "parser.c"
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
#line 1653 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier");
		}
	
#line 5504 "parser.c"
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
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 5531 "parser.c"
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
#line 1755 "parser.act"

		if (!sid_propagating_error) {
			err_expected("tuple, '=' or ';'");
		}
	
#line 5551 "parser.c"
					}
					/* END OF ACTION: expected-tuple-or-define-or-terminator */
					/* BEGINNING OF ACTION: destroy-string */
					{
#line 1830 "parser.act"

		nstring_destroy(&(ZI163));
	
#line 5560 "parser.c"
					}
					/* END OF ACTION: destroy-string */
					/* BEGINNING OF ACTION: skip-to-end-of-item */
					{
#line 1972 "parser.act"

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
	
#line 5592 "parser.c"
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
#line 376 "parser.act"

		sid_saved_pred_id = sid_current_pred_id;
	
#line 5616 "parser.c"
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
#line 372 "parser.act"

		sid_current_pred_id = FALSE;
	
#line 5635 "parser.c"
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
#line 291 "parser.act"

		(ZI172) = table_add_basic(grammar_table(sid_current_grammar), &(ZI163),
			sid_current_grammar, TRUE);
		if ((ZI172) == NULL) {
			err_redeclared("terminal", (&ZI163));
			nstring_destroy(&(ZI163));
		}
	
#line 5687 "parser.c"
					}
					/* END OF ACTION: i-terminal */
					ZR136 (sid_current_grammar, &ZI134, &ZI135);
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL3;
					}
					/* BEGINNING OF ACTION: x-terminal */
					{
#line 300 "parser.act"

		if ((ZI172)) {
			KeyT *key = entry_key((ZI172));
			BasicT *basic = entry_get_basic((ZI172));
			if (types_contains_names((&ZI134))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"parameter of declaration of terminal '%K' has names [parameter = %Y]",
					(void *) key, (void *) (&ZI134));
			}
			if (types_contains_names((&ZI135))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result of declaration of terminal '%K' has names [result = %Y]",
					(void *) key, (void *) (&ZI135));
			}
			if (types_contains_references((&ZI135))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result of declaration of terminal '%K' has references [result = %Y]",
					(void *) key, (void *) (&ZI135));
			}
			if (!types_equal_zero_tuple((&ZI134))) {
				err_basic_mismatch("declaration", key, (&ZI134));
			}
			if (!basic_get_ignored(basic)) {
				EntryT *type;

				type = types_find_ignored((&ZI134));
				if (type != NULL) {
					err_ignored("type", key_get_string(entry_key(type)));
				}

				type = types_find_ignored((&ZI135));
				if (type != NULL) {
					err_ignored("type", key_get_string(entry_key(type)));
				}
			}
			types_assign(basic_result(basic), (&ZI135));
		} else {
			types_destroy((&ZI135));
		}
		types_destroy((&ZI134));
	
#line 5739 "parser.c"
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
#line 1653 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier");
		}
	
#line 5759 "parser.c"
					}
					/* END OF ACTION: expected-identifier */
					/* BEGINNING OF ACTION: skip-to-end-of-terminal-decn */
					{
#line 1883 "parser.act"

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
	
#line 5786 "parser.c"
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
#line 282 "parser.act"

		(ZI172) = table_add_basic(grammar_table(sid_current_grammar), &(ZI163),
			sid_current_grammar, FALSE);
		if ((ZI172) == NULL) {
			err_redeclared("terminal", (&ZI163));
			nstring_destroy(&(ZI163));
		}
	
#line 5818 "parser.c"
			}
			/* END OF ACTION: terminal */
			ZR136 (sid_current_grammar, &ZI134, &ZI135);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: x-terminal */
			{
#line 300 "parser.act"

		if ((ZI172)) {
			KeyT *key = entry_key((ZI172));
			BasicT *basic = entry_get_basic((ZI172));
			if (types_contains_names((&ZI134))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"parameter of declaration of terminal '%K' has names [parameter = %Y]",
					(void *) key, (void *) (&ZI134));
			}
			if (types_contains_names((&ZI135))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result of declaration of terminal '%K' has names [result = %Y]",
					(void *) key, (void *) (&ZI135));
			}
			if (types_contains_references((&ZI135))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result of declaration of terminal '%K' has references [result = %Y]",
					(void *) key, (void *) (&ZI135));
			}
			if (!types_equal_zero_tuple((&ZI134))) {
				err_basic_mismatch("declaration", key, (&ZI134));
			}
			if (!basic_get_ignored(basic)) {
				EntryT *type;

				type = types_find_ignored((&ZI134));
				if (type != NULL) {
					err_ignored("type", key_get_string(entry_key(type)));
				}

				type = types_find_ignored((&ZI135));
				if (type != NULL) {
					err_ignored("type", key_get_string(entry_key(type)));
				}
			}
			types_assign(basic_result(basic), (&ZI135));
		} else {
			types_destroy((&ZI135));
		}
		types_destroy((&ZI134));
	
#line 5870 "parser.c"
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
#line 1671 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier or '!'");
		}
	
#line 5896 "parser.c"
		}
		/* END OF ACTION: expected-terminal-decn */
		/* BEGINNING OF ACTION: skip-to-end-of-terminal-decn */
		{
#line 1883 "parser.act"

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
	
#line 5923 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 5955 "parser.c"
						}
						/* END OF EXTRACT: IDENTIFIER */
						break;
					default:
						goto ZL3;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: action */
					{
#line 562 "parser.act"

		(ZI172) = scope_stack_add_action(sid_current_scope,
			grammar_table(sid_current_grammar), &(ZI163), sid_enclosing_rule,
			&sid_redefining_entry, FALSE);
			sid_current_entry = (ZI172);
		if (!(ZI172)) {
			err_redeclared("action", (&ZI163));
			nstring_destroy(&(ZI163));
		}
	
#line 5976 "parser.c"
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
#line 584 "parser.act"

		if ((ZI172)) {
			KeyT       *key     = entry_key(sid_current_entry);
			ActionT    *action  = entry_get_action((ZI172));
			TypeTupleT *param   = action_param(action);
			TypeTupleT *result  = action_result(action);
			BoolT       errored = FALSE;

			if (types_contains_names((&ZI134))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"parameter of declaration of action '%K' has names [parameter = %Y]",
					(void *) key, (void *) (&ZI134));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(param, (&ZI134))) {
					err_type_mismatch("parameter", "action", key, (&ZI134), param);
					errored = TRUE;
				}
			}

			if (types_contains_names((&ZI135))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result of declaration of action '%K' has names [result = %Y]",
					(void *) key, (void *) (&ZI135));
				errored = TRUE;
			}

			if (types_contains_references((&ZI135))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result of declaration of action '%K' has references [result = %Y]",
					(void *) key, (void *) (&ZI135));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(result, (&ZI135))) {
					err_type_mismatch("result", "action", key, (&ZI134), param);
					errored = TRUE;
				}
			}

			if (!action_get_ignored(action)) {
				EntryT *type;

				type = types_find_ignored((&ZI134));
				if (type != NULL) {
					err_ignored("type", key_get_string(entry_key(type)));
					errored = TRUE;
				}

				type = types_find_ignored((&ZI135));
				if (type != NULL) {
					err_ignored("type", key_get_string(entry_key(type)));
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
	
#line 6059 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 6095 "parser.c"
								}
								/* END OF EXTRACT: IDENTIFIER */
								break;
							default:
								goto ZL5;
							}
							ADVANCE_LEXER;
							/* BEGINNING OF ACTION: i-action */
							{
#line 573 "parser.act"

		(ZI172) = scope_stack_add_action(sid_current_scope,
			grammar_table(sid_current_grammar), &(ZI163), sid_enclosing_rule,
			&sid_redefining_entry, TRUE);
			sid_current_entry = (ZI172);
		if (!(ZI172)) {
			err_redeclared("action", (&ZI163));
			nstring_destroy(&(ZI163));
		}
	
#line 6116 "parser.c"
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
#line 584 "parser.act"

		if ((ZI172)) {
			KeyT       *key     = entry_key(sid_current_entry);
			ActionT    *action  = entry_get_action((ZI172));
			TypeTupleT *param   = action_param(action);
			TypeTupleT *result  = action_result(action);
			BoolT       errored = FALSE;

			if (types_contains_names((&ZI134))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"parameter of declaration of action '%K' has names [parameter = %Y]",
					(void *) key, (void *) (&ZI134));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(param, (&ZI134))) {
					err_type_mismatch("parameter", "action", key, (&ZI134), param);
					errored = TRUE;
				}
			}

			if (types_contains_names((&ZI135))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result of declaration of action '%K' has names [result = %Y]",
					(void *) key, (void *) (&ZI135));
				errored = TRUE;
			}

			if (types_contains_references((&ZI135))) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"result of declaration of action '%K' has references [result = %Y]",
					(void *) key, (void *) (&ZI135));
				errored = TRUE;
			}

			if (sid_redefining_entry) {
				if (!types_equal(result, (&ZI135))) {
					err_type_mismatch("result", "action", key, (&ZI134), param);
					errored = TRUE;
				}
			}

			if (!action_get_ignored(action)) {
				EntryT *type;

				type = types_find_ignored((&ZI134));
				if (type != NULL) {
					err_ignored("type", key_get_string(entry_key(type)));
					errored = TRUE;
				}

				type = types_find_ignored((&ZI135));
				if (type != NULL) {
					err_ignored("type", key_get_string(entry_key(type)));
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
	
#line 6199 "parser.c"
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
#line 1653 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier");
		}
	
#line 6219 "parser.c"
							}
							/* END OF ACTION: expected-identifier */
							/* BEGINNING OF ACTION: skip-to-end-of-action-decn */
							{
#line 1949 "parser.act"

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
	
#line 6247 "parser.c"
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
#line 1653 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier");
		}
	
#line 6270 "parser.c"
				}
				/* END OF ACTION: expected-identifier */
				/* BEGINNING OF ACTION: skip-to-end-of-action-decn */
				{
#line 1949 "parser.act"

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
	
#line 6298 "parser.c"
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
#line 1749 "parser.act"

		if (!sid_propagating_error) {
			err_expected("'='");
		}
	
#line 6334 "parser.c"
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
#line 1773 "parser.act"

		if (!sid_propagating_error) {
			err_expected("item");
		}
	
#line 6380 "parser.c"
		}
		/* END OF ACTION: expected-item */
		/* BEGINNING OF ACTION: skip-to-end-of-item */
		{
#line 1972 "parser.act"

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
	
#line 6412 "parser.c"
		}
		/* END OF ACTION: skip-to-end-of-item */
		/* BEGINNING OF ACTION: skip-recover */
		{
#line 2094 "parser.act"

		sid_propagating_error = FALSE;
	
#line 6421 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 6444 "parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: add-entry */
		{
#line 1618 "parser.act"

		EntryT *entry;

		entry = table_get_rule(grammar_table(sid_current_grammar), (&ZI163));
		if (entry) {
			if (entry_list_contains(grammar_entry_list(sid_current_grammar), entry)) {
				error_posn(ERR_SERIOUS, lexer_stream_name(sid_current_stream), (int) lexer_stream_line(sid_current_stream),
					"rule '%K' occurs in the entry list more than once",
					(void *) entry_key(entry));
			} else {
				entry_list_add(grammar_entry_list(sid_current_grammar), entry);
				rule_required(entry_get_rule(entry));
			}
		} else {
			err_unknown("rule", (&ZI163));
		}
		nstring_destroy(&(ZI163));
	
#line 6473 "parser.c"
		}
		/* END OF ACTION: add-entry */
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: expected-identifier */
		{
#line 1653 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier");
		}
	
#line 6488 "parser.c"
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
#line 243 "parser.act"

		nstring_assign(&ZI163, lexer_string_value(sid_current_stream));
	
#line 6511 "parser.c"
			}
			/* END OF EXTRACT: IDENTIFIER */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: prod-action */
		{
#line 1100 "parser.act"

		if (sid_current_entry && sid_current_alt) {
			EntryT *entry;

			entry = scope_stack_get_action(&sid_scope_stack,
				grammar_table(sid_current_grammar), (&ZI163));
			if (entry) {
				sid_current_item = item_create(entry);
			} else {
				err_unknown("action", (&ZI163));
				sid_current_item = NULL;
				(void) alt_deallocate(sid_current_alt);
				sid_current_alt  = NULL;
			}
		} else {
			sid_current_item = NULL;
		}
		nstring_destroy(&(ZI163));
	
#line 6541 "parser.c"
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
#line 1653 "parser.act"

		if (!sid_propagating_error) {
			err_expected("identifier");
		}
	
#line 6562 "parser.c"
		}
		/* END OF ACTION: expected-identifier */
		/* BEGINNING OF ACTION: skip-to-end-of-item */
		{
#line 1972 "parser.act"

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
	
#line 6594 "parser.c"
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
#line 1725 "parser.act"

		if (!sid_propagating_error) {
			err_expected("'>'");
		}
	
#line 6626 "parser.c"
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
#line 2103 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_CLOSE_HTUPLE)
			|| CURRENT_TERMINAL == (LEXER_TOK_EOF)
			|| sid_propagating_error);
	
#line 6656 "parser.c"
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
#line 1677 "parser.act"

		if (!sid_propagating_error) {
			err_expected("','");
		}
	
#line 6688 "parser.c"
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
#line 1767 "parser.act"

		if (!sid_propagating_error) {
			err_expected("'}'");
		}
	
#line 6732 "parser.c"
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
#line 1701 "parser.act"

		if (!sid_propagating_error) {
			err_expected("';'");
		}
	
#line 6764 "parser.c"
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
#line 2103 "parser.act"

		(ZI0) = (CURRENT_TERMINAL == (LEXER_TOK_CLOSE_HTUPLE)
			|| CURRENT_TERMINAL == (LEXER_TOK_EOF)
			|| sid_propagating_error);
	
#line 6794 "parser.c"
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
#line 1677 "parser.act"

		if (!sid_propagating_error) {
			err_expected("','");
		}
	
#line 6826 "parser.c"
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

#line 2118 "parser.act"


#line 6849 "parser.c"

/* END OF FILE */
