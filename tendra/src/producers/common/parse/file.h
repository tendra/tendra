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


#ifndef FILE_INCLUDED
#define FILE_INCLUDED


/*
    FILE MANIPULATION DECLARATIONS

    The routines in this module are concerned with the low level file
    reading and manipulation, including the processing of #include
    directives, start-up and end-up files.  The routine next_char is the
    lowest level file reading routine, which returns the next character
    in the input file.
*/

extern int refill_char PROTO_S ( ( void ) ) ;
extern string init_buffer PROTO_S ( ( unsigned long ) ) ;
extern string make_pathname PROTO_S ( ( string ) ) ;
extern int is_full_pathname PROTO_S ( ( string ) ) ;
extern string set_crt_loc PROTO_S ( ( string, int ) ) ;
extern int start_include PROTO_S ( ( string, int, int, int ) ) ;
extern int end_include PROTO_S ( ( int ) ) ;
extern void open_startup PROTO_S ( ( void ) ) ;
extern int open_input PROTO_S ( ( int ) ) ;
extern int open_output PROTO_S ( ( int, int ) ) ;
extern void close_input PROTO_S ( ( void ) ) ;
extern void close_output PROTO_S ( ( int ) ) ;
extern void set_incl_depth PROTO_S ( ( unsigned long ) ) ;
extern void add_directory PROTO_S ( ( string, string ) ) ;
extern void directory_mode PROTO_S ( ( string, OPTIONS * ) ) ;
extern void builtin_startup PROTO_S ( ( void ) ) ;
extern void term_input PROTO_S ( ( void ) ) ;
extern long tell_buffer PROTO_S ( ( unsigned long ) ) ;
extern void seek_buffer PROTO_S ( ( unsigned long, long, int ) ) ;
extern void protection_macro PROTO_S ( ( HASHID, int, int ) ) ;
extern void update_column PROTO_S ( ( void ) ) ;

#ifdef SYSTEM_INCLUDED
extern int already_included PROTO_S ( ( string, STAT_TYPE *, int ) ) ;
#endif


/*
    TYPE REPRESENTING AN INCLUSION DIRECTORY

    This type is used to represent a directory which is searched during
    file inclusion.
*/

typedef struct incl_dir_tag {
    string path ;
    string name ;
    OPTIONS *mode ;
    ulong no ;
    struct incl_dir_tag *next ;
} INCL_DIR ;


/*
    FILE READING VARIABLES

    These variables relate to the file reading and writing routines.
*/

extern int crt_line_changed ;
extern int crt_file_changed ;
extern int crt_col_changed ;
extern int crt_file_type ;
extern int bad_crt_loc ;
extern unsigned long crt_spaces ;
extern unsigned long tab_width ;
extern BUFFER internal_buff ;
extern BUFFER incl_buff ;
extern LIST ( string ) startup_files, endup_files ;
extern FILE *input_file, *output_file [] ;
extern string input_name, output_name [] ;
extern unsigned long crt_buff_no ;
extern string input_start, input_end ;
extern string input_posn, input_eof ;
extern string input_crt ;
extern INCL_DIR *dir_path ;


/*
    CHARACTER READING AND UNREADING MACROS

    The macro next_char reads the next character from the input buffer.
    It needs to be checked against char_end to spot the end of the buffer.
    The macro unread_char unreads the character A by inserting it back
    into the input buffer.
*/

#define next_char()		( ( int ) ( *( input_posn++ ) ) )
#define unread_char( A )	( *( --input_posn ) = ( character ) ( A ) )


/*
    OUTPUT FILE NUMBERS

    These values are used to represent the various output files.
*/

#define OUTPUT_TDF		0
#define OUTPUT_PREPROC		1
#define OUTPUT_SPEC		2
#define OUTPUT_DUMP		3
#define OUTPUT_ERROR		4
#define OUTPUT_FILES		5


#endif
