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


/* 	$Id: palcode.h,v 1.1.1.1 1998/01/17 15:56:01 release Exp $	 */

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










