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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/solaris/sparcddecs.h,v 1.1.1.1 1998/01/17 15:55:53 release Exp $
--------------------------------------------------------------------------
$Log: sparcddecs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1998/01/09  15:00:08  pwe
 * prep restructure
 *
 * Revision 1.2  1997/04/04  15:23:38  pwe
 * tidy re old DWARF interface
 *
 * Revision 1.1  1997/03/24  17:10:00  pwe
 * reorganise solaris/sunos split
 *
 * Revision 1.1.1.1  1995/03/13  10:18:55  john
 * Entered into CVS
 *
 * Revision 1.3  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.2  1994/07/04  08:35:54  djch
 * extra param to stabd
 *
 * Revision 1.1  1994/05/03  14:50:40  djch
 * Initial revision
 *
 * Revision 1.3  93/07/05  18:26:02  18:26:02  ra (Robert Andrews)
 * Include diag_fns.h for DWARF.
 * 
 * Revision 1.2  93/06/29  14:31:11  14:31:11  ra (Robert Andrews)
 * Minor renaming of diagnostic routines.
 * 
 * Revision 1.1  93/06/24  14:59:20  14:59:20  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef SPARCDDECS_INCLUDED
#define SPARCDDECS_INCLUDED

#ifdef NEWDIAGS

extern void init_stab PROTO_S ( ( void ) ) ;
extern void init_stab_aux PROTO_S ( ( void ) ) ;
extern void code_diag_info PROTO_S ( ( dg_info, void (*)(void *), void * ) );
extern void stab_global PROTO_S ( ( dg_name, exp, char *, int ) ) ;
extern void stab_proc PROTO_S ( ( dg_name, exp, char *, int ) ) ;
extern void stab_proc_end PROTO_S ( ( void ) ) ;
extern void stab_types PROTO_S ( ( void ) ) ;

#else

extern void init_stab PROTO_S ( ( void ) ) ;
extern void init_stab_aux PROTO_S ( ( void ) ) ;
extern void stab_collect_files PROTO_S ( ( filename ) ) ;
extern void stab_tagdefs PROTO_S ( ( void ) ) ;
extern void stab_typedefs PROTO_S ( ( void ) ) ;
extern void stab_begin PROTO_S ( ( diag_info *, int, exp ) ) ;
extern void stab_end PROTO_S ( ( diag_info *, exp ) ) ;
extern void stab_file PROTO_S ( ( long, bool ) ) ;
extern void stab_global PROTO_S ( ( diag_descriptor *, exp, char *, bool ) ) ;
extern void stab_local PROTO_S ( ( char *, diag_type, exp, long, long ) ) ;
extern void stab_proc PROTO_S ( ( diag_descriptor *, exp, char *, bool ) ) ;
extern void stab_proc_end PROTO_S ( ( void ) ) ;
extern void stab_types PROTO_S ( ( void ) ) ;
extern void stabd PROTO_S ( ( long, long, int ) ) ;
extern long currentfile ;

#endif

#endif /* SPARCDDECS_INCLUDED */
