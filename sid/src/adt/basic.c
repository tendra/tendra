/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * basic.c - Basic ADT.
 *
 * This file implements the basic manipulation routines.
 */

#include <shared/bool.h>
#include <shared/check.h>

#include "basic.h"
#include "action.h"
#include "../grammar.h"
#include "name.h"
#include "rstack.h"
#include "rule.h"
#include "type.h"

BasicT *
basic_create(GrammarT *grammar, bool ignored)
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

bool
basic_get_ignored(BasicT *basic)
{
	return basic->ignored;
}

void
basic_iter_for_table(BasicT *basic, bool full,
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
		IGNORE bitvec_next_bit(bitvec, &terminal);
	}
}
