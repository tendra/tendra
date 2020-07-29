/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * extract.c - Front end to library extraction mode of TDF linker.
 *
 * This file provides the front end to the library extraction mode of the TDF
 * linker.
 */

/* For extracting capsules from a library, only a single shape table
   is used to store the library index. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <exds/common.h>
#include <exds/error.h>

#include "adt/library.h"
#include "adt/solve-cycles.h"
#include "adt/arg-data.h"

void
extract_main(ArgDataT *arg_data)
{
    bool     extract_all  = arg_data_get_extract_all(arg_data);
    bool     extract_base = arg_data_get_extract_basename(arg_data);
    bool     match_base   = arg_data_get_extract_match_base(arg_data);
    unsigned  num_files    = arg_data_get_num_files(arg_data);
    char * *files        = arg_data_get_files(arg_data);
    LibraryT * library;

    if (extract_all && (num_files > 1)) {
	error(ERR_FATAL,"cannot extract all capsules and named capsules");
	UNREACHED;
    } else if ((!extract_all) && (num_files == 1)) {
	error(ERR_FATAL,"no capsules specified to extract");
	UNREACHED;
    }
    if ((library = library_create_stream_input(files[0])) !=
	NULL) {
	if (extract_all) {
	    library_extract_all(library, extract_base);
	} else {
	    num_files--;
	    files++;
	    library_extract(library, extract_base, match_base, num_files,
			     files);
	}
	library_close(library);
    } else {
	error(ERR_SERIOUS, "cannot open input file '%s': %s", 
		files[0], strerror(errno));
    }
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}
