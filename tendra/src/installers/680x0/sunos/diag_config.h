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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/sunos/diag_config.h,v 1.1.1.1 1998/01/17 15:55:51 release Exp $
--------------------------------------------------------------------------
$Log: diag_config.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:43:01  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:22  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:57:01  john
 *
 * Revision 1.2  1996/07/05  14:31:10  john
 * Removed copyright message
 *
 * Revision 0.1  95/03/08  16:32:46  ra
 * .
 * 
 * Revision 1.1  93/02/22  17:19:41  17:19:41  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef DIAG_CONFIG_INCLUDED
#define DIAG_CONFIG_INCLUDED

typedef diag_descriptor diag_global ;
typedef void *OUTPUT_REC ;
#define NEW_DIAG_GLOBAL( X ) X

#endif
