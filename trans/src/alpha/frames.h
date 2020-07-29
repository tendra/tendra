/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef FRAMES
#define FRAMES

#include <construct/installtypes.h>


extern bool Has_fp;

extern bool Has_tos;

extern bool No_S;

extern bool Has_vcallees;
extern bool Has_no_vcallers;

extern int local_reg;
extern int callee_size;

extern void  setframe_flags(exp e, bool leaf);


extern void setframe_info(exp e);

extern int frame_offset(exp id);

#endif
