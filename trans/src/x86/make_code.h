/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CODER_H
#define CODER_H

#include <local/ash.h>

#include <reader/exp.h>

void make_code(where dest, ash stack, exp e);
void clean_stack(void);

#ifdef TDF_DIAG4
void diag_arg(where dest, ash stack, exp e);
#endif

extern bool remove_struct_ref;
extern int regsinuse;
extern int min_rfree;
extern int max_stack;
extern int crt_ret_lab;
extern bool crt_ret_lab_used;
extern outofline *odd_bits;
extern int last_odd_bit;
extern bool doing_odd_bits;
extern outofline *current_odd_bit;
extern int repeat_level;
extern bool not_in_params;
extern bool not_in_postlude;
extern int retjmp_count;
extern float scale;
extern exp crt_proc_exp;
extern exp vc_pointer;
extern int callee_size;
extern bool has_dy_callees;
extern bool has_tail_call;
extern bool has_same_callees;
extern bool need_preserve_stack;
extern bool proc_has_asm;

#endif /* CODER_H */
