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




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/move.h,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: move.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:44  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:25  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:58:48  14:58:48  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef MOVEDECS_INCLUDED
#define MOVEDECS_INCLUDED

#include "installtypes.h"
#include "addrtypes.h"
#include "sparcins.h"

extern ins_p i_ld_sz PROTO_S ( ( int, int ) ) ;
extern ins_p i_st_sz PROTO_S ( ( int ) ) ;

extern void ld_addr PROTO_S ( ( instore, int ) ) ;
extern int addr_reg PROTO_S ( ( instore, long ) ) ;

extern int move PROTO_S ( ( ans, where, long, bool ) ) ;

#endif /* MOVEDECS_INCLUDED */
