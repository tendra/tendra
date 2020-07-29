/*
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef ASSERT_DEF_H_INCLUDED
#define ASSERT_DEF_H_INCLUDED

/* Assertion function definitions */

#ifndef assert_tdf
static void
assert_tdf
(char *s, char *fn, int ln)
{
    (void)fprintf(stderr, "Assertion %s failed, %s, line %d.\n", s, fn, ln);
    abort();
}
#endif

tdf *
check_null_tdf
(tdf *p, char *fn, int ln)
{
    if (p == NULL) assert_tdf("Null pointer", fn, ln);
    return p;
}

tdf *
check_tag_tdf
(tdf *p, unsigned t, char *fn, int ln)
{
    p = check_null_tdf(p, fn, ln);
    if (p->ag_tag != t) assert_tdf("Union tag", fn, ln);
    return p;
}

tdf *
check_tag_etc_tdf
(tdf *p, unsigned tl, unsigned tb , char *fn, int ln)
{
    p = check_null_tdf(p, fn, ln);
    if (p->ag_tag < tl || p->ag_tag >= tb) {
	assert_tdf("Union tag", fn, ln);
    }
    return p;
}

#endif
