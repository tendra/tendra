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


/**** istream.h --- Input stream handling.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies the interface to the input stream facility.
 *
 ***=== TYPES ================================================================
 *
 ** Type:	IStreamT
 ** Type:	IStreamP
 ** Repr:	<private>
 *
 * This is the input stream type.
 *
 ** Type:	IStreamStatusT
 ** Type:	IStreamStatusP
 ** Repr:	enum {ISTREAM_STAT_READ_CHAR, ISTREAM_STAT_NO_CHAR,
 *		      ISTREAM_STAT_SYNTAX_ERROR}
 *
 * This is the return type of the ``istream_read_escaped_char'' function.  The
 * constants represent the results: a character was read, no character was
 * read, and a syntax error occured respectively.
 *
 ***=== CONSTANTS ============================================================
 *
 ** Constant:	istream_input
 *
 * This value is a pointer to an input stream object that will read from the
 * standard input.  The ``istream_setup'' function must be called before this
 * constant is used.
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	void			istream_setup
 *			PROTO_S ((void))
 ** Exceptions:
 *
 * This function initialises the input stream facility.  It should be called
 * before any other istream manipulation function.
 *
 ** Function:	void			istream_init
 *			PROTO_S ((IStreamP istream))
 ** Exceptions:
 *
 * This function initialises the specified istream not to read from any file.
 *
 ** Function:	BoolT			istream_open
 *			PROTO_S ((IStreamP istream, CStringP name))
 ** Exceptions: XX_dalloc_no_memory, XX_istream_read_error
 *
 * This function initialises the specified istream to read from the file with
 * the specified name.  The name should not be modified or deallocated until
 * the istream has been closed.  If the file cannot be opened, the function
 * returns false. If the file is opened successfully, the function returns
 * true.
 *
 ** Function:	void			istream_assign
 *			PROTO_S ((IStreamP to, IStreamP from))
 ** Exceptions:
 *
 * This function assigns the from istream to the to istream.  The from istream
 * should not be used again.
 *
 ** Function:	BoolT			istream_is_open
 *			PROTO_S ((IStreamP istream))
 *
 * This function returns true if the specified istream is reading from a file,
 * and false otherwise.
 *
 ** Function:	BoolT			istream_read_char
 *			PROTO_S ((IStreamP istream, char *c_ref))
 ** Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
 *
 * This function reads the next character from the specified istream (and
 * advances the character pointer).  If a character is read then the character
 * is assigned to the reference argument, and the function returns true.  If
 * the end of file is reached, the function returns false.  If the character
 * read is a newline, then the istream's line count is incremented.
 *
 ** Function:	BoolT			istream_peek_char
 *			PROTO_S ((IStreamP istream, char *c_ref))
 ** Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
 *
 * This function reads the next character from the specified istream (but does
 * not advance the character pointer).  If a character is read then the
 * character is assigned to the reference argument, and the function returns
 * true.  If the end of file is reached, the function returns false.
 *
 ** Function:	IStreamStatusT		istream_read_escaped_char
 *			PROTO_S ((IStreamP istream, char *c_ref))
 ** Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
 *
 * This function reads a character sequence from the specified istream, and
 * parses it as an escaped character sequence.  Normally, the character to
 * which the sequence evaluates is assigned to the reference argument and
 * ``ISTREAM_STAT_READ_CHAR'' is returned.  If if it evaluates to no
 * character, then ``ISTREAM_STAT_NO_CHAR'' is returned (this is not an
 * error).  If there is an error in the syntax of the character sequence, then
 * ``ISTREAM_STAT_SYNTAX_ERROR'' is returned.  If any of the characters read
 * are newline characters, then the istream's line counter will be incremented
 * for each newline.
 *
 ** Function:	void			istream_inc_line
 *			PROTO_S ((IStreamP istream))
 ** Exceptions:
 *
 * This function increments the specified istream's line counter.  It should
 * only really be called as specified in the documentation for the
 * ``ISTREAM_READ_CHAR'' macro.
 *
 ** Function:	unsigned		istream_line
 *			PROTO_S ((IStreamP istream))
 ** Exceptions:
 *
 * This function returns the line number of the specified istream (one more
 * than the number of newlines that have been read).
 *
 ** Function:	CStringP		istream_name
 *			PROTO_S ((IStreamP istream))
 ** Exceptions:
 *
 * This function returns the name of the file from which the specified istream
 * is reading. The return value should not be modified or deallocated.
 *
 ** Function:	void			istream_close
 *			PROTO_S ((IStreamP istream))
 ** Exceptions:
 *
 * This function closes the specified istream.
 *
 ***=== MACROS ===============================================================
 *
 ** Macro:	ISTREAM_READ_CHAR (istream)
 ** Exceptions:
 *
 * This macro returns the next character from the specified istream.  It is a
 * slightly faster alternative to the ``istream_read_char'' function.  In
 * order to get the speed improvement, the program needs to do some extra
 * work: if the character returned is a newline, then the program must call
 * the ``istream_inc_line'' function to increment the line count; if the
 * character returned is a null character, then the program must call the
 * ``ISTREAM_HANDLE_NULL'' macro on the istream that was read.  It is not
 * obvious that the speed increase is worth the extra effort in coding.
 *
 ** Macro:	ISTREAM_PEEK_CHAR (istream)
 ** Exceptions:
 *
 * This macro returns the next character from the specified istream, without
 * reading it.  It is a slightly faster alternative to the
 * ``istream_peek_char'' function.  In order to get the speed improvement, the
 * program needs to do some extra work: if the character returned is the null
 * character, then the program must call the ``ISTREAM_HANDLE_NULL'' macro on
 * the istream that was read.  Unlike the ``ISTREAM_READ_CHAR'' macro, it is
 * not necessary to increment the istream's line count.  It is not obvious
 * that the speed increase is worth the extra effort in coding.
 *
 ** Macro:	ISTREAM_HANDLE_NULL (istream, redo, eof)
 ** Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
 *
 * This macro should be called when either of the previous two macros returns
 * the null character.  It checks to see if the null character is really a
 * null character, a refill buffer instruction, or an end of file.  If it is a
 * real null character, then the program continues normally.  If it is a
 * refill buffer instruction, the istream's buffer is refilled, and the
 * program goes to the label ``redo''.  If it is an end of file, then the
 * program goes to the label ``eof''.
 *
 ***=== EXCEPTIONS ===========================================================
 *
 ** Exception:	XX_istream_read_error (CStringP name)
 *
 * This exception is raised if a read attempt fails.  The data thrown is a
 * copy of the name of the file that the read error occured on.  The copy
 * should be deallocated when finished with.
 *
 **** Change Log:
 * $Log$
 * Revision 1.2  2002/11/21 22:31:25  nonce
 * Remove ossg prototypes.  This commit is largely whitespace changes,
 * but is nonetheless important.  Here's why.
 *
 * I.  Background
 * =========================
 *
 *     The current TenDRA-4.1.2 source tree uses "ossg" prototype
 * conventions, based on the Open Systems Software Group publication "C
 * Coding Standards", DRA/CIS(SE2)/WI/94/57/2.0 (OSSG internal document).
 * The goal behind ossg prototypes remains admirable: TenDRA should
 * support platforms that lack ANSI compliant compilers.  The explicit
 * nature of ossg's prototypes makes macro substition easy.
 *
 *     Here's an example of one function:
 *
 *     static void uop
 * 	PROTO_N ( ( op, sha, a, dest, stack ) )
 * 	PROTO_T ( void ( *op ) PROTO_S ( ( shape, where, where ) ) X
 * 		  shape sha X exp a X where dest X ash stack )
 *     {
 *
 * tendra/src/installers/680x0/common/codec.c
 *
 *   The reasons for removing ossg are several, including:
 *
 *   0) Variables called 'X' present a problem (besides being a poor
 * variable name).
 *
 *   1) Few platforms lack ANSI-compliant compilers.  ISO-compliant
 * prototypes are easily handled by most every compiler these days.
 *
 *   2) Although TenDRA emphasizes portability, standards compliance is
 * the primary goal of the current project.  We should expect no less
 * from the compiler source code.
 *
 *   3) The benefits of complex prototypes are few, given parameter
 * promotion rules.  (Additionally, packing more types into int-sized
 * spaces tends to diminish type safety, and greatly complicates
 * debugging and testing.)
 *
 *   4) It would prove impractical to use an OSSG internal style document
 * in an open source project.
 *
 *   5) Quite frankly, ossg prototypes are difficult to read, but that's
 * certainly a matter of taste and conditioning.
 *
 * II.  Changes
 * =========================
 *
 *    This commit touches most every .h and .c file in the tendra source
 * tree.  An emacs lisp script (http://www.tendra.org/~nonce/tendra/rmossg.el)
 * was used to automate the following changes:
 *
 *    A.  Prototype Conversions.
 *    --------------------------------------------------
 *
 *    The PROTO_S, PROTO_Z, PROTO_N, PROTO_T, and PROTO_V macros were
 * rewritten to ISO-compliant form.  Not every file was touched.  The
 * files named ossg.h, ossg_api.h, code.c, coder.c and ossg_std.h were
 * left for hand editing.  These files provide header generation, or have
 * non-ossg compliant headers to start with.  Scripting around these
 * would take too much time; a separate hand edit will fix them.
 *
 *    B.  Statement Spacing
 *    --------------------------------------------------
 *
 *    Most of the code in the TenDRA-4.1.2 used extra spaces to separate
 * parenthetical lexemes.  (See the quoted example above.)  A simple
 * text substitution was made for:
 *
 *      Before            After
 * ===================================
 *
 *    if ( x )            if (x)
 *    if(x)               if (x)
 *    x = 5 ;             x = 5;
 *    ... x) )            ... x))
 *
 * All of these changes are suggested by style(9).  Additional, statement
 * spacing considerations were made for all of the style(9) keywords:
 * "if" "while" "for" "return" "switch".
 *
 * A few files seem to have too few spaces around operators, e.g.:
 *
 *       arg1*arg2
 *
 * instead of
 *
 *       arg1 * arg2
 *
 * These were left for hand edits and later commits, since few files
 * needed these changes.  (At present, the rmossg.el script takes 1 hour
 * to run on a 2GHz P4, using a ramdisk.  Screening for the 1% that
 * needed change would take too much time.)
 *
 *    C.  License Information
 *    --------------------------------------------------
 *
 * After useful discussion on IRC, the following license changes were
 * made:
 *
 *    1) Absent support for $License::BSD$ in the repository, license
 * and copyright information was added to each file.
 *
 *    2) Each file begins with:
 *
 *    Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 *    All rights reserved.
 *
 *    Usually, copyright stays with the author of the code; however, I
 * feel very strongly that this is a group effort, and so the tendra
 * project should claim any new (c) interest.
 *
 *    3) The comment field then shows the bsd license and warranty
 *
 *    4) The comment field then shows the Crown Copyright, since our
 * changes are not yet extensive enough to claim any different.
 *
 *    5) The comment field then closes with the $TenDRA$ tag.
 *
 *    D.  Comment Formatting
 *    --------------------------------------------------
 *
 * The TenDRA-4.1.2 code base tended to use comment in this form:
 *
 *     /*
 *        Statement statement
 *        statement
 *      */
 *
 * while style(9) suggests:
 *
 *     /*
 *      * Statement statement
 *      * statement
 *      */
 *
 * Not every comment in -4.1.2 needed changing.  A parser was written to
 * identify non-compliant comments.  Note that a few comments do not
 * follow either the TenDRA-4.1.2 style or style(9), or any style I can
 * recognize.  These need hand fixing.
 *
 *    E.  Indentation
 *    --------------------------------------------------
 *
 *    A elisp tendra-c-mode was created to define how code should be
 * indented.  The structure follows style(9) in the following regards:
 *
 *   (c-set-offset 'substatement-open 0)
 *   (setq c-indent-tabs-mode t
 * 	c-indent-level 4
 * 	c-argdecl-indent t
 * 	c-tab-always-indent t
 * 	backward-delete-function nil
 * 	c-basic-offset 4
 * 	tab-width 4))
 *
 * This means that substatement opening are not indented.  E.g.:
 *
 *    if (condition)
 *    {
 *
 * instead of
 *
 *    if (condition)
 *      {
 *
 * or even
 *
 *    if (condition) {
 *
 * Each statement is indented by a tab instead of a spaces.  Set your tab
 * stop to comply with style(9); see the vim resources in the tendra
 * tree.  I'll add the emacs mode support shortly.
 *
 * No doubt, a function or two escaped change because of unusual
 * circumstances.  These must be hand fixed as well.
 *
 * III.  Things Not Changed
 * =========================
 *
 *     A large number of style(9) deficiencies remain.  These will
 * require a separate effort.  I decided to stop with the changes noted
 * above because:
 *
 *    0)  The script currently takes hours to run to completion even on
 * high-end consumer machines.
 *
 *    1)  We need to move on and fix other substantive problems.
 *
 *    2) The goal of this commit was *just* ossg removal; I took the
 * opportunity to get other major white-space issues out of the way.
 *
 *     I'll also note that despite this commit, a few ossg issues remain.
 * These include:
 *
 *    0) The ossg headers remain.  They contain useful flags needed by
 * other operations.  Additionally, the BUILD_ERRORS perl script still
 * generates ossg-compliant headers.  (This is being removed as we change
 * the build process.)
 *
 *    1) A few patches of code check for ossg flags: "if (ossg) etc."
 * These can be hand removed as well.
 *
 *    2) No doubt, a few ossg headers escaped the elisp script.  We can
 * address these seriatim.
 *
 * IV.  Testing
 * =========================
 *
 *     Without a complete build or test suite, it's difficult to
 * determine if these changes have introduced any bugs.  I've identified
 * several situations where removal of ossg caused bugs in sid and
 * calculus operations.  The elisp script avoids these situations; we
 * will hand edit a few files.
 *
 *     As is, the changes should behave properly; the source base builds
 * the same before and after the rmossg.el script is run.  Nonetheless,
 * please note that this commit changes over 23,000 PROTO declarations,
 * and countless line changes.  I'll work closely with any developers
 * affected by this change.
 *
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:45:43  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:10  smf
 * Initial import of os-interface shared files.
 *
 **/

