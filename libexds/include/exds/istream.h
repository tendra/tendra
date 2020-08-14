/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * istream.h - Input stream handling.
 *
 * This file specifies the interface to the input stream facility.
 *
 *
 * Exception:	XX_istream_read_error
 *
 * This exception is raised if a read attempt fails.  The data thrown is a
 * copy of the name of the file that the read error occured on.  The copy
 * should be deallocated when finished with.
 */

#ifndef H_ISTREAM
#define H_ISTREAM

#include <stdio.h>

#include <exds/common.h>
#include <exds/exception.h>


/*
 * This is the input stream type.
 * TODO is this private?
 */
typedef struct IStreamT IStreamT;
struct IStreamT {
	FILE *file;
	char *buffer;
	char *current;
	char *end;
	char *limit;
	unsigned line;
	const char *name;
	bool read_last;
};

/*
 * This is the return type of the istream_read_escaped_char function.  The
 * constants represent the results: a character was read, no character was
 * read, and a syntax error occured respectively.
 */
typedef enum {
	ISTREAM_STAT_READ_CHAR,
	ISTREAM_STAT_NO_CHAR,
	ISTREAM_STAT_SYNTAX_ERROR
} IStreamStatusT;


extern ExceptionT *XX_istream_read_error;

/*
 * This value is a pointer to an input stream object that will read from the
 * standard input.  The istream_setup function must be called before this
 * constant is used.
 */
extern IStreamT *const istream_input;

/*
 * This function initialises the input stream facility.  It should be called
 * before any other istream manipulation function.
 */
void
istream_setup(void);

/*
 * This function initialises the specified istream not to read from any file.
 */
void
istream_init(IStreamT *);

/*
 * Exceptions: XX_dalloc_no_memory, XX_istream_read_error
 *
 * This function initialises the specified istream to read from the file with
 * the specified name.  The name should not be modified or deallocated until
 * the istream has been closed.  If the file cannot be opened, the function
 * returns false. If the file is opened successfully, the function returns
 * true.
 */
bool
istream_open(IStreamT *, const char *);

/*
 * This function assigns the from istream to the to istream.  The from istream
 * should not be used again.
 */
void
istream_assign(IStreamT *, IStreamT *);

/*
 * This function returns true if the specified istream is reading from a file,
 * and false otherwise.
 */
bool
istream_is_open(IStreamT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
 *
 * This function reads the next character from the specified istream (and
 * advances the character pointer).  If a character is read then the character
 * is assigned to the reference argument, and the function returns true.  If
 * the end of file is reached, the function returns false.  If the character
 * read is a newline, then the istream's line count is incremented.
 */
bool
istream_read_char(IStreamT *, char *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
 *
 * This function reads the next character from the specified istream (but does
 * not advance the character pointer).  If a character is read then the
 * character is assigned to the reference argument, and the function returns
 * true.  If the end of file is reached, the function returns false.
 */
bool
istream_peek_char(IStreamT *, char *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
 *
 * This function reads a character sequence from the specified istream, and
 * parses it as an escaped character sequence.  Normally, the character to
 * which the sequence evaluates is assigned to the reference argument and
 * ISTREAM_STAT_READ_CHAR is returned.  If if it evaluates to no
 * character, then ISTREAM_STAT_NO_CHAR is returned (this is not an
 * error).  If there is an error in the syntax of the character sequence, then
 * ISTREAM_STAT_SYNTAX_ERROR is returned.  If any of the characters read
 * are newline characters, then the istream's line counter will be incremented
 * for each newline.
 */
IStreamStatusT
istream_read_escaped_char(IStreamT *, char *);

/*
 * This function increments the specified istream's line counter.  It should
 * only really be called as specified in the documentation for the
 * ISTREAM_READ_CHAR macro.
 */
void
istream_inc_line(IStreamT *);

/*
 * This function returns the line number of the specified istream (one more
 * than the number of newlines that have been read).
 */
unsigned
istream_line(IStreamT *);

/*
 * This function returns the name of the file from which the specified istream
 * is reading. The return value should not be modified or deallocated.
 */
const char *
istream_name(IStreamT *);

/*
 * This function closes the specified istream.
 */
void
istream_close(IStreamT *);

void
X__istream_fill_buffer(IStreamT *);

/*
 * This macro returns the next character from the specified istream.  It is a
 * slightly faster alternative to the istream_read_char function.  In
 * order to get the speed improvement, the program needs to do some extra
 * work: if the character returned is a newline, then the program must call
 * the istream_inc_line function to increment the line count; if the
 * character returned is a null character, then the program must call the
 * ISTREAM_HANDLE_NULL macro on the istream that was read.  It is not
 * obvious that the speed increase is worth the extra effort in coding.
 */
#define ISTREAM_READ_CHAR(istream) \
	(((istream)->read_last = true), (*((istream)->current)++))

/*
 * This macro returns the next character from the specified istream, without
 * reading it.  It is a slightly faster alternative to the
 * istream_peek_char function.  In order to get the speed improvement, the
 * program needs to do some extra work: if the character returned is the null
 * character, then the program must call the ISTREAM_HANDLE_NULL macro on
 * the istream that was read.  Unlike the ISTREAM_READ_CHAR macro, it is
 * not necessary to increment the istream's line count.  It is not obvious
 * that the speed increase is worth the extra effort in coding.
 */
#define ISTREAM_PEEK_CHAR(istream) \
	(((istream)->read_last = false), (*((istream)->current)))

/*
 * Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
 *
 * This macro should be called when either of the previous two macros returns
 * the null character.  It checks to see if the null character is really a
 * null character, a refill buffer instruction, or an end of file.  If it is a
 * real null character, then the program continues normally.  If it is a
 * refill buffer instruction, the istream's buffer is refilled, and the
 * program goes to the label redo.  If it is an end of file, then the
 * program goes to the label eof.
 */
#define ISTREAM_HANDLE_NULL(istream, redo, eof) {\
	IStreamT * X___is = (istream); \
	if (X___is->read_last) { \
		if (X___is->current == X___is->end) { \
			if (X___is->end == X___is->limit) { \
				X__istream_fill_buffer(X___is); \
				goto redo; \
			} else { \
				X___is->current--; \
				goto eof; \
			} \
		} \
	} else { \
		if (X___is->current == (X___is->end - 1)) { \
			if (X___is->end == X___is->limit) { \
				X__istream_fill_buffer(X___is); \
				goto redo; \
			} else { \
				goto eof; \
			} \
		} \
	} \
}

#endif /* !defined (H_ISTREAM) */
