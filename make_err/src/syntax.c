/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	/Users/kate/svn/tendra16/obj-regen/bin/sid
 */

/* BEGINNING OF HEADER */

#line 171 "syntax.act"

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

#include <shared/error.h>
#include <shared/xalloc.h>

#include "obj_c/errors.h"
#include "obj_c/entry_ops.h"
#include "obj_c/map_ops.h"
#include "obj_c/msg_ops.h"
#include "obj_c/name_ops.h"
#include "obj_c/param_ops.h"

#include "lex.h"
#include "process.h"
#include "syntax.h"


/*
    PARSER TYPES

    These types give the implementation of the types used in the syntax.
*/

typedef LIST ( ENTRY ) LIST_ENTRY ;
typedef LIST ( MAP ) LIST_MAP ;
typedef LIST ( MESSAGE ) LIST_MESSAGE ;
typedef LIST ( NAME ) LIST_NAME ;
typedef LIST ( PARAM ) LIST_PARAM ;
typedef LIST ( PROPERTY ) LIST_PROPERTY ;


/*
    COUNTER VARIABLE

    This variable is used to keep count of the position in a name or
    parameter list.
*/

static int counter = 0 ;


/*
    FIND A NAME

    This routine searches the name list p for an identifier matching id.
    The null name is returned if no matching name is found.
*/

static NAME find_name
    ( LIST ( NAME ) p, string id )
{
    while ( !IS_NULL_list ( p ) ) {
	NAME a = DEREF_name ( HEAD_list ( p ) ) ;
	string nm = DEREF_string ( name_id ( a ) ) ;
	if ( !strcmp ( nm, id ) ) return ( a ) ;
	p = TAIL_list ( p ) ;
    }
    return ( NULL_name ) ;
}


/*
    FIND A PARAMETER

    This routine searches the parameter list p for an identifier matching
    id.  The null parameter is returned if no matching parameter is found.
*/

static PARAM find_param
    ( LIST ( PARAM ) p, string id )
{
    while ( !IS_NULL_list ( p ) ) {
	PARAM a = DEREF_param ( HEAD_list ( p ) ) ;
	string nm = DEREF_string ( param_name ( a ) ) ;
	if ( !strcmp ( nm, id ) ) return ( a ) ;
	p = TAIL_list ( p ) ;
    }
    return ( NULL_param ) ;
}


/*
    COMPILATION MODE

    We allow unreached code and switch off the variable analysis in the
    automatically generated sections.
*/

#if FS_TENDRA
#pragma TenDRA begin
#pragma TenDRA variable analysis off
#ifndef OLD_PRODUCER
#pragma TenDRA unreachable code allow
#endif
#endif


