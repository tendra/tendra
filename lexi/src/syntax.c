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

static void ZR135(void);
static void ZRexpected__semicolon(void);
static void ZRtuple_Hargs(args_listP *);
static void ZRzone_Hdefn(zoneP);
static void ZRstring_Hplus(SID_STRING *);
static void ZRtype_Hdefn(zoneP);
static void ZRchars(zoneP, SID_CHARS *);
static void ZRaction_Hcall_C_Clhs_Htuple1(args_listP *);
static void ZRtype_Htuple(zoneP, TypeTupleT *);
static void ZRaction_Hcall_C_Crhs_Htuple1(args_listP *);
static void ZR165(void);
static void ZR166(void);
static void ZR167(void);
static void ZRinstructions_Hlist(zoneP, instructions_listP *);
static void ZRtype_Htuple_C_Ctype_Hname(zoneP, TypeTupleT *);
static void ZRargs(args_listP *);
static void ZRtrigraph_Hdefn(zoneP);
static void ZR185(args_listP *);
extern void read_lex(zoneP);
static void ZRaction_Hdecl(zoneP);
static void ZRinstruction(zoneP, instructionP *);
static void ZRcommand_Hlist(zoneP);
static void ZR210(zoneP *, SID_CHARS *);
static void ZR212(zoneP *, instructions_listP *);
static void ZRkeyword_Hdefn(zoneP);
static void ZRcopyright_Hstmt(zoneP);
static void ZRif_Hcommand(zoneP);
static void ZR226(zoneP *);
static void ZR227(zoneP *);
static void ZRcommand(zoneP);
static void ZRnon_Hempty_Htuple_Hargs(args_listP *);
static void ZR231(zoneP *, SID_STRING *, instructionP *);
static void ZRtype_Htuple_C_Ctype_Htuple1(zoneP, TypeTupleT *);
static void ZR233(zoneP *, SID_STRING *, instructionP *);
static void ZR234(argP *, args_listP *);
static void ZR235(argP *, args_listP *);
static void ZR236(argP *, args_listP *);
static void ZR237(zoneP *, instructionP *, instructions_listP *);
static void ZR238(zoneP *, TypeTupleT *);
static void ZRaction_Hcall_C_Crhs_Htuple(args_listP *);
static void ZRnon_Hempty_Hchars(zoneP, SID_CHARS *);
static void ZRsingle_Harg(argP *);
static void ZRaction_Hcall_C_Clhs_Harg(argP *);
static void ZRaction_Hcall_C_Crhs_Harg(argP *);

/* BEGINNING OF STATIC VARIABLES */

static int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZR135(void)
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
#line 958 "syntax.act"

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
#line 950 "syntax.act"

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
#line 436 "syntax.act"

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
#line 436 "syntax.act"

    (ZIl)=add_args_list();
#line 269 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: arg-char-list-tmp */
	    {
#line 421 "syntax.act"

      (ZItmp)=add_arg(arg_chars_list,0);
#line 277 "tmp.syntax.c"
	    }
	    /* END OF ACTION: arg-char-list-tmp */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 428 "syntax.act"

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
	/* BEGINNING OF INLINE: 202 */
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
#line 924 "syntax.act"

	(ZIzid)="";
	error(ERROR_SERIOUS, "Syntax error: expected identifier");
#line 352 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_identifier */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 202 */
	/* BEGINNING OF INLINE: 204 */
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
#line 946 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected colon \':\'");
#line 378 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_colon */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 204 */
	ZR210 (&ZIz, &ZIb);
	ZR212 (&ZIz, &ZIentry_Hinstl);
	/* BEGINNING OF INLINE: 208 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 27:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: true */
		    {
#line 755 "syntax.act"
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
#line 755 "syntax.act"
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
#line 756 "syntax.act"
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
#line 929 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected range");
#line 440 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_range */
		/* BEGINNING OF ACTION: false */
		{
#line 756 "syntax.act"
 (ZIlendclosed) = 0 ; 
#line 447 "tmp.syntax.c"
		}
		/* END OF ACTION: false */
	    }
	  ZL6:;
	}
	/* END OF INLINE: 208 */
	ZR210 (&ZIz, &ZIe);
	ZR212 (&ZIz, &ZIleaving_Hinstl);
	if ((CURRENT_TERMINAL) == 44) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-zone */
	{
#line 772 "syntax.act"

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

	/* BEGINNING OF INLINE: 119 */
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
	/* END OF INLINE: 119 */
	/* BEGINNING OF INLINE: 121 */
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
	/* END OF INLINE: 121 */
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
	/* BEGINNING OF INLINE: 146 */
	{
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 811 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 649 "tmp.syntax.c"
		}
		/* END OF ACTION: is-global-zone */
		if (!ZI0)
		    goto ZL3;
		/* BEGINNING OF ACTION: make-type */
		{
#line 827 "syntax.act"

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
#line 913 "syntax.act"

    error( ERROR_SERIOUS, "Syntax error: type %s should not be declared inside a zone",(ZIs)) ;
#line 688 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonetype */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 146 */
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
	ZR235 (&ZIa, &ZIl);
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
#line 873 "syntax.act"

	typetuple_init(&(ZIa));
#line 775 "tmp.syntax.c"
	}
	/* END OF ACTION: init-tuple */
	ZR238 (&ZIz, &ZIa);
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
	ZR234 (&ZIa, &ZIr);
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
ZR165(void)
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
#line 954 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected arrow \'->\'");
#line 848 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_arrow */
    }
}

