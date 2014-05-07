/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef localtypes_key
#define localtypes_key 1

#include <local/exptypes.h>

#include <construct/installtypes.h>

#include "memtdf.h"


struct specit {
  bool is_special;
  exp special_exp;
};
typedef struct specit speci;



#endif
