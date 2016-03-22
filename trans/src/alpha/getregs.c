/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/error.h>

#include <local/exp.h>

#include <tdf/tag.h>

#include <reader/exp.h>

#include <construct/exp.h>

#include <flpt/flpt.h>

#include <utility/int64.h>

#include "procrec.h"
#include "regexps.h"
#include "bitsmacs.h"
#include "getregs.h"

static int useable_fixed;
static int useable_float;

#define for1  0x002	
#define for2  0x004
#define for8  0x100	/* bit pattern for $8,  bit 9 is set */
#define for10 0x400	/* bit pattern for $10, bit 11 set */
#define for11 0x800
#define for15 0x8000	/* bit pattern for $15, bit 16 is set */
#define for24 0x1000000		/* etc ... */
#define for25 0x2000000

#define for0  0x1
#define for4  0x10
#define for5  0x20
#define for9  0x200


static int regs_corrupted_by_div = (1<<23)|(1<<24)|(1<<25)|(1<<27);



static int choosefloat = for1; /* first float reg to be allocated */
static int choosefix   = for1; /* first fixed reg to be allocated */

static int currentfloat = 1;
static int currentfix   = 1;
static int maxfloat     = 31; /* dubious */
static int maxfixed;

/* 
   tag is a proc. settempregs sets up useable_fixed etc depending 
   on how the proc treats its parameters; if they are destined for
   store or s-registers we can use some of the parameter registers 
*/
void
settempregs(exp tag)
{
  procrec * pr = &procrecs[no(tag)];
  bool leaf = ((pr->needsproc).propneeds & anyproccall)==0;
  exp stag = son(tag);
  currentfix = 1;
  currentfloat = 1;
  choosefix = for1;
  choosefloat = for1;
  useable_fixed = 0x03ff01ff;	/* leaves out parameter registers */
  useable_float = 0x7fc0fc00;
  if(has_machine_division(tag)){
    useable_fixed &= ~regs_corrupted_by_div;
  }
  if (leaf) {
    maxfixed=31;
  }
  else maxfixed = 31;
  
  while (stag->tag==ident_tag && isparam(stag)) {
    if ((props(stag) & inreg_bits) !=0 ) {
      useable_fixed &= ~ (1<<no(stag));
    }
    else
      if ((props(stag) & infreg_bits) != 0) {
	useable_float &= ~(1<<no(stag));
      }
    stag = bro(son(stag));
  }
}

/*
  Gets a free temporary fixed point register.  The int fixed masks 
  out registers which are not available.
*/
int
getreg(int32 fixed)
{
  int reg=-1;
  int start = choosefix;
  bool out_of_regs=0;
  for(;(!out_of_regs)&&(reg==-1);){
    if(currentfix>=maxfixed){
      currentfix=1;
      choosefix=for1;
    }
    else{
      currentfix++;
      choosefix<<=1;
    }
    if(!(choosefix&fixed) && (choosefix&useable_fixed)){
      reg = currentfix;
    }
    out_of_regs = (reg==-1)&&(choosefix==start);
  }
  if(out_of_regs){
    error(ERR_SERIOUS, "Register allocation: Too many fixed point t-regs required");
  }
  clear_reg(reg);
  return reg;
}


/*
  Get a free temporary floating point register.
*/
int
getfreg(int fl)
{
  int freg=-1;
  int start = choosefloat;
  bool out_of_regs=0;
  for(;(!out_of_regs)&&(freg==-1);){
    if(currentfloat>=maxfloat){
      currentfloat=10;
      choosefloat=for10;
    }
    else{
      currentfloat++;
      choosefloat<<=1;
    }
    if(!(choosefloat&fl) && (choosefloat&useable_float)){
      freg = currentfloat;
    }
    out_of_regs = (freg==-1)&&(choosefloat==start);
  }
  if(out_of_regs){
    error(ERR_SERIOUS, "Register allocation: Too many floating point t-regs required");
  }
  return freg;
}



