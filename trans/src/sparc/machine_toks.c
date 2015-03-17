/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/string.h>

int
machine_toks ( char *s )
{
	if (streq(s, "c89.stdarg.__va_start")) {
		return 1;
	}

	if (streq(s, "c89.stdarg.va_arg")) {
		return 1;
	}

	if (streq(s, "~next_caller_offset")) {
		return 1;
	}

	if (streq(s, "~next_callee_offset")) {
		return 1;
	}

	if (streq(s, "__sparc_special")) {
		return 1;
	}

	if (streq(s, "~Sync_handler")) {
		return 1;
	}

	return 0;
}