static void
ZR166(void)
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
#line 933 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected open \'(\'");
#line 877 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_open */
    }
}

static void
ZR167(void)
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
#line 937 "syntax.act"

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
	ZR237 (&ZIz, &ZIinst, &ZIinstl);
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
ZRtype_Htuple_C_Ctype_Hname(zoneP ZIz, TypeTupleT *ZIa)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
    {
	SID_STRING ZIname;
	SID_STRING ZItype;
	int ZIisref;

	/* BEGINNING OF INLINE: 150 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 0:
		{
		    /* BEGINNING OF EXTRACT: identifier */
		    {
#line 210 "syntax.act"

    ZIname = xstrcpy ( token_buff ) ;
#line 959 "tmp.syntax.c"
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

    (ZIname) = xstrcpy("");
#line 972 "tmp.syntax.c"
		    }
		    /* END OF ACTION: empty-identifier */
		}
		break;
	    }
	}
	/* END OF INLINE: 150 */
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
#line 994 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 153 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 26:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: true */
		    {
#line 755 "syntax.act"
 (ZIisref) = 1 ; 
#line 1012 "tmp.syntax.c"
		    }
		    /* END OF ACTION: true */
		}
		break;
	      default:
		{
		    /* BEGINNING OF ACTION: false */
		    {
#line 756 "syntax.act"
 (ZIisref) = 0 ; 
#line 1023 "tmp.syntax.c"
		    }
		    /* END OF ACTION: false */
		}
		break;
	    }
	}
	/* END OF INLINE: 153 */
	/* BEGINNING OF ACTION: append-tuple */
	{
#line 877 "syntax.act"

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
		typetuple_append((ZIa),typetupleentry_create(&istr,entry,(ZIisref)));
	}
	nstring_destroy(&tstr);
	xfree((ZItype));
	xfree((ZIname));
#line 1053 "tmp.syntax.c"
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
#line 443 "syntax.act"

    (ZIl) = NULL ;
#line 1092 "tmp.syntax.c"
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
	ZR165 ();
	ZRstring_Hplus (&ZIt);
	if ((CURRENT_TERMINAL) == 44) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-trigraph */
	{
#line 365 "syntax.act"

    add_char ( (ZIz), (ZIz)->zone_pre_pass, (ZIs), crt_cond, NULL, (ZIt)) ;
#line 1137 "tmp.syntax.c"
	}
	/* END OF ACTION: make-trigraph */
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZR185(args_listP *ZOr)
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
#line 436 "syntax.act"

    (ZIr)=add_args_list();
#line 1169 "tmp.syntax.c"
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
	/* BEGINNING OF INLINE: 217 */
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
#line 971 "syntax.act"

	error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1216 "tmp.syntax.c"
		}
		/* END OF ACTION: syntax-error */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 217 */
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
	/* BEGINNING OF INLINE: 158 */
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
#line 962 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected begin action \'<\'");
#line 1267 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_begin_action */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 158 */
	switch (CURRENT_TERMINAL) {
	  case 0:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 1281 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 159 */
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
#line 966 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected end action \'>\'");
#line 1308 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_end_action */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 159 */
	/* BEGINNING OF INLINE: 160 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 25:
		{
		    ADVANCE_LEXER;
		    ZR166 ();
		    ZRtype_Htuple (ZIz, &ZIit);
		    ZR167 ();
		    ZR165 ();
		    ZR166 ();
		    ZRtype_Htuple (ZIz, &ZIot);
		    ZR167 ();
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
#line 873 "syntax.act"

	typetuple_init(&(ZIit));
#line 1341 "tmp.syntax.c"
		    }
		    /* END OF ACTION: init-tuple */
		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 873 "syntax.act"

	typetuple_init(&(ZIot));
#line 1349 "tmp.syntax.c"
		    }
		    /* END OF ACTION: init-tuple */
		}
		break;
	    }
	}
	/* END OF INLINE: 160 */
	/* BEGINNING OF ACTION: make-action */
	{
#line 848 "syntax.act"

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
#line 1379 "tmp.syntax.c"
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
#line 1408 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-list */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 1417 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 975 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1425 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 436 "syntax.act"

    (ZIl)=add_args_list();
#line 1433 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 428 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1442 "tmp.syntax.c"
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
#line 1466 "tmp.syntax.c"
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
	    ZR185 (&ZIr);
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
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.litteral, q->u.litteral)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.litteral);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 1520 "tmp.syntax.c"
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
#line 1538 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-nb */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 1547 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 975 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1555 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 436 "syntax.act"

    (ZIl)=add_args_list();
#line 1563 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 428 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1572 "tmp.syntax.c"
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
#line 1596 "tmp.syntax.c"
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
	    ZR185 (&ZIr);
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
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.litteral, q->u.litteral)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.litteral);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 1650 "tmp.syntax.c"
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
#line 1668 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 1677 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 975 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1685 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 436 "syntax.act"

    (ZIl)=add_args_list();
#line 1693 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 428 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1702 "tmp.syntax.c"
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
#line 1726 "tmp.syntax.c"
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
	    ZR185 (&ZIr);
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
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.litteral, q->u.litteral)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.litteral);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 1780 "tmp.syntax.c"
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
#line 1797 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-ignore */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 436 "syntax.act"

    (ZIl)=add_args_list();
