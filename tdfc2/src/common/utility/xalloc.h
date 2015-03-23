/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef XALLOC_INCLUDED
#define XALLOC_INCLUDED


extern void *xmalloc(size_t);
extern void *xrealloc(void *, size_t);
extern void xfree(void *);
extern string xustr(size_t);
extern string xustrcpy(string);
extern string xustrncpy(string, size_t);
extern string xustrcat(string, string);
extern void xufree(string, size_t);
extern void xumemcpy(string, string, size_t);
extern int xumemcmp(string, string, size_t);


#define xalloc_scale(T, N)\
	((size_t) (N) * sizeof(T))

#define xmalloc_one(T)\
	xmalloc(xalloc_scale(T, 1))

#define xmalloc_nof(T, N)\
	xmalloc(xalloc_scale(T, N))

#define xrealloc_nof(P, T, N)\
	xrealloc((P), xalloc_scale(T, N))

#define xfree_nof(P)\
	xfree((P))


#endif
