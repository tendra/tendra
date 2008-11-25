/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */


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
#include "check/check.h"

#include "adt/instruction.h"
#include "adt/keyword.h"
#include "adt/zone.h"
#include "adt/tree.h"
#include "adt/char.h"

#include "adt.h"
#include "lexer.h"
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

typedef char *SID_STRING ;
typedef char *SID_CHARS ;
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
    COMPILATION MODE

    We allow unreached code in the automatically generated sections.
*/

#if FS_TENDRA
#pragma TenDRA begin
#ifndef OLD_PRODUCER
#pragma TenDRA unreachable code allow
#endif
#endif



/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRexpected__semicolon(void);
static void ZRzone_Hdefn(zoneP);
static void ZRstring_Hplus(SID_STRING *);
static void ZRtype_Hdefn(zoneP);
static void ZR148(void);
static void ZR149(void);
static void ZRaction_Hcall_C_Clhs_Htuple1(args_listP);
static void ZRtype_Htuple(zoneP, TypeTupleT *);
static void ZRaction_Hcall_C_Crhs_Htuple1(args_listP *);
static void ZR170(args_listP *);
static void ZRinstructions_Hlist(zoneP, instructions_listP *);
static void ZRtype_Htuple_C_Ctype_Hname(zoneP, TypeTupleT *);
static void ZRtrigraph_Hdefn(zoneP);
static void ZR190(SID_STRING *);
static void ZR192(zoneP *, instructions_listP *);
extern void read_lex(zoneP);
static void ZRaction_Hdecl(zoneP);
static void ZRinstruction(zoneP, instructionP *);
static void ZRcommand_Hlist(zoneP);
static void ZR214(zoneP, instructions_listP, zoneP *, instructions_listP *);
static void ZRkeyword_Hdefn(zoneP);
static void ZR216(zoneP *);
static void ZRcopyright_Hstmt(zoneP);
static void ZR217(zoneP *);
static void ZR218(zoneP *, args_listP *, instructionP *);
static void ZR222(zoneP *, args_listP *, SID_STRING *, instructionP *);
static void ZR223(argP *, args_listP *);
static void ZR225(zoneP *, TypeTupleT *);
static void ZRcommand(zoneP);
static void ZRtype_Htuple_C_Ctype_Htuple1(zoneP, TypeTupleT *);
static void ZRaction_Hcall_C_Crhs_Htuple(args_listP *);
static void ZRnon_Hempty_Hchars(SID_STRING *);
static void ZRaction_Hcall_C_Clhs_Harg(args_listP);
static void ZR123(void);
static void ZR125(void);
static void ZRaction_Hcall_C_Crhs_Harg(argP *);

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
		{

	error(ERROR_SERIOUS, "Syntax error: expected semicolon \';\'");
		}
	}
}

