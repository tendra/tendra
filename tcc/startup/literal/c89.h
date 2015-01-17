/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* ANSI C89 INTEGER LITERAL RULES */

#ifndef __TCC_LITERAL_H
#define __TCC_LITERAL_H

#pragma TenDRA begin

#pragma TenDRA no external declaration allow
#pragma TenDRA longlong type disallow

#define __lu  *:unsigned long
#define __u   ?:unsigned int
#define __l   ?:long
#define __i   ?:int

#pragma integer literal decimal     unsigned long      __lu
#pragma integer literal octal       unsigned long      __lu
#pragma integer literal hexadecimal unsigned long      __lu

#pragma integer literal decimal     unsigned           __u | __lu
#pragma integer literal octal       unsigned           __u | __lu
#pragma integer literal hexadecimal unsigned           __u | __lu

#pragma integer literal decimal              long      __l | __lu
#pragma integer literal octal                long      __l | __lu
#pragma integer literal hexadecimal          long      __l | __lu

#pragma integer literal decimal                        __i | __l | __lu
#pragma integer literal octal                          __i | __u | __l | __lu
#pragma integer literal hexadecimal                    __i | __u | __l | __lu

#undef __lu
#undef __u
#undef __l
#undef __i

#endif

