/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * name-key.c - External name key ADT.
 *
 * This file implements the external name key routines used by the TDF linker.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>

#include "name-key.h"
#include "solve-cycles.h"


#define SYNTAX_NO_VALUE (-1)

/*
 * This function returns the positive integer digit value that the specified
 * character should have, or SYNTAX_NO_VALUE if it has no value.
 */
static int
syntax_value(char c)
{
	if ((c >= '0') && (c <= '9')) {
		return c - '0';
	} else if ((c >= 'A') && (c <= 'Z')) {
		return c - 'A' + 10;
	} else if ((c >= 'a') && (c <= 'z')) {
		return c - 'a' + 10;
	}
	return SYNTAX_NO_VALUE;
}

static bool
name_key_parse_hex_char(char * name,				 char    *c_ref)
{
    char result;
    char c;
    int  value;

	/* TODO: this appears to be equivalent to calling isxdigit() twice */

    if ((c = name[0]), ((value = syntax_value(c)) != SYNTAX_NO_VALUE)) {
	result = (char)((unsigned)value << 4);
    } else {
	return false;
    }
    if ((c = name[1]), ((value = syntax_value(c)) != SYNTAX_NO_VALUE)) {
	result |= (char)value;
    } else {
	return false;
    }
    *c_ref = result;
    return true;
}

static bool
name_key_parse_escaped(char * *name_ref,				char     *c_ref)
{
    char * name = (*name_ref);

    switch ((*++name)) {
      case 'x': case 'X':
	if (!name_key_parse_hex_char(name, c_ref)) {
	    return false;
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
	return false;
    }
    *name_ref = name;
    return true;
}

static bool
name_key_parse_cstring_unique(NameKeyT *key,				       char * name)
{
    size_t length   = 1;
    char * tmp_name = name;
    NStringT *components;
    size_t i;

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
	return false;
    }
    name_key_init_unique(key, (unsigned) length);
    for (i = 0; i < length; i++) {
	name_key_set_component(key, (unsigned) i, & (components[i]));
    }
    DEALLOCATE(components);
    return true;
}

static bool
name_key_parse_cstring_string(NameKeyT *key,				       char * name)
{
    DStringT dstring;
    NStringT nstring;

    dstring_init(&dstring);
    while (*name) {
	if ((*name == '[') || (*name == ']') || (*name == '.')) {
	    dstring_destroy(&dstring);
	    return false;
	} else if (*name == '\\') {
	    char c;

	    if (name_key_parse_escaped(&name, &c)) {
		dstring_append_char(&dstring, c);
	    } else {
		dstring_destroy(&dstring);
		return false;
	    }
	} else {
	    dstring_append_char(&dstring, *name++);
	}
    }
    dstring_to_nstring(&dstring, &nstring);
    name_key_init_string(key, &nstring);
    return true;
}

static void
write_name_key_1(OStreamT *ostream,			  NStringT *nstring)
{
    size_t length = nstring_length(nstring);
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
    key->u.unique.length     = (size_t) components;
    key->u.unique.components = ALLOCATE_VECTOR(NStringT, components);
}

bool
name_key_parse_cstring(NameKeyT *key,				char * name)
{
    if (*name == '[') {
	return name_key_parse_cstring_unique(key, name);
    } else {
	return name_key_parse_cstring_string(key, name);
    }
}

void
name_key_set_component(NameKeyT *key,				unsigned component, 
				NStringT *string)
{
    assert((key->type == KT_UNIQUE) && (component < (unsigned) key->u.unique.length));
    nstring_assign(& (key->u.unique.components[component]), string);
}

NameKeyTypeT
name_key_type(NameKeyT *key)
{
    return key->type;
}

NStringT *
name_key_string(NameKeyT *key)
{
    assert(key->type == KT_STRING);
    return &key->u.string;
}

