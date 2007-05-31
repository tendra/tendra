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
 * alt.c - Alternative ADT.
 *
 * This file implements the alternative manipulation routines.  They are
 * specified in the file "rule.h".
 */

#include "rule.h"
#include "../action.h"
#include "../basic.h"
#include "../name.h"
#include "../type.h"

AltT *
alt_create(void)
{
    AltT * alt = ALLOCATE(AltT);

    alt->next      = NULL;
    types_init(alt_names(alt));
    bitvec_init(alt_first_set(alt));
    alt->item_head = NULL;
    alt->item_tail = &(alt->item_head);
    return(alt);
}

AltT *
alt_create_merge(ItemT * initial_item, ItemT * trailing_item,
		 TypeTransT * translator, TableT * table)
{
    AltT * alt = alt_create();

    for (; initial_item; initial_item = item_next(initial_item)) {
	ItemT * new_item = item_duplicate_and_translate(initial_item, translator,
						      table);

	alt_add_item(alt, new_item);
    }
    for (; trailing_item; trailing_item = item_next(trailing_item)) {
	ItemT * new_item = item_duplicate(trailing_item);

	alt_add_item(alt, new_item);
    }
    return(alt);
}

AltT *
alt_duplicate(AltT * alt)
{
    AltT *  new_alt = alt_create();
    ItemT * item;

    for (item = alt_item_head(alt); item; item = item_next(item)) {
	ItemT * new_item = item_duplicate(item);

	alt_add_item(new_alt, new_item);
    }
    return(new_alt);
}

BoolT
alt_less_than(AltT * alt1, AltT * alt2)
{
    ItemT *      item1 = alt_item_head(alt1);
    ItemT *      item2 = alt_item_head(alt2);
    KeyT *       key1;
    KeyT *       key2;
    TypeTupleT * type1;
    TypeTupleT * type2;

    if (item_type(item1) < item_type(item2)) {
	return(TRUE);
    } else if (item_type(item1) > item_type(item2)) {
	return(FALSE);
    }
    key1 = entry_key(item_entry(item1));
    key2 = entry_key(item_entry(item2));
    switch (key_compare(key1, key2)) EXHAUSTIVE {
      case CMP_LT:
	return(TRUE);
      case CMP_GT:
	return(FALSE);
      case CMP_EQ:
	break;
    }
    type1 = item_param(item1);
    type2 = item_param(item2);
    switch (types_compare(type1, type2)) EXHAUSTIVE {
      case CMP_LT:
	return(TRUE);
      case CMP_GT:
	return(FALSE);
      case CMP_EQ:
	break;
    }
    type1 = item_result(item1);
    type2 = item_result(item2);
    switch (types_compare(type1, type2)) EXHAUSTIVE {
      case CMP_LT:
	return(TRUE);
      case CMP_GT:
	return(FALSE);
      case CMP_EQ:
	break;
    }
    UNREACHED;
}

BoolT
alt_equal(AltT * alt1, AltT * alt2)
{
    ItemT * item1;
    ItemT * item2;

    if ((alt1 == NULL) && (alt2 == NULL)) {
	return(TRUE);
    } else if ((alt1 == NULL) || (alt2 == NULL)) {
	return(FALSE);
    }
    item1 = alt_item_head(alt1);
    item2 = alt_item_head(alt2);
    while (item1 && item2) {
	if ((item_entry(item1) == item_entry(item2)) &&
	    (types_equal_numbers(item_param(item1), item_param(item2))) &&
	    (types_equal_numbers(item_result(item1), item_result(item2)))) {
	    item1 = item_next(item1);
	    item2 = item_next(item2);
	} else {
	    return(FALSE);
	}
    }
    return(item1 == item2);
}

AltT *
alt_next(AltT * alt)
{
    return(alt->next);
}

AltT * *
alt_next_ref(AltT * alt)
{
    return(&(alt->next));
}

void
alt_set_next(AltT * alt1, AltT * alt2)
{
    alt1->next = alt2;
}

TypeTupleT *
alt_names(AltT * alt)
{
    return(&(alt->names));
}

BitVecT *
alt_first_set(AltT * alt)
{
    return(&(alt->first_set));
}

ItemT *
alt_item_head(AltT * alt)
{
    return(alt->item_head);
}

ItemT *
alt_unlink_item_head(AltT * alt)
{
    ItemT * item = alt_item_head(alt);

    alt->item_head = item_next(item);
    item_set_next(item, NULL);
    if (alt->item_tail == item_next_ref(item)) {
	alt->item_tail = &(alt->item_head);
    }
    return(item);
}

void
alt_add_item(AltT * alt, ItemT * item)
{
    *(alt->item_tail) = item;
    alt->item_tail    = item_next_ref(item);
}

AltT *
alt_deallocate(AltT * alt)
{
    AltT *  next = alt_next(alt);
    ItemT * item;

    for (item = alt_item_head(alt); item; item = item_deallocate(item)) {
	/*NOTHING*/
    }
    types_destroy(alt_names(alt));
    bitvec_destroy(alt_first_set(alt));
    DEALLOCATE(alt);
    return(next);
}

void
write_alt(OStreamT * ostream, AltT * alt)
{
    ItemT * item;

    for (item = alt_item_head(alt); item; item = item_next(item)) {
	write_tab(ostream);
	write_item(ostream, item);
	write_newline(ostream);
    }
}

void
write_alt_highlighting(OStreamT * ostream, AltT * alt, ItemT * highlight)
{
    ItemT * item;

    for (item = alt_item_head(alt); item; item = item_next(item)) {
	if (item == highlight) {
	    write_cstring(ostream, "==>>");
	}
	write_tab(ostream);
	write_item(ostream, item);
	write_newline(ostream);
    }
}
