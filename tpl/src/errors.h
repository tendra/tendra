/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* this file defines the macros which control the SORT checking; can
   be modified to eliminate SORT checking. */

#ifndef ERRORS_INCLUDED
#define ERRORS_INCLUDED


extern void fail(char *, ...);
extern void assert_sort(unsigned int);
extern void assert_sort_or_empty(unsigned int);


/* These macros can be given empty bodies if required;
   Better make sure your SORTs are right first!
*/

#define SET_RSORT(x)		current_TDF->sort = x
#define ASSERT_SORT(x)		assert_sort((unsigned int)x)
#define ASSERT_SORT_OR_EMPTY(x)	assert_sort_or_empty((unsigned int)x)

#define Assert(x) if (!(x)) {fail("Assertion %s failed", #x);}


#endif
