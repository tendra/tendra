/*
 * Automatically generated from the files:
 *	/u/g/release/Source/src/utilities/make_err/syntax.sid
 * and
 *	/u/g/release/Source/src/utilities/make_err/syntax.act
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
#include "errors.h"
#include "entry_ops.h"
#include "map_ops.h"
#include "msg_ops.h"
#include "name_ops.h"
#include "param_ops.h"
#include "error.h"
#include "lex.h"
#include "process.h"
#include "syntax.h"
#include "xalloc.h"


/*
    PARSER TYPES

    These types give the implementation of the types used in the syntax.
*/

typedef LIST ( ENTRY ) LIST_ENTRY ;
typedef LIST ( MAP ) LIST_MAP ;
typedef LIST ( MESSAGE ) LIST_MESSAGE ;
typedef LIST ( NAME ) LIST_NAME ;
typedef LIST ( PARAM ) LIST_PARAM ;
typedef LIST ( PROPERTY ) LIST_PROPERTY ;


/*
    COUNTER VARIABLE

    This variable is used to keep count of the position in a name or
    parameter list.
*/

static int counter = 0 ;


/*
    FIND A NAME

    This routine searches the name list p for an identifier matching id.
    The null name is returned if no matching name is found.
*/

static NAME find_name
    PROTO_N ( ( p, id ) )
    PROTO_T ( LIST ( NAME ) p X string id )
{
    while ( !IS_NULL_list ( p ) ) {
	NAME a = DEREF_name ( HEAD_list ( p ) ) ;
	string nm = DEREF_string ( name_id ( a ) ) ;
	if ( streq ( nm, id ) ) return ( a ) ;
	p = TAIL_list ( p ) ;
    }
    return ( NULL_name ) ;
}


/*
    FIND A PARAMETER

    This routine searches the parameter list p for an identifier matching
    id.  The null parameter is returned if no matching parameter is found.
*/

static PARAM find_param
    PROTO_N ( ( p, id ) )
    PROTO_T ( LIST ( PARAM ) p X string id )
{
    while ( !IS_NULL_list ( p ) ) {
	PARAM a = DEREF_param ( HEAD_list ( p ) ) ;
	string nm = DEREF_string ( param_name ( a ) ) ;
	if ( streq ( nm, id ) ) return ( a ) ;
	p = TAIL_list ( p ) ;
    }
    return ( NULL_param ) ;
}


/*
    COMPILATION MODE

    We allow unreached code and switch off the variable analysis in the
    automatically generated sections.
*/

#if FS_TENDRA
#pragma TenDRA begin
#pragma TenDRA variable analysis off
#ifndef OLD_PRODUCER
#pragma TenDRA unreachable code allow
#endif
#endif



