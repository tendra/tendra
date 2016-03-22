/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  handle_sregs.c
  This file contains code to handle preserved registers.
*/

#include <shared/bool.h>
#include <shared/error.h>

#include <flpt/flpt.h>

#include "alpha_ins.h"
#include "inst_fmt.h"
#include "addr.h"
#include "frames.h"
#include "reg_defs.h"

extern long frame_size;
extern int arg_stack_space;
extern int in_general_proc;

int  dumpstart;		/* where to start dumping fixeds */
int  fldumpstart;		/* where to start dumping floats */

int  fixdump;			/* all the fixeds to be dumped */
int  floatdump;		/* all the floats to be dumped */

int  fixdone;			/* the fixeds which have already been
				   dumped */
int  fltdone;			/* the floats which have already been
				   dumped */

static baseoff
dump_baseoff(int dstart)
{
  baseoff b;
  b.base = Has_vcallees?local_reg:(Has_fp?FP:SP);
  if(in_general_proc) {
    b.offset = (Has_vcallees)?(dstart - (frame_size>>3)):
      (Has_fp)?(dstart - (arg_stack_space+((frame_size+callee_size)>>3))):dstart;
  }
  else {
    b.offset = (Has_vcallees)?(dstart - (frame_size>>3)):
      (Has_fp)?(dstart - ((frame_size+callee_size)>>3)):dstart;
  }
  return b;
}


/*
** Dump registers to the stack.
*/
void
dump_sregs(unsigned int fdi, unsigned int fldi)
{
  unsigned int mask = 1<<31;
  int  ds=dumpstart-8;
  int fds=fldumpstart-8;
  unsigned int fd = fdi;
  unsigned int fld = fldi;
  baseoff b;
  int   i;
  b = dump_baseoff(ds);
  for(i=31;(fd!=0)&&(mask!=0);i--){
    if(fixdump&mask){
      /*b.offset = (ds +=8 );*/
      b.offset += 8;
      if(fd & mask){
	load_store(i_stq,i,b);
	fd &= ~mask;
      }	
    }
    mask>>=1;
  }
  if(fd!=0) error(ERR_INTERNAL, "fd != 0");
  mask=1<<31;
  b = dump_baseoff(fds);
  for (i = 31; (fld != 0)&&(mask!=0); i--){
    if (floatdump&mask) {
      b.offset += 8;
      /*b.offset = (fds+=8);*/
      if (fld & mask){
	fld &= ~mask;
	float_load_store(i_stt,i,b);
      }	
    }	
    mask>>=1;
  }
  if(fld!=0)error(ERR_SERIOUS, "float dump failed");
  fixdone |= fdi;
  fltdone |= fldi;
}


/*
  restore registers from stack.
*/
void
restore_sregs(unsigned int fd, unsigned int fld)
{
  unsigned int mask = 1<<31;
  int ds=dumpstart-8;
  int fds=fldumpstart-8;
  baseoff b = dump_baseoff(ds);
  int   i;
  for (i = 31; (fd != 0)&&(mask!=0); i--) {
    if (fixdump & mask) {
      b.offset += 8;
      /*b.offset = (ds+=8);*/
      if (fd & mask) {
	load_store(i_ldq,i,b);
	fd &= ~mask;
      }
    }
    mask >>= 1;
  }
  if(fd != 0) error(ERR_INTERNAL, "fd != 0");
  b = dump_baseoff(fds);
  mask = 1<<31;
  for (i = 31; (fld != 0)&(mask!=0); i--) {
    if (floatdump & mask) {
      b.offset += 8;
      /*b.offset = (fds+=8);*/
      if (fld & mask) {
	float_load_store(i_ldt,i,b);
	fld &= ~mask;
      }
    }
    mask = mask>>1;
  }
}














