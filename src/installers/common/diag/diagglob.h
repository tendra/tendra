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
$Log: diagglob.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1997/08/23  13:27:11  pwe
 * initial ANDF-DE
 *
 * Revision 1.1  1995/04/06  10:42:55  currie
 * Initial revision
 *
***********************************************************************/
#ifndef diagglob_key
#define diagglob_key



#ifndef EXTERN_DIAG
#define EXTERN_DIAG extern
#endif

#ifndef NEWDIAGS
EXTERN_DIAG diag_descriptor_list  unit_diagvar_tab;
#endif

EXTERN_DIAG int 		unit_no_of_diagtags;

EXTERN_DIAG diag_tagdef * *	unit_ind_diagtags;
EXTERN_DIAG diag_tagdef * 	unit_diag_tagdeftab;
#endif
