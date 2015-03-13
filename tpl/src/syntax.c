/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#line 174 "syntax.act"


/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>

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

#include <shared/xalloc.h>

static int saved = 0;
#define CURRENT_TERMINAL	(unsigned)lex_v.t
#define ADVANCE_LEXER		lex_v = reader()
#define SAVE_LEXER(e)		((saved = lex_v.t), (lex_v.t = (e)))
#define RESTORE_LEXER		(lex_v.t = saved)

typedef Al_tagdec *PTR_Al_tagdec;
typedef Labdec *PTR_Labdec;
typedef char *PTR_char;
typedef Tagdec *PTR_Tagdec;
typedef TDF *PTR_TDF;
typedef Tokdec *PTR_Tokdec;
typedef Tokpar *PTR_Tokpar;
typedef unsigned long unsigned_long;


static Tokpar *g_tokpars;
static Sort g_sname;
static TDF g_tok_defn;
static TokSort g_toksort;
int search_for_toks = 1;
static Tokdec *g_tokformals;
static int g_lastfield;
static TDF g_shape;
static TDF g_lastshape;

static Name *g_shtokname;
static int g_has_vis = 0;
static Bool issigned;
static Labdec *g_labdec;
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
static Tagdec *g_app_tags;

static void
do_procprops(int i)
{
    switch (i) {
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

static void
success(void)
{
    IGNORE printf("Reached end\n");
    print_res();
}

static int HAS_MAGIC = 1;
unsigned long MAJOR_NO = major_version;
unsigned long MINOR_NO = minor_version;


#line 132 "syntax.c"

/* BEGINNING OF FUNCTION DECLARATIONS */

extern void read_label(void);
static void ZR641(PTR_Tokdec *);
static void ZRfull__sortname(void);
static void ZR643(int *);
static void ZR645(void);
extern void read_variety(void);
static void ZR646(void);
static void ZRtok__formal__list__opt(void);
static void ZR647(void);
static void ZR648(void);
static void ZR650(void);
static void ZRsortname__list(void);
static void ZRsignature__opt(void);
static void ZRexp__sequence(void);
static void ZRrange(void);
static void ZR654(void);
static void ZR655(TDF *, PTR_TDF *);
static void ZRrange__label__list(void);
static void ZR656(void);
extern void read_shape(void);
static void ZR657(void);
static void ZRaccess__list(void);
static void ZR660(TDF *, TDF *, TDF *, TDF *);
static void ZRtagshacc__list__opt(void);
static void ZR661(TDF *, PTR_TDF *);
static void ZRlabdest__opt(void);
static void ZR662(PTR_TDF *);
static void ZRalignment__list__opt(void);
static void ZR663(void);
extern void read_string(void);
static void ZR664(void);
static void ZRotagexp__list(void);
static void ZRvariety__sign(void);
static void ZR668(void);
static void ZR669(TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, int *);
static void ZR670(TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, int *);
extern void read_signed_nat(void);
static void ZR672(TDF *, TDF *, PTR_TDF *, PTR_char *);
extern void read_token(void);
static void ZR673(void);
static void ZRnat__not__int(void);
static void ZRshape__body(void);
static void ZRrepeat__starter__opt(void);
static void ZR674(void);
static void ZRfield__list(void);
static void ZR675(void);
static void ZR676(void);
static void ZR677(TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, PTR_char *, int *);
static void ZRrounding__mode__opt(void);
static void ZR678(TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, PTR_char *, int *);
static void ZRnonst__shape(void);
static void ZR679(TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, PTR_char *, int *);
static void ZRaccess__opt(void);
extern void read_error_code(void);
static void ZRpostlude__opt(void);
static void ZR680(TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, int *);
static void ZRexponent__opt(void);
static void ZR681(TDF *, TDF *, PTR_TDF *, PTR_Tagdec *, int *);
static void ZRclosed__exp(void);
extern void read_bool(void);
static void ZRvarintro__opt(void);
extern void read_ntest(void);
extern void read_bitfield_variety(void);
static void ZRsigned__nat__body(void);
static void ZRlabset__opt(void);
static void ZRkeep__item(void);
static void ZRstruct__def(void);
static void ZRnonst__shape__body(void);
extern void read_tag(void);
static void ZRvariety__opt(void);
extern void read_nat_option(void);
static void ZRsortname__list__opt(void);
extern void read_floating_variety(void);
static void ZRtagshacc(void);
static void ZRelement__list__opt(void);
extern void read_nat(void);
extern void read_alignment(void);
static void ZRvarpar__opt(void);
static void ZRkeep__list(void);
static void ZRproc__def(void);
extern void read_error_code_list(void);
static void ZRcallee__var__opt(void);
static void ZRtag__dec(void);
static void ZRtag__intro(void);
extern void read_exp(void);
static void ZRtag__def(void);
static void ZRotagexp__list__opt(void);
static void ZRtok__formal__list(void);
static void ZRuntidy__opt(void);
static void ZRcaller__var__opt(void);
static void ZRproc__def__body(void);
static void ZRlabelled__list(void);
static void ZRoffset__exp__list(void);
static void ZRbitfield__sign(void);
static void ZRtok__dec(void);
static void ZRexp__comma__list(void);
static void ZRexp__body(void);
static void ZRtok__def(void);
static void ZRunary__exp(void);
static void ZRtagshacc__list(void);
static void ZRshapetok(void);
static void ZRalignment__list(void);
extern void read_error_treatment(void);
static void ZRcallee(void);
extern void read_al_tag(void);
extern void read_exp_list(void);
static void ZRelement(void);
static void ZR622(void);
static void ZRtok__def__body(void);
static void ZRinteger(void);
extern void read_transfer_mode(void);
extern void read_rounding_mode(void);
static void ZR625(void);
static void ZR626(void);
extern void read_access(void);
static void ZR627(void);
static void ZR628(void);
static void ZR629(void);
static void ZR630(void);
static void ZR632(void);
static void ZRkeep__list__opt(void);
static void ZR633(void);
static void ZRal__tag__def(void);
static void ZRotagexp(void);
extern void read_program(void);
static void ZR634(void);

/* BEGINNING OF STATIC VARIABLES */


/* BEGINNING OF FUNCTION DEFINITIONS */

void
read_label(void)
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
			/* BEGINNING OF INLINE: label */
			goto ZL2_label;
			/* END OF INLINE: label */
		}
		UNREACHED;
	case 60:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 298 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 307 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 54:
		{
			/* BEGINNING OF ACTION: label1 */
			{
#line 1415 "syntax.act"

    char * n =lex_v.val.name;
    Labdec * x = find_lab(n);
    if (x== (Labdec*)0) {
	x = xmalloc(sizeof *x);
	x->idname.id = n; x->idname.name.unit_name = next_label();
	x->declared = 0;
	x->next = labdecs; labdecs = x;
    }
    g_labdec = x;
    o_make_label(out_tdfint32(LOCNAME(x->idname)));
#line 328 "syntax.c"
			}
			/* END OF ACTION: label1 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 347 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR641(PTR_Tokdec *ZI640)
{
	switch (CURRENT_TERMINAL) {
	case 43:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((*ZI640), &(*ZI640)->sort);
#line 365 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 100:
		{
			TDF ZIa;
			TDF ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((*ZI640), &(*ZI640)->sort);
#line 381 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
			/* BEGINNING OF ACTION: mint1_dec */
			{
#line 1471 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 391 "syntax.c"
			}
			/* END OF ACTION: mint1_dec */
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
			/* BEGINNING OF ACTION: mint2 */
			{
#line 1477 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
#line 413 "syntax.c"
			}
			/* END OF ACTION: mint2 */
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
ZRfull__sortname(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		/* BEGINNING OF ACTION: sortname1 */
		{
#line 1819 "syntax.act"

    g_sname.sort = lex_v.t;
#line 448 "syntax.c"
		}
		/* END OF ACTION: sortname1 */
		/* BEGINNING OF INLINE: sortname */
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
		/* END OF INLINE: sortname */
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
ZR643(int *ZI642)
{
	switch (CURRENT_TERMINAL) {
	case 41:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(*ZI642)].f)();
#line 578 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 98:
		{
			TDF ZIa;
			TDF ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(*ZI642)].f)();
#line 594 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
			/* BEGINNING OF ACTION: mint1_dec */
			{
#line 1471 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 604 "syntax.c"
			}
			/* END OF ACTION: mint1_dec */
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
			/* BEGINNING OF ACTION: mint2 */
			{
#line 1477 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
#line 626 "syntax.c"
			}
			/* END OF ACTION: mint2 */
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
ZR645(void)
{
	switch (CURRENT_TERMINAL) {
	case 78:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: expneg1_dec */
			{
#line 754 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 664 "syntax.c"
			}
			/* END OF ACTION: expneg1_dec */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expnegate2 */
			{
#line 758 "syntax.act"

    RESET_TDF((ZIb));
    o_negate(o_wrap, append_TDF(&(ZIa),1));
#line 678 "syntax.c"
			}
			/* END OF ACTION: expnegate2 */
			switch (CURRENT_TERMINAL) {
			case 29:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
		}
		break;
	case 22: case 55: case 69: case 70:
	case 71:
		{
			TDF ZIa;
			TDF ZIb;

			ZR634 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: mint1_dec */
			{
#line 1471 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 708 "syntax.c"
			}
			/* END OF ACTION: mint1_dec */
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
			/* BEGINNING OF ACTION: mint2 */
			{
#line 1477 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
#line 730 "syntax.c"
			}
			/* END OF ACTION: mint2 */
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

			/* BEGINNING OF ACTION: fden2_dec */
			{
#line 935 "syntax.act"

    /* (ZIc), (ZId) uninitialised */
    (ZIf) = 1;
    (ZIg) = UL(radix);
    SET_TDF((ZIe), &(ZIa));
    out_tdfstring_bytes(fformat(lex_v.val.name,lnum), 8, UI(lnum));
    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIb));
#line 763 "syntax.c"
			}
			/* END OF ACTION: fden2_dec */
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
			/* BEGINNING OF ACTION: fden3 */
			{
#line 945 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIc));
#line 784 "syntax.c"
			}
			/* END OF ACTION: fden3 */
			read_floating_variety ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: fden4 */
			{
#line 950 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZId));
#line 798 "syntax.c"
			}
			/* END OF ACTION: fden4 */
			ZRrounding__mode__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: fden5 */
			{
#line 955 "syntax.act"

    RESET_TDF((ZIe));
    o_make_floating(append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1),
		    if ((ZIf)) { o_true; } else { o_false; },
		    o_make_string(append_TDF(&(ZIa), 1)),
		    o_make_nat(out_tdfint32((ZIg))),
		    append_TDF(&(ZIb), 1));
#line 817 "syntax.c"
			}
			/* END OF ACTION: fden5 */
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
read_variety(void)
{
ZL2_variety:;
	switch (CURRENT_TERMINAL) {
	case 127:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 649 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: variety */
						goto ZL2_variety;
						/* END OF INLINE: variety */
					}
					UNREACHED;
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 873 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
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
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 894 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
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
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 915 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
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
						/* BEGINNING OF ACTION: variety1 */
						{
#line 2337 "syntax.act"

    RESET_TDF((ZId));
    o_var_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
	       append_TDF(&(ZIc),1));
#line 937 "syntax.c"
						}
						/* END OF ACTION: variety1 */
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
			/* END OF INLINE: 649 */
		}
		break;
	case 21: case 56: case 64: case 97:
	case 101: case 121:
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

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 976 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 985 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 128:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 1000 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 1009 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 10: case 22: case 55: case 62:
	case 68: case 98: case 99: case 100:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			/* BEGINNING OF ACTION: variety2_dec */
			{
#line 2343 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 1027 "syntax.c"
			}
			/* END OF ACTION: variety2_dec */
			ZRsigned__nat__body ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: variety3 */
			{
#line 2348 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 1041 "syntax.c"
			}
			/* END OF ACTION: variety3 */
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
			/* BEGINNING OF ACTION: variety4 */
			{
#line 2353 "syntax.act"

    RESET_TDF((ZIc));
    o_var_limits(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
#line 1062 "syntax.c"
			}
			/* END OF ACTION: variety4 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 1080 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR646(void)
{
	switch (CURRENT_TERMINAL) {
	case 79:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			TDF ZId;

			/* BEGINNING OF ACTION: call1_dec */
			{
#line 336 "syntax.act"

    /* (ZIb), (ZIc), (ZId) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 1104 "syntax.c"
			}
			/* END OF ACTION: call1_dec */
			ADVANCE_LEXER;
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: call2 */
			{
#line 342 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
#line 1119 "syntax.c"
			}
			/* END OF ACTION: call2 */
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

			/* BEGINNING OF ACTION: tcall1_dec */
			{
#line 2137 "syntax.act"

    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 1146 "syntax.c"
			}
			/* END OF ACTION: tcall1_dec */
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
			/* BEGINNING OF ACTION: tcall2 */
			{
#line 2146 "syntax.act"

    TDF cees;
    cees = *current_TDF;
    INIT_TDF(current_TDF);
    o_tail_call(do_procprops(g_ce_v*2),
		append_TDF(&(ZIa),1), append_TDF(&cees,1));
#line 1172 "syntax.c"
			}
			/* END OF ACTION: tcall2 */
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
ZRtok__formal__list__opt(void)
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
			/* BEGINNING OF ACTION: tok_fml_opt1 */
			{
#line 2318 "syntax.act"

    g_tokpars = (Tokpar*)0;
#line 1215 "syntax.c"
			}
			/* END OF ACTION: tok_fml_opt1 */
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
ZR647(void)
{
	switch (CURRENT_TERMINAL) {
	case 54:
		{
			/* BEGINNING OF ACTION: expstar1 */
			{
#line 839 "syntax.act"

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
#line 1251 "syntax.c"
			}
			/* END OF ACTION: expstar1 */
			ADVANCE_LEXER;
		}
		break;
	case 78:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			/* BEGINNING OF ACTION: expstar2_dec */
			{
#line 842 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 1269 "syntax.c"
			}
			/* END OF ACTION: expstar2_dec */
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
			/* BEGINNING OF ACTION: expstar3 */
			{
#line 847 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 1290 "syntax.c"
			}
			/* END OF ACTION: expstar3 */
			ZRunary__exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expstar4 */
			{
#line 852 "syntax.act"

    RESET_TDF((ZIc));
    o_contents(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
#line 1304 "syntax.c"
			}
			/* END OF ACTION: expstar4 */
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
ZR648(void)
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

			/* BEGINNING OF ACTION: expcond1_dec */
			{
#line 640 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = defaultlab;
    (ZIf) = labdecs;
    defaultlab = -1;
    SET_TDF((ZId), &(ZIa));
#line 1342 "syntax.c"
			}
			/* END OF ACTION: expcond1_dec */
			ADVANCE_LEXER;
			ZRexp__sequence ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expcond2 */
			{
#line 648 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 1357 "syntax.c"
			}
			/* END OF ACTION: expcond2 */
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
			/* BEGINNING OF ACTION: expcond3 */
			{
#line 653 "syntax.act"

    (ZIc) = optlab;
    defaultlab = (ZIe);
    tidy_labels((ZIf));
#line 1379 "syntax.c"
			}
			/* END OF ACTION: expcond3 */
			ZRexp__sequence ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expcond4 */
			{
#line 659 "syntax.act"

    INIT_TDF((ZId));
    RESET_TDF((ZId));
    o_conditional(append_TDF(&(ZIc),1),
		  append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
#line 1395 "syntax.c"
			}
			/* END OF ACTION: expcond4 */
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

			/* BEGINNING OF ACTION: query_type1 */
			{
#line 1609 "syntax.act"

    query_t = lex_query;
#line 1420 "syntax.c"
			}
			/* END OF ACTION: query_type1 */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exptst1_dec */
			{
#line 879 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = query_t;
    SET_TDF((ZId),&(ZIa));
#line 1431 "syntax.c"
			}
			/* END OF ACTION: exptst1_dec */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst2 */
			{
#line 885 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId),&(ZIb));
#line 1445 "syntax.c"
			}
			/* END OF ACTION: exptst2 */
			read_ntest ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst3 */
			{
#line 890 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc))
#line 1459 "syntax.c"
			}
			/* END OF ACTION: exptst3 */
			read_exp ();
			ZRlabdest__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst4 */
			{
#line 895 "syntax.act"

    RESET_TDF((ZId));
    switch ((ZIe)) {
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
	    o_pointer_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_proc__query:
	    o_proc_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
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
#line 1499 "syntax.c"
			}
			/* END OF ACTION: exptst4 */
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
ZR650(void)
{
	switch (CURRENT_TERMINAL) {
	case 21:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: varietychar */
			{
#line 2363 "syntax.act"

    o_var_limits(
	o_make_signed_nat(out_tdfbool(issigned),
	    out_tdfint32(UL((issigned)?MINSC:0))),
	o_make_signed_nat(out_tdfbool(0),
	    out_tdfint32(UL((issigned)?MAXSC:MAXUSC))));
#line 1538 "syntax.c"
			}
			/* END OF ACTION: varietychar */
		}
		break;
	case 56:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: varietyint */
			{
#line 2371 "syntax.act"

    o_var_limits(
	o_make_signed_nat(out_tdfbool(issigned),
	    out_tdfint32(UL((issigned)?MINSI:0))),
	o_make_signed_nat(out_tdfbool(0),
	    out_tdfint32(UL((issigned)?MAXSI:MAXUSI))));
#line 1555 "syntax.c"
			}
			/* END OF ACTION: varietyint */
		}
		break;
	case 64:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: varietylong */
			{
#line 2379 "syntax.act"

    o_var_limits(
	o_make_signed_nat(out_tdfbool(issigned),
	    out_tdfint32(UL((issigned)?MINSL:0))),
	o_make_signed_nat(out_tdfbool(0),
	    out_tdfint32(UL((issigned)?MAXSL:MAXUSL))));
#line 1572 "syntax.c"
			}
			/* END OF ACTION: varietylong */
		}
		break;
	case 97:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: varietyshort */
			{
#line 2394 "syntax.act"

    o_var_limits(
	o_make_signed_nat(out_tdfbool(issigned),
	    out_tdfint32(UL((issigned)?MINSS:0))),
	o_make_signed_nat(out_tdfbool(0),
	    out_tdfint32(UL((issigned)?MAXSS:MAXUSS))));
#line 1589 "syntax.c"
			}
			/* END OF ACTION: varietyshort */
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
ZRsortname__list(void)
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
ZRsignature__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 85: case 104: case 105: case 107:
		{
			read_string ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: newstr_opt1 */
			{
#line 1503 "syntax.act"

    current_TDF->no=1;
#line 1641 "syntax.c"
			}
			/* END OF ACTION: newstr_opt1 */
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
ZRexp__sequence(void)
{
	switch (CURRENT_TERMINAL) {
	case 10: case 19: case 22: case 28:
	case 41: case 42: case 43: case 44:
	case 45: case 52: case 54: case 55:
	case 58: case 61: case 62: case 68:
	case 76: case 77: case 78: case 79:
	case 81: case 82: case 84: case 85:
	case 86: case 88: case 98: case 99:
	case 100: case 102: case 103: case 104:
	case 105: case 107: case 109: case 110:
	case 111: case 124:
		{
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp_sls2 */
			{
#line 613 "syntax.act"

    current_TDF->no =1;
#line 1682 "syntax.c"
			}
			/* END OF ACTION: exp_sls2 */
			ZR628 ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: exp_sls1 */
			{
#line 609 "syntax.act"

    current_TDF->no =1;
    o_make_top;
#line 1700 "syntax.c"
			}
			/* END OF ACTION: exp_sls1 */
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
ZRrange(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		PTR_TDF ZIa;

		/* BEGINNING OF ACTION: range1_dec */
		{
#line 1628 "syntax.act"

    SET_TDF((ZIa), &g_lower);
#line 1733 "syntax.c"
		}
		/* END OF ACTION: range1_dec */
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
ZR654(void)
{
	switch (CURRENT_TERMINAL) {
	case 21:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapechar */
			{
#line 1689 "syntax.act"

    Name * shtok = tokforcharsh(issigned);
    o_shape_apply_token(make_tok(shtok), {});
#line 1762 "syntax.c"
			}
			/* END OF ACTION: shapechar */
		}
		break;
	case 56:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapeint */
			{
#line 1704 "syntax.act"

    Name * shtok = tokforintsh(issigned);
    o_shape_apply_token(make_tok(shtok), {});
#line 1776 "syntax.c"
			}
			/* END OF ACTION: shapeint */
		}
		break;
	case 64:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapelong */
			{
#line 1709 "syntax.act"

    Name * shtok = tokforlongsh(issigned);
    o_shape_apply_token(make_tok(shtok), {});
#line 1790 "syntax.c"
			}
			/* END OF ACTION: shapelong */
		}
		break;
	case 97:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapeshort */
			{
#line 1719 "syntax.act"

    Name * shtok = tokforshortsh(issigned);
    o_shape_apply_token(make_tok(shtok), {});
#line 1804 "syntax.c"
			}
			/* END OF ACTION: shapeshort */
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
ZR655(TDF *ZIa, PTR_TDF *ZIb)
{
	switch (CURRENT_TERMINAL) {
	case 24:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: otagexp3 */
			{
#line 1576 "syntax.act"

    char* n = lex_v.val.name;
    Tagdec * x = find_tag(n);
    if (x != (Tagdec*)0) { fail("Tag %s declared twice", n); }
    x = xmalloc(sizeof *x); x->isdeffed = 1; x->hassh=0; x->iskept=0;
    NEW_IDNAME(x->idname, n, tag_ent);
    x->isvar = 1;
    x->next = g_app_tags; g_app_tags = x;
    RESET_TDF((*ZIb));
    o_make_otagexp(OPTION(make_tag(&x->idname.name)),append_TDF(&(*ZIa),1));
#line 1840 "syntax.c"
			}
			/* END OF ACTION: otagexp3 */
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
			/* BEGINNING OF ACTION: otagexp2 */
			{
#line 1564 "syntax.act"

    RESET_TDF((*ZIb));
    o_make_otagexp({}, append_TDF(&(*ZIa),1));
#line 1860 "syntax.c"
			}
			/* END OF ACTION: otagexp2 */
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
ZRrange__label__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		TDF ZIa;
		PTR_TDF ZIb;

		/* BEGINNING OF ACTION: rllist1_dec */
		{
#line 1648 "syntax.act"

    SET_TDF((ZIb),&(ZIa));
#line 1889 "syntax.c"
		}
		/* END OF ACTION: rllist1_dec */
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
ZR656(void)
{
	switch (CURRENT_TERMINAL) {
	case 10: case 19: case 22: case 28:
	case 41: case 42: case 43: case 44:
	case 45: case 52: case 54: case 55:
	case 58: case 61: case 62: case 68:
	case 76: case 77: case 78: case 79:
	case 81: case 82: case 84: case 85:
	case 86: case 88: case 98: case 99:
	case 100: case 102: case 103: case 104:
	case 105: case 107: case 109: case 110:
	case 111: case 124:
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
read_shape(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		TDF ZIa;
		PTR_TDF ZIb;
		int ZIc;

		/* BEGINNING OF ACTION: genhold1_dec */
		{
#line 1099 "syntax.act"

    (ZIc) = (current_TDF->first == current_TDF->last &&
	      current_TDF->first->usage == 0 &&
	      current_TDF->first->offst == 0);
    if (!(ZIc)) { SET_TDF((ZIb), &(ZIa)); }
#line 1968 "syntax.c"
		}
		/* END OF ACTION: genhold1_dec */
		ZRshape__body ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: genhold2 */
		{
#line 1106 "syntax.act"

    if (!(ZIc)) {
	SET((ZIb));
	RESET_TDF((ZIb));
	append_TDF(&(ZIa),1);
    }
#line 1985 "syntax.c"
		}
		/* END OF ACTION: genhold2 */
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 1997 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR657(void)
{
	switch (CURRENT_TERMINAL) {
	case 23:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: untidy3 */
			{
#line 2330 "syntax.act"

    g_unt = 3;
#line 2015 "syntax.c"
			}
			/* END OF ACTION: untidy3 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: untidy2 */
			{
#line 2326 "syntax.act"

    g_unt = 1;
#line 2027 "syntax.c"
			}
			/* END OF ACTION: untidy2 */
		}
		break;
	case 130:
		return;
	}
}

static void
ZRaccess__list(void)
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
		/* BEGINNING OF ACTION: acc_l1 */
		{
#line 202 "syntax.act"

    current_TDF->no=1;
#line 2054 "syntax.c"
		}
		/* END OF ACTION: acc_l1 */
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
ZR660(TDF *ZIa, TDF *ZIb, TDF *ZIc, TDF *ZId)
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
			/* BEGINNING OF ACTION: call3 */
			{
#line 347 "syntax.act"

    (*ZIc) = *current_TDF;
    INIT_TDF(current_TDF);
#line 2087 "syntax.c"
			}
			/* END OF ACTION: call3 */
			ZRvarpar__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: call4 */
			{
#line 352 "syntax.act"

    (*ZId) = *current_TDF;
    INIT_TDF(current_TDF);
    o_apply_proc(append_TDF(&(*ZIb),1), append_TDF(&(*ZIa),1),
	    { append_TDF(&(*ZIc), 1); current_TDF->no = (*ZIc).no; },
	      if ((*ZId).no !=0) { OPTION(append_TDF(&(*ZId),1)); }
	   );
#line 2105 "syntax.c"
			}
			/* END OF ACTION: call4 */
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
			/* BEGINNING OF ACTION: gcall1_dec */
			{
#line 1036 "syntax.act"

    /* (ZIe), (ZIf), (ZIg) uninitialised */
    /* (ZIh), (ZIi), (ZIk) uninitialised */
    (ZIj) = g_app_tags;
    (ZIl) = tagdecs;
    g_app_tags = (Tagdec*)0;
#line 2138 "syntax.c"
			}
			/* END OF ACTION: gcall1_dec */
			ZRotagexp__list__opt ();
			ZRcaller__var__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: gcall2 */
			{
#line 1044 "syntax.act"

    (ZIe) = *current_TDF;
    INIT_TDF(current_TDF);
    (ZIh) = g_cr_v;
    (ZIk) = g_app_tags;
    g_app_tags = (ZIj);
#line 2156 "syntax.c"
			}
			/* END OF ACTION: gcall2 */
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
			/* BEGINNING OF ACTION: gcall3 */
			{
#line 1052 "syntax.act"

    (ZIf) = *current_TDF;
    (ZIi) = g_ce_v;
    INIT_TDF(current_TDF);
    while ((ZIk) != (Tagdec*)0) {
	Tagdec * x = (ZIk);
	(ZIk) = x->next;
	x->next = tagdecs;
	tagdecs = x;
    }
#line 2185 "syntax.c"
			}
			/* END OF ACTION: gcall3 */
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
			/* BEGINNING OF ACTION: gcall4 */
			{
#line 1064 "syntax.act"

    (ZIg) = *current_TDF;
    INIT_TDF(current_TDF);
    tagdecs = (ZIl);
    o_apply_general_proc(
	append_TDF(&(*ZIb),1), do_procprops((ZIh)+2*(ZIi)+4*g_unt),
	append_TDF(&(*ZIa),1),
	{ append_TDF(&(ZIe),1); current_TDF->no = (ZIe).no; },
	append_TDF(&(ZIf),1),
	append_TDF(&(ZIg), 1))
#line 2217 "syntax.c"
			}
			/* END OF ACTION: gcall4 */
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
ZRtagshacc__list__opt(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		/* BEGINNING OF ACTION: tagshacc_l1 */
		{
#line 2130 "syntax.act"

    current_TDF->no =0;
#line 2245 "syntax.c"
		}
		/* END OF ACTION: tagshacc_l1 */
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
ZR661(TDF *ZIa, PTR_TDF *ZIb)
{
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: rllist2 */
			{
#line 1652 "syntax.act"

    RESET_TDF((*ZIb));
    o_make_caselim(append_TDF(&(*ZIa),1),
		   append_TDF(&g_lower, g_has_upper),
		   append_TDF(&g_upper,1));
    current_TDF->no = 1;
#line 2275 "syntax.c"
			}
			/* END OF ACTION: rllist2 */
		}
		break;
	case 25:
		{
			/* BEGINNING OF ACTION: rllist3 */
			{
#line 1660 "syntax.act"

    RESET_TDF((*ZIb));
    o_make_caselim(append_TDF(&(*ZIa),1),
		   append_TDF(&g_lower, g_has_upper),
		   append_TDF(&g_upper,1));
#line 2290 "syntax.c"
			}
			/* END OF ACTION: rllist3 */
			ADVANCE_LEXER;
			ZRrange__label__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: rllist4 */
			{
#line 1668 "syntax.act"

    current_TDF->no++;
#line 2304 "syntax.c"
			}
			/* END OF ACTION: rllist4 */
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
ZRlabdest__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 11:
		{
			PTR_TDF ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: dest_o1_dec */
			{
#line 465 "syntax.act"

    SET_TDF((ZIa), &optlab);
#line 2332 "syntax.c"
			}
			/* END OF ACTION: dest_o1_dec */
			read_label ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: dest_opt2 */
			{
#line 469 "syntax.act"

    RESET_TDF((ZIa));
#line 2345 "syntax.c"
			}
			/* END OF ACTION: dest_opt2 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: lset_o1 */
			{
#line 1452 "syntax.act"

    TDF * hold;
    SET_TDF(hold, &optlab);
    if (defaultlab==-1)defaultlab = next_label();
    o_make_label(out_tdfint32(UL(defaultlab)));
    RESET_TDF(hold);
#line 2361 "syntax.c"
			}
			/* END OF ACTION: lset_o1 */
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
ZR662(PTR_TDF *ZIa)
{
	switch (CURRENT_TERMINAL) {
	case 24:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: range3 */
			{
#line 1638 "syntax.act"

    RESET_TDF((*ZIa));
    SET_TDF((*ZIa), &g_upper);
#line 2388 "syntax.c"
			}
			/* END OF ACTION: range3 */
			ZRsigned__nat__body ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: range4 */
			{
#line 1643 "syntax.act"

    RESET_TDF((*ZIa));
    g_has_upper=1;
#line 2402 "syntax.c"
			}
			/* END OF ACTION: range4 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: range2 */
			{
#line 1632 "syntax.act"

    RESET_TDF((*ZIa));
    g_upper = g_lower;
    g_has_upper=0;
#line 2416 "syntax.c"
			}
			/* END OF ACTION: range2 */
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
ZRalignment__list__opt(void)
{
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: al_list_opt1 */
			{
#line 244 "syntax.act"

    o_alignment(o_top);
#line 2441 "syntax.c"
			}
			/* END OF ACTION: al_list_opt1 */
		}
		break;
	case 4: case 5: case 7: case 8:
	case 9: case 54: case 78:
		{
			TDF ZIa;
			PTR_TDF ZIb;
			int ZIc;

			/* BEGINNING OF ACTION: genhold1_dec */
			{
#line 1099 "syntax.act"

    (ZIc) = (current_TDF->first == current_TDF->last &&
	      current_TDF->first->usage == 0 &&
	      current_TDF->first->offst == 0);
    if (!(ZIc)) { SET_TDF((ZIb), &(ZIa)); }
#line 2461 "syntax.c"
			}
			/* END OF ACTION: genhold1_dec */
			ZRalignment__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: genhold2 */
			{
#line 1106 "syntax.act"

    if (!(ZIc)) {
	SET((ZIb));
	RESET_TDF((ZIb));
	append_TDF(&(ZIa),1);
    }
#line 2478 "syntax.c"
			}
			/* END OF ACTION: genhold2 */
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
ZR663(void)
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
			/* BEGINNING OF ACTION: offexpl2 */
			{
#line 1545 "syntax.act"

    current_TDF->no+=2;
#line 2509 "syntax.c"
			}
			/* END OF ACTION: offexpl2 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: offexpl1 */
			{
#line 1541 "syntax.act"

    current_TDF->no = 2;
#line 2521 "syntax.c"
			}
			/* END OF ACTION: offexpl1 */
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
read_string(void)
{
ZL2_string:;
	switch (CURRENT_TERMINAL) {
	case 105:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 631 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: string */
						goto ZL2_string;
						/* END OF INLINE: string */
					}
					UNREACHED;
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 2568 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
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
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 2589 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
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
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 2616 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_string ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: newstring2 */
						{
#line 1511 "syntax.act"

    RESET_TDF((ZId));
    o_string_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		  append_TDF(&(ZIc),1));
#line 2631 "syntax.c"
						}
						/* END OF ACTION: newstring2 */
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
			/* END OF INLINE: 631 */
		}
		break;
	case 104:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 2659 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 2668 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 107:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 2683 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 2692 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 85:
		{
			/* BEGINNING OF ACTION: newstring1 */
			{
#line 1508 "syntax.act"

    char * s = lex_v.val.name;
    o_make_string(out_tdfstring_bytes(s, 8, UI(strlen(s))));
#line 2705 "syntax.c"
			}
			/* END OF ACTION: newstring1 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 2724 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR664(void)
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
ZRotagexp__list(void)
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
		/* BEGINNING OF ACTION: otagel1 */
		{
#line 1549 "syntax.act"

    current_TDF->no = 1;
#line 2771 "syntax.c"
		}
		/* END OF ACTION: otagel1 */
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
ZRvariety__sign(void)
{
	switch (CURRENT_TERMINAL) {
	case 101:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: signedornot1 */
			{
#line 1805 "syntax.act"

    issigned = 1;
#line 2798 "syntax.c"
			}
			/* END OF ACTION: signedornot1 */
		}
		break;
	case 121:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: signedornot2 */
			{
#line 1809 "syntax.act"

    issigned = 0;
#line 2811 "syntax.c"
			}
			/* END OF ACTION: signedornot2 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: signedornot1 */
			{
#line 1805 "syntax.act"

    issigned = 1;
#line 2823 "syntax.c"
			}
			/* END OF ACTION: signedornot1 */
		}
		break;
	case 130:
		return;
	}
}

static void
ZR668(void)
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
			/* BEGINNING OF ACTION: llist4 */
			{
#line 1439 "syntax.act"

    g_lablist.no++;
#line 2850 "syntax.c"
			}
			/* END OF ACTION: llist4 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: llist3 */
			{
#line 1435 "syntax.act"

    g_lablist.no = 1;
#line 2862 "syntax.c"
			}
			/* END OF ACTION: llist3 */
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
ZR669(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_Tagdec *ZId, int *ZIe)
{
	switch (CURRENT_TERMINAL) {
	case 36:
		{
			/* BEGINNING OF ACTION: intro2 */
			{
#line 1200 "syntax.act"

    RESET_TDF((*ZIc));
    SET_TDF((*ZIc), &(*ZIb));
    (*ZIe) = g_has_vis;
#line 2889 "syntax.c"
			}
			/* END OF ACTION: intro2 */
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: intro4 */
			{
#line 1212 "syntax.act"

    RESET_TDF((*ZIc));
    intro_acc = (*ZIa);
    intro_init = (*ZIb);
    (*ZId)->isvar=1;
    if ((*ZIe)) {
	Tagdec * y = xmalloc(sizeof *y);
	*y = *(*ZId);
	y->next = tagdecs;
	tagdecs = y;
    }
    (*ZId)->next = localdecs;
    localdecs = (*ZId);
#line 2914 "syntax.c"
			}
			/* END OF ACTION: intro4 */
		}
		break;
	case 24:
		{
			/* BEGINNING OF ACTION: intro3 */
			{
#line 1206 "syntax.act"

    RESET_TDF((*ZIc));
    SET_TDF((*ZIc), &(*ZId)->sh.tdfsh);
    (*ZId)->hassh=2;
#line 2928 "syntax.c"
			}
			/* END OF ACTION: intro3 */
			ADVANCE_LEXER;
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: intro2 */
			{
#line 1200 "syntax.act"

    RESET_TDF((*ZIc));
    SET_TDF((*ZIc), &(*ZIb));
    (*ZIe) = g_has_vis;
#line 2944 "syntax.c"
			}
			/* END OF ACTION: intro2 */
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
ZR670(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_Tagdec *ZId, int *ZIe)
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
			/* BEGINNING OF ACTION: intro4 */
			{
#line 1212 "syntax.act"

    RESET_TDF((*ZIc));
    intro_acc = (*ZIa);
    intro_init = (*ZIb);
    (*ZId)->isvar=1;
    if ((*ZIe)) {
	Tagdec * y = xmalloc(sizeof *y);
	*y = *(*ZId);
	y->next = tagdecs;
	tagdecs = y;
    }
    (*ZId)->next = localdecs;
    localdecs = (*ZId);
#line 2993 "syntax.c"
			}
			/* END OF ACTION: intro4 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: intro6 */
			{
#line 1242 "syntax.act"

    o_make_value(append_TDF(&(*ZId)->sh.tdfsh, 0));
#line 3005 "syntax.c"
			}
			/* END OF ACTION: intro6 */
			/* BEGINNING OF ACTION: intro4 */
			{
#line 1212 "syntax.act"

    RESET_TDF((*ZIc));
    intro_acc = (*ZIa);
    intro_init = (*ZIb);
    (*ZId)->isvar=1;
    if ((*ZIe)) {
	Tagdec * y = xmalloc(sizeof *y);
	*y = *(*ZId);
	y->next = tagdecs;
	tagdecs = y;
    }
    (*ZId)->next = localdecs;
    localdecs = (*ZId);
#line 3024 "syntax.c"
			}
			/* END OF ACTION: intro4 */
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
read_signed_nat(void)
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 3059 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR672(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_char *ZId)
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
			/* BEGINNING OF ACTION: exp2 */
			{
#line 521 "syntax.act"

    INIT_TDF((*ZIc));
    RESET_TDF((*ZIc));
    if (strcmp((*ZId), "*+.") ==0) {
	o_add_to_ptr(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), "*-*") ==0) {
	o_subtract_ptrs(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), ".*") ==0) {
	o_offset_mult(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), ".+.") ==0) {
	o_offset_add(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), ".-.") ==0) {
	o_offset_subtract(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), "./") ==0) {
	o_offset_div_by_int(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), "./.") ==0) {
	o_offset_div(
	    o_var_limits(
		o_make_signed_nat(out_tdfbool(1), out_tdfint32(UL(MINSI))),
		o_make_signed_nat(out_tdfbool(0), out_tdfint32(UL(MAXSI)))),
	    append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), ".max.") ==0) {
	o_offset_max(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else { fail("%s not an addrop", (*ZId)); }
#line 3104 "syntax.c"
			}
			/* END OF ACTION: exp2 */
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
			/* BEGINNING OF ACTION: exp6 */
			{
#line 601 "syntax.act"

    INIT_TDF((*ZIc));
    RESET_TDF((*ZIc));
    o_assign(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
#line 3124 "syntax.c"
			}
			/* END OF ACTION: exp6 */
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
			/* BEGINNING OF ACTION: exp3 */
			{
#line 547 "syntax.act"

    INIT_TDF((*ZIc));
    RESET_TDF((*ZIc));
    if (strcmp((*ZId), "And") ==0) {
	o_and(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), "Or") ==0) {
	o_or(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId), "Xor") ==0) {
	o_xor(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else { fail("%s not a logop", (*ZId)); }
#line 3150 "syntax.c"
			}
			/* END OF ACTION: exp3 */
		}
		break;
	case 10: case 68: case 103:
		{
			/* BEGINNING OF INLINE: binop */
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
			/* END OF INLINE: binop */
			ZRunary__exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exp5 */
			{
#line 559 "syntax.act"

    INIT_TDF((*ZIc));
    RESET_TDF((*ZIc));
    if (strcmp((*ZId),"%") ==0) {
	o_rem2(o_continue, o_continue, append_TDF(&(*ZIa),1),
	       append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"%1") ==0) {
	o_rem1(o_continue, o_continue, append_TDF(&(*ZIa),1),
	       append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"*") ==0) {
	o_mult(o_wrap, append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"+") ==0) {
	o_plus(o_wrap, append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"-") ==0) {
	o_minus(o_wrap, append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"/") ==0) {
	o_div2(o_continue, o_continue, append_TDF(&(*ZIa),1),
	       append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"/1") ==0) {
	o_div1(o_continue, o_continue, append_TDF(&(*ZIa),1),
	       append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"<<") ==0) {
	o_shift_left(o_wrap, append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"F*") ==0) {
	o_floating_mult(o_continue,
	    { LIST_ELEM(append_TDF(&(*ZIa),1));
	    LIST_ELEM(append_TDF(&(*ZIb),1))});
    } else if (strcmp((*ZId),">>") ==0) {
	o_shift_right(append_TDF(&(*ZIa),1), append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"F+") ==0) {
	o_floating_plus(o_continue,
	    { LIST_ELEM(append_TDF(&(*ZIa),1));
	    LIST_ELEM(append_TDF(&(*ZIb),1))});
    } else if (strcmp((*ZId),"F-") ==0) {
	o_floating_minus(o_continue, append_TDF(&(*ZIa),1),
			 append_TDF(&(*ZIb),1));
    } else if (strcmp((*ZId),"F/") ==0) {
	o_floating_div(o_continue, append_TDF(&(*ZIa),1),
		       append_TDF(&(*ZIb),1));
    } else { fail("%s not an arithop", (*ZId)); }
#line 3228 "syntax.c"
			}
			/* END OF ACTION: exp5 */
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
read_token(void)
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
			/* BEGINNING OF INLINE: token */
			goto ZL2_token;
			/* END OF INLINE: token */
		}
		UNREACHED;
	case 123:
		{
			TDF ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tok2_dec */
			{
#line 2180 "syntax.act"

    (ZIa) = g_tok_defn;
#line 3274 "syntax.c"
			}
			/* END OF ACTION: tok2_dec */
			ZRtok__def__body ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tok3 */
			{
#line 2185 "syntax.act"

    o_use_tokdef(append_TDF(&g_tok_defn,1));
    g_tok_defn = (ZIa);
#line 3288 "syntax.c"
			}
			/* END OF ACTION: tok3 */
		}
		break;
	case 2: case 5: case 9: case 15:
	case 18: case 40: case 43: case 49:
	case 60: case 71: case 75: case 91:
	case 96: case 100: case 111: case 120:
	case 128:
		{
			/* BEGINNING OF ACTION: tok1 */
			{
#line 2177 "syntax.act"

    Tokdec * td = lex_v.val.tokname;
    if (td->isparam) {
	o_token_apply_token(make_tok(&td->idname.name), {});
    } else {
	make_tok(&td->idname.name);
    }
    /* token should only be expanded as parameter of a token */
#line 3310 "syntax.c"
			}
			/* END OF ACTION: tok1 */
			/* BEGINNING OF INLINE: tok_item */
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
			/* END OF INLINE: tok_item */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 3421 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR673(void)
{
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: snl1 */
			{
#line 1854 "syntax.act"

    g_tokpars = xmalloc(sizeof *g_tokpars);
    g_tokpars->par = g_sname;
    g_tokpars->next = (Tokpar*)0;
#line 3440 "syntax.c"
			}
			/* END OF ACTION: snl1 */
		}
		break;
	case 25:
		{
			Sort ZIa;

			/* BEGINNING OF ACTION: snl2_dec */
			{
#line 1857 "syntax.act"

    (ZIa) = g_sname;
#line 3454 "syntax.c"
			}
			/* END OF ACTION: snl2_dec */
			ADVANCE_LEXER;
			ZRsortname__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: snl3 */
			{
#line 1862 "syntax.act"

    Tokpar * x = xmalloc(sizeof *x);
    x->par = (ZIa);
    x->next = g_tokpars;
    g_tokpars = x;
#line 3471 "syntax.c"
			}
			/* END OF ACTION: snl3 */
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
ZRnat__not__int(void)
{
ZL2_nat__not__int:;
	switch (CURRENT_TERMINAL) {
	case 70:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 651 */
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
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 3520 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
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
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 3541 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
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
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 3562 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
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
						/* BEGINNING OF ACTION: nat1 */
						{
#line 1483 "syntax.act"

    RESET_TDF((ZId));
    o_nat_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
	       append_TDF(&(ZIc),1));
#line 3584 "syntax.c"
						}
						/* END OF ACTION: nat1 */
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
			/* END OF INLINE: 651 */
		}
		break;
	case 69:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 3612 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 3621 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 71:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 3636 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 3645 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
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
ZRshape__body(void)
{
	switch (CURRENT_TERMINAL) {
	case 32:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapedouble */
			{
#line 1694 "syntax.act"

    Name * shtok = tokfordoublesh();
    o_shape_apply_token(make_tok(shtok), {});
#line 3674 "syntax.c"
			}
			/* END OF ACTION: shapedouble */
		}
		break;
	case 46:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapefloat */
			{
#line 1699 "syntax.act"

    Name * shtok = tokforfloatsh();
    o_shape_apply_token(make_tok(shtok), {});
#line 3688 "syntax.c"
			}
			/* END OF ACTION: shapefloat */
		}
		break;
	case 83:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shptr1_dec */
			{
#line 1743 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 3704 "syntax.c"
			}
			/* END OF ACTION: shptr1_dec */
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: shapeptr2 */
			{
#line 1712 "syntax.act"

    RESET_TDF((ZIb));
    o_pointer(o_alignment(append_TDF(&(ZIa),1)));
#line 3718 "syntax.c"
			}
			/* END OF ACTION: shapeptr2 */
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
	case 21: case 56: case 64: case 97:
	case 101: case 121:
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

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 3753 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 3762 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 96:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 3777 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 3786 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
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
ZRrepeat__starter__opt(void)
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
			/* BEGINNING OF ACTION: strtr1 */
			{
#line 1869 "syntax.act"

    o_make_top;
#line 3829 "syntax.c"
			}
			/* END OF ACTION: strtr1 */
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
ZR674(void)
{
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: sortname2 */
			{
#line 1826 "syntax.act"

    if (g_sname.sort == token_sort) {
	fail("Token pars require result and parameter sorts");
    }
    g_sname.toksort= (TokSort*)0;
#line 3857 "syntax.c"
			}
			/* END OF ACTION: sortname2 */
		}
		break;
	case 79:
		{
			Sort ZIa;
			PTR_Tokpar ZIb;
			PTR_Tokpar ZIc;

			/* BEGINNING OF ACTION: sortname3_dec */
			{
#line 1829 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIc) = g_tokpars;
    (ZIa) = g_sname;
    if (g_sname.sort != token_sort) {
	fail("Only token pars require result and parameter sorts");
    }
#line 3878 "syntax.c"
			}
			/* END OF ACTION: sortname3_dec */
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
			/* BEGINNING OF ACTION: sortname4 */
			{
#line 1838 "syntax.act"

    (ZIb) = g_tokpars;
#line 3898 "syntax.c"
			}
			/* END OF ACTION: sortname4 */
			ZRfull__sortname ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: sortname5 */
			{
#line 1844 "syntax.act"

    TokSort * ts = xmalloc(sizeof *ts);
    ts->ressort = g_sname;
    ts->pars = (ZIb);
    g_tokpars = (ZIc);
    (ZIa).toksort = ts;
    g_sname = (ZIa);
#line 3916 "syntax.c"
			}
			/* END OF ACTION: sortname5 */
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
ZRfield__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
ZL2_field__list:;
	{
		PTR_TDF ZIa;
		PTR_Tokdec ZIb;
		PTR_Tokdec ZIc;

		/* BEGINNING OF ACTION: field1_dec */
		{
#line 967 "syntax.act"

    char * dotn = append_string(".",lex_v.val.name);
    char * n = lex_v.val.name;
    (ZIb) = find_tok(dotn);
    (ZIc) = find_tok(n);
    if ((ZIb)!= (Tokdec*)0 || (ZIc)!= (Tokdec*)0)
	    fail("Field name %s must be unique", dotn);
    (ZIb) = xmalloc(sizeof *(ZIb)); NEW_IDNAME((ZIb)->idname, dotn, tok_ent);
    (ZIb)->isdeffed = 1; (ZIb)->isused=0; (ZIb)->iskept = 0;
    (ZIb)->sort.ressort.sort = exp_sort;
    (ZIb)->sort.pars = (Tokpar *)0;

    (ZIc) = xmalloc(sizeof *(ZIc)); NEW_IDNAME((ZIc)->idname, n, tok_ent);
    (ZIc)->isdeffed = 1; (ZIc)->isused=0; (ZIc)->iskept = 0;
    (ZIc)->sort.ressort.sort = exp_sort;
    (ZIc)->sort.pars = xmalloc(sizeof *(ZIc)->sort.pars);
    (ZIc)->sort.pars->par.sort = exp_sort;
    (ZIc)->sort.pars->next = (Tokpar*)0;
    (ZIb)->next = (ZIc);
    SET_TDF((ZIa), &g_shape);
#line 3965 "syntax.c"
		}
		/* END OF ACTION: field1_dec */
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
		/* BEGINNING OF ACTION: field2 */
		{
#line 988 "syntax.act"

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
#line 4017 "syntax.c"
		}
		/* END OF ACTION: field2 */
		/* BEGINNING OF INLINE: 682 */
		{
			switch (CURRENT_TERMINAL) {
			case 25:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: field_list */
					goto ZL2_field__list;
					/* END OF INLINE: field_list */
				}
				UNREACHED;
			default:
				break;
			}
		}
		/* END OF INLINE: 682 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR675(void)
{
	switch (CURRENT_TERMINAL) {
	case 21:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapetokchar */
			{
#line 1732 "syntax.act"

    * g_shtokname = *(tokforcharsh(issigned));
#line 4055 "syntax.c"
			}
			/* END OF ACTION: shapetokchar */
		}
		break;
	case 56:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapetokint */
			{
#line 1736 "syntax.act"

    * g_shtokname = *(tokforintsh(issigned));
#line 4068 "syntax.c"
			}
			/* END OF ACTION: shapetokint */
		}
		break;
	case 64:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shapetoklong */
			{
#line 1740 "syntax.act"

    * g_shtokname = *(tokforlongsh(issigned));
#line 4081 "syntax.c"
			}
			/* END OF ACTION: shapetoklong */
		}
		break;
	case 97:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shtokshrt */
			{
#line 1764 "syntax.act"

    * g_shtokname = *(tokforshortsh(issigned));
#line 4094 "syntax.c"
			}
			/* END OF ACTION: shtokshrt */
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
ZR676(void)
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
			/* BEGINNING OF ACTION: gencond1_dec */
			{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 4138 "syntax.c"
			}
			/* END OF ACTION: gencond1_dec */
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
			/* BEGINNING OF ACTION: gencond2 */
			{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 4159 "syntax.c"
			}
			/* END OF ACTION: gencond2 */
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
			/* BEGINNING OF ACTION: gencond3 */
			{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 4180 "syntax.c"
			}
			/* END OF ACTION: gencond3 */
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
			/* BEGINNING OF ACTION: shape1 */
			{
#line 1681 "syntax.act"

    RESET_TDF((ZId));
    o_shape_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		 append_TDF(&(ZIc),1));
#line 4202 "syntax.c"
			}
			/* END OF ACTION: shape1 */
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
ZR677(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_Tagdec *ZId, PTR_char *ZIe, int *ZIf)
{
	switch (CURRENT_TERMINAL) {
	case 36:
		{
			/* BEGINNING OF ACTION: tag_def2 */
			{
#line 2005 "syntax.act"

    RESET_TDF((*ZIc));
    if (!(*ZId)->hassh)fail("No declaration shape for %s", (*ZIe));
    SET_TDF((*ZIc), &(*ZIa));
#line 4238 "syntax.c"
			}
			/* END OF ACTION: tag_def2 */
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_def3 */
			{
#line 2011 "syntax.act"

    RESET_TDF((*ZIc));
    o_make_var_tagdef(out_tdfint32(UL(non_local(&(*ZId)->idname.name, tag_ent))),
	{},
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    (*ZId)->isdeffed = 1;
#line 4258 "syntax.c"
			}
			/* END OF ACTION: tag_def3 */
		}
		break;
	case 24:
		{
			/* BEGINNING OF ACTION: tag_def4 */
			{
#line 2021 "syntax.act"

    RESET_TDF((*ZIc));
    if ((*ZId)->hassh)fail("Two declaration shapes for %s", (*ZIe));
    g_shtokname = &(*ZId)->sh.shtok;
#line 4272 "syntax.c"
			}
			/* END OF ACTION: tag_def4 */
			ADVANCE_LEXER;
			ZRshapetok ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_def5 */
			{
#line 2027 "syntax.act"

    SET_TDF((*ZIc), &(*ZIa));
#line 4286 "syntax.c"
			}
			/* END OF ACTION: tag_def5 */
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
ZRrounding__mode__opt(void)
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
			/* BEGINNING OF ACTION: rmodeopt1 */
			{
#line 1678 "syntax.act"

    o_to_nearest;
#line 4327 "syntax.c"
			}
			/* END OF ACTION: rmodeopt1 */
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
ZR678(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_Tagdec *ZId, PTR_char *ZIe, int *ZIf)
{
	switch (CURRENT_TERMINAL) {
	case 36:
		{
			/* BEGINNING OF ACTION: tag_def2 */
			{
#line 2005 "syntax.act"

    RESET_TDF((*ZIc));
    if (!(*ZId)->hassh)fail("No declaration shape for %s", (*ZIe));
    SET_TDF((*ZIc), &(*ZIa));
#line 4354 "syntax.c"
			}
			/* END OF ACTION: tag_def2 */
			ADVANCE_LEXER;
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: ctag_def3 */
			{
#line 436 "syntax.act"

    RESET_TDF((*ZIc));
    (*ZId)->iscommon = 1;
    o_common_tagdef(out_tdfint32(UL(non_local(&(*ZId)->idname.name, tag_ent))), {},
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    (*ZId)->isdeffed = 1;
#line 4374 "syntax.c"
			}
			/* END OF ACTION: ctag_def3 */
		}
		break;
	case 24:
		{
			/* BEGINNING OF ACTION: tag_def4 */
			{
#line 2021 "syntax.act"

    RESET_TDF((*ZIc));
    if ((*ZId)->hassh)fail("Two declaration shapes for %s", (*ZIe));
    g_shtokname = &(*ZId)->sh.shtok;
#line 4388 "syntax.c"
			}
			/* END OF ACTION: tag_def4 */
			ADVANCE_LEXER;
			ZRshapetok ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_def5 */
			{
#line 2027 "syntax.act"

    SET_TDF((*ZIc), &(*ZIa));
#line 4402 "syntax.c"
			}
			/* END OF ACTION: tag_def5 */
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
ZRnonst__shape(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		TDF ZIa;
		PTR_TDF ZIb;
		int ZIc;

		/* BEGINNING OF ACTION: genhold1_dec */
		{
#line 1099 "syntax.act"

    (ZIc) = (current_TDF->first == current_TDF->last &&
	      current_TDF->first->usage == 0 &&
	      current_TDF->first->offst == 0);
    if (!(ZIc)) { SET_TDF((ZIb), &(ZIa)); }
#line 4442 "syntax.c"
		}
		/* END OF ACTION: genhold1_dec */
		ZRnonst__shape__body ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: genhold2 */
		{
#line 1106 "syntax.act"

    if (!(ZIc)) {
	SET((ZIb));
	RESET_TDF((ZIb));
	append_TDF(&(ZIa),1);
    }
#line 4459 "syntax.c"
		}
		/* END OF ACTION: genhold2 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZR679(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_Tagdec *ZId, PTR_char *ZIe, int *ZIf)
{
	switch (CURRENT_TERMINAL) {
	case 36:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tag_def2 */
			{
#line 2005 "syntax.act"

    RESET_TDF((*ZIc));
    if (!(*ZId)->hassh)fail("No declaration shape for %s", (*ZIe));
    SET_TDF((*ZIc), &(*ZIa));
#line 4483 "syntax.c"
			}
			/* END OF ACTION: tag_def2 */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_def8 */
			{
#line 2069 "syntax.act"

    RESET_TDF((*ZIc));
    o_make_id_tagdef(out_tdfint32(UL(non_local(&(*ZId)->idname.name, tag_ent))),
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    (*ZId)->isdeffed = 1;
#line 4501 "syntax.c"
			}
			/* END OF ACTION: tag_def8 */
		}
		break;
	case 24:
		{
			/* BEGINNING OF ACTION: tag_def4 */
			{
#line 2021 "syntax.act"

    RESET_TDF((*ZIc));
    if ((*ZId)->hassh)fail("Two declaration shapes for %s", (*ZIe));
    g_shtokname = &(*ZId)->sh.shtok;
#line 4515 "syntax.c"
			}
			/* END OF ACTION: tag_def4 */
			ADVANCE_LEXER;
			ZRshapetok ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_def5 */
			{
#line 2027 "syntax.act"

    SET_TDF((*ZIc), &(*ZIa));
#line 4529 "syntax.c"
			}
			/* END OF ACTION: tag_def5 */
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
			/* BEGINNING OF ACTION: tag_def9 */
			{
#line 2078 "syntax.act"

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
#line 4563 "syntax.c"
			}
			/* END OF ACTION: tag_def9 */
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
ZRaccess__opt(void)
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
read_error_code(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		int ZIa;

		/* BEGINNING OF ACTION: gencons1_dec */
		{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 4624 "syntax.c"
		}
		/* END OF ACTION: gencons1_dec */
		switch (CURRENT_TERMINAL) {
		case 37:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: gencons2 */
		{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 4639 "syntax.c"
		}
		/* END OF ACTION: gencons2 */
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 4651 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRpostlude__opt(void)
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
			/* BEGINNING OF ACTION: plude1 */
			{
#line 1582 "syntax.act"

    o_make_top;
#line 4678 "syntax.c"
			}
			/* END OF ACTION: plude1 */
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
ZR680(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_Tagdec *ZId, int *ZIf)
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
			/* BEGINNING OF ACTION: tag_def6 */
			{
#line 2031 "syntax.act"

    RESET_TDF((*ZIc));
    o_make_var_tagdef(out_tdfint32(UL(local_name(&(*ZId)->idname.name, tag_ent))),
	{},
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), (*ZIf))); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(*ZIf)) {
	o_make_var_tagdec(out_tdfint32(UL(non_local(&(*ZId)->idname.name,tag_ent))),
	    {},
	    if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	    o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
	INC_LIST;
    }
    (*ZId)->isdeffed=1; (*ZId)->hassh =1;
    if (!(*ZIf)) { (*ZId)->next = tagdecs; tagdecs = (*ZId); }
#line 4724 "syntax.c"
			}
			/* END OF ACTION: tag_def6 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: tag_def10 */
			{
#line 1965 "syntax.act"

    o_make_value(o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
#line 4736 "syntax.c"
			}
			/* END OF ACTION: tag_def10 */
			/* BEGINNING OF ACTION: tag_def6 */
			{
#line 2031 "syntax.act"

    RESET_TDF((*ZIc));
    o_make_var_tagdef(out_tdfint32(UL(local_name(&(*ZId)->idname.name, tag_ent))),
	{},
	if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), (*ZIf))); },
	append_TDF(&(*ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(*ZIf)) {
	o_make_var_tagdec(out_tdfint32(UL(non_local(&(*ZId)->idname.name,tag_ent))),
	    {},
	    if ((*ZIb).no !=0) { OPTION(append_TDF(&(*ZIb), 1)); },
	    o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
	INC_LIST;
    }
    (*ZId)->isdeffed=1; (*ZId)->hassh =1;
    if (!(*ZIf)) { (*ZId)->next = tagdecs; tagdecs = (*ZId); }
#line 4759 "syntax.c"
			}
			/* END OF ACTION: tag_def6 */
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
ZRexponent__opt(void)
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
			/* BEGINNING OF ACTION: eopt1 */
			{
#line 478 "syntax.act"

    o_make_signed_nat(out_tdfbool(0), out_tdfint32(UL(0)));
#line 4794 "syntax.c"
			}
			/* END OF ACTION: eopt1 */
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
ZR681(TDF *ZIa, TDF *ZIb, PTR_TDF *ZIc, PTR_Tagdec *ZId, int *ZIf)
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
			/* BEGINNING OF ACTION: ctag_def6 */
			{
#line 446 "syntax.act"

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
#line 4840 "syntax.c"
			}
			/* END OF ACTION: ctag_def6 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: tag_def10 */
			{
#line 1965 "syntax.act"

    o_make_value(o_shape_apply_token(make_tok(&(*ZId)->sh.shtok), {}));
#line 4852 "syntax.c"
			}
			/* END OF ACTION: tag_def10 */
			/* BEGINNING OF ACTION: ctag_def6 */
			{
#line 446 "syntax.act"

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
#line 4875 "syntax.c"
			}
			/* END OF ACTION: ctag_def6 */
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
ZRclosed__exp(void)
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
			/* BEGINNING OF ACTION: explab1_dec */
			{
#line 730 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIe) = labdecs;
    (ZIc) = g_lablist;
    INIT_TDF(&g_lablist);
    SET_TDF((ZId), &(ZIa));
#line 4911 "syntax.c"
			}
			/* END OF ACTION: explab1_dec */
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
			/* BEGINNING OF ACTION: explab2 */
			{
#line 738 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 4932 "syntax.c"
			}
			/* END OF ACTION: explab2 */
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
			/* BEGINNING OF ACTION: explab3 */
			{
#line 743 "syntax.act"

    RESET_TDF((ZId));
    o_labelled({ append_TDF(&g_lablist,1);
		  current_TDF->no = g_lablist.no;},
		  append_TDF(&(ZIa), 1),
		  { append_TDF(&(ZIb),1);
		    current_TDF->no = g_lablist.no;});
    tidy_labels((ZIe));
    g_lablist = (ZIc);
#line 4965 "syntax.c"
			}
			/* END OF ACTION: explab3 */
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
			/* BEGINNING OF ACTION: expcond1_dec */
			{
#line 640 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = defaultlab;
    (ZIf) = labdecs;
    defaultlab = -1;
    SET_TDF((ZId), &(ZIa));
#line 5005 "syntax.c"
			}
			/* END OF ACTION: expcond1_dec */
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
			/* BEGINNING OF ACTION: expcond2 */
			{
#line 648 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 5026 "syntax.c"
			}
			/* END OF ACTION: expcond2 */
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
			/* BEGINNING OF ACTION: expcond3 */
			{
#line 653 "syntax.act"

    (ZIc) = optlab;
    defaultlab = (ZIe);
    tidy_labels((ZIf));
#line 5048 "syntax.c"
			}
			/* END OF ACTION: expcond3 */
			ZRexp__sequence ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expcond4 */
			{
#line 659 "syntax.act"

    INIT_TDF((ZId));
    RESET_TDF((ZId));
    o_conditional(append_TDF(&(ZIc),1),
		  append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
#line 5064 "syntax.c"
			}
			/* END OF ACTION: expcond4 */
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
			/* BEGINNING OF ACTION: exprep1_dec */
			{
#line 803 "syntax.act"

    /* (ZIb), (ZIc), (ZIf) uninitialised */
    (ZIe) = labdecs;
    SET_TDF((ZId), &(ZIa));
#line 5093 "syntax.c"
			}
			/* END OF ACTION: exprep1_dec */
			ZRrepeat__starter__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exprep2 */
			{
#line 809 "syntax.act"

    (ZIf) = defaultlab;
    defaultlab = -1;
#line 5107 "syntax.c"
			}
			/* END OF ACTION: exprep2 */
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
			/* BEGINNING OF ACTION: exprep3 */
			{
#line 814 "syntax.act"

    (ZIc) = optlab;
    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 5129 "syntax.c"
			}
			/* END OF ACTION: exprep3 */
			ZRexp__sequence ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exprep4 */
			{
#line 820 "syntax.act"

    RESET_TDF((ZId));
    o_repeat(append_TDF(&(ZIc),1), append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
    tidy_labels((ZIe));
    defaultlab = (ZIf);
#line 5145 "syntax.c"
			}
			/* END OF ACTION: exprep4 */
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

			/* BEGINNING OF ACTION: expdec1_dec */
			{
#line 682 "syntax.act"

    (ZIa) = localdecs;
#line 5172 "syntax.c"
			}
			/* END OF ACTION: expdec1_dec */
			ZRtag__intro ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: ibody1_dec */
			{
#line 1173 "syntax.act"

    (ZIg) = localdecs->isvar;
    (ZIb) = intro_acc;
    (ZIc) = intro_init;
    (ZIf) = localdecs->idname.name;
    SET_TDF((ZIe), &(ZId));
#line 5189 "syntax.c"
			}
			/* END OF ACTION: ibody1_dec */
			ZRclosed__exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: introbody2 */
			{
#line 1246 "syntax.act"

    RESET_TDF((ZIe));
    if ((ZIg)) {
	o_variable(if ((ZIb).no!=0) { OPTION(append_TDF(&(ZIb),1)); },
		    make_tag(&(ZIf)), append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1));
    } else {
	o_identify(if ((ZIb).no!=0) { OPTION(append_TDF(&(ZIb),1)); },
		    make_tag(&(ZIf)), append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1));
    }
#line 5211 "syntax.c"
			}
			/* END OF ACTION: introbody2 */
			/* BEGINNING OF ACTION: expdec2 */
			{
#line 686 "syntax.act"

    localdecs = (ZIa);
#line 5219 "syntax.c"
			}
			/* END OF ACTION: expdec2 */
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
read_bool(void)
{
ZL2_bool:;
	switch (CURRENT_TERMINAL) {
	case 17:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: after_bool_sort */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: bool */
						goto ZL2_bool;
						/* END OF INLINE: bool */
					}
					UNREACHED;
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 5267 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
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
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 5295 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
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
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 5315 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_bool ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: bool1 */
						{
#line 304 "syntax.act"

    RESET_TDF((ZId));
    o_bool_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		append_TDF(&(ZIc),1));
#line 5330 "syntax.c"
						}
						/* END OF ACTION: bool1 */
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
			/* END OF INLINE: after_bool_sort */
		}
		break;
	case 16:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 5358 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 5367 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 18:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 5382 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 5391 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 5409 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRvarintro__opt(void)
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
read_ntest(void)
{
ZL2_ntest:;
	switch (CURRENT_TERMINAL) {
	case 74:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 671 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: ntest */
						goto ZL2_ntest;
						/* END OF INLINE: ntest */
					}
					UNREACHED;
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 5484 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
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
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 5505 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
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
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 5526 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
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
						/* BEGINNING OF ACTION: ntest1 */
						{
#line 1517 "syntax.act"

    RESET_TDF((ZId));
    o_ntest_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		 append_TDF(&(ZIc),1));
#line 5548 "syntax.c"
						}
						/* END OF ACTION: ntest1 */
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
			/* END OF INLINE: 671 */
		}
		break;
	case 75:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 5577 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 5586 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 87:
		{
			/* BEGINNING OF ACTION: ntest2 */
			{
#line 1537 "syntax.act"

    char * n = lex_v.val.name;
    if (strcmp(n,"!<") ==0) { o_not_less_than; }
    else if (strcmp(n,"!<=") ==0) { o_not_less_than_or_equal; }
    else if (strcmp(n,"!=") ==0) { o_not_equal; }
    else if (strcmp(n,"!>") ==0) { o_not_greater_than; }
    else if (strcmp(n,"!>=") ==0) { o_not_greater_than_or_equal; }
    else if (strcmp(n,"!Comparable") ==0) { o_not_comparable; }
    else if (strcmp(n,"<") ==0) { o_less_than; }
    else if (strcmp(n,"<=") ==0) { o_less_than_or_equal; }
    else if (strcmp(n,"==") ==0) { o_equal; }
    else if (strcmp(n,">") ==0) { o_greater_than; }
    else if (strcmp(n,">=") ==0) { o_greater_than_or_equal; }
    else if (strcmp(n,"Comparable") ==0) { o_comparable; }
    else { fail("%s is not a comparison", n); }
#line 5611 "syntax.c"
			}
			/* END OF ACTION: ntest2 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 5630 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

void
read_bitfield_variety(void)
{
ZL2_bitfield__variety:;
	switch (CURRENT_TERMINAL) {
	case 14:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: after_bv_sort */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: bitfield_variety */
						goto ZL2_bitfield__variety;
						/* END OF INLINE: bitfield_variety */
					}
					UNREACHED;
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 5668 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
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
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 5696 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
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
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 5716 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_bitfield_variety ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: bvariety1 */
						{
#line 315 "syntax.act"

    RESET_TDF((ZId));
    o_bfvar_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		 append_TDF(&(ZIc),1));
#line 5731 "syntax.c"
						}
						/* END OF ACTION: bvariety1 */
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
			/* END OF INLINE: after_bv_sort */
		}
		break;
	case 16: case 17: case 18: case 22:
	case 55: case 69: case 70: case 71:
	case 101: case 121:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			/* BEGINNING OF ACTION: bvar3_dec */
			{
#line 310 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 5764 "syntax.c"
			}
			/* END OF ACTION: bvar3_dec */
			ZRbitfield__sign ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: bvariety4 */
			{
#line 326 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 5778 "syntax.c"
			}
			/* END OF ACTION: bvariety4 */
			read_nat ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: bvariety5 */
			{
#line 331 "syntax.act"

    RESET_TDF((ZIc));
    o_bfvar_bits(append_TDF(&(ZIa),1), append_TDF(&(ZIb), 1));
#line 5792 "syntax.c"
			}
			/* END OF ACTION: bvariety5 */
		}
		break;
	case 13:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 5806 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 5815 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 15:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 5830 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 5839 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 5857 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRsigned__nat__body(void)
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
			/* BEGINNING OF INLINE: 633 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: signed_nat_body */
						goto ZL2_signed__nat__body;
						/* END OF INLINE: signed_nat_body */
					}
					UNREACHED;
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 5906 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
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
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 5927 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
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
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 5948 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
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
						/* BEGINNING OF ACTION: signed_nat1 */
						{
#line 1767 "syntax.act"

    RESET_TDF((ZId));
    o_signed_nat_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		      append_TDF(&(ZIc),1));
#line 5970 "syntax.c"
						}
						/* END OF ACTION: signed_nat1 */
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
			/* END OF INLINE: 633 */
		}
		break;
	case 22: case 55:
		{
			ZRinteger ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: signed_nat2 */
			{
#line 1774 "syntax.act"

    o_make_signed_nat(out_tdfbool(0), out_tdfint32(intvalue));
#line 6001 "syntax.c"
			}
			/* END OF ACTION: signed_nat2 */
		}
		break;
	case 98:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 6015 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 6024 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 100:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 6039 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 6048 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 62:
		{
			/* BEGINNING OF ACTION: signed_nat4 */
			{
#line 1782 "syntax.act"

    o_make_signed_nat(out_tdfbool(0), out_tdfint32(cLINE));
#line 6060 "syntax.c"
			}
			/* END OF ACTION: signed_nat4 */
			ADVANCE_LEXER;
		}
		break;
	case 10:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			/* BEGINNING OF ACTION: signed_nat7_dec */
			{
#line 1794 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
    if (strcmp(lex_v.val.name, "+"))fail("Only + or - on NATs");
#line 6077 "syntax.c"
			}
			/* END OF ACTION: signed_nat7_dec */
			ADVANCE_LEXER;
			ZRnat__not__int ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: signed_nat8 */
			{
#line 1799 "syntax.act"

    RESET_TDF((ZIb));
    o_snat_from_nat(o_false, append_TDF(&(ZIa),1));
#line 6092 "syntax.c"
			}
			/* END OF ACTION: signed_nat8 */
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
ZRlabset__opt(void)
{
	switch (CURRENT_TERMINAL) {
	default:
		{
			/* BEGINNING OF ACTION: lset_o1 */
			{
#line 1452 "syntax.act"

    TDF * hold;
    SET_TDF(hold, &optlab);
    if (defaultlab==-1)defaultlab = next_label();
    o_make_label(out_tdfint32(UL(defaultlab)));
    RESET_TDF(hold);
#line 6123 "syntax.c"
			}
			/* END OF ACTION: lset_o1 */
		}
		break;
	case 24:
		{
			PTR_TDF ZIa;

			/* BEGINNING OF ACTION: lset_o2_dec */
			{
#line 1455 "syntax.act"

    SET_TDF((ZIa), &optlab);
    g_labdec = (Labdec*)0;
    if (defaultlab != -1) { fail("This conditional uses a default jump"); }
#line 6139 "syntax.c"
			}
			/* END OF ACTION: lset_o2_dec */
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
			/* BEGINNING OF ACTION: lset_o3 */
			{
#line 1467 "syntax.act"

    if (g_labdec != (Labdec*)0) {
	if (g_labdec->declared) {
	    fail("Label %s set twice", g_labdec->idname.id);
	}
	g_labdec->declared = 1;
    }
    RESET_TDF((ZIa));
#line 6165 "syntax.c"
			}
			/* END OF ACTION: lset_o3 */
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
ZRkeep__item(void)
{
	switch (CURRENT_TERMINAL) {
	case 2: case 5: case 9: case 15:
	case 18: case 40: case 43: case 49:
	case 60: case 71: case 75: case 91:
	case 96: case 100: case 111: case 120:
	case 128:
		{
			/* BEGINNING OF ACTION: keep1 */
			{
#line 1261 "syntax.act"

    Tokdec * k = lex_v.val.tokname;
    k->iskept = 1;
#line 6195 "syntax.c"
			}
			/* END OF ACTION: keep1 */
			/* BEGINNING OF INLINE: tok_item */
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
			/* END OF INLINE: tok_item */
		}
		break;
	case 54:
		{
			/* BEGINNING OF ACTION: keep2 */
			{
#line 1275 "syntax.act"

    char * n = lex_v.val.name;
    Tagdec * t = find_tag(n);
    if (t != (Tagdec*)0) {
	t->iskept = 1;
     } else {
	Al_tagdec * a = find_al_tag(n);
	if (a == (Al_tagdec*)0) {
	    fail("Ident %s not declared",n);
	}
	a->iskept = 1;
    }
#line 6310 "syntax.c"
			}
			/* END OF ACTION: keep2 */
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
ZRstruct__def(void)
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
		/* BEGINNING OF ACTION: struct1_dec */
		{
#line 1873 "syntax.act"

    char * n = lex_v.val.name;
    (ZIa) = find_tok(n);
    SELECT_UNIT(tokdef_unit);
    if ((ZIa)!= (Tokdec*)0)fail("Struct name %s must be unique", n);
    (ZIa) = xmalloc(sizeof *(ZIa)); NEW_IDNAME((ZIa)->idname, n, tok_ent);
    (ZIa)->sort.ressort.sort = shape_sort; (ZIa)->sort.pars = (Tokpar*)0;
    (ZIa)->isdeffed = 1; (ZIa)->isused=0; (ZIa)->iskept=0;
    g_lastfield = -1;
#line 6355 "syntax.c"
		}
		/* END OF ACTION: struct1_dec */
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
		/* BEGINNING OF ACTION: struct2 */
		{
#line 1883 "syntax.act"

    o_make_tokdef(out_tdfint32(LOCNAME((ZIa)->idname)), {},
	o_token_def(o_shape, {},
	    o_compound(o_offset_add(
		o_exp_apply_token(
		    o_make_tok(out_tdfint32(UL(g_lastfield))),{}),
		o_shape_offset(append_TDF(&g_lastshape, 1))))))
    INC_LIST;
    (ZIa)->next = tokdecs;
    tokdecs = (ZIa);
#line 6390 "syntax.c"
		}
		/* END OF ACTION: struct2 */
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
ZRnonst__shape__body(void)
{
	switch (CURRENT_TERMINAL) {
	case 83:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shptr1_dec */
			{
#line 1743 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 6422 "syntax.c"
			}
			/* END OF ACTION: shptr1_dec */
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: shapeptr2 */
			{
#line 1712 "syntax.act"

    RESET_TDF((ZIb));
    o_pointer(o_alignment(append_TDF(&(ZIa),1)));
#line 6436 "syntax.c"
			}
			/* END OF ACTION: shapeptr2 */
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

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 6460 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 6469 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 96:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 6484 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 6493 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
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
read_tag(void)
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
			/* BEGINNING OF INLINE: tag */
			goto ZL2_tag;
			/* END OF INLINE: tag */
		}
		UNREACHED;
	case 109:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 6538 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 6547 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 111:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 6562 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 6571 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
		}
		break;
	case 54:
		{
			/* BEGINNING OF ACTION: tag1 */
			{
#line 1904 "syntax.act"

    char * n =lex_v.val.name;
    Tagdec * x = find_tag(n);
    if (x == (Tagdec*)0) { fail("Ident %s not declared", n); }
    x->isused = 1;
    make_tag(&x->idname.name);
#line 6587 "syntax.c"
			}
			/* END OF ACTION: tag1 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 6606 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRvariety__opt(void)
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
			/* BEGINNING OF ACTION: varietyopt1 */
			{
#line 2386 "syntax.act"

    /* unsigned char */
    o_var_limits(
	o_make_signed_nat(out_tdfbool(0), out_tdfint32(UL(0))),
	o_make_signed_nat(out_tdfbool(0), out_tdfint32(UL(255))));
#line 6642 "syntax.c"
			}
			/* END OF ACTION: varietyopt1 */
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
read_nat_option(void)
{
	switch (CURRENT_TERMINAL) {
	case 22: case 55: case 69: case 70:
	case 71:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			/* BEGINNING OF ACTION: natopt_dec */
			{
#line 1498 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 6671 "syntax.c"
			}
			/* END OF ACTION: natopt_dec */
			read_nat ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: natopt1 */
			{
#line 1493 "syntax.act"

    RESET_TDF((ZIb));
    OPTION(append_TDF(&(ZIa),1));
#line 6685 "syntax.c"
			}
			/* END OF ACTION: natopt1 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 6703 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRsortname__list__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 1: case 4: case 8: case 14:
	case 17: case 39: case 42: case 48:
	case 59: case 70: case 74: case 90:
	case 95: case 99: case 105: case 110:
	case 116: case 119: case 127:
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
			/* BEGINNING OF ACTION: empty_snl */
			{
#line 474 "syntax.act"

    g_tokpars = (Tokpar*)0;
#line 6733 "syntax.c"
			}
			/* END OF ACTION: empty_snl */
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
read_floating_variety(void)
{
ZL2_floating__variety:;
	switch (CURRENT_TERMINAL) {
	case 32:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: fvardouble */
			{
#line 1026 "syntax.act"

    o_flvar_parms(o_make_nat(out_tdfint32(UL(2))),
		  o_make_nat(out_tdfint32(UL(MANT_DOUBLE))),
		  o_make_nat(out_tdfint32(UL(MINEXP_DOUBLE))),
		  o_make_nat(out_tdfint32(UL(MAXEXP_DOUBLE))));
#line 6763 "syntax.c"
			}
			/* END OF ACTION: fvardouble */
		}
		break;
	case 46:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: fvarfloat */
			{
#line 1033 "syntax.act"

    o_flvar_parms(o_make_nat(out_tdfint32(UL(2))),
		  o_make_nat(out_tdfint32(UL(MANT_FLOAT))),
		  o_make_nat(out_tdfint32(UL(MINEXP_FLOAT))),
		  o_make_nat(out_tdfint32(UL(MAXEXP_FLOAT))));
#line 6779 "syntax.c"
			}
			/* END OF ACTION: fvarfloat */
		}
		break;
	case 48:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 658 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: floating_variety */
						goto ZL2_floating__variety;
						/* END OF INLINE: floating_variety */
					}
					UNREACHED;
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 6811 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
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
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 6839 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
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
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 6859 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_floating_variety ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: fvar1 */
						{
#line 1016 "syntax.act"

    RESET_TDF((ZId));
    o_flvar_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		 append_TDF(&(ZIc),1));
#line 6874 "syntax.c"
						}
						/* END OF ACTION: fvar1 */
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
			/* END OF INLINE: 658 */
		}
		break;
	case 47:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 6902 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 6911 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 49:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 6926 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 6935 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 6953 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRtagshacc(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		TDF ZIa;
		PTR_TDF ZIb;
		PTR_Tagdec ZIc;
		int ZId;

		/* BEGINNING OF ACTION: tagsa1_dec */
		{
#line 2096 "syntax.act"

    /* (ZId) uninitialised */
    char * n =lex_v.val.name;
    (ZIc) = find_tag(n);
    if ((ZIc) != (Tagdec*)0)fail("Ident %s already declared", n);
    (ZIc) = xmalloc(sizeof *(ZIc));
    (ZIc)->hassh = 2; (ZIc)->isvar =1; (ZIc)->isdeffed = 1; (ZIc)->iskept=0;
    NEW_IDNAME((ZIc)->idname, n, tag_ent);
    g_has_vis =0;
    SET_TDF((ZIb), &(ZIa));
#line 6984 "syntax.c"
		}
		/* END OF ACTION: tagsa1_dec */
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
		/* BEGINNING OF ACTION: tagshacc2 */
		{
#line 2108 "syntax.act"

    RESET_TDF((ZIb));
    SET_TDF((ZIb), &(ZIc)->sh.tdfsh);
    (ZId) = g_has_vis;
#line 7006 "syntax.c"
		}
		/* END OF ACTION: tagshacc2 */
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
		/* BEGINNING OF ACTION: tagshacc3 */
		{
#line 2114 "syntax.act"

    RESET_TDF((ZIb));
    o_make_tagshacc(append_TDF(&(ZIc)->sh.tdfsh, 0),
	if ((ZIa).no != 0) {OPTION(append_TDF(&(ZIa),1));},
	make_tag(&(ZIc)->idname.name));
    if ((ZId)) {
	Tagdec * y = xmalloc(sizeof *y);
	*y = *(ZIc);
	y->next = tagdecs;
	tagdecs = y;
    }
    (ZIc)->next = localdecs;
    localdecs = (ZIc);
#line 7037 "syntax.c"
		}
		/* END OF ACTION: tagshacc3 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRelement__list__opt(void)
{
ZL2_element__list__opt:;
	switch (CURRENT_TERMINAL) {
	case 6: case 26: case 27: case 53:
	case 61: case 81: case 106: case 108:
	case 113: case 114: case 124: case 125:
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
			/* BEGINNING OF INLINE: element_list_opt */
			goto ZL2_element__list__opt;
			/* END OF INLINE: element_list_opt */
		}
		UNREACHED;
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
read_nat(void)
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
			/* BEGINNING OF ACTION: nat2 */
			{
#line 1490 "syntax.act"

    o_make_nat(out_tdfint32(intvalue));
#line 7100 "syntax.c"
			}
			/* END OF ACTION: nat2 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 7127 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

void
read_alignment(void)
{
ZL2_alignment:;
	switch (CURRENT_TERMINAL) {
	case 8:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 666 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: alignment */
						goto ZL2_alignment;
						/* END OF INLINE: alignment */
					}
					UNREACHED;
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 7166 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
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
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 7193 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
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
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 7213 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_alignment ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: alignment1 */
						{
#line 289 "syntax.act"

    RESET_TDF((ZId));
    o_alignment_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		     append_TDF(&(ZIc),1));
#line 7228 "syntax.c"
						}
						/* END OF ACTION: alignment1 */
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
			/* END OF INLINE: 666 */
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

			/* BEGINNING OF ACTION: alment2_dec */
			{
#line 300 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 7273 "syntax.c"
			}
			/* END OF ACTION: alment2_dec */
			read_al_tag ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: alignment3 */
			{
#line 295 "syntax.act"

    RESET_TDF((ZIb));
    o_obtain_al_tag(append_TDF(&(ZIa), 1));
#line 7287 "syntax.c"
			}
			/* END OF ACTION: alignment3 */
		}
		break;
	case 7:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 7301 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 7310 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 9:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 7325 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 7334 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 7352 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRvarpar__opt(void)
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
			/* BEGINNING OF ACTION: vpar1 */
			{
#line 2398 "syntax.act"

    current_TDF->no=1;
#line 7375 "syntax.c"
			}
			/* END OF ACTION: vpar1 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: vpar2 */
			{
#line 2402 "syntax.act"

    current_TDF->no=0;
#line 7387 "syntax.c"
			}
			/* END OF ACTION: vpar2 */
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
ZRkeep__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
ZL2_keep__list:;
	{
		ZRkeep__item ();
		/* BEGINNING OF INLINE: 683 */
		{
			switch (CURRENT_TERMINAL) {
			case 25:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: keep_list */
					goto ZL2_keep__list;
					/* END OF INLINE: keep_list */
				}
				UNREACHED;
			case 130:
				RESTORE_LEXER;
				goto ZL1;
			default:
				break;
			}
		}
		/* END OF INLINE: 683 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRproc__def(void)
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
		/* BEGINNING OF ACTION: tag_def7_dec */
		{
#line 2050 "syntax.act"

    /* (ZIa) uninitialised */
    (ZIe) =lex_v.val.name;
    (ZId) = find_tag((ZIe));
    SELECT_UNIT(tagdef_unit);
    if ((ZId)!= (Tagdec*)0) {
	if ((ZId)->isdeffed && !(ZId)->iscommon)fail("Tag %s defined twice", (ZIe));
	if ((ZId)->isvar)fail("Tag %s declared as variable", (ZIe));
	(ZIf) = 1;
    } else {
	(ZId) = xmalloc(sizeof *(ZId));
	(ZId)->hassh = 0; (ZId)->isvar=0; (ZId)->iskept=0; (ZId)->iscommon = 0;
	(ZId)->isused = 0;
	NEW_IDNAME((ZId)->idname, (ZIe), tag_ent);
	(ZIf) = 0;
    }
    SET_TDF((ZIc), &(ZIb));
#line 7477 "syntax.c"
		}
		/* END OF ACTION: tag_def7_dec */
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
		/* BEGINNING OF ACTION: proc_def1 */
		{
#line 1585 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIa));
#line 7500 "syntax.c"
		}
		/* END OF ACTION: proc_def1 */
		ZRproc__def__body ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: proc_def2 */
		{
#line 1590 "syntax.act"

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
#line 7527 "syntax.c"
		}
		/* END OF ACTION: proc_def2 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

void
read_error_code_list(void)
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
		/* BEGINNING OF ACTION: errc1 */
		{
#line 482 "syntax.act"

    current_TDF->no = 1;
#line 7554 "syntax.c"
		}
		/* END OF ACTION: errc1 */
		ZR625 ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 7571 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRcallee__var__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 31:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cevaropt2 */
			{
#line 394 "syntax.act"

    g_ce_v = 1;
#line 7589 "syntax.c"
			}
			/* END OF ACTION: cevaropt2 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: cevaropt1 */
			{
#line 390 "syntax.act"

    g_ce_v = 0;
#line 7601 "syntax.c"
			}
			/* END OF ACTION: cevaropt1 */
		}
		break;
	case 130:
		return;
	}
}

static void
ZRtag__dec(void)
{
	switch (CURRENT_TERMINAL) {
	case 27:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;
			PTR_Tagdec ZId;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tag_dec1_dec */
			{
#line 1907 "syntax.act"

    /* (ZIb) uninitialised */
    char * n =lex_v.val.name;
    (ZId) = find_tag(n);
    if ((ZId) != (Tagdec*)0)fail("Tag %s declared twice", n);
    SELECT_UNIT(tagdec_unit);
    (ZId) = xmalloc(sizeof *(ZId)); NEW_IDNAME((ZId)->idname, n, tag_ent);
    (ZId)->isdeffed = 0; (ZId)->hassh = 1; (ZId)->iskept=0; (ZId)->iscommon=0;
    (ZId)->isused = 0;
    SET_TDF((ZIc), &(ZIa));
#line 7636 "syntax.c"
			}
			/* END OF ACTION: tag_dec1_dec */
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
			/* BEGINNING OF ACTION: tag_dec6 */
			{
#line 1960 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 7657 "syntax.c"
			}
			/* END OF ACTION: tag_dec6 */
			ZRsignature__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_dec2 */
			{
#line 1919 "syntax.act"

    g_shtokname = &(ZId)->sh.shtok;
#line 7670 "syntax.c"
			}
			/* END OF ACTION: tag_dec2 */
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
			/* BEGINNING OF ACTION: tag_dec5 */
			{
#line 1947 "syntax.act"

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
#line 7699 "syntax.c"
			}
			/* END OF ACTION: tag_dec5 */
		}
		break;
	case 53:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;
			PTR_Tagdec ZId;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tag_dec1_dec */
			{
#line 1907 "syntax.act"

    /* (ZIb) uninitialised */
    char * n =lex_v.val.name;
    (ZId) = find_tag(n);
    if ((ZId) != (Tagdec*)0)fail("Tag %s declared twice", n);
    SELECT_UNIT(tagdec_unit);
    (ZId) = xmalloc(sizeof *(ZId)); NEW_IDNAME((ZId)->idname, n, tag_ent);
    (ZId)->isdeffed = 0; (ZId)->hassh = 1; (ZId)->iskept=0; (ZId)->iscommon=0;
    (ZId)->isused = 0;
    SET_TDF((ZIc), &(ZIa));
#line 7725 "syntax.c"
			}
			/* END OF ACTION: tag_dec1_dec */
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
			/* BEGINNING OF ACTION: tag_dec6 */
			{
#line 1960 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 7746 "syntax.c"
			}
			/* END OF ACTION: tag_dec6 */
			ZRsignature__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_dec2 */
			{
#line 1919 "syntax.act"

    g_shtokname = &(ZId)->sh.shtok;
#line 7759 "syntax.c"
			}
			/* END OF ACTION: tag_dec2 */
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
			/* BEGINNING OF ACTION: tag_dec4 */
			{
#line 1935 "syntax.act"

    RESET_TDF((ZIc));
    o_make_id_tagdec(out_tdfint32(LOCNAME((ZId)->idname)),
	if ((ZIa).no !=0) { OPTION(append_TDF(&(ZIa), 1)); },
	if ((ZIb).no !=0) { OPTION(append_TDF(&(ZIb), 1)); },
	o_shape_apply_token(make_tok(&(ZId)->sh.shtok), {}));
    INC_LIST;
    (ZId)->next = tagdecs;
    (ZId)->isvar = 0;
    tagdecs = (ZId);
#line 7787 "syntax.c"
			}
			/* END OF ACTION: tag_dec4 */
		}
		break;
	case 125:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;
			PTR_Tagdec ZId;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tag_dec1_dec */
			{
#line 1907 "syntax.act"

    /* (ZIb) uninitialised */
    char * n =lex_v.val.name;
    (ZId) = find_tag(n);
    if ((ZId) != (Tagdec*)0)fail("Tag %s declared twice", n);
    SELECT_UNIT(tagdec_unit);
    (ZId) = xmalloc(sizeof *(ZId)); NEW_IDNAME((ZId)->idname, n, tag_ent);
    (ZId)->isdeffed = 0; (ZId)->hassh = 1; (ZId)->iskept=0; (ZId)->iscommon=0;
    (ZId)->isused = 0;
    SET_TDF((ZIc), &(ZIa));
#line 7813 "syntax.c"
			}
			/* END OF ACTION: tag_dec1_dec */
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
			/* BEGINNING OF ACTION: tag_dec6 */
			{
#line 1960 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 7834 "syntax.c"
			}
			/* END OF ACTION: tag_dec6 */
			ZRsignature__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: tag_dec2 */
			{
#line 1919 "syntax.act"

    g_shtokname = &(ZId)->sh.shtok;
#line 7847 "syntax.c"
			}
			/* END OF ACTION: tag_dec2 */
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
			/* BEGINNING OF ACTION: tag_dec3 */
			{
#line 1923 "syntax.act"

    RESET_TDF((ZIc));
    o_make_var_tagdec(out_tdfint32(LOCNAME((ZId)->idname)),
	if ((ZIa).no !=0) { OPTION(append_TDF(&(ZIa), 1)); },
	if ((ZIb).no !=0) { OPTION(append_TDF(&(ZIb), 1)); },
	o_shape_apply_token(make_tok(&(ZId)->sh.shtok), {}));
    INC_LIST;
    (ZId)->next = tagdecs;
    (ZId)->isvar = 1;
    tagdecs = (ZId);
#line 7875 "syntax.c"
			}
			/* END OF ACTION: tag_dec3 */
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
ZRtag__intro(void)
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
			/* BEGINNING OF ACTION: intro1_dec */
			{
#line 1189 "syntax.act"

    /* (ZIb), (ZIe) uninitialised */
    char* n = lex_v.val.name;
    (ZId) = find_tag(n);
    if ((ZId) != (Tagdec*)0) { fail("Tag %s declared twice", n); }
    (ZId) = xmalloc(sizeof *(ZId)); (ZId)->isdeffed = 1; (ZId)->hassh=0; (ZId)->iskept=0;
    NEW_IDNAME((ZId)->idname, n, tag_ent);
    g_has_vis = 0;
    SET_TDF((ZIc), &(ZIa));
#line 7916 "syntax.c"
			}
			/* END OF ACTION: intro1_dec */
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
			/* BEGINNING OF ACTION: intro2 */
			{
#line 1200 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
    (ZIe) = g_has_vis;
#line 7938 "syntax.c"
			}
			/* END OF ACTION: intro2 */
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
			/* BEGINNING OF ACTION: intro5 */
			{
#line 1227 "syntax.act"

    RESET_TDF((ZIc));
    intro_acc = (ZIa);
    intro_init = (ZIb);
    (ZId)->isvar=0;
    if ((ZIe)) {
	Tagdec * y = xmalloc(sizeof *y);
	*y = *(ZId);
	y->next = tagdecs;
	tagdecs = y;
    }
    (ZId)->next = localdecs;
    localdecs = (ZId);
#line 7969 "syntax.c"
			}
			/* END OF ACTION: intro5 */
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
			/* BEGINNING OF ACTION: intro1_dec */
			{
#line 1189 "syntax.act"

    /* (ZIb), (ZIe) uninitialised */
    char* n = lex_v.val.name;
    (ZId) = find_tag(n);
    if ((ZId) != (Tagdec*)0) { fail("Tag %s declared twice", n); }
    (ZId) = xmalloc(sizeof *(ZId)); (ZId)->isdeffed = 1; (ZId)->hassh=0; (ZId)->iskept=0;
    NEW_IDNAME((ZId)->idname, n, tag_ent);
    g_has_vis = 0;
    SET_TDF((ZIc), &(ZIa));
#line 7995 "syntax.c"
			}
			/* END OF ACTION: intro1_dec */
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
read_exp(void)
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

		/* BEGINNING OF ACTION: exphold1_dec */
		{
#line 694 "syntax.act"

    (ZIc) = (current_TDF->first == current_TDF->last &&
	      current_TDF->first->usage == 0 &&
	      current_TDF->first->offst == 0);
    (ZId) = cLINE;
    (ZIe) = bind;
    if (!(ZIc) || line_no_tok != -1) { SET_TDF((ZIb), &(ZIa)); }
#line 8047 "syntax.c"
		}
		/* END OF ACTION: exphold1_dec */
		ZRexp__body ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: exphold2 */
		{
#line 703 "syntax.act"

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
#line 8075 "syntax.c"
		}
		/* END OF ACTION: exphold2 */
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 8087 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRtag__def(void)
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
			/* BEGINNING OF ACTION: tag_def1_dec */
			{
#line 1986 "syntax.act"

    /* (ZIa) uninitialised */
    (ZIe) =lex_v.val.name;
    (ZId) = find_tag((ZIe));
    SELECT_UNIT(tagdef_unit);
    if ((ZId)!= (Tagdec*)0) {
	if ((ZId)->isdeffed && !(ZId)->iscommon)fail("Tag %s defined twice", (ZIe));
	if (!(ZId)->isvar)fail("Tag %s declared as non-variable", (ZIe));
	(ZIf) = 1;
    } else {
	(ZId) = xmalloc(sizeof *(ZId));
	(ZId)->hassh = 0; (ZId)->isvar=1; (ZId)->iskept=0; (ZId)->iscommon = 0;
	(ZId)->isused=0;
	NEW_IDNAME((ZId)->idname, (ZIe), tag_ent);
	(ZIf)=0;
    }
    SET_TDF((ZIc), &(ZIb));
#line 8127 "syntax.c"
			}
			/* END OF ACTION: tag_def1_dec */
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
			/* BEGINNING OF ACTION: tag_def7_dec */
			{
#line 2050 "syntax.act"

    /* (ZIa) uninitialised */
    (ZIe) =lex_v.val.name;
    (ZId) = find_tag((ZIe));
    SELECT_UNIT(tagdef_unit);
    if ((ZId)!= (Tagdec*)0) {
	if ((ZId)->isdeffed && !(ZId)->iscommon)fail("Tag %s defined twice", (ZIe));
	if ((ZId)->isvar)fail("Tag %s declared as variable", (ZIe));
	(ZIf) = 1;
    } else {
	(ZId) = xmalloc(sizeof *(ZId));
	(ZId)->hassh = 0; (ZId)->isvar=0; (ZId)->iskept=0; (ZId)->iscommon = 0;
	(ZId)->isused = 0;
	NEW_IDNAME((ZId)->idname, (ZIe), tag_ent);
	(ZIf) = 0;
    }
    SET_TDF((ZIc), &(ZIb));
#line 8175 "syntax.c"
			}
			/* END OF ACTION: tag_def7_dec */
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
			/* BEGINNING OF ACTION: tag_def1_dec */
			{
#line 1986 "syntax.act"

    /* (ZIa) uninitialised */
    (ZIe) =lex_v.val.name;
    (ZId) = find_tag((ZIe));
    SELECT_UNIT(tagdef_unit);
    if ((ZId)!= (Tagdec*)0) {
	if ((ZId)->isdeffed && !(ZId)->iscommon)fail("Tag %s defined twice", (ZIe));
	if (!(ZId)->isvar)fail("Tag %s declared as non-variable", (ZIe));
	(ZIf) = 1;
    } else {
	(ZId) = xmalloc(sizeof *(ZId));
	(ZId)->hassh = 0; (ZId)->isvar=1; (ZId)->iskept=0; (ZId)->iscommon = 0;
	(ZId)->isused=0;
	NEW_IDNAME((ZId)->idname, (ZIe), tag_ent);
	(ZIf)=0;
    }
    SET_TDF((ZIc), &(ZIb));
#line 8225 "syntax.c"
			}
			/* END OF ACTION: tag_def1_dec */
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
			/* BEGINNING OF ACTION: tgdef10_dec */
			{
#line 2150 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIg));
#line 8246 "syntax.c"
			}
			/* END OF ACTION: tgdef10_dec */
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
			/* BEGINNING OF ACTION: tgdef11_dec */
			{
#line 2155 "syntax.act"

    (ZIh) = lex_v.val.name;
    if ((ZId)->hassh)fail("Two declaration shapes for %s", (ZIe));
    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIa));
    o_make_nof_int(append_TDF(&(ZIg), 0),
	o_make_string(out_tdfstring_bytes((ZIh), 8, UI(strlen((ZIh)) +1))));
#line 8270 "syntax.c"
			}
			/* END OF ACTION: tgdef11_dec */
			switch (CURRENT_TERMINAL) {
			case 85:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tag_def12 */
			{
#line 1969 "syntax.act"

    RESET_TDF((ZIc));
    o_make_var_tagdef(out_tdfint32(UL(local_name(&(ZId)->idname.name, tag_ent))),
	{}, {}, append_TDF(&(ZIa), 1));
    INC_LIST;
    SELECT_UNIT(tagdec_unit);
    if (!(ZIf)) {
	o_make_var_tagdec(out_tdfint32(UL(non_local(&(ZId)->idname.name,tag_ent))),
	    {}, {},
	    o_nof(o_make_nat(out_tdfint32(UL(strlen((ZIh)) +1))),
		o_integer(append_TDF(&(ZIg), 0))));
       INC_LIST;
    }
    (ZId)->isdeffed=1;
    if (!(ZIf)) { (ZId)->next = tagdecs; tagdecs = (ZId); }
#line 8298 "syntax.c"
			}
			/* END OF ACTION: tag_def12 */
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
			/* BEGINNING OF ACTION: tag_def1_dec */
			{
#line 1986 "syntax.act"

    /* (ZIa) uninitialised */
    (ZIe) =lex_v.val.name;
    (ZId) = find_tag((ZIe));
    SELECT_UNIT(tagdef_unit);
    if ((ZId)!= (Tagdec*)0) {
	if ((ZId)->isdeffed && !(ZId)->iscommon)fail("Tag %s defined twice", (ZIe));
	if (!(ZId)->isvar)fail("Tag %s declared as non-variable", (ZIe));
	(ZIf) = 1;
    } else {
	(ZId) = xmalloc(sizeof *(ZId));
	(ZId)->hassh = 0; (ZId)->isvar=1; (ZId)->iskept=0; (ZId)->iscommon = 0;
	(ZId)->isused=0;
	NEW_IDNAME((ZId)->idname, (ZIe), tag_ent);
	(ZIf)=0;
    }
    SET_TDF((ZIc), &(ZIb));
#line 8333 "syntax.c"
			}
			/* END OF ACTION: tag_def1_dec */
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
ZRotagexp__list__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 10: case 19: case 22: case 28:
	case 41: case 42: case 43: case 44:
	case 45: case 52: case 54: case 55:
	case 58: case 61: case 62: case 68:
	case 76: case 77: case 78: case 79:
	case 81: case 82: case 84: case 85:
	case 86: case 88: case 98: case 99:
	case 100: case 102: case 103: case 104:
	case 105: case 107: case 109: case 110:
	case 111: case 124:
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
			/* BEGINNING OF ACTION: otagel_opt1 */
			{
#line 1557 "syntax.act"

    current_TDF->no = 0;
#line 8391 "syntax.c"
			}
			/* END OF ACTION: otagel_opt1 */
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
ZRtok__formal__list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		PTR_Tokdec ZIa;

		/* BEGINNING OF ACTION: tok_fml1_dec */
		{
#line 2296 "syntax.act"

    char * n = lex_v.val.name;
    (ZIa) = find_tok(n);
    if ((ZIa)!= (Tokdec*)0)fail("Token parameter name %s must be unique", n);
    (ZIa) = xmalloc(sizeof *(ZIa)); NEW_IDNAME((ZIa)->idname, n, tok_ent);
    (ZIa)->isdeffed = 1; (ZIa)->isused = 0; (ZIa)->iskept=0;
    (ZIa)->next = (Tokdec*)0;
#line 8424 "syntax.c"
		}
		/* END OF ACTION: tok_fml1_dec */
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
		/* BEGINNING OF ACTION: tok_fml2 */
		{
#line 2304 "syntax.act"

    (ZIa)->sort.ressort = g_sname;
    (ZIa)->sort.pars = (Tokpar*)0;  /* no pars in formal pars */
    g_tokformals = (ZIa);
#line 8453 "syntax.c"
		}
		/* END OF ACTION: tok_fml2 */
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
ZRuntidy__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 23:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: untidy4 */
			{
#line 2334 "syntax.act"

    g_unt = 2;
#line 8480 "syntax.c"
			}
			/* END OF ACTION: untidy4 */
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
			/* BEGINNING OF ACTION: untidy1 */
			{
#line 2322 "syntax.act"

    g_unt = 0;
#line 8502 "syntax.c"
			}
			/* END OF ACTION: untidy1 */
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
ZRcaller__var__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 31:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: crvaropt2 */
			{
#line 417 "syntax.act"

    g_cr_v = 1;
#line 8528 "syntax.c"
			}
			/* END OF ACTION: crvaropt2 */
		}
		break;
	default:
		{
			/* BEGINNING OF ACTION: crvaropt1 */
			{
#line 413 "syntax.act"

    g_cr_v = 0;
#line 8540 "syntax.c"
			}
			/* END OF ACTION: crvaropt1 */
		}
		break;
	case 130:
		return;
	}
}

static void
ZRproc__def__body(void)
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
			/* BEGINNING OF ACTION: gproc1_dec */
			{
#line 1123 "syntax.act"

    /* (ZIb), (ZIc), (ZId) uninitialised */
    /* (ZIf), (ZIg) (ZIh) uninitialised */
    (ZIi) = localdecs;
    (ZIj) = labdecs;
    localdecs = (Tagdec*)0;
    labdecs = (Labdec *)0;
    SET_TDF((ZIe), &(ZIa));
#line 8579 "syntax.c"
			}
			/* END OF ACTION: gproc1_dec */
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: gproc2 */
			{
#line 1133 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIb));
#line 8593 "syntax.c"
			}
			/* END OF ACTION: gproc2 */
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
			/* BEGINNING OF ACTION: gproc3 */
			{
#line 1138 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIc));
    (ZIf) = g_cr_v;
#line 8616 "syntax.c"
			}
			/* END OF ACTION: gproc3 */
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
			/* BEGINNING OF ACTION: gproc4 */
			{
#line 1144 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZId));
    (ZIg) = g_ce_v;
#line 8639 "syntax.c"
			}
			/* END OF ACTION: gproc4 */
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
			/* BEGINNING OF ACTION: gproc5 */
			{
#line 1150 "syntax.act"

    (ZIh) = g_unt;
#line 8659 "syntax.c"
			}
			/* END OF ACTION: gproc5 */
			ZRclosed__exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: gproc6 */
			{
#line 1154 "syntax.act"

    RESET_TDF((ZIe));
    o_make_general_proc(append_TDF(&(ZIa),1),
			do_procprops((ZIf)+2*(ZIg)+4*(ZIh)),
			{ append_TDF(&(ZIb),1);
			  current_TDF->no = (ZIb).no;},
			{ append_TDF(&(ZIc),1);
			  current_TDF->no = (ZIc).no;},
			append_TDF(&(ZId),1))
    while (labdecs != (Labdec *)0) {
	if (!labdecs->declared) {
	    fail("Label %s not declared", labdecs->idname.id);
	}
	labdecs = labdecs->next;
    }
    localdecs = (ZIi);
    labdecs = (ZIj);
#line 8687 "syntax.c"
			}
			/* END OF ACTION: gproc6 */
		}
		break;
	case 21: case 32: case 46: case 56:
	case 64: case 83: case 94: case 95:
	case 96: case 97: case 101: case 121:
		{
			TDF ZIa;
			TDF ZIb;
			TDF ZIc;
			TDF ZId;
			PTR_TDF ZIe;
			PTR_Tagdec ZIf;
			PTR_Labdec ZIg;

			/* BEGINNING OF ACTION: expproc1_dec */
			{
#line 763 "syntax.act"

    /* (ZIa), (ZIb), (ZIc) uninitialised */
    (ZIf) = localdecs;
    (ZIg) = labdecs;
    localdecs = (Tagdec*)0;
    labdecs = (Labdec *)0;
    SET_TDF((ZIe), &(ZId));
#line 8714 "syntax.c"
			}
			/* END OF ACTION: expproc1_dec */
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expproc2 */
			{
#line 772 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIa))
#line 8728 "syntax.c"
			}
			/* END OF ACTION: expproc2 */
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
			/* BEGINNING OF ACTION: expproc3 */
			{
#line 777 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIb));
#line 8749 "syntax.c"
			}
			/* END OF ACTION: expproc3 */
			ZRvarintro__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expproc4 */
			{
#line 782 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIc));
#line 8763 "syntax.c"
			}
			/* END OF ACTION: expproc4 */
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
			/* BEGINNING OF ACTION: expproc5 */
			{
#line 787 "syntax.act"

    RESET_TDF((ZIe));
    o_make_proc(append_TDF(&(ZId),1),
		{ append_TDF(&(ZIa),1); current_TDF->no = (ZIa).no;},
		if ((ZIb).no !=0) {OPTION(append_TDF(&(ZIb),1)); },
		append_TDF(&(ZIc),1);)
    while (labdecs != (Labdec *)0) {
	if (!labdecs->declared) {
	    fail("Label %s not declared", labdecs->idname.id);
	}
	labdecs = labdecs->next;
    }
    localdecs = (ZIf);
    labdecs = (ZIg);
#line 8795 "syntax.c"
			}
			/* END OF ACTION: expproc5 */
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
ZRlabelled__list(void)
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
		/* BEGINNING OF ACTION: llist1_dec */
		{
#line 1418 "syntax.act"

    (ZIb) = current_TDF;
    INIT_TDF(&(ZIa));
    current_TDF = &g_lablist;
#line 8835 "syntax.c"
		}
		/* END OF ACTION: llist1_dec */
		read_label ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: llist2 */
		{
#line 1430 "syntax.act"

    if (g_labdec != (Labdec*)0) {
	if (g_labdec->declared) {
	    fail("Label %s set twice", g_labdec->idname.id);
	}
	g_labdec->declared = 1;
    }
    current_TDF = &(ZIa);
#line 8854 "syntax.c"
		}
		/* END OF ACTION: llist2 */
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
		/* BEGINNING OF ACTION: llist5 */
		{
#line 1442 "syntax.act"

    RESET_TDF((ZIb));
    append_TDF(&(ZIa), 1);
#line 8875 "syntax.c"
		}
		/* END OF ACTION: llist5 */
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
ZRoffset__exp__list(void)
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
ZRbitfield__sign(void)
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
			/* BEGINNING OF ACTION: bvariety2 */
			{
#line 323 "syntax.act"

    if (issigned) { o_true; }
    else { o_false; }
#line 8947 "syntax.c"
			}
			/* END OF ACTION: bvariety2 */
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
ZRtok__dec(void)
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
		/* BEGINNING OF ACTION: tok_dec1_dec */
		{
#line 2190 "syntax.act"

    char *n = lex_v.val.name;
    (ZIc) = find_tok(n);
    if ((ZIc) != (Tokdec *)0)fail("Token %s declared twice", n);
    SELECT_UNIT(tokdec_unit);
    (ZIc) = xmalloc(sizeof *(ZIc));
    NEW_IDNAME((ZIc)->idname, n, tok_ent);
    SET_TDF((ZIb), &(ZIa));
#line 8990 "syntax.c"
		}
		/* END OF ACTION: tok_dec1_dec */
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
		/* BEGINNING OF ACTION: tok_dec2 */
		{
#line 2199 "syntax.act"

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
#line 9048 "syntax.c"
		}
		/* END OF ACTION: tok_dec2 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRexp__comma__list(void)
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
		/* BEGINNING OF ACTION: expl2 */
		{
#line 727 "syntax.act"

    current_TDF->no++;
#line 9076 "syntax.c"
		}
		/* END OF ACTION: expl2 */
		/* BEGINNING OF INLINE: 624 */
		{
			switch (CURRENT_TERMINAL) {
			case 25:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: exp_comma_list */
					goto ZL2_exp__comma__list;
					/* END OF INLINE: exp_comma_list */
				}
				UNREACHED;
			default:
				break;
			}
		}
		/* END OF INLINE: 624 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRexp__body(void)
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
ZRtok__def(void)
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

		/* BEGINNING OF ACTION: tok_def0 */
		{
#line 2213 "syntax.act"

    search_for_toks = 0;
#line 9140 "syntax.c"
		}
		/* END OF ACTION: tok_def0 */
		switch (CURRENT_TERMINAL) {
		case 114:
			break;
		default:
			goto ZL1;
		}
		ADVANCE_LEXER;
		/* BEGINNING OF ACTION: tok_def1_dec */
		{
#line 2217 "syntax.act"

    char *n = lex_v.val.name;
    (ZId) = find_tok(n);
    (ZIa) = g_tok_defn;
    SELECT_UNIT(tokdef_unit);
    search_for_toks = 1;
    if ((ZId) != (Tokdec *)0) {
	if ((ZId)->isdeffed)fail("Token %s defined twice", n);
	(ZIe) = 1;
    } else {
	(ZId) = xmalloc(sizeof *(ZId));
	NEW_IDNAME((ZId)->idname, n, tok_ent);
	(ZIe) = 0;
    }
    SET_TDF((ZIc), &(ZIb));
#line 9168 "syntax.c"
		}
		/* END OF ACTION: tok_def1_dec */
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
		/* BEGINNING OF ACTION: tok_def2 */
		{
#line 2233 "syntax.act"

    RESET_TDF((ZIc));
    (ZId)->sort = g_toksort;
    (ZId)->isdeffed =1; (ZId)->iskept=0; (ZId)->isparam = 0;
    o_make_tokdef(out_tdfint32(UL(local_name(&(ZId)->idname.name,tok_ent))),
	if ((ZIb).no != 0) { OPTION(append_TDF(&(ZIb), 1)); },
	append_TDF(&g_tok_defn, 1));
    INC_LIST;
    if (!(ZIe)) { (ZId)->next = tokdecs; tokdecs = (ZId); (ZId)->isused=0; }
    g_tok_defn = (ZIa);
#line 9203 "syntax.c"
		}
		/* END OF ACTION: tok_def2 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRunary__exp(void)
{
ZL2_unary__exp:;
	switch (CURRENT_TERMINAL) {
	case 19:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: cseexp1_dec */
			{
#line 420 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 9231 "syntax.c"
			}
			/* END OF ACTION: cseexp1_dec */
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
			/* BEGINNING OF ACTION: cseexp2 */
			{
#line 425 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 9251 "syntax.c"
			}
			/* END OF ACTION: cseexp2 */
			ZRrange__label__list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: cseexp3 */
			{
#line 430 "syntax.act"

    RESET_TDF((ZIc));
    o_case(o_false, append_TDF(&(ZIa),1),
	   { append_TDF(&(ZIb),1); current_TDF->no = (ZIb).no; });
#line 9266 "syntax.c"
			}
			/* END OF ACTION: cseexp3 */
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
			/* BEGINNING OF ACTION: expcons1_dec */
			{
#line 666 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 9298 "syntax.c"
			}
			/* END OF ACTION: expcons1_dec */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expcons2 */
			{
#line 671 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 9312 "syntax.c"
			}
			/* END OF ACTION: expcons2 */
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
			/* BEGINNING OF ACTION: expcons3 */
			{
#line 676 "syntax.act"

    RESET_TDF((ZIc));
    o_make_compound(append_TDF(&(ZIa),1),
		    { append_TDF(&(ZIb),1); current_TDF->no = (ZIb).no; });
#line 9341 "syntax.c"
			}
			/* END OF ACTION: expcons3 */
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
			/* BEGINNING OF INLINE: 639 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: unary_exp */
						goto ZL2_unary__exp;
						/* END OF INLINE: unary_exp */
					}
					UNREACHED;
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 9381 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
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
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 9402 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
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
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 9423 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
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
						/* BEGINNING OF ACTION: exp1 */
						{
#line 509 "syntax.act"

    RESET_TDF((ZId));
    o_exp_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
	       append_TDF(&(ZIc),1));
#line 9445 "syntax.c"
						}
						/* END OF ACTION: exp1 */
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
			/* END OF INLINE: 639 */
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
			/* BEGINNING OF ACTION: query_type2 */
			{
#line 1613 "syntax.act"

    query_t = lex_float__query;
#line 9478 "syntax.c"
			}
			/* END OF ACTION: query_type2 */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exptst1_dec */
			{
#line 879 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = query_t;
    SET_TDF((ZId),&(ZIa));
#line 9495 "syntax.c"
			}
			/* END OF ACTION: exptst1_dec */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst2 */
			{
#line 885 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId),&(ZIb));
#line 9509 "syntax.c"
			}
			/* END OF ACTION: exptst2 */
			read_ntest ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst3 */
			{
#line 890 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc))
#line 9523 "syntax.c"
			}
			/* END OF ACTION: exptst3 */
			read_exp ();
			ZRlabdest__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst4 */
			{
#line 895 "syntax.act"

    RESET_TDF((ZId));
    switch ((ZIe)) {
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
	    o_pointer_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_proc__query:
	    o_proc_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
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
#line 9563 "syntax.c"
			}
			/* END OF ACTION: exptst4 */
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
			/* BEGINNING OF ACTION: expfail1 */
			{
#line 691 "syntax.act"

    o_fail_installer(read_string());
#line 9583 "syntax.c"
			}
			/* END OF ACTION: expfail1 */
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
			/* BEGINNING OF ACTION: explab1_dec */
			{
#line 730 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIe) = labdecs;
    (ZIc) = g_lablist;
    INIT_TDF(&g_lablist);
    SET_TDF((ZId), &(ZIa));
#line 9606 "syntax.c"
			}
			/* END OF ACTION: explab1_dec */
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
			/* BEGINNING OF ACTION: explab2 */
			{
#line 738 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 9627 "syntax.c"
			}
			/* END OF ACTION: explab2 */
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
			/* BEGINNING OF ACTION: explab3 */
			{
#line 743 "syntax.act"

    RESET_TDF((ZId));
    o_labelled({ append_TDF(&g_lablist,1);
		  current_TDF->no = g_lablist.no;},
		  append_TDF(&(ZIa), 1),
		  { append_TDF(&(ZIb),1);
		    current_TDF->no = g_lablist.no;});
    tidy_labels((ZIe));
    g_lablist = (ZIc);
#line 9660 "syntax.c"
			}
			/* END OF ACTION: explab3 */
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
			/* BEGINNING OF ACTION: query_type5 */
			{
#line 1625 "syntax.act"

    query_t = lex_offset__query;
#line 9705 "syntax.c"
			}
			/* END OF ACTION: query_type5 */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exptst1_dec */
			{
#line 879 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = query_t;
    SET_TDF((ZId),&(ZIa));
#line 9722 "syntax.c"
			}
			/* END OF ACTION: exptst1_dec */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst2 */
			{
#line 885 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId),&(ZIb));
#line 9736 "syntax.c"
			}
			/* END OF ACTION: exptst2 */
			read_ntest ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst3 */
			{
#line 890 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc))
#line 9750 "syntax.c"
			}
			/* END OF ACTION: exptst3 */
			read_exp ();
			ZRlabdest__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst4 */
			{
#line 895 "syntax.act"

    RESET_TDF((ZId));
    switch ((ZIe)) {
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
	    o_pointer_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_proc__query:
	    o_proc_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
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
#line 9790 "syntax.c"
			}
			/* END OF ACTION: exptst4 */
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
			/* BEGINNING OF ACTION: chvar1_dec */
			{
#line 397 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 9836 "syntax.c"
			}
			/* END OF ACTION: chvar1_dec */
			read_variety ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: chvar2 */
			{
#line 402 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 9850 "syntax.c"
			}
			/* END OF ACTION: chvar2 */
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
			/* BEGINNING OF ACTION: chvar3 */
			{
#line 407 "syntax.act"

    RESET_TDF((ZIc));
    o_change_variety(o_wrap, append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
#line 9871 "syntax.c"
			}
			/* END OF ACTION: chvar3 */
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
			/* BEGINNING OF ACTION: query_type4 */
			{
#line 1621 "syntax.act"

    query_t = lex_proc__query;
#line 9900 "syntax.c"
			}
			/* END OF ACTION: query_type4 */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exptst1_dec */
			{
#line 879 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = query_t;
    SET_TDF((ZId),&(ZIa));
#line 9917 "syntax.c"
			}
			/* END OF ACTION: exptst1_dec */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst2 */
			{
#line 885 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId),&(ZIb));
#line 9931 "syntax.c"
			}
			/* END OF ACTION: exptst2 */
			read_ntest ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst3 */
			{
#line 890 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc))
#line 9945 "syntax.c"
			}
			/* END OF ACTION: exptst3 */
			read_exp ();
			ZRlabdest__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst4 */
			{
#line 895 "syntax.act"

    RESET_TDF((ZId));
    switch ((ZIe)) {
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
	    o_pointer_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_proc__query:
	    o_proc_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
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
#line 9985 "syntax.c"
			}
			/* END OF ACTION: exptst4 */
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
			/* BEGINNING OF ACTION: query_type3 */
			{
#line 1617 "syntax.act"

    query_t = lex_ptr__query;
#line 10011 "syntax.c"
			}
			/* END OF ACTION: query_type3 */
			switch (CURRENT_TERMINAL) {
			case 78:
				break;
			default:
				goto ZL1;
			}
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: exptst1_dec */
			{
#line 879 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    (ZIe) = query_t;
    SET_TDF((ZId),&(ZIa));
#line 10028 "syntax.c"
			}
			/* END OF ACTION: exptst1_dec */
			read_exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst2 */
			{
#line 885 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId),&(ZIb));
#line 10042 "syntax.c"
			}
			/* END OF ACTION: exptst2 */
			read_ntest ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst3 */
			{
#line 890 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc))
#line 10056 "syntax.c"
			}
			/* END OF ACTION: exptst3 */
			read_exp ();
			ZRlabdest__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exptst4 */
			{
#line 895 "syntax.act"

    RESET_TDF((ZId));
    switch ((ZIe)) {
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
	    o_pointer_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
	   		append_TDF(&(ZIa), 1), append_TDF(&(ZIc),1));
	    break;
	case lex_proc__query:
	    o_proc_test({}, append_TDF(&(ZIb),1),append_TDF(&optlab,1),
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
#line 10096 "syntax.c"
			}
			/* END OF ACTION: exptst4 */
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
			/* BEGINNING OF ACTION: exprep1_dec */
			{
#line 803 "syntax.act"

    /* (ZIb), (ZIc), (ZIf) uninitialised */
    (ZIe) = labdecs;
    SET_TDF((ZId), &(ZIa));
#line 10135 "syntax.c"
			}
			/* END OF ACTION: exprep1_dec */
			ZRrepeat__starter__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exprep2 */
			{
#line 809 "syntax.act"

    (ZIf) = defaultlab;
    defaultlab = -1;
#line 10149 "syntax.c"
			}
			/* END OF ACTION: exprep2 */
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
			/* BEGINNING OF ACTION: exprep3 */
			{
#line 814 "syntax.act"

    (ZIc) = optlab;
    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 10171 "syntax.c"
			}
			/* END OF ACTION: exprep3 */
			ZRexp__sequence ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: exprep4 */
			{
#line 820 "syntax.act"

    RESET_TDF((ZId));
    o_repeat(append_TDF(&(ZIc),1), append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
    tidy_labels((ZIe));
    defaultlab = (ZIf);
#line 10187 "syntax.c"
			}
			/* END OF ACTION: exprep4 */
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
			/* BEGINNING OF ACTION: mint1_dec */
			{
#line 1471 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 10217 "syntax.c"
			}
			/* END OF ACTION: mint1_dec */
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
			/* BEGINNING OF ACTION: mint2 */
			{
#line 1477 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
#line 10239 "syntax.c"
			}
			/* END OF ACTION: mint2 */
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
			/* BEGINNING OF ACTION: szexp1_dec */
			{
#line 1895 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 10269 "syntax.c"
			}
			/* END OF ACTION: szexp1_dec */
			read_shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: sizeexp2 */
			{
#line 1812 "syntax.act"

    RESET_TDF((ZIb));
    o_offset_pad(o_alignment(append_TDF(&(ZIa), 0)),
		 o_shape_offset(append_TDF(&(ZIa), 1)));
#line 10284 "syntax.c"
			}
			/* END OF ACTION: sizeexp2 */
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
			/* BEGINNING OF ACTION: signed_nat2 */
			{
#line 1774 "syntax.act"

    o_make_signed_nat(out_tdfbool(0), out_tdfint32(intvalue));
#line 10321 "syntax.c"
			}
			/* END OF ACTION: signed_nat2 */
			/* BEGINNING OF ACTION: mint1_dec */
			{
#line 1471 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 10331 "syntax.c"
			}
			/* END OF ACTION: mint1_dec */
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
			/* BEGINNING OF ACTION: mint2 */
			{
#line 1477 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
#line 10353 "syntax.c"
			}
			/* END OF ACTION: mint2 */
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
			/* BEGINNING OF ACTION: exptag1 */
			{
#line 876 "syntax.act"

    TDF tg;
    tg = *current_TDF;
    INIT_TDF(current_TDF);
    o_obtain_tag(append_TDF(&tg,1));
#line 10380 "syntax.c"
			}
			/* END OF ACTION: exptag1 */
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

			/* BEGINNING OF ACTION: expdec1_dec */
			{
#line 682 "syntax.act"

    (ZIa) = localdecs;
#line 10405 "syntax.c"
			}
			/* END OF ACTION: expdec1_dec */
			ZRtag__intro ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: ibody1_dec */
			{
#line 1173 "syntax.act"

    (ZIg) = localdecs->isvar;
    (ZIb) = intro_acc;
    (ZIc) = intro_init;
    (ZIf) = localdecs->idname.name;
    SET_TDF((ZIe), &(ZId));
#line 10422 "syntax.c"
			}
			/* END OF ACTION: ibody1_dec */
			ZRclosed__exp ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: introbody2 */
			{
#line 1246 "syntax.act"

    RESET_TDF((ZIe));
    if ((ZIg)) {
	o_variable(if ((ZIb).no!=0) { OPTION(append_TDF(&(ZIb),1)); },
		    make_tag(&(ZIf)), append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1));
    } else {
	o_identify(if ((ZIb).no!=0) { OPTION(append_TDF(&(ZIb),1)); },
		    make_tag(&(ZIf)), append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1));
    }
#line 10444 "syntax.c"
			}
			/* END OF ACTION: introbody2 */
			/* BEGINNING OF ACTION: expdec2 */
			{
#line 686 "syntax.act"

    localdecs = (ZIa);
#line 10452 "syntax.c"
			}
			/* END OF ACTION: expdec2 */
		}
		break;
	case 85: case 104: case 105: case 107:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			/* BEGINNING OF ACTION: expstr1_dec */
			{
#line 857 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 10469 "syntax.c"
			}
			/* END OF ACTION: expstr1_dec */
			read_string ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: expstr2 */
			{
#line 862 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 10483 "syntax.c"
			}
			/* END OF ACTION: expstr2 */
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
			/* BEGINNING OF ACTION: expstring2 */
			{
#line 867 "syntax.act"

    RESET_TDF((ZIc));
    o_make_nof_int(append_TDF(&(ZIb), 1), append_TDF(&(ZIa), 1););
#line 10510 "syntax.c"
			}
			/* END OF ACTION: expstring2 */
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

			/* BEGINNING OF ACTION: fden1_dec */
			{
#line 925 "syntax.act"

    /* (ZIc), (ZId) uninitialised */
    (ZIf) = 0;
    (ZIg) = UL(radix);
    SET_TDF((ZIe), &(ZIa));
    out_tdfstring_bytes(fformat(lex_v.val.name,lnum), 8, UI(lnum));
    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIb));
#line 10536 "syntax.c"
			}
			/* END OF ACTION: fden1_dec */
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
			/* BEGINNING OF ACTION: fden3 */
			{
#line 945 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZIc));
#line 10557 "syntax.c"
			}
			/* END OF ACTION: fden3 */
			read_floating_variety ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: fden4 */
			{
#line 950 "syntax.act"

    RESET_TDF((ZIe));
    SET_TDF((ZIe), &(ZId));
#line 10571 "syntax.c"
			}
			/* END OF ACTION: fden4 */
			ZRrounding__mode__opt ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: fden5 */
			{
#line 955 "syntax.act"

    RESET_TDF((ZIe));
    o_make_floating(append_TDF(&(ZIc),1),
		    append_TDF(&(ZId),1),
		    if ((ZIf)) { o_true; } else { o_false; },
		    o_make_string(append_TDF(&(ZIa), 1)),
		    o_make_nat(out_tdfint32((ZIg))),
		    append_TDF(&(ZIb), 1));
#line 10590 "syntax.c"
			}
			/* END OF ACTION: fden5 */
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

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZI642) = lex_v.val.v;
#line 10611 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
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

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZI640) = lex_v.val.tokname;
    (ZI640)->isused = 1;
#line 10631 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
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

			/* BEGINNING OF ACTION: signed_nat4 */
			{
#line 1782 "syntax.act"

    o_make_signed_nat(out_tdfbool(0), out_tdfint32(cLINE));
#line 10651 "syntax.c"
			}
			/* END OF ACTION: signed_nat4 */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: mint1_dec */
			{
#line 1471 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 10662 "syntax.c"
			}
			/* END OF ACTION: mint1_dec */
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
			/* BEGINNING OF ACTION: mint2 */
			{
#line 1477 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
#line 10684 "syntax.c"
			}
			/* END OF ACTION: mint2 */
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

			/* BEGINNING OF ACTION: signed_nat7_dec */
			{
#line 1794 "syntax.act"

    SET_TDF((ZI638), &(ZI637));
    if (strcmp(lex_v.val.name, "+"))fail("Only + or - on NATs");
#line 10709 "syntax.c"
			}
			/* END OF ACTION: signed_nat7_dec */
			ADVANCE_LEXER;
			ZRnat__not__int ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: signed_nat8 */
			{
#line 1799 "syntax.act"

    RESET_TDF((ZI638));
    o_snat_from_nat(o_false, append_TDF(&(ZI637),1));
#line 10724 "syntax.c"
			}
			/* END OF ACTION: signed_nat8 */
			/* BEGINNING OF ACTION: mint1_dec */
			{
#line 1471 "syntax.act"

    /* (ZIb) uninitialised */
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 10734 "syntax.c"
			}
			/* END OF ACTION: mint1_dec */
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
			/* BEGINNING OF ACTION: mint2 */
			{
#line 1477 "syntax.act"

    (ZIb) = *current_TDF;
    INIT_TDF(current_TDF);
    o_make_int(append_TDF(&(ZIb),1), append_TDF(&(ZIa),1));
#line 10756 "syntax.c"
			}
			/* END OF ACTION: mint2 */
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
ZRtagshacc__list(void)
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
		/* BEGINNING OF ACTION: tagshacc_l2 */
		{
#line 2134 "syntax.act"

    current_TDF->no++;
#line 10797 "syntax.c"
		}
		/* END OF ACTION: tagshacc_l2 */
		/* BEGINNING OF INLINE: 623 */
		{
			switch (CURRENT_TERMINAL) {
			case 25:
				{
					ADVANCE_LEXER;
					/* BEGINNING OF INLINE: tagshacc_list */
					goto ZL2_tagshacc__list;
					/* END OF INLINE: tagshacc_list */
				}
				UNREACHED;
			default:
				break;
			}
		}
		/* END OF INLINE: 623 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRshapetok(void)
{
	switch (CURRENT_TERMINAL) {
	case 32:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shtokdb */
			{
#line 1756 "syntax.act"

    * g_shtokname = *(tokfordoublesh());
#line 10835 "syntax.c"
			}
			/* END OF ACTION: shtokdb */
		}
		break;
	case 46:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: shtokflt */
			{
#line 1760 "syntax.act"

    * g_shtokname = *(tokforfloatsh());
#line 10848 "syntax.c"
			}
			/* END OF ACTION: shtokflt */
		}
		break;
	case 21: case 56: case 64: case 97:
	case 101: case 121:
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

			/* BEGINNING OF ACTION: shtok1_dec */
			{
#line 1747 "syntax.act"

    (ZIa) = current_TDF;
    (ZId) = current_Unit;
    select_tokdef_unit();
    * g_shtokname = next_name(tok_ent);
    SET_TDF((ZIc), &(ZIb));
#line 10880 "syntax.c"
			}
			/* END OF ACTION: shtok1_dec */
			ZRnonst__shape ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: shapetok2 */
			{
#line 1722 "syntax.act"

    RESET_TDF((ZIc));
    o_make_tokdef(out_tdfint32(UL(g_shtokname->unit_name)), {},
		  o_token_def(o_shape, {}, append_TDF(&(ZIb), 1)));
    INC_LIST;
    current_Unit = (ZId);
    RESET_TDF((ZIa));
#line 10898 "syntax.c"
			}
			/* END OF ACTION: shapetok2 */
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
ZRalignment__list(void)
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
read_error_treatment(void)
{
ZL2_error__treatment:;
	switch (CURRENT_TERMINAL) {
	case 39:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 684 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: error_treatment */
						goto ZL2_error__treatment;
						/* END OF INLINE: error_treatment */
					}
					UNREACHED;
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 10966 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
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
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 10994 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
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
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 11014 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_error_treatment ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: errt1 */
						{
#line 489 "syntax.act"

    RESET_TDF((ZId));
    o_errt_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		append_TDF(&(ZIc),1));
#line 11029 "syntax.c"
						}
						/* END OF ACTION: errt1 */
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
			/* END OF INLINE: 684 */
		}
		break;
	case 79:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: errt2_dec */
			{
#line 495 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 11059 "syntax.c"
			}
			/* END OF ACTION: errt2_dec */
			read_error_code_list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: errt5 */
			{
#line 504 "syntax.act"

    RESET_TDF((ZIb));
    o_trap({append_TDF(&(ZIa),1); current_TDF->no = (ZIa).no; });
#line 11073 "syntax.c"
			}
			/* END OF ACTION: errt5 */
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

			/* BEGINNING OF ACTION: errt2_dec */
			{
#line 495 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 11095 "syntax.c"
			}
			/* END OF ACTION: errt2_dec */
			read_label ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: errt3 */
			{
#line 499 "syntax.act"

    RESET_TDF((ZIb));
    o_error_jump(append_TDF(&(ZIa),1));
#line 11109 "syntax.c"
			}
			/* END OF ACTION: errt3 */
		}
		break;
	case 38:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 11123 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 11132 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 40:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 11147 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 11156 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 11174 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRcallee(void)
{
	switch (CURRENT_TERMINAL) {
	case 33:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: callee3_dec */
			{
#line 370 "syntax.act"

    /* (ZIb) uninitialised */
    SET_TDF((ZIc), &(ZIa));
#line 11197 "syntax.c"
			}
			/* END OF ACTION: callee3_dec */
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
			/* BEGINNING OF ACTION: callee4 */
			{
#line 375 "syntax.act"

    RESET_TDF((ZIc));
    SET_TDF((ZIc), &(ZIb));
#line 11218 "syntax.c"
			}
			/* END OF ACTION: callee4 */
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
			/* BEGINNING OF ACTION: callee5 */
			{
#line 380 "syntax.act"

    RESET_TDF((ZIc));
    o_make_dynamic_callees(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1));
#line 11239 "syntax.c"
			}
			/* END OF ACTION: callee5 */
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
			/* BEGINNING OF ACTION: callee6 */
			{
#line 386 "syntax.act"

    o_same_callees;
#line 11259 "syntax.c"
			}
			/* END OF ACTION: callee6 */
		}
		break;
	default:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			/* BEGINNING OF ACTION: callee1_dec */
			{
#line 361 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 11274 "syntax.c"
			}
			/* END OF ACTION: callee1_dec */
			read_exp_list ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: callee2 */
			{
#line 365 "syntax.act"

    RESET_TDF((ZIb));
    o_make_callee_list({ append_TDF(&(ZIa),1); current_TDF->no = (ZIa).no;});
#line 11288 "syntax.c"
			}
			/* END OF ACTION: callee2 */
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
read_al_tag(void)
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
			/* BEGINNING OF INLINE: al_tag */
			goto ZL2_al__tag;
			/* END OF INLINE: al_tag */
		}
		UNREACHED;
	case 54:
		{
			/* BEGINNING OF ACTION: al_tag1 */
			{
#line 258 "syntax.act"

    char * n =lex_v.val.name;
    Al_tagdec * x = find_al_tag(n);
    if (x== (Al_tagdec*)0) {
	x= xmalloc(sizeof *x);
	x->isdeffed =0; x->iskept=0;
	NEW_IDNAME(x->idname, n, al_tag_ent);
	x->next = al_tagdecs;
	al_tagdecs = x;
    }
    x->isused =1;
    make_al_tag(&x->idname.name);
#line 11339 "syntax.c"
			}
			/* END OF ACTION: al_tag1 */
			ADVANCE_LEXER;
		}
		break;
	case 5:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 11355 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 11364 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 11382 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

void
read_exp_list(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		/* BEGINNING OF ACTION: expl1 */
		{
#line 723 "syntax.act"

    current_TDF->no=0;
#line 11400 "syntax.c"
		}
		/* END OF ACTION: expl1 */
		ZR656 ();
		if ((CURRENT_TERMINAL) == 130) {
			RESTORE_LEXER;
			goto ZL1;
		}
	}
	return;
ZL1:;
	{
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 11417 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZRelement(void)
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
ZR622(void)
{
ZL2_622:;
	switch (CURRENT_TERMINAL) {
	case 25:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			/* BEGINNING OF ACTION: al_list1_dec */
			{
#line 229 "syntax.act"

    (ZIb) = current_TDF;
    (ZIa) = *current_TDF;
    INIT_TDF(current_TDF);
#line 11518 "syntax.c"
			}
			/* END OF ACTION: al_list1_dec */
			ADVANCE_LEXER;
			read_alignment ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: al_list2 */
			{
#line 237 "syntax.act"

    TDF second;
    second = *current_TDF;
    INIT_TDF((ZIb));
    RESET_TDF((ZIb));
    o_unite_alignments(append_TDF(&(ZIa),1), append_TDF(&second,1));
#line 11536 "syntax.c"
			}
			/* END OF ACTION: al_list2 */
			/* BEGINNING OF INLINE: 622 */
			goto ZL2_622;
			/* END OF INLINE: 622 */
		}
		UNREACHED;
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
ZRtok__def__body(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		PTR_Tokdec ZIa;

		/* BEGINNING OF ACTION: tok_dn1_dec */
		{
#line 2245 "syntax.act"

    (ZIa) = g_tokformals;
#line 11569 "syntax.c"
		}
		/* END OF ACTION: tok_dn1_dec */
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
		/* BEGINNING OF ACTION: tok_dn2 */
		{
#line 2291 "syntax.act"

    Tokdec * old_tokdecs = tokdecs;
    Tokdec * tokformals = g_tokformals;
    TDF * hold = current_TDF;
    Tokpar * tp = (Tokpar*)0;
    Sort sn;
    Tokdec * tfrev = (Tokdec*)0;
    while (g_tokformals != (Tokdec*)0) { /* the wrong way round!! */
	Tokdec * x = xmalloc(sizeof *x);
	*x = *g_tokformals;
	x->next = tfrev;
	tfrev = x;
	g_tokformals = g_tokformals->next;
    }
    sn = g_sname;
    current_TDF = &g_tok_defn;
    INIT_TDF(current_TDF);
    o_token_def(out_sort(&sn),
	{
	    while (tfrev != (Tokdec*)0) {
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
	Tokpar * p = xmalloc(sizeof *p);
	p->par = tokformals->sort.ressort;
	p->next = tp;
	tokformals = tokformals->next;
	tp = p;
    }
    g_toksort.pars = tp;
    RESET_TDF(hold);
    tokdecs = old_tokdecs;
    g_tokformals = (ZIa);
#line 11642 "syntax.c"
		}
		/* END OF ACTION: tok_dn2 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRinteger(void)
{
	switch (CURRENT_TERMINAL) {
	case 55:
		{
			/* BEGINNING OF ACTION: integer1 */
			{
#line 1182 "syntax.act"

    intvalue = UL(stoi(lex_v.val.name, lnum));
#line 11663 "syntax.c"
			}
			/* END OF ACTION: integer1 */
			ADVANCE_LEXER;
		}
		break;
	case 22:
		{
			/* BEGINNING OF ACTION: integer2 */
			{
#line 1186 "syntax.act"

    intvalue = UL(lex_v.val.v);
#line 11676 "syntax.c"
			}
			/* END OF ACTION: integer2 */
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
read_transfer_mode(void)
{
ZL2_transfer__mode:;
	switch (CURRENT_TERMINAL) {
	case 119:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 685 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: transfer_mode */
						goto ZL2_transfer__mode;
						/* END OF INLINE: transfer_mode */
					}
					UNREACHED;
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 11726 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
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
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 11747 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
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
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 11768 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
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
						/* BEGINNING OF ACTION: tmode1 */
						{
#line 2164 "syntax.act"

    RESET_TDF((ZId));
    o_transfer_mode_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
			 append_TDF(&(ZIc),1));
#line 11790 "syntax.c"
						}
						/* END OF ACTION: tmode1 */
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
			/* END OF INLINE: 685 */
		}
		break;
	case 118:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 11818 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 11827 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 120:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 11842 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 11851 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 11869 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

void
read_rounding_mode(void)
{
ZL2_rounding__mode:;
	switch (CURRENT_TERMINAL) {
	case 90:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 659 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: rounding_mode */
						goto ZL2_rounding__mode;
						/* END OF INLINE: rounding_mode */
					}
					UNREACHED;
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 11908 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
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
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 11935 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
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
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 11955 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_rounding_mode ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: rmode1 */
						{
#line 1671 "syntax.act"

    RESET_TDF((ZId));
    o_rounding_mode_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
			 append_TDF(&(ZIc),1));
#line 11970 "syntax.c"
						}
						/* END OF ACTION: rmode1 */
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
			/* END OF INLINE: 659 */
		}
		break;
	case 89:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 11998 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 12007 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 91:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 12022 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 12031 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 12049 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR625(void)
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
			/* BEGINNING OF ACTION: errc2 */
			{
#line 486 "syntax.act"

    current_TDF->no++;
#line 12073 "syntax.c"
			}
			/* END OF ACTION: errc2 */
			/* BEGINNING OF INLINE: 625 */
			goto ZL2_625;
			/* END OF INLINE: 625 */
		}
		UNREACHED;
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
ZR626(void)
{
ZL2_626:;
	switch (CURRENT_TERMINAL) {
	case 25:
		{
			/* BEGINNING OF ACTION: otagel2 */
			{
#line 1553 "syntax.act"

    current_TDF->no++;
#line 12104 "syntax.c"
			}
			/* END OF ACTION: otagel2 */
			ADVANCE_LEXER;
			ZRotagexp ();
			/* BEGINNING OF INLINE: 626 */
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			} else {
				goto ZL2_626;
			}
			/* END OF INLINE: 626 */
		}
		UNREACHED;
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
read_access(void)
{
ZL2_access:;
	switch (CURRENT_TERMINAL) {
	case 1:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 665 */
			{
				switch (CURRENT_TERMINAL) {
				case 24:
					{
						ADVANCE_LEXER;
						/* BEGINNING OF INLINE: access */
						goto ZL2_access;
						/* END OF INLINE: access */
					}
					UNREACHED;
				case 86:
					{
						TDF ZIa;
						TDF ZIb;
						TDF ZIc;
						PTR_TDF ZId;

						ADVANCE_LEXER;
						/* BEGINNING OF ACTION: gencond1_dec */
						{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 12163 "syntax.c"
						}
						/* END OF ACTION: gencond1_dec */
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
						/* BEGINNING OF ACTION: gencond2 */
						{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 12184 "syntax.c"
						}
						/* END OF ACTION: gencond2 */
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
						/* BEGINNING OF ACTION: gencond3 */
						{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 12211 "syntax.c"
						}
						/* END OF ACTION: gencond3 */
						read_access ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: access1 */
						{
#line 219 "syntax.act"

    RESET_TDF((ZId));
    o_access_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		  append_TDF(&(ZIc),1));
#line 12226 "syntax.c"
						}
						/* END OF ACTION: access1 */
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
			/* END OF INLINE: 665 */
		}
		break;
	case 0:
		{
			int ZIa;

			/* BEGINNING OF ACTION: gencons1_dec */
			{
#line 1091 "syntax.act"

    (ZIa) = lex_v.val.v;
#line 12254 "syntax.c"
			}
			/* END OF ACTION: gencons1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: access2 */
			{
#line 225 "syntax.act"

    if (strcmp(constructs[(ZIa)].name, "visible") ==0) { g_has_vis = 1; }
#line 12263 "syntax.c"
			}
			/* END OF ACTION: access2 */
			/* BEGINNING OF ACTION: gencons2 */
			{
#line 1095 "syntax.act"

   (constructs[(ZIa)].f)();
#line 12271 "syntax.c"
			}
			/* END OF ACTION: gencons2 */
		}
		break;
	case 2:
		{
			PTR_Tokdec ZIa;

			/* BEGINNING OF ACTION: gentok1_dec */
			{
#line 1114 "syntax.act"

    (ZIa) = lex_v.val.tokname;
    (ZIa)->isused = 1;
#line 12286 "syntax.c"
			}
			/* END OF ACTION: gentok1_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: gentok2 */
			{
#line 1119 "syntax.act"

    expand_tok((ZIa), &(ZIa)->sort);
#line 12295 "syntax.c"
			}
			/* END OF ACTION: gentok2 */
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 12313 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR627(void)
{
ZL2_627:;
	switch (CURRENT_TERMINAL) {
	case 25:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;

			/* BEGINNING OF ACTION: acc_l2_dec */
			{
#line 205 "syntax.act"

    (ZIc) = current_TDF;
    (ZIa) = *current_TDF;
    INIT_TDF(&(ZIb));
    RESET_TDF(&(ZIb));
#line 12338 "syntax.c"
			}
			/* END OF ACTION: acc_l2_dec */
			ADVANCE_LEXER;
			read_access ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: acc_l3 */
			{
#line 212 "syntax.act"

    INIT_TDF((ZIc));
    RESET_TDF((ZIc));
    o_add_accesses(append_TDF(&(ZIa),1), append_TDF(&(ZIb), 1));
    current_TDF->no = 1;
#line 12355 "syntax.c"
			}
			/* END OF ACTION: acc_l3 */
			/* BEGINNING OF INLINE: 627 */
			goto ZL2_627;
			/* END OF INLINE: 627 */
		}
		UNREACHED;
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
ZR628(void)
{
ZL2_628:;
	switch (CURRENT_TERMINAL) {
	case 93:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			/* BEGINNING OF ACTION: exp_sls3_dec */
			{
#line 616 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 12389 "syntax.c"
			}
			/* END OF ACTION: exp_sls3_dec */
			ADVANCE_LEXER;
			/* BEGINNING OF INLINE: 667 */
			{
				switch (CURRENT_TERMINAL) {
				case 10: case 19: case 22: case 28:
				case 41: case 42: case 43: case 44:
				case 45: case 52: case 54: case 55:
				case 58: case 61: case 62: case 68:
				case 76: case 77: case 78: case 79:
				case 81: case 82: case 84: case 85:
				case 86: case 88: case 98: case 99:
				case 100: case 102: case 103: case 104:
				case 105: case 107: case 109: case 110:
				case 111: case 124:
					{
						read_exp ();
						if ((CURRENT_TERMINAL) == 130) {
							RESTORE_LEXER;
							goto ZL1;
						}
						/* BEGINNING OF ACTION: exp_sls4 */
						{
#line 620 "syntax.act"

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
#line 12429 "syntax.c"
						}
						/* END OF ACTION: exp_sls4 */
						/* BEGINNING OF INLINE: 628 */
						goto ZL2_628;
						/* END OF INLINE: 628 */
					}
					UNREACHED;
				default:
					{
						/* BEGINNING OF ACTION: exp_sls5 */
						{
#line 637 "syntax.act"

    o_make_top;
#line 12444 "syntax.c"
						}
						/* END OF ACTION: exp_sls5 */
						/* BEGINNING OF ACTION: exp_sls4 */
						{
#line 620 "syntax.act"

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
#line 12464 "syntax.c"
						}
						/* END OF ACTION: exp_sls4 */
						/* BEGINNING OF INLINE: 628 */
						goto ZL2_628;
						/* END OF INLINE: 628 */
					}
					UNREACHED;
				}
			}
			/* END OF INLINE: 667 */
		}
		UNREACHED;
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
ZR629(void)
{
ZL2_629:;
	switch (CURRENT_TERMINAL) {
	case 25:
		{
			PTR_Tokdec ZIa;

			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: tok_fml1_dec */
			{
#line 2296 "syntax.act"

    char * n = lex_v.val.name;
    (ZIa) = find_tok(n);
    if ((ZIa)!= (Tokdec*)0)fail("Token parameter name %s must be unique", n);
    (ZIa) = xmalloc(sizeof *(ZIa)); NEW_IDNAME((ZIa)->idname, n, tok_ent);
    (ZIa)->isdeffed = 1; (ZIa)->isused = 0; (ZIa)->iskept=0;
    (ZIa)->next = (Tokdec*)0;
#line 12508 "syntax.c"
			}
			/* END OF ACTION: tok_fml1_dec */
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
			/* BEGINNING OF ACTION: tok_fml3 */
			{
#line 2310 "syntax.act"

    (ZIa)->sort.ressort = g_sname;
    (ZIa)->sort.pars = (Tokpar*)0; /* no pars in formal pars */
    (ZIa)->next = g_tokformals;
    g_tokformals = (ZIa);
#line 12538 "syntax.c"
			}
			/* END OF ACTION: tok_fml3 */
			/* BEGINNING OF INLINE: 629 */
			goto ZL2_629;
			/* END OF INLINE: 629 */
		}
		UNREACHED;
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
ZR630(void)
{
	switch (CURRENT_TERMINAL) {
	case 35:
		{
			ADVANCE_LEXER;
			/* BEGINNING OF ACTION: keeps1 */
			{
#line 1282 "syntax.act"

    int i;
    for (i=0; i<NO_OF_ENTITIES; i++) {
	INIT_TDF(lk_externs+i);
    }
#line 12572 "syntax.c"
			}
			/* END OF ACTION: keeps1 */
			/* BEGINNING OF ACTION: keeps2 */
			{
#line 1402 "syntax.act"

    CONT_STREAM(&units[tld2_unit].tdf, out_tdfint32(UL(1)));
    if (line_no_tok != -1) {
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
	if (do_pp)success();
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
		for (i=0; i<NO_OF_UNITS; i++) {
		    if (units[i].present) {
			char* n;
			n = unit_names[i];
			LIST_ELEM({ out_tdfident_bytes(n); });
		    }
		}
	    },
	    {
		for (i=0; i<NO_OF_ENTITIES; i++) {
		    char* n;
		    n = ent_names[i];
		    LIST_ELEM(
			o_make_capsule_link(
			    { out_tdfident_bytes(n);},
			    out_tdfint32(UL(capsule_names[i]))))
		}
	    },
	    {
		for (i=0; i<NO_OF_ENTITIES; i++) {
		    TDF * lks = lk_externs+i;
		    LIST_ELEM(
			o_make_extern_link(
			    { append_TDF(lks,1); current_TDF->no = lks->no; });
		   )
		}
	    },
	    {
		for (i=0; i<NO_OF_UNITS; i++) {
		    if (units[i].present) {
			LIST_ELEM(
			    o_make_group(LIST_ELEM(make_unit(i))););
		    }
		}
	    }
	);
	make_tdf_file(&caps, out_file);
    }
#line 12696 "syntax.c"
			}
			/* END OF ACTION: keeps2 */
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
			/* BEGINNING OF ACTION: keeps1 */
			{
#line 1282 "syntax.act"

    int i;
    for (i=0; i<NO_OF_ENTITIES; i++) {
	INIT_TDF(lk_externs+i);
    }
#line 12719 "syntax.c"
			}
			/* END OF ACTION: keeps1 */
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
			/* BEGINNING OF ACTION: keeps2 */
			{
#line 1402 "syntax.act"

    CONT_STREAM(&units[tld2_unit].tdf, out_tdfint32(UL(1)));
    if (line_no_tok != -1) {
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
	if (do_pp)success();
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
		for (i=0; i<NO_OF_UNITS; i++) {
		    if (units[i].present) {
			char* n;
			n = unit_names[i];
			LIST_ELEM({ out_tdfident_bytes(n); });
		    }
		}
	    },
	    {
		for (i=0; i<NO_OF_ENTITIES; i++) {
		    char* n;
		    n = ent_names[i];
		    LIST_ELEM(
			o_make_capsule_link(
			    { out_tdfident_bytes(n);},
			    out_tdfint32(UL(capsule_names[i]))))
		}
	    },
	    {
		for (i=0; i<NO_OF_ENTITIES; i++) {
		    TDF * lks = lk_externs+i;
		    LIST_ELEM(
			o_make_extern_link(
			    { append_TDF(lks,1); current_TDF->no = lks->no; });
		   )
		}
	    },
	    {
		for (i=0; i<NO_OF_UNITS; i++) {
		    if (units[i].present) {
			LIST_ELEM(
			    o_make_group(LIST_ELEM(make_unit(i))););
		    }
		}
	    }
	);
	make_tdf_file(&caps, out_file);
    }
#line 12861 "syntax.c"
			}
			/* END OF ACTION: keeps2 */
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
ZR632(void)
{
	switch (CURRENT_TERMINAL) {
	case 3: case 10: case 36: case 63:
	case 68: case 103:
		{
			TDF ZIa;
			TDF ZIb;
			PTR_TDF ZIc;
			PTR_char ZId;

			/* BEGINNING OF ACTION: exp1_dec */
			{
#line 515 "syntax.act"

    (ZId) = lex_v.val.name;
    (ZIa) = *current_TDF;
    SET_TDF((ZIc), &(ZIb));
#line 12896 "syntax.c"
			}
			/* END OF ACTION: exp1_dec */
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
ZRkeep__list__opt(void)
{
	switch (CURRENT_TERMINAL) {
	case 2: case 5: case 9: case 15:
	case 18: case 40: case 43: case 49:
	case 54: case 60: case 71: case 75:
	case 91: case 96: case 100: case 111:
	case 120: case 128:
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
ZR633(void)
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
			/* BEGINNING OF ACTION: gencond1_dec */
			{
#line 1076 "syntax.act"

    /* (ZIb), (ZIc) uninitialised */
    SET_TDF((ZId), &(ZIa));
#line 12974 "syntax.c"
			}
			/* END OF ACTION: gencond1_dec */
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
			/* BEGINNING OF ACTION: gencond2 */
			{
#line 1081 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIb));
#line 12995 "syntax.c"
			}
			/* END OF ACTION: gencond2 */
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
			/* BEGINNING OF ACTION: gencond3 */
			{
#line 1086 "syntax.act"

    RESET_TDF((ZId));
    SET_TDF((ZId), &(ZIc));
#line 13016 "syntax.c"
			}
			/* END OF ACTION: gencond3 */
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
			/* BEGINNING OF ACTION: signed_nat1 */
			{
#line 1767 "syntax.act"

    RESET_TDF((ZId));
    o_signed_nat_cond(append_TDF(&(ZIa),1), append_TDF(&(ZIb),1),
		      append_TDF(&(ZIc),1));
#line 13038 "syntax.c"
			}
			/* END OF ACTION: signed_nat1 */
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
ZRal__tag__def(void)
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
		/* BEGINNING OF ACTION: al_tgdf1_dec */
		{
#line 274 "syntax.act"

    char * n =lex_v.val.name;
    (ZIa) = find_al_tag(n);
    SELECT_UNIT(al_tagdef_unit);
    if ((ZIa)== (Al_tagdec*)0) {
	(ZIa)= xmalloc(sizeof *(ZIa)); (ZIa)->isdeffed =0; (ZIa)->iskept=0; (ZIa)->isused=0;
	NEW_IDNAME((ZIa)->idname, n, al_tag_ent);
	(ZIa)->next = al_tagdecs; al_tagdecs = (ZIa);
	(ZId) = 0;
    }
    else (ZId) = 1;
    if ((ZIa)->isdeffed) { fail("Al_tag %s defined twice", n); }
    (ZIa)->isdeffed = 1;
    SET_TDF((ZIc), &(ZIb));
#line 13097 "syntax.c"
		}
		/* END OF ACTION: al_tgdf1_dec */
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
		/* BEGINNING OF ACTION: al_tagdef2 */
		{
#line 261 "syntax.act"

    RESET_TDF((ZIc));
    o_make_al_tagdef(if ((ZId)) {
			  out_tdfint32(UL(non_local(&(ZIa)->idname.name,al_tag_ent)));
			  } else {
			      out_tdfint32(LOCNAME((ZIa)->idname));
			  },
			  append_TDF(&(ZIb), 1)
			);
    INC_LIST;
#line 13132 "syntax.c"
		}
		/* END OF ACTION: al_tagdef2 */
	}
	return;
ZL1:;
	SAVE_LEXER (130);
	return;
}

static void
ZRotagexp(void)
{
	if ((CURRENT_TERMINAL) == 130) {
		return;
	}
	{
		TDF ZIa;
		PTR_TDF ZIb;

		/* BEGINNING OF ACTION: otagexp1_dec */
		{
#line 1560 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 13157 "syntax.c"
		}
		/* END OF ACTION: otagexp1_dec */
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
read_program(void)
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
		/* BEGINNING OF ACTION: syntax_error */
		{
#line 2406 "syntax.act"

    fail("Syntax error");
#line 13195 "syntax.c"
		}
		/* END OF ACTION: syntax_error */
	}
}

static void
ZR634(void)
{
	switch (CURRENT_TERMINAL) {
	case 22: case 55:
		{
			ZRinteger ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: signed_nat3 */
			{
#line 1778 "syntax.act"

    o_make_signed_nat(out_tdfbool(1), out_tdfint32(intvalue));
#line 13217 "syntax.c"
			}
			/* END OF ACTION: signed_nat3 */
		}
		break;
	case 69: case 70: case 71:
		{
			TDF ZIa;
			PTR_TDF ZIb;

			/* BEGINNING OF ACTION: signed_nat5_dec */
			{
#line 1785 "syntax.act"

    SET_TDF((ZIb), &(ZIa));
#line 13232 "syntax.c"
			}
			/* END OF ACTION: signed_nat5_dec */
			ZRnat__not__int ();
			if ((CURRENT_TERMINAL) == 130) {
				RESTORE_LEXER;
				goto ZL1;
			}
			/* BEGINNING OF ACTION: signed_nat6 */
			{
#line 1789 "syntax.act"

    RESET_TDF((ZIb));
    o_snat_from_nat(o_true, append_TDF(&(ZIa),1));
#line 13246 "syntax.c"
			}
			/* END OF ACTION: signed_nat6 */
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

#line 2409 "syntax.act"

#line 13266 "syntax.c"

/* END OF FILE */
