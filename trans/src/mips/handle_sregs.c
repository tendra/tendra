/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* handle_sregs.c
	handle_sregs dumps and recovers the s-registers;
	the registers to be dumped are expressed as bits in a long eg
	bit 31 => reg 31 must be dumped.
	They are called in the dump_tag part of make_code.

****************************************************************/

#include <assert.h>

#include <shared/bool.h>

#include <reader/basicread.h>

#include "mips_ins.h"
#include "inst_fmt.h"
#include "addrtypes.h"
#include "frames.h"
#include "handle_sregs.h"
#include "localexpmacs.h"

extern long frame_size;
long  dumpstart;		/* where to start dumping fixeds */
long  fldumpstart;		/* where to start dumping floats */

long  fixdump;			/* all the fixeds to be dumped */
long  floatdump;		/* all the floats to be dumped */

long  fixdone;			/* the fixeds which have already been
				   dumped */
long  fltdone;			/* the floats which have already been
				   dumped */

/* dump_sreg, dump_sfreg & recover .. etc not used at present!! */

static baseoff
dump_baseoff(long ds)
{	baseoff b;
	b.base = (Has_vcallees)?local_reg:(29+Has_fp);
	b.offset = (Has_vcallees)?(ds - (frame_size>>3)):
		   (Has_fp)?(ds - ((frame_size+callee_size)>>3)):ds;
        return b;
}

void
dump_sreg(int n)
{
   unsigned long maskn = 1 << n;
   unsigned long mask = 1 << 31;
   int i;
   baseoff b;
   b = dump_baseoff(dumpstart);
   assert(maskn & fixdump);

   for(i = 31; ; i--) {
       if (mask & fixdump) b.offset -=4;
       if (i== n) {
       		ls_ins(i_sw, n, b);
       		fixdone |= maskn;
       		return;
       }
       mask >>= 1;
   }
}

void
dump_sfreg(int n)
{
   unsigned long maskn = 3 << n;
   unsigned long mask = 3 << 30;
   int i;
   baseoff b;
   b = dump_baseoff(fldumpstart);
   assert(maskn & floatdump);

   for (i =30; ; i-=2) {
      if (mask & floatdump) b.offset -=8;
      if (i==n) {
      	   	lsfp_ins(i_s_d, i, b);
      	   	fltdone |= maskn;
      	   	return;
      }
      mask >>= 2;
   }
}

void
recover_sreg(int n)
{
   unsigned long maskn = 1 << n;
   unsigned long mask = 1 << 31;
   int i;
   baseoff b;
   b = dump_baseoff(dumpstart);
   assert(maskn & fixdump);

   for(i = 31; ; i--) {
       if (mask & fixdump) b.offset -=4;
       if (i== n) {
       		ls_ins(i_lw, n, b);
       		fixdone &= ~maskn;
       		return;
       }
       mask >>= 1;
   }
}

void
recover_sfreg(int n)
{
   unsigned long maskn = 3 << n;
   unsigned long mask = 3 << 30;
   int i;
   baseoff b;
   b = dump_baseoff(fldumpstart);
   assert(maskn & floatdump);

   for (i =30; ; i-=2) {
      if (mask & floatdump) b.offset -=8;
      if (i==n) {
      	   	lsfp_ins(i_l_d, i, b);
      	   	fltdone &= ~maskn;
      	   	return;
      }
      mask >>= 2;
   }
}

void
dump_sregs(long fdi, long fldi)
{
  unsigned long mask = 1 << 31;
  long fd = fdi;
  long fld = fldi;
  baseoff b;
  int   i;
  b = dump_baseoff(dumpstart);

  for (i = 31; fd != 0; i--) {
    if (mask & fixdump) {
      b.offset -= 4;
      if (mask & fd) {
	ls_ins (i_sw, i, b);
	fd &= ~mask;
      }
    }
    mask = mask >> 1;
  }

  b = dump_baseoff(fldumpstart);
  mask = 3 << 30;
  for (i = 30; fld != 0; i -= 2) {
    if ((mask & floatdump) == mask) {
      b.offset -= 8;
      if (mask & fld) {
	lsfp_ins (i_s_d, i, b);
	fld &= ~mask;
      }
    }
    mask = mask >> 2;
  }
  fixdone |= fdi;
  fltdone |= fldi;
}



void
restore_sregs(long fd, long fld)
{
  unsigned long mask = 1 << 31;
  baseoff b;
  int   i;
  b = dump_baseoff(dumpstart);

  for (i = 31; fd != 0; i--) {
    if (mask & fixdump) {
      b.offset -= 4;
      if (mask & fd) {
	ls_ins (i_lw, i, b);
	fd &= ~mask;
      }
    }
    mask = mask >> 1;
  }

 b = dump_baseoff(fldumpstart);
  mask = 3 << 30;
  for (i = 30; fld != 0; i -= 2) {
    if ((mask & floatdump) == mask) {
      b.offset-= 8;
      if (mask & fld) {
	lsfp_ins (i_l_d, i, b);
	fld &= ~mask;
      }
    }
    mask = mask >> 2;
  }
}

void
dump_all_sregs(void)
{
  unsigned long mask = 1 << 31;
  long fd = fixdump;
  long fld = floatdump;
  baseoff b;
  int   i;

  b = dump_baseoff(dumpstart);
  for (i = 31; fd != 0; i--) {
    if (mask & fixdump) {
      b.offset-= 4;
      ls_ins (i_sw, i, b);
      fd &= ~mask;
    }
    mask = mask >> 1;
  }

  b = dump_baseoff(fldumpstart);
  mask = 3 << 30;
  for (i = 30; fld != 0; i -= 2) {
    if ((mask & floatdump) == mask) {
      b.offset-= 8;
      lsfp_ins (i_s_d, i, b);
      fld &= ~mask;
    }
    mask = mask >> 2;
  }
  fixdone = fixdump;
  fltdone = floatdump;
}
