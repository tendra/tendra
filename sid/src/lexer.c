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


/*** lexer.c --- SID lexical analyser.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the interface for the SID lexical analyser.  Any
 * changes to the syntax of SID identifiers should be made to the language
 * specifc lexical analyser files as well.
 *
 * TODO eventually perhaps we could port this to lexi.
 *
 *** Change Log:
 * $Log: lexer.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:42  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:57:27  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:23  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "lexer.h"
#include "gen-errors.h"
#include "syntax.h"

/*--------------------------------------------------------------------------*/

#define LEXER_READ_ONE_CHAR(istream, redo, eof, id)\
    switch ((id) = ISTREAM_READ_CHAR(istream)) { \
      case '\0': \
        ISTREAM_HANDLE_NULL((istream), redo, eof); \
        break; \
      case '\n': \
        istream_inc_line(istream); \
        break; \
      default: \
        break; \
    }

/*--------------------------------------------------------------------------*/

static BoolT
lexer_skip_bracketed_comment(IStreamP istream)
{
    char c1;
    char c2;

  redo1:
    LEXER_READ_ONE_CHAR(istream, redo1, eof, c1);
  redo2:
    LEXER_READ_ONE_CHAR(istream, redo2, eof, c2);
    for (;;) {
	if ((c1 == '/') && (c2 == '*')) {
	    if (!lexer_skip_bracketed_comment(istream)) {
		goto eof;
	    }
	  redo3:
	    LEXER_READ_ONE_CHAR(istream, redo3, eof, c2);
	} else if ((c1 == '*') && (c2 == '/')) {
	    return(TRUE);
	}
	c1 = c2;
      redo4:
	LEXER_READ_ONE_CHAR(istream, redo4, eof, c2);
    }
  eof:
    return(FALSE);
}

static char
lexer_skip_white_space(IStreamP istream)
{
    for (;;) {
	char c;

      redo1:
	switch (c = ISTREAM_READ_CHAR(istream)) {
	  case '\0':
	    ISTREAM_HANDLE_NULL(istream, redo1, eof);
	    break;
	  case '\n':
	    istream_inc_line(istream);
	    break;
	  case '/':
	  redo2:
	    switch (c = ISTREAM_READ_CHAR(istream)) {
	      case '\0':
		ISTREAM_HANDLE_NULL(istream, redo2, eof_in_comment);
		goto illegal_in_comment;
	      case '\n':
		istream_inc_line(istream);
		goto illegal_in_comment;
	      case '*':
		if (!lexer_skip_bracketed_comment(istream)) {
		  eof_in_comment:
		    E_eof_in_comment(istream);
		    return ('\0'); /*FOR EOF*/
		}
		break;
	      case '/':
		do {
		  redo3:
		    LEXER_READ_ONE_CHAR(istream, redo3, eof, c);
		} while (c != '\n');
		break;
	      default:
	      illegal_in_comment:
		E_illegal_comment_character(istream, c);
		break;
	    }
	    break;
	  default:
	    if (!syntax_is_white_space(c)) {
		return(c);
	    }
	    break;
	}
    }
  eof:
    return ('\0'); /*FOR EOF*/
}

static void
lexer_read_builtin(IStreamP istream, LexP token)
{
    DStringT dstring;
    CStringP cstring;

    dstring_init(&dstring);
    for (;;) {
	char c;

      redo:
	switch (c = ISTREAM_READ_CHAR(istream)) {
	  case '\0':
	    ISTREAM_HANDLE_NULL(istream, redo, eof);
	    E_null_character_in_builtin(istream);
	    break;
	  case '\n':
	    istream_inc_line(istream);
	    E_newline_in_builtin(istream);
	    goto done;
	  case '%':
	    goto done;
	  default:
	    dstring_append_char(&dstring, c);
	}
    }
  eof:
    E_eof_in_builtin(istream);
  done:
    cstring = dstring_destroy_to_cstring(&dstring);
    if (cstring_ci_equal(cstring, "types")) {
	token->t = LEXER_TOK_BLT_TYPES;
    } else if (cstring_ci_equal(cstring, "terminals")) {
	token->t = LEXER_TOK_BLT_TERMINALS;
    } else if (cstring_ci_equal(cstring, "productions")) {
	token->t = LEXER_TOK_BLT_PRODUCTIONS;
    } else if (cstring_ci_equal(cstring, "entry")) {
	token->t = LEXER_TOK_BLT_ENTRY;
    } else {
	E_unknown_builtin(istream, cstring);
	UNREACHED;
    }
    DEALLOCATE(cstring);
}

