/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"

#include "68k_globals.h"

int not_in_params = 1;
int not_in_postlude = 1;
int need_preserve_stack = 0;
dec* cur_proc_dec = 0;
int cur_proc_has_tail_call = 0;
int cur_proc_use_same_callees = 0;
int cur_proc_has_vcallees = 0;
long cur_proc_callees_size = 0;
long cur_proc_callers_size = 0;
long cur_proc_env_size = 0;
int apply_tag_flag = 0;

