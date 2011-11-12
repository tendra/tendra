/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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

void
comment(char * mess)
{
    if ( do_comment ) {
	fprintf(outf, "!! " ) ;
	fprintf ( outf,"%s\n", mess ) ;
    }
    return ;
}

void
comment1(char * mess, long p1)
{
    if ( do_comment ) {
	fprintf(outf, "!! " ) ;
	fprintf ( outf, mess, p1 ) ;
	fputc('\n',outf);
    }
    return ;
}

void
comment2(char * mess, long p1, long p2)
{
    if ( do_comment ) {
	fprintf(outf, "!! " ) ;
	fprintf ( outf, mess, p1, p2 ) ;
	fputc('\n',outf);
    }
    return ;
}

void
comment3(char * mess, long p1, long p2, long p3)
{
    if ( do_comment ) {
	fprintf(outf, "!! " ) ;
	fprintf ( outf, mess, p1, p2, p3 ) ;
	fputc('\n',outf);
    }
    return ;
}

void
comment4(char * mess, long p1, long p2, long p3, long p4)
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

void
fail(char * mess)
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


