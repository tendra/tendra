/*
 * Automatically generated from the files:
 *	lctsyntax.sid
 * and
 *	lctsyntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 22 "lctsyntax.act"

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
 * $Id:$
 */
 
#include "lctsyntax.h"
#include "lctlex.h"
#include "char.h"
#include "adt.h"
#include "error.h"
#include "exds/dstring.h"

#define ADVANCE_LEXER ADVANCE_LCT_LEXER
#define CURRENT_TERMINAL CURRENT_LCT_TERMINAL 
#define SAVE_LEXER SAVE_LCT_LEXER
#define RESTORE_LEXER RESTORE_LCT_LEXER

lexer_parse_tree* lxi_top_level;

#line 60 "lctsyntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Hname(TypeTupleT);
static void ZRaction_Hdefinition_C_Cfunction_Htype_Hdefn(TypeTupleT *, TypeTupleT *);
static void ZRgrp_Hof_Hletters(DStringT *);
static void ZRletters(DStringT *);
static void ZRmap_Hstmnt(void);
static void ZR51(void);
extern void read_lct_unit(void);
static void ZR72(void);
static void ZRstatement_Hlist(void);
static void ZR74(void);
static void ZR75(void);
static void ZR84(TypeTupleT *);
static void ZRheader_Hstmnt(void);
static void ZRcode_Hblock(DStringT *);
static void ZRstatement(void);
static void ZRtrailer_Hstmnt(void);
static void ZRaction_Hdefinition(void);
static void ZRaction_Hdefinition_C_Ctype_Htuple(TypeTupleT *);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Hname(TypeTupleT ZIa)
{
    if ((CURRENT_TERMINAL) == 15) {
	return;
    }
    {
	NStringT ZIname;
	NStringT ZItype;

	switch (CURRENT_TERMINAL) {
	  case 13:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 142 "lctsyntax.act"

	nstring_copy_cstring(&ZIname,lct_token_buff);
#line 105 "lctsyntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 4:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 13:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 142 "lctsyntax.act"

	nstring_copy_cstring(&ZItype,lct_token_buff);
#line 127 "lctsyntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF ACTION: append-tuple */
	{
#line 188 "lctsyntax.act"

	EntryT* entry = table_get_entry(lxi_top_level->table,(&ZItype));
	if(entry == NULL) {
		 error(ERROR_SERIOUS, "Unknown type %s", nstring_to_cstring((&ZItype)));
		 nstring_destroy((&ZIname));
		 nstring_destroy((&ZItype));
	}
	else if(!entry_is_type(entry))
		 error(ERROR_SERIOUS, "%s is not a type", (&ZItype));
	else
		typetuple_append((&ZIa),typetupleentry_create((&ZIname),entry));
#line 149 "lctsyntax.c"
	}
	/* END OF ACTION: append-tuple */
    }
    return;
  ZL1:;
    SAVE_LEXER (15);
    return;
}

static void
ZRaction_Hdefinition_C_Cfunction_Htype_Hdefn(TypeTupleT *ZOin, TypeTupleT *ZOout)
{
    TypeTupleT ZIin;
    TypeTupleT ZIout;

    switch (CURRENT_TERMINAL) {
      case 5: case 13:
	{
	    ZRaction_Hdefinition_C_Ctype_Htuple (&ZIin);
	    ZR72 ();
	    ZRaction_Hdefinition_C_Ctype_Htuple (&ZIout);
	    if ((CURRENT_TERMINAL) == 15) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 184 "lctsyntax.act"

	typetuple_init(&(ZIin));
#line 184 "lctsyntax.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 184 "lctsyntax.act"

	typetuple_init(&(ZIout));
#line 192 "lctsyntax.c"
	    }
	    /* END OF ACTION: init-tuple */
	}
	break;
      case 15:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (15);
    return;
  ZL0:;
    *ZOin = ZIin;
    *ZOout = ZIout;
}

static void
ZRgrp_Hof_Hletters(DStringT *ZIs)
{
    if ((CURRENT_TERMINAL) == 15) {
	return;
    }
    {
	ZRletters (ZIs);
	/* BEGINNING OF INLINE: 39 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 12:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: E_unexpected_eof */
		    {
#line 284 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Unexpected End of File inside @{ @} block") ;
#line 228 "lctsyntax.c"
		    }
		    /* END OF ACTION: E_unexpected_eof */
		}
		break;
	      case 15:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
	/* END OF INLINE: 39 */
    }
    return;
  ZL1:;
    SAVE_LEXER (15);
    return;
}

