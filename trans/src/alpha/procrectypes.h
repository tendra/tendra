/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* procrectypes.h
     types for properties of procs
      needs, weights,parpair,procrec,spacereq
*/

#include <local/exptypes.h>

#ifndef procreckey

#define procreckey 1

#define wfixno 25
#define wfloatno 16

struct needst {
  int   fixneeds;		/* no of fixed t-regs required */
  int   floatneeds;		/* no of float t-regs required */
        prop propsneeds;	/* various binary properties of exp */
  int   maxargs;		/* size in bits for actual parameters in
				   exp */
  int 	numparams;	/* size in bits of parameters to function */
  
};
typedef struct needst needs;

struct weightst {
  float fix[wfixno];
  float  floating[wfloatno];
};
typedef struct weightst weights;
 /* used to allocate tags to registers */


struct spacereqt {
  int  fixdump;
  int 	fltdump;
  int  stack;
};
typedef struct spacereqt  spacereq;
 /* used characterise s-reg and stack requirements of proc */

struct procrect {
  needs needsproc;
  spacereq spacereqproc;
  int frame_size;
  int locals_offset;
  int max_args;
  int paramsdumpstart;
  int fixdump;
  int floatdump;
  int dumpstart;
  int fldumpstart;
  int callee_size;
};
typedef struct procrect procrec;
 /* various properties of a procedure */

struct wpt {
  weights wp_weights;
  long  fix_break;
  long  float_break;
};
typedef struct wpt  wp;
 /* used to allocate tags to registers */

struct spacet {
  int  fixed;
  int  flt;
};
typedef struct spacet space;
 /* used to indicate free t-regs in code production */

#endif
