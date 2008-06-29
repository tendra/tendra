/*
 * Automatically generated from the files:
 *	c-parser.sid
 * and
 *	c-parser.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 142 "c-parser.act"


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

	#include <assert.h>

	#include "../shared/check/check.h"
	#include "c-parser.h"
	#include "../adt/action.h"
	#include "c-code.h"
	#include "c-out-info.h"
	#include "../adt/basic.h"
	#include "../adt/entry.h"
	#include "../gen-errors.h"
	#include "../adt/type.h"
	#include "../adt/types.h"

	#define ERROR_TERMINAL C_TOK_ERROR
	#define CURRENT_TERMINAL c_lexer_get_terminal (c_current_stream)
	#define ADVANCE_LEXER c_lexer_next_token (c_current_stream)
	#define SAVE_LEXER(x) (c_lexer_save_terminal (c_current_stream, (CTokenT) (x)))
	#define RESTORE_LEXER (c_lexer_restore_terminal (c_current_stream))

	/* typedefs for the maps section */
	typedef CCodeT *CCodeP;

	static NStringT    c_prefix_names [CPFX_NUM_PREFIXES];
	static BoolT       c_inited_prefix_names = FALSE;
	static CPrefixT    c_current_prefix;
	static EntryT     *c_current_entry;
	static TypeTupleT  c_saved_type;
	static TypeTupleT  c_current_type;
	static BoolT       c_propagating_error = FALSE;

	CLexerStreamT *c_current_stream;
	COutputInfoT  *c_current_out_info;
	TableT        *c_current_table;

#line 109 "tmp.c-parser.c"


#ifndef ERROR_TERMINAL
#error "-s no-numeric-terminals given and ERROR_TERMINAL is not defined"
#endif

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZR136(void);
static void ZR176(void);
static void ZR117(CCodeP);
static void ZR183(void);
static void ZR111(CCodeP *);
static void ZR160(void);
static void ZR129(void);
static void ZR163(void);
static void ZR192(void);
static void ZR151(void);
static void ZR190(void);
static void ZR171(void);
static void ZR119(void);
static void ZR113(CCodeP);
static void ZR121(void);
extern void c_parse_grammar(void);
static void ZR154(void);
static void ZR156(void);
static void ZR138(void);
static void ZR178(void);
static void ZR217(void);
static void ZR146(void);
static void ZR185(void);
static void ZR127(void);
static void ZR144(void);
static void ZR161(void);
static void ZR169(void);
static void ZR123(void);
static void ZR126(void);

/* BEGINNING OF STATIC VARIABLES */

static BoolT ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZR136(void)
{
  ZL2_136:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_C_HIDENTIFIER):
	{
	    ZR138 ();
	    /* BEGINNING OF INLINE: c-parse-grammar::persistent-list */
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_136;
	    }
	    /* END OF INLINE: c-parse-grammar::persistent-list */
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
ZR176(void)
{
  ZL2_176:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
	{
	    ZR178 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 1113 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 201 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: skip-recover */
	    /* BEGINNING OF INLINE: c-parse-grammar::result-assign-list */
	    goto ZL2_176;
	    /* END OF INLINE: c-parse-grammar::result-assign-list */
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
ZR117(CCodeP ZI110)
{
  ZL2_117:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_ACT_HAT): case (C_TOK_ACT_HEXCEPTION): case (C_TOK_ACT_HTERMINAL): case (C_TOK_ACT_HADVANCE):
      case (C_TOK_ACT_HBASIC): case (C_TOK_ACT_HLABEL): case (C_TOK_ACT_HREFERENCE): case (C_TOK_ACT_HIDENTIFIER):
      case (C_TOK_ACT_HMODIFIABLE): case (C_TOK_ACT_HCODESTRING): case (C_TOK_ACT_HEOF):
	{
	    ZR113 (ZI110);
	    /* BEGINNING OF INLINE: c-parse-grammar::code-block::code-body */
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_117;
	    }
	    /* END OF INLINE: c-parse-grammar::code-block::code-body */
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
ZR183(void)
{
  ZL2_183:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
	{
	    ZR185 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 1113 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 269 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: skip-recover */
	    /* BEGINNING OF INLINE: c-parse-grammar::terminal-list */
	    goto ZL2_183;
	    /* END OF INLINE: c-parse-grammar::terminal-list */
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
ZR111(CCodeP *ZO110)
{
    CCodeP ZI110;

    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case (C_TOK_ACT_HCODESTART):
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF ACTION: ccode-init */
	{
#line 744 "c-parser.act"

		(ZI110) = c_code_create(istream_name(&(c_lexer_stream->istream)), 
			istream_line(&(c_lexer_stream->istream)));
	
#line 311 "tmp.c-parser.c"
	}
	/* END OF ACTION: ccode-init */
	ZR117 (ZI110);
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
    *ZO110 = ZI110;
}

static void
ZR160(void)
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
#line 838 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_arrow();
		}
	
#line 360 "tmp.c-parser.c"
	}
	/* END OF ACTION: expected-arrow */
    }
}

static void
ZR129(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI131;

	/* BEGINNING OF INLINE: c-parse-grammar::identifier */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_C_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI131, c_lexer_string_value(c_current_stream));
	
#line 386 "tmp.c-parser.c"
		    }
		    /* END OF EXTRACT: C-IDENTIFIER */
		    ADVANCE_LEXER;
		}
		break;
	      case (C_TOK_SID_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: SID-IDENTIFIER */
		    {
#line 200 "c-parser.act"

		nstring_assign(&ZI131, c_lexer_string_value(c_current_stream));
	
#line 400 "tmp.c-parser.c"
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
#line 298 "c-parser.act"

		c_current_entry = table_get_entry(c_current_table, (&ZI131));
		if (c_current_entry == NULL) {
			E_c_unknown_identifier((&ZI131));
		} else if (entry_get_mapping(c_current_entry)) {
			E_c_remapped_identifier((&ZI131));
			c_current_entry = NULL;
		} else {
			switch (entry_type(c_current_entry)) EXHAUSTIVE {
			case ET_NAME:
			case ET_ACTION:
			case ET_NON_LOCAL:
				E_c_illegal_map((&ZI131));
				c_current_entry = NULL;
				break;
			case ET_RENAME:
			case ET_PREDICATE:
				/* UNREACHED */
				break;
			case ET_TYPE:
			case ET_RULE:
			case ET_BASIC:
				break;
			}
		}
		nstring_destroy(&(ZI131));
	
#line 441 "tmp.c-parser.c"
	}
	/* END OF ACTION: set-map */
	ZR160 ();
	/* BEGINNING OF INLINE: 133 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		NStringT ZI134;

		switch (CURRENT_TERMINAL) {
		  case (C_TOK_C_HIDENTIFIER):
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI134, c_lexer_string_value(c_current_stream));
	
#line 462 "tmp.c-parser.c"
		    }
		    /* END OF EXTRACT: C-IDENTIFIER */
		    break;
		  default:
		    goto ZL4;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: x-set-map */
		{
#line 327 "c-parser.act"

		if (c_current_entry) {
			entry_set_mapping(c_current_entry, &(ZI134));
		} else {
			nstring_destroy(&(ZI134));
		}
	
#line 480 "tmp.c-parser.c"
		}
		/* END OF ACTION: x-set-map */
		ZR126 ();
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
#line 814 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_c_identifier();
		}
	
