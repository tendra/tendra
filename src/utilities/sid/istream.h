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


/**** istream.h --- Input stream handling.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies the interface to the input stream facility.
 *
 ***=== TYPES ================================================================
 *
 ** Type:	IStreamT
 ** Type:	IStreamP
 ** Repr:	<private>
 *
 * This is the input stream type.
 *
 ** Type:	IStreamStatusT
 ** Type:	IStreamStatusP
 ** Repr:	enum {ISTREAM_STAT_READ_CHAR, ISTREAM_STAT_NO_CHAR,
 *		      ISTREAM_STAT_SYNTAX_ERROR}
 *
 * This is the return type of the ``istream_read_escaped_char'' function.  The
 * constants represent the results: a character was read, no character was
 * read, and a syntax error occured respectively.
 *
 ***=== CONSTANTS ============================================================
 *
 ** Constant:	istream_input
 *
 * This value is a pointer to an input stream object that will read from the
 * standard input.  The ``istream_setup'' function must be called before this
 * constant is used.
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	void			istream_setup
 *			PROTO_S ((void))
 ** Exceptions:
 *
 * This function initialises the input stream facility.  It should be called
 * before any other istream manipulation function.
 *
 ** Function:	void			istream_init
 *			PROTO_S ((IStreamP istream))
 ** Exceptions:
 *
 * This function initialises the specified istream not to read from any file.
 *
 ** Function:	BoolT			istream_open
 *			PROTO_S ((IStreamP istream, CStringP name))
 ** Exceptions: XX_dalloc_no_memory, XX_istream_read_error
 *
 * This function initialises the specified istream to read from the file with
 * the specified name.  The name should not be modified or deallocated until
 * the istream has been closed.  If the file cannot be opened, the function
 * returns false. If the file is opened successfully, the function returns
 * true.
 *
 ** Function:	void			istream_assign
 *			PROTO_S ((IStreamP to, IStreamP from))
 ** Exceptions:
 *
 * This function assigns the from istream to the to istream.  The from istream
 * should not be used again.
 *
 ** Function:	BoolT			istream_is_open
 *			PROTO_S ((IStreamP istream))
 *
 * This function returns true if the specified istream is reading from a file,
 * and false otherwise.
 *
 ** Function:	BoolT			istream_read_char
 *			PROTO_S ((IStreamP istream, char *c_ref))
 ** Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
 *
 * This function reads the next character from the specified istream (and
 * advances the character pointer).  If a character is read then the character
 * is assigned to the reference argument, and the function returns true.  If
 * the end of file is reached, the function returns false.  If the character
 * read is a newline, then the istream's line count is incremented.
 *
 ** Function:	BoolT			istream_peek_char
 *			PROTO_S ((IStreamP istream, char *c_ref))
 ** Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
 *
 * This function reads the next character from the specified istream (but does
 * not advance the character pointer).  If a character is read then the
 * character is assigned to the reference argument, and the function returns
 * true.  If the end of file is reached, the function returns false.
 *
 ** Function:	IStreamStatusT		istream_read_escaped_char
 *			PROTO_S ((IStreamP istream, char *c_ref))
 ** Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
 *
 * This function reads a character sequence from the specified istream, and
 * parses it as an escaped character sequence.  Normally, the character to
 * which the sequence evaluates is assigned to the reference argument and
 * ``ISTREAM_STAT_READ_CHAR'' is returned.  If if it evaluates to no
 * character, then ``ISTREAM_STAT_NO_CHAR'' is returned (this is not an
 * error).  If there is an error in the syntax of the character sequence, then
 * ``ISTREAM_STAT_SYNTAX_ERROR'' is returned.  If any of the characters read
 * are newline characters, then the istream's line counter will be incremented
 * for each newline.
 *
 ** Function:	void			istream_inc_line
 *			PROTO_S ((IStreamP istream))
 ** Exceptions:
 *
 * This function increments the specified istream's line counter.  It should
 * only really be called as specified in the documentation for the
 * ``ISTREAM_READ_CHAR'' macro.
 *
 ** Function:	unsigned		istream_line
 *			PROTO_S ((IStreamP istream))
 ** Exceptions:
 *
 * This function returns the line number of the specified istream (one more
 * than the number of newlines that have been read).
 *
 ** Function:	CStringP		istream_name
 *			PROTO_S ((IStreamP istream))
 ** Exceptions:
 *
 * This function returns the name of the file from which the specified istream
 * is reading. The return value should not be modified or deallocated.
 *
 ** Function:	void			istream_close
 *			PROTO_S ((IStreamP istream))
 ** Exceptions:
 *
 * This function closes the specified istream.
 *
 ***=== MACROS ===============================================================
 *
 ** Macro:	ISTREAM_READ_CHAR (istream)
 ** Exceptions:
 *
 * This macro returns the next character from the specified istream.  It is a
 * slightly faster alternative to the ``istream_read_char'' function.  In
 * order to get the speed improvement, the program needs to do some extra
 * work: if the character returned is a newline, then the program must call
 * the ``istream_inc_line'' function to increment the line count; if the
 * character returned is a null character, then the program must call the
 * ``ISTREAM_HANDLE_NULL'' macro on the istream that was read.  It is not
 * obvious that the speed increase is worth the extra effort in coding.
 *
 ** Macro:	ISTREAM_PEEK_CHAR (istream)
 ** Exceptions:
 *
 * This macro returns the next character from the specified istream, without
 * reading it.  It is a slightly faster alternative to the
 * ``istream_peek_char'' function.  In order to get the speed improvement, the
 * program needs to do some extra work: if the character returned is the null
 * character, then the program must call the ``ISTREAM_HANDLE_NULL'' macro on
 * the istream that was read.  Unlike the ``ISTREAM_READ_CHAR'' macro, it is
 * not necessary to increment the istream's line count.  It is not obvious
 * that the speed increase is worth the extra effort in coding.
 *
 ** Macro:	ISTREAM_HANDLE_NULL (istream, redo, eof)
 ** Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
 *
 * This macro should be called when either of the previous two macros returns
 * the null character.  It checks to see if the null character is really a
 * null character, a refill buffer instruction, or an end of file.  If it is a
 * real null character, then the program continues normally.  If it is a
 * refill buffer instruction, the istream's buffer is refilled, and the
 * program goes to the label ``redo''.  If it is an end of file, then the
 * program goes to the label ``eof''.
 *
 ***=== EXCEPTIONS ===========================================================
 *
 ** Exception:	XX_istream_read_error (CStringP name)
 *
 * This exception is raised if a read attempt fails.  The data thrown is a
 * copy of the name of the file that the read error occured on.  The copy
 * should be deallocated when finished with.
 *
 **** Change Log:
 * $Log: istream.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:45:43  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:10  smf
 * Initial import of os-interface shared files.
 *
**/

