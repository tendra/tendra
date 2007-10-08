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

static void ZR131(zoneP *);
static void ZR132(zoneP *);
static void ZR133(argP *, args_listP *);
static void ZR134(instructionP *, instructions_listP *);
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
static void ZR120(zoneP *, SID_CHARS *);
static void ZR122(instructions_listP *);

/* BEGINNING OF STATIC VARIABLES */

static int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZR131(zoneP *ZIz)
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
#line 147 "tmp.syntax.c"
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
	    if ((CURRENT_TERMINAL) == 33) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-group */
	    {
#line 309 "syntax.act"

    make_group ( (*ZIz), (ZIi), (ZIs) ) ;
#line 168 "tmp.syntax.c"
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
	    if ((CURRENT_TERMINAL) == 33) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-white */
	    {
#line 295 "syntax.act"

    if ( (*ZIz)->white_space) {
	error ( ERROR_SERIOUS, "White space group already defined" ) ;
    }
    (*ZIz)->white_space= make_group((*ZIz),"white",(ZIs)) ;
#line 205 "tmp.syntax.c"
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
      case 33:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (33);
    return;
}

static void
ZR132(zoneP *ZIz)
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
	    if ((CURRENT_TERMINAL) == 33) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-default */
	    {
#line 411 "syntax.act"

    (*ZIz)->default_actions=(ZIinst_Hlist);
    (*ZIz)->default_cond=crt_cond;
#line 255 "tmp.syntax.c"
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
	      case 33:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (&ZIinst_Hlist);
	    if ((CURRENT_TERMINAL) == 33) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-token */
	    {
#line 394 "syntax.act"

        add_char ( (*ZIz), (*ZIz)->zone_main_pass, (ZIs), crt_cond, (ZIinst_Hlist), NULL) ;
#line 293 "tmp.syntax.c"
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
      case 33:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (33);
    return;
}

static void
ZR133(argP *ZIa, args_listP *ZOl)
{
    args_listP ZIl;

    switch (CURRENT_TERMINAL) {
      case 26:
	{
	    ADVANCE_LEXER;
	    ZRnon_Hempty_Htuple_Hargs (&ZIl);
	    if ((CURRENT_TERMINAL) == 33) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 351 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 336 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 359 "syntax.act"

    (ZIl)=add_args_list();
#line 348 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 351 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 357 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      case 33:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (33);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZR134(instructionP *ZIinst, instructions_listP *ZOinstl)
{
    instructions_listP ZIinstl;

    switch (CURRENT_TERMINAL) {
      case 26:
	{
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (&ZIinstl);
	    if ((CURRENT_TERMINAL) == 33) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: add-inst-to-list */
	    {
#line 373 "syntax.act"

	(*ZIinst)->next=(ZIinstl)->head;
	(ZIinstl)->head=(*ZIinst);
#line 393 "tmp.syntax.c"
	    }
	    /* END OF ACTION: add-inst-to-list */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-inst-list */
	    {
#line 383 "syntax.act"

    (ZIinstl)=add_instructions_list();
#line 405 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-inst-list */
	    /* BEGINNING OF ACTION: add-inst-to-list */
	    {
#line 373 "syntax.act"

	(*ZIinst)->next=(ZIinstl)->head;
	(ZIinstl)->head=(*ZIinst);
#line 414 "tmp.syntax.c"
	    }
	    /* END OF ACTION: add-inst-to-list */
	}
	break;
      case 33:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (33);
    return;
  ZL0:;
    *ZOinstl = ZIinstl;
}

static void
ZRtuple_Hargs(args_listP *ZOl)
{
    args_listP ZIl;

    switch (CURRENT_TERMINAL) {
      case 32:
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 359 "syntax.act"

    (ZIl)=add_args_list();
#line 444 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	}
	break;
      case 29: case 30: case 31:
	{
	    ZRnon_Hempty_Htuple_Hargs (&ZIl);
	    if ((CURRENT_TERMINAL) == 33) {
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
#line 359 "syntax.act"

    (ZIl)=add_args_list();
#line 467 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: arg-char-list-tmp */
	    {
#line 344 "syntax.act"

      (ZItmp)=add_arg(arg_chars_list,0);
#line 475 "tmp.syntax.c"
	    }
	    /* END OF ACTION: arg-char-list-tmp */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 351 "syntax.act"

    (ZItmp)->next=(ZIl)->head;
    (ZIl)->head=(ZItmp);
#line 484 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      case 33:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (33);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZRzone_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 33) {
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
	/* BEGINNING OF INLINE: 113 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 0:
		    /* BEGINNING OF EXTRACT: identifier */
		    {
#line 174 "syntax.act"

    ZIzid = xstrcpy ( token_buff ) ;
#line 531 "tmp.syntax.c"
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
#line 571 "syntax.act"

	(ZIzid)="";
	error(ERROR_SERIOUS, "Syntax error: expected identifier");
#line 549 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_identifier */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 113 */
	/* BEGINNING OF INLINE: 115 */
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
#line 585 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected colon \':\'");
#line 575 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_colon */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 115 */
	ZR120 (&ZIz, &ZIb);
	ZR122 (&ZIentry_Hinstl);
	/* BEGINNING OF INLINE: 119 */
	{
	    if ((CURRENT_TERMINAL) == 33) {
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
#line 576 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected range");
#line 607 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_range */
	    }
	  ZL6:;
	}
	/* END OF INLINE: 119 */
	ZR120 (&ZIz, &ZIe);
	ZR122 (&ZIleaving_Hinstl);
	if ((CURRENT_TERMINAL) == 33) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-zone */
	{
#line 529 "syntax.act"

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
#line 634 "tmp.syntax.c"
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
	  case 33:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    SAVE_LEXER (33);
    return;
}

static void
ZRstring_Hplus(SID_STRING *ZOs)
{
    SID_STRING ZIs;

    if ((CURRENT_TERMINAL) == 33) {
	return;
    }
    {
	SID_STRING ZIa;

	/* BEGINNING OF INLINE: 75 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 5:
		{
		    /* BEGINNING OF EXTRACT: digit */
		    {
#line 232 "syntax.act"
 ZIa = "0123456789" ; 
#line 682 "tmp.syntax.c"
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
#line 694 "tmp.syntax.c"
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
#line 707 "tmp.syntax.c"
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
#line 719 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: upper */
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	/* END OF INLINE: 75 */
	/* BEGINNING OF INLINE: 77 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 22:
		{
		    SID_STRING ZIb;

		    ADVANCE_LEXER;
		    ZRstring_Hplus (&ZIb);
		    if ((CURRENT_TERMINAL) == 33) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    /* BEGINNING OF ACTION: string-concat */
		    {
#line 259 "syntax.act"

    (ZIs) = xstrcat ( (ZIa), (ZIb) ) ;
#line 748 "tmp.syntax.c"
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
	/* END OF INLINE: 77 */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (33);
    return;
  ZL0:;
    *ZOs = ZIs;
}

static void
ZRchars(zoneP ZIz, SID_CHARS *ZOc)
{
    SID_CHARS ZIc;

    if ((CURRENT_TERMINAL) == 33) {
	return;
    }
    {
	SID_STRING ZIs;

	ZRstring_Hplus (&ZIs);
	if ((CURRENT_TERMINAL) == 33) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-chars */
	{
#line 282 "syntax.act"

    (ZIc) = make_string ( (ZIs), (ZIz) ) ;
#line 791 "tmp.syntax.c"
	}
	/* END OF ACTION: make-chars */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (33);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRinstructions_Hlist(instructions_listP *ZOinstl)
{
    instructions_listP ZIinstl;

    if ((CURRENT_TERMINAL) == 33) {
	return;
    }
    {
	instructionP ZIinst;

	ZRinstruction (&ZIinst);
	ZR134 (&ZIinst, &ZIinstl);
	if ((CURRENT_TERMINAL) == 33) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (33);
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
	      case 33:
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
#line 366 "syntax.act"

    (ZIl) = NULL ;
#line 858 "tmp.syntax.c"
	    }
	    /* END OF ACTION: null-args-list */
	}
	break;
      case 33:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (33);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZRtrigraph_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 33) {
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
	  case 33:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRstring_Hplus (&ZIt);
	if ((CURRENT_TERMINAL) == 33) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-trigraph */
	{
#line 320 "syntax.act"

    add_char ( (ZIz), (ZIz)->zone_pre_pass, (ZIs), crt_cond, NULL, (ZIt)) ;
#line 912 "tmp.syntax.c"
	}
	/* END OF ACTION: make-trigraph */
    }
    return;
  ZL1:;
    SAVE_LEXER (33);
    return;
}

void
read_lex(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 33) {
	return;
    }
    {
	ZRcommand_Hlist (ZIz);
	/* BEGINNING OF INLINE: 126 */
	{
	    if ((CURRENT_TERMINAL) == 33) {
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
#line 590 "syntax.act"

    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 953 "tmp.syntax.c"
		}
		/* END OF ACTION: syntax-error */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 126 */
    }
    return;
  ZL1:;
    SAVE_LEXER (33);
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

	    /* BEGINNING OF INLINE: 98 */
	    {
		switch (CURRENT_TERMINAL) {
		  case 0:
		    {
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 174 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 988 "tmp.syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			ZRargs (&ZIa);
			if ((CURRENT_TERMINAL) == 33) {
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
#line 1027 "tmp.syntax.c"
			}
			/* END OF EXTRACT: sid-identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: null-args-list */
			{
#line 366 "syntax.act"

    (ZIa) = NULL ;
#line 1036 "tmp.syntax.c"
			}
			/* END OF ACTION: null-args-list */
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    /* END OF INLINE: 98 */
	    /* BEGINNING OF ACTION: make-inst */
	    {
#line 329 "syntax.act"

    if((ZIa)) {
        (ZIinst)=add_instruction_function((ZIi),(ZIa));
    } 
    else {
        (ZIinst)=add_instruction_return_token((ZIi));
    }
#line 1056 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-inst */
	}
	break;
      case 27:
	{
	    /* BEGINNING OF INLINE: 99 */
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
#line 338 "syntax.act"

	(ZIinst)=add_instruction_donothing();
#line 1078 "tmp.syntax.c"
		    }
		    /* END OF ACTION: make-donothing-inst */
		}
	    }
	    /* END OF INLINE: 99 */
	}
	break;
      case 33:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (33);
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
	    if ((CURRENT_TERMINAL) == 33) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_command_Hlist;
	    }
	    /* END OF INLINE: command-list */
	}
	/*UNREACHED*/
      case 33:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: syntax-error */
	{
#line 590 "syntax.act"

    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1131 "tmp.syntax.c"
	}
	/* END OF ACTION: syntax-error */
    }
}

static void
ZRkeyword_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 33) {
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
#line 1161 "tmp.syntax.c"
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
	/* BEGINNING OF INLINE: 106 */
	{
	    if ((CURRENT_TERMINAL) == 33) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 547 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 1189 "tmp.syntax.c"
		}
		/* END OF ACTION: is-global-zone */
		if (!ZI0)
		    goto ZL3;
		/* BEGINNING OF ACTION: make-keyword */
		{
#line 424 "syntax.act"

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
#line 1213 "tmp.syntax.c"
		}
		/* END OF ACTION: make-keyword */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonekeyword */
		{
#line 556 "syntax.act"

    error( ERROR_SERIOUS, "Keywords not yet implemented in a non global zone ") ;

#line 1226 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonekeyword */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 106 */
    }
    return;
  ZL1:;
    SAVE_LEXER (33);
    return;
}

static void
ZRif_Hcommand(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 33) {
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
#line 1271 "tmp.syntax.c"
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
#line 481 "syntax.act"

    (ZIj) = crt_cond ;
#line 1291 "tmp.syntax.c"
	}
	/* END OF ACTION: get-condition */
	/* BEGINNING OF ACTION: add-condition */
	{
#line 449 "syntax.act"

    if ( crt_cond ) {
	crt_cond = xstrcat ( crt_cond, xstrcat ( " && ", (ZIi) ) ) ;
    } else {
	crt_cond = (ZIi) ;
    }
#line 1303 "tmp.syntax.c"
	}
	/* END OF ACTION: add-condition */
	ZRcommand (ZIz);
	/* BEGINNING OF INLINE: 111 */
	{
	    if ((CURRENT_TERMINAL) == 33) {
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
#line 464 "syntax.act"

    if ( crt_cond ) {
	if ( strchr ( crt_cond, '&' ) ) {
	    crt_cond = xstrcat ( xstrcat ( "!( ", crt_cond ), " )" ) ;
	} else {
	    crt_cond = xstrcat ( "!", crt_cond ) ;
	}
    }
#line 1332 "tmp.syntax.c"
		}
		/* END OF ACTION: compl-condition */
		ZRcommand (ZIz);
		if ((CURRENT_TERMINAL) == 33) {
		    RESTORE_LEXER;
		    goto ZL3;
		}
		/* BEGINNING OF ACTION: set-condition */
		{
#line 492 "syntax.act"

    crt_cond = (ZIj) ;
#line 1345 "tmp.syntax.c"
		}
		/* END OF ACTION: set-condition */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: set-condition */
		{
#line 492 "syntax.act"

    crt_cond = (ZIj) ;
#line 1357 "tmp.syntax.c"
		}
		/* END OF ACTION: set-condition */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 111 */
    }
    return;
  ZL1:;
    SAVE_LEXER (33);
    return;
}

static void
ZRcommand(zoneP ZIz)
{
    switch (CURRENT_TERMINAL) {
      case 6:
	{
	    ADVANCE_LEXER;
	    ZR131 (&ZIz);
	    if ((CURRENT_TERMINAL) == 33) {
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
	      case 33:
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
	    ZR132 (&ZIz);
	    if ((CURRENT_TERMINAL) == 33) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 13:
	{
	    ZRif_Hcommand (ZIz);
	    if ((CURRENT_TERMINAL) == 33) {
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
	      case 33:
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
	      case 33:
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
	    if ((CURRENT_TERMINAL) == 33) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 33:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (33);
    return;
}

static void
ZRnon_Hempty_Htuple_Hargs(args_listP *ZOl)
{
    args_listP ZIl;

    if ((CURRENT_TERMINAL) == 33) {
	return;
    }
    {
	argP ZIa;

	/* BEGINNING OF INLINE: single-arg */
	{
	    switch (CURRENT_TERMINAL) {
	      case 29:
		{
		    /* BEGINNING OF EXTRACT: arg-char-list */
		    {
#line 237 "syntax.act"

      ZIa=add_arg(arg_chars_list,0);
#line 1496 "tmp.syntax.c"
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
#line 1509 "tmp.syntax.c"
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
#line 1522 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: arg-char-string */
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	/* END OF INLINE: single-arg */
	ZR133 (&ZIa, &ZIl);
	if ((CURRENT_TERMINAL) == 33) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (33);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZRnon_Hempty_Hchars(zoneP ZIz, SID_CHARS *ZOc)
{
    SID_CHARS ZIc;

    if ((CURRENT_TERMINAL) == 33) {
	return;
    }
    {
	ZRchars (ZIz, &ZIc);
	/* BEGINNING OF INLINE: 84 */
	{
	    if ((CURRENT_TERMINAL) == 33) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-non-empty */
		{
#line 398 "syntax.act"

    (ZI0)=((ZIc)[0]!=(ZIz)->top_level->last_letter_code);
#line 1569 "tmp.syntax.c"
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
#line 402 "syntax.act"

        error(ERROR_SERIOUS, "Empty character string is not allowed here, try using DEFAULT instead");	
#line 1583 "tmp.syntax.c"
		}
		/* END OF ACTION: E_empty_character_string */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 84 */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (33);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZR120(zoneP *ZIz, SID_CHARS *ZOe)
{
    SID_CHARS ZIe;

    if ((CURRENT_TERMINAL) == 33) {
	return;
    }
    {
	ZRnon_Hempty_Hchars (*ZIz, &ZIe);
	if ((CURRENT_TERMINAL) == 33) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E_expected_chars */
	{
#line 580 "syntax.act"

        (ZIe) = NULL ;
	error(ERROR_SERIOUS, "Syntax error: expected characters");
#line 1623 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_chars */
    }
  ZL0:;
    *ZOe = ZIe;
}

static void
ZR122(instructions_listP *ZOleaving_Hinstl)
{
    instructions_listP ZIleaving_Hinstl;

    switch (CURRENT_TERMINAL) {
      case 19:
	{
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (&ZIleaving_Hinstl);
	    if ((CURRENT_TERMINAL) == 33) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-inst-list */
	    {
#line 383 "syntax.act"

    (ZIleaving_Hinstl)=add_instructions_list();
#line 1654 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-inst-list */
	}
	break;
      case 33:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (33);
    return;
  ZL0:;
    *ZOleaving_Hinstl = ZIleaving_Hinstl;
}

/* BEGINNING OF TRAILER */

#line 595 "syntax.act"

#line 1674 "tmp.syntax.c"

/* END OF FILE */
