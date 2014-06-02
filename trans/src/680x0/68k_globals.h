/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __68k_globals__
#define __68k_globals__

#include <reader/expmacs.h>

#include <construct/exp.h>

/* global variables describing the current procedure */

extern int not_in_params;
extern int not_in_postlude;
extern int need_preserve_stack;
extern dec* cur_proc_dec;
extern int cur_proc_has_tail_call;
extern int cur_proc_use_same_callees;
extern int cur_proc_has_vcallees;
extern long cur_proc_callees_size;
extern long cur_proc_callers_size;
extern long cur_proc_env_size;
extern int apply_tag_flag;

#endif

