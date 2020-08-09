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
#line 161 "psyntax.act"


/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>
#include <utility/buffer.h>
#include <construct/access.h>
#include <construct/allocate.h>
#include <construct/assign.h>
#include <construct/basetype.h>
#include <construct/cast.h>
#include <construct/chktype.h>
#include <construct/class.h>
#include <parse/preproc.h>
#include <parse/constant.h>
#include <construct/construct.h>
#include <construct/convert.h>
#include <construct/declare.h>
#include <construct/derive.h>
#include <construct/exception.h>
#include <construct/expression.h>
#include <construct/function.h>
#include <parse/hash.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/inttype.h>
#include <construct/label.h>
#include <parse/lex.h>
#include <parse/literal.h>
#include <construct/member.h>
#include <construct/namespace.h>
#include <parse/parse.h>
#include <parse/pragma.h>
#include <parse/predict.h>
#include <parse/preproc.h>
#include <construct/printf.h>
#include <construct/redeclare.h>
#include <construct/rewrite.h>
#include <construct/statement.h>
#include <parse/symbols.h>
#include <construct/template.h>
#include <construct/tokdef.h>
#include <construct/token.h>
#include <construct/typeid.h>
#include <construct/variable.h>


/*
    These are the aliases for the compound types used in the parser.
*/

typedef LIST(IDENTIFIER) SID_LIST_ID;


/*
     The function declarations are included at this point so that the
     type definitions are in scope.
*/

#include <parse/psyntax.h>
extern void parse_tok_type(TYPE *);
extern void parse_mem_type(TYPE *);
extern void parse_operator(IDENTIFIER *);

#line 98 "psyntax1.c"

/* BEGINNING OF STATIC VARIABLES */

int XI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

void
XRbound_Htok_Hpars(SID_LIST_ID *XOp)
{
	SID_LIST_ID XIp;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		IDENTIFIER XIid;
		SID_LIST_ID XIq;

		XRbound_Htok_Hparam (&XIid);
		/* BEGINNING OF INLINE: 406 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					XR835 (&XIq);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto XL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: list_id_null */
					{
#line 513 "psyntax.act"

    (XIq) = NULL_list ( IDENTIFIER ) ;
#line 139 "psyntax1.c"
					}
					/* END OF ACTION: list_id_null */
				}
				break;
			case 356:
				RESTORE_LEXER;
				goto XL1;
			}
		}
		/* END OF INLINE: 406 */
		/* BEGINNING OF ACTION: list_id_cons */
		{
#line 517 "psyntax.act"

    CONS_id ( (XIid), (XIq), (XIp) ) ;
#line 155 "psyntax1.c"
		}
		/* END OF ACTION: list_id_cons */
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
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
#line 815 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_OFF ; 
#line 180 "psyntax1.c"
			}
			/* END OF ACTION: error_off */
		}
		break;
	case 272:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: error_on */
			{
#line 814 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_ON ; 
#line 192 "psyntax1.c"
			}
			/* END OF ACTION: error_on */
		}
		break;
	case 332:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: error_warning */
			{
#line 816 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_WARN ; 
#line 204 "psyntax1.c"
			}
			/* END OF ACTION: error_warning */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOe = XIe;
}

void
XRcast_Hstate(unsigned *XOc)
{
	unsigned XIc;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		unsigned XI838;

		XRcast_Hcommand (&XI838);
		XR840 (&XI838, &XIc);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto XL1;
		}
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOc = XIc;
}

