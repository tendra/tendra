/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef ASSERT_DEF_H_INCLUDED
#define ASSERT_DEF_H_INCLUDED

#include <stdlib.h>

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
    return p;
}

c_class *
check_tag_c_class
(c_class *p, unsigned t, char *fn, int ln)
{
    p = check_null_c_class(p, fn, ln);
    if (p->ag_tag != t) assert_c_class("Union tag", fn, ln);
    return p;
}

c_class *
check_tag_etc_c_class
(c_class *p, unsigned tl, unsigned tb , char *fn, int ln)
{
    p = check_null_c_class(p, fn, ln);
    if (p->ag_tag < tl || p->ag_tag >= tb) {
	assert_c_class("Union tag", fn, ln);
    }
    return p;
}

#endif
