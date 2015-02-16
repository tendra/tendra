/*
 * Automatically generated from the files:
 *	psyntax.sid
 * and
 *	psyntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#define __SID_SPLIT
#line 177 "psyntax.act"


/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>

#include "config.h"
#include "c_types.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "access.h"
#include "allocate.h"
#include "assign.h"
#include "basetype.h"
#include "cast.h"
#include "chktype.h"
#include "class.h"
#include "constant.h"
#include "construct.h"
#include "convert.h"
#include "declare.h"
#include "derive.h"
#include "exception.h"
#include "expression.h"
#include "function.h"
#include "hash.h"
#include "identifier.h"
#include "initialise.h"
#include "inttype.h"
#include "label.h"
#include "lex.h"
#include "literal.h"
#include "member.h"
#include "namespace.h"
#include "parse.h"
#include "pragma.h"
#include "predict.h"
#include "preproc.h"
#include "printf.h"
#include "redeclare.h"
#include "rewrite.h"
#include "statement.h"
#include "symbols.h"
#include "template.h"
#include "tokdef.h"
#include "token.h"
#include "typeid.h"
#include "variable.h"


/*
    These are the aliases for the compound types used in the parser.
*/

typedef LIST(IDENTIFIER) SID_LIST_ID;


/*
     The function declarations are included at this point so that the
     type definitions are in scope.
*/

#include "psyntax.h"
extern void parse_tok_type(TYPE *);
extern void parse_mem_type(TYPE *);
extern void parse_operator(IDENTIFIER *);


/*
    The output of sid is automatically generated.  Hence it is not
    necessarily appropriate to apply the same level of checking to this
    as to the rest of the program.  These pragmas describe the relaxations
    allowed for the sid output.
*/

#if FS_TENDRA
#pragma TenDRA begin
#pragma TenDRA variable analysis off
#ifndef OLD_PRODUCER
#pragma TenDRA unreachable code allow
#endif
#endif


#line 112 "psyntax1.c"

/* BEGINNING OF STATIC VARIABLES */

int XI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

void
XRbound_Htok_Hpars(SID_LIST_ID *XOp)
{
	SID_LIST_ID XIp;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		IDENTIFIER XIid;
		SID_LIST_ID XIq;

		XRbound_Htok_Hparam (&XIid);
		/* BEGINNING OF INLINE: 405 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					XR834 (&XIq);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto XL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: list_id_null */
					{
#line 531 "psyntax.act"

    (XIq) = NULL_list ( IDENTIFIER ) ;
#line 153 "psyntax1.c"
					}
					/* END OF ACTION: list_id_null */
				}
				break;
			case 355:
				RESTORE_LEXER;
				goto XL1;
			}
		}
		/* END OF INLINE: 405 */
		/* BEGINNING OF ACTION: list_id_cons */
		{
#line 535 "psyntax.act"

    CONS_id ( (XIid), (XIq), (XIp) ) ;
#line 169 "psyntax1.c"
		}
		/* END OF ACTION: list_id_cons */
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOp = XIp;
}

void
XRerror_Hstate(unsigned *XOe)
{
	unsigned XIe;

	switch (CURRENT_TERMINAL) {
	case 271:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: error_off */
			{
#line 833 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_OFF ; 
#line 194 "psyntax1.c"
			}
			/* END OF ACTION: error_off */
		}
		break;
	case 272:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: error_on */
			{
#line 832 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_ON ; 
#line 206 "psyntax1.c"
			}
			/* END OF ACTION: error_on */
		}
		break;
	case 331:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: error_warning */
			{
#line 834 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_WARN ; 
#line 218 "psyntax1.c"
			}
			/* END OF ACTION: error_warning */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOe = XIe;
}

void
XRcast_Hstate(unsigned *XOc)
{
	unsigned XIc;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		unsigned XI837;

		XRcast_Hcommand (&XI837);
		XR839 (&XI837, &XIc);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto XL1;
		}
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOc = XIc;
}

void
XRkeyword_Hid(IDENTIFIER *XOid)
{
	IDENTIFIER XIid;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		switch (CURRENT_TERMINAL) {
		case 251:
			break;
		default:
			goto XL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: rescan_id */
		{
#line 1184 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 286 "psyntax1.c"
		}
		/* END OF ACTION: rescan_id */
		/* BEGINNING OF INLINE: any-identifier */
		{
			switch (CURRENT_TERMINAL) {
			case 1:
				{
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 206 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 299 "psyntax1.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			case 3:
				{
					/* BEGINNING OF EXTRACT: namespace-name */
					{
#line 214 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 312 "psyntax1.c"
					}
					/* END OF EXTRACT: namespace-name */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: statement-name */
					{
#line 218 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 325 "psyntax1.c"
					}
					/* END OF EXTRACT: statement-name */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: type-name */
					{
#line 210 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 338 "psyntax1.c"
					}
					/* END OF EXTRACT: type-name */
					ADVANCE_LEXER;
				}
				break;
			default:
				goto XL1;
			}
		}
		/* END OF INLINE: any-identifier */
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOid = XIid;
}

void
XRtoken_Hrule(void)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TOKEN XItok;
		int XIt;
		IDENTIFIER XIa;
		IDENTIFIER XIb;

		switch (CURRENT_TERMINAL) {
		case 312:
			break;
		default:
			goto XL1;
		}
		ADVANCE_LEXER;
		XRtoken_Hintroduction (&XItok);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto XL1;
		}
		/* BEGINNING OF ACTION: rescan_tag_line */
		{
#line 1217 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 392 "psyntax1.c"
		}
		/* END OF ACTION: rescan_tag_line */
		/* BEGINNING OF INLINE: 458 */
		{
			{
				/* BEGINNING OF ACTION: is_operator */
				{
#line 400 "psyntax.act"

    (XI0) = predict_operator () ;
#line 403 "psyntax1.c"
				}
				/* END OF ACTION: is_operator */
				if (!XI0)
					goto XL3;
				/* BEGINNING OF ACTION: parse_operator */
				{
#line 395 "psyntax.act"

    (XIa) = DEREF_id ( hashid_id ( KEYWORD ( lex_zzzz ) ) ) ;
    parse_operator ( &(XIa) ) ;
#line 414 "psyntax1.c"
				}
				/* END OF ACTION: parse_operator */
				/* BEGINNING OF ACTION: bool_false */
				{
#line 1167 "psyntax.act"
 (XIt) = 0 ; 
#line 421 "psyntax1.c"
				}
				/* END OF ACTION: bool_false */
				goto XL2;
			}
			/*UNREACHED*/
		XL3:;
			switch (CURRENT_TERMINAL) {
			case 1: case 2: case 3: case 4:
			case 308:
				{
					XRtag_Hopt (&XIt);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto XL1;
					}
					/* BEGINNING OF ACTION: rescan_id */
					{
#line 1184 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 445 "psyntax1.c"
					}
					/* END OF ACTION: rescan_id */
					/* BEGINNING OF INLINE: any-identifier */
					{
						switch (CURRENT_TERMINAL) {
						case 1:
							{
								/* BEGINNING OF EXTRACT: identifier */
								{
#line 206 "psyntax.act"

    XIa = crt_token->pp_data.id.use ;
#line 458 "psyntax1.c"
								}
								/* END OF EXTRACT: identifier */
								ADVANCE_LEXER;
							}
							break;
						case 3:
							{
								/* BEGINNING OF EXTRACT: namespace-name */
								{
#line 214 "psyntax.act"

    XIa = crt_token->pp_data.id.use ;
#line 471 "psyntax1.c"
								}
								/* END OF EXTRACT: namespace-name */
								ADVANCE_LEXER;
							}
							break;
						case 4:
							{
								/* BEGINNING OF EXTRACT: statement-name */
								{
#line 218 "psyntax.act"

    XIa = crt_token->pp_data.id.use ;
#line 484 "psyntax1.c"
								}
								/* END OF EXTRACT: statement-name */
								ADVANCE_LEXER;
							}
							break;
						case 2:
							{
								/* BEGINNING OF EXTRACT: type-name */
								{
#line 210 "psyntax.act"

    XIa = crt_token->pp_data.id.use ;
#line 497 "psyntax1.c"
								}
								/* END OF EXTRACT: type-name */
								ADVANCE_LEXER;
							}
							break;
						default:
							goto XL1;
						}
					}
					/* END OF INLINE: any-identifier */
				}
				break;
			default:
				goto XL1;
			}
		XL2:;
		}
		/* END OF INLINE: 458 */
		/* BEGINNING OF INLINE: hash */
		{
			{
				switch (CURRENT_TERMINAL) {
				case 51:
					break;
				default:
					goto XL1;
				}
				ADVANCE_LEXER;
			}
		}
		/* END OF INLINE: hash */
		/* BEGINNING OF ACTION: rescan_id */
		{
#line 1184 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 537 "psyntax1.c"
		}
		/* END OF ACTION: rescan_id */
		/* BEGINNING OF INLINE: 459 */
		{
			switch (CURRENT_TERMINAL) {
			case 59:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: id_anon */
					{
#line 451 "psyntax.act"

    HASHID nm = lookup_anon () ;
    (XIb) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 554 "psyntax1.c"
					}
					/* END OF ACTION: id_anon */
				}
				break;
			case 1: case 2: case 3: case 4:
				{
					/* BEGINNING OF INLINE: any-identifier */
					{
						switch (CURRENT_TERMINAL) {
						case 1:
							{
								/* BEGINNING OF EXTRACT: identifier */
								{
#line 206 "psyntax.act"

    XIb = crt_token->pp_data.id.use ;
#line 571 "psyntax1.c"
								}
								/* END OF EXTRACT: identifier */
								ADVANCE_LEXER;
							}
							break;
						case 3:
							{
								/* BEGINNING OF EXTRACT: namespace-name */
								{
#line 214 "psyntax.act"

    XIb = crt_token->pp_data.id.use ;
#line 584 "psyntax1.c"
								}
								/* END OF EXTRACT: namespace-name */
								ADVANCE_LEXER;
							}
							break;
						case 4:
							{
								/* BEGINNING OF EXTRACT: statement-name */
								{
#line 218 "psyntax.act"

    XIb = crt_token->pp_data.id.use ;
#line 597 "psyntax1.c"
								}
								/* END OF EXTRACT: statement-name */
								ADVANCE_LEXER;
							}
							break;
						case 2:
							{
								/* BEGINNING OF EXTRACT: type-name */
								{
#line 210 "psyntax.act"

    XIb = crt_token->pp_data.id.use ;
#line 610 "psyntax1.c"
								}
								/* END OF EXTRACT: type-name */
								ADVANCE_LEXER;
							}
							break;
						default:
							goto XL1;
						}
					}
					/* END OF INLINE: any-identifier */
				}
				break;
			default:
				{
					XIb = XIa;
				}
				break;
			}
		}
		/* END OF INLINE: 459 */
		/* BEGINNING OF ACTION: token_decl */
		{
#line 652 "psyntax.act"

    IGNORE make_token_decl ( (XItok), (XIt), (XIa), (XIb) ) ;
#line 636 "psyntax1.c"
		}
		/* END OF ACTION: token_decl */
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

