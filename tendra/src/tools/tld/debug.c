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


/**** debug.c --- Debugging routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the tracing routines for use with the TDF linker.
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
 * Revision 1.4  1995/09/22  08:39:15  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.3  1995/07/07  15:32:22  smf
 * Updated to support TDF specification 4.0.
 *
 * Revision 1.2  1994/12/12  11:46:18  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:31  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
 **/

/****************************************************************************/

#include "debug.h"
#include "tdf.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

static OStreamP	debug_file   = NIL (OStreamP);

/*--------------------------------------------------------------------------*/

void
debug_set_file(OStreamP file)
{
    if (ostream_is_open (file)) {
		debug_file = file;
    } else {
		debug_file = NIL (OStreamP);
    }
}

/*--------------------------------------------------------------------------*/

void
debug_info_u_name(NStringP name)
{
    if (debug_file) {
		write_cstring (debug_file, "Using unit set name '");
		write_nstring (debug_file, name);
		write_char (debug_file, '\'');
		write_newline (debug_file);
    }
}

/*--------------------------------------------------------------------------*/

void
debug_info_r_start_capsule(CStringP name)
{
    if (debug_file) {
		write_cstring (debug_file, "Reading capsule '");
		write_cstring (debug_file, name);
		write_cstring (debug_file, "':");
		write_newline (debug_file);
    }
}

void
debug_info_r_versions(unsigned major, unsigned minor)
{
    if (debug_file) {
		write_cstring  (debug_file, "  Read major version: ");
		write_unsigned (debug_file, major);
		write_cstring  (debug_file, "; minor version:");
		write_unsigned (debug_file, minor);
		write_newline  (debug_file);
    }
}

void
debug_info_r_start_unit_decs(unsigned num_unit_sets)
{
    if (debug_file) {
		write_cstring (debug_file, "  Reading ");
		write_unsigned (debug_file, num_unit_sets);
		write_cstring (debug_file, " unit set names:");
		write_newline (debug_file);
    }
}

void
debug_info_r_unit_dec(NStringP name)
{
    if (debug_file) {
		write_cstring (debug_file, "    ");
		write_nstring (debug_file, name);
		write_newline (debug_file);
    }
}

void
debug_info_r_start_shapes(unsigned num_shapes)
{
    if (debug_file) {
		write_cstring (debug_file, "  Reading ");
		write_unsigned (debug_file, num_shapes);
		write_cstring (debug_file, " shape names:");
		write_newline (debug_file);
    }
}

void
debug_info_r_shape(NStringP name, unsigned num_ids)
{
    if (debug_file) {
		write_cstring (debug_file, "    ");
		write_nstring (debug_file, name);
		write_cstring (debug_file, ", ");
		write_unsigned (debug_file, num_ids);
		write_newline (debug_file);
    }
}

void
debug_info_r_start_names(unsigned num_names)
{
    if (debug_file) {
		write_cstring (debug_file, "  Reading ");
		write_unsigned (debug_file, num_names);
		write_cstring (debug_file, " external name categories:");
		write_newline (debug_file);
    }
}

void
debug_info_r_start_shape_names(NStringP shape,
							   unsigned num_names)
{
    if (debug_file) {
		write_cstring (debug_file, "    Reading ");
		write_unsigned (debug_file, num_names);
		write_cstring (debug_file, " external ");
		write_nstring (debug_file, shape);
		write_cstring (debug_file, " names:");
		write_newline (debug_file);
    }
}

void
debug_info_r_name(NameKeyP name, unsigned old_id,
				  unsigned new_id, NameKeyP key)
{
    if (debug_file) {
		write_cstring (debug_file, "      ");
		write_name_key (debug_file, name);
		write_cstring (debug_file, ", ");
		write_unsigned (debug_file, old_id);
		write_cstring (debug_file, " -> ");
		write_unsigned (debug_file, new_id);
		write_cstring (debug_file, " (");
		write_name_key (debug_file, key);
		write_char (debug_file, ')');
		write_newline (debug_file);
    }
}

