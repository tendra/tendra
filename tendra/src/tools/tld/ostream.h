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


/**** ostream.h --- Output stream handling.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies the interface to the output stream facility.
 *
 ***=== TYPES ================================================================
 *
 ** Type:	OStreamT
 ** Type:	OStreamP
 ** Repr:	<private>
 *
 * This is the output stream type.
 *
 ***=== CONSTANTS ============================================================
 *
 ** Constant:	ostream_output
 *
 * This is the standard output stream.  Its initial buffering state is
 * undefined.  The ``ostream_setup'' function must be called before this
 * constant is used.
 *
 ** Constant:	ostream_error
 *
 * This is the standard error stream.  Its initial buffering state is
 * undefined.  The ``ostream_setup'' function must be called before this
 * constant is used.
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	void			ostream_setup
 *			PROTO_S ((void))
 ** Exceptions:
 *
 * This function initialises the output stream facility.  It should be called
 * before any other ostream manipulation function.
 *
 ** Function:	void			ostream_init
 *			PROTO_S ((OStreamP ostream))
 ** Exceptions:
 *
 * This function initialises the specified ostream not to write to any file.
 *
 ** Function:	BoolT			ostream_open
 *			PROTO_S ((OStreamP ostream, CStringP name))
 ** Exceptions:
 *
 * This function initialises the specified ostream to write to the file with
 * the specified name.  If the file cannot be opened, the function returns
 * false.  If the file is opened successfully, the function returns true.  The
 * name should not be modified or deallocated until the ostream has been
 * closed.  The initial buffering state of the ostream is fully buffered.
 *
 ** Function:	BoolT			ostream_is_open
 *			PROTO_S ((OStreamP ostream))
 ** Exceptions:
 *
 * This function returns true if the specified ostream is writing to a file,
 * and false otherwise.
 *
 ** Function:	void			ostream_buffer
 *			PROTO_S ((OStreamP ostream))
 ** Exceptions:
 *
 * This function sets the buffering state of the specified ostream to fully
 * buffered.
 *
 ** Function:	void			ostream_unbuffer
 *			PROTO_S ((OStreamP ostream))
 *
 * This function sets the buffering state of the specified ostream to
 * unbuffered.
 *
 ** Function:	void			ostream_close
 *			PROTO_S ((OStreamP ostream))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function closes the specified ostream.
 *
 ** Function:	void			ostream_flush
 *			PROTO_S ((OStreamP ostream))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function flushes the ostream's output buffer.
 *
 ** Function:	CStringP		ostream_name
 *			PROTO_S ((OStreamP ostream))
 ** Exceptions:
 *
 * This function returns the name of the file that the specified ostream is
 * writing to.  The return value should not be modified or deallocated.
 *
 ** Function:	unsigned		ostream_line
 *			PROTO_S ((OStreamP ostream))
 ** Exceptions:
 *
 * This function returns one more than the number of newlines that have been
 * written to the specified ostream.  The result is undefined if the stream
 * is not open.
 *
 ** Function:	void			write_newline
 *			PROTO_S ((OStreamP ostream))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes a newline to the specified ostream.
 *
 ** Function:	void			write_tab
 *			PROTO_S ((OStreamP ostream))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes a tab to the specified ostream.
 *
 ** Function:	void			write_byte
 *			PROTO_S ((OStreamP ostream, ByteT c))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified byte to the specified ostream.
 *
 ** Function:	void			write_char
 *			PROTO_S ((OStreamP ostream, char c))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified character to the specified ostream.
 *
 ** Function:	void			write_escaped_char
 *			PROTO_S ((OStreamP ostream, char c))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified character to the specified ostream.
 * This differs from the ``write_char'' function, in that it will
 * `pretty-print' non-printing characters.
 *
 ** Function:	void			write_int
 *			PROTO_S ((OStreamP ostream, int i))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified integer to the specified ostream.
 *
 ** Function:	void			write_unsigned
 *			PROTO_S ((OStreamP ostream, unsigned i))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified unsigned integer to the specified
 * ostream.
 *
 ** Function:	void			write_cstring
 *			PROTO_S ((OStreamP ostream, CStringP cstring))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified C string to the specified ostream.
 *
 ** Function:	void			write_bytes
 *			PROTO_S ((OStreamP ostream, ByteP bytes,
 *				  unsigned length))
 ** Exceptions: XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified sequence of bytes (of the specified
 * length) to the specified ostream.
 *
 ** Function:	void			write_chars
 *			PROTO_S ((OStreamP ostream, CStringP chars,
 *				  unsigned length))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified sequence of characters (of the specified
 * length) to the specified ostream.
 *
 ** Function:	void			write_escaped_chars
 *			PROTO_S ((OStreamP ostream, CStringP chars,
 *				  unsigned length))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified sequence of characters (of the specified
 * length) to the specified ostream.  This differs from the ``write_chars''
 * function, in that it will `pretty-print' non-printing characters.
 *
 ** Function:	void			write_system_error
 *			PROTO_S ((OStreamP ostream));
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes a string containing a description of the current
 * system error (as defined by the ``errno'' global variable) to the specified
 * ostream.
 *
 ** Function:	void			write_pointer
 *			PROTO_S ((OStreamP ostream, GenericP pointer));
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes a string containing the address of the object pointed
 * to by the pointer to the specified ostream.
 *
 ***=== EXCEPTIONS ===========================================================
 *
 ** Exception:	XX_ostream_write_error (CStringP name)
 *
 * This exception is raised if a write attempt fails.  The data thrown is a
 * copy of the name of the file on which the error occured.  The copy should
 * be deallocated when finished with.
 *
 **** Change Log:
 * $Log$
 * Revision 1.2  2002/11/21 22:31:26  nonce
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
 * Revision 1.2  1994/12/12  11:45:50  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:12  smf
 * Initial import of os-interface shared files.
 *
 **/

