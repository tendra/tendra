/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
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


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$
 *$Log$
 *Revision 1.2  2002/11/21 22:31:06  nonce
 *Remove ossg prototypes.  This commit is largely whitespace changes,
 *but is nonetheless important.  Here's why.
 *
 *I.  Background
 *=========================
 *
 *    The current TenDRA-4.1.2 source tree uses "ossg" prototype
 *conventions, based on the Open Systems Software Group publication "C
 *Coding Standards", DRA/CIS(SE2)/WI/94/57/2.0 (OSSG internal document).
 *The goal behind ossg prototypes remains admirable: TenDRA should
 *support platforms that lack ANSI compliant compilers.  The explicit
 *nature of ossg's prototypes makes macro substition easy.
 *
 *    Here's an example of one function:
 *
 *    static void uop
 *	PROTO_N ( ( op, sha, a, dest, stack ) )
 *	PROTO_T ( void ( *op ) PROTO_S ( ( shape, where, where ) ) X
 *		  shape sha X exp a X where dest X ash stack )
 *    {
 *
 *tendra/src/installers/680x0/common/codec.c
 *
 *  The reasons for removing ossg are several, including:
 *
 *  0) Variables called 'X' present a problem (besides being a poor
 *variable name).
 *
 *  1) Few platforms lack ANSI-compliant compilers.  ISO-compliant
 *prototypes are easily handled by most every compiler these days.
 *
 *  2) Although TenDRA emphasizes portability, standards compliance is
 *the primary goal of the current project.  We should expect no less
 *from the compiler source code.
 *
 *  3) The benefits of complex prototypes are few, given parameter
 *promotion rules.  (Additionally, packing more types into int-sized
 *spaces tends to diminish type safety, and greatly complicates
 *debugging and testing.)
 *
 *  4) It would prove impractical to use an OSSG internal style document
 *in an open source project.
 *
 *  5) Quite frankly, ossg prototypes are difficult to read, but that's
 *certainly a matter of taste and conditioning.
 *
 *II.  Changes
 *=========================
 *
 *   This commit touches most every .h and .c file in the tendra source
 *tree.  An emacs lisp script (http://www.tendra.org/~nonce/tendra/rmossg.el)
 *was used to automate the following changes:
 *
 *   A.  Prototype Conversions.
 *   --------------------------------------------------
 *
 *   The PROTO_S, PROTO_Z, PROTO_N, PROTO_T, and PROTO_V macros were
 *rewritten to ISO-compliant form.  Not every file was touched.  The
 *files named ossg.h, ossg_api.h, code.c, coder.c and ossg_std.h were
 *left for hand editing.  These files provide header generation, or have
 *non-ossg compliant headers to start with.  Scripting around these
 *would take too much time; a separate hand edit will fix them.
 *
 *   B.  Statement Spacing
 *   --------------------------------------------------
 *
 *   Most of the code in the TenDRA-4.1.2 used extra spaces to separate
 *parenthetical lexemes.  (See the quoted example above.)  A simple
 *text substitution was made for:
 *
 *     Before            After
 *===================================
 *
 *   if ( x )            if (x)
 *   if(x)               if (x)
 *   x = 5 ;             x = 5;
 *   ... x) )            ... x))
 *
 *All of these changes are suggested by style(9).  Additional, statement
 *spacing considerations were made for all of the style(9) keywords:
 *"if" "while" "for" "return" "switch".
 *
 *A few files seem to have too few spaces around operators, e.g.:
 *
 *      arg1*arg2
 *
 *instead of
 *
 *      arg1 * arg2
 *
 *These were left for hand edits and later commits, since few files
 *needed these changes.  (At present, the rmossg.el script takes 1 hour
 *to run on a 2GHz P4, using a ramdisk.  Screening for the 1% that
 *needed change would take too much time.)
 *
 *   C.  License Information
 *   --------------------------------------------------
 *
 *After useful discussion on IRC, the following license changes were
 *made:
 *
 *   1) Absent support for $License::BSD$ in the repository, license
 *and copyright information was added to each file.
 *
 *   2) Each file begins with:
 *
 *   Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 *   All rights reserved.
 *
 *   Usually, copyright stays with the author of the code; however, I
 *feel very strongly that this is a group effort, and so the tendra
 *project should claim any new (c) interest.
 *
 *   3) The comment field then shows the bsd license and warranty
 *
 *   4) The comment field then shows the Crown Copyright, since our
 *changes are not yet extensive enough to claim any different.
 *
 *   5) The comment field then closes with the $TenDRA$ tag.
 *
 *   D.  Comment Formatting
 *   --------------------------------------------------
 *
 *The TenDRA-4.1.2 code base tended to use comment in this form:
 *
 *    /*
 *       Statement statement
 *       statement
 *     */
 *
 *while style(9) suggests:
 *
 *    /*
 *     * Statement statement
 *     * statement
 *     */
 *
 *Not every comment in -4.1.2 needed changing.  A parser was written to
 *identify non-compliant comments.  Note that a few comments do not
 *follow either the TenDRA-4.1.2 style or style(9), or any style I can
 *recognize.  These need hand fixing.
 *
 *   E.  Indentation
 *   --------------------------------------------------
 *
 *   A elisp tendra-c-mode was created to define how code should be
 *indented.  The structure follows style(9) in the following regards:
 *
 *  (c-set-offset 'substatement-open 0)
 *  (setq c-indent-tabs-mode t
 *	c-indent-level 4
 *	c-argdecl-indent t
 *	c-tab-always-indent t
 *	backward-delete-function nil
 *	c-basic-offset 4
 *	tab-width 4))
 *
 *This means that substatement opening are not indented.  E.g.:
 *
 *   if (condition)
 *   {
 *
 *instead of
 *
 *   if (condition)
 *     {
 *
 *or even
 *
 *   if (condition) {
 *
 *Each statement is indented by a tab instead of a spaces.  Set your tab
 *stop to comply with style(9); see the vim resources in the tendra
 *tree.  I'll add the emacs mode support shortly.
 *
 *No doubt, a function or two escaped change because of unusual
 *circumstances.  These must be hand fixed as well.
 *
 *III.  Things Not Changed
 *=========================
 *
 *    A large number of style(9) deficiencies remain.  These will
 *require a separate effort.  I decided to stop with the changes noted
 *above because:
 *
 *   0)  The script currently takes hours to run to completion even on
 *high-end consumer machines.
 *
 *   1)  We need to move on and fix other substantive problems.
 *
 *   2) The goal of this commit was *just* ossg removal; I took the
 *opportunity to get other major white-space issues out of the way.
 *
 *    I'll also note that despite this commit, a few ossg issues remain.
 *These include:
 *
 *   0) The ossg headers remain.  They contain useful flags needed by
 *other operations.  Additionally, the BUILD_ERRORS perl script still
 *generates ossg-compliant headers.  (This is being removed as we change
 *the build process.)
 *
 *   1) A few patches of code check for ossg flags: "if (ossg) etc."
 *These can be hand removed as well.
 *
 *   2) No doubt, a few ossg headers escaped the elisp script.  We can
 *address these seriatim.
 *
 *IV.  Testing
 *=========================
 *
 *    Without a complete build or test suite, it's difficult to
 *determine if these changes have introduced any bugs.  I've identified
 *several situations where removal of ossg caused bugs in sid and
 *calculus operations.  The elisp script avoids these situations; we
 *will hand edit a few files.
 *
 *    As is, the changes should behave properly; the source base builds
 *the same before and after the rmossg.el script is run.  Nonetheless,
 *please note that this commit changes over 23,000 PROTO declarations,
 *and countless line changes.  I'll work closely with any developers
 *affected by this change.
 *
 * Revision 1.3  1998/03/11  11:03:50  pwe
 * DWARF optimisation info
 *
 * Revision 1.2  1998/02/04  10:43:39  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1996/06/18  09:21:14  currie
 * C torture long nats
 *
 *Revision 1.2  1995/07/06 09:14:29  currie
 *MAGIC NO

 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
 ***********************************************************************/

