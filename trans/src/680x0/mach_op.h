/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MACH_OP_INCLUDED
#define MACH_OP_INCLUDED

#include <construct/installtypes.h>

extern bool check_op(mach_op *, int);
extern bool equal_op(mach_op *, mach_op *);
extern void free_mach_op(mach_op *);
extern mach_op * new_mach_op(void);

extern mach_op * make_bitfield_op(mach_op *, int, int);
extern mach_op * make_dec_sp(void);
extern mach_op * make_extern(char *, long);
extern mach_op * make_extern_data(char *, long);
extern mach_op * make_extern_ind(char *, long);
extern mach_op * make_float_data(flt *);
extern mach_op * make_hex_data(long);
extern mach_op * make_hex_value(long);
extern mach_op * make_inc_sp(void);
extern mach_op * make_ind_rel_ap(long, long);
extern mach_op * make_index_op(mach_op *, mach_op *, int);
extern mach_op * make_indirect(int, long);
extern mach_op * make_int_data(long);
extern mach_op * make_lab(long, long);
extern mach_op * make_lab_data(long, long);
extern mach_op * make_lab_diff(long, long);
extern mach_op * make_lab_ind(long, long);
extern mach_op * make_postinc(int);
extern mach_op * make_reg_index(int, int, long, int);
extern mach_op * make_reg_pair(int, int);
extern mach_op * make_register(int);
extern mach_op * make_rel_ap(long);

#ifndef tdf3
extern mach_op * make_rel_ap2(long);
extern mach_op * make_rel_sp(long);
extern mach_op * make_ind_rel_ap2(long, long);
extern mach_op * make_ind_rel_ap3(long, long);
extern mach_op * make_predec(int);
extern mach_op * make_ldisp(long);
#endif

extern mach_op * make_special(char *);
extern mach_op * make_special_data(char *);
extern mach_op * make_value(long);

extern long special_no;
extern char *special_str;

extern int tmp_reg_prefer;
extern int tmp_reg_status;
extern void avoid_tmp_reg(int);
extern int next_tmp_reg(void);
extern int tmp_reg(int, mach_op *);

#endif
