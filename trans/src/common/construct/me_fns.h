/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <reader/exp.h>

#include <reader/code.h>

#include <construct/installtypes.h>

extern exp me_u1(error_treatment ov_err, exp arg1, unsigned char nm);
extern exp me_u2(exp arg1, unsigned char nm);
extern exp me_u3(shape sha, exp arg1, unsigned char nm);
extern exp me_b1(error_treatment ov_err, exp arg1, exp arg2, unsigned char nm);
extern exp me_b2(exp arg1, exp arg2, unsigned char nm);
extern exp me_b3(shape sha, exp arg1, exp arg2, unsigned char nm);
extern exp me_b4(error_treatment div0_err, error_treatment ov_err, exp arg1, exp arg2,
		unsigned char nm);
extern exp me_c1(shape sha, error_treatment ov_err, exp arg1, unsigned char nm);
extern exp me_c2(shape sha, exp arg1, unsigned char nm);
extern exp me_l1(shape sha, unsigned char nm);
extern exp me_q1(nat_option prob, ntest nt, label dest, exp arg1, exp arg2,
		 unsigned char nm);
extern exp me_q2(nat_option prob, error_treatment err, ntest nt, label dest,
		 exp arg1, exp arg2, unsigned char nm);
extern exp me_shint(shape sha, int i);
extern exp me_obtain(exp id);
extern exp me_startid(shape sha, exp def, int isv);
extern exp me_start_clearvar(shape idsh, shape initsh);
extern exp me_complete_id(exp id, exp body);
extern void note_repeat(exp r);
extern alignment long_to_al(int n);
extern int is_integer(shape s);
extern int is_float(shape s);
extern int is_complex(shape s);
extern exp me_null(shape sha, int i, unsigned char nm);

extern floating_variety float_to_complex_var(floating_variety f);
extern floating_variety complex_to_float_var(floating_variety f);

extern void clear_exp_list(exp_list el);
/* defined in install_fns.c */
