/*
 * Automatically generated from the files:
 *	/u/g/release/Source/src/utilities/calculus/syntax.sid
 * and
 *	/u/g/release/Source/src/utilities/calculus/syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */


/*
    		 Crown Copyright (c) 1997
    
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
#include "calculus.h"
#include "common.h"
#include "error.h"
#include "extra.h"
#include "lex.h"
#include "syntax.h"
#include "type_ops.h"
#include "xalloc.h"


/*
    PARSER TYPES

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
    COUNTER VARIABLES

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
    COMPILATION MODE

    We allow unreached code in the automatically generated sections.
*/

#if FS_TENDRA
#pragma TenDRA begin
#ifndef OLD_PRODUCER
#pragma TenDRA unreachable code allow
#endif
#endif



/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZR254 PROTO_S ((number, number *));
static void ZRimport_Hitem PROTO_S ((void));
static void ZR258 PROTO_S ((number, number *));
static void ZRprimary_Hexp PROTO_S ((number *));
static void ZR262 PROTO_S ((number, number *));
static void ZR264 PROTO_S ((int *));
static void ZR265 PROTO_S ((int *));
static void ZR268 PROTO_S ((CLASS_ID_P *));
static void ZR269 PROTO_S ((string *));
static void ZRextra_Hlist PROTO_S ((void));
static void ZRclass_Hid PROTO_S ((CLASS_ID_P *));
static void ZRnew_Hitem_Hlist PROTO_S ((void));
extern void extra_calculus PROTO_S ((void));
static void ZRunion_Hlist PROTO_S ((UNION_P_LIST *));
static void ZRshift_Hexp PROTO_S ((number *));
static void ZRcomponent_Hdecl PROTO_S ((TYPE_P, COMPONENT_P_LIST *));
static void ZRadd_Hexp PROTO_S ((number *));
static void ZRstructure_Hsingle PROTO_S ((STRUCTURE_P_LIST *));
static void ZRmap_Hlist PROTO_S ((MAP_P_LIST *));
static void ZRprimitive_Hdefn PROTO_S ((CLASS_ID_P, PRIMITIVE_P *));
static void ZRunary_Hexp PROTO_S ((number *));
static void ZRand_Hexp PROTO_S ((number *));
static void ZRargument_Hdecl PROTO_S ((TYPE_P, ARGUMENT_P_LIST *));
static void ZRold_Hunit PROTO_S ((void));
static void ZRenumerator_Hlist PROTO_S ((ECONST_P_LIST *));
static void ZRcomponent_Hgroup PROTO_S ((COMPONENT_P_LIST *));
static void ZRnew_Hunit PROTO_S ((void));
static void ZRidentity_Hdefn PROTO_S ((CLASS_ID_P, IDENTITY_P *));
static void ZRmult_Hexp PROTO_S ((number *));
extern void read_calculus PROTO_S ((void));
static void ZRtype PROTO_S ((TYPE_P *));
static void ZRstructure_Hdefn PROTO_S ((CLASS_ID_P, string, STRUCTURE_P *));
static void ZRcomponent_Hlist PROTO_S ((COMPONENT_P_LIST *));
static void ZRextended_Htype PROTO_S ((TYPE_P *));
static void ZRprimitive_Hlist PROTO_S ((PRIMITIVE_P_LIST *));
static void ZR209 PROTO_S ((string *));
static void ZRargument_Hlist PROTO_S ((ARGUMENT_P_LIST *));
static void ZRexpression PROTO_S ((number *));
static void ZRxor_Hexp PROTO_S ((number *));
static void ZRidentity_Hlist PROTO_S ((IDENTITY_P_LIST *));
static void ZRor_Hexp PROTO_S ((number *));
static void ZRunion_Hsingle PROTO_S ((UNION_P_LIST *));
static void ZRstructure_Hlist PROTO_S ((STRUCTURE_P_LIST *));
static void ZRunion_Hdefn_Hold PROTO_S ((CLASS_ID_P, UNION_P *));
static void ZRenum_Hsingle PROTO_S ((ENUM_P_LIST *));
static void ZRfield_Hid_Hlist PROTO_S ((int, FIELD_P_LIST *));
static void ZR242 PROTO_S ((number, number *));
static void ZRfield_Hlist PROTO_S ((FIELD_P_LIST *));
static void ZRunion_Hdefn_Hnew PROTO_S ((CLASS_ID_P, UNION_P *));
static void ZR246 PROTO_S ((number, number *));
static void ZR250 PROTO_S ((number, number *));

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZR254 PROTO_N ((ZI252, ZO253))
  PROTO_T (number ZI252 X number *ZO253)
{
    number ZI253;

  ZL2_254:;
    switch (CURRENT_TERMINAL) {
      case 35:
	{
	    number ZIp;
	    number ZIn;

	    ADVANCE_LEXER;
	    ZRadd_Hexp (&ZIp);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIn) = (ZI252) << (ZIp) ;
	    }
	    ZI252 = ZIn;
	    goto ZL2_254;
	}
	/*UNREACHED*/
      case 44:
	{
	    number ZIp;
	    number ZIn;

	    ADVANCE_LEXER;
	    ZRadd_Hexp (&ZIp);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIn) = (ZI252) >> (ZIp) ;
	    }
	    ZI252 = ZIn;
	    goto ZL2_254;
	}
	/*UNREACHED*/
      default:
	{
	    ZI253 = ZI252;
	}
	break;
      case 49:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZO253 = ZI253;
}