void
XRkeyword_Hid(IDENTIFIER *XOid)
{
	IDENTIFIER XIid;

	if ((CURRENT_TERMINAL) == 356) {
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
#line 1166 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 272 "psyntax1.c"
		}
		/* END OF ACTION: rescan_id */
		/* BEGINNING OF INLINE: any-identifier */
		{
			switch (CURRENT_TERMINAL) {
			case 1:
				{
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 188 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 285 "psyntax1.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			case 3:
				{
					/* BEGINNING OF EXTRACT: namespace-name */
					{
#line 196 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 298 "psyntax1.c"
					}
					/* END OF EXTRACT: namespace-name */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: statement-name */
					{
#line 200 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 311 "psyntax1.c"
					}
					/* END OF EXTRACT: statement-name */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: type-name */
					{
#line 192 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 324 "psyntax1.c"
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
	SAVE_LEXER (356);
	return;
XL0:;
	*XOid = XIid;
}

void
XRtoken_Hrule(void)
{
	if ((CURRENT_TERMINAL) == 356) {
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
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto XL1;
		}
		/* BEGINNING OF ACTION: rescan_tag_line */
		{
#line 1199 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 378 "psyntax1.c"
		}
		/* END OF ACTION: rescan_tag_line */
		/* BEGINNING OF INLINE: 459 */
		{
			{
				/* BEGINNING OF ACTION: is_operator */
				{
#line 382 "psyntax.act"

    (XI0) = predict_operator () ;
#line 389 "psyntax1.c"
				}
				/* END OF ACTION: is_operator */
				if (!XI0)
					goto XL3;
				/* BEGINNING OF ACTION: parse_operator */
				{
#line 377 "psyntax.act"

    (XIa) = DEREF_id ( hashid_id ( KEYWORD ( lex_zzzz ) ) ) ;
    parse_operator ( &(XIa) ) ;
#line 400 "psyntax1.c"
				}
				/* END OF ACTION: parse_operator */
				/* BEGINNING OF ACTION: bool_false */
				{
#line 1149 "psyntax.act"
 (XIt) = 0 ; 
#line 407 "psyntax1.c"
				}
				/* END OF ACTION: bool_false */
				goto XL2;
			}
			UNREACHED;
		XL3:;
			switch (CURRENT_TERMINAL) {
			case 1: case 2: case 3: case 4:
			case 308:
				{
					XRtag_Hopt (&XIt);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto XL1;
					}
					/* BEGINNING OF ACTION: rescan_id */
					{
#line 1166 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 431 "psyntax1.c"
					}
					/* END OF ACTION: rescan_id */
					/* BEGINNING OF INLINE: any-identifier */
					{
						switch (CURRENT_TERMINAL) {
						case 1:
							{
								/* BEGINNING OF EXTRACT: identifier */
								{
#line 188 "psyntax.act"

    XIa = crt_token->pp_data.id.use ;
#line 444 "psyntax1.c"
								}
								/* END OF EXTRACT: identifier */
								ADVANCE_LEXER;
							}
							break;
						case 3:
							{
								/* BEGINNING OF EXTRACT: namespace-name */
								{
#line 196 "psyntax.act"

    XIa = crt_token->pp_data.id.use ;
#line 457 "psyntax1.c"
								}
								/* END OF EXTRACT: namespace-name */
								ADVANCE_LEXER;
							}
							break;
						case 4:
							{
								/* BEGINNING OF EXTRACT: statement-name */
								{
#line 200 "psyntax.act"

    XIa = crt_token->pp_data.id.use ;
#line 470 "psyntax1.c"
								}
								/* END OF EXTRACT: statement-name */
								ADVANCE_LEXER;
							}
							break;
						case 2:
							{
								/* BEGINNING OF EXTRACT: type-name */
								{
#line 192 "psyntax.act"

    XIa = crt_token->pp_data.id.use ;
#line 483 "psyntax1.c"
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
		/* END OF INLINE: 459 */
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
#line 1166 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 523 "psyntax1.c"
		}
		/* END OF ACTION: rescan_id */
		/* BEGINNING OF INLINE: 460 */
		{
			switch (CURRENT_TERMINAL) {
			case 59:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF ACTION: id_anon */
					{
#line 433 "psyntax.act"

    HASHID nm = lookup_anon () ;
    (XIb) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 540 "psyntax1.c"
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
#line 188 "psyntax.act"

    XIb = crt_token->pp_data.id.use ;
#line 557 "psyntax1.c"
								}
								/* END OF EXTRACT: identifier */
								ADVANCE_LEXER;
							}
							break;
						case 3:
							{
								/* BEGINNING OF EXTRACT: namespace-name */
								{
#line 196 "psyntax.act"

    XIb = crt_token->pp_data.id.use ;
#line 570 "psyntax1.c"
								}
								/* END OF EXTRACT: namespace-name */
								ADVANCE_LEXER;
							}
							break;
						case 4:
							{
								/* BEGINNING OF EXTRACT: statement-name */
								{
#line 200 "psyntax.act"

    XIb = crt_token->pp_data.id.use ;
#line 583 "psyntax1.c"
								}
								/* END OF EXTRACT: statement-name */
								ADVANCE_LEXER;
							}
							break;
						case 2:
							{
								/* BEGINNING OF EXTRACT: type-name */
								{
#line 192 "psyntax.act"

    XIb = crt_token->pp_data.id.use ;
#line 596 "psyntax1.c"
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
		/* END OF INLINE: 460 */
		/* BEGINNING OF ACTION: token_decl */
		{
#line 634 "psyntax.act"

    IGNORE make_token_decl ( (XItok), (XIt), (XIa), (XIb) ) ;
#line 622 "psyntax1.c"
		}
		/* END OF ACTION: token_decl */
	}
	return;
XL1:;
	SAVE_LEXER (356);
	return;
}

void
XR782(IDENTIFIER XI780, IDENTIFIER *XO781)
{
	IDENTIFIER XI781;

XL2_782:;
	switch (CURRENT_TERMINAL) {
	case 46:
		{
			IDENTIFIER XImem;
			IDENTIFIER XIid;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1166 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 653 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 188 "psyntax.act"

    XImem = crt_token->pp_data.id.use ;
#line 666 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 196 "psyntax.act"

    XImem = crt_token->pp_data.id.use ;
#line 679 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 200 "psyntax.act"

    XImem = crt_token->pp_data.id.use ;
#line 692 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 192 "psyntax.act"

    XImem = crt_token->pp_data.id.use ;
#line 705 "psyntax1.c"
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
#line 646 "psyntax.act"

    (XIid) = find_mem_token ( (XI780), (XImem) ) ;
#line 721 "psyntax1.c"
			}
			/* END OF ACTION: token_selector */
			/* BEGINNING OF INLINE: 782 */
			XI780 = XIid;
			goto XL2_782;
			/* END OF INLINE: 782 */
		}
		UNREACHED;
	default:
		{
			XI781 = XI780;
		}
		break;
	case 356:
		return;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XO781 = XI781;
}

void
XR784(int *XIn)
{
	switch (CURRENT_TERMINAL) {
	case 179:
		{
			int XIe;

			ADVANCE_LEXER;
			XRoption_Hnumber (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: error_state */
			{
#line 819 "psyntax.act"

    set_error_sev ( (*XIn), (XIe) ) ;
#line 765 "psyntax1.c"
			}
			/* END OF ACTION: error_state */
		}
		break;
	case 172: case 205: case 271: case 272:
	case 332:
		{
			int XIe;

			XRerror_Hseverity (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: error_state */
			{
#line 819 "psyntax.act"

    set_error_sev ( (*XIn), (XIe) ) ;
#line 785 "psyntax1.c"
			}
			/* END OF ACTION: error_state */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (356);
	return;
}

void
XR785(void)
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
#line 1166 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 825 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 188 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 838 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 196 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 851 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 200 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 864 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 192 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 877 "psyntax1.c"
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
#line 759 "psyntax.act"

    begin_option ( (XIid) ) ;
#line 893 "psyntax1.c"
			}
			/* END OF ACTION: check_begin */
		}
		break;
	default:
		{
			IDENTIFIER XIid;

			/* BEGINNING OF ACTION: id_none */
			{
#line 426 "psyntax.act"

    (XIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 909 "psyntax1.c"
			}
			/* END OF ACTION: id_none */
			/* BEGINNING OF ACTION: check_begin */
			{
#line 759 "psyntax.act"

    begin_option ( (XIid) ) ;
#line 917 "psyntax1.c"
			}
			/* END OF ACTION: check_begin */
		}
		break;
	case 356:
		return;
	}
	return;
XL1:;
	SAVE_LEXER (356);
	return;
}

void
XR786(void)
{
	switch (CURRENT_TERMINAL) {
	case 211:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: decl_block_end */
			{
#line 780 "psyntax.act"

    IGNORE end_decl_block ( NULL_id, 1 ) ;
#line 943 "psyntax1.c"
			}
			/* END OF ACTION: decl_block_end */
		}
		break;
	case 1: case 2: case 3: case 4:
		{
			IDENTIFIER XIid;

			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1166 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 960 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 188 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 973 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 196 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 986 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 200 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 999 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 192 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1012 "psyntax1.c"
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
#line 775 "psyntax.act"

    begin_decl_block ( (XIid) ) ;
#line 1035 "psyntax1.c"
			}
			/* END OF ACTION: decl_block_begin */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (356);
	return;
}

void
XR787(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 197:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_decl_cond */
			{
#line 999 "psyntax.act"
 (XIn) = OPT_decl_cond ; 
#line 1064 "psyntax1.c"
			}
			/* END OF ACTION: opt_decl_cond */
		}
		break;
	case 257:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_cond_lvalue */
			{
#line 981 "psyntax.act"
 (XIn) = OPT_cond_lvalue ; 
#line 1076 "psyntax1.c"
			}
			/* END OF ACTION: opt_cond_lvalue */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
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
#line 814 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_ON ; 
#line 1108 "psyntax1.c"
			}
			/* END OF ACTION: error_on */
			/* BEGINNING OF ACTION: error_on */
			{
#line 814 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_ON ; 
#line 1115 "psyntax1.c"
			}
			/* END OF ACTION: error_on */
		}
		break;
	case 65: case 172: case 332:
		{
			unsigned XIa;
			unsigned XIb;

			/* BEGINNING OF INLINE: 720 */
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
#line 814 "psyntax.act"
 (XIa) = ( unsigned ) OPTION_ON ; 
#line 1149 "psyntax1.c"
						}
						/* END OF ACTION: error_on */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: error_off */
						{
#line 815 "psyntax.act"
 (XIa) = ( unsigned ) OPTION_OFF ; 
#line 1160 "psyntax1.c"
						}
						/* END OF ACTION: error_off */
					}
					break;
				}
			}
			/* END OF INLINE: 720 */
			/* BEGINNING OF INLINE: 721 */
			{
				switch (CURRENT_TERMINAL) {
				case 172:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: error_off */
						{
#line 815 "psyntax.act"
 (XIb) = ( unsigned ) OPTION_OFF ; 
#line 1178 "psyntax1.c"
						}
						/* END OF ACTION: error_off */
					}
					break;
				case 332:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: error_warning */
						{
#line 816 "psyntax.act"
 (XIb) = ( unsigned ) OPTION_WARN ; 
#line 1190 "psyntax1.c"
						}
						/* END OF ACTION: error_warning */
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: 721 */
			XIe = XIb;
			XIi = XIa;
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
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
#line 974 "psyntax.act"
 (XIn) = OPT_bitf_type ; 
#line 1245 "psyntax1.c"
			}
			/* END OF ACTION: opt_bitf_type */
		}
		break;
	case 42:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_comma_extra */
			{
#line 978 "psyntax.act"
 (XIn) = OPT_comma_extra ; 
#line 1257 "psyntax1.c"
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
#line 1045 "psyntax.act"
 (XIn) = OPT_macro_redef ; 
#line 1276 "psyntax1.c"
			}
			/* END OF ACTION: opt_macro_redef */
		}
		break;
	case 77:
		{
			ADVANCE_LEXER;
			XR841 (&XIn);
			if ((CURRENT_TERMINAL) == 356) {
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
#line 1073 "psyntax.act"
 (XIn) = OPT_type_redef ; 
#line 1305 "psyntax1.c"
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
#line 1012 "psyntax.act"
 (XIn) = OPT_ellipsis_extra ; 
#line 1334 "psyntax1.c"
			}
			/* END OF ACTION: opt_ellipsis_extra */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOn = XIn;
}

void
XR789(int *XOn)
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
#line 1013 "psyntax.act"
 (XIn) = OPT_ellipsis_ident ; 
#line 1383 "psyntax1.c"
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
#line 1013 "psyntax.act"
 (XIn) = OPT_ellipsis_ident ; 
#line 1412 "psyntax1.c"
			}
			/* END OF ACTION: opt_ellipsis_ident */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOn = XIn;
}

void
XR790(int *XOn)
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
			if ((CURRENT_TERMINAL) == 356) {
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
#line 1027 "psyntax.act"
 (XIn) = OPT_func_token_undef ; 
#line 1467 "psyntax1.c"
			}
			/* END OF ACTION: opt_func_token_undef */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOn = XIn;
}

void
XR791(int *XOn)
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
#line 1037 "psyntax.act"
 (XIn) = OPT_interf_incompat ; 
#line 1505 "psyntax1.c"
			}
			/* END OF ACTION: opt_interf_incompat */
		}
		break;
	case 254:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_link_incompat */
			{
#line 1040 "psyntax.act"
 (XIn) = OPT_link_incompat ; 
#line 1517 "psyntax1.c"
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
#line 1047 "psyntax.act"
 (XIn) = OPT_member_incompat ; 
#line 1536 "psyntax1.c"
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
#line 1023 "psyntax.act"
 (XIn) = OPT_func_incompat ; 
#line 1562 "psyntax1.c"
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
#line 1072 "psyntax.act"
 (XIn) = OPT_type_qual_incompat ; 
#line 1581 "psyntax1.c"
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
#line 1026 "psyntax.act"
 (XIn) = OPT_func_ret_void ; 
#line 1600 "psyntax1.c"
			}
			/* END OF ACTION: opt_func_ret_void */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
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
#line 1058 "psyntax.act"
 (XIn) = OPT_ppdir_indent_dir ; 
#line 1651 "psyntax1.c"
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
#line 1057 "psyntax.act"
 (XIn) = OPT_ppdir_indent ; 
#line 1682 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_indent */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOn = XIn;
}

