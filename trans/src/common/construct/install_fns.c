/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* This file defines procedures called from decoder which make up
   the internal representations of the various sorts of value.
   In most cases the construction of these is evident from the
   specification and the document describing the in-store
   representation: the function merely creates the corresponding value.
   In some cases processing is performed: it is only these which are
   commented.
   Many constructions have the shape of their arguments checked by
   CHECK_SHAPE. These checks are implied by the specification and are
   not commented.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <reader/exp.h>
#include <local/szs_als.h>

#include <reader/code.h>
#include <reader/basicread.h>
#include <reader/main_reads.h>
#include <reader/readglob.h>
#include <reader/table_fns.h>
#include <reader/read_fns.h>
#include <reader/sort.h>
#include <reader/readglob.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/tags.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>
#include <construct/flpttypes.h>
#include <construct/flpt.h>
#include <construct/shape.h>
#include <construct/machine.h>
#include <construct/special_fn.h>
#include <construct/messages_c.h>
#include <construct/f64.h>
#include <construct/install_fns.h>

#include <main/flags.h>

#include <utility/prefix.h>

#include <refactor/optimise.h>
#include <refactor/refactor.h>
#include <refactor/refactor_id.h>

#ifdef NEWDIAGS
#include <newdiag/dg_fns.h>
#include <newdiag/mark_scope.h>
#endif

#ifdef TRANS_SPARC
#include "needscan.h"
#endif

#define NOTYETDONE(x)	error(ERROR_INTERNAL, x)


#define MAX_ST_LENGTH 25

/* All variables initialised */

shape f_ptr1;
shape f_ptr8;
shape f_ptr16;
shape f_ptr32;
shape f_ptr64;
shape f_off0_0;
shape f_off1_1;
shape f_off8_8;
shape f_off8_1;
shape f_off16_16;
shape f_off16_8;
shape f_off16_1;
shape f_off32_32;
shape f_off32_16;
shape f_off32_8;
shape f_off32_1;
shape f_off64_64;
shape f_off64_32;
shape f_off64_16;
shape f_off64_8;
shape f_off64_1;
shape f_off512_512;
shape f_off512_64;
shape f_off512_32;
shape f_off512_16;
shape f_off512_8;
shape f_off512_1;

shape ucharsh;
shape scharsh;
shape uwordsh;
shape swordsh;
shape ulongsh;
shape slongsh;
shape u64sh;
shape s64sh;
shape shrealsh;
shape realsh;
shape doublesh;
shape shcomplexsh;
shape complexsh;
shape complexdoublesh;

shape f_bottom;
shape f_top;
shape f_local_label_value;

procprops f_dummy_procprops;
procprops f_var_callers = 1;
procprops f_var_callees = 2;
procprops f_untidy = 4;
procprops f_check_stack = 8;
procprops f_no_long_jump_dest = 16;
procprops f_inline = 32;

static proc_props initial_value_pp;

procprops
f_add_procprops(procprops t, procprops e)
{
	return t | e;
}


procprops no_procprops_option = 0;

procprops
yes_procprops_option(procprops p)
{
	return p;
}


void
init_procprops_option(void)
{
	return;
}


error_code f_overflow  = 7;
error_code f_nil_access = 19;
error_code f_stack_overflow = 35;

error_code_list
add_error_code_list(error_code_list t, error_code e, int i)
{
	UNUSED(i);
	return t | e;
}


error_code_list
new_error_code_list(int n)
{
	UNUSED(n);
	return 0;
}


transfer_mode f_trap_on_nil = 8;

shape
containedshape(int a, int s)
{
	switch ((a + 7) & ~7) {
	case  0:
	case  8: return s ? scharsh : ucharsh;
	case 16: return s ? swordsh : uwordsh;
	case 24:
	case 32: return s ? slongsh : ulongsh;
	case 40:
	case 48:
	case 56:
	case 64: return s ? s64sh : u64sh;

	default:
		error(ERROR_INTERNAL, "Illegal pointer for bitfield operations");
		return scharsh;
	}
}


dec *
make_extra_dec(char *nme, int v, int g, exp init, shape s)
{
	dec *extra_dec = (dec *)calloc(1, sizeof(dec));
	exp e = getexp(s, NULL, 0, init, NULL, 0, 0, ident_tag);
	setglob(e);
	if (v) {
		setvar(e);
	}
	brog(e) = extra_dec;
	extra_dec->def_next = NULL;
	*deflist_end = extra_dec;
	deflist_end = &((*deflist_end)->def_next);
	extra_dec->dec_u.dec_val.dec_id = nme;
	extra_dec->dec_u.dec_val.dec_shape = s;
	extra_dec->dec_u.dec_val.dec_exp = e;
	extra_dec->dec_u.dec_val.unit_number = crt_tagdef_unit_no;
	extra_dec->dec_u.dec_val.diag_info = NULL;
	extra_dec->dec_u.dec_val.extnamed = (unsigned int)g;
	extra_dec->dec_u.dec_val.dec_var = (unsigned int)v;
	extra_dec->dec_u.dec_val.dec_outermost = 0;
	extra_dec->dec_u.dec_val.have_def = init != NULL;
	extra_dec->dec_u.dec_val.processed = 0;
	extra_dec->dec_u.dec_val.isweak = 0;
	extra_dec->dec_u.dec_val.is_common = 0;
	if (init != NULL) {
		setfather(e, init);
	}
	return extra_dec;
}


dec *
find_named_dec(char *n)
{
	/* find a global with name n */
	dec *my_def = top_def;

	while (my_def != NULL) {
		char *id = my_def->dec_u.dec_val.dec_id;
		if (strcmp(id + strlen(name_prefix), n) == 0) {
			return my_def;
		}
		my_def = my_def->def_next;
	}
	return NULL;
}


exp
find_named_tg(char *n, shape s)
{
	/* find a global with name n */
	dec *my_def = find_named_dec(n);
	if (my_def != NULL) {
		return my_def->dec_u.dec_val.dec_exp;
	}
	my_def = make_extra_dec(add_prefix(name_prefix, n), 0, 1, NULL, s);
	return my_def->dec_u.dec_val.dec_exp;
}


char *
fn_of_op(int nm, int sngd)
{
	/* Find a run-time library fn corresponding to nm */

#define CSU(x, y)	return (sngd) ? x : y
	switch (nm) {
	case plus_tag:  CSU("__TDFUs_plus",  "__TDFUu_plus");
	case minus_tag: CSU("__TDFUs_minus", "__TDFUu_minus");
	case mult_tag:  CSU("__TDFUs_mult",  "__TDFUu_mult");
	case div0_tag:
	case div2_tag:  CSU("__TDFUs_div2",  "__TDFUu_div2");
	case div1_tag:  CSU("__TDFUs_div1",  "__TDFUu_div2");
	case rem0_tag:
	case rem2_tag:  CSU("__TDFUs_rem2",  "__TDFUu_rem2");
	case mod_tag:   CSU("__TDFUs_rem1",  "__TDFUu_rem2");
	case shl_tag:   CSU("__TDFUs_shl",   "__TDFUu_shl");
	case shr_tag:   CSU("__TDFUs_shr",   "__TDFUu_shr");
	case chvar_tag: CSU("__TDFUs_chvar", "__TDFUu_chvar");
	case max_tag:   CSU("__TDFUs_max",   "__TDFUu_max");
	case min_tag:   CSU("__TDFUs_min",   "__TDFUu_min");
	case test_tag:  CSU("__TDFUs_test",  "__TDFUu_test");
	case float_tag: CSU("__TDFUs_float", "__TDFUu_float");

	case neg_tag:   return "__TDFUneg";
	case abs_tag:   return "__TDFUabs";
	case and_tag:   return "__TDFUand";
	case or_tag:    return "__TDFUor";
	case xor_tag:   return "__TDFUxor";
	case not_tag:   return "__TDFUnot";

	default:
		error(ERROR_INTERNAL, "No fn for long op");
	}

	return "__TDFerror";
}


exp
TDFcallop3(exp arg1, exp arg2, int n)
{
	/* construct proc call for binary op corresponding to n */
	char *nm = fn_of_op(n, is_signed(sh(arg1)));
	exp dc;
	exp ob;
	exp_list pars;
	exp_option novar;
	exp res;
	novar.present = 0;
	dc = find_named_tg(nm, f_proc);
	ob = me_obtain(dc);
	pars.number = 2;
	pars.start = arg1;
	pars.end = arg2;
	bro(arg1) = arg2;
	clearlast(arg1);

	res = f_apply_proc(sh(arg1), ob, pars, novar);
	res = hold_refactor(res);
	return res;
}


exp
TDFwithet(error_treatment ov_err, exp e)
{
	exp id;
	exp c;
	exp_list el;
	exp Te;
	if (ov_err.err_code <= 2) {
		return e;
	}
	Te = find_named_tg("__TDFerror", slongsh);
	brog(Te)->dec_u.dec_val.dec_var = 1;
	if (keep_PIC_vars) {
		setvar(Te);
	} else if (PIC_code) {
		sh(Te) = f_pointer(f_alignment(slongsh));
	} else {
		setvar(Te);
	}
	id = me_startid(sh(e), e, 0);
	c = f_contents(slongsh, me_obtain(Te));
	el = new_exp_list(1);
	el = add_exp_list(el, f_plus(ov_err, me_shint(slongsh, (int)0x80000000),
				     c), 0);
	return me_complete_id(id, f_sequence(el, me_obtain(id)));
}


exp
TDFcallop2(error_treatment ov_err, exp arg1, exp arg2, int n)
{
	/* construct proc call for binary op corresponding to n */
	/* ignore error treatment for the moment */
	char *nm = fn_of_op(n, is_signed(sh(arg1)));
	exp dc;
	exp ob;
	exp_list pars;
	exp_option novar;
	exp res;
	novar.present = 0;
	dc = find_named_tg(nm, f_proc);
	ob = me_obtain(dc);
	pars.number = 2;
	pars.start = arg1;
	pars.end = arg2;
	bro(arg1) = arg2;
	clearlast(arg1);

	res = f_apply_proc((n==test_tag)?slongsh:sh(arg1), ob, pars, novar);

	return TDFwithet(ov_err, res);
}


exp
TDFcallaux(error_treatment ov_err, exp arg1, char *nm, shape s)
{
	exp dc;
	exp ob;
	exp_list pars;
	exp_option novar;
	exp res;
	novar.present = 0;
	dc = find_named_tg(nm, f_proc);
	ob = me_obtain(dc);
	pars.number = 1;
	pars.start = arg1;
	pars.end = arg1;

	res = f_apply_proc(s, ob, pars, novar);
	res = hold_refactor(res);
	return TDFwithet(ov_err, res);
}


exp TDFcallop1
(error_treatment ov_err, exp arg1, int n)
{
	/* construct proc call for unary op corresponding to n */
	/* ignore error treatment for the moment */
	char *nm = fn_of_op(n, is_signed(sh(arg1)));
	return TDFcallaux(ov_err, arg1, nm, sh(arg1));
}


exp
TDFcallop4(exp arg1, int n)
{
	/* construct proc call for unary op corresponding to n */

	char *nm = fn_of_op(n, is_signed(sh(arg1)));
	exp dc;
	exp ob;
	exp_list pars;
	exp_option novar;
	exp res;
	novar.present = 0;
	dc = find_named_tg(nm, f_proc);
	ob = me_obtain(dc);
	pars.number = 1;
	pars.start = arg1;
	pars.end = arg1;

	res = f_apply_proc(sh(arg1), ob, pars, novar);

	return res;
}


error_treatment f_wrap;
error_treatment f_impossible;
error_treatment f_continue;


static void
promote_actuals(exp par)
{
	for (;;) {
		shape s = sh(par);
		if (name(s) >= scharhd && name(s) <= uwordhd) {
			shape ns = (is_signed(s)) ? slongsh : ulongsh;
			exp w = hold_refactor(f_change_variety(f_wrap, ns,
							    copy(par)));
			replace(par, w, NULL);
			kill_exp(par, NULL);
			par = w;
		}
		if (last(par)) {
			break;
		}
		par = bro(par);
	}
}


static void
promote_formals(exp bdy)
{
	while ((name(bdy) == ident_tag && isparam(bdy))
#ifndef NEWDIAGS
	       || name(bdy) == diagnose_tag
#endif
	      ) {
		shape spar = sh(son(bdy));
		if (name(bdy) != ident_tag) {
			bdy = son(bdy);
			continue;
		}
		if (name(spar) >= scharhd && name(spar) <= uwordhd) {
			shape ns = (is_signed(spar)) ? slongsh : ulongsh;
			exp u = pt(bdy);
			exp w;
			sh(son(bdy)) = ns;
			if (!isvar(bdy)) {
				while (u != NULL) {
					exp nextu = pt(u);
					sh(u) = ns;
					w = f_change_variety(f_wrap, spar,
							     copy(u));
					replace(u, w, NULL);
					kill_exp(u, NULL);
					u = nextu;
				}
			} else {
				shape ps = f_pointer(f_alignment(ns));
				while (u != NULL) {
					exp nextu = pt(u);
					if (last(u) && name(bro(u)) == cont_tag) {
						if (endian == ENDIAN_LITTLE) {
							exp con = bro(u);
							sh(u) = ps;
							sh(con) = ns;
							w = f_change_variety(
							    f_wrap, spar,
							    copy(con));
							replace(con, w, NULL);
							kill_exp(con, NULL);
						}
					} else {
						setvis(bdy);
						if (endian == ENDIAN_BIG) {
							sh(u) = ps;
							no(u) = shape_size(ns) -
							    shape_size(spar);
						}
					}
					u = nextu;
				}
			}
		}
		bdy = bro(son(bdy));
	}
}


aldef frame_als[32];

alignment f_locals_alignment = &frame_als[0];
alignment nv_callers_alignment = &frame_als[1];
alignment var_callers_alignment = &frame_als[3];
alignment nv_callees_alignment = &frame_als[7];
alignment var_callees_alignment = &frame_als[15];

void
init_frame_als(void)
{
	int i;
	for (i = 0; i < 32; i++) {
		frame_als[i].al.sh_hd = 0;
		frame_als[i].al.al_n = 1;
		frame_als[i].al.al_val.al = 64;
		frame_als[i].al.al_val.al_frame = i + 1;
	}
}


error_treatment
f_trap(error_code_list ec)
{
	error_treatment res;
	res.err_code = ec;
	return res;
}


alignment
f_callers_alignment(bool var)
{
	return var ? var_callers_alignment : nv_callers_alignment;
}


alignment
f_callees_alignment(bool var)
{
	return var ? var_callees_alignment : nv_callees_alignment;
}


otagexp
f_make_otagexp(tag_option tagopt, exp e)
{
	exp init;
	if (!tagopt.present) {
		return e;
	}
	e = getexp(sh(e), NULL, 0, e, NULL, 0, 0, caller_tag);
	init = getexp(sh(e), NULL, 0, NULL , NULL, 0, 0, caller_name_tag);
	pt(e) = getexp(f_top, NULL, 0, init, NULL, 0, 0, ident_tag);
	/*  	setvar(pt(e));   - NOT ACCORDING TO SPEC */
	setfather(e, son(e));
	set_tag(tagopt.val, pt(e));
	return e;
}


otagexp_list
new_otagexp_list(int n)
{
	otagexp_list res;
	res.number =0;
	res.start = NULL;
	res.end = NULL;
	res.id = NULL;
	UNUSED(n);
	return res;
}


otagexp_list
add_otagexp_list(otagexp_list list, otagexp ote, int n)
{
	if (list.number++ == 0) {
		list.start = list.end = ote;
	} else {
		bro(list.end) = ote;
		clearlast(list.end);
		list.end = ote;
	}
	setlast(ote);
	if (name(ote) == caller_tag) {
		exp id = pt(ote);
		exp lid = list.id;
		bro(son(id)) = lid;
		if (lid != NULL) {
			bro(lid) = id;
			setlast(lid);
		}
		no(son(id)) = n;
		list.id = id;
		pt(ote) = NULL; /* this pt is a temp link */
	}
	return list;
}


callees
f_make_callee_list(exp_list args)
{
	exp e = getexp(f_top, NULL, 0, args.start, NULL, 0, args.number,
		       make_callee_list_tag);
	if (args.number != 0) {
		setfather(e, args.end);
		if (promote_pars) {
			promote_actuals(args.start);
		}
	}
	return e;
}


callees
f_make_dynamic_callees(exp ptr, exp sze)
{
	exp e = getexp(f_top, NULL, 0, ptr, NULL, 0, 0,
		       make_dynamic_callee_tag);
	bro(ptr) = sze;
	clearlast(ptr);
	setfather(e, sze);
	return e;
}


/* exps waiting to be used have the parked flag set in props,
   so that used_in need not look at their context.
   This procedure removes the parked flag from each member of an
   exp list, in preparation for putting them into their
   proper context.
 */
void
clear_exp_list(exp_list el)
{
	exp t = el.start;
	if (t == NULL) {
		return;
	}
	while (1) {
		parked(t) = 0;
		if (t == el.end) {
			return;
		}
		t = bro(t);
	}
}


alignment frame_alignment;

/* ntest codes */
ntest f_equal = 5;
ntest f_greater_than = 1;
ntest f_greater_than_or_equal = 2;
ntest f_less_than = 3;
ntest f_less_than_or_equal = 4;
ntest f_not_equal = 6;
ntest f_not_greater_than = 10;
ntest f_not_greater_than_or_equal = 9;
ntest f_not_less_than = 8;
ntest f_not_less_than_or_equal = 7;

ntest f_less_than_or_greater_than = 11;
ntest f_not_less_than_and_not_greater_than = 12;
ntest f_comparable = 13;
ntest f_not_comparable = 14;

static ntest convert_ntest[] = {0, 1, 2, 3, 4, 5, 6,
				1, 2, 3, 4, 6, 5, 13, 14};

static exp
replace_ntest(ntest nt, label dest, exp arg1, exp arg2)
{
	exp res;
	exp_list el;
	el = new_exp_list(2);
	el = add_exp_list(el, arg1, 0);
	el = add_exp_list(el, arg2, 1);

	if (nt == f_comparable) {
		res = f_make_top();
	} else {
		res = f_goto(dest);
	}

	return f_sequence(el, res);
}


/* rounding mode codes */
rounding_mode f_to_nearest = R2NEAR;
rounding_mode f_toward_larger = R2PINF;
rounding_mode f_toward_smaller = R2NINF;
rounding_mode f_toward_zero = R2ZERO;
rounding_mode f_round_as_state = 4;

transfer_mode f_standard_transfer_mode = 0;
transfer_mode f_volatile = 1;
transfer_mode f_overlap = 2;
transfer_mode f_complete = 4;

#define max(x, y)	((x) > (y)) ? (x) : (y)
/* careful: use simple arguments! */

alignment
f_alignment(shape sha)
{
	return align_of(sha);
}


  /* we may not yet know the actual values for the alignments,
     merely that they are computed from other alignments by unite.
     So we have to set up equations which are solved at the end of aldefs
  */
alignment
f_obtain_al_tag(al_tag a1)
{
	alignment j;
	if (a1->al.al_n == 1) {
		return long_to_al(a1->al.al_val.al);
	}
	j = (alignment)calloc(1, sizeof(aldef));
	j->al.al_n = 3;
	j->al.al_val.al_join.a = a1;
	j->next_aldef = top_aldef;
	top_aldef = j;
	return j;
}


alignment
f_unite_alignments(alignment a1, alignment a2)
{
	alignment j;
	if (a1->al.al_n == 1 && a2->al.al_n == 1) {
		if (a1->al.al_val.al_frame == a2->al.al_val.al_frame) {
			if (a1->al.al_val.al > a2->al.al_val.al) {
				return a1;
			} else {
				return a2;
			}
		} else if (a1->al.al_val.al_frame ==0) {
			return a2;
		} else if (a2->al.al_val.al_frame == 0) {
			return a1;
		} else {
			return &frame_als[(a1->al.al_val.al_frame |
					    a2->al.al_val.al_frame) -1];
		}
	}

	j = (alignment)calloc(1, sizeof(aldef));
	j->al.al_n = 2;
	j->al.al_val.al_join.a = a1;
	j->al.al_val.al_join.b = a2;
	j->next_aldef = top_aldef;
	top_aldef = j;
	return j;
}


void
init_access(void)
{
	return;
}


access f_dummy_access;

access f_visible = 1;
access f_standard_access = 0;
access f_long_jump_access = 2;
access f_constant = 4;
access f_no_other_read = 8;
access f_no_other_write = 16;
access f_register = 32;
access f_out_par = 64;
access f_used_as_volatile = 128;
access f_preserve = 256;

access
f_add_accesses(access a1, access a2)
{
	return a1 | a2;
}


alignment f_alloca_alignment;
alignment f_var_param_alignment;
alignment f_code_alignment;

