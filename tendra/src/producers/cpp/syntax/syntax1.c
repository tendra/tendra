/*
 * Automatically generated from the files:
 *	/u/g/release/Source/src/producers/cpp/syntax/syntax.sid
 * and
 *	/u/g/release/Source/src/producers/cpp/syntax/syntax.act
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
ZR509 PROTO_N ((ZO511))
  PROTO_T (BASE_TYPE *ZO511)
{
    BASE_TYPE ZI511;

    switch (CURRENT_TERMINAL) {
      case 127:
	{
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_bool ; 
	    }
	}
	break;
      case 184:
	{
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_bottom ; 
	    }
	}
	break;
      case 97:
	{
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_char ; 
	    }
	}
	break;
      case 102:
	{
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_double ; 
	    }
	}
	break;
      case 106:
	{
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_float ; 
	    }
	}
	break;
      case 110:
	{
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_int ; 
	    }
	}
	break;
      case 111:
	{
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_long ; 
	    }
	}
	break;
      case 285:
	{
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_ptrdiff_t ; 
	    }
	}
	break;
      case 114:
	{
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_short ; 
	    }
	}
	break;
      case 115:
	{
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_signed ; 
	    }
	}
	break;
      case 298:
	{
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_size_t ; 
	    }
	}
	break;
      case 122:
	{
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_unsigned ; 
	    }
	}
	break;
      case 123:
	{
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_void ; 
	    }
	}
	break;
      case 156:
	{
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_wchar_t ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO511 = ZI511;
}

void
ZR1398 PROTO_N ((ZI425, ZI1396, ZO419))
  PROTO_T (NAMESPACE *ZI425 X IDENTIFIER *ZI1396 X IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    BASE_TYPE ZI520;
	    NAMESPACE ZI521;
	    QUALIFIER ZI455;
	    int ZI456;
	    IDENTIFIER ZI522;
	    BASE_TYPE ZI523;
	    IDENTIFIER ZI478;

	    ADVANCE_LEXER;
	    {
 (ZI520) = btype_none ; 
	    }
	    ZI521 = *ZI425;
	    {

    (ZI455) = crt_id_qualifier ;
    (ZI456) = crt_templ_qualifier ;
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
	    ZR516 (&ZI522, &ZI523);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI455) ;
    crt_templ_qualifier = (ZI456) ;
	    }
	    {

    (ZI478) = make_pseudo_destr ( (*ZI1396), (ZI520), (ZI522), (ZI523) ) ;
	    }
	    {

    (ZI419) = check_id ( (ZI521), (ZI478), 0 ) ;
    last_namespace = (ZI521) ;
	    }
	}
	break;
      default:
	{
	    ZI419 = *ZI1396;
	}
	break;
      case 354:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO419 = ZI419;
}

void
ZR1145 PROTO_N ((ZI1143, ZO1144))
  PROTO_T (EXP ZI1143 X EXP *ZO1144)
{
    EXP ZI1144;

  ZL2_1145:;
    switch (CURRENT_TERMINAL) {
      case 27:
	{
	    EXP ZI497;
	    EXP ZI558;

	    ZI497 = ZI1143;
	    {

    ZI558 = crt_token->pp_data.exp ;
	    }
	    ADVANCE_LEXER;
	    {

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZI558), c ) ;
	    }
	    {

    target_decl ( lex_elif, (ZI558) ) ;
	    }
	    ZR1028 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		ZI1143 = ZI497;
		goto ZL2_1145;
	    }
	}
	/*UNREACHED*/
      default:
	{
	    ZI1144 = ZI1143;
	}
	break;
      case 354:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO1144 = ZI1144;
}

void
ZR1017 PROTO_N ((ZI512))
  PROTO_T (NAMESPACE ZI512)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_1017:;
    {
	ZR1016 (ZI512);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    goto ZL2_1017;
		}
		/*UNREACHED*/
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR908 PROTO_N ((ZI574, ZO511, ZO414, ZO783, ZO689))
  PROTO_T (TYPE ZI574 X BASE_TYPE *ZO511 X TYPE *ZO414 X CV_SPEC *ZO783 X DECL_SPEC *ZO689)
{
    BASE_TYPE ZI511;
    TYPE ZI414;
    CV_SPEC ZI783;
    DECL_SPEC ZI689;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI874;
	TYPE ZI875;
	CV_SPEC ZI876;
	DECL_SPEC ZI909;

	ZR906 (ZI574, &ZI874, &ZI875, &ZI876, &ZI909);
	if ((CURRENT_TERMINAL) == 354) {
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
	      case 138: case 153: case 155: case 156: case 184:
	      case 274: case 285: case 298:
		{
		    BASE_TYPE ZI878;
		    TYPE ZI879;
		    CV_SPEC ZI880;
		    DECL_SPEC ZI911;

		    ZR908 (ZI574, &ZI878, &ZI879, &ZI880, &ZI911);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    if ( (ZI874) & (ZI878) ) {
	(ZI511) = join_pre_types ( (ZI874), (ZI878) ) ;
    } else {
	(ZI511) = ( (ZI874) | (ZI878) ) ;
    }
		    }
		    {

    /* Join two partial types */
    if ( IS_NULL_type ( (ZI875) ) ) {
	(ZI414) = (ZI879) ;
    } else if ( IS_NULL_type ( (ZI879) ) ) {
	(ZI414) = (ZI875) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (ZI875), (ZI879) ) ) ;
	(ZI414) = (ZI879) ;
    }
		    }
		    {

    CV_SPEC c = ( (ZI876) & (ZI880) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI783) = ( (ZI876) | (ZI880) ) ;
		    }
		    {

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI909) & (ZI911) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI689) = ( (ZI909) | (ZI911) ) ;
		    }
		}
		break;
	      default:
		{
		    ZI511 = ZI874;
		    ZI414 = ZI875;
		    ZI783 = ZI876;
		    ZI689 = ZI909;
		}
		break;
	    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO511 = ZI511;
    *ZO414 = ZI414;
    *ZO783 = ZI783;
    *ZO689 = ZI689;
}

