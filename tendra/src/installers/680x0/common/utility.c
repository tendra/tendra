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
 *    		 Crown Copyright (c) 1996
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
#include "tenapp.h"

#if FS_STDARG
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include "common_types.h"
#include "basicread.h"
#include "instrs.h"
#include "utility.h"
extern long crt_line_num;
extern char *crt_fname;


/*
 *    FIND THE BASENAME OF A FILE
 *
 *    The string nm is analysed and a pointer to the character after the
 *    last '/' is returned.
 */

char
*basename(char *nm)
{
    char *bn = nm;
    for (; *nm ; nm++) if (*nm == '/') bn = nm + 1;
    return (bn);
}


/*
 *    FIND THE FIRST NONZERO BIT
 *
 *    This routine returns the bit number of the least significant set
 *    bit in n.  For 0 it returns -1.
 */

int
bit_one(bitpattern n)
{
    int c = 0;
    bitpattern m;
    for (m = n ; m ; m >>= 1, c++) if (m & 1) return (c);
    return (-1);
}


/*
 *    FIND THE NUMBER OF SET BITS
 *
 *    The number of set bits in n is returned.
 */

int
bits_in(bitpattern n)
{
    /* Table of bits in : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F */
    static int b [16] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };
    int c = 0;
    while (n) {
		c += b [ n & 0xf ];
		n >>= 4;
    }
    return (c);
}


/*
 *    BIT PATTERNS
 *
 *    lo_bits [n] is the number with its bottom n bits set and the rest
 *    zero.  hi_bits [n] is the number with its top n bits set and the rest
 *    zero.
 */

bitpattern lo_bits [] = { 0,
						  0x00000001, 0x00000003, 0x00000007, 0x0000000f,
						  0x0000001f, 0x0000003f, 0x0000007f, 0x000000ff,
						  0x000001ff, 0x000003ff, 0x000007ff, 0x00000fff,
						  0x00001fff, 0x00003fff, 0x00007fff, 0x0000ffff,
						  0x0001ffff, 0x0003ffff, 0x0007ffff, 0x000fffff,
						  0x001fffff, 0x003fffff, 0x007fffff, 0x00ffffff,
						  0x01ffffff, 0x03ffffff, 0x07ffffff, 0x0fffffff,
						  0x1fffffff, 0x3fffffff, 0x7fffffff, 0xffffffff };

bitpattern hi_bits [] = { 0,
						  0x80000000, 0xc0000000, 0xe0000000, 0xf0000000,
						  0xf8000000, 0xfc000000, 0xfe000000, 0xff000000,
						  0xff800000, 0xffc00000, 0xffe00000, 0xfff00000,
						  0xfff80000, 0xfffc0000, 0xfffe0000, 0xffff0000,
						  0xffff8000, 0xffffc000, 0xffffe000, 0xfffff000,
						  0xfffff800, 0xfffffc00, 0xfffffe00, 0xffffff00,
						  0xffffff80, 0xffffffc0, 0xffffffe0, 0xfffffff0,
						  0xfffffff8, 0xfffffffc, 0xfffffffe, 0xffffffff };


/*
 *    NUMBER OF ERRORS
 *
 *    errors is the number of errors which have occurred.  max_errors is
 *    the maximum number of errors that will be tolerated before exiting.
 */

int errors = 0;
#ifdef EBUG
int max_errors = 10;
#else
int max_errors = 1;
#endif


/*
 *    PRINT AN ERROR REPORT
 *
 *    This routine prints the error report s together with any additional
 *    arguments.
 */

void
error(char *s, ...)
{
    char c;
    char *p;
    va_list args;
#if FS_STDARG
    va_start (args, s);
    p = s;
#else
    va_start (args);
    p = va_arg (args, char *);
#endif
    if (progname) fprintf (stderr, "%s : ", progname);
    fprintf (stderr, "Error : ");
    c = *p;
    if (c >= 'a' && c <= 'z') {
		c += ('A' - 'a');
		fputc (c, stderr);
		p++;
    }
    vfprintf (stderr, p, args);
    if (crt_line_num != -1 && crt_fname) {
		fprintf (stderr, ", %s, line %ld", crt_fname, crt_line_num);
    }
    fprintf (stderr, ".\n");
    va_end (args);
#ifdef IGNORE_ERRORS
    return;
#endif
    if (max_errors == 0) exit (EXIT_FAILURE);
    if (++errors > max_errors) {
		fprintf (stderr, "%s : Too many errors.\n", progname);
		exit (EXIT_FAILURE);
    }
    return;
}

#if 0
/*
 *    PRINT A SIMPLE ERROR
 *
 *    This routine prints the simple error report s.
 */

void
failer(char *s)
{
    error (s);
    return;
}
#endif


/*
 *    PRINT A WARNING
 *
 *    This routine prints the warning message s together with any additional
 *    arguments.
 */

void
warning(char *s, ...)
{
    char c;
    char *p;
    va_list args;
#if FS_STDARG
    va_start (args, s);
    p = s;
#else
    va_start (args);
    p = va_arg (args, char *);
#endif
    if (progname) (void) fprintf (stderr, "%s : ", progname);
    fprintf (stderr, "Warning : ");
    c = *p;
    if (c >= 'a' && c <= 'z') {
		c += ('A' - 'a');
		fputc (c, stderr);
		p++;
    }
    (void) vfprintf (stderr, p, args);
    (void) fprintf (stderr, ".\n");
    va_end (args);
    return;
}


