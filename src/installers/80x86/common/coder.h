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


/* 80x86/coderdecs.h */

/**********************************************************************
$Author: pwe $
$Date: 1998/03/11 11:03:02 $
$Revision: 1.2 $
$Log: coder.h,v $
 * Revision 1.2  1998/03/11  11:03:02  pwe
 * DWARF optimisation info
 *
 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
 * Revision 1.7  1997/10/10  18:24:59  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.6  1996/07/31  12:56:48  pwe
 * restore alloca stack after longjump
 *
 * Revision 1.5  1995/08/23  09:42:31  pwe
 * track fpu control word for trap etc
 *
 * Revision 1.4  1995/08/14  13:53:24  pwe
 * several corrections, tail calls and error jumps
 *
 * Revision 1.3  1995/08/04  08:29:04  pwe
 * 4.0 general procs implemented
 *
 * Revision 1.2  1995/01/30  12:56:02  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:28:42  jmf
 * Initial revision
 *
**********************************************************************/

#ifndef coder_key
#define coder_key 1


extern void coder PROTO_S ((where dest, ash stack, exp e));
extern int regsinuse;
extern int min_rfree;
extern int bits_in[16];
extern int max_stack;
extern int crt_ret_lab;
extern int crt_ret_lab_used;
extern outofline * odd_bits;
extern int last_odd_bit;
extern int doing_odd_bits;
extern outofline * current_odd_bit;
extern int repeat_level;
extern int not_in_params;
extern int not_in_postlude;
extern void clean_stack PROTO_S ((void));
extern int retjmp_count;
extern float scale;
extern exp crt_proc_exp;
extern exp vc_pointer;
extern int callee_size;
extern int has_dy_callees;
extern int has_tail_call;
extern int has_same_callees;
extern int need_preserve_stack;
extern int proc_has_asm;

#ifdef NEWDIAGS
extern void diag_arg PROTO_S ((where dest, ash stack, exp e));
#endif

#endif
