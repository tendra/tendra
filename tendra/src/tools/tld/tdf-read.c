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


/*** tdf-read.c --- TDF reader ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the TDF reader routines used by the TDF linker.
 *
 *** Change Log:
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
 * Revision 1.1.1.1  1998/01/17  15:57:20  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:39:37  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:46:55  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:38  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
 **/

/****************************************************************************/

#include "tdf-read.h"
#include "gen-errors.h"
#include "ostream.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

ExceptionP XX_tdf_read_error = EXCEPTION ("error reading TDF capsule");

/*--------------------------------------------------------------------------*/

static unsigned
tdf_read_nibble(TDFReaderP reader)
{
    if (reader->new_byte) {
		switch (reader->type) EXHAUSTIVE {
		case RT_STREAM:
			if (bistream_read_byte (&(reader->u.bistream), &(reader->byte))) {
				reader->new_byte = FALSE;
				return (((unsigned) reader->byte >> 4) & 0xF);
			}
			E_unexpected_eof_in_tdf (reader);
			THROW (XX_tdf_read_error);
			UNREACHED;
		case RT_STRING:
			if (reader->u.string.current < reader->u.string.limit) {
				reader->byte     = (ByteT) (*(reader->u.string.current ++));
				reader->new_byte = FALSE;
				reader->u.string.byte ++;
				return (((unsigned) reader->byte >> 4) & 0xF);
			}
			E_unexpected_eof_in_tdf (reader);
			THROW (XX_tdf_read_error);
			UNREACHED;
		}
    }
    reader->new_byte = TRUE;
    return (reader->byte & 0xF);
}

/*--------------------------------------------------------------------------*/

BoolT
tdf_reader_open(TDFReaderP reader, CStringP name)
{
    reader->type     = RT_STREAM;
    reader->new_byte = TRUE;
    if (!bistream_open (&(reader->u.bistream), name)) {
		return (FALSE);
    }
    return (TRUE);
}

void
tdf_reader_open_string(TDFReaderP reader,
					   CStringP name, NStringP bytes)
{
    CStringP contents = nstring_contents (bytes);
    unsigned length   = nstring_length (bytes);
	
    reader->type              = RT_STRING;
    reader->new_byte          = TRUE;
    reader->u.string.contents = contents;
    reader->u.string.current  = contents;
    reader->u.string.limit    = (contents + length);
    reader->u.string.name     = name;
    reader->u.string.byte     = 0;
}

CStringP
tdf_reader_name(TDFReaderP reader)
{
    switch (reader->type) EXHAUSTIVE {
	case RT_STREAM:
		return (bistream_name (&(reader->u.bistream)));
	case RT_STRING:
		return (reader->u.string.name);
    }
    UNREACHED;
}

unsigned
tdf_reader_byte(TDFReaderP reader)
{
    switch (reader->type) EXHAUSTIVE {
	case RT_STREAM:
		return (bistream_byte (&(reader->u.bistream)));
	case RT_STRING:
		return (reader->u.string.byte);
    }
    UNREACHED;
}

unsigned
tdf_read_int(TDFReaderP reader)
{
    unsigned value = 0;
    unsigned limit = (UINT_MAX >> 3);
	
    for (;;) {
		unsigned nibble = tdf_read_nibble (reader);
		
		if (value > limit) {
			E_tdf_integer_too_big_in_tdf (reader);
			THROW (XX_tdf_read_error);
			UNREACHED;
		}
		value <<= 3;
		value |= (nibble & 0x7);
		if (nibble & 0x8) {
			return (value);
		}
    }
}

void
tdf_read_align(TDFReaderP reader)
{
    reader->new_byte = TRUE;
}

void
tdf_read_bytes(TDFReaderP reader, NStringP nstring)
{
    unsigned length   = nstring_length (nstring);
    CStringP contents = nstring_contents (nstring);
	
    tdf_read_align (reader);
    switch (reader->type) EXHAUSTIVE {
	case RT_STREAM:
		if (bistream_read_chars (&(reader->u.bistream), length, contents) !=
			length) {
			E_unexpected_eof_in_tdf (reader);
			THROW (XX_tdf_read_error);
			UNREACHED;
		}
		break;
	case RT_STRING:
		if ((reader->u.string.current + length) > reader->u.string.limit) {
			E_unexpected_eof_in_tdf (reader);
			THROW (XX_tdf_read_error);
			UNREACHED;
		}
		nstring_insert_cstring (nstring, reader->u.string.current);
		reader->u.string.current += length;
		reader->u.string.byte    += length;
		break;
    }
}

void
tdf_read_string(TDFReaderP reader, NStringP nstring)
{
    unsigned size = tdf_read_int (reader);
    unsigned length;
	
    if (size != 8) {
		E_unsupported_char_size_in_tdf (reader, size);
		THROW (XX_tdf_read_error);
		UNREACHED;
    }
    length = tdf_read_int (reader);
    nstring_init_length (nstring, length);
    tdf_read_bytes (reader, nstring);
}

void
tdf_read_name(TDFReaderP reader, NameKeyP name)
{
    unsigned type = ((tdf_read_nibble (reader) >> 2) & 0x3);
    NStringT nstring;
    unsigned components;
    unsigned i;
	
    tdf_read_align (reader);
    switch (type) {
	case 0x1:
		tdf_read_string (reader, &nstring);
		name_key_init_string (name, &nstring);
		break;
	case 0x2:
		components = tdf_read_int (reader);
		name_key_init_unique (name, components);
		for (i = 0; i < components; i ++) {
			tdf_read_string (reader, &nstring);
			name_key_set_component (name, i, &nstring);
		}
		break;
	default:
		E_bad_name_type_in_tdf (reader, type);
		THROW (XX_tdf_read_error);
		UNREACHED;
    }
}

void
tdf_read_eof(TDFReaderP reader)
{
    ByteT byte;
	
    switch (reader->type) EXHAUSTIVE {
	case RT_STREAM:
		if (bistream_read_byte (&(reader->u.bistream), &byte)) {
			E_expected_eof_in_tdf (reader);
			THROW (XX_tdf_read_error);
			UNREACHED;
		}
		break;
	case RT_STRING:
		if (reader->u.string.current < reader->u.string.limit) {
			E_expected_eof_in_tdf (reader);
			THROW (XX_tdf_read_error);
			UNREACHED;
		}
		break;
    }
}

void
tdf_reader_rewind(TDFReaderP reader)
{
    switch (reader->type) EXHAUSTIVE {
	case RT_STREAM:
		bistream_rewind (&(reader->u.bistream));
		break;
	case RT_STRING:
		reader->u.string.current = reader->u.string.contents;
		break;
    }
}

void
tdf_reader_close(TDFReaderP reader)
{
    switch (reader->type) EXHAUSTIVE {
	case RT_STREAM:
		bistream_close (&(reader->u.bistream));
		break;
	case RT_STRING:
		break;
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
 **/
