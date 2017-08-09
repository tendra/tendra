/*
 * Automatically generated from the files:
 *	c-parser.sid
 * and
 *	c-parser.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 55 "c-parser.act"


	/* $Id$ */

	/*
	 * Copyright 2008-2011, The TenDRA Project.
	 * Copyright 1997, United Kingdom Secretary of State for Defence.
	 *
	 * See doc/copyright/ for the full copyright terms.
	 */

	#include <assert.h>

	#include <shared/bool.h>
	#include <shared/check.h>
	#include <shared/error.h>

	#include "../adt/action.h"
	#include "../adt/basic.h"
	#include "../adt/entry.h"
	#include "../adt/type.h"
	#include "../adt/types.h"

	#include "c-parser.h"
	#include "c-code.h"
	#include "c-out-info.h"

	#define ERROR_TERMINAL (C_TOK_ERROR)
	#define CURRENT_TERMINAL c_lexer_get_terminal (c_current_stream)
	#define ADVANCE_LEXER c_lexer_next_token (c_current_stream)
	#define SAVE_LEXER(x) (c_lexer_save_terminal (c_current_stream, (CTokenT) (x)))
	#define RESTORE_LEXER (c_lexer_restore_terminal (c_current_stream))

	/* typedefs for the maps section */
	typedef CCodeT *CCodeP;

	static NStringT    c_prefix_names [CPFX_NUM_PREFIXES];
	static bool       c_inited_prefix_names = false;
	static CPrefixT    c_current_prefix;
	static EntryT     *c_current_entry;
	static TypeTupleT  c_saved_type;
	static TypeTupleT  c_current_type;
	static bool       c_propagating_error = false;

	CLexerStreamT *c_current_stream;
	COutputInfoT  *c_current_out_info;
	TableT        *c_current_table;


	static void err_expected(const char *item) {
		error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
			"expected %s", item);
	}

	static void err_unknown(const char *item, NStringT *name) {
		error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
			"unknown %s '%S'", item, (void *) name);
	}

	static void err_mult(const char *verb, const char *item, NStringT *name) {
		error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
			"multiple %s operations defined for %s '%S'", verb, item, (void *) name);
	}

	static void err_formal_clash(const char *verb, const char *item, KeyT *key, TypeTupleT *a, TypeTupleT *b) {
		error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
			"%s operation formal clash for %s '%K' [parameter = %Y, result = %Y]",
			verb, item, (void *) key, (void *) a, (void *) b);

	}

	static void err_clash(const char *verb, const char *field, const char *item, KeyT *key, TypeTupleT *a) {
		error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
			"%s operation %s clash (or missing name) for %s '%K' [%s = %Y]",
			verb, field, item, (void *) key, field, (void *) a);
	}

	static void err_field_clash(const char *field, const char *item, KeyT *key, TypeTupleT *a) {
		error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
			"%s clash (or missing name) for %s '%K' [%s = %Y]",
			field, item, (void *) key, field, (void *) a);
	}

	static void err_mismatch(const char *field, const char *verb, const char *item, KeyT *key, TypeTupleT *a, TypeTupleT *b) {
		error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
			"%s type mismatch for %s operation on %s '%K' [%Y should be %Y]",
			field, verb, item, (void *) key, (void *) a, (void *) b);
	}

	static void err_field_mismatch(const char *field, KeyT *key, TypeTupleT *a, TypeTupleT *b) {
		error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
			"%s type mismatch for action '%K' [%Y should be %Y]",
			field, (void *) key, (void *) a, (void *) b);
	}

#line 109 "c-parser.c"


#ifndef ERROR_TERMINAL
#error "-s no-numeric-terminals given and ERROR_TERMINAL is not defined"
#endif

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZR139(void);
static void ZR179(void);
static void ZR119(CCodeP);
static void ZR186(void);
static void ZR113(CCodeP *);
static void ZR132(void);
static void ZR163(void);
static void ZR166(void);
static void ZR195(void);
static void ZR154(void);
static void ZR193(void);
static void ZR174(void);
static void ZR122(void);
static void ZR115(CCodeP);
static void ZR124(void);
extern void c_parse_grammar(void);
static void ZR157(void);
static void ZR159(void);
static void ZR141(void);
static void ZR181(void);
static void ZR220(void);
static void ZR149(void);
static void ZR223(void);
static void ZR188(void);
static void ZR130(void);
static void ZR147(void);
static void ZR164(void);
static void ZR172(void);
static void ZR126(void);

/* BEGINNING OF STATIC VARIABLES */