static struct CAL {
	short sh_hd;
	short al;
	alignment res;
	struct CAL *rest;
} *cache_pals;

void
init_alignment(void)
{
	const_al1->al.al_n = 1;
	const_al1->al.al_val.al = 1;
	const_al1->al.al_val.al_frame = 0;
	const_al1->al.sh_hd = 0;
	const_al8->al.al_n = 1;
	const_al8->al.al_val.al = 8;
	const_al8->al.al_val.al_frame = 0;
	const_al8->al.sh_hd = 0;
	const_al16->al.al_n = 1;
	const_al16->al.al_val.al = 16;
	const_al16->al.al_val.al_frame = 0;
	const_al16->al.sh_hd = 0;
	const_al32->al.al_n = 1;
	const_al32->al.al_val.al = 32;
	const_al32->al.al_val.al_frame = 0;
	const_al32->al.sh_hd = 0;
	const_al64->al.al_n = 1;
	const_al64->al.al_val.al = 64;
	const_al64->al.al_val.al_frame = 0;
	const_al64->al.sh_hd = 0;
	const_al512->al.al_n = 1;
	const_al512->al.al_val.al = 512;
	const_al512->al.al_val.al_frame = 0;
	const_al512->al.sh_hd = 0;

	cache_pals = NULL;

	init_frame_als();
	f_alloca_alignment = ALLOCA_ALIGN;
	f_var_param_alignment = VAR_PARAM_ALIGN;
	f_code_alignment = CODE_ALIGN;
	stack_align = max(param_align, double_align);
	return;
}


alignment f_dummy_alignment;

static alignment
get_pal(alignment a, int sh_hd, int al)
{
	struct CAL *c = cache_pals;
	alignment res;
	while (c != NULL) {
		if (c->sh_hd == sh_hd && c->al == al) {
			return c->res;
		}
		c = c->rest;
	}
	res = (alignment)xmalloc(sizeof(aldef));
	*res = *a;
	res->al.sh_hd = sh_hd;
	c = (struct CAL *)xmalloc(sizeof(struct CAL));
	c->sh_hd = sh_hd;
	c->al = al;
	c->res = res;
	c->rest = cache_pals;
	cache_pals = c;
	return res;
}


alignment
f_parameter_alignment(shape sha)
{
	int n = name(sha);
	alignment t =
#if TRANS_SPARC
	    MIN_PAR_ALIGNMENT;
#else
	f_unite_alignments(MIN_PAR_ALIGNMENT, f_alignment(sha));
#endif
#if TRANS_HPPA
	if (shape_size(sha) > 64) {
		n = nofhd + 1;
	}
#endif
#if TRANS_SPARC
	if (sparccpd(sha)) {
		n = nofhd + 1;
	}
#endif

	return get_pal(t, n, shape_align(sha));
}


bitfield_variety
f_bfvar_bits(bool issigned, nat bits)
{
	bitfield_variety res;
	if (!nat_issmall(bits)) {
		error(ERROR_INTERNAL, TOO_MANY_BITS);
	}
	res.has_sign = issigned;
	res.bits = natint(bits);

	if (check & CHECK_EXTRA) {
		if (res.bits > SLONG_SZ) {
			error(ERROR_INTERNAL, TOO_MANY_BITS);
		}
	}

	return res;
}


void
init_bitfield_variety(void)
{
	return;
}


bitfield_variety f_dummy_bitfield_variety;

bool f_false = 0;
bool f_true = 1;

void
init_bool(void)
{
	return;
}


bool f_dummy_bool;

caselim
f_make_caselim(label branch, signed_nat lower, signed_nat upper)
{
	caselim c;
	c.lab = branch;
	c.low = lower;
	c.high = upper;
	return c;
}


callees f_dummy_callees;

callees f_same_callees;

void
init_callees(void)
{
	f_same_callees = getexp(f_top, NULL, 0, NULL, NULL, 0, 0,
				same_callees_tag);
	return;
}


void
init_caselim(void)
{
	return;
}


error_treatment
f_error_jump(label lab)
{
	error_treatment e;
	e.err_code = 4;
	e.jmp_dest = lab;
	return e;
}


error_code f_dummy_error_code;

void
init_error_code(void)
{
	return;
}


void
init_error_treatment(void)
{
	f_wrap.err_code = 1;
	f_impossible.err_code = 0;
	f_continue.err_code = 2;
	return;
}


error_treatment f_dummy_error_treatment;

exp
f_abs(error_treatment ov_err, exp arg1)
{
	if (name(sh(arg1)) == bothd || !is_signed(sh(arg1))) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (!is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_ABS);
		}
	}

	if (~has & HAS_64_BIT && name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || ov_err.err_code > 2)) {
		return TDFcallop1(ov_err, arg1, abs_tag);
	}

	return me_u1(ov_err, arg1, abs_tag);
}


exp
f_add_to_ptr(exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!doing_aldefs && (name(sh(arg1)) != ptrhd ||
				      name(sh(arg2)) != offsethd ||
				      (al1(sh(arg1)) < al1(sh(arg2))
#if TRANS_SPARC
			     	  && al1_of(sh(arg2)) != REAL_ALIGN
#endif
				       ))) {
			error(ERROR_INTERNAL, CHSH_ADDPTR);
		}
	}

#if TRANS_SPARC || TRANS_HPPA
	if ((al1_of(sh(arg2))->al.al_val.al_frame & 6) != 0 &&
#else
	if ((al1_of(sh(arg2))->al.al_val.al_frame & 4) != 0 &&
#endif
	    al2_of(sh(arg2))->al.sh_hd > nofhd) {
		/* indirect varargs param */
		exp z = me_b3(f_pointer(f_alignment(sh(arg1))), arg1, arg2,
			      addptr_tag);
		return f_contents(sh(arg1), z);
	}

	return me_b3(f_pointer(al2_of(sh(arg2))), arg1, arg2, addptr_tag);
}


exp
f_and(exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!eq_shape(sh(arg1), sh(arg2)) || !is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_AND);
		}
	}

	if (~has & HAS_64_BIT && name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag)) {
		return TDFcallop3(arg1, arg2, and_tag);
	}

	return me_b2(arg1, arg2, and_tag);
}


exp
f_apply_proc(shape result_shape, exp arg1, exp_list arg2, exp_option varparam)
{
	exp res = getexp(result_shape, NULL, 0, arg1, NULL, 0, 0,
			 apply_tag);
	int varhack = 0;
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (name(sh(arg1)) != prokhd) {
			error(ERROR_INTERNAL, CHSH_APPLY);
		}
	}

	if (varparam.present) {
		/* add a declaration for variable parameters */
		arg2 = add_exp_list(arg2, varparam.val, arg2.number + 1);
		varhack =1;
	}

	clear_exp_list(arg2);

	if (name(arg1) == name_tag && isglob(son(arg1)) && !isvar(son(arg1))) {
		exp e;

		/* check for substitutions for certain global procedures */
		if (special_fn(arg1, arg2.start, result_shape, &e)) {
			return e;
		}
	}

	if (arg2.number==0) {
		setfather(res, arg1);
	} else {
		clearlast(arg1);
		bro(arg1) = arg2.start;
		setfather(res, arg2.end);
		if (promote_pars) {
			promote_actuals(bro(son(res)));
		}
	}

	/* rewrite struct/union value parameters as pointer-to-copy */
	if (redo_structparams && arg2.number > 0) {
		/* has >0 params */
		exp param, prev;

		prev = arg1;
		param = bro(arg1);

		while (1 /*"break" below*/) {
			if ((varhack && last(param)) ||
#if TRANS_HPPA
			    ((name(sh(param)) == cpdhd ||
			      name(sh(param)) == nofhd ||
			      name(sh(param)) == doublehd) &&
			     (shape_size(sh(param)) > 64)))
#else
#if TRANS_SPARC
				sparccpd(sh(param)))
#else
				    name(sh(param)) == cpdhd ||
				    name(sh(param)) == nofhd ||
				    name(sh(param)) == doublehd)
#endif
#endif
				    {
					    /*
					     * param IS struct/union-by-value,
					     * pass indirectly: make a local
					     * copy of param and in the
					     * parameter list replacce param by
					     * pointer to the copy.
					     *
					     * From:(apply_tag arg1 ...param...)
					     *
					     * Make:(new_ident param(apply_tag
					     * arg1 .... new_par ...))
					     *              Where new_par =
					     *              pointer-to-new_ident
					     */
					    exp new_par, new_ident;
					    shape ptr_s =
						f_pointer(f_alignment(sh(param)));

					    /* new_ident: (ident_tag sh=sh(res)
					       no=1 pt=new_par param res) */
					    new_ident = getexp(sh(res),
							       bro(res),
							       (int)last(res),
							       param, NULL, 0,
							       1, ident_tag);

					    setvar(new_ident);
					    /* taking its address below*/

					    /* new_par: (name_tag sh=ptr_s pt=0
					       new_ident) */
					    new_par = getexp(ptr_s, bro(param),
							     (bool)last(param),
							     new_ident, NULL,
							     0, 0, name_tag);
					    pt(new_ident) = new_par;
					    /* use of new new_ident by new_par*/
					    setlastuse(new_par);
					    /* ... is last-and-only use of
					       new_ident */

					    /* install res as body of
					       new_ident */
					    clearlast(param);
					    bro(param) = res;

					    setlast(res);
					    bro(res) = new_ident;

					    bro(prev) = new_par;

					    res = new_ident;
					    /* all done */

					    /* iteration */
					    if (last(new_par)) {
						    break;
					    }

					    param = bro(new_par);
					    prev = new_par;
				    } else {
					    /* iteration */
					    if (last(param)) {
						    break;
					    }

					    prev = param;
					    param = bro(param);
				    }
		}
	}


	/* apply this transformation if the procedure has a structure-like
	   result and we want to make a new first parameter which is
	   a reference to where the result is to go. */
	if (redo_structfns && !reg_result(result_shape)) {
		/* replace f(x) by {var r; f(r, x); cont(r)} */
		exp init, vardec, cont, contname, seq, app, appname, t;
		exp_list list;
		shape ptr_res_shape = f_pointer(f_alignment(result_shape));

		init = getexp(result_shape, NULL, 0, NULL, NULL, 0, 0,
			      clear_tag);
		vardec = getexp(result_shape, NULL, 0, init, NULL, 0, 1,
				ident_tag);
		setvar(vardec);
		contname = getexp(ptr_res_shape, NULL, 0, vardec, NULL, 0,
				  0, name_tag);
		pt(vardec) = contname;
		cont = f_contents(result_shape, contname);
		appname = getexp(ptr_res_shape, bro(son(res)), 0, vardec,
				 contname, 0, 0, name_tag);
		++no(vardec);
		pt(vardec) = appname;
		app = getexp(f_top, NULL, 0, son(res), NULL, 0, 32,
			     apply_tag);
		if (last(son(res))) {
			clearlast(son(res));
			setlast(appname);
			bro(appname) = app;
		}
		bro(son(res)) = appname;
		t = son(app);
		list.number = 1;
		while (!last(t)) {
			t = bro(t);
		}
		bro(t) = app;
		list.start = app;
		list.end = app;
		seq = f_sequence(list, cont);
		bro(init) = seq;
		setfather(vardec, seq);
		retcell(res);
		return vardec;
	}

	return res;
}


exp
f_assign(exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	return me_b3(f_top, arg1, arg2, ass_tag);
}


exp
f_assign_with_mode(transfer_mode md, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (md & f_complete) {
		exp d = me_startid(f_top, arg2, 0);
		return me_complete_id(d, f_assign_with_mode(md & ~f_complete,
							    arg1,
							    me_obtain(d)));
	}

	if (trap_on_nil_contents && (md & f_trap_on_nil) != 0) {
		exp d = me_startid(f_top, arg1, 0);
		exp hldr = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, 0);
		exp lb = getexp(f_top, NULL, 0, hldr, NULL, 0, 0,
				labst_tag);
		exp_list el;
		exp test = me_q1(no_nat_option, f_equal, &lb, me_obtain(d),
				 f_make_null_ptr(al1_of(sh(arg1))), test_tag);
		exp trp = getexp(f_bottom, NULL, 0, NULL, NULL, 0,
				 f_nil_access, trap_tag);
		md &= ~f_trap_on_nil;
		el = new_exp_list(1);
		el = add_exp_list(el, test, 1);
		return me_complete_id(d, f_conditional(&lb, f_sequence(el, trp),
						       f_assign_with_mode(md,
						       me_obtain(d), arg2)));
	}

	if ((md & f_volatile) != 0) {
		return me_b3(f_top, arg1, arg2, assvol_tag);
	} else if ((md & f_overlap) &&
		   (name(arg2) == cont_tag || name(arg2) == contvol_tag) &&
		   !reg_result(sh(arg2))) {
		return f_move_some(md, son(arg2), arg1,
				   f_shape_offset(sh(arg2)));
	} else {
		return me_b3(f_top, arg1, arg2, ass_tag);
	}
}


exp
f_bitfield_assign(exp p, exp off, exp val)
{
	exp res;
	if (name(sh(p)) == bothd) {
		return p;
	}
	if (name(sh(val)) == bothd) {
		return val;
	}

	if (check & CHECK_SHAPE) {
		if (name(sh(p)) != ptrhd || name(sh(off)) != offsethd) {
			error(ERROR_INTERNAL, CHSH_BFASS);
		}
	}

	if (name(off) == val_tag) {
		res = me_b3(f_top, p, val, bfass_tag);
		no(res) = no(off);
		return res;
	} else {
		int alofptr = al1(sh(p));
		shape s = containedshape(alofptr, 0);
		shape bfs = sh(val);
		int nbits = shape_size(sh(val));
		alignment als = f_alignment(s);
		alignment alb = long_to_al(1);
		shape os = f_offset(als, als);
		shape bos = f_offset(alb, alb);
		exp mask0 = getexp(s, NULL, 0, NULL, NULL, 0,
				   ((1 << nbits) -1), val_tag);

		exp noff1 = getexp(sh(off), NULL, 0, NULL, NULL, 0, 0,
				   name_tag);
		exp noff2 = getexp(sh(off), NULL, 0, NULL, noff1, 0, 0,
				   name_tag);
		exp idoff = getexp(f_top, NULL, 0, off, noff2, 0, 2,
				   ident_tag);
		son(noff1) = idoff; son(noff2) = idoff;
		{
			exp v, idbnt;
			exp pn1, pn2, idpn;
			exp cnt; exp mask1; exp orit; exp asit;
			exp addbf = f_offset_add(noff1, f_shape_offset(bfs));
			exp byteoffinit = f_offset_subtract(hold_refactor(
					  f_offset_pad(als, addbf)),
					  hold_refactor(f_offset_pad(als,
					  f_shape_offset(s))));
			exp v1bit = getexp(bos, NULL, 0, NULL, NULL, 0, 1,
					   val_tag);
			exp nby1 = getexp(os, NULL, 0, NULL, NULL, 0, 0,
					  name_tag);
			exp nby2 = getexp(os, NULL, 0, NULL, nby1, 0, 0,
					  name_tag);
			exp nby3 = getexp(os, NULL, 0, NULL, nby2, 0, 0,
					  name_tag);
			exp idby = getexp(f_top, idoff, 1, byteoffinit, nby3, 0,
					  3, ident_tag);
			exp bitoffinit = f_offset_div(ulongsh,
					 f_offset_subtract(noff2,
					 f_offset_pad(f_alignment(bfs), nby2)),
					 v1bit);
			exp bnt1 = getexp(ulongsh, NULL, 0, NULL, NULL, 0,
					  0, name_tag);
			exp bnt2 = getexp(ulongsh, NULL, 0, NULL, bnt1, 0,
					  0, name_tag);

			switch (endian) {
			case ENDIAN_LITTLE:
				idbnt = getexp(f_top, idby, 1, bitoffinit, bnt2, 0,
					   2, ident_tag);
				break;
			case ENDIAN_BIG:
				v = getexp(ulongsh, NULL, 0, NULL, NULL, 0,
					shape_size(s) - nbits, val_tag);
				idbnt = getexp(f_top, idby, 1, f_minus(f_wrap, v,
					bitoffinit), bnt2, 0, 2, ident_tag);
				break;
			}

			pn1 = getexp(sh(p), NULL, 0, NULL, NULL, 0, 0,
				 name_tag);
			pn2 = getexp(sh(p), NULL, 0, NULL, pn1, 0, 0,
				 name_tag);
			idpn = getexp(f_top, idbnt, 1,
				  f_add_to_ptr(p, nby1), pn2, 0, 2, ident_tag);

			son(nby1) = idby; son(nby2) = idby; son(nby3) = idby;
			son(bnt1) = idbnt; son(bnt2) = idbnt;
			son(pn1) = idpn; son(pn2) = idpn;
			bro(son(idby)) = idbnt; clearlast(son(idby));
			bro(son(idbnt)) = idpn; clearlast(son(idbnt));
			bro(son(idoff)) = idby; clearlast(son(idoff));

			mask1 = f_not(f_shift_left(f_wrap, mask0, bnt1));
			cnt = f_and(f_contents(s, pn1), mask1);
			orit = f_or(cnt, f_shift_left(f_wrap,
			    f_change_bitfield_to_int(s, val), bnt2));
			asit = f_assign(pn2, orit);
			bro(son(idpn)) = asit; clearlast(son(idpn));
			bro(asit) = idpn; setlast(asit);

			return idoff;
		}
	}
}


exp
f_bitfield_assign_with_mode(transfer_mode md, exp p, exp off, exp val)
{
	exp res;
	if (name(sh(p)) == bothd) {
		return p;
	}
	if (name(sh(val)) == bothd) {
		return val;
	}

	if (md == f_standard_transfer_mode) {
		return f_bitfield_assign(p, off, val);
	}

	if (check & CHECK_SHAPE) {
		if (name(sh(p)) != ptrhd || name(sh(off)) != offsethd ||
		    name(off) != val_tag) {
			error(ERROR_INTERNAL, CHSH_BFASS);
		}
	}

	if (trap_on_nil_contents && (md & f_trap_on_nil) != 0) {
		exp d = me_startid(f_top, p, 0);
		exp hldr = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, 0);
		exp lb = getexp(f_top, NULL, 0, hldr, NULL, 0, 0,
				labst_tag);
		exp_list el;
		exp test = me_q1(no_nat_option, f_equal, &lb, me_obtain(d),
				 f_make_null_ptr(al1_of(sh(p))), test_tag);
		exp trp = getexp(f_bottom, NULL, 0, NULL, NULL, 0,
				 f_nil_access, trap_tag);
		md &= ~f_trap_on_nil;
		el = new_exp_list(1);
		el = add_exp_list(el, test, 1);
		return me_complete_id(d, f_conditional(&lb, f_sequence(el, trp),
		    f_bitfield_assign_with_mode(md, me_obtain(d), off, val)));
	}

	if (md & f_volatile) {
		res = me_b3(f_top, p, val, bfassvol_tag);
	} else {
		res = me_b3(f_top, p, val, bfass_tag);
	}

	no(res) = no(off);
	return res;
}

exp
f_bitfield_contents(bitfield_variety bf, exp p, exp off)
{
	exp res;
	if (name(sh(p)) == bothd) {
		return off;
	}
	if (name(sh(off)) == bothd) {
		return p;
	}

	if (check & CHECK_SHAPE) {
		if (name(sh(p)) != ptrhd || name(sh(off)) != offsethd)
			error(ERROR_INTERNAL, CHSH_BFCONT);
	}

	if (name(off) == val_tag) {
		res = me_u3(f_bitfield(bf), p, bfcont_tag);
		no(res) = no(off);
		return res;
	} else {
		int alofptr = al1(sh(p));
		shape s = containedshape(alofptr, bf.has_sign);
		shape bfs = f_bitfield(bf);
		alignment als = f_alignment(s);
		alignment alb = long_to_al(1);
		shape ob = f_offset(alb, alb);
		shape os = f_offset(als, als);
		exp noff1 = getexp(sh(off), NULL, 0, NULL, NULL, 0, 0,
				   name_tag);
		exp noff2 = getexp(sh(off), NULL, 0, NULL, noff1, 0, 0,
				   name_tag);
		exp idoff = getexp(s, NULL, 0, off, noff2, 0, 2, ident_tag);
		son(noff1) = idoff; son(noff2) = idoff;
		{
			exp addbf = f_offset_add(noff1, f_shape_offset(bfs));
			exp byteoffinit =
			    f_offset_subtract(hold_refactor(f_offset_pad(als,
			    addbf)), hold_refactor(f_offset_pad(als,
			    f_shape_offset(s))));
			exp nby1 = getexp(os, NULL, 0, NULL, NULL, 0, 0,
					  name_tag);
			exp nby2 = getexp(os, NULL, 0, NULL, nby1, 0, 0,
					  name_tag);
			exp idby = getexp(s, NULL, 0, byteoffinit, nby2, 0, 2,
					  ident_tag);
			exp cnt; exp sh1; exp sh2; exp bitoff; exp shl;
			exp v = getexp(ulongsh, NULL, 0, NULL, NULL, 0,
				       shape_size(s) - bf.bits, val_tag);
			exp v1bit = getexp(ob, NULL, 0, NULL, NULL, 0, 1,
					   val_tag);
			son(nby1) = idby; son(nby2) = idby;
			cnt = f_contents(s, f_add_to_ptr(p, nby1));
			bitoff =
			    f_offset_div(ulongsh, f_offset_subtract(noff2,
			    f_offset_pad(f_alignment(bfs), nby2)), v1bit);
 			switch (endian) {
			case ENDIAN_LITTLE:
				shl = f_minus(f_wrap, copy(v), bitoff);
				break;
			case ENDIAN_BIG:
				shl = bitoff;
				break;
			}
			sh1 = f_shift_left(f_wrap, cnt, shl);
			sh2 = f_shift_right(sh1, v);
			bro(byteoffinit) = sh2; clearlast(byteoffinit);
			bro(sh2) = idby; setlast(sh2);
			bro(off) = idby; clearlast(off);
			bro(idby) = idoff; setlast(idby);
			return f_change_int_to_bitfield(bf, idoff);
		}
	}
}


