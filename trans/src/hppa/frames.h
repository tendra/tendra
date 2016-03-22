/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef FRAMES
#define FRAMES

#include <construct/installtypes.h>

#include "addr.h"

extern bool Has_fp;
extern bool Has_vsp;
extern bool Has_tos;
extern bool No_S;
extern bool Has_ll;
extern bool Has_checkalloc;
extern bool Has_vcallees;
extern bool Uses_crt_env;
extern bool Has_no_vcallers;
extern bool is_PIC_and_calls;
extern bool plusZ;

extern long callees_offset;
extern long params_offset;
extern long locals_offset;
extern long frame_sz;
extern long max_args;
extern long locals_space;
extern int fixdump;
extern long stackerr_lab,aritherr_lab;

extern baseoff MEM_TEMP_BOFF,LONG_RESULT_BOFF,SP_BOFF,FP_BOFF;

/* EXTENSION */ extern bool Has_vcallees;

extern long frame_offset(exp id);
extern void set_up_frame(exp);
extern void setframe_flags(exp, bool);

/* EXTENSION */ extern long callee_sz;

#endif











