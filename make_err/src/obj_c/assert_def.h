/*
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef ASSERT_DEF_H_INCLUDED
#define ASSERT_DEF_H_INCLUDED

/* Assertion function definitions */

#ifndef assert_errors
static void
assert_errors
(char *s, char *fn, int ln)
{
    (void)fprintf(stderr, "Assertion %s failed, %s, line %d.\n", s, fn, ln);
    abort();
}
#endif

errors *
check_null_errors
(errors *p, char *fn, int ln)
{
    if (p == NULL) assert_errors("Null pointer", fn, ln);
    return p;
}

errors *
check_tag_errors
(errors *p, unsigned t, char *fn, int ln)
{
    p = check_null_errors(p, fn, ln);
    if (p->ag_tag != t) assert_errors("Union tag", fn, ln);
    return p;
}

errors *
check_tag_etc_errors
(errors *p, unsigned tl, unsigned tb , char *fn, int ln)
{
    p = check_null_errors(p, fn, ln);
    if (p->ag_tag < tl || p->ag_tag >= tb) {
	assert_errors("Union tag", fn, ln);
    }
    return p;
}

#endif
