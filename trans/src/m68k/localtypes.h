/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCAL_TYPES_H
#define LOCAL_TYPES_H

#include <local/ash.h>

#include <construct/installtypes.h>

/*
 * STRUCTURE USED TO ADD A SHAPE TO THE STACK.
 *
 * The astash field gives the new stack.  The astoff field gives the
 * offset of the last field (in bits), and the astadj field gives the
 * endianness adjustment for the last field.
 */
typedef struct {
	ash astash;
	long astoff;
	long astadj;
} ast;

/*
 * STRUCTURE USED IN REGISTER ALLOCATION
 */
typedef struct {
	long place;
	long num;
	ash new_stack;
	bool is_new;
} allocation;

#endif

