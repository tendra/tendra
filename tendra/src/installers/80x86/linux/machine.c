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


/* linux/machine.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: machine.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.6  1996/03/12  12:44:28  pwe
 * 64-bit ints compatible with gcc long long
 *
 * Revision 1.5  1996/02/08  13:45:32  pwe
 * Linux elf v aout option
 *
 * Revision 1.4  1995/10/02  08:12:15  pwe
 * correct gcc reg_result structs
 *
 * Revision 1.3  1995/09/29  16:18:07  pwe
 * gcc_compatible default on Linux
 *
 * Revision 1.2  1995/01/30  12:57:14  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/11/08  16:28:22  jmf
 * Initial revision
 *
 * Revision 1.3  1994/07/13  07:51:05  jmf
 * Added Log
 *
**********************************************************************/



#include "config.h"
#include "common_types.h"
#include "expmacs.h"
#include "exp.h"
#include "shapemacs.h"
#include "out.h"
#include "localflags.h"
#include "szs_als.h"

/* VARIABLES */
/* All variables are initialised, jmf */

int linux_elf = 1;

char * local_prefix = ".L";
char * name_prefix = "";



/* PROCEDURES */

void set_linux_format
    PROTO_N ( (elf) )
    PROTO_T ( int elf )
{
  linux_elf = elf;
  if (elf) {
    local_prefix = ".L";
    name_prefix = "";
  }
  else {
    local_prefix = "L";
    name_prefix = "_";
  }
  return;
}


/* is the result of a procedure delivering
   this shape produced in registers. */
int reg_result
    PROTO_N ( (sha) )
    PROTO_T ( shape sha )
{
  unsigned char  n = name(sha);
  if (gcc_compatible) {
    int sz = shape_size(sha);
    if (n == nofhd)
      return 0;
    if (n == cpdhd && sz != 8 && sz != 16 && sz != 32 && sz != 64)
      return 0;
    return 1;
  };
  if (n == cpdhd || n == nofhd)
    return 0;
  return 1;
}



