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

#include "common_types.h"
#include "flags.h"
#include "messages_r.h"
#include "natmacs.h"
#include "readglob.h"
#include "flpt.h"
#include "f64.h"
#include "installglob.h"

#include "basicread.h"

/* VARIABLES */

struct tdf_stream *tdfr;


static char *crt_dot_t;	/* initialised by init_reader */
int  crt_lno;		/* initialised to -1 by init_reader */
int crt_charno;		/* only used if crt_lno != -1. No init needed */
char * crt_flnm;	/* only used if crt_lno != -1. No init needed */

static int  failer_count;	/* initialised by init_reader */
/* number of failures so far. To allow for
 *				   limiting error messages */
static tdf_pos bytestream_pickup;	/* set before use */
/* records the end of a bytestream */



/**********************************************************************
 *   failer prints an error message on the standard output, and sets
 *   good_trans to 1 to indicate an error.
 **********************************************************************/

/* fails, giving error message s */
void
failer(char *s)
{
	
	good_trans = 1;
	if (crt_lno != -1)
		IGNORE fprintf (stderr, "trans:%s: internal error: after line %d: char %d: %s\n", crt_flnm, crt_lno, crt_charno, s);
	else
		IGNORE fprintf (stderr, "trans:%s: internal error: %s\n", crt_dot_t, s);
	++failer_count;
	if (failer_count >= 15)	/* errors limited to 15 */
		exit(EXIT_FAILURE);
	return;
}


/***************************************************************
 *  initreader opens the file called n and sets initial values
 *  into variables.
 ***************************************************************/
void check_magic_no(void) ;

bool
initreader(char *n)
{
	crt_dot_t = n;
	crt_lno = -1;
	failer_count = 0;

	tdfr = tdf_fstream_create (n);
	if (tdfr == NULL) {
		MSG_cant_open_input_file (n);
		return (0);
	}
	
	check_magic_no();
	return (1);
}

void
endreader()
{
	tdf_stream_destroy (tdfr);
	tdfr = NULL;
}

unsigned long
getcode(unsigned int np)
{
	return tdf_de_bits (tdfr, np);
}

int
get_big_code(unsigned int n)
{
	/* XXX: many places should be examined in order to change int -> ulong */
	return (int)tdf_de_tdfextint (tdfr, n);
}

/********************************************************************
 *   keep_place records the present state of the getcode variables
 *   in a place. It condenses the position variables into the
 *   bits_on field, measured from the start of the recorded line.
 ********************************************************************/

tdf_pos
keep_place()
{
	return tdf_stream_tell (tdfr);
}

/********************************************************************
 *  set_place resets the getcode variables from the place pl, which
 *  was produced by keep_placee. If necessary it reads more
 *  lines from the file.
 ********************************************************************/

void
set_place(tdf_pos pos)
{
	tdf_stream_seek (tdfr, pos);
}


/*********************************************************************
 *  small_dtdfint reads one TDF integer using getcode. TDF integers are
 *  encoded as a number of octal digits, most significant first.
 *  These octal digits are encoded in 4-bit chunks with 8 added on
 *  to the last digit only.
 *********************************************************************/

int
small_dtdfint()
{
	int  digit;
	int total = 0;
	while (digit = getcode (4), digit < 8)
		total = 8 * total + digit;
	return (8 * total + (digit - 8));
}

/* step the input stream on to the next byte boundary */

void
to_boundary()
{
	tdf_de_align (tdfr);
	return;
}


/* delivers a new place for the bitstream in the input stream and steps
 *    over it */

bitstream
d_bitstream()
{
	TDFINTL  length;
	tdf_pos here;

	length = tdf_de_tdfintl (tdfr);
	here = tdf_stream_tell (tdfr);
	tdf_stream_seek (tdfr, here + length);
	return here;
}




bytestream
d_bytestream()
{
	return bytestream_pickup;
}

void
ignore_bytestream()
{
	/* steps over a bytestream */
	TDFINTL length;
	tdf_pos here;

	length = tdf_de_tdfintl (tdfr);
	tdf_de_align (tdfr);
	here = tdf_stream_tell (tdfr);
	tdf_stream_seek (tdfr, here + length * TDF_BYTE_SIZE);
	return;
}

/* records in bytestream_pickup the end of a bytestream */