#line 500 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-c-identifier */
		/* BEGINNING OF ACTION: skip-to-end-of-map */
		{
#line 957 "c-parser.act"

		while (CURRENT_TERMINAL != C_TOK_EOF
			&& CURRENT_TERMINAL != C_TOK_TERMINATOR
			&& CURRENT_TERMINAL != C_TOK_BLT_HASSIGNMENTS
			&& CURRENT_TERMINAL != C_TOK_BLT_HPARAM_HASSIGN
			&& CURRENT_TERMINAL != C_TOK_BLT_HRESULT_HASSIGN
			&& CURRENT_TERMINAL != C_TOK_BLT_HTERMINALS
			&& CURRENT_TERMINAL != C_TOK_BLT_HACTIONS
			&& CURRENT_TERMINAL != C_TOK_BLT_HTRAILER) {
			if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == C_TOK_CODE) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != C_TOK_EOF) {
			ADVANCE_LEXER;
		}

		c_propagating_error = TRUE;
	
#line 533 "tmp.c-parser.c"
		}
		/* END OF ACTION: skip-to-end-of-map */
	    }
	  ZL3:;
	}
	/* END OF INLINE: 133 */
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
	NStringT ZI107;

	/* BEGINNING OF INLINE: c-parse-grammar::identifier */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_C_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI107, c_lexer_string_value(c_current_stream));
	
#line 567 "tmp.c-parser.c"
		    }
		    /* END OF EXTRACT: C-IDENTIFIER */
		    ADVANCE_LEXER;
		}
		break;
	      case (C_TOK_SID_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: SID-IDENTIFIER */
		    {
#line 200 "c-parser.act"

		nstring_assign(&ZI107, c_lexer_string_value(c_current_stream));
	
#line 581 "tmp.c-parser.c"
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
#line 392 "c-parser.act"

		c_current_entry = table_get_type(c_current_table, (&ZI107));
		if (c_current_entry == NULL) {
			E_c_unknown_assign((&ZI107));
		} else if (type_get_assign_code(entry_get_type(c_current_entry))) {
			E_c_assign_mult_def((&ZI107));
			c_current_entry = NULL;
		}
		nstring_destroy(&(ZI107));
	
#line 605 "tmp.c-parser.c"
	}
	/* END OF ACTION: assign */
	ZR144 ();
	ZR123 ();
	/* BEGINNING OF INLINE: 166 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI167;

		ZR111 (&ZI167);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
		/* BEGINNING OF ACTION: x-assign */
		{
#line 440 "c-parser.act"

		if (c_current_entry) {
			BoolT  errored = FALSE;
			KeyT  *key     = entry_key (c_current_entry);
			TypeTupleT tmp;

			types_init(&tmp);
			types_add_type_entry(&tmp, c_current_entry, FALSE);

			if (!types_disjoint_names(&c_saved_type)) {
				E_c_assign_param_clash(key, &c_saved_type);
				errored = TRUE;
			}

			if (!types_fillin_types (&c_saved_type, &tmp)) {
				E_c_assign_param_mismatch(key, &tmp, &c_saved_type);
				errored = TRUE;
			}

			if (!types_disjoint_names (&c_current_type)) {
				E_c_assign_result_clash(key, &c_current_type);
				errored = TRUE;
			}

			if (!types_fillin_types (&c_current_type, &tmp)) {
				E_c_assign_result_mismatch(key, &tmp, &c_current_type);
				errored = TRUE;
			}

			if (types_intersect (&c_saved_type, &c_current_type)) {
				E_c_assign_formal_clash(key, &c_saved_type, &c_current_type);
				errored = TRUE;
			}

			types_destroy(&tmp);
			if (errored) {
				types_destroy(&c_saved_type);
				types_destroy(&c_current_type);
				c_code_deallocate((ZI167));
				c_current_entry = NULL;
			} else {
			TypeT *type;

				type = entry_get_type (c_current_entry);
				c_code_check((ZI167), FALSE, FALSE, &c_saved_type, &c_current_type, c_current_table);
				type_set_assign_code(type,  (ZI167));
			}
		} else {
			types_destroy(&c_saved_type);
			types_destroy(&c_current_type);
			c_code_deallocate((ZI167));
		}
	
#line 680 "tmp.c-parser.c"
		}
		/* END OF ACTION: x-assign */
		ZR126 ();
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
#line 862 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 700 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
		/* BEGINNING OF ACTION: skip-to-end-of-assignment */
		{
#line 985 "c-parser.act"

		while (CURRENT_TERMINAL != C_TOK_EOF
			&& CURRENT_TERMINAL != C_TOK_TERMINATOR
			&& CURRENT_TERMINAL != C_TOK_BLT_HPARAM_HASSIGN
			&& CURRENT_TERMINAL != C_TOK_BLT_HRESULT_HASSIGN
			&& CURRENT_TERMINAL != C_TOK_BLT_HTERMINALS
			&& CURRENT_TERMINAL != C_TOK_BLT_HACTIONS
			&& CURRENT_TERMINAL != C_TOK_BLT_HTRAILER) {
			if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == C_TOK_CODE) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != C_TOK_EOF) {
			ADVANCE_LEXER;
		}

		c_propagating_error = TRUE;
	
#line 732 "tmp.c-parser.c"
		}
		/* END OF ACTION: skip-to-end-of-assignment */
	    }
	  ZL3:;
	}
	/* END OF INLINE: 166 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR192(void)
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
	/* BEGINNING OF INLINE: 194 */
	{
	    {
		NStringT ZI107;

		/* BEGINNING OF INLINE: c-parse-grammar::identifier */
		{
		    switch (CURRENT_TERMINAL) {
		      case (C_TOK_C_HIDENTIFIER):
			{
			    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
			    {
#line 196 "c-parser.act"

		nstring_assign(&ZI107, c_lexer_string_value(c_current_stream));
	
#line 776 "tmp.c-parser.c"
			    }
			    /* END OF EXTRACT: C-IDENTIFIER */
			    ADVANCE_LEXER;
			}
			break;
		      case (C_TOK_SID_HIDENTIFIER):
			{
			    /* BEGINNING OF EXTRACT: SID-IDENTIFIER */
			    {
#line 200 "c-parser.act"

		nstring_assign(&ZI107, c_lexer_string_value(c_current_stream));
	
#line 790 "tmp.c-parser.c"
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
#line 663 "c-parser.act"

		c_current_entry = table_get_action(c_current_table, (&ZI107));
		if (c_current_entry == NULL) {
			E_c_unknown_action((&ZI107));
		} else {
			ActionT *action;

			action = entry_get_action(c_current_entry);
			if (action_get_code(action)) {
				E_c_action_mult_def((&ZI107));
				c_current_entry = NULL;
			}
		}
		nstring_destroy(&(ZI107));
	
#line 819 "tmp.c-parser.c"
		}
		/* END OF ACTION: set-action */
		/* BEGINNING OF INLINE: 195 */
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
#line 850 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_end_action();
		}
	
#line 844 "tmp.c-parser.c"
			}
			/* END OF ACTION: expected-end-action */
		    }
		  ZL5:;
		}
		/* END OF INLINE: 195 */
		ZR144 ();
		ZR123 ();
		/* BEGINNING OF INLINE: 197 */
		{
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		    {
			CCodeP ZI167;

			ZR111 (&ZI167);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			    RESTORE_LEXER;
			    goto ZL8;
			}
			/* BEGINNING OF ACTION: x-set-action */
			{
#line 714 "c-parser.act"

		if (c_current_entry) {
			ActionT    *action  = entry_get_action(c_current_entry);
			TypeTupleT *param   = action_param(action);
			TypeTupleT *result  = action_result(action);
			BoolT       errored = FALSE;
			KeyT       *key     = entry_key(c_current_entry);

			if (!types_disjoint_names(&c_saved_type)) {
				E_c_action_param_clash(key, &c_saved_type);
				errored = TRUE;
			}

			if (!types_fillin_types(&c_saved_type, param)) {
				E_c_action_param_mismatch(key, param, &c_saved_type);
				errored = TRUE;
			}

			if (!types_disjoint_names(&c_current_type)) {
				E_c_action_result_clash(key, &c_current_type);
				errored = TRUE;
			}

			if (!types_fillin_types(&c_current_type, result)) {
				E_c_action_result_mismatch(key, result, &c_current_type);
				errored = TRUE;
			}

			if (types_intersect(&c_saved_type, &c_current_type)) {
				E_c_action_formal_clash(key, &c_saved_type, &c_current_type);
				errored = TRUE;
			}

			if (errored) {
				types_destroy(&c_saved_type);
				types_destroy(&c_current_type);
				c_code_deallocate((ZI167));
				c_current_entry = NULL;
			} else {
				c_code_check((ZI167), TRUE, FALSE, &c_saved_type, &c_current_type, c_current_table);
				types_propogate_mutations(param, &c_saved_type);
				action_set_code(action,  (ZI167));
			}
		} else {
			types_destroy(&c_saved_type);
			types_destroy(&c_current_type);
			c_code_deallocate((ZI167));
		}
	
#line 919 "tmp.c-parser.c"
			}
			/* END OF ACTION: x-set-action */
			ZR126 ();
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
#line 862 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 939 "tmp.c-parser.c"
			}
			/* END OF ACTION: expected-code */
			/* BEGINNING OF ACTION: skip-to-end-of-action */
			{
#line 1088 "c-parser.act"

		while (CURRENT_TERMINAL != C_TOK_EOF
			&& CURRENT_TERMINAL != C_TOK_TERMINATOR
			&& CURRENT_TERMINAL != C_TOK_BLT_HTRAILER) {
			if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER
			|| CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == C_TOK_CODE) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != C_TOK_EOF) {
			ADVANCE_LEXER;
		}

		c_propagating_error = TRUE;
	
#line 968 "tmp.c-parser.c"
			}
			/* END OF ACTION: skip-to-end-of-action */
		    }
		  ZL7:;
		}
		/* END OF INLINE: 197 */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: expected-identifier */
		{
#line 808 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_identifier();
		}
	
