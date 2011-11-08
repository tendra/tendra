/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/

/* Low level output routines */


#include "config.h"
#include "basicread.h"
#include "flags.h"
#include "localflags.h"
#include "instr.h"
#include "messages_8.h"
#include "out.h"

#ifdef NEWDWARF
#include "dw2_config.h"
#endif

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
#ifdef as_comment_symbol
	outc(as_comment_symbol);
#else
	/* Add a whitespace in front, otherwise gas might interpret this as
	 * a special instruction */
	outs(" #");
#endif
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
	keep_short = is80586;
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
