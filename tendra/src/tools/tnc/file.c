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


#include "config.h"
#include "types.h"
#include "fetch.h"
#include "read_types.h"
#include "analyser.h"
#include "utility.h"


/*
    LIST OF DIRECTORIES

    This is the list of all directories to be searched for included files.
*/

static directory *search_path = null ;


/*
    INPUT FILE

    The current input file, together with its name.
*/

FILE *input ;
char *input_file = null ;


/*
    OPEN INPUT FILE

    This routine opens the file nm.  If search is true it will search
    for it along search_path.
*/

void open_input
    PROTO_N ( ( nm, search ) )
    PROTO_T ( char *nm X int search )
{
    input = fopen ( nm, ( text_input ? "r" : "rb" ) ) ;
    if ( search && input == null ) {
	directory *d = search_path ;
	while ( input == null && d ) {
	    char buff [1000] ;
	    IGNORE sprintf ( buff, "%s/%s", d->dirname, nm ) ;
	    input = fopen ( buff, ( text_input ? "r" : "rb" ) ) ;
	    d = d->next ;
	}
    }
    if ( input == null ) fatal_error ( "Can't open input file, %s", nm ) ;
    input_file = nm ;
    bits_in_buff = 0 ;
    bytes_read = 0 ;
    crt_line_no = 1 ;
    line_no = 1 ;
    looked_ahead = 0 ;
    return ;
}


/*
    ADD A DIRECTORY TO THE SEARCH PATH

    The directory nm is added to search_path.
*/

void add_directory
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    directory *d = alloc_nof ( directory, 1 ) ;
    d->dirname = nm ;
    d->next = null ;
    if ( search_path == null ) {
	search_path = d ;
    } else {
	directory *p = search_path ;
	while ( p->next ) p = p->next ;
	p->next = d ;
    }
    return ;
}


/*
    OUTPUT FILE

    The current output file.
*/

FILE *output /* = stdout */ ;


/*
    OPEN OUTPUT FILE

    The output file nm is opened.
*/

void open_output
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    static char *opened = null ;
    if ( opened ) {
	warning ( "Multiple output files given, using %s", opened ) ;
	return ;
    }
    output = fopen ( nm, ( text_output ? "w" : "wb" ) ) ;
    if ( output == null ) fatal_error ( "Can't open output file, %s", nm ) ;
    opened = nm ;
    return ;
}
