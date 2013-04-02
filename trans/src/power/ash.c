/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "ash.h"

/*
 * ash.c:
 * ashof is for historical compatibility, from before 
 * shape_size() & shape_align() 
 */
ash ashof(shape s)
{
  ash a;

  a.ashsize = shape_size(s);
  a.ashalign = shape_align(s);
  return a;
}
