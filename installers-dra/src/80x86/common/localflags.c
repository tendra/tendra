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

#include "config.h"

#include <construct/flags.h>

#include "localflags.h"

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

void
set_format(enum format format)
{
	switch (format) {
	case FORMAT_AOUT:
		local_prefix = "L";
		name_prefix = "_";
		normal_fpucon = 0x372;
		break;

	case FORMAT_ELF:
		local_prefix = ".L";
		name_prefix = "";
		normal_fpucon = 0x37f;
		break;

	default:
		fprintf(stderr, "unknown format-specific local flags\n");
		exit(EXIT_FAILURE);
	}

	prefix_length = strlen(name_prefix);
}

