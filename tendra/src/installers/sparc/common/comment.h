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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/comment.h,v 1.1.1.1 1998/01/17 15:55:53 release Exp $
--------------------------------------------------------------------------
$Log: comment.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/07/14  16:29:51  john
 * Added comment macro
 *
 * Revision 1.1.1.1  1995/03/13  10:18:29  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:07  djch
 * Initial revision
 *
 * Revision 1.3  93/08/13  14:35:40  14:35:40  ra (Robert Andrews)
 * Got rid of the comment macros.
 * 
 * Revision 1.2  93/06/29  14:23:42  14:23:42  ra (Robert Andrews)
 * Declared sparctrans (executable name).
 * 
 * Revision 1.1  93/06/24  14:58:05  14:58:05  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef COMMENT_INCLUDED
#define COMMENT_INCLUDED

#include "exptypes.h"
#include "codetypes.h"
#include "installtypes.h"

extern char *sparctrans ;
extern bool do_comment ;
extern void fail PROTO_S ( ( char * ) ) ;
extern FILE *as_file;

#define comment(st)	fprintf(as_file,"\t! %s\n",st);

#endif /* COMMENT_INCLUDED */