exp
f_bitfield_contents_with_mode(transfer_mode md, bitfield_variety bf, exp p,
			      exp off)
{
	exp res;
	if (name(sh(p)) == bothd) {
		return p;
	}

	if (check & CHECK_SHAPE) {
		if (name(sh(p)) != ptrhd || name(sh(off)) != offsethd ||
		    name(off) != val_tag) {
			error(ERROR_INTERNAL, CHSH_BFCONT);
		}
	}

	if (trap_on_nil_contents && (md & f_trap_on_nil) != 0) {
		exp d = me_startid(f_bitfield(bf), p, 0);
		exp hldr = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, 0);
		exp lb = getexp(f_top, NULL, 0, hldr, NULL, 0, 0,
				labst_tag);
		exp_list el;
		exp test = me_q1(no_nat_option, f_equal, &lb, me_obtain(d),
				 f_make_null_ptr(al1_of(sh(p))), test_tag);
		exp trp = getexp(f_bottom, NULL, 0, NULL, NULL, 0,
				 f_nil_access, trap_tag);
		md &= ~f_trap_on_nil;
		el = new_exp_list(1);
		el = add_exp_list(el, test, 1);
		return me_complete_id(d, f_conditional(&lb, f_sequence(el, trp),
		    f_bitfield_contents_with_mode(md, bf, me_obtain(d), off)));
	}

	if (md == f_volatile) {
		res = me_u3(f_bitfield(bf), p, bfcontvol_tag);
	} else {
		res = me_u3(f_bitfield(bf), p, bfcont_tag);
	}

	no(res) = no(off);
	return res;
}


exp
f_case_transform(bool exhaustive, exp control, caselim_list branches)
{
	exp r, ht;
	shape case_shape;
	exp changer;
	exp body_of_ident;
	exp control_expression;
	exp body_of_case;
	exp id;
	exp copy_ce;
	shape changer_shape = (shape_size(sh(control)) >= SLONG_SZ) ?
	    sh(control) : is_signed(sh(control)) ? slongsh : ulongsh;

	/*  UNUSED(branches);
	 */
	if (name(sh(control)) == bothd) {
		return control;
	}

	bro(global_case) = NULL;
	while (branches != NULL) {
		exp hd = branches;
		branches = bro(branches);
		bro(hd) = NULL;
		sh(hd) = sh(control);
		if (son(hd) != NULL) {
			sh(son(hd)) = sh(control);
		}
		if (son(hd) != NULL &&
		    docmp_f((int)f_less_than, son(hd), hd)) {
			--no(son(pt(hd)));
			retcell(son(hd));
			retcell(hd);
		} else {
			case_item(hd);
		}
	}

	if (bro(global_case) == NULL) {
		return control;
	}
	case_shape = (exhaustive)? f_bottom : f_top;

	if (PIC_code) {
		proc_externs = 1;
	}

	if (check & CHECK_SHAPE) {
		if (!is_integer(sh(control))) {
			error(ERROR_INTERNAL, CHSH_CASE);
		}
	}

	r = getexp(case_shape, NULL, 0, control, NULL, 0, 0, case_tag);
	clearlast(control);
	bro(control) = bro(global_case);
	ht = control;
	while (bro(ht) != NULL) {
		ht = bro(ht);
		sh(ht) = changer_shape;
		if (son(ht) != NULL) {
			sh(son(ht)) = changer_shape;
		}
	}
	setlast(ht);
	bro(ht) = r;

	control_expression = son(r);
	body_of_case = bro(son(r));

	copy_ce = copy(control_expression);
	changer = hold_refactor(me_u3(changer_shape, control_expression,
				   chvar_tag));
	id = me_startid(sh(changer), changer, 1);
	/* the shape of the ident will be overwritten by me_complete_id */
	body_of_ident = case_optimisation(body_of_case, id, sh(r), copy_ce);
	id = me_complete_id(id, body_of_ident);

#ifdef NEWDIAGS
	if (extra_diags) {
		id = f_dg_exp(id, f_branch_dg(f_dg_null_sourcepos));
	}
#endif

	return hold_refactor(id);
}

static exp
f_case_notransform(bool exhaustive, exp control, caselim_list branches)
{
	exp r, ht;
	shape case_shape;
	/*  UNUSED(branches);
	    if (name(sh(control)) == bothd || bro(global_case) == NULL)
	    return control;
	 */
	if (name(sh(control)) == bothd) {
		return control;
	}

	bro(global_case) = NULL;
	while (branches != NULL) {
		exp hd = branches;
		branches = bro(branches);
		bro(hd) = NULL;
		sh(hd) = sh(control);
		if (son(hd) != NULL) {
			sh(son(hd)) = sh(control);
		}
		if (son(hd) != NULL &&
		    docmp_f((int)f_less_than, son(hd), hd)) {
			--no(son(pt(hd)));
			retcell(son(hd));
			retcell(hd);
		} else {
			case_item(hd);
		}
	}
	if (bro(global_case) == NULL) {
		return control;
	}
	case_shape = (exhaustive) ? f_bottom : f_top;

	if (PIC_code) {
		proc_externs = 1;
	}

	if (check & CHECK_SHAPE) {
		if (!is_integer(sh(control))) {
			error(ERROR_INTERNAL, CHSH_CASE);
		}
	}

	r = getexp(case_shape, NULL, 0, control, NULL, 0, 0, case_tag);
	clearlast(control);
	bro(control) = bro(global_case);
	ht = control;
	while (bro(ht) != NULL) {
		ht = bro(ht);
		sh(ht) = sh(control);
		if (son(ht) != NULL) {
			sh(son(ht)) = sh(control);
		}
	}
	setlast(ht);
	bro(ht) = r;

#ifdef NEWDIAGS
	if (extra_diags) {
		r = f_dg_exp(r, f_branch_dg(f_dg_null_sourcepos));
	}
#endif

	return r;
}

exp
f_case(bool exhaustive, exp control, caselim_list branches)
{
	if (optim & OPTIM_CASE) {
		return f_case_transform(exhaustive, control, branches);
	} else {
		return f_case_notransform(exhaustive, control, branches);
	}
}


exp
f_change_bitfield_to_int(variety x, exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (name(sh(arg1)) != bitfhd) {
			error(ERROR_INTERNAL, CHSH_CHBITFIELD);
		}
	}

	if (~has & HAS_64_BIT && shape_size(x) >32) {
		shape n32 = (is_signed(x)) ? slongsh : ulongsh;
		exp z = hold_refactor(me_c2(n32, arg1, bitf_to_int_tag));
		return f_change_variety(f_impossible, x, z);
	}

	return me_c2(f_integer(x), arg1, bitf_to_int_tag);
}


exp
f_change_int_to_bitfield(bitfield_variety x, exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (!is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_CHINTBF);
		}
	}

	if (~has & HAS_64_BIT && shape_size(sh(arg1)) >32) {
		shape n32 = (is_signed(sh(arg1))) ? slongsh : ulongsh;
		arg1 = hold_refactor(f_change_variety(f_wrap, n32, arg1));
	}

	return me_c2(f_bitfield(x), arg1, int_to_bitf_tag);
}



exp
f_change_variety(error_treatment ov_err, variety r, exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (!is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_CHVAR);
		}
	}

	if (~has & HAS_64_BIT && ((name(arg1) != val_tag || ov_err.err_code > 2) &&
	    (shape_size(sh(arg1)) > 32 || name(r) >=s64hd) &&
	    name(sh(arg1)) != name(r))) {
		exp e = arg1;
		int ss = is_signed(sh(arg1));
		int sd = is_signed(r);
		shape x = (ss)?slongsh:ulongsh;
		if (shape_size(sh(arg1)) <= 32) {
			exp e = hold_refactor(me_c1(x, ov_err, arg1, chvar_tag));
			exp z = TDFcallaux(ov_err, e, (sd) ? ((ss) ?
			    "__TDFUsswiden" : "__TDFUuswiden") : (ss) ?
			    "__TDFUsuwiden" : "__TDFUuuwiden", r);
			return z;
		} else if (name(r) >= s64hd) {
			return TDFcallaux(ov_err, e, (sd) ? "__TDFUu642s64" :
					  "__TDFUs642u64", r);
		} else {
			exp e = TDFcallaux(ov_err, arg1, (sd) ?
			    ((ss) ? "__TDFUssshorten" : "__TDFUusshorten") :
			    (ss) ?  "__TDFUsushorten" : "__TDFUuushorten",
			    (sd) ? slongsh : ulongsh);
			return hold_refactor(me_c1(f_integer(r), ov_err, e,
						chvar_tag));
		} 
	}

	return me_c1(f_integer(r), ov_err, arg1, chvar_tag);
}


exp
f_component(shape sha, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!doing_aldefs &&
		    (name(sh(arg2)) != offsethd || name(sh(arg1)) != cpdhd ||
		     shape_align(sh(arg1)) < al1(sh(arg2)) ||
		     shape_align(sha) > al2(sh(arg2)))) {
			error(ERROR_INTERNAL, CHSH_COMPONENT);
		}
	}

	return me_b3(sha, arg1, arg2, component_tag);
}


exp
f_concat_nof(exp arg1, exp arg2)
{
	shape sha = getshape(0, const_al1, al2_of(sh(arg1)), align_of(sh(arg1)),
			     shape_size(sh(arg1)) + shape_size(sh(arg2)),
			     nofhd);
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	/* al2_of(sh(arg1)) is the shapemacs.h hd of the nof shape */
	if (check & CHECK_SHAPE) {
		if (!doing_aldefs && (shape_align(sh(arg1)) != shape_align(sh(arg2)))) {
			error(ERROR_INTERNAL, CHSH_CONCATNOF);
		}
	}

	return me_b3(sha, arg1, arg2, concatnof_tag);
}


exp
f_conditional(label alt_label_intro, exp first, exp alt)
{
	shape res_shape;
	exp r, labst, def;
	labst = get_lab(alt_label_intro);

	res_shape = lub_shape(sh(first), sh(alt));
	r = getexp(res_shape, NULL, 0, first, NULL, 0, 0, cond_tag);
	def = son(labst);
	setbro(first, labst);
	clearlast(first);
	setbro(def, alt);
	clearlast(def);
	setbro(alt, labst);
	setlast(alt);
	setsh(labst, sh(alt));
	setfather(r, labst);
	default_freq = (float)(2.0 * default_freq);
	return r;
}


void
start_conditional(label alt_label_intro)
{
	exp tg;
	exp labst;
	tg = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, clear_tag);
	labst = getexp(f_bottom, NULL, 0, tg, NULL, 0, 0, labst_tag);
	default_freq = (float)(default_freq / 2.0);
	fno(labst) = default_freq;
	++proc_label_count;
	set_lab(alt_label_intro, labst);
	return;
}


exp
f_contents(shape s, exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (!doing_aldefs &&
		    (name(sh(arg1)) != ptrhd ||
		     (al1(sh(arg1)) < shape_align(s)
#if TRANS_SPARC
		      && align_of(s) != REAL_ALIGN
#endif
		      ))) {
			error(ERROR_INTERNAL, CHSH_CONTENTS);
		}
	}

	return me_c2(s, arg1, cont_tag);
}


exp
f_contents_with_mode(transfer_mode md, shape s, exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (!doing_aldefs &&
		    (name(sh(arg1)) != ptrhd ||
		     (al1(sh(arg1)) < shape_align(s) &&
		      al1_of(sh(arg1))->al.sh_hd != doublehd))) {
			error(ERROR_INTERNAL, CHSH_CONTENTS_VOL);
		}
	}

	if (trap_on_nil_contents && (md & f_trap_on_nil) != 0) {
		exp d = me_startid(s, arg1, 0);
		exp hldr = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, 0);
		exp lb = getexp(f_top, NULL, 0, hldr, NULL, 0, 0,
				labst_tag);
		exp_list el;
		exp test = me_q1(no_nat_option, f_equal, &lb, me_obtain(d),
				 f_make_null_ptr(f_alignment(s)), test_tag);
		exp trp = getexp(f_bottom, NULL, 0, NULL, NULL, 0,
				 f_nil_access, trap_tag);
		md &= ~f_trap_on_nil;
		el = new_exp_list(1);
		el = add_exp_list(el, test, 1);
		return me_complete_id(d, f_conditional(&lb, f_sequence(el, trp),
		    f_contents_with_mode(md, s, me_obtain(d))));
	}

	if (md & f_volatile) {
		return me_c2(s, arg1, contvol_tag);
	} else {
		return me_c2(s, arg1, cont_tag);
	}
}


exp
f_current_env(void)
{
	if (!in_proc_def) {
		error(ERROR_INTERNAL, "current_env must be in proc definition");
	}
	uses_crt_env = 1;
	uses_loc_address = 1;
	return getexp(f_pointer(frame_alignment), NULL, 0, NULL, NULL, 0,
		      0, current_env_tag);
}


int
eq_et(error_treatment a, error_treatment b)
{
	return a.err_code == b.err_code &&
		(a.err_code != 4 || a.jmp_dest == b.jmp_dest);
}


exp
div_rem(error_treatment div0_err, error_treatment ov_err, exp arg1, exp arg2,
	exp(*f)(error_treatment, exp, exp))
{
	if (eq_et(div0_err, ov_err) || eq_et(ov_err, f_impossible)) {
		return f(div0_err, arg1, arg2);
	} else if (eq_et(div0_err, f_impossible)) {
		return f(ov_err, arg1, arg2);
	} else {
		exp da2 = me_startid(sh(arg1), arg2, 0);
		exp hldr = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, 0);
		exp lb = getexp(f_top, NULL, 0, hldr, NULL, 0, 0,
				labst_tag);
		exp tst = f_integer_test(no_nat_option, f_equal, &lb,
					 me_obtain(da2), me_shint(sh(arg2), 0));
		exp_list st;
		exp wrong;
		st = new_exp_list(1);
		st = add_exp_list(st, tst, 0);
		if (div0_err.err_code == 4) {
			wrong = f_goto(div0_err.jmp_dest);
		} else if (div0_err.err_code > 4) {
			wrong = getexp(f_bottom, NULL, 0, NULL, NULL, 0,
				       f_overflow, trap_tag);
		} else {
			wrong = me_shint(sh(arg1), 0);
		}
		return me_complete_id(da2, f_conditional(&lb, f_sequence(st,
		    wrong), f(ov_err, arg1, me_obtain(da2))));
	}
}


exp
div0_aux(error_treatment ov_err, exp arg1, exp arg2)
{
	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag ||
	     ov_err.err_code > 2))) {
		return TDFcallop2(ov_err, arg1, arg2, div0_tag);
	}

	if (has & HAS_DIV0) {
		return me_b1(ov_err, arg1, arg2, div0_tag);
	}

	if (name(arg2) == val_tag && !isbigval(arg2)) {
		int n = no(arg2);
		if ((n & (n - 1)) == 0) {
			return me_b1(ov_err, arg1, arg2, div1_tag);
		}
	}
	return me_b1(ov_err, arg1, arg2, div2_tag);
}


exp
f_div0(error_treatment div0_err, error_treatment ov_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!eq_shape(sh(arg1), sh(arg2)) || !is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_DIV0);
		}
	}

	return div_rem(div0_err, ov_err, arg1, arg2, div0_aux);
}


exp
div1_aux(error_treatment ov_err, exp arg1, exp arg2)
{
	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag ||
	     ov_err.err_code > 2))) {
		return TDFcallop2(ov_err, arg1, arg2, div1_tag);
	}

	return me_b1(ov_err, arg1, arg2, div1_tag);
}


exp
f_div1(error_treatment div0_err, error_treatment ov_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!eq_shape(sh(arg1), sh(arg2)) || !is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_DIV1);
		}
	}

	return div_rem(div0_err, ov_err, arg1, arg2, div1_aux);
}


exp
div2_aux(error_treatment ov_err, exp arg1, exp arg2)
{
	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag ||
	     ov_err.err_code > 2))) {
		return TDFcallop2(ov_err, arg1, arg2, div2_tag);
	}

	return me_b1(ov_err, arg1, arg2, div2_tag);
}

exp
f_div2(error_treatment div0_err, error_treatment ov_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!eq_shape(sh(arg1), sh(arg2)) || !is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_DIV2);
		}
	}

	return div_rem(div0_err, ov_err, arg1, arg2, div2_aux);
}


exp
f_env_offset(alignment fa, alignment y, tag t)
{
	exp e = get_tag(t);
	shape s = f_offset(fa, y);
	exp res;
	if (e == NULL) {
		e = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0,
			   ident_tag);
		son(e) = e; /* used to indicate that tag is not yet defined!?*/
		set_tag(t, e);
	}
	res = getexp(s, NULL, 0, e, NULL, 0, 0, env_offset_tag);
	setvis(e);
	setenvoff(e);
	return res;
}


exp
f_fail_installer(string message)
{
	char *m = (char *)xcalloc(message.number + 1, sizeof(char));
	int i;
	for (i=0; i<message.number; ++i) {
		m[i] = message.ints.chars[i];
	}
	m[message.number] = 0;
	error(ERROR_INTERNAL, m);
	exit(EXIT_FAILURE);
	return NULL;
}


exp
f_goto(label dest)
{
	exp lab = get_lab(dest);
	exp r = getexp(f_bottom, NULL, 0, NULL, lab, 0, 0, goto_tag);
	++no(son(lab));
	return r;
}


exp
f_goto_local_lv(exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (name(sh(arg1)) != ptrhd) {
			error(ERROR_INTERNAL, CHSH_GOLOCALLV);
		}
	}

	return me_u3(f_bottom, arg1, goto_lv_tag);
}


exp
f_identify(access_option acc, tag name_intro, exp definition, exp body)
{
	exp i = get_tag(name_intro);
	exp d = son(i);
	UNUSED(acc);
	if (name(sh(definition)) == bothd) {
		kill_exp(body, body);
		return definition;
	}
	setsh(i, sh(body));
	setbro(d, body);
	clearlast(d);
	setfather(i, body);
	return i;
}


void
start_identify(access_option acc, tag name_intro, exp definition)
{
	exp i = get_tag(name_intro);
	if (i == NULL || son(i) != i) {
		i = getexp(f_bottom, NULL, 0, definition, NULL, 0, 0,
			   ident_tag);
	} else {
		/* could have been already used in env_offset */
		son(i) = definition;
	}
	clearvar(i);
	if ((acc & (f_visible | f_long_jump_access)) != 0) {
		setvis(i);
	}
	set_tag(name_intro, i);

	return;
}


exp
f_ignorable(exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}
	return me_u2(arg1, ignorable_tag);
}


exp
f_integer_test(nat_option prob, ntest nt, label dest, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!is_integer(sh(arg1)) || !eq_shape(sh(arg1), sh(arg2))) {
			error(ERROR_INTERNAL, CHSH_INTTEST);
		}
	}

	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag))) {
		error_treatment ov_err;
		ov_err = f_wrap;
		arg1 = TDFcallop2(ov_err, arg1, arg2, test_tag);
		arg2 = getexp(slongsh, NULL, 0, NULL, NULL, 0, 0,
			      val_tag);
	}

	if (nt == f_comparable || nt == f_not_comparable) {
		return replace_ntest(nt, dest, arg1, arg2);
	} else {
		return me_q1(prob, convert_ntest[nt], dest, arg1, arg2,
			     test_tag);
	}
}


