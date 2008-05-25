/*
 * Automatically generated from the files:
 *	lctsyntax.sid
 * and
 *	lctsyntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 24 "lctsyntax.act"

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
 

#include <stdbool.h>

#include "lctsyntax.h"
#include "lctlex.h"
#include "char.h"
#include "ccode.h"
#include "adt.h"
#include "error/error.h"
#include "exds/common.h"
#include "exds/exception.h"
#include "exds/dalloc.h"
#include "exds/dstring.h"
#include "exds/cstring.h"

#define ADVANCE_LEXER ADVANCE_LCT_LEXER
#define CURRENT_TERMINAL CURRENT_LCT_TERMINAL 
#define SAVE_LEXER SAVE_LCT_LEXER
#define RESTORE_LEXER RESTORE_LCT_LEXER

typedef EntryT* EntryP;

lexer_parse_tree* lxi_top_level;

#line 70 "lctsyntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Hname(TypeTupleT *);
static void ZRaction_Hdefinition_C_Cfunction_Htype_Hdefn(TypeTupleT *, TypeTupleT *);
static void ZRcode_Hblock_C_Ccode_Helement(CcodeT *, EntryP);
static void ZRmap_Hstmnt(void);
extern void read_lct_unit(void);
static void ZR71(void);
static void ZRstatement_Hlist(void);
static void ZRcode_Hblock_C_Ccode_Hbody(CcodeT *, EntryP);
static void ZRheader_Hstmnt(void);
static void ZRcode_Hblock(EntryP, CcodeT *);
static void ZRstatement(void);
static void ZR94(void);
static void ZR96(void);
static void ZRtrailer_Hstmnt(void);
static void ZR97(void);
static void ZRaction_Hdefinition(void);
static void ZR104(TypeTupleT *);
static void ZRaction_Hdefinition_C_Ctype_Htuple(TypeTupleT *);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Hname(TypeTupleT *ZIa)
{
    if ((CURRENT_TERMINAL) == 20) {
	return;
    }
    {
	NStringT ZIname;
	NStringT ZItype;
	bool ZIisref;

	switch (CURRENT_TERMINAL) {
	  case 16:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 153 "lctsyntax.act"

	nstring_copy_cstring(&ZIname,lct_token_buff);
#line 116 "lctsyntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 5:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 16:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 153 "lctsyntax.act"

	nstring_copy_cstring(&ZItype,lct_token_buff);
#line 138 "lctsyntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 86 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 4:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: true */
		    {
#line 175 "lctsyntax.act"
 (ZIisref) = true ; 
#line 156 "lctsyntax.c"
		    }
		    /* END OF ACTION: true */
		}
		break;
	      default:
		{
		    /* BEGINNING OF ACTION: false */
		    {
#line 176 "lctsyntax.act"
 (ZIisref) = false ; 
#line 167 "lctsyntax.c"
		    }
		    /* END OF ACTION: false */
		}
		break;
	    }
	}
	/* END OF INLINE: 86 */
	/* BEGINNING OF ACTION: append-tuple */
	{
#line 249 "lctsyntax.act"

	EntryT* entry = table_get_entry(lxi_top_level->table,(&ZItype));
	if(entry == NULL) {
		 char* pt = nstring_to_cstring((&ZItype));
		 error(ERROR_SERIOUS, "Unknown type %s", pt);
		 DEALLOCATE(pt);
		 nstring_destroy((&ZIname));
		 nstring_destroy((&ZItype));
	}
	else if(!entry_is_type(entry))
		 error(ERROR_SERIOUS, "%s is not a type", (&ZItype));
	else
		typetuple_append((ZIa),typetupleentry_create((&ZIname),entry, (ZIisref)));
#line 191 "lctsyntax.c"
	}
	/* END OF ACTION: append-tuple */
    }
    return;
  ZL1:;
    SAVE_LEXER (20);
    return;
}

static void
ZRaction_Hdefinition_C_Cfunction_Htype_Hdefn(TypeTupleT *ZOin, TypeTupleT *ZOout)
{
    TypeTupleT ZIin;
    TypeTupleT ZIout;

    switch (CURRENT_TERMINAL) {
      case 6: case 16:
	{
	    ZRaction_Hdefinition_C_Ctype_Htuple (&ZIin);
	    ZR94 ();
	    ZRaction_Hdefinition_C_Ctype_Htuple (&ZIout);
	    if ((CURRENT_TERMINAL) == 20) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 245 "lctsyntax.act"

	typetuple_init(&(ZIin));
#line 226 "lctsyntax.c"
	    }
	    /* END OF ACTION: init-tuple */
	    /* BEGINNING OF ACTION: init-tuple */
	    {
#line 245 "lctsyntax.act"

	typetuple_init(&(ZIout));
#line 234 "lctsyntax.c"
	    }
	    /* END OF ACTION: init-tuple */
	}
	break;
      case 20:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (20);
    return;
  ZL0:;
    *ZOin = ZIin;
    *ZOout = ZIout;
}

