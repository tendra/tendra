/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include "config.h"

int 
machine_toks ( char *s )
{
/*if (!strcmp(s, "~div"))       return 1;
  if (!strcmp(s, "JMFprofile")) return 1;
  if (!strcmp(s, "JMFinline"))  return 1;
*/
  if (!strcmp(s, "ansi.stdarg.__va_start")) return 1;
  if (!strcmp(s, "ansi.stdarg.va_arg"))     return 1;
  if (!strcmp(s, "~next_caller_offset"))    return 1;
  if (!strcmp(s, "~next_callee_offset"))    return 1;
  if (!strcmp(s, "__sparc_special"))        return 1;
  if (!strcmp(s, "~Sync_handler"))          return 1;
  return 0;
}