exp
f_labelled(label_list placelabs_intro, exp starter, exp_list places)
{
	exp f = places.start;
	exp b;
	int i;
	clear_exp_list(places);

	for (i = 0; i < places.number; ++i) {
		exp labst = get_lab(placelabs_intro.elems[i]);
		b = bro(f);

		setbro(son(labst), f);
		setbro(f, labst);
		setlast(f);
		setsh(labst, sh(f));
		if (name(starter) == case_tag ||
		    (name(starter) == seq_tag &&
		     name(son(son(starter))) == case_tag)) {
			fno(labst) = (float)(1.0 / places.number);
		} else {
			fno(labst) = (float)5.0;
		}
		f = b;
	}
	return clean_labelled(starter, placelabs_intro);
}


void
start_labelled(label_list placelabs_intro)
{
	UNUSED(placelabs_intro);
	if (crt_repeat != NULL) {
		++no(crt_repeat);
	}
	repeat_list = getexp(f_top, crt_repeat, 0, NULL, repeat_list, 0, 0,
			     0);
	crt_repeat = repeat_list;

	return;
}


exp
f_last_local(exp x)
{
	UNUSED(x);
	return getexp(f_pointer(f_alloca_alignment), NULL, 0, NULL, NULL,
		      0, 0, last_local_tag);
}


exp
f_local_alloc(exp arg1)
{
	alignment a;
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (name(sh(arg1)) != offsethd) {
			error(ERROR_INTERNAL, CHSH_LOCALLOC);
		}
	}

	if (al2(sh(arg1)) < 8) {
		arg1 = hold_refactor(f_offset_pad(f_alignment(ucharsh), arg1));
	}
	a = long_to_al(al1(sh(arg1)));
	has_alloca = 1;
	return me_u3(f_pointer(a), arg1, alloca_tag);
}


exp
f_local_alloc_check(exp arg1)
{
	exp res = f_local_alloc(arg1);
	if (name(res) ==alloca_tag) {
		set_checkalloc(res);
	}
	return res;
}


exp
f_local_free(exp a, exp p)
{
	if (name(sh(a)) == bothd) {
		kill_exp(p, p);
		return a;
	}
	if (name(sh(p)) == bothd) {
		kill_exp(a, a);
		return p;
	}

	if (check & CHECK_SHAPE) {
		if (name(sh(a)) != offsethd || name(sh(p)) != ptrhd) {
			error(ERROR_INTERNAL, CHSH_LOCFREE);
		}
	}

	if (al2(sh(a)) <8) {
		a = hold_refactor(f_offset_pad(f_alignment(ucharsh), a));
	}

	return me_b3(f_top, p, a, local_free_tag);
}


exp
f_local_free_all(void)
{
	has_setjmp = 1; /* this really means dont inline
			   and use a stack frame */
	return getexp(f_top, NULL, 0, NULL, NULL, 0, 0,
		      local_free_all_tag);
}


exp
f_long_jump(exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (name(sh(arg1)) != ptrhd || name(sh(arg2)) != ptrhd) {
			error(ERROR_INTERNAL, CHSH_LONGJUMP);
		}
	}

	has_setjmp = 1; /* this really means dont inline
			   and use a stack frame */
	return me_b3(f_bottom, arg1, arg2, long_jump_tag);
}


static int
comp_compare(const void *a, const void *b)
{
	return no(*((exp *)a)) - no(*((exp *)b));
}


exp
f_make_compound(exp arg1, exp_list arg2)
{
	exp first = arg2.start;
	exp r = getexp(f_compound(arg1), NULL, 0, first, NULL, 0, 0,
		       compound_tag);
	clear_exp_list(arg2);

	if (arg2.number == 0) {
		setname(r, clear_tag);
		return r;
	}

	if (check & CHECK_SHAPE) {
		exp t = first;
		while (1) {
			if (t != arg2.end && name(sh(bro(t))) == bothd) {
				return bro(t);
			}
			if (t == arg2.end || name(sh(t)) != offsethd ||
			    (!doing_aldefs &&
			     al2(sh(t)) < shape_align(sh(bro(t))))) {
				error(ERROR_INTERNAL, CHSH_MAKECPD);
			}
			if (bro(t) == arg2.end) {
				break;
			}
			t = bro(bro(t));
		}
	}

	setfather(r, arg2.end);

	if (!doing_aldefs && arg2.number > 2) {
		exp *arr = (exp *)xcalloc(arg2.number, sizeof(exp));
		int i;
		exp t = son(r);

		for (i = 0; i < arg2.number; ++i) {
			if (!(i & 1) && (no(t) + shape_size(sh(bro(t))) >
					 shape_size(sh(r)))) {
				error(ERROR_INTERNAL, "make_compound size exceeded");
			}
			arr[i] = t;
			t = bro(t);
		}

		if (promote_pars) {
			for (i = 0; i < arg2.number; i += 2) {
				alignment a = al2_of(sh(arr[i]));
				if (a->al.sh_hd != 0) {
					shape s = sh(arr[i + 1]);
					if (name(s) >= scharhd && name(s) <= uwordhd) {
						shape ns = (is_signed(s)) ? slongsh :
						    ulongsh;
						exp w = hold_refactor(f_change_variety(
						    f_wrap, ns, arr[i + 1]));
						arr[i+1] = w;
					}
				}
			}
		}

		qsort(arr, (size_t)(arg2.number / 2), (size_t)(2 * sizeof(exp)),
		      comp_compare);

		son(r) = arr[0];
		for (i = 1; i < arg2.number; ++i) {
			bro(arr[i - 1]) = arr[i];
			clearlast(arr[i - 1]);
		}
		bro(arr[arg2.number - 1]) = r;
		setlast(arr[arg2.number - 1]);

		xfree((void *)arr);
	}

	return r;
}


exp
f_make_int(variety v, signed_nat value)
{
	int n;

	if (!snat_issmall(value) ||
	    (n = snatint(value), shape_size(v) > 32 &&
	     (n & (int)0x80000000) != 0)) {
		flpt b;
		exp res;

		if (shape_size(v) <= 32) {
			flt64 temp;
			int ov;

			if (check & CHECK_EXTRA) {
				error(ERROR_INTERNAL, BIG_32);
				exit(EXIT_FAILURE);
			}

			temp = flt_to_f64(
			    value.signed_nat_val.big_s_nat, 0, &ov);
			n = temp.small;
			res = getexp(f_integer(v), NULL, 0, NULL,
				     NULL, 0, n, val_tag);
			return res;
		}
		if (snat_issmall(value)) {
			flt64 temp;
			temp.big = 0;
			temp.small = (unsigned int)n;
			b = f64_to_flt(temp, 0);
		} else {
			/* copy required since exp may be killed & value may be
			   token res */
			b = new_flpt();
			flt_copy(flptnos[value.signed_nat_val.big_s_nat],
				 &flptnos[b]);
		}
		if (snatneg(value)) {
			flptnos[b].sign = -1;
		}

		if (flptnos[b].exp > 3) {
			error(ERROR_INTERNAL, BIG_32);
			exit(EXIT_FAILURE);
		}
		res = getexp(f_integer(v), NULL, 0, NULL, NULL, 0, b,
			     val_tag);
		setbigval(res);
		return res;
	} else {
		if (snatneg(value)) {
			n = -n;
		}

		return getexp(f_integer(v), NULL, 0, NULL, NULL, 0, n,
			      val_tag);
	}
}


exp
f_make_local_lv(label lab)
{
	exp l = get_lab(lab);
	exp res = getexp(f_local_label_value, NULL, 0, NULL, l, 0, 0,
			 make_lv_tag);
	++no(son(l));
	set_loaded_lv(l);
	has_lv = 1;
	return res;
}


exp
f_make_nof(exp_list arg1)
{
	exp first = arg1.start;
	nat t;
	exp r;
	clear_exp_list(arg1);
	nat_issmall(t) = 1;
	natint(t) = arg1.number;
	if (arg1.number == 0) {
		return getexp(f_nof(t, f_top), NULL, 0, NULL, NULL, 0, 0,
			      nof_tag);
	}
	r = getexp(f_nof(t, sh(first)), NULL, 0, first, NULL, 0, 0,
		   nof_tag);

	if (check & CHECK_SHAPE) {
		exp temp = first;
		while (1) {
			if (!eq_shape(sh(temp), sh(first))) {
				error(ERROR_INTERNAL, CHSH_MAKENOF);
			}
			if (temp == arg1.end) {
				break;
			}
			temp = bro(temp);
		}
	}

	if (name(sh(first)) == bitfhd) {
		/* make make_nof bitbields into make-compound */
		int sf = shape_size(sh(first));
		int snof = shape_size(sh(r));
		exp *a = &arg1.start;
		int scs = (((sf - 1) &sf) == 0) ? sf : snof;
		shape cs = containedshape(scs, 1);
		int i;
		shape cpds = f_compound(hold_refactor(f_offset_pad(f_alignment(cs),
		    f_shape_offset(sh(r)))));
		exp soff = getexp(f_offset(f_alignment(cpds),
					   f_alignment(sh(first))),
				  NULL, 0, NULL, NULL, 0, 0, val_tag);
		for (i = 0; i < arg1.number; i++) {
			bro(soff) = *a;
			*a = copyexp(soff);
			a = &bro(bro(*a));
			no(soff) += sf;
		}
		arg1.number *= 2;
		return f_make_compound(hold_refactor(f_shape_offset(cpds)), arg1);
	}

	setfather(r, arg1.end);
	return r;
}


exp
f_make_nof_int(variety v, string s)
{
	shape sha;
	exp res;
	nat t;
	int i;
	shape elem_sh = f_integer(v);
	int elem_sz = shape_size(elem_sh);

	if (PIC_code) {
		proc_externs = 1;
	}

	nat_issmall(t) = 1;
	natint(t) = s.number;
	sha = f_nof(t, elem_sh);
	res = getexp(sha, NULL, 0, NULL, NULL, (prop)elem_sz, 0,
		     string_tag);


	if (elem_sz == 64) {
		int *ss;
		if (s.number == 0) {
			ss = NULL;
		} else {
			ss = (int *)xcalloc(s.number, sizeof(int));
		}
		for (i = 0; i < s.number; ++i) {
			flt64 x;
			flpt f;
			int ov;
			int sg = is_signed(elem_sh);
			x.big = 0;
			switch (s.size) {
			case  8: x.small = (unsigned int) s.ints.chars[i];  break;
			case 16: x.small = (unsigned int) s.ints.shorts[i]; break;
			case 32: x.small = (unsigned int) s.ints.longs[i];  break;

			default:
				f = (flpt)s.ints.longs[i];
				x = flt_to_f64(f, 0, &ov);
				flpt_ret(f);
				if (s.size < 64 && sg) {
					x.big = (x.big << (64 - s.size)) >>
					    (64 - s.size);
				}
			}
			ss[i] = f64_to_flt(x, sg);
		}
		nostr(res) = (char *)(void *)ss;
		return res;
	}

	switch (s.size) {
	case 8:
		switch (elem_sz) {
		case 8:
			nostr(res) = (char *)s.ints.chars;
			return res;
		case 16: {
			short *ss;
			if (s.number == 0) {
				ss = NULL;
			} else {
				ss = (short *)xcalloc(s.number, sizeof(short));
			}
			for (i = 0; i < s.number; ++i) {
				ss[i] = (short)(unsigned char)s.ints.chars[i];
			}
			nostr(res) = (char *)(void *)ss;
			return res;
		}
		case 32: {
			int *ss;
			if (s.number == 0) {
				ss = NULL;
			} else {
				ss = (int *)xcalloc(s.number, sizeof(int));
			}
			for (i = 0; i < s.number; ++i) {
				ss[i] = (int)(unsigned char)s.ints.chars[i];
			}
			nostr(res) = (char *)(void *)ss;
			return res;
		}
		}
	case 16:
		switch (elem_sz) {
		case 8: {
			char *ss;
			if (s.number == 0) {
				ss = NULL;
			} else {
				ss = (char *)xcalloc(s.number, sizeof(char));
			}
			for (i = 0; i < s.number; ++i) {
				ss[i] = (char)(unsigned short)s.ints.shorts[i];
			}
			nostr(res) = (char *)(void *)ss;
			return res;
		}
		case 16:
			nostr(res) = (char *)(void *)s.ints.shorts;
			return res;
		case 32: {
			int *ss;
			if (s.number == 0) {
				ss = NULL;
			} else {
				ss = (int *)xcalloc(s.number, sizeof(int));
			}
			for (i = 0; i < s.number; ++i) {
				ss[i] = (int)(unsigned short)s.ints.shorts[i];
			}
			nostr(res) = (char *)(void *)ss;
			return res;
		}
		}
	case 32:
		switch (elem_sz) {
		case 8: {
			char *ss;
			if (s.number == 0) {
				ss = NULL;
			} else {
				ss = (char *)xcalloc(s.number, sizeof(char));
			}
			for (i = 0; i < s.number; ++i) {
				ss[i] = (char)(unsigned long)s.ints.longs[i];
			}
			nostr(res) = (char *)(void *)ss;
			return res;
		}
		case 16: {
			short *ss;
			if (s.number == 0) {
				ss = NULL;
			} else {
				ss = (short *)xcalloc(s.number, sizeof(short));
			}
			for (i = 0; i < s.number; ++i) {
				ss[i] = (short)(unsigned long)s.ints.longs[i];
			}
			nostr(res) = (char *)(void *)ss;
			return res;
		}
		case 32:
			nostr(res) = (char *)(void *)s.ints.longs;
			return res;
		}
	}
	return res;
}


exp
f_make_null_local_lv(void)
{
	return me_null(f_local_label_value, lv_null, null_tag);
}


exp
f_make_null_proc(void)
{
	return me_null(f_proc, proc_null, null_tag);
}


exp
f_make_null_ptr(alignment a)
{
	return me_null(f_pointer(a), ptr_null, null_tag);
}

exp
f_maximum(exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!eq_shape(sh(arg1), sh(arg2)) || !is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_MAX);
		}
	}

	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag))) {
		return TDFcallop3(arg1, arg2, max_tag);
	}

	return me_b2(arg1, arg2, max_tag);
}

exp
f_minimum(exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!eq_shape(sh(arg1), sh(arg2)) || !is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_MIN);
		}
	}

	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag))) {
		error_treatment ov_err;
		ov_err = f_wrap;
		return TDFcallop2(ov_err, arg1, arg2, min_tag);
	}

	return me_b2(arg1, arg2, min_tag);
}


static int in_initial_value;

static void
push_proc_props(void)
{
	proc_props *temp = (proc_props *)xcalloc(1, sizeof(proc_props));
	temp->proc_struct_result = proc_struct_result;
	temp->has_alloca = has_alloca;
	temp->proc_is_recursive = proc_is_recursive;
	temp->uses_crt_env = uses_crt_env;
	temp->has_setjmp = has_setjmp;
	temp->uses_loc_address = uses_loc_address;
	temp->proc_label_count = proc_label_count;
	temp->proc_struct_res = proc_struct_res;
	temp->default_freq = default_freq;
	temp->proc_externs = proc_externs;
	temp->in_proc_def = in_proc_def;
	temp->pushed = old_proc_props;
	temp->rep_make_proc = rep_make_proc;
	temp->frame_alignment = frame_alignment;
	temp->in_initial_value = in_initial_value;
	old_proc_props = temp;
	return;
}


static void
pop_proc_props(void)
{
	proc_props *temp = old_proc_props;
	proc_struct_result = temp->proc_struct_result;
	has_alloca = temp->has_alloca;
	proc_is_recursive =temp->proc_is_recursive;
	uses_crt_env = temp->uses_crt_env;
	has_setjmp = temp->has_setjmp;
	uses_loc_address = temp->uses_loc_address;
	proc_label_count = temp->proc_label_count;
	proc_struct_res = temp->proc_struct_res;
	default_freq = temp->default_freq;
	proc_externs = temp->proc_externs;
	in_proc_def = temp->in_proc_def;
	old_proc_props = temp->pushed;
	rep_make_proc = temp->rep_make_proc;
	frame_alignment = temp->frame_alignment;
	in_initial_value = temp->in_initial_value;
	if (temp != &initial_value_pp) {
		xfree((void *)temp);
	}
	return;
}


void
start_make_proc(shape result_shape, tagshacc_list params_intro,
		tagacc_option vartag)
{
	/* initialise global flags which are used at the end of the
	   reading process in f_make_proc */
	UNUSED(result_shape); UNUSED(params_intro);
	push_proc_props();

	proc_struct_result = NULL;
	has_alloca = 0;
	proc_is_recursive = 0;
	uses_crt_env = 0;
	has_setjmp = 0;
	uses_loc_address = 0;
	proc_label_count = 0;
	proc_struct_res = 0;
	default_freq = 1.0;
	proc_externs = 0;
	in_initial_value = 0;
	frame_alignment = f_unite_alignments(f_locals_alignment,
					     var_callers_alignment);

	if (vartag.present) {
		shape sha = getshape(0, const_al1, const_al1, VAR_PARAM_ALIGN,
				     0, cpdhd);
		exp d = getexp(sha, NULL, 0, NULL, NULL, 0, 0, clear_tag);
		exp i = getexp(f_bottom, NULL, 1, d, NULL, 0, 0, ident_tag);
		setvis(i);
		setvar(i);
		setparam(i);
		set_tag(vartag.val.tg, i);
	}

	/* set this flag to distinguish values created during procedure
	   reading. */
	in_proc_def = 1;

	return;
}


exp
f_make_proc(shape result_shape, tagshacc_list params_intro,
	    tagacc_option vartag, exp body)
{
	exp res;
	int varhack = 0;
#if TRANS_HPPA
	exp t, id, ptr;
#endif

	if (check & CHECK_SHAPE) {
		if (name(sh(body)) != bothd) {
			error(ERROR_INTERNAL, CHSH_MAKE_PROC);
		}
	}

	if (vartag.present) {
		exp i = get_tag(vartag.val.tg);
		if (params_intro.id == NULL) {
			params_intro.id = i;
		} else {
			bro(params_intro.last_def) = i;
		}
		bro(i) = params_intro.last_id;
		params_intro.last_def = son(i);
		params_intro.last_id = i;
		setvis(i);
		++params_intro.number;
		varhack = 1;
	}

	res = getexp(f_proc, NULL, 0, params_intro.id, result_shape, 0, 0,
		     proc_tag);

	if (params_intro.number == 0) {
		son(res) = body;
		setlast(body);
		bro(body) = res;
	} else {
		bro(son(res)) = res;
		bro(params_intro.last_def) = body;
		setlast(body);
		bro(body) = params_intro.last_id;
		if (promote_pars) {
			promote_formals(son(res));
		}
	}

	/* set the properties of the procedure construction from the
	   global values accumulated during reading.
	   WE OUGHT TO POP THE OLD VALUES.
	 */
	if (has_alloca) {
		set_proc_has_alloca(res);
	}
	if (proc_is_recursive) {
		setrecursive(res);
	}
	if (has_lv) {
		set_proc_has_lv(res);
	}
	if (uses_crt_env) {
		set_proc_uses_crt_env(res);
	}
	if (has_setjmp) {
		set_proc_has_setjmp(res);
	}
	if (uses_loc_address) {
		set_loc_address(res);
	}
	if (proc_struct_res) {
		set_struct_res(res);
	}
	if (proc_externs) {
		set_proc_uses_external(res);
	}

	/* apply refactor_id to the parameters */

	if (params_intro.number != 0) {
		exp param;
		for (param = params_intro.last_id; param != res;
		     param = bro(param)) {
			if (redo_structparams &&
#if TRANS_HPPA
			    (varhack || ((shape_size(sh(son(param))) >64) &&
					 (name(sh(son(param))) == cpdhd ||
					  name(sh(son(param))) == nofhd ||
					  name(sh(son(param))) == doublehd))))
#else
#if TRANS_SPARC
			    (varhack || sparccpd(sh(son(param)))))

#else
			    (varhack || name(sh(son(param))) == cpdhd ||
			     name(sh(son(param))) == nofhd ||
			     name(sh(son(param))) == doublehd))
#endif
#endif
			{
				/*
				 * Param IS struct/union-by-value.  Incoming
				 * acutal parameter will have been changed to
				 * be ptr-to expected value (see
				 * f_apply_proc()), so adjust usage in body.
				 */
				exp use;	/* use of ident in pt() chain */
				exp prev;	/* previous use in pt() chain */
				exp eo = NULL;
				shape ptr_s =
				    f_pointer(f_alignment(sh(son(param))));

#if TRANS_HPPA
				/* modify parameter itself */
				if (!varhack) {
					exp obtain_param;
					exp assign;
					shape sha=sh(son(param));
					t=me_obtain(param);
					if (uses_crt_env) {
						eo = f_env_offset(
						     frame_alignment,
						     f_parameter_alignment(
						     ptr_s), brog(param));
						obtain_param =
						    f_add_to_ptr(
						    f_current_env(), eo);
					}
					id = me_startid(f_top,
							me_u3(sha, t, cont_tag),
							1);
					ptr = me_startid(f_top, me_obtain(id),
							 0);
					if (uses_crt_env) {
						assign =
						    f_assign(obtain_param,
							     me_obtain(id));
						body = f_sequence(add_exp_list(
						       new_exp_list(1), assign,
						       0), body);
					}
					clearlast(son(ptr));
					bro(son(ptr)) = body;
					setlast(body);
					bro(body) = ptr;
					sh(ptr) = sh(body);
					body = id;
					clearlast(son(id));
					bro(son(id)) = ptr;
					setlast(ptr);
					bro(ptr) = id;
					sh(id) = sh(ptr);
					bro(params_intro.last_def) = body;
					setlast(body);
					bro(body) = param;
				}
#endif

				/* visit each use of the parameter modifying
				   appropriately*/
				for (prev = param, use = pt(prev);
				     use != NULL;
				     prev = use, use = pt(prev)) {
					if (!uses_crt_env ||
					    (uses_crt_env && use != eo)) {
						if (!isvar(param)) {
							/* add cont */
							exp new_use =
							    getexp(ptr_s, use,
								   (bool)1,
								   son(use),
								   pt(use),
								   props(use),
								   0, name_tag);
							son(use) = new_use;
							pt(prev) = new_use;
							pt(use) = NULL;
							props(use) = (prop)0;
							setname(use, cont_tag);
							/* retain same no and
							   sh */

							use = new_use;
						}

						if (no(use) > 0) {
							/* add reff */
							exp new_use =
							    getexp(ptr_s, use,
								   (bool)1,
								   son(use),
								   pt(use),
								   props(use),
								   0, name_tag);
							son(use) = new_use;
							pt(prev) = new_use;
							pt(use) = NULL;
							props(use) = (prop)0;
							setname(use, reff_tag);
							/* retain same no and
							   sh */

							use = new_use;
						}
					}
				} /* for */

#if TRANS_HPPA
				if (!varhack) {
					/* Change all but ptr's references to
					   param to references to ptr */
					for (use = pt(param); use != NULL;
					     use = pt(use)) {
						if ((son(use) ==param) &&
						    (use != son(son(id))) &&
						    (!uses_crt_env ||
						     (uses_crt_env &&
						      use != eo))) {
							son(use) =ptr;
						}
					}
					pt(ptr) =pt(param);
				}
#endif

				/* modify parameter itself */
				if (isenvoff(param)) {
					props(param) = (prop)0;
					setvis(param);
				} else {
					props(param) = (prop)0;
				}
				setparam(param);
				setcaonly(param);
				if (varhack) {
					setvis(param);
				}
				setsh(son(param), ptr_s);
			} /* if redo... */
			varhack = 0;
			/* apply refactor_id to the parameters */
			IGNORE refactor_id(param, param);
		} /* for */
	}

	if (proc_struct_result != NULL) {
		bro(son(proc_struct_result)) = son(res);
		setfather(proc_struct_result, son(res));
		son(res) = proc_struct_result;
		setfather(res, proc_struct_result);
	}

	/* clear this flag to distinguish values created during procedure
	   reading. */
	in_proc_def = 0;

	pop_proc_props();

	if (old_proc_props != NULL || rep_make_proc) {
		dec *extra_dec = make_extra_dec(make_local_name(), 0, 0, res,
						f_proc);
		exp e = extra_dec->dec_u.dec_val.dec_exp;
		res = getexp(f_proc, NULL, 0, e, NULL, 0, 0, name_tag);
		pt(e) = res;
		no(e) = 1;
	}

	return res;
}


