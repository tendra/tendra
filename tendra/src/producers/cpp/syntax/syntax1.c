/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#define __SID_SPLIT

/*
    		 Crown Copyright (c) 1997, 1998
    
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


#include "config.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "nspace_ops.h"
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
#include "dump.h"
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
    COMPOUND TYPE ALIASES

    These are the aliases for the compound types used in the parser.
*/

typedef LIST ( EXP ) SID_LIST_EXP ;
typedef LIST ( TYPE ) SID_LIST_TYPE ;


/*
    FUNCTION DECLARATIONS

    The function declarations are included at this point so that the
    type definitions are in scope.
*/

#include "syntax.h"


/*
    COMPILATION MODE

    The output of sid is automatically generated.  Hence it is not
    necessarily appropriate to apply the same level of checking to this
    as to the rest of the program.  These pragmas describe the relaxations
    allowed for the sid output.
*/

#if FS_TENDRA
#pragma TenDRA begin
#pragma TenDRA const conditional allow
#pragma TenDRA unreachable code allow
#pragma TenDRA variable analysis off
#endif



/* BEGINNING OF STATIC VARIABLES */

int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

void
ZR1270(EXP *ZO1241)
{
    EXP ZI1241;

    switch (CURRENT_TERMINAL) {
      case 2: case 7:
	{
	    IDENTIFIER ZI461;
	    NAMESPACE ZI426;
	    IDENTIFIER ZI420;
	    TYPE ZI1267;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI785;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
	    EXP ZI432;

	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    {
			{

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI461 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			{

    ZI461 = crt_token->pp_data.id.use ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    (ZI426) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI426) ;
	    }
	    {

    (ZI420) = check_id ( (ZI426), (ZI461), 0 ) ;
    last_namespace = (ZI426) ;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1267) ) ;
    COPY_id ( type_name ( (ZI1267) ), (ZI420) ) ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI512) = btype_none ; 
	    }
	    {
 (ZI785) = cv_none ; 
	    }
	    {

    (ZI415) = complete_pre_type ( (ZI512), (ZI1267), (ZI785), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR501 (&ZI498);
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI432) = make_func_cast_exp ( (ZI415), (ZI498) ) ;
	    }
	    ZR1242 (ZI432, &ZI1241);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
      case 147:
	{
	    NAMESPACE ZI426;
	    int ZI481;
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI420;
	    EXP ZI432;

	    {

    (ZI426) = global_namespace ;
    crt_id_qualifier = qual_top ;
    qual_namespace = (ZI426) ;
	    }
	    ZR476 (ZI426, &ZI481);
	    ZR477 (ZI426, &ZI479);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI420) = check_id ( (ZI426), (ZI479), (ZI481) ) ;
    last_namespace = (ZI426) ;
	    }
	    {

    (ZI432) = make_id_exp ( (ZI420) ) ;
	    }
	    ZR1242 (ZI432, &ZI1241);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO1241 = ZI1241;
}

void
ZR510(BASE_TYPE *ZO512)
{
    BASE_TYPE ZI512;

    switch (CURRENT_TERMINAL) {
      case 127:
	{
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_bool ; 
	    }
	}
	break;
      case 185:
	{
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_bottom ; 
	    }
	}
	break;
      case 97:
	{
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_char ; 
	    }
	}
	break;
      case 102:
	{
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_double ; 
	    }
	}
	break;
      case 106:
	{
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_float ; 
	    }
	}
	break;
      case 110:
	{
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_int ; 
	    }
	}
	break;
      case 111:
	{
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_long ; 
	    }
	}
	break;
      case 286:
	{
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_ptrdiff_t ; 
	    }
	}
	break;
      case 114:
	{
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_short ; 
	    }
	}
	break;
      case 115:
	{
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_signed ; 
	    }
	}
	break;
      case 299:
	{
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_size_t ; 
	    }
	}
	break;
      case 122:
	{
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_unsigned ; 
	    }
	}
	break;
      case 123:
	{
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_void ; 
	    }
	}
	break;
      case 156:
	{
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_wchar_t ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO512 = ZI512;
}

void
ZR1019(NAMESPACE ZI513)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_1019:;
    {
	ZR1018 (ZI513);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    goto ZL2_1019;
		}
		/*UNREACHED*/
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR1400(NAMESPACE *ZI426, IDENTIFIER *ZI1398, IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    BASE_TYPE ZI521;
	    NAMESPACE ZI522;
	    QUALIFIER ZI456;
	    int ZI457;
	    IDENTIFIER ZI523;
	    BASE_TYPE ZI524;
	    IDENTIFIER ZI479;

	    ADVANCE_LEXER;
	    {
 (ZI521) = btype_none ; 
	    }
	    ZI522 = *ZI426;
	    {

    (ZI456) = crt_id_qualifier ;
    (ZI457) = crt_templ_qualifier ;
	    }
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 43:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    ZR517 (&ZI523, &ZI524);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI456) ;
    crt_templ_qualifier = (ZI457) ;
	    }
	    {

    (ZI479) = make_pseudo_destr ( (*ZI1398), (ZI521), (ZI523), (ZI524) ) ;
	    }
	    {

    (ZI420) = check_id ( (ZI522), (ZI479), 0 ) ;
    last_namespace = (ZI522) ;
	    }
	}
	break;
      default:
	{
	    ZI420 = *ZI1398;
	}
	break;
      case 355:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO420 = ZI420;
}

