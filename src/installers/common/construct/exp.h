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
$Date: 1998/01/17 15:55:46 $
$Revision: 1.1.1.1 $
$Log: exp.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/
#ifndef expdecs_key
#define expdecs_key 1



extern exp getexp PROTO_S((shape s, exp b, int l, exp sn, exp p,
                          prop pr, int n, unsigned char tg));
extern exp getshape PROTO_S((int l, alignment sn, alignment p,
                          alignment pr, int n, unsigned char tg));

extern shape lub_shape PROTO_S ((shape a, shape b));
extern int next_lab PROTO_S ((void));
extern int eq_shape PROTO_S ((shape a, shape b));
extern char * intchars PROTO_S ((int i));
extern void case_item PROTO_S ((exp e));
extern void kill_exp PROTO_S ((exp e, exp scope));
extern void altered PROTO_S ((exp e, exp scope));
extern void replace PROTO_S ((exp old, exp e, exp scope));
extern int internal_to PROTO_S ((exp whole, exp part));
extern exp next_exp PROTO_S ((void));
extern exp copy PROTO_S ((exp e));
extern exp copy_res PROTO_S ((exp e, exp var, exp lab));
extern exp copyexp PROTO_S ((exp e));
extern exp father PROTO_S ((exp e));
extern exp * refto PROTO_S ((exp f, exp e));
extern void retcell PROTO_S ((exp e));
extern int is_comm PROTO_S ((exp e));
extern void set_large_alloc PROTO_S ((void));
extern int first_alloc_size;
extern exp freelist;
extern int exps_left;
extern int crt_labno;

extern exp clean_labelled PROTO_S ((exp starter, label_list placelabs_intro));

#endif