#line 987 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-identifier */
		/* BEGINNING OF ACTION: skip-to-end-of-action */
		{
#line 1088 "c-parser.act"

		while (CURRENT_TERMINAL != C_TOK_EOF
			&& CURRENT_TERMINAL != C_TOK_TERMINATOR
			&& CURRENT_TERMINAL != C_TOK_BLT_HTRAILER) {
			if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER
			|| CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == C_TOK_CODE) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != C_TOK_EOF) {
			ADVANCE_LEXER;
		}

		c_propagating_error = TRUE;
	
#line 1016 "tmp.c-parser.c"
		}
		/* END OF ACTION: skip-to-end-of-action */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 194 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR151(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_151:;
    {
	ZR146 ();
	/* BEGINNING OF INLINE: 153 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-close-tuple-or-skipped-or-eof */
		{
#line 1116 "c-parser.act"

		(ZI0) = (CURRENT_TERMINAL == C_TOK_CLOSE_HTUPLE
			|| CURRENT_TERMINAL == C_TOK_EOF
			|| c_propagating_error);
	
#line 1054 "tmp.c-parser.c"
		}
		/* END OF ACTION: is-close-tuple-or-skipped-or-eof */
		if (!ZI0)
		    goto ZL5;
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL5:;
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_SEPARATOR):
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: c-parse-grammar::function-type-defn::tuple-defn-list-1 */
		    goto ZL2_151;
		    /* END OF INLINE: c-parse-grammar::function-type-defn::tuple-defn-list-1 */
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
#line 820 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_separator();
		}
	
#line 1086 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-separator */
		/* BEGINNING OF INLINE: c-parse-grammar::function-type-defn::tuple-defn-list-1 */
		goto ZL2_151;
		/* END OF INLINE: c-parse-grammar::function-type-defn::tuple-defn-list-1 */
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
	/* END OF INLINE: 153 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR190(void)
{
  ZL2_190:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_BEGIN_HACTION):
	{
	    ZR192 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 1113 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 1122 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: skip-recover */
	    /* BEGINNING OF INLINE: c-parse-grammar::action-list */
	    goto ZL2_190;
	    /* END OF INLINE: c-parse-grammar::action-list */
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
ZR171(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI107;

	/* BEGINNING OF INLINE: c-parse-grammar::identifier */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_C_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI107, c_lexer_string_value(c_current_stream));
	
