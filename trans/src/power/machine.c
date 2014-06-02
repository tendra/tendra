/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "memtdf.h"
#include "machine.h"
#include "localexpmacs.h"

/* prefixes for assembler labels, set in translat.c */
char *local_prefix;
char *name_prefix;


/* Is the result of a procedure delivering this shape produced in registers? */
bool reg_result(shape sha)
{
  return is_floating(name(sha) ||
    (shape_size(sha) <= 32 && !IS_AGGREGATE(sha)));
}
