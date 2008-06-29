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

static void ZR134(void);
static void ZR174(void);
static void ZR115(CCodeP);
static void ZR181(void);
static void ZR109(CCodeP *);
static void ZR158(void);
static void ZR127(void);
static void ZR161(void);
static void ZR190(void);
static void ZR149(void);
static void ZR188(void);
static void ZR169(void);
static void ZR117(void);
static void ZR111(CCodeP);
static void ZR119(void);
extern void c_parse_grammar(void);
static void ZR152(void);
static void ZR154(void);
static void ZR136(void);
static void ZR215(void);
static void ZR176(void);
static void ZR144(void);
static void ZR183(void);
static void ZR125(void);
static void ZR142(void);
static void ZR159(void);
static void ZR167(void);
static void ZR121(void);
static void ZR124(void);

/* BEGINNING OF STATIC VARIABLES */

static BoolT ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZR134(void)
{
  ZL2_134:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_C_HIDENTIFIER):
	{
	    ZR136 ();
	    /* BEGINNING OF INLINE: c-parse-grammar::persistent-list */
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_134;
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
ZR174(void)
{
  ZL2_174:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
	{
	    ZR176 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 1105 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 201 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: skip-recover */
	    /* BEGINNING OF INLINE: c-parse-grammar::result-assign-list */
	    goto ZL2_174;
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
ZR115(CCodeP ZI108)
{
  ZL2_115:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_ACT_HAT): case (C_TOK_ACT_HEXCEPTION): case (C_TOK_ACT_HTERMINAL): case (C_TOK_ACT_HADVANCE):
      case (C_TOK_ACT_HLABEL): case (C_TOK_ACT_HREFERENCE): case (C_TOK_ACT_HIDENTIFIER): case (C_TOK_ACT_HMODIFIABLE):
      case (C_TOK_ACT_HCODESTRING): case (C_TOK_ACT_HEOF):
	{
	    ZR111 (ZI108);
	    /* BEGINNING OF INLINE: c-parse-grammar::code-block::code-body */
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_115;
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
ZR181(void)
{
  ZL2_181:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
	{
	    ZR183 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 1105 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 269 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: skip-recover */
	    /* BEGINNING OF INLINE: c-parse-grammar::terminal-list */
	    goto ZL2_181;
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
ZR109(CCodeP *ZO108)
{
    CCodeP ZI108;

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
#line 740 "c-parser.act"

		(ZI108) = c_code_create(istream_name(&(c_lexer_stream->istream)), 
			istream_line(&(c_lexer_stream->istream)));
	
#line 311 "tmp.c-parser.c"
	}
	/* END OF ACTION: ccode-init */
	ZR115 (ZI108);
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
    *ZO108 = ZI108;
}

static void
ZR158(void)
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
#line 830 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_arrow();
		}
	
#line 360 "tmp.c-parser.c"
	}
	/* END OF ACTION: expected-arrow */
    }
}

static void
ZR127(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI129;

	/* BEGINNING OF INLINE: c-parse-grammar::identifier */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_C_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI129, c_lexer_string_value(c_current_stream));
	
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

		nstring_assign(&ZI129, c_lexer_string_value(c_current_stream));
	
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
#line 294 "c-parser.act"

		c_current_entry = table_get_entry(c_current_table, (&ZI129));
		if (c_current_entry == NULL) {
			E_c_unknown_identifier((&ZI129));
		} else if (entry_get_mapping(c_current_entry)) {
			E_c_remapped_identifier((&ZI129));
			c_current_entry = NULL;
		} else {
			switch (entry_type(c_current_entry)) EXHAUSTIVE {
			case ET_NAME:
			case ET_ACTION:
			case ET_NON_LOCAL:
				E_c_illegal_map((&ZI129));
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
		nstring_destroy(&(ZI129));
	
#line 441 "tmp.c-parser.c"
	}
	/* END OF ACTION: set-map */
	ZR158 ();
	/* BEGINNING OF INLINE: 131 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		NStringT ZI132;

		switch (CURRENT_TERMINAL) {
		  case (C_TOK_C_HIDENTIFIER):
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI132, c_lexer_string_value(c_current_stream));
	
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
#line 323 "c-parser.act"

		if (c_current_entry) {
			entry_set_mapping(c_current_entry, &(ZI132));
		} else {
			nstring_destroy(&(ZI132));
		}
	
#line 480 "tmp.c-parser.c"
		}
		/* END OF ACTION: x-set-map */
		ZR124 ();
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
#line 806 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_c_identifier();
		}
	
#line 500 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-c-identifier */
		/* BEGINNING OF ACTION: skip-to-end-of-map */
		{
#line 949 "c-parser.act"

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
	/* END OF INLINE: 131 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR161(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI105;

	/* BEGINNING OF INLINE: c-parse-grammar::identifier */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_C_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI105, c_lexer_string_value(c_current_stream));
	
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

		nstring_assign(&ZI105, c_lexer_string_value(c_current_stream));
	
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
#line 388 "c-parser.act"

		c_current_entry = table_get_type(c_current_table, (&ZI105));
		if (c_current_entry == NULL) {
			E_c_unknown_assign((&ZI105));
		} else if (type_get_assign_code(entry_get_type(c_current_entry))) {
			E_c_assign_mult_def((&ZI105));
			c_current_entry = NULL;
		}
		nstring_destroy(&(ZI105));
	
#line 605 "tmp.c-parser.c"
	}
	/* END OF ACTION: assign */
	ZR142 ();
	ZR121 ();
	/* BEGINNING OF INLINE: 164 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI165;

		ZR109 (&ZI165);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
		/* BEGINNING OF ACTION: x-assign */
		{
#line 436 "c-parser.act"

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
				c_code_deallocate((ZI165));
				c_current_entry = NULL;
			} else {
			TypeT *type;

				type = entry_get_type (c_current_entry);
				c_code_check((ZI165), FALSE, FALSE, &c_saved_type, &c_current_type, c_current_table);
				type_set_assign_code(type,  (ZI165));
			}
		} else {
			types_destroy(&c_saved_type);
			types_destroy(&c_current_type);
			c_code_deallocate((ZI165));
		}
	
