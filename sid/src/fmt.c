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

/*
 * fmt.h - Application-specific format specifiers for shared/error.
 */

#include <exds/ostream.h>
#include <exds/dstring.h>

#include <shared/error.h>

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

