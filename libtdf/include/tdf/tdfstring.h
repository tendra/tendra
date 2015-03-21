/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TDF_TDFSTRING_H
#define TDF_TDFSTRING_H

/*
 * the definition of the internal representation of the sort tdfstring
 * and tdfident
 */
typedef struct {
	int size;	/* size of components in bits */
	int number;	/* number of components */

	/*
	 * the components are place in the array of the smallest
	 * possible size elements
	 */
	union {
		char  *chars;
		short *shorts;
		int   *longs;
	} ints;
} tdfstring;

#endif