static void
ZRzone_Hdefn(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		SID_STRING ZIzid;
		SID_STRING ZIb;
		instructions_listP ZIentry_Hinstl;
		int ZIlendclosed;
		SID_STRING ZIe;
		instructions_listP ZIleaving_Hinstl;
		zoneP ZInew_Hzone;

		switch (CURRENT_TERMINAL) {
		case 13:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		{
			{
				switch (CURRENT_TERMINAL) {
				case 0:
					{

    ZIzid = xstrcpy ( token_buff ) ;
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

	(ZIzid)="";
	error(ERROR_SERIOUS, "Syntax error: expected identifier");
				}
			}
		ZL2:;
		}
		{
			{
				switch (CURRENT_TERMINAL) {
				case 23:
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

	error(ERROR_SERIOUS, "Syntax error: expected colon \':\'");
				}
			}
		ZL4:;
		}
		ZR190 (&ZIb);
		ZR192 (&ZIz, &ZIentry_Hinstl);
		{
			switch (CURRENT_TERMINAL) {
			case 25:
				{
					ADVANCE_LEXER;
					{
 (ZIlendclosed) = 1 ; 
					}
				}
				break;
			case 26:
				{
					ADVANCE_LEXER;
					{
 (ZIlendclosed) = 1 ; 
					}
				}
				break;
			case 27:
				{
					ADVANCE_LEXER;
					{
 (ZIlendclosed) = 0 ; 
					}
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
				{

	error(ERROR_SERIOUS, "Syntax error: expected range");
				}
				{
 (ZIlendclosed) = 0 ; 
				}
			}
		ZL6:;
		}
		ZR190 (&ZIe);
		ZR192 (&ZIz, &ZIleaving_Hinstl);
		if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		}
		{

    instruction* inst;
    instructions_list* inst_list;
    (ZInew_Hzone)=add_zone((ZIz),(ZIzid),(ZIe), (ZIlendclosed) );

    (ZInew_Hzone)->leaving_instructions=(ZIleaving_Hinstl);
    if((ZInew_Hzone)->leaving_instructions->nb_return_terminal)
	(ZInew_Hzone)->type= typezone_pseudo_token;
    (ZInew_Hzone)->entering_instructions=(ZIentry_Hinstl);
    if((ZInew_Hzone)->entering_instructions->nb_return_terminal)
	(ZInew_Hzone)->type=typezone_general_zone;
    inst=add_instruction_pushzone((ZInew_Hzone));
    inst_list=add_instructions_list();
    *(inst_list->tail)=inst;
    inst_list->tail=&(inst->next);
	add_mainpass((ZIz), (ZIb), inst_list);
		}
		switch (CURRENT_TERMINAL) {
		case 16:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRcommand_Hlist (ZInew_Hzone);
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
		{

	switch((ZInew_Hzone)->type) {
		case typezone_pseudo_token:
		case typezone_general_zone:
			(ZIz)->type = typezone_general_zone;
			break;
		case typezone_pure_function:
			break; //do nothing

	}
		}
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

		{
			switch (CURRENT_TERMINAL) {
			case 5:
				{
					{
 ZIa = "0123456789" ; 
					}
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					{
 ZIa = "abcdefghijklmnopqrstuvwxyz" ; 
					}
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					{

    ZIa = xstrcpy ( token_buff ) ;
					}
					ADVANCE_LEXER;
				}
				break;
			case 3:
				{
					{
 ZIa = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ; 
					}
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		{
			switch (CURRENT_TERMINAL) {
			case 21:
				{
					SID_STRING ZIb;

					ADVANCE_LEXER;
					ZRstring_Hplus (&ZIb);
					if ((CURRENT_TERMINAL) == 41) {
						RESTORE_LEXER;
						goto ZL1;
					}
					{

    (ZIs) = xstrcat ( (ZIa), (ZIb) ) ;
					}
				}
				break;
			default:
				{
					ZIs = ZIa;
				}
				break;
			}
		}
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
			{

    ZIs = xstrcpy ( token_buff ) ;
			}
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		{
			{
				{

   (ZI0) = tree_zoneisglobal((ZIz)->top_level, (ZIz));
				}
				if (!ZI0)
					goto ZL3;
				{

	NStringT str;
	nstring_copy_cstring(&str,(ZIs));
	xfree((ZIs));
	EntryT* entry;
	entry=table_get_entry(tree_get_table((ZIz)->top_level), &str);
	if(entry != NULL) {
		nstring_destroy(&str);
		/* TODO switch ? */
		if(entry_is_type(entry))
			error(ERROR_SERIOUS, "Type %s already exists",(ZIs));
		else if(entry_is_localname(entry))
			error(ERROR_SERIOUS, "Can't create type %s, %s has been previously used as a local name. We do not allow retroactive hiding.",(ZIs),(ZIs));
		else if(entry_is_action(entry))
			error(ERROR_SERIOUS, "Can't create type %s, %s has already been declared as an action",(ZIs), (ZIs));
		else
			UNREACHED;
	} else {
		table_add_type(tree_get_table((ZIz)->top_level), &str, false);
	}
				}
			}
			goto ZL2;
		ZL3:;
			{
				{

    error( ERROR_SERIOUS, "Syntax error: type %s should not be declared inside a zone",(ZIs)) ;
				}
			}
		ZL2:;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZR148(void)
{
	if ((CURRENT_TERMINAL) == 41) {
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
	}
	return;
ZL1:;
	{
		{

	error(ERROR_SERIOUS, "Syntax error: expected open \'(\'");
		}
	}
}

static void
ZR149(void)
{
	if ((CURRENT_TERMINAL) == 41) {
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

	error(ERROR_SERIOUS, "Syntax error: expected close \')\'");
		}
	}
}

static void
ZRaction_Hcall_C_Clhs_Htuple1(args_listP ZIl)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
ZL2_action_Hcall_C_Clhs_Htuple1:;
	{
		ZRaction_Hcall_C_Clhs_Harg (ZIl);
		{
			switch (CURRENT_TERMINAL) {
			case 28:
				{
					ADVANCE_LEXER;
					goto ZL2_action_Hcall_C_Clhs_Htuple1;
				}
				/*UNREACHED*/
			case 41:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
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
		{

	typetuple_init(&(ZIa));
		}
		ZR225 (&ZIz, &ZIa);
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
	{

	typetuple_assign(ZOa, (&ZIa));
	}
}

static void
ZRaction_Hcall_C_Crhs_Htuple1(args_listP *ZOr)
{
	args_listP ZIr;

	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		argP ZIa;

		ZRaction_Hcall_C_Crhs_Harg (&ZIa);
		ZR223 (&ZIa, &ZIr);
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
	*ZOr = ZIr;
}

static void
ZR170(args_listP *ZOr)
{
	args_listP ZIr;

	switch (CURRENT_TERMINAL) {
	case 14:
		{
			ZRaction_Hcall_C_Crhs_Htuple (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			{

    (ZIr)=add_args_list();
			}
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
	*ZOr = ZIr;
}

static void
ZRinstructions_Hlist(zoneP ZI208, instructions_listP *ZO213)
{
	instructions_listP ZI213;

	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		instructionP ZIinst;
		instructions_listP ZIinstl;
		zoneP ZI212;

		ZRinstruction (ZI208, &ZIinst);
		if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		}
		{

    (ZIinstl)=add_instructions_list();
		}
		{

	if((ZIinst)!=NULL) { /* if (ZIinst) == NULL, an error has already been issued.*/
		LocalNamesT* locals = instructionslist_localnames((ZIinstl));
/*		if(((ZIinstl)->head !=NULL) && ((ZIinst)->type==return_terminal || (ZIinst)->type==do_nothing)) {
			error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an instruction-list"); Does not work anymore since we append and do not prepend anymore. No pb as this will be unecessary due to the upcoming removal of direct function calls.
		}*/
		if((ZIinstl)->nb_return_terminal>0 && (ZIinst)->type!=do_nothing)
			error(ERROR_SERIOUS, "No instruction may follow an instruction that returns a terminal");
		if((ZIinst)->type == return_terminal) {
			++((ZIinstl)->nb_return_terminal);
		}
		if((ZIinst)->type == action_call) {
			(ZIinstl)->nb_return_terminal+=(ZIinst)->u.act.lhs->nb_return_terminal;
			if((ZIinstl)->nb_return_terminal>1)
				error(ERROR_SERIOUS, "Only one terminal may be returned per token");
			EntryT* entryaction = (ZIinst)->u.act.called_act;
			ActionT* action = entry_get_action(entryaction);
			args_list* rhs = (ZIinst)->u.act.rhs;
			args_list* lhs = (ZIinst)->u.act.lhs;

			arg* p;
			TypeTupleEntryT* q;

			/* CHECKING RHS COMPATIBILITY */ 
			for ( p = rhs->head, q = action->inputs.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
			      	EntryT* entrytype = NULL;
				NStringT str;
			      	switch (p->type) {
				case arg_identifier: 
				     	nstring_copy_cstring(&str, p->u.literal);
					entrytype=localnames_get_type(locals, &str);
					nstring_destroy(&str);
					if(!entrytype) {
						EntryT* tableentry = table_get_entry(tree_get_table((ZI208)->top_level), &str);
						if(!tableentry) {
							error(ERROR_SERIOUS, "local name %s has not been defined yet", p->u.literal);
							entrytype = NULL;
						} else if (entry_is_localname(tableentry)) {
							error(ERROR_SERIOUS, "local name %s has been defined but not in this scope", p->u.literal);
							entrytype = NULL;
						} else if (entry_is_action(tableentry)) {
							error(ERROR_SERIOUS, "%s is not a local name but an action which is not allowed", p->u.literal);
							entrytype = NULL;
						} else if (entry_is_type(tableentry)) {
							error(ERROR_SERIOUS, "%s is not a local name but a type which is not allowed", p->u.literal);
							entrytype = NULL;
						} else {
							UNREACHED;
						}
					}
					break;
				case arg_charP:
					/* TODO assert(lexer_string_type(top_level)) */
					entrytype = lexer_string_type((ZI208)->top_level);
		 			break;
				case arg_char_nb:
					/* TODO assert(lexer_char_type(top_level)) */
					entrytype = lexer_char_type((ZI208)->top_level);
			 		break;
				case arg_terminal:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_terminal_type((ZI208)->top_level);
					break;
				case arg_nb_of_chars:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_int_type((ZI208)->top_level);
		 			break;
				case arg_none:
					break; //Error already detected, do nothing and leave p->lexitype = NULL
				case arg_chars_list:
				case arg_ignore:
				case arg_return_terminal:
					UNREACHED;
				break;
			default:
				UNREACHED;
				break;
			}
			if(entrytype) {
				if( q->type!=entrytype || p->is_reference!=q->is_reference) {
						char* s1 = nstring_to_cstring(entry_key(entryaction));
						char* s2 = nstring_to_cstring(entry_key(entrytype));
						char* s3 = p->is_reference ? "&" : "";
						char* s4 = nstring_to_cstring(entry_key(q->type));
						char* s5 = q->is_reference ? "&" : "";
						error(ERROR_SERIOUS, "In call to action %s, argument \'%s\' has type \'%s%s\' when it should have type %s", s1, p->u.literal, s2, s3, s4, s5);
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
						nstring_copy_cstring(&str, p->u.literal);
						entrytype = localnames_get_type(locals, &str);
						if(!entrytype) {
							EntryT* entry = table_get_entry(tree_get_table((ZI208)->top_level), &str);
							localnames_add_nstring(locals, &str, q->type);
							if(entry) {
								nstring_destroy(&str);
								if (entry_is_action(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.literal);
								} else if (entry_is_type(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.literal);									
								}
							} else {
								table_add_local_name(tree_get_table((ZI208)->top_level), &str);
							}
							if(p->is_reference) {
								char* s = nstring_to_cstring(entry_key(entryaction));
								error(ERROR_SERIOUS, "In action call %s, you can only use references %s for preexisting variables", s, p->u.literal);
								DEALLOCATE(s);
							} 
						} else {
							nstring_destroy(&str);
							if(!p->is_reference) {
								char* s = nstring_to_cstring(entry_key(entryaction));
								error(ERROR_SERIOUS, "In action call %s, name %s already declared. Use references to change the value of an already existing variable", s, p->u.literal);
								entrytype=q->type; /* To avoid outputting that error more than once*/
								DEALLOCATE(s);
							}
						}
					}
					break;
				case arg_return_terminal:
					entrytype = lexer_terminal_type((ZI208)->top_level);
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
					/* XXX: state which action */
					if(p->is_reference)
						error(ERROR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
					else
						error(ERROR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
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
		*(ZIinstl)->tail=(ZIinst);
		(ZIinstl)->tail=&(ZIinst)->next;
		++((ZIinstl)->size);
	}
		}
		ZR214 (ZI208, ZIinstl, &ZI212, &ZI213);
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
	*ZO213 = ZI213;
}

static void
ZRtype_Htuple_C_Ctype_Hname(zoneP ZIz, TypeTupleT *ZIa)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		SID_STRING ZIname;
		SID_STRING ZItype;
		int ZIisref;

		{
			switch (CURRENT_TERMINAL) {
			case 0:
				{
					{

    ZIname = xstrcpy ( token_buff ) ;
					}
					ADVANCE_LEXER;
				}
				break;
			default:
				{
					{

    (ZIname) = xstrcpy("");
					}
				}
				break;
			}
		}
		switch (CURRENT_TERMINAL) {
		case 23:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 0:
			{

    ZItype = xstrcpy ( token_buff ) ;
			}
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		{
			switch (CURRENT_TERMINAL) {
			case 24:
				{
					ADVANCE_LEXER;
					{
 (ZIisref) = 1 ; 
					}
				}
				break;
			default:
				{
					{
 (ZIisref) = 0 ; 
					}
				}
				break;
			}
		}
		{

	NStringT tstr, istr;
	nstring_copy_cstring(&tstr,(ZItype));
	nstring_copy_cstring(&istr,(ZIname));
	EntryT* entry = table_get_entry(tree_get_table((ZIz)->top_level), &tstr);
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
		}
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZRtrigraph_Hdefn(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		SID_STRING ZIs;
		SID_STRING ZIt;

		switch (CURRENT_TERMINAL) {
		case 9:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRstring_Hplus (&ZIs);
		ZR125 ();
		ZRstring_Hplus (&ZIt);
		if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		}
		{

	assert((ZIz) != NULL);
	assert((ZIs) != NULL);
	assert((ZIt) != NULL);

	add_prepass((ZIz), (ZIs), (ZIt));
		}
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZR190(SID_STRING *ZOe)
{
	SID_STRING ZIe;

	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		ZRnon_Hempty_Hchars (&ZIe);
		if ((CURRENT_TERMINAL) == 41) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	{
		{

        (ZIe) = NULL ;
	error(ERROR_SERIOUS, "Syntax error: expected characters");
		}
	}
ZL0:;
	*ZOe = ZIe;
}

static void
ZR192(zoneP *ZIz, instructions_listP *ZOleaving_Hinstl)
{
	instructions_listP ZIleaving_Hinstl;

	switch (CURRENT_TERMINAL) {
	case 18:
		{
			ADVANCE_LEXER;
			ZRinstructions_Hlist (*ZIz, &ZIleaving_Hinstl);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			{

    (ZIleaving_Hinstl)=add_instructions_list();
			}
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

void
read_lex(zoneP ZIz)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		ZRcommand_Hlist (ZIz);
		{
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
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

	error ( ERROR_SERIOUS, "Syntax error" ) ;
				}
			}
		ZL2:;
		}
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
		{
			{
				switch (CURRENT_TERMINAL) {
				case 38:
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

	error(ERROR_SERIOUS, "Syntax error: expected begin action \'<\'");
				}
			}
		ZL2:;
		}
		switch (CURRENT_TERMINAL) {
		case 0:
			{

    ZIi = xstrcpy ( token_buff ) ;
			}
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		{
			{
				switch (CURRENT_TERMINAL) {
				case 39:
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

	error(ERROR_SERIOUS, "Syntax error: expected end action \'>\'");
				}
			}
		ZL4:;
		}
		{
			switch (CURRENT_TERMINAL) {
			case 23:
				{
					ADVANCE_LEXER;
					ZR148 ();
					ZRtype_Htuple (ZIz, &ZIit);
					ZR149 ();
					ZR125 ();
					ZR148 ();
					ZRtype_Htuple (ZIz, &ZIot);
					ZR149 ();
					if ((CURRENT_TERMINAL) == 41) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					{

	typetuple_init(&(ZIit));
					}
					{

	typetuple_init(&(ZIot));
					}
				}
				break;
			}
		}
		{

	NStringT str;
	nstring_copy_cstring(&str, (ZIi));
	EntryT* entry;
	entry=table_get_entry(tree_get_table((ZIz)->top_level), &str);
	if(entry != NULL) {
		nstring_destroy(&str);
		/* TODO switch ? */
	   	if(entry_is_action(entry))
			error(ERROR_SERIOUS, "Action %s already exists",(ZIi));
		else if(entry_is_localname(entry))
			error(ERROR_SERIOUS, "Can't create type %s, %s has been previously used as a local name. We do not allow retroactive hiding.",(ZIi),(ZIi));
		else if(entry_is_type(entry))
			error(ERROR_SERIOUS, "Can't create action %s, %s has already been declared as a type",(ZIi), (ZIi));
		else
			UNREACHED;
	} else {
		table_add_action(tree_get_table((ZIz)->top_level), &str , (&ZIit), (&ZIot));
	}
	xfree((ZIi));
		}
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZRinstruction(zoneP ZIz, instructionP *ZOinst)
{
	instructionP ZIinst;

	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		args_listP ZIl;

		{

    (ZIl)=add_args_list();
		}
		ZR218 (&ZIz, &ZIl, &ZIinst);
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
	*ZOinst = ZIinst;
}

static void
ZRcommand_Hlist(zoneP ZIz)
{
ZL2_command_Hlist:;
	switch (CURRENT_TERMINAL) {
	case 6: case 7: case 8: case 9:
	case 10: case 13: case 16: case 22:
	case 37: case 40:
		{
			ZRcommand (ZIz);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_command_Hlist;
			}
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
		{

	error ( ERROR_SERIOUS, "Syntax error" ) ;
		}
	}
}

static void
ZR214(zoneP ZI208, instructions_listP ZI211, zoneP *ZO212, instructions_listP *ZO213)
{
	zoneP ZI212;
	instructions_listP ZI213;

ZL2_214:;
	switch (CURRENT_TERMINAL) {
	case 28:
		{
			instructions_listP ZIinstl;
			instructionP ZIinst;

			ZIinstl = ZI211;
			ADVANCE_LEXER;
			ZRinstruction (ZI208, &ZIinst);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

	if((ZIinst)!=NULL) { /* if (ZIinst) == NULL, an error has already been issued.*/
		LocalNamesT* locals = instructionslist_localnames((ZIinstl));
/*		if(((ZIinstl)->head !=NULL) && ((ZIinst)->type==return_terminal || (ZIinst)->type==do_nothing)) {
			error(ERROR_SERIOUS, "A $sid-identifier or a $$ can only appear at the end of an instruction-list"); Does not work anymore since we append and do not prepend anymore. No pb as this will be unecessary due to the upcoming removal of direct function calls.
		}*/
		if((ZIinstl)->nb_return_terminal>0 && (ZIinst)->type!=do_nothing)
			error(ERROR_SERIOUS, "No instruction may follow an instruction that returns a terminal");
		if((ZIinst)->type == return_terminal) {
			++((ZIinstl)->nb_return_terminal);
		}
		if((ZIinst)->type == action_call) {
			(ZIinstl)->nb_return_terminal+=(ZIinst)->u.act.lhs->nb_return_terminal;
			if((ZIinstl)->nb_return_terminal>1)
				error(ERROR_SERIOUS, "Only one terminal may be returned per token");
			EntryT* entryaction = (ZIinst)->u.act.called_act;
			ActionT* action = entry_get_action(entryaction);
			args_list* rhs = (ZIinst)->u.act.rhs;
			args_list* lhs = (ZIinst)->u.act.lhs;

			arg* p;
			TypeTupleEntryT* q;

			/* CHECKING RHS COMPATIBILITY */ 
			for ( p = rhs->head, q = action->inputs.head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
			      	EntryT* entrytype = NULL;
				NStringT str;
			      	switch (p->type) {
				case arg_identifier: 
				     	nstring_copy_cstring(&str, p->u.literal);
					entrytype=localnames_get_type(locals, &str);
					nstring_destroy(&str);
					if(!entrytype) {
						EntryT* tableentry = table_get_entry(tree_get_table((ZI208)->top_level), &str);
						if(!tableentry) {
							error(ERROR_SERIOUS, "local name %s has not been defined yet", p->u.literal);
							entrytype = NULL;
						} else if (entry_is_localname(tableentry)) {
							error(ERROR_SERIOUS, "local name %s has been defined but not in this scope", p->u.literal);
							entrytype = NULL;
						} else if (entry_is_action(tableentry)) {
							error(ERROR_SERIOUS, "%s is not a local name but an action which is not allowed", p->u.literal);
							entrytype = NULL;
						} else if (entry_is_type(tableentry)) {
							error(ERROR_SERIOUS, "%s is not a local name but a type which is not allowed", p->u.literal);
							entrytype = NULL;
						} else {
							UNREACHED;
						}
					}
					break;
				case arg_charP:
					/* TODO assert(lexer_string_type(top_level)) */
					entrytype = lexer_string_type((ZI208)->top_level);
		 			break;
				case arg_char_nb:
					/* TODO assert(lexer_char_type(top_level)) */
					entrytype = lexer_char_type((ZI208)->top_level);
			 		break;
				case arg_terminal:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_terminal_type((ZI208)->top_level);
					break;
				case arg_nb_of_chars:
					/* TODO assert(lexer_terminal_type(top_level)) */
					entrytype = lexer_int_type((ZI208)->top_level);
		 			break;
				case arg_none:
					break; //Error already detected, do nothing and leave p->lexitype = NULL
				case arg_chars_list:
				case arg_ignore:
				case arg_return_terminal:
					UNREACHED;
				break;
			default:
				UNREACHED;
				break;
			}
			if(entrytype) {
				if( q->type!=entrytype || p->is_reference!=q->is_reference) {
						char* s1 = nstring_to_cstring(entry_key(entryaction));
						char* s2 = nstring_to_cstring(entry_key(entrytype));
						char* s3 = p->is_reference ? "&" : "";
						char* s4 = nstring_to_cstring(entry_key(q->type));
						char* s5 = q->is_reference ? "&" : "";
						error(ERROR_SERIOUS, "In call to action %s, argument \'%s\' has type \'%s%s\' when it should have type %s", s1, p->u.literal, s2, s3, s4, s5);
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
						nstring_copy_cstring(&str, p->u.literal);
						entrytype = localnames_get_type(locals, &str);
						if(!entrytype) {
							EntryT* entry = table_get_entry(tree_get_table((ZI208)->top_level), &str);
							localnames_add_nstring(locals, &str, q->type);
							if(entry) {
								nstring_destroy(&str);
								if (entry_is_action(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is an action. Hiding globals by local names is not allowed", p->u.literal);
								} else if (entry_is_type(entry)) {
									error(ERROR_SERIOUS, "In action lhs. Name %s is a type. Hiding globals by local names is not allowed", p->u.literal);									
								}
							} else {
								table_add_local_name(tree_get_table((ZI208)->top_level), &str);
							}
							if(p->is_reference) {
								char* s = nstring_to_cstring(entry_key(entryaction));
								error(ERROR_SERIOUS, "In action call %s, you can only use references %s for preexisting variables", s, p->u.literal);
								DEALLOCATE(s);
							} 
						} else {
							nstring_destroy(&str);
							if(!p->is_reference) {
								char* s = nstring_to_cstring(entry_key(entryaction));
								error(ERROR_SERIOUS, "In action call %s, name %s already declared. Use references to change the value of an already existing variable", s, p->u.literal);
								entrytype=q->type; /* To avoid outputting that error more than once*/
								DEALLOCATE(s);
							}
						}
					}
					break;
				case arg_return_terminal:
					entrytype = lexer_terminal_type((ZI208)->top_level);
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
					/* XXX: state which action */
					if(p->is_reference)
						error(ERROR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
					else
						error(ERROR_SERIOUS, "In call to action, %s should not be a reference", p->u.literal);
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
		*(ZIinstl)->tail=(ZIinst);
		(ZIinstl)->tail=&(ZIinst)->next;
		++((ZIinstl)->size);
	}
			}
			ZI211 = ZIinstl;
			goto ZL2_214;
		}
		/*UNREACHED*/
	default:
		{
			ZI212 = ZI208;
			ZI213 = ZI211;
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
	*ZO212 = ZI212;
	*ZO213 = ZI213;
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
			{

    ZIs = xstrcpy ( token_buff ) ;
			}
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 18:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRinstruction (ZIz, &ZIinst);
		{
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				{

   (ZI0) = tree_zoneisglobal((ZIz)->top_level, (ZIz));
				}
				if (!ZI0)
					goto ZL3;
				{

    switch((ZIinst)->type) {
    case return_terminal: 
    /* Fallback is intentional */
      add_keyword ( (ZIz), (ZIs), (ZIinst) ) ;
    break;
    default:
      error(ERROR_SERIOUS, "Syntax error: only a function or a token might be returned for a keyword");
  }
				}
			}
			goto ZL2;
		ZL3:;
			{
				{

    error( ERROR_SERIOUS, "Keywords not yet implemented in a non global zone ") ;

				}
			}
		ZL2:;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZR216(zoneP *ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 0:
		{
			SID_STRING ZIi;
			SID_STRING ZIs;

			{

    ZIi = xstrcpy ( token_buff ) ;
			}
			ADVANCE_LEXER;
			ZR123 ();
			ZRnon_Hempty_Hchars (&ZIs);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

    make_group ( (*ZIz), (ZIi), (ZIs) ) ;
			}
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 11:
		{
			SID_STRING ZIs;

			ADVANCE_LEXER;
			ZR123 ();
			ZRstring_Hplus (&ZIs);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

    if ( (*ZIz)->white_space) {
	error ( ERROR_SERIOUS, "White space group already defined" ) ;
    }
    (*ZIz)->white_space= make_group((*ZIz),"white",(ZIs)) ;
			}
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
		case 20:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 2:
			{

    ZIs = xstrcpy ( token_buff ) ;
			}
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		{
			{
				{

   (ZI0) = tree_zoneisglobal((ZIz)->top_level, (ZIz));
				}
				if (!ZI0)
					goto ZL3;
				{

	FILE *file=fopen((ZIs),"r");
	if(file) {
		tree_add_copyright_file((ZIz)->top_level, file, (ZIs));
	} else {
		error(ERROR_SERIOUS, "Syntax error: unable to open copright file %s", (ZIs)) ;
	}
				}
			}
			goto ZL2;
		ZL3:;
			{
				{

    error( ERROR_SERIOUS, "Syntax error: A copyright file may only be specified in the global zone") ;
				}
			}
		ZL2:;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZR217(zoneP *ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 12:
		{
			instructions_listP ZIinst_Hlist;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 18:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRinstructions_Hlist (*ZIz, &ZIinst_Hlist);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

    (*ZIz)->default_instructions=(ZIinst_Hlist);
			}
			ZRexpected__semicolon ();
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2: case 3: case 4: case 5:
		{
			SID_STRING ZIs;
			instructions_listP ZIinst_Hlist;

			ZRnon_Hempty_Hchars (&ZIs);
			switch (CURRENT_TERMINAL) {
			case 18:
				break;
			case 41:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRinstructions_Hlist (*ZIz, &ZIinst_Hlist);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

	if((ZIinst_Hlist)->nb_return_terminal>1)
		error(ERROR_SERIOUS, "At most one return terminal may be specified per instruction list");
			}
			{

	add_mainpass((*ZIz), (ZIs), (ZIinst_Hlist));
	if((ZIinst_Hlist)->nb_return_terminal)
		(*ZIz)->type=typezone_general_zone;
			}
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
ZR218(zoneP *ZIz, args_listP *ZIl, instructionP *ZOinst)
{
	instructionP ZIinst;

	switch (CURRENT_TERMINAL) {
	case 31:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			{

      ZIb=add_arg(arg_chars_list,0);
			}
			ADVANCE_LEXER;
			{

	(ZIa) = add_none_arg();
			}
			{

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
			}
			{

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
			}
			switch (CURRENT_TERMINAL) {
			case 20:
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
				{

    ZIi = xstrcpy ( token_buff ) ;
				}
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			{

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
			}
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR170 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
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
			}
		}
		break;
	case 33:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			{

      ZIb=add_arg(arg_char_nb,number_buffer);
			}
			ADVANCE_LEXER;
			{

	(ZIa) = add_none_arg();
			}
			{

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
			}
			{

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
			}
			switch (CURRENT_TERMINAL) {
			case 20:
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
				{

    ZIi = xstrcpy ( token_buff ) ;
				}
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			{

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
			}
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR170 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
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
			}
		}
		break;
	case 32:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			{

      ZIb=add_arg(arg_charP,0);
			}
			ADVANCE_LEXER;
			{

	(ZIa) = add_none_arg();
			}
			{

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
			}
			{

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
			}
			switch (CURRENT_TERMINAL) {
			case 20:
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
				{

    ZIi = xstrcpy ( token_buff ) ;
				}
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			{

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
			}
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR170 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
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
			}
		}
		break;
	case 36:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			{

      ZIa=add_arg(arg_ignore,0);
			}
			ADVANCE_LEXER;
			{

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
			}
			switch (CURRENT_TERMINAL) {
			case 20:
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
				{

    ZIi = xstrcpy ( token_buff ) ;
				}
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			{

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
			}
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR170 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
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
			}
		}
		break;
	case 34:
		{
			argP ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			{

      ZIb=add_arg(arg_nb_of_chars,0);
			}
			ADVANCE_LEXER;
			{

	(ZIa) = add_none_arg();
			}
			{

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
			}
			{

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
			}
			switch (CURRENT_TERMINAL) {
			case 20:
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
				{

    ZIi = xstrcpy ( token_buff ) ;
				}
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			{

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
			}
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR170 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
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
			}
		}
		break;
	case 35:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			{

      ZIa=add_arg(arg_return_terminal,0);
			}
			ADVANCE_LEXER;
			{

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
			}
			switch (CURRENT_TERMINAL) {
			case 20:
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
				{

    ZIi = xstrcpy ( token_buff ) ;
				}
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			{

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
			}
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR170 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
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
			}
		}
		break;
	case 38:
		{
			SID_STRING ZIi;
			args_listP ZIr;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				{

    ZIi = xstrcpy ( token_buff ) ;
				}
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			{

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
			}
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR170 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
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
			}
		}
		break;
	case 0:
		{
			SID_STRING ZI219;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			{

    ZI219 = xstrcpy ( token_buff ) ;
			}
			ADVANCE_LEXER;
			{

	(ZIa) = add_identifier_arg ((ZI219));
			}
			{

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
			}
			switch (CURRENT_TERMINAL) {
			case 20:
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
				{

    ZIi = xstrcpy ( token_buff ) ;
				}
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			{

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
			}
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR170 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
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
			}
		}
		break;
	case 29:
		{
			ADVANCE_LEXER;
			{

	(ZIinst)=add_instruction_donothing();
			}
		}
		break;
	case 14:
		{
			SID_STRING ZIi;
			args_listP ZIr;

			ADVANCE_LEXER;
			ZRaction_Hcall_C_Clhs_Htuple1 (*ZIl);
			switch (CURRENT_TERMINAL) {
			case 15:
				break;
			case 41:
				RESTORE_LEXER;
				goto ZL1;
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
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				{

    ZIi = xstrcpy ( token_buff ) ;
				}
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			{

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
			}
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR170 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
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
			}
		}
		break;
	case 24:
		{
			SID_STRING ZI220;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				{

    ZI220 = xstrcpy ( token_buff ) ;
				}
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			{

	(ZIa) = add_reference_arg ((ZI220));
			}
			{

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
			}
			switch (CURRENT_TERMINAL) {
			case 20:
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
				{

    ZIi = xstrcpy ( token_buff ) ;
				}
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			{

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
			}
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR170 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
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
			}
		}
		break;
	case 1:
		{
			SID_STRING ZI221;

			{

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
    ZI221 = xstrcpy ( buff ) ;
			}
			ADVANCE_LEXER;
			ZR222 (ZIz, ZIl, &ZI221, &ZIinst);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 2:
		{
			SID_STRING ZIb;
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			{

    ZIb = xstrcpy ( token_buff ) ;
			}
			ADVANCE_LEXER;
			{

	(ZIa) = add_none_arg();
			}
			{

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
			}
			{

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
			}
			switch (CURRENT_TERMINAL) {
			case 20:
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
				{

    ZIi = xstrcpy ( token_buff ) ;
				}
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			{

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
			}
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR170 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
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
			}
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
ZR222(zoneP *ZIz, args_listP *ZIl, SID_STRING *ZI221, instructionP *ZOinst)
{
	instructionP ZIinst;

	switch (CURRENT_TERMINAL) {
	default:
		{
			{

        (ZIinst)=add_instruction_return_terminal((*ZI221));
			}
		}
		break;
	case 20:
		{
			argP ZIa;
			SID_STRING ZIi;
			args_listP ZIr;

			{

	(ZIa) = add_none_arg();
			}
			{

	error(ERROR_SERIOUS, "Terminal argument in left handside");
			}
			{

    *(*ZIl)->tail=(ZIa);
    (*ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(*ZIl)->nb_return_terminal++;
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
				{

    ZIi = xstrcpy ( token_buff ) ;
				}
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			{

    if((*ZIl)->nb_return_terminal>1)
	error(ERROR_SERIOUS, "There can only be one return terminal argument per action lhs");
			}
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZR170 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

	NStringT key;
	nstring_copy_cstring(&key, (ZIi));
	EntryT* entry = table_get_entry(tree_get_table((*ZIz)->top_level), &key);
	if(entry) {
		if(entry_is_action(entry)) {
			/* TODO: Inefficient code follows: */
			/* Checking that a name does not appear twice in an lhs*/
			arg* p, *q;
			for(p=(*ZIl)->head;p!=NULL;p=p->next) {
				if(p->type==arg_identifier) {
					for(q=p->next; q!=NULL;q=q->next) {
						if(q->type==arg_identifier && !strcmp(p->u.literal, q->u.literal)) {
							char* s = nstring_to_cstring(entry_key(entry));
							error(ERROR_SERIOUS, "In call to action %s, the left hand side contain multiple reference to %s",s, p->u.literal);
							break;		   
						}
					}
				}
			}
			(ZIinst)=add_instruction_action(entry,(*ZIl),(ZIr));
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
			}
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

static void
ZR223(argP *ZIa, args_listP *ZOr)
{
	args_listP ZIr;

	switch (CURRENT_TERMINAL) {
	case 28:
		{
			ADVANCE_LEXER;
			ZRaction_Hcall_C_Crhs_Htuple1 (&ZIr);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{

    (*ZIa)->next=(ZIr)->head;
    (ZIr)->head=(*ZIa);
    if((*ZIa)->type==arg_return_terminal)
	(ZIr)->nb_return_terminal++;
			}
		}
		break;
	default:
		{
			{

    (ZIr)=add_args_list();
			}
			{

    (*ZIa)->next=(ZIr)->head;
    (ZIr)->head=(*ZIa);
    if((*ZIa)->type==arg_return_terminal)
	(ZIr)->nb_return_terminal++;
			}
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
	*ZOr = ZIr;
}

static void
ZR225(zoneP *ZIz, TypeTupleT *ZIa)
{
	switch (CURRENT_TERMINAL) {
	case 0: case 23:
		{
			ZRtype_Htuple_C_Ctype_Htuple1 (*ZIz, ZIa);
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
ZRcommand(zoneP ZIz)
{
	switch (CURRENT_TERMINAL) {
	case 7:
		{
			ADVANCE_LEXER;
			ZR216 (&ZIz);
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 16:
		{
			ADVANCE_LEXER;
			ZRcommand_Hlist (ZIz);
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
	case 22:
		{
			ADVANCE_LEXER;
		}
		break;
	case 10:
		{
			ADVANCE_LEXER;
			ZR217 (&ZIz);
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
ZRtype_Htuple_C_Ctype_Htuple1(zoneP ZIz, TypeTupleT *ZIa)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
ZL2_type_Htuple_C_Ctype_Htuple1:;
	{
		ZRtype_Htuple_C_Ctype_Hname (ZIz, ZIa);
		{
			switch (CURRENT_TERMINAL) {
			case 28:
				{
					ADVANCE_LEXER;
					goto ZL2_type_Htuple_C_Ctype_Htuple1;
				}
				/*UNREACHED*/
			case 41:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZRaction_Hcall_C_Crhs_Htuple(args_listP *ZOr)
{
	args_listP ZIr;

	if ((CURRENT_TERMINAL) == 41) {
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
			switch (CURRENT_TERMINAL) {
			case 0: case 1: case 2: case 24:
			case 31: case 32: case 33: case 34:
			case 35: case 36:
				{
					ZRaction_Hcall_C_Crhs_Htuple1 (&ZIr);
					if ((CURRENT_TERMINAL) == 41) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					{

    (ZIr)=add_args_list();
					}
				}
				break;
			}
		}
		switch (CURRENT_TERMINAL) {
		case 15:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZOr = ZIr;
}

static void
ZRnon_Hempty_Hchars(SID_STRING *ZOs)
{
	SID_STRING ZIs;

	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		ZRstring_Hplus (&ZIs);
		{
			if ((CURRENT_TERMINAL) == 41) {
				RESTORE_LEXER;
				goto ZL1;
			}
			{
				{

	(ZI0) = strlen((ZIs)) > 0;
				}
				if (!ZI0)
					goto ZL3;
			}
			goto ZL2;
		ZL3:;
			{
				{

        error(ERROR_SERIOUS, "Empty character string is not allowed here, try using DEFAULT instead");	
				}
			}
		ZL2:;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (41);
	return;
ZL0:;
	*ZOs = ZIs;
}

static void
ZRaction_Hcall_C_Clhs_Harg(args_listP ZIl)
{
	if ((CURRENT_TERMINAL) == 41) {
		return;
	}
	{
		argP ZIa;

		{
			switch (CURRENT_TERMINAL) {
			case 31:
				{
					argP ZIb;

					{

      ZIb=add_arg(arg_chars_list,0);
					}
					ADVANCE_LEXER;
					{

	(ZIa) = add_none_arg();
					}
					{

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
					}
				}
				break;
			case 33:
				{
					argP ZIb;

					{

      ZIb=add_arg(arg_char_nb,number_buffer);
					}
					ADVANCE_LEXER;
					{

	(ZIa) = add_none_arg();
					}
					{

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
					}
				}
				break;
			case 32:
				{
					argP ZIb;

					{

      ZIb=add_arg(arg_charP,0);
					}
					ADVANCE_LEXER;
					{

	(ZIa) = add_none_arg();
					}
					{

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
					}
				}
				break;
			case 36:
				{
					{

      ZIa=add_arg(arg_ignore,0);
					}
					ADVANCE_LEXER;
				}
				break;
			case 34:
				{
					argP ZIb;

					{

      ZIb=add_arg(arg_nb_of_chars,0);
					}
					ADVANCE_LEXER;
					{

	(ZIa) = add_none_arg();
					}
					{

	error(ERROR_SERIOUS, "Argument of style # are rvalues and should not appear on a left handside");
					}
				}
				break;
			case 35:
				{
					{

      ZIa=add_arg(arg_return_terminal,0);
					}
					ADVANCE_LEXER;
				}
				break;
			case 0:
				{
					SID_STRING ZIi;

					{

    ZIi = xstrcpy ( token_buff ) ;
					}
					ADVANCE_LEXER;
					{

	(ZIa) = add_identifier_arg ((ZIi));
					}
				}
				break;
			case 24:
				{
					SID_STRING ZIi;

					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 0:
						{

    ZIi = xstrcpy ( token_buff ) ;
						}
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					{

	(ZIa) = add_reference_arg ((ZIi));
					}
				}
				break;
			case 1:
				{
					SID_STRING ZIb;

					{

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
					}
					ADVANCE_LEXER;
					{

	(ZIa) = add_none_arg();
					}
					{

	error(ERROR_SERIOUS, "Terminal argument in left handside");
					}
				}
				break;
			case 2:
				{
					SID_STRING ZIb;

					{

    ZIb = xstrcpy ( token_buff ) ;
					}
					ADVANCE_LEXER;
					{

	(ZIa) = add_none_arg();
					}
					{

	error(ERROR_SERIOUS, "Argument of type "" are rvalues and should not appear on a left handside");
					}
				}
				break;
			default:
				goto ZL1;
			}
		}
		{

    *(ZIl)->tail=(ZIa);
    (ZIl)->tail=&(ZIa)->next;
    if((ZIa)->type==arg_return_terminal)
	(ZIl)->nb_return_terminal++;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (41);
	return;
}

static void
ZR123(void)
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
		{

	error(ERROR_SERIOUS, "Syntax error: expected equal \'=\'");
		}
	}
}

static void
ZR125(void)
{
	if ((CURRENT_TERMINAL) == 41) {
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

	error(ERROR_SERIOUS, "Syntax error: expected arrow \'->\'");
		}
	}
}

static void
ZRaction_Hcall_C_Crhs_Harg(argP *ZOa)
{
	argP ZIa;

	switch (CURRENT_TERMINAL) {
	case 31:
		{
			argP ZIb;

			{

      ZIb=add_arg(arg_chars_list,0);
			}
			ADVANCE_LEXER;
			{

	(ZIa) = add_none_arg();
			}
			{

	error(ERROR_SERIOUS, "Args of style ## are not implemented in actions right hand side. Whether they will be implemented in the future remains undecided at the moment.");
/* TODO take a decision.*/
			}
		}
		break;
	case 33:
		{
			{

      ZIa=add_arg(arg_char_nb,number_buffer);
			}
			ADVANCE_LEXER;
		}
		break;
	case 32:
		{
			{

      ZIa=add_arg(arg_charP,0);
			}
			ADVANCE_LEXER;
		}
		break;
	case 36:
		{
			argP ZIb;

			{

      ZIb=add_arg(arg_ignore,0);
			}
			ADVANCE_LEXER;
			{

	(ZIa) = add_none_arg();
			}
			{

	error(ERROR_SERIOUS, "Ignore argument in right handside");
			}
		}
		break;
	case 34:
		{
			{

      ZIa=add_arg(arg_nb_of_chars,0);
			}
			ADVANCE_LEXER;
		}
		break;
	case 35:
		{
			argP ZIb;

			{

      ZIb=add_arg(arg_return_terminal,0);
			}
			ADVANCE_LEXER;
			{

	(ZIa) = add_none_arg();
			}
			{

	error(ERROR_SERIOUS, "Return terminal argument in right handside");
			}
		}
		break;
	case 0:
		{
			SID_STRING ZIi;

			{

    ZIi = xstrcpy ( token_buff ) ;
			}
			ADVANCE_LEXER;
			{

	(ZIa) = add_identifier_arg ((ZIi));
			}
		}
		break;
	case 24:
		{
			SID_STRING ZIi;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				{

    ZIi = xstrcpy ( token_buff ) ;
				}
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			{

	(ZIa) = add_reference_arg ((ZIi));
			}
		}
		break;
	case 1:
		{
			SID_STRING ZIb;

			{

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
			}
			ADVANCE_LEXER;
			{

	(ZIa) = add_terminal_arg ((ZIb));
			}
		}
		break;
	case 2:
		{
			SID_STRING ZIb;

			{

    ZIb = xstrcpy ( token_buff ) ;
			}
			ADVANCE_LEXER;
			{

	(ZIa) = add_none_arg();
			}
			{

	error(ERROR_SERIOUS, "String argument in right handside of action call: purposefuly not implemented to avoid confusions. Will be implemented with an alternate meaning once direct function calls are removed from lexi");
			}
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

/* BEGINNING OF TRAILER */



/* END OF FILE */
