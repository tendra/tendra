/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "options.h"

/*
 * Populate command line options with default values.
 */
void
cmd_line_options_init(cmd_line_options *opt)
{
	/* TODO These are language-specific; see options.h */
	opt->generate_asserts = false;
	opt->lexi_prefix      = "lexi_";
	opt->interface_prefix = NULL;
}

