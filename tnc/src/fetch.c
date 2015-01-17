/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <limits.h>

#include "config.h"
#include "file.h"
#include "types.h"
#include "fetch.h"
#include "utility.h"


static long bytes_read = 0;
static unsigned int bits_in_buff = 0;
static unsigned long input_buff = 0;


void
byte_align(void)
{
	bits_in_buff = 0;
}


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


long
tell_posn(void)
{
	return CHAR_BIT * bytes_read - (long)bits_in_buff;
}


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


void
input_skip(long n)
{
	if (n <= 4 * CHAR_BIT)
		(void) fetch((int)n);
	else
		seek_posn(tell_posn() + n);
}
