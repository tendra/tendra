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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/glopt.c,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: glopt.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/05/26  12:58:23  john
 * Reformatting
 *
 * Revision 1.1.1.1  1995/03/13  10:18:36  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.2  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.1  1994/05/03  14:49:36  djch
 * Initial revision
 *
 * Revision 1.3  93/08/27  11:26:49  11:26:49  ra (Robert Andrews)
 * Tell lint that glopt does not use its argument.
 * 
 * Revision 1.2  93/06/29  14:25:51  14:25:51  ra (Robert Andrews)
 * Changed to new style procedure definitions.
 * 
 * Revision 1.1  93/06/24  14:58:23  14:58:23  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#define SPARCTRANS_CODE
#include "config.h"
#include "common_types.h"
#include "tags.h"
#include "externs.h"
#include "expmacs.h"
#include "shapemacs.h"
#include "exp.h"
#include "basicread.h"
#include "flags.h"
#include "table_fns.h"
#include "installglob.h"
#include "check.h"
#include "glopt.h"


/*
  GLOBAL OPTIMISATIONS
*/

void glopt 
    PROTO_N ( ( dp ) )
    PROTO_T ( dec * dp ){
  /* +++ add any SPARC-specific optimisations here */
  return ;
}
