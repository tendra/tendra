/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/68k_globals.h,v 1.1.1.1 1998/01/17 15:55:48 release Exp $
--------------------------------------------------------------------------
$Log: 68k_globals.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
Revision 1.2  1997/10/29 10:22:05  ma
Replaced use_alloca with has_alloca.

Revision 1.1.1.1  1997/10/13 12:42:46  ma
First version.

Revision 1.1  1997/10/13 09:54:24  ma
First version.


--------------------------------------------------------------------------
*/

#ifndef __68k_globals__
#define __68k_globals__
#include "config.h"
#include "expmacs.h"
#include "exp.h"

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
