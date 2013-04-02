/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
   fail.c

   This file contains the error handling functions for the 
   alpha translator.
*/

#include <stdlib.h>
#include <stdio.h>

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
