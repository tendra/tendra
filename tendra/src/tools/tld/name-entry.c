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


/*** name-entry.c --- Name table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the name table entry routines used by the TDF
 * linker.
 *
 *** Change Log:
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
 * Revision 1.1.1.1  1998/01/17  15:57:19  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:39:24  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:46:35  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:34  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
 **/

/****************************************************************************/

#include "name-entry.h"
#include "capsule.h"
#include "debug.h"
#include "gen-errors.h"
#include "library.h"
#include "name-table.h"
#include "ostream.h"
#include "shape-entry.h"
#include "shape-table.h"
#include "tdf.h"
#include "unit-table.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

NameEntryP
name_entry_create_direct(NameKeyP key, ShapeEntryP shape_entry)
{
    NameEntryP entry = ALLOCATE (NameEntryT);
	
    entry->next                    = NIL (NameEntryP);
    name_key_copy (&(entry->key), key);
    entry->type                    = NT_DIRECT;
    entry->u.direct.id             = shape_entry_next_id (shape_entry);
    entry->u.direct.use            = 0;
    entry->u.direct.definition     = NIL (CapsuleP);
    entry->u.direct.lib_definition = NIL (LibCapsuleP);
    shape_entry_add_to_list (shape_entry, entry);
    return (entry);
}

NameEntryP
name_entry_create_indirect(NameKeyP key, NameEntryP indirect)
{
    NameEntryP entry = ALLOCATE (NameEntryT);
	
    entry->next       = NIL (NameEntryP);
    name_key_copy (&(entry->key), key);
    entry->type       = NT_INDIRECT;
    entry->u.indirect = indirect;
    return (entry);
}

NameEntryP
name_entry_create_place(NameKeyP key)
{
    NameEntryP entry = ALLOCATE (NameEntryT);
	
    entry->next       = NIL (NameEntryP);
    name_key_copy (&(entry->key), key);
    entry->type       = NT_PLACEHOLDER;
    return (entry);
}

void
name_entry_make_direct(NameEntryP entry, ShapeEntryP shape_entry)
{
    ASSERT (name_entry_is_place (entry));
    entry->type                    = NT_DIRECT;
    entry->u.direct.id             = shape_entry_next_id (shape_entry);
    entry->u.direct.use            = 0;
    entry->u.direct.definition     = NIL (CapsuleP);
    entry->u.direct.lib_definition = NIL (LibCapsuleP);
    shape_entry_add_to_list (shape_entry, entry);
}

void
name_entry_make_indirect(NameEntryP entry,
						 NameEntryP indirect)
{
    ASSERT (name_entry_is_place (entry));
    entry->type       = NT_INDIRECT;
    entry->u.indirect = indirect;
}

NameEntryP
name_entry_resolve_renames(NameEntryP entry,
						   NStringP shape,
						   BoolT report)
{
    switch (entry->type) EXHAUSTIVE {
	case NT_PLACEHOLDER:
	case NT_DIRECT:
		return (entry);
	case NT_INDIRECT_DONE:
		return (name_entry_get_indirect (entry));
	case NT_INDIRECT_CYCLING:
		if (report) {
			E_rename_cycle (shape, name_entry_key (entry));
		}
		return (NIL (NameEntryP));
	case NT_INDIRECT:
		entry->type = NT_INDIRECT_CYCLING;
		entry->u.indirect = name_entry_resolve_renames (entry->u.indirect,
														shape, report);
		entry->type = NT_INDIRECT_DONE;
		return (name_entry_get_indirect (entry));
    }
    UNREACHED;
}

NameKeyP
name_entry_key(NameEntryP entry)
{
    return (&(entry->key));
}

NameEntryP
name_entry_next(NameEntryP entry)
{
    return (entry->next);
}

NameEntryP *
name_entry_next_ref(NameEntryP entry)
{
    return (&(entry->next));
}

BoolT
name_entry_is_direct(NameEntryP entry)
{
    return (entry->type == NT_DIRECT);
}

BoolT
name_entry_is_indirect(NameEntryP entry)
{
    return ((entry->type == NT_INDIRECT) ||
			(entry->type == NT_INDIRECT_CYCLING) ||
			(entry->type == NT_INDIRECT_DONE));
}

BoolT
name_entry_is_place(NameEntryP entry)
{
    return (entry->type == NT_PLACEHOLDER);
}

