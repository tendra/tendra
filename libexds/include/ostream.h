/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
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
 * ostream.h - Output stream handling.
 *
 * This file specifies the interface to the output stream facility.
 *
 * Exception:	XX_ostream_write_error (char * name)
 *
 * This exception is raised if a write attempt fails.  The data thrown is a
 * copy of the name of the file on which the error occured.  The copy should
 * be deallocated when finished with.
 */

#ifndef H_OSTREAM
#define H_OSTREAM

#include <stdio.h>

#include "os-interface.h"
#include "dalloc.h"
#include "exception.h"

/*
 * This is the output stream type.
 */
typedef struct OStreamT {
    FILE		       *file;
    char *			name;
    unsigned			line;
} OStreamT;

extern ExceptionT *	 XX_ostream_write_error;

/*
 * This is the standard output stream.  Its initial buffering state is
 * undefined.  The ``ostream_setup'' function must be called before this
 * constant is used.
 */
extern OStreamT		*const ostream_output;

/*
 * This is the standard error stream.  Its initial buffering state is
 * undefined.  The ``ostream_setup'' function must be called before this
 * constant is used.
 */
extern OStreamT		*const ostream_error;

/*
 * This function initialises the output stream facility.  It should be called
 * before any other ostream manipulation function.
 */
extern void		ostream_setup(void);

/*
 * This function initialises the specified ostream not to write to any file.
 */
extern void		ostream_init(OStreamT *);

/*
 * This function initialises the specified ostream to write to the file with
 * the specified name.  If the file cannot be opened, the function returns
 * false.  If the file is opened successfully, the function returns true.  The
 * name should not be modified or deallocated until the ostream has been
 * closed.  The initial buffering state of the ostream is fully buffered.
 */
extern BoolT		ostream_open(OStreamT *, char *);

/*
 * This function returns true if the specified ostream is writing to a file,
 * and false otherwise.
 */
extern BoolT		ostream_is_open(OStreamT *);

/*
 * This function sets the buffering state of the specified ostream to fully
 * buffered.
 */
extern void		ostream_buffer(OStreamT *);

/*
 * This function sets the buffering state of the specified ostream to
 * unbuffered.
 */
extern void		ostream_unbuffer(OStreamT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function closes the specified ostream.
 */
extern void		ostream_close(OStreamT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function flushes the ostream's output buffer.
 */
extern void		ostream_flush(OStreamT *);

/*
 * This function returns the name of the file that the specified ostream is
 * writing to.  The return value should not be modified or deallocated.
 */
extern char *		ostream_name(OStreamT *);

/*
 * This function returns one more than the number of newlines that have been
 * written to the specified ostream.  The result is undefined if the stream
 * is not open.
 */
extern unsigned		ostream_line(OStreamT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes a newline to the specified ostream.
 */
extern void		write_newline(OStreamT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes a tab to the specified ostream.
 */
extern void		write_tab(OStreamT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified byte to the specified ostream.
 */
extern void		write_byte(OStreamT *, ByteT);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified character to the specified ostream.
 */
extern void		write_char(OStreamT *, char);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified character to the specified ostream.
 * This differs from the ``write_char'' function, in that it will
 * `pretty-print' non-printing characters.
 */
extern void		write_escaped_char(OStreamT *, char);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified integer to the specified ostream.
 */
extern void		write_int(OStreamT *, int);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified unsigned integer to the specified
 * ostream.
 */
extern void		write_unsigned(OStreamT *, unsigned);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified C string to the specified ostream.
 */
extern void		write_cstring(OStreamT *, char *);

/*
 * Exceptions: XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified sequence of bytes (of the specified
 * length) to the specified ostream.
 */
extern void		write_bytes(OStreamT *, ByteT *, unsigned);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified sequence of characters (of the specified
 * length) to the specified ostream.
 */
extern void		write_chars(OStreamT *, char *, unsigned);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the specified sequence of characters (of the specified
 * length) to the specified ostream.  This differs from the ``write_chars''
 * function, in that it will `pretty-print' non-printing characters.
 */
extern void		write_escaped_chars(OStreamT *, char *, unsigned);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes a string containing a description of the current
 * system error (as defined by the ``errno'' global variable) to the specified
 * ostream.
 */
extern void		write_system_error(OStreamT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes a string containing the address of the object pointed
 * to by the pointer to the specified ostream.
 */
extern void		write_pointer(OStreamT *, void *);

#endif /* !defined (H_OSTREAM) */
