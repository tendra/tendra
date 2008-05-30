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

#include "exds/common.h"
#include "exds/exception.h"
#include "exds/dalloc.h"
#include "exds/dstring.h"

#include "error/error.h"
#include "xalloc/xalloc.h"

#include "char.h"
#include "adt.h"
#include "lex.h"
#include "syntax.h"
#include "options.h"


#define ADVANCE_LEXER ADVANCE_LXI_LEXER
#define CURRENT_TERMINAL CURRENT_LXI_TERMINAL 
#define SAVE_LEXER SAVE_LXI_LEXER
#define RESTORE_LEXER RESTORE_LXI_LEXER

/* TODO see main.c; this is a work-around for the copyright file */
extern cmd_line_options options;



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

char *token_prefix = "lex_" ;


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


#line 118 "tmp.syntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZR133(void);
static void ZRexpected__semicolon(void);
static void ZRtuple_Hargs(args_listP *);
static void ZRzone_Hdefn(zoneP);
static void ZRstring_Hplus(SID_STRING *);
static void ZRtype_Hdefn(zoneP);
static void ZRchars(zoneP, SID_CHARS *);
static void ZRaction_Hcall_C_Clhs_Htuple1(args_listP *);
static void ZRtype_Htuple(zoneP, TypeTupleT *);
static void ZRaction_Hcall_C_Crhs_Htuple1(args_listP *);
static void ZR163(void);
static void ZR164(void);
static void ZR165(void);
static void ZRinstructions_Hlist(zoneP, instructions_listP *);
static void ZRtype_Htuple_C_Ctype_Hname(zoneP, TypeTupleT *);
static void ZRargs(args_listP *);
static void ZRtrigraph_Hdefn(zoneP);
static void ZR183(args_listP *);
extern void read_lex(zoneP);
static void ZRaction_Hdecl(zoneP);
static void ZRinstruction(zoneP, instructionP *);
static void ZR208(zoneP *, SID_CHARS *);
static void ZRcommand_Hlist(zoneP);
static void ZR210(zoneP *, instructions_listP *);
static void ZRkeyword_Hdefn(zoneP);
static void ZRcopyright_Hstmt(zoneP);
static void ZR224(zoneP *);
static void ZR225(zoneP *);
static void ZRif_Hcommand(zoneP);
static void ZRcommand(zoneP);
static void ZR229(zoneP *, SID_STRING *, instructionP *);
static void ZRnon_Hempty_Htuple_Hargs(args_listP *);
static void ZR231(zoneP *, SID_STRING *, instructionP *);
static void ZRtype_Htuple_C_Ctype_Htuple1(zoneP, TypeTupleT *);
static void ZR232(argP *, args_listP *);
static void ZR233(argP *, args_listP *);
static void ZR234(argP *, args_listP *);
static void ZR235(zoneP *, instructionP *, instructions_listP *);
static void ZR236(zoneP *, TypeTupleT *);
static void ZRaction_Hcall_C_Crhs_Htuple(args_listP *);
static void ZRnon_Hempty_Hchars(zoneP, SID_CHARS *);
static void ZRsingle_Harg(argP *);
static void ZRaction_Hcall_C_Clhs_Harg(argP *);
static void ZRaction_Hcall_C_Crhs_Harg(argP *);

/* BEGINNING OF STATIC VARIABLES */

static int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZR133(void)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 22:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E_expected_equal */
	{
#line 814 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected equal \'=\'");
#line 196 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_equal */
    }
}

static void
ZRexpected__semicolon(void)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 24:
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
#line 806 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected semicolon \';\'");
#line 225 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_semicolon */
    }
}