void
ZR415 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
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
	int ZI414;

	{
 (ZI414) = lex_close_Hsquare_H1 ; 
	}
	{

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZI414) ) report ( crt_loc, ERR_lex_expect ( (ZI414) ) ) ;
	}
    }
}

void
ZR476 PROTO_N ((ZI425, ZO419))
  PROTO_T (NAMESPACE ZI425 X IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 5:
	{
	    {

    ZI419 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 1:
	{
	    {

    ZI419 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 3:
	{
	    {

    ZI419 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 6:
	{
	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI419 = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 141:
	{
	    {

    if ( add_nested_nspace ( (ZI425) ) ) {
	RESCAN_LEXER ;
    }
	    }
	    parse_operator (&ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( remove_nested_nspace ( (ZI425) ) ) {
	RESCAN_LEXER ;
    }
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO419 = ZI419;
}

void
ZR946 PROTO_N ((ZI419, ZO414, ZO558))
  PROTO_T (IDENTIFIER ZI419 X TYPE *ZO414 X int *ZO558)
{
    TYPE ZI414;
    int ZI558;

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
 (ZI558) = 1 ; 
		    }
		    {

    (ZI414) = NULL_type ;
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
		  case 156: case 184: case 274: case 285: case 298:
		    {
			int ZI943;

			{
 (ZI943) = 0 ; 
			}
			{

    func_type_defn ( 0 ) ;
    begin_param ( (ZI419) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
			}
			ZR944 (ZI943, &ZI414);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
			}
			{
 (ZI558) = 0 ; 
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
      case 331:
	{
	    int ZI943;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZI943) = 1 ; 
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI419) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR944 (ZI943, &ZI414);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	    {
 (ZI558) = 0 ; 
	    }
	}
	break;
      case 66:
	{
	    EXP ZI431;

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
	    ZR953 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI431) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI414) ) ;
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
 (ZI558) = 0 ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO414 = ZI414;
    *ZO558 = ZI558;
}

void
ZR1402 PROTO_N ((ZI425, ZI1400, ZO419))
  PROTO_T (NAMESPACE *ZI425 X IDENTIFIER *ZI1400 X IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    BASE_TYPE ZI520;
	    NAMESPACE ZI521;
	    QUALIFIER ZI455;
	    int ZI456;
	    IDENTIFIER ZI522;
	    BASE_TYPE ZI523;
	    IDENTIFIER ZI478;

	    ADVANCE_LEXER;
	    {
 (ZI520) = btype_none ; 
	    }
	    ZI521 = *ZI425;
	    {

    (ZI455) = crt_id_qualifier ;
    (ZI456) = crt_templ_qualifier ;
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
	    ZR516 (&ZI522, &ZI523);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI455) ;
    crt_templ_qualifier = (ZI456) ;
	    }
	    {

    (ZI478) = make_pseudo_destr ( (*ZI1400), (ZI520), (ZI522), (ZI523) ) ;
	    }
	    {

    (ZI419) = check_id ( (ZI521), (ZI478), 0 ) ;
    last_namespace = (ZI521) ;
	    }
	}
	break;
      default:
	{
	    ZI419 = *ZI1400;
	}
	break;
      case 354:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO419 = ZI419;
}

void
ZR971 PROTO_N ((ZI574, ZI497, ZO459))
  PROTO_T (TYPE ZI574 X int ZI497 X IDENTIFIER *ZO459)
{
    IDENTIFIER ZI459;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI511;
	TYPE ZI875;
	CV_SPEC ZI876;
	DECL_SPEC ZI909;
	TYPE ZI879;
	DECL_SPEC ZI911;
	TYPE ZI414;
	IDENTIFIER ZI419;
	EXP ZI431;

	ZR908 (ZI574, &ZI511, &ZI875, &ZI876, &ZI909);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* Complete a declaration specifier and a type */
    (ZI911) = complete_dspec ( (ZI909), (ZI511), (ZI875), (ZI876) ) ;
    (ZI879) = complete_pre_type ( (ZI511), (ZI875), (ZI876), 0 ) ;
    have_type_specifier = 0 ;
	}
	{

    crt_templ_qualifier = 0 ;
	}
	ZR961 (ZI879, &ZI414, &ZI419);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI459) = make_param_decl ( (ZI911), (ZI414), (ZI419), (ZI497) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 36:
		{
		    EXP ZI493;

		    ADVANCE_LEXER;
		    {

    in_default_arg++ ;
		    }
		    {
			{
			    {

    (ZI0) = ( in_class_defn && (ZI497) == CONTEXT_PARAMETER ) ;
			    }
			    if (!ZI0)
				goto ZL4;
			    {

    (ZI493) = skip_default_arg ( (ZI459) ) ;
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
			  case 156: case 170: case 184: case 205: case 209:
			  case 285: case 298: case 329:
			    {
				ZR649 (&ZI493);
				if ((CURRENT_TERMINAL) == 354) {
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
		    ZI431 = ZI493;
		}
		break;
	      default:
		{
		    {

    (ZI431) = NULL_exp ;
		    }
		}
		break;
	    }
	}
	{

    init_param ( (ZI459), (ZI431) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO459 = ZI459;
}

void
ZR1149 PROTO_N ((ZI1147, ZO1148))
  PROTO_T (TYPE ZI1147 X TYPE *ZO1148)
{
    TYPE ZI1148;

  ZL2_1149:;
    switch (CURRENT_TERMINAL) {
      case 66:
	{
	    EXP ZI431;
	    TYPE ZI480;
	    TYPE ZI414;

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
	    ZR651 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI431) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI480) ) ;
	    }
	    {

    (ZI414) = ( IS_NULL_type ( (ZI1147) ) ? (ZI480) : inject_pre_type ( (ZI1147), (ZI480), 0 ) ) ;
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
	    ZI1147 = ZI414;
	    goto ZL2_1149;
	}
	/*UNREACHED*/
      default:
	{
	    ZI1148 = ZI1147;
	}
	break;
      case 354:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO1148 = ZI1148;
}

void
ZR436 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    switch (CURRENT_TERMINAL) {
      case 135:
	{
	    ADVANCE_LEXER;
	    {

    (ZI431) = make_bool_exp ( BOOL_FALSE, exp_int_lit_tag ) ;
	    }
	}
	break;
      case 150:
	{
	    ADVANCE_LEXER;
	    {

    (ZI431) = make_bool_exp ( BOOL_TRUE, exp_int_lit_tag ) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR1405 PROTO_N ((ZI425, ZI1403, ZO419))
  PROTO_T (NAMESPACE *ZI425 X IDENTIFIER *ZI1403 X IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    BASE_TYPE ZI520;
	    NAMESPACE ZI521;
	    QUALIFIER ZI455;
	    int ZI456;
	    IDENTIFIER ZI522;
	    BASE_TYPE ZI523;
	    IDENTIFIER ZI478;

	    ADVANCE_LEXER;
	    {
 (ZI520) = btype_none ; 
	    }
	    ZI521 = *ZI425;
	    {

    (ZI455) = crt_id_qualifier ;
    (ZI456) = crt_templ_qualifier ;
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
	    ZR516 (&ZI522, &ZI523);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI455) ;
    crt_templ_qualifier = (ZI456) ;
	    }
	    {

    (ZI478) = make_pseudo_destr ( (*ZI1403), (ZI520), (ZI522), (ZI523) ) ;
	    }
	    {

    (ZI419) = check_id ( (ZI521), (ZI478), 0 ) ;
    last_namespace = (ZI521) ;
	    }
	}
	break;
      default:
	{
	    ZI419 = *ZI1403;
	}
	break;
      case 354:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO419 = ZI419;
}

void
ZR426 PROTO_N ((ZO425))
  PROTO_T (NAMESPACE *ZO425)
{
    NAMESPACE ZI425;

    switch (CURRENT_TERMINAL) {
      case 9:
	{
	    {

    ZI425 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_full ;
    qual_namespace = (ZI425) ;
	    }
	}
	break;
      case 8:
	{
	    {

    ZI425 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    {

    crt_id_qualifier = qual_nested ;
    qual_namespace = (ZI425) ;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO425 = ZI425;
}

void
ZR699 PROTO_N ((ZO431))
  PROTO_T (EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI493;
	EXP ZI497;
	int ZI670;
	EXP ZI456;

	ZR698 (&ZI493, &ZI497, &ZI670);
	{
	    switch (CURRENT_TERMINAL) {
	      case 28:
		{
		    int ZI574;

		    ADVANCE_LEXER;
		    {

    crt_hash_cond = make_else_cond ( crt_hash_cond ) ;
		    }
		    {

    (ZI574) = unreached_code ;
    if ( (ZI574) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
		    }
		    ZR678 (&ZI456);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZI456) = NULL_exp ;
		    }
		}
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	{

    crt_hash_cond = (ZI497) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
 unreached_prev = (ZI670) ; 
	}
	{

    (ZI431) = end_hash_if_stmt ( (ZI493), (ZI456) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR517 PROTO_N ((ZI425, ZO419))
  PROTO_T (NAMESPACE ZI425 X IDENTIFIER *ZO419)
{
    IDENTIFIER ZI419;

    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    ADVANCE_LEXER;
	    ZR1313 (&ZI425, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 9:
	{
	    NAMESPACE ZI1316;

	    {

    ZI1316 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1317 (&ZI425, &ZI1316, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 8:
	{
	    NAMESPACE ZI1314;

	    {

    ZI1314 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1315 (&ZI425, &ZI1314, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 97: case 102: case 106: case 110: case 111:
      case 114: case 115: case 122: case 123: case 127:
      case 156: case 184: case 285: case 298:
	{
	    BASE_TYPE ZI520;
	    IDENTIFIER ZI519;
	    NAMESPACE ZI521;
	    QUALIFIER ZI455;
	    int ZI456;
	    IDENTIFIER ZI522;
	    BASE_TYPE ZI523;
	    IDENTIFIER ZI478;

	    ZR509 (&ZI520);
	    switch (CURRENT_TERMINAL) {
	      case 83:
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI519) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    ZI521 = ZI425;
	    {

    (ZI455) = crt_id_qualifier ;
    (ZI456) = crt_templ_qualifier ;
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
	    ZR516 (&ZI522, &ZI523);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = (ZI455) ;
    crt_templ_qualifier = (ZI456) ;
	    }
	    {

    (ZI478) = make_pseudo_destr ( (ZI519), (ZI520), (ZI522), (ZI523) ) ;
	    }
	    {

    (ZI419) = check_id ( (ZI521), (ZI478), 0 ) ;
    last_namespace = (ZI521) ;
	    }
	}
	break;
      case 43:
	{
	    IDENTIFIER ZI522;
	    BASE_TYPE ZI523;

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
	    ZR516 (&ZI522, &ZI523);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    (ZI419) = make_pseudo_destr ( (ZI522), (ZI523), (ZI522), (ZI523) ) ;
	    }
	}
	break;
      case 1: case 3: case 5: case 6: case 141:
	{
	    IDENTIFIER ZI478;

	    ZR476 (ZI425, &ZI478);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    crt_id_qualifier = qual_none ;
    crt_templ_qualifier = 0 ;
    qual_namespace = NULL_nspace ;
	    }
	    {

    (ZI419) = check_id ( (ZI425), (ZI478), 0 ) ;
    last_namespace = (ZI425) ;
	    }
	}
	break;
      case 2: case 7:
	{
	    IDENTIFIER ZI460;
	    IDENTIFIER ZI1310;

	    ZR472 (&ZI460);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1310) = check_id ( (ZI425), (ZI460), 0 ) ;
    last_namespace = (ZI425) ;
	    }
	    ZR1312 (&ZI425, &ZI1310, &ZI419);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO419 = ZI419;
}

void
ZR906 PROTO_N ((ZI574, ZO511, ZO414, ZO783, ZO689))
  PROTO_T (TYPE ZI574 X BASE_TYPE *ZO511 X TYPE *ZO414 X CV_SPEC *ZO783 X DECL_SPEC *ZO689)
{
    BASE_TYPE ZI511;
    TYPE ZI414;
    CV_SPEC ZI783;
    DECL_SPEC ZI689;

    switch (CURRENT_TERMINAL) {
      case 2: case 7: case 8: case 9: case 25:
      case 83: case 97: case 98: case 102: case 104:
      case 106: case 110: case 111: case 114: case 115:
      case 118: case 121: case 122: case 123: case 124:
      case 127: case 129: case 153: case 156: case 184:
      case 285: case 298:
	{
	    ZR872 (ZI574, &ZI511, &ZI414, &ZI783);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI689) = dspec_none ; 
	    }
	}
	break;
      case 94: case 105: case 112: case 117: case 120:
      case 133: case 136: case 137: case 138: case 155:
      case 274:
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 136:
		    {
			ADVANCE_LEXER;
			{
 (ZI689) = dspec_friend ; 
			}
		    }
		    break;
		  case 120:
		    {
			ADVANCE_LEXER;
			{
 (ZI689) = dspec_typedef ; 
			}
		    }
		    break;
		  case 133: case 137: case 155: case 274:
		    {
			ZR899 (&ZI689);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  case 94: case 105: case 112: case 117: case 138:
		    {
			ZR894 (&ZI689);
			if ((CURRENT_TERMINAL) == 354) {
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

    if ( have_type_specifier ) report ( crt_loc, ERR_dcl_spec_order ( (ZI689) ) ) ;
	    }
	    {
 (ZI511) = btype_none ; 
	    }
	    {

    (ZI414) = NULL_type ;
	    }
	    {
 (ZI783) = cv_none ; 
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO511 = ZI511;
    *ZO414 = ZI414;
    *ZO783 = ZI783;
    *ZO689 = ZI689;
}

void
parse_init PROTO_N ((ZI459, ZO431))
  PROTO_T (IDENTIFIER ZI459 X EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	ZR998 (ZI459, &ZI431);
	if ((CURRENT_TERMINAL) == 354) {
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

    (ZI431) = NULL_exp ;
	}
    }
  ZL0:;
    *ZO431 = ZI431;
}

void
ZR1027 PROTO_N ((ZI414, ZI689))
  PROTO_T (TYPE ZI414 X DECL_SPEC ZI689)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_1027:;
    {
	BASE_TYPE ZI1248;
	TYPE ZI1249;
	CV_SPEC ZI1250;
	DECL_SPEC ZI1251;
	BASE_TYPE ZI511;
	TYPE ZI875;
	CV_SPEC ZI876;
	DECL_SPEC ZI909;
	DECL_SPEC ZI911;
	EXP ZI431;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL3;
	ZR906 (ZI414, &ZI1248, &ZI1249, &ZI1250, &ZI1251);
	ZR917 (&ZI414, &ZI1248, &ZI1249, &ZI1250, &ZI1251, &ZI511, &ZI875, &ZI876, &ZI909);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI689) & (ZI909) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI911) = ( (ZI689) | (ZI909) ) ;
	}
	ZR1252 (&ZI414, &ZI511, &ZI875, &ZI876, &ZI911);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI431) = NULL_exp ;
	}
	{

    external_declaration ( (ZI431), 1 ) ;
	}
	goto ZL2_1027;
    }
    /*UNREACHED*/
  ZL3:;
    switch (CURRENT_TERMINAL) {
      case 105:
	{
	    EXP ZI431;

	    ZR1062 (ZI414, ZI689, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI431), 1 ) ;
	    }
	    goto ZL2_1027;
	}
	/*UNREACHED*/
      case 134: case 147:
	{
	    EXP ZI431;

	    ZR1072 (ZI414, ZI689, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI431), 1 ) ;
	    }
	    goto ZL2_1027;
	}
	/*UNREACHED*/
      case 1: case 2: case 3: case 4: case 5:
      case 6: case 7: case 8: case 9: case 10:
      case 11: case 33: case 65: case 77: case 78:
      case 83: case 141:
	{
	    BASE_TYPE ZI511;
	    TYPE ZI875;
	    CV_SPEC ZI1253;
	    EXP ZI431;

	    {
 (ZI511) = btype_none ; 
	    }
	    {

    (ZI875) = NULL_type ;
	    }
	    {
 (ZI1253) = cv_none ; 
	    }
	    ZR1254 (&ZI414, &ZI689, &ZI511, &ZI875, &ZI1253, &ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI431), 1 ) ;
	    }
	    goto ZL2_1027;
	}
	/*UNREACHED*/
      case 26: case 30: case 126: case 139: case 154:
	{
	    {

    if ( !IS_NULL_type ( (ZI414) ) ) report ( crt_loc, ERR_temp_decl_bad () ) ;
    UNUSED ( (ZI689) ) ;
	    }
	    ZR1255 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_1027;
	    }
	}
	/*UNREACHED*/
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR952 PROTO_N ((ZO414))
  PROTO_T (TYPE *ZO414)
{
    TYPE ZI414;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    IDENTIFIER ZI419;
	    int ZI943;

	    ADVANCE_LEXER;
	    {

    (ZI419) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {
 (ZI943) = 0 ; 
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI419) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR944 (ZI943, &ZI414);
	    if ((CURRENT_TERMINAL) == 354) {
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
      case 331:
	{
	    IDENTIFIER ZI419;
	    int ZI943;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI419) = NULL_id ;
    crt_id_qualifier = qual_none ;
    qual_namespace = NULL_nspace ;
	    }
	    {
 (ZI943) = 1 ; 
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI419) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR944 (ZI943, &ZI414);
	    if ((CURRENT_TERMINAL) == 354) {
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
	    EXP ZI431;

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
	    ZR953 (&ZI431);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI431) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI414) ) ;
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
      case 354:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO414 = ZI414;
}

void
ZR681 PROTO_N ((ZI558, ZO431))
  PROTO_T (EXP ZI558 X EXP *ZO431)
{
    EXP ZI431;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	DECL_SPEC ZI689;
	TYPE ZI414;
	EXP ZI1512;
	EXP ZI1551;
	EXP ZI493;

	{

    /* Resolve declaration-statements from expression-statements */
    int b = predict_decl () ;
    if ( b ) in_declaration++ ;
    (ZI0) = b ;
	}
	if (!ZI0)
	    goto ZL2;
	{
 (ZI689) = dspec_none ; 
	}
	{

    (ZI414) = NULL_type ;
	}
	ZR687 (ZI414, ZI689, &ZI1512);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI1551) = (ZI1512) ;
    in_declaration-- ;
	}
	{

    unreached_fall = 1 ;
	}
	{

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1551) ) ;
	}
	{

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
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
	    int ZI450;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1522;
	    int ZI670;
	    EXP ZI1568;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_alignof ; 
	    }
	    ZR593 (ZI450, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1522);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1568) = make_exp_stmt ( (ZI1522) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1568) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 83:
	{
	    EXP ZI1558;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR1474 (&ZI1558);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1558) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 23:
	{
	    EXP ZI1279;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1532;
	    int ZI670;
	    EXP ZI1578;
	    EXP ZI493;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1279 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR1240 (ZI1279, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1532);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1578) = make_exp_stmt ( (ZI1532) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1578) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 24:
	{
	    EXP ZI1510;
	    EXP ZI1548;
	    EXP ZI493;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1510 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1548) = make_exp_stmt ( (ZI1510) ) ;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1548) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 25:
	{
	    TYPE ZI1265;
	    BASE_TYPE ZI511;
	    CV_SPEC ZI783;
	    TYPE ZI414;
	    SID_LIST_EXP ZI497;
	    EXP ZI1282;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1534;
	    int ZI670;
	    EXP ZI1580;
	    EXP ZI493;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1265 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {
 (ZI511) = btype_none ; 
	    }
	    {
 (ZI783) = cv_none ; 
	    }
	    {

    (ZI414) = complete_pre_type ( (ZI511), (ZI1265), (ZI783), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR500 (&ZI497);
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1282) = make_func_cast_exp ( (ZI414), (ZI497) ) ;
	    }
	    ZR1240 (ZI1282, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1534);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1580) = make_exp_stmt ( (ZI1534) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1580) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 130:
	{
	    TYPE ZI414;
	    EXP ZI1460;
	    int ZI551;
	    EXP ZI1271;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1525;
	    int ZI670;
	    EXP ZI1571;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI1460, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1271) = make_const_cast_exp ( (ZI414), (ZI1460), (ZI551) ) ;
	    }
	    ZR1240 (ZI1271, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1525);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1571) = make_exp_stmt ( (ZI1525) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1571) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 5:
	{
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI419;
	    EXP ZI1283;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1537;
	    int ZI670;
	    EXP ZI1583;
	    EXP ZI493;

	    {

    ZI478 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI419) = check_id ( NULL_nspace, (ZI478), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1283) = make_id_exp ( (ZI419) ) ;
	    }
	    ZR1240 (ZI1283, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1537);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1583) = make_exp_stmt ( (ZI1537) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1583) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 205:
	{
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1514;
	    int ZI670;
	    EXP ZI1560;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR581 (&ZI1453);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_cast_exp ( type_void, (ZI1453), 0 ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1514);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1560) = make_exp_stmt ( (ZI1514) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1560) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 132:
	{
	    TYPE ZI414;
	    EXP ZI1463;
	    int ZI551;
	    EXP ZI1274;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1528;
	    int ZI670;
	    EXP ZI1574;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI1463, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1274) = make_dynamic_cast_exp ( (ZI414), (ZI1463), (ZI551) ) ;
	    }
	    ZR1240 (ZI1274, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1528);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1574) = make_exp_stmt ( (ZI1528) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1574) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 209:
	{
	    EXP ZI1277;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1531;
	    int ZI670;
	    EXP ZI1577;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    {

    (ZI1277) = make_ellipsis_exp () ;
	    }
	    ZR1240 (ZI1277, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1531);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1577) = make_exp_stmt ( (ZI1531) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1577) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 9:
	{
	    NAMESPACE ZI425;
	    EXP ZI1557;
	    EXP ZI493;

	    {

    ZI425 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1473 (&ZI425, &ZI1557);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1557) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 1:
	{
	    IDENTIFIER ZI1464;
	    EXP ZI1552;
	    EXP ZI493;

	    {

    ZI1464 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1469 (&ZI1464, &ZI1552);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1552) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 345:
	{
	    EXP ZI1547;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR1439 (&ZI1547);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1547) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 61:
	{
	    EXP ZI1455;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1516;
	    int ZI670;
	    EXP ZI1562;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR581 (&ZI1455);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_prefix_exp ( lex_minus_Hminus, (ZI1455) ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1516);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1562) = make_exp_stmt ( (ZI1516) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1562) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 3:
	{
	    IDENTIFIER ZI1468;
	    EXP ZI1554;
	    EXP ZI493;

	    {

    ZI1468 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1469 (&ZI1468, &ZI1554);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1554) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 8:
	{
	    NAMESPACE ZI425;
	    EXP ZI1556;
	    EXP ZI493;

	    {

    ZI425 = crt_token->pp_data.ns ;
	    }
	    ADVANCE_LEXER;
	    ZR1472 (&ZI425, &ZI1556);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1556) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 65:
	{
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1513;
	    int ZI670;
	    EXP ZI1559;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR1286 (&ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1513);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1559) = make_exp_stmt ( (ZI1513) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1559) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 71:
	{
	    EXP ZI1454;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1515;
	    int ZI670;
	    EXP ZI1561;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR581 (&ZI1454);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_prefix_exp ( lex_plus_Hplus, (ZI1454) ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1515);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1561) = make_exp_stmt ( (ZI1515) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1561) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 145:
	{
	    TYPE ZI414;
	    EXP ZI1461;
	    int ZI551;
	    EXP ZI1272;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1526;
	    int ZI670;
	    EXP ZI1572;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI1461, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* n is the number of type definitions in t */
    (ZI1272) = make_reinterp_cast_exp ( (ZI414), (ZI1461), (ZI551) ) ;
	    }
	    ZR1240 (ZI1272, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1526);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1572) = make_exp_stmt ( (ZI1526) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1572) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 77:
	{
	    EXP ZI1545;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    {

    (ZI1545) = NULL_exp ;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1545) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 116:
	{
	    int ZI450;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1521;
	    int ZI670;
	    EXP ZI1567;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_sizeof ; 
	    }
	    ZR593 (ZI450, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1521);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1567) = make_exp_stmt ( (ZI1521) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1567) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 78:
	{
	    EXP ZI1456;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1517;
	    int ZI670;
	    EXP ZI1563;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR581 (&ZI1456);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_indir_exp ( (ZI1456) ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1517);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1563) = make_exp_stmt ( (ZI1517) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1563) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 4:
	{
	    IDENTIFIER ZI1470;
	    EXP ZI1555;
	    EXP ZI493;

	    {

    ZI1470 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1471 (&ZI1470, &ZI1555);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1555) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 146:
	{
	    TYPE ZI414;
	    EXP ZI1462;
	    int ZI551;
	    EXP ZI1273;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1527;
	    int ZI670;
	    EXP ZI1573;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    ZR552 (&ZI414, &ZI1462, &ZI551);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1273) = make_static_cast_exp ( (ZI414), (ZI1462), (ZI551) ) ;
	    }
	    ZR1240 (ZI1273, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1527);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1573) = make_exp_stmt ( (ZI1527) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1573) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 6:
	{
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI419;
	    EXP ZI1283;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1538;
	    int ZI670;
	    EXP ZI1584;
	    EXP ZI493;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI478 = parse_id_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI419) = check_id ( NULL_nspace, (ZI478), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1283) = make_id_exp ( (ZI419) ) ;
	    }
	    ZR1240 (ZI1283, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1538);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1584) = make_exp_stmt ( (ZI1538) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1584) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 7:
	{
	    IDENTIFIER ZI460;
	    IDENTIFIER ZI419;
	    TYPE ZI1265;
	    BASE_TYPE ZI511;
	    CV_SPEC ZI783;
	    TYPE ZI414;
	    SID_LIST_EXP ZI497;
	    EXP ZI1281;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1539;
	    int ZI670;
	    EXP ZI1585;
	    EXP ZI493;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI460 = parse_type_template ( id, args, 0 ) ;
    crt_templ_qualifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI419) = (ZI460) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, crt_id_qualifier, (ZI1265) ) ;
    COPY_id ( type_name ( (ZI1265) ), (ZI419) ) ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI511) = btype_none ; 
	    }
	    {
 (ZI783) = cv_none ; 
	    }
	    {

    (ZI414) = complete_pre_type ( (ZI511), (ZI1265), (ZI783), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR500 (&ZI497);
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1281) = make_func_cast_exp ( (ZI414), (ZI497) ) ;
	    }
	    ZR1240 (ZI1281, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1539);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1585) = make_exp_stmt ( (ZI1539) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1585) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 148:
	{
	    EXP ZI1276;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1530;
	    int ZI670;
	    EXP ZI1576;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    {

    (ZI1276) = make_this_exp () ;
	    }
	    ZR1240 (ZI1276, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1530);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1576) = make_exp_stmt ( (ZI1530) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1576) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 2:
	{
	    IDENTIFIER ZI1466;
	    EXP ZI1553;
	    EXP ZI493;

	    {

    ZI1466 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1467 (&ZI1466, &ZI1553);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1553) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 152:
	{
	    int ZI450;
	    EXP ZI1270;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1524;
	    int ZI670;
	    EXP ZI1570;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_typeid ; 
	    }
	    ZR553 (ZI450, &ZI1270);
	    ZR1240 (ZI1270, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1524);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1570) = make_exp_stmt ( (ZI1524) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1570) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 329:
	{
	    int ZI450;
	    EXP ZI1269;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1523;
	    int ZI670;
	    EXP ZI1569;
	    EXP ZI493;

	    ADVANCE_LEXER;
	    {
 (ZI450) = lex_vtable ; 
	    }
	    ZR553 (ZI450, &ZI1269);
	    ZR1240 (ZI1269, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1523);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1569) = make_exp_stmt ( (ZI1523) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1569) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 33:
	{
	    EXP ZI1457;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1518;
	    int ZI670;
	    EXP ZI1564;
	    EXP ZI493;

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
	    ZR581 (&ZI1457);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_ref_exp ( (ZI1457), 0 ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1518);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1564) = make_exp_stmt ( (ZI1518) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1564) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 97: case 102: case 106: case 110: case 111:
      case 114: case 115: case 122: case 123: case 127:
      case 156: case 184: case 285: case 298:
	{
	    BASE_TYPE ZI511;
	    TYPE ZI1265;
	    CV_SPEC ZI783;
	    TYPE ZI414;
	    SID_LIST_EXP ZI497;
	    EXP ZI1280;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1533;
	    int ZI670;
	    EXP ZI1579;
	    EXP ZI493;

	    ZR509 (&ZI511);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1265) = NULL_type ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI783) = cv_none ; 
	    }
	    {

    (ZI414) = complete_pre_type ( (ZI511), (ZI1265), (ZI783), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR500 (&ZI497);
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1280) = make_func_cast_exp ( (ZI414), (ZI497) ) ;
	    }
	    ZR1240 (ZI1280, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1533);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1579) = make_exp_stmt ( (ZI1533) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1579) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 288: case 322:
	{
	    EXP ZI1544;
	    EXP ZI493;

	    ZR776 (&ZI1544);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1544) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 96: case 100: case 222:
	{
	    EXP ZI1550;
	    EXP ZI493;

	    ZR662 ();
	    ZR1440 (&ZI1550);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1550) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 297: case 323:
	{
	    EXP ZI1434;
	    EXP ZI1509;
	    int ZI670;
	    EXP ZI1546;
	    EXP ZI493;

	    ZR643 (&ZI1434);
	    ZR1436 (&ZI1434, &ZI1509);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1546) = make_exp_stmt ( (ZI1509) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1546) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 101: case 107: case 125:
	{
	    EXP ZI1541;
	    EXP ZI493;

	    ZR738 (&ZI1541);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1541) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 95: case 99: case 108: case 113:
	{
	    EXP ZI1542;
	    EXP ZI493;

	    ZR752 (&ZI1542);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1542) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 17: case 18: case 19: case 20: case 21:
      case 22: case 135: case 150:
	{
	    EXP ZI1275;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1529;
	    int ZI670;
	    EXP ZI1575;
	    EXP ZI493;

	    ZR437 (&ZI1275);
	    ZR1240 (ZI1275, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1529);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1575) = make_exp_stmt ( (ZI1529) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1575) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 62:
	{
	    EXP ZI1458;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1519;
	    int ZI670;
	    EXP ZI1565;
	    EXP ZI493;

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
	    ZR581 (&ZI1458);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_not_exp ( (ZI1458) ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1519);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1565) = make_exp_stmt ( (ZI1519) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1565) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 64:
	{
	    EXP ZI493;

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

    COPY_int ( exp_sequence_block ( (ZI558) ), 2 ) ;
	    }
	    ZR676 (ZI558, &ZI493);
	    {
		if ((CURRENT_TERMINAL) == 354) {
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

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 141:
	{
	    IDENTIFIER ZI478;
	    IDENTIFIER ZI419;
	    EXP ZI1283;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1536;
	    int ZI670;
	    EXP ZI1582;
	    EXP ZI493;

	    parse_operator (&ZI478);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI419) = check_id ( NULL_nspace, (ZI478), 0 ) ;
    crt_id_qualifier = qual_none ;
    last_namespace = crt_namespace ;
	    }
	    {

    (ZI1283) = make_id_exp ( (ZI419) ) ;
	    }
	    ZR1240 (ZI1283, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1536);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1582) = make_exp_stmt ( (ZI1536) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1582) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 26: case 109: case 119:
	{
	    EXP ZI1540;
	    EXP ZI493;

	    ZR713 (&ZI1540);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1540) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 149:
	{
	    EXP ZI1287;
	    EXP ZI1511;
	    int ZI670;
	    EXP ZI1549;
	    EXP ZI493;

	    ZR635 (&ZI1287);
	    ZR1289 (&ZI1287, &ZI1511);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1549) = make_exp_stmt ( (ZI1511) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1549) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 151:
	{
	    EXP ZI1543;
	    EXP ZI493;

	    ZR771 (&ZI1543);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1543) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 131: case 140:
	{
	    int ZI456;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1535;
	    int ZI670;
	    EXP ZI1581;
	    EXP ZI493;

	    {
 (ZI456) = 0 ; 
	    }
	    ZR1430 (&ZI456, &ZI1452);
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1535);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1581) = make_exp_stmt ( (ZI1535) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1581) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      case 43: case 59: case 69: case 85:
	{
	    int ZI450;
	    EXP ZI1459;
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
	    EXP ZI1442;
	    EXP ZI1441;
	    EXP ZI1263;
	    EXP ZI1287;
	    EXP ZI1520;
	    int ZI670;
	    EXP ZI1566;
	    EXP ZI493;

	    {
 (ZI450) = crt_lex_token ; 
	    }
	    ZR596 ();
	    ZR581 (&ZI1459);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1452) = make_uminus_exp ( (ZI450), (ZI1459) ) ;
	    }
	    ZR1236 (ZI1452, &ZI1451);
	    ZR1232 (ZI1451, &ZI1450);
	    ZR1228 (ZI1450, &ZI1449);
	    ZR1224 (ZI1449, &ZI1448);
	    ZR1220 (ZI1448, &ZI1447);
	    ZR1216 (ZI1447, &ZI1446);
	    ZR1212 (ZI1446, &ZI1445);
	    ZR1208 (ZI1445, &ZI1444);
	    ZR1204 (ZI1444, &ZI1443);
	    ZR1200 (ZI1443, &ZI1442);
	    ZR1196 (ZI1442, &ZI1441);
	    ZR1192 (ZI1441, &ZI1263);
	    ZR1264 (&ZI1263, &ZI1287);
	    ZR1289 (&ZI1287, &ZI1520);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI670) = unreached_code ;
    if ( (ZI670) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI1566) = make_exp_stmt ( (ZI1520) ) ;
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

    (ZI493) = add_compound_stmt ( (ZI558), (ZI1566) ) ;
	    }
	    {

    (ZI431) = end_compound_stmt ( (ZI493) ) ;
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

    (ZI431) = end_compound_stmt ( (ZI558) ) ;
	}
	{

    RESCAN_LEXER ;
	}
    }
  ZL0:;
    *ZO431 = ZI431;
}

/* END OF FILE */