#line 1161 "tmp.c-parser.c"
		    }
		    /* END OF EXTRACT: C-IDENTIFIER */
		    ADVANCE_LEXER;
		}
		break;
	      case (C_TOK_SID_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: SID-IDENTIFIER */
		    {
#line 200 "c-parser.act"

		nstring_assign(&ZI107, c_lexer_string_value(c_current_stream));
	
#line 1175 "tmp.c-parser.c"
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
#line 457 "c-parser.act"

		c_current_entry = table_get_type(c_current_table, (&ZI107));
		if (c_current_entry == NULL) {
			E_c_unknown_param_assign((&ZI107));
		} else if (type_get_param_assign_code(entry_get_type(c_current_entry))) {
			E_c_param_assign_mult_def((&ZI107));
			c_current_entry = NULL;
		}
		nstring_destroy(&(ZI107));
	
#line 1199 "tmp.c-parser.c"
	}
	/* END OF ACTION: passign */
	ZR144 ();
	ZR123 ();
	/* BEGINNING OF INLINE: 174 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI167;

		ZR111 (&ZI167);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
		/* BEGINNING OF ACTION: x-passign */
		{
#line 504 "c-parser.act"

		if (c_current_entry) {
			BoolT  errored = FALSE;
			KeyT  *key     = entry_key(c_current_entry);
			TypeTupleT tmp;

			types_init(&tmp);
			types_add_type_entry(&tmp, c_current_entry, FALSE);
			if (!types_disjoint_names(&c_saved_type)) {
				E_c_param_assign_param_clash(key, &c_saved_type);
				errored = TRUE;
			}

			if (!types_fillin_types(&c_saved_type, &tmp)) {
				E_c_param_assign_param_mismatch(key, &tmp, &c_saved_type);
				errored = TRUE;
			}

			if (!types_disjoint_names(&c_current_type)) {
				E_c_param_assign_result_clash(key, &c_current_type);
				errored = TRUE;
			}

			if (!types_fillin_types(&c_current_type, &tmp)) {
				E_c_param_assign_res_mismatch(key, &tmp, &c_current_type);
				errored = TRUE;
			}

			if (types_intersect(&c_saved_type, &c_current_type)) {
				E_c_param_assign_formal_clash(key, &c_saved_type, &c_current_type);
				errored = TRUE;
			}

			types_destroy(&tmp);
			if (errored) {
				types_destroy(&c_saved_type);
				types_destroy(&c_current_type);
				c_code_deallocate((ZI167));
				c_current_entry = NULL;
			} else {
				TypeT *type = entry_get_type(c_current_entry);

				c_code_check((ZI167), FALSE, TRUE, &c_saved_type,
					&c_current_type, c_current_table);
				type_set_param_assign_code(type,  (ZI167));
			}
		} else {
			types_destroy(&c_saved_type);
			types_destroy(&c_current_type);
			c_code_deallocate((ZI167));
		}
	
#line 1273 "tmp.c-parser.c"
		}
		/* END OF ACTION: x-passign */
		ZR126 ();
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
#line 862 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 1293 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
		/* BEGINNING OF ACTION: skip-to-end-of-param-assign */
		{
#line 1012 "c-parser.act"

		while (CURRENT_TERMINAL != C_TOK_EOF
			&& CURRENT_TERMINAL != C_TOK_TERMINATOR
			&& CURRENT_TERMINAL != C_TOK_BLT_HRESULT_HASSIGN
			&& CURRENT_TERMINAL != C_TOK_BLT_HTERMINALS
			&& CURRENT_TERMINAL != C_TOK_BLT_HACTIONS
			&& CURRENT_TERMINAL != C_TOK_BLT_HTRAILER) {
			if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER
				|| CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == C_TOK_CODE) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != C_TOK_EOF) {
			ADVANCE_LEXER;
		}

		c_propagating_error = TRUE;
	
#line 1325 "tmp.c-parser.c"
		}
		/* END OF ACTION: skip-to-end-of-param-assign */
	    }
	  ZL3:;
	}
	/* END OF INLINE: 174 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR119(void)
{
  ZL2_119:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
	{
	    ZR121 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 1113 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 1357 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: skip-recover */
	    /* BEGINNING OF INLINE: c-parse-grammar::prefix-list */
	    goto ZL2_119;
	    /* END OF INLINE: c-parse-grammar::prefix-list */
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
ZR113(CCodeP ZI110)
{
    switch (CURRENT_TERMINAL) {
      case (C_TOK_ACT_HADVANCE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-advance */
	    {
#line 763 "c-parser.act"

		c_code_append_advance((ZI110));
	
#line 1389 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: append-ccode-advance */
	}
	break;
      case (C_TOK_ACT_HAT):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-at */
	    {
#line 750 "c-parser.act"

		NStringT ns;
		nstring_copy_cstring(&ns, "@");	/* TODO append '@' to code buffer? */
		c_code_append_string((ZI110), &ns);	/* TODO really append_label()? */
	
#line 1405 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: append-ccode-at */
	}
	break;
      case (C_TOK_ACT_HBASIC):
	{
	    NStringT ZI115;

	    /* BEGINNING OF EXTRACT: ACT-BASIC */
	    {
#line 208 "c-parser.act"

		nstring_assign(&ZI115, c_lexer_string_value(c_current_stream));
	
#line 1420 "tmp.c-parser.c"
	    }
	    /* END OF EXTRACT: ACT-BASIC */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-basic */
	    {
#line 767 "c-parser.act"

		c_code_append_basic((ZI110), &(ZI115));
	
#line 1430 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: append-ccode-basic */
	}
	break;
      case (C_TOK_ACT_HCODESTRING):
	{
	    NStringT ZI116;

	    /* BEGINNING OF EXTRACT: ACT-CODESTRING */
	    {
#line 228 "c-parser.act"

		nstring_assign(&ZI116, c_lexer_string_value(c_current_stream));
	
#line 1445 "tmp.c-parser.c"
	    }
	    /* END OF EXTRACT: ACT-CODESTRING */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-codestring */
	    {
#line 787 "c-parser.act"

		assert(!nstring_contains(&(ZI116), '@'));	/* XXX '@'? */
		c_code_append_string((ZI110), &(ZI116));
	
#line 1456 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: append-ccode-codestring */
	}
	break;
      case (C_TOK_ACT_HEOF):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: E-eof-in-code-block */
	    {
#line 793 "c-parser.act"

		E_c_eof_in_code(&c_lexer_stream->istream);
	
#line 1470 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: E-eof-in-code-block */
	}
	break;
      case (C_TOK_ACT_HEXCEPTION):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-exception */
	    {
#line 755 "c-parser.act"

		c_code_append_exception((ZI110));
	
#line 1484 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: append-ccode-exception */
	}
	break;
      case (C_TOK_ACT_HIDENTIFIER):
	{
	    NStringT ZI115;

	    /* BEGINNING OF EXTRACT: ACT-IDENTIFIER */
	    {
#line 220 "c-parser.act"

		nstring_assign(&ZI115, c_lexer_string_value(c_current_stream));
	
#line 1499 "tmp.c-parser.c"
	    }
	    /* END OF EXTRACT: ACT-IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-identifier */
	    {
#line 779 "c-parser.act"

		c_code_append_identifier((ZI110), &(ZI115));
	
#line 1509 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: append-ccode-identifier */
	}
	break;
      case (C_TOK_ACT_HLABEL):
	{
	    NStringT ZI115;

	    /* BEGINNING OF EXTRACT: ACT-LABEL */
	    {
#line 212 "c-parser.act"

		nstring_assign(&ZI115, c_lexer_string_value(c_current_stream));
	
#line 1524 "tmp.c-parser.c"
	    }
	    /* END OF EXTRACT: ACT-LABEL */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-label */
	    {
#line 771 "c-parser.act"

		c_code_append_label((ZI110), &(ZI115));
	
#line 1534 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: append-ccode-label */
	}
	break;
      case (C_TOK_ACT_HMODIFIABLE):
	{
	    NStringT ZI115;

	    /* BEGINNING OF EXTRACT: ACT-MODIFIABLE */
	    {
#line 224 "c-parser.act"

		nstring_assign(&ZI115, c_lexer_string_value(c_current_stream));
	
#line 1549 "tmp.c-parser.c"
	    }
	    /* END OF EXTRACT: ACT-MODIFIABLE */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-modifiable */
	    {
#line 783 "c-parser.act"

		c_code_append_modifiable((ZI110), &(ZI115));
	
#line 1559 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: append-ccode-modifiable */
	}
	break;
      case (C_TOK_ACT_HREFERENCE):
	{
	    NStringT ZI115;

	    /* BEGINNING OF EXTRACT: ACT-REFERENCE */
	    {
#line 216 "c-parser.act"

		nstring_assign(&ZI115, c_lexer_string_value(c_current_stream));
	
#line 1574 "tmp.c-parser.c"
	    }
	    /* END OF EXTRACT: ACT-REFERENCE */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-reference */
	    {
#line 775 "c-parser.act"

		c_code_append_reference((ZI110), &(ZI115));
	
#line 1584 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: append-ccode-reference */
	}
	break;
      case (C_TOK_ACT_HTERMINAL):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-terminal */
	    {
#line 759 "c-parser.act"

		c_code_append_terminal((ZI110));
	
#line 1598 "tmp.c-parser.c"
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
ZR121(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI122;

	/* BEGINNING OF INLINE: c-parse-grammar::identifier */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_C_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI122, c_lexer_string_value(c_current_stream));
	
#line 1634 "tmp.c-parser.c"
		    }
		    /* END OF EXTRACT: C-IDENTIFIER */
		    ADVANCE_LEXER;
		}
		break;
	      case (C_TOK_SID_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: SID-IDENTIFIER */
		    {
#line 200 "c-parser.act"

		nstring_assign(&ZI122, c_lexer_string_value(c_current_stream));
	
#line 1648 "tmp.c-parser.c"
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
#line 252 "c-parser.act"

		int prefix;

		if (!c_inited_prefix_names) {
			nstring_copy_cstring(&(c_prefix_names[CPFX_TYPE]), "type");
			nstring_copy_cstring(&(c_prefix_names[CPFX_FN]), "function");
			nstring_copy_cstring(&(c_prefix_names[CPFX_IN]), "input");
			nstring_copy_cstring(&(c_prefix_names[CPFX_OUT]), "output");
			nstring_copy_cstring(&(c_prefix_names[CPFX_LABEL]), "label");
			nstring_copy_cstring(&(c_prefix_names[CPFX_TERMINAL]), "terminal");
			nstring_copy_cstring(&(c_prefix_names[CPFX_PERSISTENTS]), "persistents");
			c_inited_prefix_names = TRUE;
		}

		for (prefix = 0; prefix < CPFX_NUM_PREFIXES; prefix++) {
			if (nstring_ci_equal((&ZI122), &c_prefix_names[prefix])) {
				break;
			}
		}

		c_current_prefix = (CPrefixT) prefix;
		if (c_current_prefix == CPFX_NUM_PREFIXES) {
			E_c_unknown_prefix((&ZI122));
		}
		nstring_destroy(&(ZI122));
	
#line 1688 "tmp.c-parser.c"
	}
	/* END OF ACTION: set-prefix */
	ZR123 ();
	/* BEGINNING OF INLINE: 124 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		NStringT ZI125;

		switch (CURRENT_TERMINAL) {
		  case (C_TOK_C_HIDENTIFIER):
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI125, c_lexer_string_value(c_current_stream));
	
#line 1709 "tmp.c-parser.c"
		    }
		    /* END OF EXTRACT: C-IDENTIFIER */
		    break;
		  default:
		    goto ZL4;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: x-set-prefix */
		{
#line 266 "c-parser.act"

		if (c_current_prefix == CPFX_NUM_PREFIXES) {
			nstring_destroy(&(ZI125));
		} else {
			NStringT *prefix = c_out_info_prefix(c_current_out_info, c_current_prefix);

			nstring_destroy(prefix);
			nstring_assign(prefix, &(ZI125));
		}
	
#line 1730 "tmp.c-parser.c"
		}
		/* END OF ACTION: x-set-prefix */
		ZR126 ();
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
#line 814 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_c_identifier();
		}
	
#line 1750 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-c-identifier */
		/* BEGINNING OF ACTION: skip-to-end-of-prefix */
		{
#line 928 "c-parser.act"

		while (CURRENT_TERMINAL != C_TOK_EOF
			&& CURRENT_TERMINAL != C_TOK_TERMINATOR
			&& CURRENT_TERMINAL != C_TOK_BLT_HMAPS
			&& CURRENT_TERMINAL != C_TOK_BLT_HTERMINALS
			&& CURRENT_TERMINAL != C_TOK_BLT_HASSIGNMENTS
			&& CURRENT_TERMINAL != C_TOK_BLT_HPARAM_HASSIGN
			&& CURRENT_TERMINAL != C_TOK_BLT_HRESULT_HASSIGN
			&& CURRENT_TERMINAL != C_TOK_BLT_HACTIONS
			&& CURRENT_TERMINAL != C_TOK_BLT_HTRAILER) {
			if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == C_TOK_CODE) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != C_TOK_EOF) {
			ADVANCE_LEXER;
		}

		c_propagating_error = TRUE;
	
#line 1784 "tmp.c-parser.c"
		}
		/* END OF ACTION: skip-to-end-of-prefix */
	    }
	  ZL3:;
	}
	/* END OF INLINE: 124 */
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
	/* BEGINNING OF INLINE: 199 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_BLT_HPREFIXES):
		{
		    ADVANCE_LEXER;
		    ZR119 ();
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
	/* END OF INLINE: 199 */
	/* BEGINNING OF INLINE: 200 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_BLT_HPERSISTENTS):
		{
		    ADVANCE_LEXER;
		    ZR136 ();
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
	/* END OF INLINE: 200 */
	/* BEGINNING OF INLINE: 201 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_BLT_HMAPS):
		{
		    ADVANCE_LEXER;
		    ZR127 ();
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
	/* END OF INLINE: 201 */
	/* BEGINNING OF INLINE: 202 */
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
#line 868 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_blt_header();
		}
	
#line 1881 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-blt-header */
	    }
	  ZL5:;
	}
	/* END OF INLINE: 202 */
	/* BEGINNING OF INLINE: 203 */
	{
	    {
		CCodeP ZI204;

		ZR111 (&ZI204);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL8;
		}
		/* BEGINNING OF ACTION: set-header1 */
		{
#line 339 "c-parser.act"

		c_code_check((ZI204), FALSE, FALSE, NULL, NULL, c_current_table);
		c_out_info_set_header1(c_current_out_info, (ZI204));
	
#line 1905 "tmp.c-parser.c"
		}
		/* END OF ACTION: set-header1 */
	    }
	    goto ZL7;
	  ZL8:;
	    {
		/* BEGINNING OF ACTION: expected-code */
		{
#line 862 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 1920 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
	    }
	  ZL7:;
	}
	/* END OF INLINE: 203 */
	ZR217 ();
	/* BEGINNING OF INLINE: 206 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI207;

		ZR111 (&ZI207);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL10;
		}
		/* BEGINNING OF ACTION: set-header2 */
		{
#line 344 "c-parser.act"

		c_code_check((ZI207), FALSE, FALSE, NULL, NULL, c_current_table);
		c_out_info_set_header2(c_current_out_info, (ZI207));
	
#line 1949 "tmp.c-parser.c"
		}
		/* END OF ACTION: set-header2 */
	    }
	    goto ZL9;
	  ZL10:;
	    {
		/* BEGINNING OF ACTION: expected-code */
		{
#line 862 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 1964 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
	    }
	  ZL9:;
	}
	/* END OF INLINE: 206 */
	ZR126 ();
	/* BEGINNING OF INLINE: 209 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_BLT_HASSIGNMENTS):
		{
		    ADVANCE_LEXER;
		    ZR161 ();
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
	/* END OF INLINE: 209 */
	/* BEGINNING OF INLINE: 210 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_BLT_HPARAM_HASSIGN):
		{
		    ADVANCE_LEXER;
		    ZR169 ();
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
	/* END OF INLINE: 210 */
	/* BEGINNING OF INLINE: 211 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_BLT_HRESULT_HASSIGN):
		{
		    ADVANCE_LEXER;
		    ZR176 ();
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
	/* END OF INLINE: 211 */
	/* BEGINNING OF INLINE: 212 */
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
#line 874 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_blt_terminals();
		}
	