#include "config.h"
#include "common_types.h"
#include "xalloc.h"
#include "flags.h"
#include "messages_r.h"
#include "natmacs.h"
#include "readglob.h"
#include "flpt.h"
#include "f64.h"
#include "installglob.h"

#include "basicread.h"

/* MACROS */

#define bpby 8
/* bits per byte */

#define cppkt 256
/* bytes per packet */

#define bppkt (bpby*cppkt)
/* the number of bits per packet (from the file). */


/* VARIABLES */
/* All variables are initialised, jmf */

static char * crt_ptr;	/* initialised by init_reader */
static char * end_ptr;	/* initialised by init_reader */

static int getcode_bitposn;
static union pun_u
{unsigned int intc;
    struct pun_s {char a; char b; char c; char d;} chars;
} crt_bits;		/* set before use */



static char *crt_dot_t;	/* initialised by init_reader */
int  crt_lno;		/* initialised to -1 by init_reader */
int crt_charno;		/* only used if crt_lno != -1. No init needed */
char * crt_flnm;	/* only used if crt_lno != -1. No init needed */
static int  failer_count;	/* initialised by init_reader */
/* number of failures so far. To allow for
 *				   limiting error messages */
static int   pkt_index;	/* initialised by init_reader */
/* the index of the current packet in the
 *				   file */