#line 141 "syntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRparam_Hlist(LIST_PARAM *);
static void ZRname_Hlist(LIST_NAME *, LIST_NAME *, LIST_NAME *);
static void ZRname_Hseq(LIST_NAME *, LIST_NAME *, LIST_NAME *);
static void ZRprops_Hlist(LIST_PROPERTY *);
static void ZRmap_Hlist(LIST_PARAM, LIST_MAP *);
static void ZRentry(ENTRY *);
extern void read_errors(void);
static void ZRmessage_Hlist(LIST_PARAM, LIST_MESSAGE *);
static void ZRsignature(LIST_PARAM *);
static void ZRentries_Hlist(LIST_ENTRY *);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRparam_Hlist(LIST_PARAM *ZOp)
{
	LIST_PARAM ZIp;

	if ((CURRENT_TERMINAL) == 26) {
		return;
	}
	{
		string ZIa;
		TYPE ZIt;
		string ZIb;
		PARAM ZIc;
		LIST_PARAM ZIq;

		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 219 "syntax.act"

    ZIa = xstrcpy ( token_buff ) ;
#line 183 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: find_type */
		{
#line 347 "syntax.act"

    NAME n = find_name ( all_types, (ZIa) ) ;
    if ( IS_NULL_name ( n ) ) {
	error ( ERROR_SERIOUS, "Type '%s' not defined", (ZIa) ) ;
	MAKE_name_basic ( (ZIa), 0, n ) ;
    }
    (ZIt) = n ;
#line 201 "syntax.c"
		}
		/* END OF ACTION: find_type */
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
#line 219 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 218 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: make_param */
		{
#line 394 "syntax.act"

    MAKE_param_basic ( (ZIt), (ZIb), counter, (ZIc) ) ;
    counter++ ;
#line 232 "syntax.c"
		}
		/* END OF ACTION: make_param */
		/* BEGINNING OF INLINE: 79 */
		{
			switch (CURRENT_TERMINAL) {
			case 17:
				{
					ADVANCE_LEXER;
					ZRparam_Hlist (&ZIq);
					if ((CURRENT_TERMINAL) == 26) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty_param_list */
					{
#line 283 "syntax.act"

    (ZIq) = NULL_list ( PARAM ) ;
#line 255 "syntax.c"
					}
					/* END OF ACTION: empty_param_list */
				}
				break;
			}
		}
		/* END OF INLINE: 79 */
		/* BEGINNING OF ACTION: cons_param_list */
		{
#line 287 "syntax.act"

    string id = DEREF_string ( param_name ( (ZIc) ) ) ;
    PARAM b = find_param ( (ZIq), id ) ;
    if ( !IS_NULL_param ( b ) ) {
	error ( ERROR_SERIOUS, "Parameter '%s' defined twice", id ) ;
    }
    CONS_param ( (ZIc), (ZIq), (ZIp) ) ;
#line 273 "syntax.c"
		}
		/* END OF ACTION: cons_param_list */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (26);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRname_Hlist(LIST_NAME *ZOp, LIST_NAME *ZOq, LIST_NAME *ZOr)
{
	LIST_NAME ZIp;
	LIST_NAME ZIq;
	LIST_NAME ZIr;

	switch (CURRENT_TERMINAL) {
	case 0:
		{
			ZRname_Hseq (&ZIp, &ZIq, &ZIr);
			if ((CURRENT_TERMINAL) == 26) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty_name_list */
			{
#line 304 "syntax.act"

    (ZIp) = NULL_list ( NAME ) ;
#line 309 "syntax.c"
			}
			/* END OF ACTION: empty_name_list */
			/* BEGINNING OF ACTION: empty_name_list */
			{
#line 304 "syntax.act"

    (ZIq) = NULL_list ( NAME ) ;
#line 317 "syntax.c"
			}
			/* END OF ACTION: empty_name_list */
			/* BEGINNING OF ACTION: empty_name_list */
			{
#line 304 "syntax.act"

    (ZIr) = NULL_list ( NAME ) ;
#line 325 "syntax.c"
			}
			/* END OF ACTION: empty_name_list */
		}
		break;
	case 26:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (26);
	return;
ZL0:;
	*ZOp = ZIp;
	*ZOq = ZIq;
	*ZOr = ZIr;
}

static void
ZRname_Hseq(LIST_NAME *ZOp, LIST_NAME *ZOq, LIST_NAME *ZOr)
{
	LIST_NAME ZIp;
	LIST_NAME ZIq;
	LIST_NAME ZIr;

	if ((CURRENT_TERMINAL) == 26) {
		return;
	}
	{
		string ZIa;
		NAME ZIn;
		NAME ZIm;
		NAME ZIk;
		LIST_NAME ZIp1;
		LIST_NAME ZIq1;
		LIST_NAME ZIr1;

		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 219 "syntax.act"

    ZIa = xstrcpy ( token_buff ) ;
#line 369 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: make_name */
		{
#line 385 "syntax.act"

    MAKE_name_basic ( (ZIa), counter, (ZIn) ) ;
    counter++ ;
#line 383 "syntax.c"
		}
		/* END OF ACTION: make_name */
		/* BEGINNING OF INLINE: 109 */
		{
			switch (CURRENT_TERMINAL) {
			case 18:
				{
					string ZIb;
					NAME ZIk1;

					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 0:
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 219 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 402 "syntax.c"
						}
						/* END OF EXTRACT: identifier */
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: make_name_aux */
					{
#line 390 "syntax.act"

    MAKE_name_basic ( (ZIb), 0, (ZIm) ) ;
#line 415 "syntax.c"
					}
					/* END OF ACTION: make_name_aux */
					/* BEGINNING OF INLINE: 110 */
					{
						switch (CURRENT_TERMINAL) {
						case 19:
							{
								string ZIc;

								ADVANCE_LEXER;
								switch (CURRENT_TERMINAL) {
								case 0:
									/* BEGINNING OF EXTRACT: identifier */
									{
#line 219 "syntax.act"

    ZIc = xstrcpy ( token_buff ) ;
#line 433 "syntax.c"
									}
									/* END OF EXTRACT: identifier */
									break;
								default:
									goto ZL1;
								}
								ADVANCE_LEXER;
								/* BEGINNING OF ACTION: make_name_aux */
								{
#line 390 "syntax.act"

    MAKE_name_basic ( (ZIc), 0, (ZIk1) ) ;
#line 446 "syntax.c"
								}
								/* END OF ACTION: make_name_aux */
							}
							break;
						default:
							{
								ZIk1 = ZIm;
							}
							break;
						}
					}
					/* END OF INLINE: 110 */
					ZIk = ZIk1;
				}
				break;
			default:
				{
					ZIm = ZIn;
					ZIk = ZIn;
				}
				break;
			}
		}
		/* END OF INLINE: 109 */
		/* BEGINNING OF INLINE: 116 */
		{
			switch (CURRENT_TERMINAL) {
			case 17:
				{
					ADVANCE_LEXER;
					ZRname_Hseq (&ZIp1, &ZIq1, &ZIr1);
					if ((CURRENT_TERMINAL) == 26) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty_name_list */
					{
#line 304 "syntax.act"

    (ZIp1) = NULL_list ( NAME ) ;
#line 491 "syntax.c"
					}
					/* END OF ACTION: empty_name_list */
					/* BEGINNING OF ACTION: empty_name_list */
					{
#line 304 "syntax.act"

    (ZIq1) = NULL_list ( NAME ) ;
#line 499 "syntax.c"
					}
					/* END OF ACTION: empty_name_list */
					/* BEGINNING OF ACTION: empty_name_list */
					{
#line 304 "syntax.act"

    (ZIr1) = NULL_list ( NAME ) ;
#line 507 "syntax.c"
					}
					/* END OF ACTION: empty_name_list */
				}
				break;
			}
		}
		/* END OF INLINE: 116 */
		/* BEGINNING OF ACTION: cons_name_list */
		{
#line 308 "syntax.act"

    string id = DEREF_string ( name_id ( (ZIn) ) ) ;
    NAME b = find_name ( (ZIp1), id ) ;
    if ( !IS_NULL_name ( b ) ) {
	error ( ERROR_SERIOUS, "Name '%s' given twice in list", id ) ;
    }
    CONS_name ( (ZIn), (ZIp1), (ZIp) ) ;
#line 525 "syntax.c"
		}
		/* END OF ACTION: cons_name_list */
		/* BEGINNING OF ACTION: join_name_list */
		{
#line 317 "syntax.act"

    CONS_name ( (ZIm), (ZIq1), (ZIq) ) ;
#line 533 "syntax.c"
		}
		/* END OF ACTION: join_name_list */
		/* BEGINNING OF ACTION: join_name_list */
		{
#line 317 "syntax.act"

    CONS_name ( (ZIk), (ZIr1), (ZIr) ) ;
#line 541 "syntax.c"
		}
		/* END OF ACTION: join_name_list */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (26);
	return;
ZL0:;
	*ZOp = ZIp;
	*ZOq = ZIq;
	*ZOr = ZIr;
}

static void
ZRprops_Hlist(LIST_PROPERTY *ZOp)
{
	LIST_PROPERTY ZIp;

	if ((CURRENT_TERMINAL) == 26) {
		return;
	}
	{
		string ZIa;
		PROPERTY ZIb;
		LIST_PROPERTY ZIq;

		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 219 "syntax.act"

    ZIa = xstrcpy ( token_buff ) ;
#line 575 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: find_props */
		{
#line 338 "syntax.act"

    NAME n = find_name ( all_props, (ZIa) ) ;
    if ( IS_NULL_name ( n ) ) {
	error ( ERROR_SERIOUS, "Property '%s' not defined", (ZIa) ) ;
	MAKE_name_basic ( (ZIa), 0, n ) ;
    }
    (ZIb) = n ;
#line 593 "syntax.c"
		}
		/* END OF ACTION: find_props */
		/* BEGINNING OF INLINE: 71 */
		{
			switch (CURRENT_TERMINAL) {
			case 17:
				{
					ADVANCE_LEXER;
					ZRprops_Hlist (&ZIq);
					if ((CURRENT_TERMINAL) == 26) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty_props_list */
					{
#line 275 "syntax.act"

    (ZIq) = NULL_list ( PROPERTY ) ;
#line 616 "syntax.c"
					}
					/* END OF ACTION: empty_props_list */
				}
				break;
			}
		}
		/* END OF INLINE: 71 */
		/* BEGINNING OF ACTION: cons_props_list */
		{
#line 279 "syntax.act"

    CONS_name ( (ZIb), (ZIq), (ZIp) ) ;
#line 629 "syntax.c"
		}
		/* END OF ACTION: cons_props_list */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (26);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRmap_Hlist(LIST_PARAM ZIs, LIST_MAP *ZOp)
{
	LIST_MAP ZIp;

	switch (CURRENT_TERMINAL) {
	case 5:
		{
			string ZIa;
			KEY ZIk;
			LIST_MESSAGE ZIm1;
			LIST_MESSAGE ZIm2;
			MAP ZIn;
			LIST_MAP ZIq;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 20:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 219 "syntax.act"

    ZIa = xstrcpy ( token_buff ) ;
#line 671 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 21:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: find_key */
			{
#line 330 "syntax.act"

    NAME n = find_name ( all_keys, (ZIa) ) ;
    if ( IS_NULL_name ( n ) ) {
	error ( ERROR_SERIOUS, "Key '%s' not defined", (ZIa) ) ;
    }
    (ZIk) = n ;
#line 695 "syntax.c"
			}
			/* END OF ACTION: find_key */
			ZRmessage_Hlist (ZIs, &ZIm1);
			/* BEGINNING OF INLINE: 63 */
			{
				switch (CURRENT_TERMINAL) {
				case 19:
					{
						ADVANCE_LEXER;
						ZRmessage_Hlist (ZIs, &ZIm2);
						if ((CURRENT_TERMINAL) == 26) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				default:
					{
						ZIm2 = ZIm1;
					}
					break;
				case 26:
					RESTORE_LEXER;
					goto ZL1;
				}
			}
			/* END OF INLINE: 63 */
			/* BEGINNING OF ACTION: make_map */
			{
#line 411 "syntax.act"

    MAKE_map_basic  ( (ZIk), (ZIm1), (ZIm2), (ZIn) ) ;
#line 728 "syntax.c"
			}
			/* END OF ACTION: make_map */
			ZRmap_Hlist (ZIs, &ZIq);
			if ((CURRENT_TERMINAL) == 26) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: cons_map_list */
			{
#line 271 "syntax.act"

    CONS_map ( (ZIn), (ZIq), (ZIp) ) ;
#line 741 "syntax.c"
			}
			/* END OF ACTION: cons_map_list */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty_map_list */
			{
#line 267 "syntax.act"

    (ZIp) = NULL_list ( MAP ) ;
#line 753 "syntax.c"
			}
			/* END OF ACTION: empty_map_list */
		}
		break;
	case 26:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (26);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRentry(ENTRY *ZOe)
{
	ENTRY ZIe;

	if ((CURRENT_TERMINAL) == 26) {
		return;
	}
	{
		string ZIa;
		LIST_PARAM ZIs;
		string ZIb;
		USAGE ZIu;
		USAGE ZIv;
		LIST_PROPERTY ZIp;
		LIST_MAP ZIm;

		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 219 "syntax.act"

    ZIa = xstrcpy ( token_buff ) ;
#line 793 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
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
		ZRsignature (&ZIs);
		switch (CURRENT_TERMINAL) {
		case 21:
			break;
		case 26:
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
		/* BEGINNING OF INLINE: 87 */
		{
			switch (CURRENT_TERMINAL) {
			case 2:
				{
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
#line 219 "syntax.act"

    ZIb = xstrcpy ( token_buff ) ;
#line 846 "syntax.c"
						}
						/* END OF EXTRACT: identifier */
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: null_identifier */
					{
#line 245 "syntax.act"

    (ZIb) = NULL ;
#line 863 "syntax.c"
					}
					/* END OF ACTION: null_identifier */
				}
				break;
			}
		}
		/* END OF INLINE: 87 */
		/* BEGINNING OF INLINE: 88 */
		{
			switch (CURRENT_TERMINAL) {
			case 11:
				{
					string ZIc;
					USAGE ZIw;

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
#line 219 "syntax.act"

    ZIc = xstrcpy ( token_buff ) ;
#line 894 "syntax.c"
						}
						/* END OF EXTRACT: identifier */
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: find_usage */
					{
#line 356 "syntax.act"

    NAME n = find_name ( all_usages, (ZIc) ) ;
    if ( IS_NULL_name ( n ) ) {
	error ( ERROR_SERIOUS, "Usage '%s' not defined", (ZIc) ) ;
	MAKE_name_basic ( (ZIc), 0, n ) ;
    }
    (ZIu) = n ;
#line 912 "syntax.c"
					}
					/* END OF ACTION: find_usage */
					/* BEGINNING OF INLINE: 90 */
					{
						switch (CURRENT_TERMINAL) {
						case 19:
							{
								string ZId;

								ADVANCE_LEXER;
								switch (CURRENT_TERMINAL) {
								case 0:
									/* BEGINNING OF EXTRACT: identifier */
									{
#line 219 "syntax.act"

    ZId = xstrcpy ( token_buff ) ;
#line 930 "syntax.c"
									}
									/* END OF EXTRACT: identifier */
									break;
								default:
									goto ZL1;
								}
								ADVANCE_LEXER;
								/* BEGINNING OF ACTION: find_usage */
								{
#line 356 "syntax.act"

    NAME n = find_name ( all_usages, (ZId) ) ;
    if ( IS_NULL_name ( n ) ) {
	error ( ERROR_SERIOUS, "Usage '%s' not defined", (ZId) ) ;
	MAKE_name_basic ( (ZId), 0, n ) ;
    }
    (ZIw) = n ;
#line 948 "syntax.c"
								}
								/* END OF ACTION: find_usage */
							}
							break;
						default:
							{
								ZIw = ZIu;
							}
							break;
						}
					}
					/* END OF INLINE: 90 */
					ZIv = ZIw;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: null_usage */
					{
#line 381 "syntax.act"

    (ZIu) = NULL_name ;
#line 971 "syntax.c"
					}
					/* END OF ACTION: null_usage */
					/* BEGINNING OF ACTION: null_usage */
					{
#line 381 "syntax.act"

    (ZIv) = NULL_name ;
#line 979 "syntax.c"
					}
					/* END OF ACTION: null_usage */
				}
				break;
			}
		}
		/* END OF INLINE: 88 */
		/* BEGINNING OF INLINE: 96 */
		{
			switch (CURRENT_TERMINAL) {
			case 8:
				{
					LIST_PROPERTY ZIq;

					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 16:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: 97 */
					{
						switch (CURRENT_TERMINAL) {
						case 0:
							{
								ZRprops_Hlist (&ZIq);
								if ((CURRENT_TERMINAL) == 26) {
									RESTORE_LEXER;
									goto ZL1;
								}
							}
							break;
						default:
							{
								/* BEGINNING OF ACTION: empty_props_list */
								{
#line 275 "syntax.act"

    (ZIq) = NULL_list ( PROPERTY ) ;
#line 1021 "syntax.c"
								}
								/* END OF ACTION: empty_props_list */
							}
							break;
						}
					}
					/* END OF INLINE: 97 */
					ZIp = ZIq;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty_props_list */
					{
#line 275 "syntax.act"

    (ZIp) = NULL_list ( PROPERTY ) ;
#line 1039 "syntax.c"
					}
					/* END OF ACTION: empty_props_list */
				}
				break;
			}
		}
		/* END OF INLINE: 96 */
		ZRmap_Hlist (ZIs, &ZIm);
		switch (CURRENT_TERMINAL) {
		case 23:
			break;
		case 26:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: make_entry */
		{
#line 416 "syntax.act"

    MAKE_entry_basic ( (ZIa), (ZIb), (ZIs), (ZIu), (ZIv), (ZIp), (ZIm), (ZIe) ) ;
    counter = 0 ;
#line 1064 "syntax.c"
		}
		/* END OF ACTION: make_entry */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (26);
	return;
ZL0:;
	*ZOe = ZIe;
}

void
read_errors(void)
{
	if ((CURRENT_TERMINAL) == 26) {
		return;
	}
	{
		LIST_NAME ZIt1;
		LIST_NAME ZIt2;
		LIST_NAME ZIt3;
		LIST_NAME ZIp1;
		LIST_NAME ZIp2;
		LIST_NAME ZIp3;
		LIST_NAME ZIk1;
		LIST_NAME ZIk2;
		LIST_NAME ZIk3;
		LIST_NAME ZIu1;
		LIST_NAME ZIu2;
		LIST_NAME ZIu3;
		LIST_ENTRY ZIe;

		/* BEGINNING OF INLINE: 131 */
		{
			switch (CURRENT_TERMINAL) {
			case 3:
				{
					string ZId;
					string ZI158;

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
#line 219 "syntax.act"

    ZId = xstrcpy ( token_buff ) ;
#line 1120 "syntax.c"
						}
						/* END OF EXTRACT: identifier */
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: 132 */
					{
						switch (CURRENT_TERMINAL) {
						case 19:
							{
								ADVANCE_LEXER;
								switch (CURRENT_TERMINAL) {
								case 0:
									/* BEGINNING OF EXTRACT: identifier */
									{
#line 219 "syntax.act"

    ZI158 = xstrcpy ( token_buff ) ;
#line 1141 "syntax.c"
									}
									/* END OF EXTRACT: identifier */
									break;
								default:
									goto ZL1;
								}
								ADVANCE_LEXER;
							}
							break;
						default:
							{
								ZI158 = ZId;
							}
							break;
						}
					}
					/* END OF INLINE: 132 */
					/* BEGINNING OF ACTION: set_db */
					{
#line 429 "syntax.act"

    db_name = (ZId) ;
    db_name_alt = (ZI158) ;
#line 1165 "syntax.c"
					}
					/* END OF ACTION: set_db */
				}
				break;
			default:
				break;
			}
		}
		/* END OF INLINE: 131 */
		/* BEGINNING OF INLINE: 134 */
		{
			switch (CURRENT_TERMINAL) {
			case 9:
				{
					string ZIr;

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
#line 219 "syntax.act"

    ZIr = xstrcpy ( token_buff ) ;
#line 1197 "syntax.c"
						}
						/* END OF EXTRACT: identifier */
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: set_rig */
					{
#line 434 "syntax.act"

    rig_name = (ZIr) ;
#line 1210 "syntax.c"
					}
					/* END OF ACTION: set_rig */
				}
				break;
			default:
				break;
			}
		}
		/* END OF INLINE: 134 */
		/* BEGINNING OF INLINE: 135 */
		{
			switch (CURRENT_TERMINAL) {
			case 7:
				{
					string ZIq1;
					string ZIq2;
					string ZIq3;

					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 16:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: 136 */
					{
						switch (CURRENT_TERMINAL) {
						case 12:
							{
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
#line 219 "syntax.act"

    ZIq1 = xstrcpy ( token_buff ) ;
#line 1257 "syntax.c"
									}
									/* END OF EXTRACT: identifier */
									break;
								default:
									goto ZL1;
								}
								ADVANCE_LEXER;
							}
							break;
						default:
							{
								/* BEGINNING OF ACTION: null_identifier */
								{
#line 245 "syntax.act"

    (ZIq1) = NULL ;
#line 1274 "syntax.c"
								}
								/* END OF ACTION: null_identifier */
							}
							break;
						}
					}
					/* END OF INLINE: 136 */
					/* BEGINNING OF INLINE: 137 */
					{
						switch (CURRENT_TERMINAL) {
						case 13:
							{
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
#line 219 "syntax.act"

    ZIq2 = xstrcpy ( token_buff ) ;
#line 1302 "syntax.c"
									}
									/* END OF EXTRACT: identifier */
									break;
								default:
									goto ZL1;
								}
								ADVANCE_LEXER;
							}
							break;
						default:
							{
								/* BEGINNING OF ACTION: null_identifier */
								{
#line 245 "syntax.act"

    (ZIq2) = NULL ;
#line 1319 "syntax.c"
								}
								/* END OF ACTION: null_identifier */
							}
							break;
						}
					}
					/* END OF INLINE: 137 */
					/* BEGINNING OF INLINE: 139 */
					{
						switch (CURRENT_TERMINAL) {
						case 14:
							{
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
#line 219 "syntax.act"

    ZIq3 = xstrcpy ( token_buff ) ;
#line 1347 "syntax.c"
									}
									/* END OF EXTRACT: identifier */
									break;
								default:
									goto ZL1;
								}
								ADVANCE_LEXER;
							}
							break;
						default:
							{
								/* BEGINNING OF ACTION: null_identifier */
								{
#line 245 "syntax.act"

    (ZIq3) = NULL ;
#line 1364 "syntax.c"
								}
								/* END OF ACTION: null_identifier */
							}
							break;
						}
					}
					/* END OF INLINE: 139 */
					/* BEGINNING OF ACTION: set_prefix */
					{
#line 438 "syntax.act"

    if ( (ZIq1) ) rig_comp_output = (ZIq1) ;
    if ( (ZIq2) ) rig_from_comp = (ZIq2) ;
    if ( (ZIq3) ) rig_from_db = (ZIq3) ;
#line 1379 "syntax.c"
					}
					/* END OF ACTION: set_prefix */
				}
				break;
			default:
				{
					string ZIq1;
					string ZIq2;
					string ZIq3;

					/* BEGINNING OF ACTION: null_identifier */
					{
#line 245 "syntax.act"

    (ZIq1) = NULL ;
#line 1395 "syntax.c"
					}
					/* END OF ACTION: null_identifier */
					/* BEGINNING OF ACTION: null_identifier */
					{
#line 245 "syntax.act"

    (ZIq2) = NULL ;
#line 1403 "syntax.c"
					}
					/* END OF ACTION: null_identifier */
					/* BEGINNING OF ACTION: null_identifier */
					{
#line 245 "syntax.act"

    (ZIq3) = NULL ;
#line 1411 "syntax.c"
					}
					/* END OF ACTION: null_identifier */
					/* BEGINNING OF ACTION: set_prefix */
					{
#line 438 "syntax.act"

    if ( (ZIq1) ) rig_comp_output = (ZIq1) ;
    if ( (ZIq2) ) rig_from_comp = (ZIq2) ;
    if ( (ZIq3) ) rig_from_db = (ZIq3) ;
#line 1421 "syntax.c"
					}
					/* END OF ACTION: set_prefix */
				}
				break;
			}
		}
		/* END OF INLINE: 135 */
		/* BEGINNING OF INLINE: 141 */
		{
			switch (CURRENT_TERMINAL) {
			case 10:
				{
					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 16:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					ZRname_Hlist (&ZIt1, &ZIt2, &ZIt3);
					if ((CURRENT_TERMINAL) == 26) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty_name_list */
					{
#line 304 "syntax.act"

    (ZIt1) = NULL_list ( NAME ) ;
#line 1456 "syntax.c"
					}
					/* END OF ACTION: empty_name_list */
					/* BEGINNING OF ACTION: empty_name_list */
					{
#line 304 "syntax.act"

    (ZIt2) = NULL_list ( NAME ) ;
#line 1464 "syntax.c"
					}
					/* END OF ACTION: empty_name_list */
					/* BEGINNING OF ACTION: empty_name_list */
					{
#line 304 "syntax.act"

    (ZIt3) = NULL_list ( NAME ) ;
#line 1472 "syntax.c"
					}
					/* END OF ACTION: empty_name_list */
				}
				break;
			}
		}
		/* END OF INLINE: 141 */
		/* BEGINNING OF ACTION: set_types */
		{
#line 444 "syntax.act"

    all_types = (ZIt1) ;
    all_types_aux = (ZIt2) ;
    all_types_alt = (ZIt3) ;
    counter = 0 ;
#line 1488 "syntax.c"
		}
		/* END OF ACTION: set_types */
		/* BEGINNING OF INLINE: 145 */
		{
			switch (CURRENT_TERMINAL) {
			case 8:
				{
					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 16:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					ZRname_Hlist (&ZIp1, &ZIp2, &ZIp3);
					if ((CURRENT_TERMINAL) == 26) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty_name_list */
					{
#line 304 "syntax.act"

    (ZIp1) = NULL_list ( NAME ) ;
#line 1518 "syntax.c"
					}
					/* END OF ACTION: empty_name_list */
					/* BEGINNING OF ACTION: empty_name_list */
					{
#line 304 "syntax.act"

    (ZIp2) = NULL_list ( NAME ) ;
#line 1526 "syntax.c"
					}
					/* END OF ACTION: empty_name_list */
					/* BEGINNING OF ACTION: empty_name_list */
					{
#line 304 "syntax.act"

    (ZIp3) = NULL_list ( NAME ) ;
#line 1534 "syntax.c"
					}
					/* END OF ACTION: empty_name_list */
				}
				break;
			}
		}
		/* END OF INLINE: 145 */
		/* BEGINNING OF ACTION: set_props */
		{
#line 451 "syntax.act"

    all_props = (ZIp1) ;
    all_props_aux = (ZIp2) ;
    all_props_alt = (ZIp3) ;
    counter = 0 ;
#line 1550 "syntax.c"
		}
		/* END OF ACTION: set_props */
		/* BEGINNING OF INLINE: 148 */
		{
			switch (CURRENT_TERMINAL) {
			case 6:
				{
					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 16:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					ZRname_Hlist (&ZIk1, &ZIk2, &ZIk3);
					if ((CURRENT_TERMINAL) == 26) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty_name_list */
					{
#line 304 "syntax.act"

    (ZIk1) = NULL_list ( NAME ) ;
#line 1580 "syntax.c"
					}
					/* END OF ACTION: empty_name_list */
					/* BEGINNING OF ACTION: empty_name_list */
					{
#line 304 "syntax.act"

    (ZIk2) = NULL_list ( NAME ) ;
#line 1588 "syntax.c"
					}
					/* END OF ACTION: empty_name_list */
					/* BEGINNING OF ACTION: empty_name_list */
					{
#line 304 "syntax.act"

    (ZIk3) = NULL_list ( NAME ) ;
#line 1596 "syntax.c"
					}
					/* END OF ACTION: empty_name_list */
				}
				break;
			}
		}
		/* END OF INLINE: 148 */
		/* BEGINNING OF ACTION: set_keys */
		{
#line 458 "syntax.act"

    all_keys = (ZIk1) ;
    all_keys_aux = (ZIk2) ;
    all_keys_alt = (ZIk3) ;
    counter = 0 ;
#line 1612 "syntax.c"
		}
		/* END OF ACTION: set_keys */
		/* BEGINNING OF INLINE: 151 */
		{
			switch (CURRENT_TERMINAL) {
			case 11:
				{
					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 16:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					ZRname_Hlist (&ZIu1, &ZIu2, &ZIu3);
					if ((CURRENT_TERMINAL) == 26) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty_name_list */
					{
#line 304 "syntax.act"

    (ZIu1) = NULL_list ( NAME ) ;
#line 1642 "syntax.c"
					}
					/* END OF ACTION: empty_name_list */
					/* BEGINNING OF ACTION: empty_name_list */
					{
#line 304 "syntax.act"

    (ZIu2) = NULL_list ( NAME ) ;
#line 1650 "syntax.c"
					}
					/* END OF ACTION: empty_name_list */
					/* BEGINNING OF ACTION: empty_name_list */
					{
#line 304 "syntax.act"

    (ZIu3) = NULL_list ( NAME ) ;
#line 1658 "syntax.c"
					}
					/* END OF ACTION: empty_name_list */
				}
				break;
			}
		}
		/* END OF INLINE: 151 */
		/* BEGINNING OF ACTION: set_usages */
		{
#line 465 "syntax.act"

    all_usages = (ZIu1) ;
    all_usages_aux = (ZIu2) ;
    all_usages_alt = (ZIu3) ;
    counter = 0 ;
#line 1674 "syntax.c"
		}
		/* END OF ACTION: set_usages */
		/* BEGINNING OF INLINE: 155 */
		{
			switch (CURRENT_TERMINAL) {
			case 4:
				{
					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 16:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					ZRentries_Hlist (&ZIe);
					if ((CURRENT_TERMINAL) == 26) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: empty_entry_list */
					{
#line 296 "syntax.act"

    (ZIe) = NULL_list ( ENTRY ) ;
#line 1704 "syntax.c"
					}
					/* END OF ACTION: empty_entry_list */
				}
				break;
			}
		}
		/* END OF INLINE: 155 */
		/* BEGINNING OF ACTION: set_entries */
		{
#line 472 "syntax.act"

    all_entries = (ZIe) ;
    counter = 0 ;
#line 1718 "syntax.c"
		}
		/* END OF ACTION: set_entries */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 485 "syntax.act"

    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1737 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRmessage_Hlist(LIST_PARAM ZIs, LIST_MESSAGE *ZOp)
{
	LIST_MESSAGE ZIp;

	switch (CURRENT_TERMINAL) {
	case 0:
		{
			string ZIa;
			PARAM ZIn;
			MESSAGE ZIm;
			LIST_MESSAGE ZIq;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 219 "syntax.act"

    ZIa = xstrcpy ( token_buff ) ;
#line 1761 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: find_param */
			{
#line 365 "syntax.act"

    PARAM a = find_param ( (ZIs), (ZIa) ) ;
    if ( IS_NULL_param ( a ) ) {
	error ( ERROR_SERIOUS, "Parameter '%s' not defined", (ZIa) ) ;
    }
    (ZIn) = a ;
#line 1774 "syntax.c"
			}
			/* END OF ACTION: find_param */
			/* BEGINNING OF ACTION: message_param */
			{
#line 399 "syntax.act"

    if ( !IS_NULL_param ( (ZIn) ) ) {
	MAKE_msg_param ( (ZIn), (ZIm) ) ;
    } else {
	MAKE_msg_text ( "<error>", (ZIm) ) ;
    }
#line 1786 "syntax.c"
			}
			/* END OF ACTION: message_param */
			ZRmessage_Hlist (ZIs, &ZIq);
			if ((CURRENT_TERMINAL) == 26) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: cons_message_list */
			{
#line 263 "syntax.act"

    CONS_msg ( (ZIm), (ZIq), (ZIp) ) ;
#line 1799 "syntax.c"
			}
			/* END OF ACTION: cons_message_list */
		}
		break;
	case 1:
		{
			string ZIa;
			MESSAGE ZIm;
			LIST_MESSAGE ZIq;

			/* BEGINNING OF EXTRACT: string */
			{
#line 231 "syntax.act"

    ZIa = xstrcpy ( token_buff ) ;
#line 1815 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: message_string */
			{
#line 407 "syntax.act"

    MAKE_msg_text ( (ZIa), (ZIm) ) ;
#line 1824 "syntax.c"
			}
			/* END OF ACTION: message_string */
			ZRmessage_Hlist (ZIs, &ZIq);
			if ((CURRENT_TERMINAL) == 26) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: cons_message_list */
			{
#line 263 "syntax.act"

    CONS_msg ( (ZIm), (ZIq), (ZIp) ) ;
#line 1837 "syntax.c"
			}
			/* END OF ACTION: cons_message_list */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty_message_list */
			{
#line 259 "syntax.act"

    (ZIp) = NULL_list ( MESSAGE ) ;
#line 1849 "syntax.c"
			}
			/* END OF ACTION: empty_message_list */
		}
		break;
	case 26:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (26);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRsignature(LIST_PARAM *ZOp)
{
	LIST_PARAM ZIp;

	switch (CURRENT_TERMINAL) {
	case 0:
		{
			ZRparam_Hlist (&ZIp);
			if ((CURRENT_TERMINAL) == 26) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty_param_list */
			{
#line 283 "syntax.act"

    (ZIp) = NULL_list ( PARAM ) ;
#line 1887 "syntax.c"
			}
			/* END OF ACTION: empty_param_list */
		}
		break;
	case 26:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (26);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRentries_Hlist(LIST_ENTRY *ZOp)
{
	LIST_ENTRY ZIp;

	switch (CURRENT_TERMINAL) {
	case 0:
		{
			ENTRY ZIa;
			LIST_ENTRY ZIq;

			ZRentry (&ZIa);
			ZRentries_Hlist (&ZIq);
			if ((CURRENT_TERMINAL) == 26) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: cons_entry_list */
			{
#line 300 "syntax.act"

    CONS_entry ( (ZIa), (ZIq), (ZIp) ) ;
#line 1925 "syntax.c"
			}
			/* END OF ACTION: cons_entry_list */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: empty_entry_list */
			{
#line 296 "syntax.act"

    (ZIp) = NULL_list ( ENTRY ) ;
#line 1937 "syntax.c"
			}
			/* END OF ACTION: empty_entry_list */
		}
		break;
	case 26:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (26);
	return;
ZL0:;
	*ZOp = ZIp;
}

/* BEGINNING OF TRAILER */

#line 489 "syntax.act"

#line 1957 "syntax.c"

/* END OF FILE */
