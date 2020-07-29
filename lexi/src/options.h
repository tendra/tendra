/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdio.h>

struct options {
	/*
	 * The selected output language. See main.c for the various
	 * possibilities here.
	 */
	/* TODO: this ought to be an enum */
	const char *lang;

	/*
	 * TODO: These are language-specific options; they should be elsewhere
	 */
	const char *lexi_prefix;
};

#endif