static int table_flag;	/* initialised by init_reader */
/* 1 if reading from memory, 0 if reading
 *				   from file buffer */
static char *crt_line;	/* set before use */
/* current line of encoding */
static int   file_pkt;	/* initialised by init_reader */
/* holds the index of the packet in the
 *				   file */
static FILE * fpin;	/* initialised by init_reader */
/* file pointer for input */
static int  buff[64];	/* set by read_line */
/* file buffer for input */
static place current_place;	/* set before use */
static place bytestream_pickup;	/* set before use */
/* records the end of a bytestream */




/* IDENTITIES */

static unsigned int  mask[33] = {
	0, 1, 3, 7, 15, 31, 63, 127, 255,
	0x1ff, 0x3ff, 0x7ff, 0xfff, 0x1fff, 0x3fff, 0x7fff, 0xffff,
	0x1ffff, 0x3ffff, 0x7ffff, 0xfffff, 0x1fffff, 0x3fffff, 0x7fffff, 0xffffff,
	0x1ffffff, 0x3ffffff, 0x7ffffff, 0xfffffff, 0x1fffffff, 0x3fffffff,
    0x7fffffff, 0xffffffff
};
/* used to mask bits out of characters */



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



/**************************************************************
 *  read_line reads the next line from the file and
 *  updates pkt_index, file_pkt and crt_line.
 **************************************************************/

static void
read_line(int complain)
{
	
	size_t   test = fread ((char *)buff, sizeof (char), cppkt, fpin);
	
	if (test == (size_t)0 && complain) {
		failer (READ_PAST_END);
		exit(EXIT_FAILURE);
	};
	pkt_index++;
	file_pkt++;
	crt_line = (char *)buff;
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
	
	fpin = fopen (n, "rb");
	if (fpin == (FILE *) 0) {
		failer (CANT_OPEN_FILE);
		return (0);
	};
	
	pkt_index = -1;
	file_pkt = -1;
	table_flag = 0;
	getcode_bitposn = 0;
	read_line (1);
	
	crt_line = (char *)buff;
	crt_ptr = crt_line;
	end_ptr = crt_line + cppkt;
	check_magic_no();
	return (1);
}

void
endreader()
{
	int   st = fclose (fpin);
	if (st == EOF) {
		failer ("failed to close file");
		exit(EXIT_FAILURE);
	};
}

int
getcode(int np)
{
	/* np = no of bits to read, np is >= 1 */
	{
		unsigned int m;
		int p;
		{
			int n = np;
			p = getcode_bitposn - n;
			m = mask[n];
		};
		if (p >= 0) {
			getcode_bitposn = p;
			return (int)((crt_bits.intc >> p) & m);
		};
	};
	
	{
		int p = getcode_bitposn;
		int q;
		unsigned int m;
		{
			int n = np - p;
			m = mask[n];
			q = (int)((crt_bits.intc & mask[p]) << n);
			p = 32 - n;
		};
		
		if (crt_ptr == end_ptr) {
			read_line (1);
			crt_ptr = crt_line;
		};
		
#ifndef FS_LITTLE_ENDIAN
		!!!!!!!!!!!!!  /* define FS_LITTLE_ENDIAN in config.h */
#else
#if FS_LITTLE_ENDIAN
									crt_bits.chars.d = crt_ptr[0];
									crt_bits.chars.c = crt_ptr[1];
									crt_bits.chars.b = crt_ptr[2];
									crt_bits.chars.a = crt_ptr[3];
#else
									crt_bits.intc = ((unsigned int*)crt_ptr)[0];
#endif
#endif
									crt_ptr += 4;
									getcode_bitposn = p;
									return q + (int)((crt_bits.intc >> p) & m);
	}
}