void
XR781(IDENTIFIER XI779, IDENTIFIER *XO780)
{
	IDENTIFIER XI780;

XL2_781:;
	switch (CURRENT_TERMINAL) {
	case 46:
		{
			IDENTIFIER XImem;
			IDENTIFIER XIid;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1184 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 667 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 206 "psyntax.act"

    XImem = crt_token->pp_data.id.use ;
#line 680 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 214 "psyntax.act"

    XImem = crt_token->pp_data.id.use ;
#line 693 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 218 "psyntax.act"

    XImem = crt_token->pp_data.id.use ;
#line 706 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 210 "psyntax.act"

    XImem = crt_token->pp_data.id.use ;
#line 719 "psyntax1.c"
						}
						/* END OF EXTRACT: type-name */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: any-identifier */
			/* BEGINNING OF ACTION: token_selector */
			{
#line 664 "psyntax.act"

    (XIid) = find_mem_token ( (XI779), (XImem) ) ;
#line 735 "psyntax1.c"
			}
			/* END OF ACTION: token_selector */
			/* BEGINNING OF INLINE: 781 */
			XI779 = XIid;
			goto XL2_781;
			/* END OF INLINE: 781 */
		}
		/*UNREACHED*/
	default:
		{
			XI780 = XI779;
		}
		break;
	case 355:
		return;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XO780 = XI780;
}