void
XR793(int *XOn)
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
#line 1056 "psyntax.act"
 (XIn) = OPT_ppdir_id ; 
#line 1741 "psyntax1.c"
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
#line 1001 "psyntax.act"
 (XIn) = OPT_decl_none ; 
#line 1760 "psyntax1.c"
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
#line 1029 "psyntax.act"
 (XIn) = OPT_hash_ident ; 
#line 1792 "psyntax1.c"
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
#line 1017 "psyntax.act"
 (XIn) = OPT_eof_nline ; 
#line 1825 "psyntax1.c"
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
#line 1070 "psyntax.act"
 (XIn) = OPT_token_undef ; 
#line 1844 "psyntax1.c"
			}
			/* END OF ACTION: opt_token_undef */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOn = XIn;
}

void
XR794(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 333:
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
#line 1028 "psyntax.act"
 (XIn) = OPT_func_weak ; 
#line 1889 "psyntax1.c"
			}
			/* END OF ACTION: opt_func_weak */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: opt_func_proto */
			{
#line 1025 "psyntax.act"
 (XIn) = OPT_func_proto ; 
#line 1900 "psyntax1.c"
			}
			/* END OF ACTION: opt_func_proto */
		}
		break;
	case 356:
		return;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOn = XIn;
}

void
XRprog_Htok_Hpars(SID_LIST_ID XIr, SID_LIST_ID *XOp)
{
	SID_LIST_ID XIp;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		IDENTIFIER XIa;
		SID_LIST_ID XIq;

		XRprog_Htok_Hparam (XIr, &XIa);
		/* BEGINNING OF INLINE: 412 */
		{
			switch (CURRENT_TERMINAL) {
			case 42:
				{
					ADVANCE_LEXER;
					XR836 (&XIr, &XIq);
					if ((CURRENT_TERMINAL) == 356) {
						RESTORE_LEXER;
						goto XL1;
					}
				}
				break;
			default:
				{
					/* BEGINNING OF ACTION: list_id_null */
					{
#line 513 "psyntax.act"

    (XIq) = NULL_list ( IDENTIFIER ) ;
#line 1949 "psyntax1.c"
					}
					/* END OF ACTION: list_id_null */
				}
				break;
			case 356:
				RESTORE_LEXER;
				goto XL1;
			}
		}
		/* END OF INLINE: 412 */
		/* BEGINNING OF ACTION: list_id_cons */
		{
#line 517 "psyntax.act"

    CONS_id ( (XIa), (XIq), (XIp) ) ;
#line 1965 "psyntax1.c"
		}
		/* END OF ACTION: list_id_cons */
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOp = XIp;
}