int
get_big_code(int n)
{
	int t;
	int res = 0;
	
	while (1)
	{
		t = getcode(n);
		if (t == 0)
			res += (int)(mask[n]);
		else
			return (res + t);
	};
}

/********************************************************************
 *   keep_place records the present state of the getcode variables
 *   in a place. It condenses the position variables into the
 *   bits_on field, measured from the start of the recorded line.
 ********************************************************************/

place
keep_place()
{
	place new_pl;
	new_pl.flag = table_flag;
	if (table_flag)
		new_pl.pl_mem = crt_line;
	new_pl.bits_on = (int)(crt_ptr - crt_line) * 8 - getcode_bitposn;
	if (!table_flag)
		new_pl.bits_on += pkt_index * bppkt;
	return (new_pl);
}

/********************************************************************
 *  set_place resets the getcode variables from the place pl, which
 *  was produced by keep_place or add_place. If necessary it reads more
 *  lines from the file.
 ********************************************************************/


void
set_place(place pl)
{
	int  new_pi;
	table_flag = pl.flag;
	if (!table_flag) {
		new_pi = pl.bits_on / bppkt;
		crt_line = (char *)buff;
		crt_ptr = crt_line + (pl.bits_on / 32) * 4 - new_pi * cppkt;
		getcode_bitposn = 32 - pl.bits_on % 32;
		pkt_index = file_pkt;
		while (pkt_index < new_pi)
			read_line (0);
	}
	else {
		crt_line = pl.pl_mem;
		crt_ptr = crt_line + (pl.bits_on/32)*4;
		getcode_bitposn = 32 - pl.bits_on % 32;
		current_place = pl;
	};
	if (getcode_bitposn == 32)
		getcode_bitposn = 0;
	
	if (getcode_bitposn > 0) {
#if FS_LITTLE_ENDIAN
		crt_bits.chars.d = crt_ptr[0];
		crt_bits.chars.c = crt_ptr[1];
		crt_bits.chars.b = crt_ptr[2];
		crt_bits.chars.a = crt_ptr[3];
#else
		crt_bits.intc = ((unsigned int*)crt_ptr)[0];
#endif
		crt_ptr += 4;
	};
	return;
}

/********************************************************************
 *   add_place produces a place n bits on from the place pl.
 ********************************************************************/


place
add_place(place pl, int n)
{
	place new_pl;
	new_pl.bits_on = pl.bits_on + n;
	new_pl.pl_mem = pl.pl_mem;
	new_pl.flag = pl.flag;
	return (new_pl);
}

/**********************************************************************
 *   new_place memorises a line starting from the current position
 *   and going on for bn bits. This may cause more lines to be read
 *   from the file.
 **********************************************************************/
void
add_capsule_frees(void * vp)
{
	capsule_frees * cf;
	cf = (capsule_frees*)xmalloc(sizeof(capsule_frees));
	cf->next = capsule_freelist;
	cf->ptr = vp;
	capsule_freelist = cf;
	return;
}


place
new_place(int bn)
{
	place pl;
	int   no_chars,
        i;
	char *mem;
	char  c;
	pl.flag = 1;
	
	if (!table_flag)  {
		pl.bits_on = 32 - getcode_bitposn;
		if (getcode_bitposn == 0)
			pl.bits_on = 0;
		no_chars = ((pl.bits_on + bn + 31) / 32) * 4;
		if (getcode_bitposn > 0) {
			crt_ptr -= 4;
		};
		mem = (char *) xcalloc (no_chars, sizeof (char));
		for (i = 0; i < no_chars; ++i) {
			if (crt_ptr == end_ptr) {
				read_line (1);
				crt_ptr = crt_line;
			};
			c = *crt_ptr++;
			mem[i] = c;
		};
		pl.pl_mem = mem;
		add_capsule_frees((void*)mem);
		return (pl);
	};
	
	pl.bits_on = (int)(crt_ptr - crt_line) * 8 - getcode_bitposn;
	pl.pl_mem = current_place.pl_mem;
	return pl;
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
	getcode_bitposn = getcode_bitposn - getcode_bitposn % 8;
	return;
}


