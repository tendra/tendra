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


/* svr4/machine.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:53 $
$Revision: 1.1.1.1 $
$Log: machine.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1996/03/12  12:44:43  pwe
 * 64-bit ints compatible with gcc long long
 *
 * Revision 1.2  1995/01/30  12:57:42  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  12:16:59  jmf
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

char * local_prefix = ".L";
char * name_prefix = "";


/* PROCEDURES */

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
    if (n == cpdhd && sz > 32 && sz != 64)
      return 0;
    return 1;
  };
  if (n == cpdhd || n == nofhd)
    return 0;
  return 1;
}



