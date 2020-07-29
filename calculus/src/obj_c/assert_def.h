/*
    AUTOMATICALLY GENERATED FROM ALGEBRA calculus (VERSION 1.2)
    BY calculus (VERSION 1.3)
*/

#ifndef ASSERT_DEF_H_INCLUDED
#define ASSERT_DEF_H_INCLUDED

/* Assertion function definitions */

#ifndef assert_calculus
static void
assert_calculus
(char *s, char *fn, int ln)
{
    (void)fprintf(stderr, "Assertion %s failed, %s, line %d.\n", s, fn, ln);
    abort();
}
#endif

calculus *
check_null_calculus
(calculus *p, char *fn, int ln)
{
    if (p == NULL) assert_calculus("Null pointer", fn, ln);
    return p;
}

calculus *
check_tag_calculus
(calculus *p, unsigned t, char *fn, int ln)
{
    p = check_null_calculus(p, fn, ln);
    if (p->ag_tag != t) assert_calculus("Union tag", fn, ln);
    return p;
}

calculus *
check_tag_etc_calculus
(calculus *p, unsigned tl, unsigned tb , char *fn, int ln)
{
    p = check_null_calculus(p, fn, ln);
    if (p->ag_tag < tl || p->ag_tag >= tb) {
	assert_calculus("Union tag", fn, ln);
    }
    return p;
}

#endif