/****************************************************************************/

#ifndef H_ISTREAM
#define H_ISTREAM

#include "os-interface.h"
#include "dalloc.h"
#include "exception.h"

/*--------------------------------------------------------------------------*/

typedef struct IStreamT {
    FILE		       *file;
    CStringP			buffer;
    CStringP			current;
    CStringP			end;
    CStringP			limit;
    unsigned			line;
    CStringP			name;
    BoolT			read_last;
} IStreamT, *IStreamP;

#ifdef FS_NO_ENUM
typedef int IStreamStatusT, *IStreamStatusP;
#define ISTREAM_STAT_READ_CHAR		(0)
#define ISTREAM_STAT_NO_CHAR		(1)
#define ISTREAM_STAT_SYNTAX_ERROR	(2)
#else
typedef enum {
    ISTREAM_STAT_READ_CHAR,
    ISTREAM_STAT_NO_CHAR,
    ISTREAM_STAT_SYNTAX_ERROR
} IStreamStatusT, *IStreamStatusP;
#endif /* defined (FS_NO_ENUM) */

/*--------------------------------------------------------------------------*/

extern ExceptionP		XX_istream_read_error;
extern IStreamT		 *const istream_input;

/*--------------------------------------------------------------------------*/

extern void			istream_setup(void);
extern void			istream_init(IStreamP);
extern BoolT			istream_open(IStreamP, CStringP);
extern void			istream_assign(IStreamP, IStreamP);
extern BoolT			istream_is_open(IStreamP);
extern BoolT			istream_read_char(IStreamP, char *);
extern BoolT			istream_peek_char(IStreamP, char *);
extern IStreamStatusT		istream_read_escaped_char(IStreamP, char *);
extern void			istream_inc_line(IStreamP);
extern unsigned			istream_line(IStreamP);
extern CStringP			istream_name(IStreamP);
extern void			istream_close(IStreamP);

