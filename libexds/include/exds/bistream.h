/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * bistream.h - Binary input stream handling.
 *
 * This file specifies the interface to the binary input stream facility.
 *
 *
 * Exception:	XX_bistream_read_error
 *
 * This exception is raised if a read attempt fails.  The data thrown is a
 * copy of the name of the file that the read error occured on.  The copy
 * should be deallocated when finished with.
 */

#ifndef H_BISTREAM
#define H_BISTREAM

#include <stdio.h>

#include <exds/common.h>
#include <exds/exception.h>


/*
 * This is the input stream type. Its representation is private.
 */
typedef struct BIStreamT BIStreamT;
struct BIStreamT {
	FILE *file;
	size_t bytes;
	const char *name;
};

extern ExceptionT *XX_bistream_read_error;

/*
 * This function initialises the specified bistream not to read from any file.
 */
void
bistream_init(BIStreamT *);

/*
 * This function initialises the specified bistream to read from the file with
 * the specified name.  The name should not be modified or deallocated until
 * the bistream has been closed.  If the file cannot be opened, the function
 * returns false. If the file is opened successfully, the function returns
 * true.
 */
BoolT
bistream_open(BIStreamT *, const char *);

/*
 * This function assigns the from bistream to the to bistream.  The from
 * bistream should not be used again.
 */
void
bistream_assign(BIStreamT *, BIStreamT *);

/*
 * This function returns true if the specified bistream is reading from a file,
 * and false otherwise.
 */
BoolT
bistream_is_open(BIStreamT *);

/*
 * Exceptions:	XX_bistream_read_error
 *
 * This function reads the next length characters from the specified bistream.
 * The characters read are placed in the chars vector, which should be long
 * enough to hold at least length characters.  The function returns the number
 * of characters actually read.
 */
size_t
bistream_read_chars(BIStreamT *, size_t, char *);

/*
 * Exceptions:	XX_bistream_read_error
 *
 * This function reads the next length bytes from the specified bistream.  The
 * bytes read are placed in the bytes vector, which should be long enough to
 * hold at least length bytes.  The function returns the number of bytes
 * actually read.
 */
size_t
bistream_read_bytes(BIStreamT *, size_t, ByteT *);

/*
 * Exceptions:	XX_bistream_read_error
 *
 * This function reads the next character from the specified bistream.  If a
 * byte is read then the byte is assigned to the reference argument, and the
 * function returns true.  If the end of file is reached, the function returns
 * false.
 */
BoolT
bistream_read_byte(BIStreamT *, ByteT *);

/*
 * This function returns the number of bytes that have been read from the
 * specified bistream.
 */
size_t
bistream_byte(BIStreamT *);

/*
 * This function returns the name of the file from which the specified
 * bistream is reading. The return value should not be modified or
 * deallocated.
 */
const char *
bistream_name(BIStreamT *);

/*
 * This function rewinds the specified bistream.
 */
void
bistream_rewind(BIStreamT *);

/*
 * This function closes the specified bistream.
 */
void
bistream_close(BIStreamT *);

#endif /* !defined (H_BISTREAM) */