/****************************************************************************/

#ifndef H_ISTREAM
#define H_ISTREAM

#include "os-interface.h"
#include "dalloc.h"
#include "exception.h"

/*--------------------------------------------------------------------------*/

typedef struct IStreamT {
    FILE		       *file;
    CStringP			buffer;
    CStringP			current;
    CStringP			end;
    CStringP			limit;
    unsigned			line;
    CStringP			name;
    BoolT			read_last;
} IStreamT, *IStreamP;

#ifdef FS_NO_ENUM
typedef int IStreamStatusT, *IStreamStatusP;
#define ISTREAM_STAT_READ_CHAR		(0)
#define ISTREAM_STAT_NO_CHAR		(1)
#define ISTREAM_STAT_SYNTAX_ERROR	(2)
#else
typedef enum {
    ISTREAM_STAT_READ_CHAR,
    ISTREAM_STAT_NO_CHAR,
    ISTREAM_STAT_SYNTAX_ERROR
} IStreamStatusT, *IStreamStatusP;
#endif /* defined (FS_NO_ENUM) */

/*--------------------------------------------------------------------------*/

extern ExceptionP		XX_istream_read_error;
extern IStreamT		 *const istream_input;

/*--------------------------------------------------------------------------*/

extern void			istream_setup
	PROTO_S ((void));
extern void			istream_init
	PROTO_S ((IStreamP));
extern BoolT			istream_open
	PROTO_S ((IStreamP, CStringP));
extern void			istream_assign
	PROTO_S ((IStreamP, IStreamP));
extern BoolT			istream_is_open
	PROTO_S ((IStreamP));
extern BoolT			istream_read_char
	PROTO_S ((IStreamP, char *));
extern BoolT			istream_peek_char
	PROTO_S ((IStreamP, char *));
extern IStreamStatusT		istream_read_escaped_char
	PROTO_S ((IStreamP, char *));
extern void			istream_inc_line
	PROTO_S ((IStreamP));
extern unsigned			istream_line
	PROTO_S ((IStreamP));
extern CStringP			istream_name
	PROTO_S ((IStreamP));
extern void			istream_close
	PROTO_S ((IStreamP));

/*--------------------------------------------------------------------------*/

extern void			X__istream_fill_buffer
	PROTO_S ((IStreamP));

/*--------------------------------------------------------------------------*/

#define ISTREAM_READ_CHAR(istream) \
(((istream)->read_last = TRUE), (*((istream)->current) ++))

#define ISTREAM_PEEK_CHAR(istream) \
(((istream)->read_last = FALSE), (*((istream)->current)))

#define ISTREAM_HANDLE_NULL(istream,redo,eof) \
{ \
    IStreamP X___is = (istream); \
    if (X___is->read_last) { \
	if (X___is->current == X___is->end) { \
	    if (X___is->end == X___is->limit) { \
		X__istream_fill_buffer (X___is); \
		goto redo; \
	    } else { \
		X___is->current --; \
		goto eof; \
	    } \
	} \
    } else { \
	if (X___is->current == (X___is->end - 1)) { \
	    if (X___is->end == X___is->limit) { \
		X__istream_fill_buffer (X___is); \
		goto redo; \
	    } else { \
		goto eof; \
	    } \
	} \
    } \
}

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define istream_init(is) ((is)->name = NIL (CStringP))
#define istream_is_open(is) ((is)->name != NIL (CStringP))
#define istream_inc_line(is) ((is)->line ++)
#define istream_line(is) ((is)->line)
#define istream_name(is) ((is)->name)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_ISTREAM) */
