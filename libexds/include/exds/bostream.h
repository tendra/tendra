/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * bostream.h - Binary output stream handling.
 *
 * This file specifies the interface to the binary output stream facility.
 *
 *
 * Exception:	XX_bostream_write_error
 *
 * This exception is raised if a write attempt fails.  The data thrown is a
 * copy of the name of the file that the write error occured on.  The copy
 * should be deallocated when finished with.
 */

#ifndef H_BOSTREAM
#define H_BOSTREAM

#include <stdio.h>

#include <exds/common.h>
#include <exds/exception.h>


/*
 * This is the output stream type. Its representation is private.
 */
typedef struct BOStreamT BOStreamT;
struct BOStreamT {
	FILE *file;
	const char *name;
};

extern ExceptionT *XX_bostream_write_error;

/*
 * This function initialises the specified bostream not to write to any file.
 *
 * See bostream_open() to initialise to write to a specific file.
 */
void
bostream_init(BOStreamT *);

/*
 * This function initialises the specified bostream to write to the file with
 * the specified name.  The name should not be modified or deallocated until
 * the bostream has been closed.  If the file cannot be opened, the function
 * returns false. If the file is opened successfully, the function returns
 * true.
 *
 * See bostream_init() to initialise not to write to a file.
 */
bool
bostream_open(BOStreamT *, const char *);

/*
 * This function assigns the from bostream to the to bostream.  The from
 * bostream should not be used again.
 */
void
bostream_assign(BOStreamT *, BOStreamT *);

/*
 * This function returns true if the specified bostream is writing to a file,
 * and false otherwise.
 */
bool
bostream_is_open(BOStreamT *);

/*
 * Exceptions:	XX_bostream_write_error
 *
 * This function writes the length characters in the chars vector to the
 * specified bostream.
 */
void
bostream_write_chars(BOStreamT *, size_t, const char *);

/*
 * Exceptions:	XX_bostream_write_error
 *
 * This function writes the length bytes in the bytes vector to the specified
 * bostream.
 */
void
bostream_write_bytes(BOStreamT *, size_t, const ByteT *);

/*
 * Exceptions:	XX_bostream_write_error
 *
 * This function writes the byte to the specified bostream.
 */
void
bostream_write_byte(BOStreamT *, ByteT);

/*
 * This function returns the name of the file to which the specified
 * bostream is writing. The return value should not be modified or
 * deallocated.
 */
const char *
bostream_name(BOStreamT *);

/*
 * This function closes the specified bostream.
 */
void
bostream_close(BOStreamT *);

#endif /* !defined (H_BOSTREAM) */
