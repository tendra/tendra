/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  This function recognises special tokens used by the 
  alpha installer 
*/

#include <string.h>

int
machine_toks(char *s)
{
  
  if (!strcmp(s,"__builtin_isfloat"))  return 1;
  if (!strcmp(s,"__builtin_va_start")) return 1;
  if (!strcmp(s,"__builtin_va_token")) return 1;
  if (!strcmp(s,"__alpha_special"))    return 1;
  if (!strcmp(s,"~Sync_handler"))      return 1;
  return 0;
}