/****************************************************************************/


#ifndef H_OSTREAM
#define H_OSTREAM

#include "os-interface.h"
#include "dalloc.h"
#include "exception.h"

/*--------------------------------------------------------------------------*/

typedef struct OStreamT {
    FILE		       *file;
    CStringP			name;
    unsigned			line;
} OStreamT, *OStreamP;

/*--------------------------------------------------------------------------*/

extern ExceptionP		XX_ostream_write_error;
extern OStreamT		 *const ostream_output;
extern OStreamT		 *const ostream_error;

/*--------------------------------------------------------------------------*/

extern void			ostream_setup(void);
extern void			ostream_init(OStreamP);
extern BoolT			ostream_open(OStreamP, CStringP);
extern BoolT			ostream_is_open(OStreamP);
extern void			ostream_buffer(OStreamP);
extern void			ostream_unbuffer(OStreamP);
extern void			ostream_close(OStreamP);
extern void			ostream_flush(OStreamP);
extern CStringP			ostream_name(OStreamP);
extern unsigned			ostream_line(OStreamP);

extern void			write_newline(OStreamP);
extern void			write_tab(OStreamP);
extern void			write_byte(OStreamP, ByteT);
extern void			write_char(OStreamP, char);
extern void			write_escaped_char(OStreamP, char);
extern void			write_int(OStreamP, int);
extern void			write_unsigned(OStreamP, unsigned);
extern void			write_cstring(OStreamP, CStringP);
extern void			write_bytes(OStreamP, ByteP, unsigned);
extern void			write_chars(OStreamP, CStringP, unsigned);
extern void			write_escaped_chars(OStreamP, CStringP, unsigned);
extern void			write_system_error(OStreamP);
extern void			write_pointer(OStreamP, GenericP);

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define ostream_init(os) ((os)->name = NIL (CStringP))
#define ostream_is_open(os) ((os)->name != NIL (CStringP))
#define ostream_name(os) ((os)->name)
#define ostream_line(os) ((os)->line)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_OSTREAM) */
