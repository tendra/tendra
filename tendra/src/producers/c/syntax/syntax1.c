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



/* BEGINNING OF STATIC VARIABLES */

int ZI0;

/* BEGINNING OF FUNCTION DEFINITIONS */

void
ZR659 PROTO_N ((ZO658))
  PROTO_T (BASE_TYPE *ZO658)
{
    BASE_TYPE ZI658;

    switch (CURRENT_TERMINAL) {
      case 184:
	{
	    ADVANCE_LEXER;
	    {
 (ZI658) = btype_bottom ; 
	    }
	}
	break;
      case 97:
	{
	    ADVANCE_LEXER;
	    {
 (ZI658) = btype_char ; 
	    }
	}
	break;
      case 102:
	{
	    ADVANCE_LEXER;
	    {
 (ZI658) = btype_double ; 
	    }
	}
	break;
      case 106:
	{
	    ADVANCE_LEXER;
	    {
 (ZI658) = btype_float ; 
	    }
	}
	break;
      case 110:
	{
	    ADVANCE_LEXER;
	    {
 (ZI658) = btype_int ; 
	    }
	}
	break;
      case 111:
	{
	    ADVANCE_LEXER;
	    {
 (ZI658) = btype_long ; 
	    }
	}
	break;
      case 285:
	{
	    ADVANCE_LEXER;
	    {
 (ZI658) = btype_ptrdiff_t ; 
	    }
	}
	break;
      case 114:
	{
	    ADVANCE_LEXER;
	    {
 (ZI658) = btype_short ; 
	    }
	}
	break;
      case 115:
	{
	    ADVANCE_LEXER;
	    {
 (ZI658) = btype_signed ; 
	    }
	}
	break;
      case 298:
	{
	    ADVANCE_LEXER;
	    {
 (ZI658) = btype_size_t ; 
	    }
	}
	break;
      case 122:
	{
	    ADVANCE_LEXER;
	    {
 (ZI658) = btype_unsigned ; 
	    }
	}
	break;
      case 123:
	{
	    ADVANCE_LEXER;
	    {
 (ZI658) = btype_void ; 
	    }
	}
	break;
      case 156:
	{
	    ADVANCE_LEXER;
	    {
 (ZI658) = btype_wchar_t ; 
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
}

void
ZR890 PROTO_N ((ZI888, ZO889))
  PROTO_T (EXP ZI888 X EXP *ZO889)
{
    EXP ZI889;

  ZL2_890:;
    switch (CURRENT_TERMINAL) {
      case 80:
	{
	    EXP ZI448;
	    EXP ZI404;

	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 80:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
	    }
	    ZR493 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_xor_exp ( (ZI888), (ZI448) ) ;
	    }
	    ZI888 = ZI404;
	    goto ZL2_890;
	}
	/*UNREACHED*/
      default:
	{
	    ZI889 = ZI888;
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
    *ZO889 = ZI889;
}

void
ZR715 PROTO_N ((ZO658, ZO395, ZO630, ZO605))
  PROTO_T (BASE_TYPE *ZO658 X TYPE *ZO395 X CV_SPEC *ZO630 X DECL_SPEC *ZO605)
{
    BASE_TYPE ZI658;
    TYPE ZI395;
    CV_SPEC ZI630;
    DECL_SPEC ZI605;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI688;
	TYPE ZI689;
	CV_SPEC ZI690;
	DECL_SPEC ZI716;

	ZR714 (&ZI688, &ZI689, &ZI690, &ZI716);
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
	      case 2: case 25: case 94: case 97: case 98:
	      case 102: case 104: case 105: case 106: case 110:
	      case 111: case 112: case 114: case 115: case 117:
	      case 118: case 120: case 121: case 122: case 123:
	      case 124: case 137: case 156: case 184: case 285:
	      case 298:
		{
		    BASE_TYPE ZI692;
		    TYPE ZI693;
		    CV_SPEC ZI694;
		    DECL_SPEC ZI718;

		    ZR715 (&ZI692, &ZI693, &ZI694, &ZI718);
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
		    {

    /* Combine two declaration specifiers */
    DECL_SPEC d = ( ( (ZI716) & (ZI718) ) & dspec_duplicate ) ;
    if ( d ) report ( crt_loc, ERR_dcl_spec_dup ( d ) ) ;
    (ZI605) = ( (ZI716) | (ZI718) ) ;
		    }
		}
		break;
	      default:
		{
		    ZI658 = ZI688;
		    ZI395 = ZI689;
		    ZI630 = ZI690;
		    ZI605 = ZI716;
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
    *ZO658 = ZI658;
    *ZO395 = ZI395;
    *ZO630 = ZI630;
    *ZO605 = ZI605;
}

void
ZR745 PROTO_N ((ZI399, ZO395))
  PROTO_T (IDENTIFIER ZI399 X TYPE *ZO395)
{
    TYPE ZI395;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI568;

	    ADVANCE_LEXER;
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI399) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 2: case 25: case 47: case 94: case 97:
		  case 98: case 102: case 104: case 105: case 106:
		  case 110: case 111: case 112: case 114: case 115:
		  case 117: case 118: case 120: case 121: case 122:
		  case 123: case 124: case 137: case 156: case 184:
		  case 285: case 298:
		    {
			int ZI747;

			ZR743 (&ZI747);
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    (ZI568) = make_func_type ( NULL_type, (ZI747), cv_c, empty_type_set ) ;
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
		  case 1: case 4:
		    {
			ZR744 ();
			if ((CURRENT_TERMINAL) == 354) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    (ZI568) = make_func_type ( NULL_type, FUNC_PARAMS, cv_c, empty_type_set ) ;
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
		  case 39:
		    {
			{

    (ZI568) = make_func_type ( NULL_type, FUNC_NO_PARAMS, cv_c, empty_type_set ) ;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    ZI395 = ZI568;
	    {

    end_param () ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 1 ;
	    }
	}
	break;
      case 331:
	{
	    int ZI747;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI399) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR758 (&ZI747);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = make_func_type ( NULL_type, ( (ZI747) | FUNC_WEAK ), cv_c, empty_type_set ) ;
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
	    ZR757 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI404) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI395) ) ;
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
    *ZO395 = ZI395;
}

void
ZR894 PROTO_N ((ZI892, ZO893))
  PROTO_T (EXP ZI892 X EXP *ZO893)
{
    EXP ZI893;

  ZL2_894:;
    switch (CURRENT_TERMINAL) {
      case 33:
	{
	    EXP ZI448;
	    EXP ZI404;

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
	    ZR491 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_and_exp ( (ZI892), (ZI448) ) ;
	    }
	    ZI892 = ZI404;
	    goto ZL2_894;
	}
	/*UNREACHED*/
      default:
	{
	    ZI893 = ZI892;
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
    *ZO893 = ZI893;
}

void
ZR770 PROTO_N ((ZO547))
  PROTO_T (IDENTIFIER *ZO547)
{
    IDENTIFIER ZI547;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI658;
	TYPE ZI689;
	CV_SPEC ZI630;
	DECL_SPEC ZI716;
	TYPE ZI693;
	DECL_SPEC ZI605;
	TYPE ZI395;
	IDENTIFIER ZI399;

	ZR715 (&ZI658, &ZI689, &ZI630, &ZI716);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    /* Complete a declaration specifier and a type */
    (ZI605) = complete_dspec ( (ZI716), (ZI658), (ZI689), (ZI630) ) ;
    (ZI693) = complete_pre_type ( (ZI658), (ZI689), (ZI630), 0 ) ;
    have_type_specifier = 0 ;
	}
	ZR766 (ZI693, &ZI395, &ZI399);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZI547) = make_param_decl ( (ZI605), (ZI395), (ZI399), CONTEXT_PARAMETER ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO547 = ZI547;
}

void
ZR569 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI416;
	EXP ZI420;
	int ZI537;
	EXP ZI448;

	ZR567 (&ZI416, &ZI420, &ZI537);
	{
	    switch (CURRENT_TERMINAL) {
	      case 28:
		{
		    int ZI568;

		    ADVANCE_LEXER;
		    {

    crt_hash_cond = make_else_cond ( crt_hash_cond ) ;
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
		}
		break;
	      default:
		{
		    {

    (ZI448) = NULL_exp ;
		    }
		}
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	{

    crt_hash_cond = (ZI420) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
 unreached_prev = (ZI537) ; 
	}
	{

    (ZI404) = end_hash_if_stmt ( (ZI416), (ZI448) ) ;
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
ZR898 PROTO_N ((ZI896, ZO897))
  PROTO_T (EXP ZI896 X EXP *ZO897)
{
    EXP ZI897;

  ZL2_898:;
    switch (CURRENT_TERMINAL) {
      case 86: case 87:
	{
	    int ZI460;
	    EXP ZI448;
	    EXP ZI404;

	    {
 (ZI460) = crt_lex_token ; 
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 86:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 87:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    ZR488 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_mult_exp ( (ZI460), (ZI896), (ZI448) ) ;
	    }
	    ZI896 = ZI404;
	    goto ZL2_898;
	}
	/*UNREACHED*/
      default:
	{
	    ZI897 = ZI896;
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
    *ZO897 = ZI897;
}

void
ZR656 PROTO_N ((ZO395))
  PROTO_T (TYPE *ZO395)
{
    TYPE ZI395;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI669;

	ZR670 (&ZI669);
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
		    ZR1030 (&ZI669, &ZI399, &ZI395);
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
		    int ZI585;
		    IDENTIFIER ZI672;

		    {

    HASHID nm = lookup_anon () ;
    (ZI399) = DEREF_id ( hashid_id ( nm ) ) ;
		    }
		    {

    (ZI420) = begin_class_defn ( (ZI399), (ZI669), cinfo_none, NULL_type ) ;
    (ZI585) = in_function_defn ;
    in_function_defn = 0 ;
    in_class_defn++ ;
    really_in_class_defn++ ;
    no_type_defns++ ;
    end_base_class ( crt_class, 1 ) ;
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
		    ZR662 ();
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

    (ZI672) = end_class_defn ( (ZI420) ) ;
    in_function_defn = (ZI585) ;
    in_class_defn-- ;
    really_in_class_defn-- ;
		    }
		    {

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZI395) ) ;
    COPY_id ( type_name ( (ZI395) ), (ZI672) ) ;
    have_type_specifier = 1 ;
		    }
		    {

    RESCAN_LEXER ;
		    }
		}
		break;
	      case 354:
		RESTORE_LEXER;
		goto ZL1;
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
ZR427 PROTO_N ((ZI426, ZO399))
  PROTO_T (NAMESPACE ZI426 X IDENTIFIER *ZO399)
{
    IDENTIFIER ZI399;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI428;

	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    {

    ZI428 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    {

    ZI428 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      case 2:
		{
		    {

    ZI428 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    HASHID nm = DEREF_hashid ( id_name ( (ZI428) ) ) ;
    (ZI399) = find_qual_id ( (ZI426), nm, 1, 0 ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO399 = ZI399;
}

void
ZR714 PROTO_N ((ZO658, ZO395, ZO630, ZO605))
  PROTO_T (BASE_TYPE *ZO658 X TYPE *ZO395 X CV_SPEC *ZO630 X DECL_SPEC *ZO605)
{
    BASE_TYPE ZI658;
    TYPE ZI395;
    CV_SPEC ZI630;
    DECL_SPEC ZI605;

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
	    {
 (ZI605) = dspec_none ; 
	    }
	}
	break;
      case 94: case 105: case 112: case 117: case 120:
      case 137:
	{
	    ZR709 (&ZI605);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( have_type_specifier ) report ( crt_loc, ERR_dcl_spec_order ( (ZI605) ) ) ;
	    }
	    {
 (ZI658) = btype_none ; 
	    }
	    {

    (ZI395) = NULL_type ;
	    }
	    {
 (ZI630) = cv_none ; 
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
	    {
 (ZI605) = dspec_none ; 
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
    *ZO605 = ZI605;
}

void
parse_init PROTO_N ((ZI547, ZO404))
  PROTO_T (IDENTIFIER ZI547 X EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	ZR788 (ZI547, &ZI404);
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
ZR1027 PROTO_N ((ZI1025, ZO404))
  PROTO_T (EXP *ZI1025 X EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    SID_LIST_EXP ZI423;
	    SID_LIST_EXP ZI420;

	    ADVANCE_LEXER;
	    ZR515 (&ZI423);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI1025), (ZI423), (ZI420) ) ;
	    }
	    {

    (ZI404) = make_comma_exp ( (ZI420) ) ;
	    }
	}
	break;
      default:
	{
	    ZI404 = *ZI1025;
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
ZR803 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_803:;
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
	    goto ZL3;
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
	goto ZL2_803;
    }
    /*UNREACHED*/
  ZL3:;
    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    ADVANCE_LEXER;
	    {

    report ( crt_loc, ERR_dcl_dcl_semicolon () ) ;
	    }
	    goto ZL2_803;
	}
	/*UNREACHED*/
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
	    goto ZL2_803;
	}
	/*UNREACHED*/
      case 26: case 30:
	{
	    ZR806 ();
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_803;
	    }
	}
	/*UNREACHED*/
      case 1: case 2: case 4: case 65: case 78:
	{
	    BASE_TYPE ZI658;
	    TYPE ZI689;
	    CV_SPEC ZI630;
	    DECL_SPEC ZI716;
	    TYPE ZI395;
	    DECL_SPEC ZI605;
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
    (ZI605) = complete_dspec ( (ZI716), (ZI658), (ZI689), (ZI630) ) ;
    (ZI395) = complete_pre_type ( (ZI658), (ZI689), (ZI630), 0 ) ;
    have_type_specifier = 0 ;
	    }
	    ZR752 (ZI395, &ZI568, &ZI399);
	    ZR819 (&ZI658, &ZI395, &ZI605, &ZI568, &ZI399);
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
	    goto ZL2_803;
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
ZR1028 PROTO_N ((ZI416, ZO420))
  PROTO_T (EXP *ZI416 X SID_LIST_EXP *ZO420)
{
    SID_LIST_EXP ZI420;

    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    SID_LIST_EXP ZI423;

	    ADVANCE_LEXER;
	    ZR515 (&ZI423);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_exp ( (*ZI416), (ZI423), (ZI420) ) ;
	    }
	}
	break;
      default:
	{
	    SID_LIST_EXP ZI423;

	    {

    (ZI423) = NULL_list ( EXP ) ;
	    }
	    {

    CONS_exp ( (*ZI416), (ZI423), (ZI420) ) ;
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
ZR754 PROTO_N ((ZO395))
  PROTO_T (TYPE *ZO395)
{
    TYPE ZI395;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    IDENTIFIER ZI399;
	    TYPE ZI568;

	    ADVANCE_LEXER;
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
	}
	break;
      case 331:
	{
	    IDENTIFIER ZI399;
	    int ZI747;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 65:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI399) = NULL_id ;
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI399) ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	    ZR758 (&ZI747);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = make_func_type ( NULL_type, ( (ZI747) | FUNC_WEAK ), cv_c, empty_type_set ) ;
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
	    ZR757 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    NAT n = make_array_dim ( (ZI404) ) ;
    MAKE_type_array ( cv_none, NULL_type, n, (ZI395) ) ;
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
    *ZO395 = ZI395;
}

void
ZR1029 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 297:
	{
	    EXP ZI416;

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
	      case 346:
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
	    ZR414 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_unused_exp ( (ZI416) ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 346:
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
ZR902 PROTO_N ((ZI900, ZO901))
  PROTO_T (EXP ZI900 X EXP *ZO901)
{
    EXP ZI901;

  ZL2_902:;
    switch (CURRENT_TERMINAL) {
      case 48: case 63:
	{
	    int ZI460;
	    EXP ZI448;
	    EXP ZI404;

	    {
 (ZI460) = crt_lex_token ; 
	    }
	    ZR487 ();
	    ZR485 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI404) = make_equality_exp ( (ZI460), (ZI900), (ZI448) ) ;
	    }
	    ZI900 = ZI404;
	    goto ZL2_902;
	}
	/*UNREACHED*/
      default:
	{
	    ZI901 = ZI900;
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
    *ZO901 = ZI901;
}

void
ZR556 PROTO_N ((ZI467, ZO404))
  PROTO_T (EXP ZI467 X EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI416;

	ZR555 (ZI467, &ZI416);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
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
    {
	{

    /* Syntax errors */
    ERROR err = ERR_lex_parse ( crt_token ) ;
    report ( crt_loc, err ) ;
    have_syntax_error = 1 ;
	}
	{

    (ZI404) = end_compound_stmt ( (ZI467) ) ;
	}
	{

    RESCAN_LEXER ;
	}
    }
  ZL0:;
    *ZO404 = ZI404;
}

void
ZR1030 PROTO_N ((ZI669, ZI399, ZO395))
  PROTO_T (BASE_TYPE *ZI669 X IDENTIFIER *ZI399 X TYPE *ZO395)
{
    TYPE ZI395;

    switch (CURRENT_TERMINAL) {
      case 64:
	{
	    IDENTIFIER ZI420;
	    int ZI585;
	    IDENTIFIER ZI672;

	    {

    (ZI420) = begin_class_defn ( (*ZI399), (*ZI669), cinfo_none, NULL_type ) ;
    (ZI585) = in_function_defn ;
    in_function_defn = 0 ;
    in_class_defn++ ;
    really_in_class_defn++ ;
    no_type_defns++ ;
    end_base_class ( crt_class, 1 ) ;
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
	    ZR662 ();
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

    (ZI672) = end_class_defn ( (ZI420) ) ;
    in_function_defn = (ZI585) ;
    in_class_defn-- ;
    really_in_class_defn-- ;
	    }
	    {

    MAKE_type_pre ( cv_none, btype_alias, qual_none, (ZI395) ) ;
    COPY_id ( type_name ( (ZI395) ), (ZI672) ) ;
    have_type_specifier = 1 ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	}
	break;
      default:
	{
	    {

    MAKE_type_pre ( cv_none, (*ZI669), qual_none, (ZI395) ) ;
    COPY_id ( type_name ( (ZI395) ), (*ZI399) ) ;
    if ( have_type_declaration == TYPE_DECL_NONE ) {
	have_type_declaration = TYPE_DECL_ELABORATE ;
    }
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
ZR796 PROTO_N ((ZI605, ZI658, ZI420))
  PROTO_T (DECL_SPEC ZI605 X BASE_TYPE ZI658 X TYPE ZI420)
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	TYPE ZI395;
	IDENTIFIER ZI399;
	IDENTIFIER ZI547;
	EXP ZI404;

	ZR752 (ZI420, &ZI395, &ZI399);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( in_weak_param ) {
	(ZI547) = make_param_decl ( (ZI605), (ZI395), (ZI399), CONTEXT_WEAK_PARAM ) ;
    } else if ( type_tag ( (ZI395) ) == type_func_tag ) {
	check_weak_func ( (ZI395), 0 ) ;
	(ZI547) = make_func_decl ( (ZI605), (ZI395), (ZI399), 0 ) ;
    } else {
	int def = predict_obj_defn () ;
	(ZI547) = make_object_decl ( (ZI605), (ZI395), (ZI399), def ) ;
    }
    if ( IS_id_type_alias ( (ZI547) ) ) {
	BASE_TYPE bs = DEREF_btype ( id_type_alias_rep ( (ZI547) ) ) ;
	bs |= (ZI658) ;
	COPY_btype ( id_type_alias_rep ( (ZI547) ), bs ) ;
    }
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	}
	ZR792 (ZI547, &ZI404);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    int def = init_object ( (ZI547), (ZI404) ) ;
    if ( do_dump ) dump_declare ( (ZI547), &decl_loc, def ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR1031 PROTO_N ((ZI658, ZI420, ZI630))
  PROTO_T (BASE_TYPE *ZI658 X TYPE *ZI420 X CV_SPEC *ZI630)
{
    switch (CURRENT_TERMINAL) {
      case 77:
	{
	    {

    IGNORE empty_decl ( dspec_none, NULL_type, (*ZI658), (*ZI420), (*ZI630), last_lex_token, 1 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
    have_type_specifier = 0 ;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 1: case 2: case 4: case 41: case 65:
      case 78:
	{
	    TYPE ZI395;

	    {

    (ZI395) = complete_pre_type ( (*ZI658), (*ZI420), (*ZI630), 1 ) ;
    have_type_specifier = 0 ;
	    }
	    ZR824 (ZI395, *ZI658);
	    {
		switch (CURRENT_TERMINAL) {
		  case 42:
		    {
			ADVANCE_LEXER;
			ZR825 (ZI395, *ZI658);
			switch (CURRENT_TERMINAL) {
			  case 77:
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
		  case 77:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 354:
		    RESTORE_LEXER;
		    goto ZL1;
		  default:
		    goto ZL1;
		}
	    }
	}
	break;
      case 354:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR559 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI688;
	TYPE ZI1094;
	CV_SPEC ZI690;
	DECL_SPEC ZI1095;
	BASE_TYPE ZI658;
	TYPE ZI689;
	CV_SPEC ZI630;
	DECL_SPEC ZI716;

	{

    /* Resolve declaration-specifiers from other declarators */
    (ZI0) = predict_dspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL1;
	ZR714 (&ZI688, &ZI1094, &ZI690, &ZI1095);
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
	ZR724 (&ZI688, &ZI1094, &ZI690, &ZI1095, &ZI658, &ZI689, &ZI630, &ZI716);
	ZR813 (&ZI658, &ZI689, &ZI630, &ZI716);
	switch (CURRENT_TERMINAL) {
	  case 77:
	    break;
	  case 354:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR415 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 23:
	{
	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI404 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 209:
	{
	    ADVANCE_LEXER;
	    {

    (ZI404) = make_ellipsis_exp () ;
	    }
	}
	break;
      case 1:
	{
	    IDENTIFIER ZI399;

	    {

    ZI399 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI404) = make_id_exp ( (ZI399) ) ;
	    }
	}
	break;
      case 65:
	{
	    EXP ZI416;

	    ADVANCE_LEXER;
	    {

    IGNORE incr_value ( OPT_VAL_paren_depth ) ;
	    }
	    ZR414 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_paren_exp ( (ZI416) ) ;
    decr_value ( OPT_VAL_paren_depth ) ;
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
      case 17: case 18: case 19: case 20: case 21:
      case 22:
	{
	    ZR409 (&ZI404);
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
ZR906 PROTO_N ((ZI904, ZO905))
  PROTO_T (EXP ZI904 X EXP *ZO905)
{
    EXP ZI905;

  ZL2_906:;
    switch (CURRENT_TERMINAL) {
      case 49: case 50: case 53: case 54:
	{
	    int ZI460;
	    EXP ZI448;
	    EXP ZI404;

	    {
 (ZI460) = crt_lex_token ; 
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 49:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 50:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 53:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 54:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    ZR482 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* op will be in its primary form */
    (ZI404) = make_relation_exp ( (ZI460), (ZI904), (ZI448) ) ;
	    }
	    ZI904 = ZI404;
	    goto ZL2_906;
	}
	/*UNREACHED*/
      default:
	{
	    ZI905 = ZI904;
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
    *ZO905 = ZI905;
}

void
ZR620 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 288:
	{
	    EXP ZI416;

	    ADVANCE_LEXER;
	    {
 unreached_code = 0 ; 
	    }
	    ZR528 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_reach_stmt ( (ZI416), 1 ) ;
	    }
	}
	break;
      case 322:
	{
	    EXP ZI416;

	    ADVANCE_LEXER;
	    {
 unreached_code = 1 ; 
	    }
	    ZR528 (&ZI416);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_reach_stmt ( (ZI416), 0 ) ;
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
ZR670 PROTO_N ((ZO669))
  PROTO_T (BASE_TYPE *ZO669)
{
    BASE_TYPE ZI669;

    switch (CURRENT_TERMINAL) {
      case 118:
	{
	    ADVANCE_LEXER;
	    {
 (ZI669) = btype_struct ; 
	    }
	}
	break;
      case 121:
	{
	    ADVANCE_LEXER;
	    {
 (ZI669) = btype_union ; 
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
    *ZO669 = ZI669;
}

void
ZR789 PROTO_N ((ZI547, ZO420))
  PROTO_T (IDENTIFIER ZI547 X SID_LIST_EXP *ZO420)
{
    SID_LIST_EXP ZI420;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI448;
	EXP ZI416;
	SID_LIST_EXP ZI423;

	ZR788 (ZI547, &ZI448);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    MAKE_exp_location ( type_void, crt_loc, (ZI448), (ZI416) ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 42:
		{
		    ADVANCE_LEXER;
		    ZR1072 (&ZI547, &ZI423);
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
	    }
	}
	{

    CONS_exp ( (ZI416), (ZI423), (ZI420) ) ;
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
parse_tok_type PROTO_N ((ZO395))
  PROTO_T (TYPE *ZO395)
{
    TYPE ZI395;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	BASE_TYPE ZI658;
	TYPE ZI420;
	CV_SPEC ZI630;
	TYPE ZI423;

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
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO395 = ZI395;
}

void
ZR910 PROTO_N ((ZI908, ZO909))
  PROTO_T (EXP ZI908 X EXP *ZO909)
{
    EXP ZI909;

  ZL2_910:;
    switch (CURRENT_TERMINAL) {
      case 57:
	{
	    EXP ZI448;
	    EXP ZI404;

	    ADVANCE_LEXER;
	    ZR479 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_shift_exp ( lex_lshift, (ZI908), (ZI448) ) ;
	    }
	    ZI908 = ZI404;
	    goto ZL2_910;
	}
	/*UNREACHED*/
      case 75:
	{
	    EXP ZI448;
	    EXP ZI404;

	    ADVANCE_LEXER;
	    ZR479 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_shift_exp ( lex_rshift, (ZI908), (ZI448) ) ;
	    }
	    ZI908 = ZI404;
	    goto ZL2_910;
	}
	/*UNREACHED*/
      default:
	{
	    ZI909 = ZI908;
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
    *ZO909 = ZI909;
}

void
ZR487 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 48:
	{
	    ADVANCE_LEXER;
	}
	break;
      case 63:
	{
	    {
		{
		    switch (CURRENT_TERMINAL) {
		      case 63:
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
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR491 PROTO_N ((ZO897))
  PROTO_T (EXP *ZO897)
{
    EXP ZI897;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI404;

	ZR488 (&ZI404);
	ZR898 (ZI404, &ZI897);
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
    *ZO897 = ZI897;
}

void
ZR511 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 345:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR1029 (&ZI404);
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
parse_type_param PROTO_N ((ZO547))
  PROTO_T (IDENTIFIER *ZO547)
{
    IDENTIFIER ZI547;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
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
    *ZO547 = ZI547;
}

void
ZR914 PROTO_N ((ZI912, ZO913))
  PROTO_T (EXP ZI912 X EXP *ZO913)
{
    EXP ZI913;

  ZL2_914:;
    switch (CURRENT_TERMINAL) {
      case 59:
	{
	    EXP ZI448;
	    EXP ZI404;

	    ADVANCE_LEXER;
	    ZR476 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_minus_exp ( (ZI912), (ZI448) ) ;
	    }
	    ZI912 = ZI404;
	    goto ZL2_914;
	}
	/*UNREACHED*/
      case 69:
	{
	    EXP ZI448;
	    EXP ZI404;

	    ADVANCE_LEXER;
	    ZR476 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_plus_exp ( (ZI912), (ZI448) ) ;
	    }
	    ZI912 = ZI404;
	    goto ZL2_914;
	}
	/*UNREACHED*/
      default:
	{
	    ZI913 = ZI912;
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
    *ZO913 = ZI913;
}

void
ZR447 PROTO_N ((ZO921))
  PROTO_T (EXP *ZO921)
{
    EXP ZI921;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	EXP ZI404;

	ZR415 (&ZI404);
	ZR922 (ZI404, &ZI921);
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
    *ZO921 = ZI921;
}

void
ZR554 PROTO_N ((ZO404))
  PROTO_T (EXP *ZO404)
{
    EXP ZI404;

    switch (CURRENT_TERMINAL) {
      case 170:
	{
	    int ZI1006;
	    EXP ZI1007;
	    EXP ZI1025;
	    EXP ZI416;
	    int ZI537;

	    ADVANCE_LEXER;
	    {
 (ZI1006) = lex_alignof ; 
	    }
	    ZR461 (ZI1006, &ZI1007);
	    ZR1014 (&ZI1007, &ZI1025);
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
      case 23:
	{
	    EXP ZI1018;
	    EXP ZI1019;
	    EXP ZI1025;
	    EXP ZI416;
	    int ZI537;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1018 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    ZR922 (ZI1018, &ZI1019);
	    ZR1014 (&ZI1019, &ZI1025);
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
      case 24:
	{
	    EXP ZI416;

	    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI416 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZI404) = make_exp_stmt ( (ZI416) ) ;
	    }
	}
	break;
      case 205:
	{
	    EXP ZI1080;
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
	    EXP ZI1025;
	    EXP ZI416;
	    int ZI537;

	    ADVANCE_LEXER;
	    ZR459 (&ZI1080);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI961) = make_cast_exp ( type_void, (ZI1080), 0 ) ;
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
	    ZR950 (&ZI948, &ZI1025);
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
      case 209:
	{
	    EXP ZI1015;
	    EXP ZI1016;
	    EXP ZI1025;
	    EXP ZI416;
	    int ZI537;

	    ADVANCE_LEXER;
	    {

    (ZI1015) = make_ellipsis_exp () ;
	    }
	    ZR922 (ZI1015, &ZI1016);
	    ZR1014 (&ZI1016, &ZI1025);
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
      case 1:
	{
	    IDENTIFIER ZI399;

	    {

    ZI399 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1081 (&ZI399, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 345:
	{
	    ADVANCE_LEXER;
	    ZR1078 (&ZI404);
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
	    EXP ZI1025;
	    EXP ZI416;
	    int ZI537;

	    ADVANCE_LEXER;
	    ZR458 (&ZI987);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI988) = make_prefix_exp ( lex_minus_Hminus, (ZI987) ) ;
	    }
	    ZR1014 (&ZI988, &ZI1025);
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
      case 65:
	{
	    EXP ZI1025;
	    EXP ZI416;
	    int ZI537;

	    ADVANCE_LEXER;
	    ZR983 (&ZI1025);
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
      case 71:
	{
	    EXP ZI984;
	    EXP ZI985;
	    EXP ZI1025;
	    EXP ZI416;
	    int ZI537;

	    ADVANCE_LEXER;
	    ZR458 (&ZI984);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI985) = make_prefix_exp ( lex_plus_Hplus, (ZI984) ) ;
	    }
	    ZR1014 (&ZI985, &ZI1025);
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
      case 77:
	{
	    ADVANCE_LEXER;
	    {

    (ZI404) = NULL_exp ;
	    }
	}
	break;
      case 116:
	{
	    int ZI1003;
	    EXP ZI1004;
	    EXP ZI1025;
	    EXP ZI416;
	    int ZI537;

	    ADVANCE_LEXER;
	    {
 (ZI1003) = lex_sizeof ; 
	    }
	    ZR461 (ZI1003, &ZI1004);
	    ZR1014 (&ZI1004, &ZI1025);
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
      case 78:
	{
	    EXP ZI990;
	    EXP ZI991;
	    EXP ZI1025;
	    EXP ZI416;
	    int ZI537;

	    ADVANCE_LEXER;
	    ZR459 (&ZI990);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI991) = make_indir_exp ( (ZI990) ) ;
	    }
	    ZR1014 (&ZI991, &ZI1025);
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
      case 4:
	{
	    IDENTIFIER ZI399;

	    {

    ZI399 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    ZR1082 (&ZI399, &ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 2:
	{
	    IDENTIFIER ZI399;
	    EXP ZI416;
	    EXP ZI448;

	    {

    ZI399 = crt_token->pp_data.id.use ;
	    }
	    ADVANCE_LEXER;
	    {

    if ( unreached_code ) unreached_fall = 0 ;
	    }
	    {

    (ZI416) = begin_label_stmt ( (ZI399), lex_identifier ) ;
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

    (ZI404) = end_label_stmt ( (ZI416), (ZI448) ) ;
	    }
	}
	break;
      case 33:
	{
	    EXP ZI993;
	    EXP ZI994;
	    EXP ZI1025;
	    EXP ZI416;
	    int ZI537;

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
	    ZR1014 (&ZI994, &ZI1025);
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
      case 126:
	{
	    ZR623 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 288: case 322:
	{
	    ZR620 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 96: case 100: case 222:
	{
	    ZR529 ();
	    ZR1079 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 297: case 323:
	{
	    EXP ZI1073;
	    EXP ZI416;
	    int ZI537;

	    ZR510 (&ZI1073);
	    ZR1075 (&ZI1073, &ZI416);
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
      case 101: case 107: case 125:
	{
	    ZR602 (&ZI404);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 95: case 99: case 108: case 113:
	{
	    ZR614 (&ZI404);
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
	    EXP ZI1025;
	    EXP ZI416;
	    int ZI537;

	    ZR409 (&ZI1009);
	    ZR922 (ZI1009, &ZI1010);
	    ZR1014 (&ZI1010, &ZI1025);
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
      case 62:
	{
	    EXP ZI996;
	    EXP ZI997;
	    EXP ZI1025;
	    EXP ZI416;
	    int ZI537;

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
	    ZR1014 (&ZI997, &ZI1025);
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
      case 26: case 109: case 119:
	{
	    ZR580 (&ZI404);
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
	    EXP ZI1025;
	    EXP ZI416;
	    int ZI537;

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
	    ZR1014 (&ZI1001, &ZI1025);
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
ZR662 PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
  ZL2_662:;
    {
	BASE_TYPE ZI688;
	TYPE ZI689;
	CV_SPEC ZI690;
	BASE_TYPE ZI658;
	TYPE ZI420;
	CV_SPEC ZI630;

	{

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
	}
	if (!ZI0)
	    goto ZL3;
	ZR686 (&ZI688, &ZI689, &ZI690);
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
	ZR699 (&ZI688, &ZI689, &ZI690, &ZI658, &ZI420, &ZI630);
	ZR1031 (&ZI658, &ZI420, &ZI630);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	} else {
	    goto ZL2_662;
	}
    }
    /*UNREACHED*/
  ZL3:;
    return;
  ZL1:;
    SAVE_LEXER (354);
    return;
}

void
ZR1043 PROTO_N ((ZI420, ZI423, ZI1042))
  PROTO_T (TYPE *ZI420 X BASE_TYPE *ZI423 X IDENTIFIER *ZI1042)
{
    switch (CURRENT_TERMINAL) {
      case 41:
	{
	    EXP ZI467;
	    TYPE ZI395;

	    {

    IDENTIFIER pid = underlying_id ( (*ZI1042) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ADVANCE_LEXER;
	    ZR518 (&ZI467);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* Check for anonymous bitfields */
    HASHID nm = DEREF_hashid ( id_name ( (*ZI1042) ) ) ;
    int z = IS_hashid_anon ( nm ) ;
    (ZI395) = make_bitfield_type ( (*ZI420), (*ZI423), (ZI467), z ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( dspec_none, (ZI395), (*ZI1042), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
	    }
	}
	break;
      default:
	{
	    TYPE ZI1041;
	    TYPE ZI1035;
	    IDENTIFIER ZI399;
	    TYPE ZI395;

	    {

    (ZI1041) = NULL_type ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (*ZI1042) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR868 (ZI1041, *ZI1042, &ZI1035, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI1035) ) ? (*ZI420) : inject_pre_type ( (ZI1035), (*ZI420), 1 ) ) ;
	    }
	    {

    IDENTIFIER id = make_member_decl ( dspec_none, (ZI395), (ZI399), 0 ) ;
    if ( do_dump ) dump_declare ( id, &decl_loc, 0 ) ;
    have_type_declaration = TYPE_DECL_NONE ;
    have_func_declarator = 0 ;
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
ZR461 PROTO_N ((ZI460, ZO404))
  PROTO_T (int ZI460 X EXP *ZO404)
{
    EXP ZI404;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	int ZI462;
	int ZI463;
	EXP ZI467;

	{

    suppress_usage++ ;
	}
	{

    (ZI462) = no_side_effects ;
	}
	{

    (ZI463) = no_type_defns ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 170:
		{
		    int ZI1069;
		    EXP ZI416;
		    int ZI465;
		    int ZI466;
		    TYPE ZI395;

		    ADVANCE_LEXER;
		    {
 (ZI1069) = lex_alignof ; 
		    }
		    ZR461 (ZI1069, &ZI416);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI465) = no_side_effects - (ZI462) ;
		    }
		    {

    (ZI466) = no_type_defns - (ZI463) ;
		    }
		    {

    (ZI395) = typeof_exp ( &(ZI416), (ZI465), (ZI460) ) ;
		    }
		    {

    (ZI467) = make_sizeof_exp ( (ZI395), (ZI416), (ZI466), (ZI460) ) ;
		    }
		}
		break;
	      case 23:
		{
		    EXP ZI1100;
		    EXP ZI416;
		    int ZI465;
		    int ZI466;
		    TYPE ZI395;

		    {

    IDENTIFIER id = crt_token->pp_data.tok.id ;
    PPTOKEN *args = crt_token->pp_data.tok.args ;
    ZI1100 = parse_exp_token ( id, args ) ;
    RESCAN_LEXER ;
		    }
		    ADVANCE_LEXER;
		    ZR922 (ZI1100, &ZI416);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI465) = no_side_effects - (ZI462) ;
		    }
		    {

    (ZI466) = no_type_defns - (ZI463) ;
		    }
		    {

    (ZI395) = typeof_exp ( &(ZI416), (ZI465), (ZI460) ) ;
		    }
		    {

    (ZI467) = make_sizeof_exp ( (ZI395), (ZI416), (ZI466), (ZI460) ) ;
		    }
		}
		break;
	      case 209:
		{
		    EXP ZI1101;
		    EXP ZI416;
		    int ZI465;
		    int ZI466;
		    TYPE ZI395;

		    ADVANCE_LEXER;
		    {

    (ZI1101) = make_ellipsis_exp () ;
		    }
		    ZR922 (ZI1101, &ZI416);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI465) = no_side_effects - (ZI462) ;
		    }
		    {

    (ZI466) = no_type_defns - (ZI463) ;
		    }
		    {

    (ZI395) = typeof_exp ( &(ZI416), (ZI465), (ZI460) ) ;
		    }
		    {

    (ZI467) = make_sizeof_exp ( (ZI395), (ZI416), (ZI466), (ZI460) ) ;
		    }
		}
		break;
	      case 1:
		{
		    IDENTIFIER ZI399;
		    EXP ZI1102;
		    EXP ZI416;
		    int ZI465;
		    int ZI466;
		    TYPE ZI395;

		    {

    ZI399 = crt_token->pp_data.id.use ;
		    }
		    ADVANCE_LEXER;
		    {

    (ZI1102) = make_id_exp ( (ZI399) ) ;
		    }
		    ZR922 (ZI1102, &ZI416);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI465) = no_side_effects - (ZI462) ;
		    }
		    {

    (ZI466) = no_type_defns - (ZI463) ;
		    }
		    {

    (ZI395) = typeof_exp ( &(ZI416), (ZI465), (ZI460) ) ;
		    }
		    {

    (ZI467) = make_sizeof_exp ( (ZI395), (ZI416), (ZI466), (ZI460) ) ;
		    }
		}
		break;
	      case 61:
		{
		    EXP ZI1062;
		    EXP ZI416;
		    int ZI465;
		    int ZI466;
		    TYPE ZI395;

		    ADVANCE_LEXER;
		    ZR458 (&ZI1062);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI416) = make_prefix_exp ( lex_minus_Hminus, (ZI1062) ) ;
		    }
		    {

    (ZI465) = no_side_effects - (ZI462) ;
		    }
		    {

    (ZI466) = no_type_defns - (ZI463) ;
		    }
		    {

    (ZI395) = typeof_exp ( &(ZI416), (ZI465), (ZI460) ) ;
		    }
		    {

    (ZI467) = make_sizeof_exp ( (ZI395), (ZI416), (ZI466), (ZI460) ) ;
		    }
		}
		break;
	      case 65:
		{
		    ADVANCE_LEXER;
		    ZR1071 (&ZI460, &ZI462, &ZI463, &ZI467);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 71:
		{
		    EXP ZI1061;
		    EXP ZI416;
		    int ZI465;
		    int ZI466;
		    TYPE ZI395;

		    ADVANCE_LEXER;
		    ZR458 (&ZI1061);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI416) = make_prefix_exp ( lex_plus_Hplus, (ZI1061) ) ;
		    }
		    {

    (ZI465) = no_side_effects - (ZI462) ;
		    }
		    {

    (ZI466) = no_type_defns - (ZI463) ;
		    }
		    {

    (ZI395) = typeof_exp ( &(ZI416), (ZI465), (ZI460) ) ;
		    }
		    {

    (ZI467) = make_sizeof_exp ( (ZI395), (ZI416), (ZI466), (ZI460) ) ;
		    }
		}
		break;
	      case 116:
		{
		    int ZI1068;
		    EXP ZI416;
		    int ZI465;
		    int ZI466;
		    TYPE ZI395;

		    ADVANCE_LEXER;
		    {
 (ZI1068) = lex_sizeof ; 
		    }
		    ZR461 (ZI1068, &ZI416);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI465) = no_side_effects - (ZI462) ;
		    }
		    {

    (ZI466) = no_type_defns - (ZI463) ;
		    }
		    {

    (ZI395) = typeof_exp ( &(ZI416), (ZI465), (ZI460) ) ;
		    }
		    {

    (ZI467) = make_sizeof_exp ( (ZI395), (ZI416), (ZI466), (ZI460) ) ;
		    }
		}
		break;
	      case 78:
		{
		    EXP ZI1063;
		    EXP ZI416;
		    int ZI465;
		    int ZI466;
		    TYPE ZI395;

		    ADVANCE_LEXER;
		    ZR459 (&ZI1063);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI416) = make_indir_exp ( (ZI1063) ) ;
		    }
		    {

    (ZI465) = no_side_effects - (ZI462) ;
		    }
		    {

    (ZI466) = no_type_defns - (ZI463) ;
		    }
		    {

    (ZI395) = typeof_exp ( &(ZI416), (ZI465), (ZI460) ) ;
		    }
		    {

    (ZI467) = make_sizeof_exp ( (ZI395), (ZI416), (ZI466), (ZI460) ) ;
		    }
		}
		break;
	      case 33:
		{
		    EXP ZI1064;
		    EXP ZI416;
		    int ZI465;
		    int ZI466;
		    TYPE ZI395;

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
		    ZR459 (&ZI1064);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI416) = make_ref_exp ( (ZI1064), 0 ) ;
		    }
		    {

    (ZI465) = no_side_effects - (ZI462) ;
		    }
		    {

    (ZI466) = no_type_defns - (ZI463) ;
		    }
		    {

    (ZI395) = typeof_exp ( &(ZI416), (ZI465), (ZI460) ) ;
		    }
		    {

    (ZI467) = make_sizeof_exp ( (ZI395), (ZI416), (ZI466), (ZI460) ) ;
		    }
		}
		break;
	      case 17: case 18: case 19: case 20: case 21:
	      case 22:
		{
		    EXP ZI1103;
		    EXP ZI416;
		    int ZI465;
		    int ZI466;
		    TYPE ZI395;

		    ZR409 (&ZI1103);
		    ZR922 (ZI1103, &ZI416);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI465) = no_side_effects - (ZI462) ;
		    }
		    {

    (ZI466) = no_type_defns - (ZI463) ;
		    }
		    {

    (ZI395) = typeof_exp ( &(ZI416), (ZI465), (ZI460) ) ;
		    }
		    {

    (ZI467) = make_sizeof_exp ( (ZI395), (ZI416), (ZI466), (ZI460) ) ;
		    }
		}
		break;
	      case 62:
		{
		    EXP ZI1065;
		    EXP ZI416;
		    int ZI465;
		    int ZI466;
		    TYPE ZI395;

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
		    ZR459 (&ZI1065);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI416) = make_not_exp ( (ZI1065) ) ;
		    }
		    {

    (ZI465) = no_side_effects - (ZI462) ;
		    }
		    {

    (ZI466) = no_type_defns - (ZI463) ;
		    }
		    {

    (ZI395) = typeof_exp ( &(ZI416), (ZI465), (ZI460) ) ;
		    }
		    {

    (ZI467) = make_sizeof_exp ( (ZI395), (ZI416), (ZI466), (ZI460) ) ;
		    }
		}
		break;
	      case 43: case 59: case 69: case 85:
		{
		    int ZI1066;
		    EXP ZI1067;
		    EXP ZI416;
		    int ZI465;
		    int ZI466;
		    TYPE ZI395;

		    {
 (ZI1066) = crt_lex_token ; 
		    }
		    ZR469 ();
		    ZR459 (&ZI1067);
		    if ((CURRENT_TERMINAL) == 354) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZI416) = make_uminus_exp ( (ZI1066), (ZI1067) ) ;
		    }
		    {

    (ZI465) = no_side_effects - (ZI462) ;
		    }
		    {

    (ZI466) = no_type_defns - (ZI463) ;
		    }
		    {

    (ZI395) = typeof_exp ( &(ZI416), (ZI465), (ZI460) ) ;
		    }
		    {

    (ZI467) = make_sizeof_exp ( (ZI395), (ZI416), (ZI466), (ZI460) ) ;
		    }
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	{

    suppress_usage-- ;
	}
	ZI404 = ZI467;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (354);
    return;
  ZL0:;
    *ZO404 = ZI404;
}

void
ZR918 PROTO_N ((ZI916, ZO917))
  PROTO_T (EXP ZI916 X EXP *ZO917)
{
    EXP ZI917;

  ZL2_918:;
    switch (CURRENT_TERMINAL) {
      case 44:
	{
	    EXP ZI448;
	    EXP ZI404;

	    ADVANCE_LEXER;
	    ZR459 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_mult_exp ( lex_div, (ZI916), (ZI448) ) ;
	    }
	    ZI916 = ZI404;
	    goto ZL2_918;
	}
	/*UNREACHED*/
      case 73:
	{
	    EXP ZI448;
	    EXP ZI404;

	    ADVANCE_LEXER;
	    ZR459 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_rem_exp ( (ZI916), (ZI448) ) ;
	    }
	    ZI916 = ZI404;
	    goto ZL2_918;
	}
	/*UNREACHED*/
      case 78:
	{
	    EXP ZI448;
	    EXP ZI404;

	    ADVANCE_LEXER;
	    ZR459 (&ZI448);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_mult_exp ( lex_star, (ZI916), (ZI448) ) ;
	    }
	    ZI916 = ZI404;
	    goto ZL2_918;
	}
	/*UNREACHED*/
      default:
	{
	    ZI917 = ZI916;
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
    *ZO917 = ZI917;
}

void
ZR1046 PROTO_N ((ZO854, ZO855))
  PROTO_T (TYPE *ZO854 X IDENTIFIER *ZO855)
{
    TYPE ZI854;
    IDENTIFIER ZI855;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI1047;
	TYPE ZI1048;
	TYPE ZI395;
	IDENTIFIER ZI399;

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
	ZR856 (ZI1048, ZI1047, &ZI395, &ZI399);
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
	ZR856 (ZI395, ZI399, &ZI854, &ZI855);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    TYPE ZI395;
	    IDENTIFIER ZI399;

	    ADVANCE_LEXER;
	    ZR1046 (&ZI395, &ZI399);
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
	    ZR856 (ZI395, ZI399, &ZI854, &ZI855);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 331:
	{
	    IDENTIFIER ZI1045;
	    int ZI747;
	    TYPE ZI1051;
	    IDENTIFIER ZI1052;
	    TYPE ZI395;
	    IDENTIFIER ZI399;

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
	    ZR856 (ZI1051, ZI1052, &ZI395, &ZI399);
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
	    ZR856 (ZI395, ZI399, &ZI854, &ZI855);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI404;
	    TYPE ZI1049;
	    IDENTIFIER ZI1050;
	    TYPE ZI395;
	    IDENTIFIER ZI399;

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
	    ZR856 (ZI1049, ZI1050, &ZI395, &ZI399);
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
	    ZR856 (ZI395, ZI399, &ZI854, &ZI855);
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
	    IDENTIFIER ZI399;
	    TYPE ZI395;

	    ZR731 (&ZI420);
	    ZR764 (&ZI423, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI423) ) ? (ZI420) : inject_pre_type ( (ZI423), (ZI420), 0 ) ) ;
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
	    ZR856 (ZI395, ZI399, &ZI854, &ZI855);
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
	    IDENTIFIER ZI1044;
	    TYPE ZI568;
	    TYPE ZI395;
	    IDENTIFIER ZI399;

	    {

    (ZI1044) = NULL_id ;
	    }
	    {

    func_type_defn ( 0 ) ;
    begin_param ( (ZI1044) ) ;
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
	    {

    HASHID nm = lookup_anon () ;
    (ZI399) = DEREF_id ( hashid_id ( nm ) ) ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI399) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
	    }
	    ZR856 (ZI395, ZI399, &ZI854, &ZI855);
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
    *ZO854 = ZI854;
    *ZO855 = ZI855;
}

void
ZR778 PROTO_Z ()
{
  ZL2_778:;
    switch (CURRENT_TERMINAL) {
      case 42:
	{
	    IDENTIFIER ZI399;

	    ADVANCE_LEXER;
	    ZR777 (&ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
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
	    goto ZL2_778;
	}
	/*UNREACHED*/
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
ZR764 PROTO_N ((ZO395, ZO399))
  PROTO_T (TYPE *ZO395 X IDENTIFIER *ZO399)
{
    TYPE ZI395;
    IDENTIFIER ZI399;

    if ((CURRENT_TERMINAL) == 354) {
	return;
    }
    {
	IDENTIFIER ZI1047;
	TYPE ZI1048;

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
	ZR856 (ZI1048, ZI1047, &ZI395, &ZI399);
	if ((CURRENT_TERMINAL) == 354) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	goto ZL0;
    }
    /*UNREACHED*/
  ZL2:;
    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    ZR1046 (&ZI395, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 331:
	{
	    IDENTIFIER ZI1045;
	    int ZI747;
	    TYPE ZI1051;
	    IDENTIFIER ZI1052;

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
	    ZR856 (ZI1051, ZI1052, &ZI395, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 66:
	{
	    EXP ZI404;
	    TYPE ZI1049;
	    IDENTIFIER ZI1050;

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
	    ZR856 (ZI1049, ZI1050, &ZI395, &ZI399);
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
	    ZR764 (&ZI423, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI395) = ( IS_NULL_type ( (ZI423) ) ? (ZI420) : inject_pre_type ( (ZI423), (ZI420), 0 ) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZI395) = NULL_type ;
	    }
	    {

    HASHID nm = lookup_anon () ;
    (ZI399) = DEREF_id ( hashid_id ( nm ) ) ;
	    }
	    {

    IDENTIFIER pid = underlying_id ( (ZI399) ) ;
    DEREF_loc ( id_loc ( pid ), decl_loc ) ;
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
ZR922 PROTO_N ((ZI920, ZO921))
  PROTO_T (EXP ZI920 X EXP *ZO921)
{
    EXP ZI921;

  ZL2_922:;
    switch (CURRENT_TERMINAL) {
      case 61:
	{
	    EXP ZI404;

	    ADVANCE_LEXER;
	    {

    (ZI404) = make_postfix_exp ( lex_minus_Hminus, (ZI920) ) ;
	    }
	    ZI920 = ZI404;
	    goto ZL2_922;
	}
	/*UNREACHED*/
      case 65:
	{
	    SID_LIST_EXP ZI420;
	    EXP ZI404;

	    ADVANCE_LEXER;
	    ZR424 (&ZI420);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = make_func_exp ( (ZI920), (ZI420), 0 ) ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 39:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZI920 = ZI404;
	    goto ZL2_922;
	}
	/*UNREACHED*/
      case 71:
	{
	    EXP ZI404;

	    ADVANCE_LEXER;
	    {

    (ZI404) = make_postfix_exp ( lex_plus_Hplus, (ZI920) ) ;
	    }
	    ZI920 = ZI404;
	    goto ZL2_922;
	}
	/*UNREACHED*/
      case 66:
	{
	    EXP ZI448;
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
	    ZR414 (&ZI448);
	    {
		if ((CURRENT_TERMINAL) == 354) {
		    RESTORE_LEXER;
		    goto ZL1;
		}
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

    (ZI404) = make_index_exp ( (ZI920), (ZI448) ) ;
	    }
	    ZI920 = ZI404;
	    goto ZL2_922;
	}
	/*UNREACHED*/
      case 35:
	{
	    EXP ZI448;
	    TYPE ZI395;
	    NAMESPACE ZI426;
	    IDENTIFIER ZI399;
	    EXP ZI404;

	    {

    (ZI448) = begin_field_exp ( lex_arrow, (ZI920), &(ZI395), &(ZI426) ) ;
	    }
	    ADVANCE_LEXER;
	    ZR427 (ZI426, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = end_field_exp ( lex_arrow, (ZI448), (ZI395), (ZI426), (ZI399), 0 ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	    ZI920 = ZI404;
	    goto ZL2_922;
	}
	/*UNREACHED*/
      case 46:
	{
	    EXP ZI448;
	    TYPE ZI395;
	    NAMESPACE ZI426;
	    IDENTIFIER ZI399;
	    EXP ZI404;

	    {

    (ZI448) = begin_field_exp ( lex_dot, (ZI920), &(ZI395), &(ZI426) ) ;
	    }
	    ADVANCE_LEXER;
	    ZR427 (ZI426, &ZI399);
	    if ((CURRENT_TERMINAL) == 354) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZI404) = end_field_exp ( lex_dot, (ZI448), (ZI395), (ZI426), (ZI399), 0 ) ;
	    }
	    {

    RESCAN_LEXER ;
	    }
	    ZI920 = ZI404;
	    goto ZL2_922;
	}
	/*UNREACHED*/
      default:
	{
	    ZI921 = ZI920;
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
    *ZO921 = ZI921;
}

/* END OF FILE */