void
XR783(int *XIn)
{
	switch (CURRENT_TERMINAL) {
	case 179:
		{
			int XIe;

			ADVANCE_LEXER;
			XRoption_Hnumber (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: error_state */
			{
#line 837 "psyntax.act"

    set_error_sev ( (*XIn), (XIe) ) ;
#line 779 "psyntax1.c"
			}
			/* END OF ACTION: error_state */
		}
		break;
	case 172: case 205: case 271: case 272:
	case 331:
		{
			int XIe;

			XRerror_Hseverity (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: error_state */
			{
#line 837 "psyntax.act"

    set_error_sev ( (*XIn), (XIe) ) ;
#line 799 "psyntax1.c"
			}
			/* END OF ACTION: error_state */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

void
XR784(void)
{
	switch (CURRENT_TERMINAL) {
	case 262:
		{
			IDENTIFIER XIid;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 213:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1184 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 839 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 206 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 852 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 214 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 865 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 218 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 878 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 210 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 891 "psyntax1.c"
						}
						/* END OF EXTRACT: type-name */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: any-identifier */
			/* BEGINNING OF ACTION: check_begin */
			{
#line 777 "psyntax.act"

    begin_option ( (XIid) ) ;
#line 907 "psyntax1.c"
			}
			/* END OF ACTION: check_begin */
		}
		break;
	default:
		{
			IDENTIFIER XIid;

			/* BEGINNING OF ACTION: id_none */
			{
#line 444 "psyntax.act"

    (XIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 923 "psyntax1.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: check_begin */
			{
#line 777 "psyntax.act"

    begin_option ( (XIid) ) ;
#line 931 "psyntax1.c"
			}
			/* END OF ACTION: check_begin */
		}
		break;
	case 355:
		return;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

void
XR785(void)
{
	switch (CURRENT_TERMINAL) {
	case 211:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: decl_block_end */
			{
#line 798 "psyntax.act"

    IGNORE end_decl_block ( NULL_id, 1 ) ;
#line 957 "psyntax1.c"
			}
			/* END OF ACTION: decl_block_end */
		}
		break;
	case 1: case 2: case 3: case 4:
		{
			IDENTIFIER XIid;

			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1184 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 974 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 206 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 987 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 214 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1000 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 218 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1013 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 210 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1026 "psyntax1.c"
						}
						/* END OF EXTRACT: type-name */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: any-identifier */
			switch (CURRENT_TERMINAL) {
			case 182:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: decl_block_begin */
			{
#line 793 "psyntax.act"

    begin_decl_block ( (XIid) ) ;
#line 1049 "psyntax1.c"
			}
			/* END OF ACTION: decl_block_begin */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

void
XR786(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 197:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_decl_cond */
			{
#line 1017 "psyntax.act"
 (XIn) = OPT_decl_cond ; 
#line 1078 "psyntax1.c"
			}
			/* END OF ACTION: opt_decl_cond */
		}
		break;
	case 257:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_cond_lvalue */
			{
#line 999 "psyntax.act"
 (XIn) = OPT_cond_lvalue ; 
#line 1090 "psyntax1.c"
			}
			/* END OF ACTION: opt_cond_lvalue */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
}

void
XR787(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 183:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 110:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 313:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_bitf_type */
			{
#line 992 "psyntax.act"
 (XIn) = OPT_bitf_type ; 
#line 1135 "psyntax1.c"
			}
			/* END OF ACTION: opt_bitf_type */
		}
		break;
	case 42:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_comma_extra */
			{
#line 996 "psyntax.act"
 (XIn) = OPT_comma_extra ; 
#line 1147 "psyntax1.c"
			}
			/* END OF ACTION: opt_comma_extra */
		}
		break;
	case 258:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 201:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_macro_redef */
			{
#line 1063 "psyntax.act"
 (XIn) = OPT_macro_redef ; 
#line 1166 "psyntax1.c"
			}
			/* END OF ACTION: opt_macro_redef */
		}
		break;
	case 77:
		{
			ADVANCE_LEXER;
			XR840 (&XIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 313:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 201:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_type_redef */
			{
#line 1091 "psyntax.act"
 (XIn) = OPT_type_redef ; 
#line 1195 "psyntax1.c"
			}
			/* END OF ACTION: opt_type_redef */
		}
		break;
	case 47: case 210:
		{
			/* BEGINNING OF INLINE: ellipsis-aux */
			{
				switch (CURRENT_TERMINAL) {
				case 47:
					{
						ADVANCE_LEXER;
					}
					break;
				case 210:
					{
						ADVANCE_LEXER;
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: ellipsis-aux */
			/* BEGINNING OF ACTION: opt_ellipsis_extra */
			{
#line 1030 "psyntax.act"
 (XIn) = OPT_ellipsis_extra ; 
#line 1224 "psyntax1.c"
			}
			/* END OF ACTION: opt_ellipsis_extra */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
}

void
XRdirective_Hstate(unsigned *XOe, unsigned *XOi)
{
	unsigned XIe;
	unsigned XIi;

	switch (CURRENT_TERMINAL) {
	case 205:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: error_on */
			{
#line 832 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_ON ; 
#line 1256 "psyntax1.c"
			}
			/* END OF ACTION: error_on */
			/* BEGINNING OF ACTION: error_on */
			{
#line 832 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_ON ; 
#line 1263 "psyntax1.c"
			}
			/* END OF ACTION: error_on */
		}
		break;
	case 65: case 172: case 331:
		{
			unsigned XIa;
			unsigned XIb;

			/* BEGINNING OF INLINE: 719 */
			{
				switch (CURRENT_TERMINAL) {
				case 65:
					{
						ADVANCE_LEXER;
						switch (CURRENT_TERMINAL) {
						case 235:
							break;
						default:
							goto XL1;
						}
						ADVANCE_LEXER;
						switch (CURRENT_TERMINAL) {
						case 39:
							break;
						default:
							goto XL1;
						}
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: error_on */
						{
#line 832 "psyntax.act"
 (XIa) = ( unsigned ) OPTION_ON ; 
#line 1297 "psyntax1.c"
						}
						/* END OF ACTION: error_on */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: error_off */
						{
#line 833 "psyntax.act"
 (XIa) = ( unsigned ) OPTION_OFF ; 
#line 1308 "psyntax1.c"
						}
						/* END OF ACTION: error_off */
					}
					break;
				}
			}
			/* END OF INLINE: 719 */
			/* BEGINNING OF INLINE: 720 */
			{
				switch (CURRENT_TERMINAL) {
				case 172:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: error_off */
						{
#line 833 "psyntax.act"
 (XIb) = ( unsigned ) OPTION_OFF ; 
#line 1326 "psyntax1.c"
						}
						/* END OF ACTION: error_off */
					}
					break;
				case 331:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: error_warning */
						{
#line 834 "psyntax.act"
 (XIb) = ( unsigned ) OPTION_WARN ; 
#line 1338 "psyntax1.c"
						}
						/* END OF ACTION: error_warning */
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: 720 */
			XIe = XIb;
			XIi = XIa;
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOe = XIe;
	*XOi = XIi;
}

void
XR788(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 179:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: ellipsis-aux */
			{
				switch (CURRENT_TERMINAL) {
				case 47:
					{
						ADVANCE_LEXER;
					}
					break;
				case 210:
					{
						ADVANCE_LEXER;
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: ellipsis-aux */
			/* BEGINNING OF ACTION: opt_ellipsis_ident */
			{
#line 1031 "psyntax.act"
 (XIn) = OPT_ellipsis_ident ; 
#line 1397 "psyntax1.c"
			}
			/* END OF ACTION: opt_ellipsis_ident */
		}
		break;
	case 47: case 210:
		{
			/* BEGINNING OF INLINE: ellipsis-aux */
			{
				switch (CURRENT_TERMINAL) {
				case 47:
					{
						ADVANCE_LEXER;
					}
					break;
				case 210:
					{
						ADVANCE_LEXER;
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: ellipsis-aux */
			/* BEGINNING OF ACTION: opt_ellipsis_ident */
			{
#line 1031 "psyntax.act"
 (XIn) = OPT_ellipsis_ident ; 
#line 1426 "psyntax1.c"
			}
			/* END OF ACTION: opt_ellipsis_ident */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
}

void
XR789(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 110:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 313:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			XRimplicit_Hspec (&XIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 312:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 201:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_func_token_undef */
			{
#line 1045 "psyntax.act"
 (XIn) = OPT_func_token_undef ; 
#line 1481 "psyntax1.c"
			}
			/* END OF ACTION: opt_func_token_undef */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
}

void
XR790(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 247:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 197:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_interf_incompat */
			{
#line 1055 "psyntax.act"
 (XIn) = OPT_interf_incompat ; 
#line 1519 "psyntax1.c"
			}
			/* END OF ACTION: opt_interf_incompat */
		}
		break;
	case 254:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_link_incompat */
			{
#line 1058 "psyntax.act"
 (XIn) = OPT_link_incompat ; 
#line 1531 "psyntax1.c"
			}
			/* END OF ACTION: opt_link_incompat */
		}
		break;
	case 260:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 197:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_member_incompat */
			{
#line 1065 "psyntax.act"
 (XIn) = OPT_member_incompat ; 
#line 1550 "psyntax1.c"
			}
			/* END OF ACTION: opt_member_incompat */
		}
		break;
	case 284:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 228:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 176:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_func_incompat */
			{
#line 1041 "psyntax.act"
 (XIn) = OPT_func_incompat ; 
#line 1576 "psyntax1.c"
			}
			/* END OF ACTION: opt_func_incompat */
		}
		break;
	case 313:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 287:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_type_qual_incompat */
			{
#line 1090 "psyntax.act"
 (XIn) = OPT_type_qual_incompat ; 
#line 1595 "psyntax1.c"
			}
			/* END OF ACTION: opt_type_qual_incompat */
		}
		break;
	case 123:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 113:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_func_ret_void */
			{
#line 1044 "psyntax.act"
 (XIn) = OPT_func_ret_void ; 
#line 1614 "psyntax1.c"
			}
			/* END OF ACTION: opt_func_ret_void */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
}

void
XR791(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 203:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 169:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: hash */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 51:
						break;
					default:
						goto XL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: hash */
			/* BEGINNING OF ACTION: opt_ppdir_indent_dir */
			{
#line 1076 "psyntax.act"
 (XIn) = OPT_ppdir_indent_dir ; 
#line 1665 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_indent_dir */
		}
		break;
	case 51:
		{
			/* BEGINNING OF INLINE: hash */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 51:
						break;
					default:
						goto XL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: hash */
			switch (CURRENT_TERMINAL) {
			case 203:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_indent */
			{
#line 1075 "psyntax.act"
 (XIn) = OPT_ppdir_indent ; 
#line 1696 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_indent */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
}

void
XR792(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 203:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 44:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 265:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 169:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 231:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_id */
			{
#line 1074 "psyntax.act"
 (XIn) = OPT_ppdir_id ; 
#line 1755 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_id */
		}
		break;
	case 221:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 197:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_decl_none */
			{
#line 1019 "psyntax.act"
 (XIn) = OPT_decl_none ; 
#line 1774 "psyntax1.c"
			}
			/* END OF ACTION: opt_decl_none */
		}
		break;
	case 231:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 169:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: hash */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 51:
						break;
					default:
						goto XL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: hash */
			/* BEGINNING OF ACTION: opt_hash_ident */
			{
#line 1047 "psyntax.act"
 (XIn) = OPT_hash_ident ; 
#line 1806 "psyntax1.c"
			}
			/* END OF ACTION: opt_hash_ident */
		}
		break;
	case 265:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 169:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 224:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 211:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_eof_nline */
			{
#line 1035 "psyntax.act"
 (XIn) = OPT_eof_nline ; 
#line 1839 "psyntax1.c"
			}
			/* END OF ACTION: opt_eof_nline */
		}
		break;
	case 312:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 201:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_token_undef */
			{
#line 1088 "psyntax.act"
 (XIn) = OPT_token_undef ; 
#line 1858 "psyntax1.c"
			}
			/* END OF ACTION: opt_token_undef */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
}

void
XR793(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 332:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_func_weak */
			{
#line 1046 "psyntax.act"
 (XIn) = OPT_func_weak ; 
#line 1903 "psyntax1.c"
			}
			/* END OF ACTION: opt_func_weak */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: opt_func_proto */
			{
#line 1043 "psyntax.act"
 (XIn) = OPT_func_proto ; 
#line 1914 "psyntax1.c"
			}
			/* END OF ACTION: opt_func_proto */
		}
		break;
	case 355:
		return;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
}

void
XR794(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 203:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_unknown */
			{
#line 1078 "psyntax.act"
 (XIn) = OPT_ppdir_unknown ; 
#line 1943 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_unknown */
		}
		break;
	case 216:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_escape_unknown */
			{
#line 1037 "psyntax.act"
 (XIn) = OPT_escape_unknown ; 
#line 1955 "psyntax1.c"
			}
			/* END OF ACTION: opt_escape_unknown */
		}
		break;
	case 278:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_pragma_unknown */
			{
#line 1079 "psyntax.act"
 (XIn) = OPT_pragma_unknown ; 
#line 1967 "psyntax1.c"
			}
			/* END OF ACTION: opt_pragma_unknown */
		}
		break;
	case 118:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 44:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 121:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_decl_struct_anon */
			{
#line 1020 "psyntax.act"
 (XIn) = OPT_decl_struct_anon ; 
#line 1993 "psyntax1.c"
			}
			/* END OF ACTION: opt_decl_struct_anon */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
}

void
XRprog_Htok_Hpars(SID_LIST_ID XIr, SID_LIST_ID *XOp)
{
	SID_LIST_ID XIp;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		IDENTIFIER XIa;
		SID_LIST_ID XIq;

		XRprog_Htok_Hparam (XIr, &XIa);
		/* BEGINNING OF INLINE: 411 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					XR835 (&XIr, &XIq);
					if ((CURRENT_TERMINAL) == 355) {
						RESTORE_LEXER;
						goto XL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: list_id_null */
					{
#line 531 "psyntax.act"

    (XIq) = NULL_list ( IDENTIFIER ) ;
#line 2044 "psyntax1.c"
					}
					/* END OF ACTION: list_id_null */
				}
				break;
			case 355:
				RESTORE_LEXER;
				goto XL1;
			}
		}
		/* END OF INLINE: 411 */
		/* BEGINNING OF ACTION: list_id_cons */
		{
#line 535 "psyntax.act"

    CONS_id ( (XIa), (XIq), (XIp) ) ;
#line 2060 "psyntax1.c"
		}
		/* END OF ACTION: list_id_cons */
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOp = XIp;
}

void
XR795(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 245:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 174:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_init_aggregate */
			{
#line 1051 "psyntax.act"
 (XIn) = OPT_init_aggregate ; 
#line 2092 "psyntax1.c"
			}
			/* END OF ACTION: opt_init_aggregate */
		}
		break;
	case 118:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 44:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 121:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 174:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_complete_struct */
			{
#line 997 "psyntax.act"
 (XIn) = OPT_complete_struct ; 
#line 2125 "psyntax1.c"
			}
			/* END OF ACTION: opt_complete_struct */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
}

void
XR796(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 134:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 147:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_templ_export */
			{
#line 1083 "psyntax.act"
 (XIn) = OPT_templ_export ; 
#line 2163 "psyntax1.c"
			}
			/* END OF ACTION: opt_templ_export */
		}
		break;
	case 228:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 197:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_func_impl */
			{
#line 1040 "psyntax.act"
 (XIn) = OPT_func_impl ; 
#line 2182 "psyntax1.c"
			}
			/* END OF ACTION: opt_func_impl */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
}

void
XRdirective_Hspec(int *XOn, int *XOm)
{
	int XIn;
	int XIm;

	switch (CURRENT_TERMINAL) {
	case 180:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_assert */
			{
#line 1104 "psyntax.act"

    (XIn) = OPT_ppdir_assert ;
    (XIm) = OPT_ppdir_assert_ignore ;
#line 2216 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_assert */
		}
		break;
	case 224:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_file */
			{
#line 1109 "psyntax.act"

    (XIn) = OPT_ppdir_file ;
    (XIm) = OPT_ppdir_file_ignore ;
#line 2230 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_file */
		}
		break;
	case 231:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_ident */
			{
#line 1114 "psyntax.act"

    (XIn) = OPT_ppdir_ident ;
    (XIm) = OPT_ppdir_ident_ignore ;
#line 2244 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_ident */
		}
		break;
	case 238:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_import */
			{
#line 1119 "psyntax.act"

    (XIn) = OPT_ppdir_import ;
    (XIm) = OPT_ppdir_import_ignore ;
#line 2258 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_import */
		}
		break;
	case 241:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_import */
			{
#line 1119 "psyntax.act"

    (XIn) = OPT_ppdir_import ;
    (XIm) = OPT_ppdir_import_ignore ;
#line 2272 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_import */
		}
		break;
	case 317:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_unassert */
			{
#line 1124 "psyntax.act"

    (XIn) = OPT_ppdir_unassert ;
    (XIm) = OPT_ppdir_unassert_ignore ;
#line 2286 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_unassert */
		}
		break;
	case 331:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_warning */
			{
#line 1129 "psyntax.act"

    (XIn) = OPT_ppdir_warning ;
    (XIm) = OPT_ppdir_warning_ignore ;
#line 2300 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_warning */
		}
		break;
	case 332:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_weak */
			{
#line 1134 "psyntax.act"

    (XIn) = OPT_ppdir_weak ;
    (XIm) = OPT_ppdir_weak_ignore ;
#line 2314 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_weak */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
	*XOm = XIm;
}

void
XR797(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 141:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 174:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_int_operator */
			{
#line 1056 "psyntax.act"
 (XIn) = OPT_int_operator ; 
#line 2353 "psyntax1.c"
			}
			/* END OF ACTION: opt_int_operator */
		}
		break;
	case 274:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 174:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_int_overflow */
			{
#line 1057 "psyntax.act"
 (XIn) = OPT_int_overflow ; 
#line 2372 "psyntax1.c"
			}
			/* END OF ACTION: opt_int_overflow */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
}

void
XRlinkage_Hdescr(unsigned *XOi)
{
	unsigned XIi;

	switch (CURRENT_TERMINAL) {
	case 221:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: error_off */
			{
#line 833 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_OFF ; 
#line 2403 "psyntax1.c"
			}
			/* END OF ACTION: error_off */
		}
		break;
	case 248:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: error_on */
			{
#line 832 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_ON ; 
#line 2415 "psyntax1.c"
			}
			/* END OF ACTION: error_on */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOi = XIi;
}

void
XR798(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 174:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_variable */
			{
#line 1094 "psyntax.act"
 (XIn) = OPT_variable ; 
#line 2446 "psyntax1.c"
			}
			/* END OF ACTION: opt_variable */
		}
		break;
	case 230:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 174:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_decl_hide */
			{
#line 1018 "psyntax.act"
 (XIn) = OPT_decl_hide ; 
#line 2465 "psyntax1.c"
			}
			/* END OF ACTION: opt_decl_hide */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
}

void
XR799(void)
{
	switch (CURRENT_TERMINAL) {
	case 275:
		{
			unsigned XIi;
			unsigned XIe;
			int XIn;
			int XIm;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 294:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			XRcomplete_Hstate (&XIi);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: opt_overload_dep */
			{
#line 1069 "psyntax.act"
 (XIn) = OPT_overload_dep ; 
#line 2512 "psyntax1.c"
			}
			/* END OF ACTION: opt_overload_dep */
			/* BEGINNING OF ACTION: opt_overload_strict */
			{
#line 1071 "psyntax.act"
 (XIm) = OPT_overload_strict ; 
#line 2519 "psyntax1.c"
			}
			/* END OF ACTION: opt_overload_strict */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2527 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIm), (XIi) ) ;
#line 2535 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 197: case 257:
		{
			int XIn;
			unsigned XIe;

			XR786 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2556 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

void
XR800(void)
{
	switch (CURRENT_TERMINAL) {
	case 179:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 258:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 176:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_macro_arg_dir */
			{
#line 1062 "psyntax.act"
 (XIn) = OPT_macro_arg_dir ; 
#line 2600 "psyntax1.c"
			}
			/* END OF ACTION: opt_macro_arg_dir */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2613 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 180: case 224: case 231: case 238:
	case 241: case 317: case 331: case 332:
		{
			int XIn;
			int XIm;
			unsigned XIe;
			unsigned XIi;

			XRdirective_Hspec (&XIn, &XIm);
			XRdirective_Hstate (&XIe, &XIi);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2637 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIm), (XIi) ) ;
#line 2645 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

void
XR801(void)
{
	switch (CURRENT_TERMINAL) {
	case 228:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 254:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_func_linkage */
			{
#line 1042 "psyntax.act"
 (XIn) = OPT_func_linkage ; 
#line 2682 "psyntax1.c"
			}
			/* END OF ACTION: opt_func_linkage */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2695 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 254:
		{
			EXP XIe;
			DECL_SPEC XIa;

			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: string-literal */
			{
				switch (CURRENT_TERMINAL) {
				case 19:
					{
						/* BEGINNING OF EXTRACT: string-exp */
						{
#line 310 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 2716 "psyntax1.c"
						}
						/* END OF EXTRACT: string-exp */
						ADVANCE_LEXER;
					}
					break;
				case 20:
					{
						/* BEGINNING OF EXTRACT: wstring-exp */
						{
#line 314 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 2729 "psyntax1.c"
						}
						/* END OF EXTRACT: wstring-exp */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: string-literal */
			/* BEGINNING OF ACTION: linkage_string */
			{
#line 508 "psyntax.act"

    (XIa) = find_linkage ( (XIe) ) ;
#line 2745 "psyntax1.c"
			}
			/* END OF ACTION: linkage_string */
			/* BEGINNING OF ACTION: analysis_linkage */
			{
#line 984 "psyntax.act"

    set_link_opt ( (XIa) ) ;
#line 2753 "psyntax1.c"
			}
			/* END OF ACTION: analysis_linkage */
		}
		break;
	case 124: case 329:
		{
			int XIn;
			unsigned XIe;

			/* BEGINNING OF INLINE: 744 */
			{
				switch (CURRENT_TERMINAL) {
				case 124:
					{
						ADVANCE_LEXER;
					}
					break;
				case 329:
					{
						ADVANCE_LEXER;
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: 744 */
			/* BEGINNING OF ACTION: opt_decl_volatile */
			{
#line 1022 "psyntax.act"
 (XIn) = OPT_decl_volatile ; 
#line 2785 "psyntax1.c"
			}
			/* END OF ACTION: opt_decl_volatile */
			/* BEGINNING OF ACTION: error_on */
			{
#line 832 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_ON ; 
#line 2792 "psyntax1.c"
			}
			/* END OF ACTION: error_on */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2800 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

void
XR802(void)
{
	switch (CURRENT_TERMINAL) {
	case 194:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_const_cond */
			{
#line 1000 "psyntax.act"
 (XIn) = OPT_const_cond ; 
#line 2830 "psyntax1.c"
			}
			/* END OF ACTION: opt_const_cond */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2843 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 254:
		{
			unsigned XIe;
			int XIn;

			ADVANCE_LEXER;
			XRlinkage_Hdescr (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: opt_const_internal */
			{
#line 1001 "psyntax.act"
 (XIn) = OPT_const_internal ; 
#line 2863 "psyntax1.c"
			}
			/* END OF ACTION: opt_const_internal */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2871 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

void
XR803(void)
{
	switch (CURRENT_TERMINAL) {
	case 224:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 240:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_include_full */
			{
#line 1050 "psyntax.act"
 (XIn) = OPT_include_full ; 
#line 2908 "psyntax1.c"
			}
			/* END OF ACTION: opt_include_full */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2921 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 118: case 245:
		{
			int XIn;
			unsigned XIe;

			XR795 (&XIn);
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2942 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

void
XR804(void)
{
	switch (CURRENT_TERMINAL) {
	case 110: case 312:
		{
			int XIn;
			unsigned XIe;

			XR789 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2978 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 134: case 228:
		{
			int XIn;
			unsigned XIe;

			XR796 (&XIn);
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2999 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

void
XRconversion_Hspec(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			ADVANCE_LEXER;
			XR843 (&XIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: opt_conv */
			{
#line 1003 "psyntax.act"
 (XIn) = OPT_conv ; 
#line 3037 "psyntax1.c"
			}
			/* END OF ACTION: opt_conv */
		}
		break;
	case 355:
		return;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
}

void
XR805(void)
{
	switch (CURRENT_TERMINAL) {
	case 221:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 254:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_decl_unify */
			{
#line 1021 "psyntax.act"
 (XIn) = OPT_decl_unify ; 
#line 3074 "psyntax1.c"
			}
			/* END OF ACTION: opt_decl_unify */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3087 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 242:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 304:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 255:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_concat_string */
			{
#line 998 "psyntax.act"
 (XIn) = OPT_concat_string ; 
#line 3116 "psyntax1.c"
			}
			/* END OF ACTION: opt_concat_string */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3129 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

void
parse_preproc(int *XOt)
{
	int XIt;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		XRpragma_Hrule ();
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto XL1;
		}
		/* BEGINNING OF ACTION: lex_none */
		{
#line 419 "psyntax.act"
 (XIt) = lex_ignore_token ; 
#line 3163 "psyntax1.c"
		}
		/* END OF ACTION: lex_none */
	}
	goto XL0;
XL1:;
	{
		/* BEGINNING OF ACTION: lex_pragma */
		{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3174 "psyntax1.c"
		}
		/* END OF ACTION: lex_pragma */
	}
XL0:;
	*XOt = XIt;
}

void
XR806(void)
{
	switch (CURRENT_TERMINAL) {
	case 245:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_init_dynamic */
			{
#line 1052 "psyntax.act"
 (XIn) = OPT_init_dynamic ; 
#line 3196 "psyntax1.c"
			}
			/* END OF ACTION: opt_init_dynamic */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3209 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 174: case 230:
		{
			int XIn;
			unsigned XIe;

			XR798 (&XIn);
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3230 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

void
XR807(void)
{
	switch (CURRENT_TERMINAL) {
	case 258:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 214:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_macro_weak */
			{
#line 1064 "psyntax.act"
 (XIn) = OPT_macro_weak ; 
#line 3267 "psyntax1.c"
			}
			/* END OF ACTION: opt_macro_weak */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3280 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 285:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 174:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_weak */
			{
#line 1096 "psyntax.act"
 (XIn) = OPT_weak ; 
#line 3302 "psyntax1.c"
			}
			/* END OF ACTION: opt_weak */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3315 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

void
parse_tendra(int *XOt)
{
	int XIt;

	switch (CURRENT_TERMINAL) {
	case 168:
		{
			ADVANCE_LEXER;
			XR816 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3349 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 173:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 275:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 294:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_overload_ambig */
			{
#line 1068 "psyntax.act"
 (XIn) = OPT_overload_ambig ; 
#line 3378 "psyntax1.c"
			}
			/* END OF ACTION: opt_overload_ambig */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3391 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3398 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 175:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 121:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_anon_union */
			{
#line 990 "psyntax.act"
 (XIn) = OPT_anon_union ; 
#line 3420 "psyntax1.c"
			}
			/* END OF ACTION: opt_anon_union */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3433 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3440 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 176:
		{
			TYPE XI824;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_as_line */
			{
#line 1208 "psyntax.act"

    rescan_pragma ( lex_as ) ;
    RESCAN_LEXER ;
#line 3456 "psyntax1.c"
			}
			/* END OF ACTION: rescan_as_line */
			/* BEGINNING OF ACTION: parse_type */
			{
#line 377 "psyntax.act"

    (XI824) = type_error ;
    parse_tok_type ( &(XI824) ) ;
    object_type ( (XI824), null_tag ) ;
#line 3466 "psyntax1.c"
			}
			/* END OF ACTION: parse_type */
			switch (CURRENT_TERMINAL) {
			case 179:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			XR813 (&XI824);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3485 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 181:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 179:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 127:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_bool_assign */
			{
#line 993 "psyntax.act"
 (XIn) = OPT_bool_assign ; 
#line 3514 "psyntax1.c"
			}
			/* END OF ACTION: opt_bool_assign */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3527 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3534 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 182:
		{
			ADVANCE_LEXER;
			XR784 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3551 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 183:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 274:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_bitf_overflow */
			{
#line 991 "psyntax.act"
 (XIn) = OPT_bitf_overflow ; 
#line 3573 "psyntax1.c"
			}
			/* END OF ACTION: opt_bitf_overflow */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3586 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3593 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 184:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 228:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 117:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_func_block */
			{
#line 1039 "psyntax.act"
 (XIn) = OPT_func_block ; 
#line 3622 "psyntax1.c"
			}
			/* END OF ACTION: opt_func_block */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3635 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3642 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 185:
		{
			IDENTIFIER XIid;
			TYPE XI825;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1184 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 3661 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 520 "psyntax.act"

    crt_templ_qualifier = 0 ;
#line 3669 "psyntax1.c"
			}
			/* END OF ACTION: declarator_start */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 206 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3682 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 214 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3695 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 218 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3708 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 210 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3721 "psyntax1.c"
						}
						/* END OF EXTRACT: type-name */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: any-identifier */
			/* BEGINNING OF ACTION: type_bottom */
			{
#line 904 "psyntax.act"
 (XI825) = type_bottom ; 
#line 3736 "psyntax1.c"
			}
			/* END OF ACTION: type_bottom */
			/* BEGINNING OF ACTION: type_special */
			{
#line 897 "psyntax.act"

    typedef_special ( (XIid), (XI825) ) ;
#line 3744 "psyntax1.c"
			}
			/* END OF ACTION: type_special */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3751 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 128:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 171:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_wall */
			{
#line 1095 "psyntax.act"
 (XIn) = OPT_wall ; 
#line 3773 "psyntax1.c"
			}
			/* END OF ACTION: opt_wall */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3786 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3793 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 187:
		{
			ADVANCE_LEXER;
			XR817 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3810 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 191:
		{
			ADVANCE_LEXER;
			XR818 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3827 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 192:
		{
			ADVANCE_LEXER;
			XR803 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3844 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 193:
		{
			IDENTIFIER XIid;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 283:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1184 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 3869 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 206 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3882 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 214 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3895 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 218 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3908 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 210 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3921 "psyntax1.c"
						}
						/* END OF EXTRACT: type-name */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: any-identifier */
			/* BEGINNING OF ACTION: type_compute */
			{
#line 885 "psyntax.act"

    compute_promote_type ( (XIid) ) ;
#line 3937 "psyntax1.c"
			}
			/* END OF ACTION: type_compute */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3944 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 194:
		{
			ADVANCE_LEXER;
			XR799 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3961 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 98:
		{
			ADVANCE_LEXER;
			XR802 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3978 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 195:
		{
			ADVANCE_LEXER;
			XR820 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3995 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 197:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 184:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			XR785 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4019 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 198:
		{
			int XIi;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: interface_define */
			{
#line 711 "psyntax.act"
 (XIi) = lex_define ; 
#line 4033 "psyntax1.c"
			}
			/* END OF ACTION: interface_define */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1217 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 4046 "psyntax1.c"
			}
			/* END OF ACTION: rescan_tag_line */
			XR479 (&XIi);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4058 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 203:
		{
			ADVANCE_LEXER;
			XR800 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4075 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 204:
		{
			IDENTIFIER XIdir;
			IDENTIFIER XIid;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1184 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 4094 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 206 "psyntax.act"

    XIdir = crt_token->pp_data.id.use ;
#line 4107 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 214 "psyntax.act"

    XIdir = crt_token->pp_data.id.use ;
#line 4120 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 218 "psyntax.act"

    XIdir = crt_token->pp_data.id.use ;
#line 4133 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 210 "psyntax.act"

    XIdir = crt_token->pp_data.id.use ;
#line 4146 "psyntax1.c"
						}
						/* END OF EXTRACT: type-name */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: any-identifier */
			switch (CURRENT_TERMINAL) {
			case 325:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 213:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1184 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 4179 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 206 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4192 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 214 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4205 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 218 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4218 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 210 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4231 "psyntax1.c"
						}
						/* END OF EXTRACT: type-name */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: any-identifier */
			/* BEGINNING OF ACTION: check_directory */
			{
#line 785 "psyntax.act"

    directory_option ( (XIdir), (XIid) ) ;
#line 4247 "psyntax1.c"
			}
			/* END OF ACTION: check_directory */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4254 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 206:
		{
			ADVANCE_LEXER;
			XR828 (&XIt);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 207:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 179:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 231:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_dollar_ident */
			{
#line 1027 "psyntax.act"
 (XIn) = OPT_dollar_ident ; 
#line 4293 "psyntax1.c"
			}
			/* END OF ACTION: opt_dollar_ident */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4306 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4313 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 211:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check_end */
			{
#line 782 "psyntax.act"

    end_option ( 1 ) ;
#line 4326 "psyntax1.c"
			}
			/* END OF ACTION: check_end */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4333 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 104:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 119:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 174:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_enum_switch */
			{
#line 1034 "psyntax.act"
 (XIn) = OPT_enum_switch ; 
#line 4362 "psyntax1.c"
			}
			/* END OF ACTION: opt_enum_switch */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4375 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4382 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 216:
		{
			EXP XIa;
			EXP XIb;

			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: character-literal */
			{
				switch (CURRENT_TERMINAL) {
				case 17:
					{
						/* BEGINNING OF EXTRACT: char-exp */
						{
#line 302 "psyntax.act"

    XIa = crt_token->pp_data.exp ;
#line 4403 "psyntax1.c"
						}
						/* END OF EXTRACT: char-exp */
						ADVANCE_LEXER;
					}
					break;
				case 18:
					{
						/* BEGINNING OF EXTRACT: wchar-exp */
						{
#line 306 "psyntax.act"

    XIa = crt_token->pp_data.exp ;
#line 4416 "psyntax1.c"
						}
						/* END OF EXTRACT: wchar-exp */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: character-literal */
			XR755 (&XIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: escape_set */
			{
#line 946 "psyntax.act"

    set_escape ( (XIa), (XIb) ) ;
#line 4437 "psyntax1.c"
			}
			/* END OF ACTION: escape_set */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4444 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 217:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_exhaustive */
			{
#line 416 "psyntax.act"
 (XIt) = lex_exhaustive ; 
#line 4456 "psyntax1.c"
			}
			/* END OF ACTION: lex_exhaustive */
		}
		break;
	case 133:
		{
			unsigned XIc;
			unsigned XIe;
			int XIn;
			int XIm;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 186:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			XR743 (&XIc);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: opt_cast_explicit */
			{
#line 995 "psyntax.act"
 (XIn) = OPT_cast_explicit ; 
#line 4486 "psyntax1.c"
			}
			/* END OF ACTION: opt_cast_explicit */
			/* BEGINNING OF ACTION: opt_val_cast_explicit */
			{
#line 1098 "psyntax.act"
 (XIm) = OPT_VAL_cast_explicit ; 
#line 4493 "psyntax1.c"
			}
			/* END OF ACTION: opt_val_cast_explicit */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4501 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: analysis_value */
			{
#line 976 "psyntax.act"

    set_value ( (XIm), NULL_exp, ( unsigned long ) (XIc) ) ;
#line 4509 "psyntax1.c"
			}
			/* END OF ACTION: analysis_value */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4516 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 221:
		{
			ADVANCE_LEXER;
			XR801 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4533 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 222:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XR787 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4555 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4562 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 223:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 249:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 96:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_case_fall */
			{
#line 994 "psyntax.act"
 (XIn) = OPT_case_fall ; 
#line 4591 "psyntax1.c"
			}
			/* END OF ACTION: opt_case_fall */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4604 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4611 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 107:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 245:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 184:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_for_scope */
			{
#line 1038 "psyntax.act"
 (XIn) = OPT_for_scope ; 
#line 4640 "psyntax1.c"
			}
			/* END OF ACTION: opt_for_scope */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4653 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4660 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 226:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 104:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 197:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_enum_decl */
			{
#line 1033 "psyntax.act"
 (XIn) = OPT_enum_decl ; 
#line 4689 "psyntax1.c"
			}
			/* END OF ACTION: opt_enum_decl */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4702 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4709 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 228:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 276:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 179:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 276:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_conv_ptr_func */
			{
#line 1011 "psyntax.act"
 (XIn) = OPT_conv_ptr_func ; 
#line 4745 "psyntax1.c"
			}
			/* END OF ACTION: opt_conv_ptr_func */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4758 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4765 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 231:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XR788 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4787 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4794 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 235:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 118:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 44:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 121:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 44:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 104:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 307:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_type_tag_ignore */
			{
#line 1092 "psyntax.act"
 (XIn) = OPT_type_tag_ignore ; 
#line 4851 "psyntax1.c"
			}
			/* END OF ACTION: opt_type_tag_ignore */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4864 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4871 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 237:
		{
			ADVANCE_LEXER;
			XR804 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4888 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 240:
		{
			int XIn;
			EXP XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 202:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_val_include_depth */
			{
#line 1099 "psyntax.act"
 (XIn) = OPT_VAL_include_depth ; 
#line 4910 "psyntax1.c"
			}
			/* END OF ACTION: opt_val_include_depth */
			/* BEGINNING OF INLINE: integer-literal */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 21:
						/* BEGINNING OF EXTRACT: integer-exp */
						{
#line 285 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 4923 "psyntax1.c"
						}
						/* END OF EXTRACT: integer-exp */
						break;
					default:
						goto XL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: integer-literal */
			/* BEGINNING OF ACTION: analysis_exp */
			{
#line 980 "psyntax.act"

    set_value ( (XIn), (XIe), ( unsigned long ) 0 ) ;
#line 4939 "psyntax1.c"
			}
			/* END OF ACTION: analysis_exp */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4946 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 242:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XR790 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4968 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4975 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 243:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 313:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 179:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 268:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 313:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_type_obj_incompl */
			{
#line 1089 "psyntax.act"
 (XIn) = OPT_type_obj_incompl ; 
#line 5018 "psyntax1.c"
			}
			/* END OF ACTION: opt_type_obj_incompl */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5031 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5038 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 244:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XR791 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5060 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5067 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 245:
		{
			ADVANCE_LEXER;
			XR819 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5084 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 137:
		{
			unsigned XIe;
			int XIn;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 254:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			XRlinkage_Hdescr (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: opt_inline_internal */
			{
#line 1054 "psyntax.act"
 (XIn) = OPT_inline_internal ; 
#line 5111 "psyntax1.c"
			}
			/* END OF ACTION: opt_inline_internal */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5119 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5126 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 246:
		{
			ADVANCE_LEXER;
			XR821 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5143 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 247:
		{
			int XIi;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: interface_crt */
			{
#line 714 "psyntax.act"
 (XIi) = crt_interface ; 
#line 5157 "psyntax1.c"
			}
			/* END OF ACTION: interface_crt */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1217 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 5170 "psyntax1.c"
			}
			/* END OF ACTION: rescan_tag_line */
			XR479 (&XIi);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5182 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 254:
		{
			unsigned XIe;
			unsigned XIi;
			int XIn;
			int XIm;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 294:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 41:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			XRlinkage_Hstate (&XIe, &XIi);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: opt_link_resolve */
			{
#line 1060 "psyntax.act"
 (XIn) = OPT_link_resolve ; 
#line 5218 "psyntax1.c"
			}
			/* END OF ACTION: opt_link_resolve */
			/* BEGINNING OF ACTION: opt_link_internal */
			{
#line 1059 "psyntax.act"
 (XIm) = OPT_link_internal ; 
#line 5225 "psyntax1.c"
			}
			/* END OF ACTION: opt_link_internal */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5233 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIm), (XIi) ) ;
#line 5241 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5248 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 256:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 313:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_longlong */
			{
#line 1061 "psyntax.act"
 (XIn) = OPT_longlong ; 
#line 5270 "psyntax1.c"
			}
			/* END OF ACTION: opt_longlong */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5283 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5290 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 264:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 190:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 174:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_nest_comment */
			{
#line 1067 "psyntax.act"
 (XIn) = OPT_nest_comment ; 
#line 5319 "psyntax1.c"
			}
			/* END OF ACTION: opt_nest_comment */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5332 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5339 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 266:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XR792 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5361 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5368 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 267:
		{
			int XIi;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: interface_no_def */
			{
#line 712 "psyntax.act"
 (XIi) = lex_no_Hdef ; 
#line 5382 "psyntax1.c"
			}
			/* END OF ACTION: interface_no_def */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1217 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 5395 "psyntax1.c"
			}
			/* END OF ACTION: rescan_tag_line */
			XR479 (&XIi);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5407 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 141:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 279:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 174:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_paren */
			{
#line 1073 "psyntax.act"
 (XIn) = OPT_paren ; 
#line 5436 "psyntax1.c"
			}
			/* END OF ACTION: opt_paren */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5449 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5456 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 273:
		{
			ADVANCE_LEXER;
			XR811 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5473 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 275:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 294:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_overload_res */
			{
#line 1070 "psyntax.act"
 (XIn) = OPT_overload_res ; 
#line 5495 "psyntax1.c"
			}
			/* END OF ACTION: opt_overload_res */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5508 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5515 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 276:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 141:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 174:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ptr_operator */
			{
#line 1080 "psyntax.act"
 (XIn) = OPT_ptr_operator ; 
#line 5544 "psyntax1.c"
			}
			/* END OF ACTION: opt_ptr_operator */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5557 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5564 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 277:
		{
			int XIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1198 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 5580 "psyntax1.c"
			}
			/* END OF ACTION: rescan_line */
			/* BEGINNING OF ACTION: lex_postpone */
			{
#line 420 "psyntax.act"
 (XIa) = lex_postpone ; 
#line 5587 "psyntax1.c"
			}
			/* END OF ACTION: lex_postpone */
			XRpostpone_Hlist (XIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5599 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 280:
		{
			ADVANCE_LEXER;
			XR812 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5616 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 284:
		{
			TYPE XI826;
			TYPE XIs;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1198 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 5633 "psyntax1.c"
			}
			/* END OF ACTION: rescan_line */
			/* BEGINNING OF ACTION: parse_type */
			{
#line 377 "psyntax.act"

    (XI826) = type_error ;
    parse_tok_type ( &(XI826) ) ;
    object_type ( (XI826), null_tag ) ;
#line 5643 "psyntax1.c"
			}
			/* END OF ACTION: parse_type */
			switch (CURRENT_TERMINAL) {
			case 41:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: parse_type */
			{
#line 377 "psyntax.act"

    (XIs) = type_error ;
    parse_tok_type ( &(XIs) ) ;
    object_type ( (XIs), null_tag ) ;
#line 5660 "psyntax1.c"
			}
			/* END OF ACTION: parse_type */
			/* BEGINNING OF ACTION: type_promote */
			{
#line 889 "psyntax.act"

    set_promote_type ( (XI826), (XIs), ntype_ellipsis ) ;
#line 5668 "psyntax1.c"
			}
			/* END OF ACTION: type_promote */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5675 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 285:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XR793 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5697 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5704 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 291:
		{
			int XIi;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: interface_ignore */
			{
#line 713 "psyntax.act"
 (XIi) = lex_ignore ; 
#line 5718 "psyntax1.c"
			}
			/* END OF ACTION: interface_ignore */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1217 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 5731 "psyntax1.c"
			}
			/* END OF ACTION: rescan_tag_line */
			XR479 (&XIi);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5743 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 295:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 312:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 179:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 98:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_token_const */
			{
#line 1086 "psyntax.act"
 (XIn) = OPT_token_const ; 
#line 5779 "psyntax1.c"
			}
			/* END OF ACTION: opt_token_const */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5792 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5799 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 77:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5811 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 298:
		{
			ADVANCE_LEXER;
			XR829 (&XIt);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 306:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 117:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1198 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 5842 "psyntax1.c"
			}
			/* END OF ACTION: rescan_line */
			XRsuspend_Hlist ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5854 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 310:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 169:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 203:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_text */
			{
#line 1077 "psyntax.act"
 (XIn) = OPT_ppdir_text ; 
#line 5883 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_text */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5896 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5903 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 148:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 257:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_this_lvalue */
			{
#line 1084 "psyntax.act"
 (XIn) = OPT_this_lvalue ; 
#line 5925 "psyntax1.c"
			}
			/* END OF ACTION: opt_this_lvalue */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5938 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5945 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 149:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 174:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_throw_bad */
			{
#line 1085 "psyntax.act"
 (XIn) = OPT_throw_bad ; 
#line 5967 "psyntax1.c"
			}
			/* END OF ACTION: opt_throw_bad */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5980 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5987 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 313:
		{
			IDENTIFIER XIid;
			TYPE XI827;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1184 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 6006 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 520 "psyntax.act"

    crt_templ_qualifier = 0 ;
#line 6014 "psyntax1.c"
			}
			/* END OF ACTION: declarator_start */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 206 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 6027 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 214 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 6040 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 218 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 6053 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 210 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 6066 "psyntax1.c"
						}
						/* END OF EXTRACT: type-name */
						ADVANCE_LEXER;
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: any-identifier */
			switch (CURRENT_TERMINAL) {
			case 107:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 591 */
			{
				switch (CURRENT_TERMINAL) {
				case 185:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: type_bottom */
						{
#line 904 "psyntax.act"
 (XI827) = type_bottom ; 
#line 6094 "psyntax1.c"
						}
						/* END OF ACTION: type_bottom */
					}
					break;
				case 286:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: type_ptrdiff_t */
						{
#line 909 "psyntax.act"
 (XI827) = type_ptrdiff_t ; 
#line 6106 "psyntax1.c"
						}
						/* END OF ACTION: type_ptrdiff_t */
					}
					break;
				case 299:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: type_size_t */
						{
#line 910 "psyntax.act"
 (XI827) = type_size_t ; 
#line 6118 "psyntax1.c"
						}
						/* END OF ACTION: type_size_t */
					}
					break;
				case 156:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: type_wchar_t */
						{
#line 911 "psyntax.act"
 (XI827) = type_wchar_t ; 
#line 6130 "psyntax1.c"
						}
						/* END OF ACTION: type_wchar_t */
					}
					break;
				case 47: case 210:
					{
						/* BEGINNING OF INLINE: ellipsis-aux */
						{
							switch (CURRENT_TERMINAL) {
							case 47:
								{
									ADVANCE_LEXER;
								}
								break;
							case 210:
								{
									ADVANCE_LEXER;
								}
								break;
							default:
								goto XL1;
							}
						}
						/* END OF INLINE: ellipsis-aux */
						XR860 (&XI827);
						if ((CURRENT_TERMINAL) == 355) {
							RESTORE_LEXER;
							goto XL1;
						}
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: 591 */
			/* BEGINNING OF ACTION: type_special */
			{
#line 897 "psyntax.act"

    typedef_special ( (XIid), (XI827) ) ;
#line 6172 "psyntax1.c"
			}
			/* END OF ACTION: type_special */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6179 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 316:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XR794 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 6201 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6208 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 318:
		{
			ADVANCE_LEXER;
			XR822 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6225 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 319:
		{
			ADVANCE_LEXER;
			XR805 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6242 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 321:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 288:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_unmatched */
			{
#line 1093 "psyntax.act"
 (XIn) = OPT_unmatched ; 
#line 6264 "psyntax1.c"
			}
			/* END OF ACTION: opt_unmatched */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 6277 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6284 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 322:
		{
			int XIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1198 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 6300 "psyntax1.c"
			}
			/* END OF ACTION: rescan_line */
			/* BEGINNING OF ACTION: lex_unpostpone */
			{
#line 425 "psyntax.act"
 (XIa) = lex_unpostpone ; 
#line 6307 "psyntax1.c"
			}
			/* END OF ACTION: lex_unpostpone */
			XRpostpone_Hlist (XIa);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6319 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 323:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 189:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_reached */
			{
#line 1081 "psyntax.act"
 (XIn) = OPT_reached ; 
#line 6341 "psyntax1.c"
			}
			/* END OF ACTION: opt_reached */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 6354 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6361 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 325:
		{
			ADVANCE_LEXER;
			XR808 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6378 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 327:
		{
			ADVANCE_LEXER;
			XR806 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6395 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 332:
		{
			ADVANCE_LEXER;
			XR807 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6412 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 333:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 304:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 255:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_const_string */
			{
#line 1002 "psyntax.act"
 (XIn) = OPT_const_string ; 
#line 6441 "psyntax1.c"
			}
			/* END OF ACTION: opt_const_string */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 972 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 6454 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6461 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 215:
		{
			int XIn;

			XRerror_Hnumber (&XIn);
			XR783 (&XIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6480 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 251:
		{
			IDENTIFIER XIid;
			int XI823;

			XRkeyword_Hid (&XIid);
			switch (CURRENT_TERMINAL) {
			case 107:
				break;
			case 355:
				RESTORE_LEXER;
				goto XL1;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			XRkeyword_Hspec (&XI823);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: keyword_define */
			{
#line 926 "psyntax.act"

    define_keyword ( (XIid), (XI823) ) ;
#line 6511 "psyntax1.c"
			}
			/* END OF ACTION: keyword_define */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6518 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 260:
		{
			XRtokdef_Hrule ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6534 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 312:
		{
			XRtoken_Hrule ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6550 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 355:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1152 "psyntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 6571 "psyntax1.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: lex_pragma */
		{
#line 421 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6578 "psyntax1.c"
		}
		/* END OF ACTION: lex_pragma */
	}
XL0:;
	*XOt = XIt;
}

/* END OF FILE */