static void
ZRletters(DStringT *ZIs)
{
  ZL2_letters:;
    switch (CURRENT_TERMINAL) {
      case 6:
	{
	    char ZIc;

	    /* BEGINNING OF EXTRACT: letter */
	    {
#line 138 "lctsyntax.act"

	ZIc = saved_lct_letter ;
#line 262 "lctsyntax.c"
	    }
	    /* END OF EXTRACT: letter */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-letter */
	    {
#line 176 "lctsyntax.act"

	dstring_append_char((ZIs), (ZIc)) ;
#line 271 "lctsyntax.c"
	    }
	    /* END OF ACTION: append-letter */
	    /* BEGINNING OF INLINE: letters */
	    goto ZL2_letters;
	    /* END OF INLINE: letters */
	}
	/*UNREACHED*/
      case 15:
	return;
      default:
	break;
    }
}

static void
ZRmap_Hstmnt(void)
{
    if ((CURRENT_TERMINAL) == 15) {
	return;
    }
    {
	NStringT ZIlexitype;
	NStringT ZIctype;

	switch (CURRENT_TERMINAL) {
	  case 2:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 13:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 142 "lctsyntax.act"

	nstring_copy_cstring(&ZIlexitype,lct_token_buff);
#line 310 "lctsyntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR72 ();
	switch (CURRENT_TERMINAL) {
	  case 13:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 142 "lctsyntax.act"

	nstring_copy_cstring(&ZIctype,lct_token_buff);
#line 326 "lctsyntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  case 15:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR75 ();
	if ((CURRENT_TERMINAL) == 15) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (15);
    return;
}

static void
ZR51(void)
{
    if ((CURRENT_TERMINAL) == 15) {
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
	/* BEGINNING OF ACTION: E_expected_comma */
	{
#line 265 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected ','") ;
#line 372 "lctsyntax.c"
	}
	/* END OF ACTION: E_expected_comma */
    }
}

void
read_lct_unit(void)
{
    if ((CURRENT_TERMINAL) == 15) {
	return;
    }
    {
	ZRstatement_Hlist ();
	switch (CURRENT_TERMINAL) {
	  case 12:
	    break;
	  case 15:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E-syntax-error */
	{
#line 253 "lctsyntax.act"

	    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 405 "lctsyntax.c"
	}
	/* END OF ACTION: E-syntax-error */
    }
}

static void
ZR72(void)
{
    if ((CURRENT_TERMINAL) == 15) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 5:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E_expected_arrow */
	{
#line 274 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected '->'") ;

#line 435 "lctsyntax.c"
	}
	/* END OF ACTION: E_expected_arrow */
    }
}

static void
ZRstatement_Hlist(void)
{
  ZL2_statement_Hlist:;
    switch (CURRENT_TERMINAL) {
      case 0: case 1: case 2: case 3:
	{
	    ZRstatement ();
	    /* BEGINNING OF INLINE: statement-list */
	    if ((CURRENT_TERMINAL) == 15) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_statement_Hlist;
	    }
	    /* END OF INLINE: statement-list */
	}
	/*UNREACHED*/
      case 15:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (15);
    return;
}

static void
ZR74(void)
{
    if ((CURRENT_TERMINAL) == 15) {
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
	/* BEGINNING OF ACTION: E_expected_define */
	{
#line 269 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected '='") ;

#line 494 "lctsyntax.c"
	}
	/* END OF ACTION: E_expected_define */
    }
}

static void
ZR75(void)
{
    if ((CURRENT_TERMINAL) == 15) {
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
	/* BEGINNING OF ACTION: E_expected_semicolon */
	{
#line 279 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected ';'") ;
#line 523 "lctsyntax.c"
	}
	/* END OF ACTION: E_expected_semicolon */
    }
}

static void
ZR84(TypeTupleT *ZIa)
{
  ZL2_84:;
    switch (CURRENT_TERMINAL) {
      case 13:
	{
	    /* BEGINNING OF INLINE: action-definition::type-tuple::type-tuple1 */
	    {
		{
		    ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Hname (*ZIa);
		    /* BEGINNING OF INLINE: 84 */
		    if ((CURRENT_TERMINAL) == 15) {
			RESTORE_LEXER;
			goto ZL1;
		    } else {
			goto ZL2_84;
		    }
		    /* END OF INLINE: 84 */
		}
		/*UNREACHED*/
	    }
	    /* END OF INLINE: action-definition::type-tuple::type-tuple1 */
	}
	/*UNREACHED*/
      case 15:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (15);
    return;
}

static void
ZRheader_Hstmnt(void)
{
    if ((CURRENT_TERMINAL) == 15) {
	return;
    }
    {
	DStringT ZIsc;
	DStringT ZIsh;

	switch (CURRENT_TERMINAL) {
	  case 0:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR74 ();
	ZRcode_Hblock (&ZIsc);
	ZR51 ();
	ZRcode_Hblock (&ZIsh);
	if ((CURRENT_TERMINAL) == 15) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: set-headers */
	{
#line 152 "lctsyntax.act"

	if(!global_lct_parse_tree.trailersdefined) {
		global_lct_parse_tree.headersdefined = 1;
		dstring_to_nstring((&ZIsh),&(global_lct_parse_tree.hfileheader)) ;
		dstring_to_nstring((&ZIsc),&(global_lct_parse_tree.cfileheader)) ;
	} else {
		error(ERROR_SERIOUS, "Headers may not be redefined");
	}
	dstring_destroy((&ZIsc));
	dstring_destroy((&ZIsh));
#line 603 "lctsyntax.c"
	}
	/* END OF ACTION: set-headers */
	ZR75 ();
	if ((CURRENT_TERMINAL) == 15) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (15);
    return;
}

static void
ZRcode_Hblock(DStringT *ZOs)
{
    DStringT ZIs;

    if ((CURRENT_TERMINAL) == 15) {
	return;
    }
    {
	/* BEGINNING OF INLINE: 41 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 10:
		    break;
		  default:
		    goto ZL3;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_expected_code_start */
		{
#line 261 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected  '@{'") ;
#line 646 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_code_start */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 41 */
	/* BEGINNING OF ACTION: init-string */
	{
#line 148 "lctsyntax.act"

	dstring_init(&(ZIs));
#line 658 "lctsyntax.c"
	}
	/* END OF ACTION: init-string */
	ZRgrp_Hof_Hletters (&ZIs);
	/* BEGINNING OF INLINE: 42 */
	{
	    if ((CURRENT_TERMINAL) == 15) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 11:
		    break;
		  default:
		    goto ZL5;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL4;
	  ZL5:;
	    {
		/* BEGINNING OF ACTION: E_expected_code_end */
		{
#line 257 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected  '@}'") ;
#line 685 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_code_end */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 42 */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (15);
    return;
  ZL0:;
    /* BEGINNING OF RESULT ASSIGNMENT: BIGSTRING */
    {
#line 132 "lctsyntax.act"

	dstring_assign(ZOs,(&ZIs));
#line 703 "lctsyntax.c"
    }
    /* END OF RESULT ASSIGNMENT: BIGSTRING */
}

static void
ZRstatement(void)
{
    switch (CURRENT_TERMINAL) {
      case 3:
	{
	    ZRaction_Hdefinition ();
	    if ((CURRENT_TERMINAL) == 15) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 0:
	{
	    ZRheader_Hstmnt ();
	    if ((CURRENT_TERMINAL) == 15) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 2:
	{
	    ZRmap_Hstmnt ();
	    if ((CURRENT_TERMINAL) == 15) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1:
	{
	    ZRtrailer_Hstmnt ();
	    if ((CURRENT_TERMINAL) == 15) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 15:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (15);
    return;
}

static void
ZRtrailer_Hstmnt(void)
{
    if ((CURRENT_TERMINAL) == 15) {
	return;
    }
    {
	DStringT ZIsc;
	DStringT ZIsh;

	switch (CURRENT_TERMINAL) {
	  case 1:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR74 ();
	ZRcode_Hblock (&ZIsc);
	ZR51 ();
	ZRcode_Hblock (&ZIsh);
	if ((CURRENT_TERMINAL) == 15) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: set-trailers */
	{
#line 164 "lctsyntax.act"

	if(!(global_lct_parse_tree.trailersdefined)) {
		global_lct_parse_tree.trailersdefined = 1;
		dstring_to_nstring((&ZIsh),&(global_lct_parse_tree.hfiletrailer)) ;
		dstring_to_nstring((&ZIsc),&(global_lct_parse_tree.cfiletrailer)) ;
	} else {
		error(ERROR_SERIOUS, "Trailers may not be redefined");
	}
	dstring_destroy((&ZIsc));
	dstring_destroy((&ZIsh));
#line 797 "lctsyntax.c"
	}
	/* END OF ACTION: set-trailers */
	ZR75 ();
	if ((CURRENT_TERMINAL) == 15) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (15);
    return;
}

static void
ZRaction_Hdefinition(void)
{
    if ((CURRENT_TERMINAL) == 15) {
	return;
    }
    {
	NStringT ZInm;
	TypeTupleT ZIin;
	TypeTupleT ZIout;
	DStringT ZIc;

	switch (CURRENT_TERMINAL) {
	  case 3:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 13:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 142 "lctsyntax.act"

	nstring_copy_cstring(&ZInm,lct_token_buff);
#line 838 "lctsyntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRaction_Hdefinition_C_Cfunction_Htype_Hdefn (&ZIin, &ZIout);
	ZR74 ();
	ZRcode_Hblock (&ZIc);
	if ((CURRENT_TERMINAL) == 15) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: define-action */
	{
#line 201 "lctsyntax.act"

	EntryT* entry=table_get_entry(lxi_top_level->table,(&ZInm));
	nstring_destroy((&ZInm));
	if(entry) {
		if(entry_is_action(entry)) {
			ActionT* action = entry_get_action(entry);
			int types_errored=0;
			if(typetuple_length(action_get_inputs(action))!=typetuple_length((&ZIin))) {
				error(ERROR_SERIOUS,"Action %s decalared with an incopatible number of inputs", 
							     nstring_to_cstring((&ZInm)));
				types_errored=1;
			} else if(!typetuple_match(action_get_inputs(action),(&ZIin))) {
				error(ERROR_SERIOUS, "params do not match for action %s",nstring_to_cstring((&ZInm)));
				types_errored=1;
			} else {
				int allhavenames = typetuple_assign_names(action_get_inputs(action),(&ZIin));
				if(!allhavenames) {
					error(ERROR_SERIOUS,"outputs tuples in action definition should have names");
					types_errored=1;
				}
			}
			if(typetuple_length(action_get_outputs(action))!=typetuple_length((&ZIout))) {
				error(ERROR_SERIOUS,"Action %s decalared with an incompatible number of outputs", 
						     nstring_to_cstring((&ZInm)));
			} else if (!typetuple_match(action_get_outputs(action),(&ZIout))) {
				error(ERROR_SERIOUS, "results do not match for action %s",nstring_to_cstring((&ZInm)));
				types_errored=1;
			} else {				
				int allhavenames = typetuple_assign_names(action_get_outputs(action),(&ZIout));
				if(!allhavenames) {
					error(ERROR_SERIOUS,"outputs tuples in action definition should have names");
					types_errored=1;
				}
			}
			if(!types_errored) {
				if(action_is_defined(action))
					action_set_code(action,(&ZIc));
				else
					error(ERROR_SERIOUS,"Action %s has already been defined", nstring_to_cstring((&ZInm)));
			}
		} else {
			dstring_destroy((&ZIc));
			error(ERROR_SERIOUS,"%s is not an action", nstring_to_cstring((&ZInm)));
		}
	} else {
		dstring_destroy((&ZIc));
		error(ERROR_SERIOUS,"Defining an undeclared action: %s", nstring_to_cstring((&ZInm)));
	}
	typetuple_destroy((&ZIin));
	typetuple_destroy((&ZIout));	
#line 906 "lctsyntax.c"
	}
	/* END OF ACTION: define-action */
	ZR75 ();
	if ((CURRENT_TERMINAL) == 15) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (15);
    return;
}

static void
ZRaction_Hdefinition_C_Ctype_Htuple(TypeTupleT *ZOa)
{
    TypeTupleT ZIa;

    if ((CURRENT_TERMINAL) == 15) {
	return;
    }
    {
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 184 "lctsyntax.act"

	typetuple_init(&(ZIa));
#line 935 "lctsyntax.c"
	}
	/* END OF ACTION: init-tuple */
	ZR84 (&ZIa);
	if ((CURRENT_TERMINAL) == 15) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (15);
    return;
  ZL0:;
    *ZOa = ZIa;
}

/* BEGINNING OF TRAILER */

#line 287 "lctsyntax.act"


#line 957 "lctsyntax.c"

/* END OF FILE */
