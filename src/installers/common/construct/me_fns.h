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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:47 $
$Revision: 1.1.1.1 $
$Log: me_fns.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/



extern exp me_u1 PROTO_S ((error_treatment ov_err, exp arg1, unsigned char nm));
extern exp me_u2 PROTO_S ((exp arg1, unsigned char nm));
extern exp me_u3 PROTO_S ((shape sha, exp arg1, unsigned char nm));
extern exp me_b1 PROTO_S ((error_treatment ov_err, exp arg1, exp arg2, unsigned char nm));
extern exp me_b2 PROTO_S ((exp arg1, exp arg2, unsigned char nm));
extern exp me_b3 PROTO_S ((shape sha, exp arg1, exp arg2, unsigned char nm));
extern exp me_b4 PROTO_S ((error_treatment div0_err, error_treatment ov_err, exp arg1, exp arg2, unsigned char nm));
extern exp me_c1 PROTO_S ((shape sha, error_treatment ov_err, exp arg1, unsigned char nm));
extern exp me_c2 PROTO_S ((shape sha, exp arg1, unsigned char nm));
extern exp me_l1 PROTO_S ((shape sha, unsigned char nm));
extern exp me_q1 PROTO_S ((nat_option prob, ntest nt, label dest, exp arg1,
    exp arg2, unsigned char nm));
extern exp me_q2 PROTO_S ((nat_option prob, error_treatment err, ntest nt,
    label dest, exp arg1, exp arg2, unsigned char nm));
extern exp me_q1_aux PROTO_S ((nat_option prob, ntest nt, exp lab,
    exp arg1, exp arg2, unsigned char nm));
extern exp me_q2_aux PROTO_S ((nat_option prob, error_treatment err,
    ntest nt, exp lab, exp arg1, exp arg2, unsigned char nm));
extern exp me_shint PROTO_S ((shape sha, int i));
extern exp me_obtain PROTO_S ((exp id));
extern exp me_startid PROTO_S ((shape sha, exp def, int isv));
extern exp me_start_clearvar PROTO_S ((shape idsh, shape initsh));
extern exp me_complete_id PROTO_S ((exp id, exp body));
extern void note_repeat PROTO_S ((exp r));
extern alignment long_to_al PROTO_S ((int n));
extern int is_integer PROTO_S ((shape s));
extern int is_float PROTO_S ((shape s));
extern int is_complex PROTO_S ((shape s));
extern exp me_null PROTO_S ((shape sha, int i, unsigned char nm));
extern floating_variety float_to_complex_var PROTO_S ((floating_variety f));
extern floating_variety complex_to_float_var PROTO_S ((floating_variety s));

extern void clear_exp_list PROTO_S ((exp_list el));
	/* defined in install_fns.c */
