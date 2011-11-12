/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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


#include <shared/error.h>

#include "config.h"
#include "utility.h"
#define failer failer_reject
#include "basicread.c"


/*
    OPEN INPUT FILE

    This routine is intended to replace initreader in basicread.c.
*/

void
open_input(char *nm)
{
	crt_dot_t = nm;
	crt_lno = -1;
	failer_count = 0;

	if (strcmp(nm, "-")) {
		fpin = fopen(nm, "r");
		if (fpin == null) {
			error(ERROR_FATAL, "Can't open input file, %s", nm);
		}
	} else {
		int c;
		fpin = tmpfile();
		if (fpin == null) {
			error(ERROR_FATAL, "Can't open temporary file");
		}
		while (c = fgetc(stdin), c != EOF) {
			fputc(c, fpin);
		}
		rewind(fpin);
	}
	pkt_index = -1;
	file_pkt = -1;
	table_flag = 0;
	getcode_bitposn = 0;
	read_line(1);
	crt_line = buff;
	crt_ptr = crt_line;
	end_ptr = crt_line + cppkt;

#if 0
	bignat_work = alloc_nof(unsigned short, 2);
	bignat_work[0] = 0;
	bignat_work[1] = 0;
	bignat_len = 2;
#endif
	return;
}
