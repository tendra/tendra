/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EXPTYPES_INCLUDED
#define EXPTYPES_INCLUDED

#include <reader/codetypes.h>

#ifdef NEWDIAGS
#include <newdiag/dg_first.h>
#else
#include <diag/dg_first.h>
#include <diag/diaginfo.h>
#endif


/*
    TYPE REPRESENTING EXPRESSION PROPERTIES
*/

typedef unsigned short prop ;


/*
    UNION REPRESENTING AN EXPRESSION CONSTITUENT
*/

typedef union {
    struct exp_t *e ;
    char *str ;
    int l ;
    unsigned int ui ;
    float f ;
    struct dec_t *glob ;
#ifndef NEWDIAGS
    diag_info *d ;
#endif
    struct aldef_t *ald ;
} expno ;


/*
    TYPE REPRESENTING AN EXPRESSION
*/

struct exp_t {
    expno brof ;
    expno numf ;
    expno ptf ;
    expno sonf ;
    struct exp_t *shf ;
    prop propsf ;
    unsigned char namef ;
    unsigned int lastf : 1 ;
    unsigned int park : 1 ;
#ifdef NEWDIAGS
    diag_info * diagf; 
#endif
} ;

typedef struct exp_t *exp ;

#endif /* EXPTYPES_INCLUDED */
