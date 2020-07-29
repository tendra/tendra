/*
 * Copyright 2008-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * fmt.h - Application-specific format specifiers for shared/error.
 */

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <exds/ostream.h>
#include <exds/dstring.h>

#include "adt/basic.h"
#include "adt/entry.h"
#include "adt/entry-list.h"
#include "adt/key.h"
#include "adt/rule.h"


static void fmt_clashlist(FILE *fp, void *p) {
	ClashListT *clashlist = p;

	write_clashes(ostream_error, clashlist);
}

static void fmt_basics(FILE *fp, void *p) {
	BasicClosureT *b = p;

	write_basics(ostream_error, b);
}

static void fmt_esc(FILE *fp, void *p) {
	int *c = p;

	write_escaped_char(ostream_error, *c);
}

static void fmt_key(FILE *fp, void *p) {
	KeyT *key = p;

	write_key(ostream_error, key);
}

static void fmt_entrylist(FILE *fp, void *p) {
	EntryListT *entrylist = p;

	write_entry_list(ostream_error, entrylist);
}

static void fmt_rulename(FILE *fp, void *p) {
	RuleT *rule = p;

	write_key(ostream_error, entry_key(rule_entry(rule)));
}

static void fmt_productions(FILE *fp, void *p) {
	RuleT *rule = p;

	for (; rule; rule = rule_get_next_in_reverse_dfs(rule)) {
		write_newline(ostream_error);
		write_rule(ostream_error, rule);
	}
}

static void fmt_rule(FILE *fp, void *p) {
	RuleT *rule = p;

	write_rule(ostream_error, rule);
}

static void fmt_nstring(FILE *fp, void *p) {
	NStringT *nstring = p;

	write_nstring(ostream_error, nstring);
}

static void fmt_entry(FILE *fp, void *p) {
	EntryT *entry = p;

	write_key(ostream_error, entry_key(entry));
}

static void fmt_rulenames(FILE *fp, void *p) {
	RuleT *rule = p;
	char  *sep  = "";

	for ( ; rule; rule = rule_get_next_in_reverse_dfs(rule)) {
		RuleT *next = rule_get_next_in_reverse_dfs(rule);

		write_cstring(ostream_error, sep);
		write_char(ostream_error, '\'');
		write_key(ostream_error, entry_key(rule_entry(rule)));
		write_char(ostream_error, '\'');
		if (next != NULL) {
			if (rule_get_next_in_reverse_dfs(next)) {
				sep = ", ";
			} else {
				sep = " & ";
			}
		}
	}
}

static void fmt_typetuple(FILE *fp, void *p) {
	TypeTupleT *typetuple = p;

	write_type_types(ostream_error, typetuple);
}

void
fmt_init(void)
{
	fmt_register('A', fmt_clashlist);
	fmt_register('B', fmt_basics);
	fmt_register('C', fmt_esc);
	fmt_register('K', fmt_key);
	fmt_register('L', fmt_entrylist);
	fmt_register('N', fmt_rulename);
	fmt_register('P', fmt_productions);
	fmt_register('R', fmt_rule);
	fmt_register('S', fmt_nstring);
	fmt_register('T', fmt_entry);
	fmt_register('W', fmt_rulenames);
	fmt_register('Y', fmt_typetuple);
}

