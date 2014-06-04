/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* psu_ops.c
	Output various psuedo operations to assembler
*/

#include <stdio.h>

#include <main/driver.h>

#include "ibinasm.h"
#include "out_ba.h"
#include "psu_ops.h"

void
setnoreorder(void)
{
  if (as_file)
    fprintf (as_file, "\t.set\tnoreorder\n");
  out_value (0, iset, set_noreorder, 0);
}

void
setreorder(void)
{
  if (as_file)
    fprintf (as_file, "\t.set\treorder\n");
  out_value (0, iset, set_reorder, 0);
}

void
setnomove(void)
{
  if (as_file)
    fprintf (as_file, "\t.set\tnomove\n");
  out_value (0, iset, set_nomove, 0);
}

void
setmove(void)
{
  if (as_file)
    fprintf (as_file, "\t.set\tmove\n");
  out_value (0, iset, set_move, 0);
}

void
setvolatile(void)
{
  if (as_file)
    fprintf (as_file, "\t.set\tvolatile\n");
  out_value (0, iset, set_volatile, 0);
}

void
setnovolatile(void)
{
  if (as_file)
    fprintf (as_file, "\t.set\tnovolatile\n");
  out_value (0, iset, set_novolatile, 0);
}

void
setnoat(void)
{
  if (as_file)
    fprintf (as_file, "\t.set\tnoat\n");
  out_value (0, iset, set_noat, 0);
}

void
setat(void)
{
  if (as_file)
    fprintf (as_file, "\t.set\tat\n");
  out_value (0, iset, set_at, 0);
}

void
comment(char *mess)
{
  if (as_file)
    fprintf (as_file, " ## %s\n", mess);
}

void
setframe(long st)
{
  if (as_file)
    fprintf (as_file, "\t.frame\t$sp, %ld, $31\n", st);
  out_frame (0, iframe, st, 29, 31);
}

void
settext(void)
{
  if (as_file)
    fprintf (as_file, "\t.text\n");
  out_common (0, itext);
}

void
setmask(long mask, long disp)
{
  if (as_file)
    fprintf (as_file, "\t.mask\t0x%lx,%ld\n", mask, disp);
  out_mask (0, imask, mask, disp);
}

void
setfmask(long mask, long disp)
{
  if (as_file)
    fprintf (as_file, "\t.fmask\t0x%lx,%ld\n", mask, disp);
  out_mask (0, ifmask, mask, disp);
}