unsigned
name_key_components(NameKeyT *key)
{
    assert(key->type == KT_UNIQUE);
    return (unsigned) key->u.unique.length;
}

NStringT *
name_key_get_component(NameKeyT *key,				unsigned component)
{
    assert((key->type == KT_UNIQUE) && (component < (unsigned) key->u.unique.length));
    return &key->u.unique.components[component];
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

    switch (key->type) {
      case KT_STRING:
	hash_value = nstring_hash_value(& (key->u.string));
	break;
      case KT_UNIQUE:
	components = (unsigned) key->u.unique.length;
	hash_value = components;
	for (i = 0; i < components; i++) {
	    hash_value += nstring_hash_value(& (key->u.unique.components[i]));
	}
	break;
    }
    return hash_value;
}

bool
name_key_equal(NameKeyT *key1,			NameKeyT *key2)
{
    unsigned components;
    unsigned i;

    if (key1->type != key2->type) {
	return false;
    }
    switch (key1->type) {
      case KT_STRING:
	return nstring_equal(&key1->u.string, &key2->u.string);
      case KT_UNIQUE:
	if ((components = (unsigned) key1->u.unique.length) != (unsigned) key2->u.unique.length) {
	    return false;
	}
	for (i = 0; i < components; i++) {
	    if (!nstring_equal(& (key1->u.unique.components[i]),
				& (key2->u.unique.components[i]))) {
		return false;
	    }
	}
	break;
    }
    return true;
}

void
name_key_assign(NameKeyT *to,			 NameKeyT *from)
{
    switch (to->type = from->type) {
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

    switch (to->type = from->type) {
      case KT_STRING:
	nstring_copy(& (to->u.string), & (from->u.string));
	break;
      case KT_UNIQUE:
	components = (unsigned) (to->u.unique.length = from->u.unique.length);
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

    switch (key->type) {
      case KT_STRING:
	nstring_destroy(& (key->u.string));
	break;
      case KT_UNIQUE:
	components = (unsigned) (unsigned) (unsigned) (unsigned) (unsigned) (unsigned) (unsigned) (unsigned) (unsigned) key->u.unique.length;
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

    switch (key->type) {
      case KT_STRING:
	write_name_key_1(ostream, & (key->u.string));
	break;
      case KT_UNIQUE:
	components = (unsigned) key->u.unique.length;
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

void
name_key_list_init(NameKeyListT *list)
{
    list->head = NULL;
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
    return list->head;
}

NameKeyT *
name_key_list_entry_key(NameKeyListEntryT *entry)
{
    return &entry->key;
}

NameKeyListEntryT *
name_key_list_entry_next(NameKeyListEntryT *entry)
{
    return entry->next;
}

void
name_key_pair_list_init(NameKeyPairListT *list)
{
    list->head = NULL;
}

bool
name_key_pair_list_add(NameKeyPairListT *list,				NameKeyT *        from, 
				NameKeyT *        to)
{
    NameKeyPairListEntryT *entry;

    for (entry = name_key_pair_list_head(list); entry;
	 entry = name_key_pair_list_entry_next(entry)) {
	if (name_key_equal(from, & (entry->from))) {
	    return false;
	}
    }
    entry       = ALLOCATE(NameKeyPairListEntryT);
    entry->next = list->head;
    name_key_assign(& (entry->from), from);
    name_key_assign(& (entry->to), to);
    list->head  = entry;
    return true;
}

NameKeyPairListEntryT *
name_key_pair_list_head(NameKeyPairListT *list)
{
    return list->head;
}

NameKeyT *
name_key_pair_list_entry_from(NameKeyPairListEntryT *entry)
{
    return &entry->from;
}

NameKeyT *
name_key_pair_list_entry_to(NameKeyPairListEntryT *entry)
{
    return &entry->to;
}

NameKeyPairListEntryT *
name_key_pair_list_entry_next(NameKeyPairListEntryT *entry)
{
    return entry->next;
}
