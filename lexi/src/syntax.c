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

static void ZRexpected__semicolon(void);
static void ZRtuple_Hargs(args_listP *);
static void ZRzone_Hdefn(zoneP);
static void ZRstring_Hplus(SID_STRING *);
static void ZRtype_Hdefn(zoneP);
static void ZRchars(zoneP, SID_CHARS *);
static void ZR153(void);
static void ZRaction_Hcall_C_Clhs_Htuple1(args_listP *);
static void ZRtype_Htuple(zoneP, TypeTupleT *);
static void ZRaction_Hcall_C_Crhs_Htuple1(args_listP *);
static void ZR171(args_listP *);
static void ZRinstructions_Hlist(zoneP, instructions_listP *);
static void ZRtype_Htuple_C_Ctype_Hname(zoneP, TypeTupleT *);
static void ZRargs(args_listP *);
static void ZRtrigraph_Hdefn(zoneP);
extern void read_lex(zoneP);
static void ZR196(zoneP *, SID_CHARS *);
static void ZR198(zoneP *, instructions_listP *);
static void ZRaction_Hdecl(zoneP);
static void ZRinstruction(zoneP, instructionP *);
static void ZRcommand_Hlist(zoneP);
static void ZR212(zoneP *);
static void ZR213(zoneP *);
static void ZRkeyword_Hdefn(zoneP);
static void ZRcopyright_Hstmt(zoneP);
static void ZR217(zoneP *, SID_STRING *, instructionP *);
static void ZR219(zoneP *, SID_STRING *, instructionP *);
static void ZR220(argP *, args_listP *);
static void ZR221(argP *, args_listP *);
static void ZR222(argP *, args_listP *);
static void ZR223(zoneP *, instructionP *, instructions_listP *);
static void ZR225(zoneP *, TypeTupleT *);
static void ZRif_Hcommand(zoneP);
static void ZRcommand(zoneP);
static void ZRnon_Hempty_Htuple_Hargs(args_listP *);
static void ZRaction_Hcall_C_Crhs_Htuple(args_listP *);
static void ZRnon_Hempty_Hchars(zoneP, SID_CHARS *);
static void ZRsingle_Harg(argP *);
static void ZRaction_Hcall_C_Clhs_Harg(argP *);
static void ZR125(void);
static void ZRaction_Hcall_C_Crhs_Harg(argP *);

/* BEGINNING OF STATIC VARIABLES */

static int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

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
#line 795 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected semicolon \';\'");
#line 193 "tmp.syntax.c"
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
#line 213 "tmp.syntax.c"
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
#line 237 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: arg-char-list-tmp */
	    {
#line 407 "syntax.act"

      (ZItmp)=add_arg(arg_chars_list,0);
#line 245 "tmp.syntax.c"
	    }
	    /* END OF ACTION: arg-char-list-tmp */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZItmp)->next=(ZIl)->head;
    (ZIl)->head=(ZItmp);