static void
ZRimport_Hitem PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	string ZIa;

	switch (CURRENT_TERMINAL) {
	  case 0:
	    {

    ZIa = xstrcpy ( token_buff ) ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR269 (&ZIa);
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (49);
    return;
}

static void
ZR258 PROTO_N ((ZI256, ZO257))
  PROTO_T (number ZI256 X number *ZO257)
{
    number ZI257;

  ZL2_258:;
    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    number ZIp;
	    number ZIn;

	    ADVANCE_LEXER;
	    ZRmult_Hexp (&ZIp);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIn) = (ZI256) - (ZIp) ;
	    }
	    ZI256 = ZIn;
	    goto ZL2_258;
	}
	/*UNREACHED*/
      case 41:
	{
	    number ZIp;
	    number ZIn;

	    ADVANCE_LEXER;
	    ZRmult_Hexp (&ZIp);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIn) = (ZI256) + (ZIp) ;
	    }
	    ZI256 = ZIn;
	    goto ZL2_258;
	}
	/*UNREACHED*/
      default:
	{
	    ZI257 = ZI256;
	}
	break;
      case 49:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZO257 = ZI257;
}

static void
ZRprimary_Hexp PROTO_N ((ZOn))
  PROTO_T (number *ZOn)
{
    number ZIn;

    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    string ZIe;

	    {

    ZIe = xstrcpy ( token_buff ) ;
	    }
	    ADVANCE_LEXER;
	    {

    number n = 0 ;
    LIST ( ECONST_P ) p = enum_list ;
    while ( !IS_NULL_list ( p ) ) {
	ECONST_P q = DEREF_ptr ( HEAD_list ( p ) ) ;
	string s = DEREF_string ( ec_name ( q ) ) ;
	if ( streq ( s, (ZIe) ) ) {
	    n = DEREF_number ( ec_value ( q ) ) ;
	    break ;
	}
	p = TAIL_list ( p ) ;
    }
    if ( IS_NULL_list ( p ) ) {
	error ( ERROR_SERIOUS, "Unknown enumerator '%s'", (ZIe) ) ;
    }
    (ZIn) = n ;
	    }
	}
	break;
      case 1:
	{
	    {

    ZIn = token_value ;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 38:
	{
	    ADVANCE_LEXER;
	    ZRexpression (&ZIn);
	    switch (CURRENT_TERMINAL) {
	      case 23:
		break;
	      case 49:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 42:
	{
	    ADVANCE_LEXER;
	    {

    (ZIn) = enum_value - 1 ;
	    }
	}
	break;
      case 49:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOn = ZIn;
}

static void
ZR262 PROTO_N ((ZI260, ZO261))
  PROTO_T (number ZI260 X number *ZO261)
{
    number ZI261;

  ZL2_262:;
    switch (CURRENT_TERMINAL) {
      case 29:
	{
	    number ZIp;
	    number ZIn;

	    ADVANCE_LEXER;
	    ZRunary_Hexp (&ZIp);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( (ZIp) == 0 ) {
	error ( ERROR_SERIOUS, "Division by zero" ) ;
	(ZIn) = 0 ;
    } else {
	(ZIn) = (ZI260) / (ZIp) ;
    }
	    }
	    ZI260 = ZIn;
	    goto ZL2_262;
	}
	/*UNREACHED*/
      case 43:
	{
	    number ZIp;
	    number ZIn;

	    ADVANCE_LEXER;
	    ZRunary_Hexp (&ZIp);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( (ZIp) == 0 ) {
	error ( ERROR_SERIOUS, "Division by zero" ) ;
	(ZIn) = 0 ;
    } else {
	(ZIn) = (ZI260) % (ZIp) ;
    }
	    }
	    ZI260 = ZIn;
	    goto ZL2_262;
	}
	/*UNREACHED*/
      case 46:
	{
	    number ZIp;
	    number ZIn;

	    ADVANCE_LEXER;
	    ZRunary_Hexp (&ZIp);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIn) = (ZI260) * (ZIp) ;
	    }
	    ZI260 = ZIn;
	    goto ZL2_262;
	}
	/*UNREACHED*/
      default:
	{
	    ZI261 = ZI260;
	}
	break;
      case 49:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZO261 = ZI261;
}

static void
ZR264 PROTO_N ((ZOn))
  PROTO_T (int *ZOn)
{
    int ZIn;

    switch (CURRENT_TERMINAL) {
      case 25:
	{
	    ADVANCE_LEXER;
	    {
 (ZIn) = 3 ; 
	    }
	}
	break;
      default:
	{
	    {
 (ZIn) = 1 ; 
	    }
	}
	break;
      case 49:
	return;
    }
    *ZOn = ZIn;
}

static void
ZR265 PROTO_N ((ZOn))
  PROTO_T (int *ZOn)
{
    int ZIn;

    switch (CURRENT_TERMINAL) {
      case 34:
	{
	    ADVANCE_LEXER;
	    {
 (ZIn) = 2 ; 
	    }
	}
	break;
      default:
	{
	    {
 (ZIn) = 1 ; 
	    }
	}
	break;
      case 49:
	return;
    }
    *ZOn = ZIn;
}

static void
ZR268 PROTO_N ((ZI267))
  PROTO_T (CLASS_ID_P *ZI267)
{
    switch (CURRENT_TERMINAL) {
      case 0: case 15: case 16: case 17: case 18:
      case 19:
	{
	    IDENTITY_P ZIq;
	    IDENTITY_P_LIST ZIr;
	    IDENTITY_P_LIST ZIi;

	    ZRidentity_Hdefn (*ZI267, &ZIq);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIr) = NULL_list ( IDENTITY_P ) ;
	    }
	    {

    CONS_ptr ( (ZIq), (ZIr), (ZIi) ) ;
	    }
	    {

    algebra->identities = APPEND_list ( algebra->identities, (ZIi) ) ;
	    }
	}
	break;
      case 2:
	{
	    PRIMITIVE_P ZIq;
	    PRIMITIVE_P_LIST ZIr;
	    PRIMITIVE_P_LIST ZIp;

	    ZRprimitive_Hdefn (*ZI267, &ZIq);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIr) = NULL_list ( PRIMITIVE_P ) ;
	    }
	    {

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
	    }
	    {

    algebra->primitives = APPEND_list ( algebra->primitives, (ZIp) ) ;
	    }
	}
	break;
      case 49:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (49);
    return;
}

