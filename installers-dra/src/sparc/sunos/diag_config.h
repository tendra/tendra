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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/sunos/diag_config.h,v 1.1.1.1 1998/01/17 15:55:56 release Exp $
--------------------------------------------------------------------------
$Log: diag_config.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1997/04/04  15:23:52  pwe
 * tidy re old DWARF interface
 *
 * Revision 1.1  1997/03/24  17:10:13  pwe
 * reorganise solaris/sunos split
 *
 * Revision 1.2  1995/09/13  11:01:26  john
 * Fix to prototypes
 *
 * Revision 1.1.1.1  1995/03/13  10:18:58  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:43  djch
 * Initial revision
 *
 * Revision 1.2  93/06/29  14:35:48  14:35:48  ra (Robert Andrews)
 * Minor renaming of diagnostic routines.
 * 
 * Revision 1.1  93/06/24  14:59:30  14:59:30  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef STAB_CONF_INCLUDED
#define STAB_CONF_INCLUDED

#include "config.h"

typedef long OUTPUT_REC ;
typedef diag_descriptor diag_global ;

#define INSPECT_FILENAME( x )	stab_collect_files ( x )
#define NEW_DIAG_GLOBAL( x )	( x )
#define OUTPUT_DIAG_TAGS()	stab_tagdefs ()
#define OUTPUT_GLOBALS_TAB()	stab_typedefs ()

#define DIAG_VAL_BEGIN(d,g,c,s,e)	\
				stab_global (d, e, s, g);
#define DIAG_VAL_END(d)		
#define DIAG_PROC_BEGIN(d,g,c,s,e)	\
				stab_proc (d, e, s, g);
#define DIAG_PROC_END(d)
#define CODE_DIAG_INFO(d,n,x,a)	code_diag_info (d, n, x, a);


#endif /* STAB_CONF_INCLUDED */

