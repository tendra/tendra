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
$Log: flpt.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/
#ifndef flpt_key
#define flpt_key 1



#include "flpttypes.h"

extern  void init_flpt PROTO_S ((void));
extern  void more_flpts PROTO_S ((void));
extern  flpt new_flpt PROTO_S ((void));
extern  void flpt_ret PROTO_S ((flpt f));
extern  int cmpflpt PROTO_S ((flpt a, flpt b, int testno));
extern  flpt floatrep PROTO_S ((int n));
extern  flpt floatrep_unsigned PROTO_S ((unsigned int n));
extern  flt * flptnos;

/* floatingpoint functions - are these needed externally??? */
extern  void flt_zero PROTO_S ((flt * f));
extern  void flt_copy PROTO_S ((flt f, flt * res));
extern int  flt_add PROTO_S ((flt f1, flt f2, flt * res));
extern int  flt_sub PROTO_S ((flt f1, flt f2, flt * res));
extern int  flt_mul PROTO_S ((flt f1, flt f2, flt * res));
extern int  flt_div PROTO_S ((flt f1, flt f2, flt * res));
extern int  flt_cmp PROTO_S ((flt f1, flt f2));
extern  void flt_round PROTO_S ((flt f, flt * res));
extern  void flt_trunc PROTO_S ((flt f, flt * res));
extern void flpt_newdig PROTO_S ((unsigned int dig, flt * res, int base));
extern void flpt_scale PROTO_S ((int decexp, flt * res, int base));
extern void flpt_round PROTO_S ((int rdnmd, int pos, flt * res));
extern int flpt_bits PROTO_S ((floating_variety fv));
extern int flpt_round_to_integer PROTO_S ((int rndmd, flt * f));

#if FBASE != 10
extern r2l real2longs_IEEE PROTO_S ((flt * f, int sw));
#endif

extern int fzero_no;
extern int fone_no;

#endif

