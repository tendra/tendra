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

#define LEXER_READ_ONE_CHAR(istream, redo, eof, id) \
    switch ((id) = ISTREAM_READ_CHAR (istream)) { \
      case '\0': \
        ISTREAM_HANDLE_NULL ((istream), redo, eof); \
        break; \
      case '\n': \
        istream_inc_line (istream); \
        break; \
      default: \
        break; \
    }

/*--------------------------------------------------------------------------*/

static BoolT
lexer_skip_bracketed_comment PROTO_N ((istream))
			     PROTO_T (IStreamP istream)
{
    char c1;
    char c2;

  redo1:
    LEXER_READ_ONE_CHAR (istream, redo1, eof, c1);
  redo2:
    LEXER_READ_ONE_CHAR (istream, redo2, eof, c2);
    for (;;) {
	if ((c1 == '/') && (c2 == '*')) {
	    if (!lexer_skip_bracketed_comment (istream)) {
		goto eof;
	    }
	  redo3:
	    LEXER_READ_ONE_CHAR (istream, redo3, eof, c2);
	} else if ((c1 == '*') && (c2 == '/')) {
	    return (TRUE);
	}
	c1 = c2;
      redo4:
	LEXER_READ_ONE_CHAR (istream, redo4, eof, c2);
    }
  eof:
    return (FALSE);
}

static char
lexer_skip_white_space PROTO_N ((istream))
		       PROTO_T (IStreamP istream)
{
    for (;;) {
	char c;

      redo1:
	switch (c = ISTREAM_READ_CHAR (istream)) {
	  case '\0':
	    ISTREAM_HANDLE_NULL (istream, redo1, eof);
	    break;
	  case '\n':
	    istream_inc_line (istream);
	    break;
	  case '/':
	  redo2:
	    switch (c = ISTREAM_READ_CHAR (istream)) {
	      case '\0':
		ISTREAM_HANDLE_NULL (istream, redo2, eof_in_comment);
		goto illegal_in_comment;
	      case '\n':
		istream_inc_line (istream);
		goto illegal_in_comment;
	      case '*':
		if (!lexer_skip_bracketed_comment (istream)) {
		  eof_in_comment:
		    E_eof_in_comment (istream);
		    return ('\0'); /*FOR EOF*/
		}
		break;
	      case '/':
		do {
		  redo3:
		    LEXER_READ_ONE_CHAR (istream, redo3, eof, c);
		} while (c != '\n');
		break;
	      default:
	      illegal_in_comment:
		E_illegal_comment_character (istream, c);
		break;
	    }
	    break;
	  default:
	    if (!syntax_is_white_space (c)) {
		return (c);
	    }
	    break;
	}
    }
  eof:
    return ('\0'); /*FOR EOF*/
}

static void
lexer_read_builtin PROTO_N ((istream, token))
		   PROTO_T (IStreamP istream X
			    LexP     token)
{
    DStringT dstring;
    CStringP cstring;

    dstring_init (&dstring);
    for (;;) {
	char c;

      redo:
	switch (c = ISTREAM_READ_CHAR (istream)) {
	  case '\0':
	    ISTREAM_HANDLE_NULL (istream, redo, eof);
	    E_null_character_in_builtin (istream);
	    break;
	  case '\n':
	    istream_inc_line (istream);
	    E_newline_in_builtin (istream);
	    goto done;
	  case '%':
	    goto done;
	  default:
	    dstring_append_char (&dstring, c);
	}
    }
  eof:
    E_eof_in_builtin (istream);
  done:
    cstring = dstring_destroy_to_cstring (&dstring);
    if (cstring_ci_equal (cstring, "types")) {
	token->t = LEXER_TOK_BLT_TYPES;
    } else if (cstring_ci_equal (cstring, "terminals")) {
	token->t = LEXER_TOK_BLT_TERMINALS;
    } else if (cstring_ci_equal (cstring, "productions")) {
	token->t = LEXER_TOK_BLT_PRODUCTIONS;
    } else if (cstring_ci_equal (cstring, "entry")) {
	token->t = LEXER_TOK_BLT_ENTRY;
    } else {
	E_unknown_builtin (istream, cstring);
	UNREACHED;
    }
    DEALLOCATE (cstring);
}

static void
lexer_read_identifier PROTO_N ((istream, c, token))
		      PROTO_T (IStreamP istream X
			       char     c X
			       LexP     token)
{
    DStringT dstring;

    dstring_init (&dstring);
    dstring_append_char (&dstring, c);
    for (;;) {
      redo1:
	switch (c = ISTREAM_PEEK_CHAR (istream)) {
	  case '\0':
	    ISTREAM_HANDLE_NULL (istream, redo1, done);
	    goto done;
	  default:
	    if ((syntax_is_letter (c)) || (syntax_is_digit (c)) ||
		(c == '_') || (c == '-')) {
	      redo2:
		LEXER_READ_ONE_CHAR (istream, redo2, done, c);
		dstring_append_char (&dstring, c);
	    } else {
		goto done;
	    }
	    break;
	}
    }
  done:
    token->t = LEXER_TOK_IDENTIFIER;
    dstring_to_nstring (&dstring, &(token->u.string));
    dstring_destroy (&dstring);
}

