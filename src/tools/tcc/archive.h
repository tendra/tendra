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


#ifndef ARCHIVE_INCLUDED
#define ARCHIVE_INCLUDED


/*
    ARCHIVE OPTION MARKER

    This is used to indicate the end of the archive files, and the
    beginning of the archive options in build_archive.
*/

#define ARCHIVE_OPTION_START	"+"


/*
    ARCHIVE OPTIONS

    These flags control the inclusion of certain information in the
    archives.
*/

extern int archive_type ;
extern void process_archive_opt PROTO_S ( ( void ) ) ;


/*
    PROCEDURE DECLARATIONS

    These routines include the general utilities for file manipulation
    plus the procedures for building and splitting TDF archives.
*/

extern int cat_file PROTO_S ( ( char * ) ) ;
extern int make_dir PROTO_S ( ( char * ) ) ;
extern int move_file PROTO_S ( ( char *, char * ) ) ;
extern int remove_file PROTO_S ( ( char * ) ) ;
extern int touch_file PROTO_S ( ( char *, char * ) ) ;
extern boolean is_archive PROTO_S ( ( char * ) ) ;
extern int split_archive PROTO_S ( ( char *, filename ** ) ) ;
extern int build_archive PROTO_S ( ( char *, char ** ) ) ;
extern long file_size PROTO_S ( ( char * ) ) ;


#endif