unsigned
name_entry_id(NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    return (entry->u.direct.id);
}

void
name_entry_merge_use(NameEntryP entry, unsigned use)
{
    ASSERT (name_entry_is_direct (entry));
    entry->u.direct.use |= use;
}

unsigned
name_entry_get_use(NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    return (entry->u.direct.use & (U_DEFD | U_DECD | U_MULT | U_USED));
}

void
name_entry_hide(NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    entry->u.direct.use |= U_HIDE;
}

void
name_entry_unhide(NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    entry->u.direct.use &= ~U_HIDE;
}

BoolT
name_entry_is_hidden(NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    return ((entry->u.direct.use & U_HIDE) == U_HIDE);
}

void
name_entry_set_definition(NameEntryP entry,
						  CapsuleP capsule)
{
    ASSERT (name_entry_is_direct (entry));
    entry->u.direct.definition = capsule;
}

CapsuleP
name_entry_get_definition(NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    return (entry->u.direct.definition);
}

void
name_entry_set_lib_definition(NameEntryP entry,
							  LibCapsuleP capsule)
{
    ASSERT (name_entry_is_direct (entry));
    entry->u.direct.lib_definition = capsule;
}

LibCapsuleP
name_entry_get_lib_definition(NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    return (entry->u.direct.lib_definition);
}

NameEntryP
name_entry_list_next(NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    return (entry->u.direct.list_next);
}

NameEntryP *
name_entry_list_next_ref(NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    return (&(entry->u.direct.list_next));
}

NameEntryP
name_entry_get_indirect(NameEntryP entry)
{
    ASSERT (name_entry_is_indirect (entry));
    return (entry->u.indirect);
}

NameEntryP
name_entry_deallocate(NameEntryP entry)
{
    NameEntryP next = name_entry_next (entry);
	
    name_key_destroy (name_entry_key (entry));
    DEALLOCATE (entry);
    return (next);
}

/*--------------------------------------------------------------------------*/

void
name_entry_do_count(NameEntryP entry, GenericP gclosure)
{
    unsigned *count_ref = (unsigned *) gclosure;
	
    if (!(name_entry_is_hidden (entry))) {
		(*count_ref) ++;
    }
}

void
name_entry_write_name(NameEntryP entry, GenericP gclosure)
{
    if (!(name_entry_is_hidden (entry))) {
		TDFWriterP writer = (TDFWriterP) gclosure;
		NameKeyP   key    = name_entry_key (entry);
		unsigned   id     = name_entry_id (entry);
		
		debug_info_w_name (key, id);
		tdf_write_int (writer, id);
		tdf_write_name (writer, key);
    }
}

void
name_entry_compute_tld_size(NameEntryP entry,
							GenericP gclosure)
{
    unsigned *size_ref = (unsigned *) gclosure;
	
    if (!name_entry_is_hidden (entry)) {
		unsigned use = name_entry_get_use (entry);
		
		(*size_ref) += tdf_int_size (use);
    }
}

void
name_entry_write_tld(NameEntryP entry, GenericP gclosure)
{
    TDFWriterP writer = (TDFWriterP) gclosure;
	
    if (!(name_entry_is_hidden (entry))) {
		unsigned use = name_entry_get_use (entry);
		
		debug_info_w_usage (use, name_entry_key (entry));
		tdf_write_int (writer, use);
    }
}

void
name_entry_check_multi_defs(NameEntryP entry,
							GenericP gclosure)
{
    NStringP shape_name = (NStringP) gclosure;
	
    if ((name_entry_get_use (entry) & U_MULT) &&
		(name_entry_get_definition (entry) == NIL (CapsuleP))) {
		E_no_single_definition (shape_name, name_entry_key (entry));
    }
}

void
name_entry_do_lib_count(NameEntryP entry,
						GenericP gclosure)
{
    if (name_entry_get_definition (entry)) {
		unsigned *num_names_ref = (unsigned *) gclosure;
		
		(*num_names_ref) ++;
    }
}