static bool ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZR139(void)
{
ZL2_139:;
	switch (CURRENT_TERMINAL) {
	case (C_TOK_C_HIDENTIFIER):
		{
			ZR141 ();
			/* BEGINNING OF INLINE: c-parse-grammar::persistent-list */
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_139;
			}
			/* END OF INLINE: c-parse-grammar::persistent-list */
		}
		UNREACHED;
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
ZR179(void)
{
ZL2_179:;
	switch (CURRENT_TERMINAL) {
	case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
		{
			ZR181 ();
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: skip-recover */
			{
#line 1110 "c-parser.act"

		c_propagating_error = false;
	
#line 201 "c-parser.c"
			}
			/* END OF ACTION: skip-recover */
			/* BEGINNING OF INLINE: c-parse-grammar::result-assign-list */
			goto ZL2_179;
			/* END OF INLINE: c-parse-grammar::result-assign-list */
		}
		UNREACHED;
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
ZR119(CCodeP ZI112)
{
ZL2_119:;
	switch (CURRENT_TERMINAL) {
	case (C_TOK_ACT_HAT): case (C_TOK_ACT_HEXCEPTION): case (C_TOK_ACT_HTERMINAL): case (C_TOK_ACT_HADVANCE):
	case (C_TOK_ACT_HBASIC): case (C_TOK_ACT_HLABEL): case (C_TOK_ACT_HREFERENCE): case (C_TOK_ACT_HIDENTIFIER):
	case (C_TOK_ACT_HMODIFIABLE): case (C_TOK_ACT_HCODESTRING): case (C_TOK_ACT_HEOF):
		{
			ZR115 (ZI112);
			/* BEGINNING OF INLINE: c-parse-grammar::code-block::code-body */
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_119;
			}
			/* END OF INLINE: c-parse-grammar::code-block::code-body */
		}
		UNREACHED;
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
ZR186(void)
{
ZL2_186:;
	switch (CURRENT_TERMINAL) {
	case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
		{
			ZR188 ();
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: skip-recover */
			{
#line 1110 "c-parser.act"

		c_propagating_error = false;
	
#line 269 "c-parser.c"
			}
			/* END OF ACTION: skip-recover */
			/* BEGINNING OF INLINE: c-parse-grammar::terminal-list */
			goto ZL2_186;
			/* END OF INLINE: c-parse-grammar::terminal-list */
		}
		UNREACHED;
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
ZR113(CCodeP *ZO112)
{
	CCodeP ZI112;

	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		unsigned ZI121;

		switch (CURRENT_TERMINAL) {
		case (C_TOK_ACT_HCODESTART):
			/* BEGINNING OF EXTRACT: ACT-CODESTART */
			{
#line 209 "c-parser.act"

		ZI121 = c_lexer_stream_line(c_current_stream);
	
#line 307 "c-parser.c"
			}
			/* END OF EXTRACT: ACT-CODESTART */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: ccode-init */
		{
#line 741 "c-parser.act"

		(ZI112) = c_code_create(istream_name(&c_lexer_stream->istream), (ZI121));
	
#line 321 "c-parser.c"
		}
		/* END OF ACTION: ccode-init */
		ZR119 (ZI112);
		switch (CURRENT_TERMINAL) {
		case (C_TOK_ACT_HCODEEND):
			break;
		case (ERROR_TERMINAL):
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
ZL0:;
	*ZO112 = ZI112;
}

static void
ZR132(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		NStringT ZI134;

		/* BEGINNING OF INLINE: c-parse-grammar::identifier */
		{
			switch (CURRENT_TERMINAL) {
			case (C_TOK_C_HIDENTIFIER):
				{
					/* BEGINNING OF EXTRACT: C-IDENTIFIER */
					{
#line 173 "c-parser.act"

		nstring_assign(&ZI134, c_lexer_string_value(c_current_stream));
	
#line 364 "c-parser.c"
					}
					/* END OF EXTRACT: C-IDENTIFIER */
					ADVANCE_LEXER;
				}
				break;
			case (C_TOK_SID_HIDENTIFIER):
				{
					/* BEGINNING OF EXTRACT: SID-IDENTIFIER */
					{
#line 177 "c-parser.act"

		nstring_assign(&ZI134, c_lexer_string_value(c_current_stream));
	
#line 378 "c-parser.c"
					}
					/* END OF EXTRACT: SID-IDENTIFIER */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: c-parse-grammar::identifier */
		/* BEGINNING OF ACTION: set-map */
		{
#line 279 "c-parser.act"

		c_current_entry = table_get_entry(c_current_table, (&ZI134));
		if (c_current_entry == NULL) {
			err_unknown("identifier", (&ZI134));
		} else if (entry_get_mapping(c_current_entry)) {
			error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
				"attempt to remap identifier '%S'", (void *) (&ZI134));
			c_current_entry = NULL;
		} else {
			switch (entry_type(c_current_entry)) EXHAUSTIVE {
			case ET_NAME:
			case ET_ACTION:
			case ET_NON_LOCAL:
				error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
					"cannot map identifier '%S' [it must be a rule, a basic or a type]", (void *) (&ZI134));
				c_current_entry = NULL;
				break;
			case ET_RENAME:
			case ET_PREDICATE:
				UNREACHED;
				break;
			case ET_TYPE:
			case ET_RULE:
			case ET_BASIC:
				break;
			}
		}
		nstring_destroy(&(ZI134));
	
#line 421 "c-parser.c"
		}
		/* END OF ACTION: set-map */
		ZR163 ();
		/* BEGINNING OF INLINE: 136 */
		{
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				NStringT ZI137;

				switch (CURRENT_TERMINAL) {
				case (C_TOK_C_HIDENTIFIER):
					/* BEGINNING OF EXTRACT: C-IDENTIFIER */
					{
#line 173 "c-parser.act"

		nstring_assign(&ZI137, c_lexer_string_value(c_current_stream));
	
#line 442 "c-parser.c"
					}
					/* END OF EXTRACT: C-IDENTIFIER */
					break;
				default:
					goto ZL4;
				}
				ADVANCE_LEXER;
				/* BEGINNING OF ACTION: x-set-map */
				{
#line 310 "c-parser.act"

		if (c_current_entry) {
			entry_set_mapping(c_current_entry, &(ZI137));
		} else {
			nstring_destroy(&(ZI137));
		}
	
#line 460 "c-parser.c"
				}
				/* END OF ACTION: x-set-map */
				ZR223 ();
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL4;
				}
			}
			goto ZL3;
		ZL4:;
			{
				/* BEGINNING OF ACTION: expected-c-identifier */
				{
#line 811 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("C identifier");
		}
	
#line 480 "c-parser.c"
				}
				/* END OF ACTION: expected-c-identifier */
				/* BEGINNING OF ACTION: skip-to-end-of-map */
				{
#line 954 "c-parser.act"

		while (CURRENT_TERMINAL != (C_TOK_EOF)
			&& CURRENT_TERMINAL != (C_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HASSIGNMENTS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HPARAM_HASSIGN)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HRESULT_HASSIGN)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTERMINALS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HACTIONS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTRAILER)) {
			if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == (C_TOK_CODE)) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != (C_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		c_propagating_error = true;
	
#line 513 "c-parser.c"
				}
				/* END OF ACTION: skip-to-end-of-map */
			}
		ZL3:;
		}
		/* END OF INLINE: 136 */
	}
	return;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
}

static void
ZR163(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case (C_TOK_ARROW):
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
#line 835 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("'->'");
		}
	
#line 553 "c-parser.c"
		}
		/* END OF ACTION: expected-arrow */
	}
}

static void
ZR166(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		NStringT ZI109;

		/* BEGINNING OF INLINE: c-parse-grammar::identifier */
		{
			switch (CURRENT_TERMINAL) {
			case (C_TOK_C_HIDENTIFIER):
				{
					/* BEGINNING OF EXTRACT: C-IDENTIFIER */
					{
#line 173 "c-parser.act"

		nstring_assign(&ZI109, c_lexer_string_value(c_current_stream));
	
#line 579 "c-parser.c"
					}
					/* END OF EXTRACT: C-IDENTIFIER */
					ADVANCE_LEXER;
				}
				break;
			case (C_TOK_SID_HIDENTIFIER):
				{
					/* BEGINNING OF EXTRACT: SID-IDENTIFIER */
					{
#line 177 "c-parser.act"

		nstring_assign(&ZI109, c_lexer_string_value(c_current_stream));
	
#line 593 "c-parser.c"
					}
					/* END OF EXTRACT: SID-IDENTIFIER */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: c-parse-grammar::identifier */
		/* BEGINNING OF ACTION: assign */
		{
#line 377 "c-parser.act"

		c_current_entry = table_get_type(c_current_table, (&ZI109));
		if (c_current_entry == NULL) {
			error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
				"assignment operation defined for unknown type '%S'", (void *) (&ZI109));
		} else if (type_get_assign_code(entry_get_type(c_current_entry))) {
			err_mult("assignment", "type", (&ZI109));
			c_current_entry = NULL;
		}
		nstring_destroy(&(ZI109));
	
#line 618 "c-parser.c"
		}
		/* END OF ACTION: assign */
		ZR147 ();
		ZR126 ();
		/* BEGINNING OF INLINE: 169 */
		{
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				CCodeP ZI170;

				ZR113 (&ZI170);
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL4;
				}
				/* BEGINNING OF ACTION: x-assign */
				{
#line 426 "c-parser.act"

		if (c_current_entry) {
			bool  errored = false;
			KeyT  *key     = entry_key (c_current_entry);
			TypeTupleT tmp;

			types_init(&tmp);
			types_add_type_entry(&tmp, c_current_entry, false);

			if (!types_disjoint_names(&c_saved_type)) {
				err_clash("assignment", "parameter", "type", key, &c_saved_type);
				errored = true;
			}

			if (!types_fillin_types (&c_saved_type, &tmp)) {
				err_mismatch("parameter", "assignment", "type", key, &tmp, &c_saved_type);
				errored = true;
			}

			if (!types_disjoint_names (&c_current_type)) {
				err_clash("assignment", "result", "type", key, &c_saved_type);
				errored = true;
			}

			if (!types_fillin_types (&c_current_type, &tmp)) {
				err_mismatch("result", "assignment", "type", key, &tmp, &c_saved_type);
				errored = true;
			}

			if (types_intersect (&c_saved_type, &c_current_type)) {
				err_formal_clash("assignment", "type", key, &c_saved_type, &c_current_type);
				errored = true;
			}

			types_destroy(&tmp);
			if (errored) {
				types_destroy(&c_saved_type);
				types_destroy(&c_current_type);
				c_code_deallocate((ZI170));
				c_current_entry = NULL;
			} else {
			TypeT *type;

				type = entry_get_type (c_current_entry);
				c_code_check((ZI170), false, false, false, &c_saved_type, &c_current_type, c_current_table);
				type_set_assign_code(type,  (ZI170));
			}
		} else {
			types_destroy(&c_saved_type);
			types_destroy(&c_current_type);
			c_code_deallocate((ZI170));
		}
	
#line 693 "c-parser.c"
				}
				/* END OF ACTION: x-assign */
				ZR223 ();
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL4;
				}
			}
			goto ZL3;
		ZL4:;
			{
				/* BEGINNING OF ACTION: expected-code */
				{
#line 859 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("code block");
		}
	
#line 713 "c-parser.c"
				}
				/* END OF ACTION: expected-code */
				/* BEGINNING OF ACTION: skip-to-end-of-assignment */
				{
#line 982 "c-parser.act"

		while (CURRENT_TERMINAL != (C_TOK_EOF)
			&& CURRENT_TERMINAL != (C_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HPARAM_HASSIGN)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HRESULT_HASSIGN)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTERMINALS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HACTIONS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTRAILER)) {
			if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == (C_TOK_CODE)) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != (C_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		c_propagating_error = true;
	
#line 745 "c-parser.c"
				}
				/* END OF ACTION: skip-to-end-of-assignment */
			}
		ZL3:;
		}
		/* END OF INLINE: 169 */
	}
	return;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
}

