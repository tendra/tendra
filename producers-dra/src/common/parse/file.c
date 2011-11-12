/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#define _POSIX_SOURCE

#include <sys/types.h>
#include <sys/stat.h>

#include "config.h"
#include "system.h"
#include "c_types.h"
#include "loc_ext.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "file.h"
#include "buffer.h"
#include "char.h"
#include "dump.h"
#include "lex.h"
#include "preproc.h"
#include "syntax.h"
#include "token.h"
#include "ustring.h"
#include "xalloc.h"


/*
    INPUT AND OUTPUT FILES

    These are the files from which the lexical routines read their input
    and to which the output routines write.
*/

FILE *input_file = NULL;
FILE *output_file[OUTPUT_FILES] = { NULL, NULL, NULL, NULL, NULL };


/*
    CURRENT FILE NAMES

    The variable input_name is used to hold the name of the current input
    file name.  This remains constant and is not, for example, changed by
    #line directives.  Similarly output_name holds the names of the output
    files.
*/

string input_name = NULL;
string output_name[OUTPUT_FILES] = { NULL, NULL, NULL, NULL, NULL };


/*
    STANDARD FILE NAME

    The macro std_file_name checks whether the file name A is the special
    string "-" used to indicate the standard input or output.  The other
    macros give the corresponding names used in error reports.
*/

#define std_file_name(A)	ustrseq((A), "-")
#define stdin_name		ustrlit("<stdin>")
#define stdout_name		ustrlit("<stdout>")


/*
    INTERNAL FILE BUFFER

    This buffer is used as the internal file buffer which is used to hold
    any preprocessing directives arising from command-line options.  It
    has an associated dummy file and file name.
*/

BUFFER internal_buff = NULL_buff;
static FILE *internal_file = NULL;
static string internal_name = NULL;


/*
    INCLUDE FILE BUFFER

    This buffer is used to build up file names when processing #include
    directives.
*/

BUFFER incl_buff = NULL_buff;


/*
    INPUT FLAGS

    These flags are used to record changes in the current file location.
*/

unsigned long crt_spaces = 0;
unsigned long tab_width = 8;
int crt_line_changed = 0;
int crt_file_changed = 0;
int crt_col_changed = 0;
int crt_file_type = 0;
int bad_crt_loc = 0;


/*
    INPUT BUFFERS

    These variables describe the buffers used in reading the input file.
    Each buffer consists of an array of characters, preceded by space
    for the storage of unread characters, and followed by an overflow
    area for repeated end of file markers.  The position within the
    buffer is indicated by the pointer input_posn.  Other pointers give
    the end of the current buffer and the end of the last buffer.
    Characters beyond the end of the buffer hold char_end.
*/

#define NO_BUFFER		4
#define CHAR_SZ			sizeof(character)
#define BUFF_SZ			((size_t)(BUFSIZ))
#define PENDING_SZ		16
#define OVERFLOW_SZ		16
#define TOTAL_SZ		(PENDING_SZ + BUFF_SZ + OVERFLOW_SZ)

typedef struct {
	string buff;
	string posn;
	string end;
	string eof;
	long bytes;
} INPUT_BUFFER;

static INPUT_BUFFER input_buff[NO_BUFFER] = {
	{ NULL, NULL, NULL, NULL, 0 },
	{ NULL, NULL, NULL, NULL, 0 },
	{ NULL, NULL, NULL, NULL, 0 },
	{ NULL, NULL, NULL, NULL, 0 }
};

string input_start = NULL;
string input_posn = NULL;
string input_end = NULL;
string input_eof = NULL;
string input_crt = NULL;
static long input_bytes = 0;
static int input_special = 0;
static int started_buff = 0;
unsigned long crt_buff_no = 0;


/*
    IS A FILE NAME A FULL PATHNAME?

    This routine checks whether the file name nm represents a full
    pathname.
*/

int
is_full_pathname(string nm)
{
	character c = nm[0];
	character q = (character)drive_sep;
	if (c == char_slash) {
		return 1;
	}
	if (c && q && nm[1] == q) {
		/* Allow for DOS drive letters */
		return is_alpha_char((unsigned long)c);
	}
	return 0;
}


/*
    CONVERT A FILE NAME TO STANDARD FORMAT

    This routine modifies the file name nm to the standard format with
    sensible forward slashes rather backslashes.
*/