procprops crt_procprops;

void
start_make_general_proc(shape result_shape, procprops prcprops,
			tagshacc_list caller_intro, tagshacc_list callee_intro)
{
	/* initialise global flags which are used at the end of the
	   reading process in f_make_proc */

	push_proc_props();

	proc_struct_result = NULL;
	has_alloca = 0;
	proc_is_recursive = 0;
	uses_crt_env = 0;
	has_setjmp = 0;
	uses_loc_address = 0;
	proc_label_count = 0;
	proc_struct_res = 0;
	default_freq = 1.0;
	frame_alignment = f_unite_alignments(f_locals_alignment,
					     f_callers_alignment((prcprops &
					     f_var_callers) != 0));
	frame_alignment =  f_unite_alignments(frame_alignment,
					      f_callees_alignment((prcprops &
					      f_var_callees) != 0));

	proc_externs = 0;
	/* set this flag to distinguish values created during procedure
	   reading. */
	in_proc_def = 1;
	crt_procprops = prcprops;
	return;
}


exp
f_make_general_proc(shape result_shape, procprops prcprops,
		    tagshacc_list caller_intro, tagshacc_list callee_intro,
		    exp body)
{
	exp res;

	if (check & CHECK_SHAPE) {
		if (name(sh(body)) != bothd) {
			error(ERROR_INTERNAL, CHSH_MAKE_PROC);
		}
	}

	res = getexp(f_proc, NULL, 0, caller_intro.id, result_shape, 0, 0,
		     general_proc_tag);

	if (caller_intro.number == 0 && callee_intro.number == 0) {
		son(res) = body;
		setlast(body);
		bro(body) = res;
	} else if (callee_intro.number == 0) {
		bro(son(res)) = res;
		bro(caller_intro.last_def) = body;
		setlast(body);
		bro(body) = caller_intro.last_id;
	} else {
		int i;
		exp z = callee_intro.id;
		for (i = 0; i < callee_intro.number; i++) {
			set_callee(z);
			z = bro(son(z));
		}
		if (caller_intro.number != 0) {
			bro(caller_intro.last_def) = callee_intro.id;
			bro(callee_intro.id) = caller_intro.last_id;	/*???*/
		} else {
			son(res) = callee_intro.id;
		}
		bro(son(res)) = res;
		bro(callee_intro.last_def) = body;
		setlast(body);
		bro(body) = callee_intro.last_id;
	}

	if (promote_pars) {
		promote_formals(son(res));
	}

	/* set the properties of the procedure construction from the
	   global values accumulated during reading.
	   WE OUGHT TO POP THE OLD VALUES.
	 */
	if (has_alloca) {
		set_proc_has_alloca(res);
	}
	if (proc_is_recursive) {
		setrecursive(res);
	}
	if (has_lv) {
		set_proc_has_lv(res);
	}
	if (uses_crt_env) {
		set_proc_uses_crt_env(res);
	}
	if (has_setjmp) {
		set_proc_has_setjmp(res);
	}
	if (uses_loc_address) {
		set_loc_address(res);
	}
	if (proc_struct_res) {
		set_struct_res(res);
	}
	if (proc_externs) {
		set_proc_uses_external(res);
	}

	if (caller_intro.number != 0) {
		bool varhack = 0;
		exp param;
		for (param = caller_intro.last_id; param != res;
		     param = bro(param)) {
			if (redo_structparams && !varhack &&
#if TRANS_HPPA
			    shape_size(sh(son(param))) > 64)
#else
				(name(sh(son(param))) == cpdhd ||
				 name(sh(son(param))) == nofhd ||
#if TRANS_SPARC
				 sparccpd(sh(son(param))) ||
#endif
				 name(sh(son(param))) == doublehd))
#endif
			{
				/*
				 * Param IS struct/union-by-value.  Incoming
				 * acutal parameter will have been changed to
				 * be ptr-to expected value (see
				 * f_apply_proc()), so adjust usage in body.
				 */
				exp use;  /* use of ident in pt() chain */
				exp prev; /* previous use in pt() chain */

				shape ptr_s =
				    f_pointer(f_alignment(sh(son(param))));
				int mustbevis;

				/* visit each use of the parameter modifying
				   appropriately*/
				for (prev = param, use = pt(prev);
				     use != NULL;
				     prev = use, use = pt(prev)) {
					if (!isvar(param)) {
						/* add cont */
						exp new_use =
						    getexp(ptr_s, use, (bool)1,
							   son(use), pt(use),
							   props(use), 0,
							   name_tag);
						son(use) = new_use;
						pt(prev) = new_use;
						pt(use) = NULL;
						props(use) = (prop)0;
						/* retain same no and sh */
						setname(use, cont_tag);

						use = new_use;
					}

					if (no(use) > 0) {	/* add reff */
						exp new_use =
						    getexp(ptr_s, use, (bool)1,
							   son(use), pt(use),
							   props(use), 0,
							   name_tag);
						son(use) = new_use;
						pt(prev) = new_use;
						pt(use) = NULL;
						props(use) = (prop)0;
						/* retain same no and sh */
						setname(use, reff_tag);

						use = new_use;
					}
				} /* for */

				/* modify parameter itself */
				mustbevis = isenvoff(param);
				if (isoutpar(param)) {
					props(param) = (prop)0;
					setoutpar(param);
				} else {
					props(param) = (prop)0;
				}
				if (mustbevis) {
					setvis(param);
				}
				setparam(param);
				setcaonly(param);
				setsh(son(param), ptr_s);
			} /* if redo... */
			varhack = 0;
			/* apply refactor_id to the caller parameters */
			IGNORE refactor_id(param, param);
		} /* for */
	}

	if (callee_intro.number != 0) {
		exp param= callee_intro.last_id;
		int i;

		for (i=callee_intro.number; i != 0;
		     param = father(param), i--) {

			/* apply refactor_id to the callee parameters */
			IGNORE refactor_id(param, param);
		} /* for */
	}

	if (redo_structfns && !reg_result(result_shape)) {
		if (proc_struct_result==NULL) {
			exp init = getexp(f_pointer(f_alignment(result_shape)),
					  NULL, 0, NULL, NULL, 0, 0,
					  clear_tag);
			exp iddec = getexp(sh(son(res)), NULL, 0, init,
					   NULL, 0, 0, ident_tag);
			setparam(iddec);
			proc_struct_result = iddec;
		}

		bro(son(proc_struct_result)) = son(res);
		setfather(proc_struct_result, son(res));
		son(res) = proc_struct_result;
		setfather(res, proc_struct_result);
	}

	/* clear this flag to distinguish values created during procedure
	   reading. */
	in_proc_def = 0;

	set_make_procprops(res, prcprops);

	pop_proc_props();
	if (old_proc_props != NULL || rep_make_proc) {
		dec *extra_dec = make_extra_dec(make_local_name(), 0, 0, res,
						f_proc);
		exp e = extra_dec->dec_u.dec_val.dec_exp;
		res = getexp(f_proc, NULL, 0, e, NULL, 0, 0, name_tag);
		pt(e) = res;
		no(e) = 1;
	}

	return res;
}


exp
find_caller_id(int n, exp p)
{
	while (name(p) == ident_tag) {
		if (name(son(p)) == caller_name_tag && no(son(p)) ==n) {
			return p;
		}
		p = bro(son(p));
	}
	return NULL;
}


void
start_apply_general_proc(shape result_shape, procprops_option prcprops, exp p,
			 otagexp_list caller_params_intro,
			 callees callee_params)
{
	return;
}


exp
f_apply_general_proc(shape result_shape, procprops prcprops, exp p,
		     otagexp_list caller_pars, callees callee_pars,
		     exp postlude)
{
	exp res = getexp(result_shape, NULL, 0, p, NULL, 0, 0,
			 apply_general_tag);
	exp r_p;
	exp redos = NULL;
	exp last_redo;
	has_alloca = 1;

	if (name(callee_pars) == same_callees_tag) {
		/* it's a constant */
		callee_pars = copy(callee_pars);
	}


	if (redo_structparams) {
		int i;
		exp *plce = &caller_pars.start;
		for (i = 0; i < caller_pars.number; i++) {
			exp ote = *plce;
			exp param = (name(ote) == caller_tag) ? son(ote) : ote;
			if ((name(sh(param)) == cpdhd ||
			     name(sh(param)) == nofhd ||
			     name(sh(param)) == doublehd)
#if TRANS_SPARC
			    || sparccpd(sh(param))
#endif
#if TRANS_HPPA
			    && shape_size(sh(param)) >64
#endif
			    ) {
				/* make copy of par and use ptr as par */
				shape nshape =
				    f_pointer(f_alignment(sh(param)));
				exp rd = me_startid(nshape, param, 1);
				exp npar = me_obtain(rd);
				exp id;
				if (name(ote) ==caller_tag &&
				    (id = find_caller_id(i, caller_pars.id)) !=
				    NULL) {
					exp p = pt(id);
					son(ote) = npar;
					bro(npar) = ote;
					setlast(npar);
					sh(son(id)) = sh(npar);
					while(p != NULL) {
						/* replaces uses in postlude */
						exp bp = bro(p);
						int l = last(p);
						exp np = pt(p);
						exp *pos = refto(father(p), p);
						exp c;
						sh(p) = nshape;
						c = f_contents(sh(ote), p);
						if (l) {
							setlast(c);
						} else {
							clearlast(c);
						}
						bro(c) = bp;
						*pos = c;
						p = np;
					}
					sh(ote) = nshape;
					plce = &bro(ote);
				} else {
					if (last(ote)) {
						setlast(npar);
					}
					bro(npar) = bro(ote);
					if (ote == caller_pars.end) {
						caller_pars.end = npar;
					}
					*plce = npar;
					plce = &bro(npar);
				}
				bro(son(rd)) = redos;
				clearlast(son(rd));
				if (redos != NULL) {
					bro(redos) = rd;
					setlast(redos);
				} else {
					last_redo = rd;
				}
				redos = rd;
			} else {
				plce = &bro(ote);}
		}
	}

	if (caller_pars.id != NULL) {
		exp a = caller_pars.id;
		while (bro(son(a)) != NULL) {
			a = bro(son(a));
		}
		bro(son(a)) = postlude;
		setfather(a, postlude);
		postlude = caller_pars.id;
	}

	setfather(res, postlude);

	bro(callee_pars) = postlude;
	clearlast(callee_pars);
	props(callee_pars) = prcprops;

	r_p = getexp(f_top, callee_pars, 0, caller_pars.start, NULL, prcprops,
		     caller_pars.number, 0);
	if (caller_pars.number != 0) {
		setfather(r_p, caller_pars.end);
	}

	bro(p) = r_p; clearlast(p);

	if (promote_pars) {
		int i;
		exp ote = caller_pars.start;
		for (i = 0; i < caller_pars.number; i++) {
			shape s = sh(ote);
			if (name(s) >= scharhd && name(s) <= uwordhd) {
				shape ns = (is_signed(s)) ? slongsh : ulongsh;
				exp par = (name(ote) == caller_tag) ?
				    son(ote) : ote;
				exp next = bro(ote);
				exp id;
				int l = last(ote);
				exp w = hold_refactor(f_change_variety(f_wrap, ns,
								    copy(par)));
				if (name(ote) == caller_tag) {
					sh(ote) = ns;
				}
				replace(par, w, NULL);
				kill_exp(par, NULL);
				if (name(ote) == caller_tag &&
				    (id = find_caller_id(i, postlude)) !=
				    NULL) {
					exp p = pt(id);
					sh(son(id)) = ns;
					while(p != NULL) {
						/* replaces uses in postlude */
						exp nextp = pt(p);
						sh(p) = ns;
						w = f_change_variety(f_wrap, s,
								     copy(p));
						replace(p, w, NULL);
						kill_exp(p, NULL);
						p = nextp;
					}
				}
				if (l) {
					break;
				}
				ote = next;
			} else ote = bro(ote);
		}
	}

	if (redo_structfns && !reg_result(result_shape))
	{
		/* replace f(x) by {var r; f(r, x); cont(r)} */
		exp init, vardec, cont, contname, seq, app, appname, tmp;
		exp_list list;
		shape ptr_res_shape = f_pointer(f_alignment(result_shape));

		init = getexp(result_shape, NULL, 0, NULL, NULL, 0, 0,
			      clear_tag);
		vardec = getexp(result_shape, NULL, 0, init, NULL, 0, 1,
				ident_tag);
		setvar(vardec);
		contname = getexp(ptr_res_shape, NULL, 0, vardec, NULL, 0,
				  0, name_tag);
		pt(vardec) = contname;
		cont = f_contents(result_shape, contname);

		appname = getexp(ptr_res_shape, son(r_p), 0, vardec, contname,
				 0, 0, name_tag);
		if (no(r_p)++ == 0) {
			setfather(r_p, appname);
		}
		++no(vardec);
		pt(vardec) = appname;
		app = getexp(f_top, NULL, 0, son(res), NULL, 0, 32,
			     apply_general_tag);
		son(r_p) = appname;

		tmp = postlude;
		while (name(tmp) ==ident_tag &&
		       name(son(tmp)) == caller_name_tag) {
			no(son(tmp))++;
			tmp = bro(son(tmp));
		}

		bro(postlude) = app;
		list.number = 1;
		list.start = app;
		list.end = app;
		seq = f_sequence(list, cont);
		bro(init) = seq;
		setfather(vardec, seq);
		retcell(res);
		res = vardec;
	}

	if (redos != NULL) {
		/* put in decs given by redo_structparams */
		bro(son(last_redo)) = res;
		clearlast(son(last_redo));
		bro(res) = last_redo;
		setlast(res);
		res = redos;
	}

	return res;
}


exp
f_tail_call(procprops prcprops, exp p, callees callee_params)
{
	exp res = getexp(f_bottom, NULL, 0, p, NULL, 0, 0, tail_call_tag);
	exp e_p;
	if (name(callee_params) == same_callees_tag) {
		/* it's a constant */
		callee_params = copy(callee_params);
	}
	e_p = getexp(f_top, res, 1, callee_params, NULL, prcprops, 0, 0);
	has_setjmp = 1; /* stop inlining! */
	has_alloca = 1; /* make sure has fp */
	props(callee_params) = prcprops;
	bro(p) = callee_params;
	clearlast(p);
	setfather(res, callee_params);
	return res;
}


exp
f_untidy_return(exp arg)
{
	exp res = getexp(f_bottom, NULL, 0, arg, NULL, 0, 0,
			 untidy_return_tag);
	setfather(res, arg);
	has_setjmp = 1;
	return res;
}


alignment
f_parameter_align(alignment a)
{
	return f_var_param_alignment;

}

exp
f_set_stack_limit(exp flim)
{
   	return me_u3(f_top, flim, set_stack_limit_tag);
}

exp
f_give_stack_limit(alignment frame_al)
{
   	exp res = getexp(f_pointer(frame_al), NULL, 0, NULL, NULL, 0, 0,
			 give_stack_limit_tag);
   	return res;
}

exp
f_make_stack_limit(exp stack_base, exp frame_size, exp alloca_size)
{

	exp sz;
	frame_size = hold_refactor(f_offset_pad(al1_of(sh(alloca_size)),
					     frame_size));
	alloca_size = hold_refactor(f_offset_pad(f_alignment(ucharsh),
					      alloca_size));
	sz = hold_refactor(f_offset_add(frame_size, alloca_size));
	return me_b2(stack_base, sz, make_stack_limit_tag);
}


exp
f_env_size(tag proctag)
{
  	exp res = getexp(f_offset(f_locals_alignment, f_locals_alignment),
			 NULL, 0, f_obtain_tag(proctag), NULL, 0, 0,
			 env_size_tag);
  	bro(son(res)) = res;
	setlast(son(res));
  	return res;
}



nat
f_error_val(error_code ec)
{
	nat res;
	nat_issmall(res) =1;
	natint(res) = ec;
	return res;
}

exp
f_make_top(void)
{
	return getexp(f_top, NULL, 0, NULL, NULL, 0, 0, top_tag);
}

exp
f_make_value(shape s)
{
	return me_l1(s, clear_tag);
}

exp
f_minus(error_treatment ov_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!eq_shape(sh(arg1), sh(arg2)) || !is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_MINUS);
		}
	}

	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag ||
	     ov_err.err_code > 2))) {
		return TDFcallop2(ov_err, arg1, arg2, minus_tag);
	}

	return me_b1(ov_err, arg1, arg2, minus_tag);
}

