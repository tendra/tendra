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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/special.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: special.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:58  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:42  djch
 * Initial revision
 *
 * Revision 1.3  93/07/14  11:23:08  11:23:08  ra (Robert Andrews)
 * Declare library_key.
 * 
 * Revision 1.2  93/07/12  15:20:07  15:20:07  ra (Robert Andrews)
 * Added support for special_routines.
 * 
 * Revision 1.1  93/06/24  14:59:29  14:59:29  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef SPECIAL_INCLUDED
#define SPECIAL_INCLUDED

#include "exp.h"
#include "proctypes.h"
#include "addrtypes.h"

extern char *special_call_name PROTO_S ( ( int ) ) ;
extern int specialfn PROTO_S ( ( exp ) ) ;
extern int specialmake PROTO_S ( ( int, exp, space, where, int ) ) ;
extern int specialopt PROTO_S ( ( exp ) ) ;
extern needs specialneeds PROTO_S ( ( int, exp, exp ) ) ;
extern speci special_fn PROTO_S ( ( exp, exp, shape ) ) ;

extern int library_key ;
extern void call_special_routine PROTO_S ( ( int ) ) ;
extern void output_special_routines PROTO_S ( ( void ) ) ;

#define SPECIAL_MUL	0
#define SPECIAL_UMUL	1
#define SPECIAL_DIV2	2
#define SPECIAL_UDIV2	3
#define SPECIAL_REM2	4
#define SPECIAL_UREM2	5
#define SPECIAL_DIV1	6
#define SPECIAL_REM1	7

#endif /* SPECIAL_INCLUDED */
