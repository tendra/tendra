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


/**** error-file.c --- Error file parsing routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the error file parsing facility specified in the file
 * "error-file.h".  See that file for more details.
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
 * Revision 1.1.1.1  1998/01/17  15:57:17  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1994/12/12  11:44:37  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.2  1994/08/22  09:36:44  smf
 * Fixed bug DR114:ids-too-long.
 *
 * Revision 1.1.1.1  1994/07/25  16:05:49  smf
 * Initial import of library shared files.
 *
 **/

/****************************************************************************/

#include "error-file.h"
#include "dstring.h"
#include "error.h"
#include "gen-errors.h"
#include "syntax.h"

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int ErrorFileTagT, *ErrorFileTagP;
#define EFTOKEN_NAME		(0)
#define EFTOKEN_STRING		(1)
#define EFTOKEN_BLT_STRINGS	(2)
#define EFTOKEN_BLT_PREFIX	(3)
#define EFTOKEN_BLT_ERRORS	(4)
#define EFTOKEN_EOF		(5)
#else
typedef enum {
    EFTOKEN_NAME,
    EFTOKEN_STRING,
    EFTOKEN_BLT_STRINGS,
    EFTOKEN_BLT_PREFIX,
    EFTOKEN_BLT_ERRORS,
    EFTOKEN_EOF
} ErrorFileTagT, *ErrorFileTagP;
#endif /* defined (FS_NO_ENUM) */

typedef struct ErrorFileLexT {
    ErrorFileTagT		tag;
    union {
		CStringP		string;
    } u;
} ErrorFileLexT, *ErrorFileLexP;

#ifdef FS_NO_ENUM
typedef int ErrorFileTokenT, *ErrorFileTokenP;
#define EFN_BUILTIN	(0)
#define EFN_NAME	(1)
#define EFN_STRING	(2)
#else
typedef enum {
    EFN_BUILTIN,
    EFN_NAME,
    EFN_STRING
} ErrorFileTokenT, *ErrorFileTokenP;
#endif /* defined (FS_NO_ENUM) */

/*--------------------------------------------------------------------------*/

static BoolT
error_file_skip_white_space(IStreamP istream,
							char *c_ref)
{
    BoolT comment = FALSE;
	
    for (;;) {
		char c;
		
      redo:
		switch (c = ISTREAM_READ_CHAR (istream)) {
		case '\0':
			ISTREAM_HANDLE_NULL (istream, redo, eof);
			break;
		case '\n':
			istream_inc_line (istream);
			comment = FALSE;
			break;
		case '#':
			comment = TRUE;
			break;
		default:
			if ((!comment) && (!syntax_is_white_space (c))) {
				*c_ref = c;
				return (TRUE);
			}
		}
    }
  eof:
    return (FALSE);
}

static void
error_file_null_character(IStreamP istream,
						  ErrorFileTokenT type)
{
    switch (type) EXHAUSTIVE {
	case EFN_NAME:
		E_errf_null_character_in_name (istream);
		UNREACHED;
	case EFN_BUILTIN:
		E_errf_null_char_in_builtin (istream);
		UNREACHED;
	case EFN_STRING:
		E_errf_null_character_in_string (istream);
		UNREACHED;
    }
}

static void
error_file_newline(IStreamP istream, ErrorFileTokenT type)
{
    switch (type) EXHAUSTIVE {
	case EFN_NAME:
		E_errf_newline_in_name (istream);
		UNREACHED;
	case EFN_BUILTIN:
		E_errf_newline_in_builtin (istream);
		UNREACHED;
	case EFN_STRING:
		E_errf_newline_in_string (istream);
		UNREACHED;
    }
}

static void
error_file_illegal_escape(IStreamP istream,
						  ErrorFileTokenT type)
{
    switch (type) EXHAUSTIVE {
	case EFN_NAME:
		E_errf_illegal_escape_in_name (istream);
		UNREACHED;
	case EFN_BUILTIN:
		E_errf_illegal_esc_in_builtin (istream);
		UNREACHED;
	case EFN_STRING:
		E_errf_illegal_escape_in_string (istream);
		UNREACHED;
    }
}

static void
error_file_eof(IStreamP istream, ErrorFileTokenT type)
{
    switch (type) EXHAUSTIVE {
	case EFN_NAME:
		E_errf_eof_in_name (istream);
		UNREACHED;
	case EFN_BUILTIN:
		E_errf_eof_in_builtin (istream);
		UNREACHED;
	case EFN_STRING:
		E_errf_eof_in_string (istream);
		UNREACHED;
    }
}

