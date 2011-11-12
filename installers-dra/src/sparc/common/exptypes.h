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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/exptypes.h,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: exptypes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/08/23  13:53:40  pwe
 * initial ANDF-DE
 *
 * Revision 1.3  1997/02/18  11:47:50  pwe
 * NEWDIAGS for debugging optimised code
 *
 * Revision 1.2  1995/12/15  10:12:30  john
 * Minor change
 *
 * Revision 1.1.1.1  1995/03/13  10:18:33  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:14  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:58:13  14:58:13  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef EXPTYPES_INCLUDED
#define EXPTYPES_INCLUDED

#include "config.h"

#include "codetypes.h"

#include "dg_first.h"
#include "diaginfo.h"



/*
    TYPE REPRESENTING EXPRESSION PROPERTIES
*/

typedef unsigned short prop ;


/*
    UNION REPRESENTING AN EXPRESSION CONSTITUENT
*/

typedef union {
    struct exp_t *e ;
    char *str ;
    int l ;
    unsigned int ui ;
    float f ;
    struct dec_t *glob ;
#ifndef NEWDIAGS
    diag_info *d ;
#endif
    struct aldef_t *ald ;
} expno ;


/*
    TYPE REPRESENTING AN EXPRESSION
*/

struct exp_t {
    expno brof ;
    expno numf ;
    expno ptf ;
    expno sonf ;
    struct exp_t *shf ;
    prop propsf ;
    unsigned char namef ;
    unsigned int lastf : 1 ;
    unsigned int park : 1 ;
#ifdef NEWDIAGS
    diag_info * diagf; 
#endif
} ;

typedef struct exp_t *exp ;

#endif /* EXPTYPES_INCLUDED */
