/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/*
 * Define the low level output routines.
 */

#include "config.h"
#include "msgcat.h"

#include "common_types.h"
#include "basicread.h"
#include "flags.h"
#include "localflags.h"
#include "instr.h"
#include "messages_8.h"
#include "out.h"

#ifdef NEWDWARF
#include "dw2_config.h"
#endif


/* VARIABLES */
/* All variables initialised */

FILE * fpout;	/* init by outinit */
static char *out_fname;

#ifdef NEWDWARF
long instr_count = -1;
#endif


/* PROCEDURES */

int
outinit(char *intermed)
{
	out_fname = intermed;
	fpout = fopen (intermed, "w");
	return (fpout != (FILE *) 0);
}

void
outc(char c)
{
	int   st = fputc (c, fpout);
	if (st == EOF)
		MSG_file_write_error(out_fname);
}

void
outs(char *s)
{
	int   st = fputs (s, fpout);

	if (st == EOF)
		MSG_file_write_error(out_fname);
}

void
outnl()
{

	int   st = fputs ("\n", fpout);

	if (st == EOF)
		MSG_file_write_error(out_fname);

#ifdef NEWDWARF
	instr_count = -1;
#endif
	last_jump_label = -1;
	keep_short = is80586;
	return;
}

void
outn(long n)
{
	int   st = fprintf (fpout, "%ld", n);

	if (st == EOF)
		MSG_file_write_error(out_fname);
}

void
outhex(int n)
{
	int   st = fprintf (fpout, "0x%x", (unsigned int)n);

	if (st == EOF)
		MSG_file_write_error(out_fname);
}
