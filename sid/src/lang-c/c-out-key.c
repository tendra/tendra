/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * c-out-key.c --- Output of key ADT objects.
 *
 * This file implements the identifier key output routines used by SID.
 */

#include <assert.h>
#include <stddef.h>
#include <ctype.h>

#include <shared/bool.h>
#include <shared/check.h>

#include "c-out-key.h"
#include "../adt/action.h"
#include "../adt/basic.h"
#include "../adt/name.h"
#include "../adt/rstack.h"
#include "../adt/rule.h"
#include "../adt/type.h"

static void
write_c_key(OStreamT *ostream, char *contents, unsigned length)
{
	while (length--) {
		char c;

		switch (c = *contents++) {
		case '-':
			write_cstring(ostream, "_H");
			break;

		case '_':
			write_cstring(ostream, "__");
			break;

		case ':':
			write_cstring(ostream, "_C");
			break;

		default:
			if (isalpha((unsigned char) c) || isdigit((unsigned char) c)) {
				write_char(ostream, c);
			} else {
				write_cstring(ostream, "_X");
				write_unsigned(ostream, (unsigned char) c);
				write_char(ostream, '_');
			}
			break;
		}
	}
}


/*
 * Externally visible functions
 */

void
c_output_mapped_key(COutputInfoT * info, EntryT * entry)
{
	OStreamT *ostream = c_out_info_ostream(info);
	NStringT *mapping = entry_get_mapping(entry);
	bool     strict  = c_out_info_get_numeric_ids(info);
	KeyT     *key;
	NStringT *prefix = NULL;

	if (mapping) {
		write_nstring(ostream, mapping);
		return;
	}

	key = entry_key(entry);
	switch (entry_type(entry)) EXHAUSTIVE {
	case ET_TYPE:
		prefix = c_out_info_type_prefix(info);
		break;

	case ET_RULE:
		prefix = c_out_info_fn_prefix(info);
		break;

	case ET_BASIC:
		prefix = c_out_info_terminal_prefix(info);
		strict = false;
		break;

	case ET_NON_LOCAL:
		prefix = c_out_info_in_prefix(info);
		break;

	case ET_ACTION:
	case ET_NAME:
	case ET_RENAME:
	case ET_PREDICATE:
		UNREACHED;
	}

	assert(prefix != NULL);
	write_nstring(ostream, prefix);
	if (key_is_string(key) && !strict) {
		NStringT *nstring = key_get_string(key);

		write_c_key(ostream, nstring_contents(nstring),
			nstring_length(nstring));
	} else {
		write_unsigned(ostream, key_get_number(key));
	}
}

void
c_output_key(COutputInfoT *info, KeyT *key, NStringT *prefix)
{
	OStreamT *ostream = c_out_info_ostream(info);
	bool     strict  = c_out_info_get_numeric_ids(info);

	write_nstring(ostream, prefix);
	if (key_is_string(key) && !strict) {
		NStringT *nstring = key_get_string(key);

		write_c_key(ostream, nstring_contents(nstring),
			nstring_length(nstring));
	} else {
		write_unsigned(ostream, key_get_number(key));
	}
}

void
c_output_label_key(COutputInfoT *info, KeyT *key, unsigned label)
{
	OStreamT *ostream = c_out_info_ostream(info);
	NStringT *prefix  = c_out_info_label_prefix(info);
	bool     strict  = c_out_info_get_numeric_ids(info);

	write_nstring(ostream, prefix);
	write_unsigned(ostream, label);
	write_char(ostream, '_');
	if (key_is_string(key) && !strict) {
		NStringT *nstring = key_get_string(key);

		write_c_key(ostream, nstring_contents(nstring),
			nstring_length(nstring));
	} else {
		write_unsigned(ostream, key_get_number(key));
	}
}

void
c_output_string_key(COutputInfoT *info, KeyT *key, NStringT *prefix)
{
	OStreamT *ostream = c_out_info_ostream(info);

	write_nstring(ostream, prefix);
	if (key_is_string(key)) {
		NStringT *nstring = key_get_string(key);

		write_c_key(ostream, nstring_contents(nstring),
			nstring_length(nstring));
	} else {
		write_unsigned(ostream, key_get_number(key));
	}
}