#line 254 "tmp.syntax.c"
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
	/* BEGINNING OF INLINE: 188 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 0:
		    /* BEGINNING OF EXTRACT: identifier */
		    {
#line 210 "syntax.act"

    ZIzid = xstrcpy ( token_buff ) ;
#line 302 "tmp.syntax.c"
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
#line 777 "syntax.act"

	(ZIzid)="";
	error(ERROR_SERIOUS, "Syntax error: expected identifier");
#line 320 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_identifier */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 188 */
	/* BEGINNING OF INLINE: 190 */
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
#line 791 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected colon \':\'");
#line 346 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_colon */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 190 */
	ZR196 (&ZIz, &ZIb);
	ZR198 (&ZIz, &ZIentry_Hinstl);
	/* BEGINNING OF INLINE: 194 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 27:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: true */
		    {
#line 611 "syntax.act"
 (ZIlendclosed) = 1 ; 
#line 365 "tmp.syntax.c"
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
#line 377 "tmp.syntax.c"
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
#line 389 "tmp.syntax.c"
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
#line 782 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected range");
#line 408 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_range */
		/* BEGINNING OF ACTION: false */
		{
#line 612 "syntax.act"
 (ZIlendclosed) = 0 ; 
#line 415 "tmp.syntax.c"
		}
		/* END OF ACTION: false */
	    }
	  ZL6:;
	}
	/* END OF INLINE: 194 */
	ZR196 (&ZIz, &ZIe);
	ZR198 (&ZIz, &ZIleaving_Hinstl);
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
#line 442 "tmp.syntax.c"
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

	/* BEGINNING OF INLINE: 112 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 5:
		{
		    /* BEGINNING OF EXTRACT: digit */
		    {
#line 268 "syntax.act"
 ZIa = "0123456789" ; 
#line 490 "tmp.syntax.c"
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
#line 502 "tmp.syntax.c"
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
#line 515 "tmp.syntax.c"
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
#line 527 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: upper */
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	/* END OF INLINE: 112 */
	/* BEGINNING OF INLINE: 114 */
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
#line 556 "tmp.syntax.c"
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
	/* END OF INLINE: 114 */
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
#line 601 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 139 */
	{
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 667 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 617 "tmp.syntax.c"
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
#line 644 "tmp.syntax.c"
		}
		/* END OF ACTION: make-type */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonetype */
		{
#line 766 "syntax.act"

    error( ERROR_SERIOUS, "Syntax error: type %s should not be declared inside a zone",(ZIs)) ;
#line 656 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonetype */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 139 */
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
#line 329 "syntax.act"

    (ZIc) = make_string ( (ZIs), (ZIz) ) ;
#line 691 "tmp.syntax.c"
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
ZR153(void)
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
#line 799 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected arrow \'->\'");
#line 726 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_arrow */
    }
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
	ZR221 (&ZIa, &ZIl);
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
#line 772 "tmp.syntax.c"
	}
	/* END OF ACTION: init-tuple */
	ZR225 (&ZIz, &ZIa);
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
#line 791 "tmp.syntax.c"
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
	ZR220 (&ZIa, &ZIr);
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
ZR171(args_listP *ZOr)
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
#line 844 "tmp.syntax.c"
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
	ZR223 (&ZIz, &ZIinst, &ZIinstl);
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
#line 896 "tmp.syntax.c"
    }
    /* END OF PARAM ASSIGNMENT: TYPETUPLE */
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	SID_STRING ZIname;
	SID_STRING ZItype;
	int ZIisref;

	switch (CURRENT_TERMINAL) {
	  case 0:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 210 "syntax.act"

    ZIname = xstrcpy ( token_buff ) ;
#line 914 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
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
#line 936 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 145 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 26:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: true */
		    {
#line 611 "syntax.act"
 (ZIisref) = 1 ; 
#line 954 "tmp.syntax.c"
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
#line 965 "tmp.syntax.c"
		    }
		    /* END OF ACTION: false */
		}
		break;
	    }
	}
	/* END OF INLINE: 145 */
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
		 nstring_destroy(&tstr);
	}
	else if(!entry_is_type(entry))
		 error(ERROR_SERIOUS, "%s is not a type", (ZItype));
	else
		typetuple_append((&ZIa),typetupleentry_create(&istr,entry,(ZIisref)));
	xfree((ZItype));
	xfree((ZIname));
#line 992 "tmp.syntax.c"
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
#line 1031 "tmp.syntax.c"
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
	ZR153 ();
	ZRstring_Hplus (&ZIt);
	if ((CURRENT_TERMINAL) == 44) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-trigraph */
	{
#line 367 "syntax.act"

    add_char ( (ZIz), (ZIz)->zone_pre_pass, (ZIs), crt_cond, NULL, (ZIt)) ;
#line 1076 "tmp.syntax.c"
	}
	/* END OF ACTION: make-trigraph */
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