exp
f_move_some(transfer_mode md, exp arg1, exp arg2, exp arg3)
{
	exp r = getexp(f_top, NULL, 0, arg1, NULL, 0, 0, movecont_tag);
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		kill_exp(arg3, arg3);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		kill_exp(arg3, arg3);
		return arg2;
	}
	if (name(sh(arg3)) == bothd) {
		kill_exp(arg1, arg1);
		kill_exp(arg2, arg2);
		return arg3;
	}

	if (check & CHECK_SHAPE) {
		if (name(sh(arg1)) != ptrhd || name(sh(arg2)) != ptrhd ||
		    name(sh(arg3)) != offsethd || al1(sh(arg1)) < al1(sh(arg3)) ||
		    al1(sh(arg2)) < al1(sh(arg3))) {
			error(ERROR_INTERNAL, CHSH_MOVESOME);
		}
	}

	if (trap_on_nil_contents && (md & f_trap_on_nil) != 0) {
		exp d2 = me_startid(f_top, arg2, 0);
		exp d1 = me_startid(f_top, arg1, 0);
		exp hldr = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, 0);
		exp lb = getexp(f_top, NULL, 0, hldr, NULL, 0, 0,
				labst_tag);
		exp_list el;
		exp test2 = me_q1(no_nat_option, f_not_equal, &lb,
				  me_obtain(d2),
				  f_make_null_ptr(al1_of(sh(arg2))), test_tag);
		exp test1 = me_q1(no_nat_option, f_not_equal, &lb,
				  me_obtain(d1), f_make_null_ptr(al1_of(
				  sh(arg1))), test_tag);
		exp trp = getexp(f_bottom, NULL, 0, NULL, NULL, 0,
				 f_nil_access, trap_tag);
		md &= ~f_trap_on_nil;
		el = new_exp_list(2);
		el = add_exp_list(el, test1, 1);
		el = add_exp_list(el, test2, 2);

		return me_complete_id(d2, me_complete_id(d1, f_conditional(&lb,
		    f_sequence(el, f_move_some(md, me_obtain(d1), me_obtain(d2),
					       arg3)), trp)));
	}

	if (!(md & f_overlap) && name(arg3) == val_tag && al2(sh(arg3)) > 1) {
		exp c = f_contents(f_compound(arg3), arg1);
		return f_assign(arg2, c);
	}

	if (al2(sh(arg3)) < 8) {
		arg3 = hold_refactor(f_offset_pad(f_alignment(ucharsh), arg3));
	}

	if (!(md & f_overlap)) {
		setnooverlap(r);
	}
	clearlast(arg1);
	setbro(arg1, arg2);
	clearlast(arg2);
	setbro(arg2, arg3);
	setfather(r, arg3);
	return r;
}


exp
f_mult(error_treatment ov_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!eq_shape(sh(arg1), sh(arg2)) || !is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_MULT);
		}
	}

	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag ||
	     ov_err.err_code > 2))) {
		return TDFcallop2(ov_err, arg1, arg2, mult_tag);
	}

	return me_b1(ov_err, arg1, arg2, mult_tag);
}


exp
f_n_copies(nat n, exp arg1)
{
	exp r;
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (~has & HAS_64_BIT && !nat_issmall(n)) {
		error(ERROR_INTERNAL, TOO_BIG_A_VECTOR);
	}

	r = getexp(f_nof(n, sh(arg1)), NULL, 0, arg1, NULL, 0, natint(n),
		   ncopies_tag);
	if (name(sh(arg1)) == bitfhd) {
		/* make ncopies bitfields into (ncopies) make-compound */
		int sf = shape_size(sh(arg1));
		int snof = shape_size(sh(r));
		int scs = (((sf - 1) &sf) ==0) ? sf : snof;
		shape cs = containedshape(scs, 1);
		exp_list a;
		shape cpds = f_compound(hold_refactor(f_offset_pad(f_alignment(cs),
		    f_shape_offset(sh(r)))));
		exp soff = getexp(f_offset(f_alignment(cpds),
					   f_alignment(sh(arg1))), NULL, 0,
				  NULL, NULL, 0, 0, val_tag);
		exp cexp;
		a.start = copyexp(soff);
		a.end = a.start;
		a.number = 2;
		bro(a.end) = copyexp(arg1);
		a.end = bro(a.end);
		for (no(soff) = sf; no(soff) <= shape_size(cs) -sf;
		     no(soff) +=sf) {
			bro(a.end) = copyexp(soff);
			clearlast(a.end);
			a.end = bro(a.end);
			bro(a.end) = copyexp(arg1);
			a.end = bro(a.end);
			a.number += 2;
		}

		setlast(a.end);
		bro(a.end) = NULL;
		cexp = f_make_compound(hold_refactor(f_shape_offset(cs)), a);
		if (shape_size(cs) >= shape_size(cpds)) {
			return cexp;
		} else {
			natint(n) = shape_size(cpds) / shape_size(cs);
			return f_n_copies(n, cexp);
		}
	}

	setfather(r, arg1);
	return r;
}


exp
f_negate(error_treatment ov_err, exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (!is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_NEGATE);
		}
	}

	if (!is_signed(sh(arg1)) && ov_err.err_code > 2) {
		return f_minus(ov_err, me_shint(sh(arg1), 0), arg1);
	}

	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag|| ov_err.err_code > 2))) {
		return TDFcallop1(ov_err, arg1, neg_tag);
	}

	return me_u1(ov_err, arg1, neg_tag);
}


exp
f_not(exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (!is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_NOT);
		}
	}

	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    name(arg1) != val_tag)) {
		return TDFcallop4(arg1, not_tag);
	}

	return me_u2(arg1, not_tag);
}


exp
f_obtain_tag(tag t)
{
	shape s;
	exp r;
	exp tg = get_tag(t);

	if (tg == NULL) {
		error(ERROR_INTERNAL, UNDEF_TAG);
	}

	if (isglob(tg)) {
		s = sh(t->dec_u.dec_val.dec_exp);
#ifdef NEWDIAGS
		if (!within_diags) {
			proc_externs = 1;
		}
#else
		proc_externs = 1;
#endif
	} else {
		s = sh(son(tg));
	}

	if (isvar(tg)) {
		if (isparam(tg)) {
			s = f_pointer(f_parameter_alignment(s));
		} else {
			s = f_pointer(f_alignment(s));
		}
	}

	r = getexp(s, NULL, 0, tg, pt(tg), 0, 0, name_tag);
	pt(tg) = r;
	no(tg) = no(tg) +1;
	return r;
}


exp
f_offset_add(exp arg1, exp arg2)
{
	shape sres;
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!doing_aldefs &&
		    ((name(sh(arg1)) != offsethd || name(sh(arg2)) != offsethd ||
		      (al1(sh(arg2)) > al2(sh(arg1))
#if TRANS_SPARC
		       && al1_of(sh(arg2)) != REAL_ALIGN
#endif
		       )))) {
			error(ERROR_INTERNAL, CHSH_OFFSETADD);
		}
	}

	sres = f_offset(al1_of(sh(arg1)), al2_of(sh(arg2)));
#if 0
	if ((al1_of(sh(arg1))->al.al_val.al_frame & 4) != 0 &&
	    al2_of(sh(arg2))->al.sh_hd != 0) {
		exp ne;
		if (al2_of(sh(arg2))->al.sh_hd > nofhd) {
			shape ps = f_pointer(f_alignment(sh(arg1)));
			ne = hold_refactor(f_offset_pad(f_alignment(ps),
						     f_shape_offset(ps)));
		} else {
			ne = arg2;
		}
		arg2 = hold_refactor(me_u2(ne, offset_negate_tag));
	}
#endif
	return me_b3(sres, arg1, arg2, offset_add_tag);
}


exp
f_offset_div(variety v, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (name(sh(arg1)) != offsethd || name(sh(arg2)) != offsethd) {
			error(ERROR_INTERNAL, CHSH_OFFSETDIV);
		}
	}

	return me_b3(f_integer(v), arg1, arg2, offset_div_tag);
}


exp
f_offset_div_by_int(exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!doing_aldefs &&
		    (name(sh(arg1)) != offsethd || !is_integer(sh(arg2)) ||
		     (al1(sh(arg1)) != al2(sh(arg1)) && al2(sh(arg1)) != 1))) {
			error(ERROR_INTERNAL, CHSH_OFFSETDIVINT);
		}
	}

	return me_b3(sh(arg1), arg1, arg2, offset_div_by_int_tag);
}


exp
f_offset_max(exp arg1, exp arg2)
{
	alignment a1 = al1_of(sh(arg1));
	alignment a2 = al1_of(sh(arg2));
	alignment a3 = al2_of(sh(arg1));
	shape sha;
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!doing_aldefs &&
		    (name(sh(arg1)) != offsethd || name(sh(arg2)) != offsethd)) {
			error(ERROR_INTERNAL, CHSH_OFFSETMAX);
		}
	}

	if (a1->al.al_n != 1 || a2->al.al_n != 1) {
		alignment ares = (alignment)calloc(1, sizeof(aldef));
		if (!doing_aldefs) {
			error(ERROR_INTERNAL, CHSH_OFFSETMAX);
		}
		ares->al.al_n = 2;
		ares->al.al_val.al_join.a = a1;
		ares->al.al_val.al_join.b = a2;
		ares->next_aldef = top_aldef;
		top_aldef = ares;
		sha = f_offset(ares, a3);
	} else {
		sha = f_offset(long_to_al(max(a1->al.al_val.al,
					      a2->al.al_val.al)), a3);
	}

	return me_b3(sha, arg1, arg2, offset_max_tag);
}


exp
f_offset_mult(exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!doing_aldefs &&
		    (name(sh(arg1)) != offsethd || !is_integer(sh(arg2)))) {
			error(ERROR_INTERNAL, CHSH_OFFSETMULT);
		}
	}

	if (shape_size(sh(arg2)) != PTR_SZ) {
		if (PTR_SZ == 32) {
			arg2 = hold_refactor(f_change_variety(f_impossible,
							   slongsh, arg2));
		} else {
			arg2 = hold_refactor(f_change_variety(f_impossible,
							   s64sh, arg2));
		}
	}

	return me_b3(sh(arg1), arg2, arg1, offset_mult_tag);
	/* the order of arguments is being interchanged */
}


exp
f_offset_negate(exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (!doing_aldefs &&
		    (name(sh(arg1)) != offsethd ||
		     (al1(sh(arg1)) != al2(sh(arg1)) && al2(sh(arg1)) != 1
#if TRANS_SPARC
		      && al1_of(sh(arg1)) != REAL_ALIGN
#endif
		      ))) {
			error(ERROR_INTERNAL, CHSH_OFFSETNEG);
		}
	}

	return me_u2(arg1, offset_negate_tag);
}


exp
f_offset_pad(alignment a, exp arg1)
{
	shape sha;
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (name(sh(arg1)) != offsethd) {
			error(ERROR_INTERNAL, CHSH_OFFSETPAD);
		}
	}

	if (a->al.al_n != 1 || al1_of(sh(arg1))->al.al_n != 1) {
		alignment ares = (alignment)calloc(1, sizeof(aldef));
		if (!doing_aldefs) {
			error(ERROR_INTERNAL, ILL_OFFSETPAD);
		}
		ares->al.al_n = 2;
		ares->al.al_val.al_join.a = a;
		ares->al.al_val.al_join.b = al1_of(sh(arg1));
		ares->next_aldef = top_aldef;
		top_aldef = ares;
		sha = f_offset(ares, a);
	} else if (al1_of(sh(arg1))->al.al_val.al_frame != 0) {
		sha = f_offset(al1_of(sh(arg1)), a);
	} else {
		sha = f_offset(long_to_al(max(a->al.al_val.al, al1(sh(arg1)))),
			       a);
	}

	return me_u3(sha, arg1, offset_pad_tag);
}


exp
f_offset_subtract(exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	return me_b3(f_offset(al2_of(sh(arg2)), al2_of(sh(arg1))), arg1, arg2,
		     offset_subtract_tag);
}


exp
f_offset_test(nat_option prob, ntest nt, label dest, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!doing_aldefs &&
		    (name(sh(arg1)) != offsethd || name(sh(arg2)) != offsethd ||
		     /* al1(sh(arg1)) != al1(sh(arg2)) || */
		     al2(sh(arg1)) != al2(sh(arg2)))) {
			error(ERROR_INTERNAL, CHSH_OFFSETTEST);
		}
	}

	if (nt == f_comparable || nt == f_not_comparable) {
		return replace_ntest(nt, dest, arg1, arg2);
	} else {
		return me_q1(prob, convert_ntest[nt], dest, arg1, arg2,
			     test_tag);
	}
}


exp
f_offset_zero(alignment a)
{
	return getexp(f_offset(a, a), NULL, 0, NULL, NULL, 0, 0, val_tag);
}


exp
f_or(exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!eq_shape(sh(arg1), sh(arg2)) || !is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_OR);
		}
	}

	if (~has && HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag))) {
		return TDFcallop3(arg1, arg2, or_tag);
	}

	return me_b2(arg1, arg2, or_tag);
}


exp
f_plus(error_treatment ov_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!eq_shape(sh(arg1), sh(arg2)) || !is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_PLUS);
		}
	}

	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag||
	     ov_err.err_code > 2))) {
		return TDFcallop2(ov_err, arg1, arg2, plus_tag);
	}

	return me_b1(ov_err, arg1, arg2, plus_tag);
}


exp
f_pointer_test(nat_option prob, ntest nt, label dest, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!doing_aldefs &&
		    (name(sh(arg1)) != ptrhd || al1(sh(arg1)) != al1(sh(arg2)))) {
			error(ERROR_INTERNAL, CHSH_PTRTEST);
		}
	}

	if (nt == f_comparable || nt == f_not_comparable) {
		return replace_ntest(nt, dest, arg1, arg2);
	} else {
		return me_q1(prob, convert_ntest[nt], dest, arg1, arg2,
			     test_tag);
	}
}


exp
f_proc_test(nat_option prob, ntest nt, label dest, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		/*
		   ONLY REMOVED TEMPORARILY!
		   if (name(sh(arg1)) != prokhd || name(sh(arg2)) != prokhd)
		   error(ERROR_INTERNAL, CHSH_PROCTEST);
		 */
	}

	if (nt == f_comparable || nt == f_not_comparable) {
		return replace_ntest(nt, dest, arg1, arg2);
	} else {
		return me_q1(prob, convert_ntest[nt], dest, arg1, arg2,
			     test_tag);
	}
}


exp
f_profile(nat n)
{
	return getexp(f_top, NULL, 0, NULL, NULL, 0, natint(n), prof_tag);
}


exp
rem1_aux(error_treatment ov_err, exp arg1, exp arg2)
{
	if (~has && HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag ||
	     ov_err.err_code > 2))) {
		return TDFcallop2(ov_err, arg1, arg2, mod_tag);
	}

	return me_b1(ov_err, arg1, arg2, mod_tag);
}


exp
f_rem1(error_treatment div0_err, error_treatment ov_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!eq_shape(sh(arg1), sh(arg2)) || !is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_REM1);
		}
	}

	return div_rem(div0_err, ov_err, arg1, arg2, rem1_aux);
}


exp
rem0_aux(error_treatment ov_err, exp arg1, exp arg2)
{
	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag ||
	     ov_err.err_code > 2))) {
		return TDFcallop2(ov_err, arg1, arg2, rem0_tag);
	}

	if (has & HAS_DIV0) {
		return me_b1(ov_err, arg1, arg2, rem0_tag);
	}

	if (name(arg2) == val_tag && !isbigval(arg2)) {
		int n = no(arg2);
		if ((n & (n - 1)) == 0) {
			return me_b1(ov_err, arg1, arg2, mod_tag);
		}
	}
	return me_b1(ov_err, arg1, arg2, rem2_tag);
}


exp
f_rem0(error_treatment div0_err, error_treatment ov_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!eq_shape(sh(arg1), sh(arg2)) || !is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_REM0);
		}
	}

	return div_rem(div0_err, ov_err, arg1, arg2, rem0_aux);
}


exp
rem2_aux(error_treatment ov_err, exp arg1, exp arg2)
{
	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag ||
	     ov_err.err_code > 2))) {
		return TDFcallop2(ov_err, arg1, arg2, rem2_tag);
	}

	return me_b1(ov_err, arg1, arg2, rem2_tag);
}


exp
f_rem2(error_treatment div0_err, error_treatment ov_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!eq_shape(sh(arg1), sh(arg2)) || !is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_REM2);
		}
	}

	return div_rem(div0_err, ov_err, arg1, arg2, rem2_aux);
}


static int silly_count = 0; /* for pathological numbers of repeats*/
exp
f_repeat(label repeat_label_intro, exp start, exp body)
{
	exp r = getexp(sh(body), NULL, 0, start, crt_repeat, 0, 0, rep_tag);
	exp labst = get_lab(repeat_label_intro);

	bro(start) = labst;
	clearlast(start);
	setbro(son(labst), body);
	clearlast(son(labst));
	setbro(body, labst);
	setlast(body);
	setsh(labst, sh(body));
	son(crt_repeat) = r;
	crt_repeat = bro(crt_repeat);
	setfather(r, labst);
	if (silly_count == 0) {
		default_freq = (float)(default_freq / 20.0);
	} else {
		silly_count--;
	}
	
	return r;
}


void
start_repeat(label repeat_label_intro)
{
	exp labst;
	exp def;
	def = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, clear_tag);

	/* enter this repeat on crt_repeat and repeat_list - see
	   documentation */
	if (crt_repeat != NULL) {
		++no(crt_repeat);
	}
	repeat_list = getexp(f_top, crt_repeat, 0, NULL, repeat_list, 1, 0,
			     0);
	crt_repeat = repeat_list;
	labst = getexp(f_bottom, NULL, 0, def, NULL, 0, 0, labst_tag);
	if (default_freq < (float)10e10) {
		default_freq = (float)(20.0 * default_freq);
	} else {
		silly_count++;
	}
	fno(labst) = default_freq;
	++proc_label_count;
	set_lab(repeat_label_intro, labst);
	return;
}


exp
f_return(exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}
	if (!reg_result(sh(arg1))) {
		proc_struct_res = 1;
	}

	/* transformation if we are giving procedures which deliver a struct
	   result an extra pointer parameter */
	if (redo_structfns && !reg_result(sh(arg1))) {
		exp ret, obt;
		exp assname, ass;
		shape ptr_res_shape;
		exp_list list;

		if (proc_struct_result == NULL) {
			exp init = getexp(f_pointer(f_alignment(sh(arg1))),
					  NULL, 0, NULL, NULL, 0, 0,
					  clear_tag);
			exp iddec = getexp(sh(arg1), NULL, 0, init, NULL,
					   0, 0, ident_tag);
			setparam(iddec);
			proc_struct_result = iddec;
		}
		ptr_res_shape = f_pointer(f_alignment(sh(arg1)));
		obt = getexp(ptr_res_shape, NULL, 0, proc_struct_result,
			     pt(proc_struct_result), 0, 0, name_tag);
		++no(proc_struct_result);
		pt(proc_struct_result) = obt;

		ret = me_u3(f_bottom, obt, res_tag);

		assname = getexp(ptr_res_shape, NULL, 0, proc_struct_result,
				 pt(proc_struct_result), 0, 0, name_tag);
		++no(proc_struct_result);
		pt(proc_struct_result) = assname;
		ass = hold_refactor(f_assign(assname, arg1));
		list.number = 1;
		list.start = ass;
		list.end = ass;
		return f_sequence(list, ret);
	}
	return me_u3(f_bottom, arg1, res_tag);
}


exp
f_rotate_left(exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!is_integer(sh(arg1)) || !is_integer(sh(arg2))) {
			error(ERROR_INTERNAL, CHSH_ROTL);
		}
	}

	if (~has & HAS_ROTATE) {
		shape sa = sh(arg1);
		int sz = shape_size(sa);
		shape usa = (sz == 8) ? ucharsh : (sz == 16) ?
		    uwordsh : (sz==32)?ulongsh:u64sh;
		exp d1 = me_startid(sa, hold_refactor(f_change_variety(f_wrap,
								    usa, arg1)),
				    0);
		exp d2 = me_startid(sa, arg2, 0);
		exp d3 = me_startid(sa, hold_refactor(f_shift_left(f_impossible,
								me_obtain(d1),
								me_obtain(d2))),
				    0);
		exp d4 = me_startid(sa, hold_refactor(f_minus(f_impossible,
							   me_shint(sh(arg2),
								    sz),
							   me_obtain(d2))), 0);
		exp sr = hold_refactor(f_shift_right(me_obtain(d1),
						  me_obtain(d4)));
		exp orit = hold_refactor(f_or(sr, me_obtain(d3)));
		exp corit = hold_refactor(f_change_variety(f_wrap, sa, orit));
		return hold_refactor(me_complete_id(d1,
						 hold_refactor(me_complete_id(d2,
						 hold_refactor(me_complete_id(d3,
						 hold_refactor(me_complete_id(d4,
								corit))))))));
	}

	return me_b2(arg1, arg2, rotl_tag);
}


exp
f_rotate_right(exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!is_integer(sh(arg1)) || !is_integer(sh(arg2))) {
			error(ERROR_INTERNAL, CHSH_ROTR);
		}
	}

	if (~has & HAS_ROTATE) {
		return f_rotate_left(arg1, hold_refactor(f_minus(f_impossible,
						      me_shint(sh(arg2),
							shape_size(sh(arg1))),
						      arg2)));
	}

	return me_b2(arg1, arg2, rotr_tag);
}


