/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CHARSET_INCLUDED
#define CHARSET_INCLUDED


/*
 * Note the character set mapping file is assumed to be written in the
 * host execution character set (i.e. the set on which tdfc2 is built).
 */

int
charset_load(char map[], FILE *f, unsigned int seed);

void
charset_dump(char map[], FILE *f);


#endif