static void
ZR195(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case (C_TOK_BEGIN_HACTION):
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 197 */
		{
			{
				NStringT ZI109;

				/* BEGINNING OF INLINE: c-parse-grammar::identifier */
				{
					switch (CURRENT_TERMINAL) {
					case (C_TOK_C_HIDENTIFIER):
						{
							/* BEGINNING OF EXTRACT: C-IDENTIFIER */
							{
#line 173 "c-parser.act"

		nstring_assign(&ZI109, c_lexer_string_value(c_current_stream));
	
#line 789 "c-parser.c"
							}
							/* END OF EXTRACT: C-IDENTIFIER */
							ADVANCE_LEXER;
						}
						break;
					case (C_TOK_SID_HIDENTIFIER):
						{
							/* BEGINNING OF EXTRACT: SID-IDENTIFIER */
							{
#line 177 "c-parser.act"

		nstring_assign(&ZI109, c_lexer_string_value(c_current_stream));
	
#line 803 "c-parser.c"
							}
							/* END OF EXTRACT: SID-IDENTIFIER */
							ADVANCE_LEXER;
						}
						break;
					default:
						goto ZL3;
					}
				}
				/* END OF INLINE: c-parse-grammar::identifier */
				/* BEGINNING OF ACTION: set-action */
				{
#line 656 "c-parser.act"

		c_current_entry = table_get_action(c_current_table, (&ZI109));
		if (c_current_entry == NULL) {
			error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
				"definition for unknown action '%S'", (void *) (&ZI109));
		} else {
			ActionT *action;

			action = entry_get_action(c_current_entry);
			if (action_get_code(action)) {
				error_posn(ERR_SERIOUS, istream_name(&c_lexer_stream->istream), (int) istream_line(&c_lexer_stream->istream),
					"multiple definitions for action '%S'", (void *) (&ZI109));
				c_current_entry = NULL;
			}
		}
		nstring_destroy(&(ZI109));
	
#line 834 "c-parser.c"
				}
				/* END OF ACTION: set-action */
				/* BEGINNING OF INLINE: 198 */
				{
					{
						switch (CURRENT_TERMINAL) {
						case (C_TOK_END_HACTION):
							break;
						default:
							goto ZL6;
						}
						ADVANCE_LEXER;
					}
					goto ZL5;
				ZL6:;
					{
						/* BEGINNING OF ACTION: expected-end-action */
						{
#line 847 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("'>'");
		}
	
#line 859 "c-parser.c"
						}
						/* END OF ACTION: expected-end-action */
					}
				ZL5:;
				}
				/* END OF INLINE: 198 */
				ZR147 ();
				ZR126 ();
				/* BEGINNING OF INLINE: 200 */
				{
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL3;
					}
					{
						CCodeP ZI170;

						ZR113 (&ZI170);
						if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
							RESTORE_LEXER;
							goto ZL8;
						}
						/* BEGINNING OF ACTION: x-set-action */
						{
#line 711 "c-parser.act"

		if (c_current_entry) {
			ActionT    *action  = entry_get_action(c_current_entry);
			TypeTupleT *param   = action_param(action);
			TypeTupleT *result  = action_result(action);
			bool       errored = false;
			KeyT       *key     = entry_key(c_current_entry);

			if (!types_disjoint_names(&c_saved_type)) {
				err_field_clash("parameter", "action", key, &c_saved_type);
				errored = true;
			}

			if (!types_fillin_types(&c_saved_type, param)) {
				err_field_mismatch("parameter", key, &c_saved_type, param);
				errored = true;
			}

			if (!types_disjoint_names(&c_current_type)) {
				err_field_clash("result", "action", key, &c_current_type);
				errored = true;
			}

			if (!types_fillin_types(&c_current_type, result)) {
				err_field_mismatch("result", key, &c_saved_type, result);
				errored = true;
			}

			if (types_intersect(&c_saved_type, &c_current_type)) {
				error_posn(ERR_SERIOUS, istream_name(&c_lexer_stream->istream), (int) istream_line(&c_lexer_stream->istream),
					"formal clash for action '%K' [parameter = %Y, result = %Y]",
					(void *) key, (void *) &c_saved_type, (void *) &c_current_type);
				errored = true;
			}

			if (errored) {
				types_destroy(&c_saved_type);
				types_destroy(&c_current_type);
				c_code_deallocate((ZI170));
				c_current_entry = NULL;
			} else {
				c_code_check((ZI170), true, true, false, &c_saved_type, &c_current_type, c_current_table);
				types_propogate_mutations(param, &c_saved_type);
				action_set_code(action,  (ZI170));
			}
		} else {
			types_destroy(&c_saved_type);
			types_destroy(&c_current_type);
			c_code_deallocate((ZI170));
		}
	
#line 936 "c-parser.c"
						}
						/* END OF ACTION: x-set-action */
						ZR223 ();
						if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
							RESTORE_LEXER;
							goto ZL8;
						}
					}
					goto ZL7;
				ZL8:;
					{
						/* BEGINNING OF ACTION: expected-code */
						{
#line 859 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("code block");
		}
	
#line 956 "c-parser.c"
						}
						/* END OF ACTION: expected-code */
						/* BEGINNING OF ACTION: skip-to-end-of-action */
						{
#line 1085 "c-parser.act"

		while (CURRENT_TERMINAL != (C_TOK_EOF)
			&& CURRENT_TERMINAL != (C_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTRAILER)) {
			if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER)
			|| CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == (C_TOK_CODE)) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != (C_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		c_propagating_error = true;
	
#line 985 "c-parser.c"
						}
						/* END OF ACTION: skip-to-end-of-action */
					}
				ZL7:;
				}
				/* END OF INLINE: 200 */
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: expected-identifier */
				{
#line 805 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("identifier");
		}
	
#line 1004 "c-parser.c"
				}
				/* END OF ACTION: expected-identifier */
				/* BEGINNING OF ACTION: skip-to-end-of-action */
				{
#line 1085 "c-parser.act"

		while (CURRENT_TERMINAL != (C_TOK_EOF)
			&& CURRENT_TERMINAL != (C_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTRAILER)) {
			if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER)
			|| CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == (C_TOK_CODE)) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != (C_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		c_propagating_error = true;
	
#line 1033 "c-parser.c"
				}
				/* END OF ACTION: skip-to-end-of-action */
			}
		ZL2:;
		}
		/* END OF INLINE: 197 */
	}
	return;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
}

static void
ZR154(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
ZL2_154:;
	{
		ZR149 ();
		/* BEGINNING OF INLINE: 156 */
		{
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				/* BEGINNING OF ACTION: is-close-tuple-or-skipped-or-eof */
				{
#line 1113 "c-parser.act"

		(ZI0) = (CURRENT_TERMINAL == (C_TOK_CLOSE_HTUPLE)
			|| CURRENT_TERMINAL == (C_TOK_EOF)
			|| c_propagating_error);
	
#line 1071 "c-parser.c"
				}
				/* END OF ACTION: is-close-tuple-or-skipped-or-eof */
				if (!ZI0)
					goto ZL5;
				goto ZL3;
			}
			UNREACHED;
		ZL5:;
			switch (CURRENT_TERMINAL) {
			case (C_TOK_SEPARATOR):
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: c-parse-grammar::function-type-defn::tuple-defn-list-1 */
					goto ZL2_154;
					/* END OF INLINE: c-parse-grammar::function-type-defn::tuple-defn-list-1 */
				}
				UNREACHED;
			default:
				goto ZL4;
			}
			UNREACHED;
		ZL4:;
			{
				/* BEGINNING OF ACTION: expected-separator */
				{
#line 817 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("','");
		}
	
#line 1103 "c-parser.c"
				}
				/* END OF ACTION: expected-separator */
				/* BEGINNING OF INLINE: c-parse-grammar::function-type-defn::tuple-defn-list-1 */
				goto ZL2_154;
				/* END OF INLINE: c-parse-grammar::function-type-defn::tuple-defn-list-1 */
			}
			UNREACHED;
		ZL3:;
		}
		/* END OF INLINE: 156 */
	}
	return;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
}