static void
ZRtuple_Hargs(args_listP *ZOl)
{
    args_listP ZIl;

    switch (CURRENT_TERMINAL) {
      case 39:
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 245 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	}
	break;
      case 0: case 1: case 2: case 26: case 33:
      case 34: case 35: case 36: case 37: case 38:
	{
	    ZRnon_Hempty_Htuple_Hargs (&ZIl);
	    if ((CURRENT_TERMINAL) == 44) {
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
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 269 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: arg-char-list-tmp */
	    {
#line 407 "syntax.act"

      (ZItmp)=add_arg(arg_chars_list,0);
#line 277 "tmp.syntax.c"
	    }
	    /* END OF ACTION: arg-char-list-tmp */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZItmp)->next=(ZIl)->head;
    (ZIl)->head=(ZItmp);
#line 286 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      case 44:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZRzone_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	SID_STRING ZIzid;
	SID_CHARS ZIb;
	instructions_listP ZIentry_Hinstl;
	int ZIlendclosed;
	SID_CHARS ZIe;
	instructions_listP ZIleaving_Hinstl;
	zoneP ZInew_Hzone;

	switch (CURRENT_TERMINAL) {
	  case 13:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 200 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 0:
		    /* BEGINNING OF EXTRACT: identifier */
		    {
#line 210 "syntax.act"

    ZIzid = xstrcpy ( token_buff ) ;
#line 334 "tmp.syntax.c"
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
#line 780 "syntax.act"

	(ZIzid)="";
	error(ERROR_SERIOUS, "Syntax error: expected identifier");
#line 352 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_identifier */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 200 */
	/* BEGINNING OF INLINE: 202 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 25:
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
#line 802 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected colon \':\'");
#line 378 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_colon */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 202 */
	ZR208 (&ZIz, &ZIb);
	ZR210 (&ZIz, &ZIentry_Hinstl);
	/* BEGINNING OF INLINE: 206 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 27:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: true */
		    {
#line 611 "syntax.act"
 (ZIlendclosed) = 1 ; 
#line 397 "tmp.syntax.c"
		    }
		    /* END OF ACTION: true */
		}
		break;
	      case 28:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: true */
		    {
#line 611 "syntax.act"
 (ZIlendclosed) = 1 ; 
#line 409 "tmp.syntax.c"
		    }
		    /* END OF ACTION: true */
		}
		break;
	      case 29:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: false */
		    {
#line 612 "syntax.act"
 (ZIlendclosed) = 0 ; 
#line 421 "tmp.syntax.c"
		    }
		    /* END OF ACTION: false */
		}
		break;
	      case 44:
		RESTORE_LEXER;
		goto ZL7;
	      default:
		goto ZL7;
	    }
	    goto ZL6;
	  ZL7:;
	    {
		/* BEGINNING OF ACTION: E_expected_range */
		{
#line 785 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected range");
#line 440 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_range */
		/* BEGINNING OF ACTION: false */
		{
#line 612 "syntax.act"
 (ZIlendclosed) = 0 ; 
#line 447 "tmp.syntax.c"
		}
		/* END OF ACTION: false */
	    }
	  ZL6:;
	}
	/* END OF INLINE: 206 */
	ZR208 (&ZIz, &ZIe);
	ZR210 (&ZIz, &ZIleaving_Hinstl);
	if ((CURRENT_TERMINAL) == 44) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-zone */
	{
#line 628 "syntax.act"

    instruction* inst;
    instructions_list* inst_list;
    (ZInew_Hzone)=add_zone((ZIz),(ZIzid),(ZIe), (ZIlendclosed) );
    (ZInew_Hzone)->entering_instructions=(ZIentry_Hinstl);
    (ZInew_Hzone)->leaving_instructions=(ZIleaving_Hinstl);
    inst=add_instruction_pushzone((ZInew_Hzone));
    inst_list=add_instructions_list();
    *(inst_list->tail)=inst;
    inst_list->tail=&(inst->next);
    add_char ( (ZIz), (ZIz)->zone_main_pass, (ZIb), crt_cond, inst_list, NULL ) ;
#line 474 "tmp.syntax.c"
	}
	/* END OF ACTION: make-zone */
	switch (CURRENT_TERMINAL) {
	  case 18:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRcommand_Hlist (ZInew_Hzone);
	switch (CURRENT_TERMINAL) {
	  case 19:
	    break;
	  case 44:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZRstring_Hplus(SID_STRING *ZOs)
{
    SID_STRING ZIs;

    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	SID_STRING ZIa;

	/* BEGINNING OF INLINE: 117 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 5:
		{
		    /* BEGINNING OF EXTRACT: digit */
		    {
#line 268 "syntax.act"
 ZIa = "0123456789" ; 
#line 522 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: digit */
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    /* BEGINNING OF EXTRACT: lower */
		    {
#line 267 "syntax.act"
 ZIa = "abcdefghijklmnopqrstuvwxyz" ; 
#line 534 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: lower */
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    /* BEGINNING OF EXTRACT: string */
		    {
#line 255 "syntax.act"

    ZIa = xstrcpy ( token_buff ) ;
#line 547 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: string */
		    ADVANCE_LEXER;
		}
		break;
	      case 3:
		{
		    /* BEGINNING OF EXTRACT: upper */
		    {
#line 266 "syntax.act"
 ZIa = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ; 
#line 559 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: upper */
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	/* END OF INLINE: 117 */
	/* BEGINNING OF INLINE: 119 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 23:
		{
		    SID_STRING ZIb;

		    ADVANCE_LEXER;
		    ZRstring_Hplus (&ZIb);
		    if ((CURRENT_TERMINAL) == 44) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    /* BEGINNING OF ACTION: string-concat */
		    {
#line 306 "syntax.act"

    (ZIs) = xstrcat ( (ZIa), (ZIb) ) ;
#line 588 "tmp.syntax.c"
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
	/* END OF INLINE: 119 */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOs = ZIs;
}

static void
ZRtype_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	SID_STRING ZIs;

	switch (CURRENT_TERMINAL) {
	  case 43:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 0:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 210 "syntax.act"

    ZIs = xstrcpy ( token_buff ) ;
#line 633 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 144 */
	{
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 667 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 649 "tmp.syntax.c"
		}
		/* END OF ACTION: is-global-zone */
		if (!ZI0)
		    goto ZL3;
		/* BEGINNING OF ACTION: make-type */
		{
#line 683 "syntax.act"

	NStringT str;
	nstring_copy_cstring(&str,(ZIs));
	xfree((ZIs));
	EntryT* entry;
	if(entry=table_get_entry((ZIz)->top_level->table, &str)) {
		nstring_destroy(&str);
		/* TODO switch ? */
		if(entry_is_type(entry))
			error(ERROR_SERIOUS, "Type %s already exists",(ZIs));
		else if(entry_is_localname(entry))
			error(ERROR_SERIOUS, "Can't create type %s, %s has been previously used as a local name. We do not allow retroactive hiding.",(ZIs),(ZIs));
		else if(entry_is_action(entry))
			error(ERROR_SERIOUS, "Can't create type %s, %s has already been declared as an action",(ZIs), (ZIs));
		else
			; /* TODO assert(0): we should never reach that place*/
	} else {
		table_add_type((ZIz)->top_level->table, &str, false);
	}
#line 676 "tmp.syntax.c"
		}
		/* END OF ACTION: make-type */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonetype */
		{
#line 769 "syntax.act"

    error( ERROR_SERIOUS, "Syntax error: type %s should not be declared inside a zone",(ZIs)) ;
#line 688 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonetype */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 144 */
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZRchars(zoneP ZIz, SID_CHARS *ZOc)
{
    SID_CHARS ZIc;

    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	SID_STRING ZIs;

	ZRstring_Hplus (&ZIs);
	if ((CURRENT_TERMINAL) == 44) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-chars */
	{
#line 327 "syntax.act"

    (ZIc) = make_string ( (ZIs), (ZIz) ) ;
#line 723 "tmp.syntax.c"
	}
	/* END OF ACTION: make-chars */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRaction_Hcall_C_Clhs_Htuple1(args_listP *ZOl)
{
    args_listP ZIl;

    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	argP ZIa;

	ZRaction_Hcall_C_Clhs_Harg (&ZIa);
	ZR233 (&ZIa, &ZIl);
	if ((CURRENT_TERMINAL) == 44) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZRtype_Htuple(zoneP ZIz, TypeTupleT *ZOa)
{
    TypeTupleT ZIa;

    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 729 "syntax.act"

	typetuple_init(&(ZIa));
#line 775 "tmp.syntax.c"
	}
	/* END OF ACTION: init-tuple */
	ZR236 (&ZIz, &ZIa);
	if ((CURRENT_TERMINAL) == 44) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    /* BEGINNING OF RESULT ASSIGNMENT: TYPETUPLE */
    {
#line 195 "syntax.act"

	typetuple_assign(ZOa, (&ZIa));
#line 794 "tmp.syntax.c"
    }
    /* END OF RESULT ASSIGNMENT: TYPETUPLE */
}

static void
ZRaction_Hcall_C_Crhs_Htuple1(args_listP *ZOr)
{
    args_listP ZIr;

    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	argP ZIa;

	ZRaction_Hcall_C_Crhs_Harg (&ZIa);
	ZR232 (&ZIa, &ZIr);
	if ((CURRENT_TERMINAL) == 44) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOr = ZIr;
}

static void
ZR163(void)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 20:
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
#line 810 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected arrow \'->\'");
#line 848 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_arrow */
    }
}

static void
ZR164(void)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 16:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E_expected_open */
	{
#line 789 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected open \'(\'");
#line 877 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_open */
    }
}

static void
ZR165(void)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 17:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E_expected_close */
	{
#line 793 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected close \')\'");
#line 906 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_close */
    }
}

static void
ZRinstructions_Hlist(zoneP ZIz, instructions_listP *ZOinstl)
{
    instructions_listP ZIinstl;

    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	instructionP ZIinst;

	ZRinstruction (ZIz, &ZIinst);
	ZR235 (&ZIz, &ZIinst, &ZIinstl);
	if ((CURRENT_TERMINAL) == 44) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOinstl = ZIinstl;
}

static void
ZRtype_Htuple_C_Ctype_Hname(zoneP ZIz, TypeTupleT *ZOa)
{
    TypeTupleT ZIa;

    /* BEGINNING OF PARAM ASSIGNMENT: TYPETUPLE */
    {
#line 189 "syntax.act"

	typetuple_assign(&ZIa,ZOa);
#line 948 "tmp.syntax.c"
    }
    /* END OF PARAM ASSIGNMENT: TYPETUPLE */
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	SID_STRING ZIname;
	SID_STRING ZItype;
	int ZIisref;

	/* BEGINNING OF INLINE: 148 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 0:
		{
		    /* BEGINNING OF EXTRACT: identifier */
		    {
#line 210 "syntax.act"

    ZIname = xstrcpy ( token_buff ) ;
#line 969 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: identifier */
		    ADVANCE_LEXER;
		}
		break;
	      default:
		{
		    /* BEGINNING OF ACTION: empty-identifier */
		    {
#line 316 "syntax.act"

    (ZIname) = "";
#line 982 "tmp.syntax.c"
		    }
		    /* END OF ACTION: empty-identifier */
		}
		break;
	    }
	}
	/* END OF INLINE: 148 */
	switch (CURRENT_TERMINAL) {
	  case 25:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 0:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 210 "syntax.act"

    ZItype = xstrcpy ( token_buff ) ;
#line 1004 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 151 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 26:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: true */
		    {
#line 611 "syntax.act"
 (ZIisref) = 1 ; 
#line 1022 "tmp.syntax.c"
		    }
		    /* END OF ACTION: true */
		}
		break;
	      default:
		{
		    /* BEGINNING OF ACTION: false */
		    {
#line 612 "syntax.act"
 (ZIisref) = 0 ; 
#line 1033 "tmp.syntax.c"
		    }
		    /* END OF ACTION: false */
		}
		break;
	    }
	}
	/* END OF INLINE: 151 */
	/* BEGINNING OF ACTION: append-tuple */
	{
#line 733 "syntax.act"

	NStringT tstr, istr;
	nstring_copy_cstring(&tstr,(ZItype));
	nstring_copy_cstring(&istr,(ZIname));
	EntryT* entry = table_get_entry((ZIz)->top_level->table,&tstr);
	if(entry == NULL) {
		 error(ERROR_SERIOUS, "Unknown type %s", (ZItype));
		 nstring_destroy(&istr);
	}
	else if(!entry_is_type(entry)) {
		 error(ERROR_SERIOUS, "%s is not a type", (ZItype));
		 nstring_destroy(&istr);
	}
	else {
		typetuple_append((&ZIa),typetupleentry_create(&istr,entry,(ZIisref)));
	}
	nstring_destroy(&tstr);
	xfree((ZItype));
	xfree((ZIname));
#line 1063 "tmp.syntax.c"
	}
	/* END OF ACTION: append-tuple */
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZRargs(args_listP *ZOl)
{
    args_listP ZIl;

    switch (CURRENT_TERMINAL) {
      case 16:
	{
	    ADVANCE_LEXER;
	    ZRtuple_Hargs (&ZIl);
	    switch (CURRENT_TERMINAL) {
	      case 17:
		break;
	      case 44:
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
#line 429 "syntax.act"

    (ZIl) = NULL ;
#line 1102 "tmp.syntax.c"
	    }
	    /* END OF ACTION: null-args-list */
	}
	break;
      case 44:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZRtrigraph_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	SID_CHARS ZIs;
	SID_STRING ZIt;

	switch (CURRENT_TERMINAL) {
	  case 9:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRchars (ZIz, &ZIs);
	ZR163 ();
	ZRstring_Hplus (&ZIt);
	if ((CURRENT_TERMINAL) == 44) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-trigraph */
	{
#line 365 "syntax.act"

    add_char ( (ZIz), (ZIz)->zone_pre_pass, (ZIs), crt_cond, NULL, (ZIt)) ;
#line 1147 "tmp.syntax.c"
	}
	/* END OF ACTION: make-trigraph */
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZR183(args_listP *ZOr)
{
    args_listP ZIr;

    switch (CURRENT_TERMINAL) {
      case 16:
	{
	    ZRaction_Hcall_C_Crhs_Htuple (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIr)=add_args_list();
#line 1179 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	}
	break;
      case 44:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOr = ZIr;
}

void
read_lex(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	ZRcommand_Hlist (ZIz);
	/* BEGINNING OF INLINE: 215 */
	{
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 21:
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
#line 827 "syntax.act"

	error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1226 "tmp.syntax.c"
		}
		/* END OF ACTION: syntax-error */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 215 */
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZRaction_Hdecl(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	SID_STRING ZIi;
	TypeTupleT ZIit;
	TypeTupleT ZIot;

	switch (CURRENT_TERMINAL) {
	  case 40:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 156 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 41:
		    break;
		  default:
		    goto ZL3;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_expected_begin_action */
		{
#line 818 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected begin action \'<\'");
#line 1277 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_begin_action */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 156 */
	switch (CURRENT_TERMINAL) {
	  case 0:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 1291 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 157 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 42:
		    break;
		  default:
		    goto ZL5;
		}
		ADVANCE_LEXER;
	    }
	    goto ZL4;
	  ZL5:;
	    {
		/* BEGINNING OF ACTION: E_expected_end_action */
		{
#line 822 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected end action \'>\'");
#line 1318 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_end_action */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 157 */
	/* BEGINNING OF INLINE: 158 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 25:
		{
		    ADVANCE_LEXER;
		    ZR164 ();
		    ZRtype_Htuple (ZIz, &ZIit);
		    ZR165 ();
		    ZR163 ();
		    ZR164 ();
		    ZRtype_Htuple (ZIz, &ZIot);
		    ZR165 ();
		    if ((CURRENT_TERMINAL) == 44) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 729 "syntax.act"

	typetuple_init(&(ZIit));
#line 1351 "tmp.syntax.c"
		    }
		    /* END OF ACTION: init-tuple */
		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 729 "syntax.act"

	typetuple_init(&(ZIot));
#line 1359 "tmp.syntax.c"
		    }
		    /* END OF ACTION: init-tuple */
		}
		break;
	    }
	}
	/* END OF INLINE: 158 */
	/* BEGINNING OF ACTION: make-action */
	{
#line 704 "syntax.act"

	NStringT str;
	nstring_copy_cstring(&str, (ZIi));
	EntryT* entry;
	if(entry=table_get_entry((ZIz)->top_level->table, &str)) {
		nstring_destroy(&str);
		/* TODO switch ? */
	   	if(entry_is_action(entry))
			error(ERROR_SERIOUS, "Action %s already exists",(ZIi));
		else if(entry_is_localname(entry))
			error(ERROR_SERIOUS, "Can't create type %s, %s has been previously used as a local name. We do not allow retroactive hiding.",(ZIi),(ZIi));
		else if(entry_is_type(entry))
			error(ERROR_SERIOUS, "Can't create action %s, %s has already been declared as a type",(ZIi), (ZIi));
		else
			; /* TODO assert(0): we should never reach that place*/
	} else {
		table_add_action((ZIz)->top_level->table, &str , (&ZIit), (&ZIot));
	}
	xfree((ZIi));
#line 1389 "tmp.syntax.c"
	}
	/* END OF ACTION: make-action */
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZRinstruction(zoneP ZIz, instructionP *ZOinst)
{
    instructionP ZIinst;

    switch (CURRENT_TERMINAL) {
      case 33:
	{
	    argP ZIb;
	    argP ZIa;
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    /* BEGINNING OF EXTRACT: arg-char-list */
	    {
#line 273 "syntax.act"

      ZIb=add_arg(arg_chars_list,0);
#line 1418 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-list */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 1427 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 831 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1435 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 1443 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1452 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	    switch (CURRENT_TERMINAL) {
	      case 22:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 1476 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 42:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR183 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 387 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		}
		else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 1516 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 35:
	{
	    argP ZIb;
	    argP ZIa;
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    /* BEGINNING OF EXTRACT: arg-char-nb */
	    {
#line 281 "syntax.act"

      ZIb=add_arg(arg_char_nb,number_buffer);
#line 1534 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-nb */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 1543 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 831 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1551 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 1559 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1568 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	    switch (CURRENT_TERMINAL) {
	      case 22:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 1592 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 42:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR183 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 387 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		}
		else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 1632 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 34:
	{
	    argP ZIb;
	    argP ZIa;
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    /* BEGINNING OF EXTRACT: arg-char-string */
	    {
#line 277 "syntax.act"

      ZIb=add_arg(arg_charP,0);
#line 1650 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 1659 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 831 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1667 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 1675 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1684 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	    switch (CURRENT_TERMINAL) {
	      case 22:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 1708 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 42:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR183 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 387 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		}
		else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 1748 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 38:
	{
	    argP ZIa;
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    /* BEGINNING OF EXTRACT: arg-ignore */
	    {
#line 293 "syntax.act"

      ZIa=add_arg(arg_ignore,0);
#line 1765 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-ignore */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 1774 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1783 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	    switch (CURRENT_TERMINAL) {
	      case 22:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 1807 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 42:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR183 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 387 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		}
		else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 1847 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 36:
	{
	    argP ZIb;
	    argP ZIa;
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    /* BEGINNING OF EXTRACT: arg-nb-of-chars */
	    {
#line 285 "syntax.act"

      ZIb=add_arg(arg_nb_of_chars,0);
#line 1865 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-nb-of-chars */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 1874 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 831 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1882 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 1890 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1899 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	    switch (CURRENT_TERMINAL) {
	      case 22:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 1923 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 42:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR183 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 387 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		}
		else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 1963 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 37:
	{
	    argP ZIa;
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    /* BEGINNING OF EXTRACT: arg-return-terminal */
	    {
#line 289 "syntax.act"

      ZIa=add_arg(arg_return_terminal,0);
#line 1980 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-return-terminal */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 1989 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1998 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	    switch (CURRENT_TERMINAL) {
	      case 22:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2022 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 42:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR183 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 387 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		}
		else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2062 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 0:
	{
	    SID_STRING ZI228;

	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 210 "syntax.act"

    ZI228 = xstrcpy ( token_buff ) ;
#line 2076 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    ZR229 (&ZIz, &ZI228, &ZIinst);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 16:
	{
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    ADVANCE_LEXER;
	    ZRaction_Hcall_C_Clhs_Htuple1 (&ZIl);
	    switch (CURRENT_TERMINAL) {
	      case 17:
		break;
	      case 44:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 22:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2126 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 42:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR183 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 387 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		}
		else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2166 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 26:
	{
	    SID_STRING ZI227;
	    argP ZIa;
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZI227 = xstrcpy ( token_buff ) ;
#line 2187 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_reference */
	    {
#line 649 "syntax.act"

	(ZIa) = add_reference_arg ((ZI227));
#line 2200 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_reference */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 2208 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 2217 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	    switch (CURRENT_TERMINAL) {
	      case 22:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2241 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 42:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR183 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 387 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		}
		else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2281 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 1:
	{
	    SID_STRING ZI230;

	    /* BEGINNING OF EXTRACT: sid-identifier */
	    {
#line 222 "syntax.act"

    int n ;
    char *s ;
    char buff [1000] ;
    strcpy ( buff, token_prefix ) ;
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
    ZI230 = xstrcpy ( buff ) ;
#line 2316 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: sid-identifier */
	    ADVANCE_LEXER;
	    ZR231 (&ZIz, &ZI230, &ZIinst);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 2:
	{
	    SID_STRING ZIb;
	    argP ZIa;
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    /* BEGINNING OF EXTRACT: string */
	    {
#line 255 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 2340 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 2349 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_string_arg_in_lhs */
	    {
#line 835 "syntax.act"

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
#line 2357 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_string_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 2365 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 2374 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	    switch (CURRENT_TERMINAL) {
	      case 22:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2398 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 42:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR183 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 387 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		}
		else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2438 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 31:
	{
	    /* BEGINNING OF INLINE: 186 */
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 31:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: make-donothing-inst */
		    {
#line 383 "syntax.act"

	(ZIinst)=add_instruction_donothing();
#line 2460 "tmp.syntax.c"
		    }
		    /* END OF ACTION: make-donothing-inst */
		}
	    }
	    /* END OF INLINE: 186 */
	}
	break;
      case 41:
	{
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 2479 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2490 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 42:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR183 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 387 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		}
		else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2530 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 44:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOinst = ZIinst;
}

static void
ZR208(zoneP *ZIz, SID_CHARS *ZOe)
{
    SID_CHARS ZIe;

    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	ZRnon_Hempty_Hchars (*ZIz, &ZIe);
	if ((CURRENT_TERMINAL) == 44) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E_expected_chars */
	{
#line 797 "syntax.act"

        (ZIe) = NULL ;
	error(ERROR_SERIOUS, "Syntax error: expected characters");
#line 2572 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_chars */
    }
  ZL0:;
    *ZOe = ZIe;
}

static void
ZRcommand_Hlist(zoneP ZIz)
{
  ZL2_command_Hlist:;
    switch (CURRENT_TERMINAL) {
      case 6: case 7: case 8: case 9: case 10:
      case 13: case 14: case 18: case 24: case 40:
      case 43:
	{
	    ZRcommand (ZIz);
	    /* BEGINNING OF INLINE: command-list */
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_command_Hlist;
	    }
	    /* END OF INLINE: command-list */
	}
	/*UNREACHED*/
      case 44:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: syntax-error */
	{
#line 827 "syntax.act"

	error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 2613 "tmp.syntax.c"
	}
	/* END OF ACTION: syntax-error */
    }
}

static void
ZR210(zoneP *ZIz, instructions_listP *ZOleaving_Hinstl)
{
    instructions_listP ZIleaving_Hinstl;

    switch (CURRENT_TERMINAL) {
      case 20:
	{
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (*ZIz, &ZIleaving_Hinstl);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-inst-list */
	    {
#line 491 "syntax.act"

    (ZIleaving_Hinstl)=add_instructions_list();
#line 2642 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-inst-list */
	}
	break;
      case 44:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOleaving_Hinstl = ZIleaving_Hinstl;
}

static void
ZRkeyword_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	SID_STRING ZIs;
	instructionP ZIinst;

	switch (CURRENT_TERMINAL) {
	  case 8:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 2:
	    /* BEGINNING OF EXTRACT: string */
	    {
#line 255 "syntax.act"

    ZIs = xstrcpy ( token_buff ) ;
#line 2682 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 20:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRinstruction (ZIz, &ZIinst);
	/* BEGINNING OF INLINE: 193 */
	{
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 667 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 2710 "tmp.syntax.c"
		}
		/* END OF ACTION: is-global-zone */
		if (!ZI0)
		    goto ZL3;
		/* BEGINNING OF ACTION: make-keyword */
		{
#line 532 "syntax.act"

    switch((ZIinst)->type) {
    case apply_function:
      if((ZIinst)->u.fun->args->head==NULL) {
        error(ERROR_SERIOUS, "Syntax error: for keywords using "
	"user defined functions, "
	"the arglist must remain empty");
        break;
      }
    case return_terminal: 
    /* Fallback is intentional */
      add_keyword ( (ZIz), (ZIs), crt_cond, (ZIinst) ) ;
    break;
    default:
      error(ERROR_SERIOUS, "Syntax error: only a function or a token might be returned for a keyword");
  }
#line 2734 "tmp.syntax.c"
		}
		/* END OF ACTION: make-keyword */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonekeyword */
		{
#line 759 "syntax.act"

    error( ERROR_SERIOUS, "Keywords not yet implemented in a non global zone ") ;

#line 2747 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonekeyword */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 193 */
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZRcopyright_Hstmt(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	SID_STRING ZIs;

	switch (CURRENT_TERMINAL) {
	  case 6:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 22:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 2:
	    /* BEGINNING OF EXTRACT: string */
	    {
#line 255 "syntax.act"

    ZIs = xstrcpy ( token_buff ) ;
#line 2791 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 128 */
	{
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 667 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 2807 "tmp.syntax.c"
		}
		/* END OF ACTION: is-global-zone */
		if (!ZI0)
		    goto ZL3;
		/* BEGINNING OF ACTION: make-copyright */
		{
#line 671 "syntax.act"

	/* TODO can copyright_file be passed in somehow, other than with options as a global? */
	if(options.copyright_file==NULL) {
		options.copyright_file=fopen((ZIs),"r");
		if(!options.copyright_file) {
			error(ERROR_SERIOUS, "Syntax error: unable to open copright file %s", (ZIs)) ;
		}
	}
	else 
		error(ERROR_SERIOUS, "Syntax error: you can only specify one copyright file") ;
#line 2825 "tmp.syntax.c"
		}
		/* END OF ACTION: make-copyright */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonecopyright */
		{
#line 764 "syntax.act"

    error( ERROR_SERIOUS, "Syntax error: A copyright file may only be specified in the global zone") ;
#line 2837 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonecopyright */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 128 */
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZR224(zoneP *ZIz)
{
    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    SID_STRING ZIi;
	    SID_CHARS ZIs;

	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2865 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    ZR133 ();
	    ZRchars (*ZIz, &ZIs);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-group */
	    {
#line 354 "syntax.act"

    make_group ( (*ZIz), (ZIi), (ZIs) ) ;
#line 2880 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-group */
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 11:
	{
	    SID_CHARS ZIs;

	    ADVANCE_LEXER;
	    ZR133 ();
	    ZRchars (*ZIz, &ZIs);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-white */
	    {
#line 340 "syntax.act"

    if ( (*ZIz)->white_space) {
	error ( ERROR_SERIOUS, "White space group already defined" ) ;
    }
    (*ZIz)->white_space= make_group((*ZIz),"white",(ZIs)) ;
#line 2909 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-white */
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 44:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZR225(zoneP *ZIz)
{
    switch (CURRENT_TERMINAL) {
      case 12:
	{
	    instructions_listP ZIinst_Hlist;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 20:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (*ZIz, &ZIinst_Hlist);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-default */
	    {
#line 519 "syntax.act"

    (*ZIz)->default_instructions=(ZIinst_Hlist);
    (*ZIz)->default_cond=crt_cond;
#line 2957 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-default */
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 2: case 3: case 4: case 5:
	{
	    SID_CHARS ZIs;
	    instructions_listP ZIinst_Hlist;

	    ZRnon_Hempty_Hchars (*ZIz, &ZIs);
	    switch (CURRENT_TERMINAL) {
	      case 20:
		break;
	      case 44:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (*ZIz, &ZIinst_Hlist);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-token */
	    {
#line 502 "syntax.act"

        add_char ( (*ZIz), (*ZIz)->zone_main_pass, (ZIs), crt_cond, (ZIinst_Hlist), NULL) ;
#line 2993 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-token */
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 44:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZRif_Hcommand(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	SID_STRING ZIi;
	SID_STRING ZIj;

	switch (CURRENT_TERMINAL) {
	  case 14:
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
	switch (CURRENT_TERMINAL) {
	  case 0:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 3045 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 17:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF ACTION: get-condition */
	{
#line 589 "syntax.act"

    (ZIj) = crt_cond ;
#line 3065 "tmp.syntax.c"
	}
	/* END OF ACTION: get-condition */
	/* BEGINNING OF ACTION: add-condition */
	{
#line 557 "syntax.act"

    if ( crt_cond ) {
	crt_cond = xstrcat ( crt_cond, xstrcat ( " && ", (ZIi) ) ) ;
    } else {
	crt_cond = (ZIi) ;
    }
#line 3077 "tmp.syntax.c"
	}
	/* END OF ACTION: add-condition */
	ZRcommand (ZIz);
	/* BEGINNING OF INLINE: 198 */
	{
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 15:
		    break;
		  default:
		    goto ZL3;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: compl-condition */
		{
#line 572 "syntax.act"

    if ( crt_cond ) {
	if ( strchr ( crt_cond, '&' ) ) {
	    crt_cond = xstrcat ( xstrcat ( "!( ", crt_cond ), " )" ) ;
	} else {
	    crt_cond = xstrcat ( "!", crt_cond ) ;
	}
    }
#line 3106 "tmp.syntax.c"
		}
		/* END OF ACTION: compl-condition */
		ZRcommand (ZIz);
		if ((CURRENT_TERMINAL) == 44) {
		    RESTORE_LEXER;
		    goto ZL3;
		}
		/* BEGINNING OF ACTION: set-condition */
		{
#line 600 "syntax.act"

    crt_cond = (ZIj) ;
#line 3119 "tmp.syntax.c"
		}
		/* END OF ACTION: set-condition */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: set-condition */
		{
#line 600 "syntax.act"

    crt_cond = (ZIj) ;
#line 3131 "tmp.syntax.c"
		}
		/* END OF ACTION: set-condition */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 198 */
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZRcommand(zoneP ZIz)
{
    switch (CURRENT_TERMINAL) {
      case 7:
	{
	    ADVANCE_LEXER;
	    ZR224 (&ZIz);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 18:
	{
	    ADVANCE_LEXER;
	    ZRcommand_Hlist (ZIz);
	    switch (CURRENT_TERMINAL) {
	      case 19:
		break;
	      case 44:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 24:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 10:
	{
	    ADVANCE_LEXER;
	    ZR225 (&ZIz);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 40:
	{
	    ZRaction_Hdecl (ZIz);
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 6:
	{
	    ZRcopyright_Hstmt (ZIz);
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 14:
	{
	    ZRif_Hcommand (ZIz);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 8:
	{
	    ZRkeyword_Hdefn (ZIz);
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 9:
	{
	    ZRtrigraph_Hdefn (ZIz);
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 43:
	{
	    ZRtype_Hdefn (ZIz);
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 13:
	{
	    ZRzone_Hdefn (ZIz);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 44:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZR229(zoneP *ZIz, SID_STRING *ZI228, instructionP *ZOinst)
{
    instructionP ZIinst;

    switch (CURRENT_TERMINAL) {
      default:
	{
	    args_listP ZIa;

	    ZRargs (&ZIa);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-inst */
	    {
#line 374 "syntax.act"

    if((ZIa)) {
        (ZIinst)=add_instruction_function((*ZI228),(ZIa));
    } 
    else {
        (ZIinst)=add_instruction_return_terminal((*ZI228));
    }
#line 3294 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-inst */
	}
	break;
      case 22:
	{
	    argP ZIa;
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    /* BEGINNING OF ACTION: make_arg_from_identifier */
	    {
#line 645 "syntax.act"

	(ZIa) = add_identifier_arg ((*ZI228));
#line 3311 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_identifier */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 3319 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 3328 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 3346 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 42:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR183 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 387 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		}
		else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 3386 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 44:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOinst = ZIinst;
}

static void
ZRnon_Hempty_Htuple_Hargs(args_listP *ZOl)
{
    args_listP ZIl;

    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	argP ZIa;

	ZRsingle_Harg (&ZIa);
	ZR234 (&ZIa, &ZIl);
	if ((CURRENT_TERMINAL) == 44) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZR231(zoneP *ZIz, SID_STRING *ZI230, instructionP *ZOinst)
{
    instructionP ZIinst;

    switch (CURRENT_TERMINAL) {
      case 22:
	{
	    argP ZIa;
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 3446 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_terminal_in_lhs */
	    {
#line 858 "syntax.act"

	error(ERROR_SERIOUS, "Terminal argument in left handside");
#line 3454 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_terminal_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 3462 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 3471 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 3489 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 42:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR183 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 387 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry)) {
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		}
		else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 3529 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      default:
	{
	    args_listP ZIa;

	    /* BEGINNING OF ACTION: null-args-list */
	    {
#line 429 "syntax.act"

    (ZIa) = NULL ;
#line 3543 "tmp.syntax.c"
	    }
	    /* END OF ACTION: null-args-list */
	    /* BEGINNING OF ACTION: make-inst */
	    {
#line 374 "syntax.act"

    if((ZIa)) {
        (ZIinst)=add_instruction_function((*ZI230),(ZIa));
    } 
    else {
        (ZIinst)=add_instruction_return_terminal((*ZI230));
    }
#line 3556 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-inst */
	}
	break;
      case 44:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOinst = ZIinst;
}

static void
ZRtype_Htuple_C_Ctype_Htuple1(zoneP ZIz, TypeTupleT *ZIa)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
  ZL2_type_Htuple_C_Ctype_Htuple1:;
    {
	ZRtype_Htuple_C_Ctype_Hname (ZIz, ZIa);
	/* BEGINNING OF INLINE: 237 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 30:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: type-tuple::type-tuple1 */
		    goto ZL2_type_Htuple_C_Ctype_Htuple1;
		    /* END OF INLINE: type-tuple::type-tuple1 */
		}
		/*UNREACHED*/
	      case 44:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
	/* END OF INLINE: 237 */
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZR232(argP *ZIa, args_listP *ZOr)
{
    args_listP ZIr;

    switch (CURRENT_TERMINAL) {
      case 30:
	{
	    ADVANCE_LEXER;
	    ZRaction_Hcall_C_Crhs_Htuple1 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (*ZIa)->next=(ZIr)->head;
    (ZIr)->head=(*ZIa);
#line 3627 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIr)=add_args_list();
#line 3639 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (*ZIa)->next=(ZIr)->head;
    (ZIr)->head=(*ZIa);
#line 3648 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      case 44:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOr = ZIr;
}

static void
ZR233(argP *ZIa, args_listP *ZOl)
{
    args_listP ZIl;

    switch (CURRENT_TERMINAL) {
      case 30:
	{
	    ADVANCE_LEXER;
	    ZRaction_Hcall_C_Clhs_Htuple1 (&ZIl);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 3684 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 3696 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 3705 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      case 44:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZR234(argP *ZIa, args_listP *ZOl)
{
    args_listP ZIl;

    switch (CURRENT_TERMINAL) {
      case 30:
	{
	    ADVANCE_LEXER;
	    ZRnon_Hempty_Htuple_Hargs (&ZIl);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 3741 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 3753 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 3762 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      case 44:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZR235(zoneP *ZIz, instructionP *ZIinst, instructions_listP *ZOinstl)
{
    instructions_listP ZIinstl;

    switch (CURRENT_TERMINAL) {
      case 30:
	{
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (*ZIz, &ZIinstl);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: add-inst-to-list */
	    {
#line 436 "syntax.act"

	if((*ZIinst)!=NULL) { /* if (*ZIinst) == NULL, an error has already been issued.*/
		LocalNamesT** locals = instructionslist_localnamesref((ZIinstl));
		if(((ZIinstl)->head !=NULL) && ((*ZIinst)->type==return_terminal || (*ZIinst)->type==do_nothing)) {
			error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an instruction-list"); 
		}
		if((*ZIinst)->type == apply_function) {
			args_rhs_fill_type((*ZIinst)->u.fun->args, *locals, (*ZIz)->top_level) ;
		}
		if((*ZIinst)->type == action_call) {
			EntryT* entryaction = (*ZIinst)->u.act.called_act;
			ActionT* action = entry_get_action(entryaction);
			args_list* rhs = (*ZIinst)->u.act.rhs;
			args_list* lhs = (*ZIinst)->u.act.lhs;

			/* CHECKING RHS COMPATIBILITY */ 
			if(args_rhs_fill_type(rhs, *locals, (*ZIz)->top_level)) {
				arg* p;
				TypeTupleEntryT* q;
				for ( p = rhs->head, q = action->inputs.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
					if(p->lexi_type!=q->type || p->is_reference!=q->is_reference) {
						char* s = nstring_to_cstring(entry_key(entryaction));
						/* TODO in error message: output type specification of both rhs and inputs*/
						error(ERROR_SERIOUS, "In call to action %s, arguments do not match, TODO should be TODO", s);
						DEALLOCATE(s);
					}
				}
				if(p!=NULL) {
					char* s = nstring_to_cstring(entry_key(entryaction));
					error(ERROR_SERIOUS, "In call to action %s, too many arguments", s);
					DEALLOCATE(s);
				}
				if(q!=NULL) {
					char* s = nstring_to_cstring(entry_key(entryaction));
					error(ERROR_SERIOUS, "In call to action %s, not enough arguments", s);
					DEALLOCATE(s);
				}
			}
			/* CHECKING LHS COMPATIBILITY */ 
     			/* TODO: check that the same reference or identifier does not appear twice in the lhs*/
     			/* TODO: check that no identifier has been set before in the the instruction list*/
			/* TODO: Check that types corresponds including length: beware ignore that match all types */
			/* TODO: Add new variables to localnames */
			/* TODO in case of  errors in lhs match print types of outputs and types of lhs */
		}
		/* TODO only append if no error */
		(*ZIinst)->next=(ZIinstl)->head;
		(ZIinstl)->head=(*ZIinst);
	}
#line 3844 "tmp.syntax.c"
	    }
	    /* END OF ACTION: add-inst-to-list */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-inst-list */
	    {
#line 491 "syntax.act"

    (ZIinstl)=add_instructions_list();
#line 3856 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-inst-list */
	    /* BEGINNING OF ACTION: add-inst-to-list */
	    {
#line 436 "syntax.act"

	if((*ZIinst)!=NULL) { /* if (*ZIinst) == NULL, an error has already been issued.*/
		LocalNamesT** locals = instructionslist_localnamesref((ZIinstl));
		if(((ZIinstl)->head !=NULL) && ((*ZIinst)->type==return_terminal || (*ZIinst)->type==do_nothing)) {
			error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an instruction-list"); 
		}
		if((*ZIinst)->type == apply_function) {
			args_rhs_fill_type((*ZIinst)->u.fun->args, *locals, (*ZIz)->top_level) ;
		}
		if((*ZIinst)->type == action_call) {
			EntryT* entryaction = (*ZIinst)->u.act.called_act;
			ActionT* action = entry_get_action(entryaction);
			args_list* rhs = (*ZIinst)->u.act.rhs;
			args_list* lhs = (*ZIinst)->u.act.lhs;

			/* CHECKING RHS COMPATIBILITY */ 
			if(args_rhs_fill_type(rhs, *locals, (*ZIz)->top_level)) {
				arg* p;
				TypeTupleEntryT* q;
				for ( p = rhs->head, q = action->inputs.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
					if(p->lexi_type!=q->type || p->is_reference!=q->is_reference) {
						char* s = nstring_to_cstring(entry_key(entryaction));
						/* TODO in error message: output type specification of both rhs and inputs*/
						error(ERROR_SERIOUS, "In call to action %s, arguments do not match, TODO should be TODO", s);
						DEALLOCATE(s);
					}
				}
				if(p!=NULL) {
					char* s = nstring_to_cstring(entry_key(entryaction));
					error(ERROR_SERIOUS, "In call to action %s, too many arguments", s);
					DEALLOCATE(s);
				}
				if(q!=NULL) {
					char* s = nstring_to_cstring(entry_key(entryaction));
					error(ERROR_SERIOUS, "In call to action %s, not enough arguments", s);
					DEALLOCATE(s);
				}
			}
			/* CHECKING LHS COMPATIBILITY */ 
     			/* TODO: check that the same reference or identifier does not appear twice in the lhs*/
     			/* TODO: check that no identifier has been set before in the the instruction list*/
			/* TODO: Check that types corresponds including length: beware ignore that match all types */
			/* TODO: Add new variables to localnames */
			/* TODO in case of  errors in lhs match print types of outputs and types of lhs */
		}
		/* TODO only append if no error */
		(*ZIinst)->next=(ZIinstl)->head;
		(ZIinstl)->head=(*ZIinst);
	}
#line 3911 "tmp.syntax.c"
	    }
	    /* END OF ACTION: add-inst-to-list */
	}
	break;
      case 44:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOinstl = ZIinstl;
}

static void
ZR236(zoneP *ZIz, TypeTupleT *ZIa)
{
    switch (CURRENT_TERMINAL) {
      case 0: case 25:
	{
	    ZRtype_Htuple_C_Ctype_Htuple1 (*ZIz, ZIa);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 44:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZRaction_Hcall_C_Crhs_Htuple(args_listP *ZOr)
{
    args_listP ZIr;

    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 16:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 181 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 0: case 1: case 2: case 26: case 33:
	      case 34: case 35: case 36: case 37: case 38:
		{
		    ZRaction_Hcall_C_Crhs_Htuple1 (&ZIr);
		    if ((CURRENT_TERMINAL) == 44) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    /* BEGINNING OF ACTION: empty-args-list */
		    {
#line 422 "syntax.act"

    (ZIr)=add_args_list();
#line 3987 "tmp.syntax.c"
		    }
		    /* END OF ACTION: empty-args-list */
		}
		break;
	    }
	}
	/* END OF INLINE: 181 */
	switch (CURRENT_TERMINAL) {
	  case 17:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOr = ZIr;
}

static void
ZRnon_Hempty_Hchars(zoneP ZIz, SID_CHARS *ZOc)
{
    SID_CHARS ZIc;

    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	ZRchars (ZIz, &ZIc);
	/* BEGINNING OF INLINE: 126 */
	{
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-non-empty */
		{
#line 506 "syntax.act"

    (ZI0)=((ZIc)[0]!=(ZIz)->top_level->last_letter_code);
#line 4033 "tmp.syntax.c"
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
#line 510 "syntax.act"

        error(ERROR_SERIOUS, "Empty character string is not allowed here, try using DEFAULT instead");	
#line 4047 "tmp.syntax.c"
		}
		/* END OF ACTION: E_empty_character_string */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 126 */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRsingle_Harg(argP *ZOa)
{
    argP ZIa;

    switch (CURRENT_TERMINAL) {
      case 33:
	{
	    /* BEGINNING OF EXTRACT: arg-char-list */
	    {
#line 273 "syntax.act"

      ZIa=add_arg(arg_chars_list,0);
#line 4076 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-list */
	    ADVANCE_LEXER;
	}
	break;
      case 35:
	{
	    /* BEGINNING OF EXTRACT: arg-char-nb */
	    {
#line 281 "syntax.act"

      ZIa=add_arg(arg_char_nb,number_buffer);
#line 4089 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-nb */
	    ADVANCE_LEXER;
	}
	break;
      case 34:
	{
	    /* BEGINNING OF EXTRACT: arg-char-string */
	    {
#line 277 "syntax.act"

      ZIa=add_arg(arg_charP,0);
#line 4102 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-string */
	    ADVANCE_LEXER;
	}
	break;
      case 38:
	{
	    /* BEGINNING OF EXTRACT: arg-ignore */
	    {
#line 293 "syntax.act"

      ZIa=add_arg(arg_ignore,0);
#line 4115 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-ignore */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: E_ignore_in_rhs */
	    {
#line 854 "syntax.act"

	error(ERROR_SERIOUS, "Ignore argument in right handside");
#line 4124 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_ignore_in_rhs */
	}
	break;
      case 36:
	{
	    /* BEGINNING OF EXTRACT: arg-nb-of-chars */
	    {
#line 285 "syntax.act"

      ZIa=add_arg(arg_nb_of_chars,0);
#line 4136 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-nb-of-chars */
	    ADVANCE_LEXER;
	}
	break;
      case 37:
	{
	    /* BEGINNING OF EXTRACT: arg-return-terminal */
	    {
#line 289 "syntax.act"

      ZIa=add_arg(arg_return_terminal,0);
#line 4149 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-return-terminal */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: E_return_terminal_in_rhs */
	    {
#line 839 "syntax.act"

	error(ERROR_SERIOUS, "Return terminal argument in right handside");
#line 4158 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_return_terminal_in_rhs */
	}
	break;
      case 0:
	{
	    SID_STRING ZIi;

	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 4172 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_identifier */
	    {
#line 645 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 4181 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_identifier */
	}
	break;
      case 26:
	{
	    SID_STRING ZIi;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 4198 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_reference */
	    {
#line 649 "syntax.act"

	(ZIa) = add_reference_arg ((ZIi));
#line 4211 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_reference */
	}
	break;
      case 1:
	{
	    SID_STRING ZIb;

	    /* BEGINNING OF EXTRACT: sid-identifier */
	    {
#line 222 "syntax.act"

    int n ;
    char *s ;
    char buff [1000] ;
    strcpy ( buff, token_prefix ) ;
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
    ZIb = xstrcpy ( buff ) ;
#line 4246 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: sid-identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_terminal */
	    {
#line 653 "syntax.act"

	(ZIa) = add_terminal_arg ((ZIb));
#line 4255 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_terminal */
	}
	break;
      case 2:
	{
	    SID_STRING ZIb;

	    /* BEGINNING OF EXTRACT: string */
	    {
#line 255 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 4269 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_string */
	    {
#line 641 "syntax.act"

	(ZIa) = add_litteral_arg ((ZIb));
#line 4278 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_string */
	}
	break;
      case 44:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOa = ZIa;
}

static void
ZRaction_Hcall_C_Clhs_Harg(argP *ZOa)
{
    argP ZIa;

    switch (CURRENT_TERMINAL) {
      case 33:
	{
	    argP ZIb;

	    /* BEGINNING OF EXTRACT: arg-char-list */
	    {
#line 273 "syntax.act"

      ZIb=add_arg(arg_chars_list,0);
#line 4311 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-list */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4320 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 831 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4328 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	}
	break;
      case 35:
	{
	    argP ZIb;

	    /* BEGINNING OF EXTRACT: arg-char-nb */
	    {
#line 281 "syntax.act"

      ZIb=add_arg(arg_char_nb,number_buffer);
#line 4342 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-nb */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4351 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 831 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4359 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	}
	break;
      case 34:
	{
	    argP ZIb;

	    /* BEGINNING OF EXTRACT: arg-char-string */
	    {
#line 277 "syntax.act"

      ZIb=add_arg(arg_charP,0);
#line 4373 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4382 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 831 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4390 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	}
	break;
      case 38:
	{
	    /* BEGINNING OF EXTRACT: arg-ignore */
	    {
#line 293 "syntax.act"

      ZIa=add_arg(arg_ignore,0);
#line 4402 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-ignore */
	    ADVANCE_LEXER;
	}
	break;
      case 36:
	{
	    argP ZIb;

	    /* BEGINNING OF EXTRACT: arg-nb-of-chars */
	    {
#line 285 "syntax.act"

      ZIb=add_arg(arg_nb_of_chars,0);
#line 4417 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-nb-of-chars */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4426 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 831 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4434 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	}
	break;
      case 37:
	{
	    /* BEGINNING OF EXTRACT: arg-return-terminal */
	    {
#line 289 "syntax.act"

      ZIa=add_arg(arg_return_terminal,0);
#line 4446 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-return-terminal */
	    ADVANCE_LEXER;
	}
	break;
      case 0:
	{
	    SID_STRING ZIi;

	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 4461 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_identifier */
	    {
#line 645 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 4470 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_identifier */
	}
	break;
      case 26:
	{
	    SID_STRING ZIi;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 4487 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_reference */
	    {
#line 649 "syntax.act"

	(ZIa) = add_reference_arg ((ZIi));
#line 4500 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_reference */
	}
	break;
      case 1:
	{
	    SID_STRING ZIb;

	    /* BEGINNING OF EXTRACT: sid-identifier */
	    {
#line 222 "syntax.act"

    int n ;
    char *s ;
    char buff [1000] ;
    strcpy ( buff, token_prefix ) ;
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
    ZIb = xstrcpy ( buff ) ;
#line 4535 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: sid-identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4544 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_terminal_in_lhs */
	    {
#line 858 "syntax.act"

	error(ERROR_SERIOUS, "Terminal argument in left handside");
#line 4552 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_terminal_in_lhs */
	}
	break;
      case 2:
	{
	    SID_STRING ZIb;

	    /* BEGINNING OF EXTRACT: string */
	    {
#line 255 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 4566 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4575 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_string_arg_in_lhs */
	    {
#line 835 "syntax.act"

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
#line 4583 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_string_arg_in_lhs */
	}
	break;
      case 44:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOa = ZIa;
}

static void
ZRaction_Hcall_C_Crhs_Harg(argP *ZOa)
{
    argP ZIa;

    switch (CURRENT_TERMINAL) {
      case 33:
	{
	    argP ZIb;

	    /* BEGINNING OF EXTRACT: arg-char-list */
	    {
#line 273 "syntax.act"

      ZIb=add_arg(arg_chars_list,0);
#line 4616 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-list */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4625 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_list_in_action_rhs */
	    {
#line 848 "syntax.act"

	error(ERROR_SERIOUS, "Args of style ## are not implemented in actions right hand side. Whether they will be implemented in the future remains undecided at the moment.");
/* TODO take a decision.*/
#line 4634 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_list_in_action_rhs */
	}
	break;
      case 35:
	{
	    /* BEGINNING OF EXTRACT: arg-char-nb */
	    {
#line 281 "syntax.act"

      ZIa=add_arg(arg_char_nb,number_buffer);
#line 4646 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-nb */
	    ADVANCE_LEXER;
	}
	break;
      case 34:
	{
	    /* BEGINNING OF EXTRACT: arg-char-string */
	    {
#line 277 "syntax.act"

      ZIa=add_arg(arg_charP,0);
#line 4659 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-string */
	    ADVANCE_LEXER;
	}
	break;
      case 38:
	{
	    argP ZIb;

	    /* BEGINNING OF EXTRACT: arg-ignore */
	    {
#line 293 "syntax.act"

      ZIb=add_arg(arg_ignore,0);
#line 4674 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-ignore */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4683 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_ignore_in_rhs */
	    {
#line 854 "syntax.act"

	error(ERROR_SERIOUS, "Ignore argument in right handside");
#line 4691 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_ignore_in_rhs */
	}
	break;
      case 36:
	{
	    /* BEGINNING OF EXTRACT: arg-nb-of-chars */
	    {
#line 285 "syntax.act"

      ZIa=add_arg(arg_nb_of_chars,0);
#line 4703 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-nb-of-chars */
	    ADVANCE_LEXER;
	}
	break;
      case 37:
	{
	    argP ZIb;

	    /* BEGINNING OF EXTRACT: arg-return-terminal */
	    {
#line 289 "syntax.act"

      ZIb=add_arg(arg_return_terminal,0);
#line 4718 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-return-terminal */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4727 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_return_terminal_in_rhs */
	    {
#line 839 "syntax.act"

	error(ERROR_SERIOUS, "Return terminal argument in right handside");
#line 4735 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_return_terminal_in_rhs */
	}
	break;
      case 0:
	{
	    SID_STRING ZIi;

	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 4749 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_identifier */
	    {
#line 645 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 4758 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_identifier */
	}
	break;
      case 26:
	{
	    SID_STRING ZIi;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 4775 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_reference */
	    {
#line 649 "syntax.act"

	(ZIa) = add_reference_arg ((ZIi));
#line 4788 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_reference */
	}
	break;
      case 1:
	{
	    SID_STRING ZIb;

	    /* BEGINNING OF EXTRACT: sid-identifier */
	    {
#line 222 "syntax.act"

    int n ;
    char *s ;
    char buff [1000] ;
    strcpy ( buff, token_prefix ) ;
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
    ZIb = xstrcpy ( buff ) ;
#line 4823 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: sid-identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_terminal */
	    {
#line 653 "syntax.act"

	(ZIa) = add_terminal_arg ((ZIb));
#line 4832 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_terminal */
	}
	break;
      case 2:
	{
	    SID_STRING ZIb;

	    /* BEGINNING OF EXTRACT: string */
	    {
#line 255 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 4846 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4855 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_string_in_action_rhs */
	    {
#line 843 "syntax.act"

	error(ERROR_SERIOUS, "String argument in right handside of action call: purposefuly not implemented to avoid confusions. Will be implemented with an alternate meaning once direct function calls are removed from lexi");
#line 4863 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_string_in_action_rhs */
	}
	break;
      case 44:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (44);
    return;
  ZL0:;
    *ZOa = ZIa;
}

/* BEGINNING OF TRAILER */

#line 862 "syntax.act"

#line 4885 "tmp.syntax.c"

/* END OF FILE */
