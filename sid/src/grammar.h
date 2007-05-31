/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
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

/*
 * grammar.h - Grammar transforms frontend.
 *
 * See the file "grammar.c" for more information.
 *
 */

#ifndef H_GRAMMAR
#define H_GRAMMAR

#include "os-interface.h"
#include "entry.h"
#include "entry-list.h"
#include "ostream.h"
#include "table.h"
#include "types.h"

typedef struct GrammarT {
    TableT			table;
    EntryListT			entry_list;
    unsigned			terminal;
    EntryT *			predicate_type;
    EntryT *			predicate_id;
} GrammarT;

extern void		grammar_init(GrammarT *);
extern TableT *		grammar_table(GrammarT *);
extern EntryListT *	grammar_entry_list(GrammarT *);
extern unsigned		grammar_max_terminal(GrammarT *);
extern unsigned		grammar_next_terminal(GrammarT *);
extern EntryT *		grammar_get_predicate_type(GrammarT *);
extern void		grammar_set_predicate_type(GrammarT *, EntryT *);
extern EntryT *		grammar_get_predicate_id(GrammarT *);
extern void		grammar_check_complete(GrammarT *);
extern void		grammar_remove_left_recursion(GrammarT *);
extern void		grammar_compute_first_sets(GrammarT *);
extern void		grammar_factor(GrammarT *);
extern void		grammar_simplify(GrammarT *);
extern void		grammar_compute_inlining(GrammarT *);
extern void		grammar_check_collisions(GrammarT *);
extern void		grammar_recompute_alt_names(GrammarT *);
extern void		grammar_compute_mutations(GrammarT *);

extern void		write_grammar(OStreamT *, GrammarT *);

#endif /* !defined (H_GRAMMAR) */
