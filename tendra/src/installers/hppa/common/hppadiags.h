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
$Log: hppadiags.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:11:28  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.4  1995/10/20  13:51:54  wfs
 * Added the declaration of "output_DEBUG()" for gcc compilation.
 *
 * Revision 5.3  1995/10/09  13:08:17  wfs
 * Cosmetic changes.
 *
 * Revision 5.2  1995/09/25  11:21:40  wfs
 * *** empty log message ***
 *
 * Revision 5.1  1995/09/15  14:01:35  wfs
 * "extern void stab_end PROTO_S (( diag_info*, exp ))" added.
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
 * Revision 3.1  95/04/10  16:26:42  16:26:42  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:17:20  11:17:20  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:27:07  15:27:07  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/17  14:12:19  14:12:19  wfs (William Simmonds)
 * Initial revision
 * 
*/


#ifndef HPPADDECS_INCLUDED
#define HPPADDECS_INCLUDED

extern void init_stab PROTO_S ( ( void ) ) ;
extern void init_stab_aux PROTO_S ( ( void ) ) ;
extern void stab_collect_files PROTO_S ( ( filename ) ) ;
extern void stab_tagdefs PROTO_S ( ( void ) ) ;
extern void stab_typedefs PROTO_S ( ( void ) ) ;
extern void stab_begin PROTO_S ( ( diag_info *, int, exp ) ) ;

extern void init_stab_aux PROTO_S ( ( void ) ) ;
extern void init_diag PROTO_S ( ( void ) ) ;
extern void stab_file PROTO_S ( ( long, bool ) ) ;
extern void stabn PROTO_S ( ( long, long ) ) ;
extern long diagbr_open PROTO_S ( ( long ) ) ;
extern void diagbr_close PROTO_S ( ( long ) ) ;
extern void stab_types PROTO_S ( ( void ) ) ;
extern void stab_global PROTO_S ( ( shape, char *, bool ) ) ;
extern void stab_proc PROTO_S ( ( exp, char *, bool ) ) ;
extern void stab_local PROTO_S ( ( char *, diag_type, exp, long, long ) ) ;
extern void close_function_scope PROTO_S ( ( int ) );
extern long currentfile ;
extern void stab_end PROTO_S (( diag_info*, exp ));
#ifdef _SYMTAB_INCLUDED
extern void output_DEBUG PROTO_S (( void ));
#endif
#endif /* HPPADDECS_INCLUDED */