static void
ZR193(void)
{
ZL2_193:;
	switch (CURRENT_TERMINAL) {
	case (C_TOK_BEGIN_HACTION):
		{
			ZR195 ();
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: skip-recover */
			{
#line 1110 "c-parser.act"

		c_propagating_error = false;
	
#line 1139 "c-parser.c"
			}
			/* END OF ACTION: skip-recover */
			/* BEGINNING OF INLINE: c-parse-grammar::action-list */
			goto ZL2_193;
			/* END OF INLINE: c-parse-grammar::action-list */
		}
		UNREACHED;
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
ZR174(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		NStringT ZI109;

		/* BEGINNING OF INLINE: c-parse-grammar::identifier */
		{
			switch (CURRENT_TERMINAL) {
			case (C_TOK_C_HIDENTIFIER):
				{
					/* BEGINNING OF EXTRACT: C-IDENTIFIER */
					{
#line 173 "c-parser.act"

		nstring_assign(&ZI109, c_lexer_string_value(c_current_stream));
	
#line 1178 "c-parser.c"
					}
					/* END OF EXTRACT: C-IDENTIFIER */
					ADVANCE_LEXER;
				}
				break;
			case (C_TOK_SID_HIDENTIFIER):
				{
					/* BEGINNING OF EXTRACT: SID-IDENTIFIER */
					{
#line 177 "c-parser.act"

		nstring_assign(&ZI109, c_lexer_string_value(c_current_stream));
	
#line 1192 "c-parser.c"
					}
					/* END OF EXTRACT: SID-IDENTIFIER */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: c-parse-grammar::identifier */
		/* BEGINNING OF ACTION: passign */
		{
#line 443 "c-parser.act"

		c_current_entry = table_get_type(c_current_table, (&ZI109));
		if (c_current_entry == NULL) {
			error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
				"parameter assignment operation defined for unknown type '%S'", (void *) (&ZI109));
		} else if (type_get_param_assign_code(entry_get_type(c_current_entry))) {
			err_mult("parameter assignment", "type", (&ZI109));
			c_current_entry = NULL;
		}
		nstring_destroy(&(ZI109));
	
#line 1217 "c-parser.c"
		}
		/* END OF ACTION: passign */
		ZR147 ();
		ZR126 ();
		/* BEGINNING OF INLINE: 177 */
		{
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				CCodeP ZI170;

				ZR113 (&ZI170);
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL4;
				}
				/* BEGINNING OF ACTION: x-passign */
				{
#line 491 "c-parser.act"

		if (c_current_entry) {
			bool  errored = false;
			KeyT  *key     = entry_key(c_current_entry);
			TypeTupleT tmp;

			types_init(&tmp);
			types_add_type_entry(&tmp, c_current_entry, false);
			if (!types_disjoint_names(&c_saved_type)) {
				err_clash("parameter assignment", "parameter", "type", key, &c_saved_type);
				errored = true;
			}

			if (!types_fillin_types(&c_saved_type, &tmp)) {
				err_mismatch("parameter", "parameter assignment", "type", key, &c_saved_type, &tmp);
				errored = true;
			}

			if (!types_disjoint_names(&c_current_type)) {
				err_clash("parameter assignment", "result", "type", key, &c_saved_type);
				errored = true;
			}

			if (!types_fillin_types(&c_current_type, &tmp)) {
				err_mismatch("result type", "parameter assignment", "type", key, &c_saved_type, &tmp);
				errored = true;
			}

			if (types_intersect(&c_saved_type, &c_current_type)) {
				err_formal_clash("parameter assignment", "type", key, &c_saved_type, &c_current_type);
				errored = true;
			}

			types_destroy(&tmp);
			if (errored) {
				types_destroy(&c_saved_type);
				types_destroy(&c_current_type);
				c_code_deallocate((ZI170));
				c_current_entry = NULL;
			} else {
				TypeT *type = entry_get_type(c_current_entry);

				c_code_check((ZI170), false, false, false, &c_saved_type,
					&c_current_type, c_current_table);
				type_set_param_assign_code(type,  (ZI170));
			}
		} else {
			types_destroy(&c_saved_type);
			types_destroy(&c_current_type);
			c_code_deallocate((ZI170));
		}
	
#line 1291 "c-parser.c"
				}
				/* END OF ACTION: x-passign */
				ZR223 ();
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL4;
				}
			}
			goto ZL3;
		ZL4:;
			{
				/* BEGINNING OF ACTION: expected-code */
				{
#line 859 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("code block");
		}
	
#line 1311 "c-parser.c"
				}
				/* END OF ACTION: expected-code */
				/* BEGINNING OF ACTION: skip-to-end-of-param-assign */
				{
#line 1009 "c-parser.act"

		while (CURRENT_TERMINAL != (C_TOK_EOF)
			&& CURRENT_TERMINAL != (C_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HRESULT_HASSIGN)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTERMINALS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HACTIONS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTRAILER)) {
			if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER)
				|| CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == (C_TOK_CODE)) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != (C_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		c_propagating_error = true;
	
#line 1343 "c-parser.c"
				}
				/* END OF ACTION: skip-to-end-of-param-assign */
			}
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
ZR122(void)
{
ZL2_122:;
	switch (CURRENT_TERMINAL) {
	case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
		{
			ZR124 ();
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: skip-recover */
			{
#line 1110 "c-parser.act"

		c_propagating_error = false;
	
#line 1375 "c-parser.c"
			}
			/* END OF ACTION: skip-recover */
			/* BEGINNING OF INLINE: c-parse-grammar::prefix-list */
			goto ZL2_122;
			/* END OF INLINE: c-parse-grammar::prefix-list */
		}
		UNREACHED;
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
ZR115(CCodeP ZI112)
{
	switch (CURRENT_TERMINAL) {
	case (C_TOK_ACT_HADVANCE):
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-ccode-advance */
			{
#line 759 "c-parser.act"

		c_code_append_advance((ZI112));
	
#line 1407 "c-parser.c"
			}
			/* END OF ACTION: append-ccode-advance */
		}
		break;
	case (C_TOK_ACT_HAT):
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-ccode-at */
			{
#line 746 "c-parser.act"

		NStringT ns;
		nstring_copy_cstring(&ns, "@");	/* TODO append '@' to code buffer? */
		c_code_append_string((ZI112), &ns);	/* TODO really append_label()? */
	
#line 1423 "c-parser.c"
			}
			/* END OF ACTION: append-ccode-at */
		}
		break;
	case (C_TOK_ACT_HBASIC):
		{
			NStringT ZI117;

			/* BEGINNING OF EXTRACT: ACT-BASIC */
			{
#line 185 "c-parser.act"

		nstring_assign(&ZI117, c_lexer_string_value(c_current_stream));
	
#line 1438 "c-parser.c"
			}
			/* END OF EXTRACT: ACT-BASIC */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-ccode-basic */
			{
#line 763 "c-parser.act"

		c_code_append_basic((ZI112), &(ZI117));
	
#line 1448 "c-parser.c"
			}
			/* END OF ACTION: append-ccode-basic */
		}
		break;
	case (C_TOK_ACT_HCODESTRING):
		{
			NStringT ZI118;

			/* BEGINNING OF EXTRACT: ACT-CODESTRING */
			{
#line 205 "c-parser.act"

		nstring_assign(&ZI118, c_lexer_string_value(c_current_stream));
	
#line 1463 "c-parser.c"
			}
			/* END OF EXTRACT: ACT-CODESTRING */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-ccode-codestring */
			{
#line 783 "c-parser.act"

		assert(!nstring_contains(&(ZI118), '@'));	/* XXX '@'? */
		c_code_append_string((ZI112), &(ZI118));
	
#line 1474 "c-parser.c"
			}
			/* END OF ACTION: append-ccode-codestring */
		}
		break;
	case (C_TOK_ACT_HEOF):
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: E-eof-in-code-block */
			{
#line 790 "c-parser.act"

		error_posn(ERR_SERIOUS, istream_name(&c_lexer_stream->istream), (int) istream_line(&c_lexer_stream->istream),
			"end of file in C code block");
	
#line 1489 "c-parser.c"
			}
			/* END OF ACTION: E-eof-in-code-block */
		}
		break;
	case (C_TOK_ACT_HEXCEPTION):
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-ccode-exception */
			{
#line 751 "c-parser.act"

		c_code_append_exception((ZI112));
	
#line 1503 "c-parser.c"
			}
			/* END OF ACTION: append-ccode-exception */
		}
		break;
	case (C_TOK_ACT_HIDENTIFIER):
		{
			NStringT ZI117;

			/* BEGINNING OF EXTRACT: ACT-IDENTIFIER */
			{
#line 197 "c-parser.act"

		nstring_assign(&ZI117, c_lexer_string_value(c_current_stream));
	
#line 1518 "c-parser.c"
			}
			/* END OF EXTRACT: ACT-IDENTIFIER */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-ccode-identifier */
			{
#line 775 "c-parser.act"

		c_code_append_identifier((ZI112), &(ZI117));
	
#line 1528 "c-parser.c"
			}
			/* END OF ACTION: append-ccode-identifier */
		}
		break;
	case (C_TOK_ACT_HLABEL):
		{
			NStringT ZI117;

			/* BEGINNING OF EXTRACT: ACT-LABEL */
			{
#line 189 "c-parser.act"

		nstring_assign(&ZI117, c_lexer_string_value(c_current_stream));
	
#line 1543 "c-parser.c"
			}
			/* END OF EXTRACT: ACT-LABEL */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-ccode-label */
			{
#line 767 "c-parser.act"

		c_code_append_label((ZI112), &(ZI117));
	
#line 1553 "c-parser.c"
			}
			/* END OF ACTION: append-ccode-label */
		}
		break;
	case (C_TOK_ACT_HMODIFIABLE):
		{
			NStringT ZI117;

			/* BEGINNING OF EXTRACT: ACT-MODIFIABLE */
			{
#line 201 "c-parser.act"

		nstring_assign(&ZI117, c_lexer_string_value(c_current_stream));
	
#line 1568 "c-parser.c"
			}
			/* END OF EXTRACT: ACT-MODIFIABLE */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-ccode-modifiable */
			{
#line 779 "c-parser.act"

		c_code_append_modifiable((ZI112), &(ZI117));
	
#line 1578 "c-parser.c"
			}
			/* END OF ACTION: append-ccode-modifiable */
		}
		break;
	case (C_TOK_ACT_HREFERENCE):
		{
			NStringT ZI117;

			/* BEGINNING OF EXTRACT: ACT-REFERENCE */
			{
#line 193 "c-parser.act"

		nstring_assign(&ZI117, c_lexer_string_value(c_current_stream));
	
#line 1593 "c-parser.c"
			}
			/* END OF EXTRACT: ACT-REFERENCE */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-ccode-reference */
			{
#line 771 "c-parser.act"

		c_code_append_reference((ZI112), &(ZI117));
	
#line 1603 "c-parser.c"
			}
			/* END OF ACTION: append-ccode-reference */
		}
		break;
	case (C_TOK_ACT_HTERMINAL):
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: append-ccode-terminal */
			{
#line 755 "c-parser.act"

		c_code_append_terminal((ZI112));
	
#line 1617 "c-parser.c"
			}
			/* END OF ACTION: append-ccode-terminal */
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
ZR124(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		NStringT ZI125;

		/* BEGINNING OF INLINE: c-parse-grammar::identifier */
		{
			switch (CURRENT_TERMINAL) {
			case (C_TOK_C_HIDENTIFIER):
				{
					/* BEGINNING OF EXTRACT: C-IDENTIFIER */
					{
#line 173 "c-parser.act"

		nstring_assign(&ZI125, c_lexer_string_value(c_current_stream));
	
#line 1653 "c-parser.c"
					}
					/* END OF EXTRACT: C-IDENTIFIER */
					ADVANCE_LEXER;
				}
				break;
			case (C_TOK_SID_HIDENTIFIER):
				{
					/* BEGINNING OF EXTRACT: SID-IDENTIFIER */
					{
#line 177 "c-parser.act"

		nstring_assign(&ZI125, c_lexer_string_value(c_current_stream));
	
#line 1667 "c-parser.c"
					}
					/* END OF EXTRACT: SID-IDENTIFIER */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: c-parse-grammar::identifier */
		/* BEGINNING OF ACTION: set-prefix */
		{
#line 233 "c-parser.act"

		int prefix;

		if (!c_inited_prefix_names) {
			nstring_copy_cstring(&c_prefix_names[CPFX_TYPE], "type");
			nstring_copy_cstring(&c_prefix_names[CPFX_FN], "function");
			nstring_copy_cstring(&c_prefix_names[CPFX_IN], "input");
			nstring_copy_cstring(&c_prefix_names[CPFX_OUT], "output");
			nstring_copy_cstring(&c_prefix_names[CPFX_LABEL], "label");
			nstring_copy_cstring(&c_prefix_names[CPFX_TERMINAL], "terminal");
			nstring_copy_cstring(&c_prefix_names[CPFX_PERSISTENTS], "persistents");
			c_inited_prefix_names = true;
		}

		for (prefix = 0; prefix < CPFX_NUM_PREFIXES; prefix++) {
			if (nstring_ci_equal((&ZI125), &c_prefix_names[prefix])) {
				break;
			}
		}

		c_current_prefix = (CPrefixT) prefix;
		if (c_current_prefix == CPFX_NUM_PREFIXES) {
			err_unknown("prefix type", (&ZI125));
		}
		nstring_destroy(&(ZI125));
	
#line 1707 "c-parser.c"
		}
		/* END OF ACTION: set-prefix */
		ZR126 ();
		/* BEGINNING OF INLINE: 127 */
		{
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				NStringT ZI128;

				switch (CURRENT_TERMINAL) {
				case (C_TOK_C_HIDENTIFIER):
					/* BEGINNING OF EXTRACT: C-IDENTIFIER */
					{
#line 173 "c-parser.act"

		nstring_assign(&ZI128, c_lexer_string_value(c_current_stream));
	
#line 1728 "c-parser.c"
					}
					/* END OF EXTRACT: C-IDENTIFIER */
					break;
				default:
					goto ZL4;
				}
				ADVANCE_LEXER;
				/* BEGINNING OF ACTION: x-set-prefix */
				{
#line 247 "c-parser.act"

		if (c_current_prefix == CPFX_NUM_PREFIXES) {
			nstring_destroy(&(ZI128));
		} else {
			NStringT *prefix = c_out_info_prefix(c_current_out_info, c_current_prefix);

			nstring_destroy(prefix);
			nstring_assign(prefix, &(ZI128));
		}
	
#line 1749 "c-parser.c"
				}
				/* END OF ACTION: x-set-prefix */
				ZR223 ();
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL4;
				}
			}
			goto ZL3;
		ZL4:;
			{
				/* BEGINNING OF ACTION: expected-c-identifier */
				{
#line 811 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("C identifier");
		}
	
#line 1769 "c-parser.c"
				}
				/* END OF ACTION: expected-c-identifier */
				/* BEGINNING OF ACTION: skip-to-end-of-prefix */
				{
#line 925 "c-parser.act"

		while (CURRENT_TERMINAL != (C_TOK_EOF)
			&& CURRENT_TERMINAL != (C_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HMAPS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTERMINALS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HASSIGNMENTS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HPARAM_HASSIGN)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HRESULT_HASSIGN)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HACTIONS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTRAILER)) {
			if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == (C_TOK_CODE)) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != (C_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		c_propagating_error = true;
	
#line 1803 "c-parser.c"
				}
				/* END OF ACTION: skip-to-end-of-prefix */
			}
		ZL3:;
		}
		/* END OF INLINE: 127 */
	}
	return;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
}