string
make_pathname(string nm)
{
	character q = (character)file_sep;
	if (q != char_slash) {
		string s;
		nm = xustrcpy(nm);
		for (s = nm; *s; s++) {
			if (*s == q) {
				*s = char_slash;
			}
		}
	}
	return nm;
}


/*
    NORMALISE A FILE NAME

    This routine normalises the file name s by removing any . or ..
    components.  The result is only used in the printing of error
    messages so it doesn't matter too much if the result isn't quite
    right.
*/

static string
normalise_pathname(string s)
{
	character c;
	string p = s;
	int depth = 0;
	int changed = 0;
	BUFFER *bf = clear_buffer(&incl_buff, NIL(FILE));
	while (c = *(p++), c != 0) {
		if (c == char_slash) {
			if (p[0] == char_dot) {
				if (p[1] == char_slash) {
					/* Have '/./' */
					p++;
					changed = 1;
				} else if (p[1] == char_dot &&
					   p[2] == char_slash) {
					/* Have '/../' */
					string q = bf->posn;
					if (depth > 0) {
						string q0 = bf->start;
						*q = 0;
						q = ustrrchr(q0, char_slash);
						if (q && q != q0) {
							bf->posn = q;
							p += 2;
							changed = 1;
							c = 0;
						}
					}
					if (c) {
						bfputc(bf, (int)c);
					}
					depth--;
				} else {
					bfputc(bf, (int)c);
					depth++;
				}
			} else if (p[0] == char_slash) {
				/* Have '//' */
				changed = 1;
			} else {
				bfputc(bf, (int)c);
				depth++;
			}
		} else {
			bfputc(bf, (int)c);
		}
	}
	bfputc(bf, 0);
	if (changed) {
		s = xustrcpy(bf->start);
	}
	return s;
}


/*
    SET CURRENT LOCATION

    This routine sets the current location from the filename nm.  It returns
    the result of applying make_pathname to nm.
*/

string
set_crt_loc(string nm, int special)
{
	string en;
	unsigned long date;
	if (special) {
		/* Standard input */
		en = ustrlit("");
		date = 0;
	} else {
		/* Simple file */
		STAT_TYPE *fs;
		STAT_TYPE fstr;
		nm = make_pathname(nm);
		en = nm;
		fs = stat_func(strlit(nm), &fstr);
		date = stat_date(fs);
	}
	CREATE_loc(nm, en, nm, NULL, NULL_ptr(LOCATION), date, crt_loc);
	return nm;
}


/*
    OPEN INPUT FILE

    This routine opens the input file, using input_name as the name of the
    file to be opened.  If this is the null string then the standard input
    is used.  The file is opened in binary mode if bin is true.  The routine
    also allocates space for each of the buffers above.  The routine returns
    1 if the file is opened successfully.
*/

int
open_input(int bin)
{
	if (input_file == NULL) {
		string nm = input_name;
		if (nm == NULL || std_file_name(nm)) {
			nm = set_crt_loc(stdin_name, 1);
			input_special = 1;
			if (!bin) {
				input_file = stdin;
			}
		} else {
			const char *mode = (bin ? "rb" : "r");
			nm = set_crt_loc(nm, 0);
			input_special = 0;
			input_file = fopen(strlit(nm), mode);
		}
		input_name = nm;
		if (input_file == NULL) {
			return 0;
		}
		if (!started_buff) {
			unsigned i;
			for (i = 0; i < NO_BUFFER; i++) {
				string buff = xmalloc_nof(character, TOTAL_SZ);
				input_buff[i].buff = buff;
			}
			started_buff = 1;
		}
		crt_file_changed = 1;
		crt_line_changed = 1;
		crt_spaces = 0;
	}
	return 1;
}


/*
    FREE SPACE ALLOCATED FOR INPUT BUFFERS

    This routine frees the memory allocated for the input buffers.
*/

void
term_input(void)
{
	free_buffer(&incl_buff);
	free_buffer(&internal_buff);
	if (started_buff) {
		unsigned i;
		for (i = 0; i < NO_BUFFER; i++) {
			xfree_nof(input_buff[i].buff);
			input_buff[i].buff = NULL;
		}
		started_buff = 0;
	}
	input_start = NULL;
	input_bytes = 0;
	return;
}