/* delivers a new place for the bitstream in the input stream and steps
 *    over it */

bitstream
d_bitstream()
{
	bitstream crt_bitstream;
	place here;
	int  length;
	length = small_dtdfint ();
	here = keep_place ();
	crt_bitstream = new_place (length);
	set_place (add_place (here, length));
	return crt_bitstream;
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
	int  length;
	place here;
	length = small_dtdfint ();
	to_boundary ();
	here = keep_place ();
	set_place (add_place (here, (length * 8)));
	return;
}

/* records in bytestream_pickup the end of a bytestream */

void
start_bytestream()
{
	int  length;
	place here;
	length = small_dtdfint ();
	to_boundary ();
	here = keep_place ();
	bytestream_pickup = add_place (here, (length * 8));
	return;
}


/* resets the input stream from bytestream_pickup */

void
end_bytestream()
{
	set_place (bytestream_pickup);
	return;
}

tdfstring
d_tdfstring()
{
	/* reads a tdfstring from the input stream */
	int  bits = small_dtdfint ();
	int  n = small_dtdfint ();
	tdfstring tdb;
	int  i;
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
		tdb.ints.longs = (int *) xcalloc (n + 1, sizeof (int));
		for (i = 0; i < n; ++i)
			tdb.ints.longs[i] = getcode (bits);
		tdb.ints.longs[n] = 0;
		tdb.size = 32;
		return tdb;
	};
	if (bits <= 64) {
		tdb.ints.longs = (int *) xcalloc (n + 1, sizeof (int));
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
	/* reads a tdfident from the input stream */
	int  bits = small_dtdfint ();
	int  n = small_dtdfint ();
	tdfstring tdb;
	int  i;
	tdb.size = bits;
	tdb.number = n;
	if (bits <= 8) {
		tdb.ints.chars = (char *) xcalloc (n + 1, sizeof (char));
		to_boundary ();
		for (i = 0; i < n; ++i)
			tdb.ints.chars[i] = (char)getcode (bits);
		tdb.ints.chars[n] = 0;
		to_boundary ();
		return tdb;
	};
	if (bits <= 16) {
		tdb.ints.shorts = (short *) xcalloc (n + 1, sizeof (short));
		to_boundary ();
		for (i = 0; i < n; ++i)
			tdb.ints.shorts[i] = (short)getcode (bits);
		tdb.ints.shorts[n] = 0;
		to_boundary ();
		return tdb;
	};
	tdb.ints.longs = (int *) xcalloc (n + 1, sizeof (int));
	to_boundary ();
	for (i = 0; i < n; ++i)
		tdb.ints.longs[i] = getcode (bits);
	tdb.ints.longs[n] = 0;
	to_boundary ();
	return tdb;
}

tdfbool
d_tdfbool()
{
	/* reads a tdfbool from the input stream */
	return (tdfbool)getcode (1);
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
	tdfint maj;
	tdfint min;
	
	if (getcode(8) != 'T' || getcode(8) != 'D' || getcode(8) != 'F' ||
		getcode(8) != 'C') {
		failer("This is not a TDF Version >= 4 capsule");
		exit(EXIT_FAILURE);
	}
	maj = d_tdfint();
	if (natint(maj) > MAJOR_VERSION) {
		failer("TDF version of capsule is later than version dealt with by translator - update the translator");
		exit(EXIT_FAILURE);
	}
	else
		if (natint(maj) < MAJOR_VERSION) {
			failer("TDF version dealt with by translator is later than version of capsule - recompile capsule with later compiler");
			exit(EXIT_FAILURE);
		}
	min = d_tdfint();
	if (natint(min) > MINOR_VERSION) {
	    IGNORE fprintf(stderr, "Warning: capsule may contain constructions not dealt with in this minor version of the translator\n");
	}
	to_boundary();
}
