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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/tests.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: tests.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:59  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:18  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:46  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:59  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:18  john
 *
 * Revision 1.2  94/02/21  16:04:44  16:04:44  ra (Robert Andrews)
 * A couple of values which were previously bool are now int.
 * 
 * Revision 1.1  93/02/22  17:16:48  17:16:48  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef TESTS_INCLUDED
#define TESTS_INCLUDED

extern int cc_conventions ;
extern int do_sub_params ;

extern bool no_side PROTO_S ( ( exp ) ) ;
extern bool push_arg PROTO_S ( ( exp ) ) ;
extern bool regable PROTO_S ( ( exp ) ) ;

extern bool cpd_param PROTO_S ( ( shape ) ) ;
extern bool is_ptr_void PROTO_S ( ( shape ) ) ;
extern bool issigned PROTO_S ( ( shape ) ) ;
extern int reg_result PROTO_S ( ( shape ) ) ;
extern bool varsize PROTO_S ( ( shape ) ) ;

#define  result_in_reg( X )	reg_result ( X )
#define  setmarked( X )		props ( X ) |= 0x100
#define  ismarked( X )		( props ( X ) & 0x100 )

#endif