void
debug_info_r_start_unit_sets(unsigned num_unit_sets)
{
    if (debug_file) {
		write_cstring (debug_file, "  Reading ");
		write_unsigned (debug_file, num_unit_sets);
		write_cstring (debug_file, " unit sets:");
		write_newline (debug_file);
    }
}

void
debug_info_r_start_units(NStringP unit_set,
						 unsigned num_units)
{
    if (debug_file) {
		write_cstring (debug_file, "    Reading ");
		write_unsigned (debug_file, num_units);
		write_char (debug_file, ' ');
		write_nstring (debug_file, unit_set);
		write_cstring (debug_file, " units:");
		write_newline (debug_file);
    }
}

void
debug_info_r_start_unit(NStringP unit_set,
						unsigned unit, unsigned num_units)
{
    if (debug_file) {
		write_cstring (debug_file, "      Reading ");
		write_nstring (debug_file, unit_set);
		write_cstring (debug_file, " unit ");
		write_unsigned (debug_file, unit);
		write_cstring (debug_file, " of ");
		write_unsigned (debug_file, num_units);
		write_char (debug_file, ':');
		write_newline (debug_file);
    }
}

void
debug_info_r_start_counts(unsigned num_counts)
{
    if (debug_file) {
		write_cstring (debug_file, "        Reading ");
		write_unsigned (debug_file, num_counts);
		write_cstring (debug_file, " counts:");
		write_newline (debug_file);
    }
}

void
debug_info_r_count(unsigned count, NStringP shape)
{
    if (debug_file) {
		write_cstring (debug_file, "          ");
		write_unsigned (debug_file, count);
		write_cstring (debug_file, " (");
		write_nstring (debug_file, shape);
		write_char (debug_file, ')');
		write_newline (debug_file);
    }
}

void
debug_info_r_start_maps(unsigned num_maps)
{
    if (debug_file) {
		write_cstring (debug_file, "        Reading ");
		write_unsigned (debug_file, num_maps);
		write_cstring (debug_file, " mapping categories:");
		write_newline (debug_file);
    }
}

void
debug_info_r_start_shape_maps(NStringP shape,
							  unsigned num_maps)
{
    if (debug_file) {
		write_cstring (debug_file, "          Reading ");
		write_unsigned (debug_file, num_maps);
		write_char (debug_file, ' ');
		write_nstring (debug_file, shape);
		write_cstring (debug_file, " mappings:");
		write_newline (debug_file);
    }
}

void
debug_info_r_map(unsigned internal, unsigned old_external,
				 unsigned new_external)
{
    if (debug_file) {
		write_cstring (debug_file, "            ");
		write_unsigned (debug_file, internal);
		write_cstring (debug_file, ", ");
		write_unsigned (debug_file, old_external);
		write_cstring (debug_file, " -> ");
		write_unsigned (debug_file, new_external);
		write_newline (debug_file);
    }
}

void
debug_info_r_unit_body(unsigned size)
{
    if (debug_file) {
		write_cstring (debug_file, "        Reading ");
		write_unsigned (debug_file, size);
		write_cstring (debug_file, " bytes of unit body");
		write_newline (debug_file);
    }
}

void
debug_info_r_tld_version(unsigned version)
{
    if (debug_file) {
		write_cstring (debug_file, "          Reading version ");
		write_unsigned (debug_file, version);
		write_cstring (debug_file, " linker information unit:");
		write_newline (debug_file);
    }
}

void
debug_info_r_start_usages(NStringP shape,
						  unsigned num_names)
{
    if (debug_file) {
		write_cstring (debug_file, "            Reading ");
		write_unsigned (debug_file, num_names);
		write_cstring (debug_file, " external ");
		write_nstring (debug_file, shape);
		write_cstring (debug_file, " name usages:");
		write_newline (debug_file);
    }
}

void
debug_info_r_usage(unsigned use, unsigned name_use,
				   NameKeyP key)
{
    if (debug_file) {
		write_cstring (debug_file, "              ");
		write_usage (debug_file, use);
		write_cstring (debug_file, " (");
		write_name_key (debug_file, key);
		write_cstring (debug_file, ", ");
		write_usage (debug_file, name_use);
		write_char (debug_file, ')');
		write_newline (debug_file);
    }
}

