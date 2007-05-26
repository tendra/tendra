/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef ASSERT_DEF_H_INCLUDED
#define ASSERT_DEF_H_INCLUDED

/* Assertion function definitions */

#ifndef assert_c_class
static void
assert_c_class
(char *s, char *fn, int ln)
{
    (void)fprintf(stderr, "Assertion %s failed, %s, line %d.\n", s, fn, ln);
    abort();
}
#endif

c_class *
check_null_c_class
(c_class *p, char *fn, int ln)
{
    if (p == NULL) assert_c_class("Null pointer", fn, ln);
    return(p);
}

c_class *
check_tag_c_class
(c_class *p, unsigned t, char *fn, int ln)
{
    p = check_null_c_class(p, fn, ln);
    if (p->ag_tag != t) assert_c_class("Union tag", fn, ln);
    return(p);
}

c_class *
check_tag_etc_c_class
(c_class *p, unsigned tl, unsigned tb , char *fn, int ln)
{
    p = check_null_c_class(p, fn, ln);
    if (p->ag_tag < tl || p->ag_tag >= tb) {
	assert_c_class("Union tag", fn, ln);
    }
    return(p);
}

#endif