#line 2051 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-blt-terminals */
	    }
	  ZL14:;
	}
	/* END OF INLINE: 212 */
	ZR183 ();
	/* BEGINNING OF INLINE: 213 */
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
#line 880 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_blt_actions();
		}
	
#line 2085 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-blt-actions */
	    }
	  ZL16:;
	}
	/* END OF INLINE: 213 */
	ZR190 ();
	/* BEGINNING OF INLINE: 214 */
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
#line 886 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_blt_trailer();
		}
	
#line 2119 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-blt-trailer */
	    }
	  ZL18:;
	}
	/* END OF INLINE: 214 */
	/* BEGINNING OF INLINE: 215 */
	{
	    {
		CCodeP ZI216;

		ZR111 (&ZI216);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL21;
		}
		/* BEGINNING OF ACTION: set-trailer1 */
		{
#line 729 "c-parser.act"

		c_code_check((ZI216), FALSE, FALSE, NULL, NULL, c_current_table);
		c_out_info_set_trailer1 (c_current_out_info, (ZI216));
	
#line 2143 "tmp.c-parser.c"
		}
		/* END OF ACTION: set-trailer1 */
	    }
	    goto ZL20;
	  ZL21:;
	    {
		/* BEGINNING OF ACTION: expected-code */
		{
#line 862 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 2158 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
	    }
	  ZL20:;
	}
	/* END OF INLINE: 215 */
	ZR217 ();
	/* BEGINNING OF INLINE: 218 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI219;

		ZR111 (&ZI219);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL23;
		}
		/* BEGINNING OF ACTION: set-trailer2 */
		{
#line 734 "c-parser.act"

		c_code_check((ZI219), FALSE, FALSE, NULL, NULL, c_current_table);
		c_out_info_set_trailer2(c_current_out_info, (ZI219));
	
#line 2187 "tmp.c-parser.c"
		}
		/* END OF ACTION: set-trailer2 */
	    }
	    goto ZL22;
	  ZL23:;
	    {
		/* BEGINNING OF ACTION: expected-code */
		{
#line 862 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 2202 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
	    }
	  ZL22:;
	}
	/* END OF INLINE: 218 */
	ZR126 ();
	/* BEGINNING OF INLINE: 221 */
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
#line 892 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_eof();
		}
	
