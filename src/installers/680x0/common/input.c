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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/input.c,v 1.1.1.1 1998/01/17 15:55:48 release Exp $
--------------------------------------------------------------------------
$Log: input.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:54  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:12  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:56:54  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:12  john
 *
 * Revision 1.3  94/02/21  15:58:54  15:58:54  ra (Robert Andrews)
 * Accomodate changes in basicread.c.
 *
 * Revision 1.2  93/11/19  16:21:20  16:21:20  ra (Robert Andrews)
 * Comment of bignat stuff (no longer used).
 *
 * Revision 1.1  93/02/22  17:15:49  17:15:49  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#include "config.h"
#include "utility.h"
#define failer failer_reject
#include "basicread.c"


/*
    OPEN INPUT FILE

    This routine is intended to replace initreader in basicread.c.
*/

void open_input
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    crt_dot_t = nm ;
    crt_lno = -1 ;
    failer_count = 0 ;

    if ( strcmp ( nm, "-" ) ) {
	fpin = fopen ( nm, "r" ) ;
	if ( fpin == null ) {
	    error ( "Can't open input file, %s", nm ) ;
	    exit ( EXIT_FAILURE ) ;
	}
    } else {
	int c ;
	fpin = tmpfile () ;
	if ( fpin == null ) {
	    error ( "Can't open temporary file" ) ;
	    exit ( EXIT_FAILURE ) ;
	}
	while ( c = fgetc ( stdin ), c != EOF ) fputc ( c, fpin ) ;
	rewind ( fpin ) ;
    }
    pkt_index = -1 ;
    file_pkt = -1 ;
    table_flag = 0 ;
    getcode_bitposn = 0 ;
    read_line ( 1 ) ;
    crt_line = buff ;
    crt_ptr = crt_line ;
    end_ptr = crt_line + cppkt ;

#if 0
    bignat_work = alloc_nof ( unsigned short, 2 ) ;
    bignat_work [0] = 0 ;
    bignat_work [1] = 0 ;
    bignat_len = 2 ;
#endif
    return ;
}