void
XR795(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 203:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_unknown */
			{
#line 1060 "psyntax.act"
 (XIn) = OPT_ppdir_unknown ; 
#line 1990 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_unknown */
		}
		break;
	case 216:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_escape_unknown */
			{
#line 1019 "psyntax.act"
 (XIn) = OPT_escape_unknown ; 
#line 2002 "psyntax1.c"
			}
			/* END OF ACTION: opt_escape_unknown */
		}
		break;
	case 278:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_pragma_unknown */
			{
#line 1061 "psyntax.act"
 (XIn) = OPT_pragma_unknown ; 
#line 2014 "psyntax1.c"
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
#line 1002 "psyntax.act"
 (XIn) = OPT_decl_struct_anon ; 
#line 2040 "psyntax1.c"
			}
			/* END OF ACTION: opt_decl_struct_anon */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOn = XIn;
}

void
XR796(int *XOn)
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
#line 1033 "psyntax.act"
 (XIn) = OPT_init_aggregate ; 
#line 2078 "psyntax1.c"
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
#line 979 "psyntax.act"
 (XIn) = OPT_complete_struct ; 
#line 2111 "psyntax1.c"
			}
			/* END OF ACTION: opt_complete_struct */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
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
#line 1086 "psyntax.act"

    (XIn) = OPT_ppdir_assert ;
    (XIm) = OPT_ppdir_assert_ignore ;
#line 2145 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_assert */
		}
		break;
	case 224:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_file */
			{
#line 1091 "psyntax.act"

    (XIn) = OPT_ppdir_file ;
    (XIm) = OPT_ppdir_file_ignore ;
#line 2159 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_file */
		}
		break;
	case 231:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_ident */
			{
#line 1096 "psyntax.act"

    (XIn) = OPT_ppdir_ident ;
    (XIm) = OPT_ppdir_ident_ignore ;
#line 2173 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_ident */
		}
		break;
	case 238:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_import */
			{
#line 1101 "psyntax.act"

    (XIn) = OPT_ppdir_import ;
    (XIm) = OPT_ppdir_import_ignore ;
#line 2187 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_import */
		}
		break;
	case 241:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_import */
			{
#line 1101 "psyntax.act"

    (XIn) = OPT_ppdir_import ;
    (XIm) = OPT_ppdir_import_ignore ;
#line 2201 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_import */
		}
		break;
	case 317:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_unassert */
			{
#line 1106 "psyntax.act"

    (XIn) = OPT_ppdir_unassert ;
    (XIm) = OPT_ppdir_unassert_ignore ;
#line 2215 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_unassert */
		}
		break;
	case 332:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_warning */
			{
#line 1111 "psyntax.act"

    (XIn) = OPT_ppdir_warning ;
    (XIm) = OPT_ppdir_warning_ignore ;
#line 2229 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_warning */
		}
		break;
	case 333:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ppdir_weak */
			{
#line 1116 "psyntax.act"

    (XIn) = OPT_ppdir_weak ;
    (XIm) = OPT_ppdir_weak_ignore ;
#line 2243 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_weak */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
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
#line 1065 "psyntax.act"
 (XIn) = OPT_templ_export ; 
#line 2282 "psyntax1.c"
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
#line 1022 "psyntax.act"
 (XIn) = OPT_func_impl ; 
#line 2301 "psyntax1.c"
			}
			/* END OF ACTION: opt_func_impl */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
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
#line 815 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_OFF ; 
#line 2332 "psyntax1.c"
			}
			/* END OF ACTION: error_off */
		}
		break;
	case 248:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: error_on */
			{
#line 814 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_ON ; 
#line 2344 "psyntax1.c"
			}
			/* END OF ACTION: error_on */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOi = XIi;
}

void
XR798(int *XOn)
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
#line 1038 "psyntax.act"
 (XIn) = OPT_int_operator ; 
#line 2382 "psyntax1.c"
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
#line 1039 "psyntax.act"
 (XIn) = OPT_int_overflow ; 
#line 2401 "psyntax1.c"
			}
			/* END OF ACTION: opt_int_overflow */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOn = XIn;
}

void
XR799(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 174:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_variable */
			{
#line 1076 "psyntax.act"
 (XIn) = OPT_variable ; 
#line 2432 "psyntax1.c"
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
#line 1000 "psyntax.act"
 (XIn) = OPT_decl_hide ; 
#line 2451 "psyntax1.c"
			}
			/* END OF ACTION: opt_decl_hide */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOn = XIn;
}

void
XR800(void)
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: opt_overload_dep */
			{
#line 1051 "psyntax.act"
 (XIn) = OPT_overload_dep ; 
#line 2498 "psyntax1.c"
			}
			/* END OF ACTION: opt_overload_dep */
			/* BEGINNING OF ACTION: opt_overload_strict */
			{
#line 1053 "psyntax.act"
 (XIm) = OPT_overload_strict ; 
#line 2505 "psyntax1.c"
			}
			/* END OF ACTION: opt_overload_strict */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2513 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIm), (XIi) ) ;
#line 2521 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 197: case 257:
		{
			int XIn;
			unsigned XIe;

			XR787 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2542 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (356);
	return;
}

void
XR801(void)
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
#line 1044 "psyntax.act"
 (XIn) = OPT_macro_arg_dir ; 
