/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/* 	$Id: file.c,v 1.1.1.1 1998/01/17 15:56:00 release Exp $	 */

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

#include "config.h"
#include "fail.h"
#include "file.h"
#include "xalloc.h"

/*
   Opens the file 'fname' with mode 'mode'.
*/
FILE *open_file
    PROTO_N ( ( fname,mode ) )
    PROTO_T ( char *fname X FileMode mode )
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

void close_file
    PROTO_N ( ( fp ) )
    PROTO_T ( FILE *fp )
{
  fclose(fp);
  return;
}



