/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
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
#include "object.h"
#include "hash.h"
#include "lex.h"
#include "name.h"
#include "syntax.h"
#include "type.h"
#include "utility.h"
#include "variable.h"


/*
    PARSER TYPES

    These types give the implementations of the various types used
    in the syntax.
*/

typedef char *SID_STRING ;
typedef type *SID_TYPE ;

typedef struct {
    char *iname ;
    char *ename ;
    int ivers ;
    int evers ;
} SID_IDENTIFIER ;


/*
    CURRENT FIELD NAME

    The name of the current structure is stored during a +FIELD
    construct.
*/

static char *crt_field_name = null ;
static int anon_no = 0 ;


/*
    CV-QUALIFIER NAMES

    This table gives the mapping between the values used to represent
    cv-qualifiers in the parser and the qualifier names used in the
    internal representation.
*/

static char *cv_qualifier [] = {
    null, "const", "volatile", "const volatile"
} ;

/*
    COMPILATION MODE

    We allow unreached code in the automatically generated sections.
*/

#if FS_TENDRA
#pragma TenDRA begin
#pragma TenDRA unreachable code allow
#pragma TenDRA variable analysis off
#endif



/* BEGINNING OF FUNCTION DECLARATIONS */

static void ZRsimple_Htype(SID_TYPE *);
static void ZRparameter_Hdeclaration(SID_TYPE *);
static void ZRnat_Hdeclarator_Hlist(SID_COMMAND *);
static void ZRtype_Hdeclarator_Hlist(SID_COMMAND *);
static void ZRfunction_Hoperator(SID_TYPE *);
static void ZRexp_Hdeclarator_Hlist(int, SID_TYPE, int, SID_COMMAND *);
static void ZRsubset_Hkey(SID_STRING *);
static void ZRmacro_Hparam_Hdeclaration(SID_TYPE *);
static void ZRifdef_Hmacro_Hname(SID_STRING *);
static void ZRdefine_Hparam_Hlist(SID_STRING *);
static void ZR287(SID_TYPE *);
static void ZRdeclarator(SID_IDENTIFIER *, SID_TYPE *);
static void ZRidentifier(SID_IDENTIFIER *);
static void ZRsubset_Hcommand(SID_COMMAND *);
static void ZRqualified_Htype(SID_TYPE *);
static void ZRabstract_Hdeclarator(SID_STRING *, SID_TYPE *);
static void ZRparameter_Hlist(SID_TYPE *);
static void ZRinternal_Hname(SID_STRING *, int *);
static void ZR308(SID_STRING, SID_TYPE, SID_STRING *, SID_TYPE *);
static void ZRmacro_Hoperator(SID_TYPE *);
static void ZRenumerator_Hlist(SID_COMMAND *);
static void ZRexternal_Hname(SID_STRING *, int *);
static void ZRtype_Hqualifier(unsigned *);
static void ZRtype_Hkey(int *);
static void ZRtype_Hqualifier_Hopt(unsigned *);
static void ZRconstant_Hvalue(SID_STRING *);
static void ZR318(SID_IDENTIFIER, SID_TYPE, SID_IDENTIFIER *, SID_TYPE *);
static void ZRspec_Hcommand(SID_COMMAND *);
static void ZRfunc_Hcommand(int *);
static void ZR320(SID_STRING *, SID_STRING *);
static void ZR321(SID_STRING *, SID_STRING *, SID_STRING *);
static void ZRarray_Hoperator(SID_TYPE *);
static void ZR322(SID_COMMAND *);
static void ZR323(int *, SID_COMMAND *);
static void ZRmacro_Hparam_Hlist(SID_TYPE *);
static void ZR324(SID_STRING *, int *, SID_IDENTIFIER *);
static void ZR325(SID_STRING *);
static void ZR328(SID_STRING *, SID_STRING *);
static void ZRenum_Hcommand(int *);
static void ZRenumerator(SID_COMMAND *);
static void ZR329(int *);
static void ZRfield_Hdeclarator_Hlist(SID_TYPE, SID_TYPE, SID_COMMAND *);
static void ZR330(int *);
static void ZRfield_Hexact(int *);
static void ZR333(SID_TYPE *, SID_TYPE *);
static void ZR335(SID_TYPE *);
static void ZRcommand_Hlist(SID_COMMAND *);
static void ZR338(SID_STRING *, SID_TYPE *, SID_STRING *, SID_TYPE *);
static void ZR339(SID_TYPE *);
static void ZR340(int *);
static void ZRdirect_Hdeclarator(SID_IDENTIFIER *, SID_TYPE *);
static void ZRtype_Hcommand(int *);
static void ZRtext_Hcommand(SID_COMMAND *);
static void ZR347(SID_IDENTIFIER *, SID_IDENTIFIER *, SID_TYPE *);
static void ZRname_Hversion(int *);
static void ZR348(int *);
static void ZRdirect_Habstract_Hdeclarator(SID_STRING *, SID_TYPE *);
static void ZRfield_Hdeclarator(SID_IDENTIFIER *, SID_TYPE *);
static void ZRvariable_Hcommand(void);
static void ZR349(int *);
static void ZR350(SID_TYPE *);
static void ZR351(SID_STRING *);
static void ZRdefine_Hparam_Hclause(SID_STRING *);
static void ZRexp_Hcommand(int *);
static void ZR352(SID_STRING *);
static void ZRif_Hcommand(SID_COMMAND *, SID_STRING *);
static void ZR353(SID_STRING *);
static void ZR354(SID_STRING *);
static void ZRbitfield_Hoperator(SID_TYPE *);
static void ZRuse_Hsubset_Hname(SID_STRING *);
extern void read_spec(SID_COMMAND *);
static void ZRmacro_Hdeclarator(SID_IDENTIFIER *, SID_TYPE *);
static void ZRsubset_Hname(SID_STRING *);
static void ZRbuiltin_Htype(unsigned *);
static void ZRobject_Hqualifier(int *);
static void ZRfield_Hlist(SID_TYPE, SID_COMMAND *);
static void ZRptr_Hoperator(SID_TYPE *);
static void ZRtype_Hkeyword(unsigned *);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

