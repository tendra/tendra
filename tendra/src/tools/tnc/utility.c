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
#include "cstring.h"
#include "fmm.h"

#include "types.h"
#include "read_types.h"
#include "analyser.h"
#include "file.h"
#include "table.h"
#include "utility.h"
#include "write.h"


/*
 *    ARE INPUT AND OUTPUT TEXT OR CODE?
 *
 *    The form of any error message depends on whether the input file
 *    is text or code.
 */

boolean text_input = 1;
boolean text_output = 0;


/*
 *    MAKE A TEMPORARY COPY OF A STRING
 *
 *    This routine copies a string into a temporary buffer.
 */

char
*temp_copy(char *s)
{
    static char *buff = null;
    static int bufflen = 0;
    int n = (int) strlen (s) + 1;
    if (n >= bufflen) {
		bufflen = n + 100;
		buff = (char *) xrealloc ((pointer) buff, bufflen);
    }
    return (strcpy (buff, s));
}


/*
 *    CONVERT AN UNSIGNED LONG TO OCTAL
 *
 *    The result is returned as a string of octal digits.
 */

char
*ulong_to_octal(unsigned long n)
{
    int i = 99;
    char buff [100];
    if (n == 0) return ("0");
    buff [i] = 0;
    while (n) {
		buff [ --i ] = (char) ('0' + (n & 7));
		n >>= 3;
    }
    return (string_ncopy (buff + i, 99 - i));
}


/*
 *    CONVERT AN OCTAL STRING TO AN UNSIGNED LONG
 *
 *    Any overflow is ignored (but see below).
 */

unsigned long
octal_to_ulong(char *num)
{
    unsigned long n = 0;
    for (; *num ; num++) {
		n = (n << 3) + (unsigned long) (*num - '0');
    }
    return (n);
}


/*
 *    DOES THE GIVEN OCTAL STRING FIT INTO AN UNSIGNED LONG?
 *
 *    The number of binary digits needed to represent the octal number
 *    is calculated and compared against the number of bits in an
 *    unsigned long, minus sz (to allow for a sign bit).
 */

boolean
fits_ulong(char *num, int sz)
{
    int n = 3 * (int) strlen (num);
    int m = BYTESIZE * (int) sizeof (unsigned long) - sz;
    switch (*num) {
	case '0' : n -= 3 ; break;
	case '1' : n -= 2 ; break;
	case '2' : n -= 1 ; break;
	case '3' : n -= 1 ; break;
    }
    if (n <= m) return (1);
    return (0);
}
