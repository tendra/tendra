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
$Author: pwe $
$Date: 1998/02/11 16:56:37 $
$Revision: 1.2 $
$Log: check.h,v $
 * Revision 1.2  1998/02/11  16:56:37  pwe
 * corrections
 *
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/



/*******************************************************************

                              checkdecs.h

  The routine check performs the bottom-up TDF-to-TDF optimising
  transformations. When a new exp is created check is applied to
  see if a recognised situation has arisen. check assumes that
  all components of this new exp have already had check applied to them.
  It returns 1 if it has made a change, 0 if not.


  hold_check holds an exp as the son of a dummy exp and then 
  applies check. the need for this operation is explained in
  the overall documentation.

  eq_exp compares two exp for equality of effect. 

  dochvar takes the int, i, and delivers the number which results from
  changing its variety to that specified by the shape, t.

 *******************************************************************/



extern  int check PROTO_S ((exp e, exp scope));
extern  int eq_exp PROTO_S ((exp a, exp b));
extern  int dochvar PROTO_S ((int i, shape t));
extern  int dochvar_e PROTO_S ((int v, int big, shape f, shape t, int* pr));
extern  exp hold_check PROTO_S ((exp e));
extern  exp hold_const_check PROTO_S ((exp e));
extern  exp hold PROTO_S ((exp e));
extern  int docmp_f PROTO_S ((int test_no, exp a, exp b));
extern  ntest int_inverse_ntest[];
extern  ntest real_inverse_ntest[];
extern  ntest exchange_ntest[];

