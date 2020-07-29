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
#line 166 "psyntax.act"



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


#line 101 "psyntax2.c"

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
#line 1173 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 121 "psyntax2.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 195 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 134 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 203 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 147 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 207 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 160 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 199 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 173 "psyntax2.c"
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
#line 821 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_ON ; 
#line 203 "psyntax2.c"
						}
						/* END OF ACTION: error_on */
					}
					break;
				}
			}
			/* END OF INLINE: 769 */
			/* BEGINNING OF ACTION: check_use */
			{
#line 778 "psyntax.act"

    use_option ( (XIid), (XIe) ) ;
#line 216 "psyntax2.c"
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
#line 830 "psyntax.act"

    if ( (XIn) >= 0 ) {
	no_error_args = 1 ;
	report ( crt_loc, make_error ( (XIn) ) ) ;
	no_error_args = 0 ;
    }
#line 239 "psyntax2.c"
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
#line 1089 "psyntax.act"
 (XIn) = OPT_VAL_maximum_error ; 
#line 276 "psyntax2.c"
			}
			/* END OF ACTION: opt_val_maximum_error */
			/* BEGINNING OF INLINE: integer-literal */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 21:
						/* BEGINNING OF EXTRACT: integer-exp */
						{
#line 274 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 289 "psyntax2.c"
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
#line 969 "psyntax.act"

    set_value ( (XIn), (XIe), ( unsigned long ) 0 ) ;
#line 305 "psyntax2.c"
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
#line 274 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 335 "psyntax2.c"
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
#line 1090 "psyntax.act"
 (XIn) = OPT_VAL_name_limit ; 
#line 355 "psyntax2.c"
			}
			/* END OF ACTION: opt_val_name_limit */
			/* BEGINNING OF ACTION: opt_name_limit */
			{
#line 1055 "psyntax.act"
 (XIm) = OPT_name_limit ; 
#line 362 "psyntax2.c"
			}
			/* END OF ACTION: opt_name_limit */
			/* BEGINNING OF ACTION: analysis_exp */
			{
#line 969 "psyntax.act"

    set_value ( (XIn), (XIe), ( unsigned long ) 0 ) ;
#line 370 "psyntax2.c"
			}
			/* END OF ACTION: analysis_exp */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 961 "psyntax.act"

    set_option ( (XIm), (XIi) ) ;
#line 378 "psyntax2.c"
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
#line 1025 "psyntax.act"
 (XIn) = OPT_escape_overflow ; 
#line 415 "psyntax2.c"
			}
			/* END OF ACTION: opt_escape_overflow */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 961 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 428 "psyntax2.c"
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
#line 291 "psyntax.act"

    XIa = crt_token->pp_data.exp ;
#line 452 "psyntax2.c"
									}
									/* END OF EXTRACT: char-exp */
									ADVANCE_LEXER;
								}
								break;
							case 18:
								{
									/* BEGINNING OF EXTRACT: wchar-exp */
									{
#line 295 "psyntax.act"

    XIa = crt_token->pp_data.exp ;
#line 465 "psyntax2.c"
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
#line 299 "psyntax.act"

    XIa = crt_token->pp_data.exp ;
#line 490 "psyntax2.c"
									}
									/* END OF EXTRACT: string-exp */
									ADVANCE_LEXER;
								}
								break;
							case 20:
								{
									/* BEGINNING OF EXTRACT: wstring-exp */
									{
#line 303 "psyntax.act"

    XIa = crt_token->pp_data.exp ;
#line 503 "psyntax2.c"
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
#line 291 "psyntax.act"

    XIb = crt_token->pp_data.exp ;
#line 539 "psyntax2.c"
									}
									/* END OF EXTRACT: char-exp */
									ADVANCE_LEXER;
								}
								break;
							case 18:
								{
									/* BEGINNING OF EXTRACT: wchar-exp */
									{
#line 295 "psyntax.act"

    XIb = crt_token->pp_data.exp ;
#line 552 "psyntax2.c"
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
#line 931 "psyntax.act"

    set_character ( (XIa), (XIb) ) ;
#line 568 "psyntax2.c"
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
#line 446 "psyntax.act"

    (XIb) = NULL_exp ;
#line 590 "psyntax2.c"
						}
						/* END OF ACTION: exp_none */
						/* BEGINNING OF ACTION: char_set */
						{
#line 931 "psyntax.act"

    set_character ( (XIa), (XIb) ) ;
#line 598 "psyntax2.c"
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
#line 299 "psyntax.act"

    XIs = crt_token->pp_data.exp ;
#line 642 "psyntax2.c"
						}
						/* END OF EXTRACT: string-exp */
						ADVANCE_LEXER;
					}
					break;
				case 20:
					{
						/* BEGINNING OF EXTRACT: wstring-exp */
						{
#line 303 "psyntax.act"

    XIs = crt_token->pp_data.exp ;
#line 655 "psyntax2.c"
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
#line 814 "psyntax.act"

    STRING s = DEREF_str ( exp_string_lit_str ( (XIs) ) ) ;
    (XIn) = find_value_no ( s, 0 ) ;
    if ( (XIn) == -1 ) {
	report ( preproc_loc, ERR_pragma_option_bad ( s ) ) ;
    }
#line 675 "psyntax2.c"
			}
			/* END OF ACTION: option_value_number */
			/* BEGINNING OF INLINE: integer-literal */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 21:
						/* BEGINNING OF EXTRACT: integer-exp */
						{
#line 274 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 688 "psyntax2.c"
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
#line 969 "psyntax.act"

    set_value ( (XIn), (XIe), ( unsigned long ) 0 ) ;
#line 704 "psyntax2.c"
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
#line 299 "psyntax.act"

    XIs = crt_token->pp_data.exp ;
#line 725 "psyntax2.c"
						}
						/* END OF EXTRACT: string-exp */
						ADVANCE_LEXER;
					}
					break;
				case 20:
					{
						/* BEGINNING OF EXTRACT: wstring-exp */
						{
#line 303 "psyntax.act"

    XIs = crt_token->pp_data.exp ;
#line 738 "psyntax2.c"
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
#line 806 "psyntax.act"

    STRING s = DEREF_str ( exp_string_lit_str ( (XIs) ) ) ;
    (XIn) = find_option_no ( s, 0 ) ;
    if ( (XIn) == -1 ) {
	report ( preproc_loc, ERR_pragma_option_bad ( s ) ) ;
    }
#line 758 "psyntax2.c"
			}
			/* END OF ACTION: option_number */
			XRoption_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 961 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 771 "psyntax2.c"
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
#line 694 "psyntax.act"

    preserve_all = 1 ;
#line 799 "psyntax2.c"
			}
			/* END OF ACTION: id_preserve_all */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1187 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 812 "psyntax2.c"
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
#line 821 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_ON ; 
#line 853 "psyntax2.c"
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
#line 850 "psyntax.act"

    accept_ellipsis ( (*XIt) ) ;
