/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include <shared/error.h>

#include "config.h"
#include "types.h"
#include "read_types.h"
#include "analyser.h"
#include "file.h"
#include "names.h"
#include "utility.h"


/*
    The previous line (where any errors were likely to have been).
*/

long line_no = 1;


/*
    This flag controls whether the input should be lisp-like (default)
    or c-like.
*/

boolean func_input = 0;


/*
    The looked_ahead flag is true to indicate that the next word has
    already been read.  The really_analyse flag is false to indicate
    that the next word may be ignored.
*/

boolean looked_ahead = 0;
static boolean really_analyse = 1;


/*
    The input is read into a buffer.
*/

#define BUFFSIZE	5000
static char word_buff[BUFFSIZE];


/*
    The word just read from the input file is word.  It has length
    word_length and input type word_type.
*/

char *word = "";
long word_length;
int word_type = INPUT_EOF;


/*
    In reading a word we almost always read one too many character.
    This is stored in pending.  A value of 0 indicates that there is
    no pending character.
*/

static int pending = 0;


/*
    The next word is read from the input file.
*/

void
read_word(void)
{
	int c;
	char *p;
	int negate = 0;
	unsigned int base = 10;

	/* If we have looked ahead one, return last value */
	if (looked_ahead) {
		looked_ahead = 0;
		return;
	}

	/* Get the first letter */
	if (pending) {
		c = pending;
		if (c == EOF) {
			word_type = INPUT_EOF;
			return;
		}

		pending = 0;
	} else {
		c = getc(input);
		if (c == '\n')
			crt_line_no++;
	}

	/* Step over any white space and comments */
	while (white_space(c) || c == '#') {

		if (c == '#') {
			/* Comments go to the end of the line */
			while (c = getc(input), c != '\n') {
				if (c == EOF) {
					is_fatal = 0;
					input_error("End of file in comment");
					word_type = INPUT_EOF;
					pending = EOF;
					return;
				}
			}

			crt_line_no++;
		} else {
			c = getc(input);
			if (c == '\n')
				crt_line_no++;
		}
	}

	line_no = crt_line_no;

	/* Check for end of file */
	if (c == EOF) {
		word_type = INPUT_EOF;
		pending = EOF;
		return;
	}

	/* Check for open brackets */
	if (c == '(') {
		word = "(";
		word_type = INPUT_OPEN;
		return;
	}

	/* Check for close brackets */
	if (c == ')') {
		word = ")";
		word_type = INPUT_CLOSE;
		return;
	}

	if (func_input) {
		/* Check for commas (c-like input only) */
		if (c == ',') {
			word = ",";
			word_type = INPUT_COMMA;
			return;
		}

		/* Check for semicolons (c-like input only) */
		if (c == ';') {
			word = ";";
			word_type = INPUT_SEMICOLON;
			return;
		}
	}

	/* Check for strings */
	if (c == '"') {
		boolean escaped;
		p = word_buff;

		do {
			boolean ignore = 0;
			escaped = 0;

			c = getc(input);

			if (c == '\n') {
				is_fatal = 0;
				input_error("New line in string");
				crt_line_no++;
				line_no = crt_line_no;
				ignore = 1;
			}

			/* Escape sequences */
			if (c == '\\') {
				escaped = 1;

				c = getc(input);

				if (c == '\n') {
					crt_line_no++;
					line_no = crt_line_no;
					ignore = 1;
				} else if (c == 'n')
					c = '\n';
				else if (c == 't')
					c = '\t';
				else if (octal_digit(c)) {
					int e = (c - '0');

					c = getc(input);

					if (!octal_digit(c)) {
						is_fatal = 0;
						input_error("Invalid escape sequence");
						c = '0';
					}

					e = 8 * e + (c - '0');

					c = getc(input);

					if (!octal_digit(c)) {
						is_fatal = 0;
						input_error("Invalid escape sequence");
						c = '0';
					}

					e = 8 * e + (c - '0');

					c = e;

					if (c >= 256) {
						is_fatal = 0;
						input_error("Invalid escape sequence");
						c = 0;
					}
				}
			}

			if (c == EOF) {
				is_fatal = 0;
				input_error("End of file in string");
				word_type = INPUT_EOF;
				pending = EOF;
				return;
			}

			if (!ignore)
				*(p++) = (char)c;

		} while (c != '"' || escaped);

		*(--p) = 0;

#if 0
		c = getc(input);
		if (c == '\n')crt_line_no++;
		if (!terminator(c)) {
			is_fatal = 0;
			input_error("Terminator character expected");
		}

		pending = c;
#endif
		word = word_buff;
		word_length = (int)(p - word);
		word_type = INPUT_STRING;
		return;
	}

	/* Check for words */
	if (alpha(c)) {
		p = word_buff;

		do {
			*(p++) = (char)c;
			c = getc(input);

			if (c == '\n')
				crt_line_no++;

		} while (alphanum(c));

		*p = 0;

		if (!terminator(c)) {
			is_fatal = 0;
			input_error("Terminator character expected");
		}

		pending = c;
		word = word_buff;
		word_type = INPUT_WORD;

		return;
	}

	/* Check for bars */
	if (c == '|') {
		c = getc(input);

		if (c == '\n')
			crt_line_no++;

		if (!terminator(c)) {
			is_fatal = 0;
			input_error("Terminator character expected");
		}

		pending = c;
		word = "|" ;
		word_type = INPUT_BAR;
		return;
	}

	/* Check for a single dash and arrow */
	if (c == '-') {
		c = getc(input);

		if (c == '\n')
			crt_line_no++;

		if (terminator(c)) {
			pending = c;
			word = "-" ;
			word_type = INPUT_BLANK;
			return;
		}

		if (func_input && c == '>') {
			pending = 0;
			word = "->";
			word_type = INPUT_ARROW;
			return;
		}

		negate = 1;
	}

	/* Step over any signs */
	while (c == '-' || c == '+') {
		if (c == '-')
			negate = 1 - negate;

		c = getc(input);

		if (c == '\n')
			crt_line_no++;
	}

	/* Check for numbers */
	if (c == '0') {
		base = 8;

		c = getc(input);

		if (c == '\n')
			crt_line_no++;

		if (terminator(c)) {
			pending = c;
			word = "0";
			word_type = INPUT_NUMBER;
			return;
		}

		if (c == 'x' || c == 'X') {
			base = 16;

			c = getc(input);

			if (c == '\n')
				crt_line_no++;
		}
	} else if (!dec_digit(c)) {
		is_fatal = 0;
		input_error("Illegal character, %c",(unsigned char)c);
		pending = 0;
		read_word();
		return;
	}

	/* Set up buffer */
	p = word_buff + BUFFSIZE;
	*(--p) = 0;
	*(--p) = '0';
	*(--p) = 0;


	/* Read the number */
	do {
		unsigned n;

		if (dec_digit(c))
			n = (unsigned)(c - '0');
		else if (c >= 'A' && c <= 'F')
			n = 10 + (unsigned)(c - 'A');
		else if (c >= 'a' && c <= 'f')
			n = 10 + (unsigned)(c - 'a');
		else {
			is_fatal = 0;
			input_error("Illegal digit, %c",(unsigned char)c);
			n = 0;
		}

		if (n >= base) {
			is_fatal = 0;
			input_error("Illegal digit, %c",(unsigned char)c);
			n = 0;
		}

		if (really_analyse) {
			p = word_buff + (BUFFSIZE - 2);

			do {
				if (*p == 0)
					*(p - 1) = 0;
				else
					n += base *(unsigned)(*p - '0');

				*p = (char)('0' + (n & 7));
				n >>= 3;
				p--;
			} while (n || *p);
		}

		c = getc(input);

		if (c == '\n')
			crt_line_no++;

	} while (!terminator(c));

	/* Find the start of the number */
	if (really_analyse) {
		for (p = word_buff + (BUFFSIZE - 2); *p; p--)
			/* empty */;

		if (negate)
			*(p--) = '-';
	}

	pending = c;
	word = p + 1;

	if (strcmp(word, "-0") == 0)
		word = "0";

	word_type = INPUT_NUMBER;
}


/*
    This routine skips over the input until the first closing bracket
    unmatched by an open bracket is read.  The routine returns the
    number of word read at the highest bracket level.  (Not currently
    used.)
*/

long
skip_words(void)
{
	long n = 0;
	int level = 1;

	really_analyse = 0;

	while (level) {
		read_word();

		switch (word_type) {
		case INPUT_OPEN:
			level++;
			break;
		case INPUT_CLOSE:
			level--;
			break;
		case INPUT_EOF:
			input_error("Unexpected end of file");
			return n;
		}

		if (level == 1)
			n++;
	}

	really_analyse = 1;

	return n;
}


/*
    The current position in the input file is stored in p.
*/

void
store_position(position *p)
{
	p->line = crt_line_no;
	p->posn = ftell(input);
	p->pending = pending;
	p->ahead = looked_ahead;
}


/*
    The position in the input file is set from p.
*/

void
set_position(position *p)
{
	crt_line_no = p->line;
	pending = p->pending;
	looked_ahead = p->ahead;

	if (fseek(input, p->posn, SEEK_SET))
		fatal_error("Illegal seek command");
}
