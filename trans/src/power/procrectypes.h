/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef procreckey
#define procreckey 1

#include <reader/exp.h>

#include <construct/installtypes.h>

#define wfixno		32
#define wfloatno	32

struct needst {
  int   fixneeds;		/* no of fixed t-regs required */
  int   floatneeds;		/* no of float t-regs required */
  prop propsneeds;		/* various binary properties of exp */
  int   maxargs;		/* size in bits for actual parameters in
				   exp */
};
typedef struct needst needs;

struct weightst {
  float  fix[wfixno];
  float  floating[wfloatno];
};
typedef struct weightst weights;
 /* used to allocate tags to registers */


struct spacereqt {
  long  fixdump;
  long	fltdump;
  long  stack;
  exp obtain;
};
typedef struct spacereqt  spacereq;
 /* used characterise s-reg and stack requirements of proc */

struct procrect {
  needs      needsproc;
  spacereq   spacereqproc;
  bool leaf_proc;
  bool alloca_proc;
  bool has_fp;
  bool has_tp;
  bool has_saved_sp;
  bool save_all_sregs;
  bool has_vcallees;
  bool has_no_vcallers;
  long callee_size;
  long locals_space;
  long locals_offset;
  long frame_size;
  long params_offset;
  long maxargs;
  long max_callee_bytes;
  int sreg_first_save;
  int sfreg_first_save;
  long no_of_returns;
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
  long  fixed;
  long  flt;
};
typedef struct spacet space;
 /* used to indicate free t-regs in code production */

#endif
