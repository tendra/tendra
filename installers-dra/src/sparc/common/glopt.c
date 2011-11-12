/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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

void 
glopt ( dec * dp ){
  /* +++ add any SPARC-specific optimisations here */
  return ;
}