#line 1806 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 428 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1815 "tmp.syntax.c"
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
#line 1839 "tmp.syntax.c"
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
	    ZR185 (&ZIr);
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
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.litteral, q->u.litteral)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.litteral);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 1893 "tmp.syntax.c"
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
#line 1911 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-nb-of-chars */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 1920 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 975 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1928 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 436 "syntax.act"

    (ZIl)=add_args_list();
#line 1936 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 428 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1945 "tmp.syntax.c"
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
#line 1969 "tmp.syntax.c"
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
	    ZR185 (&ZIr);
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
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.litteral, q->u.litteral)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.litteral);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2023 "tmp.syntax.c"
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
#line 2040 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-return-terminal */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 436 "syntax.act"

    (ZIl)=add_args_list();
#line 2049 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 428 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 2058 "tmp.syntax.c"
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
#line 2082 "tmp.syntax.c"
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
	    ZR185 (&ZIr);
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
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.litteral, q->u.litteral)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.litteral);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2136 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 0:
	{
	    SID_STRING ZI230;

	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 210 "syntax.act"

    ZI230 = xstrcpy ( token_buff ) ;
#line 2150 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    ZR231 (&ZIz, &ZI230, &ZIinst);
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
#line 2200 "tmp.syntax.c"
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
	    ZR185 (&ZIr);
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
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.litteral, q->u.litteral)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.litteral);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2254 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 26:
	{
	    SID_STRING ZI229;
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

    ZI229 = xstrcpy ( token_buff ) ;
#line 2275 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_reference */
	    {
#line 793 "syntax.act"

	(ZIa) = add_reference_arg ((ZI229));
#line 2288 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_reference */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 436 "syntax.act"

    (ZIl)=add_args_list();
#line 2296 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 428 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 2305 "tmp.syntax.c"
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
#line 2329 "tmp.syntax.c"
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
	    ZR185 (&ZIr);
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
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.litteral, q->u.litteral)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.litteral);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2383 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 1:
	{
	    SID_STRING ZI232;

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
    ZI232 = xstrcpy ( buff ) ;
#line 2418 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: sid-identifier */
	    ADVANCE_LEXER;
	    ZR233 (&ZIz, &ZI232, &ZIinst);
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
#line 2442 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 2451 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_string_arg_in_lhs */
	    {
#line 979 "syntax.act"

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
#line 2459 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_string_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 436 "syntax.act"

    (ZIl)=add_args_list();
#line 2467 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 428 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 2476 "tmp.syntax.c"
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
#line 2500 "tmp.syntax.c"
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
	    ZR185 (&ZIr);
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
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.litteral, q->u.litteral)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.litteral);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2554 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 31:
	{
	    /* BEGINNING OF INLINE: 188 */
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
#line 2576 "tmp.syntax.c"
		    }
		    /* END OF ACTION: make-donothing-inst */
		}
	    }
	    /* END OF INLINE: 188 */
	}
	break;
      case 41:
	{
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 436 "syntax.act"

    (ZIl)=add_args_list();
#line 2595 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 210 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2606 "tmp.syntax.c"
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
	    ZR185 (&ZIr);
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
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.litteral, q->u.litteral)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.litteral);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 2660 "tmp.syntax.c"
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
#line 971 "syntax.act"

	error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 2711 "tmp.syntax.c"
	}
	/* END OF ACTION: syntax-error */
    }
}

static void
ZR210(zoneP *ZIz, SID_CHARS *ZOe)
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
#line 941 "syntax.act"

        (ZIe) = NULL ;
	error(ERROR_SERIOUS, "Syntax error: expected characters");
#line 2741 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_chars */
    }
  ZL0:;
    *ZOe = ZIe;
}

static void
ZR212(zoneP *ZIz, instructions_listP *ZOleaving_Hinstl)
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
#line 635 "syntax.act"

    (ZIleaving_Hinstl)=add_instructions_list();
