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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/translat.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: translat.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.7  1997/04/17  12:00:07  pwe
 * dwarf2 support
 *
 * Revision 1.6  1996/08/27  14:09:22  pwe
 * ensure all varargs are stored, and ptr is not64bit
 *
 * Revision 1.5  1995/11/07  09:54:05  john
 * New externs
 *
 * Revision 1.4  1995/10/04  09:01:34  john
 * Added init section
 *
 * Revision 1.3  1995/06/14  15:36:55  john
 * Added prototype for find_tag
 *
 * Revision 1.2  1995/05/26  13:02:25  john
 * Change for new spec
 *
 * Revision 1.1.1.1  1995/03/13  10:19:00  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:52  djch
 * Initial revision
 *
 * Revision 1.3  93/07/05  18:29:36  18:29:36  ra (Robert Andrews)
 * Made distinction between the System V assembler and the System V ABI.
 * 
 * Revision 1.2  93/06/29  14:38:25  14:38:25  ra (Robert Andrews)
 * Declare diag_def, init_translator and exit_translator.
 * 
 * Revision 1.1  93/06/24  14:59:37  14:59:37  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef TRANSLAT_INCLUDED
#define TRANSLAT_INCLUDED
#include "addrtypes.h"
extern int optim_level ;
extern int g_reg_max ;
extern int maxfix_tregs ;
extern int sysV_abi ;
extern int sysV_assembler ;

extern dec *diag_def ;
extern dec **main_globals ;

enum section {
    no_section = 0,
    data_section,
    text_section,
    rodata_section,
    init_section
} ;
extern int local_reg;
extern int callee_start_reg;
extern int callee_end_reg;
extern int caller_offset_used;
extern enum section current_section;
extern ash ashof PROTO_S ( ( shape ) ) ;
extern void init_translator PROTO_S ( ( void ) ) ;
extern void exit_translator PROTO_S ( ( void ) ) ;
extern void insection PROTO_S ( ( enum section ) ) ;
extern void mark_unaliased PROTO_S ( ( exp ) ) ;
extern void translate_capsule PROTO_S ( ( void ) ) ;
extern void translate_tagdef PROTO_S ( ( void ) ) ;
extern void translate_unit PROTO_S ( ( void ) ) ;
extern baseoff find_tag PROTO_S ((char *));


#endif /* TRANSLAT_INCLUDED */

