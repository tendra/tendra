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
 * This file implements the SID transformation front-end routines.
 */

#ifndef H_GRAMMAR
#define H_GRAMMAR

#include "adt/entry.h"
#include "adt/entry-list.h"
#include <exds/ostream.h>
#include "adt/table.h"
#include "adt/types.h"

typedef struct GrammarT {
	/*
	 * The table acts as storage for:
	 *
	 *  - Types in the %types% section of the .sid file
	 *
	 *  - Terminals existing in the %terminals% section of the .sid file
	 *
	 *  - Rules defined in the %productions% section of the .sid file
	 *
	 *  - Actions declared in the %production% section of the .sid file,
	 *    and defined in the .act file.
	 *
	 *  - Local variables in a rule. This contains scope information.
	 *
	 *  - Non-local variables. TODO: clarify
	 */
    TableT			table;

	/*
	 * The starting points (yes, it's plural) of the grammar.
	 */
    EntryListT			entry_list;

	/*
	 * The number of terminals.
	 *
	 * Terminals are numbered from 0 to .terminal - 1. The value of
	 * .terminal is primarily [TODO only?] used while parsing the * .sid file
	 * to tell each newly constructed terminal which number it should hold.
	 * See the BasicT type.
	 */
    unsigned			terminal;

	/*
	 * A pointer to an EntryT preexisting in .table. This EntryT indicates the
	 * boolean type. There can only be one boolean type. It is set when SID
	 * first encounters a predicate function.
	 */
    EntryT *			predicate_type;

	/*
	 * Points to an automatically generated entry in .table.
	 *
	 * This internallyrepresents the predicate indicator '?' in a left hand
	 * side name tuple in the .sid grammar file. For eample, in a .sid file:
	 *
	 *  a = <non-predicate>
	 *  ? = <predicate-function>
	 *
	 * There must be a representation of 'a' and '?'. 'a' is a local or
	 * non-local name represented by an EntryT in .table, and '?' must also
	 * have an EntryT in .table. This EntryT in .table is pointed to by
	 * .predicate_id.
	 */
    EntryT *			predicate_id;
} GrammarT, *GrammarP;

extern void		grammar_init(GrammarT *);
extern TableT *		grammar_table(GrammarT *);
extern EntryListT *	grammar_entry_list(GrammarT *);
extern unsigned		grammar_max_terminal(GrammarT *);
extern unsigned		grammar_next_terminal(GrammarT *);
extern EntryT *		grammar_get_predicate_type(GrammarT *);
extern void		grammar_set_predicate_type(GrammarT *, EntryT *);
extern EntryT *		grammar_get_predicate_id(GrammarT *);


/*
 * Before any of these routines are called, the grammar should have been read
 * in by the parser.  The functions should be called in the following order:
 */

/*
 * This function traces the grammar that is accessible from the entry points,
 * and ensures that there are no unused rules, basics, actions or types, and
 * that all of the rules are defined.
 */
extern void		grammar_check_complete(GrammarT *);

/*
 * This function applies several functions from the file "rule.c" to the rules
 * in the grammar, to detect left cycles (this is done by the
 * "grammar_find_cycles" function).  When such a cycle is found, it calls
 * rule_remove_left_cycle() (defined in the file "rule-lre.c") to remove the
 * cycle.  The function removes any left recursion from the rules, replacing
 * it with a right recursive equivalent.  See the file "rule-lre.c" for more
 * details.
 *
 * The cycle detection algorithm works as follows: firstly a list of rules is
 * built by the function()`rule_build_root_list(); this list acts as the root
 * node of the graph.  The remainder of the graph is built up from the
 * leftmost rule invocations (if any) in each alternative of each production.
 * This graph is depth first searched by the function ``rule_compute_dfs'', to
 * produce an ordered list of productions.  The reverse graph (which is
 * computed by applying the function ``rule_compute_reverse_list'' to each
 * production, at the same time as the dfs is being performed) is then depth
 * first searched in the order specified by the list, using the function
 * rule_compute_reverse_dfs().  The result of this is the set of left
 * cycles.  The algorithm is explained fully in {"Data Structures and
 * Algorithms"; Aho, Hopcroft, Ullman; Addison Wesley; ISBN 0-201-00023-7;
 * page 222}.
 */
extern void		grammar_remove_left_recursion(GrammarT *);

/*
 * This function applies the rule_compute_first_set() function to all rules
 * in the grammar.  The function computes the first set for each rule.  It
 * also computes a priority for the rule, and whether the rule is see through
 * or not.  See the file "rule-first.c" for more details.
 */
extern void		grammar_compute_first_sets(GrammarT *);

/*
 * This function applies the rule_factor() function to all of the rules in
 * the grammar.  The function does a number of transformations on the rules to
 * make them more likely to be LL(1).  See the file "rule-factor.c" for more
 * details.
 */
extern void		grammar_factor(GrammarT *);

/*
 * This function calls the rule_remove_duplicates() function on the grammar,
 * to remove any rules that have identical form.  See the file "rule-simp.c"
 * for more details.
 */
extern void		grammar_simplify(GrammarT *);

/*
 * This function applies a number of functions to the rules in the grammar in
 * order to indicate which rules should be inlined during the output phase.
 * See the file "rule-tail.c" for more details.
 */
extern void		grammar_compute_inlining(GrammarT *);

/*
 * This function applies a number of functions to the rules in the grammar in
 * order to check that the grammar is valid.  It also causes the first sets
 * for all of the alternatives within a rule to be calculated, and if there is
 * a see through alternative.  See the file "rule-check.c" for more details.
 */
extern void		grammar_check_collisions(GrammarT *);

/*
 * This function applies the rule_recompute_alt_names() function to all
 * rules in the grammar.  The function recomputes the identifier names that
 * are used within each alternative of the rule.  See the file "rule-names.c"
 * for more details.
 */
extern void		grammar_recompute_alt_names(GrammarT *);

/*
 * This function applies the rule_compute_mutations() function to all rules
 * in the grammar.  The function computes the mutation effects from actions
 * that mutate their parameters.  See the file "rule-mutate.c" for more
 * details.
 */
extern void		grammar_compute_mutations(GrammarT *);

extern void		write_grammar(OStreamT *, GrammarT *);

#endif /* !defined (H_GRAMMAR) */

