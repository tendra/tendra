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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/needscan.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: needscan.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/12/04  19:54:27  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.3  1995/10/31  12:47:46  john
 * Introduced min macro
 *
 * Revision 1.2  1995/05/26  13:00:08  john
 * Reformatting
 *
 * Revision 1.1.1.1  1995/03/13  10:18:50  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:28  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:58:56  14:58:56  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef NEEDSCAN_INCLUDED
#define NEEDSCAN_INCLUDED

#include "exptypes.h"
#include "proctypes.h"

extern bool chase PROTO_S ( ( exp, exp * ) ) ;
extern bool complex PROTO_S ( ( exp ) ) ;
extern bool subvar_use PROTO_S ( ( exp ) ) ;
extern bool unchanged PROTO_S ( ( exp, exp ) ) ;
extern exp *ptr_position PROTO_S ( ( exp ) ) ;
extern needs fpop PROTO_S ( ( exp *, exp ** ) ) ;
extern needs likediv PROTO_S ( ( exp *, exp ** ) ) ;
extern needs likeplus PROTO_S ( ( exp *, exp ** ) ) ;
extern needs maxneeds PROTO_S ( ( needs, needs ) ) ;
extern needs maxtup PROTO_S ( ( exp, exp ** ) ) ;
extern needs scan PROTO_S ( ( exp *, exp ** ) ) ;
extern needs shapeneeds PROTO_S ( ( shape ) ) ;
extern void cca PROTO_S ( ( exp **, exp * ) ) ;
extern void check_asm_seq PROTO_S ( ( exp, int ) ) ;

extern int maxfix, maxfloat ;
#define max(X,Y) (X>Y)?(X):(Y)
#define min(X,Y) (X<Y)?(X):(Y)
#endif /* NEEDSCAN_INCLUDED */
