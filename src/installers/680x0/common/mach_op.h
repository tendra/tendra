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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/mach_op.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: mach_op.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.2  1997/10/29 10:22:23  ma
Replaced use_alloca with has_alloca.

Revision 1.1.1.1  1997/10/13 12:42:55  ma
First version.

Revision 1.3  1997/09/25 06:45:17  ma
All general_proc tests passed

Revision 1.2  1997/06/18 10:09:39  ma
Checking in before merging with Input Baseline changes.

Revision 1.1.1.1  1997/03/14 07:50:15  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:40  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:55  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:15  john
 *
 * Revision 1.2  94/02/21  16:00:39  16:00:39  ra (Robert Andrews)
 * Declare functions with no arguments using ( void ).
 * 
 * Revision 1.1  93/02/22  17:16:09  17:16:09  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef MACH_OP_INCLUDED
#define MACH_OP_INCLUDED

extern bool check_op PROTO_S ( ( mach_op *, int ) ) ;
extern bool equal_op PROTO_S ( ( mach_op *, mach_op * ) ) ;
extern void free_mach_op PROTO_S ( ( mach_op * ) ) ;
extern mach_op * new_mach_op PROTO_S ( ( void ) ) ;

extern mach_op * make_bitfield_op PROTO_S ( ( mach_op *, int, int ) ) ;
extern mach_op * make_dec_sp PROTO_S ( ( void ) ) ;
extern mach_op * make_extern PROTO_S ( ( char *, long ) ) ;
extern mach_op * make_extern_data PROTO_S ( ( char *, long ) ) ;
extern mach_op * make_extern_ind PROTO_S ( ( char *, long ) ) ;
extern mach_op * make_float_data PROTO_S ( ( flt * ) ) ;
extern mach_op * make_hex_data PROTO_S ( ( long ) ) ;
extern mach_op * make_hex_value PROTO_S ( ( long ) ) ;
extern mach_op * make_inc_sp PROTO_S ( ( void ) ) ;
extern mach_op * make_ind_rel_ap PROTO_S ( ( long, long ) ) ;
extern mach_op * make_index_op PROTO_S ( ( mach_op *, mach_op *, int ) ) ;
extern mach_op * make_indirect PROTO_S ( ( int, long ) ) ;
extern mach_op * make_int_data PROTO_S ( ( long ) ) ;
extern mach_op * make_lab PROTO_S ( ( long, long ) ) ;
extern mach_op * make_lab_data PROTO_S ( ( long, long ) ) ;
extern mach_op * make_lab_diff PROTO_S ( ( long, long ) ) ;
extern mach_op * make_lab_ind PROTO_S ( ( long, long ) ) ;
extern mach_op * make_postinc PROTO_S ( ( int ) ) ;
extern mach_op * make_reg_index PROTO_S ( ( int, int, long, int ) ) ;
extern mach_op * make_reg_pair PROTO_S ( ( int, int ) ) ;
extern mach_op * make_register PROTO_S ( ( int ) ) ;
extern mach_op * make_rel_ap PROTO_S ( ( long ) ) ;

#ifndef tdf3
extern mach_op * make_rel_ap2 PROTO_S ( ( long ) ) ;
extern mach_op * make_rel_sp PROTO_S ( ( long ) ) ;
extern mach_op * make_ind_rel_ap2 PROTO_S ( ( long, long ) ) ;
extern mach_op * make_ind_rel_ap3 PROTO_S ( ( long, long ) ) ;
extern mach_op * make_predec PROTO_S ( ( int ) ) ;
extern mach_op * make_ldisp PROTO_S ( ( long ) ) ;
#endif

extern mach_op * make_special PROTO_S ( ( char * ) ) ;
extern mach_op * make_special_data PROTO_S ( ( char * ) ) ;
extern mach_op * make_value PROTO_S ( ( long ) ) ;

extern long special_no ;
extern char *special_str ;

extern int tmp_reg_prefer ;
extern int tmp_reg_status ;
extern void avoid_tmp_reg PROTO_S ( ( int ) ) ;
extern int next_tmp_reg PROTO_S ( ( void ) ) ;
extern int tmp_reg PROTO_S ( ( int, mach_op * ) ) ;

#endif