void
read_lex(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	ZRcommand_Hlist (ZIz);
	/* BEGINNING OF INLINE: 203 */
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
#line 807 "syntax.act"

	error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1117 "tmp.syntax.c"
		}
		/* END OF ACTION: syntax-error */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 203 */
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZR196(zoneP *ZIz, SID_CHARS *ZOe)
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
#line 786 "syntax.act"

        (ZIe) = NULL ;
	error(ERROR_SERIOUS, "Syntax error: expected characters");
#line 1155 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_chars */
    }
  ZL0:;
    *ZOe = ZIe;
}

static void
ZR198(zoneP *ZIz, instructions_listP *ZOleaving_Hinstl)
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
#line 1186 "tmp.syntax.c"
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
#line 1234 "tmp.syntax.c"
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
	/* BEGINNING OF INLINE: 150 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 25:
		{
		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 16:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    ZRtype_Htuple (ZIz, &ZIit);
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
		    ZR153 ();
		    switch (CURRENT_TERMINAL) {
		      case 16:
			break;
		      case 44:
			RESTORE_LEXER;
			goto ZL1;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    ZRtype_Htuple (ZIz, &ZIot);
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
		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 729 "syntax.act"

	typetuple_init(&(ZIit));
#line 1304 "tmp.syntax.c"
		    }
		    /* END OF ACTION: init-tuple */
		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 729 "syntax.act"

	typetuple_init(&(ZIot));
#line 1312 "tmp.syntax.c"
		    }
		    /* END OF ACTION: init-tuple */
		}
		break;
	    }
	}
	/* END OF INLINE: 150 */
	/* BEGINNING OF ACTION: make-action */
	{
#line 704 "syntax.act"

	NStringT str;
	nstring_copy_cstring(&str, (ZIi));
	xfree((ZIi));
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
#line 1342 "tmp.syntax.c"
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
#line 1371 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-list */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 1380 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 811 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1388 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 1396 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1405 "tmp.syntax.c"
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
#line 1429 "tmp.syntax.c"
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
	    ZR171 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 389 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry))
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		else
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 1467 "tmp.syntax.c"
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
#line 1485 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-nb */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 1494 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 811 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1502 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 1510 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1519 "tmp.syntax.c"
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
#line 1543 "tmp.syntax.c"
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
	    ZR171 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 389 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry))
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		else
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 1581 "tmp.syntax.c"
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
#line 1599 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 1608 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 811 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1616 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 1624 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1633 "tmp.syntax.c"
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
#line 1657 "tmp.syntax.c"
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
	    ZR171 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 389 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry))
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		else
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 1695 "tmp.syntax.c"
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
#line 1712 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-ignore */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 1721 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1730 "tmp.syntax.c"
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
#line 1754 "tmp.syntax.c"
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
	    ZR171 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 389 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry))
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		else
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 1792 "tmp.syntax.c"
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
#line 1810 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-nb-of-chars */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 1819 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 811 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1827 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 1835 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1844 "tmp.syntax.c"
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
#line 1868 "tmp.syntax.c"
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
	    ZR171 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 389 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry))
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		else
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 1906 "tmp.syntax.c"
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
#line 1923 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-return-terminal */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 1932 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1941 "tmp.syntax.c"
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
#line 1965 "tmp.syntax.c"
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
	    ZR171 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 389 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry))
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		else
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2003 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 0:
	{
	    SID_STRING ZI216;

	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 210 "syntax.act"

    ZI216 = xstrcpy ( token_buff ) ;
#line 2017 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    ZR217 (&ZIz, &ZI216, &ZIinst);
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
#line 2067 "tmp.syntax.c"
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
	    ZR171 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 389 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry))
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		else
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2105 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 26:
	{
	    SID_STRING ZI215;
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

    ZI215 = xstrcpy ( token_buff ) ;
#line 2126 "tmp.syntax.c"
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

	(ZIa) = add_reference_arg ((ZI215));
#line 2139 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_reference */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 2147 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 2156 "tmp.syntax.c"
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
#line 2180 "tmp.syntax.c"
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
	    ZR171 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 389 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry))
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		else
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2218 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 1:
	{
	    SID_STRING ZI218;

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
    ZI218 = xstrcpy ( buff ) ;
#line 2253 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: sid-identifier */
	    ADVANCE_LEXER;
	    ZR219 (&ZIz, &ZI218, &ZIinst);
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
#line 2277 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 2286 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_string_arg_in_lhs */
	    {
#line 815 "syntax.act"

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
#line 2294 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_string_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 2302 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 2311 "tmp.syntax.c"
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
#line 2335 "tmp.syntax.c"
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
	    ZR171 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 389 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry))
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		else
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2373 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 31:
	{
	    /* BEGINNING OF INLINE: 174 */
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
#line 385 "syntax.act"

	(ZIinst)=add_instruction_donothing();
#line 2395 "tmp.syntax.c"
		    }
		    /* END OF ACTION: make-donothing-inst */
		}
	    }
	    /* END OF INLINE: 174 */
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
#line 2414 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2425 "tmp.syntax.c"
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
	    ZR171 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 389 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry))
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		else
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2463 "tmp.syntax.c"
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
#line 807 "syntax.act"

	error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 2514 "tmp.syntax.c"
	}
	/* END OF ACTION: syntax-error */
    }
}