#line 2772 "tmp.syntax.c"
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
#line 2812 "tmp.syntax.c"
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
	/* BEGINNING OF INLINE: 195 */
	{
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 811 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 2840 "tmp.syntax.c"
		}
		/* END OF ACTION: is-global-zone */
		if (!ZI0)
		    goto ZL3;
		/* BEGINNING OF ACTION: make-keyword */
		{
#line 676 "syntax.act"

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
#line 2864 "tmp.syntax.c"
		}
		/* END OF ACTION: make-keyword */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonekeyword */
		{
#line 903 "syntax.act"

    error( ERROR_SERIOUS, "Keywords not yet implemented in a non global zone ") ;

#line 2877 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonekeyword */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 195 */
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
#line 2921 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 130 */
	{
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 811 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 2937 "tmp.syntax.c"
		}
		/* END OF ACTION: is-global-zone */
		if (!ZI0)
		    goto ZL3;
		/* BEGINNING OF ACTION: make-copyright */
		{
#line 815 "syntax.act"

	/* TODO can copyright_file be passed in somehow, other than with options as a global? */
	if(options.copyright_file==NULL) {
		options.copyright_file=fopen((ZIs),"r");
		if(!options.copyright_file) {
			error(ERROR_SERIOUS, "Syntax error: unable to open copright file %s", (ZIs)) ;
		}
	}
	else 
		error(ERROR_SERIOUS, "Syntax error: you can only specify one copyright file") ;
#line 2955 "tmp.syntax.c"
		}
		/* END OF ACTION: make-copyright */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonecopyright */
		{
#line 908 "syntax.act"

    error( ERROR_SERIOUS, "Syntax error: A copyright file may only be specified in the global zone") ;
#line 2967 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonecopyright */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 130 */
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
#line 3012 "tmp.syntax.c"
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
#line 733 "syntax.act"

    (ZIj) = crt_cond ;
#line 3032 "tmp.syntax.c"
	}
	/* END OF ACTION: get-condition */
	/* BEGINNING OF ACTION: add-condition */
	{
#line 701 "syntax.act"

    if ( crt_cond ) {
	crt_cond = xstrcat ( crt_cond, xstrcat ( " && ", (ZIi) ) ) ;
    } else {
	crt_cond = (ZIi) ;
    }
#line 3044 "tmp.syntax.c"
	}
	/* END OF ACTION: add-condition */
	ZRcommand (ZIz);
	/* BEGINNING OF INLINE: 200 */
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
#line 716 "syntax.act"

    if ( crt_cond ) {
	if ( strchr ( crt_cond, '&' ) ) {
	    crt_cond = xstrcat ( xstrcat ( "!( ", crt_cond ), " )" ) ;
	} else {
	    crt_cond = xstrcat ( "!", crt_cond ) ;
	}
    }
#line 3073 "tmp.syntax.c"
		}
		/* END OF ACTION: compl-condition */
		ZRcommand (ZIz);
		if ((CURRENT_TERMINAL) == 44) {
		    RESTORE_LEXER;
		    goto ZL3;
		}
		/* BEGINNING OF ACTION: set-condition */
		{
#line 744 "syntax.act"

    crt_cond = (ZIj) ;
#line 3086 "tmp.syntax.c"
		}
		/* END OF ACTION: set-condition */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: set-condition */
		{
#line 744 "syntax.act"

    crt_cond = (ZIj) ;
#line 3098 "tmp.syntax.c"
		}
		/* END OF ACTION: set-condition */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 200 */
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZR226(zoneP *ZIz)
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
#line 3126 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    ZR135 ();
	    ZRchars (*ZIz, &ZIs);
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-group */
	    {
#line 354 "syntax.act"

    make_group ( (*ZIz), (ZIi), (ZIs) ) ;
#line 3141 "tmp.syntax.c"
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
	    ZR135 ();
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
#line 3170 "tmp.syntax.c"
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
ZR227(zoneP *ZIz)
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
#line 663 "syntax.act"

    (*ZIz)->default_instructions=(ZIinst_Hlist);
    (*ZIz)->default_cond=crt_cond;
#line 3218 "tmp.syntax.c"
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
#line 646 "syntax.act"

        add_char ( (*ZIz), (*ZIz)->zone_main_pass, (ZIs), crt_cond, (ZIinst_Hlist), NULL) ;
#line 3254 "tmp.syntax.c"
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
ZRcommand(zoneP ZIz)
{
    switch (CURRENT_TERMINAL) {
      case 7:
	{
	    ADVANCE_LEXER;
	    ZR226 (&ZIz);
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
	    ZR227 (&ZIz);
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
	ZR236 (&ZIa, &ZIl);
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
        (ZIinst)=add_instruction_function((*ZI230),(ZIa));
    } 
    else {
        (ZIinst)=add_instruction_return_terminal((*ZI230));
    }
#line 3450 "tmp.syntax.c"
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
#line 789 "syntax.act"

	(ZIa) = add_identifier_arg ((*ZI230));
#line 3467 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_identifier */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 436 "syntax.act"

    (ZIl)=add_args_list();
#line 3475 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 428 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 3484 "tmp.syntax.c"
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
#line 3502 "tmp.syntax.c"
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
	    ZR185 (&ZIr);
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
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.litteral, q->u.litteral)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.litteral);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 3556 "tmp.syntax.c"
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
ZRtype_Htuple_C_Ctype_Htuple1(zoneP ZIz, TypeTupleT *ZIa)
{
    if ((CURRENT_TERMINAL) == 44) {
	return;
    }
  ZL2_type_Htuple_C_Ctype_Htuple1:;
    {
	ZRtype_Htuple_C_Ctype_Hname (ZIz, ZIa);
	/* BEGINNING OF INLINE: 239 */
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
	/* END OF INLINE: 239 */
    }
    return;
  ZL1:;
    SAVE_LEXER (44);
    return;
}

static void
ZR233(zoneP *ZIz, SID_STRING *ZI232, instructionP *ZOinst)
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
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 3625 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_terminal_in_lhs */
	    {
#line 1011 "syntax.act"

	error(ERROR_SERIOUS, "Terminal argument in left handside");
#line 3633 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_terminal_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 436 "syntax.act"

    (ZIl)=add_args_list();
#line 3641 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 428 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 3650 "tmp.syntax.c"
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
#line 3668 "tmp.syntax.c"
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
	    ZR185 (&ZIr);
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
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.litteral, q->u.litteral)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.litteral);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(ZIl),(ZIr));
		 /* END Inefficient code*/
		} else {
			(ZIinst)=NULL;
			error(ERROR_SERIOUS, "Name %s is not an action", (ZIi));
		}
	} else {
		(ZIinst)=NULL;
		error(ERROR_SERIOUS, "Unknown action %s", (ZIi));
	}
	xfree((ZIi));