#line 898 "psyntax2.c"
			}
			/* END OF ACTION: type_ellipsis */
		}
		break;
	default:
		{
			TYPE XIs;

			/* BEGINNING OF ACTION: parse_type */
			{
#line 366 "psyntax.act"

    (XIs) = type_error ;
    parse_tok_type ( &(XIs) ) ;
    object_type ( (XIs), null_tag ) ;
#line 914 "psyntax2.c"
			}
			/* END OF ACTION: parse_type */
			/* BEGINNING OF ACTION: type_argument */
			{
#line 846 "psyntax.act"

    accept_argument ( (*XIt), (XIs) ) ;
#line 922 "psyntax2.c"
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
#line 822 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_OFF ; 
#line 950 "psyntax2.c"
			}
			/* END OF ACTION: error_off */
			/* BEGINNING OF ACTION: error_off */
			{
#line 822 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_OFF ; 
#line 957 "psyntax2.c"
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
#line 822 "psyntax.act"
 (XIb) = ( unsigned ) OPTION_OFF ; 
#line 988 "psyntax2.c"
						}
						/* END OF ACTION: error_off */
					}
					break;
				case 331:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: error_warning */
						{
#line 823 "psyntax.act"
 (XIb) = ( unsigned ) OPTION_WARN ; 
#line 1000 "psyntax2.c"
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
#line 1187 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 1056 "psyntax2.c"
			}
			/* END OF ACTION: rescan_line */
			/* BEGINNING OF ACTION: parse_type */
			{
#line 366 "psyntax.act"

    (XIt) = type_error ;
    parse_tok_type ( &(XIt) ) ;
    object_type ( (XIt), null_tag ) ;
#line 1066 "psyntax2.c"
			}
			/* END OF ACTION: parse_type */
			/* BEGINNING OF ACTION: type_char_lit */
			{
#line 854 "psyntax.act"

    set_char_lit ( (XIt) ) ;
#line 1074 "psyntax2.c"
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
#line 1157 "psyntax.act"
 (XIb) = 1 ; 
#line 1115 "psyntax2.c"
						}
						/* END OF ACTION: bool_true */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: bool_false */
						{
#line 1156 "psyntax.act"
 (XIb) = 0 ; 
#line 1126 "psyntax2.c"
						}
						/* END OF ACTION: bool_false */
					}
					break;
				}
			}
			/* END OF INLINE: 587 */
			/* BEGINNING OF ACTION: type_long_long */
			{
#line 866 "psyntax.act"

    set_long_long_type ( (XIb) ) ;
#line 1139 "psyntax2.c"
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
#line 1173 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 1171 "psyntax2.c"
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
#line 433 "psyntax.act"

    (XIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 1187 "psyntax2.c"
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
#line 195 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1204 "psyntax2.c"
									}
									/* END OF EXTRACT: identifier */
									ADVANCE_LEXER;
								}
								break;
							case 3:
								{
									/* BEGINNING OF EXTRACT: namespace-name */
									{
#line 203 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1217 "psyntax2.c"
									}
									/* END OF EXTRACT: namespace-name */
									ADVANCE_LEXER;
								}
								break;
							case 4:
								{
									/* BEGINNING OF EXTRACT: statement-name */
									{
#line 207 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1230 "psyntax2.c"
									}
									/* END OF EXTRACT: statement-name */
									ADVANCE_LEXER;
								}
								break;
							case 2:
								{
									/* BEGINNING OF EXTRACT: type-name */
									{
#line 199 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1243 "psyntax2.c"
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
#line 890 "psyntax.act"

    set_std_namespace ( (XIid) ) ;
#line 1266 "psyntax2.c"
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
#line 457 "psyntax.act"
 (XIcv) = cv_none ; 
#line 1300 "psyntax2.c"
						}
						/* END OF ACTION: cv_none */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: cv_const */
						{
#line 458 "psyntax.act"
 (XIcv) = cv_const ; 
#line 1311 "psyntax2.c"
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
#line 862 "psyntax.act"

    set_string_qual ( (XIcv) ) ;
#line 1331 "psyntax2.c"
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
#line 472 "psyntax.act"
 (XIbt) = btype_ptrdiff_t ; 
#line 1351 "psyntax2.c"
						}
						/* END OF ACTION: btype_ptrdiff_t */
					}
					break;
				case 299:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_size_t */
						{
#line 471 "psyntax.act"
 (XIbt) = btype_size_t ; 
#line 1363 "psyntax2.c"
						}
						/* END OF ACTION: btype_size_t */
					}
					break;
				case 156:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_wchar_t */
						{
#line 470 "psyntax.act"
 (XIbt) = btype_wchar_t ; 
#line 1375 "psyntax2.c"
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
#line 1187 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 1398 "psyntax2.c"
			}
			/* END OF ACTION: rescan_line */
			/* BEGINNING OF ACTION: parse_type */
			{
#line 366 "psyntax.act"

    (XIt) = type_error ;
    parse_tok_type ( &(XIt) ) ;
    object_type ( (XIt), null_tag ) ;
#line 1408 "psyntax2.c"
			}
			/* END OF ACTION: parse_type */
			/* BEGINNING OF ACTION: type_builtin */
			{
#line 882 "psyntax.act"

    set_builtin_type ( (XIbt), (XIt) ) ;
#line 1416 "psyntax2.c"
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
#line 1187 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 1479 "psyntax2.c"
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
#line 1020 "psyntax.act"
 (XIn) = OPT_ellipsis_ident ; 
#line 1523 "psyntax2.c"
			}
			/* END OF ACTION: opt_ellipsis_ident */
			/* BEGINNING OF ACTION: error_off */
			{
#line 822 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_OFF ; 
#line 1530 "psyntax2.c"
			}
			/* END OF ACTION: error_off */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 961 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 1538 "psyntax2.c"
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
#line 473 "psyntax.act"
 (XIbt) = btype_none ; 
