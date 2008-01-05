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


#include <limits.h>
#include <stdarg.h>

#include "config.h"
#include "types.h"
#include "read_types.h"
#include "analyser.h"
#include "fetch.h"
#include "file.h"
#include "table.h"
#include "utility.h"
#include "write.h"

extern char *progname;
extern char *capname;
extern int decode_status;
extern int have_version;


/*
    ARE INPUT AND OUTPUT TEXT OR CODE?

    The form of any error message depends on whether the input file
    is text or code.
*/

boolean text_input = 1;
boolean text_output = 0;


/*
    EXIT STATUS

    The overall exit status of the program.
*/

int exit_status = EXIT_SUCCESS;


/*
    IS AN INPUT ERROR FATAL?

    Not all input errors cause an immediate exit.  These should set
    is_fatal to false before calling input_error.
*/

boolean is_fatal = 1;


/*
    REPORT A FATAL ERROR

    The error s is reported and the program exits.
*/

void
fatal_error(char *s, ...)
{
	va_list args;

	va_start(args, s);

	if (progname)
		(void) fprintf(stderr, "%s: ", progname);
	(void) fprintf(stderr, "Error: ");
	(void) vfprintf(stderr, s, args);
	(void) fprintf(stderr, ".\n");

	va_end(args);

	exit(EXIT_FAILURE);
}


/*
    REPORT AN INPUT ERROR

    The input error s is reported and the program exits.
*/

void
input_error(char *s, ...)
{
	va_list args;

	va_start(args, s);

	if (progname)
		(void) fprintf(stderr, "%s: ", progname);
	(void) fprintf(stderr, "Error: ");
	(void) vfprintf(stderr, s, args);

	if (input_file) {
		(void) fprintf(stderr, ", %s", input_file);

		if (text_input)
			(void) fprintf(stderr, ", line %ld", line_no);
		else {
			long b = input_posn();

			if (capname) {
				(void) fprintf(stderr, ", capsule %s", capname);
			}

			switch (decode_status) {
			case 0:
				(void) fprintf(stderr, " (at outermost level)");
				break;
			case 1:
				(void) fprintf(stderr, " (in linking information)");
				break;
			case 2:
				(void) fprintf(stderr, " (in unit body)");
				break;
			}

			(void) fprintf(stderr, ", byte %ld, bit %ld", b / 8, b % 8);

			if (decode_status == 0)
				(void) fprintf(stderr, " (Illegal TDF capsule?)");

			if (decode_status >= 1 && !have_version)
				(void) fprintf(stderr, " (TDF version error?)");
		}
	}

	(void) fprintf(stderr, ".\n");

	va_end(args);

	if (is_fatal) {
		if (text_output) {
			sort_all();
			print_capsule();
			(void) fputs("# TERMINATED ON INPUT ERROR\n", output);
		}

		exit(EXIT_FAILURE);
	}

	is_fatal = 1;
	exit_status = EXIT_FAILURE;
}


/*
    ISSUE A WARNING

    The warning message s is printed.
*/

void
warning(char *s, ...)
{
	va_list args;

	va_start(args, s);

	if (progname)
		(void) fprintf(stderr, "%s: ", progname);
	(void) fprintf(stderr, "Warning: ");
	(void) vfprintf(stderr, s, args);
	(void) fprintf(stderr, ".\n");

	va_end(args);
}


/*
    ALLOCATE A SECTION OF MEMORY

    This routine allocates n bytes of memory.
*/

void *
xalloc(int n)
{
	void *ptr;

	if (n == 0)
		return (NULL);

	ptr = malloc(n);
	if (ptr == NULL) {
		if (!text_input && decode_status == 0)
			fatal_error("Memory allocation error (Illegal TDF capsule?)");

		fatal_error("Memory allocation error");
	}

	return (ptr);
}


/*
    REALLOCATE A SECTION OF MEMORY

    This routine reallocates n bytes of memory for the pointer p.
*/

void *
xrealloc(void *p, int n)
{
	void *ptr;

	if (n == 0)
		return (NULL);

	if (p == NULL)
		return (xalloc(n));

	ptr = realloc(p, n);
	if (ptr == NULL)
		fatal_error("Memory allocation error");

	return (ptr);
}


/*
    MAKE A COPY OF A STRING

    This routine makes a permanent copy of the string s of length n.
*/

char *
string_copy(char *s, int n)
{
	char *p;

	p = xalloc(n+1);

	(void) strncpy(p, s, n);
	p[n] = '\0';

	return(p);
}


/*
    MAKE A TEMPORARY COPY OF A STRING

    This routine copies a string into a temporary buffer.
*/

char *
temp_copy(char *s)
{
	static char *buff = NULL;
	static int bufflen = 0;
	int n = strlen(s) + 1;

	if (n >= bufflen) {
		bufflen = n + 100;
		buff = xrealloc(buff, bufflen);
	}

	(void) strcpy(buff, s);

	return (buff);
}


/*
    CONVERT AN UNSIGNED LONG TO OCTAL

    The result is returned as a string of octal digits.
*/

char *
ulong_to_octal(unsigned long n)
{
	int i = 99;
	char buff[100];

	if (n == 0)
		return ("0");

	buff[i] = 0;
	while (n) {
		buff[--i] = (char)('0' + (n & 7));
		n >>= 3;
	}

	return(string_copy(buff + i, 99 - i));
}


/*
    CONVERT AN OCTAL STRING TO AN UNSIGNED LONG

    Any overflow is ignored (but see below).
*/

unsigned long
octal_to_ulong(char *num)
{
	unsigned long n = 0;

	for (; *num; num++)
		n = (n << 3) + (unsigned long)(*num - '0');

	return (n);
}


/*
    DOES THE GIVEN OCTAL STRING FIT INTO AN UNSIGNED LONG?

    The number of binary digits needed to represent the octal number
    is calculated and compared against the number of bits in an
    unsigned long, minus sz (to allow for a sign bit).
*/

boolean
fits_ulong(char *num, int sz)
{
	int n = 3 * strlen(num);
	int m = CHAR_BIT * sizeof(unsigned long) - sz;

	switch (*num) {
	case '0': n -= 3; break;
	case '1': n -= 2; break;
	case '2': n -= 1; break;
	case '3': n -= 1; break;
	}

	if (n <= m)
		return (1);

	return (0);
}
