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
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/regmacs.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: regmacs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/12/15  10:27:01  john
 * Minor changes
 *
 * Revision 1.2  1995/05/26  13:01:37  john
 * Change for new spec
 *
 * Revision 1.1.1.1  1995/03/13  10:18:54  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:38  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:59:19  14:59:19  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef REGMACS_INCLUDED
#define REGMACS_INCLUDED


/*
    SPARC FIXED REGISTERS
*/

/* Global registers */
#define R_G0		0	/* always holds 0 */
#define R_G1		1
#define R_G2		2
#define R_G3		3
#define R_G4		4
#define R_G5		5
#define R_G6		6
#define R_G7		7

/* Output registers (input for called procedure) */
#define R_O0		8
#define R_O1		9
#define R_O2		10
#define R_O3		11
#define R_O4		12
#define R_O5		13
#define R_SP		14	/* stack pointer */
#define R_O7		15	/* prospective return address */

/* Local registers */
#define R_L0		16
#define R_L1		17
#define R_L2		18
#define R_L3		19
#define R_L4		20
#define R_L5		21
#define R_L6		22
#define R_L7		23

/* Input (parameter) registers */
#define R_I0		24
#define R_I1		25
#define R_I2		26
#define R_I3		27
#define R_I4		28
#define R_I5		29
#define R_FP		30	/* frame pointer */
#define R_I7		31	/* return address */

/* Temporary scratch register */
#define R_TMP		R_G1

/* Range of all fixed registers */
#define R_FIRST		R_G0
#define R_LAST		R_I7


/*
    SPARC FLOATING POINT REGISTERS

    Two representations are used in sparctrans, 0...15 to represent 16
    register-pairs for doubles at the higher (e.g. fregalloc) levels, and
    0...31 at the lower (assembler) levels.  This is somewhat confusing,
    conversion is one way using a 'frg << 1'-like expression, often in
    the parameter position of a ???_ins () function call.
*/

/* Floating point registers */
#define R_F0		0	/* procedure result register */

/* Range of all floating point registers */
#define R_FLT_FIRST	0
#define R_FLT_LAST	15


/*
    PSEUDO-REGISTER CODES
*/

#define R_NO_REG	100	/* code for no register allocated */
#define R_USE_RES_REG	101	/* code to indicate result register */
#define R_DEFER_F0	16	/* code to indicate %f0 to be used */


/*
  REGISTER MASKS
  A register mask, with one bit per register, is used in 'space' etc.
  A set bit indicates that the register is not available for 
  allocation.
*/

#define	RMASK( r )	( ( ( long ) 1 ) << ( r ) )


/*
  REGISTER SETS
  IS_FIXREG tests for fixed registers, IS_SREG for s-registers (those
  preserved over procedure calls), and IS_TREG for t-registers (those
  not so preserved).  PARAM_TREGS gives all the procedure parameter
  registers (O0-O7)
*/

#define IS_FIXREG( r )		( ( r ) >= R_FIRST && ( r ) <= R_LAST )
#define IS_SREG( r )		( ( r ) >= R_L0 && ( r ) <= R_I5 )
#define IS_TREG( r )		( ( ( r ) >= R_G2 && ( r ) <= R_G7 ) ||\
				  ( ( r ) >= R_O0 && ( r ) <= R_O5 ) ||\
				  ( ( r ) == R_O7 ) )
#define IS_IN_REG(r)	((r)>=R_I0 && (r)<= R_I5)
#define PARAM_TREGS		0x0000ff00L
#define PROC_TREGS		0xffff40ffL
#define IS_FLT_SREG( r )	0
#define IS_FLT_TREG( r )	( ( r ) >= 0 && ( r ) <= 15 )
#define PARAM_FLT_TREGS		0x0000
#define PROC_FLT_TREGS		0x0000
#define MAXFLOAT_TREGS		16


#endif /* REGMACS_INCLUDED */
