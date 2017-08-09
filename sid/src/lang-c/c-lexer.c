/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * c-lexer.c - SID C lexical analyser.
 *
 * This file implements the SID C lexical analyser.  Any changes to the syntax
 * of SID identifiers should be made both here and in the file
 * "lexer.c".
 */

/*
 * XXX Possibly the various calls to c_lexer_readchar() should really call
 * c_lexi_getchar() instead.
 */

#include <assert.h>
#include <ctype.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include "c-lexer.h"
#include "c-lexi_lexer.h"

struct c_lexi_state c_lexer_current_state ;


/*
 * These are global until lexi supports passing opaque pointers, which is
 * planned during its forthcoming API change.
 */
CLexerStreamT *c_lexer_stream;
CLexT *c_lexer_token;
CCodeT *code;

/*
 * Generic identifier-reading support; this takes the type of token
 * to return once the identifier is read.
 *
 * This (and everything using it) will be removed once Lexi supports reading
 * identifiers by itself.
 */
int
c_lexer_support_read_id(int c, int rettok, enum c_lexi_groups bodygroup)
{
	IStreamT *istream;
	DStringT dstring;

	istream = &c_lexer_stream->istream;

	dstring_init(&dstring);
	for (;;) {
		char t;

		dstring_append_char(&dstring, c);

		if (!istream_peek_char(istream, &t)) {
			error_posn(ERR_SERIOUS, istream_name(istream), (int) istream_line(istream),
				"end of file in identifier");
			return C_TOK_EOF;
		}

		c = t;

		if (!c_lexi_group(bodygroup, c)) {
			break;
		}

		c_lexi_getchar();
	}

	c_lexer_token->t = rettok;
	dstring_to_nstring(&dstring, &c_lexer_token->u.string);
	dstring_destroy(&dstring);

	if (rettok == C_TOK_C_HIDENTIFIER) {
		/*
		 * This is a special case; we differentiate between C and SID
		 * identifiers based on the premise that all SID identifiers
		 * contain at least one hyphen.
		 */
		if (nstring_contains(&c_lexer_token->u.string, '-')) {
			c_lexer_token->t = C_TOK_SID_HIDENTIFIER;
		}
	}

	return c_lexer_token->t;
}


/*
 * Externally visible functions. These form sid's interface to the lexer.
 */

void
c_lexer_init(CLexerStreamT *stream, IStreamT *istream)
{
	istream_assign(&stream->istream, istream);
	c_lexer_stream = stream;
	c_lexer_token = &stream->token;
	c_lexi_init(&c_lexer_current_state);
	c_lexer_next_token(stream);
}

void
c_lexer_close(CLexerStreamT *stream)
{
	istream_close(&stream->istream);
}

const char *
c_lexer_stream_name(CLexerStreamT *stream)
{
	return istream_name(&stream->istream);
}

unsigned
c_lexer_stream_line(CLexerStreamT *stream)
{
	return istream_line(&stream->istream);
}

CTokenT
c_lexer_get_terminal(CLexerStreamT *stream)
{
	return stream->token.t;
}

void
c_lexer_next_token(CLexerStreamT *stream)
{
	stream->token = *c_lexer_token;
	c_lexer_token->t = c_lexi_read_token(&c_lexer_current_state);
	c_lexer_token->line = c_lexer_stream_line(stream);
}

NStringT *
c_lexer_string_value(CLexerStreamT *stream)
{
	assert(stream->token.t == C_TOK_C_HIDENTIFIER
		|| stream->token.t == C_TOK_SID_HIDENTIFIER
		|| stream->token.t == C_TOK_ACT_HBASIC
		|| stream->token.t == C_TOK_ACT_HLABEL
		|| stream->token.t == C_TOK_ACT_HMODIFIABLE
		|| stream->token.t == C_TOK_ACT_HIDENTIFIER
		|| stream->token.t == C_TOK_ACT_HREFERENCE
		|| stream->token.t == C_TOK_ACT_HCODESTRING);

	return &stream->token.u.string;
}

CCodeT *
c_lexer_code_value(CLexerStreamT *stream)
{
	assert(stream->token.t == C_TOK_CODE);
	return stream->token.u.code;
}

void
c_lexer_save_terminal(CLexerStreamT *stream, CTokenT error_terminal)
{
	assert(stream->token.t != error_terminal);
	stream->saved_terminal = stream->token.t;
	stream->token.t = error_terminal;
}

void
c_lexer_restore_terminal(CLexerStreamT *stream)
{
	stream->token.t = stream->saved_terminal;
}


/*
 * Lexi interface wrappers.
 */

int
c_lexi_getchar(void)
{
	IStreamT *istream;
	char c;

	istream = &c_lexer_stream->istream;
	assert(istream);

	if (!istream_read_char(istream, &c)) {
		return LEXI_EOF;
	}

	return c;
}