void
debug_info_r_end_capsule()
{
    if (debug_file) {
		write_cstring (debug_file, "Finished reading capsule");
		write_newline (debug_file);
    }
}

void
debug_info_r_abort_capsule()
{
    if (debug_file) {
		write_cstring (debug_file, "Aborted reading capsule");
		write_newline (debug_file);
    }
}

/*--------------------------------------------------------------------------*/

void
debug_info_w_start_capsule(CStringP name)
{
    if (debug_file) {
		write_cstring (debug_file, "Writing capsule '");
		write_cstring (debug_file, name);
		write_cstring (debug_file, "':");
		write_newline (debug_file);
    }
}

void
debug_info_w_versions(unsigned major, unsigned minor)
{
    if (debug_file) {
		write_cstring  (debug_file, "  Writing major version: ");
		write_unsigned (debug_file, major);
		write_cstring  (debug_file, "; minor version:");
		write_unsigned (debug_file, minor);
		write_newline  (debug_file);
    }
}

void
debug_info_w_start_unit_decs(unsigned num_unit_sets)
{
    if (debug_file) {
		write_cstring (debug_file, "  Writing ");
		write_unsigned (debug_file, num_unit_sets);
		write_cstring (debug_file, " unit set names:");
		write_newline (debug_file);
    }
}

void
debug_info_w_unit_dec(NStringP name)
{
    if (debug_file) {
		write_cstring (debug_file, "    ");
		write_nstring (debug_file, name);
		write_newline (debug_file);
    }
}

void
debug_info_w_start_shapes(unsigned num_shapes)
{
    if (debug_file) {
		write_cstring (debug_file, "  Writing ");
		write_unsigned (debug_file, num_shapes);
		write_cstring (debug_file, " shape names:");
		write_newline (debug_file);
    }
}

void
debug_info_w_shape(NStringP name, unsigned num_ids)
{
    if (debug_file) {
		write_cstring (debug_file, "    ");
		write_nstring (debug_file, name);
		write_cstring (debug_file, ", ");
		write_unsigned (debug_file, num_ids);
		write_newline (debug_file);
    }
}

void
debug_info_w_start_names(unsigned num_names)
{
    if (debug_file) {
		write_cstring (debug_file, "  Writing ");
		write_unsigned (debug_file, num_names);
		write_cstring (debug_file, " external name categories:");
		write_newline (debug_file);
    }
}

void
debug_info_w_start_shape_names(NStringP shape,
							   unsigned num_names)
{
    if (debug_file) {
		write_cstring (debug_file, "    Writing ");
		write_unsigned (debug_file, num_names);
		write_cstring (debug_file, " external ");
		write_nstring (debug_file, shape);
		write_cstring (debug_file, " names:");
		write_newline (debug_file);
    }
}

void
debug_info_w_name(NameKeyP name, unsigned id)
{
    if (debug_file) {
		write_cstring (debug_file, "      ");
		write_name_key (debug_file, name);
		write_cstring (debug_file, ", ");
		write_unsigned (debug_file, id);
		write_newline (debug_file);
    }
}

void
debug_info_w_start_unit_sets(unsigned num_unit_sets)
{
    if (debug_file) {
		write_cstring (debug_file, "  Writing ");
		write_unsigned (debug_file, num_unit_sets);
		write_cstring (debug_file, " unit sets:");
		write_newline (debug_file);
    }
}

void
debug_info_w_start_units(NStringP unit_set,
						 unsigned num_units)
{
    if (debug_file) {
		write_cstring (debug_file, "    Writing ");
		write_unsigned (debug_file, num_units);
		write_char (debug_file, ' ');
		write_nstring (debug_file, unit_set);
		write_cstring (debug_file, " units:");
		write_newline (debug_file);
    }
}

void
debug_info_w_start_unit(NStringP unit_set,
						unsigned unit, unsigned num_units)
{
    if (debug_file) {
		write_cstring (debug_file, "      Writing ");
		write_nstring (debug_file, unit_set);
		write_cstring (debug_file, " unit ");
		write_unsigned (debug_file, unit);
		write_cstring (debug_file, " of ");
		write_unsigned (debug_file, num_units);
		write_char (debug_file, ':');
		write_newline (debug_file);
    }
}