void
c_parse_grammar(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		/* BEGINNING OF INLINE: 202 */
		{
			switch (CURRENT_TERMINAL) {
			case (C_TOK_BLT_HPREFIXES):
				{
					ADVANCE_LEXER;
					ZR122 ();
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				break;
			}
		}
		/* END OF INLINE: 202 */
		/* BEGINNING OF INLINE: 203 */
		{
			switch (CURRENT_TERMINAL) {
			case (C_TOK_BLT_HPERSISTENTS):
				{
					ADVANCE_LEXER;
					ZR139 ();
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				break;
			}
		}
		/* END OF INLINE: 203 */
		/* BEGINNING OF INLINE: 204 */
		{
			switch (CURRENT_TERMINAL) {
			case (C_TOK_BLT_HMAPS):
				{
					ADVANCE_LEXER;
					ZR130 ();
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				break;
			}
		}
		/* END OF INLINE: 204 */
		/* BEGINNING OF INLINE: 205 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case (C_TOK_BLT_HHEADER):
					break;
				default:
					goto ZL6;
				}
				ADVANCE_LEXER;
			}
			goto ZL5;
		ZL6:;
			{
				/* BEGINNING OF ACTION: expected-blt-header */
				{
#line 865 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("'%header%'");
		}
	
#line 1900 "c-parser.c"
				}
				/* END OF ACTION: expected-blt-header */
			}
		ZL5:;
		}
		/* END OF INLINE: 205 */
		/* BEGINNING OF INLINE: 206 */
		{
			{
				CCodeP ZI207;

				ZR113 (&ZI207);
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL8;
				}
				/* BEGINNING OF ACTION: set-header1 */
				{
#line 322 "c-parser.act"

		c_code_check((ZI207), false, false, false, NULL, NULL, c_current_table);
		c_out_info_set_header1(c_current_out_info, (ZI207));
	
#line 1924 "c-parser.c"
				}
				/* END OF ACTION: set-header1 */
			}
			goto ZL7;
		ZL8:;
			{
				/* BEGINNING OF ACTION: expected-code */
				{
#line 859 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("code block");
		}
	
#line 1939 "c-parser.c"
				}
				/* END OF ACTION: expected-code */
			}
		ZL7:;
		}
		/* END OF INLINE: 206 */
		ZR220 ();
		/* BEGINNING OF INLINE: 209 */
		{
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				CCodeP ZI210;

				ZR113 (&ZI210);
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL10;
				}
				/* BEGINNING OF ACTION: set-header2 */
				{
#line 327 "c-parser.act"

		c_code_check((ZI210), false, false, false, NULL, NULL, c_current_table);
		c_out_info_set_header2(c_current_out_info, (ZI210));
	
#line 1968 "c-parser.c"
				}
				/* END OF ACTION: set-header2 */
			}
			goto ZL9;
		ZL10:;
			{
				/* BEGINNING OF ACTION: expected-code */
				{
#line 859 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("code block");
		}
	
#line 1983 "c-parser.c"
				}
				/* END OF ACTION: expected-code */
			}
		ZL9:;
		}
		/* END OF INLINE: 209 */
		ZR223 ();
		/* BEGINNING OF INLINE: 212 */
		{
			switch (CURRENT_TERMINAL) {
			case (C_TOK_BLT_HASSIGNMENTS):
				{
					ADVANCE_LEXER;
					ZR164 ();
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
		/* END OF INLINE: 212 */
		/* BEGINNING OF INLINE: 213 */
		{
			switch (CURRENT_TERMINAL) {
			case (C_TOK_BLT_HPARAM_HASSIGN):
				{
					ADVANCE_LEXER;
					ZR172 ();
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				break;
			}
		}
		/* END OF INLINE: 213 */
		/* BEGINNING OF INLINE: 214 */
		{
			switch (CURRENT_TERMINAL) {
			case (C_TOK_BLT_HRESULT_HASSIGN):
				{
					ADVANCE_LEXER;
					ZR179 ();
					if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				break;
			}
		}
		/* END OF INLINE: 214 */
		/* BEGINNING OF INLINE: 215 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case (C_TOK_BLT_HTERMINALS):
					break;
				default:
					goto ZL15;
				}
				ADVANCE_LEXER;
			}
			goto ZL14;
		ZL15:;
			{
				/* BEGINNING OF ACTION: expected-blt-terminals */
				{
#line 871 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("'%terminals%'");
		}
	
#line 2070 "c-parser.c"
				}
				/* END OF ACTION: expected-blt-terminals */
			}
		ZL14:;
		}
		/* END OF INLINE: 215 */
		ZR186 ();
		/* BEGINNING OF INLINE: 216 */
		{
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				switch (CURRENT_TERMINAL) {
				case (C_TOK_BLT_HACTIONS):
					break;
				default:
					goto ZL17;
				}
				ADVANCE_LEXER;
			}
			goto ZL16;
		ZL17:;
			{
				/* BEGINNING OF ACTION: expected-blt-actions */
				{
#line 877 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("'%actions%'");
		}
	
#line 2104 "c-parser.c"
				}
				/* END OF ACTION: expected-blt-actions */
			}
		ZL16:;
		}
		/* END OF INLINE: 216 */
		ZR193 ();
		/* BEGINNING OF INLINE: 217 */
		{
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				switch (CURRENT_TERMINAL) {
				case (C_TOK_BLT_HTRAILER):
					break;
				default:
					goto ZL19;
				}
				ADVANCE_LEXER;
			}
			goto ZL18;
		ZL19:;
			{
				/* BEGINNING OF ACTION: expected-blt-trailer */
				{
#line 883 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("'%trailer%'");
		}
	
#line 2138 "c-parser.c"
				}
				/* END OF ACTION: expected-blt-trailer */
			}
		ZL18:;
		}
		/* END OF INLINE: 217 */
		/* BEGINNING OF INLINE: 218 */
		{
			{
				CCodeP ZI219;

				ZR113 (&ZI219);
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL21;
				}
				/* BEGINNING OF ACTION: set-trailer1 */
				{
#line 726 "c-parser.act"

		c_code_check((ZI219), false, false, false, NULL, NULL, c_current_table);
		c_out_info_set_trailer1 (c_current_out_info, (ZI219));
	
#line 2162 "c-parser.c"
				}
				/* END OF ACTION: set-trailer1 */
			}
			goto ZL20;
		ZL21:;
			{
				/* BEGINNING OF ACTION: expected-code */
				{
#line 859 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("code block");
		}
	
#line 2177 "c-parser.c"
				}
				/* END OF ACTION: expected-code */
			}
		ZL20:;
		}
		/* END OF INLINE: 218 */
		ZR220 ();
		/* BEGINNING OF INLINE: 221 */
		{
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				CCodeP ZI222;

				ZR113 (&ZI222);
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL23;
				}
				/* BEGINNING OF ACTION: set-trailer2 */
				{
#line 731 "c-parser.act"

		c_code_check((ZI222), false, false, false, NULL, NULL, c_current_table);
		c_out_info_set_trailer2(c_current_out_info, (ZI222));
	
#line 2206 "c-parser.c"
				}
				/* END OF ACTION: set-trailer2 */
			}
			goto ZL22;
		ZL23:;
			{
				/* BEGINNING OF ACTION: expected-code */
				{
#line 859 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("code block");
		}
	
#line 2221 "c-parser.c"
				}
				/* END OF ACTION: expected-code */
			}
		ZL22:;
		}
		/* END OF INLINE: 221 */
		ZR223 ();
		/* BEGINNING OF INLINE: 224 */
		{
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				switch (CURRENT_TERMINAL) {
				case (C_TOK_EOF):
					break;
				default:
					goto ZL25;
				}
				ADVANCE_LEXER;
			}
			goto ZL24;
		ZL25:;
			{
				/* BEGINNING OF ACTION: expected-eof */
				{
#line 889 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("end of file");
		}
	
#line 2255 "c-parser.c"
				}
				/* END OF ACTION: expected-eof */
			}
		ZL24:;
		}
		/* END OF INLINE: 224 */
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: unhandled-syntax-error */
		{
#line 799 "c-parser.act"

		UNREACHED;
	
#line 2272 "c-parser.c"
		}
		/* END OF ACTION: unhandled-syntax-error */
	}
}

