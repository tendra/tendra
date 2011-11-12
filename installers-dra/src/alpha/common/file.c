/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef lint
static char vcid[] = "$Id: file.c,v 1.1.1.1 1998/01/17 15:56:00 release Exp $";
#endif /* lint */

/*
   file.c
   file handling functions for the alpha translator.
*/

/*
$Log: file.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:00  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/04/07  11:02:41  john
 * Removed unecessary call to xcalloc.
 *
 * Revision 1.1.1.1  1995/03/23  10:39:08  john
 * Entered into CVS
 *
 * Revision 1.6  1995/01/26  13:40:29  john
 * Added return to open_file
 *
 * Revision 1.5  1995/01/12  15:13:12  john
 * Changed error reporting
 *
*/

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



