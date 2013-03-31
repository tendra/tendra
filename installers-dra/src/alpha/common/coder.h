/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CODER_H
#define CODER_H

#include "config.h"

#include <construct/installtypes.h>
#include "addresstypes.h"
#include "procrectypes.h"
#include "exptypes.h"

extern where nowhere;
extern int fscopefile;

extern bool last_param(exp);
extern makeans make_code(exp e, space sp, where dest, int exitlab);
extern int bitsin(int);


typedef struct _postl {
  exp postlude;
  struct _postl * outer;
} postlude_chain;


#define start_new_capsule(X)
#define close_capsule()
#define false 0
#define true 1

#endif
