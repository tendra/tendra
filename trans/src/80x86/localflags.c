/* $Id$ */

/*
 * Copyright 2007-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <local/localflags.h>

#include <construct/flags.h>

enum cpu cpu;
int always_use_frame;
int gcc_compatible = 0;
int module_has_setjmp = 0;
int stack_aligned_8byte = 0;
int permit_8byte_align = 1;
int useful_double = 0;
int keep_short = 0;	/* init by cproc */
int remove_struct_ref;

unsigned prefix_length;
unsigned normal_fpucon;

char *local_prefix;
char *name_prefix;

