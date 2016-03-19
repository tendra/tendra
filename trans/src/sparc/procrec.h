/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef PROCTYPES_INCLUDED
#define PROCTYPES_INCLUDED

#include <reader/exp.h>


/*
  TYPE REPRESENTING REGISTER NEEDS
*/

typedef struct {
    int fixneeds  ;
    int floatneeds ;
    prop prps ;
    int maxargs ;
  int callee_size;
} needs ;

int callee_size;


/*
  TYPE REPRESENTING REGISTER WEIGHTS
*/

#define wfixno		25
#define wfloatno	16

typedef struct {
    float fix [ wfixno ] ;
    float floating [ wfloatno ] ;
} weights ;

typedef struct {
    weights wp_weights ;
    long fix_break ;
    long float_break ;
} wp ;


/*
  TYPE REPRESENTING THE SPACE REQUIRED BY A PROCEDURE
*/

typedef struct {
    long fixdump ;
    long fltdump ;
    long stack ;
} spacereq ;


/*
  TYPE REPRESENTING A PROCEDURE RECORD
*/

typedef struct {
    exp nameproc ;
    int tlrecstart ;
    needs needsproc ;
    spacereq spacereqproc ;
    int expproc ;
} procrec ;


/*
  TYPE REPRESENTING REGISTER USAGE
*/

typedef struct {
    long fixed ;
    long flt ;
} space  ;


/*
  Type representing postlude chain
*/
typedef struct _postl {
  exp postlude;
  struct _postl * outer;
} postlude_chain;


extern procrec *procrecs ;

#endif /* PROCTYPES_INCLUDED */
