/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	/Users/kate/svn/tendra20/obj-regen/bin/sid
 */

/* BEGINNING OF HEADER */

#line 140 "syntax.act"


/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>
#include <string.h>

#include <shared/error.h>
#include <shared/xalloc.h>
#include <shared/string.h>

#include "calculus.h"
#include "common.h"
#include "extra.h"
#include "lex.h"
#include "syntax.h"
#include "type_ops.h"


/*
    These types give the implementations of the various types used
    in the syntax.
*/

typedef LIST ( ARGUMENT_P ) ARGUMENT_P_LIST ;
typedef LIST ( COMPONENT_P ) COMPONENT_P_LIST ;
typedef LIST ( ECONST_P ) ECONST_P_LIST ;
typedef LIST ( ENUM_P ) ENUM_P_LIST ;
typedef LIST ( FIELD_P ) FIELD_P_LIST ;
typedef LIST ( IDENTITY_P ) IDENTITY_P_LIST ;
typedef LIST ( MAP_P ) MAP_P_LIST ;
typedef LIST ( PRIMITIVE_P ) PRIMITIVE_P_LIST ;
typedef LIST ( STRUCTURE_P ) STRUCTURE_P_LIST ;
typedef LIST ( UNION_P ) UNION_P_LIST ;


/*
    The variable enum_value is used to determine the value of enumerators.
    enum_max is used to record the maximum value of enum_value.  Both are
    reset to zero at the end of each enumeration type.  no_fields is used
    to count the number of field in each union.  It is reset to zero at
    the end of each union type.
*/

static number enum_value = 0 ;
static number enum_max = 0 ;
static int no_fields = 0 ;
static LIST ( ECONST_P ) enum_list = NULL_list ( ECONST_P ) ;


/*
    We allow unreached code in the automatically generated sections.
*/

#if FS_TENDRA
#pragma TenDRA begin
#ifndef OLD_PRODUCER
#pragma TenDRA unreachable code allow
#endif
#endif


#line 89 "syntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRimport_Hitem(void);
static void ZRprimary_Hexp(number *);
static void ZRextra_Hlist(void);
static void ZRclass_Hid(CLASS_ID_P *);
static void ZRnew_Hitem_Hlist(void);
extern void extra_calculus(void);
static void ZRshift_Hexp(number *);
static void ZRcomponent_Hdecl(TYPE_P, COMPONENT_P_LIST *);
static void ZRadd_Hexp(number *);
static void ZRstructure_Hsingle(STRUCTURE_P_LIST *);
static void ZRmap_Hlist(MAP_P_LIST *);
static void ZRprimitive_Hdefn(CLASS_ID_P, PRIMITIVE_P *);
static void ZRunary_Hexp(number *);
static void ZRand_Hexp(number *);
static void ZRargument_Hdecl(TYPE_P, ARGUMENT_P_LIST *);
static void ZRenumerator_Hlist(ECONST_P_LIST *);
static void ZRcomponent_Hgroup(COMPONENT_P_LIST *);
static void ZRnew_Hunit(void);
static void ZRidentity_Hdefn(CLASS_ID_P, IDENTITY_P *);
static void ZRmult_Hexp(number *);
extern void read_calculus(void);
static void ZRtype(TYPE_P *);
static void ZR197(string *);
static void ZRstructure_Hdefn(CLASS_ID_P, string, STRUCTURE_P *);
static void ZRcomponent_Hlist(COMPONENT_P_LIST *);
static void ZRextended_Htype(TYPE_P *);
static void ZRargument_Hlist(ARGUMENT_P_LIST *);
static void ZRexpression(number *);
static void ZRxor_Hexp(number *);
static void ZRor_Hexp(number *);
static void ZR224(number, number *);
static void ZRunion_Hsingle(UNION_P_LIST *);
static void ZR228(number, number *);
static void ZR232(number, number *);
static void ZRenum_Hsingle(ENUM_P_LIST *);
static void ZR236(number, number *);
static void ZRfield_Hid_Hlist(int, FIELD_P_LIST *);
static void ZR240(number, number *);
static void ZRfield_Hlist(FIELD_P_LIST *);
static void ZRunion_Hdefn_Hnew(CLASS_ID_P, UNION_P *);
static void ZR244(number, number *);
static void ZR248(CLASS_ID_P *);
static void ZR249(int *);
static void ZR250(int *);
static void ZR251(string *);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRimport_Hitem(void)
{
	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		string ZIa;

		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 168 "syntax.act"

    ZIa = xstrdup ( token_buff ) ;
#line 160 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR251 (&ZIa);
		if ((CURRENT_TERMINAL) == 42) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (42);
	return;
}

static void
ZRprimary_Hexp(number *ZOn)
{
	number ZIn;

	switch (CURRENT_TERMINAL) {
	case 0:
		{
			string ZIe;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 168 "syntax.act"

    ZIe = xstrdup ( token_buff ) ;
#line 195 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp-id */
			{
#line 378 "syntax.act"

    number n = 0 ;
    LIST ( ECONST_P ) p = enum_list ;
    while ( !IS_NULL_list ( p ) ) {
	ECONST_P q = DEREF_ptr ( HEAD_list ( p ) ) ;
	string s = DEREF_string ( ec_name ( q ) ) ;
	if ( !strcmp( s, (ZIe) ) ) {
	    n = DEREF_number ( ec_value ( q ) ) ;
	    break ;
	}
	p = TAIL_list ( p ) ;
    }
    if ( IS_NULL_list ( p ) ) {
	error ( ERROR_SERIOUS, "Unknown enumerator '%s'", (ZIe) ) ;
    }
    (ZIn) = n ;
#line 218 "syntax.c"
			}
			/* END OF ACTION: exp-id */
		}
		break;
	case 1:
		{
			/* BEGINNING OF EXTRACT: number */
			{
#line 180 "syntax.act"

    ZIn = token_value ;
#line 230 "syntax.c"
			}
			/* END OF EXTRACT: number */
			ADVANCE_LEXER;
		}
		break;
	case 31:
		{
			ADVANCE_LEXER;
			ZRexpression (&ZIn);
			switch (CURRENT_TERMINAL) {
			case 16:
				break;
			case 42:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 35:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp-crt */
			{
#line 369 "syntax.act"

    (ZIn) = enum_value - 1 ;
#line 260 "syntax.c"
			}
			/* END OF ACTION: exp-crt */
		}
		break;
	case 42:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOn = ZIn;
}

static void
ZRextra_Hlist(void)
{
ZL2_extra_Hlist:;
	switch (CURRENT_TERMINAL) {
	case 0: case 8: case 9: case 10:
	case 11: case 12:
		{
			TYPE_P ZIt;

			ZRtype (&ZIt);
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			case 42:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make-extra */
			{
#line 1012 "syntax.act"

    /* UNUSED ( (ZIt) ) ; */
#line 304 "syntax.c"
			}
			/* END OF ACTION: make-extra */
			/* BEGINNING OF INLINE: extra-list */
			goto ZL2_extra_Hlist;
			/* END OF INLINE: extra-list */
		}
		/*UNREACHED*/
	case 42:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (42);
	return;
}

static void
ZRclass_Hid(CLASS_ID_P *ZOi)
{
	CLASS_ID_P ZIi;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		int ZIn;
		string ZIc;
		string ZIa;

		/* BEGINNING OF INLINE: 148 */
		{
			switch (CURRENT_TERMINAL) {
			case 18:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: two */
					{
#line 207 "syntax.act"
 (ZIn) = 2 ; 
#line 346 "syntax.c"
					}
					/* END OF ACTION: two */
				}
				break;
			case 27:
				{
					ADVANCE_LEXER;
					ZR249 (&ZIn);
					if ((CURRENT_TERMINAL) == 42) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: zero */
					{
#line 205 "syntax.act"
 (ZIn) = 0 ; 
#line 367 "syntax.c"
					}
					/* END OF ACTION: zero */
				}
				break;
			}
		}
		/* END OF INLINE: 148 */
		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 168 "syntax.act"

    ZIc = xstrdup ( token_buff ) ;
#line 382 "syntax.c"
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
			case 31:
				{
					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 0:
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 168 "syntax.act"

    ZIa = xstrdup ( token_buff ) ;
#line 403 "syntax.c"
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
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: default-name */
					{
#line 242 "syntax.act"

    (ZIa) = (ZIc) ;
#line 427 "syntax.c"
					}
					/* END OF ACTION: default-name */
				}
				break;
			}
		}
		/* END OF INLINE: 151 */
		/* BEGINNING OF ACTION: make-class-id */
		{
#line 254 "syntax.act"

    (ZIi) = MAKE_ptr ( SIZE_cid ) ;
    MAKE_cid ( (ZIc), (ZIa), (ZIn), ( string ) crt_file_name, crt_line_no, (ZIi) ) ;
#line 441 "syntax.c"
		}
		/* END OF ACTION: make-class-id */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOi = ZIi;
}