static void
error_file_read_until(IStreamP istream, char term,
					  ErrorFileTokenT type,
					  ErrorFileLexP token)
{
    DStringT dstring;
	
    dstring_init (&dstring);
    for (;;) {
		char c;
		
      redo:
		switch (c = ISTREAM_READ_CHAR (istream)) {
		case '\0':
			ISTREAM_HANDLE_NULL (istream, redo, eof);
			error_file_null_character (istream, type);
			UNREACHED;
		case '\n':
			istream_inc_line (istream);
			error_file_newline (istream, type);
			UNREACHED;
		default:
			if (c == term) {
				CStringP tmp;
				
				tmp = dstring_to_cstring (&dstring);
				dstring_destroy (&dstring);
				token->u.string = tmp;
				return;
			} else if (c == '\\') {
				switch (istream_read_escaped_char (istream, &c)) EXHAUSTIVE {
				case ISTREAM_STAT_READ_CHAR:
					if (c == '\0') {
						error_file_null_character (istream, type);
						UNREACHED;
					}
					dstring_append_char (&dstring, c);
					break;
				case ISTREAM_STAT_SYNTAX_ERROR:
					error_file_illegal_escape (istream, type);
					UNREACHED;
				case ISTREAM_STAT_NO_CHAR:
					/*NOTHING*/
					break;
				}
			} else {
				dstring_append_char (&dstring, c);
			}
			break;
		}
    }
  eof:
    error_file_eof (istream, type);
    UNREACHED;
}

static void
error_file_check_builtin(IStreamP istream,
						 ErrorFileLexP token)
{
    if (cstring_ci_equal (token->u.string, "strings")) {
		token->tag = EFTOKEN_BLT_STRINGS;
    } else if (cstring_ci_equal (token->u.string, "prefix")) {
		token->tag = EFTOKEN_BLT_PREFIX;
    } else if (cstring_ci_equal (token->u.string, "errors")) {
		token->tag = EFTOKEN_BLT_ERRORS;
    } else {
		E_errf_unknown_builtin (istream, token->u.string);
		UNREACHED;
    }
    DEALLOCATE (token->u.string);
}

static void
error_file_next_token(IStreamP istream, ErrorFileLexP token)
{
    char c;
	
    if (error_file_skip_white_space (istream, &c)) {
		switch (c) {
		case '%':
			error_file_read_until (istream, '%', EFN_BUILTIN, token);
			error_file_check_builtin (istream, token);
			break;
		case '\'':
			error_file_read_until (istream, '\'', EFN_NAME, token);
			token->tag = EFTOKEN_NAME;
			break;
		case '"':
			error_file_read_until (istream, '"', EFN_STRING, token);
			token->tag = EFTOKEN_STRING;
			break;
		default:
			E_errf_illegal_character (istream, c);
			UNREACHED;
		}
    } else {
		token->tag = EFTOKEN_EOF;
    }
}

static void
error_file_parse_strings(IStreamP istream,
						 ErrorFileLexP token)
{
    while (error_file_next_token (istream, token),
		   (token->tag == EFTOKEN_NAME)) {
		CStringP name = token->u.string;
		
		if (error_file_next_token (istream, token),
			(token->tag != EFTOKEN_STRING)) {
			E_errf_expected_string (istream);
			UNREACHED;
		} else if (!error_redefine_string (name, token->u.string)) {
			E_errf_unknown_string (istream, name);
			UNREACHED;
		}
		DEALLOCATE (name);
    }
}

static void
error_file_parse_prefix(IStreamP istream,
						ErrorFileLexP token)
{
    error_file_next_token (istream, token);
    if (token->tag != EFTOKEN_STRING) {
		E_errf_expected_string (istream);
		UNREACHED;
    } else if (!error_set_prefix_message (token->u.string)) {
		E_errf_illegal_message (istream, token->u.string);
		UNREACHED;
    }
    DEALLOCATE (token->u.string);
    error_file_next_token (istream, token);
}

static void
error_file_parse_errors(IStreamP istream,
						ErrorFileLexP token)
{
    while (error_file_next_token (istream, token),
		   (token->tag == EFTOKEN_NAME)) {
		CStringP name = token->u.string;
		
		error_file_next_token (istream, token);
		if (token->tag != EFTOKEN_STRING) {
			E_errf_expected_string (istream);
			UNREACHED;
		} else {
			switch (error_redefine_error (name, token->u.string)) EXHAUSTIVE {
			case ERROR_STATUS_BAD_ERROR:
				E_errf_unknown_error (istream, name);
				UNREACHED;
			case ERROR_STATUS_BAD_MESSAGE:
				E_errf_illegal_message (istream, token->u.string);
				UNREACHED;
			case ERROR_STATUS_SUCCESS:
				/*NOTHING*/
				break;
			}
		}
		DEALLOCATE (name);
		DEALLOCATE (token->u.string);
    }
}

/*--------------------------------------------------------------------------*/

void
error_file_parse(CStringP name, BoolT must_open)
{
    IStreamT      istream;
    ErrorFileLexT token;
	
    if (istream_open (&istream, name)) {
		error_file_next_token (&istream, &token);
		while (token.tag != EFTOKEN_EOF) {
			switch (token.tag) {
			case EFTOKEN_BLT_STRINGS:
				error_file_parse_strings (&istream, &token);
				break;
			case EFTOKEN_BLT_PREFIX:
				error_file_parse_prefix (&istream, &token);
				break;
			case EFTOKEN_BLT_ERRORS:
				error_file_parse_errors (&istream, &token);
				break;
			default:
				E_errf_expected_section (&istream);
				UNREACHED;
			}
		}
		istream_close (&istream);
    } else if (must_open) {
		E_errf_cannot_open (name);
		UNREACHED;
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
 **/