#line 680 "tmp.c-parser.c"
		}
		/* END OF ACTION: x-assign */
		ZR124 ();
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
#line 854 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 700 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
		/* BEGINNING OF ACTION: skip-to-end-of-assignment */
		{
#line 977 "c-parser.act"

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
	/* END OF INLINE: 164 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR190(void)
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
	/* BEGINNING OF INLINE: 192 */
	{
	    {
		NStringT ZI105;

		/* BEGINNING OF INLINE: c-parse-grammar::identifier */
		{
		    switch (CURRENT_TERMINAL) {
		      case (C_TOK_C_HIDENTIFIER):
			{
			    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
			    {
#line 196 "c-parser.act"

		nstring_assign(&ZI105, c_lexer_string_value(c_current_stream));
	
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

		nstring_assign(&ZI105, c_lexer_string_value(c_current_stream));
	
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
#line 659 "c-parser.act"

		c_current_entry = table_get_action(c_current_table, (&ZI105));
		if (c_current_entry == NULL) {
			E_c_unknown_action((&ZI105));
		} else {
			ActionT *action;

			action = entry_get_action(c_current_entry);
			if (action_get_code(action)) {
				E_c_action_mult_def((&ZI105));
				c_current_entry = NULL;
			}
		}
		nstring_destroy(&(ZI105));
	
#line 819 "tmp.c-parser.c"
		}
		/* END OF ACTION: set-action */
		/* BEGINNING OF INLINE: 193 */
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
#line 842 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_end_action();
		}
	
#line 844 "tmp.c-parser.c"
			}
			/* END OF ACTION: expected-end-action */
		    }
		  ZL5:;
		}
		/* END OF INLINE: 193 */
		ZR142 ();
		ZR121 ();
		/* BEGINNING OF INLINE: 195 */
		{
		    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		    {
			CCodeP ZI165;

			ZR109 (&ZI165);
			if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
			    RESTORE_LEXER;
			    goto ZL8;
			}
			/* BEGINNING OF ACTION: x-set-action */
			{
#line 710 "c-parser.act"

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
				c_code_deallocate((ZI165));
				c_current_entry = NULL;
			} else {
				c_code_check((ZI165), TRUE, FALSE, &c_saved_type, &c_current_type, c_current_table);
				types_propogate_mutations(param, &c_saved_type);
				action_set_code(action,  (ZI165));
			}
		} else {
			types_destroy(&c_saved_type);
			types_destroy(&c_current_type);
			c_code_deallocate((ZI165));
		}
	
#line 919 "tmp.c-parser.c"
			}
			/* END OF ACTION: x-set-action */
			ZR124 ();
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
#line 854 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 939 "tmp.c-parser.c"
			}
			/* END OF ACTION: expected-code */
			/* BEGINNING OF ACTION: skip-to-end-of-action */
			{
#line 1080 "c-parser.act"

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
		/* END OF INLINE: 195 */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: expected-identifier */
		{
#line 800 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_identifier();
		}
	
#line 987 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-identifier */
		/* BEGINNING OF ACTION: skip-to-end-of-action */
		{
#line 1080 "c-parser.act"

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
	/* END OF INLINE: 192 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR149(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
  ZL2_149:;
    {
	ZR144 ();
	/* BEGINNING OF INLINE: 151 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-close-tuple-or-skipped-or-eof */
		{
#line 1108 "c-parser.act"

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
		    goto ZL2_149;
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
#line 812 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_separator();
		}
	
#line 1086 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-separator */
		/* BEGINNING OF INLINE: c-parse-grammar::function-type-defn::tuple-defn-list-1 */
		goto ZL2_149;
		/* END OF INLINE: c-parse-grammar::function-type-defn::tuple-defn-list-1 */
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
	/* END OF INLINE: 151 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR188(void)
{
  ZL2_188:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_BEGIN_HACTION):
	{
	    ZR190 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 1105 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 1122 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: skip-recover */
	    /* BEGINNING OF INLINE: c-parse-grammar::action-list */
	    goto ZL2_188;
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
ZR169(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI105;

	/* BEGINNING OF INLINE: c-parse-grammar::identifier */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_C_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI105, c_lexer_string_value(c_current_stream));
	
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

		nstring_assign(&ZI105, c_lexer_string_value(c_current_stream));
	
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
#line 453 "c-parser.act"

		c_current_entry = table_get_type(c_current_table, (&ZI105));
		if (c_current_entry == NULL) {
			E_c_unknown_param_assign((&ZI105));
		} else if (type_get_param_assign_code(entry_get_type(c_current_entry))) {
			E_c_param_assign_mult_def((&ZI105));
			c_current_entry = NULL;
		}
		nstring_destroy(&(ZI105));
	
#line 1199 "tmp.c-parser.c"
	}
	/* END OF ACTION: passign */
	ZR142 ();
	ZR121 ();
	/* BEGINNING OF INLINE: 172 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI165;

		ZR109 (&ZI165);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
		/* BEGINNING OF ACTION: x-passign */
		{
#line 500 "c-parser.act"

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
				c_code_deallocate((ZI165));
				c_current_entry = NULL;
			} else {
				TypeT *type = entry_get_type(c_current_entry);

				c_code_check((ZI165), FALSE, TRUE, &c_saved_type,
					&c_current_type, c_current_table);
				type_set_param_assign_code(type,  (ZI165));
			}
		} else {
			types_destroy(&c_saved_type);
			types_destroy(&c_current_type);
			c_code_deallocate((ZI165));
		}
	
