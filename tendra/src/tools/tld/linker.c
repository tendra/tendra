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


/**** linker.c --- Front end to linking mode of TDF linker.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file provides the front end to the linking mode of the TDF linker.
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
 * Revision 1.3  1995/09/22  08:37:11  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 *
 * Revision 1.2  1994/12/12  11:44:06  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:26  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
 **/

/****************************************************************************/

#include "linker.h"
#include "capsule.h"
#include "debug.h"
#include "error.h"
#include "file-name.h"
#include "gen-errors.h"
#include "library.h"
#include "shape-table.h"
#include "tdf.h"
#include "unit-table.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

typedef struct RenameClosureT {
    ShapeTableP			shapes;
    ShapeTableP			lib_shapes;
} RenameClosureT, *RenameClosureP;

/*--------------------------------------------------------------------------*/

static void
linker_rename_1(NStringP shape, NameKeyPairListP names,
				GenericP gclosure)
{
    RenameClosureP        closure    = (RenameClosureP) gclosure;
    ShapeTableP           shapes     = closure->shapes;
    ShapeTableP           lib_shapes = closure->lib_shapes;
    ShapeEntryP           entry      = shape_table_add (shapes, shape);
    ShapeEntryP           lib_entry  = shape_table_add (lib_shapes, shape);
    NameTableP            table      = shape_entry_name_table (entry);
    NameTableP            lib_table  = shape_entry_name_table (lib_entry);
    NameKeyPairListEntryP name       = name_key_pair_list_head (names);
	
    for (; name; name = name_key_pair_list_entry_next (name)) {
		NameKeyP from = name_key_pair_list_entry_from (name);
		NameKeyP to   = name_key_pair_list_entry_to (name);
		
		debug_info_l_rename (shape, from, to);
		name_table_add_rename (table, from, to);
		name_table_add_rename (lib_table, from, to);
    }
    name_table_resolve_renames (table, shape, TRUE);
    name_table_resolve_renames (lib_table, shape, FALSE);
}

static void
linker_rename(ArgDataP arg_data, ShapeTableP shapes,
			  ShapeTableP lib_shapes)
{
    RenameClosureT closure;
	
    closure.shapes     = shapes;
    closure.lib_shapes = lib_shapes;
    rename_control_iter (arg_data_get_renames (arg_data), linker_rename_1,
						 (GenericP) &closure);
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
		exit (EXIT_FAILURE);
		UNREACHED;
    }
}

static void
linker_read_capsules(ArgDataP arg_data, UnitTableP units,
					 ShapeTableP shapes)
{
    unsigned  num_input_files = arg_data_get_num_files (arg_data);
    CStringP *input_files     = arg_data_get_files (arg_data);
    unsigned  i;
	
    for (i = 0; i < num_input_files; i ++) {
		CapsuleP capsule;
		
		if ((capsule = capsule_create_stream_input (input_files [i])) !=
			NIL (CapsuleP)) {
			capsule_read (capsule, units, shapes);
			capsule_close (capsule);
		} else {
			E_cannot_open_input_file (input_files [i]);
		}
    }
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
		exit (EXIT_FAILURE);
		UNREACHED;
    }
}

static void
linker_load_libraries(ArgDataP arg_data, ShapeTableP lib_shapes)
{
    CStringP   *files     = arg_data_library_files (arg_data);
    CStringP   *paths     = arg_data_library_paths (arg_data);
    unsigned    num_files = arg_data_num_library_files (arg_data);
    unsigned    num_paths = arg_data_num_library_paths (arg_data);
    unsigned    i;
	
    for (i = 0; i < num_files; i ++) {
		LibraryP library = NIL (LibraryP);
		
		if (file_name_is_basename (files [i])) {
			unsigned j;
			
			for (j = 0; j < num_paths; j ++) {
				CStringP name = file_name_expand (paths [j], files [i], "tl");
				
				if ((library = library_create_stream_input (name)) !=
					NIL (LibraryP)) {
					goto found;
				} else {
					DEALLOCATE (name);
				}
			}
			E_cannot_open_library_file (files [i]);
		} else {
			if ((library = library_create_stream_input (files [i])) ==
				NIL (LibraryP)) {
				E_cannot_open_library_file (files [i]);
			}
		}
      found:
		if (library) {
			library_read (library, lib_shapes);
			library_close (library);
		}
    }
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
		exit (EXIT_FAILURE);
		UNREACHED;
    }
}

static void
linker_suppress_1(NStringP shape, BoolT all,
				  NameKeyListP names, GenericP gclosure)
{
    ShapeTableP lib_shapes = (ShapeTableP) gclosure;
    ShapeEntryP entry      = shape_table_get (lib_shapes, shape);
	
    if (entry) {
		NameTableP        table = shape_entry_name_table (entry);
		NameKeyListEntryP name  = name_key_list_head (names);
		
		if (all) {
			name_table_iter (table, name_entry_suppress, (GenericP) shape);
		}
		for (; name; name = name_key_list_entry_next (name)) {
			NameKeyP   key        = name_key_list_entry_key (name);
			NameEntryP name_entry = name_table_get (table, key);
			
			if (name_entry) {
				debug_info_l_suppress (shape, key);
				name_entry_set_lib_definition (name_entry, NIL (LibCapsuleP));
			}
		}
    }
}

