/*
 * Automatically generated from the files:
 *	/u/g/release/Source/src/tools/pl/syntax.sid
 * and
 *	/u/g/release/Source/src/tools/pl/syntax.act
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
#include "util.h"
#include "defs.h"
#include "encodings.h"
#include "enc_nos.h"
#include "consfile.h"
#include "lex.h"
#include "analyse_sort.h"
#include "find_id.h"
#include "readstreams.h"
#include "standardsh.h"
#include "syntax.h"
#include "units.h"

#if FS_TENDRA
#pragma TenDRA begin
#pragma TenDRA unreachable code allow
#pragma TenDRA variable analysis off
#endif

static int saved = 0 ;
#define CURRENT_TERMINAL (unsigned)lex_v.t
#define ADVANCE_LEXER lex_v = reader ()
#define SAVE_LEXER(e) ((saved = lex_v.t), (lex_v.t = (e)))
#define RESTORE_LEXER (lex_v.t = saved)

typedef Al_tagdec *PTR_Al_tagdec ;
typedef Labdec *PTR_Labdec ;
typedef char *PTR_char ;
typedef Tagdec *PTR_Tagdec ;
typedef TDF *PTR_TDF ;
typedef Tokdec *PTR_Tokdec ;
typedef Tokpar *PTR_Tokpar ;
typedef unsigned long unsigned_long ;


static Tokpar * g_tokpars;
static Sort g_sname;
static TDF g_tok_defn;
static TokSort g_toksort;
int search_for_toks = 1;
static Tokdec * g_tokformals;
static int g_lastfield;
static TDF g_shape;
static TDF g_lastshape;
 
static Name * g_shtokname;
static int g_has_vis = 0;
static Bool issigned;
static Labdec * g_labdec;
static unsigned long intvalue;
static TDF optlab;
static TDF g_lower;
static TDF g_upper;
static Bool g_has_upper;
static TDF intro_acc;
static TDF intro_init;

static int query_t;
static int g_cr_v;
static int g_ce_v;
static int g_unt;
static Tagdec * g_app_tags;

static void do_procprops
    PROTO_N ( (i) )
    PROTO_T ( int i )
{
    switch(i) {
       case 0: return;
       case 1: OPTION(o_var_callers); return;
       case 2: OPTION(o_var_callees); return;
       case 3: OPTION(o_add_procprops(o_var_callers, o_var_callees)); return;
       case 4: OPTION(o_untidy); return;
       case 5: OPTION(o_add_procprops(o_var_callers, o_untidy)); return;
       case 6: OPTION(o_add_procprops(o_var_callees, o_untidy)); return;
       case 7: OPTION(o_add_procprops(o_var_callers, 
		      o_add_procprops(o_var_callees, o_untidy))); return;
       case 8: OPTION(o_check_stack); return;
       case 9: OPTION(o_add_procprops(o_var_callers,o_check_stack)); return;
       case 10: OPTION(o_add_procprops(o_var_callees,o_check_stack)); return;
       case 11: OPTION(o_add_procprops(o_check_stack,
		       o_add_procprops(o_var_callers, o_var_callees))); return;
       case 12: OPTION(o_add_procprops(o_untidy,o_check_stack)); return;
       case 13: OPTION(o_add_procprops(o_check_stack,
		       o_add_procprops(o_var_callers, o_untidy))); return;
       case 14: OPTION(o_add_procprops(o_check_stack,
		       o_add_procprops(o_var_callees, o_untidy))); return;
       case 15: OPTION(o_add_procprops(o_check_stack,
		       o_add_procprops(o_var_callers, 
		       o_add_procprops(o_var_callees, o_untidy)))); return;
    }
}

static int defaultlab = -1;
static TDF g_lablist;
int do_pp = 0;

static void success
    PROTO_Z ()
{
    IGNORE printf("Reached end\n");
    print_res();
}

static int HAS_MAGIC = 1;
unsigned long MAJOR_NO = major_version;
unsigned long MINOR_NO = minor_version;



/* BEGINNING OF FUNCTION DECLARATIONS */

extern void read_label PROTO_S ((void));
static void ZR641 PROTO_S ((PTR_Tokdec *));
static void ZRfull__sortname PROTO_S ((void));
static void ZR643 PROTO_S ((int *));
static void ZR645 PROTO_S ((void));
extern void read_variety PROTO_S ((void));
static void ZR646 PROTO_S ((void));
static void ZRtok__formal__list__opt PROTO_S ((void));
static void ZR647 PROTO_S ((void));
static void ZR648 PROTO_S ((void));
static void ZR650 PROTO_S ((void));
static void ZRsortname__list PROTO_S ((void));
static void ZRsignature__opt PROTO_S ((void));
static void ZRexp__sequence PROTO_S ((void));
static void ZRrange PROTO_S ((void));
static void ZR654 PROTO_S ((void));
static void ZR655 PROTO_S ((TDF *, PTR_TDF *));
static void ZRrange__label__list PROTO_S ((void));
static void ZR656 PROTO_S ((void));
extern void read_shape PROTO_S ((void));
static void ZR657 PROTO_S ((void));
static void ZRaccess__list PROTO_S ((void));
static void ZR660 PROTO_S ((TDF *, TDF *, TDF *, TDF *));
static void ZRtagshacc__list__opt PROTO_S ((void));
static void ZR661 PROTO_S ((TDF *, PTR_TDF *));
static void ZRlabdest__opt PROTO_S ((void));
static void ZR662 PROTO_S ((PTR_TDF *));
static void ZRalignment__list__opt PROTO_S ((void));
static void ZR663 PROTO_S ((void));
extern void read_string PROTO_S ((void));
static void ZR664 PROTO_S ((void));
static void ZRotagexp__list PROTO_S ((void));
static void ZRvariety__sign PROTO_S ((void));
static void ZR668 PROTO_S ((void));
static void ZR669 PROTO_S ((TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, int *));
static void ZR670 PROTO_S ((TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, int *));
extern void read_signed_nat PROTO_S ((void));
static void ZR672 PROTO_S ((TDF *, TDF *, PTR_TDF *, PTR_char *));
extern void read_token PROTO_S ((void));
static void ZR673 PROTO_S ((void));
static void ZRnat__not__int PROTO_S ((void));
static void ZRshape__body PROTO_S ((void));
static void ZRrepeat__starter__opt PROTO_S ((void));
static void ZR674 PROTO_S ((void));
static void ZRfield__list PROTO_S ((void));
static void ZR675 PROTO_S ((void));
static void ZR676 PROTO_S ((void));
static void ZR677 PROTO_S ((TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, PTR_char *, int *));
static void ZRrounding__mode__opt PROTO_S ((void));
static void ZR678 PROTO_S ((TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, PTR_char *, int *));
static void ZRnonst__shape PROTO_S ((void));
static void ZR679 PROTO_S ((TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, PTR_char *, int *));
static void ZRaccess__opt PROTO_S ((void));
extern void read_error_code PROTO_S ((void));
static void ZRpostlude__opt PROTO_S ((void));
static void ZR680 PROTO_S ((TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, int *));
static void ZRexponent__opt PROTO_S ((void));
static void ZR681 PROTO_S ((TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, int *));
static void ZRclosed__exp PROTO_S ((void));
extern void read_bool PROTO_S ((void));
static void ZRvarintro__opt PROTO_S ((void));
extern void read_ntest PROTO_S ((void));
extern void read_bitfield_variety PROTO_S ((void));
static void ZRsigned__nat__body PROTO_S ((void));
static void ZRlabset__opt PROTO_S ((void));
static void ZRkeep__item PROTO_S ((void));
static void ZRstruct__def PROTO_S ((void));
static void ZRnonst__shape__body PROTO_S ((void));
extern void read_tag PROTO_S ((void));
static void ZRvariety__opt PROTO_S ((void));
extern void read_nat_option PROTO_S ((void));
static void ZRsortname__list__opt PROTO_S ((void));
extern void read_floating_variety PROTO_S ((void));
static void ZRtagshacc PROTO_S ((void));
static void ZRelement__list__opt PROTO_S ((void));
extern void read_nat PROTO_S ((void));
extern void read_alignment PROTO_S ((void));
static void ZRvarpar__opt PROTO_S ((void));
static void ZRkeep__list PROTO_S ((void));
static void ZRproc__def PROTO_S ((void));
extern void read_error_code_list PROTO_S ((void));
static void ZRcallee__var__opt PROTO_S ((void));
static void ZRtag__dec PROTO_S ((void));
static void ZRtag__intro PROTO_S ((void));
extern void read_exp PROTO_S ((void));
static void ZRtag__def PROTO_S ((void));
static void ZRotagexp__list__opt PROTO_S ((void));
static void ZRtok__formal__list PROTO_S ((void));
static void ZRuntidy__opt PROTO_S ((void));
static void ZRcaller__var__opt PROTO_S ((void));
static void ZRproc__def__body PROTO_S ((void));
static void ZRlabelled__list PROTO_S ((void));
static void ZRoffset__exp__list PROTO_S ((void));
static void ZRbitfield__sign PROTO_S ((void));
static void ZRtok__dec PROTO_S ((void));
static void ZRexp__comma__list PROTO_S ((void));
static void ZRexp__body PROTO_S ((void));
static void ZRtok__def PROTO_S ((void));
static void ZRunary__exp PROTO_S ((void));
static void ZRtagshacc__list PROTO_S ((void));
static void ZRshapetok PROTO_S ((void));
static void ZRalignment__list PROTO_S ((void));
extern void read_error_treatment PROTO_S ((void));
static void ZRcallee PROTO_S ((void));
extern void read_al_tag PROTO_S ((void));
extern void read_exp_list PROTO_S ((void));
static void ZRelement PROTO_S ((void));
static void ZR622 PROTO_S ((void));
static void ZRtok__def__body PROTO_S ((void));
static void ZRinteger PROTO_S ((void));
extern void read_transfer_mode PROTO_S ((void));
extern void read_rounding_mode PROTO_S ((void));
static void ZR625 PROTO_S ((void));
static void ZR626 PROTO_S ((void));
extern void read_access PROTO_S ((void));
static void ZR627 PROTO_S ((void));
static void ZR628 PROTO_S ((void));
static void ZR629 PROTO_S ((void));
static void ZR630 PROTO_S ((void));
static void ZR632 PROTO_S ((void));
static void ZRkeep__list__opt PROTO_S ((void));
static void ZR633 PROTO_S ((void));
static void ZRal__tag__def PROTO_S ((void));
static void ZRotagexp PROTO_S ((void));
extern void read_program PROTO_S ((void));
static void ZR634 PROTO_S ((void));

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

