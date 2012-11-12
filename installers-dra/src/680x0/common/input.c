/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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
		if (fpin == NULL) {
			error(ERROR_FATAL, "Can't open input file, %s", nm);
		}
	} else {
		int c;
		fpin = tmpfile();
		if (fpin == NULL) {
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
