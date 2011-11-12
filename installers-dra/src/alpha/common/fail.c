/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef lint
static char vcid[] = "$Id: fail.c,v 1.1.1.1 1998/01/17 15:56:00 release Exp $";
#endif /* lint */

/*
$Log: fail.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:00  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1995/09/13  08:22:59  john
 * Addition for exception handling
 *
 * Revision 1.4  1995/09/06  09:00:58  john
 * removed old command line argument parsing
 *
 * Revision 1.3  1995/05/16  10:48:19  john
 * Cosmetic changes
 *
 * Revision 1.2  1995/03/29  14:07:18  john
 * Added a couple of breaks
 *
 * Revision 1.1.1.1  1995/03/23  10:39:07  john
 * Entered into CVS
 *
 * Revision 1.5  1995/01/12  15:04:26  john
 * Changed message formats
 *
*/

/*
   fail.c

   This file contains the error handling functions for the 
   alpha translator.
*/

#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "fail.h"
#include "pseudo.h"
#define USEAGE_STRING "alphatrans -[ABCDEFHIKMPQRSUXVWZu] file.t file.G file.T [file.s]"
void
alphafail(fail_conditions reason, char *message, char *extra_info)
{
  int fatal=0;
  static int warnings=0;
  switch(reason){
  case FILE_OPEN:
    fprintf(stderr,"Error: Cannot Open file %s",message);
    fatal=1;
    break;
  case USEAGE:
    fprintf(stderr,"Error: %s\nuseage: is %s",message,USEAGE_STRING);
    fatal=1;
    break;
  case OVERFLOW:
    fprintf(stderr,"Overflow error: %s",message);
    fatal=1;
    break;
  case CROSS_IMPLEMENTATION:
    fprintf(stderr,
	    "Error: incomplete implementation on this machine: %s",
	    message);
    fatal=1;
    break;
  case REG_ALLOC:
    fprintf(stderr,"Error: error in register allocation: %s",message);
    comment("***ERROR HERE***");
    fatal=0;
    break;
  case IMPLEMENTATION:
    fprintf(stderr,"Warning: implementation : %s",message);
    ++warnings;
    break;
  case INSTRUCTION_OUTPUT:
    fprintf(stderr,"Warning: assembler output: %s",message);
    ++warnings;
    break;
  case MISC:
    fprintf(stderr,"Warning: %s",message);
    ++warnings;
    break;
  case INTERNAL:
    fprintf(stderr,"Internal error: %s",message);
    fatal=1;
    break;
  }
  fprintf(stderr,"%s\n",extra_info);
  fatal = fatal || (warnings>MAX_WARNINGS);
  if(fatal) exit(EXIT_FAILURE);
  return;
}