int
c_lexer_read_builtin(int c1)
{
	IStreamT *istream;
	DStringT dstring;
	char *cstring;
	int c;

	istream = &c_lexer_stream->istream;

	dstring_init(&dstring);
	c = c1;	/* [builtinstart] */
	do {
		if (!c_lexi_group(c_lexi_group_builtinbody,c)) {
			error_posn(ERR_SERIOUS, istream_name(&c_lexer_stream->istream), (int) istream_line(&c_lexer_stream->istream),
				"illegal character in identifier': '%C'", (void *) &c);
			return C_TOK_EOF;	/* XXX EOF? */
		}

		dstring_append_char(&dstring, c);

		c = c_lexi_getchar();
		if (c == LEXI_EOF) {
			error_posn(ERR_SERIOUS, istream_name(istream), (int) istream_line(istream),
				"end of file in identifier");
			return C_TOK_EOF;
		}
	} while (!c_lexi_group(c_lexi_group_builtindlmt, c));

	/* XXX This would be replaced by keywords pending lexi's reworked keyword API */
	cstring = dstring_destroy_to_cstring(&dstring);
	if (cstring_ci_equal(cstring, "prefixes")) {
		c_lexer_token->t = C_TOK_BLT_HPREFIXES;
	} else if (cstring_ci_equal(cstring, "persistents")) {
		c_lexer_token->t = C_TOK_BLT_HPERSISTENTS;
	} else if (cstring_ci_equal(cstring, "maps")) {
		c_lexer_token->t = C_TOK_BLT_HMAPS;
	} else if (cstring_ci_equal(cstring, "assignments")) {
		c_lexer_token->t = C_TOK_BLT_HASSIGNMENTS;
	} else if (cstring_ci_equal(cstring, "assign")) {
		c_lexer_token->t = C_TOK_BLT_HASSIGNMENTS;
	} else if (cstring_ci_equal(cstring, "terminals")) {
		c_lexer_token->t = C_TOK_BLT_HTERMINALS;
	} else if (cstring_ci_equal(cstring, "header")) {
		c_lexer_token->t = C_TOK_BLT_HHEADER;
	} else if (cstring_ci_equal(cstring, "actions")) {
		c_lexer_token->t = C_TOK_BLT_HACTIONS;
	} else if (cstring_ci_equal(cstring, "trailer")) {
		c_lexer_token->t = C_TOK_BLT_HTRAILER;
	} else if (cstring_ci_equal(cstring, "result-assignments")) {
		c_lexer_token->t = C_TOK_BLT_HRESULT_HASSIGN;
	} else if (cstring_ci_equal(cstring, "result-assign")) {
		c_lexer_token->t = C_TOK_BLT_HRESULT_HASSIGN;
	} else if (cstring_ci_equal(cstring, "parameter-assignments")) {
		c_lexer_token->t = C_TOK_BLT_HPARAM_HASSIGN;
	} else if (cstring_ci_equal(cstring, "parameter-assign")) {
		c_lexer_token->t = C_TOK_BLT_HPARAM_HASSIGN;
	} else if (cstring_ci_equal(cstring, "param-assignments")) {
		c_lexer_token->t = C_TOK_BLT_HPARAM_HASSIGN;
	} else if (cstring_ci_equal(cstring, "param-assign")) {
		c_lexer_token->t = C_TOK_BLT_HPARAM_HASSIGN;
	} else {
		error_posn(ERR_FATAL, istream_name(istream), (int) istream_line(istream),
			"unknown builtin '%%%s%%'", cstring);
		UNREACHED;
	}
	DEALLOCATE(cstring);

	return c_lexer_token->t;
}

/*
 * Read a code string until an @ is found (since all non-codestring tokens begin
 * with an @).
 */
int
c_lexer_act_read_string(int c)
{
	IStreamT *istream;
	DStringT dstring;

	istream = &c_lexer_stream->istream;

	dstring_init(&dstring);
	for (;;) {
		char t;

		dstring_append_char(&dstring, c);

		if (!istream_peek_char(istream, &t)) {
			error_posn(ERR_SERIOUS, istream_name(istream), (int) istream_line(istream),
				"end of file in C code block");
			return C_TOK_EOF;
		}

		c = t;

		if (c == '@') {
			break;
		}

		c_lexi_getchar();
	}

	c_lexer_token->t = C_TOK_ACT_HCODESTRING;
	dstring_to_nstring(&dstring, &c_lexer_token->u.string);
	dstring_destroy(&dstring);

	return c_lexer_token->t;
}

int
c_lexer_unknown_token(int c)
{
	IStreamT *istream;

	istream = &c_lexer_stream->istream;

	if (c == LEXI_EOF) {
		return C_TOK_EOF;
	}

	error_posn(ERR_SERIOUS, istream_name(istream), (int) istream_line(istream),
		"illegal character '%C'", (void *) &c);
	/*
	 * We try to continue regardless as convenience to the user so that
	 * any further errors might possibly be identified.
	 */
	return c_lexi_read_token(&c_lexer_current_state);
}
