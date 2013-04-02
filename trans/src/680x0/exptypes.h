/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EXPTYPES_INCLUDED
#define EXPTYPES_INCLUDED

#include <reader/codetypes.h>

#include <diag/dg_first.h>
#include <diag/diaginfo.h>


/*
    STRUCTURE REPRESENTING EXPRESSION PROPERTIES

    This is basically a bitfield, with different bits representing
    different properties.  See expmacs.h for details.
*/

typedef unsigned short prop ;


/*
    UNION REPRESENTING A EXPRESSION CONSTITUENT

    An expression constituent can be another expression, a string, a
    numerical value, a floating-point value or an external declaration.
*/

typedef union {
#ifndef tdf3
   long l ;
   unsigned long ui ;
#else
    int l ;
    unsigned int ui ;
#endif
    float fp ;
    char *str ;
    struct exp_t *expr ;
    struct dec_t *glob ;
    diag_info *d ;
    struct aldef_t *ald ;
} expno ; 


/*
    STRUCTURE REPRESENTING EXPRESSIONS

    An expression has a number of constituents given by the sonf, brof,
    ptrf and numf fields, a shape (which is another expression), a
    name representing the expression type, a properties field, and a
    single byte as an end marker.
*/

struct exp_t {
    unsigned char namef ;
    unsigned char lastf ;
    unsigned char park ;
    prop propsf ;
    expno sonf ;
    expno brof ;
    expno ptf ;
    expno numf ;
    struct exp_t *shf ;
} ;


/*
    THE EXPRESSION TYPE

    The type exp is a pointer to the structure given above.  Access to the
    fields of the structure is by means of the macros given in expmacs.h.
*/

typedef struct exp_t *exp ;

#endif




