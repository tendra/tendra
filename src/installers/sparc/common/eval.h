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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/eval.h,v 1.1.1.1 1998/01/17 15:55:53 release Exp $
--------------------------------------------------------------------------
$Log: eval.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1997/10/10  18:32:17  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.1.1.1  1995/03/13  10:18:32  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:12  djch
 * Initial revision
 *
 * Revision 1.2  93/08/27  11:24:29  11:24:29  ra (Robert Andrews)
 * The routines oneval and set_align are now static.
 * 
 * Revision 1.1  93/06/24  14:58:10  14:58:10  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef EVALDECS_INCLUDED
#define EVALDECS_INCLUDED

#include "addrtypes.h"
#include "flpttypes.h"
#include "common_types.h"

extern bool is_zero PROTO_S ( ( exp ) ) ;
extern instore evaluated PROTO_S ( ( exp, long, bool ) ) ;
extern int next_data_lab PROTO_S ( ( void ) ) ;
extern long *realrep PROTO_S ( ( exp ) ) ;
extern long evalexp PROTO_S ( ( exp ) ) ;
extern mm maxmin PROTO_S ( ( shape ) ) ;
extern void evalone PROTO_S ( ( exp, int, bool ) ) ;
extern void outlab PROTO_S ( ( int ) ) ;

#endif /* EVALDECS_INCLUDED */
