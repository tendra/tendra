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


/*** shape-entry.c --- Shape table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the shape table entry routines used by the TDF
 * linker.
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
 * Revision 1.3  1995/09/22  08:39:31  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:46:46  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:37  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
 **/

/****************************************************************************/

#include "shape-entry.h"
#include "debug.h"
#include "gen-errors.h"
#include "unit-table.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

ShapeEntryP
shape_entry_create(NStringP key)
{
    ShapeEntryP entry = ALLOCATE (ShapeEntryT);
	
    entry->next      = NIL (ShapeEntryP);
    nstring_copy (shape_entry_key (entry), key);
    entry->names     = name_table_create ();
    entry->id_count  = 0;
    entry->non_empty = FALSE;
    entry->head      = NIL (NameEntryP);
    entry->tail      = &(entry->head);
    return (entry);
}

ShapeEntryP
shape_entry_next(ShapeEntryP entry)
{
    return (entry->next);
}

ShapeEntryP *
shape_entry_next_ref(ShapeEntryP entry)
{
    return (&(entry->next));
}

NStringP
shape_entry_key(ShapeEntryP entry)
{
    return (&(entry->key));
}

NameTableP
shape_entry_name_table(ShapeEntryP entry)
{
    return (entry->names);
}

unsigned
shape_entry_next_id(ShapeEntryP entry)
{
    if (entry->id_count == UINT_MAX) {
		E_too_many_ids ();
    }
    return (entry->id_count ++);
}

void
shape_entry_set_non_empty(ShapeEntryP entry)
{
    entry->non_empty = TRUE;
}

BoolT
shape_entry_get_non_empty(ShapeEntryP entry)
{
    return (entry->non_empty);
}

void
shape_entry_add_to_list(ShapeEntryP entry,
						NameEntryP name_entry)
{
    *(entry->tail) = name_entry;
    entry->tail    = name_entry_list_next_ref (name_entry);
}

NameEntryP
shape_entry_get_from_list(ShapeEntryP entry)
{
    NameEntryP name_entry;
	
    if ((name_entry = entry->head) != NIL (NameEntryP)) {
		entry->head = name_entry_list_next (name_entry);
		if (entry->head == NIL (NameEntryP)) {
			entry->tail = (&entry->head);
		}
    }
    return (name_entry);
}

ShapeEntryP
shape_entry_deallocate(ShapeEntryP entry)
{
    ShapeEntryP next = shape_entry_next (entry);
	
    nstring_destroy (shape_entry_key (entry));
    name_table_deallocate (shape_entry_name_table (entry));
    DEALLOCATE (entry);
    return (next);
}

/*--------------------------------------------------------------------------*/

void
shape_entry_do_count(ShapeEntryP entry, GenericP gclosure)
{
    unsigned *count_ref = (unsigned *) gclosure;
	
    if ((entry->id_count > 0) || (shape_entry_get_non_empty (entry))) {
		shape_entry_set_non_empty (entry);
		(*count_ref) ++;
    }
}

void
shape_entry_write_shape(ShapeEntryP entry,
						GenericP gclosure)
{
    if (shape_entry_get_non_empty (entry)) {
		TDFWriterP writer  = (TDFWriterP) gclosure;
		NStringP   key     = shape_entry_key (entry);
		unsigned   num_ids = entry->id_count;
		
		debug_info_w_shape (key, num_ids);
		tdf_write_string (writer, key);
		tdf_write_int (writer, num_ids);
    }
}

void
shape_entry_write_externs(ShapeEntryP entry,
						  GenericP gclosure)
{
    if (shape_entry_get_non_empty (entry)) {
		TDFWriterP writer      = (TDFWriterP) gclosure;
		unsigned   num_externs = 0;
		NameTableP table       = entry->names;
		NStringP   key         = shape_entry_key (entry);
		
		name_table_iter (table, name_entry_do_count, (GenericP) &num_externs);
		debug_info_w_start_shape_names (key, num_externs);
		tdf_write_int (writer, num_externs);
		name_table_iter (table, name_entry_write_name, (GenericP) writer);
    }
}

void
shape_entry_compute_tld_size(ShapeEntryP entry,
							 GenericP gclosure)
{
    if (shape_entry_get_non_empty (entry)) {
		name_table_iter (entry->names, name_entry_compute_tld_size, gclosure);
    }
}

void
shape_entry_write_tld(ShapeEntryP entry, GenericP gclosure)
{
    if (shape_entry_get_non_empty (entry)) {
		debug_info_w_start_usages (shape_entry_key (entry));
		name_table_iter (entry->names, name_entry_write_tld, gclosure);
    }
}

void
shape_entry_write_count(ShapeEntryP entry,
						GenericP gclosure)
{
    ShapeClosureP closure = (ShapeClosureP) gclosure;
	
    if (shape_entry_get_non_empty (entry)) {
		MapTableP  table     = closure->table;
		TDFWriterP writer    = closure->writer;
		MapEntryP  map_entry = map_table_get (table, shape_entry_key (entry));
		unsigned   count     = (map_entry ? map_entry_get_count (map_entry) :
								0);
		NStringP   key       = shape_entry_key (entry);
		
		debug_info_w_count (count, key);
		tdf_write_int (writer, count);
    }
}

