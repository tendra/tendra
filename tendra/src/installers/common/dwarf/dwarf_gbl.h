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
$Author$
$Date$
$Revision$
$Log$
Revision 1.1  2002/01/26 21:31:18  asmodai
Initial version of TenDRA 4.1.2.

 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/08/14  14:30:20  pwe
 * transferred from DJCH
 *
**********************************************************************/

/* 14/2/94 djch new_dwarf_global was declared as diag_global *, but should
   be dwarf_global *. Note that diag_global is typedefed to be 
   dwarf_global in diag_config.h */

				/* this is on its own to break cycles */
extern void out_dwarf_global_list PROTO_S ((void)); 
extern void out_dwarf_diag_tags PROTO_S ((void)); 
extern dwarf_global *new_dwarf_global PROTO_S ((diag_descriptor * d));
extern void dwarf_inspect_filename PROTO_S ((filename f));

