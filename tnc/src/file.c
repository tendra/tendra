/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include "config.h"
#include "types.h"
#include "fetch.h"
#include "file.h"
#include "read_types.h"
#include "analyser.h"
#include "utility.h"


/*
    This is the list of all directories to be searched for included files.
*/

static directory *search_path = NULL;


/*
    The current input file, together with its name.
*/

FILE *input;
char *input_file = NULL;


/*
    The current output file.
*/

FILE *output /* = stdout */ ;


/*
    This routine opens the file nm.  If search is true it will search
    for it along search_path.
*/

void
open_input(char *nm, int search)
{
	input = fopen(nm,(text_input ? "r" : "rb"));

	if (search && input == NULL) {
		directory *d = search_path;

		while (input == NULL && d) {
			/* XXX: unsafe sprintf */
			char buff[1000];
			IGNORE sprintf(buff, "%s/%s", d->dirname, nm);
			input = fopen(buff, "r");
			d = d->next;
		}
	}

	if (input == NULL)
		fatal_error("Can't open input file, %s", nm);

	input_file = nm;
	rewind_posn();
	crt_line_no = 1;
	line_no = 1;
	looked_ahead = 0;
}


/*
    The directory nm is added to search_path.
*/

void
add_directory(char *nm)
{
	directory *d = xmalloc_nof(directory, 1);
	d->dirname = nm;
	d->next = NULL;

	if (search_path == NULL)
		search_path = d;
	else {
		directory *p = search_path;

		while (p->next)
			p = p->next;

		p->next = d;
	}
}


/*
    The output file nm is opened.
*/

void
open_output(char *nm)
{
	static char *opened = NULL;

	if (opened) {
		warning("Multiple output files given, using %s", opened);
		return;
	}

	output = fopen(nm, "w");
	if (output == NULL)
		fatal_error("Can't open output file, %s", nm);

	opened = nm;
}
