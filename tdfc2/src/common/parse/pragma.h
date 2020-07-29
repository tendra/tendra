/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef PRAGMA_INCLUDED
#define PRAGMA_INCLUDED


/*
    PRAGMA ANALYSIS DECLARATIONS

    The routines in this module are concerned with the processing of the
    #pragma directives used to configure the program.
*/

extern int read_pragma(void);
extern int lint_comment(void);
extern int find_keyword(IDENTIFIER);
extern void define_keyword(IDENTIFIER, int);
extern void undef_keyword(IDENTIFIER);
extern void rescan_pragma(int);


#endif
