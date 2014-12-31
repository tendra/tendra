/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* SIMPLE INTEGER LITERAL RULES */

#ifndef __TCC_LITERAL_H
#define __TCC_LITERAL_H

#pragma TenDRA begin

#pragma TenDRA no external declaration allow
#pragma TenDRA longlong type allow

#define __llu *:unsigned long long
#define __lu  ?:unsigned long
#define __u   ?:unsigned int
#define __ll  ?:long long
#define __l   ?:long
#define __i   ?:int

#pragma integer literal decimal     unsigned long long __llu
#pragma integer literal octal       unsigned long long __llu
#pragma integer literal hexadecimal unsigned long long __llu

#pragma integer literal decimal     unsigned long      __lu | __llu
#pragma integer literal octal       unsigned long      __lu | __llu
#pragma integer literal hexadecimal unsigned long      __lu | __llu

#pragma integer literal decimal     unsigned           __u | __lu | __llu
#pragma integer literal octal       unsigned           __u | __lu | __llu
#pragma integer literal hexadecimal unsigned           __u | __lu | __llu

#pragma integer literal decimal              long long __ll | __llu
#pragma integer literal octal                long long __ll | __llu
#pragma integer literal hexadecimal          long long __ll | __llu

#pragma integer literal decimal              long      __l | __ll | __llu
#pragma integer literal octal                long      __l | __ll | __llu
#pragma integer literal hexadecimal          long      __l | __ll | __llu

#pragma integer literal decimal                        __i | __l | __ll | __llu
#pragma integer literal octal                          __i | __l | __ll | __llu
#pragma integer literal hexadecimal                    __i | __l | __ll | __llu

#undef __llu
#undef __lu
#undef __u
#undef __ll
#undef __l
#undef __i

#endif

