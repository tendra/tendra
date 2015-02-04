/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CODER_H
#define CODER_H

#include <shared/bool.h>

#include <reader/exp.h>

#include <construct/installtypes.h>

#include "addresstypes.h"
#include "procrectypes.h"

extern int use_umulh_for_div;
extern bool fail_with_denormal_constant;
extern bool treat_denorm_specially;

extern where nowhere;
extern int fscopefile;

extern bool last_param(exp);
extern makeans make_code(exp e, space sp, where dest, int exitlab);


typedef struct _postl {
  exp postlude;
  struct _postl * outer;
} postlude_chain;


#define start_new_capsule(X)
#define close_capsule()

#endif
