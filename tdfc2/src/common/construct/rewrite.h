/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef REWRITE_INCLUDED
#define REWRITE_INCLUDED


/*
    REWRITE RULE DECLARATIONS

    The routines in this module are concerned with the rewrite rule for
    inline class function definitions etc.
*/

extern void skip_function(IDENTIFIER);
extern EXP skip_default_arg(IDENTIFIER);
extern void rescan_functions(void);
extern void rescan_param(IDENTIFIER, int);
extern TYPE begin_templ_scope(TYPE);
extern void end_templ_scope(TYPE);


#endif
