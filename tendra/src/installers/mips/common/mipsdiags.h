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
$Date: 1998/01/17 15:56:06 $
$Revision: 1.1.1.1 $
$Log: mipsdiags.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/09/12  10:59:33  currie
 * gcc pedanttry
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/*   mipsdgdecs.h   - definitions in mipsdiags.c  */
#ifndef MIPSDGDECS
#define MIPSDGDECS

#include "exptypes.h"
#include "diagtypes.h"
extern int nofds;
extern int *file_dnos;		/* dense nos for files */
extern void collect_files PROTO_S ((filename f));
extern  current_file;		/* dense no of current source file */
extern  void stab_file PROTO_S ((int i));	/* symtab entry for file source file i */
extern  void stabd PROTO_S ((long findex, long lno));/* .. entry for linenos */
extern  void diagbr_open PROTO_S ((long findex));/* .. entry for open scope */
extern  void diagbr_close PROTO_S ((long findex));/* .. entry for close scope */
extern  void stab_local PROTO_S((char *nm, diag_type dt, exp id, long disp, long
findex));
 /* entry for local */
extern  void stab_types PROTO_S ((void));	/* aux entries for types  */
extern long currentlno;


extern long find_aux PROTO_S ((diag_type s /* struct or union shape */ ));
extern void symnosforfiles PROTO_S ((void));
extern int find_file PROTO_S ((char*));

#endif
