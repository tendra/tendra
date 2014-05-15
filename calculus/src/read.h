/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef READ_INCLUDED
#define READ_INCLUDED


#ifndef NO_LIMITS_H
#include <limits.h>
#endif

#ifndef CHAR_BIT
#define CHAR_BIT		8
#endif

#define MASK(N)	((unsigned long)((1 << (N)) - 1))


extern unsigned long bitmask[];
extern void init_bitmask(void);
extern void read_file(char *);


#endif
