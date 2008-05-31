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
 * basic.c - Basic ADT.
 *
 * This file implements the basic manipulation routines.
 */

#include "../shared/check/check.h"
#include "basic.h"
#include "action.h"
#include "../grammar.h"
#include "name.h"
#include "rstack.h"
#include "rule.h"
#include "type.h"

BasicT *
basic_create(GrammarT *grammar, BoolT ignored)
{
	BasicT *basic = ALLOCATE(BasicT);

	basic->terminal    = grammar_next_terminal(grammar);
	types_init(basic_result(basic));
	basic->result_code = NULL;
	basic->ignored     = ignored;

	return basic;
}

unsigned
basic_terminal(BasicT *basic)
{
	return basic->terminal;
}

TypeTupleT *
basic_result(BasicT *basic)
{
	return &basic->result;
}

void *
basic_get_result_code(BasicT *basic)
{
	return basic->result_code;
}

void
basic_set_result_code(BasicT *basic, void *code)
{
	basic->result_code = code;
}

BoolT
basic_get_ignored(BasicT *basic)
{
	return basic->ignored;
}

void
basic_iter_for_table(BasicT *basic, BoolT full,
	void (*proc) WEAK (EntryT *, void *), void *closure)
{
	if (full) {
		types_iter_for_table(basic_result(basic), proc, closure);
	}
}

void
write_basics(OStreamT *ostream, BasicClosureT *closure)
{
	BitVecT  *bitvec   = closure->bitvec;
	TableT   *table    = grammar_table(closure->grammar);
	unsigned  terminal = bitvec_first_bit(bitvec);
	unsigned  num_bits = bitvec_num_bits(bitvec);

	while (num_bits) {
		EntryT *entry;

		entry = table_get_basic_by_number(table, terminal);
		if (entry) {
			write_char(ostream, '\'');
			write_key(ostream, entry_key(entry));
			write_char(ostream, '\'');
		} else {
			write_unsigned(ostream, terminal);
		}

		if (num_bits > 2) {
			write_cstring(ostream, ", ");
		} else if (num_bits == 2) {
			write_cstring(ostream, " & ");
		}

		num_bits--;
		(void) bitvec_next_bit(bitvec, &terminal);
	}
}

