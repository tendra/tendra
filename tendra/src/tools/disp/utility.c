/*
 * Copyright (c) 2002, 2003, 2004 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * This code is derived from software contributed to The TenDRA Project by
 * Jeroen Ruigrok van der Werven.
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


#include "config.h"
#if FS_STDARG
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include "types.h"
#include "file.h"
#include "pretty.h"
#include "utility.h"


/*
    PROGRAM NAME

    The program name is output in all error reports.
*/

char *progname = "disp";


/*
    EXIT STATUS

    This flag is set to 1 whenever an error occurs.  It is the value
    with which the program finally exits.
*/

int exit_status = EXIT_SUCCESS;


/*
    RECOVERY FLAG

    This flag controls whether an attempt is made to recover from
    non-fatal errors.  Anything after an error is likely to be of very
    little use.
*/

int recover = 0;


/*
    REPORT A FATAL ERROR

    An error is reported and the program aborts immediately.
*/

void
fatal_error(char *s, ...) /* VARARGS */
{
    va_list args;
#if FS_STDARG
    va_start(args, s);
#else
    char *s;
    va_start(args);
    s = va_arg(args, char *);
#endif
    if (progname)IGNORE fprintf(stderr, "%s: ", progname);
    IGNORE fprintf(stderr, "Error: ");
    IGNORE vfprintf(stderr, s, args);
    IGNORE fprintf(stderr, ".\n");
    va_end(args);
    exit(EXIT_FAILURE);
}


/*
    REPORT AN INPUT ERROR

    An error is reported together with the position within the input
    file where it occured, and the program either attempts to recover
    (if the recover flag is true) or outputs what it has read so far
    and then exits (otherwise).
*/

void
input_error(char *s, ...) /* VARARGS */
{
    va_list args;
    long b = here.byte;
#if FS_STDARG
    va_start(args, s);
#else
    char *s;
    va_start(args);
    s = va_arg(args, char *);
#endif
    if (progname)IGNORE fprintf(stderr, "%s: ", progname);
    IGNORE fprintf(stderr, "Error: ");
    IGNORE vfprintf(stderr, s, args);
    IGNORE fprintf(stderr, ", byte %ld, bit %d.\n", b, here.bit);
    va_end(args);
    exit_status = EXIT_FAILURE;
    if (!recover) {
	pretty_tree();
	exit(EXIT_FAILURE);
    }
    return;
}


/*
    ALLOCATE A SECTION OF MEMORY

    This routine allocates n bytes of memory.
*/

pointer
xalloc(int n)
{
    pointer ptr = (pointer)malloc((size_t)n);
    if (ptr == null)fatal_error("Memory allocation error");
    return(ptr);
}


/*
    REALLOCATE A SECTION OF MEMORY

    This routine reallocates n bytes of memory.
*/

pointer
xrealloc(pointer p, int n)
{
    pointer ptr;
    if (p == null) return(xalloc(n));
    ptr = (pointer)realloc(p,(size_t)n);
    if (ptr == null)fatal_error("Memory allocation error");
    return(ptr);
}
