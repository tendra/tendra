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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/68k_globals.c,v 1.1.1.1 1998/01/17 15:55:48 release Exp $
--------------------------------------------------------------------------
$Log: 68k_globals.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
Revision 1.2  1997/10/29 10:22:03  ma
Replaced use_alloca with has_alloca.

Revision 1.1.1.1  1997/10/13 12:42:46  ma
First version.

Revision 1.1  1997/10/13 09:54:22  ma
First version.


--------------------------------------------------------------------------
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
