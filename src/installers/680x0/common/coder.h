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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/coder.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: coder.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:48  ma
First version.

Revision 1.2  1997/06/18 10:09:25  ma
Checking in before merging with Input Baseline changes.

Revision 1.1.1.1  1997/03/14 07:50:10  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:56:52  john
 *
 * Revision 1.2  1996/07/05  14:17:52  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:09  john
 *
 * Revision 1.1  93/02/22  17:15:23  17:15:23  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef CODER_INCLUDED
#define CODER_INCLUDED

extern void coder PROTO_S ( ( where, ash, exp ) ) ;


/*
    LOCATION IDENTIFIERS

    These values are used by the register allocation routines to indicate
    where an expression is held.
*/

#define  reg_pl		0	/* In a register */
#define  par_pl		1	/* On the stack (procedure argument) */
#define  var_pl		2	/* On the stack (allocated variable) */
#define  nowhere_pl	3	/* Elsewhere */
#ifndef tdf3
#define  par2_pl        4       /* procedure argument accessed by use of A5 */ 
#define  par3_pl        5       /* procedure argument accessed by use of SP */ 
#endif
/*
    TEST NUMBERS

    These numbers give the tests recognised by branch, cmp etc.
*/

#define  tst_le		L1
#define  tst_ls		L2
#define  tst_ge		L3
#define  tst_gr		L4
#define  tst_neq	L5
#define  tst_eq		L6
#define  tst_ngr	L7
#define  tst_nge	L8
#define  tst_nls	L9
#define  tst_nle	L10

#endif
