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


/**** bitvec.h --- Bit vector manipulation.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies the interface to a single size bit vector manipulation
 * facility.  It is necessary to call the ``bitvec_set_size'' function to set
 * the size of these bit vectors, before any are actually created.
 *
 ***=== TYPES ================================================================
 *
 ** Type:	BitVecT
 ** Type:	BitVecP
 ** Repr:	<private>
 *
 * This is the bit vector type.
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	void			bitvec_set_size
 *			PROTO_S ((unsigned size))
 ** Exceptions:
 *
 * This function should be called once, before any bit vectors are
 * initialised.  Its argument should specify the number of bits in a bit
 * vector.  The bits will be numbered from zero to one less than the number
 * specified.
 *
 ** Function:	void			bitvec_init
 *			PROTO_S ((BitVecP bitvec))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function initialises the specified bit vector.  Initially, all bits
 * are zero.
 *
 ** Function:	void			bitvec_copy
 *			PROTO_S ((BitVecP to, BitVecP from))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function initialises the to bit vector from the from bit vector.  It
 * is not necessary to have initialised the to bit vector with the
 * `bitvec_init' function previously.
 *
 ** Function:	void			bitvec_replace
 *			PROTO_S ((BitVecP to, BitVecP from))
 ** Exceptions:
 *
 * This function copies the from bit vector into the to bit vector.  The to
 * bit vector must have been initialised previously.
 *
 ** Function:	void			bitvec_empty
 *			PROTO_S ((BitVecP bitvec))
 ** Exceptions:
 *
 * This function sets all of the bits in the specified bit vector to zero.
 *
 ** Function:	BoolT			bitvec_is_empty
 *			PROTO_S ((BitVecP bitvec))
 ** Exceptions:
 *
 * This function returns true if all of the bits in the specified bit vector
 * are zero, and false otherwise.
 *
 ** Function:	BoolT			bitvec_is_full
 *			PROTO_S ((BitVecP bitvec))
 ** Exceptions:
 *
 * This function returns true if all of the bits in the specified bit vector
 * are set, and false otherwise.
 *
 ** Function:	void			bitvec_set
 *			PROTO_S ((BitVecP bitvec, unsigned bit))
 ** Exceptions:
 *
 * This function sets the specified bit in the specified bit vector to one.
 * Bits are numbered from zero.  If the bit is out of range, then the effect
 * of this function is undefined.
 *
 ** Function:	BoolT			bitvec_is_set
 *			PROTO_S ((BitVecP bitvec, unsigned bit))
 ** Exceptions:
 *
 * This function returns true if the specified bit in the specified bit vector
 * is set to one, and false otherwise.  Bits are numbered from zero.  If the
 * bit is out of range, the effect of this function is undefined.
 *
 ** Function:	void			bitvec_or
 *			PROTO_S ((BitVecP to, BitVecP from))
 ** Exceptions:
 *
 * This function performs an in-place bitwise or of the to bit vector and the
 * from bit vector, leaving the result in the to bit vector.
 *
 ** Function:	void			bitvec_and
 *			PROTO_S ((BitVecP to, BitVecPfrom))
 ** Exceptions:
 *
 * This function performs an in-place bitwise and of the to bit vector and the
 * from bit vector, leaving the result in the to bit vector.
 *
 ** Function:	void			bitvec_not
 *			PROTO_S ((BitVecP to))
 ** Exceptions:
 *
 * This function performs an in-place bitwise negation of the to bit vector.
 *
 ** Function:	BoolT			bitvec_equal
 *			PROTO_S ((BitVecP bitvec1, BitVecP bitvec2))
 ** Exceptions:
 *
 * This function returns true if both of the specified bit vectors are equal,
 * and false otherwise.
 *
 ** Function:	BoolT			bitvec_intersects
 *			PROTO_S ((BitVecP bitvec1, BitVecP bitvec2))
 ** Exceptions:
 *
 * This function returns true if the bitwise and of the specified bit vectors
 * contains at least one bit that is set to one, and false otherwise.
 *
 ** Function:	unsigned		bitvec_num_bits
 *			PROTO_S ((BitVecP bitvec))
 ** Exceptions:
 *
 * This function returns the number of bits in the bit vector that are set to
 * one.
 *
 ** Function:	unsigned		bitvec_first_bit
 *			PROTO_S ((BitVecP bitvec))
 ** Exceptions:
 *
 * This function returns the index of the first bit in the specified bit
 * vector that is set to one.
 *
 ** Function:	BoolT			bitvec_next_bit
 *			PROTO_S ((BitVecP bitvec, unsigned *next_ref))
 ** Exceptions:
 *
 * This function looks for the first bit set to one in the specified bit
 * vector with a higher index than that specified in the number pointed to by
 * next_ref.  If such a bit is found, then the index of that bit is written
 * back into next_ref, and the function returns true.  If no such bit is
 * found, then the function returns false.
 *
 ** Function:	void			bitvec_destroy
 *			PROTO_S ((BitVecP bitvec))
 ** Exceptions:
 *
 * This function destroys the specified bit vector.  After this, it should be
 * reinitialised before it is used.
 *
 ** Function:	void			write_bitvec_indices
 *			PROTO_S ((OStreamP ostream, BitVecP bitvec))
 ** Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes out to the specified ostream the indices of all bits
 * in the specified bit vector that are set to one.
 *
 **** Change log:
 * $Log$
 * Revision 1.2  2002/11/21 22:31:31  nonce
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
 * Revision 1.1.1.1  1998/01/17  15:57:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:57:01  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:05:47  smf
 * Initial import of library shared files.
 *
 **/

/****************************************************************************/

#ifndef H_BITVEC
#define H_BITVEC

#include "os-interface.h"
#include "dalloc.h"
#include "ostream.h"

/*--------------------------------------------------------------------------*/

typedef struct BitVecT {
    ByteP		bits;
} BitVecT, *BitVecP;

/*--------------------------------------------------------------------------*/

extern void			bitvec_set_size(unsigned);
extern void			bitvec_init(BitVecP);
extern void			bitvec_copy(BitVecP, BitVecP);
extern void			bitvec_replace(BitVecP, BitVecP);
extern void			bitvec_empty(BitVecP);
extern BoolT			bitvec_is_empty(BitVecP);
extern BoolT			bitvec_is_full(BitVecP);
extern void			bitvec_set(BitVecP, unsigned);
extern BoolT			bitvec_is_set(BitVecP, unsigned);
extern void			bitvec_or(BitVecP, BitVecP);
extern void			bitvec_and(BitVecP, BitVecP);
extern void			bitvec_not(BitVecP);
extern BoolT			bitvec_equal(BitVecP, BitVecP);
extern BoolT			bitvec_intersects(BitVecP, BitVecP);
extern unsigned			bitvec_num_bits(BitVecP);
extern unsigned			bitvec_first_bit(BitVecP);
extern BoolT			bitvec_next_bit(BitVecP, unsigned *);
extern void			bitvec_destroy(BitVecP);

extern void			write_bitvec_indices(OStreamP, BitVecP);

#endif /* !defined (H_BITVEC) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
 **/
