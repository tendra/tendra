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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/inst_fmt.h,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: inst_fmt.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.6  1997/10/10  18:32:29  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.5  1995/09/13  11:00:55  john
 * New prototype
 *
 * Revision 1.4  1995/07/18  09:38:50  john
 * New functions for return_to_label
 *
 * Revision 1.3  1995/07/14  16:31:16  john
 * Changed prototype name
 *
 * Revision 1.2  1995/05/26  12:58:48  john
 * New prototype
 *
 * Revision 1.1.1.1  1995/03/13  10:18:39  john
 * Entered into CVS
 *
 * Revision 1.5  1994/12/21  12:10:54  djch
 * added maxmin functions
 *
 * Revision 1.4  1994/12/01  13:17:17  djch
 * Added 3 new fns
 *
 * Revision 1.3  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.2  1994/05/13  12:32:10  djch
 * Incorporates improvements from expt version
 * changed extj_special_ins to match
 *
 * Revision 1.1  1994/05/03  14:50:19  djch
 * Initial revision
 *
 * Revision 1.2  93/08/27  11:28:10  11:28:10  ra (Robert Andrews)
 *  ext_name now takes an int not a long (I got the comment in inst_fmt.c
 * wrong).
 * 
 * Revision 1.1  93/06/24  14:58:30  14:58:30  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef INST_FMT_INCLUDED
#define INST_FMT_INCLUDED

#include "addrtypes.h"
#include "sparcins.h"

/* special registers */
#define YREG	65
#define FSR	33

extern char *ext_name PROTO_S ( ( int ) ) ;

extern void ld_ro_ins PROTO_S ( ( ins_p, baseoff, int ) ) ;
extern void ld_rr_ins PROTO_S ( ( ins_p, int, int, int ) ) ;
extern void ld_ins PROTO_S ( ( ins_p, baseoff, int ) ) ;

extern void st_ro_ins PROTO_S ( ( ins_p, int, baseoff ) ) ;
extern void st_rr_ins PROTO_S ( ( ins_p, int, int, int ) ) ;
extern void st_ins PROTO_S ( ( ins_p, int, baseoff ) ) ;

extern void rrr_ins PROTO_S ( ( ins_p, int, int, int ) ) ;
extern void rir_ins PROTO_S ( ( ins_p, int, long, int ) ) ;
extern void rr_ins PROTO_S ( ( ins_p, int, int ) ) ;
extern void ir_ins PROTO_S ( ( ins_p, long, int ) ) ;
extern void lr_ins PROTO_S ( ( int, int ) ) ;

extern void set_ins PROTO_S ( ( baseoff, int ) ) ;
extern void z_ins PROTO_S ( ( ins_p ) ) ;
extern void unimp_ins PROTO_S ( ( long ) ) ;

extern void condrr_ins PROTO_S ( ( ins_p, int, int, int ) ) ;
extern void condri_ins PROTO_S ( ( ins_p, int, long, int ) ) ;
extern void fmaxminrr_ins PROTO_S ((ins_p,int,int,int,int));
extern void maxminrr_ins PROTO_S ( ( ins_p, int, int, int ) ) ;
extern void maxminri_ins PROTO_S ( ( ins_p, int, long, int ) ) ;
extern void uncond_ins PROTO_S ( ( ins_p, int ) ) ;
extern void br_ins PROTO_S ( ( ins_p, int ) ) ;
extern void br_abs PROTO_S ((int));
extern void lngjmp PROTO_S ((int,int,int));

extern void extj_ins PROTO_S ( ( ins_p, baseoff, int ) ) ;
extern void extj_ins_without_delay PROTO_S ( ( ins_p, baseoff, int ) ) ;

extern void extj_special_ins PROTO_S ( ( ins_p, CONST char * CONST, int ) ) ;
extern void extj_special_ins_no_delay PROTO_S ( ( ins_p, CONST char * CONST, int ) ) ;
extern void extj_reg_ins PROTO_S ( ( ins_p, int, int ) ) ;
extern void extj_reg_ins_no_delay PROTO_S ( ( ins_p, int, int ) ) ;

extern void ret_ins PROTO_S ( ( ins_p ) ) ;
extern void ret_restore_ins PROTO_S ( ( void ) ) ;
extern void stret_restore_ins PROTO_S ( ( void ) ) ;

extern void ldf_ro_ins PROTO_S ( ( ins_p, baseoff, int ) ) ;
extern void ldf_rr_ins PROTO_S ( ( ins_p, int, int, int ) ) ;
extern void ldf_ins PROTO_S ( ( ins_p, baseoff, int ) ) ;
extern void stf_ro_ins PROTO_S ( ( ins_p, int, baseoff ) ) ;
extern void stf_rr_ins PROTO_S ( ( ins_p, int, int, int ) ) ;
extern void stf_ins PROTO_S ( ( ins_p, int, baseoff ) ) ;

extern void rrf_ins PROTO_S ( ( ins_p, int, int ) ) ;
extern void rrrf_ins PROTO_S ( ( ins_p, int, int, int ) ) ;

extern void rrf_cmp_ins PROTO_S ( ( ins_p, int, int ) ) ;
extern void fbr_ins PROTO_S ( ( ins_p, int ) ) ;

extern void out_asm_reg PROTO_S ( ( int, int ) ) ;
extern void out_asm_boff PROTO_S ( ( baseoff, long ) ) ;

#endif /* INST_FMT_INCLUDED */
