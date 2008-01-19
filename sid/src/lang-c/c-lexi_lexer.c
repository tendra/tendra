
/*
 * Automatically generated by lexi version 2.0
 */



#include "c-lexer.h"
#include "../gen-errors.h"

/*
 * Lexi interface identifier wrappers.
 *
 * These are defined here just to keep them out of the way; nothing but the
 * lxi file references them.
 *
 * TODO These will be removed once Lexi provides identifier support.
 */
#define c_lexer_read_identifier(c) \
	c_lexer_support_read_id(c, C_TOK_C_IDENTIFIER, c_lexi_group_identbody)

#define c_lexer_act_read_label(c0, c1, c2) \
	c_lexer_support_read_id(c2, C_TOK_ACT_LABEL, c_lexi_group_act_identbody)

#define c_lexer_act_read_reference(c0, c1, c2) \
	c_lexer_support_read_id(c2, C_TOK_ACT_REFERENCE, c_lexi_group_act_identbody)

#define c_lexer_act_read_modifiable(c0, c1, c2) \
	c_lexer_support_read_id(c2, C_TOK_ACT_MODIFIABLE, c_lexi_group_act_identbody)

#define c_lexer_act_read_identifier(c0, c1) \
	c_lexer_support_read_id(c1, C_TOK_ACT_IDENTIFIER, c_lexi_group_act_identbody)

#include "c-lexi_lexer.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

/* LOOKUP TABLE */

typedef uint16_t lookup_type;
static lookup_type lookup_tab[257] = {
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0200, 0x0200, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0200, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0040, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0022, 0x0000, 0x0000,
	0x0082, 0x0082, 0x0082, 0x0082,
	0x0082, 0x0082, 0x0082, 0x0082,
	0x0082, 0x0082, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0083, 0x0083, 0x0083,
	0x0083, 0x0083, 0x0083, 0x0083,
	0x0083, 0x0083, 0x0083, 0x0083,
	0x0083, 0x0083, 0x0083, 0x0083,
	0x0083, 0x0083, 0x0083, 0x0083,
	0x0083, 0x0083, 0x0083, 0x0083,
	0x0083, 0x0083, 0x0083, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0083,
	0x0000, 0x00b3, 0x00b3, 0x00b3,
	0x00b3, 0x00b3, 0x00b3, 0x00b3,
	0x00b3, 0x00b3, 0x00b3, 0x00b3,
	0x00b3, 0x00b3, 0x00b3, 0x00b3,
	0x00b3, 0x00b3, 0x00b3, 0x00b3,
	0x00b3, 0x00b3, 0x00b3, 0x00b3,
	0x00b3, 0x00b3, 0x00b3, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000
};

void c_lexi_push(struct c_lexi_state *state, const int c) {
	assert(state);
	assert(state->buffer_index < sizeof state->buffer / sizeof *state->buffer);
	state->buffer[state->buffer_index++] = c;
}

int c_lexi_pop(struct c_lexi_state *state) {
	assert(state);
	assert(state->buffer_index > 0);
	return state->buffer[--state->buffer_index];
}

void c_lexi_flush(struct c_lexi_state *state) {
	state->buffer_index = 0;
}

int c_lexi_readchar(struct c_lexi_state *state) {
	if(state->buffer_index) {
		return c_lexi_pop(state);
	}

	return c_lexi_getchar();
}

bool c_lexi_group(enum c_lexi_groups group, int c) {
	return lookup_tab[c] & group;
}


#include <string.h>
int c_lexi_keyword(const char *identifier, int notfound) {
	return notfound;
}
/* PRE-PASS ANALYSERS */

void c_lexi_init(struct c_lexi_state *state) {
	state->zone_function = c_lexi_read_token;
	state->buffer_index = 0;
}
/* ZONES PASS ANALYSER PROTOTYPES*/

static int c_lexi_read_token_act(struct c_lexi_state *state);
static int c_lexi_read_token_singleline_comment(struct c_lexi_state *state);
static int c_lexi_read_token_bracketed_comment(struct c_lexi_state *state);
/* MAIN PASS ANALYSERS */

/* MAIN PASS ANALYSER for zone act*/

