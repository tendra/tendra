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
$Date: 1998/01/17 15:55:45 $
$Revision: 1.1.1.1 $
$Log: table_fns.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
***********************************************************************/
#ifndef table_decs_key
#define table_decs_key 1




extern exp get_lab PROTO_S ((label l));
  /* find the exp which is labelled by l */

extern void set_lab PROTO_S ((label l, exp e));
  /* set the exp which is labelled by l */

extern exp get_tag PROTO_S ((tag tg));
  /* find the exp known as tg */

extern void set_tag PROTO_S ((tag tg, exp e));
  /* set the exp known as tg */


extern dec * get_dec PROTO_S ((int tg));
  /* find the tag declaration indexed by tg */

extern aldef * get_aldef PROTO_S ((int tg));
  /* find the alignment tag value indexed by tg */

extern tok_define * get_tok PROTO_S ((int tk));
  /* find the token declaration indexed by tg */

extern tokval apply_tok PROTO_S((token tk, bitstream pars, int sortcode,
				tokval * actual_pars));
  /* apply tk to its parameters in pars, and return the result */

#endif
