/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <reader/token.h>

tokval
special_token(token t, bitstream pars, int sortcode, int *done)
{
	const static tokval dummy;

	*done = 1;

	return dummy;
}

