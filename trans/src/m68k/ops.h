/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPERATIONS_INCLUDED
#define OPERATIONS_INCLUDED

#include <local/ash.h>

#include <reader/exp.h>

#include <construct/installtypes.h>

extern bool have_cond;
extern bool D1_is_special;
extern int crt_rmode;

extern void absop(shape, where, where);
extern void add(shape, where, where, where);
extern void and(shape, where, where, where);
extern void bitf_to_int(exp, shape, where, ash);
extern void bit_test(shape, where, where);
extern void callins(long, exp);
extern void jmpins(exp);
extern void trap_ins(int);
extern void change_var_sh(shape, shape, where, where);
extern void change_var(shape, where, where);
extern bool cmp(shape, where, where, long);
extern void div1(shape, where, where, where);
extern void div2(shape, where, where, where);
extern void int_to_bitf(exp, exp, ash);
extern void maxop(shape, where, where, where);
extern void minop(shape, where, where, where);
extern void mova(where, where);
extern void move(shape, where, where);
extern void move_const(shape, long, long, where);
extern void move_bytes(long, where, where, int);
extern void mult(shape, where, where, where);
extern void negate(shape, where, where);
extern void not(shape, where, where);
extern void or(shape, where, where, where);
extern void rem1(shape, where, where, where);
extern void rem2(shape, where, where, where);
extern void rshift(shape, where, where, where);
extern void shift(shape, where, where, where);
extern void sub(shape, where, where, where);
extern void xor(shape, where, where, where);

extern void abs_float(shape, where, where);
extern void change_flvar(shape, where, where);
extern void fl_binop(int, shape, where, where, where);
extern void int_to_float(shape, where, where);
extern void negate_float(shape, where, where);
extern void round_float(shape, where, where);

extern long range_max(shape);
extern long range_min(shape);

extern int overflow_jump;
extern int err_continue;

#define CONTINUE_ERR 2

#define set_continue(e) if (errhandle(e) ==CONTINUE_ERR)err_continue = 1
#define clear_continue(e)(err_continue = 0)
#define have_continue()(err_continue != 0)
#endif
