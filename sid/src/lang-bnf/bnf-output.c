/*
 * Copyright (c) 2008 The TenDRA Project <http://www.tendra.org/>.
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

#include <stdio.h>
#include <assert.h>

#include <exds/dstring.h>

#include <shared/check.h>

#include "bnf-output.h"
#include "bnf-out-info.h"
#include "../grammar.h"
#include "../adt/entry-list.h"
#include "../adt/rule.h"
#include "../adt/key.h"

static void
output_bnf_key(BNFOutputInfoT *info, KeyT *key)
{
	OStreamT *ostream = bnf_out_info_ostream(info);

	write_char(ostream, '<');
	write_key(ostream, key);
	write_char(ostream, '>');
}

static int
bnf_output_item(BNFOutputInfoT *info, ItemT *item, int i)
{
	OStreamT *ostream = bnf_out_info_ostream(info);
	EntryT   *entry   = item_entry(item);

	switch (item_type(item)) {
	case ET_RULE:
	case ET_BASIC:
		if (i != 0) {
			write_newline(ostream);
			write_tab(ostream);
			write_cstring(ostream, "| ");
		}

		output_bnf_key(info, entry_key(entry));
		return 1;

	default:
		/* Other entries are irrelevant to BNF */
		return 0;
	}
}

static void
bnf_output_alt(BNFOutputInfoT *info, AltT *alt)
{
	OStreamT *ostream = bnf_out_info_ostream(info);

	ItemT *item;
	int i = 0;

	for (item = alt_item_head(alt); item; item = item_next(item)) {
		if (!bnf_output_item(info, item, i)) {
			continue;
		}

		write_char(ostream, ' ');
		i++;
	}
}

static void
bnf_output_rule(BNFOutputInfoT *info, RuleT *rule)
{
	OStreamT *ostream = bnf_out_info_ostream(info);
	KeyT     *key     = entry_key(rule_entry(rule));

	AltT *alt;

	output_bnf_key(info, key);
	write_cstring(ostream, " ::= ");

	for (alt = rule->alt_head; alt; alt = alt_next(alt)) {
		bnf_output_alt(info, alt);
	}

	if (rule_has_empty_alt(rule)) {
		write_newline(ostream);
		write_tab(ostream);
		write_cstring(ostream, "| \"\"");
	}

	write_newline(ostream);
	write_newline(ostream);
}

static void
bnf_output_entry(EntryT *entry, void *gclosure)
{
	BNFOutputInfoT *info = gclosure;

	if (!entry_is_rule(entry)) {
		return;
	}

	bnf_output_rule(info, entry_get_rule(entry));
}

extern void
bnf_output_parser(BNFOutputInfoT *info, GrammarT *grammar)
{
	TableT     *table      = grammar_table(grammar);
	EntryListT *entry_list = grammar_entry_list(grammar);

	table_untrace(table);
	entry_list_iter_table(entry_list, FALSE, bnf_output_entry, info);
}