#line 1572 "psyntax2.c"
						}
						/* END OF ACTION: btype_none */
					}
					break;
				case 115:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_signed */
						{
#line 468 "psyntax.act"
 (XIbt) = btype_signed ; 
#line 1584 "psyntax2.c"
						}
						/* END OF ACTION: btype_signed */
					}
					break;
				case 122:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_unsigned */
						{
#line 469 "psyntax.act"
 (XIbt) = btype_unsigned ; 
#line 1596 "psyntax2.c"
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
#line 858 "psyntax.act"

    set_char_sign ( (XIbt) ) ;
#line 1611 "psyntax2.c"
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
#line 1076 "psyntax.act"
 (XIn) = OPT_token_redef ; 
#line 1651 "psyntax2.c"
			}
			/* END OF ACTION: opt_token_redef */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 961 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 1664 "psyntax2.c"
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
#line 1187 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 1689 "psyntax2.c"
			}
			/* END OF ACTION: rescan_line */
			/* BEGINNING OF ACTION: parse_type */
			{
#line 366 "psyntax.act"

    (XIt) = type_error ;
    parse_tok_type ( &(XIt) ) ;
    object_type ( (XIt), null_tag ) ;
#line 1699 "psyntax2.c"
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
#line 366 "psyntax.act"

    (XIs) = type_error ;
    parse_tok_type ( &(XIs) ) ;
    object_type ( (XIs), null_tag ) ;
#line 1716 "psyntax2.c"
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
#line 1182 "psyntax.act"

    int t = crt_lex_token ;
    if ( t == lex_identifier || t == lex_type_Hname ||
	 t == lex_namespace_Hname || t == lex_statement_Hname ) {
	t = find_hashid ( crt_token->pp_data.id.hash ) ;
	crt_lex_token = t ;
    }
#line 1736 "psyntax2.c"
			}
			/* END OF ACTION: rescan_keyword */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: type_compatible */
			{
#line 870 "psyntax.act"

    set_compatible_type ( (XIt), (XIs), (XIe) ) ;
#line 1749 "psyntax2.c"
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
#line 1042 "psyntax.act"
 (XIn) = OPT_init_struct ; 
#line 1821 "psyntax2.c"
			}
			/* END OF ACTION: opt_init_struct */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 961 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 1834 "psyntax2.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 1: case 2: case 3: case 4:
		{
			IDENTIFIER XIid;

			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1173 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 1851 "psyntax2.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 195 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1864 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 203 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1877 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 207 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1890 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 199 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1903 "psyntax2.c"
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
#line 681 "psyntax.act"

    allow_initialiser ( (XIid) ) ;
#line 1926 "psyntax2.c"
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
#line 961 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 1963 "psyntax2.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 1: case 2: case 3: case 4:
	case 172:
		{
			/* BEGINNING OF ACTION: rescan_allow_line */
			{
#line 1192 "psyntax.act"

    rescan_pragma ( lex_allow ) ;
    RESCAN_LEXER ;
#line 1977 "psyntax2.c"
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
#line 718 "psyntax.act"
 (XIs) = SUFFIX_NONE ; 
#line 2036 "psyntax2.c"
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
#line 727 "psyntax.act"

    pragma_number = 1 ;
#line 2067 "psyntax2.c"
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
#line 730 "psyntax.act"

    begin_literal ( (XIb), (XIs) ) ;
#line 2081 "psyntax2.c"
			}
			/* END OF ACTION: literal_begin */
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1187 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 2090 "psyntax2.c"
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
#line 961 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2116 "psyntax2.c"
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
#line 195 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 2151 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 203 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 2164 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 207 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 2177 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 199 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 2190 "psyntax2.c"
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
#line 677 "psyntax.act"

    allow_conversion ( (XIid) ) ;
#line 2206 "psyntax2.c"
			}
			/* END OF ACTION: id_conv */
			/* BEGINNING OF INLINE: conversion-list */
			goto XL2_conversion_Hlist;
			/* END OF INLINE: conversion-list */
		}
		UNREACHED;
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
#line 1012 "psyntax.act"
 (XIn) = OPT_discard ; 
