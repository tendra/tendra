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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/tempdecs.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: tempdecs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:59  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:51  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:59:34  14:59:34  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef TEMPDECS_INCLUDED
#define TEMPDECS_INCLUDED

#include "exptypes.h"

extern bool tempdecopt ;
extern bool simple_seq PROTO_S ( ( exp, exp ) ) ;
extern bool tempdec PROTO_S ( ( exp, bool ) ) ;
extern int trace_uses PROTO_S ( ( exp, exp ) ) ;
extern void after_a PROTO_S ( ( exp, exp ) ) ;

#endif /* TEMPDECS_INCLUDED */
