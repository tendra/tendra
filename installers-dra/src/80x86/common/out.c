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

#include <shared/check.h>

#include "config.h"

#ifdef NEWDWARF
#include "dw2_config.h"
#endif

#include <reader/basicread.h>

#include <construct/flags.h>

#include "localflags.h"
#include "instr.h"
#include "messages_8.h"
#include "out.h"

static FILE *fpout;

#ifdef NEWDWARF
long instr_count = -1;
#endif

/* XXX: rename to out_open ? */
int
outinit(char *intermed)
{
	fpout = fopen(intermed, "w");
	return fpout != NULL;
}

void
out_close(void)
{
	if (fclose(fpout) == EOF) {
		failer("out_close: fclose error");
		exit(EXIT_FAILURE);
	}
}

/*
 * XXX: break fpout encapsulation.
 * This ugly hack seems currently to be necessary for inserting
 * stabs debug information until the stabs mechanism is fixed
 * properly.
 */
FILE *
out_get_stream(void)
{
	return fpout;
}

void
outc(char c)
{
	int st;

	st = fputc(c, fpout);
	if (st == EOF) {
		failer(BAD_OUTPUT);
		exit(EXIT_FAILURE);
	}
}

void
outs(char *s)
{
	int st;

	st = fputs(s, fpout);
	if (st == EOF) {
		failer(BAD_OUTPUT);
		exit(EXIT_FAILURE);
	}
}

void
out_comment(void)
{
	switch (assembler) {
	case ASM_SUN:
		outc('/');
		break;

	case ASM_GAS:
		/* Add a whitespace in front, otherwise gas might interpret this as
		 * a special instruction */
		outs(" #");
		break;
	}
}

void
outnl(void)
{
	int st;

	st = fputs("\n", fpout);
	if (st == EOF) {
		failer(BAD_OUTPUT);
		exit(EXIT_FAILURE);
	}

	/* XXX: is out.c the right place? */
#ifdef NEWDWARF
	instr_count = -1;
#endif
	last_jump_label = -1;
	keep_short = cpu & CPU_80586;
}

void
outn(long n)
{
	int st;

	st = fprintf(fpout, "%ld", n);
	if (st == EOF) {
		failer(BAD_OUTPUT);
		exit(EXIT_FAILURE);
	}
}

void
outhex(int n)
{
	int st;

	st = fprintf(fpout, "0x%x",(unsigned int)n);
	if (st == EOF) {
		failer(BAD_OUTPUT);
		exit(EXIT_FAILURE);
	}
}

/*
 * Return the current position in bytes
 */
long
out_tell_pos(void)
{
	long p;

	if ((p = ftell(fpout)) == -1L) {
		failer("out_tell_pos: ftell error");
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
	if (fseek(fpout, pos, SEEK_SET) == -1) {
		failer("out_set_pos: fseek error");
		exit(EXIT_FAILURE);
	}
}
