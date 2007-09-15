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
 * c-lexer.c - SID C lexical analyser.
 *
 * This file implements the SID C lexical analyser.  Any changes to the syntax
 * of SID identifiers should be made both here and in the file
 * "lexer.c".
 */

#include <assert.h>
#include <ctype.h>

#include "c-lexer.h"
#include "../gen-errors.h"

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

static BoolT
c_lexer_skip_bracketed_comment(IStreamT * istream)
{
    char c1;
    char c2;

  redo1:
    LEXER_READ_ONE_CHAR(istream, redo1, eof, c1);
  redo2:
    LEXER_READ_ONE_CHAR(istream, redo2, eof, c2);
    for (;;) {
	if ((c1 == '/') && (c2 == '*')) {
	    if (!c_lexer_skip_bracketed_comment(istream)) {
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
c_lexer_skip_white_space(IStreamT * istream)
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
		if (!c_lexer_skip_bracketed_comment(istream)) {
		  eof_in_comment:
		    E_c_eof_in_comment(istream);
		    return('\0'); /*FOR EOF*/
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
		E_c_illegal_comment_character(istream, c);
		break;
	    }
	    break;
	  default:
	    if (!isspace((unsigned char)c)) {
		return(c);
	    }
	    break;
	}
    }
  eof:
    return('\0'); /*FOR EOF*/
}

static void
c_lexer_read_builtin(IStreamT * istream, CLexT * token)
{
    DStringT dstring;
    char * cstring;

    dstring_init(&dstring);
    for (;;) {
	char c;

      redo:
	switch (c = ISTREAM_READ_CHAR(istream)) {
	  case '\0':
	    ISTREAM_HANDLE_NULL(istream, redo, eof);
	    E_c_null_character_in_builtin(istream);
	    break;
	  case '\n':
	    istream_inc_line(istream);
	    E_c_newline_in_builtin(istream);
	    goto done;
	  case '%':
	    goto done;
	  default:
	    dstring_append_char(&dstring, c);
	    break;
	}
    }
  eof:
    E_c_eof_in_builtin(istream);
  done:
    cstring = dstring_destroy_to_cstring(&dstring);
    if (cstring_ci_equal(cstring, "prefixes")) {
	token->t = C_TOK_BLT_PREFIXES;
    } else if (cstring_ci_equal(cstring, "maps")) {
	token->t = C_TOK_BLT_MAPS;
    } else if (cstring_ci_equal(cstring, "assignments")) {
	token->t = C_TOK_BLT_ASSIGNMENTS;
    } else if (cstring_ci_equal(cstring, "assign")) {
	token->t = C_TOK_BLT_ASSIGNMENTS;
    } else if (cstring_ci_equal(cstring, "terminals")) {
	token->t = C_TOK_BLT_TERMINALS;
    } else if (cstring_ci_equal(cstring, "header")) {
	token->t = C_TOK_BLT_HEADER;
    } else if (cstring_ci_equal(cstring, "actions")) {
	token->t = C_TOK_BLT_ACTIONS;
    } else if (cstring_ci_equal(cstring, "trailer")) {
	token->t = C_TOK_BLT_TRAILER;
    } else if (cstring_ci_equal(cstring, "result-assignments")) {
	token->t = C_TOK_BLT_RESULT_ASSIGN;
    } else if (cstring_ci_equal(cstring, "result-assign")) {
	token->t = C_TOK_BLT_RESULT_ASSIGN;
    } else if (cstring_ci_equal(cstring, "parameter-assignments")) {
	token->t = C_TOK_BLT_PARAM_ASSIGN;
    } else if (cstring_ci_equal(cstring, "parameter-assign")) {
	token->t = C_TOK_BLT_PARAM_ASSIGN;
    } else if (cstring_ci_equal(cstring, "param-assignments")) {
	token->t = C_TOK_BLT_PARAM_ASSIGN;
    } else if (cstring_ci_equal(cstring, "param-assign")) {
	token->t = C_TOK_BLT_PARAM_ASSIGN;
    } else {
	E_c_unknown_builtin(istream, cstring);
	UNREACHED;
    }
    DEALLOCATE(cstring);
}

static void
c_lexer_read_identifier(IStreamT * istream, char c, CLexT * token)
{
    BoolT    c_ident = (c != '-');
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
	    if (isalpha((unsigned char)c) || isdigit((unsigned char)c) ||
		(c == '_') || (c == '-')) {
	      redo2:
		LEXER_READ_ONE_CHAR(istream, redo2, done, c);
		dstring_append_char(&dstring, c);
		if (c == '-') {
		    c_ident = FALSE;
		}
	    } else {
		goto done;
	    }
	    break;
	}
    }
  done:
    if (c_ident) {
	token->t = C_TOK_C_IDENTIFIER;
    } else {
	token->t = C_TOK_SID_IDENTIFIER;
    }
    dstring_to_nstring(&dstring, &(token->u.string));
    dstring_destroy(&dstring);
}

