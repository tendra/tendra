/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
   file.c
   file handling functions for the alpha translator.
*/

#include <stdio.h>

#include <shared/xalloc.h>

#include "config.h"

#include "fail.h"
#include "file.h"


/*
   Opens the file 'fname' with mode 'mode'.
*/
FILE *
open_file(char *fname, FileMode mode)
{
  char *options;
  FILE *fp;
  switch(mode){
   case WRITE:
    options="w";
    break;
   case READ:
    options="r";
    break;
  }
  if((fp = fopen(fname,options)) != NULL)
    return fp;
  else
    alphafail(CANNOT_OPEN_FILE,fname);
  return (FILE*)NULL;
}

void
close_file(FILE *fp)
{
  fclose(fp);
  return;
}



