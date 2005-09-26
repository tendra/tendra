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


/**** bostream.h --- Binary output stream handling.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies the interface to the binary output stream facility.
 *
 ***=== TYPES ================================================================
 *
 ** Type:	BOStreamT
 ** Type:	BOStreamP
 ** Repr:	<private>
 *
 * This is the output stream type.
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	void		bostream_init(BOStreamP bostream)
 ** Exceptions:
 *
 * This function initialises the specified bostream not to write to any file.
 *
 ** Function:	BoolT		bostream_open(BOStreamP bostream, char *name)
 ** Exceptions:
 *
 * This function initialises the specified bostream to write to the file with
 * the specified name.  The name should not be modified or deallocated until
 * the bostream has been closed.  If the file cannot be opened, the function
 * returns false. If the file is opened successfully, the function returns
 * true.
 *
 ** Function:	void		bostream_assign(BOStreamP to, BOStreamP from)
 ** Exceptions:
 *
 * This function assigns the from bostream to the to bostream.  The from
 * bostream should not be used again.
 *
 ** Function:	BoolT		bostream_is_open(BOStreamP bostream)
 *
 * This function returns true if the specified bostream is writing to a file,
 * and false otherwise.
 *
 ** Function:	void		bostream_write_chars(BOStreamP bostream,
 *				    unsigned length, char *chars)
 ** Exceptions:	XX_bostream_write_error
 *
 * This function writes the length characters in the chars vector to the
 * specified bostream.
 *
 ** Function:	void		bostream_write_bytes(BOStreamP bostream,
 *				    unsigned length, ByteP bytes)
 ** Exceptions:	XX_bostream_write_error
 *
 * This function writes the length bytes in the bytes vector to the specified
 * bostream.
 *
 ** Function:	void		bostream_write_byte(BOStreamP bostream,
 *				    ByteT byte)
 ** Exceptions:	XX_bostream_write_error
 *
 * This function writes the byte to the specified bostream.
 *
 ** Function:	char *		bostream_name(BOStreamP bostream)
 ** Exceptions:
 *
 * This function returns the name of the file to which the specified
 * bostream is writing. The return value should not be modified or
 * deallocated.
 *
 ** Function:	void		bostream_close(BOStreamP bostream)
 ** Exceptions:
 *
 * This function closes the specified bostream.
 *
 ***=== EXCEPTIONS ===========================================================
 *
 ** Exception:	XX_bostream_write_error (char *name)
 *
 * This exception is raised if a write attempt fails.  The data thrown is a
 * copy of the name of the file that the write error occurred on.  The copy
 * should be deallocated when finished with.
 *
 **** Change Log:*/

/****************************************************************************/

#ifndef H_BOSTREAM
#define H_BOSTREAM

#include "config.h"
#include "exception.h"

/*--------------------------------------------------------------------------*/

typedef struct BOStreamT {
    FILE		       *file;
    char *			name;
} BOStreamT, *BOStreamP;

/*--------------------------------------------------------------------------*/

extern ExceptionP		XX_bostream_write_error;

/*--------------------------------------------------------------------------*/

extern void			bostream_init(BOStreamP);
extern BoolT			bostream_open(BOStreamP, char *);
extern void			bostream_assign(BOStreamP, BOStreamP);
extern BoolT			bostream_is_open(BOStreamP);
extern void			bostream_write_chars(BOStreamP, unsigned, char *);
extern void			bostream_write_bytes(BOStreamP, unsigned, ByteP);
extern void			bostream_write_byte(BOStreamP, ByteT);
extern char *			bostream_name(BOStreamP);
extern void			bostream_close(BOStreamP);

#endif /* !defined (H_BOSTREAM) */