#line 1273 "tmp.c-parser.c"
		}
		/* END OF ACTION: x-passign */
		ZR124 ();
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
#line 854 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 1293 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
		/* BEGINNING OF ACTION: skip-to-end-of-param-assign */
		{
#line 1004 "c-parser.act"

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
	/* END OF INLINE: 172 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR117(void)
{
  ZL2_117:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
	{
	    ZR119 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 1105 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 1357 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: skip-recover */
	    /* BEGINNING OF INLINE: c-parse-grammar::prefix-list */
	    goto ZL2_117;
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
ZR111(CCodeP ZI108)
{
    switch (CURRENT_TERMINAL) {
      case (C_TOK_ACT_HADVANCE):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-advance */
	    {
#line 759 "c-parser.act"

		c_code_append_advance((ZI108));
	
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
#line 746 "c-parser.act"

		NStringT ns;
		nstring_copy_cstring(&ns, "@");	/* TODO append '@' to code buffer? */
		c_code_append_string((ZI108), &ns);	/* TODO really append_label()? */
	
#line 1405 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: append-ccode-at */
	}
	break;
      case (C_TOK_ACT_HCODESTRING):
	{
	    NStringT ZI114;

	    /* BEGINNING OF EXTRACT: ACT-CODESTRING */
	    {
#line 224 "c-parser.act"

		nstring_assign(&ZI114, c_lexer_string_value(c_current_stream));
	
#line 1420 "tmp.c-parser.c"
	    }
	    /* END OF EXTRACT: ACT-CODESTRING */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-codestring */
	    {
#line 779 "c-parser.act"

		assert(!nstring_contains(&(ZI114), '@'));	/* XXX '@'? */
		c_code_append_string((ZI108), &(ZI114));
	
#line 1431 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: append-ccode-codestring */
	}
	break;
      case (C_TOK_ACT_HEOF):
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: E-eof-in-code-block */
	    {
#line 785 "c-parser.act"

		E_c_eof_in_code(&c_lexer_stream->istream);
	
#line 1445 "tmp.c-parser.c"
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

		c_code_append_exception((ZI108));
	
#line 1459 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: append-ccode-exception */
	}
	break;
      case (C_TOK_ACT_HIDENTIFIER):
	{
	    NStringT ZI113;

	    /* BEGINNING OF EXTRACT: ACT-IDENTIFIER */
	    {
#line 216 "c-parser.act"

		nstring_assign(&ZI113, c_lexer_string_value(c_current_stream));
	
#line 1474 "tmp.c-parser.c"
	    }
	    /* END OF EXTRACT: ACT-IDENTIFIER */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-identifier */
	    {
#line 771 "c-parser.act"

		c_code_append_identifier((ZI108), &(ZI113));
	
#line 1484 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: append-ccode-identifier */
	}
	break;
      case (C_TOK_ACT_HLABEL):
	{
	    NStringT ZI113;

	    /* BEGINNING OF EXTRACT: ACT-LABEL */
	    {
#line 208 "c-parser.act"

		nstring_assign(&ZI113, c_lexer_string_value(c_current_stream));
	
#line 1499 "tmp.c-parser.c"
	    }
	    /* END OF EXTRACT: ACT-LABEL */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-label */
	    {
#line 763 "c-parser.act"

		c_code_append_label((ZI108), &(ZI113));
	
#line 1509 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: append-ccode-label */
	}
	break;
      case (C_TOK_ACT_HMODIFIABLE):
	{
	    NStringT ZI113;

	    /* BEGINNING OF EXTRACT: ACT-MODIFIABLE */
	    {
#line 220 "c-parser.act"

		nstring_assign(&ZI113, c_lexer_string_value(c_current_stream));
	
#line 1524 "tmp.c-parser.c"
	    }
	    /* END OF EXTRACT: ACT-MODIFIABLE */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-modifiable */
	    {
#line 775 "c-parser.act"

		c_code_append_modifiable((ZI108), &(ZI113));
	
#line 1534 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: append-ccode-modifiable */
	}
	break;
      case (C_TOK_ACT_HREFERENCE):
	{
	    NStringT ZI113;

	    /* BEGINNING OF EXTRACT: ACT-REFERENCE */
	    {
#line 212 "c-parser.act"

		nstring_assign(&ZI113, c_lexer_string_value(c_current_stream));
	
#line 1549 "tmp.c-parser.c"
	    }
	    /* END OF EXTRACT: ACT-REFERENCE */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-reference */
	    {
#line 767 "c-parser.act"

		c_code_append_reference((ZI108), &(ZI113));
	
#line 1559 "tmp.c-parser.c"
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

		c_code_append_terminal((ZI108));
	
#line 1573 "tmp.c-parser.c"
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
ZR119(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI120;

	/* BEGINNING OF INLINE: c-parse-grammar::identifier */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_C_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI120, c_lexer_string_value(c_current_stream));
	
#line 1609 "tmp.c-parser.c"
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

		nstring_assign(&ZI120, c_lexer_string_value(c_current_stream));
	
#line 1623 "tmp.c-parser.c"
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
#line 248 "c-parser.act"

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
			if (nstring_ci_equal((&ZI120), &c_prefix_names[prefix])) {
				break;
			}
		}

		c_current_prefix = (CPrefixT) prefix;
		if (c_current_prefix == CPFX_NUM_PREFIXES) {
			E_c_unknown_prefix((&ZI120));
		}
		nstring_destroy(&(ZI120));
	
#line 1663 "tmp.c-parser.c"
	}
	/* END OF ACTION: set-prefix */
	ZR121 ();
	/* BEGINNING OF INLINE: 122 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		NStringT ZI123;

		switch (CURRENT_TERMINAL) {
		  case (C_TOK_C_HIDENTIFIER):
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI123, c_lexer_string_value(c_current_stream));
	
#line 1684 "tmp.c-parser.c"
		    }
		    /* END OF EXTRACT: C-IDENTIFIER */
		    break;
		  default:
		    goto ZL4;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: x-set-prefix */
		{
#line 262 "c-parser.act"

		if (c_current_prefix == CPFX_NUM_PREFIXES) {
			nstring_destroy(&(ZI123));
		} else {
			NStringT *prefix = c_out_info_prefix(c_current_out_info, c_current_prefix);

			nstring_destroy(prefix);
			nstring_assign(prefix, &(ZI123));
		}
	
#line 1705 "tmp.c-parser.c"
		}
		/* END OF ACTION: x-set-prefix */
		ZR124 ();
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
#line 806 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_c_identifier();
		}
	
#line 1725 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-c-identifier */
		/* BEGINNING OF ACTION: skip-to-end-of-prefix */
		{
#line 920 "c-parser.act"

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
	
#line 1759 "tmp.c-parser.c"
		}
		/* END OF ACTION: skip-to-end-of-prefix */
	    }
	  ZL3:;
	}
	/* END OF INLINE: 122 */
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
	/* BEGINNING OF INLINE: 197 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_BLT_HPREFIXES):
		{
		    ADVANCE_LEXER;
		    ZR117 ();
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
	/* END OF INLINE: 197 */
	/* BEGINNING OF INLINE: 198 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_BLT_HPERSISTENTS):
		{
		    ADVANCE_LEXER;
		    ZR134 ();
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
	/* END OF INLINE: 198 */
	/* BEGINNING OF INLINE: 199 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_BLT_HMAPS):
		{
		    ADVANCE_LEXER;
		    ZR125 ();
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
#line 860 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_blt_header();
		}
	
#line 1856 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-blt-header */
	    }
	  ZL5:;
	}
	/* END OF INLINE: 200 */
	/* BEGINNING OF INLINE: 201 */
	{
	    {
		CCodeP ZI202;

		ZR109 (&ZI202);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL8;
		}
		/* BEGINNING OF ACTION: set-header1 */
		{
#line 335 "c-parser.act"

		c_code_check((ZI202), FALSE, FALSE, NULL, NULL, c_current_table);
		c_out_info_set_header1(c_current_out_info, (ZI202));
	
#line 1880 "tmp.c-parser.c"
		}
		/* END OF ACTION: set-header1 */
	    }
	    goto ZL7;
	  ZL8:;
	    {
		/* BEGINNING OF ACTION: expected-code */
		{
#line 854 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 1895 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
	    }
	  ZL7:;
	}
	/* END OF INLINE: 201 */
	ZR215 ();
	/* BEGINNING OF INLINE: 204 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI205;

		ZR109 (&ZI205);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL10;
		}
		/* BEGINNING OF ACTION: set-header2 */
		{
#line 340 "c-parser.act"

		c_code_check((ZI205), FALSE, FALSE, NULL, NULL, c_current_table);
		c_out_info_set_header2(c_current_out_info, (ZI205));
	
#line 1924 "tmp.c-parser.c"
		}
		/* END OF ACTION: set-header2 */
	    }
	    goto ZL9;
	  ZL10:;
	    {
		/* BEGINNING OF ACTION: expected-code */
		{
#line 854 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 1939 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
	    }
	  ZL9:;
	}
	/* END OF INLINE: 204 */
	ZR124 ();
	/* BEGINNING OF INLINE: 207 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_BLT_HASSIGNMENTS):
		{
		    ADVANCE_LEXER;
		    ZR159 ();
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
	/* END OF INLINE: 207 */
	/* BEGINNING OF INLINE: 208 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_BLT_HPARAM_HASSIGN):
		{
		    ADVANCE_LEXER;
		    ZR167 ();
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
	/* END OF INLINE: 208 */
	/* BEGINNING OF INLINE: 209 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_BLT_HRESULT_HASSIGN):
		{
		    ADVANCE_LEXER;
		    ZR174 ();
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
	/* END OF INLINE: 209 */
	/* BEGINNING OF INLINE: 210 */
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
#line 866 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_blt_terminals();
		}
	
