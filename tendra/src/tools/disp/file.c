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


#include "config.h"
#include "fmm.h"
#include "msgcat.h"
#include "tdf_types.h"
#include "tdf_stream.h"

#include "types.h"
#include "ascii.h"
#include "file.h"
#include "pretty.h"
#include "tree.h"


/*
 *    INPUT AND OUTPUT FILES AND BUFFERS
 *
 *    The input TDF capsule is read from tdf_file.  The pretty-printed
 *    output is placed into pp_file.  The input uses the buffer
 *    inbuffer.
 */

struct tdf_stream *tdfr;
FILE *pp_file;


/*
 *    INPUT AND OUTPUT VARIABLES
 *
 *    printflag is used to switch the printing on or off.  The present
 *    column number in the output file is given by column.  The maximum
 *    value attained by column is recorded in maximum.  The last character
 *    output is held in lastc.
 */

int printflag = 1;
int column;
int maximum;
int lastc = 0;
BoolT dump = FALSE;


/*
 *    OPEN FILES
 *
 *    The file name1 is opened for input and name2 for output.  If name2
 *    is the null string, the standard output is used.
 */

void
open_files(char *name1, char *name2)
{
	tdfr = tdf_fstream_create (name1);
    if (tdfr == null) MSG_cant_open_input_file (name1);
    if (name2) {
		pp_file = fopen (name2, "w");
		if (pp_file == null) MSG_cant_open_output_file (name2);
    } else {
		pp_file = stdout;
    }
    return;
}


/*
 *    ARRAY OF SPACES
 *
 *    The indentation spaces used during pretty-printing are stored in
 *    an array.
 */

static char *spaces1;


/*
 *    INITIALIZE SPACES
 *
 *    This routine initializes the array of indentation spaces, spaces1.
 */

void
init_spaces(int d)
{
    int i, j;
    if (helpflag) {
		spaces1 = xmalloc_nof (char, 5000);
		/* every dth character should be a '.' */
		for (i = 0, j = 0 ; i < 5000 ; i++) {
			if (++j == d) {
				spaces1 [i] = '.';
				j = 0;
			} else {
				spaces1 [i] = ' ';
			}
		}
    }
    return;
}


/*
 *    OUTPUT n SPACES
 *
 *    This routine outputs n indentation spaces, using the array spaces1
 *    when appropriate.
 */

void
spaces(int n)
{
    if (n < 0) n = 0;
    if (printflag) {
		if (helpflag) {
			if (n) {
				IGNORE fwrite (spaces1, sizeof (char),
							   (size_t) n, pp_file);
			}
		} else {
			int i;
			int q = (n / TBSIZE);
			int r = (n % TBSIZE);
			for (i = 0 ; i < q ; i++) IGNORE fputc (TAB, pp_file);
			for (i = 0 ; i < r ; i++) IGNORE fputc (SPACE, pp_file);
		}
    }
    column = n;
    lastc = ' ';
    return;
}