#line 2247 "psyntax2.c"
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
#line 704 "psyntax.act"
 (XIi) = lex_undef ; 
#line 2276 "psyntax2.c"
			}
			/* END OF ACTION: interface_undef */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1206 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 2289 "psyntax2.c"
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
#line 919 "psyntax.act"

    undef_keyword ( (XIid) ) ;
#line 2313 "psyntax2.c"
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
#line 1037 "psyntax.act"
 (XIn) = OPT_infer_int ; 
#line 2351 "psyntax2.c"
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
#line 715 "psyntax.act"
 (XIb) = BASE_DECIMAL ; 
#line 2380 "psyntax2.c"
			}
			/* END OF ACTION: base_decimal */
		}
		break;
	case 229:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: base_hexadecimal */
			{
#line 716 "psyntax.act"
 (XIb) = BASE_HEXADECIMAL ; 
#line 2392 "psyntax2.c"
			}
			/* END OF ACTION: base_hexadecimal */
		}
		break;
	case 269:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: base_octal */
			{
#line 714 "psyntax.act"
 (XIb) = BASE_OCTAL ; 
#line 2404 "psyntax2.c"
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
#line 743 "psyntax.act"

    add_range_literal ( NULL_exp, 1 ) ;
#line 2435 "psyntax2.c"
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
		UNREACHED;
	case 78:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: literal_infinity */
			{
#line 735 "psyntax.act"

    add_range_literal ( NULL_exp, 0 ) ;
#line 2469 "psyntax2.c"
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
#line 274 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 2493 "psyntax2.c"
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
#line 738 "psyntax.act"

    add_range_literal ( (XIe), 2 ) ;
#line 2509 "psyntax2.c"
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
		UNREACHED;
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
#line 948 "psyntax.act"
 (XIc) = CAST_CONST ; 
#line 2559 "psyntax2.c"
			}
			/* END OF ACTION: cast_const */
		}
		break;
	case 145:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cast_reinterp */
			{
#line 947 "psyntax.act"
 (XIc) = CAST_REINTERP ; 
#line 2571 "psyntax2.c"
			}
			/* END OF ACTION: cast_reinterp */
		}
		break;
	case 146:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cast_static */
			{
#line 946 "psyntax.act"
 (XIc) = CAST_STATIC ; 
#line 2583 "psyntax2.c"
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
#line 1157 "psyntax.act"
 (XIt) = 1 ; 
#line 2614 "psyntax2.c"
			}
			/* END OF ACTION: bool_true */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: bool_false */
			{
#line 1156 "psyntax.act"
 (XIt) = 0 ; 
#line 2625 "psyntax2.c"
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
#line 961 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2659 "psyntax2.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 410 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 2666 "psyntax2.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: lex_unused */
			{
#line 416 "psyntax.act"
 (XIt) = lex_unused ; 
#line 2677 "psyntax2.c"
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
#line 410 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 2712 "psyntax2.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: lex_set */
			{
#line 413 "psyntax.act"
 (XIt) = lex_set ; 
#line 2723 "psyntax2.c"
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
#line 1013 "psyntax.act"
 (XIn) = OPT_discard_func ; 
#line 2766 "psyntax2.c"
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
#line 1014 "psyntax.act"
 (XIn) = OPT_discard_static ; 
#line 2785 "psyntax2.c"
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
#line 1015 "psyntax.act"
 (XIn) = OPT_discard_value ; 
#line 2804 "psyntax2.c"
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
#line 556 "psyntax.act"

    (XItok) = make_type_token ( btype_signed | btype_int ) ;
#line 2836 "psyntax2.c"
			}
			/* END OF ACTION: token_signed */
		}
		break;
	case 122:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: token_unsigned */
			{
#line 560 "psyntax.act"

    (XItok) = make_type_token ( btype_unsigned | btype_int ) ;
#line 2849 "psyntax2.c"
			}
			/* END OF ACTION: token_unsigned */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: token_variety */
			{
#line 552 "psyntax.act"

    (XItok) = make_type_token ( btype_int ) ;
#line 2861 "psyntax2.c"
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
#line 625 "psyntax.act"

    (XIa) = begin_proc_token () ;
#line 2891 "psyntax2.c"
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
#line 520 "psyntax.act"

    (XIp) = NULL_list ( IDENTIFIER ) ;
#line 2916 "psyntax2.c"
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
#line 629 "psyntax.act"

    (XIb) = cont_proc_token ( (XIa), (XIp), (XIp) ) ;
#line 2936 "psyntax2.c"
			}
			/* END OF ACTION: token_proc_simple */
			XRtoken_Hintroduction (&XIr);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: token_proc_end */
			{
#line 637 "psyntax.act"

    (XItok) = end_proc_token ( (XIb), (XIr) ) ;
#line 2949 "psyntax2.c"
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
#line 625 "psyntax.act"

    (XIa) = begin_proc_token () ;
#line 2982 "psyntax2.c"
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
#line 520 "psyntax.act"

    (XIp0) = NULL_list ( IDENTIFIER ) ;
#line 3007 "psyntax2.c"
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
#line 520 "psyntax.act"

    (XIq0) = NULL_list ( IDENTIFIER ) ;
#line 3049 "psyntax2.c"
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
#line 633 "psyntax.act"

    (XIb) = cont_proc_token ( (XIa), (XIp), (XIq) ) ;
#line 3076 "psyntax2.c"
			}
			/* END OF ACTION: token_proc_complex */
			XRtoken_Hintroduction (&XIr);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: token_proc_end */
			{
#line 637 "psyntax.act"

    (XItok) = end_proc_token ( (XIb), (XIr) ) ;
#line 3089 "psyntax2.c"
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
#line 1146 "psyntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 3133 "psyntax2.c"
			}
			/* END OF ACTION: error_comma */
			/* BEGINNING OF ACTION: list_id_null */
			{
#line 520 "psyntax.act"

    (XIq) = NULL_list ( IDENTIFIER ) ;
#line 3141 "psyntax2.c"
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
#line 1146 "psyntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 3183 "psyntax2.c"
			}
			/* END OF ACTION: error_comma */
			/* BEGINNING OF ACTION: list_id_null */
			{
#line 520 "psyntax.act"

    (XIq) = NULL_list ( IDENTIFIER ) ;
#line 3191 "psyntax2.c"
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
#line 1146 "psyntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 3231 "psyntax2.c"
			}
			/* END OF ACTION: error_comma */
			/* BEGINNING OF ACTION: list_id_null */
			{
#line 520 "psyntax.act"

    (XIq) = NULL_list ( IDENTIFIER ) ;
#line 3239 "psyntax2.c"
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
#line 821 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_ON ; 
#line 3275 "psyntax2.c"
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
#line 822 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_OFF ; 
#line 3294 "psyntax2.c"
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
#line 950 "psyntax.act"
 (XIc) = ( (*XI837) | (XIb) ) ; 
#line 3344 "psyntax2.c"
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
#line 1021 "psyntax.act"
 (XIn) = OPT_empty_body ; 
#line 3385 "psyntax2.c"
			}
			/* END OF ACTION: opt_empty_body */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: opt_semicolon_extra */
			{
#line 1071 "psyntax.act"
 (XIn) = OPT_semicolon_extra ; 
#line 3396 "psyntax2.c"
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
#line 1038 "psyntax.act"
 (XIn) = OPT_infer_int_cv ; 
#line 3439 "psyntax2.c"
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
#line 1017 "psyntax.act"
 (XIn) = OPT_dspec_none ; 
#line 3458 "psyntax2.c"
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
#line 195 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 3516 "psyntax2.c"
								}
								/* END OF EXTRACT: identifier */
								ADVANCE_LEXER;
							}
							break;
						case 3:
							{
								/* BEGINNING OF EXTRACT: namespace-name */
								{
#line 203 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 3529 "psyntax2.c"
								}
								/* END OF EXTRACT: namespace-name */
								ADVANCE_LEXER;
							}
							break;
						case 4:
							{
								/* BEGINNING OF EXTRACT: statement-name */
								{
#line 207 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 3542 "psyntax2.c"
								}
								/* END OF EXTRACT: statement-name */
								ADVANCE_LEXER;
							}
							break;
						case 2:
							{
								/* BEGINNING OF EXTRACT: type-name */
								{
#line 199 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 3555 "psyntax2.c"
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
#line 440 "psyntax.act"

    HASHID nm = lookup_anon () ;
    (XItid) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 3578 "psyntax2.c"
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
#line 600 "psyntax.act"

    (XIid) = make_tok_param ( (XItok), (XIt), (XItid) ) ;
#line 3594 "psyntax2.c"
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
#line 1061 "psyntax.act"
 (XIn) = OPT_param_impl ; 
#line 3619 "psyntax2.c"
			}
			/* END OF ACTION: opt_param_impl */
		}
		break;
	case 113:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_dspec_none_func */
			{
#line 1018 "psyntax.act"
 (XIn) = OPT_dspec_none_func ; 
#line 3631 "psyntax2.c"
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
#line 1005 "psyntax.act"
 (XIn) = OPT_conv_ptr_void_ptr ; 
#line 3731 "psyntax2.c"
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
#line 1004 "psyntax.act"
 (XIn) = OPT_conv_ptr_ptr_void ; 
#line 3803 "psyntax2.c"
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
#line 366 "psyntax.act"

    (XIt) = type_error ;
    parse_tok_type ( &(XIt) ) ;
    object_type ( (XIt), null_tag ) ;
#line 3837 "psyntax2.c"
			}
			/* END OF ACTION: parse_type */
			/* BEGINNING OF ACTION: literal_type */
			{
#line 746 "psyntax.act"

    add_type_literal ( (XIt) ) ;
#line 3845 "psyntax2.c"
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
#line 993 "psyntax.act"
 (XIn) = OPT_conv_int_enum ; 
#line 3898 "psyntax2.c"
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
#line 1001 "psyntax.act"
 (XIn) = OPT_conv_ptr_ptr ; 
#line 3949 "psyntax2.c"
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
#line 1002 "psyntax.act"
 (XIn) = OPT_conv_ptr_ptr_expl ; 
#line 3968 "psyntax2.c"
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
#line 1003 "psyntax.act"
 (XIn) = OPT_conv_ptr_ptr_impl ; 
#line 3987 "psyntax2.c"
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
#line 994 "psyntax.act"
 (XIn) = OPT_conv_int_int ; 
#line 4018 "psyntax2.c"
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
#line 995 "psyntax.act"
 (XIn) = OPT_conv_int_int_expl ; 
#line 4037 "psyntax2.c"
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
#line 996 "psyntax.act"
 (XIn) = OPT_conv_int_int_impl ; 
#line 4056 "psyntax2.c"
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
#line 997 "psyntax.act"
 (XIn) = OPT_conv_int_ptr ; 
#line 4087 "psyntax2.c"
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
#line 998 "psyntax.act"
 (XIn) = OPT_conv_int_ptr_expl ; 
#line 4106 "psyntax2.c"
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
#line 999 "psyntax.act"
 (XIn) = OPT_conv_int_ptr_impl ; 
#line 4125 "psyntax2.c"
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
#line 719 "psyntax.act"
 (XIs) = SUFFIX_U ; 
#line 4165 "psyntax2.c"
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
#line 722 "psyntax.act"
 (XIs) = SUFFIX_LL ; 
#line 4194 "psyntax2.c"
			}
			/* END OF ACTION: suffix_ll */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: suffix_l */
			{
#line 720 "psyntax.act"
 (XIs) = SUFFIX_L ; 
#line 4205 "psyntax2.c"
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
#line 299 "psyntax.act"

    XIs = crt_token->pp_data.exp ;
#line 4244 "psyntax2.c"
					}
					/* END OF EXTRACT: string-exp */
					ADVANCE_LEXER;
				}
				break;
			case 20:
				{
					/* BEGINNING OF EXTRACT: wstring-exp */
					{
#line 303 "psyntax.act"

    XIs = crt_token->pp_data.exp ;
#line 4257 "psyntax2.c"
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
#line 806 "psyntax.act"

    STRING s = DEREF_str ( exp_string_lit_str ( (XIs) ) ) ;
    (XIn) = find_option_no ( s, 0 ) ;
    if ( (XIn) == -1 ) {
	report ( preproc_loc, ERR_pragma_option_bad ( s ) ) ;
    }
#line 4277 "psyntax2.c"
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
#line 723 "psyntax.act"
 (XIs) = SUFFIX_ULL ; 
#line 4302 "psyntax2.c"
			}
			/* END OF ACTION: suffix_ull */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: suffix_ul */
			{
#line 721 "psyntax.act"
 (XIs) = SUFFIX_UL ; 
#line 4313 "psyntax2.c"
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
#line 1182 "psyntax.act"

    int t = crt_lex_token ;
    if ( t == lex_identifier || t == lex_type_Hname ||
	 t == lex_namespace_Hname || t == lex_statement_Hname ) {
	t = find_hashid ( crt_token->pp_data.id.hash ) ;
	crt_lex_token = t ;
    }
#line 4343 "psyntax2.c"
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
#line 821 "psyntax.act"
 (XIa) = ( unsigned ) OPTION_ON ; 
#line 4364 "psyntax2.c"
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
#line 754 "psyntax.act"

    add_token_literal ( NULL_id, (XIa) ) ;
#line 4384 "psyntax2.c"
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
#line 1182 "psyntax.act"

    int t = crt_lex_token ;
    if ( t == lex_identifier || t == lex_type_Hname ||
	 t == lex_namespace_Hname || t == lex_statement_Hname ) {
	t = find_hashid ( crt_token->pp_data.id.hash ) ;
	crt_lex_token = t ;
    }
#line 4404 "psyntax2.c"
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
#line 822 "psyntax.act"
 (XIa) = ( unsigned ) OPTION_OFF ; 
#line 4425 "psyntax2.c"
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
#line 1173 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 4448 "psyntax2.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 195 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4461 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 203 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4474 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 207 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4487 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 199 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4500 "psyntax2.c"
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
#line 750 "psyntax.act"

    add_token_literal ( (XIid), (XIa) ) ;
#line 4516 "psyntax2.c"
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
#line 404 "psyntax.act"
 (XIt) = lex_discard ; 
#line 4545 "psyntax2.c"
			}
			/* END OF ACTION: lex_discard */
		}
		break;
	case 327:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_unused */
			{
#line 416 "psyntax.act"
 (XIt) = lex_unused ; 
#line 4557 "psyntax2.c"
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
#line 195 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 4600 "psyntax2.c"
					}
					/* END OF EXTRACT: identifier */
					ADVANCE_LEXER;
				}
				break;
			case 3:
				{
					/* BEGINNING OF EXTRACT: namespace-name */
					{
#line 203 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 4613 "psyntax2.c"
					}
					/* END OF EXTRACT: namespace-name */
					ADVANCE_LEXER;
				}
				break;
			case 4:
				{
					/* BEGINNING OF EXTRACT: statement-name */
					{
#line 207 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 4626 "psyntax2.c"
					}
					/* END OF EXTRACT: statement-name */
					ADVANCE_LEXER;
				}
				break;
			case 2:
				{
					/* BEGINNING OF EXTRACT: type-name */
					{
#line 199 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 4639 "psyntax2.c"
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
#line 600 "psyntax.act"

    (XIid) = make_tok_param ( (XItok), (XIt), (XItid) ) ;
#line 4658 "psyntax2.c"
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
#line 411 "psyntax.act"
 (XIt) = lex_reachable ; 
#line 4683 "psyntax2.c"
			}
			/* END OF ACTION: lex_reachable */
		}
		break;
	case 323:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_unreachable */
			{
#line 415 "psyntax.act"
 (XIt) = lex_unreachable ; 
#line 4695 "psyntax2.c"
			}
			/* END OF ACTION: lex_unreachable */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: lex_set */
			{
#line 413 "psyntax.act"
 (XIt) = lex_set ; 
#line 4706 "psyntax2.c"
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
#line 977 "psyntax.act"
 (XIe) = OPT_none ; 
#line 4730 "psyntax2.c"
			}
			/* END OF ACTION: opt_off */
		}
		break;
	case 205:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_on */
			{
#line 976 "psyntax.act"
 (XIe) = OPT_error ; 
#line 4742 "psyntax2.c"
			}
			/* END OF ACTION: opt_on */
		}
		break;
	case 271:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_off */
			{
#line 977 "psyntax.act"
 (XIe) = OPT_none ; 
#line 4754 "psyntax2.c"
			}
			/* END OF ACTION: opt_off */
		}
		break;
	case 272:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_on */
			{
#line 976 "psyntax.act"
 (XIe) = OPT_error ; 
#line 4766 "psyntax2.c"
			}
			/* END OF ACTION: opt_on */
		}
		break;
	case 331:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_warning */
			{
#line 978 "psyntax.act"
 (XIe) = OPT_warning ; 
#line 4778 "psyntax2.c"
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
#line 195 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4815 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 203 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4828 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 207 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4841 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 199 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4854 "psyntax2.c"
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
#line 689 "psyntax.act"

    preserve_id ( (XIid), lex_preserve ) ;
#line 4870 "psyntax2.c"
			}
			/* END OF ACTION: id_preserve */
			/* BEGINNING OF INLINE: preserve-list */
			goto XL2_preserve_Hlist;
			/* END OF INLINE: preserve-list */
		}
		UNREACHED;
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
#line 894 "psyntax.act"
 (XIt) = type_printf ; 
