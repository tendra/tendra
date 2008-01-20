/*
 * Automatically generated from the files:
 *	c-parser.sid
 * and
 *	c-parser.act
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


#include "c-parser.h"
#include "../adt/action.h"
#include "c-code.h"
#include "c-out-info.h"
#include "../adt/basic.h"
#include "../adt/entry.h"
#include "../gen-errors.h"
#include "../adt/type.h"
#include "../adt/types.h"

#define CURRENT_TERMINAL c_lexer_get_terminal (c_current_stream)
#define ADVANCE_LEXER c_lexer_next_token (c_current_stream)
#define SAVE_LEXER(x) (c_lexer_save_terminal (c_current_stream, (CTokenT) (x)))
#define RESTORE_LEXER (c_lexer_restore_terminal (c_current_stream))

/* typedefs for the maps section */
typedef CCodeT * CCodeP;

static NStringT		c_prefix_names [CPFX_NUM_PREFIXES];
static BoolT		c_inited_prefix_names = FALSE;
static CPrefixT		c_current_prefix;
static EntryT *		c_current_entry;
static TypeTupleT	c_saved_type;
static TypeTupleT	c_current_type;
static BoolT		c_propagating_error = FALSE;

CLexerStreamT *		c_current_stream;
COutputInfoT *		c_current_out_info;
TableT *			c_current_table;

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
      case 10:
	{
	    ZR136 ();
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_134;
	    }
	}
	/*UNREACHED*/
      case 36:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR174(void)
{
  ZL2_174:;
    switch (CURRENT_TERMINAL) {
      case 9: case 10:
	{
	    ZR176 ();
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    c_propagating_error = FALSE;
	    }
	    goto ZL2_174;
	}
	/*UNREACHED*/
      case 36:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR115(CCodeP ZI108)
{
  ZL2_115:;
    switch (CURRENT_TERMINAL) {
      case 24: case 25: case 26: case 27: case 28:
      case 29: case 30: case 31: case 32: case 33:
	{
	    ZR111 (ZI108);
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_115;
	    }
	}
	/*UNREACHED*/
      case 36:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR181(void)
{
  ZL2_181:;
    switch (CURRENT_TERMINAL) {
      case 9: case 10:
	{
	    ZR183 ();
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    c_propagating_error = FALSE;
	    }
	    goto ZL2_181;
	}
	/*UNREACHED*/
      case 36:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR109(CCodeP *ZO108)
{
    CCodeP ZI108;

    if ((CURRENT_TERMINAL) == 36) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 34:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

	(ZI108) = c_code_create(istream_name(&(c_lexer_stream->istream)), 
	      		      istream_line(&(c_lexer_stream->istream)));
	}
	ZR115 (ZI108);
	switch (CURRENT_TERMINAL) {
	  case 35:
	    break;
	  case 36:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (36);
    return;
  ZL0:;
    *ZO108 = ZI108;
}

static void
ZR158(void)
{
    if ((CURRENT_TERMINAL) == 36) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 18:
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

    if (!c_propagating_error) {
	E_c_expected_arrow ();
    }
	}
    }
}

static void
ZR127(void)
{
    if ((CURRENT_TERMINAL) == 36) {
	return;
    }
    {
	NStringT ZI129;

	{
	    switch (CURRENT_TERMINAL) {
	      case 10:
		{
		    {

    nstring_assign (&ZI129, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 9:
		{
		    {

    nstring_assign (&ZI129, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    if ((c_current_entry = table_get_entry (c_current_table, (&ZI129))) ==
	NULL) {
	E_c_unknown_identifier ((&ZI129));
    } else if (entry_get_mapping (c_current_entry)) {
	E_c_remapped_identifier ((&ZI129));
	c_current_entry = NULL;
    } else {
	switch (entry_type (c_current_entry)) EXHAUSTIVE {
	  case ET_NAME:
	  case ET_ACTION:
	  case ET_NON_LOCAL:
	    E_c_illegal_map ((&ZI129));
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
    nstring_destroy (&(ZI129));
	}
	ZR158 ();
	{
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		NStringT ZI132;

		switch (CURRENT_TERMINAL) {
		  case 10:
		    {

    nstring_assign (&ZI132, c_lexer_string_value (c_current_stream));
		    }
		    break;
		  default:
		    goto ZL4;
		}
		ADVANCE_LEXER;
		{

    if (c_current_entry) {
	entry_set_mapping (c_current_entry, &(ZI132));
    } else {
	nstring_destroy (&(ZI132));
    }
		}
		ZR124 ();
		if ((CURRENT_TERMINAL) == 36) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
	    }
	    goto ZL3;
	  ZL4:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_c_identifier ();
    }
		}
		{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ASSIGNMENTS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_PARAM_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_RESULT_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TERMINALS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
		}
	    }
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR161(void)
{
    if ((CURRENT_TERMINAL) == 36) {
	return;
    }
    {
	NStringT ZI105;

	{
	    switch (CURRENT_TERMINAL) {
	      case 10:
		{
		    {

    nstring_assign (&ZI105, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 9:
		{
		    {

    nstring_assign (&ZI105, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    if ((c_current_entry = table_get_type (c_current_table, (&ZI105))) ==
	NULL) {
	E_c_unknown_assign ((&ZI105));
    } else if (type_get_assign_code (entry_get_type (c_current_entry))) {
	E_c_assign_mult_def ((&ZI105));
	c_current_entry = NULL;
    }
    nstring_destroy (&(ZI105));
	}
	ZR142 ();
	ZR121 ();
	{
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI165;

		ZR109 (&ZI165);
		if ((CURRENT_TERMINAL) == 36) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
		{

    if (c_current_entry) {
	BoolT      errored = FALSE;
	KeyT *       key     = entry_key (c_current_entry);
	TypeTupleT tmp;

	types_init (&tmp);
	types_add_type_entry (&tmp, c_current_entry, FALSE);
	if (!types_disjoint_names (&c_saved_type)) {
	    E_c_assign_param_clash (key, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_saved_type, &tmp)) {
	    E_c_assign_param_mismatch (key, &tmp, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_disjoint_names (&c_current_type)) {
	    E_c_assign_result_clash (key, &c_current_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_current_type, &tmp)) {
	    E_c_assign_result_mismatch (key, &tmp, &c_current_type);
	    errored = TRUE;
	}
	if (types_intersect (&c_saved_type, &c_current_type)) {
	    E_c_assign_formal_clash (key, &c_saved_type, &c_current_type);
	    errored = TRUE;
	}
	types_destroy (&tmp);
	if (errored) {
	    types_destroy (&c_saved_type);
	    types_destroy (&c_current_type);
	    c_code_deallocate ((ZI165));
	    c_current_entry = NULL;
	} else {
	    TypeT * type = entry_get_type (c_current_entry);

	    c_code_check ((ZI165), FALSE, FALSE, &c_saved_type, &c_current_type,
			  c_current_table);
	    type_set_assign_code (type,  (ZI165));
	}
    } else {
	types_destroy (&c_saved_type);
	types_destroy (&c_current_type);
	c_code_deallocate ((ZI165));
    }
		}
		ZR124 ();
		if ((CURRENT_TERMINAL) == 36) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
	    }
	    goto ZL3;
	  ZL4:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_code ();
    }
		}
		{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_PARAM_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_RESULT_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TERMINALS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
		}
	    }
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR190(void)
{
    if ((CURRENT_TERMINAL) == 36) {
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
	{
	    {
		NStringT ZI105;

		{
		    switch (CURRENT_TERMINAL) {
		      case 10:
			{
			    {

    nstring_assign (&ZI105, c_lexer_string_value (c_current_stream));
			    }
			    ADVANCE_LEXER;
			}
			break;
		      case 9:
			{
			    {

    nstring_assign (&ZI105, c_lexer_string_value (c_current_stream));
			    }
			    ADVANCE_LEXER;
			}
			break;
		      default:
			goto ZL3;
		    }
		}
		{

    if ((c_current_entry = table_get_action (c_current_table, (&ZI105))) ==
	NULL) {
	E_c_unknown_action ((&ZI105));
    } else {
	ActionT * action = entry_get_action (c_current_entry);

	if (action_get_code (action)) {
	    E_c_action_mult_def ((&ZI105));
	    c_current_entry = NULL;
	}
    }
    nstring_destroy (&(ZI105));
		}
		{
		    {
			switch (CURRENT_TERMINAL) {
			  case 16:
			    break;
			  default:
			    goto ZL6;
			}
			ADVANCE_LEXER;
		    }
		    goto ZL5;
		  ZL6:;
		    {
			{

    if (!c_propagating_error) {
	E_c_expected_end_action ();
    }
			}
		    }
		  ZL5:;
		}
		ZR142 ();
		ZR121 ();
		{
		    if ((CURRENT_TERMINAL) == 36) {
			RESTORE_LEXER;
			goto ZL3;
		    }
		    {
			CCodeP ZI165;

			ZR109 (&ZI165);
			if ((CURRENT_TERMINAL) == 36) {
			    RESTORE_LEXER;
			    goto ZL8;
			}
			{

    if (c_current_entry) {
	ActionT *    action  = entry_get_action (c_current_entry);
	TypeTupleT * param   = action_param (action);
	TypeTupleT * result  = action_result (action);
	BoolT      errored = FALSE;
	KeyT *       key     = entry_key (c_current_entry);

	if (!types_disjoint_names (&c_saved_type)) {
	    E_c_action_param_clash (key, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_saved_type, param)) {
	    E_c_action_param_mismatch (key, param, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_disjoint_names (&c_current_type)) {
	    E_c_action_result_clash (key, &c_current_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_current_type, result)) {
	    E_c_action_result_mismatch (key, result, &c_current_type);
	    errored = TRUE;
	}
	if (types_intersect (&c_saved_type, &c_current_type)) {
	    E_c_action_formal_clash (key, &c_saved_type, &c_current_type);
	    errored = TRUE;
	}
	if (errored) {
	    types_destroy (&c_saved_type);
	    types_destroy (&c_current_type);
	    c_code_deallocate ((ZI165));
	    c_current_entry = NULL;
	} else {
	    c_code_check ((ZI165), TRUE, FALSE, &c_saved_type, &c_current_type,
			  c_current_table);
	    types_propogate_mutations (param, &c_saved_type);
	    action_set_code (action,  (ZI165));
	}
    } else {
	types_destroy (&c_saved_type);
	types_destroy (&c_current_type);
	c_code_deallocate ((ZI165));
    }
			}
			ZR124 ();
			if ((CURRENT_TERMINAL) == 36) {
			    RESTORE_LEXER;
			    goto ZL8;
			}
		    }
		    goto ZL7;
		  ZL8:;
		    {
			{

    if (!c_propagating_error) {
	E_c_expected_code ();
    }
			}
			{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
			}
		    }
		  ZL7:;
		}
	    }
	    goto ZL2;
	  ZL3:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_identifier ();
    }
		}
		{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
		}
	    }
	  ZL2:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR149(void)
{
    if ((CURRENT_TERMINAL) == 36) {
	return;
    }
  ZL2_149:;
    {
	ZR144 ();
	{
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		{

    (ZI0) = ((CURRENT_TERMINAL == C_TOK_CLOSE_TUPLE) ||
		  (CURRENT_TERMINAL == C_TOK_EOF) ||
		  (c_propagating_error));
		}
		if (!ZI0)
		    goto ZL5;
		goto ZL3;
	    }
	    /*UNREACHED*/
	  ZL5:;
	    switch (CURRENT_TERMINAL) {
	      case 11:
		{
		    ADVANCE_LEXER;
		    goto ZL2_149;
		}
		/*UNREACHED*/
	      default:
		goto ZL4;
	    }
	    /*UNREACHED*/
	  ZL4:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_separator ();
    }
		}
		goto ZL2_149;
	    }
	    /*UNREACHED*/
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR188(void)
{
  ZL2_188:;
    switch (CURRENT_TERMINAL) {
      case 14:
	{
	    ZR190 ();
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    c_propagating_error = FALSE;
	    }
	    goto ZL2_188;
	}
	/*UNREACHED*/
      case 36:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR169(void)
{
    if ((CURRENT_TERMINAL) == 36) {
	return;
    }
    {
	NStringT ZI105;

	{
	    switch (CURRENT_TERMINAL) {
	      case 10:
		{
		    {

    nstring_assign (&ZI105, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 9:
		{
		    {

    nstring_assign (&ZI105, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    if ((c_current_entry = table_get_type (c_current_table, (&ZI105))) ==
	NULL) {
	E_c_unknown_param_assign ((&ZI105));
    } else if (type_get_param_assign_code (entry_get_type (c_current_entry))) {
	E_c_param_assign_mult_def ((&ZI105));
	c_current_entry = NULL;
    }
    nstring_destroy (&(ZI105));
	}
	ZR142 ();
	ZR121 ();
	{
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI165;

		ZR109 (&ZI165);
		if ((CURRENT_TERMINAL) == 36) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
		{

    if (c_current_entry) {
	BoolT      errored = FALSE;
	KeyT *       key     = entry_key (c_current_entry);
	TypeTupleT tmp;

	types_init (&tmp);
	types_add_type_entry (&tmp, c_current_entry, FALSE);
	if (!types_disjoint_names (&c_saved_type)) {
	    E_c_param_assign_param_clash (key, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_saved_type, &tmp)) {
	    E_c_param_assign_param_mismatch (key, &tmp, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_disjoint_names (&c_current_type)) {
	    E_c_param_assign_result_clash (key, &c_current_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_current_type, &tmp)) {
	    E_c_param_assign_res_mismatch (key, &tmp, &c_current_type);
	    errored = TRUE;
	}
	if (types_intersect (&c_saved_type, &c_current_type)) {
	    E_c_param_assign_formal_clash (key, &c_saved_type,
					    &c_current_type);
	    errored = TRUE;
	}
	types_destroy (&tmp);
	if (errored) {
	    types_destroy (&c_saved_type);
	    types_destroy (&c_current_type);
	    c_code_deallocate ((ZI165));
	    c_current_entry = NULL;
	} else {
	    TypeT * type = entry_get_type (c_current_entry);

	    c_code_check ((ZI165), FALSE, TRUE, &c_saved_type, &c_current_type,
			  c_current_table);
	    type_set_param_assign_code (type,  (ZI165));
	}
    } else {
	types_destroy (&c_saved_type);
	types_destroy (&c_current_type);
	c_code_deallocate ((ZI165));
    }
		}
		ZR124 ();
		if ((CURRENT_TERMINAL) == 36) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
	    }
	    goto ZL3;
	  ZL4:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_code ();
    }
		}
		{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_RESULT_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TERMINALS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
		}
	    }
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR117(void)
{
  ZL2_117:;
    switch (CURRENT_TERMINAL) {
      case 9: case 10:
	{
	    ZR119 ();
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    c_propagating_error = FALSE;
	    }
	    goto ZL2_117;
	}
	/*UNREACHED*/
      case 36:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR111(CCodeP ZI108)
{
    switch (CURRENT_TERMINAL) {
      case 27:
	{
	    ADVANCE_LEXER;
	    {

	c_code_append_advance((ZI108));
	    }
	}
	break;
      case 24:
	{
	    ADVANCE_LEXER;
	    {

	NStringT ns;
	nstring_copy_cstring(&ns, "@");		/* TODO append '@' to code buffer? */

	c_code_append_string((ZI108), &ns);	/* TODO really append_label()? */
	    }
	}
	break;
      case 32:
	{
	    NStringT ZI114;

	    {

	nstring_assign(&ZI114, c_lexer_string_value (c_current_stream));
	    }
	    ADVANCE_LEXER;
	    {

	assert(!nstring_contains(&(ZI114), '@'));
	c_code_append_string((ZI108), &(ZI114));
	    }
	}
	break;
      case 33:
	{
	    ADVANCE_LEXER;
	    {

	E_c_eof_in_code(&(c_lexer_stream->istream));
	    }
	}
	break;
      case 25:
	{
	    ADVANCE_LEXER;
	    {

	c_code_append_exception((ZI108));
	    }
	}
	break;
      case 30:
	{
	    NStringT ZI113;

	    {

	nstring_assign(&ZI113, c_lexer_string_value (c_current_stream));
	    }
	    ADVANCE_LEXER;
	    {

	c_code_append_identifier((ZI108), &(ZI113));
	    }
	}
	break;
      case 28:
	{
	    NStringT ZI113;

	    {

	nstring_assign(&ZI113, c_lexer_string_value (c_current_stream));
	    }
	    ADVANCE_LEXER;
	    {

	c_code_append_label((ZI108), &(ZI113));
	    }
	}
	break;
      case 31:
	{
	    NStringT ZI113;

	    {

	nstring_assign(&ZI113, c_lexer_string_value (c_current_stream));
	    }
	    ADVANCE_LEXER;
	    {

	c_code_append_modifiable((ZI108), &(ZI113));
	    }
	}
	break;
      case 29:
	{
	    NStringT ZI113;

	    {

	nstring_assign(&ZI113, c_lexer_string_value (c_current_stream));
	    }
	    ADVANCE_LEXER;
	    {

	c_code_append_reference((ZI108), &(ZI113));
	    }
	}
	break;
      case 26:
	{
	    ADVANCE_LEXER;
	    {

	c_code_append_terminal((ZI108));
	    }
	}
	break;
      case 36:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR119(void)
{
    if ((CURRENT_TERMINAL) == 36) {
	return;
    }
    {
	NStringT ZI120;

	{
	    switch (CURRENT_TERMINAL) {
	      case 10:
		{
		    {

    nstring_assign (&ZI120, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 9:
		{
		    {

    nstring_assign (&ZI120, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    int prefix;

    if (!c_inited_prefix_names) {
	nstring_copy_cstring (&(c_prefix_names [CPFX_TYPE]), "type");
	nstring_copy_cstring (&(c_prefix_names [CPFX_FN]), "function");
	nstring_copy_cstring (&(c_prefix_names [CPFX_IN]), "input");
	nstring_copy_cstring (&(c_prefix_names [CPFX_OUT]), "output");
	nstring_copy_cstring (&(c_prefix_names [CPFX_LABEL]), "label");
	nstring_copy_cstring (&(c_prefix_names [CPFX_TERMINAL]), "terminal");
	nstring_copy_cstring (&(c_prefix_names [CPFX_PERSISTENTS]), "persistents");
	c_inited_prefix_names = TRUE;
    }
    for (prefix = 0; prefix < CPFX_NUM_PREFIXES; prefix ++) {
	if (nstring_ci_equal ((&ZI120), &(c_prefix_names [prefix]))) {
	    break;
	}
    }
    if ((c_current_prefix = (CPrefixT) prefix) == CPFX_NUM_PREFIXES) {
	E_c_unknown_prefix ((&ZI120));
    }
    nstring_destroy (&(ZI120));
	}
	ZR121 ();
	{
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		NStringT ZI123;

		switch (CURRENT_TERMINAL) {
		  case 10:
		    {

    nstring_assign (&ZI123, c_lexer_string_value (c_current_stream));
		    }
		    break;
		  default:
		    goto ZL4;
		}
		ADVANCE_LEXER;
		{

    if (c_current_prefix == CPFX_NUM_PREFIXES) {
	nstring_destroy (&(ZI123));
    } else {
	NStringT * prefix = c_out_info_prefix (c_current_out_info,
					     c_current_prefix);

	nstring_destroy (prefix);
	nstring_assign (prefix, &(ZI123));
    }
		}
		ZR124 ();
		if ((CURRENT_TERMINAL) == 36) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
	    }
	    goto ZL3;
	  ZL4:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_c_identifier ();
    }
		}
		{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_MAPS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TERMINALS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ASSIGNMENTS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_PARAM_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_RESULT_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
		}
	    }
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

void
c_parse_grammar(void)
{
    if ((CURRENT_TERMINAL) == 36) {
	return;
    }
    {
	{
	    switch (CURRENT_TERMINAL) {
	      case 0:
		{
		    ADVANCE_LEXER;
		    ZR117 ();
		    if ((CURRENT_TERMINAL) == 36) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 2:
		{
		    ADVANCE_LEXER;
		    ZR134 ();
		    if ((CURRENT_TERMINAL) == 36) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    ADVANCE_LEXER;
		    ZR125 ();
		    if ((CURRENT_TERMINAL) == 36) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 5:
		    break;
		  default:
		    goto ZL6;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL5;
	  ZL6:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_blt_header ();
    }
		}
	    }
	  ZL5:;
	}
	{
	    {
		CCodeP ZI202;

		ZR109 (&ZI202);
		if ((CURRENT_TERMINAL) == 36) {
		    RESTORE_LEXER;
		    goto ZL8;
		}
		{

    c_code_check ((ZI202), FALSE, FALSE, NULL, NULL,
		  c_current_table);
    c_out_info_set_header1 (c_current_out_info, (ZI202));
		}
	    }
	    goto ZL7;
	  ZL8:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_code ();
    }
		}
	    }
	  ZL7:;
	}
	ZR215 ();
	{
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI205;

		ZR109 (&ZI205);
		if ((CURRENT_TERMINAL) == 36) {
		    RESTORE_LEXER;
		    goto ZL10;
		}
		{

    c_code_check ((ZI205), FALSE, FALSE, NULL, NULL,
		  c_current_table);
    c_out_info_set_header2 (c_current_out_info, (ZI205));
		}
	    }
	    goto ZL9;
	  ZL10:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_code ();
    }
		}
	    }
	  ZL9:;
	}
	ZR124 ();
	{
	    switch (CURRENT_TERMINAL) {
	      case 3:
		{
		    ADVANCE_LEXER;
		    ZR159 ();
		    if ((CURRENT_TERMINAL) == 36) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 36:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 21:
		{
		    ADVANCE_LEXER;
		    ZR167 ();
		    if ((CURRENT_TERMINAL) == 36) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 8:
		{
		    ADVANCE_LEXER;
		    ZR174 ();
		    if ((CURRENT_TERMINAL) == 36) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 4:
		    break;
		  default:
		    goto ZL15;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL14;
	  ZL15:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_blt_terminals ();
    }
		}
	    }
	  ZL14:;
	}
	ZR181 ();
	{
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 6:
		    break;
		  default:
		    goto ZL17;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL16;
	  ZL17:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_blt_actions ();
    }
		}
	    }
	  ZL16:;
	}
	ZR188 ();
	{
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    break;
		  default:
		    goto ZL19;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL18;
	  ZL19:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_blt_trailer ();
    }
		}
	    }
	  ZL18:;
	}
	{
	    {
		CCodeP ZI214;

		ZR109 (&ZI214);
		if ((CURRENT_TERMINAL) == 36) {
		    RESTORE_LEXER;
		    goto ZL21;
		}
		{

    c_code_check ((ZI214), FALSE, FALSE, NULL, NULL,
		  c_current_table);
    c_out_info_set_trailer1 (c_current_out_info, (ZI214));
		}
	    }
	    goto ZL20;
	  ZL21:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_code ();
    }
		}
	    }
	  ZL20:;
	}
	ZR215 ();
	{
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI217;

		ZR109 (&ZI217);
		if ((CURRENT_TERMINAL) == 36) {
		    RESTORE_LEXER;
		    goto ZL23;
		}
		{

    c_code_check ((ZI217), FALSE, FALSE, NULL, NULL,
		  c_current_table);
    c_out_info_set_trailer2 (c_current_out_info, (ZI217));
		}
	    }
	    goto ZL22;
	  ZL23:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_code ();
    }
		}
	    }
	  ZL22:;
	}
	ZR124 ();
	{
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 23:
		    break;
		  default:
		    goto ZL25;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL24;
	  ZL25:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_eof ();
    }
		}
	    }
	  ZL24:;
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
ZR152(void)
{
    switch (CURRENT_TERMINAL) {
      case 10:
	{
	    ZR149 ();
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 36:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR154(void)
{
    if ((CURRENT_TERMINAL) == 36) {
	return;
    }
    {
	{

    types_init (&c_current_type);
	}
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 19:
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

    if (!c_propagating_error) {
	E_c_expected_open_tuple ();
    }
		}
	    }
	  ZL2:;
	}
	ZR152 ();
	if ((CURRENT_TERMINAL) == 36) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    c_propagating_error = FALSE;
	}
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 20:
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

    if (!c_propagating_error) {
	E_c_expected_close_tuple ();
    }
		}
	    }
	  ZL4:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR136(void)
{
    if ((CURRENT_TERMINAL) == 36) {
	return;
    }
    {
	NStringT ZI123;
	NStringT ZI140;

	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 10:
		    {

    nstring_assign (&ZI123, c_lexer_string_value (c_current_stream));
		    }
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

	nstring_init(&(ZI123));
		}
		{

    if (!c_propagating_error) {
	E_c_expected_c_identifier ();
    }
		}
	    }
	  ZL2:;
	}
	switch (CURRENT_TERMINAL) {
	  case 12:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 10:
		    {

    nstring_assign (&ZI140, c_lexer_string_value (c_current_stream));
		    }
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

	nstring_init(&(ZI140));
		}
		{

    if (!c_propagating_error) {
	E_c_expected_identifier ();
    }
		}
	    }
	  ZL4:;
	}
	{

    if(persistent_list_find(c_out_info_persistents(c_current_out_info), (&ZI123)) == NULL) {
      	   PersistentT* p = persistent_create(&(ZI123), &(ZI140));
	   persistent_list_append(c_out_info_persistents(c_current_out_info),p);
    } else {
	nstring_destroy(&(ZI123));
	nstring_destroy(&(ZI140));
	/* TODO error out E_c_persistent_variable_name_conflict((&ZI123))) ;*/
    }
	}
	ZR124 ();
	if ((CURRENT_TERMINAL) == 36) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR215(void)
{
    if ((CURRENT_TERMINAL) == 36) {
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

    if (!c_propagating_error) {
	E_c_expected_separator ();
    }
	}
    }
}

static void
ZR176(void)
{
    if ((CURRENT_TERMINAL) == 36) {
	return;
    }
    {
	NStringT ZI105;

	{
	    switch (CURRENT_TERMINAL) {
	      case 10:
		{
		    {

    nstring_assign (&ZI105, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 9:
		{
		    {

    nstring_assign (&ZI105, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    if ((c_current_entry = table_get_type (c_current_table, (&ZI105))) ==
	NULL) {
	E_c_unknown_result_assign ((&ZI105));
    } else if (type_get_result_assign_code (entry_get_type (c_current_entry))) {
	E_c_result_assign_mult_def ((&ZI105));
	c_current_entry = NULL;
    }
    nstring_destroy (&(ZI105));
	}
	ZR142 ();
	ZR121 ();
	{
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI165;

		ZR109 (&ZI165);
		if ((CURRENT_TERMINAL) == 36) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
		{

    if (c_current_entry) {
	BoolT      errored = FALSE;
	KeyT *       key     = entry_key (c_current_entry);
	TypeTupleT tmp;

	types_init (&tmp);
	types_add_type_entry (&tmp, c_current_entry, FALSE);
	if (!types_disjoint_names (&c_saved_type)) {
	    E_c_result_assign_param_clash (key, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_saved_type, &tmp)) {
	    E_c_res_assign_param_mismatch (key, &tmp, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_disjoint_names (&c_current_type)) {
	    E_c_result_assign_result_clash (key, &c_current_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_current_type, &tmp)) {
	    E_c_res_assign_result_mismatch (key, &tmp, &c_current_type);
	    errored = TRUE;
	}
	if (types_intersect (&c_saved_type, &c_current_type)) {
	    E_c_result_assign_formal_clash (key, &c_saved_type,
					    &c_current_type);
	    errored = TRUE;
	}
	types_destroy (&tmp);
	if (errored) {
	    types_destroy (&c_saved_type);
	    types_destroy (&c_current_type);
	    c_code_deallocate ((ZI165));
	    c_current_entry = NULL;
	} else {
	    TypeT * type = entry_get_type (c_current_entry);

	    c_code_check ((ZI165), FALSE, FALSE, &c_saved_type, &c_current_type,
			  c_current_table);
	    type_set_result_assign_code (type,  (ZI165));
	}
    } else {
	types_destroy (&c_saved_type);
	types_destroy (&c_current_type);
	c_code_deallocate ((ZI165));
    }
		}
		ZR124 ();
		if ((CURRENT_TERMINAL) == 36) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
	    }
	    goto ZL3;
	  ZL4:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_code ();
    }
		}
		{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TERMINALS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
		}
	    }
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR144(void)
{
    if ((CURRENT_TERMINAL) == 36) {
	return;
    }
    {
	NStringT ZI123;

	switch (CURRENT_TERMINAL) {
	  case 10:
	    {

    nstring_assign (&ZI123, c_lexer_string_value (c_current_stream));
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 12:
		{
		    ADVANCE_LEXER;
		    {
			{
			    NStringT ZI140;

			    {
				switch (CURRENT_TERMINAL) {
				  case 10:
				    {
					{

    nstring_assign (&ZI140, c_lexer_string_value (c_current_stream));
					}
					ADVANCE_LEXER;
				    }
				    break;
				  case 9:
				    {
					{

    nstring_assign (&ZI140, c_lexer_string_value (c_current_stream));
					}
					ADVANCE_LEXER;
				    }
				    break;
				  default:
				    goto ZL4;
				}
			    }
			    {
				switch (CURRENT_TERMINAL) {
				  case 22:
				    {
					ADVANCE_LEXER;
					{

    if (!types_add_typed_name (&c_current_type, c_current_table, &(ZI123),
			       (&ZI140), TRUE)) {
	E_c_unknown_type ((&ZI140));
    }
    nstring_destroy (&(ZI140));
					}
				    }
				    break;
				  default:
				    {
					{

    if (!types_add_typed_name (&c_current_type, c_current_table, &(ZI123),
			       (&ZI140), FALSE)) {
	E_c_unknown_type ((&ZI140));
    }
    nstring_destroy (&(ZI140));
					}
				    }
				    break;
				}
			    }
			}
			goto ZL3;
		      ZL4:;
			{
			    {

    if (!c_propagating_error) {
	E_c_expected_identifier ();
    }
			    }
			    {

    nstring_destroy (&(ZI123));
			    }
			    {

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_DEFINE) &&
	   (CURRENT_TERMINAL != C_TOK_CODE) &&
	   (CURRENT_TERMINAL != C_TOK_SEPARATOR) &&
	   (CURRENT_TERMINAL != C_TOK_CLOSE_TUPLE) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_PARAM_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_RESULT_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TERMINALS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
			    }
			}
		      ZL3:;
		    }
		}
		break;
	      default:
		{
		    {

    types_add_name (&c_current_type, c_current_table, &(ZI123), FALSE);
		    }
		}
		break;
	    }
	}
    }
    return;
  ZL1:;
    {
	{

    if (!c_propagating_error) {
	E_c_expected_identifier ();
    }
	}
	{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_DEFINE) &&
	   (CURRENT_TERMINAL != C_TOK_CODE) &&
	   (CURRENT_TERMINAL != C_TOK_SEPARATOR) &&
	   (CURRENT_TERMINAL != C_TOK_CLOSE_TUPLE) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_PARAM_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_RESULT_ASSIGN) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TERMINALS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
	}
    }
}

static void
ZR183(void)
{
    if ((CURRENT_TERMINAL) == 36) {
	return;
    }
    {
	NStringT ZI105;

	{
	    switch (CURRENT_TERMINAL) {
	      case 10:
		{
		    {

    nstring_assign (&ZI105, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 9:
		{
		    {

    nstring_assign (&ZI105, c_lexer_string_value (c_current_stream));
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    if ((c_current_entry = table_get_basic (c_current_table, (&ZI105))) ==
	NULL) {
	E_c_unknown_basic ((&ZI105));
    } else {
	BasicT * basic = entry_get_basic (c_current_entry);

	if (basic_get_result_code (basic)) {
	    E_c_basic_mult_def ((&ZI105));
	    c_current_entry = NULL;
	} else if (types_equal_zero_tuple (basic_result (basic))) {
	    E_c_basic_has_no_result ((&ZI105));
	    c_current_entry = NULL;
	}
    }
    nstring_destroy (&(ZI105));
	}
	ZR142 ();
	ZR121 ();
	{
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		CCodeP ZI165;

		ZR109 (&ZI165);
		if ((CURRENT_TERMINAL) == 36) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
		{

    if (c_current_entry) {
	BasicT *     basic   = entry_get_basic (c_current_entry);
	TypeTupleT * result  = basic_result (basic);
	BoolT      errored = FALSE;
	KeyT *       key     = entry_key (c_current_entry);

	if (!types_disjoint_names (&c_saved_type)) {
	    E_c_basic_param_clash (key, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_equal_zero_tuple (&c_saved_type)) {
	    E_c_basic_param_mismatch (key, &c_saved_type);
	    errored = TRUE;
	}
	if (!types_disjoint_names (&c_current_type)) {
	    E_c_basic_result_clash (key, &c_current_type);
	    errored = TRUE;
	}
	if (!types_fillin_types (&c_current_type, result)) {
	    E_c_basic_result_mismatch (key, result, &c_current_type);
	    errored = TRUE;
	}
	if (types_intersect (&c_saved_type, &c_current_type)) {
	    E_c_basic_formal_clash (key, &c_saved_type, &c_current_type);
	    errored = TRUE;
	}
	if (errored) {
	    types_destroy (&c_saved_type);
	    types_destroy (&c_current_type);
	    c_code_deallocate ((ZI165));
	    c_current_entry = NULL;
	} else {
	    types_destroy (&c_saved_type);
	    c_code_check ((ZI165), FALSE, FALSE, NULL,
			  &c_current_type, c_current_table);
	    basic_set_result_code (basic,  (ZI165));
	}
    } else {
	types_destroy (&c_saved_type);
	types_destroy (&c_current_type);
	c_code_deallocate ((ZI165));
    }
		}
		ZR124 ();
		if ((CURRENT_TERMINAL) == 36) {
		    RESTORE_LEXER;
		    goto ZL4;
		}
	    }
	    goto ZL3;
	  ZL4:;
	    {
		{

    if (!c_propagating_error) {
	E_c_expected_code ();
    }
		}
		{

    while ((CURRENT_TERMINAL != C_TOK_EOF) &&
	   (CURRENT_TERMINAL != C_TOK_TERMINATOR) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_ACTIONS) &&
	   (CURRENT_TERMINAL != C_TOK_BLT_TRAILER)) {
	if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	    (CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	    nstring_destroy (c_lexer_string_value (c_current_stream));
	} else if (CURRENT_TERMINAL == C_TOK_CODE) {
	    c_code_deallocate (c_lexer_code_value (c_current_stream));
	}
	ADVANCE_LEXER;
    }
    if ((CURRENT_TERMINAL == C_TOK_SID_IDENTIFIER) ||
	(CURRENT_TERMINAL == C_TOK_C_IDENTIFIER)) {
	nstring_destroy (c_lexer_string_value (c_current_stream));
    }
    if (CURRENT_TERMINAL != C_TOK_EOF) {
	ADVANCE_LEXER;
    }
    c_propagating_error = TRUE;
		}
	    }
	  ZL3:;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR125(void)
{
  ZL2_125:;
    switch (CURRENT_TERMINAL) {
      case 9: case 10:
	{
	    ZR127 ();
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    c_propagating_error = FALSE;
	    }
	    goto ZL2_125;
	}
	/*UNREACHED*/
      case 36:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR142(void)
{
    switch (CURRENT_TERMINAL) {
      case 12:
	{
	    ADVANCE_LEXER;
	    ZR154 ();
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    types_assign (&c_saved_type, &c_current_type);
	    }
	    ZR158 ();
	    ZR154 ();
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    types_init (&c_saved_type);
    types_init (&c_current_type);
	    }
	}
	break;
      case 36:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR159(void)
{
  ZL2_159:;
    switch (CURRENT_TERMINAL) {
      case 9: case 10:
	{
	    ZR161 ();
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    c_propagating_error = FALSE;
	    }
	    goto ZL2_159;
	}
	/*UNREACHED*/
      case 36:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR167(void)
{
  ZL2_167:;
    switch (CURRENT_TERMINAL) {
      case 9: case 10:
	{
	    ZR169 ();
	    if ((CURRENT_TERMINAL) == 36) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    c_propagating_error = FALSE;
	    }
	    goto ZL2_167;
	}
	/*UNREACHED*/
      case 36:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (36);
    return;
}

static void
ZR121(void)
{
    if ((CURRENT_TERMINAL) == 36) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 15:
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

    if (!c_propagating_error) {
	E_c_expected_define ();
    }
	}
    }
}

static void
ZR124(void)
{
    if ((CURRENT_TERMINAL) == 36) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 13:
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

    if (!c_propagating_error) {
	E_c_expected_terminator ();
    }
	}
    }
}

/* BEGINNING OF TRAILER */



/* END OF FILE */