#line 2586 "psyntax1.c"
			}
			/* END OF ACTION: opt_macro_arg_dir */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2599 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 180: case 224: case 231: case 238:
	case 241: case 317: case 332: case 333:
		{
			int XIn;
			int XIm;
			unsigned XIe;
			unsigned XIi;

			XRdirective_Hspec (&XIn, &XIm);
			XRdirective_Hstate (&XIe, &XIi);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2623 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIm), (XIi) ) ;
#line 2631 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (356);
	return;
}

void
XR802(void)
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
#line 1024 "psyntax.act"
 (XIn) = OPT_func_linkage ; 
#line 2668 "psyntax1.c"
			}
			/* END OF ACTION: opt_func_linkage */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2681 "psyntax1.c"
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
#line 292 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 2702 "psyntax1.c"
						}
						/* END OF EXTRACT: string-exp */
						ADVANCE_LEXER;
					}
					break;
				case 20:
					{
						/* BEGINNING OF EXTRACT: wstring-exp */
						{
#line 296 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 2715 "psyntax1.c"
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
#line 490 "psyntax.act"

    (XIa) = find_linkage ( (XIe) ) ;
#line 2731 "psyntax1.c"
			}
			/* END OF ACTION: linkage_string */
			/* BEGINNING OF ACTION: analysis_linkage */
			{
#line 966 "psyntax.act"

    set_link_opt ( (XIa) ) ;
#line 2739 "psyntax1.c"
			}
			/* END OF ACTION: analysis_linkage */
		}
		break;
	case 124: case 330:
		{
			int XIn;
			unsigned XIe;

			/* BEGINNING OF INLINE: 745 */
			{
				switch (CURRENT_TERMINAL) {
				case 124:
					{
						ADVANCE_LEXER;
					}
					break;
				case 330:
					{
						ADVANCE_LEXER;
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: 745 */
			/* BEGINNING OF ACTION: opt_decl_volatile */
			{
#line 1004 "psyntax.act"
 (XIn) = OPT_decl_volatile ; 
#line 2771 "psyntax1.c"
			}
			/* END OF ACTION: opt_decl_volatile */
			/* BEGINNING OF ACTION: error_on */
			{
#line 814 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_ON ; 
#line 2778 "psyntax1.c"
			}
			/* END OF ACTION: error_on */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2786 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (356);
	return;
}

void
XR803(void)
{
	switch (CURRENT_TERMINAL) {
	case 194:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_const_cond */
			{
#line 982 "psyntax.act"
 (XIn) = OPT_const_cond ; 
#line 2816 "psyntax1.c"
			}
			/* END OF ACTION: opt_const_cond */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2829 "psyntax1.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: opt_const_internal */
			{
#line 983 "psyntax.act"
 (XIn) = OPT_const_internal ; 
#line 2849 "psyntax1.c"
			}
			/* END OF ACTION: opt_const_internal */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2857 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (356);
	return;
}

void
XR804(void)
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
#line 1032 "psyntax.act"
 (XIn) = OPT_include_full ; 
#line 2894 "psyntax1.c"
			}
			/* END OF ACTION: opt_include_full */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2907 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 118: case 245:
		{
			int XIn;
			unsigned XIe;

			XR796 (&XIn);
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2928 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (356);
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
			XR844 (&XIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: opt_conv */
			{
#line 985 "psyntax.act"
 (XIn) = OPT_conv ; 
#line 2966 "psyntax1.c"
			}
			/* END OF ACTION: opt_conv */
		}
		break;
	case 356:
		return;
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOn = XIn;
}

void
XR805(void)
{
	switch (CURRENT_TERMINAL) {
	case 110: case 312:
		{
			int XIn;
			unsigned XIe;

			XR790 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3002 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 134: case 228:
		{
			int XIn;
			unsigned XIe;

			XR797 (&XIn);
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3023 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (356);
	return;
}

void
parse_preproc(int *XOt)
{
	int XIt;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		XRpragma_Hrule ();
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto XL1;
		}
		/* BEGINNING OF ACTION: lex_none */
		{
#line 401 "psyntax.act"
 (XIt) = lex_ignore_token ; 
#line 3057 "psyntax1.c"
		}
		/* END OF ACTION: lex_none */
	}
	goto XL0;
XL1:;
	{
		/* BEGINNING OF ACTION: lex_pragma */
		{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3068 "psyntax1.c"
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
#line 1003 "psyntax.act"
 (XIn) = OPT_decl_unify ; 
#line 3097 "psyntax1.c"
			}
			/* END OF ACTION: opt_decl_unify */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3110 "psyntax1.c"
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
#line 980 "psyntax.act"
 (XIn) = OPT_concat_string ; 
#line 3139 "psyntax1.c"
			}
			/* END OF ACTION: opt_concat_string */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3152 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (356);
	return;
}

void
XR807(void)
{
	switch (CURRENT_TERMINAL) {
	case 245:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_init_dynamic */
			{
#line 1034 "psyntax.act"
 (XIn) = OPT_init_dynamic ; 
#line 3182 "psyntax1.c"
			}
			/* END OF ACTION: opt_init_dynamic */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3195 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 174: case 230:
		{
			int XIn;
			unsigned XIe;

			XR799 (&XIn);
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3216 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	return;
XL1:;
	SAVE_LEXER (356);
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
			XR817 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3250 "psyntax1.c"
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
#line 1050 "psyntax.act"
 (XIn) = OPT_overload_ambig ; 
#line 3279 "psyntax1.c"
			}
			/* END OF ACTION: opt_overload_ambig */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3292 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3299 "psyntax1.c"
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
#line 972 "psyntax.act"
 (XIn) = OPT_anon_union ; 
#line 3321 "psyntax1.c"
			}
			/* END OF ACTION: opt_anon_union */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3334 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3341 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 176:
		{
			TYPE XI825;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_as_line */
			{
#line 1190 "psyntax.act"

    rescan_pragma ( lex_as ) ;
    RESCAN_LEXER ;
#line 3357 "psyntax1.c"
			}
			/* END OF ACTION: rescan_as_line */
			/* BEGINNING OF ACTION: parse_type */
			{
#line 359 "psyntax.act"

    (XI825) = type_error ;
    parse_tok_type ( &(XI825) ) ;
    object_type ( (XI825), null_tag ) ;
#line 3367 "psyntax1.c"
			}
			/* END OF ACTION: parse_type */
			switch (CURRENT_TERMINAL) {
			case 179:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			XR814 (&XI825);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3386 "psyntax1.c"
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
#line 975 "psyntax.act"
 (XIn) = OPT_bool_assign ; 
#line 3415 "psyntax1.c"
			}
			/* END OF ACTION: opt_bool_assign */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3428 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3435 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 182:
		{
			ADVANCE_LEXER;
			XR785 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3452 "psyntax1.c"
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
#line 973 "psyntax.act"
 (XIn) = OPT_bitf_overflow ; 
#line 3474 "psyntax1.c"
			}
			/* END OF ACTION: opt_bitf_overflow */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3487 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3494 "psyntax1.c"
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
#line 1021 "psyntax.act"
 (XIn) = OPT_func_block ; 
#line 3523 "psyntax1.c"
			}
			/* END OF ACTION: opt_func_block */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3536 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3543 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 185:
		{
			IDENTIFIER XIid;
			TYPE XI826;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1166 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 3562 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 502 "psyntax.act"

    crt_templ_qualifier = 0 ;
#line 3570 "psyntax1.c"
			}
			/* END OF ACTION: declarator_start */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 188 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3583 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 196 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3596 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 200 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3609 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 192 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3622 "psyntax1.c"
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
#line 886 "psyntax.act"
 (XI826) = type_bottom ; 
#line 3637 "psyntax1.c"
			}
			/* END OF ACTION: type_bottom */
			/* BEGINNING OF ACTION: type_special */
			{
#line 879 "psyntax.act"

    typedef_special ( (XIid), (XI826) ) ;
#line 3645 "psyntax1.c"
			}
			/* END OF ACTION: type_special */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3652 "psyntax1.c"
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
#line 1077 "psyntax.act"
 (XIn) = OPT_wall ; 
#line 3674 "psyntax1.c"
			}
			/* END OF ACTION: opt_wall */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 3687 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3694 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 187:
		{
			ADVANCE_LEXER;
			XR818 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3711 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 191:
		{
			ADVANCE_LEXER;
			XR819 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3728 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 192:
		{
			ADVANCE_LEXER;
			XR804 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3745 "psyntax1.c"
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
#line 1166 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 3770 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 188 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3783 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 196 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3796 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 200 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3809 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 192 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 3822 "psyntax1.c"
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
#line 867 "psyntax.act"

    compute_promote_type ( (XIid) ) ;
#line 3838 "psyntax1.c"
			}
			/* END OF ACTION: type_compute */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3845 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 194:
		{
			ADVANCE_LEXER;
			XR800 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3862 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 98:
		{
			ADVANCE_LEXER;
			XR803 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3879 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 195:
		{
			ADVANCE_LEXER;
			XR821 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3896 "psyntax1.c"
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
			XR786 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3920 "psyntax1.c"
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
#line 693 "psyntax.act"
 (XIi) = lex_define ; 
#line 3934 "psyntax1.c"
			}
			/* END OF ACTION: interface_define */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1199 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 3947 "psyntax1.c"
			}
			/* END OF ACTION: rescan_tag_line */
			XR480 (&XIi);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3959 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 203:
		{
			ADVANCE_LEXER;
			XR801 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 3976 "psyntax1.c"
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
#line 1166 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 3995 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 188 "psyntax.act"

    XIdir = crt_token->pp_data.id.use ;
#line 4008 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 196 "psyntax.act"

    XIdir = crt_token->pp_data.id.use ;
#line 4021 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 200 "psyntax.act"

    XIdir = crt_token->pp_data.id.use ;
#line 4034 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 192 "psyntax.act"

    XIdir = crt_token->pp_data.id.use ;
#line 4047 "psyntax1.c"
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
#line 1166 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 4080 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 188 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4093 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 196 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4106 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 200 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4119 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 192 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4132 "psyntax1.c"
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
#line 767 "psyntax.act"

    directory_option ( (XIdir), (XIid) ) ;
#line 4148 "psyntax1.c"
			}
			/* END OF ACTION: check_directory */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4155 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 206:
		{
			ADVANCE_LEXER;
			XR829 (&XIt);
			if ((CURRENT_TERMINAL) == 356) {
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
#line 1009 "psyntax.act"
 (XIn) = OPT_dollar_ident ; 
#line 4194 "psyntax1.c"
			}
			/* END OF ACTION: opt_dollar_ident */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4207 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4214 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 211:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: check_end */
			{
#line 764 "psyntax.act"

    end_option ( 1 ) ;
#line 4227 "psyntax1.c"
			}
			/* END OF ACTION: check_end */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4234 "psyntax1.c"
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
#line 1016 "psyntax.act"
 (XIn) = OPT_enum_switch ; 
#line 4263 "psyntax1.c"
			}
			/* END OF ACTION: opt_enum_switch */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4276 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4283 "psyntax1.c"
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
#line 284 "psyntax.act"

    XIa = crt_token->pp_data.exp ;
#line 4304 "psyntax1.c"
						}
						/* END OF EXTRACT: char-exp */
						ADVANCE_LEXER;
					}
					break;
				case 18:
					{
						/* BEGINNING OF EXTRACT: wchar-exp */
						{
#line 288 "psyntax.act"

    XIa = crt_token->pp_data.exp ;
#line 4317 "psyntax1.c"
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
			XR756 (&XIb);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: escape_set */
			{
#line 928 "psyntax.act"

    set_escape ( (XIa), (XIb) ) ;
#line 4338 "psyntax1.c"
			}
			/* END OF ACTION: escape_set */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4345 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 217:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_exhaustive */
			{
#line 398 "psyntax.act"
 (XIt) = lex_exhaustive ; 
#line 4357 "psyntax1.c"
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
			XR744 (&XIc);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: opt_cast_explicit */
			{
#line 977 "psyntax.act"
 (XIn) = OPT_cast_explicit ; 
#line 4387 "psyntax1.c"
			}
			/* END OF ACTION: opt_cast_explicit */
			/* BEGINNING OF ACTION: opt_val_cast_explicit */
			{
#line 1080 "psyntax.act"
 (XIm) = OPT_VAL_cast_explicit ; 
#line 4394 "psyntax1.c"
			}
			/* END OF ACTION: opt_val_cast_explicit */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4402 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: analysis_value */
			{
#line 958 "psyntax.act"

    set_value ( (XIm), NULL_exp, ( unsigned long ) (XIc) ) ;
#line 4410 "psyntax1.c"
			}
			/* END OF ACTION: analysis_value */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4417 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 221:
		{
			ADVANCE_LEXER;
			XR802 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4434 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 222:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XR788 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4456 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4463 "psyntax1.c"
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
#line 976 "psyntax.act"
 (XIn) = OPT_case_fall ; 
#line 4492 "psyntax1.c"
			}
			/* END OF ACTION: opt_case_fall */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4505 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4512 "psyntax1.c"
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
#line 1020 "psyntax.act"
 (XIn) = OPT_for_scope ; 
#line 4541 "psyntax1.c"
			}
			/* END OF ACTION: opt_for_scope */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4554 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4561 "psyntax1.c"
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
#line 1015 "psyntax.act"
 (XIn) = OPT_enum_decl ; 
#line 4590 "psyntax1.c"
			}
			/* END OF ACTION: opt_enum_decl */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4603 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4610 "psyntax1.c"
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
#line 993 "psyntax.act"
 (XIn) = OPT_conv_ptr_func ; 
#line 4646 "psyntax1.c"
			}
			/* END OF ACTION: opt_conv_ptr_func */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4659 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4666 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 231:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XR789 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4688 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4695 "psyntax1.c"
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
#line 1074 "psyntax.act"
 (XIn) = OPT_type_tag_ignore ; 
#line 4752 "psyntax1.c"
			}
			/* END OF ACTION: opt_type_tag_ignore */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4765 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4772 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 237:
		{
			ADVANCE_LEXER;
			XR805 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4789 "psyntax1.c"
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
#line 1081 "psyntax.act"
 (XIn) = OPT_VAL_include_depth ; 
#line 4811 "psyntax1.c"
			}
			/* END OF ACTION: opt_val_include_depth */
			/* BEGINNING OF INLINE: integer-literal */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 21:
						/* BEGINNING OF EXTRACT: integer-exp */
						{
#line 267 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 4824 "psyntax1.c"
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
#line 962 "psyntax.act"

    set_value ( (XIn), (XIe), ( unsigned long ) 0 ) ;
#line 4840 "psyntax1.c"
			}
			/* END OF ACTION: analysis_exp */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4847 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 242:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XR791 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4869 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4876 "psyntax1.c"
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
#line 1071 "psyntax.act"
 (XIn) = OPT_type_obj_incompl ; 
#line 4919 "psyntax1.c"
			}
			/* END OF ACTION: opt_type_obj_incompl */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4932 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4939 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 244:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XR792 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 4961 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4968 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 245:
		{
			ADVANCE_LEXER;
			XR820 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 4985 "psyntax1.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: opt_inline_internal */
			{
#line 1036 "psyntax.act"
 (XIn) = OPT_inline_internal ; 
#line 5012 "psyntax1.c"
			}
			/* END OF ACTION: opt_inline_internal */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5020 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5027 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 246:
		{
			ADVANCE_LEXER;
			XR822 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5044 "psyntax1.c"
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
#line 696 "psyntax.act"
 (XIi) = crt_interface ; 
#line 5058 "psyntax1.c"
			}
			/* END OF ACTION: interface_crt */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1199 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 5071 "psyntax1.c"
			}
			/* END OF ACTION: rescan_tag_line */
			XR480 (&XIi);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5083 "psyntax1.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: opt_link_resolve */
			{
#line 1042 "psyntax.act"
 (XIn) = OPT_link_resolve ; 
#line 5119 "psyntax1.c"
			}
			/* END OF ACTION: opt_link_resolve */
			/* BEGINNING OF ACTION: opt_link_internal */
			{
#line 1041 "psyntax.act"
 (XIm) = OPT_link_internal ; 
#line 5126 "psyntax1.c"
			}
			/* END OF ACTION: opt_link_internal */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5134 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIm), (XIi) ) ;
