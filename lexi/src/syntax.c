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
static void ZR145(void);
static void ZRtype_Hdefn(zoneP);
static void ZRchars(zoneP, SID_CHARS *);
static void ZRaction_Hcall_C_Clhs_Htuple1(args_listP *);
static void ZR159(args_listP *);
static void ZRtype_Htuple(zoneP, TypeTupleT *);
static void ZRinstructions_Hlist(zoneP, instructions_listP *);
static void ZRtype_Htuple_C_Ctype_Hname(zoneP, TypeTupleT *);
static void ZRargs(args_listP *);
static void ZRtrigraph_Hdefn(zoneP);
static void ZR184(zoneP *, SID_CHARS *);
static void ZR186(zoneP *, instructions_listP *);
extern void read_lex(zoneP);
static void ZR200(zoneP *);
static void ZR201(zoneP *);
static void ZRaction_Hdecl(zoneP);
static void ZRinstruction(zoneP, instructionP *);
static void ZR204(zoneP *, SID_STRING *, instructionP *);
static void ZR205(argP *, args_listP *);
static void ZR206(argP *, args_listP *);
static void ZR207(zoneP *, instructionP *, instructions_listP *);
static void ZRcommand_Hlist(zoneP);
static void ZR209(zoneP *, TypeTupleT *);
static void ZRkeyword_Hdefn(zoneP);
static void ZRcopyright_Hstmt(zoneP);
static void ZRif_Hcommand(zoneP);
static void ZRcommand(zoneP);
static void ZRnon_Hempty_Htuple_Hargs(args_listP *);
static void ZRaction_Hcall_C_Crhs_Htuple(args_listP *);
static void ZRnon_Hempty_Hchars(zoneP, SID_CHARS *);
static void ZRsingle_Harg(argP *);
static void ZRaction_Hcall_C_Clhs_Harg(argP *);
static void ZR122(void);

/* BEGINNING OF STATIC VARIABLES */

static int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRexpected__semicolon(void)
{
    if ((CURRENT_TERMINAL) == 43) {
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
#line 722 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected semicolon \';\'");
#line 184 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_semicolon */
    }
}

static void
ZRtuple_Hargs(args_listP *ZOl)
{
    args_listP ZIl;

    switch (CURRENT_TERMINAL) {
      case 38:
	{
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 417 "syntax.act"

    (ZIl)=add_args_list();
#line 204 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	}
	break;
      case 0: case 2: case 32: case 33: case 34:
      case 35: case 36: case 37:
	{
	    ZRnon_Hempty_Htuple_Hargs (&ZIl);
	    if ((CURRENT_TERMINAL) == 43) {
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
#line 417 "syntax.act"

    (ZIl)=add_args_list();
#line 228 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: arg-char-list-tmp */
	    {
#line 402 "syntax.act"

      (ZItmp)=add_arg(arg_chars_list,0);
#line 236 "tmp.syntax.c"
	    }
	    /* END OF ACTION: arg-char-list-tmp */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 409 "syntax.act"

    (ZItmp)->next=(ZIl)->head;
    (ZIl)->head=(ZItmp);
#line 245 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      case 43:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZRzone_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 43) {
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
	/* BEGINNING OF INLINE: 176 */
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 0:
		    /* BEGINNING OF EXTRACT: identifier */
		    {
#line 205 "syntax.act"

    ZIzid = xstrcpy ( token_buff ) ;
#line 293 "tmp.syntax.c"
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
#line 704 "syntax.act"

	(ZIzid)="";
	error(ERROR_SERIOUS, "Syntax error: expected identifier");
#line 311 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_identifier */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 176 */
	/* BEGINNING OF INLINE: 178 */
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
#line 718 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected colon \':\'");
#line 337 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_colon */
	    }
	  ZL4:;
	}
	/* END OF INLINE: 178 */
	ZR184 (&ZIz, &ZIb);
	ZR186 (&ZIz, &ZIentry_Hinstl);
	/* BEGINNING OF INLINE: 182 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 26:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: true */
		    {
#line 565 "syntax.act"
 (ZIlendclosed) = 1 ; 
#line 356 "tmp.syntax.c"
		    }
		    /* END OF ACTION: true */
		}
		break;
	      case 27:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: true */
		    {
#line 565 "syntax.act"
 (ZIlendclosed) = 1 ; 
#line 368 "tmp.syntax.c"
		    }
		    /* END OF ACTION: true */
		}
		break;
	      case 28:
		{
		    ADVANCE_LEXER;
		    /* BEGINNING OF ACTION: false */
		    {
#line 566 "syntax.act"
 (ZIlendclosed) = 0 ; 
#line 380 "tmp.syntax.c"
		    }
		    /* END OF ACTION: false */
		}
		break;
	      case 43:
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
#line 709 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected range");
#line 399 "tmp.syntax.c"
		}
		/* END OF ACTION: E_expected_range */
		/* BEGINNING OF ACTION: false */
		{
#line 566 "syntax.act"
 (ZIlendclosed) = 0 ; 
#line 406 "tmp.syntax.c"
		}
		/* END OF ACTION: false */
	    }
	  ZL6:;
	}
	/* END OF INLINE: 182 */
	ZR184 (&ZIz, &ZIe);
	ZR186 (&ZIz, &ZIleaving_Hinstl);
	if ((CURRENT_TERMINAL) == 43) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-zone */
	{
#line 582 "syntax.act"

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
#line 433 "tmp.syntax.c"
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
	  case 43:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    SAVE_LEXER (43);
    return;
}