void
ZR910(TYPE ZI575, BASE_TYPE *ZO512, TYPE *ZO415, CV_SPEC *ZO785, DECL_SPEC *ZO691)
{
    BASE_TYPE ZI512;
    TYPE ZI415;
    CV_SPEC ZI785;
    DECL_SPEC ZI691;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI876;
	TYPE ZI877;
	CV_SPEC ZI878;
	DECL_SPEC ZI911;

	ZR908 (ZI575, &ZI876, &ZI877, &ZI878, &ZI911);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* A type-name can be a declarator-id */
    if ( have_type_specifier && crt_lex_token == lex_type_Hname ) {
	crt_lex_token = lex_identifier ;
    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 2: case 7: case 8: case 9: case 25:
	      case 83: case 94: case 97: case 98: case 102:
	      case 104: case 105: case 106: case 110: case 111:
	      case 112: case 114: case 115: case 117: case 118:
	      case 120: case 121: case 122: case 123: case 124:
	      case 127: case 129: case 133: case 136: case 137:
	      case 138: case 153: case 155: case 156: case 185:
	      case 275: case 286: case 299:
		{
		    BASE_TYPE ZI880;
		    TYPE ZI881;
		    CV_SPEC ZI882;
		    DECL_SPEC ZI913;

		    ZR910 (ZI575, &ZI880, &ZI881, &ZI882, &ZI913);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    if ( (ZI876) & (ZI880) ) {
	(ZI512) = join_pre_types ( (ZI876), (ZI880) ) ;
    } else {
	(ZI512) = ( (ZI876) | (ZI880) ) ;
    }
		    }
		    {

    /* Join two partial types */
    if ( IS_NULL_type ( (ZI877) ) ) {
	(ZI415) = (ZI881) ;
    } else if ( IS_NULL_type ( (ZI881) ) ) {
	(ZI415) = (ZI877) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (ZI877), (ZI881) ) ) ;
	(ZI415) = (ZI881) ;
    }
		    }
		    {

    CV_SPEC c = ( (ZI878) & (ZI882) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI785) = ( (ZI878) | (ZI882) ) ;
		    }
		    {

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI911) & (ZI913) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI691) = ( (ZI911) | (ZI913) ) ;
		    }
		}
		break;
	      default:
		{
		    ZI512 = ZI876;
		    ZI415 = ZI877;
		    ZI785 = ZI878;
		    ZI691 = ZI911;
		}
		break;
	    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO512 = ZI512;
    *ZO415 = ZI415;
    *ZO785 = ZI785;
    *ZO691 = ZI691;
}

void
ZR1147(EXP ZI1145, EXP *ZO1146)
{
    EXP ZI1146;

  ZL2_1147:;
    switch (CURRENT_TERMINAL) {
      case 27:
	{
	    EXP ZI498;
	    EXP ZI559;

	    ZI498 = ZI1145;
	    {

    ZI559 = crt_token->pp_data.exp ;
	    }
	    ADVANCE_LEXER;
	    {

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZI559), c ) ;
	    }
	    {

    target_decl ( lex_elif, (ZI559) ) ;
	    }
	    ZR1030 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		ZI1145 = ZI498;
		goto ZL2_1147;
	    }
	}
	/*UNREACHED*/
      default:
	{
	    ZI1146 = ZI1145;
	}
	break;
      case 355:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO1146 = ZI1146;
}

void
ZR416(void)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 40:
		    break;
		  default:
		    goto ZL1;
		}
		ADVANCE_LEXER;
	    }
	}
    }
    return;
  ZL1:;
    {
	int ZI415;

	{
 (ZI415) = lex_close_Hsquare_H1 ; 
	}
	{

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZI415) ) report ( crt_loc, ERR_lex_expect ( (ZI415) ) ) ;
	}
    }
}

