/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef DE_TYPES_H
#define DE_TYPES_H


/*
    TYPE USED TO REPRESENT VARIABLE SORTS

    Each variable sort has a name (tag, token etc) and an associated
    sort number.
*/

typedef struct {
	char *name;
	sortname sortnum;
} var_sort;


/*
    TYPE REPRESENTING BINDINGS

    The bindings between variable sort constructs are represented by
    the structure binding.  This consists of a table of constructs of
    actual size sz, but of visible size max_no.
*/

typedef struct {
	long max_no;
	long sz;
	construct **table;
} binding;


#endif /* DE_TYPES_H */
