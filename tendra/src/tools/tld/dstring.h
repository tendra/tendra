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


/**** dstring.h --- String manipulation.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies the interface to a string manipulation facility.  There
 * are two types of strings supported: nstrings (strings are stored as a
 * length, and a vector of characters), and dstrings which are only of use
 * when it is necessary to append characters to a string one at a time with
 * reasonable efficiency.
 *
 * Null pointers are not valid as nstrings or dstrings. Passing a null pointer
 * as the argument to a function will have an undefined effect (on many
 * machines the program will abort, but this is not guaranteed).
 *
 ***=== TYPES ================================================================
 *
 ** Type:	NStringT
 ** Type:	NStringP
 ** Repr:	<private>
 *
 * This is the nstring type.  These strings may contain null characters.
 *
 ** Type:	DStringT
 ** Type:	DStringP
 ** Repr:	<private>
 *
 * This is the dstring type.  It is only for appending characters and C
 * strings to.  Once it has been completely initialised, it should be
 * converted to one of the other string types.
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	void			nstring_init
 *			PROTO_S ((NStringP nstring))
 ** Exceptions:
 *
 * This function initialises the specified nstring to be an empty nstring.
 *
 ** Function:	void			nstring_init_length
 *			PROTO_S ((NStringP nstring, unsigned length))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function initialises the specified nstring to be an nstring of the
 * specified length.  The initial contents are unspecified.
 *
 ** Function:	void			nstring_assign
 *			PROTO_S ((NStringP to, NStringP from))
 ** Exceptions:
 *
 * This function assigns the from nstring to the to nstring.  The from nstring
 * should not be used afterwards, without reinitialising it.
 *
 ** Function:	void			nstring_copy_cstring
 *			PROTO_S ((NStringP nstring, CStringP cstring))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function initialises the specified nstring from the content of the
 * specified cstring.
 *
 ** Function:	void			nstring_insert_cstring
 *			PROTO_S ((NStringP nstring, CStringP cstring))
 ** Exceptions:
 *
 * This function inserts the specified cstring into the specified nstring.
 * Sufficient characters are copied to fill up the nstring.
 *
 ** Function:	void			nstring_copy
 *			PROTO_S ((NStringP to, NStringP from))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function copies the specified from nstring into the specified to
 * nstring.
 *
 ** Function:	CStringP		nstring_to_cstring
 *			PROTO_S ((NStringP nstring))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated cstring copy of the specified
 * nstring.  If the nstring contains null characters, then the characters
 * after the first null will be ignored in the cstring (although they will
 * still be part of it).
 *
 ** Function:	unsigned		nstring_hash_value
 *			PROTO_S ((NStringP nstring))
 ** Exceptions:
 *
 * This function returns the hash value associated with the specified nstring.
 * This value is guaranteed to be identical for all nstrings with the same
 * content.
 *
 ** Function:	unsigned		nstring_length
 *			PROTO_S ((NStringP nstring))
 ** Exceptions:
 *
 * This function returns the length of the specified nstring.
 *
 ** Function:	CStringP		nstring_contents
 *			PROTO_S ((NStringP nstring))
 ** Exceptions:
 *
 * This function returns the contents of the specified nstring.
 *
 ** Function:	CmpT			nstring_compare
 *			PROTO_S ((NStringP nstring1, NStringP nstring2))
 ** Exceptions:
 *
 * This function returns ``CMP_LT'', ``CMP_EQ'', or ``CMP_GT'', depending on
 * whether the content of nstring1 is lexicographically less than, equal to,
 * or greater than the content of nstring2.
 *
 ** Function:	BoolT			nstring_equal
 *			PROTO_S ((NStringP nstring1, NStringP nstring2))
 ** Exceptions:
 *
 * This function returns true if the specified nstrings have the same content,
 * and false otherwise.
 *
 ** Function:	BoolT			nstring_ci_equal
 *			PROTO_S ((NStringP nstring1, NStringP nstring2))
 ** Exceptions:
 *
 * This function returns true if the specified nstrings have the same content
 * (ignoring differences in case), and false otherwise.
 *
 ** Function:	BoolT			nstring_contains
 *			PROTO_S ((NStringP nstring, char c))
 ** Exceptions:
 *
 * This function returns true if the specified nstring contains the specified
 * character, and false otherwise.
 *
 ** Function:	BoolT			nstring_is_prefix
 *			PROTO_S ((NStringP nstring1, NStringP nstring2))
 ** Exceptions:
 *
 * This function returns true if the second nstring is a prefix of the first
 * nstring, and false otherwise.
 *
 ** Function:	void			nstring_destroy
 *			PROTO_S ((NStringP nstring))
 ** Exceptions:
 *
 * This function deallocates the contents of the specified nstring.
 *
 ** Function:	void			write_nstring
 *			PROTO_S ((OStreamP stream, NStringP nstring))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the content of the specified nstring to the specified
 * ostream.
 *
 ** Function:	void			dstring_init
 *			PROTO_S ((DStringP dstring))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function initialises the specified dstring to be an empty dstring.
 *
 ** Function:	unsigned		dstring_length
 *			PROTO_S ((DStringP dstring))
 ** Exceptions:
 *
 * This function returns the length of the specified dstring.
 *
 ** Function:	void			dstring_append_char
 *			PROTO_S ((DStringP dstring, char c))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function appends the specified character to the specified dstring.
 *
 ** Function:	void			dstring_append_cstring
 *			PROTO_S ((DStringP dstring, CStringP cstring)
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function appends the content of the specified cstring to the specified
 * dstring.
 *
 ** Function:	void			dstring_append_nstring
 *			PROTO_S ((DStringP dstring, NStringP nstring)
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function appends the content of the specified nstring to the specified
 * dstring.
 *
 ** Function:	BoolT			dstring_last_char_equal
 *			PROTO_S ((DStringP dstring, char c))
 ** Exceptions:
 *
 * This function returns true if the last character of the specified dstring
 * is the same as the specified character, and false otherwise.  If the
 * dstring is empty, then false is always returned.
 *
 ** Function:	void			dstring_to_nstring
 *			PROTO_S ((DStringP dstring, NStringP nstring_ref))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function copies the content of the specified dstring into the
 * specified nstring.
 *
 ** Functions:	CStringP		dstring_to_cstring
 *			PROTO_S ((DStringP dstring))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function copies the content of the specified dstring into a
 * dynamically allocated cstring, and returns it.
 *
 ** Function:	CStringP		dstring_destroy_to_cstring
 *			PROTO_S ((DStringP dstring))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function does the equivalent of a call to ``dstring_to_cstring''
 * followed by a call to ``dstring_destroy''.  It returns a cstring that is
 * normally the internal cstring of the dstring (if there isn't enough room
 * for a null character at the end, then the cstring will need to be
 * reallocated).
 *
 ** Function:	void			dstring_destroy
 *			PROTO_S ((DStringP dstring))
 ** Exceptions:
 *
 * This function deallocates the contents of the specified dstring.
 *
 **** Change log:
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
 * Revision 1.1.1.1  1998/01/17  15:57:17  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:44:35  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:05:49  smf
 * Initial import of library shared files.
 *
 **/