void
shape_entry_write_links(ShapeEntryP entry,
						GenericP gclosure)
{
    ShapeClosureP closure = (ShapeClosureP) gclosure;
	
    if (shape_entry_get_non_empty (entry)) {
		MapTableP  table     = closure->table;
		TDFWriterP writer    = closure->writer;
		MapEntryP  map_entry = map_table_get (table, shape_entry_key (entry));
		NStringP   key       = shape_entry_key (entry);
		
		if (map_entry) {
			unsigned num_links = map_entry_get_num_links (map_entry);
			unsigned i;
			
			debug_info_w_start_shape_maps (key, num_links);
			tdf_write_int (writer, num_links);
			for (i = 0; i < num_links; i ++) {
				unsigned internal;
				unsigned external;
				
				map_entry_get_link (map_entry, i , &internal, &external);
				debug_info_w_map (internal, external);
				tdf_write_int (writer, internal);
				tdf_write_int (writer, external);
			}
		} else {
			debug_info_w_start_shape_maps (key, (unsigned) 0);
			tdf_write_int (writer, (unsigned) 0);
		}
    }
}

void
shape_entry_check_multi_defs(ShapeEntryP entry,
							 GenericP gclosure)
{
    NameTableP table = shape_entry_name_table (entry);
    NStringP   key   = shape_entry_key (entry);
	
    UNUSED (gclosure);
    name_table_iter (table, name_entry_check_multi_defs, (GenericP) key);
}

void
shape_entry_do_lib_count(ShapeEntryP entry,
						 GenericP gclosure)
{
    NameTableP table     = shape_entry_name_table (entry);
    unsigned   num_names = 0;
	
    name_table_iter (table, name_entry_do_lib_count, (GenericP) &num_names);
    if (num_names > 0) {
		unsigned *num_shapes_ref = (unsigned *) gclosure;
		
		(*num_shapes_ref) ++;
    }
    entry->num_lib_names = num_names;
}

void
shape_entry_do_lib_write(ShapeEntryP entry,
						 GenericP gclosure)
{
    unsigned num_names = entry->num_lib_names;
	
    if (num_names > 0) {
		TDFWriterP writer = (TDFWriterP) gclosure;
		NameTableP table  = shape_entry_name_table (entry);
		NStringP   key    = shape_entry_key (entry);
		
		debug_info_w_start_shape_index (key, num_names);
		tdf_write_string (writer, shape_entry_key (entry));
		tdf_write_int (writer, num_names);
		name_table_iter (table, name_entry_do_lib_write, gclosure);
    }
}

void
shape_entry_resolve_undefined(ShapeEntryP entry,
							  GenericP gclosure)
{
    ShapeLibClosureP closure   = (ShapeLibClosureP) gclosure;
    NStringP         key       = shape_entry_key (entry);
    ShapeEntryP      lib_entry = shape_table_get (closure->lib_shapes, key);
    NameTableP       table     = ((lib_entry != NIL (ShapeEntryP)) ?
								  shape_entry_name_table (lib_entry) :
								  NIL (NameTableP));
    NameEntryP       name_entry;
	
    while ((name_entry = shape_entry_get_from_list (entry)) !=
		   NIL (NameEntryP)) {
		if (name_entry_resolve_undefined (name_entry, table, closure->units,
										  closure->shapes, key)) {
			closure->did_define = TRUE;
		}
    }
}

void
shape_entry_hide_all_defd(ShapeEntryP entry,
						  GenericP gclosure)
{
    NameTableP table = shape_entry_name_table (entry);
    NStringP   shape = shape_entry_key (entry);
	
    UNUSED (gclosure);
    name_table_iter (table, name_entry_hide_defd, (GenericP) shape);
}

void
shape_entry_suppress_mult(ShapeEntryP entry,
						  GenericP gclosure)
{
    NameTableP table = shape_entry_name_table (entry);
    NStringP   shape = shape_entry_key (entry);
	
    UNUSED (gclosure);
    name_table_iter (table, name_entry_suppress_mult, (GenericP) shape);
}

void
shape_entry_lib_suppress_mult(ShapeEntryP entry,
							  GenericP gclosure)
{
    NameTableP table = shape_entry_name_table (entry);
    NStringP   shape = shape_entry_key (entry);
	
    UNUSED (gclosure);
    name_table_iter (table, name_entry_lib_suppress_mult, (GenericP) shape);
}

void
shape_entry_show_content(ShapeEntryP entry,
						 GenericP gclosure)
{
    UNUSED (gclosure);
    write_nstring (ostream_output, shape_entry_key (entry));
    write_char (ostream_output, ':');
    write_newline (ostream_output);
    name_table_iter (shape_entry_name_table (entry), name_entry_show_content,
					 NIL (GenericP));
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
 **/
