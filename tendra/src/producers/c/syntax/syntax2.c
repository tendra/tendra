/*
 * Automatically generated from the files:
 *	/u/g/release/Source/src/producers/c/syntax/syntax.sid
 * and
 *	/u/g/release/Source/src/producers/c/syntax/syntax.act
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
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
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



void
ZR623 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI416;
	SID_LIST_EXP ZI420;

	switch (CURRENT_TERMINAL) {
	  case 126:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 65:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 19:
		{
		    {

    ZI416 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 20:
		{
		    {

    ZI416 = crt_token->pp_data.exp ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	ZR624 (&ZI420);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI404) = make_asm ( (ZI416), (ZI420) ) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 39:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR396 ();
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO404 = ZI404;
}

void
ZR766 PROTO_N ((ZI420, ZO395, ZO399))
  PROTO_T (TYPE ZI420 X TYPE *ZO395 X IDENTIFIER *ZO399)
{
    TYPE ZI395;
    IDENTIFIER ZI399;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI1047;
	TYPE ZI1048;
	TYPE ZI423;

	{

    /* Resolve parameter declarators from type names */
    (ZI0) = predict_param () ;
	}
	if (!ZI0)
	    goto ZL2;
	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    {

    ZI1047 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {

    ZI1047 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    {

    ZI1047 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    (ZI1048) = NULL_type ;
	}
	{

    IDENTIFIER pid = underlying_id ( (ZI1047) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	}
	ZR856 (ZI1048, ZI1047, &ZI423, &ZI399);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI395) = ( IS_NULL_type ( (ZI423) ) ? (ZI420) : inject_pre_type ( (ZI423), (ZI420), 1 ) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI423;

	    ADVANCE_LEXER;
	    ZR1046 (&ZI423, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI423) ) ? (ZI420) : inject_pre_type ( (ZI423), (ZI420), 1 ) ) ;
	    }
	}
	break;
      case 331:
	{
	    IDENTIFIER ZI1045;
	    int ZI747;
	    TYPE ZI1051;
	    IDENTIFIER ZI1052;
	    TYPE ZI423;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1045) = NULL_id ;
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1045) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR758 (&ZI747);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1051) = make_func_type ( NULL_type, ( (ZI747) | FUNC_WEAK ), cv_c, empty_type_set ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	    {

    HASHID nm = lookup_anon () ;
    (ZI1052) = DEREF_id ( hashid_id ( nm ) ) ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI1052) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR856 (ZI1051, ZI1052, &ZI423, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI423) ) ? (ZI420) : inject_pre_type ( (ZI423), (ZI420), 1 ) ) ;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI404;
	    TYPE ZI1049;
	    IDENTIFIER ZI1050;
	    TYPE ZI423;

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
	    ZR757 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI404) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI1049) ) ;
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

    HASHID nm = lookup_anon () ;
    (ZI1050) = DEREF_id ( hashid_id ( nm ) ) ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI1050) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR856 (ZI1049, ZI1050, &ZI423, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI423) ) ? (ZI420) : inject_pre_type ( (ZI423), (ZI420), 1 ) ) ;
	    }
	}
	break;
      case 78:
	{
	    TYPE ZI1053;
	    TYPE ZI1054;
	    TYPE ZI423;

	    ZR731 (&ZI1053);
	    ZR764 (&ZI1054, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI423) = ( IS_NULL_type ( (ZI1054) ) ? (ZI1053) : inject_pre_type ( (ZI1054), (ZI1053), 0 ) ) ;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI423) ) ? (ZI420) : inject_pre_type ( (ZI423), (ZI420), 1 ) ) ;
	    }
	}
	break;
      default:
	{
	    TYPE ZI423;

	    {

    (ZI423) = NULL_type ;
	    }
	    {

    HASHID nm = lookup_anon () ;
    (ZI399) = DEREF_id ( hashid_id ( nm ) ) ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI399) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI423) ) ? (ZI420) : inject_pre_type ( (ZI423), (ZI420), 1 ) ) ;
	    }
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO395 = ZI395;
    *ZO399 = ZI399;
}

void
ZR503 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI948;

	ZR501 (&ZI948);
	ZR950 (&ZI948, &ZI404);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO404 = ZI404;
}

void
parse_type PROTO_N ((ZO395))
  PROTO_T (TYPE *ZO395)
{
    TYPE ZI395;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	parse_tok_type (&ZI395);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    object_type ( (ZI395), null_tag ) ;
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

    (ZI395) = NULL_type ;
	}
    }
  ZL0:;
    *ZO395 = ZI395;
}