static void
ZRnew_Hitem_Hlist(void)
{
ZL2_new_Hitem_Hlist:;
	switch (CURRENT_TERMINAL) {
	case 0: case 4: case 5: case 6:
	case 7: case 18: case 27:
		{
			/* BEGINNING OF INLINE: 213 */
			{
				switch (CURRENT_TERMINAL) {
				case 7:
					{
						ADVANCE_LEXER;
						ZRimport_Hitem ();
						switch (CURRENT_TERMINAL) {
						case 38:
							break;
						case 42:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
					}
					break;
				case 0: case 18: case 27:
					{
						CLASS_ID_P ZI247;

						ZRclass_Hid (&ZI247);
						switch (CURRENT_TERMINAL) {
						case 25:
							break;
						case 42:
							RESTORE_LEXER;
							goto ZL1;
						default:
							goto ZL1;
						}
						ADVANCE_LEXER;
						ZR248 (&ZI247);
						if ((CURRENT_TERMINAL) == 42) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				case 4:
					{
						ENUM_P_LIST ZIe;

						ZRenum_Hsingle (&ZIe);
						if ((CURRENT_TERMINAL) == 42) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: add-enum */
						{
#line 1094 "syntax.act"

    algebra->enumerations = APPEND_list ( algebra->enumerations, (ZIe) ) ;
#line 516 "syntax.c"
						}
						/* END OF ACTION: add-enum */
					}
					break;
				case 5:
					{
						STRUCTURE_P_LIST ZIs;

						ZRstructure_Hsingle (&ZIs);
						if ((CURRENT_TERMINAL) == 42) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: add-structure */
						{
#line 1105 "syntax.act"

    algebra->structures = APPEND_list ( algebra->structures, (ZIs) ) ;
#line 535 "syntax.c"
						}
						/* END OF ACTION: add-structure */
					}
					break;
				case 6:
					{
						UNION_P_LIST ZIu;

						ZRunion_Hsingle (&ZIu);
						if ((CURRENT_TERMINAL) == 42) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: add-union */
						{
#line 1116 "syntax.act"

    algebra->unions = APPEND_list ( algebra->unions, (ZIu) ) ;
#line 554 "syntax.c"
						}
						/* END OF ACTION: add-union */
					}
					break;
				default:
					goto ZL1;
				}
			}
			/* END OF INLINE: 213 */
			/* BEGINNING OF INLINE: new-item-list */
			goto ZL2_new_Hitem_Hlist;
			/* END OF INLINE: new-item-list */
		}
		/*UNREACHED*/
	case 42:
		return;
	default:
		break;
	}
	return;
ZL1:;
	SAVE_LEXER (42);
	return;
}

void
extra_calculus(void)
{
	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		ZRextra_Hlist ();
		switch (CURRENT_TERMINAL) {
		case 24:
			break;
		case 42:
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
		/* BEGINNING OF ACTION: syntax-error */
		{
#line 230 "syntax.act"

    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 607 "syntax.c"
		}
		/* END OF ACTION: syntax-error */
	}
}

static void
ZRshift_Hexp(number *ZO235)
{
	number ZI235;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		number ZIn;

		ZRadd_Hexp (&ZIn);
		ZR236 (ZIn, &ZI235);
		if ((CURRENT_TERMINAL) == 42) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZO235 = ZI235;
}

static void
ZRcomponent_Hdecl(TYPE_P ZIt, COMPONENT_P_LIST *ZOp)
{
	COMPONENT_P_LIST ZIp;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		string ZIi;
		string ZIv;
		COMPONENT_P ZIq;
		COMPONENT_P_LIST ZIr;

		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 168 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 660 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 185 */
		{
			switch (CURRENT_TERMINAL) {
			case 25:
				{
					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 2:
						/* BEGINNING OF EXTRACT: string */
						{
#line 192 "syntax.act"

    ZIv = xstrdup ( token_buff ) ;
#line 681 "syntax.c"
						}
						/* END OF EXTRACT: string */
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: null-string */
					{
#line 218 "syntax.act"

    (ZIv) = NULL ;
#line 698 "syntax.c"
					}
					/* END OF ACTION: null-string */
				}
				break;
			}
		}
		/* END OF INLINE: 185 */
		/* BEGINNING OF ACTION: make-component */
		{
#line 668 "syntax.act"

    (ZIq) = MAKE_ptr ( SIZE_cmp ) ;
    MAKE_cmp ( (ZIi), (ZIt), (ZIv), (ZIq) ) ;
#line 712 "syntax.c"
		}
		/* END OF ACTION: make-component */
		/* BEGINNING OF INLINE: 187 */
		{
			switch (CURRENT_TERMINAL) {
			case 20:
				{
					ADVANCE_LEXER;
					ZRcomponent_Hdecl (ZIt, &ZIr);
					if ((CURRENT_TERMINAL) == 42) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: null-component */
					{
#line 656 "syntax.act"

    (ZIr) = NULL_list ( COMPONENT_P ) ;
#line 735 "syntax.c"
					}
					/* END OF ACTION: null-component */
				}
				break;
			}
		}
		/* END OF INLINE: 187 */
		/* BEGINNING OF ACTION: join-component */
		{
#line 681 "syntax.act"

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
#line 748 "syntax.c"
		}
		/* END OF ACTION: join-component */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRadd_Hexp(number *ZO239)
{
	number ZI239;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		number ZIn;

		ZRmult_Hexp (&ZIn);
		ZR240 (ZIn, &ZI239);
		if ((CURRENT_TERMINAL) == 42) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZO239 = ZI239;
}

static void
ZRstructure_Hsingle(STRUCTURE_P_LIST *ZOp)
{
	STRUCTURE_P_LIST ZIp;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		CLASS_ID_P ZIi;
		string ZIj;
		STRUCTURE_P ZIq;
		STRUCTURE_P_LIST ZIr;

		switch (CURRENT_TERMINAL) {
		case 5:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRclass_Hid (&ZIi);
		switch (CURRENT_TERMINAL) {
		case 25:
			break;
		case 42:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR197 (&ZIj);
		ZRstructure_Hdefn (ZIi, ZIj, &ZIq);
		if ((CURRENT_TERMINAL) == 42) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: null-structure */
		{
#line 704 "syntax.act"

    (ZIr) = NULL_list ( STRUCTURE_P ) ;
#line 829 "syntax.c"
		}
		/* END OF ACTION: null-structure */
		/* BEGINNING OF ACTION: join-structure */
		{
#line 747 "syntax.act"

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
#line 837 "syntax.c"
		}
		/* END OF ACTION: join-structure */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRmap_Hlist(MAP_P_LIST *ZOp)
{
	MAP_P_LIST ZIp;

	switch (CURRENT_TERMINAL) {
	case 0: case 2: case 8: case 9:
	case 10: case 11: case 12:
		{
			TYPE_P ZIt;
			int ZIn;
			string ZIi;
			ARGUMENT_P_LIST ZIa;
			MAP_P ZIq;
			MAP_P_LIST ZIr;

			ZRextended_Htype (&ZIt);
			/* BEGINNING OF INLINE: 204 */
			{
				switch (CURRENT_TERMINAL) {
				case 27:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: one */
						{
#line 206 "syntax.act"
 (ZIn) = 1 ; 
#line 876 "syntax.c"
						}
						/* END OF ACTION: one */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: zero */
						{
#line 205 "syntax.act"
 (ZIn) = 0 ; 
#line 887 "syntax.c"
						}
						/* END OF ACTION: zero */
					}
					break;
				case 42:
					RESTORE_LEXER;
					goto ZL1;
				}
			}
			/* END OF INLINE: 204 */
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 168 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 905 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 31:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 205 */
			{
				switch (CURRENT_TERMINAL) {
				case 0: case 2: case 8: case 9:
				case 10: case 11: case 12:
					{
						ZRargument_Hlist (&ZIa);
						if ((CURRENT_TERMINAL) == 42) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: null-argument */
						{
#line 835 "syntax.act"

    (ZIa) = NULL_list ( ARGUMENT_P ) ;
#line 940 "syntax.c"
						}
						/* END OF ACTION: null-argument */
					}
					break;
				}
			}
			/* END OF INLINE: 205 */
			switch (CURRENT_TERMINAL) {
			case 16:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: make-map */
			{
#line 894 "syntax.act"

    (ZIq) = MAKE_ptr ( SIZE_map ) ;
    MAKE_map ( (ZIi), (ZIn), (ZIt), (ZIa), (ZIq) ) ;
#line 961 "syntax.c"
			}
			/* END OF ACTION: make-map */
			ZRmap_Hlist (&ZIr);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: join-map */
			{
#line 906 "syntax.act"

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
#line 974 "syntax.c"
			}
			/* END OF ACTION: join-map */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: null-map */
			{
#line 882 "syntax.act"

    (ZIp) = NULL_list ( MAP_P ) ;
#line 986 "syntax.c"
			}
			/* END OF ACTION: null-map */
		}
		break;
	case 42:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRprimitive_Hdefn(CLASS_ID_P ZIi, PRIMITIVE_P *ZOp)
{
	PRIMITIVE_P ZIp;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		string ZIs;

		switch (CURRENT_TERMINAL) {
		case 2:
			/* BEGINNING OF EXTRACT: string */
			{
#line 192 "syntax.act"

    ZIs = xstrdup ( token_buff ) ;
#line 1020 "syntax.c"
			}
			/* END OF EXTRACT: string */
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
		/* BEGINNING OF ACTION: make-primitive */
		{
#line 518 "syntax.act"

    TYPE r ;
    TYPE_P t ;
    (ZIp) = MAKE_ptr ( SIZE_prim ) ;
    MAKE_prim ( (ZIi), (ZIs), (ZIp) ) ;
    t = MAKE_ptr ( SIZE_type ) ;
    MAKE_type_primitive ( 0, (ZIp), r ) ;
    COPY_type ( t, r ) ;
    register_type ( t ) ;
#line 1047 "syntax.c"
		}
		/* END OF ACTION: make-primitive */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRunary_Hexp(number *ZOn)
{
	number ZIn;

	switch (CURRENT_TERMINAL) {
	case 21:
		{
			number ZIm;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 1:
				/* BEGINNING OF EXTRACT: number */
				{
#line 180 "syntax.act"

    ZIm = token_value ;
#line 1077 "syntax.c"
				}
				/* END OF EXTRACT: number */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp-compl */
			{
#line 395 "syntax.act"

    (ZIn) = ~(ZIm) ;
#line 1090 "syntax.c"
			}
			/* END OF ACTION: exp-compl */
		}
		break;
	case 29:
		{
			number ZIm;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 1:
				/* BEGINNING OF EXTRACT: number */
				{
#line 180 "syntax.act"

    ZIm = token_value ;
#line 1107 "syntax.c"
				}
				/* END OF EXTRACT: number */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exp-neg */
			{
#line 391 "syntax.act"

    (ZIn) = -(ZIm) ;
#line 1120 "syntax.c"
			}
			/* END OF ACTION: exp-neg */
		}
		break;
	case 34:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 1:
				/* BEGINNING OF EXTRACT: number */
				{
#line 180 "syntax.act"

    ZIn = token_value ;
#line 1135 "syntax.c"
				}
				/* END OF EXTRACT: number */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 0: case 1: case 31: case 35:
		{
			ZRprimary_Hexp (&ZIn);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 42:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOn = ZIn;
}

static void
ZRand_Hexp(number *ZO231)
{
	number ZI231;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		number ZIn;

		ZRshift_Hexp (&ZIn);
		ZR232 (ZIn, &ZI231);
		if ((CURRENT_TERMINAL) == 42) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZO231 = ZI231;
}

static void
ZRargument_Hdecl(TYPE_P ZIt, ARGUMENT_P_LIST *ZOp)
{
	ARGUMENT_P_LIST ZIp;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		string ZIi;
		ARGUMENT_P ZIq;
		ARGUMENT_P_LIST ZIr;

		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 168 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 1213 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: make-argument */
		{
#line 846 "syntax.act"

    (ZIq) = MAKE_ptr ( SIZE_arg ) ;
    MAKE_arg ( (ZIi), (ZIt), (ZIq) ) ;
#line 1227 "syntax.c"
		}
		/* END OF ACTION: make-argument */
		/* BEGINNING OF INLINE: 200 */
		{
			switch (CURRENT_TERMINAL) {
			case 20:
				{
					ADVANCE_LEXER;
					ZRargument_Hdecl (ZIt, &ZIr);
					if ((CURRENT_TERMINAL) == 42) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: null-argument */
					{
#line 835 "syntax.act"

    (ZIr) = NULL_list ( ARGUMENT_P ) ;
#line 1250 "syntax.c"
					}
					/* END OF ACTION: null-argument */
				}
				break;
			}
		}
		/* END OF INLINE: 200 */
		/* BEGINNING OF ACTION: join-argument */
		{
#line 859 "syntax.act"

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
#line 1263 "syntax.c"
		}
		/* END OF ACTION: join-argument */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRenumerator_Hlist(ECONST_P_LIST *ZOp)
{
	ECONST_P_LIST ZIp;

	switch (CURRENT_TERMINAL) {
	case 0:
		{
			string ZIs;
			ECONST_P ZIq;
			ECONST_P_LIST ZIr;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 168 "syntax.act"

    ZIs = xstrdup ( token_buff ) ;
#line 1292 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 176 */
			{
				switch (CURRENT_TERMINAL) {
				case 25:
					{
						number ZIn;

						ADVANCE_LEXER;
						ZRexpression (&ZIn);
						if ((CURRENT_TERMINAL) == 42) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: set-econst */
						{
#line 494 "syntax.act"

    enum_value = (ZIn) ;
#line 1314 "syntax.c"
						}
						/* END OF ACTION: set-econst */
					}
					break;
				default:
					break;
				}
			}
			/* END OF INLINE: 176 */
			/* BEGINNING OF ACTION: make-econst */
			{
#line 469 "syntax.act"

    number v = enum_value++ ;
    if ( v > enum_max ) enum_max = v ;
    (ZIq) = MAKE_ptr ( SIZE_ec ) ;
    MAKE_ec ( (ZIs), v, (ZIq) ) ;
    CONS_ptr ( (ZIq), enum_list, enum_list ) ;
#line 1333 "syntax.c"
			}
			/* END OF ACTION: make-econst */
			/* BEGINNING OF INLINE: 177 */
			{
				switch (CURRENT_TERMINAL) {
				case 20:
					{
						ADVANCE_LEXER;
						ZRenumerator_Hlist (&ZIr);
						if ((CURRENT_TERMINAL) == 42) {
							RESTORE_LEXER;
							goto ZL1;
						}
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: null-econst */
						{
#line 456 "syntax.act"

    (ZIr) = NULL_list ( ECONST_P ) ;
#line 1356 "syntax.c"
						}
						/* END OF ACTION: null-econst */
					}
					break;
				}
			}
			/* END OF INLINE: 177 */
			/* BEGINNING OF ACTION: join-econst */
			{
#line 483 "syntax.act"

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
#line 1369 "syntax.c"
			}
			/* END OF ACTION: join-econst */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: null-econst */
			{
#line 456 "syntax.act"

    (ZIp) = NULL_list ( ECONST_P ) ;
#line 1381 "syntax.c"
			}
			/* END OF ACTION: null-econst */
		}
		break;
	case 42:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRcomponent_Hgroup(COMPONENT_P_LIST *ZOp)
{
	COMPONENT_P_LIST ZIp;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 30:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRcomponent_Hlist (&ZIp);
		switch (CURRENT_TERMINAL) {
		case 15:
			break;
		case 42:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRnew_Hunit(void)
{
	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		string ZIm;

		switch (CURRENT_TERMINAL) {
		case 3:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 168 "syntax.act"

    ZIm = xstrdup ( token_buff ) ;
#line 1456 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: set-main */
		{
#line 1045 "syntax.act"

    string nm = (ZIm) ;
    if ( find_algebra ( nm ) ) {
	error ( ERROR_SERIOUS, "Algebra %s already defined", nm ) ;
    }
    algebra->name = nm ;
#line 1473 "syntax.c"
		}
		/* END OF ACTION: set-main */
		/* BEGINNING OF INLINE: 216 */
		{
			switch (CURRENT_TERMINAL) {
			case 31:
				{
					number ZIa;
					number ZIb;

					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 1:
						/* BEGINNING OF EXTRACT: number */
						{
#line 180 "syntax.act"

    ZIa = token_value ;
#line 1492 "syntax.c"
						}
						/* END OF EXTRACT: number */
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 23:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 1:
						/* BEGINNING OF EXTRACT: number */
						{
#line 180 "syntax.act"

    ZIb = token_value ;
#line 1514 "syntax.c"
						}
						/* END OF EXTRACT: number */
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
					/* BEGINNING OF ACTION: set-version */
					{
#line 1060 "syntax.act"

    algebra->major_no = ( int ) (ZIa) ;
    algebra->minor_no = ( int ) (ZIb) ;
#line 1535 "syntax.c"
					}
					/* END OF ACTION: set-version */
				}
				break;
			default:
				break;
			}
		}
		/* END OF INLINE: 216 */
		switch (CURRENT_TERMINAL) {
		case 18:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRnew_Hitem_Hlist ();
		if ((CURRENT_TERMINAL) == 42) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	SAVE_LEXER (42);
	return;
}

static void
ZRidentity_Hdefn(CLASS_ID_P ZIi, IDENTITY_P *ZOp)
{
	IDENTITY_P ZIp;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		TYPE_P ZIt;

		ZRtype (&ZIt);
		switch (CURRENT_TERMINAL) {
		case 38:
			break;
		case 42:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: make-identity */
		{
#line 559 "syntax.act"

    TYPE r ;
    TYPE_P t ;
    (ZIp) = MAKE_ptr ( SIZE_ident ) ;
    MAKE_ident ( (ZIi), (ZIt), (ZIp) ) ;
    t = MAKE_ptr ( SIZE_type ) ;
    MAKE_type_ident ( 0, (ZIp), r ) ;
    COPY_type ( t, r ) ;
    register_type ( t ) ;
#line 1598 "syntax.c"
		}
		/* END OF ACTION: make-identity */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRmult_Hexp(number *ZO243)
{
	number ZI243;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		number ZIn;

		ZRunary_Hexp (&ZIn);
		ZR244 (ZIn, &ZI243);
		if ((CURRENT_TERMINAL) == 42) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZO243 = ZI243;
}

void
read_calculus(void)
{
	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		ZRnew_Hunit ();
		switch (CURRENT_TERMINAL) {
		case 24:
			break;
		case 42:
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
		/* BEGINNING OF ACTION: syntax-error */
		{
#line 230 "syntax.act"

    error ( ERROR_SERIOUS, "Syntax error" ) ;
#line 1663 "syntax.c"
		}
		/* END OF ACTION: syntax-error */
	}
}

static void
ZRtype(TYPE_P *ZOt)
{
	TYPE_P ZIt;

	switch (CURRENT_TERMINAL) {
	case 0:
		{
			string ZIi;

			/* BEGINNING OF EXTRACT: identifier */
			{
#line 168 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 1684 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: find-type */
			{
#line 277 "syntax.act"

    (ZIt) = find_type ( algebra, (ZIi) ) ;
#line 1693 "syntax.c"
			}
			/* END OF ACTION: find-type */
		}
		break;
	case 8:
		{
			TYPE_P ZIs;

			ADVANCE_LEXER;
			ZRtype (&ZIs);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: list-type */
			{
#line 299 "syntax.act"

    (ZIt) = compound_type ( type_list_tag, (ZIs), 0 ) ;
#line 1713 "syntax.c"
			}
			/* END OF ACTION: list-type */
		}
		break;
	case 9:
		{
			TYPE_P ZIs;

			ADVANCE_LEXER;
			ZRtype (&ZIs);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: ptr-type */
			{
#line 288 "syntax.act"

    (ZIt) = compound_type ( type_ptr_tag, (ZIs), 0 ) ;
#line 1733 "syntax.c"
			}
			/* END OF ACTION: ptr-type */
		}
		break;
	case 10:
		{
			TYPE_P ZIs;

			ADVANCE_LEXER;
			ZRtype (&ZIs);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: stack-type */
			{
#line 310 "syntax.act"

    (ZIt) = compound_type ( type_stack_tag, (ZIs), 0 ) ;
#line 1753 "syntax.c"
			}
			/* END OF ACTION: stack-type */
		}
		break;
	case 11:
		{
			TYPE_P ZIs;

			ADVANCE_LEXER;
			ZRtype (&ZIs);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: vec-type */
			{
#line 321 "syntax.act"

    (ZIt) = compound_type ( type_vec_tag, (ZIs), 0 ) ;
#line 1773 "syntax.c"
			}
			/* END OF ACTION: vec-type */
		}
		break;
	case 12:
		{
			TYPE_P ZIs;

			ADVANCE_LEXER;
			ZRtype (&ZIs);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: vec-ptr-type */
			{
#line 332 "syntax.act"

    (ZIt) = compound_type ( type_vec_ptr_tag, (ZIs), 0 ) ;
#line 1793 "syntax.c"
			}
			/* END OF ACTION: vec-ptr-type */
		}
		break;
	case 42:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: error-type */
		{
#line 358 "syntax.act"

    error ( ERROR_SERIOUS, "Type expected" ) ;
    (ZIt) = find_type ( algebra, "ERROR!" ) ;
#line 1812 "syntax.c"
		}
		/* END OF ACTION: error-type */
	}
ZL0:;
	*ZOt = ZIt;
}

static void
ZR197(string *ZOj)
{
	string ZIj;

	switch (CURRENT_TERMINAL) {
	case 0:
		{
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 168 "syntax.act"

    ZIj = xstrdup ( token_buff ) ;
#line 1833 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 34:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: null-identifier */
			{
#line 266 "syntax.act"

    (ZIj) = NULL ;
#line 1853 "syntax.c"
			}
			/* END OF ACTION: null-identifier */
		}
		break;
	case 42:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOj = ZIj;
}

static void
ZRstructure_Hdefn(CLASS_ID_P ZIi, string ZIj, STRUCTURE_P *ZOp)
{
	STRUCTURE_P ZIp;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		COMPONENT_P_LIST ZIc;

		ZRcomponent_Hgroup (&ZIc);
		switch (CURRENT_TERMINAL) {
		case 38:
			break;
		case 42:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: make-structure */
		{
#line 718 "syntax.act"

    TYPE r ;
    TYPE_P t ;
    string nm = (ZIj) ;
    STRUCTURE_P str = NULL_ptr ( STRUCTURE ) ;
    if ( nm ) {
	r = DEREF_type ( find_type ( algebra, nm ) ) ;
	if ( IS_type_structure ( r ) ) {
	    str = DEREF_ptr ( type_structure_struc ( r ) ) ;
	    (ZIc) = ADD_list ( DEREF_list ( str_defn ( str ) ), (ZIc),
			    SIZE_ptr ( COMPONENT ) ) ;
	} else {
	    error ( ERROR_SERIOUS, "Can't inherit from %s", nm ) ;
	}
    }
    (ZIp) = MAKE_ptr ( SIZE_str ) ;
    MAKE_str ( (ZIi), str, (ZIc), 0, (ZIp) ) ;
    t = MAKE_ptr ( SIZE_type ) ;
    MAKE_type_structure ( 0, (ZIp), r ) ;
    COPY_type ( t, r ) ;
    register_type ( t ) ;
#line 1915 "syntax.c"
		}
		/* END OF ACTION: make-structure */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRcomponent_Hlist(COMPONENT_P_LIST *ZOp)
{
	COMPONENT_P_LIST ZIp;

	switch (CURRENT_TERMINAL) {
	case 0: case 8: case 9: case 10:
	case 11: case 12:
		{
			TYPE_P ZIt;
			COMPONENT_P_LIST ZIq;
			COMPONENT_P_LIST ZIr;

			ZRtype (&ZIt);
			ZRcomponent_Hdecl (ZIt, &ZIq);
			switch (CURRENT_TERMINAL) {
			case 38:
				break;
			case 42:
				RESTORE_LEXER;
				goto ZL1;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			ZRcomponent_Hlist (&ZIr);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: link-component */
			{
#line 693 "syntax.act"

    (ZIp) = APPEND_list ( (ZIq), (ZIr) ) ;
#line 1962 "syntax.c"
			}
			/* END OF ACTION: link-component */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: null-component */
			{
#line 656 "syntax.act"

    (ZIp) = NULL_list ( COMPONENT_P ) ;
#line 1974 "syntax.c"
			}
			/* END OF ACTION: null-component */
		}
		break;
	case 42:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRextended_Htype(TYPE_P *ZOt)
{
	TYPE_P ZIt;

	switch (CURRENT_TERMINAL) {
	case 2:
		{
			string ZIs;

			/* BEGINNING OF EXTRACT: string */
			{
#line 192 "syntax.act"

    ZIs = xstrdup ( token_buff ) ;
#line 2005 "syntax.c"
			}
			/* END OF EXTRACT: string */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: quoted-type */
			{
#line 344 "syntax.act"

    TYPE r ;
    (ZIt) = MAKE_ptr ( SIZE_type ) ;
    MAKE_type_quote ( 0, (ZIs), r ) ;
    COPY_type ( (ZIt), r ) ;
#line 2017 "syntax.c"
			}
			/* END OF ACTION: quoted-type */
		}
		break;
	case 0: case 8: case 9: case 10:
	case 11: case 12:
		{
			ZRtype (&ZIt);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	case 42:
		return;
	default:
		goto ZL1;
	}
	goto ZL0;
ZL1:;
	{
		/* BEGINNING OF ACTION: error-type */
		{
#line 358 "syntax.act"

    error ( ERROR_SERIOUS, "Type expected" ) ;
    (ZIt) = find_type ( algebra, "ERROR!" ) ;
#line 2046 "syntax.c"
		}
		/* END OF ACTION: error-type */
	}
ZL0:;
	*ZOt = ZIt;
}

static void
ZRargument_Hlist(ARGUMENT_P_LIST *ZOp)
{
	ARGUMENT_P_LIST ZIp;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		TYPE_P ZIt;
		ARGUMENT_P_LIST ZIq;
		ARGUMENT_P_LIST ZIr;

		ZRextended_Htype (&ZIt);
		ZRargument_Hdecl (ZIt, &ZIq);
		/* BEGINNING OF INLINE: 202 */
		{
			switch (CURRENT_TERMINAL) {
			case 38:
				{
					ADVANCE_LEXER;
					ZRargument_Hlist (&ZIr);
					if ((CURRENT_TERMINAL) == 42) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: null-argument */
					{
#line 835 "syntax.act"

    (ZIr) = NULL_list ( ARGUMENT_P ) ;
#line 2089 "syntax.c"
					}
					/* END OF ACTION: null-argument */
				}
				break;
			case 42:
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		/* END OF INLINE: 202 */
		/* BEGINNING OF ACTION: link-argument */
		{
#line 871 "syntax.act"

    (ZIp) = APPEND_list ( (ZIq), (ZIr) ) ;
#line 2105 "syntax.c"
		}
		/* END OF ACTION: link-argument */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRexpression(number *ZOn)
{
	number ZIn;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		ZRor_Hexp (&ZIn);
		if ((CURRENT_TERMINAL) == 42) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOn = ZIn;
}

static void
ZRxor_Hexp(number *ZO227)
{
	number ZI227;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		number ZIn;

		ZRand_Hexp (&ZIn);
		ZR228 (ZIn, &ZI227);
		if ((CURRENT_TERMINAL) == 42) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZO227 = ZI227;
}

static void
ZRor_Hexp(number *ZO223)
{
	number ZI223;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		number ZIn;

		ZRxor_Hexp (&ZIn);
		ZR224 (ZIn, &ZI223);
		if ((CURRENT_TERMINAL) == 42) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZO223 = ZI223;
}

static void
ZR224(number ZI222, number *ZO223)
{
	number ZI223;

ZL2_224:;
	switch (CURRENT_TERMINAL) {
	case 33:
		{
			number ZIp;
			number ZIn;

			ADVANCE_LEXER;
			ZRxor_Hexp (&ZIp);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp-or */
			{
#line 445 "syntax.act"

    (ZIn) = (ZI222) | (ZIp) ;
#line 2215 "syntax.c"
			}
			/* END OF ACTION: exp-or */
			/* BEGINNING OF INLINE: 224 */
			ZI222 = ZIn;
			goto ZL2_224;
			/* END OF INLINE: 224 */
		}
		/*UNREACHED*/
	default:
		{
			ZI223 = ZI222;
		}
		break;
	case 42:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZO223 = ZI223;
}

static void
ZRunion_Hsingle(UNION_P_LIST *ZOp)
{
	UNION_P_LIST ZIp;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		CLASS_ID_P ZIi;
		UNION_P ZIq;
		UNION_P_LIST ZIr;

		switch (CURRENT_TERMINAL) {
		case 6:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRclass_Hid (&ZIi);
		ZRunion_Hdefn_Hnew (ZIi, &ZIq);
		if ((CURRENT_TERMINAL) == 42) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: null-union */
		{
#line 917 "syntax.act"

    (ZIr) = NULL_list ( UNION_P ) ;
#line 2271 "syntax.c"
		}
		/* END OF ACTION: null-union */
		/* BEGINNING OF ACTION: join-union */
		{
#line 1000 "syntax.act"

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
#line 2279 "syntax.c"
		}
		/* END OF ACTION: join-union */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZR228(number ZI226, number *ZO227)
{
	number ZI227;

ZL2_228:;
	switch (CURRENT_TERMINAL) {
	case 40:
		{
			number ZIp;
			number ZIn;

			ADVANCE_LEXER;
			ZRand_Hexp (&ZIp);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp-xor */
			{
#line 441 "syntax.act"

    (ZIn) = (ZI226) ^ (ZIp) ;
#line 2314 "syntax.c"
			}
			/* END OF ACTION: exp-xor */
			/* BEGINNING OF INLINE: 228 */
			ZI226 = ZIn;
			goto ZL2_228;
			/* END OF INLINE: 228 */
		}
		/*UNREACHED*/
	default:
		{
			ZI227 = ZI226;
		}
		break;
	case 42:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZO227 = ZI227;
}

static void
ZR232(number ZI230, number *ZO231)
{
	number ZI231;

ZL2_232:;
	switch (CURRENT_TERMINAL) {
	case 13:
		{
			number ZIp;
			number ZIn;

			ADVANCE_LEXER;
			ZRshift_Hexp (&ZIp);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp-and */
			{
#line 437 "syntax.act"

    (ZIn) = (ZI230) & (ZIp) ;
#line 2362 "syntax.c"
			}
			/* END OF ACTION: exp-and */
			/* BEGINNING OF INLINE: 232 */
			ZI230 = ZIn;
			goto ZL2_232;
			/* END OF INLINE: 232 */
		}
		/*UNREACHED*/
	default:
		{
			ZI231 = ZI230;
		}
		break;
	case 42:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZO231 = ZI231;
}

static void
ZRenum_Hsingle(ENUM_P_LIST *ZOp)
{
	ENUM_P_LIST ZIp;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		int ZIl;
		CLASS_ID_P ZIi;
		ECONST_P_LIST ZIf;
		ECONST_P_LIST ZIe;
		ENUM_P ZIq;
		ENUM_P_LIST ZIr;

		switch (CURRENT_TERMINAL) {
		case 4:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 179 */
		{
			switch (CURRENT_TERMINAL) {
			case 26:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: zero */
					{
#line 205 "syntax.act"
 (ZIl) = 0 ; 
#line 2420 "syntax.c"
					}
					/* END OF ACTION: zero */
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: one */
					{
#line 206 "syntax.act"
 (ZIl) = 1 ; 
#line 2431 "syntax.c"
					}
					/* END OF ACTION: one */
				}
				break;
			}
		}
		/* END OF INLINE: 179 */
		ZRclass_Hid (&ZIi);
		switch (CURRENT_TERMINAL) {
		case 25:
			break;
		case 42:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 181 */
		{
			switch (CURRENT_TERMINAL) {
			case 0:
				{
					string ZIj;

					/* BEGINNING OF EXTRACT: identifier */
					{
#line 168 "syntax.act"

    ZIj = xstrdup ( token_buff ) ;
#line 2462 "syntax.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: get-enum */
					{
#line 599 "syntax.act"

    string nm = (ZIj) ;
    TYPE r = DEREF_type ( find_type ( algebra, nm ) ) ;
    if ( IS_type_enumeration ( r ) ) {
	ENUM_P en = DEREF_ptr ( type_enumeration_en ( r ) ) ;
	(ZIf) = DEREF_list ( en_consts ( en ) ) ;
	enum_value = DEREF_number ( en_order ( en ) ) ;
	enum_max = enum_value ;
    } else {
	error ( ERROR_SERIOUS, "Can't inherit from %s", nm ) ;
	(ZIf) = NULL_list ( ECONST_P ) ;
    }
#line 2481 "syntax.c"
					}
					/* END OF ACTION: get-enum */
					switch (CURRENT_TERMINAL) {
					case 34:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: null-econst */
					{
#line 456 "syntax.act"

    (ZIf) = NULL_list ( ECONST_P ) ;
#line 2500 "syntax.c"
					}
					/* END OF ACTION: null-econst */
				}
				break;
			}
		}
		/* END OF INLINE: 181 */
		switch (CURRENT_TERMINAL) {
		case 30:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRenumerator_Hlist (&ZIe);
		switch (CURRENT_TERMINAL) {
		case 15:
			break;
		case 42:
			RESTORE_LEXER;
			goto ZL1;
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
		/* BEGINNING OF ACTION: make-enum */
		{
#line 623 "syntax.act"

    TYPE r ;
    TYPE_P t ;
    (ZIe) = ADD_list ( (ZIf), (ZIe), SIZE_ptr ( ECONST ) ) ;
    (ZIq) = MAKE_ptr ( SIZE_en ) ;
    MAKE_en ( (ZIi), (ZIe), enum_max + 1, (ZIl), (ZIq) ) ;
    enum_value = 0 ;
    enum_max = 0 ;
    DESTROY_list ( enum_list, SIZE_ptr ( ECONST ) ) ;
    enum_list = NULL_list ( ECONST_P ) ;
    t = MAKE_ptr ( SIZE_type ) ;
    MAKE_type_enumeration ( 0, (ZIq), r ) ;
    COPY_type ( t, r ) ;
    register_type ( t ) ;
#line 2550 "syntax.c"
		}
		/* END OF ACTION: make-enum */
		/* BEGINNING OF ACTION: null-enum */
		{
#line 587 "syntax.act"

    (ZIr) = NULL_list ( ENUM_P ) ;
#line 2558 "syntax.c"
		}
		/* END OF ACTION: null-enum */
		/* BEGINNING OF ACTION: join-enum */
		{
#line 645 "syntax.act"

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
#line 2566 "syntax.c"
		}
		/* END OF ACTION: join-enum */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZR236(number ZI234, number *ZO235)
{
	number ZI235;

ZL2_236:;
	switch (CURRENT_TERMINAL) {
	case 28:
		{
			number ZIp;
			number ZIn;

			ADVANCE_LEXER;
			ZRadd_Hexp (&ZIp);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp-lshift */
			{
#line 429 "syntax.act"

    (ZIn) = (ZI234) << (ZIp) ;
#line 2601 "syntax.c"
			}
			/* END OF ACTION: exp-lshift */
			/* BEGINNING OF INLINE: 236 */
			ZI234 = ZIn;
			goto ZL2_236;
			/* END OF INLINE: 236 */
		}
		/*UNREACHED*/
	case 37:
		{
			number ZIp;
			number ZIn;

			ADVANCE_LEXER;
			ZRadd_Hexp (&ZIp);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp-rshift */
			{
#line 433 "syntax.act"

    (ZIn) = (ZI234) >> (ZIp) ;
#line 2626 "syntax.c"
			}
			/* END OF ACTION: exp-rshift */
			/* BEGINNING OF INLINE: 236 */
			ZI234 = ZIn;
			goto ZL2_236;
			/* END OF INLINE: 236 */
		}
		/*UNREACHED*/
	default:
		{
			ZI235 = ZI234;
		}
		break;
	case 42:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZO235 = ZI235;
}

static void
ZRfield_Hid_Hlist(int ZIn, FIELD_P_LIST *ZOp)
{
	FIELD_P_LIST ZIp;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		string ZIi;
		COMPONENT_P_LIST ZIc;
		FIELD_P ZIq;
		FIELD_P_LIST ZIr;

		switch (CURRENT_TERMINAL) {
		case 0:
			/* BEGINNING OF EXTRACT: identifier */
			{
#line 168 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 2672 "syntax.c"
			}
			/* END OF EXTRACT: identifier */
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: null-component */
		{
#line 656 "syntax.act"

    (ZIc) = NULL_list ( COMPONENT_P ) ;
#line 2685 "syntax.c"
		}
		/* END OF ACTION: null-component */
		/* BEGINNING OF ACTION: make-field */
		{
#line 770 "syntax.act"

    (ZIq) = MAKE_ptr ( SIZE_fld ) ;
    MAKE_fld ( (ZIi), 0, (ZIn), 0, NULL_ptr ( FIELD ),  (ZIc), (ZIq) ) ;
    no_fields++ ;
#line 2695 "syntax.c"
		}
		/* END OF ACTION: make-field */
		/* BEGINNING OF INLINE: 194 */
		{
			switch (CURRENT_TERMINAL) {
			case 20:
				{
					ADVANCE_LEXER;
					ZRfield_Hid_Hlist (ZIn, &ZIr);
					if ((CURRENT_TERMINAL) == 42) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: null-field */
					{
#line 758 "syntax.act"

    (ZIr) = NULL_list ( FIELD_P ) ;
#line 2718 "syntax.c"
					}
					/* END OF ACTION: null-field */
				}
				break;
			}
		}
		/* END OF INLINE: 194 */
		/* BEGINNING OF ACTION: join-field */
		{
#line 783 "syntax.act"

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
#line 2731 "syntax.c"
		}
		/* END OF ACTION: join-field */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZR240(number ZI238, number *ZO239)
{
	number ZI239;

ZL2_240:;
	switch (CURRENT_TERMINAL) {
	case 29:
		{
			number ZIp;
			number ZIn;

			ADVANCE_LEXER;
			ZRmult_Hexp (&ZIp);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp-minus */
			{
#line 425 "syntax.act"

    (ZIn) = (ZI238) - (ZIp) ;
#line 2766 "syntax.c"
			}
			/* END OF ACTION: exp-minus */
			/* BEGINNING OF INLINE: 240 */
			ZI238 = ZIn;
			goto ZL2_240;
			/* END OF INLINE: 240 */
		}
		/*UNREACHED*/
	case 34:
		{
			number ZIp;
			number ZIn;

			ADVANCE_LEXER;
			ZRmult_Hexp (&ZIp);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp-plus */
			{
#line 421 "syntax.act"

    (ZIn) = (ZI238) + (ZIp) ;
#line 2791 "syntax.c"
			}
			/* END OF ACTION: exp-plus */
			/* BEGINNING OF INLINE: 240 */
			ZI238 = ZIn;
			goto ZL2_240;
			/* END OF INLINE: 240 */
		}
		/*UNREACHED*/
	default:
		{
			ZI239 = ZI238;
		}
		break;
	case 42:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZO239 = ZI239;
}

static void
ZRfield_Hlist(FIELD_P_LIST *ZOp)
{
	FIELD_P_LIST ZIp;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		int ZIn;
		FIELD_P_LIST ZIq;
		string ZIj;
		COMPONENT_P_LIST ZIc;
		FIELD_P_LIST ZIr;

		/* BEGINNING OF INLINE: 196 */
		{
			switch (CURRENT_TERMINAL) {
			case 27:
				{
					ADVANCE_LEXER;
					ZR250 (&ZIn);
					if ((CURRENT_TERMINAL) == 42) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: zero */
					{
#line 205 "syntax.act"
 (ZIn) = 0 ; 
#line 2850 "syntax.c"
					}
					/* END OF ACTION: zero */
				}
				break;
			}
		}
		/* END OF INLINE: 196 */
		ZRfield_Hid_Hlist (ZIn, &ZIq);
		switch (CURRENT_TERMINAL) {
		case 14:
			break;
		case 42:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZR197 (&ZIj);
		ZRcomponent_Hgroup (&ZIc);
		if ((CURRENT_TERMINAL) == 42) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: set-field-cmp */
		{
#line 807 "syntax.act"

    int n = 0 ;
    FIELD_P_LIST p = (ZIq) ;
    FIELD_P b = NULL_ptr ( FIELD ) ;
    if ( (ZIj) ) {
	b = MAKE_ptr ( SIZE_fld ) ;
	MAKE_fld ( (ZIj), 0, 0, 0, NULL_ptr ( FIELD ),
		   NULL_list ( COMPONENT_P ), b ) ;
    }
    while ( !IS_NULL_list ( p ) ) {
	FIELD_P q = DEREF_ptr ( HEAD_list ( p ) ) ;
	COPY_ptr ( fld_base ( q ), b ) ;
	COPY_list ( fld_defn ( q ), (ZIc) ) ;
	p = TAIL_list ( p ) ;
	n++ ;
    }
    if ( n >= 2 ) {
	FIELD_P q = DEREF_ptr ( HEAD_list ( (ZIq) ) ) ;
	COPY_int ( fld_set ( q ), n ) ;
    }
#line 2898 "syntax.c"
		}
		/* END OF ACTION: set-field-cmp */
		/* BEGINNING OF INLINE: 198 */
		{
			switch (CURRENT_TERMINAL) {
			case 20:
				{
					ADVANCE_LEXER;
					ZRfield_Hlist (&ZIr);
					if ((CURRENT_TERMINAL) == 42) {
						RESTORE_LEXER;
						goto ZL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: null-field */
					{
#line 758 "syntax.act"

    (ZIr) = NULL_list ( FIELD_P ) ;
#line 2921 "syntax.c"
					}
					/* END OF ACTION: null-field */
				}
				break;
			}
		}
		/* END OF INLINE: 198 */
		/* BEGINNING OF ACTION: link-field */
		{
#line 794 "syntax.act"

    (ZIp) = APPEND_list ( (ZIq), (ZIr) ) ;
#line 2934 "syntax.c"
		}
		/* END OF ACTION: link-field */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZRunion_Hdefn_Hnew(CLASS_ID_P ZIi, UNION_P *ZOp)
{
	UNION_P ZIp;

	if ((CURRENT_TERMINAL) == 42) {
		return;
	}
	{
		COMPONENT_P_LIST ZIc;
		string ZIj;
		FIELD_P_LIST ZIf;
		MAP_P_LIST ZIm;

		switch (CURRENT_TERMINAL) {
		case 25:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 207 */
		{
			switch (CURRENT_TERMINAL) {
			case 30:
				{
					ZRcomponent_Hgroup (&ZIc);
					if ((CURRENT_TERMINAL) == 42) {
						RESTORE_LEXER;
						goto ZL1;
					}
					/* BEGINNING OF ACTION: null-identifier */
					{
#line 266 "syntax.act"

    (ZIj) = NULL ;
#line 2982 "syntax.c"
					}
					/* END OF ACTION: null-identifier */
				}
				break;
			case 0:
				{
					/* BEGINNING OF ACTION: null-component */
					{
#line 656 "syntax.act"

    (ZIc) = NULL_list ( COMPONENT_P ) ;
#line 2994 "syntax.c"
					}
					/* END OF ACTION: null-component */
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 168 "syntax.act"

    ZIj = xstrdup ( token_buff ) ;
#line 3002 "syntax.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto ZL1;
			}
		}
		/* END OF INLINE: 207 */
		switch (CURRENT_TERMINAL) {
		case 34:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		switch (CURRENT_TERMINAL) {
		case 30:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		ZRfield_Hlist (&ZIf);
		switch (CURRENT_TERMINAL) {
		case 15:
			break;
		case 42:
			RESTORE_LEXER;
			goto ZL1;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: 208 */
		{
			switch (CURRENT_TERMINAL) {
			case 18:
				{
					ADVANCE_LEXER;
					switch (CURRENT_TERMINAL) {
					case 32:
						break;
					default:
						goto ZL1;
					}
					ADVANCE_LEXER;
					ZRmap_Hlist (&ZIm);
					switch (CURRENT_TERMINAL) {
					case 17:
						break;
					case 42:
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
					/* BEGINNING OF ACTION: null-map */
					{
#line 882 "syntax.act"

    (ZIm) = NULL_list ( MAP_P ) ;
#line 3071 "syntax.c"
					}
					/* END OF ACTION: null-map */
				}
				break;
			}
		}
		/* END OF INLINE: 208 */
		switch (CURRENT_TERMINAL) {
		case 38:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: make-union */
		{
#line 932 "syntax.act"

    TYPE r ;
    TYPE_P t ;
    int tag = 0 ;
    string nm = (ZIj) ;
    FIELD_P_LIST p = (ZIf) ;
    UNION_P un = NULL_ptr ( UNION ) ;

    /* Deal with overall inheritance */
    if ( nm ) {
	r = DEREF_type ( find_type ( algebra, nm ) ) ;
	if ( IS_type_onion ( r ) ) {
	    un = DEREF_ptr ( type_onion_un ( r ) ) ;
	    (ZIc) = ADD_list ( DEREF_list ( un_s_defn ( un ) ), (ZIc),
			    SIZE_ptr ( COMPONENT ) ) ;
	    (ZIf) = ADD_list ( DEREF_list ( un_u_defn ( un ) ), p,
			    SIZE_ptr ( FIELD ) ) ;
	    (ZIm) = ADD_list ( DEREF_list ( un_map ( un ) ), (ZIm),
			    SIZE_ptr ( MAP ) ) ;
	    tag = DEREF_int ( un_no_fields ( un ) ) ;
	    no_fields += tag ;
	} else {
	    error ( ERROR_SERIOUS, "Can't inherit from %s", nm ) ;
	}
    }

    /* Deal with inheritance of fields and field tags */
    while ( !IS_NULL_list ( p ) ) {
	FIELD_P q = DEREF_ptr ( HEAD_list ( p ) ) ;
	FIELD_P b = DEREF_ptr ( fld_base ( q ) ) ;
	if ( !IS_NULL_ptr ( b ) ) {
	    int ok = 0 ;
	    FIELD_P_LIST pp = (ZIf) ;
	    string n = DEREF_string ( fld_name ( b ) ) ;
	    while ( !IS_NULL_list ( pp ) ) {
		FIELD_P qq = DEREF_ptr ( HEAD_list ( pp ) ) ;
		string nn = DEREF_string ( fld_name ( qq ) ) ;
		if ( !strcmp( n, nn ) ) {
		    COMPONENT_P_LIST cc = DEREF_list ( fld_defn ( qq ) ) ;
		    COMPONENT_P_LIST c = DEREF_list ( fld_defn ( q ) ) ;
		    c = ADD_list ( cc, c, SIZE_ptr ( COMPONENT ) ) ;
		    COPY_list ( fld_defn ( q ), c ) ;
		    COPY_ptr ( fld_base ( q ), qq ) ;
		    ok = 1 ;
		    break ;
		}
		pp = TAIL_list ( pp ) ;
	    }
	    if ( !ok ) error ( ERROR_SERIOUS, "Can't find field %s", n ) ;
	}
	COPY_int ( fld_tag ( q ), tag++ ) ;
	p = TAIL_list ( p ) ;
    }

    /* Construct output */
    (ZIp) = MAKE_ptr ( SIZE_un ) ;
    MAKE_un ( (ZIi), un, (ZIc), (ZIf), (ZIm), no_fields, (ZIp) ) ;
    no_fields = 0 ;
    t = MAKE_ptr ( SIZE_type ) ;
    MAKE_type_onion ( 0, (ZIp), r ) ;
    COPY_type ( t, r ) ;
    register_type ( t ) ;
#line 3151 "syntax.c"
		}
		/* END OF ACTION: make-union */
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZOp = ZIp;
}

static void
ZR244(number ZI242, number *ZO243)
{
	number ZI243;

ZL2_244:;
	switch (CURRENT_TERMINAL) {
	case 22:
		{
			number ZIp;
			number ZIn;

			ADVANCE_LEXER;
			ZRunary_Hexp (&ZIp);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp-div */
			{
#line 403 "syntax.act"

    if ( (ZIp) == 0 ) {
	error ( ERROR_SERIOUS, "Division by zero" ) ;
	(ZIn) = 0 ;
    } else {
	(ZIn) = (ZI242) / (ZIp) ;
    }
#line 3191 "syntax.c"
			}
			/* END OF ACTION: exp-div */
			/* BEGINNING OF INLINE: 244 */
			ZI242 = ZIn;
			goto ZL2_244;
			/* END OF INLINE: 244 */
		}
		/*UNREACHED*/
	case 36:
		{
			number ZIp;
			number ZIn;

			ADVANCE_LEXER;
			ZRunary_Hexp (&ZIp);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp-rem */
			{
#line 412 "syntax.act"

    if ( (ZIp) == 0 ) {
	error ( ERROR_SERIOUS, "Division by zero" ) ;
	(ZIn) = 0 ;
    } else {
	(ZIn) = (ZI242) % (ZIp) ;
    }
#line 3221 "syntax.c"
			}
			/* END OF ACTION: exp-rem */
			/* BEGINNING OF INLINE: 244 */
			ZI242 = ZIn;
			goto ZL2_244;
			/* END OF INLINE: 244 */
		}
		/*UNREACHED*/
	case 39:
		{
			number ZIp;
			number ZIn;

			ADVANCE_LEXER;
			ZRunary_Hexp (&ZIp);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp-mult */
			{
#line 399 "syntax.act"

    (ZIn) = (ZI242) * (ZIp) ;
#line 3246 "syntax.c"
			}
			/* END OF ACTION: exp-mult */
			/* BEGINNING OF INLINE: 244 */
			ZI242 = ZIn;
			goto ZL2_244;
			/* END OF INLINE: 244 */
		}
		/*UNREACHED*/
	default:
		{
			ZI243 = ZI242;
		}
		break;
	case 42:
		return;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (42);
	return;
ZL0:;
	*ZO243 = ZI243;
}

static void
ZR248(CLASS_ID_P *ZI247)
{
	switch (CURRENT_TERMINAL) {
	case 0: case 8: case 9: case 10:
	case 11: case 12:
		{
			IDENTITY_P ZIq;
			IDENTITY_P_LIST ZIr;
			IDENTITY_P_LIST ZIi;

			ZRidentity_Hdefn (*ZI247, &ZIq);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: null-identity */
			{
#line 546 "syntax.act"

    (ZIr) = NULL_list ( IDENTITY_P ) ;
#line 3292 "syntax.c"
			}
			/* END OF ACTION: null-identity */
			/* BEGINNING OF ACTION: join-identity */
			{
#line 576 "syntax.act"

    CONS_ptr ( (ZIq), (ZIr), (ZIi) ) ;
#line 3300 "syntax.c"
			}
			/* END OF ACTION: join-identity */
			/* BEGINNING OF ACTION: add-identity */
			{
#line 1083 "syntax.act"

    algebra->identities = APPEND_list ( algebra->identities, (ZIi) ) ;
#line 3308 "syntax.c"
			}
			/* END OF ACTION: add-identity */
		}
		break;
	case 2:
		{
			PRIMITIVE_P ZIq;
			PRIMITIVE_P_LIST ZIr;
			PRIMITIVE_P_LIST ZIp;

			ZRprimitive_Hdefn (*ZI247, &ZIq);
			if ((CURRENT_TERMINAL) == 42) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: null-primitive */
			{
#line 505 "syntax.act"

    (ZIr) = NULL_list ( PRIMITIVE_P ) ;
#line 3329 "syntax.c"
			}
			/* END OF ACTION: null-primitive */
			/* BEGINNING OF ACTION: join-primitive */
			{
#line 535 "syntax.act"

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
#line 3337 "syntax.c"
			}
			/* END OF ACTION: join-primitive */
			/* BEGINNING OF ACTION: add-primitive */
			{
#line 1072 "syntax.act"

    algebra->primitives = APPEND_list ( algebra->primitives, (ZIp) ) ;
#line 3345 "syntax.c"
			}
			/* END OF ACTION: add-primitive */
		}
		break;
	case 42:
		return;
	default:
		goto ZL1;
	}
	return;
ZL1:;
	SAVE_LEXER (42);
	return;
}

static void
ZR249(int *ZOn)
{
	int ZIn;

	switch (CURRENT_TERMINAL) {
	case 18:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: three */
			{
#line 208 "syntax.act"
 (ZIn) = 3 ; 
#line 3374 "syntax.c"
			}
			/* END OF ACTION: three */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: one */
			{
#line 206 "syntax.act"
 (ZIn) = 1 ; 
#line 3385 "syntax.c"
			}
			/* END OF ACTION: one */
		}
		break;
	case 42:
		return;
	}
	*ZOn = ZIn;
}

static void
ZR250(int *ZOn)
{
	int ZIn;

	switch (CURRENT_TERMINAL) {
	case 27:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: two */
			{
#line 207 "syntax.act"
 (ZIn) = 2 ; 
#line 3409 "syntax.c"
			}
			/* END OF ACTION: two */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: one */
			{
#line 206 "syntax.act"
 (ZIn) = 1 ; 
#line 3420 "syntax.c"
			}
			/* END OF ACTION: one */
		}
		break;
	case 42:
		return;
	}
	*ZOn = ZIn;
}

static void
ZR251(string *ZIa)
{
	switch (CURRENT_TERMINAL) {
	case 19:
		{
			string ZIi;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 0:
				/* BEGINNING OF EXTRACT: identifier */
				{
#line 168 "syntax.act"

    ZIi = xstrdup ( token_buff ) ;
#line 3447 "syntax.c"
				}
				/* END OF EXTRACT: identifier */
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: import-one */
			{
#line 1034 "syntax.act"

    import_type ( (*ZIa), (ZIi) ) ;
#line 3460 "syntax.c"
			}
			/* END OF ACTION: import-one */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: import-all */
			{
#line 1023 "syntax.act"

    import_algebra ( (*ZIa) ) ;
#line 3472 "syntax.c"
			}
			/* END OF ACTION: import-all */
		}
		break;
	case 42:
		return;
	}
	return;
ZL1:;
	SAVE_LEXER (42);
	return;
}

/* BEGINNING OF TRAILER */

#line 1121 "syntax.act"

#line 3490 "syntax.c"

/* END OF FILE */
