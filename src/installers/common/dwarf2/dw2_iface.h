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
$Date: 1998/01/17 15:55:48 $
$Revision: 1.1.1.1 $
$Log: dw2_iface.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/11/06  09:22:11  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.3  1997/10/10  18:18:35  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.2  1997/08/23  13:36:42  pwe
 * initial ANDF-DE
 *
 * Revision 1.1  1997/03/20  16:09:15  pwe
 * first version
 *
**********************************************************************/

#ifndef dw2_iface_key
#define dw2_iface_key 1

extern int dwarf2;
extern long dw_info_start;
extern long dw_text_start;

extern void dw_out_path PROTO_S ((dg_filename f, int w));
extern void init_dwarf2 PROTO_S ((void));
extern void dwarf2_prelude PROTO_S ((void));
extern void dwarf2_postlude PROTO_S ((void));
extern void end_dwarf2 PROTO_S ((void));

#endif
