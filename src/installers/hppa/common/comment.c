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
$Log: comment.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:11:02  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.5  1995/08/25  11:20:15  wfs
 * Name of installer occuring in messages changed from "hppatrans" to
 * "trans"
 *
 * Revision 3.5  1995/08/25  11:20:15  wfs
 * Name of installer occuring in messages changed from "hppatrans" to
 * "trans"
 *
 * Revision 3.4  1995/08/25  09:12:46  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:25:56  16:25:56  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:14:35  11:14:35  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:25:28  15:25:28  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.2  95/01/17  17:21:25  17:21:25  wfs (William Simmonds)
 * name of included header file changed
 * 
 * Revision 1.1  95/01/11  13:03:22  13:03:22  wfs (William Simmonds)
 * Initial revision
 * 
*/


#define HPPATRANS_CODE
#include "config.h"
#include "comment.h"
#include "const.h"
#include "out.h"


/*
    FLAG : PRINT COMMENTS?

    This is set in hppatrans.c.
*/

bool do_comment ;


/*
    COMMENTING ROUTINES

    If DO_COMMENT is not defined then these routines are replaced by
    the macros in comment.h.
*/

#ifdef DO_COMMENT

void comment 
    PROTO_N ( ( mess ) )
    PROTO_T ( char * mess )
{
    if ( do_comment ) {
	fprintf(outf, "!! " ) ;
	fprintf ( outf,"%s\n", mess ) ;
    }
    return ;
}

void comment1 
    PROTO_N ( ( mess, p1 ) )
    PROTO_T ( char * mess X long p1 )
{
    if ( do_comment ) {
	fprintf(outf, "!! " ) ;
	fprintf ( outf, mess, p1 ) ;
	fputc('\n',outf);
    }
    return ;
}

void comment2 
    PROTO_N ( ( mess, p1, p2 ) )
    PROTO_T ( char * mess X long p1 X long p2 )
{
    if ( do_comment ) {
	fprintf(outf, "!! " ) ;
	fprintf ( outf, mess, p1, p2 ) ;
	fputc('\n',outf);
    }
    return ;
}

void comment3 
    PROTO_N ( ( mess, p1, p2, p3 ) )
    PROTO_T ( char * mess X long p1 X long p2 X long p3 )
{
    if ( do_comment ) {
	fprintf(outf, "!! " ) ;
	fprintf ( outf, mess, p1, p2, p3 ) ;
	fputc('\n',outf);
    }
    return ;
}

void comment4 
    PROTO_N ( ( mess, p1, p2, p3, p4 ) )
    PROTO_T ( char * mess X long p1 X long p2 X long p3 X long p4 )
{
    if ( do_comment ) {
	fprintf(outf, "!! " ) ;
	fprintf ( outf, mess, p1, p2, p3, p4 ) ;
	fputc('\n',outf);
    }
    return ;
}

#endif /* DO_COMMENT */


/*
    ERROR REPORTING ROUTINE
*/

void fail 
    PROTO_N ( ( mess ) )
    PROTO_T ( char * mess )
{
    if ( do_comment ) {
	fprintf(outf, "!! TRANSLATION FAILED : " ) ;
	fprintf(outf, mess ) ;
	fputc('\n',outf);
	fflush ( outf ) ;
    }
    fprintf ( stderr, "trans : internal error '%s'\n", mess ) ;
    if ( !do_comment ) exit ( EXIT_FAILURE ) ;
    /* generate more code to give the error context when commenting */
    return ;
}