exp
f_sequence(exp_list statements, exp result)
{
	exp r;
	exp h = getexp(f_bottom, result, 0, statements.start, NULL, 0,
		       statements.number, 0);
	exp l = statements.end;
	clear_exp_list(statements);

	/* re-organise so that sequence lists do not get too long.
	   limit to MAX_ST_LENGTH */
	if (statements.number == 0) {
		return result;
	}
	if (statements.number <= MAX_ST_LENGTH) {
		setlast(l);
		setbro(l, h);
		r = getexp(sh(result), NULL, 0, h, NULL, 0, 0, seq_tag);
		setfather(r, result);
		return r;
	} else {
		int num_bits = statements.number / MAX_ST_LENGTH;
		int rest = statements.number - (num_bits * MAX_ST_LENGTH);
		exp_list work;
		exp_list res;
		exp t = statements.start;
		int i, j;
		res = new_exp_list(num_bits + 1);
		if (rest == 0) {
			--num_bits;
			rest = MAX_ST_LENGTH;
		}

		for (i = 0; i < num_bits; ++i) {
			work.start = t;
			work.number = MAX_ST_LENGTH;
			for (j = 0; j < (MAX_ST_LENGTH - 1); ++j) {
				t = bro(t);
			}
			work.end = t;
			t = bro(t);
			res = add_exp_list(res, hold_refactor(f_sequence(work,
							f_make_top())), i);
		}

		work.start = t;
		work.end = l;
		work.number = rest;
		res = add_exp_list(res, hold_refactor(f_sequence(work,
							      f_make_top())),
				   num_bits);
		return f_sequence(res, result);
	}
}


exp
f_shape_offset(shape s)
{
	return getexp(f_offset(f_alignment(s), long_to_al(1)), NULL, 0,
		      NULL, NULL, 0, shape_size(s), val_tag);
}


exp
f_shift_left(error_treatment ov_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!is_integer(sh(arg1)) || !is_integer(sh(arg2))) {
			error(ERROR_INTERNAL, CHSH_SHL);
		}
	}

	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag ||
	     ov_err.err_code > 2))) {
		arg2 = hold_refactor(f_change_variety(ov_err, ulongsh, arg2));
		return TDFcallop2(ov_err, arg1, arg2, shl_tag);
	}

	if (ov_err.err_code == 4) {
		exp d1 = me_startid(f_top, arg1, 0);
		exp d2 = me_startid(f_top, arg2, 0);
		exp d3 = me_startid(f_top, hold_refactor(f_shift_left(f_impossible,
								me_obtain(d1),
								me_obtain(d2))),
				    0);
		exp_list el;
		exp right = hold_refactor(f_shift_right(me_obtain(d3),
						     me_obtain(d2)));
		exp test = me_q1(no_nat_option, f_equal, ov_err.jmp_dest, right,
				 me_obtain(d1), test_tag);
		el = new_exp_list(1);
		el = add_exp_list(el, test, 1);
		return me_complete_id(d1, me_complete_id(d2, me_complete_id(d3,
				      f_sequence(el, me_obtain(d3)))));
	} else if (ov_err.err_code > 4) {
		exp d1 = me_startid(f_top, arg1, 0);
		exp d2 = me_startid(f_top, arg2, 0);
		exp d3 = me_startid(f_top, hold_refactor(f_shift_left(f_impossible,
						      me_obtain(d1),
						      me_obtain(d2))), 0);
		exp_list el;
		exp right = hold_refactor(f_shift_right(me_obtain(d3),
						     me_obtain(d2)));
		exp trp = getexp(f_bottom, NULL, 0, NULL, NULL, 0,
				 f_overflow, trap_tag);
		exp hldr = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, 0);
		exp lb = getexp(f_top, NULL, 0, hldr, NULL, 0, 0,
				labst_tag);
		exp test = me_q1(no_nat_option, f_equal, &lb, right,
				 me_obtain(d1), test_tag);
		el = new_exp_list(1);
		el = add_exp_list(el, test, 1);
		return me_complete_id(d1, me_complete_id(d2, me_complete_id(d3,
				      f_conditional(&lb, f_sequence(el,
						    me_obtain(d3)), trp))));
	}

	return me_b1(ov_err, arg1, arg2, shl_tag);
}


exp
f_shift_right(exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!is_integer(sh(arg1)) || !is_integer(sh(arg2))) {
			error(ERROR_INTERNAL, CHSH_SHR);
		}
	}

	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag))) {
		error_treatment ov_err;
		ov_err = f_wrap;
		arg2 = hold_refactor(f_change_variety(ov_err, ulongsh, arg2));
		return TDFcallop2(ov_err, arg1, arg2, shr_tag);
	}

	return me_b2(arg1, arg2, shr_tag);
}


exp
f_subtract_ptrs(exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}
	return me_b3(f_offset(al1_of(sh(arg2)), al1_of(sh(arg1))), arg1, arg2,
		     minptr_tag);
}


exp
f_variable(access_option acc, tag name_intro, exp init, exp body)
{
	exp i = get_tag(name_intro);
	exp d = son(i);
	UNUSED(acc);
	UNUSED(init);
	setsh(i, sh(body));
	setbro(d, body);
	clearlast(d);
	setfather(i, body);
#ifdef NEWDIAGS
	if (doing_mark_scope) {
		/* must be reading old diags */
		correct_mark_scope(i);
	}
#endif
	return i;
}


void
start_variable(access_option acc, tag name_intro, exp init)
{
	exp i = get_tag(name_intro);
	if (i == NULL || son(i) != i) {
		i = getexp(f_bottom, NULL, 0, init, NULL, 0, 0, ident_tag);
	} else {
		/* could have been already used in env_offset */
		son(i) = init;
	}

	setvar(i);
	if (acc & (f_visible | f_long_jump_access)) {
		setvis(i);
		setenvoff(i);
	} else if ((acc & f_no_other_read) && (acc & f_no_other_write)) {
		setcaonly(i);
	}
	set_tag(name_intro, i);

	return;
}


exp
f_xor(exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!eq_shape(sh(arg1), sh(arg2)) || !is_integer(sh(arg1))) {
			error(ERROR_INTERNAL, CHSH_XOR);
		}
	}

	if (~has & HAS_64_BIT && (name(sh(arg1)) >= s64hd &&
	    (name(arg1) != val_tag || name(arg2) != val_tag))) {
		return TDFcallop3(arg1, arg2, xor_tag);
	}

	return me_b2(arg1, arg2, xor_tag);
}


void
init_exp(void)
{
	freelist = NULL;
	exps_left = 0;
	crt_labno = 0;
	global_case = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, 0);
	in_initial_value = 0;
	initial_value_pp.proc_struct_result = NULL;
	initial_value_pp.has_alloca = 0;
	initial_value_pp.proc_is_recursive = 0;
	initial_value_pp.uses_crt_env = 0;
	initial_value_pp.has_setjmp = 0;
	initial_value_pp.uses_loc_address = 0;
	initial_value_pp.proc_label_count = 0;
	initial_value_pp.proc_struct_res = 0;
	initial_value_pp.default_freq = default_freq;
	initial_value_pp.proc_externs = 0;
	initial_value_pp.in_proc_def = 0;
	initial_value_pp.pushed = NULL;
	initial_value_pp.rep_make_proc = 0;
	return;
}


exp f_dummy_exp;

exp
f_return_to_label(exp e)
{
	has_lv = 1;
	return me_u3(f_bottom, e, return_to_label_tag);
}


nat
f_computed_nat(exp arg)
{
	nat res;
	if (name(arg) == val_tag) {
		if (check & CHECK_EXTRA) {
			if (constovf(arg)) {
				error(ERROR_INTERNAL, ILLNAT);
			}
		}

		if (!isbigval(arg)) {
			nat_issmall(res) = 1;
			natint(res) = no(arg);
			return res;
		} else {
			nat_issmall(res) = 0;
			natbig(res) = no(arg);
			return res;
		}
	}

	if (name(arg) == name_tag && !isvar(son(arg))) {
		res = f_computed_nat(son(son(arg)));
		kill_exp(arg, arg);
		return res;
	}

	error(ERROR_INTERNAL, ILLCOMPNAT);
	nat_issmall(res) = 1;
	natint(res) = 1;
	return res;
}


nat
f_make_nat(tdfint n)
{
	return n;
}


void
init_nat(void)
{
	return;
}


nat f_dummy_nat;

void
init_ntest(void)
{
	return;
}


void
init_otagexp(void)
{
	return;
}


void
init_procprops(void)
{
	return;
}


ntest f_dummy_ntest;

void
init_rounding_mode(void)
{
	return;
}


rounding_mode f_dummy_rounding_mode;

shape
f_bitfield(bitfield_variety bf_var)
{
	return getshape(bf_var.has_sign, const_al1, const_al1, BF_ALIGN,
			bf_var.bits, bitfhd);
}


shape
f_compound(exp off)
{
	int sz;
	if (name(off) ==val_tag) {
		sz = no(off);
	} else {
		error(ERROR_INTERNAL, ILLCPDOFFSET);
		sz = 0;
	}
	return getshape(0, const_al1, const_al1, al1_of(sh(off)), sz, cpdhd);
}


shape
f_floating(floating_variety fv)
{
	switch (fv) {
	case shrealfv:        return shrealsh;
	case realfv:          return realsh;
	case doublefv:        return doublesh;
	case shcomplexfv:     return shcomplexsh;
	case complexfv:       return complexsh;
	case complexdoublefv: return complexdoublesh;
	}

	return realsh;
}


shape
f_integer(variety var)
{
	return var;
}


shape
f_nof(nat n, shape s)
{
	if (doing_aldefs) {
		return s;
	} else {
		int al = shape_align(s);
		int sz = rounder(shape_size(s), al);
		int nm = (int)name(s);
		int nofsz = natint(n)*sz;
		shape res;
		if (name(s) == nofhd) {
			nm = ptno(s);
		}

		if (~has & HAS_64_BIT && !nat_issmall(n)) {
			error(ERROR_INTERNAL, TOO_BIG_A_VECTOR);
		}

		if (name(s) == tophd) {
			/* pathological - make it nof(0, char) */
			res = getshape(0, const_al1, const_al1,
				       align_of(ucharsh), 0, nofhd);
		} else if (al == 1) {
			if ((sz & (sz - 1)) != 0 && nofsz > BF_STORE_UNIT) {
				IGNORE error(ERROR_WARNING, "Bitfields of nof cannot all be variety enclosed");
			}
			if ((sz & (sz - 1)) == 0 || nofsz > BF_STORE_UNIT) {
				shape news = containedshape(sz, 1);
				int nsz = shape_align(news);
				int newn = rounder(nofsz, nsz);
				res = getshape(0, const_al1, const_al1,
					       align_of(news), newn, nofhd);
			} else {
				shape news = containedshape(nofsz, 1);
				res = getshape(0, const_al1, const_al1,
					       align_of(news), shape_size(news),
					       cpdhd);
			}
		} else {
			res = getshape(0, const_al1, const_al1, align_of(s),
				       nofsz, nofhd);
		}

		ptno(res) = nm;	/* set the pt field of the shape to the
				   shapemacs.h hd identifier of the shape */
		return res;
	}
}


shape
f_offset(alignment arg1, alignment arg2)
{
	/* use values pre-computed by init since we never alter shapes */
	if (arg1->al.al_n != 1 || arg2->al.al_n != 1 || arg1->al.sh_hd != 0 ||
	    arg2->al.sh_hd != 0 || arg1->al.al_val.al_frame != 0 ||
	    arg2->al.al_val.al_frame != 0) {
		return getshape(0, arg1, arg2, OFFSET_ALIGN, OFFSET_SZ,
				offsethd);
	}

	/* use values pre-computed by init since we never alter shapes */
	switch (arg1->al.al_val.al) {
	case 512:
		switch (arg2->al.al_val.al) {
		case 512: return f_off512_512;
		case  64: return f_off512_64;
		case  32: return f_off512_32;
		case  16: return f_off512_16;
		case   8: return f_off512_8;
		case   1: return f_off512_1;

		default:
			error(ERROR_INTERNAL, ILLOFF2);
			return f_off64_8;
		}
	case 64:
		switch (arg2->al.al_val.al) {
		case 64: return f_off64_64;
		case 32: return f_off64_32;
		case 16: return f_off64_16;
		case  8: return f_off64_8;
		case  1: return f_off64_1;

		default:
			error(ERROR_INTERNAL, ILLOFF2);
			return f_off64_8;
		}
	case 32:
		switch (arg2->al.al_val.al) {
		case 32: return f_off32_32;
		case 16: return f_off32_16;
		case  8: return f_off32_8;
		case  1: return f_off32_1;

		default:
			error(ERROR_INTERNAL, ILLOFF2);
			return f_off32_8;
		}
	case 16:
		switch (arg2->al.al_val.al) {
		case 16: return f_off16_16;
		case  8: return f_off16_8;
		case  1: return f_off16_1;

		default:
			error(ERROR_INTERNAL, ILLOFF2);
			return f_off16_8;
		}
	case 8:
		switch (arg2->al.al_val.al) {
		case 8: return f_off8_8;
		case 1: return f_off8_1;

		default:
			error(ERROR_INTERNAL, ILLOFF2);
			return f_off8_8;
		}
	case 1:
		switch (arg2->al.al_val.al) {
		case 1: return f_off1_1;

		default:
			error(ERROR_INTERNAL, ILLOFF2);
			return f_off1_1;
		}
	default:
		error(ERROR_INTERNAL, ILLOFF1);
		return f_off8_8;
	}
}


static shape frame_ptrs[32];

static struct SAL {
	alignment al;
	shape ptr_sh;
	struct SAL *rest;
} *cache_pashs;

shape
f_pointer(alignment arg)
{
	/* use values pre-computed by init since we never alter shapes */
	int af = arg->al.al_val.al_frame;
	if (arg->al.al_n != 1 && af == 0) {
		return getshape(0, arg, const_al1, PTR_ALIGN, PTR_SZ, ptrhd);
	}
	if (af != 0) {
		if (frame_ptrs[af] == (shape)0) {
			frame_ptrs[af] = getshape(0, arg, const_al1, PTR_ALIGN,
						  PTR_SZ, ptrhd);
		}
		return frame_ptrs[af];
	}
	if (arg->al.sh_hd != 0) {
		struct SAL *c = cache_pashs;
		shape res;
		while (c != NULL) {
			if (arg == c->al) return c->ptr_sh;
			c = c->rest;
		}
		res = getshape(0, arg, const_al1, PTR_ALIGN, PTR_SZ, ptrhd);
		c = (struct SAL*)xmalloc(sizeof(struct SAL));
		c->al = arg; c->ptr_sh = res; c->rest = cache_pashs;
		cache_pashs = c;
		return res;
	}

	switch (arg->al.al_val.al) {
	case  1: return f_ptr1;
	case  8: return f_ptr8;
	case 16: return f_ptr16;
	case 32: return f_ptr32;
	case 64: return f_ptr64;

	default:
		error(ERROR_INTERNAL, ILLALIGN);
		return f_ptr8;
	};
}


shape f_proc;

void
init_shape(void)
{
	/* pre-compute values for use in f_pointer and f_offset */

	int i;
	for (i = 0; i < 32; i++) {
		frame_ptrs[i] = (shape)0;
	}
	cache_pashs = NULL;

	f_bottom = getshape(0, const_al1, const_al1, const_al1, 0, bothd);

	f_top = getshape(0, const_al1, const_al1, TOP_ALIGN, TOP_SZ, tophd);

	f_proc = getshape(0, const_al1, const_al1, PROC_ALIGN, PROC_SZ, prokhd);

	f_ptr1 = getshape(0, const_al1, const_al1, PTR_ALIGN, PTRBIT_SZ, ptrhd);

	f_ptr8 = getshape(0, const_al8, const_al1, PTR_ALIGN, PTR_SZ, ptrhd);
	f_local_label_value = f_ptr8;

	f_ptr16 = getshape(0, const_al16, const_al1, PTR_ALIGN, PTR_SZ, ptrhd);

	f_ptr32 = getshape(0, const_al32, const_al1, PTR_ALIGN, PTR_SZ, ptrhd);

	f_ptr64 = getshape(0, const_al64, const_al1, PTR_ALIGN, PTR_SZ, ptrhd);

	f_off1_1 = getshape(1, const_al1, const_al1, OFFSET_ALIGN, OFFSET_SZ,
			    offsethd);

	f_off0_0 = getshape(1, const_al1, const_al1, OFFSET_ALIGN, OFFSET_SZ,
			    offsethd);

	f_off8_8 = getshape(1, const_al8, const_al8, OFFSET_ALIGN, OFFSET_SZ,
			    offsethd);

	f_off8_1 = getshape(1, const_al8, const_al1, OFFSET_ALIGN, OFFSET_SZ,
			    offsethd);

	f_off16_16 = getshape(1, const_al16, const_al16, OFFSET_ALIGN,
			      OFFSET_SZ, offsethd);

	f_off16_8 = getshape(1, const_al16, const_al8, OFFSET_ALIGN, OFFSET_SZ,
			     offsethd);

	f_off16_1 = getshape(1, const_al16, const_al1, OFFSET_ALIGN, OFFSET_SZ,
			     offsethd);

	f_off32_32 = getshape(1, const_al32, const_al32, OFFSET_ALIGN,
			      OFFSET_SZ, offsethd);

	f_off32_16 = getshape(1, const_al32, const_al16, OFFSET_ALIGN,
			      OFFSET_SZ, offsethd);

	f_off32_8 = getshape(1, const_al32, const_al8, OFFSET_ALIGN, OFFSET_SZ,
			     offsethd);

	f_off32_1 = getshape(1, const_al32, const_al1, OFFSET_ALIGN, OFFSET_SZ,
			     offsethd);

	f_off64_64 = getshape(1, const_al64, const_al64, OFFSET_ALIGN,
			      OFFSET_SZ, offsethd);

	f_off64_32 = getshape(1, const_al64, const_al32, OFFSET_ALIGN,
			      OFFSET_SZ, offsethd);

	f_off64_16 = getshape(1, const_al64, const_al16, OFFSET_ALIGN,
			      OFFSET_SZ, offsethd);

	f_off64_8 = getshape(1, const_al64, const_al8, OFFSET_ALIGN, OFFSET_SZ,
			     offsethd);

	f_off64_1 = getshape(1, const_al64, const_al1, OFFSET_ALIGN, OFFSET_SZ,
			     offsethd);

	f_off512_512 = getshape(1, const_al512, const_al512, OFFSET_ALIGN,
				OFFSET_SZ, offsethd);

	f_off512_64 = getshape(1, const_al512, const_al64, OFFSET_ALIGN,
			       OFFSET_SZ, offsethd);

	f_off512_32 = getshape(1, const_al512, const_al32, OFFSET_ALIGN,
			       OFFSET_SZ, offsethd);

	f_off512_16 = getshape(1, const_al512, const_al16, OFFSET_ALIGN,
			       OFFSET_SZ, offsethd);

	f_off512_8 = getshape(1, const_al512, const_al8, OFFSET_ALIGN,
			      OFFSET_SZ, offsethd);

	f_off512_1 = getshape(1, const_al512, const_al1, OFFSET_ALIGN,
			      OFFSET_SZ, offsethd);

	return;
}


shape f_dummy_shape;

signed_nat
f_computed_signed_nat(exp arg)
{
	signed_nat res;
	if (name(arg) == val_tag) {
		if (check & CHECK_EXTRA) {
			if (constovf(arg)) {
				error(ERROR_INTERNAL, ILLNAT);
			}
		}

		if (!isbigval(arg)) {
			snat_issmall(res) = 1;
			if (!is_signed(sh(arg))) {
				snatneg(res) = 0;
				snatint(res) = no(arg);
			} else {
				if (no(arg) < 0) {
					snatneg(res) = 1;
					snatint(res) = -no(arg);
				} else {
					snatneg(res) = 0;
					snatint(res) = no(arg);
				}
			}
			return res;
		} else {
			snat_issmall(res) = 0;
			snatneg(res) = (bool)(flptnos[no(arg)].sign == -1);
			flptnos[no(arg)].sign = 1;
			snatint(res) = no(arg);
			return res;
		}
	}

	if (name(arg) == name_tag && !isvar(son(arg))) {
		res = f_computed_signed_nat(son(son(arg)));
		kill_exp(arg, arg);
		return res;
	}

	error(ERROR_INTERNAL, ILLCOMPSNAT);
	snat_issmall(res) = 1;
	snatneg(res) = 0;
	snatint(res) = 1;
	return res;
}


signed_nat
f_snat_from_nat(bool neg, nat n)
{
	signed_nat res;

	if (snat_issmall(n)) {
		snatneg(res) = (bool)((natint(n) == 0) ? 0 : neg);
		snat_issmall(res) = 1;
		snatint(res) = natint(n);
		return res;
	}

	snat_issmall(res) = 0;
	snatbig(res) = natbig(n);
	snatneg(res) = neg;
	return res;
}


