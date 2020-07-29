/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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

extern int refill_char(void);
extern string init_buffer(unsigned long);
extern string make_pathname(string);
extern int is_full_pathname(string);
extern string set_crt_loc(string, int);
extern int start_include(string, int, int, int);
extern int end_include(int);
extern void open_startup(void);
extern int open_input(int);
extern int open_output(int, int);
extern void close_input(void);
extern void close_output(int);
extern void set_incl_depth(unsigned long);
extern void add_directory(string, string);
extern void directory_mode(string, OPTIONS *);
extern void builtin_startup(void);
extern void term_input(void);
extern long tell_buffer(unsigned long);
extern void seek_buffer(unsigned long, long, int);
extern void protection_macro(HASHID, int, int);
extern void update_column(void);

#ifdef SYSTEM_INCLUDED
extern int already_included(string, STAT_TYPE *, int);
#endif


/*
    TYPE REPRESENTING AN INCLUSION DIRECTORY

    This type is used to represent a directory which is searched during
    file inclusion.
*/

typedef struct incl_dir_tag {
	string path;
	string name;
	OPTIONS *mode;
	ulong no;
	struct incl_dir_tag *next;
} INCL_DIR;


/*
    FILE READING VARIABLES

    These variables relate to the file reading and writing routines.
*/

extern int crt_line_changed;
extern int crt_file_changed;
extern int crt_col_changed;
extern int crt_file_type;
extern int bad_crt_loc;
extern unsigned long crt_spaces;
extern unsigned long tab_width;
extern BUFFER internal_buff;
extern BUFFER incl_buff;
extern LIST(string)startup_files, endup_files;
extern FILE *input_file, *output_file[];
extern string input_name, output_name[];
extern unsigned long crt_buff_no;
extern string input_start, input_end;
extern string input_posn, input_eof;
extern string input_crt;
extern INCL_DIR *dir_path;


/*
    CHARACTER READING AND UNREADING MACROS

    The macro next_char reads the next character from the input buffer.
    It needs to be checked against char_end to spot the end of the buffer.
    The macro unread_char unreads the character A by inserting it back
    into the input buffer.
*/

#define next_char()	((int)(*(input_posn++)))
#define unread_char(A)	(*(--input_posn) = (character)(A))


/*
    OUTPUT FILE NUMBERS

    These values are used to represent the various output files.
*/

enum {
	OUTPUT_TDF,
	OUTPUT_PREPROC,
	OUTPUT_SPEC,
	OUTPUT_DUMP,
	OUTPUT_ERROR,
	OUTPUT_FILES
};


#endif
