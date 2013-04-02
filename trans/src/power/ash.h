/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef ASHDECS_H
#define ASHDECS_H	1

#include "memtdf.h"

#include <construct/installtypes.h>


struct asht {			/* structure definition for ash */
  long  ashsize;		/* the minimum size in bits of a shape */
  long  ashalign;		/* the required alignment in bit units of
				   the start of a shape */
};

typedef struct asht ash;


extern ash ashof(shape);

#endif


