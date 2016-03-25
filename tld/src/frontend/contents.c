/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * contents.c - Front end to library contents mode of TDF linker.
 *
 * This file provides the front end to the library contents mode of the TDF
 * linker.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
contents_main(ArgDataT *arg_data)
{
    bool     content_index   = arg_data_get_content_index(arg_data);
    bool     content_size    = arg_data_get_content_size(arg_data);
    bool     content_version = arg_data_get_content_version(arg_data);
    unsigned  num_files       = arg_data_get_num_files(arg_data);
    char * *files           = arg_data_get_files(arg_data);
    LibraryT * library;

    if (num_files != 1) {
	 error(ERR_FATAL, "too many library files specified (should be one)");
	UNREACHED;
    }
    if ((library = library_create_stream_input(files[0])) !=
	NULL) {
	library_content(library, content_index, content_size,
			 content_version);
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