static void
ZRsimple_Htype(SID_TYPE *ZOt)
{
    SID_TYPE ZIt;

    switch (CURRENT_TERMINAL) {
      case 32: case 34: case 37: case 38: case 39:
      case 42: case 43: case 46: case 47:
	{
	    unsigned ZIb;

	    ZRbuiltin_Htype (&ZIb);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = basic_type ( (ZIb) ) ;
	    }
	}
	break;
      case 0: case 35: case 44: case 45:
	{
	    int ZItag;
	    SID_STRING ZInm;

	    ZRtype_Hkey (&ZItag);
	    switch (CURRENT_TERMINAL) {
	      case 0:
		{
 ZInm = token_value ; 
		}
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZIt) = find_type ( (ZInm), any_version, (ZItag), 1 ) ;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOt = ZIt;
}

static void
ZRparameter_Hdeclaration(SID_TYPE *ZOt)
{
    SID_TYPE ZIt;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_TYPE ZIs;
	SID_STRING ZInm;
	SID_TYPE ZIp;

	ZRqualified_Htype (&ZIs);
	ZRabstract_Hdeclarator (&ZInm, &ZIp);
	if ((CURRENT_TERMINAL) == 75) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZIt) = inject_type ( (ZIp), (ZIs) ) ;
	}
	{

    UNUSED ( (ZInm) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOt = ZIt;
}

static void
ZRnat_Hdeclarator_Hlist(SID_COMMAND *ZOc)
{
    SID_COMMAND ZIc;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_IDENTIFIER ZIid;
	SID_COMMAND ZIa;
	SID_COMMAND ZIb;

	ZRidentifier (&ZIid);
	if ((CURRENT_TERMINAL) == 75) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    object *p = make_exp ( (ZIid).iname, (ZIid).ivers, OBJ_NAT ) ;
    (ZIa) = make_token ( (ZIid).ename, (ZIid).evers, p, OBJ_NAT ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 62:
		{
		    ADVANCE_LEXER;
		    ZRnat_Hdeclarator_Hlist (&ZIb);
		    if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIb) = null ;
		    }
		}
		break;
	    }
	}
	{

    (ZIc) = join_object ( (ZIa), (ZIb) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRtype_Hdeclarator_Hlist(SID_COMMAND *ZOc)
{
    SID_COMMAND ZIc;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	int ZItag;
	SID_IDENTIFIER ZIid;
	SID_COMMAND ZIa;
	SID_COMMAND ZIb;

	ZRtype_Hcommand (&ZItag);
	ZRidentifier (&ZIid);
	if ((CURRENT_TERMINAL) == 75) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    type *t = make_type ( (ZIid).iname, (ZIid).ivers, (ZItag) ) ;
    (ZIa) = make_token ( (ZIid).ename, (ZIid).evers, t->u.obj, OBJ_TYPE ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 62:
		{
		    ADVANCE_LEXER;
		    ZRtype_Hdeclarator_Hlist (&ZIb);
		    if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIb) = null ;
		    }
		}
		break;
	    }
	}
	{

    (ZIc) = join_object ( (ZIa), (ZIb) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRfunction_Hoperator(SID_TYPE *ZOt)
{
    SID_TYPE ZIt;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 56:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR335 (&ZIt);
	if ((CURRENT_TERMINAL) == 75) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOt = ZIt;
}

static void
ZRexp_Hdeclarator_Hlist(int ZIcmd, SID_TYPE ZIs, int ZIlv, SID_COMMAND *ZOc)
{
    SID_COMMAND ZIc;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_IDENTIFIER ZIid;
	SID_TYPE ZIp;
	SID_TYPE ZIu;
	SID_TYPE ZIt;
	SID_COMMAND ZIa;
	SID_COMMAND ZIb;

	ZRdeclarator (&ZIid, &ZIp);
	if ((CURRENT_TERMINAL) == 75) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZIu) = inject_type ( (ZIp), (ZIs) ) ;
	}
	{

    (ZIt) = make_subtype ( (ZIu), (ZIlv) ) ;
	}
	{

    object *p = make_exp ( (ZIid).iname, (ZIid).ivers, (ZIcmd) ) ;
    p->u.u_type = check_type ( (ZIt), (ZIcmd) ) ;
    (ZIa) = make_token ( (ZIid).ename, (ZIid).evers, p, (ZIcmd) ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 62:
		{
		    ADVANCE_LEXER;
		    ZRexp_Hdeclarator_Hlist (ZIcmd, ZIs, ZIlv, &ZIb);
		    if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIb) = null ;
		    }
		}
		break;
	    }
	}
	{

    (ZIc) = join_object ( (ZIa), (ZIb) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRsubset_Hkey(SID_STRING *ZOkey)
{
    SID_STRING ZIkey;

    switch (CURRENT_TERMINAL) {
      case 56:
	{
	    ADVANCE_LEXER;
	    ZR351 (&ZIkey);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZIkey) = "11" ; 
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOkey = ZIkey;
}

static void
ZRmacro_Hparam_Hdeclaration(SID_TYPE *ZOt)
{
    SID_TYPE ZIt;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	int ZIlv;
	SID_TYPE ZIs;
	SID_STRING ZInm;
	SID_TYPE ZIp;
	SID_TYPE ZIu;

	ZRobject_Hqualifier (&ZIlv);
	ZRqualified_Htype (&ZIs);
	ZRabstract_Hdeclarator (&ZInm, &ZIp);
	if ((CURRENT_TERMINAL) == 75) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZIu) = inject_type ( (ZIp), (ZIs) ) ;
	}
	{

    (ZIt) = make_subtype ( (ZIu), (ZIlv) ) ;
	}
	{

    UNUSED ( (ZInm) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOt = ZIt;
}

static void
ZRifdef_Hmacro_Hname(SID_STRING *ZOc)
{
    SID_STRING ZIc;

    switch (CURRENT_TERMINAL) {
      case 50:
	{
	    ADVANCE_LEXER;
	    {

    (ZIc) = BUILDING_MACRO ;
	    }
	}
	break;
      case 0:
	{
	    {
 ZIc = token_value ; 
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 52:
	{
	    SID_STRING ZIa;
	    SID_STRING ZIb;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 56:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 2:
		{
 ZIa = token_value ; 
		}
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 62:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 2:
		{
 ZIb = token_value ; 
		}
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZIc) = macro_name ( PROTECT_PREFIX, (ZIa), (ZIb), null_str ) ;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRdefine_Hparam_Hlist(SID_STRING *ZOp)
{
    SID_STRING ZIp;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_STRING ZI326;

	switch (CURRENT_TERMINAL) {
	  case 0:
	    {
 ZI326 = token_value ; 
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR328 (&ZI326, &ZIp);
	if ((CURRENT_TERMINAL) == 75) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZR287(SID_TYPE *ZOt)
{
    SID_TYPE ZIt;

    switch (CURRENT_TERMINAL) {
      case 56:
	{
	    ZRmacro_Hoperator (&ZIt);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZIt) = null ;
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOt = ZIt;
}

static void
ZRdeclarator(SID_IDENTIFIER *ZOid, SID_TYPE *ZOt)
{
    SID_IDENTIFIER ZIid;
    SID_TYPE ZIt;

    switch (CURRENT_TERMINAL) {
      case 0: case 56:
	{
	    ZRdirect_Hdeclarator (&ZIid, &ZIt);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 72:
	{
	    SID_TYPE ZIp;
	    SID_TYPE ZIs;

	    ZRptr_Hoperator (&ZIp);
	    ZRdeclarator (&ZIid, &ZIs);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = inject_type ( (ZIs), (ZIp) ) ;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOid = ZIid;
    *ZOt = ZIt;
}

static void
ZRidentifier(SID_IDENTIFIER *ZOid)
{
    SID_IDENTIFIER ZIid;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_STRING ZInm;
	int ZIv;

	ZRinternal_Hname (&ZInm, &ZIv);
	ZR324 (&ZInm, &ZIv, &ZIid);
	if ((CURRENT_TERMINAL) == 75) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOid = ZIid;
}

static void
ZRsubset_Hcommand(SID_COMMAND *ZOc)
{
    SID_COMMAND ZIc;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_STRING ZIs;
	SID_COMMAND ZIa;
	SID_COMMAND ZIb;

	switch (CURRENT_TERMINAL) {
	  case 23:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRsubset_Hname (&ZIs);
	switch (CURRENT_TERMINAL) {
	  case 60:
	    break;
	  case 75:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    object *p = make_subset ( (ZIs) ) ;
    info *i = p->u.u_info ;
    if ( i->subset ) {
	char *nm = subset_name ( i->api, i->file, null_str ) ;
	object *q = search_hash ( subsets, nm, no_version ) ;
	update_time ( p, q ) ;
    }
    (ZIa) = crt_object ;
    crt_object = p ;
	}
	switch (CURRENT_TERMINAL) {
	  case 54:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRcommand_Hlist (&ZIb);
	switch (CURRENT_TERMINAL) {
	  case 55:
	    break;
	  case 75:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    object *p = crt_object ;
    if ( p ) p->u.u_info->elements = (ZIb) ;
    (ZIc) = make_object ( null_str, OBJ_SET ) ;
    (ZIc)->u.u_obj = p ;
    crt_object = (ZIa) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRqualified_Htype(SID_TYPE *ZOt)
{
    SID_TYPE ZIt;

    switch (CURRENT_TERMINAL) {
      case 0: case 32: case 34: case 35: case 37:
      case 38: case 39: case 42: case 43: case 44:
      case 45: case 46: case 47:
	{
	    SID_TYPE ZI331;

	    ZRsimple_Htype (&ZI331);
	    ZR333 (&ZI331, &ZIt);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 33: case 48:
	{
	    unsigned ZIcv;
	    SID_TYPE ZIs;

	    ZRtype_Hqualifier (&ZIcv);
	    ZRsimple_Htype (&ZIs);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = make_subtype ( (ZIs), TYPE_QUALIFIER ) ;
    (ZIt)->v.str = cv_qualifier [ (ZIcv) ] ;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOt = ZIt;
}

static void
ZRabstract_Hdeclarator(SID_STRING *ZOnm, SID_TYPE *ZOt)
{
    SID_STRING ZInm;
    SID_TYPE ZIt;

    switch (CURRENT_TERMINAL) {
      default:
	{
	    ZRdirect_Habstract_Hdeclarator (&ZInm, &ZIt);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 72:
	{
	    SID_TYPE ZIp;
	    SID_TYPE ZIs;

	    ZRptr_Hoperator (&ZIp);
	    ZRabstract_Hdeclarator (&ZInm, &ZIs);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = inject_type ( (ZIs), (ZIp) ) ;
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOnm = ZInm;
    *ZOt = ZIt;
}

static void
ZRparameter_Hlist(SID_TYPE *ZOp)
{
    SID_TYPE ZIp;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_TYPE ZIt;
	SID_TYPE ZIq;

	ZRparameter_Hdeclaration (&ZIt);
	{
	    switch (CURRENT_TERMINAL) {
	      case 62:
		{
		    ADVANCE_LEXER;
		    ZR339 (&ZIq);
		    if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIq) = null ;
		    }
		}
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	{

    (ZIp) = make_subtype ( (ZIt), TYPE_LIST ) ;
    (ZIp)->v.next = (ZIq) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRinternal_Hname(SID_STRING *ZOnm, int *ZOv)
{
    SID_STRING ZInm;
    int ZIv;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_STRING ZIa;

	switch (CURRENT_TERMINAL) {
	  case 0:
	    {
 ZIa = token_value ; 
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRname_Hversion (&ZIv);
	if ((CURRENT_TERMINAL) == 75) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if ( crt_field_name ) {
	(ZInm) = string_printf ( "%s.%s", crt_field_name, (ZIa) ) ;
    } else {
	(ZInm) = (ZIa) ;
    }
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOnm = ZInm;
    *ZOv = ZIv;
}

static void
ZR308(SID_STRING ZI304, SID_TYPE ZI305, SID_STRING *ZO306, SID_TYPE *ZO307)
{
    SID_STRING ZI306;
    SID_TYPE ZI307;

  ZL2_308:;
    switch (CURRENT_TERMINAL) {
      case 58:
	{
	    SID_STRING ZInm;
	    SID_TYPE ZIs;
	    SID_TYPE ZIt;

	    ZInm = ZI304;
	    ZRarray_Hoperator (&ZIs);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = inject_type ( (ZI305), (ZIs) ) ;
	    }
	    ZI304 = ZInm;
	    ZI305 = ZIt;
	    goto ZL2_308;
	}
	/*UNREACHED*/
      default:
	{
	    ZI306 = ZI304;
	    ZI307 = ZI305;
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZO306 = ZI306;
    *ZO307 = ZI307;
}

static void
ZRmacro_Hoperator(SID_TYPE *ZOt)
{
    SID_TYPE ZIt;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 56:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR350 (&ZIt);
	if ((CURRENT_TERMINAL) == 75) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOt = ZIt;
}

static void
ZRenumerator_Hlist(SID_COMMAND *ZOc)
{
    SID_COMMAND ZIc;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_COMMAND ZIa;
	SID_COMMAND ZIb;

	ZRenumerator (&ZIa);
	{
	    switch (CURRENT_TERMINAL) {
	      case 62:
		{
		    ADVANCE_LEXER;
		    ZRenumerator_Hlist (&ZIb);
		    if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIb) = null ;
		    }
		}
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	{

    (ZIc) = join_object ( (ZIa), (ZIb) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRexternal_Hname(SID_STRING *ZOnm, int *ZOv)
{
    SID_STRING ZInm;
    int ZIv;

    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    SID_STRING ZIa;
	    SID_STRING ZIb;

	    {
 ZIa = token_value ; 
	    }
	    ADVANCE_LEXER;
	    ZRname_Hversion (&ZIv);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( crt_field_name ) {
	(ZIb) = string_printf ( "%s.%s", crt_field_name, (ZIa) ) ;
    } else {
	(ZIb) = (ZIa) ;
    }
	    }
	    {

    (ZInm) = token_name ( (ZIb) ) ;
	    }
	}
	break;
      case 2:
	{
	    {
 ZInm = token_value ; 
	    }
	    ADVANCE_LEXER;
	    ZRname_Hversion (&ZIv);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOnm = ZInm;
    *ZOv = ZIv;
}

static void
ZRtype_Hqualifier(unsigned *ZOcv)
{
    unsigned ZIcv;

    switch (CURRENT_TERMINAL) {
      case 33:
	{
	    unsigned ZIa;

	    ADVANCE_LEXER;
	    ZRtype_Hqualifier_Hopt (&ZIa);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( (ZIa) & 1 ) error ( ERR_SERIOUS, "Duplicate type qualifier" ) ;
    (ZIcv) = ( (ZIa) | 1 ) ;
	    }
	}
	break;
      case 48:
	{
	    unsigned ZIa;

	    ADVANCE_LEXER;
	    ZRtype_Hqualifier_Hopt (&ZIa);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( (ZIa) & 2 ) error ( ERR_SERIOUS, "Duplicate type qualifier" ) ;
    (ZIcv) = ( (ZIa) | 2 ) ;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOcv = ZIcv;
}

static void
ZRtype_Hkey(int *ZOtag)
{
    int ZItag;

    switch (CURRENT_TERMINAL) {
      case 35:
	{
	    ADVANCE_LEXER;
	    {
 (ZItag) = TYPE_ENUM_TAG ; 
	    }
	}
	break;
      case 44:
	{
	    ADVANCE_LEXER;
	    {
 (ZItag) = TYPE_STRUCT_TAG ; 
	    }
	}
	break;
      case 45:
	{
	    ADVANCE_LEXER;
	    {
 (ZItag) = TYPE_UNION_TAG ; 
	    }
	}
	break;
      default:
	{
	    {
 (ZItag) = TYPE_GENERIC ; 
	    }
	}
	break;
      case 75:
	return;
    }
    *ZOtag = ZItag;
}

static void
ZRtype_Hqualifier_Hopt(unsigned *ZOcv)
{
    unsigned ZIcv;

    switch (CURRENT_TERMINAL) {
      case 33: case 48:
	{
	    ZRtype_Hqualifier (&ZIcv);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZIcv) = 0 ;
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOcv = ZIcv;
}

static void
ZRconstant_Hvalue(SID_STRING *ZOs)
{
    SID_STRING ZIs;

    switch (CURRENT_TERMINAL) {
      case 67:
	{
	    SID_STRING ZIa;

	    ADVANCE_LEXER;
	    ZRconstant_Hvalue (&ZIa);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIs) = string_concat ( "!", (ZIa) ) ;
	    }
	}
	break;
      case 5:
	{
	    {
 ZIs = token_value ; 
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 68:
	{
	    SID_STRING ZIa;

	    ADVANCE_LEXER;
	    ZRconstant_Hvalue (&ZIa);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIs) = string_concat ( "-", (ZIa) ) ;
	    }
	}
	break;
      case 0:
	{
	    SID_STRING ZIa;

	    {
 ZIa = token_value ; 
	    }
	    ADVANCE_LEXER;
	    {

    object *p = search_hash ( exps, (ZIa), any_version ) ;
    if ( p == null ) {
	error ( ERR_SERIOUS, "Undefined NAT, '%s'", (ZIa) ) ;
    } else if ( p->objtype != OBJ_NAT ) {
	error ( ERR_SERIOUS, "'%s' is not a NAT", (ZIa) ) ;
    }
    (ZIs) = (ZIa) ;
	    }
	}
	break;
      case 1:
	{
	    {
 ZIs = token_value ; 
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOs = ZIs;
}

static void
ZR318(SID_IDENTIFIER ZI312, SID_TYPE ZI313, SID_IDENTIFIER *ZO316, SID_TYPE *ZO317)
{
    SID_IDENTIFIER ZI316;
    SID_TYPE ZI317;

  ZL2_318:;
    switch (CURRENT_TERMINAL) {
      case 56: case 58:
	{
	    SID_IDENTIFIER ZIid;

	    ZIid = ZI312;
	    {
		switch (CURRENT_TERMINAL) {
		  case 58:
		    {
			SID_TYPE ZIs;
			SID_TYPE ZIt;

			ZRarray_Hoperator (&ZIs);
			if ((CURRENT_TERMINAL) == 75) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    (ZIt) = inject_type ( (ZI313), (ZIs) ) ;
			}
			ZI312 = ZIid;
			ZI313 = ZIt;
			goto ZL2_318;
		    }
		    /*UNREACHED*/
		  case 56:
		    {
			SID_TYPE ZIs;
			SID_TYPE ZIt;

			ZRfunction_Hoperator (&ZIs);
			if ((CURRENT_TERMINAL) == 75) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    (ZIt) = inject_type ( (ZI313), (ZIs) ) ;
			}
			ZI312 = ZIid;
			ZI313 = ZIt;
			goto ZL2_318;
		    }
		    /*UNREACHED*/
		  default:
		    goto ZL1;
		}
	    }
	}
	/*UNREACHED*/
      default:
	{
	    ZI316 = ZI312;
	    ZI317 = ZI313;
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZO316 = ZI316;
    *ZO317 = ZI317;
}

static void
ZRspec_Hcommand(SID_COMMAND *ZOc)
{
    SID_COMMAND ZIc;

    switch (CURRENT_TERMINAL) {
      case 7:
	{
	    ADVANCE_LEXER;
	    {

    (ZIc) = null ;
	    }
	}
	break;
      case 9:
	{
	    SID_IDENTIFIER ZIid;
	    SID_STRING ZIp;
	    SID_STRING ZIs;

	    ADVANCE_LEXER;
	    ZRidentifier (&ZIid);
	    ZRdefine_Hparam_Hclause (&ZIp);
	    ZRconstant_Hvalue (&ZIs);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    char *def ;
    object *p = make_exp ( (ZIid).iname, (ZIid).ivers, OBJ_DEFINE ) ;
    if ( (ZIp) ) {
	if ( *(ZIp) ) {
	    def = string_printf ( "( %s ) %s", (ZIp), (ZIs) ) ;
	} else {
	    def = string_printf ( "() %s", (ZIs) ) ;
	}
    } else {
	def = string_printf ( " %s", (ZIs) ) ;
    }
    p->u.u_str = def ;
    (ZIc) = make_token ( (ZIid).ename, (ZIid).evers, p, OBJ_EXTERN ) ;
	    }
	}
	break;
      case 30:
	{
	    SID_IDENTIFIER ZIid;
	    SID_STRING ZIp;
	    SID_STRING ZIs;

	    ADVANCE_LEXER;
	    ZRidentifier (&ZIid);
	    ZRdefine_Hparam_Hclause (&ZIp);
	    ZRconstant_Hvalue (&ZIs);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    char *def ;
    object *p = make_exp ( (ZIid).iname, (ZIid).ivers, OBJ_DEFMIN ) ;
    if ( (ZIp) ) {
	if ( *(ZIp) ) {
	    def = string_printf ( "( %s ) %s", (ZIp), (ZIs) ) ;
	} else {
	    def = string_printf ( "() %s", (ZIs) ) ;
	}
    } else {
	def = string_printf ( " %s", (ZIs) ) ;
    }
    p->u.u_str = def ;
    (ZIc) = make_token ( (ZIid).ename, (ZIid).evers, p, OBJ_EXTERN ) ;
	    }
	}
	break;
      case 12:
	{
	    int ZItag;
	    SID_IDENTIFIER ZIid;
	    SID_COMMAND ZIe;

	    ADVANCE_LEXER;
	    ZRenum_Hcommand (&ZItag);
	    ZRidentifier (&ZIid);
	    switch (CURRENT_TERMINAL) {
	      case 60:
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 54:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRenumerator_Hlist (&ZIe);
	    switch (CURRENT_TERMINAL) {
	      case 55:
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    type *t = make_type ( (ZIid).iname, (ZIid).ivers, (ZItag) ) ;
    t->v.obj2 = (ZIe) ;
    (ZIc) = make_token ( (ZIid).ename, (ZIid).evers, t->u.obj, OBJ_TYPE ) ;
	    }
	}
	break;
      case 14:
	{
	    int ZItag;
	    SID_IDENTIFIER ZIid;
	    int ZIe;
	    SID_TYPE ZIt;
	    SID_COMMAND ZIa;
	    SID_COMMAND ZIb;

	    ADVANCE_LEXER;
	    ZRtype_Hcommand (&ZItag);
	    ZRidentifier (&ZIid);
	    ZRfield_Hexact (&ZIe);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = find_type ( (ZIid).iname, any_version, (ZItag), 0 ) ;
    if ( (ZIt) == null ) {
	(ZIt) = make_type ( (ZIid).iname, (ZIid).ivers, (ZItag) ) ;
	(ZIa) = make_token ( (ZIid).ename, (ZIid).evers, (ZIt)->u.obj, OBJ_TYPE ) ;
    } else {
	(ZIa) = null ;
    }
    (ZIt) = expand_type ( (ZIt) ) ;
    switch ( (ZIt)->id ) {
	case TYPE_STRUCT :
	case TYPE_UNION :
	case TYPE_STRUCT_TAG :
	case TYPE_UNION_TAG : {
	    break ;
	}
	default : {
	    error ( ERR_SERIOUS, "Illegal field type, '%s'", (ZIid).iname ) ;
	    break ;
	}
    }
    crt_field_name = (ZIt)->u.obj->name ;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 54:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRfield_Hlist (ZIt, &ZIb);
	    switch (CURRENT_TERMINAL) {
	      case 55:
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    if ( (ZIe) ) {
	if ( (ZIt)->v.obj2 ) {
	    char *nm = crt_field_name ;
	    error ( ERR_SERIOUS, "Redefinition of type '%s'", nm ) ;
	}
	if ( (ZIb) == null ) {
	    error ( ERR_SERIOUS, "Empty struct/union definition" ) ;
	} else {
	    (ZIt)->v.obj2 = (ZIb) ;
	}
	if ( (ZIa) == null ) {
	    /* This is a hack, do properly later */
	    (ZIc) = make_object ( null_str, OBJ_TYPE ) ;
	    (ZIc)->u.u_type = (ZIt) ;
	    if ( streq ( (ZIc)->filename, (ZIt)->u.obj->filename ) ) {
		(ZIt)->state = 1 ;
	    } else {
		(ZIt)->state = 3 ;
	    }
	} else {
	    (ZIc) = (ZIa) ;
	}
    } else {
	(ZIc) = join_object ( (ZIa), (ZIb) ) ;
    }
    crt_field_name = null ;
	    }
	}
	break;
      case 19:
	{
	    int ZIcmd;
	    SID_STRING ZIs;
	    SID_STRING ZIkey;

	    ADVANCE_LEXER;
	    {
 (ZIcmd) = OBJ_IMPLEMENT ; 
	    }
	    ZRsubset_Hname (&ZIs);
	    ZRsubset_Hkey (&ZIkey);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    object *p = make_subset ( (ZIs) ) ;
    update_time ( crt_object, p ) ;
    (ZIc) = make_object ( (ZIkey), (ZIcmd) ) ;
    (ZIc)->u.u_obj = p ;
	    }
	}
	break;
      case 21:
	{
	    int ZIlv;
	    SID_TYPE ZIs;
	    SID_IDENTIFIER ZIid;
	    SID_TYPE ZIp;
	    SID_TYPE ZIu;
	    SID_TYPE ZIv;
	    SID_TYPE ZIq;
	    SID_TYPE ZIt;

	    ADVANCE_LEXER;
	    ZRobject_Hqualifier (&ZIlv);
	    ZRqualified_Htype (&ZIs);
	    ZRmacro_Hdeclarator (&ZIid, &ZIp);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIu) = inject_type ( (ZIp), (ZIs) ) ;
	    }
	    {

    (ZIv) = make_subtype ( (ZIu), (ZIlv) ) ;
	    }
	    ZR287 (&ZIq);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = inject_type ( (ZIq), (ZIv) ) ;
	    }
	    {

    object *p ;
    int cmd = OBJ_MACRO ;
    if ( (ZIt)->id != TYPE_PROC ) cmd = OBJ_EXP ;
    p = make_exp ( (ZIid).iname, (ZIid).ivers, cmd ) ;
    p->u.u_type = check_type ( (ZIt), cmd ) ;
    (ZIc) = make_token ( (ZIid).ename, (ZIid).evers, p, cmd ) ;
	    }
	}
	break;
      case 22:
	{
	    ADVANCE_LEXER;
	    ZRnat_Hdeclarator_Hlist (&ZIc);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 24:
	{
	    SID_IDENTIFIER ZIid;
	    SID_TYPE ZIt;

	    ADVANCE_LEXER;
	    ZRidentifier (&ZIid);
	    ZR287 (&ZIt);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    object *p = make_exp ( (ZIid).iname, (ZIid).ivers, OBJ_STATEMENT ) ;
    p->u.u_type = check_type ( (ZIt), OBJ_STATEMENT ) ;
    (ZIc) = make_token ( (ZIid).ename, (ZIid).evers, p, OBJ_STATEMENT ) ;
	    }
	}
	break;
      case 26:
	{
	    SID_IDENTIFIER ZIid;
	    SID_STRING ZIs;

	    ADVANCE_LEXER;
	    ZRidentifier (&ZIid);
	    switch (CURRENT_TERMINAL) {
	      case 5:
		{
 ZIs = token_value ; 
		}
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    object *p = make_exp ( (ZIid).iname, (ZIid).ivers, OBJ_TOKEN ) ;
    p->u.u_str = (ZIs) ;
    (ZIc) = make_token ( (ZIid).ename, (ZIid).evers, p, OBJ_TOKEN ) ;
	    }
	}
	break;
      case 27:
	{
	    ADVANCE_LEXER;
	    ZRtype_Hdeclarator_Hlist (&ZIc);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 28:
	{
	    ADVANCE_LEXER;
	    ZR322 (&ZIc);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 29:
	{
	    int ZIcmd;

	    ADVANCE_LEXER;
	    {
 (ZIcmd) = OBJ_USE ; 
	    }
	    ZR323 (&ZIcmd, &ZIc);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 8: case 13:
	{
	    int ZIcmd;
	    int ZIlv1;
	    int ZIlv;
	    SID_TYPE ZIt;

	    ZRexp_Hcommand (&ZIcmd);
	    ZRobject_Hqualifier (&ZIlv1);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if ( (ZIcmd) == OBJ_CONST ) {
	if ( (ZIlv1) == TYPE_LVALUE ) {
	    error ( ERR_SERIOUS, "Constant can't be an lvalue" ) ;
	}
	(ZIlv) = TYPE_RVALUE ;
    } else if ( (ZIcmd) == OBJ_EXTERN ) {
	(ZIlv) = TYPE_LVALUE ;
    } else {
	(ZIlv) = (ZIlv1) ;
    }
	    }
	    ZRqualified_Htype (&ZIt);
	    ZRexp_Hdeclarator_Hlist (ZIcmd, ZIt, ZIlv, &ZIc);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 15:
	{
	    int ZIcmd;
	    SID_TYPE ZIs;
	    SID_IDENTIFIER ZIid;
	    SID_TYPE ZIp;
	    SID_TYPE ZIt;

	    ZRfunc_Hcommand (&ZIcmd);
	    ZRqualified_Htype (&ZIs);
	    ZRdeclarator (&ZIid, &ZIp);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = inject_type ( (ZIp), (ZIs) ) ;
	    }
	    {

    object *p = make_exp ( (ZIid).iname, (ZIid).ivers, (ZIcmd) ) ;
    p->u.u_type = check_type ( (ZIt), OBJ_FUNC ) ;
    (ZIc) = make_token ( (ZIid).ename, (ZIid).evers, p, (ZIcmd) ) ;
	    }
	}
	break;
      case 23:
	{
	    ZRsubset_Hcommand (&ZIc);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRfunc_Hcommand(int *ZOcmd)
{
    int ZIcmd;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	switch (CURRENT_TERMINAL) {
	  case 15:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR348 (&ZIcmd);
	if ((CURRENT_TERMINAL) == 75) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOcmd = ZIcmd;
}

static void
ZR320(SID_STRING *ZIa, SID_STRING *ZOs)
{
    SID_STRING ZIs;

    switch (CURRENT_TERMINAL) {
      case 62:
	{
	    SID_STRING ZIb;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 2:
		{
 ZIb = token_value ; 
		}
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR321 (ZIa, &ZIb, &ZIs);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    (ZIs) = subset_name ( (*ZIa), null_str, null_str ) ;
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOs = ZIs;
}

static void
ZR321(SID_STRING *ZIa, SID_STRING *ZIb, SID_STRING *ZOs)
{
    SID_STRING ZIs;

    switch (CURRENT_TERMINAL) {
      case 62:
	{
	    SID_STRING ZIc;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 2:
		{
 ZIc = token_value ; 
		}
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    if ( (*ZIb) [0] == 0 ) (*ZIb) = null ;
    (ZIs) = subset_name ( (*ZIa), (*ZIb), (ZIc) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZIs) = subset_name ( (*ZIa), (*ZIb), null_str ) ;
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOs = ZIs;
}

static void
ZRarray_Hoperator(SID_TYPE *ZOt)
{
    SID_TYPE ZIt;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_STRING ZIa;

	switch (CURRENT_TERMINAL) {
	  case 58:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{
	    switch (CURRENT_TERMINAL) {
	      case 0: case 1: case 5: case 67: case 68:
		{
		    ZRconstant_Hvalue (&ZIa);
		    if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIa) = "" ;
		    }
		}
		break;
	    }
	}
	switch (CURRENT_TERMINAL) {
	  case 59:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    (ZIt) = make_subtype ( ( type * ) null, TYPE_ARRAY ) ;
    (ZIt)->v.str = (ZIa) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOt = ZIt;
}

static void
ZR322(SID_COMMAND *ZOc)
{
    SID_COMMAND ZIc;

    switch (CURRENT_TERMINAL) {
      case 51:
	{
	    SID_TYPE ZIt;
	    SID_IDENTIFIER ZIid;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 56:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRqualified_Htype (&ZIt);
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRidentifier (&ZIid);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    type *t = make_type ( (ZIid).iname, (ZIid).ivers, TYPE_PROMOTE ) ;
    type *s = expand_type ( (ZIt) ) ;
    switch ( s->id ) {
	case TYPE_INT :
	case TYPE_SIGNED :
	case TYPE_UNSIGNED : {
	    break ;
	}
	default : {
	    error ( ERR_SERIOUS, "Non-integral promotion type" ) ;
	    break ;
	}
    }
    t->v.next = s ;
    (ZIc) = make_token ( (ZIid).ename, (ZIid).evers, t->u.obj, OBJ_EXTERN ) ;
	    }
	}
	break;
      case 53:
	{
	    SID_STRING ZIs;
	    SID_TYPE ZIt;
	    SID_IDENTIFIER ZIid;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 56:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 2:
		{
 ZIs = token_value ; 
		}
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZIt) = special_type ( (ZIs) ) ;
	    }
	    ZRidentifier (&ZIid);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    type *t = make_type ( (ZIid).iname, (ZIid).ivers, TYPE_DEFINED ) ;
    t->v.next = check_type ( (ZIt), OBJ_TYPE ) ;
    (ZIc) = make_token ( (ZIid).ename, (ZIid).evers, t->u.obj, OBJ_EXTERN ) ;
	    }
	}
	break;
      case 0: case 32: case 33: case 34: case 35:
      case 37: case 38: case 39: case 42: case 43:
      case 44: case 45: case 46: case 47: case 48:
	{
	    SID_TYPE ZIs;
	    SID_IDENTIFIER ZIid;
	    SID_TYPE ZIp;
	    SID_TYPE ZIt;

	    ZRqualified_Htype (&ZIs);
	    ZRdeclarator (&ZIid, &ZIp);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = inject_type ( (ZIp), (ZIs) ) ;
	    }
	    {

    type *t = make_type ( (ZIid).iname, (ZIid).ivers, TYPE_DEFINED ) ;
    t->v.next = check_type ( (ZIt), OBJ_TYPE ) ;
    (ZIc) = make_token ( (ZIid).ename, (ZIid).evers, t->u.obj, OBJ_EXTERN ) ;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZR323(int *ZIcmd, SID_COMMAND *ZOc)
{
    SID_COMMAND ZIc;

    switch (CURRENT_TERMINAL) {
      case 2:
	{
	    SID_STRING ZIs;
	    SID_STRING ZIkey;

	    ZRsubset_Hname (&ZIs);
	    ZRsubset_Hkey (&ZIkey);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    object *p = make_subset ( (ZIs) ) ;
    update_time ( crt_object, p ) ;
    (ZIc) = make_object ( (ZIkey), (*ZIcmd) ) ;
    (ZIc)->u.u_obj = p ;
	    }
	}
	break;
      case 56:
	{
	    SID_STRING ZIs;
	    SID_STRING ZIkey1;
	    SID_STRING ZIkey;

	    ZRuse_Hsubset_Hname (&ZIs);
	    ZRsubset_Hkey (&ZIkey1);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {
 (ZIkey) = string_concat ( (ZIkey1), "G" ) ; 
	    }
	    {

    object *p = make_subset ( (ZIs) ) ;
    update_time ( crt_object, p ) ;
    (ZIc) = make_object ( (ZIkey), (*ZIcmd) ) ;
    (ZIc)->u.u_obj = p ;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRmacro_Hparam_Hlist(SID_TYPE *ZOp)
{
    SID_TYPE ZIp;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_TYPE ZIt;
	SID_TYPE ZIq;

	ZRmacro_Hparam_Hdeclaration (&ZIt);
	{
	    switch (CURRENT_TERMINAL) {
	      case 62:
		{
		    ADVANCE_LEXER;
		    ZRmacro_Hparam_Hlist (&ZIq);
		    if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIq) = null ;
		    }
		}
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	{

    (ZIp) = make_subtype ( (ZIt), TYPE_LIST ) ;
    (ZIp)->v.next = (ZIq) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZR324(SID_STRING *ZInm, int *ZIv, SID_IDENTIFIER *ZOid)
{
    SID_IDENTIFIER ZIid;

    switch (CURRENT_TERMINAL) {
      case 69:
	{
	    SID_STRING ZItnm;
	    int ZItv;

	    ADVANCE_LEXER;
	    ZRexternal_Hname (&ZItnm, &ZItv);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIid).iname = (*ZInm) ;
    (ZIid).ivers = (*ZIv) ;
    (ZIid).ename = (ZItnm) ;
    (ZIid).evers = (ZItv) ;
	    }
	}
	break;
      default:
	{
	    SID_STRING ZItnm;

	    {

    (ZItnm) = token_name ( (*ZInm) ) ;
	    }
	    {

    (ZIid).iname = (*ZInm) ;
    (ZIid).ivers = (*ZIv) ;
    (ZIid).ename = (ZItnm) ;
    (ZIid).evers = (*ZIv) ;
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOid = ZIid;
}

static void
ZR325(SID_STRING *ZOp)
{
    SID_STRING ZIp;

    switch (CURRENT_TERMINAL) {
      case 57:
	{
	    ADVANCE_LEXER;
	    {
 (ZIp) = "" ; 
	    }
	}
	break;
      case 0:
	{
	    ZRdefine_Hparam_Hlist (&ZIp);
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZR328(SID_STRING *ZI326, SID_STRING *ZOp)
{
    SID_STRING ZIp;

    switch (CURRENT_TERMINAL) {
      case 62:
	{
	    SID_STRING ZIq;

	    ADVANCE_LEXER;
	    ZRdefine_Hparam_Hlist (&ZIq);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIp) = string_printf ( "%s, %s", (*ZI326), (ZIq) ) ;
	    }
	}
	break;
      default:
	{
	    ZIp = *ZI326;
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRenum_Hcommand(int *ZOtag)
{
    int ZItag;

    switch (CURRENT_TERMINAL) {
      case 35:
	{
	    ADVANCE_LEXER;
	    {
 (ZItag) = TYPE_ENUM_TAG ; 
	    }
	}
	break;
      default:
	{
	    {
 (ZItag) = TYPE_ENUM ; 
	    }
	}
	break;
      case 75:
	return;
    }
    *ZOtag = ZItag;
}

static void
ZRenumerator(SID_COMMAND *ZOc)
{
    SID_COMMAND ZIc;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_IDENTIFIER ZIid;
	SID_STRING ZIs;

	ZRidentifier (&ZIid);
	{
	    switch (CURRENT_TERMINAL) {
	      case 66:
		{
		    ADVANCE_LEXER;
		    ZRconstant_Hvalue (&ZIs);
		    if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIs) = "" ;
		    }
		}
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	{

    object *p = make_exp ( (ZIid).iname, (ZIid).ivers, OBJ_ENUMVAL ) ;
    p->u.u_str = (ZIs) ;
    (ZIc) = make_token ( (ZIid).ename, (ZIid).evers, p, OBJ_EXTERN ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZR329(int *ZOcmd)
{
    int ZIcmd;

    switch (CURRENT_TERMINAL) {
      case 56:
	{
	    ADVANCE_LEXER;
	    ZR330 (&ZIcmd);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZIcmd) = OBJ_EXP ; 
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOcmd = ZIcmd;
}

static void
ZRfield_Hdeclarator_Hlist(SID_TYPE ZIm, SID_TYPE ZIs, SID_COMMAND *ZOc)
{
    SID_COMMAND ZIc;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_IDENTIFIER ZIid;
	SID_TYPE ZIp;
	SID_TYPE ZIt;
	SID_COMMAND ZIa;
	SID_COMMAND ZIb;

	ZRfield_Hdeclarator (&ZIid, &ZIp);
	if ((CURRENT_TERMINAL) == 75) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZIt) = inject_type ( (ZIp), (ZIs) ) ;
	}
	{

    type *t = check_type ( (ZIt), OBJ_FIELD ) ;
    field *f = make_field ( (ZIid).iname, (ZIid).ivers, (ZIm), t ) ;
    (ZIa) = make_token ( (ZIid).ename, (ZIid).evers, f->obj, OBJ_FIELD ) ;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 62:
		{
		    ADVANCE_LEXER;
		    ZRfield_Hdeclarator_Hlist (ZIm, ZIs, &ZIb);
		    if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		}
		break;
	      default:
		{
		    {

    (ZIb) = null ;
		    }
		}
		break;
	    }
	}
	{

    (ZIc) = join_object ( (ZIa), (ZIb) ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZR330(int *ZOcmd)
{
    int ZIcmd;

    switch (CURRENT_TERMINAL) {
      case 33:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZIcmd) = OBJ_CONST ; 
	    }
	}
	break;
      case 36:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZIcmd) = OBJ_EXTERN ; 
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOcmd = ZIcmd;
}

static void
ZRfield_Hexact(int *ZOe)
{
    int ZIe;

    switch (CURRENT_TERMINAL) {
      case 60:
	{
	    ADVANCE_LEXER;
	    {
 (ZIe) = 1 ; 
	    }
	}
	break;
      default:
	{
	    {
 (ZIe) = 0 ; 
	    }
	}
	break;
      case 75:
	return;
    }
    *ZOe = ZIe;
}

static void
ZR333(SID_TYPE *ZI331, SID_TYPE *ZOt)
{
    SID_TYPE ZIt;

    switch (CURRENT_TERMINAL) {
      case 33: case 48:
	{
	    unsigned ZIcv;

	    ZRtype_Hqualifier (&ZIcv);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = make_subtype ( (*ZI331), TYPE_QUALIFIER ) ;
    (ZIt)->v.str = cv_qualifier [ (ZIcv) ] ;
	    }
	}
	break;
      default:
	{
	    ZIt = *ZI331;
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOt = ZIt;
}

static void
ZR335(SID_TYPE *ZOt)
{
    SID_TYPE ZIt;

    switch (CURRENT_TERMINAL) {
      case 57:
	{
	    SID_TYPE ZIp;

	    ADVANCE_LEXER;
	    {

    error ( ERR_WARNING, "Empty parameter list" ) ;
    (ZIp) = null ;
	    }
	    {

    (ZIt) = make_subtype ( ( type * ) null, TYPE_PROC ) ;
    (ZIt)->v.next = (ZIp) ;
	    }
	}
	break;
      case 0: case 32: case 33: case 34: case 35:
      case 37: case 38: case 39: case 42: case 43:
      case 44: case 45: case 46: case 47: case 48:
	{
	    SID_TYPE ZIp;

	    ZRparameter_Hlist (&ZIp);
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZIt) = make_subtype ( ( type * ) null, TYPE_PROC ) ;
    (ZIt)->v.next = (ZIp) ;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOt = ZIt;
}

static void
ZRcommand_Hlist(SID_COMMAND *ZOc)
{
    SID_COMMAND ZIc;

  ZL2_command_Hlist:;
    switch (CURRENT_TERMINAL) {
      case 7: case 8: case 9: case 12: case 13:
      case 14: case 15: case 19: case 21: case 22:
      case 23: case 24: case 26: case 27: case 28:
      case 29: case 30:
	{
	    SID_COMMAND ZIa;
	    SID_COMMAND ZIb;

	    ZRspec_Hcommand (&ZIa);
	    switch (CURRENT_TERMINAL) {
	      case 71:
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRcommand_Hlist (&ZIb);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIc) = join_object ( (ZIa), (ZIb) ) ;
	    }
	}
	break;
      case 4: case 5: case 6: case 16: case 17:
      case 18:
	{
	    SID_COMMAND ZIa;
	    SID_COMMAND ZIb;

	    ZRtext_Hcommand (&ZIa);
	    ZRcommand_Hlist (&ZIb);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIc) = join_object ( (ZIa), (ZIb) ) ;
	    }
	}
	break;
      case 3: case 20:
	{
	    ZRvariable_Hcommand ();
	    switch (CURRENT_TERMINAL) {
	      case 71:
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    goto ZL2_command_Hlist;
	}
	/*UNREACHED*/
      default:
	{
	    {

    (ZIc) = null ;
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZR338(SID_STRING *ZI336, SID_TYPE *ZI337, SID_STRING *ZO306, SID_TYPE *ZO307)
{
    SID_STRING ZI306;
    SID_TYPE ZI307;

    switch (CURRENT_TERMINAL) {
      case 56:
	{
	    SID_TYPE ZIs;
	    SID_TYPE ZIt;

	    ZRfunction_Hoperator (&ZIs);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = inject_type ( (*ZI337), (ZIs) ) ;
	    }
	    ZR308 (*ZI336, ZIt, &ZI306, &ZI307);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    ZR308 (*ZI336, *ZI337, &ZI306, &ZI307);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZO306 = ZI306;
    *ZO307 = ZI307;
}

static void
ZR339(SID_TYPE *ZOq)
{
    SID_TYPE ZIq;

    switch (CURRENT_TERMINAL) {
      case 65:
	{
	    ADVANCE_LEXER;
	    {

    (ZIq) = make_subtype ( type_ellipsis, TYPE_LIST ) ;
    (ZIq)->v.next = null ;
	    }
	}
	break;
      case 0: case 32: case 33: case 34: case 35:
      case 37: case 38: case 39: case 42: case 43:
      case 44: case 45: case 46: case 47: case 48:
	{
	    ZRparameter_Hlist (&ZIq);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOq = ZIq;
}

static void
ZR340(int *ZOtag)
{
    int ZItag;

    switch (CURRENT_TERMINAL) {
      case 31:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZItag) = TYPE_ARITH ; 
	    }
	}
	break;
      case 37:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZItag) = TYPE_FLOAT ; 
	    }
	}
	break;
      case 38:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZItag) = TYPE_INT ; 
	    }
	}
	break;
      case 41:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZItag) = TYPE_SCALAR ; 
	    }
	}
	break;
      case 43:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZItag) = TYPE_SIGNED ; 
	    }
	}
	break;
      case 44:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZItag) = TYPE_STRUCT ; 
	    }
	}
	break;
      case 45:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZItag) = TYPE_UNION ; 
	    }
	}
	break;
      case 46:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZItag) = TYPE_UNSIGNED ; 
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOtag = ZItag;
}

static void
ZRdirect_Hdeclarator(SID_IDENTIFIER *ZO316, SID_TYPE *ZO317)
{
    SID_IDENTIFIER ZI316;
    SID_TYPE ZI317;

    switch (CURRENT_TERMINAL) {
      case 56:
	{
	    SID_IDENTIFIER ZIid;
	    SID_TYPE ZIt;

	    ADVANCE_LEXER;
	    ZRdeclarator (&ZIid, &ZIt);
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR318 (ZIid, ZIt, &ZI316, &ZI317);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 0:
	{
	    SID_IDENTIFIER ZIid;
	    SID_TYPE ZIt;

	    ZRidentifier (&ZIid);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = null ;
	    }
	    ZR318 (ZIid, ZIt, &ZI316, &ZI317);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZO316 = ZI316;
    *ZO317 = ZI317;
}

static void
ZRtype_Hcommand(int *ZOtag)
{
    int ZItag;

    switch (CURRENT_TERMINAL) {
      case 56:
	{
	    ADVANCE_LEXER;
	    ZR340 (&ZItag);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 44:
	{
	    ADVANCE_LEXER;
	    {
 (ZItag) = TYPE_STRUCT_TAG ; 
	    }
	}
	break;
      case 45:
	{
	    ADVANCE_LEXER;
	    {
 (ZItag) = TYPE_UNION_TAG ; 
	    }
	}
	break;
      default:
	{
	    {
 (ZItag) = TYPE_GENERIC ; 
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOtag = ZItag;
}

static void
ZRtext_Hcommand(SID_COMMAND *ZOc)
{
    SID_COMMAND ZIc;

    switch (CURRENT_TERMINAL) {
      case 6:
	{
	    SID_STRING ZIs;

	    {
 ZIs = token_value ; 
	    }
	    ADVANCE_LEXER;
	    {

    (ZIc) = make_object ( (ZIs), OBJ_TEXT_SRC ) ;
	    }
	}
	break;
      case 4:
	{
	    SID_STRING ZIs;

	    {
 ZIs = token_value ; 
	    }
	    ADVANCE_LEXER;
	    {

    (ZIc) = make_object ( (ZIs), OBJ_TEXT_INCL ) ;
	    }
	}
	break;
      case 5:
	{
	    SID_STRING ZIs;

	    {
 ZIs = token_value ; 
	    }
	    ADVANCE_LEXER;
	    {

    (ZIc) = make_object ( (ZIs), OBJ_TEXT_INCL ) ;
	    }
	}
	break;
      case 16: case 17: case 18:
	{
	    SID_COMMAND ZIi;
	    SID_STRING ZIs;
	    SID_COMMAND ZIa;
	    SID_COMMAND ZIb;

	    ZRif_Hcommand (&ZIi, &ZIs);
	    ZRcommand_Hlist (&ZIa);
	    {
		switch (CURRENT_TERMINAL) {
		  case 10:
		    {
			ADVANCE_LEXER;
			ZRcommand_Hlist (&ZIb);
			if ((CURRENT_TERMINAL) == 75) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  default:
		    {
			{

    (ZIb) = null ;
			}
		    }
		    break;
		  case 75:
		    RESTORE_LEXER;
		    goto ZL1;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 11:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    object *p, *q ;
    p = join_object ( (ZIi), (ZIa) ) ;
    if ( (ZIb) ) {
	q = make_object ( (ZIs), OBJ_IF ) ;
	q->u.u_num = CMD_ELSE ;
	p = join_object ( p, q ) ;
	p = join_object ( p, (ZIb) ) ;
    }
    q = make_object ( (ZIs), OBJ_IF ) ;
    q->u.u_num = CMD_ENDIF ;
    (ZIc) = join_object ( p, q ) ;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZR347(SID_IDENTIFIER *ZI345, SID_IDENTIFIER *ZOid, SID_TYPE *ZOt)
{
    SID_IDENTIFIER ZIid;
    SID_TYPE ZIt;

    switch (CURRENT_TERMINAL) {
      case 61:
	{
	    ZRbitfield_Hoperator (&ZIt);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    ZIid = *ZI345;
	}
	break;
      default:
	{
	    SID_TYPE ZI344;

	    {

    (ZI344) = null ;
	    }
	    ZR318 (*ZI345, ZI344, &ZIid, &ZIt);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOid = ZIid;
    *ZOt = ZIt;
}

static void
ZRname_Hversion(int *ZOv)
{
    int ZIv;

    switch (CURRENT_TERMINAL) {
      case 63:
	{
	    SID_STRING ZIn;

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
	    {

    (ZIv) = atoi ( (ZIn) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZIv) = no_version ;
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOv = ZIv;
}

static void
ZR348(int *ZOcmd)
{
    int ZIcmd;

    switch (CURRENT_TERMINAL) {
      case 56:
	{
	    ADVANCE_LEXER;
	    ZR349 (&ZIcmd);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZIcmd) = OBJ_FUNC ; 
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOcmd = ZIcmd;
}

static void
ZRdirect_Habstract_Hdeclarator(SID_STRING *ZO306, SID_TYPE *ZO307)
{
    SID_STRING ZI306;
    SID_TYPE ZI307;

    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    SID_STRING ZInm;
	    SID_TYPE ZIt;

	    {
 ZInm = token_value ; 
	    }
	    ADVANCE_LEXER;
	    {

    (ZIt) = null ;
	    }
	    ZR308 (ZInm, ZIt, &ZI306, &ZI307);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 56:
	{
	    SID_STRING ZI336;
	    SID_TYPE ZI337;

	    ADVANCE_LEXER;
	    ZRabstract_Hdeclarator (&ZI336, &ZI337);
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR338 (&ZI336, &ZI337, &ZI306, &ZI307);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    SID_STRING ZInm;
	    SID_TYPE ZIt;

	    {

    (ZInm) = null ;
	    }
	    {

    (ZIt) = null ;
	    }
	    ZR308 (ZInm, ZIt, &ZI306, &ZI307);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZO306 = ZI306;
    *ZO307 = ZI307;
}

static void
ZRfield_Hdeclarator(SID_IDENTIFIER *ZOid, SID_TYPE *ZOt)
{
    SID_IDENTIFIER ZIid;
    SID_TYPE ZIt;

    switch (CURRENT_TERMINAL) {
      case 56:
	{
	    SID_IDENTIFIER ZI341;
	    SID_TYPE ZI342;

	    ADVANCE_LEXER;
	    ZRdeclarator (&ZI341, &ZI342);
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR318 (ZI341, ZI342, &ZIid, &ZIt);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 61:
	{
	    ZRbitfield_Hoperator (&ZIt);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    char *nm = string_printf ( "%s%d", HIDDEN_NAME, anon_no++ ) ;
    if ( crt_field_name ) {
	nm = string_printf ( "%s.%s", crt_field_name, nm ) ;
    }
    (ZIid).iname = nm ;
    (ZIid).ivers = no_version ;
    (ZIid).ename = token_name ( nm ) ;
    (ZIid).evers = no_version ;
	    }
	}
	break;
      case 0:
	{
	    SID_IDENTIFIER ZI345;

	    ZRidentifier (&ZI345);
	    ZR347 (&ZI345, &ZIid, &ZIt);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 72:
	{
	    SID_TYPE ZIp;
	    SID_TYPE ZIs;

	    ZRptr_Hoperator (&ZIp);
	    ZRdeclarator (&ZIid, &ZIs);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = inject_type ( (ZIs), (ZIp) ) ;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOid = ZIid;
    *ZOt = ZIt;
}

static void
ZRvariable_Hcommand(void)
{
    switch (CURRENT_TERMINAL) {
      case 20:
	{
	    SID_STRING ZIs;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 2:
		{
 ZIs = token_value ; 
		}
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 3:
	{
	    SID_STRING ZInm;

	    {
 ZInm = token_value ; 
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 66:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR354 (&ZInm);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (75);
    return;
}

static void
ZR349(int *ZOcmd)
{
    int ZIcmd;

    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZIcmd) = OBJ_EXTERN ; 
	    }
	}
	break;
      case 49:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZIcmd) = OBJ_WEAK ; 
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOcmd = ZIcmd;
}

static void
ZR350(SID_TYPE *ZOt)
{
    SID_TYPE ZIt;

    switch (CURRENT_TERMINAL) {
      case 57:
	{
	    SID_TYPE ZIp;

	    ADVANCE_LEXER;
	    {

    (ZIp) = null ;
	    }
	    {

    (ZIt) = make_subtype ( ( type * ) null, TYPE_PROC ) ;
    (ZIt)->v.next = (ZIp) ;
	    }
	}
	break;
      case 0: case 32: case 33: case 34: case 35:
      case 37: case 38: case 39: case 40: case 42:
      case 43: case 44: case 45: case 46: case 47:
      case 48:
	{
	    SID_TYPE ZIp;

	    ZRmacro_Hparam_Hlist (&ZIp);
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZIt) = make_subtype ( ( type * ) null, TYPE_PROC ) ;
    (ZIt)->v.next = (ZIp) ;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOt = ZIt;
}

static void
ZR351(SID_STRING *ZOkey)
{
    SID_STRING ZIkey;

    switch (CURRENT_TERMINAL) {
      case 67:
	{
	    ADVANCE_LEXER;
	    ZR352 (&ZIkey);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 70:
	{
	    ADVANCE_LEXER;
	    ZR353 (&ZIkey);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOkey = ZIkey;
}

static void
ZRdefine_Hparam_Hclause(SID_STRING *ZOp)
{
    SID_STRING ZIp;

    switch (CURRENT_TERMINAL) {
      case 56:
	{
	    ADVANCE_LEXER;
	    ZR325 (&ZIp);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {
 (ZIp) = null ; 
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOp = ZIp;
}

static void
ZRexp_Hcommand(int *ZOcmd)
{
    int ZIcmd;

    switch (CURRENT_TERMINAL) {
      case 8:
	{
	    ADVANCE_LEXER;
	    {
 (ZIcmd) = OBJ_CONST ; 
	    }
	}
	break;
      case 13:
	{
	    ADVANCE_LEXER;
	    ZR329 (&ZIcmd);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOcmd = ZIcmd;
}

static void
ZR352(SID_STRING *ZOkey)
{
    SID_STRING ZIkey;

    switch (CURRENT_TERMINAL) {
      case 67:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZIkey) = "11" ; 
	    }
	}
	break;
      case 70:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZIkey) = "10" ; 
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOkey = ZIkey;
}

static void
ZRif_Hcommand(SID_COMMAND *ZOc, SID_STRING *ZOs)
{
    SID_COMMAND ZIc;
    SID_STRING ZIs;

    switch (CURRENT_TERMINAL) {
      case 16:
	{
	    ADVANCE_LEXER;
	    ZRconstant_Hvalue (&ZIs);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIc) = make_object ( (ZIs), OBJ_IF ) ;
    (ZIc)->u.u_num = CMD_IF ;
	    }
	}
	break;
      case 17:
	{
	    ADVANCE_LEXER;
	    ZRifdef_Hmacro_Hname (&ZIs);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIc) = make_object ( (ZIs), OBJ_IF ) ;
    (ZIc)->u.u_num = CMD_IFDEF ;
	    }
	}
	break;
      case 18:
	{
	    ADVANCE_LEXER;
	    ZRifdef_Hmacro_Hname (&ZIs);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIc) = make_object ( (ZIs), OBJ_IF ) ;
    (ZIc)->u.u_num = CMD_IFNDEF ;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOc = ZIc;
    *ZOs = ZIs;
}

static void
ZR353(SID_STRING *ZOkey)
{
    SID_STRING ZIkey;

    switch (CURRENT_TERMINAL) {
      case 67:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZIkey) = "01" ; 
	    }
	}
	break;
      case 70:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 57:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {
 (ZIkey) = "00" ; 
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOkey = ZIkey;
}

static void
ZR354(SID_STRING *ZInm)
{
    switch (CURRENT_TERMINAL) {
      case 68:
	{
	    SID_STRING ZIs;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
 ZIs = token_value ; 
		}
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    set_integer ( (*ZInm), -atoi ( (ZIs) ) ) ;
	    }
	}
	break;
      case 1:
	{
	    SID_STRING ZIs;

	    {
 ZIs = token_value ; 
	    }
	    ADVANCE_LEXER;
	    {

    set_integer ( (*ZInm), atoi ( (ZIs) ) ) ;
	    }
	}
	break;
      case 2:
	{
	    SID_STRING ZIs;

	    {
 ZIs = token_value ; 
	    }
	    ADVANCE_LEXER;
	    {

    set_string ( (*ZInm), (ZIs) ) ;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (75);
    return;
}

static void
ZRbitfield_Hoperator(SID_TYPE *ZOt)
{
    SID_TYPE ZIt;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_STRING ZIa;

	switch (CURRENT_TERMINAL) {
	  case 61:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRconstant_Hvalue (&ZIa);
	if ((CURRENT_TERMINAL) == 75) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZIt) = make_subtype ( ( type * ) null, TYPE_BITFIELD ) ;
    (ZIt)->v.str = (ZIa) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOt = ZIt;
}

static void
ZRuse_Hsubset_Hname(SID_STRING *ZOs)
{
    SID_STRING ZIs;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_STRING ZIa;
	SID_STRING ZIb;

	switch (CURRENT_TERMINAL) {
	  case 56:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 2:
	    {
 ZIa = token_value ; 
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 57:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 62:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 2:
	    {
 ZIb = token_value ; 
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    (ZIs) = subset_name ( (ZIa), (ZIb), null_str ) ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOs = ZIs;
}

void
read_spec(SID_COMMAND *ZOc)
{
    SID_COMMAND ZIc;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	ZRsubset_Hcommand (&ZIc);
	switch (CURRENT_TERMINAL) {
	  case 71:
	    break;
	  case 75:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 73:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    goto ZL0;
  ZL1:;
    {
	{

    error ( ERR_SERIOUS, "Syntax error" ) ;
	}
	{

    (ZIc) = null ;
	}
    }
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRmacro_Hdeclarator(SID_IDENTIFIER *ZOid, SID_TYPE *ZOt)
{
    SID_IDENTIFIER ZIid;
    SID_TYPE ZIt;

    switch (CURRENT_TERMINAL) {
      case 0:
	{
	    ZRidentifier (&ZIid);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = null ;
	    }
	}
	break;
      case 72:
	{
	    SID_TYPE ZIp;
	    SID_TYPE ZIs;

	    ZRptr_Hoperator (&ZIp);
	    ZRmacro_Hdeclarator (&ZIid, &ZIs);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIt) = inject_type ( (ZIs), (ZIp) ) ;
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOid = ZIid;
    *ZOt = ZIt;
}

static void
ZRsubset_Hname(SID_STRING *ZOs)
{
    SID_STRING ZIs;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	SID_STRING ZIa;

	switch (CURRENT_TERMINAL) {
	  case 2:
	    {
 ZIa = token_value ; 
	    }
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZR320 (&ZIa, &ZIs);
	if ((CURRENT_TERMINAL) == 75) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOs = ZIs;
}

static void
ZRbuiltin_Htype(unsigned *ZOb)
{
    unsigned ZIb;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	unsigned ZIa;
	unsigned ZIc;

	ZRtype_Hkeyword (&ZIa);
	{
	    switch (CURRENT_TERMINAL) {
	      case 32: case 34: case 37: case 38: case 39:
	      case 42: case 43: case 46: case 47:
		{
		    unsigned ZId;

		    ZRbuiltin_Htype (&ZId);
		    if ((CURRENT_TERMINAL) == 75) {
			RESTORE_LEXER;
			goto ZL1;
		    }
		    {

    while ( (ZIa) & (ZId) ) {
	if ( (ZIa) == BTYPE_LONG && allow_long_long ) {
	    (ZIa) = BTYPE_LLONG ;
	} else {
	    error ( ERR_SERIOUS, "Duplicate type specifier" ) ;
	    break ;
	}
    }
    (ZIc) = ( (ZIa) | (ZId) ) ;
		    }
		}
		break;
	      default:
		{
		    ZIc = ZIa;
		}
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	ZIb = ZIc;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOb = ZIb;
}

static void
ZRobject_Hqualifier(int *ZOlv)
{
    int ZIlv;

    switch (CURRENT_TERMINAL) {
      case 40:
	{
	    ADVANCE_LEXER;
	    {
 (ZIlv) = TYPE_LVALUE ; 
	    }
	}
	break;
      default:
	{
	    {
 (ZIlv) = TYPE_RVALUE ; 
	    }
	}
	break;
      case 75:
	return;
    }
    *ZOlv = ZIlv;
}

static void
ZRfield_Hlist(SID_TYPE ZIm, SID_COMMAND *ZOc)
{
    SID_COMMAND ZIc;

    switch (CURRENT_TERMINAL) {
      case 16: case 17: case 18:
	{
	    SID_COMMAND ZIi;
	    SID_STRING ZIs;
	    SID_COMMAND ZIa;
	    SID_COMMAND ZIb;
	    SID_COMMAND ZIc1;
	    SID_COMMAND ZIc2;

	    ZRif_Hcommand (&ZIi, &ZIs);
	    ZRfield_Hlist (ZIm, &ZIa);
	    {
		switch (CURRENT_TERMINAL) {
		  case 10:
		    {
			ADVANCE_LEXER;
			ZRfield_Hlist (ZIm, &ZIb);
			if ((CURRENT_TERMINAL) == 75) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  default:
		    {
			{

    (ZIb) = null ;
			}
		    }
		    break;
		  case 75:
		    RESTORE_LEXER;
		    goto ZL1;
		}
	    }
	    switch (CURRENT_TERMINAL) {
	      case 11:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    object *p, *q ;
    p = join_object ( (ZIi), (ZIa) ) ;
    if ( (ZIb) ) {
	q = make_object ( (ZIs), OBJ_IF ) ;
	q->u.u_num = CMD_ELSE ;
	p = join_object ( p, q ) ;
	p = join_object ( p, (ZIb) ) ;
    }
    q = make_object ( (ZIs), OBJ_IF ) ;
    q->u.u_num = CMD_ENDIF ;
    (ZIc1) = join_object ( p, q ) ;
	    }
	    ZRfield_Hlist (ZIm, &ZIc2);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIc) = join_object ( (ZIc1), (ZIc2) ) ;
	    }
	}
	break;
      case 0: case 32: case 33: case 34: case 35:
      case 37: case 38: case 39: case 42: case 43:
      case 44: case 45: case 46: case 47: case 48:
	{
	    SID_TYPE ZIt;
	    SID_COMMAND ZIa;
	    SID_COMMAND ZIb;

	    ZRqualified_Htype (&ZIt);
	    ZRfield_Hdeclarator_Hlist (ZIm, ZIt, &ZIa);
	    switch (CURRENT_TERMINAL) {
	      case 71:
		break;
	      case 75:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRfield_Hlist (ZIm, &ZIb);
	    if ((CURRENT_TERMINAL) == 75) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIc) = join_object ( (ZIa), (ZIb) ) ;
	    }
	}
	break;
      default:
	{
	    {

    (ZIc) = null ;
	    }
	}
	break;
      case 75:
	return;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOc = ZIc;
}

static void
ZRptr_Hoperator(SID_TYPE *ZOt)
{
    SID_TYPE ZIt;

    if ((CURRENT_TERMINAL) == 75) {
	return;
    }
    {
	unsigned ZIcv;

	switch (CURRENT_TERMINAL) {
	  case 72:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRtype_Hqualifier_Hopt (&ZIcv);
	if ((CURRENT_TERMINAL) == 75) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZIt) = make_subtype ( ( type * ) null, TYPE_PTR ) ;
    (ZIt)->v.str = cv_qualifier [ (ZIcv) ] ;
	}
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOt = ZIt;
}

static void
ZRtype_Hkeyword(unsigned *ZOb)
{
    unsigned ZIb;

    switch (CURRENT_TERMINAL) {
      case 32:
	{
	    ADVANCE_LEXER;
	    {
 (ZIb) = BTYPE_CHAR ; 
	    }
	}
	break;
      case 34:
	{
	    ADVANCE_LEXER;
	    {
 (ZIb) = BTYPE_DOUBLE ; 
	    }
	}
	break;
      case 37:
	{
	    ADVANCE_LEXER;
	    {
 (ZIb) = BTYPE_FLOAT ; 
	    }
	}
	break;
      case 38:
	{
	    ADVANCE_LEXER;
	    {
 (ZIb) = BTYPE_INT ; 
	    }
	}
	break;
      case 39:
	{
	    ADVANCE_LEXER;
	    {
 (ZIb) = BTYPE_LONG ; 
	    }
	}
	break;
      case 42:
	{
	    ADVANCE_LEXER;
	    {
 (ZIb) = BTYPE_SHORT ; 
	    }
	}
	break;
      case 43:
	{
	    ADVANCE_LEXER;
	    {
 (ZIb) = BTYPE_SIGNED ; 
	    }
	}
	break;
      case 46:
	{
	    ADVANCE_LEXER;
	    {
 (ZIb) = BTYPE_UNSIGNED ; 
	    }
	}
	break;
      case 47:
	{
	    ADVANCE_LEXER;
	    {
 (ZIb) = BTYPE_VOID ; 
	    }
	}
	break;
      case 75:
	return;
      default:
	goto ZL1;
    }
    goto ZL0;
  ZL1:;
    SAVE_LEXER (75);
    return;
  ZL0:;
    *ZOb = ZIb;
}

/* BEGINNING OF TRAILER */



/* END OF FILE */
