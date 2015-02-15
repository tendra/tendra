/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>

#include <shared/error.h>
#include <shared/xalloc.h>
#include <shared/string.h>

#include "obj_c/tdf.h"
#include "obj_c/cmd_ops.h"
#include "obj_c/spec_ops.h"
#include "input.h"
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

static int pending_buff[12] = { '?' };
static int *pending = pending_buff;


/*
    These macros give the mappings between the actions used in the
    automatically generated lexical analyser and the routines defined
    in this file.
*/

static int read_char(void);
static int read_comment(void);
static int read_identifier(int);
static int read_number(int);

#define get_comment(A)		read_comment()
#define get_identifier(A)	read_identifier((A))
#define get_number(A)		read_number((A))
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
	if (c == '\n') crt_line_no++;
	if (c == EOF) return LEX_EOF;
	c &= 0xff;
    }
    return c;
}


/*
    This buffer is used by read_token to hold the values of identifiers.
    Similarly token_value is used to hold the values of numbers.
*/

char token_buff[2000];
static char *token_end = token_buff + sizeof(token_buff);
char *first_comment = NULL;
unsigned token_value = 0;


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
	*(t++) = (char)c;
	if (t == token_end) error(ERR_FATAL, "Buffer overflow");
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
    return lex_name;
}


/*
    This routine reads a number.  It is entered after the initial digit,
    a, has been read.  The number's value is stored in token_value.
*/

static int
read_number(int a)
{
    int c = a, cl;
    unsigned n = 0;
    do {
	unsigned m = 10 * n + (unsigned)(c - '0');
	if (m < n) error(ERR_SERIOUS, "Number overflow");
	n = m;
	c = read_char();
	cl = lookup_char(c);
    } while (is_digit(cl));
    unread_char(c);
    token_value = n;
    return lex_number;
}


/*
    This routine reads a shell style comment.  It is entered after the
    initial hash character has been read.
*/

static int
read_comment(void)
{
    int c;
    char *t = token_buff;
    do {
	*(t++) = ' ';
	if (t == token_end) t = token_buff;
	*(t++) = '*';
	if (t == token_end) t = token_buff;
	do {
	    c = read_char();
	    if (c == LEX_EOF) {
		error(ERR_SERIOUS, "End of file in comment");
		return lex_eof;
	    }
	    *(t++) = (char)c;
	    if (t == token_end) t = token_buff;
	} while (c != '\n');
	c = read_char();
    } while (c == '#');
    unread_char(c);
    *t = 0;
    if (first_comment == 0) first_comment = xstrdup(token_buff);
    return read_token();
}


/*
    This routine returns the address of the first non-white space character
    from the string ps.  It returns the null pointer if the end of the line
    is reached.
*/

static char *
get_command(char **ps)
{
    char *t = *ps;
    char *s = t;
    if (s) {
	char c;
	while (c = *s,(c == ' ' || c == '\t' || c == '\r')) {
	    *s = 0;
	    s++;
	}
	if (c == '#' || c == '\n' || c == 0) {
	    *s = 0;
	    *ps = NULL;
	    return NULL;
	}
	t = s;
	while (c = *s, !(c == ' ' || c == '\t' || c == '\r' ||
			   c == '\n' || c == 0)) {
	    s++;
	}
	*ps = s;
    }
    return t;
}


/*
    This routine reads a template file from the current input file.
*/