/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRparam_Hlist PROTO_S ((LIST_PARAM *));
static void ZRname_Hlist PROTO_S ((LIST_NAME *, LIST_NAME *, LIST_NAME *));
static void ZRname_Hseq PROTO_S ((LIST_NAME *, LIST_NAME *, LIST_NAME *));
static void ZRprops_Hlist PROTO_S ((LIST_PROPERTY *));
static void ZRmap_Hlist PROTO_S ((LIST_PARAM, LIST_MAP *));
static void ZRentry PROTO_S ((ENTRY *));
extern void read_errors PROTO_S ((void));
static void ZRmessage_Hlist PROTO_S ((LIST_PARAM, LIST_MESSAGE *));
static void ZRsignature PROTO_S ((LIST_PARAM *));
static void ZRentries_Hlist PROTO_S ((LIST_ENTRY *));

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRparam_Hlist PROTO_N ((ZOp))
  PROTO_T (LIST_PARAM *ZOp)
{
    LIST_PARAM ZIp;

    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	string ZIa;
	TYPE ZIt;
	string ZIb;
	PARAM ZIc;
	LIST_PARAM ZIq;

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
	{

    NAME n = find_name ( all_types, (ZIa) ) ;
    if ( IS_NULL_name ( n ) ) {
	error ( ERROR_SERIOUS, "Type '%s' not defined", (ZIa) ) ;
	MAKE_name_basic ( (ZIa), 0, n ) ;
    }
    (ZIt) = n ;
	}
	switch (CURRENT_TERMINAL) {
	  case 16:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 0:
	    {

    ZIb = xstrcpy ( token_buff ) ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    MAKE_param_basic ( (ZIt), (ZIb), counter, (ZIc) ) ;
    counter++ ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 17:
		{
		    ADVANCE_LEXER;
		    ZRparam_Hlist (&ZIq);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIq) = NULL_list ( PARAM ) ;
		    }
		}
		break;
	    }
	}
	{

    string id = DEREF_string ( param_name ( (ZIc) ) ) ;
    PARAM b = find_param ( (ZIq), id ) ;
    if ( !IS_NULL_param ( b ) ) {
	error ( ERROR_SERIOUS, "Parameter '%s' defined twice", id ) ;
    }
    CONS_param ( (ZIc), (ZIq), (ZIp) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (26);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRname_Hlist PROTO_N ((ZOp, ZOq, ZOr))
  PROTO_T (LIST_NAME *ZOp X LIST_NAME *ZOq X LIST_NAME *ZOr)
{
    LIST_NAME ZIp;
    LIST_NAME ZIq;
    LIST_NAME ZIr;

    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    ZRname_Hseq (&ZIp, &ZIq, &ZIr);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZIp) = NULL_list ( NAME ) ;
	    }
	    {

    (ZIq) = NULL_list ( NAME ) ;
	    }
	    {

    (ZIr) = NULL_list ( NAME ) ;
	    }
	}
	break;
      case 26:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (26);
    return;
  ZL0:;
    *ZOp = ZIp;
    *ZOq = ZIq;
    *ZOr = ZIr;
}

