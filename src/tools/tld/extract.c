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


/**** extract.c --- Front end to library extraction mode of TDF linker.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file provides the front end to the library extraction mode of the TDF
 * linker.
 *
 **** Change Log:
 * $Log: extract.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:16  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:37:08  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 *
 * Revision 1.2  1994/12/12  11:44:02  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:24  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "extract.h"
#include "error.h"
#include "gen-errors.h"
#include "library.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

void
extract_main PROTO_N ((arg_data))
	     PROTO_T (ArgDataP arg_data)
{
    BoolT     extract_all  = arg_data_get_extract_all (arg_data);
    BoolT     extract_base = arg_data_get_extract_basename (arg_data);
    BoolT     match_base   = arg_data_get_extract_match_base (arg_data);
    unsigned  num_files    = arg_data_get_num_files (arg_data);
    CStringP *files        = arg_data_get_files (arg_data);
    LibraryP  library;

    if (extract_all && (num_files > 1)) {
	E_all_specified_with_capsules ();
	UNREACHED;
    } else  if ((!extract_all) && (num_files == 1)) {
	E_no_capsules_specified ();
	UNREACHED;
    }
    if ((library = library_create_stream_input (files [0])) !=
	NIL (LibraryP)) {
	if (extract_all) {
	    library_extract_all (library, extract_base);
	} else {
	    num_files --;
	    files ++;
	    library_extract (library, extract_base, match_base, num_files,
			     files);
	}
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