void
ZR477(NAMESPACE ZI426, IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 5:
	{
	    {

    ZI420 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 1:
	{
	    {

    ZI420 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 3:
	{
	    {

    ZI420 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 6:
	{
	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI420 = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 141:
	{
	    {

    if ( add_nested_nspace ( (ZI426) ) ) {
	RESCAN_LEXER ;
    }
	    }
	    parse_operator (&ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( remove_nested_nspace ( (ZI426) ) ) {
	RESCAN_LEXER ;
    }
	    }
	}
	break;
      case 355:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO420 = ZI420;
}

void
ZR948(IDENTIFIER ZI420, TYPE *ZO415, int *ZO559)
{
    TYPE ZI415;
    int ZI559;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    {
		{
		    {

    /* Resolve function-style initialisers from function declarators */
    (ZI0) = predict_init () ;
		    }
		    if (!ZI0)
			goto ZL3;
		    {
 (ZI559) = 1 ; 
		    }
		    {

    (ZI415) = NULL_type ;
		    }
		    goto ZL2;
		}
		/*UNREACHED*/
	      ZL3:;
		switch (CURRENT_TERMINAL) {
		  case 2: case 7: case 8: case 9: case 25:
		  case 39: case 47: case 83: case 94: case 97:
		  case 98: case 102: case 104: case 105: case 106:
		  case 110: case 111: case 112: case 114: case 115:
		  case 117: case 118: case 120: case 121: case 122:
		  case 123: case 124: case 127: case 129: case 133:
		  case 136: case 137: case 138: case 153: case 155:
		  case 156: case 185: case 275: case 286: case 299:
		    {
			int ZI945;

			{
 (ZI945) = 0 ; 
			}
			{

    func_type_defn ( 0 ) ;
    begin_param ( (ZI420) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
			}
			ZR946 (ZI945, &ZI415);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
			}
			{
 (ZI559) = 0 ; 
			}
		    }
		    break;
		  default:
		    goto ZL1;
		}
	      ZL2:;
	    }
	}
	break;
      case 332:
	{
	    int ZI945;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZI945) = 1 ; 
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI420) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR946 (ZI945, &ZI415);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	    {
 (ZI559) = 0 ; 
	    }
	}
	break;
      case 66:
	{
	    EXP ZI432;

	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 66:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    ZR955 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI432) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI415) ) ;
	    }
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 40:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    {
 (ZI559) = 0 ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO415 = ZI415;
    *ZO559 = ZI559;
}

void
ZR973(TYPE ZI575, int ZI498, IDENTIFIER *ZO460)
{
    IDENTIFIER ZI460;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	BASE_TYPE ZI512;
	TYPE ZI877;
	CV_SPEC ZI878;
	DECL_SPEC ZI911;
	TYPE ZI881;
	DECL_SPEC ZI913;
	TYPE ZI415;
	IDENTIFIER ZI420;
	EXP ZI432;

	ZR910 (ZI575, &ZI512, &ZI877, &ZI878, &ZI911);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* Complete a declaration specifier and a type */
    (ZI913) = complete_dspec ( (ZI911), (ZI512), (ZI877), (ZI878) ) ;
    (ZI881) = complete_pre_type ( (ZI512), (ZI877), (ZI878), 0 ) ;
    have_type_specifier = 0 ;
	}
	{

    crt_templ_qualifier = 0 ;
	}
	ZR963 (ZI881, &ZI415, &ZI420);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI460) = make_param_decl ( (ZI913), (ZI415), (ZI420), (ZI498) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 36:
		{
		    EXP ZI494;

		    ADVANCE_LEXER;
		    {

    in_default_arg++ ;
		    }
		    {
			{
			    {

    (ZI0) = ( in_class_defn && (ZI498) == CONTEXT_PARAMETER ) ;
			    }
			    if (!ZI0)
				goto ZL4;
			    {

    (ZI494) = skip_default_arg ( (ZI460) ) ;
			    }
			    goto ZL3;
			}
			/*UNREACHED*/
		      ZL4:;
			switch (CURRENT_TERMINAL) {
			  case 1: case 2: case 3: case 5: case 6:
			  case 7: case 8: case 9: case 17: case 18:
			  case 19: case 20: case 21: case 22: case 23:
			  case 25: case 33: case 43: case 59: case 61:
			  case 62: case 65: case 69: case 71: case 78:
			  case 83: case 85: case 97: case 102: case 106:
			  case 110: case 111: case 114: case 115: case 116:
			  case 122: case 123: case 127: case 130: case 131:
			  case 132: case 135: case 140: case 141: case 145:
			  case 146: case 148: case 149: case 150: case 152:
			  case 156: case 170: case 185: case 206: case 210:
			  case 255: case 286: case 299: case 330:
			    {
				ZR651 (&ZI494);
				if ((CURRENT_TERMINAL) == 355) {
				    RESTORE_LEXER;
				    goto ZL1;
				}
			    }
			    break;
			  default:
			    goto ZL1;
			}
		      ZL3:;
		    }
		    {

    in_default_arg-- ;
		    }
		    ZI432 = ZI494;
		}
		break;
	      default:
		{
		    {

    (ZI432) = NULL_exp ;
		    }
		}
		break;
	    }
	}
	{

    init_param ( (ZI460), (ZI432) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO460 = ZI460;
}

void
ZR437(EXP *ZO432)
{
    EXP ZI432;

    switch (CURRENT_TERMINAL) {
      case 135:
	{
	    ADVANCE_LEXER;
	    {

    (ZI432) = make_bool_exp ( BOOL_FALSE, exp_int_lit_tag ) ;
	    }
	}
	break;
      case 150:
	{
	    ADVANCE_LEXER;
	    {

    (ZI432) = make_bool_exp ( BOOL_TRUE, exp_int_lit_tag ) ;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO432 = ZI432;
}

void
ZR1404(NAMESPACE *ZI426, IDENTIFIER *ZI1402, IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    BASE_TYPE ZI521;
	    NAMESPACE ZI522;
	    QUALIFIER ZI456;
	    int ZI457;
	    IDENTIFIER ZI523;
	    BASE_TYPE ZI524;
	    IDENTIFIER ZI479;

	    ADVANCE_LEXER;
	    {
 (ZI521) = btype_none ; 
	    }
	    ZI522 = *ZI426;
	    {

    (ZI456) = crt_id_qualifier ;
    (ZI457) = crt_templ_qualifier ;
	    }
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 43:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    ZR517 (&ZI523, &ZI524);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI456) ;
    crt_templ_qualifier = (ZI457) ;
	    }
	    {

    (ZI479) = make_pseudo_destr ( (*ZI1402), (ZI521), (ZI523), (ZI524) ) ;
	    }
	    {

    (ZI420) = check_id ( (ZI522), (ZI479), 0 ) ;
    last_namespace = (ZI522) ;
	    }
	}
	break;
      default:
	{
	    ZI420 = *ZI1402;
	}
	break;
      case 355:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO420 = ZI420;
}

void
ZR1151(TYPE ZI1149, TYPE *ZO1150)
{
    TYPE ZI1150;

  ZL2_1151:;
    switch (CURRENT_TERMINAL) {
      case 66:
	{
	    EXP ZI432;
	    TYPE ZI481;
	    TYPE ZI415;

	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 66:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    ZR653 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI432) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI481) ) ;
	    }
	    {

    (ZI415) = ( IS_NULL_type ( (ZI1149) ) ? (ZI481) : inject_pre_type ( (ZI1149), (ZI481), 0 ) ) ;
	    }
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 40:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    ZI1149 = ZI415;
	    goto ZL2_1151;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1150 = ZI1149;
	}
	break;
      case 355:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO1150 = ZI1150;
}

