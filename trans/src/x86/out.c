/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* Low level output routines */

#include <stdio.h>
#include <stdlib.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <local/out.h>
#include <local/cpu.h>

#ifdef DWARF2
#include <local/dw2_config.h>
#endif

#include <reader/basicread.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include "localtypes.h"
#include "cproc.h"
#include "instr.h"

#ifdef DWARF2
long instr_count = -1;
#endif

/*
 * XXX: break as_file encapsulation.
 * This ugly hack seems currently to be necessary for inserting
 * stabs debug information until the stabs mechanism is fixed
 * properly.
 */
FILE *
out_get_stream(void)
{
	return as_file;
}

void
out_hook_nl(void)
{
	/* XXX: is out.c the right place? */
#ifdef DWARF2
	instr_count = -1;
#endif
	keep_short = cpu & CPU_80586;
}

/*
 * Return the current position in bytes
 */
long
out_tell_pos(void)
{
	long p;

	if ((p = ftell(as_file)) == -1L) {
		error(ERR_INTERNAL, "out_tell_pos: ftell error");
		exit(EXIT_FAILURE);
	}

	return p;
}

/*
 * Set position in bytes
 */
void
out_set_pos(long pos)
{
	if (fseek(as_file, pos, SEEK_SET) == -1) {
		error(ERR_INTERNAL, "out_set_pos: fseek error");
		exit(EXIT_FAILURE);
	}
}