#line 5142 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5149 "psyntax1.c"
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
#line 1043 "psyntax.act"
 (XIn) = OPT_longlong ; 
#line 5171 "psyntax1.c"
			}
			/* END OF ACTION: opt_longlong */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5184 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5191 "psyntax1.c"
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
#line 1049 "psyntax.act"
 (XIn) = OPT_nest_comment ; 
#line 5220 "psyntax1.c"
			}
			/* END OF ACTION: opt_nest_comment */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5233 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5240 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 266:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XR793 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5262 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5269 "psyntax1.c"
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
#line 694 "psyntax.act"
 (XIi) = lex_no_Hdef ; 
#line 5283 "psyntax1.c"
			}
			/* END OF ACTION: interface_no_def */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1199 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 5296 "psyntax1.c"
			}
			/* END OF ACTION: rescan_tag_line */
			XR480 (&XIi);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5308 "psyntax1.c"
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
#line 1055 "psyntax.act"
 (XIn) = OPT_paren ; 
#line 5337 "psyntax1.c"
			}
			/* END OF ACTION: opt_paren */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5350 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5357 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 273:
		{
			ADVANCE_LEXER;
			XR812 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5374 "psyntax1.c"
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
#line 1052 "psyntax.act"
 (XIn) = OPT_overload_res ; 
#line 5396 "psyntax1.c"
			}
			/* END OF ACTION: opt_overload_res */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5409 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5416 "psyntax1.c"
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
#line 1062 "psyntax.act"
 (XIn) = OPT_ptr_operator ; 
