/*
 * Copyright (c) 2003-2004, by Boris Popov
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $TenDRA$
 */

#ifndef TEN_CSTRING_H
#define	TEN_CSTRING_H

#include <stddef.h>

#define	cstring_equal(s1, s2)		(strcmp ((s1), (s2)) == 0)
#define	cstring_ci_equal(s1, s2)	(strcasecmp ((s1), (s2)) == 0)

char *string_alloc(size_t);
void  string_free(char *);
char *string_copy(const char *);
char *string_ncopy(const char *, size_t);
char *string_join(const char *, const char *, char);
char *string_concat(const char *, const char *);
int   string_to_unsigned(const char *, unsigned *);


struct fmm_type;

extern struct fmm_type *memtype_str;

/*
 * Usage of string_append() deprecated.  Use string_join() instead.
 */
#define	string_append(a, b, c)	string_join((a), (b), (c))

#endif /* !defined(TEN_CSTRING_H) */