void
name_entry_do_lib_write(NameEntryP entry,
						GenericP gclosure)
{
    CapsuleP definition = name_entry_get_definition (entry);
	
    if (definition) {
		TDFWriterP writer        = (TDFWriterP) gclosure;
		NameKeyP   key           = name_entry_key (entry);
		unsigned   use           = name_entry_get_use (entry);
		unsigned   capsule_index = capsule_get_index (definition);
		
		debug_info_w_index_entry (key, use, capsule_name (definition),
								  capsule_index);
		tdf_write_name (writer, key);
		tdf_write_int (writer, use);
		tdf_write_int (writer, capsule_index);
    }
}

void
name_entry_suppress(NameEntryP entry, GenericP gclosure)
{
    NStringP shape = (NStringP) gclosure;
	
    debug_info_l_suppress (shape, name_entry_key (entry));
    name_entry_set_lib_definition (entry, NIL (LibCapsuleP));
}

void
name_entry_builder_suppress(NameEntryP entry,
							GenericP gclosure)
{
    NStringP shape = (NStringP) gclosure;
	
    debug_info_l_suppress (shape, name_entry_key (entry));
    name_entry_set_definition (entry, NIL (CapsuleP));
}

BoolT
name_entry_resolve_undefined(NameEntryP entry,
							 NameTableP table,
							 UnitTableP units,
							 ShapeTableP shapes,
							 NStringP shape_key)
{
    unsigned use = name_entry_get_use (entry);
    NameKeyP key = name_entry_key (entry);
	
    if ((use & U_DEFD) || (!(use & U_USED))) {
		debug_info_l_not_needed (key, shape_key, use);
		return (FALSE);
    } else if (table) {
		NameEntryP lib_entry = name_table_get (table, key);
		
		if (lib_entry) {
			LibCapsuleP lib_def = name_entry_get_lib_definition (lib_entry);
			unsigned    lib_use = name_entry_get_use (lib_entry);
			
			if (lib_def && (!lib_capsule_is_loaded (lib_def)) &&
				((!(use & U_MULT)) || (lib_use & U_DEFD))) {
				CStringP name     = lib_capsule_full_name (lib_def);
				NStringP contents = lib_capsule_contents (lib_def);
				CapsuleP capsule;
				
				debug_info_l_found (key, shape_key, use, name);
				capsule = capsule_create_string_input (name, contents);
				capsule_read (capsule, units, shapes);
				capsule_close (capsule);
				lib_capsule_loaded (lib_def);
				return (TRUE);
			}
		}
    }
    E_no_definition_found (shape_key, key);
    debug_info_l_not_found (key, shape_key, use);
    return (FALSE);
}

void
name_entry_hide_defd(NameEntryP entry, GenericP gclosure)
{
    if (name_entry_get_use (entry) & U_DEFD) {
		NStringP shape = (NStringP) gclosure;
		
		debug_info_l_hide (shape, name_entry_key (entry));
		name_entry_hide (entry);
    }
}

void
name_entry_keep(NameEntryP entry, GenericP gclosure)
{
    NStringP shape = (NStringP) gclosure;
	
    debug_info_l_keep (shape, name_entry_key (entry));
    name_entry_unhide (entry);
}

void
name_entry_suppress_mult(NameEntryP entry,
						 GenericP gclosure)
{
    if ((name_entry_get_use (entry) & (U_DEFD | U_MULT)) == U_MULT) {
		NStringP shape = (NStringP) gclosure;
		
		debug_info_l_suppress (shape, name_entry_key (entry));
		name_entry_set_definition (entry, NIL (CapsuleP));
    }
}

void
name_entry_lib_suppress_mult(NameEntryP entry,
							 GenericP gclosure)
{
    if ((name_entry_get_use (entry) & (U_DEFD | U_MULT)) == U_MULT) {
		NStringP shape = (NStringP) gclosure;
		
		debug_info_l_suppress (shape, name_entry_key (entry));
		name_entry_set_lib_definition (entry, NIL (LibCapsuleP));
    }
}

void
name_entry_show_content(NameEntryP entry,
						GenericP gclosure)
{
    LibCapsuleP capsule = name_entry_get_lib_definition (entry);
	
    UNUSED (gclosure);
    write_cstring (ostream_output, "  ");
    write_name_key (ostream_output, name_entry_key (entry));
    write_char (ostream_output, ' ');
    write_usage (ostream_output, name_entry_get_use (entry));
    write_cstring (ostream_output, " '");
    write_cstring (ostream_output, lib_capsule_name (capsule));
    write_char (ostream_output, '\'');
    write_newline (ostream_output);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
 **/
