/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 36 "syntax.act"

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

#include <string.h>
#include <stdio.h>

#include "error.h"
#include "xalloc.h"

#include "char.h"
#include "lex.h"
#include "syntax.h"


/*
    PARSER TYPES

    These types give the implementation of the types used in the syntax.
*/

typedef letter *SID_CHARS ;
typedef char *SID_STRING ;
/*typedef zone* zoneP; Done in syntax.h */
typedef instruction* instructionP ;
typedef instructions_list* instructions_listP ;
typedef arg* argP;
typedef args_list* args_listP;

/*
    SID IDENTIFIER PREFIX

    This string is added to the start of each sid identifier.
*/

char *sid_prefix = "lex_" ;


/*
    CURRENT CONDITIONAL

    This variable is used to record the current conditional.
*/

static char *crt_cond = NULL ;


/*
    COMPILATION MODE

    We allow unreached code in the automatically generated sections.
*/

#if FS_TENDRA
#pragma TenDRA begin
#ifndef OLD_PRODUCER
#pragma TenDRA unreachable code allow
#endif
#endif


#line 101 "tmp.syntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZR133(zoneP *);
static void ZR134(zoneP *);
static void ZR135(argP *, args_listP *);
static void ZR136(instructionP *, instructions_listP *);
static void ZRtuple_Hargs(args_listP *);
static void ZRzone_Hdefn(zoneP);
static void ZRstring_Hplus(SID_STRING *);
static void ZRchars(zoneP, SID_CHARS *);
static void ZRinstructions_Hlist(instructions_listP *);
static void ZRargs(args_listP *);
static void ZRtrigraph_Hdefn(zoneP);
extern void read_lex(zoneP);
static void ZRinstruction(instructionP *);
static void ZRcommand_Hlist(zoneP);
static void ZRkeyword_Hdefn(zoneP);
static void ZRif_Hcommand(zoneP);
static void ZRcommand(zoneP);
static void ZRnon_Hempty_Htuple_Hargs(args_listP *);
static void ZRnon_Hempty_Hchars(zoneP, SID_CHARS *);
static void ZRsingle_Harg(argP *);
static void ZR122(zoneP *, SID_CHARS *);
static void ZR124(instructions_listP *);

/* BEGINNING OF STATIC VARIABLES */

