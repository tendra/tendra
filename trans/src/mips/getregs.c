/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Routines for choosing temporary registers. The next free register is
 * chosen cyclically from the registers 8-15, 24 and 25 for fixed point
 * and 4-10 and 16-18 in floating point (a factor of 2 is involved here)
 * by examining the bit pattern of the parameter.
 *
 * If the current proc allows it, regs 4-7 may also be used as t-regs
 * - this is the function of chooseafter25 etc. The parameter is usually
 * taken from a value of type space (which has bits for fixed and
 * floating regs).
 *
 * A clear bit indicates that the corresponding register is free for use.
 */

#include <shared/bool.h>
#include <shared/error.h>

#include <reader/exp.h>
#include <reader/basicread.h>

#include <construct/exp.h>
#include <construct/tags.h>

#include <main/flags.h>

#include "procrectypes.h"
#include "regexps.h"
#include "bitsmacs.h"
#include "getregs.h"

extern  procrec * procrecs;
static long useable_fixed;
static long useable_float;

#define for8  0x100		/* bit pattern for $8,  bit 9 is set */
#define for15    0x8000		/* bit pattern for $15, bit 16 is set */
#define for24 0x1000000		/* etc ... */
#define for25 0x2000000

#define for0  0x1
#define for4  0x10
#define for5  0x20
#define for9  0x200


static long  choosefix = for8;		/* first fixed reg to be allocated */
static long  choosefloat = for0;	/* first float reg to be allocated */

static int currentfix   = 8;
static int currentfloat = 2;
static int maxfixed;
static int maxfloat = 9;
static int minfixed;
static long formin;

/*
 * tg is a proc; sets up useable_fixed etc depending on how the proc
 * treats its parameters; if they are destined for store or s-registers
 * we can use some of regs 4-7
 */
void
settempregs(exp tg)
{
  procrec * pr = &procrecs[no(tg)];
  bool leaf = ((pr->needsproc).propsneeds & anyproccall)==0;
  exp stg = son(tg);
  currentfix = 8;
  currentfloat = 0;
  choosefix = for8;
  choosefloat = for0;
  useable_fixed = 0x8300fffc;
	/* r31 (lnk) /r24-25/ r8-r15/ r4-r7 (pars) /r2-r3*/
  useable_float = 0x3ff;	/* f0-f2 (resreg) f4-f10 f12-f14 (pars) f16-f18*/
  if (leaf) {
  	useable_fixed &= ~0x80000000;
  	maxfixed = 25;
  }
  else maxfixed = 31;

  if (PIC_code) {
	useable_fixed &= ~0x02000000;
	if (maxfixed==25) maxfixed = 24;
  }

  if (((pr->needsproc).propsneeds & uses2_bit) != 0) {
	useable_fixed &= ~0x4;
	minfixed = 3;
	formin = 0x8;
  }
  else {
	minfixed = 2;
	formin = 0x4;
  }

  while (name(stg)==ident_tag && isparam(stg)) {
  	if ((props(stg) & inreg_bits) !=0 ) {
  		useable_fixed &= ~ (1<<no(stg));
  	}
  	else
  	if ((props(stg) & infreg_bits) != 0) {
  		useable_float &= ~(1<<no(stg));
  	}
  	stg = bro(son(stg));
  }

}

int
getreg(long fixed)
{	/* get a free temporary fixed pt reg */
  int   reg = -1;
  long  start = choosefix;


  for (;;) {
    if ((choosefix & fixed) == 0) {
      reg = currentfix;
    }
  cycle:
    if (currentfix >= maxfixed) {
    	currentfix = minfixed;
    	choosefix = formin;
    }
    else {
      currentfix +=1;
      choosefix <<= 1;
    }

    if ((choosefix & useable_fixed) != 0) {
    	if (reg >=0) break;
    	else continue;
    }
    if (choosefix == start) {
    	error(ERR_INTERNAL, "Too many fixed regs required");
    		break;
    }
    goto cycle;
  }
  return reg;
}


int
getfreg(long fl)
{	/* get a free temporary floating reg */
  int   reg = -1;
  long  start = choosefloat;

  for (;;) {
    if ((choosefloat & fl) == 0) {
      reg = currentfloat;
    }
  cycle:
    if (currentfloat >= maxfloat) {
    	currentfloat = 0;
    	choosefloat = for0;
    }
    else {
      currentfloat +=1;
      choosefloat <<= 1;
    }

    if ((choosefloat & useable_float) != 0) {
    	if (reg >=0) break;
    	else continue;
    }
    if (choosefloat == start) {
    	error(ERR_INTERNAL, "Too many float regs required");
    		break;
    }
    goto cycle;
  }
  return reg;
}
