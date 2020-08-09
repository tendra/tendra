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

#line 98 "psyntax2.c"

void
XR808(void)
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
#line 1046 "psyntax.act"
 (XIn) = OPT_macro_weak ; 
#line 121 "psyntax2.c"
			}
			/* END OF ACTION: opt_macro_weak */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 134 "psyntax2.c"
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
#line 1078 "psyntax.act"
 (XIn) = OPT_weak ; 
#line 156 "psyntax2.c"
			}
			/* END OF ACTION: opt_weak */
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 169 "psyntax2.c"
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
XR809(void)
{
	switch (CURRENT_TERMINAL) {
	case 213:
		{
			IDENTIFIER XIid;
			unsigned XIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1166 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 203 "psyntax2.c"
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
#line 216 "psyntax2.c"
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
#line 229 "psyntax2.c"
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
#line 242 "psyntax2.c"
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
#line 255 "psyntax2.c"
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
			/* BEGINNING OF INLINE: 770 */
			{
				switch (CURRENT_TERMINAL) {
				case 293:
					{
						ADVANCE_LEXER;
						XRallow_Hstate (&XIe);
						if ((CURRENT_TERMINAL) == 356) {
							RESTORE_LEXER;
							goto XL1;
						}
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: error_on */
						{
#line 814 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_ON ; 
#line 285 "psyntax2.c"
						}
						/* END OF ACTION: error_on */
					}
					break;
				}
			}
			/* END OF INLINE: 770 */
			/* BEGINNING OF ACTION: check_use */
			{
#line 771 "psyntax.act"

    use_option ( (XIid), (XIe) ) ;
#line 298 "psyntax2.c"
			}
			/* END OF ACTION: check_use */
		}
		break;
	case 215:
		{
			int XIn;

			XRerror_Hnumber (&XIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: error_use */
			{
#line 823 "psyntax.act"

    if ( (XIn) >= 0 ) {
	no_error_args = 1 ;
	report ( crt_loc, make_error ( (XIn) ) ) ;
	no_error_args = 0 ;
    }
#line 321 "psyntax2.c"
			}
			/* END OF ACTION: error_use */
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
XR810(void)
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
#line 1082 "psyntax.act"
 (XIn) = OPT_VAL_maximum_error ; 
#line 358 "psyntax2.c"
			}
			/* END OF ACTION: opt_val_maximum_error */
			/* BEGINNING OF INLINE: integer-literal */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 21:
						/* BEGINNING OF EXTRACT: integer-exp */
						{
#line 267 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 371 "psyntax2.c"
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
#line 387 "psyntax2.c"
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
#line 267 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 417 "psyntax2.c"
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: opt_val_name_limit */
			{
#line 1083 "psyntax.act"
 (XIn) = OPT_VAL_name_limit ; 
#line 437 "psyntax2.c"
			}
			/* END OF ACTION: opt_val_name_limit */
			/* BEGINNING OF ACTION: opt_name_limit */
			{
#line 1048 "psyntax.act"
 (XIm) = OPT_name_limit ; 
#line 444 "psyntax2.c"
			}
			/* END OF ACTION: opt_name_limit */
			/* BEGINNING OF ACTION: analysis_exp */
			{
#line 962 "psyntax.act"

    set_value ( (XIn), (XIe), ( unsigned long ) 0 ) ;
#line 452 "psyntax2.c"
			}
			/* END OF ACTION: analysis_exp */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIm), (XIi) ) ;
#line 460 "psyntax2.c"
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
XR811(void)
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
#line 1018 "psyntax.act"
 (XIn) = OPT_escape_overflow ; 
#line 497 "psyntax2.c"
			}
			/* END OF ACTION: opt_escape_overflow */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 510 "psyntax2.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 17: case 18: case 19: case 20:
		{
			EXP XIa;

			/* BEGINNING OF INLINE: 754 */
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
#line 284 "psyntax.act"

    XIa = crt_token->pp_data.exp ;
#line 534 "psyntax2.c"
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
#line 547 "psyntax2.c"
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
#line 292 "psyntax.act"

    XIa = crt_token->pp_data.exp ;
#line 572 "psyntax2.c"
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

    XIa = crt_token->pp_data.exp ;
#line 585 "psyntax2.c"
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
			/* END OF INLINE: 754 */
			/* BEGINNING OF INLINE: 755 */
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
#line 284 "psyntax.act"

    XIb = crt_token->pp_data.exp ;
#line 621 "psyntax2.c"
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

    XIb = crt_token->pp_data.exp ;
#line 634 "psyntax2.c"
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
#line 924 "psyntax.act"

    set_character ( (XIa), (XIb) ) ;
#line 650 "psyntax2.c"
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
#line 439 "psyntax.act"

    (XIb) = NULL_exp ;
#line 672 "psyntax2.c"
						}
						/* END OF ACTION: exp_none */
						/* BEGINNING OF ACTION: char_set */
						{
#line 924 "psyntax.act"

    set_character ( (XIa), (XIb) ) ;
#line 680 "psyntax2.c"
						}
						/* END OF ACTION: char_set */
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: 755 */
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
XR812(void)
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
#line 292 "psyntax.act"

    XIs = crt_token->pp_data.exp ;
#line 724 "psyntax2.c"
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

    XIs = crt_token->pp_data.exp ;
#line 737 "psyntax2.c"
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
#line 807 "psyntax.act"

    STRING s = DEREF_str ( exp_string_lit_str ( (XIs) ) ) ;
    (XIn) = find_value_no ( s, 0 ) ;
    if ( (XIn) == -1 ) {
	report ( preproc_loc, ERR_pragma_option_bad ( s ) ) ;
    }
#line 757 "psyntax2.c"
			}
			/* END OF ACTION: option_value_number */
			/* BEGINNING OF INLINE: integer-literal */
			{
				{
					switch (CURRENT_TERMINAL) {
					case 21:
						/* BEGINNING OF EXTRACT: integer-exp */
						{
#line 267 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 770 "psyntax2.c"
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
#line 786 "psyntax2.c"
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
#line 292 "psyntax.act"

    XIs = crt_token->pp_data.exp ;
#line 807 "psyntax2.c"
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

    XIs = crt_token->pp_data.exp ;
#line 820 "psyntax2.c"
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
#line 799 "psyntax.act"

    STRING s = DEREF_str ( exp_string_lit_str ( (XIs) ) ) ;
    (XIn) = find_option_no ( s, 0 ) ;
    if ( (XIn) == -1 ) {
	report ( preproc_loc, ERR_pragma_option_bad ( s ) ) ;
    }
#line 840 "psyntax2.c"
			}
			/* END OF ACTION: option_number */
			XRoption_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 853 "psyntax2.c"
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
XRcomplete_Hstate(unsigned *XOi)
{
	unsigned XIi;

	switch (CURRENT_TERMINAL) {
	case 65:
		{
			ADVANCE_LEXER;
			XR837 (&XIi);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: error_on */
			{
#line 814 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_ON ; 
#line 891 "psyntax2.c"
			}
			/* END OF ACTION: error_on */
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
	*XOi = XIi;
}

void
XR813(void)
{
	switch (CURRENT_TERMINAL) {
	case 78:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: id_preserve_all */
			{
#line 687 "psyntax.act"

    preserve_all = 1 ;
#line 919 "psyntax2.c"
			}
			/* END OF ACTION: id_preserve_all */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1180 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 932 "psyntax2.c"
			}
			/* END OF ACTION: rescan_line */
			XRpreserve_Hlist ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
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
#line 815 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_OFF ; 
#line 965 "psyntax2.c"
			}
			/* END OF ACTION: error_off */
			/* BEGINNING OF ACTION: error_off */
			{
#line 815 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_OFF ; 
#line 972 "psyntax2.c"
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
			case 356:
				RESTORE_LEXER;
				goto XL1;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 726 */
			{
				switch (CURRENT_TERMINAL) {
				case 272:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: error_off */
						{
#line 815 "psyntax.act"
 (XIb) = ( unsigned ) OPTION_OFF ; 
#line 1003 "psyntax2.c"
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
#line 1015 "psyntax2.c"
						}
						/* END OF ACTION: error_warning */
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: 726 */
			XIe = XIb;
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
XR814(TYPE *XIt)
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
#line 843 "psyntax.act"

    accept_ellipsis ( (*XIt) ) ;
#line 1071 "psyntax2.c"
			}
			/* END OF ACTION: type_ellipsis */
		}
		break;
	default:
		{
			TYPE XIs;

			/* BEGINNING OF ACTION: parse_type */
			{
#line 359 "psyntax.act"

    (XIs) = type_error ;
    parse_tok_type ( &(XIs) ) ;
    object_type ( (XIs), null_tag ) ;
#line 1087 "psyntax2.c"
			}
			/* END OF ACTION: parse_type */
			/* BEGINNING OF ACTION: type_argument */
			{
#line 839 "psyntax.act"

    accept_argument ( (*XIt), (XIs) ) ;
#line 1095 "psyntax2.c"
			}
			/* END OF ACTION: type_argument */
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
XR815(void)
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
#line 1180 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 1138 "psyntax2.c"
			}
			/* END OF ACTION: rescan_line */
			/* BEGINNING OF ACTION: parse_type */
			{
#line 359 "psyntax.act"

    (XIt) = type_error ;
    parse_tok_type ( &(XIt) ) ;
    object_type ( (XIt), null_tag ) ;
#line 1148 "psyntax2.c"
			}
			/* END OF ACTION: parse_type */
			/* BEGINNING OF ACTION: type_char_lit */
			{
#line 847 "psyntax.act"

    set_char_lit ( (XIt) ) ;
#line 1156 "psyntax2.c"
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
			/* BEGINNING OF INLINE: 588 */
			{
				switch (CURRENT_TERMINAL) {
				case 111:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: bool_true */
						{
#line 1150 "psyntax.act"
 (XIb) = 1 ; 
#line 1197 "psyntax2.c"
						}
						/* END OF ACTION: bool_true */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: bool_false */
						{
#line 1149 "psyntax.act"
 (XIb) = 0 ; 
#line 1208 "psyntax2.c"
						}
						/* END OF ACTION: bool_false */
					}
					break;
				}
			}
			/* END OF INLINE: 588 */
			/* BEGINNING OF ACTION: type_long_long */
			{
#line 859 "psyntax.act"

    set_long_long_type ( (XIb) ) ;
#line 1221 "psyntax2.c"
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
#line 1166 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 1253 "psyntax2.c"
			}
			/* END OF ACTION: rescan_id */
			/* BEGINNING OF INLINE: 591 */
			{
				switch (CURRENT_TERMINAL) {
				case 83:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: id_none */
						{
#line 426 "psyntax.act"

    (XIid) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 1269 "psyntax2.c"
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
#line 188 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 1286 "psyntax2.c"
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
#line 1299 "psyntax2.c"
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
#line 1312 "psyntax2.c"
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
#line 1325 "psyntax2.c"
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
			/* END OF INLINE: 591 */
			/* BEGINNING OF ACTION: nspace_std */
			{
#line 883 "psyntax.act"

    set_std_namespace ( (XIid) ) ;
#line 1348 "psyntax2.c"
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
			/* BEGINNING OF INLINE: 589 */
			{
				switch (CURRENT_TERMINAL) {
				case 266:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: cv_none */
						{
#line 450 "psyntax.act"
 (XIcv) = cv_none ; 
#line 1382 "psyntax2.c"
						}
						/* END OF ACTION: cv_none */
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: cv_const */
						{
#line 451 "psyntax.act"
 (XIcv) = cv_const ; 
#line 1393 "psyntax2.c"
						}
						/* END OF ACTION: cv_const */
					}
					break;
				}
			}
			/* END OF INLINE: 589 */
			switch (CURRENT_TERMINAL) {
			case 98:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_string_lit */
			{
#line 855 "psyntax.act"

    set_string_qual ( (XIcv) ) ;
#line 1413 "psyntax2.c"
			}
			/* END OF ACTION: type_string_lit */
		}
		break;
	case 156: case 286: case 299:
		{
			BASE_TYPE XIbt;
			TYPE XIt;

			/* BEGINNING OF INLINE: 587 */
			{
				switch (CURRENT_TERMINAL) {
				case 286:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_ptrdiff_t */
						{
#line 465 "psyntax.act"
 (XIbt) = btype_ptrdiff_t ; 
#line 1433 "psyntax2.c"
						}
						/* END OF ACTION: btype_ptrdiff_t */
					}
					break;
				case 299:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_size_t */
						{
#line 464 "psyntax.act"
 (XIbt) = btype_size_t ; 
#line 1445 "psyntax2.c"
						}
						/* END OF ACTION: btype_size_t */
					}
					break;
				case 156:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_wchar_t */
						{
#line 463 "psyntax.act"
 (XIbt) = btype_wchar_t ; 
#line 1457 "psyntax2.c"
						}
						/* END OF ACTION: btype_wchar_t */
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: 587 */
			switch (CURRENT_TERMINAL) {
			case 41:
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
#line 1480 "psyntax2.c"
			}
			/* END OF ACTION: rescan_line */
			/* BEGINNING OF ACTION: parse_type */
			{
#line 359 "psyntax.act"

    (XIt) = type_error ;
    parse_tok_type ( &(XIt) ) ;
    object_type ( (XIt), null_tag ) ;
#line 1490 "psyntax2.c"
			}
			/* END OF ACTION: parse_type */
			/* BEGINNING OF ACTION: type_builtin */
			{
#line 875 "psyntax.act"

    set_builtin_type ( (XIbt), (XIt) ) ;
#line 1498 "psyntax2.c"
			}
			/* END OF ACTION: type_builtin */
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
XR816(void)
{
	switch (CURRENT_TERMINAL) {
	case 215: case 262:
		{
			XR810 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 156: case 187: case 256: case 286:
	case 299: case 302: case 304:
		{
			XR815 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
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
XR817(void)
{
	switch (CURRENT_TERMINAL) {
	case 195:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1180 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 1561 "psyntax2.c"
			}
			/* END OF ACTION: rescan_line */
			XRconversion_Hlist ();
			if ((CURRENT_TERMINAL) == 356) {
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
#line 1013 "psyntax.act"
 (XIn) = OPT_ellipsis_ident ; 
#line 1605 "psyntax2.c"
			}
			/* END OF ACTION: opt_ellipsis_ident */
			/* BEGINNING OF ACTION: error_off */
			{
#line 815 "psyntax.act"
 (XIe) = ( unsigned ) OPTION_OFF ; 
#line 1612 "psyntax2.c"
			}
			/* END OF ACTION: error_off */
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 1620 "psyntax2.c"
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
XR818(void)
{
	switch (CURRENT_TERMINAL) {
	case 115: case 122: case 208:
		{
			BASE_TYPE XIbt;

			/* BEGINNING OF INLINE: 585 */
			{
				switch (CURRENT_TERMINAL) {
				case 208:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_none */
						{
#line 466 "psyntax.act"
 (XIbt) = btype_none ; 
#line 1654 "psyntax2.c"
						}
						/* END OF ACTION: btype_none */
					}
					break;
				case 115:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_signed */
						{
#line 461 "psyntax.act"
 (XIbt) = btype_signed ; 
#line 1666 "psyntax2.c"
						}
						/* END OF ACTION: btype_signed */
					}
					break;
				case 122:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: btype_unsigned */
						{
#line 462 "psyntax.act"
 (XIbt) = btype_unsigned ; 
#line 1678 "psyntax2.c"
						}
						/* END OF ACTION: btype_unsigned */
					}
					break;
				default:
					goto XL1;
				}
			}
			/* END OF INLINE: 585 */
			/* BEGINNING OF ACTION: type_char_sign */
			{
#line 851 "psyntax.act"

    set_char_sign ( (XIbt) ) ;
#line 1693 "psyntax2.c"
			}
			/* END OF ACTION: type_char_sign */
		}
		break;
	case 17: case 18: case 19: case 20:
	case 216:
		{
			XR811 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
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
XR819(void)
{
	switch (CURRENT_TERMINAL) {
	case 312:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_token_redef */
			{
#line 1069 "psyntax.act"
 (XIn) = OPT_token_redef ; 
#line 1733 "psyntax2.c"
			}
			/* END OF ACTION: opt_token_redef */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 1746 "psyntax2.c"
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
#line 1180 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 1771 "psyntax2.c"
			}
			/* END OF ACTION: rescan_line */
			/* BEGINNING OF ACTION: parse_type */
			{
#line 359 "psyntax.act"

    (XIt) = type_error ;
    parse_tok_type ( &(XIt) ) ;
    object_type ( (XIt), null_tag ) ;
#line 1781 "psyntax2.c"
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
#line 359 "psyntax.act"

    (XIs) = type_error ;
    parse_tok_type ( &(XIs) ) ;
    object_type ( (XIs), null_tag ) ;
#line 1798 "psyntax2.c"
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
#line 1175 "psyntax.act"

    int t = crt_lex_token ;
    if ( t == lex_identifier || t == lex_type_Hname ||
	 t == lex_namespace_Hname || t == lex_statement_Hname ) {
	t = find_hashid ( crt_token->pp_data.id.hash ) ;
	crt_lex_token = t ;
    }
#line 1818 "psyntax2.c"
			}
			/* END OF ACTION: rescan_keyword */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: type_compatible */
			{
#line 863 "psyntax.act"

    set_compatible_type ( (XIt), (XIs), (XIe) ) ;
#line 1831 "psyntax2.c"
			}
			/* END OF ACTION: type_compatible */
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
XR820(void)
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
#line 1035 "psyntax.act"
 (XIn) = OPT_init_struct ; 
#line 1903 "psyntax2.c"
			}
			/* END OF ACTION: opt_init_struct */
			XRallow_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 1916 "psyntax2.c"
			}
			/* END OF ACTION: analysis_state */
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
#line 1933 "psyntax2.c"
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
#line 1946 "psyntax2.c"
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
#line 1959 "psyntax2.c"
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
#line 1972 "psyntax2.c"
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
#line 1985 "psyntax2.c"
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
#line 674 "psyntax.act"

    allow_initialiser ( (XIid) ) ;
#line 2008 "psyntax2.c"
			}
			/* END OF ACTION: id_init */
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
XRliteral_Hsuffix(int *XOs)
{
	int XIs;

	switch (CURRENT_TERMINAL) {
	case 111:
		{
			ADVANCE_LEXER;
			XR852 (&XIs);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 122:
		{
			ADVANCE_LEXER;
			XR851 (&XIs);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: suffix_none */
			{
#line 711 "psyntax.act"
 (XIs) = SUFFIX_NONE ; 
#line 2056 "psyntax2.c"
			}
			/* END OF ACTION: suffix_none */
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
	*XOs = XIs;
}

void
XR821(void)
{
	switch (CURRENT_TERMINAL) {
	case 174:
		{
			int XIn;
			unsigned XIe;

			ADVANCE_LEXER;
			XRconversion_Hspec (&XIn);
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2093 "psyntax2.c"
			}
			/* END OF ACTION: analysis_state */
		}
		break;
	case 1: case 2: case 3: case 4:
	case 172:
		{
			/* BEGINNING OF ACTION: rescan_allow_line */
			{
#line 1185 "psyntax.act"

    rescan_pragma ( lex_allow ) ;
    RESCAN_LEXER ;
#line 2107 "psyntax2.c"
			}
			/* END OF ACTION: rescan_allow_line */
			XRconversion_Hlist ();
			switch (CURRENT_TERMINAL) {
			case 172:
				break;
			case 356:
				RESTORE_LEXER;
				goto XL1;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
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
#line 188 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 2153 "psyntax2.c"
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
#line 2166 "psyntax2.c"
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
#line 2179 "psyntax2.c"
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
#line 2192 "psyntax2.c"
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
#line 670 "psyntax.act"

    allow_conversion ( (XIid) ) ;
#line 2208 "psyntax2.c"
			}
			/* END OF ACTION: id_conv */
			/* BEGINNING OF INLINE: conversion-list */
			goto XL2_conversion_Hlist;
			/* END OF INLINE: conversion-list */
		}
		UNREACHED;
	case 356:
		return;
	default:
		break;
	}
	return;
XL1:;
	SAVE_LEXER (356);
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
			XR831 (&XIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: opt_discard */
			{
#line 1005 "psyntax.act"
 (XIn) = OPT_discard ; 
#line 2249 "psyntax2.c"
			}
			/* END OF ACTION: opt_discard */
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
XR822(void)
{
	switch (CURRENT_TERMINAL) {
	case 255:
		{
			int XIb;
			int XIs;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: literal_set */
			{
#line 720 "psyntax.act"

    pragma_number = 1 ;
#line 2280 "psyntax2.c"
			}
			/* END OF ACTION: literal_set */
			XRliteral_Hbase (&XIb);
			XRliteral_Hsuffix (&XIs);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: literal_begin */
			{
#line 723 "psyntax.act"

    begin_literal ( (XIb), (XIs) ) ;
#line 2294 "psyntax2.c"
			}
			/* END OF ACTION: literal_begin */
			/* BEGINNING OF ACTION: rescan_line */
			{
#line 1180 "psyntax.act"

    rescan_pragma ( lex_unknown ) ;
    RESCAN_LEXER ;
#line 2303 "psyntax2.c"
			}
			/* END OF ACTION: rescan_line */
			XRliteral_Hitem_Hlist ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 141: case 274:
		{
			int XIn;
			unsigned XIe;

			XR798 (&XIn);
			XRerror_Hstate (&XIe);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2329 "psyntax2.c"
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
XR823(void)
{
	switch (CURRENT_TERMINAL) {
	case 312:
		{
			int XIi;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: interface_undef */
			{
#line 697 "psyntax.act"
 (XIi) = lex_undef ; 
#line 2358 "psyntax2.c"
			}
			/* END OF ACTION: interface_undef */
			/* BEGINNING OF ACTION: rescan_tag_line */
			{
#line 1199 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	if ( t != lex_tag_Hcap && !predict_operator () ) {
	    crt_lex_token = lex_identifier ;
	}
    }
#line 2371 "psyntax2.c"
			}
			/* END OF ACTION: rescan_tag_line */
			XR480 (&XIi);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 251:
		{
			IDENTIFIER XIid;

			XRkeyword_Hid (&XIid);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: keyword_undef */
			{
#line 912 "psyntax.act"

    undef_keyword ( (XIid) ) ;
#line 2395 "psyntax2.c"
			}
			/* END OF ACTION: keyword_undef */
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
XRimplicit_Hspec(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 107:
		{
			ADVANCE_LEXER;
			XR842 (&XIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: opt_infer_int */
			{
#line 1030 "psyntax.act"
 (XIn) = OPT_infer_int ; 
#line 2433 "psyntax2.c"
			}
			/* END OF ACTION: opt_infer_int */
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
XRliteral_Hbase(int *XOb)
{
	int XIb;

	switch (CURRENT_TERMINAL) {
	case 196:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: base_decimal */
			{
#line 708 "psyntax.act"
 (XIb) = BASE_DECIMAL ; 
#line 2462 "psyntax2.c"
			}
			/* END OF ACTION: base_decimal */
		}
		break;
	case 229:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: base_hexadecimal */
			{
#line 709 "psyntax.act"
 (XIb) = BASE_HEXADECIMAL ; 
#line 2474 "psyntax2.c"
			}
			/* END OF ACTION: base_hexadecimal */
		}
		break;
	case 269:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: base_octal */
			{
#line 707 "psyntax.act"
 (XIb) = BASE_OCTAL ; 
#line 2486 "psyntax2.c"
			}
			/* END OF ACTION: base_octal */
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
#line 736 "psyntax.act"

    add_range_literal ( NULL_exp, 1 ) ;
#line 2517 "psyntax2.c"
			}
			/* END OF ACTION: literal_range */
			XRliteral_Hitem ();
			/* BEGINNING OF INLINE: or */
			{
				if ((CURRENT_TERMINAL) == 356) {
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
#line 728 "psyntax.act"

    add_range_literal ( NULL_exp, 0 ) ;
#line 2551 "psyntax2.c"
			}
			/* END OF ACTION: literal_infinity */
			XRliteral_Hitem ();
			if ((CURRENT_TERMINAL) == 356) {
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
#line 267 "psyntax.act"

    XIe = crt_token->pp_data.exp ;
#line 2575 "psyntax2.c"
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
#line 731 "psyntax.act"

    add_range_literal ( (XIe), 2 ) ;
#line 2591 "psyntax2.c"
			}
			/* END OF ACTION: literal_integer */
			XRliteral_Hitem ();
			/* BEGINNING OF INLINE: or */
			{
				if ((CURRENT_TERMINAL) == 356) {
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
XRcast_Hcommand(unsigned *XOc)
{
	unsigned XIc;

	switch (CURRENT_TERMINAL) {
	case 130:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cast_const */
			{
#line 941 "psyntax.act"
 (XIc) = CAST_CONST ; 
#line 2641 "psyntax2.c"
			}
			/* END OF ACTION: cast_const */
		}
		break;
	case 145:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cast_reinterp */
			{
#line 940 "psyntax.act"
 (XIc) = CAST_REINTERP ; 
#line 2653 "psyntax2.c"
			}
			/* END OF ACTION: cast_reinterp */
		}
		break;
	case 146:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cast_static */
			{
#line 939 "psyntax.act"
 (XIc) = CAST_STATIC ; 
#line 2665 "psyntax2.c"
			}
			/* END OF ACTION: cast_static */
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
#line 1150 "psyntax.act"
 (XIt) = 1 ; 
#line 2696 "psyntax2.c"
			}
			/* END OF ACTION: bool_true */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: bool_false */
			{
#line 1149 "psyntax.act"
 (XIt) = 0 ; 
#line 2707 "psyntax2.c"
			}
			/* END OF ACTION: bool_false */
		}
		break;
	case 356:
		return;
	}
	*XOt = XIt;
}

void
XR829(int *XOt)
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: analysis_state */
			{
#line 954 "psyntax.act"

    set_option ( (XIn), (XIe) ) ;
#line 2741 "psyntax2.c"
			}
			/* END OF ACTION: analysis_state */
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 2748 "psyntax2.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: lex_unused */
			{
#line 409 "psyntax.act"
 (XIt) = lex_unused ; 
#line 2759 "psyntax2.c"
			}
			/* END OF ACTION: lex_unused */
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
	*XOt = XIt;
}

void
XR830(int *XOt)
{
	int XIt;

	switch (CURRENT_TERMINAL) {
	case 156: case 187: case 215: case 256:
	case 262: case 286: case 299: case 302:
	case 304:
		{
			XR816 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: lex_pragma */
			{
#line 403 "psyntax.act"
 (XIt) = lex_hash_Hpragma ; 
#line 2794 "psyntax2.c"
			}
			/* END OF ACTION: lex_pragma */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: lex_set */
			{
#line 406 "psyntax.act"
 (XIt) = lex_set ; 
#line 2805 "psyntax2.c"
			}
			/* END OF ACTION: lex_set */
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
	*XOt = XIt;
}

void
XR831(int *XOn)
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
#line 1006 "psyntax.act"
 (XIn) = OPT_discard_func ; 
#line 2848 "psyntax2.c"
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
#line 1007 "psyntax.act"
 (XIn) = OPT_discard_static ; 
#line 2867 "psyntax2.c"
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
#line 1008 "psyntax.act"
 (XIn) = OPT_discard_value ; 
#line 2886 "psyntax2.c"
			}
			/* END OF ACTION: opt_discard_value */
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
XR832(TOKEN *XOtok)
{
	TOKEN XItok;

	switch (CURRENT_TERMINAL) {
	case 115:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: token_signed */
			{
#line 549 "psyntax.act"

    (XItok) = make_type_token ( btype_signed | btype_int ) ;
#line 2918 "psyntax2.c"
			}
			/* END OF ACTION: token_signed */
		}
		break;
	case 122:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: token_unsigned */
			{
#line 553 "psyntax.act"

    (XItok) = make_type_token ( btype_unsigned | btype_int ) ;
#line 2931 "psyntax2.c"
			}
			/* END OF ACTION: token_unsigned */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: token_variety */
			{
#line 545 "psyntax.act"

    (XItok) = make_type_token ( btype_int ) ;
#line 2943 "psyntax2.c"
			}
			/* END OF ACTION: token_variety */
		}
		break;
	case 356:
		return;
	}
	*XOtok = XItok;
}

void
XR833(TOKEN *XOtok)
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
#line 618 "psyntax.act"

    (XIa) = begin_proc_token () ;
#line 2973 "psyntax2.c"
			}
			/* END OF ACTION: token_proc_begin */
			/* BEGINNING OF INLINE: 457 */
			{
				switch (CURRENT_TERMINAL) {
				case 177: case 188: case 218: case 225:
				case 227: case 250: case 261: case 263:
				case 282: case 296: case 303: case 305:
				case 314: case 320: case 328:
					{
						XRsimple_Htok_Hpars (&XIp);
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

    (XIp) = NULL_list ( IDENTIFIER ) ;
#line 2998 "psyntax2.c"
						}
						/* END OF ACTION: list_id_null */
					}
					break;
				}
			}
			/* END OF INLINE: 457 */
			switch (CURRENT_TERMINAL) {
			case 39:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: token_proc_simple */
			{
#line 622 "psyntax.act"

    (XIb) = cont_proc_token ( (XIa), (XIp), (XIp) ) ;
#line 3018 "psyntax2.c"
			}
			/* END OF ACTION: token_proc_simple */
			XRtoken_Hintroduction (&XIr);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: token_proc_end */
			{
#line 630 "psyntax.act"

    (XItok) = end_proc_token ( (XIb), (XIr) ) ;
#line 3031 "psyntax2.c"
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
#line 618 "psyntax.act"

    (XIa) = begin_proc_token () ;
#line 3064 "psyntax2.c"
			}
			/* END OF ACTION: token_proc_begin */
			/* BEGINNING OF INLINE: 451 */
			{
				switch (CURRENT_TERMINAL) {
				case 177: case 188: case 218: case 225:
				case 227: case 250: case 261: case 263:
				case 282: case 296: case 303: case 305:
				case 314: case 320: case 328:
					{
						XRbound_Htok_Hpars (&XIp0);
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

    (XIp0) = NULL_list ( IDENTIFIER ) ;
#line 3089 "psyntax2.c"
						}
						/* END OF ACTION: list_id_null */
					}
					break;
				}
			}
			/* END OF INLINE: 451 */
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
			/* BEGINNING OF INLINE: 454 */
			{
				switch (CURRENT_TERMINAL) {
				case 218: case 261: case 282: case 303:
				case 314:
					{
						XRprog_Htok_Hpars (XIp, &XIq0);
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

    (XIq0) = NULL_list ( IDENTIFIER ) ;
#line 3131 "psyntax2.c"
						}
						/* END OF ACTION: list_id_null */
					}
					break;
				}
			}
			/* END OF INLINE: 454 */
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
#line 626 "psyntax.act"

    (XIb) = cont_proc_token ( (XIa), (XIp), (XIq) ) ;
#line 3158 "psyntax2.c"
			}
			/* END OF ACTION: token_proc_complex */
			XRtoken_Hintroduction (&XIr);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: token_proc_end */
			{
#line 630 "psyntax.act"

    (XItok) = end_proc_token ( (XIb), (XIr) ) ;
#line 3171 "psyntax2.c"
			}
			/* END OF ACTION: token_proc_end */
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
	*XOtok = XItok;
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
			XRsimple_Htok_Hpars (&XIq);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: error_comma */
			{
#line 1139 "psyntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 3215 "psyntax2.c"
			}
			/* END OF ACTION: error_comma */
			/* BEGINNING OF ACTION: list_id_null */
			{
#line 513 "psyntax.act"

    (XIq) = NULL_list ( IDENTIFIER ) ;
#line 3223 "psyntax2.c"
			}
			/* END OF ACTION: list_id_null */
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
	*XOq = XIq;
}

void
XR835(SID_LIST_ID *XOq)
{
	SID_LIST_ID XIq;

	switch (CURRENT_TERMINAL) {
	case 177: case 188: case 218: case 225:
	case 227: case 250: case 261: case 263:
	case 282: case 296: case 303: case 305:
	case 314: case 320: case 328:
		{
			XRbound_Htok_Hpars (&XIq);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: error_comma */
			{
#line 1139 "psyntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 3265 "psyntax2.c"
			}
			/* END OF ACTION: error_comma */
			/* BEGINNING OF ACTION: list_id_null */
			{
#line 513 "psyntax.act"

    (XIq) = NULL_list ( IDENTIFIER ) ;
#line 3273 "psyntax2.c"
			}
			/* END OF ACTION: list_id_null */
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
	*XOq = XIq;
}

void
XR836(SID_LIST_ID *XIr, SID_LIST_ID *XOq)
{
	SID_LIST_ID XIq;

	switch (CURRENT_TERMINAL) {
	case 218: case 261: case 282: case 303:
	case 314:
		{
			XRprog_Htok_Hpars (*XIr, &XIq);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: error_comma */
			{
#line 1139 "psyntax.act"

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
#line 3313 "psyntax2.c"
			}
			/* END OF ACTION: error_comma */
			/* BEGINNING OF ACTION: list_id_null */
			{
#line 513 "psyntax.act"

    (XIq) = NULL_list ( IDENTIFIER ) ;
#line 3321 "psyntax2.c"
			}
			/* END OF ACTION: list_id_null */
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
	*XOq = XIq;
}

void
XR837(unsigned *XOi)
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
#line 814 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_ON ; 
#line 3357 "psyntax2.c"
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
#line 815 "psyntax.act"
 (XIi) = ( unsigned ) OPTION_OFF ; 
#line 3376 "psyntax2.c"
			}
			/* END OF ACTION: error_off */
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
XR840(unsigned *XI838, unsigned *XOc)
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
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
			/* BEGINNING OF ACTION: cast_join */
			{
#line 943 "psyntax.act"
 (XIc) = ( (*XI838) | (XIb) ) ; 
#line 3426 "psyntax2.c"
			}
			/* END OF ACTION: cast_join */
		}
		break;
	default:
		{
			XIc = *XI838;
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
	*XOc = XIc;
}

void
XR841(int *XOn)
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
#line 1014 "psyntax.act"
 (XIn) = OPT_empty_body ; 
#line 3467 "psyntax2.c"
			}
			/* END OF ACTION: opt_empty_body */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: opt_semicolon_extra */
			{
#line 1064 "psyntax.act"
 (XIn) = OPT_semicolon_extra ; 
#line 3478 "psyntax2.c"
			}
			/* END OF ACTION: opt_semicolon_extra */
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
XRsimple_Htok_Hparam(IDENTIFIER *XOid)
{
	IDENTIFIER XIid;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		TOKEN XItok;
		int XIt;
		IDENTIFIER XItid;

		XRtoken_Hintroduction (&XItok);
		XRtag_Hopt (&XIt);
		/* BEGINNING OF INLINE: 414 */
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
#line 188 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 3524 "psyntax2.c"
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

    XItid = crt_token->pp_data.id.use ;
#line 3537 "psyntax2.c"
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

    XItid = crt_token->pp_data.id.use ;
#line 3550 "psyntax2.c"
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

    XItid = crt_token->pp_data.id.use ;
#line 3563 "psyntax2.c"
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
#line 433 "psyntax.act"

    HASHID nm = lookup_anon () ;
    (XItid) = DEREF_id ( hashid_id ( nm ) ) ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
#line 3586 "psyntax2.c"
					}
					/* END OF ACTION: id_anon */
				}
				break;
			case 356:
				RESTORE_LEXER;
				goto XL1;
			}
		}
		/* END OF INLINE: 414 */
		/* BEGINNING OF ACTION: token_param */
		{
#line 593 "psyntax.act"

    (XIid) = make_tok_param ( (XItok), (XIt), (XItid) ) ;
#line 3602 "psyntax2.c"
		}
		/* END OF ACTION: token_param */
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOid = XIid;
}

void
XR842(int *XOn)
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
#line 1031 "psyntax.act"
 (XIn) = OPT_infer_int_cv ; 
#line 3641 "psyntax2.c"
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
#line 1010 "psyntax.act"
 (XIn) = OPT_dspec_none ; 
#line 3660 "psyntax2.c"
			}
			/* END OF ACTION: opt_dspec_none */
		}
		break;
	case 228:
		{
			ADVANCE_LEXER;
			XR843 (&XIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
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
XR843(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 176:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_param_impl */
			{
#line 1054 "psyntax.act"
 (XIn) = OPT_param_impl ; 
#line 3701 "psyntax2.c"
			}
			/* END OF ACTION: opt_param_impl */
		}
		break;
	case 113:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_dspec_none_func */
			{
#line 1011 "psyntax.act"
 (XIn) = OPT_dspec_none_func ; 
#line 3713 "psyntax2.c"
			}
			/* END OF ACTION: opt_dspec_none_func */
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
XR844(int *XOn)
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
			XR846 (&XIn);
			if ((CURRENT_TERMINAL) == 356) {
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
			XR845 (&XIn);
			if ((CURRENT_TERMINAL) == 356) {
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
#line 998 "psyntax.act"
 (XIn) = OPT_conv_ptr_void_ptr ; 
#line 3813 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_ptr_void_ptr */
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
XRliteral_Hitem(void)
{
	switch (CURRENT_TERMINAL) {
	case 41:
		{
			TYPE XIt;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: parse_type */
			{
#line 359 "psyntax.act"

    (XIt) = type_error ;
    parse_tok_type ( &(XIt) ) ;
    object_type ( (XIt), null_tag ) ;
#line 3847 "psyntax2.c"
			}
			/* END OF ACTION: parse_type */
			/* BEGINNING OF ACTION: literal_type */
			{
#line 739 "psyntax.act"

    add_type_literal ( (XIt) ) ;
#line 3855 "psyntax2.c"
			}
			/* END OF ACTION: literal_type */
		}
		break;
	case 78:
		{
			ADVANCE_LEXER;
			XR854 ();
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
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
XR845(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 110:
		{
			ADVANCE_LEXER;
			XR850 (&XIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 276:
		{
			ADVANCE_LEXER;
			XR848 (&XIn);
			if ((CURRENT_TERMINAL) == 356) {
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
#line 997 "psyntax.act"
 (XIn) = OPT_conv_ptr_ptr_void ; 
#line 3935 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_ptr_ptr_void */
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
XR846(int *XOn)
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
#line 986 "psyntax.act"
 (XIn) = OPT_conv_int_enum ; 
#line 3980 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_int_enum */
		}
		break;
	case 110:
		{
			ADVANCE_LEXER;
			XR849 (&XIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	case 276:
		{
			ADVANCE_LEXER;
			XR850 (&XIn);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
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
XR848(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 39:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_conv_ptr_ptr */
			{
#line 994 "psyntax.act"
 (XIn) = OPT_conv_ptr_ptr ; 
#line 4031 "psyntax2.c"
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
#line 995 "psyntax.act"
 (XIn) = OPT_conv_ptr_ptr_expl ; 
#line 4050 "psyntax2.c"
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
#line 996 "psyntax.act"
 (XIn) = OPT_conv_ptr_ptr_impl ; 
#line 4069 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_ptr_ptr_impl */
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
XR849(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 39:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_conv_int_int */
			{
#line 987 "psyntax.act"
 (XIn) = OPT_conv_int_int ; 
#line 4100 "psyntax2.c"
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
#line 988 "psyntax.act"
 (XIn) = OPT_conv_int_int_expl ; 
#line 4119 "psyntax2.c"
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
#line 989 "psyntax.act"
 (XIn) = OPT_conv_int_int_impl ; 
#line 4138 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_int_int_impl */
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
XR850(int *XOn)
{
	int XIn;

	switch (CURRENT_TERMINAL) {
	case 39:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_conv_int_ptr */
			{
#line 990 "psyntax.act"
 (XIn) = OPT_conv_int_ptr ; 
#line 4169 "psyntax2.c"
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
#line 991 "psyntax.act"
 (XIn) = OPT_conv_int_ptr_expl ; 
#line 4188 "psyntax2.c"
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
#line 992 "psyntax.act"
 (XIn) = OPT_conv_int_ptr_impl ; 
#line 4207 "psyntax2.c"
			}
			/* END OF ACTION: opt_conv_int_ptr_impl */
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
XR851(int *XOs)
{
	int XIs;

	switch (CURRENT_TERMINAL) {
	case 111:
		{
			ADVANCE_LEXER;
			XR853 (&XIs);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: suffix_u */
			{
#line 712 "psyntax.act"
 (XIs) = SUFFIX_U ; 
#line 4247 "psyntax2.c"
			}
			/* END OF ACTION: suffix_u */
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
	*XOs = XIs;
}

void
XRoption_Hnumber(int *XOn)
{
	int XIn;

	if ((CURRENT_TERMINAL) == 356) {
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
#line 292 "psyntax.act"

    XIs = crt_token->pp_data.exp ;
#line 4291 "psyntax2.c"
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

    XIs = crt_token->pp_data.exp ;
#line 4304 "psyntax2.c"
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
#line 799 "psyntax.act"

    STRING s = DEREF_str ( exp_string_lit_str ( (XIs) ) ) ;
    (XIn) = find_option_no ( s, 0 ) ;
    if ( (XIn) == -1 ) {
	report ( preproc_loc, ERR_pragma_option_bad ( s ) ) ;
    }
#line 4324 "psyntax2.c"
		}
		/* END OF ACTION: option_number */
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
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
			/* BEGINNING OF ACTION: suffix_ll */
			{
#line 715 "psyntax.act"
 (XIs) = SUFFIX_LL ; 
#line 4349 "psyntax2.c"
			}
			/* END OF ACTION: suffix_ll */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: suffix_l */
			{
#line 713 "psyntax.act"
 (XIs) = SUFFIX_L ; 
#line 4360 "psyntax2.c"
			}
			/* END OF ACTION: suffix_l */
		}
		break;
	case 356:
		return;
	}
	*XOs = XIs;
}

void
XR853(int *XOs)
{
	int XIs;

	switch (CURRENT_TERMINAL) {
	case 111:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: suffix_ull */
			{
#line 716 "psyntax.act"
 (XIs) = SUFFIX_ULL ; 
#line 4384 "psyntax2.c"
			}
			/* END OF ACTION: suffix_ull */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: suffix_ul */
			{
#line 714 "psyntax.act"
 (XIs) = SUFFIX_UL ; 
#line 4395 "psyntax2.c"
			}
			/* END OF ACTION: suffix_ul */
		}
		break;
	case 356:
		return;
	}
	*XOs = XIs;
}

void
XR854(void)
{
	switch (CURRENT_TERMINAL) {
	case 78:
		{
			unsigned XIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: rescan_keyword */
			{
#line 1175 "psyntax.act"

    int t = crt_lex_token ;
    if ( t == lex_identifier || t == lex_type_Hname ||
	 t == lex_namespace_Hname || t == lex_statement_Hname ) {
	t = find_hashid ( crt_token->pp_data.id.hash ) ;
	crt_lex_token = t ;
    }
#line 4425 "psyntax2.c"
			}
			/* END OF ACTION: rescan_keyword */
			/* BEGINNING OF INLINE: 533 */
			{
				switch (CURRENT_TERMINAL) {
				case 172: case 205: case 332:
					{
						XRallow_Hstate (&XIa);
						if ((CURRENT_TERMINAL) == 356) {
							RESTORE_LEXER;
							goto XL1;
						}
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: error_on */
						{
#line 814 "psyntax.act"
 (XIa) = ( unsigned ) OPTION_ON ; 
#line 4446 "psyntax2.c"
						}
						/* END OF ACTION: error_on */
					}
					break;
				}
			}
			/* END OF INLINE: 533 */
			switch (CURRENT_TERMINAL) {
			case 41:
				break;
			default:
				goto XL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: literal_star */
			{
#line 747 "psyntax.act"

    add_token_literal ( NULL_id, (XIa) ) ;
#line 4466 "psyntax2.c"
			}
			/* END OF ACTION: literal_star */
		}
		break;
	case 41: case 172: case 205: case 332:
		{
			unsigned XIa;
			IDENTIFIER XIid;

			/* BEGINNING OF ACTION: rescan_keyword */
			{
#line 1175 "psyntax.act"

    int t = crt_lex_token ;
    if ( t == lex_identifier || t == lex_type_Hname ||
	 t == lex_namespace_Hname || t == lex_statement_Hname ) {
	t = find_hashid ( crt_token->pp_data.id.hash ) ;
	crt_lex_token = t ;
    }
#line 4486 "psyntax2.c"
			}
			/* END OF ACTION: rescan_keyword */
			/* BEGINNING OF INLINE: 532 */
			{
				switch (CURRENT_TERMINAL) {
				case 172: case 205: case 332:
					{
						XRallow_Hstate (&XIa);
						if ((CURRENT_TERMINAL) == 356) {
							RESTORE_LEXER;
							goto XL1;
						}
					}
					break;
				default:
					{
						/* BEGINNING OF ACTION: error_off */
						{
#line 815 "psyntax.act"
 (XIa) = ( unsigned ) OPTION_OFF ; 
#line 4507 "psyntax2.c"
						}
						/* END OF ACTION: error_off */
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
			/* BEGINNING OF ACTION: rescan_id */
			{
#line 1166 "psyntax.act"

    int t = crt_lex_token ;
    if ( t >= FIRST_KEYWORD && t <= LAST_KEYWORD ) {
	crt_lex_token = lex_identifier ;
    }
#line 4530 "psyntax2.c"
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
#line 4543 "psyntax2.c"
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
#line 4556 "psyntax2.c"
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
#line 4569 "psyntax2.c"
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
#line 4582 "psyntax2.c"
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
#line 743 "psyntax.act"

    add_token_literal ( (XIid), (XIa) ) ;
#line 4598 "psyntax2.c"
			}
			/* END OF ACTION: literal_token */
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
XRbound_Htok_Hparam(IDENTIFIER *XOid)
{
	IDENTIFIER XIid;

	if ((CURRENT_TERMINAL) == 356) {
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
#line 188 "psyntax.act"

    XItid = crt_token->pp_data.id.use ;
#line 4639 "psyntax2.c"
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

    XItid = crt_token->pp_data.id.use ;
#line 4652 "psyntax2.c"
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

    XItid = crt_token->pp_data.id.use ;
#line 4665 "psyntax2.c"
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

    XItid = crt_token->pp_data.id.use ;
#line 4678 "psyntax2.c"
					}
					/* END OF EXTRACT: type-name */
					ADVANCE_LEXER;
				}
				break;
			case 356:
				RESTORE_LEXER;
				goto XL1;
			default:
				goto XL1;
			}
		}
		/* END OF INLINE: any-identifier */
		/* BEGINNING OF ACTION: token_param */
		{
#line 593 "psyntax.act"

    (XIid) = make_tok_param ( (XItok), (XIt), (XItid) ) ;
#line 4697 "psyntax2.c"
		}
		/* END OF ACTION: token_param */
	}
	goto XL0;
XL1:;
	SAVE_LEXER (356);
	return;
XL0:;
	*XOid = XIid;
}

void
XR855(int *XOt)
{
	int XIt;

	switch (CURRENT_TERMINAL) {
	case 326:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_discard */
			{
#line 397 "psyntax.act"
 (XIt) = lex_discard ; 
#line 4722 "psyntax2.c"
			}
			/* END OF ACTION: lex_discard */
		}
		break;
	case 327:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_unused */
			{
#line 409 "psyntax.act"
 (XIt) = lex_unused ; 
#line 4734 "psyntax2.c"
			}
			/* END OF ACTION: lex_unused */
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
#line 970 "psyntax.act"
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
#line 969 "psyntax.act"
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
#line 970 "psyntax.act"
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
#line 969 "psyntax.act"
 (XIe) = OPT_error ; 
#line 4801 "psyntax2.c"
			}
			/* END OF ACTION: opt_on */
		}
		break;
	case 332:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: opt_warning */
			{
#line 971 "psyntax.act"
 (XIe) = OPT_warning ; 
#line 4813 "psyntax2.c"
			}
			/* END OF ACTION: opt_warning */
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
XR856(int *XOt)
{
	int XIt;

	switch (CURRENT_TERMINAL) {
	case 289:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_reachable */
			{
#line 404 "psyntax.act"
 (XIt) = lex_reachable ; 
#line 4844 "psyntax2.c"
			}
			/* END OF ACTION: lex_reachable */
		}
		break;
	case 323:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: lex_unreachable */
			{
#line 408 "psyntax.act"
 (XIt) = lex_unreachable ; 
#line 4856 "psyntax2.c"
			}
			/* END OF ACTION: lex_unreachable */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: lex_set */
			{
#line 406 "psyntax.act"
 (XIt) = lex_set ; 
#line 4867 "psyntax2.c"
			}
			/* END OF ACTION: lex_set */
		}
		break;
	case 356:
		return;
	}
	*XOt = XIt;
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
#line 188 "psyntax.act"

    XIid = crt_token->pp_data.id.use ;
#line 4897 "psyntax2.c"
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
#line 4910 "psyntax2.c"
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
#line 4923 "psyntax2.c"
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
#line 4936 "psyntax2.c"
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
#line 682 "psyntax.act"

    preserve_id ( (XIid), lex_preserve ) ;
#line 4952 "psyntax2.c"
			}
			/* END OF ACTION: id_preserve */
			/* BEGINNING OF INLINE: preserve-list */
			goto XL2_preserve_Hlist;
			/* END OF INLINE: preserve-list */
		}
		UNREACHED;
	case 356:
		return;
	default:
		break;
	}
	return;
XL1:;
	SAVE_LEXER (356);
	return;
}

void
XR861(TYPE *XOt)
{
	TYPE XIt;

	switch (CURRENT_TERMINAL) {
	case 281:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_printf */
			{
#line 887 "psyntax.act"
 (XIt) = type_printf ; 
#line 4984 "psyntax2.c"
			}
			/* END OF ACTION: type_printf */
		}
		break;
	case 297:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: type_scanf */
			{
#line 888 "psyntax.act"
 (XIt) = type_scanf ; 
#line 4996 "psyntax2.c"
			}
			/* END OF ACTION: type_scanf */
		}
		break;
	case 156:
		{
			ADVANCE_LEXER;
			XR862 (&XIt);
			if ((CURRENT_TERMINAL) == 356) {
				RESTORE_LEXER;
				goto XL1;
			}
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
	*XOt = XIt;
}

/* END OF FILE */
