/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <local/szs_als.h>
#include <local/tag.h>

#include <tdf/nat.h>
#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/messages_r.h>
#include <reader/main_reads.h>

#include <construct/exp.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>

#include <special/special_tok.h>

#include <main/flags.h>

#include <refactor/refactor.h>

#include "localexpmacs.h"

#define MAX_INT 2147483647
#define MIN_INT (-MAX_INT-1)
#define UMAX_INT 4294967295U

extern shape f_off64_64;
extern shape f_off32_32;

/*
 * This function returns a component at offset 'align' from the
 * compound given in e.
 */
static exp
get_component(exp e, alignment shc, alignment align, int size, int nm, shape offshape, int offset)
{
	/* offset in compound for required component */
	exp offsetexp = getexp(offshape, NULL, 0, NULL, NULL, 0, offset, val_tag);

	/* shape of component */
	shape resshape = getshape(1, shc, shc, align, size, nm);

	return hold_refactor(f_component(resshape, hold_refactor(me_u3(sh(son(son(e))), e, cont_tag)), offsetexp));
}

static bool
special_sync_handler(tokval *tkv, token t, bitstream pars)
{
	tkv->tk_exp = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, special_tag);

	return true;
}

/*
 * This is a means of invoking alpha assembler instructions
 * from a TDF file
 */
static bool
special_alpha(tokval *tkv, token t, bitstream pars)
{
	exp arg;
	place old_place;

	old_place = keep_place();
	set_place(pars);
	arg = d_exp();
	assert(arg->tag == val_tag);

	if (no(arg) == 0) {
		/* trapb : used to ensure that all pending execptions have been raised
		before continuing */
		tkv->tk_exp = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, special_tag);
	} else {
		error(ERR_INTERNAL,  "Unsupported argument to token __alpha_special");
		tkv->tk_exp = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, null_tag);
	}

	set_place(old_place);

	return true;
}

/*
 * builtin function taking a TYPE argument and returning true
 * if the argument is float, double or long double and false otherwise
 *
 * This token is provided only for va_arg() in the API header glue to give
 * the appropriate sizes for the Alpha calling conventions.
 */
static bool
special_isfloat(tokval *tkv, token t, bitstream pars)
{
	place old_place;
	shape arg;
	signed_nat lower,upper,resval;

	old_place=keep_place();
	set_place(pars);
	arg = d_shape();

	resval.issmall  = lower.issmall  = upper.issmall  = 1;
	resval.negative = lower.negative = upper.negative = 0;
	lower.signed_nat_val.small_s_nat = MIN_INT;
	upper.signed_nat_val.small_s_nat = MAX_INT;

	if (is_floating(arg->tag)) {
		resval.signed_nat_val.small_s_nat=1;
	} else {
		resval.signed_nat_val.small_s_nat=0;
	}

	tkv->tk_exp = f_make_int(slongsh,resval);
	set_place(old_place);

	return true;
}

static bool
special_va_token(tokval *tkv, token t, bitstream pars)
{
	tkv->tk_exp = getexp(f_off32_32, NULL, 0, NULL, NULL, 0, 0, val_tag);
	set_vararg(tkv->tk_exp);

	return true;
}

/*
 * builtin function taking 3 arguments: a va_list, a va_alist,
 * and an integer i.e a compound(ptrhd,slonghd),
 * an integer(s64shd) and an integer(slonghd).
 *
 * The pointer field of the compound is set equal to the 64 bit integer,
 * and the integer field is set to 8.
 */
static bool
special_va_start(tokval *tkv, token t, bitstream pars)
{
	place old_place;
	exp arg1, arg2, arg3; /* parameters of the token */
	exp_list list; /* list of exps used to construct the result sequence */
	exp res = f_make_top();	/* the result part of the sequence */
	exp assignment1, assignment2; /* the two assignment operations */
	exp component1, component2; /* the components of the exp */
	exp copy_of_compound;

	old_place = keep_place();
	set_place(pars);

	arg1 = d_exp();
	arg2 = d_exp();
	arg3 = d_exp(); /* don't care */

	/*
	 * here we start to perform the transformation.
	 * We must obtain the compound variable of arg1 and apply the
	 * component operation to separate out the pointer and integer
	 * for use in subsequent assignments.
	 */

	set_vararg(arg1);
	copy_of_compound = copyexp(arg1);
	component1 = get_component(arg1, const_al64, PTR_ALIGN, PTR_SZ, ptrhd, f_off64_64, 0);
	component2 = get_component(copy_of_compound, const_al32, SLONG_ALIGN, SLONG_SZ, slonghd, f_off32_32, 64);
	assignment1 = f_assign(component1, arg2);
	assignment2 = f_assign(component2, getexp(f_off32_32, NULL, 0, NULL, NULL, 0, 0, val_tag));
	bro(assignment1) = assignment2;
	list.start = assignment1;
	list.end = assignment2;
	list.number = 2;
	tkv->tk_exp = f_sequence(list,res);
	kill_exp(arg3,arg3);
	set_place(old_place);

	return true;
}

const struct special_tok special_toks[] = {
	{ "~Sync_handler",      0,              special_sync_handler },

	{ "__alpha_special",    BUILTIN_ASM,    special_alpha        },

	{ "__builtin_isfloat",  BUILTIN_VARARG, special_isfloat      },
	{ "__builtin_va_token", BUILTIN_VARARG, special_va_token     },
	{ "__builtin_va_start", BUILTIN_VARARG, special_va_start     }
};

size_t special_toks_count = sizeof special_toks / sizeof *special_toks;

