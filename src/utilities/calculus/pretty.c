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


#define calculus_IO_ROUTINES
#include "config.h"
#include "calculus.h"
#include "common.h"
#include "error.h"
#include "pretty.h"


/*
    AUTOMATICALLY GENERATED PRETTY PRINTING ROUTINES

    The main pretty printing routines are automatically generated.  The
    various macros are used to customise these routines.
*/

#define OUTPUT_int( A, B )	fprintf_v ( ( A ), "%d", ( B ) )
#define OUTPUT_number( A, B )	fprintf_v ( ( A ), "%lu", ( B ) )
#define OUTPUT_string( A, B )	fprintf_v ( ( A ), "\"%s\"", ( B ) )

#ifndef DEBUG
#define BAD_PRINT_OP				0
#define PRINT_alg( A, B, C, D )			ASSERT ( BAD_PRINT_OP )
#define PRINT_list_ptr_en( A, B, C, D )		ASSERT ( BAD_PRINT_OP )
#define PRINT_list_ptr_ident( A, B, C, D )	ASSERT ( BAD_PRINT_OP )
#define PRINT_list_ptr_prim( A, B, C, D )	ASSERT ( BAD_PRINT_OP )
#define PRINT_list_ptr_str( A, B, C, D )	ASSERT ( BAD_PRINT_OP )
#define PRINT_list_ptr_un( A, B, C, D )		ASSERT ( BAD_PRINT_OP )
#define PRINT_ptr_int( A, B, C, D )		ASSERT ( BAD_PRINT_OP )
#define PRINT_ptr_number( A, B, C, D )		ASSERT ( BAD_PRINT_OP )
#define PRINT_ptr_ptr_cid( A, B, C, D )		ASSERT ( BAD_PRINT_OP )
#define PRINT_ptr_ptr_type( A, B, C, D )	ASSERT ( BAD_PRINT_OP )
#define PRINT_ptr_string( A, B, C, D )		ASSERT ( BAD_PRINT_OP )
#endif

#include "print_def.h"


/*
    PRETTY PRINT AN ALGEBRA

    This routine pretty prints the entire algebra type list into the
    file named nm.
*/

void pretty_file
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    int old_indent_step ;
    int old_ptr_depth ;
    int old_list_expand ;

    /* Open file */
    FILE *f ;
    if ( streq ( nm, "." ) ) {
	f = stdout ;
    } else {
	f = fopen ( nm, "w" ) ;
	if ( f == NULL ) {
	    error ( ERROR_SERIOUS, "Can't open output file, '%s'", nm ) ;
	    return ;
	}
    }

    /* Save values */
    old_indent_step = print_indent_step ;
    old_ptr_depth = print_ptr_depth ;
    old_list_expand = print_list_expand ;
    print_indent_step = 2 ;
    print_ptr_depth = 10000 ;
    print_list_expand = 1 ;

    /* Print the algebra */
    PRINT_string ( f, algebra->name, "name", 0 ) ;
    PRINT_int ( f, algebra->major_no, "major_no", 0 ) ;
    PRINT_int ( f, algebra->minor_no, "minor_no", 0 ) ;
    fputc_v ( '\n', f ) ;
    PRINT_list_ptr_type ( f, algebra->types, "types", 0 ) ;

    /* Restore values */
    clear_calculus_alias () ;
    print_indent_step = old_indent_step ;
    print_ptr_depth = old_ptr_depth ;
    print_list_expand = old_list_expand ;

    /* Close file */
    if ( f != stdout ) fclose_v ( f ) ;
    return ;
}
