/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include "config.h"

int machine_toks
(char * s)
{
  if (!strcmp(s, "~div"))
    return 1;
  if (!strcmp(s, "~rem"))
    return 1;
  if (!strcmp(s, "JMFprofile"))
    return 1;
  if (!strcmp(s, "JMFinline"))
    return 1;

  return 0;
}
