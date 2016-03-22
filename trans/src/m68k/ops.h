/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPS_H
#define OPS_H

extern bool have_cond;
extern bool D1_is_special;
extern int crt_rmode;

/* ops_float.c */
void abs_float(shape, where, where);
void change_flvar(shape, where, where);
void fl_binop(int, shape, where, where, where);
void int_to_float(shape, where, where);
void negate_float(shape, where, where);
void round_float(shape, where, where);

/* ops_int.c */
void add(shape, where, where, where);
void sub(shape, where, where, where);
void negate(shape, where, where);
void mult(shape, where, where, where);
void div1(shape, where, where, where);
void div2(shape, where, where, where);
void rem1(shape, where, where, where);
void rem2(shape, where, where, where);
void maxop(shape, where, where, where);
void minop(shape, where, where, where);
void absop(shape, where, where);

/* ops_misc.c */
void trap_ins(int);
void callins(long, exp);
void jmpins(exp);
bool cmp(shape, where, where, long);
void move_const(shape, long, long, where);
void move_bytes(long, where, where, int);
void move(shape, where, where);
void mova(where, where);
long range_max(shape);
long range_min(shape);
void change_var_sh(shape, shape, where, where);
void change_var(shape, where, where);

/* ops_logic.c */
void and (shape, where, where, where);
void or (shape, where, where, where);
void xor(shape, where, where, where);
void not(shape, where, where);
void rshift(shape, where, where, where);
void shift(shape, where, where, where);
void bitf_to_int(exp, shape, where, ash);
void int_to_bitf(exp, exp, ash);
void bit_test(shape, where, where);

extern int overflow_jump;
extern int err_continue;

#define CONTINUE_ERR 2

#define set_continue(e) if (errhandle(e) ==CONTINUE_ERR)err_continue = 1
#define clear_continue(e)(err_continue = 0)
#define have_continue()(err_continue != 0)

#endif