#line 2026 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-blt-terminals */
	    }
	  ZL14:;
	}
	/* END OF INLINE: 210 */
	ZR181 ();
	/* BEGINNING OF INLINE: 211 */
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
#line 872 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_blt_actions();
		}
	
#line 2060 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-blt-actions */
	    }
	  ZL16:;
	}
	/* END OF INLINE: 211 */
	ZR188 ();
	/* BEGINNING OF INLINE: 212 */
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
#line 878 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_blt_trailer();
		}
	
#line 2094 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-blt-trailer */
	    }
	  ZL18:;
	}
	/* END OF INLINE: 212 */
	/* BEGINNING OF INLINE: 213 */
	{
	    {
		CCodeP ZI214;

		ZR109 (&ZI214);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL21;
		}
		/* BEGINNING OF ACTION: set-trailer1 */
		{
#line 725 "c-parser.act"

		c_code_check((ZI214), FALSE, FALSE, NULL, NULL, c_current_table);
		c_out_info_set_trailer1 (c_current_out_info, (ZI214));
	
#line 2118 "tmp.c-parser.c"
		}
		/* END OF ACTION: set-trailer1 */
	    }
	    goto ZL20;
	  ZL21:;
	    {
		/* BEGINNING OF ACTION: expected-code */
		{
#line 854 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 2133 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
	    }
	  ZL20:;
	}
	/* END OF INLINE: 213 */
	ZR215 ();
	/* BEGINNING OF INLINE: 216 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI217;

		ZR109 (&ZI217);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL23;
		}
		/* BEGINNING OF ACTION: set-trailer2 */
		{
#line 730 "c-parser.act"

		c_code_check((ZI217), FALSE, FALSE, NULL, NULL, c_current_table);
		c_out_info_set_trailer2(c_current_out_info, (ZI217));
	
#line 2162 "tmp.c-parser.c"
		}
		/* END OF ACTION: set-trailer2 */
	    }
	    goto ZL22;
	  ZL23:;
	    {
		/* BEGINNING OF ACTION: expected-code */
		{
#line 854 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 2177 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
	    }
	  ZL22:;
	}
	/* END OF INLINE: 216 */
	ZR124 ();
	/* BEGINNING OF INLINE: 219 */
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
#line 884 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_eof();
		}
	
