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


/**** arg-parse.c --- Command line argument parsing.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the command line argument parsing routines specified
 * in "arg-parse.h".  See that file for more details.
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
 * Revision 1.1.1.1  1998/01/17  15:57:16  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1994/12/12  11:44:26  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.2  1994/08/22  09:36:39  smf
 * Fixed bug DR114:ids-too-long.
 *
 * Revision 1.1.1.1  1994/07/25  16:05:47  smf
 * Initial import of library shared files.
 *
 **/

/****************************************************************************/

#include "arg-parse.h"
#include "gen-errors.h"

/*--------------------------------------------------------------------------*/

void
arg_parse_intern_descriptions(ArgListP arg_list)
{
    while ((arg_list->name != NIL (CStringP)) ||
		   (arg_list->short_name != '\0')) {
		EStringP estring = error_lookup_string (arg_list->u.name);
		
		ASSERT (estring != NIL (EStringP));
		arg_list->u.message = estring;
		arg_list ++;
    }
}

int
arg_parse_arguments(ArgListP arg_list, EStringP usage,
					int argc, char **argv)
{
    int       tmp_argc = argc;
    char    **tmp_argv = argv;
    ArgUsageT closure;
	
    closure.usage    = error_string_contents (usage);
    closure.arg_list = arg_list;
    while (tmp_argc) {
		CStringP option = (tmp_argv [0]);
		char     c      = (option [0]);
		
		if ((((c == '-') && (option [1] == '-')) ||
			 ((c == '+') && (option [1] == '+'))) && (option [2] == '\0')) {
			return (argc - tmp_argc + 1);
		} else if (((c == '-') && (option [1] == '-')) ||
				   ((c == '+') && (option [1] == '+'))) {
			ArgListP tmp_list  = arg_list;
			ArgListP chosen    = NIL (ArgListP);
			unsigned matches   = 0;
			CStringP immediate = NIL (CStringP);
			
			while ((tmp_list->name != NIL (CStringP)) ||
				   (tmp_list->short_name != '\0')) {
				CStringP opt = (tmp_list->name);
				CStringP arg = (&(option [2]));
				
				if (opt != NIL (CStringP)) {
					char optch;
					char argch;
					
					do {
						optch = (*opt ++);
						argch = (*arg ++);
					} while (optch && argch && (optch == argch));
					if (optch == argch) {
						chosen    = tmp_list;
						matches   = 1;
						immediate = (arg - 1);
						break;
					} else if ((optch == '\0') &&
							   (((tmp_list->type) == AT_IMMEDIATE) ||
								((tmp_list->type) == AT_EITHER))) {
						chosen    = tmp_list;
						matches   = 1;
						immediate = (arg - 1);
						break;
					} else if (argch == '\0') {
						chosen = tmp_list;
						matches ++;
					}
				}
				tmp_list ++;
			}
			if (matches == 0) {
				E_arg_parse_unknown_option (option, &closure);
				UNREACHED;
			} else if (matches > 1) {
				E_arg_parse_ambiguous_option (option, &closure);
				UNREACHED;
			} else {
				switch (chosen->type) EXHAUSTIVE {
				case AT_SWITCH:
					(*((BoolP) (chosen->closure))) = (c == '-');
					break;
				case AT_NEG_SWITCH:
					(*((BoolP) (chosen->closure))) = (c == '+');
					break;
				case AT_PROC_SWITCH:
					(*(chosen->proc)) (option, &closure, chosen->closure,
									   c == '-');
					break;
				case AT_IMMEDIATE:
					if (immediate != NIL (CStringP)) {
						(*(chosen->proc)) (option, &closure, chosen->closure,
										   immediate);
					} else {
						E_arg_parse_unknown_option (option, &closure);
						UNREACHED;
					}
					break;
				case AT_EITHER:
					if (immediate != NIL (CStringP)) {
						if (immediate [0] != '\0') {
							(*(chosen->proc)) (option, &closure,
											   chosen->closure, immediate);
						} else if (tmp_argc > 1) {
							tmp_argv ++;
							tmp_argc --;
							(*(chosen->proc)) (option, &closure,
											   chosen->closure, tmp_argv [0]);
						} else {
							E_arg_parse_missing_argument (option, &closure);
							UNREACHED;
						}
					} else {
						E_arg_parse_unknown_option (option, &closure);
						UNREACHED;
					}
					break;
				case AT_FOLLOWING:
					if (tmp_argc > 1) {
						tmp_argv ++;
						tmp_argc --;
						(*(chosen->proc)) (option, &closure, chosen->closure,
										   tmp_argv [0]);
					} else {
						E_arg_parse_missing_argument (option, &closure);
						UNREACHED;
					}
					break;
				case AT_EMPTY:
					(*(chosen->proc)) (option, &closure, chosen->closure);
					break;
				case AT_FOLLOWING2:
					if (tmp_argc > 2) {
						tmp_argv += 2;
						tmp_argc -= 2;
						(*(chosen->proc)) (option, &closure, chosen->closure,
										   tmp_argv [-1], tmp_argv [0]);
					} else {
						E_arg_parse_missing_argument (option, &closure);
						UNREACHED;
					}
					break;
				case AT_FOLLOWING3:
					if (tmp_argc > 3) {
						tmp_argv += 3;
						tmp_argc -= 3;
						(*(chosen->proc)) (option, &closure, chosen->closure,
										   tmp_argv [-2], tmp_argv [-1],
										   tmp_argv [0]);
					} else {
						E_arg_parse_missing_argument (option, &closure);
						UNREACHED;
					}
					break;
				}
			}
		} else if (((c == '-') && (option [1] == '+')) ||
				   ((c == '+') && (option [1] == '-')) ||
				   ((c == '-') && (option [1] == '\0')) ||
				   ((c == '+') && (option [1] == '\0'))) {
			E_arg_parse_unknown_option (option, &closure);
			UNREACHED;
		} else if ((c == '-') || (c == '+')) {
			CStringP opt = &(option [1]);
			
			while ((opt != NIL (CStringP)) && (*opt != '\0')) {
				ArgListP tmp_list = arg_list;
				ArgListP chosen   = NIL (ArgListP);
				
				while ((tmp_list->name != NIL (CStringP)) ||
					   (tmp_list->short_name != '\0')) {
					if (tmp_list->short_name == *opt) {
						chosen = tmp_list;
						break;
					}
					tmp_list ++;
				}
				if (chosen) {
					switch (chosen->type) EXHAUSTIVE {
					case AT_SWITCH:
						(*((BoolP) (chosen->closure))) = (c == '-');
						break;
					case AT_NEG_SWITCH:
						(*((BoolP) (chosen->closure))) = (c == '+');
						break;
					case AT_PROC_SWITCH:
						(*(chosen->proc)) (opt, &closure, chosen->closure,
										   c == '-');
						break;
					case AT_IMMEDIATE:
						(*(chosen->proc)) (opt, &closure, chosen->closure,
										   opt + 1);
						opt = NIL (CStringP);
						break;
					case AT_EITHER:
						if (opt [1] != '\0') {
							(*(chosen->proc)) (opt, &closure, chosen->closure,
											   opt + 1);
						} else if (tmp_argc > 1) {
							tmp_argv ++;
							tmp_argc --;
							(*(chosen->proc)) (opt, &closure, chosen->closure,
											   tmp_argv [0]);
						} else {
							E_arg_parse_missing_short_arg (option, opt,
														   &closure);
							UNREACHED;
						}
						opt = NIL (CStringP);
						break;
					case AT_FOLLOWING:
						if (tmp_argc > 1) {
							tmp_argv ++;
							tmp_argc --;
							(*(chosen->proc)) (opt, &closure, chosen->closure,
											   tmp_argv [0]);
						} else {
							E_arg_parse_missing_short_arg (option, opt,
														   &closure);
							UNREACHED;
						}
						break;
					case AT_EMPTY:
						(*(chosen->proc)) (opt, &closure, chosen->closure);
						break;
					case AT_FOLLOWING2:
						if (tmp_argc > 2) {
							tmp_argv += 2;
							tmp_argc -= 2;
							(*(chosen->proc)) (opt, &closure, chosen->closure,
											   tmp_argv [-1], tmp_argv [0]);
						} else {
							E_arg_parse_missing_short_arg (option, opt,
														   &closure);
							UNREACHED;
						}
						break;
					case AT_FOLLOWING3:
						if (tmp_argc > 3) {
							tmp_argv += 3;
							tmp_argc -= 3;
							(*(chosen->proc)) (opt, &closure, chosen->closure,
											   tmp_argv [-2], tmp_argv [-1],
											   tmp_argv [0]);
						} else {
							E_arg_parse_missing_short_arg (option, opt,
														   &closure);
							UNREACHED;
						}
						break;
					}
				} else {
					E_arg_parse_unknown_short_opt (option, opt, &closure);
					UNREACHED;
				}
				if (opt) {
					opt ++;
				}
			}
		} else {
			return (argc - tmp_argc);
		}
		tmp_argv ++;
		tmp_argc --;
    }
    return (argc);
}

void
write_arg_usage(OStreamP ostream, ArgUsageP closure)
{
    CStringP usage    = (closure->usage);
    ArgListP arg_list = (closure->arg_list);
	
    write_cstring (ostream, usage);
    while ((arg_list->name != NIL (CStringP)) ||
		   (arg_list->short_name != '\0')) {
		CStringP desc = error_string_contents (arg_list->u.message);
		
		if (arg_list->name) {
			write_newline (ostream);
			write_cstring (ostream, "    {--|++}");
			write_cstring (ostream, arg_list->name);
			write_cstring (ostream, desc);
		}
		if (arg_list->short_name != '\0') {
			write_newline (ostream);
			write_cstring (ostream, "    {-|+}");
			write_char (ostream, arg_list->short_name);
			write_cstring (ostream, desc);
		}
		arg_list ++;
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
 **/