static void
c_lexer_read_code_id(IStreamT * istream, char c, NStringT * nstring)
{
    BoolT    numbers_ok = (isalpha((unsigned char)c) || (c == '_'));
    DStringT dstring;
    char     c1;

    dstring_init(&dstring);
    if (numbers_ok) {
	dstring_append_char(&dstring, c);
    }
    for (;;) {
      redo1:
	switch (c1 = ISTREAM_PEEK_CHAR(istream)) {
	  case '\0':
	    ISTREAM_HANDLE_NULL(istream, redo1, done);
	    goto done;
	  default:
	    if (isalpha((unsigned char)c1) || (c1 == '_') ||
		(numbers_ok && isdigit((unsigned char)c1))) {
	      redo2:
		LEXER_READ_ONE_CHAR(istream, redo2, done, c1);
		dstring_append_char(&dstring, c1);
		numbers_ok = TRUE;
	    } else {
		goto done;
	    }
	    break;
	}
    }
  done:
    if (!numbers_ok) {
	E_c_expected_at_id(istream, c);
    }
    dstring_to_nstring(&dstring, nstring);
    dstring_destroy(&dstring);
}

static void
c_lexer_flush_string(DStringT * dstring, CCodeT * code, BoolT force_nl)
{
    NStringT nstring;

    if (dstring_length(dstring) > 0) {
	if (force_nl && (!dstring_last_char_equal(dstring, '\n'))) {
	    dstring_append_char(dstring, '\n');
	}
	dstring_to_nstring(dstring, &nstring);
	c_code_append_string(code, &nstring);
	dstring_destroy(dstring);
	dstring_init(dstring);
    } else if (force_nl) {
	nstring_copy_cstring(&nstring, "\n");
	c_code_append_string(code, &nstring);
    }
}

static BoolT
c_lexer_read_at(IStreamT * istream, DStringT * dstring, CCodeT * code)
{
    char     c;
    NStringT nstring;

  redo:
    switch (c = ISTREAM_READ_CHAR(istream)) {
      case '\0':
	ISTREAM_HANDLE_NULL(istream, redo, error);
	goto error;
      case '\n':
	istream_inc_line(istream);
	goto error;
      case '@':
	dstring_append_char(dstring, c);
	break;
      case '}':
	return(TRUE);
      case '!':
	c_lexer_flush_string(dstring, code, FALSE);
	c_code_append_exception(code);
	break;
      case '.':
	c_lexer_flush_string(dstring, code, FALSE);
	c_code_append_terminal(code);
	break;
      case '>':
	c_lexer_flush_string(dstring, code, FALSE);
	c_code_append_advance(code);
	break;
      case ':':
	c_lexer_flush_string(dstring, code, FALSE);
	c_lexer_read_code_id(istream, ':', &nstring);
	c_code_append_label(code, &nstring);
	break;
      case '&':
	c_lexer_flush_string(dstring, code, FALSE);
	c_lexer_read_code_id(istream, '&', &nstring);
	c_code_append_reference(code, &nstring);
	break;
      case '=':
	c_lexer_flush_string(dstring, code, FALSE);
	c_lexer_read_code_id(istream, '=', &nstring);
	c_code_append_modifiable(code, &nstring);
	break;
      default:
	if (isalpha((unsigned char)(c)) || (c == '_')) {
	    c_lexer_flush_string(dstring, code, FALSE);
	    c_lexer_read_code_id(istream, c, &nstring);
	    c_code_append_identifier(code, &nstring);
	} else {
	  error:
	    E_c_illegal_at_char(istream, c);
	}
	break;
    }
    return(FALSE);
}