static void
lexer_read_identifier(IStreamP istream, char c, LexP token)
{
    DStringT dstring;

    dstring_init(&dstring);
    dstring_append_char(&dstring, c);
    for (;;) {
      redo1:
	switch (c = ISTREAM_PEEK_CHAR(istream)) {
	  case '\0':
	    ISTREAM_HANDLE_NULL(istream, redo1, done);
	    goto done;
	  default:
	    if ((syntax_is_letter(c)) || (syntax_is_digit(c)) ||
		(c == '_') || (c == '-')) {
	      redo2:
		LEXER_READ_ONE_CHAR(istream, redo2, done, c);
		dstring_append_char(&dstring, c);
	    } else {
		goto done;
	    }
	    break;
	}
    }
  done:
    token->t = LEXER_TOK_IDENTIFIER;
    dstring_to_nstring(&dstring, &(token->u.string));
    dstring_destroy(&dstring);
}

/*--------------------------------------------------------------------------*/

void
lexer_init(LexerStreamP stream, IStreamP istream)
{
    istream_assign(&(stream->istream), istream);
    lexer_next_token(stream);
}

void
lexer_close(LexerStreamP stream)
{
    istream_close(&(stream->istream));
}

CStringP
lexer_stream_name(LexerStreamP stream)
{
    return(istream_name(&(stream->istream)));
}

unsigned
lexer_stream_line(LexerStreamP stream)
{
    return(istream_line(&(stream->istream)));
}

LexerTokenT
lexer_get_terminal(LexerStreamP stream)
{
    return(stream->token.t);
}

void
lexer_next_token(LexerStreamP stream)
{
    IStreamP istream = &(stream->istream);
    LexT     token;
    char     c;

  retry:
    switch (c = lexer_skip_white_space(istream)) {
      case '\0': /*FOR EOF*/
	token.t = LEXER_TOK_EOF;
	break;
      case '#':
	if ((istream_peek_char(istream, &c)) && (c == '#')) {
	   (void)istream_read_char(istream, &c);
	    token.t = LEXER_TOK_HANDLER_SEP;
	    break;
	}
	E_expected_hash(istream);
	goto retry;
      case '$':
	token.t = LEXER_TOK_EMPTY;
	break;
      case '%':
	lexer_read_builtin(istream, &token);
	break;
      case '|':
	if ((istream_peek_char(istream, &c)) && (c == '|')) {
	   (void)istream_read_char(istream, &c);
	    token.t = LEXER_TOK_ALT_SEP;
	    break;
	}
	E_expected_pipe(istream);
	goto retry;
      case ',':
	token.t = LEXER_TOK_SEPARATOR;
	break;
      case ':':
	if ((istream_peek_char(istream, &c)) && (c == ':')) {
	   (void)istream_read_char(istream, &c);
	    token.t = LEXER_TOK_SCOPEMARK;
	    break;
	}
	token.t = LEXER_TOK_TYPEMARK;
	break;
      case ';':
	token.t = LEXER_TOK_TERMINATOR;
	break;
      case '<':
	token.t = LEXER_TOK_BEGIN_ACTION;
	break;
      case '=':
	token.t = LEXER_TOK_DEFINE;
	break;
      case '>':
	token.t = LEXER_TOK_END_ACTION;
	break;
      case '?':
	token.t = LEXER_TOK_PRED_RESULT;
	break;
      case '!':
	token.t = LEXER_TOK_IGNORE;
	break;
      case '{':
	token.t = LEXER_TOK_BEGIN_RULE;
	break;
      case '}':
	token.t = LEXER_TOK_END_RULE;
	break;
      case '[':
	token.t = LEXER_TOK_BEGIN_SCOPE;
	break;
      case ']':
	token.t = LEXER_TOK_END_SCOPE;
	break;
      case '(':
	token.t = LEXER_TOK_OPEN_TUPLE;
	break;
      case ')':
	token.t = LEXER_TOK_CLOSE_TUPLE;
	break;
      case '&':
	token.t = LEXER_TOK_REFERENCE;
	break;
      case '-':
	if ((istream_peek_char(istream, &c)) && (c == '>')) {
	   (void)istream_read_char(istream, &c);
	    token.t = LEXER_TOK_ARROW;
	    break;
	}
	lexer_read_identifier(istream, '-', &token);
	break;
      default:
	if ((syntax_is_letter(c)) || (c == '_')) {
	    lexer_read_identifier(istream, c, &token);
	} else {
	    E_illegal_character(istream, c);
	    goto retry;
	}
	break;
    }
    stream->token = token;
}

NStringP
lexer_string_value(LexerStreamP stream)
{
    ASSERT(stream->token.t == LEXER_TOK_IDENTIFIER);
    return(&(stream->token.u.string));
}

void
lexer_save_terminal(LexerStreamP stream, LexerTokenT error_terminal)
{
    ASSERT(stream->token.t != error_terminal);
    stream->saved_terminal = stream->token.t;
    stream->token.t        = error_terminal;
}

void
lexer_restore_terminal(LexerStreamP stream)
{
    stream->token.t = stream->saved_terminal;
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../generated")
 * end:
**/
