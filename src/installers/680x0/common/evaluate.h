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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/evaluate.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: evaluate.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:50  ma
First version.

Revision 1.2  1997/09/25 06:44:59  ma
All general_proc tests passed

Revision 1.1.1.1  1997/03/14 07:50:11  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:29  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:53  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:11  john
 *
 * Revision 1.1  93/02/22  17:15:34  17:15:34  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef EVALUATE_INCLUDED
#define EVALUATE_INCLUDED
#include "mach.h"
extern exp const_list ;
extern long * realrep PROTO_S ( ( exp ) ) ;
extern void evaluate PROTO_S ( ( exp, long, char *, int, int, diag_global * ) ) ;
extern void eval_op PROTO_S ( ( long sz, mach_op* op ) ) ;

#define  make_constant( X, Y )\
    const_list = getexp ( botsh, const_list, 0, (Y), nilexp, 0, (X), 0 )

#endif
