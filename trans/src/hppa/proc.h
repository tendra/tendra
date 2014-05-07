/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef PROCDECS_INCLUDED
#define PROCDECS_INCLUDED

#include <local/exptypes.h>

#include <construct/installtypes.h>

#include "addrtypes.h"
#include "proctypes.h"

struct proc_state {
    ans procans;
    bool leaf;
    baseoff mem_temp0;
    int rscope_level;
    int rscope_label;
    int result_label;
    long callees_offset;
    long params_offset;
    long frame_sz;
    long locals_offset;
    long locals_space;
    long max_args;
    long fixdump;
};


extern struct proc_state proc_state;
extern baseoff mem_temp(int);
extern makeans make_proc_tag_code(exp, space, where, int);
extern makeans make_rscope_tag_code(exp, space, where, int);
extern makeans make_res_tag_code(exp, space, where, int);
extern makeans make_apply_tag_code(exp, space, where, int);
extern void restore_sregs(void);

#endif /* PROCDECS_INCLUDED */
