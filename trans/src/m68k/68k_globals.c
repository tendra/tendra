/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>

#include "68k_globals.h"

bool need_preserve_stack       = false;
dec* cur_proc_dec              = 0;
bool cur_proc_has_tail_call    = false;
bool cur_proc_use_same_callees = false;
bool cur_proc_has_vcallees     = false;
long cur_proc_callees_size     = 0;
long cur_proc_callers_size     = 0;
long cur_proc_env_size         = 0;
int apply_tag_flag             = 0;