static void
ZR269 PROTO_N ((ZIa))
  PROTO_T (string *ZIa)
{
    switch (CURRENT_TERMINAL) {
      case 26:
	{
	    string ZIi;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 0:
		{

    ZIi = xstrcpy ( token_buff ) ;
		}
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    import_type ( (*ZIa), (ZIi) ) ;
	    }
	}
	break;
      default:
	{
	    {

    import_algebra ( (*ZIa) ) ;
	    }
	}
	break;
      case 49:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (49);
    return;
}

static void
ZRextra_Hlist PROTO_Z ()
{
  ZL2_extra_Hlist:;
    switch (CURRENT_TERMINAL) {
      case 0: case 15: case 16: case 17: case 18:
      case 19:
	{
	    TYPE_P ZIt;

	    ZRtype (&ZIt);
	    switch (CURRENT_TERMINAL) {
	      case 45:
		break;
	      case 49:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    UNUSED ( (ZIt) ) ;
	    }
	    goto ZL2_extra_Hlist;
	}
	/*UNREACHED*/
      case 49:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (49);
    return;
}

static void
ZRclass_Hid PROTO_N ((ZOi))
  PROTO_T (CLASS_ID_P *ZOi)
{
    CLASS_ID_P ZIi;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	int ZIn;
	string ZIc;
	string ZIa;

	{
	    switch (CURRENT_TERMINAL) {
	      case 25:
		{
		    ADVANCE_LEXER;
		    {
 (ZIn) = 2 ; 
		    }
		}
		break;
	      case 34:
		{
		    ADVANCE_LEXER;
		    ZR264 (&ZIn);
		    if ((CURRENT_TERMINAL) == 49) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {
 (ZIn) = 0 ; 
		    }
		}
		break;
	    }
	}
	switch (CURRENT_TERMINAL) {
	  case 0:
	    {

    ZIc = xstrcpy ( token_buff ) ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 38:
		{
		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 0:
			{

    ZIa = xstrcpy ( token_buff ) ;
			}
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
		}
		break;
	      default:
		{
		    {

    (ZIa) = (ZIc) ;
		    }
		}
		break;
	    }
	}
	{

    (ZIi) = MAKE_ptr ( SIZE_cid ) ;
    MAKE_cid ( (ZIc), (ZIa), (ZIn), ( string ) crt_file_name, crt_line_no, (ZIi) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOi = ZIi;
}

static void
ZRnew_Hitem_Hlist PROTO_Z ()
{
  ZL2_new_Hitem_Hlist:;
    switch (CURRENT_TERMINAL) {
      case 0: case 4: case 5: case 6: case 7:
      case 25: case 34:
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 7:
		    {
			ADVANCE_LEXER;
			ZRimport_Hitem ();
			switch (CURRENT_TERMINAL) {
			  case 45:
			    break;
			  case 49:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
		    }
		    break;
		  case 0: case 25: case 34:
		    {
			CLASS_ID_P ZI267;

			ZRclass_Hid (&ZI267);
			switch (CURRENT_TERMINAL) {
			  case 32:
			    break;
			  case 49:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			ZR268 (&ZI267);
			if ((CURRENT_TERMINAL) == 49) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  case 4:
		    {
			ENUM_P_LIST ZIe;

			ZRenum_Hsingle (&ZIe);
			if ((CURRENT_TERMINAL) == 49) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    algebra->enumerations = APPEND_list ( algebra->enumerations, (ZIe) ) ;
			}
		    }
		    break;
		  case 5:
		    {
			STRUCTURE_P_LIST ZIs;

			ZRstructure_Hsingle (&ZIs);
			if ((CURRENT_TERMINAL) == 49) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    algebra->structures = APPEND_list ( algebra->structures, (ZIs) ) ;
			}
		    }
		    break;
		  case 6:
		    {
			UNION_P_LIST ZIu;

			ZRunion_Hsingle (&ZIu);
			if ((CURRENT_TERMINAL) == 49) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    algebra->unions = APPEND_list ( algebra->unions, (ZIu) ) ;
			}
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    goto ZL2_new_Hitem_Hlist;
	}
	/*UNREACHED*/
      case 49:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (49);
    return;
}

void
extra_calculus PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	ZRextra_Hlist ();
	switch (CURRENT_TERMINAL) {
	  case 31:
	    break;
	  case 49:
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
	{

    error ( ERROR_SERIOUS, "Syntax error" ) ;
	}
    }
}

static void
ZRunion_Hlist PROTO_N ((ZOp))
  PROTO_T (UNION_P_LIST *ZOp)
{
    UNION_P_LIST ZIp;

    switch (CURRENT_TERMINAL) {
      case 0: case 25: case 34:
	{
	    CLASS_ID_P ZIi;
	    UNION_P ZIq;
	    UNION_P_LIST ZIr;

	    ZRclass_Hid (&ZIi);
	    ZRunion_Hdefn_Hold (ZIi, &ZIq);
	    ZRunion_Hlist (&ZIr);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZIp) = NULL_list ( UNION_P ) ;
	    }
	}
	break;
      case 49:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRshift_Hexp PROTO_N ((ZO253))
  PROTO_T (number *ZO253)
{
    number ZI253;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	number ZIn;

	ZRadd_Hexp (&ZIn);
	ZR254 (ZIn, &ZI253);
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZO253 = ZI253;
}

static void
ZRcomponent_Hdecl PROTO_N ((ZIt, ZOp))
  PROTO_T (TYPE_P ZIt X COMPONENT_P_LIST *ZOp)
{
    COMPONENT_P_LIST ZIp;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	string ZIi;
	string ZIv;
	COMPONENT_P ZIq;
	COMPONENT_P_LIST ZIr;

	switch (CURRENT_TERMINAL) {
	  case 0:
	    {

    ZIi = xstrcpy ( token_buff ) ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 32:
		{
		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 2:
			{

    ZIv = xstrcpy ( token_buff ) ;
			}
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		{
		    {

    (ZIv) = NULL ;
		    }
		}
		break;
	    }
	}
	{

    (ZIq) = MAKE_ptr ( SIZE_cmp ) ;
    MAKE_cmp ( (ZIi), (ZIt), (ZIv), (ZIq) ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 27:
		{
		    ADVANCE_LEXER;
		    ZRcomponent_Hdecl (ZIt, &ZIr);
		    if ((CURRENT_TERMINAL) == 49) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIr) = NULL_list ( COMPONENT_P ) ;
		    }
		}
		break;
	    }
	}
	{

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRadd_Hexp PROTO_N ((ZO257))
  PROTO_T (number *ZO257)
{
    number ZI257;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	number ZIn;

	ZRmult_Hexp (&ZIn);
	ZR258 (ZIn, &ZI257);
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZO257 = ZI257;
}

static void
ZRstructure_Hsingle PROTO_N ((ZOp))
  PROTO_T (STRUCTURE_P_LIST *ZOp)
{
    STRUCTURE_P_LIST ZIp;

    if ((CURRENT_TERMINAL) == 49) {
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
	  case 32:
	    break;
	  case 49:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR209 (&ZIj);
	ZRstructure_Hdefn (ZIi, ZIj, &ZIq);
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZIr) = NULL_list ( STRUCTURE_P ) ;
	}
	{

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRmap_Hlist PROTO_N ((ZOp))
  PROTO_T (MAP_P_LIST *ZOp)
{
    MAP_P_LIST ZIp;

    switch (CURRENT_TERMINAL) {
      case 0: case 2: case 15: case 16: case 17:
      case 18: case 19:
	{
	    TYPE_P ZIt;
	    int ZIn;
	    string ZIi;
	    ARGUMENT_P_LIST ZIa;
	    MAP_P ZIq;
	    MAP_P_LIST ZIr;

	    ZRextended_Htype (&ZIt);
	    {
		switch (CURRENT_TERMINAL) {
		  case 34:
		    {
			ADVANCE_LEXER;
			{
 (ZIn) = 1 ; 
			}
		    }
		    break;
		  default:
		    {
			{
 (ZIn) = 0 ; 
			}
		    }
		    break;
		  case 49:
		    RESTORE_LEXER;
		    goto ZL1;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 0:
		{

    ZIi = xstrcpy ( token_buff ) ;
		}
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
	    {
		switch (CURRENT_TERMINAL) {
		  case 0: case 2: case 15: case 16: case 17:
		  case 18: case 19:
		    {
			ZRargument_Hlist (&ZIa);
			if ((CURRENT_TERMINAL) == 49) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  default:
		    {
			{

    (ZIa) = NULL_list ( ARGUMENT_P ) ;
			}
		    }
		    break;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 23:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZIq) = MAKE_ptr ( SIZE_map ) ;
    MAKE_map ( (ZIi), (ZIn), (ZIt), (ZIa), (ZIq) ) ;
	    }
	    ZRmap_Hlist (&ZIr);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZIp) = NULL_list ( MAP_P ) ;
	    }
	}
	break;
      case 49:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRprimitive_Hdefn PROTO_N ((ZIi, ZOp))
  PROTO_T (CLASS_ID_P ZIi X PRIMITIVE_P *ZOp)
{
    PRIMITIVE_P ZIp;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	string ZIs;

	switch (CURRENT_TERMINAL) {
	  case 2:
	    {

    ZIs = xstrcpy ( token_buff ) ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 45:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    TYPE r ;
    TYPE_P t ;
    (ZIp) = MAKE_ptr ( SIZE_prim ) ;
    MAKE_prim ( (ZIi), (ZIs), (ZIp) ) ;
    t = MAKE_ptr ( SIZE_type ) ;
    MAKE_type_primitive ( 0, (ZIp), r ) ;
    COPY_type ( t, r ) ;
    IGNORE register_type ( t ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRunary_Hexp PROTO_N ((ZOn))
  PROTO_T (number *ZOn)
{
    number ZIn;

    switch (CURRENT_TERMINAL) {
      case 28:
	{
	    number ZIm;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{

    ZIm = token_value ;
		}
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZIn) = ~(ZIm) ;
	    }
	}
	break;
      case 36:
	{
	    number ZIm;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{

    ZIm = token_value ;
		}
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZIn) = -(ZIm) ;
	    }
	}
	break;
      case 41:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{

    ZIn = token_value ;
		}
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 0: case 1: case 38: case 42:
	{
	    ZRprimary_Hexp (&ZIn);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 49:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOn = ZIn;
}

static void
ZRand_Hexp PROTO_N ((ZO249))
  PROTO_T (number *ZO249)
{
    number ZI249;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	number ZIn;

	ZRshift_Hexp (&ZIn);
	ZR250 (ZIn, &ZI249);
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZO249 = ZI249;
}

static void
ZRargument_Hdecl PROTO_N ((ZIt, ZOp))
  PROTO_T (TYPE_P ZIt X ARGUMENT_P_LIST *ZOp)
{
    ARGUMENT_P_LIST ZIp;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	string ZIi;
	ARGUMENT_P ZIq;
	ARGUMENT_P_LIST ZIr;

	switch (CURRENT_TERMINAL) {
	  case 0:
	    {

    ZIi = xstrcpy ( token_buff ) ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    (ZIq) = MAKE_ptr ( SIZE_arg ) ;
    MAKE_arg ( (ZIi), (ZIt), (ZIq) ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 27:
		{
		    ADVANCE_LEXER;
		    ZRargument_Hdecl (ZIt, &ZIr);
		    if ((CURRENT_TERMINAL) == 49) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIr) = NULL_list ( ARGUMENT_P ) ;
		    }
		}
		break;
	    }
	}
	{

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRold_Hunit PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	string ZIm;
	PRIMITIVE_P_LIST ZIp;
	IDENTITY_P_LIST ZIi;
	STRUCTURE_P_LIST ZIs;
	UNION_P_LIST ZIu;

	switch (CURRENT_TERMINAL) {
	  case 0:
	    {

    ZIm = xstrcpy ( token_buff ) ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    string nm = (ZIm) ;
    if ( !new_format ) error ( ERROR_WARNING, "Old style algebra syntax" ) ;
    if ( find_algebra ( nm ) ) {
	error ( ERROR_SERIOUS, "Algebra %s already defined", nm ) ;
    }
    algebra->name = nm ;
	}
	switch (CURRENT_TERMINAL) {
	  case 25:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 11:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 25:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRprimitive_Hlist (&ZIp);
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    algebra->primitives = APPEND_list ( algebra->primitives, (ZIp) ) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 9:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 25:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRidentity_Hlist (&ZIi);
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    algebra->identities = APPEND_list ( algebra->identities, (ZIi) ) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 12:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 25:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRstructure_Hlist (&ZIs);
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    algebra->structures = APPEND_list ( algebra->structures, (ZIs) ) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 13:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 25:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRunion_Hlist (&ZIu);
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    algebra->unions = APPEND_list ( algebra->unions, (ZIu) ) ;
	}
	switch (CURRENT_TERMINAL) {
	  case 8:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 25:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRextra_Hlist ();
	switch (CURRENT_TERMINAL) {
	  case 34:
	    break;
	  case 49:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    SAVE_LEXER (49);
    return;
}

static void
ZRenumerator_Hlist PROTO_N ((ZOp))
  PROTO_T (ECONST_P_LIST *ZOp)
{
    ECONST_P_LIST ZIp;

    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    string ZIs;
	    ECONST_P ZIq;
	    ECONST_P_LIST ZIr;

	    {

    ZIs = xstrcpy ( token_buff ) ;
	    }
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 32:
		    {
			number ZIn;

			ADVANCE_LEXER;
			ZRexpression (&ZIn);
			if ((CURRENT_TERMINAL) == 49) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    enum_value = (ZIn) ;
			}
		    }
		    break;
		  default:
		    break;
		}
	    }
	    {

    number v = enum_value++ ;
    if ( v > enum_max ) enum_max = v ;
    (ZIq) = MAKE_ptr ( SIZE_ec ) ;
    MAKE_ec ( (ZIs), v, (ZIq) ) ;
    CONS_ptr ( (ZIq), enum_list, enum_list ) ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 27:
		    {
			ADVANCE_LEXER;
			ZRenumerator_Hlist (&ZIr);
			if ((CURRENT_TERMINAL) == 49) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  default:
		    {
			{

    (ZIr) = NULL_list ( ECONST_P ) ;
			}
		    }
		    break;
		}
	    }
	    {

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZIp) = NULL_list ( ECONST_P ) ;
	    }
	}
	break;
      case 49:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRcomponent_Hgroup PROTO_N ((ZOp))
  PROTO_T (COMPONENT_P_LIST *ZOp)
{
    COMPONENT_P_LIST ZIp;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 37:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRcomponent_Hlist (&ZIp);
	switch (CURRENT_TERMINAL) {
	  case 22:
	    break;
	  case 49:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRnew_Hunit PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 49) {
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
	{

    new_format = 1 ;
	}
	switch (CURRENT_TERMINAL) {
	  case 0:
	    {

    ZIm = xstrcpy ( token_buff ) ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    string nm = (ZIm) ;
    if ( !new_format ) error ( ERROR_WARNING, "Old style algebra syntax" ) ;
    if ( find_algebra ( nm ) ) {
	error ( ERROR_SERIOUS, "Algebra %s already defined", nm ) ;
    }
    algebra->name = nm ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 38:
		{
		    number ZIa;
		    number ZIb;

		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 1:
			{

    ZIa = token_value ;
			}
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
		    switch (CURRENT_TERMINAL) {
		      case 1:
			{

    ZIb = token_value ;
			}
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
		    {

    algebra->major_no = ( int ) (ZIa) ;
    algebra->minor_no = ( int ) (ZIb) ;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	switch (CURRENT_TERMINAL) {
	  case 25:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRnew_Hitem_Hlist ();
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (49);
    return;
}

static void
ZRidentity_Hdefn PROTO_N ((ZIi, ZOp))
  PROTO_T (CLASS_ID_P ZIi X IDENTITY_P *ZOp)
{
    IDENTITY_P ZIp;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	TYPE_P ZIt;

	ZRtype (&ZIt);
	switch (CURRENT_TERMINAL) {
	  case 45:
	    break;
	  case 49:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    TYPE r ;
    TYPE_P t ;
    (ZIp) = MAKE_ptr ( SIZE_ident ) ;
    MAKE_ident ( (ZIi), (ZIt), (ZIp) ) ;
    t = MAKE_ptr ( SIZE_type ) ;
    MAKE_type_ident ( 0, (ZIp), r ) ;
    COPY_type ( t, r ) ;
    IGNORE register_type ( t ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRmult_Hexp PROTO_N ((ZO261))
  PROTO_T (number *ZO261)
{
    number ZI261;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	number ZIn;

	ZRunary_Hexp (&ZIn);
	ZR262 (ZIn, &ZI261);
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZO261 = ZI261;
}

void
read_calculus PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	{

    new_format = 0 ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 3:
		{
		    ZRnew_Hunit ();
		    if ((CURRENT_TERMINAL) == 49) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      case 0:
		{
		    ZRold_Hunit ();
		    if ((CURRENT_TERMINAL) == 49) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	switch (CURRENT_TERMINAL) {
	  case 31:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    {
	{

    error ( ERROR_SERIOUS, "Syntax error" ) ;
	}
    }
}

static void
ZRtype PROTO_N ((ZOt))
  PROTO_T (TYPE_P *ZOt)
{
    TYPE_P ZIt;

    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    string ZIi;

	    {

    ZIi = xstrcpy ( token_buff ) ;
	    }
	    ADVANCE_LEXER;
	    {

    (ZIt) = find_type ( algebra, (ZIi) ) ;
	    }
	}
	break;
      case 15:
	{
	    TYPE_P ZIs;

	    ADVANCE_LEXER;
	    ZRtype (&ZIs);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = compound_type ( type_list_tag, (ZIs), 0 ) ;
	    }
	}
	break;
      case 16:
	{
	    TYPE_P ZIs;

	    ADVANCE_LEXER;
	    ZRtype (&ZIs);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = compound_type ( type_ptr_tag, (ZIs), 0 ) ;
	    }
	}
	break;
      case 17:
	{
	    TYPE_P ZIs;

	    ADVANCE_LEXER;
	    ZRtype (&ZIs);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = compound_type ( type_stack_tag, (ZIs), 0 ) ;
	    }
	}
	break;
      case 18:
	{
	    TYPE_P ZIs;

	    ADVANCE_LEXER;
	    ZRtype (&ZIs);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = compound_type ( type_vec_tag, (ZIs), 0 ) ;
	    }
	}
	break;
      case 19:
	{
	    TYPE_P ZIs;

	    ADVANCE_LEXER;
	    ZRtype (&ZIs);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = compound_type ( type_vec_ptr_tag, (ZIs), 0 ) ;
	    }
	}
	break;
      case 49:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    {
	{

    error ( ERROR_SERIOUS, "Type expected" ) ;
    (ZIt) = find_type ( algebra, "ERROR!" ) ;
	}
    }
  ZL0:;
    *ZOt = ZIt;
}

static void
ZRstructure_Hdefn PROTO_N ((ZIi, ZIj, ZOp))
  PROTO_T (CLASS_ID_P ZIi X string ZIj X STRUCTURE_P *ZOp)
{
    STRUCTURE_P ZIp;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	COMPONENT_P_LIST ZIc;

	ZRcomponent_Hgroup (&ZIc);
	switch (CURRENT_TERMINAL) {
	  case 45:
	    break;
	  case 49:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

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
    IGNORE register_type ( t ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRcomponent_Hlist PROTO_N ((ZOp))
  PROTO_T (COMPONENT_P_LIST *ZOp)
{
    COMPONENT_P_LIST ZIp;

    switch (CURRENT_TERMINAL) {
      case 0: case 15: case 16: case 17: case 18:
      case 19:
	{
	    TYPE_P ZIt;
	    COMPONENT_P_LIST ZIq;
	    COMPONENT_P_LIST ZIr;

	    ZRtype (&ZIt);
	    ZRcomponent_Hdecl (ZIt, &ZIq);
	    switch (CURRENT_TERMINAL) {
	      case 45:
		break;
	      case 49:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRcomponent_Hlist (&ZIr);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIp) = APPEND_list ( (ZIq), (ZIr) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZIp) = NULL_list ( COMPONENT_P ) ;
	    }
	}
	break;
      case 49:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRextended_Htype PROTO_N ((ZOt))
  PROTO_T (TYPE_P *ZOt)
{
    TYPE_P ZIt;

    switch (CURRENT_TERMINAL) {
      case 2:
	{
	    string ZIs;

	    {

    ZIs = xstrcpy ( token_buff ) ;
	    }
	    ADVANCE_LEXER;
	    {

    TYPE r ;
    (ZIt) = MAKE_ptr ( SIZE_type ) ;
    MAKE_type_quote ( 0, (ZIs), r ) ;
    COPY_type ( (ZIt), r ) ;
	    }
	}
	break;
      case 0: case 15: case 16: case 17: case 18:
      case 19:
	{
	    ZRtype (&ZIt);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 49:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    {
	{

    error ( ERROR_SERIOUS, "Type expected" ) ;
    (ZIt) = find_type ( algebra, "ERROR!" ) ;
	}
    }
  ZL0:;
    *ZOt = ZIt;
}

static void
ZRprimitive_Hlist PROTO_N ((ZOp))
  PROTO_T (PRIMITIVE_P_LIST *ZOp)
{
    PRIMITIVE_P_LIST ZIp;

    switch (CURRENT_TERMINAL) {
      case 0: case 25: case 34:
	{
	    CLASS_ID_P ZIi;
	    PRIMITIVE_P ZIq;
	    PRIMITIVE_P_LIST ZIr;

	    ZRclass_Hid (&ZIi);
	    switch (CURRENT_TERMINAL) {
	      case 25:
		break;
	      case 49:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRprimitive_Hdefn (ZIi, &ZIq);
	    ZRprimitive_Hlist (&ZIr);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZIp) = NULL_list ( PRIMITIVE_P ) ;
	    }
	}
	break;
      case 49:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZR209 PROTO_N ((ZOj))
  PROTO_T (string *ZOj)
{
    string ZIj;

    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    {

    ZIj = xstrcpy ( token_buff ) ;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 41:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      default:
	{
	    {

    (ZIj) = NULL ;
	    }
	}
	break;
      case 49:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOj = ZIj;
}

static void
ZRargument_Hlist PROTO_N ((ZOp))
  PROTO_T (ARGUMENT_P_LIST *ZOp)
{
    ARGUMENT_P_LIST ZIp;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	TYPE_P ZIt;
	ARGUMENT_P_LIST ZIq;
	ARGUMENT_P_LIST ZIr;

	ZRextended_Htype (&ZIt);
	ZRargument_Hdecl (ZIt, &ZIq);
	{
	    switch (CURRENT_TERMINAL) {
	      case 45:
		{
		    ADVANCE_LEXER;
		    ZRargument_Hlist (&ZIr);
		    if ((CURRENT_TERMINAL) == 49) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIr) = NULL_list ( ARGUMENT_P ) ;
		    }
		}
		break;
	      case 49:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	{

    (ZIp) = APPEND_list ( (ZIq), (ZIr) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRexpression PROTO_N ((ZOn))
  PROTO_T (number *ZOn)
{
    number ZIn;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	ZRor_Hexp (&ZIn);
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOn = ZIn;
}

static void
ZRxor_Hexp PROTO_N ((ZO245))
  PROTO_T (number *ZO245)
{
    number ZI245;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	number ZIn;

	ZRand_Hexp (&ZIn);
	ZR246 (ZIn, &ZI245);
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZO245 = ZI245;
}

static void
ZRidentity_Hlist PROTO_N ((ZOp))
  PROTO_T (IDENTITY_P_LIST *ZOp)
{
    IDENTITY_P_LIST ZIp;

    switch (CURRENT_TERMINAL) {
      case 0: case 25: case 34:
	{
	    CLASS_ID_P ZIi;
	    IDENTITY_P ZIq;
	    IDENTITY_P_LIST ZIr;

	    ZRclass_Hid (&ZIi);
	    switch (CURRENT_TERMINAL) {
	      case 25:
		break;
	      case 49:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRidentity_Hdefn (ZIi, &ZIq);
	    ZRidentity_Hlist (&ZIr);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZIp) = NULL_list ( IDENTITY_P ) ;
	    }
	}
	break;
      case 49:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRor_Hexp PROTO_N ((ZO241))
  PROTO_T (number *ZO241)
{
    number ZI241;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	number ZIn;

	ZRxor_Hexp (&ZIn);
	ZR242 (ZIn, &ZI241);
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZO241 = ZI241;
}

static void
ZRunion_Hsingle PROTO_N ((ZOp))
  PROTO_T (UNION_P_LIST *ZOp)
{
    UNION_P_LIST ZIp;

    if ((CURRENT_TERMINAL) == 49) {
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
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZIr) = NULL_list ( UNION_P ) ;
	}
	{

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRstructure_Hlist PROTO_N ((ZOp))
  PROTO_T (STRUCTURE_P_LIST *ZOp)
{
    STRUCTURE_P_LIST ZIp;

    switch (CURRENT_TERMINAL) {
      case 0: case 25: case 34:
	{
	    CLASS_ID_P ZIi;
	    string ZIj;
	    STRUCTURE_P ZIq;
	    STRUCTURE_P_LIST ZIr;

	    ZRclass_Hid (&ZIi);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIj) = NULL ;
	    }
	    ZRstructure_Hdefn (ZIi, ZIj, &ZIq);
	    ZRstructure_Hlist (&ZIr);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZIp) = NULL_list ( STRUCTURE_P ) ;
	    }
	}
	break;
      case 49:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRunion_Hdefn_Hold PROTO_N ((ZIi, ZOp))
  PROTO_T (CLASS_ID_P ZIi X UNION_P *ZOp)
{
    UNION_P ZIp;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	COMPONENT_P_LIST ZIc;
	FIELD_P_LIST ZIf;
	MAP_P_LIST ZIm;
	string ZIj;

	{
	    switch (CURRENT_TERMINAL) {
	      case 37:
		{
		    ZRcomponent_Hgroup (&ZIc);
		    if ((CURRENT_TERMINAL) == 49) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIc) = NULL_list ( COMPONENT_P ) ;
		    }
		}
		break;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 0: case 34:
		{
		    ZRfield_Hlist (&ZIf);
		    if ((CURRENT_TERMINAL) == 49) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIf) = NULL_list ( FIELD_P ) ;
		    }
		}
		break;
	    }
	}
	switch (CURRENT_TERMINAL) {
	  case 14:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 10:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 39:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRmap_Hlist (&ZIm);
	switch (CURRENT_TERMINAL) {
	  case 24:
	    break;
	  case 49:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    (ZIj) = NULL ;
	}
	{

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
		if ( streq ( n, nn ) ) {
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
    IGNORE register_type ( t ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRenum_Hsingle PROTO_N ((ZOp))
  PROTO_T (ENUM_P_LIST *ZOp)
{
    ENUM_P_LIST ZIp;

    if ((CURRENT_TERMINAL) == 49) {
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
	{
	    switch (CURRENT_TERMINAL) {
	      case 33:
		{
		    ADVANCE_LEXER;
		    {
 (ZIl) = 0 ; 
		    }
		}
		break;
	      default:
		{
		    {
 (ZIl) = 1 ; 
		    }
		}
		break;
	    }
	}
	ZRclass_Hid (&ZIi);
	switch (CURRENT_TERMINAL) {
	  case 32:
	    break;
	  case 49:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 0:
		{
		    string ZIj;

		    {

    ZIj = xstrcpy ( token_buff ) ;
		    }
		    ADVANCE_LEXER;
		    {

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
		    }
		    switch (CURRENT_TERMINAL) {
		      case 41:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		{
		    {

    (ZIf) = NULL_list ( ECONST_P ) ;
		    }
		}
		break;
	    }
	}
	switch (CURRENT_TERMINAL) {
	  case 37:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRenumerator_Hlist (&ZIe);
	switch (CURRENT_TERMINAL) {
	  case 22:
	    break;
	  case 49:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 45:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

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
    IGNORE register_type ( t ) ;
	}
	{

    (ZIr) = NULL_list ( ENUM_P ) ;
	}
	{

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRfield_Hid_Hlist PROTO_N ((ZIn, ZOp))
  PROTO_T (int ZIn X FIELD_P_LIST *ZOp)
{
    FIELD_P_LIST ZIp;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	string ZIi;
	COMPONENT_P_LIST ZIc;
	FIELD_P ZIq;
	FIELD_P_LIST ZIr;

	switch (CURRENT_TERMINAL) {
	  case 0:
	    {

    ZIi = xstrcpy ( token_buff ) ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    (ZIc) = NULL_list ( COMPONENT_P ) ;
	}
	{

    (ZIq) = MAKE_ptr ( SIZE_fld ) ;
    MAKE_fld ( (ZIi), 0, (ZIn), 0, NULL_ptr ( FIELD ),  (ZIc), (ZIq) ) ;
    no_fields++ ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 27:
		{
		    ADVANCE_LEXER;
		    ZRfield_Hid_Hlist (ZIn, &ZIr);
		    if ((CURRENT_TERMINAL) == 49) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIr) = NULL_list ( FIELD_P ) ;
		    }
		}
		break;
	    }
	}
	{

    CONS_ptr ( (ZIq), (ZIr), (ZIp) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZR242 PROTO_N ((ZI240, ZO241))
  PROTO_T (number ZI240 X number *ZO241)
{
    number ZI241;

  ZL2_242:;
    switch (CURRENT_TERMINAL) {
      case 40:
	{
	    number ZIp;
	    number ZIn;

	    ADVANCE_LEXER;
	    ZRxor_Hexp (&ZIp);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIn) = (ZI240) | (ZIp) ;
	    }
	    ZI240 = ZIn;
	    goto ZL2_242;
	}
	/*UNREACHED*/
      default:
	{
	    ZI241 = ZI240;
	}
	break;
      case 49:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZO241 = ZI241;
}

static void
ZRfield_Hlist PROTO_N ((ZOp))
  PROTO_T (FIELD_P_LIST *ZOp)
{
    FIELD_P_LIST ZIp;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	int ZIn;
	FIELD_P_LIST ZIq;
	string ZIj;
	COMPONENT_P_LIST ZIc;
	FIELD_P_LIST ZIr;

	{
	    switch (CURRENT_TERMINAL) {
	      case 34:
		{
		    ADVANCE_LEXER;
		    ZR265 (&ZIn);
		    if ((CURRENT_TERMINAL) == 49) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {
 (ZIn) = 0 ; 
		    }
		}
		break;
	    }
	}
	ZRfield_Hid_Hlist (ZIn, &ZIq);
	switch (CURRENT_TERMINAL) {
	  case 21:
	    break;
	  case 49:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR209 (&ZIj);
	ZRcomponent_Hgroup (&ZIc);
	if ((CURRENT_TERMINAL) == 49) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

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
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 27:
		{
		    ADVANCE_LEXER;
		    ZRfield_Hlist (&ZIr);
		    if ((CURRENT_TERMINAL) == 49) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIr) = NULL_list ( FIELD_P ) ;
		    }
		}
		break;
	    }
	}
	{

    (ZIp) = APPEND_list ( (ZIq), (ZIr) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRunion_Hdefn_Hnew PROTO_N ((ZIi, ZOp))
  PROTO_T (CLASS_ID_P ZIi X UNION_P *ZOp)
{
    UNION_P ZIp;

    if ((CURRENT_TERMINAL) == 49) {
	return;
    }
    {
	COMPONENT_P_LIST ZIc;
	string ZIj;
	FIELD_P_LIST ZIf;
	MAP_P_LIST ZIm;

	switch (CURRENT_TERMINAL) {
	  case 32:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 37:
		{
		    ZRcomponent_Hgroup (&ZIc);
		    if ((CURRENT_TERMINAL) == 49) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    (ZIj) = NULL ;
		    }
		}
		break;
	      case 0:
		{
		    {

    (ZIc) = NULL_list ( COMPONENT_P ) ;
		    }
		    {

    ZIj = xstrcpy ( token_buff ) ;
		    }
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	switch (CURRENT_TERMINAL) {
	  case 41:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 37:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRfield_Hlist (&ZIf);
	switch (CURRENT_TERMINAL) {
	  case 22:
	    break;
	  case 49:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 25:
		{
		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 39:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    ZRmap_Hlist (&ZIm);
		    switch (CURRENT_TERMINAL) {
		      case 24:
			break;
		      case 49:
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
		    {

    (ZIm) = NULL_list ( MAP_P ) ;
		    }
		}
		break;
	    }
	}
	switch (CURRENT_TERMINAL) {
	  case 45:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

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
		if ( streq ( n, nn ) ) {
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
    IGNORE register_type ( t ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZR246 PROTO_N ((ZI244, ZO245))
  PROTO_T (number ZI244 X number *ZO245)
{
    number ZI245;

  ZL2_246:;
    switch (CURRENT_TERMINAL) {
      case 47:
	{
	    number ZIp;
	    number ZIn;

	    ADVANCE_LEXER;
	    ZRand_Hexp (&ZIp);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIn) = (ZI244) ^ (ZIp) ;
	    }
	    ZI244 = ZIn;
	    goto ZL2_246;
	}
	/*UNREACHED*/
      default:
	{
	    ZI245 = ZI244;
	}
	break;
      case 49:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZO245 = ZI245;
}

static void
ZR250 PROTO_N ((ZI248, ZO249))
  PROTO_T (number ZI248 X number *ZO249)
{
    number ZI249;

  ZL2_250:;
    switch (CURRENT_TERMINAL) {
      case 20:
	{
	    number ZIp;
	    number ZIn;

	    ADVANCE_LEXER;
	    ZRshift_Hexp (&ZIp);
	    if ((CURRENT_TERMINAL) == 49) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIn) = (ZI248) & (ZIp) ;
	    }
	    ZI248 = ZIn;
	    goto ZL2_250;
	}
	/*UNREACHED*/
      default:
	{
	    ZI249 = ZI248;
	}
	break;
      case 49:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (49);
    return;
  ZL0:;
    *ZO249 = ZI249;
}

/* BEGINNING OF TRAILER */



/* END OF FILE */