#line 4902 "psyntax2.c"
			}
			/* END OF ACTION: type_printf */
		}
		break;
	case 297:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_scanf */
			{
#line 895 "psyntax.act"
 (XIt) = type_scanf ; 
#line 4914 "psyntax2.c"
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
#line 389 "psyntax.act"

    (XI0) = predict_operator () ;
#line 4959 "psyntax2.c"
		}
		/* END OF ACTION: is_operator */
		if (!XI0)
			goto XL3;
		/* BEGINNING OF ACTION: parse_operator */
		{
#line 384 "psyntax.act"

    (XInm) = DEREF_id ( hashid_id ( KEYWORD ( lex_zzzz ) ) ) ;
    parse_operator ( &(XInm) ) ;
#line 4970 "psyntax2.c"
		}
		/* END OF ACTION: parse_operator */
		/* BEGINNING OF ACTION: token_name */
		{
#line 645 "psyntax.act"

    (XI857) = check_id ( crt_namespace, (XInm), 0 ) ;
#line 4978 "psyntax2.c"
		}
		/* END OF ACTION: token_name */
		XR781 (XI857, &XIid);
		if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto XL1;
		}
		/* BEGINNING OF ACTION: token_interface */
		{
#line 661 "psyntax.act"

    token_interface ( (XIid), (*XIi) ) ;
#line 4991 "psyntax2.c"
		}
		/* END OF ACTION: token_interface */
		/* BEGINNING OF ACTION: rescan_tag_line */
		{
#line 1206 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 5004 "psyntax2.c"
		}
		/* END OF ACTION: rescan_tag_line */
		/* BEGINNING OF INLINE: 479 */
		goto XL2_479;
		/* END OF INLINE: 479 */
	}
	UNREACHED;
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
#line 1173 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 5029 "psyntax2.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 195 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5042 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 203 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5055 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 207 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5068 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 199 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5081 "psyntax2.c"
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
#line 649 "psyntax.act"

    (XI858) = find_tag_token ( (XInm) ) ;
