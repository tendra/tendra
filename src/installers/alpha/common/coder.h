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


/* 	$Id: coder.h,v 1.1.1.1 1998/01/17 15:55:59 release Exp $	 */
/* 
   coder.h 
*/

/*
$Log: coder.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:59  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/08/21  08:44:07  john
 * Changed include files
 *
 * Revision 1.2  1995/07/27  09:32:24  john
 * New structure for postlude handling
 *
 * Revision 1.1.1.1  1995/03/23  10:39:29  john
 * Entered into CVS
 *
 * Revision 1.4  1995/03/23  10:01:57  john
 * Added support for scheduler
 *
 * Revision 1.3  1995/01/26  13:38:00  john
 * Changed declaration of fscopefile
 *
*/

#ifndef CODER_H
#define CODER_H
#include "addresstypes.h"
#include "procrectypes.h"
#include "exptypes.h"

extern where nowhere;
extern int fscopefile;

extern bool last_param PROTO_S ((exp));
extern makeans make_code PROTO_S ((exp e, space sp, where dest, int exitlab));
extern int bitsin PROTO_S ((int));


typedef struct _postl {
  exp postlude;
  struct _postl * outer;
} postlude_chain;


#if !DO_SCHEDULE
#define start_new_capsule(X)
#define close_capsule()
#define false 0
#define true 1
#endif

#endif
