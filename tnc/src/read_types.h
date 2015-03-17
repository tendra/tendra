/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef READ_TYPES_H
#define READ_TYPES_H


/*
    TYPE REPRESENTING AN INPUT FILE POSITION

    A position in the input file is represented by the line number,
    the file position (in bytes from the start of the file) and the
    current values of the pending and looked_ahead flags (see
    analyser.c).
*/

typedef struct {
	long line;
	long posn;
	int pending;
	bool ahead;
} position;


#endif /* READ_TYPES_H */