#line 2236 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-eof */
	    }
	  ZL24:;
	}
	/* END OF INLINE: 221 */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: unhandled-syntax-error */
	{
#line 802 "c-parser.act"

		UNREACHED;
	
#line 2253 "tmp.c-parser.c"
	}
	/* END OF ACTION: unhandled-syntax-error */
    }
}

static void
ZR154(void)
{
    switch (CURRENT_TERMINAL) {
      case (C_TOK_C_HIDENTIFIER):
	{
	    ZR151 ();
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
ZR156(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 364 "c-parser.act"

		types_init(&c_current_type);
	
#line 2296 "tmp.c-parser.c"
	}
	/* END OF ACTION: init-tuple */
	/* BEGINNING OF INLINE: 158 */
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
#line 826 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_open_tuple();
		}
	
#line 2321 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-open-tuple */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 158 */
	ZR154 ();
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 1113 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 2339 "tmp.c-parser.c"
	}
	/* END OF ACTION: skip-recover */
	/* BEGINNING OF INLINE: 159 */
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
#line 832 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_close_tuple();
		}
	
#line 2364 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-close-tuple */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 159 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR138(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI125;
	NStringT ZI142;

	/* BEGINNING OF INLINE: 140 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case (C_TOK_C_HIDENTIFIER):
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI125, c_lexer_string_value(c_current_stream));
	
#line 2399 "tmp.c-parser.c"
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
#line 289 "c-parser.act"

		nstring_init(&(ZI125));
	
#line 2417 "tmp.c-parser.c"
		}
		/* END OF ACTION: empty-string */
		/* BEGINNING OF ACTION: expected-c-identifier */
		{
#line 814 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_c_identifier();
		}
	
#line 2428 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-c-identifier */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 140 */
	switch (CURRENT_TERMINAL) {
	  case (C_TOK_TYPEMARK):
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 141 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case (C_TOK_C_HIDENTIFIER):
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI142, c_lexer_string_value(c_current_stream));
	
#line 2453 "tmp.c-parser.c"
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
#line 289 "c-parser.act"

		nstring_init(&(ZI142));
	
#line 2471 "tmp.c-parser.c"
		}
		/* END OF ACTION: empty-string */
		/* BEGINNING OF ACTION: expected-identifier */
		{
#line 808 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_identifier();
		}
	
#line 2482 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-identifier */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 141 */
	/* BEGINNING OF ACTION: set-persistent */
	{
#line 276 "c-parser.act"

		if(persistent_list_find(c_out_info_persistents(c_current_out_info), (&ZI125)) == NULL) {
			PersistentT *p;

			p = persistent_create(&(ZI125), &(ZI142));
			persistent_list_append(c_out_info_persistents(c_current_out_info), p);
		} else {
			nstring_destroy(&(ZI125));
			nstring_destroy(&(ZI142));
			/* TODO error out E_c_persistent_variable_name_conflict((&ZI125))) ;*/
		}
	
#line 2504 "tmp.c-parser.c"
	}
	/* END OF ACTION: set-persistent */
	ZR126 ();
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
ZR178(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI107;

	/* BEGINNING OF INLINE: c-parse-grammar::identifier */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_C_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI107, c_lexer_string_value(c_current_stream));
	
#line 2539 "tmp.c-parser.c"
		    }
		    /* END OF EXTRACT: C-IDENTIFIER */
		    ADVANCE_LEXER;
		}
		break;
	      case (C_TOK_SID_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: SID-IDENTIFIER */
		    {
#line 200 "c-parser.act"

		nstring_assign(&ZI107, c_lexer_string_value(c_current_stream));
	
#line 2553 "tmp.c-parser.c"
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
#line 521 "c-parser.act"

		c_current_entry = table_get_type(c_current_table, (&ZI107));
		if (c_current_entry == NULL) {
			E_c_unknown_result_assign((&ZI107));
		} else if (type_get_result_assign_code(entry_get_type(c_current_entry))) {
			E_c_result_assign_mult_def((&ZI107));
			c_current_entry = NULL;
		}
		nstring_destroy(&(ZI107));
	
#line 2577 "tmp.c-parser.c"
	}
	/* END OF ACTION: rassign */
	ZR144 ();
	ZR123 ();
	/* BEGINNING OF INLINE: 181 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI167;

		ZR111 (&ZI167);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
		/* BEGINNING OF ACTION: x-rassign */
		{
#line 568 "c-parser.act"

		if (c_current_entry) {
			BoolT  errored = FALSE;
			KeyT  *key     = entry_key (c_current_entry);
			TypeTupleT tmp;

			types_init (&tmp);
			types_add_type_entry (&tmp, c_current_entry, FALSE);
			if (!types_disjoint_names(&c_saved_type)) {
				E_c_result_assign_param_clash(key, &c_saved_type);
				errored = TRUE;
			}

			if (!types_fillin_types(&c_saved_type, &tmp)) {
				E_c_res_assign_param_mismatch(key, &tmp, &c_saved_type);
				errored = TRUE;
			}

			if (!types_disjoint_names(&c_current_type)) {
				E_c_result_assign_result_clash(key, &c_current_type);
				errored = TRUE;
			}

			if (!types_fillin_types(&c_current_type, &tmp)) {
				E_c_res_assign_result_mismatch(key, &tmp, &c_current_type);
				errored = TRUE;
			}

			if (types_intersect(&c_saved_type, &c_current_type)) {
				E_c_result_assign_formal_clash(key, &c_saved_type, &c_current_type);
				errored = TRUE;
			}

			types_destroy (&tmp);
			if (errored) {
				types_destroy(&c_saved_type);
				types_destroy(&c_current_type);
				c_code_deallocate((ZI167));
				c_current_entry = NULL;
			} else {
				TypeT *type = entry_get_type(c_current_entry);

				c_code_check((ZI167), FALSE, FALSE, &c_saved_type,
					&c_current_type, c_current_table);
				type_set_result_assign_code (type,  (ZI167));
			}
		} else {
			types_destroy(&c_saved_type);
			types_destroy(&c_current_type);
			c_code_deallocate((ZI167));
		}
	
#line 2651 "tmp.c-parser.c"
		}
		/* END OF ACTION: x-rassign */
		ZR126 ();
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
#line 862 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 2671 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
		/* BEGINNING OF ACTION: skip-to-end-of-result-assign */
		{
#line 1039 "c-parser.act"

		while (CURRENT_TERMINAL != C_TOK_EOF
			&& CURRENT_TERMINAL != C_TOK_TERMINATOR
			&& CURRENT_TERMINAL != C_TOK_BLT_HTERMINALS
			&& CURRENT_TERMINAL != C_TOK_BLT_HACTIONS
			&& CURRENT_TERMINAL != C_TOK_BLT_HTRAILER) {
			if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == C_TOK_CODE) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != C_TOK_EOF) {
			ADVANCE_LEXER;
		}

		c_propagating_error = TRUE;
	
#line 2701 "tmp.c-parser.c"
		}
		/* END OF ACTION: skip-to-end-of-result-assign */
	    }
	  ZL3:;
	}
	/* END OF INLINE: 181 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR217(void)
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
#line 820 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_separator();
		}
	
#line 2741 "tmp.c-parser.c"
	}
	/* END OF ACTION: expected-separator */
    }
}

