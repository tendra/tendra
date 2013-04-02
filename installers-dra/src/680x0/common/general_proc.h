/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <construct/installtypes.h>

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
