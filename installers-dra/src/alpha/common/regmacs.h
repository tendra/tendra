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


/* 	$Id: regmacs.h,v 1.1.1.1 1998/01/17 15:56:01 release Exp $	 */


/* regmacs.h
    defines good numbers for registers
*/

#define maxfix 18
#define maxfloat 15
/*
#define tempfix 0x300ff00
*/
/* corresponds to t0-t9 regs ,  maxfix regs */
#define tempfix 0x3ffff00

#define tempfloat 0x33c		/* corresponds to temp float regs,
				   maxfloat regs */