static void
ZR212(zoneP *ZIz)
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
#line 2534 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    ZR125 ();
	    ZRchars (*ZIz, &ZIs);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-group */
	    {
#line 356 "syntax.act"

    make_group ( (*ZIz), (ZIi), (ZIs) ) ;
#line 2549 "tmp.syntax.c"
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
	    ZR125 ();
	    ZRchars (*ZIz, &ZIs);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-white */
	    {
#line 342 "syntax.act"

    if ( (*ZIz)->white_space) {
	error ( ERROR_SERIOUS, "White space group already defined" ) ;
    }
    (*ZIz)->white_space= make_group((*ZIz),"white",(ZIs)) ;
#line 2578 "tmp.syntax.c"
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
ZR213(zoneP *ZIz)
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
#line 2626 "tmp.syntax.c"
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
#line 2662 "tmp.syntax.c"
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
#line 2707 "tmp.syntax.c"
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
	/* BEGINNING OF INLINE: 181 */
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
#line 2735 "tmp.syntax.c"
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
#line 2759 "tmp.syntax.c"
		}
		/* END OF ACTION: make-keyword */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonekeyword */
		{
#line 756 "syntax.act"

    error( ERROR_SERIOUS, "Keywords not yet implemented in a non global zone ") ;

#line 2772 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonekeyword */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 181 */
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
#line 2816 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 123 */
	{
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 667 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 2832 "tmp.syntax.c"
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
#line 2850 "tmp.syntax.c"
		}
		/* END OF ACTION: make-copyright */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonecopyright */
		{
#line 761 "syntax.act"

    error( ERROR_SERIOUS, "Syntax error: A copyright file may only be specified in the global zone") ;
#line 2862 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonecopyright */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 123 */
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZR217(zoneP *ZIz, SID_STRING *ZI216, instructionP *ZOinst)
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
#line 376 "syntax.act"

    if((ZIa)) {
        (ZIinst)=add_instruction_function((*ZI216),(ZIa));
    } 
    else {
        (ZIinst)=add_instruction_return_terminal((*ZI216));
    }
#line 2901 "tmp.syntax.c"
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

	(ZIa) = add_identifier_arg ((*ZI216));
#line 2918 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_identifier */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 2926 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 2935 "tmp.syntax.c"
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
#line 2953 "tmp.syntax.c"
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
	    ZR171 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 389 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry))
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		else
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2991 "tmp.syntax.c"
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
ZR219(zoneP *ZIz, SID_STRING *ZI218, instructionP *ZOinst)
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
#line 3025 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_terminal_in_lhs */
	    {
#line 838 "syntax.act"

	error(ERROR_SERIOUS, "Terminal argument in left handside");
#line 3033 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_terminal_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 422 "syntax.act"

    (ZIl)=add_args_list();
#line 3041 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 3050 "tmp.syntax.c"
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
#line 3068 "tmp.syntax.c"
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
	    ZR171 (&ZIr);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 389 "syntax.act"

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry((*ZIz)->top_level->table, &key);
	if(entry) {
		if(entry_is_action(entry))
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		else
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 3106 "tmp.syntax.c"
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
#line 3120 "tmp.syntax.c"
	    }
	    /* END OF ACTION: null-args-list */
	    /* BEGINNING OF ACTION: make-inst */
	    {
#line 376 "syntax.act"

    if((ZIa)) {
        (ZIinst)=add_instruction_function((*ZI218),(ZIa));
    } 
    else {
        (ZIinst)=add_instruction_return_terminal((*ZI218));
    }
#line 3133 "tmp.syntax.c"
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
ZR220(argP *ZIa, args_listP *ZOr)
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
#line 3169 "tmp.syntax.c"
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
#line 3181 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (*ZIa)->next=(ZIr)->head;
    (ZIr)->head=(*ZIa);
#line 3190 "tmp.syntax.c"
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
ZR221(argP *ZIa, args_listP *ZOl)
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
#line 3226 "tmp.syntax.c"
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
#line 3238 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 3247 "tmp.syntax.c"
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
ZR222(argP *ZIa, args_listP *ZOl)
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
#line 3283 "tmp.syntax.c"
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
#line 3295 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 414 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 3304 "tmp.syntax.c"
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
ZR223(zoneP *ZIz, instructionP *ZIinst, instructions_listP *ZOinstl)
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
#line 3386 "tmp.syntax.c"
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
#line 3398 "tmp.syntax.c"
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
#line 3453 "tmp.syntax.c"
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
ZR225(zoneP *ZIz, TypeTupleT *ZIa)
{
  ZL2_225:;
    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    /* BEGINNING OF INLINE: type-tuple::type-tuple1 */
	    {
		{
		    ZRtype_Htuple_C_Ctype_Hname (*ZIz, ZIa);
		    /* BEGINNING OF INLINE: 225 */
		    if ((CURRENT_TERMINAL) == 44) {
			RESTORE_LEXER;
			goto ZL1;
		    } else {
			goto ZL2_225;
		    }
		    /* END OF INLINE: 225 */
		}
		/*UNREACHED*/
	    }
	    /* END OF INLINE: type-tuple::type-tuple1 */
	}
	/*UNREACHED*/
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
#line 3536 "tmp.syntax.c"
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
#line 3556 "tmp.syntax.c"
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
#line 3568 "tmp.syntax.c"
	}
	/* END OF ACTION: add-condition */
	ZRcommand (ZIz);
	/* BEGINNING OF INLINE: 186 */
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
#line 3597 "tmp.syntax.c"
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
#line 3610 "tmp.syntax.c"
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
#line 3622 "tmp.syntax.c"
		}
		/* END OF ACTION: set-condition */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 186 */
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
	    ZR212 (&ZIz);
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
	    ZR213 (&ZIz);
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
ZRnon_Hempty_Htuple_Hargs(args_listP *ZOl)
{
    args_listP ZIl;

    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	argP ZIa;

	ZRsingle_Harg (&ZIa);
	ZR222 (&ZIa, &ZIl);
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
	/* BEGINNING OF INLINE: 169 */
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
#line 3822 "tmp.syntax.c"
		    }
		    /* END OF ACTION: empty-args-list */
		}
		break;
	    }
	}
	/* END OF INLINE: 169 */
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
	/* BEGINNING OF INLINE: 121 */
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
#line 3868 "tmp.syntax.c"
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
#line 3882 "tmp.syntax.c"
		}
		/* END OF ACTION: E_empty_character_string */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 121 */
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
#line 3911 "tmp.syntax.c"
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
#line 3924 "tmp.syntax.c"
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
#line 3937 "tmp.syntax.c"
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
#line 3950 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-ignore */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: E_ignore_in_rhs */
	    {
#line 834 "syntax.act"

	error(ERROR_SERIOUS, "Ignore argument in right handside");
#line 3959 "tmp.syntax.c"
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
#line 3971 "tmp.syntax.c"
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
#line 3984 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-return-terminal */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: E_return_terminal_in_rhs */
	    {
#line 819 "syntax.act"

	error(ERROR_SERIOUS, "Return terminal argument in right handside");
#line 3993 "tmp.syntax.c"
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
#line 4007 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_identifier */
	    {
#line 645 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 4016 "tmp.syntax.c"
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
#line 4033 "tmp.syntax.c"
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
#line 4046 "tmp.syntax.c"
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
#line 4081 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: sid-identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_terminal */
	    {
#line 653 "syntax.act"

	(ZIa) = add_terminal_arg ((ZIb));
#line 4090 "tmp.syntax.c"
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
#line 4104 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_string */
	    {
#line 641 "syntax.act"

	(ZIa) = add_litteral_arg ((ZIb));
#line 4113 "tmp.syntax.c"
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
#line 4146 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-list */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4155 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 811 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4163 "tmp.syntax.c"
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
#line 4177 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-nb */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4186 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 811 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4194 "tmp.syntax.c"
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
#line 4208 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4217 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 811 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4225 "tmp.syntax.c"
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
#line 4237 "tmp.syntax.c"
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
#line 4252 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-nb-of-chars */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4261 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 811 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4269 "tmp.syntax.c"
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
#line 4281 "tmp.syntax.c"
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
#line 4296 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_identifier */
	    {
#line 645 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 4305 "tmp.syntax.c"
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
#line 4322 "tmp.syntax.c"
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
#line 4335 "tmp.syntax.c"
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
#line 4370 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: sid-identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4379 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_terminal_in_lhs */
	    {
#line 838 "syntax.act"

	error(ERROR_SERIOUS, "Terminal argument in left handside");
#line 4387 "tmp.syntax.c"
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
#line 4401 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4410 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_string_arg_in_lhs */
	    {
#line 815 "syntax.act"

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
#line 4418 "tmp.syntax.c"
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
ZR125(void)
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
#line 803 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected equal \'=\'");
#line 4459 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_equal */
    }
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
#line 4480 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-list */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4489 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_list_in_action_rhs */
	    {
#line 828 "syntax.act"

	error(ERROR_SERIOUS, "Args of style ## are not implemented in actions right hand side. Whether they will be implemented in the future remains undecided at the moment.");
/* TODO take a decision.*/
#line 4498 "tmp.syntax.c"
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
#line 4510 "tmp.syntax.c"
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
#line 4523 "tmp.syntax.c"
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
#line 4538 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-ignore */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4547 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_ignore_in_rhs */
	    {
#line 834 "syntax.act"

	error(ERROR_SERIOUS, "Ignore argument in right handside");
#line 4555 "tmp.syntax.c"
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
#line 4567 "tmp.syntax.c"
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
#line 4582 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-return-terminal */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4591 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_return_terminal_in_rhs */
	    {
#line 819 "syntax.act"

	error(ERROR_SERIOUS, "Return terminal argument in right handside");
#line 4599 "tmp.syntax.c"
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
#line 4613 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_identifier */
	    {
#line 645 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 4622 "tmp.syntax.c"
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
#line 4639 "tmp.syntax.c"
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
#line 4652 "tmp.syntax.c"
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
#line 4687 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: sid-identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_terminal */
	    {
#line 653 "syntax.act"

	(ZIa) = add_terminal_arg ((ZIb));
#line 4696 "tmp.syntax.c"
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
#line 4710 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 658 "syntax.act"

	(ZIa) = add_none_arg();
#line 4719 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_string_in_action_rhs */
	    {
#line 823 "syntax.act"

	error(ERROR_SERIOUS, "String argument in right handside of action call: purposefuly not implemented to avoid confusions. Will be implemented with an alternate meaning once direct function calls are removed from lexi");
#line 4727 "tmp.syntax.c"
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

#line 842 "syntax.act"

#line 4749 "tmp.syntax.c"

/* END OF FILE */
