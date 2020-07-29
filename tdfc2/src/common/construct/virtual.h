/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef VIRTUAL_INCLUDED
#define VIRTUAL_INCLUDED


/*
    VIRTUAL FUNCTION DECLARATIONS

    The routines in this module are concerned with virtual functions.
*/

extern void begin_virtual(CLASS_TYPE);
extern void end_virtual(CLASS_TYPE);
extern void add_virtual(CLASS_TYPE, IDENTIFIER, LIST(VIRTUAL));
extern LIST(VIRTUAL) overrides_virtual(CLASS_TYPE, HASHID, TYPE, IDENTIFIER *);
extern VIRTUAL find_overrider(CLASS_TYPE, IDENTIFIER, GRAPH, GRAPH *);
extern IDENTIFIER find_pure_function(CLASS_TYPE);
extern unsigned long virtual_start(GRAPH);


#endif
