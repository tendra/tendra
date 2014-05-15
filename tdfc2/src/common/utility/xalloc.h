/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef XALLOC_INCLUDED
#define XALLOC_INCLUDED


extern gen_ptr xmalloc(gen_size);
extern gen_ptr xrealloc(gen_ptr, gen_size);
extern void xfree(gen_ptr);
extern string xustr(gen_size);
extern string xustrcpy(string);
extern string xustrncpy(string, gen_size);
extern string xustrcat(string, string);
extern void xufree(string, gen_size);
extern void xumemcpy(string, string, gen_size);
extern int xumemcmp(string, string, gen_size);


#define xalloc_scale(T, N)\
	((gen_size)(N)*(gen_size)sizeof(T))

#define xmalloc_one(T)\
	xmalloc(xalloc_scale(T, 1))

#define xmalloc_nof(T, N)\
	xmalloc(xalloc_scale(T, N))

#define xrealloc_nof(P, T, N)\
	xrealloc((gen_ptr)(P), xalloc_scale(T, N))

#define xfree_nof(P)\
	xfree((gen_ptr)(P))


#endif