void
ZR427(NAMESPACE *ZO426)
{
    NAMESPACE ZI426;

    switch (CURRENT_TERMINAL) {
      case 9:
	{
	    {

    ZI426 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (ZI426) ;
	    }
	}
	break;
      case 8:
	{
	    {

    ZI426 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (ZI426) ;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO426 = ZI426;
}

void
ZR701(EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	EXP ZI494;
	EXP ZI498;
	int ZI672;
	EXP ZI457;

	ZR700 (&ZI494, &ZI498, &ZI672);
	{
	    switch (CURRENT_TERMINAL) {
	      case 28:
		{
		    int ZI575;

		    ADVANCE_LEXER;
		    {

    crt_hash_cond = make_else_cond ( crt_hash_cond ) ;
		    }
		    {

    (ZI575) = unreached_code ;
    if ( (ZI575) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
		    }
		    ZR680 (&ZI457);
		    if ((CURRENT_TERMINAL) == 355) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZI457) = NULL_exp ;
		    }
		}
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	{

    crt_hash_cond = (ZI498) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
 unreached_prev = (ZI672) ; 
	}
	{

    (ZI432) = end_hash_if_stmt ( (ZI494), (ZI457) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO432 = ZI432;
}

void
ZR1407(NAMESPACE *ZI426, IDENTIFIER *ZI1405, IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    BASE_TYPE ZI521;
	    NAMESPACE ZI522;
	    QUALIFIER ZI456;
	    int ZI457;
	    IDENTIFIER ZI523;
	    BASE_TYPE ZI524;
	    IDENTIFIER ZI479;

	    ADVANCE_LEXER;
	    {
 (ZI521) = btype_none ; 
	    }
	    ZI522 = *ZI426;
	    {

    (ZI456) = crt_id_qualifier ;
    (ZI457) = crt_templ_qualifier ;
	    }
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 43:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    ZR517 (&ZI523, &ZI524);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI456) ;
    crt_templ_qualifier = (ZI457) ;
	    }
	    {

    (ZI479) = make_pseudo_destr ( (*ZI1405), (ZI521), (ZI523), (ZI524) ) ;
	    }
	    {

    (ZI420) = check_id ( (ZI522), (ZI479), 0 ) ;
    last_namespace = (ZI522) ;
	    }
	}
	break;
      default:
	{
	    ZI420 = *ZI1405;
	}
	break;
      case 355:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO420 = ZI420;
}

void
ZR518(NAMESPACE ZI426, IDENTIFIER *ZO420)
{
    IDENTIFIER ZI420;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    ADVANCE_LEXER;
	    ZR1315 (&ZI426, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 9:
	{
	    NAMESPACE ZI1318;

	    {

    ZI1318 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1319 (&ZI426, &ZI1318, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 8:
	{
	    NAMESPACE ZI1316;

	    {

    ZI1316 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1317 (&ZI426, &ZI1316, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 97: case 102: case 106: case 110: case 111:
      case 114: case 115: case 122: case 123: case 127:
      case 156: case 185: case 286: case 299:
	{
	    BASE_TYPE ZI521;
	    IDENTIFIER ZI520;
	    NAMESPACE ZI522;
	    QUALIFIER ZI456;
	    int ZI457;
	    IDENTIFIER ZI523;
	    BASE_TYPE ZI524;
	    IDENTIFIER ZI479;

	    ZR510 (&ZI521);
	    switch (CURRENT_TERMINAL) {
	      case 83:
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI520) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    ZI522 = ZI426;
	    {

    (ZI456) = crt_id_qualifier ;
    (ZI457) = crt_templ_qualifier ;
	    }
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 43:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    ZR517 (&ZI523, &ZI524);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI456) ;
    crt_templ_qualifier = (ZI457) ;
	    }
	    {

    (ZI479) = make_pseudo_destr ( (ZI520), (ZI521), (ZI523), (ZI524) ) ;
	    }
	    {

    (ZI420) = check_id ( (ZI522), (ZI479), 0 ) ;
    last_namespace = (ZI522) ;
	    }
	}
	break;
      case 43:
	{
	    IDENTIFIER ZI523;
	    BASE_TYPE ZI524;

	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 43:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    ZR517 (&ZI523, &ZI524);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    (ZI420) = make_pseudo_destr ( (ZI523), (ZI524), (ZI523), (ZI524) ) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
	{
	    IDENTIFIER ZI479;

	    ZR477 (ZI426, &ZI479);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    (ZI420) = check_id ( (ZI426), (ZI479), 0 ) ;
    last_namespace = (ZI426) ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI461;
	    IDENTIFIER ZI1312;

	    ZR473 (&ZI461);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1312) = check_id ( (ZI426), (ZI461), 0 ) ;
    last_namespace = (ZI426) ;
	    }
	    ZR1314 (&ZI426, &ZI1312, &ZI420);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 355:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO420 = ZI420;
}

void
ZR908(TYPE ZI575, BASE_TYPE *ZO512, TYPE *ZO415, CV_SPEC *ZO785, DECL_SPEC *ZO691)
{
    BASE_TYPE ZI512;
    TYPE ZI415;
    CV_SPEC ZI785;
    DECL_SPEC ZI691;

    switch (CURRENT_TERMINAL) {
      case 2: case 7: case 8: case 9: case 25:
      case 83: case 97: case 98: case 102: case 104:
      case 106: case 110: case 111: case 114: case 115:
      case 118: case 121: case 122: case 123: case 124:
      case 127: case 129: case 153: case 156: case 185:
      case 286: case 299:
	{
	    ZR874 (ZI575, &ZI512, &ZI415, &ZI785);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI691) = dspec_none ; 
	    }
	}
	break;
      case 94: case 105: case 112: case 117: case 120:
      case 133: case 136: case 137: case 138: case 155:
      case 275:
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 136:
		    {
			ADVANCE_LEXER;
			{
 (ZI691) = dspec_friend ; 
			}
		    }
		    break;
		  case 120:
		    {
			ADVANCE_LEXER;
			{
 (ZI691) = dspec_typedef ; 
			}
		    }
		    break;
		  case 133: case 137: case 155: case 275:
		    {
			ZR901 (&ZI691);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  case 94: case 105: case 112: case 117: case 138:
		    {
			ZR896 (&ZI691);
			if ((CURRENT_TERMINAL) == 355) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    {

    if ( have_type_specifier ) report ( crt_loc, ERR_dcl_spec_order ( (ZI691) ) ) ;
	    }
	    {
 (ZI512) = btype_none ; 
	    }
	    {

    (ZI415) = NULL_type ;
	    }
	    {
 (ZI785) = cv_none ; 
	    }
	}
	break;
      case 355:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO512 = ZI512;
    *ZO415 = ZI415;
    *ZO785 = ZI785;
    *ZO691 = ZI691;
}

void
parse_init(IDENTIFIER ZI460, EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	ZR1000 (ZI460, &ZI432);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    {
	{

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
	{

    (ZI432) = NULL_exp ;
	}
    }
  ZL0:;
    *ZO432 = ZI432;
}

void
ZR1029(TYPE ZI415, DECL_SPEC ZI691)
{
    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
  ZL2_1029:;
    {
	BASE_TYPE ZI1250;
	TYPE ZI1251;
	CV_SPEC ZI1252;
	DECL_SPEC ZI1253;
	BASE_TYPE ZI512;
	TYPE ZI877;
	CV_SPEC ZI878;
	DECL_SPEC ZI911;
	DECL_SPEC ZI913;
	EXP ZI432;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL3;
	ZR908 (ZI415, &ZI1250, &ZI1251, &ZI1252, &ZI1253);
	ZR919 (&ZI415, &ZI1250, &ZI1251, &ZI1252, &ZI1253, &ZI512, &ZI877, &ZI878, &ZI911);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI691) & (ZI911) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI913) = ( (ZI691) | (ZI911) ) ;
	}
	ZR1254 (&ZI415, &ZI512, &ZI877, &ZI878, &ZI913);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI432) = NULL_exp ;
	}
	{

    external_declaration ( (ZI432), 1 ) ;
	}
	goto ZL2_1029;
    }
    /*UNREACHED*/
  ZL3:;
    switch (CURRENT_TERMINAL) {
      case 105:
	{
	    EXP ZI432;

	    ZR1064 (ZI415, ZI691, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI432), 1 ) ;
	    }
	    goto ZL2_1029;
	}
	/*UNREACHED*/
      case 134: case 147:
	{
	    EXP ZI432;

	    ZR1074 (ZI415, ZI691, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI432), 1 ) ;
	    }
	    goto ZL2_1029;
	}
	/*UNREACHED*/
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 10:
      case 11: case 33: case 65: case 77: case 78:
      case 83: case 141:
	{
	    BASE_TYPE ZI512;
	    TYPE ZI877;
	    CV_SPEC ZI1255;
	    EXP ZI432;

	    {
 (ZI512) = btype_none ; 
	    }
	    {

    (ZI877) = NULL_type ;
	    }
	    {
 (ZI1255) = cv_none ; 
	    }
	    ZR1256 (&ZI415, &ZI691, &ZI512, &ZI877, &ZI1255, &ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI432), 1 ) ;
	    }
	    goto ZL2_1029;
	}
	/*UNREACHED*/
      case 26: case 30: case 126: case 139: case 154:
	{
	    {

    if ( !IS_NULL_type ( (ZI415) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI691) ) ;
	    }
	    ZR1257 ();
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_1029;
	    }
	}
	/*UNREACHED*/
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (355);
    return;
}

