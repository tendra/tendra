/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * bnf-main.c - BNF language entry points.
 */

#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <exds/dalloc.h>
#include <exds/cstring-list.h>

#include "bnf-main.h"
#include "bnf-out-info.h"
#include "bnf-output.h"

#include "../lang.h"
#include "../output.h"

static void *
main_init_bnf(OutputInfoT *out_info, CStringListT *options)
{
	BNFOutputInfoT      *bnf_out_info;
	CStringListEntryT   *entry;

	bnf_out_info = ALLOCATE(BNFOutputInfoT);
	bnf_out_info_init(bnf_out_info, out_info);

	for (entry = cstring_list_head(options); entry;
		entry = cstring_list_entry_deallocate(entry)) {
		error(ERR_FATAL, "language '%s' doesn't understand option '%s'"
			"bnf", cstring_list_entry_string(entry));
	}

	return bnf_out_info;
}

static void
main_output_bnf(void *gclosure, GrammarT *grammar)
{
	BNFOutputInfoT *bnf_out_info = gclosure;

	out_info_set_current_ostream(bnf_out_info_info(bnf_out_info), 0);
	bnf_output_parser(bnf_out_info, grammar);
}

struct LangListT bnf_language_list = {
	"bnf", 1, 1, main_init_bnf, NULL, main_output_bnf
};
