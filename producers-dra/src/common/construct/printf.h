/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef PRINTF_INCLUDED
#define PRINTF_INCLUDED


/*
    PRINTF AND SCANF ARGUMENT CHECKING

    The routines in this module are concerned with the checking of the
    arguments to functions like printf and scanf where a format string is
    used to specify a list of extra arguments.
*/

extern LIST(TYPE) find_printf_args(STRING, unsigned, int);
extern int is_printf_type(TYPE);
extern void init_printf(void);
extern TYPE type_printf;
extern TYPE type_scanf;
extern TYPE type_wprintf;
extern TYPE type_wscanf;


#endif