void
ZR836 PROTO_N ((ZI448, ZI568, ZO847, ZO848))
  PROTO_T (OFFSET ZI448 X TYPE ZI568 X OFFSET *ZO847 X TYPE *ZO848)
{
    OFFSET ZI847;
    TYPE ZI848;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_836:;
    {
	OFFSET ZI416;
	TYPE ZI395;

	ZR835 (ZI448, ZI568, &ZI416, &ZI395);
	{
	    switch (CURRENT_TERMINAL) {
	      case 46: case 66:
		{
		    ZI448 = ZI416;
		    ZI568 = ZI395;
		    goto ZL2_836;
		}
		/*UNREACHED*/
	      default:
		{
		    ZI847 = ZI416;
		    ZI848 = ZI395;
		}
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO847 = ZI847;
    *ZO848 = ZI848;
}

void
ZR805 PROTO_N ((ZO873))
  PROTO_T (EXP *ZO873)
{
    EXP ZI873;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI467;
	EXP ZI420;

	switch (CURRENT_TERMINAL) {
	  case 26:
	    {

    ZI467 = crt_token->pp_data.exp ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    EXP c = crt_hash_cond ;
    crt_hash_cond = make_if_cond ( (ZI467), c ) ;
    (ZI420) = c ;
	}
	{

    target_decl ( lex_if, (ZI467) ) ;
	}
	ZR804 ();
	ZR874 (ZI420, &ZI873);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO873 = ZI873;
}

void
ZR1055 PROTO_N ((ZI399, ZO395))
  PROTO_T (IDENTIFIER *ZI399 X TYPE *ZO395)
{
    TYPE ZI395;

    switch (CURRENT_TERMINAL) {
      default:
	{
	    BASE_TYPE ZI669;

	    {
 (ZI669) = btype_enum ; 
	    }
	    {

    MAKE_type_pre ( cv_none, (ZI669), qual_none, (ZI395) ) ;
    COPY_id ( type_name ( (ZI395) ), (*ZI399) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
    }
    have_type_specifier = 1 ;
	    }
	}
	break;
      case 64:
	{
	    IDENTIFIER ZI420;
	    IDENTIFIER ZI672;

	    {

    (ZI420) = begin_enum_defn ( (*ZI399), NULL_type ) ;
    no_type_defns++ ;
	    }
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
	    ZR683 (&ZI420);
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

    (ZI672) = end_enum_defn ( (ZI420) ) ;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZI395) ) ;
    COPY_id ( type_name ( (ZI395) ), (ZI672) ) ;
    have_type_specifier = 1 ;
	    }
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
    *ZO395 = ZI395;
}

void
ZR657 PROTO_N ((ZO395))
  PROTO_T (TYPE *ZO395)
{
    TYPE ZI395;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 104:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 1: case 2: case 4:
		{
		    IDENTIFIER ZI399;

		    {
			switch (CURRENT_TERMINAL) {
			  case 1:
			    {
				{

    ZI399 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 4:
			    {
				{

    ZI399 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  case 2:
			    {
				{

    ZI399 = crt_token->pp_data.id.use ;
				}
				ADVANCE_LEXER;
			    }
			    break;
			  default:
			    goto ZL1;
			}
		    }
		    ZR1055 (&ZI399, &ZI395);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 64:
		{
		    IDENTIFIER ZI399;
		    IDENTIFIER ZI420;
		    IDENTIFIER ZI672;

		    {

    HASHID nm = lookup_anon () ;
    (ZI399) = DEREF_id ( hashid_id ( nm ) ) ;
		    }
		    {

    (ZI420) = begin_enum_defn ( (ZI399), NULL_type ) ;
    no_type_defns++ ;
		    }
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
		    ZR683 (&ZI420);
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

    (ZI672) = end_enum_defn ( (ZI420) ) ;
		    }
		    {

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZI395) ) ;
    COPY_id ( type_name ( (ZI395) ), (ZI672) ) ;
    have_type_specifier = 1 ;
		    }
		}
		break;
	      default:
		goto ZL1;
	    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO395 = ZI395;
}

void
ZR742 PROTO_N ((ZO395, ZO399))
  PROTO_T (TYPE *ZO395 X IDENTIFIER *ZO399)
{
    TYPE ZI395;
    IDENTIFIER ZI399;

    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 4: case 65:
	{
	    ZR751 (&ZI395, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    TYPE ZI420;
	    TYPE ZI423;

	    ZR731 (&ZI420);
	    ZR742 (&ZI423, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI423) ) ? (ZI420) : inject_pre_type ( (ZI423), (ZI420), 0 ) ) ;
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
    *ZO395 = ZI395;
    *ZO399 = ZI399;
}

void
ZR482 PROTO_N ((ZO909))
  PROTO_T (EXP *ZO909)
{
    EXP ZI909;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI404;

	ZR479 (&ZI404);
	ZR910 (ZI404, &ZI909);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO909 = ZI909;
}

void
ZR599 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI416;
	EXP ZI448;

	ZR615 (&ZI416);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI448) = bind_temporary ( (ZI416) ) ;
	}
	{

    MAKE_exp_location ( type_void, crt_loc, (ZI448), (ZI404) ) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 77:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO404 = ZI404;
}

void
ZR678 PROTO_N ((ZI404))
  PROTO_T (IDENTIFIER ZI404)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI399;
	EXP ZI467;

	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    {

    ZI399 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {

    ZI399 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    {

    ZI399 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    IDENTIFIER pid = underlying_id ( (ZI399) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 36:
		{
		    ADVANCE_LEXER;
		    ZR518 (&ZI467);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZI467) = NULL_exp ;
		    }
		}
		break;
	    }
	}
	{

    IGNORE make_enumerator ( (ZI404), (ZI399), (ZI467) ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR752 PROTO_N ((ZI420, ZO395, ZO399))
  PROTO_T (TYPE ZI420 X TYPE *ZO395 X IDENTIFIER *ZO399)
{
    TYPE ZI395;
    IDENTIFIER ZI399;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI423;

	ZR742 (&ZI423, &ZI399);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI395) = ( IS_NULL_type ( (ZI423) ) ? (ZI420) : inject_pre_type ( (ZI423), (ZI420), 1 ) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO395 = ZI395;
    *ZO399 = ZI399;
}

void
ZR792 PROTO_N ((ZI547, ZO404))
  PROTO_T (IDENTIFIER ZI547 X EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    ADVANCE_LEXER;
	    ZR788 (ZI547, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI404) = NULL_exp ;
	    }
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
    *ZO404 = ZI404;
}

void
parse_file PROTO_N ((ZI395, ZI605))
  PROTO_T (TYPE ZI395 X DECL_SPEC ZI605)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI937;
	TYPE ZI938;
	CV_SPEC ZI939;
	DECL_SPEC ZI940;
	BASE_TYPE ZI941;
	TYPE ZI942;
	CV_SPEC ZI943;
	DECL_SPEC ZI944;
	EXP ZI404;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR714 (&ZI937, &ZI938, &ZI939, &ZI940);
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
	ZR724 (&ZI937, &ZI938, &ZI939, &ZI940, &ZI941, &ZI942, &ZI943, &ZI944);
	ZR945 (&ZI941, &ZI942, &ZI943, &ZI944, &ZI404);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    external_declaration ( (ZI404), 1 ) ;
	}
	ZR803 ();
	switch (CURRENT_TERMINAL) {
	  case 32:
	    break;
	  case 354:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 32:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 77:
	{
	    ADVANCE_LEXER;
	    {

    report ( crt_loc, ERR_dcl_dcl_semicolon () ) ;
	    }
	    ZR803 ();
	    switch (CURRENT_TERMINAL) {
	      case 32:
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 126:
	{
	    EXP ZI404;

	    ZR623 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    external_declaration ( (ZI404), 1 ) ;
	    }
	    ZR803 ();
	    switch (CURRENT_TERMINAL) {
	      case 32:
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 26: case 30:
	{
	    ZR806 ();
	    ZR803 ();
	    switch (CURRENT_TERMINAL) {
	      case 32:
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 1: case 2: case 4: case 65: case 78:
	{
	    BASE_TYPE ZI658;
	    TYPE ZI689;
	    CV_SPEC ZI630;
	    DECL_SPEC ZI716;
	    TYPE ZI946;
	    DECL_SPEC ZI947;
	    TYPE ZI568;
	    IDENTIFIER ZI399;
	    EXP ZI404;

	    {
 (ZI658) = btype_none ; 
	    }
	    {

    (ZI689) = NULL_type ;
	    }
	    {
 (ZI630) = cv_none ; 
	    }
	    {
 (ZI716) = dspec_none ; 
	    }
	    {

    /* Complete a declaration specifier and a type */
    (ZI947) = complete_dspec ( (ZI716), (ZI658), (ZI689), (ZI630) ) ;
    (ZI946) = complete_pre_type ( (ZI658), (ZI689), (ZI630), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    ZR752 (ZI946, &ZI568, &ZI399);
	    ZR819 (&ZI658, &ZI946, &ZI947, &ZI568, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = NULL_exp ;
	    }
	    {

    external_declaration ( (ZI404), 1 ) ;
	    }
	    ZR803 ();
	    switch (CURRENT_TERMINAL) {
	      case 32:
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    /* Unrecoverable syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    err = concat_error ( err, ERR_lex_abort () ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
    }
  ZL0:;
}

void
parse_offset PROTO_N ((ZI448, ZI568, ZO416, ZO395))
  PROTO_T (OFFSET ZI448 X TYPE ZI568 X OFFSET *ZO416 X TYPE *ZO395)
{
    OFFSET ZI416;
    TYPE ZI395;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	OFFSET ZI467;
	TYPE ZI837;

	ZR834 (ZI448, ZI568, &ZI467, &ZI837);
	{
	    switch (CURRENT_TERMINAL) {
	      case 46: case 66:
		{
		    ZR836 (ZI467, ZI837, &ZI416, &ZI395);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    ZI416 = ZI467;
		    ZI395 = ZI837;
		}
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	    }
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
	ZI416 = ZI448;
	ZI395 = ZI568;
    }
  ZL0:;
    *ZO416 = ZI416;
    *ZO395 = ZI395;
}

void
ZR1059 PROTO_N ((ZI1057, ZO395))
  PROTO_T (TYPE *ZI1057 X TYPE *ZO395)
{
    TYPE ZI395;

    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 78: case 331:
	{
	    TYPE ZI423;

	    ZR753 (&ZI423);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI423) ) ? (*ZI1057) : inject_pre_type ( (ZI423), (*ZI1057), 0 ) ) ;
	    }
	}
	break;
      default:
	{
	    ZI395 = *ZI1057;
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
    *ZO395 = ZI395;
}

void
parse_nat PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	ZR518 (&ZI404);
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

    (ZI404) = NULL_exp ;
	}
    }
  ZL0:;
    *ZO404 = ZI404;
}

void
ZR1060 PROTO_N ((ZO859))
  PROTO_T (TYPE *ZO859)
{
    TYPE ZI859;

    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 78: case 331:
	{
	    TYPE ZI395;

	    ZR753 (&ZI395);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( IS_NULL_type ( (ZI395) ) ) {
	report ( crt_loc, ERR_dcl_meaning_paren () ) ;
    }
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR860 (ZI395, &ZI859);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 2: case 25: case 39: case 47: case 94:
      case 97: case 98: case 102: case 104: case 105:
      case 106: case 110: case 111: case 112: case 114:
      case 115: case 117: case 118: case 120: case 121:
      case 122: case 123: case 124: case 137: case 156:
      case 184: case 285: case 298:
	{
	    IDENTIFIER ZI399;
	    TYPE ZI568;
	    TYPE ZI395;

	    {

    (ZI399) = NULL_id ;
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI399) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR755 (&ZI568);
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
	    ZI395 = ZI568;
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	    ZR860 (ZI395, &ZI859);
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
    *ZO859 = ZI859;
}

void
ZR933 PROTO_N ((ZI927, ZI928, ZI929, ZO930, ZO931, ZO932))
  PROTO_T (EXP ZI927 X EXP ZI928 X int ZI929 X EXP *ZO930 X EXP *ZO931 X int *ZO932)
{
    EXP ZI930;
    EXP ZI931;
    int ZI932;

  ZL2_933:;
    switch (CURRENT_TERMINAL) {
      case 27:
	{
	    EXP ZI420;
	    int ZI537;
	    EXP ZI467;
	    int ZI568;
	    EXP ZI448;
	    EXP ZI404;

	    ZI420 = ZI928;
	    ZI537 = ZI929;
	    {

    ZI467 = crt_token->pp_data.exp ;
	    }
	    ADVANCE_LEXER;
	    {

    EXP c = make_else_cond ( crt_hash_cond ) ;
    crt_hash_cond = make_if_cond ( (ZI467), c ) ;
	    }
	    {

    (ZI568) = unreached_code ;
    if ( (ZI568) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR551 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 unreached_prev = (ZI537) ; 
	    }
	    {

    (ZI404) = cont_hash_if_stmt ( (ZI927), (ZI467), (ZI448) ) ;
	    }
	    ZI927 = ZI404;
	    ZI928 = ZI420;
	    ZI929 = ZI537;
	    goto ZL2_933;
	}
	/*UNREACHED*/
      default:
	{
	    ZI930 = ZI927;
	    ZI931 = ZI928;
	    ZI932 = ZI929;
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
    *ZO930 = ZI930;
    *ZO931 = ZI931;
    *ZO932 = ZI932;
}

void
ZR516 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	ZR419 (&ZI404);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO404 = ZI404;
}

void
parse_param PROTO_N ((ZI568, ZI420, ZO547))
  PROTO_T (TYPE ZI568 X int ZI420 X IDENTIFIER *ZO547)
{
    IDENTIFIER ZI547;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	ZR770 (&ZI547);
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

    (ZI547) = NULL_id ;
	}
    }
  ZL0:;
    *ZO547 = ZI547;
}

void
ZR687 PROTO_N ((ZO658, ZO395, ZO630))
  PROTO_T (BASE_TYPE *ZO658 X TYPE *ZO395 X CV_SPEC *ZO630)
{
    BASE_TYPE ZI658;
    TYPE ZI395;
    CV_SPEC ZI630;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI688;
	TYPE ZI689;
	CV_SPEC ZI690;

	ZR686 (&ZI688, &ZI689, &ZI690);
	{
	    switch (CURRENT_TERMINAL) {
	      case 2: case 25: case 97: case 98: case 102:
	      case 104: case 106: case 110: case 111: case 114:
	      case 115: case 118: case 121: case 122: case 123:
	      case 124: case 156: case 184: case 285: case 298:
		{
		    BASE_TYPE ZI692;
		    TYPE ZI693;
		    CV_SPEC ZI694;

		    ZR687 (&ZI692, &ZI693, &ZI694);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    if ( (ZI688) & (ZI692) ) {
	(ZI658) = join_pre_types ( (ZI688), (ZI692) ) ;
    } else {
	(ZI658) = ( (ZI688) | (ZI692) ) ;
    }
		    }
		    {

    /* Join two partial types */
    if ( IS_NULL_type ( (ZI689) ) ) {
	(ZI395) = (ZI693) ;
    } else if ( IS_NULL_type ( (ZI693) ) ) {
	(ZI395) = (ZI689) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (ZI689), (ZI693) ) ) ;
	(ZI395) = (ZI693) ;
    }
		    }
		    {

    CV_SPEC c = ( (ZI690) & (ZI694) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI630) = ( (ZI690) | (ZI694) ) ;
		    }
		}
		break;
	      default:
		{
		    ZI658 = ZI688;
		    ZI395 = ZI689;
		    ZI630 = ZI690;
		}
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO658 = ZI658;
    *ZO395 = ZI395;
    *ZO630 = ZI630;
}

void
parse_func PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	ZR552 (&ZI404);
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

    (ZI404) = NULL_exp ;
	}
    }
  ZL0:;
    *ZO404 = ZI404;
}

void
ZR753 PROTO_N ((ZO395))
  PROTO_T (TYPE *ZO395)
{
    TYPE ZI395;

    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 331:
	{
	    ZR759 (&ZI395);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    TYPE ZI1057;

	    ZR731 (&ZI1057);
	    ZR1059 (&ZI1057, &ZI395);
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
    *ZO395 = ZI395;
}

void
ZR683 PROTO_N ((ZI420))
  PROTO_T (IDENTIFIER *ZI420)
{
    switch (CURRENT_TERMINAL) {
      case 1: case 2: case 4:
	{
	    ZR680 (*ZI420);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 354:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR709 PROTO_N ((ZO605))
  PROTO_T (DECL_SPEC *ZO605)
{
    DECL_SPEC ZI605;

    switch (CURRENT_TERMINAL) {
      case 94:
	{
	    ADVANCE_LEXER;
	    {
 (ZI605) = dspec_auto ; 
	    }
	}
	break;
      case 105:
	{
	    ADVANCE_LEXER;
	    {
 (ZI605) = dspec_extern ; 
	    }
	}
	break;
      case 137:
	{
	    ADVANCE_LEXER;
	    {
 (ZI605) = dspec_inline ; 
	    }
	}
	break;
      case 112:
	{
	    ADVANCE_LEXER;
	    {
 (ZI605) = dspec_register ; 
	    }
	}
	break;
      case 117:
	{
	    ADVANCE_LEXER;
	    {
 (ZI605) = dspec_static ; 
	    }
	}
	break;
      case 120:
	{
	    ADVANCE_LEXER;
	    {
 (ZI605) = dspec_typedef ; 
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
    *ZO605 = ZI605;
}

void
ZR744 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI399;

	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    {

    ZI399 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {

    ZI399 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    IDENTIFIER pid = underlying_id ( (ZI399) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	}
	{

    IGNORE weak_param_decl ( (ZI399) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	}
	ZR778 ();
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
parse_id PROTO_N ((ZO399))
  PROTO_T (IDENTIFIER *ZO399)
{
    IDENTIFIER ZI399;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    {

    ZI399 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {

    ZI399 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    {

    ZI399 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
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

    (ZI399) = NULL_id ;
	}
    }
  ZL0:;
    *ZO399 = ZI399;
}

void
ZR813 PROTO_N ((ZI658, ZI689, ZI630, ZI716))
  PROTO_T (BASE_TYPE *ZI658 X TYPE *ZI689 X CV_SPEC *ZI630 X DECL_SPEC *ZI716)
{
    switch (CURRENT_TERMINAL) {
      default:
	{
	    {

    IGNORE empty_decl ( (*ZI716), NULL_type, (*ZI658), (*ZI689), (*ZI630), last_lex_token, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
	    }
	}
	break;
      case 1: case 2: case 4: case 65: case 78:
	{
	    TYPE ZI395;
	    DECL_SPEC ZI605;

	    {

    /* Complete a declaration specifier and a type */
    (ZI605) = complete_dspec ( (*ZI716), (*ZI658), (*ZI689), (*ZI630) ) ;
    (ZI395) = complete_pre_type ( (*ZI658), (*ZI689), (*ZI630), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    ZR797 (ZI605, *ZI658, ZI395);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 354:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR459 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 170:
	{
	    int ZI460;

	    ADVANCE_LEXER;
	    {
 (ZI460) = lex_alignof ; 
	    }
	    ZR461 (ZI460, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 23:
	{
	    EXP ZI962;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI962 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR922 (ZI962, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 205:
	{
	    EXP ZI416;

	    ADVANCE_LEXER;
	    ZR459 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_cast_exp ( type_void, (ZI416), 0 ) ;
	    }
	}
	break;
      case 209:
	{
	    EXP ZI962;

	    ADVANCE_LEXER;
	    {

    (ZI962) = make_ellipsis_exp () ;
	    }
	    ZR922 (ZI962, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1:
	{
	    IDENTIFIER ZI399;
	    EXP ZI962;

	    {

    ZI399 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI962) = make_id_exp ( (ZI399) ) ;
	    }
	    ZR922 (ZI962, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 61:
	{
	    EXP ZI416;

	    ADVANCE_LEXER;
	    ZR458 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_prefix_exp ( lex_minus_Hminus, (ZI416) ) ;
	    }
	}
	break;
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR963 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 71:
	{
	    EXP ZI416;

	    ADVANCE_LEXER;
	    ZR458 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_prefix_exp ( lex_plus_Hplus, (ZI416) ) ;
	    }
	}
	break;
      case 116:
	{
	    int ZI460;

	    ADVANCE_LEXER;
	    {
 (ZI460) = lex_sizeof ; 
	    }
	    ZR461 (ZI460, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    EXP ZI416;

	    ADVANCE_LEXER;
	    ZR459 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_indir_exp ( (ZI416) ) ;
	    }
	}
	break;
      case 33:
	{
	    EXP ZI416;

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
	    ZR459 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_ref_exp ( (ZI416), 0 ) ;
	    }
	}
	break;
      case 17: case 18: case 19: case 20: case 21:
      case 22:
	{
	    EXP ZI962;

	    ZR409 (&ZI962);
	    ZR922 (ZI962, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 62:
	{
	    EXP ZI416;

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
	    ZR459 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_not_exp ( (ZI416) ) ;
	    }
	}
	break;
      case 43: case 59: case 69: case 85:
	{
	    int ZI460;
	    EXP ZI416;

	    {
 (ZI460) = crt_lex_token ; 
	    }
	    ZR469 ();
	    ZR459 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_uminus_exp ( (ZI460), (ZI416) ) ;
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
    *ZO404 = ZI404;
}

void
ZR660 PROTO_N ((ZO658, ZO395))
  PROTO_T (BASE_TYPE *ZO658 X TYPE *ZO395)
{
    BASE_TYPE ZI658;
    TYPE ZI395;

    switch (CURRENT_TERMINAL) {
      case 25:
	{
	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI395 = parse_type_token ( id, args ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_type_specifier = 1 ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {
 (ZI658) = btype_none ; 
	    }
	}
	break;
      case 2:
	{
	    IDENTIFIER ZI399;

	    {

    ZI399 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZI395) ) ;
    COPY_id ( type_name ( (ZI395) ), (ZI399) ) ;
    have_type_specifier = 1 ;
	    }
	    {
 (ZI658) = btype_none ; 
	    }
	}
	break;
      case 97: case 102: case 106: case 110: case 111:
      case 114: case 115: case 122: case 123: case 156:
      case 184: case 285: case 298:
	{
	    ZR659 (&ZI658);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = NULL_type ;
    have_type_specifier = 1 ;
	    }
	}
	break;
      case 118: case 121:
	{
	    ZR656 (&ZI395);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI658) = btype_none ; 
	    }
	}
	break;
      case 104:
	{
	    ZR657 (&ZI395);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI658) = btype_none ; 
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
    *ZO658 = ZI658;
    *ZO395 = ZI395;
}

void
ZR760 PROTO_N ((ZI420, ZO395))
  PROTO_T (TYPE ZI420 X TYPE *ZO395)
{
    TYPE ZI395;

    switch (CURRENT_TERMINAL) {
      case 65: case 66: case 78: case 331:
	{
	    TYPE ZI423;

	    ZR753 (&ZI423);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI423) ) ? (ZI420) : inject_pre_type ( (ZI423), (ZI420), 1 ) ) ;
	    }
	}
	break;
      default:
	{
	    ZI395 = ZI420;
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
    *ZO395 = ZI395;
}

void
ZR394 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 65:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	int ZI395;

	{
 (ZI395) = lex_open_Hround ; 
	}
	{

    /* Expected symbol */
    int p = primary_form ( crt_lex_token ) ;
    if ( p != (ZI395) ) report ( crt_loc, ERR_lex_expect ( (ZI395) ) ) ;
	}
    }
}

void
ZR1071 PROTO_N ((ZI460, ZI462, ZI463, ZO467))
  PROTO_T (int *ZI460 X int *ZI462 X int *ZI463 X EXP *ZO467)
{
    EXP ZI467;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI395;
	int ZI466;
	EXP ZI416;

	{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 1 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR444 (&ZI395, &ZI466);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI416) = NULL_exp ;
	}
	{

    (ZI467) = make_sizeof_exp ( (ZI395), (ZI416), (ZI466), (*ZI460) ) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 39:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 205: case 209: case 297: case 323: case 345:
	{
	    EXP ZI1070;
	    EXP ZI404;
	    EXP ZI416;
	    int ZI465;
	    int ZI466;
	    TYPE ZI395;

	    {

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
	    }
	    ZR414 (&ZI1070);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_paren_exp ( (ZI1070) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR922 (ZI404, &ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI465) = no_side_effects - (*ZI462) ;
	    }
	    {

    (ZI466) = no_type_defns - (*ZI463) ;
	    }
	    {

    (ZI395) = typeof_exp ( &(ZI416), (ZI465), (*ZI460) ) ;
	    }
	    {

    (ZI467) = make_sizeof_exp ( (ZI395), (ZI416), (ZI466), (*ZI460) ) ;
	    }
	}
	break;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO467 = ZI467;
}

void
ZR680 PROTO_N ((ZI404))
  PROTO_T (IDENTIFIER ZI404)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_680:;
    {
	ZR678 (ZI404);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    {
			switch (CURRENT_TERMINAL) {
			  case 42:
			    {
				ADVANCE_LEXER;
				{

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
				}
				goto ZL2_680;
			    }
			    /*UNREACHED*/
			  case 1: case 2: case 4:
			    {
				goto ZL2_680;
			    }
			    /*UNREACHED*/
			  default:
			    {
				{

    /* Extra comma at the end of a list */
    report ( crt_loc, ERR_lex_extra_comma () ) ;
				}
			    }
			    break;
			}
		    }
		}
		break;
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
ZR1072 PROTO_N ((ZI547, ZO423))
  PROTO_T (IDENTIFIER *ZI547 X SID_LIST_EXP *ZO423)
{
    SID_LIST_EXP ZI423;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 64: case 65:
      case 69: case 71: case 78: case 85: case 116:
      case 170: case 205: case 209:
	{
	    ZR789 (*ZI547, &ZI423);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI423) = NULL_list ( EXP ) ;
	    }
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
    *ZO423 = ZI423;
}

void
ZR945 PROTO_N ((ZI941, ZI942, ZI943, ZI944, ZO404))
  PROTO_T (BASE_TYPE *ZI941 X TYPE *ZI942 X CV_SPEC *ZI943 X DECL_SPEC *ZI944 X EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    {

    IGNORE empty_decl ( (*ZI944), NULL_type, (*ZI941), (*ZI942), (*ZI943), last_lex_token, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI404) = NULL_exp ;
	    }
	}
	break;
      case 1: case 2: case 4: case 65: case 78:
	{
	    TYPE ZI395;
	    DECL_SPEC ZI605;
	    TYPE ZI568;
	    IDENTIFIER ZI399;

	    {

    /* Complete a declaration specifier and a type */
    (ZI605) = complete_dspec ( (*ZI944), (*ZI941), (*ZI942), (*ZI943) ) ;
    (ZI395) = complete_pre_type ( (*ZI941), (*ZI942), (*ZI943), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    ZR752 (ZI395, &ZI568, &ZI399);
	    ZR819 (ZI941, &ZI395, &ZI605, &ZI568, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = NULL_exp ;
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
    *ZO404 = ZI404;
}

void
ZR598 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	ZR536 (&ZI404);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO404 = ZI404;
}

void
ZR835 PROTO_N ((ZI448, ZI568, ZO416, ZO395))
  PROTO_T (OFFSET ZI448 X TYPE ZI568 X OFFSET *ZO416 X TYPE *ZO395)
{
    OFFSET ZI416;
    TYPE ZI395;

    switch (CURRENT_TERMINAL) {
      case 46:
	{
	    ADVANCE_LEXER;
	    ZR834 (ZI448, ZI568, &ZI416, &ZI395);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI404;

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
	    ZR518 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    OFFSET off = offset_index ( (ZI568), (ZI404), &(ZI395) ) ;
    (ZI416) = offset_add ( (ZI448), off ) ;
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
    *ZO416 = ZI416;
    *ZO395 = ZI395;
}

void
ZR819 PROTO_N ((ZI658, ZI395, ZI605, ZI568, ZI399))
  PROTO_T (BASE_TYPE *ZI658 X TYPE *ZI395 X DECL_SPEC *ZI605 X TYPE *ZI568 X IDENTIFIER *ZI399)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI547;
	int ZI448;
	EXP ZI416;

	{

    (ZI0) = function_params ( (*ZI568) ) ;
	}
	if (!ZI0)
	    goto ZL2;
	{

    (ZI547) = make_func_decl ( (*ZI605), (*ZI568), (*ZI399), 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	}
	{

    (ZI448) = in_class_defn ;
    in_class_defn = 0 ;
    in_function_defn++ ;
    really_in_function_defn++ ;
    begin_function ( (ZI547) ) ;
	}
	ZR552 (&ZI416);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    IGNORE end_function ( (ZI547), (ZI416) ) ;
    in_class_defn = (ZI448) ;
    in_function_defn-- ;
    really_in_function_defn-- ;
	}
	{

    RESCAN_LEXER ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 36: case 42: case 77:
	{
	    IDENTIFIER ZI547;
	    EXP ZI416;

	    {

    if ( in_weak_param ) {
	(ZI547) = make_param_decl ( (*ZI605), (*ZI568), (*ZI399), CONTEXT_WEAK_PARAM ) ;
    } else if ( type_tag ( (*ZI568) ) == type_func_tag ) {
	check_weak_func ( (*ZI568), 0 ) ;
	(ZI547) = make_func_decl ( (*ZI605), (*ZI568), (*ZI399), 0 ) ;
    } else {
	int def = predict_obj_defn () ;
	(ZI547) = make_object_decl ( (*ZI605), (*ZI568), (*ZI399), def ) ;
    }
    if ( IS_id_type_alias ( (ZI547) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI547) ) ) ;
	bs |= (*ZI658) ;
	COPY_btype ( id_type_alias_rep ( (ZI547) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR792 (ZI547, &ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    int def = init_object ( (ZI547), (ZI416) ) ;
    if ( do_dump ) dump_declare ( (ZI547), &decl_loc, def ) ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 42:
		    {
			ADVANCE_LEXER;
			ZR797 (*ZI605, *ZI658, *ZI395);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  default:
		    break;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 77:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
}

void
ZR458 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 170:
	{
	    int ZI460;

	    ADVANCE_LEXER;
	    {
 (ZI460) = lex_alignof ; 
	    }
	    ZR461 (ZI460, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 61:
	{
	    EXP ZI416;

	    ADVANCE_LEXER;
	    ZR458 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_prefix_exp ( lex_minus_Hminus, (ZI416) ) ;
	    }
	}
	break;
      case 71:
	{
	    EXP ZI416;

	    ADVANCE_LEXER;
	    ZR458 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_prefix_exp ( lex_plus_Hplus, (ZI416) ) ;
	    }
	}
	break;
      case 116:
	{
	    int ZI460;

	    ADVANCE_LEXER;
	    {
 (ZI460) = lex_sizeof ; 
	    }
	    ZR461 (ZI460, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    EXP ZI416;

	    ADVANCE_LEXER;
	    ZR459 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_indir_exp ( (ZI416) ) ;
	    }
	}
	break;
      case 33:
	{
	    EXP ZI416;

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
	    ZR459 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_ref_exp ( (ZI416), 0 ) ;
	    }
	}
	break;
      case 62:
	{
	    EXP ZI416;

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
	    ZR459 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_not_exp ( (ZI416) ) ;
	    }
	}
	break;
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 65: case 209:
	{
	    ZR447 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 43: case 59: case 69: case 85:
	{
	    int ZI460;
	    EXP ZI416;

	    {
 (ZI460) = crt_lex_token ; 
	    }
	    ZR469 ();
	    ZR459 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_uminus_exp ( (ZI460), (ZI416) ) ;
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
    *ZO404 = ZI404;
}

void
ZR485 PROTO_N ((ZO905))
  PROTO_T (EXP *ZO905)
{
    EXP ZI905;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI404;

	ZR482 (&ZI404);
	ZR906 (ZI404, &ZI905);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO905 = ZI905;
}

void
ZR601 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 205: case 209: case 297: case 323: case 345:
	{
	    EXP ZI416;
	    EXP ZI448;

	    ZR414 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI448) = make_exp_stmt ( (ZI416) ) ;
	    }
	    {

    (ZI404) = bind_temporary ( (ZI448) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZI404) = NULL_exp ;
	    }
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
    *ZO404 = ZI404;
}

void
ZR1075 PROTO_N ((ZI1073, ZO404))
  PROTO_T (EXP *ZI1073 X EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 205: case 209: case 297: case 323: case 345:
	{
	    SID_LIST_EXP ZI423;
	    SID_LIST_EXP ZI420;

	    ZR515 (&ZI423);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1073), (ZI423), (ZI420) ) ;
	    }
	    {

    (ZI404) = make_comma_exp ( (ZI420) ) ;
	    }
	}
	break;
      default:
	{
	    ZI404 = *ZI1073;
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
    *ZO404 = ZI404;
}

void
ZR493 PROTO_N ((ZO893))
  PROTO_T (EXP *ZO893)
{
    EXP ZI893;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI404;

	ZR491 (&ZI404);
	ZR894 (ZI404, &ZI893);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO893 = ZI893;
}

void
parse_exp PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	ZR419 (&ZI404);
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

    (ZI404) = NULL_exp ;
	}
    }
  ZL0:;
    *ZO404 = ZI404;
}

void
ZR686 PROTO_N ((ZO658, ZO395, ZO630))
  PROTO_T (BASE_TYPE *ZO658 X TYPE *ZO395 X CV_SPEC *ZO630)
{
    BASE_TYPE ZI658;
    TYPE ZI395;
    CV_SPEC ZI630;

    switch (CURRENT_TERMINAL) {
      case 98: case 124:
	{
	    ZR631 (&ZI630);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI658) = btype_none ; 
	    }
	    {

    (ZI395) = NULL_type ;
	    }
	}
	break;
      case 2: case 25: case 97: case 102: case 104:
      case 106: case 110: case 111: case 114: case 115:
      case 118: case 121: case 122: case 123: case 156:
      case 184: case 285: case 298:
	{
	    ZR660 (&ZI658, &ZI395);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZI630) = cv_none ; 
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
    *ZO658 = ZI658;
    *ZO395 = ZI395;
    *ZO630 = ZI630;
}

void
ZR950 PROTO_N ((ZI948, ZO404))
  PROTO_T (EXP *ZI948 X EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 72:
	{
	    EXP ZI416;
	    EXP ZI448;

	    ADVANCE_LEXER;
	    ZR414 (&ZI416);
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR503 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_cond_exp ( (*ZI948), (ZI416), (ZI448) ) ;
	    }
	}
	break;
      default:
	{
	    ZI404 = *ZI948;
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
    *ZO404 = ZI404;
}

void
ZR1078 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 297:
	{
	    EXP ZI1090;
	    EXP ZI1091;

	    ADVANCE_LEXER;
	    ZR414 (&ZI1090);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1091) = make_set_exp ( (ZI1090) ) ;
	    }
	    ZR1092 (&ZI1091, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 323:
	{
	    EXP ZI1087;
	    EXP ZI1088;

	    ADVANCE_LEXER;
	    ZR414 (&ZI1087);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1088) = make_unused_exp ( (ZI1087) ) ;
	    }
	    ZR1092 (&ZI1088, &ZI404);
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
    *ZO404 = ZI404;
}

void
ZR1079 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 96:
	{
	    EXP ZI467;
	    EXP ZI416;
	    EXP ZI448;

	    ADVANCE_LEXER;
	    ZR518 (&ZI467);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI416) = begin_case_stmt ( (ZI467), 0 ) ;
	    }
	    {

    unreached_fall = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR528 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = end_case_stmt ( (ZI416), (ZI448) ) ;
	    }
	}
	break;
      case 100:
	{
	    EXP ZI416;
	    EXP ZI448;

	    ADVANCE_LEXER;
	    {

    (ZI416) = begin_default_stmt ( 0 ) ;
	    }
	    {

    unreached_fall = 0 ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR528 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = end_default_stmt ( (ZI416), (ZI448) ) ;
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
    *ZO404 = ZI404;
}

void
ZR699 PROTO_N ((ZI688, ZI689, ZI690, ZO658, ZO395, ZO630))
  PROTO_T (BASE_TYPE *ZI688 X TYPE *ZI689 X CV_SPEC *ZI690 X BASE_TYPE *ZO658 X TYPE *ZO395 X CV_SPEC *ZO630)
{
    BASE_TYPE ZI658;
    TYPE ZI395;
    CV_SPEC ZI630;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI1032;
	TYPE ZI1033;
	CV_SPEC ZI1034;
	BASE_TYPE ZI692;
	TYPE ZI693;
	CV_SPEC ZI694;

	{

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR686 (&ZI1032, &ZI1033, &ZI1034);
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
	ZR699 (&ZI1032, &ZI1033, &ZI1034, &ZI692, &ZI693, &ZI694);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( (*ZI688) & (ZI692) ) {
	(ZI658) = join_pre_types ( (*ZI688), (ZI692) ) ;
    } else {
	(ZI658) = ( (*ZI688) | (ZI692) ) ;
    }
	}
	{

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZI689) ) ) {
	(ZI395) = (ZI693) ;
    } else if ( IS_NULL_type ( (ZI693) ) ) {
	(ZI395) = (*ZI689) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZI689), (ZI693) ) ) ;
	(ZI395) = (ZI693) ;
    }
	}
	{

    CV_SPEC c = ( (*ZI690) & (ZI694) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI630) = ( (*ZI690) | (ZI694) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      default:
	{
	    ZI658 = *ZI688;
	    ZI395 = *ZI689;
	    ZI630 = *ZI690;
	}
	break;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO658 = ZI658;
    *ZO395 = ZI395;
    *ZO630 = ZI630;
}

void
parse_stmt PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	ZR528 (&ZI404);
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

    (ZI404) = NULL_exp ;
	}
    }
  ZL0:;
    *ZO404 = ZI404;
}

void
ZR825 PROTO_N ((ZI420, ZI423))
  PROTO_T (TYPE ZI420 X BASE_TYPE ZI423)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_825:;
    {
	ZR824 (ZI420, ZI423);
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    goto ZL2_825;
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
ZR1081 PROTO_N ((ZI399, ZO404))
  PROTO_T (IDENTIFIER *ZI399 X EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 33: case 34: case 35: case 36: case 42:
      case 44: case 45: case 46: case 48: case 49:
      case 50: case 53: case 54: case 55: case 56:
      case 57: case 58: case 59: case 60: case 61:
      case 63: case 65: case 66: case 67: case 68:
      case 69: case 70: case 71: case 72: case 73:
      case 74: case 75: case 76: case 77: case 78:
      case 79: case 80: case 81: case 86: case 87:
	{
	    EXP ZI1012;
	    EXP ZI1013;
	    EXP ZI1025;
	    EXP ZI416;
	    int ZI537;

	    {

    (ZI1012) = make_id_exp ( (*ZI399) ) ;
	    }
	    ZR922 (ZI1012, &ZI1013);
	    ZR1014 (&ZI1013, &ZI1025);
	    ZR1027 (&ZI1025, &ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI537) = unreached_code ;
    if ( (ZI537) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI404) = make_exp_stmt ( (ZI416) ) ;
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
	}
	break;
      case 41:
	{
	    EXP ZI416;
	    EXP ZI448;

	    {

    if ( unreached_code ) unreached_fall = 0 ;
	    }
	    {

    (ZI416) = begin_label_stmt ( (*ZI399), lex_identifier ) ;
	    }
	    ADVANCE_LEXER;
	    ZR528 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = end_label_stmt ( (ZI416), (ZI448) ) ;
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
    *ZO404 = ZI404;
}

void
ZR444 PROTO_N ((ZO395, ZO472))
  PROTO_T (TYPE *ZO395 X int *ZO472)
{
    TYPE ZI395;
    int ZI472;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	int ZI462;
	BASE_TYPE ZI658;
	TYPE ZI420;
	CV_SPEC ZI630;
	TYPE ZI423;

	{

    (ZI462) = no_type_defns ;
	}
	ZR687 (&ZI658, &ZI420, &ZI630);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI423) = complete_pre_type ( (ZI658), (ZI420), (ZI630), 1 ) ;
    have_type_specifier = 0 ;
	}
	ZR760 (ZI423, &ZI395);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI472) = no_type_defns - (ZI462) ;
	}
	{

    object_type ( (ZI395), null_tag ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO395 = ZI395;
    *ZO472 = ZI472;
}

void
ZR510 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 297:
	{
	    EXP ZI416;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR414 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_set_exp ( (ZI416) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 323:
	{
	    EXP ZI416;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR414 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_unused_exp ( (ZI416) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
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
    *ZO404 = ZI404;
}

void
ZR1082 PROTO_N ((ZI399, ZO404))
  PROTO_T (IDENTIFIER *ZI399 X EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      default:
	{
	    EXP ZI416;

	    {

    (ZI416) = make_id_exp ( (*ZI399) ) ;
	    }
	    {

    (ZI404) = make_exp_stmt ( (ZI416) ) ;
	    }
	}
	break;
      case 41:
	{
	    EXP ZI416;
	    EXP ZI448;

	    {

    if ( unreached_code ) unreached_fall = 0 ;
	    }
	    {

    (ZI416) = begin_label_stmt ( (*ZI399), lex_identifier ) ;
	    }
	    ADVANCE_LEXER;
	    ZR528 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = end_label_stmt ( (ZI416), (ZI448) ) ;
	    }
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
    *ZO404 = ZI404;
}

void
ZR804 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	DECL_SPEC ZI605;
	TYPE ZI395;

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
 (ZI605) = dspec_none ; 
	}
	{

    (ZI395) = NULL_type ;
	}
	ZR803 ();
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
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR421 PROTO_N ((ZO420))
  PROTO_T (SID_LIST_EXP *ZO420)
{
    SID_LIST_EXP ZI420;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI404;
	SID_LIST_EXP ZI423;

	ZR419 (&ZI404);
	ZR624 (&ZI423);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    CONS_exp ( (ZI404), (ZI423), (ZI420) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO420 = ZI420;
}

void
ZR419 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 170:
	{
	    int ZI1006;
	    EXP ZI1007;

	    ADVANCE_LEXER;
	    {
 (ZI1006) = lex_alignof ; 
	    }
	    ZR461 (ZI1006, &ZI1007);
	    ZR1014 (&ZI1007, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 23:
	{
	    EXP ZI1018;
	    EXP ZI1019;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1018 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR922 (ZI1018, &ZI1019);
	    ZR1014 (&ZI1019, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 205:
	{
	    EXP ZI416;
	    EXP ZI961;
	    EXP ZI960;
	    EXP ZI959;
	    EXP ZI958;
	    EXP ZI957;
	    EXP ZI956;
	    EXP ZI955;
	    EXP ZI954;
	    EXP ZI953;
	    EXP ZI952;
	    EXP ZI951;
	    EXP ZI948;

	    ADVANCE_LEXER;
	    ZR459 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI961) = make_cast_exp ( type_void, (ZI416), 0 ) ;
	    }
	    ZR918 (ZI961, &ZI960);
	    ZR914 (ZI960, &ZI959);
	    ZR910 (ZI959, &ZI958);
	    ZR906 (ZI958, &ZI957);
	    ZR902 (ZI957, &ZI956);
	    ZR898 (ZI956, &ZI955);
	    ZR894 (ZI955, &ZI954);
	    ZR890 (ZI954, &ZI953);
	    ZR886 (ZI953, &ZI952);
	    ZR882 (ZI952, &ZI951);
	    ZR878 (ZI951, &ZI948);
	    ZR950 (&ZI948, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 209:
	{
	    EXP ZI1015;
	    EXP ZI1016;

	    ADVANCE_LEXER;
	    {

    (ZI1015) = make_ellipsis_exp () ;
	    }
	    ZR922 (ZI1015, &ZI1016);
	    ZR1014 (&ZI1016, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 1:
	{
	    IDENTIFIER ZI399;
	    EXP ZI1012;
	    EXP ZI1013;

	    {

    ZI399 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI1012) = make_id_exp ( (ZI399) ) ;
	    }
	    ZR922 (ZI1012, &ZI1013);
	    ZR1014 (&ZI1013, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 61:
	{
	    EXP ZI987;
	    EXP ZI988;

	    ADVANCE_LEXER;
	    ZR458 (&ZI987);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI988) = make_prefix_exp ( lex_minus_Hminus, (ZI987) ) ;
	    }
	    ZR1014 (&ZI988, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR983 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 71:
	{
	    EXP ZI984;
	    EXP ZI985;

	    ADVANCE_LEXER;
	    ZR458 (&ZI984);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI985) = make_prefix_exp ( lex_plus_Hplus, (ZI984) ) ;
	    }
	    ZR1014 (&ZI985, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 116:
	{
	    int ZI1003;
	    EXP ZI1004;

	    ADVANCE_LEXER;
	    {
 (ZI1003) = lex_sizeof ; 
	    }
	    ZR461 (ZI1003, &ZI1004);
	    ZR1014 (&ZI1004, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 78:
	{
	    EXP ZI990;
	    EXP ZI991;

	    ADVANCE_LEXER;
	    ZR459 (&ZI990);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI991) = make_indir_exp ( (ZI990) ) ;
	    }
	    ZR1014 (&ZI991, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 33:
	{
	    EXP ZI993;
	    EXP ZI994;

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
	    ZR459 (&ZI993);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI994) = make_ref_exp ( (ZI993), 0 ) ;
	    }
	    ZR1014 (&ZI994, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 17: case 18: case 19: case 20: case 21:
      case 22:
	{
	    EXP ZI1009;
	    EXP ZI1010;

	    ZR409 (&ZI1009);
	    ZR922 (ZI1009, &ZI1010);
	    ZR1014 (&ZI1010, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 62:
	{
	    EXP ZI996;
	    EXP ZI997;

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
	    ZR459 (&ZI996);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI997) = make_not_exp ( (ZI996) ) ;
	    }
	    ZR1014 (&ZI997, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 43: case 59: case 69: case 85:
	{
	    int ZI999;
	    EXP ZI1000;
	    EXP ZI1001;

	    {
 (ZI999) = crt_lex_token ; 
	    }
	    ZR469 ();
	    ZR459 (&ZI1000);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI1001) = make_uminus_exp ( (ZI999), (ZI1000) ) ;
	    }
	    ZR1014 (&ZI1001, &ZI404);
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
    *ZO404 = ZI404;
}

void
ZR424 PROTO_N ((ZO420))
  PROTO_T (SID_LIST_EXP *ZO420)
{
    SID_LIST_EXP ZI420;

    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 205: case 209:
	{
	    ZR421 (&ZI420);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZI420) = NULL_list ( EXP ) ;
	    }
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
    *ZO420 = ZI420;
}

void
ZR499 PROTO_N ((ZO881))
  PROTO_T (EXP *ZO881)
{
    EXP ZI881;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI404;

	ZR497 (&ZI404);
	ZR882 (ZI404, &ZI881);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO881 = ZI881;
}

void
ZR614 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 95:
	{
	    int ZI537;

	    ADVANCE_LEXER;
	    {

    (ZI537) = unreached_code ;
    if ( (ZI537) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI404) = make_break_stmt () ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR396 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 99:
	{
	    int ZI537;

	    ADVANCE_LEXER;
	    {

    (ZI537) = unreached_code ;
    if ( (ZI537) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    {

    (ZI404) = make_continue_stmt () ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR396 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 108:
	{
	    int ZI537;

	    ADVANCE_LEXER;
	    {

    (ZI537) = unreached_code ;
    if ( (ZI537) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR613 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR396 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 113:
	{
	    int ZI537;
	    EXP ZI416;

	    ADVANCE_LEXER;
	    {

    (ZI537) = unreached_code ;
    if ( (ZI537) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	    }
	    ZR615 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_return_stmt ( (ZI416), lex_return ) ;
	    }
	    {

    unreached_fall = 1 ;
	    }
	    ZR396 ();
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
    *ZO404 = ZI404;
}

void
ZR963 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI395;
	int ZI472;
	EXP ZI416;

	{

    /* Resolve type-ids from expressions */
    (ZI0) = predict_typeid ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL2;
	ZR444 (&ZI395, &ZI472);
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
	ZR459 (&ZI416);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* n is the number of type definitions in t */
    (ZI404) = make_cast_exp ( (ZI395), (ZI416), (ZI472) ) ;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 1: case 17: case 18: case 19: case 20:
      case 21: case 22: case 23: case 33: case 43:
      case 59: case 61: case 62: case 65: case 69:
      case 71: case 78: case 85: case 116: case 170:
      case 205: case 209: case 297: case 323: case 345:
	{
	    EXP ZI416;
	    EXP ZI962;

	    {

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
	    }
	    ZR414 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI962) = make_paren_exp ( (ZI416) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR922 (ZI962, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO404 = ZI404;
}

void
ZR567 PROTO_N ((ZO930, ZO931, ZO932))
  PROTO_T (EXP *ZO930 X EXP *ZO931 X int *ZO932)
{
    EXP ZI930;
    EXP ZI931;
    int ZI932;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI467;
	EXP ZI420;
	int ZI537;
	EXP ZI416;
	EXP ZI404;

	switch (CURRENT_TERMINAL) {
	  case 26:
	    {

    ZI467 = crt_token->pp_data.exp ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    EXP c = crt_hash_cond ;
    crt_hash_cond = make_if_cond ( (ZI467), c ) ;
    (ZI420) = c ;
	}
	{

    (ZI537) = unreached_code ;
    if ( (ZI537) ) {
	if ( !unreached_last ) {
	    report ( crt_loc, ERR_stmt_stmt_unreach () ) ;
	    unreached_last = 1 ;
	}
    } else {
	unreached_last = 0 ;
    }
	}
	ZR551 (&ZI416);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{
 unreached_prev = (ZI537) ; 
	}
	{

    (ZI404) = begin_hash_if_stmt ( (ZI467), (ZI416) ) ;
	}
	ZR933 (ZI404, ZI420, ZI537, &ZI930, &ZI931, &ZI932);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO930 = ZI930;
    *ZO931 = ZI931;
    *ZO932 = ZI932;
}

void
ZR632 PROTO_N ((ZO630))
  PROTO_T (CV_SPEC *ZO630)
{
    CV_SPEC ZI630;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	CV_SPEC ZI416;

	ZR631 (&ZI416);
	{
	    switch (CURRENT_TERMINAL) {
	      case 98: case 124:
		{
		    CV_SPEC ZI448;

		    ZR632 (&ZI448);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    CV_SPEC c = ( (ZI416) & (ZI448) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZI630) = ( (ZI416) | (ZI448) ) ;
		    }
		}
		break;
	      default:
		{
		    ZI630 = ZI416;
		}
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO630 = ZI630;
}

void
ZR552 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI467;
	int ZI547;
	EXP ZI448;
	EXP ZI537;
	EXP ZI416;

	{

    (ZI467) = begin_compound_stmt ( 1 ) ;
	}
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

    COPY_int ( exp_sequence_block ( (ZI467) ), 2 ) ;
    (ZI547) = 1 ;
	}
	ZR548 (ZI467, ZI547, &ZI448);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI537) = fall_return_stmt () ;
	}
	{

    (ZI416) = add_compound_stmt ( (ZI448), (ZI537) ) ;
	}
	{
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

    (ZI404) = end_compound_stmt ( (ZI416) ) ;
	}
	{

    RESCAN_LEXER ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO404 = ZI404;
}

/* END OF FILE */
