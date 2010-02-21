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


/*
$Log: bitsmacs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:10:56  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 4.0  1995/08/25  13:34:00  wfs
 * *** empty log message ***
 *
 * Revision 4.0  1995/08/25  13:34:00  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  10:45:48  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  10:45:48  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:25:43  16:25:43  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:14:17  11:14:17  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:25:03  15:25:03  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:35:49  13:35:49  wfs (William Simmonds)
 * Initial revision
 * 
*/


#ifndef BITSMACS_INCLUDED
#define BITSMACS_INCLUDED


/*
    PROPERTIES FOR NEEDS
*/

#define morefix			0x0100
#define morefloat		0x0200
#define hasproccall		0x0400
#define usesproccall		0x0800	/* hasproccall << 1 */
#define anyproccall		0x0c00
#define long_result_bit 	0x1000
#define has_result_bit		0x2000
#define regsused		0x0d00	/* composite */
#define fregsused		0x0e00	/* composite */
#define realresult_bit		0x4000
#define longrealresult_bit  	0x8000
#define uses_res_reg_bit 	0x0002
#define dont_optimise 		0x0004
#define uses2_bit 2

/*
    HPPA-SPECIFIC IDENT PROPERTIES
*/

#define inreg_bits 		0x0800
#define infreg_bits 		0x1000
#define inanyreg 		0x1800
#define defer_bit 		0x2000
#define notparreg 		0x4000
#define notresreg 		0x8000
#define sreguse 		0x0200
#define inlined			0x0200
/* #define subvar 			0x0100 */

/*
    PROPERTIES OF REAL OPERATIONS
*/

#define SetRev( e )		props ( e ) |= 0x1000
#define IsRev( e )		( props (e) & 0x1000 )
#define ClearRev( e )		props ( e ) &= ~0x1000


/*
    MISCELLANEOUS MACROS
*/

#define inlineassign		9
#define UNITWEIGHT		16.0


#endif /* BITSMACS_INCLUDED */

















