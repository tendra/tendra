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

#include "config.h"
#include "file.h"
#include "types.h"
#include "fetch.h"
#include "utility.h"


/*
    CURRENT FILE POINTER

    As they are read from the input file bits are stored in input_buff.
    The current number of bits in the buffer is bits_in_buff.  bytes_read
    records the position in the input file.
*/

static long bytes_read = 0;
static unsigned int bits_in_buff = 0;
static unsigned long input_buff = 0;


/*
    ALIGN TO NEXT BYTE BOUNDARY

    Any bits remaining in the current byte are ignored.
*/

void
byte_align(void)
{
	bits_in_buff = 0;
}


/*
    FETCH A NUMBER OF BITS

    This routine reads the next n bits from the input file and returns
    them as a long.
*/

long
fetch(int n)
{
	unsigned long s;
	unsigned long r = 0;
	unsigned int b = (unsigned int) n;

	while (b) {
		unsigned int m;

		if (bits_in_buff == 0) {
			int c = getc(input);

			bytes_read++;

			if (c == EOF) {
				input_error("Premature end of file");
				c = 0xff;
			}

			bits_in_buff = CHAR_BIT;
			input_buff = (unsigned long)(c & 0xff);
		}

		m = (b <= bits_in_buff ? b : bits_in_buff);
		s = (input_buff << m);
		r = ((r << m) | ((s >> CHAR_BIT) & 0xff));
		b -= m;
		bits_in_buff -= m;
		input_buff = (s & 0xff);
	}
	return (long)r;
}


/*
 * Rewind the internal state of fetch() to the beginning of a file
 */
void
rewind_posn(void)
{
	bits_in_buff = 0;
	bytes_read = 0;
}


/*
    FIND CURRENT POSITION IN FILE

    The current position in the input file (in bits) is returned.
*/

long
tell_posn(void)
{
	return CHAR_BIT * bytes_read - (long)bits_in_buff;
}


/*
    GO TO A POSITION IN FILE

    The position in the input file is set to the nth bit.
*/

void
seek_posn(long n)
{
	int b = (int)(n % CHAR_BIT);

	bytes_read = n / CHAR_BIT;
	bits_in_buff = 0;

	if (fseek(input, bytes_read, SEEK_SET)) {
		bits_in_buff = (unsigned)b;
		input_error("Illegal seek command");
		return;
	}

	if (b)
		(void) fetch(b);
}


/*
    SKIP A NUMBER OF BITS

    The next n bits in the input file are ignored.
*/

void
input_skip(long n)
{
	if (n <= 4 * CHAR_BIT)
		(void) fetch((int)n);
	else
		seek_posn(tell_posn() + n);
}
