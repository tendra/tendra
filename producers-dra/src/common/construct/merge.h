/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef MERGE_INCLUDED
#define MERGE_INCLUDED


/*
    IDENTIFIER MERGE ROUTINE DECLARATIONS

    The routines in this module are concerned with the merging of
    identifiers declared in separate compilation units.
*/

extern int compatible_class(CLASS_TYPE, CLASS_TYPE);
extern void merge_namespaces(NAMESPACE, NAMESPACE);
extern int merge_type(IDENTIFIER, IDENTIFIER);
extern int force_merge;


#endif