static int
c_lexi_read_token_act(struct c_lexi_state *state)
{
	start: {
		int c0 = c_lexi_readchar(state);
		if (c_lexi_group(c_lexi_group_act_white, c0)) goto start;
		if (c0 == '@') {
			int c1 = c_lexi_readchar(state);
			switch (c1) {
				case '!': {
					return C_TOK_ACT_EXCEPTION;
				}
				case '&': {
					int c2 = c_lexi_readchar(state);
					if (c_lexi_group(c_lexi_group_identstart, c2)) {
						return c_lexer_act_read_reference(c0, c1, c2);
					}
					c_lexi_push(state, c2);
					break;
				}
				case '.': {
					return C_TOK_ACT_TERMINAL;
				}
				case ':': {
					int c2 = c_lexi_readchar(state);
					if (c_lexi_group(c_lexi_group_identstart, c2)) {
						return c_lexer_act_read_label(c0, c1, c2);
					}
					c_lexi_push(state, c2);
					break;
				}
				case '=': {
					int c2 = c_lexi_readchar(state);
					if (c_lexi_group(c_lexi_group_identstart, c2)) {
						return c_lexer_act_read_modifiable(c0, c1, c2);
					}
					c_lexi_push(state, c2);
					break;
				}
				case '>': {
					return C_TOK_ACT_ADVANCE;
				}
				case '@': {
					return C_TOK_ACT_AT;
				}
				case '}': {
					state->zone_function = c_lexi_read_token;
					return C_TOK_ACT_CODEEND;
				}
			}
			if (c_lexi_group(c_lexi_group_identstart, c1)) {
				return c_lexer_act_read_identifier(c0, c1);
			}
			c_lexi_push(state, c1);
		} else if (c0 == LEXI_EOF) {
			return C_TOK_ACT_EOF;
		}
		return c_lexer_act_read_string(c0);
	}
}
/* MAIN PASS ANALYSER for zone singleline_comment*/

static int
c_lexi_read_token_singleline_comment(struct c_lexi_state *state)
{
	start: {
		int c0 = c_lexi_readchar(state);
		if (c_lexi_group(c_lexi_group_singleline_comment_white, c0)) goto start;
		if (c0 == '\n') {
			state->zone_function = c_lexi_read_token;
			return c_lexi_read_token(state);
		} else if (c0 == LEXI_EOF) {
			E_c_eof_in_comment(&(c_lexer_stream->istream));
			goto start;
		}
		goto start;
	}
}
/* MAIN PASS ANALYSER for zone bracketed_comment*/

static int
c_lexi_read_token_bracketed_comment(struct c_lexi_state *state)
{
	start: {
		int c0 = c_lexi_readchar(state);
		if (c_lexi_group(c_lexi_group_bracketed_comment_white, c0)) goto start;
		if (c0 == '*') {
			int c1 = c_lexi_readchar(state);
			if (c1 == '/') {
				state->zone_function = c_lexi_read_token;
				return c_lexi_read_token(state);
			}
			c_lexi_push(state, c1);
		} else if (c0 == LEXI_EOF) {
			E_c_eof_in_comment(&(c_lexer_stream->istream));
			goto start;
		}
		goto start;
	}
}
/* MAIN PASS ANALYSER for zone global*/

int
c_lexi_read_token(struct c_lexi_state *state)
{
	if(state->zone_function != c_lexi_read_token)
		return (*state->zone_function)(state);
	start: {
		int c0 = c_lexi_readchar(state);
		if (c_lexi_group(c_lexi_group_white, c0)) goto start;
		switch (c0) {
			case '&': {
				return C_TOK_REFERENCE;
			}
			case '(': {
				return C_TOK_OPEN_TUPLE;
			}
			case ')': {
				return C_TOK_CLOSE_TUPLE;
			}
			case ',': {
				return C_TOK_SEPARATOR;
			}
			case '-': {
				int c1 = c_lexi_readchar(state);
				if (c1 == '>') {
					return C_TOK_ARROW;
				}
				c_lexi_push(state, c1);
				break;
			}
			case '/': {
				int c1 = c_lexi_readchar(state);
				if (c1 == '*') {
					state->zone_function = c_lexi_read_token_bracketed_comment;
					return c_lexi_read_token(state);
				} else if (c1 == '/') {
					state->zone_function = c_lexi_read_token_singleline_comment;
					return c_lexi_read_token(state);
				}
				c_lexi_push(state, c1);
				break;
			}
			case ':': {
				return C_TOK_TYPEMARK;
			}
			case ';': {
				return C_TOK_TERMINATOR;
			}
			case '<': {
				return C_TOK_BEGIN_ACTION;
			}
			case '=': {
				return C_TOK_DEFINE;
			}
			case '>': {
				return C_TOK_END_ACTION;
			}
			case '@': {
				int c1 = c_lexi_readchar(state);
				if (c1 == '{') {
					state->zone_function = c_lexi_read_token_act;
					return C_TOK_ACT_CODESTART;
				}
				c_lexi_push(state, c1);
				break;
			}
			case LEXI_EOF: {
				return C_TOK_EOF;
			}
		}
		if (c_lexi_group(c_lexi_group_identstart, c0)) {
			return c_lexer_read_identifier(c0);
		} else if (c_lexi_group(c_lexi_group_builtindlmt, c0)) {
			int c1 = c_lexi_readchar(state);
			if (c_lexi_group(c_lexi_group_builtinstart, c1)) {
				return c_lexer_read_builtin(c0, c1);
			}
			c_lexi_push(state, c1);
		}
		return c_lexer_unknown_token(c0);
	}
}


