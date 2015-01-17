/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

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
#line 193 "psyntax.act"



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


#line 136 "psyntax2.c"

void
XR808(void)
{
	switch (CURRENT_TERMINAL) {
	case 213:
		{
			IDENTIFIER XIid;
			unsigned XIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1220 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 156 "psyntax2.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 242 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 169 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 250 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 182 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 254 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 195 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 246 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 208 "psyntax2.c"
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
			/* BEGINNING OF INLINE: 769 */
			{
				switch (CURRENT_TERMINAL) {
				case 293:
					{
						ADVANCE_LEXER;
						XRallow_Hstate (&XIe);
						if ((CURRENT_TERMINAL) == 355) {
							RESTORE_LEXER;
							goto XL1;
						}
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: error_on */
						{
#line 868 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_ON ; 
#line 238 "psyntax2.c"
						}
						/* END OF ACTION: error_on */
					}
					break;
				}
			}
			/* END OF INLINE: 769 */
			/* BEGINNING OF ACTION: check_use */
			{
#line 825 "psyntax.act"

    use_option ( (XIid), (XIe) ) ;
#line 251 "psyntax2.c"
			}
			/* END OF ACTION: check_use */
		}
		break;
	case 215:
		{
			int XIn;

			XRerror_Hnumber (&XIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: error_use */
			{
#line 877 "psyntax.act"

    if ( (XIn) >= 0 ) {
	no_error_args = 1 ;
	report ( crt_loc, make_error ( (XIn) ) ) ;
	no_error_args = 0 ;
    }
#line 274 "psyntax2.c"
			}
			/* END OF ACTION: error_use */
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
XR809(void)
{
	switch (CURRENT_TERMINAL) {
	case 215:
		{
			int XIn;
			EXP XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 252:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_val_maximum_error */
			{
#line 1136 "psyntax.act"
 (XIn) = OPT_VAL_maximum_error ; 
#line 311 "psyntax2.c"
			}
			/* END OF ACTION: opt_val_maximum_error */
			/* BEGINNING OF INLINE: integer-literal */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 21:
						/* BEGINNING OF EXTRACT: integer-exp */
						{
#line 321 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 324 "psyntax2.c"
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
#line 1016 "psyntax.act"

    set_value ( (XIn), (XIe), ( unsigned long ) 0 ) ;
#line 340 "psyntax2.c"
			}
			/* END OF ACTION: analysis_exp */
		}
		break;
	case 262:
		{
			EXP XIe;
			unsigned XIi;
			int XIn;
			int XIm;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 252:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: integer-literal */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 21:
						/* BEGINNING OF EXTRACT: integer-exp */
						{
#line 321 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 370 "psyntax2.c"
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
			XRwarning_Hopt (&XIi);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: opt_val_name_limit */
			{
#line 1137 "psyntax.act"
 (XIn) = OPT_VAL_name_limit ; 
#line 390 "psyntax2.c"
			}
			/* END OF ACTION: opt_val_name_limit */
			/* BEGINNING OF ACTION: opt_name_limit */
			{
#line 1102 "psyntax.act"
 (XIm) = OPT_name_limit ; 
#line 397 "psyntax2.c"
			}
			/* END OF ACTION: opt_name_limit */
			/* BEGINNING OF ACTION: analysis_exp */
			{
#line 1016 "psyntax.act"

    set_value ( (XIn), (XIe), ( unsigned long ) 0 ) ;
#line 405 "psyntax2.c"
			}
			/* END OF ACTION: analysis_exp */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 1008 "psyntax.act"

    set_option ( (XIm), (XIi) ) ;
#line 413 "psyntax2.c"
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
XR810(void)
{
	switch (CURRENT_TERMINAL) {
	case 216:
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
			/* BEGINNING OF ACTION: opt_escape_overflow */
			{
#line 1072 "psyntax.act"
 (XIn) = OPT_escape_overflow ; 
#line 450 "psyntax2.c"
			}
			/* END OF ACTION: opt_escape_overflow */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 1008 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 463 "psyntax2.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 17: case 18: case 19: case 20:
		{
			EXP XIa;

			/* BEGINNING OF INLINE: 753 */
			{
				switch (CURRENT_TERMINAL) {
				case 17: case 18:
					{
						/* BEGINNING OF INLINE: character-literal */
						{
							switch (CURRENT_TERMINAL) {
							case 17:
								{
									/* BEGINNING OF EXTRACT: char-exp */
									{
#line 338 "psyntax.act"

    XIa = crt_token->pp_data.exp ;
#line 487 "psyntax2.c"
									}
									/* END OF EXTRACT: char-exp */
									ADVANCE_LEXER;
								}
								break;
							case 18:
								{
									/* BEGINNING OF EXTRACT: wchar-exp */
									{
#line 342 "psyntax.act"

    XIa = crt_token->pp_data.exp ;
#line 500 "psyntax2.c"
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
					}
					break;
				case 19: case 20:
					{
						/* BEGINNING OF INLINE: string-literal */
						{
							switch (CURRENT_TERMINAL) {
							case 19:
								{
									/* BEGINNING OF EXTRACT: string-exp */
									{
#line 346 "psyntax.act"

    XIa = crt_token->pp_data.exp ;
#line 525 "psyntax2.c"
									}
									/* END OF EXTRACT: string-exp */
									ADVANCE_LEXER;
								}
								break;
							case 20:
								{
									/* BEGINNING OF EXTRACT: wstring-exp */
									{
#line 350 "psyntax.act"

    XIa = crt_token->pp_data.exp ;
#line 538 "psyntax2.c"
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
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: 753 */
			/* BEGINNING OF INLINE: 754 */
			{
				switch (CURRENT_TERMINAL) {
				case 179:
					{
						EXP XIb;

						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: character-literal */
						{
							switch (CURRENT_TERMINAL) {
							case 17:
								{
									/* BEGINNING OF EXTRACT: char-exp */
									{
#line 338 "psyntax.act"

    XIb = crt_token->pp_data.exp ;
#line 574 "psyntax2.c"
									}
									/* END OF EXTRACT: char-exp */
									ADVANCE_LEXER;
								}
								break;
							case 18:
								{
									/* BEGINNING OF EXTRACT: wchar-exp */
									{
#line 342 "psyntax.act"

    XIb = crt_token->pp_data.exp ;
#line 587 "psyntax2.c"
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
						/* BEGINNING OF ACTION: char_set */
						{
#line 978 "psyntax.act"

    set_character ( (XIa), (XIb) ) ;
#line 603 "psyntax2.c"
						}
						/* END OF ACTION: char_set */
						switch (CURRENT_TERMINAL) {
						case 172:
							break;
						default:
							goto XL1;
						}
						ADVANCE_LEXER;
					}
					break;
				case 205:
					{
						EXP XIb;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: exp_none */
						{
#line 493 "psyntax.act"

    (XIb) = NULL_exp ;
#line 625 "psyntax2.c"
						}
						/* END OF ACTION: exp_none */
						/* BEGINNING OF ACTION: char_set */
						{
#line 978 "psyntax.act"

    set_character ( (XIa), (XIb) ) ;
#line 633 "psyntax2.c"
						}
						/* END OF ACTION: char_set */
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: 754 */
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
XR811(void)
{
	switch (CURRENT_TERMINAL) {
	case 326:
		{
			EXP XIs;
			int XIn;
			EXP XIe;

			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: string-literal */
			{
				switch (CURRENT_TERMINAL) {
				case 19:
					{
						/* BEGINNING OF EXTRACT: string-exp */
						{
#line 346 "psyntax.act"

    XIs = crt_token->pp_data.exp ;
#line 677 "psyntax2.c"
						}
						/* END OF EXTRACT: string-exp */
						ADVANCE_LEXER;
					}
					break;
				case 20:
					{
						/* BEGINNING OF EXTRACT: wstring-exp */
						{
#line 350 "psyntax.act"

    XIs = crt_token->pp_data.exp ;
#line 690 "psyntax2.c"
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
			/* BEGINNING OF ACTION: option_value_number */
			{
#line 861 "psyntax.act"

    STRING s = DEREF_str ( exp_string_lit_str ( (XIs) ) ) ;
    (XIn) = find_value_no ( s, 0 ) ;
    if ( (XIn) == -1 ) {
	report ( preproc_loc, ERR_pragma_option_bad ( s ) ) ;
    }
#line 710 "psyntax2.c"
			}
			/* END OF ACTION: option_value_number */
			/* BEGINNING OF INLINE: integer-literal */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 21:
						/* BEGINNING OF EXTRACT: integer-exp */
						{
#line 321 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 723 "psyntax2.c"
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
#line 1016 "psyntax.act"

    set_value ( (XIn), (XIe), ( unsigned long ) 0 ) ;
#line 739 "psyntax2.c"
			}
			/* END OF ACTION: analysis_exp */
		}
		break;
	case 19: case 20:
		{
			EXP XIs;
			int XIn;
			unsigned XIe;

			/* BEGINNING OF INLINE: string-literal */
			{
				switch (CURRENT_TERMINAL) {
				case 19:
					{
						/* BEGINNING OF EXTRACT: string-exp */
						{
#line 346 "psyntax.act"

    XIs = crt_token->pp_data.exp ;
#line 760 "psyntax2.c"
						}
						/* END OF EXTRACT: string-exp */
						ADVANCE_LEXER;
					}
					break;
				case 20:
					{
						/* BEGINNING OF EXTRACT: wstring-exp */
						{
#line 350 "psyntax.act"

    XIs = crt_token->pp_data.exp ;
#line 773 "psyntax2.c"
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
			/* BEGINNING OF ACTION: option_number */
			{
#line 853 "psyntax.act"

    STRING s = DEREF_str ( exp_string_lit_str ( (XIs) ) ) ;
    (XIn) = find_option_no ( s, 0 ) ;
    if ( (XIn) == -1 ) {
	report ( preproc_loc, ERR_pragma_option_bad ( s ) ) ;
    }
#line 793 "psyntax2.c"
			}
			/* END OF ACTION: option_number */
			XRoption_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 1008 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 806 "psyntax2.c"
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
XR812(void)
{
	switch (CURRENT_TERMINAL) {
	case 78:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: id_preserve_all */
			{
#line 741 "psyntax.act"

    preserve_all = 1 ;
#line 834 "psyntax2.c"
			}
			/* END OF ACTION: id_preserve_all */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1234 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 847 "psyntax2.c"
			}
			/* END OF ACTION: rescan_line */
			XRpreserve_Hlist ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
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
XRcomplete_Hstate(unsigned *XOi)
{
	unsigned XIi;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			ADVANCE_LEXER;
			XR836 (&XIi);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: error_on */
			{
#line 868 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_ON ; 
#line 888 "psyntax2.c"
			}
			/* END OF ACTION: error_on */
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
	*XOi = XIi;
}

void
XR813(TYPE *XIt)
{
	switch (CURRENT_TERMINAL) {
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
			/* BEGINNING OF ACTION: type_ellipsis */
			{
#line 897 "psyntax.act"

    accept_ellipsis ( (*XIt) ) ;
#line 933 "psyntax2.c"
			}
			/* END OF ACTION: type_ellipsis */
		}
		break;
	default:
		{
			TYPE XIs;

			/* BEGINNING OF ACTION: parse_type */
			{
#line 413 "psyntax.act"

    (XIs) = type_error ;
    parse_tok_type ( &(XIs) ) ;
    object_type ( (XIs), null_tag ) ;
#line 949 "psyntax2.c"
			}
			/* END OF ACTION: parse_type */
			/* BEGINNING OF ACTION: type_argument */
			{
#line 893 "psyntax.act"

    accept_argument ( (*XIt), (XIs) ) ;
#line 957 "psyntax2.c"
			}
			/* END OF ACTION: type_argument */
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
XRlinkage_Hstate(unsigned *XOe, unsigned *XOi)
{
	unsigned XIe;
	unsigned XIi;

	switch (CURRENT_TERMINAL) {
	case 271:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: error_off */
			{
#line 869 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_OFF ; 
#line 985 "psyntax2.c"
			}
			/* END OF ACTION: error_off */
			/* BEGINNING OF ACTION: error_off */
			{
#line 869 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_OFF ; 
#line 992 "psyntax2.c"
			}
			/* END OF ACTION: error_off */
		}
		break;
	case 65:
		{
			unsigned XIb;

			ADVANCE_LEXER;
			XRlinkage_Hdescr (&XIi);
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			case 355:
				RESTORE_LEXER;
				goto XL1;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 725 */
			{
				switch (CURRENT_TERMINAL) {
				case 272:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: error_off */
						{
#line 869 "psyntax.act"
 (XIb) = ( unsigned ) OPTION_OFF ; 
#line 1023 "psyntax2.c"
						}
						/* END OF ACTION: error_off */
					}
					break;
				case 331:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: error_warning */
						{
#line 870 "psyntax.act"
 (XIb) = ( unsigned ) OPTION_WARN ; 
#line 1035 "psyntax2.c"
						}
						/* END OF ACTION: error_warning */
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: 725 */
			XIe = XIb;
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
XR814(void)
{
	switch (CURRENT_TERMINAL) {
	case 187:
		{
			TYPE XIt;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 255:
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
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1234 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 1091 "psyntax2.c"
			}
			/* END OF ACTION: rescan_line */
			/* BEGINNING OF ACTION: parse_type */
			{
#line 413 "psyntax.act"

    (XIt) = type_error ;
    parse_tok_type ( &(XIt) ) ;
    object_type ( (XIt), null_tag ) ;
#line 1101 "psyntax2.c"
			}
			/* END OF ACTION: parse_type */
			/* BEGINNING OF ACTION: type_char_lit */
			{
#line 901 "psyntax.act"

    set_char_lit ( (XIt) ) ;
#line 1109 "psyntax2.c"
			}
			/* END OF ACTION: type_char_lit */
		}
		break;
	case 256:
		{
			int XIb;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 313:
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
			switch (CURRENT_TERMINAL) {
			case 111:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 587 */
			{
				switch (CURRENT_TERMINAL) {
				case 111:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: bool_true */
						{
#line 1204 "psyntax.act"
 (XIb) = 1 ; 
#line 1150 "psyntax2.c"
						}
						/* END OF ACTION: bool_true */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: bool_false */
						{
#line 1203 "psyntax.act"
 (XIb) = 0 ; 
#line 1161 "psyntax2.c"
						}
						/* END OF ACTION: bool_false */
					}
					break;
				}
			}
			/* END OF INLINE: 587 */
			/* BEGINNING OF ACTION: type_long_long */
			{
#line 913 "psyntax.act"

    set_long_long_type ( (XIb) ) ;
#line 1174 "psyntax2.c"
			}
			/* END OF ACTION: type_long_long */
		}
		break;
	case 302:
		{
			IDENTIFIER XIid;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 139:
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
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1220 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 1206 "psyntax2.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: 590 */
			{
				switch (CURRENT_TERMINAL) {
				case 83:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: id_none */
						{
#line 480 "psyntax.act"

    (XIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 1222 "psyntax2.c"
						}
						/* END OF ACTION: id_none */
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
#line 242 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1239 "psyntax2.c"
									}
									/* END OF EXTRACT: identifier */
									ADVANCE_LEXER;
								}
								break;
							case 3:
								{
									/* BEGINNING OF EXTRACT: namespace-name */
									{
#line 250 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1252 "psyntax2.c"
									}
									/* END OF EXTRACT: namespace-name */
									ADVANCE_LEXER;
								}
								break;
							case 4:
								{
									/* BEGINNING OF EXTRACT: statement-name */
									{
#line 254 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1265 "psyntax2.c"
									}
									/* END OF EXTRACT: statement-name */
									ADVANCE_LEXER;
								}
								break;
							case 2:
								{
									/* BEGINNING OF EXTRACT: type-name */
									{
#line 246 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1278 "psyntax2.c"
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
			}
			/* END OF INLINE: 590 */
			/* BEGINNING OF ACTION: nspace_std */
			{
#line 937 "psyntax.act"

    set_std_namespace ( (XIid) ) ;
#line 1301 "psyntax2.c"
			}
			/* END OF ACTION: nspace_std */
		}
		break;
	case 304:
		{
			CV_SPEC XIcv;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 255:
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
			/* BEGINNING OF INLINE: 588 */
			{
				switch (CURRENT_TERMINAL) {
				case 266:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: cv_none */
						{
#line 504 "psyntax.act"
 (XIcv) = cv_none ; 
#line 1335 "psyntax2.c"
						}
						/* END OF ACTION: cv_none */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: cv_const */
						{
#line 505 "psyntax.act"
 (XIcv) = cv_const ; 
#line 1346 "psyntax2.c"
						}
						/* END OF ACTION: cv_const */
					}
					break;
				}
			}
			/* END OF INLINE: 588 */
			switch (CURRENT_TERMINAL) {
			case 98:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_string_lit */
			{
#line 909 "psyntax.act"

    set_string_qual ( (XIcv) ) ;
#line 1366 "psyntax2.c"
			}
			/* END OF ACTION: type_string_lit */
		}
		break;
	case 156: case 286: case 299:
		{
			BASE_TYPE XIbt;
			TYPE XIt;

			/* BEGINNING OF INLINE: 586 */
			{
				switch (CURRENT_TERMINAL) {
				case 286:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_ptrdiff_t */
						{
#line 519 "psyntax.act"
 (XIbt) = btype_ptrdiff_t ; 
#line 1386 "psyntax2.c"
						}
						/* END OF ACTION: btype_ptrdiff_t */
					}
					break;
				case 299:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_size_t */
						{
#line 518 "psyntax.act"
 (XIbt) = btype_size_t ; 
#line 1398 "psyntax2.c"
						}
						/* END OF ACTION: btype_size_t */
					}
					break;
				case 156:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_wchar_t */
						{
#line 517 "psyntax.act"
 (XIbt) = btype_wchar_t ; 
#line 1410 "psyntax2.c"
						}
						/* END OF ACTION: btype_wchar_t */
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: 586 */
			switch (CURRENT_TERMINAL) {
			case 41:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1234 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 1433 "psyntax2.c"
			}
			/* END OF ACTION: rescan_line */
			/* BEGINNING OF ACTION: parse_type */
			{
#line 413 "psyntax.act"

    (XIt) = type_error ;
    parse_tok_type ( &(XIt) ) ;
    object_type ( (XIt), null_tag ) ;
#line 1443 "psyntax2.c"
			}
			/* END OF ACTION: parse_type */
			/* BEGINNING OF ACTION: type_builtin */
			{
#line 929 "psyntax.act"

    set_builtin_type ( (XIbt), (XIt) ) ;
#line 1451 "psyntax2.c"
			}
			/* END OF ACTION: type_builtin */
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
XR815(void)
{
	switch (CURRENT_TERMINAL) {
	case 215: case 262:
		{
			XR809 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 156: case 187: case 256: case 286:
	case 299: case 302: case 304:
		{
			XR814 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
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
XR816(void)
{
	switch (CURRENT_TERMINAL) {
	case 195:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1234 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 1514 "psyntax2.c"
			}
			/* END OF ACTION: rescan_line */
			XRconversion_Hlist ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 47: case 210:
		{
			int XIn;
			unsigned XIe;

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
			switch (CURRENT_TERMINAL) {
			case 232:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_ellipsis_ident */
			{
#line 1067 "psyntax.act"
 (XIn) = OPT_ellipsis_ident ; 
#line 1558 "psyntax2.c"
			}
			/* END OF ACTION: opt_ellipsis_ident */
			/* BEGINNING OF ACTION: error_off */
			{
#line 869 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_OFF ; 
#line 1565 "psyntax2.c"
			}
			/* END OF ACTION: error_off */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 1008 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 1573 "psyntax2.c"
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
XR817(void)
{
	switch (CURRENT_TERMINAL) {
	case 115: case 122: case 208:
		{
			BASE_TYPE XIbt;

			/* BEGINNING OF INLINE: 584 */
			{
				switch (CURRENT_TERMINAL) {
				case 208:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_none */
						{
#line 520 "psyntax.act"
 (XIbt) = btype_none ; 
#line 1607 "psyntax2.c"
						}
						/* END OF ACTION: btype_none */
					}
					break;
				case 115:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_signed */
						{
#line 515 "psyntax.act"
 (XIbt) = btype_signed ; 
#line 1619 "psyntax2.c"
						}
						/* END OF ACTION: btype_signed */
					}
					break;
				case 122:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_unsigned */
						{
#line 516 "psyntax.act"
 (XIbt) = btype_unsigned ; 
#line 1631 "psyntax2.c"
						}
						/* END OF ACTION: btype_unsigned */
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: 584 */
			/* BEGINNING OF ACTION: type_char_sign */
			{
#line 905 "psyntax.act"

    set_char_sign ( (XIbt) ) ;
#line 1646 "psyntax2.c"
			}
			/* END OF ACTION: type_char_sign */
		}
		break;
	case 17: case 18: case 19: case 20:
	case 216:
		{
			XR810 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
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
XR818(void)
{
	switch (CURRENT_TERMINAL) {
	case 312:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_token_redef */
			{
#line 1123 "psyntax.act"
 (XIn) = OPT_token_redef ; 
#line 1686 "psyntax2.c"
			}
			/* END OF ACTION: opt_token_redef */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 1008 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 1699 "psyntax2.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 313:
		{
			TYPE XIt;
			TYPE XIs;
			unsigned XIe;

			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 41:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1234 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 1724 "psyntax2.c"
			}
			/* END OF ACTION: rescan_line */
			/* BEGINNING OF ACTION: parse_type */
			{
#line 413 "psyntax.act"

    (XIt) = type_error ;
    parse_tok_type ( &(XIt) ) ;
    object_type ( (XIt), null_tag ) ;
#line 1734 "psyntax2.c"
			}
			/* END OF ACTION: parse_type */
			switch (CURRENT_TERMINAL) {
			case 48:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: parse_type */
			{
#line 413 "psyntax.act"

    (XIs) = type_error ;
    parse_tok_type ( &(XIs) ) ;
    object_type ( (XIs), null_tag ) ;
#line 1751 "psyntax2.c"
			}
			/* END OF ACTION: parse_type */
			switch (CURRENT_TERMINAL) {
			case 41:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_keyword */
			{
#line 1229 "psyntax.act"

    int t = crt_lex_token ;
    if ( t == lex_identifier || t == lex_type_Hname ||
	 t == lex_namespace_Hname || t == lex_statement_Hname ) {
	t = find_hashid ( crt_token->pp_data.id.hash ) ;
	crt_lex_token = t ;
    }
#line 1771 "psyntax2.c"
			}
			/* END OF ACTION: rescan_keyword */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: type_compatible */
			{
#line 917 "psyntax.act"

    set_compatible_type ( (XIt), (XIs), (XIe) ) ;
#line 1784 "psyntax2.c"
			}
			/* END OF ACTION: type_compatible */
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
XR819(void)
{
	switch (CURRENT_TERMINAL) {
	case 270:
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
			case 65:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 94:
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
			/* BEGINNING OF ACTION: opt_init_struct */
			{
#line 1089 "psyntax.act"
 (XIn) = OPT_init_struct ; 
#line 1856 "psyntax2.c"
			}
			/* END OF ACTION: opt_init_struct */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 1008 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 1869 "psyntax2.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 1: case 2: case 3: case 4:
		{
			IDENTIFIER XIid;

			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1220 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 1886 "psyntax2.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 242 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1899 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 250 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1912 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 254 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1925 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 246 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1938 "psyntax2.c"
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
			case 172:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: id_init */
			{
#line 728 "psyntax.act"

    allow_initialiser ( (XIid) ) ;
#line 1961 "psyntax2.c"
			}
			/* END OF ACTION: id_init */
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
XR820(void)
{
	switch (CURRENT_TERMINAL) {
	case 174:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XRconversion_Hspec (&XIn);
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 1008 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 1998 "psyntax2.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 1: case 2: case 3: case 4:
	case 172:
		{
			/* BEGINNING OF ACTION: rescan_allow_line */
			{
#line 1239 "psyntax.act"

    rescan_pragma ( lex_allow ) ;
    RESCAN_LEXER ;
#line 2012 "psyntax2.c"
			}
			/* END OF ACTION: rescan_allow_line */
			XRconversion_Hlist ();
			switch (CURRENT_TERMINAL) {
			case 172:
				break;
			case 355:
				RESTORE_LEXER;
				goto XL1;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
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
XRliteral_Hsuffix(int *XOs)
{
	int XIs;

	switch (CURRENT_TERMINAL) {
	case 111:
		{
			ADVANCE_LEXER;
			XR851 (&XIs);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 122:
		{
			ADVANCE_LEXER;
			XR850 (&XIs);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: suffix_none */
			{
#line 765 "psyntax.act"
 (XIs) = SUFFIX_NONE ; 
#line 2071 "psyntax2.c"
			}
			/* END OF ACTION: suffix_none */
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
	*XOs = XIs;
}

void
XR821(void)
{
	switch (CURRENT_TERMINAL) {
	case 255:
		{
			int XIb;
			int XIs;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: literal_set */
			{
#line 774 "psyntax.act"

    pragma_number = 1 ;
#line 2102 "psyntax2.c"
			}
			/* END OF ACTION: literal_set */
			XRliteral_Hbase (&XIb);
			XRliteral_Hsuffix (&XIs);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: literal_begin */
			{
#line 777 "psyntax.act"

    begin_literal ( (XIb), (XIs) ) ;
#line 2116 "psyntax2.c"
			}
			/* END OF ACTION: literal_begin */
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1234 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 2125 "psyntax2.c"
			}
			/* END OF ACTION: rescan_line */
			XRliteral_Hitem_Hlist ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 141: case 274:
		{
			int XIn;
			unsigned XIe;

			XR797 (&XIn);
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 1008 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2151 "psyntax2.c"
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
XRconversion_Hlist(void)
{
XL2_conversion_Hlist:;
	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 4:
		{
			IDENTIFIER XIid;

			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 242 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 2186 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 250 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 2199 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 254 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 2212 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 246 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 2225 "psyntax2.c"
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
			/* BEGINNING OF ACTION: id_conv */
			{
#line 724 "psyntax.act"

    allow_conversion ( (XIid) ) ;
#line 2241 "psyntax2.c"
			}
			/* END OF ACTION: id_conv */
			/* BEGINNING OF INLINE: conversion-list */
			goto XL2_conversion_Hlist;
			/* END OF INLINE: conversion-list */
		}
		/*UNREACHED*/
	case 355:
		return;
	default:
		break;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

void
XRdiscard_Hspec(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			ADVANCE_LEXER;
			XR830 (&XIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: opt_discard */
			{
#line 1059 "psyntax.act"
 (XIn) = OPT_discard ; 
#line 2282 "psyntax2.c"
			}
			/* END OF ACTION: opt_discard */
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
XR822(void)
{
	switch (CURRENT_TERMINAL) {
	case 312:
		{
			int XIi;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: interface_undef */
			{
#line 751 "psyntax.act"
 (XIi) = lex_undef ; 
#line 2311 "psyntax2.c"
			}
			/* END OF ACTION: interface_undef */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1253 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 2324 "psyntax2.c"
			}
			/* END OF ACTION: rescan_tag_line */
			XR479 (&XIi);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 251:
		{
			IDENTIFIER XIid;

			XRkeyword_Hid (&XIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: keyword_undef */
			{
#line 966 "psyntax.act"

    undef_keyword ( (XIid) ) ;
#line 2348 "psyntax2.c"
			}
			/* END OF ACTION: keyword_undef */
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
XRimplicit_Hspec(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 107:
		{
			ADVANCE_LEXER;
			XR841 (&XIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: opt_infer_int */
			{
#line 1084 "psyntax.act"
 (XIn) = OPT_infer_int ; 
#line 2386 "psyntax2.c"
			}
			/* END OF ACTION: opt_infer_int */
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
XRliteral_Hbase(int *XOb)
{
	int XIb;

	switch (CURRENT_TERMINAL) {
	case 196:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: base_decimal */
			{
#line 762 "psyntax.act"
 (XIb) = BASE_DECIMAL ; 
#line 2415 "psyntax2.c"
			}
			/* END OF ACTION: base_decimal */
		}
		break;
	case 229:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: base_hexadecimal */
			{
#line 763 "psyntax.act"
 (XIb) = BASE_HEXADECIMAL ; 
#line 2427 "psyntax2.c"
			}
			/* END OF ACTION: base_hexadecimal */
		}
		break;
	case 269:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: base_octal */
			{
#line 761 "psyntax.act"
 (XIb) = BASE_OCTAL ; 
#line 2439 "psyntax2.c"
			}
			/* END OF ACTION: base_octal */
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
	*XOb = XIb;
}

void
XRliteral_Hitem_Hlist(void)
{
XL2_literal_Hitem_Hlist:;
	switch (CURRENT_TERMINAL) {
	case 72:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: literal_range */
			{
#line 790 "psyntax.act"

    add_range_literal ( NULL_exp, 1 ) ;
#line 2470 "psyntax2.c"
			}
			/* END OF ACTION: literal_range */
			XRliteral_Hitem ();
			/* BEGINNING OF INLINE: or */
			{
				if ((CURRENT_TERMINAL) == 355) {
					RESTORE_LEXER;
					goto XL1;
				}
				{
					switch (CURRENT_TERMINAL) {
					case 67:
						break;
					default:
						goto XL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: or */
			/* BEGINNING OF INLINE: literal-item-list */
			goto XL2_literal_Hitem_Hlist;
			/* END OF INLINE: literal-item-list */
		}
		/*UNREACHED*/
	case 78:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: literal_infinity */
			{
#line 782 "psyntax.act"

    add_range_literal ( NULL_exp, 0 ) ;
#line 2504 "psyntax2.c"
			}
			/* END OF ACTION: literal_infinity */
			XRliteral_Hitem ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 21:
		{
			EXP XIe;

			/* BEGINNING OF INLINE: integer-literal */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 21:
						/* BEGINNING OF EXTRACT: integer-exp */
						{
#line 321 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 2528 "psyntax2.c"
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
			/* BEGINNING OF ACTION: literal_integer */
			{
#line 785 "psyntax.act"

    add_range_literal ( (XIe), 2 ) ;
#line 2544 "psyntax2.c"
			}
			/* END OF ACTION: literal_integer */
			XRliteral_Hitem ();
			/* BEGINNING OF INLINE: or */
			{
				if ((CURRENT_TERMINAL) == 355) {
					RESTORE_LEXER;
					goto XL1;
				}
				{
					switch (CURRENT_TERMINAL) {
					case 67:
						break;
					default:
						goto XL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: or */
			/* BEGINNING OF INLINE: literal-item-list */
			goto XL2_literal_Hitem_Hlist;
			/* END OF INLINE: literal-item-list */
		}
		/*UNREACHED*/
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
XRcast_Hcommand(unsigned *XOc)
{
	unsigned XIc;

	switch (CURRENT_TERMINAL) {
	case 130:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cast_const */
			{
#line 995 "psyntax.act"
 (XIc) = CAST_CONST ; 
#line 2594 "psyntax2.c"
			}
			/* END OF ACTION: cast_const */
		}
		break;
	case 145:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cast_reinterp */
			{
#line 994 "psyntax.act"
 (XIc) = CAST_REINTERP ; 
#line 2606 "psyntax2.c"
			}
			/* END OF ACTION: cast_reinterp */
		}
		break;
	case 146:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cast_static */
			{
#line 993 "psyntax.act"
 (XIc) = CAST_STATIC ; 
#line 2618 "psyntax2.c"
			}
			/* END OF ACTION: cast_static */
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
	*XOc = XIc;
}

void
XRtag_Hopt(int *XOt)
{
	int XIt;

	switch (CURRENT_TERMINAL) {
	case 308:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: bool_true */
			{
#line 1204 "psyntax.act"
 (XIt) = 1 ; 
#line 2649 "psyntax2.c"
			}
			/* END OF ACTION: bool_true */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: bool_false */
			{
#line 1203 "psyntax.act"
 (XIt) = 0 ; 
#line 2660 "psyntax2.c"
			}
			/* END OF ACTION: bool_false */
		}
		break;
	case 355:
		return;
	}
	*XOt = XIt;
}

void
XR828(int *XOt)
{
	int XIt;

	switch (CURRENT_TERMINAL) {
	case 174:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XRdiscard_Hspec (&XIn);
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 1008 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2694 "psyntax2.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 457 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 2701 "psyntax2.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: lex_unused */
			{
#line 463 "psyntax.act"
 (XIt) = lex_unused ; 
#line 2712 "psyntax2.c"
			}
			/* END OF ACTION: lex_unused */
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
	*XOt = XIt;
}

void
XR829(int *XOt)
{
	int XIt;

	switch (CURRENT_TERMINAL) {
	case 156: case 187: case 215: case 256:
	case 262: case 286: case 299: case 302:
	case 304:
		{
			XR815 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 457 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 2747 "psyntax2.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: lex_set */
			{
#line 460 "psyntax.act"
 (XIt) = lex_set ; 
#line 2758 "psyntax2.c"
			}
			/* END OF ACTION: lex_set */
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
	*XOt = XIt;
}

void
XR830(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 228:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 113:
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
			/* BEGINNING OF ACTION: opt_discard_func */
			{
#line 1060 "psyntax.act"
 (XIn) = OPT_discard_func ; 
#line 2801 "psyntax2.c"
			}
			/* END OF ACTION: opt_discard_func */
		}
		break;
	case 117:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_discard_static */
			{
#line 1061 "psyntax.act"
 (XIn) = OPT_discard_static ; 
#line 2820 "psyntax2.c"
			}
			/* END OF ACTION: opt_discard_static */
		}
		break;
	case 326:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_discard_value */
			{
#line 1062 "psyntax.act"
 (XIn) = OPT_discard_value ; 
#line 2839 "psyntax2.c"
			}
			/* END OF ACTION: opt_discard_value */
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
XR831(TOKEN *XOtok)
{
	TOKEN XItok;

	switch (CURRENT_TERMINAL) {
	case 115:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: token_signed */
			{
#line 603 "psyntax.act"

    (XItok) = make_type_token ( btype_signed | btype_int ) ;
#line 2871 "psyntax2.c"
			}
			/* END OF ACTION: token_signed */
		}
		break;
	case 122:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: token_unsigned */
			{
#line 607 "psyntax.act"

    (XItok) = make_type_token ( btype_unsigned | btype_int ) ;
#line 2884 "psyntax2.c"
			}
			/* END OF ACTION: token_unsigned */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: token_variety */
			{
#line 599 "psyntax.act"

    (XItok) = make_type_token ( btype_int ) ;
#line 2896 "psyntax2.c"
			}
			/* END OF ACTION: token_variety */
		}
		break;
	case 355:
		return;
	}
	*XOtok = XItok;
}

void
XR832(TOKEN *XOtok)
{
	TOKEN XItok;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			TOKEN XIa;
			SID_LIST_ID XIp;
			TOKEN XIb;
			TOKEN XIr;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: token_proc_begin */
			{
#line 672 "psyntax.act"

    (XIa) = begin_proc_token () ;
#line 2926 "psyntax2.c"
			}
			/* END OF ACTION: token_proc_begin */
			/* BEGINNING OF INLINE: 456 */
			{
				switch (CURRENT_TERMINAL) {
				case 177: case 188: case 218: case 225:
				case 227: case 250: case 261: case 263:
				case 282: case 296: case 303: case 305:
				case 314: case 320: case 328:
					{
						XRsimple_Htok_Hpars (&XIp);
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
#line 567 "psyntax.act"

    (XIp) = NULL_list ( IDENTIFIER ) ;
#line 2951 "psyntax2.c"
						}
						/* END OF ACTION: list_id_null */
					}
					break;
				}
			}
			/* END OF INLINE: 456 */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: token_proc_simple */
			{
#line 676 "psyntax.act"

    (XIb) = cont_proc_token ( (XIa), (XIp), (XIp) ) ;
#line 2971 "psyntax2.c"
			}
			/* END OF ACTION: token_proc_simple */
			XRtoken_Hintroduction (&XIr);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: token_proc_end */
			{
#line 684 "psyntax.act"

    (XItok) = end_proc_token ( (XIb), (XIr) ) ;
#line 2984 "psyntax2.c"
			}
			/* END OF ACTION: token_proc_end */
		}
		break;
	case 64:
		{
			TOKEN XIa;
			SID_LIST_ID XIp0;
			SID_LIST_ID XIp;
			SID_LIST_ID XIq0;
			SID_LIST_ID XIq;
			TOKEN XIb;
			TOKEN XIr;

			/* BEGINNING OF INLINE: open-brace */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 64:
						break;
					default:
						goto XL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: open-brace */
			/* BEGINNING OF ACTION: token_proc_begin */
			{
#line 672 "psyntax.act"

    (XIa) = begin_proc_token () ;
#line 3017 "psyntax2.c"
			}
			/* END OF ACTION: token_proc_begin */
			/* BEGINNING OF INLINE: 450 */
			{
				switch (CURRENT_TERMINAL) {
				case 177: case 188: case 218: case 225:
				case 227: case 250: case 261: case 263:
				case 282: case 296: case 303: case 305:
				case 314: case 320: case 328:
					{
						XRbound_Htok_Hpars (&XIp0);
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
#line 567 "psyntax.act"

    (XIp0) = NULL_list ( IDENTIFIER ) ;
#line 3042 "psyntax2.c"
						}
						/* END OF ACTION: list_id_null */
					}
					break;
				}
			}
			/* END OF INLINE: 450 */
			XIp = XIp0;
			/* BEGINNING OF INLINE: or */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 67:
						break;
					default:
						goto XL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: or */
			/* BEGINNING OF INLINE: 453 */
			{
				switch (CURRENT_TERMINAL) {
				case 218: case 261: case 282: case 303:
				case 314:
					{
						XRprog_Htok_Hpars (XIp, &XIq0);
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
#line 567 "psyntax.act"

    (XIq0) = NULL_list ( IDENTIFIER ) ;
#line 3084 "psyntax2.c"
						}
						/* END OF ACTION: list_id_null */
					}
					break;
				}
			}
			/* END OF INLINE: 453 */
			XIq = XIq0;
			/* BEGINNING OF INLINE: close-brace */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 38:
						break;
					default:
						goto XL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: close-brace */
			/* BEGINNING OF ACTION: token_proc_complex */
			{
#line 680 "psyntax.act"

    (XIb) = cont_proc_token ( (XIa), (XIp), (XIq) ) ;
#line 3111 "psyntax2.c"
			}
			/* END OF ACTION: token_proc_complex */
			XRtoken_Hintroduction (&XIr);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: token_proc_end */
			{
#line 684 "psyntax.act"

    (XItok) = end_proc_token ( (XIb), (XIr) ) ;
#line 3124 "psyntax2.c"
			}
			/* END OF ACTION: token_proc_end */
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
	*XOtok = XItok;
}

void
XR833(SID_LIST_ID *XOq)
{
	SID_LIST_ID XIq;

	switch (CURRENT_TERMINAL) {
	case 177: case 188: case 218: case 225:
	case 227: case 250: case 261: case 263:
	case 282: case 296: case 303: case 305:
	case 314: case 320: case 328:
		{
			XRsimple_Htok_Hpars (&XIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: error_comma */
			{
#line 1193 "psyntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 3168 "psyntax2.c"
			}
			/* END OF ACTION: error_comma */
			/* BEGINNING OF ACTION: list_id_null */
			{
#line 567 "psyntax.act"

    (XIq) = NULL_list ( IDENTIFIER ) ;
#line 3176 "psyntax2.c"
			}
			/* END OF ACTION: list_id_null */
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
	*XOq = XIq;
}

void
XR834(SID_LIST_ID *XOq)
{
	SID_LIST_ID XIq;

	switch (CURRENT_TERMINAL) {
	case 177: case 188: case 218: case 225:
	case 227: case 250: case 261: case 263:
	case 282: case 296: case 303: case 305:
	case 314: case 320: case 328:
		{
			XRbound_Htok_Hpars (&XIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: error_comma */
			{
#line 1193 "psyntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 3218 "psyntax2.c"
			}
			/* END OF ACTION: error_comma */
			/* BEGINNING OF ACTION: list_id_null */
			{
#line 567 "psyntax.act"

    (XIq) = NULL_list ( IDENTIFIER ) ;
#line 3226 "psyntax2.c"
			}
			/* END OF ACTION: list_id_null */
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
	*XOq = XIq;
}

void
XR835(SID_LIST_ID *XIr, SID_LIST_ID *XOq)
{
	SID_LIST_ID XIq;

	switch (CURRENT_TERMINAL) {
	case 218: case 261: case 282: case 303:
	case 314:
		{
			XRprog_Htok_Hpars (*XIr, &XIq);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: error_comma */
			{
#line 1193 "psyntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 3266 "psyntax2.c"
			}
			/* END OF ACTION: error_comma */
			/* BEGINNING OF ACTION: list_id_null */
			{
#line 567 "psyntax.act"

    (XIq) = NULL_list ( IDENTIFIER ) ;
#line 3274 "psyntax2.c"
			}
			/* END OF ACTION: list_id_null */
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
	*XOq = XIq;
}

void
XR836(unsigned *XOi)
{
	unsigned XIi;

	switch (CURRENT_TERMINAL) {
	case 192:
		{
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
#line 868 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_ON ; 
#line 3310 "psyntax2.c"
			}
			/* END OF ACTION: error_on */
		}
		break;
	case 243:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: error_off */
			{
#line 869 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_OFF ; 
#line 3329 "psyntax2.c"
			}
			/* END OF ACTION: error_off */
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
XR839(unsigned *XI837, unsigned *XOc)
{
	unsigned XIc;

	switch (CURRENT_TERMINAL) {
	case 67:
		{
			unsigned XIb;

			/* BEGINNING OF INLINE: or */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 67:
						break;
					default:
						goto XL1;
					}
					ADVANCE_LEXER;
				}
			}
			/* END OF INLINE: or */
			XRcast_Hstate (&XIb);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: cast_join */
			{
#line 997 "psyntax.act"
 (XIc) = ( (*XI837) | (XIb) ) ; 
#line 3379 "psyntax2.c"
			}
			/* END OF ACTION: cast_join */
		}
		break;
	default:
		{
			XIc = *XI837;
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
	*XOc = XIc;
}

void
XR840(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 169:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 194:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_empty_body */
			{
#line 1068 "psyntax.act"
 (XIn) = OPT_empty_body ; 
#line 3420 "psyntax2.c"
			}
			/* END OF ACTION: opt_empty_body */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: opt_semicolon_extra */
			{
#line 1118 "psyntax.act"
 (XIn) = OPT_semicolon_extra ; 
#line 3431 "psyntax2.c"
			}
			/* END OF ACTION: opt_semicolon_extra */
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
XR841(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 98:
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
			case 124:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_infer_int_cv */
			{
#line 1085 "psyntax.act"
 (XIn) = OPT_infer_int_cv ; 
#line 3474 "psyntax2.c"
			}
			/* END OF ACTION: opt_infer_int_cv */
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
			/* BEGINNING OF ACTION: opt_dspec_none */
			{
#line 1064 "psyntax.act"
 (XIn) = OPT_dspec_none ; 
#line 3493 "psyntax2.c"
			}
			/* END OF ACTION: opt_dspec_none */
		}
		break;
	case 228:
		{
			ADVANCE_LEXER;
			XR842 (&XIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
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
XRsimple_Htok_Hparam(IDENTIFIER *XOid)
{
	IDENTIFIER XIid;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TOKEN XItok;
		int XIt;
		IDENTIFIER XItid;

		XRtoken_Hintroduction (&XItok);
		XRtag_Hopt (&XIt);
		/* BEGINNING OF INLINE: 413 */
		{
			switch (CURRENT_TERMINAL) {
			case 1: case 2: case 3: case 4:
				{
					/* BEGINNING OF INLINE: any-identifier */
					{
						switch (CURRENT_TERMINAL) {
						case 1:
							{
								/* BEGINNING OF EXTRACT: identifier */
								{
#line 242 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 3551 "psyntax2.c"
								}
								/* END OF EXTRACT: identifier */
								ADVANCE_LEXER;
							}
							break;
						case 3:
							{
								/* BEGINNING OF EXTRACT: namespace-name */
								{
#line 250 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 3564 "psyntax2.c"
								}
								/* END OF EXTRACT: namespace-name */
								ADVANCE_LEXER;
							}
							break;
						case 4:
							{
								/* BEGINNING OF EXTRACT: statement-name */
								{
#line 254 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 3577 "psyntax2.c"
								}
								/* END OF EXTRACT: statement-name */
								ADVANCE_LEXER;
							}
							break;
						case 2:
							{
								/* BEGINNING OF EXTRACT: type-name */
								{
#line 246 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 3590 "psyntax2.c"
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
					/* BEGINNING OF ACTION: id_anon */
					{
#line 487 "psyntax.act"

    HASHID nm = lookup_anon () ;
    (XItid) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 3613 "psyntax2.c"
					}
					/* END OF ACTION: id_anon */
				}
				break;
			case 355:
				RESTORE_LEXER;
				goto XL1;
			}
		}
		/* END OF INLINE: 413 */
		/* BEGINNING OF ACTION: token_param */
		{
#line 647 "psyntax.act"

    (XIid) = make_tok_param ( (XItok), (XIt), (XItid) ) ;
#line 3629 "psyntax2.c"
		}
		/* END OF ACTION: token_param */
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOid = XIid;
}

void
XR842(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 176:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_param_impl */
			{
#line 1108 "psyntax.act"
 (XIn) = OPT_param_impl ; 
#line 3654 "psyntax2.c"
			}
			/* END OF ACTION: opt_param_impl */
		}
		break;
	case 113:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_dspec_none_func */
			{
#line 1065 "psyntax.act"
 (XIn) = OPT_dspec_none_func ; 
#line 3666 "psyntax2.c"
			}
			/* END OF ACTION: opt_dspec_none_func */
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
XR843(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 110:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 59:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			XR845 (&XIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 276:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 59:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			XR844 (&XIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 123:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 59:
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
			switch (CURRENT_TERMINAL) {
			case 237:
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
			/* BEGINNING OF ACTION: opt_conv_ptr_void_ptr */
			{
#line 1052 "psyntax.act"
 (XIn) = OPT_conv_ptr_void_ptr ; 
#line 3766 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_ptr_void_ptr */
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
XR844(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 110:
		{
			ADVANCE_LEXER;
			XR849 (&XIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 276:
		{
			ADVANCE_LEXER;
			XR847 (&XIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 123:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 237:
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
			/* BEGINNING OF ACTION: opt_conv_ptr_ptr_void */
			{
#line 1051 "psyntax.act"
 (XIn) = OPT_conv_ptr_ptr_void ; 
#line 3838 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_ptr_ptr_void */
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
XRliteral_Hitem(void)
{
	switch (CURRENT_TERMINAL) {
	case 41:
		{
			TYPE XIt;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: parse_type */
			{
#line 413 "psyntax.act"

    (XIt) = type_error ;
    parse_tok_type ( &(XIt) ) ;
    object_type ( (XIt), null_tag ) ;
#line 3872 "psyntax2.c"
			}
			/* END OF ACTION: parse_type */
			/* BEGINNING OF ACTION: literal_type */
			{
#line 793 "psyntax.act"

    add_type_literal ( (XIt) ) ;
#line 3880 "psyntax2.c"
			}
			/* END OF ACTION: literal_type */
		}
		break;
	case 78:
		{
			ADVANCE_LEXER;
			XR853 ();
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
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
XR845(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 104:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 237:
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
			/* BEGINNING OF ACTION: opt_conv_int_enum */
			{
#line 1040 "psyntax.act"
 (XIn) = OPT_conv_int_enum ; 
#line 3933 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_int_enum */
		}
		break;
	case 110:
		{
			ADVANCE_LEXER;
			XR848 (&XIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 276:
		{
			ADVANCE_LEXER;
			XR849 (&XIn);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
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
XR847(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 39:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_conv_ptr_ptr */
			{
#line 1048 "psyntax.act"
 (XIn) = OPT_conv_ptr_ptr ; 
#line 3984 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_ptr_ptr */
		}
		break;
	case 133:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_conv_ptr_ptr_expl */
			{
#line 1049 "psyntax.act"
 (XIn) = OPT_conv_ptr_ptr_expl ; 
#line 4003 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_ptr_ptr_expl */
		}
		break;
	case 237:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_conv_ptr_ptr_impl */
			{
#line 1050 "psyntax.act"
 (XIn) = OPT_conv_ptr_ptr_impl ; 
#line 4022 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_ptr_ptr_impl */
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
XR848(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 39:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_conv_int_int */
			{
#line 1041 "psyntax.act"
 (XIn) = OPT_conv_int_int ; 
#line 4053 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_int_int */
		}
		break;
	case 133:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_conv_int_int_expl */
			{
#line 1042 "psyntax.act"
 (XIn) = OPT_conv_int_int_expl ; 
#line 4072 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_int_int_expl */
		}
		break;
	case 237:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_conv_int_int_impl */
			{
#line 1043 "psyntax.act"
 (XIn) = OPT_conv_int_int_impl ; 
#line 4091 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_int_int_impl */
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
XR849(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 39:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_conv_int_ptr */
			{
#line 1044 "psyntax.act"
 (XIn) = OPT_conv_int_ptr ; 
#line 4122 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_int_ptr */
		}
		break;
	case 133:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_conv_int_ptr_expl */
			{
#line 1045 "psyntax.act"
 (XIn) = OPT_conv_int_ptr_expl ; 
#line 4141 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_int_ptr_expl */
		}
		break;
	case 237:
		{
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_conv_int_ptr_impl */
			{
#line 1046 "psyntax.act"
 (XIn) = OPT_conv_int_ptr_impl ; 
#line 4160 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_int_ptr_impl */
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
XR850(int *XOs)
{
	int XIs;

	switch (CURRENT_TERMINAL) {
	case 111:
		{
			ADVANCE_LEXER;
			XR852 (&XIs);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: suffix_u */
			{
#line 766 "psyntax.act"
 (XIs) = SUFFIX_U ; 
#line 4200 "psyntax2.c"
			}
			/* END OF ACTION: suffix_u */
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
	*XOs = XIs;
}

void
XR851(int *XOs)
{
	int XIs;

	switch (CURRENT_TERMINAL) {
	case 111:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: suffix_ll */
			{
#line 769 "psyntax.act"
 (XIs) = SUFFIX_LL ; 
#line 4229 "psyntax2.c"
			}
			/* END OF ACTION: suffix_ll */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: suffix_l */
			{
#line 767 "psyntax.act"
 (XIs) = SUFFIX_L ; 
#line 4240 "psyntax2.c"
			}
			/* END OF ACTION: suffix_l */
		}
		break;
	case 355:
		return;
	}
	*XOs = XIs;
}

void
XRoption_Hnumber(int *XOn)
{
	int XIn;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		EXP XIs;

		switch (CURRENT_TERMINAL) {
		case 273:
			break;
		default:
			goto XL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF INLINE: string-literal */
		{
			switch (CURRENT_TERMINAL) {
			case 19:
				{
					/* BEGINNING OF EXTRACT: string-exp */
					{
#line 346 "psyntax.act"

    XIs = crt_token->pp_data.exp ;
#line 4279 "psyntax2.c"
					}
					/* END OF EXTRACT: string-exp */
					ADVANCE_LEXER;
				}
				break;
			case 20:
				{
					/* BEGINNING OF EXTRACT: wstring-exp */
					{
#line 350 "psyntax.act"

    XIs = crt_token->pp_data.exp ;
#line 4292 "psyntax2.c"
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
		/* BEGINNING OF ACTION: option_number */
		{
#line 853 "psyntax.act"

    STRING s = DEREF_str ( exp_string_lit_str ( (XIs) ) ) ;
    (XIn) = find_option_no ( s, 0 ) ;
    if ( (XIn) == -1 ) {
	report ( preproc_loc, ERR_pragma_option_bad ( s ) ) ;
    }
#line 4312 "psyntax2.c"
		}
		/* END OF ACTION: option_number */
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOn = XIn;
}

void
XR852(int *XOs)
{
	int XIs;

	switch (CURRENT_TERMINAL) {
	case 111:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: suffix_ull */
			{
#line 770 "psyntax.act"
 (XIs) = SUFFIX_ULL ; 
#line 4337 "psyntax2.c"
			}
			/* END OF ACTION: suffix_ull */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: suffix_ul */
			{
#line 768 "psyntax.act"
 (XIs) = SUFFIX_UL ; 
#line 4348 "psyntax2.c"
			}
			/* END OF ACTION: suffix_ul */
		}
		break;
	case 355:
		return;
	}
	*XOs = XIs;
}

void
XR853(void)
{
	switch (CURRENT_TERMINAL) {
	case 78:
		{
			unsigned XIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_keyword */
			{
#line 1229 "psyntax.act"

    int t = crt_lex_token ;
    if ( t == lex_identifier || t == lex_type_Hname ||
	 t == lex_namespace_Hname || t == lex_statement_Hname ) {
	t = find_hashid ( crt_token->pp_data.id.hash ) ;
	crt_lex_token = t ;
    }
#line 4378 "psyntax2.c"
			}
			/* END OF ACTION: rescan_keyword */
			/* BEGINNING OF INLINE: 532 */
			{
				switch (CURRENT_TERMINAL) {
				case 172: case 205: case 331:
					{
						XRallow_Hstate (&XIa);
						if ((CURRENT_TERMINAL) == 355) {
							RESTORE_LEXER;
							goto XL1;
						}
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: error_on */
						{
#line 868 "psyntax.act"
 (XIa) = ( unsigned ) OPTION_ON ; 
#line 4399 "psyntax2.c"
						}
						/* END OF ACTION: error_on */
					}
					break;
				}
			}
			/* END OF INLINE: 532 */
			switch (CURRENT_TERMINAL) {
			case 41:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: literal_star */
			{
#line 801 "psyntax.act"

    add_token_literal ( NULL_id, (XIa) ) ;
#line 4419 "psyntax2.c"
			}
			/* END OF ACTION: literal_star */
		}
		break;
	case 41: case 172: case 205: case 331:
		{
			unsigned XIa;
			IDENTIFIER XIid;

			/* BEGINNING OF ACTION: rescan_keyword */
			{
#line 1229 "psyntax.act"

    int t = crt_lex_token ;
    if ( t == lex_identifier || t == lex_type_Hname ||
	 t == lex_namespace_Hname || t == lex_statement_Hname ) {
	t = find_hashid ( crt_token->pp_data.id.hash ) ;
	crt_lex_token = t ;
    }
#line 4439 "psyntax2.c"
			}
			/* END OF ACTION: rescan_keyword */
			/* BEGINNING OF INLINE: 531 */
			{
				switch (CURRENT_TERMINAL) {
				case 172: case 205: case 331:
					{
						XRallow_Hstate (&XIa);
						if ((CURRENT_TERMINAL) == 355) {
							RESTORE_LEXER;
							goto XL1;
						}
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: error_off */
						{
#line 869 "psyntax.act"
 (XIa) = ( unsigned ) OPTION_OFF ; 
#line 4460 "psyntax2.c"
						}
						/* END OF ACTION: error_off */
					}
					break;
				}
			}
			/* END OF INLINE: 531 */
			switch (CURRENT_TERMINAL) {
			case 41:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1220 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 4483 "psyntax2.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 242 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4496 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 250 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4509 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 254 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4522 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 246 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4535 "psyntax2.c"
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
			/* BEGINNING OF ACTION: literal_token */
			{
#line 797 "psyntax.act"

    add_token_literal ( (XIid), (XIa) ) ;
#line 4551 "psyntax2.c"
			}
			/* END OF ACTION: literal_token */
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
XR854(int *XOt)
{
	int XIt;

	switch (CURRENT_TERMINAL) {
	case 326:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_discard */
			{
#line 451 "psyntax.act"
 (XIt) = lex_discard ; 
#line 4580 "psyntax2.c"
			}
			/* END OF ACTION: lex_discard */
		}
		break;
	case 327:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_unused */
			{
#line 463 "psyntax.act"
 (XIt) = lex_unused ; 
#line 4592 "psyntax2.c"
			}
			/* END OF ACTION: lex_unused */
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
	*XOt = XIt;
}

void
XRbound_Htok_Hparam(IDENTIFIER *XOid)
{
	IDENTIFIER XIid;

	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
	{
		TOKEN XItok;
		int XIt;
		IDENTIFIER XItid;

		XRtoken_Hintroduction (&XItok);
		XRtag_Hopt (&XIt);
		/* BEGINNING OF INLINE: any-identifier */
		{
			switch (CURRENT_TERMINAL) {
			case 1:
				{
					/* BEGINNING OF EXTRACT: identifier */
					{
#line 242 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 4635 "psyntax2.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			case 3:
				{
					/* BEGINNING OF EXTRACT: namespace-name */
					{
#line 250 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 4648 "psyntax2.c"
					}
					/* END OF EXTRACT: namespace-name */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: statement-name */
					{
#line 254 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 4661 "psyntax2.c"
					}
					/* END OF EXTRACT: statement-name */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: type-name */
					{
#line 246 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 4674 "psyntax2.c"
					}
					/* END OF EXTRACT: type-name */
					ADVANCE_LEXER;
				}
				break;
			case 355:
				RESTORE_LEXER;
				goto XL1;
			default:
				goto XL1;
			}
		}
		/* END OF INLINE: any-identifier */
		/* BEGINNING OF ACTION: token_param */
		{
#line 647 "psyntax.act"

    (XIid) = make_tok_param ( (XItok), (XIt), (XItid) ) ;
#line 4693 "psyntax2.c"
		}
		/* END OF ACTION: token_param */
	}
	goto XL0;
XL1:;
	SAVE_LEXER (355);
	return;
XL0:;
	*XOid = XIid;
}

void
XR855(int *XOt)
{
	int XIt;

	switch (CURRENT_TERMINAL) {
	case 289:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_reachable */
			{
#line 458 "psyntax.act"
 (XIt) = lex_reachable ; 
#line 4718 "psyntax2.c"
			}
			/* END OF ACTION: lex_reachable */
		}
		break;
	case 323:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_unreachable */
			{
#line 462 "psyntax.act"
 (XIt) = lex_unreachable ; 
#line 4730 "psyntax2.c"
			}
			/* END OF ACTION: lex_unreachable */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: lex_set */
			{
#line 460 "psyntax.act"
 (XIt) = lex_set ; 
#line 4741 "psyntax2.c"
			}
			/* END OF ACTION: lex_set */
		}
		break;
	case 355:
		return;
	}
	*XOt = XIt;
}

void
XRerror_Hseverity(int *XOe)
{
	int XIe;

	switch (CURRENT_TERMINAL) {
	case 172:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_off */
			{
#line 1024 "psyntax.act"
 (XIe) = OPT_none ; 
#line 4765 "psyntax2.c"
			}
			/* END OF ACTION: opt_off */
		}
		break;
	case 205:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_on */
			{
#line 1023 "psyntax.act"
 (XIe) = OPT_error ; 
#line 4777 "psyntax2.c"
			}
			/* END OF ACTION: opt_on */
		}
		break;
	case 271:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_off */
			{
#line 1024 "psyntax.act"
 (XIe) = OPT_none ; 
#line 4789 "psyntax2.c"
			}
			/* END OF ACTION: opt_off */
		}
		break;
	case 272:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_on */
			{
#line 1023 "psyntax.act"
 (XIe) = OPT_error ; 
#line 4801 "psyntax2.c"
			}
			/* END OF ACTION: opt_on */
		}
		break;
	case 331:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_warning */
			{
#line 1025 "psyntax.act"
 (XIe) = OPT_warning ; 
#line 4813 "psyntax2.c"
			}
			/* END OF ACTION: opt_warning */
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
XRpreserve_Hlist(void)
{
XL2_preserve_Hlist:;
	switch (CURRENT_TERMINAL) {
	case 1: case 2: case 3: case 4:
		{
			IDENTIFIER XIid;

			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 242 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4850 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 250 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4863 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 254 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4876 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 246 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4889 "psyntax2.c"
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
			/* BEGINNING OF ACTION: id_preserve */
			{
#line 736 "psyntax.act"

    preserve_id ( (XIid), lex_preserve ) ;
#line 4905 "psyntax2.c"
			}
			/* END OF ACTION: id_preserve */
			/* BEGINNING OF INLINE: preserve-list */
			goto XL2_preserve_Hlist;
			/* END OF INLINE: preserve-list */
		}
		/*UNREACHED*/
	case 355:
		return;
	default:
		break;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

void
XR860(TYPE *XOt)
{
	TYPE XIt;

	switch (CURRENT_TERMINAL) {
	case 281:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_printf */
			{
#line 941 "psyntax.act"
 (XIt) = type_printf ; 
#line 4937 "psyntax2.c"
			}
			/* END OF ACTION: type_printf */
		}
		break;
	case 297:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_scanf */
			{
#line 942 "psyntax.act"
 (XIt) = type_scanf ; 
#line 4949 "psyntax2.c"
			}
			/* END OF ACTION: type_scanf */
		}
		break;
	case 156:
		{
			ADVANCE_LEXER;
			XR861 (&XIt);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
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
	*XOt = XIt;
}

void
XR479(int *XIi)
{
	if ((CURRENT_TERMINAL) == 355) {
		return;
	}
XL2_479:;
	{
		IDENTIFIER XInm;
		IDENTIFIER XI857;
		IDENTIFIER XIid;

		/* BEGINNING OF ACTION: is_operator */
		{
#line 436 "psyntax.act"

    (XI0) = predict_operator () ;
#line 4994 "psyntax2.c"
		}
		/* END OF ACTION: is_operator */
		if (!XI0)
			goto XL3;
		/* BEGINNING OF ACTION: parse_operator */
		{
#line 431 "psyntax.act"

    (XInm) = DEREF_id ( hashid_id ( KEYWORD ( lex_zzzz ) ) ) ;
    parse_operator ( &(XInm) ) ;
#line 5005 "psyntax2.c"
		}
		/* END OF ACTION: parse_operator */
		/* BEGINNING OF ACTION: token_name */
		{
#line 692 "psyntax.act"

    (XI857) = check_id ( crt_namespace, (XInm), 0 ) ;
#line 5013 "psyntax2.c"
		}
		/* END OF ACTION: token_name */
		XR781 (XI857, &XIid);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto XL1;
		}
		/* BEGINNING OF ACTION: token_interface */
		{
#line 708 "psyntax.act"

    token_interface ( (XIid), (*XIi) ) ;
#line 5026 "psyntax2.c"
		}
		/* END OF ACTION: token_interface */
		/* BEGINNING OF ACTION: rescan_tag_line */
		{
#line 1253 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 5039 "psyntax2.c"
		}
		/* END OF ACTION: rescan_tag_line */
		/* BEGINNING OF INLINE: 479 */
		goto XL2_479;
		/* END OF INLINE: 479 */
	}
	/*UNREACHED*/
XL3:;
	switch (CURRENT_TERMINAL) {
	case 308:
		{
			IDENTIFIER XInm;
			IDENTIFIER XI858;
			IDENTIFIER XIid;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1220 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 5064 "psyntax2.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 242 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5077 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 250 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5090 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 254 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5103 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 246 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5116 "psyntax2.c"
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
			/* BEGINNING OF ACTION: token_tag */
			{
#line 696 "psyntax.act"

    (XI858) = find_tag_token ( (XInm) ) ;
#line 5132 "psyntax2.c"
			}
			/* END OF ACTION: token_tag */
			XR781 (XI858, &XIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: token_interface */
			{
#line 708 "psyntax.act"

    token_interface ( (XIid), (*XIi) ) ;
#line 5145 "psyntax2.c"
			}
			/* END OF ACTION: token_interface */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1253 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 5158 "psyntax2.c"
			}
			/* END OF ACTION: rescan_tag_line */
			/* BEGINNING OF INLINE: 479 */
			goto XL2_479;
			/* END OF INLINE: 479 */
		}
		/*UNREACHED*/
	case 1: case 2: case 3: case 4:
		{
			IDENTIFIER XInm;
			IDENTIFIER XI859;
			IDENTIFIER XIid;

			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 242 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5182 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 250 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5195 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 254 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5208 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 246 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5221 "psyntax2.c"
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
			/* BEGINNING OF ACTION: token_name */
			{
#line 692 "psyntax.act"

    (XI859) = check_id ( crt_namespace, (XInm), 0 ) ;
#line 5237 "psyntax2.c"
			}
			/* END OF ACTION: token_name */
			XR781 (XI859, &XIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: token_interface */
			{
#line 708 "psyntax.act"

    token_interface ( (XIid), (*XIi) ) ;
#line 5250 "psyntax2.c"
			}
			/* END OF ACTION: token_interface */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1253 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 5263 "psyntax2.c"
			}
			/* END OF ACTION: rescan_tag_line */
			/* BEGINNING OF INLINE: 479 */
			goto XL2_479;
			/* END OF INLINE: 479 */
		}
		/*UNREACHED*/
	case 51:
		{
			IDENTIFIER XInm;
			IDENTIFIER XI856;
			IDENTIFIER XIid;

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
#line 1220 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 5298 "psyntax2.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 242 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5311 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 250 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5324 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 254 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5337 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 246 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5350 "psyntax2.c"
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
			/* BEGINNING OF ACTION: token_extern */
			{
#line 704 "psyntax.act"

    (XI856) = find_ext_token ( (XInm) ) ;
#line 5366 "psyntax2.c"
			}
			/* END OF ACTION: token_extern */
			XR781 (XI856, &XIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: token_interface */
			{
#line 708 "psyntax.act"

    token_interface ( (XIid), (*XIi) ) ;
#line 5379 "psyntax2.c"
			}
			/* END OF ACTION: token_interface */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1253 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 5392 "psyntax2.c"
			}
			/* END OF ACTION: rescan_tag_line */
			/* BEGINNING OF INLINE: 479 */
			goto XL2_479;
			/* END OF INLINE: 479 */
		}
		/*UNREACHED*/
	default:
		break;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

/* END OF FILE */
