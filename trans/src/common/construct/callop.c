/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/bool.h>
#include <shared/error.h>
#include <shared/string.h>

#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>
#include <construct/machine.h>
#include <construct/install_fns.h>
#include <construct/callop.h>

#include <main/flags.h>

#include <utility/prefix.h>

#include <refactor/refactor.h>


static dec *
find_named_dec(char *n)
{
	/* find a global with name n */
	dec *d;

	for (d = top_def; d != NULL; d = d->next) {
		char *name = d->name;
		if (streq(name + strlen(name_prefix), n)) {
			return d;
		}
	}

	return NULL;
}


exp
find_named_tag(char *n, shape s)
{
	/* find a global with name n */
	dec *d = find_named_dec(n);
	if (d != NULL) {
		return d->exp;
	}
	d = make_extra_dec(add_prefix(name_prefix, n), 0, 1, NULL, s);
	return d->exp;
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
		error(ERR_INTERNAL, "No fn for long op");
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
	novar.present = false;
	dc = find_named_tag(nm, f_proc);
	ob = me_obtain(dc);
	pars.number = 2;
	pars.start = arg1;
	pars.end = arg2;
	bro(arg1) = arg2;
	arg1->last = false;

	res = f_apply_proc(sh(arg1), ob, pars, novar);
	res = hold_refactor(res);
	return res;
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
	novar.present = false;
	dc = find_named_tag(nm, f_proc);
	ob = me_obtain(dc);
	pars.number = 2;
	pars.start = arg1;
	pars.end = arg2;
	bro(arg1) = arg2;
	arg1->last = false;

	res = f_apply_proc((n==test_tag)?slongsh:sh(arg1), ob, pars, novar);

	return TDFwithet(ov_err, res);
}


exp
TDFcallop1(error_treatment ov_err, exp arg1, int n)
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
	novar.present = false;
	dc = find_named_tag(nm, f_proc);
	ob = me_obtain(dc);
	pars.number = 1;
	pars.start = arg1;
	pars.end = arg1;

	res = f_apply_proc(sh(arg1), ob, pars, novar);

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
	Te = find_named_tag("__TDFerror", slongsh);
	brog(Te)->var = 1;
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
TDFcallaux(error_treatment ov_err, exp arg1, char *nm, shape s)
{
	exp dc;
	exp ob;
	exp_list pars;
	exp_option novar;
	exp res;
	novar.present = false;
	dc = find_named_tag(nm, f_proc);
	ob = me_obtain(dc);
	pars.number = 1;
	pars.start = arg1;
	pars.end = arg1;

	res = f_apply_proc(s, ob, pars, novar);
	res = hold_refactor(res);
	return TDFwithet(ov_err, res);
}


