/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
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


/*** name-key.c --- External name key ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the external name key routines used by the TDF linker.
 *
 *** Change Log:
 * $Log: name-key.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:19  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:39:28  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:46:38  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:35  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "name-key.h"
#include "../syntax.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

static BoolT
name_key_parse_hex_char(char * name,				 char    *c_ref)
{
    char result;
    char c;
    int  value;

    if ((c = name[0]), ((value = syntax_value(c)) != SYNTAX_NO_VALUE)) {
	result = (char)((unsigned)value << 4);
    } else {
	return(FALSE);
    }
    if ((c = name[1]), ((value = syntax_value(c)) != SYNTAX_NO_VALUE)) {
	result |= (char)value;
    } else {
	return(FALSE);
    }
    *c_ref = result;
    return(TRUE);
}

static BoolT
name_key_parse_escaped(char * *name_ref,				char     *c_ref)
{
    char * name = (*name_ref);

    switch ((*++name)) {
      case 'x': case 'X':
	if (!name_key_parse_hex_char(name, c_ref)) {
	    return(FALSE);
	}
	name += 3;
	break;
      case 'n': case 'N':
	*c_ref = '\n';
	name++;
	break;
      case 'r': case 'R':
	*c_ref = '\r';
	name++;
	break;
      case 't': case 'T':
	*c_ref= '\t';
	name++;
	break;
      case '0':
	*c_ref = '\0';
	name++;
	break;
      case '\\': case '.': case '[': case ']':
	*c_ref = *name++;
	break;
      default:
	return(FALSE);
    }
    *name_ref = name;
    return(TRUE);
}

static BoolT
name_key_parse_cstring_unique(NameKeyT *key,				       char * name)
{
    unsigned length   = 1;
    char * tmp_name = name;
    NStringT *components;
    unsigned i;

    while (*++tmp_name) {
	if (*tmp_name == '.') {
	    length++;
	}
    }
    components = ALLOCATE_VECTOR(NStringT, length);
    length     = 0;
    for (;;) {
	DStringT dstring;

	name++;
	dstring_init(&dstring);
	while ((*name != '.') && (*name != ']')) {
	    if ((*name == '\0') || (*name == '[')) {
		dstring_destroy(&dstring);
		goto fail;
	    } else if (*name == '\\') {
		char c;

		if (name_key_parse_escaped(&name, &c)) {
		    dstring_append_char(&dstring, c);
		} else {
		    dstring_destroy(&dstring);
		    goto fail;
		}
	    } else {
		dstring_append_char(&dstring, *name++);
	    }
	}
	dstring_to_nstring(&dstring, & (components[length++]));
	if (*name == ']') {
	    break;
	}
    }
    if (*name) {
      fail:
	for (i = 0; i < length; i++) {
	    nstring_destroy(& (components[i]));
	}
	DEALLOCATE(components);
	return(FALSE);
    }
    name_key_init_unique(key, length);
    for (i = 0; i < length; i++) {
	name_key_set_component(key, i, & (components[i]));
    }
    DEALLOCATE(components);
    return(TRUE);
}

static BoolT
name_key_parse_cstring_string(NameKeyT *key,				       char * name)
{
    DStringT dstring;
    NStringT nstring;

    dstring_init(&dstring);
    while (*name) {
	if ((*name == '[') || (*name == ']') || (*name == '.')) {
	    dstring_destroy(&dstring);
	    return(FALSE);
	} else if (*name == '\\') {
	    char c;

	    if (name_key_parse_escaped(&name, &c)) {
		dstring_append_char(&dstring, c);
	    } else {
		dstring_destroy(&dstring);
		return(FALSE);
	    }
	} else {
	    dstring_append_char(&dstring, *name++);
	}
    }
    dstring_to_nstring(&dstring, &nstring);
    name_key_init_string(key, &nstring);
    return(TRUE);
}

static void
write_name_key_1(OStreamT *ostream,			  NStringT *nstring)
{
    unsigned length = nstring_length(nstring);
    char * bytes  = nstring_contents(nstring);

    while (length--) {
	switch (*bytes) {
	  case '[': case ']': case '.': case '\\':
	    write_char(ostream, '\\');
	    FALL_THROUGH;
	  default:
	    write_char(ostream, *bytes);
	}
	bytes++;
    }
}

/*--------------------------------------------------------------------------*/

