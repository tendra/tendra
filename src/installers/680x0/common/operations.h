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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/operations.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: operations.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:56  ma
First version.

Revision 1.3  1997/10/13 08:49:41  ma
Made all pl_tests for general proc & exception handling pass.

Revision 1.2  1997/09/25 06:45:21  ma
All general_proc tests passed

Revision 1.1.1.1  1997/03/14 07:50:15  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:56:57  john
 *
 * Revision 1.2  1996/07/05  14:23:29  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:15  john
 *
 * Revision 1.4  94/11/16  10:37:07  10:37:07  ra (Robert Andrews)
 * Added support for integer absolute.
 * 
 * Revision 1.3  94/06/29  14:23:06  14:23:06  ra (Robert Andrews)
 * Declare maximum and minimum operations.
 * 
 * Revision 1.2  93/03/03  14:47:52  14:47:52  ra (Robert Andrews)
 * Added error handling routines.
 * 
 * Revision 1.1  93/02/22  17:16:15  17:16:15  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef OPERATIONS_INCLUDED
#define OPERATIONS_INCLUDED
#include "ecodes.h"
extern bool have_cond ;
extern bool D1_is_special ;
extern int crt_rmode ;

extern void absop PROTO_S ( ( shape, where, where ) ) ;
extern void add PROTO_S ( ( shape, where, where, where ) ) ;
extern void and PROTO_S ( ( shape, where, where, where ) ) ;
extern void bitf_to_int PROTO_S ( ( exp, shape, where, ash ) ) ;
extern void bit_test PROTO_S ( ( shape, where, where ) ) ;
extern void callins PROTO_S ( ( long, exp ) ) ;
extern void jmpins PROTO_S ( ( exp ) ) ;
extern void trap_ins PROTO_S ( ( int ) ) ;
extern void change_var_sh PROTO_S ( ( shape, shape, where, where ) ) ;
extern void change_var PROTO_S ( ( shape, where, where ) ) ;
extern bool cmp PROTO_S ( ( shape, where, where, long ) ) ;
extern void div1 PROTO_S ( ( shape, where, where, where ) ) ;
extern void div2 PROTO_S ( ( shape, where, where, where ) ) ;
extern void exactdiv PROTO_S ( ( shape, where, where, where ) ) ;
extern void int_to_bitf PROTO_S ( ( exp, exp, ash ) ) ;
extern void maxop PROTO_S ( ( shape, where, where, where ) ) ;
extern void minop PROTO_S ( ( shape, where, where, where ) ) ;
extern void mova PROTO_S ( ( where, where ) ) ;
extern void move PROTO_S ( ( shape, where, where ) ) ;
extern void move_const PROTO_S ( ( shape, long, long, where ) ) ;
extern void move_bytes PROTO_S ( ( long, where, where, int ) ) ;
extern void mult PROTO_S ( ( shape, where, where, where ) ) ;
extern void negate PROTO_S ( ( shape, where, where ) ) ;
extern void not PROTO_S ( ( shape, where, where ) ) ;
extern void or PROTO_S ( ( shape, where, where, where ) ) ;
extern void rem1 PROTO_S ( ( shape, where, where, where ) ) ;
extern void rem2 PROTO_S ( ( shape, where, where, where ) ) ;
extern void rshift PROTO_S ( ( shape, where, where, where ) ) ;
extern void shift PROTO_S ( ( shape, where, where, where ) ) ;
extern void sub PROTO_S ( ( shape, where, where, where ) ) ;
extern void xor PROTO_S ( ( shape, where, where, where ) ) ;

extern void abs_float PROTO_S ( ( shape, where, where ) ) ;
extern void change_flvar PROTO_S ( ( shape, where, where ) ) ;
extern void fl_binop PROTO_S ( ( int, shape, where, where, where ) ) ;
extern void int_to_float PROTO_S ( ( shape, where, where ) ) ;
extern void negate_float PROTO_S ( ( shape, where, where ) ) ;
extern void round_float PROTO_S ( ( shape, where, where ) ) ;

extern long range_max PROTO_S ( (shape) );
extern long range_min PROTO_S ( (shape) );

extern int overflow_jump ;
extern int err_continue;

#define CONTINUE_ERR 2

#define set_continue(e) if(errhandle(e)==CONTINUE_ERR) err_continue = 1
#define clear_continue(e) (err_continue = 0)
#define have_continue() (err_continue != 0)
#endif
