/*
 * Copyright (c) 2002, 2003, 2004 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * This code is derived from software contributed to The TenDRA Project by
 * Jeroen Ruigrok van der Werven.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/*** grammar.h --- Grammar transforms frontend.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "grammar.c" for more information.
 *
 *** Change Log:
 * $Log: grammar.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:58:15  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:34  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_GRAMMAR
#define H_GRAMMAR

#include "os-interface.h"
#include "entry.h"
#include "entry-list.h"
#include "ostream.h"
#include "table.h"
#include "types.h"

/*--------------------------------------------------------------------------*/

typedef struct GrammarT {
    TableT			table;
    EntryListT			entry_list;
    unsigned			terminal;
    EntryP			predicate_type;
    EntryP			predicate_id;
} GrammarT, *GrammarP;

/*--------------------------------------------------------------------------*/

extern void		grammar_init(GrammarP);
extern TableP		grammar_table(GrammarP);
extern EntryListP	grammar_entry_list(GrammarP);
extern unsigned		grammar_max_terminal(GrammarP);
extern unsigned		grammar_next_terminal(GrammarP);
extern EntryP		grammar_get_predicate_type(GrammarP);
extern void		grammar_set_predicate_type(GrammarP, EntryP);
extern EntryP		grammar_get_predicate_id(GrammarP);
extern void		grammar_check_complete(GrammarP);
extern void		grammar_remove_left_recursion(GrammarP);
extern void		grammar_compute_first_sets(GrammarP);
extern void		grammar_factor(GrammarP);
extern void		grammar_simplify(GrammarP);
extern void		grammar_compute_inlining(GrammarP);
extern void		grammar_check_collisions(GrammarP);
extern void		grammar_recompute_alt_names(GrammarP);
extern void		grammar_compute_mutations(GrammarP);

extern void		write_grammar(OStreamP, GrammarP);

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define grammar_table(g)			(&((g) ->table))
#define grammar_entry_list(g)			(&((g) ->entry_list))
#define grammar_max_terminal(g)			((g) ->terminal)
#define grammar_get_predicate_type(g)		((g) ->predicate_type)
#define grammar_set_predicate_type(g, t)	((g) ->predicate_type = (t))
#define grammar_get_predicate_id(g)		((g) ->predicate_id)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_GRAMMAR) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
