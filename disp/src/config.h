/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef SEEK_SET
#define SEEK_SET		0
#endif

#define null			NULL
#define BYTESIZE		8
#define streq(X, Y)		(strcmp((X), (Y)) == 0)


#endif