COMMAND
read_template(COMMAND p)
{
    int go = 1;
    char buff[1000];
    FILE *f = lex_input;
    int ln1 = crt_line_no;
    LIST(COMMAND)q = NULL_list(COMMAND);
    do {
	COMMAND r = NULL_cmd;
	int ln2 = crt_line_no;
	char *s = fgets(buff, 1000, f);
	if (s == NULL) {
	    /* End of file */
	    if (IS_cmd_cond(p)) {
		error(ERR_SERIOUS, "End of '@if' expected");
	    } else if (IS_cmd_loop(p)) {
		error(ERR_SERIOUS, "End of '@loop' expected");
	    }
	    break;
	}
	s = xstrdup(s);
	if (s[0] == '@') {
	    /* Complex command */
	    int complex = 1;
	    char *s1, *s2, *s3;
	    s++;
	    s1 = get_command(&s);
	    if (s1 == NULL) s1 = "<empty>";
	    s2 = get_command(&s);
	    s3 = get_command(&s);
	    if (!strcmp(s1, "if")) {
		if (s2 == NULL) {
		    error(ERR_SERIOUS, "Incomplete '@%s' command", s1);
		    s2 = "true";
		}
		MAKE_cmd_cond(ln2, s2, NULL_cmd, NULL_cmd, r);
	    } else if (!strcmp(s1, "else")) {
		if (IS_cmd_cond(p)) {
		    COMMAND v = DEREF_cmd(cmd_cond_true_code(p));
		    if (!IS_NULL_cmd(v)) {
			error(ERR_SERIOUS, "Duplicate '@%s' command", s1);
		    }
		    q = REVERSE_list(q);
		    MAKE_cmd_compound(ln1, q, v);
		    COPY_cmd(cmd_cond_true_code(p), v);
		    q = NULL_list(COMMAND);
		    ln1 = ln2;
		} else {
		    error(ERR_SERIOUS, "Misplaced '@%s' command", s1);
		}
		s3 = s2;
	    } else if (!strcmp(s1, "endif")) {
		if (IS_cmd_cond(p)) {
		    go = 0;
		} else {
		    error(ERR_SERIOUS, "Misplaced '@%s' command", s1);
		}
		s3 = s2;
	    } else if (!strcmp(s1, "loop")) {
		if (s2 == NULL) {
		    error(ERR_SERIOUS, "Incomplete '@%s' command", s1);
		    s2 = "false";
		}
		MAKE_cmd_loop(ln2, s2, NULL_cmd, r);
	    } else if (!strcmp(s1, "end")) {
		if (IS_cmd_loop(p)) {
		    go = 0;
		} else {
		    error(ERR_SERIOUS, "Misplaced '@%s' command", s1);
		}
		s3 = s2;
	    } else if (!strcmp(s1, "use")) {
		if (s2 == NULL) {
		    error(ERR_SERIOUS, "Incomplete '@%s' command", s1);
		    s2 = "all";
		}
		MAKE_cmd_use(ln2, s2, s3, r);
		if (s3) s3 = get_command(&s);
		complex = 0;
	    } else if (!strcmp(s1, "special")) {
		if (s2 == NULL) {
		    error(ERR_SERIOUS, "Incomplete '@%s' command", s1);
		    s2 = "<none>";
		}
		MAKE_cmd_special(ln2, s2, s3, r);
		if (s3) s3 = get_command(&s);
		complex = 0;
	    } else if (!strcmp(s1, "comment")) {
		s3 = NULL;
	    } else {
		error(ERR_SERIOUS, "Unknown command, '@%s'", s1);
		s3 = NULL;
	    }
	    if (s3) {
		error(ERR_SERIOUS, "End of '@%s' expected", s1);
	    }
	    crt_line_no = ln2 + 1;
	    if (!IS_NULL_cmd(r)) {
		/* Read body of command */
		if (complex) {
		    COMMAND u = read_template(r);
		    if (IS_cmd_cond(r)) {
			COMMAND v = DEREF_cmd(cmd_cond_true_code(r));
			if (IS_NULL_cmd(v)) {
			    COPY_cmd(cmd_cond_true_code(r), u);
			} else {
			    COPY_cmd(cmd_cond_false_code(r), u);
			}
		    } else if (IS_cmd_loop(r)) {
			COPY_cmd(cmd_loop_body(r), u);
		    }
		}
		CONS_cmd(r, q, q);
	    }
	} else {
	    /* Simple command */
	    MAKE_cmd_simple(ln2, s, r);
	    CONS_cmd(r, q, q);
	    crt_line_no = ln2 + 1;
	}
    } while (go);
    q = REVERSE_list(q);
    MAKE_cmd_compound(ln1, q, p);
    return p;
}


/*
    These variables are used by the parser to hold the current and former
    lexical tokens.
*/

int crt_lex_token;
int saved_lex_token;


/*
    This routine opens the input file nm.  It returns true if the file is
    opened successfully.
*/

int
open_file(char *nm)
{
    crt_line_no = 1;
    if (nm == NULL || !strcmp(nm, "-")) {
	crt_file_name = "stdin";
	lex_input = stdin;
    } else {
	crt_file_name = nm;
	lex_input = fopen(nm, "r");
	if (lex_input == NULL) {
	    error(ERR_SERIOUS, "Can't open input file, '%s'", nm);
	    return 0;
	}
    }
    return 1;
}


/*
    This routine closes the current input file.
*/

void
close_file(void)
{
    FILE *f = lex_input;
    if (f != stdin) (void) fclose(f);
    return;
}