static void
c_lexer_read_code(IStreamT * istream, CLexT * token)
{
    CCodeT *   code = c_code_create(istream_name(istream),
				   istream_line(istream));
    DStringT dstring;
    char     c;

  redo1:
    switch (ISTREAM_PEEK_CHAR(istream)) {
      case '\0':
	ISTREAM_HANDLE_NULL(istream, redo1, error);
	goto error;
      case '{':
      redo2:
	LEXER_READ_ONE_CHAR(istream, redo2, error, c);
	UNUSED(c);
	break;
      default:
      error:
	E_c_code_block_syntax(istream);
	break;
    }
    dstring_init(&dstring);
    for (;;) {
      redo3:
	switch (c = ISTREAM_READ_CHAR(istream)) {
	  case '\0':
	    ISTREAM_HANDLE_NULL(istream, redo3, eof);
	    dstring_append_char(&dstring, c);
	    break;
	  case '\n':
	    istream_inc_line(istream);
	    dstring_append_char(&dstring, c);
	    break;
	  case '@':
	    if (c_lexer_read_at(istream, &dstring, code)) {
		goto done;
	    }
	    break;
	  default:
	    dstring_append_char(&dstring, c);
	    break;
	}
    }
  eof:
    E_c_eof_in_code(istream);
  done:
    token->t = C_TOK_CODE;
    c_lexer_flush_string(&dstring, code, TRUE);
    dstring_destroy(&dstring);
    token->u.code = code;
}


/*
 * Externally visible functions
 */

void
c_lexer_init(CLexerStreamT * stream, IStreamT * istream)
{
    istream_assign(&(stream->istream), istream);
    c_lexer_next_token(stream);
}

void
c_lexer_close(CLexerStreamT * stream)
{
    istream_close(&(stream->istream));
}

char *
c_lexer_stream_name(CLexerStreamT * stream)
{
    return(istream_name(&(stream->istream)));
}

unsigned
c_lexer_stream_line(CLexerStreamT * stream)
{
    return(istream_line(&(stream->istream)));
}

CTokenT
c_lexer_get_terminal(CLexerStreamT * stream)
{
    return(stream->token.t);
}

void
c_lexer_next_token(CLexerStreamT * stream)
{
    IStreamT * istream = &(stream->istream);
    CLexT    token;
    char     c;

  retry:
    switch (c = c_lexer_skip_white_space(istream)) {
      case '\0': /*FOR EOF*/
	token.t = C_TOK_EOF;
	break;
      case '%':
	c_lexer_read_builtin(istream, &token);
	break;
      case ',':
	token.t = C_TOK_SEPARATOR;
	break;
      case ':':
	token.t = C_TOK_TYPEMARK;
	break;
      case ';':
	token.t = C_TOK_TERMINATOR;
	break;
      case '<':
	token.t = C_TOK_BEGIN_ACTION;
	break;
      case '=':
	token.t = C_TOK_DEFINE;
	break;
      case '>':
	token.t = C_TOK_END_ACTION;
	break;
      case '(':
	token.t = C_TOK_OPEN_TUPLE;
	break;
      case ')':
	token.t = C_TOK_CLOSE_TUPLE;
	break;
      case '&':
	token.t = C_TOK_REFERENCE;
	break;
      case '@':
	c_lexer_read_code(istream, &token);
	break;
      case '-':
	if ((istream_peek_char(istream, &c)) && (c == '>')) {
	   (void)istream_read_char(istream, &c);
	    token.t = C_TOK_ARROW;
	    break;
	}
	c_lexer_read_identifier(istream, '-', &token);
	break;
      default:
	if (isalpha((unsigned char)(c)) || (c == '_')) {
	    c_lexer_read_identifier(istream, c, &token);
	} else {
	    E_c_illegal_character(istream, c);
	    goto retry;
	}
	break;
    }
    stream->token = token;
}

NStringT *
c_lexer_string_value(CLexerStreamT * stream)
{
    assert((stream->token.t == C_TOK_C_IDENTIFIER) ||
	   (stream->token.t == C_TOK_SID_IDENTIFIER));
    return(&(stream->token.u.string));
}

CCodeT *
c_lexer_code_value(CLexerStreamT * stream)
{
    assert(stream->token.t == C_TOK_CODE);
    return(stream->token.u.code);
}

void
c_lexer_save_terminal(CLexerStreamT * stream, CTokenT error_terminal)
{
    assert(stream->token.t != error_terminal);
    stream->saved_terminal = stream->token.t;
    stream->token.t        = error_terminal;
}

void
c_lexer_restore_terminal(CLexerStreamT * stream)
{
    stream->token.t = stream->saved_terminal;
}