signed_nat
f_make_signed_nat(tdfbool neg, tdfint n)
{
	return f_snat_from_nat(neg, n);
}


void
init_signed_nat(void)
{
	return;
}


signed_nat f_dummy_signed_nat;

string f_dummy_string;

void
init_string(void)
{
	return;
}


string
f_concat_string(string a1, string a2)
{
	int i;
	string res;
	if (a1.size != a2.size) {
		error(ERROR_INTERNAL, "Concatenated strings have different unit size");
	}
	res.number = a1.number + a2.number;
	res.size = a1.size;
	if (res.size <= 8) {
		res.ints.chars = (char *)xcalloc(res.number + 1, sizeof(char));
		for (i = 0; i < a1.number; i++) {
			res.ints.chars[i] = a1.ints.chars[i];
		}
		for (i = 0; i < a2.number; i++) {
			res.ints.chars[i + a1.number] = a2.ints.chars[i];
		}
		res.ints.chars[res.number] = 0;
	} else if (res.size <= 16) {
		res.ints.shorts = (short *)xcalloc(res.number + 1,
						   sizeof(short));
		for (i = 0; i < a1.number; i++) {
			res.ints.shorts[i] = a1.ints.shorts[i];
		}
		for (i = 0; i < a2.number; i++) {
			res.ints.shorts[i + a1.number] = a2.ints.shorts[i];
		}
		res.ints.shorts[res.number] =0;
	} else {
		res.ints.longs = (int *)xcalloc(res.number + 1, sizeof(int));
		for (i = 0; i < a1.number; i++) {
			res.ints.longs[i] = a1.ints.longs[i];
		}
		for (i = 0; i < a2.number; i++) {
			res.ints.longs[i + a1.number] = a2.ints.longs[i];
		}
		res.ints.longs[res.number] =0;
	}
	return res;
}


string
f_make_string(tdfstring s)
{
	return s;
}


tagshacc
f_make_tagshacc(shape sha, access_option visible, tag tg_intro)
{
	tagshacc res;
	res.sha = sha;
	res.visible = visible;
	res.tg = tg_intro;
	return res;
}


void
init_tagshacc(void)
{
	return;
}


transfer_mode f_dummy_transfer_mode;

transfer_mode
f_add_modes(transfer_mode md1, transfer_mode md2)
{
	return md1 | md2;
}


version
f_user_info(tdfident t)
{
	version res;
	UNUSED(t);
	res.major_version = MAJOR_VERSION;
	res.minor_version = MINOR_VERSION;
	return res;
}


variety
f_var_limits(signed_nat lower_bound, signed_nat upper_bound)
{
	unsigned int h;
	unsigned int l;

	if (!snat_issmall(lower_bound) || !snat_issmall(upper_bound)) {
		if (snatneg(lower_bound)) {
			return s64sh;
		} else {
			return u64sh;
		}
	}

	/* normalise the varieties to use only the six standard ones */
	l = (unsigned int)(snatint(lower_bound));
	/* these assume the length of unsigned int equals int */
	h = (unsigned int)(snatint(upper_bound));

	if (!snatneg(lower_bound)) {
		if (h <= 255) {
			return ucharsh;
		}
		if (h <= 65535) {
			return uwordsh;
		}
		return ulongsh;
	}

	if (l <= 128 && h <= 127) {
		return scharsh;
	}
	if (l<= 32768 && h <= 32767) {
		return swordsh;
	}

	return slongsh;
}


variety
f_var_width(bool sig, nat bits)
{
	int w = natint(bits);
	if (sig) {
		if (w <= 8) {
			return scharsh;
		}
		if (w <= 16) {
			return swordsh;
		}
		if (w <= 32) {
			return slongsh;
		}
		if (w <= 64) {
			return s64sh;
		}
		error(ERROR_INTERNAL, WIDTH_ERROR);
		return slongsh;
	}

	if (w <= 8) {
		return ucharsh;
	}
	if (w <= 16) {
		return uwordsh;
	}
	if (w <= 32) {
		return ulongsh;
	}
	if (w <= 64) {
		return u64sh;
	}
	error(ERROR_INTERNAL, WIDTH_ERROR);
	return ulongsh;
}


void init_variety
(void)
{
	ucharsh = getshape(0, const_al1, const_al1, UCHAR_ALIGN, UCHAR_SZ,
			   ucharhd);
	scharsh = getshape(1, const_al1, const_al1, SCHAR_ALIGN, SCHAR_SZ,
			   scharhd);
	uwordsh = getshape(0, const_al1, const_al1, UWORD_ALIGN, UWORD_SZ,
			   uwordhd);
	swordsh = getshape(1, const_al1, const_al1, SWORD_ALIGN, SWORD_SZ,
			   swordhd);
	ulongsh = getshape(0, const_al1, const_al1, ULONG_ALIGN, ULONG_SZ,
			   ulonghd);
	slongsh = getshape(1, const_al1, const_al1, SLONG_ALIGN, SLONG_SZ,
			   slonghd);
	u64sh = getshape(0, const_al1, const_al1, U64_ALIGN, U64_SZ, u64hd);
	s64sh = getshape(1, const_al1, const_al1, S64_ALIGN, S64_SZ, s64hd);
	return;
}


variety f_dummy_variety;

version
f_make_version(tdfint major_version, tdfint minor_version)
{
	version res;
	res.major_version = natint(major_version);
	res.minor_version = natint(minor_version);
	if (res.major_version >= 3) {
		newcode = 1;
	} else {
		newcode = 0;
	}
	return res;
}


version_props
f_make_versions(version_props version_info)
{
	UNUSED(version_info);
	return 0;
}


exp_list
new_exp_list(int n)
{
	exp_list res;
	UNUSED(n);
	res.number = 0;;
	res.start = NULL;
	res.end = NULL;

	return res;
}


exp_list
add_exp_list(exp_list list, exp elem, int index)
{
	UNUSED(index);
	++list.number;
	parked(elem) = 1;
	if (list.start == NULL) {
		list.start = elem;
		list.end = elem;
		setlast(elem);
		bro(elem) = NULL;
		return list;
	}
	clearlast(list.end);
	bro(list.end) = elem;
	list.end = elem;
	setlast(elem);
	bro(elem) = NULL;
	return list;
}


caselim_list
new_caselim_list(int n)
{
	UNUSED(n);
	/*  bro(global_case) = NULL;
	    return 0;
	 */
	return NULL;
}


caselim_list
add_caselim_list(caselim_list list, caselim elem, int index)
{
	/* see the documentation for the representation of cases */
	exp ht;
	int low;
	int high;
	exp lowval = getexp(slongsh, NULL, 0, NULL, NULL, 0, 0, 0);
	/* UNUSED(list); */
	UNUSED(index);
	pt(lowval) = get_lab(elem.lab);	/* label for this branch */

	if (snat_issmall(elem.low)) {
		low = snatint(elem.low);
		if (snatneg(elem.low)) {
			low = - low;
		}
	} else if (~has & HAS_64_BIT) {
		SET(low);
		error(ERROR_INTERNAL, TOO_BIG_A_CASE_ELEMENT);
	} else {
		low = snatbig(elem.low);
		if (snatneg(elem.low)) {
			flpt z = new_flpt();
			flt_copy(flptnos[low], &flptnos[z]);
			low = z;
			flptnos[low].sign = - flptnos[low].sign;
		}
		setbigval(lowval);
	}
	no(lowval) = low;

	if (snat_issmall(elem.high)) {
		high = snatint(elem.high);
		if (snatneg(elem.high)) {
			high = - high;
		}
		if (!isbigval(lowval) && high == low) {
			ht = NULL;
		} else {
			ht = getexp(slongsh, NULL, 1, NULL, NULL, 0,
				    high, 0);
		}
	} else if (~has & HAS_64_BIT) {
		SET(ht);
		error(ERROR_INTERNAL, TOO_BIG_A_CASE_ELEMENT);
	} else {
		int lh_eq;
		high = snatbig(elem.high);
		if (snatneg(elem.high)) {
			flpt z = new_flpt();
			flt_copy(flptnos[high], &flptnos[z]);
			high = z;
			flptnos[high].sign = - flptnos[high].sign;
		}
		if (isbigval(lowval)) {
			lh_eq = flt_cmp(flptnos[low], flptnos[high]);
		} else {
			lh_eq = 0;
		}

		if (!lh_eq) {
			ht = getexp(slongsh, NULL, 1, NULL, NULL, 0,
				    high, 0);
			setbigval(ht);
		} else {
			ht = NULL;
		}
	}

	/*     if (ht != NULL && docmp_f((int)f_less_than, ht, lowval)){
	       retcell(lowval);
	       retcell(ht);
	       return 0;
	       }
	 */
	++no(son(pt(lowval)));	/* record label use */
	son(lowval) = ht;
	/*    case_item (lowval);
	 */
	bro(lowval) = list;
	return lowval;
}


label_list
new_label_list(int n)
{
	label_list res;
	res.elems = (label *)xcalloc(n, sizeof(label));
	res.number = n;
	return res;
}


label_list
add_label_list(label_list list, label elem, int index)
{
	exp def;
	exp labst;
	def = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, clear_tag);
	labst = getexp(f_bottom, NULL, 0, def, NULL, 0, 0, labst_tag);
	fno(labst) = default_freq;
	++proc_label_count;
	set_lab(elem, labst);
	list.elems[index] = elem;
	return list;
}


tagshacc_list
new_tagshacc_list(int n)
{
	tagshacc_list res;
	res.size = 0;
	res.id = NULL;
	res.last_id = NULL;
	res.last_def = NULL;
	res.number = n;
	return res;
}


tagshacc_list
add_tagshacc_list(tagshacc_list list, tagshacc elem, int index)
{
	exp d = getexp(elem.sha, NULL, 0, NULL, NULL, 0, 0, clear_tag);
	exp i = getexp(f_bottom, list.last_id, 1, d, NULL, 0, 0, ident_tag);
	UNUSED(index);
	set_tag(elem.tg, i);
	if (list.id == NULL) {
		list.id = i;
	} else {
		bro(list.last_def) = i;
	}
	list.last_def = d;
	list.last_id = i;
	if (elem.visible & (f_visible | f_long_jump_access)) {
		setvis(i);
	}
	if (elem.visible & f_out_par) {
		setoutpar(i);
	}
	setvar(i);
	setparam(i);
	return list;
}


version_list
new_version_list(int n)
{
	UNUSED(n);
	return 0;
}


static int version_printed = 0;

version_list
add_version_list(version_list list, version elem, int index)
{
	UNUSED(list);
	UNUSED(index);
	if (global_version.major_version == 0) {
		global_version = elem;
	}

	if (elem.major_version != global_version.major_version) {
		error(ERROR_INTERNAL, WRONG_VERSION);
		IGNORE fprintf(stderr, "This TDF has mixed versions\n");
	}

	if (report_versions) {
		if (!version_printed) {
			version_printed = 1;
			IGNORE fprintf(stderr, "This TDF is composed from Capsules of the following versions:\n");
		}
		IGNORE fprintf(stderr, "TDF Version %d.%d\n",
			       elem.major_version, elem.minor_version);
	}

	return 0;
}


version f_dummy_version;

access_option no_access_option = 0;

access_option
yes_access_option(access acc)
{
	return acc;
}


string_option no_string_option;
string_option
yes_string_option(string s)
{
	string_option res;
	res.val = s;
	res.present = 1;
	return res;
}


void
init_string_option(void)
{
	no_string_option.present = 0;
}


tagacc_option no_tagacc_option;
tagacc_option
yes_tagacc_option(tagacc elem)
{
	tagacc_option res;
	res.val = elem;
	res.present = 1;
	return res;
}


void
init_tagacc_option(void)
{
	no_tagacc_option.present = 0;
	return;
}


nat_option no_nat_option;
nat_option
yes_nat_option(nat n)
{
	nat_option res;
	res.val = n;
	res.present = 1;
	return res;
}


void
init_nat_option(void)
{
	no_nat_option.present = 0;
	return;
}


void
init_tagacc(void)
{
	return;
}


tagacc
f_make_tagacc(tag tg, access_option acc)
{
	tagacc res;
	res.tg = tg;
	res.visible = acc;
	return res;
}


void
init_transfer_mode(void)
{
	return;
}


void
init_version_props(void)
{
	global_version.major_version = 0;
	global_version.minor_version = 0;
	return;
}


void
init_version(void)
{
	return;
}


void
init_access_option(void)
{
	return;
}


static int seq_n = 0;

char *
init_NAME(char *good_name)
{
	char *prefix  = "__I.TDF";
	time_t t;
	int i, j;
	char *c;
	char *res;
	int sc;
	int sp;
	int sg;
	t = time(NULL) + (time_t)(seq_n++);
	c = asctime(localtime(&t));
	sc = (int)strlen(c);
	sp = (int)strlen(prefix);
	sg = (int)strlen(good_name);
	res = (char*)xcalloc(sc + sp + sg, sizeof(char));
	for (i = 0; i < sp; i++) {
		res[i] = prefix[i];
	}
	for (j = 0; j < sg; i++, j++) {
		res[i] = good_name[j];
	}
	for (j = 0; j < sc; j++) {
		if (isalpha(c[j]) || isdigit(c[j])) {
			res[i] = c[j]; i++;
		}
	}
	res[i] = 0;
	dynamic_init_proc = res;
	return res;
}


void
start_initial_value(void)
{
	if (in_initial_value++ == 0) {
		proc_props *real_pp = NULL;
		if (old_proc_props != NULL) {
			/* initial value in proc */
			push_proc_props();
			real_pp = old_proc_props;
		}
		old_proc_props = &initial_value_pp;
		pop_proc_props();
		old_proc_props = real_pp;
	}
}


exp
f_initial_value(exp e)
{
	if (--in_initial_value > 0) {
		return e;
	}

	initial_value_pp.proc_struct_result = proc_struct_result;
	initial_value_pp.has_alloca = has_alloca;
	initial_value_pp.proc_is_recursive = proc_is_recursive;
	initial_value_pp.uses_crt_env = uses_crt_env;
	initial_value_pp.has_setjmp = has_setjmp;
	initial_value_pp.uses_loc_address = uses_loc_address;
	initial_value_pp.proc_label_count = proc_label_count;
	initial_value_pp.proc_struct_res = proc_struct_res;
	initial_value_pp.default_freq = default_freq;
	initial_value_pp.proc_externs = proc_externs;
	initial_value_pp.in_proc_def = in_proc_def;
	initial_value_pp.pushed = old_proc_props;
	initial_value_pp.rep_make_proc = rep_make_proc;
	if (old_proc_props != NULL) {
		/* init was in a proc - must make new variable */
		dec *my_def = make_extra_dec(make_local_name(), 1, 0, me_u2(e,
					     initial_value_tag), sh(e));
		exp crt_exp = my_def->dec_u.dec_val.dec_exp;
		pop_proc_props();
		return f_contents(sh(e), me_obtain(crt_exp));
	}
	return me_u2(e, initial_value_tag);
}


void
tidy_initial_values(void)
{
	dec *my_def = top_def;
	exp_list initial_as;
	exp_list prom_as;
	char *good_name = NULL;
	initial_as = new_exp_list(0);
	prom_as = new_exp_list(0);
	dynamic_init_proc = NULL;
	while (my_def != NULL) {
		exp crt_exp = my_def->dec_u.dec_val.dec_exp;
		if (son(crt_exp) != NULL && my_def->dec_u.dec_val.extnamed) {
			good_name = my_def->dec_u.dec_val.dec_id;
		}
		if (son(crt_exp) != NULL &&
		    name(son(crt_exp)) == initial_value_tag) {
			/* accumulate assignments of initial values in one
			   explist */
			if (!(my_def->dec_u.dec_val.dec_var)) {
				/* make sure its a variable */
				exp p = pt(crt_exp);
				setvar(crt_exp);
				my_def->dec_u.dec_val.dec_var = 1;
				while (p != NULL) {
					exp np = pt(p);
					exp c = hold_refactor(f_contents(sh(p),
							   me_obtain(crt_exp)));
					replace(p, c, NULL);
					p = np;
				}
			}
			{
				exp init = son(son(crt_exp));
				exp new_init = f_make_value(sh(init));
				if (good_name == NULL) {
					good_name =
					    my_def->dec_u.dec_val.dec_id;
				}
				retcell(son(crt_exp));
				son(crt_exp) = new_init;
				bro(new_init) = crt_exp; setlast(new_init);
				initial_as = add_exp_list(initial_as,
				    hold_refactor(f_assign(me_obtain(crt_exp),
							init)), 0);
			}
		}
		if (do_prom && son(crt_exp) != NULL &&
		    my_def->dec_u.dec_val.dec_var && !is_comm(son(crt_exp))) {
			/* accumulate assignments of non-zero initialisations
			   in one explist */
			exp init = son(crt_exp);
			exp new_init = f_make_value(sh(init));
			if (good_name == NULL) {
				good_name = my_def->dec_u.dec_val.dec_id;
			}
			if (name(init) == compound_tag ||
			    name(init) == nof_tag ||
			    name(init) == concatnof_tag ||
			    name(init) == ncopies_tag ||
			    name(init) == string_tag) {
				dec *id_dec = make_extra_dec(make_local_name(),
							     0, 0, init,
							     sh(init));
				init = me_obtain(id_dec->dec_u.dec_val.dec_exp);
			}
			son(crt_exp) = new_init;
			no(new_init) = -1; /* we may need to distinguish for
					      diags */
			bro(new_init) = crt_exp;
			setlast(new_init);
			prom_as = add_exp_list(prom_as,
					       hold_refactor(f_assign(me_obtain(
							  crt_exp), init)), 0);
		}
		my_def = my_def->def_next;
	}
	if (initial_as.number != 0) {
		/* ie there are some dynamic initialisations */
		exp prc;
		dec *extra_dec;
		tagshacc_list tsl;

		exp ret = f_return(f_make_top());
		exp seq = f_sequence(initial_as, ret);
		tsl = new_tagshacc_list(0);

		old_proc_props = &initial_value_pp;  pop_proc_props();
		old_proc_props = NULL;
		rep_make_proc = 0;
		push_proc_props();
		prc = f_make_proc(f_top, tsl, no_tagacc_option, seq);
		/* prc has one visible param - hence looks like varargs */
		if (do_prom) {
			/* struct (proc, ptr) */
			exp off_proc = hold_refactor(f_offset_zero(PROC_ALIGN));
			exp off_ptr = hold_refactor(f_offset_pad(PTR_ALIGN,
						 hold_refactor(f_offset_add(copy(
						 off_proc), hold_refactor(
						 f_shape_offset(f_proc))))));
			shape str_sh = f_compound(hold_refactor(f_offset_add(copy(
						  off_ptr), hold_refactor(
						  f_shape_offset(f_pointer(
						  PROC_ALIGN))))));
			dec *str_dec = make_extra_dec(make_local_name(), 1, 0,
						      f_make_value(str_sh),
						      str_sh);
			dec *prc_dec = make_extra_dec(make_local_name(), 0, 0,
						      prc, f_proc);
			exp prc_exp = prc_dec->dec_u.dec_val.dec_exp;
			exp str_exp = str_dec->dec_u.dec_val.dec_exp;
			exp list_exp = find_named_tg("__PROM_init_list",
						     f_pointer(f_alignment(
						     str_sh)));
			brog(list_exp)->dec_u.dec_val.dec_var = 1;
			setvar(list_exp);
			prom_as = add_exp_list(prom_as, hold_refactor(f_assign(
					       f_add_to_ptr(me_obtain(str_exp),
							    copy(off_proc)),
					       me_obtain(prc_exp))), 0);
			prom_as = add_exp_list(prom_as, hold_refactor(f_assign(
					       f_add_to_ptr(me_obtain(str_exp),
							    copy(off_ptr)),
					       f_contents(sh(list_exp),
					       me_obtain(list_exp)))), 0);
			prom_as = add_exp_list(prom_as, hold_refactor(f_assign(
					       me_obtain(list_exp),
					       me_obtain(str_exp))), 0);
		} else {
			extra_dec = make_extra_dec(add_prefix(name_prefix, init_NAME(good_name)),
				0, 1, prc, f_proc);
		}
	}
	if (do_prom && prom_as.number != 0) {
		/* ie there are some prom initialisations */
		exp prc;
		dec *extra_dec;
		tagshacc_list tsl;

		exp ret = f_return(f_make_top());
		exp seq = f_sequence(prom_as, ret);
		tsl = new_tagshacc_list(0);

		rep_make_proc = 0;
		start_make_proc(f_top, tsl, no_tagacc_option);
		prc = f_make_proc(f_top, tsl, no_tagacc_option, seq);
		extra_dec = make_extra_dec(add_prefix(name_prefix, init_NAME(good_name)),
			0, 1, prc, f_proc);
	}
}
