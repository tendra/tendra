/*
    		 Crown Copyright (c) 1996
    
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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/where.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: where.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.2  1997/10/29 10:22:33  ma
Replaced use_alloca with has_alloca.

Revision 1.1.1.1  1997/10/13 12:43:01  ma
First version.

Revision 1.3  1997/10/13 08:50:22  ma
Made all pl_tests for general proc & exception handling pass.

Revision 1.2  1997/09/25 06:45:43  ma
All general_proc tests passed

Revision 1.1.1.1  1997/03/14 07:50:21  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:57:00  john
 *
 * Revision 1.2  1996/07/05  14:30:26  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:19  john
 *
 * Revision 1.2  94/02/21  16:07:24  16:07:24  ra (Robert Andrews)
 * Declare functions with no arguments with ( void ).  Make 0 into a long
 * in the definition of zw.
 * 
 * Revision 1.1  93/02/22  17:17:07  17:17:07  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef WHERE_INCLUDED
#define WHERE_INCLUDED

/*
    STRUCTURE REPRESENTING ALLOCATED EXPRESSIONS

    A where consists of an expression, wh_exp, and an offset wh_off.
    The wh_is field gives information on where the expression is
    stored (see below).  The wh_regs field gives the register mask
    of all the registers involved in storing the expression.
*/

typedef struct {
    exp wh_exp ;
    long wh_off ;
    int wh_is ;
    bitpattern wh_regs ;
} where ;


/*
    POSSIBLE VALUES FOR THE wh_is FIELD OF A WHERE
*/


#define  Dreg		0	/* In a D-register */
#define  Areg		1	/* In an A-register */
#define  Freg		2	/* In an F-register */
#define  Value		3	/* Constant value */
#define  Parameter	4	/* On the stack (procedure argument) */
#define  Variable	5	/* On the stack (allocated variable) */
#define  RegInd		6	/* Indirect relative to a register */
#define  EffAddr	7	/* In a valid 68020 effective address */
#define  External	8	/* External data */
#define  RegPair	9	/* In a register pair */
#define  Other		10	/* All other cases */

/*
    PROCEDURES INVOLVING WHERE'S
*/

extern void init_wheres PROTO_S ( ( void ) ) ;
extern int shtype PROTO_S ( ( shape ) ) ;
extern where mw PROTO_S ( ( exp, long ) ) ;
extern where mnw PROTO_S ( ( long ) ) ;
extern bool eq_where_a PROTO_S ( ( where, where, int ) ) ;
extern where where_operand PROTO_S ( (mach_op*) ) ;


/*
    MACROS INVOLVING WHERE'S
*/

#define  whereis( X )		( ( X ).wh_is )
#define  interfere( X, Y )	( ( X ).wh_regs & ( Y ).wh_regs )
#define  last_use( X )		( ( X ).wh_regs & reuseables )
#define  nw( X )		( no ( ( X ).wh_exp ) + ( X ).wh_off )
#define  zw( X )		mw ( X, L0 )
#define  eq_where( X, Y )	eq_where_a ( X, Y, 1 )


/*
    CONSTANT EXP'S AND WHERE'S
*/

extern exp zeroe ;
extern where zero, fzero ;
extern where A6_4, A0_p, A1_p, SP_p, A6_4_p, D0_D1 ;
extern where RW [] ;

extern where dummy_double_dest ; /* used to force floating-point overflow */
extern where firstlocal ; /* represents first local on the stack */

/*
    DEFINITION OF REGISTER WHERE'S
*/

#define  D0		( RW [ REG_D0 ] )
#define  D1		( RW [ REG_D1 ] )
#define  D2		( RW [ REG_D2 ] )
#define  D3		( RW [ REG_D3 ] )
#define  D4		( RW [ REG_D4 ] )
#define  D5		( RW [ REG_D5 ] )
#define  D6		( RW [ REG_D6 ] )
#define  D7		( RW [ REG_D7 ] )
#define  A0		( RW [ REG_A0 ] )
#define  A1		( RW [ REG_A1 ] )
#define  A2		( RW [ REG_A2 ] )
#define  A3		( RW [ REG_A3 ] )
#define  A4		( RW [ REG_A4 ] )
#define  A5		( RW [ REG_A5 ] )
#define  AP		( RW [ REG_AP ] )
#define  SP		( RW [ REG_SP ] )
#define  FP0		( RW [ REG_FP0 ] )
#define  FP1		( RW [ REG_FP1 ] )
#define  FP2		( RW [ REG_FP2 ] )
#define  FP3		( RW [ REG_FP3 ] )
#define  FP4		( RW [ REG_FP4 ] )
#define  FP5		( RW [ REG_FP5 ] )
#define  FP6		( RW [ REG_FP6 ] )
#define  FP7		( RW [ REG_FP7 ] )
#define  register( X )	( RW [ ( X ) ] )

#endif
