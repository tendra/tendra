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


/* freebsd/machine.c */

#include "config.h"
#include "common_types.h"
#include "expmacs.h"
#include "exp.h"
#include "shapemacs.h"
#include "out.h"
#include "localflags.h"
#include "szs_als.h"

/* VARIABLES */

char * local_prefix = "L";
char * name_prefix = "_";



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
    if (n == cpdhd && sz != 8 && sz != 16 && sz != 32 && sz != 64)
      return 0;
    return 1;
  };
  if (n == cpdhd || n == nofhd)
    return 0;
  return 1;
}