void
start_bytestream()
{
	TDFINTL length;
	tdf_pos here;

	length = tdf_de_tdfintl (tdfr);
	tdf_de_align (tdfr);
	here = tdf_stream_tell (tdfr);
	bytestream_pickup = here + length * TDF_BYTE_SIZE;
	return;
}


/* resets the input stream from bytestream_pickup */

void
end_bytestream()
{
	tdf_stream_seek (tdfr, bytestream_pickup);
	return;
}

tdfstring
d_tdfstring()
{
	/* reads a tdfstring from the input stream */
	TDFINTL bits, i, n;
	tdfstring tdb;

	bits = tdf_de_tdfintl (tdfr);
	n = tdf_de_tdfintl (tdfr);
	tdb.number = n;
	if (bits <= 8) {
		tdb.ints.chars = (char *) xcalloc (n + 1, sizeof (char));
		for (i = 0; i < n; ++i)
			tdb.ints.chars[i] = (char)getcode (bits);
		tdb.ints.chars[n] = 0;
		tdb.size = 8;
		return tdb;
	};
	if (bits <= 16) {
		tdb.ints.shorts = (short *) xcalloc (n + 1, sizeof (short));
		for (i = 0; i < n; ++i)
			tdb.ints.shorts[i] = (short)getcode (bits);
		tdb.ints.shorts[n] = 0;
		tdb.size = 16;
		return tdb;
	};
	if (bits <= 32) {
		tdb.ints.longs = (long *) xcalloc (n + 1, sizeof (long));
		for (i = 0; i < n; ++i)
			tdb.ints.longs[i] = getcode (bits);
		tdb.ints.longs[n] = 0;
		tdb.size = 32;
		return tdb;
	};
	if (bits <= 64) {
		tdb.ints.longs = (long *) xcalloc (n + 1, sizeof (long));
		for (i = 0; i < n; ++i) {
			flt64 x;
			flpt f;
			x.big = getcode(bits - 32);
			x.small = (unsigned int)getcode(32);
			f = f64_to_flt(x, 0);
			tdb.ints.longs[i] = f;
		};
		tdb.ints.longs[n] = 0;
		tdb.size = 64;
		return tdb;
	};
	failer(NO_BIG_STRINGS);
	return tdb;
}

tdfstring
d_tdfident()
{
	tdfstring tdb;

	tdf_de_tdfident (tdfr, &tdb);
	return tdb;
}

tdfbool
d_tdfbool()
{
	/* reads a tdfbool from the input stream */
	return (tdfbool)tdf_de_tdfbool (tdfr);
}



tdfint
d_tdfint()
{
	/* reads a tdfint from the input stream */
	nat n;
	unsigned int  digit;
	unsigned int total = 0;
	int  small = 1;
	int goon = 1;
	flpt f;
	
	while (goon)
	{
		digit = (unsigned int)getcode(4);
		if (digit >= 8)
		{ goon = 0;
		digit -= 8;
		};
		if (small)
		{ if (total > 0x1fffffff)
		{ small = 0;
		f = floatrep_unsigned(total);
		flpt_newdig(digit, &flptnos[f], 8);
		}
		else
			total = (total << 3) + digit;
		}
		else {
			SET(f);
			flpt_newdig(digit, &flptnos[f], 8);
		};
	};
	nat_issmall(n) = (bool)small;
	if (small)
		natint(n) = (int)total;
	else
	{
		SET(f);
		nat_issmall(n) = 0;
		natbig(n) = f;
	};
	return n;
}

void
check_magic_no()
{
	struct tdf_version v;

	tdf_de_magic (tdfr, tdf_cap_magic);
	tdf_de_make_version (tdfr, &v);
	if (v.major > MAJOR_VERSION) {
		failer("TDF version of capsule is later than version dealt with by translator - update the translator");
		exit(EXIT_FAILURE);
	} else if (v.major < MAJOR_VERSION) {
		failer("TDF version dealt with by translator is later than version of capsule - recompile capsule with later compiler");
		exit(EXIT_FAILURE);
	}
	if (v.minor > MINOR_VERSION) {
	    IGNORE fprintf(stderr, "Warning: capsule may contain constructions not dealt with in this minor version of the translator\n");
	}
	tdf_de_align (tdfr);
}