#line 2211 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-eof */
	    }
	  ZL24:;
	}
	/* END OF INLINE: 219 */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: unhandled-syntax-error */
	{
#line 794 "c-parser.act"

		UNREACHED;
	
#line 2228 "tmp.c-parser.c"
	}
	/* END OF ACTION: unhandled-syntax-error */
    }
}

static void
ZR152(void)
{
    switch (CURRENT_TERMINAL) {
      case (C_TOK_C_HIDENTIFIER):
	{
	    ZR149 ();
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
ZR154(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 360 "c-parser.act"

		types_init(&c_current_type);
	
#line 2271 "tmp.c-parser.c"
	}
	/* END OF ACTION: init-tuple */
	/* BEGINNING OF INLINE: 156 */
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
#line 818 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_open_tuple();
		}
	
#line 2296 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-open-tuple */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 156 */
	ZR152 ();
	if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: skip-recover */
	{
#line 1105 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 2314 "tmp.c-parser.c"
	}
	/* END OF ACTION: skip-recover */
	/* BEGINNING OF INLINE: 157 */
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
#line 824 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_close_tuple();
		}
	
#line 2339 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-close-tuple */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 157 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR136(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI123;
	NStringT ZI140;

	/* BEGINNING OF INLINE: 138 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case (C_TOK_C_HIDENTIFIER):
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI123, c_lexer_string_value(c_current_stream));
	
#line 2374 "tmp.c-parser.c"
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
#line 285 "c-parser.act"

		nstring_init(&(ZI123));
	
#line 2392 "tmp.c-parser.c"
		}
		/* END OF ACTION: empty-string */
		/* BEGINNING OF ACTION: expected-c-identifier */
		{
#line 806 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_c_identifier();
		}
	
#line 2403 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-c-identifier */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 138 */
	switch (CURRENT_TERMINAL) {
	  case (C_TOK_TYPEMARK):
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 139 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case (C_TOK_C_HIDENTIFIER):
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI140, c_lexer_string_value(c_current_stream));
	
#line 2428 "tmp.c-parser.c"
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
#line 285 "c-parser.act"

		nstring_init(&(ZI140));
	
#line 2446 "tmp.c-parser.c"
		}
		/* END OF ACTION: empty-string */
		/* BEGINNING OF ACTION: expected-identifier */
		{
#line 800 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_identifier();
		}
	