static void
ZRcode_Hblock_C_Ccode_Helement(CcodeT *ZIc, EntryP ZIe)
{
    switch (CURRENT_TERMINAL) {
      case 13:
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-at */
	    {
#line 186 "lctsyntax.act"

	ccode_append_at(&(*ZIc));
#line 263 "lctsyntax.c"
	    }
	    /* END OF ACTION: append-ccode-at */
	}
	break;
      case 17:
	{
	    NStringT ZIi;

	    /* BEGINNING OF EXTRACT: code-identifier */
	    {
#line 157 "lctsyntax.act"

	nstring_copy_cstring(&ZIi,lct_token_buff);
#line 277 "lctsyntax.c"
	    }
	    /* END OF EXTRACT: code-identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-identifier */
	    {
#line 194 "lctsyntax.act"

	if((ZIe)) {
		ActionT* action = entry_get_action((ZIe));
	 	if (typetuple_name_is_in(action_get_inputs(action),(&ZIi)) || 
	       	   typetuple_name_is_in(action_get_outputs(action),(&ZIi))) {
			ccode_append_identifier((ZIc),(&ZIi));
		} else {
			char* pi = nstring_to_cstring((&ZIi));
			nstring_destroy((&ZIi));
			char* pe =  nstring_to_cstring(entry_key((ZIe)));
			error(ERROR_SERIOUS, "Identifier @%s is neither an input nor an output" 
					     "parameter of action %s", pi, pe );
			DEALLOCATE(pi);
			DEALLOCATE(pe);
		}
	} else {
		error(ERROR_SERIOUS, "The @ code identifiers are not allowed in headers or trailers");
		nstring_destroy((&ZIi));
	}
#line 303 "lctsyntax.c"
	    }
	    /* END OF ACTION: append-ccode-identifier */
	}
	break;
      case 18:
	{
	    NStringT ZIs;

	    /* BEGINNING OF EXTRACT: code-string */
	    {
#line 161 "lctsyntax.act"

	nstring_assign(&ZIs, &lct_token_nstring);
#line 317 "lctsyntax.c"
	    }
	    /* END OF EXTRACT: code-string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: append-ccode-string */
	    {
#line 190 "lctsyntax.act"

	ccode_append_string((ZIc),(&ZIs));
#line 326 "lctsyntax.c"
	    }
	    /* END OF ACTION: append-ccode-string */
	}
	break;
      case 12:
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: E_lone_at_in_code_block */
	    {
#line 396 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Lone @ inside @{ @} block") ;
#line 339 "lctsyntax.c"
	    }
	    /* END OF ACTION: E_lone_at_in_code_block */
	}
	break;
      case 20:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (20);
    return;
}

static void
ZRmap_Hstmnt(void)
{
    if ((CURRENT_TERMINAL) == 20) {
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
	  case 16:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 153 "lctsyntax.act"

	nstring_copy_cstring(&ZIlexitype,lct_token_buff);
#line 379 "lctsyntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR94 ();
	switch (CURRENT_TERMINAL) {
	  case 16:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 153 "lctsyntax.act"

	nstring_copy_cstring(&ZIctype,lct_token_buff);
#line 395 "lctsyntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  case 20:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF ACTION: make-map */
	{
#line 264 "lctsyntax.act"

	EntryT* entry= table_get_entry(lxi_top_level->table,(&ZIlexitype));
	if(entry !=NULL) {
		if(entry_is_type(entry)) {
			TypeT* type = entry_get_type(entry);
			type_map(type, (&ZIctype));
		} else {
			error(ERROR_SERIOUS, "Name in maps section is not a type");
			nstring_destroy((&ZIctype));
		}
	} else {
		error(ERROR_SERIOUS, "Unknown type in mapping");
		nstring_destroy((&ZIctype));
	}
	nstring_destroy((&ZIlexitype));
#line 424 "lctsyntax.c"
	}
	/* END OF ACTION: make-map */
	ZR97 ();
	if ((CURRENT_TERMINAL) == 20) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (20);
    return;
}

void
read_lct_unit(void)
{
    if ((CURRENT_TERMINAL) == 20) {
	return;
    }
    {
	ZRstatement_Hlist ();
	switch (CURRENT_TERMINAL) {
	  case 15:
	    break;
	  case 20:
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
#line 362 "lctsyntax.act"

	    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 466 "lctsyntax.c"
	}
	/* END OF ACTION: E-syntax-error */
    }
}

static void
ZR71(void)
{
    if ((CURRENT_TERMINAL) == 20) {
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
#line 374 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected ','") ;
#line 495 "lctsyntax.c"
	}
	/* END OF ACTION: E_expected_comma */
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
	    if ((CURRENT_TERMINAL) == 20) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_statement_Hlist;
	    }
	    /* END OF INLINE: statement-list */
	}
	/*UNREACHED*/
      case 20:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (20);
    return;
}

