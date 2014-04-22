/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>
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
	bool generate_asserts;
	const char *lexi_prefix;
	const char *interface_prefix;

	/*
	 * An array of files to which output is written. The number (and
	 * purposes) of files is specific to each output language. This
	 * array must be large enough to hold the maximum number of files
	 * specified by outputs[] in main().
	 *
	 * Elements beyond that of the selected output language's number
	 * are undefined. The order of files is defined by each output language.
	 *
	 * Since this is known at compile-time and is relatively small,
	 * a linked list was considered cumbersome.
	 *
	 */
	struct {
		const char *name;
		FILE *file;
	} out[2];
};

#endif

