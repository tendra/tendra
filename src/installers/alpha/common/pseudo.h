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


/* 	$Id: pseudo.h,v 1.1.1.1 1998/01/17 15:56:00 release Exp $	 */


/* 
   psu_opsdecs.h
*/

/*
$Log: pseudo.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:00  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/23  10:39:18  john
 * Entered into CVS
 *
 * Revision 1.7  1995/03/23  10:12:05  john
 * Changed prototype
 *
 * Revision 1.6  1995/01/26  13:47:22  john
 * Added prototype for set_lineno
 *
*/

#ifndef PSEUDO_H
#define PSEUDO_H
#include "cross.h"


extern void setnoreorder PROTO_S ((void));
extern void setreorder PROTO_S ((void));
extern void setnomove PROTO_S ((void));
extern void setmove PROTO_S ((void));
extern void setvolatile PROTO_S ((void));
extern void setnovolatile PROTO_S ((void));
extern void setnoat PROTO_S ((void));
extern void setat PROTO_S ((void));
extern void comment PROTO_S ((char *mess));
extern void setframe PROTO_S ((int32,int32));
extern void set_text_section PROTO_S ((void));
extern void setmask PROTO_S ((int mask, int disp));
extern void setfmask PROTO_S ((int mask, int disp));
extern void set_file PROTO_S ((char *,int));
extern void setprologue PROTO_S ((int));
extern void set_align PROTO_S ((int));
extern void set_lineno PROTO_S ((int,int));


#endif