static void
ZRcode_Hblock_C_Ccode_Hbody(CcodeT *ZIc, EntryP ZIe)
{
  ZL2_code_Hblock_C_Ccode_Hbody:;
    switch (CURRENT_TERMINAL) {
      case 12: case 13: case 17: case 18:
	{
	    ZRcode_Hblock_C_Ccode_Helement (ZIc, ZIe);
	    /* BEGINNING OF INLINE: code-block::code-body */
	    if ((CURRENT_TERMINAL) == 20) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_code_Hblock_C_Ccode_Hbody;
	    }
	    /* END OF INLINE: code-block::code-body */
	}
	/*UNREACHED*/
      case 20:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (20);
    return;
}

static void
ZRheader_Hstmnt(void)
{
    if ((CURRENT_TERMINAL) == 20) {
	return;
    }
    {
	EntryP ZIe;
	CcodeT ZIsc;
	CcodeT ZIsh;

	switch (CURRENT_TERMINAL) {
	  case 0:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR96 ();
	if ((CURRENT_TERMINAL) == 20) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: null-entry */
	{
#line 300 "lctsyntax.act"

	(ZIe)=NULL;
#line 587 "lctsyntax.c"
	}
	/* END OF ACTION: null-entry */
	ZRcode_Hblock (ZIe, &ZIsc);
	ZR71 ();
	ZRcode_Hblock (ZIe, &ZIsh);
	if ((CURRENT_TERMINAL) == 20) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: set-headers */
	{
#line 216 "lctsyntax.act"

	if(!global_lct_parse_tree.trailersdefined) {
		global_lct_parse_tree.headersdefined = 1;
		ccode_assign(&(global_lct_parse_tree.hfileheader),(&ZIsh)) ;
		ccode_assign(&(global_lct_parse_tree.cfileheader),(&ZIsc)) ;
	} else {
		error(ERROR_SERIOUS, "Headers may not be redefined");
		ccode_destroy((&ZIsc));
		ccode_destroy((&ZIsh));
	}
#line 610 "lctsyntax.c"
	}
	/* END OF ACTION: set-headers */
	ZR97 ();
	if ((CURRENT_TERMINAL) == 20) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (20);
    return;
}

static void
ZRcode_Hblock(EntryP ZIe, CcodeT *ZOc)
{
    CcodeT ZIc;

    if ((CURRENT_TERMINAL) == 20) {
	return;
    }
    {
	/* BEGINNING OF INLINE: 60 */
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
#line 370 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected  '@{'") ;
#line 653 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_code_start */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 60 */
	/* BEGINNING OF ACTION: init-ccode */
	{
#line 182 "lctsyntax.act"

	ccode_init(&(ZIc));
#line 665 "lctsyntax.c"
	}
	/* END OF ACTION: init-ccode */
	ZRcode_Hblock_C_Ccode_Hbody (&ZIc, ZIe);
	/* BEGINNING OF INLINE: 61 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 14:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: E_unexpected_eof */
		    {
#line 392 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Unexpected End of File inside @{ @} block") ;
#line 680 "lctsyntax.c"
		    }
		    /* END OF ACTION: E_unexpected_eof */
		}
		break;
	      case 20:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
	/* END OF INLINE: 61 */
	/* BEGINNING OF INLINE: 62 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 11:
		    break;
		  default:
		    goto ZL6;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL5;
	  ZL6:;
	    {
		/* BEGINNING OF ACTION: E_expected_code_end */
		{
#line 366 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected  '@}'") ;
#line 712 "lctsyntax.c"
		}
		/* END OF ACTION: E_expected_code_end */
	    }
	  ZL5:;
	}
	/* END OF INLINE: 62 */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (20);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRstatement(void)
{
    switch (CURRENT_TERMINAL) {
      case 3:
	{
	    ZRaction_Hdefinition ();
	    if ((CURRENT_TERMINAL) == 20) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 0:
	{
	    ZRheader_Hstmnt ();
	    if ((CURRENT_TERMINAL) == 20) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 2:
	{
	    ZRmap_Hstmnt ();
	    if ((CURRENT_TERMINAL) == 20) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1:
	{
	    ZRtrailer_Hstmnt ();
	    if ((CURRENT_TERMINAL) == 20) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 20:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (20);
    return;
}

static void
ZR94(void)
{
    if ((CURRENT_TERMINAL) == 20) {
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
	/* BEGINNING OF ACTION: E_expected_arrow */
	{
#line 383 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected '->'") ;
#line 802 "lctsyntax.c"
	}
	/* END OF ACTION: E_expected_arrow */
    }
}

static void
ZR96(void)
{
    if ((CURRENT_TERMINAL) == 20) {
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
#line 378 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected '='") ;

#line 832 "lctsyntax.c"
	}
	/* END OF ACTION: E_expected_define */
    }
}

static void
ZRtrailer_Hstmnt(void)
{
    if ((CURRENT_TERMINAL) == 20) {
	return;
    }
    {
	EntryP ZIe;
	CcodeT ZIsc;
	CcodeT ZIsh;

	switch (CURRENT_TERMINAL) {
	  case 1:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR96 ();
	if ((CURRENT_TERMINAL) == 20) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: null-entry */
	{
#line 300 "lctsyntax.act"

	(ZIe)=NULL;
#line 866 "lctsyntax.c"
	}
	/* END OF ACTION: null-entry */
	ZRcode_Hblock (ZIe, &ZIsc);
	ZR71 ();
	ZRcode_Hblock (ZIe, &ZIsh);
	if ((CURRENT_TERMINAL) == 20) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: set-trailers */
	{
#line 228 "lctsyntax.act"

	if(!(global_lct_parse_tree.trailersdefined)) {
		global_lct_parse_tree.trailersdefined = 1;
		ccode_assign(&(global_lct_parse_tree.hfiletrailer),(&ZIsh)) ;
		ccode_assign(&(global_lct_parse_tree.cfiletrailer),(&ZIsc)) ;
	} else {
		error(ERROR_SERIOUS, "Trailers may not be redefined");
		ccode_destroy((&ZIsc));
		ccode_destroy((&ZIsh));
	}
#line 889 "lctsyntax.c"
	}
	/* END OF ACTION: set-trailers */
	ZR97 ();
	if ((CURRENT_TERMINAL) == 20) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (20);
    return;
}

static void
ZR97(void)
{
    if ((CURRENT_TERMINAL) == 20) {
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
#line 387 "lctsyntax.act"

	    error( ERROR_SERIOUS, "Syntax error: expected ';'") ;
#line 927 "lctsyntax.c"
	}
	/* END OF ACTION: E_expected_semicolon */
    }
}

static void
ZRaction_Hdefinition(void)
{
    if ((CURRENT_TERMINAL) == 20) {
	return;
    }
    {
	NStringT ZInm;
	TypeTupleT ZIin;
	TypeTupleT ZIout;
	EntryP ZIe;
	CcodeT ZIc;

	switch (CURRENT_TERMINAL) {
	  case 3:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 16:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 153 "lctsyntax.act"

	nstring_copy_cstring(&ZInm,lct_token_buff);
#line 960 "lctsyntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRaction_Hdefinition_C_Cfunction_Htype_Hdefn (&ZIin, &ZIout);
	ZR96 ();
	if ((CURRENT_TERMINAL) == 20) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: get-entry-action */
	{
#line 282 "lctsyntax.act"

	(ZIe)=table_get_entry(lxi_top_level->table,(&ZInm));
	nstring_destroy((&ZInm));
	if((ZIe)) {
		if(!entry_is_action((ZIe))) {
			(ZIe)=NULL; /*TODO skip to end of action */
			char* pi = nstring_to_cstring((&ZInm));
			error(ERROR_SERIOUS,"%s is not an action", pi);
			DEALLOCATE(pi);
		}
	} else {
		char* pi = nstring_to_cstring((&ZInm));		
		error(ERROR_SERIOUS,"Defining an undeclared action: %s", pi);
		DEALLOCATE(pi);
	}
		nstring_destroy((&ZInm));
#line 993 "lctsyntax.c"
	}
	/* END OF ACTION: get-entry-action */
	/* BEGINNING OF ACTION: check-action-tuples */
	{
#line 304 "lctsyntax.act"

	if((ZIe)) {
		/*TODO assert (entry_is_action((ZIe))); */	       
		ActionT* action = entry_get_action((ZIe));
		if(typetuple_length(action_get_inputs(action))!=typetuple_length((&ZIin))) {
			char* pe=nstring_to_cstring(entry_key((ZIe)));
			error(ERROR_SERIOUS,"Action %s declared with an incompatible number of inputs", pe);
			DEALLOCATE(pe);
		} else if(!typetuple_match(action_get_inputs(action),(&ZIin))) {
			char* pe=nstring_to_cstring(entry_key((ZIe)));
			error(ERROR_SERIOUS, "params do not match for action %s",pe);
			DEALLOCATE(pe);
		} else {
			int allhavenames = typetuple_assign_names(action_get_inputs(action),(&ZIin));
			if(!allhavenames) {
				error(ERROR_SERIOUS,"outputs tuples in action definition should have names");
			}
		}
		if(typetuple_length(action_get_outputs(action))!=typetuple_length((&ZIout))) {
			char* pe=nstring_to_cstring(entry_key((ZIe)));
			error(ERROR_SERIOUS,"Action %s decalared with an incompatible number of outputs", pe);
			DEALLOCATE(pe);
		} else if (!typetuple_match(action_get_outputs(action),(&ZIout))) {
			char* pe=nstring_to_cstring(entry_key((ZIe)));
			error(ERROR_SERIOUS, "results do not match for action %s",pe);
			DEALLOCATE(pe);
		} else {				
			int allhavenames = typetuple_assign_names(action_get_outputs(action),(&ZIout));
			if(!allhavenames) {
			char* pe=nstring_to_cstring(entry_key((ZIe)));
				error(ERROR_SERIOUS,"outputs tuples in the definition of action %s should have names",pe);
			DEALLOCATE(pe);
			}
		}
	}
	typetuple_destroy((&ZIin));
	typetuple_destroy((&ZIout));
#line 1036 "lctsyntax.c"
	}
	/* END OF ACTION: check-action-tuples */
	ZRcode_Hblock (ZIe, &ZIc);
	if ((CURRENT_TERMINAL) == 20) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: define-action */
	{
#line 344 "lctsyntax.act"

	if((ZIe)) {
	       /*TODO assert entry_is_action */	       
	        ActionT* action = entry_get_action((ZIe));
			if(action_is_defined(action)) {
				action_set_define(action);
				action_set_code(action, (&ZIc));
			}
			else {
				char* pe=nstring_to_cstring(entry_key((ZIe)));
				error(ERROR_SERIOUS,"Action %s has already been defined", pe);
				DEALLOCATE(pe);
			}
	} else {
		ccode_destroy((&ZIc));
	}
#line 1063 "lctsyntax.c"
	}
	/* END OF ACTION: define-action */
	ZR97 ();
	if ((CURRENT_TERMINAL) == 20) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (20);
    return;
}

static void
ZR104(TypeTupleT *ZIa)
{
  ZL2_104:;
    switch (CURRENT_TERMINAL) {
      case 16:
	{
	    /* BEGINNING OF INLINE: action-definition::type-tuple::type-tuple1 */
	    {
		{
		    ZRaction_Hdefinition_C_Ctype_Htuple_C_Ctype_Hname (ZIa);
		    /* BEGINNING OF INLINE: 104 */
		    if ((CURRENT_TERMINAL) == 20) {
			RESTORE_LEXER;
			goto ZL1;
		    } else {
			goto ZL2_104;
		    }
		    /* END OF INLINE: 104 */
		}
		/*UNREACHED*/
	    }
	    /* END OF INLINE: action-definition::type-tuple::type-tuple1 */
	}
	/*UNREACHED*/
      case 20:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (20);
    return;
}

static void
ZRaction_Hdefinition_C_Ctype_Htuple(TypeTupleT *ZOa)
{
    TypeTupleT ZIa;

    if ((CURRENT_TERMINAL) == 20) {
	return;
    }
    {
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 245 "lctsyntax.act"

	typetuple_init(&(ZIa));
#line 1128 "lctsyntax.c"
	}
	/* END OF ACTION: init-tuple */
	ZR104 (&ZIa);
	if ((CURRENT_TERMINAL) == 20) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (20);
    return;
  ZL0:;
    *ZOa = ZIa;
}

/* BEGINNING OF TRAILER */

#line 402 "lctsyntax.act"


#line 1150 "lctsyntax.c"

/* END OF FILE */
