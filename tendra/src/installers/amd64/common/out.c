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


/* 80x86/out.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: out.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/04/17  11:55:58  pwe
 * dwarf2 improvements
 *
 * Revision 1.3  1997/03/20  16:24:02  pwe
 * dwarf2
 *
 * Revision 1.2  1995/01/30  12:56:38  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:38:46  jmf
 * Initial revision
 *
**********************************************************************/


/*******************************************************************
                                out.c

   defines the low level output routines

*******************************************************************/

#include "config.h"
#include "common_types.h"
#include "basicread.h"
#include "flags.h"
#include "localflags.h"
#include "instr.h"
#include "messages_8.h"
#include "out.h"

#ifdef NEWDWARF
#include "dw2_config.h"
#endif


/* VARIABLES */
/* All variables initialised */

FILE * fpout;	/* init by outinit */

#ifdef NEWDWARF
long instr_count = -1;
#endif


/* PROCEDURES */

int outinit
    PROTO_N ( (intermed) )
    PROTO_T ( char *intermed )
{
  fpout = fopen (intermed, "w");
  return (fpout != (FILE *) 0);
}

void outc
    PROTO_N ( (c) )
    PROTO_T ( char c )
{
  int   st = fputc (c, fpout);
  if (st == EOF) {
    failer (BAD_OUTPUT);
    exit(EXIT_FAILURE);
  };
}

void outs
    PROTO_N ( (s) )
    PROTO_T ( char *s )
{
  int   st = fputs (s, fpout);
  if (st == EOF) {
    failer (BAD_OUTPUT);
    exit(EXIT_FAILURE);
  };
}




void outnl
    PROTO_Z ()
{

  int   st = fputs ("\n", fpout);
  if (st == EOF) {
    failer (BAD_OUTPUT);
    exit(EXIT_FAILURE);
  };

#ifdef NEWDWARF
  instr_count = -1;
#endif
  last_jump_label = -1;
  keep_short = is80586;
  return;
}



void outn
    PROTO_N ( (n) )
    PROTO_T ( long n )
{
  int   st = fprintf (fpout, "%ld", n);
  if (st == EOF) {
    failer (BAD_OUTPUT);
    exit(EXIT_FAILURE);
  };

}

void outhex
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  int   st = fprintf (fpout, "0x%x", (unsigned int)n);
  if (st == EOF) {
    failer (BAD_OUTPUT);
    exit(EXIT_FAILURE);
  };

}
