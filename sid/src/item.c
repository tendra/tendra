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
 * item.c - Item ADT.
 *
 * This file implements the item manipulation routines.  These are specified
 * in the file "rule.h".
 */

#include <assert.h>

#include "rule.h"
#include "action.h"
#include "basic.h"
#include "name.h"
#include "type.h"

ItemP
item_create(EntryP entry)
{
    ItemP item = ALLOCATE(ItemT);

    item->next         = NULL;
    types_init(item_param(item));
    types_init(item_result(item));
    item->type         = entry_type(entry);
    item->entry        = entry;
    item->inlinable    = FALSE;
    item->tail_call    = FALSE;
    return(item);
}

ItemP
item_duplicate(ItemP item)
{
    ItemP new_item = ALLOCATE(ItemT);

    new_item->next         = NULL;
    types_copy(item_param(new_item), item_param(item));
    types_copy(item_result(new_item), item_result(item));
    new_item->type         = item->type;
    new_item->entry        = item->entry;
    new_item->inlinable    = item->inlinable;
    new_item->tail_call    = item->tail_call;
    return(new_item);
}

ItemP
item_duplicate_and_translate(ItemP item, TypeTransP translator, TableP table)
{
    ItemP new_item = ALLOCATE(ItemT);

    new_item->next         = NULL;
    types_copy_and_translate(item_param(new_item), item_param(item),
			      translator, table);
    types_copy_and_translate(item_result(new_item), item_result(item),
			      translator, table);
    new_item->type         = item->type;
    new_item->entry        = item->entry;
    new_item->inlinable    = item->inlinable;
    new_item->tail_call    = item->tail_call;
    return(new_item);
}

void
item_translate_list(ItemP item, TypeBTransP translator)
{
    for (; item; item = item_next(item)) {
	types_translate(item_param(item), translator);
	types_translate(item_result(item), translator);
    }
}

void
item_to_predicate(ItemP item)
{
    assert(item_is_action(item));
    item->type = ET_PREDICATE;
}

ItemP
item_next(ItemP item)
{
    return(item->next);
}

ItemP *
item_next_ref(ItemP item)
{
    return(&(item->next));
}

void
item_set_next(ItemP item1, ItemP item2)
{
    item1->next = item2;
}

EntryP
item_entry(ItemP item)
{
    return(item->entry);
}

void
item_set_entry(ItemP item, EntryP entry)
{
    item->entry = entry;
}

EntryTypeT
item_type(ItemP item)
{
    return(item->type);
}

BoolT
item_is_rule(ItemP item)
{
    return(item->type == ET_RULE);
}

BoolT
item_is_action(ItemP item)
{
    return(item->type == ET_ACTION);
}

BoolT
item_is_predicate(ItemP item)
{
    return(item->type == ET_PREDICATE);
}

BoolT
item_is_basic(ItemP item)
{
    return(item->type == ET_BASIC);
}

BoolT
item_is_rename(ItemP item)
{
    return(item->type == ET_RENAME);
}

TypeTupleP
item_param(ItemP item)
{
    return(&(item->param));
}

void
item_add_param(ItemP item, TypeTupleP param)
{
    types_assign(item_param(item), param);
}

TypeTupleP
item_result(ItemP item)
{
    return(&(item->result));
}

void
item_add_result(ItemP item, TypeTupleP result)
{
    types_assign(item_result(item), result);
}

BoolT
item_is_inlinable(ItemP item)
{
    return(item->inlinable);
}

void
item_inlinable(ItemP item)
{
    item->inlinable = TRUE;
}

BoolT
item_is_tail_call(ItemP item)
{
    return(item->tail_call);
}

void
item_tail_call(ItemP item)
{
    item->tail_call = TRUE;
}

BoolT
item_names_used_in_list(ItemP item, TypeTupleP names)
{
    while (item) {
	if ((types_intersect(item_param(item), names)) ||
	    (types_intersect(item_result(item), names))) {
	    return(TRUE);
	}
	item = item_next(item);
    }
    return(FALSE);
}

void
item_compute_minimal_dataflow(ItemP item, TypeTupleP used)
{
    if (item) {
	ItemP next = item_next(item);

	if (next) {
	    item_compute_minimal_dataflow(next, used);
	}
	if (item_is_inlinable(item)) {
	    RuleP rule = entry_get_rule(item_entry(item));

	    types_inplace_intersection(item_result(item), used);
	    types_inplace_intersection(rule_result(rule), used);
	    rule_compute_minimal_dataflow(rule, item_param(item));
	}
	types_add_new_names(used, item_param(item), NULL);
    }
}

ItemP
item_deallocate(ItemP item)
{
    ItemP next = item_next(item);

    types_destroy(item_param(item));
    types_destroy(item_result(item));
    DEALLOCATE(item);
    return(next);
}

void
write_item(OStreamP ostream, ItemP item)
{
    EntryP entry = item_entry(item);

    write_type_names(ostream, item_result(item), TRUE);
    if (item_is_predicate(item)) {
	write_cstring(ostream, " ?");
    }
    write_cstring(ostream, " = ");
    switch (item_type(item))EXHAUSTIVE {
      case ET_ACTION:
      case ET_PREDICATE:
	write_char(ostream, '<');
	write_key(ostream, entry_key(entry));
	write_cstring(ostream, "> ");
	break;
      case ET_RULE:
	if (item_is_inlinable(item)) {
	    if (item_is_tail_call(item)) {
		write_char(ostream, '*');
	    } else {
		write_char(ostream, '+');
	    }
	}
	FALL_THROUGH;
      case ET_BASIC:
	write_key(ostream, entry_key(item_entry(item)));
	write_char(ostream, ' ');
	break;
      case ET_RENAME:
	break;
      case ET_NON_LOCAL:
      case ET_NAME:
      case ET_TYPE:
	UNREACHED;
    }
    write_type_names(ostream, item_param(item), TRUE);
    write_char(ostream, ';');
}