/*
    OPEN OUTPUT FILE

    This routine opens the nth output file, using output_name as the name
    of the file to be opened.  If this is the null string then the standard
    output is used.  The file is opened in binary mode if bin is true.  The
    routine returns 1 if the file is opened successfully.
*/

int
open_output(int n, int bin)
{
	if (output_file[n] == NULL) {
		string nm = output_name[n];
		if (nm == NULL || std_file_name(nm)) {
			nm = stdout_name;
			output_name[n] = nm;
			output_file[n] = stdout;
			if (bin) {
				return 0;
			}
		} else {
			const char *mode = (bin ? "wb" : "w");
			nm = make_pathname(nm);
			output_name[n] = nm;
			output_file[n] = fopen(strlit(nm), mode);
			if (output_file[n] == NULL) {
				return 0;
			}
		}
	}
	return 1;
}


/*
    CLOSE INPUT FILE

    This routine closes the input file.
*/

void
close_input(void)
{
	FILE *fin = input_file;
	if (fin && !input_special) {
		if (ferror(fin) || fclose(fin)) {
			char *nm = strlit(input_name);
			error(ERROR_INTERNAL, "Reading error in '%s'", nm);
		}
	}
	input_file = NULL;
	return;
}


/*
    CLOSE OUTPUT FILE

    This routine closes the nth output file.
*/

void
close_output(int n)
{
	FILE *fout = output_file[n];
	if (fout && fout != stdout && fout != stderr) {
		if (ferror(fout) || fclose(fout)) {
			char *nm = strlit(output_name[n]);
			error(ERROR_INTERNAL, "Writing error in '%s'", nm);
		}
	}
	output_file[n] = NULL;
	return;
}


/*
    FILL THE INPUT BUFFER

    This routine fills the current input buffer from the input file, setting
    up the associated buffer pointers.  It returns NULL to indicate that no
    bytes were read.
*/

static string
fill_buffer(void)
{
	size_t i, n;
	size_t m = TOTAL_SZ;
	FILE *f = input_file;
	string p = input_start;

	/* Fill the buffer from the input file */
	if (f == internal_file) {
		n = (size_t)bfread(&internal_buff, p, (gen_size)BUFF_SZ);
		if (n < BUFF_SZ)m = n;
	} else if (f) {
		n = fread((gen_ptr)p, CHAR_SZ, BUFF_SZ, f);
		if (n < BUFF_SZ)m = n;
	} else {
		n = 0;
		m = 0;
	}
	input_posn = p;
	input_end = p + n;
	input_eof = p + m;
	input_crt = p;
	input_bytes += (long)n;

	/* Fill the overflow area with char_end's */
	for (i = n; i < n + OVERFLOW_SZ; i++) {
		p[i] = char_end;
	}
	if (n == 0) {
		p = NULL;
	}
	return p;
}


/*
    INITIALISE BUFFER

    This routine initialises buffer number i and makes it into the current
    buffer.  It returns NULL to indicate an empty file.
*/

string
init_buffer(unsigned long i)
{
	crt_buff_no = i;
	input_start = input_buff[i].buff + PENDING_SZ;
	input_bytes = 0;
	return fill_buffer();
}


/*
    RESUME BUFFER

    This routine makes buffer number i into the current buffer by restoring
    the main values from those stored in the buffer.
*/

static void
resume_buffer(unsigned long i)
{
	INPUT_BUFFER *p = input_buff + i;
	input_start = p->buff + PENDING_SZ;
	input_posn = p->posn;
	input_end = p->end;
	input_eof = p->eof;
	input_crt = p->posn;
	input_bytes = p->bytes;
	return;
}


/*
    FIND CURRENT FILE POSITION

    This routine finds the current file position and updates the pointers
    in buffer i (which should be the current buffer number).
*/

long
tell_buffer(unsigned long i)
{
	long bytes_left;
	INPUT_BUFFER *p = input_buff + i;
	p->posn = input_posn;
	p->end = input_end;
	p->eof = input_eof;
	p->bytes = input_bytes;
	bytes_left = (long)(input_end - input_posn);
	if (bytes_left < 0) {
		bytes_left = 0;
	}
	return input_bytes - bytes_left;
}


/*
    SET CURRENT FILE POSITION

    This routine sets the current file position to n and the current buffer
    to number i.  started is false if the file has just been opened.
*/

