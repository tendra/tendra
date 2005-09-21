/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


/*** name-key.c --- External name key ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the external name key routines used by the TDF linker.
 *
 *** Change Log:*/

/****************************************************************************/

#include "msgcat.h"

#include "name-key.h"
#include "syntax.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

static BoolT
name_key_parse_hex_char(char *name, char *c_ref)
{
    char result;
    char c;
    int  value;

    if ((c = name [0]), ((value = syntax_value (c)) != SYNTAX_NO_VALUE)) {
		result = (char) ((unsigned) value << 4);
    } else {
		return (FALSE);
    }
    if ((c = name [1]), ((value = syntax_value (c)) != SYNTAX_NO_VALUE)) {
		result |= (char) value;
    } else {
		return (FALSE);
    }
    *c_ref = result;
    return (TRUE);
}

static BoolT
name_key_parse_escaped(char **name_ref, char *c_ref)
{
    char *name = (*name_ref);

    switch ((*++ name)) {
	case 'x': case 'X':
		if (!name_key_parse_hex_char (name, c_ref)) {
			return (FALSE);
		}
		name += 3;
		break;
	case 'n': case 'N':
		*c_ref = '\n';
		name ++;
		break;
	case 'r': case 'R':
		*c_ref = '\r';
		name ++;
		break;
	case 't': case 'T':
		*c_ref= '\t';
		name ++;
		break;
	case '0':
		*c_ref = '\0';
		name ++;
		break;
	case '\\': case '.': case '[': case ']':
		*c_ref = *name ++;
		break;
	default:
		return (FALSE);
    }
    *name_ref = name;
    return (TRUE);
}

static BoolT
name_key_parse_cstring_unique(NameKeyP key, char *name)
{
    unsigned length   = 1;
    char *tmp_name = name;
    NStringP components;
    unsigned i;

    while (*++ tmp_name) {
		if (*tmp_name == '.') {
			length ++;
		}
    }
    components = ALLOCATE_VECTOR (NStringT, length);
    length     = 0;
    for (;;) {
		DStringT dstring;

		name ++;
		dstring_init (&dstring);
		while ((*name != '.') && (*name != ']')) {
			if ((*name == '\0') || (*name == '[')) {
				dstring_destroy (&dstring);
				goto fail;
			} else if (*name == '\\') {
				char c;

				if (name_key_parse_escaped (&name, &c)) {
					dstring_append_char (&dstring, c);
				} else {
					dstring_destroy (&dstring);
					goto fail;
				}
			} else {
				dstring_append_char (&dstring, *name ++);
			}
		}
		dstring_to_nstring (&dstring, &(components [length ++]));
		if (*name == ']') {
			break;
		}
    }
    if (*name) {
      fail:
		for (i = 0; i < length ; i ++) {
			nstring_destroy (&(components [i]));
		}
		DEALLOCATE (components);
		return (FALSE);
    }
    name_key_init_unique (key, length);
    for (i = 0; i < length; i ++) {
		name_key_set_component (key, i, &(components [i]));
    }
    DEALLOCATE (components);
    return (TRUE);
}

static BoolT
name_key_parse_cstring_string(NameKeyP key, char *name)
{
    DStringT dstring;
    NStringT nstring;

    dstring_init (&dstring);
    while (*name) {
		if ((*name == '[') || (*name == ']') || (*name == '.')) {
			dstring_destroy (&dstring);
			return (FALSE);
		} else if (*name == '\\') {
			char c;

			if (name_key_parse_escaped (&name, &c)) {
				dstring_append_char (&dstring, c);
			} else {
				dstring_destroy (&dstring);
				return (FALSE);
			}
		} else {
			dstring_append_char (&dstring, *name ++);
		}
    }
    dstring_to_nstring (&dstring, &nstring);
    name_key_init_string (key, &nstring);
    return (TRUE);
}

