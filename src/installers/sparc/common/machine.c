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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/machine.c,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: machine.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:42  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.2  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.1  1994/05/03  14:49:42  djch
 * Initial revision
 *
 * Revision 1.5  94/02/21  16:11:33  16:11:33  ra (Robert Andrews)
 * reg_result now returns an int, not a bool.
 * 
 * Revision 1.4  93/09/27  14:47:18  14:47:18  ra (Robert Andrews)
 * Long double procedure return values are not passed in registers.
 * 
 * Revision 1.3  93/08/27  11:29:57  11:29:57  ra (Robert Andrews)
 * Added a couple of explicit integer casts.  Removed definitions of
 * local_prefix and name_prefix (they are duplicated in sparctrans.c).
 * 
 * Revision 1.2  93/06/29  14:27:38  14:27:38  ra (Robert Andrews)
 * Need to include regable.h.
 * 
 * Revision 1.1  93/06/24  14:58:39  14:58:39  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#define SPARCTRANS_CODE
#include "config.h"
#include "common_types.h"
#include "expmacs.h"
#include "shapemacs.h"
#include "regable.h"


/*
    DOES A PROCEDURE RETURN THE GIVEN SHAPE IN A REGISTER?
*/

int reg_result 
    PROTO_N ( ( sha ) )
    PROTO_T ( shape sha )
{
    if ( valregable ( sha ) ) return ( 1 ) ;
    if ( is_floating ( name ( sha ) ) ) {
#if use_long_double
	if ( shape_size ( sha ) > 64 ) return ( 0 ) ;
#endif
	return ( 1 ) ;
    }
    return ( 0 ) ;
}
