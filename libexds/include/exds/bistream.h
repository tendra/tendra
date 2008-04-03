/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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

/*
 * bistream.h - Binary input stream handling.
 *
 * This file specifies the interface to the binary input stream facility.
 *
 *
 * Exception:	XX_bistream_read_error (char * name)
 *
 * This exception is raised if a read attempt fails.  The data thrown is a
 * copy of the name of the file that the read error occured on.  The copy
 * should be deallocated when finished with.
 */

#ifndef H_BISTREAM
#define H_BISTREAM

#include <stdio.h>
#include <stdint.h>

#include <exds/common.h>
#include <exds/exception.h>


/*
 * This is the input stream type. Its representation is private.
 */
typedef struct BIStreamT BIStreamT;
struct BIStreamT {
	FILE *file;
	unsigned bytes;
	char *name;
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
bistream_open(BIStreamT *, char *);

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
unsigned
bistream_read_chars(BIStreamT *, unsigned, char *);

/*
 * Exceptions:	XX_bistream_read_error
 *
 * This function reads the next length bytes from the specified bistream.  The
 * bytes read are placed in the bytes vector, which should be long enough to
 * hold at least length bytes.  The function returns the number of bytes
 * actually read.
 */
unsigned
bistream_read_bytes(BIStreamT *, unsigned, uint8_t *);

/*
 * Exceptions:	XX_bistream_read_error
 *
 * This function reads the next character from the specified bistream.  If a
 * byte is read then the byte is assigned to the reference argument, and the
 * function returns true.  If the end of file is reached, the function returns
 * false.
 */
BoolT
bistream_read_byte(BIStreamT *, uint8_t *);

/*
 * This function returns the number of bytes that have been read from the
 * specified bistream.
 */
unsigned
bistream_byte(BIStreamT *);

/*
 * This function returns the name of the file from which the specified
 * bistream is reading. The return value should not be modified or
 * deallocated.
 */
char *
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

