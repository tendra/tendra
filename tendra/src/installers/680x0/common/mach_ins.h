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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/mach_ins.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: mach_ins.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:55  ma
First version.

Revision 1.3  1997/10/13 08:49:37  ma
Made all pl_tests for general proc & exception handling pass.

Revision 1.2  1997/05/13 11:30:35  ma
Introduced make_comment for debug.

Revision 1.1.1.1  1997/03/14 07:50:14  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:56:55  john
 *
 * Revision 1.2  1996/07/05  14:22:32  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:14  john
 *
 * Revision 1.2  94/02/21  16:00:14  16:00:14  ra (Robert Andrews)
 * A couple of flags which used to be bool are now int.
 * 
 * Revision 1.1  93/02/22  17:16:05  17:16:05  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef MACH_INS_INCLUDED
#define MACH_INS_INCLUDED

extern void make_instr_aux PROTO_S ( ( int, mach_op *, mach_op *, bitpattern, int ) ) ;

#define  make_instr( A, B, C, D )\
    make_instr_aux ( ( A ), ( B ), ( C ), ( D ), 0 )

extern int output_immediately ;
extern mach_ins *all_mach_ins ;
extern mach_ins *current_ins ;
extern void free_all_ins PROTO_S ( ( void ) ) ;
extern void reclaim_ins PROTO_S ( ( mach_ins * ) ) ;

extern long last_jump ;
extern bitpattern last_jump_regs ;

extern void make_external_label PROTO_S ( ( char * ) ) ;
extern void make_jump PROTO_S ( ( int, long ) ) ;
extern void make_label PROTO_S ( ( long ) ) ;
extern void set_special PROTO_S ( ( char *, mach_op * ) ) ;
#ifdef EBUG
extern void make_comment PROTO_S ( ( char *) ) ;
#else
#define make_comment( X )
#endif

#endif













