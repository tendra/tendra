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
$Log: dg_fns.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1997/08/23  13:26:49  pwe
 * initial ANDF-DE
 *
***********************************************************************/

#ifndef dg_fns_key
#define dg_fns_key 1

extern int unit_no_of_dgtags;
extern dgtag_struct ** unit_ind_dgtags;
extern dgtag_struct * 	unit_dgtagtab;

extern void init_capsule_dgtags PROTO_S ((void));
extern void init_unit_dgtags PROTO_S ((int n));
extern void start_make_dg_comp_unit PROTO_S ((int toks, int tags, int als, int dgnames));
extern void f_make_dg_comp_unit PROTO_S ((void));
extern void f_make_dglink PROTO_S ((tdfint i, tdfint ext));
extern linkextern f_make_dgtagextern PROTO_S ((tdfint internal, external ext));

extern exp f_dg_exp PROTO_S ((exp body, dg diagnostic));
extern exp read_dg_exp PROTO_S ((exp body));


#endif
