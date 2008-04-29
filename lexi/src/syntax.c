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


#line 113 "tmp.syntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRexpected__semicolon(void);
static void ZRtuple_Hargs(args_listP *);
static void ZRzone_Hdefn(zoneP);
static void ZRstring_Hplus(SID_STRING *);
static void ZRtype_Hdefn(zoneP);
static void ZRchars(zoneP, SID_CHARS *);
static void ZR151(void);
static void ZRaction_Hcall_C_Clhs_Htuple1(void);
static void ZRtype_Htuple(zoneP, TypeTupleT *);
static void ZRaction_Hcall_C_Crhs_Htuple1(void);
static void ZRinstructions_Hlist(instructions_listP *);
static void ZRtype_Htuple_C_Ctype_Hname(zoneP, TypeTupleT *);
static void ZRargs(args_listP *);
static void ZR176(zoneP *, SID_CHARS *);
static void ZR178(instructions_listP *);
static void ZRtrigraph_Hdefn(zoneP);
static void ZR191(zoneP *);
static void ZR192(zoneP *);
static void ZR194(SID_STRING *, instructionP *);
extern void read_lex(zoneP);
static void ZR196(argP *, args_listP *);
static void ZR198(instructionP *, instructions_listP *);
static void ZR200(zoneP *, TypeTupleT *);
static void ZRaction_Hdecl(zoneP);
static void ZRinstruction(instructionP *);
static void ZRcommand_Hlist(zoneP);
static void ZRkeyword_Hdefn(zoneP);
static void ZRcopyright_Hstmt(zoneP);
static void ZRif_Hcommand(zoneP);
static void ZRcommand(zoneP);
static void ZRnon_Hempty_Htuple_Hargs(args_listP *);
static void ZRaction_Hcall_C_Crhs_Htuple(void);
static void ZRnon_Hempty_Hchars(zoneP, SID_CHARS *);
static void ZRsingle_Harg(argP *);
static void ZR114(void);
static void ZR122(void);

/* BEGINNING OF STATIC VARIABLES */

static int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRexpected__semicolon(void)
{
    if ((CURRENT_TERMINAL) == 41) {
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
#line 701 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected semicolon \';\'");
#line 183 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_semicolon */
    }
}

static void
ZRtuple_Hargs(args_listP *ZOl)
{
    args_listP ZIl;

    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 402 "syntax.act"

    (ZIl)=add_args_list();
#line 203 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	}
	break;
      case 2: case 32: case 33: case 34: case 35:
	{
	    ZRnon_Hempty_Htuple_Hargs (&ZIl);
	    if ((CURRENT_TERMINAL) == 41) {
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
#line 402 "syntax.act"

    (ZIl)=add_args_list();
#line 226 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: arg-char-list-tmp */
	    {
#line 382 "syntax.act"

      (ZItmp)=add_arg(arg_chars_list,0);
#line 234 "tmp.syntax.c"
	    }
	    /* END OF ACTION: arg-char-list-tmp */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 389 "syntax.act"

    if((ZItmp)->next!= NULL) {
       if((ZItmp)->type==return_token || (ZItmp)->type==do_nothing) {
         error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an arg-list"); 
       }
    }
    (ZItmp)->next=(ZIl)->head;
    (ZIl)->head=(ZItmp);
#line 248 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      case 41:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (41);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZRzone_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 41) {
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
	/* BEGINNING OF INLINE: 168 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 0:
		    /* BEGINNING OF EXTRACT: identifier */
		    {
#line 205 "syntax.act"

    ZIzid = xstrcpy ( token_buff ) ;
#line 296 "tmp.syntax.c"
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
#line 683 "syntax.act"

	(ZIzid)="";
	error(ERROR_SERIOUS, "Syntax error: expected identifier");
#line 314 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_identifier */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 168 */
	/* BEGINNING OF INLINE: 170 */
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
#line 697 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected colon \':\'");
#line 340 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_colon */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 170 */
	ZR176 (&ZIz, &ZIb);
	ZR178 (&ZIentry_Hinstl);
	/* BEGINNING OF INLINE: 174 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 26:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: true */
		    {
#line 546 "syntax.act"
 (ZIlendclosed) = 1 ; 
#line 359 "tmp.syntax.c"
		    }
		    /* END OF ACTION: true */
		}
		break;
	      case 27:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: true */
		    {
#line 546 "syntax.act"
 (ZIlendclosed) = 1 ; 
#line 371 "tmp.syntax.c"
		    }
		    /* END OF ACTION: true */
		}
		break;
	      case 28:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: false */
		    {
#line 547 "syntax.act"
 (ZIlendclosed) = 0 ; 
#line 383 "tmp.syntax.c"
		    }
		    /* END OF ACTION: false */
		}
		break;
	      case 41:
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
#line 688 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected range");
#line 402 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_range */
		/* BEGINNING OF ACTION: false */
		{
#line 547 "syntax.act"
 (ZIlendclosed) = 0 ; 
#line 409 "tmp.syntax.c"
		}
		/* END OF ACTION: false */
	    }
	  ZL6:;
	}
	/* END OF INLINE: 174 */
	ZR176 (&ZIz, &ZIe);
	ZR178 (&ZIleaving_Hinstl);
	if ((CURRENT_TERMINAL) == 41) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-zone */
	{
#line 572 "syntax.act"

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
#line 436 "tmp.syntax.c"
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
	  case 41:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
    return;
}

