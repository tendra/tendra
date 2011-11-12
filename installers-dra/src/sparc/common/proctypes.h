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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/proctypes.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: proctypes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/07/14  16:33:48  john
 * Changes for new spec
 *
 * Revision 1.2  1995/05/26  13:00:41  john
 * Reformatting
 *
 * Revision 1.1.1.1  1995/03/13  10:18:52  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:33  djch
 * Initial revision
 *
 * Revision 1.2  93/08/27  11:35:29  11:35:29  ra (Robert Andrews)
 * Added comments.  Changed properties field of needs and introduced
 * macros for manipulating it.
 * 
 * Revision 1.1  93/06/24  14:59:06  14:59:06  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef PROCTYPES_INCLUDED
#define PROCTYPES_INCLUDED

#include "exptypes.h"


/*
  TYPE REPRESENTING REGISTER NEEDS
*/

typedef struct {
    int fixneeds  ;
    int floatneeds ;
    prop prps ;
    int maxargs ;
  int callee_size;
} needs ;

int callee_size;

/*
  MACROS FOR MANIPULATING PROPERTIES OF NEEDS
*/

#define pnset( x, m )	( x ).prps = ( prop ) ( ( x ).prps | ( m ) )
#define pnclr( x, m )	( x ).prps = ( prop ) ( ( x ).prps & ~( m ) )
#define pntst( x, m )	( ( x ).prps & ( m ) )


/*
  TYPE REPRESENTING REGISTER WEIGHTS
*/

#define wfixno		25
#define wfloatno	16

typedef struct {
    float fix [ wfixno ] ;
    float floating [ wfloatno ] ;
} weights ;

typedef struct {
    weights wp_weights ;
    long fix_break ;
    long float_break ;
} wp ;


/*
  TYPE REPRESENTING THE SPACE REQUIRED BY A PROCEDURE
*/

typedef struct {
    long fixdump ;
    long fltdump ;
    long stack ;
} spacereq ;


/*
  TYPE REPRESENTING A PROCEDURE RECORD
*/

typedef struct {
    exp nameproc ;
    int tlrecstart ;
    needs needsproc ;
    spacereq spacereqproc ;
    int expproc ;
} procrec ;


/*
  TYPE REPRESENTING REGISTER USAGE
*/

typedef struct {
    long fixed ;
    long flt ;
} space  ;


/*
  Type representing postlude chain
*/
typedef struct _postl {
  exp postlude;
  struct _postl * outer;
} postlude_chain;


#endif /* PROCTYPES_INCLUDED */
