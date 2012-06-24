/* $Id$ */

/*
 * Copyright 2007-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"

#include <construct/flags.h>

#include <linkinfo/li_types.h>

extern  int is80486;		/* compile for 80486 */
extern  int is80586;		/* compile for 80586 */
extern  int always_use_frame;	/* always use %ebp as a frame pointer */
extern  int gcc_compatible;	/* produce gcc compatible code */
extern  int module_has_setjmp;
extern  int stack_aligned_8byte;
extern  int permit_8byte_align;
extern  int useful_double;
extern  int keep_short;
extern	int remove_struct_ref;

extern	unsigned prefix_length;
extern	unsigned normal_fpucon;

extern	char *local_prefix;
extern	char *name_prefix;

void set_format(enum format format);

