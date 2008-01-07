/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.ten15.org/>
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


/*** rule-mutate.c --- Compute mutation effects.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the functions that compute the propogation of mutation
 * effects from actions that mutate their parameters.
 */

/****************************************************************************/

#include "rule.h"
#include "action.h"
#include "types.h"

/*--------------------------------------------------------------------------*/

static void	rule_compute_mutations_3(EntryP, void *);

static void
rule_compute_mutations_4(RuleP rule, AltP alt,
						 RuleP from_rule)
{
	BoolT  propogate = FALSE;
	ItemP  item;
	
	for (item = alt_item_head (alt); item; item = item_next (item)) {
		switch (item_type (item)) EXHAUSTIVE {
		case ET_RULE:
			if (entry_get_rule (item_entry (item)) == from_rule) {
				if (types_compute_mutations (rule_param (rule),
											 item_param (item),
											 rule_param (from_rule))) {
					propogate = TRUE;
				}
			}
			break;
		case ET_ACTION:
		case ET_PREDICATE:
		case ET_RENAME:
		case ET_BASIC:
			break;
		case ET_NON_LOCAL:
		case ET_TYPE:
		case ET_NAME:
			UNREACHED;
		}
	}
	if (propogate) {
		entry_list_iter (rule_reverse_list (rule), rule_compute_mutations_3,
						 (void *) rule);
	}
}

static void
rule_compute_mutations_3(EntryP entry, void *gclosure)
{
	RuleP rule      = entry_get_rule (entry);
	RuleP from_rule = (RuleP) gclosure;
	AltP  alt;
	
	if ((alt = rule_get_handler (rule)) != NIL (AltP)) {
		rule_compute_mutations_4 (rule, alt, from_rule);
	}
	for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
		rule_compute_mutations_4 (rule, alt, from_rule);
	}
}

static void
rule_compute_mutations_2(RuleP rule, AltP alt)
{
	BoolT   propogate = FALSE;
	ItemP   item;
	ActionP action;
	
	for (item = alt_item_head (alt); item; item = item_next (item)) {
		switch (item_type (item)) EXHAUSTIVE {
		case ET_ACTION:
		case ET_PREDICATE:
			action = entry_get_action (item_entry (item));
			if (types_compute_mutations (rule_param (rule), item_param (item),
										 action_param (action))) {
				propogate = TRUE;
			}
			break;
		case ET_RENAME:
		case ET_BASIC:
		case ET_RULE:
			break;
		case ET_NON_LOCAL:
		case ET_TYPE:
		case ET_NAME:
			UNREACHED;
		}
		if (types_compute_assign_mutations (rule_param (rule),
											item_param (item))) {
			propogate = TRUE;
		}
	}
	if (propogate) {
		entry_list_iter (rule_reverse_list (rule), rule_compute_mutations_3,
						 (void *) rule);
	}
}

static void
rule_compute_mutations_1(RuleP rule)
{
	AltP alt;
	
	if ((alt = rule_get_handler (rule)) != NIL (AltP)) {
		rule_compute_mutations_2 (rule, alt);
	}
	for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
		rule_compute_mutations_2 (rule, alt);
	}
}

/*--------------------------------------------------------------------------*/

void
rule_compute_mutations(EntryP entry, void *gclosure)
{
	UNUSED (gclosure);
	if (entry_is_rule (entry)) {
		RuleP rule = entry_get_rule (entry);
		
		rule_compute_mutations_1 (rule);
	}
}
