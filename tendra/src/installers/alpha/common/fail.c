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


/* 	$Id: fail.c,v 1.1.1.1 1998/01/17 15:56:00 release Exp $	 */

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

#include "config.h"
#include "fail.h"
#include "pseudo.h"
#define USEAGE_STRING "alphatrans -[ABCDEFHIKMPQRSUXVWZu] file.t file.G file.T [file.s]"
void alphafail
    PROTO_N ( ( reason,message,extra_info ) )
    PROTO_T ( fail_conditions reason X char *message X char *extra_info )
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
