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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:57:22 $
$Revision: 1.1.1.1 $
$Log: lex.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:22  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/08/21  16:00:57  currie
 * put <stdlib> at top of headers
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.2  1994/07/21  10:36:31  currie
 * Added banner
 *
***********************************************************************/
#ifndef LEX_INCLUDED
#define LEX_INCLUDED

#include "defs.h"

extern LEX reader PROTO_S((void));
extern char * fformat PROTO_S((char* s, int l));
extern void skip_term PROTO_S((int));
extern FILE *in_file ;

#endif