static int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZR133(zoneP *ZIz)
{
    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    SID_STRING ZIi;
	    SID_CHARS ZIs;

	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 174 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 148 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 21:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRchars (*ZIz, &ZIs);
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-group */
	    {
#line 313 "syntax.act"

    make_group ( (*ZIz), (ZIi), (ZIs) ) ;
#line 169 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-group */
	    switch (CURRENT_TERMINAL) {
	      case 23:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 10:
	{
	    SID_CHARS ZIs;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 21:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRchars (*ZIz, &ZIs);
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-white */
	    {
#line 299 "syntax.act"

    if ( (*ZIz)->white_space) {
	error ( ERROR_SERIOUS, "White space group already defined" ) ;
    }
    (*ZIz)->white_space= make_group((*ZIz),"white",(ZIs)) ;
#line 206 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-white */
	    switch (CURRENT_TERMINAL) {
	      case 23:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 34:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (34);
    return;
}

static void
ZR134(zoneP *ZIz)
{
    switch (CURRENT_TERMINAL) {
      case 11:
	{
	    instructions_listP ZIinst_Hlist;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 19:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (&ZIinst_Hlist);
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-default */
	    {
#line 420 "syntax.act"

    (*ZIz)->default_actions=(ZIinst_Hlist);
    (*ZIz)->default_cond=crt_cond;
#line 256 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-default */
	    switch (CURRENT_TERMINAL) {
	      case 23:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 2: case 3: case 4: case 5:
	{
	    SID_CHARS ZIs;
	    instructions_listP ZIinst_Hlist;

	    ZRnon_Hempty_Hchars (*ZIz, &ZIs);
	    switch (CURRENT_TERMINAL) {
	      case 19:
		break;
	      case 34:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (&ZIinst_Hlist);
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-token */
	    {
#line 403 "syntax.act"

        add_char ( (*ZIz), (*ZIz)->zone_main_pass, (ZIs), crt_cond, (ZIinst_Hlist), NULL) ;
#line 294 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-token */
	    switch (CURRENT_TERMINAL) {
	      case 23:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 34:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (34);
    return;
}

static void
ZR135(argP *ZIa, args_listP *ZOl)
{
    args_listP ZIl;

    switch (CURRENT_TERMINAL) {
      case 26:
	{
	    ADVANCE_LEXER;
	    ZRnon_Hempty_Htuple_Hargs (&ZIl);
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 355 "syntax.act"

    if((*ZIa)->next!= NULL) {
       if((*ZIa)->type==return_token || (*ZIa)->type==do_nothing) {
         error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an arg-list"); 
       }
    }
    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 342 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 368 "syntax.act"

    (ZIl)=add_args_list();
#line 354 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 355 "syntax.act"

    if((*ZIa)->next!= NULL) {
       if((*ZIa)->type==return_token || (*ZIa)->type==do_nothing) {
         error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an arg-list"); 
       }
    }
    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 368 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      case 34:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (34);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZR136(instructionP *ZIinst, instructions_listP *ZOinstl)
{
    instructions_listP ZIinstl;

    switch (CURRENT_TERMINAL) {
      case 26:
	{
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (&ZIinstl);
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: add-inst-to-list */
	    {
#line 382 "syntax.act"

	(*ZIinst)->next=(ZIinstl)->head;
	(ZIinstl)->head=(*ZIinst);
#line 404 "tmp.syntax.c"
	    }
	    /* END OF ACTION: add-inst-to-list */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-inst-list */
	    {
#line 392 "syntax.act"

    (ZIinstl)=add_instructions_list();
#line 416 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-inst-list */
	    /* BEGINNING OF ACTION: add-inst-to-list */
	    {
#line 382 "syntax.act"

	(*ZIinst)->next=(ZIinstl)->head;
	(ZIinstl)->head=(*ZIinst);
#line 425 "tmp.syntax.c"
	    }
	    /* END OF ACTION: add-inst-to-list */
	}
	break;
      case 34:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (34);
    return;
  ZL0:;
    *ZOinstl = ZIinstl;
}

static void
ZRtuple_Hargs(args_listP *ZOl)
{
    args_listP ZIl;

    switch (CURRENT_TERMINAL) {
      case 33:
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 368 "syntax.act"

    (ZIl)=add_args_list();
#line 455 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	}
	break;
      case 2: case 29: case 30: case 31: case 32:
	{
	    ZRnon_Hempty_Htuple_Hargs (&ZIl);
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    argP ZItmp;

	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 368 "syntax.act"

    (ZIl)=add_args_list();
#line 478 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: arg-char-list-tmp */
	    {
#line 348 "syntax.act"

      (ZItmp)=add_arg(arg_chars_list,0);
#line 486 "tmp.syntax.c"
	    }
	    /* END OF ACTION: arg-char-list-tmp */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 355 "syntax.act"

    if((ZItmp)->next!= NULL) {
       if((ZItmp)->type==return_token || (ZItmp)->type==do_nothing) {
         error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an arg-list"); 
       }
    }
    (ZItmp)->next=(ZIl)->head;
    (ZIl)->head=(ZItmp);
#line 500 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      case 34:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (34);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZRzone_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 34) {
	return;
    }
    {
	SID_STRING ZIzid;
	SID_CHARS ZIb;
	instructions_listP ZIentry_Hinstl;
	SID_CHARS ZIe;
	instructions_listP ZIleaving_Hinstl;
	zoneP ZInew_Hzone;

	switch (CURRENT_TERMINAL) {
	  case 12:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 115 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 0:
		    /* BEGINNING OF EXTRACT: identifier */
		    {
#line 174 "syntax.act"

    ZIzid = xstrcpy ( token_buff ) ;
#line 547 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: identifier */
		    break;
		  default:
		    goto ZL3;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_expected_identifier */
		{
#line 585 "syntax.act"

	(ZIzid)="";
	error(ERROR_SERIOUS, "Syntax error: expected identifier");
#line 565 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_identifier */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 115 */
	/* BEGINNING OF INLINE: 117 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 24:
		    break;
		  default:
		    goto ZL5;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL4;
	  ZL5:;
	    {
		/* BEGINNING OF ACTION: E_expected_colon */
		{
#line 599 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected colon \':\'");
#line 591 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_colon */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 117 */
	ZR122 (&ZIz, &ZIb);
	ZR124 (&ZIentry_Hinstl);
	/* BEGINNING OF INLINE: 121 */
	{
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 25:
		    break;
		  default:
		    goto ZL7;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL6;
	  ZL7:;
	    {
		/* BEGINNING OF ACTION: E_expected_range */
		{
#line 590 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected range");
#line 623 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_range */
	    }
	  ZL6:;
	}
	/* END OF INLINE: 121 */
	ZR122 (&ZIz, &ZIe);
	ZR124 (&ZIleaving_Hinstl);
	if ((CURRENT_TERMINAL) == 34) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-zone */
	{
#line 538 "syntax.act"

    instruction* inst;
    instructions_list* inst_list;
    (ZInew_Hzone)=add_zone((ZIz),(ZIzid),(ZIe));
    (ZInew_Hzone)->entering_instructions=(ZIentry_Hinstl);
    (ZInew_Hzone)->leaving_instructions=(ZIleaving_Hinstl);
    inst=add_instruction_pushzone((ZInew_Hzone));
    inst_list=add_instructions_list();
    *(inst_list->tail)=inst;
    inst_list->tail=&(inst->next);
    add_char ( (ZIz), (ZIz)->zone_main_pass, (ZIb), crt_cond, inst_list, NULL ) ;
#line 650 "tmp.syntax.c"
	}
	/* END OF ACTION: make-zone */
	switch (CURRENT_TERMINAL) {
	  case 17:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRcommand_Hlist (ZInew_Hzone);
	switch (CURRENT_TERMINAL) {
	  case 18:
	    break;
	  case 34:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    SAVE_LEXER (34);
    return;
}

static void
ZRstring_Hplus(SID_STRING *ZOs)
{
    SID_STRING ZIs;

    if ((CURRENT_TERMINAL) == 34) {
	return;
    }
    {
	SID_STRING ZIa;

	/* BEGINNING OF INLINE: 77 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 5:
		{
		    /* BEGINNING OF EXTRACT: digit */
		    {
#line 232 "syntax.act"
 ZIa = "0123456789" ; 
#line 698 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: digit */
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    /* BEGINNING OF EXTRACT: lower */
		    {
#line 231 "syntax.act"
 ZIa = "abcdefghijklmnopqrstuvwxyz" ; 
#line 710 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: lower */
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    /* BEGINNING OF EXTRACT: string */
		    {
#line 219 "syntax.act"

    ZIa = xstrcpy ( token_buff ) ;
#line 723 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: string */
		    ADVANCE_LEXER;
		}
		break;
	      case 3:
		{
		    /* BEGINNING OF EXTRACT: upper */
		    {
#line 230 "syntax.act"
 ZIa = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ; 
#line 735 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: upper */
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	/* END OF INLINE: 77 */
	/* BEGINNING OF INLINE: 79 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 22:
		{
		    SID_STRING ZIb;

		    ADVANCE_LEXER;
		    ZRstring_Hplus (&ZIb);
		    if ((CURRENT_TERMINAL) == 34) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    /* BEGINNING OF ACTION: string-concat */
		    {
#line 263 "syntax.act"

    (ZIs) = xstrcat ( (ZIa), (ZIb) ) ;
#line 764 "tmp.syntax.c"
		    }
		    /* END OF ACTION: string-concat */
		}
		break;
	      default:
		{
		    ZIs = ZIa;
		}
		break;
	    }
	}
	/* END OF INLINE: 79 */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (34);
    return;
  ZL0:;
    *ZOs = ZIs;
}

static void
ZRchars(zoneP ZIz, SID_CHARS *ZOc)
{
    SID_CHARS ZIc;

    if ((CURRENT_TERMINAL) == 34) {
	return;
    }
    {
	SID_STRING ZIs;

	ZRstring_Hplus (&ZIs);
	if ((CURRENT_TERMINAL) == 34) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-chars */
	{
#line 286 "syntax.act"

    (ZIc) = make_string ( (ZIs), (ZIz) ) ;
#line 807 "tmp.syntax.c"
	}
	/* END OF ACTION: make-chars */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (34);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRinstructions_Hlist(instructions_listP *ZOinstl)
{
    instructions_listP ZIinstl;

    if ((CURRENT_TERMINAL) == 34) {
	return;
    }
    {
	instructionP ZIinst;

	ZRinstruction (&ZIinst);
	ZR136 (&ZIinst, &ZIinstl);
	if ((CURRENT_TERMINAL) == 34) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (34);
    return;
  ZL0:;
    *ZOinstl = ZIinstl;
}

static void
ZRargs(args_listP *ZOl)
{
    args_listP ZIl;

    switch (CURRENT_TERMINAL) {
      case 15:
	{
	    ADVANCE_LEXER;
	    ZRtuple_Hargs (&ZIl);
	    switch (CURRENT_TERMINAL) {
	      case 16:
		break;
	      case 34:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: null-args-list */
	    {
#line 375 "syntax.act"

    (ZIl) = NULL ;
#line 874 "tmp.syntax.c"
	    }
	    /* END OF ACTION: null-args-list */
	}
	break;
      case 34:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (34);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZRtrigraph_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 34) {
	return;
    }
    {
	SID_CHARS ZIs;
	SID_STRING ZIt;

	switch (CURRENT_TERMINAL) {
	  case 8:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRchars (ZIz, &ZIs);
	switch (CURRENT_TERMINAL) {
	  case 19:
	    break;
	  case 34:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRstring_Hplus (&ZIt);
	if ((CURRENT_TERMINAL) == 34) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-trigraph */
	{
#line 324 "syntax.act"

    add_char ( (ZIz), (ZIz)->zone_pre_pass, (ZIs), crt_cond, NULL, (ZIt)) ;
#line 928 "tmp.syntax.c"
	}
	/* END OF ACTION: make-trigraph */
    }
    return;
  ZL1:;
    SAVE_LEXER (34);
    return;
}

void
read_lex(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 34) {
	return;
    }
    {
	ZRcommand_Hlist (ZIz);
	/* BEGINNING OF INLINE: 128 */
	{
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 20:
		    break;
		  default:
		    goto ZL3;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: syntax-error */
		{
#line 604 "syntax.act"

    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 969 "tmp.syntax.c"
		}
		/* END OF ACTION: syntax-error */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 128 */
    }
    return;
  ZL1:;
    SAVE_LEXER (34);
    return;
}

static void
ZRinstruction(instructionP *ZOinst)
{
    instructionP ZIinst;

    switch (CURRENT_TERMINAL) {
      case 0: case 1:
	{
	    SID_STRING ZIi;
	    args_listP ZIa;

	    /* BEGINNING OF INLINE: 100 */
	    {
		switch (CURRENT_TERMINAL) {
		  case 0:
		    {
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 174 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 1004 "tmp.syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			ZRargs (&ZIa);
			if ((CURRENT_TERMINAL) == 34) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  case 1:
		    {
			/* BEGINNING OF EXTRACT: sid-identifier */
			{
#line 186 "syntax.act"

    int n ;
    char *s ;
    char buff [1000] ;
    strcpy ( buff, sid_prefix ) ;
    n = ( int ) strlen ( buff ) ;
    for ( s = token_buff ; *s ; s++ ) {
	if ( *s == '-' ) {
	    buff [ n++ ] = '_' ;
	    buff [ n++ ] = 'H' ;
	} else if ( *s == '_' ) {
	    buff [ n++ ] = '_' ;
	    buff [ n++ ] = '_' ;
	} else {
	    buff [ n++ ] = *s ;
	}
	if ( n >= 900 ) {
	    error ( ERROR_SERIOUS, "Identifier too long" ) ;
	    break ;
	}
    }
    buff [n] = 0 ;
    ZIi = xstrcpy ( buff ) ;
#line 1043 "tmp.syntax.c"
			}
			/* END OF EXTRACT: sid-identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: null-args-list */
			{
#line 375 "syntax.act"

    (ZIa) = NULL ;
#line 1052 "tmp.syntax.c"
			}
			/* END OF ACTION: null-args-list */
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    /* END OF INLINE: 100 */
	    /* BEGINNING OF ACTION: make-inst */
	    {
#line 333 "syntax.act"

    if((ZIa)) {
        (ZIinst)=add_instruction_function((ZIi),(ZIa));
    } 
    else {
        (ZIinst)=add_instruction_return_token((ZIi));
    }
#line 1072 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-inst */
	}
	break;
      case 27:
	{
	    /* BEGINNING OF INLINE: 101 */
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 27:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: make-donothing-inst */
		    {
#line 342 "syntax.act"

	(ZIinst)=add_instruction_donothing();
#line 1094 "tmp.syntax.c"
		    }
		    /* END OF ACTION: make-donothing-inst */
		}
	    }
	    /* END OF INLINE: 101 */
	}
	break;
      case 34:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (34);
    return;
  ZL0:;
    *ZOinst = ZIinst;
}

static void
ZRcommand_Hlist(zoneP ZIz)
{
  ZL2_command_Hlist:;
    switch (CURRENT_TERMINAL) {
      case 6: case 7: case 8: case 9: case 12:
      case 13: case 17: case 23:
	{
	    ZRcommand (ZIz);
	    /* BEGINNING OF INLINE: command-list */
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_command_Hlist;
	    }
	    /* END OF INLINE: command-list */
	}
	/*UNREACHED*/
      case 34:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: syntax-error */
	{
#line 604 "syntax.act"

    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1147 "tmp.syntax.c"
	}
	/* END OF ACTION: syntax-error */
    }
}

static void
ZRkeyword_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 34) {
	return;
    }
    {
	SID_STRING ZIs;
	instructionP ZIinst;

	switch (CURRENT_TERMINAL) {
	  case 7:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 2:
	    /* BEGINNING OF EXTRACT: string */
	    {
#line 219 "syntax.act"

    ZIs = xstrcpy ( token_buff ) ;
#line 1177 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 19:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRinstruction (&ZIinst);
	/* BEGINNING OF INLINE: 108 */
	{
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 561 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 1205 "tmp.syntax.c"
		}
		/* END OF ACTION: is-global-zone */
		if (!ZI0)
		    goto ZL3;
		/* BEGINNING OF ACTION: make-keyword */
		{
#line 433 "syntax.act"

    switch((ZIinst)->type) {
    case apply_function:
      if((ZIinst)->u.fun->args->head==NULL) {
        error(ERROR_SERIOUS, "Syntax error: for keywords using "
	"user defined functions, "
	"the arglist must remain empty");
        break;
      }
    case return_token: 
    /* Fallback is intentional */
      add_keyword ( (ZIz), (ZIs), crt_cond, (ZIinst) ) ;
    break;
    default:
      error(ERROR_SERIOUS, "Syntax error: only a function or a token might be returned for a keyword");
  }
#line 1229 "tmp.syntax.c"
		}
		/* END OF ACTION: make-keyword */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonekeyword */
		{
#line 570 "syntax.act"

    error( ERROR_SERIOUS, "Keywords not yet implemented in a non global zone ") ;

#line 1242 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonekeyword */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 108 */
    }
    return;
  ZL1:;
    SAVE_LEXER (34);
    return;
}

static void
ZRif_Hcommand(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 34) {
	return;
    }
    {
	SID_STRING ZIi;
	SID_STRING ZIj;

	switch (CURRENT_TERMINAL) {
	  case 13:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 15:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 0:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 174 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 1287 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 16:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF ACTION: get-condition */
	{
#line 490 "syntax.act"

    (ZIj) = crt_cond ;
#line 1307 "tmp.syntax.c"
	}
	/* END OF ACTION: get-condition */
	/* BEGINNING OF ACTION: add-condition */
	{
#line 458 "syntax.act"

    if ( crt_cond ) {
	crt_cond = xstrcat ( crt_cond, xstrcat ( " && ", (ZIi) ) ) ;
    } else {
	crt_cond = (ZIi) ;
    }
#line 1319 "tmp.syntax.c"
	}
	/* END OF ACTION: add-condition */
	ZRcommand (ZIz);
	/* BEGINNING OF INLINE: 113 */
	{
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 14:
		    break;
		  default:
		    goto ZL3;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: compl-condition */
		{
#line 473 "syntax.act"

    if ( crt_cond ) {
	if ( strchr ( crt_cond, '&' ) ) {
	    crt_cond = xstrcat ( xstrcat ( "!( ", crt_cond ), " )" ) ;
	} else {
	    crt_cond = xstrcat ( "!", crt_cond ) ;
	}
    }
#line 1348 "tmp.syntax.c"
		}
		/* END OF ACTION: compl-condition */
		ZRcommand (ZIz);
		if ((CURRENT_TERMINAL) == 34) {
		    RESTORE_LEXER;
		    goto ZL3;
		}
		/* BEGINNING OF ACTION: set-condition */
		{
#line 501 "syntax.act"

    crt_cond = (ZIj) ;
#line 1361 "tmp.syntax.c"
		}
		/* END OF ACTION: set-condition */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: set-condition */
		{
#line 501 "syntax.act"

    crt_cond = (ZIj) ;
#line 1373 "tmp.syntax.c"
		}
		/* END OF ACTION: set-condition */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 113 */
    }
    return;
  ZL1:;
    SAVE_LEXER (34);
    return;
}

static void
ZRcommand(zoneP ZIz)
{
    switch (CURRENT_TERMINAL) {
      case 6:
	{
	    ADVANCE_LEXER;
	    ZR133 (&ZIz);
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 17:
	{
	    ADVANCE_LEXER;
	    ZRcommand_Hlist (ZIz);
	    switch (CURRENT_TERMINAL) {
	      case 18:
		break;
	      case 34:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 23:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 9:
	{
	    ADVANCE_LEXER;
	    ZR134 (&ZIz);
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 13:
	{
	    ZRif_Hcommand (ZIz);
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 7:
	{
	    ZRkeyword_Hdefn (ZIz);
	    switch (CURRENT_TERMINAL) {
	      case 23:
		break;
	      case 34:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 8:
	{
	    ZRtrigraph_Hdefn (ZIz);
	    switch (CURRENT_TERMINAL) {
	      case 23:
		break;
	      case 34:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 12:
	{
	    ZRzone_Hdefn (ZIz);
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 34:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (34);
    return;
}

static void
ZRnon_Hempty_Htuple_Hargs(args_listP *ZOl)
{
    args_listP ZIl;

    if ((CURRENT_TERMINAL) == 34) {
	return;
    }
    {
	argP ZIa;

	ZRsingle_Harg (&ZIa);
	ZR135 (&ZIa, &ZIl);
	if ((CURRENT_TERMINAL) == 34) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (34);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZRnon_Hempty_Hchars(zoneP ZIz, SID_CHARS *ZOc)
{
    SID_CHARS ZIc;

    if ((CURRENT_TERMINAL) == 34) {
	return;
    }
    {
	ZRchars (ZIz, &ZIc);
	/* BEGINNING OF INLINE: 86 */
	{
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-non-empty */
		{
#line 407 "syntax.act"

    (ZI0)=((ZIc)[0]!=(ZIz)->top_level->last_letter_code);
#line 1539 "tmp.syntax.c"
		}
		/* END OF ACTION: is-non-empty */
		if (!ZI0)
		    goto ZL3;
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_empty_character_string */
		{
#line 411 "syntax.act"

        error(ERROR_SERIOUS, "Empty character string is not allowed here, try using DEFAULT instead");	
#line 1553 "tmp.syntax.c"
		}
		/* END OF ACTION: E_empty_character_string */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 86 */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (34);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRsingle_Harg(argP *ZOa)
{
    argP ZIa;

    switch (CURRENT_TERMINAL) {
      case 29:
	{
	    /* BEGINNING OF EXTRACT: arg-char-list */
	    {
#line 237 "syntax.act"

      ZIa=add_arg(arg_chars_list,0);
#line 1582 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-list */
	    ADVANCE_LEXER;
	}
	break;
      case 31:
	{
	    /* BEGINNING OF EXTRACT: arg-char-nb */
	    {
#line 245 "syntax.act"

      ZIa=add_arg(arg_char_nb,number_buffer);
#line 1595 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-nb */
	    ADVANCE_LEXER;
	}
	break;
      case 30:
	{
	    /* BEGINNING OF EXTRACT: arg-char-string */
	    {
#line 241 "syntax.act"

      ZIa=add_arg(arg_charP,0);
#line 1608 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-string */
	    ADVANCE_LEXER;
	}
	break;
      case 32:
	{
	    /* BEGINNING OF EXTRACT: arg-nb-of-chars */
	    {
#line 249 "syntax.act"

      ZIa=add_arg(arg_nb_of_chars,0);
#line 1621 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-nb-of-chars */
	    ADVANCE_LEXER;
	}
	break;
      case 2:
	{
	    SID_STRING ZIb;

	    /* BEGINNING OF EXTRACT: string */
	    {
#line 219 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 1636 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_string */
	    {
#line 551 "syntax.act"

	(ZIa) = add_litteral_arg ((ZIb));
#line 1645 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_string */
	}
	break;
      case 34:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (34);
    return;
  ZL0:;
    *ZOa = ZIa;
}

static void
ZR122(zoneP *ZIz, SID_CHARS *ZOe)
{
    SID_CHARS ZIe;

    if ((CURRENT_TERMINAL) == 34) {
	return;
    }
    {
	ZRnon_Hempty_Hchars (*ZIz, &ZIe);
	if ((CURRENT_TERMINAL) == 34) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E_expected_chars */
	{
#line 594 "syntax.act"

        (ZIe) = NULL ;
	error(ERROR_SERIOUS, "Syntax error: expected characters");
#line 1687 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_chars */
    }
  ZL0:;
    *ZOe = ZIe;
}

static void
ZR124(instructions_listP *ZOleaving_Hinstl)
{
    instructions_listP ZIleaving_Hinstl;

    switch (CURRENT_TERMINAL) {
      case 19:
	{
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (&ZIleaving_Hinstl);
	    if ((CURRENT_TERMINAL) == 34) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-inst-list */
	    {
#line 392 "syntax.act"

    (ZIleaving_Hinstl)=add_instructions_list();
#line 1718 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-inst-list */
	}
	break;
      case 34:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (34);
    return;
  ZL0:;
    *ZOleaving_Hinstl = ZIleaving_Hinstl;
}

/* BEGINNING OF TRAILER */

#line 609 "syntax.act"

#line 1738 "tmp.syntax.c"

/* END OF FILE */