static void
write_name_key_1(OStreamP ostream, NStringP nstring)
{
    unsigned length = nstring_length (nstring);
    char *bytes = nstring_contents (nstring);

    while (length --) {
		switch (*bytes) {
		case '[': case ']': case '.': case '\\':
			write_char (ostream, '\\');
			FALL_THROUGH;
		default:
			write_char (ostream, *bytes);
		}
		bytes ++;
    }
}

/*--------------------------------------------------------------------------*/

void
name_key_init_string(NameKeyP key, NStringP string)
{
    key->type = KT_STRING;
    nstring_assign (&(key->u.string), string);
}

void
name_key_init_unique(NameKeyP key, unsigned components)
{
    key->type                = KT_UNIQUE;
    key->u.unique.length     = components;
    key->u.unique.components = ALLOCATE_VECTOR (NStringT, components);
}

BoolT
name_key_parse_cstring(NameKeyP key, char *name)
{
    if (*name == '[') {
		return (name_key_parse_cstring_unique (key, name));
    } else {
		return (name_key_parse_cstring_string (key, name));
    }
}

void
name_key_set_component(NameKeyP key, unsigned component, NStringP string)
{
    ASSERT ((key->type == KT_UNIQUE) && (component < key->u.unique.length));
    nstring_assign (&(key->u.unique.components [component]), string);
}

NameKeyTypeT
name_key_type(NameKeyP key)
{
    return (key->type);
}

NStringP
name_key_string(NameKeyP key)
{
    ASSERT (key->type == KT_STRING);
    return (&(key->u.string));
}

unsigned
name_key_components(NameKeyP key)
{
    ASSERT (key->type == KT_UNIQUE);
    return (key->u.unique.length);
}

NStringP
name_key_get_component(NameKeyP key, unsigned component)
{
    ASSERT ((key->type == KT_UNIQUE) && (component < key->u.unique.length));
    return (&(key->u.unique.components [component]));
}

unsigned
name_key_hash_value(NameKeyP key)
{
#ifdef __TenDRA__
    unsigned hash_value; /* "tcc" complains if this is initialised */
#else
    unsigned hash_value = 0; /* "gcc" complains if this is not initialised */
#endif /* defined (__TenDRA__) */
    unsigned components;
    unsigned i;

    switch (key->type) EXHAUSTIVE {
	case KT_STRING:
		hash_value = nstring_hash_value (&(key->u.string));
		break;
	case KT_UNIQUE:
		components = key->u.unique.length;
		hash_value = components;
		for (i = 0; i < components; i ++) {
			hash_value += nstring_hash_value (&(key->u.unique.components [i]));
		}
		break;
    }
    return (hash_value);
}

BoolT
name_key_equal(NameKeyP key1, NameKeyP key2)
{
    unsigned components;
    unsigned i;

    if (key1->type != key2->type) {
		return (FALSE);
    }
    switch (key1->type) EXHAUSTIVE {
	case KT_STRING:
		return (nstring_equal (&(key1->u.string), &(key2->u.string)));
	case KT_UNIQUE:
		if ((components = key1->u.unique.length) != key2->u.unique.length) {
			return (FALSE);
		}
		for (i = 0; i < components; i ++) {
			if (!nstring_equal (&(key1->u.unique.components [i]),
								&(key2->u.unique.components [i]))) {
				return (FALSE);
			}
		}
		break;
    }
    return (TRUE);
}

void
name_key_assign(NameKeyP to, NameKeyP from)
{
    switch (to->type = from->type) EXHAUSTIVE {
	case KT_STRING:
		nstring_assign (&(to->u.string), &(from->u.string));
		break;
	case KT_UNIQUE:
		to->u.unique.length     = from->u.unique.length;
		to->u.unique.components = from->u.unique.components;
		break;
    }
}