static void
ZR157(void)
{
	switch (CURRENT_TERMINAL) {
	case (C_TOK_C_HIDENTIFIER):
		{
			ZR154 ();
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
ZR159(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		/* BEGINNING OF ACTION: init-tuple */
		{
#line 347 "c-parser.act"

		types_init(&c_current_type);
	
#line 2315 "c-parser.c"
		}
		/* END OF ACTION: init-tuple */
		/* BEGINNING OF INLINE: 161 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case (C_TOK_OPEN_HTUPLE):
					break;
				default:
					goto ZL3;
				}
				ADVANCE_LEXER;
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: expected-open-tuple */
				{
#line 823 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("'('");
		}
	
#line 2340 "c-parser.c"
				}
				/* END OF ACTION: expected-open-tuple */
			}
		ZL2:;
		}
		/* END OF INLINE: 161 */
		ZR157 ();
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: skip-recover */
		{
#line 1110 "c-parser.act"

		c_propagating_error = false;
	
#line 2358 "c-parser.c"
		}
		/* END OF ACTION: skip-recover */
		/* BEGINNING OF INLINE: 162 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case (C_TOK_CLOSE_HTUPLE):
					break;
				default:
					goto ZL5;
				}
				ADVANCE_LEXER;
			}
			goto ZL4;
		ZL5:;
			{
				/* BEGINNING OF ACTION: expected-close-tuple */
				{
#line 829 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("')'");
		}
	
#line 2383 "c-parser.c"
				}
				/* END OF ACTION: expected-close-tuple */
			}
		ZL4:;
		}
		/* END OF INLINE: 162 */
	}
	return;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
}

