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
/*
 *			    VERSION INFORMATION
 *			    ===================
 *
 *--------------------------------------------------------------------------
 *$Header$
 *--------------------------------------------------------------------------
 *$Log$
 *Revision 1.2  2002/11/21 22:30:45  nonce
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
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
 *Revision 1.1.1.1  1997/10/13 12:43:00  ma
 *First version.
 *
 *Revision 1.3  1997/10/13 08:50:16  ma
 *Made all pl_tests for general proc & exception handling pass.
 *
 *Revision 1.2  1997/03/20 12:52:20  ma
 *Removed #if 0 and #endif around used definitions.
 *
 *Revision 1.1.1.1  1997/03/14 07:50:19  ma
 *Imported from DRA
 
 * Revision 1.1.1.1  1996/09/20  10:56:59  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:18  john
 *
 * Revision 1.4  94/11/08  11:24:26  11:24:26  ra (Robert Andrews)
 * Changed error reporting format slightly.
 *
 * Revision 1.3  94/02/21  16:05:37  16:05:37  ra (Robert Andrews)
 * Clear up a long-int confusion.
 *
 * Revision 1.2  93/04/19  13:37:53  13:37:53  ra (Robert Andrews)
 * Line numbers in error reports were wrong.
 *
 * Revision 1.1  93/02/22  17:16:55  17:16:55  ra (Robert Andrews)
 * Initial revision
 *
 *--------------------------------------------------------------------------
 */


#include "config.h"
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
extern char *progname;
long total_calloced;
#if 0
/* Makes automatically generated makefile work */
#include "xalloc.c"
#endif


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


/*
 *    MEMORY HACK VALUE
 */

#define memhack 0

/*
 *    ALLOCATE A BLOCK OF MEMORY
 *
 *    A pointer to a block of memory of size sz is returned.  Failure to
 *    allocate this memory gives an immediate fatal error.
 */

voidstar
xmalloc(size_t sz)
{
    voidstar res;
    if (sz == 0) return (null);
    res = (voidstar) malloc (sz + memhack);
    if (res == null) {
		error ("Can't allocate memory");
		exit (EXIT_FAILURE);
    }
#ifdef MEM_DEBUG
    printf ("%d (malloc, %d bytes)\n", res, sz);
    fflush (stdout);
#endif
    return (res);
}


/*
 *    ALLOCATE ROOM IN MEMORY
 *
 *    A pointer to a block of memory of size n * sz is returned.  This
 *    memory is initialized to 0.  Failure to allocate memory gives an
 *    immediate fatal error.
 */

voidstar
xcalloc(int n, size_t sz)
{
    voidstar res;
    if (n == 0 || sz == 0) return (null);
    if (sz == sizeof (char) && n < 100) {
		/* Be careful not to free character arrays */
		static char *cbuffer = null;
		static size_t cbuffsz = 0;
		if (n + memhack >= cbuffsz) {
			cbuffsz = 2000;
			cbuffer = (char *) calloc (cbuffsz, sizeof (char));
			if (cbuffer == null) {
				error ("Can't allocate memory");
				exit (EXIT_FAILURE);
			}
		}
		res = (voidstar) cbuffer;
		cbuffer += (n + memhack);
		cbuffsz -= (n + memhack);
    } else {
		res = (voidstar) calloc (n + memhack, sz);
		if (res == null) {
			error ("Can't allocate memory");
			exit (EXIT_FAILURE);
		}
    }
#ifdef MEM_DEBUG
    printf ("%d (calloc, %d bytes)\n", res, n * sz);
    fflush (stdout);
#endif
    return (res);
}


/*
 *    REALLOCATE A BLOCK OF MEMORY
 *
 *    The previously allocated memory pointed to by p is reallocated
 *    to size n.  A pointer to the new block of memory is returned.
 *    Failure to allocate memory gives an immediate fatal error.
 */

voidstar
xrealloc(voidstar p, size_t sz)
{
    voidstar res;
    if (p == null) return (xmalloc (sz));
    if (sz == 0) return (null);
    res = (voidstar) realloc (p, sz + memhack);
    if (res == null) {
		error ("Can't reallocate memory");
		exit (EXIT_FAILURE);
    }
#ifdef MEM_DEBUG
    printf ("%d (realloc, %d bytes)\n", res, sz);
    fflush (stdout);
#endif
    return (res);
}


/*
 *    FREE A BLOCK OF MEMORY
 *
 *    The block of memory pointed to by p is returned to free.  p must
 *    previously have been allocated using one of the routines above.
 */

void
xfree(voidstar p)
{
    if (p == null) return;
    free (p);
    return;
}

