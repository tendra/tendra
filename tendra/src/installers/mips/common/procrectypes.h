/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/
/* procrectypes.h
 *     types for properties of procs
 *      needs, weights,parpair,procrec,spacereq
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
						 *				   exp */
};
typedef struct needst needs;

struct weightst {
	float fix[wfixno];
	float  floating[wfloatno];
};
typedef struct weightst weights;
/* used to allocate tags to registers */


struct spacereqt {
	long  fixdump;
	long 	fltdump;
	long  stack;
};
typedef struct spacereqt  spacereq;
/* used characterise s-reg and stack requirements of proc */

struct procrect {
	needs needsproc;
	spacereq spacereqproc;
  	long frame_size;
  	long locals_offset;
  	long max_args;
  	long fixdump;
  	long floatdump;
  	long dumpstart;
  	long fldumpstart;
  	long callee_size;	
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