static void
ZR146(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI125;

	switch (CURRENT_TERMINAL) {
	  case (C_TOK_C_HIDENTIFIER):
	    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
	    {
#line 196 "c-parser.act"

		nstring_assign(&ZI125, c_lexer_string_value(c_current_stream));
	
#line 2764 "tmp.c-parser.c"
	    }
	    /* END OF EXTRACT: C-IDENTIFIER */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 148 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_TYPEMARK):
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: 149 */
		    {
			{
			    NStringT ZI142;

			    /* BEGINNING OF INLINE: c-parse-grammar::identifier */
			    {
				switch (CURRENT_TERMINAL) {
				  case (C_TOK_C_HIDENTIFIER):
				    {
					/* BEGINNING OF EXTRACT: C-IDENTIFIER */
					{
#line 196 "c-parser.act"

		nstring_assign(&ZI142, c_lexer_string_value(c_current_stream));
	
#line 2794 "tmp.c-parser.c"
					}
					/* END OF EXTRACT: C-IDENTIFIER */
					ADVANCE_LEXER;
				    }
				    break;
				  case (C_TOK_SID_HIDENTIFIER):
				    {
					/* BEGINNING OF EXTRACT: SID-IDENTIFIER */
					{
#line 200 "c-parser.act"

		nstring_assign(&ZI142, c_lexer_string_value(c_current_stream));
	
#line 2808 "tmp.c-parser.c"
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
			    /* BEGINNING OF INLINE: 150 */
			    {
				switch (CURRENT_TERMINAL) {
				  case (C_TOK_REFERENCE):
				    {
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: tuple-ref-type */
					{
#line 375 "c-parser.act"

		if (!types_add_typed_name(&c_current_type, c_current_table, &(ZI125),
			(&ZI142), TRUE)) {
			E_c_unknown_type((&ZI142));
		}
		nstring_destroy(&(ZI142));
	
#line 2835 "tmp.c-parser.c"
					}
					/* END OF ACTION: tuple-ref-type */
				    }
				    break;
				  default:
				    {
					/* BEGINNING OF ACTION: tuple-type */
					{
#line 367 "c-parser.act"

		if (!types_add_typed_name(&c_current_type, c_current_table, &(ZI125),
			(&ZI142), FALSE)) {
			E_c_unknown_type((&ZI142));
		}
		nstring_destroy(&(ZI142));
	
#line 2852 "tmp.c-parser.c"
					}
					/* END OF ACTION: tuple-type */
				    }
				    break;
				}
			    }
			    /* END OF INLINE: 150 */
			}
			goto ZL3;
		      ZL4:;
			{
			    /* BEGINNING OF ACTION: expected-identifier */
			    {
#line 808 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_identifier();
		}
	
#line 2872 "tmp.c-parser.c"
			    }
			    /* END OF ACTION: expected-identifier */
			    /* BEGINNING OF ACTION: destroy-string */
			    {
#line 895 "c-parser.act"

		nstring_destroy(&(ZI125));
	
#line 2881 "tmp.c-parser.c"
			    }
			    /* END OF ACTION: destroy-string */
			    /* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
			    {
#line 899 "c-parser.act"

		while (CURRENT_TERMINAL != C_TOK_EOF
			&& CURRENT_TERMINAL != C_TOK_DEFINE
			&& CURRENT_TERMINAL != C_TOK_CODE
			&& CURRENT_TERMINAL != C_TOK_SEPARATOR
			&& CURRENT_TERMINAL != C_TOK_CLOSE_HTUPLE
			&& CURRENT_TERMINAL != C_TOK_TERMINATOR
			&& CURRENT_TERMINAL != C_TOK_BLT_HPARAM_HASSIGN
			&& CURRENT_TERMINAL != C_TOK_BLT_HRESULT_HASSIGN
			&& CURRENT_TERMINAL != C_TOK_BLT_HTERMINALS
			&& CURRENT_TERMINAL != C_TOK_BLT_HACTIONS
			&& CURRENT_TERMINAL != C_TOK_BLT_HTRAILER) {
			if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != C_TOK_EOF) {
			ADVANCE_LEXER;
		}

		c_propagating_error = TRUE;
	
#line 2915 "tmp.c-parser.c"
			    }
			    /* END OF ACTION: skip-to-end-of-tuple-defn */
			}
		      ZL3:;
		    }
		    /* END OF INLINE: 149 */
		}
		break;
	      default:
		{
		    /* BEGINNING OF ACTION: tuple-name */
		    {
#line 383 "c-parser.act"

		types_add_name(&c_current_type, c_current_table, &(ZI125), FALSE);
	
#line 2932 "tmp.c-parser.c"
		    }
		    /* END OF ACTION: tuple-name */
		}
		break;
	    }
	}
	/* END OF INLINE: 148 */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-identifier */
	{
#line 808 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_identifier();
		}
	
#line 2952 "tmp.c-parser.c"
	}
	/* END OF ACTION: expected-identifier */
	/* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
	{
#line 899 "c-parser.act"

		while (CURRENT_TERMINAL != C_TOK_EOF
			&& CURRENT_TERMINAL != C_TOK_DEFINE
			&& CURRENT_TERMINAL != C_TOK_CODE
			&& CURRENT_TERMINAL != C_TOK_SEPARATOR
			&& CURRENT_TERMINAL != C_TOK_CLOSE_HTUPLE
			&& CURRENT_TERMINAL != C_TOK_TERMINATOR
			&& CURRENT_TERMINAL != C_TOK_BLT_HPARAM_HASSIGN
			&& CURRENT_TERMINAL != C_TOK_BLT_HRESULT_HASSIGN
			&& CURRENT_TERMINAL != C_TOK_BLT_HTERMINALS
			&& CURRENT_TERMINAL != C_TOK_BLT_HACTIONS
			&& CURRENT_TERMINAL != C_TOK_BLT_HTRAILER) {
			if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != C_TOK_EOF) {
			ADVANCE_LEXER;
		}

		c_propagating_error = TRUE;
	
#line 2986 "tmp.c-parser.c"
	}
	/* END OF ACTION: skip-to-end-of-tuple-defn */
    }
}