void
ZR954(TYPE *ZO415)
{
    TYPE ZI415;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    IDENTIFIER ZI420;
	    int ZI945;

	    ADVANCE_LEXER;
	    {

    (ZI420) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {
 (ZI945) = 0 ; 
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI420) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR946 (ZI945, &ZI415);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	}
	break;
      case 332:
	{
	    IDENTIFIER ZI420;
	    int ZI945;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI420) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {
 (ZI945) = 1 ; 
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI420) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR946 (ZI945, &ZI415);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI432;

	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 66:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    ZR955 (&ZI432);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI432) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI415) ) ;
	    }
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 40:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	}
	break;
      case 355:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (355);
    return;
  ZL0:;
    *ZO415 = ZI415;
}

void
ZR683(EXP ZI559, EXP *ZO432)
{
    EXP ZI432;

    if ((CURRENT_TERMINAL) == 355) {
	return;
    }
    {
	DECL_SPEC ZI691;
	TYPE ZI415;
	EXP ZI1516;
	EXP ZI1556;
	EXP ZI494;

	{

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
	}
	if (!ZI0)
	    goto ZL2;
	{
 (ZI691) = dspec_none ; 
	}
	{

    (ZI415) = NULL_type ;
	}
	ZR689 (ZI415, ZI691, &ZI1516);
	if ((CURRENT_TERMINAL) == 355) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI1556) = (ZI1516) ;
    in_declaration-- ;
	}
	{

    unreached_fall = 1 ;
	}
	{

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1556) ) ;
	}
	{

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	}
	{

    RESCAN_LEXER ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 170:
	{
	    int ZI451;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1527;
	    int ZI672;
	    EXP ZI1574;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_alignof ; 
	    }
	    ZR594 (ZI451, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1527);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1574) = make_exp_stmt ( (ZI1527) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1574) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 83:
	{
	    EXP ZI1563;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR1477 (&ZI1563);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1563) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 23:
	{
	    EXP ZI1281;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1537;
	    int ZI672;
	    EXP ZI1584;
	    EXP ZI494;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1281 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR1242 (ZI1281, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1537);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1584) = make_exp_stmt ( (ZI1537) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1584) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 24:
	{
	    EXP ZI1514;
	    EXP ZI1553;
	    EXP ZI494;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1514 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1553) = make_exp_stmt ( (ZI1514) ) ;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1553) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 25:
	{
	    TYPE ZI1267;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI785;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
	    EXP ZI1284;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1539;
	    int ZI672;
	    EXP ZI1586;
	    EXP ZI494;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1267 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {
 (ZI512) = btype_none ; 
	    }
	    {
 (ZI785) = cv_none ; 
	    }
	    {

    (ZI415) = complete_pre_type ( (ZI512), (ZI1267), (ZI785), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR501 (&ZI498);
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1284) = make_func_cast_exp ( (ZI415), (ZI498) ) ;
	    }
	    ZR1242 (ZI1284, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1539);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1586) = make_exp_stmt ( (ZI1539) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1586) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 130:
	{
	    TYPE ZI415;
	    EXP ZI1463;
	    int ZI552;
	    EXP ZI1273;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1530;
	    int ZI672;
	    EXP ZI1577;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1463, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1273) = make_const_cast_exp ( (ZI415), (ZI1463), (ZI552) ) ;
	    }
	    ZR1242 (ZI1273, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1530);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1577) = make_exp_stmt ( (ZI1530) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1577) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 5:
	{
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI420;
	    EXP ZI1285;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1542;
	    int ZI672;
	    EXP ZI1589;
	    EXP ZI494;

	    {

    ZI479 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI420) = check_id ( NULL_nspace, (ZI479), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1285) = make_id_exp ( (ZI420) ) ;
	    }
	    ZR1242 (ZI1285, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1542);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1589) = make_exp_stmt ( (ZI1542) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1589) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 206:
	{
	    EXP ZI1456;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1519;
	    int ZI672;
	    EXP ZI1566;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1456);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_cast_exp ( type_void, (ZI1456), 0 ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1519);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1566) = make_exp_stmt ( (ZI1519) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1566) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 132:
	{
	    TYPE ZI415;
	    EXP ZI1466;
	    int ZI552;
	    EXP ZI1276;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1533;
	    int ZI672;
	    EXP ZI1580;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1466, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1276) = make_dynamic_cast_exp ( (ZI415), (ZI1466), (ZI552) ) ;
	    }
	    ZR1242 (ZI1276, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1533);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1580) = make_exp_stmt ( (ZI1533) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1580) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 210:
	{
	    EXP ZI1279;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1536;
	    int ZI672;
	    EXP ZI1583;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    {

    (ZI1279) = make_ellipsis_exp () ;
	    }
	    ZR1242 (ZI1279, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1536);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1583) = make_exp_stmt ( (ZI1536) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1583) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 9:
	{
	    NAMESPACE ZI426;
	    EXP ZI1562;
	    EXP ZI494;

	    {

    ZI426 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1476 (&ZI426, &ZI1562);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1562) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 1:
	{
	    IDENTIFIER ZI1467;
	    EXP ZI1557;
	    EXP ZI494;

	    {

    ZI1467 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1472 (&ZI1467, &ZI1557);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1557) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 346:
	{
	    EXP ZI1552;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR1441 (&ZI1552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1552) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 255:
	{
	    EXP ZI1455;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1517;
	    int ZI672;
	    EXP ZI1564;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1455);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_lit_exp ( (ZI1455) ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1517);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1564) = make_exp_stmt ( (ZI1517) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1564) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 61:
	{
	    EXP ZI1458;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1521;
	    int ZI672;
	    EXP ZI1568;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1458);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_prefix_exp ( lex_minus_Hminus, (ZI1458) ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1521);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1568) = make_exp_stmt ( (ZI1521) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1568) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 3:
	{
	    IDENTIFIER ZI1471;
	    EXP ZI1559;
	    EXP ZI494;

	    {

    ZI1471 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1472 (&ZI1471, &ZI1559);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1559) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 8:
	{
	    NAMESPACE ZI426;
	    EXP ZI1561;
	    EXP ZI494;

	    {

    ZI426 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1475 (&ZI426, &ZI1561);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1561) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 65:
	{
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1518;
	    int ZI672;
	    EXP ZI1565;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR1288 (&ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1518);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1565) = make_exp_stmt ( (ZI1518) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1565) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 71:
	{
	    EXP ZI1457;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1520;
	    int ZI672;
	    EXP ZI1567;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1457);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_prefix_exp ( lex_plus_Hplus, (ZI1457) ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1520);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1567) = make_exp_stmt ( (ZI1520) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1567) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 145:
	{
	    TYPE ZI415;
	    EXP ZI1464;
	    int ZI552;
	    EXP ZI1274;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1531;
	    int ZI672;
	    EXP ZI1578;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1464, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1274) = make_reinterp_cast_exp ( (ZI415), (ZI1464), (ZI552) ) ;
	    }
	    ZR1242 (ZI1274, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1531);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1578) = make_exp_stmt ( (ZI1531) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1578) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 77:
	{
	    EXP ZI1550;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    {

    (ZI1550) = NULL_exp ;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1550) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 116:
	{
	    int ZI451;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1526;
	    int ZI672;
	    EXP ZI1573;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_sizeof ; 
	    }
	    ZR594 (ZI451, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1526);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1573) = make_exp_stmt ( (ZI1526) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1573) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 78:
	{
	    EXP ZI1459;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1522;
	    int ZI672;
	    EXP ZI1569;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR582 (&ZI1459);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_indir_exp ( (ZI1459) ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1522);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1569) = make_exp_stmt ( (ZI1522) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1569) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 4:
	{
	    IDENTIFIER ZI1473;
	    EXP ZI1560;
	    EXP ZI494;

	    {

    ZI1473 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1474 (&ZI1473, &ZI1560);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1560) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 146:
	{
	    TYPE ZI415;
	    EXP ZI1465;
	    int ZI552;
	    EXP ZI1275;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1532;
	    int ZI672;
	    EXP ZI1579;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    ZR553 (&ZI415, &ZI1465, &ZI552);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1275) = make_static_cast_exp ( (ZI415), (ZI1465), (ZI552) ) ;
	    }
	    ZR1242 (ZI1275, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1532);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1579) = make_exp_stmt ( (ZI1532) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1579) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 6:
	{
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI420;
	    EXP ZI1285;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1543;
	    int ZI672;
	    EXP ZI1590;
	    EXP ZI494;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI479 = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI420) = check_id ( NULL_nspace, (ZI479), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1285) = make_id_exp ( (ZI420) ) ;
	    }
	    ZR1242 (ZI1285, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1543);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1590) = make_exp_stmt ( (ZI1543) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1590) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 7:
	{
	    IDENTIFIER ZI461;
	    IDENTIFIER ZI420;
	    TYPE ZI1267;
	    BASE_TYPE ZI512;
	    CV_SPEC ZI785;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
	    EXP ZI1283;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1544;
	    int ZI672;
	    EXP ZI1591;
	    EXP ZI494;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI461 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI420) = (ZI461) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1267) ) ;
    COPY_id ( type_name ( (ZI1267) ), (ZI420) ) ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI512) = btype_none ; 
	    }
	    {
 (ZI785) = cv_none ; 
	    }
	    {

    (ZI415) = complete_pre_type ( (ZI512), (ZI1267), (ZI785), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR501 (&ZI498);
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1283) = make_func_cast_exp ( (ZI415), (ZI498) ) ;
	    }
	    ZR1242 (ZI1283, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1544);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1591) = make_exp_stmt ( (ZI1544) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1591) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 148:
	{
	    EXP ZI1278;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1535;
	    int ZI672;
	    EXP ZI1582;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    {

    (ZI1278) = make_this_exp () ;
	    }
	    ZR1242 (ZI1278, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1535);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1582) = make_exp_stmt ( (ZI1535) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1582) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 2:
	{
	    IDENTIFIER ZI1469;
	    EXP ZI1558;
	    EXP ZI494;

	    {

    ZI1469 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1470 (&ZI1469, &ZI1558);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1558) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 152:
	{
	    int ZI451;
	    EXP ZI1272;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1529;
	    int ZI672;
	    EXP ZI1576;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_typeid ; 
	    }
	    ZR554 (ZI451, &ZI1272);
	    ZR1242 (ZI1272, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1529);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1576) = make_exp_stmt ( (ZI1529) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1576) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 330:
	{
	    int ZI451;
	    EXP ZI1271;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1528;
	    int ZI672;
	    EXP ZI1575;
	    EXP ZI494;

	    ADVANCE_LEXER;
	    {
 (ZI451) = lex_vtable ; 
	    }
	    ZR554 (ZI451, &ZI1271);
	    ZR1242 (ZI1271, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1528);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1575) = make_exp_stmt ( (ZI1528) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1575) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 33:
	{
	    EXP ZI1460;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1523;
	    int ZI672;
	    EXP ZI1570;
	    EXP ZI494;

	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 33:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    ZR582 (&ZI1460);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_ref_exp ( (ZI1460), 0 ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1523);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1570) = make_exp_stmt ( (ZI1523) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1570) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 97: case 102: case 106: case 110: case 111:
      case 114: case 115: case 122: case 123: case 127:
      case 156: case 185: case 286: case 299:
	{
	    BASE_TYPE ZI512;
	    TYPE ZI1267;
	    CV_SPEC ZI785;
	    TYPE ZI415;
	    SID_LIST_EXP ZI498;
	    EXP ZI1282;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1538;
	    int ZI672;
	    EXP ZI1585;
	    EXP ZI494;

	    ZR510 (&ZI512);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1267) = NULL_type ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI785) = cv_none ; 
	    }
	    {

    (ZI415) = complete_pre_type ( (ZI512), (ZI1267), (ZI785), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR501 (&ZI498);
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      case 355:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1282) = make_func_cast_exp ( (ZI415), (ZI498) ) ;
	    }
	    ZR1242 (ZI1282, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1538);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1585) = make_exp_stmt ( (ZI1538) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1585) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 289: case 323:
	{
	    EXP ZI1549;
	    EXP ZI494;

	    ZR778 (&ZI1549);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1549) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 96: case 100: case 223:
	{
	    EXP ZI1555;
	    EXP ZI494;

	    ZR664 ();
	    ZR1442 (&ZI1555);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1555) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 298: case 324:
	{
	    EXP ZI1436;
	    EXP ZI1513;
	    int ZI672;
	    EXP ZI1551;
	    EXP ZI494;

	    ZR645 (&ZI1436);
	    ZR1438 (&ZI1436, &ZI1513);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1551) = make_exp_stmt ( (ZI1513) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1551) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 101: case 107: case 125:
	{
	    EXP ZI1546;
	    EXP ZI494;

	    ZR740 (&ZI1546);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1546) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 95: case 99: case 108: case 113:
	{
	    EXP ZI1547;
	    EXP ZI494;

	    ZR754 (&ZI1547);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1547) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 17: case 18: case 19: case 20: case 21:
      case 22: case 135: case 150:
	{
	    EXP ZI1277;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1534;
	    int ZI672;
	    EXP ZI1581;
	    EXP ZI494;

	    ZR438 (&ZI1277);
	    ZR1242 (ZI1277, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1534);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1581) = make_exp_stmt ( (ZI1534) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1581) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 62:
	{
	    EXP ZI1461;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1524;
	    int ZI672;
	    EXP ZI1571;
	    EXP ZI494;

	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 62:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    ZR582 (&ZI1461);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_not_exp ( (ZI1461) ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1524);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1571) = make_exp_stmt ( (ZI1524) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1571) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 64:
	{
	    EXP ZI494;

	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 64:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    {

    COPY_int ( exp_sequence_block ( (ZI559) ), 2 ) ;
	    }
	    ZR678 (ZI559, &ZI494);
	    {
		if ((CURRENT_TERMINAL) == 355) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
		{
		    switch (CURRENT_TERMINAL) {
		      case 38:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 141:
	{
	    IDENTIFIER ZI479;
	    IDENTIFIER ZI420;
	    EXP ZI1285;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1541;
	    int ZI672;
	    EXP ZI1588;
	    EXP ZI494;

	    parse_operator (&ZI479);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI420) = check_id ( NULL_nspace, (ZI479), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1285) = make_id_exp ( (ZI420) ) ;
	    }
	    ZR1242 (ZI1285, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1541);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1588) = make_exp_stmt ( (ZI1541) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1588) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 26: case 109: case 119:
	{
	    EXP ZI1545;
	    EXP ZI494;

	    ZR715 (&ZI1545);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1545) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 149:
	{
	    EXP ZI1289;
	    EXP ZI1515;
	    int ZI672;
	    EXP ZI1554;
	    EXP ZI494;

	    ZR637 (&ZI1289);
	    ZR1291 (&ZI1289, &ZI1515);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1554) = make_exp_stmt ( (ZI1515) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1554) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 151:
	{
	    EXP ZI1548;
	    EXP ZI494;

	    ZR773 (&ZI1548);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1548) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 131: case 140:
	{
	    int ZI457;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1540;
	    int ZI672;
	    EXP ZI1587;
	    EXP ZI494;

	    {
 (ZI457) = 0 ; 
	    }
	    ZR1432 (&ZI457, &ZI1454);
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1540);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1587) = make_exp_stmt ( (ZI1540) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1587) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 43: case 59: case 69: case 85:
	{
	    int ZI451;
	    EXP ZI1462;
	    EXP ZI1454;
	    EXP ZI1453;
	    EXP ZI1452;
	    EXP ZI1451;
	    EXP ZI1450;
	    EXP ZI1449;
	    EXP ZI1448;
	    EXP ZI1447;
	    EXP ZI1446;
	    EXP ZI1445;
	    EXP ZI1444;
	    EXP ZI1443;
	    EXP ZI1265;
	    EXP ZI1289;
	    EXP ZI1525;
	    int ZI672;
	    EXP ZI1572;
	    EXP ZI494;

	    {
 (ZI451) = crt_lex_token ; 
	    }
	    ZR597 ();
	    ZR582 (&ZI1462);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1454) = make_uminus_exp ( (ZI451), (ZI1462) ) ;
	    }
	    ZR1238 (ZI1454, &ZI1453);
	    ZR1234 (ZI1453, &ZI1452);
	    ZR1230 (ZI1452, &ZI1451);
	    ZR1226 (ZI1451, &ZI1450);
	    ZR1222 (ZI1450, &ZI1449);
	    ZR1218 (ZI1449, &ZI1448);
	    ZR1214 (ZI1448, &ZI1447);
	    ZR1210 (ZI1447, &ZI1446);
	    ZR1206 (ZI1446, &ZI1445);
	    ZR1202 (ZI1445, &ZI1444);
	    ZR1198 (ZI1444, &ZI1443);
	    ZR1194 (ZI1443, &ZI1265);
	    ZR1266 (&ZI1265, &ZI1289);
	    ZR1291 (&ZI1289, &ZI1525);
	    if ((CURRENT_TERMINAL) == 355) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI672) = unreached_code ;
    if ( (ZI672) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1572) = make_exp_stmt ( (ZI1525) ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI494) = add_compound_stmt ( (ZI559), (ZI1572) ) ;
	    }
	    {

    (ZI432) = end_compound_stmt ( (ZI494) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    {
	{

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
	{

    (ZI432) = end_compound_stmt ( (ZI559) ) ;
	}
	{

    RESCAN_LEXER ;
	}
    }
  ZL0:;
    *ZO432 = ZI432;
}

/* END OF FILE */