void
seek_buffer(unsigned long i, long n, int started)
{
	int s;
	FILE *f = input_file;
	if (f == NULL) {
		return;
	}
	if (f == internal_file) {
		if (started) {
			/* Reset position to start of buffer */
			internal_buff.posn = internal_buff.start;
			started = 0;
		}
		s = 0;
	} else {
		s = file_seek(f, n);
	}
	if (s == 0) {
		/* Perform seek by hand */
		string p;
		if (started) {
			/* Rewind to start of file */
			IGNORE file_seek(f, (long)0);
		}
		p = init_buffer(i);
		while (input_bytes < n) {
			if (p == NULL) {
				char *nm = strlit(input_name);
				const char *msg = "Internal seek error in '%s'";
				error(ERROR_INTERNAL, msg, nm);
				return;
			}
			p = fill_buffer();
		}
		input_posn = input_end - (input_bytes - n);
		input_crt = input_posn;
	} else {
		if (s == -1) {
			char *nm = strlit(input_name);
			const char *msg = "Internal seek error in '%s'";
			error(ERROR_INTERNAL, msg, nm);
		}
		input_start = input_buff[i].buff + PENDING_SZ;
		input_bytes = n;
		IGNORE fill_buffer();
	}
	return;
}


/*
    UPDATE THE CURRENT COLUMN POSITION

    The current column position is only updated at convenient junctures.
    The variable input_crt is used to keep track of the last such location.
*/

void
update_column(void)
{
	string p = input_posn;
	if (p) {
		unsigned long n = (unsigned long)(p - input_crt);
		if (n) {
			crt_loc.column += n;
			input_crt = p;
		}
	}
	return;
}


/*
    REFILL THE INPUT BUFFER

    This routine refills the input buffer, returning the first character.
    It is called whenever the next character in the buffer is char_end.
    It is possible that the character is really char_end, in which case
    this is returned.  Otherwise the buffer is refilled.  Note that in order
    for unread_char to work correctly with char_eof, ( char_eof & 0xff )
    must equal char_end.
*/

int
refill_char(void)
{
	int c;
	update_column();
	do {
		string p = input_posn;
		if (p <= input_end) {
			return char_end;
		}
		if (p > input_eof) {
			return char_eof;
		}
		crt_loc.column += (unsigned long)(p - input_crt);
		IGNORE fill_buffer();
		c = next_char();
	} while (c == char_end);
	input_crt = input_posn;
	return c;
}


/*
    INCLUDE FILE SEARCH PATH

    The variable dir_path gives the list of directories searched for
    #include'd files.  The variable crt_dir_path is set after each #include
    directive to the position in the path after that at which the included
    file was found.
*/

INCL_DIR *dir_path = NULL;
static INCL_DIR *crt_dir_path = NULL;
static INCL_DIR *crt_found_path = NULL;


/*
    FIND A NAMED DIRECTORY

    This routine looks up a named directory called nm.  It returns the
    corresponding directory structure, or the null pointer if nm is not
    defined.
*/