void
debug_info_w_start_counts(unsigned num_counts)
{
    if (debug_file) {
		write_cstring (debug_file, "        Writing ");
		write_unsigned (debug_file, num_counts);
		write_cstring (debug_file, " counts:");
		write_newline (debug_file);
    }
}

void
debug_info_w_count(unsigned count, NStringP shape)
{
    if (debug_file) {
		write_cstring (debug_file, "          ");
		write_unsigned (debug_file, count);
		write_cstring (debug_file, " (");
		write_nstring (debug_file, shape);
		write_char (debug_file, ')');
		write_newline (debug_file);
    }
}

void
debug_info_w_start_maps(unsigned num_maps)
{
    if (debug_file) {
		write_cstring (debug_file, "        Writing ");
		write_unsigned (debug_file, num_maps);
		write_cstring (debug_file, " mapping categories:");
		write_newline (debug_file);
    }
}

void
debug_info_w_start_shape_maps(NStringP shape,
							  unsigned num_maps)
{
    if (debug_file) {
		write_cstring (debug_file, "          Writing ");
		write_unsigned (debug_file, num_maps);
		write_char (debug_file, ' ');
		write_nstring (debug_file, shape);
		write_cstring (debug_file, " mappings:");
		write_newline (debug_file);
    }
}

void
debug_info_w_map(unsigned internal, unsigned external)
{
    if (debug_file) {
		write_cstring (debug_file, "            ");
		write_unsigned (debug_file, internal);
		write_cstring (debug_file, ", ");
		write_unsigned (debug_file, external);
		write_newline (debug_file);
    }
}

void
debug_info_w_unit_body(unsigned size)
{
    if (debug_file) {
		write_cstring (debug_file, "        Writing ");
		write_unsigned (debug_file, size);
		write_cstring (debug_file, " bytes of unit body");
		write_newline (debug_file);
    }
}

void
debug_info_w_tld_version(unsigned version)
{
    if (debug_file) {
		write_cstring (debug_file, "          Writing version ");
		write_unsigned (debug_file, version);
		write_cstring (debug_file, " linker information unit:");
		write_newline (debug_file);
    }
}

void
debug_info_w_start_usages(NStringP shape)
{
    if (debug_file) {
		write_cstring (debug_file, "            Writing external ");
		write_nstring (debug_file, shape);
		write_cstring (debug_file, " name usages:");
		write_newline (debug_file);
    }
}

void
debug_info_w_usage(unsigned use, NameKeyP key)
{
    if (debug_file) {
		write_cstring (debug_file, "              ");
		write_usage (debug_file, use);
		write_cstring (debug_file, " (");
		write_name_key (debug_file, key);
		write_char (debug_file, ')');
		write_newline (debug_file);
    }
}

void
debug_info_w_end_capsule()
{
    if (debug_file) {
		write_cstring (debug_file, "Finished writing capsule");
		write_newline (debug_file);
    }
}

/*--------------------------------------------------------------------------*/

void
debug_info_r_start_library(CStringP name)
{
    if (debug_file) {
		write_cstring (debug_file, "Reading library '");
		write_cstring (debug_file, name);
		write_cstring (debug_file, "':");
		write_newline (debug_file);
    }
}

void
debug_info_r_lib_versions(unsigned major,
						  unsigned minor)
{
    if (debug_file) {
		write_cstring  (debug_file, "  Reading major version: ");
		write_unsigned (debug_file, major);
		write_cstring  (debug_file, "; minor version: ");
		write_unsigned (debug_file, minor);
		write_newline  (debug_file);
    }
}

void
debug_info_r_library_version(unsigned version)
{
    if (debug_file) {
		write_cstring (debug_file, "  Reading type ");
		write_unsigned (debug_file, version);
		write_cstring (debug_file, " library:");
		write_newline (debug_file);
    }
}

void
debug_info_r_start_capsules(unsigned num_capsules)
{
    if (debug_file) {
		write_cstring (debug_file, "    Reading ");
		write_unsigned (debug_file, num_capsules);
		write_cstring (debug_file, " capsules:");
		write_newline (debug_file);
    }
}

