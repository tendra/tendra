/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>
#include <shared/string.h>

#include "obj_c/errors.h"

#include "lex.h"
#include "syntax.h"


/*
    This is the file from which the lexical routine read their input.
*/

static FILE *lex_input;


/*
    Pending characters are dealt with by means of this buffer.  pending
    is set to the start of the buffer to indicate that there are no
    characters pending, otherwise the pending characters are stored in
    the buffer.  The buffer may need increasing in size if the look-ahead
    required by the lexical analyser increases.
*/

static int pending_buff[12] = {'?'};
static int *pending = pending_buff;


/*
    These macros give the mappings between the actions used in the
    automatically generated lexical analyser and the routines defined
    in this file.
*/

static int read_char(void);
static int read_comment(void);
static int read_identifier(int);
static int read_string(void);

#define get_comment(A, B)	read_comment()
#define get_identifier(A)	read_identifier((A))
#define get_string(A)		read_string()
#define unknown_token(A)	lex_unknown
#define unread_char(A)		*(++pending) = (A)


/*
    The main body of the lexical analyser is automatically generated.
*/

#include "lexer.h"


/*
    This routine reads the next character, either from the pending buffer
    or from the input file.
*/

static int
read_char(void)
{
	int c;
	if (pending != pending_buff) {
		c = *(pending--);
	} else {
		c = fgetc(lex_input);
		if (c == '\n') {
			crt_line_no++;
		}
		if (c == EOF) {
			return LEX_EOF;
		}
		c &= 0xff;
	}
	return c;
}


/*
    This buffer is used by read_token to hold the values of identifiers
    and strings.
*/

char token_buff[2000];
static char *token_end = token_buff + sizeof(token_buff);
char *first_comment = NULL;


/*
    This routine reads an identifier beginning with a, returning the
    corresponding lexical token.  Keywords are dealt with locally.
*/

static int
read_identifier(int a)
{
	int c = a, cl;
	char *t = token_buff;
	do {
		*(t++) = (char) c;
		if (t == token_end) {
			error(ERR_FATAL, "Buffer overflow");
		}
		c = read_char();
		cl = lookup_char(c);
	} while (is_alphanum(cl));
	*t = 0;
	unread_char(c);

	/* Deal with keywords */
	t = token_buff;
#define MAKE_KEYWORD(A, B)\
	if (!strcmp(t, (A))) return B;
#include "keyword.h"
	return lex_identifier;
}


/*
    This routine reads a string.  It is entered after the initial quote has
    been read.  Note that new line characters are allowed in strings.
*/

static int
read_string(void)
{
	int c;
	int escaped = 0;
	char *t = token_buff;
	while (c = read_char(),(c != '"' || escaped)) {
		if (c == LEX_EOF) {
			error(ERR_SERIOUS, "Unexpected end of string");
			break;
		}
		*(t++) = (char) c;
		if (t == token_end) {
			error(ERR_FATAL, "Buffer overflow");
		}
		if (escaped) {
			escaped = 0;
		} else {
			if (c == '\\') {
				escaped = 1;
			}
		}
	}
	*t = 0;
	return lex_string;
}


/*
    This routine reads a C style comment, returning the lexical token
    immediately following.  It is entered after the first two characters
    have been read.
*/

static int
read_comment(void)
{
	int state = 0;
	char *t = token_buff;
	*(t++) = '/';
	*(t++) = '*';
	while (state != 2) {
		int c = read_char();
		if (c == LEX_EOF) {
			error(ERR_SERIOUS, "End of file in comment");
			return lex_eof;
		}
		if (c == '*') {
			state = 1;
		} else if (state == 1 && c == '/') {
			state = 2;
		} else {
			state = 0;
		}
		*(t++) = (char) c;
		if (t == token_end) {
			t = token_buff + 2;
		}
	}
	if (first_comment == NULL) {
		first_comment = xstrdup(token_buff);
	}
	return read_token();
}


/*
    These variables are used by the parser to hold the current and former
    lexical tokens.
*/

int crt_lex_token;
int saved_lex_token;


/*
    This routine processes the input file nm.  If nm is the null string
    then the standard input is used.
*/

void
process_file(char *nm)
{
	crt_line_no = 1;
	if (nm == NULL || !strcmp(nm, "-")) {
		crt_file_name = "stdin";
		lex_input = stdin;
		nm = NULL;
	} else {
		crt_file_name = nm;
		lex_input = fopen(nm, "r");
		if (lex_input == NULL) {
			error(ERR_SERIOUS, "Can't open input file, '%s'", nm);
			return;
		}
	}
	ADVANCE_LEXER;
	read_errors();
	if (nm != NULL) {
		IGNORE fclose(lex_input);
	}
	return;
}
