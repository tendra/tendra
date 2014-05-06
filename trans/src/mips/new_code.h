/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <construct/installtypes.h>

#include "addrtypes.h"
#include "procrectypes.h"
#include <local/exptypes.h>

extern  where nowhere;

extern makeans make_code(exp e, space sp, where dest, int exitlab);
extern bool last_param(exp e);
extern int bitsin(long);
