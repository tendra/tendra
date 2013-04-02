/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  palcode.h

  This file defines the palcode instructions supported by the 
  implementation.
*/

#ifdef INS_DEFINE
#define pal_instr(inst)	char * PASTE(p_,inst) = #inst
#else
#define pal_instr(inst) extern char * PASTE(p_,inst)
#endif

/* common instructions */
pal_instr(HALT);	/* HALT processor */
pal_instr(IMB);		/* I-stream memory barrier.  Makes 
			 instructions stream coherent with Data 
			 Stream. */


#ifdef OSF1
pal_instr(bpt)		/* break point trap */
pal_instr(bugchk)	/* bug check */
pal_instr(callsys)	/* system call */
pal_instr(gentrap)	/* generate trap */
pal_instr(rdunique)	/* read unique - return process unique value */
pal_instr(wrunique)	/* write unique */
#else 
#ifdef OPEN_VMS
#else 
#ifdef WIN_NT
#endif
#endif
#endif










