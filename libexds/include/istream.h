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
 * istream.h - Input stream handling.
 *
 * This file specifies the interface to the input stream facility.
 *
 * This depends on:
 *
 *  <exds/common.h>
 *  <exds/exception.h>
 *
 *
 * Exception:	XX_istream_read_error (char * name)
 *
 * This exception is raised if a read attempt fails.  The data thrown is a
 * copy of the name of the file that the read error occured on.  The copy
 * should be deallocated when finished with.
 */

#ifndef H_ISTREAM
#define H_ISTREAM

#include <stdio.h>

/*
 * This is the input stream type.
 */
struct IStreamT {
    FILE		       *file;
    char *			buffer;
    char *			current;
    char *			end;
    char *			limit;
    unsigned			line;
    char *			name;
    BoolT			read_last;
};

/*
 * This is the return type of the ``istream_read_escaped_char'' function.  The
 * constants represent the results: a character was read, no character was
 * read, and a syntax error occured respectively.
 */
typedef enum {
    ISTREAM_STAT_READ_CHAR,
    ISTREAM_STAT_NO_CHAR,
    ISTREAM_STAT_SYNTAX_ERROR
} IStreamStatusT;


extern ExceptionT *	 XX_istream_read_error;

/*
 * This value is a pointer to an input stream object that will read from the
 * standard input.  The ``istream_setup'' function must be called before this
 * constant is used.
 */
extern struct IStreamT		*const istream_input;

/*
 * This function initialises the input stream facility.  It should be called
 * before any other istream manipulation function.
 */
extern void			istream_setup(void);

/*
 * This function initialises the specified istream not to read from any file.
 */
extern void			istream_init(struct IStreamT *);

/*
 * Exceptions: XX_dalloc_no_memory, XX_istream_read_error
 *
 * This function initialises the specified istream to read from the file with
 * the specified name.  The name should not be modified or deallocated until
 * the istream has been closed.  If the file cannot be opened, the function
 * returns false. If the file is opened successfully, the function returns
 * true.
 */
extern BoolT			istream_open(struct IStreamT *, char *);

/*
 * This function assigns the from istream to the to istream.  The from istream
 * should not be used again.
 */
extern void			istream_assign(struct IStreamT *, struct IStreamT *);

/*
 * This function returns true if the specified istream is reading from a file,
 * and false otherwise.
 */
extern BoolT			istream_is_open(struct IStreamT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
 *
 * This function reads the next character from the specified istream (and
 * advances the character pointer).  If a character is read then the character
 * is assigned to the reference argument, and the function returns true.  If
 * the end of file is reached, the function returns false.  If the character
 * read is a newline, then the istream's line count is incremented.
 */
extern BoolT			istream_read_char(struct IStreamT *, char *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
 *
 * This function reads the next character from the specified istream (but does
 * not advance the character pointer).  If a character is read then the
 * character is assigned to the reference argument, and the function returns
 * true.  If the end of file is reached, the function returns false.
 */
extern BoolT			istream_peek_char(struct IStreamT *, char *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
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
 */
extern IStreamStatusT		istream_read_escaped_char(struct IStreamT *, char *);

/*
 * This function increments the specified istream's line counter.  It should
 * only really be called as specified in the documentation for the
 * ``ISTREAM_READ_CHAR'' macro.
 */
extern void			istream_inc_line(struct IStreamT *);

/*
 * This function returns the line number of the specified istream (one more
 * than the number of newlines that have been read).
 */
extern unsigned			istream_line(struct IStreamT *);

/*
 * This function returns the name of the file from which the specified istream
 * is reading. The return value should not be modified or deallocated.
 */
extern char *			istream_name(struct IStreamT *);

/*
 * This function closes the specified istream.
 */
extern void			istream_close(struct IStreamT *);


extern void			X__istream_fill_buffer(struct IStreamT *);

/*
 * This macro returns the next character from the specified istream.  It is a
 * slightly faster alternative to the ``istream_read_char'' function.  In
 * order to get the speed improvement, the program needs to do some extra
 * work: if the character returned is a newline, then the program must call
 * the ``istream_inc_line'' function to increment the line count; if the
 * character returned is a null character, then the program must call the
 * ``ISTREAM_HANDLE_NULL'' macro on the istream that was read.  It is not
 * obvious that the speed increase is worth the extra effort in coding.
 */
#define ISTREAM_READ_CHAR(istream)\
(((istream)->read_last = TRUE), (*((istream)->current)++))

/*
 * This macro returns the next character from the specified istream, without
 * reading it.  It is a slightly faster alternative to the
 * ``istream_peek_char'' function.  In order to get the speed improvement, the
 * program needs to do some extra work: if the character returned is the null
 * character, then the program must call the ``ISTREAM_HANDLE_NULL'' macro on
 * the istream that was read.  Unlike the ``ISTREAM_READ_CHAR'' macro, it is
 * not necessary to increment the istream's line count.  It is not obvious
 * that the speed increase is worth the extra effort in coding.
 */
#define ISTREAM_PEEK_CHAR(istream)\
(((istream)->read_last = FALSE), (*((istream)->current)))

/*
 * Exceptions:	XX_dalloc_no_memory, XX_istream_read_error
 *
 * This macro should be called when either of the previous two macros returns
 * the null character.  It checks to see if the null character is really a
 * null character, a refill buffer instruction, or an end of file.  If it is a
 * real null character, then the program continues normally.  If it is a
 * refill buffer instruction, the istream's buffer is refilled, and the
 * program goes to the label ``redo''.  If it is an end of file, then the
 * program goes to the label ``eof''.
 */
#define ISTREAM_HANDLE_NULL(istream,redo,eof)\
{ \
    struct IStreamT * X___is = (istream); \
    if (X___is->read_last) { \
	if (X___is->current == X___is->end) { \
	    if (X___is->end == X___is->limit) { \
		X__istream_fill_buffer(X___is); \
		goto redo; \
	    } else { \
		X___is->current--; \
		goto eof; \
	    } \
	} \
    } else { \
	if (X___is->current == (X___is->end - 1)) { \
	    if (X___is->end == X___is->limit) { \
		X__istream_fill_buffer(X___is); \
		goto redo; \
	    } else { \
		goto eof; \
	    } \
	} \
    } \
}

#endif /* !defined (H_ISTREAM) */