void
name_key_init_string(NameKeyT *key,			      NStringT *string)
{
    key->type = KT_STRING;
    nstring_assign(& (key->u.string), string);
}

void
name_key_init_unique(NameKeyT *key,			      unsigned components)
{
    key->type                = KT_UNIQUE;
    key->u.unique.length     = components;
    key->u.unique.components = ALLOCATE_VECTOR(NStringT, components);
}

BoolT
name_key_parse_cstring(NameKeyT *key,				char * name)
{
    if (*name == '[') {
	return(name_key_parse_cstring_unique(key, name));
    } else {
	return(name_key_parse_cstring_string(key, name));
    }
}

void
name_key_set_component(NameKeyT *key,				unsigned component, 
				NStringT *string)
{
    ASSERT((key->type == KT_UNIQUE) && (component < key->u.unique.length));
    nstring_assign(& (key->u.unique.components[component]), string);
}

NameKeyTypeT
name_key_type(NameKeyT *key)
{
    return(key->type);
}

NStringT *
name_key_string(NameKeyT *key)
{
    ASSERT(key->type == KT_STRING);
    return(& (key->u.string));
}

unsigned
name_key_components(NameKeyT *key)
{
    ASSERT(key->type == KT_UNIQUE);
    return(key->u.unique.length);
}

NStringT *
name_key_get_component(NameKeyT *key,				unsigned component)
{
    ASSERT((key->type == KT_UNIQUE) && (component < key->u.unique.length));
    return(& (key->u.unique.components[component]));
}

unsigned
name_key_hash_value(NameKeyT *key)
{
#ifdef __TenDRA__
    unsigned hash_value; /* "tcc" complains if this is initialised */
#else
    unsigned hash_value = 0; /* "gcc" complains if this is not initialised */
#endif /* defined (__TenDRA__) */
    unsigned components;
    unsigned i;

    switch (key->type)EXHAUSTIVE {
      case KT_STRING:
	hash_value = nstring_hash_value(& (key->u.string));
	break;
      case KT_UNIQUE:
	components = key->u.unique.length;
	hash_value = components;
	for (i = 0; i < components; i++) {
	    hash_value += nstring_hash_value(& (key->u.unique.components[i]));
	}
	break;
    }
    return(hash_value);
}

BoolT
name_key_equal(NameKeyT *key1,			NameKeyT *key2)
{
    unsigned components;
    unsigned i;

    if (key1->type != key2->type) {
	return(FALSE);
    }
    switch (key1->type)EXHAUSTIVE {
      case KT_STRING:
	return(nstring_equal(& (key1->u.string), & (key2->u.string)));
      case KT_UNIQUE:
	if ((components = key1->u.unique.length) != key2->u.unique.length) {
	    return(FALSE);
	}
	for (i = 0; i < components; i++) {
	    if (!nstring_equal(& (key1->u.unique.components[i]),
				& (key2->u.unique.components[i]))) {
		return(FALSE);
	    }
	}
	break;
    }
    return(TRUE);
}

void
name_key_assign(NameKeyT *to,			 NameKeyT *from)
{
    switch (to->type = from->type)EXHAUSTIVE {
      case KT_STRING:
	nstring_assign(& (to->u.string), & (from->u.string));
	break;
      case KT_UNIQUE:
	to->u.unique.length     = from->u.unique.length;
	to->u.unique.components = from->u.unique.components;
	break;
    }
}

