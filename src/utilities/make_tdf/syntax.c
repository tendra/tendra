/*
 * Automatically generated from the files:
 *	/u/g/release/Source/src/utilities/make_tdf/syntax.sid
 * and
 *	/u/g/release/Source/src/utilities/make_tdf/syntax.act
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
#include "tdf.h"
#include "cmd_ops.h"
#include "cons_ops.h"
#include "info_ops.h"
#include "link_ops.h"
#include "par_ops.h"
#include "sort_ops.h"
#include "spec_ops.h"
#include "error.h"
#include "input.h"
#include "lex.h"
#include "syntax.h"
#include "xalloc.h"


/*
    LOCAL TYPE ALIASES

    These definitions give the aliases used for compound types within the
    grammar.
*/

typedef LIST ( CONSTRUCT ) SID_CONS_LIST ;
typedef LIST ( LINKAGE ) SID_LINK_LIST ;
typedef LIST ( PARAMETER ) SID_PARAM_LIST ;


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

static void ZRlink_Hpack PROTO_S ((SID_LINK_LIST *));
static void ZRparam_Hlist PROTO_S ((SID_PARAM_LIST *));
static void ZRclist_Hitem PROTO_S ((void));
static void ZRslist_Hpack PROTO_S ((void));
static void ZRedge_Hlist PROTO_S ((void));
static void ZRkind_Hitem PROTO_S ((LINKAGE *));
static void ZRoption_Hlist PROTO_S ((void));
static void ZR139 PROTO_S ((CONSTRUCT *));
static void ZRold_Hsort_Hname PROTO_S ((SORT *));
static void ZR140 PROTO_S ((CONSTRUCT *));
static void ZR141 PROTO_S ((CONSTRUCT *));
static void ZRclist_Hlist PROTO_S ((void));
static void ZRlink_Hitem PROTO_S ((LINKAGE *));
static void ZRslist_Hitem PROTO_S ((void));
static void ZRkind_Hlist PROTO_S ((SID_LINK_LIST *));
static void ZRnew_Hsort_Hname PROTO_S ((SORT *));
static void ZRsort_Hpack PROTO_S ((void));
static void ZRany_Hname PROTO_S ((string *));
static void ZRlink_Hlist PROTO_S ((SID_LINK_LIST *));
static void ZRslist_Hlist PROTO_S ((void));
static void ZRsort_Hitem PROTO_S ((void));
static void ZRsort_Hlist PROTO_S ((void));
static void ZRconstruct_Hpack PROTO_S ((SORT, SID_CONS_LIST *));
static void ZRconstruct_Hextra PROTO_S ((CONSTRUCT));
static void ZRboundary_Hitem PROTO_S ((CONSTRUCT));
static void ZRconstruct_Hitem PROTO_S ((SORT, CONSTRUCT *));
static void ZRconstruct_Hlist PROTO_S ((SORT, SID_CONS_LIST *));
static void ZRparam_Hpack PROTO_S ((SID_PARAM_LIST *));
static void ZRedge_Hpack PROTO_S ((void));
extern void read_spec PROTO_S ((SPECIFICATION *));
static void ZRoption_Hpack PROTO_S ((void));
static void ZRclist_Hpack PROTO_S ((void));
static void ZRparam_Hitem PROTO_S ((PARAMETER *));
static void ZRedge_Hitem PROTO_S ((void));
static void ZRkind_Hpack PROTO_S ((SID_LINK_LIST *));
static void ZRnumber_Hlist PROTO_S ((CONSTRUCT));
static void ZRoption_Hitem PROTO_S ((void));

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRlink_Hpack PROTO_N ((ZOp))
  PROTO_T (SID_LINK_LIST *ZOp)
{
    SID_LINK_LIST ZIp;

    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	SID_LINK_LIST ZIq;

	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 27:
		{
		    ZRlink_Hlist (&ZIq);
		    if ((CURRENT_TERMINAL) == 32) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIq) = NULL_list ( LINKAGE ) ;
		    }
		}
		break;
	    }
	}
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZIp = ZIq;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (32);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRparam_Hlist PROTO_N ((ZOp))
  PROTO_T (SID_PARAM_LIST *ZOp)
{
    SID_PARAM_LIST ZIp;

    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	PARAMETER ZIa;
	SID_PARAM_LIST ZIq;

	ZRparam_Hitem (&ZIa);
	{
	    switch (CURRENT_TERMINAL) {
	      case 29:
		{
		    ADVANCE_LEXER;
		    ZRparam_Hlist (&ZIq);
		    if ((CURRENT_TERMINAL) == 32) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIq) = NULL_list ( PARAMETER ) ;
		    }
		}
		break;
	      case 32:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	{

    CONS_par ( (ZIa), (ZIq), (ZIp) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (32);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRclist_Hitem PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	SORT ZIs;

	ZRnew_Hsort_Hname (&ZIs);
	if ((CURRENT_TERMINAL) == 32) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    compound_sort ( (ZIs), "_list", info_clist_tag, '*' ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRslist_Hpack PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 0:
		{
		    ZRslist_Hlist ();
		    if ((CURRENT_TERMINAL) == 32) {
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
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRedge_Hlist PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
  ZL2_edge_Hlist:;
    {
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRedge_Hitem ();
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 29:
		{
		    ADVANCE_LEXER;
		    goto ZL2_edge_Hlist;
		}
		/*UNREACHED*/
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRkind_Hitem PROTO_N ((ZOa))
  PROTO_T (LINKAGE *ZOa)
{
    LINKAGE ZIa;

    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	SORT ZIs;
	string ZIe;

	switch (CURRENT_TERMINAL) {
	  case 27:
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
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRold_Hsort_Hname (&ZIs);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 26:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRany_Hname (&ZIe);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    MAKE_link_basic ( (ZIe), (ZIs), (ZIa) ) ;
    COPY_string ( sort_unit ( (ZIs) ), (ZIe) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (32);
    return;
  ZL0:;
    *ZOa = ZIa;
}

static void
ZRoption_Hlist PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
  ZL2_option_Hlist:;
    {
	ZRoption_Hitem ();
	{
	    switch (CURRENT_TERMINAL) {
	      case 29:
		{
		    ADVANCE_LEXER;
		    goto ZL2_option_Hlist;
		}
		/*UNREACHED*/
	      case 32:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZR139 PROTO_N ((ZIc))
  PROTO_T (CONSTRUCT *ZIc)
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR140 (ZIc);
	if ((CURRENT_TERMINAL) == 32) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRold_Hsort_Hname PROTO_N ((ZOs))
  PROTO_T (SORT *ZOs)
{
    SORT ZIs;

    if ((CURRENT_TERMINAL) == 32) {
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
	{

    (ZIs) = find_sort ( (ZIa), 0 ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (32);
    return;
  ZL0:;
    *ZOs = ZIs;
}

static void
ZR140 PROTO_N ((ZIc))
  PROTO_T (CONSTRUCT *ZIc)
{
    switch (CURRENT_TERMINAL) {
      case 3:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 27:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRnumber_Hlist (*ZIc);
	    switch (CURRENT_TERMINAL) {
	      case 28:
		break;
	      case 32:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 28:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 2:
	{
	    unsigned ZIa;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
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
	      case 28:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    PARAMETER p = find_param ( (*ZIc), (ZIa) ) ;
    if ( !IS_NULL_par ( p ) ) COPY_int ( par_brk ( p ), 1 ) ;
	    }
	    ZR141 (ZIc);
	    if ((CURRENT_TERMINAL) == 32) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 32:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZR141 PROTO_N ((ZIc))
  PROTO_T (CONSTRUCT *ZIc)
{
    switch (CURRENT_TERMINAL) {
      case 29:
	{
	    ADVANCE_LEXER;
	    ZRboundary_Hitem (*ZIc);
	    if ((CURRENT_TERMINAL) == 32) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 32:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRclist_Hlist PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
  ZL2_clist_Hlist:;
    {
	ZRclist_Hitem ();
	{
	    switch (CURRENT_TERMINAL) {
	      case 29:
		{
		    ADVANCE_LEXER;
		    goto ZL2_clist_Hlist;
		}
		/*UNREACHED*/
	      case 32:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRlink_Hitem PROTO_N ((ZOa))
  PROTO_T (LINKAGE *ZOa)
{
    LINKAGE ZIa;

    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	SORT ZIs;
	string ZIe;

	switch (CURRENT_TERMINAL) {
	  case 27:
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
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRold_Hsort_Hname (&ZIs);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
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
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRany_Hname (&ZIe);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    MAKE_link_basic ( (ZIe), (ZIs), (ZIa) ) ;
    COPY_string ( sort_link ( (ZIs) ), (ZIe) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (32);
    return;
  ZL0:;
    *ZOa = ZIa;
}

static void
ZRslist_Hitem PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	SORT ZIs;

	ZRnew_Hsort_Hname (&ZIs);
	if ((CURRENT_TERMINAL) == 32) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    compound_sort ( (ZIs), "_list", info_slist_tag, '%' ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRkind_Hlist PROTO_N ((ZOp))
  PROTO_T (SID_LINK_LIST *ZOp)
{
    SID_LINK_LIST ZIp;

    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	LINKAGE ZIa;
	SID_LINK_LIST ZIq;

	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRkind_Hitem (&ZIa);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 29:
		{
		    ADVANCE_LEXER;
		    ZRkind_Hlist (&ZIq);
		    if ((CURRENT_TERMINAL) == 32) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIq) = NULL_list ( LINKAGE ) ;
		    }
		}
		break;
	    }
	}
	{

    CONS_link ( (ZIa), (ZIq), (ZIp) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (32);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRnew_Hsort_Hname PROTO_N ((ZOs))
  PROTO_T (SORT *ZOs)
{
    SORT ZIs;

    if ((CURRENT_TERMINAL) == 32) {
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
	{

    (ZIs) = find_sort ( (ZIa), 1 ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (32);
    return;
  ZL0:;
    *ZOs = ZIs;
}

static void
ZRsort_Hpack PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 27:
		{
		    ZRsort_Hlist ();
		    if ((CURRENT_TERMINAL) == 32) {
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
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRany_Hname PROTO_N ((ZOn))
  PROTO_T (string *ZOn)
{
    string ZIn;

    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    {

    ZIn = xstrcpy ( token_buff ) ;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 2: case 3: case 4: case 5: case 6:
      case 7: case 8: case 9: case 10: case 11:
      case 12: case 13: case 14: case 15: case 16:
      case 17: case 18: case 19: case 20: case 21:
      case 22: case 23: case 24: case 25: case 26:
	{
	    {

    (ZIn) = xstrcpy ( token_buff ) ;
	    }
	    {
		switch (CURRENT_TERMINAL) {
		  case 3:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 2:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 5:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 4:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 6:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 7:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 8:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 9:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 10:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 11:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 12:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 13:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 14:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 15:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 16:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 17:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 18:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 19:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 20:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 21:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 22:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 23:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 24:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 25:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 26:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	}
	break;
      case 32:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (32);
    return;
  ZL0:;
    *ZOn = ZIn;
}

static void
ZRlink_Hlist PROTO_N ((ZOp))
  PROTO_T (SID_LINK_LIST *ZOp)
{
    SID_LINK_LIST ZIp;

    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	LINKAGE ZIa;
	SID_LINK_LIST ZIq;

	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRlink_Hitem (&ZIa);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 29:
		{
		    ADVANCE_LEXER;
		    ZRlink_Hlist (&ZIq);
		    if ((CURRENT_TERMINAL) == 32) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIq) = NULL_list ( LINKAGE ) ;
		    }
		}
		break;
	    }
	}
	{

    CONS_link ( (ZIa), (ZIq), (ZIp) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (32);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRslist_Hlist PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
  ZL2_slist_Hlist:;
    {
	ZRslist_Hitem ();
	{
	    switch (CURRENT_TERMINAL) {
	      case 29:
		{
		    ADVANCE_LEXER;
		    goto ZL2_slist_Hlist;
		}
		/*UNREACHED*/
	      case 32:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRsort_Hitem PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	SORT ZIs;
	unsigned ZIb;
	unsigned ZIe;
	SID_CONS_LIST ZIp;

	switch (CURRENT_TERMINAL) {
	  case 27:
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
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRnew_Hsort_Hname (&ZIs);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 9:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
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
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 13:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 1:
	    {

    ZIe = token_value ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 4:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRconstruct_Hpack (ZIs, &ZIp);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    basic_sort ( (ZIs), (ZIb), (ZIe), (ZIp) ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRsort_Hlist PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
  ZL2_sort_Hlist:;
    {
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRsort_Hitem ();
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 29:
		{
		    ADVANCE_LEXER;
		    goto ZL2_sort_Hlist;
		}
		/*UNREACHED*/
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRconstruct_Hpack PROTO_N ((ZIs, ZOp))
  PROTO_T (SORT ZIs X SID_CONS_LIST *ZOp)
{
    SID_CONS_LIST ZIp;

    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	SID_CONS_LIST ZIq;

	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 27:
		{
		    ZRconstruct_Hlist (ZIs, &ZIq);
		    if ((CURRENT_TERMINAL) == 32) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIq) = NULL_list ( CONSTRUCT ) ;
		    }
		}
		break;
	    }
	}
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZIp = ZIq;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (32);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRconstruct_Hextra PROTO_N ((ZIc))
  PROTO_T (CONSTRUCT ZIc)
{
    switch (CURRENT_TERMINAL) {
      case 29:
	{
	    ADVANCE_LEXER;
	    ZR139 (&ZIc);
	    if ((CURRENT_TERMINAL) == 32) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 32:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRboundary_Hitem PROTO_N ((ZIc))
  PROTO_T (CONSTRUCT ZIc)
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 3:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRnumber_Hlist (ZIc);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRconstruct_Hitem PROTO_N ((ZIs, ZOc))
  PROTO_T (SORT ZIs X CONSTRUCT *ZOc)
{
    CONSTRUCT ZIc;

    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	string ZIn;
	unsigned ZIe;
	SORT ZIr;
	SID_PARAM_LIST ZIp;

	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 5:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 0:
	    {

    ZIn = xstrcpy ( token_buff ) ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 8:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 1:
	    {

    ZIe = token_value ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
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
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRnew_Hsort_Hname (&ZIr);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
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
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRparam_Hpack (&ZIp);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    if ( !EQ_sort ( (ZIr), (ZIs) ) ) {
	error ( ERROR_SERIOUS, "Wrong result sort for '%s'", (ZIn) ) ;
    }
    (ZIc) = make_construct ( (ZIn), (ZIe), (ZIs), (ZIp) ) ;
	}
	ZRconstruct_Hextra (ZIc);
	if ((CURRENT_TERMINAL) == 32) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (32);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRconstruct_Hlist PROTO_N ((ZIs, ZOp))
  PROTO_T (SORT ZIs X SID_CONS_LIST *ZOp)
{
    SID_CONS_LIST ZIp;

    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	CONSTRUCT ZIc;
	SID_CONS_LIST ZIq;

	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRconstruct_Hitem (ZIs, &ZIc);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 29:
		{
		    ADVANCE_LEXER;
		    ZRconstruct_Hlist (ZIs, &ZIq);
		    if ((CURRENT_TERMINAL) == 32) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIq) = NULL_list ( CONSTRUCT ) ;
		    }
		}
		break;
	    }
	}
	{

    CONS_cons ( (ZIc), (ZIq), (ZIp) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (32);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRparam_Hpack PROTO_N ((ZOp))
  PROTO_T (SID_PARAM_LIST *ZOp)
{
    SID_PARAM_LIST ZIp;

    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	SID_PARAM_LIST ZIq;

	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 27:
		{
		    ZRparam_Hlist (&ZIq);
		    if ((CURRENT_TERMINAL) == 32) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIq) = NULL_list ( PARAMETER ) ;
		    }
		}
		break;
	    }
	}
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZIp = ZIq;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (32);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRedge_Hpack PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 27:
		{
		    ZRedge_Hlist ();
		    if ((CURRENT_TERMINAL) == 32) {
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
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

void
read_spec PROTO_N ((ZOspec))
  PROTO_T (SPECIFICATION *ZOspec)
{
    SPECIFICATION ZIspec;

    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	SID_LINK_LIST ZIp;
	SID_LINK_LIST ZIq;
	unsigned ZIv1;
	unsigned ZIv2;

	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 24:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRsort_Hpack ();
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 16:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRclist_Hpack ();
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
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
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRslist_Hpack ();
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 19:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRoption_Hpack ();
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 15:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRlink_Hpack (&ZIp);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 14:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRkind_Hpack (&ZIq);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 12:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRedge_Hpack ();
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 17:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 1:
	    {

    ZIv1 = token_value ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 18:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 1:
	    {

    ZIv2 = token_value ;
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 28:
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
	{

    LIST ( SORT ) p = check_sorts () ;
    LIST ( LINKAGE ) q = foreign_sorts () ;
    MAKE_spec_basic ( (ZIv1), (ZIv2), p, (ZIp), (ZIq), q, (ZIspec) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    {
	{

    error ( ERROR_SERIOUS, "Syntax error" ) ;
	}
	{

    (ZIspec) = NULL_spec ;
	}
    }
  ZL0:;
    *ZOspec = ZIspec;
}

static void
ZRoption_Hpack PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 0:
		{
		    ZRoption_Hlist ();
		    if ((CURRENT_TERMINAL) == 32) {
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
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRclist_Hpack PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 0:
		{
		    ZRclist_Hlist ();
		    if ((CURRENT_TERMINAL) == 32) {
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
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRparam_Hitem PROTO_N ((ZOa))
  PROTO_T (PARAMETER *ZOa)
{
    PARAMETER ZIa;

    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	string ZIn;
	SORT ZIs;

	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRany_Hname (&ZIn);
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRnew_Hsort_Hname (&ZIs);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    int intro = 0 ;
    if ( ends_in ( (ZIn), "_intro" ) ) intro = 1 ;
    MAKE_par_basic ( (ZIn), (ZIs), 0, 0, intro, (ZIa) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (32);
    return;
  ZL0:;
    *ZOa = ZIa;
}

static void
ZRedge_Hitem PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	SORT ZIs;
	string ZIc;

	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 7:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRold_Hsort_Hname (&ZIs);
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  case 32:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 6:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 29:
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
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    set_special ( (ZIs), (ZIc), KIND_edge ) ;
    COPY_int ( sort_edge ( (ZIs) ), 1 ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRkind_Hpack PROTO_N ((ZOp))
  PROTO_T (SID_LINK_LIST *ZOp)
{
    SID_LINK_LIST ZIp;

    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	SID_LINK_LIST ZIq;

	switch (CURRENT_TERMINAL) {
	  case 27:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 27:
		{
		    ZRkind_Hlist (&ZIq);
		    if ((CURRENT_TERMINAL) == 32) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIq) = NULL_list ( LINKAGE ) ;
		    }
		}
		break;
	    }
	}
	switch (CURRENT_TERMINAL) {
	  case 28:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZIp = ZIq;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (32);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRnumber_Hlist PROTO_N ((ZIc))
  PROTO_T (CONSTRUCT ZIc)
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
  ZL2_number_Hlist:;
    {
	unsigned ZIa;

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
	{

    PARAMETER p = find_param ( (ZIc), (ZIa) ) ;
    if ( !IS_NULL_par ( p ) ) COPY_int ( par_align ( p ), 1 ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 29:
		{
		    ADVANCE_LEXER;
		    goto ZL2_number_Hlist;
		}
		/*UNREACHED*/
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

static void
ZRoption_Hitem PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 32) {
	return;
    }
    {
	SORT ZIs;

	ZRnew_Hsort_Hname (&ZIs);
	if ((CURRENT_TERMINAL) == 32) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    compound_sort ( (ZIs), "_option", info_option_tag, '?' ) ;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (32);
    return;
}

/* BEGINNING OF TRAILER */



/* END OF FILE */
