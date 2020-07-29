/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
	Output various psuedo operations to assembler
*/

#include <stdio.h>

#include <main/driver.h>
#include <main/print.h>

#include "ibinasm.h"
#include "out_ba.h"
#include "pseudo.h"

void
setnoreorder(void)
{
  if (as_file)
    asm_printop(".set noreorder");
  out_value (0, iset, set_noreorder, 0);
}

void
setreorder(void)
{
  if (as_file)
    asm_printop(".set reorder");
  out_value (0, iset, set_reorder, 0);
}

void
setnomove(void)
{
  if (as_file)
    asm_printop(".set nomove");
  out_value (0, iset, set_nomove, 0);
}

void
setmove(void)
{
  if (as_file)
    asm_printop(".set move");
  out_value (0, iset, set_move, 0);
}

void
setvolatile(void)
{
  if (as_file)
    asm_printop(".set volatile");
  out_value (0, iset, set_volatile, 0);
}

void
setnovolatile(void)
{
  if (as_file)
    asm_printop(".set novolatile");
  out_value (0, iset, set_novolatile, 0);
}

void
setnoat(void)
{
  if (as_file)
    asm_printop(".set noat");
  out_value (0, iset, set_noat, 0);
}

void
setat(void)
{
  if (as_file)
    asm_printop(".set at");
  out_value (0, iset, set_at, 0);
}

void
setframe(long st)
{
  if (as_file)
    asm_printop(".frame $sp, %ld, $31", st);
  out_frame (0, iframe, st, 29, 31);
}

void
settext(void)
{
  if (as_file)
    asm_printop(".text");
  out_common (0, itext);
}

void
setmask(long mask, long disp)
{
  if (as_file)
    asm_printop(".mask 0x%lx,%ld", mask, disp);
  out_mask (0, imask, mask, disp);
}

void
setfmask(long mask, long disp)
{
  if (as_file)
    asm_printop(".fmask 0x%lx,%ld", mask, disp);
  out_mask (0, ifmask, mask, disp);
}
