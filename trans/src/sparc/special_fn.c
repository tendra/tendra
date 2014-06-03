/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <string.h>

#include <reader/exptypes.h>
#include <reader/expmacs.h>
#include <reader/codetypes.h>

#include <construct/installtypes.h>
#include <construct/exp.h>
#include <construct/special_fn.h>

/*
 * LOOK FOR SPECIAL FUNCTIONS
 */

/* ARGSUSED */ 
special
special_fn ( exp a1, exp a2, shape s )
{
    special spr ;
    spr.is_special = 0 ;
    spr.special_exp = NULL ;
    return spr;
}

