/* $Id$ */

/*
 * Copyright 2007-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"

#include "localflags.h"

int is80486;		/* compile for 80486 */
int is80586;		/* compile for 80586 */
int always_use_frame;
int gcc_compatible = GCC_STRUCTS;
int module_has_setjmp = 0;
int stack_aligned_8byte = 0;
int permit_8byte_align = 1;
int useful_double = 0;
int keep_short = 0;	/* init by cproc */

weak_cell * weak_list = (weak_cell*)0;
