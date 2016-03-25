/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * test-main.c - Test language entry points.
 */

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <exds/dalloc.h>
#include <exds/cstring-list.h>

#include "test-main.h"

#include "../lang.h"
#include "../output.h"

static void *
main_init_test(OutputInfoT *info, CStringListT *options)
{
	CStringListEntryT *entry;

	UNUSED(info);
	for (entry = cstring_list_head(options); entry;
		entry = cstring_list_entry_deallocate(entry)) {
		const char *option;

		option = cstring_list_entry_string(entry);
		error(ERR_FATAL, "language '%s' doesn't understand option '%s'",
			"test", option);
	}

	return NULL;
}

struct LangListT test_language_list = {
	"test", 1, 0, main_init_test, NULL, NULL
};
