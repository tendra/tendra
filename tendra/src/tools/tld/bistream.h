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


/**** bistream.h --- Binary input stream handling.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies the interface to the binary input stream facility.
 *
 ***=== TYPES ================================================================
 *
 ** Type:	BIStreamT
 ** Type:	BIStreamP
 ** Repr:	<private>
 *
 * This is the input stream type.
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	void			bistream_init
 *			PROTO_S ((BIStreamP bistream))
 ** Exceptions:
 *
 * This function initialises the specified bistream not to read from any file.
 *
 ** Function:	BoolT			bistream_open
 *			PROTO_S ((BIStreamP bistream, CStringP name))
 ** Exceptions:
 *
 * This function initialises the specified bistream to read from the file with
 * the specified name.  The name should not be modified or deallocated until
 * the bistream has been closed.  If the file cannot be opened, the function
 * returns false. If the file is opened successfully, the function returns
 * true.
 *
 ** Function:	void			bistream_assign
 *			PROTO_S ((BIStreamP to, BIStreamP from))
 ** Exceptions:
 *
 * This function assigns the from bistream to the to bistream.  The from
 * bistream should not be used again.
 *
 ** Function:	BoolT			bistream_is_open
 *			PROTO_S ((BIStreamP bistream))
 *
 * This function returns true if the specified bistream is reading from a file,
 * and false otherwise.
 *
 ** Function:	unsigned		bistream_read_chars
 *			PROTO_S ((BIStreamP bistream, unsigned length,
 *				  CStringP chars))
 ** Exceptions:	XX_bistream_read_error
 *
 * This function reads the next length characters from the specified bistream.
 * The characters read are placed in the chars vector, which should be long
 * enough to hold at least length characters.  The function returns the number
 * of characters actually read.
 *
 ** Function:	unsigned		bistream_read_bytes
 *			PROTO_S ((BIStreamP bistream, unsigned length,
 *				  ByteP bytes))
 ** Exceptions:	XX_bistream_read_error
 *
 * This function reads the next length bytes from the specified bistream.  The
 * bytes read are placed in the bytes vector, which should be long enough to
 * hold at least length bytes.  The function returns the number of bytes
 * actually read.
 *
 ** Function:	BoolT			bistream_read_byte
 *			PROTO_S ((BIStreamP bistream, ByteT *byte_ref))
 ** Exceptions:	XX_bistream_read_error
 *
 * This function reads the next character from the specified bistream.  If a
 * byte is read then the byte is assigned to the reference argument, and the
 * function returns true.  If the end of file is reached, the function returns
 * false.
 *
 ** Function:	unsigned		bistream_byte
 *			PROTO_S ((BIStreamP bistream))
 ** Exceptions:
 *
 * This function returns the number of bytes that have been read from the
 * specified bistream.
 *
 ** Function:	CStringP		bistream_name
 *			PROTO_S ((BIStreamP bistream))
 ** Exceptions:
 *
 * This function returns the name of the file from which the specified
 * bistream is reading. The return value should not be modified or
 * deallocated.
 *
 ** Function:	void			bistream_rewind
 *			PROTO_S ((BIStreamP bistream))
 ** Exceptions:
 *
 * This function rewinds the specified bistream.
 *
 ** Function:	void			bistream_close
 *			PROTO_S ((BIStreamP bistream))
 ** Exceptions:
 *
 * This function closes the specified bistream.
 *
 ***=== EXCEPTIONS ===========================================================
 *
 ** Exception:	XX_bistream_read_error (CStringP name)
 *
 * This exception is raised if a read attempt fails.  The data thrown is a
 * copy of the name of the file that the read error occured on.  The copy
 * should be deallocated when finished with.
 *
 **** Change Log:*/

/****************************************************************************/

#ifndef H_BISTREAM
#define H_BISTREAM

#include "os-interface.h"
#include "exception.h"

/*--------------------------------------------------------------------------*/

typedef struct BIStreamT {
    FILE		       *file;
    unsigned			bytes;
    CStringP			name;
} BIStreamT, *BIStreamP;

/*--------------------------------------------------------------------------*/

extern ExceptionP		XX_bistream_read_error;

/*--------------------------------------------------------------------------*/

extern void			bistream_init(BIStreamP);
extern BoolT			bistream_open(BIStreamP, CStringP);
extern void			bistream_assign(BIStreamP, BIStreamP);
extern BoolT			bistream_is_open(BIStreamP);
extern unsigned			bistream_read_chars(BIStreamP, unsigned, CStringP);
extern unsigned			bistream_read_bytes(BIStreamP, unsigned, ByteP);
extern BoolT			bistream_read_byte(BIStreamP, ByteT *);
extern unsigned			bistream_byte(BIStreamP);
extern CStringP			bistream_name(BIStreamP);
extern void			bistream_rewind(BIStreamP);
extern void			bistream_close(BIStreamP);

#endif /* !defined (H_BISTREAM) */
