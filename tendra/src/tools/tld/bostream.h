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
 ** Function:	void			bostream_init
 *			PROTO_S ((BOStreamP bostream))
 ** Exceptions:
 *
 * This function initialises the specified bostream not to write to any file.
 *
 ** Function:	BoolT			bostream_open
 *			PROTO_S ((BOStreamP bostream, CStringP name))
 ** Exceptions:
 *
 * This function initialises the specified bostream to write to the file with
 * the specified name.  The name should not be modified or deallocated until
 * the bostream has been closed.  If the file cannot be opened, the function
 * returns false. If the file is opened successfully, the function returns
 * true.
 *
 ** Function:	void			bostream_assign
 *			PROTO_S ((BOStreamP to, BOStreamP from))
 ** Exceptions:
 *
 * This function assigns the from bostream to the to bostream.  The from
 * bostream should not be used again.
 *
 ** Function:	BoolT			bostream_is_open
 *			PROTO_S ((BOStreamP bostream))
 *
 * This function returns true if the specified bostream is writing to a file,
 * and false otherwise.
 *
 ** Function:	void			bostream_write_chars
 *			PROTO_S ((BOStreamP bostream, unsigned length,
 *				  CStringP chars))
 ** Exceptions:	XX_bostream_write_error
 *
 * This function writes the length characters in the chars vector to the
 * specified bostream.
 *
 ** Function:	void			bostream_write_bytes
 *			PROTO_S ((BOStreamP bostream, unsigned length,
 *				  ByteP bytes))
 ** Exceptions:	XX_bostream_write_error
 *
 * This function writes the length bytes in the bytes vector to the specified
 * bostream.
 *
 ** Function:	void			bostream_write_byte
 *			PROTO_S ((BOStreamP bostream, ByteT byte))
 ** Exceptions:	XX_bostream_write_error
 *
 * This function writes the byte to the specified bostream.
 *
 ** Function:	CStringP		bostream_name
 *			PROTO_S ((BOStreamP bostream))
 ** Exceptions:
 *
 * This function returns the name of the file to which the specified
 * bostream is writing. The return value should not be modified or
 * deallocated.
 *
 ** Function:	void			bostream_close
 *			PROTO_S ((BOStreamP bostream))
 ** Exceptions:
 *
 * This function closes the specified bostream.
 *
 ***=== EXCEPTIONS ===========================================================
 *
 ** Exception:	XX_bostream_write_error (CStringP name)
 *
 * This exception is raised if a write attempt fails.  The data thrown is a
 * copy of the name of the file that the write error occured on.  The copy
 * should be deallocated when finished with.
 *
 **** Change Log:
 * $Log: bostream.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:17  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:45:23  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:14  smf
 * Initial import of os-interface shared files.
 *
**/

/****************************************************************************/

#ifndef H_BOSTREAM
#define H_BOSTREAM

#include "os-interface.h"
#include "exception.h"

/*--------------------------------------------------------------------------*/

typedef struct BOStreamT {
    FILE		       *file;
    CStringP			name;
} BOStreamT, *BOStreamP;

/*--------------------------------------------------------------------------*/

extern ExceptionP		XX_bostream_write_error;

/*--------------------------------------------------------------------------*/

extern void			bostream_init
	PROTO_S ((BOStreamP));
extern BoolT			bostream_open
	PROTO_S ((BOStreamP, CStringP));
extern void			bostream_assign
	PROTO_S ((BOStreamP, BOStreamP));
extern BoolT			bostream_is_open
	PROTO_S ((BOStreamP));
extern void			bostream_write_chars
	PROTO_S ((BOStreamP, unsigned, CStringP));
extern void			bostream_write_bytes
	PROTO_S ((BOStreamP, unsigned, ByteP));
extern void			bostream_write_byte
	PROTO_S ((BOStreamP, ByteT));
extern CStringP			bostream_name
	PROTO_S ((BOStreamP));
extern void			bostream_close
	PROTO_S ((BOStreamP));

#endif /* !defined (H_BOSTREAM) */