static void
ZRname_Hseq PROTO_N ((ZOp, ZOq, ZOr))
  PROTO_T (LIST_NAME *ZOp X LIST_NAME *ZOq X LIST_NAME *ZOr)
{
    LIST_NAME ZIp;
    LIST_NAME ZIq;
    LIST_NAME ZIr;

    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	string ZIa;
	NAME ZIn;
	NAME ZIm;
	NAME ZIk;
	LIST_NAME ZIp1;
	LIST_NAME ZIq1;
	LIST_NAME ZIr1;

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
	{

    MAKE_name_basic ( (ZIa), counter, (ZIn) ) ;
    counter++ ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 18:
		{
		    string ZIb;
		    NAME ZIk1;

		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 0:
			{

    ZIb = xstrcpy ( token_buff ) ;
			}
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    {

    MAKE_name_basic ( (ZIb), 0, (ZIm) ) ;
		    }
		    {
			switch (CURRENT_TERMINAL) {
			  case 19:
			    {
				string ZIc;

				ADVANCE_LEXER;
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

    MAKE_name_basic ( (ZIc), 0, (ZIk1) ) ;
				}
			    }
			    break;
			  default:
			    {
				ZIk1 = ZIm;
			    }
			    break;
			}
		    }
		    ZIk = ZIk1;
		}
		break;
	      default:
		{
		    ZIm = ZIn;
		    ZIk = ZIn;
		}
		break;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 17:
		{
		    ADVANCE_LEXER;
		    ZRname_Hseq (&ZIp1, &ZIq1, &ZIr1);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIp1) = NULL_list ( NAME ) ;
		    }
		    {

    (ZIq1) = NULL_list ( NAME ) ;
		    }
		    {

    (ZIr1) = NULL_list ( NAME ) ;
		    }
		}
		break;
	    }
	}
	{

    string id = DEREF_string ( name_id ( (ZIn) ) ) ;
    NAME b = find_name ( (ZIp1), id ) ;
    if ( !IS_NULL_name ( b ) ) {
	error ( ERROR_SERIOUS, "Name '%s' given twice in list", id ) ;
    }
    CONS_name ( (ZIn), (ZIp1), (ZIp) ) ;
	}
	{

    CONS_name ( (ZIm), (ZIq1), (ZIq) ) ;
	}
	{

    CONS_name ( (ZIk), (ZIr1), (ZIr) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (26);
    return;
  ZL0:;
    *ZOp = ZIp;
    *ZOq = ZIq;
    *ZOr = ZIr;
}

static void
ZRprops_Hlist PROTO_N ((ZOp))
  PROTO_T (LIST_PROPERTY *ZOp)
{
    LIST_PROPERTY ZIp;

    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	string ZIa;
	PROPERTY ZIb;
	LIST_PROPERTY ZIq;

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
	{

    NAME n = find_name ( all_props, (ZIa) ) ;
    if ( IS_NULL_name ( n ) ) {
	error ( ERROR_SERIOUS, "Property '%s' not defined", (ZIa) ) ;
	MAKE_name_basic ( (ZIa), 0, n ) ;
    }
    (ZIb) = n ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 17:
		{
		    ADVANCE_LEXER;
		    ZRprops_Hlist (&ZIq);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIq) = NULL_list ( PROPERTY ) ;
		    }
		}
		break;
	    }
	}
	{

    CONS_name ( (ZIb), (ZIq), (ZIp) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (26);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRmap_Hlist PROTO_N ((ZIs, ZOp))
  PROTO_T (LIST_PARAM ZIs X LIST_MAP *ZOp)
{
    LIST_MAP ZIp;

    switch (CURRENT_TERMINAL) {
      case 5:
	{
	    string ZIa;
	    KEY ZIk;
	    LIST_MESSAGE ZIm1;
	    LIST_MESSAGE ZIm2;
	    MAP ZIn;
	    LIST_MAP ZIq;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 20:
		break;
	      default:
		goto ZL1;
	    }
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
	      case 21:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    NAME n = find_name ( all_keys, (ZIa) ) ;
    if ( IS_NULL_name ( n ) ) {
	error ( ERROR_SERIOUS, "Key '%s' not defined", (ZIa) ) ;
    }
    (ZIk) = n ;
	    }
	    ZRmessage_Hlist (ZIs, &ZIm1);
	    {
		switch (CURRENT_TERMINAL) {
		  case 19:
		    {
			ADVANCE_LEXER;
			ZRmessage_Hlist (ZIs, &ZIm2);
			if ((CURRENT_TERMINAL) == 26) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  default:
		    {
			ZIm2 = ZIm1;
		    }
		    break;
		  case 26:
		    RESTORE_LEXER;
		    goto ZL1;
		}
	    }
	    {

    MAKE_map_basic  ( (ZIk), (ZIm1), (ZIm2), (ZIn) ) ;
	    }
	    ZRmap_Hlist (ZIs, &ZIq);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_map ( (ZIn), (ZIq), (ZIp) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZIp) = NULL_list ( MAP ) ;
	    }
	}
	break;
      case 26:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (26);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRentry PROTO_N ((ZOe))
  PROTO_T (ENTRY *ZOe)
{
    ENTRY ZIe;

    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	string ZIa;
	LIST_PARAM ZIs;
	string ZIb;
	USAGE ZIu;
	USAGE ZIv;
	LIST_PROPERTY ZIp;
	LIST_MAP ZIm;

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
	  case 20:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRsignature (&ZIs);
	switch (CURRENT_TERMINAL) {
	  case 21:
	    break;
	  case 26:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 22:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 2:
		{
		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 16:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 0:
			{

    ZIb = xstrcpy ( token_buff ) ;
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

    (ZIb) = NULL ;
		    }
		}
		break;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 11:
		{
		    string ZIc;
		    USAGE ZIw;

		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 16:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
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

    NAME n = find_name ( all_usages, (ZIc) ) ;
    if ( IS_NULL_name ( n ) ) {
	error ( ERROR_SERIOUS, "Usage '%s' not defined", (ZIc) ) ;
	MAKE_name_basic ( (ZIc), 0, n ) ;
    }
    (ZIu) = n ;
		    }
		    {
			switch (CURRENT_TERMINAL) {
			  case 19:
			    {
				string ZId;

				ADVANCE_LEXER;
				switch (CURRENT_TERMINAL) {
				  case 0:
				    {

    ZId = xstrcpy ( token_buff ) ;
				    }
				    break;
				  default:
				    goto ZL1;
				}
				ADVANCE_LEXER;
				{

    NAME n = find_name ( all_usages, (ZId) ) ;
    if ( IS_NULL_name ( n ) ) {
	error ( ERROR_SERIOUS, "Usage '%s' not defined", (ZId) ) ;
	MAKE_name_basic ( (ZId), 0, n ) ;
    }
    (ZIw) = n ;
				}
			    }
			    break;
			  default:
			    {
				ZIw = ZIu;
			    }
			    break;
			}
		    }
		    ZIv = ZIw;
		}
		break;
	      default:
		{
		    {

    (ZIu) = NULL_name ;
		    }
		    {

    (ZIv) = NULL_name ;
		    }
		}
		break;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 8:
		{
		    LIST_PROPERTY ZIq;

		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 16:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    {
			switch (CURRENT_TERMINAL) {
			  case 0:
			    {
				ZRprops_Hlist (&ZIq);
				if ((CURRENT_TERMINAL) == 26) {
				    RESTORE_LEXER;
				    goto ZL1;
				}
			    }
			    break;
			  default:
			    {
				{

    (ZIq) = NULL_list ( PROPERTY ) ;
				}
			    }
			    break;
			}
		    }
		    ZIp = ZIq;
		}
		break;
	      default:
		{
		    {

    (ZIp) = NULL_list ( PROPERTY ) ;
		    }
		}
		break;
	    }
	}
	ZRmap_Hlist (ZIs, &ZIm);
	switch (CURRENT_TERMINAL) {
	  case 23:
	    break;
	  case 26:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    MAKE_entry_basic ( (ZIa), (ZIb), (ZIs), (ZIu), (ZIv), (ZIp), (ZIm), (ZIe) ) ;
    counter = 0 ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (26);
    return;
  ZL0:;
    *ZOe = ZIe;
}

void
read_errors PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 26) {
	return;
    }
    {
	LIST_NAME ZIt1;
	LIST_NAME ZIt2;
	LIST_NAME ZIt3;
	LIST_NAME ZIp1;
	LIST_NAME ZIp2;
	LIST_NAME ZIp3;
	LIST_NAME ZIk1;
	LIST_NAME ZIk2;
	LIST_NAME ZIk3;
	LIST_NAME ZIu1;
	LIST_NAME ZIu2;
	LIST_NAME ZIu3;
	LIST_ENTRY ZIe;

	{
	    switch (CURRENT_TERMINAL) {
	      case 3:
		{
		    string ZId;
		    string ZI158;

		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 16:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 0:
			{

    ZId = xstrcpy ( token_buff ) ;
			}
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    {
			switch (CURRENT_TERMINAL) {
			  case 19:
			    {
				ADVANCE_LEXER;
				switch (CURRENT_TERMINAL) {
				  case 0:
				    {

    ZI158 = xstrcpy ( token_buff ) ;
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
				ZI158 = ZId;
			    }
			    break;
			}
		    }
		    {

    db_name = (ZId) ;
    db_name_alt = (ZI158) ;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 9:
		{
		    string ZIr;

		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 16:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 0:
			{

    ZIr = xstrcpy ( token_buff ) ;
			}
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    {

    rig_name = (ZIr) ;
		    }
		}
		break;
	      default:
		break;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 7:
		{
		    string ZIq1;
		    string ZIq2;
		    string ZIq3;

		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 16:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    {
			switch (CURRENT_TERMINAL) {
			  case 12:
			    {
				ADVANCE_LEXER;
				switch (CURRENT_TERMINAL) {
				  case 15:
				    break;
				  default:
				    goto ZL1;
				}
				ADVANCE_LEXER;
				switch (CURRENT_TERMINAL) {
				  case 0:
				    {

    ZIq1 = xstrcpy ( token_buff ) ;
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

    (ZIq1) = NULL ;
				}
			    }
			    break;
			}
		    }
		    {
			switch (CURRENT_TERMINAL) {
			  case 13:
			    {
				ADVANCE_LEXER;
				switch (CURRENT_TERMINAL) {
				  case 15:
				    break;
				  default:
				    goto ZL1;
				}
				ADVANCE_LEXER;
				switch (CURRENT_TERMINAL) {
				  case 0:
				    {

    ZIq2 = xstrcpy ( token_buff ) ;
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

    (ZIq2) = NULL ;
				}
			    }
			    break;
			}
		    }
		    {
			switch (CURRENT_TERMINAL) {
			  case 14:
			    {
				ADVANCE_LEXER;
				switch (CURRENT_TERMINAL) {
				  case 15:
				    break;
				  default:
				    goto ZL1;
				}
				ADVANCE_LEXER;
				switch (CURRENT_TERMINAL) {
				  case 0:
				    {

    ZIq3 = xstrcpy ( token_buff ) ;
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

    (ZIq3) = NULL ;
				}
			    }
			    break;
			}
		    }
		    {

    if ( (ZIq1) ) rig_comp_output = (ZIq1) ;
    if ( (ZIq2) ) rig_from_comp = (ZIq2) ;
    if ( (ZIq3) ) rig_from_db = (ZIq3) ;
		    }
		}
		break;
	      default:
		{
		    string ZIq1;
		    string ZIq2;
		    string ZIq3;

		    {

    (ZIq1) = NULL ;
		    }
		    {

    (ZIq2) = NULL ;
		    }
		    {

    (ZIq3) = NULL ;
		    }
		    {

    if ( (ZIq1) ) rig_comp_output = (ZIq1) ;
    if ( (ZIq2) ) rig_from_comp = (ZIq2) ;
    if ( (ZIq3) ) rig_from_db = (ZIq3) ;
		    }
		}
		break;
	    }
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 10:
		{
		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 16:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    ZRname_Hlist (&ZIt1, &ZIt2, &ZIt3);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIt1) = NULL_list ( NAME ) ;
		    }
		    {

    (ZIt2) = NULL_list ( NAME ) ;
		    }
		    {

    (ZIt3) = NULL_list ( NAME ) ;
		    }
		}
		break;
	    }
	}
	{

    all_types = (ZIt1) ;
    all_types_aux = (ZIt2) ;
    all_types_alt = (ZIt3) ;
    counter = 0 ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 8:
		{
		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 16:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    ZRname_Hlist (&ZIp1, &ZIp2, &ZIp3);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIp1) = NULL_list ( NAME ) ;
		    }
		    {

    (ZIp2) = NULL_list ( NAME ) ;
		    }
		    {

    (ZIp3) = NULL_list ( NAME ) ;
		    }
		}
		break;
	    }
	}
	{

    all_props = (ZIp1) ;
    all_props_aux = (ZIp2) ;
    all_props_alt = (ZIp3) ;
    counter = 0 ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 6:
		{
		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 16:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    ZRname_Hlist (&ZIk1, &ZIk2, &ZIk3);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIk1) = NULL_list ( NAME ) ;
		    }
		    {

    (ZIk2) = NULL_list ( NAME ) ;
		    }
		    {

    (ZIk3) = NULL_list ( NAME ) ;
		    }
		}
		break;
	    }
	}
	{

    all_keys = (ZIk1) ;
    all_keys_aux = (ZIk2) ;
    all_keys_alt = (ZIk3) ;
    counter = 0 ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 11:
		{
		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 16:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    ZRname_Hlist (&ZIu1, &ZIu2, &ZIu3);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIu1) = NULL_list ( NAME ) ;
		    }
		    {

    (ZIu2) = NULL_list ( NAME ) ;
		    }
		    {

    (ZIu3) = NULL_list ( NAME ) ;
		    }
		}
		break;
	    }
	}
	{

    all_usages = (ZIu1) ;
    all_usages_aux = (ZIu2) ;
    all_usages_alt = (ZIu3) ;
    counter = 0 ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 4:
		{
		    ADVANCE_LEXER;
		    switch (CURRENT_TERMINAL) {
		      case 16:
			break;
		      default:
			goto ZL1;
		    }
		    ADVANCE_LEXER;
		    ZRentries_Hlist (&ZIe);
		    if ((CURRENT_TERMINAL) == 26) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIe) = NULL_list ( ENTRY ) ;
		    }
		}
		break;
	    }
	}
	{

    all_entries = (ZIe) ;
    counter = 0 ;
	}
	switch (CURRENT_TERMINAL) {
	  case 24:
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
ZRmessage_Hlist PROTO_N ((ZIs, ZOp))
  PROTO_T (LIST_PARAM ZIs X LIST_MESSAGE *ZOp)
{
    LIST_MESSAGE ZIp;

    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    string ZIa;
	    PARAM ZIn;
	    MESSAGE ZIm;
	    LIST_MESSAGE ZIq;

	    {

    ZIa = xstrcpy ( token_buff ) ;
	    }
	    ADVANCE_LEXER;
	    {

    PARAM a = find_param ( (ZIs), (ZIa) ) ;
    if ( IS_NULL_param ( a ) ) {
	error ( ERROR_SERIOUS, "Parameter '%s' not defined", (ZIa) ) ;
    }
    (ZIn) = a ;
	    }
	    {

    if ( !IS_NULL_param ( (ZIn) ) ) {
	MAKE_msg_param ( (ZIn), (ZIm) ) ;
    } else {
	MAKE_msg_text ( "<error>", (ZIm) ) ;
    }
	    }
	    ZRmessage_Hlist (ZIs, &ZIq);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_msg ( (ZIm), (ZIq), (ZIp) ) ;
	    }
	}
	break;
      case 1:
	{
	    string ZIa;
	    MESSAGE ZIm;
	    LIST_MESSAGE ZIq;

	    {

    ZIa = xstrcpy ( token_buff ) ;
	    }
	    ADVANCE_LEXER;
	    {

    MAKE_msg_text ( (ZIa), (ZIm) ) ;
	    }
	    ZRmessage_Hlist (ZIs, &ZIq);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_msg ( (ZIm), (ZIq), (ZIp) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZIp) = NULL_list ( MESSAGE ) ;
	    }
	}
	break;
      case 26:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (26);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRsignature PROTO_N ((ZOp))
  PROTO_T (LIST_PARAM *ZOp)
{
    LIST_PARAM ZIp;

    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    ZRparam_Hlist (&ZIp);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZIp) = NULL_list ( PARAM ) ;
	    }
	}
	break;
      case 26:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (26);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRentries_Hlist PROTO_N ((ZOp))
  PROTO_T (LIST_ENTRY *ZOp)
{
    LIST_ENTRY ZIp;

    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    ENTRY ZIa;
	    LIST_ENTRY ZIq;

	    ZRentry (&ZIa);
	    ZRentries_Hlist (&ZIq);
	    if ((CURRENT_TERMINAL) == 26) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    CONS_entry ( (ZIa), (ZIq), (ZIp) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZIp) = NULL_list ( ENTRY ) ;
	    }
	}
	break;
      case 26:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (26);
    return;
  ZL0:;
    *ZOp = ZIp;
}

/* BEGINNING OF TRAILER */



/* END OF FILE */
