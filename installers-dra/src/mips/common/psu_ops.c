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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:06 $
$Revision: 1.1.1.1 $
$Log: psu_ops.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* psu_ops.c
	Output various psuedo operations to assembler
*/

#include "config.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "psu_ops.h"

extern  FILE * as_file;


void setnoreorder
    PROTO_Z ()
{
  if (as_file)
    fprintf (as_file, "\t.set\tnoreorder\n");
  out_value (0, iset, set_noreorder, 0);
}

void setreorder
    PROTO_Z ()
{
  if (as_file)
    fprintf (as_file, "\t.set\treorder\n");
  out_value (0, iset, set_reorder, 0);
}

void setnomove
    PROTO_Z ()
{
  if (as_file)
    fprintf (as_file, "\t.set\tnomove\n");
  out_value (0, iset, set_nomove, 0);
}

void setmove
    PROTO_Z ()
{
  if (as_file)
    fprintf (as_file, "\t.set\tmove\n");
  out_value (0, iset, set_move, 0);
}

void setvolatile
    PROTO_Z ()
{
  if (as_file)
    fprintf (as_file, "\t.set\tvolatile\n");
  out_value (0, iset, set_volatile, 0);
}

void setnovolatile
    PROTO_Z ()
{
  if (as_file)
    fprintf (as_file, "\t.set\tnovolatile\n");
  out_value (0, iset, set_novolatile, 0);
}

void setnoat
    PROTO_Z ()
{
  if (as_file)
    fprintf (as_file, "\t.set\tnoat\n");
  out_value (0, iset, set_noat, 0);
}

void setat
    PROTO_Z ()
{
  if (as_file)
    fprintf (as_file, "\t.set\tat\n");
  out_value (0, iset, set_at, 0);
}

void comment
    PROTO_N ( (mess) )
    PROTO_T ( char *mess )
{
  if (as_file)
    fprintf (as_file, " ## %s\n", mess);
}

void setframe
    PROTO_N ( (st) )
    PROTO_T ( long st )
{
  if (as_file)
    fprintf (as_file, "\t.frame\t$sp, %ld, $31\n", st);
  out_frame (0, iframe, st, 29, 31);
}

void settext
    PROTO_Z ()
{
  if (as_file)
    fprintf (as_file, "\t.text\n");
  out_common (0, itext);
}

void setmask
    PROTO_N ( (mask, disp) )
    PROTO_T ( long mask X long disp )
{
  if (as_file)
    fprintf (as_file, "\t.mask\t0x%lx,%ld\n", mask, disp);
  out_mask (0, imask, mask, disp);
}

void setfmask
    PROTO_N ( (mask, disp) )
    PROTO_T ( long mask X long disp )
{
  if (as_file)
    fprintf (as_file, "\t.fmask\t0x%lx,%ld\n", mask, disp);
  out_mask (0, ifmask, mask, disp);
}
