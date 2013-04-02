/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef localtypes_key
#define localtypes_key 1

#include <construct/installtypes.h>

#include "exptypes.h"

struct asht {			/* structure definition for ash  */
  long  ashsize;	/*  the minimum size in bits of a shape
				*/
  long  ashalign;	/* the required alignment in bit units of
				   the start of a shape */
};

typedef struct asht ash;

extern ash ashof(shape s);

struct specit {
  bool is_special;
  exp special_exp;
};
typedef struct specit speci;


#endif
