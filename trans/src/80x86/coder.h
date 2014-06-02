/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CODER_H
#define CODER_H

#include <reader/exptypes.h>
#include <local/localtypes.h>

void coder(where dest, ash stack, exp e);
void clean_stack(void);

#ifdef NEWDIAGS
void diag_arg(where dest, ash stack, exp e);
#endif

extern int regsinuse;
extern int min_rfree;
extern int max_stack;
extern int crt_ret_lab;
extern int crt_ret_lab_used;
extern outofline *odd_bits;
extern int last_odd_bit;
extern int doing_odd_bits;
extern outofline *current_odd_bit;
extern int repeat_level;
extern int not_in_params;
extern int not_in_postlude;
extern int retjmp_count;
extern float scale;
extern exp crt_proc_exp;
extern exp vc_pointer;
extern int callee_size;
extern int has_dy_callees;
extern int has_tail_call;
extern int has_same_callees;
extern int need_preserve_stack;
extern int proc_has_asm;

#endif /* CODER_H */