static void
ZRstring_Hplus(SID_STRING *ZOs)
{
    SID_STRING ZIs;

    if ((CURRENT_TERMINAL) == 41) {
	return;
    }
    {
	SID_STRING ZIa;

	/* BEGINNING OF INLINE: 98 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 5:
		{
		    /* BEGINNING OF EXTRACT: digit */
		    {
#line 263 "syntax.act"
 ZIa = "0123456789" ; 
#line 484 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: digit */
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    /* BEGINNING OF EXTRACT: lower */
		    {
#line 262 "syntax.act"
 ZIa = "abcdefghijklmnopqrstuvwxyz" ; 
#line 496 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: lower */
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    /* BEGINNING OF EXTRACT: string */
		    {
#line 250 "syntax.act"

    ZIa = xstrcpy ( token_buff ) ;
#line 509 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: string */
		    ADVANCE_LEXER;
		}
		break;
	      case 3:
		{
		    /* BEGINNING OF EXTRACT: upper */
		    {
#line 261 "syntax.act"
 ZIa = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ; 
#line 521 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: upper */
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	/* END OF INLINE: 98 */
	/* BEGINNING OF INLINE: 100 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 23:
		{
		    SID_STRING ZIb;

		    ADVANCE_LEXER;
		    ZRstring_Hplus (&ZIb);
		    if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    /* BEGINNING OF ACTION: string-concat */
		    {
#line 294 "syntax.act"

    (ZIs) = xstrcat ( (ZIa), (ZIb) ) ;
#line 550 "tmp.syntax.c"
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
	/* END OF INLINE: 100 */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (41);
    return;
  ZL0:;
    *ZOs = ZIs;
}

static void
ZRtype_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 41) {
	return;
    }
    {
	SID_STRING ZIs;

	switch (CURRENT_TERMINAL) {
	  case 40:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 0:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 205 "syntax.act"

    ZIs = xstrcpy ( token_buff ) ;
#line 595 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 125 */
	{
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 595 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 611 "tmp.syntax.c"
		}
		/* END OF ACTION: is-global-zone */
		if (!ZI0)
		    goto ZL3;
		/* BEGINNING OF ACTION: make-type */
		{
#line 611 "syntax.act"

	NStringT str;
	nstring_copy_cstring(&str,(ZIs));
	if(table_get_entry((ZIz)->top_level->table, &str)) {
		nstring_destroy(&str);
		error(ERROR_SERIOUS, "can't create type %s because of name clash",(ZIs));
	} else {
		table_add_type((ZIz)->top_level->table, &str);
	}
#line 628 "tmp.syntax.c"
		}
		/* END OF ACTION: make-type */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonetype */
		{
#line 672 "syntax.act"

    error( ERROR_SERIOUS, "Syntax error: type %s should not be declared inside a zone",(ZIs)) ;
#line 640 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonetype */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 125 */
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
    return;
}

static void
ZRchars(zoneP ZIz, SID_CHARS *ZOc)
{
    SID_CHARS ZIc;

    if ((CURRENT_TERMINAL) == 41) {
	return;
    }
    {
	SID_STRING ZIs;

	ZRstring_Hplus (&ZIs);
	if ((CURRENT_TERMINAL) == 41) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-chars */
	{
#line 317 "syntax.act"

    (ZIc) = make_string ( (ZIs), (ZIz) ) ;
#line 675 "tmp.syntax.c"
	}
	/* END OF ACTION: make-chars */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (41);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZR151(void)
{
    switch (CURRENT_TERMINAL) {
      case 16:
	{
	    ZRaction_Hcall_C_Crhs_Htuple ();
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 41:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
    return;
}

static void
ZRaction_Hcall_C_Clhs_Htuple1(void)
{
    if ((CURRENT_TERMINAL) == 41) {
	return;
    }
  ZL2_action_Hcall_C_Clhs_Htuple1:;
    {
	SID_STRING ZIid;

	switch (CURRENT_TERMINAL) {
	  case 0:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 205 "syntax.act"

    ZIid = xstrcpy ( token_buff ) ;
#line 728 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 197 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 29:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: action-call::lhs-tuple1 */
		    goto ZL2_action_Hcall_C_Clhs_Htuple1;
		    /* END OF INLINE: action-call::lhs-tuple1 */
		}
		/*UNREACHED*/
	      default:
		break;
	    }
	}
	/* END OF INLINE: 197 */
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
    return;
}

static void
ZRtype_Htuple(zoneP ZIz, TypeTupleT *ZOa)
{
    TypeTupleT ZIa;

    if ((CURRENT_TERMINAL) == 41) {
	return;
    }
    {
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 637 "syntax.act"

	typetuple_init(&(ZIa));
#line 773 "tmp.syntax.c"
	}
	/* END OF ACTION: init-tuple */
	ZR200 (&ZIz, &ZIa);
	if ((CURRENT_TERMINAL) == 41) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (41);
    return;
  ZL0:;
    /* BEGINNING OF RESULT ASSIGNMENT: TYPETUPLE */
    {
#line 190 "syntax.act"

	typetuple_assign(ZOa, (&ZIa));
#line 792 "tmp.syntax.c"
    }
    /* END OF RESULT ASSIGNMENT: TYPETUPLE */
}

static void
ZRaction_Hcall_C_Crhs_Htuple1(void)
{
    if ((CURRENT_TERMINAL) == 41) {
	return;
    }
  ZL2_action_Hcall_C_Crhs_Htuple1:;
    {
	SID_STRING ZIid;

	switch (CURRENT_TERMINAL) {
	  case 0:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 205 "syntax.act"

    ZIid = xstrcpy ( token_buff ) ;
#line 814 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 195 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 29:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF INLINE: action-call::rhs-tuple1 */
		    goto ZL2_action_Hcall_C_Crhs_Htuple1;
		    /* END OF INLINE: action-call::rhs-tuple1 */
		}
		/*UNREACHED*/
	      default:
		break;
	    }
	}
	/* END OF INLINE: 195 */
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
    return;
}

static void
ZRinstructions_Hlist(instructions_listP *ZOinstl)
{
    instructions_listP ZIinstl;

    if ((CURRENT_TERMINAL) == 41) {
	return;
    }
    {
	instructionP ZIinst;

	ZRinstruction (&ZIinst);
	ZR198 (&ZIinst, &ZIinstl);
	if ((CURRENT_TERMINAL) == 41) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (41);
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
#line 184 "syntax.act"

	typetuple_assign(&ZIa,ZOa);
#line 881 "tmp.syntax.c"
    }
    /* END OF PARAM ASSIGNMENT: TYPETUPLE */
    if ((CURRENT_TERMINAL) == 41) {
	return;
    }
    {
	SID_STRING ZIname;
	SID_STRING ZItype;

	switch (CURRENT_TERMINAL) {
	  case 0:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 205 "syntax.act"

    ZIname = xstrcpy ( token_buff ) ;
#line 898 "tmp.syntax.c"
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
#line 205 "syntax.act"

    ZItype = xstrcpy ( token_buff ) ;
#line 920 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF ACTION: append-tuple */
	{
#line 641 "syntax.act"

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
		typetuple_append((&ZIa),typetupleentry_create(&istr,entry));
#line 945 "tmp.syntax.c"
	}
	/* END OF ACTION: append-tuple */
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
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
	      case 41:
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
#line 409 "syntax.act"

    (ZIl) = NULL ;
#line 984 "tmp.syntax.c"
	    }
	    /* END OF ACTION: null-args-list */
	}
	break;
      case 41:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (41);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZR176(zoneP *ZIz, SID_CHARS *ZOe)
{
    SID_CHARS ZIe;

    if ((CURRENT_TERMINAL) == 41) {
	return;
    }
    {
	ZRnon_Hempty_Hchars (*ZIz, &ZIe);
	if ((CURRENT_TERMINAL) == 41) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E_expected_chars */
	{
#line 692 "syntax.act"

        (ZIe) = NULL ;
	error(ERROR_SERIOUS, "Syntax error: expected characters");
#line 1024 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_chars */
    }
  ZL0:;
    *ZOe = ZIe;
}

static void
ZR178(instructions_listP *ZOleaving_Hinstl)
{
    instructions_listP ZIleaving_Hinstl;

    switch (CURRENT_TERMINAL) {
      case 20:
	{
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (&ZIleaving_Hinstl);
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-inst-list */
	    {
#line 426 "syntax.act"

    (ZIleaving_Hinstl)=add_instructions_list();
#line 1055 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-inst-list */
	}
	break;
      case 41:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (41);
    return;
  ZL0:;
    *ZOleaving_Hinstl = ZIleaving_Hinstl;
}

static void
ZRtrigraph_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 41) {
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
	ZR122 ();
	ZRstring_Hplus (&ZIt);
	if ((CURRENT_TERMINAL) == 41) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-trigraph */
	{
#line 355 "syntax.act"

    add_char ( (ZIz), (ZIz)->zone_pre_pass, (ZIs), crt_cond, NULL, (ZIt)) ;
#line 1100 "tmp.syntax.c"
	}
	/* END OF ACTION: make-trigraph */
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
    return;
}

static void
ZR191(zoneP *ZIz)
{
    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    SID_STRING ZIi;
	    SID_CHARS ZIs;

	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 205 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 1124 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    ZR114 ();
	    ZRchars (*ZIz, &ZIs);
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-group */
	    {
#line 344 "syntax.act"

    make_group ( (*ZIz), (ZIi), (ZIs) ) ;
#line 1139 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-group */
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 11:
	{
	    SID_CHARS ZIs;

	    ADVANCE_LEXER;
	    ZR114 ();
	    ZRchars (*ZIz, &ZIs);
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-white */
	    {
#line 330 "syntax.act"

    if ( (*ZIz)->white_space) {
	error ( ERROR_SERIOUS, "White space group already defined" ) ;
    }
    (*ZIz)->white_space= make_group((*ZIz),"white",(ZIs)) ;
#line 1168 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-white */
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 41:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
    return;
}

static void
ZR192(zoneP *ZIz)
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
	    ZRinstructions_Hlist (&ZIinst_Hlist);
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-default */
	    {
#line 454 "syntax.act"

    (*ZIz)->default_actions=(ZIinst_Hlist);
    (*ZIz)->default_cond=crt_cond;
#line 1216 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-default */
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 41) {
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
	      case 41:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (&ZIinst_Hlist);
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-token */
	    {
#line 437 "syntax.act"

        add_char ( (*ZIz), (*ZIz)->zone_main_pass, (ZIs), crt_cond, (ZIinst_Hlist), NULL) ;
#line 1252 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-token */
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 41:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
    return;
}

static void
ZR194(SID_STRING *ZI193, instructionP *ZOinst)
{
    instructionP ZIinst;

    switch (CURRENT_TERMINAL) {
      case 22:
	{
	    SID_STRING ZIi;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 38:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 205 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 1298 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR151 ();
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 377 "syntax.act"

	(ZIinst)=add_instruction_action((ZIi));
#line 1323 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      default:
	{
	    args_listP ZIa;

	    ZRargs (&ZIa);
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-inst */
	    {
#line 364 "syntax.act"

    if((ZIa)) {
        (ZIinst)=add_instruction_function((*ZI193),(ZIa));
    } 
    else {
        (ZIinst)=add_instruction_return_token((*ZI193));
    }
#line 1347 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-inst */
	}
	break;
      case 41:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (41);
    return;
  ZL0:;
    *ZOinst = ZIinst;
}

void
read_lex(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 41) {
	return;
    }
    {
	ZRcommand_Hlist (ZIz);
	/* BEGINNING OF INLINE: 183 */
	{
	    if ((CURRENT_TERMINAL) == 41) {
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
#line 713 "syntax.act"

    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1394 "tmp.syntax.c"
		}
		/* END OF ACTION: syntax-error */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 183 */
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
    return;
}

static void
ZR196(argP *ZIa, args_listP *ZOl)
{
    args_listP ZIl;

    switch (CURRENT_TERMINAL) {
      case 29:
	{
	    ADVANCE_LEXER;
	    ZRnon_Hempty_Htuple_Hargs (&ZIl);
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 389 "syntax.act"

    if((*ZIa)->next!= NULL) {
       if((*ZIa)->type==return_token || (*ZIa)->type==do_nothing) {
         error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an arg-list"); 
       }
    }
    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 1433 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 402 "syntax.act"

    (ZIl)=add_args_list();
#line 1445 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 389 "syntax.act"

    if((*ZIa)->next!= NULL) {
       if((*ZIa)->type==return_token || (*ZIa)->type==do_nothing) {
         error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an arg-list"); 
       }
    }
    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 1459 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      case 41:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (41);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZR198(instructionP *ZIinst, instructions_listP *ZOinstl)
{
    instructions_listP ZIinstl;

    switch (CURRENT_TERMINAL) {
      case 29:
	{
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (&ZIinstl);
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: add-inst-to-list */
	    {
#line 416 "syntax.act"

	(*ZIinst)->next=(ZIinstl)->head;
	(ZIinstl)->head=(*ZIinst);
#line 1495 "tmp.syntax.c"
	    }
	    /* END OF ACTION: add-inst-to-list */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-inst-list */
	    {
#line 426 "syntax.act"

    (ZIinstl)=add_instructions_list();
#line 1507 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-inst-list */
	    /* BEGINNING OF ACTION: add-inst-to-list */
	    {
#line 416 "syntax.act"

	(*ZIinst)->next=(ZIinstl)->head;
	(ZIinstl)->head=(*ZIinst);
#line 1516 "tmp.syntax.c"
	    }
	    /* END OF ACTION: add-inst-to-list */
	}
	break;
      case 41:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (41);
    return;
  ZL0:;
    *ZOinstl = ZIinstl;
}

static void
ZR200(zoneP *ZIz, TypeTupleT *ZIa)
{
  ZL2_200:;
    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    /* BEGINNING OF INLINE: type-tuple::type-tuple1 */
	    {
		{
		    ZRtype_Htuple_C_Ctype_Hname (*ZIz, ZIa);
		    /* BEGINNING OF INLINE: 200 */
		    if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		    } else {
			goto ZL2_200;
		    }
		    /* END OF INLINE: 200 */
		}
		/*UNREACHED*/
	    }
	    /* END OF INLINE: type-tuple::type-tuple1 */
	}
	/*UNREACHED*/
      case 41:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
    return;
}

static void
ZRaction_Hdecl(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 41) {
	return;
    }
    {
	SID_STRING ZIi;
	TypeTupleT ZIit;
	TypeTupleT ZIot;

	switch (CURRENT_TERMINAL) {
	  case 37:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 38:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 0:
	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 205 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 1600 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 39:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 134 */
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
		      case 41:
			RESTORE_LEXER;
			goto ZL1;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    ZR122 ();
		    switch (CURRENT_TERMINAL) {
		      case 16:
			break;
		      case 41:
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
		      case 41:
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
#line 637 "syntax.act"

	typetuple_init(&(ZIit));
#line 1670 "tmp.syntax.c"
		    }
		    /* END OF ACTION: init-tuple */
		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 637 "syntax.act"

	typetuple_init(&(ZIot));
#line 1678 "tmp.syntax.c"
		    }
		    /* END OF ACTION: init-tuple */
		}
		break;
	    }
	}
	/* END OF INLINE: 134 */
	/* BEGINNING OF ACTION: make-action */
	{
#line 622 "syntax.act"

	NStringT str;
	nstring_copy_cstring(&str, (ZIi));
	if(table_get_entry((ZIz)->top_level->table, &str)) {
		error(ERROR_SERIOUS, "can't create action %s because of name clash",(ZIi));
		nstring_destroy(&str);
	} else {
		table_add_action((ZIz)->top_level->table, &str , (&ZIit), (&ZIot));
	}
#line 1698 "tmp.syntax.c"
	}
	/* END OF ACTION: make-action */
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
    return;
}

static void
ZRinstruction(instructionP *ZOinst)
{
    instructionP ZIinst;

    switch (CURRENT_TERMINAL) {
      case 38:
	{
	    SID_STRING ZIi;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 205 "syntax.act"

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
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR151 ();
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 377 "syntax.act"

	(ZIinst)=add_instruction_action((ZIi));
#line 1751 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 0:
	{
	    SID_STRING ZI193;

	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 205 "syntax.act"

    ZI193 = xstrcpy ( token_buff ) ;
#line 1765 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    ZR194 (&ZI193, &ZIinst);
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 16:
	{
	    SID_STRING ZIi;

	    ADVANCE_LEXER;
	    ZRaction_Hcall_C_Clhs_Htuple1 ();
	    switch (CURRENT_TERMINAL) {
	      case 17:
		break;
	      case 41:
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
	      case 38:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 205 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 1813 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR151 ();
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 377 "syntax.act"

	(ZIinst)=add_instruction_action((ZIi));
#line 1838 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 1:
	{
	    SID_STRING ZIi;
	    args_listP ZIa;

	    /* BEGINNING OF EXTRACT: sid-identifier */
	    {
#line 217 "syntax.act"

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
    ZIi = xstrcpy ( buff ) ;
#line 1874 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: sid-identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: null-args-list */
	    {
#line 409 "syntax.act"

    (ZIa) = NULL ;
#line 1883 "tmp.syntax.c"
	    }
	    /* END OF ACTION: null-args-list */
	    /* BEGINNING OF ACTION: make-inst */
	    {
#line 364 "syntax.act"

    if((ZIa)) {
        (ZIinst)=add_instruction_function((ZIi),(ZIa));
    } 
    else {
        (ZIinst)=add_instruction_return_token((ZIi));
    }
#line 1896 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-inst */
	}
	break;
      case 30:
	{
	    /* BEGINNING OF INLINE: 154 */
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 30:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: make-donothing-inst */
		    {
#line 373 "syntax.act"

	(ZIinst)=add_instruction_donothing();
#line 1918 "tmp.syntax.c"
		    }
		    /* END OF ACTION: make-donothing-inst */
		}
	    }
	    /* END OF INLINE: 154 */
	}
	break;
      case 41:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (41);
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
      case 13: case 14: case 18: case 24: case 37:
      case 40:
	{
	    ZRcommand (ZIz);
	    /* BEGINNING OF INLINE: command-list */
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_command_Hlist;
	    }
	    /* END OF INLINE: command-list */
	}
	/*UNREACHED*/
      case 41:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: syntax-error */
	{
#line 713 "syntax.act"

    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1972 "tmp.syntax.c"
	}
	/* END OF ACTION: syntax-error */
    }
}

static void
ZRkeyword_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 41) {
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
#line 250 "syntax.act"

    ZIs = xstrcpy ( token_buff ) ;
#line 2002 "tmp.syntax.c"
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
	ZRinstruction (&ZIinst);
	/* BEGINNING OF INLINE: 161 */
	{
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 595 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 2030 "tmp.syntax.c"
		}
		/* END OF ACTION: is-global-zone */
		if (!ZI0)
		    goto ZL3;
		/* BEGINNING OF ACTION: make-keyword */
		{
#line 467 "syntax.act"

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
#line 2054 "tmp.syntax.c"
		}
		/* END OF ACTION: make-keyword */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonekeyword */
		{
#line 662 "syntax.act"

    error( ERROR_SERIOUS, "Keywords not yet implemented in a non global zone ") ;

#line 2067 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonekeyword */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 161 */
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
    return;
}

static void
ZRcopyright_Hstmt(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 41) {
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
#line 250 "syntax.act"

    ZIs = xstrcpy ( token_buff ) ;
#line 2111 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 109 */
	{
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 595 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 2127 "tmp.syntax.c"
		}
		/* END OF ACTION: is-global-zone */
		if (!ZI0)
		    goto ZL3;
		/* BEGINNING OF ACTION: make-copyright */
		{
#line 599 "syntax.act"

	/* TODO can copyright_file be passed in somehow, other than with options as a global? */
	if(options.copyright_file==NULL) {
		options.copyright_file=fopen((ZIs),"r");
		if(!options.copyright_file) {
			error(ERROR_SERIOUS, "Syntax error: unable to open copright file %s", (ZIs)) ;
		}
	}
	else 
		error(ERROR_SERIOUS, "Syntax error: you can only specify one copyright file") ;
#line 2145 "tmp.syntax.c"
		}
		/* END OF ACTION: make-copyright */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonecopyright */
		{
#line 667 "syntax.act"

    error( ERROR_SERIOUS, "Syntax error: A copyright file may only be specified in the global zone") ;
#line 2157 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonecopyright */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 109 */
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
    return;
}

static void
ZRif_Hcommand(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 41) {
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
#line 205 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2202 "tmp.syntax.c"
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
#line 524 "syntax.act"

    (ZIj) = crt_cond ;
#line 2222 "tmp.syntax.c"
	}
	/* END OF ACTION: get-condition */
	/* BEGINNING OF ACTION: add-condition */
	{
#line 492 "syntax.act"

    if ( crt_cond ) {
	crt_cond = xstrcat ( crt_cond, xstrcat ( " && ", (ZIi) ) ) ;
    } else {
	crt_cond = (ZIi) ;
    }
#line 2234 "tmp.syntax.c"
	}
	/* END OF ACTION: add-condition */
	ZRcommand (ZIz);
	/* BEGINNING OF INLINE: 166 */
	{
	    if ((CURRENT_TERMINAL) == 41) {
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
#line 507 "syntax.act"

    if ( crt_cond ) {
	if ( strchr ( crt_cond, '&' ) ) {
	    crt_cond = xstrcat ( xstrcat ( "!( ", crt_cond ), " )" ) ;
	} else {
	    crt_cond = xstrcat ( "!", crt_cond ) ;
	}
    }
#line 2263 "tmp.syntax.c"
		}
		/* END OF ACTION: compl-condition */
		ZRcommand (ZIz);
		if ((CURRENT_TERMINAL) == 41) {
		    RESTORE_LEXER;
		    goto ZL3;
		}
		/* BEGINNING OF ACTION: set-condition */
		{
#line 535 "syntax.act"

    crt_cond = (ZIj) ;
#line 2276 "tmp.syntax.c"
		}
		/* END OF ACTION: set-condition */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: set-condition */
		{
#line 535 "syntax.act"

    crt_cond = (ZIj) ;
#line 2288 "tmp.syntax.c"
		}
		/* END OF ACTION: set-condition */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 166 */
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
    return;
}

static void
ZRcommand(zoneP ZIz)
{
    switch (CURRENT_TERMINAL) {
      case 7:
	{
	    ADVANCE_LEXER;
	    ZR191 (&ZIz);
	    if ((CURRENT_TERMINAL) == 41) {
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
	      case 41:
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
	    ZR192 (&ZIz);
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 37:
	{
	    ZRaction_Hdecl (ZIz);
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 6:
	{
	    ZRcopyright_Hstmt (ZIz);
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 14:
	{
	    ZRif_Hcommand (ZIz);
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 8:
	{
	    ZRkeyword_Hdefn (ZIz);
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 9:
	{
	    ZRtrigraph_Hdefn (ZIz);
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 40:
	{
	    ZRtype_Hdefn (ZIz);
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 13:
	{
	    ZRzone_Hdefn (ZIz);
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 41:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (41);
    return;
}

static void
ZRnon_Hempty_Htuple_Hargs(args_listP *ZOl)
{
    args_listP ZIl;

    if ((CURRENT_TERMINAL) == 41) {
	return;
    }
    {
	argP ZIa;

	ZRsingle_Harg (&ZIa);
	ZR196 (&ZIa, &ZIl);
	if ((CURRENT_TERMINAL) == 41) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (41);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZRaction_Hcall_C_Crhs_Htuple(void)
{
    if ((CURRENT_TERMINAL) == 41) {
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
	/* BEGINNING OF INLINE: 149 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 0:
		{
		    ZRaction_Hcall_C_Crhs_Htuple1 ();
		    if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	/* END OF INLINE: 149 */
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
    SAVE_LEXER (41);
    return;
}

static void
ZRnon_Hempty_Hchars(zoneP ZIz, SID_CHARS *ZOc)
{
    SID_CHARS ZIc;

    if ((CURRENT_TERMINAL) == 41) {
	return;
    }
    {
	ZRchars (ZIz, &ZIc);
	/* BEGINNING OF INLINE: 107 */
	{
	    if ((CURRENT_TERMINAL) == 41) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-non-empty */
		{
#line 441 "syntax.act"

    (ZI0)=((ZIc)[0]!=(ZIz)->top_level->last_letter_code);
#line 2519 "tmp.syntax.c"
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
#line 445 "syntax.act"

        error(ERROR_SERIOUS, "Empty character string is not allowed here, try using DEFAULT instead");	
#line 2533 "tmp.syntax.c"
		}
		/* END OF ACTION: E_empty_character_string */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 107 */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (41);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRsingle_Harg(argP *ZOa)
{
    argP ZIa;

    switch (CURRENT_TERMINAL) {
      case 32:
	{
	    /* BEGINNING OF EXTRACT: arg-char-list */
	    {
#line 268 "syntax.act"

      ZIa=add_arg(arg_chars_list,0);
#line 2562 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-list */
	    ADVANCE_LEXER;
	}
	break;
      case 34:
	{
	    /* BEGINNING OF EXTRACT: arg-char-nb */
	    {
#line 276 "syntax.act"

      ZIa=add_arg(arg_char_nb,number_buffer);
#line 2575 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-nb */
	    ADVANCE_LEXER;
	}
	break;
      case 33:
	{
	    /* BEGINNING OF EXTRACT: arg-char-string */
	    {
#line 272 "syntax.act"

      ZIa=add_arg(arg_charP,0);
#line 2588 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-string */
	    ADVANCE_LEXER;
	}
	break;
      case 35:
	{
	    /* BEGINNING OF EXTRACT: arg-nb-of-chars */
	    {
#line 280 "syntax.act"

      ZIa=add_arg(arg_nb_of_chars,0);
#line 2601 "tmp.syntax.c"
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
#line 250 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 2616 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_string */
	    {
#line 585 "syntax.act"

	(ZIa) = add_litteral_arg ((ZIb));
#line 2625 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_string */
	}
	break;
      case 41:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (41);
    return;
  ZL0:;
    *ZOa = ZIa;
}

static void
ZR114(void)
{
    if ((CURRENT_TERMINAL) == 41) {
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
#line 709 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected equal \'=\'");
#line 2666 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_equal */
    }
}

static void
ZR122(void)
{
    if ((CURRENT_TERMINAL) == 41) {
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
#line 705 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected arrow \'->\'");
#line 2695 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_arrow */
    }
}

/* BEGINNING OF TRAILER */

#line 718 "syntax.act"

#line 2705 "tmp.syntax.c"

/* END OF FILE */