/*--------------------------------------------------------------------------*/

void
lexer_init PROTO_N ((stream, istream))
	   PROTO_T (LexerStreamP stream X
		    IStreamP     istream)
{
    istream_assign (&(stream->istream), istream);
    lexer_next_token (stream);
}

#ifdef FS_FAST
#undef lexer_close
#endif /* defined (FS_FAST) */
void
lexer_close PROTO_N ((stream))
	    PROTO_T (LexerStreamP stream)
{
    istream_close (&(stream->istream));
}
#ifdef FS_FAST
#define lexer_close(s) (istream_close (&((s)->istream)))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef lexer_stream_name
#endif /* defined (FS_FAST) */
CStringP
lexer_stream_name PROTO_N ((stream))
		  PROTO_T (LexerStreamP stream)
{
    return (istream_name (&(stream->istream)));
}
#ifdef FS_FAST
#define lexer_stream_name(s) (istream_name (&((s)->istream)))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef lexer_stream_line
#endif /* defined (FS_FAST) */
unsigned
lexer_stream_line PROTO_N ((stream))
		  PROTO_T (LexerStreamP stream)
{
    return (istream_line (&(stream->istream)));
}
#ifdef FS_FAST
#define lexer_stream_line(s) (istream_line (&((s)->istream)))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef lexer_get_terminal
#endif /* defined (FS_FAST) */
LexerTokenT
lexer_get_terminal PROTO_N ((stream))
		   PROTO_T (LexerStreamP stream)
{
    return (stream->token.t);
}
#ifdef FS_FAST
#define lexer_get_terminal(s) ((s)->token.t)
#endif /* defined (FS_FAST) */

void
lexer_next_token PROTO_N ((stream))
		 PROTO_T (LexerStreamP stream)
{
    IStreamP istream = &(stream->istream);
    LexT     token;
    char     c;

  retry:
    switch (c = lexer_skip_white_space (istream)) {
      case '\0': /*FOR EOF*/
	token.t = LEXER_TOK_EOF;
	break;
      case '#':
	if ((istream_peek_char (istream, &c)) && (c == '#')) {
	    (void) istream_read_char (istream, &c);
	    token.t = LEXER_TOK_HANDLER_SEP;
	    break;
	}
	E_expected_hash (istream);
	goto retry;
      case '$':
	token.t = LEXER_TOK_EMPTY;
	break;
      case '%':
	lexer_read_builtin (istream, &token);
	break;
      case '|':
	if ((istream_peek_char (istream, &c)) && (c == '|')) {
	    (void) istream_read_char (istream, &c);
	    token.t = LEXER_TOK_ALT_SEP;
	    break;
	}
	E_expected_pipe (istream);
	goto retry;
      case ',':
	token.t = LEXER_TOK_SEPARATOR;
	break;	
      case ':':
	if ((istream_peek_char (istream, &c)) && (c == ':')) {
	    (void) istream_read_char (istream, &c);
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
	if ((istream_peek_char (istream, &c)) && (c == '>')) {
	    (void) istream_read_char (istream, &c);
	    token.t = LEXER_TOK_ARROW;
	    break;
	}
	lexer_read_identifier (istream, '-', &token);
	break;
      default:
	if ((syntax_is_letter (c)) || (c == '_')) {
	    lexer_read_identifier (istream, c, &token);
	} else {
	    E_illegal_character (istream, c);
	    goto retry;
	}
	break;
    }
    stream->token = token;
}

#ifdef FS_FAST
#undef lexer_string_value
#endif /* defined (FS_FAST) */
NStringP
lexer_string_value PROTO_N ((stream))
		   PROTO_T (LexerStreamP stream)
{
    ASSERT (stream->token.t == LEXER_TOK_IDENTIFIER);
    return (&(stream->token.u.string));
}
#ifdef FS_FAST
#define lexer_string_value(s) (&((s)->token.u.string))
#endif /* defined (FS_FAST) */

void
lexer_save_terminal PROTO_N ((stream, error_terminal))
		    PROTO_T (LexerStreamP stream X
			     LexerTokenT  error_terminal)
{
    ASSERT (stream->token.t != error_terminal);
    stream->saved_terminal = stream->token.t;
    stream->token.t        = error_terminal;
}

void
lexer_restore_terminal PROTO_N ((stream))
		       PROTO_T (LexerStreamP stream)
{
    stream->token.t = stream->saved_terminal;
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../generated")
 * end:
**/
