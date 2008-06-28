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
 * c-out-key.c --- Output of key ADT objects.
 *
 * This file implements the identifier key output routines used by SID.
 */

#include <assert.h>
#include <ctype.h>

#include "../shared/check/check.h"
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
	BoolT     strict  = c_out_info_get_numeric_ids(info);
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
		strict = FALSE;
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
	BoolT     strict  = c_out_info_get_numeric_ids(info);

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
	BoolT     strict  = c_out_info_get_numeric_ids(info);

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

