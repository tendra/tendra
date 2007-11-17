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
 * bostream.h - Binary output stream handling.
 *
 * This file specifies the interface to the binary output stream facility.
 *
 * This depends on:
 *
 *  <exds/common.h>
 *  <exds/exception.h>
 *
 *
 * Exception:	XX_bostream_write_error (char * name)
 *
 * This exception is raised if a write attempt fails.  The data thrown is a
 * copy of the name of the file that the write error occured on.  The copy
 * should be deallocated when finished with.
 */

#ifndef H_BOSTREAM
#define H_BOSTREAM

#include <stdint.h>
#include <stdio.h>


/*
 * This is the output stream type. Its representation is private.
 */
struct BOStreamT {
    FILE		       *file;
    char *			name;
};

extern ExceptionT *		XX_bostream_write_error;

/*
 * This function initialises the specified bostream not to write to any file.
 *
 * See bostream_open() to initialise to write to a specific file.
 */
extern void			bostream_init (struct BOStreamT *);

/*
 * This function initialises the specified bostream to write to the file with
 * the specified name.  The name should not be modified or deallocated until
 * the bostream has been closed.  If the file cannot be opened, the function
 * returns false. If the file is opened successfully, the function returns
 * true.
 *
 * See bostream_init() to initialise not to write to a file.
 */
extern BoolT			bostream_open (struct BOStreamT *, char *);

/*
 * This function assigns the from bostream to the to bostream.  The from
 * bostream should not be used again.
 */
extern void			bostream_assign (struct BOStreamT *, struct BOStreamT *);

/*
 * This function returns true if the specified bostream is writing to a file,
 * and false otherwise.
 */
extern BoolT			bostream_is_open (struct BOStreamT *);

/*
 * Exceptions:	XX_bostream_write_error
 *
 * This function writes the length characters in the chars vector to the
 * specified bostream.
 */
extern void			bostream_write_chars (struct BOStreamT *, unsigned, char *);

/*
 * Exceptions:	XX_bostream_write_error
 *
 * This function writes the length bytes in the bytes vector to the specified
 * bostream.
 */
extern void			bostream_write_bytes (struct BOStreamT *, unsigned, uint8_t *);

/*
 * Exceptions:	XX_bostream_write_error
 *
 * This function writes the byte to the specified bostream.
 */
extern void			bostream_write_byte (struct BOStreamT *, uint8_t);

/*
 * This function returns the name of the file to which the specified
 * bostream is writing. The return value should not be modified or
 * deallocated.
 */
extern char *			bostream_name (struct BOStreamT *);

/*
 * This function closes the specified bostream.
 */
extern void			bostream_close (struct BOStreamT *);

#endif /* !defined (H_BOSTREAM) */
