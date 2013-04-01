/* $Id$ */

/*
 * Copyright 2002-2013, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCALFLAGS_H
#define LOCALFLAGS_H

extern int gencompat;

/* condition for shape to be treated as a struct */
#define sparccpd(s)(name(s) == cpdhd || name(s) == nofhd || \
                        name(s) == shcomplexhd || shape_size(s) >64 || \
                        name(s) == u64hd || name(s) == s64hd)

#endif