#line 2457 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-identifier */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 139 */
	/* BEGINNING OF ACTION: set-persistent */
	{
#line 272 "c-parser.act"

		if(persistent_list_find(c_out_info_persistents(c_current_out_info), (&ZI123)) == NULL) {
			PersistentT *p;

			p = persistent_create(&(ZI123), &(ZI140));
			persistent_list_append(c_out_info_persistents(c_current_out_info), p);
		} else {
			nstring_destroy(&(ZI123));
			nstring_destroy(&(ZI140));
			/* TODO error out E_c_persistent_variable_name_conflict((&ZI123))) ;*/
		}
	
#line 2479 "tmp.c-parser.c"
	}
	/* END OF ACTION: set-persistent */
	ZR124 ();
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
ZR215(void)
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
#line 812 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_separator();
		}
	
#line 2520 "tmp.c-parser.c"
	}
	/* END OF ACTION: expected-separator */
    }
}

static void
ZR176(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI105;

	/* BEGINNING OF INLINE: c-parse-grammar::identifier */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_C_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI105, c_lexer_string_value(c_current_stream));
	
#line 2546 "tmp.c-parser.c"
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

		nstring_assign(&ZI105, c_lexer_string_value(c_current_stream));
	
#line 2560 "tmp.c-parser.c"
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
#line 517 "c-parser.act"

		c_current_entry = table_get_type(c_current_table, (&ZI105));
		if (c_current_entry == NULL) {
			E_c_unknown_result_assign((&ZI105));
		} else if (type_get_result_assign_code(entry_get_type(c_current_entry))) {
			E_c_result_assign_mult_def((&ZI105));
			c_current_entry = NULL;
		}
		nstring_destroy(&(ZI105));
	
#line 2584 "tmp.c-parser.c"
	}
	/* END OF ACTION: rassign */
	ZR142 ();
	ZR121 ();
	/* BEGINNING OF INLINE: 179 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI165;

		ZR109 (&ZI165);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
		/* BEGINNING OF ACTION: x-rassign */
		{
#line 564 "c-parser.act"

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
				c_code_deallocate((ZI165));
				c_current_entry = NULL;
			} else {
				TypeT *type = entry_get_type(c_current_entry);

				c_code_check((ZI165), FALSE, FALSE, &c_saved_type,
					&c_current_type, c_current_table);
				type_set_result_assign_code (type,  (ZI165));
			}
		} else {
			types_destroy(&c_saved_type);
			types_destroy(&c_current_type);
			c_code_deallocate((ZI165));
		}
	
