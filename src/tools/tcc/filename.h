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


#ifndef FILENAME_INCLUDED
#define FILENAME_INCLUDED


/*
    TYPE REPRESENTING A FILE NAME

    The filename structure is used to represent a tcc input or output
    file.  It has an associated name (the full pathname), a basename
    (with the directory and file suffix removed), a file type (see
    below) and a file storage type (see below).  filenames are formed
    into lists using the next field.  The may also be associated into
    groups which are passed around as if they were a single file using
    the aux field.
*/

typedef struct filename_t {
    char *name ;
    char *bname ;
    int uniq ;
    int type ;
    int storage ;
    boolean final ;
    struct filename_t *aux ;
    struct filename_t *next ;
} filename ;

#define no_filename		( ( filename * ) null )


/*
    FILE TYPES

    Each of the file types handled by tcc is allocated an identifier.
    This is Table 1, if it is changed then it may have knock-on effects
    in several places in the program.  Hopefully I have marked them all
    by suitable comments.
*/

#define C_SOURCE		0
#define PREPROC_C		1
#define CPP_SOURCE		2
#define PREPROC_CPP		3
#define INDEP_TDF		4
#define DEP_TDF			5
#define AS_SOURCE		6
#define BINARY_OBJ		7
#define EXECUTABLE		8
#define PRETTY_TDF		9
#define PL_TDF			10
#define TDF_ARCHIVE		11
#define MIPS_G_FILE		12
#define MIPS_T_FILE		13
#define C_SPEC			14
#define CPP_SPEC		15
#define STARTUP_FILE		16
#define UNKNOWN_TYPE		17
#define ALL_TYPES		31
#define DEFAULT_TYPE		BINARY_OBJ


/*
    FILE STORAGE TYPES

    The files handled by tcc may be of three basic types, input files,
    permanent output files and temporary output files.  The first type
    may also contain input options which are treated like input files
    (for example, system libraries).  The second type includes the
    preserved intermediate files.  In fact PRESERVED_FILE is only used
    as the input to make_filename.
*/

#define INPUT_FILE		0
#define INPUT_OPTION		1
#define OUTPUT_FILE		2
#define PRESERVED_FILE		3
#define TEMP_FILE		4


/*
    SUFFIX OVERRIDES

    This table contains the strings which are used when the suffix
    overrides are set from the command line.  Initially, it is empty.
*/

extern char *suffixes [] ;


/*
    FILE STORAGE LOCATIONS

    Output files may be stored either in the temporary directory or
    the work directory.
*/

extern char *tempdir ;
extern char *workdir ;


/*
    INPUT FILE VARIABLES

    These variables are used to pass information to and from find_filename.
*/

extern boolean case_insensitive ;
extern boolean option_next ;
extern int no_input_files ;


/*
    PROCEDURE DECLARATIONS

    These routines are concerned with creating and manipulating filenames.
*/

extern char *find_basename PROTO_S ( ( char * ) ) ;
extern char *find_fullname PROTO_S ( ( char * ) ) ;
extern filename *add_filename PROTO_S ( ( filename *, filename * ) ) ;
extern filename *find_filename PROTO_S ( ( char *, int ) ) ;
extern filename *make_filename PROTO_S ( ( filename *, int, int ) ) ;
extern int find_type PROTO_S ( ( int, int ) ) ;
extern int where PROTO_S ( ( int ) ) ;


#endif