void
debug_info_r_capsule(NStringP name, unsigned length)
{
    if (debug_file) {
		write_cstring (debug_file, "      Loaded '");
		write_nstring (debug_file, name);
		write_cstring (debug_file, "', ");
		write_unsigned (debug_file, length);
		write_cstring (debug_file, " bytes");
		write_newline (debug_file);
    }
}

void
debug_info_r_start_index(unsigned num_shapes)
{
    if (debug_file) {
		write_cstring (debug_file, "    Reading ");
		write_unsigned (debug_file, num_shapes);
		write_cstring (debug_file, " shape indices:");
		write_newline (debug_file);
    }
}

void
debug_info_r_start_shape_index(NStringP shape,
							   unsigned num_names)
{
    if (debug_file) {
		write_cstring (debug_file, "      Reading ");
		write_unsigned (debug_file, num_names);
		write_cstring (debug_file, " entries in ");
		write_nstring (debug_file, shape);
		write_cstring (debug_file, " external name index:");
		write_newline (debug_file);
    }
}

void
debug_info_r_index_entry(NameKeyP name, unsigned use,
						 unsigned name_use,
						 NameKeyP key, CStringP cap_name)
{
    if (debug_file) {
		write_cstring (debug_file, "        ");
		write_name_key (debug_file, name);
		write_cstring (debug_file, ", ");
		write_usage (debug_file, use);
		write_cstring (debug_file, ", '");
		write_cstring (debug_file, cap_name);
		write_cstring (debug_file, "' (");
		write_name_key (debug_file, key);
		write_cstring (debug_file, ", ");
		write_usage (debug_file, name_use);
		write_char (debug_file, ')');
		write_newline (debug_file);
    }
}

void
debug_info_r_end_library()
{
    if (debug_file) {
		write_cstring (debug_file, "Finished reading library");
		write_newline (debug_file);
    }
}

void
debug_info_r_abort_library()
{
    if (debug_file) {
		write_cstring (debug_file, "Aborted reading library");
		write_newline (debug_file);
    }
}

/*--------------------------------------------------------------------------*/

void
debug_info_w_start_library(CStringP name)
{
    if (debug_file) {
		write_cstring (debug_file, "Writing library '");
		write_cstring (debug_file, name);
		write_cstring (debug_file, "':");
		write_newline (debug_file);
    }
}

void
debug_info_w_lib_versions(unsigned major,
						  unsigned minor)
{
    if (debug_file) {
		write_cstring  (debug_file, "  Writing major version: ");
		write_unsigned (debug_file, major);
		write_cstring  (debug_file, "; minor version: ");
		write_unsigned (debug_file, minor);
		write_newline  (debug_file);
    }
}

void
debug_info_w_library_version(unsigned version)
{
    if (debug_file) {
		write_cstring (debug_file, "  Writing type ");
		write_unsigned (debug_file, version);
		write_cstring (debug_file, " library:");
		write_newline (debug_file);
    }
}

void
debug_info_w_start_capsules(unsigned num_capsules)
{
    if (debug_file) {
		write_cstring (debug_file, "    Writing ");
		write_unsigned (debug_file, num_capsules);
		write_cstring (debug_file, " capsules:");
		write_newline (debug_file);
    }
}

void
debug_info_w_capsule(CStringP name, unsigned length)
{
    if (debug_file) {
		write_cstring (debug_file, "      Saved '");
		write_cstring (debug_file, name);
		write_cstring (debug_file, "', ");
		write_unsigned (debug_file, length);
		write_cstring (debug_file, " bytes");
		write_newline (debug_file);
    }
}

void
debug_info_w_start_index(unsigned num_shapes)
{
    if (debug_file) {
		write_cstring (debug_file, "    Writing ");
		write_unsigned (debug_file, num_shapes);
		write_cstring (debug_file, " shape indices:");
		write_newline (debug_file);
    }
}