static void
ZR141(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		NStringT ZI128;
		NStringT ZI145;

		/* BEGINNING OF INLINE: 143 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case (C_TOK_C_HIDENTIFIER):
					/* BEGINNING OF EXTRACT: C-IDENTIFIER */
					{
#line 173 "c-parser.act"

		nstring_assign(&ZI128, c_lexer_string_value(c_current_stream));
	
#line 2418 "c-parser.c"
					}
					/* END OF EXTRACT: C-IDENTIFIER */
					break;
				default:
					goto ZL3;
				}
				ADVANCE_LEXER;
			}
			goto ZL2;
		ZL3:;
			{
				/* BEGINNING OF ACTION: empty-string */
				{
#line 270 "c-parser.act"

		nstring_init(&(ZI128));
	
#line 2436 "c-parser.c"
				}
				/* END OF ACTION: empty-string */
				/* BEGINNING OF ACTION: expected-c-identifier */
				{
#line 811 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("C identifier");
		}
	
#line 2447 "c-parser.c"
				}
				/* END OF ACTION: expected-c-identifier */
			}
		ZL2:;
		}
		/* END OF INLINE: 143 */
		switch (CURRENT_TERMINAL) {
		case (C_TOK_TYPEMARK):
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 144 */
		{
			{
				switch (CURRENT_TERMINAL) {
				case (C_TOK_C_HIDENTIFIER):
					/* BEGINNING OF EXTRACT: C-IDENTIFIER */
					{
#line 173 "c-parser.act"

		nstring_assign(&ZI145, c_lexer_string_value(c_current_stream));
	
#line 2472 "c-parser.c"
					}
					/* END OF EXTRACT: C-IDENTIFIER */
					break;
				default:
					goto ZL5;
				}
				ADVANCE_LEXER;
			}
			goto ZL4;
		ZL5:;
			{
				/* BEGINNING OF ACTION: empty-string */
				{
#line 270 "c-parser.act"

		nstring_init(&(ZI145));
	
#line 2490 "c-parser.c"
				}
				/* END OF ACTION: empty-string */
				/* BEGINNING OF ACTION: expected-identifier */
				{
#line 805 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("identifier");
		}
	
#line 2501 "c-parser.c"
				}
				/* END OF ACTION: expected-identifier */
			}
		ZL4:;
		}
		/* END OF INLINE: 144 */
		/* BEGINNING OF ACTION: set-persistent */
		{
#line 257 "c-parser.act"

		if(persistent_list_find(c_out_info_persistents(c_current_out_info), (&ZI128)) == NULL) {
			PersistentT *p;

			p = persistent_create(&(ZI128), &(ZI145));
			persistent_list_append(c_out_info_persistents(c_current_out_info), p);
		} else {
			nstring_destroy(&(ZI128));
			nstring_destroy(&(ZI145));
			/* TODO error out E_c_persistent_variable_name_conflict((&ZI128))) ;*/
		}
	
#line 2523 "c-parser.c"
		}
		/* END OF ACTION: set-persistent */
		ZR223 ();
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
ZR181(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		NStringT ZI109;

		/* BEGINNING OF INLINE: c-parse-grammar::identifier */
		{
			switch (CURRENT_TERMINAL) {
			case (C_TOK_C_HIDENTIFIER):
				{
					/* BEGINNING OF EXTRACT: C-IDENTIFIER */
					{
#line 173 "c-parser.act"

		nstring_assign(&ZI109, c_lexer_string_value(c_current_stream));
	
#line 2558 "c-parser.c"
					}
					/* END OF EXTRACT: C-IDENTIFIER */
					ADVANCE_LEXER;
				}
				break;
			case (C_TOK_SID_HIDENTIFIER):
				{
					/* BEGINNING OF EXTRACT: SID-IDENTIFIER */
					{
#line 177 "c-parser.act"

		nstring_assign(&ZI109, c_lexer_string_value(c_current_stream));
	
#line 2572 "c-parser.c"
					}
					/* END OF EXTRACT: SID-IDENTIFIER */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: c-parse-grammar::identifier */
		/* BEGINNING OF ACTION: rassign */
		{
#line 508 "c-parser.act"

		c_current_entry = table_get_type(c_current_table, (&ZI109));
		if (c_current_entry == NULL) {
			error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
				"result assignment operation defined for unknown type '%S'", (void *) (&ZI109));
		} else if (type_get_result_assign_code(entry_get_type(c_current_entry))) {
			err_mult("result assignment", "type", (&ZI109));
			c_current_entry = NULL;
		}
		nstring_destroy(&(ZI109));
	
#line 2597 "c-parser.c"
		}
		/* END OF ACTION: rassign */
		ZR147 ();
		ZR126 ();
		/* BEGINNING OF INLINE: 184 */
		{
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				CCodeP ZI170;

				ZR113 (&ZI170);
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL4;
				}
				/* BEGINNING OF ACTION: x-rassign */
				{
#line 556 "c-parser.act"

		if (c_current_entry) {
			bool  errored = false;
			KeyT  *key     = entry_key (c_current_entry);
			TypeTupleT tmp;

			types_init (&tmp);
			types_add_type_entry (&tmp, c_current_entry, false);
			if (!types_disjoint_names(&c_saved_type)) {
				err_clash("result essignment", "parameter", "type", key, &c_saved_type);
				errored = true;
			}

			if (!types_fillin_types(&c_saved_type, &tmp)) {
				err_mismatch("parameter", "result assignment", "type", key, &c_saved_type, &tmp);
				errored = true;
			}

			if (!types_disjoint_names(&c_current_type)) {
				err_clash("result assignment", "result", "type", key, &c_saved_type);
				errored = true;
			}

			if (!types_fillin_types(&c_current_type, &tmp)) {
				err_mismatch("result", "result assignment", "type", key, &c_saved_type, &tmp);
				errored = true;
			}

			if (types_intersect(&c_saved_type, &c_current_type)) {
				err_formal_clash("result assignment", "type", key, &c_saved_type, &c_current_type);
				errored = true;
			}

			types_destroy (&tmp);
			if (errored) {
				types_destroy(&c_saved_type);
				types_destroy(&c_current_type);
				c_code_deallocate((ZI170));
				c_current_entry = NULL;
			} else {
				TypeT *type = entry_get_type(c_current_entry);

				c_code_check((ZI170), false, false, false, &c_saved_type,
					&c_current_type, c_current_table);
				type_set_result_assign_code (type,  (ZI170));
			}
		} else {
			types_destroy(&c_saved_type);
			types_destroy(&c_current_type);
			c_code_deallocate((ZI170));
		}
	
#line 2671 "c-parser.c"
				}
				/* END OF ACTION: x-rassign */
				ZR223 ();
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL4;
				}
			}
			goto ZL3;
		ZL4:;
			{
				/* BEGINNING OF ACTION: expected-code */
				{
#line 859 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("code block");
		}
	
#line 2691 "c-parser.c"
				}
				/* END OF ACTION: expected-code */
				/* BEGINNING OF ACTION: skip-to-end-of-result-assign */
				{
#line 1036 "c-parser.act"

		while (CURRENT_TERMINAL != (C_TOK_EOF)
			&& CURRENT_TERMINAL != (C_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTERMINALS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HACTIONS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTRAILER)) {
			if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == (C_TOK_CODE)) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != (C_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		c_propagating_error = true;
	
#line 2721 "c-parser.c"
				}
				/* END OF ACTION: skip-to-end-of-result-assign */
			}
		ZL3:;
		}
		/* END OF INLINE: 184 */
	}
	return;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
}

static void
ZR220(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case (C_TOK_SEPARATOR):
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: expected-separator */
		{
#line 817 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("','");
		}
	
#line 2761 "c-parser.c"
		}
		/* END OF ACTION: expected-separator */
	}
}

static void
ZR149(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		NStringT ZI128;

		switch (CURRENT_TERMINAL) {
		case (C_TOK_C_HIDENTIFIER):
			/* BEGINNING OF EXTRACT: C-IDENTIFIER */
			{
#line 173 "c-parser.act"

		nstring_assign(&ZI128, c_lexer_string_value(c_current_stream));
	
#line 2784 "c-parser.c"
			}
			/* END OF EXTRACT: C-IDENTIFIER */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 151 */
		{
			switch (CURRENT_TERMINAL) {
			case (C_TOK_TYPEMARK):
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: 152 */
					{
						{
							NStringT ZI145;

							/* BEGINNING OF INLINE: c-parse-grammar::identifier */
							{
								switch (CURRENT_TERMINAL) {
								case (C_TOK_C_HIDENTIFIER):
									{
										/* BEGINNING OF EXTRACT: C-IDENTIFIER */
										{
#line 173 "c-parser.act"

		nstring_assign(&ZI145, c_lexer_string_value(c_current_stream));
	
#line 2814 "c-parser.c"
										}
										/* END OF EXTRACT: C-IDENTIFIER */
										ADVANCE_LEXER;
									}
									break;
								case (C_TOK_SID_HIDENTIFIER):
									{
										/* BEGINNING OF EXTRACT: SID-IDENTIFIER */
										{
#line 177 "c-parser.act"

		nstring_assign(&ZI145, c_lexer_string_value(c_current_stream));
	
#line 2828 "c-parser.c"
										}
										/* END OF EXTRACT: SID-IDENTIFIER */
										ADVANCE_LEXER;
									}
									break;
								default:
									goto ZL4;
								}
							}
							/* END OF INLINE: c-parse-grammar::identifier */
							/* BEGINNING OF INLINE: 153 */
							{
								switch (CURRENT_TERMINAL) {
								case (C_TOK_REFERENCE):
									{
										ADVANCE_LEXER;
										/* BEGINNING OF ACTION: tuple-ref-type */
										{
#line 359 "c-parser.act"

		if (!types_add_typed_name(&c_current_type, c_current_table, &(ZI128),
			(&ZI145), true)) {
			error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
				"type '%S' hasn't been declared", (void *) (&ZI145));
		}
		nstring_destroy(&(ZI145));
	
#line 2856 "c-parser.c"
										}
										/* END OF ACTION: tuple-ref-type */
									}
									break;
								default:
									{
										/* BEGINNING OF ACTION: tuple-type */
										{
#line 350 "c-parser.act"

		if (!types_add_typed_name(&c_current_type, c_current_table, &(ZI128),
			(&ZI145), false)) {
			error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
				"type '%S' hasn't been declared", (void *) (&ZI145));
		}
		nstring_destroy(&(ZI145));
	
#line 2874 "c-parser.c"
										}
										/* END OF ACTION: tuple-type */
									}
									break;
								}
							}
							/* END OF INLINE: 153 */
						}
						goto ZL3;
					ZL4:;
						{
							/* BEGINNING OF ACTION: expected-identifier */
							{
#line 805 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("identifier");
		}
	
#line 2894 "c-parser.c"
							}
							/* END OF ACTION: expected-identifier */
							/* BEGINNING OF ACTION: destroy-string */
							{
#line 892 "c-parser.act"

		nstring_destroy(&(ZI128));
	
#line 2903 "c-parser.c"
							}
							/* END OF ACTION: destroy-string */
							/* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
							{
#line 896 "c-parser.act"

		while (CURRENT_TERMINAL != (C_TOK_EOF)
			&& CURRENT_TERMINAL != (C_TOK_DEFINE)
			&& CURRENT_TERMINAL != (C_TOK_CODE)
			&& CURRENT_TERMINAL != (C_TOK_SEPARATOR)
			&& CURRENT_TERMINAL != (C_TOK_CLOSE_HTUPLE)
			&& CURRENT_TERMINAL != (C_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HPARAM_HASSIGN)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HRESULT_HASSIGN)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTERMINALS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HACTIONS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTRAILER)) {
			if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != (C_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		c_propagating_error = true;
	
#line 2937 "c-parser.c"
							}
							/* END OF ACTION: skip-to-end-of-tuple-defn */
						}
					ZL3:;
					}
					/* END OF INLINE: 152 */
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: tuple-name */
					{
#line 368 "c-parser.act"

		types_add_name(&c_current_type, c_current_table, &(ZI128), false);
	
#line 2954 "c-parser.c"
					}
					/* END OF ACTION: tuple-name */
				}
				break;
			}
		}
		/* END OF INLINE: 151 */
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: expected-identifier */
		{
#line 805 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("identifier");
		}
	