void
read_label PROTO_Z ()
{
  ZL2_label:;
    switch (CURRENT_TERMINAL) {
      case 59:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 24:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    goto ZL2_label;
	}
	/*UNREACHED*/
      case 60:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 54:
	{
	    {

    char * n =lex_v.val.name;
    Labdec * x = find_lab(n);
    if (x==(Labdec*)0) {
	x = MALLOC(Labdec);
	x->idname.id = n; x->idname.name.unit_name = next_label();
	x->declared = 0;
	x->next = labdecs; labdecs = x;
    }
    g_labdec = x;
    o_make_label(out_tdfint32(LOCNAME(x->idname)));
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZR641 PROTO_N ((ZI640))
  PROTO_T (PTR_Tokdec *ZI640)
{
    switch (CURRENT_TERMINAL) {
      case 43:
	{
	    ADVANCE_LEXER;
	    {

    expand_tok((*ZI640), &(*ZI640)->sort);
	    }
	}
	break;
      case 100:
	{
	    TDF ZIa;
	    TDF ZIb;

	    ADVANCE_LEXER;
	    {

    expand_tok((*ZI640), &(*ZI640)->sort);
	    }
	    {

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_variety ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRfull__sortname PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	{

    g_sname.sort = lex_v.t;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 1:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 4:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 8:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 14:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 17:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 39:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 42:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 48:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 59:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 70:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 74:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 90:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 95:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 99:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 105:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 110:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 116:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 119:
		{
		    ADVANCE_LEXER;
		}
		break;
	      case 127:
		{
		    ADVANCE_LEXER;
		}
		break;
	      default:
		goto ZL1;
	    }
	}
	ZR674 ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR643 PROTO_N ((ZI642))
  PROTO_T (int *ZI642)
{
    switch (CURRENT_TERMINAL) {
      case 41:
	{
	    ADVANCE_LEXER;
	    {

    (constructs[(*ZI642)].f)();
	    }
	}
	break;
      case 98:
	{
	    TDF ZIa;
	    TDF ZIb;

	    ADVANCE_LEXER;
	    {

    (constructs[(*ZI642)].f)();
	    }
	    {

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_variety ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR645 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 78:
	{
	    TDF ZIa;
	    PTR_TDF ZIb;

	    ADVANCE_LEXER;
	    {

    SET_TDF((ZIb), &(ZIa));
	    }
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIb));
    o_negate(o_wrap, append_TDF(&(ZIa),1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 22: case 55: case 69: case 70: case 71:
	{
	    TDF ZIa;
	    TDF ZIb;

	    ZR634 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_variety ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 44:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    TDF ZId;
	    PTR_TDF ZIe;
	    int ZIf;
	    unsigned_long ZIg;

	    {

    /* (ZIc), (ZId) uninitialised */
    (ZIf) = 1;
    (ZIg) = UL(radix);
    SET_TDF((ZIe), &(ZIa));
    out_tdfstring_bytes(fformat(lex_v.val.name,lnum), 8, UI(lnum));
    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIb));
	    }
	    ADVANCE_LEXER;
	    ZRexponent__opt ();
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIc));
	    }
	    read_floating_variety ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZId));
	    }
	    ZRrounding__mode__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIe));
    o_make_floating(append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1),
		    if ((ZIf)) { o_true; } else { o_false; },
		    o_make_string(append_TDF(&(ZIa), 1)),
		    o_make_nat(out_tdfint32((ZIg))),
		    append_TDF(&(ZIb), 1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_variety PROTO_Z ()
{
  ZL2_variety:;
    switch (CURRENT_TERMINAL) {
      case 127:
	{
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 24:
		    {
			ADVANCE_LEXER;
			goto ZL2_variety;
		    }
		    /*UNREACHED*/
		  case 86:
		    {
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			ADVANCE_LEXER;
			{

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
			}
			switch (CURRENT_TERMINAL) {
			  case 78:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
			}
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_variety ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
			}
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_variety ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    o_var_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
	       append_TDF(&(ZIc),1));
			}
			switch (CURRENT_TERMINAL) {
			  case 29:
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
	    }
	}
	break;
      case 21: case 56: case 64: case 97: case 101:
      case 121:
	{
	    ZRvariety__sign ();
	    ZR650 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 126:
	{
	    int ZIa;

	    {

    (ZIa) = lex_v.val.v;
	    }
	    ADVANCE_LEXER;
	    {

    (constructs[(ZIa)].f)();
	    }
	}
	break;
      case 128:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 10: case 22: case 55: case 62: case 68:
      case 98: case 99: case 100:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;

	    {

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
	    }
	    ZRsigned__nat__body ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 24:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRsigned__nat__body ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    o_var_limits(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZR646 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 79:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    TDF ZId;

	    {

    /* (ZIb), (ZIc), (ZId) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
	    }
	    ADVANCE_LEXER;
	    read_shape ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
	    }
	    switch (CURRENT_TERMINAL) {
	      case 30:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR660 (&ZIa, &ZIb, &ZIc, &ZId);
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 112:
	{
	    TDF ZIa;

	    {

    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 79:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRcallee ();
	    ZRcallee__var__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    TDF cees;
    cees = *current_TDF;
    INIT_TDF(current_TDF);
    o_tail_call(do_procprops(g_ce_v*2),
		append_TDF(&(ZIa),1), append_TDF(&cees,1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 30:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRtok__formal__list__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 54:
	{
	    ZRtok__formal__list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    g_tokpars = (Tokpar*)0;
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR647 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 54:
	{
	    {

    char * n = lex_v.val.name;
    Tagdec * x = find_tag(n);
    if (x == (Tagdec*)0) { fail("%s is not a tag", n); }
    else
    if (!x->isvar || x->hassh == 0) {
	fail("Don't know shape of %s", n);
    }
    o_contents(
	if (x->hassh == 1) {
	    o_shape_apply_token(make_tok(&x->sh.shtok), {});
	} else { append_TDF(&x->sh.tdfsh, 0); },
	o_obtain_tag(make_tag(&x->idname.name)));
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 78:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;

	    {

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
	    }
	    ADVANCE_LEXER;
	    read_shape ();
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
	    }
	    ZRunary__exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    o_contents(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR648 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 76:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    PTR_TDF ZId;
	    int ZIe;
	    PTR_Labdec ZIf;

	    {

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = defaultlab;
    (ZIf) = labdecs;
    defaultlab = -1;
    SET_TDF((ZId), &(ZIa));
	    }
	    ADVANCE_LEXER;
	    ZRexp__sequence ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 11:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRlabset__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIc) = optlab;
    defaultlab = (ZIe);
    tidy_labels((ZIf));
	    }
	    ZRexp__sequence ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    INIT_TDF((ZId));
    RESET_TDF((ZId));
    o_conditional(append_TDF(&(ZIc),1),
		  append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 20:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 78:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    PTR_TDF ZId;
	    int ZIe;

	    {

    query_t = lex_query;
	    }
	    ADVANCE_LEXER;
	    {

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = query_t;
    SET_TDF((ZId),&(ZIa));
	    }
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId),&(ZIb));
	    }
	    read_ntest ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc))
	    }
	    read_exp ();
	    ZRlabdest__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    switch((ZIe)) {
	case lex_query:
	    o_integer_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_float__query:
	    o_floating_test({}, o_impossible, append_TDF(&(ZIb),1),
	   		append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_ptr__query:
	    o_pointer_test( {}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_proc__query:
	    o_proc_test( {}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	case lex_offset__query:
	    o_offset_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	default: fail("Don't understand test");
    }
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR650 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 21:
	{
	    ADVANCE_LEXER;
	    {

    o_var_limits(
	o_make_signed_nat(out_tdfbool(issigned),
	    out_tdfint32(UL((issigned)?MINSC:0))),
	o_make_signed_nat(out_tdfbool(0),
	    out_tdfint32(UL((issigned)?MAXSC:MAXUSC))));
	    }
	}
	break;
      case 56:
	{
	    ADVANCE_LEXER;
	    {

    o_var_limits(
	o_make_signed_nat(out_tdfbool(issigned),
	    out_tdfint32(UL((issigned)?MINSI:0))),
	o_make_signed_nat(out_tdfbool(0),
	    out_tdfint32(UL((issigned)?MAXSI:MAXUSI))));
	    }
	}
	break;
      case 64:
	{
	    ADVANCE_LEXER;
	    {

    o_var_limits(
	o_make_signed_nat(out_tdfbool(issigned),
	    out_tdfint32(UL((issigned)?MINSL:0))),
	o_make_signed_nat(out_tdfbool(0),
	    out_tdfint32(UL((issigned)?MAXSL:MAXUSL))));
	    }
	}
	break;
      case 97:
	{
	    ADVANCE_LEXER;
	    {

    o_var_limits(
	o_make_signed_nat(out_tdfbool(issigned),
	    out_tdfint32(UL((issigned)?MINSS:0))),
	o_make_signed_nat(out_tdfbool(0),
	    out_tdfint32(UL((issigned)?MAXSS:MAXUSS))));
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRsortname__list PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	ZRfull__sortname ();
	ZR673 ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRsignature__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 85: case 104: case 105: case 107:
	{
	    read_string ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    current_TDF->no=1;
	    }
	}
	break;
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRexp__sequence PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 10: case 19: case 22: case 28: case 41:
      case 42: case 43: case 44: case 45: case 52:
      case 54: case 55: case 58: case 61: case 62:
      case 68: case 76: case 77: case 78: case 79:
      case 81: case 82: case 84: case 85: case 86:
      case 88: case 98: case 99: case 100: case 102:
      case 103: case 104: case 105: case 107: case 109:
      case 110: case 111: case 124:
	{
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    current_TDF->no =1;
	    }
	    ZR628 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    current_TDF->no =1;
    o_make_top;
	    }
	    ZR628 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRrange PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	PTR_TDF ZIa;

	{

    SET_TDF((ZIa), &g_lower);
	}
	ZRsigned__nat__body ();
	ZR662 (&ZIa);
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR654 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 21:
	{
	    ADVANCE_LEXER;
	    {

    Name * shtok = tokforcharsh(issigned);
    o_shape_apply_token(make_tok(shtok), {});
	    }
	}
	break;
      case 56:
	{
	    ADVANCE_LEXER;
	    {

    Name * shtok = tokforintsh(issigned);
    o_shape_apply_token(make_tok(shtok), {});
	    }
	}
	break;
      case 64:
	{
	    ADVANCE_LEXER;
	    {

    Name * shtok = tokforlongsh(issigned);
    o_shape_apply_token(make_tok(shtok), {});
	    }
	}
	break;
      case 97:
	{
	    ADVANCE_LEXER;
	    {

    Name * shtok = tokforshortsh(issigned);
    o_shape_apply_token(make_tok(shtok), {});
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR655 PROTO_N ((ZIa, ZIb))
  PROTO_T (TDF *ZIa X PTR_TDF *ZIb)
{
    switch (CURRENT_TERMINAL) {
      case 24:
	{
	    ADVANCE_LEXER;
	    {

    char* n = lex_v.val.name;
    Tagdec * x = find_tag(n);
    if (x != (Tagdec*)0) { fail("Tag %s declared twice", n); }
    x = MALLOC(Tagdec); x->isdeffed = 1; x->hassh=0; x->iskept=0;
    NEW_IDNAME(x->idname, n, tag_ent);
    x->isvar = 1;
    x->next = g_app_tags; g_app_tags = x;
    RESET_TDF((*ZIb));
    o_make_otagexp( OPTION(make_tag(&x->idname.name)),append_TDF(&(*ZIa),1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 54:
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

    RESET_TDF((*ZIb));
    o_make_otagexp( {}, append_TDF(&(*ZIa),1));
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRrange__label__list PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	TDF ZIa;
	PTR_TDF ZIb;

	{

    SET_TDF((ZIb),&(ZIa));
	}
	ZRrange ();
	switch (CURRENT_TERMINAL) {
	  case 51:
	    break;
	  case 130:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	read_label ();
	ZR661 (&ZIa, &ZIb);
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR656 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 10: case 19: case 22: case 28: case 41:
      case 42: case 43: case 44: case 45: case 52:
      case 54: case 55: case 58: case 61: case 62:
      case 68: case 76: case 77: case 78: case 79:
      case 81: case 82: case 84: case 85: case 86:
      case 88: case 98: case 99: case 100: case 102:
      case 103: case 104: case 105: case 107: case 109:
      case 110: case 111: case 124:
	{
	    ZRexp__comma__list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_shape PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	TDF ZIa;
	PTR_TDF ZIb;
	int ZIc;

	{

    (ZIc) = (current_TDF->first == current_TDF->last &&
	      current_TDF->first->usage == 0 &&
	      current_TDF->first->offst == 0);
    if (!(ZIc)) { SET_TDF((ZIb), &(ZIa)); }
	}
	ZRshape__body ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if (!(ZIc) ) {
	SET((ZIb));
	RESET_TDF((ZIb));
	append_TDF(&(ZIa),1);
    }
	}
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZR657 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 23:
	{
	    ADVANCE_LEXER;
	    {

    g_unt = 3;
	    }
	}
	break;
      default:
	{
	    {

    g_unt = 1;
	    }
	}
	break;
      case 130:
	return;
    }
}

static void
ZRaccess__list PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	read_access ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    current_TDF->no=1;
	}
	ZR627 ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR660 PROTO_N ((ZIa, ZIb, ZIc, ZId))
  PROTO_T (TDF *ZIa X TDF *ZIb X TDF *ZIc X TDF *ZId)
{
    switch (CURRENT_TERMINAL) {
      case 78:
	{
	    ADVANCE_LEXER;
	    read_exp_list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (*ZIc) = *current_TDF;
    INIT_TDF(current_TDF);
	    }
	    ZRvarpar__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (*ZId) = *current_TDF;
    INIT_TDF(current_TDF);
    o_apply_proc(append_TDF(&(*ZIb),1), append_TDF(&(*ZIa),1),
	    { append_TDF(&(*ZIc), 1); current_TDF->no = (*ZIc).no; },
	      if ((*ZId).no !=0) { OPTION(append_TDF(&(*ZId),1)); }
	    );
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 79:
	{
	    TDF ZIe;
	    TDF ZIf;
	    TDF ZIg;
	    int ZIh;
	    int ZIi;
	    PTR_Tagdec ZIj;
	    PTR_Tagdec ZIk;
	    PTR_Tagdec ZIl;

	    ADVANCE_LEXER;
	    {

    /* (ZIe), (ZIf), (ZIg) uninitialised */
    /* (ZIh), (ZIi), (ZIk) uninitialised */
    (ZIj) = g_app_tags;
    (ZIl) = tagdecs;
    g_app_tags = (Tagdec*)0;
	    }
	    ZRotagexp__list__opt ();
	    ZRcaller__var__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIe) = *current_TDF;
    INIT_TDF(current_TDF);
    (ZIh) = g_cr_v;
    (ZIk) = g_app_tags;
    g_app_tags = (ZIj);
	    }
	    switch (CURRENT_TERMINAL) {
	      case 93:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRcallee ();
	    ZRcallee__var__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIf) = *current_TDF;
    (ZIi) = g_ce_v;
    INIT_TDF(current_TDF);
    while ((ZIk) != (Tagdec*)0) {
	Tagdec * x = (ZIk);
	(ZIk) = x->next;
	x->next = tagdecs;
	tagdecs = x;
    }
	    }
	    ZRpostlude__opt ();
	    switch (CURRENT_TERMINAL) {
	      case 30:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRuntidy__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIg) = *current_TDF;
    INIT_TDF(current_TDF);
    tagdecs = (ZIl);
    o_apply_general_proc(
	append_TDF(&(*ZIb),1), do_procprops((ZIh)+2*(ZIi)+4*g_unt),
	append_TDF(&(*ZIa),1),
	{ append_TDF(&(ZIe),1); current_TDF->no = (ZIe).no; },
	append_TDF(&(ZIf),1),
	append_TDF(&(ZIg), 1))
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRtagshacc__list__opt PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	{

    current_TDF->no =0;
	}
	ZR664 ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR661 PROTO_N ((ZIa, ZIb))
  PROTO_T (TDF *ZIa X PTR_TDF *ZIb)
{
    switch (CURRENT_TERMINAL) {
      default:
	{
	    {

    RESET_TDF((*ZIb));
    o_make_caselim(append_TDF(&(*ZIa),1),
		   append_TDF(&g_lower, g_has_upper),
		   append_TDF(&g_upper,1));
    current_TDF->no = 1;
	    }
	}
	break;
      case 25:
	{
	    {

    RESET_TDF((*ZIb));
    o_make_caselim(append_TDF(&(*ZIa),1),
		   append_TDF(&g_lower, g_has_upper),
		   append_TDF(&g_upper,1));
	    }
	    ADVANCE_LEXER;
	    ZRrange__label__list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    current_TDF->no++;
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRlabdest__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 11:
	{
	    PTR_TDF ZIa;

	    ADVANCE_LEXER;
	    {

    SET_TDF((ZIa), &optlab);
	    }
	    read_label ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIa));
	    }
	}
	break;
      default:
	{
	    {

    TDF * hold;
    SET_TDF(hold, &optlab);
    if (defaultlab==-1) defaultlab = next_label();
    o_make_label(out_tdfint32(UL(defaultlab)));
    RESET_TDF(hold);
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR662 PROTO_N ((ZIa))
  PROTO_T (PTR_TDF *ZIa)
{
    switch (CURRENT_TERMINAL) {
      case 24:
	{
	    ADVANCE_LEXER;
	    {

    RESET_TDF((*ZIa));
    SET_TDF((*ZIa), &g_upper);
	    }
	    ZRsigned__nat__body ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((*ZIa));
    g_has_upper=1;
	    }
	}
	break;
      default:
	{
	    {

    RESET_TDF((*ZIa));
    g_upper = g_lower;
    g_has_upper=0;
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRalignment__list__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      default:
	{
	    {

    o_alignment(o_top);
	    }
	}
	break;
      case 4: case 5: case 7: case 8: case 9:
      case 54: case 78:
	{
	    TDF ZIa;
	    PTR_TDF ZIb;
	    int ZIc;

	    {

    (ZIc) = (current_TDF->first == current_TDF->last &&
	      current_TDF->first->usage == 0 &&
	      current_TDF->first->offst == 0);
    if (!(ZIc)) { SET_TDF((ZIb), &(ZIa)); }
	    }
	    ZRalignment__list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if (!(ZIc) ) {
	SET((ZIb));
	RESET_TDF((ZIb));
	append_TDF(&(ZIa),1);
    }
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR663 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 25:
	{
	    ADVANCE_LEXER;
	    ZRoffset__exp__list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    current_TDF->no+=2;
	    }
	}
	break;
      default:
	{
	    {

    current_TDF->no = 2;
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_string PROTO_Z ()
{
  ZL2_string:;
    switch (CURRENT_TERMINAL) {
      case 105:
	{
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 24:
		    {
			ADVANCE_LEXER;
			goto ZL2_string;
		    }
		    /*UNREACHED*/
		  case 86:
		    {
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			ADVANCE_LEXER;
			{

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
			}
			switch (CURRENT_TERMINAL) {
			  case 78:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
			}
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_string ();
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  case 130:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
			}
			read_string ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    o_string_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		  append_TDF(&(ZIc),1));
			}
			switch (CURRENT_TERMINAL) {
			  case 29:
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
	    }
	}
	break;
      case 104:
	{
	    int ZIa;

	    {

    (ZIa) = lex_v.val.v;
	    }
	    ADVANCE_LEXER;
	    {

    (constructs[(ZIa)].f)();
	    }
	}
	break;
      case 107:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 85:
	{
	    {

    char * s = lex_v.val.name;
    o_make_string(out_tdfstring_bytes(s, 8, UI(strlen(s))));
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZR664 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 54:
	{
	    ZRtagshacc__list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRotagexp__list PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	ZRotagexp ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    current_TDF->no = 1;
	}
	ZR626 ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRvariety__sign PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 101:
	{
	    ADVANCE_LEXER;
	    {

    issigned = 1;
	    }
	}
	break;
      case 121:
	{
	    ADVANCE_LEXER;
	    {

    issigned = 0;
	    }
	}
	break;
      default:
	{
	    {

    issigned = 1;
	    }
	}
	break;
      case 130:
	return;
    }
}

static void
ZR668 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 11:
	{
	    ADVANCE_LEXER;
	    ZRlabelled__list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    g_lablist.no++;
	    }
	}
	break;
      default:
	{
	    {

    g_lablist.no = 1;
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR669 PROTO_N ((ZIa, ZIb, ZIc, ZId, ZIe))
  PROTO_T (TDF *ZIa X TDF *ZIb X PTR_TDF *ZIc X PTR_Tagdec *ZId X int *ZIe)
{
    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    {

    RESET_TDF((*ZIc));
    SET_TDF((*ZIc), &(*ZIb));
    (*ZIe) = g_has_vis;
	    }
	    ADVANCE_LEXER;
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((*ZIc));
    intro_acc = (*ZIa);
    intro_init = (*ZIb);
    (*ZId)->isvar=1;
    if ((*ZIe)) {
	Tagdec * y = MALLOC(Tagdec);
	*y = *(*ZId);
	y->next = tagdecs;
	tagdecs = y;
    }
    (*ZId)->next = localdecs;
    localdecs = (*ZId);
	    }
	}
	break;
      case 24:
	{
	    {

    RESET_TDF((*ZIc));
    SET_TDF((*ZIc), &(*ZId)->sh.tdfsh);
    (*ZId)->hassh=2;
	    }
	    ADVANCE_LEXER;
	    read_shape ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((*ZIc));
    SET_TDF((*ZIc), &(*ZIb));
    (*ZIe) = g_has_vis;
	    }
	    ZR670 (ZIa, ZIb, ZIc, ZId, ZIe);
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR670 PROTO_N ((ZIa, ZIb, ZIc, ZId, ZIe))
  PROTO_T (TDF *ZIa X TDF *ZIb X PTR_TDF *ZIc X PTR_Tagdec *ZId X int *ZIe)
{
    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    ADVANCE_LEXER;
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((*ZIc));
    intro_acc = (*ZIa);
    intro_init = (*ZIb);
    (*ZId)->isvar=1;
    if ((*ZIe)) {
	Tagdec * y = MALLOC(Tagdec);
	*y = *(*ZId);
	y->next = tagdecs;
	tagdecs = y;
    }
    (*ZId)->next = localdecs;
    localdecs = (*ZId);
	    }
	}
	break;
      default:
	{
	    {

    o_make_value(append_TDF(&(*ZId)->sh.tdfsh, 0));
	    }
	    {

    RESET_TDF((*ZIc));
    intro_acc = (*ZIa);
    intro_init = (*ZIb);
    (*ZId)->isvar=1;
    if ((*ZIe)) {
	Tagdec * y = MALLOC(Tagdec);
	*y = *(*ZId);
	y->next = tagdecs;
	tagdecs = y;
    }
    (*ZId)->next = localdecs;
    localdecs = (*ZId);
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_signed_nat PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	ZRsigned__nat__body ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZR672 PROTO_N ((ZIa, ZIb, ZIc, ZId))
  PROTO_T (TDF *ZIa X TDF *ZIb X PTR_TDF *ZIc X PTR_char *ZId)
{
    switch (CURRENT_TERMINAL) {
      case 3:
	{
	    ADVANCE_LEXER;
	    ZRunary__exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    INIT_TDF((*ZIc));
    RESET_TDF((*ZIc));
    if(strcmp((*ZId), "*+.")==0) {
	o_add_to_ptr(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if(strcmp((*ZId), "*-*")==0) {
	o_subtract_ptrs(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if(strcmp((*ZId), ".*")==0) {
	o_offset_mult(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if(strcmp((*ZId), ".+.")==0) {
	o_offset_add(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if(strcmp((*ZId), ".-.")==0) {
	o_offset_subtract(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if(strcmp((*ZId), "./")==0) {
	o_offset_div_by_int(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if(strcmp((*ZId), "./.")==0) {
	o_offset_div(
	    o_var_limits(
		o_make_signed_nat(out_tdfbool(1), out_tdfint32(UL(MINSI))),
		o_make_signed_nat(out_tdfbool(0), out_tdfint32(UL(MAXSI)))),
	    append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if(strcmp((*ZId), ".max.")==0) {
	o_offset_max(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else { fail("%s not an addrop", (*ZId)); }
	    }
	}
	break;
      case 36:
	{
	    ADVANCE_LEXER;
	    ZRunary__exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    INIT_TDF((*ZIc));
    RESET_TDF((*ZIc));
    o_assign(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
	    }
	}
	break;
      case 63:
	{
	    ADVANCE_LEXER;
	    ZRunary__exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    INIT_TDF((*ZIc));
    RESET_TDF((*ZIc));
    if(strcmp((*ZId), "And")==0) {
	o_and(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if(strcmp((*ZId), "Or")==0) {
	o_or(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if(strcmp((*ZId), "Xor")==0) {
	o_xor(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else { fail("%s not a logop", (*ZId)); }
	    }
	}
	break;
      case 10: case 68: case 103:
	{
	    {
		switch (CURRENT_TERMINAL) {
		  case 10:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 68:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 103:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  default:
		    goto ZL1;
		}
	    }
	    ZRunary__exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    INIT_TDF((*ZIc));
    RESET_TDF((*ZIc));
    if (strcmp((*ZId),"%")==0) {
	o_rem2(o_continue, o_continue, append_TDF(&(*ZIa),1),
	       append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"%1")==0) {
	o_rem1(o_continue, o_continue, append_TDF(&(*ZIa),1),
	       append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"*")==0) {
	o_mult(o_wrap, append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"+")==0) {
	o_plus(o_wrap, append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"-")==0) {
	o_minus(o_wrap, append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"/")==0) {
	o_div2(o_continue, o_continue, append_TDF(&(*ZIa),1),
	       append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"/1")==0) {
	o_div1(o_continue, o_continue, append_TDF(&(*ZIa),1),
	       append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"<<")==0) {
	o_shift_left(o_wrap, append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"F*")==0) {
	o_floating_mult(o_continue,
	    { LIST_ELEM(append_TDF(&(*ZIa),1));
	    LIST_ELEM(append_TDF(&(*ZIb),1)) });
    } else if (strcmp((*ZId),">>")==0) {
	o_shift_right(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"F+")==0) {
	o_floating_plus(o_continue,
	    { LIST_ELEM(append_TDF(&(*ZIa),1));
	    LIST_ELEM(append_TDF(&(*ZIb),1)) });
    } else if (strcmp((*ZId),"F-")==0) {
	o_floating_minus(o_continue, append_TDF(&(*ZIa),1),
			 append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"F/")==0) {
	o_floating_div(o_continue, append_TDF(&(*ZIa),1),
		       append_TDF(&(*ZIb),1));
    } else { fail("%s not an arithop", (*ZId)); }
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_token PROTO_Z ()
{
  ZL2_token:;
    switch (CURRENT_TERMINAL) {
      case 116:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 24:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    goto ZL2_token;
	}
	/*UNREACHED*/
      case 123:
	{
	    TDF ZIa;

	    ADVANCE_LEXER;
	    {

    (ZIa) = g_tok_defn;
	    }
	    ZRtok__def__body ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    o_use_tokdef(append_TDF(&g_tok_defn,1));
    g_tok_defn = (ZIa);
	    }
	}
	break;
      case 2: case 5: case 9: case 15: case 18:
      case 40: case 43: case 49: case 60: case 71:
      case 75: case 91: case 96: case 100: case 111:
      case 120: case 128:
	{
	    {

    Tokdec * td = lex_v.val.tokname;
    if (td->isparam) {
	o_token_apply_token(make_tok(&td->idname.name), {});
    } else {
	make_tok(&td->idname.name);
    }
    /* token should only be expanded as parameter of a token */
	    }
	    {
		switch (CURRENT_TERMINAL) {
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
		  case 9:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 15:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 18:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 40:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 43:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 49:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 60:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 71:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 75:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 91:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 96:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 100:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 111:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 120:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 128:
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
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZR673 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      default:
	{
	    {

    g_tokpars = MALLOC(Tokpar);
    g_tokpars->par = g_sname;
    g_tokpars->next = (Tokpar*)0;
	    }
	}
	break;
      case 25:
	{
	    Sort ZIa;

	    {

    (ZIa) = g_sname;
	    }
	    ADVANCE_LEXER;
	    ZRsortname__list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    Tokpar * x = MALLOC(Tokpar);
    x->par = (ZIa);
    x->next = g_tokpars;
    g_tokpars = x;
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRnat__not__int PROTO_Z ()
{
  ZL2_nat__not__int:;
    switch (CURRENT_TERMINAL) {
      case 70:
	{
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 24:
		    {
			ADVANCE_LEXER;
			read_nat ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
		    }
		    break;
		  case 86:
		    {
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			ADVANCE_LEXER;
			{

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
			}
			switch (CURRENT_TERMINAL) {
			  case 78:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
			}
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_nat ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
			}
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_nat ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    o_nat_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
	       append_TDF(&(ZIc),1));
			}
			switch (CURRENT_TERMINAL) {
			  case 29:
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
	    }
	}
	break;
      case 69:
	{
	    int ZIa;

	    {

    (ZIa) = lex_v.val.v;
	    }
	    ADVANCE_LEXER;
	    {

    (constructs[(ZIa)].f)();
	    }
	}
	break;
      case 71:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRshape__body PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 32:
	{
	    ADVANCE_LEXER;
	    {

    Name * shtok = tokfordoublesh();
    o_shape_apply_token(make_tok(shtok), {});
	    }
	}
	break;
      case 46:
	{
	    ADVANCE_LEXER;
	    {

    Name * shtok = tokforfloatsh();
    o_shape_apply_token(make_tok(shtok), {});
	    }
	}
	break;
      case 83:
	{
	    TDF ZIa;
	    PTR_TDF ZIb;

	    ADVANCE_LEXER;
	    {

    SET_TDF((ZIb), &(ZIa));
	    }
	    read_shape ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIb));
    o_pointer(o_alignment(append_TDF(&(ZIa),1)));
	    }
	}
	break;
      case 95:
	{
	    ADVANCE_LEXER;
	    ZR676 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 21: case 56: case 64: case 97: case 101:
      case 121:
	{
	    ZRvariety__sign ();
	    ZR654 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 94:
	{
	    int ZIa;

	    {

    (ZIa) = lex_v.val.v;
	    }
	    ADVANCE_LEXER;
	    {

    (constructs[(ZIa)].f)();
	    }
	}
	break;
      case 96:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRrepeat__starter__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 78:
	{
	    ADVANCE_LEXER;
	    ZRexp__sequence ();
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      case 130:
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

    o_make_top;
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR674 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      default:
	{
	    {

    if(g_sname.sort == token_sort) {
	fail("Token pars require result and parameter sorts");
    }
    g_sname.toksort= (TokSort*)0;
	    }
	}
	break;
      case 79:
	{
	    Sort ZIa;
	    PTR_Tokpar ZIb;
	    PTR_Tokpar ZIc;

	    {

    /* (ZIb) uninitialised */
    (ZIc) = g_tokpars;
    (ZIa) = g_sname;
    if (g_sname.sort != token_sort) {
	fail("Only token pars require result and parameter sorts");
    }
	    }
	    ADVANCE_LEXER;
	    ZRsortname__list__opt ();
	    switch (CURRENT_TERMINAL) {
	      case 30:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZIb) = g_tokpars;
	    }
	    ZRfull__sortname ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    TokSort * ts = MALLOC(TokSort);
    ts->ressort = g_sname;
    ts->pars = (ZIb);
    g_tokpars = (ZIc);
    (ZIa).toksort = ts;
    g_sname = (ZIa);
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRfield__list PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
  ZL2_field__list:;
    {
	PTR_TDF ZIa;
	PTR_Tokdec ZIb;
	PTR_Tokdec ZIc;

	{

    char * dotn = append_string(".",lex_v.val.name);
    char * n = lex_v.val.name;
    (ZIb) = find_tok(dotn);
    (ZIc) = find_tok(n);
    if ((ZIb)!=(Tokdec*)0 || (ZIc)!=(Tokdec*)0)
	    fail("Field name %s must be unique", dotn);
    (ZIb) = MALLOC(Tokdec); NEW_IDNAME((ZIb)->idname, dotn, tok_ent);
    (ZIb)->isdeffed = 1; (ZIb)->isused=0; (ZIb)->iskept = 0;
    (ZIb)->sort.ressort.sort = exp_sort;
    (ZIb)->sort.pars = (Tokpar *)0;

    (ZIc) = MALLOC(Tokdec); NEW_IDNAME((ZIc)->idname, n, tok_ent);
    (ZIc)->isdeffed = 1; (ZIc)->isused=0; (ZIc)->iskept = 0;
    (ZIc)->sort.ressort.sort = exp_sort;
    (ZIc)->sort.pars = MALLOC(Tokpar);
    (ZIc)->sort.pars->par.sort = exp_sort;
    (ZIc)->sort.pars->next = (Tokpar*)0;
    (ZIb)->next = (ZIc);
    SET_TDF((ZIa), &g_shape);
	}
	switch (CURRENT_TERMINAL) {
	  case 54:
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
	read_shape ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    int tn;
    RESET_TDF((ZIa));
    o_make_tokdef(out_tdfint32(LOCNAME((ZIb)->idname)), {},
	o_token_def(o_exp, {},
	    if (g_lastfield==-1) { /* first field */
		o_offset_zero(o_alignment(append_TDF(&g_shape, 0)));
	    } else {
		o_offset_pad(o_alignment(append_TDF(&g_shape,0)),
		    o_offset_add(o_exp_apply_token(
			o_make_tok(out_tdfint32(UL(g_lastfield))),{}),
		    o_shape_offset(append_TDF(&g_lastshape, 1))))
	    }));
    g_lastfield = (int)(LOCNAME((ZIb)->idname));
    g_lastshape = g_shape;
    INC_LIST;
    o_make_tokdef(out_tdfint32(LOCNAME((ZIc)->idname)), {},
	o_token_def(o_exp,
	    LIST_ELEM(o_make_tokformals(o_exp,
		out_tdfint32(UL(tn=next_unit_name(tok_ent))))),
	    o_component(append_TDF(&g_lastshape,0),
		o_exp_apply_token(o_make_tok(out_tdfint32(UL(tn))),{}),
		o_exp_apply_token(
		    o_make_tok(out_tdfint32(UL(g_lastfield))),{}))));
    INC_LIST;
    (ZIc)->next = tokdecs;
    tokdecs = (ZIb);
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 25:
		{
		    ADVANCE_LEXER;
		    goto ZL2_field__list;
		}
		/*UNREACHED*/
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR675 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 21:
	{
	    ADVANCE_LEXER;
	    {

    * g_shtokname = *(tokforcharsh(issigned));
	    }
	}
	break;
      case 56:
	{
	    ADVANCE_LEXER;
	    {

    * g_shtokname = *(tokforintsh(issigned));
	    }
	}
	break;
      case 64:
	{
	    ADVANCE_LEXER;
	    {

    * g_shtokname = *(tokforlongsh(issigned));
	    }
	}
	break;
      case 97:
	{
	    ADVANCE_LEXER;
	    {

    * g_shtokname = *(tokforshortsh(issigned));
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR676 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 24:
	{
	    ADVANCE_LEXER;
	    read_shape ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 86:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    PTR_TDF ZId;

	    ADVANCE_LEXER;
	    {

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 25:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_shape ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 25:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_shape ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    o_shape_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		 append_TDF(&(ZIc),1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR677 PROTO_N ((ZIa, ZIb, ZIc, ZId, ZIe, ZIf))
  PROTO_T (TDF *ZIa X TDF *ZIb X PTR_TDF *ZIc X PTR_Tagdec *ZId X PTR_char *ZIe X int *ZIf)
{
    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    {

    RESET_TDF((*ZIc));
    if (!(*ZId)->hassh) fail("No declaration shape for %s", (*ZIe));
    SET_TDF((*ZIc), &(*ZIa));
	    }
	    ADVANCE_LEXER;
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((*ZIc));
    o_make_var_tagdef(out_tdfint32(UL(non_local(&(*ZId)->idname.name, tag_ent))),
	{},
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    (*ZId)->isdeffed = 1;
	    }
	}
	break;
      case 24:
	{
	    {

    RESET_TDF((*ZIc));
    if ((*ZId)->hassh) fail("Two declaration shapes for %s", (*ZIe));
    g_shtokname = &(*ZId)->sh.shtok;
	    }
	    ADVANCE_LEXER;
	    ZRshapetok ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    SET_TDF((*ZIc), &(*ZIa));
	    }
	    ZR680 (ZIa, ZIb, ZIc, ZId, ZIf);
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRrounding__mode__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 89: case 90: case 91:
	{
	    read_rounding_mode ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    o_to_nearest;
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR678 PROTO_N ((ZIa, ZIb, ZIc, ZId, ZIe, ZIf))
  PROTO_T (TDF *ZIa X TDF *ZIb X PTR_TDF *ZIc X PTR_Tagdec *ZId X PTR_char *ZIe X int *ZIf)
{
    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    {

    RESET_TDF((*ZIc));
    if (!(*ZId)->hassh) fail("No declaration shape for %s", (*ZIe));
    SET_TDF((*ZIc), &(*ZIa));
	    }
	    ADVANCE_LEXER;
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((*ZIc));
    (*ZId)->iscommon = 1;
    o_common_tagdef(out_tdfint32(UL(non_local(&(*ZId)->idname.name, tag_ent))), {},
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    (*ZId)->isdeffed = 1;
	    }
	}
	break;
      case 24:
	{
	    {

    RESET_TDF((*ZIc));
    if ((*ZId)->hassh) fail("Two declaration shapes for %s", (*ZIe));
    g_shtokname = &(*ZId)->sh.shtok;
	    }
	    ADVANCE_LEXER;
	    ZRshapetok ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    SET_TDF((*ZIc), &(*ZIa));
	    }
	    ZR681 (ZIa, ZIb, ZIc, ZId, ZIf);
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRnonst__shape PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	TDF ZIa;
	PTR_TDF ZIb;
	int ZIc;

	{

    (ZIc) = (current_TDF->first == current_TDF->last &&
	      current_TDF->first->usage == 0 &&
	      current_TDF->first->offst == 0);
    if (!(ZIc)) { SET_TDF((ZIb), &(ZIa)); }
	}
	ZRnonst__shape__body ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if (!(ZIc) ) {
	SET((ZIb));
	RESET_TDF((ZIb));
	append_TDF(&(ZIa),1);
    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR679 PROTO_N ((ZIa, ZIb, ZIc, ZId, ZIe, ZIf))
  PROTO_T (TDF *ZIa X TDF *ZIb X PTR_TDF *ZIc X PTR_Tagdec *ZId X PTR_char *ZIe X int *ZIf)
{
    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    ADVANCE_LEXER;
	    {

    RESET_TDF((*ZIc));
    if (!(*ZId)->hassh) fail("No declaration shape for %s", (*ZIe));
    SET_TDF((*ZIc), &(*ZIa));
	    }
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((*ZIc));
    o_make_id_tagdef(out_tdfint32(UL(non_local(&(*ZId)->idname.name, tag_ent))),
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    (*ZId)->isdeffed = 1;
	    }
	}
	break;
      case 24:
	{
	    {

    RESET_TDF((*ZIc));
    if ((*ZId)->hassh) fail("Two declaration shapes for %s", (*ZIe));
    g_shtokname = &(*ZId)->sh.shtok;
	    }
	    ADVANCE_LEXER;
	    ZRshapetok ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    SET_TDF((*ZIc), &(*ZIa));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 36:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((*ZIc));
    o_make_id_tagdef(out_tdfint32(UL(local_name(&(*ZId)->idname.name, tag_ent))),
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), (*ZIf))); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(*ZIf)) {
	o_make_id_tagdec(out_tdfint32(UL(non_local(&(*ZId)->idname.name,tag_ent))),
	    {},
	    if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	    o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
	INC_LIST;
    }
    (*ZId)->isdeffed=1; (*ZId)->hassh =1;
    if (!(*ZIf)) { (*ZId)->next = tagdecs; tagdecs = (*ZId); }
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRaccess__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 79:
	{
	    ADVANCE_LEXER;
	    ZRaccess__list ();
	    switch (CURRENT_TERMINAL) {
	      case 30:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_error_code PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	int ZIa;

	{

    (ZIa) = lex_v.val.v;
	}
	switch (CURRENT_TERMINAL) {
	  case 37:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    (constructs[(ZIa)].f)();
	}
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZRpostlude__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 93:
	{
	    ADVANCE_LEXER;
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    o_make_top;
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR680 PROTO_N ((ZIa, ZIb, ZIc, ZId, ZIf))
  PROTO_T (TDF *ZIa X TDF *ZIb X PTR_TDF *ZIc X PTR_Tagdec *ZId X int *ZIf)
{
    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    ADVANCE_LEXER;
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((*ZIc));
    o_make_var_tagdef(out_tdfint32(UL(local_name(&(*ZId)->idname.name, tag_ent))),
	{},
	if ((*ZIb).no !=0 ) { OPTION(append_TDF(&(*ZIb), (*ZIf))); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(*ZIf)) {
	o_make_var_tagdec(out_tdfint32(UL(non_local(&(*ZId)->idname.name,tag_ent))),
	    {},
	    if ((*ZIb).no !=0 ) { OPTION(append_TDF(&(*ZIb), 1)); },
	    o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
	INC_LIST;
    }
    (*ZId)->isdeffed=1; (*ZId)->hassh =1;
    if (!(*ZIf)) { (*ZId)->next = tagdecs; tagdecs = (*ZId); }
	    }
	}
	break;
      default:
	{
	    {

    o_make_value(o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
	    }
	    {

    RESET_TDF((*ZIc));
    o_make_var_tagdef(out_tdfint32(UL(local_name(&(*ZId)->idname.name, tag_ent))),
	{},
	if ((*ZIb).no !=0 ) { OPTION(append_TDF(&(*ZIb), (*ZIf))); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(*ZIf)) {
	o_make_var_tagdec(out_tdfint32(UL(non_local(&(*ZId)->idname.name,tag_ent))),
	    {},
	    if ((*ZIb).no !=0 ) { OPTION(append_TDF(&(*ZIb), 1)); },
	    o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
	INC_LIST;
    }
    (*ZId)->isdeffed=1; (*ZId)->hassh =1;
    if (!(*ZIf)) { (*ZId)->next = tagdecs; tagdecs = (*ZId); }
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRexponent__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 34:
	{
	    ADVANCE_LEXER;
	    ZRsigned__nat__body ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    o_make_signed_nat(out_tdfbool(0), out_tdfint32(UL(0)));
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR681 PROTO_N ((ZIa, ZIb, ZIc, ZId, ZIf))
  PROTO_T (TDF *ZIa X TDF *ZIb X PTR_TDF *ZIc X PTR_Tagdec *ZId X int *ZIf)
{
    switch (CURRENT_TERMINAL) {
      case 36:
	{
	    ADVANCE_LEXER;
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((*ZIc));
    (*ZId)->iscommon = 1;
    o_common_tagdef(out_tdfint32(UL(local_name(&(*ZId)->idname.name, tag_ent))), {},
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), (*ZIf))); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(*ZIf)) {
	o_common_tagdec(out_tdfint32(UL(non_local(&(*ZId)->idname.name,tag_ent))),
	    {},
	    if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	    o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
	INC_LIST;
    }
    (*ZId)->isdeffed=1; (*ZId)->hassh =1;
    if (!(*ZIf)) { (*ZId)->next = tagdecs; tagdecs = (*ZId); }
	    }
	}
	break;
      default:
	{
	    {

    o_make_value(o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
	    }
	    {

    RESET_TDF((*ZIc));
    (*ZId)->iscommon = 1;
    o_common_tagdef(out_tdfint32(UL(local_name(&(*ZId)->idname.name, tag_ent))), {},
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), (*ZIf))); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(*ZIf)) {
	o_common_tagdec(out_tdfint32(UL(non_local(&(*ZId)->idname.name,tag_ent))),
	    {},
	    if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	    o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
	INC_LIST;
    }
    (*ZId)->isdeffed=1; (*ZId)->hassh =1;
    if (!(*ZIf)) { (*ZId)->next = tagdecs; tagdecs = (*ZId); }
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRclosed__exp PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 58:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    PTR_TDF ZId;
	    PTR_Labdec ZIe;

	    ADVANCE_LEXER;
	    {

    /* (ZIb) uninitialised */
    (ZIe) = labdecs;
    (ZIc) = g_lablist;
    INIT_TDF(&g_lablist);
    SET_TDF((ZId), &(ZIa));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 76:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRexp__sequence ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 11:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRlabelled__list ();
	    switch (CURRENT_TERMINAL) {
	      case 20:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    RESET_TDF((ZId));
    o_labelled( { append_TDF(&g_lablist,1);
		  current_TDF->no = g_lablist.no;},
		  append_TDF(&(ZIa), 1),
		  { append_TDF(&(ZIb),1);
		    current_TDF->no = g_lablist.no;});
    tidy_labels((ZIe));
    g_lablist = (ZIc);
	    }
	}
	break;
      case 76:
	{
	    ADVANCE_LEXER;
	    ZRexp__sequence ();
	    switch (CURRENT_TERMINAL) {
	      case 20:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 86:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    PTR_TDF ZId;
	    int ZIe;
	    PTR_Labdec ZIf;

	    ADVANCE_LEXER;
	    {

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = defaultlab;
    (ZIf) = labdecs;
    defaultlab = -1;
    SET_TDF((ZId), &(ZIa));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 76:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRexp__sequence ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 11:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRlabset__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIc) = optlab;
    defaultlab = (ZIe);
    tidy_labels((ZIf));
	    }
	    ZRexp__sequence ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    INIT_TDF((ZId));
    RESET_TDF((ZId));
    o_conditional(append_TDF(&(ZIc),1),
		  append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 20:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 88:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    PTR_TDF ZId;
	    PTR_Labdec ZIe;
	    int ZIf;

	    ADVANCE_LEXER;
	    {

    /* (ZIb), (ZIc), (ZIf) uninitialised */
    (ZIe) = labdecs;
    SET_TDF((ZId), &(ZIa));
	    }
	    ZRrepeat__starter__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIf) = defaultlab;
    defaultlab = -1;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 76:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRlabset__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIc) = optlab;
    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
	    }
	    ZRexp__sequence ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    o_repeat(append_TDF(&(ZIc),1), append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
    tidy_labels((ZIe));
    defaultlab = (ZIf);
	    }
	    switch (CURRENT_TERMINAL) {
	      case 20:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 61: case 124:
	{
	    PTR_Tagdec ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    TDF ZId;
	    PTR_TDF ZIe;
	    Name ZIf;
	    int ZIg;

	    {

    (ZIa) = localdecs;
	    }
	    ZRtag__intro ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIg) = localdecs->isvar;
    (ZIb) = intro_acc;
    (ZIc) = intro_init;
    (ZIf) = localdecs->idname.name;
    SET_TDF((ZIe), &(ZId));
	    }
	    ZRclosed__exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIe));
    if ((ZIg)) {
	o_variable( if((ZIb).no!=0) { OPTION(append_TDF(&(ZIb),1)); },
		    make_tag(&(ZIf)), append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1));
    } else {
	o_identify( if((ZIb).no!=0) { OPTION(append_TDF(&(ZIb),1)); },
		    make_tag(&(ZIf)), append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1));
    }
	    }
	    {

    localdecs = (ZIa);
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_bool PROTO_Z ()
{
  ZL2_bool:;
    switch (CURRENT_TERMINAL) {
      case 17:
	{
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 24:
		    {
			ADVANCE_LEXER;
			goto ZL2_bool;
		    }
		    /*UNREACHED*/
		  case 86:
		    {
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			{

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			  case 78:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  case 130:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
			}
			read_bool ();
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  case 130:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
			}
			read_bool ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    o_bool_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		append_TDF(&(ZIc),1));
			}
			switch (CURRENT_TERMINAL) {
			  case 29:
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
	    }
	}
	break;
      case 16:
	{
	    int ZIa;

	    {

    (ZIa) = lex_v.val.v;
	    }
	    ADVANCE_LEXER;
	    {

    (constructs[(ZIa)].f)();
	    }
	}
	break;
      case 18:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZRvarintro__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 129:
	{
	    ADVANCE_LEXER;
	    read_tag ();
	    switch (CURRENT_TERMINAL) {
	      case 24:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_alignment ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_ntest PROTO_Z ()
{
  ZL2_ntest:;
    switch (CURRENT_TERMINAL) {
      case 74:
	{
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 24:
		    {
			ADVANCE_LEXER;
			goto ZL2_ntest;
		    }
		    /*UNREACHED*/
		  case 86:
		    {
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			ADVANCE_LEXER;
			{

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
			}
			switch (CURRENT_TERMINAL) {
			  case 78:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
			}
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_ntest ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
			}
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_ntest ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    o_ntest_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		 append_TDF(&(ZIc),1));
			}
			switch (CURRENT_TERMINAL) {
			  case 29:
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
	    }
	}
	break;
      case 75:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 87:
	{
	    {

    char * n = lex_v.val.name;
    if (strcmp(n,"!<")==0) { o_not_less_than; }
    else if (strcmp(n,"!<=")==0) { o_not_less_than_or_equal; }
    else if (strcmp(n,"!=")==0) { o_not_equal; }
    else if (strcmp(n,"!>")==0) { o_not_greater_than; }
    else if (strcmp(n,"!>=")==0) { o_not_greater_than_or_equal; }
    else if (strcmp(n,"!Comparable")==0) { o_not_comparable; }
    else if (strcmp(n,"<")==0) { o_less_than; }
    else if (strcmp(n,"<=")==0) { o_less_than_or_equal; }
    else if (strcmp(n,"==")==0) { o_equal; }
    else if (strcmp(n,">")==0) { o_greater_than; }
    else if (strcmp(n,">=")==0) { o_greater_than_or_equal; }
    else if (strcmp(n,"Comparable")==0) { o_comparable; }
    else { fail("%s is not a comparison", n); }
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

void
read_bitfield_variety PROTO_Z ()
{
  ZL2_bitfield__variety:;
    switch (CURRENT_TERMINAL) {
      case 14:
	{
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 24:
		    {
			ADVANCE_LEXER;
			goto ZL2_bitfield__variety;
		    }
		    /*UNREACHED*/
		  case 86:
		    {
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			{

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			  case 78:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  case 130:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
			}
			read_bitfield_variety ();
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  case 130:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
			}
			read_bitfield_variety ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    o_bfvar_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		 append_TDF(&(ZIc),1));
			}
			switch (CURRENT_TERMINAL) {
			  case 29:
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
	    }
	}
	break;
      case 16: case 17: case 18: case 22: case 55:
      case 69: case 70: case 71: case 101: case 121:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;

	    {

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
	    }
	    ZRbitfield__sign ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
	    }
	    read_nat ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    o_bfvar_bits(append_TDF(&(ZIa),1), append_TDF(&(ZIb), 1));
	    }
	}
	break;
      case 13:
	{
	    int ZIa;

	    {

    (ZIa) = lex_v.val.v;
	    }
	    ADVANCE_LEXER;
	    {

    (constructs[(ZIa)].f)();
	    }
	}
	break;
      case 15:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZRsigned__nat__body PROTO_Z ()
{
  ZL2_signed__nat__body:;
    switch (CURRENT_TERMINAL) {
      case 68:
	{
	    ADVANCE_LEXER;
	    ZR634 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 99:
	{
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 24:
		    {
			ADVANCE_LEXER;
			goto ZL2_signed__nat__body;
		    }
		    /*UNREACHED*/
		  case 86:
		    {
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			ADVANCE_LEXER;
			{

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
			}
			switch (CURRENT_TERMINAL) {
			  case 78:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
			}
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			ZRsigned__nat__body ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
			}
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			ZRsigned__nat__body ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    o_signed_nat_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		      append_TDF(&(ZIc),1));
			}
			switch (CURRENT_TERMINAL) {
			  case 29:
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
	    }
	}
	break;
      case 22: case 55:
	{
	    ZRinteger ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    o_make_signed_nat(out_tdfbool(0), out_tdfint32(intvalue));
	    }
	}
	break;
      case 98:
	{
	    int ZIa;

	    {

    (ZIa) = lex_v.val.v;
	    }
	    ADVANCE_LEXER;
	    {

    (constructs[(ZIa)].f)();
	    }
	}
	break;
      case 100:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 62:
	{
	    {

    o_make_signed_nat(out_tdfbool(0), out_tdfint32(cLINE));
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 10:
	{
	    TDF ZIa;
	    PTR_TDF ZIb;

	    {

    SET_TDF((ZIb), &(ZIa));
    if (strcmp(lex_v.val.name, "+")) fail("Only + or - on NATs");
	    }
	    ADVANCE_LEXER;
	    ZRnat__not__int ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIb));
    o_snat_from_nat(o_false, append_TDF(&(ZIa),1));
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRlabset__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      default:
	{
	    {

    TDF * hold;
    SET_TDF(hold, &optlab);
    if (defaultlab==-1) defaultlab = next_label();
    o_make_label(out_tdfint32(UL(defaultlab)));
    RESET_TDF(hold);
	    }
	}
	break;
      case 24:
	{
	    PTR_TDF ZIa;

	    {

    SET_TDF((ZIa), &optlab);
    g_labdec = (Labdec*)0;
    if (defaultlab != -1) { fail("This conditional uses a default jump"); }
	    }
	    ADVANCE_LEXER;
	    read_label ();
	    switch (CURRENT_TERMINAL) {
	      case 24:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    if (g_labdec != (Labdec*)0) {
	if (g_labdec->declared) {
	    fail("Label %s set twice", g_labdec->idname.id);
	}
	g_labdec->declared = 1;
    }
    RESET_TDF((ZIa));
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRkeep__item PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 2: case 5: case 9: case 15: case 18:
      case 40: case 43: case 49: case 60: case 71:
      case 75: case 91: case 96: case 100: case 111:
      case 120: case 128:
	{
	    {

    Tokdec * k = lex_v.val.tokname;
    k->iskept = 1;
	    }
	    {
		switch (CURRENT_TERMINAL) {
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
		  case 9:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 15:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 18:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 40:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 43:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 49:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 60:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 71:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 75:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 91:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 96:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 100:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 111:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 120:
		    {
			ADVANCE_LEXER;
		    }
		    break;
		  case 128:
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
      case 54:
	{
	    {

    char * n = lex_v.val.name;
    Tagdec * t = find_tag(n);
    if (t != (Tagdec*)0){
	t->iskept = 1;
     } else {
	Al_tagdec * a = find_al_tag(n);
	if (a == (Al_tagdec*)0) {
	    fail("Ident %s not declared",n);
	}
	a->iskept = 1;
    }
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRstruct__def PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	PTR_Tokdec ZIa;

	switch (CURRENT_TERMINAL) {
	  case 108:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    char * n = lex_v.val.name;
    (ZIa) = find_tok(n);
    SELECT_UNIT(tokdef_unit);
    if ((ZIa)!=(Tokdec*)0) fail("Struct name %s must be unique", n);
    (ZIa) = MALLOC(Tokdec); NEW_IDNAME((ZIa)->idname, n, tok_ent);
    (ZIa)->sort.ressort.sort = shape_sort; (ZIa)->sort.pars = (Tokpar*)0;
    (ZIa)->isdeffed = 1; (ZIa)->isused=0; (ZIa)->iskept=0;
    g_lastfield = -1;
	}
	switch (CURRENT_TERMINAL) {
	  case 54:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 78:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRfield__list ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    o_make_tokdef(out_tdfint32(LOCNAME((ZIa)->idname)), {},
	o_token_def(o_shape, {},
	    o_compound(o_offset_add(
		o_exp_apply_token(
		    o_make_tok(out_tdfint32(UL(g_lastfield))),{}),
		o_shape_offset(append_TDF(&g_lastshape, 1))))))
    INC_LIST;
    (ZIa)->next = tokdecs;
    tokdecs = (ZIa);
	}
	switch (CURRENT_TERMINAL) {
	  case 29:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRnonst__shape__body PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 83:
	{
	    TDF ZIa;
	    PTR_TDF ZIb;

	    ADVANCE_LEXER;
	    {

    SET_TDF((ZIb), &(ZIa));
	    }
	    read_shape ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIb));
    o_pointer(o_alignment(append_TDF(&(ZIa),1)));
	    }
	}
	break;
      case 95:
	{
	    ADVANCE_LEXER;
	    ZR676 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 94:
	{
	    int ZIa;

	    {

    (ZIa) = lex_v.val.v;
	    }
	    ADVANCE_LEXER;
	    {

    (constructs[(ZIa)].f)();
	    }
	}
	break;
      case 96:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_tag PROTO_Z ()
{
  ZL2_tag:;
    switch (CURRENT_TERMINAL) {
      case 110:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 24:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    goto ZL2_tag;
	}
	/*UNREACHED*/
      case 109:
	{
	    int ZIa;

	    {

    (ZIa) = lex_v.val.v;
	    }
	    ADVANCE_LEXER;
	    {

    (constructs[(ZIa)].f)();
	    }
	}
	break;
      case 111:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 54:
	{
	    {

    char * n =lex_v.val.name;
    Tagdec * x = find_tag(n);
    if (x == (Tagdec*)0) { fail("Ident %s not declared", n); }
    x->isused = 1;
    make_tag(&x->idname.name);
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZRvariety__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 78:
	{
	    ADVANCE_LEXER;
	    read_variety ();
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      case 130:
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

    /* unsigned char */
    o_var_limits(
	o_make_signed_nat(out_tdfbool(0), out_tdfint32(UL(0))),
	o_make_signed_nat(out_tdfbool(0), out_tdfint32(UL(255))));
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_nat_option PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 22: case 55: case 69: case 70: case 71:
	{
	    TDF ZIa;
	    PTR_TDF ZIb;

	    {

    SET_TDF((ZIb), &(ZIa));
	    }
	    read_nat ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIb));
    OPTION(append_TDF(&(ZIa),1));
	    }
	}
	break;
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZRsortname__list__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 1: case 4: case 8: case 14: case 17:
      case 39: case 42: case 48: case 59: case 70:
      case 74: case 90: case 95: case 99: case 105:
      case 110: case 116: case 119: case 127:
	{
	    ZRsortname__list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    g_tokpars = (Tokpar*)0;
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_floating_variety PROTO_Z ()
{
  ZL2_floating__variety:;
    switch (CURRENT_TERMINAL) {
      case 32:
	{
	    ADVANCE_LEXER;
	    {

    o_flvar_parms(o_make_nat(out_tdfint32(UL(2))),
		  o_make_nat(out_tdfint32(UL(MANT_DOUBLE))),
		  o_make_nat(out_tdfint32(UL(MINEXP_DOUBLE))),
		  o_make_nat(out_tdfint32(UL(MAXEXP_DOUBLE))));
	    }
	}
	break;
      case 46:
	{
	    ADVANCE_LEXER;
	    {

    o_flvar_parms(o_make_nat(out_tdfint32(UL(2))),
		  o_make_nat(out_tdfint32(UL(MANT_FLOAT))),
		  o_make_nat(out_tdfint32(UL(MINEXP_FLOAT))),
		  o_make_nat(out_tdfint32(UL(MAXEXP_FLOAT))));
	    }
	}
	break;
      case 48:
	{
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 24:
		    {
			ADVANCE_LEXER;
			goto ZL2_floating__variety;
		    }
		    /*UNREACHED*/
		  case 86:
		    {
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			{

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			  case 78:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  case 130:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
			}
			read_floating_variety ();
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  case 130:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
			}
			read_floating_variety ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    o_flvar_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		 append_TDF(&(ZIc),1));
			}
			switch (CURRENT_TERMINAL) {
			  case 29:
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
	    }
	}
	break;
      case 47:
	{
	    int ZIa;

	    {

    (ZIa) = lex_v.val.v;
	    }
	    ADVANCE_LEXER;
	    {

    (constructs[(ZIa)].f)();
	    }
	}
	break;
      case 49:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZRtagshacc PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	TDF ZIa;
	PTR_TDF ZIb;
	PTR_Tagdec ZIc;
	int ZId;

	{

    /* (ZId) uninitialised */
    char * n =lex_v.val.name;
    (ZIc) = find_tag(n);
    if ((ZIc) != (Tagdec*)0) fail("Ident %s already declared", n);
    (ZIc) = MALLOC(Tagdec);
    (ZIc)->hassh = 2; (ZIc)->isvar =1; (ZIc)->isdeffed = 1; (ZIc)->iskept=0;
    NEW_IDNAME((ZIc)->idname, n, tag_ent);
    g_has_vis =0;
    SET_TDF((ZIb), &(ZIa));
	}
	switch (CURRENT_TERMINAL) {
	  case 54:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRaccess__opt ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    RESET_TDF((ZIb));
    SET_TDF((ZIb), &(ZIc)->sh.tdfsh);
    (ZId) = g_has_vis;
	}
	switch (CURRENT_TERMINAL) {
	  case 24:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	read_shape ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    RESET_TDF((ZIb));
    o_make_tagshacc( append_TDF(&(ZIc)->sh.tdfsh, 0),
	if((ZIa).no != 0) {OPTION(append_TDF(&(ZIa),1));},
	make_tag(&(ZIc)->idname.name));
    if ((ZId)) {
	Tagdec * y = MALLOC(Tagdec);
	*y = *(ZIc);
	y->next = tagdecs;
	tagdecs = y;
    }
    (ZIc)->next = localdecs;
    localdecs = (ZIc);
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRelement__list__opt PROTO_Z ()
{
  ZL2_element__list__opt:;
    switch (CURRENT_TERMINAL) {
      case 6: case 26: case 27: case 53: case 61:
      case 81: case 106: case 108: case 113: case 114:
      case 124: case 125:
	{
	    ZRelement ();
	    switch (CURRENT_TERMINAL) {
	      case 93:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    goto ZL2_element__list__opt;
	}
	/*UNREACHED*/
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_nat PROTO_Z ()
{
  ZL2_nat:;
    switch (CURRENT_TERMINAL) {
      case 22: case 55:
	{
	    ZRinteger ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    o_make_nat(out_tdfint32(intvalue));
	    }
	}
	break;
      case 69: case 70: case 71:
	{
	    ZRnat__not__int ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

void
read_alignment PROTO_Z ()
{
  ZL2_alignment:;
    switch (CURRENT_TERMINAL) {
      case 8:
	{
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 24:
		    {
			ADVANCE_LEXER;
			goto ZL2_alignment;
		    }
		    /*UNREACHED*/
		  case 86:
		    {
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			ADVANCE_LEXER;
			{

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
			}
			switch (CURRENT_TERMINAL) {
			  case 78:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  case 130:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
			}
			read_alignment ();
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  case 130:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
			}
			read_alignment ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    o_alignment_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		     append_TDF(&(ZIc),1));
			}
			switch (CURRENT_TERMINAL) {
			  case 29:
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
	    }
	}
	break;
      case 78:
	{
	    ADVANCE_LEXER;
	    ZRalignment__list__opt ();
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 4: case 5: case 54:
	{
	    TDF ZIa;
	    PTR_TDF ZIb;

	    {

    SET_TDF((ZIb), &(ZIa));
	    }
	    read_al_tag ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIb));
    o_obtain_al_tag(append_TDF(&(ZIa), 1));
	    }
	}
	break;
      case 7:
	{
	    int ZIa;

	    {

    (ZIa) = lex_v.val.v;
	    }
	    ADVANCE_LEXER;
	    {

    (constructs[(ZIa)].f)();
	    }
	}
	break;
      case 9:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZRvarpar__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 129:
	{
	    ADVANCE_LEXER;
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    current_TDF->no=1;
	    }
	}
	break;
      default:
	{
	    {

    current_TDF->no=0;
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRkeep__list PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
  ZL2_keep__list:;
    {
	ZRkeep__item ();
	{
	    switch (CURRENT_TERMINAL) {
	      case 25:
		{
		    ADVANCE_LEXER;
		    goto ZL2_keep__list;
		}
		/*UNREACHED*/
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRproc__def PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	TDF ZIa;
	TDF ZIb;
	PTR_TDF ZIc;
	PTR_Tagdec ZId;
	PTR_char ZIe;
	int ZIf;

	switch (CURRENT_TERMINAL) {
	  case 81:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    /* (ZIa) uninitialised */
    (ZIe) =lex_v.val.name;
    (ZId) = find_tag((ZIe));
    SELECT_UNIT(tagdef_unit);
    if((ZId)!= (Tagdec*)0) {
	if ((ZId)->isdeffed && !(ZId)->iscommon) fail("Tag %s defined twice", (ZIe));
	if ((ZId)->isvar) fail("Tag %s declared as variable", (ZIe));
	(ZIf) = 1;
    } else {
	(ZId) = MALLOC(Tagdec);
	(ZId)->hassh = 0; (ZId)->isvar=0; (ZId)->iskept=0; (ZId)->iscommon = 0;
	(ZId)->isused = 0;
	NEW_IDNAME((ZId)->idname, (ZIe), tag_ent);
	(ZIf) = 0;
    }
    SET_TDF((ZIc), &(ZIb));
	}
	switch (CURRENT_TERMINAL) {
	  case 54:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 36:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIa));
	}
	ZRproc__def__body ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    RESET_TDF((ZIc));
    o_make_id_tagdef(out_tdfint32(UL(local_name(&(ZId)->idname.name, tag_ent))),
	if ((ZIb).no !=0) { OPTION(append_TDF(&(ZIb), (ZIf))); },
      append_TDF(&(ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(ZIf)) {
	o_make_id_tagdec(out_tdfint32(UL(non_local(&(ZId)->idname.name,tag_ent))),
	    {},
	    if ((ZIb).no !=0) { OPTION(append_TDF(&(ZIb), 1)); },
	    o_proc);
	INC_LIST;
    }
    (ZId)->isdeffed=1;
    if (!(ZIf)) {(ZId)->next = tagdecs; tagdecs = (ZId);}
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_error_code_list PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	read_error_code ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    current_TDF->no = 1;
	}
	ZR625 ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZRcallee__var__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 31:
	{
	    ADVANCE_LEXER;
	    {

    g_ce_v = 1;
	    }
	}
	break;
      default:
	{
	    {

    g_ce_v = 0;
	    }
	}
	break;
      case 130:
	return;
    }
}

static void
ZRtag__dec PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 27:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;
	    PTR_Tagdec ZId;

	    ADVANCE_LEXER;
	    {

    /* (ZIb) uninitialised */
    char * n =lex_v.val.name;
    (ZId) = find_tag(n);
    if ((ZId) != (Tagdec*)0) fail("Tag %s declared twice", n);
    SELECT_UNIT(tagdec_unit);
    (ZId) = MALLOC(Tagdec); NEW_IDNAME((ZId)->idname, n, tag_ent);
    (ZId)->isdeffed = 0; (ZId)->hassh = 1; (ZId)->iskept=0; (ZId)->iscommon=0;
    (ZId)->isused = 0;
    SET_TDF((ZIc), &(ZIa));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 54:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRaccess__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
	    }
	    ZRsignature__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    g_shtokname = &(ZId)->sh.shtok;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 24:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRshapetok ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    (ZId)->iscommon = 1;
    o_common_tagdec(out_tdfint32(LOCNAME((ZId)->idname)),
	if ((ZIa).no !=0) { OPTION(append_TDF(&(ZIa), 1)); },
	if ((ZIb).no !=0) { OPTION(append_TDF(&(ZIb), 1)); },
	o_shape_apply_token(make_tok(&(ZId)->sh.shtok), {}));
    INC_LIST;
    (ZId)->next = tagdecs;
    (ZId)->isvar = 1;
    tagdecs = (ZId);
	    }
	}
	break;
      case 53:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;
	    PTR_Tagdec ZId;

	    ADVANCE_LEXER;
	    {

    /* (ZIb) uninitialised */
    char * n =lex_v.val.name;
    (ZId) = find_tag(n);
    if ((ZId) != (Tagdec*)0) fail("Tag %s declared twice", n);
    SELECT_UNIT(tagdec_unit);
    (ZId) = MALLOC(Tagdec); NEW_IDNAME((ZId)->idname, n, tag_ent);
    (ZId)->isdeffed = 0; (ZId)->hassh = 1; (ZId)->iskept=0; (ZId)->iscommon=0;
    (ZId)->isused = 0;
    SET_TDF((ZIc), &(ZIa));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 54:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRaccess__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
	    }
	    ZRsignature__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    g_shtokname = &(ZId)->sh.shtok;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 24:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRshapetok ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    o_make_id_tagdec(out_tdfint32(LOCNAME((ZId)->idname)),
	if ((ZIa).no !=0) { OPTION(append_TDF(&(ZIa), 1)); },
	if ((ZIb).no !=0) { OPTION(append_TDF(&(ZIb), 1)); },
	o_shape_apply_token(make_tok(&(ZId)->sh.shtok), {}));
    INC_LIST;
    (ZId)->next = tagdecs;
    (ZId)->isvar = 0;
    tagdecs = (ZId);
	    }
	}
	break;
      case 125:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;
	    PTR_Tagdec ZId;

	    ADVANCE_LEXER;
	    {

    /* (ZIb) uninitialised */
    char * n =lex_v.val.name;
    (ZId) = find_tag(n);
    if ((ZId) != (Tagdec*)0) fail("Tag %s declared twice", n);
    SELECT_UNIT(tagdec_unit);
    (ZId) = MALLOC(Tagdec); NEW_IDNAME((ZId)->idname, n, tag_ent);
    (ZId)->isdeffed = 0; (ZId)->hassh = 1; (ZId)->iskept=0; (ZId)->iscommon=0;
    (ZId)->isused = 0;
    SET_TDF((ZIc), &(ZIa));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 54:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRaccess__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
	    }
	    ZRsignature__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    g_shtokname = &(ZId)->sh.shtok;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 24:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRshapetok ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    o_make_var_tagdec(out_tdfint32(LOCNAME((ZId)->idname)),
	if ((ZIa).no !=0) { OPTION(append_TDF(&(ZIa), 1)); },
	if ((ZIb).no !=0) { OPTION(append_TDF(&(ZIb), 1)); },
	o_shape_apply_token(make_tok(&(ZId)->sh.shtok), {}));
    INC_LIST;
    (ZId)->next = tagdecs;
    (ZId)->isvar = 1;
    tagdecs = (ZId);
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRtag__intro PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 61:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;
	    PTR_Tagdec ZId;
	    int ZIe;

	    ADVANCE_LEXER;
	    {

    /* (ZIb), (ZIe) uninitialised */
    char* n = lex_v.val.name;
    (ZId) = find_tag(n);
    if ((ZId) != (Tagdec*)0) { fail("Tag %s declared twice", n); }
    (ZId) = MALLOC(Tagdec); (ZId)->isdeffed = 1; (ZId)->hassh=0; (ZId)->iskept=0;
    NEW_IDNAME((ZId)->idname, n, tag_ent);
    g_has_vis = 0;
    SET_TDF((ZIc), &(ZIa));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 54:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRaccess__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
    (ZIe) = g_has_vis;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 36:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    intro_acc = (ZIa);
    intro_init = (ZIb);
    (ZId)->isvar=0;
    if ((ZIe)) {
	Tagdec * y = MALLOC(Tagdec);
	*y = *(ZId);
	y->next = tagdecs;
	tagdecs = y;
    }
    (ZId)->next = localdecs;
    localdecs = (ZId);
	    }
	}
	break;
      case 124:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;
	    PTR_Tagdec ZId;
	    int ZIe;

	    ADVANCE_LEXER;
	    {

    /* (ZIb), (ZIe) uninitialised */
    char* n = lex_v.val.name;
    (ZId) = find_tag(n);
    if ((ZId) != (Tagdec*)0) { fail("Tag %s declared twice", n); }
    (ZId) = MALLOC(Tagdec); (ZId)->isdeffed = 1; (ZId)->hassh=0; (ZId)->iskept=0;
    NEW_IDNAME((ZId)->idname, n, tag_ent);
    g_has_vis = 0;
    SET_TDF((ZIc), &(ZIa));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 54:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRaccess__opt ();
	    ZR669 (&ZIa, &ZIb, &ZIc, &ZId, &ZIe);
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_exp PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	TDF ZIa;
	PTR_TDF ZIb;
	int ZIc;
	unsigned_long ZId;
	int ZIe;

	{

    (ZIc) = (current_TDF->first == current_TDF->last &&
	      current_TDF->first->usage == 0 &&
	      current_TDF->first->offst == 0);
    (ZId) = cLINE;
    (ZIe) = bind;
    if (!(ZIc) || line_no_tok != -1) { SET_TDF((ZIb), &(ZIa)); }
	}
	ZRexp__body ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if (!(ZIc) || line_no_tok != -1) {
	SET((ZIb));
	RESET_TDF((ZIb));
	if (line_no_tok != -1) {
	    o_exp_apply_token(
		o_make_tok(out_tdfint32(UL(cname_to_lname(line_no_tok,tok_ent)))),
		{ append_TDF(&(ZIa),1);
		  o_make_sourcemark(FILENAME(),
			o_make_nat(out_tdfint32((ZId))),
			o_make_nat(out_tdfint32(UL((ZIe)))));
			o_make_sourcemark(FILENAME(),
			    o_make_nat(out_tdfint32(cLINE)),
			    o_make_nat(out_tdfint32(UL(bind))));
		});
	 } else append_TDF(&(ZIa),1);
    }
	}
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZRtag__def PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 26:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;
	    PTR_Tagdec ZId;
	    PTR_char ZIe;
	    int ZIf;

	    ADVANCE_LEXER;
	    {

    /* (ZIa) uninitialised */
    (ZIe) =lex_v.val.name;
    (ZId) = find_tag((ZIe));
    SELECT_UNIT(tagdef_unit);
    if((ZId)!= (Tagdec*)0) {
	if ((ZId)->isdeffed && !(ZId)->iscommon) fail("Tag %s defined twice", (ZIe));
	if (!(ZId)->isvar) fail("Tag %s declared as non-variable", (ZIe));
	(ZIf) = 1;
    } else {
	(ZId) = MALLOC(Tagdec);
	(ZId)->hassh = 0; (ZId)->isvar=1; (ZId)->iskept=0; (ZId)->iscommon = 0;
	(ZId)->isused=0;
	NEW_IDNAME((ZId)->idname, (ZIe), tag_ent);
	(ZIf)=0;
    }
    SET_TDF((ZIc), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 54:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRsignature__opt ();
	    ZR678 (&ZIa, &ZIb, &ZIc, &ZId, &ZIe, &ZIf);
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 61:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;
	    PTR_Tagdec ZId;
	    PTR_char ZIe;
	    int ZIf;

	    ADVANCE_LEXER;
	    {

    /* (ZIa) uninitialised */
    (ZIe) =lex_v.val.name;
    (ZId) = find_tag((ZIe));
    SELECT_UNIT(tagdef_unit);
    if((ZId)!= (Tagdec*)0) {
	if ((ZId)->isdeffed && !(ZId)->iscommon) fail("Tag %s defined twice", (ZIe));
	if ((ZId)->isvar) fail("Tag %s declared as variable", (ZIe));
	(ZIf) = 1;
    } else {
	(ZId) = MALLOC(Tagdec);
	(ZId)->hassh = 0; (ZId)->isvar=0; (ZId)->iskept=0; (ZId)->iscommon = 0;
	(ZId)->isused = 0;
	NEW_IDNAME((ZId)->idname, (ZIe), tag_ent);
	(ZIf) = 0;
    }
    SET_TDF((ZIc), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 54:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRsignature__opt ();
	    ZR679 (&ZIa, &ZIb, &ZIc, &ZId, &ZIe, &ZIf);
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 106:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;
	    PTR_Tagdec ZId;
	    PTR_char ZIe;
	    int ZIf;
	    TDF ZIg;
	    PTR_char ZIh;

	    ADVANCE_LEXER;
	    {

    /* (ZIa) uninitialised */
    (ZIe) =lex_v.val.name;
    (ZId) = find_tag((ZIe));
    SELECT_UNIT(tagdef_unit);
    if((ZId)!= (Tagdec*)0) {
	if ((ZId)->isdeffed && !(ZId)->iscommon) fail("Tag %s defined twice", (ZIe));
	if (!(ZId)->isvar) fail("Tag %s declared as non-variable", (ZIe));
	(ZIf) = 1;
    } else {
	(ZId) = MALLOC(Tagdec);
	(ZId)->hassh = 0; (ZId)->isvar=1; (ZId)->iskept=0; (ZId)->iscommon = 0;
	(ZId)->isused=0;
	NEW_IDNAME((ZId)->idname, (ZIe), tag_ent);
	(ZIf)=0;
    }
    SET_TDF((ZIc), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 54:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRsignature__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIg));
	    }
	    ZRvariety__opt ();
	    switch (CURRENT_TERMINAL) {
	      case 36:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    (ZIh) = lex_v.val.name;
    if ((ZId)->hassh) fail("Two declaration shapes for %s", (ZIe));
    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIa));
    o_make_nof_int(append_TDF(&(ZIg), 0),
	o_make_string(out_tdfstring_bytes((ZIh), 8, UI(strlen((ZIh))+1))));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 85:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    RESET_TDF((ZIc));
    o_make_var_tagdef(out_tdfint32(UL(local_name(&(ZId)->idname.name, tag_ent))),
	{}, {}, append_TDF(&(ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(ZIf)) {
	o_make_var_tagdec(out_tdfint32(UL(non_local(&(ZId)->idname.name,tag_ent))),
	    {}, {},
	    o_nof(o_make_nat(out_tdfint32(UL(strlen((ZIh))+1))),
		o_integer(append_TDF(&(ZIg), 0))));
       INC_LIST;
    }
    (ZId)->isdeffed=1;
    if (!(ZIf)) { (ZId)->next = tagdecs; tagdecs = (ZId); }
	    }
	}
	break;
      case 124:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;
	    PTR_Tagdec ZId;
	    PTR_char ZIe;
	    int ZIf;

	    ADVANCE_LEXER;
	    {

    /* (ZIa) uninitialised */
    (ZIe) =lex_v.val.name;
    (ZId) = find_tag((ZIe));
    SELECT_UNIT(tagdef_unit);
    if((ZId)!= (Tagdec*)0) {
	if ((ZId)->isdeffed && !(ZId)->iscommon) fail("Tag %s defined twice", (ZIe));
	if (!(ZId)->isvar) fail("Tag %s declared as non-variable", (ZIe));
	(ZIf) = 1;
    } else {
	(ZId) = MALLOC(Tagdec);
	(ZId)->hassh = 0; (ZId)->isvar=1; (ZId)->iskept=0; (ZId)->iscommon = 0;
	(ZId)->isused=0;
	NEW_IDNAME((ZId)->idname, (ZIe), tag_ent);
	(ZIf)=0;
    }
    SET_TDF((ZIc), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 54:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRsignature__opt ();
	    ZR677 (&ZIa, &ZIb, &ZIc, &ZId, &ZIe, &ZIf);
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRotagexp__list__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 10: case 19: case 22: case 28: case 41:
      case 42: case 43: case 44: case 45: case 52:
      case 54: case 55: case 58: case 61: case 62:
      case 68: case 76: case 77: case 78: case 79:
      case 81: case 82: case 84: case 85: case 86:
      case 88: case 98: case 99: case 100: case 102:
      case 103: case 104: case 105: case 107: case 109:
      case 110: case 111: case 124:
	{
	    ZRotagexp__list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    current_TDF->no = 0;
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRtok__formal__list PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	PTR_Tokdec ZIa;

	{

    char * n = lex_v.val.name;
    (ZIa) = find_tok(n);
    if ((ZIa)!=(Tokdec*)0) fail("Token parameter name %s must be unique", n);
    (ZIa) = MALLOC(Tokdec); NEW_IDNAME((ZIa)->idname, n, tok_ent);
    (ZIa)->isdeffed = 1; (ZIa)->isused = 0; (ZIa)->iskept=0;
    (ZIa)->next = (Tokdec*)0;
	}
	switch (CURRENT_TERMINAL) {
	  case 54:
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
	ZRfull__sortname ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    (ZIa)->sort.ressort = g_sname;
    (ZIa)->sort.pars = (Tokpar*)0;  /* no pars in formal pars */
    g_tokformals = (ZIa);
	}
	ZR629 ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRuntidy__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 23:
	{
	    ADVANCE_LEXER;
	    {

    g_unt = 2;
	    }
	}
	break;
      case 122:
	{
	    ADVANCE_LEXER;
	    ZR657 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    {

    g_unt = 0;
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRcaller__var__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 31:
	{
	    ADVANCE_LEXER;
	    {

    g_cr_v = 1;
	    }
	}
	break;
      default:
	{
	    {

    g_cr_v = 0;
	    }
	}
	break;
      case 130:
	return;
    }
}

static void
ZRproc__def__body PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 50:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    TDF ZId;
	    PTR_TDF ZIe;
	    int ZIf;
	    int ZIg;
	    int ZIh;
	    PTR_Tagdec ZIi;
	    PTR_Labdec ZIj;

	    ADVANCE_LEXER;
	    {

    /* (ZIb), (ZIc), (ZId) uninitialised */
    /* (ZIf), (ZIg) (ZIh) uninitialised */
    (ZIi) = localdecs;
    (ZIj) = labdecs;
    localdecs = (Tagdec*)0;
    labdecs = (Labdec *)0;
    SET_TDF((ZIe), &(ZIa));
	    }
	    read_shape ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRtagshacc__list__opt ();
	    ZRcaller__var__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIc));
    (ZIf) = g_cr_v;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 93:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRtagshacc__list__opt ();
	    ZRcallee__var__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZId));
    (ZIg) = g_ce_v;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRuntidy__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIh) = g_unt;
	    }
	    ZRclosed__exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIe));
    o_make_general_proc(append_TDF(&(ZIa),1),
			do_procprops((ZIf)+2*(ZIg)+4*(ZIh)),
			{ append_TDF(&(ZIb),1);
			  current_TDF->no = (ZIb).no;},
			{ append_TDF(&(ZIc),1);
			  current_TDF->no = (ZIc).no;},
			append_TDF(&(ZId),1))
    while (labdecs != (Labdec *)0 ) {
	if (!labdecs->declared) {
	    fail("Label %s not declared", labdecs->idname.id);
	}
	labdecs = labdecs->next;
    }
    localdecs = (ZIi);
    labdecs = (ZIj);
	    }
	}
	break;
      case 21: case 32: case 46: case 56: case 64:
      case 83: case 94: case 95: case 96: case 97:
      case 101: case 121:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    TDF ZId;
	    PTR_TDF ZIe;
	    PTR_Tagdec ZIf;
	    PTR_Labdec ZIg;

	    {

    /* (ZIa), (ZIb), (ZIc) uninitialised */
    (ZIf) = localdecs;
    (ZIg) = labdecs;
    localdecs = (Tagdec*)0;
    labdecs = (Labdec *)0;
    SET_TDF((ZIe), &(ZId));
	    }
	    read_shape ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIa))
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRtagshacc__list__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIb));
	    }
	    ZRvarintro__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIc));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRclosed__exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIe));
    o_make_proc(append_TDF(&(ZId),1),
		{ append_TDF(&(ZIa),1); current_TDF->no = (ZIa).no;},
		if ((ZIb).no !=0) {OPTION(append_TDF(&(ZIb),1)); },
		append_TDF(&(ZIc),1);)
    while (labdecs != (Labdec *)0 ) {
	if (!labdecs->declared) {
	    fail("Label %s not declared", labdecs->idname.id);
	}
	labdecs = labdecs->next;
    }
    localdecs = (ZIf);
    labdecs = (ZIg);
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRlabelled__list PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	TDF ZIa;
	PTR_TDF ZIb;

	switch (CURRENT_TERMINAL) {
	  case 24:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    (ZIb) = current_TDF;
    INIT_TDF(&(ZIa));
    current_TDF = &g_lablist;
	}
	read_label ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    if (g_labdec != (Labdec*)0) {
	if (g_labdec->declared) {
	    fail("Label %s set twice", g_labdec->idname.id);
	}
	g_labdec->declared = 1;
    }
    current_TDF = &(ZIa);
	}
	switch (CURRENT_TERMINAL) {
	  case 24:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRexp__sequence ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    RESET_TDF((ZIb));
    append_TDF(&(ZIa), 1);
	}
	ZR668 ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRoffset__exp__list PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	read_exp ();
	switch (CURRENT_TERMINAL) {
	  case 24:
	    break;
	  case 130:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	read_exp ();
	ZR663 ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRbitfield__sign PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 16: case 17: case 18:
	{
	    read_bool ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      default:
	{
	    ZRvariety__sign ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    if (issigned) { o_true; }
    else { o_false; }
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRtok__dec PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	TDF ZIa;
	PTR_TDF ZIb;
	PTR_Tokdec ZIc;

	switch (CURRENT_TERMINAL) {
	  case 113:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    char *n = lex_v.val.name;
    (ZIc) = find_tok(n);
    if ((ZIc) != (Tokdec *)0) fail("Token %s declared twice", n);
    SELECT_UNIT(tokdec_unit);
    (ZIc) = MALLOC(Tokdec);
    NEW_IDNAME((ZIc)->idname, n, tok_ent);
    SET_TDF((ZIb), &(ZIa));
	}
	switch (CURRENT_TERMINAL) {
	  case 54:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRsignature__opt ();
	switch (CURRENT_TERMINAL) {
	  case 24:
	    break;
	  case 130:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 79:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRsortname__list__opt ();
	switch (CURRENT_TERMINAL) {
	  case 30:
	    break;
	  case 130:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRfull__sortname ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    RESET_TDF((ZIb));
    (ZIc)->sort.ressort = g_sname;
    (ZIc)->sort.pars = g_tokpars;
    (ZIc)->next = tokdecs;
    (ZIc)->isdeffed = 0; (ZIc)->isused = 0; (ZIc)->iskept=0; (ZIc)->isparam=0;
    tokdecs = (ZIc);
    o_make_tokdec(out_tdfint32(LOCNAME((ZIc)->idname)),
	if ((ZIa).no != 0) { OPTION(append_TDF(&(ZIa), 1)); },
	out_toksort(&(ZIc)->sort));
    INC_LIST;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRexp__comma__list PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
  ZL2_exp__comma__list:;
    {
	read_exp ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    current_TDF->no++;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 25:
		{
		    ADVANCE_LEXER;
		    goto ZL2_exp__comma__list;
		}
		/*UNREACHED*/
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRexp__body PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	ZRunary__exp ();
	ZR632 ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRtok__def PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	TDF ZIa;
	TDF ZIb;
	PTR_TDF ZIc;
	PTR_Tokdec ZId;
	int ZIe;

	{

    search_for_toks = 0;
	}
	switch (CURRENT_TERMINAL) {
	  case 114:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    char *n = lex_v.val.name;
    (ZId) = find_tok(n);
    (ZIa) = g_tok_defn;
    SELECT_UNIT(tokdef_unit);
    search_for_toks = 1;
    if ((ZId) != (Tokdec *)0) {
	if ((ZId)->isdeffed) fail("Token %s defined twice", n);
	(ZIe) = 1;
    } else {
	(ZId) = MALLOC(Tokdec);
	NEW_IDNAME((ZId)->idname, n, tok_ent);
	(ZIe) = 0;
    }
    SET_TDF((ZIc), &(ZIb));
	}
	switch (CURRENT_TERMINAL) {
	  case 54:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 36:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRtok__def__body ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    RESET_TDF((ZIc));
    (ZId)->sort = g_toksort;
    (ZId)->isdeffed =1; (ZId)->iskept=0; (ZId)->isparam = 0;
    o_make_tokdef(out_tdfint32(UL(local_name(&(ZId)->idname.name,tok_ent))),
	if ((ZIb).no != 0) { OPTION(append_TDF(&(ZIb), 1)); },
	append_TDF(&g_tok_defn, 1));
    INC_LIST;
    if (!(ZIe)) { (ZId)->next = tokdecs; tokdecs = (ZId); (ZId)->isused=0; }
    g_tok_defn = (ZIa);
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRunary__exp PROTO_Z ()
{
  ZL2_unary__exp:;
    switch (CURRENT_TERMINAL) {
      case 19:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;

	    ADVANCE_LEXER;
	    {

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
	    }
	    read_exp ();
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
	    }
	    ZRrange__label__list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    o_case(o_false, append_TDF(&(ZIa),1),
	   { append_TDF(&(ZIb),1); current_TDF->no = (ZIb).no; });
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 28:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 79:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
	    }
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 30:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRoffset__exp__list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    o_make_compound(append_TDF(&(ZIa),1),
		    { append_TDF(&(ZIb),1); current_TDF->no = (ZIb).no; });
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
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
		switch (CURRENT_TERMINAL) {
		  case 24:
		    {
			ADVANCE_LEXER;
			goto ZL2_unary__exp;
		    }
		    /*UNREACHED*/
		  case 86:
		    {
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			ADVANCE_LEXER;
			{

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
			}
			switch (CURRENT_TERMINAL) {
			  case 78:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
			}
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
			}
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    o_exp_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
	       append_TDF(&(ZIc),1));
			}
			switch (CURRENT_TERMINAL) {
			  case 29:
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
	    }
	}
	break;
      case 45:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    PTR_TDF ZId;
	    int ZIe;

	    ADVANCE_LEXER;
	    {

    query_t = lex_float__query;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = query_t;
    SET_TDF((ZId),&(ZIa));
	    }
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId),&(ZIb));
	    }
	    read_ntest ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc))
	    }
	    read_exp ();
	    ZRlabdest__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    switch((ZIe)) {
	case lex_query:
	    o_integer_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_float__query:
	    o_floating_test({}, o_impossible, append_TDF(&(ZIb),1),
	   		append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_ptr__query:
	    o_pointer_test( {}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_proc__query:
	    o_proc_test( {}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	case lex_offset__query:
	    o_offset_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	default: fail("Don't understand test");
    }
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 52:
	{
	    ADVANCE_LEXER;
	    {

    o_fail_installer(read_string());
	    }
	}
	break;
      case 58:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    PTR_TDF ZId;
	    PTR_Labdec ZIe;

	    ADVANCE_LEXER;
	    {

    /* (ZIb) uninitialised */
    (ZIe) = labdecs;
    (ZIc) = g_lablist;
    INIT_TDF(&g_lablist);
    SET_TDF((ZId), &(ZIa));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 76:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRexp__sequence ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 11:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRlabelled__list ();
	    switch (CURRENT_TERMINAL) {
	      case 20:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    RESET_TDF((ZId));
    o_labelled( { append_TDF(&g_lablist,1);
		  current_TDF->no = g_lablist.no;},
		  append_TDF(&(ZIa), 1),
		  { append_TDF(&(ZIb),1);
		    current_TDF->no = g_lablist.no;});
    tidy_labels((ZIe));
    g_lablist = (ZIc);
	    }
	}
	break;
      case 68:
	{
	    ADVANCE_LEXER;
	    ZR645 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 76:
	{
	    ADVANCE_LEXER;
	    ZRexp__sequence ();
	    switch (CURRENT_TERMINAL) {
	      case 20:
		break;
	      case 130:
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
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    PTR_TDF ZId;
	    int ZIe;

	    ADVANCE_LEXER;
	    {

    query_t = lex_offset__query;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = query_t;
    SET_TDF((ZId),&(ZIa));
	    }
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId),&(ZIb));
	    }
	    read_ntest ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc))
	    }
	    read_exp ();
	    ZRlabdest__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    switch((ZIe)) {
	case lex_query:
	    o_integer_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_float__query:
	    o_floating_test({}, o_impossible, append_TDF(&(ZIb),1),
	   		append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_ptr__query:
	    o_pointer_test( {}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_proc__query:
	    o_proc_test( {}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	case lex_offset__query:
	    o_offset_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	default: fail("Don't understand test");
    }
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 78:
	{
	    ADVANCE_LEXER;
	    read_exp ();
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZR646 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 79:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;

	    ADVANCE_LEXER;
	    {

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
	    }
	    read_variety ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 30:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRunary__exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    o_change_variety(o_wrap, append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
	    }
	}
	break;
      case 81:
	{
	    ADVANCE_LEXER;
	    ZRproc__def__body ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 82:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    PTR_TDF ZId;
	    int ZIe;

	    ADVANCE_LEXER;
	    {

    query_t = lex_proc__query;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = query_t;
    SET_TDF((ZId),&(ZIa));
	    }
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId),&(ZIb));
	    }
	    read_ntest ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc))
	    }
	    read_exp ();
	    ZRlabdest__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    switch((ZIe)) {
	case lex_query:
	    o_integer_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_float__query:
	    o_floating_test({}, o_impossible, append_TDF(&(ZIb),1),
	   		append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_ptr__query:
	    o_pointer_test( {}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_proc__query:
	    o_proc_test( {}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	case lex_offset__query:
	    o_offset_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	default: fail("Don't understand test");
    }
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 84:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    PTR_TDF ZId;
	    int ZIe;

	    ADVANCE_LEXER;
	    {

    query_t = lex_ptr__query;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = query_t;
    SET_TDF((ZId),&(ZIa));
	    }
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId),&(ZIb));
	    }
	    read_ntest ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc))
	    }
	    read_exp ();
	    ZRlabdest__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    switch((ZIe)) {
	case lex_query:
	    o_integer_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_float__query:
	    o_floating_test({}, o_impossible, append_TDF(&(ZIb),1),
	   		append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_ptr__query:
	    o_pointer_test( {}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_proc__query:
	    o_proc_test( {}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	case lex_offset__query:
	    o_offset_test({}, append_TDF(&(ZIb),1), append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1)
	   		);
	    break;
	default: fail("Don't understand test");
    }
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 86:
	{
	    ADVANCE_LEXER;
	    ZR648 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 88:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    PTR_TDF ZId;
	    PTR_Labdec ZIe;
	    int ZIf;

	    ADVANCE_LEXER;
	    {

    /* (ZIb), (ZIc), (ZIf) uninitialised */
    (ZIe) = labdecs;
    SET_TDF((ZId), &(ZIa));
	    }
	    ZRrepeat__starter__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIf) = defaultlab;
    defaultlab = -1;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 76:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRlabset__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIc) = optlab;
    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
	    }
	    ZRexp__sequence ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    o_repeat(append_TDF(&(ZIc),1), append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
    tidy_labels((ZIe));
    defaultlab = (ZIf);
	    }
	    switch (CURRENT_TERMINAL) {
	      case 20:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 99:
	{
	    TDF ZIa;
	    TDF ZIb;

	    ADVANCE_LEXER;
	    ZR633 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_variety ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 102:
	{
	    TDF ZIa;
	    PTR_TDF ZIb;

	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    SET_TDF((ZIb), &(ZIa));
	    }
	    read_shape ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIb));
    o_offset_pad(o_alignment(append_TDF(&(ZIa), 0)),
		 o_shape_offset(append_TDF(&(ZIa), 1)));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 103:
	{
	    ADVANCE_LEXER;
	    ZR647 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 22: case 55:
	{
	    TDF ZIa;
	    TDF ZIb;

	    ZRinteger ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    o_make_signed_nat(out_tdfbool(0), out_tdfint32(intvalue));
	    }
	    {

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_variety ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 54: case 109: case 110: case 111:
	{
	    read_tag ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    TDF tg;
    tg = *current_TDF;
    INIT_TDF(current_TDF);
    o_obtain_tag(append_TDF(&tg,1));
	    }
	    ZR646 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 61: case 124:
	{
	    PTR_Tagdec ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    TDF ZId;
	    PTR_TDF ZIe;
	    Name ZIf;
	    int ZIg;

	    {

    (ZIa) = localdecs;
	    }
	    ZRtag__intro ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIg) = localdecs->isvar;
    (ZIb) = intro_acc;
    (ZIc) = intro_init;
    (ZIf) = localdecs->idname.name;
    SET_TDF((ZIe), &(ZId));
	    }
	    ZRclosed__exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIe));
    if ((ZIg)) {
	o_variable( if((ZIb).no!=0) { OPTION(append_TDF(&(ZIb),1)); },
		    make_tag(&(ZIf)), append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1));
    } else {
	o_identify( if((ZIb).no!=0) { OPTION(append_TDF(&(ZIb),1)); },
		    make_tag(&(ZIf)), append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1));
    }
	    }
	    {

    localdecs = (ZIa);
	    }
	}
	break;
      case 85: case 104: case 105: case 107:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;

	    {

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
	    }
	    read_string ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_variety ();
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    RESET_TDF((ZIc));
    o_make_nof_int(append_TDF(&(ZIb), 1), append_TDF(&(ZIa), 1););
	    }
	}
	break;
      case 44:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    TDF ZId;
	    PTR_TDF ZIe;
	    int ZIf;
	    unsigned_long ZIg;

	    {

    /* (ZIc), (ZId) uninitialised */
    (ZIf) = 0;
    (ZIg) = UL(radix);
    SET_TDF((ZIe), &(ZIa));
    out_tdfstring_bytes(fformat(lex_v.val.name,lnum), 8, UI(lnum));
    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIb));
	    }
	    ADVANCE_LEXER;
	    ZRexponent__opt ();
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIc));
	    }
	    read_floating_variety ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZId));
	    }
	    ZRrounding__mode__opt ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIe));
    o_make_floating(append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1),
		    if ((ZIf)) { o_true; } else { o_false; },
		    o_make_string(append_TDF(&(ZIa), 1)),
		    o_make_nat(out_tdfint32((ZIg))),
		    append_TDF(&(ZIb), 1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 41: case 98:
	{
	    int ZI642;

	    {

    (ZI642) = lex_v.val.v;
	    }
	    ZR643 (&ZI642);
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 43: case 100:
	{
	    PTR_Tokdec ZI640;

	    {

    (ZI640) = lex_v.val.tokname;
    (ZI640)->isused = 1;
	    }
	    ZR641 (&ZI640);
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 62:
	{
	    TDF ZIa;
	    TDF ZIb;

	    {

    o_make_signed_nat(out_tdfbool(0), out_tdfint32(cLINE));
	    }
	    ADVANCE_LEXER;
	    {

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_variety ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 10:
	{
	    TDF ZI637;
	    PTR_TDF ZI638;
	    TDF ZIa;
	    TDF ZIb;

	    {

    SET_TDF((ZI638), &(ZI637));
    if (strcmp(lex_v.val.name, "+")) fail("Only + or - on NATs");
	    }
	    ADVANCE_LEXER;
	    ZRnat__not__int ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZI638));
    o_snat_from_nat(o_false, append_TDF(&(ZI637),1));
	    }
	    {

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_variety ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRtagshacc__list PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
  ZL2_tagshacc__list:;
    {
	ZRtagshacc ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    current_TDF->no++;
	}
	{
	    switch (CURRENT_TERMINAL) {
	      case 25:
		{
		    ADVANCE_LEXER;
		    goto ZL2_tagshacc__list;
		}
		/*UNREACHED*/
	      default:
		break;
	    }
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRshapetok PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 32:
	{
	    ADVANCE_LEXER;
	    {

    * g_shtokname = *(tokfordoublesh());
	    }
	}
	break;
      case 46:
	{
	    ADVANCE_LEXER;
	    {

    * g_shtokname = *(tokforfloatsh());
	    }
	}
	break;
      case 21: case 56: case 64: case 97: case 101:
      case 121:
	{
	    ZRvariety__sign ();
	    ZR675 ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 83: case 94: case 95: case 96:
	{
	    PTR_TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;
	    int ZId;

	    {

    (ZIa) = current_TDF;
    (ZId) = current_Unit;
    select_tokdef_unit();
    * g_shtokname = next_name(tok_ent);
    SET_TDF((ZIc), &(ZIb));
	    }
	    ZRnonst__shape ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    o_make_tokdef(out_tdfint32(UL(g_shtokname->unit_name)), {},
		  o_token_def(o_shape, {}, append_TDF(&(ZIb), 1)));
    INC_LIST;
    current_Unit = (ZId);
    RESET_TDF((ZIa));
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRalignment__list PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	read_alignment ();
	ZR622 ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_error_treatment PROTO_Z ()
{
  ZL2_error__treatment:;
    switch (CURRENT_TERMINAL) {
      case 39:
	{
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 24:
		    {
			ADVANCE_LEXER;
			goto ZL2_error__treatment;
		    }
		    /*UNREACHED*/
		  case 86:
		    {
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			{

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
			}
			ADVANCE_LEXER;
			switch (CURRENT_TERMINAL) {
			  case 78:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  case 130:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
			}
			read_error_treatment ();
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  case 130:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
			}
			read_error_treatment ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    o_errt_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		append_TDF(&(ZIc),1));
			}
			switch (CURRENT_TERMINAL) {
			  case 29:
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
	    }
	}
	break;
      case 79:
	{
	    TDF ZIa;
	    PTR_TDF ZIb;

	    ADVANCE_LEXER;
	    {

    SET_TDF((ZIb), &(ZIa));
	    }
	    read_error_code_list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIb));
    o_trap({append_TDF(&(ZIa),1); current_TDF->no = (ZIa).no; });
	    }
	    switch (CURRENT_TERMINAL) {
	      case 30:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 54: case 59: case 60:
	{
	    TDF ZIa;
	    PTR_TDF ZIb;

	    {

    SET_TDF((ZIb), &(ZIa));
	    }
	    read_label ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIb));
    o_error_jump(append_TDF(&(ZIa),1));
	    }
	}
	break;
      case 38:
	{
	    int ZIa;

	    {

    (ZIa) = lex_v.val.v;
	    }
	    ADVANCE_LEXER;
	    {

    (constructs[(ZIa)].f)();
	    }
	}
	break;
      case 40:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZRcallee PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 33:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;

	    ADVANCE_LEXER;
	    {

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 25:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIc));
    o_make_dynamic_callees(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 92:
	{
	    ADVANCE_LEXER;
	    {

    o_same_callees;
	    }
	}
	break;
      default:
	{
	    TDF ZIa;
	    PTR_TDF ZIb;

	    {

    SET_TDF((ZIb), &(ZIa));
	    }
	    read_exp_list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIb));
    o_make_callee_list( { append_TDF(&(ZIa),1); current_TDF->no = (ZIa).no;} );
	    }
	}
	break;
      case 130:
	return;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_al_tag PROTO_Z ()
{
  ZL2_al__tag:;
    switch (CURRENT_TERMINAL) {
      case 4:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 24:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    goto ZL2_al__tag;
	}
	/*UNREACHED*/
      case 54:
	{
	    {

    char * n =lex_v.val.name;
    Al_tagdec * x = find_al_tag(n);
    if (x==(Al_tagdec*)0) {
	x= MALLOC(Al_tagdec);
	x->isdeffed =0; x->iskept=0;
	NEW_IDNAME(x->idname, n, al_tag_ent);
	x->next = al_tagdecs;
	al_tagdecs = x;
    }
    x->isused =1;
    make_al_tag(&x->idname.name);
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 5:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

void
read_exp_list PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	{

    current_TDF->no=0;
	}
	ZR656 ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZRelement PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 6:
	{
	    ZRal__tag__def ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 81:
	{
	    ZRproc__def ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 108:
	{
	    ZRstruct__def ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 27: case 53: case 125:
	{
	    ZRtag__dec ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 26: case 61: case 106: case 124:
	{
	    ZRtag__def ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 113:
	{
	    ZRtok__dec ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 114:
	{
	    ZRtok__def ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR622 PROTO_Z ()
{
  ZL2_622:;
    switch (CURRENT_TERMINAL) {
      case 25:
	{
	    TDF ZIa;
	    PTR_TDF ZIb;

	    {

    (ZIb) = current_TDF;
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
	    }
	    ADVANCE_LEXER;
	    read_alignment ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    TDF second;
    second = *current_TDF;
    INIT_TDF((ZIb));
    RESET_TDF((ZIb));
    o_unite_alignments(append_TDF(&(ZIa),1), append_TDF(&second,1));
	    }
	    goto ZL2_622;
	}
	/*UNREACHED*/
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRtok__def__body PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	PTR_Tokdec ZIa;

	{

    (ZIa) = g_tokformals;
	}
	switch (CURRENT_TERMINAL) {
	  case 79:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRtok__formal__list__opt ();
	switch (CURRENT_TERMINAL) {
	  case 30:
	    break;
	  case 130:
	    RESTORE_LEXER;
	    goto ZL1;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	ZRfull__sortname ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    Tokdec * old_tokdecs = tokdecs;
    Tokdec * tokformals = g_tokformals;
    TDF * hold = current_TDF;
    Tokpar * tp = (Tokpar*)0;
    Sort sn;
    Tokdec * tfrev = (Tokdec*)0;
    while (g_tokformals != (Tokdec*)0) { /* the wrong way round!! */
	Tokdec * x = MALLOC(Tokdec);
	*x = *g_tokformals;
	x->next = tfrev;
	tfrev = x;
	g_tokformals = g_tokformals->next;
    }
    sn = g_sname;
    current_TDF = &g_tok_defn;
    INIT_TDF(current_TDF);
    o_token_def( out_sort(&sn),
	{
	    while(tfrev != (Tokdec*)0) {
		Tokdec * x = tfrev->next;
		LIST_ELEM(
		    o_make_tokformals(
			out_sort(&tfrev->sort.ressort),
			out_tdfint32(LOCNAME(tfrev->idname))));
		tfrev->isparam = 1;
		tfrev->next = tokdecs;
		tokdecs = tfrev;
		tfrev = x;
	    }
	},
	analyse_sort(sn.sort));
    g_toksort.ressort = sn;
    while (tokformals != (Tokdec*)0) {
	Tokpar * p = MALLOC(Tokpar);
	p->par = tokformals->sort.ressort;
	p->next = tp;
	tokformals = tokformals->next;
	tp = p;
    }
    g_toksort.pars = tp;
    RESET_TDF(hold);
    tokdecs = old_tokdecs;
    g_tokformals = (ZIa);
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRinteger PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 55:
	{
	    {

    intvalue = UL(stoi(lex_v.val.name, lnum));
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 22:
	{
	    {

    intvalue = UL(lex_v.val.v);
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_transfer_mode PROTO_Z ()
{
  ZL2_transfer__mode:;
    switch (CURRENT_TERMINAL) {
      case 119:
	{
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 24:
		    {
			ADVANCE_LEXER;
			goto ZL2_transfer__mode;
		    }
		    /*UNREACHED*/
		  case 86:
		    {
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			ADVANCE_LEXER;
			{

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
			}
			switch (CURRENT_TERMINAL) {
			  case 78:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
			}
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_transfer_mode ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
			}
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_transfer_mode ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    o_transfer_mode_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
			 append_TDF(&(ZIc),1));
			}
			switch (CURRENT_TERMINAL) {
			  case 29:
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
	    }
	}
	break;
      case 118:
	{
	    int ZIa;

	    {

    (ZIa) = lex_v.val.v;
	    }
	    ADVANCE_LEXER;
	    {

    (constructs[(ZIa)].f)();
	    }
	}
	break;
      case 120:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

void
read_rounding_mode PROTO_Z ()
{
  ZL2_rounding__mode:;
    switch (CURRENT_TERMINAL) {
      case 90:
	{
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 24:
		    {
			ADVANCE_LEXER;
			goto ZL2_rounding__mode;
		    }
		    /*UNREACHED*/
		  case 86:
		    {
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			ADVANCE_LEXER;
			{

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
			}
			switch (CURRENT_TERMINAL) {
			  case 78:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  case 130:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
			}
			read_rounding_mode ();
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  case 130:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
			}
			read_rounding_mode ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    o_rounding_mode_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
			 append_TDF(&(ZIc),1));
			}
			switch (CURRENT_TERMINAL) {
			  case 29:
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
	    }
	}
	break;
      case 89:
	{
	    int ZIa;

	    {

    (ZIa) = lex_v.val.v;
	    }
	    ADVANCE_LEXER;
	    {

    (constructs[(ZIa)].f)();
	    }
	}
	break;
      case 91:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZR625 PROTO_Z ()
{
  ZL2_625:;
    switch (CURRENT_TERMINAL) {
      case 25:
	{
	    ADVANCE_LEXER;
	    read_error_code ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    current_TDF->no ++;
	    }
	    goto ZL2_625;
	}
	/*UNREACHED*/
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR626 PROTO_Z ()
{
  ZL2_626:;
    switch (CURRENT_TERMINAL) {
      case 25:
	{
	    {

    current_TDF->no++;
	    }
	    ADVANCE_LEXER;
	    ZRotagexp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    } else {
		goto ZL2_626;
	    }
	}
	/*UNREACHED*/
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_access PROTO_Z ()
{
  ZL2_access:;
    switch (CURRENT_TERMINAL) {
      case 1:
	{
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 24:
		    {
			ADVANCE_LEXER;
			goto ZL2_access;
		    }
		    /*UNREACHED*/
		  case 86:
		    {
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			PTR_TDF ZId;

			ADVANCE_LEXER;
			{

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
			}
			switch (CURRENT_TERMINAL) {
			  case 78:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
			}
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			read_access ();
			switch (CURRENT_TERMINAL) {
			  case 25:
			    break;
			  case 130:
			    RESTORE_LEXER;
			    goto ZL1;
			  default:
			    goto ZL1;
			}
			ADVANCE_LEXER;
			{

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
			}
			read_access ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZId));
    o_access_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		  append_TDF(&(ZIc),1));
			}
			switch (CURRENT_TERMINAL) {
			  case 29:
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
	    }
	}
	break;
      case 0:
	{
	    int ZIa;

	    {

    (ZIa) = lex_v.val.v;
	    }
	    ADVANCE_LEXER;
	    {

    if (strcmp(constructs[(ZIa)].name, "visible")==0) { g_has_vis = 1; }
	    }
	    {

    (constructs[(ZIa)].f)();
	    }
	}
	break;
      case 2:
	{
	    PTR_Tokdec ZIa;

	    {

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
	    }
	    ADVANCE_LEXER;
	    {

    expand_tok((ZIa), &(ZIa)->sort);
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZR627 PROTO_Z ()
{
  ZL2_627:;
    switch (CURRENT_TERMINAL) {
      case 25:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;

	    {

    (ZIc) = current_TDF;
    (ZIa) = *current_TDF;
    INIT_TDF(&(ZIb));
    RESET_TDF(&(ZIb));
	    }
	    ADVANCE_LEXER;
	    read_access ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    INIT_TDF((ZIc));
    RESET_TDF((ZIc));
    o_add_accesses(append_TDF(&(ZIa),1), append_TDF(&(ZIb), 1));
    current_TDF->no = 1;
	    }
	    goto ZL2_627;
	}
	/*UNREACHED*/
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR628 PROTO_Z ()
{
  ZL2_628:;
    switch (CURRENT_TERMINAL) {
      case 93:
	{
	    TDF ZIa;
	    PTR_TDF ZIb;

	    {

    SET_TDF((ZIb), &(ZIa));
	    }
	    ADVANCE_LEXER;
	    {
		switch (CURRENT_TERMINAL) {
		  case 10: case 19: case 22: case 28: case 41:
		  case 42: case 43: case 44: case 45: case 52:
		  case 54: case 55: case 58: case 61: case 62:
		  case 68: case 76: case 77: case 78: case 79:
		  case 81: case 82: case 84: case 85: case 86:
		  case 88: case 98: case 99: case 100: case 102:
		  case 103: case 104: case 105: case 107: case 109:
		  case 110: case 111: case 124:
		    {
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
			    RESTORE_LEXER;
			    goto ZL1;
			}
			{

    RESET_TDF((ZIb));
    if (lex_v.t == lex_semi) {
	current_TDF->no +=1;
	append_TDF(&(ZIa),1);
    } else {
	TDF stats;
	stats = *current_TDF;
	INIT_TDF(current_TDF);
	o_sequence(
	    { append_TDF(&stats,1); current_TDF->no = stats.no; },
	    append_TDF(&(ZIa),1));
	/* cheats LIST in o_sequence */
    }
			}
			goto ZL2_628;
		    }
		    /*UNREACHED*/
		  default:
		    {
			{

    o_make_top;
			}
			{

    RESET_TDF((ZIb));
    if (lex_v.t == lex_semi) {
	current_TDF->no +=1;
	append_TDF(&(ZIa),1);
    } else {
	TDF stats;
	stats = *current_TDF;
	INIT_TDF(current_TDF);
	o_sequence(
	    { append_TDF(&stats,1); current_TDF->no = stats.no; },
	    append_TDF(&(ZIa),1));
	/* cheats LIST in o_sequence */
    }
			}
			goto ZL2_628;
		    }
		    /*UNREACHED*/
		}
	    }
	}
	/*UNREACHED*/
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR629 PROTO_Z ()
{
  ZL2_629:;
    switch (CURRENT_TERMINAL) {
      case 25:
	{
	    PTR_Tokdec ZIa;

	    ADVANCE_LEXER;
	    {

    char * n = lex_v.val.name;
    (ZIa) = find_tok(n);
    if ((ZIa)!=(Tokdec*)0) fail("Token parameter name %s must be unique", n);
    (ZIa) = MALLOC(Tokdec); NEW_IDNAME((ZIa)->idname, n, tok_ent);
    (ZIa)->isdeffed = 1; (ZIa)->isused = 0; (ZIa)->iskept=0;
    (ZIa)->next = (Tokdec*)0;
	    }
	    switch (CURRENT_TERMINAL) {
	      case 54:
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
	    ZRfull__sortname ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    (ZIa)->sort.ressort = g_sname;
    (ZIa)->sort.pars = (Tokpar*)0; /* no pars in formal pars */
    (ZIa)->next = g_tokformals;
    g_tokformals = (ZIa);
	    }
	    goto ZL2_629;
	}
	/*UNREACHED*/
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR630 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 35:
	{
	    ADVANCE_LEXER;
	    {

    int i;
    for(i=0; i<NO_OF_ENTITIES; i++) {
	INIT_TDF(lk_externs+i);
    }
	    }
	    {

    CONT_STREAM(&units[tld2_unit].tdf, out_tdfint32(UL(1)));
    if(line_no_tok != -1) {
	current_TDF = lk_externs+tok_ent;
	o_make_linkextern(
	    out_tdfint32(UL(line_no_tok)),
		o_string_extern(
		    { out_tdfident_bytes("~exp_to_source"); }));
	current_TDF->no++;
	CONT_STREAM(&units[tld2_unit].tdf, out_tdfint32(UL(3)));
    }
    {
	Tokdec * k = tokdecs;
	while (k != (Tokdec*)0) {
	    if (!k->isdeffed || k->iskept) {
		int capname = capsule_name(&k->idname.name, tok_ent);
		char * n = k->idname.id;
		current_TDF = lk_externs+tok_ent;
		o_make_linkextern(out_tdfint32(UL(capname)),
		    o_string_extern({ out_tdfident_bytes(n); }));
		current_TDF->no++;
		CONT_STREAM(&units[tld2_unit].tdf,
		    { int i = k->isused + 2 + 4*k->isdeffed;
		      out_tdfint32(UL(i)); });
	    }
	    k = k->next;
	}
    }
    {
	Tagdec * k = tagdecs;
	while (k != (Tagdec*)0) {
	    if (!k->isdeffed || k->iskept) {
		int capname = capsule_name(&k->idname.name, tag_ent);
		char * n = k->idname.id;
		current_TDF = lk_externs+tag_ent;
		o_make_linkextern(out_tdfint32(UL(capname)),
		    o_string_extern({ out_tdfident_bytes(n); }));
		current_TDF->no++;
		CONT_STREAM(&units[tld2_unit].tdf,
		    { int i = k->isused + 2 + ((k->iscommon)?8:(4*k->isdeffed));
		      out_tdfint32(UL(i)); });
	    }
	    k = k->next;
	}
    }
    {
	Al_tagdec * k = al_tagdecs;
	while (k != (Al_tagdec*)0) {
	    if (!k->isdeffed || k->iskept) {
		int capname = capsule_name(&k->idname.name, al_tag_ent);
		char * n = k->idname.id;
		current_TDF = lk_externs+al_tag_ent;
		o_make_linkextern(out_tdfint32(UL(capname)),
		    o_string_extern({ out_tdfident_bytes(n); }));
		current_TDF->no++;
		CONT_STREAM(&units[tld2_unit].tdf,
		    { int i = k->isused + 2 + 4*k->isdeffed;
		      out_tdfint32(UL(i)); });
	    }
	    k = k->next;
	}
    }
    {
	int i;
	TDF caps;
	add_extra_toks();
	INIT_TDF(&caps);
	RESET_TDF(&caps);
	if (do_pp) success();
	if (HAS_MAGIC) {
	    out_basic_int(UL('T'), UI(8));
	    out_basic_int(UL('D'), UI(8));
	    out_basic_int(UL('F'), UI(8));
	    out_basic_int(UL('C'), UI(8));
	    out_tdfint32(MAJOR_NO);
	    out_tdfint32(MINOR_NO);
	    byte_align();
	}
	o_make_capsule(
	    {
		for(i=0; i<NO_OF_UNITS; i++) {
		    if(units[i].present) {
			char* n;
			n = unit_names[i];
			LIST_ELEM({ out_tdfident_bytes(n); });
		    }
		}
	    },
	    {
		for(i=0; i<NO_OF_ENTITIES; i++) {
		    char* n;
		    n = ent_names[i];
		    LIST_ELEM(
			o_make_capsule_link(
			    { out_tdfident_bytes(n);},
			    out_tdfint32(UL(capsule_names[i]))))
		}
	    },
	    {
		for(i=0; i<NO_OF_ENTITIES; i++) {
		    TDF * lks = lk_externs+i;
		    LIST_ELEM(
			o_make_extern_link(
			    { append_TDF(lks,1); current_TDF->no = lks->no; });
		    )
		}
	    },
	    {
		for(i=0; i<NO_OF_UNITS; i++) {
		    if(units[i].present) {
			LIST_ELEM(
			    o_make_group(LIST_ELEM(make_unit(i))););
		    }
		}
	    }
	);
	make_tdf_file(&caps, out_file);
    }
	    }
	}
	break;
      case 57:
	{
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    int i;
    for(i=0; i<NO_OF_ENTITIES; i++) {
	INIT_TDF(lk_externs+i);
    }
	    }
	    ZRkeep__list__opt ();
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      case 130:
		RESTORE_LEXER;
		goto ZL1;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    switch (CURRENT_TERMINAL) {
	      case 35:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    {

    CONT_STREAM(&units[tld2_unit].tdf, out_tdfint32(UL(1)));
    if(line_no_tok != -1) {
	current_TDF = lk_externs+tok_ent;
	o_make_linkextern(
	    out_tdfint32(UL(line_no_tok)),
		o_string_extern(
		    { out_tdfident_bytes("~exp_to_source"); }));
	current_TDF->no++;
	CONT_STREAM(&units[tld2_unit].tdf, out_tdfint32(UL(3)));
    }
    {
	Tokdec * k = tokdecs;
	while (k != (Tokdec*)0) {
	    if (!k->isdeffed || k->iskept) {
		int capname = capsule_name(&k->idname.name, tok_ent);
		char * n = k->idname.id;
		current_TDF = lk_externs+tok_ent;
		o_make_linkextern(out_tdfint32(UL(capname)),
		    o_string_extern({ out_tdfident_bytes(n); }));
		current_TDF->no++;
		CONT_STREAM(&units[tld2_unit].tdf,
		    { int i = k->isused + 2 + 4*k->isdeffed;
		      out_tdfint32(UL(i)); });
	    }
	    k = k->next;
	}
    }
    {
	Tagdec * k = tagdecs;
	while (k != (Tagdec*)0) {
	    if (!k->isdeffed || k->iskept) {
		int capname = capsule_name(&k->idname.name, tag_ent);
		char * n = k->idname.id;
		current_TDF = lk_externs+tag_ent;
		o_make_linkextern(out_tdfint32(UL(capname)),
		    o_string_extern({ out_tdfident_bytes(n); }));
		current_TDF->no++;
		CONT_STREAM(&units[tld2_unit].tdf,
		    { int i = k->isused + 2 + ((k->iscommon)?8:(4*k->isdeffed));
		      out_tdfint32(UL(i)); });
	    }
	    k = k->next;
	}
    }
    {
	Al_tagdec * k = al_tagdecs;
	while (k != (Al_tagdec*)0) {
	    if (!k->isdeffed || k->iskept) {
		int capname = capsule_name(&k->idname.name, al_tag_ent);
		char * n = k->idname.id;
		current_TDF = lk_externs+al_tag_ent;
		o_make_linkextern(out_tdfint32(UL(capname)),
		    o_string_extern({ out_tdfident_bytes(n); }));
		current_TDF->no++;
		CONT_STREAM(&units[tld2_unit].tdf,
		    { int i = k->isused + 2 + 4*k->isdeffed;
		      out_tdfint32(UL(i)); });
	    }
	    k = k->next;
	}
    }
    {
	int i;
	TDF caps;
	add_extra_toks();
	INIT_TDF(&caps);
	RESET_TDF(&caps);
	if (do_pp) success();
	if (HAS_MAGIC) {
	    out_basic_int(UL('T'), UI(8));
	    out_basic_int(UL('D'), UI(8));
	    out_basic_int(UL('F'), UI(8));
	    out_basic_int(UL('C'), UI(8));
	    out_tdfint32(MAJOR_NO);
	    out_tdfint32(MINOR_NO);
	    byte_align();
	}
	o_make_capsule(
	    {
		for(i=0; i<NO_OF_UNITS; i++) {
		    if(units[i].present) {
			char* n;
			n = unit_names[i];
			LIST_ELEM({ out_tdfident_bytes(n); });
		    }
		}
	    },
	    {
		for(i=0; i<NO_OF_ENTITIES; i++) {
		    char* n;
		    n = ent_names[i];
		    LIST_ELEM(
			o_make_capsule_link(
			    { out_tdfident_bytes(n);},
			    out_tdfint32(UL(capsule_names[i]))))
		}
	    },
	    {
		for(i=0; i<NO_OF_ENTITIES; i++) {
		    TDF * lks = lk_externs+i;
		    LIST_ELEM(
			o_make_extern_link(
			    { append_TDF(lks,1); current_TDF->no = lks->no; });
		    )
		}
	    },
	    {
		for(i=0; i<NO_OF_UNITS; i++) {
		    if(units[i].present) {
			LIST_ELEM(
			    o_make_group(LIST_ELEM(make_unit(i))););
		    }
		}
	    }
	);
	make_tdf_file(&caps, out_file);
    }
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR632 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 3: case 10: case 36: case 63: case 68:
      case 103:
	{
	    TDF ZIa;
	    TDF ZIb;
	    PTR_TDF ZIc;
	    PTR_char ZId;

	    {

    (ZId) = lex_v.val.name;
    (ZIa) = *current_TDF;
    SET_TDF((ZIc), &(ZIb));
	    }
	    ZR672 (&ZIa, &ZIb, &ZIc, &ZId);
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRkeep__list__opt PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 2: case 5: case 9: case 15: case 18:
      case 40: case 43: case 49: case 54: case 60:
      case 71: case 75: case 91: case 96: case 100:
      case 111: case 120: case 128:
	{
	    ZRkeep__list ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 130:
	return;
      default:
	break;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZR633 PROTO_Z ()
{
  ZL2_633:;
    switch (CURRENT_TERMINAL) {
      case 24:
	{
	    ADVANCE_LEXER;
	    ZRsigned__nat__body ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	}
	break;
      case 86:
	{
	    TDF ZIa;
	    TDF ZIb;
	    TDF ZIc;
	    PTR_TDF ZId;

	    ADVANCE_LEXER;
	    {

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 78:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    read_exp ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 25:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRsigned__nat__body ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 25:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	    ZRsigned__nat__body ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZId));
    o_signed_nat_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		      append_TDF(&(ZIc),1));
	    }
	    switch (CURRENT_TERMINAL) {
	      case 29:
		break;
	      default:
		goto ZL1;
	    }
	    ADVANCE_LEXER;
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRal__tag__def PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	PTR_Al_tagdec ZIa;
	TDF ZIb;
	PTR_TDF ZIc;
	int ZId;

	switch (CURRENT_TERMINAL) {
	  case 6:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	{

    char * n =lex_v.val.name;
    (ZIa) = find_al_tag(n);
    SELECT_UNIT(al_tagdef_unit);
    if ((ZIa)==(Al_tagdec*)0) {
	(ZIa)= MALLOC(Al_tagdec); (ZIa)->isdeffed =0; (ZIa)->iskept=0; (ZIa)->isused=0;
	NEW_IDNAME((ZIa)->idname, n, al_tag_ent);
	(ZIa)->next = al_tagdecs; al_tagdecs = (ZIa);
	(ZId) = 0;
    }
    else (ZId) = 1;
    if ((ZIa)->isdeffed) { fail("Al_tag %s defined twice", n); }
    (ZIa)->isdeffed = 1;
    SET_TDF((ZIc), &(ZIb));
	}
	switch (CURRENT_TERMINAL) {
	  case 54:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	switch (CURRENT_TERMINAL) {
	  case 36:
	    break;
	  default:
	    goto ZL1;
	}
	ADVANCE_LEXER;
	read_alignment ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
	{

    RESET_TDF((ZIc));
    o_make_al_tagdef( if ((ZId)) {
			  out_tdfint32(UL(non_local(&(ZIa)->idname.name,al_tag_ent)));
			  } else {
			      out_tdfint32(LOCNAME((ZIa)->idname));
			  },
			  append_TDF(&(ZIb), 1)
			);
    INC_LIST;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

static void
ZRotagexp PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	TDF ZIa;
	PTR_TDF ZIb;

	{

    SET_TDF((ZIb), &(ZIa));
	}
	read_exp ();
	ZR655 (&ZIa, &ZIb);
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

void
read_program PROTO_Z ()
{
    if ((CURRENT_TERMINAL) == 130) {
	return;
    }
    {
	ZRelement__list__opt ();
	ZR630 ();
	if ((CURRENT_TERMINAL) == 130) {
	    RESTORE_LEXER;
	    goto ZL1;
	}
    }
    return;
  ZL1:;
    {
	{

    fail("Syntax error");
	}
    }
}

static void
ZR634 PROTO_Z ()
{
    switch (CURRENT_TERMINAL) {
      case 22: case 55:
	{
	    ZRinteger ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    o_make_signed_nat(out_tdfbool(1), out_tdfint32(intvalue));
	    }
	}
	break;
      case 69: case 70: case 71:
	{
	    TDF ZIa;
	    PTR_TDF ZIb;

	    {

    SET_TDF((ZIb), &(ZIa));
	    }
	    ZRnat__not__int ();
	    if ((CURRENT_TERMINAL) == 130) {
		RESTORE_LEXER;
		goto ZL1;
	    }
	    {

    RESET_TDF((ZIb));
    o_snat_from_nat(o_true, append_TDF(&(ZIa),1));
	    }
	}
	break;
      case 130:
	return;
      default:
	goto ZL1;
    }
    return;
  ZL1:;
    SAVE_LEXER (130);
    return;
}

/* BEGINNING OF TRAILER */



/* END OF FILE */