/****************************************************************************/

#ifndef H_DSTRING
#define H_DSTRING

#include "os-interface.h"
#include "cstring.h"
#include "dalloc.h"
#include "ostream.h"

/*--------------------------------------------------------------------------*/

typedef struct NStringT {
    unsigned			length;
    CStringP			contents;
} NStringT, *NStringP;

typedef struct DStringT {
    unsigned			length;
    unsigned			max_length;
    CStringP			contents;
} DStringT, *DStringP;

/*--------------------------------------------------------------------------*/

extern void			nstring_init(NStringP);
extern void			nstring_init_length(NStringP, unsigned);
extern void			nstring_assign(NStringP, NStringP);
extern void			nstring_copy_cstring(NStringP, CStringP);
extern void			nstring_insert_cstring(NStringP, CStringP);
extern void			nstring_copy(NStringP, NStringP);
extern CStringP			nstring_to_cstring(NStringP);
extern unsigned			nstring_hash_value(NStringP);
extern unsigned			nstring_length(NStringP);
extern CStringP			nstring_contents(NStringP);
extern CmpT			nstring_compare(NStringP, NStringP);
extern BoolT			nstring_equal(NStringP, NStringP);
extern BoolT			nstring_ci_equal(NStringP, NStringP);
extern BoolT			nstring_contains(NStringP, char);
extern BoolT			nstring_is_prefix(NStringP, NStringP);
extern void			nstring_destroy(NStringP);

extern void			write_nstring(OStreamP, NStringP);

extern void			dstring_init(DStringP);
extern unsigned			dstring_length(DStringP);
extern void			dstring_append_char(DStringP, char);
extern void			dstring_append_cstring(DStringP, CStringP);
extern void			dstring_append_nstring(DStringP, NStringP);
extern BoolT			dstring_last_char_equal(DStringP, char);
extern void			dstring_to_nstring(DStringP, NStringP);
extern CStringP			dstring_to_cstring(DStringP);
extern CStringP			dstring_destroy_to_cstring(DStringP);
extern void			dstring_destroy(DStringP);

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define nstring_length(s) ((s)->length)
#define nstring_contents(s) ((s)->contents)
#define dstring_length(s) ((s)->length)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_DSTRING) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
 **/
