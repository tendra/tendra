/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef XALLOC_INCLUDED
#define XALLOC_INCLUDED


extern string xustrcpy(string);
extern string xustrncpy(string, size_t);
extern string xustrcat(string, string);
extern void xumemcpy(string, string, size_t);
extern int xumemcmp(string, string, size_t);


#endif