/*--------------------------------------------------------------------------*/

extern void			X__istream_fill_buffer(IStreamP);

/*--------------------------------------------------------------------------*/

#define ISTREAM_READ_CHAR(istream) \
(((istream)->read_last = TRUE), (*((istream)->current) ++))

#define ISTREAM_PEEK_CHAR(istream) \
(((istream)->read_last = FALSE), (*((istream)->current)))

#define ISTREAM_HANDLE_NULL(istream,redo,eof) \
{ \
    IStreamP X___is = (istream); \
    if (X___is->read_last) { \
	if (X___is->current == X___is->end) { \
	    if (X___is->end == X___is->limit) { \
		X__istream_fill_buffer (X___is); \
		goto redo; \
	    } else { \
		X___is->current --; \
		goto eof; \
	    } \
	} \
    } else { \
	if (X___is->current == (X___is->end - 1)) { \
	    if (X___is->end == X___is->limit) { \
		X__istream_fill_buffer (X___is); \
		goto redo; \
	    } else { \
		goto eof; \
	    } \
	} \
    } \
}

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define istream_init(is) ((is)->name = NIL (CStringP))
#define istream_is_open(is) ((is)->name != NIL (CStringP))
#define istream_inc_line(is) ((is)->line ++)
#define istream_line(is) ((is)->line)
#define istream_name(is) ((is)->name)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_ISTREAM) */