#line 3722 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      default:
	{
	    args_listP ZIa;

	    /* BEGINNING OF ACTION: null-args-list */
	    {
#line 443 "syntax.act"

    (ZIa) = NULL ;
#line 3736 "tmp.syntax.c"
	    }
	    /* END OF ACTION: null-args-list */
	    /* BEGINNING OF ACTION: make-inst */
	    {
#line 374 "syntax.act"

    if((ZIa)) {
        (ZIinst)=add_instruction_function((*ZI232),(ZIa));
    } 
    else {
        (ZIinst)=add_instruction_return_terminal((*ZI232));
    }
#line 3749 "tmp.syntax.c"
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
ZR234(argP *ZIa, args_listP *ZOr)
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
#line 428 "syntax.act"

    (*ZIa)->next=(ZIr)->head;
    (ZIr)->head=(*ZIa);
#line 3785 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 436 "syntax.act"

    (ZIr)=add_args_list();
#line 3797 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 428 "syntax.act"

    (*ZIa)->next=(ZIr)->head;
    (ZIr)->head=(*ZIa);
#line 3806 "tmp.syntax.c"
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
ZR235(argP *ZIa, args_listP *ZOl)
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
#line 428 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 3842 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 436 "syntax.act"

    (ZIl)=add_args_list();
#line 3854 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 428 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 3863 "tmp.syntax.c"
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
ZR236(argP *ZIa, args_listP *ZOl)
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
#line 428 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 3899 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 436 "syntax.act"

    (ZIl)=add_args_list();
#line 3911 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 428 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 3920 "tmp.syntax.c"
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
ZR237(zoneP *ZIz, instructionP *ZIinst, instructions_listP *ZOinstl)
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
#line 450 "syntax.act"

	if((*ZIinst)!=NULL) { /* if (*ZIinst) == NULL, an error has already been issued.*/
		LocalNamesT** locals = instructionslist_localnamesref((ZIinstl));
/*		if(((ZIinstl)->head !=NULL) && ((*ZIinst)->type==return_terminal || (*ZIinst)->type==do_nothing)) {
			error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an instruction-list"); Does not work anymore since we append and do not prepend anymore. No pb as this will be unecessary due to the upcoming removal of direct function calls.
		}*/
		if((*ZIinst)->type == action_call) {
			EntryT* entryaction = (*ZIinst)->u.act.called_act;
			ActionT* action = entry_get_action(entryaction);
			args_list* rhs = (*ZIinst)->u.act.rhs;
			args_list* lhs = (*ZIinst)->u.act.lhs;

			arg* p;
			TypeTupleEntryT* q;

			/* CHECKING RHS COMPATIBILITY */ 
			for ( p = rhs->head, q = action->inputs.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
			      	EntryT* entrytype = NULL;
				NStringT str;
			      	switch (p->type) {
				case arg_identifier: 
				     	nstring_copy_cstring(&str, p->u.litteral);
					entrytype=localnames_get_type(*locals, &str);
					nstring_destroy(&str);
					if(!entrytype) {
						EntryT* tableentry = table_get_entry((*ZIz)->top_level->table, &str);
						if(!tableentry) {
							error(ERROR_SERIOUS, "local name %s has not been defined yet", p->u.litteral);
							entrytype = NULL;
						} else if (entry_is_localname(tableentry)) {
							error(ERROR_SERIOUS, "local name %s has been defined but not in this scope", p->u.litteral);
							entrytype = NULL;
						} else if (entry_is_action(tableentry)) {
							error(ERROR_SERIOUS, "%s is not a local name but an action which is not allowed", p->u.litteral);
							entrytype = NULL;
						} else if (entry_is_type(tableentry)) {
							error(ERROR_SERIOUS, "%s is not a local name but a type which is not allowed", p->u.litteral);
							entrytype = NULL;
						} else {
							; /* TODO assert(0) this should be unreachable*/
						}
					}
					break;
				case arg_charP:
					/* TODO assert(lexer_string_type(top_level)) */
					entrytype = lexer_string_type((*ZIz)->top_level);
		 			break;
				case arg_char_nb:
					/* TODO assert(lexer_char_type(top_level)) */
					entrytype = lexer_char_type((*ZIz)->top_level);
			 		break;
				case arg_terminal:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_terminal_type((*ZIz)->top_level);
					break;
				case arg_nb_of_chars:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_int_type((*ZIz)->top_level);
		 			break;
				case arg_none:
					break; //Error already detected, do nothing and leave p->lexitype = NULL
				case arg_litteral:
				case arg_chars_list:
				case arg_ignore:
				case arg_return_terminal:
					/* TODO assert(0): we should never reach this place */
				break;
			default:
				break;
				/* TODO assert(0): we should never reach this place either, doubly so*/
			}
			if(entrytype) {
				if( q->type!=entrytype || p->is_reference!=q->is_reference) {
						char* s1 = nstring_to_cstring(entry_key(entryaction));
						char* s2 = nstring_to_cstring(entry_key(entrytype));
						char* s3 = p->is_reference ? "&" : "";
						char* s4 = nstring_to_cstring(entry_key(q->type));
						char* s5 = q->is_reference ? "&" : "";
						error(ERROR_SERIOUS, "In call to action %s, argument \'%s\' has type \'%s%s\' when it should have type %s", s1, p->u.litteral, s2, s3, s4, s5);
						DEALLOCATE(s1);
						DEALLOCATE(s2);
						DEALLOCATE(s4);
					}
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

			for ( p = lhs->head, q = action->outputs.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
			      	EntryT* entrytype;
				switch (p->type) {
				case arg_identifier: 
					{
						NStringT str;
						EntryT* entry; 
						nstring_copy_cstring(&str, p->u.litteral);
						entrytype = localnames_get_type(*locals, &str);
						if(!entrytype) {
							EntryT* entry = table_get_entry((*ZIz)->top_level->table, &str);
							localnames_add_nstring(locals, &str, q->type);
							if(entry) {
								nstring_destroy(&str);
								if (entry_is_action(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.litteral);
								} else if (entry_is_type(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.litteral);									
								}
							} else {
								table_add_local_name((*ZIz)->top_level->table, &str);
							}
							if(p->is_reference) {
								char* s = nstring_to_cstring(entry_key(entryaction));
								error(ERROR_SERIOUS, "In action call %s, you can only use references %s for preexisting variables", s, p->u.litteral);
								DEALLOCATE(s);
							} 
						} else {
							nstring_destroy(&str);
							if(!p->is_reference) {
								char* s = nstring_to_cstring(entry_key(entryaction));
								error(ERROR_SERIOUS, "In action call %s, name %s already declared. Use references to change the value of an already existing variable", s, p->u.litteral);
								entrytype=q->type; /* To avoid outputting that error more than once*/
								DEALLOCATE(s);
							}
						}
					}
					break;
				case arg_return_terminal:
					entrytype = lexer_terminal_type((*ZIz)->top_level);
					q->is_reference = false;
					/* TODO assert(q->is_reference == false) */
					break;
				case arg_ignore:
					/*always acceptable */
					entrytype=q->type;
					p->is_reference=q->is_reference;
					break;
				case arg_none:
					break;
					/* TODO asserting errored is already set */
					/* Error has already been detected */
				case arg_charP:
				case arg_char_nb:
				case arg_chars_list:
				case arg_terminal:
				case arg_nb_of_chars:
					break; /* UNREACHABLE */
				default:
					break; /* UNREACHABLE */
				}
				if(p->is_reference != q->is_reference) {
					if(p->is_reference)
						error(ERROR_SERIOUS, "In call to action %, %s should not be a reference", p->u.litteral);
					else
						error(ERROR_SERIOUS, "In call to action %, %s should not be a reference", p->u.litteral);
				}
			}
			if(p!=NULL) {
				char* s = nstring_to_cstring(entry_key(entryaction));
				error(ERROR_SERIOUS, "In call to action %s, too many results", s);
				DEALLOCATE(s);
			}
			if(q!=NULL) {
				char* s = nstring_to_cstring(entry_key(entryaction));
				error(ERROR_SERIOUS, "In call to action %s, not enough results", s);
				DEALLOCATE(s);
			}
		}
		/* TODO only append if no error */
		(*ZIinst)->next=(ZIinstl)->head;
		(ZIinstl)->head=(*ZIinst);
	}
#line 4132 "tmp.syntax.c"
	    }
	    /* END OF ACTION: add-inst-to-list */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-inst-list */
	    {
#line 635 "syntax.act"

    (ZIinstl)=add_instructions_list();
#line 4144 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-inst-list */
	    /* BEGINNING OF ACTION: add-inst-to-list */
	    {
#line 450 "syntax.act"

	if((*ZIinst)!=NULL) { /* if (*ZIinst) == NULL, an error has already been issued.*/
		LocalNamesT** locals = instructionslist_localnamesref((ZIinstl));
/*		if(((ZIinstl)->head !=NULL) && ((*ZIinst)->type==return_terminal || (*ZIinst)->type==do_nothing)) {
			error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an instruction-list"); Does not work anymore since we append and do not prepend anymore. No pb as this will be unecessary due to the upcoming removal of direct function calls.
		}*/
		if((*ZIinst)->type == action_call) {
			EntryT* entryaction = (*ZIinst)->u.act.called_act;
			ActionT* action = entry_get_action(entryaction);
			args_list* rhs = (*ZIinst)->u.act.rhs;
			args_list* lhs = (*ZIinst)->u.act.lhs;

			arg* p;
			TypeTupleEntryT* q;

			/* CHECKING RHS COMPATIBILITY */ 
			for ( p = rhs->head, q = action->inputs.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
			      	EntryT* entrytype = NULL;
				NStringT str;
			      	switch (p->type) {
				case arg_identifier: 
				     	nstring_copy_cstring(&str, p->u.litteral);
					entrytype=localnames_get_type(*locals, &str);
					nstring_destroy(&str);
					if(!entrytype) {
						EntryT* tableentry = table_get_entry((*ZIz)->top_level->table, &str);
						if(!tableentry) {
							error(ERROR_SERIOUS, "local name %s has not been defined yet", p->u.litteral);
							entrytype = NULL;
						} else if (entry_is_localname(tableentry)) {
							error(ERROR_SERIOUS, "local name %s has been defined but not in this scope", p->u.litteral);
							entrytype = NULL;
						} else if (entry_is_action(tableentry)) {
							error(ERROR_SERIOUS, "%s is not a local name but an action which is not allowed", p->u.litteral);
							entrytype = NULL;
						} else if (entry_is_type(tableentry)) {
							error(ERROR_SERIOUS, "%s is not a local name but a type which is not allowed", p->u.litteral);
							entrytype = NULL;
						} else {
							; /* TODO assert(0) this should be unreachable*/
						}
					}
					break;
				case arg_charP:
					/* TODO assert(lexer_string_type(top_level)) */
					entrytype = lexer_string_type((*ZIz)->top_level);
		 			break;
				case arg_char_nb:
					/* TODO assert(lexer_char_type(top_level)) */
					entrytype = lexer_char_type((*ZIz)->top_level);
			 		break;
				case arg_terminal:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_terminal_type((*ZIz)->top_level);
					break;
				case arg_nb_of_chars:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_int_type((*ZIz)->top_level);
		 			break;
				case arg_none:
					break; //Error already detected, do nothing and leave p->lexitype = NULL
				case arg_litteral:
				case arg_chars_list:
				case arg_ignore:
				case arg_return_terminal:
					/* TODO assert(0): we should never reach this place */
				break;
			default:
				break;
				/* TODO assert(0): we should never reach this place either, doubly so*/
			}
			if(entrytype) {
				if( q->type!=entrytype || p->is_reference!=q->is_reference) {
						char* s1 = nstring_to_cstring(entry_key(entryaction));
						char* s2 = nstring_to_cstring(entry_key(entrytype));
						char* s3 = p->is_reference ? "&" : "";
						char* s4 = nstring_to_cstring(entry_key(q->type));
						char* s5 = q->is_reference ? "&" : "";
						error(ERROR_SERIOUS, "In call to action %s, argument \'%s\' has type \'%s%s\' when it should have type %s", s1, p->u.litteral, s2, s3, s4, s5);
						DEALLOCATE(s1);
						DEALLOCATE(s2);
						DEALLOCATE(s4);
					}
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

			for ( p = lhs->head, q = action->outputs.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
			      	EntryT* entrytype;
				switch (p->type) {
				case arg_identifier: 
					{
						NStringT str;
						EntryT* entry; 
						nstring_copy_cstring(&str, p->u.litteral);
						entrytype = localnames_get_type(*locals, &str);
						if(!entrytype) {
							EntryT* entry = table_get_entry((*ZIz)->top_level->table, &str);
							localnames_add_nstring(locals, &str, q->type);
							if(entry) {
								nstring_destroy(&str);
								if (entry_is_action(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.litteral);
								} else if (entry_is_type(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.litteral);									
								}
							} else {
								table_add_local_name((*ZIz)->top_level->table, &str);
							}
							if(p->is_reference) {
								char* s = nstring_to_cstring(entry_key(entryaction));
								error(ERROR_SERIOUS, "In action call %s, you can only use references %s for preexisting variables", s, p->u.litteral);
								DEALLOCATE(s);
							} 
						} else {
							nstring_destroy(&str);
							if(!p->is_reference) {
								char* s = nstring_to_cstring(entry_key(entryaction));
								error(ERROR_SERIOUS, "In action call %s, name %s already declared. Use references to change the value of an already existing variable", s, p->u.litteral);
								entrytype=q->type; /* To avoid outputting that error more than once*/
								DEALLOCATE(s);
							}
						}
					}
					break;
				case arg_return_terminal:
					entrytype = lexer_terminal_type((*ZIz)->top_level);
					q->is_reference = false;
					/* TODO assert(q->is_reference == false) */
					break;
				case arg_ignore:
					/*always acceptable */
					entrytype=q->type;
					p->is_reference=q->is_reference;
					break;
				case arg_none:
					break;
					/* TODO asserting errored is already set */
					/* Error has already been detected */
				case arg_charP:
				case arg_char_nb:
				case arg_chars_list:
				case arg_terminal:
				case arg_nb_of_chars:
					break; /* UNREACHABLE */
				default:
					break; /* UNREACHABLE */
				}
				if(p->is_reference != q->is_reference) {
					if(p->is_reference)
						error(ERROR_SERIOUS, "In call to action %, %s should not be a reference", p->u.litteral);
					else
						error(ERROR_SERIOUS, "In call to action %, %s should not be a reference", p->u.litteral);
				}
			}
			if(p!=NULL) {
				char* s = nstring_to_cstring(entry_key(entryaction));
				error(ERROR_SERIOUS, "In call to action %s, too many results", s);
				DEALLOCATE(s);
			}
			if(q!=NULL) {
				char* s = nstring_to_cstring(entry_key(entryaction));
				error(ERROR_SERIOUS, "In call to action %s, not enough results", s);
				DEALLOCATE(s);
			}
		}
		/* TODO only append if no error */
		(*ZIinst)->next=(ZIinstl)->head;
		(ZIinstl)->head=(*ZIinst);
	}
#line 4329 "tmp.syntax.c"
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
ZR238(zoneP *ZIz, TypeTupleT *ZIa)
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
	/* BEGINNING OF INLINE: 183 */
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
#line 436 "syntax.act"

    (ZIr)=add_args_list();
#line 4405 "tmp.syntax.c"
		    }
		    /* END OF ACTION: empty-args-list */
		}
		break;
	    }
	}
	/* END OF INLINE: 183 */
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
	/* BEGINNING OF INLINE: 128 */
	{
	    if ((CURRENT_TERMINAL) == 44) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-non-empty */
		{
#line 650 "syntax.act"

    (ZI0)=((ZIc)[0]!=(ZIz)->top_level->last_letter_code);
#line 4451 "tmp.syntax.c"
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
#line 654 "syntax.act"

        error(ERROR_SERIOUS, "Empty character string is not allowed here, try using DEFAULT instead");	
#line 4465 "tmp.syntax.c"
		}
		/* END OF ACTION: E_empty_character_string */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 128 */
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
#line 4494 "tmp.syntax.c"
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
#line 4507 "tmp.syntax.c"
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
#line 4520 "tmp.syntax.c"
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
#line 4533 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-ignore */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: E_ignore_in_rhs */
	    {
#line 1007 "syntax.act"

	error(ERROR_SERIOUS, "Ignore argument in right handside");
#line 4542 "tmp.syntax.c"
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
#line 4554 "tmp.syntax.c"
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
#line 4569 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-return-terminal */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 4578 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_return_terminal_in_rhs */
	    {
#line 983 "syntax.act"

	error(ERROR_SERIOUS, "Return terminal argument in right handside");
#line 4586 "tmp.syntax.c"
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
#line 4600 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 4609 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_localname_in_function_rhs */
	    {
#line 996 "syntax.act"

	error(ERROR_SERIOUS, "Local names in function rhs not implemented yet ");
#line 4617 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_localname_in_function_rhs */
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
#line 4634 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_reference */
	    {
#line 793 "syntax.act"

	(ZIa) = add_reference_arg ((ZIi));
#line 4647 "tmp.syntax.c"
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
#line 4682 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: sid-identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 4691 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_terminal_in_function_rhs */
	    {
#line 992 "syntax.act"

	error(ERROR_SERIOUS, "Terminals in function rhs not implemented yet ");
#line 4699 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_terminal_in_function_rhs */
	}
	break;
      case 2:
	{
	    SID_STRING ZIb;

	    /* BEGINNING OF EXTRACT: string */
	    {
#line 255 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 4713 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_string */
	    {
#line 785 "syntax.act"

	(ZIa) = add_litteral_arg ((ZIb));
#line 4722 "tmp.syntax.c"
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
#line 4755 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-list */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 4764 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 975 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4772 "tmp.syntax.c"
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
#line 4786 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-nb */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 4795 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 975 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4803 "tmp.syntax.c"
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
#line 4817 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 4826 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 975 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4834 "tmp.syntax.c"
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
#line 4846 "tmp.syntax.c"
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
#line 4861 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-nb-of-chars */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 4870 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 975 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 4878 "tmp.syntax.c"
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
#line 4890 "tmp.syntax.c"
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
#line 4905 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_identifier */
	    {
#line 789 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 4914 "tmp.syntax.c"
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
#line 4931 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_reference */
	    {
#line 793 "syntax.act"

	(ZIa) = add_reference_arg ((ZIi));
#line 4944 "tmp.syntax.c"
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
#line 4979 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: sid-identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 4988 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_terminal_in_lhs */
	    {
#line 1011 "syntax.act"

	error(ERROR_SERIOUS, "Terminal argument in left handside");
#line 4996 "tmp.syntax.c"
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
#line 5010 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 5019 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_string_arg_in_lhs */
	    {
#line 979 "syntax.act"

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
#line 5027 "tmp.syntax.c"
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
#line 5060 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-list */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 5069 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_list_in_action_rhs */
	    {
#line 1001 "syntax.act"

	error(ERROR_SERIOUS, "Args of style ## are not implemented in actions right hand side. Whether they will be implemented in the future remains undecided at the moment.");
/* TODO take a decision.*/
#line 5078 "tmp.syntax.c"
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
#line 5090 "tmp.syntax.c"
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
#line 5103 "tmp.syntax.c"
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
#line 5118 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-ignore */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 5127 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_ignore_in_rhs */
	    {
#line 1007 "syntax.act"

	error(ERROR_SERIOUS, "Ignore argument in right handside");
#line 5135 "tmp.syntax.c"
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
#line 5147 "tmp.syntax.c"
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
#line 5162 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-return-terminal */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 5171 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_return_terminal_in_rhs */
	    {
#line 983 "syntax.act"

	error(ERROR_SERIOUS, "Return terminal argument in right handside");
#line 5179 "tmp.syntax.c"
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
#line 5193 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_identifier */
	    {
#line 789 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 5202 "tmp.syntax.c"
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
#line 5219 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_reference */
	    {
#line 793 "syntax.act"

	(ZIa) = add_reference_arg ((ZIi));
#line 5232 "tmp.syntax.c"
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
#line 5267 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: sid-identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_terminal */
	    {
#line 797 "syntax.act"

	(ZIa) = add_terminal_arg ((ZIb));
#line 5276 "tmp.syntax.c"
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
#line 5290 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 802 "syntax.act"

	(ZIa) = add_none_arg();
#line 5299 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_string_in_action_rhs */
	    {
#line 987 "syntax.act"

	error(ERROR_SERIOUS, "String argument in right handside of action call: purposefuly not implemented to avoid confusions. Will be implemented with an alternate meaning once direct function calls are removed from lexi");
#line 5307 "tmp.syntax.c"
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

#line 1015 "syntax.act"

#line 5329 "tmp.syntax.c"

/* END OF FILE */