void
debug_info_w_start_shape_index(NStringP shape,
							   unsigned num_names)
{
    if (debug_file) {
		write_cstring (debug_file, "      Writing ");
		write_unsigned (debug_file, num_names);
		write_cstring (debug_file, " entries in ");
		write_nstring (debug_file, shape);
		write_cstring (debug_file, " external name index:");
		write_newline (debug_file);
    }
}

void
debug_info_w_index_entry(NameKeyP key, unsigned use,
						 CStringP cap_name,
						 unsigned cap_index)
{
    if (debug_file) {
		write_cstring (debug_file, "        ");
		write_name_key (debug_file, key);
		write_cstring (debug_file, ", ");
		write_usage (debug_file, use);
		write_cstring (debug_file, ", '");
		write_cstring (debug_file, cap_name);
		write_cstring (debug_file, "' (");
		write_unsigned (debug_file, cap_index);
		write_char (debug_file, ')');
		write_newline (debug_file);
    }
}

void
debug_info_w_end_library()
{
    if (debug_file) {
		write_cstring (debug_file, "Finished writing library");
		write_newline (debug_file);
    }
}

/*--------------------------------------------------------------------------*/

void
debug_info_l_not_needed(NameKeyP key, NStringP shape_key,
						unsigned use)
{
    if (debug_file) {
		write_cstring (debug_file, "No definition needed for ");
		write_nstring (debug_file, shape_key);
		write_cstring (debug_file, " '");
		write_name_key (debug_file, key);
		write_cstring (debug_file, "' (");
		write_usage (debug_file, use);
		write_char (debug_file, ')');
		write_newline (debug_file);
    }
}

void
debug_info_l_not_found(NameKeyP key, NStringP shape_key,
					   unsigned use)
{
    if (debug_file) {
		write_cstring (debug_file, "No definition found for ");
		write_nstring (debug_file, shape_key);
		write_cstring (debug_file, " '");
		write_name_key (debug_file, key);
		write_cstring (debug_file, "' (");
		write_usage (debug_file, use);
		write_char (debug_file, ')');
		write_newline (debug_file);
    }
}

void
debug_info_l_found(NameKeyP key, NStringP shape_key,
				   unsigned use, CStringP name)
{
    if (debug_file) {
		write_cstring (debug_file, "Definition found for ");
		write_nstring (debug_file, shape_key);
		write_cstring (debug_file, " '");
		write_name_key (debug_file, key);
		write_cstring (debug_file, "' (");
		write_usage (debug_file, use);
		write_cstring (debug_file, ") in file '");
		write_cstring (debug_file, name);
		write_char (debug_file, '\'');
		write_newline (debug_file);
    }
}

void
debug_info_l_hide(NStringP shape, NameKeyP key)
{
    if (debug_file) {
		write_cstring (debug_file, "Hid external ");
		write_nstring (debug_file, shape);
		write_cstring (debug_file, " '");
		write_name_key (debug_file, key);
		write_char (debug_file, '\'');
		write_newline (debug_file);
    }
}

void
debug_info_l_keep(NStringP shape, NameKeyP key)
{
    if (debug_file) {
		write_cstring (debug_file, "Kept external ");
		write_nstring (debug_file, shape);
		write_cstring (debug_file, " '");
		write_name_key (debug_file, key);
		write_char (debug_file, '\'');
		write_newline (debug_file);
    }
}

void
debug_info_l_suppress(NStringP shape, NameKeyP key)
{
    if (debug_file) {
		write_cstring (debug_file, "Suppressed external ");
		write_nstring (debug_file, shape);
		write_cstring (debug_file, " '");
		write_name_key (debug_file, key);
		write_char (debug_file, '\'');
		write_newline (debug_file);
    }
}

void
debug_info_l_rename(NStringP shape, NameKeyP from,
					NameKeyP to)
{
    if (debug_file) {
		write_cstring (debug_file, "Renamed external ");
		write_nstring (debug_file, shape);
		write_cstring (debug_file, " '");
		write_name_key (debug_file, from);
		write_cstring (debug_file, "' to '");
		write_name_key (debug_file, to);
		write_char (debug_file, '\'');
		write_newline (debug_file);
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "os-interface" "library" "generated")
 * End:
 **/
