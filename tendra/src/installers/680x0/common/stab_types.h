/*
    		 Crown Copyright (c) 1996
    
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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/stab_types.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: stab_types.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:43:02  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:22  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:57:01  john
 *
 * Revision 1.2  1996/07/05  14:33:10  john
 * Removed copyright message
 *
 * Revision 1.1  95/03/08  16:46:15  ra
 * Added missing files.
 * 
 * Revision 1.2  94/02/21  16:08:31  16:08:31  ra (Robert Andrews)
 * make_stabs and make_stabn now take an int in place of one long.
 * 
 * Revision 1.1  93/02/22  17:17:18  17:17:18  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef STAB_TYPES_INCLUDED
#define STAB_TYPES_INCLUDED

extern void make_stabs PROTO_S ( ( char *, int, long, mach_op * ) ) ;
extern void make_stabn PROTO_S ( ( int, long ) ) ;
extern void init_stab_types PROTO_S ( ( void ) ) ;
extern char * analyse_stab_type PROTO_S ( ( diag_type, char *, char * ) ) ;

#endif
