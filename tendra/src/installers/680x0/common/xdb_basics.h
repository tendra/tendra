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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/xdb_basics.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: xdb_basics.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:43:02  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:23  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:57:01  john
 *
 * Revision 1.2  1996/07/05  14:35:27  john
 * Fix to diagnostics
 *
 * Revision 1.1  95/03/08  16:46:22  ra
 * Added missing files.
 * 
 * Revision 1.1  93/02/22  17:17:22  17:17:22  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef XDB_BASICS_INCLUDED
#define XDB_BASICS_INCLUDED

extern void diag_prologue PROTO_S ( ( void ) ) ;
extern void diag_epilogue PROTO_S ( ( void ) ) ;
extern void diag_start PROTO_S ( ( diag_info *, exp ) ) ;
extern void diag_end PROTO_S ( ( diag_info *, exp ) ) ;
extern void xdb_diag_proc_begin PROTO_S ( ( diag_global *, exp, char *, long, int ) ) ;
extern void xdb_diag_proc_return PROTO_S ( ( void ) ) ;
extern void xdb_diag_proc_end PROTO_S ( ( diag_global * ) ) ;
extern void xdb_diag_val_begin PROTO_S ( ( diag_global *, char *, long, int ) ) ;
extern dec *sort_decs PROTO_S ( ( dec * ) ) ;
extern void OUTPUT_GLOBALS_TAB PROTO_S ( ( void ) ) ;
extern void OUTPUT_DIAG_TAGS PROTO_S ( ( void ) ) ;
extern void INSPECT_FILENAME PROTO_S ( ( filename ) ) ;

#endif