#line 2658 "tmp.c-parser.c"
		}
		/* END OF ACTION: x-rassign */
		ZR124 ();
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
#line 854 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 2678 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
		/* BEGINNING OF ACTION: skip-to-end-of-result-assign */
		{
#line 1031 "c-parser.act"

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
	
#line 2708 "tmp.c-parser.c"
		}
		/* END OF ACTION: skip-to-end-of-result-assign */
	    }
	  ZL3:;
	}
	/* END OF INLINE: 179 */
    }
    return;
  ZL1:;
    SAVE_LEXER ((ERROR_TERMINAL));
    return;
}

static void
ZR144(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI123;

	switch (CURRENT_TERMINAL) {
	  case (C_TOK_C_HIDENTIFIER):
	    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
	    {
#line 196 "c-parser.act"

		nstring_assign(&ZI123, c_lexer_string_value(c_current_stream));
	
#line 2739 "tmp.c-parser.c"
	    }
	    /* END OF EXTRACT: C-IDENTIFIER */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 146 */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_TYPEMARK):
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: 147 */
		    {
			{
			    NStringT ZI140;

			    /* BEGINNING OF INLINE: c-parse-grammar::identifier */
			    {
				switch (CURRENT_TERMINAL) {
				  case (C_TOK_C_HIDENTIFIER):
				    {
					/* BEGINNING OF EXTRACT: C-IDENTIFIER */
					{
#line 196 "c-parser.act"

		nstring_assign(&ZI140, c_lexer_string_value(c_current_stream));
	
#line 2769 "tmp.c-parser.c"
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

		nstring_assign(&ZI140, c_lexer_string_value(c_current_stream));
	
#line 2783 "tmp.c-parser.c"
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
			    /* BEGINNING OF INLINE: 148 */
			    {
				switch (CURRENT_TERMINAL) {
				  case (C_TOK_REFERENCE):
				    {
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: tuple-ref-type */
					{
#line 371 "c-parser.act"

		if (!types_add_typed_name(&c_current_type, c_current_table, &(ZI123),
			(&ZI140), TRUE)) {
			E_c_unknown_type((&ZI140));
		}
		nstring_destroy(&(ZI140));
	
#line 2810 "tmp.c-parser.c"
					}
					/* END OF ACTION: tuple-ref-type */
				    }
				    break;
				  default:
				    {
					/* BEGINNING OF ACTION: tuple-type */
					{
#line 363 "c-parser.act"

		if (!types_add_typed_name(&c_current_type, c_current_table, &(ZI123),
			(&ZI140), FALSE)) {
			E_c_unknown_type((&ZI140));
		}
		nstring_destroy(&(ZI140));
	
#line 2827 "tmp.c-parser.c"
					}
					/* END OF ACTION: tuple-type */
				    }
				    break;
				}
			    }
			    /* END OF INLINE: 148 */
			}
			goto ZL3;
		      ZL4:;
			{
			    /* BEGINNING OF ACTION: expected-identifier */
			    {
#line 800 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_identifier();
		}
	
#line 2847 "tmp.c-parser.c"
			    }
			    /* END OF ACTION: expected-identifier */
			    /* BEGINNING OF ACTION: destroy-string */
			    {
#line 887 "c-parser.act"

		nstring_destroy(&(ZI123));
	
#line 2856 "tmp.c-parser.c"
			    }
			    /* END OF ACTION: destroy-string */
			    /* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
			    {
#line 891 "c-parser.act"

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
	
#line 2890 "tmp.c-parser.c"
			    }
			    /* END OF ACTION: skip-to-end-of-tuple-defn */
			}
		      ZL3:;
		    }
		    /* END OF INLINE: 147 */
		}
		break;
	      default:
		{
		    /* BEGINNING OF ACTION: tuple-name */
		    {
#line 379 "c-parser.act"

		types_add_name(&c_current_type, c_current_table, &(ZI123), FALSE);
	
#line 2907 "tmp.c-parser.c"
		    }
		    /* END OF ACTION: tuple-name */
		}
		break;
	    }
	}
	/* END OF INLINE: 146 */
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: expected-identifier */
	{
#line 800 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_identifier();
		}
	
#line 2927 "tmp.c-parser.c"
	}
	/* END OF ACTION: expected-identifier */
	/* BEGINNING OF ACTION: skip-to-end-of-tuple-defn */
	{
#line 891 "c-parser.act"

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
	
#line 2961 "tmp.c-parser.c"
	}
	/* END OF ACTION: skip-to-end-of-tuple-defn */
    }
}

