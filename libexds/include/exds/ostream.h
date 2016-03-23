/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * ostream.h - Output stream handling.
 *
 * This file specifies the interface to the output stream facility.
 *
 *
 * Exception:	XX_ostream_write_error
 *
 * This exception is raised if a write attempt fails.  The data thrown is a
 * copy of the name of the file on which the error occured.  The copy should
 * be deallocated when finished with.
 */

#ifndef H_OSTREAM
#define H_OSTREAM

#include <stdio.h>

#include <exds/common.h>
#include <exds/exception.h>


/*
 * This is the output stream type.
 * TODO is this private?
 */
typedef struct OStreamT OStreamT;
struct OStreamT {
	FILE *file;
	const char *name;
	const char *gen_name;
	int no;
	unsigned line;
};

extern ExceptionT *XX_ostream_write_error;

/*
 * This is the standard output stream.  Its initial buffering state is
 * undefined.  The ``ostream_setup'' function must be called before this
 * constant is used.
 */
extern OStreamT *const ostream_output;

/*
 * This is the standard error stream.  Its initial buffering state is
 * undefined.  The ``ostream_setup'' function must be called before this
 * constant is used.
 */
extern OStreamT *const ostream_error;

/*
 * This function initialises the output stream facility.  It should be called
 * before any other ostream manipulation function.
 */
void
ostream_setup(void);

/*
 * This function initialises the specified ostream not to write to any file.
 */
void
ostream_init(OStreamT *);

/*
 * This function initialises the specified ostream to write to the file with
 * the specified name.  If the file cannot be opened, the function returns
 * false.  If the file is opened successfully, the function returns true.  The
 * name should not be modified or deallocated until the ostream has been
 * closed.  The initial buffering state of the ostream is fully buffered.
 */
BoolT
ostream_open(OStreamT *, const char *);

/*
 * This function returns true if the specified ostream is writing to a file,
 * and false otherwise.
 */
BoolT
ostream_is_open(OStreamT *);

/*
 * This function sets the buffering state of the specified ostream to fully
 * buffered.
 */
void
ostream_buffer(OStreamT *);

/*
 * This function sets the buffering state of the specified ostream to
 * unbuffered.
 */
void
ostream_unbuffer(OStreamT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function closes the specified ostream.
 */
void
ostream_close(OStreamT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function flushes the ostream's output buffer.
 */
void
ostream_flush(OStreamT *);

/*
 * This function returns the name of the file that the specified ostream is
 * writing to.  The return value should not be modified or deallocated.
 */
const char *
ostream_name(OStreamT *);

const char *
ostream_gen_name(OStreamT * ostream);

/*
 * This function returns one more than the number of newlines that have been
 * written to the specified ostream.  The result is undefined if the stream
 * is not open.
 */
unsigned
ostream_line(OStreamT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes a newline to the specified ostream.
 */
void
write_newline(OStreamT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes a tab to the specified ostream.
 */
void
write_tab(OStreamT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified character to the specified ostream.
 */
void
write_char(OStreamT *, char);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified character to the specified ostream.
 * This differs from the ``write_char'' function, in that it will
 * `pretty-print' non-printing characters.
 */
void
write_escaped_char(OStreamT *, char);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified integer to the specified ostream.
 */
void
write_int(OStreamT *, int);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified unsigned integer to the specified
 * ostream.
 */
void
write_unsigned(OStreamT *, unsigned);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified C string to the specified ostream.
 */
void
write_cstring(OStreamT *, const char *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified sequence of characters (of the specified
 * length) to the specified ostream.
 */
void
write_chars(OStreamT *, const char *, size_t);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified sequence of characters (of the specified
 * length) to the specified ostream.  This differs from the ``write_chars''
 * function, in that it will `pretty-print' non-printing characters.
 */
void
write_escaped_chars(OStreamT *, const char *, size_t);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes a string containing a description of the current
 * system error (as defined by the ``errno'' global variable) to the specified
 * ostream.
 */
void
write_system_error(OStreamT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes a string containing the address of the object pointed
 * to by the pointer to the specified ostream.
 */
void
write_pointer(OStreamT *, const void *);

#endif /* !defined (H_OSTREAM) */