#line 5097 "psyntax2.c"
			}
			/* END OF ACTION: token_tag */
			XR781 (XI858, &XIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: token_interface */
			{
#line 661 "psyntax.act"

    token_interface ( (XIid), (*XIi) ) ;
#line 5110 "psyntax2.c"
			}
			/* END OF ACTION: token_interface */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1206 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 5123 "psyntax2.c"
			}
			/* END OF ACTION: rescan_tag_line */
			/* BEGINNING OF INLINE: 479 */
			goto XL2_479;
			/* END OF INLINE: 479 */
		}
		UNREACHED;
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
#line 195 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5147 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 203 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5160 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 207 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5173 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 199 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5186 "psyntax2.c"
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
#line 645 "psyntax.act"

    (XI859) = check_id ( crt_namespace, (XInm), 0 ) ;
#line 5202 "psyntax2.c"
			}
			/* END OF ACTION: token_name */
			XR781 (XI859, &XIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: token_interface */
			{
#line 661 "psyntax.act"

    token_interface ( (XIid), (*XIi) ) ;
#line 5215 "psyntax2.c"
			}
			/* END OF ACTION: token_interface */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1206 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 5228 "psyntax2.c"
			}
			/* END OF ACTION: rescan_tag_line */
			/* BEGINNING OF INLINE: 479 */
			goto XL2_479;
			/* END OF INLINE: 479 */
		}
		UNREACHED;
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
#line 1173 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 5263 "psyntax2.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: any-identifier */
			{
				switch (CURRENT_TERMINAL) {
				case 1:
					{
						/* BEGINNING OF EXTRACT: identifier */
						{
#line 195 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5276 "psyntax2.c"
						}
						/* END OF EXTRACT: identifier */
						ADVANCE_LEXER;
					}
					break;
				case 3:
					{
						/* BEGINNING OF EXTRACT: namespace-name */
						{
#line 203 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5289 "psyntax2.c"
						}
						/* END OF EXTRACT: namespace-name */
						ADVANCE_LEXER;
					}
					break;
				case 4:
					{
						/* BEGINNING OF EXTRACT: statement-name */
						{
#line 207 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5302 "psyntax2.c"
						}
						/* END OF EXTRACT: statement-name */
						ADVANCE_LEXER;
					}
					break;
				case 2:
					{
						/* BEGINNING OF EXTRACT: type-name */
						{
#line 199 "psyntax.act"

    XInm = crt_token->pp_data.id.use ;
#line 5315 "psyntax2.c"
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
#line 657 "psyntax.act"

    (XI856) = find_ext_token ( (XInm) ) ;
#line 5331 "psyntax2.c"
			}
			/* END OF ACTION: token_extern */
			XR781 (XI856, &XIid);
			if ((CURRENT_TERMINAL) == 355) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: token_interface */
			{
#line 661 "psyntax.act"

    token_interface ( (XIid), (*XIi) ) ;
#line 5344 "psyntax2.c"
			}
			/* END OF ACTION: token_interface */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1206 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 5357 "psyntax2.c"
			}
			/* END OF ACTION: rescan_tag_line */
			/* BEGINNING OF INLINE: 479 */
			goto XL2_479;
			/* END OF INLINE: 479 */
		}
		UNREACHED;
	default:
		break;
	}
	return;
XL1:;
	SAVE_LEXER (355);
	return;
}

/* END OF FILE */
