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

#include <stdio.h>
#include <string.h>

#define calculus_IO_ROUTINES
#include "read.h"
#include "calculus.h"
#include "common.h"
#include "shared/error.h"
#include "write.h"


/*
 * OUTPUT FILE
 *
 * These variables describe the output file.  There is a one byte output
 * buffer.
 */

static FILE *output_file;
static unsigned long output_buff = 0;
static int output_bits = 0;


/*
 * WRITE A NUMBER OF BITS
 *
 * This routine writes the value v into n bits.
 */

static void
write_bits(int n, unsigned long v)
{
    if (n > CHAR_BIT) {
	write_bits(n - CHAR_BIT,(v >> CHAR_BIT));
	write_bits(CHAR_BIT,(v & (unsigned)MASK(CHAR_BIT)));
    } else {
	int b = output_bits + n;
	unsigned long m = (output_buff << n) | v;
	int c = b - CHAR_BIT;
	if (c >= 0) {
	    /* Write next byte */
	    int p = (int)(m >> c);
	    fputc(p, output_file);
	    m &= bitmask[c];
	    b = c;
	}
	output_bits = b;
	output_buff = m;
    }
    return;
}


/*
 * WRITE AN INTEGER
 *
 * This routine writes the integer n to the output file.  This is
 * encoded as a sequence of octal digits, plus a flag to indicate the
 * last digit.  The variable d is used to indicate whether this last
 * digit marker should be output.  The normal method of accessing the
 * routine is via the macro write_int.
 */

static void
write_int_aux(unsigned long n, unsigned long d)
{
    unsigned long m = (n >> 3);
    if (m) {
	    write_int_aux(m,(unsigned long)0x00);
    }
    write_bits(4,((n & 0x07) | d));
    return;
}

#define write_int(N)	write_int_aux((N), (unsigned long)0x08)


/*
 * WRITE A STRING
 *
 * This routine writes the string s to the output file.  This is
 * encoded as the string length followed by the component characters
 * (8 bits each).
 */

static void
write_string(char *s)
{
    unsigned long i, n = (unsigned long)strlen(s);
    write_int(n);
    for (i = 0; i < n; i++) {
	write_bits(8,(unsigned long)s[i]);
    }
    return;
}


/*
 * LAST FILE NAME WRITTEN
 *
 * This variable is used to store the last file name written.
 */

static char *last_filename = NULL;


/*
 * WRITE A FILE NAME
 *
 * This routine writes the file name s.  This is just a simple string,
 * but file names are buffered using last_filename.
 */

static void
write_filename(char *s)
{
    char *t = last_filename;
    if (t && !strcmp(t, s)) {
	write_bits(1,(unsigned long)1);
    } else {
	write_bits(1,(unsigned long)0);
	write_string(s);
	last_filename = s;
    }
    return;
}


/*
 * AUTOMATICALLY GENERATED DISK WRITING ROUTINES
 *
 * The main disk writing routines are automatically generated.  The
 * various macros are used to customise these routines.
 */

#define WRITE_BITS(A, B)	write_bits((A), (unsigned long)(B))
#define WRITE_ALIAS(A)		write_int((unsigned long)(A))
#define WRITE_DIM(A)		write_int((unsigned long)(A))
#define WRITE_int(A)		write_int((unsigned long)(A))
#define WRITE_number(A)		write_int((unsigned long)(A))
#define WRITE_string(A)		write_string(A)
#define WRITE_name_string(A)	write_filename(A)
#define WRITE_zero_int(A)	/* UNUSED(A) */
#define crt_disk_alias		crt_calculus_alias

#include "write_def.h"


/*
 * WRITE A FILE
 *
 * This routine writes the current algebra to disk into the file nm.
 */

void
write_file(char *nm)
{
    /* Open file */
    if (!strcmp(nm, ".")) {
	error(ERROR_SERIOUS, "Output file not specified");
	return;
    }
    output_file = fopen(nm, "wb");
    if (output_file == NULL) {
	error(ERROR_SERIOUS, "Can't open output file, '%s'", nm);
	return;
    }
    init_bitmask();
    output_buff = 0;
    output_bits = 0;
    last_filename = NULL;

    /* Write the file header */
    WRITE_string(calculus_NAME);
    WRITE_string(calculus_VERSION);

    /* Write the algebra */
    WRITE_string(algebra->name);
    WRITE_int(algebra->major_no);
    WRITE_int(algebra->minor_no);
    WRITE_list_ptr_type(algebra->types);

    /* Close file */
    if (output_bits) {
	/* Tidy up any odd bits */
	write_bits(CHAR_BIT - output_bits,(unsigned long)0);
    }
    clear_calculus_alias();
    fclose(output_file);
    return;
}