static void
ZR185(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI107;

	/* BEGINNING OF INLINE: c-parse-grammar::identifier */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_C_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI107, c_lexer_string_value(c_current_stream));
	
#line 3012 "tmp.c-parser.c"
		    }
		    /* END OF EXTRACT: C-IDENTIFIER */
		    ADVANCE_LEXER;
		}
		break;
	      case (C_TOK_SID_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: SID-IDENTIFIER */
		    {
#line 200 "c-parser.act"

		nstring_assign(&ZI107, c_lexer_string_value(c_current_stream));
	
#line 3026 "tmp.c-parser.c"
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
#line 590 "c-parser.act"

		c_current_entry = table_get_basic(c_current_table, (&ZI107));
		if (c_current_entry == NULL) {
			E_c_unknown_basic((&ZI107));
		} else {
			BasicT * basic = entry_get_basic(c_current_entry);

			if (basic_get_result_code(basic)) {
				E_c_basic_mult_def((&ZI107));
				c_current_entry = NULL;
			} else if (types_equal_zero_tuple(basic_result (basic))) {
				E_c_basic_has_no_result((&ZI107));
				c_current_entry = NULL;
			}
		}
		nstring_destroy(&(ZI107));
	
#line 3057 "tmp.c-parser.c"
	}
	/* END OF ACTION: set-terminal */
	ZR144 ();
	ZR123 ();
	/* BEGINNING OF INLINE: 188 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI167;

		ZR111 (&ZI167);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
		/* BEGINNING OF ACTION: x-set-terminal */
		{
#line 643 "c-parser.act"

		if (c_current_entry) {
			BasicT     *basic   = entry_get_basic(c_current_entry);
			TypeTupleT *result  = basic_result(basic);
			BoolT       errored = FALSE;
			KeyT       *key     = entry_key(c_current_entry);

			if (!types_disjoint_names(&c_saved_type)) {
				E_c_basic_param_clash(key, &c_saved_type);
				errored = TRUE;
			}

			if (!types_equal_zero_tuple(&c_saved_type)) {
				E_c_basic_param_mismatch(key, &c_saved_type);
				errored = TRUE;
			}

			if (!types_disjoint_names(&c_current_type)) {
				E_c_basic_result_clash(key, &c_current_type);
				errored = TRUE;
			}

			if (!types_fillin_types(&c_current_type, result)) {
				E_c_basic_result_mismatch(key, result, &c_current_type);
				errored = TRUE;
			}

			if (types_intersect(&c_saved_type, &c_current_type)) {
				E_c_basic_formal_clash(key, &c_saved_type, &c_current_type);
				errored = TRUE;
			}

			if (errored) {
				types_destroy(&c_saved_type);
				types_destroy(&c_current_type);
				c_code_deallocate((ZI167));
				c_current_entry = NULL;
			} else {
				types_destroy(&c_saved_type);
				c_code_check((ZI167), FALSE, FALSE, NULL, &c_current_type, c_current_table);
				basic_set_result_code(basic,  (ZI167));
			}
		} else {
			types_destroy(&c_saved_type);
			types_destroy(&c_current_type);
			c_code_deallocate((ZI167));
		}
	
#line 3127 "tmp.c-parser.c"
		}
		/* END OF ACTION: x-set-terminal */
		ZR126 ();
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
#line 862 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 3147 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
		/* BEGINNING OF ACTION: skip-to-end-of-terminal */
		{
#line 1064 "c-parser.act"

		while (CURRENT_TERMINAL != C_TOK_EOF
			&& CURRENT_TERMINAL != C_TOK_TERMINATOR
			&& CURRENT_TERMINAL != C_TOK_BLT_HACTIONS
			&& CURRENT_TERMINAL != C_TOK_BLT_HTRAILER) {
			if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
				nstring_destroy(c_lexer_string_value(c_current_stream));
			} else if (CURRENT_TERMINAL == C_TOK_CODE) {
				c_code_deallocate(c_lexer_code_value(c_current_stream));
			}
			ADVANCE_LEXER;
		}

		if (CURRENT_TERMINAL == C_TOK_SID_HIDENTIFIER || CURRENT_TERMINAL == C_TOK_C_HIDENTIFIER) {
			nstring_destroy(c_lexer_string_value(c_current_stream));
		}

		if (CURRENT_TERMINAL != C_TOK_EOF) {
			ADVANCE_LEXER;
		}

		c_propagating_error = TRUE;
	
#line 3176 "tmp.c-parser.c"
		}
		/* END OF ACTION: skip-to-end-of-terminal */
	    }
	  ZL3:;
	}
	/* END OF INLINE: 188 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR127(void)
{
  ZL2_127:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
	{
	    ZR129 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 1113 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 3208 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: skip-recover */
	    /* BEGINNING OF INLINE: c-parse-grammar::map-list */
	    goto ZL2_127;
	    /* END OF INLINE: c-parse-grammar::map-list */
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
ZR144(void)
{
    switch (CURRENT_TERMINAL) {
      case (C_TOK_TYPEMARK):
	{
	    ADVANCE_LEXER;
	    ZR156 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 355 "c-parser.act"

		types_assign(&c_saved_type, &c_current_type);
	
#line 3245 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR160 ();
	    ZR156 ();
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
#line 360 "c-parser.act"

		types_init(&c_saved_type);
		types_init(&c_current_type);
	
#line 3265 "tmp.c-parser.c"
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
ZR161(void)
{
  ZL2_161:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
	{
	    ZR163 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 1113 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 3297 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: skip-recover */
	    /* BEGINNING OF INLINE: c-parse-grammar::assignment-list */
	    goto ZL2_161;
	    /* END OF INLINE: c-parse-grammar::assignment-list */
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
ZR169(void)
{
  ZL2_169:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
	{
	    ZR171 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 1113 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 3334 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: skip-recover */
	    /* BEGINNING OF INLINE: c-parse-grammar::param-assign-list */
	    goto ZL2_169;
	    /* END OF INLINE: c-parse-grammar::param-assign-list */
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
ZR123(void)
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
#line 856 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_define();
		}
	
#line 3379 "tmp.c-parser.c"
	}
	/* END OF ACTION: expected-define */
    }
}

static void
ZR126(void)
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
#line 844 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_terminator();
		}
	
#line 3411 "tmp.c-parser.c"
	}
	/* END OF ACTION: expected-terminator */
    }
}

/* BEGINNING OF TRAILER */

#line 1123 "c-parser.act"


#line 3422 "tmp.c-parser.c"

/* END OF FILE */