#line 5445 "psyntax1.c"
			}
			/* END OF ACTION: opt_ptr_operator */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5458 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5465 "psyntax1.c"
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
#line 1180 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 5481 "psyntax1.c"
			}
			/* END OF ACTION: rescan_line */
			/* BEGINNING OF ACTION: lex_postpone */
			{
#line 402 "psyntax.act"
 (XIa) = lex_postpone ; 
#line 5488 "psyntax1.c"
			}
			/* END OF ACTION: lex_postpone */
			XRpostpone_Hlist (XIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5500 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 280:
		{
			ADVANCE_LEXER;
			XR813 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5517 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 284:
		{
			TYPE XI827;
			TYPE XIs;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1180 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 5534 "psyntax1.c"
			}
			/* END OF ACTION: rescan_line */
			/* BEGINNING OF ACTION: parse_type */
			{
#line 359 "psyntax.act"

    (XI827) = type_error ;
    parse_tok_type ( &(XI827) ) ;
    object_type ( (XI827), null_tag ) ;
#line 5544 "psyntax1.c"
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
#line 359 "psyntax.act"

    (XIs) = type_error ;
    parse_tok_type ( &(XIs) ) ;
    object_type ( (XIs), null_tag ) ;
#line 5561 "psyntax1.c"
			}
			/* END OF ACTION: parse_type */
			/* BEGINNING OF ACTION: type_promote */
			{
#line 871 "psyntax.act"

    set_promote_type ( (XI827), (XIs), ntype_ellipsis ) ;
#line 5569 "psyntax1.c"
			}
			/* END OF ACTION: type_promote */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5576 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 285:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XR794 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5598 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5605 "psyntax1.c"
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
#line 695 "psyntax.act"
 (XIi) = lex_ignore ; 
#line 5619 "psyntax1.c"
			}
			/* END OF ACTION: interface_ignore */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1199 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 5632 "psyntax1.c"
			}
			/* END OF ACTION: rescan_tag_line */
			XR480 (&XIi);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5644 "psyntax1.c"
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
#line 1068 "psyntax.act"
 (XIn) = OPT_token_const ; 