static void
ZRstring_Hplus(SID_STRING *ZOs)
{
    SID_STRING ZIs;

    if ((CURRENT_TERMINAL) == 43) {
	return;
    }
    {
	SID_STRING ZIa;

	/* BEGINNING OF INLINE: 106 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 5:
		{
		    /* BEGINNING OF EXTRACT: digit */
		    {
#line 263 "syntax.act"
 ZIa = "0123456789" ; 
#line 481 "tmp.syntax.c"
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
#line 493 "tmp.syntax.c"
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
#line 506 "tmp.syntax.c"
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
#line 518 "tmp.syntax.c"
		    }
		    /* END OF EXTRACT: upper */
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	/* END OF INLINE: 106 */
	/* BEGINNING OF INLINE: 108 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 23:
		{
		    SID_STRING ZIb;

		    ADVANCE_LEXER;
		    ZRstring_Hplus (&ZIb);
		    if ((CURRENT_TERMINAL) == 43) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    /* BEGINNING OF ACTION: string-concat */
		    {
#line 301 "syntax.act"

    (ZIs) = xstrcat ( (ZIa), (ZIb) ) ;
#line 547 "tmp.syntax.c"
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
	/* END OF INLINE: 108 */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOs = ZIs;
}

static void
ZR145(void)
{
    if ((CURRENT_TERMINAL) == 43) {
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
#line 726 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected arrow \'->\'");
#line 592 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_arrow */
    }
}

static void
ZRtype_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 43) {
	return;
    }
    {
	SID_STRING ZIs;

	switch (CURRENT_TERMINAL) {
	  case 42:
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
#line 621 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 133 */
	{
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 612 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 637 "tmp.syntax.c"
		}
		/* END OF ACTION: is-global-zone */
		if (!ZI0)
		    goto ZL3;
		/* BEGINNING OF ACTION: make-type */
		{
#line 628 "syntax.act"

	NStringT str;
	nstring_copy_cstring(&str,(ZIs));
	xfree((ZIs));
	if(table_get_entry((ZIz)->top_level->table, &str)) {
		nstring_destroy(&str);
		error(ERROR_SERIOUS, "can't create type %s because of name clash",(ZIs));
	} else {
		table_add_type((ZIz)->top_level->table, &str);
	}
#line 655 "tmp.syntax.c"
		}
		/* END OF ACTION: make-type */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonetype */
		{
#line 693 "syntax.act"

    error( ERROR_SERIOUS, "Syntax error: type %s should not be declared inside a zone",(ZIs)) ;
#line 667 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonetype */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 133 */
    }
    return;
  ZL1:;
    SAVE_LEXER (43);
    return;
}

static void
ZRchars(zoneP ZIz, SID_CHARS *ZOc)
{
    SID_CHARS ZIc;

    if ((CURRENT_TERMINAL) == 43) {
	return;
    }
    {
	SID_STRING ZIs;

	ZRstring_Hplus (&ZIs);
	if ((CURRENT_TERMINAL) == 43) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-chars */
	{
#line 324 "syntax.act"

    (ZIc) = make_string ( (ZIs), (ZIz) ) ;
#line 702 "tmp.syntax.c"
	}
	/* END OF ACTION: make-chars */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRaction_Hcall_C_Clhs_Htuple1(args_listP *ZOl)
{
    args_listP ZIl;

    if ((CURRENT_TERMINAL) == 43) {
	return;
    }
    {
	argP ZIa;

	ZRaction_Hcall_C_Clhs_Harg (&ZIa);
	ZR206 (&ZIa, &ZIl);
	if ((CURRENT_TERMINAL) == 43) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZR159(args_listP *ZOr)
{
    args_listP ZIr;

    switch (CURRENT_TERMINAL) {
      case 16:
	{
	    ZRaction_Hcall_C_Crhs_Htuple (&ZIr);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 417 "syntax.act"

    (ZIr)=add_args_list();
#line 762 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	}
	break;
      case 43:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOr = ZIr;
}

static void
ZRtype_Htuple(zoneP ZIz, TypeTupleT *ZOa)
{
    TypeTupleT ZIa;

    if ((CURRENT_TERMINAL) == 43) {
	return;
    }
    {
	/* BEGINNING OF ACTION: init-tuple */
	{
#line 656 "syntax.act"

	typetuple_init(&(ZIa));
#line 792 "tmp.syntax.c"
	}
	/* END OF ACTION: init-tuple */
	ZR209 (&ZIz, &ZIa);
	if ((CURRENT_TERMINAL) == 43) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    /* BEGINNING OF RESULT ASSIGNMENT: TYPETUPLE */
    {
#line 190 "syntax.act"

	typetuple_assign(ZOa, (&ZIa));
#line 811 "tmp.syntax.c"
    }
    /* END OF RESULT ASSIGNMENT: TYPETUPLE */
}

static void
ZRinstructions_Hlist(zoneP ZIz, instructions_listP *ZOinstl)
{
    instructions_listP ZIinstl;

    if ((CURRENT_TERMINAL) == 43) {
	return;
    }
    {
	instructionP ZIinst;

	ZRinstruction (ZIz, &ZIinst);
	ZR207 (&ZIz, &ZIinst, &ZIinstl);
	if ((CURRENT_TERMINAL) == 43) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
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
#line 852 "tmp.syntax.c"
    }
    /* END OF PARAM ASSIGNMENT: TYPETUPLE */
    if ((CURRENT_TERMINAL) == 43) {
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
#line 869 "tmp.syntax.c"
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
#line 891 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF ACTION: append-tuple */
	{
#line 660 "syntax.act"

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
	xfree((ZItype));
	xfree((ZIname));
#line 918 "tmp.syntax.c"
	}
	/* END OF ACTION: append-tuple */
    }
    return;
  ZL1:;
    SAVE_LEXER (43);
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
	      case 43:
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
#line 424 "syntax.act"

    (ZIl) = NULL ;
#line 957 "tmp.syntax.c"
	    }
	    /* END OF ACTION: null-args-list */
	}
	break;
      case 43:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZRtrigraph_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 43) {
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
	ZR145 ();
	ZRstring_Hplus (&ZIt);
	if ((CURRENT_TERMINAL) == 43) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	/* BEGINNING OF ACTION: make-trigraph */
	{
#line 362 "syntax.act"

    add_char ( (ZIz), (ZIz)->zone_pre_pass, (ZIs), crt_cond, NULL, (ZIt)) ;
#line 1002 "tmp.syntax.c"
	}
	/* END OF ACTION: make-trigraph */
    }
    return;
  ZL1:;
    SAVE_LEXER (43);
    return;
}

static void
ZR184(zoneP *ZIz, SID_CHARS *ZOe)
{
    SID_CHARS ZIe;

    if ((CURRENT_TERMINAL) == 43) {
	return;
    }
    {
	ZRnon_Hempty_Hchars (*ZIz, &ZIe);
	if ((CURRENT_TERMINAL) == 43) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    {
	/* BEGINNING OF ACTION: E_expected_chars */
	{
#line 713 "syntax.act"

        (ZIe) = NULL ;
	error(ERROR_SERIOUS, "Syntax error: expected characters");
#line 1036 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_chars */
    }
  ZL0:;
    *ZOe = ZIe;
}

static void
ZR186(zoneP *ZIz, instructions_listP *ZOleaving_Hinstl)
{
    instructions_listP ZIleaving_Hinstl;

    switch (CURRENT_TERMINAL) {
      case 20:
	{
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (*ZIz, &ZIleaving_Hinstl);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-inst-list */
	    {
#line 445 "syntax.act"

    (ZIleaving_Hinstl)=add_instructions_list();
#line 1067 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-inst-list */
	}
	break;
      case 43:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOleaving_Hinstl = ZIleaving_Hinstl;
}

void
read_lex(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 43) {
	return;
    }
    {
	ZRcommand_Hlist (ZIz);
	/* BEGINNING OF INLINE: 191 */
	{
	    if ((CURRENT_TERMINAL) == 43) {
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
#line 734 "syntax.act"

	error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1114 "tmp.syntax.c"
		}
		/* END OF ACTION: syntax-error */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 191 */
    }
    return;
  ZL1:;
    SAVE_LEXER (43);
    return;
}

static void
ZR200(zoneP *ZIz)
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
#line 1142 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    ZR122 ();
	    ZRchars (*ZIz, &ZIs);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-group */
	    {
#line 351 "syntax.act"

    make_group ( (*ZIz), (ZIi), (ZIs) ) ;
#line 1157 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-group */
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 11:
	{
	    SID_CHARS ZIs;

	    ADVANCE_LEXER;
	    ZR122 ();
	    ZRchars (*ZIz, &ZIs);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-white */
	    {
#line 337 "syntax.act"

    if ( (*ZIz)->white_space) {
	error ( ERROR_SERIOUS, "White space group already defined" ) ;
    }
    (*ZIz)->white_space= make_group((*ZIz),"white",(ZIs)) ;
#line 1186 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-white */
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 43:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (43);
    return;
}

static void
ZR201(zoneP *ZIz)
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
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-default */
	    {
#line 473 "syntax.act"

    (*ZIz)->default_actions=(ZIinst_Hlist);
    (*ZIz)->default_cond=crt_cond;
#line 1234 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-default */
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 43) {
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
	      case 43:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (*ZIz, &ZIinst_Hlist);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-token */
	    {
#line 456 "syntax.act"

        add_char ( (*ZIz), (*ZIz)->zone_main_pass, (ZIs), crt_cond, (ZIinst_Hlist), NULL) ;
#line 1270 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-token */
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 43:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (43);
    return;
}

static void
ZRaction_Hdecl(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 43) {
	return;
    }
    {
	SID_STRING ZIi;
	TypeTupleT ZIit;
	TypeTupleT ZIot;

	switch (CURRENT_TERMINAL) {
	  case 39:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
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

    ZIi = xstrcpy ( token_buff ) ;
#line 1323 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
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
	/* BEGINNING OF INLINE: 142 */
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
		      case 43:
			RESTORE_LEXER;
			goto ZL1;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    ZR145 ();
		    switch (CURRENT_TERMINAL) {
		      case 16:
			break;
		      case 43:
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
		      case 43:
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
#line 656 "syntax.act"

	typetuple_init(&(ZIit));
#line 1393 "tmp.syntax.c"
		    }
		    /* END OF ACTION: init-tuple */
		    /* BEGINNING OF ACTION: init-tuple */
		    {
#line 656 "syntax.act"

	typetuple_init(&(ZIot));
#line 1401 "tmp.syntax.c"
		    }
		    /* END OF ACTION: init-tuple */
		}
		break;
	    }
	}
	/* END OF INLINE: 142 */
	/* BEGINNING OF ACTION: make-action */
	{
#line 640 "syntax.act"

	NStringT str;
	nstring_copy_cstring(&str, (ZIi));
	xfree((ZIi));
	if(table_get_entry((ZIz)->top_level->table, &str)) {
		error(ERROR_SERIOUS, "can't create action %s because of name clash",(ZIi));
		nstring_destroy(&str);
	} else {
		table_add_action((ZIz)->top_level->table, &str , (&ZIit), (&ZIot));
	}
#line 1422 "tmp.syntax.c"
	}
	/* END OF ACTION: make-action */
    }
    return;
  ZL1:;
    SAVE_LEXER (43);
    return;
}

static void
ZRinstruction(zoneP ZIz, instructionP *ZOinst)
{
    instructionP ZIinst;

    switch (CURRENT_TERMINAL) {
      case 32:
	{
	    argP ZIb;
	    argP ZIa;
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    /* BEGINNING OF EXTRACT: arg-char-list */
	    {
#line 268 "syntax.act"

      ZIb=add_arg(arg_chars_list,0);
#line 1451 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-list */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 603 "syntax.act"

	(ZIa) = add_none_arg();
#line 1460 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 738 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1468 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 417 "syntax.act"

    (ZIl)=add_args_list();
#line 1476 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 409 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1485 "tmp.syntax.c"
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

    ZIi = xstrcpy ( token_buff ) ;
#line 1509 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
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
	    ZR159 (&ZIr);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 384 "syntax.act"

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
#line 1547 "tmp.syntax.c"
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

	    /* BEGINNING OF EXTRACT: arg-char-nb */
	    {
#line 276 "syntax.act"

      ZIb=add_arg(arg_char_nb,number_buffer);
#line 1565 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-nb */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 603 "syntax.act"

	(ZIa) = add_none_arg();
#line 1574 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 738 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1582 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 417 "syntax.act"

    (ZIl)=add_args_list();
#line 1590 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 409 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1599 "tmp.syntax.c"
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

    ZIi = xstrcpy ( token_buff ) ;
#line 1623 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
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
	    ZR159 (&ZIr);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 384 "syntax.act"

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
#line 1661 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 33:
	{
	    argP ZIb;
	    argP ZIa;
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    /* BEGINNING OF EXTRACT: arg-char-string */
	    {
#line 272 "syntax.act"

      ZIb=add_arg(arg_charP,0);
#line 1679 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 603 "syntax.act"

	(ZIa) = add_none_arg();
#line 1688 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 738 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1696 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 417 "syntax.act"

    (ZIl)=add_args_list();
#line 1704 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 409 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1713 "tmp.syntax.c"
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

    ZIi = xstrcpy ( token_buff ) ;
#line 1737 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
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
	    ZR159 (&ZIr);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 384 "syntax.act"

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
#line 1775 "tmp.syntax.c"
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

	    /* BEGINNING OF EXTRACT: arg-ignore */
	    {
#line 288 "syntax.act"

      ZIa=add_arg(arg_ignore,0);
#line 1792 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-ignore */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 417 "syntax.act"

    (ZIl)=add_args_list();
#line 1801 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 409 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1810 "tmp.syntax.c"
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

    ZIi = xstrcpy ( token_buff ) ;
#line 1834 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
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
	    ZR159 (&ZIr);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 384 "syntax.act"

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
#line 1872 "tmp.syntax.c"
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

	    /* BEGINNING OF EXTRACT: arg-nb-of-chars */
	    {
#line 280 "syntax.act"

      ZIb=add_arg(arg_nb_of_chars,0);
#line 1890 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-nb-of-chars */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 603 "syntax.act"

	(ZIa) = add_none_arg();
#line 1899 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 738 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 1907 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 417 "syntax.act"

    (ZIl)=add_args_list();
#line 1915 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 409 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 1924 "tmp.syntax.c"
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

    ZIi = xstrcpy ( token_buff ) ;
#line 1948 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
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
	    ZR159 (&ZIr);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 384 "syntax.act"

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
#line 1986 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 36:
	{
	    argP ZIa;
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    /* BEGINNING OF EXTRACT: arg-return-terminal */
	    {
#line 284 "syntax.act"

      ZIa=add_arg(arg_return_terminal,0);
#line 2003 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-return-terminal */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 417 "syntax.act"

    (ZIl)=add_args_list();
#line 2012 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 409 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 2021 "tmp.syntax.c"
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

    ZIi = xstrcpy ( token_buff ) ;
#line 2045 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
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
	    ZR159 (&ZIr);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 384 "syntax.act"

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
#line 2083 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 0:
	{
	    SID_STRING ZI203;

	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 205 "syntax.act"

    ZI203 = xstrcpy ( token_buff ) ;
#line 2097 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    ZR204 (&ZIz, &ZI203, &ZIinst);
	    if ((CURRENT_TERMINAL) == 43) {
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
	      case 43:
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

    ZIi = xstrcpy ( token_buff ) ;
#line 2147 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
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
	    ZR159 (&ZIr);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 384 "syntax.act"

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
#line 2185 "tmp.syntax.c"
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
#line 2221 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: sid-identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: null-args-list */
	    {
#line 424 "syntax.act"

    (ZIa) = NULL ;
#line 2230 "tmp.syntax.c"
	    }
	    /* END OF ACTION: null-args-list */
	    /* BEGINNING OF ACTION: make-inst */
	    {
#line 371 "syntax.act"

    if((ZIa)) {
        (ZIinst)=add_instruction_function((ZIi),(ZIa));
    } 
    else {
        (ZIinst)=add_instruction_return_terminal((ZIi));
    }
#line 2243 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-inst */
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
#line 250 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 2261 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 603 "syntax.act"

	(ZIa) = add_none_arg();
#line 2270 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_string_arg_in_lhs */
	    {
#line 742 "syntax.act"

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
#line 2278 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_string_arg_in_lhs */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 417 "syntax.act"

    (ZIl)=add_args_list();
#line 2286 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 409 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 2295 "tmp.syntax.c"
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

    ZIi = xstrcpy ( token_buff ) ;
#line 2319 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
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
	    ZR159 (&ZIr);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 384 "syntax.act"

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
#line 2357 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 30:
	{
	    /* BEGINNING OF INLINE: 162 */
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
#line 380 "syntax.act"

	(ZIinst)=add_instruction_donothing();
#line 2379 "tmp.syntax.c"
		    }
		    /* END OF ACTION: make-donothing-inst */
		}
	    }
	    /* END OF INLINE: 162 */
	}
	break;
      case 40:
	{
	    args_listP ZIl;
	    SID_STRING ZIi;
	    args_listP ZIr;

	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 417 "syntax.act"

    (ZIl)=add_args_list();
#line 2398 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		/* BEGINNING OF EXTRACT: identifier */
		{
#line 205 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 2409 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
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
	    ZR159 (&ZIr);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 384 "syntax.act"

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
#line 2447 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 43:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOinst = ZIinst;
}

static void
ZR204(zoneP *ZIz, SID_STRING *ZI203, instructionP *ZOinst)
{
    instructionP ZIinst;

    switch (CURRENT_TERMINAL) {
      default:
	{
	    args_listP ZIa;

	    ZRargs (&ZIa);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-inst */
	    {
#line 371 "syntax.act"

    if((ZIa)) {
        (ZIinst)=add_instruction_function((*ZI203),(ZIa));
    } 
    else {
        (ZIinst)=add_instruction_return_terminal((*ZI203));
    }
#line 2490 "tmp.syntax.c"
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
#line 599 "syntax.act"

	(ZIa) = add_identifier_arg ((*ZI203));
#line 2507 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_identifier */
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 417 "syntax.act"

    (ZIl)=add_args_list();
#line 2515 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 409 "syntax.act"

    (ZIa)->next=(ZIl)->head;
    (ZIl)->head=(ZIa);
#line 2524 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	    ADVANCE_LEXER;
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

    ZIi = xstrcpy ( token_buff ) ;
#line 2542 "tmp.syntax.c"
		}
		/* END OF EXTRACT: identifier */
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
	    ZR159 (&ZIr);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: make-action-inst */
	    {
#line 384 "syntax.act"

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
#line 2580 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make-action-inst */
	}
	break;
      case 43:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOinst = ZIinst;
}

static void
ZR205(argP *ZIa, args_listP *ZOl)
{
    args_listP ZIl;

    switch (CURRENT_TERMINAL) {
      case 29:
	{
	    ADVANCE_LEXER;
	    ZRnon_Hempty_Htuple_Hargs (&ZIl);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 409 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 2616 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 417 "syntax.act"

    (ZIl)=add_args_list();
#line 2628 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 409 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 2637 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      case 43:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZR206(argP *ZIa, args_listP *ZOl)
{
    args_listP ZIl;

    switch (CURRENT_TERMINAL) {
      case 29:
	{
	    ADVANCE_LEXER;
	    ZRaction_Hcall_C_Clhs_Htuple1 (&ZIl);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 409 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 2673 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-args-list */
	    {
#line 417 "syntax.act"

    (ZIl)=add_args_list();
#line 2685 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-args-list */
	    /* BEGINNING OF ACTION: args-list-push-front */
	    {
#line 409 "syntax.act"

    (*ZIa)->next=(ZIl)->head;
    (ZIl)->head=(*ZIa);
#line 2694 "tmp.syntax.c"
	    }
	    /* END OF ACTION: args-list-push-front */
	}
	break;
      case 43:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZR207(zoneP *ZIz, instructionP *ZIinst, instructions_listP *ZOinstl)
{
    instructions_listP ZIinstl;

    switch (CURRENT_TERMINAL) {
      case 29:
	{
	    ADVANCE_LEXER;
	    ZRinstructions_Hlist (*ZIz, &ZIinstl);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    /* BEGINNING OF ACTION: add-inst-to-list */
	    {
#line 431 "syntax.act"

	if((*ZIinst)!=NULL) { // if (*ZIinst) == NULL, an error has already been issued.
		if(((ZIinstl)->head !=NULL) && ((*ZIinst)->type==return_terminal || (*ZIinst)->type==do_nothing)) {
			error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an arg-list"); 
		}
		(*ZIinst)->next=(ZIinstl)->head;
		(ZIinstl)->head=(*ZIinst);
	}
#line 2735 "tmp.syntax.c"
	    }
	    /* END OF ACTION: add-inst-to-list */
	}
	break;
      default:
	{
	    /* BEGINNING OF ACTION: empty-inst-list */
	    {
#line 445 "syntax.act"

    (ZIinstl)=add_instructions_list();
#line 2747 "tmp.syntax.c"
	    }
	    /* END OF ACTION: empty-inst-list */
	    /* BEGINNING OF ACTION: add-inst-to-list */
	    {
#line 431 "syntax.act"

	if((*ZIinst)!=NULL) { // if (*ZIinst) == NULL, an error has already been issued.
		if(((ZIinstl)->head !=NULL) && ((*ZIinst)->type==return_terminal || (*ZIinst)->type==do_nothing)) {
			error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an arg-list"); 
		}
		(*ZIinst)->next=(ZIinstl)->head;
		(ZIinstl)->head=(*ZIinst);
	}
#line 2761 "tmp.syntax.c"
	    }
	    /* END OF ACTION: add-inst-to-list */
	}
	break;
      case 43:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOinstl = ZIinstl;
}

static void
ZRcommand_Hlist(zoneP ZIz)
{
  ZL2_command_Hlist:;
    switch (CURRENT_TERMINAL) {
      case 6: case 7: case 8: case 9: case 10:
      case 13: case 14: case 18: case 24: case 39:
      case 42:
	{
	    ZRcommand (ZIz);
	    /* BEGINNING OF INLINE: command-list */
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_command_Hlist;
	    }
	    /* END OF INLINE: command-list */
	}
	/*UNREACHED*/
      case 43:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    {
	/* BEGINNING OF ACTION: syntax-error */
	{
#line 734 "syntax.act"

	error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 2810 "tmp.syntax.c"
	}
	/* END OF ACTION: syntax-error */
    }
}

static void
ZR209(zoneP *ZIz, TypeTupleT *ZIa)
{
  ZL2_209:;
    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    /* BEGINNING OF INLINE: type-tuple::type-tuple1 */
	    {
		{
		    ZRtype_Htuple_C_Ctype_Hname (*ZIz, ZIa);
		    /* BEGINNING OF INLINE: 209 */
		    if ((CURRENT_TERMINAL) == 43) {
			RESTORE_LEXER;
			goto ZL1;
		    } else {
			goto ZL2_209;
		    }
		    /* END OF INLINE: 209 */
		}
		/*UNREACHED*/
	    }
	    /* END OF INLINE: type-tuple::type-tuple1 */
	}
	/*UNREACHED*/
      case 43:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (43);
    return;
}

static void
ZRkeyword_Hdefn(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 43) {
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
#line 2876 "tmp.syntax.c"
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
	/* BEGINNING OF INLINE: 169 */
	{
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 612 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 2904 "tmp.syntax.c"
		}
		/* END OF ACTION: is-global-zone */
		if (!ZI0)
		    goto ZL3;
		/* BEGINNING OF ACTION: make-keyword */
		{
#line 486 "syntax.act"

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
#line 2928 "tmp.syntax.c"
		}
		/* END OF ACTION: make-keyword */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonekeyword */
		{
#line 683 "syntax.act"

    error( ERROR_SERIOUS, "Keywords not yet implemented in a non global zone ") ;

#line 2941 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonekeyword */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 169 */
    }
    return;
  ZL1:;
    SAVE_LEXER (43);
    return;
}

static void
ZRcopyright_Hstmt(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 43) {
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
#line 2985 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	/* BEGINNING OF INLINE: 117 */
	{
	    {
		/* BEGINNING OF ACTION: is-global-zone */
		{
#line 612 "syntax.act"

   (ZI0)=((ZIz)==(ZIz)->top_level->global_zone);
#line 3001 "tmp.syntax.c"
		}
		/* END OF ACTION: is-global-zone */
		if (!ZI0)
		    goto ZL3;
		/* BEGINNING OF ACTION: make-copyright */
		{
#line 616 "syntax.act"

	/* TODO can copyright_file be passed in somehow, other than with options as a global? */
	if(options.copyright_file==NULL) {
		options.copyright_file=fopen((ZIs),"r");
		if(!options.copyright_file) {
			error(ERROR_SERIOUS, "Syntax error: unable to open copright file %s", (ZIs)) ;
		}
	}
	else 
		error(ERROR_SERIOUS, "Syntax error: you can only specify one copyright file") ;
#line 3019 "tmp.syntax.c"
		}
		/* END OF ACTION: make-copyright */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: E_nonglobalzonecopyright */
		{
#line 688 "syntax.act"

    error( ERROR_SERIOUS, "Syntax error: A copyright file may only be specified in the global zone") ;
#line 3031 "tmp.syntax.c"
		}
		/* END OF ACTION: E_nonglobalzonecopyright */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 117 */
    }
    return;
  ZL1:;
    SAVE_LEXER (43);
    return;
}

static void
ZRif_Hcommand(zoneP ZIz)
{
    if ((CURRENT_TERMINAL) == 43) {
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
#line 3076 "tmp.syntax.c"
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
#line 543 "syntax.act"

    (ZIj) = crt_cond ;
#line 3096 "tmp.syntax.c"
	}
	/* END OF ACTION: get-condition */
	/* BEGINNING OF ACTION: add-condition */
	{
#line 511 "syntax.act"

    if ( crt_cond ) {
	crt_cond = xstrcat ( crt_cond, xstrcat ( " && ", (ZIi) ) ) ;
    } else {
	crt_cond = (ZIi) ;
    }
#line 3108 "tmp.syntax.c"
	}
	/* END OF ACTION: add-condition */
	ZRcommand (ZIz);
	/* BEGINNING OF INLINE: 174 */
	{
	    if ((CURRENT_TERMINAL) == 43) {
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
#line 526 "syntax.act"

    if ( crt_cond ) {
	if ( strchr ( crt_cond, '&' ) ) {
	    crt_cond = xstrcat ( xstrcat ( "!( ", crt_cond ), " )" ) ;
	} else {
	    crt_cond = xstrcat ( "!", crt_cond ) ;
	}
    }
#line 3137 "tmp.syntax.c"
		}
		/* END OF ACTION: compl-condition */
		ZRcommand (ZIz);
		if ((CURRENT_TERMINAL) == 43) {
		    RESTORE_LEXER;
		    goto ZL3;
		}
		/* BEGINNING OF ACTION: set-condition */
		{
#line 554 "syntax.act"

    crt_cond = (ZIj) ;
#line 3150 "tmp.syntax.c"
		}
		/* END OF ACTION: set-condition */
	    }
	    goto ZL2;
	  ZL3:;
	    {
		/* BEGINNING OF ACTION: set-condition */
		{
#line 554 "syntax.act"

    crt_cond = (ZIj) ;
#line 3162 "tmp.syntax.c"
		}
		/* END OF ACTION: set-condition */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 174 */
    }
    return;
  ZL1:;
    SAVE_LEXER (43);
    return;
}

static void
ZRcommand(zoneP ZIz)
{
    switch (CURRENT_TERMINAL) {
      case 7:
	{
	    ADVANCE_LEXER;
	    ZR200 (&ZIz);
	    if ((CURRENT_TERMINAL) == 43) {
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
	      case 43:
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
	    ZR201 (&ZIz);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 39:
	{
	    ZRaction_Hdecl (ZIz);
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 6:
	{
	    ZRcopyright_Hstmt (ZIz);
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 14:
	{
	    ZRif_Hcommand (ZIz);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 8:
	{
	    ZRkeyword_Hdefn (ZIz);
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 9:
	{
	    ZRtrigraph_Hdefn (ZIz);
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 42:
	{
	    ZRtype_Hdefn (ZIz);
	    ZRexpected__semicolon ();
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 13:
	{
	    ZRzone_Hdefn (ZIz);
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 43:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (43);
    return;
}

static void
ZRnon_Hempty_Htuple_Hargs(args_listP *ZOl)
{
    args_listP ZIl;

    if ((CURRENT_TERMINAL) == 43) {
	return;
    }
    {
	argP ZIa;

	ZRsingle_Harg (&ZIa);
	ZR205 (&ZIa, &ZIl);
	if ((CURRENT_TERMINAL) == 43) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOl = ZIl;
}

static void
ZRaction_Hcall_C_Crhs_Htuple(args_listP *ZOr)
{
    args_listP ZIr;

    if ((CURRENT_TERMINAL) == 43) {
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
	/* BEGINNING OF INLINE: 157 */
	{
	    switch (CURRENT_TERMINAL) {
	      case 0: case 2: case 32: case 33: case 34:
	      case 35: case 36: case 37:
		{
		    ZRnon_Hempty_Htuple_Hargs (&ZIr);
		    if ((CURRENT_TERMINAL) == 43) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    /* BEGINNING OF ACTION: empty-args-list */
		    {
#line 417 "syntax.act"

    (ZIr)=add_args_list();
#line 3362 "tmp.syntax.c"
		    }
		    /* END OF ACTION: empty-args-list */
		}
		break;
	    }
	}
	/* END OF INLINE: 157 */
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
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOr = ZIr;
}

static void
ZRnon_Hempty_Hchars(zoneP ZIz, SID_CHARS *ZOc)
{
    SID_CHARS ZIc;

    if ((CURRENT_TERMINAL) == 43) {
	return;
    }
    {
	ZRchars (ZIz, &ZIc);
	/* BEGINNING OF INLINE: 115 */
	{
	    if ((CURRENT_TERMINAL) == 43) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
		/* BEGINNING OF ACTION: is-non-empty */
		{
#line 460 "syntax.act"

    (ZI0)=((ZIc)[0]!=(ZIz)->top_level->last_letter_code);
#line 3408 "tmp.syntax.c"
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
#line 464 "syntax.act"

        error(ERROR_SERIOUS, "Empty character string is not allowed here, try using DEFAULT instead");	
#line 3422 "tmp.syntax.c"
		}
		/* END OF ACTION: E_empty_character_string */
	    }
	  ZL2:;
	}
	/* END OF INLINE: 115 */
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
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
#line 3451 "tmp.syntax.c"
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
#line 3464 "tmp.syntax.c"
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
#line 3477 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-string */
	    ADVANCE_LEXER;
	}
	break;
      case 37:
	{
	    /* BEGINNING OF EXTRACT: arg-ignore */
	    {
#line 288 "syntax.act"

      ZIa=add_arg(arg_ignore,0);
#line 3490 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-ignore */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: E_ignore_in_rhs */
	    {
#line 750 "syntax.act"

	error(ERROR_SERIOUS, "Ignore argument in right handside");
#line 3499 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_ignore_in_rhs */
	}
	break;
      case 35:
	{
	    /* BEGINNING OF EXTRACT: arg-nb-of-chars */
	    {
#line 280 "syntax.act"

      ZIa=add_arg(arg_nb_of_chars,0);
#line 3511 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-nb-of-chars */
	    ADVANCE_LEXER;
	}
	break;
      case 36:
	{
	    /* BEGINNING OF EXTRACT: arg-return-terminal */
	    {
#line 284 "syntax.act"

      ZIa=add_arg(arg_return_terminal,0);
#line 3524 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-return-terminal */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: E_return_terminal_in_rhs */
	    {
#line 746 "syntax.act"

	error(ERROR_SERIOUS, "Return terminal argument in right handside");
#line 3533 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_return_terminal_in_rhs */
	}
	break;
      case 0:
	{
	    SID_STRING ZIi;

	    /* BEGINNING OF EXTRACT: identifier */
	    {
#line 205 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 3547 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_identifier */
	    {
#line 599 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 3556 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_identifier */
	}
	break;
      case 2:
	{
	    SID_STRING ZIb;

	    /* BEGINNING OF EXTRACT: string */
	    {
#line 250 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 3570 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_string */
	    {
#line 595 "syntax.act"

	(ZIa) = add_litteral_arg ((ZIb));
#line 3579 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_string */
	}
	break;
      case 43:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOa = ZIa;
}

static void
ZRaction_Hcall_C_Clhs_Harg(argP *ZOa)
{
    argP ZIa;

    switch (CURRENT_TERMINAL) {
      case 32:
	{
	    argP ZIb;

	    /* BEGINNING OF EXTRACT: arg-char-list */
	    {
#line 268 "syntax.act"

      ZIb=add_arg(arg_chars_list,0);
#line 3612 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-list */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 603 "syntax.act"

	(ZIa) = add_none_arg();
#line 3621 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 738 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 3629 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	}
	break;
      case 34:
	{
	    argP ZIb;

	    /* BEGINNING OF EXTRACT: arg-char-nb */
	    {
#line 276 "syntax.act"

      ZIb=add_arg(arg_char_nb,number_buffer);
#line 3643 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-nb */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 603 "syntax.act"

	(ZIa) = add_none_arg();
#line 3652 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 738 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 3660 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	}
	break;
      case 33:
	{
	    argP ZIb;

	    /* BEGINNING OF EXTRACT: arg-char-string */
	    {
#line 272 "syntax.act"

      ZIb=add_arg(arg_charP,0);
#line 3674 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-char-string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 603 "syntax.act"

	(ZIa) = add_none_arg();
#line 3683 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 738 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 3691 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	}
	break;
      case 37:
	{
	    /* BEGINNING OF EXTRACT: arg-ignore */
	    {
#line 288 "syntax.act"

      ZIa=add_arg(arg_ignore,0);
#line 3703 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-ignore */
	    ADVANCE_LEXER;
	}
	break;
      case 35:
	{
	    argP ZIb;

	    /* BEGINNING OF EXTRACT: arg-nb-of-chars */
	    {
#line 280 "syntax.act"

      ZIb=add_arg(arg_nb_of_chars,0);
#line 3718 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: arg-nb-of-chars */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 603 "syntax.act"

	(ZIa) = add_none_arg();
#line 3727 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_sharp_arg_in_lhs */
	    {
#line 738 "syntax.act"

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
#line 3735 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_sharp_arg_in_lhs */
	}
	break;
      case 36:
	{
	    /* BEGINNING OF EXTRACT: arg-return-terminal */
	    {
#line 284 "syntax.act"

      ZIa=add_arg(arg_return_terminal,0);
#line 3747 "tmp.syntax.c"
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
#line 205 "syntax.act"

    ZIi = xstrcpy ( token_buff ) ;
#line 3762 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: identifier */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_from_identifier */
	    {
#line 599 "syntax.act"

	(ZIa) = add_identifier_arg ((ZIi));
#line 3771 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_from_identifier */
	}
	break;
      case 2:
	{
	    SID_STRING ZIb;

	    /* BEGINNING OF EXTRACT: string */
	    {
#line 250 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 3785 "tmp.syntax.c"
	    }
	    /* END OF EXTRACT: string */
	    ADVANCE_LEXER;
	    /* BEGINNING OF ACTION: make_arg_none */
	    {
#line 603 "syntax.act"

	(ZIa) = add_none_arg();
#line 3794 "tmp.syntax.c"
	    }
	    /* END OF ACTION: make_arg_none */
	    /* BEGINNING OF ACTION: E_string_arg_in_lhs */
	    {
#line 742 "syntax.act"

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
#line 3802 "tmp.syntax.c"
	    }
	    /* END OF ACTION: E_string_arg_in_lhs */
	}
	break;
      case 43:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (43);
    return;
  ZL0:;
    *ZOa = ZIa;
}

static void
ZR122(void)
{
    if ((CURRENT_TERMINAL) == 43) {
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
#line 730 "syntax.act"

	error(ERROR_SERIOUS, "Syntax error: expected equal \'=\'");
#line 3843 "tmp.syntax.c"
	}
	/* END OF ACTION: E_expected_equal */
    }
}

/* BEGINNING OF TRAILER */

#line 754 "syntax.act"

#line 3853 "tmp.syntax.c"

/* END OF FILE */
