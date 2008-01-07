/*
 * Copyright (c) 2003, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/* 	handle_sregs.c,v 1.3 1995/08/21 08:44:43 john Exp	 */

#ifndef lint
static char vcid[] = "handle_sregs.c,v 1.3 1995/08/21 08:44:43 john Exp";
#endif /* lint */

/*
  handle_sregs.c
  This file contains code to handle preserved registers.
*/



#include "config.h"
#include "alpha_ins.h"
#include "inst_fmt.h"
#include "addresstypes.h"
#include "frames.h"
#include "reg_defs.h"
#include "maxminmacs.h"
#include "fail.h"
#include "coder.h"
#include "procrectypes.h"
#include "locate.h"

int  dumpstart;		/* where to start dumping fixeds */
int  fldumpstart;		/* where to start dumping floats */

int  fixdump;			/* all the fixeds to be dumped */
int  floatdump;		/* all the floats to be dumped */

int  fixdone;			/* the fixeds which have already been
				   dumped */
int  fltdone;			/* the floats which have already been
				   dumped */

baseoff
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
  if(fd!=0) failer("fd <> 0");
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
  if(fld!=0)failer("float dump failed\n");
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
  if(fd != 0) failer("fd<>0");
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














