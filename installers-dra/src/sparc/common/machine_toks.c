/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */



/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/machine_toks.c,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: machine_toks.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.7  1996/09/06  17:18:11  pwe
 * explicit next_callee_offset to correct double alignment
 *
 * Revision 1.6  1996/08/20  12:21:25  pwe
 * structures (etc) in varargs
 *
 * Revision 1.5  1996/08/15  15:55:19  pwe
 * add missing file headers
 *
--------------------------------------------------------------------------
*/


#include "config.h"

int 
machine_toks ( char *s )
{
/*  if (!strcmp(s, "~div"))
    return 1;
  if (!strcmp(s, "JMFprofile"))
    return 1;
  if (!strcmp(s, "JMFinline"))
    return 1;
*/
  if (!strcmp(s,"ansi.stdarg.__va_start"))
    return 1;
  if (!strcmp(s,"ansi.stdarg.va_arg"))
    return 1;
  if (!strcmp(s,"~next_caller_offset"))
    return 1;
  if (!strcmp(s,"~next_callee_offset"))
    return 1;
  if (!strcmp(s,"__sparc_special"))
    return 1;
  if(!strcmp(s,"~Sync_handler")){
    return 1;
  }
  return 0;
}