void
name_key_copy(NameKeyT *to,		       NameKeyT *from)
{
    unsigned components;
    unsigned i;

    switch (to->type = from->type)EXHAUSTIVE {
      case KT_STRING:
	nstring_copy(& (to->u.string), & (from->u.string));
	break;
      case KT_UNIQUE:
	components = to->u.unique.length = from->u.unique.length;
	to->u.unique.components = ALLOCATE_VECTOR(NStringT, components);
	for (i = 0; i < components; i++) {
	    nstring_copy(& (to->u.unique.components[i]),
			  & (from->u.unique.components[i]));
	}
	break;
    }
}

void
name_key_destroy(NameKeyT *key)
{
    unsigned components;
    unsigned i;

    switch (key->type)EXHAUSTIVE {
      case KT_STRING:
	nstring_destroy(& (key->u.string));
	break;
      case KT_UNIQUE:
	components = key->u.unique.length;
	for (i = 0; i < components; i++) {
	    nstring_destroy(& (key->u.unique.components[i]));
	}
	DEALLOCATE(key->u.unique.components);
	break;
    }
}

void
write_name_key(OStreamT *ostream,			NameKeyT *key)
{
    char     sep = '[';
    unsigned components;
    unsigned i;

    switch (key->type)EXHAUSTIVE {
      case KT_STRING:
	write_name_key_1(ostream, & (key->u.string));
	break;
      case KT_UNIQUE:
	components = key->u.unique.length;
	for (i = 0; i < components; i++) {
	    NStringT *nstring = & (key->u.unique.components[i]);

	    write_char(ostream, sep);
	    write_name_key_1(ostream, nstring);
	    sep = '.';
	}
	write_char(ostream, ']');
	break;
    }
}

/*--------------------------------------------------------------------------*/

void
name_key_list_init(NameKeyListT *list)
{
    list->head = NIL(NameKeyListEntryT *);
}

void
name_key_list_add(NameKeyListT *list,			   NameKeyT *    key)
{
    NameKeyListEntryT *entry;

    for (entry = name_key_list_head(list); entry;
	 entry = name_key_list_entry_next(entry)) {
	if (name_key_equal(key, & (entry->key))) {
	    name_key_destroy(key);
	    return;
	}
    }
    entry       = ALLOCATE(NameKeyListEntryT);
    entry->next = list->head;
    name_key_assign(& (entry->key), key);
    list->head  = entry;
}

NameKeyListEntryT *
name_key_list_head(NameKeyListT *list)
{
    return(list->head);
}

NameKeyT *
name_key_list_entry_key(NameKeyListEntryT *entry)
{
    return(& (entry->key));
}

NameKeyListEntryT *
name_key_list_entry_next(NameKeyListEntryT *entry)
{
    return(entry->next);
}

/*--------------------------------------------------------------------------*/

void
name_key_pair_list_init(NameKeyPairListT *list)
{
    list->head = NIL(NameKeyPairListEntryT *);
}

BoolT
name_key_pair_list_add(NameKeyPairListT *list,				NameKeyT *        from, 
				NameKeyT *        to)
{
    NameKeyPairListEntryT *entry;

    for (entry = name_key_pair_list_head(list); entry;
	 entry = name_key_pair_list_entry_next(entry)) {
	if (name_key_equal(from, & (entry->from))) {
	    return(FALSE);
	}
    }
    entry       = ALLOCATE(NameKeyPairListEntryT);
    entry->next = list->head;
    name_key_assign(& (entry->from), from);
    name_key_assign(& (entry->to), to);
    list->head  = entry;
    return(TRUE);
}

NameKeyPairListEntryT *
name_key_pair_list_head(NameKeyPairListT *list)
{
    return(list->head);
}

NameKeyT *
name_key_pair_list_entry_from(NameKeyPairListEntryT *entry)
{
    return(& (entry->from));
}

NameKeyT *
name_key_pair_list_entry_to(NameKeyPairListEntryT *entry)
{
    return(& (entry->to));
}

NameKeyPairListEntryT *
name_key_pair_list_entry_next(NameKeyPairListEntryT *entry)
{
    return(entry->next);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