#line 2974 "c-parser.c"
		}
		/* END OF ACTION: expected-identifier */
		/* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
		{
#line 896 "c-parser.act"

		while (CURRENT_TERMINAL != (C_TOK_EOF)
			&& CURRENT_TERMINAL != (C_TOK_DEFINE)
			&& CURRENT_TERMINAL != (C_TOK_CODE)
			&& CURRENT_TERMINAL != (C_TOK_SEPARATOR)
			&& CURRENT_TERMINAL != (C_TOK_CLOSE_HTUPLE)
			&& CURRENT_TERMINAL != (C_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HPARAM_HASSIGN)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HRESULT_HASSIGN)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTERMINALS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HACTIONS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTRAILER)) {
			if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != (C_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		c_propagating_error = true;
	
#line 3008 "c-parser.c"
		}
		/* END OF ACTION: skip-to-end-of-tuple-defn */
	}
}

static void
ZR223(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case (C_TOK_TERMINATOR):
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
#line 841 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("';'");
		}
	
#line 3040 "c-parser.c"
		}
		/* END OF ACTION: expected-terminator */
	}
}

static void
ZR188(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		NStringT ZI109;

		/* BEGINNING OF INLINE: c-parse-grammar::identifier */
		{
			switch (CURRENT_TERMINAL) {
			case (C_TOK_C_HIDENTIFIER):
				{
					/* BEGINNING OF EXTRACT: C-IDENTIFIER */
					{
#line 173 "c-parser.act"

		nstring_assign(&ZI109, c_lexer_string_value(c_current_stream));
	
#line 3066 "c-parser.c"
					}
					/* END OF EXTRACT: C-IDENTIFIER */
					ADVANCE_LEXER;
				}
				break;
			case (C_TOK_SID_HIDENTIFIER):
				{
					/* BEGINNING OF EXTRACT: SID-IDENTIFIER */
					{
#line 177 "c-parser.act"

		nstring_assign(&ZI109, c_lexer_string_value(c_current_stream));
	
#line 3080 "c-parser.c"
					}
					/* END OF EXTRACT: SID-IDENTIFIER */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: c-parse-grammar::identifier */
		/* BEGINNING OF ACTION: set-terminal */
		{
#line 578 "c-parser.act"

		c_current_entry = table_get_basic(c_current_table, (&ZI109));
		if (c_current_entry == NULL) {
			error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
				"extraction operation defined for unknown terminal '%S'", (void *) (&ZI109));
		} else {
			BasicT * basic = entry_get_basic(c_current_entry);

			if (basic_get_result_code(basic)) {
				err_mult("extraction", "terminal", (&ZI109));
				c_current_entry = NULL;
			} else if (types_equal_zero_tuple(basic_result (basic))) {
				error_posn(ERR_SERIOUS, c_lexer_stream_name(c_current_stream), (int) c_lexer_stream_line(c_current_stream),
					"extraction operation defined for terminal '%S' that returns nothing", (void *) (&ZI109));
				c_current_entry = NULL;
			}
		}
		nstring_destroy(&(ZI109));
	
#line 3113 "c-parser.c"
		}
		/* END OF ACTION: set-terminal */
		ZR147 ();
		ZR126 ();
		/* BEGINNING OF INLINE: 191 */
		{
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				CCodeP ZI170;

				ZR113 (&ZI170);
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL4;
				}
				/* BEGINNING OF ACTION: x-set-terminal */
				{
#line 636 "c-parser.act"

		if (c_current_entry) {
			BasicT     *basic   = entry_get_basic(c_current_entry);
			TypeTupleT *result  = basic_result(basic);
			bool       errored = false;
			KeyT       *key     = entry_key(c_current_entry);

			if (!types_disjoint_names(&c_saved_type)) {
				err_clash("extraction", "parameter", "terminal", key, &c_saved_type);
				errored = true;
			}

			if (!types_equal_zero_tuple(&c_saved_type)) {
				error_posn(ERR_SERIOUS, istream_name(&c_lexer_stream->istream), (int) istream_line(&c_lexer_stream->istream),
					"parameter type mismatch for extraction operation on "
					"terminal '%K' [%Y should be ()]",
					(void *) key, (void *) &c_saved_type);
				errored = true;
			}

			if (!types_disjoint_names(&c_current_type)) {
				err_clash("extraction", "result", "terminal", key, &c_saved_type);
				errored = true;
			}

			if (!types_fillin_types(&c_current_type, result)) {
				err_mismatch("result", "extraction", "terminal", key, &c_current_type, result);
				errored = true;
			}

			if (types_intersect(&c_saved_type, &c_current_type)) {
				err_formal_clash("extraction", "terminal", key, &c_saved_type, &c_current_type);
				errored = true;
			}

			if (errored) {
				types_destroy(&c_saved_type);
				types_destroy(&c_current_type);
				c_code_deallocate((ZI170));
				c_current_entry = NULL;
			} else {
				types_destroy(&c_saved_type);
				c_code_check((ZI170), false, true, false, NULL, &c_current_type, c_current_table);
				basic_set_result_code(basic,  (ZI170));
			}
		} else {
			types_destroy(&c_saved_type);
			types_destroy(&c_current_type);
			c_code_deallocate((ZI170));
		}
	
#line 3186 "c-parser.c"
				}
				/* END OF ACTION: x-set-terminal */
				ZR223 ();
				if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
					RESTORE_LEXER;
					goto ZL4;
				}
			}
			goto ZL3;
		ZL4:;
			{
				/* BEGINNING OF ACTION: expected-code */
				{
#line 859 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("code block");
		}
	
#line 3206 "c-parser.c"
				}
				/* END OF ACTION: expected-code */
				/* BEGINNING OF ACTION: skip-to-end-of-terminal */
				{
#line 1061 "c-parser.act"

		while (CURRENT_TERMINAL != (C_TOK_EOF)
			&& CURRENT_TERMINAL != (C_TOK_TERMINATOR)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HACTIONS)
			&& CURRENT_TERMINAL != (C_TOK_BLT_HTRAILER)) {
			if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == (C_TOK_CODE)) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == (C_TOK_SID_HIDENTIFIER) || CURRENT_TERMINAL == (C_TOK_C_HIDENTIFIER)) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != (C_TOK_EOF)) {
			ADVANCE_LEXER;
		}

		c_propagating_error = true;
	
#line 3235 "c-parser.c"
				}
				/* END OF ACTION: skip-to-end-of-terminal */
			}
		ZL3:;
		}
		/* END OF INLINE: 191 */
	}
	return;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
}

static void
ZR130(void)
{
ZL2_130:;
	switch (CURRENT_TERMINAL) {
	case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
		{
			ZR132 ();
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: skip-recover */
			{
#line 1110 "c-parser.act"

		c_propagating_error = false;
	
#line 3267 "c-parser.c"
			}
			/* END OF ACTION: skip-recover */
			/* BEGINNING OF INLINE: c-parse-grammar::map-list */
			goto ZL2_130;
			/* END OF INLINE: c-parse-grammar::map-list */
		}
		UNREACHED;
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
ZR147(void)
{
	switch (CURRENT_TERMINAL) {
	case (C_TOK_TYPEMARK):
		{
			ADVANCE_LEXER;
			ZR159 ();
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: save-tuple */
			{
#line 338 "c-parser.act"

		types_assign(&c_saved_type, &c_current_type);
	
#line 3304 "c-parser.c"
			}
			/* END OF ACTION: save-tuple */
			ZR163 ();
			ZR159 ();
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: null-type */
			{
#line 343 "c-parser.act"

		types_init(&c_saved_type);
		types_init(&c_current_type);
	
#line 3324 "c-parser.c"
			}
			/* END OF ACTION: null-type */
		}
		break;
	case (ERROR_TERMINAL):
		return;
	}
	return;
ZL1:;
	SAVE_LEXER ((ERROR_TERMINAL));
	return;
}

static void
ZR164(void)
{
ZL2_164:;
	switch (CURRENT_TERMINAL) {
	case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
		{
			ZR166 ();
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: skip-recover */
			{
#line 1110 "c-parser.act"

		c_propagating_error = false;
	
#line 3356 "c-parser.c"
			}
			/* END OF ACTION: skip-recover */
			/* BEGINNING OF INLINE: c-parse-grammar::assignment-list */
			goto ZL2_164;
			/* END OF INLINE: c-parse-grammar::assignment-list */
		}
		UNREACHED;
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
ZR172(void)
{
ZL2_172:;
	switch (CURRENT_TERMINAL) {
	case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
		{
			ZR174 ();
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: skip-recover */
			{
#line 1110 "c-parser.act"

		c_propagating_error = false;
	
#line 3393 "c-parser.c"
			}
			/* END OF ACTION: skip-recover */
			/* BEGINNING OF INLINE: c-parse-grammar::param-assign-list */
			goto ZL2_172;
			/* END OF INLINE: c-parse-grammar::param-assign-list */
		}
		UNREACHED;
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
ZR126(void)
{
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case (C_TOK_DEFINE):
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
#line 853 "c-parser.act"

		if (!c_propagating_error) {
			err_expected("'='");
		}
	
#line 3438 "c-parser.c"
		}
		/* END OF ACTION: expected-define */
	}
}

/* BEGINNING OF TRAILER */

#line 1120 "c-parser.act"


#line 3449 "c-parser.c"

/* END OF FILE */
