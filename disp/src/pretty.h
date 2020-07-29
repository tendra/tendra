/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef PRETTY_INCLUDED
#define PRETTY_INCLUDED


/*
 * PRETTY PRINTING ROUTINES
 *
 * Once the TDF tree has been read in it needs to be output in a
 * form which reflects the underlying tree structure.  This is
 * done by means of indentation.  The difficult problem is the
 * maximum amount of indentation which can be used while fitting the
 * output into a reasonable number of columns.
 */

extern void pretty_tree(void);
extern int helpflag;
extern int dflag;
extern int maxcol;
extern int progress;
extern int quickflag;


#endif