static void
linker_suppress(ArgDataP arg_data, ShapeTableP lib_shapes)
{
    if (arg_data_get_suppress_mult (arg_data)) {
		shape_table_iter (lib_shapes, shape_entry_lib_suppress_mult,
						  NIL (GenericP));
    }
    shape_control_iter (arg_data_get_suppresses (arg_data), linker_suppress_1,
						(GenericP) lib_shapes);
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
		exit (EXIT_FAILURE);
		UNREACHED;
    }
}

static void
linker_resolve_undefined(UnitTableP units,
						 ShapeTableP shapes,
						 ShapeTableP lib_shapes)
{
    ShapeLibClosureT closure;
	
    closure.lib_shapes = lib_shapes;
    closure.units      = units;
    closure.shapes     = shapes;
    do {
		closure.did_define = FALSE;
		shape_table_iter (shapes, shape_entry_resolve_undefined,
						  (GenericP) &closure);
    } while (closure.did_define);
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
		exit (EXIT_FAILURE);
		UNREACHED;
    }
}

static void
linker_hide(NStringP shape, BoolT all, NameKeyListP names,
			GenericP gclosure)
{
    ShapeTableP shapes = (ShapeTableP) gclosure;
    ShapeEntryP entry  = shape_table_get (shapes, shape);
	
    if (entry == NIL (ShapeEntryP)) {
		E_cannot_hide_shape (shape);
    } else {
		NameTableP        table = shape_entry_name_table (entry);
		NameKeyListEntryP name  = name_key_list_head (names);
		
		if (all) {
			name_table_iter (table, name_entry_hide_defd, (GenericP) shape);
		}
		for (; name; name = name_key_list_entry_next (name)) {
			NameKeyP   key        = name_key_list_entry_key (name);
			NameEntryP name_entry = name_table_get (table, key);
			
			if (name_entry == NIL (NameEntryP)) {
				E_cannot_hide (shape, key);
			} else if (name_entry_get_use (name_entry) & U_DEFD) {
				debug_info_l_hide (shape, key);
				name_entry_hide (name_entry);
			} else {
				E_cannot_hide_undefined (shape, key);
			}
		}
    }
}

static void
linker_keep(NStringP shape, BoolT all, NameKeyListP names,
			GenericP gclosure)
{
    ShapeTableP shapes = (ShapeTableP) gclosure;
    ShapeEntryP entry  = shape_table_get (shapes, shape);
	
    if (entry == NIL (ShapeEntryP)) {
		E_cannot_keep_shape (shape);
    } else {
		NameTableP        table = shape_entry_name_table (entry);
		NameKeyListEntryP name  = name_key_list_head (names);
		
		if (all) {
			name_table_iter (table, name_entry_keep, (GenericP) shape);
		}
		for (; name; name = name_key_list_entry_next (name)) {
			NameKeyP   key        = name_key_list_entry_key (name);
			NameEntryP name_entry = name_table_get (table, key);
			
			if (name_entry == NIL (NameEntryP)) {
				E_cannot_keep (shape, key);
			} else {
				debug_info_l_keep (shape, key);
				name_entry_unhide (name_entry);
			}
		}
    }
}

static void
linker_hide_and_keep(ArgDataP arg_data, ShapeTableP shapes)
{
    if (arg_data_get_all_hide_defd (arg_data)) {
		shape_table_iter (shapes, shape_entry_hide_all_defd, NIL (GenericP));
    }
    shape_control_iter (arg_data_get_hides (arg_data), linker_hide,
						(GenericP) shapes);
    shape_control_iter (arg_data_get_keeps (arg_data), linker_keep,
						(GenericP) shapes);
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
		exit (EXIT_FAILURE);
		UNREACHED;
    }
}

static void
linker_write_capsule(ArgDataP arg_data, UnitTableP units,
					 ShapeTableP shapes)
{
    CStringP output_file = arg_data_get_output_file (arg_data);
    CapsuleP capsule;
	
    if ((capsule = capsule_create_stream_output (output_file)) !=
		NIL (CapsuleP)) {
		capsule_write (capsule, units, shapes);
		capsule_close (capsule);
    } else {
		E_cannot_open_output_file (output_file);
		UNREACHED;
    }
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
		exit (EXIT_FAILURE);
		UNREACHED;
    }
}

/*--------------------------------------------------------------------------*/

void
linker_main(ArgDataP arg_data)
{
    UnitTableP  units      = unit_table_create ();
    ShapeTableP shapes     = shape_table_create ();
    ShapeTableP lib_shapes = shape_table_create ();
	
    linker_rename (arg_data, shapes, lib_shapes);
    linker_read_capsules (arg_data, units, shapes);
    linker_load_libraries (arg_data, lib_shapes);
    linker_suppress (arg_data, lib_shapes);
    linker_resolve_undefined (units, shapes, lib_shapes);
    linker_hide_and_keep (arg_data, shapes);
    linker_write_capsule (arg_data, units, shapes);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library" "../tdf")
 * eval: (include::add-path-entry "../generated")
 * End:
 **/
