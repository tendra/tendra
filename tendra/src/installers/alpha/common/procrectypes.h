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


/* procrectypes.h
     types for properties of procs
      needs, weights,parpair,procrec,spacereq
*/

#include "exptypes.h"

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
