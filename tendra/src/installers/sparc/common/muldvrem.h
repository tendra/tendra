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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/muldvrem.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: muldvrem.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/04/17  08:25:59  john
 * Changed div2 trap treatment
 *
 * Revision 1.1.1.1  1995/03/13  10:18:46  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:26  djch
 * Initial revision
 *
 * Revision 1.3  93/09/27  14:50:54  14:50:54  ra (Robert Andrews)
 * Declare clear_sun_call_divrem_regs.
 * 
 * Revision 1.2  93/07/12  15:16:34  15:16:34  ra (Robert Andrews)
 * The final argument of call_muldivrem is now one of the SPECIAL values
 * from special.h.
 * 
 * Revision 1.1  93/06/24  14:58:51  14:58:51  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef MULDVREM_INCLUDED
#define MULDVREM_INCLUDED

#include "exptypes.h"
#include "addrtypes.h"
#include "proctypes.h"
#include "exptypes.h"
#include "installtypes.h"

extern bool is_muldivrem_call PROTO_S ( ( exp ) ) ;
extern int call_muldivrem PROTO_S ( ( exp, exp, space, int, int ) ) ;

extern needs multneeds PROTO_S ( ( exp *, exp ** ) ) ;
extern needs divneeds PROTO_S ( ( exp *, exp ** ) ) ;
extern needs remneeds PROTO_S ( ( exp *, exp ** ) ) ;

extern int do_mul_comm_op PROTO_S ( ( exp, space, where, bool ) ) ;
extern int do_div_op PROTO_S ( ( exp, space, where, bool ) ) ;
extern int do_rem_op PROTO_S ( ( exp, space, where, bool ) ) ;

extern void clear_sun_call_divrem_regs PROTO_S ( ( space ) ) ;

#endif /* MULDVREM_INCLUDED */
