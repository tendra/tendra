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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/output.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: output.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:58  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:17  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:42  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:58  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:16  john
 *
 * Revision 1.2  94/02/21  16:03:02  16:03:02  ra (Robert Andrews)
 * Put in a couple of explicit casts.
 * 
 * Revision 1.1  93/02/22  17:16:32  17:16:32  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef OUTPUT_INCLUDED
#define OUTPUT_INCLUDED

extern FILE *fpout ;

#define  outc( X )	fputc ( ( X ), fpout )
#define  outs( X )	fputs ( ( X ), fpout )
#define  outn( X )	fprintf ( fpout, "%ld", ( long ) ( X ) )
#define  outh( X )	fprintf ( fpout, "0x%lx", ( unsigned long ) ( X ) )

#ifdef EBUG
extern void outnl PROTO_S ( ( void ) ) ;
#else
#define  outnl()	fputc ( '\n', fpout )
#endif

extern void open_output PROTO_S ( ( char * ) ) ;
extern void init_instructions PROTO_S ( ( void ) ) ;
extern void init_output PROTO_S ( ( void ) ) ;
extern void output_all PROTO_S ( ( void ) ) ;

extern char *reg_names [] ;
extern char *instr_names [] ;

#endif
