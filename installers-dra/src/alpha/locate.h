/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
   locatedecs.h
   externs from locate.c
*/

#include <construct/installtypes.h>
#include "exptypes.h"
#include "addresstypes.h"
#include "procrectypes.h"


extern int locals_offset;
extern int frame_size;


extern  baseoff boff(exp x);
extern  where locate(exp e, space sp, shape s, int dreg);
extern  bool simplepars;