void
name_key_copy(NameKeyP to, NameKeyP from)
{
    unsigned components;
    unsigned i;

    switch (to->type = from->type) EXHAUSTIVE {
	case KT_STRING:
		nstring_copy (&(to->u.string), &(from->u.string));
		break;
	case KT_UNIQUE:
		components = to->u.unique.length = from->u.unique.length;
		to->u.unique.components = ALLOCATE_VECTOR (NStringT, components);
		for (i = 0; i < components; i ++) {
			nstring_copy (&(to->u.unique.components [i]),
						  &(from->u.unique.components [i]));
		}
		break;
    }
}

void
name_key_destroy(NameKeyP key)
{
    unsigned components;
    unsigned i;

    switch (key->type) EXHAUSTIVE {
	case KT_STRING:
		nstring_destroy (&(key->u.string));
		break;
	case KT_UNIQUE:
		components = key->u.unique.length;
		for (i = 0; i < components; i ++) {
			nstring_destroy (&(key->u.unique.components [i]));
		}
		DEALLOCATE (key->u.unique.components);
		break;
    }
}

void
write_name_key(OStreamP ostream, NameKeyP key)
{
    char     sep = '[';
    unsigned components;
    unsigned i;

    switch (key->type) EXHAUSTIVE {
	case KT_STRING:
		write_name_key_1 (ostream, &(key->u.string));
		break;
	case KT_UNIQUE:
		components = key->u.unique.length;
		for (i = 0; i < components; i ++) {
			NStringP nstring = &(key->u.unique.components [i]);

			write_char (ostream, sep);
			write_name_key_1 (ostream, nstring);
			sep = '.';
		}
		write_char (ostream, ']');
		break;
    }
}

/*--------------------------------------------------------------------------*/

void
name_key_list_init(NameKeyListP list)
{
    list->head = NIL (NameKeyListEntryP);
}

void
name_key_list_add(NameKeyListP list, NameKeyP key)
{
    NameKeyListEntryP entry;

    for (entry = name_key_list_head (list); entry;
		 entry = name_key_list_entry_next (entry)) {
		if (name_key_equal (key, &(entry->key))) {
			name_key_destroy (key);
			return;
		}
    }
    entry       = ALLOCATE (NameKeyListEntryT);
    entry->next = list->head;
    name_key_assign (&(entry->key), key);
    list->head  = entry;
}

NameKeyListEntryP
name_key_list_head(NameKeyListP list)
{
    return (list->head);
}

NameKeyP
name_key_list_entry_key(NameKeyListEntryP entry)
{
    return (&(entry->key));
}

NameKeyListEntryP
name_key_list_entry_next(NameKeyListEntryP entry)
{
    return (entry->next);
}

/*--------------------------------------------------------------------------*/

void
name_key_pair_list_init(NameKeyPairListP list)
{
    list->head = NIL (NameKeyPairListEntryP);
}

BoolT
name_key_pair_list_add(NameKeyPairListP list, NameKeyP from, NameKeyP to)
{
    NameKeyPairListEntryP entry;

    for (entry = name_key_pair_list_head (list); entry;
		 entry = name_key_pair_list_entry_next (entry)) {
		if (name_key_equal (from, &(entry->from))) {
			return (FALSE);
		}
    }
    entry       = ALLOCATE (NameKeyPairListEntryT);
    entry->next = list->head;
    name_key_assign (&(entry->from), from);
    name_key_assign (&(entry->to), to);
    list->head  = entry;
    return (TRUE);
}

NameKeyPairListEntryP
name_key_pair_list_head(NameKeyPairListP list)
{
    return (list->head);
}

NameKeyP
name_key_pair_list_entry_from(NameKeyPairListEntryP entry)
{
    return (&(entry->from));
}

NameKeyP
name_key_pair_list_entry_to(NameKeyPairListEntryP entry)
{
    return (&(entry->to));
}

NameKeyPairListEntryP
name_key_pair_list_entry_next(NameKeyPairListEntryP entry)
{
    return (entry->next);
}