#line 5680 "psyntax1.c"
			}
			/* END OF ACTION: opt_token_const */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5693 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5700 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 77:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5712 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 298:
		{
			ADVANCE_LEXER;
			XR830 (&XIt);
			if ((CURRENT_TERMINAL) == 356) {
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
#line 1180 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 5743 "psyntax1.c"
			}
			/* END OF ACTION: rescan_line */
			XRsuspend_Hlist ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5755 "psyntax1.c"
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
#line 1059 "psyntax.act"
 (XIn) = OPT_ppdir_text ; 
#line 5784 "psyntax1.c"
			}
			/* END OF ACTION: opt_ppdir_text */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5797 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5804 "psyntax1.c"
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
#line 1066 "psyntax.act"
 (XIn) = OPT_this_lvalue ; 
#line 5826 "psyntax1.c"
			}
			/* END OF ACTION: opt_this_lvalue */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5839 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5846 "psyntax1.c"
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
#line 1067 "psyntax.act"
 (XIn) = OPT_throw_bad ; 
#line 5868 "psyntax1.c"
			}
			/* END OF ACTION: opt_throw_bad */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 5881 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 5888 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 313:
		{
			IDENTIFIER XIid;
			TYPE XI828;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1166 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 5907 "psyntax1.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF ACTION: declarator_start */
			{
#line 502 "psyntax.act"

    crt_templ_qualifier = 0 ;
#line 5915 "psyntax1.c"
			}
			/* END OF ACTION: declarator_start */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 188 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 5928 "psyntax1.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 196 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 5941 "psyntax1.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 200 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 5954 "psyntax1.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 192 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 5967 "psyntax1.c"
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
			/* BEGINNING OF INLINE: 592 */
			{
				switch (CURRENT_TERMINAL) {
				case 185:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: type_bottom */
						{
#line 886 "psyntax.act"
 (XI828) = type_bottom ; 
#line 5995 "psyntax1.c"
						}
						/* END OF ACTION: type_bottom */
					}
					break;
				case 286:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: type_ptrdiff_t */
						{
#line 891 "psyntax.act"
 (XI828) = type_ptrdiff_t ; 
#line 6007 "psyntax1.c"
						}
						/* END OF ACTION: type_ptrdiff_t */
					}
					break;
				case 299:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: type_size_t */
						{
#line 892 "psyntax.act"
 (XI828) = type_size_t ; 
#line 6019 "psyntax1.c"
						}
						/* END OF ACTION: type_size_t */
					}
					break;
				case 156:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: type_wchar_t */
						{
#line 893 "psyntax.act"
 (XI828) = type_wchar_t ; 
#line 6031 "psyntax1.c"
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
						XR861 (&XI828);
						if ((CURRENT_TERMINAL) == 356) {
							RESTORE_LEXER;
							goto XL1;
						}
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: 592 */
			/* BEGINNING OF ACTION: type_special */
			{
#line 879 "psyntax.act"

    typedef_special ( (XIid), (XI828) ) ;
#line 6073 "psyntax1.c"
			}
			/* END OF ACTION: type_special */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6080 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 316:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XR795 (&XIn);
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 6102 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6109 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 318:
		{
			ADVANCE_LEXER;
			XR823 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6126 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 319:
		{
			ADVANCE_LEXER;
			XR806 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6143 "psyntax1.c"
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
#line 1075 "psyntax.act"
 (XIn) = OPT_unmatched ; 
#line 6165 "psyntax1.c"
			}
			/* END OF ACTION: opt_unmatched */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 6178 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6185 "psyntax1.c"
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
#line 1180 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 6201 "psyntax1.c"
			}
			/* END OF ACTION: rescan_line */
			/* BEGINNING OF ACTION: lex_unpostpone */
			{
#line 407 "psyntax.act"
 (XIa) = lex_unpostpone ; 
#line 6208 "psyntax1.c"
			}
			/* END OF ACTION: lex_unpostpone */
			XRpostpone_Hlist (XIa);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6220 "psyntax1.c"
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
#line 1063 "psyntax.act"
 (XIn) = OPT_reached ; 
#line 6242 "psyntax1.c"
			}
			/* END OF ACTION: opt_reached */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 6255 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6262 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 325:
		{
			ADVANCE_LEXER;
			XR809 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6279 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 327:
		{
			ADVANCE_LEXER;
			XR807 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6296 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 333:
		{
			ADVANCE_LEXER;
			XR808 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6313 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 334:
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
#line 984 "psyntax.act"
 (XIn) = OPT_const_string ; 
#line 6342 "psyntax1.c"
			}
			/* END OF ACTION: opt_const_string */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 6355 "psyntax1.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6362 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 215:
		{
			int XIn;

			XRerror_Hnumber (&XIn);
			XR784 (&XIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6381 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 251:
		{
			IDENTIFIER XIid;
			int XI824;

			XRkeyword_Hid (&XIid);
			switch (CURRENT_TERMINAL) {
			case 107:
				break;
			case 356:
				RESTORE_LEXER;
				goto XL1;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			XRkeyword_Hspec (&XI824);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: keyword_define */
			{
#line 908 "psyntax.act"

    define_keyword ( (XIid), (XI824) ) ;
#line 6412 "psyntax1.c"
			}
			/* END OF ACTION: keyword_define */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6419 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 260:
		{
			XRtokdef_Hrule ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6435 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 312:
		{
			XRtoken_Hrule ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6451 "psyntax1.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	case 356:
		return;
	default:
		goto XL1;
	}
	goto XL0;
XL1:;
	{
		/* BEGINNING OF ACTION: error_syntax */
		{
#line 1134 "psyntax.act"

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
#line 6472 "psyntax1.c"
		}
		/* END OF ACTION: error_syntax */
		/* BEGINNING OF ACTION: lex_pragma */
		{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 6479 "psyntax1.c"
		}
		/* END OF ACTION: lex_pragma */
	}
XL0:;
	*XOt = XIt;
}

/* END OF FILE */