static void
ZR183(void)
{
    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
	return;
    }
    {
	NStringT ZI105;

	/* BEGINNING OF INLINE: c-parse-grammar::identifier */
	{
	    switch (CURRENT_TERMINAL) {
	      case (C_TOK_C_HIDENTIFIER):
		{
		    /* BEGINNING OF EXTRACT: C-IDENTIFIER */
		    {
#line 196 "c-parser.act"

		nstring_assign(&ZI105, c_lexer_string_value(c_current_stream));
	
#line 2987 "tmp.c-parser.c"
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

		nstring_assign(&ZI105, c_lexer_string_value(c_current_stream));
	
#line 3001 "tmp.c-parser.c"
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
#line 586 "c-parser.act"

		c_current_entry = table_get_basic(c_current_table, (&ZI105));
		if (c_current_entry == NULL) {
			E_c_unknown_basic((&ZI105));
		} else {
			BasicT * basic = entry_get_basic(c_current_entry);

			if (basic_get_result_code(basic)) {
				E_c_basic_mult_def((&ZI105));
				c_current_entry = NULL;
			} else if (types_equal_zero_tuple(basic_result (basic))) {
				E_c_basic_has_no_result((&ZI105));
				c_current_entry = NULL;
			}
		}
		nstring_destroy(&(ZI105));
	
#line 3032 "tmp.c-parser.c"
	}
	/* END OF ACTION: set-terminal */
	ZR142 ();
	ZR121 ();
	/* BEGINNING OF INLINE: 186 */
	{
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI165;

		ZR109 (&ZI165);
		if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
		/* BEGINNING OF ACTION: x-set-terminal */
		{
#line 639 "c-parser.act"

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
				c_code_deallocate((ZI165));
				c_current_entry = NULL;
			} else {
				types_destroy(&c_saved_type);
				c_code_check((ZI165), FALSE, FALSE, NULL, &c_current_type, c_current_table);
				basic_set_result_code(basic,  (ZI165));
			}
		} else {
			types_destroy(&c_saved_type);
			types_destroy(&c_current_type);
			c_code_deallocate((ZI165));
		}
	
#line 3102 "tmp.c-parser.c"
		}
		/* END OF ACTION: x-set-terminal */
		ZR124 ();
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
#line 854 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_code();
		}
	
#line 3122 "tmp.c-parser.c"
		}
		/* END OF ACTION: expected-code */
		/* BEGINNING OF ACTION: skip-to-end-of-terminal */
		{
#line 1056 "c-parser.act"

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
	
#line 3151 "tmp.c-parser.c"
		}
		/* END OF ACTION: skip-to-end-of-terminal */
	    }
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
ZR125(void)
{
  ZL2_125:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
	{
	    ZR127 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 1105 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 3183 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: skip-recover */
	    /* BEGINNING OF INLINE: c-parse-grammar::map-list */
	    goto ZL2_125;
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
ZR142(void)
{
    switch (CURRENT_TERMINAL) {
      case (C_TOK_TYPEMARK):
	{
	    ADVANCE_LEXER;
	    ZR154 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: save-tuple */
	    {
#line 351 "c-parser.act"

		types_assign(&c_saved_type, &c_current_type);
	
#line 3220 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: save-tuple */
	    ZR158 ();
	    ZR154 ();
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
#line 356 "c-parser.act"

		types_init(&c_saved_type);
		types_init(&c_current_type);
	
#line 3240 "tmp.c-parser.c"
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
ZR159(void)
{
  ZL2_159:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
	{
	    ZR161 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 1105 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 3272 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: skip-recover */
	    /* BEGINNING OF INLINE: c-parse-grammar::assignment-list */
	    goto ZL2_159;
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
ZR167(void)
{
  ZL2_167:;
    switch (CURRENT_TERMINAL) {
      case (C_TOK_SID_HIDENTIFIER): case (C_TOK_C_HIDENTIFIER):
	{
	    ZR169 ();
	    if ((CURRENT_TERMINAL) == (ERROR_TERMINAL)) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: skip-recover */
	    {
#line 1105 "c-parser.act"

		c_propagating_error = FALSE;
	
#line 3309 "tmp.c-parser.c"
	    }
	    /* END OF ACTION: skip-recover */
	    /* BEGINNING OF INLINE: c-parse-grammar::param-assign-list */
	    goto ZL2_167;
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
ZR121(void)
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
#line 848 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_define();
		}
	
#line 3354 "tmp.c-parser.c"
	}
	/* END OF ACTION: expected-define */
    }
}

static void
ZR124(void)
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
#line 836 "c-parser.act"

		if (!c_propagating_error) {
			E_c_expected_terminator();
		}
	
#line 3386 "tmp.c-parser.c"
	}
	/* END OF ACTION: expected-terminator */
    }
}

/* BEGINNING OF TRAILER */

#line 1115 "c-parser.act"


#line 3397 "tmp.c-parser.c"

/* END OF FILE */
