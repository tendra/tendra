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


/* 80x86/operanddecs.h */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:51 $
$Revision: 1.1.1.1 $
$Log: operand.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/04/03  08:30:26  pwe
 * invalidate regs if overlap, eg if bitfield on byte boundaries
 *
 * Revision 1.2  1995/01/30  12:56:37  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:38:32  jmf
 * Initial revision
 *
**********************************************************************/

#ifndef opdecs_key
#define opdecs_key 1


extern  void operand PROTO_S ((int sz, where wh, int b, int addr));
extern int  stack_dec;
extern  int eq_where PROTO_S ((where a, where b));
extern  int eq_where_exp PROTO_S ((exp a, exp b, int first, int overlap));
extern  where mw PROTO_S ((exp e, int off));
extern int  crt_proc_id;
extern  exp const_list;
extern  frr first_reg PROTO_S ((int r));


#endif
