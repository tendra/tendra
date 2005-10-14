/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#ifndef FILE_INCLUDED
#define FILE_INCLUDED


/*
 *    FILE MANIPULATION DECLARATIONS
 *
 *    The routines in this module are concerned with the low level file
 *    reading and manipulation, including the processing of #include
 *    directives, start-up and end-up files.  The routine next_char is the
 *    lowest level file reading routine, which returns the next character
 *    in the input file.
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
 *    CONSTANTS FOR VARIOUS INCLUDE FUNCTIONS
 *
 *    The order is important, don't change it at will.
 */

enum {
    INCLUDE_NORMAL,		/* normal inclusion */
    INCLUDE_IMPORT,		/* imported inclusion */
    INCLUDE_STARTUP,		/* inclusion of start-up files */
    INCLUDE_ENDUP,		/* inclusion of end-up files */
    INCLUDE_CHECK		/* checking inclusion */
};


/*
 *    TYPE REPRESENTING AN INCLUSION DIRECTORY
 *
 *    This type is used to represent a directory which is searched during
 *    file inclusion.
 */

typedef struct incl_dir_tag {
	string path;
	string name;
	OPTIONS *mode;
	ulong no;
	struct incl_dir_tag *next;
} INCL_DIR;


/*
 *    FILE READING VARIABLES
 *
 *    These variables relate to the file reading and writing routines.
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
extern LIST (string) startup_files, endup_files;
extern FILE *input_file, *output_file [];
extern string input_name, output_name [];
extern unsigned long crt_buff_no;
extern string input_start, input_end;
extern string input_posn, input_eof;
extern string input_crt;
extern INCL_DIR *dir_path;


/*
 *    CHARACTER READING AND UNREADING MACROS
 *
 *    The macro next_char reads the next character from the input buffer.
 *    It needs to be checked against char_end to spot the end of the buffer.
 *    The macro unread_char unreads the character A by inserting it back
 *    into the input buffer.
 */

#define next_char()		((int) (*(input_posn++)))
#define unread_char(A)	(*(--input_posn) = (character) (A))


/*
 *    OUTPUT FILE NUMBERS
 *
 *    These values are used to represent the various output files.
 */

#define OUTPUT_TDF		0
#define OUTPUT_PREPROC		1
#define OUTPUT_SPEC		2
#define OUTPUT_DUMP		3
#define OUTPUT_ERROR		4
#define OUTPUT_FILES		5


#endif
