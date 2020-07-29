/*
 * Copyright 2008-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <exds/dstring.h>

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
	entry_list_iter_table(entry_list, false, bnf_output_entry, info);
}

