/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * syntax.c - Character classification.
 *
 * This file implements the syntax table facility specified in the file
 * "syntax.h". See that file for more details.
 *
 * This particular implementation assumes that the ASCII character set is
 * being used. It will need changing for other character sets.
 *
 * TODO possibly this could be merged into the cstring interface.
 */

#include "syntax.h"

int
syntax_value(char c)
{
	if (c >= '0' && c <= '9') {
		return c - '0';
	} else if (c >= 'A' && c <= 'Z') {
		return c - 'A' + 10;
	} else if (c >= 'a' && c <= 'z') {
		return c - 'a' + 10;
	}

	return SYNTAX_NO_VALUE;
}
