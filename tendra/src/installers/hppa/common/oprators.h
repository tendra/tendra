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
$Log: oprators.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:12:16  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.2  1995/10/20  14:08:50  wfs
 * Declared "import_long_double_lib()" for gcc compilation.
 *
 * Revision 5.1  1995/09/15  14:30:15  wfs
 * Some "extern" declarations added.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:27:41  16:27:41  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:18:33  11:18:33  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:28:23  15:28:23  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:41:21  13:41:21  wfs (William Simmonds)
 * Initial revision
 * 
*/


#ifndef OPRATORS_INCLUDED
#define OPRATORS_INCLUDED

#include "exptypes.h"
#include "addrtypes.h"

extern int comm_op PROTO_S ( ( exp, space, where, ins_p ) ) ;
extern int non_comm_op PROTO_S ( ( exp, space, where, ins_p ) ) ;
extern int monop PROTO_S ( ( exp, space, where, ins_p ) ) ;
extern int fop PROTO_S ( ( exp, space, where, ins_p ) ) ;
extern int fmop PROTO_S ( ( exp, space, where, char * ) ) ;
extern void logical_op PROTO_S (( CONST char*, long, int, int ));
extern void quad_op PROTO_S (( exp, space, where ));
extern void tidyshort PROTO_S (( int, shape ));
extern void import_long_double_lib PROTO_S (( void ));
#endif /* OPRATORS_INCLUDED */
