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
$Log: dwarf_loc.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/09/28  12:39:45  pwe
 * dwarf.h via import, and type changes for tcc checks
 *
 * Revision 1.1.1.1  1995/08/14  14:30:22  pwe
 * transferred from DJCH
 *
**********************************************************************/

extern void out_dwarf_member_loc_attr PROTO_S ((exp e));
extern void out_dwarf_bit_member_loc_attr PROTO_S ((int u));
extern int  out_dwarf_loc_attr PROTO_S ((exp t, int proc_no));
extern void	out_dwarf_const4 PROTO_S ((exp x));
extern void	out_dwarf_const_by8 PROTO_S ((exp x));

