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


/**** contents.c --- Front end to library contents mode of TDF linker.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file provides the front end to the library contents mode of the TDF
 * linker.
 *
 **** Change Log:
 * $Log: contents.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:16  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1995/09/22  08:37:04  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 *
 * Revision 1.3  1995/07/07  15:31:57  smf
 * Updated to support TDF specification 4.0.
 *
 * Revision 1.2  1994/12/12  11:43:59  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:24  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "contents.h"
#include "gen-errors.h"
#include "library.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

void
contents_main PROTO_N ((arg_data))
	      PROTO_T (ArgDataP arg_data)
{
    BoolT     content_index   = arg_data_get_content_index (arg_data);
    BoolT     content_size    = arg_data_get_content_size (arg_data);
    BoolT     content_version = arg_data_get_content_version (arg_data);
    unsigned  num_files       = arg_data_get_num_files (arg_data);
    CStringP *files           = arg_data_get_files (arg_data);
    LibraryP  library;

    if (num_files != 1) {
	E_too_many_library_files ();
	UNREACHED;
    }
    if ((library = library_create_stream_input (files [0])) !=
	NIL (LibraryP)) {
	library_content (library, content_index, content_size,
			 content_version);
	library_close (library);
    } else {
	E_cannot_open_input_file (files [0]);
    }
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
	exit (EXIT_FAILURE);
	UNREACHED;
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library" "../tdf")
 * eval: (include::add-path-entry "../generated")
 * End:
**/
