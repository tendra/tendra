/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
			    VERSION INFORMATION
			    ===================
--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/general_proc.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: general_proc.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.2  1997/10/29 10:22:16  ma
Replaced use_alloca with has_alloca.

Revision 1.1.1.1  1997/10/13 12:42:52  ma
First version.

Revision 1.3  1997/09/25 06:45:07  ma
All general_proc tests passed


--------------------------------------------------------------------------
*/

#include "config.h"

#include "installtypes.h"
#include "exptypes.h"
#include "localtypes.h"

void apply_general_proc(exp e, where dest, ash stack);
void tail_call(exp e, where dest, ash stack);
void gcproc(exp p, char* pname, long cname, int is_ext, int reg_res, diag_global* di);
void general_epilogue(bool uses_caller_pointer, bool has_checkstack);
void untidy_return(void);
void make_visible(exp e);
void make_transformations(void);
void output_env_size(dec* proc, long envsize);
typedef enum {ALL, NOT_SP, NOT_A6_OR_SP} restore_type_t;
void restore_regs(restore_type_t);
