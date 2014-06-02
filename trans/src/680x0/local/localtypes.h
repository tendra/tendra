/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */
    
#ifndef LOCALTYPES_INCLUDED
#define LOCALTYPES_INCLUDED

#include <reader/exptypes.h>

#include <construct/installtypes.h>


/*
    STRUCTURE REPRESENTING THE LAYOUT OF THE STACK

    This is just a value giving the stack size.
*/

typedef long ash ;


/*
    STRUCTURE USED TO ADD A SHAPE TO THE STACK.

    The astash field gives the new stack.  The astoff field gives the
    offset of the last field (in bits), and the astadj field gives the
    endianness adjustment for the last field.
*/

typedef struct {
    ash astash ;
    long astoff ;
    long astadj ;
} ast ;


/*

    STRUCTURE REPRESENTING SPECIAL FUNCTIONS
*/

typedef struct {
    bool is_special ;
    exp special_exp ;
} speci ;


/*
    STRUCTURE USED IN REGISTER ALLOCATION
*/

typedef struct {
    long place ;
    long num ;
    ash new_stack ;
    bool is_new ;
} allocation ;

#endif