static INCL_DIR *
find_directory(string nm)
{
	INCL_DIR *p = dir_path;
	while (p != NULL) {
		string s = p->name;
		if (s && ustreq(s, nm)) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}


/*
    ADD A DIRECTORY TO THE SEARCH PATH

    This routine adds the directory dir with associated name nm to the
    include file search path.
*/

void
add_directory(string dir, string nm)
{
	INCL_DIR *p = dir_path;
	INCL_DIR *q = xmalloc_one(INCL_DIR);
	if (nm && find_directory(nm)) {
		char *s = strlit(nm);
		error(ERROR_WARNING, "Directory '%s' already defined", s);
		nm = NULL;
	}
	q->path = make_pathname(dir);
	q->name = nm;
	q->mode = NULL;
	q->no = LINK_NONE;
	q->next = NULL;
	if (p == NULL) {
		dir_path = q;
		crt_dir_path = q;
	} else {
		while (p->next) {
			p = p->next;
		}
		p->next = q;
	}
	return;
}


/*
    SET A DIRECTORY COMPILATION MODE

    This routine sets the compilation mode for the directory named nm
    to be p.
*/

void
directory_mode(string nm, OPTIONS *p)
{
	INCL_DIR *q = find_directory(nm);
	if (q) {
		if (q->mode) {
			report(preproc_loc, ERR_pragma_dir_mode(nm));
		}
		if (p) {
			q->mode = p;
		}
	} else {
		report(preproc_loc, ERR_pragma_dir_undef(nm));
	}
	return;
}


/*
    LISTS OF START-UP AND END-UP FILES

    These variables give the lists of start-up and end-up files.  These
    are equivalent to #include "file" directives at respectively the start
    and the end of the main include file.
*/

LIST(string)startup_files = NULL_list(string);
LIST(string)endup_files = NULL_list(string);


/*
    SET UP INTERNAL START-UP FILE

    This routine sets up the built-in internal start-up file.
*/

void
builtin_startup(void)
{
	BUFFER *bf = &internal_buff;
	internal_name = DEREF_string(posn_file(crt_loc.posn));
	internal_file = xmalloc_one(FILE *);
	if (bf->posn != bf->start) {
		/* Add to list of start-up files if necessary */
		CONS_string(internal_name, startup_files, startup_files);
		bf->end = bf->posn;
		bf->posn = bf->start;
	}
	return;
}


/*
    OPEN NEXT START-UP FILE

    This routine opens the next start-up file.  It continues trying until
    a start-up file is successfully opened or there are no start-up files
    left.
*/

void
open_startup(void)
{
	LIST(string)p = startup_files;
	while (!IS_NULL_list(p)) {
		string fn = DEREF_string(HEAD_list(p));
		p = TAIL_list(p);
		startup_files = p;
		preproc_loc = crt_loc;
		crt_file_type = 1;
		if (start_include(fn, char_quote, 2, 0)) {
			return;
		}
	}
	crt_file_type = 0;
	return;
}


/*
    LIST OF INCLUDED FILES

    This list is used to record all the files included plus the position
    of the current file within this list.
*/

typedef struct incl_file_tag {
	string name;
	int imported;
	HASHID macro;
	unsigned test;
	int state;
	PTR(LOCATION)from;
	STAT_TYPE *data;
	STAT_TYPE data_ref;
	struct incl_file_tag *next;
} INCL_FILE;

static INCL_FILE *included_files = NULL;
static INCL_FILE *crt_included_file = NULL;


/*
    TABLE OF INCLUSIONS

    This table is used to hold the file positions for all the currently
    active #include directives.  Note that this is done as a finite
    (but hopefully sufficiently large) array to detect recursive
    inclusions.
*/

typedef struct {
	string name;
	FILE *fileptr;
	long offset;
	int special;
	int startup;
	int interface;
	OPTIONS *mode;
	INCL_DIR *path;
	INCL_DIR *found;
	INCL_FILE *incl;
} INCL_BUFF;

#define MAX_INCL_DEPTH		256

static INCL_BUFF position_array[MAX_INCL_DEPTH];
static INCL_BUFF *position = position_array;
static unsigned long position_size = MAX_INCL_DEPTH;


/*
    SIMPLE INCLUSION DEPTH

    There are two approaches to suspending the current file - either
    leaving the file open or closing it and reopening it later.  The
    latter is more efficient, but is limited by the maximum number of
    files which can be opened at one time (FOPEN_MAX).  Therefore this
    strategy is only used for this number of files.  Note that FOPEN_MAX
    is at least 8 (including the 3 standard files).
*/

#define LAST_BUFFER_NO		((unsigned long)(NO_BUFFER - 1))
#define SIMPLE_INCL_DEPTH	LAST_BUFFER_NO


/*
    SET MAXIMUM INCLUDE DEPTH

    This routine sets the maximum include file depth to n.
*/

void
set_incl_depth(unsigned long n)
{
	if (n > 10000) {
		n = 10000;
	}
	if (n > position_size) {
		/* Allocate more space if necessary */
		unsigned long i, m;
		INCL_BUFF *p = xmalloc_nof(INCL_BUFF, n);
		INCL_BUFF *q = position;
		m = crt_option_value(OPT_VAL_include_depth);
		for (i = 0; i < m; i++) {
			p[i] = q[i];
		}
		position_size = n;
		position = p;
		if (q != position_array) {
			xfree_nof(q);
		}
	}
	option_value(OPT_VAL_include_depth) = n;
	return;
}


/*
    CHECK WHETHER A FILE HAS ALREADY BEEN INCLUDED

    This routine checks whether the file with pathname nm and file
    statistics fs has already been included and does not need to be
    included again.  It also sets crt_included_file.  st is as in
    start_include.
*/

int
already_included(string nm, STAT_TYPE *fs, int st)
{
	INCL_FILE *p = included_files;
	while (p != NULL) {
		int ok;
		if (ustreq(nm, p->name) && st != 4) {
			/* Check file names */
			ok = 1;
		} else {
			/* Check file statistics */
			ok = stat_equal(fs, p->data);
		}
		if (ok) {
			/* Check matching file */
			if (st == 4) {
				/* Simple enquiry */
				return 1;
			}
			crt_included_file = p;
			if (st == 1) {
				/* Imported file */
				if (p->imported == 1) {
					return 1;
				}
				p->imported = 1;
			}
			if (p->state == 2) {
				/* Check protection macro */
				unsigned def = check_macro(p->macro, 0);
				def &= PP_COND_MASK;
				if (def == p->test) {
					return 1;
				}
			}
			return 0;
		}
		p = p->next;
	}

	/* Create new imported file structure */
	p = xmalloc_one(INCL_FILE);
	if (st != 4) {
		crt_included_file = p;
	}
	p->name = nm;
	p->imported = st;
	p->macro = NULL_hashid;
	p->state = 0;
	p->test = PP_TRUE;
	p->from = NULL_ptr(LOCATION);
	if (fs) {
		/* File system information available */
		p->data = & (p->data_ref);
		p->data_ref = *fs;
	} else {
		p->data = NULL;
	}
	p->next = included_files;
	included_files = p;
	return 0;
}


/*
    CHECK A FILE PROTECTION MACRO

    This routine checks whether the given macro identifier is a file
    protection macro for the current file, that is to say, whether the
    file has the form:

		#ifndef macro
		....
		#endif

    prev gives the previous preprocessing directive and dir gives the
    current preprocessing directive.
*/

void
protection_macro(HASHID macro, int prev, int dir)
{
	INCL_FILE *incl = crt_included_file;
	if (incl) {
		if (prev == lex_included) {
			if (incl->state == 0) {
				if (dir == lex_ifndef) {
					/* Have '#ifndef macro' at start of
					 * file */
					incl->macro = macro;
					incl->test = PP_TRUE;
					incl->state = 1;
					return;
				}
				if (dir == lex_ifdef) {
					/* Have '#ifdef macro' at start of
					 * file */
					incl->macro = macro;
					incl->test = PP_FALSE;
					incl->state = 1;
					return;
				}
				if (dir == lex_eof) {
					/* Start and end of file coincide */
					incl->macro = NULL_hashid;
					incl->test = PP_TRUE;
					incl->state = 2;
					return;
				}
			}
		}
		if (prev == lex_end_condition) {
			if (incl->state == 1) {
				if (dir == lex_eof) {
					/* Have '#endif' at end of file */
					incl->state = 2;
					return;
				}
			}
		}
		incl->state = 0;
	}
	return;
}


/*
    CREATE A FILE NAME

    This routine forms a composite file name consisting of a directory
    component d and a file component f.  The up argument is true if the
    existing file component is to be removed from d.
*/

static string
add_pathname(string d, string f, int up)
{
	if (d) {
		BUFFER *bf = clear_buffer(&incl_buff, NIL(FILE));
		bfputs(bf, d);
		if (up) {
			/* Remove file component */
			string s = ustrrchr(bf->start, char_slash);
			if (s == NULL) {
				return f;
			}
			bf->posn = s;
		}
		bfputc(bf, char_slash);
		bfputs(bf, f);
		return bf->start;
	}
	return f;
}


/*
    FIND AN INCLUDE FILE

    This routine searches for, and opens, an included file named nm.  The
    argument q equals '"' or '>', depending on the form of the #include
    directive.  The argument st is 0 for normal inclusions, 1 for imported
    inclusions, 2 for start-up files and 3 for end-up files.  A value of
    4 is used for checking inclusion.  next is true if the search is to
    restart at the current position in the directory path.  The routine
    returns 1 to indicate that the file was opened successfully.
*/

int
start_include(string nm, int q, int st, int next)
{
	FILE *g;
	FILE *f = NULL;
	int special = 0;
	string file = nm;
	string dir = NULL;
	unsigned long c, m;
	string rfile = NULL;
	OPTIONS *mode = NULL;
	PTR(LOCATION)from;
	unsigned long date = 0;
	INCL_DIR *found = NULL;
	INCL_DIR *path = dir_path;
	INCL_FILE *incl = crt_included_file;

	/* Check for empty file name */
	if (nm[0] == 0) {
		report(preproc_loc, ERR_cpp_include_empty());
		return 0;
	}

	/* Search for included file */
	if (nm == internal_name) {
		/* Allow for command-line options */
		rfile = ustrlit("");
		f = internal_file;
		special = 1;

	} else if (is_full_pathname(nm)) {
		/* Allow for full file names */
		if (st < 2) {
			report(preproc_loc, ERR_cpp_include_full(nm));
		}
		f = fopen(strlit(file), "r");

	} else if (std_file_name(nm)) {
		/* Allow for standard input (extension) */
		file = stdin_name;
		rfile = ustrlit("");
		f = stdin;
		special = 1;

	} else {
		/* Check quoted include directives */
		if (q == char_quote) {
			file = add_pathname(input_name, nm, 1);
			f = fopen(strlit(file), "r");
			found = crt_found_path;
		}

		/* Search directory path */
		if (f == NULL) {
			if (next) {
				/* Start search at current position */
				path = crt_dir_path;
			}
			while (f == NULL && path != NULL) {
				dir = path->path;
				file = add_pathname(dir, nm, 0);
				f = fopen(strlit(file), "r");
				found = path;
				mode = path->mode;
				path = path->next;
			}
		} else {
			path = crt_dir_path;
			dir = DEREF_string(posn_dir(crt_loc.posn));
		}
	}
	if (st == 4) {
		/* Just testing ... */
		if (f == NULL) {
			return 0;
		}
		if (!special) {
			fclose_v(f);
		}
		return 1;
	}

	/* Report unfound files */
	if (f == NULL) {
		report(preproc_loc, ERR_cpp_include_unknown(nm));
		return 0;
	}

	/* Check for multiple inclusions */
	file = xustrcpy(file);
	if (special) {
		crt_included_file = NULL;
	} else {
		STAT_TYPE fstr;
		STAT_TYPE *fs = stat_func(strlit(file), &fstr);
		if (already_included(file, fs, st)) {
			/* Only read file if necessary */
			from = crt_included_file->from;
			report(preproc_loc, ERR_cpp_include_dup(nm, from));
			crt_included_file = incl;
			fclose_v(f);
			return 0;
		}
		date = stat_date(fs);
	}

	/* Store position of #include directive */
	c = crt_option_value(OPT_VAL_include_depth);
	if (!incr_value(OPT_VAL_include_depth)) {
		/* Include depth too great */
		crt_option_value(OPT_VAL_include_depth) = c;
		crt_included_file = incl;
		return 0;
	}
	g = input_file;
	position[c].name = input_name;
	position[c].special = input_special;
	position[c].startup = st;
	position[c].interface = crt_interface;
	position[c].mode = mode;
	position[c].path = crt_dir_path;
	position[c].found = crt_found_path;
	position[c].incl = incl;
	if (c < SIMPLE_INCL_DEPTH || input_special) {
		/* Store open file */
		m = c + 1;
		position[c].fileptr = g;
		position[c].offset = tell_buffer(c);
	} else {
		/* Store position in closed file */
		m = LAST_BUFFER_NO;
		position[c].fileptr = NULL;
		position[c].offset = tell_buffer(m);
		if (ferror(g) || fclose(g)) {
			char *gnm = strlit(input_name);
			error(ERROR_INTERNAL, "Reading error in '%s'", gnm);
		}
	}
	crt_found_path = found;
	crt_dir_path = path;

	/* Set up new file */
	input_name = file;
	input_file = f;
	input_special = special;
	nm = (file + ustrlen(file)) - ustrlen(nm);
	if (rfile == NULL) {
		rfile = file;
		file = normalise_pathname(file);
	}
	if (option(OPT_include_verbose)) {
		report(preproc_loc, ERR_cpp_include_open(file));
	}
	crt_loc.line--;
	crt_loc.column = 0;
	input_crt = input_posn;
	if (do_header) {
		dump_include(&crt_loc, nm, st, q);
	}
	from = MAKE_ptr(SIZE_loc);
	COPY_loc(from, crt_loc);
	CREATE_loc(file, rfile, nm, dir, from, date, crt_loc);
	if (crt_included_file) {
		/* Set inclusion position */
		crt_included_file->from = from;
	}
	if (do_header) {
		dump_start(&crt_loc, found);
	}
	IGNORE init_buffer(m);
	start_preproc_if ();
	if (mode) {
		/* Begin new checking scope if necessary */
		begin_option(NULL_id);
		use_mode(mode, ERROR_SERIOUS);
	}
	crt_file_changed = 2;
	crt_line_changed = 1;
	crt_spaces = 0;
	return 1;
}


/*
    END AN INCLUDE FILE

    This routine is called at the end of each source file.  prev is as
    in protection_macro.  The routine returns 1 if the end of file causes
    a reversion to a previous file via a #include directive, and 0 if this
    is the main source file.  Note that start-up and end-up files are
    spotted during this process (except the first start-up file which is
    dealt with in process_file).  Start-up files are at depth 1, whereas
    end-up files are at depth 0.
*/

int
end_include(int prev)
{
	unsigned long c;
	PTR(LOCATION)loc;
	FILE *f = input_file;
	string nm = input_name;

	/* Check for protection macros */
	if (!clear_preproc_if ())prev = lex_end_condition;
	protection_macro(NULL_hashid, prev, lex_eof);

	/* Tidy up the current file */
	if (f != NULL) {
		if (input_special) {
			if (f == internal_file) {
				free_buffer(&internal_buff);
			}
		} else {
			if (ferror(f) || fclose(f)) {
				char *fnm = strlit(nm);
				error(ERROR_INTERNAL, "Reading error in '%s'",
				      fnm);
			}
		}
		input_file = NULL;
		if (do_header)dump_end(&crt_loc);
	}

	/* Check for previous file */
	c = crt_option_value(OPT_VAL_include_depth);
	if (c == 0) {
		/* End of main file - deal with end-up files */
		LIST(string)p = endup_files;
		while (!IS_NULL_list(p)) {
			string fn = DEREF_string(HEAD_list(p));
			p = TAIL_list(p);
			endup_files = p;
			preproc_loc = crt_loc;
			crt_file_type = 1;
			if (start_include(fn, char_quote, 3, 0)) {
				return 1;
			}
		}
		crt_file_type = 0;
		return 0;
	}
	decr_value(OPT_VAL_include_depth);
	c--;

	/* End checking scope if necessary */
	if (position[c].mode)end_option(0);

	/* Restore previous file position (don't destroy old value) */
	loc = DEREF_ptr(posn_from(crt_loc.posn));
	DEREF_loc(loc, crt_loc);
	crt_file_changed = 2;
	crt_line_changed = 1;
	crt_spaces = 0;

	/* Reopen the previous buffer */
	input_name = position[c].name;
	input_file = position[c].fileptr;
	input_special = position[c].special;
	crt_dir_path = position[c].path;
	crt_found_path = position[c].found;
	crt_included_file = position[c].incl;
	crt_interface = position[c].interface;
	if (input_file == NULL) {
		/* Reopen old file */
		char *str = strlit(input_name);
		if (str) {
			input_file = fopen(str, "r");
			if (input_file == NULL) {
				const char *msg = "Internal file error in '%s'";
				error(ERROR_INTERNAL, msg, str);
				crt_loc.line++;
				crt_loc.column = 0;
				input_crt = input_posn;
				return end_include(lex_ignore_token);
			}
			seek_buffer(LAST_BUFFER_NO, position[c].offset, 0);
		}
	} else {
		/* Resume old file position */
		resume_buffer(c);
	}
	if (option(OPT_include_verbose)) {
		LOCATION ploc;
		int st = position[c].startup;
		ploc = crt_loc;
		if (st >= 2) {
			ploc.line++;
		}
		report(ploc, ERR_cpp_include_close(nm));
	}
	if (do_header) {
		dump_include(&crt_loc, NULL_string, 4, 0);
	}
	crt_loc.line++;
	crt_loc.column = 0;
	input_crt = input_posn;

	/* Could be the end of a start-up file - try the next one */
	if (c == 0) {
		open_startup();
	}
	return 1;
}
