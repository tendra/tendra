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


#ifndef NAME_INCLUDED
#define NAME_INCLUDED


/*
    INPUT AND OUTPUT DIRECTORIES

    These macros give the standard input and output directories, and may
    vary between machines.
*/

#ifndef INPUT_DIR
#define INPUT_DIR		"/u/g/release/Source/src/lib/apis"
#endif

#ifndef INCLUDE_DIR
#define INCLUDE_DIR		"/u/g/release/Source/lib/include"
#endif

#ifndef SRC_DIR
#define SRC_DIR			"/u/g/release/Source/lib/building"
#endif


/*
    ENVIRONMENTAL VARIABLES

    These macros give the names of the various environmental variables
    which are checked for input and output directories.
*/

#define INPUT_ENV		"TSPEC_INPUT"
#define OUTPUT_ENV		"TSPEC_OUTPUT"
#define INCLUDE_ENV		"TSPEC_INCL_OUTPUT"
#define SRC_ENV			"TSPEC_SRC_OUTPUT"
#define COPYRIGHT_ENV		"TSPEC_COPYRIGHT"


/*
    OUTPUT INCLUDE FILES

    These macros are concerned with the include output files.
*/

#define OUTPUT_API		"%s/shared/%s.api/MASTER.h"
#define OUTPUT_FILE		"%s/%s.api/%s"
#define OUTPUT_SUBSET		"%s/shared/%s.api/%s.h"
#define OUTPUT_SUFFIX		".api"
#define OUTPUT_LENGTH		8


/*
    OUTPUT SOURCE FILES

    These macros are concerned with the source output files.
*/

#define SOURCE_API		"%s/%s.api/MASTER.c"
#define SOURCE_FILE		"%s/%s.api/%s.c"
#define SOURCE_SUBSET		"%s/%s.api/%s.c"


/*
    OUTPUT MAKEFILES

    These macros give the location of the output makefiles.
*/

#define MAKEFILE		"%s/%s.api/Makefile"
#define MAKEFILE_API		"%s/%s.api/M_%s"


/*
    MISCELLANEOUS FILES

    These macros give certain standard file names.
*/

#define MASTER_FILE		"MASTER"
#define LOCAL_API		"LOCAL"


/*
    NAME CONSTANTS

    These macros give various name prefixes and other standard names.
*/

#define HIDDEN_NAME		"__local_"
#define HIDDEN_LEN		sizeof ( HIDDEN_NAME )
#define BUILDING_MACRO		"__BUILDING_LIBS"
#define PROTECT_PREFIX		"__TDF"
#define DEFINE_PREFIX		"__BUILDING_TDF"
#define WEAK_PROTO		"__WEAK_SPEC"
#define WRONG_PREFIX		"__WRONG"


/*
    PROCEDURE DECLARATIONS

    These routines concerned with generating names of various sorts - file
    names, token names etc.
*/

extern char *basename PROTO_S ( ( char * ) ) ;
extern char *dirname PROTO_S ( ( char * ) ) ;
extern char *relative PROTO_S ( ( char *, char *, int ) ) ;
extern char *hack_name PROTO_S ( ( char *, char * ) ) ;
extern char *token_name PROTO_S ( ( char * ) ) ;
extern char *token_prefix PROTO_S ( ( char *, char *, char * ) ) ;
extern char *subset_name PROTO_S ( ( char *, char *, char * ) ) ;
extern char *include_name PROTO_S ( ( char *, char *, char *, char * ) ) ;
extern char *src_name PROTO_S ( ( char *, char *, char *, char * ) ) ;
extern char *macro_name PROTO_S ( ( char *, char *, char *, char * ) ) ;
extern char *block_name PROTO_S ( ( char *, char *, char * ) ) ;


/*
    STANDARD FLAGS

    These are standard flags which are set by command line options.
*/

extern boolean allow_long_long ;
extern boolean force_output ;
extern boolean local_input ;
extern boolean restrict_depth ;
extern boolean restrict_use ;
extern boolean unique_names ;
extern int verbose ;


/*
    INPUT AND OUTPUT DIRECTORIES

    These variables give the input and output directories.
*/

extern char *input_dir ;
extern char *output_incl_dir ;
extern char *output_src_dir ;
extern int output_incl_len ;
extern int output_src_len ;


#endif
